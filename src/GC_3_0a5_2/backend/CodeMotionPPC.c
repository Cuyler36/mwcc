/* GC 3.0a5.2 CodeMotionPPC.c; native Windows layouts, not 1.2.5 records.
 * The supplied maps do not identify the four Windows function names.
 * General CodeMotion roles are carried over where their behavior is proven.
 */
typedef unsigned int UInt32;
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef signed short SInt16;
typedef struct NativeInstruction NativeInstruction;
typedef struct NativeBlock NativeBlock;
typedef struct NativeLoop NativeLoop;
typedef struct NativeReference NativeReference;

#pragma pack(push, 2)
typedef struct NativeOperand {
    SInt8 kind;
    SInt8 regclass;
    unsigned short flags;
    SInt16 reg;
    UInt32 payload[2];
} NativeOperand;
struct NativeInstruction {
    NativeInstruction *next;
    NativeInstruction *previous;
    NativeBlock *block;
    UInt32 flags;
    UInt32 flags2;
    int useStart;
    int definitionStart;
    NativeReference *reference;
    unsigned char unknown20[8];
    SInt16 opcode;
    SInt16 operandCount;
    NativeOperand operands[3];
};
struct NativeBlock {
    NativeBlock *next;
    unsigned char unknown04[16];
    NativeInstruction *firstInstruction;
    NativeInstruction *lastInstruction;
    int index;
};
struct NativeLoop {
    unsigned char unknown00[20];
    NativeBlock *preheader;
    unsigned char unknown18[16];
    UInt32 *memberblocks;
    unsigned char unknown2c[40];
    int bodySize;
};
struct NativeReference {
    unsigned char unknown00[16];
    void *object;
    UInt32 unknown14;
    int size;
    unsigned char unknown1c[16];
    UInt8 kind;
};
typedef struct NativeDefinition {
    SInt8 kind;
    SInt8 regclass;
    union {
        SInt16 reg;
        UInt32 raw;
        void *object;
    } value;
} NativeDefinition;
typedef struct NativeMotionEntry {
    NativeInstruction *instruction;
    NativeDefinition definition;
} NativeMotionEntry;
typedef struct NativeEntryLink {
    struct NativeEntryLink *next;
    int entryIndex;
} NativeEntryLink;
#pragma pack(pop)

typedef char CheckOperandSize[sizeof(NativeOperand) == 14 ? 1 : -1];
typedef char CheckEntrySize[sizeof(NativeMotionEntry) == 10 ? 1 : -1];
typedef char CheckLoopBodyOffset[sizeof(NativeLoop) == 88 ? 1 : -1];

extern int codeMotionPhysicalRegisterCounts[];
extern NativeEntryLink **codeMotionDefinitionHeads[];
extern NativeMotionEntry *codeMotionEntries;
extern int codeMotionEntryCount;
extern int gCodeMotionChanged;
extern UInt8 is_loop_invariant(NativeInstruction *, NativeLoop *, UInt32 *, UInt8, UInt8);
extern void move_instruction_to_preheader(NativeInstruction *, NativeLoop *);
extern void PCode_UnlinkInstruction(NativeInstruction *);
extern void PCode_InsertInstructionBefore(NativeInstruction *, NativeInstruction *);
extern int fn_00629df0(int, NativeLoop *);
extern int fn_00629ca0(NativeInstruction *, NativeLoop *);
extern int has_use_outside_loop_in_preheader_set(NativeDefinition *, NativeLoop *);
extern UInt8 fn_004531a0(void *);
extern int nbytes_loaded_or_stored_by(NativeInstruction *);
extern void CError_Internal(const char *, int);

/* All five native references to 0x7028e0 belong to fn_006438a0. */
NativeInstruction *codeMotionPPCNextInstruction;

NativeInstruction *fn_006436d0(NativeLoop *loop, NativeInstruction *instruction, UInt32 *definitions)
{
    NativeInstruction *candidate;
    NativeInstruction *selected;
    NativeEntryLink *link;
    int index;
    int blockIndex;

    if (instruction->operands[0].reg < codeMotionPhysicalRegisterCounts[instruction->operands[0].regclass]) {
        for (selected = instruction->previous; selected; selected = selected->previous) {
            if (selected->operandCount > 0 && selected->operands[0].kind == 0 &&
                selected->operands[0].regclass == 1 && (selected->operands[0].flags & 2) &&
                !((selected->flags & 0x1a9) | (selected->flags2 & 0x100000)) &&
                is_loop_invariant(selected, loop, definitions, 1, 0) == 1)
                break;
        }
    } else {
      selected = 0;
      for (link = codeMotionDefinitionHeads[instruction->operands[0].regclass][instruction->operands[0].reg];
         link; link = link->next) {
        index = link->entryIndex;
        if ((definitions[index >> 5] >> (index & 31)) & 1) {
            candidate = codeMotionEntries[index].instruction;
            if (candidate->block) {
                blockIndex = codeMotionEntries[index].instruction->block->index;
                if ((loop->memberblocks[blockIndex >> 5] >> (blockIndex & 31)) & 1) {
                    if (candidate->block != instruction->block)
                        return 0;
                    if (is_loop_invariant(candidate, loop, definitions, 1, 0) != 1)
                        return 0;
                    if (selected)
                        return 0;
                    selected = candidate;
                }
            }
        }
      }
    }
    return selected;
}

void fn_00643840(NativeLoop *loop, NativeInstruction *instruction, NativeInstruction *comparison)
{
    if (!(instruction->flags2 & 0x100000) &&
        comparison->operands[0].reg < codeMotionPhysicalRegisterCounts[comparison->operands[0].regclass]) {
        PCode_UnlinkInstruction(instruction);
        PCode_InsertInstructionBefore(loop->preheader->lastInstruction, instruction);
        --loop->bodySize;
        gCodeMotionChanged = 1;
    } else {
        move_instruction_to_preheader(instruction, loop);
    }
}

int fn_006438a0(NativeInstruction *instruction, NativeLoop *loop)
{
    NativeInstruction *next = instruction->next;
    NativeInstruction *other;
    NativeMotionEntry *entry;
    NativeDefinition *definition;
    NativeEntryLink *link;
    int index;
    int nextIndex;
    int otherIndex;
    int blockIndex;

    if (instruction->opcode == 0x44 && codeMotionPPCNextInstruction == instruction) {
        codeMotionPPCNextInstruction = 0;
        return 1;
    }
    codeMotionPPCNextInstruction = 0;
    if (instruction->opcode != 0x6c || !next || next->opcode != 0x44 ||
        instruction->operands[0].reg != next->operands[0].reg ||
        next->operands[0].reg != next->operands[1].reg ||
        (instruction->flags & 0x1a8) || (next->flags & 0x1a8))
        return 0;

    index = instruction->definitionStart;
    nextIndex = instruction->next->definitionStart;
    entry = &codeMotionEntries[index];
    definition = &entry->definition;
    codeMotionPPCNextInstruction = 0;
    if (index >= codeMotionEntryCount || entry->instruction != instruction ||
        (index + 1 < codeMotionEntryCount && entry[1].instruction == instruction))
        return 0;
    if (entry->definition.kind == 0 && entry->definition.regclass == 4) {
        for (link = codeMotionDefinitionHeads[4][definition->value.reg]; link; link = link->next) {
            otherIndex = link->entryIndex;
            other = codeMotionEntries[otherIndex].instruction;
            if (other->block) {
                blockIndex = codeMotionEntries[otherIndex].instruction->block->index;
                if (((loop->memberblocks[blockIndex >> 5] >> (blockIndex & 31)) & 1) &&
                    otherIndex != index && otherIndex != nextIndex)
                    return 0;
            }
        }
    } else {
        CError_Internal("CodeMotionPPC.c", 151);
    }
    if (!fn_00629df0(instruction->definitionStart, loop))
        return 0;
    if (!fn_00629ca0(instruction, loop) &&
        has_use_outside_loop_in_preheader_set(&codeMotionEntries[instruction->definitionStart].definition, loop))
        return 0;
    if (!fn_00629ca0(instruction->next, loop) &&
        has_use_outside_loop_in_preheader_set(&codeMotionEntries[instruction->next->definitionStart].definition, loop))
        return 0;
    codeMotionPPCNextInstruction = next;
    return 1;
}

int fn_00643b00(NativeInstruction *instruction, int bodySize, int allowComparison, int skipComparison,
                int limitLifetime)
{
    if (instruction->operands[0].kind == 0 && instruction->operands[0].regclass == 1 &&
        (skipComparison || !allowComparison))
        return 0;
    if (bodySize <= 25 || !limitLifetime)
        return 1;
    switch (instruction->opcode) {
    case 0x89:
    case 0x8a:
    case 0x160:
    case 0x161:
    case 0x162:
        return 1;
    case 0x3f:
    case 0x42:
        if (instruction->operands[2].kind != 4)
            return 0;
        return 1;
    case 0x8e:
    case 0x92:
    case 0xf9:
        if (!(instruction->flags & 0x180) && instruction->reference &&
            (instruction->reference->kind == 0 || instruction->reference->kind == 1) && fn_004531a0(instruction->reference->object) &&
            instruction->reference->size == nbytes_loaded_or_stored_by(instruction))
            return 1;
        break;
    }
    return 0;
}

UInt8 fn_00643bd0(NativeInstruction *instruction, NativeOperand *operand, NativeLoop *loop,
                  UInt32 *definitions, UInt32 allowComparison)
{
    if (!allowComparison && operand->kind == 0 && operand->regclass == 1)
        return 0;
    return 1;
}

UInt8 fn_00643c00(NativeInstruction *instruction, NativeOperand *operand, NativeLoop *loop,
                  UInt32 *definitions, UInt32 allowComparison)
{
    if (operand->regclass == 1) {
        if (allowComparison && (operand->flags & 3) == 2)
            return 1;
    } else if (operand->regclass == 0 && operand->reg == 0) {
        return 2;
    }
    return 0;
}
