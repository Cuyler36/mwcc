#define CERROR_FILE "CLFiles.c"
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include "driver/Memory.h"
#include "driver/MsDos.h"
#include <string.h>

extern void *__stdcall xmalloc(const char *context, unsigned int size);
extern void *__stdcall xcalloc(const char *context, unsigned int size);
extern void __stdcall xfree(void *allocation);
extern void Deps_Terminate(void *dependencies);
extern DWORD __stdcall CLFileOps_AppendMemBuffer(void *handle, const void *source, unsigned int size);
extern short FixTextHandle(MemBuffer *handle);

#pragma auto_inline off

/* Names come from the Mac symbol map; offsets reflect the Windows image. */
#pragma pack(push, 1)
typedef struct FileOSSpec {
    char path[260];
    char name[256];
} FileOSSpec;
typedef struct File {
    struct File *next;
    int filenum;
    unsigned char reserved008[0x217];
    FileOSSpec srcfss;
    FileOSSpec outfss;
    unsigned char reserved627[0x1d];
    MemBuffer *textdata;
    MemBuffer *objectdata;
    MemBuffer *browsedata;
    unsigned char reserved650[0x220];
    unsigned char deps[0x44];
} File;
#pragma pack(pop)

typedef struct Files {
    File *fileList;
    int fileCount;
    File **fileMap;
} Files;

typedef struct VFile {
    char name[32];
    MemBuffer text;
    struct VFile *next;
} VFile;

File *File_New(void)
{
    return xcalloc(NULL, sizeof(File));
}

void File_Free(File *file)
{
    if (file != NULL) {
        if (file->textdata != NULL) {
            OS_FreeHandle(file->textdata);
            file->textdata = NULL;
        }
        if (file->objectdata != NULL) {
            OS_FreeHandle(file->objectdata);
            file->objectdata = NULL;
        }
        if (file->browsedata != NULL) {
            OS_FreeHandle(file->browsedata);
            file->browsedata = NULL;
        }
        Deps_Terminate(file->deps);
        xfree(file);
    }
}

Boolean Files_Initialize(Files *this)
{
    if (!this)
        OS_ASSERT_AT("this != NULL", "CLFiles.c", 49);
    this->fileList = NULL;
    this->fileCount = 0;
    this->fileMap = NULL;
    return 1;
}

Boolean Files_Terminate(Files *this)
{
    File *file;
    File *next;
    if (!this)
        OS_ASSERT_AT("this != NULL", "CLFiles.c", 59);
    file = this->fileList;
    while (file) {
        next = file->next;
        File_Free(file);
        file = next;
    }
    xfree(this->fileMap);
    this->fileMap = NULL;
    return 1;
}

Boolean Files_InsertFile(Files *this, File *file, int pos);

Boolean Files_AddFile(Files *this, File *file)
{
    return Files_InsertFile(this, file, this->fileCount);
}

/* Additional Windows helper; no static name survives in the symbol map. */
void fn_00436670(Files *this)
{
    File *file;
    if (this->fileMap)
        xfree(this->fileMap);
    this->fileMap = xcalloc("file map", this->fileCount * sizeof(File *));
    for (file = this->fileList; file; file = file->next) {
        if (!(file->filenum < this->fileCount))
            OS_ASSERT_AT("file->filenum < this->fileCount", "CLFiles.c", 91);
        this->fileMap[file->filenum] = file;
    }
}

Boolean Files_InsertFile(Files *this, File *file, int pos)
{
    File *p;
    if (!this)
        OS_ASSERT_AT("this != NULL", "CLFiles.c", 100);
    if (!file)
        OS_ASSERT_AT("file != NULL", "CLFiles.c", 101);
    if (pos < 0)
        pos = 0;
    else if (pos > this->fileCount)
        pos = this->fileCount;
    file->filenum = pos;
    p = (File *)this;
    while (pos-- > 0)
        p = p->next;
    this->fileCount++;
    file->next = p->next;
    p->next = file;
    for (p = file->next; p; p = p->next)
        p->filenum++;
    xfree(this->fileMap);
    this->fileMap = NULL;
    return 1;
}

File *Files_GetFile(Files *this, int filenum)
{
    if (!this)
        OS_ASSERT_AT("this != NULL", "CLFiles.c", 133);
    if (filenum < 0)
        OS_ASSERT_AT("filenum >= 0", "CLFiles.c", 134);
    if (!this->fileMap)
        fn_00436670(this);
    if (this->fileMap && filenum < this->fileCount)
        return this->fileMap[filenum];
    return NULL;
}

File *Files_FindFile(Files *this, const OSSpec *spec)
{
    File *file = this->fileList;
    while (file && !OS_EqualSpec((OSSpec *)&file->srcfss, spec))
        file = file->next;
    return file;
}

int Files_Count(Files *this)
{
    if (!this)
        OS_ASSERT_AT("this != NULL", "CLFiles.c", 171);
    return this->fileCount;
}

Boolean VFiles_Initialize(VFile **this)
{
    *this = NULL;
    return 1;
}

void VFiles_Terminate(VFile **this)
{
    VFile *next;
    while (*this) {
        next = (*this)->next;
        OS_FreeHandle(&(*this)->text);
        xfree(*this);
        this = &next;
    }
    *this = NULL;
}

VFile *VFile_New(const char *name, MemBuffer *text)
{
    VFile *file;
    void *data;
    UInt32 size;
    file = xmalloc(NULL, sizeof(VFile));
    if (file == NULL)
        return NULL;
    strncpy(file->name, name, 32);
    file->name[31] = 0;
    if (OS_NewHandle(0, &file->text) != 0) {
        xfree(file);
        return NULL;
    }
    data = MsDos_GetValidMemBufferPtr(text);
    OS_GetHandleSize(text, &size);
    if (CLFileOps_AppendMemBuffer(&file->text, data, size) != 0) {
        fn_004129c0(text);
        xfree(file);
        return NULL;
    }
    fn_004129c0(text);
    FixTextHandle(&file->text);
    file->next = NULL;
    return file;
}

Boolean VFiles_Add(VFile **this, VFile *file)
{
    VFile **link = this;
    for (; *link; link = &(*link)->next) {
    }
    *link = file;
    return 1;
}

VFile *VFiles_Find(VFile *first, const char *name)
{
    VFile *file = first;
    while (file) {
        if (!strcmp(file->name, name))
            break;
        file = file->next;
    }
    return file;
}
