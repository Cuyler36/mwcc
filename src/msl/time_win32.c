#include "msl/time_win32.h"
#include "ansi_prefix.Win32.h"
#include "time.win32.c"
int __cdecl subtract_time_zone_bias(int *timeValue)
{
  DWORD timeZoneResult;
  TIME_ZONE_INFORMATION timeZoneInfo;
  timeZoneResult = GetTimeZoneInformation(&timeZoneInfo);
  if (timeZoneResult == 0) {
    return 0;
  }
  *timeValue -= timeZoneInfo.Bias * 60;
  return 1;
}

