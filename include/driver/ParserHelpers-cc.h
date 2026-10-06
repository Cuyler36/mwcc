#ifndef DRIVER_PARSERHELPERS_CC_H
#define DRIVER_PARSERHELPERS_CC_H

#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int append_undef_directive(char *option, int unused, char *symbol);
extern int append_include_directive(char *option, void *handle, char *filename);
extern int ParserHelpers_cc_EmitPragmas(Pragma *pragmas);
extern int set_output_path(char *name, int unused, char *path);
extern Boolean output_path_set;
extern Boolean data_0058851d;
extern unsigned char data_00588530;
extern int log_linker_option(const char *option);
extern void fn_0040d822(void);
extern unsigned char data_00537845;
extern char data_00537848[];
extern char data_00587d04[];

#ifdef __cplusplus
}
#endif

#endif
