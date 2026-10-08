/* GC 3.0 Windows access paths; original core names from CLAccessPaths.c STABS. */
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include <string.h>

typedef struct OSPathSpec {
    char text[260];
} OSPathSpec;
typedef struct OSSpec {
    OSPathSpec directory;
    char name[256];
} OSSpec;
typedef struct DirectorySearch {
    void *handle, *findData;
    OSPathSpec path;
} DirectorySearch;
typedef struct Path Path;
typedef struct Paths {
    Path **pathsArray;
    UInt16 arraySize, pathsCount;
} Paths;
struct Path {
    OSPathSpec *spec;
    Paths *recursive;
    UInt16 flags;
    UInt16 index; /* Windows field meanings recovered from Add/Insert/Remove. */
    UInt16 order; /* Windows preorder ordinal; original field name is unknown. */
    UInt8 gathered;
};
extern void *__stdcall xmalloc(const char *, unsigned int);
extern void *__stdcall xcalloc(const char *, unsigned int);
extern void *__stdcall xrealloc(const char *, void *, unsigned int);
extern void __stdcall xfree(void *);
extern int __stdcall OS_EqualPathSpec(const void *, const void *);
extern int __stdcall OS_OpenDir(const OSPathSpec *, DirectorySearch *);
extern int __stdcall OS_ReadDir(DirectorySearch *, OSSpec *, char *, UInt8 *);
extern int __stdcall OS_CloseDir(DirectorySearch *);
extern char *__stdcall CLProj_GetFileName(char *);
extern unsigned int __stdcall CLProj_MakeOSSpecFromPath(const OSPathSpec *, char *, UInt8, OSSpec *, int);
extern Boolean fn_004151f0(void);
extern void fn_00427c40(void *, Path *, const char *);
extern void *data_0071099c;
Path *Path_Init(OSPathSpec *, Path *);
Path *Path_New(OSPathSpec *);
void Path_Free(Path *);
Boolean Paths_Initialize(Paths *);
Boolean Paths_Terminate(Paths *);
static Boolean Paths_GrowPaths(Paths *, UInt16 *);
Boolean Paths_AddPath(Paths *, void *);
Boolean Paths_InsertPath(Paths *, UInt16, Path *);
Boolean Paths_RemovePath(Paths *, UInt16);
Boolean Paths_DeletePath(Paths *, UInt16);
Path *Paths_GetPath(Paths *, UInt16);
UInt16 Paths_Count(Paths *);
Path *Paths_FindPathSpec(Paths *, void *);
static Boolean GatherRecurse(Paths *, Path *);
Boolean Paths_GatherRecurse(Path *);
int Paths_CountRecurse(Paths *);
static void CopyRecurseSpecs(void *, OSSpec **, Paths *, UInt16 *);
void Paths_CopyRecurseSpecs(void *, OSSpec *, Paths *, UInt16);
int fn_00426a80(char *);

/* Windows-only helpers; original names are unavailable in the Mac map. */
static UInt16 fn_00426900(Paths *paths, UInt16 order)
{
    UInt16 idx;
    Path *path;
    if (!paths)
        return order;
    for (idx = 0; idx < paths->pathsCount; idx++) {
        path = paths->pathsArray[idx];
        path->order = order;
        order = fn_00426900(path->recursive, order + 1);
    }
    return order;
}

UInt16 fn_00426950(Paths *paths, UInt16 order)
{
    return fn_00426900(paths, order);
}

void fn_004269e0(Path *path)
{
    DirectorySearch rf;
    OSSpec spec;
    char filename[256];
    struct {
        UInt8 value;
        char padding[3];
    } mode;
    int err;
    if (path->gathered)
        return;
    path->gathered = 1;
    err = OS_OpenDir(path->spec, &rf);
    while (err == 0) {
        err = OS_ReadDir(&rf, &spec, filename, &mode.value);
        if (err == 0 && (mode.value & 1))
            fn_00427c40(data_0071099c, path, filename);
    }
    OS_CloseDir(&rf);
}

int fn_00426a80(char *filename)
{
    char *name = CLProj_GetFileName(filename);
    char *end = name + strlen(name) - 1;
    if (*end == '\\')
        end--;
    if (name < end && *name == '(' && *end == ')')
        return 0;
    return 1;
}

Path *Path_Init(OSPathSpec *dir, Path *path)
{
    path->spec = xmalloc(NULL, sizeof(*dir));
    *path->spec = *dir;
    path->recursive = NULL;
    path->flags = 0;
    path->order = 0;
    path->gathered = 0;
    return path;
}

Path *Path_New(OSPathSpec *source)
{
    Path *result;
    OSPathSpec *spec = source;

    result = xmalloc(NULL, 0x10);
    return Path_Init(spec, result);
}

void Path_Free(Path *blocks)
{
    if (blocks != NULL) {
        blocks->index = 0xffff;
        if (blocks->spec != NULL) {
            xfree(blocks->spec);
        }
        if (blocks->recursive != NULL) {
            Paths_Terminate(blocks->recursive);
            xfree(blocks->recursive);
        }
        xfree(blocks);
    }
}

void Paths_CopyRecurseSpecs(void *plugin, OSSpec *list, Paths *paths, UInt16 count)
{
    CopyRecurseSpecs(plugin, &list, paths, &count);
    if (count != 0)
        OS_ASSERT_AT("count == 0", "CLAccessPaths.c", 421);
}

unsigned char Paths_Terminate(Paths *paths)
{
    unsigned int index;
    if (!paths)
        OS_ASSERT_AT("paths != NULL", "CLAccessPaths.c", 66U);
    if (paths->pathsArray) {
        for (index = 0; (unsigned short)index < paths->pathsCount; ++index)
            Path_Free(paths->pathsArray[(unsigned short)index]);
        xfree(paths->pathsArray);
    }
    paths->pathsArray = NULL;
    paths->pathsCount = 0;
    paths->arraySize = 0;
    return 1;
}

unsigned char Paths_Initialize(Paths *paths)
{
    if (paths == NULL) {
        OS_ASSERT_AT("paths != NULL", "CLAccessPaths.c", 55U);
    }
    memset(paths, 0, sizeof(*paths));
    paths->pathsArray = NULL;
    return 1;
}
unsigned char Paths_GatherRecurse(Path *spec)
{
    spec->recursive = xcalloc(0U, 8U);
    GatherRecurse(spec->recursive, spec);
    return (unsigned char)(Paths_Count(spec->recursive) != 0);
}

int Paths_CountRecurse(Paths *accessPaths)
{
    unsigned short index;
    int pathsCount;
    Path *entry;

    pathsCount = Paths_Count(accessPaths);
    for (index = 0; index < pathsCount; index++) {
        entry = Paths_GetPath(accessPaths, index);
        if (entry == NULL)
            OS_ASSERT_AT("path", "CLAccessPaths.c", 390);
        if (entry->recursive)
            pathsCount += Paths_CountRecurse(entry->recursive);
    }
    return pathsCount;
}

static void CopyRecurseSpecs(void *plugin, OSSpec **list, Paths *paths, UInt16 *count)
{
    int valid;
    Path *path;
    UInt16 idx;
    OSSpec spec;
    for (idx = 0; idx < Paths_Count(paths); idx++) {
        path = Paths_GetPath(paths, idx);
        valid = 0;
        if (path && *count != 0)
            valid = 1;
        if (!valid)
            OS_ASSERT_AT("path && *count > 0", "CLAccessPaths.c", 406);
        CLProj_MakeOSSpecFromPath(path->spec, NULL, 0, &spec, 0);
        **list = spec;
        *list += 1;
        *count -= 1;
        if (path->recursive)
            CopyRecurseSpecs(plugin, list, path->recursive, count);
    }
}

Path *Paths_FindPathSpec(Paths *table, void *value)
{
    unsigned int index;
    Path *entry;

    if (!table)
        OS_ASSERT_AT("paths != NULL", "CLAccessPaths.c", 228U);
    for (index = 0; (unsigned short)index < table->pathsCount; ++index) {
        entry = table->pathsArray[(unsigned short)index];
        if (OS_EqualPathSpec(entry->spec, value))
            return entry;
    }
    return NULL;
}

Boolean Paths_InsertPath(Paths *paths, UInt16 index, Path *path)
{
    UInt16 ni;
    int scan;
    if (Paths_GrowPaths(paths, &ni)) {
        if (index > ni)
            index = ni ? ni - 1 : 0;
        memmove(&paths->pathsArray[index + 1], &paths->pathsArray[index], (UInt32)(paths->pathsCount - index) * 4);
        paths->pathsArray[index] = path;
        path->index = index;
        for (scan = index + 1; scan < paths->pathsCount; scan++)
            paths->pathsArray[scan]->index = scan;
        return 1;
    }
    return 0;
}

static Boolean GatherRecurse(Paths *list, Path *path)
{
    DirectorySearch rf;
    OSSpec spec;
    char filename[256];
    struct {
        UInt8 value;
        char padding[3];
    } mode;
    int err;
    int files = 0;
    UInt16 ni;
    Path *sub;
    if (fn_004151f0())
        return 1;
    err = OS_OpenDir(path->spec, &rf);
    while (err == 0) {
        err = OS_ReadDir(&rf, &spec, filename, &mode.value);
        if (err == 0) {
            if (mode.value & 2) {
                if (fn_00426a80(filename)) {
                    sub = Path_New(&spec.directory);
                    sub->flags = path->flags;
                    if (!Paths_AddPath(list, sub))
                        break;
                    ni = Paths_Count(list) - 1;
                    if (!GatherRecurse(list, sub))
                        Paths_DeletePath(list, ni);
                }
            } else {
                if (!path->gathered)
                    fn_00427c40(data_0071099c, path, filename);
                files++;
                if (files % 50 == 0 && fn_004151f0())
                    return 0;
            }
        }
    }
    OS_CloseDir(&rf);
    path->gathered = 1;
    return files > 0;
}

unsigned short Paths_Count(Paths *table)
{
    if (!table) {
        OS_ASSERT_AT("paths != NULL", "CLAccessPaths.c", 175U);
    }
    return table->pathsCount;
}

Path *Paths_GetPath(Paths *table, unsigned short index)
{
    if (table == NULL)
        OS_ASSERT_AT("paths != NULL", "CLAccessPaths.c", 165U);
    if ((unsigned short)index < table->pathsCount)
        return table->pathsArray[(unsigned short)index];
    return 0U;
}

Boolean Paths_RemovePath(Paths *paths, UInt16 index)
{
    int scan;
    if (index >= paths->pathsCount)
        return 0;
    memmove(&paths->pathsArray[index], &paths->pathsArray[index + 1], (paths->pathsCount - index - 1) * sizeof(*paths->pathsArray));
    paths->pathsCount--;
    for (scan = index; scan < paths->pathsCount; scan++)
        paths->pathsArray[scan]->index = scan;
    return 1;
}

Boolean Paths_DeletePath(Paths *paths, UInt16 index)
{
    if (index >= paths->pathsCount)
        return 0;
    Path_Free(paths->pathsArray[index]);
    return Paths_RemovePath(paths, index);
}

unsigned char Paths_AddPath(Paths *ctx, void *value)
{
    UInt16 idx;
    if (Paths_GrowPaths(ctx, &idx)) {
        ctx->pathsArray[idx] = value;
        ((Path *)value)->index = idx;
        return 1;
    }
    return 0;
}

static Boolean Paths_GrowPaths(Paths *table, UInt16 *slotIndex)
{
    if (table == NULL) {
        OS_ASSERT_AT("paths != NULL", "CLAccessPaths.c", 89U);
    }
    if (table->pathsCount >= table->arraySize) {
        table->arraySize += 20U;
        table->pathsArray = xrealloc("access paths", table->pathsArray, table->arraySize << 2);
    }
    *slotIndex = table->pathsCount++;
    return 1;
}
