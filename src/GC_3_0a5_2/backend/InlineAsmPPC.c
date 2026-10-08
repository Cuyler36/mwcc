/* Native GC3 inline assembler. Unproved private names retain native addresses. */
#include <stddef.h>
#include <string.h>

#pragma pack(push, 2)
typedef struct MachineInt64 { unsigned int hi, lo; } MachineInt64;
typedef struct MachineType { unsigned char kind, unknown01; int size; } MachineType;
typedef struct MachineObject {
    unsigned char objectClass, unknown01, kind;
    unsigned char unknown03[9];
    char *name;
    MachineType *type;
    unsigned char unknown14[4];
    short storage;
    unsigned short flags;
} MachineObject;
typedef struct MachineLabel { unsigned char unknown00[12]; char *name; } MachineLabel;
typedef struct MachineExpression {
    unsigned char kind, unknown01[15];
    MachineObject *object;
} MachineExpression;
typedef struct MachineAsmOperand {
    unsigned char kind, negative;
    union {
        struct { int value; MachineObject *object; } reference;
        MachineInt64 integer;
    } data;
    unsigned short flags;
    unsigned char registerClass, unknown0d;
} MachineAsmOperand;
typedef struct MachineAsmInstruction {
    unsigned int opcode;
    unsigned char specialFlags, branchFlags;
    short operandCount;
    MachineAsmOperand operands[1];
} MachineAsmInstruction;
typedef struct MachineStatement {
    unsigned char unknown00[10];
    MachineAsmInstruction *instruction;
    unsigned char unknown0e[20];
} MachineStatement;
typedef struct MachineAsmOpcode {
    const char *mnemonic, *operandFormat;
    unsigned char operandCount, rank;
    unsigned int flags, flags2, encoding;
} MachineAsmOpcode;
typedef struct MachineAsmExpression {
    unsigned char type, flags;
    short isLocal;
    MachineInt64 value;
    MachineObject *objectLabel, *object, *secondObject;
    MachineLabel *label, *secondLabel;
} MachineAsmExpression;
typedef struct MachineAsmEffectOperand {
    unsigned char kind, unknown01;
    MachineObject *object;
    int offset, size;
} MachineAsmEffectOperand;
typedef struct MachineAsmEffects {
    unsigned char barrier, writesMemory, readsMemory, controlFlow, branchWithLink, noFallthrough;
    unsigned char unknown06[4];
    int operandCount, labelCount;
    MachineAsmEffectOperand operands[16];
    void *labels[16];
} MachineAsmEffects;
#pragma pack(pop)
typedef char VerifyAsmOperand[(sizeof(MachineAsmOperand)==14)?1:-1];
typedef char VerifyAsmInstruction[(offsetof(MachineAsmInstruction,operands)==8)?1:-1];
typedef char VerifyAsmStatement[(sizeof(MachineStatement)==34)?1:-1];
typedef char VerifyAsmOpcode[(sizeof(MachineAsmOpcode)==22)?1:-1];
typedef char VerifyAsmExpression[(sizeof(MachineAsmExpression)==32)?1:-1];
typedef char VerifyEffectOperand[(sizeof(MachineAsmEffectOperand)==14)?1:-1];
typedef char VerifyEffectLabels[(offsetof(MachineAsmEffects,labels)==242)?1:-1];

extern void *galloc(int);
extern void memclrw(void *, int);
extern signed char Registers_ClassForType(MachineType *);
extern MachineAsmOpcode inlineAsmOpcodes[];
extern void Test_Version_Numbers(void);
extern MachineInt64 fn_00449290(short);
extern void fn_005cc290(void), fn_005cb7b0(void);
extern void MWCATS_AddProc(void *, int);
extern void process_arguments(void (*)(void), void *);
extern void fn_004bdd80(void), fn_004bd970(void), fn_004bdb80(void);
extern short getbit(int);
extern void PPCError_Error(int, ...), PPCError_Warning(int, ...);
extern void *Registers_GetVarInfo(MachineObject *);
extern int CError_Internal(const char *, int);
static char inlineAsmFilename[] = "InlineAsmPPC.c";

extern unsigned char assembler_type;
extern unsigned char asmSectionAttributeEnabled, asmSectionAttributeDisabled;
extern void *asmCurrentFunction;
extern unsigned char asmOptionSticky, asmOptionForceSticky, asmGlobalEnabled;
extern int asmInitializationFlag;
extern unsigned char asmHardwareFPU;
extern int asmInstructionCount;
extern short asmProcessor;
extern MachineInt64 asmCPU;
extern unsigned char asmOptionFPU, asmOptionFloat, asmOptionExtensions;
extern unsigned char asmFrameAlignmentLog;
extern short asmToken;
extern unsigned char InlineAsm_gccmode;
extern void CError_Error(int, ...);
extern short fn_0055ebc0(void);
extern void *fn_005a3730(void);
extern int InlineAsm_ExpressionPPC(int);
extern MachineType asmExpressionIntegerType;
extern MachineInt64 CMach_CalcIntDiadic(MachineType *, MachineInt64, short, MachineInt64);
extern short fn_00456110(short);
extern char *asmIdentifier;
typedef struct MachineAsmLookup { unsigned char unknown00[8]; MachineObject *object; unsigned char unknown0c[16]; } MachineAsmLookup;
extern unsigned char fn_0055e9a0(char *, MachineAsmLookup *);
extern int fn_0057a740(MachineObject *);
extern MachineObject *asmCurrentObject;
extern void CFunc_SetStatementSourceRef(void);
extern MachineStatement *CFunc_AppendStatement(int);
void fn_00574640(MachineAsmOperand *, signed char, int, int);
int InlineAsm_ConstantExpressionPPC(int, int);
void InlineAsm_ProcessDirective(int);
void fn_00575b60(MachineAsmExpression *, int);
void fn_00575760(MachineAsmExpression *, int);
void fn_005754f0(MachineAsmExpression *, int);
void fn_00575820(MachineAsmExpression *, short, MachineAsmExpression *);



MachineStatement *CodeGen_CopyAsmStat(MachineStatement *statement)
{
    MachineStatement *copy;
    int size;
    MachineAsmInstruction *newInstruction, *instruction;
    copy = galloc(sizeof(MachineStatement));
    *copy = *statement;
    instruction = statement->instruction;
    size = 8 + instruction->operandCount * 14;
    newInstruction = galloc(size);
    memcpy(newInstruction, instruction, size);
    copy->instruction = newInstruction;
    return copy;
}

void CodeGen_PropagateIntoAsm(MachineStatement *statement, MachineObject *oldObject,
                             MachineExpression *expression)
{
    MachineAsmInstruction *instruction = statement->instruction;
    MachineObject *replacement;
    MachineAsmOperand *operand;
    int i;
    if (expression->kind != 0x3b) return;
    replacement = expression->object;
    if (oldObject->objectClass != replacement->objectClass || oldObject->kind != replacement->kind) return;
    for (i = 0; i < instruction->operandCount; i++) {
        operand = &instruction->operands[i];
        switch (operand->kind) {
            case 2:
                if (operand->data.reference.object == oldObject && (operand->flags & 3) == 1 &&
                    operand->registerClass == (unsigned char)Registers_ClassForType(replacement->type))
                    operand->data.reference.object = replacement;
                break;
            case 3: case 4:
                if (!(inlineAsmOpcodes[instruction->opcode].flags & 0x40004) &&
                    operand->data.reference.object == oldObject)
                    operand->data.reference.object = replacement;
                break;
        }
    }
}

const char *InlineAsm_GetMnemonic(MachineAsmInstruction *instruction)
{
    return inlineAsmOpcodes[instruction->opcode].mnemonic;
}

void InlineAsm_InitializePPC(void)
{
    Test_Version_Numbers();
    asmOptionSticky = asmOptionSticky || asmOptionForceSticky;
    asmGlobalEnabled = 1;
    asmInitializationFlag = 1;
    asmHardwareFPU = 1;
    asmInstructionCount = 0;
    asmCPU = fn_00449290(asmProcessor);
    if (asmOptionFPU) {
        if (asmOptionFloat) asmHardwareFPU = 0;
    } else asmHardwareFPU = 0;
    if (asmOptionExtensions) asmCPU.lo |= 0x40000000;
}

void InlineAsm_Initialize(unsigned char mode)
{
    assembler_type = mode;
    if (asmSectionAttributeEnabled && !asmSectionAttributeDisabled)
        MWCATS_AddProc(asmCurrentFunction, 1);
    if (!assembler_type) InlineAsm_InitializePPC();
    fn_005cc290();
    fn_005cb7b0();
    if (assembler_type) {
        process_arguments(fn_004bdd80, 0);
        fn_004bdb80();
    }
}

void fn_005721a0(void)
{
    assembler_type = 1;
    if (asmSectionAttributeEnabled && !asmSectionAttributeDisabled)
        MWCATS_AddProc(asmCurrentFunction, 1);
    if (!assembler_type) InlineAsm_InitializePPC();
    fn_005cc290();
    fn_005cb7b0();
    if (assembler_type) {
        process_arguments(fn_004bdd80, 0);
        fn_004bd970();
    }
}

MachineAsmInstruction *fn_00572410(MachineInt64 alignment)
{
    int size = alignment.lo;
    MachineAsmInstruction *instruction = galloc(22);
    memclrw(instruction, 22);
    if (getbit(size) < 2) { PPCError_Error(0x7e, size); size = 4; }
    if (size > (1 << asmFrameAlignmentLog)) {
        PPCError_Warning(0x7f, size, 1 << asmFrameAlignmentLog, 1 << asmFrameAlignmentLog);
        size = 1 << asmFrameAlignmentLog;
    }
    instruction->opcode = 12;
    instruction->specialFlags = 1;
    instruction->operandCount = 1;
    instruction->operands[0].kind = 1;
    instruction->operands[0].data.integer.hi = size < 0 ? -1 : 0;
    instruction->operands[0].data.integer.lo = size;
    return instruction;
}

int InlineAsm_OpcodeSize(MachineAsmInstruction *instruction)
{
    MachineAsmOpcode *descriptor = &inlineAsmOpcodes[instruction->opcode];
    int opcode = instruction->opcode;
    if (descriptor->flags & 6) {
        switch (opcode) {
            case 0x15: case 0x16: case 0x17: case 0x18:
            case 0x28: case 0x29: case 0x2a: case 0x2b: return 1;
            case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
            case 0x20: case 0x21: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30: return 2;
            case 0x22: case 0x23: case 0x24: case 0x25: case 0x26:
            case 0x31: case 0x32: case 0x33: case 0x34: case 0x35:
            case 0x8e: case 0x8f: case 0x90: case 0x91: case 0x96: case 0x97: case 0x98: case 0x99:
            case 0xba: case 0xbd: case 0xc0: case 0xc1: case 0xc2: case 0xdb: case 0x1e2: return 4;
            case 0x27: case 0x36:
                if (instruction->operands[0].kind == 2 && !instruction->operands[0].data.reference.object)
                    return (32 - instruction->operands[0].data.reference.value) * 4;
                return 128;
            case 0x92: case 0x93: case 0x94: case 0x95: case 0x9a: case 0x9b: case 0x9c: case 0x9d: return 8;
            case 0xbb: case 0xbe: return instruction->operands[2].data.integer.lo;
            case 0xbc: case 0xbf: return 128;
            case 0xf4: case 0xfb: return 1;
            case 0xf5: case 0xfc: return 2;
            case 0xf6: case 0xfd: return 4;
            case 0xf7: case 0xf8: case 0xf9: case 0xfa: case 0xfe: case 0xff: return 16;
            default: CError_Internal(inlineAsmFilename, 0x12dd);
        }
    } else {
        if (descriptor->flags2 & 0x80000000) return 4;
        if (descriptor->flags2 & 0x40000000) return 8;
        if (descriptor->flags2 & 0x20000000) return 16;
        if (descriptor->flags & 0x100) {
            switch (opcode) {
                case 0xd3: case 0xd4: case 0xd5: return 4;
                default: CError_Internal(inlineAsmFilename, 0x12ee);
            }
        }
    }
    CError_Internal(inlineAsmFilename, 0x12f1);
    return 0;
}

void CodeGen_GetAsmEffects(MachineStatement *statement, MachineAsmEffects *out)
{
    MachineAsmInstruction *instruction = statement->instruction;
    MachineAsmOpcode *descriptor = &inlineAsmOpcodes[instruction->opcode];
    MachineAsmOperand *operand;
    void *info;
    int i;
    out->operandCount = 0;
    out->labelCount = 0;
    out->writesMemory = 0;
    out->readsMemory = 0;
    out->controlFlow = 0;
    out->branchWithLink = 0;
    out->barrier = 0;
    out->noFallthrough = 0;
    if (descriptor->flags2 & 0x1000000) {
        if (instruction->branchFlags & 8) out->branchWithLink = 1;
        else if (descriptor->flags & 12) out->controlFlow = 1;
        if (instruction->opcode == 0) {
            if (instruction->operands[0].kind == 1) out->barrier = 1;
            out->noFallthrough = 1;
        }
    }
    if (descriptor->flags & 0x100) out->barrier = 1;
    if (instruction->opcode == 2 && (instruction->branchFlags & 8)) out->branchWithLink = 1;
    for (i = 0, operand = instruction->operands; i < instruction->operandCount; i++, operand++) {
        switch (operand->kind) {
            case 0: case 1: break;
            case 2:
                if (operand->data.reference.object) {
                    info = Registers_GetVarInfo(operand->data.reference.object);
                    if (info) *((unsigned char *)info + 14) |= 0x80;
                    if (operand->flags & 1) {
                        if (Registers_ClassForType(operand->data.reference.object->type) == -2)
                            CError_Internal(inlineAsmFilename, 0x1355);
                        else {
                            out->operands[out->operandCount].kind = 0;
                            out->operands[out->operandCount].object = operand->data.reference.object;
                            out->operands[out->operandCount].offset = 0;
                            out->operands[out->operandCount].size = operand->data.reference.object->type->size;
                            out->operandCount++;
                        }
                    }
                }
                break;
            case 3: case 4:
                if (operand->data.reference.object) {
                    if (descriptor->flags & 2) {
                        out->operands[out->operandCount].kind = 0;
                        out->operands[out->operandCount].object = operand->data.reference.object;
                        out->operands[out->operandCount].offset = operand->data.reference.value;
                        out->operands[out->operandCount].size = InlineAsm_OpcodeSize(instruction);
                        out->operandCount++;
                    } else if (!(descriptor->flags & 9)) {
                        out->operands[out->operandCount].kind = 3;
                        out->operands[out->operandCount].object = operand->data.reference.object;
                        out->operands[out->operandCount].offset = operand->data.reference.value;
                        out->operands[out->operandCount].size = InlineAsm_OpcodeSize(instruction);
                        out->operandCount++;
                    }
                }
                break;
            case 5:
                out->labels[out->labelCount++] = (void *)operand->data.reference.value;
                break;
            case 6:
                out->labels[out->labelCount++] = (void *)operand->data.reference.value;
                out->labels[out->labelCount++] = operand->data.reference.object;
                out->controlFlow = 1;
                break;
            default: CError_Internal(inlineAsmFilename, 0x1379);
        }
        if ((unsigned int)out->operandCount > 16) CError_Internal(inlineAsmFilename, 0x137c);
        if ((unsigned int)out->labelCount > 16) CError_Internal(inlineAsmFilename, 0x137f);
    }
    for (i = 0, operand = instruction->operands; i < instruction->operandCount; i++, operand++) {
        switch (operand->kind) {
            case 2:
                if (operand->data.reference.object) {
                    info = Registers_GetVarInfo(operand->data.reference.object);
                    if (info) *((unsigned char *)info + 14) |= 0x80;
                    if (operand->flags & 2) {
                        if (Registers_ClassForType(operand->data.reference.object->type) == -2)
                            CError_Internal(inlineAsmFilename, 0x1396);
                        else {
                            out->operands[out->operandCount].kind = 1;
                            out->operands[out->operandCount].object = operand->data.reference.object;
                            out->operands[out->operandCount].offset = 0;
                            out->operands[out->operandCount].size = operand->data.reference.object->type->size;
                            out->operandCount++;
                        }
                    }
                }
                break;
            case 3: case 4:
                if (operand->data.reference.object && (descriptor->flags & 4)) {
                    out->operands[out->operandCount].kind = 1;
                    out->operands[out->operandCount].object = operand->data.reference.object;
                    out->operands[out->operandCount].offset = operand->data.reference.value;
                    out->operands[out->operandCount].size = InlineAsm_OpcodeSize(instruction);
                    out->operandCount++;
                }
                break;
        }
        if ((unsigned int)out->operandCount > 16) CError_Internal(inlineAsmFilename, 0x13a9);
    }
    if (!out->operandCount) {
        if (descriptor->flags & 2) out->readsMemory = 1;
    }
    if (!out->operandCount && (descriptor->flags & 4)) out->writesMemory = 1;
    if ((descriptor->flags & 9) && !out->labelCount) out->controlFlow = 1;
}

int fn_00575330(void)
{
    int value = InlineAsm_ExpressionPPC(1);
    if (value < 0 || value > 31) CError_Error(0x27aa);
    return value;
}

 #pragma dont_inline on
int InlineAsm_ConstantExpressionPPC(int minimum, int maximum)
{
    int value = InlineAsm_ExpressionPPC(0);
    if (value < minimum || value > maximum) CError_Error(0x27aa);
    if (value >= 0x8000 && maximum == 0xffff) value = (short)value;
    return value;
}

int fn_005755f0(MachineAsmOperand *operand, int minimum, int maximum)
{
    int value;
    MachineInt64 integer;
    if (InlineAsm_gccmode && asmToken == '%') {
        CError_Error(0x27a0);
        return 0;
    }
    value = InlineAsm_ExpressionPPC(0);
    if (value < minimum || value > maximum) CError_Error(0x27aa);
    if (value >= 0x8000 && maximum == 0xffff) value = (short)value;
    operand->kind = 1;
    integer.lo = value;
    integer.hi = value < 0 ? -1 : 0;
    operand->data.integer = integer;
    return value;
}

#pragma dont_inline reset
void fn_00575690(MachineAsmOperand *operand, int minimum, int maximum)
{
    int value;
    MachineInt64 integer;
    void *argument;
    if (InlineAsm_gccmode && asmToken == '%') {
        asmToken = fn_0055ebc0();
        argument = fn_005a3730();
        if (!((*((unsigned char *)argument + 0x1c9) >> 1) & 1)) CError_Error(0x27a0);
        value = *(int *)((char *)argument + 0x1b0);
    } else value = InlineAsm_ExpressionPPC(0);
    if (value < minimum || value > maximum) CError_Error(0x27aa);
    if (value >= 0x8000 && maximum == 0xffff && minimum < 0) value = (short)value;
    operand->kind = 1;
    integer.lo = value;
    integer.hi = value < 0 ? -1 : 0;
    operand->data.integer = integer;
}

static char asmOpMul[] = "*", asmOpDiv[] = "/", asmOpMod[] = "%";
static char asmOpAdd[] = "+", asmOpSub[] = "-", asmOpShl[] = "<<", asmOpShr[] = ">>";
static char asmOpLt[] = "<", asmOpGt[] = ">", asmOpGe[] = ">=", asmOpLe[] = "<=";
static char asmOpEq[] = "==", asmOpNe[] = "!=", asmOpAnd[] = "&", asmOpXor[] = "^", asmOpOr[] = "|";
static char asmOpLAnd[] = "&&", asmOpLOr[] = "||", asmOpUnknown[] = "???";

void fn_005771a0(char *leftName, char *rightName, short operation)
{
    char *name;
    switch (operation) {
        case '*': name = asmOpMul; break;
        case '/': name = asmOpDiv; break;
        case '%': name = asmOpMod; break;
        case '+': name = asmOpAdd; break;
        case '-': name = asmOpSub; break;
        case 0x17a: name = asmOpShl; break;
        case 0x17b: name = asmOpShr; break;
        case '<': name = asmOpLt; break;
        case '>': name = asmOpGt; break;
        case 0x178: name = asmOpGe; break;
        case 0x179: name = asmOpLe; break;
        case 0x176: name = asmOpEq; break;
        case 0x177: name = asmOpNe; break;
        case '&': name = asmOpAnd; break;
        case '^': name = asmOpXor; break;
        case '|': name = asmOpOr; break;
        case 0x175: name = asmOpLAnd; break;
        case 0x174: name = asmOpLOr; break;
        default: name = asmOpUnknown;
    }
    if (!rightName) PPCError_Error(0x14, name, leftName + 10);
    else if (!leftName) PPCError_Error(0x15, name, rightName + 10);
    else PPCError_Error(0x13, leftName + 10, name, rightName + 10);
}

void fn_00575820(MachineAsmExpression *left, short op, MachineAsmExpression *right)
{
    unsigned char kind;
    MachineLabel *label;
    
    MachineInt64 result;

    result = CMach_CalcIntDiadic(&asmExpressionIntegerType, left->value, op, right->value);
    if (left->object != NULL) {
        if (right->label != NULL) {
            PPCError_Error(0x19, left->object->name + 10, right->label->name + 10);
        }
        if (right->object != NULL) {
            if (left->secondObject != NULL) {
                PPCError_Error(0x16, left->object->name + 10, left->secondObject->name + 10,
                                     right->object->name + 10);
            } else if (right->secondObject != NULL) {
                PPCError_Error(0x16, left->object->name + 10, right->object->name + 10,
                                     right->secondObject->name + 10);
            } else if (op == '-') {
                left->value = result;
                left->secondObject = right->object;
            } else {
                fn_005771a0(left->object->name, right->object->name, op);
            }
        } else if (op == '-' || op == '+') {
            left->value = result;
        } else {
            fn_005771a0(left->object->name, NULL, op);
        }
    } else if (right->object != NULL) {
        if (right->label != NULL) {
            PPCError_Error(0x19, right->object->name + 10, right->label->name + 10);
        }
        if (op == '+') {
            left->object = right->object;
            left->secondObject = right->secondObject;
            left->value = result;
        } else {
            fn_005771a0(NULL, right->object->name, op);
        }
    } else if (left->label != NULL) {
        if (left->object != NULL) {
            PPCError_Error(0x19, left->label->name + 10, left->object->name + 10);
        }
        if ((label = right->label) != NULL) {
            if (left->secondLabel != NULL) {
                PPCError_Error(0x16, left->label->name + 10, left->secondLabel->name + 10, label->name + 10);
            } else if (right->secondLabel != NULL) {
                PPCError_Error(0x16, left->label->name + 10, label->name + 10, right->secondLabel->name + 10);
            } else if (op == '-') {
                left->value = result;
                left->secondLabel = right->label;
            } else {
                fn_005771a0(left->label->name, label->name, op);
            }
        } else if (op == '+' || op == '-') {
            left->value = result;
        } else {
            fn_005771a0(NULL, left->label->name, op);
        }
    } else if (right->label != NULL) {
        if (op == '+') {
            left->label = right->label;
            left->secondLabel = right->secondLabel;
            left->value = result;
        } else {
            fn_005771a0(NULL, right->label->name, op);
        }
    } else {
        left->value = result;
    }
    left->flags |= right->flags;
    if (left->type == 5) {
        if (right->type != 5) {
            left->type = ((volatile MachineAsmExpression *)right)->type;
        }
    } else {
        kind = right->type;
        if (kind != 5 && kind != left->type)
            PPCError_Error(0x1b);
    }
}

void fn_00575760(MachineAsmExpression *result, int parseMode)
{
    short token;
    short nextPrecedence;
    short precedence;
    MachineAsmExpression operand;
    while (1) {
        token = asmToken;
        asmToken = fn_0055ebc0();
        fn_00575b60(&operand, parseMode);
        nextPrecedence = fn_00456110(asmToken);
        if (nextPrecedence == 0) {
            fn_00575820(result, token, &operand);
            return;
        }
        precedence = fn_00456110(token);
        if (precedence >= nextPrecedence) {
            fn_00575820(result, token, &operand);
            continue;
        }
        fn_00575760(&operand, parseMode);
        fn_00575820(result, token, &operand);
        if (fn_00456110(asmToken) == 0)
            return;
    }
}

void fn_005754f0(MachineAsmExpression *expression, int parseMode)
{
    fn_00575b60(expression, parseMode);
    if (fn_00456110(asmToken)) fn_00575760(expression, parseMode);
    if (fn_00456110(asmToken)) fn_00575760(expression, parseMode);
    if (expression->type == 5 && asmToken == -3) {
        if (!strcmp(asmIdentifier + 10, "@l")) expression->type = 6;
        else if (!strcmp(asmIdentifier + 10, "@ha")) expression->type = 8;
        else if (!strcmp(asmIdentifier + 10, "@h")) expression->type = 7;
        else { PPCError_Error(0x87); return; }
        asmToken = fn_0055ebc0();
    }
}

int InlineAsm_ExpressionPPC(int mode)
{
    MachineAsmExpression expression;
    fn_005754f0(&expression, mode);
    if (expression.object || expression.objectLabel || expression.label) {
        if (expression.object) PPCError_Error(0x17, expression.object->name + 10);
        else if (expression.objectLabel) PPCError_Error(0x17, expression.objectLabel->name + 10);
        else if (expression.label) PPCError_Error(0x43, expression.label->name + 10);
        return 0;
    }
    switch (expression.type) {
        case 8: return (short)((expression.value.lo >> 16) + ((expression.value.lo >> 15) & 1));
        case 7: return (short)(expression.value.lo >> 16);
        case 6: return (short)expression.value.lo;
        default: return expression.value.lo;
    }
}

static char asmDirectiveMachine[] = "machine";
static char asmDirectiveReserved[] = "warn_def_reserved_reg";
static char asmDirectiveVolatile[] = "volatile";
static char asmDirectiveNonvolatile[] = "nonvolatile";
static char asmDirectiveScheduling[] = "scheduling";
static char asmDirectiveAlign[] = "align";
static char asmDirectiveEntry[] = "entry";
static char asmDirectiveFralloc[] = "fralloc";
static char asmDirectiveNofralloc[] = "nofralloc";
static char asmDirectiveFrfree[] = "frfree";
static char asmDirectiveSmclass[] = "smclass";

int InlineAsm_IsDirective(unsigned char mode)
{
    int result = 0;
    char *text;
    if (asmToken == '.') asmToken = fn_0055ebc0();
    if (asmToken == -3 || asmToken == 0x124) {
    text = asmIdentifier + 10;
    if (!memcmp(text, asmDirectiveMachine, 8)) result = 5;
    else if (!memcmp(text, asmDirectiveReserved, 22)) result = 6;
    else if (!memcmp(text, asmDirectiveVolatile, 9)) result = 7;
    else if (!memcmp(text, asmDirectiveNonvolatile, 12)) result = 8;
    else if (!memcmp(text, asmDirectiveScheduling, 11)) result = 9;
    else if (!memcmp(text, asmDirectiveAlign, 6)) result = 12;
    else if (mode == 1) {
        if (!memcmp(text, asmDirectiveEntry, 6)) result = 1;
        else if (!memcmp(text, asmDirectiveFralloc, 8)) result = 2;
        else if (!memcmp(text, asmDirectiveNofralloc, 10)) result = 3;
        else if (!memcmp(text, asmDirectiveFrfree, 7)) result = 4;
        else if (!memcmp(text, asmDirectiveSmclass, 8)) result = 10;
        else result = 0;
    }
    }
    return result;
}

void InlineAsm_ScanAssemblyDirective(void)
{
    int directive = InlineAsm_IsDirective(assembler_type);
    if (directive) InlineAsm_ProcessDirective(directive);
    else PPCError_Error(0x86);
}

void InlineAsm_CreateEntryPoint(char *name, unsigned char global)
{
    MachineAsmLookup lookup;
    MachineObject *object;
    MachineStatement *statement;
    MachineAsmInstruction *instruction;
    if (fn_0055e9a0(name, &lookup) && (object = lookup.object)) {
        if (object->kind != 3 || object->flags & 4)
            CError_Error(0x278a, name + 10);
        object->flags |= 4;
        object->storage = global ? 0x102 : 0x103;
        if (object->storage == 0x103 && asmCurrentObject->storage == 0x102 &&
            !(asmCurrentObject->flags & 8)) {
            asmCurrentObject->flags |= 8;
            CFunc_SetStatementSourceRef();
            statement = CFunc_AppendStatement(0x10);
            statement->instruction = 0;
            instruction = galloc(36);
            memclrw(instruction, 36);
            instruction->opcode = 1;
            instruction->specialFlags = 1;
            instruction->operandCount = 2;
            statement->instruction = instruction;
            statement->instruction->operands[0].kind = 3;
            statement->instruction->operands[0].data.reference.object = object;
            statement->instruction->operands[0].data.reference.value = 0;
        } else {
            CFunc_SetStatementSourceRef();
            statement = CFunc_AppendStatement(0x10);
            statement->instruction = 0;
            instruction = galloc(22);
            memclrw(instruction, 22);
            instruction->opcode = 1;
            instruction->specialFlags = 1;
            instruction->operandCount = 1;
            statement->instruction = instruction;
            statement->instruction->operands[0].kind = 3;
            statement->instruction->operands[0].data.reference.object = object;
            statement->instruction->operands[0].data.reference.value = 0;
        }
    } else CError_Error(0x279c, name + 10);
}

MachineObject *fn_005751c0(void)
{
    MachineAsmLookup lookup;
    MachineObject *object;
    MachineType *type, *base;
    void *info;
    int isregister;
    if (asmToken != -3) return 0;
    fn_0055e9a0(asmIdentifier, &lookup);
    object = lookup.object;
    if (object) {
    if (object->kind == 1) {
    if (object->kind == 1) {
        info = Registers_GetVarInfo(object);
        if (info && !((unsigned char *)info)[8]) isregister = 1;
        else isregister = 0;
    } else {
        fn_0057a740(object);
        isregister = 1;
    }
    if (!isregister) return 0;
    type = object->type;
    if (type->kind != 12 && type->kind != 13) return 0;
    base = *(MachineType **)((char *)type + 6);
    if (base->kind != 5 && base->kind != 6) return 0;
    return object;
    }
    }
    return 0;
}

MachineAsmOperand *fn_00574b70(MachineAsmOperand *operand, MachineAsmInstruction *instruction,
                              int flags)
{
    MachineInt64 integer;
    int value = InlineAsm_ConstantExpressionPPC(-2048, 2047);
    if (asmToken != '(') CError_Error(0x2782);
    else {
        asmToken = fn_0055ebc0();
        fn_00574640(operand, 4, -1, flags);
        if (operand->data.reference.object || operand->data.reference.value) operand->flags = flags;
        else operand->flags = 0;
        operand++;
        instruction->operandCount++;
        if (asmToken != ')') CError_Error(0x2783);
        asmToken = fn_0055ebc0();
    }
    operand->kind = 1;
    integer.hi = value < 0 ? -1 : 0;
    integer.lo = value;
    operand->data.integer = integer;
    return operand;
}

/* Mnemonic lookup records carry processor masks, unlike the opcode descriptors. */
#pragma pack(push, 2)
typedef struct MachineAsmMnemonic {
    char *name;
    unsigned int opcode;
    unsigned int unknown08;
    MachineInt64 processors;
    unsigned int flags;
} MachineAsmMnemonic;
#pragma pack(pop)

unsigned char fn_005715e0(MachineAsmMnemonic *mnemonic, MachineInt64 processors,
                          unsigned char *needsFPU)
{
    MachineInt64 available, common;
    if (needsFPU) *needsFPU = 0;
    if ((processors.hi == 0x1ffffff && !processors.lo) ||
        (processors.hi == 0x1ffffff && processors.lo == 0xff800000)) return 1;
    available = mnemonic->processors;
    if (!(available.hi & 0x1ffffff)) return 1;
    if (processors.hi == 0x1ffffff && !processors.lo) {
        common.hi = available.hi & processors.hi;
        common.lo = available.lo & processors.lo;
        if ((common.hi & 0x1ffffff) != (processors.hi & 0x1ffffff)) return 0;
    }
    common.hi = available.hi & processors.hi;
    common.lo = available.lo & processors.lo;
    if (!(common.hi & 0x1ffffff)) return 0;
    if ((available.lo & 0x10000000) && !(processors.lo & 0x10000000)) return 0;
    if ((available.lo & 0x08000000) && !(processors.lo & 0x08000000)) return 0;
    if ((available.lo & 0x02000000) && !(processors.lo & 0x02000000)) return 0;
    if ((available.lo & 0x04000000) && !(processors.lo & 0x04000000)) return 0;
    if ((available.lo & 0x01000000) && !(processors.lo & 0x01000000)) return 0;
    if ((available.lo & 0x40000000) && !(processors.lo & 0x40000000)) return 0;
    if ((available.lo & 0x20000000) && !(processors.lo & 0x20000000)) return 0;
    if ((available.lo & 0x00800000) && !(processors.lo & 0x00800000)) return 0;
    if ((available.lo & 0x80000000) && !asmHardwareFPU) {
        if (needsFPU) *needsFPU = 1;
        return 0;
    }
    if ((available.lo & 0x00100000) && !(processors.lo & 0x00100000)) return 0;
    if ((available.lo & 0x00400000) && !(processors.lo & 0x00400000)) return 0;
    if ((available.lo & 0x00200000) && !(processors.lo & 0x00200000)) return 0;
    return 1;
}

extern unsigned char asmHasFrame, asmHasNoFrame, asmHasFreeFrame;
extern unsigned char asmNeedsFrame, asmHasExplicitNoFrame;
extern int asmFrameSize;
extern MachineInt64 asmTokenInteger;
extern short fn_00449c80(unsigned int);
extern short GetProcessorIndexFromName(const char *);
extern void *lalloc(int);
static char asmMachineAll[] = "all", asmMachineGeneric[] = "generic";
static char asmMachine403GA[] = "PPC403GA", asmMachine403GB[] = "PPC403GB";
static char asmMachine403GC[] = "PPC403GC", asmMachine403GCX[] = "PPC403GCX";
static char asmMachineAltivec[] = "altivec", asmMachineOn[] = "on", asmMachineOff[] = "off";

void InlineAsm_ProcessDirective(int directive)
{
    MachineStatement *statement;
    MachineAsmInstruction *instruction;
    int size;
    short processor;
    unsigned char global;
    char *text;
    switch (directive) {
        case 1:
            global = 0;
            asmToken = fn_0055ebc0();
            if (asmToken == 0x102) {
                global = 1;
                asmToken = fn_0055ebc0();
            } else if (asmToken == 0x103) asmToken = fn_0055ebc0();
            if (asmToken != -3) CError_Error(0x277b);
            InlineAsm_CreateEntryPoint(asmIdentifier, global);
            asmToken = fn_0055ebc0();
            break;
        case 2:
            if (asmInstructionCount) CError_Error(0x27b6);
            if (asmHasFrame) CError_Error(0x27b5);
            if (asmHasNoFrame || asmHasFreeFrame) CError_Error(0x27b6);
            asmToken = fn_0055ebc0();
            if (asmToken != -7 && asmToken != ';')
                asmFrameSize = InlineAsm_ConstantExpressionPPC(32, 0x7ffe);
            size = asmFrameSize;
            CFunc_SetStatementSourceRef();
            statement = CFunc_AppendStatement(0x10);
            statement->instruction = 0;
            instruction = galloc(22);
            memclrw(instruction, 22);
            instruction->opcode = 2;
            instruction->specialFlags = 1;
            instruction->operandCount = 1;
            statement->instruction = instruction;
            statement->instruction->operands[0].kind = 1;
            statement->instruction->operands[0].data.integer.hi = size < 0 ? -1 : 0;
            statement->instruction->operands[0].data.integer.lo = size;
            asmNeedsFrame = 1;
            asmHasFrame = 1;
            break;
        case 3:
            if (asmHasFrame || asmHasNoFrame) CError_Error(0x27b5);
            if (asmHasFreeFrame) CError_Error(0x27b6);
            if (asmInstructionCount) CError_Error(0x27b6);
            asmToken = fn_0055ebc0();
            CFunc_SetStatementSourceRef();
            statement = CFunc_AppendStatement(0x10);
            statement->instruction = 0;
            instruction = galloc(8);
            memclrw(instruction, 8);
            instruction->opcode = 3;
            instruction->specialFlags = 1;
            instruction->operandCount = 0;
            statement->instruction = instruction;
            asmHasNoFrame = 1;
            asmHasExplicitNoFrame = 1;
            break;
        case 4:
            if (asmHasNoFrame || asmHasFreeFrame) CError_Error(0x27b6);
            asmHasFreeFrame = 1;
            CFunc_SetStatementSourceRef();
            statement = CFunc_AppendStatement(0x10);
            statement->instruction = 0;
            instruction = lalloc(8);
            memclrw(instruction, 8);
            instruction->opcode = 4;
            instruction->specialFlags = 1;
            statement->instruction = instruction;
            asmToken = fn_0055ebc0();
            break;
        case 5:
            asmToken = fn_0055ebc0();
            if (asmToken == -1) {
                processor = fn_00449c80(asmTokenInteger.lo);
                if (processor == 20) CError_Error(0x27a0);
                asmCPU = fn_00449290(processor);
            } else if (asmToken == -3) {
                text = asmIdentifier + 10;
                if (!memcmp(text, asmMachineAll, 4)) { asmCPU.hi = 0x1ffffff; asmCPU.lo = 0xff800000; }
                else if (!memcmp(text, asmMachineGeneric, 8)) { asmCPU.hi = 0x1ffffff; asmCPU.lo = 0; }
                else if (!memcmp(text, asmMachine403GA, 9)) { asmCPU.hi = 0x180; asmCPU.lo = 0x08000000; }
                else if (!memcmp(text, asmMachine403GB, 9)) { asmCPU.hi = 0x80; asmCPU.lo = 0x08000000; }
                else if (!memcmp(text, asmMachine403GC, 9)) { asmCPU.hi = 0x280; asmCPU.lo = 0x0c000000; }
                else if (!memcmp(text, asmMachine403GCX, 10)) { asmCPU.hi = 0x480; asmCPU.lo = 0x0c000000; }
                else if (!memcmp(text, asmMachineAltivec, 8)) { asmCPU.hi = 0x6000; asmCPU.lo = 0xdf800000; }
                else {
                    if (asmIdentifier[10] == 'P' && asmIdentifier[11] == 'P' && asmIdentifier[12] == 'C')
                        processor = GetProcessorIndexFromName(asmIdentifier + 13);
                    else processor = GetProcessorIndexFromName(text);
                    if (processor == 20) CError_Error(0x27a0);
                    asmCPU = fn_00449290(processor);
                }
            } else CError_Error(0x27a0);
            asmToken = fn_0055ebc0();
            break;
        case 6:
            asmToken = fn_0055ebc0();
            if (asmToken == -3) {
                if (!memcmp(asmIdentifier + 10, asmMachineOn, 3)) asmGlobalEnabled = 1;
                else if (!memcmp(asmIdentifier + 10, asmMachineOff, 4)) asmGlobalEnabled = 0;
                else CError_Error(0x27a0);
            } else CError_Error(0x27a0);
            asmToken = fn_0055ebc0();
            break;
        case 7:
            asmOptionSticky = 1;
            asmToken = fn_0055ebc0();
            break;
        case 8:
            asmOptionSticky = 0;
            asmToken = fn_0055ebc0();
            break;
        case 9:
            asmToken = fn_0055ebc0();
            if (asmToken == -3) {
                if (!memcmp(asmIdentifier + 10, asmMachineOn, 3)) asmOptionSticky = 0;
                else if (!memcmp(asmIdentifier + 10, asmMachineOff, 4)) asmOptionSticky = 1;
                else CError_Error(0x27a0);
            } else CError_Error(0x27a0);
            asmToken = fn_0055ebc0();
            break;
        case 12:
            asmToken = fn_0055ebc0();
            if (asmToken != -1) CError_Error(0x278c);
            CFunc_SetStatementSourceRef();
            statement = CFunc_AppendStatement(0x10);
            statement->instruction = 0;
            statement->instruction = fn_00572410(asmTokenInteger);
            asmToken = fn_0055ebc0();
            break;
        default:
            CError_Error(0x2815);
    }
}

extern short lookahead(void);
extern MachineAsmMnemonic *fn_0056ef00(const char *, MachineInt64);
extern MachineAsmInstruction *InlineAsm_ScanAssemblyOperands(MachineAsmMnemonic *);
static char asmMnemonicDot[] = ".";

void InlineAsm_ScanAssemblyInstruction(void)
{
    unsigned char hasPlus = 0, hasMinus = 0, hasDot = 0, needsFPU;
    unsigned char hasLink, hasAbsolute;
    int directive, overflow;
    MachineStatement *statement;
    MachineAsmMnemonic *mnemonic;
    MachineAsmOpcode *descriptor;
    MachineAsmInstruction *instruction;
    char name[30];
    directive = InlineAsm_IsDirective(assembler_type);
    if (directive) { InlineAsm_ProcessDirective(directive); return; }
    CFunc_SetStatementSourceRef();
    statement = CFunc_AppendStatement(0x10);
    statement->instruction = 0;
    strncpy(name, asmIdentifier + 10, 20);
    name[29] = 0;
    if (lookahead() == '.') {
        asmToken = fn_0055ebc0();
        hasDot = 1;
        strcat(name, asmMnemonicDot);
    }
    mnemonic = fn_0056ef00(name, asmCPU);
    if (!mnemonic) {
        MachineInt64 all;
        all.hi = 0x1ffffff; all.lo = 0xff800000;
        mnemonic = fn_0056ef00(name, all);
        if (!mnemonic) CError_Error(0x2815);
        else CError_Error(0x27a8);
    }
    descriptor = &inlineAsmOpcodes[mnemonic->opcode];
    overflow = 0;
    if ((descriptor->flags2 & 0x10000) && (mnemonic->flags & 0x400)) overflow = 1;
    hasAbsolute = (descriptor->flags2 & 0x10000000) != 0;
    if (hasAbsolute) hasAbsolute = (mnemonic->flags & 2) != 0;
    hasLink = (descriptor->flags2 & 0x1000000) != 0;
    if (hasLink) hasLink = (mnemonic->flags & 1) != 0;
    if (!fn_005715e0(mnemonic, asmCPU, &needsFPU)) {
        if (needsFPU) PPCError_Error(0x21);
        else CError_Error(0x27a8);
    }
    asmToken = fn_0055ebc0();
    if (asmToken == '+' || asmToken == '-') {
        if ((((mnemonic->flags >> 26) & 63) == 16 && ((mnemonic->flags >> 21) & 31) != 20) ||
            (((mnemonic->flags >> 26) & 63) == 19 && ((mnemonic->flags >> 1) & 1023) == 0x210 &&
             ((mnemonic->flags >> 21) & 31) != 20) ||
            (((mnemonic->flags >> 26) & 63) == 19 && ((mnemonic->flags >> 1) & 1023) == 0x10 &&
             ((mnemonic->flags >> 21) & 31) != 20)) {
            if (asmToken == '+') hasPlus = 1;
            else if (asmToken == '-') hasMinus = 1;
            asmToken = fn_0055ebc0();
        } else CError_Error(0x2788);
    }
    statement->instruction = InlineAsm_ScanAssemblyOperands(mnemonic);
    instruction = statement->instruction;
    if (descriptor->flags & 8) instruction->specialFlags |= 2;
    if (hasDot) instruction->branchFlags |= 1;
    if (overflow) instruction->branchFlags |= 2;
    if (hasAbsolute) instruction->branchFlags |= 4;
    if (hasLink) instruction->branchFlags |= 8;
    if (hasPlus) instruction->branchFlags |= 0x10;
    if (hasMinus) instruction->branchFlags |= 0x20;
    if (asmOptionSticky) instruction->branchFlags |= 0x40;
    asmInstructionCount++;
}

extern MachineObject *fn_00581920(MachineType *, void *);
extern unsigned char asmTokenFloatValue[];
extern char *CMangler_GetLinkName(MachineObject *);
extern void *fn_0055d190(void);
extern void *fn_0055eb30(char *);

void fn_00575280(MachineAsmOperand *operand, MachineAsmInstruction *instruction, MachineType *type)
{
    MachineObject *object = fn_00581920(type, asmTokenFloatValue);
    unsigned char *info;
    operand[0].kind = 2;
    *(short *)&operand[0].registerClass = 4;
    operand[0].data.reference.object = 0;
    operand[0].flags = 1;
    operand[0].data.reference.value = 0;
    operand[0].flags = 0;
    instruction->operandCount++;
    operand[1].kind = 3;
    operand[1].data.reference.object = object;
    if (object->kind == 1) {
        info = Registers_GetVarInfo(object);
        if (info && !(info[14] & 0x80)) info[8] = 1;
        else goto float_operand_error;
    } else if (fn_0057a740(object)) {
float_operand_error:
        PPCError_Error(0x9a, CMangler_GetLinkName(object) + 10);
    }
    operand[1].flags = 2;
    operand[1].data.reference.value = 0;
    asmToken = fn_0055ebc0();
}

void fn_005743c0(MachineAsmInstruction *instruction, MachineAsmOperand *operand,
                  unsigned char wide, unsigned char displacement, unsigned char special)
{
    MachineAsmLookup lookup;
    void *label;
    int value;
    if (asmToken == -100 || (asmToken == -1 && lookahead() == -3)) {
        label = fn_0055d190();
        if (label) { operand->kind = 5; operand->data.reference.value = (int)label; return; }
    }
    if (asmToken == -3) {
        if (!fn_0055e9a0(asmIdentifier, &lookup))
            *(void **)((char *)&lookup + 4) = fn_0055eb30(asmIdentifier);
        label = *(void **)((char *)&lookup + 4);
        if (label) { operand->kind = 5; operand->data.reference.value = (int)label; }
        else if (lookup.object && lookup.object->kind == 3) {
            if (special) instruction->specialFlags |= 2;
            operand->kind = 3;
            operand->data.reference.object = lookup.object;
            operand->data.reference.value = 0;
            if (wide) { operand->flags = 4; if (displacement) operand->flags = 9; }
            else { operand->flags = 2; if (displacement) operand->flags = 10; }
        } else CError_Error(0x27a0);
        asmToken = fn_0055ebc0();
    } else if (asmToken == '*') {
        if (assembler_type != 1) PPCError_Error(0x8f);
        if (displacement) { CError_Error(0x27a0); return; }
        asmToken = fn_0055ebc0();
        if (asmToken == '+') {
            asmToken = fn_0055ebc0();
            fn_00575690(operand, wide ? (int)0xfe000000 : -32768, wide ? 0x1ffffff : 65535);
        } else if (asmToken == '-') {
            asmToken = fn_0055ebc0();
            value = (int)(0U - (unsigned int)fn_005755f0(operand, wide ? (int)0xfe000001 : -32767, wide ? 0x2000000 : 65535));
            operand->data.integer.hi = value < 0 ? -1 : 0;
            operand->data.integer.lo = value;
        } else CError_Error(0x27a0);
    } else if (displacement)
        fn_00575690(operand, wide ? (int)0xfe000000 : -32768, wide ? 0x1ffffff : 65535);
    else CError_Error(0x27a0);
}

/* These macros expand the native repeated address-use and relocation operations. */
#define ASM_MARK_ADDRESS(o) do { \
    if ((o)->kind == 1) { \
        unsigned char *vi = Registers_GetVarInfo(o); \
        if (vi && !(vi[14] & 0x80)) vi[8] = 1; \
        else PPCError_Error(0x9a, CMangler_GetLinkName(o) + 10); \
    } else if (fn_0057a740(o)) PPCError_Error(0x9a, CMangler_GetLinkName(o) + 10); \
} while (0)
#define ASM_VALUE(e,v) do { \
    int av; \
    switch ((e).type) { \
        case 8: av = (short)(((e).value.lo >> 16) + (((e).value.lo >> 15) & 1)); break; \
        case 7: av = (short)((e).value.lo >> 16); break; \
        case 6: av = (short)(e).value.lo; break; \
        default: (v) = (e).value; av = 0; break; \
    } \
    if ((e).type >= 6 && (e).type <= 8) { (v).hi = av < 0 ? -1 : 0; (v).lo = av; } \
} while (0)
extern short fn_004c2b40(MachineObject *);

void fn_00573f60(MachineAsmInstruction *instruction, MachineAsmOperand *operand,
                 int minimum, int maximum, unsigned char negative)
{
    MachineAsmExpression expression;
    MachineInt64 value;
    MachineObject *object;
    int size;
    fn_005754f0(&expression, 0);
    object = expression.object;
    if (object && !expression.secondObject &&
        (expression.type == 5 || (expression.type == 3 && !object->kind)) && !object->kind &&
        ((object->type->kind == 1 && ((unsigned char *)object->type)[6] < 23) || object->type->kind == 4) &&
        (*(unsigned int *)((char *)object + 20) & 0x10000)) {
        if ((instruction->opcode >= 0x3f && instruction->opcode <= 0x42) ||
            (instruction->opcode >= 0x58 && instruction->opcode <= 0x59) ||
            (instruction->opcode >= 0x8a && instruction->opcode <= 0x8b) ||
            (instruction->opcode >= 0xda && instruction->opcode <= 0xdb)) {
            if (((instruction->opcode >= 0x3f && instruction->opcode <= 0x42) ||
                 (instruction->opcode >= 0x58 && instruction->opcode <= 0x59)) &&
                *(int *)((char *)instruction + 24) &&
                *(int *)((char *)instruction + 24) == fn_004c2b40(object)) { }
            else {
                size = (int)((unsigned int)*(int *)((char *)object + 68) + expression.value.lo);
                expression.type = 5;
                expression.flags = 0;
                expression.value.hi = size < 0 ? -1 : 0;
                expression.value.lo = size;
                expression.isLocal = 0;
                expression.objectLabel = expression.object = expression.secondObject = 0;
                expression.label = expression.secondLabel = 0;
            }
        }
    }
    if (expression.label) {
        if (expression.secondLabel) {
            operand->kind = 6;
            operand->negative = negative ? 1 : 0;
            operand->data.reference.value = (int)expression.label;
            operand->data.reference.object = (MachineObject *)expression.secondLabel;
            *(int *)&operand->flags = expression.value.lo;
        } else PPCError_Error(0x1a, expression.label->name + 10);
        return;
    }
    if (expression.object) {
        if (expression.secondObject) {
            PPCError_Error(0x18, expression.object->name + 10, expression.secondObject->name + 10);
            return;
        }
        if (instruction->opcode != 0xda && expression.type == 5) {
            if (expression.object) PPCError_Error(0x17, expression.object->name + 10);
            else if (expression.objectLabel) PPCError_Error(0x17, expression.objectLabel->name + 10);
            else if (expression.label) PPCError_Error(0x43, expression.label->name + 10);
            return;
        }
        if (expression.object->kind == 1) {
            operand->kind = 4;
            switch (expression.type) {
                case 6: operand->flags = 13; break;
                case 8: operand->flags = 12; break;
                default: operand->flags = 1;
            }
        } else {
            operand->kind = 3;
            if (expression.type == 5) expression.type = 2;
            operand->flags = expression.type;
        }
        ASM_MARK_ADDRESS(expression.object);
        operand->data.reference.object = expression.object;
        operand->data.reference.value = expression.value.lo;
        return;
    }
    ASM_VALUE(expression, value);
    size = value.lo;
    if (size < minimum || size > maximum) CError_Error(0x27aa);
    if (size >= 0x8000 && maximum == 65535) size = (short)size;
    operand->kind = 1;
    if (negative) size = (int)(0U - (unsigned int)size);
    operand->data.integer.hi = size < 0 ? -1 : 0;
    operand->data.integer.lo = size;
}

#pragma pack(push,2)
typedef struct MachineAsmRegister {
    char *name;
    signed char registerClass;
    unsigned char unknown05;
    int value;
    MachineObject *object;
} MachineAsmRegister;
#pragma pack(pop)
extern MachineAsmRegister *fn_005cbdd0(const char *);
extern void fn_0055c3d0(const char *, int);
static char asmZeroRegister[] = "r0";
#define ASM_MEMORY_BASE(operand,expression,flags) do { \
    if (asmToken == '(') { \
        MachineAsmRegister *ar; \
        asmToken = fn_0055ebc0(); \
        if (asmToken == -1 && !asmTokenInteger.hi && !asmTokenInteger.lo) { \
            ar = fn_005cbdd0(asmZeroRegister); \
            if (ar) { \
                (operand)->kind = 2; *(short *)&(operand)->registerClass = 4; \
                (operand)->data.reference.object = ar->object; (operand)->data.reference.value = ar->value; \
                (operand)->flags = 0; \
            } else fn_0055c3d0(asmZeroRegister, 4); \
            asmToken = fn_0055ebc0(); \
        } else fn_00574640(operand, 4, -1, flags); \
        if (asmToken != ')') CError_Error(0x2783); \
        asmToken = fn_0055ebc0(); \
    } else { \
        (operand)->kind = 2; *(short *)&(operand)->registerClass = 4; \
        (operand)->data.reference.object = (expression).objectLabel; \
        (operand)->data.reference.value = (expression).isLocal; \
    } \
    (operand)->flags = ((operand)->data.reference.object || (operand)->data.reference.value) ? (flags) : 0; \
} while (0)

void fn_00574c40(MachineAsmOperand *operand, MachineAsmInstruction *instruction,
                 unsigned char memory, int flags)
{
    MachineAsmExpression expression;
    MachineInt64 value;
    fn_005754f0(&expression, 0);
    if (expression.objectLabel) {
        if (!memory) CError_Error(0x27ab);
        if (expression.object) PPCError_Error(0x17, expression.object);
        operand->kind = 2;
        *(short *)&operand->registerClass = 4;
        operand->data.reference.object = expression.objectLabel;
        operand->data.reference.value = 0;
        operand->flags = flags;
        instruction->operandCount++;
        operand[1].kind = 1;
        switch (expression.type) {
            case 5: expression.type = 2;
            case 2: case 6: case 7: case 8:
                ASM_VALUE(expression, value);
                operand[1].data.integer = value;
                break;
            default: CError_Error(0x27ab);
        }
        expression.objectLabel->flags |= 1;
        return;
    }
    if (expression.object) {
        if (expression.secondObject)
            PPCError_Error(0x18, expression.object->name + 10, expression.secondObject->name + 10);
        if (memory) {
            ASM_MEMORY_BASE(operand, expression, flags);
            operand++;
            instruction->operandCount++;
        }
        if (expression.object->kind == 1) { operand->kind = 4; operand->flags = 1; }
        else {
            operand->kind = 3;
            if (expression.type == 5) expression.type = 2;
            operand->flags = expression.type;
        }
        ASM_MARK_ADDRESS(expression.object);
        operand->data.reference.object = expression.object;
        operand->data.reference.value = expression.value.lo;
        expression.object->flags |= 1;
        return;
    }
    if (memory) {
        ASM_MEMORY_BASE(operand, expression, flags);
        operand++;
        instruction->operandCount++;
    }
    if (expression.label) {
        if (expression.secondLabel) {
            operand->kind = 6;
            operand->negative = 0;
            operand->data.reference.value = (int)expression.label;
            operand->data.reference.object = (MachineObject *)expression.secondLabel;
            *(int *)&operand->flags = expression.value.lo;
        } else PPCError_Error(0x1a, expression.label->name + 10);
    } else {
        operand->kind = 1;
        ASM_VALUE(expression, value);
        operand->data.integer = value;
    }
}

extern MachineAsmRegister *fn_005cc070(char *);
extern void fn_0055c3a0(const char *, int, int);
extern void fn_005ed3d0(int, ...);
extern void *asmRegisterClassNames[];
static char asmLowWord[] = "@loword", asmHighWord[] = "@hiword";
extern int fn_0055dfb0(MachineType *), fn_0055e150(MachineType *), fn_0055e4f0(MachineType *);
extern int fn_005162d0(void);
extern unsigned char is_safe_const(MachineObject *, int);
extern void PPC_EABI_SetSection(MachineObject *, int, unsigned char);
extern unsigned char is_16bitdata(MachineObject *);
extern void createIndirect(MachineObject *, int, int);
extern MachineInt64 fn_004da330(MachineInt64), fn_004da3d0(MachineInt64), fn_004da3f0(MachineInt64);
extern short asmLowWordOffset, asmHighWordOffset;
#pragma pack(push,2)
typedef struct MachineAsmResolved {
    unsigned int unknown00;
    MachineLabel *label;
    MachineObject *object;
    MachineType *type;
    unsigned int unknown10;
    int value;
    unsigned char isRegister, unknown19[3];
} MachineAsmResolved;
#pragma pack(pop)
extern unsigned char fn_0055e9c0(char *, MachineAsmResolved *, int);
#pragma pack(push,2)
typedef struct MachinePCodeOperand {
    unsigned char kind, registerClass;
    union {
        int immediate;
        void *pointer;
        struct { unsigned short flags; short reg; MachineObject *object; unsigned char tail[4]; } reg;
        struct { unsigned short offset; void *first, *second; } difference;
        unsigned char bytes[12];
    } data;
} MachinePCodeOperand;
typedef struct MachinePCodeInstruction {
    void *next, *previous, *block;
    unsigned int flags, flags2;
    unsigned char unknown14[8];
    void *memoryOperand, *source;
    int offset;
    short opcode, operandCount;
    MachinePCodeOperand operands[1];
} MachinePCodeInstruction;
#pragma pack(pop)
typedef char VerifyPCodeOperand[(sizeof(MachinePCodeOperand)==14)?1:-1];
typedef char VerifyPCodeOperands[(offsetof(MachinePCodeInstruction,operands)==44)?1:-1];
extern void *asmPCodeSource, *asmActiveStatement;
extern unsigned char asmExceptionRegisters, asmUsesSpecialRegister, asmUsesExtraRegister;
extern unsigned char asmReservedRegisters[][32];
extern int asmFirstVirtualRegister[];
extern short asmMappedSPR[4];
extern int fn_00595dd0(void);
extern int countexceptionactionregisters(void *);
extern void noteexceptionactionregisters(void *, MachinePCodeOperand *);
extern void *makepclabel(void);
extern void fn_00596090(MachinePCodeInstruction *);
extern void fn_0057a830(MachineObject *, short, short);
extern void retain_register(MachineObject *, signed char, short);
extern int fn_0058b4c0(MachinePCodeInstruction *);
extern void *fn_005a05d0(MachineObject *, int, int);
extern unsigned char is_volatile_object(MachineObject *);
extern void branch_record_volatiles(MachinePCodeOperand *, unsigned int *);
static unsigned int asmAllVolatileRegisters[5] = {-1,-1,-1,-1,-1};
extern void *asmCurrentBlock;
extern unsigned char asmPermitOptimization, asmInterruptHandler, asmInterruptCode;
extern unsigned char asmInterruptObserved, asmHasBlr, asmHasRfi, asmRfiOutsideHandler, asmRfiInsideHandler;
extern unsigned char asmWarnInterruptReturn, asmHasBranchWithLink;
extern void fn_0058b310(MachinePCodeInstruction *, int);
extern void fn_0058b210(MachinePCodeInstruction *, short);
extern void appendpcode(void *, MachinePCodeInstruction *);
extern unsigned char fn_004530f0(MachineObject *);
extern void setpcodeflags(MachineInt64);
extern void fn_005960e0(MachinePCodeInstruction *), fn_00595fc0(MachinePCodeInstruction *);
extern void pcaddedge(void *, void *, int), makepcblock(void), pclabelblock(void *,void *);
static char asmBlrMnemonic[] = "blr", asmRfiMnemonic[] = "rfi";
#define ASM_PCODE_FLAGS(a,b) do { MachineInt64 af;af.hi=(a);af.lo=(b);setpcodeflags(af); } while(0)
static char asmHa16[] = "ha16", asmHi16[] = "hi16", asmLo16[] = "lo16", asmCRPrefix[] = "cr";
#define ASM_CONST(e,n) do { \
    int ac = (n); \
    (e)->type = 5; (e)->flags = 0; \
    (e)->value.hi = ac < 0 ? -1 : 0; (e)->value.lo = ac; \
    (e)->isLocal = 0; (e)->objectLabel = 0; (e)->object = 0; (e)->secondObject = 0; \
    (e)->label = 0; (e)->secondLabel = 0; \
} while (0)
#define ASM_PREP_OBJECT(o) do { \
    unsigned char ac = is_safe_const(o,0); \
    PPC_EABI_SetSection(o,(o)->type->size,ac); \
    if ((o)->kind == 1) { \
        unsigned char *vi = Registers_GetVarInfo(o); \
        if (vi && (vi[14] & 2)) (o) = 0; \
    } else if ((o)->kind != 3 && (o)->kind != 4) { \
        if (!(o)->kind || is_16bitdata(o)) createIndirect(o,0,0); \
        else (o) = 0; \
    } \
} while(0)
#define ASM_REGISTER_OBJECT(obj,operand,regclass) do { \
    unsigned char *vi = Registers_GetVarInfo(obj); \
    MachineType *ty = (obj)->type; \
    if (vi[8] || ty->kind == 13 || ty->kind == 6 || ty->kind == 3 || \
        (ty->kind == 5 && (((signed char *)ty)[16] <= 3 || ((signed char *)ty)[16] >= 15)) || \
        (ty->kind == 11 && (*(MachineType **)((char *)ty + 6))->kind == 7)) { \
        fn_005ed3d0(9,(operand)->data.reference.object,asmRegisterClassNames[regclass]); return; \
    } \
    (obj)->flags |= 1; \
    if ((obj)->kind == 1) { \
        vi = Registers_GetVarInfo(obj); \
        if (vi && !vi[8]) vi[14] |= 0x80; \
        else PPCError_Error(0x99,CMangler_GetLinkName(obj)+10); \
    } else if (!fn_0057a740(obj)) PPCError_Error(0x99,CMangler_GetLinkName(obj)+10); \
} while(0)

void fn_00574640(MachineAsmOperand *operand, signed char registerClass, int fixedRegister, int flags)
{
    MachineAsmRegister *reg;
    MachineObject *object;
    MachineType *type;
    unsigned char *gcc;
    signed char objectClass;
    char *name;
    if (fixedRegister != -1) {
        operand->kind = 2;
        *(short *)&operand->registerClass = registerClass;
        operand->data.reference.object = 0;
        operand->data.reference.value = fixedRegister;
        operand->flags = flags;
        return;
    }
    reg = 0;
    if (asmToken == -3) {
        reg = fn_005cc070(asmIdentifier);
        if (reg && reg->registerClass == registerClass) {
            operand->kind = 2;
            *(short *)&operand->registerClass = registerClass;
            object = reg->object;
            operand->data.reference.object = object;
            operand->data.reference.value = reg->value;
            operand->flags = flags;
            if (object) { ASM_REGISTER_OBJECT(object,operand,registerClass); }
            goto identifier_done;
        }
    }
    if (registerClass == 1) {
        operand->kind = 2;
        *(short *)&operand->registerClass = 1;
        operand->data.reference.object = 0;
        operand->data.reference.value = InlineAsm_ConstantExpressionPPC(0,7);
        operand->flags = flags;
        return;
    }
    if (registerClass == 0) {
        operand->kind = 2;
        *(short *)&operand->registerClass = 0;
        operand->data.reference.object = 0;
        operand->data.reference.value = InlineAsm_ConstantExpressionPPC(0,1024);
        operand->flags = flags;
        return;
    }
    if (asmToken == '%' && InlineAsm_gccmode) {
        asmToken = fn_0055ebc0();
        gcc = fn_005a3730();
        if (!(gcc[0x1c8] & 4)) fn_005ed3d0(8);
        operand->kind = 2;
        *(short *)&operand->registerClass = registerClass;
        object = *(MachineObject **)(gcc + 0x1bc);
        operand->data.reference.object = object;
        operand->data.reference.value = 0;
        operand->flags = flags;
        if (object) {
            objectClass = Registers_ClassForType(object->type);
            if (objectClass != -2 && objectClass != registerClass)
                fn_0055c3a0(object->name + 10, objectClass, registerClass);
            ASM_REGISTER_OBJECT(object,operand,registerClass);
        }
        return;
    }
    if (reg && reg->registerClass != -2 && reg->registerClass != registerClass)
        fn_0055c3a0(asmIdentifier + 10,reg->registerClass,registerClass);
    else if (asmToken == -3) fn_0055c3d0(asmIdentifier + 10,registerClass);
    else fn_005ed3d0(8);
identifier_done:
    asmToken = fn_0055ebc0();
    object = operand->data.reference.object;
    if (registerClass != 4 || !object) return;
    type = object->type;
    if ((asmOptionFloat && type->kind == 2 && ((unsigned char *)type)[6] < 23 && type->size != 4) ||
        (type->kind == 1 && ((unsigned char *)type)[6] < 23 && type->size == 8) ||
        (type->kind == 4 && type->size == 8)) {
        name = object->name;
        if (!memcmp(asmIdentifier + 10,asmLowWord,8)) {
            asmToken = fn_0055ebc0();
        } else if (!memcmp(asmIdentifier + 10,asmHighWord,8)) {
            if (!object) PPCError_Error(0x45);
            operand->data.reference.value = -3;
            asmToken = fn_0055ebc0();
        } else PPCError_Error(0x1c,name+10,name+10,name+10);
    } else if (Registers_ClassForType(type) == -2)
        fn_005ed3d0(9,operand->data.reference.object,asmRegisterClassNames[registerClass]);
}

void fn_00575b60(MachineAsmExpression *expression, int mode)
{
    unsigned char relocation = 0, *gcc = 0;
    MachineObject *object;
    MachineAsmLookup lookup;
    MachineAsmResolved resolved;
    MachineAsmRegister *reg, *reg2;
    MachineAsmExpression offset;
    MachineInt64 value;
    int local, number, base;
    char registerName[4];
    switch (asmToken) {
        case -3:
            object = fn_005751c0();
            if (object) {
                asmToken = fn_0055ebc0();
                ASM_CONST(expression,fn_0055dfb0(*(MachineType **)((char *)object->type+6)));
                expression->objectLabel = object;
                return;
            }
            object = 0;
            if (asmToken == -3) {
                fn_0055e9a0(asmIdentifier,&lookup);
                object = lookup.object;
                if (object) { ASM_PREP_OBJECT(object); }
            }
            if (object) goto variable;
            if (fn_0055e9c0(asmIdentifier,&resolved,1)) {
                if (resolved.isRegister) {
                    asmToken = fn_0055ebc0();
                    ASM_CONST(expression,resolved.value);
                    return;
                }
                if (resolved.type && (resolved.type->kind == 5 || resolved.type->kind == 6)) {
                    asmToken = fn_0055ebc0();
                    if (asmToken != '.') CError_Error(0x2788);
                    if (asmInitializationFlag) { ASM_CONST(expression,fn_0055e150(resolved.type)); }
                    else { ASM_CONST(expression,fn_0055e4f0(resolved.type)); }
                    return;
                }
                if (resolved.object && resolved.object->kind == 2) {
                    asmToken = fn_0055ebc0();
                    ASM_CONST(expression,*(int *)((char *)resolved.object+64));
                    return;
                }
            } else if (mode) {
                if (asmToken == -3 && (reg = fn_005cc070(asmIdentifier)) && reg->registerClass == 1) {
                    number = 0;
                    if (asmToken == -3 && (reg = fn_005cc070(asmIdentifier)) && reg->registerClass == 1)
                        number = reg->value;
                    else fn_0055c3d0(asmIdentifier+10,1);
                    asmToken = fn_0055ebc0();
                    ASM_CONST(expression,number);
                    return;
                }
                if (asmToken == -3 && (reg = fn_005cc070(asmIdentifier)) && reg->registerClass == 6) {
                    number = 0;
                    if (asmToken == -3 && (reg = fn_005cc070(asmIdentifier)) && reg->registerClass == 6)
                        number = reg->value;
                    else fn_0055c3d0(asmIdentifier+10,6);
                    asmToken = fn_0055ebc0();
                    ASM_CONST(expression,number);
                    return;
                }
                if (strlen(asmIdentifier+10) == 6 && !strncmp(asmIdentifier+10,asmCRPrefix,2) && asmIdentifier[13] == '_') {
                    registerName[0] = asmIdentifier[10]; registerName[1] = asmIdentifier[11];
                    registerName[2] = asmIdentifier[12]; registerName[3] = 0;
                    reg = fn_005cbdd0(registerName);
                    if (reg && reg->registerClass == 1) {
                        base = reg->value * 4;
                        registerName[0] = asmIdentifier[14]; registerName[1] = asmIdentifier[15]; registerName[2] = 0;
                        reg2 = fn_005cbdd0(registerName);
                        if (reg2 && reg2->registerClass == 6) {
                            asmToken = fn_0055ebc0();
                            ASM_CONST(expression,base + reg2->value);
                            return;
                        }
                    }
                }
            }
            if (!memcmp(asmHa16,asmIdentifier+10,5)) relocation = 8;
            else if (!memcmp(asmHi16,asmIdentifier+10,5)) relocation = 7;
            else if (!memcmp(asmLo16,asmIdentifier+10,5)) relocation = 6;
            if (relocation) {
                asmToken = fn_0055ebc0();
                if (asmToken == '(') {
                    asmToken = fn_0055ebc0();
                    fn_00575b60(expression,mode);
                    expression->type = relocation;
                    if (asmToken != ')') CError_Error(0x2783);
                    asmToken = fn_0055ebc0();
                    if (!expression->object && !expression->objectLabel && !expression->label) {
                        ASM_VALUE((*expression),value);
                        expression->value = value;
                        expression->type = 5;
                    }
                    return;
                }
                CError_Error(0x2782);
                goto primary_zero;
            }
            if (!resolved.label) resolved.label = fn_0055eb30(asmIdentifier);
            ASM_CONST(expression,0);
            expression->flags |= 1;
            expression->label = resolved.label;
            asmToken = fn_0055ebc0();
            return;
        case -1:
            number = asmTokenInteger.lo;
            asmToken = fn_0055ebc0();
            ASM_CONST(expression,number);
            return;
        case 0x151:
            ASM_CONST(expression,fn_005162d0());
            return;
        case '+':
            asmToken = fn_0055ebc0();
            fn_00575b60(expression,mode);
            return;
        case '-': case '!': case '~':
            number = asmToken;
            asmToken = fn_0055ebc0();
            fn_00575b60(expression,mode);
            if (!expression->object && !expression->objectLabel && !expression->label) {
                if (number == '-') expression->value = fn_004da330(expression->value);
                else if (number == '!') expression->value = fn_004da3f0(expression->value);
                else expression->value = fn_004da3d0(expression->value);
            } else CError_Error(0x278c);
            return;
        case '(':
            asmToken = fn_0055ebc0();
            fn_005754f0(expression,mode);
            if (asmToken != ')') CError_Error(0x2783);
            asmToken = fn_0055ebc0();
            return;
        case '%':
            if (!InlineAsm_gccmode) break;
            asmToken = fn_0055ebc0();
            gcc = fn_005a3730();
            if (gcc[0x1c9] & 2) { ASM_CONST(expression,*(int *)(gcc+0x1b0)); return; }
            object = *(MachineObject **)(gcc+0x1bc);
            if (!object && !(gcc[0x1c8] & 2)) break;
            ASM_PREP_OBJECT(object);
            if (!object) break;
variable:
            ASM_CONST(expression,(gcc && (gcc[0x1c8] & 2)) ? *(int *)(gcc+0x1b8) : 0);
            expression->object = object;
            local = object->kind == 1;
            asmToken = fn_0055ebc0();
            if (asmToken == '.' || asmToken == '[') {
                ASM_CONST(&offset,fn_0055e150(object->type));
                fn_00575820(expression,'+',&offset);
            }
            if (asmToken == '+' || asmToken == '-') {
                number = asmToken;
                asmToken = fn_0055ebc0();
                fn_005754f0(&offset,mode);
                fn_00575820(expression,number,&offset);
            } else if (gcc || asmToken == -3) {
                if (!memcmp(asmIdentifier+10,asmLowWord,8)) {
                    asmToken = fn_0055ebc0();
                    if (asmLowWordOffset) {
                        ASM_CONST(&offset,asmLowWordOffset);
                        fn_00575820(expression,'+',&offset);
                    }
                } else if (!memcmp(asmIdentifier+10,asmHighWord,8)) {
                    asmToken = fn_0055ebc0();
                    if (asmHighWordOffset) {
                        ASM_CONST(&offset,asmHighWordOffset);
                        fn_00575820(expression,'+',&offset);
                    }
                }
            }
            expression->isLocal = local;
            return;
        default: break;
    }
    CError_Error(0x2788);
primary_zero:
    ASM_CONST(expression,0);
}

MachinePCodeInstruction *InlineAsm_TranslateIRtoPCodePPC(MachineAsmInstruction *instruction,
                                                        int argumentCount, unsigned char mode)
{
    MachineAsmOpcode *descriptor = &inlineAsmOpcodes[instruction->opcode];
    MachinePCodeInstruction *result;
    MachinePCodeOperand *out;
    MachineAsmOperand *operand;
    MachineObject *object;
    MachineType *type;
    unsigned char *info;
    unsigned int flags, volatileRegisters[5];
    int extra = 0, i, firstRegister = 0, count, size, reg = 0, low, high;
    if ((descriptor->flags2 & 0x20000) && !(descriptor->flags2 & 0x100000)) extra++;
    if (!(descriptor->flags2 & 0x80000) && (descriptor->flags2 & 0x10000)) extra++;
    if (argumentCount < instruction->operandCount) {
        if (argumentCount + extra >= instruction->operandCount) {
            extra -= instruction->operandCount - argumentCount;
            argumentCount = instruction->operandCount;
        } else CError_Internal(inlineAsmFilename,0xfa6);
    }
    if (!instruction->opcode && instruction->operands[0].kind == 1) instruction->branchFlags |= 0x40;
    if (instruction->specialFlags & 2) {
        count = argumentCount + fn_00595dd0();
        if (asmExceptionRegisters && asmActiveStatement && !assembler_type)
            count += countexceptionactionregisters(*(void **)((char *)asmActiveStatement+18));
        size = 44 + (count + extra)*14;
        result = lalloc(size);
        memset(result,0,size);
        result->operandCount = count;
    } else if (instruction->opcode == 0x36 || instruction->opcode == 0x27) {
        operand = instruction->operands;
        if (operand->data.reference.object) {
            info = Registers_GetVarInfo(operand->data.reference.object);
            firstRegister = (info && (info[14]&2)) ? *(short *)(info+16) : -1;
        } else firstRegister = operand->data.reference.value;
        count = 32-firstRegister+argumentCount;
        size = 44+count*14;
        result = lalloc(size); memset(result,0,size); result->operandCount = count;
    } else {
        if (argumentCount + extra < 6) extra = 6-argumentCount;
        size = 44+(argumentCount+extra)*14;
        result = lalloc(size); memset(result,0,size);
        if (instruction->operandCount <= argumentCount) result->operandCount = argumentCount;
    }
    result->opcode = instruction->opcode;
    result->flags = descriptor->flags;
    result->flags2 = descriptor->flags2;
    result->source = asmPCodeSource;
    out = result->operands;
    operand = instruction->operands;
    for (i=0;i<argumentCount+extra;i++,out++,operand++) {
        if (i >= instruction->operandCount) { out->kind = 8; continue; }
        switch (operand->kind) {
            case 0: out->kind = 8; break;
            case 1:
                out->kind = 2;
                out->data.immediate = operand->data.integer.lo;
                if (result->flags & 6) result->flags |= 0x20;
                break;
            case 2:
                object = operand->data.reference.object;
                reg = 0;
                if (object) {
                    info = Registers_GetVarInfo(object);
                    if (info[14]&2) {
                        info = Registers_GetVarInfo(object);
                        if (operand->data.reference.value == -3)
                            reg = (info && (info[14]&6)==6) ? *(short *)(info+18) : -1;
                        else reg = (info && (info[14]&2)) ? *(short *)(info+16) : -1;
                    } else {
                        info = Registers_GetVarInfo(object);
                        if (info[14]&0x80) PPCError_Error(0x49,object->name+10);
                        else fn_0055c3d0(object->name+10,(signed char)operand->registerClass);
                    }
                } else reg = operand->data.reference.value;
                out->kind = 0;
                out->registerClass = operand->registerClass;
                out->data.reg.reg = reg;
                out->data.reg.flags = operand->flags;
                if (operand->flags & 0x8000) asmUsesSpecialRegister = 1;
                if (operand->flags & 0x2000) asmUsesExtraRegister = 1;
                if (result->opcode==0x69 && (out->data.reg.flags&2) && out->registerClass==4 && !(out->data.reg.flags&1))
                    CError_Internal(inlineAsmFilename,0x1024);
                if (!out->registerClass) {
                    out->kind = 1;
                    for (reg=0;reg<4;reg++) if (out->data.reg.reg == asmMappedSPR[reg]) {
                        out->kind = 0; out->registerClass = 0; out->data.reg.reg = reg; break;
                    }
                    if ((result->opcode>=0x192 && result->opcode<=0x196) || result->opcode==0x198) {
                        if (out->data.reg.reg != 0x390) fn_00596090(result);
                    } else fn_00596090(result);
                } else if (out->registerClass == 6 || out->registerClass == 7) {
                    reg = out->data.reg.reg;
                    out->kind = 2;
                    out->data.immediate = reg;
                    break;
                }
                if ((operand->flags&2) && out->data.reg.reg < asmFirstVirtualRegister[(signed char)out->registerClass]) {
                    if (asmGlobalEnabled && out->data.reg.reg < asmFirstVirtualRegister[(signed char)out->registerClass] &&
                        asmReservedRegisters[(signed char)out->registerClass][out->data.reg.reg]==2 && !mode) {
                        PPCError_Warning(0x71,descriptor->mnemonic,out->data.reg.reg);
                        fn_00596090(result);
                    }
                    if (object && (((unsigned char *)Registers_GetVarInfo(object))[14]&4)) {
                        if (out->registerClass!=4) CError_Internal(inlineAsmFilename,0x105c);
                        info = Registers_GetVarInfo(object);
                        low = (info && (info[14]&2)) ? *(short *)(info+16) : -1;
                        info = Registers_GetVarInfo(object);
                        high = (info && (info[14]&6)==6) ? *(short *)(info+18) : -1;
                        fn_0057a830(object,low,high);
                    } else retain_register(object,(signed char)out->registerClass,out->data.reg.reg);
                }
                break;
            case 5:
                if (!*(void **)((char *)operand->data.reference.value+20))
                    *(void **)((char *)operand->data.reference.value+20)=makepclabel();
                out->kind=6;
                out->data.pointer=*(void **)((char *)operand->data.reference.value+20);
                break;
            case 3: case 4:
                out->kind=4;
                out->registerClass=(unsigned char)operand->flags;
                out->data.reg.object=operand->data.reference.object;
                out->data.immediate=operand->data.reference.value;
                if (result->flags&0x60006) {
                    result->memoryOperand=fn_005a05d0(out->data.reg.object,out->data.immediate,fn_0058b4c0(result));
                    object=out->data.reg.object;
                    if (is_volatile_object(object)) result->flags|=0x80;
                    type=object->type;
                    flags=(type->kind==12 || type->kind==13) ? *(unsigned int *)((char *)type+10) :
                        *(unsigned int *)((char *)object+20);
                    if (flags&1) result->flags|=0x40;
                }
                break;
            case 6:
                if (!*(void **)((char *)operand->data.reference.value+20))
                    *(void **)((char *)operand->data.reference.value+20)=makepclabel();
                if (!*(void **)((char *)operand->data.reference.object+20))
                    *(void **)((char *)operand->data.reference.object+20)=makepclabel();
                if (result->flags&6) result->flags|=0x20;
                out->kind=7;
                out->data.difference.first=*(void **)((char *)operand->data.reference.value+20);
                out->data.difference.second=*(void **)((char *)operand->data.reference.object+20);
                out->registerClass=operand->negative;
                out->data.difference.offset=operand->flags;
                break;
            default: CError_Internal(inlineAsmFilename,0x109f);
        }
    }
    if (instruction->opcode==0x36 || instruction->opcode==0x27)
        for (reg=firstRegister;reg<32;reg++,out++) {
            out->kind=0;out->registerClass=4;out->data.reg.reg=reg;
            out->data.reg.flags=instruction->opcode==0x27?2:1;
        }
    if (instruction->specialFlags&2) {
        for(i=0;i<5;i++) volatileRegisters[i]=asmAllVolatileRegisters[i];
        branch_record_volatiles(out,volatileRegisters);
        if (asmExceptionRegisters && asmActiveStatement && !assembler_type)
            noteexceptionactionregisters(*(void **)((char *)asmActiveStatement+18),out);
    }
    return result;
}

void InlineAsm_TranslateIRtoPCode(MachineStatement *statement)
{
    MachineAsmInstruction *instruction = statement->instruction;
    MachinePCodeInstruction *code;
    MachineAsmOperand *operand;
    void *label, *endLabel;
    int i, encoding;
    const char *mnemonic;
    code = InlineAsm_TranslateIRtoPCodePPC(instruction,inlineAsmOpcodes[instruction->opcode].operandCount,assembler_type);
    if (code->opcode == 0x42 && !code->operands[1].data.reg.reg) {
        code->operands[1] = code->operands[2];
        fn_0058b310(code,2);
        fn_0058b210(code,0x8a);
    }
    appendpcode(asmCurrentBlock,code);
    if (!(instruction->branchFlags & 0x40) && asmPermitOptimization) {
        for (i=0,operand=instruction->operands;(unsigned)i<(unsigned)instruction->operandCount;i++,operand++) {
            if (operand->kind==2 && operand->data.reference.object) {
                if (is_volatile_object(operand->data.reference.object)) { ASM_PCODE_FLAGS(0x80,0);break; }
                if ((code->flags&0x60006) && fn_004530f0(operand->data.reference.object)) {
                    ASM_PCODE_FLAGS(0x80,0);break;
                }
            }
        }
    } else { ASM_PCODE_FLAGS(0x100,0); }
    if (instruction->branchFlags&1) {
        if (code->flags2&0x20000) fn_005960e0(*(MachinePCodeInstruction **)((char *)asmCurrentBlock+24));
        else CError_Error(0x2815);
    }
    if (instruction->branchFlags&2) {
        if (code->flags2&0x10000) { ASM_PCODE_FLAGS(0,0x2000); }
        else CError_Error(0x2815);
    }
    if (instruction->branchFlags&4) {
        if (code->flags2&0x10000000) {
            for(i=0;i<code->operandCount;i++) if(code->operands[i].kind==6) { PPCError_Error(0x4e);break; }
            ASM_PCODE_FLAGS(0,0x08000000);
        } else CError_Error(0x2815);
    }
    if (instruction->branchFlags&8) {
        if (code->flags2&0x1000000) {
            fn_00595fc0(*(MachinePCodeInstruction **)((char *)asmCurrentBlock+24));
            if (!(instruction->specialFlags&2)) {
                (*(MachinePCodeInstruction **)((char *)asmCurrentBlock+24))->flags &= ~8;
                (*(MachinePCodeInstruction **)((char *)asmCurrentBlock+24))->flags |= 1;
            }
            asmHasBranchWithLink=1;
        } else CError_Error(0x2815);
    }
    if (instruction->branchFlags&0x10) { ASM_PCODE_FLAGS(0,0x04000000); }
    if (instruction->branchFlags&0x20) { ASM_PCODE_FLAGS(0,0x02000000); }
    encoding = (int)inlineAsmOpcodes[code->opcode].encoding >> 26;
    switch(encoding) {
        case 16:
            label=0;
            endLabel=makepclabel();
            switch(code->opcode) {
                case 2: if(code->operands[3].kind==6) label=code->operands[3].data.pointer;break;
                case 5: case 8: case 12: case 13: case 15: case 16:
                    if(code->operands[2].kind==6) label=code->operands[2].data.pointer;break;
                case 11: case 14: if(code->operands[0].kind==6) label=code->operands[0].data.pointer;break;
                default:CError_Internal(inlineAsmFilename,0x117d);
            }
            if(label) {
                pcaddedge(asmCurrentBlock,label,0);
                pcaddedge(asmCurrentBlock,endLabel,0);
                makepcblock();
                pclabelblock(asmCurrentBlock,endLabel);
            }
            break;
        case 18:
            if(instruction->branchFlags&8) {
                endLabel=makepclabel();
                pcaddedge(asmCurrentBlock,endLabel,0);
            }
            if(code->operands[0].kind==6) pcaddedge(asmCurrentBlock,code->operands[0].data.pointer,0);
            makepcblock();
            if(instruction->branchFlags&8) pclabelblock(asmCurrentBlock,endLabel);
            break;
        case 19:
            if(code->opcode==0x11 || code->opcode==0x88) {
                if(asmInterruptHandler) asmRfiInsideHandler=1;
                else asmRfiOutsideHandler=1;
                if(asmInterruptCode) asmInterruptObserved=1;
                if(code->opcode==0x11) { mnemonic=asmBlrMnemonic;asmHasBlr=1; }
                else { mnemonic=asmRfiMnemonic;asmHasRfi=1; }
                if(asmWarnInterruptReturn) PPCError_Warning(0x93,mnemonic,mnemonic);
            }
            break;
    }
}

extern void fn_00462e40(void *);
#pragma pack(push,2)
typedef struct MachineAsmConstraint {
    int cost;
    void *value;
    signed char registerClass;
    unsigned char unknown09[3], flags, flags2;
} MachineAsmConstraint;
#pragma pack(pop)
typedef char VerifyConstraint[(sizeof(MachineAsmConstraint)==14)?1:-1];
/* Target constraint callbacks precede the assertion-backed cluster; physical ownership remains under review. */




extern int fn_0058d8e0(const char *,int *);
extern int fn_0058d960(int,int,signed char);
extern void fn_0058da70(int,signed char,int *,int *);
extern void *fn_00403ff0(int);
extern MachineAsmRegister *fn_005cbc20(const char *), *fn_005cba70(const char *);
extern short lex(void);
extern MachineInt64 CMach_CalcFloatMonadic(MachineType *,short,MachineInt64);
extern MachineType asmFloatType,asmDoubleType;
extern char *asmRegisterFormat;
extern int sprintf(char *,const char *,...);
static char asmZeroCR[]="cr0",asmFormatOperators[]="/<>|*@",asmOptionalBasePair[]=",b,r";
#define ASM_FORMAT_DIGIT(c) ((signed char)(c)>=0 && ((*(unsigned short **)(*(char **)((char *)fn_00403ff0(1)+0x1bc)+8))[(signed char)(c)]&8))
#define ASM_OPERAND_INTEGER(o,n) do { int ai=(n);(o)->kind=1;(o)->data.integer.hi=ai<0?-1:0;(o)->data.integer.lo=ai; }while(0)
#define ASM_OPERAND_REGISTER(o,c,n,f) do { (o)->kind=2;*(short *)&(o)->registerClass=(c);(o)->data.reference.object=0;(o)->data.reference.value=(n);(o)->flags=(f); }while(0)
#define ASM_BASE_WARNING(o,inst,desc) do { \
    if (!(o)->data.reference.object && !(o)->data.reference.value) { \
        (o)->flags=0; if ((desc)->flags2&0x8000) PPCError_Warning(0x90); \
    } else if (((desc)->flags2&0x8000) && ((desc)->flags&2) && \
        (inst)->operands[0].kind==2 && *(short *)&(inst)->operands[0].registerClass==4 && \
        (inst)->operands[0].data.reference.object==(o)->data.reference.object && \
        (inst)->operands[0].data.reference.value==(o)->data.reference.value) { \
        if ((o)->data.reference.object) PPCError_Warning(0x91,(o)->data.reference.object->name+10); \
        else { char ab[40];sprintf(ab,asmRegisterFormat,(o)->data.reference.value);PPCError_Warning(0x91,ab); } \
    } \
}while(0)

MachineAsmInstruction *InlineAsm_ScanAssemblyOperands(MachineAsmMnemonic *mnemonic)
{
    MachineAsmOpcode *descriptor=&inlineAsmOpcodes[mnemonic->opcode];
    MachineAsmInstruction *instruction;
    MachineAsmOperand *operand,copy;
    MachineAsmRegister *reg;
    const char *format=(char *)mnemonic->unknown08;
    int capacity=descriptor->operandCount,size,flags,fixedRegister,number,bits,minimum,maximum;
    int value,other,operation,mask,i,baseFlags;
    unsigned char optional,ignore,negative,kind;
    if(descriptor->flags2&0x20000) capacity++;
    if(!(descriptor->flags2&0x80000) && (descriptor->flags2&0x10000)) capacity++;
    if(descriptor->flags2&0x1000000) capacity++;
    size=8+capacity*14;
    instruction=galloc(size);memclrw(instruction,size);
    instruction->opcode=(short)mnemonic->opcode;
    instruction->specialFlags=0;instruction->operandCount=0;
    operand=instruction->operands;
    for(;*format;format++) {
        if(instruction->operandCount>=capacity) CError_Internal(inlineAsmFilename,0x78f);
        if(*format==',') {
            if(asmToken==',') asmToken=fn_0055ebc0();
            else CError_Error(0x2784);
            format++;
        } else if(*format==';') format++;
        if(*format=='[' || *format=='(') format++;
        flags=1;ignore=optional=negative=0;
        if(*format=='=') {flags=2;format++;}
        else if(*format=='+') {flags=3;format++;}
        if(*format=='^') {flags|=0x8000;format++;}
        else if(*format==':') {flags|=0xc000;format++;}
        else if(*format=='.') {flags|=0x4000;format++;}
        else if(*format=='`') {if(asmProcessor==22)flags|=0x2000;format++;}
        if(*format=='-') {negative=1;format++;}
        if(*format=='?') {optional=1;format++;}
        if(*format=='!') {ignore=1;format++;}
        fixedRegister=-1;
        if(*format=='$') {format++;format+=fn_0058d8e0(format+1,&fixedRegister);}
        switch(*format) {
            case '&':
                if(format[1]=='2') {
                    *operand=operand[-2];format++;
                    if(operand->kind==2)operand->flags=flags;
                    operand++;instruction->operandCount++;
                    *operand=operand[-2];
                } else *operand=operand[-1];
                if(operand->kind==2)operand->flags=flags;
                break;
            case '%':
                format+=fn_0058d8e0(format+1,&number);
                if(format[1]=='(') {
                    format++;
                    if(format[1]=='=' || format[1]=='+')format++;
                    fixedRegister=-1;
                    if(format[1]=='$') {format++;format+=fn_0058d8e0(format+1,&fixedRegister);}
                    if(format[1]=='b') {
                        fn_00574640(operand,4,fixedRegister,flags);
                        if(!operand->data.reference.object && !operand->data.reference.value)operand->flags=0;
                    } else CError_Internal(inlineAsmFilename,0x81a);
                    operand++;
                    if(format[1]==')')format++;
                }
                ASM_OPERAND_INTEGER(operand,number);
                break;
            case 'b':
                if(asmToken==-1 && !asmTokenInteger.hi && !asmTokenInteger.lo) {
                    reg=fn_005cbdd0(asmZeroRegister);
                    if(reg) { ASM_OPERAND_REGISTER(operand,4,reg->value,0);operand->data.reference.object=reg->object; }
                    else fn_0055c3d0(asmZeroRegister,4);
                    asmToken=fn_0055ebc0();
                    if(descriptor->flags2&0x8000)PPCError_Warning(0x90);
                } else {
                    fn_00574640(operand,4,fixedRegister,flags);
                    ASM_BASE_WARNING(operand,instruction,descriptor);
                }
                break;
            case 'r':fn_00574640(operand,4,fixedRegister,flags);break;
            case 'a':case 'i':case 't':case 'u':case 'x':
                kind=*format;bits=16;
                if(kind=='a') {
                    if(ASM_FORMAT_DIGIT(format[1])) {kind=(unsigned char)*++format;}
                    else CError_Internal(inlineAsmFilename,0x867);
                } else if(kind=='k' || kind=='K')bits=32;
                if(ASM_FORMAT_DIGIT(format[1])) format+=fn_0058d8e0(format+1,&bits);
                else if(kind=='t') {kind='u';bits=5;}
                fn_0058da70(bits,kind,&maximum,&minimum);
                if(optional && asmToken==-1 && !asmTokenInteger.hi && !asmTokenInteger.lo &&
                    !strncmp(format+1,asmOptionalBasePair,4)) {
                    ASM_OPERAND_INTEGER(operand,0);operand++;instruction->operandCount++;format++;
                    asmToken=fn_0055ebc0();
                    if(asmToken==',')asmToken=fn_0055ebc0();
                    if(asmToken!=-1) {
                        fn_00574640(operand,4,fixedRegister,flags);
                        ASM_BASE_WARNING(operand,instruction,descriptor);
                        if(asmToken==',') {
                            asmToken=fn_0055ebc0();
                            reg=asmToken==-3?fn_005cc070(asmIdentifier):0;
                            if(reg && reg->registerClass==4) {format+=2;goto scanner_modifiers;}
                        }
                        operand[1]=*operand;
                        operand->data.reference.object=0;operand->data.reference.value=0;operand->flags=0;
                        operand++;instruction->operandCount++;format+=3;
                    }
                    goto scanner_modifiers;
                }
                if(optional && asmToken!=',' && asmToken!=-1) {
                    ASM_OPERAND_INTEGER(operand,0);
                    if(format[1]==',')format++;
                } else {
                    if(asmToken==',')asmToken=fn_0055ebc0();
                    if(ignore)InlineAsm_ConstantExpressionPPC(minimum,maximum);
                    else fn_00575690(operand,minimum,maximum);
                }
                if(kind=='i' && bits==16) {
                    number=(short)operand->data.integer.lo;
                    operand->data.integer.hi=number<0?-1:0;operand->data.integer.lo=number;
                }
                if(negative)operand->data.integer=fn_004da330(operand->data.integer);
                if(fn_0058d960(operand->data.integer.lo,bits,kind))CError_Internal(inlineAsmFilename,0x8e8);
                break;
            case 'O':
                if(asmToken==-1 && !asmTokenInteger.hi && !asmTokenInteger.lo) {
                    InlineAsm_ConstantExpressionPPC(0,0);
                    if(asmToken==',')asmToken=fn_0055ebc0();else CError_Error(0x2784);
                }
                continue;
            case 'f':fn_00574640(operand,3,fixedRegister,flags);break;
            case 'v':fn_00574640(operand,2,fixedRegister,flags);break;
            case 'T':
                if(optional && asmToken!=',')number=0x11c;
                else {
                    if(optional)asmToken=fn_0055ebc0();
                    fn_00575690(operand,0x10c,0x10d);
                    number=operand->data.integer.lo==0x10c?0x11c:0x11d;
                }
                ASM_OPERAND_REGISTER(operand,0,number,flags);break;
            case 'S':
                format+=fn_0058d8e0(format+1,&number);
                ASM_OPERAND_REGISTER(operand,0,number,flags);break;
            case 'c':case 'z':
                if(optional) {
                    if(asmToken==',')asmToken=fn_0055ebc0();
                    reg=asmToken==-3?fn_005cc070(asmIdentifier):0;
                    if(asmToken!=-1 && !(reg && reg->registerClass==1)) {
                        reg=fn_005cbdd0(asmZeroCR);
                        if(reg) { ASM_OPERAND_REGISTER(operand,1,reg->value,flags);operand->data.reference.object=reg->object; }
                        else fn_0055c3d0(asmZeroCR,1);
                        if(format[1]==',')format++;
                        break;
                    }
                    fn_00574640(operand,1,fixedRegister,flags);
                    if(*format=='z' && operand->data.reference.value>3)
                        PPCError_Error(0xa5,descriptor->mnemonic,operand->data.reference.value);
                } else {
                    fn_00574640(operand,1,fixedRegister,flags);
                    if(*format=='q' && operand->data.reference.value>3)
                        PPCError_Error(0xa5,descriptor->mnemonic,operand->data.reference.value);
                }
                break;
            case 'l':
                fn_005743c0(instruction,operand,instruction->opcode<=1,(unsigned char)(mnemonic->flags&2),(unsigned char)(mnemonic->flags&1));
                break;
            case 'w':fn_00573f60(instruction,operand,(int)0x80000000,0x7fffffff,negative);break;
            case 'M':case 'm':case 'n':case 'o':fn_00573f60(instruction,operand,-32768,65535,negative);break;
            case 'Q':case 'q':
                number=fn_00575330();
                ASM_OPERAND_REGISTER(operand,1,number>>2,flags);
                if(*format=='q' && operand->data.reference.value>3)
                    PPCError_Error(0x9f,descriptor->mnemonic,operand->data.reference.value,number);
                operand++;instruction->operandCount++;
                ASM_OPERAND_INTEGER(operand,number%4);break;
            case 'B':
                number=fn_00575330();
                if(*format=='q' && (number>>2)>0)CError_Error(0x27b3);
                ASM_OPERAND_INTEGER(operand,number%4);break;
            case 'd':
                if(format[1]!='(')CError_Internal(inlineAsmFilename,0x990);
                format++;baseFlags=1;
                if(format[1]=='=') {format++;baseFlags=2;}
                else if(format[1]=='+') {format++;baseFlags=3;}
                if(format[1]!='b')CError_Internal(inlineAsmFilename,0x9a2);
                if(format[2]!=')')CError_Internal(inlineAsmFilename,0x9a5);
                format+=2;
                if(instruction->opcode==0x8e || instruction->opcode==0x92) {
                    MachineType *floatType=instruction->opcode==0x8e?&asmFloatType:&asmDoubleType;
                    if(asmToken=='-' && lookahead()==-2) {
                        asmToken=lex();
                        *(MachineInt64 *)asmTokenFloatValue=CMach_CalcFloatMonadic(floatType,'-',*(MachineInt64 *)asmTokenFloatValue);
                    }
                    if(asmToken==-2)fn_00575280(operand,instruction,floatType);
                    else fn_00574c40(operand,instruction,1,baseFlags);
                } else if(instruction->opcode>=0x192 && instruction->opcode<=0x199)
                    operand=fn_00574b70(operand,instruction,baseFlags);
                else fn_00574c40(operand,instruction,1,baseFlags);
                break;
            case 'N':fn_00575690(operand,1,32);break;
            case 's':fn_00574640(operand,0,fixedRegister,flags);break;
            case 'D':case 'R':
                reg=asmToken==-3?(*format=='D'?fn_005cbc20(asmIdentifier+10):fn_005cba70(asmIdentifier+10)):0;
                if(reg) {ASM_OPERAND_INTEGER(operand,reg->value);asmToken=fn_0055ebc0();}
                else fn_00575690(operand,0,1023);
                break;
            case 'Y':
                mask=255;
                if(instruction->opcode==0x7a) {
                    if(instruction->operands[0].kind!=1)CError_Error(0x27a0);
                    mask=instruction->operands[0].data.integer.lo;
                }
                for(i=0;i<8;i++)if((0x80>>i)&mask) {
                    ASM_OPERAND_REGISTER(operand,1,i,flags);operand++;instruction->operandCount++;
                }
                operand--;instruction->operandCount--;break;
            case 'P':
                operand->kind=2;*(short *)&operand->registerClass=0;operand->data.reference.object=0;
                if(format[1]=='3') {format++;operand->data.reference.value=InlineAsm_ConstantExpressionPPC(0,7);}
                else operand->data.reference.value=InlineAsm_ConstantExpressionPPC(0,3);
                operand->flags=flags;break;
            case 'C':ASM_OPERAND_REGISTER(operand,0,9,flags);break;
            case 'L':ASM_OPERAND_REGISTER(operand,0,8,flags);break;
            case 'X':ASM_OPERAND_REGISTER(operand,0,1,flags);break;
            case 'Z':
                number=descriptor->flags2&0xe0000000;
                ASM_OPERAND_REGISTER(operand,1,number==0x40000000?1:(number==0x20000000?6:0),flags);break;
            case 'p':continue;
            default:CError_Internal(inlineAsmFilename,0xab8);
        }
scanner_modifiers:
        while(format[1] && strchr(asmFormatOperators,format[1])) {
            operation=*++format;
            if(operation=='/') {
                i=-1;if(format[1]=='2'){format++;i=-2;}
                copy=operand[i];operand[i]=*operand;*operand=copy;
            } else if(operation=='*' || operation=='<' || operation=='>' || operation=='|' || operation=='@') {
                if(operand->kind==1)value=operand->data.integer.lo;
                else if(operand->kind==2)value=operand->data.reference.value;
                else CError_Internal(inlineAsmFilename,0xae6);
                if(format[1]=='p') {
                    format++;
                    if(operand[-1].kind==1)other=operand[-1].data.integer.lo;
                    else if(operand[-1].kind==2)other=operand[-1].data.reference.value;
                    else CError_Internal(inlineAsmFilename,0xaf0);
                } else if(ASM_FORMAT_DIGIT(format[1]))format+=fn_0058d8e0(format+1,&other);
                else CError_Internal(inlineAsmFilename,0xaf5);
                switch(operation) {
                    case '<':value=(int)((unsigned int)other-(unsigned int)value);break;
                    case '>':value=(int)((unsigned int)value-(unsigned int)other);break;
                    case '|':value=(int)((unsigned int)value+(unsigned int)other);break;
                    case '*':value=(int)((unsigned int)value*(unsigned int)other);break;
                    case '@':value&=0xffffffffU>>((32U-(unsigned int)other)&31);break;
                    default:CError_Internal(inlineAsmFilename,0xb0e);
                }
                if(operand->kind==1) {operand->data.integer.hi=value<0?-1:0;operand->data.integer.lo=value;}
                else if(operand->kind==2)operand->data.reference.value=value;
                else CError_Internal(inlineAsmFilename,0xb15);
            }
        }
        instruction->operandCount++;operand++;
        if(format[1]==']' || format[1]==')')format++;
    }
    return instruction;
}
