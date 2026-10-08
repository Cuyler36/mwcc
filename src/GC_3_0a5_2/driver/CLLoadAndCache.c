#define CERROR_FILE "CLLoadAndCache.c"
#include "compiler/common.h"
#include "driver/Memory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern __declspec(noreturn) void exit(int);
typedef struct LoadOSSpec { char path[260]; char name[256]; } LoadOSSpec;
typedef struct LoadPluginDesc { unsigned char reserved[8]; UInt32 flags; } LoadPluginDesc;
extern MemBuffer *CachedIncludeFile(LoadOSSpec *, Boolean *);
extern void CacheIncludeFile(LoadOSSpec *, MemBuffer *, Boolean);
extern LoadPluginDesc *CLPlugins_GetPluginDesc(void *);
extern int __stdcall MacFileTypes_GetFileType(LoadOSSpec *, UInt32 *);
extern int __stdcall OS_Open(LoadOSSpec *, Boolean, SInt32 *);
extern int __stdcall OS_GetSize(SInt32, UInt32 *);
extern int __stdcall OS_Read(SInt32, void *, UInt32 *);
extern int __stdcall OS_Close(SInt32);
extern int __stdcall OS_NewHandle(UInt32, MemBuffer *);
extern int __stdcall OS_FreeHandle(MemBuffer *);
extern char *__stdcall OS_LockHandle(MemBuffer *);
extern void __stdcall OS_UnlockHandle(MemBuffer *);
extern int __stdcall OS_GetHandleSize(MemBuffer *, UInt32 *);
extern void *__stdcall xmalloc(const char *, unsigned int);
extern void __stdcall xfree(void *);
#pragma auto_inline off

short FixTextHandle(MemBuffer *txt)
{
    char *tptr;
    char *scan;
    UInt32 tlen;
    tptr = OS_LockHandle(txt);
    OS_GetHandleSize(txt, &tlen);
    scan = tptr;
    while (scan < tptr + tlen) {
        if (*scan == '\r') {
            if (scan[1] == '\n') scan += 2;
            else scan++;
        } else if (*scan == '\n') {
            *scan++ = '\r';
        } else {
            scan++;
        }
    }
    OS_UnlockHandle(txt);
    return 0;
}

int LoadAndCacheFile(void *plugin, LoadOSSpec *spec, MemBuffer **texthandle, Boolean *precomp)
{
    MemBuffer *h;
    char *ptr;
    int err;
    UInt32 mactype;
    SInt32 refnum;
    UInt32 ltxtlen;
    *texthandle = CachedIncludeFile(spec, precomp);
    if (*texthandle)
        return 0;
    *precomp = MacFileTypes_GetFileType(spec, &mactype) == 0 && mactype != 0x54455854;
    *texthandle = NULL;
    err = OS_Open(spec, 0, &refnum);
    if (err)
        return err;
    err = OS_GetSize(refnum, &ltxtlen);
    if (err)
        return err;
    h = xmalloc(NULL, sizeof(MemBuffer));
    if (OS_NewHandle(ltxtlen + 1, h)) {
        fprintf(stderr, "\n*** Out of memory\n");
        exit(-23);
    }
    ptr = OS_LockHandle(h);
    err = OS_Read(refnum, ptr, &ltxtlen);
    if (err) {
        OS_FreeHandle(h);
        xfree(h);
        OS_Close(refnum);
        return err;
    }
    OS_Close(refnum);
    ptr[ltxtlen] = 0;
    OS_UnlockHandle(h);
    if (!*precomp && !(CLPlugins_GetPluginDesc(plugin)->flags & 0x80))
        FixTextHandle(h);
    CacheIncludeFile(spec, h, *precomp);
    *texthandle = h;
    return 0;
}

void CopyFileText(MemBuffer *src, void **text, UInt32 *textsize)
{
    void *ptr;
    OS_GetHandleSize(src, textsize);
    *text = xmalloc(NULL, *textsize);
    ptr = OS_LockHandle(src);
    memcpy(*text, ptr, *textsize);
    *textsize -= 1;
    OS_UnlockHandle(src);
}
