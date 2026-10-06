#ifndef RUNTIME_EXCEPTIONTABLES_H
#define RUNTIME_EXCEPTIONTABLES_H

#include "compiler/win32.h"

struct ExceptionInfo {
    DWORD code;
    DWORD flags;
};
typedef struct ExceptionInfo ExceptionInfo;
struct RuntimeCallEntry {
    char *instruction;
    unsigned int value;
};
typedef struct RuntimeCallEntry RuntimeCallEntry;
struct RuntimeLookupResult {
    struct RuntimeRecord *record;
    unsigned int reserved;
    unsigned int value;
};
typedef struct RuntimeLookupResult RuntimeLookupResult;
struct RuntimeRangeEntry {
    char *address;
    struct RuntimeRecord *record;
};
typedef struct RuntimeRangeEntry RuntimeRangeEntry;
#pragma pack(push, 1)
struct RuntimeRecord {
    signed char flags;
    unsigned int value;
    unsigned short call_count;
    RuntimeCallEntry calls[1];
};
typedef struct RuntimeRecord RuntimeRecord;
#pragma pack(pop)
struct X86FloatingPointState {
    DWORD controlWord;
    DWORD statusWord;
    DWORD tagWord;
    DWORD errorOffset;
    DWORD errorSelector;
    DWORD dataOffset;
    DWORD dataSelector;
    unsigned char registers[80];
    DWORD cr0NpxState;
};
typedef struct X86FloatingPointState X86FloatingPointState;
struct X86ThreadContext {
    DWORD flags;
    DWORD dr0, dr1, dr2, dr3, dr6, dr7;
    X86FloatingPointState floatingPoint;
    DWORD gs, fs, es, ds;
    DWORD edi, esi, ebx, edx, ecx, eax;
    DWORD ebp;
    DWORD eip;
};
typedef struct X86ThreadContext X86ThreadContext;
struct _NODE {
    struct RuntimeRangeEntry *begin;
    struct RuntimeRangeEntry *end;
    struct _NODE *next;
};
typedef struct _NODE NODE;
typedef struct _NODE _NODE;
extern char data_00536030[];
extern struct _NODE *data_0057d000;
extern int data_0057d004;
extern char data_0057d008;
extern unsigned int _MWCHandler(ExceptionInfo *record, int frame, X86ThreadContext *context);
extern void __cdecl _RegisterExceptionTables(NODE *node);
extern void lookup_runtime_record_and_call_value(char *address, RuntimeLookupResult *result);

#endif
