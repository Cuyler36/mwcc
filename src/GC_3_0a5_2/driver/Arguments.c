/* Baseline bodies ported under the source/function names in the 3.0 map. */
#include "compiler/common.h"
#include "GC_3_0a5_2/driver/ParserDriver.h"
#include "compiler/objects.h"
#include "compiler/scopes.h"
#include "compiler/win32.h"
#include "compiler/CError.h"
#include "driver/CLFileOps.h"
#include "driver/CLIO.h"
#include "driver/CLMain.h"
#include "driver/CLPluginRequests.h"
#include "driver/CLToolExec.h"
#include "driver/CWParserPluginsPrivate.h"
#include "driver/CWPluginsPrivate.h"
#include "driver/ClientGlue.h"
#include "driver/Help.h"
#include "driver/Memory.h"
#include "driver/MsDos.h"
#include "driver/Option.h"
#include "driver/TargetOptimizer-ppc-eabi.h"
#include "driver/ToolHelpers-cc.h"
#include "driver/ToolHelpers.h"
#include <stdio.h>
#include <setjmp.h>
#include <stdio.h>

#define pTool driverTool

#define va_start(ap, parm) ap = (char *)&parm + ((((char *)(&parm + 1) - (char *)&parm) + 3) / 4 * 4)

#include <string.h>
void Arg_AddToken(short kind, char *text)
{
    long count;
    TokenText *last;
    TokenText *previous;
    TokenText *third;
    TokenText *fourth;
    TokenText *entry;
    if (coalesced_argument_count > 0) {
        last = token_texts + (coalesced_argument_count - 1);
    } else {
        last = NULL;
    }
    if (last != NULL && last->kind == 2 && last->text[0] == 0) {
        previous = NULL;
        third = NULL;
        fourth = NULL;
        if (coalesced_argument_count > 3) {
            fourth = token_texts + (coalesced_argument_count - 4);
        }
        if (coalesced_argument_count > 2) {
            third = token_texts + (coalesced_argument_count - 3);
        }
        if (coalesced_argument_count > 1) {
            previous = token_texts + (coalesced_argument_count - 2);
        }
        if (previous != NULL) {
            if (kind == 1 && (previous->kind == 5 || previous->kind == 4) && (third->kind != 2 || fourth->kind != 3)) {
                if (data_00588519 != 0) {
                    printf("Coalescing args with '%s'\n", Arg_GetTokenName(previous));
                }
                {
                    short previousKind = previous->kind;
                    coalesced_argument_count -= 2;
                    kind = previousKind;
                }
            } else if (previous->kind == 1) {
                if (!(kind != 5 && kind != 4)) {
                    if (data_00588519 != 0) {
                        printf("Coalescing args, removing '%s'\n", Arg_GetTokenName(previous));
                    }
                    coalesced_argument_count -= 2;
                }
            }
        }
    }
    count = coalesced_argument_count;
    if (count >= coalesced_argument_capacity) {
        token_texts = ToolHelpers_ResizeBuffer("argument list", token_texts, coalesced_argument_capacity + 16 << 3);
        coalesced_argument_capacity += 16;
    }
    entry = token_texts + coalesced_argument_count;
    entry->kind = kind;
    if (text) {
        entry->text = ClientGlue_DuplicateString(text);
    } else {
        entry->text = NULL;
    }
    coalesced_argument_count += 1;
}

void Arg_Setup(unsigned int value, char **otherValue)
{
    data_0057e06c = 0;
    token_cursor = NULL;
    data_0057e070 = value;
    data_0057e078 = (char **)otherValue;
    arg_index = 1;
}

void Arg_SkipRespFileWS(void)
{
    for (;;) {
        while (*token_cursor && (__ctype_map[(unsigned char)*token_cursor] & 6))
            token_cursor++;
        if (*token_cursor == 0x1a)
            token_cursor = data_0057e1d0 + data_0057e1d4 - 1;
        if (token_cursor[0] == '\\' && token_cursor[1] == '#') {
            token_cursor++;
            return;
        }
        if (*token_cursor == '#' && (token_cursor > data_0057e1d0 ? token_cursor[-1] != '\\' : 1)) {
            while (*token_cursor && *token_cursor != '\n' && *token_cursor != '\r')
                token_cursor++;
            while (*token_cursor == '\r' || *token_cursor == '\n')
                token_cursor++;
        } else
            return;
    }
}

Boolean Arg_OpenRespFile(char *name)
{
    char buffer[0x144];
    unsigned int error;
    Boolean result;

    if ((error = OS_MakeFileSpec(name, (OSSpec *)buffer)) != 0 ||
        (error = TargetOptimizer_ppc_eabi_InitOperationRecord((OSSpec *)buffer, NULL, 0,
                                                              (OperationRecord *)&operation_record)) != 0 ||
        (error = CLFileOps_AppendMemBuffer(&data_0057e1c0, &empty_string, 1)) != 0 ||
        (error = TargetOptimizer_ppc_eabi_GetMemBufferPtrAndSize((unsigned char *)&operation_record, &token_cursor,
                                                                 &data_0057e1d4)) != 0) {
        CLPOSAlert(0x4a, error, name);
        result = 0;
    } else {
        data_0057e1d0 = token_cursor;
        Arg_SkipRespFileWS();
        data_0057e06c = 1;
        result = 1;
    }
    return result;
}

unsigned int Arg_CloseRespFile(void)
{
    data_0057e06c = (unsigned char)(0U);
    TargetOptimizer_ppc_eabi_UnloadOperationRecord((struct OperationRecord *)operation_record);
}

char *Arg_GetRespFileToken(void)
{
    int quoted = 0;
    char *start;
    char *d;
    if (!*token_cursor)
        return NULL;
    start = d = token_cursor;
    while (*token_cursor) {
        if (!quoted && (__ctype_map[(unsigned char)*token_cursor] & 6))
            break;
        if (*token_cursor == '"') {
            quoted = !quoted;
            token_cursor++;
        } else if (token_cursor[0] == '\\' && token_cursor[1] == '"') {
            *d++ = '"';
            token_cursor += 2;
        } else
            *d++ = *token_cursor++;
    }
    if (*token_cursor)
        Arg_SkipRespFileWS();
    *d = 0;
    return start;
}

char *Arg_GetNext(Boolean expand)
{
    char *arg;
    int len;
    for (;;) {
        if (!data_0057e06c) {
            char *p;
            len = 1;
            p = NULL;
            arg = data_0057e078[arg_index++];
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
            arg += len;
            if (Arg_OpenRespFile(arg))
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
    if (!data_0057e06c)
        return arg_index < data_0057e070;
    if (*token_cursor)
        return 1;
    return arg_index < data_0057e070;
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
    unsigned char kind;
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
                ch = ch | 0x80;
            } else if (data_0054aa78 == 1 && ch == 0x3a && src[1] == 0x5c) {
                ch = ch | 0x80;
            }
            if (ch != argument_space && ch != argument_space_char && ch != data_00588505) {
                if ((ch & 0x7f) == argument_space || (ch & 0x7f) == argument_space_char || (ch & 0x7f) == data_00588505)
                    ch = ch & 0x7f;
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
            Arg_AddToken(2, buf + i + 1);
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

    coalesced_argument_capacity = 0;
    coalesced_argument_count = 0;
    data_00588519 = 0;
    if (argc > 1) {
        if (memcmp(argv[1], "--parser-debug", 15) == 0) {
            data_00588519 = 1;
            fn_00404ba0((argv + 1), (argv + 2), (argc - 1) * sizeof(*argv));
            argc--;
        }
    }
    if (data_0054aa78 == 0) {
        data_00587eec = "-";
        data_005876ac = (int)"=";
        help_option_separator = " ";
        argument_space = ',';
        argument_space_char = '=';
        data_00588505 = '=';
        data_0058852c = '@';
        data_00587eb0 = empty_string;
    } else if (data_0054aa78 == 1) {
        data_00587eec = "/-";
        data_005876ac = (int)":";
        help_option_separator = ":";
        argument_space = ',';
        argument_space_char = '=';
        data_00588505 = ':';
        data_0058852c = '@';
        data_00587eb0 = empty_string;
    } else if (data_0054aa78 == 2) {
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
        if (data_0058852c == 0)
            data_0058852c = '@';
        if (data_00587eb0 == NULL)
            data_00587eb0 = empty_string;
    } else {
        CLPFatalError("Unknown parser compatibility type (%d)\n", data_0054aa78);
    }
    if (data_00588519 != 0) {
        fn_00403ae0("Incoming arguments: \n");
        for (argumentIndex = 0; argumentIndex < argc; argumentIndex++)
            fn_00403ae0("[%s] ", argv[argumentIndex]);
        fn_00403ae0("\n");
    }
    Arg_Setup(argc, argv);
    Arg_Parse();
    Arg_Reset();
    if (data_00588519 != 0) {
        for (resultIndex = 0; resultIndex < coalesced_argument_count; resultIndex++) {
            fn_00403ae0("TOKEN:  '%s'\n", Arg_GetTokenName(token_texts + resultIndex));
        }
    }
}

void Arg_Terminate(void)
{
    struct TokenText *p;

    while (coalesced_argument_count > 0) {
        p = token_texts + --coalesced_argument_count;
        if (p->text != NULL)
            free(p->text);
    }
    if (coalesced_argument_capacity != 0)
        free(token_texts);
    coalesced_argument_capacity = 0;
}

void Arg_Reset(void)
{
    data_0057e1d8 = 0;
    return;
}

unsigned int Arg_PeekToken(void)
{
    int i = data_0057e1d8;
    if (i >= coalesced_argument_count) {
        return 0U;
    }
    return (unsigned int)(token_texts + data_0057e1d8);
}

TokenText *Arg_UsedToken(void)
{
    int c;
    if ((c = data_0057e1d8) < coalesced_argument_count)
        data_0057e1d8++;
    return (TokenText *)Arg_PeekToken();
}

int Arg_IsEmpty(void)
{
    unsigned short *value = (unsigned short *)Arg_PeekToken();
    return value == NULL || *value == 0;
}

int Arg_GetToken(void)

{
    int result = Arg_PeekToken();
    if (result != 0) {
        data_0057e1d8 = data_0057e1d8 + 1;
    }
    return result;
}

TokenText *Arg_UndoToken(void)
{
    if (data_0057e1d8 > 0) {
        --data_0057e1d8;
        return (TokenText *)Arg_PeekToken();
    }
    return NULL;
}

char *Arg_GetTokenName(TokenText *token)
{
    char *result;
    int matchesKind;
    if (token->kind == 2)
        return token->text;
    if (token->kind == 3)
        result = "option";
    else if (token->kind == 5)
        result = "comma";
    else {
        matchesKind = (data_0054aa78 == 1) && (token->kind == 4);
        if (matchesKind)
            result = "colon or equals";
        else {
            matchesKind = (data_0054aa78 != 1) && (token->kind == 4);
            if (matchesKind)
                result = "equals";
            else if (token->kind == 1)
                result = "end of argument";
            else if (token->kind == 0)
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
    if (arg->kind == 2 || arg->kind == 3)
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
        list->items = ToolHelpers_ResizeBuffer("argument list", list->items, (list->size + 1) * 4);
        for (; i <= list->size; i++)
            list->items[i] = NULL;
    }
    list->count++;
}

void Arg_GrowArg(struct PtrList *list, char *text)
{
    char *value = text;
    char **slot = &list->items[list->count];
    if (!*slot) {
        *slot = ClientGlue_DuplicateString(value);
    } else {
        char *string = value;
        *slot = ToolHelpers_ResizeBuffer("command line", *slot, strlen(*slot) + strlen(string) + 1);
        strcpy(*slot + strlen(*slot), string);
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
    if (kind == 0)
        Arg_FinishToolArgs(list);
    else if (kind == 1) {
        if (list->items && list->items[list->count])
            Arg_GrowArgs(list);
    } else if (kind == 2)
        Arg_GrowArg(list, text);
    else if (kind == 3)
        Arg_GrowArg(list, "-");
    else if (kind == 4)
        Arg_GrowArg(list, "=");
    else if (kind == 5)
        Arg_GrowArg(list, ",");
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
