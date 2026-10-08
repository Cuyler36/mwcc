#define CERROR_FILE "CLPrefs.c"
#include "compiler/common.h"
#include "driver/Memory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern __declspec(noreturn) void exit(int);
typedef struct PrefPanel { char *name; MemBuffer data; struct PrefPanel *next; } PrefPanel;
static PrefPanel *panellist;
extern char data_00702f34;
extern void (*data_00710b2c)(char *);
extern void *__stdcall xmalloc(const char *, unsigned int);
extern char *__stdcall xstrdup(const char *);
extern void __stdcall xfree(void *);
extern int __stdcall OS_NewHandle(UInt32, MemBuffer *);
extern int __stdcall OS_FreeHandle(MemBuffer *);
extern void *__stdcall OS_LockHandle(MemBuffer *);
extern void __stdcall OS_UnlockHandle(MemBuffer *);
extern int __stdcall OS_GetHandleSize(MemBuffer *, UInt32 *);
extern unsigned int __stdcall CLFileOps_CopyMemBuffer(MemBuffer *, MemBuffer *);
extern unsigned char CLErrors_EmitDiagnostic(volatile int, ...);
extern void CLIO_FormatAndDispatchText(char *, ...);
extern int __stdcall CLIO_CompareStringsIgnoreCase(char *, char *);
#pragma auto_inline off

PrefPanel *PrefPanel_New(char *name, void *initdata, unsigned int initdatasize)
{
    PrefPanel *pnl;
    void *ptr;
    pnl = xmalloc(NULL, sizeof(PrefPanel));
    if (!pnl)
        return pnl;
    pnl->name = xstrdup(name);
    if (OS_NewHandle(initdatasize, &pnl->data)) {
        fprintf(stderr, "\n*** Out of memory\n");
        exit(-23);
    }
    ptr = OS_LockHandle(&pnl->data);
    if (initdata)
        memcpy(ptr, initdata, initdatasize);
    else
        memset(ptr, 0, initdatasize);
    OS_UnlockHandle(&pnl->data);
    pnl->next = NULL;
    return pnl;
}

MemBuffer *PrefPanel_GetHandle(PrefPanel *panel, MemBuffer *copy)
{
    if (CLFileOps_CopyMemBuffer(&panel->data, copy) == 0)
        return copy;
    return NULL;
}

int PrefPanel_PutHandle(PrefPanel *panel, MemBuffer *data)
{
    return OS_FreeHandle(&panel->data) == 0 && CLFileOps_CopyMemBuffer(data, &panel->data) == 0;
}

void Prefs_Initialize(void)
{
    panellist = NULL;
}

void Prefs_Terminate(void)
{
    PrefPanel *scan;
    PrefPanel *next;
    for (scan = panellist; scan; scan = next) {
        xfree(scan->name);
        OS_FreeHandle(&scan->data);
        next = scan->next;
        xfree(scan);
    }
    panellist = NULL;
}

Boolean Prefs_AddPanel(PrefPanel *panel)
{
    PrefPanel **scan;
    UInt32 size;
    scan = &panellist;
    while (*scan) {
        if (strcmp((*scan)->name, panel->name) == 0) {
            CLErrors_EmitDiagnostic(0x5c, panel->name);
            return 0;
        }
        scan = &(*scan)->next;
    }
    if (data_00702f34) {
        OS_GetHandleSize(&panel->data, &size);
        CLIO_FormatAndDispatchText("Defining/adding pref panel '%s' (size=%d)\n", panel->name, size);
    }
    *scan = panel;
    return 1;
}

PrefPanel *Prefs_FindPanel(char *name)
{
    PrefPanel *scan;
    for (scan = panellist; scan; scan = scan->next) {
        if (CLIO_CompareStringsIgnoreCase(scan->name, name) == 0)
            break;
    }
    return scan;
}

int fn_00426220(char *name, MemBuffer *data)
{
    PrefPanel *panel;
    UInt32 size;
    void *ptr;
    panel = Prefs_FindPanel(name);
    if (panel) {
        if (!PrefPanel_PutHandle(panel, data))
            return 0;
    } else {
        OS_GetHandleSize(data, &size);
        ptr = OS_LockHandle(data);
        panel = PrefPanel_New(name, ptr, size);
        OS_UnlockHandle(data);
        if (!panel || !Prefs_AddPanel(panel))
            return 0;
    }
    if (data_00710b2c)
        data_00710b2c(name);
    return 1;
}
