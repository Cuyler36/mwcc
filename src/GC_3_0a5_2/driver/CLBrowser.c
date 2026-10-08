#define CERROR_FILE "CLBrowser.c"
#include "compiler/common.h"
#include "GC_3_0a5_2/driver/CLBrowser.h"
#include "compiler/win32.h"
#include "compiler/CPrep.h"
#include "driver/CLDropinCallbacks_V10.h"
#include "driver/CLErrors.h"
#include "driver/CLFileOps.h"
#include "driver/CLFiles.h"
#include "driver/CLIO.h"
#include "driver/CLPlugins.h"
#include "driver/CLProj.h"
#include "driver/CLTarg.h"
#include "driver/Files.h"
#include "driver/Memory.h"
#include "driver/MsDos.h"
#include <setjmp.h>
#include <string.h>
#include <stdio.h>

extern void __stdcall xfree(void *allocation);
extern char *__stdcall xstrdup(const char *text);
extern __declspec(noreturn) void exit(int status);

#pragma auto_inline off

/* Allocation diagnostics owned by this TU; no original static names were
 * present in the symbol map, so retain the established binding names. */
unsigned char browse_file_table_string[] = "browse file table";
unsigned char data_0054d9c4[] = "allocate";

/* An entry in the browser's name table. */

/* A browser table entry associates a value with a name. */
#include <stdlib.h>
/* The symbol map marks the four browser helpers as file-local. Their
 * current linkage preserves emitted bodies while matching is in progress. */
void GetBrowseTableInfoAndLock(MemBuffer *value, struct CLBrowserLookupEntry **result, unsigned int *shifted_value,
                 unsigned int *raw_value)
{
    DWORD extracted_value;

    OS_GetHandleSize(value, &extracted_value);
    if (result != NULL) {
        *result = MsDos_GetValidMemBufferPtr(value);
    }
    if (shifted_value != NULL) {
        *shifted_value = extracted_value >> 3;
    }
    if (raw_value != NULL) {
        *raw_value = extracted_value;
    }
}

unsigned int Browser_Initialize(MemBuffer *buffer)
{
    unsigned int error = OS_NewHandle(0U, buffer);
    if (error != 0U) {
        CLErrors_ReportOSError(63, error, data_0054d9c4, browse_file_table_string);
        return 0U;
    }
    return 1U;
}

unsigned int Destroy(MemBuffer *container)
{
    struct CLBrowserLookupEntry *entry;
    unsigned int count;

    GetBrowseTableInfoAndLock(container, &entry, &count, NULL);
    while (count--) {
        xfree(entry->name);
        entry++;
    }
    fn_004129c0(container);
    return 1;
}

unsigned int Browser_Terminate(MemBuffer *value)
{
    if (!Destroy(value))
        return 0U;
    OS_FreeHandle(value);
    return 1U;
}

int Browser_SearchFile(void *table, char *name, short *value)
{
    int index;
    int comparison;
    UInt8 found;
    CLBrowserLookupEntry *entry;
    int count;
    unsigned int tableInfo;

    found = 0;
    index = MsDos_IsAbsolutePath(name);
    if (index == 0) {
        OS_ASSERT_AT("OS_IsFullPath(fullpath)", "CLBrowser.c", 0x72);
    }
    if (!table) {
        OS_ASSERT_AT("browsetable!=NULL", "CLBrowser.c", 0x73);
    }
    GetBrowseTableInfoAndLock(table, &entry, (unsigned int *)&count, &tableInfo);
    index = 0;
    if (0 < count) {
        do {
            comparison = OS_EqualPath(name, entry->name);
            if (comparison != 0) {
                found = 1;
                break;
            }
            ++index;
            ++entry;
        } while (index < count);
    }
    if (found != 0) {
        *value = entry->value;
    } else {
        *value = 0;
    }
    fn_004129c0(table);
    return found;
}

int Browser_SearchAndAddFile(MemBuffer *browser, char *name, short *result)
{
    CLBrowserLookupEntry *entry;
    unsigned int count, offset;
    char *savedName;
    if (Browser_SearchFile(browser, name, result) == 0) {
        savedName = xstrdup(name);
        GetBrowseTableInfoAndLock(browser, &entry, &count, &offset);
        fn_004129c0(browser);
        if (OS_ResizeHandle(browser, (count + 1) << 3) != 0) {
            fprintf(stderr, "\n*** Out of memory\n");
            exit(-23);
        }
        entry = (CLBrowserLookupEntry *)((char *)MsDos_GetValidMemBufferPtr(browser) + offset);
        entry->name = savedName;
        entry->value = count + 1;
        fn_004129c0(browser);
        *result = entry->value;
        return -1;
    }
    return 1;
}
/* Serialized browser file header. */

/* Opaque two-word allocation handle. */

/* Count returned as a word, serialized as a short. */

unsigned int Browser_PackBrowseFile(struct StorageHandle *dataHandle, void *indexHandle, MemBuffer *result)
{
    int indexOffset;
    int totalSize;
    DWORD error;
    unsigned char *buffer;
    DstRec *indexBuffer;
    DWORD dataSize;
    unsigned int indexSize;
    MemBuffer output;
    struct BrowserFileHeader header;
    CLBrowserLookupEntry *indexData;
    unsigned int itemCount;
    int byteOrder = 1;
    void *dataBuffer;

    if (dataHandle == NULL) {
        OS_ASSERT_AT("browsedata!=NULL", "CLBrowser.c", 0xfe);
    }
    if (indexHandle == NULL) {
        OS_ASSERT_AT("browsetable!=NULL", "CLBrowser.c", 0xff);
    }
    OS_GetHandleSize((MemBuffer *)dataHandle, &dataSize);
    indexOffset = (dataSize + sizeof(header) + 7) & -8;
    GetBrowseTableInfoAndLock(indexHandle, &indexData, &itemCount, NULL);
    indexSize = CalcDiskSpaceRequirements(indexData, itemCount);
    fn_004129c0(indexHandle);
    totalSize = indexSize + indexOffset;
    memcpy(header.signature, "DubL", sizeof(header.signature));
    header.version = 1;
    header.flag = (*(unsigned char *)&byteOrder == 0);
    memset(header.reserved, 0, sizeof(header.reserved));
    header.itemCount = itemCount;
    header.dataOffset = sizeof(header);
    header.dataSize = dataSize;
    header.indexOffset = indexOffset;
    header.indexSize = indexSize;
    error = OS_NewHandle(totalSize, &output);
    *result = output;
    if (error != 0) {
        fprintf(stderr, "\n*** Out of memory\n");
        exit(-23);
    }
    buffer = MsDos_GetValidMemBufferPtr(&output);
    *(struct BrowserFileHeader *)buffer = header;
    dataBuffer = MsDos_GetValidMemBufferPtr((MemBuffer *)dataHandle);
    memcpy(buffer + sizeof(header), dataBuffer, dataSize);
    memset((unsigned char *)((int)buffer + sizeof(header) + dataSize), 0, indexOffset - sizeof(header) - dataSize);
    fn_004129c0((MemBuffer *)dataHandle);
    GetBrowseTableInfoAndLock(indexHandle, &indexData, &itemCount, NULL);
    indexBuffer = (DstRec *)(buffer + indexOffset);
    ConvertMemToDisk(indexData, indexBuffer, itemCount);
    memset(buffer + indexOffset + indexSize, 0, totalSize - indexOffset - indexSize);
    fn_004129c0(indexHandle);
    fn_004129c0(&output);
    return 1;
}

int ConvertMemToDisk(CLBrowserLookupEntry *entries, DstRec *output, UInt32 count)
{
    SInt32 nameLength;
    SInt32 paddedLength;
    while (count--) {
        output->id = entries->value;
        memset(&output->id + 1, 0, 3 * sizeof(UInt32));
        nameLength = strlen(entries->name);
        paddedLength = (nameLength + 7) & ~7;
        output->len = nameLength;
        memset(output->data, 0, paddedLength);
        strncpy(output->data, entries->name, nameLength);
        entries++;
        output = (DstRec *)((char *)output + paddedLength + 16);
    }
    return 1;
}

unsigned int CalcDiskSpaceRequirements(CLBrowserLookupEntry *entries, unsigned int count)
{
    unsigned int total = 0;
    while (count--) {
        const char *name = entries->name;
        total += 16U;
        total += (strlen(name) + 7U) & ~7U;
        ++entries;
    }
    return total;
}
