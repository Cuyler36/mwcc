#ifndef DRIVER_CLIOASSERT_H
#define DRIVER_CLIOASSERT_H

#include "version.h"

#ifdef __cplusplus
extern "C" {
#endif

#if VERSION == VERSION_GC_3_0A5_2
extern void CLIO_ReportAssertionFailure(char *expression, char *file, char *function, unsigned int line);
#else
extern void CLIO_ReportAssertionFailure(char *expression, char *file, unsigned int line);
#endif

#ifdef __cplusplus
}
#endif

#endif
