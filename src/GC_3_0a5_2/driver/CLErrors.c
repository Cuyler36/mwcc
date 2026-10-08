/* GC 3.0 diagnostic names and static buffers from CLErrors.c STABS. */
#pragma exceptions off
#include "compiler/common.h"
#include "compiler/win32.h"
#include "driver/CLIO.h"
#include "driver/StringUtils.h"
#include "msl/string.h"
#include <string.h>
#include <stdio.h>

extern void __stdcall xfree(void *ptr);
extern __declspec(noreturn) void exit(int status);
extern FILE *data_00711b88;
extern unsigned char data_007101d0[];
extern void fn_00423010(void *state);
extern void fn_00423080(void);
static char stmsg[256];
static char stbuf[256];

#define va_start(ap, parm) do { \
    char *argumentAddress = (char *)&parm; \
    char *argumentEnd = (char *)(&parm + 1); \
    ap = argumentAddress + (argumentEnd - argumentAddress + 3) / 4 * 4; \
} while (0)

static char *CLGetErrorString(short errid, char *buffer)
{
    CLIO_GetResourceString((unsigned char *)buffer, 12000, errid);
    CLIO_ConvertPascalToCString(buffer);
    strcat(buffer, "\n");
    return buffer;
}

static void CLMessageReporter(int flags, short errid, va_list va)
{
    char *txt;
    UInt8 diagnosticKind;

    CLGetErrorString(errid, stmsg);
    txt = mvprintf(stbuf, 0x100, stmsg, va);
    if (flags == 2) {
        diagnosticKind = 3;
    } else if (flags == 1) {
        diagnosticKind = 2;
    } else {
        diagnosticKind = 5;
    }
    CLIO_ReportDiagnostic(NULL, NULL, 0, diagnosticKind, "%", txt);
    if (txt != stbuf) {
        xfree(txt);
    }
}

void CLReportError(short errid, ...)
{
    va_list va;
    va_start(va, errid);
    CLMessageReporter(2, errid, va);
}

void CLReportWarning(short errid, ...)
{
    va_list va;
    va_start(va, errid);
    CLMessageReporter(1, errid, va);
}

void CLReport(short errid, ...)
{
    va_list va;
    va_start(va, errid);
    CLMessageReporter(0, errid, va);
}

void CLReportOSError(short errid, UInt32 err, ...)
{
    char mybuf[256];
    char myerr[256];
    char *txt;
    char *oserr;
    va_list args;

    va_start(args, err);
    txt = mvprintf(mybuf, sizeof(mybuf), CLGetErrorString(errid, myerr), args);
    oserr = OS_GetErrText(err);
    CLReportError(101, txt, oserr, err);
    if (txt != mybuf)
        xfree(txt);
}

void CLReportCError(short errid, SInt32 err_no, ...)
{
    char mybuf[256];
    char myerr[256];
    char *txt;
    va_list args;

    va_start(args, err_no);
    txt = mvprintf(mybuf, sizeof(mybuf), CLGetErrorString(errid, myerr), args);
    {
        int serr = get_strerror(err_no);
        CLReportError(102, txt, serr, err_no);
    }
    if (txt != mybuf)
        xfree(txt);
}

void CLInternalError(const char *file, int line, const char *format, ...)
{
    char mybuf[256];
    char *txt;
    va_list args;
    va_start(args, format);
    txt = mvprintf(mybuf, sizeof(mybuf), format, args);
    CLIO_WriteFormattedText("INTERNAL ERROR [%s:%d]:\n%s\n", file, line, txt);
    if (data_00711b88)
        fprintf(data_00711b88, "INTERNAL ERROR [%s:%d]:\n%s\n", file, line, txt);
    fn_00423010(data_007101d0);
    fn_00423080();
    if (txt != mybuf)
        xfree(txt);
}

#pragma exceptions reset
void CLFatalError(char *format, ...)
{
    char *txt;
    char mybuf[256];
    va_list args;

    va_start(args, format);
    txt = mvprintf(mybuf, sizeof(mybuf), format, args);
    CLIO_WriteFormattedText("FATAL ERROR:\n%s\n", txt);
    if (data_00711b88)
        fprintf(data_00711b88, "FATAL ERROR:\n%s\n", txt);
    fn_00423010(data_007101d0);
    fn_00423080();
    if (txt != mybuf) {
        xfree(txt);
    }
    exit(-123);
}
