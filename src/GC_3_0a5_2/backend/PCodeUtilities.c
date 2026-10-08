/* Native GC3 utility bodies. Address-based names remain provisional until a
 * symbol-bearing build establishes their original spelling. */
#pragma pack(push, 2)
typedef struct PCodeLabel PCodeLabel;
typedef struct Object { unsigned char unknown00[2]; unsigned char kind; } Object;
typedef struct PCodeOperand {
    unsigned char kind, registerClass;
    unsigned short flags;
    union { short reg; int immediate; void *pointer; } value;
    unsigned char unknown08[6];
} PCodeOperand;
typedef struct PCodeInstruction {
    unsigned char unknown00[12];
    unsigned int flags, flags2;
    unsigned char unknown14[20];
    short opcode, operandCount;
    PCodeOperand operands[1];
} PCodeInstruction;
typedef struct PCodeBlock { unsigned char unknown00[40]; short instructionCount; } PCodeBlock;
typedef struct PCodeOpcodeDescriptor {
    unsigned char unknown00[6];
    unsigned int flags, flags2;
    unsigned char unknown0e[8];
} PCodeOpcodeDescriptor;
#pragma pack(pop)
extern PCodeBlock *gCurrentBlock;
extern PCodeOpcodeDescriptor gPCodeOpcodeDescriptors[];
extern unsigned char pcodeObjectUsesBaseRegister;
extern PCodeInstruction *emitpcode(short opcode, ...);
extern PCodeInstruction *makepcode(short opcode, ...);
extern PCodeLabel *makepclabel(void);
extern void makepcblock(void);
extern void pcbranch(PCodeBlock *, PCodeLabel *, int);
extern void pclabel(PCodeBlock *, PCodeLabel *);
extern void appendpcode(PCodeBlock *, PCodeInstruction *);
extern void CError_Internal(const char *, int);
extern int fn_00587410(Object *);
extern void change_opcode(PCodeInstruction *, short);
extern void change_num_operands(PCodeInstruction *, int);
extern int gUsedVirtualRegistersGPR;
extern unsigned char fn_004c3f60(Object *);
typedef struct UtilityType { short unknown00, size; } UtilityType;
extern unsigned char Registers_LoadStoreType(UtilityType *);
extern unsigned char fn_00454260(UtilityType *);

void branch_indirect(Object *object)
{
    emitpcode(0x12, object, 0);
    makepcblock();
}

void branch_decrement_always(short opcode, PCodeLabel *target)
{
    PCodeLabel *fallthrough = makepclabel();
    emitpcode(opcode, target);
    pcbranch(gCurrentBlock, target, 0);
    pcbranch(gCurrentBlock, fallthrough, 0);
    makepcblock();
    pclabel(gCurrentBlock, fallthrough);
}

void branch_always(PCodeLabel *target)
{
    emitpcode(0, target);
    pcbranch(gCurrentBlock, target, 0);
    makepcblock();
}

void branch_conditional(short operand, short condition,
                                       short branchIfTrue, PCodeLabel *target)
{
    PCodeLabel *fallthrough = makepclabel();
    int kind;
    switch (condition) {
        case 0x18: branchIfTrue = !branchIfTrue;
        case 0x17: kind = 2; break;
        case 0x16: branchIfTrue = !branchIfTrue;
        case 0x13: kind = 0; break;
        case 0x15: branchIfTrue = !branchIfTrue;
        case 0x14: kind = 1; break;
    }
    emitpcode((short)(branchIfTrue ? 5 : 8), operand, kind, target);
    pcbranch(gCurrentBlock, target, 0);
    pcbranch(gCurrentBlock, fallthrough, 0);
    makepcblock();
    pclabel(gCurrentBlock, fallthrough);
}

void branch_label(PCodeLabel *label)
{
    if (gCurrentBlock->instructionCount) {
        pcbranch(gCurrentBlock, label, 0);
        makepcblock();
    }
    pclabel(gCurrentBlock, label);
}

PCodeInstruction *op_absolute_ha(short first, short base,
                                Object *object, short displacement, char append)
{
    PCodeInstruction *instruction;
    if (object->kind == 1) {
        instruction = makepcode(0x42, first, base, object, displacement);
    } else if (pcodeObjectUsesBaseRegister) {
        if (!(int)base) CError_Internal("PCodeUtilities.c", 752);
        instruction = makepcode(0x42, first, base, object, displacement);
    } else {
        if ((int)base) CError_Internal("PCodeUtilities.c", 757);
        instruction = makepcode(0x8a, first, object, displacement);
    }
    if (append) appendpcode(gCurrentBlock, instruction);
    return instruction;
}

PCodeInstruction *add_immediate_lo(short first, short base,
                                Object *object, short displacement, unsigned char append)
{
    PCodeInstruction *instruction;
    if (!object) CError_Internal("PCodeUtilities.c", 728);
    instruction = makepcode(0x3f, first, base, object, displacement);
    if (append) appendpcode(gCurrentBlock, instruction);
    return instruction;
}

/* This conversion changes branches to calls and records the link register.
 * Its original spelling is not established by the supplied Mac symbols. */
void pcsetlinkbit(PCodeInstruction *instruction)
{
    PCodeOperand *operand;
    int remaining;
    switch (instruction->opcode) {
        case 0: instruction->opcode = 1; break;
        case 0x12: instruction->opcode = 0x13; break;
        case 0x11: instruction->opcode = 0x14; break;
    }
    operand = instruction->operands;
    remaining = instruction->operandCount;
    while (operand->kind != 8 && remaining) {
        if (!operand->kind && !operand->registerClass && operand->value.reg == 1) {
            operand->flags |= 2;
            instruction->flags2 |= 0x800000;
            return;
        }
        operand++;
        remaining--;
    }
    if (operand->kind != 8) CError_Internal("PCodeUtilities.c", 266);
    operand->kind = 0;
    operand->registerClass = 0;
    operand->value.reg = 1;
    operand->flags = 2;
    if (gPCodeOpcodeDescriptors[instruction->opcode].flags & 8) {
        instruction->flags &= ~1;
        instruction->flags |= 8;
    }
    instruction->flags2 |= 0x800000;
}

void pcsetsideeffects(PCodeInstruction *instruction)
{
    instruction->flags &= ~0x6010;
    instruction->flags |= 0x100;
}

int fn_005960b0(PCodeInstruction *instruction)
{
    unsigned int second = instruction->flags2;
    unsigned int first = instruction->flags;
    second &= 0x20000;
    first &= 0x100;
    if (second == 0x20000 && !first) return 1;
    return 0;
}

static inline int vector_opcode(Object *object, int displacement, int selector)
{
    int opcode;
    if (object && object->kind == 1) {
        if ((fn_00587410(object) + displacement) >> 11)
            opcode = selector ? 0x194 : 0x198;
        else opcode = selector ? 0x192 : 0x196;
    } else opcode = selector ? 0x194 : 0x198;
    return opcode;
}

int fn_00594b60(Object *object, int displacement, int selector)
{
    return vector_opcode(object, displacement, selector);
}

void store_vr_x(short first, short second, short third)
{
    emitpcode(0xfe, first, second, third);
}

void load_vr_x(short first, short second, short third)
{
    emitpcode(0xf9, first, second, third);
}

void pcsetrecordbit(PCodeInstruction *instruction)
{
    PCodeOperand *operand;
    int remaining, registerNumber;
    instruction->flags &= ~0x6010;
    if ((instruction->flags2 & 0xe0000000) == 0x40000000)
        registerNumber = 1;
    else if ((instruction->flags2 & 0xe0000000) == 0x20000000)
        registerNumber = 6;
    else registerNumber = 0;
    if ((unsigned short)(instruction->opcode - 0x3f) <= 1) {
        instruction->flags2 |= 0x80000;
        instruction->flags2 |= 0x100000;
        change_num_operands(instruction, 5);
        change_opcode(instruction, 0x41);
        operand = &instruction->operands[3];
        if (operand->kind == 0 && operand->registerClass == 0 &&
            operand->value.reg != 0 && operand->kind != 8)
            CError_Internal("PCodeUtilities.c", 157);
        operand->kind = 0;
        operand->registerClass = 0;
        operand->value.reg = 0;
        operand->flags = 2;
        operand = &instruction->operands[4];
        if (operand->kind != 8) CError_Internal("PCodeUtilities.c", 162);
        operand->kind = 0;
        operand->registerClass = 1;
        operand->value.reg = registerNumber;
        operand->flags = 2;
        return;
    }
    operand = instruction->operands;
    remaining = instruction->operandCount;
    while (operand->kind != 8 && remaining) {
        if (operand->kind == 0 && operand->registerClass == 1 &&
            operand->value.reg == registerNumber) {
            operand->flags |= 2;
            instruction->flags2 |= 0x100000;
            return;
        }
        operand++;
        remaining--;
    }
    if (remaining <= 0) {
        operand = &instruction->operands[instruction->operandCount];
        instruction->operandCount++;
    }
    if (operand->kind != 8) CError_Internal("PCodeUtilities.c", 187);
    operand->kind = 0;
    operand->registerClass = 1;
    operand->value.reg = registerNumber;
    operand->flags = 2;
    instruction->flags2 |= 0x100000;
}

void fn_00596280(PCodeInstruction *instruction)
{
    PCodeOperand *operand;
    int remaining, registerNumber;
    if (!(instruction->flags2 & 0x100000)) CError_Internal("PCodeUtilities.c", 46);
    if ((instruction->flags2 & 0xe0000000) == 0x40000000)
        registerNumber = 1;
    else if ((instruction->flags2 & 0xe0000000) == 0x20000000)
        registerNumber = 6;
    else registerNumber = 0;
    if ((unsigned short)(instruction->opcode - 0x40) <= 1) {
        instruction->flags2 &= ~0x100000;
        change_num_operands(instruction, 4);
        change_opcode(instruction, 0x40);
        operand = &instruction->operands[3];
        operand->kind = 0;
        operand->registerClass = 0;
        operand->value.reg = 0;
        operand->flags = 2;
        return;
    }
    operand = instruction->operands;
    remaining = instruction->operandCount;
    while (operand->kind != 8 && remaining) {
        if (operand->kind == 0 && operand->registerClass == 1 &&
            operand->value.reg == registerNumber) {
            if (operand->flags & 1) CError_Internal("PCodeUtilities.c", 79);
            while (remaining > 1) {
                *operand = operand[1];
                operand++;
                remaining--;
            }
            change_num_operands(instruction, instruction->operandCount - 1);
            change_opcode(instruction, instruction->opcode);
            instruction->flags2 &= ~0x100000;
            return;
        }
        operand++;
        remaining--;
    }
    CError_Internal("PCodeUtilities.c", 98);
}

void load_store_register(short opcode, short destination, short base,
                                 Object *object, int displacement)
{
    short address = base, offsetRegister, temporary;
    if (object && object->kind != 1) {
        if (fn_004c3f60(object) && (base == 2 || base == 13)) {
            address = 0;
        } else if (displacement) {
            address = gUsedVirtualRegistersGPR++;
            appendpcode(gCurrentBlock,
                add_immediate_lo(address, base, object, 0, 0));
            object = 0;
        }
    }
    if (displacement != (short)displacement) {
        if (opcode == 0x22 && destination == 12) offsetRegister = 12;
        else if (opcode == 0x22 && destination == 11) offsetRegister = 11;
        else offsetRegister = gUsedVirtualRegistersGPR++;
        emitpcode(0x42, offsetRegister, address, 0,
                  (short)((displacement >> 16) + ((displacement >> 15) & 1)));
        displacement = (short)displacement;
        address = offsetRegister;
    }
    if (gPCodeOpcodeDescriptors[opcode].flags2 & 0x4000) {
        offsetRegister = 0;
        if (object) {
            temporary = gUsedVirtualRegistersGPR++;
            emitpcode(0x3f, temporary, address, object, displacement);
            address = temporary;
        } else if (displacement) {
            offsetRegister = gUsedVirtualRegistersGPR++;
            emitpcode(0x89, offsetRegister, displacement);
        }
        if (opcode >= 0x192 && opcode <= 0x199) {
            if (offsetRegister) emitpcode(opcode, destination, address, offsetRegister, 0, 0x390);
            else emitpcode(opcode, destination, 0, address, 0, 0x390);
        } else {
            if (offsetRegister) emitpcode(opcode, destination, address, offsetRegister);
            else emitpcode(opcode, destination, 0, address);
        }
    } else emitpcode(opcode, destination, address, object, displacement);
}

static inline int opcode_for_store_gpr(unsigned char registerClass, short size)
{
    int opcode = 0x31;
    switch (registerClass) {
        case 0:
            switch (size) {
                case 1: opcode = 0x28; break;
                case -2: case 2: opcode = 0x2c; break;
                case 4: opcode = 0x31; break;
                case 8: default: CError_Internal("PCodeUtilities.c", 1052);
            }
            break;
        default: CError_Internal("PCodeUtilities.c", 1098);
    }
    return opcode;
}

static inline int opcode_for_store_fpr(unsigned char registerClass, short size)
{
    int opcode = 0x9a;
    switch (registerClass) {
        case 0:
            switch (size) {
                case 4: opcode = 0x96; break;
                case 8: opcode = 0x9a; break;
                default: CError_Internal("PCodeUtilities.c", 1117);
            }
            break;
        case 1: opcode = 0x198; break;
        default: CError_Internal("PCodeUtilities.c", 1143);
    }
    return opcode;
}

static inline int opcode_for_load_fpr(unsigned char registerClass, short size)
{
    int opcode = 0x92;
    switch (registerClass) {
        case 0:
            switch (size) {
                case 4: opcode = 0x8e; break;
                case 8: opcode = 0x92; break;
                default: CError_Internal("PCodeUtilities.c", 995);
            }
            break;
        case 1: opcode = 0x194; break;
        default: CError_Internal("PCodeUtilities.c", 1021);
    }
    return opcode;
}

int opcode_for_load_gpr(unsigned char registerClass, short size)
{
    int opcode = 0x22;
    switch (registerClass) {
        case 0:
            switch (size) {
                case 1: opcode = 0x15; break;
                case 2: opcode = 0x19; break;
                case -2: opcode = 0x1d; break;
                case 4: opcode = 0x22; break;
                case 8: default: CError_Internal("PCodeUtilities.c", 916);
            }
            break;
        case 2:
            switch (size) {
                case 4: case 8: opcode = 0x22; break;
                default: CError_Internal("PCodeUtilities.c", 927);
            }
            break;
        default: CError_Internal("PCodeUtilities.c", 976);
    }
    return opcode;
}

void store_fpr_x(UtilityType *type, short first, short second, short third)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    int opcode;
    switch (registerClass) {
        case 0: opcode = opcode_for_store_fpr(registerClass, size) + 2; break;
        case 1:
            opcode = opcode_for_store_fpr(registerClass, size);
            emitpcode((short)opcode, first, second, third, 0, 0x390);
            return;
        default: CError_Internal("PCodeUtilities.c", 1495);
    }
    emitpcode((short)opcode, first, second, third);
}

void store_fpr(UtilityType *type, short destination, short base, Object *object, int displacement)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    short opcode = opcode_for_store_fpr(registerClass, size);
    load_store_register(opcode, destination, base, object, displacement);
}

void store_gpr_x(UtilityType *type, short first, short second, short third)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    int opcode;
    switch (registerClass) {
        case 0: opcode = opcode_for_store_gpr(registerClass, size) + 2; break;
        default: CError_Internal("PCodeUtilities.c", 1426);
    }
    emitpcode((short)opcode, first, second, third);
}

void store_gpr_u(UtilityType *type, short destination, short base, Object *object, int displacement)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    int opcode;
    switch (registerClass) {
        case 0: opcode = opcode_for_store_gpr(registerClass, size) + 1; break;
        default: CError_Internal("PCodeUtilities.c", 1399);
    }
    load_store_register((short)opcode, destination, base, object, displacement);
}

void store_gpr(UtilityType *type, short destination, short base, Object *object, int displacement)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    short opcode = opcode_for_store_gpr(registerClass, size);
    load_store_register(opcode, destination, base, object, displacement);
}

void load_fpr_x(UtilityType *type, short first, short second, short third)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    int opcode;
    switch (registerClass) {
        case 0: opcode = opcode_for_load_fpr(registerClass, size) + 2; break;
        case 1:
            opcode = opcode_for_load_fpr(registerClass, size);
            emitpcode((short)opcode, first, second, third, 0, 0x390);
            return;
        default: CError_Internal("PCodeUtilities.c", 1323);
    }
    emitpcode((short)opcode, first, second, third);
}

void load_fpr(UtilityType *type, short destination, short base, Object *object, int displacement)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    short opcode = opcode_for_load_fpr(registerClass, size);
    load_store_register(opcode, destination, base, object, displacement);
}

void load_gpr_x(UtilityType *type, short first, short second, short third)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    int opcode;
    if (!fn_00454260(type) && size == 2) size = -2;
    switch (registerClass) {
        case 0: opcode = opcode_for_load_gpr(registerClass, size) + 2; break;
        default: CError_Internal("PCodeUtilities.c", 1250);
    }
    emitpcode((short)opcode, first, second, third);
}

void load_gpr_u(UtilityType *type, short destination, short base, Object *object, int displacement)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    int opcode;
    if (!fn_00454260(type) && size == 2) size = -2;
    switch (registerClass) {
        case 0: opcode = opcode_for_load_gpr(registerClass, size) + 1; break;
        default: CError_Internal("PCodeUtilities.c", 1219);
    }
    load_store_register((short)opcode, destination, base, object, displacement);
}

void load_gpr(UtilityType *type, short destination, short base, Object *object, int displacement)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    if (!fn_00454260(type) && size == 2) size = -2;
    load_store_register((short)opcode_for_load_gpr(registerClass, size), destination, base, object, displacement);
}

PCodeInstruction *make_load_gpr(UtilityType *type, short destination, short base, int displacement)
{
    unsigned char registerClass = Registers_LoadStoreType(type);
    short size = type->size;
    if (!fn_00454260(type) && size == 2) size = -2;
    return makepcode((short)opcode_for_load_gpr(registerClass, size), destination, base, 0, displacement);
}

void store_vr(short destination, short base, Object *object, int displacement)
{
    load_store_register(0xfe, destination, base, object, displacement);
}

void load_vr(short destination, short base, Object *object, int displacement)
{
    load_store_register(0xf9, destination, base, object, displacement);
}

void fn_005949a0(short destination, short base, Object *object, int displacement,
                 int firstPayload, int secondPayload, int selector)
{
    short opcode = vector_opcode(object, displacement, selector);
    short address = base, index = 0;
    if (object && object->kind != 1 && fn_004c3f60(object) && (base == 2 || base == 13))
        address = 0;
    if (opcode == 0x192 || opcode == 0x196) {
            emitpcode(opcode, destination, address, object, displacement, firstPayload, secondPayload);
    } else if (opcode == 0x194 || opcode == 0x198) {
            if (object) {
                short temporary = gUsedVirtualRegistersGPR++;
                emitpcode(0x3f, temporary, address, object, displacement);
                address = temporary;
            } else if (displacement) {
                index = gUsedVirtualRegistersGPR++;
                emitpcode(0x89, index, displacement);
            }
            if (index) emitpcode(opcode, destination, address, index, firstPayload, secondPayload);
            else emitpcode(opcode, destination, 0, address, firstPayload, secondPayload);
    } else CError_Internal("PCodeUtilities.c", 1644);
}

extern void fn_005829d0(PCodeInstruction *, PCodeInstruction *);
void add_immediate_before(PCodeInstruction *before, short destination, short base,
                 Object *object, short displacement)
{
    short address = base;
    unsigned char append = before == 0;
    PCodeInstruction *instruction;
    if (object) {
        if (base == 2 || base == 13) {
            if (object->kind == 1) CError_Internal("PCodeUtilities.c", 662);
            address = 0;
        } else if (displacement && object->kind != 1) {
            address = gUsedVirtualRegistersGPR++;
            instruction = add_immediate_lo(address, base, object, 0, 0);
            if (append) appendpcode(gCurrentBlock, instruction);
            else fn_005829d0(before, instruction);
            object = 0;
        }
    }
    if (!object && !displacement) {
        instruction = makepcode(0x8b, destination, address);
        if (append) appendpcode(gCurrentBlock, instruction);
        else fn_005829d0(before, instruction);
        return;
    }
    instruction = makepcode(0x3f, destination, address, object, displacement);
    if (!address) {
        instruction->flags = (instruction->flags & ~gPCodeOpcodeDescriptors[instruction->opcode].flags) |
                              gPCodeOpcodeDescriptors[0x89].flags;
        instruction->flags2 = (instruction->flags2 & ~gPCodeOpcodeDescriptors[instruction->opcode].flags2) |
                               gPCodeOpcodeDescriptors[0x89].flags2;
        instruction->opcode = 0x89;
        instruction->operands[1] = instruction->operands[2];
        change_num_operands(instruction, 2);
    }
    if (append) appendpcode(gCurrentBlock, instruction);
    else fn_005829d0(before, instruction);
}

void add_immediate(short destination, short base, Object *object, short displacement)
{
    add_immediate_before(0, destination, base, object, displacement);
}

#pragma pack(push, 2)
typedef struct UtilityRegister {
    struct UtilityRegister *next;
    int active;
    unsigned char unknown08[4], registerClass;
    signed char reg;
} UtilityRegister;
typedef struct UtilityStatement { unsigned char unknown00[18]; void *boundObjects; } UtilityStatement;
#pragma pack(pop)
extern int utilityRegisterCounts[5], utilityRegisterNumbers[5][32];
extern UtilityRegister *utilityAdditionalRegisters;
extern UtilityStatement *gCurrentStatement;
extern unsigned char utilityCollectExceptionOperands, utilityPreserveFPR1;
extern int countexceptionactionregisters(void *);
extern void noteexceptionactionregisters(void *, PCodeOperand *);
extern void recordexceptionactions(PCodeInstruction *, void *);
extern unsigned char fn_004c3f90(Object *, int);
extern void fn_00582b50(void);

PCodeOperand *branch_record_volatiles(PCodeOperand *operand, int *registerMasks)
{
    signed char registerClass;
    int index;
    UtilityRegister *additional;
    for (registerClass = 4; registerClass >= 0; registerClass--) {
        for (index = 0; index < utilityRegisterCounts[registerClass]; index++) {
            operand->kind = 0;
            operand->registerClass = registerClass;
            operand->value.reg = utilityRegisterNumbers[registerClass][index];
            operand->flags = 2;
            if (registerMasks[registerClass] & (1 << utilityRegisterNumbers[registerClass][index]))
                operand->flags |= 1;
            if (registerClass == 1 && operand->value.reg == 1 && utilityPreserveFPR1)
                operand->flags |= 1;
            operand++;
        }
    }
    for (additional = utilityAdditionalRegisters; additional; additional = additional->next) {
        if (additional->active) {
            operand->kind = 0;
            operand->registerClass = additional->registerClass;
            operand->value.reg = additional->reg;
            operand->flags = 3;
            operand++;
        }
    }
    return operand;
}

#pragma opt_unroll_loops off
int branch_count_volatiles(void)
{
    signed char registerClass;
    int count = 0;
    UtilityRegister *additional;
    for (registerClass = 0; registerClass < 5; registerClass++)
        count += utilityRegisterCounts[registerClass];
    for (additional = utilityAdditionalRegisters; additional; additional = additional->next)
        if (additional->active) count++;
    return count;
}
#pragma opt_unroll_loops reset

void branch_subroutine_ctr(int *registerMasks)
{
    int count = branch_count_volatiles();
    PCodeInstruction *instruction;
    PCodeOperand *operand;
    if (utilityCollectExceptionOperands && gCurrentStatement)
        count += countexceptionactionregisters(gCurrentStatement->boundObjects);
    instruction = makepcode(0x13, count);
    operand = branch_record_volatiles(instruction->operands + 1, registerMasks);
    if (utilityCollectExceptionOperands && gCurrentStatement)
        noteexceptionactionregisters(gCurrentStatement->boundObjects, operand);
    appendpcode(gCurrentBlock, instruction);
    fn_00582b50();
    if (utilityCollectExceptionOperands && gCurrentStatement)
        recordexceptionactions(instruction, gCurrentStatement->boundObjects);
}

void branch_subroutine(Object *object, short emitInstruction, int *registerMasks)
{
    int count = branch_count_volatiles();
    unsigned char kind;
    PCodeInstruction *instruction;
    PCodeOperand *operand;
    if (utilityCollectExceptionOperands && gCurrentStatement)
        count += countexceptionactionregisters(gCurrentStatement->boundObjects);
    kind = fn_004c3f90(object, 2);
    if (kind == 8) instruction = makepcode(1, count, object, 0);
    else if (kind == 9) {
        instruction = makepcode(1, count, object, 0);
        instruction->flags2 |= 0x8000000;
    } else instruction = makepcode(1, count, object, 0);
    operand = branch_record_volatiles(instruction->operands + 1, registerMasks);
    if (utilityCollectExceptionOperands && gCurrentStatement)
        noteexceptionactionregisters(gCurrentStatement->boundObjects, operand);
    appendpcode(gCurrentBlock, instruction);
    if (emitInstruction) emitpcode(0x8c);
    fn_00582b50();
    if (utilityCollectExceptionOperands && gCurrentStatement)
        recordexceptionactions(instruction, gCurrentStatement->boundObjects);
}
