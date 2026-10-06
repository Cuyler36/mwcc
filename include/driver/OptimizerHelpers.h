#ifndef DRIVER_OPTIMIZERHELPERS_H
#define DRIVER_OPTIMIZERHELPERS_H

#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

union OptFlag {
    int i;
    Boolean b;
};
extern int fn_0040d8c0(short arg1, int arg2, int arg3, int arg4);
extern int parse_optimizer_settings(SInt32 option, unsigned char *options, int unused, UInt32 flags);
extern Boolean data_00540b26;
extern char data_00540b27;
extern char data_0054a2f8;
extern char data_0054a2fd;
extern char data_0054a2fe;
extern char data_0054a2ff;
extern char data_0054a300;
extern char data_0054a301;
extern char data_0054a302;
extern int report_optimizer_options(void);
extern char data_0054a2fc;

#ifdef __cplusplus
}
#endif

#endif
