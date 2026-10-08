/* GC 3.0 argument parser, retaining the baseline token and argument ABI. */
#include "compiler/common.h"
#include "compiler/objects.h"
#include "driver/Help.h"
#include "driver/Option.h"
#include "driver/CWParserPluginsPrivate.h"
#include "GC_3_0a5_2/driver/ParserDriver.h"
#include "driver/CLFileOps.h"
#include "driver/TargetOptimizer-ppc-eabi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private names from the GC 3.0 symbol map; Windows OSSpec is 516 bytes. */
static int scantok;
static int respfilesize;
static char *respfilestart;
static char *respfile;
static struct {
    unsigned char spec[0x204];
    MemBuffer hand;
    Boolean loaded;
    Boolean changed;
    Boolean writeable;
} respfilehandle;
static char **margv;
static int margind;
static int margc;
static Boolean in_response_file;
static int maxargtoks;
static int numargtoks;
static TokenText *argtoks;

/* The Windows MSL runtime owns the active locale and 16-bit ctype table. */
typedef struct ArgCTypeLocale {
    unsigned char reserved[8];
    unsigned short *ctype;
} ArgCTypeLocale;
typedef struct ArgRuntime {
    unsigned char reserved[0x1bc];
    ArgCTypeLocale *locale;
} ArgRuntime;
extern ArgRuntime *fn_00403ff0(int create);
extern int __stdcall fn_004050e0(char *left, char *right, int count);
extern void *__stdcall xmalloc(const char *what, unsigned int size);
extern void *__stdcall xrealloc(const char *what, void *ptr, unsigned int size);
extern char *__stdcall xstrdup(const char *text);
extern void __stdcall xfree(void *ptr);
extern void Arg_InsertArg(PtrList *list, char *text);
extern void Arg_FreeToolArgs(PtrList *list);
static inline int Arg_IsSpace(int c)
{
    return c < 0 || c >= 256 ? 0 : fn_00403ff0(1)->locale->ctype[c] & 0x100;
}

void Arg_AddToken(short kind, char *text)
{
    long count;
    TokenText *last;
    TokenText *previous;
    TokenText *third;
    TokenText *fourth;
    TokenText *entry;
    if (numargtoks > 0) {
        last = argtoks + (numargtoks - 1);
    } else {
        last = NULL;
    }
    if (last != NULL && last->kind == 2 && last->text[0] == 0) {
        previous = NULL;
        third = NULL;
        fourth = NULL;
        if (numargtoks > 3) {
            fourth = argtoks + (numargtoks - 4);
        }
        if (numargtoks > 2) {
            third = argtoks + (numargtoks - 3);
        }
        if (numargtoks > 1) {
            previous = argtoks + (numargtoks - 2);
        }
        if (previous != NULL) {
            if (kind == 1 && (previous->kind == 5 || previous->kind == 4) && (third->kind != 2 || fourth->kind != 3)) {
                if (data_00588519 != 0) {
                    printf("Coalescing args with '%s'\n", Arg_GetTokenName(previous));
                }
                {
                    short previousKind = previous->kind;
                    numargtoks -= 2;
                    kind = previousKind;
                }
            } else if (previous->kind == 1) {
                if (!(kind != 5 && kind != 4)) {
                    if (data_00588519 != 0) {
                        printf("Coalescing args, removing '%s'\n", Arg_GetTokenName(previous));
                    }
                    numargtoks -= 2;
                }
            }
        }
    }
    count = numargtoks;
    if (count >= maxargtoks) {
        argtoks = xrealloc("argument list", argtoks, maxargtoks + 16 << 3);
        maxargtoks += 16;
    }
    entry = argtoks + numargtoks;
    entry->kind = kind;
    if (text) {
        entry->text = xstrdup(text);
    } else {
        entry->text = NULL;
    }
    numargtoks++;
}

void Arg_Setup(unsigned int value, char **otherValue)
{
    in_response_file = 0;
    respfile = NULL;
    margc = value;
    margv = (char **)otherValue;
    margind = 1;
}

void Arg_SkipRespFileWS(void)
{
    for (;;) {
        while (*respfile && Arg_IsSpace(*respfile))
            respfile++;
        if (*respfile == 0x1a)
            respfile = respfilestart + respfilesize - 1;
        if (respfile[0] == '\\' && respfile[1] == '#') {
            respfile++;
            return;
        }
        if (*respfile == '#' && (respfile > respfilestart ? respfile[-1] != '\\' : 1)) {
            while (*respfile && *respfile != '\n' && *respfile != '\r')
                respfile++;
            while (*respfile == '\r' || *respfile == '\n')
                respfile++;
        } else
            return;
    }
}

Boolean Arg_OpenRespFile(char *name)
{
    char buffer[0x204];
    unsigned int error;
    Boolean result;

    if ((error = OS_MakeFileSpec(name, (OSSpec *)buffer)) != 0 ||
        (error = TargetOptimizer_ppc_eabi_InitOperationRecord((OSSpec *)buffer, NULL, 0,
                                                              (OperationRecord *)&respfilehandle)) != 0 ||
        (error = CLFileOps_AppendMemBuffer(&respfilehandle.hand, &empty_string, 1)) != 0 ||
        (error = TargetOptimizer_ppc_eabi_GetMemBufferPtrAndSize((unsigned char *)&respfilehandle, &respfile,
                                                                 &respfilesize)) != 0) {
        CLPOSAlert(0x4a, error, "response ", name);
        result = 0;
    } else {
        respfilestart = respfile;
        Arg_SkipRespFileWS();
        in_response_file = 1;
        result = 1;
    }
    return result;
}

unsigned int Arg_CloseRespFile(void)
{
    in_response_file = (unsigned char)(0U);
    TargetOptimizer_ppc_eabi_UnloadOperationRecord((struct OperationRecord *)&respfilehandle);
}

char *Arg_GetRespFileToken(void)
{
    int quoted = 0;
    char *start;
    char *d;
    if (!*respfile)
        return NULL;
    start = d = respfile;
    while (*respfile) {
        if (!quoted && Arg_IsSpace(*respfile))
            break;
        if (*respfile == '"') {
            quoted = !quoted;
            respfile++;
        } else if (respfile[0] == '\\' && strchr("\" \r\n", respfile[1])) {
            *d++ = respfile[1];
            respfile += 2;
        } else
            *d++ = *respfile++;
    }
    if (*respfile)
        Arg_SkipRespFileWS();
    *d = 0;
    return start;
}

char *Arg_GetNext(Boolean expand)
{
    char *arg;
    int len;
    for (;;) {
        if (!in_response_file) {
            char *p;
            len = 1;
            p = NULL;
            arg = margv[margind++];
            if ((p = strrchr(arg, '\r')) && p[1] == 0)
                *p = 0;
            if (arg[0] == '\\' && arg[1] == data_0058852c) {
                arg++;
                break;
            }
            if (!expand)
                break;
            if (*arg != data_0058852c) {
                if (!*data_00587eb0)
                    break;
                len = strlen(data_00587eb0);
                if (fn_004050e0(arg, data_00587eb0, len))
                    break;
                if (!arg[len])
                    break;
            }
            if ((p = strchr(arg + len, '=')))
                len = p + 1 - arg;
            if (Arg_OpenRespFile(arg + len))
                continue;
            arg = NULL;
            break;
        } else {
            if ((arg = Arg_GetRespFileToken()))
                break;
            Arg_CloseRespFile();
        }
    }
    if (data_00588519)
        fprintf(stderr, "Got arg = '%s'\n", arg ? arg : "<NULL>");
    return arg;
}

unsigned char Arg_GotMore(void)
{
    if (!in_response_file)
        return margind < margc;
    if (*respfile)
        return 1;
    return margind < margc;
}

void Arg_Parse(void)
{
    char buf[0x1000];
    unsigned char flagA;
    unsigned char flagB;
    char *tok;
    char *src;
    char *dst;
    char ch;
    short kind;
    int i;
    int eq;

    flagA = 0;
    flagB = 0;
    while (Arg_GotMore()) {
        src = Arg_GetNext(1);
        tok = src;
        if (src == NULL)
            break;
        dst = buf;
        *dst = 0;
        flagB = 0;
        if (*src != 0 && src[1] != 0 && strchr(data_00587eec, *src) != NULL) {
            if (flagA || flagB)
                Arg_AddToken(1, NULL);
            *dst = src[1];
            dst++;
            *dst = 0;
            src += 2;
            flagA = 1;
            flagB = 0;
        } else {
            flagA = 0;
        }
        for (; src != NULL && *src != 0; src++) {
            ch = *src;
            if (ch == 0x5c && (src[1] == argument_space || src[1] == argument_space_char || src[1] == data_00588505)) {
                src++;
                ch = *src;
                ch |= 0x80;
            } else if (data_0054aa78 == 1 && ch == 0x3a && src[1] == 0x5c) {
                ch |= 0x80;
            }
            if (ch != argument_space && ch != argument_space_char && ch != data_00588505) {
                if ((ch & 0x7f) == argument_space || (ch & 0x7f) == argument_space_char || (ch & 0x7f) == data_00588505)
                    ch &= 0x7f;
                *dst = ch;
                dst++;
                if (dst >= buf + 0x1000)
                    CLPReportError(2, tok, tok + strlen(tok) - 15, 0x1000);
                *dst = 0;
            } else {
                if (flagA)
                    Arg_AddToken(3, buf);
                Arg_AddToken(2, buf);
                if (ch == 0x2c)
                    kind = 5;
                else {
                    eq = (ch == 0x3d || ch == data_00588505);
                    if (eq)
                        kind = 4;
                    else
                        kind = 0;
                }
                Arg_AddToken(kind, NULL);
                dst = buf;
                *dst = 0;
                if (ch == argument_space || ch == argument_space_char || ch == data_00588505)
                    flagA = 0;
                flagB = 1;
            }
        }
        if (flagA && dst > buf) {
            i = 0;
            if (flagB && strchr(data_00587eec, buf[0]) != NULL)
                i = 1;
            Arg_AddToken(3, buf + i);
            i = 0;
            if (flagB && strchr(data_00587eec, buf[0]) != NULL)
                i = 1;
            Arg_AddToken(2, buf + 1 + i);
        } else {
            Arg_AddToken(2, buf);
            Arg_AddToken(1, NULL);
        }
    }
    if (flagA || flagB)
        Arg_AddToken(1, NULL);
    Arg_AddToken(0, NULL);
}

void Arg_Init(int argc, char **argv)
{
    int argumentIndex;
    int resultIndex;
    int compatibility;

    numargtoks = maxargtoks = 0;
    data_00588519 = 0;
    if (argc > 1) {
        if (memcmp(argv[1], "--parser-debug", 15) == 0) {
            data_00588519 = 1;
            memmove(argv + 1, argv + 2, (argc - 1) * sizeof(*argv));
            argc--;
        }
    }
    compatibility = data_0054aa78;
    if (compatibility == 0) {
        data_00587eec = "-";
        data_005876ac = (int)"=";
        help_option_separator = " ";
        argument_space = ',';
        argument_space_char = '=';
        data_00588505 = '=';
        data_0058852c = '@';
        data_00587eb0 = empty_string;
    } else if (compatibility == 1) {
        data_00587eec = "/-";
        data_005876ac = (int)":";
        help_option_separator = ":";
        argument_space = ',';
        argument_space_char = '=';
        data_00588505 = ':';
        data_0058852c = '@';
        data_00587eb0 = empty_string;
    } else if (compatibility == 2) {
        if (data_00587eec == NULL)
            data_00587eec = "-";
        if (data_005876ac == 0)
            data_005876ac = (int)"=";
        if (help_option_separator == NULL)
            help_option_separator = " ";
        if (argument_space == 0)
            argument_space = ',';
        if (argument_space_char == 0)
            argument_space_char = '=';
        if (data_00588505 == 0)
            data_00588505 = '=';
        if (data_0058852c == 0 && data_00587eb0 == NULL)
            data_0058852c = '@';
        if (data_00587eb0 == NULL)
            data_00587eb0 = empty_string;
    } else {
        CLPFatalError("Unknown parser compatibility type (%d)\n", compatibility);
    }
    if (data_00588519 != 0) {
        printf("Incoming arguments: \n");
        for (argumentIndex = 0; argumentIndex < argc; argumentIndex++)
            printf("[%s] ", argv[argumentIndex]);
        printf("\n");
    }
    Arg_Setup(argc, argv);
    Arg_Parse();
    Arg_Reset();
    if (data_00588519 != 0) {
        for (resultIndex = 0; resultIndex < numargtoks; resultIndex++) {
            printf("TOKEN:  '%s'\n", Arg_GetTokenName(argtoks + resultIndex));
        }
    }
}

void Arg_Terminate(void)
{
    struct TokenText *p;

    while (numargtoks > 0) {
        p = argtoks + --numargtoks;
        if (p->text != NULL)
            xfree(p->text);
    }
    if (maxargtoks != 0)
        xfree(argtoks);
    maxargtoks = 0;
}

void Arg_Reset(void)
{
    scantok = 0;
    return;
}

unsigned int Arg_PeekToken(void)
{
    int i = scantok;
    if (i >= numargtoks) {
        return 0U;
    }
    return (unsigned int)(argtoks + scantok);
}

TokenText *Arg_UsedToken(void)
{
    int c;
    if ((c = scantok) < numargtoks)
        scantok++;
    return (TokenText *)Arg_PeekToken();
}

int Arg_IsEmpty(void)
{
    unsigned short *value = (unsigned short *)Arg_PeekToken();
    return value == NULL || *value == 0;
}

int Arg_GetToken(void)

{
    unsigned int result = Arg_PeekToken();
    if (result != 0) {
        scantok++;
    }
    return result;
}

TokenText *Arg_UndoToken(void)
{
    if (scantok > 0) {
        --scantok;
        return (TokenText *)Arg_PeekToken();
    }
    return NULL;
}

char *Arg_GetTokenName(TokenText *token)
{
    char *result;
    int matchesKind;
    int kind = token->kind;
    int compatibility;
    if (kind == 2)
        return token->text;
    if (kind == 3)
        result = "option";
    else if (kind == 5)
        result = "comma";
    else {
        compatibility = data_0054aa78;
        matchesKind = (compatibility == 1) && (kind == 4);
        if (matchesKind)
            result = "colon or equals";
        else {
            matchesKind = (compatibility != 1) && (kind == 4);
            if (matchesKind)
                result = "equals";
            else if (kind == 1)
                result = "end of argument";
            else if (kind == 0)
                result = "end of command line";
            else
                result = "<error>";
        }
    }
    return result;
}

char *Arg_GetTokenText(TokenText *arg, char *buffer, int maxlen, Boolean warn)
{
    char *d = buffer;
    int n = 0;
    char *s;
    int kind = arg->kind;
    if (kind == 2 || kind == 3)
        s = arg->text;
    else
        s = Arg_GetTokenName(arg);
    while (*s && n++ < maxlen)
        *d++ = *s++;
    if (n < maxlen)
        *d = 0;
    else {
        d[-1] = 0;
        if (warn)
            CLPReportWarning(0x38, buffer, s + strlen(s) - (maxlen > 32 ? 32 : maxlen), maxlen);
    }
    return buffer;
}

void Arg_GrowArgs(PtrList *list)
{
    int i;
    if (!list->items || list->count + 1 >= list->size) {
        i = list->size;
        list->size += 16;
        list->items = xrealloc("argument list", list->items, (list->size + 1) * 4);
        for (; i <= list->size; i++)
            list->items[i] = NULL;
    }
    list->count++;
}

void Arg_GrowArg(struct PtrList *list, char *text)
{
    char **slot = &list->items[list->count];
    int len;
    if (!*slot) {
        *slot = xstrdup(text);
    } else {
        len = strlen(*slot);
        *slot = xrealloc("command line", *slot, len + strlen(text) + 1);
        strcpy(*slot + len, text);
    }
}

void Arg_InitToolArgs(PtrList *state)
{
    state->count = 0;
    state->size = 0;
    state->items = NULL;
    Arg_GrowArgs(state);
}

void Arg_AddToToolArgs(PtrList *list, short kind, char *text)
{
    int insert = (kind & 0x8000) != 0;
    kind &= ~0x8000;
    switch (kind) {
    case 0:
        Arg_FinishToolArgs(list);
        break;
    case 1:
        if (list->items && list->items[list->count])
            Arg_GrowArgs(list);
        break;
    case 2:
        if (insert)
            Arg_InsertArg(list, text);
        else
            Arg_GrowArg(list, text);
        break;
    case 3:
        Arg_GrowArg(list, "-");
        break;
    case 4:
        Arg_GrowArg(list, "=");
        break;
    case 5:
        Arg_GrowArg(list, ",");
        break;
    default:
        CLPFatalError("Arguments.c", 0x31f, "Unknown token (%d)", kind);
    }
}

void Arg_FinishToolArgs(PtrList *list)
{
    Arg_GrowArgs(list);
    list->items[list->count] = NULL;
}

void Arg_ToolArgsForPlugin(PtrList *source, IntegerSequenceResult *result)
{
    unsigned int value;
    result->count = 1;
    result->entries = (int *)source->items;
    while (result->entries[result->count] != 0) {
        result->count++;
    }
    value = 0;
    result->value = value;
    return;
}

/* Insert a tool argument before the first accumulated argument. */
void Arg_InsertArg(PtrList *list, char *text)
{
    Arg_GrowArgs(list);
    memmove(list->items + 2, list->items + 1, (list->size - 1) * sizeof(*list->items));
    list->items[1] = xmalloc("command line", strlen(text) + 1);
    strcpy(list->items[1], text);
}

void Arg_FreeToolArgs(PtrList *list)
{
    int i;
    if (list->items) {
        for (i = 1; i < list->count; i++)
            if (list->items[i])
                xfree(list->items[i]);
        xfree(list->items);
    }
}
