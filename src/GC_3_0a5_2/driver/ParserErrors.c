/* Baseline bodies ported under the source/function names in the 3.0 map. */
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

#define va_start(ap, parm) ap = (char *)&parm + ((((char *)(&parm + 1) - (char *)&parm) + 3) / 4 * 4)

#include <string.h>
void CLPReportError_V(char *message, char *arguments)
{
    vsprintf(formatted_message, message, (char *)(unsigned int *)arguments);
    CWPluginsPrivate_InvokeMessageCallback((struct DispatchObject_0041b830 *)pluginPrivateContext, NULL,
                                           formatted_message, NULL, 2, 0);
    data_00587e1d = 1;
}

void CLPReportWarning_V(char *format, char *arguments)
{
    vsprintf(formatted_message, format, arguments);
    CWPluginsPrivate_InvokeMessageCallback(pluginPrivateContext, NULL, formatted_message, NULL, 1, 0);
}

void CLPReport_V(char *first, char *second)
{
    vsprintf(formatted_message, first, (char *)(unsigned int *)second);
    CWPluginsPrivate_InvokeMessageCallback((struct DispatchObject_0041b830 *)pluginPrivateContext, NULL,
                                           formatted_message, NULL, 0, 0);
}

void CLPStatus_V(char *message, unsigned int *arguments)
{
    vsprintf(formatted_message, message, (char *)arguments);
    fn_0041b8d0((CWPluginPrivateContext *)pluginPrivateContext, formatted_message, NULL);
}

void CLPAlert_V(const char *text, va_list position)
{
    vsprintf(formatted_message, text, position);
    CWPluginsPrivate_CallCallback9(pluginPrivateContext, formatted_message, NULL, NULL, 0);
    data_00587e1d = 1;
}

void CLPOSAlert_V(char *name, DWORD value, unsigned int *result)
{
    vsprintf(formatted_message, name, (char *)result);
    CWPluginsPrivate_CallCallback9(pluginPrivateContext, formatted_message,
                                   "Operating system error:", (unsigned char *)OS_GetErrText(value), 0);
}

char *CLPGetErrorString(SInt32 argument, char *buffer)
{
    CLIO_GetResourceCString(buffer, 0x2eea, argument);
    return buffer;
}

void CLPReportError(SInt32 messageId, ...)
{
    char message[256];
    va_list arguments;

    CLPGetErrorString(messageId, message);
    arguments = (char *)&messageId + (((char *)((SInt16 *)&messageId + 1) - (char *)&messageId + 3) / 4 * 4);
    CLPReportError_V(message, arguments);
}

void CLPReportWarning(int messageId, ...)
{
    char buffer[256];
    va_list args;

    CLPGetErrorString(messageId, buffer);
    args = (char *)&messageId + (((char *)((SInt16 *)&messageId + 1) - (char *)&messageId + 3) / 4 * 4);
    CLPReportWarning_V(buffer, args);
}

void CLPReport(int messageId, ...)
{
    char buffer[256];
    va_list arguments;
    char *argumentAddress;
    char *argumentEnd;

    CLPGetErrorString(messageId, buffer);
    argumentAddress = (va_list)&messageId;
    argumentEnd = (va_list)&messageId + sizeof(short);
    arguments = (va_list)&messageId + (argumentEnd - argumentAddress + 3) / 4 * 4;
    CLPReport_V(buffer, arguments);
}

unsigned char CLPOSAlert(int resourceId, short errorCode, ...)
{
    unsigned char CLPOSAlert_V(char *message, int errorCode, va_list arguments);
    char message[256];
    va_list arguments;

    CLPGetErrorString(resourceId, message);
    va_start(arguments, errorCode);
    return CLPOSAlert_V(message, errorCode, arguments);
}

void CLPStatus(int messageId, ...)
{
    char buffer[256];
    va_list arguments;

    CLPGetErrorString(messageId, buffer);
    arguments = (char *)&messageId + ((((char *)((short *)&messageId + 1) - (char *)&messageId) + 3) / 4 * 4);
    CLPStatus_V(buffer, (unsigned int *)arguments);
}

void CLPFatalError(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    CLPAlert_V(fmt, ap);
    longjmp(plugin_request_jmp_buf, -123);
}
