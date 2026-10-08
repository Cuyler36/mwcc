#include "compiler/common.h"
#pragma pack(push, 1)
struct ConversionBlockEntry {
    unsigned int value;
    UInt16 shortValue;
    unsigned int trailingValue;
};
#pragma pack(pop)
struct ConversionBlockHeader {
    unsigned int size;
    unsigned int value;
};
struct ElfSymbolRecord {
    unsigned int name;           /* 0x00: ELF_Endian_ConvertSymbolRecord converts symbol name index */
    unsigned int value;          /* 0x04: ELF_Endian_ConvertSymbolRecord converts symbol value */
    unsigned int size;           /* 0x08: ELF_Endian_ConvertSymbolRecord converts symbol size */
    unsigned char info;          /* 0x0c: ELF_Endian_ConvertSymbolRecord leaves ELF symbol info byte unchanged */
    unsigned char other;         /* 0x0d: ELF_Endian_ConvertSymbolRecord leaves ELF symbol other byte unchanged */
    unsigned short sectionIndex; /* 0x0e: ELF_Endian_ConvertSymbolRecord converts and returns section index */
};
struct RecordBounds {
    int length;
    int endOffset;
};

int swap_tagged_record_data(void *,unsigned short,unsigned char);
long double read_double(UInt8 *,unsigned char);
#include "compiler/CompilerTools.h"
#include "driver/libimp-eabi-ppc.h"

/* Original callback name is unavailable in the supplied Mac symbols. */
int (*DAT_005805e0)(const char *,int);

/* Bounds of a serialized record in the input buffer. */

int swap_tagged_record_data(void *,unsigned short,unsigned char);
long double read_double(UInt8 *,unsigned char);
#include "compiler/CompilerTools.h"
#include "driver/libimp-eabi-ppc.h"

/* Original callback name is unavailable in the supplied Mac symbols. */
int (*DAT_005805e0)(const char *,int);

/* Bounds of a serialized record in the input buffer. */

void swap_tagged_records(unsigned char *data, unsigned int size, int (*errorHandler)(const char *, int),
                         unsigned char swapBeforeRead)
{
    int offset = 0;
    int recordLength;
    unsigned short tag;
    volatile int recordEnd;
    int length;
    unsigned short count;
    unsigned int *valueAddress;
    int value;
    int scalar;
    unsigned char character;
    unsigned int *wordAddress;
    short *shortAddress;

    DAT_005805e0 = errorHandler;
    while (offset < size) {
        recordEnd = offset;
        if (swapBeforeRead) {
            recordLength = *(unsigned int *)(data + offset);
            CTool_EndianConvertInPlaceWord32Ptr((unsigned int *)(data + offset));
        } else {
            CTool_EndianConvertInPlaceWord32Ptr((unsigned int *)(data + offset));
            recordLength = *(unsigned int *)(data + offset);
        }
        if (recordLength < 8) {
            if (recordLength <= 0)
                (*DAT_005805e0)("ELF_Endian.c", 0x1fd);
            offset += recordLength;
        } else {
            if (swapBeforeRead) {
                count = *(short *)((offset + 4) + data);
                CTool_EndianConvertInPlaceWord16Ptr((short *)((offset + 4) + data));
            } else {
                shortAddress = (short *)((offset + 4) + data);
                CTool_EndianConvertInPlaceWord16Ptr(shortAddress);
                count = *shortAddress;
            }
            offset += 6;
            if (count == 0) {
                recordLength = recordLength - 6;
                offset += recordLength;
            } else {
                /* Preserve the original volatile boundary update. */
                recordEnd=recordEnd;
                recordEnd+=recordLength;
                while (offset < recordEnd) {
                    if (swapBeforeRead) {
                        shortAddress = (short *)(data + offset);
                        tag = (unsigned short)*shortAddress;
                        CTool_EndianConvertInPlaceWord16Ptr(shortAddress);
                    } else {
                        shortAddress = (short *)(data + offset);
                        CTool_EndianConvertInPlaceWord16Ptr(shortAddress);
                        tag = (unsigned short)*shortAddress;
                    }
                    offset += 2;
                    switch ((unsigned short)tag & 0xf) {
                        case 1:
                            if (swapBeforeRead) {
                                value = *(int *)(data + offset);
                                valueAddress = (unsigned int *)(data + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                            } else {
                                valueAddress = (unsigned int *)(data + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                                value = *valueAddress;
                            }
                            offset += 4;
                            break;
                        case 2:
                            if (swapBeforeRead) {
                                value = *(int *)(data + offset);
                                valueAddress = (unsigned int *)(data + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                            } else {
                                wordAddress = (unsigned int *)(data + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(wordAddress);
                                value = *wordAddress;
                            }
                            offset += 4;
                            break;
                        case 3:
                            offset += swap_tagged_record_data(data + offset, (unsigned short)tag, swapBeforeRead);
                            break;
                        case 4:
                            if (swapBeforeRead) {
                                length = *(int *)(data + offset);
                                valueAddress = (unsigned int *)(data + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                            } else {
                                valueAddress = (unsigned int *)(data + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                                length = *(int *)(data + offset);
                            }
                            offset += 4;
                            if ((unsigned short)tag == 0xf4) {
                                while (length != 0) {
                                    if (swapBeforeRead) {
                                        value = *(int *)(data + offset);
                                        valueAddress = (unsigned int *)(data + offset);
                                        CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                                    } else {
                                        valueAddress = (unsigned int *)(data + offset);
                                        CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                                        value = *(int *)(data + offset);
                                    }
                                    offset += 4;
                                    length -= 4;
                                    while (data[offset] != '\0') {
                                        offset++;
                                        length--;
                                    }
                                    length--;
                                    offset++;
                                }
                            }
                            break;
                        case 5:
                            if (swapBeforeRead) {
                                shortAddress = (short *)(data + offset);
                                scalar = *shortAddress;
                                CTool_EndianConvertInPlaceWord16Ptr(shortAddress);
                            } else {
                                shortAddress = (short *)(data + offset);
                                CTool_EndianConvertInPlaceWord16Ptr(shortAddress);
                                scalar = *shortAddress;
                            }
                            offset += 2;
                            break;
                        case 6:
                            if (swapBeforeRead) {
                                scalar = *(int *)(data + offset);
                                valueAddress = (unsigned int *)(data + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                            } else {
                                valueAddress = (unsigned int *)(data + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                                scalar = *(int *)(data + offset);
                            }
                            offset += 4;
                            break;
                        case 7:
                            read_double(data + offset, swapBeforeRead);
                            offset += 8;
                            break;
                        case 8:
                            while ((character = data[offset]) != '\0')
                                offset++;
                            offset++;
                            break;
                    }
                }
            }
        }
    }
    (void)value;
}

int swap_tagged_record_data(void *data, unsigned short kind, unsigned char readBeforeSwap)
{
    int offset = 0;
    char *bytes;
    unsigned int *valueAddress;
    short remaining;
    unsigned char tag;
    short length;
    int size;
    int registerValue;
    int extendedValue;
    int constantValue;
    int typeReference;
    short shortValue;
    short extraValue;
    unsigned char flag = 0;

    bytes=data;
    if (readBeforeSwap != 0) {
        length = *(short *)bytes;
        CTool_EndianConvertInPlaceWord16Ptr((short *)bytes);
    } else {
        CTool_EndianConvertInPlaceWord16Ptr((short *)bytes);
        length = *(short *)bytes;
    }
    remaining = length;
    offset += 2;
    if (length > 0) {
        do {
            tag = *(unsigned char *)(bytes + offset);
            offset++;
            remaining--;
            if (kind == 0x23 || kind == 0x2a3 || kind == 0x2013 || kind == 0x293 || kind == 0x303 || kind == 0x2343) {
                switch (tag) {
                    case 1:
                    case 2:
                    case 4:
                    case 0x80:
                    case 0x81:
                        if (readBeforeSwap != 0) {
                            (void)(size = *(int *)(bytes + offset));
                            valueAddress = (unsigned int *)(bytes + offset);
                            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                        } else {
                            valueAddress = (unsigned int *)(bytes + offset);
                            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                            (void)(size = *valueAddress);
                        }
                        offset += 4;
                        remaining -= 4;
                        break;
                    case 3:
                        if (readBeforeSwap != 0) {
                            valueAddress = (unsigned int *)(bytes + offset);
                            (void)(registerValue = *valueAddress);
                            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                        } else {
                            valueAddress = (unsigned int *)(bytes + offset);
                            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                            (void)(registerValue = *valueAddress);
                        }
                        offset += 4;
                        remaining -= 4;
                        break;
                    case 5:
                    case 6:
                    case 7:
                        break;
                    case 0x93:
                        offset++;
                        remaining--;
                        break;
                    case 0xe0:
                        if (readBeforeSwap != 0) {
                            valueAddress = (unsigned int *)(bytes + offset);
                            (void)(extendedValue = *valueAddress);
                            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                        } else {
                            valueAddress = (unsigned int *)(bytes + offset);
                            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                            (void)(extendedValue = *valueAddress);
                        }
                        offset += 4;
                        remaining -= 4;
                        break;
                }
            } else if (kind == 0x83) {
                if (remaining < 4) {
                    if (readBeforeSwap != 0) {
                        valueAddress = (unsigned int *)(bytes + offset - 1);
                        (void)(constantValue = *valueAddress);
                        CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                    } else {
                        valueAddress = (unsigned int *)(bytes + offset - 1);
                        CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                        (void)(constantValue = *valueAddress);
                    }
                    offset += 3;
                    remaining -= 3;
                }
            } else if (kind == 0x63) {
                if (remaining < 2) {
                    if (readBeforeSwap != 0) {
                        (void)(shortValue = *(short *)(bytes + offset - 1));
                        CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset - 1));
                    } else {
                        CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset - 1));
                        (void)(shortValue = *(short *)(bytes + offset - 1));
                    }
                    offset += 1;
                    remaining -= 1;
                }
            } else if (kind == 0xa3) {
                if (!flag)
                    flag = 1;
                switch (tag) {
                    case 8:
                        if (readBeforeSwap != 0) {
                            kind = *(short *)(bytes + offset);
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        } else {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                            kind = *(short *)(bytes + offset);
                        }
                        offset += 2;
                        remaining -= 2;
                        if (kind == 0x55) {
                            if (readBeforeSwap != 0) {
                                (void)(extraValue = *(short *)(bytes + offset));
                                CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                            } else {
                                CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                                (void)(extraValue = *(short *)(bytes + offset));
                            }
                            offset += 2;
                            remaining -= 2;
                        } else if (kind == 0x63 || kind == 0x83) {
                            size = swap_tagged_record_data(bytes + offset, kind, readBeforeSwap);
                            offset += size;
                            remaining -= size;
                        } else if (kind == 0x72) {
                            if (readBeforeSwap != 0) {
                                valueAddress = (unsigned int *)(bytes + offset);
                                (void)(typeReference = *valueAddress);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                            } else {
                                valueAddress = (unsigned int *)(bytes + offset);
                                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                                (void)(typeReference = *valueAddress);
                            }
                            offset += 4;
                            remaining -= 4;
                        }
                        flag = 0;
                        break;
                    case 0:
                        if (readBeforeSwap != 0) {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        } else {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        }
                        if (readBeforeSwap != 0) {
                            (void)(offset + 2 + bytes);
                            CTool_EndianConvertInPlaceWord32Ptr((unsigned int *)(offset + 2 + bytes));
                        } else {
                            CTool_EndianConvertInPlaceWord32Ptr((unsigned int *)(offset + 2 + bytes));
                        }
                        if (readBeforeSwap != 0) {
                            (void)(offset + 6 + bytes);
                            CTool_EndianConvertInPlaceWord32Ptr((unsigned int *)(offset + 6 + bytes));
                        } else {
                            CTool_EndianConvertInPlaceWord32Ptr((unsigned int *)(offset + 6 + bytes));
                        }
                        offset += 10;
                        remaining -= 10;
                        break;
                    case 1:
                        if (readBeforeSwap != 0) {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        } else {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        }
                        if (readBeforeSwap != 0) {
                            (void)(offset + 2 + bytes);
                            CTool_EndianConvertInPlaceWord32Ptr((unsigned int *)(offset + 2 + bytes));
                        } else {
                            CTool_EndianConvertInPlaceWord32Ptr((unsigned int *)(offset + 2 + bytes));
                        }
                        offset += 6;
                        remaining -= 6;
                        size = swap_tagged_record_data(bytes + offset, 0x23, readBeforeSwap);
                        offset += size;
                        remaining -= size;
                        break;
                    case 2:
                        if (readBeforeSwap != 0) {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        } else {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        }
                        offset += 2;
                        remaining -= 2;
                        size = swap_tagged_record_data(bytes + offset, 0x23, readBeforeSwap);
                        offset += size;
                        remaining -= size;
                        if (readBeforeSwap != 0) {
                            valueAddress = (unsigned int *)(bytes + offset);
                            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                        } else {
                            valueAddress = (unsigned int *)(bytes + offset);
                            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
                        }
                        offset += 4;
                        remaining -= 4;
                        break;
                    case 3:
                        if (readBeforeSwap != 0) {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        } else {
                            CTool_EndianConvertInPlaceWord16Ptr((short *)(bytes + offset));
                        }
                        offset += 2;
                        remaining -= 2;
                        size = swap_tagged_record_data(bytes + offset, 0x23, readBeforeSwap);
                        offset += size;
                        remaining -= size;
                        size = swap_tagged_record_data(bytes + offset, 0x23, readBeforeSwap);
                        offset += size;
                        remaining -= size;
                        break;
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        flag = 0;
                        kind = 0;
                        break;
                }
            }
        } while (remaining > 0);
    }
    return offset;
}

#pragma pack(push, 4)
typedef union { double value; unsigned char bytes[8]; } ELFDoubleRepresentation;
#pragma pack(pop)
long double read_double(UInt8 *bytes, unsigned char flag)
{
    ELFDoubleRepresentation representation;

    if (flag != '\0') {
        representation.bytes[0] = bytes[0];
        representation.bytes[1] = bytes[1];
        representation.bytes[2] = bytes[2];
        representation.bytes[3] = bytes[3];
        representation.bytes[4] = bytes[4];
        representation.bytes[5] = bytes[5];
        representation.bytes[6] = bytes[6];
        representation.bytes[7] = bytes[7];
        CTool_EndianConvertMem(&bytes, 8);
    } else {
        CTool_EndianConvertMem(&bytes, 8);
        representation.bytes[0] = bytes[0];
        representation.bytes[1] = bytes[1];
        representation.bytes[2] = bytes[2];
        representation.bytes[3] = bytes[3];
        representation.bytes[4] = bytes[4];
        representation.bytes[5] = bytes[5];
        representation.bytes[6] = bytes[6];
        representation.bytes[7] = bytes[7];
    }
    return (long double)representation.value;
}

void swap_conversion_blocks(char *data, int remainingSize, int (*conversionMode)(const char *, int),
                            unsigned char readBeforeConversion)
{
    unsigned int blockSize;
    unsigned int offset;
    unsigned int *valueAddress;
    short *shortAddress;

    DAT_005805e0 = conversionMode;
    offset = 0;
    while (remainingSize != 0) {
        if (readBeforeConversion != '\0') {
            blockSize = ((ConversionBlockHeader *)(offset + data))->size;
            valueAddress = &((ConversionBlockHeader *)(offset + data))->size;
            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
        } else {
            valueAddress = &((ConversionBlockHeader *)(offset + data))->size;
            blockSize = CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
        }
        valueAddress = (unsigned int *)(offset + 4 + data);
        CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
        offset = offset + 8;
        remainingSize -= 8;
        /* GC 3 rejects malformed blocks before walking their ten-byte entries. */
        if (!blockSize || (blockSize - 8) % 10)
            return;
        do {
            if (readBeforeConversion != '\0') {
                valueAddress = &((ConversionBlockEntry *)(offset + data))->value;
                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
            } else {
                valueAddress = &((ConversionBlockEntry *)(offset + data))->value;
                CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
            }
            shortAddress = (short *)(offset + 4 + data);
            CTool_EndianConvertInPlaceWord16Ptr(shortAddress);
            valueAddress = (unsigned int *)(offset + 6 + data);
            CTool_EndianConvertInPlaceWord32Ptr(valueAddress);
            offset = offset + 10;
            remainingSize = remainingSize - 10;
        } while (offset < blockSize);
        data = data + offset;
        offset = 0;
    }
}

void ELF_Endian_ConvertThreeWords(unsigned int *words)
{
    words[0] = CTool_EndianConvertWord32(words[0]);
    words[1] = CTool_EndianConvertWord32(words[1]);
    words[2] = CTool_EndianConvertWord32(words[2]);
}

unsigned short ELF_Endian_ConvertSymbolRecord(void *data)
{
    unsigned short sectionIndex;
    struct ElfSymbolRecord *symbol;
    unsigned int name = CTool_EndianConvertWord32(((struct ElfSymbolRecord *)data)->name);

    symbol = data;
    symbol->name = name;
    symbol->value = CTool_EndianConvertWord32(symbol->value);
    symbol->size = CTool_EndianConvertWord32(symbol->size);
    sectionIndex = CTool_EndianConvertWord16(symbol->sectionIndex);
    symbol->sectionIndex = sectionIndex;
    return sectionIndex;
}

void ELF_Endian_SwapElf32Section(Elf32Section *values)
{
    values->name = CTool_EndianConvertWord32(values->name);
    values->type = CTool_EndianConvertWord32(values->type);
    values->flags = CTool_EndianConvertWord32(values->flags);
    values->address = CTool_EndianConvertWord32(values->address);
    values->file_offset = CTool_EndianConvertWord32(values->file_offset);
    values->size = CTool_EndianConvertWord32(values->size);
    values->link = CTool_EndianConvertWord32(values->link);
    values->info = CTool_EndianConvertWord32(values->info);
    values->alignment = CTool_EndianConvertWord32(values->alignment);
    values->entry_size = CTool_EndianConvertWord32(values->entry_size);
}

void ELF_Endian_SwapElf32Header(struct Elf32Header *header)
{
    header->type = CTool_EndianConvertWord16(header->type);
    header->machine = CTool_EndianConvertWord16(header->machine);
    header->version = CTool_EndianConvertWord32(header->version);
    header->entry = CTool_EndianConvertWord32(header->entry);
    header->program_header_offset = CTool_EndianConvertWord32(header->program_header_offset);
    header->section_header_offset = CTool_EndianConvertWord32(header->section_header_offset);
    header->flags = CTool_EndianConvertWord32(header->flags);
    header->header_size = CTool_EndianConvertWord16(header->header_size);
    header->program_header_size = CTool_EndianConvertWord16(header->program_header_size);
    header->program_header_count = CTool_EndianConvertWord16(header->program_header_count);
    header->section_header_size = CTool_EndianConvertWord16(header->section_header_size);
    header->section_header_count = CTool_EndianConvertWord16(header->section_header_count);
    header->section_name_index = CTool_EndianConvertWord16(header->section_name_index);
}
