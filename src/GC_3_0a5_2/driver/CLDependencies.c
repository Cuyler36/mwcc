#define CERROR_FILE "CLDependencies.c"
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include "driver/Memory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern __declspec(noreturn) void exit(int);
#define EMPTYS ""

typedef struct GC3OSSpec { struct { char path[260]; } directory; char name[256]; } GC3OSSpec;
typedef struct Path Path;
typedef struct Paths { Path **items; UInt16 capacity; UInt16 count; } Paths;
struct Path { char *path; Paths *children; char *dirlist; short flags; };
typedef struct GC3Target GC3Target;
typedef struct InclFile {
    int nameOffset;
    Path *searchPath;
    Path *resolvedPath;
    Path *contextPath;
    short usage;
    UInt8 flag;
    UInt8 padding;
} InclFile;
typedef struct Incls {
    GC3Target *target;
    int count;
    int alloccount;
    InclFile *records;
    int textsize;
    int textused;
    char *text;
    Paths *scope;
} Incls;
struct GC3Target {
    unsigned char reserved000[0x44];
    Incls dependencyTable;
    Paths userPaths;
    Paths systemPaths;
};
typedef struct Deps { int count; int capacity; int *entries; Incls *dependencyTable; } Deps;
#pragma pack(push, 1)
typedef struct GC3File {
    unsigned char reserved000[0x1c];
    char inputName[256];
    unsigned char reserved11c[0x307];
    GC3OSSpec outputPath;
    unsigned char reserved627[0x249];
    Deps dependencies;
} GC3File;
#pragma pack(pop)

static Path *specialAccessPath;
#define data_0054d898 specialAccessPath
static GC3OSSpec *currentsrcfss;
extern GC3Target *default_target;
extern short data_00541b44;
extern short DAT_00541b28;
extern char DAT_00541c0b;
extern char data_005880e0[];
extern void *(*includeStackTOS)(void);
extern void *__stdcall xmalloc(const char *, unsigned int);
extern void *__stdcall xrealloc(const char *, void *, unsigned int);
extern void __stdcall xfree(void *);
extern Boolean CLAccessPaths_Init(Paths *);
extern Boolean CLAccessPaths_FreeItems(Paths *);
extern Path *CLAccessPaths_FindPath(Paths *, char *);
extern Path *CLAccessPaths_CreateAccessPathEntry(char *);
extern Boolean CLAccessPaths_StoreItem(Paths *, Path *);
extern UInt16 CLAccessPaths_GetCount(Paths *);
extern Path *CLAccessPaths_GetEntry(Paths *, UInt16);
extern int __stdcall CLProj_MakeOSSpecFromPath(char *, char *, int, GC3OSSpec *, UInt8 *);
extern char *__stdcall CLProj_GetFileName(char *);
extern char *__stdcall CLProj_MakeRelativePath(GC3OSSpec *, GC3OSSpec *, char *, unsigned int);
extern unsigned int __stdcall CLFileOps_AppendMemBuffer(void *, const void *, unsigned int);
extern int __stdcall OS_MakeFileSpec(const char *, GC3OSSpec *);
extern int __stdcall OS_Status(GC3OSSpec *);
extern int __stdcall OS_EqualPath(const char *, const char *);
extern int __stdcall OS_EqualPathSpec(const char *, const char *);
extern int __stdcall MsDos_IsAbsolutePath(char *);
extern int __stdcall OS_GetCWD(char *);
extern char *__stdcall OS_SpecToString(GC3OSSpec *, char *, int);
extern char *__stdcall fn_00412340(char *, char *, unsigned int);
extern int __stdcall OS_NewHandle(unsigned int, MemBuffer *);
extern void CLErrors_ReportInternalError(char *, int, char *, ...);
extern void CLErrors_ForwardMessage(int, ...);
extern Boolean fn_00427b90(GC3Target *, char *, Boolean, Path **, GC3OSSpec *, Boolean *);
extern void fn_00434d30(int, void *, GC3OSSpec *);

Boolean FindFileInPaths(Paths *, char *, Path **, GC3OSSpec *);
void AddFileToIncls(Incls *, char *, UInt8, Path *, Path *, Path *, SInt32 *);
Path *Deps_GetSpecialAccessPath(void);
SInt32 Deps_ChangeSpecialAccessPath(GC3OSSpec *, Boolean);
void SetSpecialAccessPathFromIncludeStackTOS(int);

#pragma auto_inline off

unsigned char Incls_Initialize(Incls *state, GC3Target *target)
{
    Paths *scope;
    data_0054d898 = NULL;
    state->target = target;
    state->count = state->alloccount = 0;
    state->textsize = state->textused = 0;
    state->text = NULL;
    state->records = NULL;
    scope = (Paths *)xmalloc(NULL, sizeof(Paths));
    state->scope = scope;
    CLAccessPaths_Init(state->scope);
    return 1;
}

void Incls_Terminate(Incls *block)
{
    if (block->text != NULL) {
        xfree(block->text);
    }
    if (block->records != NULL) {
        xfree(block->records);
    }
    CLAccessPaths_FreeItems(block->scope);
    xfree(block->scope);
}

unsigned char IsSysIncl(Incls *table, unsigned int index)
{
    return table->records[index].flag;
}

void MakeInclFileSpec(Incls *table, int index, char *output)
{
    InclFile *record = &table->records[index];
    struct Path *path = record->resolvedPath;

    CLProj_MakeOSSpecFromPath(path->path, table->text + record->nameOffset, 0, (GC3OSSpec *)output, NULL);
}



Boolean SameIncl(Incls *table, SInt32 firstIndex, SInt32 secondIndex)
{
    InclFile *first;
    InclFile *second;
    SInt32 result;

    if (firstIndex == secondIndex)
        return 1;
    first = &table->records[firstIndex];
    second = &table->records[secondIndex];
    result = 0;
    if (first->resolvedPath == second->resolvedPath) {
        if (OS_EqualPath(table->text + first->nameOffset, table->text + second->nameOffset))
            result = 1;
    }
    return result;
}

Path *FindOrAddGlobalInclPath(Paths *scope, char *name)
{
    Path *result = CLAccessPaths_FindPath(scope, name);
    if (result == NULL) {
        result = CLAccessPaths_CreateAccessPathEntry(name);
        CLAccessPaths_StoreItem(scope, result);
    }
    return result;
}

Boolean _FindFileInPath(Path *entry, char *comparison, Path **result, GC3OSSpec *context)
{
    UInt32 status;
    if (CLProj_MakeOSSpecFromPath(entry->path, comparison, 0, context, (UInt8 *)&status) == 0 && ((UInt8)status & 1)) {
        *result = entry;
        return 1;
    }
    if (entry->children && FindFileInPaths(entry->children, comparison, result, context))
        return 1;
    return 0;
}

Path *Deps_GetSpecialAccessPath(void)
{
    return data_0054d898;
}

UInt8 FindDepFile(Deps *collection, SInt32 key)
{
    int index;
    index = 0;
    while (index < collection->count) {
        if (SameIncl(&default_target->dependencyTable, collection->entries[index], key) != 0) {
            return 1;
        }
        index = index + 1;
    }
    return 0;
}

void AddDepFile(Deps *v, int x, short flag)
{
    if (v->count >= v->capacity) {
        v->capacity += 16;
        v->entries = xrealloc("dependency list", v->entries, v->capacity * 4);
    }
    v->entries[v->count++] = x;
}

void Deps_AddDependency(Deps *collection, SInt32 *index, GC3OSSpec *name, unsigned char flags, short entryFlag, char *result)
{
    Boolean matched;
    unsigned int alternateMatch;
    if (*index < 0)
        AddFileToIncls(&default_target->dependencyTable, OS_SpecToString(name, data_005880e0, 0x104), 0, NULL, NULL, NULL, index);
    matched = FindDepFile(collection, *index);
    if (!matched) {
        if (DAT_00541c0b) alternateMatch = IsSysIncl(collection->dependencyTable, *index);
        else alternateMatch = 0;
        if ((unsigned char)alternateMatch == 0)
            AddDepFile(collection, *index, entryFlag);
    }
    if (result) *result = matched;
}

char *EscapeName(Boolean escapeSpaces, char *destination, char *source)
{
    char *result;

    if (!escapeSpaces) {
        return source;
    }
    result = destination;
    while (*source) {
        if (*source == ' ') {
            *destination++ = '\\';
        }
        *destination++ = *source++;
    }
    *destination = '\0';
    return result;
}

void Deps_ListDependencies(Incls *ctx, GC3File *file, MemBuffer *stream)
{
    struct GC3OSSpec *source;
    SInt32 remaining;
    char line[520];
    char target[260];
    char dependency[260];
    char escaped[516];
    GC3OSSpec path;
    Boolean hasSpace;
    SInt32 i;
    int *items;
    char *separator;

    do {
        if (OS_NewHandle(0, stream) != 0) {
            break;
        }
        remaining = file->dependencies.count;
        source = &file->outputPath;
        CLProj_MakeRelativePath(source, NULL, target, 0x104);
        if (target[0] != 0) {
            hasSpace = (strchr(target, ' ') != NULL);
            sprintf(line, "%s%s%s%s ", hasSpace ? EMPTYS : EMPTYS, EscapeName(hasSpace, escaped, target),
                    hasSpace ? EMPTYS : EMPTYS, ":");
            if (CLFileOps_AppendMemBuffer(stream, line, strlen(line)) != 0) {
                break;
            }
            hasSpace = (strchr(file->inputName, ' ') != NULL);
            separator = remaining ? "\\" : EMPTYS;
            sprintf(line, "%s%s%s %s\n", hasSpace ? EMPTYS : EMPTYS, EscapeName(hasSpace, escaped, file->inputName),
                    hasSpace ? EMPTYS : EMPTYS, separator);
            if (CLFileOps_AppendMemBuffer(stream, line, strlen(line)) != 0) {
                break;
            }
        } else {
            hasSpace = (strchr(file->inputName, ' ') != NULL);
            separator = remaining ? "\\" : EMPTYS;
            sprintf(line, "%s%s%s%s %s\n", hasSpace ? EMPTYS : EMPTYS,
                    EscapeName(hasSpace, escaped, file->inputName), hasSpace ? EMPTYS : EMPTYS, ":", separator);
            if (CLFileOps_AppendMemBuffer(stream, line, strlen(line)) != 0) {
                break;
            }
        }
        for (i = 0; i < file->dependencies.count; i++) {
            remaining--;
            items = file->dependencies.entries;
            MakeInclFileSpec(ctx, items[i], (char *)&path);
            OS_SpecToString(&path, dependency, 0x104);
            hasSpace = (strchr(dependency, ' ') != NULL);
            separator = remaining ? "\\" : EMPTYS;
            sprintf(line, "\t%s%s%s %s\n", hasSpace ? EMPTYS : EMPTYS, EscapeName(hasSpace, escaped, dependency),
                    hasSpace ? EMPTYS : EMPTYS, separator);
            if (CLFileOps_AppendMemBuffer(stream, line, strlen(line)) != 0) {
                goto out_of_memory;
            }
        }
        return;
    } while (0);
out_of_memory:
    fprintf(stderr, "\n*** Out of memory\n");
    exit(-23);
}

Boolean FindFileInPaths(Paths *dependencies, char *comparison, Path **result,
                                          GC3OSSpec *path)
{
    UInt16 index;
    Path *dependency;

    for (index = 0; index < CLAccessPaths_GetCount(dependencies); index++) {
        dependency = CLAccessPaths_GetEntry(dependencies, index);
        if (dependency == NULL)
            OS_ASSERT_AT("path", "CLDependencies.c", 0xaf);
        if (_FindFileInPath(dependency, comparison, result, path))
            return 1;
    }
    return 0;
}

void AddFileToIncls(Incls *deps, char *name, UInt8 flag, Path *obj, Path *type,
                       Path *unused, SInt32 *out)
{
    char *str;
    GC3OSSpec buf;
    InclFile *rec;
    SInt32 len;

    if (obj == NULL && type == NULL)
        str = CLProj_GetFileName(name);
    else
        str = name;

    len = strlen(str) + 1;

    if (deps->count >= deps->alloccount) {
        deps->alloccount += 0x10;
        deps->records = xrealloc("include list", deps->records, deps->alloccount * sizeof(InclFile));
    }

    rec = &deps->records[deps->count];
    rec->nameOffset = deps->textused;
    rec->flag = flag;
    rec->searchPath = obj;

    if (type != NULL) {
        rec->resolvedPath = type;
    } else if (obj != NULL) {
        rec->resolvedPath = FindOrAddGlobalInclPath(deps->scope, obj->path);
    } else {
        OS_MakeFileSpec(name, &buf);
        rec->resolvedPath = FindOrAddGlobalInclPath(deps->scope, buf.directory.path);
    }
    rec->contextPath = Deps_GetSpecialAccessPath();
    rec->usage = 0;

    if (deps->textused + len > deps->textsize) {
        deps->textsize += 0x400;
        deps->text = xrealloc("include list", deps->text, deps->textsize);
    }
    strcpy(deps->text + deps->textused, str);
    deps->textused += len;
    *out = deps->count++;
}

Boolean Incls_FindFileInPaths(int cwplugin_api, Incls *dependencies, char *file, Boolean searchFirst, GC3OSSpec *context, SInt32 *index)
{
    Boolean found = 0;
    Path *lookupText;
    Path *result;
    Path *value;
    Boolean searchMode;
    if (data_00541b44 == 3) {
        if (searchFirst)
            SetSpecialAccessPathFromIncludeStackTOS(cwplugin_api);
        else {
            data_0054d898 = NULL;
            if (DAT_00541b28 > 2)
                CLErrors_ForwardMessage(107, "<none>");
        }
    }
    *index = -1;
    result = NULL;
    value = NULL;
    searchMode = searchFirst;
    if (MsDos_IsAbsolutePath(file)) {
        found = OS_MakeFileSpec(file, context) == 0 && OS_Status(context) == 0;
        value = result = lookupText = NULL;
    } else {
        result = lookupText = Deps_GetSpecialAccessPath();
        if (lookupText) {
            found = _FindFileInPath(result, file, &result, context);
            value = NULL;
        }
        if (!found && !strpbrk(file, "/\\:")) {
            result = NULL;
            searchMode = 1;
            found = fn_00427b90(default_target, file, searchFirst, &value, context, &searchMode);
        } else {
            if (!found && searchFirst) {
                searchMode = 1;
                result = NULL;
                found = FindFileInPaths(&dependencies->target->systemPaths, file, &value, context);
            }
            if (!found) {
                searchMode = 0;
                result = NULL;
                found = FindFileInPaths(&dependencies->target->userPaths, file, &value, context);
            }
        }
    }
    if (found && *index < 0)
        AddFileToIncls(dependencies, file, !searchMode, value, result, lookupText, index);
    return found;
}

Boolean Deps_Initialize(Deps *value, struct Incls *fourth)
{
    value->count = 0;
    value->capacity = 0;
    value->entries = NULL;
    value->dependencyTable = fourth;
    return 1;
}

SInt32 Deps_ChangeSpecialAccessPath(GC3OSSpec *name, Boolean flag)
{
    char buffer[260];
    char *path;
    if (flag && name)
        currentsrcfss = name;
    switch (data_00541b44) {
        case 2: data_0054d898 = NULL; return 1;
        case 0:
            if (!flag) return 1;
            OS_GetCWD(buffer); path = buffer; break;
        case 1:
            if (!flag) return 1;
        case 3:
            if (name) path = name->directory.path;
            else if (currentsrcfss) path = currentsrcfss->directory.path;
            else { OS_GetCWD(buffer); path = buffer; }
            break;
        default:
            CLErrors_ReportInternalError("CLDependencies.c", 0x1ef, "Unhandled include file search type (%d)\n", data_00541b44);
            break;
    }
    data_0054d898 = FindOrAddGlobalInclPath(default_target->dependencyTable.scope, path);
    if (DAT_00541b28 > 2)
        CLErrors_ForwardMessage(107, fn_00412340(path, data_005880e0, 0x104));
    return 1;
}

void Deps_Terminate(Deps *deps)
{
    if (deps->entries)
        xfree(deps->entries);
}

void SetSpecialAccessPathFromIncludeStackTOS(int cwplugin_api)
{
    GC3OSSpec spec;
    void *tos;
    if (data_00541b44 == 3) {
        tos = NULL;
        if (includeStackTOS)
            tos = includeStackTOS();
        if (tos) {
            fn_00434d30(cwplugin_api, tos, &spec);
            if (data_0054d898 && OS_EqualPathSpec(spec.directory.path, data_0054d898->path))
                return;
            Deps_ChangeSpecialAccessPath(&spec, 0);
            return;
        } else
            Deps_ChangeSpecialAccessPath(NULL, 0);
    }
}
