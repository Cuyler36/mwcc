#ifndef DRIVER_LICENSEIMPORTS_H
#define DRIVER_LICENSEIMPORTS_H

#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern __declspec(naked) int fn_004270ba(struct MWInfo *info, int version, int request, int options, int flag,
                                         char *path, int *handle);
extern __declspec(naked) void fn_004270c0(int handle);
extern __declspec(naked) char *fn_004270c6(int handle);
extern void *data_0057a224;
extern void *data_0057a228;
extern void *data_0057a22c;

#ifdef __cplusplus
}
#endif

#endif
