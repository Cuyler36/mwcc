#include "msl/time_g.h"
#include "msl/time_win32.h"
#define adjust time_g_adjust
#define asciitime time_g_asciitime
#define clear_tm time_g_clear_tm
#define emit time_g_emit
#define leap_days time_g_leap_days
#define week_num time_g_week_num
#include "ansi_prefix.Win32.h"
#include "time.c"
int __cdecl get_gm_time(int *result)
{
  time_t value;

  value = __get_time();
  __to_gm_time(&value);
  if (result != 0) {
    *result = value;
  }
  return value;
}

struct tm data_0057e1e0;

struct tm *time_to_tm(long *param) {
    long tmp;
    if (param == 0) {
        struct tm *result = &data_0057e1e0;
        time_g_clear_tm(result);
    } else {
        tmp = *param;
        subtract_time_zone_bias((int *)&tmp);
        __time2tm(tmp, &data_0057e1e0);
    }
    return &data_0057e1e0;
}

