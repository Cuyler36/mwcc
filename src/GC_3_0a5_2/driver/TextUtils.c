#include "compiler/common.h"
#include "driver/Memory.h"
#define Resources_GetHand GC3_UnusedGetHandPrototype
#include "driver/Resources.h"
#undef Resources_GetHand
extern unsigned char **__stdcall Resources_GetHand(SInt32, SInt16);
#include "driver/ResourceStrings.h"
#include "driver/StringUtils.h"
#include <stdio.h>
#include <string.h>

struct StringListHeader { unsigned char countHigh, countLow; };
char *__stdcall c2pstr(char *string);
char *__stdcall p2cstr(char *string);
void __stdcall GetIndString(unsigned char *output, short resourceID, short stringIndex);

char *__stdcall c2pstr(char *string)
{
    unsigned int length;

    length = strlen(string);
    if (length > 255) {
        length = 255;
    }
    memmove(string + 1, string, length);
    *string = (char)length;
    return string;
}

char *__stdcall p2cstr(char *string)
{
    unsigned int length = (unsigned char)*string;
    memmove(string, string + 1, length);
    string[length] = '\0';
    return string;
}

void __stdcall GetIndString(unsigned char *output, short resourceID, short stringIndex)
{
    unsigned char *cursor;
    unsigned char *end;
    short remaining;
    char *message;
    struct StorageHandle *resource;
    short stringCount;
    unsigned char *dest;
    int resourceSize;
    unsigned char length;
    unsigned char buffer[256];

    message = ResourceStrings_GetString(resourceID, stringIndex);
    if (message != NULL) {
        strcpy((char *)buffer, message);
        c2pstr((char *)buffer);
    } else {
        sprintf((char *)buffer, "[Resource string id=%d index=%d not found]", resourceID, stringIndex);
        c2pstr((char *)buffer);
        resource = (struct StorageHandle *)Resources_GetHand(1398034979, resourceID);
        if (resource != NULL) {
            {
                struct StringListHeader *header = (struct StringListHeader *)resource->data;
                stringCount = header->countLow + (header->countHigh << 8);
            }
            if (stringIndex > 0 && stringIndex <= stringCount) {
                unsigned char *strings;
                resourceSize = Memory_GetHandleSize(resource);
                fn_00413a00(resource);
                strings = (unsigned char *)resource->data;
                cursor = strings + sizeof(struct StringListHeader);
                end = strings + resourceSize;
                remaining = stringIndex;
                while (end > cursor && --remaining != 0) {
                    length = *cursor;
                    cursor += length + 1;
                }
                if (cursor < strings + resourceSize) {
                    _pstrcpy(buffer, cursor);
                }
                fn_00413a50(resource);
            }
        }
    }
    cursor = buffer + 1;
    dest = output + 1;
    while (cursor <= buffer + buffer[0]) {
        if (*cursor == 0xD4) {
            *dest = '`';
        } else if (*cursor == 0xD5) {
            *dest = '\'';
        } else if (*cursor == 0xD2 || *cursor == 0xD3) {
            *dest = '"';
        } else if (*cursor == 0xC9 && dest - output < 253) {
            *dest = '.';
            dest[1] = '.';
            dest += 2;
            *dest = '.';
        } else {
            *dest = *cursor;
        }
        ++cursor;
        ++dest;
    }
    *output = dest - output - 1;
}

/* Mac source membership is proven; no retained Windows body is established. */
void __stdcall getindstring(char *output, int resourceID, int stringIndex)
{
    GetIndString((unsigned char *)output, resourceID, stringIndex);
    p2cstr(output);
}

