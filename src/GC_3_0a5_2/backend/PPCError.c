/* Windows diagnostic entry points; names from the GC3 Mac symbol map. */
#include "compiler/common.h"

typedef struct ErrorEscape { void *next; char jumpBuffer[1]; } ErrorEscape;
extern ErrorEscape *data_0071035c;
extern UInt8 data_00725f3f, data_0070f094;
extern char error_jmp_buf[];
extern __declspec(noreturn) void longjmp(void *, int);
extern void CError_Internal(const char *, int);
extern void InlineAsm_LongJump(void);
extern void fn_0044e000(char *, SInt16, SInt16);
extern void fn_0045c600(SInt32, const char *, char *, int, int);

#define va_start(ap, parm) do { \
    char *argumentAddress = (char *)&parm; \
    char *argumentEnd = (char *)(&parm + 1); \
    ap = argumentAddress + (argumentEnd - argumentAddress + 3) / 4 * 4; \
} while (0)

static inline void PPCError_GetErrorString(char *buffer, SInt16 code)
{
    if (code < 1 || code >= 166)
        CError_Internal("PPCError.c", 52);
    fn_0044e000(buffer, 10001, code + 1000);
}

void PPCError_ErrorTerm(SInt16 code, ...)
{
    char buffer[256];
    char *args;
    SInt32 diagnostic;
    if (data_0071035c)
        longjmp(data_0071035c->jumpBuffer, 1);
    va_start(args, code);
    diagnostic = code;
    PPCError_GetErrorString(buffer, diagnostic);
    fn_0045c600(diagnostic + 33000, buffer, args, 1, 0);
    if (data_00725f3f)
        InlineAsm_LongJump();
    longjmp(error_jmp_buf, 1);
}

void PPCError_Message(char *message, ...)
{
    char *args;
    if (data_0071035c)
        return;
    va_start(args, message);
    fn_0045c600(33166, message, args, 0, 1);
}

void PPCError_Warning(SInt32 code, ...)
{
    char buffer[256];
    char *args;
    SInt32 diagnostic;
    if (data_0071035c || data_0070f094)
        return;
    va_start(args, code);
    diagnostic = code;
    PPCError_GetErrorString(buffer, diagnostic);
    fn_0045c600(diagnostic + 33000, buffer, args, 0, 1);
}

void PPCError_Error(SInt32 code, ...)
{
    char buffer[256];
    char *args;
    SInt32 diagnostic;
    if (data_0071035c)
        longjmp(data_0071035c->jumpBuffer, 1);
    va_start(args, code);
    diagnostic = code;
    PPCError_GetErrorString(buffer, diagnostic);
    fn_0045c600(diagnostic + 33000, buffer, args, 0, 0);
    if (data_00725f3f)
        InlineAsm_LongJump();
}
