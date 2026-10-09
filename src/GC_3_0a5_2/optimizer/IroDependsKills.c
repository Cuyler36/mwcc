/* Native IroDependsKills.c; private packed Windows optimizer records. */
#include "compiler/common.h"

#include <string.h>

typedef UInt8 byte;
typedef UInt16 ushort;
typedef UInt32 uint;

#pragma pack(push, 2)
typedef struct NativeIR NativeIR;
typedef struct NativeObject NativeObject;
typedef struct NativeVariable NativeVariable;
typedef struct NativeRange NativeRange;
typedef struct NativeObjectLink NativeObjectLink;

typedef struct NativeBits {
    uint count;
    uint words[1];
} NativeBits;

struct NativeIR {
    byte kind;
    byte operation;
    uint flags;
    uint nodeFlags;
    uint serial;
    void *statement;
    void *type;
    byte unknown16[20];
    NativeIR *left;
    NativeIR *right;
    NativeIR *third;
    void *functionType;
    byte unknown3a[4];
    NativeIR *next;
};

typedef struct NativeENode {
    byte kind;
    byte operation;
    byte unknown02[14];
    union {
        NativeObject *object;
        struct {
            uint lo;
            uint hi;
        } integer;
    } value;
} NativeENode;

struct NativeObject {
    byte unknown00[2];
    byte storage;
    byte unknown03[13];
    void *type;
    uint qualifiers;
    ushort flags18;
    byte unknown1a[4];
    void *alias;
    byte unknown22[56];
    byte flag5a;
};

struct NativeVariable {
    uint index;
    NativeObject *object;
    byte unknown08[5];
    byte addressed;
    byte unknown0e[2];
    NativeVariable *next;
};

struct NativeRange {
    NativeIR *first;
    NativeIR *last;
    NativeRange *next;
};

struct NativeObjectLink {
    NativeObjectLink *next;
    NativeObject *object;
};

typedef struct NativeAsmOperand {
    byte type;
    byte unknown01[9];
    NativeObject *object;
} NativeAsmOperand;

typedef struct NativeAsmEffects {
    byte flags[10];
    SInt32 numOperands;
    SInt32 numLabels;
    NativeAsmOperand operands[16];
    void *labels[16];
} NativeAsmEffects;
#pragma pack(pop)

typedef char CheckNativeIRSize[(sizeof(NativeIR) == 66) ? 1 : -1];
typedef char CheckNativeAsmEffectsSize[(sizeof(NativeAsmEffects) == 306) ? 1 : -1];

extern byte DAT_0070f240;
extern byte DAT_0070f279;
extern byte DAT_0070f1a8;
extern byte DAT_0070f26d;
extern uint native_variable_count;
extern NativeVariable *native_variables;
extern NativeBits *native_modified;
extern NativeBits *DAT_00710358;
extern void *DAT_007107e8;
extern NativeBits *DAT_0071085c;
extern void *DAT_007101c4;
extern byte DAT_00725f44;
extern byte IRO_IsAssignOp[];
extern byte DAT_00726059;
extern byte DAT_0072605f;
extern byte DAT_007260c2;
extern uint DAT_00704908;
extern uint DAT_0070490c;
extern byte nativeEffectTemplate[306];
extern void (*IRO_GetAsmEffects)(void *, NativeAsmEffects *);
extern char s_BitVector_h_00698a16[];
extern char s___clear_006b9ae6[];
extern char s_IRO_SetFuncKills_node_d_is_tre_006b9aee[];
extern byte DAT_006771c8;
extern uint stMaxTypeSize;
extern NativeBits *stPtrKills;
extern NativeBits *stFuncKills[1025];
extern NativeBits *IRO_VarKills;
extern NativeBits *IRO_Depends;

extern void CError_Internal(const char *, SInt32);
extern void fn_004a6fb0(void *, NativeObject *, NativeRange **);
extern void fn_004a5fb0(NativeObject *, NativeIR *, NativeObjectLink **);
extern void fn_004a60c0(NativeObject *, NativeIR *, NativeObjectLink **);
extern byte fn_004531f0(void *, uint);
extern byte fn_00453290(void *, uint);
extern byte fn_004a0a90(void);
extern NativeVariable *fn_004a0960(void);
extern void fn_004c5330(void *);
extern byte is_volatile_object(NativeObject *);
extern void fn_005a9dd0(void *, void (*)(NativeObject *), SInt32);
extern void fn_005ab3b0(NativeIR *, NativeIR **, SInt32 *, SInt32 *);
extern byte fn_005aba80(NativeIR *);
extern byte fn_005ac460(NativeIR *);
extern byte fn_005b07f0(NativeIR *);
extern NativeVariable *fn_005b3510(NativeIR *, SInt32);
extern NativeVariable *fn_005b53d0(NativeObject *, SInt32, SInt32);
extern byte CClass_Constructor(void *);
extern byte CClass_Destructor(void *);
extern void *CABI_GetSizeTType(void);
extern void IroBitVect_SetAllBits(NativeBits *);
extern void IroBitVect_ClearBitVector(NativeBits *);
extern void fn_005bf780(NativeBits *, NativeBits *);
extern void fn_005bf940(NativeBits *, NativeBits *);
extern void fn_005bfae0(NativeBits **, uint);
extern void fn_005f57b0(NativeBits *, NativeIR *);
extern void fn_005f5880(NativeBits *, NativeIR *);
extern byte CInt64_Equal(uint, uint, uint, uint);
extern void fn_005ed4c0(const char *, ...);

static char filename[] = "IroDependsKills.c";

#define set_bit(bits, bit) do {                                  \
    if (((bit) >> 5) < (bits)->count)                            \
        (bits)->words[(bit) >> 5] |= 1U << ((bit) & 31);         \
    else                                                         \
        CError_Internal(s_BitVector_h_00698a16, 0x52);           \
} while (0)

#define free_object_links(head) do {                             \
    NativeObjectLink *next;                                     \
    while (*(head)) {                                           \
        next = (*(head))->next;                                 \
        fn_004c5330(*(head));                                   \
        *(head) = next;                                         \
    }                                                           \
} while (0)

#define free_ranges(head) do {                                  \
    NativeRange *next;                                          \
    while (*(head)) {                                           \
        next = (*(head))->next;                                 \
        fn_004c5330(*(head));                                   \
        *(head) = next;                                         \
    }                                                           \
} while (0)

#define operand_object(node) (((NativeENode *)(node)->left)->value.object)

#define ensure_bits(bits) do {                                  \
    if (!(bits)) {                                              \
        fn_005bfae0(&(bits), native_variable_count + 1);        \
        set_bit((bits), 0);                                     \
    }                                                           \
} while (0)

void IRO_ComputeFuncKills(void);
void fn_005f6240(NativeIR *node, byte enabled);
void IRO_FindDepends(NativeIR *node);
void fn_005f6890(NativeObject *object);
void fn_005f7580(NativeObject *object);
void fn_005f6530(NativeIR *node);
void fn_005f6910(NativeIR *node);
void IRO_GetKills(NativeIR *node, byte allocate, byte stopAtSideEffect, byte recurse);
void IRO_GetKillsInExpr(NativeIR *node, byte stopAtSideEffect, byte recurse);
void fn_005f7240(NativeIR *node);
void fn_005f7620(NativeIR *node);

void fn_005f57b0(NativeBits *bits, NativeIR *node)
{
    NativeBits **table;
    SInt32 size;
    ushort flags;

    if (node->kind == 2 && node->operation == 4 && (node->flags & 4)) {
        size = *(SInt32 *)((byte *)node->type + 2);
        if (size > 0x400)
            size = 0x400;
        table = stFuncKills;
    } else {
        if (node->kind == 7) {
            flags = *(ushort *)((byte *)node->functionType + 0x1c);
            if (DAT_0070f279 && (flags & 3) == 3) {
                IroBitVect_ClearBitVector(bits);
                return;
            }
            if (DAT_0070f279 && (flags & 1)) {
                size = 0;
                table = &stPtrKills;
                goto selected;
            }
        }
        size = 0;
        table = &IRO_Depends;
    }

selected:
    if (stMaxTypeSize < (uint)size) {
        IroBitVect_ClearBitVector(bits);
        set_bit(bits, 0);
    } else {
        fn_005bf780(table[size], bits);
    }
}

void fn_005f5880(NativeBits *bits, NativeIR *node)
{
    byte *callee;
    byte *enode;
    byte *object;
    byte *name;
    byte *call;
    byte *parameter;
    byte *expression;
    byte *argument;
    NativeVariable *variable;
    NativeBits **table;
    SInt32 size;
    ushort flags;

    if (node->kind == 7 && (callee = (byte *)node->third) && callee[0] == 1 &&
        (enode = *(byte **)(callee + 0x2a)) && enode[0] == 59 &&
        (object = *(byte **)(enode + 0x10)) &&
        (name = *(byte **)(object + 0xc)) && name != (byte *)-10 &&
        strncmp((char *)name + 10, s___clear_006b9ae6, 8) == 0 &&
        object[0] == 5 && object[1] == 0 && object[2] == 3 &&
        (!DAT_0070f1a8 || *(void **)(object + 8) == DAT_007101c4) &&
        (call = *(byte **)(object + 0x10)) && call[0] == 7 &&
        *(void **)(call + 0xe) == &DAT_006771c8 &&
        (parameter = *(byte **)(call + 6)) && *(void **)(parameter + 0xc) == &DAT_006771c8 &&
        (expression = *(byte **)parameter) &&
        *(void **)(expression + 0xc) == CABI_GetSizeTType() && *(uint *)expression == 0 &&
        node->right && (argument = *(byte **)node->right) && argument[0] == 1 &&
        (enode = *(byte **)(argument + 0x2a)) && enode[0] == 59 &&
        (variable = fn_005b53d0(*(NativeObject **)(enode + 0x10), 0, 1))) {
        set_bit(bits, variable->index);
        return;
    }

    if (node->kind == 7 && DAT_0070f279) {
        flags = *(ushort *)((byte *)node->functionType + 0x1c);
        if ((flags & 3) == 3 || (flags & 1)) {
            IroBitVect_ClearBitVector(bits);
            if (!(flags & 4))
                return;
            if (fn_004a0a90()) {
                variable = fn_004a0960();
                if (!variable)
                    return;
                set_bit(bits, variable->index);
                return;
            }
            fn_005ed4c0(s_IRO_SetFuncKills_node_d_is_tre_006b9aee, node->serial);
        }
    }

    if (node->kind == 2 && node->operation == 4 && (node->flags & 4)) {
        size = *(SInt32 *)((byte *)node->type + 2);
        if (size > 0x400)
            size = 0x400;
        table = stFuncKills;
    } else {
        size = 0;
        table = &IRO_VarKills;
    }

    if (stMaxTypeSize < (uint)size) {
        IroBitVect_ClearBitVector(bits);
        set_bit(bits, 0);
    } else {
        fn_005bf780(table[size], bits);
    }
}

void IRO_ComputeFuncKills(void)
{
    NativeVariable *variable;
    NativeObject *object;
    byte addressed;
    byte storage;
    byte eligible;
    uint index;
    uint word;
    SInt32 size;
    SInt32 i;

    fn_005bfae0(&DAT_0071085c, native_variable_count + 1);
    stMaxTypeSize = 0;
    for (variable = native_variables; variable; variable = variable->next) {
        object = variable->object;
        if (variable->addressed || object->storage == 0 || object->storage == 2) {
            if (!fn_00453290(object->type, object->qualifiers) ||
                (*(byte *)object->type == 6 &&
                 (CClass_Constructor(object->type) || CClass_Destructor(object->type)))) {
                size = *(SInt32 *)((byte *)object->type + 2);
                if (size > 0x400)
                    size = 0x400;
                if (stMaxTypeSize < (uint)size)
                    stMaxTypeSize = size;
            }
        }
    }

    IRO_Depends = 0;
    IRO_VarKills = 0;
    stPtrKills = 0;
    memset(stFuncKills, 0, sizeof(stFuncKills));

    for (variable = native_variables; variable; variable = variable->next) {
        addressed = variable->addressed;
        object = variable->object;
        storage = object->storage;
        if (!addressed && storage != 0 && storage != 2) {
            if (DAT_0070f279 && (storage == 0 || storage == 2) &&
                object->flags18 == 0x102 && object->flag5a == 1 &&
                !fn_004531f0(object->type, object->qualifiers)) {
                ensure_bits(stPtrKills);
                set_bit(stPtrKills, index);
            }
            continue;
        }

        index = variable->index;
        ensure_bits(IRO_Depends);
        set_bit(IRO_Depends, index);

        eligible = !fn_00453290(object->type, object->qualifiers);
        if (!eligible && *(byte *)object->type == 6)
            eligible = CClass_Constructor(object->type) || CClass_Destructor(object->type);
        if (eligible) {
            ensure_bits(IRO_VarKills);
            set_bit(IRO_VarKills, index);

            if (addressed || ((storage == 0 || storage == 2) &&
                (object->flags18 != 0x102 || object->flag5a == 0))) {
                size = *(SInt32 *)((byte *)object->type + 2);
                if (size > 0x400)
                    size = 0x400;
                ensure_bits(stFuncKills[size]);
                set_bit(stFuncKills[size], index);
            }
        }

        if (DAT_0070f279 && (storage == 0 || storage == 2) &&
            !fn_004531f0(object->type, object->qualifiers)) {
            ensure_bits(stPtrKills);
            set_bit(stPtrKills, index);
        }
    }

    ensure_bits(IRO_Depends);
    ensure_bits(IRO_VarKills);
    if (DAT_0070f279)
        ensure_bits(stPtrKills);
    ensure_bits(stFuncKills[stMaxTypeSize]);

    for (i = (SInt32)stMaxTypeSize - 1; i >= 0; i--) {
        if (!stFuncKills[i])
            stFuncKills[i] = stFuncKills[i + 1];
        else
            fn_005bf940(stFuncKills[i + 1], stFuncKills[i]);
    }
}

void fn_005f6240(NativeIR *node, byte enabled)
{
    if (enabled)
        IRO_FindDepends(node);
}

void IRO_FindDepends(NativeIR *node)
{
    NativeVariable *variable;
    NativeAsmEffects effects;
    ushort flags;
    uint index;
    SInt32 i;

    switch (node->kind) {
    case 2:
    case 3:
        if (IRO_IsAssignOp[node->operation]) {
            variable = fn_005b3510(node, 0);
            index = variable ? variable->index : 0;
            set_bit(DAT_00710358, index);
            if (!index)
                fn_005f6910(node);
        }
        break;

    case 7:
        if ((*(uint *)((byte *)node->functionType + 0x16) & 0x200) == 0 || DAT_0070f26d) {
            flags = *(ushort *)((byte *)node->functionType + 0x1c);
            if (!DAT_0070f279 || ((flags & 3) != 3 && !(flags & 1))) {
                fn_005f6530(node);
            } else if (flags & 4) {
                if (!fn_004a0a90()) {
                    fn_005ed4c0(s_IRO_SetFuncKills_node_d_is_tre_006b9aee, node->serial);
                    fn_005f6530(node);
                } else {
                    variable = fn_004a0960();
                    if (variable)
                        set_bit(DAT_00710358, variable->index);
                }
            }
        }
        break;

    case 20:
        if (IRO_GetAsmEffects && node->left) {
            memcpy(&effects, nativeEffectTemplate, sizeof(effects));
            IRO_GetAsmEffects(node->left, &effects);
            for (i = 0; i < effects.numOperands; i++) {
                switch (effects.operands[i].type) {
                case 1:
                case 2:
                case 4:
                    variable = fn_005b53d0(effects.operands[i].object, 0, 1);
                    if (variable)
                        set_bit(DAT_00710358, variable->index);
                    break;
                }
            }
            if (effects.flags[4]) {
                fn_005f5880(DAT_0071085c, node);
                fn_005bf940(DAT_0071085c, DAT_00710358);
                if (node->statement)
                    fn_005a9dd0(*(void **)((byte *)node->statement + 0x12), fn_005f6890, 0);
            }
            if (effects.flags[1])
                IroBitVect_SetAllBits(DAT_00710358);
        }
        break;
    }
}

void fn_005f6530(NativeIR *node)
{
    NativeObject *callee = (NativeObject *)node->third;
    NativeRange *ranges = 0;
    NativeRange *range;
    NativeIR *linear;
    NativeObjectLink *objects;
    NativeObjectLink *link;
    NativeVariable *variable;
    uint index;
    byte failed = 0;
    byte found;

    if (!callee || !DAT_0070f240 || !callee->alias || !DAT_007107e8) {
        failed = 1;
    } else {
        fn_004a6fb0(DAT_007107e8, callee, &ranges);
        if (!ranges) {
            failed = 1;
        } else {
            for (range = ranges; range; range = range->next) {
                if (!range->first || !range->last) {
                    failed = 1;
                    break;
                }
                found = 0;
                for (linear = range->first; linear != range->last->next; linear = linear->next) {
                    if (linear->kind == 1 && ((NativeENode *)linear->left)->kind == 59) {
                        NativeObject *object;
                        found = 1;
                        object = operand_object(linear);
                        if (!object)
                            CError_Internal(filename, 0x351);
                        objects = 0;
                        fn_004a60c0(object, node, &objects);
                        for (link = objects; link; link = link->next) {
                            if (!link->object) {
                                failed = 1;
                                break;
                            }
                        }
                        free_object_links(&objects);
                        if (failed)
                            break;
                    }
                }
                if (!found)
                    failed = 1;
                if (failed)
                    break;
            }
            if (!failed) {
                for (range = ranges; range; range = range->next) {
                    for (linear = range->first; linear != range->last->next; linear = linear->next) {
                        if (linear->kind == 1 && ((NativeENode *)linear->left)->kind == 59) {
                            objects = 0;
                            fn_004a60c0(operand_object(linear), node, &objects);
                            for (link = objects; link; link = link->next) {
                                variable = fn_005b53d0(link->object, 1, 1);
                                if (!variable)
                                    CError_Internal(filename, 900);
                                index = variable->index;
                                if (!index)
                                    CError_Internal(filename, 0x386);
                                set_bit(DAT_00710358, index);
                            }
                            free_object_links(&objects);
                        }
                    }
                }
            }
            free_ranges(&ranges);
        }
    }
    if (failed) {
        fn_005f5880(DAT_0071085c, node);
        fn_005bf940(DAT_0071085c, DAT_00710358);
    }
    if (node->statement && fn_005aba80(node))
        fn_005a9dd0(*(void **)((byte *)node->statement + 0x12), fn_005f6890, 0);
}

void fn_005f6890(NativeObject *object)
{
    NativeVariable *variable = fn_005b53d0(object, 1, 1);
    NativeBits *bits;
    uint index;

    if (!variable)
        CError_Internal(filename, 0x31d);
    if (!(index = variable->index))
        CError_Internal(filename, 0x31f);
    bits = DAT_00710358;
    set_bit(bits, index);
}

void fn_005f6910(NativeIR *node)
{
    NativeIR *left = node->left;
    NativeObject *object;
    NativeRange *ranges = 0;
    NativeRange *range;
    NativeIR *linear;
    NativeVariable *variable;
    uint index;
    byte failed = 0;
    byte found;

    if (!left || left->kind != 2 || left->operation != 4 ||
        !(object = operand_object(left)) || !DAT_0070f240 || !object->alias || !DAT_007107e8) {
        failed = 1;
    } else {
        fn_004a6fb0(DAT_007107e8, object, &ranges);
        if (!ranges) {
            failed = 1;
        } else {
            for (range = ranges; range; range = range->next) {
                if (!range->first || !range->last) {
                    failed = 1;
                    break;
                }
                found = 0;
                for (linear = range->first; linear != range->last->next; linear = linear->next) {
                    if (linear->kind == 1 && ((NativeENode *)linear->left)->kind == 59) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    failed = 1;
                    break;
                }
            }
            if (!failed) {
                for (range = ranges; range; range = range->next) {
                    for (linear = range->first; linear != range->last->next; linear = linear->next) {
                        if (linear->kind == 1 && ((NativeENode *)linear->left)->kind == 59) {
                            object = operand_object(linear);
                            if (!object)
                                CError_Internal(filename, 0x2f3);
                            variable = fn_005b53d0(object, 1, 1);
                            if (!variable)
                                CError_Internal(filename, 0x2f5);
                            index = variable->index;
                            if (!index)
                                CError_Internal(filename, 0x2f7);
                            set_bit(DAT_00710358, index);
                        }
                    }
                }
            }
            free_ranges(&ranges);
        }
    }
    if (failed) {
        fn_005f5880(DAT_0071085c, left);
        fn_005bf940(DAT_0071085c, DAT_00710358);
    }
}

void IRO_GetKills(NativeIR *node, byte allocate, byte stopAtSideEffect, byte recurse)
{
    if (allocate)
        fn_005bfae0(&native_modified, native_variable_count + 1);
    else
        IroBitVect_ClearBitVector(native_modified);
    DAT_00726059 = 0;
    DAT_007260c2 = 0;
    DAT_0072605f = 0;
    DAT_00725f44 = 0;
    IRO_GetKillsInExpr(node, stopAtSideEffect, recurse);
}

void IRO_GetKillsInExpr(NativeIR *node, byte stopAtSideEffect, byte recurse)
{
    NativeVariable *variable;
    NativeIR *operand;
    NativeObject *object;
    NativeAsmEffects effects;
    SInt32 i;
    SInt32 count;
    SInt32 unknown;

    if (node->type && fn_004531f0(node->type, node->nodeFlags & 0x1f200003)) {
        DAT_0072605f = 1;
        DAT_007260c2 = 1;
    }
    if (node->kind && node->kind < 8 && fn_005ac460(node))
        DAT_007260c2 = 1;
    if (DAT_007260c2 && !DAT_00725f44 && stopAtSideEffect)
        return;

    switch (node->kind) {
    case 1:
    case 5:
        break;
    case 2:
        if (IRO_IsAssignOp[node->operation]) {
            DAT_007260c2 = 1;
            if (stopAtSideEffect)
                return;
        }
        operand = node->left;
        if (node->operation == 4) {
            if (operand->kind == 2 && operand->operation == 51)
                operand = operand->left;
            if (operand->kind == 1 && ((NativeENode *)operand->left)->kind == 59) {
                variable = fn_005b53d0(operand_object(operand), 0, 1);
                if (!variable) {
                    DAT_007260c2 = 1;
                } else {
                    if (is_volatile_object(variable->object)) {
                        DAT_0072605f = 1;
                        DAT_007260c2 = 1;
                    }
                    set_bit(native_modified, variable->index);
                }
            } else {
                fn_005f7620(node);
            }
        }
        if (recurse)
            IRO_GetKillsInExpr(operand, stopAtSideEffect, recurse);
        break;
    case 3:
        if (IRO_IsAssignOp[node->operation]) {
            DAT_007260c2 = 1;
            if (stopAtSideEffect)
                return;
        }
        if ((byte)(node->operation - 11) < 2) {
            if (!fn_005b07f0(node->right)) {
                DAT_00726059 = 1;
            } else {
                NativeENode *constant = (NativeENode *)node->right->left;
                if (CInt64_Equal(constant->value.integer.lo, constant->value.integer.hi,
                                 DAT_00704908, DAT_0070490c))
                    DAT_00726059 = 1;
            }
        }
        if (recurse) {
            IRO_GetKillsInExpr(node->left, stopAtSideEffect, recurse);
            IRO_GetKillsInExpr(node->right, stopAtSideEffect, recurse);
        }
        break;
    case 4:
        if (IRO_IsAssignOp[node->operation]) {
            DAT_007260c2 = 1;
            if (stopAtSideEffect)
                return;
        }
        if (recurse) {
            IRO_GetKillsInExpr(node->left, stopAtSideEffect, recurse);
            IRO_GetKillsInExpr(node->right, stopAtSideEffect, recurse);
            IRO_GetKillsInExpr(node->third, stopAtSideEffect, recurse);
        }
        break;
    case 6:
        operand = *(NativeIR **)((byte *)node + 0x2c);
        if (recurse && operand)
            IRO_GetKillsInExpr(operand, stopAtSideEffect, recurse);
        break;
    case 7:
        DAT_007260c2 = 1;
        if (!DAT_0070f279 || (*(ushort *)((byte *)node->functionType + 0x1c) & 3) != 3) {
            if (stopAtSideEffect)
                return;
        } else {
            DAT_00725f44 = 1;
        }
        fn_005f7240(node);
        if (node->statement && fn_005aba80(node))
            fn_005a9dd0(*(void **)((byte *)node->statement + 0x12), fn_005f7580, 0);
        if (recurse) {
            IRO_GetKillsInExpr(node->third, 0, recurse);
            count = *(SInt16 *)((byte *)node + 0x2c);
            while (--count >= 0)
                IRO_GetKillsInExpr(((NativeIR **)node->right)[count], 0, recurse);
        }
        break;
    case 20:
        if (IRO_GetAsmEffects && node->left) {
            memcpy(&effects, nativeEffectTemplate, sizeof(effects));
            IRO_GetAsmEffects(node->left, &effects);
            for (i = 0; i < effects.numOperands; i++) {
                variable = fn_005b53d0(effects.operands[i].object, 0, 1);
                if ((byte)(effects.operands[i].type - 1) < 2) {
                    DAT_007260c2 = 1;
                    if (stopAtSideEffect)
                        return;
                    set_bit(native_modified, variable->index);
                } else if (!effects.operands[i].type || effects.operands[i].type == 4) {
                    set_bit(native_modified, variable->index);
                }
            }
            if (effects.flags[2] || effects.flags[1]) {
                IroBitVect_SetAllBits(native_modified);
                if (effects.flags[1]) {
                    DAT_007260c2 = 1;
                    if (stopAtSideEffect)
                        return;
                }
            }
            if (effects.flags[4]) {
                DAT_007260c2 = 1;
                if (stopAtSideEffect)
                    return;
                fn_005f57b0(DAT_0071085c, node);
                fn_005bf940(DAT_0071085c, native_modified);
                if (node->statement && fn_005aba80(node))
                    fn_005a9dd0(*(void **)((byte *)node->statement + 0x12), fn_005f7580, 0);
            }
        }
        break;
    default:
        CError_Internal(filename, 0x28d);
        break;
    }
}

void fn_005f7240(NativeIR *node)
{
    NativeObject *callee = (NativeObject *)node->third;
    NativeRange *ranges = 0;
    NativeRange *range;
    NativeIR *linear;
    NativeObjectLink *objects;
    NativeObjectLink *link;
    NativeVariable *variable;
    uint index;
    byte failed = 0;
    byte found;

    if (!callee || !DAT_0070f240 || !callee->alias || !DAT_007107e8) {
        failed = 1;
    } else {
        fn_004a6fb0(DAT_007107e8, callee, &ranges);
        if (!ranges) {
            failed = 1;
        } else {
            for (range = ranges; range; range = range->next) {
                if (!range->first || !range->last) {
                    failed = 1;
                    break;
                }
                found = 0;
                for (linear = range->first; linear != range->last->next; linear = linear->next) {
                    if (linear->kind == 1 && ((NativeENode *)linear->left)->kind == 59) {
                        NativeObject *object;
                        found = 1;
                        object = operand_object(linear);
                        if (!object)
                            CError_Internal(filename, 0x115);
                        objects = 0;
                        fn_004a5fb0(object, node, &objects);
                        for (link = objects; link; link = link->next) {
                            if (!link->object) {
                                failed = 1;
                                break;
                            }
                        }
                        free_object_links(&objects);
                        if (failed)
                            break;
                    }
                }
                if (!found)
                    failed = 1;
                if (failed)
                    break;
            }
            if (!failed) {
                for (range = ranges; range; range = range->next) {
                    for (linear = range->first; linear != range->last->next; linear = linear->next) {
                        if (linear->kind == 1 && ((NativeENode *)linear->left)->kind == 59) {
                            objects = 0;
                            fn_004a5fb0(operand_object(linear), node, &objects);
                            for (link = objects; link; link = link->next) {
                                variable = fn_005b53d0(link->object, 1, 1);
                                if (!variable)
                                    CError_Internal(filename, 0x148);
                                index = variable->index;
                                if (!index)
                                    CError_Internal(filename, 0x14a);
                                if (is_volatile_object(link->object)) {
                                    DAT_0072605f = 1;
                                    DAT_007260c2 = 1;
                                }
                                set_bit(native_modified, index);
                            }
                            free_object_links(&objects);
                        }
                    }
                }
            }
            free_ranges(&ranges);
        }
    }
    if (failed) {
        fn_005f57b0(DAT_0071085c, node);
        fn_005bf940(DAT_0071085c, native_modified);
    }
}

void fn_005f7580(NativeObject *object)
{
    NativeVariable *variable = fn_005b53d0(object, 1, 1);
    NativeBits *bits;
    uint index;

    if (!variable)
        CError_Internal(filename, 0xdb);
    if (!(index = variable->index))
        CError_Internal(filename, 0xdd);
    if (is_volatile_object(object)) {
        DAT_0072605f = 1;
        DAT_007260c2 = 1;
    }
    bits = native_modified;
    set_bit(bits, index);
}

void fn_005f7620(NativeIR *node)
{
    NativeObject *object;
    NativeRange *ranges = 0;
    NativeRange *range;
    NativeIR *linear;
    NativeVariable *variable;
    uint index;
    NativeIR *base;
    SInt32 count;
    SInt32 unknown;
    byte failed = 0;
    byte found;

    if (!node || !DAT_0070f240 || !((NativeObject *)node)->alias || !DAT_007107e8) {
        failed = 1;
    } else {
        fn_004a6fb0(DAT_007107e8, (NativeObject *)node, &ranges);
        if (!ranges) {
            failed = 1;
        } else {
            for (range = ranges; range; range = range->next) {
                if (!range->first || !range->last) {
                    failed = 1;
                    break;
                }
                found = 0;
                for (linear = range->first; linear != range->last->next; linear = linear->next) {
                    if (linear->kind == 1 && ((NativeENode *)linear->left)->kind == 59) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    failed = 1;
                    break;
                }
            }
            if (!failed) {
                for (range = ranges; range; range = range->next) {
                    for (linear = range->first; linear != range->last->next; linear = linear->next) {
                        if (linear->kind == 1 && ((NativeENode *)linear->left)->kind == 59) {
                            object = operand_object(linear);
                            if (!object)
                                CError_Internal(filename, 0x82);
                            variable = fn_005b53d0(object, 1, 1);
                            if (!variable)
                                CError_Internal(filename, 0x84);
                            index = variable->index;
                            if (!index)
                                CError_Internal(filename, 0x86);
                            if (is_volatile_object(object)) {
                                DAT_0072605f = 1;
                                DAT_007260c2 = 1;
                            }
                            set_bit(native_modified, index);
                        }
                    }
                }
            }
            free_ranges(&ranges);
        }
    }
    if (failed) {
        linear = node->left;
        if (linear->kind == 2 && linear->operation == 51)
            linear = linear->left;
        if (linear->kind == 3 && linear->operation == 15) {
            fn_005ab3b0(linear, &base, &count, &unknown);
            if (count == 1) {
                object = operand_object(base);
                variable = fn_005b53d0(object, 1, 1);
                if (is_volatile_object(object)) {
                    DAT_0072605f = 1;
                    DAT_007260c2 = 1;
                }
                set_bit(native_modified, variable->index);
            } else {
                DAT_00726059 = 1;
                set_bit(native_modified, 0);
                fn_005f57b0(DAT_0071085c, node);
                fn_005bf940(DAT_0071085c, native_modified);
            }
            if (unknown)
                DAT_00726059 = 1;
        } else {
            DAT_00726059 = 1;
            set_bit(native_modified, 0);
            fn_005f57b0(DAT_0071085c, node);
            fn_005bf940(DAT_0071085c, native_modified);
        }
    }
}
