#define CERROR_FILE "Generic.c"
#include "compiler/common.h"
#include "driver/Memory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct OSSpec { struct { char path[260]; } directory; char name[256]; } OSSpec;
typedef struct GenericPathTextBuffer { char bytes[260]; } GenericPathTextBuffer;
typedef struct DirectorySearch { unsigned char bytes[268]; } DirectorySearch;
static char wildname[255];
static char wilddir[260];
static DirectorySearch wilddirref;
static OSSpec wildmatch;
extern char STSbuf[];
extern char *__stdcall strcpyn(char *, const char *, unsigned int, int);
extern char *__stdcall strcatn(char *, char *, int);
extern int __stdcall ustrcmp(char *, char *);
extern int __stdcall OS_MakePathSpec(char *, char *, char *);
extern int __stdcall OS_MakeNameSpec(char *, char *);
extern int __stdcall OS_OpenDir(char *, DirectorySearch *);
extern int __stdcall OS_ReadDir(DirectorySearch *, OSSpec *, char *, Boolean *);
extern int __stdcall OS_CloseDir(DirectorySearch *);
extern int __stdcall OS_GetCWD(char *);
extern int __stdcall MsDos_IsAbsolutePath(char *);
extern int __stdcall OS_MakeSpec(char *, OSSpec *, UInt8 *);
extern int __stdcall OS_MakeFileSpec(char *, OSSpec *);
extern int __stdcall OS_Status(OSSpec *);
extern char *__stdcall OS_SpecToString(OSSpec *, char *, unsigned int);
extern char *__stdcall OS_PathSpecToString(char *, char *, unsigned int);
extern char *__stdcall OS_NameSpecToString(void *, char *, unsigned int);
extern void *__stdcall fn_004263c0(unsigned int);
#pragma auto_inline off

int WildCardMatch(char *pattern, char *str)
{
    char c;
    char *last;

    if (*str == 0)
        return 0;

    while (*pattern != 0) {
        if (*pattern == '*') {
            c = *++pattern;
            last = NULL;
            while (*str != 0) {
                if (tolower(*str) == tolower(c))
                    last = str;
                str++;
            }
            if (last != NULL)
                str = last;
            if (tolower(*str) != tolower(c))
                return 0;
        } else if (*pattern == '?' && *str != 0) {
            pattern++;
            str++;
            if (*pattern == 0 && *str != 0)
                return 0;
        } else {
            if (tolower(*pattern) == tolower(*str)) {
                pattern++;
                str++;
            } else
                return 0;
        }
    }

    return *str == 0 || (*str == '\\' && str[1] == 0);
}

OSSpec *__stdcall OS_MatchPath(char *name)
{
    char entryName[256];
    UInt32 flag;
    char path[516];
    char *fileName;
    DirectorySearch *state;
    OSSpec *spec;
    if (name != NULL) {
        fileName = strrchr(name, '\\');
        if (fileName == NULL) {
            fileName = name;
            strcpyn(wilddir, ".", -1, 0x104);
        } else {
            ++fileName;
            strcpyn(wilddir, name, fileName - name, 0x104);
        }
        if (OS_MakePathSpec(NULL, wilddir, path) != 0)
            return NULL;
        strcpyn(wildname, fileName, -1, 0x100);
        if (OS_MakeNameSpec(wildname, path + 0x104) != 0)
            return NULL;
        if (OS_OpenDir(path, &wilddirref) != 0)
            return NULL;
    }
    while ((state = &wilddirref, spec = &wildmatch,
            OS_ReadDir(state, spec, entryName, (Boolean *)&flag)) == 0) {
        if (((UInt8)flag & 1) != 0 && WildCardMatch(wildname, entryName) != 0)
            return &wildmatch;
    }
    state = &wilddirref;
    OS_CloseDir(state);
    return NULL;
}

char *__stdcall OS_GetFileNamePtr(char *path)
{
    char *name;
    name = strrchr(path, '\\');
    if (!name)
        name = path;
    else
        name += 1;
    return name;
}

int __stdcall OS_MakeSpec2(char *directory, char *filename, OSSpec *result)
{
    char path[260];
    int directoryLength;
    int filenameLength;
    char *end;
    OSSpec *output;
    if (directory == NULL)
        directory = "";
    if (filename == NULL)
        filename = "";
    filenameLength = strlen(filename);
    directoryLength = strlen(directory);
    if (259 < filenameLength + directoryLength + 1)
        return 0x6f;
    strncpy(path, directory, directoryLength);
    end = path + directoryLength;
    if (end[-1] != '\\') {
        *end = '\\';
        end++;
    }
    strcpy(end, filename);
    output = result;
    return OS_MakeSpec(path, output, NULL);
}

unsigned int __stdcall OS_MakeSpecWithPath(char *basePath, char *path, UInt8 useSpecialPath, OSSpec *destination, UInt8 *status)
{
    Boolean hasSpecialCharacters;
    UInt8 specialCharacters;
    char buffer[0x104];

    hasSpecialCharacters = path != NULL && strpbrk(path, "/\\:") != NULL;
    if (path == NULL) {
        if (basePath != NULL)
            *(GenericPathTextBuffer *)destination->directory.path = *(GenericPathTextBuffer *)basePath;
        else
            OS_GetCWD(destination->directory.path);
        if (status) *status = 2;
        return OS_MakeNameSpec("", destination->name);
    }
    specialCharacters = hasSpecialCharacters;
    if (!((useSpecialPath && specialCharacters) || MsDos_IsAbsolutePath(path) != 0)) {
        if (basePath != NULL)
            OS_PathSpecToString(basePath, buffer, 0x104);
        else
            buffer[0] = 0;
        {
            char *appendAt = buffer + 0x103 - strlen(path);
            char *end = buffer + strlen(buffer);
            if (end <= appendAt)
                appendAt = end;
            strcpy(appendAt, path);
        }
        return OS_MakeSpec(buffer, destination, status);
    }
    return OS_MakeSpec(path, destination, status);
}

unsigned int __stdcall OS_NameSpecChangeExtension(void *file, const char *extensionAddress, unsigned char append)
{
    char buffer[256];
    char *extensionStart;
    OS_NameSpecToString(file, buffer, 260U);
    if (!append) {
        extensionStart = strrchr(buffer, '.');
        if (extensionStart == NULL)
            extensionStart = buffer + strlen(buffer);
    } else {
        extensionStart = buffer + strlen(buffer);
        if (*extensionAddress != '.') {
            *extensionStart = '.';
            extensionStart++;
            *extensionStart = 0;
        }
    }
    if (strlen(buffer) + strlen(extensionAddress) > sizeof(buffer))
        extensionStart = buffer + sizeof(buffer) - 1 - strlen(extensionAddress);
    strcpy(extensionStart, extensionAddress);
    return OS_MakeNameSpec(buffer, file);
}

unsigned int __stdcall OS_NameSpecSetExtension(char *file, char *extensionAddress)
{
    char path[256];
    char *suffix;
    OS_NameSpecToString(file, path, 260U);
    if (*extensionAddress != '.') {
        suffix = strrchr(path, '.');
        if (!suffix)
            suffix = path + strlen(path);
        if (*extensionAddress) {
            if (strlen(path) + 1 >= sizeof(path)) {
                suffix[-1] = '.';
            } else {
                *suffix++ = '.';
            }
        }
    } else {
        suffix = path + strlen(path);
    }
    if (strlen(path) + strlen(extensionAddress) > sizeof(path)) {
        suffix = path + sizeof(path) - 1 - strlen(extensionAddress);
    }
    strcpy(suffix, extensionAddress);
    return OS_MakeNameSpec(path, file);
}

char *__stdcall OS_SpecToStringRelative(OSSpec *source, char *base, char *destination, int capacity)
{
    char *sourceCursor;
    char *baseCursor;
    char *outputCursor;
    char sourcePath[260];
    char basePath[260];
    char currentPath[260];
    sourceCursor = sourcePath;
    baseCursor = basePath;
    OS_SpecToString(source, sourcePath, sizeof(sourcePath));
    if (capacity == 0) {
        capacity = sizeof(sourcePath);
    }
    if (destination == NULL) {
        destination = (char *)fn_004263c0(capacity);
        if (destination == NULL) {
            return NULL;
        }
    }
    if (base == NULL) {
        OS_GetCWD(currentPath);
        base = currentPath;
    }
    if (OS_PathSpecToString(base, basePath, sizeof(basePath)) == NULL) {
        memcpy(destination, sourcePath, capacity - 1);
        destination[capacity - 1] = 0;
        return destination;
    }
    for (; *baseCursor != 0 && tolower(*sourceCursor) == tolower(*baseCursor); baseCursor++) {
        sourceCursor++;
    }
    if ((baseCursor - basePath) < (strlen(sourcePath) >> 1) && strlen(baseCursor) > (strlen(sourcePath) >> 1)) {
        memcpy(destination, sourcePath, capacity - 1);
        destination[capacity - 1] = 0;
        return destination;
    }
    while (baseCursor > basePath) {
        baseCursor--;
        sourceCursor--;
        if (*baseCursor == '\\') {
            break;
        }
    }
    if (baseCursor == basePath) {
        strncpy(destination, sourceCursor, capacity - 1);
        destination[capacity - 1] = 0;
    } else {
        baseCursor++;
        if (*baseCursor != 0) {
            outputCursor = destination;
            for (; *baseCursor != 0; baseCursor++) {
                if (*baseCursor == '\\') {
                    outputCursor += sprintf(outputCursor, "..\\");
                }
            }
            strcpy(outputCursor, (sourceCursor + 1));
        } else {
            strncpy(destination, (sourceCursor + 1), capacity - 1);
            destination[capacity - 1] = 0;
        }
    }
    return destination;
}

unsigned int __stdcall OS_FindFileInPath(char *name, const char *searchPath, void *result)
{
    const char *separator;
    unsigned int status;
    char directory[260];
    while (searchPath != NULL && *searchPath != 0) {
        separator = strchr((char *)searchPath, ';');
        if (separator == NULL) {
            separator = strpbrk(searchPath, ";,");
        }
        if (separator == NULL) {
            separator = searchPath + strlen(searchPath);
        }
        strcpyn(directory, searchPath, separator - searchPath, 0x103);
        status = OS_MakeSpec2(directory, name, result);
        if (status == 0) {
            status = OS_Status(result);
            if (status == 0) {
                return 0;
            }
        }
        searchPath = (*separator != 0) ? separator + 1 : NULL;
    }
    status = OS_MakeFileSpec(name, result);
    if (status == 0) {
        status = OS_Status(result);
        if (status == 0) {
            return 0;
        }
    }
    return status;
}


char *__stdcall OS_GetDirName(char *spec, char *buf, int size)
{
    char *path;
    char *pptr;
    if (!spec || !buf || size <= 0)
        return NULL;
    path = OS_PathSpecToString(spec, STSbuf, 260);
    pptr = path + strlen(path) - 1;
    if (pptr > path && *pptr == '\\') {
        *pptr = 0;
        pptr--;
    }
    while (pptr >= path && *pptr != '\\') pptr--;
    strncpy(buf, pptr, size - 1);
    buf[size - 1] = 0;
    return buf;
}

extern __declspec(dllimport) unsigned int __stdcall GetSystemDirectoryA(char *, unsigned int);
extern __declspec(dllimport) unsigned int __stdcall GetWindowsDirectoryA(char *, unsigned int);

int __stdcall OS_FindProgram(char *name, OSSpec *spec)
{
    char path[260];
    char filename[260];
    int err;
    char *envpath;
    strncpy(filename, name, sizeof(filename));
    filename[259] = 0;
    if (strlen(filename) < 4 || (ustrcmp(filename + strlen(filename) - 4, ".exe") &&
                               ustrcmp(filename + strlen(filename) - 4, ".dll")))
        strcatn(filename, ".exe", sizeof(filename));
    if (strchr(filename, '\\')) {
last_try:
        err = OS_MakeFileSpec(filename, spec);
        if (err == 0) err = OS_Status(spec);
        return err;
    }
    {
        if (GetSystemDirectoryA(path, sizeof(path))) {
            err = OS_MakeSpec2(path, filename, spec);
            if (err == 0) {
                err = OS_Status(spec);
                if (err == 0) return err;
            }
        }
        if (GetWindowsDirectoryA(path, sizeof(path))) {
            err = OS_MakeSpec2(path, filename, spec);
            if (err == 0) {
                err = OS_Status(spec);
                if (err == 0) return err;
            }
        }
        envpath = getenv("PATH");
        err = OS_FindFileInPath(filename, envpath, spec);
        if (err != 0) goto last_try;
    }
    return 0;
}

extern int __stdcall OS_GetHandleSize(MemBuffer *, UInt32 *);
extern int __stdcall OS_NewHandle(UInt32, MemBuffer *);
extern int __stdcall OS_ResizeHandle(MemBuffer *, UInt32);
extern int __stdcall OS_FreeHandle(MemBuffer *);
extern void *__stdcall OS_LockHandle(MemBuffer *);
extern void __stdcall OS_UnlockHandle(MemBuffer *);

int __stdcall OS_CopyHandle(MemBuffer *src, MemBuffer *dst)
{
    UInt32 len;
    int err;
    void *ptr;
    void *dstptr;
    err = OS_GetHandleSize(src, &len);
    if (err) goto error;
    err = OS_NewHandle(len, dst);
    if (err) goto error;
    ptr = OS_LockHandle(src);
    dstptr = OS_LockHandle(dst);
    memcpy(dstptr, ptr, len);
    OS_UnlockHandle(src);
    OS_UnlockHandle(dst);
    return 0;
error:
    OS_FreeHandle(dst);
    return err;
}

int __stdcall OS_AppendHandle(MemBuffer *hand, void *data, UInt32 len)
{
    UInt32 oldlen;
    int err;
    void *ptr;
    err = OS_GetHandleSize(hand, &oldlen);
    if (err) goto done;
    err = OS_ResizeHandle(hand, oldlen + len);
    if (err) goto done;
    ptr = OS_LockHandle(hand);
    if (!ptr) goto done;
    memcpy((char *)ptr + oldlen, data, len);
    OS_UnlockHandle(hand);
    return 0;
done:
    return err;
}

int __stdcall fn_00418010(char *path, OSSpec *spec)
{
    char *end;
    int size;
    char *name;
    end = path + strlen(path);
    name = strrchr(path, '\\');
    if (!name) name = strrchr(path, '/');
    if (name) name++;
    else name = path;
    size = name - path;
    if (size >= 259) return 111;
    strncpy(spec->directory.path, path, size);
    spec->directory.path[size] = 0;
    size = end - name;
    if (size >= 259) return 111;
    strncpy(spec->name, name, size);
    spec->name[size] = 0;
    return 0;
}
