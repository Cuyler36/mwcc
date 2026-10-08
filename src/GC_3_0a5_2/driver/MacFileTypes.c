/* GC 3.0 Windows file type mappings; original names/types from MacFileTypes.c STABS. */
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include <string.h>
#pragma pack(push, 1)
typedef struct OSFileTypeMapping {
    UInt32 mactype;
    const char *magic;
    char length, executable;
    const char *mimetype;
} OSFileTypeMapping;
typedef struct OSFileTypeMappingList {
    SInt16 numMappings;
    OSFileTypeMapping *mappings;
} OSFileTypeMappingList;
#pragma pack(pop)
typedef struct OSFileTypeMappings {
    OSFileTypeMappingList *mappingList;
    struct OSFileTypeMappings *next;
} OSFileTypeMappings;
typedef struct OSSpec { char path[260], name[256]; } OSSpec;
typedef struct OSType { int perm; } OSType;
static OSFileTypeMappings *defaultList;
static OSFileTypeMappings **fmList = &defaultList;
int (*__OS_ExtendedGetMacFileTypeHook)(const OSSpec *, UInt32 *);
extern OSType OS_TEXTTYPE;
extern void *__stdcall fn_004263c0(unsigned int);
extern int __stdcall OS_SetFileType(const OSSpec *, const OSType *);
extern int __stdcall OS_Open(const OSSpec *, int, int *);
extern int __stdcall OS_GetSize(int, UInt32 *);
extern int __stdcall OS_Read(int, void *, UInt32 *);
extern int __stdcall OS_Close(int);
extern int __stdcall MacSpecs_MakeResourceForkSpec(const OSSpec *, OSSpec *, int);
void __stdcall OS_AddFileTypeMappingList(OSFileTypeMappings **list, OSFileTypeMappingList *entry)
{
    OSFileTypeMappings **scan;
    if (!list) list = fmList;
    scan = list;
    while (*scan) scan = &(*scan)->next;
    *scan = fn_004263c0(sizeof(OSFileTypeMappings));
    if (!*scan) OS_ASSERT_AT("*scan != NULL", "MacFileTypes.c", 0x24);
    (*scan)->mappingList = entry;
    (*scan)->next = NULL;
}
void __stdcall OS_MacType_To_OSType(UInt32 mactype, OSType *type)
{
    OSFileTypeMappings *list;
    OSFileTypeMappingList *scan;
    int idx;
    list = *fmList;
    while (list) {
        scan = list->mappingList;
        idx = 0;
        while (idx < scan->numMappings) {
            if (mactype == scan->mappings[idx].mactype) {
                memset(type, 0, sizeof(*type));
                return;
            }
            idx++;
        }
        list = list->next;
    }
    *type = OS_TEXTTYPE;
}
int __stdcall OS_SetMacFileType(const OSSpec *spec, UInt32 mactype)
{
    OSType type;
    OS_MacType_To_OSType(mactype, &type);
    return OS_SetFileType(spec, &type);
}
UInt8 __stdcall OS_GetMacFileTypeMagic(const char *buffer, int count, UInt32 *mactype)
{
    OSFileTypeMappingList *scan;
    int comparison;
    int idx;
    OSFileTypeMappings *list;
    OSFileTypeMappings **head;
    *mactype = 0;
    head = fmList;
    list = *head;
    while (list) {
        scan = list->mappingList;
        idx = 0;
        while (idx < scan->numMappings) {
            if (scan->mappings[idx].length <= count && scan->mappings[idx].magic != NULL) {
                comparison = memcmp(buffer, scan->mappings[idx].magic, scan->mappings[idx].length);
                if (comparison == 0) {
                    *mactype = scan->mappings[idx].mactype;
                    return 1;
                }
            }
            idx = idx + 1;
        }
        list = list->next;
    }
    return 0;
}
int __stdcall OS_GetMacFileType(const OSSpec *spec, UInt32 *mactype)
{
    int ref;
    int err;
    char buffer[32];
    UInt32 count, flen = 0;
    OSSpec rsrc;
    UInt32 rsize;
    int rref;
    err = OS_Open(spec, 0, &ref);
    if (!err) {
        OS_GetSize(ref, &flen);
        count = 32;
        err = OS_Read(ref, buffer, &count);
        OS_Close(ref);
        if (!err && count && OS_GetMacFileTypeMagic(buffer, count, mactype)) return 0;
    }
    if (__OS_ExtendedGetMacFileTypeHook == NULL || __OS_ExtendedGetMacFileTypeHook(spec, mactype) == 0) {
        if (flen == 0) {
            err = MacSpecs_MakeResourceForkSpec(spec, &rsrc, 0);
            if (err == 0) {
                err = OS_Open(&rsrc, 0, &rref);
                if (err == 0) {
                    OS_GetSize(rref, &rsize);
                    OS_Close(rref);
                    if (rsize != 0) { *mactype = 0x72737263; return 0; }
                }
            }
        }
        *mactype = 0x54455854;
    }
    return 0;
}

int __stdcall OS_SetMacFileCreatorAndType(const OSSpec *spec, UInt32 creator, UInt32 mactype)
{
    return OS_SetMacFileType(spec, mactype);
}


