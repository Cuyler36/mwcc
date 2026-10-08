/* Original CLOverlays.c names and records recovered from GC 3.0 STABS. */
#define CERROR_FILE "CLOverlays.c"
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include <string.h>

typedef struct OvlAddr {
    unsigned long lo, hi;
} OvlAddr;
typedef struct Overlay {
    char name[256];
    long *list;
    long cnt, max;
    struct Overlay *next;
} Overlay;
typedef struct OvlGroup {
    char name[256];
    OvlAddr addr;
    Overlay *olys, *lastoly;
    long olycnt;
    struct OvlGroup *next;
} OvlGroup;
struct Overlays {
    OvlGroup *groups, *lastgrp;
    long grpcnt;
};
extern void *__stdcall xmalloc(const char *what, unsigned int size);
extern void *__stdcall xrealloc(const char *what, void *ptr, unsigned int size);
extern void __stdcall xfree(void *ptr);
extern void CLInternalError(const char *file, int line, const char *format, ...);
Boolean Overlays_Initialize(Overlays *this);
Boolean Overlays_Terminate(Overlays *list);
Boolean Overlays_AddOvlGroup(Overlays *list, OvlGroup *entry, long *index);
OvlGroup *Overlays_GetOvlGroup(Overlays *list, long index);
long Overlays_CountGroups(Overlays *list);
Overlay *Overlays_GetOverlayInGroup(Overlays *overlay, long name, long value);
long Overlays_GetFileInOverlay(Overlays *overlay, long groupName, long groupIndex, long valueIndex);
OvlGroup *OvlGroup_New(const char *name, OvlAddr overlayValues);
void OvlGroup_Delete(OvlGroup *list);
Boolean OvlGroup_AddOverlay(OvlGroup *self, Overlay *overlay, long *index);
Overlay *OvlGroup_GetOverlay(OvlGroup *list, long index);
long OvlGroup_CountOverlays(OvlGroup *record);
Overlay *Overlay_New(const char *name);
void Overlay_Delete(Overlay *overlay);
UInt8 Overlay_AddFile(Overlay *table, long entry, long *entryIndex);
long Overlay_GetFile(Overlay *table, long index);
long Overlay_CountFiles(Overlay *record);

Boolean Overlays_Initialize(Overlays *this)
{
    OvlGroup *grp;
    struct Overlay *ovl;
    OvlAddr addr;
    long idx;

    OS_ASSERT(24, this);
    this->groups = NULL;
    this->lastgrp = NULL;
    this->grpcnt = 0;
    addr.lo = addr.hi = 0;
    grp = OvlGroup_New("main_application", addr);
    if (!grp)
        return 0;
    ovl = Overlay_New("MAIN");
    if (!ovl)
        return 0;
    OvlGroup_AddOverlay(grp, ovl, &idx);
    OS_ASSERT(42, idx==0);
    Overlays_AddOvlGroup(this, grp, &idx);
    OS_ASSERT(45, idx==0);
    return 1;
}

Boolean OvlGroup_AddOverlay(OvlGroup *self, struct Overlay *overlay, long *index)
{
    if (self == NULL) {
        OS_ASSERT_AT("this", "CLOverlays.c", 211U);
    }
    if (overlay == NULL) {
        OS_ASSERT_AT("oly", "CLOverlays.c", 212U);
    }
    if (self->lastoly == NULL) {
        self->olys = overlay;
    } else {
        self->lastoly->next = overlay;
    }
    self->lastoly = overlay;
    if (index != NULL) {
        *index = self->olycnt;
    }
    self->olycnt++;
    return 1;
}

long Overlays_CountGroups(struct Overlays *list)
{
    struct OvlGroup *record;
    int count;
    count = 0;
    if (!list)
        OS_ASSERT_AT("this", "CLOverlays.c", 112U);
    record = list->groups;
    while (record) {
        record = record->next;
        count += 1;
    }
    return count;
}

long Overlays_GetFileInOverlay(Overlays *overlay, long groupName,
                                                       long groupIndex, long valueIndex)
{
    struct Overlay *allocation;
    if (!overlay)
        OS_ASSERT_AT("this", "CLOverlays.c", 160U);
    allocation = Overlays_GetOverlayInGroup(overlay, groupName, groupIndex);
    if (allocation)
        return Overlay_GetFile(allocation, valueIndex);
    return 4294967295U;
}

struct Overlay *Overlays_GetOverlayInGroup(Overlays *overlay, long name, long value)
{
    struct OvlGroup *entry;
    if (overlay == 0U)
        OS_ASSERT_AT("this", "CLOverlays.c", 144U);
    entry = Overlays_GetOvlGroup(overlay, name);
    if (entry != 0U)
        return OvlGroup_GetOverlay(entry, value);
    return 0U;
}

struct OvlGroup *Overlays_GetOvlGroup(struct Overlays *list, long index)
{
    struct OvlGroup *record;
    int count;

    count = 0;
    if (!list)
        OS_ASSERT_AT("this", "CLOverlays.c", 93);

    record = list->groups;
    while (record && count < index) {
        ++count;
        record = record->next;
    }
    if (count == index)
        return record;
    return NULL;
}

struct Overlay *OvlGroup_GetOverlay(struct OvlGroup *list, long index)
{
    struct Overlay *entry;
    int position;
    position = 0;
    if (list == NULL)
        OS_ASSERT_AT("this", "CLOverlays.c", 234U);
    entry = list->olys;
    while (entry != NULL && position < index) {
        position += 1;
        entry = entry->next;
    }
    if (position == index)
        return entry;
    return NULL;
}

long OvlGroup_CountOverlays(OvlGroup *record)
{
    struct Overlay *link;
    int count;

    count = 0;
    if (record == NULL)
        OS_ASSERT_AT("this", "CLOverlays.c", 254U);

    link = record->olys;
    while (link != NULL) {
        link = link->next;
        count += 1;
    }
    return count;
}

struct Overlay *Overlay_New(const char *name)
{
    struct Overlay *overlay;
    overlay = xmalloc(NULL, 272U);
    if (overlay) {
        strncpy(overlay->name, name, 256U);
        overlay->name[255] = 0;
        overlay->list = NULL;
        overlay->max = 0U;
        overlay->cnt = overlay->max;
        overlay->next = NULL;
    } else {
        CLInternalError("CLOverlays.c", 281, "Could not allocate %s", "overlay");
    }
    return overlay;
}

long Overlay_CountFiles(struct Overlay *record)
{
    if (record == NULL)
        OS_ASSERT_AT("oly", "CLOverlays.c", 323U);
    return record->cnt;
}

Boolean Overlays_AddOvlGroup(Overlays *list, OvlGroup *entry, long *index)
{
    if (!list)
        OS_ASSERT_AT("this", "CLOverlays.c", 70U);
    if (!entry)
        OS_ASSERT_AT("grp", "CLOverlays.c", 71U);
    if (!list->groups)
        list->groups = entry;
    else
        list->lastgrp->next = entry;
    list->lastgrp = entry;
    if (index)
        *index = list->grpcnt;
    list->grpcnt += 1U;
    return 1;
}

long Overlay_GetFile(Overlay *table, long index)
{
    int allocationIndex;
    int cnt;

    if (table == NULL) {
        OS_ASSERT_AT("oly", "CLOverlays.c", 314U);
    }
    allocationIndex = index;
    cnt = table->cnt;
    if (allocationIndex < cnt) {
        return table->list[index];
    }
    return 0xffffffffU;
}

Boolean Overlays_Terminate(Overlays *list)
{
    struct OvlGroup *entry;
    struct OvlGroup *next;

    if (!list)
        OS_ASSERT_AT("this", "CLOverlays.c", 54U);
    entry = list->groups;
    while (entry) {
        next = entry->next;
        OvlGroup_Delete(entry);
        xfree(entry);
        entry = next;
    }
    list->groups = NULL;
    return 1;
}

void OvlGroup_Delete(OvlGroup *list)
{
    struct Overlay *p;
    struct Overlay *next;
    if (list == NULL) {
        OS_ASSERT_AT("grp", "CLOverlays.c", 0xc5);
    }
    p = list->olys;
    while (p) {
        next = p->next;
        Overlay_Delete(p);
        xfree(p);
        p = next;
    }
    list->olys = NULL;
}

void Overlay_Delete(struct Overlay *overlay)
{
    if (overlay == NULL)
        OS_ASSERT_AT("oly", "CLOverlays.c", 288U);
    if (overlay->list != NULL)
        xfree(overlay->list);
    overlay->list = NULL;
}

OvlGroup *OvlGroup_New(const char *name, OvlAddr overlayValues)
{
    OvlGroup *overlay;
    if (!name)
        OS_ASSERT_AT("name", "CLOverlays.c", 175U);
    overlay = xmalloc(NULL, 280U);
    if (overlay) {
        strncpy(overlay->name, name, 256U);
        overlay->name[255] = 0;
        overlay->addr = overlayValues;
        overlay->lastoly = NULL;
        overlay->olys = overlay->lastoly;
        overlay->olycnt = 0U;
        overlay->next = NULL;
    } else {
        CLInternalError("CLOverlays.c", 188, "Could not allocate %s", "overlay group");
    }
    return overlay;
}

UInt8 Overlay_AddFile(struct Overlay *table, long entry, long *entryIndex)
{
    SInt32 count;
    SInt32 capacity;
    if (!table) {
        OS_ASSERT_AT("oly", "CLOverlays.c", 296U);
    }
    count = table->cnt;
    capacity = table->max;
    if (count >= capacity) {
        table->max += 16;
        table->list = xrealloc("overlay file list", table->list, table->max << 2);
    }
    table->list[table->cnt] = entry;
    if (entryIndex) {
        *entryIndex = table->cnt;
    }
    table->cnt += 1;
    return 1;
}
