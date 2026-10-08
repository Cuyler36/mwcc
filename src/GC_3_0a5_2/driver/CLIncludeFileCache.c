#define CERROR_FILE "CLIncludeFileCache.c"
#include "compiler/common.h"
#include "GC_3_0a5_2/driver/CLBrowser.h"
#include "driver/Memory.h"
#include "driver/MsDos.h"

/* Windows 3.0 copies 516 bytes for a file spec. Keep the recovered layout
 * local until the shared OS interface has been ported to this version. */
typedef struct GC3CacheFileSpec {
    unsigned char bytes[0x204];
} GC3CacheFileSpec;

struct CacheEntry {
    struct CacheEntry *next;
    struct CacheEntry *prev;
    int locked;
    int precompiled;
    MemBuffer *text;
    GC3CacheFileSpec spec;
    unsigned int size;
    unsigned int when;
};
typedef struct CacheEntry CacheEntry;

/* Original file-local names are recorded by STABS. */
static CacheEntry *cachelist;
static CacheEntry *freelist;
static unsigned int availablecache;

extern void *__stdcall xmalloc(const char *description, unsigned int size);
extern void __stdcall xfree(void *allocation);

#pragma auto_inline off

/* These helpers are file-local in the map; preserve emitted bodies while
 * matching their code ranges. */
CacheEntry *makecacheentry(void)
{
    CacheEntry *entry;
    if (freelist != NULL) {
        entry = freelist;
        freelist = freelist->next;
    } else {
        entry = (CacheEntry *)xmalloc("include file cache", sizeof(CacheEntry));
    }
    return entry;
}

void insertcacheentry(CacheEntry *node)
{
    if (cachelist != NULL)
        cachelist->prev = node;
    node->next = cachelist;
    node->prev = NULL;
    cachelist = node;
}

void deletecacheentry(CacheEntry *links)
{
    if (links->next != NULL)
        links->next->prev = links->prev;
    if (links->prev != NULL)
        links->prev->next = links->next;
    else
        cachelist = links->next;
}

void InitializeIncludeCache(void)
{
    CacheEntry **head = &freelist;
    *head = NULL;
    cachelist = freelist;
    availablecache = 8U * 1024 * 1024;
}

void CleanupIncludeCache(void)
{
    CacheEntry *node;
    CacheEntry *next;
    CacheEntry *allocation;
    CacheEntry *nextAllocation;
    MemBuffer *record;
    node = cachelist;
    while (node != NULL) {
        next = node->next;
        record = node->text;
        if (record != NULL) {
            OS_FreeHandle(record);
            xfree(node->text);
        }
        xfree(node);
        node = next;
    }
    allocation = freelist;
    while (allocation != NULL) {
        nextAllocation = allocation->next;
        xfree(allocation);
        allocation = nextAllocation;
    }
    InitializeIncludeCache();
}

static inline CacheEntry *find_oldest_unpinned_entry(void)
{
    CacheEntry *cursor;
    CacheEntry *entry;
    entry = NULL;
    for (cursor = cachelist; cursor != NULL; cursor = cursor->next) {
        if (cursor->locked == 0 && cursor->precompiled == 0 &&
            (entry == NULL || cursor->when < entry->when))
            entry = cursor;
    }
    return entry;
}

static inline void release_entry_buffer(CacheEntry *entry)
{
    OS_FreeHandle(entry->text);
    xfree(entry->text);
    entry->text = NULL;
}

static inline void recycle_entry(CacheEntry *entry)
{
    deletecacheentry(entry);
    entry->next = freelist;
    freelist = entry;
}

void CacheIncludeFile(OSSpec *spec, StorageHandle *text, unsigned char precompiled)
{
    DWORD size;
    CacheEntry *entry;
    CacheEntry *cursor;
    CacheEntry *newEntry;
    OS_GetHandleSize((MemBuffer *)text, &size);
    if (precompiled) {
        entry = NULL;
        for (cursor = cachelist; cursor != NULL; cursor = cursor->next) {
            if (cursor->precompiled) {
                entry = cursor;
                break;
            }
        }
        if (entry != NULL) {
            release_entry_buffer(entry);
            recycle_entry(entry);
        }
    } else {
        if (size > 8U * 1024 * 1024)
            return;
        while (size > availablecache) {
            entry = find_oldest_unpinned_entry();
            if (entry == NULL)
                return;
            release_entry_buffer(entry);
            availablecache += entry->size;
            recycle_entry(entry);
        }
    }
    newEntry = makecacheentry();
    newEntry->locked = 1;
    newEntry->precompiled = precompiled;
    newEntry->spec = *(GC3CacheFileSpec *)spec;
    newEntry->text = (MemBuffer *)text;
    newEntry->size = size;
    newEntry->when = OS_GetMilliseconds();
    insertcacheentry(newEntry);
    if (!precompiled)
        availablecache -= size;
}

StorageHandle *CachedIncludeFile(OSSpec *key, unsigned char *value)
{
    CacheEntry *entry;
    CacheEntry *prev;
    int matched;
    prev = NULL;
    entry = cachelist;
    while (entry != NULL) {
        matched = OS_EqualSpec((OSSpec *)&entry->spec, key);
        if (matched != 0) {
            entry->when = OS_GetMilliseconds();
            *value = (unsigned char)entry->precompiled;
            ++entry->locked;
            if (prev != NULL) {
                deletecacheentry(entry);
                insertcacheentry(entry);
            }
            return (StorageHandle *)entry->text;
        }
        prev = entry;
        entry = entry->next;
    }
    return NULL;
}

void FreeIncludeFile(StorageHandle *value)
{
    CacheEntry *entry;
    for (entry = cachelist; entry != NULL; entry = entry->next) {
        if (entry->text == (MemBuffer *)value) {
            --entry->locked;
            return;
        }
    }
    OS_FreeHandle((MemBuffer *)value);
}
