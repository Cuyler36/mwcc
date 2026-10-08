/* Native GC3 assembler records are private while backend callers migrate. */
#include "compiler/common.h"
#include <stddef.h>
#pragma pack(push, 2)
typedef struct NativePCBlock NativePCBlock;
typedef struct NativePCInstruction NativePCInstruction;
typedef struct NativePCLabel NativePCLabel;
typedef struct NativePCObject {
    UInt8 kind, access, datatype, unknown03;
    UInt32 unknown04;
    void *nameSpace, *name, *type;
    UInt32 qualifiers;
    UInt16 storageClass, flags;
} NativePCObject;
struct NativePCLabel {
    NativePCLabel *next;
    NativePCBlock *block;
    SInt16 resolved;
    UInt16 number;
};
typedef struct NativePCOperand {
    UInt8 kind, arg;
    union {
        SInt32 immediate;
        struct { UInt16 flags; SInt16 reg; } reg;
        struct { SInt32 offset; NativePCObject *object; } mem;
        struct { NativePCLabel *label; } label;
        struct { SInt16 offset; NativePCLabel *labelA, *labelB; } labeldiff;
    } data;
    UInt8 unknown0c[2];
} NativePCOperand;
typedef struct NativePCSource { void *location; } NativePCSource;
struct NativePCInstruction {
    NativePCInstruction *next, *previous;
    NativePCBlock *block;
    unsigned long long flags;
    UInt8 unknown14[12];
    NativePCSource *source;
    UInt32 offset;
    SInt16 opcode, operandCount;
    NativePCOperand operands[1];
};
typedef struct NativePCEdge {
    struct NativePCEdge *nextHash, *nextSuccessor, *nextPredecessor;
    NativePCBlock *from, *to;
    SInt32 number;
    UInt16 hash, flags;
} NativePCEdge;
struct NativePCBlock {
    NativePCBlock *next, *previous;
    NativePCLabel *labels;
    NativePCEdge *predecessors, *successors;
    NativePCInstruction *first, *last;
    SInt32 number, offset, version;
    SInt16 instructionCount;
    UInt16 flags;
    UInt8 alignment, unknown2d;
};
typedef struct NativePCRelocation {
    SInt16 kind;
    NativePCObject *object;
    SInt32 addend;
} NativePCRelocation;
typedef struct NativePCDescriptor {
    const char *name, *format;
    UInt8 count, unknown09;
    unsigned long long flags;
    UInt32 encoding;
} NativePCDescriptor;
#pragma pack(pop)
typedef char NativePCOperandSize[sizeof(NativePCOperand) == 14 ? 1 : -1];
typedef char NativePCBlockSize[sizeof(NativePCBlock) == 46 ? 1 : -1];
typedef char NativePCInstructionOperands[offsetof(NativePCInstruction, operands) == 44 ? 1 : -1];
typedef char NativePCInstructionFlags[offsetof(NativePCInstruction, flags) == 12 ? 1 : -1];
typedef char NativePCRelocationSize[sizeof(NativePCRelocation) == 10 ? 1 : -1];
typedef char NativePCDescriptorSize[sizeof(NativePCDescriptor) == 22 ? 1 : -1];
extern NativePCBlock *pcbasicblocks;
extern NativePCDescriptor pcodeInfoDescriptors[];
extern void CError_Internal(const char *, int);
extern void PPCError_Error(int, ...);
extern int pccomputeoffsets(void);
extern NativePCInstruction *makepcode(SInt16, ...);
extern void appendpcode(NativePCBlock *, NativePCInstruction *);
extern void deletepcode(NativePCInstruction *);
extern int getbit(UInt32);
extern SInt32 fn_005873a0(NativePCObject *), fn_00587340(NativePCObject *), fn_005872d0(NativePCObject *);
extern SInt32 fn_005873d0(NativePCObject *, SInt32), fn_005873f0(NativePCObject *, SInt32);
extern UInt8 fn_005ccef0(NativePCObject *);
extern SInt32 fn_005cd070(NativePCObject *);

#define NATIVE_PREDICT_FALSE 0x200000000000000ULL
#define NATIVE_PREDICT_TRUE 0x400000000000000ULL

void invertybit(NativePCInstruction *instruction, SInt32 displacement)
{
    if (instruction->opcode == 2) {
        if (instruction->operands[0].data.immediate & 1) {
            if (displacement < 0) instruction->flags |= NATIVE_PREDICT_FALSE;
            else instruction->flags |= NATIVE_PREDICT_TRUE;
        }
    } else if ((instruction->opcode == 3 || instruction->opcode == 4) &&
               (instruction->operands[0].data.immediate & 1))
        instruction->flags |= NATIVE_PREDICT_TRUE;
    if (instruction->flags & NATIVE_PREDICT_TRUE)
        instruction->flags = (instruction->flags & ~NATIVE_PREDICT_TRUE) | NATIVE_PREDICT_FALSE;
    else if (instruction->flags & NATIVE_PREDICT_FALSE)
        instruction->flags = (instruction->flags & ~NATIVE_PREDICT_FALSE) | NATIVE_PREDICT_TRUE;
    else if (displacement < 0)
        instruction->flags = (instruction->flags & ~NATIVE_PREDICT_TRUE) | NATIVE_PREDICT_FALSE;
    else instruction->flags = (instruction->flags & ~NATIVE_PREDICT_FALSE) | NATIVE_PREDICT_TRUE;
}

SInt32 pcode_update_mem_labeldiff_imm(NativePCInstruction *instruction,
    NativePCOperand *operand, NativePCRelocation *relocation)
{
    NativePCObject *object;
    SInt32 value;
    if (operand->kind == 4) {
        object = operand->data.mem.object;
        value = operand->data.mem.offset;
        switch (object->datatype) {
            case 1:
                switch (operand->arg) {
                    case 1: value += fn_005873a0(object); break;
                    case 12: value = fn_005873d0(object, value); break;
                    case 13: value = fn_005873f0(object, value); break;
                    case 15: value += fn_00587340(object); break;
                    case 16: value += fn_005872d0(object); break;
                    default: CError_Internal("PCodeAssembly.c", 187); break;
                }
                break;
            case 0:
                if (instruction->flags & 6) {
                    if (operand->arg != 10 && !fn_005ccef0(object)) {
                        if (operand->arg == 14) {
                            value += fn_005cd070(object);
                            if (value != (SInt16)value) CError_Internal("PCodeAssembly.c", 219);
                        }
                        return value;
                    }
                    switch (operand->arg) {
                        case 2: case 3: case 6: case 10: break;
                        default: CError_Internal("PCodeAssembly.c", 212); break;
                    }
                }
                if (operand->arg == 14) {
                    value += fn_005cd070(object);
                    if (value != (SInt16)value) CError_Internal("PCodeAssembly.c", 229);
                    return value;
                }
                /* Native data operands otherwise use the relocation cases. */
            case 3: case 4:
                switch (operand->arg) {
                    case 2: relocation->kind = 3; break;
                    case 3: relocation->kind = 4; break;
                    case 6: relocation->kind = 5; break;
                    case 7: relocation->kind = 6; break;
                    case 8: relocation->kind = 7; break;
                    case 10: relocation->kind = 13; break;
                    case 11: relocation->kind = 14; break;
                    default: CError_Internal("PCodeAssembly.c", 279); break;
                }
                relocation->object = object;
                relocation->addend = value;
                value = 0;
                break;
            default: CError_Internal("PCodeAssembly.c", 321); break;
        }
    } else if (operand->kind == 7) {
        value = operand->data.labeldiff.labelA->block->offset -
                operand->data.labeldiff.labelB->block->offset + operand->data.labeldiff.offset;
        if (operand->arg == 1) value = -value;
        if (value > 32767 || value < -32768) PPCError_Error(10);
    } else if (operand->kind == 2) value = operand->data.immediate;
    else CError_Internal("PCodeAssembly.c", 350);
    return value;
}

void insertlongbranches(SInt32 maximum, SInt32 minimum)
{
    NativePCBlock *block;
    NativePCInstruction *instruction;
    NativePCLabel *target;
    SInt32 displacement;
    SInt16 opcode;
    pccomputeoffsets();
    for (block = pcbasicblocks; block; block = block->next) {
        if (!block->instructionCount) continue;
        instruction = block->last;
        if (!(instruction->flags & 1)) continue;
        opcode = instruction->opcode;
        switch (opcode) {
            case 5: case 8:
                if (instruction->operands[2].kind != 6) break;
                target = instruction->operands[2].data.label.label;
                displacement = target->block->offset - instruction->offset;
                if (displacement <= maximum && displacement >= minimum) break;
                instruction->opcode = opcode == 5 ? 8 : 5;
                block->last->operands[2].data.label.label = block->next->labels;
                invertybit(block->last, displacement);
                appendpcode(block, makepcode(0, target));
                break;
            case 2:
                if (instruction->operands[3].kind != 6) break;
                target = instruction->operands[3].data.label.label;
                displacement = target->block->offset - instruction->offset;
                invertybit(instruction, displacement);
                if (displacement <= maximum && displacement >= minimum) break;
                switch (block->last->operands[0].data.immediate & 0x1e) {
                    case 0: case 2: case 8: case 10:
                        block->last->operands[0].data.immediate ^= 11;
                        block->last->operands[3].data.label.label = block->next->labels;
                        break;
                    case 16: case 18:
                        block->last->operands[0].data.immediate ^= 3;
                        block->last->operands[3].data.label.label = block->next->labels;
                        break;
                    case 4: case 12:
                        block->last->operands[0].data.immediate ^= 9;
                        block->last->operands[3].data.label.label = block->next->labels;
                        break;
                    case 20: deletepcode(block->last); break;
                    default: CError_Internal("PCodeAssembly.c", 4089); break;
                }
                appendpcode(block, makepcode(0, target));
                break;
            case 11: case 14:
                if (instruction->operands[0].kind != 6) break;
                target = instruction->operands[0].data.label.label;
                displacement = target->block->offset - instruction->offset;
                if (displacement <= maximum && displacement >= minimum) break;
                switch (opcode) {
                    case 11: instruction->opcode = 14; break;
                    case 14: instruction->opcode = 11; break;
                    default: CError_Internal("PCodeAssembly.c", 4110); break;
                }
                block->last->operands[0].data.label.label = block->next->labels;
                invertybit(block->last, displacement);
                appendpcode(block, makepcode(0, target));
                break;
            case 12: case 13: case 15: case 16:
                if (instruction->operands[2].kind != 6) break;
                target = instruction->operands[2].data.label.label;
                displacement = target->block->offset - instruction->offset;
                if (displacement <= maximum && displacement >= minimum) break;
                switch (opcode) {
                    case 12: instruction->opcode = 16; break;
                    case 13: instruction->opcode = 15; break;
                    case 15: instruction->opcode = 13; break;
                    case 16: instruction->opcode = 12; break;
                    default: CError_Internal("PCodeAssembly.c", 4141); break;
                }
                block->last->operands[2].data.label.label = block->next->labels;
                invertybit(block->last, displacement);
                appendpcode(block, makepcode(0, target));
                break;
        }
    }
}

extern UInt32 fn_0070f056;
SInt32 insert_align_nops(void *unused, SInt32 size)
{
    NativePCBlock *block, *previous;
    NativePCInstruction *instruction;
    SInt32 alignment, padding, changed, mask;
    NativePCBlock *initial;
    for (initial = pcbasicblocks; initial; initial = initial->next) {
        if ((1 << initial->alignment) < 4) initial->alignment = getbit(4);
        if ((initial->flags & 0x600) == 0x400 && initial->instructionCount < 8 &&
            (1 << initial->alignment) < 8) initial->alignment = getbit(8);
    }
    do {
        changed = 0;
        for (block = pcbasicblocks; block; block = block->next) {
            previous = block->previous;
            if (!previous) continue;
            alignment = 1 << block->alignment;
            mask = ~(alignment - 1);
            padding = ((block->offset + alignment - 1) & mask) - block->offset;
            if (!padding) continue;
            while (previous->last && previous->last->opcode == 0x8c && !(previous->last->flags & 0x100)) {
                block->offset -= 4;
                deletepcode(previous->last);
                changed = 1;
            }
            padding = ((block->offset + alignment - 1) & mask) - block->offset;
            if (padding > 0) {
                changed = 1;
                while (padding > 0) {
                    instruction = makepcode(0x8c);
                    instruction->flags &= ~0x100ULL;
                    block->offset += 4;
                    padding -= 4;
                    appendpcode(previous, instruction);
                }
            }
            size = pccomputeoffsets();
        }
        if (changed && (UInt32)size >= (fn_0070f056 >> 1)) {
            insertlongbranches((fn_0070f056 >> 1) - 1, -(fn_0070f056 >> 1));
            size = pccomputeoffsets();
        }
    } while (changed);
    return size;
}

extern UInt8 fn_0070f04b;
extern void fn_0058b310(NativePCInstruction *, SInt16);
static inline NativePCInstruction *targetinstruction(NativePCLabel *label)
{
    NativePCBlock *block;
    for (block = label->block; block && block->instructionCount == 0; block = block->next) ;
    return block ? block->first : 0;
}
int optimizefinalbranches(int arg)
{
    long prev;
    int removed, changed;
    NativePCBlock *n;
    NativePCLabel *q, *qq;
    NativePCBlock *blk;
    int previousOffset;
    NativePCInstruction *fd;
    SInt16 k, op;
    unsigned long long flags;

    do {
        changed = removed = 0;
        for (blk = pcbasicblocks; blk; blk = blk->next) {
            NativePCInstruction *p;
            if (blk->instructionCount == 0)
                continue;
            flags = (p = blk->last)->flags;
            if ((flags & 1) == 0)
                continue;
            previousOffset = p->offset;
            if ((op = p->opcode) == 0 && p->operands[0].kind == 6) {
                fd = targetinstruction(q = p->operands[0].data.label.label);
                if (!fd || q->block->offset == previousOffset + 4 * 1) {
                    deletepcode(p);
                    changed = removed = 1;
                } else {
                    if (fd->opcode == 0) {
                        if (fd->operands[0].kind == 6 &&
                            fd->operands[0].data.label.label != p->operands[0].data.label.label) {
                            p->operands[0].data.label.label = fd->operands[0].data.label.label;
                            changed = 1;
                        }
                    } else if (fd->opcode == 17) {
                        p->opcode = 17;
                        changed = 1;
                    }
                }
            } else if ((op == 5 || op == 8) && p->operands[2].kind == 6) {
                NativePCBlock *n;
                NativePCLabel *q;
                NativePCBlock *ref = p->block;
                fd = targetinstruction(qq = q = p->operands[2].data.label.label);
                if (!fd || qq->block->offset == previousOffset + 4 * 1) {
                    deletepcode(p);
                    changed = removed = 1;
                } else {
                    if ((k = fd->opcode) == 0) {
                        if (fd->operands[0].kind == 6 &&
                            fd->operands[0].data.label.label != q) {
                            p->operands[2].data.label.label = fd->operands[0].data.label.label;
                            changed = 1;
                        }
                    } else if (!fn_0070f04b) {
                        ;
                    } else if (k == 0x11) {
                        if (op == 5)
                            p->opcode = 6;
                        else
                            p->opcode = 9;
                        p->operandCount = 2;
                        changed = 1;
                    } else if (k == 0x12) {
                        if (op == 5)
                            p->opcode = 7;
                        else
                            p->opcode = 10;
                        p->operandCount = 2;
                        changed = 1;
                    } else {
                        NativePCEdge *r;
                        NativePCBlock *b;
                        if ((b = ref->next) && (fd = b->first) != NULL && fd->opcode == 17 &&
                            qq->block->offset == previousOffset + 4 * 2) {
                            NativePCEdge *r;
                            r = b->predecessors;
                            if (r != NULL && r->from == ref && r->nextPredecessor == NULL) {
                                if (op == 5)
                                    p->opcode = 9;
                                else
                                    p->opcode = 6;
                                fn_0058b310(p, 2);
                                deletepcode(ref->next->first);
                                changed = removed = 1;
                            }
                        } else if (b && (fd = b->first) != NULL && fd->opcode == 18 &&
                                   qq->block->offset == previousOffset + 4 * 2) {
                            NativePCEdge *r;
                            r = b->predecessors;
                            if (r != NULL && r->from == ref && r->nextPredecessor == NULL) {
                                if (op == 5)
                                    p->opcode = 10;
                                else
                                    p->opcode = 7;
                                fn_0058b310(p, 2);
                                deletepcode(ref->next->first);
                                changed = removed = 1;
                            }
                        }
                    }
                }
            } else if (op == 2 && p->operands[3].kind == 6 &&
                       (flags & 0x80000000000100ULL) == 0) {
                NativePCBlock *n;
                NativePCLabel *q;
                NativePCBlock *ref = p->block;
                fd = targetinstruction(qq = q = p->operands[3].data.label.label);
                if (!fd || qq->block->offset == previousOffset + 4 * 1) {
                    deletepcode(p);
                    changed = removed = 1;
                } else {
                    if ((k = fd->opcode) == 0) {
                        if (fd->operands[0].kind == 6 &&
                            fd->operands[0].data.label.label != q) {
                            p->operands[3].data.label.label = fd->operands[0].data.label.label;
                            changed = 1;
                        }
                    } else if (!fn_0070f04b) {
                        ;
                    } else if (k == 0x11) {
                        p->opcode = 3;
                        p->operandCount = 3;
                        changed = 1;
                    } else if (k == 0x12) {
                        p->opcode = 4;
                        p->operandCount = 3;
                        changed = 1;
                    } else {
                        UInt32 x;
                        NativePCBlock *b;
                        NativePCEdge *r;
                        if ((b = ref->next) && (fd = b->first) != NULL && fd->opcode == 17 &&
                            qq->block->offset == previousOffset + 4 * 2) {
                            NativePCEdge *r;
                            x = p->operands[0].data.immediate & 0x1e;
                            r = b->predecessors;
                            if (r != NULL && r->from == ref && r->nextPredecessor == NULL) {
                                if ((x & 0x1e) == 4)
                                    p->operands[0].data.immediate = x | 0xc;
                                else if ((x & 0x1e) == 0xc)
                                    p->operands[0].data.immediate = x & 0x17;
                                p->opcode = 3;
                                p->operandCount = 3;
                                deletepcode(ref->next->first);
                                changed = removed = 1;
                            }
                        } else if (b && (fd = b->first) != NULL && fd->opcode == 18 &&
                                   qq->block->offset == previousOffset + 4 * 2) {
                            NativePCEdge *r;
                            x = p->operands[0].data.immediate & 0x1e;
                            r = b->predecessors;
                            if (r && r->from == ref && r->nextPredecessor == NULL) {
                                if ((x & 0x1e) == 4)
                                    p->operands[0].data.immediate = x | 0xc;
                                else if ((x & 0x1e) == 0xc)
                                    p->operands[0].data.immediate = x & 0x17;
                                p->opcode = 4;
                                p->operandCount = 3;
                                deletepcode(ref->next->first);
                                changed = removed = 1;
                            }
                        }
                    }
                }
            }
        }
        if (removed)
            arg = pccomputeoffsets();
        if (!changed)
            return arg;
    } while (1);
}

#pragma pack(push, 2)
typedef struct NativePCAssemblyEntry {
    struct NativePCAssemblyEntry *next;
    NativePCObject *object;
    NativePCBlock *block;
} NativePCAssemblyEntry;
typedef struct NativePCObjectList {
    struct NativePCObjectList *next;
    NativePCObject *object;
} NativePCObjectList;
typedef struct NativePCBuffer { UInt8 **data; SInt32 size; } NativePCBuffer;
#pragma pack(pop)
UInt32 codebase;
extern UInt8 fn_0070f222, fn_0070f00a, fn_0070f287, fn_0070efff;
extern UInt8 fn_0070f06e, fn_00725eda, fn_0070f00b;
extern SInt8 fn_0070f230;
extern UInt8 *fn_00710130;
extern NativePCObjectList *fn_007108b0;
extern void pcodestats_compute(void), ObjGen_BestSection(NativePCObject *), ObjGen_SymFunc(NativePCObject *);
extern UInt8 *CMangler_GetLinkName(NativePCObject *);
extern UInt8 *generate_traceback(int, const char *, int *, NativePCObject *);
extern void *ObjGen_DeclareCode(NativePCObject *, int);
extern NativePCBuffer *ObjGen_GetSectionGList(void *);
extern void AppendGListNoData(NativePCBuffer *, int);
extern void fn_004c3010(void), fn_004c4770(void), fn_004c1500(void);
extern void fn_004dcf40(NativePCObject *, int, UInt32, void *);
extern void fn_004c16c0(void *, int), fn_004c1ca0(NativePCObject *, int);
extern void fn_004c0990(void *, int);
extern void fn_004c0fc0(void *, int, NativePCObject *, UInt8, int);
extern UInt8 *Registers_GetVarInfo(NativePCObject *);
extern void fn_005d84f0(NativePCObject *), fn_004c07d0(NativePCObject *, int);
extern void *memcpy(void *, const void *, unsigned long);
UInt32 assemblepcode(NativePCInstruction *, UInt32, NativePCRelocation *);

int assemblefunction(NativePCObject *object, NativePCAssemblyEntry *symbolEntries)
{
    NativePCBlock *block;
    NativePCInstruction *instruction;
    NativePCBuffer *buffer;
    void *output;
    int size, extraDataSize, extraSize, offset;
    UInt8 *extraData;
    NativePCRelocation relocation;
    NativePCAssemblyEntry *entry;
    NativePCObjectList *variable;
    UInt32 limit;
    size = pccomputeoffsets();
    if (size <= 0) PPCError_Error(91, (UInt8 *)object->name + 10);
    if (fn_0070f222 || fn_0070f230 >= 3) size = optimizefinalbranches(size);
    limit = fn_0070f056 >> 1;
    if ((UInt32)size >= limit) {
        insertlongbranches(limit - 1, -limit);
        size = pccomputeoffsets();
    }
    if ((1 << fn_0070f00a) > 4) size = insert_align_nops(object, size);
    pcodestats_compute();
    ObjGen_BestSection(object);
    if (fn_0070f287) ObjGen_SymFunc(object);
    extraSize = 0;
    if (fn_0070efff)
        extraData = generate_traceback(size, (char *)CMangler_GetLinkName(object) + 10, &extraSize, object);
    if (!object->unknown04) object->unknown04 = 1;
    extraDataSize = extraSize;
    output = ObjGen_DeclareCode(object, size + extraSize);
    buffer = ObjGen_GetSectionGList(output);
    codebase = buffer->size;
    AppendGListNoData(buffer, size + extraDataSize);
    if (!fn_0070f06e) {
        if (!fn_00725eda) fn_004c3010();
        if (fn_0070f287) {
            fn_004dcf40(object, size + extraSize, codebase, output);
            fn_004c16c0(fn_00710130 + 18, 0);
        } else fn_004dcf40(object, size + extraSize, codebase, output);
    }
    fn_004c4770();
    if (symbolEntries) {
        entry = symbolEntries;
        while (entry) {
            fn_004c1ca0(entry->object, entry->block->offset);
            entry = entry->next;
        }
    }
    for (block = pcbasicblocks; block; block = block->next) {
        instruction = block->first;
        offset = block->offset;
        while (instruction) {
            UInt32 bits;
            if (fn_0070f287 && instruction->source && *(UInt32 *)instruction->source)
                fn_004c16c0(instruction->source, offset);
            bits = assemblepcode(instruction, offset, &relocation);
            *(UInt32 *)(*buffer->data + codebase + offset) = bits;
            if (instruction->flags & 0x80000) fn_004c0990(output, offset);
            if (relocation.kind != -1)
                fn_004c0fc0(output, offset, relocation.object, (UInt8)relocation.kind, relocation.addend);
            instruction = instruction->next;
            offset += 4;
        }
    }
    if (fn_007108b0) {
        for (variable = fn_007108b0; variable; variable = variable->next) {
            if (variable->object && variable->object->kind == 5 && Registers_GetVarInfo(variable->object)[9])
                fn_005d84f0(variable->object);
        }
    }
    if (fn_0070efff) memcpy(*buffer->data + codebase + size, extraData, extraDataSize);
    if (fn_0070f00b) fn_004c07d0(object, size);
    if (fn_0070f287) fn_004c1500();
    if (fn_0070efff) return size + extraSize;
    return size;
}

#define PC_B 0
#define PC_BL 1
#define PC_BC 2
#define PC_BCLR 3
#define PC_BCCTR 4
#define PC_BT 5
#define PC_BTLR 6
#define PC_BTCTR 7
#define PC_BF 8
#define PC_BFLR 9
#define PC_BFCTR 10
#define PC_BDNZ 11
#define PC_BDNZT 12
#define PC_BDNZF 13
#define PC_BDZ 14
#define PC_BDZT 15
#define PC_BDZF 16
#define PC_BLR 17
#define PC_BCTR 18
#define PC_BCTRL 19
#define PC_BLRL 20
#define PC_LBZ 21
#define PC_LBZU 22
#define PC_LBZX 23
#define PC_LBZUX 24
#define PC_LHZ 25
#define PC_LHZU 26
#define PC_LHZX 27
#define PC_LHZUX 28
#define PC_LHA 29
#define PC_LHAU 30
#define PC_LHAX 31
#define PC_LHAUX 32
#define PC_LHBRX 33
#define PC_LWZ 34
#define PC_LWZU 35
#define PC_LWZX 36
#define PC_LWZUX 37
#define PC_LWBRX 38
#define PC_LMW 39
#define PC_STB 40
#define PC_STBU 41
#define PC_STBX 42
#define PC_STBUX 43
#define PC_STH 44
#define PC_STHU 45
#define PC_STHX 46
#define PC_STHUX 47
#define PC_STHBRX 48
#define PC_STW 49
#define PC_STWU 50
#define PC_STWX 51
#define PC_STWUX 52
#define PC_STWBRX 53
#define PC_STMW 54
#define PC_DCBF 55
#define PC_DCBST 56
#define PC_DCBT 57
#define PC_DCBTST 58
#define PC_DCBZ 59
#define PC_ADD 60
#define PC_ADDC 61
#define PC_ADDE 62
#define PC_ADDI 63
#define PC_ADDIC 64
#define PC_ADDICR 65
#define PC_ADDIS 66
#define PC_ADDME 67
#define PC_ADDZE 68
#define PC_DIVW 69
#define PC_DIVWU 70
#define PC_MULHW 71
#define PC_MULHWU 72
#define PC_MULLI 73
#define PC_MULLW 74
#define PC_NEG 75
#define PC_SUBF 76
#define PC_SUBFC 77
#define PC_SUBFE 78
#define PC_SUBFIC 79
#define PC_SUBFME 80
#define PC_SUBFZE 81
#define PC_CMPI 82
#define PC_CMP 83
#define PC_CMPLI 84
#define PC_CMPL 85
#define PC_ANDI 86
#define PC_ANDIS 87
#define PC_ORI 88
#define PC_ORIS 89
#define PC_XORI 90
#define PC_XORIS 91
#define PC_AND 92
#define PC_OR 93
#define PC_XOR 94
#define PC_NAND 95
#define PC_NOR 96
#define PC_EQV 97
#define PC_ANDC 98
#define PC_ORC 99
#define PC_EXTSB 100
#define PC_EXTSH 101
#define PC_CNTLZW 102
#define PC_RLWINM 103
#define PC_RLWNM 104
#define PC_RLWIMI 105
#define PC_SLW 106
#define PC_SRW 107
#define PC_SRAWI 108
#define PC_SRAW 109
#define PC_CRAND 110
#define PC_CRANDC 111
#define PC_CREQV 112
#define PC_CRNAND 113
#define PC_CRNOR 114
#define PC_CROR 115
#define PC_CRORC 116
#define PC_CRXOR 117
#define PC_MCRF 118
#define PC_MTXER 119
#define PC_MTCTR 120
#define PC_MTLR 121
#define PC_MTCRF 122
#define PC_MTMSR 123
#define PC_MTSPR 124
#define PC_MFMSR 125
#define PC_MFSPR 126
#define PC_MFXER 127
#define PC_MFCTR 128
#define PC_MFLR 129
#define PC_MFCR 130
#define PC_MFFS 131
#define PC_MTFSF 132
#define PC_EIEIO 133
#define PC_ISYNC 134
#define PC_SYNC 135
#define PC_RFI 136
#define PC_LI 137
#define PC_LIS 138
#define PC_MR 139
#define PC_NOP 140
#define PC_NOT 141
#define PC_LFS 142
#define PC_LFSU 143
#define PC_LFSX 144
#define PC_LFSUX 145
#define PC_LFD 146
#define PC_LFDU 147
#define PC_LFDX 148
#define PC_LFDUX 149
#define PC_STFS 150
#define PC_STFSU 151
#define PC_STFSX 152
#define PC_STFSUX 153
#define PC_STFD 154
#define PC_STFDU 155
#define PC_STFDX 156
#define PC_STFDUX 157
#define PC_FMR 158
#define PC_FABS 159
#define PC_FNEG 160
#define PC_FNABS 161
#define PC_FADD 162
#define PC_FADDS 163
#define PC_FSUB 164
#define PC_FSUBS 165
#define PC_FMUL 166
#define PC_FMULS 167
#define PC_FDIV 168
#define PC_FDIVS 169
#define PC_FMADD 170
#define PC_FMADDS 171
#define PC_FMSUB 172
#define PC_FMSUBS 173
#define PC_FNMADD 174
#define PC_FNMADDS 175
#define PC_FNMSUB 176
#define PC_FNMSUBS 177
#define PC_FRES 178
#define PC_FRSQRTE 179
#define PC_FSEL 180
#define PC_FRSP 181
#define PC_FCTIW 182
#define PC_FCTIWZ 183
#define PC_FCMPU 184
#define PC_FCMPO 185
#define PC_LWARX 186
#define PC_LSWI 187
#define PC_LSWX 188
#define PC_STFIWX 189
#define PC_STSWI 190
#define PC_STSWX 191
#define PC_STWCX 192
#define PC_ECIWX 193
#define PC_ECOWX 194
#define PC_DCBI 195
#define PC_ICBI 196
#define PC_MCRFS 197
#define PC_MCRXR 198
#define PC_MFTB 199
#define PC_MFSR 200
#define PC_MTSR 201
#define PC_MFSRIN 202
#define PC_MTSRIN 203
#define PC_MTFSB0 204
#define PC_MTFSB1 205
#define PC_MTFSFI 206
#define PC_SC 207
#define PC_FSQRT 208
#define PC_FSQRTS 209
#define PC_TLBIA 210
#define PC_TLBIE 211
#define PC_TLBLD 212
#define PC_TLBLI 213
#define PC_TLBSYNC 214
#define PC_TW 215
#define PC_TRAP 216
#define PC_TWI 217
#define PC_OPWORD 218
#define PC_MFROM 219
#define PC_DSA 220
#define PC_ESA 221
#define PC_DCCCI 222
#define PC_DCREAD 223
#define PC_ICBT 224
#define PC_ICBT_E 225
#define PC_ICCCI 226
#define PC_ICREAD 227
#define PC_RFCI 228
#define PC_TLBRE 229
#define PC_TLBSX 230
#define PC_TLBWE 231
#define PC_WRTEE 232
#define PC_WRTEEI 233
#define PC_MFDCR 234
#define PC_MTDCR 235
#define PC_DCBA 236
#define PC_ISEL 237
#define PC_DSS 238
#define PC_DSSALL 239
#define PC_DST 240
#define PC_DSTT 241
#define PC_DSTST 242
#define PC_DSTSTT 243
#define PC_LVEBX 244
#define PC_LVEHX 245
#define PC_LVEWX 246
#define PC_LVSL 247
#define PC_LVSR 248
#define PC_LVX 249
#define PC_LVXL 250
#define PC_STVEBX 251
#define PC_STVEHX 252
#define PC_STVEWX 253
#define PC_STVX 254
#define PC_STVXL 255
#define PC_MFVSCR 256
#define PC_MTVSCR 257
#define PC_VADDCUW 258
#define PC_VADDFP 259
#define PC_VADDSBS 260
#define PC_VADDSHS 261
#define PC_VADDSWS 262
#define PC_VADDUBM 263
#define PC_VADDUBS 264
#define PC_VADDUHM 265
#define PC_VADDUHS 266
#define PC_VADDUWM 267
#define PC_VADDUWS 268
#define PC_VAND 269
#define PC_VANDC 270
#define PC_VAVGSB 271
#define PC_VAVGSH 272
#define PC_VAVGSW 273
#define PC_VAVGUB 274
#define PC_VAVGUH 275
#define PC_VAVGUW 276
#define PC_VCFSX 277
#define PC_VCFUX 278
#define PC_VCMPBFP 279
#define PC_VCMPEQFP 280
#define PC_VCMPEQUB 281
#define PC_VCMPEQUH 282
#define PC_VCMPEQUW 283
#define PC_VCMPGEFP 284
#define PC_VCMPGTFP 285
#define PC_VCMPGTSB 286
#define PC_VCMPGTSH 287
#define PC_VCMPGTSW 288
#define PC_VCMPGTUB 289
#define PC_VCMPGTUH 290
#define PC_VCMPGTUW 291
#define PC_VCTSXS 292
#define PC_VCTUXS 293
#define PC_VEXPTEFP 294
#define PC_VLOGEFP 295
#define PC_VMAXFP 296
#define PC_VMAXSB 297
#define PC_VMAXSH 298
#define PC_VMAXSW 299
#define PC_VMAXUB 300
#define PC_VMAXUH 301
#define PC_VMAXUW 302
#define PC_VMINFP 303
#define PC_VMINSB 304
#define PC_VMINSH 305
#define PC_VMINSW 306
#define PC_VMINUB 307
#define PC_VMINUH 308
#define PC_VMINUW 309
#define PC_VMRGHB 310
#define PC_VMRGHH 311
#define PC_VMRGHW 312
#define PC_VMRGLB 313
#define PC_VMRGLH 314
#define PC_VMRGLW 315
#define PC_VMULESB 316
#define PC_VMULESH 317
#define PC_VMULEUB 318
#define PC_VMULEUH 319
#define PC_VMULOSB 320
#define PC_VMULOSH 321
#define PC_VMULOUB 322
#define PC_VMULOUH 323
#define PC_VNOR 324
#define PC_VOR 325
#define PC_VPKPX 326
#define PC_VPKSHSS 327
#define PC_VPKSHUS 328
#define PC_VPKSWSS 329
#define PC_VPKSWUS 330
#define PC_VPKUHUM 331
#define PC_VPKUHUS 332
#define PC_VPKUWUM 333
#define PC_VPKUWUS 334
#define PC_VREFP 335
#define PC_VRFIM 336
#define PC_VRFIN 337
#define PC_VRFIP 338
#define PC_VRFIZ 339
#define PC_VRLB 340
#define PC_VRLH 341
#define PC_VRLW 342
#define PC_VRSQRTEFP 343
#define PC_VSL 344
#define PC_VSLB 345
#define PC_VSLH 346
#define PC_VSLO 347
#define PC_VSLW 348
#define PC_VSPLTB 349
#define PC_VSPLTH 350
#define PC_VSPLTW 351
#define PC_VSPLTISB 352
#define PC_VSPLTISH 353
#define PC_VSPLTISW 354
#define PC_VSR 355
#define PC_VSRAB 356
#define PC_VSRAH 357
#define PC_VSRAW 358
#define PC_VSRB 359
#define PC_VSRH 360
#define PC_VSRO 361
#define PC_VSRW 362
#define PC_VSUBCUW 363
#define PC_VSUBFP 364
#define PC_VSUBSBS 365
#define PC_VSUBSHS 366
#define PC_VSUBSWS 367
#define PC_VSUBUBM 368
#define PC_VSUBUBS 369
#define PC_VSUBUHM 370
#define PC_VSUBUHS 371
#define PC_VSUBUWM 372
#define PC_VSUBUWS 373
#define PC_VSUMSWS 374
#define PC_VSUM2SWS 375
#define PC_VSUM4SBS 376
#define PC_VSUM4SHS 377
#define PC_VSUM4UBS 378
#define PC_VUPKHPX 379
#define PC_VUPKHSB 380
#define PC_VUPKHSH 381
#define PC_VUPKLPX 382
#define PC_VUPKLSB 383
#define PC_VUPKLSH 384
#define PC_VXOR 385
#define PC_VMADDFP 386
#define PC_VMHADDSHS 387
#define PC_VMHRADDSHS 388
#define PC_VMLADDUHM 389
#define PC_VMSUMMBM 390
#define PC_VMSUMSHM 391
#define PC_VMSUMSHS 392
#define PC_VMSUMUBM 393
#define PC_VMSUMUHM 394
#define PC_VMSUMUHS 395
#define PC_VNMSUBFP 396
#define PC_VPERM 397
#define PC_VSEL 398
#define PC_VSLDOI 399
#define PC_VMR 400
#define PC_VMRP 401
#define PC_PSQ_L 402
#define PC_PSQ_LU 403
#define PC_PSQ_LX 404
#define PC_PSQ_LUX 405
#define PC_PSQ_ST 406
#define PC_PSQ_STU 407
#define PC_PSQ_STX 408
#define PC_PSQ_STUX 409
#define PC_DCBZ_L 410
#define PC_PS_ADD 411
#define PC_PS_SUB 412
#define PC_PS_MUL 413
#define PC_PS_DIV 414
#define PC_PS_MADD 415
#define PC_PS_MSUB 416
#define PC_PS_NMADD 417
#define PC_PS_NMSUB 418
#define PC_PS_RES 419
#define PC_PS_SEL 420
#define PC_PS_ABS 421
#define PC_PS_NABS 422
#define PC_PS_NEG 423
#define PC_PS_MR 424
#define PC_PS_RSQRTE 425
#define PC_PS_CMPU0 426
#define PC_PS_CMPO0 427
#define PC_PS_CMPU1 428
#define PC_PS_CMPO1 429
#define PC_PS_MERGE00 430
#define PC_PS_MERGE01 431
#define PC_PS_MERGE10 432
#define PC_PS_MERGE11 433
#define PC_PS_SUM0 434
#define PC_PS_SUM1 435
#define PC_PS_MULS0 436
#define PC_PS_MULS1 437
#define PC_PS_MADDS0 438
#define PC_PS_MADDS1 439
#define PC_MFAPIDI 440
#define PC_MACCHW 441
#define PC_MACCHWS 442
#define PC_MACCHWSU 443
#define PC_MACCHWU 444
#define PC_MACHHW 445
#define PC_MACHHWS 446
#define PC_MACHHWSU 447
#define PC_MACHHWU 448
#define PC_MACLHW 449
#define PC_MACLHWS 450
#define PC_MACLHWSU 451
#define PC_MACLHWU 452
#define PC_NMACCHW 453
#define PC_NMACCHWS 454
#define PC_NMACHHW 455
#define PC_NMACHHWS 456
#define PC_NMACLHW 457
#define PC_NMACLHWS 458
#define PC_MULCHW 459
#define PC_MULCHWU 460
#define PC_MULHHW 461
#define PC_MULHHWU 462
#define PC_MULLHW 463
#define PC_MULLHWU 464
#define PC_SLE 465
#define PC_SLEQ 466
#define PC_SLIQ 467
#define PC_SLLIQ 468
#define PC_SLLQ 469
#define PC_SLQ 470
#define PC_SRAIQ 471
#define PC_SRAQ 472
#define PC_SRE 473
#define PC_SREA 474
#define PC_SREQ 475
#define PC_SRIQ 476
#define PC_SRLIQ 477
#define PC_SRLQ 478
#define PC_SRQ 479
#define PC_MASKG 480
#define PC_MASKIR 481
#define PC_LSCBX 482
#define PC_DIV 483
#define PC_DIVS 484
#define PC_DOZ 485
#define PC_MUL 486
#define PC_NABS 487
#define PC_ABS 488
#define PC_CLCS 489
#define PC_DOZI 490
#define PC_RLMI 491
#define PC_RRIB 492
#define PC_GETCRBIT 493
#define PC_GETCRFIELD 494
#define PC_PUTCRFIELD 495

#define R(n) ((SInt32)instr->operands[n].data.reg.reg)
#define I(n) (instr->operands[n].data.immediate)
#define O(n) (instr->operands[n])
extern UInt32 CTool_EndianConvertWord32(UInt32);
extern UInt32 fn_0070f05a;
extern UInt8 fn_0070f063;
extern SInt16 pcodeSpecialRegisters[];
UInt32 assemblepcode(NativePCInstruction *instr, UInt32 offset, NativePCRelocation *relocation)
{
    UInt32 bits;
    SInt32 value;
    bits = pcodeInfoDescriptors[instr->opcode].encoding;
    relocation->kind = -1;
    relocation->addend = 0;
    switch (instr->opcode) {
        case PC_BL: {
            int absoluteBranch = instr->flags & 0x100000000000000ULL;
            if (O(0).kind == 4) {
                bits |= O(0).data.mem.offset & 0x3fffffc;
                relocation->kind = 2;
                relocation->object = O(0).data.mem.object;
                if (!absoluteBranch) relocation->kind = 2;
                else { relocation->kind = 9; bits |= 2; }
            } else if (O(0).kind == 2) {
                bits |= I(0) & 0x3fffffc;
                if (absoluteBranch) bits |= 2;
            } else {
                if (O(0).data.label.label->block->flags & 0x20) CError_Internal("PCodeAssembly.c", 533);
                bits |= (O(0).data.label.label->block->offset - offset) & 0x3fffffc;
                if (absoluteBranch) CError_Internal("PCodeAssembly.c", 537);
            }
            break;
        }
        case PC_B: {
            int absoluteBranch = instr->flags & 0x100000000000000ULL;
            if (O(0).kind == 4) {
                bits |= O(0).data.mem.offset & 0x3fffffc;
                relocation->object = O(0).data.mem.object;
                if (!absoluteBranch) relocation->kind = 2;
                else { relocation->kind = 9; bits |= 2; }
            } else if (O(0).kind == 2) {
                bits |= I(0) & 0x3fffffc;
                if (absoluteBranch) bits |= 2;
            } else {
                SInt32 limit;
                if (O(0).data.label.label->block->flags & 0x20) CError_Internal("PCodeAssembly.c", 578);
                value = O(0).data.label.label->block->offset - offset;
                bits |= value & 0x3fffffc;
                limit = fn_0070f05a >> 1;
                if (value > limit - 1 || value < -limit) PPCError_Error(122, value, limit - 1, -limit);
                if (absoluteBranch) CError_Internal("PCodeAssembly.c", 586);
            }
            if (instr->flags & 0x80000000000000ULL) bits |= 1;
            break;
        }
        case PC_BDNZ:
        case PC_BDZ: {
            int absoluteBranch = instr->flags & 0x100000000000000ULL;
            if (O(0).kind == 4) {
                bits |= O(0).data.mem.offset & 0xfffc;
                relocation->object = O(0).data.mem.object;
                if (!absoluteBranch) relocation->kind = 8;
                else { relocation->kind = 9; bits |= 2; }
            } else {
                if (O(0).kind == 2) value = I(0);
                else {
                    if (O(0).data.label.label->block->flags & 0x20) CError_Internal("PCodeAssembly.c", 624);
                    value = O(0).data.label.label->block->offset - offset;
                }
                bits |= (UInt16)value;
                if (value < 0) { if (instr->flags & NATIVE_PREDICT_FALSE) bits |= 0x200000; }
                else { if (instr->flags & NATIVE_PREDICT_TRUE) bits |= 0x200000; }
            }
            if (instr->flags & 0x80000000000000ULL) bits |= 1;
            break;
        }
        case PC_BC: {
            int absoluteBranch = instr->flags & 0x100000000000000ULL;
            bits |= (I(0) & 31) << 21;
            bits |= ((R(1) * 4 + I(2)) & 31) << 16;
            if (O(3).kind == 4) {
                bits |= O(3).data.mem.offset & 0xfffc;
                relocation->object = O(3).data.mem.object;
                if (!absoluteBranch) relocation->kind = 8;
                else { relocation->kind = 9; bits |= 2; }
            } else {
                if (O(3).kind == 2) value = I(3);
                else {
                    if (O(3).data.label.label->block->flags & 0x20) CError_Internal("PCodeAssembly.c", 683);
                    value = O(3).data.label.label->block->offset - offset;
                }
                bits |= (UInt16)value;
                if (value < 0) { if (instr->flags & NATIVE_PREDICT_FALSE) bits |= 0x200000; }
                else { if (instr->flags & NATIVE_PREDICT_TRUE) bits |= 0x200000; }
            }
            if (instr->flags & 0x80000000000000ULL) bits |= 1;
            break;
        }
        case PC_BT: case PC_BF: case PC_BDNZT: case PC_BDNZF: case PC_BDZT: case PC_BDZF: {
            int absoluteBranch = instr->flags & 0x100000000000000ULL;
            bits |= ((R(0) * 4 + I(1)) & 31) << 16;
            if (O(2).kind == 4) {
                bits |= O(2).data.mem.offset & 0xfffc;
                relocation->object = O(2).data.mem.object;
                if (!absoluteBranch) relocation->kind = 8;
                else { relocation->kind = 9; bits |= 2; }
            } else {
                if (O(2).kind == 2) {
                    value = I(2);
                    if (absoluteBranch) bits |= 2;
                } else {
                    if (O(2).data.label.label->block->flags & 0x20) CError_Internal("PCodeAssembly.c", 747);
                    value = O(2).data.label.label->block->offset - offset;
                    if (absoluteBranch) CError_Internal("PCodeAssembly.c", 750);
                }
                bits |= (UInt16)value;
                if (value < 0) { if (instr->flags & NATIVE_PREDICT_FALSE) bits |= 0x200000; }
                else { if (instr->flags & NATIVE_PREDICT_TRUE) bits |= 0x200000; }
            }
            if (instr->flags & 0x80000000000000ULL) bits |= 1;
            break;
        }
        case PC_LBZ: case PC_LBZU: case PC_LHZ: case PC_LHZU: case PC_LHA: case PC_LHAU:
        case PC_LWZ: case PC_LWZU: case PC_LMW: case PC_STB: case PC_STBU: case PC_STH:
        case PC_STHU: case PC_STW: case PC_STWU: case PC_STMW: case PC_LFS: case PC_LFSU:
        case PC_LFD: case PC_LFDU: case PC_STFS: case PC_STFSU: case PC_STFD: case PC_STFDU:
            bits |= R(0) << 21;
            bits |= R(1) << 16;
            bits |= (UInt16)pcode_update_mem_labeldiff_imm(instr, &O(2), relocation);
            break;
        case PC_ADDI: case PC_ADDIC: case PC_ADDICR:
        case PC_ADDIS:
            bits |= R(0) << 21;
            bits |= R(1) << 16;
            bits |= (UInt16)pcode_update_mem_labeldiff_imm(instr, &O(2), relocation);
            break;
        case PC_LI: case PC_LIS:
            bits |= R(0) << 21;
            bits |= (UInt16)pcode_update_mem_labeldiff_imm(instr, &O(1), relocation);
            break;
        case PC_ANDI: case PC_ANDIS: case PC_ORI: case PC_ORIS: case PC_XORI: case PC_XORIS:
            bits |= R(0) << 16;
            bits |= R(1) << 21;
            bits |= (UInt16)pcode_update_mem_labeldiff_imm(instr, &O(2), relocation);
            break;
        case PC_MTSPR:
            if (O(0).kind == 0) {
                if (O(0).arg != 0) CError_Internal("PCodeAssembly.c", 1369);
                if ((SInt16)R(0) >= 4) CError_Internal("PCodeAssembly.c", 1370);
                value = pcodeSpecialRegisters[R(0)];
                bits |= ((value & 0x3e0) << 6) + ((value & 31) << 16);
            } else if (O(0).kind == 1 && O(0).arg == 0) {
                value = R(0);
                bits |= ((value & 0x3e0) << 6) + ((value & 31) << 16);
            } else CError_Internal("PCodeAssembly.c", 1375);
            bits |= R(1) << 21;
            break;
        case PC_MTDCR:
            if (O(0).kind != 2) CError_Internal("PCodeAssembly.c", 1384);
            value = I(0);
            bits |= ((value & 0x3e0) << 6) + ((value & 31) << 16);
            bits |= R(1) << 21;
            break;
        case PC_MFSPR:
            bits |= R(0) << 21;
            if (O(1).kind == 0 && O(1).arg == 0) {
                if ((SInt16)R(1) >= 4) CError_Internal("PCodeAssembly.c", 1397);
                value = pcodeSpecialRegisters[R(1)];
                bits |= ((value & 0x3e0) << 6) + ((value & 31) << 16);
            } else if (O(1).kind == 1 && O(1).arg == 0) {
                value = R(1);
                bits |= ((value & 0x3e0) << 6) + ((value & 31) << 16);
            } else CError_Internal("PCodeAssembly.c", 1402);
            break;
        case PC_MFDCR:
            bits |= R(0) << 21;
            if (O(1).kind != 2) CError_Internal("PCodeAssembly.c", 1411);
            else {
                value = I(1);
                bits |= ((value & 0x3e0) << 6) + ((value & 31) << 16);
            }
            break;
        case PC_MFTB:
            bits |= R(0) << 21;
            if (O(1).kind == 1 && O(1).arg == 0) {
                if (R(1) == 284) bits |= 0xc4000;
                else if (R(1) == 285) bits |= 0xd4000;
                else CError_Internal("PCodeAssembly.c", 1442);
            } else CError_Internal("PCodeAssembly.c", 1445);
            break;
        case PC_OPWORD:
            if (O(0).kind == 4) CError_Internal("PCodeAssembly.c", 1518);
            bits = pcode_update_mem_labeldiff_imm(instr, &O(0), relocation);
            break;
        case PC_PSQ_L: case PC_PSQ_LU: case PC_PSQ_ST: case PC_PSQ_STU:
            bits |= R(0) << 21;
            bits |= R(1) << 16;
            bits |= I(3) << 15;
            bits |= (R(4) - 912) << 12;
            bits |= pcode_update_mem_labeldiff_imm(instr, &O(2), relocation) & 0xfff;
            break;
        case PC_LVXL: case PC_STVXL:
            bits |= R(0) << 21;
            bits |= R(1) << 16;
            bits |= R(2) << 11;
            if (fn_0070f063) bits |= 1;
            break;
        case PC_DCBT: case PC_DCBTST: case PC_DCBZ: case PC_ICBT: case PC_ICBT_E:
            bits |= I(0) << 21;
            bits |= R(1) << 16;
            bits |= R(2) << 11;
            if (instr->operandCount > 3 && O(3).kind == 2) bits |= I(3) << 21;
            break;
        case PC_MFAPIDI:
        default: CError_Internal("PCodeAssembly.c", 3873); break;
        case PC_EIEIO: case PC_ISYNC: case PC_SYNC: case PC_RFI: case PC_NOP: case PC_SC:
        case PC_TLBIA: case PC_TLBSYNC: case PC_TRAP: case PC_DSA: case PC_ESA: case PC_RFCI:
        case PC_GETCRBIT: case PC_GETCRFIELD: case PC_PUTCRFIELD:
            break;
        case PC_BTLR:
        case PC_BTCTR:
        case PC_BFLR:
        case PC_BFCTR:
            bits |= ((((R(0) * 4) + I(1)) & 0x1fUL) << 0x10UL);
            if (((UInt32)(instr->flags >> 32) & 0x800000UL)) bits |= 1;
            if (((UInt32)(instr->flags >> 32) & 0x4000000UL)) bits |= 0x200000UL;
            break;

        case PC_BCLR:
        case PC_BCCTR:
            bits |= (I(0) << 0x15UL);
            bits |= ((((R(1) * 4) + I(2)) & 0x1fUL) << 0x10UL);
            if (((UInt32)(instr->flags >> 32) & 0x800000UL)) bits |= 1;
            if (((UInt32)(instr->flags >> 32) & 0x4000000UL)) bits |= 0x200000UL;
            break;

        case PC_BLR:
        case PC_BCTR:
        case PC_BCTRL:
        case PC_BLRL:
            if (((UInt32)(instr->flags >> 32) & 0x800000UL)) bits |= 1;
            if (((UInt32)(instr->flags >> 32) & 0x4000000UL)) bits |= 0x200000UL;
            break;

        case PC_CRAND:
        case PC_CRANDC:
        case PC_CREQV:
        case PC_CRNAND:
        case PC_CRNOR:
        case PC_CROR:
        case PC_CRORC:
        case PC_CRXOR:
            bits |= ((((R(0) * 4) + I(1)) & 0x1fUL) << 0x15UL);
            bits |= ((((R(2) * 4) + I(3)) & 0x1fUL) << 0x10UL);
            bits |= ((((R(4) * 4) + I(5)) & 0x1fUL) << 0xbUL);
            break;

        case PC_MCRF:
            bits |= (R(0) << 0x17UL);
            bits |= (R(1) << 0x12UL);
            break;

        case PC_LBZX:
        case PC_LBZUX:
        case PC_LHZX:
        case PC_LHZUX:
        case PC_LHAX:
        case PC_LHAUX:
        case PC_LHBRX:
        case PC_LWZX:
        case PC_LWZUX:
        case PC_LWBRX:
        case PC_STBX:
        case PC_STBUX:
        case PC_STHX:
        case PC_STHUX:
        case PC_STHBRX:
        case PC_STWX:
        case PC_STWUX:
        case PC_STWBRX:
        case PC_LFSX:
        case PC_LFSUX:
        case PC_LFDX:
        case PC_LFDUX:
        case PC_STFSX:
        case PC_STFSUX:
        case PC_STFDX:
        case PC_STFDUX:
        case PC_LWARX:
        case PC_LSWX:
        case PC_STFIWX:
        case PC_STSWX:
        case PC_STWCX:
        case PC_ECIWX:
        case PC_ECOWX:
        case PC_DCREAD:
        case PC_TLBSX:
        case PC_MULCHW:
        case PC_MULCHWU:
        case PC_MULHHW:
        case PC_MULHHWU:
        case PC_MULLHW:
        case PC_MULLHWU:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_DCBF:
        case PC_DCBST:
        case PC_DCBI:
        case PC_ICBI:
        case PC_DCCCI:
        case PC_ICCCI:
        case PC_ICREAD:
        case PC_DCBA:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0xbUL);
            break;

        case PC_ADD:
        case PC_ADDC:
        case PC_ADDE:
        case PC_DIVW:
        case PC_DIVWU:
        case PC_MULHW:
        case PC_MULHWU:
        case PC_MULLW:
        case PC_SUBF:
        case PC_SUBFC:
        case PC_SUBFE:
        case PC_MACCHW:
        case PC_MACCHWS:
        case PC_MACCHWSU:
        case PC_MACCHWU:
        case PC_MACHHW:
        case PC_MACHHWS:
        case PC_MACHHWSU:
        case PC_MACHHWU:
        case PC_MACLHW:
        case PC_MACLHWS:
        case PC_MACLHWSU:
        case PC_MACLHWU:
        case PC_NMACCHW:
        case PC_NMACCHWS:
        case PC_NMACHHW:
        case PC_NMACHHWS:
        case PC_NMACLHW:
        case PC_NMACLHWS:
            bits |= (R(2) << 0xbUL);
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            if (((UInt32)(instr->flags >> 32) & 0x2000UL)) bits |= 0x400UL;
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_ADDME:
        case PC_ADDZE:
        case PC_NEG:
        case PC_SUBFME:
        case PC_SUBFZE:
        case PC_MFROM:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            if (((UInt32)(instr->flags >> 32) & 0x2000UL)) bits |= 0x400UL;
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_MULLI:
        case PC_SUBFIC:
            bits |= (R(1) << 0x10UL);
            bits |= (R(0) << 0x15UL);
            bits |= (UInt16)I(2);
            break;

        case PC_AND:
        case PC_OR:
        case PC_XOR:
        case PC_NAND:
        case PC_NOR:
        case PC_EQV:
        case PC_ANDC:
        case PC_ORC:
        case PC_SLW:
        case PC_SRW:
        case PC_SRAW:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0x15UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_ISEL:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            bits |= ((((R(3) * 4) + I(4)) & 0x1fUL) << 6);
            break;

        case PC_EXTSB:
        case PC_EXTSH:
        case PC_CNTLZW:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0x15UL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_MR:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0x15UL);
            bits |= (R(1) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_NOT:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0x15UL);
            bits |= (R(1) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_SRAWI:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0x15UL);
            bits |= ((I(2) & 0x1fUL) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_RLWINM:
        case PC_RLWIMI:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0x15UL);
            bits |= ((I(2) & 0x1fUL) << 0xbUL);
            bits |= ((I(3) & 0x1fUL) << 6);
            bits |= ((I(4) & 0x1fUL) + (I(4) & 0x1fUL));
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_RLWNM:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0x15UL);
            bits |= (R(2) << 0xbUL);
            bits |= ((I(3) & 0x1fUL) << 6);
            bits |= ((I(4) & 0x1fUL) + (I(4) & 0x1fUL));
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_CMP:
        case PC_CMPL:
            bits |= (R(0) << 0x17UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            break;

        case PC_CMPI:
        case PC_CMPLI:
            bits |= (R(0) << 0x17UL);
            bits |= (R(1) << 0x10UL);
            bits |= (UInt16)I(2);
            break;

        case PC_MTXER:
        case PC_MTCTR:
        case PC_MTLR:
        case PC_MTMSR:
        case PC_MFMSR:
        case PC_MFXER:
        case PC_MFCTR:
        case PC_MFLR:
        case PC_MFCR:
            bits |= (R(0) << 0x15UL);
            break;

        case PC_MFFS:
            bits |= (R(0) << 0x15UL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_MTCRF:
            bits |= (I(0) << 0xcUL);
            bits |= (R(1) << 0x15UL);
            break;

        case PC_MTFSF:
            bits |= ((UInt8)I(0) << 0x11UL);
            bits |= (R(1) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_FMR:
        case PC_FABS:
        case PC_FNEG:
        case PC_FNABS:
        case PC_FRES:
        case PC_FRSQRTE:
        case PC_FRSP:
        case PC_FCTIW:
        case PC_FCTIWZ:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_FADD:
        case PC_FADDS:
        case PC_FSUB:
        case PC_FSUBS:
        case PC_FDIV:
        case PC_FDIVS:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_FMADD:
        case PC_FMADDS:
        case PC_FMSUB:
        case PC_FMSUBS:
        case PC_FNMADD:
        case PC_FNMADDS:
        case PC_FNMSUB:
        case PC_FNMSUBS:
        case PC_FSEL:
            bits |= (R(3) << 0xbUL);
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 6);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_FMUL:
        case PC_FMULS:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 6);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_FCMPU:
        case PC_FCMPO:
            bits |= (R(0) << 0x17UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            break;

        case PC_LSWI:
        case PC_STSWI:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= ((I(2) & 0x1fUL) << 0xbUL);
            break;

        case PC_MCRFS:
            bits |= ((I(1) & 7) << 0x12UL);
            bits |= (R(0) << 0x17UL);
            break;

        case PC_MCRXR:
            bits |= (R(0) << 0x17UL);
            break;

        case PC_MTSR:
            bits |= (R(1) << 0x15UL);
            bits |= ((I(0) & 0xfUL) << 0x10UL);
            break;

        case PC_MFSR:
            bits |= (R(0) << 0x15UL);
            bits |= ((I(1) & 0xfUL) << 0x10UL);
            break;

        case PC_MFSRIN:
        case PC_MTSRIN:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0xbUL);
            break;

        case PC_MTFSB0:
        case PC_MTFSB1:
            bits |= ((I(0) & 0x1fUL) << 0x15UL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_MTFSFI:
            bits |= (R(0) << 0x17UL);
            bits |= ((I(1) & 0xfUL) << 0xcUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_FSQRT:
        case PC_FSQRTS:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_TLBIE:
        case PC_TLBLD:
        case PC_TLBLI:
            bits |= (R(0) << 0xbUL);
            break;

        case PC_TW:
            bits |= ((I(0) & 0x1fUL) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            break;

        case PC_TWI:
            bits |= ((I(0) & 0x1fUL) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (UInt16)I(2);
            break;

        case PC_MASKG:
        case PC_MASKIR:
            bits |= (R(1) << 0x15UL);
            bits |= (R(0) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_LSCBX:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_DIV:
        case PC_DIVS:
        case PC_DOZ:
        case PC_MUL:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x2000UL)) bits |= 0x400UL;
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_NABS:
        case PC_ABS:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            if (((UInt32)(instr->flags >> 32) & 0x2000UL)) bits |= 0x400UL;
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_CLCS:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_DOZI:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (UInt16)I(2);
            break;

        case PC_RLMI:
            bits |= (R(1) << 0x15UL);
            bits |= (R(0) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            bits |= ((I(3) & 0x1fUL) << 6);
            bits |= ((I(4) & 0x1fUL) + (I(4) & 0x1fUL));
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_SLE:
        case PC_SLEQ:
        case PC_SLLQ:
        case PC_SLQ:
        case PC_SRAQ:
        case PC_SRE:
        case PC_SREA:
        case PC_SREQ:
        case PC_SRLQ:
        case PC_SRQ:
        case PC_RRIB:
            bits |= (R(1) << 0x15UL);
            bits |= (R(0) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_SLIQ:
        case PC_SLLIQ:
        case PC_SRAIQ:
        case PC_SRIQ:
        case PC_SRLIQ:
            bits |= (R(1) << 0x15UL);
            bits |= (R(0) << 0x10UL);
            bits |= ((I(2) & 0x1fUL) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_TLBRE:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= ((I(2) & 1) << 0xbUL);
            break;

        case PC_TLBWE:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= ((I(2) & 1) << 0xbUL);
            break;

        case PC_WRTEE:
            bits |= (R(0) << 0x15UL);
            break;

        case PC_WRTEEI:
            bits |= (I(0) << 0xfUL);
            break;

        case PC_DSTT:
        case PC_DSTSTT:
            bits |= 0x2000000UL;
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0xbUL);
            bits |= ((I(2) & 3) << 0x15UL);
            break;

        case PC_DST:
        case PC_DSTST:
            bits |= ((I(3) & 1) << 0x19UL);
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0xbUL);
            bits |= ((I(2) & 3) << 0x15UL);
            break;

        case PC_DSSALL:
            bits |= 0x2000000UL;
            break;

        case PC_DSS:
            bits |= ((I(1) & 1) << 0x19UL);
            bits |= ((I(0) & 3) << 0x15UL);
            break;

        case PC_LVEBX:
        case PC_LVEHX:
        case PC_LVEWX:
        case PC_LVSL:
        case PC_LVSR:
        case PC_LVX:
        case PC_STVEBX:
        case PC_STVEHX:
        case PC_STVEWX:
        case PC_STVX:
        case PC_VADDCUW:
        case PC_VADDFP:
        case PC_VADDSBS:
        case PC_VADDSHS:
        case PC_VADDSWS:
        case PC_VADDUBM:
        case PC_VADDUBS:
        case PC_VADDUHM:
        case PC_VADDUHS:
        case PC_VADDUWM:
        case PC_VADDUWS:
        case PC_VAND:
        case PC_VANDC:
        case PC_VAVGSB:
        case PC_VAVGSH:
        case PC_VAVGSW:
        case PC_VAVGUB:
        case PC_VAVGUH:
        case PC_VAVGUW:
        case PC_VMAXFP:
        case PC_VMAXSB:
        case PC_VMAXSH:
        case PC_VMAXSW:
        case PC_VMAXUB:
        case PC_VMAXUH:
        case PC_VMAXUW:
        case PC_VMINFP:
        case PC_VMINSB:
        case PC_VMINSH:
        case PC_VMINSW:
        case PC_VMINUB:
        case PC_VMINUH:
        case PC_VMINUW:
        case PC_VMRGHB:
        case PC_VMRGHH:
        case PC_VMRGHW:
        case PC_VMRGLB:
        case PC_VMRGLH:
        case PC_VMRGLW:
        case PC_VMULESB:
        case PC_VMULESH:
        case PC_VMULEUB:
        case PC_VMULEUH:
        case PC_VMULOSB:
        case PC_VMULOSH:
        case PC_VMULOUB:
        case PC_VMULOUH:
        case PC_VNOR:
        case PC_VOR:
        case PC_VPKPX:
        case PC_VPKSHSS:
        case PC_VPKSHUS:
        case PC_VPKSWSS:
        case PC_VPKSWUS:
        case PC_VPKUHUM:
        case PC_VPKUHUS:
        case PC_VPKUWUM:
        case PC_VPKUWUS:
        case PC_VRLB:
        case PC_VRLH:
        case PC_VRLW:
        case PC_VSL:
        case PC_VSLB:
        case PC_VSLH:
        case PC_VSLO:
        case PC_VSLW:
        case PC_VSR:
        case PC_VSRAB:
        case PC_VSRAH:
        case PC_VSRAW:
        case PC_VSRB:
        case PC_VSRH:
        case PC_VSRO:
        case PC_VSRW:
        case PC_VSUBCUW:
        case PC_VSUBFP:
        case PC_VSUBSBS:
        case PC_VSUBSHS:
        case PC_VSUBSWS:
        case PC_VSUBUBM:
        case PC_VSUBUBS:
        case PC_VSUBUHM:
        case PC_VSUBUHS:
        case PC_VSUBUWM:
        case PC_VSUBUWS:
        case PC_VSUMSWS:
        case PC_VSUM2SWS:
        case PC_VSUM4SBS:
        case PC_VSUM4SHS:
        case PC_VSUM4UBS:
        case PC_VXOR:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            break;

        case PC_VCFSX:
        case PC_VCFUX:
        case PC_VCTSXS:
        case PC_VCTUXS:
        case PC_VSPLTB:
        case PC_VSPLTH:
        case PC_VSPLTW:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0xbUL);
            bits |= ((I(2) & 0x1fUL) << 0x10UL);
            break;

        case PC_VEXPTEFP:
        case PC_VLOGEFP:
        case PC_VREFP:
        case PC_VRFIM:
        case PC_VRFIN:
        case PC_VRFIP:
        case PC_VRFIZ:
        case PC_VRSQRTEFP:
        case PC_VUPKHPX:
        case PC_VUPKHSB:
        case PC_VUPKHSH:
        case PC_VUPKLPX:
        case PC_VUPKLSB:
        case PC_VUPKLSH:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0xbUL);
            break;

        case PC_VCMPBFP:
        case PC_VCMPEQFP:
        case PC_VCMPEQUB:
        case PC_VCMPEQUH:
        case PC_VCMPEQUW:
        case PC_VCMPGEFP:
        case PC_VCMPGTFP:
        case PC_VCMPGTSB:
        case PC_VCMPGTSH:
        case PC_VCMPGTSW:
        case PC_VCMPGTUB:
        case PC_VCMPGTUH:
        case PC_VCMPGTUW:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 0x400UL;
            break;

        case PC_VSPLTISB:
        case PC_VSPLTISH:
        case PC_VSPLTISW:
            bits |= (R(0) << 0x15UL);
            bits |= ((I(1) & 0x1fUL) << 0x10UL);
            break;

        case PC_VMHADDSHS:
        case PC_VMHRADDSHS:
        case PC_VMLADDUHM:
        case PC_VMSUMMBM:
        case PC_VMSUMSHM:
        case PC_VMSUMSHS:
        case PC_VMSUMUBM:
        case PC_VMSUMUHM:
        case PC_VMSUMUHS:
        case PC_VPERM:
        case PC_VSEL:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            bits |= (R(3) << 6);
            break;

        case PC_VMADDFP:
        case PC_VNMSUBFP:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 6);
            bits |= (R(3) << 0xbUL);
            break;

        case PC_VSLDOI:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            bits |= ((I(3) & 0xfUL) << 6);
            break;

        case PC_VMR:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(1) << 0xbUL);
            break;

        case PC_VMRP:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(1) << 0xbUL);
            break;

        case PC_MFVSCR:
            bits |= (R(0) << 0x15UL);
            break;

        case PC_MTVSCR:
            bits |= (R(0) << 0xbUL);
            break;

        case PC_PSQ_LX:
        case PC_PSQ_LUX:
        case PC_PSQ_STX:
        case PC_PSQ_STUX:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            bits |= (I(3) << 0xaUL);
            bits |= ((R(4) + 0xfffffc70UL) << 7);
            break;

        case PC_DCBZ_L:
            bits |= (R(0) << 0x10UL);
            bits |= (R(1) << 0xbUL);
            break;

        case PC_PS_ADD:
        case PC_PS_SUB:
        case PC_PS_DIV:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_PS_MADD:
        case PC_PS_MSUB:
        case PC_PS_NMADD:
        case PC_PS_NMSUB:
        case PC_PS_SEL:
        case PC_PS_SUM0:
        case PC_PS_SUM1:
        case PC_PS_MADDS0:
        case PC_PS_MADDS1:
            bits |= (R(3) << 0xbUL);
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 6);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_PS_MUL:
        case PC_PS_MULS0:
        case PC_PS_MULS1:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 6);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_PS_RES:
        case PC_PS_ABS:
        case PC_PS_NABS:
        case PC_PS_NEG:
        case PC_PS_MR:
        case PC_PS_RSQRTE:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

        case PC_PS_CMPU0:
        case PC_PS_CMPO0:
        case PC_PS_CMPU1:
        case PC_PS_CMPO1:
            bits |= (R(0) << 0x17UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            break;

        case PC_PS_MERGE00:
        case PC_PS_MERGE01:
        case PC_PS_MERGE10:
        case PC_PS_MERGE11:
            bits |= (R(0) << 0x15UL);
            bits |= (R(1) << 0x10UL);
            bits |= (R(2) << 0xbUL);
            if (((UInt32)(instr->flags >> 32) & 0x100000UL)) bits |= 1;
            break;

    }
    return CTool_EndianConvertWord32(bits);
}
#undef R
#undef I
#undef O

