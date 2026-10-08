#define CERROR_FILE "FileHandles.c"
#include "compiler/common.h"
#include "driver/Memory.h"

typedef struct FileHandleSpec { char path[260]; char name[256]; } FileHandleSpec;
typedef struct FileHandle {
    FileHandleSpec spec;
    MemBuffer hand;
    Boolean loaded;
    Boolean changed;
    Boolean writeable;
} FileHandle;

extern UInt32 data_00710104;
extern int __stdcall OS_Open(FileHandleSpec *, Boolean, int *);
extern int __stdcall OS_Close(int);
extern int __stdcall OS_GetSize(int, UInt32 *);
extern int __stdcall OS_Read(int, void *, UInt32 *);
extern int __stdcall OS_Write(int, void *, UInt32 *);
extern int __stdcall OS_Delete(FileHandleSpec *);
extern int __stdcall OS_Create(FileHandleSpec *, UInt32 *);
extern int __stdcall OS_NewHandle(UInt32, MemBuffer *);
extern int __stdcall OS_ResizeHandle(MemBuffer *, UInt32);
extern int __stdcall OS_FreeHandle(MemBuffer *);
extern int __stdcall OS_GetHandleSize(MemBuffer *, UInt32 *);
extern Boolean __stdcall OS_ValidHandle(MemBuffer *);
extern void *__stdcall OS_LockHandle(MemBuffer *);
extern void __stdcall OS_UnlockHandle(MemBuffer *);
extern int __stdcall OS_CopyHandle(MemBuffer *, MemBuffer *);
#pragma auto_inline off

static int OS_LoadFileHandle(FileHandle *hand)
{
    int err;
    int ref;
    UInt32 sz;
    void *buffer;
    hand->loaded = 0;
    err = OS_Open(&hand->spec, 0, &ref);
    if (err == 0) {
        err = OS_GetSize(ref, &sz);
        if (err == 0) {
            err = OS_ResizeHandle(&hand->hand, sz);
            if (err == 0) {
                buffer = OS_LockHandle(&hand->hand);
                err = OS_Read(ref, buffer, &sz);
                if (err == 0) {
                    hand->loaded = 1;
                    hand->changed = 0;
                }
                OS_UnlockHandle(&hand->hand);
            }
        }
        OS_Close(ref);
    }
    return err;
}

static int OS_WriteFileHandle(FileHandle *hand)
{
    int err;
    int ref;
    UInt32 sz;
    void *buffer;
    if (!hand->loaded && !hand->changed)
        return 0;
    OS_Delete(&hand->spec);
    err = OS_Create(&hand->spec, &data_00710104);
    if (err) goto done;
    err = OS_Open(&hand->spec, 2, &ref);
    if (err) goto done;
    err = OS_GetHandleSize(&hand->hand, &sz);
    if (err) goto done;
    buffer = OS_LockHandle(&hand->hand);
    err = OS_Write(ref, buffer, &sz);
    if (err == 0) hand->changed = 0;
    OS_UnlockHandle(&hand->hand);
    OS_Close(ref);
done:
    return err;
}

int __stdcall OS_NewFileHandle(FileHandleSpec *spec, MemBuffer *src, Boolean writeable, FileHandle *hand)
{
    int err;
    if (!writeable && src)
        return 12;
    hand->spec = *spec;
    hand->writeable = writeable;
    if (src) {
        err = OS_CopyHandle(src, &hand->hand);
        if (err) return err;
    } else {
        err = OS_NewHandle(0, &hand->hand);
        if (err) return err;
        err = OS_LoadFileHandle(hand);
        goto done;
    }
    hand->changed = 1;
    hand->loaded = 1;
done:
    return err;
}

int __stdcall OS_LockFileHandle(FileHandle *hand, void **ptr, UInt32 *size)
{
    *size = 0;
    if (!OS_ValidHandle(&hand->hand))
        return 8;
    *ptr = OS_LockHandle(&hand->hand);
    OS_GetHandleSize(&hand->hand, size);
    return 0;
}

int __stdcall OS_FreeFileHandle(FileHandle *hand)
{
    int err;
    if (hand->writeable && hand->changed) {
        err = OS_WriteFileHandle(hand);
        if (err) return err;
    }
    if (!OS_ValidHandle(&hand->hand))
        return 8;
    err = OS_FreeHandle(&hand->hand);
    if (err) return err;
    hand->loaded = 0;
    return 0;
}
