/* RegisterInfo.c native GC 3.0a5.2 records and recovered register operations. */
#include "compiler/common.h"
#pragma pack(push, 2)
typedef struct NativeObject {
    UInt8 kind;
    UInt8 unknown_01;
    UInt8 datatype;
    UInt8 unknown_03[9];
    void *name;
    void *type;
    UInt8 unknown_14[4];
    UInt16 storageClass;
    UInt16 objectFlags;
    UInt8 unknown_1c[0x24];
    void *localInfo;
    UInt8 unknown_44[0x10];
    void *dataInfo;
    UInt8 registerAttribute;
} NativeObject;
#pragma pack(pop)
extern void *galloc(SInt32);
extern void memclrw(void *, SInt32);
extern void CError_Internal(const char *, int);

void *Registers_GetVarInfo(NativeObject *object)
{
    void *info;
    switch (object->datatype) {
        case 0:
            if (!object->dataInfo) {
                info = galloc(20);
                memclrw(info, 20);
                object->dataInfo = info;
            }
            return object->dataInfo;
        case 1:
            if (!object->localInfo)
                CError_Internal("RegisterInfo.c", 649);
            return object->localInfo;
        case 2:
            if (!object->dataInfo) {
                info = galloc(20);
                memclrw(info, 20);
                object->dataInfo = info;
            }
            return object->dataInfo;
        default:
            CError_Internal("RegisterInfo.c", 662);
            return 0;
    }
}

static inline void *native_var_info(NativeObject *object)
{
    void *info;
    switch (object->datatype) {
        case 0:
            if (!object->dataInfo) {
                info = galloc(20);
                memclrw(info, 20);
                object->dataInfo = info;
            }
            return object->dataInfo;
        case 1:
            if (!object->localInfo)
                CError_Internal("RegisterInfo.c", 649);
            return object->localInfo;
        case 2:
            if (!object->dataInfo) {
                info = galloc(20);
                memclrw(info, 20);
                object->dataInfo = info;
            }
            return object->dataInfo;
        default:
            CError_Internal("RegisterInfo.c", 662);
            return 0;
    }
}

/* Native records are private until their callers have been ported. */
#pragma pack(push, 2)
typedef struct NativeType {
    UInt8 kind, unknown_01;
    SInt32 size;
    UInt8 integral, unknown_07[9];
    SInt8 vectorKind;
} NativeType;
typedef struct NativeVarInfo {
    UInt8 unknown_00[9], used, unknown_0a[4], flags, regClass;
    SInt16 reg, regHi;
} NativeVarInfo;
typedef struct NativeArg {
    UInt8 kind, regClass;
    SInt16 displacement, reg;
    NativeObject *object;
    UInt8 unknown_0a[4];
} NativeArg;
typedef struct NativePCode {
    struct NativePCode *next;
    UInt8 unknown_04[8];
    UInt32 flagsLow, flags;
    UInt8 unknown_14[20];
    SInt16 opcode, numArgs;
    NativeArg args[1];
} NativePCode;
typedef struct NativeBlock {
    struct NativeBlock *next;
    UInt8 unknown_04[16];
    NativePCode *first;
} NativeBlock;
typedef struct NativeExplicitReg {
    struct NativeExplicitReg *next;
    NativeObject *object;
    void *name;
    SInt8 regClass, reg;
} NativeExplicitReg;
#pragma pack(pop)
extern UInt8 nativeByteOrder, operandsDebug, use_vrsave, disable_explicit_registers;
extern UInt8 register_init_enabled;
extern SInt16 target_cpu, high_word_offset, low_word_offset;
extern SInt16 data_007172c4, data_007171e2, data_007172d0, data_00717280;
extern SInt8 current_register_class;
extern SInt32 total_physical_registers[5], available_registers[5];
extern SInt32 nonvolatile_registers[5][32], nonvolatile_count[5], nonvolatile_used[5];
extern UInt8 physical_register_used[5][32];
extern char *register_class_names[5], *register_formats[5];
extern NativeExplicitReg *explicit_registers;
SInt32 last_argument_register[5];
extern SInt32 force_spill;
extern void fn_00594740(NativeObject *, SInt8, SInt16);
extern int fn_00594650(SInt8, SInt16);
extern void fn_00588120(void);
extern SInt32 gUsedVirtualRegistersFPR;


SInt8 Registers_ClassForType(NativeType *type)
{
    int kind = (SInt8)type->kind;
    int vectorKind;
    switch (kind) {
        case 11:
            if (type->kind != 11 || ((NativeType *) *(void **)((UInt8 *)type + 6))->kind == 7)
                break;
            /* fall through */
        case 4: case 12: return 4;
        case 1:
            if (type->integral < 23) return 4;
            return -2;
        case 2:
            if (operandsDebug && type->kind == 2 && type->integral < 23) return 4;
            if (target_cpu == 22) {
                switch (type->integral) { case 25: return 3; }
            }
            if (type->integral < 23) return 3;
            /* fall through */
        case 5:
            vectorKind = type->vectorKind;
            if (vectorKind > 3 && vectorKind < 15 && type->size == 16) return 2;
            break;
    }
    return -2;
}

SInt8 Registers_LoadStoreType(NativeType *type)
{
    switch (Registers_ClassForType(type)) {
        case 4:
            if ((operandsDebug && type->kind == 2 && type->integral < 23 && type->size != 4) ||
                ((type->kind == 1 && type->integral < 23 || type->kind == 4) && type->size == 8))
                return 2;
            break;
        case 3:
            if (target_cpu == 22) {
                switch (type->integral) { case 25: return 1; }
            }
            break;
    }
    return 0;
}

void init_endian(void)
{
    if (nativeByteOrder) {
        high_word_offset = 4; low_word_offset = 0;
        data_007172c4 = 4; data_007171e2 = 3;
        data_007172d0 = 6; data_00717280 = 5;
    } else {
        high_word_offset = 0; low_word_offset = 4;
        data_007172c4 = 3; data_007171e2 = 4;
        data_007172d0 = 5; data_00717280 = 6;
    }
}

UInt32 colored_vrs_as_vrsave(NativeBlock *blocks)
{
    UInt8 mode = use_vrsave;
    UInt32 mask = 0;
    NativeBlock *block;
    NativePCode *pc;
    int i;
    if (mode == 2) return 0xffffffff;
    if (!mode) return 0;
    for (block = blocks; block; block = block->next)
        for (pc = block->first; pc; pc = pc->next)
            if (pc->flags & 0x20000000)
                for (i = 0; i < pc->numArgs; i++)
                    if (pc->args[i].kind == 0 && pc->args[i].regClass == 2)
                        mask |= 1U << (31 - pc->args[i].reg);
    return mask;
}

void setup_diagnostic_reg_strings(void)
{
    register_class_names[0] = "SPR"; register_formats[0] = "spr%ld";
    register_class_names[1] = "CRFIELD"; register_formats[1] = "cr%ld";
    register_class_names[2] = "VR"; register_formats[2] = "vr%ld";
    register_class_names[3] = "FPR"; register_formats[3] = "f%ld";
    register_class_names[4] = "GPR"; register_formats[4] = "r%ld";
}

static inline int native_GetABIFirstNonVolatile(SInt8 regClass)
{
    switch (regClass) {
        case 0: return 3;
        case 1: return 2;
        case 2: return 20;
        case 4: return 14;
        case 3: return 14;
        default: return -1;
    }
}

int GetABIFirstNonVolatile(SInt8 regClass)
{
    switch (regClass) {
        case 0: return 3;
        case 1: return 2;
        case 2: return 20;
        case 4: return 14;
        case 3: return 14;
        default: return -1;
    }
}

void open_fe_temp_registers(void)
{
    SInt8 regClass = 0;
    explicit_registers = 0;
    register_init_enabled = 1;
    for (; regClass < 5; regClass++)
        last_argument_register[regClass] = 29 - native_GetABIFirstNonVolatile(regClass);
}

static inline UInt8 *native_fn_0057a790(NativeObject *object)
{
    if (object) {
        switch (object->datatype) {
            case 0: return &object->registerAttribute;
            default: return 0;
        }
    }
    return 0;
}

UInt8 *fn_0057a790(NativeObject *object)
{
    if (object) {
        switch (object->datatype) {
            case 0: return &object->registerAttribute;
            default: return 0;
        }
    }
    return 0;
}

static inline int native_fn_0057a740(NativeObject *object)
{
    UInt8 *attribute = native_fn_0057a790(object);
    if (disable_explicit_registers) return 0;
    if (attribute && *attribute) return 1;
    return 0;
}

int fn_0057a740(NativeObject *object)
{
    UInt8 *attribute = native_fn_0057a790(object);
    if (disable_explicit_registers) return 0;
    if (attribute && *attribute) return 1;
    return 0;
}

int is_register_object(NativeObject *object)
{
    return object->storageClass == 0x101 || native_fn_0057a740(object);
}

void retain_GPR_pair(NativeObject *object, SInt16 low, SInt16 high)
{
    NativeVarInfo *info;
    fn_00594740(0, 4, low);
    fn_00594740(0, 4, high);
    if (object) {
        info = native_var_info(object);
        info->regClass = 4;
        info->flags |= 6;
        info->reg = low;
        info->regHi = high;
    }
}

void fn_00579600(void)
{
    SInt8 regClass;
    int i, count;
    for (regClass = 0; regClass < 5; regClass++) {
        count = nonvolatile_count[regClass];
        for (i = count - 1; i >= 0; i--) {
            if (physical_register_used[regClass][nonvolatile_registers[regClass][i]] == 1)
                break;
            count--;
        }
        if (count > nonvolatile_used[regClass])
            nonvolatile_used[regClass] = count;
    }
}

void asm_used_register(SInt8 regClass, SInt16 reg)
{
    int i;
    if (reg >= total_physical_registers[regClass]) return;
    if (!fn_00594650(regClass, reg)) force_spill = 1;
    if (!physical_register_used[regClass][reg]) {
        i = nonvolatile_used[regClass];
        if (nonvolatile_registers[regClass][i] == reg) {
            if (available_registers[regClass] > 0) available_registers[regClass]--;
            physical_register_used[regClass][reg] = 1;
            nonvolatile_used[regClass]++;
        } else {
            for (; i < nonvolatile_count[regClass]; i++)
                if (nonvolatile_registers[regClass][i] == reg) {
                    physical_register_used[regClass][reg] = 1;
                    if (available_registers[regClass] > 0) available_registers[regClass]--;
                }
        }
    }
}

void fn_005792c0(SInt8 regClass)
{
    if (regClass == 4) fn_00588120();
    else if (regClass == 3 && operandsDebug && gUsedVirtualRegistersFPR > 32)
        CError_Internal("RegisterInfo.c", 1164);
}

#pragma pack(push, 2)
typedef struct NativeVirtualReg {
    UInt8 unknown_00[4];
    NativeObject *object;
    UInt8 unknown_08[12];
    UInt16 flags;
    UInt8 unknown_16[8];
} NativeVirtualReg;
typedef struct NativeObjectList {
    struct NativeObjectList *next;
    NativeObject *object;
} NativeObjectList;
typedef struct NativeExceptionReg {
    UInt8 regClass, padding;
    SInt16 reg;
} NativeExceptionReg;
#pragma pack(pop)
extern NativeVirtualReg *virtual_registers;
extern NativeObjectList *local_objects, *other_objects;
extern NativeBlock *basic_blocks;
extern SInt32 virtual_mode, virtual_register_count[5];
extern SInt32 volatile_registers[5][32], volatile_count[5];
char *special_register_names[5][32];
SInt32 last_nonvolatile_reg[5] = {3, 5, 31, 31, 31};
SInt32 nonvol_reserve[5] = {0, 0, 0, 4, 3};
extern SInt16 stack_base_reg, frame_base_reg;
extern SInt8 optimization_level;
extern SInt32 has_inline_assembly;
extern NativeObject *current_function;
extern SInt32 exception_register_count;
extern NativeExceptionReg exception_registers[];
extern int fn_00594590(SInt8);
extern void fn_005947e0(NativeObject *, SInt8);
extern NativeObject *fn_00620ec0(void *);
extern void fn_00620320(int, int);
extern UInt8 fn_004e2470(NativeType *);
extern void fn_00621cf0(void *);
extern void fn_0056ee40(int, ...);
extern void fn_005ed3d0(int, ...);

#define native_wide_type(type) \
    ((operandsDebug && (type)->kind == 2 && (type)->integral < 23 && (type)->size != 4) || \
    (((type)->kind == 1 && (type)->integral < 23 || (type)->kind == 4) && (type)->size == 8))

void assign_GPR_pair(NativeObject *object)
{
    NativeVarInfo *info = native_var_info(object);
    SInt32 low, high;
    NativeVarInfo *assigned;
    if (!virtual_mode) {
        if (available_registers[4] < 2) CError_Internal("RegisterInfo.c", 573);
        low = fn_00594590(4);
        high = fn_00594590(4);
        fn_00594740(0, 4, low);
        fn_00594740(0, 4, high);
        if (object) {
            assigned = native_var_info(object);
            assigned->regClass = 4;
            assigned->flags |= 6;
            assigned->reg = low;
            assigned->regHi = high;
        }
    } else {
        low = virtual_register_count[4]++;
        high = virtual_register_count[4]++;
    }
    info->regClass = 4;
    if ((SInt16)low > 0 && (SInt16)high > 0) {
        info->flags |= 6;
        info->reg = low;
        info->regHi = high;
    } else CError_Internal("RegisterInfo.c", 586);
}

void assign_register_by_type(NativeObject *object)
{
    NativeType *type = object->type;
    NativeVarInfo *info = native_var_info(object);
    UInt8 pair = 0;
    info->reg = 0;
    info->regHi = 0;
    info->regClass = Registers_ClassForType(type);
    if (info->regClass == 4) {
        if (native_wide_type(type)) pair = 1;
        else native_var_info(object);
    }
    if (info->regClass < 5) {
        if (pair) {
            if (info->regClass != 4) CError_Internal("RegisterInfo.c", 539);
            if (virtual_mode || available_registers[info->regClass] > 1)
                assign_GPR_pair(object);
        } else if (virtual_mode || available_registers[info->regClass] > 0)
            fn_005947e0(object, info->regClass);
    }
}

void fn_00578970(NativeObjectList *entity, void *expr)
{
    SInt32 saved = virtual_mode;
    virtual_mode = 1;
    entity->object = fn_00620ec0(expr);
    assign_register_by_type(entity->object);
    virtual_mode = saved;
}

int fn_00579300(int a, int b)
{
    NativeVirtualReg *left = &virtual_registers[a], *right = &virtual_registers[b];
    NativeObject *lo = left->object, *ro = right->object;
    int first;
    if (lo && lo->datatype != 1) return 1;
    if (ro && ro->datatype != 1) return 1;
    first = total_physical_registers[current_register_class];
    if (a >= first && b >= first) {
        if (lo && *((UInt8 *)lo->name + 10) != 64) return 1;
        if (ro && *((UInt8 *)ro->name + 10) != 64) return 1;
        if ((left->flags & 0x800) && lo && ((NativeType *)lo->type)->size < 4) return 1;
        if ((right->flags & 0x800) && ro && ((NativeType *)ro->type)->size < 4) return 1;
    }
    if (current_register_class == 4 && (a > b ? a : b) == frame_base_reg) return 1;
    return 0;
}

void fn_00579420(NativePCode *pc)
{
    if (current_register_class == 4) {
        if ((pc->flagsLow & 6) || (pc->flags & 0x1000)) {
            if (pc->args[1].reg >= total_physical_registers[current_register_class])
                fn_00620320(0, pc->args[1].reg);
            if (pc->flags & 0x8000)
                fn_00620320(pc->args[0].reg, pc->args[1].reg);
        } else {
            switch (pc->opcode) {
                case 0x37: case 0x38: case 0xc3: case 0xc4:
                case 0xde: case 0xe2: case 0xe3: case 0xec:
                case 0xf0: case 0xf1: case 0xf2: case 0xf3: case 0x19a:
                    if (pc->args[0].reg >= total_physical_registers[current_register_class])
                        fn_00620320(0, pc->args[0].reg);
                    break;
            }
        }
    }
}

int first_nonvolatile_reg(SInt8 regClass)
{
    int first = native_GetABIFirstNonVolatile(regClass), result = first;
    int used[32], i, warnings;
    NativeExplicitReg *entry;
    NativeObject *object;
    NativeVarInfo *info;
    SInt8 cls;
    char prefix[2];
    if (disable_explicit_registers) return first;
    for (i = 0; i < 32; i++) used[i] = 0;
    for (entry = explicit_registers; entry; entry = entry->next) {
        if (entry->regClass != regClass) continue;
        used[entry->reg - first] = entry->reg;
        if (entry->reg >= result) result = entry->reg + 1;
        object = entry->object;
        if (object && object->kind == 5) {
            info = native_var_info(object);
            if (info->reg) CError_Internal("RegisterInfo.c", 262);
            cls = entry->regClass;
            if (cls < 0 || cls >= 5) CError_Internal("RegisterInfo.c", 178);
            if (!physical_register_used[cls][entry->reg]) {
                physical_register_used[cls][entry->reg] = 1;
                info = native_var_info(object);
                info->regClass = cls;
                info->flags |= 2;
                info->reg = entry->reg;
                info->regHi = 0;
            } else fn_005ed3d0(10, object, register_class_names[cls], entry->reg);
        } else fn_0056ee40(11, (UInt8 *)entry->name + 10);
    }
    warnings = 0;
    for (i = 0; i < last_argument_register[regClass]; i++) {
        if (!used[i]) {
            for (i++; i < last_argument_register[regClass]; i++) {
                if (used[i]) {
                    switch (regClass) {
                        case 2: prefix[0] = 'v'; break;
                        case 3: prefix[0] = 'f'; break;
                        case 4: prefix[0] = 'r'; break;
                        default: CError_Internal("RegisterInfo.c", 226); prefix[0] = '?'; break;
                    }
                    prefix[1] = 0;
                    fn_0056ee40(100, prefix, used[i] - 1);
                    warnings++;
                    break;
                }
            }
        }
    }
    if (warnings) return first;
    return result;
}


void reset_nonvolatile_registers(void)
{
    SInt8 regClass;
    if (register_init_enabled) {
        memclrw(physical_register_used, sizeof(physical_register_used));
        for (regClass = 0; regClass < 5; regClass++) first_nonvolatile_reg(regClass);
    }
}

static inline void native_append_exception_reg(UInt8 regClass, SInt16 reg)
{
    exception_registers[exception_register_count].regClass = regClass;
    exception_registers[exception_register_count].reg = reg;
    exception_register_count++;
}

void set_last_exception_registers(void)
{
    NativeType *type = *(NativeType **)((UInt8 *)current_function->type + 14);
    NativeExplicitReg *entry;
    exception_register_count = 0;
    native_append_exception_reg(4, 1);
    for (entry = explicit_registers; entry; entry = entry->next)
        if (entry->object) native_append_exception_reg(entry->regClass, entry->reg);
    switch (Registers_ClassForType(type)) {
        case 4:
            native_append_exception_reg(4, 3);
            if (native_wide_type(type)) native_append_exception_reg(4, 4);
            break;
        case 3: native_append_exception_reg(3, 1); break;
        case 2: native_append_exception_reg(2, 2); break;
        default:
            if ((type->kind == 5 || type->kind == 6) && !fn_004e2470(type)) {
                native_append_exception_reg(4, 3);
                if (type->size > 4) native_append_exception_reg(4, 4);
            }
            break;
    }
    fn_00621cf0(&exception_register_count);
}

void init_target_registers(void)
{
    SInt8 cls;
    int i, first, last;
    for (cls = 0; cls < 5; cls++)
        for (i = 0; i < 32; i++) special_register_names[cls][i] = 0;
    special_register_names[0][0] = "XER";
    special_register_names[0][1] = "LR";
    special_register_names[0][2] = "CTR";
    special_register_names[0][3] = "VRSAVE";
    special_register_names[4][1] = "SP";
    special_register_names[4][13] = "SDA";
    register_class_names[0] = "SPR"; register_formats[0] = "spr%ld";
    register_class_names[1] = "CRFIELD"; register_formats[1] = "cr%ld";
    register_class_names[2] = "VR"; register_formats[2] = "vr%ld";
    register_class_names[3] = "FPR"; register_formats[3] = "f%ld";
    register_class_names[4] = "GPR"; register_formats[4] = "r%ld";
    total_physical_registers[0] = 4; total_physical_registers[1] = 8;
    total_physical_registers[2] = 32; total_physical_registers[3] = 32;
    total_physical_registers[4] = 32;
    physical_register_used[4][1] = 2;
    physical_register_used[4][2] = 2;
    physical_register_used[4][13] = 2;
    physical_register_used[1][5] = 2;
    for (cls = 0; cls < 5; cls++) {
        nonvolatile_count[cls] = 0;
        last = last_nonvolatile_reg[cls];
        if (last >= 0) {
            first = first_nonvolatile_reg(cls);
            last = last_nonvolatile_reg[cls];
            for (i = last; i >= first; i--)
                if (!physical_register_used[cls][i])
                    nonvolatile_registers[cls][nonvolatile_count[cls]++] = i;
        }
        available_registers[cls] = nonvolatile_count[cls] - nonvol_reserve[cls];
        if (available_registers[cls] < 0) available_registers[cls] = 0;
        volatile_count[cls] = 0;
        for (i = 0; i < total_physical_registers[cls]; i++)
            if ((i < native_GetABIFirstNonVolatile(cls) || i > last) && !physical_register_used[cls][i])
                volatile_registers[cls][volatile_count[cls]++] = i;
    }
    stack_base_reg = -1;
    frame_base_reg = -1;
    virtual_mode = optimization_level > 0 && !has_inline_assembly;
    force_spill = 0;
    set_last_exception_registers();
}

extern NativeType stsignedint, stunsignedint, stdouble, stlongdouble, vector_type;
extern int scratch_register;
extern void *PCodeUtilities_MakeInstruction(SInt16, ...);
extern void PCode_InsertBefore(void *, void *), PCode_InsertAfter(void *, void *);
extern SInt16 fn_00587230(NativeObject *);
extern SInt16 fn_00594b60(NativeObject *, int, int);
extern UInt8 Type_IsUnsigned(NativeType *);
extern void *fn_00595770(SInt16, SInt16, NativeObject *, SInt16, char);
extern void *fn_00595830(SInt16, SInt16, NativeObject *, SInt16, char);
extern SInt16 fn_004c2b40(NativeObject *);
#pragma pack(push, 2)
typedef struct NativeOperand {
    UInt8 kind, padding;
    SInt16 reg, regHi, secondaryReg;
    SInt32 displacement, immediate;
    NativeObject *object;
    unsigned long long flags;
} NativeOperand;
#pragma pack(pop)
extern void coerce_to_addressable_before(void *, NativeOperand *, SInt16);

NativeType *fn_005789b0(NativeVirtualReg *reg)
{
    NativeType *type = 0;
    switch (current_register_class) {
        case 4: type = &stsignedint; break;
        case 1: type = &stunsignedint; break;
        case 3: type = (reg->flags & 0x1000) ? &stlongdouble : &stdouble; break;
        case 2: type = &vector_type; break;
        default: CError_Internal("RegisterInfo.c", 1681); break;
    }
    return type;
}

void fn_00579230(void *before, SInt16 reg, NativePCode *pc)
{
    NativeArg *arg = &pc->args[2];
    SInt16 base;
    if (pc->opcode == 0x3f && arg->kind == 4 && (arg->regClass == 6 || arg->regClass == 13)) {
        base = fn_004c2b40(arg->object);
        PCode_InsertBefore(before, fn_00595770(reg, base, arg->object, arg->displacement, 0));
        PCode_InsertBefore(before, fn_00595830(reg, reg, arg->object, arg->displacement, 0));
    }
}

void fn_005784c0(void)
{
    NativeObjectList *list;
    NativeObject *object;
    NativeVarInfo *info;
    NativeBlock *block;
    NativePCode *pc;
    NativeArg *arg;
    UInt32 count;
    for (list = local_objects; list; list = list->next) {
        info = native_var_info(list->object);
        if ((info->flags & 2) && info->regClass == current_register_class) info->used = 0;
    }
    for (list = other_objects; list; list = list->next) {
        object = list->object;
        info = native_var_info(object);
        if (!(object->objectFlags & 3) && (info->flags & 2) && info->regClass == current_register_class)
            info->used = 0;
    }
    for (block = basic_blocks; block; block = block->next)
        for (pc = block->first; pc; pc = pc->next) {
            arg = pc->args;
            for (count = (SInt32)pc->numArgs; count--; arg++)
                if (arg->kind == 0 && arg->regClass == (UInt8)current_register_class) {
                    object = virtual_registers[arg->reg].object;
                    if (object) {
                        info = native_var_info(object);
                        info->used = 1;
                    }
                }
        }
    for (list = local_objects; list; list = list->next) {
        info = native_var_info(list->object);
        if ((info->flags & 2) && !info->used) info->flags &= ~2;
    }
    for (list = other_objects; list; list = list->next) {
        info = native_var_info(list->object);
        if ((info->flags & 2) && !info->used) info->flags &= ~2;
    }
}

void fn_00578a20(void *anchor, UInt8 before, SInt16 reg, NativeVirtualReg *state)
{
    NativeObject *object = state->object;
    NativeType *type = object->type;
    NativeVarInfo *info;
    SInt16 opcode;
    int offset;
    void *first, *second;
    switch (current_register_class) {
        case 1:
            info = native_var_info(object);
            first = PCodeUtilities_MakeInstruction(0x1ee,
                (info && (info->flags & 2)) ? info->reg : -1, reg);
            if (before) PCode_InsertBefore(anchor, first);
            else PCode_InsertAfter(anchor, first);
            break;
        case 4:
            switch (type->size) {
                case 1: opcode = 0x28; break;
                case 2: opcode = 0x2c; break;
                case 4: opcode = 0x31; break;
                case 8: opcode = 0x31; break;
                default: CError_Internal("RegisterInfo.c", 1507); break;
            }
            offset = (state->flags & 0x20) ? low_word_offset : ((state->flags & 0x10) ? high_word_offset : 0);
            first = PCodeUtilities_MakeInstruction(opcode, reg, fn_00587230(object), object, offset);
            if (before) PCode_InsertBefore(anchor, first);
            else PCode_InsertAfter(anchor, first);
            break;
        case 3:
            if ((state->flags & 0x1000) && target_cpu == 22 && type->kind == 2 && type->integral == 25) {
                opcode = fn_00594b60(object, 0, 0);
                if (opcode == 0x196) {
                    first = PCodeUtilities_MakeInstruction(opcode, reg, fn_00587230(object), object, 0, 0x390);
                    if (before) PCode_InsertBefore(anchor, first);
                    else PCode_InsertAfter(anchor, first);
                } else {
                    first = PCodeUtilities_MakeInstruction(0x3f, scratch_register, fn_00587230(object), object, 0);
                    second = PCodeUtilities_MakeInstruction(opcode, reg, 0, scratch_register, 0, 0x390);
                    if (before) PCode_InsertBefore(anchor, first);
                    else PCode_InsertAfter(anchor, first);
                    PCode_InsertBefore(anchor, first);
                    PCode_InsertAfter(first, second);
                }
            } else {
                opcode = type->size == 8 ? 0x9a : 0x96;
                first = PCodeUtilities_MakeInstruction(opcode, reg, fn_00587230(object), object, 0);
                if (before) PCode_InsertBefore(anchor, first);
                else PCode_InsertAfter(anchor, first);
            }
            break;
        case 2:
            first = PCodeUtilities_MakeInstruction(0x3f, scratch_register, fn_00587230(object), object, 0);
            second = PCodeUtilities_MakeInstruction(0xfe, reg, 0, scratch_register);
            if (before) PCode_InsertBefore(anchor, first);
            else PCode_InsertAfter(anchor, first);
            PCode_InsertAfter(first, second);
            break;
        default: CError_Internal("RegisterInfo.c", 1628); break;
    }
}

void fn_00578dd0(void *before, SInt16 reg, NativeVirtualReg *state)
{
    NativeObject *object = state->object;
    NativeType *type = object->type;
    NativeVarInfo *info;
    NativeOperand operand;
    SInt16 opcode;
    int offset;
    void *first, *second;
    switch (current_register_class) {
        case 1:
            info = native_var_info(object);
            first = PCodeUtilities_MakeInstruction(0x1ef, reg, scratch_register,
                (info && (info->flags & 2)) ? info->reg : -1);
            PCode_InsertBefore(before, first);
            break;
        case 4:
            switch (type->size) {
                case 1: opcode = 0x15; break;
                case 2: opcode = Type_IsUnsigned(type) ? 0x19 : 0x1d; break;
                case 4: opcode = 0x22; break;
                case 8: opcode = 0x22; break;
                default: CError_Internal("RegisterInfo.c", 1305); break;
            }
            memclrw(&operand, 28);
            operand.reg = operand.regHi = -1;
            operand.kind = 8;
            operand.object = state->object;
            if (state->object->datatype != 1) CError_Internal("RegisterInfo.c", 1342);
            coerce_to_addressable_before(before, &operand, reg);
            if (operand.kind != 1) CError_Internal("RegisterInfo.c", 1353);
            offset = (state->flags & 0x20) ? low_word_offset : ((state->flags & 0x10) ? high_word_offset : 0);
            PCode_InsertBefore(before, PCodeUtilities_MakeInstruction(opcode, reg, operand.reg,
                operand.object, operand.displacement + offset));
            break;
        case 3:
            if (object->datatype != 1) CError_Internal("RegisterInfo.c", 1375);
            if ((state->flags & 0x1000) && target_cpu == 22 && type->kind == 2 && type->integral == 25) {
                opcode = fn_00594b60(object, 0, 1);
                if (opcode == 0x192)
                    PCode_InsertBefore(before, PCodeUtilities_MakeInstruction(opcode, reg,
                        fn_00587230(object), object, 0, 0x390));
                else {
                    first = PCodeUtilities_MakeInstruction(0x3f, scratch_register, fn_00587230(object), object, 0);
                    second = PCodeUtilities_MakeInstruction(opcode, reg, 0, scratch_register, 0, 0x390);
                    PCode_InsertBefore(before, first);
                    PCode_InsertAfter(first, second);
                }
            } else {
                offset = (state->flags & 0x20) ? low_word_offset : ((state->flags & 0x10) ? high_word_offset : 0);
                opcode = type->size == 8 ? 0x92 : 0x8e;
                PCode_InsertBefore(before, PCodeUtilities_MakeInstruction(opcode, reg,
                    fn_00587230(object), object, offset));
            }
            break;
        case 2:
            if (object->datatype != 1) CError_Internal("RegisterInfo.c", 1422);
            first = PCodeUtilities_MakeInstruction(0x3f, scratch_register, fn_00587230(object), object, 0);
            second = PCodeUtilities_MakeInstruction(0xf9, reg, 0, scratch_register);
            PCode_InsertBefore(before, first);
            PCode_InsertAfter(first, second);
            break;
        default: CError_Internal("RegisterInfo.c", 1438); break;
    }
}
