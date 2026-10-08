/* GC 3.0 CLSegs.c; original names and records from explicit STABS. */
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include <string.h>

#pragma pack(push, 2)
typedef struct Segment {
    char name[32];
    UInt16 attrs;
} Segment;
#pragma pack(pop)
typedef struct Segments {
    Segment **segsArray;
    UInt16 arraySize, segsCount;
} Segments;
extern void *__stdcall xmalloc(const char *what, unsigned int size);
extern void *__stdcall xrealloc(const char *what, void *ptr, unsigned int size);
extern void __stdcall xfree(void *ptr);
Segment *Segment_New(const char *source, UInt16 attrs);
void Segment_Free(Segment *ptr);
Segment *Segments_GetSegment(Segments *table, UInt16 index);
UInt16 Segments_Count(Segments *table);
Boolean Segments_Initialize(Segments *segments);
Boolean Segments_AddSegment(Segments *table, Segment *attrs, UInt16 *index);
static Boolean Segments_GrowSegments(Segments *table, UInt16 *index);
Boolean Segments_Terminate(Segments *array);

struct Segment *Segment_New(const char *source, UInt16 attrs)
{
    struct Segment *record;
    record = xmalloc(NULL, sizeof(*record));
    strncpy(record->name, source, sizeof(record->name));
    record->name[sizeof(record->name) - 1] = 0;
    record->attrs = attrs;
    return record;
}

void Segment_Free(Segment *ptr)
{
    if (ptr != NULL) {
        xfree(ptr);
    }
}

struct Segment *Segments_GetSegment(struct Segments *table, UInt16 index)
{
    if (table == NULL) {
        OS_ASSERT_AT("segs != NULL", "CLSegs.c", 137U);
    }
    if ((unsigned short)index < table->segsCount) {
        struct Segment **entries = (struct Segment **)table->segsArray;
        return entries[(unsigned short)index];
    }
    return 0U;
}

unsigned short Segments_Count(struct Segments *table)
{
    if (table == NULL) {
        OS_ASSERT_AT("segs != NULL", "CLSegs.c", 147U);
    }
    return table->segsCount;
}

Boolean Segments_Initialize(Segments *segments)
{
    unsigned short segmentIndex;
    struct Segment *segment;
    if (segments == NULL) {
        OS_ASSERT_AT("segs != NULL", "CLSegs.c", 36U);
    }
    memset(segments, 0, 8U);
    segments->segsArray = NULL;
    segment = Segment_New("Jump Table", 40U);
    Segments_AddSegment(segments, segment, &segmentIndex);
    if (segmentIndex != 0U) {
        OS_ASSERT_AT("idx==0", "CLSegs.c", 44U);
    }
    segment = Segment_New("Main", 65535U);
    Segments_AddSegment(segments, segment, &segmentIndex);
    if (segmentIndex != 1U) {
        OS_ASSERT_AT("idx==1", "CLSegs.c", 49U);
    }
    return 1;
}

Boolean Segments_AddSegment(Segments *table, struct Segment *attrs, UInt16 *index)
{
    UInt16 allocated_index;

    if (Segments_GrowSegments(table, &allocated_index)) {
        struct Segment **entries = (struct Segment **)table->segsArray;
        entries[allocated_index] = attrs;
        *index = allocated_index;
        return 1;
    }
    return 0;
}

static Boolean Segments_GrowSegments(Segments *table, UInt16 *index)
{
    if (table == NULL) {
        OS_ASSERT_AT("segs != NULL", "CLSegs.c", 78U);
    }
    if (table->segsCount >= table->arraySize) {
        UInt16 arraySize;
        Segment **entries;
        table->arraySize += 20U;
        arraySize = table->arraySize;
        entries = (Segment **)xrealloc("segments", table->segsArray, arraySize * sizeof(*entries));
        table->segsArray = entries;
    }
    {
        UInt16 entryIndex;
        entryIndex = table->segsCount;
        table->segsCount += 1U;
        *index = entryIndex;
    }
    return 1;
}
unsigned char Segments_Terminate(Segments *array)
{
    unsigned short index;
    if (array == NULL)
        OS_ASSERT_AT("segs != NULL", "CLSegs.c", 57U);
    if (array->segsArray != NULL) {
        index = 0;
        while (index < array->segsCount) {
            struct Segment **entries = (struct Segment **)array->segsArray;
            Segment_Free(entries[index]);
            index++;
        }
        xfree(array->segsArray);
    }
    array->segsArray = NULL;
    return 1;
}
