/* Native cobraError.c diagnostics; unsupported symbol identities retain addresses. */
#include "compiler/common.h"
#include <string.h>

typedef struct ErrorEscape { void *next; char jumpBuffer[1]; } ErrorEscape;
extern ErrorEscape *data_0071035c;
extern UInt8 data_00725f3f, data_0070f094;
extern char error_jmp_buf[];
extern __declspec(noreturn) void longjmp(void *, int);
extern void CError_Internal(const char *, int);
extern void InlineAsm_LongJump(void);
extern void fn_0045c600(SInt32, const char *, char *, int, int);

static const char cobraErrorFilename[] = "cobraError.c";
static char *cobraErrorStrings[] = {
    "%u was not assigned to a %u register (try using register qualifier)",
    "%u was assigned to the wrong class of register %u expected %u",
    "GCC constraint '%u' indicates writing but expression is constant",
    "GCC constraint '%u' is not supported at this time.",
    "%i arguments to gcc style inline assember exceeded maximum number supported (%i)",
    "%i alternates in a single argument to gcc style inline assember exceeded maximum number supported (%i)",
    "GCC style assembler processing could not match any of the constraints in '%u'.",
    "expected a register name here.",
    "%o can not be assigned to a %u register (it is an array or structure, or had it's address taken)",
    "global register variable '%o' cannot be assigned %u%i because that register has already been assigned to something else",
    "global register variables must be variables; '%n' isn't a variable",
    "all registers are explictly used, can't color virtual '%u' registers",
    "function consumes too many virtual registers; make function smaller, reduce inlining, or try optimization level 0",
    "Optimizer computes it would need more than %iM of memory to compute memory def-use chains.  Some optimizations disabled\nLimit currently set to %iM\nIncrease limit using '#pragma opt_usedef_mem_limit %i'",
    "Optimizer computes it would need more than %iM of memory to compute register def-use chains.  Key Optimizations Failed\nLimit currently set to %iM\nIncrease limit using '#pragma opt_usedef_mem_limit %i'"
};

#define va_start(ap, parm) do { \
    char *argumentAddress = (char *)&parm; \
    char *argumentEnd = (char *)(&parm + 1); \
    ap = argumentAddress + (argumentEnd - argumentAddress + 3) / 4 * 4; \
} while (0)

static inline void GetErrorString(char *buffer, SInt16 code)
{
    if (code < 1 || code >= 16)
        CError_Internal(cobraErrorFilename, 61);
    strcpy(buffer, cobraErrorStrings[code - 1]);
}

void fn_005ed160(SInt32 code, ...)
{
    char buffer[256];
    char *args;
    SInt32 diagnostic;
    switch (code) {
    case 0: code = 5; break;
    case 1: code = 6; break;
    case 2: code = 7; break;
    default: CError_Internal(cobraErrorFilename, 169); break;
    }
    if (data_0071035c)
        longjmp(data_0071035c->jumpBuffer, 1);
    va_start(args, code);
    diagnostic = code;
    GetErrorString(buffer, diagnostic);
    fn_0045c600(diagnostic + 34000, buffer, args, 0, 0);
    if (data_00725f3f)
        InlineAsm_LongJump();
}

void fn_005ed260(SInt16 code, ...)
{
    char buffer[256];
    char *args;
    SInt32 diagnostic;
    if (data_0071035c)
        longjmp(data_0071035c->jumpBuffer, 1);
    va_start(args, code);
    diagnostic = code;
    GetErrorString(buffer, diagnostic);
    fn_0045c600(diagnostic + 34000, buffer, args, 1, 0);
    if (data_00725f3f)
        InlineAsm_LongJump();
    longjmp(error_jmp_buf, 1);
}

void fn_005ed320(SInt32 code, ...)
{
    char buffer[256];
    char *args;
    SInt32 diagnostic;
    if (data_0071035c || data_0070f094)
        return;
    va_start(args, code);
    diagnostic = code;
    GetErrorString(buffer, diagnostic);
    fn_0045c600(diagnostic + 34000, buffer, args, 0, 1);
}

void fn_005ed3d0(SInt32 code, ...)
{
    char buffer[256];
    char *args;
    SInt32 diagnostic;
    if (data_0071035c)
        longjmp(data_0071035c->jumpBuffer, 1);
    va_start(args, code);
    diagnostic = code;
    GetErrorString(buffer, diagnostic);
    fn_0045c600(diagnostic + 34000, buffer, args, 0, 0);
    if (data_00725f3f)
        InlineAsm_LongJump();
}
