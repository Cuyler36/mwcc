#ifndef DRIVER_RESOURCESTRINGS_H
#define DRIVER_RESOURCESTRINGS_H

#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct ResourceRegistration {
    char *data;
    short resourceId;
    char **value;
} resourceRegistrations[16];
extern char resource_string_buffer[];
extern int ResourceStrings_AddResource(char *resourceData, short resourceId, char **resourceValue);
extern char *ResourceStrings_GetString(short id, short index);
extern ResourceRegistration resourceRegistrations[16];

#ifdef __cplusplus
}
#endif

#endif
