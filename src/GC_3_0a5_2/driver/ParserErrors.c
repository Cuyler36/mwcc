/* ParserErrors.c: the 11 functions retained in the Windows executable. */
#include "compiler/common.h"
#include "GC_3_0a5_2/driver/ParserDriver.h"
#include "compiler/objects.h"
#include "compiler/scopes.h"
#include "compiler/win32.h"
#include "compiler/CError.h"
#include "driver/CLFileOps.h"
#include "driver/CLIO.h"
#include "driver/CLMain.h"
#include "driver/CLPluginRequests.h"
#include "driver/CLToolExec.h"
#include "driver/CWParserPluginsPrivate.h"
#include "driver/CWPluginsPrivate.h"
#include "driver/ClientGlue.h"
#include "driver/Help.h"
#include "driver/Memory.h"
#include "driver/MsDos.h"
#include "driver/Option.h"
#include "driver/TargetOptimizer-ppc-eabi.h"
#include "driver/ToolHelpers-cc.h"
#include "driver/ToolHelpers.h"
#include <stdio.h>
#include <setjmp.h>
#include <stdio.h>

#define pTool driverTool

#define va_start(ap, parm) do { \
    char *argumentAddress = (char *)&parm; \
    char *argumentEnd = (char *)(&parm + 1); \
    ap = argumentAddress + (argumentEnd - argumentAddress + 3) / 4 * 4; \
} while (0)

#if __MWERKS__ >= 0x3000
extern __declspec(noreturn) void longjmp(jmp_buf env, int val);
#endif

#include <string.h>
static char errorbuf[1024];
void CLPReportError_V(char *message, char *arguments)
{
    vsprintf(errorbuf, message, (char *)(unsigned int *)arguments);
    CWPluginsPrivate_InvokeMessageCallback((struct DispatchObject_0041b830 *)pluginPrivateContext, NULL,
                                           errorbuf, NULL, 2, 0);
    data_00587e1d = 1;
}

void CLPReportWarning_V(char *format, char *arguments)
{
    vsprintf(errorbuf, format, arguments);
    CWPluginsPrivate_InvokeMessageCallback(pluginPrivateContext, NULL, errorbuf, NULL, 1, 0);
}

void CLPStatus_V(char *message, unsigned int *arguments)
{
    vsprintf(errorbuf, message, (char *)arguments);
    fn_0041b8d0((CWPluginPrivateContext *)pluginPrivateContext, errorbuf, NULL);
}

void CLPAlert_V(const char *text, va_list position)
{
    vsprintf(errorbuf, text, position);
    CWPluginsPrivate_CallCallback9(pluginPrivateContext, errorbuf, NULL, NULL, 0);
    data_00587e1d = 1;
}

void CLPOSAlert_V(char *name, DWORD value, unsigned int *result)
{
    vsprintf(errorbuf, name, (char *)result);
    CWPluginsPrivate_CallCallback9(pluginPrivateContext, errorbuf,
                                   "Operating system error:", (unsigned char *)OS_GetErrText(value), 0);
}

char *CLPGetErrorString(SInt16 argument, char *buffer)
{
    CLIO_GetResourceString((unsigned char *)buffer, 0x2eea, argument);
    CLIO_ConvertPascalToCString(buffer);
    return buffer;
}

void CLPReportError(SInt16 messageId, ...)
{
    char message[256];
    va_list arguments;

    CLPGetErrorString(messageId, message);
    va_start(arguments, messageId);
    CLPReportError_V(message, arguments);
}

void CLPReportWarning(SInt16 messageId, ...)
{
    char buffer[256];
    va_list args;

    CLPGetErrorString(messageId, buffer);
    va_start(args, messageId);
    CLPReportWarning_V(buffer, args);
}

void CLPOSAlert(SInt16 resourceId, short errorCode, ...)
{
    char message[256];
    va_list arguments;

    CLPGetErrorString(resourceId, message);
    va_start(arguments, errorCode);
    CLPOSAlert_V(message, errorCode, (unsigned int *)arguments);
}

void CLPStatus(SInt16 messageId, ...)
{
    char buffer[256];
    va_list arguments;

    CLPGetErrorString(messageId, buffer);
    va_start(arguments, messageId);
    CLPStatus_V(buffer, (unsigned int *)arguments);
}

void CLPFatalError(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    CLPAlert_V(fmt, ap);
    longjmp(plugin_request_jmp_buf, -123);
}
