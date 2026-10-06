#include "msl/string.h"
#include "ansi_prefix.Win32.h"
#include "string.c"
char DAT_0057d2c0[256];

int __cdecl get_strerror(int value)
{
  value = (int)__strerror(value, DAT_0057d2c0);
  return value;
}

