#ifndef DRIVER_TARGETOPTIMIZER_PPC_EABI_H
#define DRIVER_TARGETOPTIMIZER_PPC_EABI_H

#include <setjmp.h>
#include "compiler/common.h"
#include "compiler/win32.h"
#include "driver/Memory.h"
#include "driver/MsDos.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OperationRecord {
    OSSpec fileSpec;
    struct MemBuffer buffer;
    unsigned char loaded;
    unsigned char dirty;
    unsigned char writeBack;
};
extern void fn_00420700(void);
extern unsigned int fn_00420710(OperationRecord *context);
extern DWORD write_file_buffer(struct OperationRecord *file);
extern unsigned int __stdcall TargetOptimizer_ppc_eabi_InitOperationRecord(OSSpec *source, MemBuffer *argument,
                                                                           unsigned char flag, OperationRecord *state);
extern int __stdcall TargetOptimizer_ppc_eabi_GetMemBufferPtrAndSize(unsigned char *state, char **firstResult,
                                                                     int *secondResult);
extern unsigned int __stdcall TargetOptimizer_ppc_eabi_UnloadOperationRecord(struct OperationRecord *record);
extern int TargetOptimizer_ppc_eabi_SetOption(short a0, char a1);
extern char data_00537a60;
extern char data_00537a63;
extern unsigned int TargetOptimizer_ppc_eabi_ReportScheduling(struct StorageHandle *argument);
extern short data_00537a68;
extern unsigned char generic_ppc_message[];
extern unsigned char data_0054c5d0[];
extern unsigned char data_0054c5d4[];
extern unsigned char data_0054c5d8[];
extern unsigned char data_0054c5dc[];
extern unsigned char data_0054c5e0[];
extern unsigned char data_0054c5e4[];
extern unsigned char data_0054c5e8[];
extern unsigned char data_0054c5ec[];
extern unsigned char data_0054c5f0[];
extern unsigned char data_0054c5f8[];
extern unsigned char data_0054c5fc[];
extern unsigned char data_0054c604[];
extern unsigned char data_0054c608[];
extern unsigned char data_0054c60c[];
extern unsigned char data_0054c610[];
extern unsigned char data_0054c614[];
extern unsigned char data_0054c618[];
extern unsigned char data_0054c61c[];
extern signed char data_0054c624[];
extern unsigned char data_0054c628[];

#ifdef __cplusplus
}
#endif

#endif
