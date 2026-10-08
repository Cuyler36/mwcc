/* GC 3.0 Windows allocation wrappers; names and parameters from MemUtils.c STABS. */
#include "compiler/common.h"
#include "compiler/win32.h"
#include <stdio.h>
#include <string.h>

extern __declspec(noreturn) void exit(int status);

void *__stdcall xmalloc(const char *what, unsigned int size)
{
    void *ret = GlobalAlloc(0x40, size);
    if (!ret) {
        fprintf(stderr, "*** Out of memory when allocating %d bytes%s%s", size,
                what ? " for " : "", what ? what : "");
        exit(-23);
    }
    return ret;
}

void *__stdcall xcalloc(const char *what, unsigned int size)
{
    void *ret = GlobalAlloc(0x40, size);
    if (!ret) {
        fprintf(stderr, "*** Out of memory when allocating %d bytes%s%s", size,
                what ? " for " : "", what ? what : "");
        exit(-23);
    }
    return ret;
}

/* Windows-only adjacent wrappers; original names have not been recovered. */
void *__stdcall fn_004263c0(unsigned int size)
{
    return GlobalAlloc(0x40, size);
}

void *__stdcall fn_004263d0(unsigned int size)
{
    return GlobalAlloc(0x40, size);
}

void *__stdcall xrealloc(const char *what, void *old, unsigned int size)
{
    void *ret;
    if (old)
        ret = GlobalReAlloc(old, size, 2);
    else
        ret = GlobalAlloc(0x40, size);
    if (!ret) {
        fprintf(stderr, "*** Out of memory when resizing buffer to %d bytes%s%s", size,
                what ? " for " : "", what ? what : "");
        exit(-23);
    }
    return ret;
}

char *__stdcall xstrdup(const char *str)
{
    return strcpy(xmalloc(NULL, strlen(str) + 1), str);
}

void __stdcall xfree(void *ptr)
{
    if (ptr)
        GlobalFree(ptr);
}
