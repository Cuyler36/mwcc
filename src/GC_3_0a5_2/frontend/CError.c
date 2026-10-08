#define CERROR_FILE "CError.c"
#include "compiler/common.h"
#include "compiler/CError.h"
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

struct GC3ErrorToken { UInt32 words[3]; };
static UInt8 cerror_handlinginternal;
static SInt32 cerror_checkerrorid;
static SInt32 cerror_checkfounderrs;
static UInt8 cerror_checkmode;
static SInt32 cerror_lasterrorline;
static SInt16 cerror_errorcount;
static struct GC3ErrorToken cerror_token, cerror_locktoken;
extern void *data_0071079c;
extern void *fn_00459d70(void *, void *);
extern UInt8 fn_0045d700(SInt32, SInt32);
extern void CError_Error(SInt32 code, ...);
extern void *lalloc(SInt32 size);

void CError_ResetErrorSkip(void) { cerror_lasterrorline = -1; }

void CError_SetErrorToken(struct GC3ErrorToken *token)
{
    cerror_token = *token;
}

void fn_00462de0(struct GC3ErrorToken *token, struct GC3ErrorToken *saved)
{
    *saved = cerror_token;
    if (token && token->words[0]) goto set;
done:
    return;
set:
    cerror_token = *token;
    goto done;
}

void CError_SetNullErrorSourceRef(void) { cerror_locktoken.words[0] = -1; }

void CError_SetErrorSourceRef(struct GC3ErrorToken *token)
{
    if (token && token && token->words[0]) cerror_locktoken = *token;
}

void CError_BeginErrorCheckMode(SInt32 id)
{
    cerror_checkmode = 1;
    cerror_checkfounderrs = 0;
    cerror_checkerrorid = id;
}

void CError_Init(void)
{
    cerror_errorcount = 0;
    cerror_lasterrorline = -1;
    cerror_locktoken.words[0] = 0;
    cerror_token.words[0] = 0;
    cerror_checkmode = 0;
    cerror_handlinginternal = 0;
    fn_00459d70(data_0071079c, fn_0045d700);
}

static inline void CError_BufferGrow(StrBuf *buffer, UInt32 amount)
{
    char *storage = lalloc(buffer->size + amount);
    memcpy(storage, buffer->start, buffer->size);
    buffer->start = storage;
    buffer->cursor = storage + buffer->size - buffer->avail;
    buffer->size += amount;
    buffer->avail += amount;
}

void CError_BufferAppendString(StrBuf *buffer, const char *text)
{
    UInt32 length;
    if (buffer) {
        length = strlen(text);
        if (buffer->avail < length) CError_BufferGrow(buffer, length + 256);
        memcpy(buffer->cursor, text, length);
        buffer->cursor += length;
        buffer->avail -= length;
    }
}

extern char *fn_0045c650(char *, SInt32, const char *, char *);
extern void fn_0045d380(SInt32, const char *, UInt8, UInt8);
extern SInt32 fn_00459110(void *, SInt32);
extern UInt8 data_00725ffe;
extern void *cprep_cu;
extern void CompilerGetCString(SInt16, char *);
extern void FreeGList(void *);
extern char data_0070f838[];
extern UInt8 data_00725e6c;

void CError_VAErrorMessage(SInt32 code, const char *format, char *args,
                          UInt8 force, UInt8 warning)
{
    char buffer[256];
    char *message = fn_0045c650(buffer, sizeof(buffer), format, args);
    fn_0045d380(code, message, force, warning);
}

void CError_QualifierCheck(UInt32 flags)
{
    if (flags) {
        UInt8 found = 0;
        if (flags & 0x1) { CError_Error(10313, "const"); found = 1; }
        if (flags & 0x2) { CError_Error(10313, "volatile"); found = 1; }
        if (flags & 0x200000) { CError_Error(10313, "restrict"); found = 1; }
        if (flags & 0x4) { CError_Error(10313, "asm"); found = 1; }
        if (flags & 0x8) { CError_Error(10313, "pascal"); found = 1; }
        if (flags & 0x10) { CError_Error(10313, "inline"); found = 1; }
        if (flags & 0x20) { CError_Error(10313, "& reference type"); found = 1; }
        if (flags & 0x40) { CError_Error(10313, "explicit"); found = 1; }
        if (flags & 0x80) { CError_Error(10313, "mutable"); found = 1; }
        if (flags & 0x100) { CError_Error(10313, "virtual"); found = 1; }
        if (flags & 0x80000000) { CError_Error(10313, "__declspec(interrupt)"); found = 1; }
        if (flags & 0x1f000000) { CError_Error(10313, "__attribute__((aligned(...)))"); found = 1; }
        if (!found) CError_Error(10176);
    }
}

static inline void CError_UserBreakImpl(void)
{
    CompilerGetCString(8, error_message_buffer);
    if (*((UInt8 *)cprep_cu + 0x25a) && *(void **)data_0070f838)
        FreeGList(data_0070f838);
    *(SInt32 *)((char *)cprep_cu + 4) = 0;
    longjmp(error_jmp_buf, 1);
}

void CError_UserBreak(void) { CError_UserBreakImpl(); }

void CError_NoMem(void)
{
    data_00725e6c = 1;
    longjmp(error_jmp_buf, 1);
}

void CError_EndErrorCheckMode(SInt32 expected)
{
    SInt32 id = fn_00459110(data_0071079c, cerror_checkerrorid);
    cerror_checkmode = 0;
    switch (id) {
        case 10428:
        case 10429:
        case 10430:
        case 10431:
        case 10433:
        case 10434:
        case 10435:
        case 10436:
        case 10437:
        case 10438:
        case 10439:
        case 10440:
        case 10441:
        case 10442:
        case 10443:
        case 10447:
        case 10448:
        case 10449:
        case 10451:
        case 10453:
        case 10462:
        case 10463:
        case 10464:
        case 10465:
        case 10466:
        case 10467:
        case 10478:
        case 10479:
            if (!data_00725ffe) return;
            break;
        default:
            if (data_00725ffe) return;
            break;
    }
    if (expected >= 0) {
        if (cerror_checkfounderrs != expected) CError_Error(10414);
    } else if (!cerror_checkfounderrs) CError_Error(10414);
}

extern char *fn_0044d570(void *);
extern void *data_00716c9c;
extern char emptystring[];

static inline void CError_InternalImpl(const char *file, int line)
{
    char format[256];
    char message[512];
    char *path, *name;
    if (cerror_handlinginternal) goto terminate;
    cerror_handlinginternal = 1;
    path = fn_0044d570((char *)cprep_cu + 0x14c);
    if (data_00716c9c) {
        if (*(char **)((char *)data_00716c9c + 0x44))
            name = *(char **)((char *)data_00716c9c + 0x44) + 10;
        else
            name = *(char **)((char *)data_00716c9c + 0x0c) + 10;
    } else name = emptystring;
    CompilerGetCString(5, format);
    snprintf(message, sizeof(message), format, file, line, name, path);
    fn_0045d380(10424, message, 1, 0);
terminate:
    longjmp(error_jmp_buf, 1);
}

int CError_Internal(const char *file, int line) { CError_InternalImpl(file, line); }

extern void fn_0055ec00(const char *, char *, SInt32);
extern void fn_0045e350(StrBuf *, void *);
extern void fn_0045f060(StrBuf *, void *, UInt32);
extern void fn_00460fc0(StrBuf *, void *);
extern void fn_0044dea0(char *, void *, SInt32);
extern void fn_0045d010(StrBuf *);
extern char *fn_00447940(void);
extern UInt8 data_0070f1e5;

static inline void CError_BufferPutChar(StrBuf *buf, char c)
{
    if (!buf->avail) CError_BufferGrow(buf, 256);
    *buf->cursor++ = c;
    --buf->avail;
}

static inline void CError_BufferPutString(StrBuf *buf, const char *text)
{
    UInt32 length = strlen(text);
    if (buf->avail < length) CError_BufferGrow(buf, length + 256);
    memcpy(buf->cursor, text, length);
    buf->cursor += length;
    buf->avail -= length;
}

char *CError_ErrorMessageVA(char *buffer, SInt32 size, const char *fmt, char *args)
{
    StrBuf eb;
    char temp[256];
    char path[260];
    char c;
    void *type;
    UInt32 qualifiers;
    char *name;
    if (!fmt) return 0;
    eb.cursor = buffer;
    eb.avail = size - 1;
    eb.start = eb.cursor;
    eb.size = eb.avail;
    for (;;) {
        switch (c = *fmt) {
            case '%':
                switch (fmt[1]) {
                    case 'n':
                        args += 4;
                        fn_0055ec00(*(char **)(args - 4), temp, sizeof(temp));
                        CError_BufferPutString(&eb, temp);
                        fmt += 2; continue;
                    case 's':
                    case 'u':
                        args += 4;
                        name = *(char **)(args - 4);
                        CError_BufferPutString(&eb, name);
                        fmt += 2; continue;
                    case 'o':
                        args += 4;
                        fn_0045e350(&eb, *(void **)(args - 4));
                        fmt += 2; continue;
                    case 't':
                        args += 4; type = *(void **)(args - 4);
                        args += 4; qualifiers = *(UInt32 *)(args - 4);
                        fn_0045f060(&eb, type, qualifiers);
                        fmt += 2; continue;
                    case 'e':
                        args += 4;
                        fn_00460fc0(&eb, *(void **)(args - 4));
                        fmt += 2; continue;
                    case '%':
                        CError_BufferPutChar(&eb, '%');
                        fmt += 2; continue;
                    case 'i':
                        args += 4;
                        sprintf(temp, "%ld", *(SInt32 *)(args - 4));
                        CError_BufferPutString(&eb, temp);
                        fmt += 2; continue;
                    case 'x':
                        args += 4;
                        sprintf(temp, "%x", *(UInt32 *)(args - 4));
                        CError_BufferPutString(&eb, temp);
                        fmt += 2; continue;
                    case 'f':
                        args += 4;
                        fn_0044dea0(path, *(void **)(args - 4), 0);
                        CError_BufferPutString(&eb, path);
                        fmt += 2; continue;
                    default:
                        CError_InternalImpl(CERROR_FILE, 0x740);
                        break;
                }
                break;
            case 0: break;
            default:
                ++fmt;
                CError_BufferPutChar(&eb, c);
                continue;
        }
        break;
    }
    fn_0045d010(&eb);
    if (data_0070f1e5 && (name = fn_00447940())) {
        CError_BufferPutString(&eb, "\n(included from:\n");
        CError_BufferPutString(&eb, name);
        CError_BufferPutChar(&eb, ')');
    }
    if (!eb.avail) CError_BufferGrow(&eb, 1);
    *eb.cursor = 0;
    eb.avail = 0;
    return eb.start;
}

/* Native diagnostic IDs 10100 through 10569, in original table order. */
static const char *cerror_errorstrings[470] = {
    "illegal character constant",
    "illegal string constant",
    "unexpected end of file",
    "unterminated comment",
    "undefined preprocessor directive",
    "illegal token",
    "string too long",
    "identifier expected",
    "macro '%u' redefined",
    "illegal argument list",
    "too many macro arguments",
    "macro(s) too complex",
    "unexpected end of line",
    "end of line expected",
    "'(' expected",
    "')' expected",
    "',' expected",
    "preprocessor syntax error",
    "preceding #if is missing",
    "unterminated #if / macro",
    "unexpected token",
    "declaration syntax error",
    "identifier '%u' redeclared",
    "';' expected",
    "illegal constant expression",
    "']' expected",
    "illegal use of type '%t'",
    "illegal function definition",
    "illegal function return type",
    "illegal array declaration",
    "'}' expected",
    "illegal struct/union/enum/class definition",
    "struct/union/enum/class tag '%u' redefined",
    "struct/union/class member '%u' redefined",
    "declarator expected",
    "'{' expected",
    "illegal use of incomplete struct/union/class '%t'",
    "",
    "illegal bitfield type '%t'",
    "division by 0",
    "undefined identifier '%u'",
    "expression syntax error",
    "not an lvalue",
    "illegal operation",
    "illegal operand",
    "data type is incomplete",
    "illegal type",
    "too many initializers",
    "pointer/array required",
    "not a struct/union/class",
    "'%u' is not a struct/union/class member",
    "the file '%u' cannot be opened",
    "illegal instruction for this processor",
    "illegal operands for this processor",
    "number is out of range",
    "illegal addressing mode",
    "illegal data size",
    "illegal register list",
    "branch out of range",
    "undefined label '%u'",
    "reference to label '%u' is out of range",
    "call of non-function",
    "function call does not match prototype",
    "illegal use of register variable",
    "illegal type cast",
    "function already has a stackframe",
    "function has no initialized stackframe",
    "value is not stored in register",
    "",
    "illegal use of keyword",
    "':' expected",
    "label '%u' redefined",
    "case constant defined more than once",
    "default label defined more than once",
    "illegal initialization",
    "illegal use of inline function",
    "illegal type qualifier(s)",
    "illegal storage class",
    "function has no prototype",
    "illegal assignment to constant",
    "illegal use of precompiled header",
    "illegal data in precompiled header (%u)",
    "variable / argument '%u' is not used in function",
    "illegal use of direct parameters",
    "return value expected",
    "variable '%u' is not initialized before being used",
    "illegal #pragma",
    "illegal access to protected/private member",
    "ambiguous access to class/struct/union member",
    "illegal use of 'this'",
    "unimplemented feature: %u",
    "illegal use of 'HandleObject'",
    "",
    "illegal 'operator' declaration",
    "illegal use of abstract class ('%o')",
    "illegal use of pure function",
    "illegal reference type '%t'",
    "illegal function overloading",
    "",
    "ambiguous access to overloaded function ",
    "illegal access/using declaration",
    "illegal 'friend' declaration",
    "",
    "class has no default constructor",
    "illegal operator",
    "illegal default argument(s)",
    "possible unwanted ';'",
    "possible unwanted assignment",
    "possible unwanted compare",
    "illegal implicit conversion from '%t' to\n'%t'",
    "local data >32k",
    "illegal jump past initializer",
    "illegal ctor initializer",
    "cannot construct %t's base class '%t'",
    "cannot construct %t's direct member '%u'",
    "#if nesting overflow",
    "illegal empty declaration",
    "illegal implicit enum conversion from '%t' to\n'%t'",
    "illegal use of #pragma parameter",
    "virtual functions cannot be pascal functions",
    "illegal implicit const/volatile pointer conversion from '%t' to\n'%t'",
    "illegal use of non-static member",
    "illegal precompiled header version (%u)",
    "illegal precompiled header compiler flags or target (%u)",
    "'const' or '&' variable needs initializer",
    "'%o' hides inherited virtual function '%o'",
    "pascal function cannot be overloaded",
    "virtual function override type mismatch between '%o' and '%o'\n'%t'\n'%t'",
    "non-const '&' reference initialized to temporary",
    "illegal template declaration",
    "'<' expected",
    "'>' expected",
    "illegal template argument(s)",
    "cannot instantiate '%o'",
    "template redefined",
    "template parameter mismatch",
    "cannot pass const/volatile data object to non-const/volatile member function",
    "preceding '#pragma push' is missing",
    "illegal explicit template instantiation",
    "illegal X::X(X) copy constructor",
    "",
    "illegal constructor/destructor declaration",
    "'catch' expected",
    "#include nesting overflow",
    "cannot convert\n'%t' to\n'%t'",
    "type mismatch\n'%t' and\n'%t'",
    "class type expected",
    "illegal explicit conversion from '%t' to\n'%t'",
    "function call '*' does not match",
    "identifier '%u' redeclared\nwas declared as: '%t'\nnow declared as: '%t'",
    "",
    "class '%t': '%o' has more than one final overrider:\n'%o'\nand '%o'",
    "exception handling option is disabled",
    "",
    "",
    "const member '%u' is not initialized",
    "'&' reference member '%u' is not initialized",
    "RTTI option is disabled",
    "constness casted away",
    "illegal const/volatile '&' reference initialization",
    "inconsistent linkage: 'extern' object redeclared as 'static'",
    "unknown assembler instruction mnemonic",
    "local data > 224 bytes",
    "'%u' could not be assigned to a register",
    "illegal exception specification",
    "exception specification list mismatch '%e' and '%e'",
    "the parameter(s) of the '%n' function must be immediate value(s)",
    "SOM classes can only inherit from other SOM based classes",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "'%u' is not an Objective-C class",
    "method '%m' redeclared",
    "undefined method '%m'",
    "",
    "class '%t' redefined",
    "Objective-C type '%u' is undefined (should be defined in objc.h)",
    "Objective-C type '%u' has unexpected type",
    "method '%m' not defined",
    "method '%m' redefined",
    "illegal use of 'self'",
    "illegal use of 'super'",
    "illegal message receiver",
    "receiver cannot handle this message",
    "ambiguous message selector\nused: '%m'\nalso had: '%m'",
    "unknown message selector",
    "illegal use of Objective-C object",
    "protocol '%u' redefined",
    "protocol '%u' is undefined",
    "protocol '%u' is already in protocol list",
    "category '%u' redefined",
    "category '%u' is undefined",
    "illegal use of '%u'",
    "template too complex or recursive",
    "illegal return value in void/constructor/destructor function",
    "assigning a non-int numeric value to an unprototyped function",
    "implicit arithmetic conversion from '%t' to '%t'",
    "preprocessor #error directive",
    "ambiguous access to name found '%u' and '%u'",
    "illegal namespace",
    "illegal use of namespace name",
    "illegal name overloading",
    "instance variable list does not match @interface",
    "protocol list does not match @interface",
    "super class does not match @interface",
    "function result is a pointer/reference to an automatic/temporary variable",
    "cannot allocate initialized objects in the scratchpad",
    "illegal class member access",
    "data object '%o' redefined",
    "illegal access to local variable from other function",
    "illegal implicit member pointer conversion",
    "typename redefined",
    "object '%o' redefined",
    "'main' not defined as external 'int main()' function",
    "illegal explicit template specialization",
    "name has not been declared in namespace/class",
    "preprocessor #warning directive",
    "illegal use of asm inline function",
    "illegal use of C++ feature in EC++",
    "illegal use of template argument dependent type 'T::%u'",
    "illegal use of alloca() in function argument",
    "'%o' inline function call from '%o' not inlined",
    "inconsistent use of 'class' and 'struct' keywords",
    "illegal partial specialization",
    "",
    "ambiguous use of partial specialization",
    "local classes shall not have member templates",
    "illegal template argument dependent expression",
    "implicit 'int' is no longer supported in C++",
    "%i pad byte(s) inserted after data member '%u'",
    "pure function '%o' is not virtual",
    "illegal virtual function '%o' in 'union'",
    "cannot pass 'void' or 'function' parameter",
    "illegal static const member '%u' initialization",
    "'typename' is missing in template argument dependent qualified type",
    "more than one expression in non-class type conversion",
    "template non-type argument '%o' does not have external linkage",
    "illegal or unsupported __attribute__",
    "",
    "cannot create object file '%f'",
    "error writing to object file '%f'",
    "printf-family format string doesn't match arguments",
    "scanf-family format string doesn't match arguments",
    "",
    "illegal macro argument name '%u'",
    "case has an empty range of values",
    "'long long' switch() is not supported",
    "'long long' case range is not supported",
    "expression has no side effect",
    "result of function call is not used",
    "illegal non-type template argument",
    "illegal use of abstract class ('%t')",
    "illegal use of 'template' prefix",
    "template parameter/argument list mismatch",
    "cannot find matching deallocation function for '%t'",
    "illegal operand '%t'",
    "illegal operands '%t' %u '%t'",
    "illegal use of default template-argument",
    "illegal UUID syntax",
    "",
    "illegal access from '%t' to protected/private member '%o'",
    "integral type is not large enough to hold pointer",
    "",
    "illegal use of const/volatile function qualifier sequence",
    "illegal optimization level for this limited version of CodeWarrior",
    "no UUID defined for type '%t'",
    "using implicit copy assignment for class with const or reference member ('%t')",
    "unimplemented assembler instruction/directive",
    "override of dllimport function '%u' only has application/DLL scope",
    "illegal combination of operands in inline statement at line %i",
    "illegal operand in inline statement at line %i",
    "function call '*' is ambiguous",
    "'%u' is not a member of class '%t'",
    "immediate operand in inline statement at line %i cannot span more than 8 bits",
    "'__except' or '__finally' expected",
    "cannot mix structured exception handling and C++ exception handling",
    "illegal multiway transfer out of __try...__finally statement",
    "illegal use of structured exception handling keyword outside of __try statement",
    "illegal use of __leave in __try...__except statement",
    "unions cannot have reference members",
    "unions cannot have static data members",
    "unions cannot have nontrivial class members",
    "unions cannot have base classes",
    "unions cannot be used as base classes",
    "'%u' is not a member of namespace '%t'",
    "'%u' is not a class/namespace name",
    "'%u' is not a class name",
    "recursive operator-> delegation",
    "illegal use of type-name",
    "empty array must be last class/struct member",
    "included file '%u' is spelled differently on disk ('%u')",
    "illegal access from '%t' to protected/private member '%t::%u'",
    "",
    "no matching error(s) reported in error check mode",
    "ambiguous ?: expression, '%t' can be converted to '%t' and vice versa",
    "override '%o' is declared without 'virtual' keyword",
    "illegal use of calling convention declarator",
    "calling convention ignored due to incompatible compiler options",
    "illegal redefinition of UUID for '%t'",
    "using '#pragma once [on]' in a precompiled header",
    "ambiguous access from '%t' to '%t'",
    "allocation/deallocation functions shall be global scope or class members",
    "types that are declared in parameter lists ('%u') go out of scope at the end of the function declaration/definition,\nthis is probably not what you want (maybe use a forward declaration?)",
    "internal scanner error (report to <cw_bug@freescale.com>)",
    "expression too complex (perhaps enable optimizer?)",
    "too many errors emitted, quitting",
    "out of memory",
    "cannot load main source file (%u)",
    "the file '%u' cannot be opened (%u)",
    "system does not support converting from '%u',\ntreating as ASCII",
    "unterminated comment",
    "unknown escape sequence '\\%u'",
    "number expected",
    "string expected",
    "    (corresponding #line reference)",
    "    (location of previous definition)",
    "argument expected while expanding macro '%u' (got %i, wanted %u%i)",
    "unexpected argument while expanding macro '%u' (wanted %i)",
    "invalid token pasting of '%u' and '%u'",
    "illegal token for integral constant expression",
    "illegal number",
    "invalid integer constant",
    "invalid floating-point constant",
    "character is out of range",
    "character cannot be represented in a 'long long'",
    "illegal universal character 0x%x",
    "ASCII shift state expected",
    "multi-byte character constant",
    "illegal multi-line string constant",
    "loss of precision in floating-point constant",
    "nested comment detected",
    "illegal universal character sequence",
    "illegal UTF-8 sequence, treating as raw bytes",
    "the (elided) copy constructor '%o' is not callable because the reference parameter cannot be bound to an rvalue",
    "could not create or write file '%u' for instrumentation ('%u')",
    "could not read file '%u' for instrumentation ('%u')",
    "cannot locate instrumenter program '%u' (PATH='%u', AMC_HOME='%u')",
    "cannot execute instrumenter program '%u' (%u)\n(command line: '%u')\n%u",
    "instrumenter program '%u' failed with exit code %i\n(command line: '%u')\n%u",
    "cannot use precompiled header '%u' with these instrumentation options",
    "compatible IDB list changed; you may want to remove object code and rebuild this target",
    "undefined macro '%u' used in #if or #elif conditional",
    "combining character detected at beginning of identifier",
    "extended universal character used in identifier",
    "cannot locate prefix file '%u'",
    "illegal option '%u'",
    "cannot query option '%u'",
    "object '%o' hidden by local declaration",
    "complex types are not implemented",
    "variable length arrays cannot be used in function template prototypes or local template typedefs",
    "variable length array types can only be used in local or function prototype scope",
    "the local type '%t' cannot be used in template arguments",
    "'<' expected (you may have accidentally used a <: token)",
    "template argument list expected",
    "illegal bitfield size '%i'",
    "invalid message number",
    "could not generate intrinsic '%u' due to incompatible arguments or compiler options",
    "illegal macro name; '%u' is a C++ keyword",
    "illegal macro name '%u'",
    "deleting a void pointer is undefined",
    "cannot enable instance manager here",
    "some instances are missing; please rebuild",
    "illegal or unsupported __declspec",
    "illegal use of __declspec(%u)",
    "illegal use of function qualifier(s)",
    "illegal use of data qualifier(s)",
    "pointer to integral conversion",
    "integral to pointer conversion",
    "cannot modify '%u' after declarations have begun",
    "using non-POD classes in variable argument lists is undefined",
    "%i arguments to gcc style inline assember exceeded maximum number supported (%i)",
    "%i alternates in a single argument to gcc style inline assember exceeded maximum number supported (%i)",
    "GCC style assembler processing could not match any of the constraints in '%u'.",
    "GCC constraint '%u' is not supported at this time.",
    "ignored attribute '%u' due to conflict with calling convention",
    "size of type is too large (maximum %i bytes)",
    "whitespace expected after integer constant (at '%u')",
    "illegal use of expression statement outside function",
    "a pointer/array type was expected for this operation instead of '%t'",
    "cannot write file '%u' (%u)",
    "direct struct members shall not have base classes",
    "anonymous unions/structs shall not have private/protected members",
    "anonymous unions/structs shall not have member functions",
    "illegal object definition in precompiled header:\n'%o'",
    "illegal overloading '%o'\nwas declared as '%t'\nnow declared as '%t'",
    "cannot use #pragma %u after declarations have begun",
    "the object '%o' has already been instantiated",
    "static assert check '%u' failed",
    "shell returned error %i storing object data for '%u' (whichfile=%i)",
    "cannot load IDB manipulation DLL ('%u');\nplease use external instrumenter",
    "cannot locate symbol '%u' in IDB manipulation DLL ('%u');\nplease use external instrumenter",
    "unsupported version '%u' in IDB manipulation DLL ('%u')",
    "IDB error: %u",
    "cannot instrument function '%u' since its body spans multiple files\n('%u':%i -> '%u':%i)",
    "illegal IPA file format",
    "illegal IPA file version",
    "the global object '%o' (%t)\nfrom '%u'\nconflicts with the object '%o' (%t)\nin '%u'",
    "the global type '%t'\ndefinded in '%u'\nconflicts with a type in '%u'",
    "shell returned error %i loading object data for '%u' (whichfile=%i)",
    "invalid tagging method option value '%u'\n(expected integer for 'Write to address...' or expression containing '@' for 'Write through expression...')",
    "overriding IDB filename to %u for current multi-target IDB mode",
    "cannot add file '%u' to project (error %i); reset 'read-only' flag if necessary",
    "invalid memory allocator map file syntax in file '%u' line %i",
    "environment variable 'AMC_HOME' not defined:\nusing built-in CodeTEST declarations and disabling C++ memory coverage",
    "cannot read file '%u':\nusing built-in CodeTEST declarations and disabling C++ memory coverage",
    "did not find declaration for '%u' in '%u'",
    "cannot use both '#pragma instrument no_tag_files' and '#pragma instrument only_tag_files'",
    "#pragma '%u' is meaningless for native instrumentation",
    "cannot load allocator call map ('%u'); disabling memory instrumentation",
    "this target's IDB file not found in compatible IDB file list (%u)",
    "this feature is not supported in this release",
    "the global object '%o' is not defined",
    "CodeTEST compilation not supported during concurrent builds",
    "expected formal macro argument after '#'",
    "illegal or unsupported alignment value",
    "structs/classes with flexibile array members cannot be used as struct/class members or array elements",
    "flexible array member in otherwise empty struct",
    "cannot initialize nested flexible array members",
    "intrinsic functions cannot be defined",
    "the exception specification of the function '%o'\nis more restrictive than the specification of the override '%o'",
    "the target exception specification '%e'\nis more restrictive than the source specification '%e'",
    "    (corresponding point of instantiation)",
    "    (corresponding point of instantiation for '%t')",
    "    (corresponding point of instantiation for '%o')",
    "possible unwanted use of object address",
    "illegal 'main()' function call",
    "function declaration conflicts with using declaration for '%o'",
    "explicit template specialization without 'template<>' prefix",
    "illegal use of 'template<>' prefix",
    "the 'override' function '%o' does not override any inherited functions",
    "the 'final' function '%o' is overridden by '%o'",
    "environment variable '%u' not defined: using empty string as default",
    "local variables/parameters ('%o') shall not be used in a default argument",
    "no suitable copy-ctor for class '%t'",
    "the type '::std::type_info' that is required for 'typeid' expressions is not defined (usually defined in the <typeinfo> header file)",
    "no members allowed after a flexible array",
    "'typename' is not required/legal in this context",
    "calling class method using an instance",
    "calling instance method using class method",
    "the const or reference class member '%u' is not initialized",
    "the enumerator '%u' does not have a matching case label",
    "C99 this cast is incompatible with the C99 typing rules and could make the alias by type analysis fail",
    "identifier '%u' redeclared as '%t'",
    "identifier '%u' was originally declared as '%t'",
    "'typename' prefix used outside of template",
    "initializing '%t' with braces is non-standard",
    "declaration specifier conflict: %s",
    "flexible arrays are not allowed in unions",
    "the parameter '%u' has not been declared",
};

extern void *data_0071035c;
extern UInt8 data_0070f094, data_00725f3f;
extern SInt16 data_00717466;
extern void fn_0055eba0(void);
extern void fn_0045be40(void);
#define GC3_VA_START(ap, last) ((ap) = (char *)((int)((char *)&(last)) + (((int)((char *)(&(last) + 1)) - (int)((char *)&(last)) + 3) / 4 * 4)))

void CError_Warning(SInt32 code, ...)
{
    char format[256], buffer[256];
    char *args, *message;
    SInt32 diagnosticID;
    if (data_0071035c || data_0070f094) return;
    GC3_VA_START(args, code);
    diagnosticID = code;
    if (diagnosticID < 10100 || diagnosticID >= 10570) CError_InternalImpl(CERROR_FILE, 257);
    strcpy(format, cerror_errorstrings[diagnosticID - 10100]);
    message = fn_0045c650(buffer, 256, format, args);
    fn_0045d380(diagnosticID, message, 0, 1);
}

void CError_Error(SInt32 code, ...)
{
    char format[256], buffer[256];
    char *args, *message;
    SInt32 diagnosticID;
    if (data_0071035c) longjmp(*(jmp_buf *)((char *)data_0071035c + 4), 1);
    GC3_VA_START(args, code);
    diagnosticID = code;
    if (diagnosticID < 10100 || diagnosticID >= 10570) CError_InternalImpl(CERROR_FILE, 257);
    strcpy(format, cerror_errorstrings[diagnosticID - 10100]);
    message = fn_0045c650(buffer, 256, format, args);
    fn_0045d380(diagnosticID, message, 0, 0);
    if (data_00725f3f && !data_00725ffe) fn_0055eba0();
}

void CError_ErrorSkipExpr(SInt32 code, ...)
{
    char format[256], buffer[256];
    char *args, *message;
    SInt32 diagnosticID;
    if (data_0071035c) longjmp(*(jmp_buf *)((char *)data_0071035c + 4), 1);
    GC3_VA_START(args, code);
    diagnosticID = code;
    if (diagnosticID < 10100 || diagnosticID >= 10570) CError_InternalImpl(CERROR_FILE, 257);
    strcpy(format, cerror_errorstrings[diagnosticID - 10100]);
    message = fn_0045c650(buffer, 256, format, args);
    fn_0045d380(diagnosticID, message, 0, 0);
    fn_0045be40();
}

void CError_ErrorSkipStmt(SInt32 code, ...)
{
    char format[256], buffer[256];
    char *args, *message;
    SInt32 diagnosticID;
    if (data_0071035c) longjmp(*(jmp_buf *)((char *)data_0071035c + 4), 1);
    GC3_VA_START(args, code);
    diagnosticID = code;
    if (diagnosticID < 10100 || diagnosticID >= 10570) CError_InternalImpl(CERROR_FILE, 257);
    strcpy(format, cerror_errorstrings[diagnosticID - 10100]);
    message = fn_0045c650(buffer, 256, format, args);
    fn_0045d380(diagnosticID, message, 0, 0);
    do { fn_0045be40(); }
    while (data_00717466 != 0 && data_00717466 != -7 && data_00717466 != 59 &&
           data_00717466 != 125 && data_00717466 != 328);
}

extern void *oalloc(SInt32);
extern void fn_0045e5a0(StrBuf *, void *, void *, SInt32, SInt32, UInt32);
extern void fn_00460bb0(StrBuf *, void *);

static inline void CError_BufferInit(StrBuf *buf, char *buffer, SInt32 size)
{
    buf->cursor = buffer;
    buf->start = buf->cursor;
    buf->avail = size - 1;
    buf->size = buf->avail;
}
static inline void CError_BufferTerminate(StrBuf *buf)
{
    if (!buf->avail) CError_BufferGrow(buf, 1);
    *buf->cursor = 0;
    buf->avail = 0;
}

char *CError_GetObjectName(void *object)
{
    StrBuf buf;
    char buffer[256];
    CError_BufferInit(&buf, buffer, sizeof(buffer));
    fn_0045e350(&buf, object);
    CError_BufferTerminate(&buf);
    if (buf.start == buffer) buf.start = strcpy(lalloc(buf.size + 1), buf.start);
    return buf.start;
}

char *CError_GetFunctionName(void *object, void *type, UInt32 flag)
{
    StrBuf buf;
    char buffer[256];
    CError_BufferInit(&buf, buffer, sizeof(buffer));
    fn_0045e5a0(&buf, object, type, 0, 0, flag);
    CError_BufferTerminate(&buf);
    if (buf.start == buffer) buf.start = strcpy(lalloc(buf.size + 1), buf.start);
    return buf.start;
}

static inline char *CError_BufferGetString(StrBuf *buf, char *buffer, UInt8 permanent)
{
    char *result;
    if (permanent || buf->start == buffer) {
        if (permanent) result = oalloc(buf->size + 1);
        else result = lalloc(buf->size + 1);
        return strcpy(result, buf->start);
    }
    return buf->start;
}

char *CError_GetTypeName(void *type, UInt32 qualifiers, UInt8 permanent)
{
    StrBuf buf;
    char buffer[256];
    CError_BufferInit(&buf, buffer, sizeof(buffer));
    fn_0045f060(&buf, type, qualifiers);
    CError_BufferTerminate(&buf);
    return CError_BufferGetString(&buf, buffer, permanent);
}

char *CError_GetNameString(void *object, UInt8 permanent)
{
    StrBuf buf;
    char buffer[256];
    CError_BufferInit(&buf, buffer, sizeof(buffer));
    fn_00460bb0(&buf, object);
    CError_BufferTerminate(&buf);
    return CError_BufferGetString(&buf, buffer, permanent);
}

extern void fn_00461c60(StrBuf *, void *, SInt32);
extern void *fn_00540770(void *);

char *CError_GetQualifiedName(NameSpace *space, HashNameNode *name)
{
    StrBuf buf;
    char buffer[256];
    CError_BufferInit(&buf, buffer, sizeof(buffer));
    fn_00461c60(&buf, space, 1);
    CError_BufferPutString(&buf, (char *)name + 10);
    CError_BufferTerminate(&buf);
    if (buf.start == buffer) buf.start = strcpy(lalloc(buf.size + 1), buf.start);
    return buf.start;
}

void CError_AbstractClassError(void *type)
{
    void *function = fn_00540770(type);
    if (function) CError_Error(10194, function);
    else CError_Error(10372, type, 0);
}

extern UInt8 fn_004d5e80(void *, char *, SInt32, struct GC3ErrorToken *, SInt32, SInt32, SInt32);
extern UInt8 fn_004593b0(void *, SInt16, void *, const char *, SInt32, char *, SInt32);
extern SInt32 fn_004d6c40(void);
extern SInt32 __stdcall fn_00458b50(void *, SInt32);
extern void fn_00459200(void *, SInt32, void *, char *, SInt32, ...);
extern void fn_0045d5c0(SInt32);
extern char *data_00710814, *data_00715c68;
extern struct GC3ErrorToken data_0070ffcc;

void CError_ErrorMessage(SInt32 code, const char *message, UInt8 force, UInt8 warning)
{
    char position[276], text[128];
    void *saved_callback;
    struct GC3ErrorToken *token;
    void *where;
    SInt16 mode;
    saved_callback = fn_00459d70(data_0071079c, force ? 0 : fn_0045d700);
    if (cerror_locktoken.words[0]) token = &cerror_locktoken;
    else if (cerror_token.words[0]) token = &cerror_token;
    else token = 0;
    if (token && token->words[0] == -1) {
        where = 0;
        text[0] = 0;
    } else {
        where = 0;
        text[0] = 0;
        if (!data_00725e6c) {
            if (token && !token->words[0]) token = 0;
            if (!token && data_00710814 < data_00715c68)
                token = (struct GC3ErrorToken *)(data_00715c68 - 14);
            if (!token) token = &data_0070ffcc;
            if (!fn_004d5e80(position, text, 128, token, 0, 0, 0)) token = 0;
            else where = position;
        }
    }
    mode = warning ? 1 : 2;
    if (fn_004593b0(data_0071079c, mode, where, message, code, text, 0)) {
        if (fn_00458b50(*(void **)cprep_cu, fn_004d6c40())) CError_UserBreakImpl();
        if (token && token->words[0] != -1 && token->words[0] &&
            *(UInt8 *)((char *)token->words[0] + 8) == 1 &&
            fn_004d5e80(position, text, 128, token, 0, 0, 1)) {
            fn_00459d70(data_0071079c, 0);
            fn_00459200(data_0071079c, 0, position, text, 10435);
        }
        fn_0045d5c0(mode);
    }
    cerror_locktoken.words[0] = 0;
    fn_00459d70(data_0071079c, saved_callback);
}

extern UInt8 data_00725ecb, data_00725dfa;
extern SInt16 fn_00447b70(void);
extern SInt32 __stdcall fn_00420060(void *, void *, char *, void *, SInt32, SInt32);

UInt8 fn_0045d700(SInt32 mode, SInt32 code)
{
    char text[256];
    if (cerror_checkmode) {
        if (!cerror_checkerrorid || cerror_checkerrorid == code) {
            ++cerror_checkfounderrs;
            cerror_locktoken.words[0] = 0;
            cerror_lasterrorline = fn_004d6c40();
            return 0;
        }
        if (cerror_lasterrorline == fn_004d6c40()) return 0;
    }
    if (mode == 2) data_00725dfa = (data_00725ecb = 1);
    if (!data_00725f3f && cerror_lasterrorline == fn_004d6c40()) {
        if (mode && cerror_errorcount++ >= 50) {
            if (cerror_errorcount > 60) longjmp(error_jmp_buf, 1);
            data_00717466 = fn_00447b70();
            cerror_errorcount = 0;
            if (!data_00717466) {
                CompilerGetCString(1, text);
                fn_00420060(*(void **)cprep_cu, 0, text, 0, 2, code);
                longjmp(error_jmp_buf, 1);
            }
        }
        cerror_locktoken.words[0] = 0;
        return 0;
    }
    if (mode == 2) {
        cerror_lasterrorline = fn_004d6c40();
        cerror_errorcount = 0;
    }
    return 1;
}

extern SInt32 fn_00545210(UInt32);

static inline void CError_BufferAppendStringInline(StrBuf *buf, const char *text)
{
    if (buf) CError_BufferPutString(buf, text);
}

void CError_BufferAppendQualifier(StrBuf *buf, UInt32 qualifiers)
{
    char text[64];
    SInt32 alignment;
    if (qualifiers & 8) CError_BufferAppendStringInline(buf, "pascal ");
    if (qualifiers & 1) CError_BufferAppendStringInline(buf, "const ");
    if (qualifiers & 2) CError_BufferAppendStringInline(buf, "volatile ");
    if (qualifiers & 0x40) CError_BufferAppendStringInline(buf, "explicit ");
    if (qualifiers & 0x200000) CError_BufferAppendStringInline(buf, "restrict ");
    if (qualifiers & 0x1f000000) {
        alignment = fn_00545210(qualifiers);
        if (qualifiers & 0x10000000) {
            CError_BufferAppendStringInline(buf, "__packed");
            if (alignment > 1) sprintf(text, "(%d)", alignment);
            else text[0] = 0;
        } else {
            CError_BufferAppendStringInline(buf, "__aligned");
            if (alignment >= 1) sprintf(text, "(%d)", alignment);
            else text[0] = 0;
        }
        CError_BufferAppendStringInline(buf, text);
        CError_BufferAppendStringInline(buf, " ");
    }
}

struct GC3ErrorNameSpace {
    struct GC3ErrorNameSpace *parent;
    char *name;
    void *unused;
    char *theclass;
};
extern char *fn_0053ed70(void *);
extern void fn_00461e80(StrBuf *, void *);

void CError_BufferAppendNameSpace(StrBuf *buf, struct GC3ErrorNameSpace *space, UInt8 templates)
{
    for (; space; space = space->parent) {
        if (space->name) {
            CError_BufferAppendNameSpace(buf, space->parent, templates);
            if (space->theclass) {
                CError_BufferAppendStringInline(buf, *(char **)(space->theclass + 10) + 10);
                if (templates && (*(UInt32 *)(space->theclass + 0x22) & 0x800)) {
                    void *args = *(void **)(fn_0053ed70(space->theclass) + 0x44);
                    if (!args) args = *(void **)(fn_0053ed70(space->theclass) + 0x3c);
                    fn_00461e80(buf, args);
                }
            } else CError_BufferAppendStringInline(buf, space->name + 10);
            CError_BufferAppendStringInline(buf, "::");
            return;
        }
    }
}

extern void fn_00462120(StrBuf *, void *);

void CError_BufferAppendTemplArgs(StrBuf *buf, char *args)
{
    if (!args) return;
    if (buf) CError_BufferPutChar(buf, '<');
    for (; args; args = *(char **)args) {
        switch ((UInt8)args[7]) {
            case 0:
                fn_0045f060(buf, *(void **)(args + 8), *(UInt32 *)(args + 12));
                break;
            case 1:
                fn_00462120(buf, *(void **)(args + 8));
                break;
            case 2:
                fn_0045f060(buf, *(void **)(args + 8), 0);
                break;
            default:
                CError_InternalImpl(CERROR_FILE, 0x245);
                break;
        }
        if (*(void **)args) CError_BufferAppendStringInline(buf, ", ");
    }
    if (buf) CError_BufferPutChar(buf, '>');
}

extern char *fn_0045da00(void *, void *, SInt32, SInt32);

void fn_0045be10(void)
{
    if (data_00717466 == 123) {
        do { fn_0045be40(); }
        while (data_00717466 != 0 && data_00717466 != 125);
    }
}

void CError_ErrorLTExp(SInt16 token, UInt8 argument)
{
    if (token == 91) CError_Error(10473);
    else if (argument) CError_Error(10474);
    else CError_Error(10230);
}

char *fn_0045d9e0(void *space, void *name)
{
    return fn_0045da00(space, name, 1, 0);
}

void CError_ObjectRedeclared(char *object, void *type, UInt32 qualifiers)
{
    char *name = CError_GetObjectName(object);
    struct GC3ErrorToken *token = (struct GC3ErrorToken *)(object + 0x24);
    if (token && token->words[0]) {
        cerror_lasterrorline = -1;
        CError_Error(10563, name, type, qualifiers);
        cerror_lasterrorline = -1;
        if (token && token && token->words[0]) cerror_locktoken = *token;
        CError_Error(10564, name, *(void **)(object + 0x10), *(UInt32 *)(object + 0x14));
    } else CError_Error(10249, name, *(void **)(object + 0x10),
                        *(UInt32 *)(object + 0x14), type, qualifiers);
}

void CError_ErrorTerm(SInt16 code)
{
    if (code < 10100 || code >= 10570) CError_InternalImpl(CERROR_FILE, 257);
    strcpy(error_message_buffer, cerror_errorstrings[code - 10100]);
    fn_0045d380(code, error_message_buffer, 0, 0);
    longjmp(error_jmp_buf, 1);
}

struct GC3ErrorTemplateStack {
    struct GC3ErrorTemplateStack *next;
    struct GC3ErrorToken token;
    void *value;
    UInt8 kind, point;
};
extern struct GC3ErrorTemplateStack *data_00716cf8;

void CError_BufferAppendTemplateStack(StrBuf *buf)
{
    struct GC3ErrorTemplateStack *stack[64], *p;
    SInt32 count, i, j;
    count = 0;
    p = data_00716cf8;
    while (p && count < 64) {
        stack[count++] = p;
        p = p->next;
    }
    for (i = count - 1; i >= 0; --i) {
        if (buf) CError_BufferPutChar(buf, '\n');
        for (j = i; j < count; ++j)
            if (buf) CError_BufferPutChar(buf, ' ');
        p = stack[i];
        if (p->point) CError_BufferAppendStringInline(buf, "(point of instantiation: '");
        else CError_BufferAppendStringInline(buf, "(instantiating: '");
        if (p->kind) {
            if (p->value) fn_0045e350(buf, p->value);
            else CError_BufferAppendStringInline(buf, "global scope");
        } else fn_0045f060(buf, p->value, 0);
        CError_BufferAppendStringInline(buf, "')");
    }
}

void CError_AppendObjectName(StrBuf *buf, char *object)
{
    char *type, *extension;
    SInt32 has_template_args;
    if (object) {
        type = *(char **)(object + 0x10);
        if ((UInt8)type[0] == 7) {
            extension = *(char **)(object + 0x48);
            has_template_args = extension && (UInt8)object[2] != 5;
            fn_0045e5a0(buf, *(void **)(object + 8), *(void **)(object + 12),
                        (SInt32)object, has_template_args ? *(SInt32 *)(extension + 8) : 0, (UInt32)type);
            if (*(UInt32 *)(*(char **)(object + 0x10) + 0x16) & 0x8000)
                CError_BufferAppendStringInline(buf, " const");
            if (*(UInt32 *)(*(char **)(object + 0x10) + 0x16) & 0x10000)
                CError_BufferAppendStringInline(buf, " volatile");
        } else {
            fn_00461c60(buf, *(void **)(object + 8), 1);
            CError_BufferAppendStringInline(buf, *(char **)(object + 12) + 10);
        }
    } else CError_BufferAppendStringInline(buf, "unknown object/init code");
}

extern UInt8 data_0070f1ee;
void CError_BufferAppendPType(StrBuf *, char *);

static inline const char *CError_ReferenceSpelling(char *type)
{
    if (data_0070f1ee && (UInt8)type[0] == 12 &&
        (*(UInt32 *)(type + 10) & 0xa0) == 0xa0) return "&&";
    return "&";
}

static inline void CError_BufferAppendPTypeNested(StrBuf *buf, char *type)
{
    switch ((SInt8)type[0]) {
        case 12:
            CError_BufferAppendPType(buf, *(char **)(type + 6));
            if (*(UInt32 *)(type + 10) & 0x20)
                CError_BufferAppendString(buf, CError_ReferenceSpelling(type));
            else CError_BufferAppendString(buf, "*");
            CError_BufferAppendQualifier(buf, *(UInt32 *)(type + 10));
            return;
        case 11:
            CError_BufferAppendPType(buf, *(char **)(type + 6));
            fn_0045f060(buf, *(void **)(type + 10), 0);
            CError_BufferAppendString(buf, "::*");
            CError_BufferAppendQualifier(buf, *(UInt32 *)(type + 14));
            return;
    }
}

void CError_BufferAppendPType(StrBuf *buf, char *type)
{
    switch ((SInt8)type[0]) {
        case 12:
            CError_BufferAppendPTypeNested(buf, *(char **)(type + 6));
            if (*(UInt32 *)(type + 10) & 0x20)
                CError_BufferAppendStringInline(buf, CError_ReferenceSpelling(type));
            else CError_BufferAppendStringInline(buf, "*");
            CError_BufferAppendQualifier(buf, *(UInt32 *)(type + 10));
            return;
        case 11:
            CError_BufferAppendPTypeNested(buf, *(char **)(type + 6));
            fn_0045f060(buf, *(void **)(type + 10), 0);
            CError_BufferAppendStringInline(buf, "::*");
            CError_BufferAppendQualifier(buf, *(UInt32 *)(type + 14));
            return;
    }
}

struct GC3ErrorObjectList {
    struct GC3ErrorObjectList *next;
    void *object;
};
struct GC3ErrorCandidateSet {
    struct GC3ErrorObjectList *objects;
    void *object;
};
extern void fn_0045ab40(SInt16, struct GC3ErrorCandidateSet *, void *, void *);

void fn_0045aae0(void *object, struct GC3ErrorObjectList *list, void *type, void *args)
{
    struct GC3ErrorCandidateSet set;
    struct GC3ErrorObjectList **tail;
    set.object = object;
    tail = &set.objects;
    for (; list; list = list->next) {
        *tail = lalloc(sizeof(struct GC3ErrorObjectList));
        (*tail)->object = list->object;
        tail = &(*tail)->next;
    }
    *tail = 0;
    fn_0045ab40(10392, &set, type, args);
}

void CError_ErrorSemantic(SInt32 code, ...)
{
    char format[256], buffer[256];
    char *args, *message;
    SInt32 diagnosticID;
    if (data_0071035c) return;
    GC3_VA_START(args, code);
    diagnosticID = code;
    if (diagnosticID < 10100 || diagnosticID >= 10570) CError_InternalImpl(CERROR_FILE, 257);
    strcpy(format, cerror_errorstrings[diagnosticID - 10100]);
    message = fn_0045c650(buffer, 256, format, args);
    fn_0045d380(diagnosticID, message, 0, 0);
    if (data_00725f3f && !data_00725ffe) fn_0055eba0();
}

void fn_00460bb0(StrBuf *buf, void *class_type)
{
    char *type = class_type;
    void *args;
    if (*(UInt32 *)(type + 0x22) & 0x100000)
        CError_BufferAppendStringInline(buf, *(char **)(*(char **)(type + 6) + 4) + 10);
    else if (*(void **)(type + 10)) {
        CError_BufferAppendStringInline(buf, *(char **)(type + 10) + 10);
        if (*(UInt32 *)(type + 0x22) & 0x800) {
            args = *(void **)(fn_0053ed70(type) + 0x44);
            if (!args) args = *(void **)(fn_0053ed70(type) + 0x3c);
            fn_00461e80(buf, args);
        }
    } else CError_BufferAppendStringInline(buf, "{unnamed-class}");
}

struct GC3ErrorExceptionType {
    struct GC3ErrorExceptionType *next;
    void *type;
    UInt32 qualifiers;
};

void fn_00460fc0(StrBuf *buf, void *exceptions)
{
    struct GC3ErrorExceptionType *node = exceptions;
    if (node) {
        CError_BufferAppendStringInline(buf, "throw(");
        if (node->type) {
            for (;;) {
                fn_0045f060(buf, node->type, node->qualifiers);
                node = node->next;
                if (!node) break;
                CError_BufferAppendStringInline(buf, ", ");
            }
        }
        CError_BufferAppendStringInline(buf, ")");
    }
}

extern UInt8 data_0070f1f6;

void fn_0045d5c0(SInt32 mode)
{
    char position[276], text[128];
    struct GC3ErrorTemplateStack *head, *p;
    void *last_object, *last_type;
    if (data_0070f1f6 && !data_00725e6c && (head = data_00716cf8)) {
        fn_00459d70(data_0071079c, 0);
        last_object = last_type = 0;
        p = head;
        data_00716cf8 = 0;
        while (p) {
            if (&p->token && p->token.words[0] &&
                fn_004d5e80(position, text, 128, &p->token, 0, 0, 0)) {
                if (last_object) fn_00459200(data_0071079c, 0, position, text, 10544, last_object);
                else if (last_type) fn_00459200(data_0071079c, 0, position, text, 10543, last_type, 0);
                else fn_00459200(data_0071079c, 0, position, text, 10542);
            }
            if (p->kind) { last_object = p->value; last_type = 0; }
            else { last_object = 0; last_type = p->value; }
            p = p->next;
        }
        data_00716cf8 = head;
    }
}

extern UInt8 data_00725e59;
extern SInt16 fn_00447a30(void);

void fn_0045be40(void)
{
    SInt16 closers[8];
    UInt32 depth = 0;
    UInt8 saved = data_00725e59;
    data_00725e59 = 1;
    if (data_00717466 == 40 || data_00717466 == 123 || data_00717466 == 91)
        closers[depth++] = data_00717466 == 40 ? 41 : data_00717466 == 123 ? 125 : 93;
    while (data_00717466) {
        data_00717466 = fn_00447b70();
        if (data_00717466 == -7 && fn_00447a30() == -7) break;
        if (!depth && (data_00717466 == 44 || data_00717466 == 41 ||
            data_00717466 == 125 || data_00717466 == 93 ||
            data_00717466 == 59 || data_00717466 == 328)) break;
        if ((SInt32)depth > 0 && data_00717466 == closers[depth - 1]) {
            if (!--depth) {
                data_00717466 = fn_00447b70();
                break;
            }
        } else if (depth < 8 && (data_00717466 == 40 || data_00717466 == 123 || data_00717466 == 91))
            closers[depth++] = data_00717466 == 40 ? 41 : data_00717466 == 123 ? 125 : 93;
    }
    data_00725e59 = saved;
}

void CError_ErrorSkip(SInt32 code, ...)
{
    char format[256], buffer[256];
    char *args, *message;
    SInt32 diagnosticID;
    if (data_0071035c) longjmp(*(jmp_buf *)((char *)data_0071035c + 4), 1);
    GC3_VA_START(args, code);
    diagnosticID = code;
    if (diagnosticID < 10100 || diagnosticID >= 10570) CError_InternalImpl(CERROR_FILE, 257);
    strcpy(format, cerror_errorstrings[diagnosticID - 10100]);
    message = fn_0045c650(buffer, 256, format, args);
    fn_0045d380(diagnosticID, message, 0, 0);
    if (data_00717466 != 59 && data_00717466 != 0 && data_00717466 != 41 &&
        data_00717466 != 125 && data_00717466 != 44 && data_00717466 != 93)
        data_00717466 = fn_00447b70();
}

struct GC3ErrorFunctionArg {
    struct GC3ErrorFunctionArg *next;
    void *unused[2];
    void *type;
    UInt32 qualifiers;
};
extern struct GC3ErrorFunctionArg data_007037c0, data_0070bb08;
extern struct GC3ErrorFunctionArg *fn_00553440(void *);

void CError_BufferAppendFuncArgs(StrBuf *buf, char *type, UInt8 implicit)
{
    struct GC3ErrorFunctionArg *arg;
    UInt32 qualifiers = 0;
    if (buf) CError_BufferPutChar(buf, '(');
    arg = *(struct GC3ErrorFunctionArg **)(type + 6);
    if (arg) {
        if (implicit) {
            qualifiers = arg->qualifiers;
            arg = arg->next;
            if (arg) arg = arg->next;
        } else if (*(UInt32 *)(type + 0x16) & 0x10) arg = fn_00553440(type);
        while (arg) {
            if (arg == &data_007037c0 || arg == &data_0070bb08) {
                CError_BufferAppendStringInline(buf, "...");
                break;
            }
            fn_0045f060(buf, arg->type, arg->qualifiers);
            arg = arg->next;
            if (arg) CError_BufferAppendStringInline(buf, ", ");
        }
    }
    if (buf) CError_BufferPutChar(buf, ')');
    if (qualifiers) CError_BufferAppendQualifier(buf, qualifiers);
}

void fn_0045d870(void *space, char *name, char *type)
{
    StrBuf buf;
    char buffer[256];
    char *message = 0;
    if (space) {
        if (type && (UInt8)type[0] == 7) {
            CError_BufferInit(&buf, buffer, sizeof(buffer));
            fn_0045e5a0(&buf, space, name, 0, 0, (UInt32)type);
            CError_BufferTerminate(&buf);
            if (buf.start == buffer) message = strcpy(lalloc(buf.size + 1), buf.start);
            else message = buf.start;
        } else if (!type && space) message = fn_0045da00(space, name, 1, 0);
    }
    CError_Error(10140, message ? message : name + 10);
}

extern void *data_00711b28, *data_007107d0;
extern char *fn_00558760(void *);
extern void fn_0045eab0(StrBuf *, void *, void *, void *);
extern char *fn_0053ec70(void *);
extern void fn_0045e7d0(StrBuf *, char *);

void CError_AppendUnqualFunctionName(StrBuf *buf, struct GC3ErrorNameSpace *space, char *name, char *type)
{
    char *text;
    UInt8 done = 0;
    if (space && space->theclass) {
        if (name == data_00711b28) {
            CError_BufferAppendStringInline(buf, *(char **)(space->theclass + 10) + 10);
            done = 1;
        } else if (name == data_007107d0) {
            if (buf) CError_BufferPutChar(buf, '~');
            CError_BufferAppendStringInline(buf, *(char **)(space->theclass + 10) + 10);
            done = 1;
        }
    }
    if (!done) {
        text = fn_00558760(name);
        if (text) CError_BufferAppendStringInline(buf, text);
        else if (type && (*(UInt32 *)(type + 0x16) & 0x40)) {
            CError_BufferAppendStringInline(buf, "operator ");
            fn_0045f060(buf, *(void **)(type + 14), *(UInt32 *)(type + 18));
        } else CError_BufferAppendStringInline(buf, name + 10);
    }
}

void CError_AppendFunctionName(StrBuf *buf, struct GC3ErrorNameSpace *space,
                             void *name, void *object, void *args, char *type)
{
    while (*((UInt8 *)space + 31) && space->parent) space = space->parent;
    fn_00461c60(buf, space, 1);
    fn_0045eab0(buf, space, name, type);
    fn_00461e80(buf, args);
    if (type) {
        if (*(UInt32 *)(type + 0x16) & 0x100000) {
            if (buf) CError_BufferPutChar(buf, '<');
            if (object) fn_0045e7d0(buf, *(void **)(fn_0053ec70(object) + 8));
            if (buf) CError_BufferPutChar(buf, '>');
        }
        CError_BufferAppendFuncArgs(buf, type, 0);
    } else CError_BufferAppendStringInline(buf, "()");
    if (*(void **)(type + 10)) {
        if (buf) CError_BufferPutChar(buf, ' ');
        fn_00460fc0(buf, *(void **)(type + 10));
    }
}

void fn_0045e7d0(StrBuf *buf, char *param)
{
    SInt32 index;
    char text[64];
    if (param) {
        index = 0;
        for (;;) {
            switch ((UInt8)param[11]) {
                case 0:
                    sprintf(text, "typename __T%ld", index);
                    CError_BufferAppendStringInline(buf, text);
                    break;
                case 1:
                    fn_0045f060(buf, *(void **)(param + 12), *(UInt32 *)(param + 16));
                    break;
                case 2:
                    sprintf(text, "template<typename T> class __T%ld", index);
                    CError_BufferAppendStringInline(buf, text);
                    break;
                default: CError_InternalImpl(CERROR_FILE, 0x509); break;
            }
            param = *(char **)param;
            if (!param) break;
            CError_BufferAppendStringInline(buf, ", ");
            ++index;
        }
    }
}

void CError_BufferAppendTemplDepType(StrBuf *buf, char *node)
{
    char temp[64], temp2[64];
    switch ((UInt8)node[6]) {
        case 0:
            if ((UInt8)node[10]) sprintf(temp, "__T%ld_%ld", (UInt8)node[10], *(UInt16 *)(node + 8));
            else sprintf(temp, "__T%ld", *(UInt16 *)(node + 8));
            CError_BufferAppendStringInline(buf, temp);
            break;
        case 11:
            if ((UInt8)node[10]) sprintf(temp2, "__T%ld_%ld", (UInt8)node[10], *(UInt16 *)(node + 8));
            else sprintf(temp2, "__T%ld", *(UInt16 *)(node + 8));
            CError_BufferAppendStringInline(buf, temp2);
            break;
        case 1:
            CError_BufferAppendTemplDepType(buf, *(char **)(node + 8));
            CError_BufferAppendStringInline(buf, "::");
            CError_BufferAppendStringInline(buf, *(char **)(node + 12) + 10);
            break;
        case 2:
            fn_0045f060(buf, *(void **)(node + 8), 0);
            fn_00461e80(buf, *(void **)(node + 12));
            break;
        case 3:
            fn_0045f060(buf, *(void **)(node + 8), 0);
            if (buf) CError_BufferPutChar(buf, '[');
            fn_00462120(buf, *(void **)(node + 12));
            if (buf) CError_BufferPutChar(buf, ']');
            break;
        case 4:
            CError_BufferAppendTemplDepType(buf, *(char **)(node + 8));
            fn_00461e80(buf, *(void **)(node + 12));
            break;
        case 5:
        case 6:
            fn_0045f060(buf, *(void **)(node + 8), 0);
            if (buf) CError_BufferPutChar(buf, '[');
            fn_00462120(buf, *(void **)(node + 12));
            if (buf) CError_BufferPutChar(buf, ']');
            break;
        case 7:
            fn_0045f060(buf, *(void **)(node + 8), 0);
            break;
        case 8:
            CError_BufferAppendStringInline(buf, "<dep-enum-value>");
            break;
        case 9:
            CError_BufferAppendStringInline(buf, "__typeof__(");
            fn_00462120(buf, *(void **)(node + 8));
            if (buf) CError_BufferPutChar(buf, ')');
            break;
        case 10:
            CError_BufferAppendStringInline(buf, "__decltype__(");
            fn_00462120(buf, *(void **)(node + 8));
            if (buf) CError_BufferPutChar(buf, ')');
            break;
        default:
            CError_InternalImpl(CERROR_FILE, 0x2f1);
            break;
    }
}

extern char data_00699c1c[];
extern void fn_004d8810(char *, UInt32, UInt32);

void CError_BufferAppendTemplArgExpr(StrBuf *buf, char *node)
{
    char number[64], parameter[64];
    char *symbol, *owner;
    if (node) {
        switch ((UInt8)node[0]) {
            case 52:
                if (*(void **)(node + 4) != data_00699c1c) {
                    fn_004d8810(number, *(UInt32 *)(node + 16), *(UInt32 *)(node + 20));
                    CError_BufferAppendStringInline(buf, number);
                } else {
                    CError_BufferAppendStringInline(buf,
                        (*(UInt32 *)(node + 16) || *(UInt32 *)(node + 20)) ? "true" : "false");
                }
                return;
            case 59:
            case 82:
                if (buf) CError_BufferPutChar(buf, '&');
                fn_0045e350(buf, *(void **)(node + 16));
                return;
            case 75:
                if (buf) CError_BufferPutChar(buf, '&');
                symbol = *(char **)(*(char **)(node + 16) + 4);
                switch ((UInt8)symbol[0]) {
                    case 4:
                        owner = *(char **)(node + 20);
                        if (!owner) CError_InternalImpl(CERROR_FILE, 0x1e2);
                        fn_0045f060(buf, owner, 0);
                        CError_BufferAppendStringInline(buf, "::");
                        CError_BufferAppendStringInline(buf, *(char **)(*(char **)(*(char **)(node + 16) + 4) + 8) + 10);
                        return;
                    case 5:
                        switch ((UInt8)symbol[2]) {
                            case 0:
                            case 3:
                            case 4:
                                fn_0045e350(buf, symbol);
                                return;
                            default: CError_InternalImpl(CERROR_FILE, 0x1f2); break;
                        }
                        break;
                }
                break;
            case 76:
                switch ((UInt8)node[44]) {
                    case 0:
                        if ((UInt8)node[18])
                            sprintf(parameter, "__T%ld_%ld", (UInt8)node[18], *(UInt16 *)(node + 16));
                        else sprintf(parameter, "__T%ld", *(UInt16 *)(node + 16));
                        CError_BufferAppendStringInline(buf, parameter);
                        return;
                    case 3:
                        CError_BufferAppendTemplDepType(buf, *(char **)(node + 16));
                        CError_BufferAppendStringInline(buf, "::");
                        CError_BufferAppendStringInline(buf, *(char **)(node + 20) + 10);
                        return;
                }
                break;
        }
    }
    CError_BufferAppendStringInline(buf, "{targ_expr}");
}

void CError_OverloadedFunctionError(Object *name, struct MatchLink *names)
{
    StrBuf message;
    char buffer[256];
    char *link = (char *)names;
    if (data_0071035c) longjmp(*(jmp_buf *)((char *)data_0071035c + 4), 1);
    strcpy(error_message_buffer, cerror_errorstrings[99]);
    CError_BufferInit(&message, buffer, sizeof(buffer));
    CError_BufferPutString(&message, error_message_buffer);
    if (name) {
        CError_BufferPutChar(&message, '\n');
        CError_BufferPutChar(&message, '\'');
        fn_0045e350(&message, name);
        CError_BufferPutChar(&message, '\'');
    }
    while (link) {
        CError_BufferPutChar(&message, '\n');
        CError_BufferPutChar(&message, '\'');
        fn_0045e350(&message, *(void **)(link + 4));
        CError_BufferPutChar(&message, '\'');
        link = *(char **)link;
    }
    fn_0045d010(&message);
    CError_BufferTerminate(&message);
    fn_0045d380(10199, message.start, 0, 0);
}

char *fn_0045da00(void *rawspace, void *rawname, SInt32 qualified, SInt32 force)
{
    struct GC3ErrorNameSpace *space = rawspace, *enclosing;
    char *name = rawname, *text;
    const char *prefix = emptystring;
    char buffer[256];
    StrBuf buf;
    if (!name) CError_InternalImpl(CERROR_FILE, 0x5cd);
    if (name == data_00711b28) {
        enclosing = space;
        while (enclosing && !enclosing->theclass) enclosing = enclosing->parent;
        if (!enclosing) CError_InternalImpl(CERROR_FILE, 0x5c4);
        text = *(char **)(enclosing->theclass + 10) + 10;
    } else if (name == data_007107d0) {
        enclosing = space;
        while (enclosing && !enclosing->theclass) enclosing = enclosing->parent;
        if (!enclosing) CError_InternalImpl(CERROR_FILE, 0x5c4);
        text = *(char **)(enclosing->theclass + 10) + 10;
        prefix = "~";
    } else {
        text = fn_00558760(name);
        if (!text) text = name + 10;
    }
    if (space && ((UInt8)force || space->name)) {
        CError_BufferInit(&buf, buffer, sizeof(buffer));
        fn_00461c60(&buf, space, (UInt8)qualified);
        CError_BufferPutString(&buf, prefix);
        CError_BufferPutString(&buf, text);
        CError_BufferTerminate(&buf);
        if (buf.start == buffer) buf.start = strcpy(lalloc(buf.size + 1), buf.start);
        return buf.start;
    }
    return text;
}

extern UInt8 data_0070f1a8;
extern UInt8 fn_00559680(void *);
extern char *fn_00543680(void *, SInt32, SInt32, SInt32, SInt32);

void CError_ErrorFuncCall(SInt16 code, struct GC3ErrorCandidateSet *candidates,
                         void *rawtype, void *rawargs)
{
    StrBuf message;
    char buffer[256], *format, *object, *type, *expr, *resolved;
    struct GC3ErrorObjectList *names = (void *)candidates, *arg, *overloads;
    char *receiver = rawtype;
    struct GC3ErrorObjectList *args = rawargs;
    UInt8 first;
    if (data_0071035c) longjmp(*(jmp_buf *)((char *)data_0071035c + 4), 1);
    if (code < 10100 || code >= 10570) CError_InternalImpl(CERROR_FILE, 0x101);
    strcpy(error_message_buffer, cerror_errorstrings[code - 10100]);
    CError_BufferInit(&message, buffer, sizeof(buffer));
    while (names && *(UInt8 *)names->object != 5) names = names->next;
    if (!names) { CError_Error(10161); return; }
    for (format = error_message_buffer; *format; ++format) {
        if (*format != '*') { CError_BufferPutChar(&message, *format); continue; }
        if (receiver) {
            CError_BufferPutString(&message, "[");
            fn_0045f060(&message, *(void **)(receiver + 4),
                        *(UInt32 *)(receiver + 8) & 0x1f200003);
            CError_BufferPutString(&message, "].");
        }
        object = names->object;
        type = *(char **)(object + 16);
        if ((UInt8)*type == 7) fn_0045eab0(&message, *(void **)(object + 8),
                                         *(void **)(object + 12), type);
        else CError_BufferPutString(&message, *(char **)(object + 12) + 10);
        type = *(char **)((char *)names->object + 16);
        if ((*(UInt32 *)(type + 22) & 0x10) &&
            (*(UInt32 *)(type + 22) & 0x1000) &&
            (*(UInt32 *)(*(char **)(type + 30) + 34) & 0x20) && args)
            args = args->next;
        CError_BufferPutChar(&message, '(');
        for (arg = args; arg; arg = arg->next) {
            expr = arg->object;
            if ((UInt8)*expr == 75) {
                overloads = *(void **)(expr + 16);
                if (overloads && !*(void **)(expr + 36)) {
                    if (!overloads->next && (UInt8)expr[41] &&
                        ((UInt8)*(char *)overloads->object == 4 ||
                         (UInt8)*(char *)overloads->object == 5)) {
                        expr[42] = ((UInt8)expr[42] & 0xfd) | 2;
                        ((char *)arg->object)[40] = 1;
                        resolved = fn_00543680(arg->object, 0, 0, 0, 0);
                        fn_0045f060(&message, *(void **)(resolved + 4),
                                    *(UInt32 *)(resolved + 8) & 0x1f200003);
                    } else {
                        first = 1;
                        for (; overloads; overloads = overloads->next) {
                            if (*(UInt8 *)overloads->object == 5) {
                                if (first) {
                                    CError_BufferPutString(&message, "&{ ");
                                    first = 0;
                                } else CError_BufferPutString(&message, ", ");
                                fn_0045e350(&message, overloads->object);
                            }
                        }
                        if (!first) CError_BufferPutString(&message, " }");
                        else CError_BufferPutString(&message, "<unknown type>");
                    }
                } else CError_BufferPutString(&message, "<unknown type>");
            } else {
                if (data_0070f1a8 && fn_00559680(arg->object))
                    CError_BufferPutString(&message, "{lval} ");
                expr = arg->object;
                fn_0045f060(&message, *(void **)(expr + 4),
                            *(UInt32 *)(expr + 8) & 0x1f200003);
            }
            if (arg->next) CError_BufferPutString(&message, ", ");
        }
        CError_BufferPutChar(&message, ')');
    }
    for (; names; names = names->next) {
        object = names->object;
        if ((UInt8)*object == 5) {
            CError_BufferPutChar(&message, '\n');
            CError_BufferPutChar(&message, '\'');
            fn_0045e350(&message, names->object);
            CError_BufferPutChar(&message, '\'');
            object = names->object;
            type = *(char **)(object + 16);
            if ((UInt8)*type == 7 && (*(UInt32 *)(type + 22) & 0x10) &&
                !(*(UInt32 *)(type + 22) & 0x3000)) {
                if ((UInt8)type[42]) CError_BufferPutString(&message, " (static)");
                else CError_BufferPutString(&message, " (non-static)");
            }
            if (*(UInt32 *)((char *)names->object + 20) & 0x40)
                CError_BufferPutString(&message, " (explicit)");
        }
    }
    fn_0045d010(&message);
    CError_BufferTerminate(&message);
    fn_0045d380(code, message.start, 0, 0);
}

extern char *data_0070f520;

void CError_BufferAppendType(StrBuf *buf, char *type, UInt32 qualifiers)
{
    char *base, *array, *name;
    SInt32 stype;
    char text[16];
    switch ((SInt8)*type) {
        case -1:
            CError_BufferAppendStringInline(buf, "<unknown-type>");
            return;
        case 0:
            CError_BufferAppendQualifier(buf, qualifiers);
            CError_BufferAppendStringInline(buf, "void");
            return;
        case 1:
        case 2:
        case 3:
            CError_BufferAppendQualifier(buf, qualifiers);
            switch ((UInt8)type[6]) {
                case 0: CError_BufferAppendStringInline(buf, "bool"); return;
                case 1: CError_BufferAppendStringInline(buf, "char"); return;
                case 3: CError_BufferAppendStringInline(buf, "unsigned char"); return;
                case 2: CError_BufferAppendStringInline(buf, "signed char"); return;
                case 4: CError_BufferAppendStringInline(buf, "wchar_t"); return;
                case 5: CError_BufferAppendStringInline(buf, "short"); return;
                case 6: CError_BufferAppendStringInline(buf, "unsigned short"); return;
                case 7: CError_BufferAppendStringInline(buf, "int"); return;
                case 8: CError_BufferAppendStringInline(buf, "unsigned int"); return;
                case 9: CError_BufferAppendStringInline(buf, "long"); return;
                case 10: CError_BufferAppendStringInline(buf, "unsigned long"); return;
                case 11: CError_BufferAppendStringInline(buf, "long long"); return;
                case 12: CError_BufferAppendStringInline(buf, "unsigned long long"); return;
                case 13: CError_BufferAppendStringInline(buf, "float"); return;
                case 14: CError_BufferAppendStringInline(buf, "short double"); return;
                case 15: CError_BufferAppendStringInline(buf, "double"); return;
                case 16: CError_BufferAppendStringInline(buf, "long double"); return;
                case 17: CError_BufferAppendStringInline(buf, "_Imaginary float"); return;
                case 18: CError_BufferAppendStringInline(buf, "_Imaginary double"); return;
                case 19: CError_BufferAppendStringInline(buf, "_Imaginary long double"); return;
                case 20: CError_BufferAppendStringInline(buf, "_Complex float"); return;
                case 21: CError_BufferAppendStringInline(buf, "_Complex double"); return;
                case 22: CError_BufferAppendStringInline(buf, "_Complex long double"); return;
                case 25: CError_BufferAppendStringInline(buf, data_0070f520); return;
                default: CError_InternalImpl(CERROR_FILE, 0x3a2); break;
            }
            break;
        case 4:
            CError_BufferAppendQualifier(buf, qualifiers);
            fn_00461c60(buf, *(void **)(type + 6), 1);
            if (*(char **)(type + 18)) {
                name = *(char **)(type + 18) + 10;
                CError_BufferAppendStringInline(buf, name);
            } else CError_BufferAppendStringInline(buf, "{unnamed-enum}");
            return;
        case 5:
            CError_BufferAppendQualifier(buf, qualifiers);
            stype = (SInt8)type[16];
            switch (stype) {
                case 0: CError_BufferAppendStringInline(buf, "struct "); break;
                case 1: CError_BufferAppendStringInline(buf, "union "); break;
                default:
                    if (stype < 15) break;
                case 15:
                    CError_InternalImpl(CERROR_FILE, 0x3c5); break;
            }
            if (*(char **)(type + 6)) {
                name = *(char **)(type + 6) + 10;
                CError_BufferAppendStringInline(buf, name);
            }
            return;
        case 6:
            CError_BufferAppendQualifier(buf, qualifiers);
            if (*(char **)(type + 6)) fn_00461c60(buf, **(void ***)(type + 6), 1);
            fn_00460bb0(buf, type);
            return;
        case 11:
        case 12:
            base = type;
            for (;;) {
                switch ((SInt8)*base) {
                    case 12: base = *(char **)(base + 6); continue;
                    case 11: base = *(char **)(base + 6); continue;
                }
                break;
            }
            CError_BufferAppendQualifier(buf, qualifiers);
            switch ((SInt8)*base) {
                case 7:
                    if (*(UInt32 *)(base + 22) & 1) CError_BufferAppendStringInline(buf, "pascal ");
                    if (!(*(UInt32 *)(base + 22) & 0x40000000) && data_0070f1a8)
                        CError_BufferAppendStringInline(buf, "extern \"C\" ");
                    CError_BufferAppendType(buf, *(void **)(base + 14), *(UInt32 *)(base + 18));
                    CError_BufferAppendStringInline(buf, " (");
                    CError_BufferAppendPType(buf, type);
                    if (buf) CError_BufferPutChar(buf, ')');
                    CError_BufferAppendFuncArgs(buf, base, (UInt8)*type == 11);
                    if (*(void **)(base + 10)) {
                        if (buf) CError_BufferPutChar(buf, ' ');
                        fn_00460fc0(buf, *(void **)(base + 10));
                    }
                    return;
                case 13:
                    array = base;
                    while ((SInt8)*base == 13) base = *(char **)(base + 6);
                    CError_BufferAppendType(buf, base, 0);
                    CError_BufferAppendStringInline(buf, " (");
                    CError_BufferAppendPType(buf, type);
                    if (buf) CError_BufferPutChar(buf, ')');
                    type = array;
                    break;
                default:
                    CError_BufferAppendType(buf, base, 0);
                    if (buf) CError_BufferPutChar(buf, ' ');
                    CError_BufferAppendPType(buf, type);
                    return;
            }
            goto arrays;
        case 7:
            if (*(UInt32 *)(type + 22) & 1) CError_BufferAppendStringInline(buf, "pascal ");
            if (!(*(UInt32 *)(type + 22) & 0x40000000) && data_0070f1a8)
                CError_BufferAppendStringInline(buf, "extern \"C\" ");
            CError_BufferAppendQualifier(buf, qualifiers);
            CError_BufferAppendType(buf, *(void **)(type + 14), *(UInt32 *)(type + 18));
            if (buf) CError_BufferPutChar(buf, ' ');
            CError_BufferAppendFuncArgs(buf, type, 0);
            if (*(UInt32 *)(type + 22) & 0x8000) CError_BufferAppendStringInline(buf, "const ");
            if (*(UInt32 *)(type + 22) & 0x10000) CError_BufferAppendStringInline(buf, "volatile ");
            if (*(SInt32 *)(type + 10)) goto function_exceptions;
function_done:
            return;
        case 13:
            CError_BufferAppendQualifier(buf, qualifiers);
            for (base = type; (SInt8)*base == 13; base = *(char **)(base + 6)) {}
            CError_BufferAppendType(buf, base, 0);
arrays:
            while ((SInt8)*type == 13) {
                if (buf) CError_BufferPutChar(buf, '[');
                if ((UInt8)type[18] && !(UInt8)type[19]) {
                    if (buf) CError_BufferPutChar(buf, '*');
                } else if (*(SInt32 *)(type + 14)) {
                    sprintf(text, "%ld", *(SInt32 *)(type + 14));
                    CError_BufferAppendStringInline(buf, text);
                }
                if (buf) CError_BufferPutChar(buf, ']');
                type = *(char **)(type + 6);
            }
            return;
        case 10:
            CError_BufferAppendQualifier(buf, qualifiers);
            CError_BufferAppendTemplDepType(buf, type);
            return;
        case 15:
            CError_BufferAppendStringInline(buf, "__T?");
            return;
        case 8:
            sprintf(text, "bitfield:%ld", (UInt8)type[11]);
            CError_BufferAppendStringInline(buf, text);
            return;
        case -2:
        default:
            CError_InternalImpl(CERROR_FILE, 0x461);
            return;
    }
    return;
function_exceptions:
    fn_00460fc0(buf, *(void **)(type + 10));
    if (buf) CError_BufferPutChar(buf, ' ');
    goto function_done;
}
