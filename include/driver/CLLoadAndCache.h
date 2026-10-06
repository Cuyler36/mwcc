#ifndef DRIVER_CLLOADANDCACHE_H
#define DRIVER_CLLOADANDCACHE_H

#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int CLLoadAndCache_GetFileText(OSSpec *path, StorageHandle **outHandle, UInt8 *outFlag);
extern void CLLoadAndCache_CopyStorageHandleData(StorageHandle *sourceHandle, void **bufferOut, unsigned int *sizeOut);

#ifdef __cplusplus
}
#endif

#endif
