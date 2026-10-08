#include "compiler/common.h"
/* Private GC3 diagnostic layout: each original OSSpec occupies 516 bytes. */
#ifndef DRIVER_CLIO_H
#define DRIVER_CLIO_H

#include "driver/OSAssert.h"
#include <setjmp.h>
#include "compiler/common.h"
#include "driver/MsDos.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _FILE;

struct StringListHeader {
    unsigned char countHigh; /* 0x00: CLIO_GetResourceString reads the high byte of the big-endian STR# string count */
    unsigned char countLow;  /* 0x01: CLIO_GetResourceString reads the low byte of the STR# string count */
};

struct ByteBuffer {
    char *data;
    int size;
    int capacity;
    short column;
    unsigned char callerOwned;
    char *prefix;
};
struct DiagnosticDetails {
    unsigned char precedingData[516];
    char text[516];
    int formatValue;
    int diagnosticValue;
};
#pragma pack(push, 1)
struct DiagnosticSourcePosition {
    OSSpec primaryFile;
    unsigned char gc3PrimarySpecTail[192];
    OSSpec
        file; /* 0x204: styledMessage_Terse passes the diagnostic file to CLProj_MakeRelativePath; CLStyledMessageDispatch copies it from record. */
    unsigned char gc3FileSpecTail[192];
    char *sourceLine;
    SInt32 line; /* 0x40c: styledMessage_Terse prints the source line number after the file path. */
    int column;
    short length;
    char reserved662[2];
    int selectionOffset; /* 0x418: report_message copies the diagnostic selection position; styledMessage_Parseable emits it after column and length. */
    short
        selectionLength; /* 0x41c: report_message copies and clamps the selection extent; styledMessage_Parseable emits it after selectionOffset. */
    char reserved670[2];
};
#pragma pack(pop)

extern char data_005880e0[];
extern void __stdcall GetIndString(unsigned char *output, short resourceID, short stringIndex);
#define CLIO_GetResourceString GetIndString
extern char *__stdcall p2cstr(char *p);
#define CLIO_ConvertPascalToCString p2cstr
extern char *__stdcall c2pstr(char *string);
#define CLIO_ConvertToPascalString c2pstr
extern Boolean write_text_buffer(struct _FILE *fp, StorageHandle *bufp, SInt32 len);
extern unsigned char CLIO_WriteStorageToStdout(StorageHandle *first, SInt32 second, unsigned int reset);
extern Boolean CLIO_WriteTextFile(OSSpec *fileRef, StorageHandle *text, SInt32 textLength, SInt32 fileType,
                                  SInt32 creator);
extern unsigned char WriteBinaryHandleToFile(OSSpec *a0, unsigned int a1, unsigned int a2, MemBuffer *a3);
extern unsigned char CLIO_AppendStorageToFile(OSSpec *a0, struct StorageHandle *a1, SInt32 a2, SInt32 a3, SInt32 a4);
extern void InitWorking(void);
extern void ProgressFunction(int);
extern void TermWorking(void);
extern unsigned char CheckForUserBreak(void);
extern void StartLine(struct ByteBuffer *node);
extern void WrapText(struct ByteBuffer *p);
extern void append_prefix_separator(struct ByteBuffer *state);
extern char *IO_VFormatText(char *output, int remaining, char *prefix, char *format, char **args);
extern char *IO_FormatText(char *output, int size, char *prefix, char *format, ...);
extern void CLPrintDispatch(DiagnosticSourcePosition *info, short messageType, const char *textAddress);
extern void append_byte(struct ByteBuffer *buffer, char value);
extern void append_text(struct ByteBuffer *buffer, char *text);
extern char DAT_00541b3e;
extern SInt8 no_wrap;
extern char data_00541b35;
extern SInt16 data_00541b3a;
extern int data_0054b988;
extern const char *data_0054b9c0[];
extern char data_0054b9dc;
extern char data_00587325;
extern void __stdcall getindstring(char *a0, int a1, int a2);
extern int __stdcall catchinterrupt(unsigned int value);
extern void SetupConsoleInfo(void);
extern void Crash(void);
extern void SetupDebuggingTraps(void);
extern char IO_Initialize(void);
extern unsigned char IO_Terminate(void);
extern unsigned char IO_HelpTerminate(void);
extern short consoleBufferHeight;
extern char DAT_0057eb68;
extern char data_0057eb69;
extern short CLStyledMessageDispatch(Plugin *type, DiagnosticSourcePosition *record, int message, short severity,
                                   char *argument, ...);
extern char data_00541b2c;
extern char data_00541b2d;
extern short diagnostic_count_limit;
extern short diagnostic_limit;
extern short data_00541b32;
extern char data_00541b36;
extern char *Arrows(DiagnosticSourcePosition *sourcePosition);
extern void GetFileInfo(OSSpec *recordAddress);
extern unsigned char IsLikelyAnImporter(Plugin *type);
extern char *GuessTool(Plugin *tool);
extern unsigned char *GuessDoing(Plugin *value);
extern void styledMessage_Terse(Plugin *type, struct DiagnosticSourcePosition *obj, int messageCode, SInt16 kind,
                                     char *formatFlags, char **formatOptions);
extern void styledMessage_IDE(Plugin *unused, struct DiagnosticDetails *details, int unused2,
                                          short diagnostic, char *formatArg, char **formatArgs);
extern void styledMessage_Parseable(Plugin *kind, DiagnosticSourcePosition *record, int unused, short level,
                                            char *argument1, char **argument2);
extern void CLPrintType(short kind, char *format, ...);
extern void CLPrintErr(const char *format, ...);
extern void styledMessage_Default(Plugin *source, DiagnosticSourcePosition *diagnostic, int unused, short kind,
                                      char *format, char **arguments);
extern void styledMessage_MPW(Plugin *object, DiagnosticSourcePosition *dump, SInt32 code, SInt16 level,
                             char *messageArg1, char **messageArg2);
extern void CLPrint(char *fmt, ...);
extern void FixupMessageRef(DiagnosticSourcePosition *info);
extern char DAT_0057edfd[];
extern char *diagnostic_level_names[];
extern unsigned char plugin_type_strings[];
extern unsigned char compiling_plugin_type[];
extern unsigned char data_0054bab8[];
extern unsigned char data_0054bac0[];
extern UInt8 data_0057eb70;
extern UInt8 data_0057eb71;
extern char specs_equal;
extern char data_0057edfb;
extern char data_0057edfc;
extern char *program_name;
extern int __stdcall ustrcmp(char *left, char *right);

extern OSSpec cachedRecordSpec;
extern OSSpec data_0057ecb6;

#ifdef __cplusplus
}
#endif

#endif

#include "compiler/objects.h"
#include "compiler/scopes.h"
#include "compiler/types.h"
#include "compiler/win32.h"
#include "compiler/CExpr2.h"
#include "compiler/CPrep.h"
#include "driver/CLAccessPaths.h"
#include "driver/CLBrowser.h"
#include "driver/CLDependencies.h"
#include "driver/CLDropinCallbacks_V10.h"
#include "driver/CLErrors.h"
#include "driver/CLFileOps.h"
#include "driver/CLFiles.h"
#include "driver/CLPlugins.h"
#include "driver/CLPrefs.h"
#include "driver/CLProj.h"
#include "driver/CLSegs.h"
#include "driver/CLTarg.h"
#include "driver/CWParserPluginsPrivate.h"
#include "driver/CWPluginsPrivate.h"
#include "driver/Files.h"
#include "driver/MacFileTypes.h"
extern void *__stdcall xmalloc(const char *, unsigned int);
extern void *__stdcall xrealloc(const char *, void *, unsigned int);
extern char *__stdcall xstrdup(const char *);
extern void __stdcall xfree(void *);
#include "driver/Memory.h"
#include "driver/MsDos.h"
#include "driver/ResourceStrings.h"
#include "driver/Resources.h"
#include "driver/StringUtils.h"
#include "driver/TargetOptimizer-ppc-eabi.h"
#include "msl/signal.h"
#define _GetThreadLocalData GC3_UnusedThreadLocalPrototype
#include "msl/startup_win32.h"
#undef _GetThreadLocalData
extern ThreadLocalData *_GetThreadLocalData(unsigned int);
extern CFileRec *consoleFiles_00705ac8[3];
extern struct _FILE *outputFile_00711b88;
extern char *handleBorder_0066b084;
extern char *fileBorder_0066b088;
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

static int ioLineNum;
static unsigned char printedAnything;
static char arrowBuf[256];
static unsigned char newErr, newSrc, srcIsErr;
static unsigned char validErr, validSrc;
static unsigned char ioInHelp, ioPiping;
static char *msgnames[6] = {"", "Note", "Warning", "Error", "Alert", "Status"};
#define data_0054b988 ioLineNum
#define data_0054b9dc printedAnything
#define DAT_0057edfd arrowBuf
#define data_0057edfc newErr
#define data_0057edfb newSrc
#define specs_equal srcIsErr
#define data_0057eb71 validErr
#define data_0057eb70 validSrc
#define data_0057eb69 ioInHelp
#define DAT_0057eb68 ioPiping
#define diagnostic_level_names msgnames
static char *msgnames_gcc[6] = {"", " note", " warning", "", " alert", " status"};

/* GC3 caches complete 516-byte Win32 file specifications. */
struct GC3StoredSpec { OSSpec header; unsigned char tail[192]; };
static struct GC3StoredSpec srcSpec;
static struct GC3StoredSpec errSpec;
#define cachedRecordSpec srcSpec.header
#define data_0057ecb6 errSpec.header

/* "\r\n" */

#if VERSION != VERSION_GC_3_0A5_2
void CLIO_ReportAssertionFailure(char *message, char *file, unsigned int line)
{
    fprintf(stderr, "Assertion (%s) failed in \"%s\" on line %d\n", message, file, line);
    abort();
}
#endif

int __stdcall catchinterrupt(unsigned int value)
{
    if (value <= 1) {
        if (data_00587325) {
            CLPrintErr("\nUser break, terminating!\n");
            exit(2);
        }
        CLPrintErr("\nUser break, cancelling...\n");
        data_00587325++;
        return 1;
    }
    return 0;
}

void SetupConsoleInfo(void)
{
    HANDLE consoleOutput;
    BOOL gotBufferInfo;
    PHANDLER_ROUTINE handler;
    _CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

    consoleOutput = GetStdHandle((DWORD)-11);
    handler = (PHANDLER_ROUTINE)catchinterrupt;
    SetConsoleCtrlHandler(handler, 1);
    DAT_0057eb68 = 0;
    gotBufferInfo = GetConsoleScreenBufferInfo(consoleOutput, &bufferInfo);
    if (!gotBufferInfo) {
        consoleBufferHeight = 0;
        data_00541b3a = 80;
    } else {
        consoleBufferHeight = bufferInfo.dwSize.Y;
        data_00541b3a = (unsigned short)bufferInfo.dwSize.X;
        if (data_00541b3a > 256) {
            data_00541b3a = 256;
        }
    }
    consoleFiles_00705ac8[0]->readonly = 0;
    consoleFiles_00705ac8[1]->readonly = 0;
    consoleFiles_00705ac8[2]->readonly = 0;
}

void Crash(void)

{
    *(unsigned char *)NULL = 0;
    return;
}

void SetupDebuggingTraps(void)
{
    unsigned int value = (unsigned int)Crash;
    exchange_indexed_value(1, value);
}

char IO_Initialize(void)
{
    DAT_0057eb68 = 0;
    data_0057eb69 = 0;
    data_0054b988 = 0;
    SetupConsoleInfo();
    if (DAT_0057eb68 != 0) {
        setvbuf(stdout, NULL, 2, 4096U);
        setvbuf(stderr, NULL, 2, 4096U);
    } else {
        setvbuf(stdout, NULL, 1, 4096U);
        setvbuf(stderr, NULL, 1, 4096U);
    }
    InitWorking();
    return 1;
}

unsigned char IO_Terminate(void)
{
    if (data_0057eb69) {
        IO_HelpTerminate();
    }
    TermWorking();
    return 1;
}

unsigned char IO_HelpTerminate(void)
{
    data_0057eb69 = 0U;
    return 1U;
}

static Boolean emit_text(FILE *file, char *cursor, unsigned int size)
{
    char *end;
    char *lineEnd;
    Boolean atEol;
    if (file != stdout && file != stderr)
        setvbuf(file, NULL, 2, 4096);
    end = cursor + size;
    while (cursor < end) {
        lineEnd = cursor;
        while (lineEnd < end && *lineEnd != '\n' && *lineEnd != '\r')
            lineEnd++;
        atEol = *lineEnd == '\n' || *lineEnd == '\r';
        if (lineEnd - cursor != 0 && fwrite(cursor, lineEnd - cursor, 1, file) != 1) {
            CLErrors_ReportFormattedOSError(10, _GetThreadLocalData(1)->secondaryValue);
            return 0;
        }
        if (CheckForUserBreak())
            return 1;
        if (atEol) {
            if (fwrite("\r\n", 2, 1, file) != 1) {
                CLErrors_ReportFormattedOSError(10, _GetThreadLocalData(1)->secondaryValue);
                return 0;
            }
            if (lineEnd < end && *lineEnd++ == '\r' && *lineEnd == '\n')
                lineEnd++;
        }
        cursor = lineEnd;
    }
    fflush(file);
    if (file != stdout && file != stderr)
        setvbuf(file, NULL, 0, 4096);
    return 1;
}

Boolean SendHandleToFile(FILE *file, MemBuffer *handle)
{
    char *data = (char *)MsDos_GetValidMemBufferPtr(handle);
    DWORD size;
    Boolean ok;
    if (!data)
        return 0;
    OS_GetHandleSize(handle, &size);
    if (size && data[size - 1] == 0)
        size--;
    if (size)
        ok = emit_text(file, data, size);
    else
        ok = 1;
    fn_004129c0(handle);
    return ok;
}

unsigned char ShowHandle(MemBuffer *handle, unsigned char decorated)
{
    Boolean ok;
    if (decorated)
        fprintf(stdout, handleBorder_0066b084);
    if (DAT_00541b3e) {
        if (outputFile_00711b88)
            SendHandleToFile(outputFile_00711b88, handle);
        ok = 1;
    } else
        ok = SendHandleToFile(stdout, handle);
    if (decorated)
        fprintf(stdout, handleBorder_0066b084);
    fflush(stdout);
    return ok;
}

unsigned char ShowFile(OSSpec *spec, unsigned char decorated)
{
    char buffer[1024];
    SInt32 size, file;
    DWORD error;
    Boolean ok = 1;
    if (decorated)
        fprintf(stdout, fileBorder_0066b088);
    error = OS_Open(spec, 0, &file);
    if (error) {
        CLErrors_ReportOSError(95, error, OS_SpecToString(spec, data_005880e0, 260));
        ok = 0;
    } else {
        do {
            size = 1024;
            error = OS_Read(file, buffer, &size);
            if (!size)
                break;
            if (error)
                ok = 0;
            else
                ok = emit_text(stdout, buffer, size);
        } while (ok);
        OS_Close(file);
    }
    if (decorated)
        fprintf(stdout, fileBorder_0066b088);
    fflush(stdout);
    return ok;
}

Boolean WriteHandleToFile(OSSpec *fileRef, MemBuffer *text, SInt32 fileType, SInt32 creator)
{
    char path[256];
    FILE *file;
    OS_SpecToString(fileRef, path, 260);
    file = fopen(path, "w+b");
    if (file == NULL) {
        CLErrors_ReportFormattedOSError(8, _GetThreadLocalData(1)->secondaryValue, path);
        return 0;
    }
    SendHandleToFile(file, text);
    fclose(file);
    fn_00421d30(fileRef, fileType, creator);
    return 1;
}

unsigned char WriteBinaryHandleToFile(OSSpec *fileSpec, unsigned int fileType, unsigned int creator, MemBuffer *buffer)
{
    union { OperationRecord typed; unsigned char storage[528]; } recovery;
    unsigned int result;
    if ((result = TargetOptimizer_ppc_eabi_InitOperationRecord(fileSpec, buffer, 1U, &recovery.typed)) != 0U ||
        (result = TargetOptimizer_ppc_eabi_UnloadOperationRecord(&recovery.typed)) != 0U ||
        (result = fn_00421d30(fileSpec, fileType, creator)) != 0U) {
        char *message = OS_SpecToString(fileSpec, data_005880e0, 260U);
        CLErrors_ReportOSError(8U, result, message);
        return 0;
    }
    return 1;
}

unsigned char AppendHandleToFile(OSSpec *fileSpec, MemBuffer *storage, SInt32 fileType, SInt32 fileCreator)
{
    char path[256];
    FILE *file;
    OS_SpecToString(fileSpec, path, 260);
    file = fopen(path, "a+b");
    if (file == NULL) {
        CLErrors_ReportFormattedOSError(8, _GetThreadLocalData(1)->secondaryValue, path);
        return 0;
    }
    SendHandleToFile(file, storage);
    fclose(file);
    fn_00421d30(fileSpec, fileType, fileCreator);
    return 1;
}

void InitWorking(void)
{
    return;
}

void TermWorking(void)
{
    return;
}

unsigned char CheckForUserBreak(void)
{
    ProgressFunction(4);
    return data_00587325;
}

void ProgressFunction(int)
{
    return;
}

void WrapText(struct ByteBuffer *p)
{
    char buf[256];
    SInt32 n = 0;

    if (no_wrap || p->prefix == NULL || strlen(p->prefix) > data_00541b3a / 2)
        return;

    while (n < data_00541b3a - 1 && p->column > strlen(p->prefix)) {
        char c = p->data[p->size - 1];
        if (c == ' ' || c == '/' || c == '-')
            break;
        buf[n] = c;
        n++;
        p->size--;
        p->column--;
    }

    if (p->column <= strlen(p->prefix)) {
        while (p->column < data_00541b3a - 1 && n > 0) {
            n--;
            append_byte(p, buf[n]);
        }
    }

    append_prefix_separator(p);

    while (n > 0 && p->capacity > 0) {
        n--;
        append_byte(p, buf[n]);
    }
}

/* Growable byte buffer with a count of appended bytes. */

/* 0x541b3a, word width */

char *IO_VFormatText(char *output, int remaining, char *prefix, char *format, char **args)
{
    char *text;
    struct ByteBuffer state;
    int column;

    state.data = output;
    state.size = 0;
    state.capacity = remaining;
    state.column = 0;
    state.callerOwned = 1;
    state.prefix = prefix;
    StartLine(&state);

    while (*format != '\0' && state.capacity > 0) {
        if (*format == '%') {
            args++;
            text = *(char **)((char *)args - 4);
            while (*text != '\0' && state.capacity > 0) {
                if (*text == '\r' || *text == '\n') {
                    append_prefix_separator(&state);
                    text++;
                } else if (*text == '\t') {
                    if (state.capacity > 0) {
                        do {
                            append_byte(&state, ' ');
                        } while ((state.column & 7) != 0);
                    }
                    text++;
                } else {
                    append_byte(&state, *text++);
                    if (no_wrap == 0 && state.prefix != NULL && state.column >= data_00541b3a - 1)
                        WrapText(&state);
                }
            }
            format++;
        } else if (*format == '\r' || *format == '\n') {
            format++;
            append_prefix_separator(&state);
        } else {
            append_byte(&state, *format++);
            if (no_wrap == 0 && state.column >= data_00541b3a - 1)
                WrapText(&state);
        }
    }

    if (state.prefix != NULL) {
        if ((column = state.column) == strlen((const char *)state.prefix)) {
            state.size -= column;
            state.column = 0;
        }
    }
    append_byte(&state, 0);
    return (char *)state.data;
}

void append_prefix_separator(struct ByteBuffer *state)
{
    if (state->prefix)
        append_byte(state, '\n');
    else
        append_byte(state, ' ');
    StartLine(state);
}

void StartLine(struct ByteBuffer *node)
{
    node->column = 0;
    if ((DAT_00541b3e == '\0') && (node->prefix != NULL)) {
        append_text(node, node->prefix);
    }
}

void append_text(struct ByteBuffer *buffer, char *text)
{
    int length;
    length = strlen(text);
    if (buffer->size + length >= buffer->capacity) {
        buffer->capacity = buffer->capacity * 2 + length;
        if (buffer->callerOwned != 0) {
            char *oldData = buffer->data;
            buffer->data = xmalloc("message buffer", buffer->capacity);
            memcpy(buffer->data, oldData, buffer->size);
        } else {
            buffer->data =
                xrealloc("message buffer", (buffer->callerOwned != 0) ? NULL : buffer->data, buffer->capacity);
        }
        buffer->callerOwned = 0;
    }
    memcpy(buffer->data + buffer->size, text, length);
    buffer->size += length;
    buffer->column += length;
}

void append_byte(struct ByteBuffer *buffer, char value)
{
    char *old_data;
    if (buffer->size >= buffer->capacity) {
        buffer->capacity <<= 1;
        if (buffer->callerOwned) {
            old_data = buffer->data;
            buffer->data = xmalloc("message buffer", buffer->capacity);
            memcpy(buffer->data, old_data, buffer->size);
        } else {
            buffer->data = xrealloc("message buffer", buffer->data, buffer->capacity);
        }
        buffer->callerOwned = 0;
    }
    buffer->data[buffer->size++] = (unsigned char)value;
    buffer->column++;
}

char *IO_FormatText(char *output, int size, char *prefix, char *format, ...)
{
    char **arguments = &format + (((char *)(&format + 1) - (char *)&format + 3) / 4);
    return IO_VFormatText(output, size, prefix, format, arguments);
}

extern unsigned char ideOutputEnabled_00710210;
extern short flushMode_00710244;
extern char ideContext_007101d0[];
extern void (*idePrint_00669c64)(void *, const char *, int, int, int, int, int, const char *, int, int, int);

void CLPrintDispatch(DiagnosticSourcePosition *info, short messageType, const char *textAddress)
{
    FILE *output;
    int type;
    const char *cursor;
    const char *lineEnd;
    char mode;
    if (DAT_00541b3e && ideOutputEnabled_00710210) {
        if (outputFile_00711b88)
            fprintf(outputFile_00711b88, "SendMessage: %d, %s\n", messageType, textAddress);
        type = messageType == 3 ? 2 : messageType == 2 ? 1 : 0;
        if (info && OS_Status(&info->file) == 0)
            idePrint_00669c64(ideContext_007101d0,
                OS_SpecToString(&info->file, data_005880e0, 260), info->line,
                (unsigned short)info->column, (unsigned short)info->length,
                info->selectionOffset, info->selectionLength, textAddress, 0, type, 0);
        else
            idePrint_00669c64(ideContext_007101d0, "", 0, 0, 0, 0, 0, textAddress, 0, type, 0);
        return;
    }
    if ((mode = data_00541b35) == 1 || mode == 2 || (type = messageType) == 1 || type == 5)
        output = stdout;
    else if (type == 2 || type == 3 || type == 4)
        output = stderr;
    else
        OS_ASSERT_AT("0", "CLIO.c", 958);
    if (data_0054b9dc == 0 && DAT_0057eb68 == 0) {
        data_0054b9dc = 1;
        data_0054b988 = 0;
    }
    cursor = textAddress;
    while (*cursor != 0) {
        lineEnd = cursor;
        while (*lineEnd != 0 && *lineEnd != '\n' && *lineEnd != '\r')
            ++lineEnd;
        if (lineEnd - cursor != 0 && fwrite(cursor, lineEnd - cursor, 1, output) != 1)
            data_00587325 = 1;
        if (*lineEnd != 0) {
            data_0054b988++;
            fwrite("\r\n", 2, 1, output);
            if (*lineEnd == '\r')
                lineEnd++;
            if (*lineEnd == '\n')
                lineEnd++;
            if (*lineEnd && !lineEnd[1] && (*lineEnd == '\n' || *lineEnd == '\r'))
                lineEnd++;
        }
        cursor = lineEnd;
    }
    if (output == stdout && flushMode_00710244 > 1)
        fflush(output);
}

void GetFileInfo(OSSpec *recordAddress)
{
    if (recordAddress == NULL)
        return;
    specs_equal = OS_EqualSpec(recordAddress, (OSSpec *)((char *)recordAddress + 516));
    if (data_0057eb70 == 0 || OS_EqualSpec(recordAddress, &cachedRecordSpec) == 0) {
        const struct GC3StoredSpec *records = (const struct GC3StoredSpec *)recordAddress;
        struct GC3StoredSpec *cachedRecord = &srcSpec;
        data_0057edfb = 1;
        *cachedRecord = *records;
        data_0057eb70 = 1;
    } else {
        data_0057edfb = 0;
    }
    if (data_0057eb71 == 0 || OS_EqualSpec((OSSpec *)((char *)recordAddress + 516), &data_0057ecb6) == 0) {
        const struct GC3StoredSpec *records = (const struct GC3StoredSpec *)recordAddress;
        struct GC3StoredSpec *cachedRecord = &errSpec;
        data_0057edfc = 1;
        *cachedRecord = records[1];
        data_0057eb71 = 1;
    } else {
        data_0057edfc = 0;
    }
}

void styledMessage_Terse(Plugin *type, DiagnosticSourcePosition *obj, int messageCode, SInt16 kind,
                              char *formatFlags, char **formatOptions)
{
    char formattedBuffer[256];
    char sourceBuffer[256];
    char messageBuffer[256];
    char *formatted;
    char *message;
    char *sourceMessage;
    char *line;
    char *end;

    if (obj != NULL) {
        if (*msgnames_gcc[kind])
            message = mprintf(messageBuffer, sizeof(messageBuffer), "%s:%d:%s: ",
                              CLProj_MakeRelativePath(&obj->file, NULL, data_005880e0, 260),
                              obj->line, msgnames_gcc[kind]);
        else
            message = mprintf(messageBuffer, sizeof(messageBuffer), "%s:%d: ",
                              CLProj_MakeRelativePath(&obj->file, NULL, data_005880e0, 260), obj->line);
    } else if (kind != 5) {
        if (*msgnames_gcc[kind])
            message = mprintf(messageBuffer, sizeof(messageBuffer), "%s:%s: ", program_name, msgnames_gcc[kind]);
        else
            message = mprintf(messageBuffer, sizeof(messageBuffer), "%s: ", program_name);
    } else {
        messageBuffer[0] = 0;
        message = messageBuffer;
    }
    formatted = IO_VFormatText(formattedBuffer, sizeof(formattedBuffer), message, formatFlags, formatOptions);
    if ((strstr(formatted, "preprocessor #warning") || strstr(formatted, " preprocessor #error")) &&
        *obj->sourceLine)
        sourceMessage = IO_FormatText(sourceBuffer, sizeof(sourceBuffer), message, "%", obj->sourceLine);
    else
        sourceMessage = NULL;
    if (message != messageBuffer)
        xfree(message);
    line = formatted;
    while (*line) {
        end = line;
        while (*end && *end != '\n')
            end++;
        CLPrintType(kind, "%.*s\n", end - line, line);
        if (sourceMessage) {
            CLPrintType(kind, "%s\n", sourceMessage);
            if (sourceMessage != sourceBuffer)
                xfree(sourceMessage);
            sourceMessage = NULL;
        }
        if (*end)
            end++;
        line = end;
    }
    if (formatted != formattedBuffer)
        xfree(formatted);
}

void CLPrint(char *fmt, ...)
{
    char buf[256];
    char *text;
    va_list args;

    args = (va_list)&fmt + (((va_list)(&fmt + 1) - (va_list)&fmt + 3) / 4 * 4);
    text = mvprintf(buf, sizeof(buf), fmt, args);
    CLPrintDispatch(0, 1, text);
    if (text != buf)
        xfree(text);
}

void CLPrintErr(const char *format, ...)
{
    char buffer[256];
    va_list args;
    char *text;

    args = (va_list)&format + (((va_list)(&format + 1) - (va_list)&format) + 3) / 4 * 4;
    text = mvprintf(buffer, sizeof(buffer), format, args);
    CLPrintDispatch(0, 3, text);
    if (text != buffer)
        xfree(text);
}

void FixupMessageRef(DiagnosticSourcePosition *info)
{
    char *start, *end;
    SInt32 len, i;
    if (info->sourceLine != NULL && *info->sourceLine != '\0') {
        start = info->sourceLine + info->column;
        end = info->sourceLine + info->column + info->length - 1;
        if (end < start)
            end = start;
        while (start > info->sourceLine && start[-1] != '\r')
            start--;
        while (*end != '\0' && *end != '\r' && *end != '\n')
            end++;
        len = end - start;
        info->sourceLine = xmalloc("text buffer", len + 1);
        strncpy(info->sourceLine, start, len);
        info->sourceLine[len] = '\0';
        for (i = 0; i < len; i++) {
            if (info->sourceLine[i] < ' ' || info->sourceLine[i] >= 0x7f)
                info->sourceLine[i] = ' ';
        }
    } else {
        info->sourceLine = NULL;
    }
}

void styledMessage_MPW(Plugin *object, DiagnosticSourcePosition *dump, SInt32 diagnosticCode, SInt16 level,
                      char *messageArg1, char **messageArg2)
{
    char buffer[256];
    char *message;

    message = IO_VFormatText(buffer, sizeof(buffer), "#   ", messageArg1, messageArg2);
    if (level != 5) {
        CLPrintType(level, "### %s %s %s:\n", program_name, GuessTool(object),
                               diagnostic_level_names[level]);
    }
    if (dump != NULL) {
        CLPrintType(level, "#\t%s\n", dump->sourceLine);
        CLPrintType(level, "#\t%s\n", Arrows(dump));
    }
    CLPrintDispatch(0, level, message);
    if (dump != NULL) {
        CLPrintType(level, "#----------------------------------------------------------\n");
        CLPrintType(level, "    File \"%s\"; Line %d\n", OS_SpecToString(&dump->file, data_005880e0, 0x104),
                               dump->line);
        GetFileInfo(&dump->primaryFile);
        if (specs_equal == 0) {
            CLPrintType(level, "#\twhile %s \"%s\"\n", GuessDoing(object),
                                   OS_SpecToString(&dump->primaryFile, data_005880e0, 0x104));
        }
        CLPrintType(level, "#----------------------------------------------------------\n");
    }
    if (message != buffer) {
        xfree(message);
    }
}

static inline void emitDiagnosticText(short kind, const char *text)
{
    CLPrintDispatch(0, kind, text);
}
static inline void formatDiagnosticDetail(char *buffer, const char *format, const char *label, char *location)
{
    sprintf(buffer, format, label, location);
}

void styledMessage_Default(Plugin *source, DiagnosticSourcePosition *diagnostic, int unused, short kind,
                               char *format, char **arguments)
{
    char *message;
    char *cursor;
    short limit;
    char detail[324];
    char buffer[256];

    message = IO_VFormatText(buffer, sizeof(buffer), "#   ", format, arguments);
    if (diagnostic != NULL) {
        CLPrintType(kind, "### %s %s:\n", program_name, GuessTool(source));
    } else if (kind != 5) {
        CLPrintType(kind, "### %s %s %s:\n", program_name, GuessTool(source),
                               diagnostic_level_names[kind]);
    }
    if (diagnostic != NULL) {
        GetFileInfo(&diagnostic->primaryFile);
        if (data_0057edfc != 0 || (data_0057edfb != 0 && specs_equal != 0)) {
            if (specs_equal != 0) {
                formatDiagnosticDetail(detail, "#%8s: %s\n", "File",
                                       CLProj_MakeRelativePath(&data_0057ecb6, NULL, data_005880e0, 260));
            } else {
                formatDiagnosticDetail(detail, "#%8s: %s\n", "In",
                                       CLProj_MakeRelativePath(&data_0057ecb6, NULL, data_005880e0, 260));
            }
            emitDiagnosticText(kind, detail);
        }
        if (data_0057edfb != 0 && specs_equal == 0) {
            formatDiagnosticDetail(detail, "# %7s: %s\n", "From",
                                   CLProj_MakeRelativePath(&cachedRecordSpec, NULL, data_005880e0, 260));
            emitDiagnosticText(kind, detail);
        }
        if (data_0057edfc != 0 || data_0057edfb != 0) {
            cursor = detail + 2;
            while (*cursor != 0 && *cursor != '\n') {
                *cursor = '-';
                ++cursor;
            }
            *cursor = 0;
            if (cursor - detail >= (limit = data_00541b3a) - 1) {
                (detail + limit)[-1] = 0;
            }
            strcat(detail, "\n");
            emitDiagnosticText(kind, detail);
        }
        CLPrintType(kind, "#%8d: %s\n", diagnostic->line, diagnostic->sourceLine);
        CLPrintType(kind, "#%8s: %s\n", diagnostic_level_names[kind],
                               Arrows(diagnostic));
    }
    emitDiagnosticText(kind, message);
    if (message != buffer) {
        xfree(message);
    }
}

char *Arrows(DiagnosticSourcePosition *sourcePosition)
{
    int column;
    int length;

    DAT_0057edfd[0] = 0;
    column = sourcePosition->column;
    column %= data_00541b3a;
    if ((column >= 0) && ((unsigned)column < 0x100)) {
        length = (int)sourcePosition->length;
        if (0x100 < (unsigned)(length + column)) {
            length = 0x100 - column;
        }
        if (length == 0) {
            length = 1;
        }
        memset(DAT_0057edfd, ' ', column);
        memset(DAT_0057edfd + column, '^', length);
        DAT_0057edfd[column + length] = 0;
    }
    return DAT_0057edfd;
}

static inline char *formatDiagnosticPath(const char *path)
{
    return CLProj_MakeRelativePath((OSSpec *)path, NULL, data_005880e0, 260);
}

unsigned char IsLikelyAnImporter(Plugin *type)
{
    struct GC3TargetView { unsigned char preceding[0x78]; SInt32 cpu; SInt32 os; } *entries;
    struct ObjFlagsData *flags;

    flags = CLPlugins_GetObjectFlags(type);
    if ((flags->compilerFlags & 0x80000000U) != 0U &&
        (((struct ObjFlagsData *)CLPlugins_GetObjectFlags(type))->compilerFlags & 0x40000000U) == 0)
        return 0;

    entries = (struct GC3TargetView *)default_target;

    if (type == CLPlugins_FindMatchingTargetPlugin(NULL, entries->cpu, entries->os, plugin_type, data_005871d0))
        return 0;
    return 1;
}

void styledMessage_IDE(Plugin *unused, struct DiagnosticDetails *details, int unused2, short diagnostic,
                                   char *formatArg, char **formatArgs)
{
    char *message;
    short savedDiagnostic;
    char *detailMessage;
    char buffer[256];

    savedDiagnostic = data_00541b3a;
    message = IO_VFormatText(buffer, sizeof(buffer), "           ", formatArg, formatArgs);
    data_00541b3a = savedDiagnostic;
    CLPrintType(diagnostic, "%8s : %s\n", diagnostic_level_names[diagnostic], message + 11);
    if (message != buffer) {
        xfree(message);
    }
    if (details != NULL) {
        detailMessage = IO_FormatText(buffer, sizeof(buffer), "\t", "%", details->formatValue);
        CLPrintType(diagnostic, "%s line %d%s\n",
                               CLProj_MakeRelativePath((OSSpec *)details->text, NULL, data_005880e0, 260),
                               details->diagnosticValue, detailMessage);
        if (detailMessage != buffer) {
            xfree(detailMessage);
        }
    }
}

void styledMessage_Parseable(Plugin *kind, DiagnosticSourcePosition *record, int unused, short level,
                                     char *argument1, char **argument2)
{
    char *message;
    char messageBuffer[256];

    CLPrintType(level, "%s|%s|%s\n", program_name, GuessTool(kind),
                           diagnostic_level_names[level]);
    if (record != NULL) {
        CLPrintType(level, "(%s|%d|%d|%d|%d|%d)\n", OS_SpecToString(&record->file, data_005880e0, 260),
                               record->line, record->column, record->length, record->selectionOffset,
                               record->selectionLength);
        CLPrintType(level, "=%s\n", record->sourceLine);
    }
    message = IO_VFormatText(messageBuffer, sizeof(messageBuffer), ">", argument1, argument2);
    CLPrintType(level, "%s\n", message);
    if (message != messageBuffer) {
        xfree(message);
    }
}

void CLPrintType(short kind, char *format, ...)
{
    char buffer[256];
    char *message;
    char **args;

    args = (&format + (((char *)(&format + 1) - (char *)&format + 3) / 4));
    message = mvprintf(buffer, sizeof(buffer), format, (va_list)args);
    CLPrintDispatch(0, kind, message);
    if (message != buffer)
        xfree(message);
}

char *GuessTool(Plugin *tool)
{
    PluginDesc *identification;

    if (tool != NULL) {
        identification = CLPlugins_GetPluginDesc(tool);
        switch (identification->type) {
            case 'cldr':
                return "Driver";
            case 'Pars':
                return "Usage";
            case 'Comp':
                if (identification->lang == 'c++ ' || identification->lang == 'pasc')
                    return "Compiler";
                if (identification->lang == 'Asm ' || identification->lang == 'MAsm')
                    return "Assembler";
                if (IsLikelyAnImporter(tool) != 0)
                    return "Importer";
                return "Compiler";
            case 'Link':
                return "Linker";
        }
    }
    return "Driver";
}

unsigned char *GuessDoing(Plugin *value)
{
    PluginDesc *record;
    if (value != NULL) {
        record = CLPlugins_GetPluginDesc(value);
        switch (record->type) {
            case 0x50617273:
                return plugin_type_strings;
            case 0x436F6D70:
                return compiling_plugin_type;
            case 0x4C696E6B:
                return data_0054bab8;
        }
    }
    return data_0054bac0;
}

/* Added Windows formatter; no source symbol name is available in the Mac map. */
static void fn_00419b30(Plugin *tool, DiagnosticSourcePosition *info, int code, short kind,
                        char *format, char **args)
{
    char buffer[256];
    char *message;
    int category;
    message = IO_VFormatText(buffer, sizeof(buffer), "", format, args);
    if (kind == 0) category = 0;
    else if (kind == 1) category = 0;
    else if (kind == 2) category = 1;
    else if (kind == 3) category = 2;
    else if (kind == 4) category = 3;
    else if (kind == 5) category = 0;
    else category = 3;
    if (info) {
        CLPrintType(kind, "[%s,%d,%d,%d,%s]: \n", "MWFE", category, code, info->line,
                    OS_SpecToString(&info->file, data_005880e0, 260));
        CLPrintType(kind, "\"%s\", line %d: %s: %s\n",
                    CLProj_MakeRelativePath(&info->file, NULL, data_005880e0, 260), info->line,
                    diagnostic_level_names[kind], message);
        CLPrintType(kind, "\t%s\n", info->sourceLine);
        CLPrintType(kind, "\t%s\n", Arrows(info));
    } else {
        CLPrintType(kind, "[%s,%d,%d,%d,%s]: \n", "MWFE", category, code, -1, "(command-line)");
        CLPrintType(kind, "\"%s\", line %d: %s: %s\n", "(command-line)", -1,
                    diagnostic_level_names[kind], message);
    }
    CLPrintType(kind, "\n");
    if (message != buffer)
        xfree(message);
}

short CLStyledMessageDispatch(Plugin *type, DiagnosticSourcePosition *record, int message, short severity, char *argument,
                            ...)
{
    unsigned int language;
    char **args;
    unsigned short limit;
    long diagnosticKind;
    union {
        DiagnosticSourcePosition record;
        DiagnosticSourcePosition dump;
        DiagnosticSourcePosition msg;
        struct DiagnosticDetails details;
        DiagnosticSourcePosition diagnostic;
    } diagnostic;
    if (severity == 2) {
        if (type != NULL) {
            language = CLPlugins_GetType(type);
        } else {
            language = 1668047986;
        }
        if (data_00541b2c != 0) {
            return 0;
        }
        if ((language == 1668047986 || language == 1348563571) && data_00541b36 != 0) {
            return 0;
        }
        if (data_00541b2d != 0) {
            severity = 3;
        }
    }
    diagnosticKind = severity;
    if (diagnosticKind == 3 && diagnosticReported != 0) {
        return 0;
    }
    if (diagnosticKind == 2 && data_00587326 != 0) {
        return 0;
    }
    if (record != NULL) {
        diagnostic.record = *record;
        FixupMessageRef(&diagnostic.record);
    }
    args = &argument + (((char *)(&argument + 1) - (char *)&argument + 3) / 4);
    {
        if ((language = data_00541b32) == 2) {
            styledMessage_MPW(type, record != NULL ? &diagnostic.dump : NULL, message, severity, argument, args);
        } else if (language == 1) {
            styledMessage_Terse(type, record != NULL ? &diagnostic.msg : NULL, message, severity, argument, args);
        } else if (language == 3) {
            styledMessage_IDE(type, record != NULL ? &diagnostic.details : NULL, message, severity,
                                          argument, args);
        } else if (language == 4) {
            styledMessage_Parseable(type, record != NULL ? &diagnostic.record : NULL, message, severity,
                                            argument, args);
        } else if (language == 5) {
            fn_00419b30(type, record != NULL ? &diagnostic.diagnostic : NULL, message, severity, argument, args);
        } else {
            styledMessage_Default(type, record != NULL ? &diagnostic.diagnostic : NULL, message, severity, argument,
                                      args);
        }
    }
    if (record != NULL && diagnostic.record.sourceLine != NULL) {
        xfree(diagnostic.record.sourceLine);
    }
    if (diagnosticKind == 3) {
        if ((limit = diagnostic_count_limit) != 0 && ++diagnostic_limit_count >= limit) {
            diagnosticReported = 1;
            if (data_00541b43 == 0) {
                CLErrors_ForwardMessage(70);
                data_00587325 = 1;
            } else {
                CLErrors_ForwardMessage(71);
            }
        }
    }
    if (diagnosticKind == 2) {
        if ((limit = diagnostic_limit) != 0 && ++diagnostic_count >= limit) {
            data_00587326 = 1;
            CLErrors_ForwardMessage(72);
        }
    }
    return severity;
}

