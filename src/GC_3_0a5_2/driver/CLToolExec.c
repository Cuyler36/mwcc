/* CLToolExec.c original names from GC 3.0 STABS; native Windows records. */
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct OSSpec { char directory[260]; char name[256]; } OSSpec;
#pragma pack(push, 1)
typedef struct File {
    char prefix[0x1c];
    char inputName[256];
    char objectName[256];
    char nameFlags[2];
    UInt8 nameFlag;
    OSSpec sourcePath;
    OSSpec outputPath;
    char pad627;
    SInt16 outputMask, onDiskMask, temporaryOutputMask;
    char pad62e[0x12];
    SInt16 inputArgumentMask, outputArgumentMask;
} File;
typedef struct Settings { char prefix[0xe]; OSSpec firstFile; } Settings;
typedef struct Target {
    char prefix[0x10];
    Settings *settings;
    char pad14[0x18];
    char files[1];
} Target;
typedef struct ToolRequest {
    UInt32 tag;
    char pad4[4];
    UInt32 flags;
    char padc[6];
} ToolRequest;
#pragma pack(pop)
typedef struct CWCommandLineArgs { int argc; char **argv, **envp; } CWCommandLineArgs;
extern Target *default_target;
extern ToolRequest *plugin_requests;
extern int plugin_request_count;
extern CWCommandLineArgs *tool_argument_sets;
extern SInt16 data_00541b22, DAT_00541b28, data_0065b6ee;
extern UInt8 data_00541b26, data_00710669;
extern char data_005880e0[], linker_tool_name[];
extern char *program_name;
extern void *__stdcall xmalloc(const char *, unsigned int);
extern void *__stdcall xrealloc(const char *, void *, unsigned int);
extern char *__stdcall xstrdup(const char *);
extern void __stdcall xfree(void *);
extern int CLFiles_GetIndex(void *);
extern File *CLFiles_FindFileByIndex(void *, int);
extern int CLFileOps_SetupOutputPath(File *, int, int);
extern int fn_00419e90(File *);
extern int __stdcall CLFileOps_FindExecutable(const char *, OSSpec *);
extern char *__stdcall OS_SpecToString(const OSSpec *, char *, int);
extern int __stdcall OS_Delete(OSSpec *);
extern int __stdcall OS_Execute(OSSpec *, char **, char **, char *, char *, UInt32 *);
extern char *__stdcall OS_GetErrText(int);
extern int __stdcall fn_004050e0(const char *, const char *, int);
extern char *CLPlugins_GetName(Plugin *);
extern void CLMain_AppendEnabledCommandLineOptions(int *, char ***);
extern void CLReport(SInt16, ...);
extern void CLReportError(SInt16, ...);
extern void CLReportWarning(SInt16, ...);
extern void CLIO_FormatAndDispatchText(const char *, ...);
void AppendArgumentList(int *, char ***, const char *);
static int CopyArgumentList(int, char **, int *, char ***);
static int FreeArgumentList(char **);
static int SetupLinkerCommandLine(int, File *, CWCommandLineArgs *);
int SetupTemporaries(void);
int DeleteTemporaries(void);
int ExecuteLinker(Plugin *, UInt32, File *, char *, char *);

int SetupTemporaries(void)
{
    File *record;
    int index = 0;
    while (index < CLFiles_GetIndex(&default_target->files)) {
        record = CLFiles_FindFileByIndex(&default_target->files, index);
        if ((record->outputArgumentMask & 2) != 0 && (data_00541b22 & 2) == 0 && (record->outputMask & 2) == 0)
            {
                if (!data_00710669)
                    record->temporaryOutputMask |= 2;
                else
                    record->outputMask |= 2;
            }
        ++index;
    }
    return 1;
}

int DeleteTemporaries(void)
{
    SInt32 index;
    File *entry;
    index = 0;
    while (index < CLFiles_GetIndex(&default_target->files)) {
        entry = CLFiles_FindFileByIndex(&default_target->files, index);
        if ((entry->outputArgumentMask & 2) && (entry->temporaryOutputMask & 2) && (entry->onDiskMask & 2)) {
            CLFileOps_SetupOutputPath(entry, 2, 0);
            if (DAT_00541b28 > 1) {
                CLReport(19U, OS_SpecToString(&entry->outputPath, data_005880e0, 260U));
            }
            OS_Delete(&entry->outputPath);
            entry->temporaryOutputMask &= ~2;
            entry->onDiskMask &= ~2;
        }
        ++index;
    }
    return 1U;
}
int ExecuteLinker(Plugin *tool, UInt32 flags, File *argument, char *inputPath, char *outputPath)
{
    char fallbackName[256];
    char *toolName;
    OSSpec toolPath;
    CWCommandLineArgs command;
    UInt32 status;
    int executionError;
    char *message;
    int result;
    Boolean found = 0;
    char *cursor;
    int index;

    if ((flags & 1) == 0)
        OS_ASSERT_AT("dropinflags & isExecutableTool", "CLToolExec.c", 266);

    command.envp = NULL;
    command.argc = 0;
    command.argv = command.envp;

    if (flags & 0x8000000)
        message = "pre-linker";
    else if (flags & 0x40000000)
        message = "post-linker";
    else
        message = "linker";

    toolName = CLPlugins_GetName(tool);
    if ((flags & 0x48000000) == 0 && linker_tool_name[0] != 0)
        toolName = linker_tool_name;

    else if (fn_004050e0(program_name, "nmw", 3) == 0) {
        fallbackName[0] = 'n';
        strncpy(fallbackName + 1, toolName, 254);
        if (CLFileOps_FindExecutable(fallbackName, &toolPath) == 0) {
            found = 1;
            toolName = fallbackName;
        }
    }

    if (!found) {
        if (CLFileOps_FindExecutable(toolName, &toolPath) == 0)
            found = 1;
    }
    if (!found) {
        strcpy(fallbackName, program_name);
        for (cursor = fallbackName; *cursor != 0; cursor++)
            *cursor = (char)tolower(*cursor);

        if ((cursor = strstr(fallbackName, "cc")) != NULL || (cursor = strstr(fallbackName, "pas")) != NULL ||
            (cursor = strstr(fallbackName, "asm")) != NULL) {
            if (*cursor != 'c') {
                memmove(cursor + 2, cursor + 3, strlen(cursor) - 3);
                cursor[strlen(cursor) - 1] = '\0';
            }
            cursor[0] = 'l';
            cursor[1] = 'd';
        } else {
            cursor = strstr(fallbackName, "mwc");
            if (cursor != NULL) {
                char *suffix = cursor + 2;
                memmove(suffix + 3, cursor + 2, strlen(cursor + 2));
                cursor += 2;
                memcpy(cursor, "Link", 4);
            }
        }

        if (CLFileOps_FindExecutable(fallbackName, &toolPath) == 0) {
            toolName = fallbackName;
            if (linker_tool_name[0]) {
                CLReportWarning(0x42, message, linker_tool_name);
                CLReport(0x41, toolName, program_name);
            } else if (DAT_00541b28 != 0)
                CLReport(0x41, toolName, program_name);
        } else {
            CLReportError(0x42, message, toolName);
            return 0;
        }
    }

    result = 1;
    SetupLinkerCommandLine(flags, argument, &command);
    cursor = OS_SpecToString(&toolPath, data_005880e0, 0x104);
    command.argv[0] = xstrdup(cursor);
    command.argv[command.argc] = NULL;

    if (DAT_00541b28 != 0 || data_00541b26 != 0) {
        CLIO_FormatAndDispatchText("\nCommand line:\n");
        for (index = 0; index < command.argc && command.argv[index] != NULL; index++) {
            CLIO_FormatAndDispatchText(strchr(command.argv[index], ' ') != NULL ? "\"%s\" " : "%s ", command.argv[index]);
        }
        CLIO_FormatAndDispatchText("\n\n");
    }

    fflush(stdout);
    fflush(stderr);

    if (DAT_00541b28 != 0) {
        cursor = OS_SpecToString(&toolPath, data_005880e0, 0x104);
        CLReport(0x43, message, cursor);
    }

    if (data_00541b26 == 0) {
        executionError = OS_Execute(&toolPath, command.argv, command.envp, inputPath, outputPath, &status);
        if (executionError != 0) {
            char *errorDetail = OS_GetErrText(executionError);
            CLReportError(0x44, message, command.argv[0], errorDetail);
            result = 0;
        } else if (status != 0) {
            CLReportError(0x45, message, command.argv[0], status);
            result = 0;
        }
    }

    FreeArgumentList(command.argv);
    FreeArgumentList(command.envp);
    return result;
}

static int SetupLinkerCommandLine(int flags, File *tool, struct CWCommandLineArgs *arguments)
{
    int index;
    struct CWCommandLineArgs *argument_set;
    
    index = 0;
    if (plugin_request_count > 0) {
        do {
            if (plugin_requests[index].tag == 1281977963 &&
                (flags & 1207959552) == (plugin_requests[index].flags & 1207959552)) {
                break;
            }
            index = index + 1;
        } while (index < plugin_request_count);
    }
    if (index >= plugin_request_count) {
        OS_ASSERT_AT("x < numPlugins", "CLToolExec.c", 89);
    }
    arguments->argc = 1;
    arguments->argv = xmalloc("command-line arguments", 8);
    CLMain_AppendEnabledCommandLineOptions(&arguments->argc, &arguments->argv);
    argument_set = &tool_argument_sets[index];
    CopyArgumentList(argument_set->argc - 1, argument_set->argv + 1, &arguments->argc,
                                  &arguments->argv);
    index = 0;
    if (argument_set->envp != NULL) {
        while (argument_set->envp[index] != NULL) {
            index = index + 1;
        }
    }
    arguments->envp = NULL;
    CopyArgumentList(index, argument_set->envp, NULL, &arguments->envp);
    if (tool == NULL && (flags & 1073741824) == 0) {
        for (index = 0; index < CLFiles_GetIndex(&default_target->files); index = index + 1) {
            tool = CLFiles_FindFileByIndex(&default_target->files, index);
            if ((tool->inputArgumentMask & 2) != 0) {
                AppendArgumentList(&arguments->argc, &arguments->argv, tool->inputName);
            }
            if ((tool->outputArgumentMask & 2) != 0) {
                if (CLFileOps_SetupOutputPath(tool, 2, 1) != 0 && fn_00419e90(tool) != 0) {
                    AppendArgumentList(&arguments->argc, &arguments->argv,
                                              OS_SpecToString((OSSpec *)&tool->outputPath, data_005880e0, 260));
                } else {
                    return 0;
                }
            }
        }
    } else if (tool != NULL) {
        arguments->argv = xrealloc("command-line arguments", arguments->argv, (arguments->argc + 1) << 2);
        if ((tool->inputArgumentMask & 2) != 0) {
            AppendArgumentList(&arguments->argc, &arguments->argv, tool->inputName);
        }
        if ((tool->outputArgumentMask & 2) != 0 && CLFileOps_SetupOutputPath(tool, 2, 1) != 0 && fn_00419e90(tool) != 0) {
            AppendArgumentList(&arguments->argc, &arguments->argv,
                                      OS_SpecToString((OSSpec *)&tool->outputPath, data_005880e0, 260));
        }
        if ((data_0065b6ee & 4) && (tool->outputArgumentMask & 1) && tool->nameFlag && tool->objectName[0] &&
            CLFileOps_SetupOutputPath(tool, 4, 1)) {
            AppendArgumentList(&arguments->argc, &arguments->argv, "-o");
            AppendArgumentList(&arguments->argc, &arguments->argv,
                               OS_SpecToString(&tool->outputPath, data_005880e0, 260));
        }
    } else {
        if ((flags & 1073741824) != 0) {
            
            AppendArgumentList(&arguments->argc, &arguments->argv,
                                      OS_SpecToString(&default_target->settings->firstFile, data_005880e0, 260));
        }
    }
    arguments->argv[arguments->argc] = NULL;
    return 1;
}

static int CopyArgumentList(int count, char **strings, int *stored_count, char ***stored_strings)
{
    int i;
    int total;

    total = stored_count ? *stored_count : 0;

    *stored_strings = xrealloc("command-line arguments", *stored_strings, (total + count + 1) * sizeof(char *));

    if (strings != NULL) {
        for (i = 0; i < count; i++) {
            (*stored_strings)[total] = xstrdup(strings[i]);
            total++;
        }
    }

    (*stored_strings)[total] = NULL;

    if (stored_count != NULL)
        *stored_count = total;

    return 1;
}

void AppendArgumentList(int *count, char ***storage, const char *value)
{
    *storage = xrealloc("command-line arguments", *storage, (*count + 2U) << 2);
    (*storage)[(*count)++] = xstrdup(value);
}

static int FreeArgumentList(char **items)
{
    int index;

    for (index = 0; items[index] != NULL; index = index + 1) {
        xfree(items[index]);
    }
    xfree(items);
    return 1;
}
