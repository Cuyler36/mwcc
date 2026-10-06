#ifndef DRIVER_CLSEGS_H
#define DRIVER_CLSEGS_H

#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct AccessPathValueTable {
    unsigned int *values;
    unsigned short capacity;
    unsigned short count;
};
struct PayloadWithValue {
    char name[32];
    unsigned short value;
};
extern Boolean allocate_access_path_value_index(AccessPathValueTable *table, UInt16 *index);
extern struct PayloadWithValue *CLSegs_GetValue(struct AccessPathValueTable *table, unsigned int index);
extern unsigned short CLSegs_GetCount(struct AccessPathValueTable *table);
extern Boolean CLSegs_AddValue(AccessPathValueTable *table, struct PayloadWithValue *value, UInt16 *index);
extern Boolean CLSegs_InitSegments(AccessPathValueTable *segments);
extern unsigned char CLSegs_FreeValues(AccessPathValueTable *array);
extern struct PayloadWithValue *CLSegs_CreatePayloadWithValue(const char *source, UInt16 value);
extern void free_if_not_null(void *ptr);

#ifdef __cplusplus
}
#endif

#endif
