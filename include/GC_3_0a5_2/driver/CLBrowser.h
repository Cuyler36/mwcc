#ifndef GC_3_0A5_2_DRIVER_CLBROWSER_H
#define GC_3_0A5_2_DRIVER_CLBROWSER_H

#include "driver/CLBrowser.h"

#ifdef __cplusplus
extern "C" {
#endif

void GetBrowseTableInfoAndLock(MemBuffer *value, CLBrowserLookupEntry **result,
                               unsigned int *count, unsigned int *size);
unsigned int Browser_Initialize(MemBuffer *buffer);
unsigned int Destroy(MemBuffer *container);
unsigned int Browser_Terminate(MemBuffer *buffer);
int Browser_SearchFile(void *table, char *name, short *value);
int Browser_SearchAndAddFile(MemBuffer *browser, char *name, short *result);
unsigned int CalcDiskSpaceRequirements(CLBrowserLookupEntry *entries, unsigned int count);
int ConvertMemToDisk(CLBrowserLookupEntry *entries, DstRec *output, UInt32 count);
unsigned int Browser_PackBrowseFile(StorageHandle *data, void *index, MemBuffer *result);

struct CacheEntry;
struct CacheEntry *makecacheentry(void);
void insertcacheentry(struct CacheEntry *entry);
void deletecacheentry(struct CacheEntry *entry);
void InitializeIncludeCache(void);
void CleanupIncludeCache(void);
void CacheIncludeFile(OSSpec *path, StorageHandle *buffer, unsigned char flag);
StorageHandle *CachedIncludeFile(OSSpec *path, unsigned char *flag);
void FreeIncludeFile(StorageHandle *buffer);

#ifdef __cplusplus
}
#endif

#endif
