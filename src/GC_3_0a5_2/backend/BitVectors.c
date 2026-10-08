#include "compiler/common.h"

/* Ordinary Mac symbols name these operations. Original source membership
 * remains provisional until Windows source records corroborate it. */
static inline SInt32 word_count(SInt32 bits)
{
    return (SInt32)((UInt32)bits + 31U) >> 5;
}

void bitvectorcopy(UInt32 *destination, const UInt32 *source, SInt32 bits)
{
    SInt32 count = word_count(bits);
    while (count != 0) {
        *destination = *source;
        ++destination;
        ++source;
        --count;
    }
}

SInt32 bitvectorchanged(UInt32 *destination, const UInt32 *source, SInt32 bits)
{
    SInt32 count = word_count(bits);
    SInt32 changed = 0;
    while (count != 0) {
        UInt32 value = *source;
        if (*destination != value)
            changed = 1;
        *destination++ = value;
        ++source;
        --count;
    }
    return changed;
}

void bitvectorinitialize(UInt32 *destination, SInt32 bits, UInt32 value)
{
    SInt32 count = word_count(bits);
    while (count != 0) {
        *destination++ = value;
        --count;
    }
}

void bitvectorunion(UInt32 *destination, const UInt32 *source, SInt32 bits)
{
    SInt32 count = word_count(bits);
    while (count != 0) {
        *destination |= *source;
        ++destination;
        ++source;
        --count;
    }
}

void bitvectorintersect(UInt32 *destination, const UInt32 *source, SInt32 bits)
{
    SInt32 count = word_count(bits);
    while (count != 0) {
        *destination &= *source;
        ++destination;
        ++source;
        --count;
    }
}

SInt32 bitvectorintersectionisempty(const UInt32 *left, const UInt32 *right, SInt32 bits)
{
    SInt32 count = word_count(bits);
    while (count != 0) {
        if (*left & *right)
            return 0;
        ++left;
        ++right;
        --count;
    }
    return 1;
}
