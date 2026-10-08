#define CERROR_FILE "MacSpecs.c"
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include <string.h>
#include <stdio.h>

typedef unsigned long DWORD;
typedef struct OSSpec { struct { char path[260]; } directory; char name[256]; } OSSpec;
#pragma pack(push, 1)
typedef struct FSSpec { short vRefNum; int parID; unsigned char name[256]; } FSSpec;
#pragma pack(pop)
union MacSpecParent { struct MacSpecEntry *entry; struct NameRegistryEntry *registry; };
typedef struct MacSpecEntry { char *name; unsigned int index; union MacSpecParent parent; struct MacSpecEntry *children; struct MacSpecEntry *next; } MacSpecEntry;
typedef struct NameRegistryEntry { unsigned short id; MacSpecEntry root; struct NameRegistryEntry *next; } NameRegistryEntry;
static unsigned int lastDirID = 3;
static unsigned int lastVolRef = 2;
static char stname[260];
static char stdir[260];
static char stvol[64];
static unsigned int dirMapRows;
static MacSpecEntry **dirIDMap[256];
static NameRegistryEntry *vols;
extern char STSbuf[];
extern void *__stdcall fn_004263c0(unsigned int);
extern void *__stdcall fn_004263d0(unsigned int);
extern int __stdcall OS_EqualPath(char *, char *);
extern char *__stdcall OS_PathSpecToString(char *, char *, unsigned int);
extern char *__stdcall OS_GetDirPtr(char *);
extern char *__stdcall OS_NameSpecToString(char *, char *, unsigned int);
extern int __stdcall OS_GetCWD(char *);
extern int __stdcall OS_MakeNameSpec(char *, char *);
extern int __stdcall OS_MakeSpec2(char *, char *, OSSpec *);
extern int __stdcall OS_Status(OSSpec *);
extern int __stdcall OS_Mkdir(OSSpec *);
extern int __stdcall OS_IsFile(OSSpec *);
extern char *__stdcall OS_SpecToString(OSSpec *, char *, unsigned int);
extern void __stdcall c2pstrcpy(unsigned char *, char *);
extern void __stdcall p2cstrcpy(char *, unsigned char *);
__declspec(dllimport) int __stdcall SetFileAttributesA(const char *, DWORD);
#pragma auto_inline off

static struct NameRegistryEntry *FindOrAddVolRef(struct NameRegistryEntry **entries, char *name)
{
    NameRegistryEntry *entry;
    int sz;

    for (; *entries != NULL; entries = &(*entries)->next) {
        if (OS_EqualPath(name, (*entries)->root.name) != 0) {
            return *entries;
        }
    }
    if (lastVolRef >= 0x100) {
        return NULL;
    }
    entry = (NameRegistryEntry *)fn_004263c0(sizeof(NameRegistryEntry));
    if (entry == NULL) {
        return NULL;
    }
    entry->next = NULL;
    entry->id = lastVolRef;
    lastVolRef = lastVolRef + 1;
    sz = strlen(name) + 1;
    entry->root.name = (char *)fn_004263c0(sz);
    if (entry->root.name == NULL) {
        return NULL;
    }
    strcpy(entry->root.name, name);
    entry->root.index = 2;
    entry->root.parent.registry = entry;
    entry->root.children = NULL;
    entry->root.next = NULL;
    *entries = entry;
    return entry;
}

static int AddDirMapEntry(MacSpecEntry *entry)
{
    unsigned int directory = entry->index >> 8;
    unsigned int slot = entry->index & 0xff;
    if (directory >= dirMapRows) {
        do {
            if (directory >= 0x100) {
                fprintf(stderr, "Fatal error:  too many directories referenced, out of memory\n");
                return 0;
            }
            dirIDMap[directory] = fn_004263d0(0x400);
            if (dirIDMap[directory] == NULL) {
                return 0;
            }
            ++dirMapRows;
        } while (directory >= dirMapRows);
    }
    dirIDMap[directory][slot] = entry;
    return 1;
}

static struct MacSpecEntry *FindDirMapEntry(unsigned int dirID)
{
    unsigned int index = dirID >> 8;
    unsigned int entryIndex = dirID & 0xff;
    if (dirID == 2U)
        OS_ASSERT_AT("dirID != 2", "MacSpecs.c", 195U);
    if (index >= dirMapRows)
        return NULL;
    return dirIDMap[index][entryIndex];
}

/* A named entry and the table that owns its entry chain. */
static MacSpecEntry *FindOrAddDirRef(MacSpecEntry *table, char *name)
{
    MacSpecEntry **link;
    int result;
    MacSpecEntry *entry;

    for (link = &table->children; *link != NULL; link = &(*link)->next) {
        result = OS_EqualPath(name, (*link)->name);
        if (result != 0) {
            return *link;
        }
    }
    if (lastDirID >= 0x10000) {
        return NULL;
    }
    result = strlen(name) + 1;
    entry = (MacSpecEntry *)fn_004263c0(sizeof(MacSpecEntry));
    if (entry == NULL) {
        return NULL;
    }
    entry->name = (char *)fn_004263c0(result);
    if (entry->name == NULL) {
        return NULL;
    }
    strcpy(entry->name, name);
    entry->children = NULL;
    entry->next = NULL;
    entry->index = lastDirID;
    lastDirID = lastDirID + 1;
    result = AddDirMapEntry(entry);
    if (result == 0) {
        return NULL;
    }
    entry->parent.entry = table;
    *link = entry;
    return entry;
}

static int FindOrAdd(char *spec, unsigned int *typePtr, unsigned int *offsetPtr)
{
    char str[0x104];
    char name[0x40];
    char buf[0x104];
    char *p;
    NameRegistryEntry *node;
    MacSpecEntry *rec;
    char *tok;

    if (!OS_PathSpecToString(spec, buf, 0x104))
        return 0;
    if (buf[0] == 0)
        return 0;
    p = OS_GetDirPtr(buf);
    strncpy(name, buf, p - buf);
    name[p - buf] = '\0';
    strcpy(str, p);
    node = FindOrAddVolRef(&vols, name);
    if (node == NULL)
        return 0;
    *typePtr = node->id;
    rec = &node->root;
    p = str + 1;
    if (str[0] != '\\')
        OS_ASSERT_AT("*pb == OS_PATHSEP", "MacSpecs.c", 0x128);
    while (*p != '\0') {
        tok = p;
        while (*p != '\0' && *p != '\\')
            p++;
        if (*p == '\\') {
            *p = '\0';
            p++;
        }
        rec = FindOrAddDirRef(rec, tok);
        if (rec == NULL)
            return 0;
    }
    *offsetPtr = rec->index;
    return 1;
}

static void StepVolDir(int *id, int *kind, unsigned int **result)
{
    NameRegistryEntry *node;

    if (*id == 1) {
        *result = NULL;
    } else if (*kind == 2U) {
        node = vols;
        while (node != NULL && node->id != *id) {
            node = node->next;
        }
        if (node != NULL) {
            *result = (unsigned int *)&node->root;
            *id = 1;
            *kind = 1;
        } else {
            *result = NULL;
        }
    } else {
        *result = (unsigned int *)FindDirMapEntry(*kind);
        if (*result != NULL) {
            MacSpecEntry *entry = (MacSpecEntry *)*result;
            MacSpecEntry *parent = entry->parent.entry;
            *kind = parent->index;
        }
    }
}

static int ResolvePath(char *input, unsigned int *firstResult, unsigned int *secondResult)
{
    if (FindOrAdd(input, firstResult, secondResult) != 0) {
        *firstResult = -*firstResult;
        return 1;
    }
    *firstResult = 0;
    *secondResult = 0;
    return 0;
}

static int ResolveVolDir(int a, int b, char *out1, char *out2)
{
    int n;
    int len;
    MacSpecEntry *arr[256];
    MacSpecEntry *val;
    char *p;

    a = -a;
    n = 0;
    do {
        StepVolDir(&a, &b, (unsigned int **)&val);
        if (val != NULL) {
            arr[n] = val;
            n++;
        }
    } while (val != NULL);

    if (n != 0) {
        strcpy(out1, arr[--n]->name);
    } else {
        *out1 = 0;
        *out2 = 0;
        return 0;
    }

    p = out2;
    *p++ = '\\';
    while (n--) {
        len = strlen(arr[n]->name);
        if (p - out2 + len + 1 > 0x104) {
            *p = 0;
            return 0;
        }
        memcpy(p, arr[n]->name, len);
        p += len;
        *p++ = '\\';
    }
    *p = 0;
    return 1;
}

int __stdcall OS_OSPathSpec_To_VolDir(char *text, unsigned short *value, unsigned int *offset)
{
    unsigned int parsedValue;
    unsigned int parsedOffset;

    if (ResolvePath(text, &parsedValue, &parsedOffset)) {
        *value = parsedValue;
        *offset = parsedOffset;
        return 0;
    }
    *value = 0;
    *offset = 0;
    return 3;
}

int __stdcall OS_OSSpec_To_FSSpec(char *input, FSSpec *output)
{
    UInt16 volumeRef;
    unsigned int directoryId;
    int status;

    status = OS_OSPathSpec_To_VolDir(input, &volumeRef, &directoryId);
    output->vRefNum = volumeRef;
    output->parID = directoryId;
    if (status != 0) {
        return status;
    }
    if (OS_NameSpecToString(input + 0x104, stname, 0x40) == NULL) {
        return 0x6f;
    }
    c2pstrcpy(output->name, stname);
    return 0;
}

DWORD __stdcall OS_VolDir_To_OSPathSpec(short kind, int value, char *path)
{
    unsigned int directoryLength;
    unsigned int nameLength;
    DWORD result;

    if (kind == 0 || value == 0) {
        result = OS_GetCWD(path);
        if (result != 0) {
            return result;
        }
    } else {
        if (ResolveVolDir(kind, value, stvol, stdir) == 0) {
            return 3;
        }
        directoryLength = strlen(stvol);
        nameLength = strlen(stdir);
        if ((int)(directoryLength + nameLength) < 0x104) {
            memcpy(path, stvol, directoryLength);
            memcpy(path + directoryLength, stdir, 1 + nameLength);
        }
    }
    return 0;
}

/* Unused lookup request declaration removed: no accesses or allocations. */
int __stdcall OS_FSSpec_To_OSSpec(FSSpec *record, char *buffer)
{
    int result = OS_VolDir_To_OSPathSpec(record->vRefNum, record->parID, buffer);
    if (result != 0) {
        return result;
    }
    p2cstrcpy(stname, record->name);
    return OS_MakeNameSpec(stname, buffer + 0x104);
}

int __stdcall OS_GetRsrcOSSpec(OSSpec *source, OSSpec *destination, unsigned char retryOnError)
{
    char pathBuffer[0x104];
    DWORD error;

    OS_PathSpecToString(source->directory.path, pathBuffer, 0x104);

    error = OS_MakeSpec2(pathBuffer, "RESOURCE.FRK", destination);
    if (error != 0)
        return error;

    error = OS_Status(destination);
    if (error != 0) {
        if (retryOnError != 0) {
            error = OS_Mkdir(destination);
            if (error != 0)
                return error;
            SetFileAttributesA(OS_SpecToString(destination, STSbuf, 0x104), 2);
        } else {
            return error;
        }
        error = OS_MakeSpec2(pathBuffer, "RESOURCE.FRK", destination);
        if (error != 0)
            return error;
    } else {
        if (OS_IsFile(destination) != 0)
            return 0x10b;
    }

    error = OS_MakeNameSpec(OS_NameSpecToString(source->name, STSbuf, 0x104), destination->name);
    if (error == 0)
        return 0;
    return error;
}
