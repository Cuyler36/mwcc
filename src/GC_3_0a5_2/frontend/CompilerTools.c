#include "compiler/common.h"
#include "compiler/CompilerTools.h"
#include <string.h>
#include <ctype.h>

extern int fn_004c07c0(void);
static void MoreHeapSpace(Pool *pool, SInt32 size);

static inline unsigned short swap16(unsigned short x)
{
    union {
        unsigned short w;
        unsigned char b[2];
    } in, out;
    in.w = x;
    out.b[0] = in.b[1];
    out.b[1] = in.b[0];
    return out.w;
}

static inline unsigned int Swap32(unsigned int x)
{
    union {
        unsigned int w;
        unsigned char b[4];
    } in, out;
    in.w = x;
    out.b[0] = in.b[3];
    out.b[1] = in.b[2];
    out.b[2] = in.b[1];
    out.b[3] = in.b[0];
    return out.w;
}

unsigned int CTool_EndianConvertInPlaceWord32Ptr(unsigned int *p)
{
    unsigned int value = *p;
    value = !fn_004c07c0() ? value : Swap32(value);
    *p = value;
    value = *p;
    return value;
}

short CTool_EndianConvertInPlaceWord16Ptr(short *word)
{
    short *destination = word;
    short value = *destination;
    if (fn_004c07c0() != 0) {
        value = swap16(value);
    }
    *destination = value;
    return *destination;
}

static inline UInt32 swap32(UInt32 x)
{
    UInt32ByteSwapStorage s, d;
    if (!fn_004c07c0())
        return x;
    s.word = x;
    d.bytes[0] = s.bytes[3];
    d.bytes[1] = s.bytes[2];
    d.bytes[2] = s.bytes[1];
    d.bytes[3] = s.bytes[0];
    return d.word;
}

void CTool_EndianConvertWord64(CInt64 ci, char *result)
{
    UInt32 buf[2];
    UInt32 h;
    if (fn_004c07c0() != 0) {
        h = ci.hi;
        buf[0] = swap32(h);
        buf[1] = swap32(ci.lo);
    } else {
        buf[0] = swap32(ci.lo);
        h = ci.hi;
        buf[1] = swap32(h);
    }
    memcpy(result, buf, 8);
}

UInt32 CTool_EndianConvertMem(void *buffer, short size)
{
    unsigned char *front;
    unsigned char *back;
    unsigned char saved;

    if (fn_004c07c0() == 0)
        return;

    front = buffer;
    back = front + size;

    for (;;) {
        back--;
        if (back <= front)
            break;
        saved = *back;
        *back = *front;
        *front = saved;
        front++;
    }
}

unsigned int CTool_EndianConvertWord32(unsigned int value)
{
    if (fn_004c07c0() == 0)
        return value;
    return Swap32(value);
}

UInt16 CTool_EndianConvertWord16(UInt16 word)
{
    if (fn_004c07c0() == 0)
        return word;
    return swap16(word);
}

SInt16 getbit(UInt32 value)
{
    switch ((SInt32)value) {
        case 0:
            return -1;
        case 1:
            return 0;
        case 2:
            return 1;
        case 4:
            return 2;
        case 8:
            return 3;
        case 0x10:
            return 4;
        case 0x20:
            return 5;
        case 0x40:
            return 6;
        case 0x80:
            return 7;
        case 0x100:
            return 8;
        case 0x200:
            return 9;
        case 0x400:
            return 10;
        case 0x800:
            return 11;
        case 0x1000:
            return 12;
        case 0x2000:
            return 13;
        case 0x4000:
            return 14;
        case 0x8000:
            return 15;
        case 0x10000:
            return 16;
        case 0x20000:
            return 17;
        case 0x40000:
            return 18;
        case 0x80000:
            return 19;
        case 0x100000:
            return 20;
        case 0x200000:
            return 21;
        case 0x400000:
            return 22;
        case 0x800000:
            return 23;
        case 0x1000000:
            return 24;
        case 0x2000000:
            return 25;
        case 0x4000000:
            return 26;
        case 0x8000000:
            return 27;
        case 0x10000000:
            return 28;
        case 0x20000000:
            return 29;
        case 0x40000000:
            return 30;
        case (SInt32)0x80000000:
            return 31;
    }
    return -2;
}

extern char *fn_00403ff0(int);
static inline int gc3_tolower(int value)
{
    if (value < 0 || value >= 256)
        return value;
    return (*(UInt8 ***)(fn_00403ff0(1) + 0x1bc))[4][value];
}

void CToLowercase(char *src, char *dst)
{
    while ((*dst++ = (char)gc3_tolower(*src++)) != 0)
        ;
}

void memclrw(void *buffer, unsigned int size)
{
    memset(buffer, 0, size);
}

char *ScanDec(char *src, SInt32 *value, Boolean *flag)
{
    unsigned int val = 0U;
    short digit;
    *flag = 0;
    for (;;) {
        digit = (short)(*src - '0');
        if (digit < 0 || digit > 9)
            break;
        if (val >= 0x19999999U) {
            if (val > 0x19999999U || digit > 5)
                *flag = 1;
        }
        val = (val << 3) + (val << 1) + digit;
        src++;
    }
    *value = val;
    return src;
}


static Pool bheap, aheap, oheap, lheap, gheap;
static SInt16 lheaplockcount;
static void (*heaperror)(void);
static void *data_006dac60[128];
struct GC3HeapAllocation { struct GC3HeapAllocation *next, *prev; };
static struct GC3HeapAllocation *data_006daeca;
extern void fn_004c5160(void *(*allocator)(SInt32));
extern void fn_004c5190(void *(*allocator)(SInt32));
extern void *aalloc(SInt32 size);

static inline void reset_pool(Pool *pool)
{
    PoolNode *node;
    for (node = pool->head; node; node = node->next) {
        if (node == pool->cur) {
            node->avail = node->size - sizeof(PoolNode);
            break;
        }
        node->avail = node->size - sizeof(PoolNode);
    }
    node = pool->head;
    pool->cur = node;
    pool->ptr = (char *)(node + 1);
    pool->free = node->avail;
}

void freeaheap(void)
{
    reset_pool(&aheap);
    fn_004c5160(aalloc);
    fn_004c5190(aalloc);
}

void freeoheap(void) { reset_pool(&oheap); }
void freelheap(void) { if (lheaplockcount == 0) reset_pool(&lheap); }
void unlocklheap(void) { if (lheaplockcount > 0) --lheaplockcount; }
void locklheap(void) { ++lheaplockcount; }

void *aalloc(SInt32 size)
{
    char *result;
    size = (size + 7) & ~7U;
    if (aheap.free < size)
        MoreHeapSpace(&aheap, size);
    aheap.free -= size;
    result = aheap.ptr;
    aheap.ptr += size;
    return result;
}

void *oalloc(SInt32 size)
{
    char *result;
    size = (size + 7) & ~7U;
    if (oheap.free < size)
        MoreHeapSpace(&oheap, size);
    oheap.free -= size;
    result = oheap.ptr;
    oheap.ptr += size;
    return result;
}

void *lalloc(SInt32 size)
{
    char *result;
    size = (size + 7) & ~7U;
    if (lheap.free < size)
        MoreHeapSpace(&lheap, size);
    lheap.free -= size;
    result = lheap.ptr;
    lheap.ptr += size;
    return result;
}

static inline void *gc3_galloc(SInt32 size)
{
    char *result;
    size = (size + 7) & ~7U;
    if (gheap.free < (SInt32)size)
        MoreHeapSpace(&gheap, size);
    gheap.free -= size;
    result = gheap.ptr;
    gheap.ptr += size;
    return result;
}

void *galloc(SInt32 size) { return gc3_galloc(size); }

extern void fn_0044ced0(void *);
extern void *fn_0044ceb0(SInt32);
extern void *fn_0044cec0(SInt32);
extern Boolean fn_0044cf40(void *, UInt32);
extern void fn_0044d040(void *);
extern void fn_0044d0a0(void *);
static void (*GListErrorProc)(void);
void AppendGListName(GList *buf, const char *str)
{
    UInt32 len = strlen(str) + 1;
    if (buf->size + len > buf->hndlsize) {
        struct StorageHandle *handle;
        buf->hndlsize += len + buf->growsize;
        handle = (struct StorageHandle *)buf->data;
        if (!fn_0044cf40(handle, buf->hndlsize)) {
            if (GListErrorProc != NULL) {
                GListErrorProc();
            }
        }
    }
    memcpy(buf->data[0] + buf->size, str, len);
    buf->size += len;
}

void AppendGListWord(GList *buffer, SInt16 value)
{
    Boolean resized;
    char *destination;
    const char *valueBytes;

    if (buffer->size + (SInt32)sizeof(value) > buffer->hndlsize) {
        buffer->hndlsize += buffer->growsize + (SInt32)sizeof(value);
        resized = fn_0044cf40((struct StorageHandle *)buffer->data, buffer->hndlsize);
        if (!resized && GListErrorProc) {
            (*GListErrorProc)();
        }
    }
    destination = *buffer->data + buffer->size;
    buffer->size += sizeof(value);
    valueBytes = (const char *)&value;
    *destination = *valueBytes;
    valueBytes = (const char *)&value;
    destination[1] = valueBytes[1];
}

union U16Bytes { UInt16 value; UInt8 b[2]; };
static inline UInt16 SwapOutputWord(UInt16 x)
{
    union {
        UInt16 w;
        UInt8 b[2];
    } t, r;
    if (!fn_004c07c0())
        return x;
    t.w = x;
    r.b[0] = t.b[1];
    r.b[1] = t.b[0];
    return r.w;
}

void AppendGListTargetEndianWord(GList *buf, UInt16 word)
{
    char *dest;
    const U16Bytes *bytes;
    if (buf->size + 2 > buf->hndlsize) {
        buf->hndlsize += buf->growsize + 2;
        if (!fn_0044cf40((StorageHandle *)buf->data, buf->hndlsize)) {
            if (GListErrorProc != NULL)
                GListErrorProc();
        }
    }
    dest = *buf->data + buf->size;
    buf->size += 2;
    word = SwapOutputWord(word);
    bytes = (const U16Bytes *)&word;
    dest[0] = bytes->b[0];
    dest[1] = ((const U16Bytes *)&word)->b[1];
}

static inline UInt32 MaybeSwap32(UInt32 x)
{
    union {
        UInt32 l;
        UInt8 b[4];
    } t, r;
    if (!fn_004c07c0())
        return x;
    t.l = x;
    r.b[0] = t.b[3];
    r.b[1] = t.b[2];
    r.b[2] = t.b[1];
    r.b[3] = t.b[0];
    return r.l;
}
static inline void CopyFourBytes(UInt8 *dest, const UInt8 *source)
{
    dest[0] = source[0];
    dest[1] = source[1];
    dest[2] = source[2];
    dest[3] = source[3];
}

void AppendGListTargetEndianLong(GList *buf, UInt32 value)
{
    UInt8 *dest;
    if (buf->size + 4 > buf->hndlsize) {
        buf->hndlsize += buf->growsize + 4;
        if (!fn_0044cf40((struct StorageHandle *)buf->data, buf->hndlsize)) {
            if (GListErrorProc != NULL)
                GListErrorProc();
        }
    }
    dest = (UInt8 *)*buf->data + buf->size;
    buf->size += 4;
    value = MaybeSwap32(value);
    CopyFourBytes(dest, (const UInt8 *)&value);
}

void AppendGListLong(GList *buffer, SInt32 value)
{
    Boolean allocated;
    char *destination;

    if (buffer->size + (SInt32)sizeof(value) > buffer->hndlsize) {
        buffer->hndlsize += buffer->growsize + (SInt32)sizeof(value);
        allocated = fn_0044cf40((struct StorageHandle *)buffer->data, buffer->hndlsize);
        if (!allocated && GListErrorProc != NULL) {
            (*GListErrorProc)();
        }
    }
    destination = *buffer->data + buffer->size;
    buffer->size += sizeof(value);
    destination[0] = ((const NativeLongBytes *)&value)->byte0;
    destination[1] = ((const NativeLongBytes *)&value)->byte1;
    destination[2] = ((const NativeLongBytes *)&value)->byte2;
    destination[3] = ((const NativeLongBytes *)&value)->byte3;
}

void fn_0046d530(GList *buf, const char *str)
{
    UInt32 len = strlen(str);
    if ((buf->size + len) > (UInt32)buf->hndlsize) {
        buf->hndlsize += len + buf->growsize;
        if (!fn_0044cf40((struct StorageHandle *)buf->data, buf->hndlsize) && GListErrorProc != NULL)
            GListErrorProc();
    }
    memcpy(*buf->data + buf->size, str, len);
    buf->size += len;
}

void AppendGListByte(GList *buffer, SInt8 value)
{
    if (buffer->size + 1 > buffer->hndlsize) {
        Boolean success;
        buffer->hndlsize += buffer->growsize + 1;
        success = fn_0044cf40((struct StorageHandle *)buffer->data, buffer->hndlsize);
        if (!success && GListErrorProc != NULL) {
            (*GListErrorProc)();
        }
    }
    (*buffer->data)[buffer->size++] = value;
}

void ShrinkGList(GList *list)
{
    list->hndlsize = list->size;
    fn_0044cf40((struct StorageHandle *)list->data, list->hndlsize);
}

void UnlockGList(GList *entry)
{
    fn_0044d0a0(entry->data);
}

void LockGList(GList *entry)
{
    fn_0044d040(entry->data);
}

void FreeGList(GList *storage)
{
    if (storage->data != NULL) {
        fn_0044ced0(storage->data);
        storage->data = NULL;
    }
    storage->hndlsize = 0;
    storage->size = storage->hndlsize;
}

void *AppendGListData(GList *buffer, const void *source, SInt32 count)
{
    char *data;
    Boolean result;
    if (buffer->size + count > buffer->hndlsize) {
        buffer->hndlsize += count + buffer->growsize;
        result = fn_0044cf40((struct StorageHandle *)buffer->data, buffer->hndlsize);
        if (result == 0 && GListErrorProc != NULL) {
            (*GListErrorProc)();
        }
    }
    data = memcpy(*buffer->data + buffer->size, source, count);
    buffer->size += count;
    return data;
}

SInt16 InitGList(GList *allocation, SInt32 size)
{
    allocation->data = fn_0044cec0(size);
    if (!allocation->data) {
        allocation->data = fn_0044ceb0(size);
        if (!allocation->data)
            return -1;
    }
    allocation->size = 0;
    allocation->growsize = (int)size >> 1;
    allocation->hndlsize = size;
    return 0;
}

void AppendGListNoData(GList *buffer, SInt32 additionalLength)
{
    if (buffer->size + additionalLength > buffer->hndlsize) {
        buffer->hndlsize += additionalLength + buffer->growsize;
        if (!fn_0044cf40((struct StorageHandle *)buffer->data, buffer->hndlsize) && GListErrorProc != NULL) {
            GListErrorProc();
        }
    }
    buffer->size += additionalLength;
}


static SInt32 hash_name_id;
static HashNameNode **name_hash_nodes;

void InitNameHash(void)
{
    name_hash_nodes = gc3_galloc(8192);
    memset(name_hash_nodes, 0, 8192);
    hash_name_id = 1;
}

static inline short gc3_name_hash(const char *text)
{
    SInt16 length = 0;
    UInt8 checksum = 0;
    UInt8 c = *text;
    while (c) {
        checksum = ((checksum >> 3) | (checksum << 5)) + c;
        ++text;
        ++length;
        c = *text;
        if (length == 255) break;
    }
    return ((length & 255) << 8 | checksum) & 2047;
}

short CHash(const char *text) { return gc3_name_hash(text); }

HashNameNode *GetHashNameNode(const char *text)
{
    SInt16 bucket = gc3_name_hash(text);
    HashNameNode *entry, *tail;
    entry = name_hash_nodes[bucket];
    if (!entry) {
        entry = gc3_galloc(strlen(text) + 12);
        name_hash_nodes[bucket] = entry;
        entry->next = NULL;
        entry->id = -1;
        entry->hashval = bucket;
        strcpy(entry->name, text);
        return entry;
    }
    for (;;) {
        if (!strcmp(text, entry->name)) return entry;
        if (!entry->next) {
            entry->next = gc3_galloc(strlen(text) + 12);
            tail = entry->next;
            tail->next = NULL;
            tail->id = -1;
            tail->hashval = bucket;
            strcpy(tail->name, text);
            return tail;
        }
        entry = entry->next;
    }
}

HashNameNode *GetHashNameNodeExport(const char *text)
{
    SInt16 bucket = gc3_name_hash(text);
    HashNameNode *entry, *tail;
    entry = name_hash_nodes[bucket];
    if (!entry) {
        entry = gc3_galloc(strlen(text) + 12);
        name_hash_nodes[bucket] = entry;
        entry->next = NULL;
        entry->id = hash_name_id++;
        entry->hashval = bucket;
        strcpy(entry->name, text);
        return entry;
    }
    for (;;) {
        if (!strcmp(text, entry->name)) {
            if (entry->id < 0) entry->id = hash_name_id++;
            return entry;
        }
        if (!entry->next) {
            entry->next = gc3_galloc(strlen(text) + 12);
            tail = entry->next;
            tail->next = NULL;
            tail->id = hash_name_id++;
            tail->hashval = bucket;
            strcpy(tail->name, text);
            return tail;
        }
        entry = entry->next;
    }
}

int CTool_TotalHeapSize(void)
{
    SInt32 total = 0;
    PoolNode *node;
    for (node = gheap.head; node; node = node->next) total += node->size;
    for (node = lheap.head; node; node = node->next) total += node->size;
    for (node = oheap.head; node; node = node->next) total += node->size;
    for (node = aheap.head; node; node = node->next) total += node->size;
    for (node = bheap.head; node; node = node->next) total += node->size;
    return total;
}

extern Boolean data_00670c18;
static void MoreHeapSpace(Pool *pool, SInt32 size)
{
    PoolNode **block;
    PoolNode *node;

    if ((node = pool->head) != NULL) {
        pool->cur->avail = pool->free;
        while (node != NULL) {
            if (node->avail >= size)
                goto selected;
            node = node->next;
        }
    }
    size += pool->overhead;
    if (!data_00670c18)
        goto fallback;
    block = fn_0044cec0(size * 2);
    if (block == NULL) {
        block = fn_0044cec0(size);
        if (block == NULL) {
        fallback:
            block = fn_0044ceb0(size);
            if (block == NULL) {
                if (heaperror != NULL)
                    heaperror();
                return;
            }
        }
    } else {
        size <<= 1;
    }
    fn_0044d040(block);
    node = *block;
    node->next = pool->head;
    pool->head = node;
    node->block = block;
    node->size = size;
    node->avail = size - sizeof(PoolNode);
selected:
    pool->cur = node;
    pool->free = node->avail;
    pool->ptr = (char *)node + node->size - node->avail;
}


void setheaperror(void (*callback)(void)) { heaperror = callback; }
void (*getheaperror(void))(void) { return heaperror; }

static inline void clear_heap(Pool *pool)
{
    PoolNode *node = pool->head;
    while (node) {
        void *handle = node->block;
        node = node->next;
        fn_0044ced0(handle);
    }
    memset(pool, 0, sizeof(*pool));
}

extern void *fn_0044d100(SInt32);
extern void fn_0044d140(void *);

static inline void release_all_direct(void)
{
    while (data_006daeca) {
        struct GC3HeapAllocation *node = data_006daeca;
        if (node->prev) {
            node->prev->next = node->next;
            if (node->prev->next) node->next->prev = node->prev;
        } else {
            data_006daeca = node->next;
            if (data_006daeca) node->next->prev = NULL;
        }
        fn_0044d140(node);
    }
}

void releaseheaps(void)
{
    release_all_direct();
    clear_heap(&gheap);
    clear_heap(&lheap);
    clear_heap(&oheap);
    clear_heap(&aheap);
    clear_heap(&bheap);
}

void fn_0046c7b0(void *pointer)
{
    struct GC3HeapAllocation *node;
    if (!pointer) return;
    node = (struct GC3HeapAllocation *)((char *)pointer - 8);
    if (node->prev) {
        node->prev->next = node->next;
        if (node->prev->next) node->next->prev = node->prev;
    } else {
        data_006daeca = node->next;
        if (data_006daeca) node->next->prev = NULL;
    }
    fn_0044d140(node);
}

void *fn_0046c800(SInt32 size)
{
    struct GC3HeapAllocation *node = fn_0044d100(size + 8);
    if (node) {
        node->prev = NULL;
        node->next = data_006daeca;
        if (node->next) node->next->prev = node;
        data_006daeca = node;
        return node + 1;
    }
    if (heaperror) heaperror();
    return NULL;
}

void fn_0046c6e0(void *pointer, UInt32 size)
{
    SInt32 index = (((size + 7) & ~7U) >> 3) - 1;
    if (index >= 128) {
        if (heaperror) heaperror();
        return;
    }
    *(void **)pointer = data_006dac60[index];
    data_006dac60[index] = pointer;
}

void *fn_0046c730(UInt32 size)
{
    void *node;
    SInt32 index;
    size = (size + 7) & ~7U;
    index = (size >> 3) - 1;
    if (index < 128) {
        if (data_006dac60[index]) {
            node = data_006dac60[index];
            data_006dac60[index] = *(void **)node;
            return node;
        }
    } else if (heaperror) heaperror();
    if ((UInt32)gheap.free < size) MoreHeapSpace(&gheap, size);
    gheap.free -= size;
    node = gheap.ptr;
    gheap.ptr += size;
    return node;
}

void fn_0046c860(void)
{
    clear_heap(&gheap);
    aheap.overhead = 0x40000;
    MoreHeapSpace(&aheap, 0);
}

void fn_0046c8b0(void)
{
    release_all_direct();
    clear_heap(&gheap);
}

SInt16 initheaps(void (*callback)(void))
{
    heaperror = NULL;
    lheaplockcount = 0;
    data_006daeca = NULL;
    memset(data_006dac60, 0, sizeof(data_006dac60));
    memset(&gheap, 0, sizeof(gheap));
    memset(&lheap, 0, sizeof(lheap));
    memset(&oheap, 0, sizeof(oheap));
    memset(&aheap, 0, sizeof(aheap));
    memset(&bheap, 0, sizeof(bheap));
    gheap.overhead = 0x80000;
    MoreHeapSpace(&gheap, 0);
    gheap.overhead = 0x40000;
    heaperror = callback;
    return gheap.cur ? 0 : -1;
}

SInt16 fn_0046cb30(void (*callback)(void))
{
    heaperror = NULL;
    lheaplockcount = 0;
    data_006daeca = NULL;
    memset(data_006dac60, 0, sizeof(data_006dac60));
    memset(&gheap, 0, sizeof(gheap));
    memset(&lheap, 0, sizeof(lheap));
    memset(&oheap, 0, sizeof(oheap));
    memset(&aheap, 0, sizeof(aheap));
    memset(&bheap, 0, sizeof(bheap));
    gheap.overhead = 0x80000;
    lheap.overhead = 0x40000;
    oheap.overhead = 0x4000;
    aheap.overhead = 0x40000;
    bheap.overhead = 0x4000;
    MoreHeapSpace(&gheap, 0);
    MoreHeapSpace(&lheap, 0);
    MoreHeapSpace(&oheap, 0);
    MoreHeapSpace(&aheap, 0);
    MoreHeapSpace(&bheap, 0);
    gheap.overhead = 0x40000;
    lheap.overhead = 0x20000;
    oheap.overhead = 0x4000;
    aheap.overhead = 0x40000;
    bheap.overhead = 0x4000;
    heaperror = callback;
    return gheap.cur && lheap.cur && oheap.cur && aheap.cur && bheap.cur ? 0 : -1;
}

struct GC3HeapInfo {
    SInt32 blockCount, blockSize, totalSize, freeSize;
    SInt32 averageSize, averageFree, largestFree;
};

static inline void getheapinfo(struct GC3HeapInfo *info, Pool *pool)
{
    PoolNode *node;
    info->blockSize = pool->overhead;
    for (node = pool->head; node; node = node->next) {
        info->totalSize += node->size - sizeof(PoolNode);
        info->freeSize += node->avail;
        ++info->blockCount;
        if (node->avail > info->largestFree) info->largestFree = node->avail;
    }
    info->averageSize = info->totalSize / info->blockCount;
    info->averageFree = info->freeSize / info->blockCount;
}

void CTool_GetHeapInfo(struct GC3HeapInfo *info, SInt8 kind)
{
    memset(info, 0, sizeof(*info));
    switch (kind) {
    case -1: break;
    case 0: getheapinfo(info, &gheap); break;
    case 1: getheapinfo(info, &lheap); break;
    case 2: getheapinfo(info, &oheap); break;
    case 3: getheapinfo(info, &aheap); break;
    case 4: getheapinfo(info, &bheap); break;
    case 5:
        getheapinfo(info, &gheap);
        getheapinfo(info, &lheap);
        getheapinfo(info, &oheap);
        getheapinfo(info, &aheap);
        getheapinfo(info, &bheap);
        break;
    }
}

UInt32 fn_0046d0a0(void)
{
    UInt32 total = 0;
    PoolNode *node;
    for (node = gheap.head; node; node = node->next) total += node->size;
    return total;
}

void memclr(void *buffer, UInt32 size) { memset(buffer, 0, size); }

static char *data_0067dc6c[14] = {
    "### Error: Compilation aborted at end of file ###",
    "Save precompiled header as...",
    "### Error while creating precompiled headerfile (OSErr %ld) ###",
    "### Error while writing precompiled headerfile (OSErr %ld) ### ",
    "internal compiler error (report to <cw_bug@freescale.com>)\nwhile executing in file '%s' line: %ld\n(compiling '%s' in '%s')",
    "ran out of registers--turn on Global Optimization for this function",
    "### Error: Out of memory ###",
    "### User break detected ###",
    "### Error: Cannot open main file ###",
    "Analyzing symbol table...",
    "Writing precompiled header file...",
    "Running instrumenter...",
    "Recompiling instrumented code...",
    "compiler assertion '%s' failed\nwhile executing in file '%s' line: %ld\n(compiling '%s' in '%s')"
};

void CompilerGetCString(short index, char *destination)
{
    int resourceIndex = index;
    if (resourceIndex >= 1 && resourceIndex < 15)
        strcpy(destination, data_0067dc6c[resourceIndex - 1]);
    else
        strcpy(destination, "<unknown error>");
}

char *CTool_PtoCstr(unsigned char *text)
{
    char *cursor = (char *)text;
    SInt32 length = (UInt8)*cursor;
    while (length > 0) {
        *cursor = cursor[1];
        --length;
        ++cursor;
    }
    *cursor = 0;
    return (char *)text;
}

int fn_0046d9f0(char *first, char *second)
{
    char a, b;
    do {
        b = gc3_tolower(*second++);
        a = gc3_tolower(*first++);
        if (a != b) return a - b;
    } while (a);
    return 0;
}

void NameHashExportReset(void)
{
    HashNameNode *entry;
    SInt16 bucket;
    for (bucket = 0; bucket < 2048; ++bucket)
        for (entry = name_hash_nodes[bucket]; entry; entry = entry->next)
            entry->id = -1;
    hash_name_id = 1;
}
