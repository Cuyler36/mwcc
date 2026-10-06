#ifndef MSL_CRITICAL_REGIONS_WIN32_H
#define MSL_CRITICAL_REGIONS_WIN32_H

#include "compiler/win32.h"

extern void delete_critical_sections(void);
extern void __begin_critical_region(unsigned int a);
extern void __end_critical_region(unsigned int a);
extern void initialize_critical_sections(void);
extern struct _RTL_CRITICAL_SECTION DAT_0057d228[5];

#endif
