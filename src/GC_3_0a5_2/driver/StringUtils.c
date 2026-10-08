#include "compiler/common.h"
#include "driver/StringUtils.h"
#include "compiler/objects.h"
#include "compiler/scopes.h"
#include "compiler/win32.h"
#include "driver/CLIO.h"
/* The GC3 caller tests a signed 16-bit append result. */
extern short __stdcall Memory_AppendStorageHandle(const void *, struct StorageHandle *, int);
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define va_start(ap, last)                                                                                             \
    ((ap) = (char *)&(last) + (((int)((char *)&(last) + sizeof(last)) - (int)(char *)&(last) + 3) / 4) * 4)
extern void *__stdcall fn_004263c0(int size);
extern void __stdcall xfree(void *pointer);
/* The symbol map names this TU's private formatting buffer pfbuf. */
static char pfbuf[256];

typedef char *(*TextFormatFunction)(char *buffer, unsigned int capacity, const char *format, va_list arguments);

UInt8 *_pstrcpy(UInt8 *destination, UInt8 *string)
{
    memcpy(destination, string, *string + 1);
    return destination;
}

unsigned int pstrcmp(UInt8 *left, char *right)
{
    int length;
    unsigned int difference;

    if ((difference = (length = *left++) - ((UInt8)*right++)) > 0) {
        return difference;
    }
    while (length-- > 0) {
        if ((difference = (*left++ != (UInt8)*right++))) {
            return difference;
        }
    }
    return 0;
}

int pstrchr(UInt8 *characters, char character)
{
    int index;

    index = 0;
    while (index++ < *characters) {
        if (character == characters[index]) {
            return index;
        }
    }
    return 0;
}

void __stdcall c2pstrcpy(unsigned char *dst, const char *src)
{
    int length;

    length = strlen(src);
    if (0xff < length) {
        length = 0xff;
    }
    memmove(1 + dst, src, length);
    *dst = (char)length;
}

void __stdcall p2cstrcpy(char *destination, UInt8 *source)
{
    memcpy(destination, (source + 1), *source);
    destination[*source] = 0;
}

char *mvprintf(char *mybuf, unsigned int len, const char *format, va_list va)
{
    int maxlen;
    char *buf;
    int ret;

    if (mybuf == NULL)
        OS_ASSERT_AT("mybuf != NULL", "StringUtils.c", 138U);

    maxlen = len - 1;
    buf = mybuf;
    ret = vsnprintf(mybuf, maxlen, format, va);
    if (ret < 0) {
        do {
            if (buf != mybuf)
                xfree(buf);
            maxlen <<= 1;
            buf = fn_004263c0(maxlen);
            if (buf == NULL)
                return strncpy(mybuf, "<out of memory>", len);
            ret = vsnprintf(buf, maxlen, format, va);
        } while (ret < 0);
    } else if (ret > maxlen) {
        maxlen = ret + 1;
        buf = fn_004263c0(maxlen);
        if (buf == NULL)
            return strncpy(mybuf, "<out of memory>", len);
        vsnprintf(buf, maxlen, format, va);
    }
    return buf;
}

char *mprintf(char *buffer, int size, char *format, ...)
{
    va_list args = (va_list)&format + (((va_list)(&format + 1) - (va_list)&format + 3) / 4) * 4;
    char *result = mvprintf(buffer, size, format, args);
    return result;
}

int HPrintF(struct StorageHandle *text, char *format, ...)
{
    char *buf;
    int ret;
    va_list arguments;

    va_start(arguments, format);
    buf = mvprintf(pfbuf, 0x100, format, arguments);
    ret = strlen(buf);
    if (Memory_AppendStorageHandle(buf, text, strlen(buf)) != 0) {
        return 0;
    }
    if (buf != pfbuf) {
        xfree(buf);
    }
    return ret;
}

#pragma auto_inline reset
