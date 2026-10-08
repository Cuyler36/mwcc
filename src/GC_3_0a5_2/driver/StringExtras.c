#include "compiler/common.h"
#include <ctype.h>
#include <string.h>

int __stdcall ustrcmp(char *left, char *right)
{
    int difference;
    do {
        if ((difference = tolower(*left) - tolower(*right++)) != 0)
            return difference;
    } while (*left++ != '\0');
    return 0;
}

char *__stdcall strcatn(char *destination, const char *source, int capacity)
{
    char *output = destination + strlen(destination);
    while (*source && (int)(output - destination + 1) < capacity)
        *output++ = *source++;
    *output = 0;
    return destination;
}

char *__stdcall strcpyn(char *destination, const char *source, unsigned int count, int capacity)
{
    char *output;
    for (output = destination; count-- && *source && (int)(output - destination + 1) < capacity; output++)
        *output = *source++;
    *output = 0;
    return destination;
}

int __stdcall ustrncmp(char *left, char *right, unsigned int count)
{
    int difference;
    while (count-- != 0) {
        if ((difference = tolower(*left) - tolower(*right++)) != 0)
            return difference;
        if (*left++ == 0)
            return 0;
    }
    return 0;
}
