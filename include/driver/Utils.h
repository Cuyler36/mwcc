#ifndef DRIVER_UTILS_H
#define DRIVER_UTILS_H

#include <setjmp.h>
#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int to_lowercase(int character);
extern unsigned int Utils_IsDigit(char c);
extern int Utils_IsAlpha(char c);
extern int Utils_IsAlnum(char character);
extern int Utils_IsHexDigit(char c);
extern char *Utils_FormatOptions(char *options, char *destination, SInt8 flags);
extern int Utils_MatchStringSegments(char *s1, char *s2, int casesens, int abbrev);

#ifdef __cplusplus
}
#endif

#endif
