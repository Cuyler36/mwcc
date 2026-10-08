/* CLTarg.c canonical functions from the GC 3.0 Mac STABS map; Windows ABI. */
#include "compiler/common.h"
#include <string.h>

typedef struct OSPathSpec { char s[260]; } OSPathSpec;
typedef struct OSSpec { OSPathSpec path; char name[256]; } OSSpec;
typedef struct CLTargetInfo {
    UInt32 targetCPU, targetOS;
    SInt16 outputType, linkType;
    UInt8 canRun, canDebug;
    OSSpec outfile, symfile, runfile, linkAgainstFile;
} CLTargetInfo;
typedef struct Segments { void *segsArray; UInt16 arraySize, segsCount; } Segments;
typedef struct TargetOverlays { void *groups, *lastgrp; long grpcnt; } TargetOverlays;
typedef struct Files { void *fileList; long fileCount; void *fileMap; } Files;
typedef struct Incls {
    void *targ;
    long numincls, maxincls;
    void *files;
    long buflen, bufpos;
    char *buffer;
    void *allPaths;
} Incls;
typedef struct Paths { void *pathsArray; UInt16 arraySize, pathsCount; } Paths;
/* Windows-only cache entry; original type and member names are unavailable. */
typedef struct TargetCacheEntry {
    struct TargetCacheEntry *next;
    void *value;
} TargetCacheEntry;
typedef struct Target {
    struct { UInt32 linesCompiled, codeSize, iDataSize, uDataSize; } info;
    CLTargetInfo *targetinfo;
    struct { Segments segs; TargetOverlays overlays; } linkage;
    long linkmodel;
    Files files, pchs;
    Incls incls;
    Paths sysPaths, userPaths;
    UInt32 lang, cpu, os;
    char targetName[256];
    Plugin *preLinker, *linker, *postLinker;
    long preLinkerDropinFlags, linkerDropinFlags, postLinkerDropinFlags;
    OSPathSpec outputDirectory;
    OSPathSpec workingDirectory; /* Windows field meaning inferred from copy of CWD. */
    char unknown3a0[260];
    void *virtualFiles;
    TargetCacheEntry *cache[997];
    struct Target *next;
} Target;
extern void *__stdcall xcalloc(const char *, unsigned int);
extern void __stdcall xfree(void *);
extern int __stdcall OS_GetCWD(OSPathSpec *);
extern Boolean Segments_Initialize(Segments *);
extern Boolean Segments_Terminate(Segments *);
extern Boolean Overlays_Initialize(TargetOverlays *);
extern Boolean Overlays_Terminate(TargetOverlays *);
extern Boolean Files_Initialize(Files *);
extern Boolean Files_Terminate(Files *);
extern Boolean VFiles_Initialize(void **);
extern void VFiles_Terminate(void **);
extern Boolean Paths_Initialize(Paths *);
extern Boolean Paths_Terminate(Paths *);
extern Boolean Incls_Initialize(Incls *, Target *);
extern void Incls_Terminate(Incls *);
void fn_004270b0(Target *);
void fn_004270d0(Target *);

Target *Target_New(char *name, UInt32 cpu, UInt32 os, UInt32 lang)
{
    Target *targ;
    targ = xcalloc("target", sizeof(Target));
    strncpy(targ->targetName, name, sizeof(targ->targetName));
    targ->targetinfo = xcalloc("target info", sizeof(CLTargetInfo));
    targ->cpu = cpu;
    targ->os = os;
    targ->lang = lang;
    OS_GetCWD(&targ->outputDirectory);
    targ->workingDirectory = targ->outputDirectory;
    fn_004270b0(targ);
    Segments_Initialize(&targ->linkage.segs);
    Overlays_Initialize(&targ->linkage.overlays);
    Files_Initialize(&targ->files);
    Files_Initialize(&targ->pchs);
    VFiles_Initialize(&targ->virtualFiles);
    Paths_Initialize(&targ->sysPaths);
    Paths_Initialize(&targ->userPaths);
    Incls_Initialize(&targ->incls, targ);
    return targ;
}

void Target_Free(Target *targ)
{
    Segments_Terminate(&targ->linkage.segs);
    Overlays_Terminate(&targ->linkage.overlays);
    fn_004270d0(targ);
    Paths_Terminate(&targ->sysPaths);
    Paths_Terminate(&targ->userPaths);
    Files_Terminate(&targ->files);
    Files_Terminate(&targ->pchs);
    VFiles_Terminate(&targ->virtualFiles);
    Incls_Terminate(&targ->incls);
    xfree(targ->targetinfo);
    xfree(targ);
}

/* Windows-only helpers; original names are absent from the Mac map. */
void fn_004270b0(Target *targ)
{
    memset(targ->cache, 0, sizeof(targ->cache));
}

void fn_004270d0(Target *targ)
{
    int index;
    TargetCacheEntry *scan, *next;
    for (index = 0; index < 997; index++) {
        scan = targ->cache[index];
        while (scan) {
            next = scan->next;
            if (scan->value)
                xfree(scan->value);
            xfree(scan);
            scan = next;
        }
    }
}

void Targets_Term(Target *list)
{
    Target *scan, *next;
    scan = list;
    if (list) {
        do {
            next = scan->next;
            Target_Free(scan);
            scan = next;
        } while (next);
    }
}

void Target_Add(Target **list, Target *targ)
{
    Target **scan;
    for (scan = list; *scan; scan = &(*scan)->next) {
    }
    *scan = targ;
}
