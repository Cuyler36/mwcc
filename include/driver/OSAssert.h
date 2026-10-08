#ifndef DRIVER_OSASSERT_H
#define DRIVER_OSASSERT_H

#include "driver/CLIOAssert.h"

#ifndef CERROR_FILE
#define CERROR_FILE __FILE__
#endif

/* Port the baseline assertion interface with the observed 3.0 argument list. */
#if VERSION == VERSION_GC_3_0A5_2
#define OS_ASSERT_AT(expression, file, line) CLIO_ReportAssertionFailure(expression, file, 0, line)
#define OS_ASSERT(line, cond)                                                                                           \
    do {                                                                                                               \
        if (!(cond))                                                                                                   \
            CLIO_ReportAssertionFailure(#cond, CERROR_FILE, 0, line);                                                   \
    } while (0)
#else
#define OS_ASSERT_AT(expression, file, line) CLIO_ReportAssertionFailure(expression, file, line)
#define OS_ASSERT(line, cond)                                                                                           \
    do {                                                                                                               \
        if (!(cond))                                                                                                   \
            CLIO_ReportAssertionFailure(#cond, CERROR_FILE, line);                                                      \
    } while (0)
#endif

#endif
