/* Native GC3 layouts are kept private until the shared frontend ABI is ported. */
#include "compiler/common.h"
#include "GC_3_0a5_2/compiler/CInt64.h"
#include <string.h>
#include <stddef.h>
#pragma pack(push, 2)
struct Type { unsigned char type; int size; unsigned char payload[1]; };
typedef struct MachineObject {
    unsigned char unknown00[16]; Type *type; int qualifiers;
} MachineObject;
typedef struct MachineStructMember {
    struct MachineStructMember *next; Type *type; unsigned char unknown08[8]; int qualifiers;
} MachineStructMember;
typedef struct MachineClassMember {
    void *unknown00; struct MachineClassMember *next; void *unknown08;
    Type *type; int qualifiers; int offset;
} MachineClassMember;
typedef struct MachineBase { struct MachineBase *next; Type *type; } MachineBase;
typedef struct MachineRegisterConstraint {
    Type *type; unsigned char unknown04[12]; void *context;
    unsigned char unknown14[4]; char *name;
    unsigned char unknown1c[50]; short parameterKind;
    unsigned char unknown50[69]; signed char registerClass, registerNumber;
} MachineRegisterConstraint;
typedef struct MachineRegisterBinding {
    struct MachineRegisterBinding *next; int flags; char *name;
    signed char registerClass, registerNumber; void *context; signed char isOutput;
} MachineRegisterBinding;
#pragma pack(pop)
typedef char MachineObjectTypeOffset[offsetof(MachineObject, type) == 16 ? 1 : -1];
typedef char MachineObjectQualifierOffset[offsetof(MachineObject, qualifiers) == 20 ? 1 : -1];
typedef char MachineConstraintClassOffset[offsetof(MachineRegisterConstraint, registerClass) == 149 ? 1 : -1];
typedef char MachineRegisterBindingSize[sizeof(MachineRegisterBinding) == 20 ? 1 : -1];
#define TYPEINT 1
#define TYPEFLOAT 2
#define TYPEENUM 4
#define TYPESTRUCT 5
#define TYPECLASS 6
#define KIND(t) ((signed char)(t)->type)
#define SIZE(t) ((t)->size)
#define SUBTYPE(t) (*(Type **)((char *)(t) + 6))
#define STYPE(t) (*(signed char *)((char *)(t) + 16))
#define STRUCTALIGN(t) (*(unsigned short *)((char *)(t) + 14))
#define CLASSALIGN(t) (*(unsigned short *)((char *)(t) + 42))
extern void CError_Internal(const char *, int);
extern void CError_ReportError(int, ...);
extern void CError_Warning(int, ...);
extern void CError_FatalError(int, ...);
extern unsigned char Type_IsUnsigned(Type *);
extern int fn_004533f0(Type *, int);
extern unsigned char CClass_IsTrivialCopyClass(Type *);
extern unsigned char machineUnsignedChar, machineReturnSmallStructs;
extern signed char machineAlignment;
extern unsigned char machineAlignArray, machineAlignEight, machinePragmaWarnings;
extern unsigned char machineAllocationQualOnly;
extern signed char machineMinimumAllocation;
extern short machineAlignLimits[5];
extern short cmach_curbfbasesize, cmach_curbfsize;
extern int cmach_structalign, cmach_structoffset;
extern int cmach_curaligned, cmach_curbfoffset;
extern unsigned char cmach_curispacked, machinePackedBits;
extern unsigned char machinePPCAlignment;
extern int machineBuiltinDoubleSize, machineBuiltinLongDoubleSize;
extern int machineBuiltinLongSize, machineBuiltinPointerSize;
extern unsigned short machineProcessor;
extern Type machineVectorType, machineFallbackType;
extern char machineFallbackName[];
extern void *fn_00579790(MachineObject *);
extern int fn_004c07c0(void);
extern unsigned char machineRegisterConstraintsEnabled, machineFloatOption;
extern void *machineCurrentFunction;
extern MachineRegisterBinding *machineRegisterBindings;
extern int machineRegisterCounts[];
extern const char *machineRegisterClassNames[];
extern signed char fn_00579560(Type *);
extern int fn_0057a700(signed char);
extern void fn_0056ee40(int, ...);
extern void fn_0056ed90(int, ...);
extern void *galloc(int);
extern int sscanf(const char *, const char *, ...);
extern unsigned short CTool_EndianConvertWord16(unsigned short);
extern unsigned int CTool_EndianConvertWord32(unsigned int);
extern void CTool_EndianConvertWord64(CInt64, void *);
extern void CTool_EndianConvertMem(void *, int);
extern void fn_0046c400(void *, int);
extern short CPrep_ScanMacroExpandedChar(void);
extern void CPrepTokenizer_GetNextToken(void);
extern char *CTemplateClass_ParseDouble(char *, double *, char *);
extern double CExpr2_ConvertCInt64ToDouble(CInt64 *);
extern double CExpr2_ConvertUnsignedCInt64ToDouble(CInt64 *);
extern void CExpr2_ConvertDoubleToCInt64(CInt64 *, double);
extern void CExpr2_ConvertDoubleToUnsignedCInt64(CInt64 *, double);
extern void CExpr2_ConvertCInt64ToUInt8(CInt64 *);
extern void CExpr2_ConvertCInt64ToUnsignedShort(CInt64 *);
extern void CExpr2_ClearCInt64Hi(CInt64 *);
extern void CExpr2_SignExtendSignedChar(CInt64 *);
extern void CExpr2_SignExtendShort(CInt64 *);
extern void CExpr2_SignExtendCInt64(CInt64 *);
extern CInt64 CExpr2_BitwiseOrCInt64(CInt64, CInt64);
extern CInt64 xor_64(CInt64, CInt64);
static const char cmachine_filename[] = "CMachine.c";
#undef CError_FATAL
#define CError_FATAL(line) CError_Internal(cmachine_filename, line)
#define ERR_UNEXPECTED_TOKEN 0x2788
#define ERR_DIVISION_BY_0 0x279b
short CMach_GetQualifiedTypeAlign(Type *, unsigned char);
unsigned short CMach_GetQualifiedStructAlign(Type *, unsigned char);
unsigned short CMach_GetQualifiedClassAlign(Type *, unsigned char);
int CMach_GetQUALalign(Type *, int);
int CMach_AllocationAlignment(Type *, int);
short fn_004e2cf0(Type *, int, unsigned char);
int fn_004e3720(Type *, unsigned char, unsigned char);

int CMach_RoundedSizeOf(MachineObject *object)
{
    int size;
    Type *type = object->type;
    int align;
    size = type->size;
    align = (short)CMach_GetQUALalign(type, object->qualifiers);
    if (!align) align = CMach_GetQualifiedTypeAlign(type, 1);
    align--;
    return (size + align) & ~align;
}
Float CMach_FloatReciprocal(Float value)
{
    value.data.value = 1.0 / value.data.value;
    return value;
}
Float CMach_CustomIntConvert(void)
{
    Float result;
    result.data.value = 0.0;
    return result;
}
unsigned char CMach_IsUnsignedType(Type *type)
{
    switch (KIND(type)) {
        case 1:
            switch (type->payload[0]) {
                case 0: case 3: case 4: case 6: case 8: case 10: case 12: return 1;
                case 1: return machineUnsignedChar;
            }
            return 0;
        case 12: return 1;
    }
    return 0;
}
unsigned char CMach_FloatIsPowerOf2(Float value)
{
    return value.data.value == 2.0 || value.data.value == 4.0 ||
        value.data.value == 8.0 || value.data.value == 16.0 ||
        value.data.value == 32.0 || value.data.value == 64.0 ||
        value.data.value == 128.0 || value.data.value == 256.0 ||
        value.data.value == 512.0 || value.data.value == 1024.0;
}
unsigned char CMach_PassAddressOf(Type *type)
{
    switch (KIND(type)) {
        case 3: return 1;
        case 5: if (STYPE(type) > 3 && STYPE(type) < 15) return 0;
        case 6: return 1;
        case 11: return SUBTYPE(type)->type == 7;
    }
    return 0;
}
unsigned char CMach_PassResultInHiddenArg(Type *type)
{
    switch (KIND(type)) {
        case 3: return 1;
        case 5:
            if (STYPE(type) > 3 && STYPE(type) < 15) return 0;
            return type->size > 8 || machineReturnSmallStructs;
        case 6:
            if (type->size > 8) return 1;
            if (!CClass_IsTrivialCopyClass(type) || machineReturnSmallStructs) return 1;
            return 0;
        case 11: return SUBTYPE(type)->type == 7;
    }
    return 0;
}
unsigned char CMach_GetFunctionResultClass(Type *type)
{
    Type *result = *(Type **)((char *)type + 14);
    switch (KIND(result)) {
        case 3: return 1;
        case 5: if (STYPE(result) > 3 && STYPE(result) < 15) return 0;
        case 6: case 11: return CMach_PassResultInHiddenArg(result) != 0;
    }
    return 0;
}
void CMach_StructLayoutInitOffset(unsigned int offset, int mode, unsigned char flag)
{
    cmach_structoffset = offset;
    cmach_structalign = 4;
    cmach_curbfsize = 0;
    cmach_curaligned = mode;
    cmach_curispacked = flag;
    if (!machinePackedBits) {
        cmach_curbfbasesize = 0;
        cmach_curbfoffset = 0;
    }
}
int CMach_MemberAlignValue(Type *type, int offset)
{
    int align = fn_004e2cf0(type, 0, 1);
    if (align > 1) {
        int mask = align - 1;
        return (align - (offset & mask)) & mask;
    }
    return 0;
}
short CMach_GetTypeAlign(Type *type, int qualifiers)
{
    short result = CMach_GetQUALalign(type, qualifiers);
    if (result) return result;
    return CMach_GetQualifiedTypeAlign(type, 1);
}
unsigned short CMach_GetClassAlign(Type *type)
{
    return CMach_GetQualifiedClassAlign(type, 1);
}
unsigned short CMach_GetStructAlign(Type *type)
{
    return CMach_GetQualifiedStructAlign(type, 1);
}
int fn_004e3720(Type *type, unsigned char first, unsigned char cached)
{
    return CMach_GetQualifiedTypeAlign(type, cached);
}
void CMach_PragmaParams(void)
{
    if (machinePragmaWarnings) CError_Warning(0x27ca, 0);
    while (CPrep_ScanMacroExpandedChar()) CPrepTokenizer_GetNextToken();
}
/* The GC3 body reads target float storage; it does not format text. */
Float fn_004e3780(Type *type, const void *memory)
{
    Float result;
    if (type->type == 2) {
        switch (type->size) {
            case 4: {
                float value;
                memcpy(&value, memory, 4);
                CTool_EndianConvertMem(&value, 4);
                result.data.value = value;
                return result;
            }
            case 8: {
                Float value;
                memcpy(&value, memory, 8);
                CTool_EndianConvertMem(&value, 8);
                result = value;
                return result;
            }
        }
    }
    CError_FATAL(0x43f);
    fn_0046c400(&result, 8);
    return result;
}
unsigned char CMach_FloatIsNegOne(double value) { return value == -1.0; }
unsigned char CMach_FloatIsOne(double value) { return value == 1.0; }
unsigned char CMach_FloatIsZero(double value) { return value == 0.0; }
int CMach_GetQUALalign(Type *type, int qualifiers)
{
    int alignment = 0;
    qualifiers = fn_004533f0(type, qualifiers) & ~0x10000000;
    if ((qualifiers &= 0x1f000000) != 0) {
        if (qualifiers == 0x01000000) alignment = 1;
        else if (qualifiers == 0x02000000) alignment = 2;
        else if (qualifiers == 0x03000000) alignment = 4;
        else if (qualifiers == 0x04000000) alignment = 8;
        else if (qualifiers == 0x05000000) alignment = 16;
        else if (qualifiers == 0x06000000) alignment = 32;
        else if (qualifiers == 0x07000000) alignment = 64;
        else if (qualifiers == 0x08000000) alignment = 128;
        else if (qualifiers == 0x09000000) alignment = 256;
        else if (qualifiers == 0x0a000000) alignment = 512;
        else if (qualifiers == 0x0b000000) alignment = 1024;
        else if (qualifiers == 0x0c000000) alignment = 2048;
        else if (qualifiers == 0x0d000000) alignment = 4096;
        else if (qualifiers == 0x0e000000) alignment = 8192;
        else CError_FATAL(0x12f);
    }
    return alignment;
}

int CMach_ArgumentAlignment(Type *type)
{
    unsigned char oldAlign = machineAlignment;
    unsigned char oldEight = machineAlignEight;
    int result;
    if (type->type == 5) return STRUCTALIGN(type);
    if (type->type == 6) return CLASSALIGN(type);
    machineAlignment = 2;
    machineAlignEight = 0;
    result = CMach_GetQualifiedTypeAlign(type, 0);
    machineAlignment = oldAlign;
    machineAlignEight = oldEight;
    return result;
}
void CMach_Configure(void)
{
    machineBuiltinLongDoubleSize = machineBuiltinDoubleSize;
    machineBuiltinPointerSize = machineBuiltinLongSize;
}
void *fn_004e2290(int kind)
{
    if (machineProcessor == 22 && kind == 25) return &machineVectorType;
    CError_FATAL(0x951);
    return machineFallbackName;
}
Type *fn_004e22c0(short token)
{
    if (machineProcessor == 22 && token == 0x115) return &machineVectorType;
    CError_ReportError(0x27a2);
    return &machineFallbackType;
}
int CMach_AllocationAlignment(Type *type, int qualifiers)
{
    int align, base, value;
    unsigned char kind;
    if (machineAllocationQualOnly) {
        short result = CMach_GetQUALalign(type, qualifiers);
        if (!result) result = CMach_GetQualifiedTypeAlign(type, 1);
        return result;
    }
    align = CMach_GetQUALalign(type, qualifiers);
    base = CMach_GetQualifiedTypeAlign(type, 1);
    if (align > base) base = align;
    kind = type->type;
    switch ((signed char)kind) {
        case 0: case 11: case 12: align = 4; break;
        default: align = 1;
    }
    if (align > base) base = align;
    if (kind == 13 || (kind == 5 && !(STYPE(type) > 3 && STYPE(type) < 15)) ||
        kind == 6 || (kind == 11 && SUBTYPE(type)->type == 7) || kind == 3) {
        value = machineMinimumAllocation;
        if (value > base) base = value;
    }
    for (value = base; value <= 8; value += value) {
        if (!((value - 1) & type->size) && value > base) base = value;
    }
    if (base < 8) {
        value = CMach_ArgumentAlignment(type);
        if (value > base) base = value;
    }
    return base;
}
int fn_004e5180(MachineObject *object)
{
    if (*((unsigned char *)object + 2) == 1) {
        void *info = fn_00579790(object);
        if (info && (*((unsigned char *)info + 14) & 1))
            return CMach_ArgumentAlignment(object->type);
        return CMach_AllocationAlignment(object->type, object->qualifiers);
    }
    return CMach_GetTypeAlign(object->type, object->qualifiers);
}
/* Target-order integer storage loading, distinct from InitIntMem. */
CInt64 fn_004e3fc0(Type *type, const void *memory)
{
    CInt64 result;
    signed char ch;
    short sh;
    unsigned int word;
    CInt64 wide;
    switch (KIND(type)) {
        case 1:
            switch (type->size) {
                case 1:
                    memcpy(&ch, memory, 1);
                    result.hi = 0; result.lo = ch;
                    return result;
                case 2:
                    memcpy(&sh, memory, 2);
                    sh = CTool_EndianConvertWord16(sh);
                    result.hi = 0; result.lo = sh;
                    return result;
                case 4:
                    memcpy(&word, memory, 4);
                    word = CTool_EndianConvertWord32(word);
                    result.hi = 0; result.lo = word;
                    return result;
                case 8:
                    memcpy(&wide, memory, 8);
                    CTool_EndianConvertWord64(wide, &result);
                    return result;
                default: CError_FATAL(0x2ed);
            }
        default: CError_FATAL(0x2f1);
    }
    result.lo = 0; result.hi = 0;
    return result;
}
CInt64 CMach_CalcIntConvertFromFloat(Type *type, double value)
{
    CInt64 result;
    if (((type->type == 1 && type->payload[0] < 23) || type->type == 4) && type->size == 8) {
        if (Type_IsUnsigned(type)) CExpr2_ConvertDoubleToUnsignedCInt64(&result, value);
        else CExpr2_ConvertDoubleToCInt64(&result, value);
    } else if (Type_IsUnsigned(type)) {
        switch (type->size) {
            case 1: result.lo = (unsigned char)value; result.hi = 0; break;
            case 2: result.lo = (unsigned short)value; result.hi = 0; break;
            case 4: result.lo = (unsigned int)value; result.hi = 0; break;
        }
    } else {
        switch (type->size) {
            case 1: { int v = (signed char)value; result.lo = v; result.hi = v < 0 ? -1 : 0; break; }
            case 2: { int v = (short)value; result.lo = v; result.hi = v < 0 ? -1 : 0; break; }
            case 4: { int v; result.lo = (int)value; v = value; result.hi = v < 0 ? -1 : 0; break; }
        }
    }
    return result;
}
void CMach_InitVectorMem(Type *type, const void *value, void *memory, unsigned char convert)
{
    unsigned char bytes[16];
    unsigned short shorts[8];
    unsigned int words[4];
    MachineStructMember *member;
    Type *element;
    int count, i, offset, total = type->size;
    if (STYPE(type) <= 3 || STYPE(type) >= 15) { CError_FATAL(0x350); return; }
    member = *(MachineStructMember **)((char *)type + 10);
    if (!member || !member->type) CError_FATAL(0x309);
    element = member->type;
    count = total / element->size;
    switch (element->size) {
        case 1:
            for (i = 0; i < count; i++) {
                if (fn_004c07c0()) bytes[i] = ((unsigned char *)value)[i];
                else bytes[i] = ((unsigned char *)value)[count - 1 - i];
            }
            memcpy(memory, bytes, total);
            break;
        case 2:
            for (i = 0; i < count; i++) {
                if (fn_004c07c0()) shorts[i] = ((unsigned short *)value)[i];
                else shorts[i] = ((unsigned short *)value)[count - 1 - i];
                if (convert) shorts[i] = CTool_EndianConvertWord16(shorts[i]);
            }
            memcpy(memory, shorts, total);
            break;
        case 4:
            for (i = 0; i < count; i++) {
                if (fn_004c07c0()) words[i] = ((unsigned int *)value)[i];
                else words[i] = ((unsigned int *)value)[count - 1 - i];
                if (!(element->type == 2 && element->payload[0] < 23) && convert)
                    words[i] = CTool_EndianConvertWord32(words[i]);
            }
            memcpy(memory, words, total);
            break;
        case 8:
            for (i = 0; i < count; i++) {
                offset = i * 2;
                if (fn_004c07c0()) {
                    words[offset] = ((unsigned int *)value)[offset];
                    words[offset + 1] = ((unsigned int *)value)[offset + 1];
                } else {
                    words[offset] = ((unsigned int *)value)[count * 2 - 1 - offset];
                    words[offset + 1] = ((unsigned int *)value)[count * 2 - 2 - offset];
                }
                if (!(element->type == 2 && element->payload[0] < 23)) {
                    /* These indices deliberately preserve the native loop. */
                    if (convert) words[i] = CTool_EndianConvertWord32(words[i]);
                    if (convert) words[i + 1] = CTool_EndianConvertWord32(words[i + 1]);
                }
            }
            memcpy(memory, words, total);
            break;
        default: CError_FATAL(0x34d);
    }
}
int fn_004e2770(short storage, Type *field, int alignment, int requested)
{
    int size = storage, capacity = size * 8;
    int padding = 0, current, bits, boundary, available, remainder;
    unsigned char empty = *((unsigned char *)field + 11) == 0;
    if (capacity < *((unsigned char *)field + 11)) CError_FATAL(0x77a);
    if (alignment && ((alignment - 1) & cmach_structoffset))
        padding = alignment - ((alignment - 1) & cmach_structoffset);
    if (!cmach_structoffset || empty || requested) {
        if (empty) {
            if (cmach_curbfsize) {
                cmach_structoffset = cmach_curbfoffset + cmach_curbfsize / 8 + (cmach_curbfsize % 8 != 0);
                if (alignment && ((alignment - 1) & cmach_structoffset))
                    padding = alignment - ((alignment - 1) & cmach_structoffset);
            }
            cmach_curbfsize = 0;
            if (alignment < size && storage && ((size - 1) & cmach_structoffset))
                padding = size - ((size - 1) & cmach_structoffset);
        }
        cmach_structoffset += padding;
        if (!*((unsigned char *)field + 11)) return cmach_structoffset;
        goto start;
    }
    if (cmach_curbfsize) {
        if (cmach_curbfbasesize == storage) {
            if (*((unsigned char *)field + 11) + cmach_curbfsize <= capacity) {
                cmach_structoffset = cmach_curbfoffset;
                *((unsigned char *)field + 10) = cmach_curbfsize;
                cmach_curbfsize += *((unsigned char *)field + 11);
                cmach_curbfbasesize = storage;
                cmach_curbfoffset = cmach_structoffset;
                cmach_structoffset += storage;
                return cmach_curbfoffset;
            }
            cmach_structoffset += padding;
            if (!*((unsigned char *)field + 11)) return cmach_structoffset;
            goto start;
        }
        current = cmach_curbfoffset + cmach_curbfsize / 8;
        remainder = cmach_curbfsize % 8;
    } else {
        current = cmach_structoffset;
        remainder = 0;
    }
    if (storage && ((size - 1) & current)) boundary = size - ((size - 1) & current);
    else boundary = 0;
    if (!boundary) boundary = size;
    bits = boundary * 8 - remainder;
    available = bits - *((unsigned char *)field + 11);
    if (available >= 0) {
        current += boundary - size;
        if (current < 0) CError_FATAL(0x7ae);
        cmach_curbfsize = capacity - bits;
        cmach_structoffset = current;
        *((unsigned char *)field + 10) = cmach_curbfsize;
        cmach_curbfsize += *((unsigned char *)field + 11);
        cmach_curbfbasesize = storage;
        cmach_curbfoffset = cmach_structoffset;
        cmach_structoffset += storage;
        return cmach_curbfoffset;
    }
    if (remainder) current++;
    cmach_structoffset = current;
    if (alignment && ((alignment - 1) & current)) padding = alignment - ((alignment - 1) & current);
    else padding = 0;
    cmach_structoffset += padding;
    if (!*((unsigned char *)field + 11)) return cmach_structoffset;
start:
    cmach_curbfsize = *((unsigned char *)field + 11);
    cmach_curbfbasesize = storage;
    cmach_curbfoffset = cmach_structoffset;
    cmach_structoffset += storage;
    *((unsigned char *)field + 10) = 0;
    return cmach_curbfoffset;
}
int CMach_StructLayoutBitfield(Type *field, int qualifiers)
{
    int requested = CMach_GetQUALalign(SUBTYPE(field), qualifiers);
    int align = 0, storage = 0, capacity = 0, padding = 0;
    if ((short)requested < SUBTYPE(field)->size) requested = 0;
    switch (SUBTYPE(field)->size) {
        case 1: storage = 1; capacity = 8; align = 0; break;
        case 2: storage = 2; capacity = 16; align = 2; break;
        case 4:
            storage = 4; capacity = 32;
            align = machineAlignment == 0 || machineAlignment == 4 ? 2 : 4;
            break;
        case 8: storage = 8; capacity = 64; align = 8; break;
        default: CError_FATAL(0x7ec);
    }
    switch (machineAlignment) {
        case 3: case 8: align = 0; break;
    }
    align = (short)requested > (short)align ? requested : align;
    if (!machinePackedBits) return fn_004e2770(storage, field, (short)align, (short)requested);
    if ((short)align && (((short)align - 1) & cmach_structoffset))
        padding = (short)align - (((short)align - 1) & cmach_structoffset);
    if (!cmach_curbfsize) {
        cmach_structoffset += (short)padding;
        if (!*((unsigned char *)field + 11)) return cmach_structoffset;
        cmach_curbfsize = *((unsigned char *)field + 11);
        cmach_curbfbasesize = storage;
        cmach_curbfoffset = cmach_structoffset;
        cmach_structoffset += (short)storage;
        *((unsigned char *)field + 10) = 0;
        return cmach_curbfoffset;
    }
    if (*((unsigned char *)field + 11) &&
        *((unsigned char *)field + 11) + cmach_curbfsize <= (short)capacity &&
        cmach_curbfbasesize == (short)storage) {
        *((unsigned char *)field + 10) = cmach_curbfsize;
        cmach_curbfsize += *((unsigned char *)field + 11);
        return cmach_curbfoffset;
    }
    cmach_structoffset += (short)padding;
    cmach_curbfsize = 0;
    cmach_curbfbasesize = storage;
    if (!*((unsigned char *)field + 11)) return cmach_structoffset;
    cmach_curbfoffset = cmach_structoffset;
    cmach_structoffset += (short)storage;
    *((unsigned char *)field + 10) = cmach_curbfsize;
    cmach_curbfsize += *((unsigned char *)field + 11);
    return cmach_curbfoffset;
}
void fn_004e1a50(MachineRegisterConstraint *object, const char *constraint)
{
    int parsed = 0, reg = 0, first;
    unsigned char isOutput = object->parameterKind == 0x102;
    Type *type = object->type;
    signed char actualClass, requestedClass;
    MachineRegisterBinding *binding;
    if (!machineRegisterConstraintsEnabled) { fn_0056ee40(0x6b); return; }
    if (machineCurrentFunction) { fn_0056ed90(0x5e); return; }
    actualClass = fn_00579560(type);
    if (actualClass == -2) { fn_0056ee40(0x6a, object->name + 10); return; }
    if (actualClass == 4) {
        if ((machineFloatOption && type->type == 2 && type->payload[0] < 23 && type->size != 4) ||
            (((type->type == 1 && type->payload[0] < 23) || type->type == 4) && type->size == 8)) {
            fn_0056ee40(0x66); return;
        }
    }
    if (object->parameterKind && (object->parameterKind < 0x101 || object->parameterKind > 0x103)) {
        fn_0056ee40(0x5f); return;
    }
    switch ((signed char)*constraint) {
        case 'r': requestedClass = 4; break;
        case 'f': requestedClass = 3; break;
        case 'v': requestedClass = 2; break;
        default: fn_0056ee40(0x60); return;
    }
    if (actualClass != requestedClass) {
        fn_0056ee40(0x65, machineRegisterClassNames[requestedClass], machineRegisterClassNames[actualClass]);
        return;
    }
    if (constraint[1]) parsed = sscanf(constraint + 1, "%i", &reg);
    if (parsed == -1 || parsed == 0) { fn_0056ee40(0x60); return; }
    first = fn_0057a700(requestedClass);
    if (reg < first || reg >= first + machineRegisterCounts[requestedClass]) {
        fn_0056ee40(0x61, machineRegisterCounts[requestedClass], machineRegisterClassNames[requestedClass], first);
        return;
    }
    if (object->registerClass == requestedClass && object->registerNumber == (signed char)reg) return;
    if (object->registerClass && object->registerNumber) {
        fn_0056ee40(0x62, machineRegisterClassNames[object->registerClass], object->registerNumber,
            machineRegisterClassNames[requestedClass], (signed char)reg);
        return;
    }
    for (binding = machineRegisterBindings; binding; binding = binding->next) {
        if (binding->registerClass != requestedClass) continue;
        if (!object->name || !((unsigned int)object->name + 10)) CError_FATAL(0xa78);
        if (binding->name == object->name && binding->context == object->context) {
            if (isOutput != binding->isOutput) fn_0056ee40(0x68, object->name + 10);
            else if ((signed char)reg != binding->registerNumber)
                fn_0056ee40(0x62, machineRegisterClassNames[requestedClass], binding->registerNumber,
                    machineRegisterClassNames[actualClass], (signed char)reg);
            else { object->registerClass = requestedClass; object->registerNumber = reg; }
            return;
        }
        if (binding->name && (signed char)reg == binding->registerNumber) {
            fn_0056ee40(0x63, binding->name + 10, machineRegisterClassNames[requestedClass], binding->registerNumber);
            return;
        }
    }
    binding = galloc(20);
    fn_0046c400(binding, 20);
    object->registerClass = requestedClass;
    object->registerNumber = reg;
    binding->registerClass = object->registerClass;
    binding->registerNumber = object->registerNumber;
    binding->name = object->name;
    binding->flags = 0;
    binding->context = object->context;
    binding->isOutput = isOutput;
    binding->next = machineRegisterBindings;
    machineRegisterBindings = binding;
}

short CMach_GetQualifiedTypeAlign(Type *type, unsigned char cached)
{
    int mode, size;
    unsigned char limited, array;
    short result;
    if (type->type == 5 && STYPE(type) > 3 && STYPE(type) < 15)
        return STRUCTALIGN(type);
    mode = machineAlignment;
    switch (mode) {
        case 3: case 8: return 1;
        case 4: case 5: case 6: case 7: limited = 1; break;
        default: limited = 0;
    }
    array = machineAlignArray;
again:
    switch (KIND(type)) {
        case 0: case 7: return 0;
        case 4: type = *(Type **)((char *)type + 14);
        case 1:
            if (limited) return type->size < machineAlignLimits[mode - 3] ? type->size : machineAlignLimits[mode - 3];
            size = type->size;
            if (size == 1) return 1;
            if (mode && size >= 8) return 8;
            if (mode == 11 && size >= 8) return 8;
            if (machineAlignEight && size == 8) return 8;
            if (mode && size >= 4) return 4;
            return 2;
        case 2: case 3:
            if (limited) return type->size < machineAlignLimits[mode - 3] ? type->size : machineAlignLimits[mode - 3];
            switch (mode) {
                case 0: return 2;
                case 1: return 4;
                case 2: case 9: case 10: case 11: return type->size > 4 ? 8 : 4;
                default: CError_FATAL(0x653);
            }
        case 11: case 12:
            if (limited) return type->size < machineAlignLimits[machineAlignment - 3] ? type->size : machineAlignLimits[machineAlignment - 3];
            return machineAlignment ? 4 : 2;
        case 13:
            if (!array) { type = SUBTYPE(type); goto again; }
            if (limited) return type->size < machineAlignLimits[mode - 3] ? type->size : machineAlignLimits[mode - 3];
            size = type->size;
            if (size == 1) return 1;
            if (!mode || size <= 2) return 2;
            if (mode == 1 || size < 8) return 4;
            result = CMach_GetQualifiedTypeAlign(SUBTYPE(type), cached);
            return result > 4 ? result : 4;
        case 5:
            result = cached ? STRUCTALIGN(type) : CMach_GetQualifiedStructAlign(type, cached);
            if (limited && machineAlignLimits[machineAlignment - 3] < result) result = machineAlignLimits[machineAlignment - 3];
            return result;
        case 6:
            result = cached ? CLASSALIGN(type) : CMach_GetQualifiedClassAlign(type, cached);
            if (limited && machineAlignLimits[machineAlignment - 3] < result) result = machineAlignLimits[machineAlignment - 3];
            return result;
        case 8: type = SUBTYPE(type); goto again;
        case 10: return 1;
        default: CError_FATAL(0x688); return 0;
    }
}
short fn_004e2cf0(Type *type, int requested, unsigned char cached)
{
    int align = CMach_GetQualifiedTypeAlign(type, cached);
    int mode;
    if (align < 1) align = 1;
    if (type->type == 5 && STYPE(type) > 3 && STYPE(type) < 15 && align < STRUCTALIGN(type))
        align = STRUCTALIGN(type);
    mode = machineAlignment;
    switch (mode) {
        case 0: if (align > 2) align = 2; break;
        case 1: if (align > 4) align = 4; break;
        case 8: align = 1; break;
        case 2: case 9: case 10:
            if (!machineAlignEight) {
                if (mode == 10 || (mode == 2 && machinePPCAlignment))
                    align = fn_004e3720(type, cmach_structoffset == 0 || cmach_structalign >= 8, cached);
                else align = fn_004e3720(type, cmach_structoffset == 0, cached);
            }
        case 11: if (requested > align) align = requested; break;
    }
    if (align > cmach_structalign) cmach_structalign = align;
    return align;
}
int CMach_StructLayoutGetCurSize(void)
{
    int divisor = 0;
    if (!machinePackedBits && cmach_curbfsize) {
        switch (machineAlignment) {
            case 3: case 8: divisor = 8; break;
            case 0: case 4: divisor = 16; break;
        }
        if (divisor) {
            int unused = cmach_curbfbasesize * 8 - cmach_curbfsize;
            if (unused > 0) cmach_structoffset -= unused / divisor;
        }
        cmach_curbfsize = 0;
    }
    return cmach_structoffset;
}
int CMach_StructLayoutGetOffset(Type *type, int qualifiers)
{
    int align, result;
    short padding;
    if (!machinePackedBits && cmach_curbfsize) {
        int unused = cmach_curbfbasesize * 8 - cmach_curbfsize;
        if (unused >= 0) cmach_structoffset -= unused / 8;
    }
    qualifiers = fn_004533f0(type, qualifiers);
    cmach_curbfsize = 0;
    align = CMach_GetQUALalign(type, qualifiers);
    result = cmach_structoffset;
    align = fn_004e2cf0(type, align, 1);
    padding = (align - (result & (align - 1))) & (align - 1);
    result = cmach_structoffset + padding;
    cmach_structoffset = result + type->size;
    return result;
}
unsigned short CMach_GetQualifiedStructAlign(Type *type, unsigned char cached)
{
    int packed = machineAlignEight;
    int mode, align = 1, value;
    signed char stype = STYPE(type);
    MachineStructMember *member;
    unsigned char first;
    if (stype > 3 && stype < 15) return STRUCTALIGN(type);
    mode = machineAlignment;
    switch (mode) {
        case 3: case 8: return 1;
        case 0: return 2;
        case 1: return type->size > 2 ? 4 : 2;
    }
    if (type->size <= 1) return 1;
    switch (mode) {
        default: CError_FATAL(0x4ef);
        case 4: case 5: case 6: case 7:
            for (member = *(MachineStructMember **)((char *)type + 10); member; member = member->next) {
                value = CMach_GetQualifiedTypeAlign(member->type, cached);
                if (value > align) align = value;
                if (cached) {
                    value = CMach_GetQUALalign(member->type, member->qualifiers);
                    if (value > align) align = value;
                }
            }
            return align;
        case 11: packed = 1;
        case 2: case 9: case 10: break;
    }
    if (packed) {
        for (member = *(MachineStructMember **)((char *)type + 10); member; member = member->next) {
            value = CMach_GetQualifiedTypeAlign(member->type, cached);
            if (value > align) align = value;
            if (cached) {
                value = CMach_GetQUALalign(member->type, member->qualifiers);
                if (value > align) align = value;
            }
        }
    } else if (stype == 1) {
        for (member = *(MachineStructMember **)((char *)type + 10); member; member = member->next) {
            value = fn_004e3720(member->type, 1, cached);
            if (value > align) align = value;
            if (cached) {
                value = CMach_GetQUALalign(member->type, member->qualifiers);
                if (value > align) align = value;
            }
        }
    } else {
        first = 1;
        for (member = *(MachineStructMember **)((char *)type + 10); member; member = member->next) {
            mode = machineAlignment;
            if (mode == 10 || (mode == 2 && machinePPCAlignment))
                value = fn_004e3720(member->type, first || align >= 8, cached);
            else value = fn_004e3720(member->type, first, cached);
            if (value > align) align = value;
            if (cached) {
                value = CMach_GetQUALalign(member->type, member->qualifiers);
                if (value > align) align = value;
            }
            first = 0;
        }
    }
    return align;
}
unsigned short CMach_GetQualifiedClassAlign(Type *type, unsigned char cached)
{
    int packed = machineAlignEight;
    int mode = machineAlignment;
    /* Native ECX at 004e3366 can be unspecified on the no-base path. It only
     * changes `first`, which is passed as the ignored middle argument of the
     * exact wrapper at 004e3720. It cannot change alignment or helper effects.
     * Initialize the source temporary to avoid an unnecessary undefined read;
     * CW94 eliminates this entire dead flag calculation when inlining wrapper.
     */
    int align = 1, value = 0;
    MachineBase *base;
    MachineClassMember *member;
    unsigned char first;
    switch (mode) {
        case 3: case 8: return 1;
        case 0: return 2;
        case 1: return type->size > 2 ? 4 : 2;
    }
    if (type->size <= 1) return 1;
    switch (mode) {
        default: CError_FATAL(0x576);
        case 4: case 5: case 6: case 7:
            for (base = *(MachineBase **)((char *)type + 14); base; base = base->next)
                if (CLASSALIGN(base->type) > align) align = CLASSALIGN(base->type);
            for (member = *(MachineClassMember **)((char *)type + 22); member; member = member->next) {
                value = cached ? CMach_GetQUALalign(member->type, member->qualifiers) : 0;
                value = (short)fn_004e2cf0(member->type, value, cached);
                if (value > align) align = value;
            }
            return align;
        case 11: packed = 1;
        case 2: case 9: case 10: break;
    }
    if (packed) {
        for (base = *(MachineBase **)((char *)type + 14); base; base = base->next)
            if (CLASSALIGN(base->type) > align) align = CLASSALIGN(base->type);
        for (member = *(MachineClassMember **)((char *)type + 22); member; member = member->next) {
            value = cached ? CMach_GetQUALalign(member->type, member->qualifiers) : 0;
            value = (short)fn_004e2cf0(member->type, value, cached);
            if (value > align) align = value;
        }
    } else {
        first = 1;
        base = *(MachineBase **)((char *)type + 14);
        if (base) {
            first = 0;
            for (; base; base = base->next)
                if (CLASSALIGN(base->type) > align) align = CLASSALIGN(base->type);
        }
        if (*(unsigned char *)((char *)type + 46) == 1) {
            for (member = *(MachineClassMember **)((char *)type + 22); member; member = member->next) {
                value = fn_004e3720(member->type, 1, cached);
                if (value > align) align = value;
                if (cached) {
                    value = CMach_GetQUALalign(member->type, member->qualifiers);
                    if (value > align) align = value;
                }
            }
        } else {
            for (member = *(MachineClassMember **)((char *)type + 22); member; member = member->next) {
                /* The native code tests its previous alignment result against 8. */
                if (member->offset && value != 8) first = 0;
                mode = machineAlignment;
                if (mode == 10 || (mode == 2 && machinePPCAlignment))
                    value = fn_004e3720(member->type, first || align >= 8, cached);
                else value = fn_004e3720(member->type, first, cached);
                if (value > align) align = value;
                if (cached) {
                    value = CMach_GetQUALalign(member->type, member->qualifiers);
                    if (value > align) align = value;
                }
            }
        }
    }
    return align;
}

#define ISZERO64(v) ((Boolean)(((v).hi == 0) && ((v).lo == 0)))
void CMach_InitFloatMem(Type *type, Float value, unsigned char *dest)
{
    if (type->type == TYPEFLOAT) {
        switch (type->size) {
            case 4: {
                float f = value.data.value;
                memcpy(dest, &f, 4);
                CTool_EndianConvertMem(dest, 4);
                return;
            }
            case 8: {
                double d = value.data.value;
                memcpy(dest, &d, 8);
                CTool_EndianConvertMem(dest, 8);
                return;
            }
        }
    }
    CError_FATAL(0x41f);
}

Float CMach_CalcFloatConvert(Type *type, Float value)
{
    switch (type->size) {
        case 4:
            value.data.value = (float)value.data.value;
            break;
        case 8:
            value.data.value = value.data.value;
            break;
        case 10:
            break;
        case 12:
            break;
        default:
            CError_Internal(cmachine_filename, 0x3de);
    }
    return value;
}

Float CMach_CalcFloatConvertFromInt(Type *type, CInt64 value)
{
    Float f;
    if (((type->type == TYPEINT && type->payload[0] < 23) || type->type == TYPEENUM) && type->size == 8) {
        if (Type_IsUnsigned(type))
            f.data.value = CExpr2_ConvertUnsignedCInt64ToDouble(&value);
        else
            f.data.value = CExpr2_ConvertCInt64ToDouble(&value);
    } else {
        if (Type_IsUnsigned(type))
            f.data.value = value.lo;
        else
            f.data.value = (SInt32)value.lo;
    }
    return f;
}

void *CMach_FloatScan(char *text, Float *result, char *flag)
{
    union {
        double value;
        Float integer;
    } val;

    char *end = CTemplateClass_ParseDouble(text, &val.value, flag);
    if (end == NULL)
        CError_FatalError(0x27aa);
    if (*flag) {
        result->data.value = 0.0;
    } else
        *result = val.integer;
    return end;
}

Boolean CMach_CalcFloatDiadicBool(Type *self, volatile double a, SInt16 op, volatile double b)
{
    int dead_1;
    dead_1 = 0;
    switch (op) {
        case 0x176:
            return a == b;
        case 0x177:
            return a != b;
        case 0x178:
            return a <= b;
        case 0x179:
            return a >= b;
        case 0x3e:
            return a > b;
        case 0x3c:
            return a < b;
        default:
            CError_Internal(cmachine_filename, 0x387);
            return 0;
    }
}

Float CMach_CalcFloatMonadic(Type *type, short op, Float value)
{
    Float result;
    if (op != 0x2d)
        CError_FATAL(0x371);
    value.data.value = -value.data.value;
    result = value;
    switch (type->size) {
        case 4:
            result.data.value = (float)result.data.value;
            break;
        case 8:
            result.data.value = result.data.value;
            break;
        case 10:
        case 12:
            break;
        default:
            CError_FATAL(0x3de);
            break;
    }
    return result;
}

Float CMach_CalcFloatDiadic(Type *type, Float left, short op, Float right)
{
    switch (op) {
        case '+':
            left.data.value += right.data.value;
            break;
        case '-':
            left.data.value -= right.data.value;
            break;
        case '*':
            left.data.value *= right.data.value;
            break;
        case '/':
            left.data.value /= right.data.value;
            break;
        default:
            CError_FATAL(0x364);
    }
    return CMach_CalcFloatConvert(type, left);
}

void CMach_InitIntMem(Type *type, CInt64 val, void *mem)
{
    UInt8 ch;
    UInt16 sh;
    UInt32 lg;

    switch ((char)type->type) {
        case TYPEINT:
            switch (type->size) {
                case 1:
                    ch = (UInt8)val.lo;
                    memcpy(mem, &ch, 1);
                    break;
                case 2:
                    sh = val.lo;
                    sh = CTool_EndianConvertWord16(sh);
                    memcpy(mem, &sh, 2);
                    break;
                case 4:
                    lg = CTool_EndianConvertWord32(val.lo);
                    memcpy(mem, &lg, 4);
                    break;
                case 8:
                    CTool_EndianConvertWord64(val, mem);
                    break;
                default:
                    CError_FATAL(0x2ba);
            }
            break;
        default:
            CError_FATAL(0x2be);
    }
}

CInt64 CMach_CalcIntMonadic(Type *type, SInt16 op, CInt64 val)
{
    if (Type_IsUnsigned(type)) {
        switch (type->size) {
            case 1:
                CExpr2_ConvertCInt64ToUInt8(&val);
                break;
            case 2:
                CExpr2_ConvertCInt64ToUnsignedShort(&val);
                break;
            case 4:
                CExpr2_ClearCInt64Hi(&val);
                break;
            case 8:
                break;
            default:
                CError_Internal(cmachine_filename, 0x237);
        }
        switch (op) {
            case '-':
                val = CInt64_Neg(val);
                break;
            case '~':
                val = CInt64_Inv(val);
                break;
            case '!':
                val = CInt64_Not(val);
                break;
            default:
                CError_ReportError(ERR_UNEXPECTED_TOKEN);
        }
        switch (type->size) {
            case 1:
                CExpr2_ConvertCInt64ToUInt8(&val);
                break;
            case 2:
                CExpr2_ConvertCInt64ToUnsignedShort(&val);
                break;
            case 4:
                CExpr2_ClearCInt64Hi(&val);
                break;
            case 8:
                break;
        }
    } else {
        switch (type->size) {
            case 1:
                CExpr2_SignExtendSignedChar(&val);
                break;
            case 2:
                CExpr2_SignExtendShort(&val);
                break;
            case 4:
                CExpr2_SignExtendCInt64(&val);
                break;
            case 8:
                break;
            default:
                CError_Internal(cmachine_filename, 0x255);
        }
        switch (op) {
            case '-':
                val = CInt64_Neg(val);
                break;
            case '~':
                val = CInt64_Inv(val);
                break;
            case '!':
                val = CInt64_Not(val);
                break;
            default:
                CError_ReportError(ERR_UNEXPECTED_TOKEN);
        }
        switch (type->size) {
            case 1:
                CExpr2_SignExtendSignedChar(&val);
                break;
            case 2:
                CExpr2_SignExtendShort(&val);
                break;
            case 4:
                CExpr2_SignExtendCInt64(&val);
                break;
            case 8:
                break;
        }
    }
    return val;
}

CInt64 CMach_CalcIntDiadic(Type *type, CInt64 a, SInt16 op, CInt64 b)
{
    if (Type_IsUnsigned(type)) {
        switch (type->size) {
            case 1:
                CExpr2_ConvertCInt64ToUInt8(&a);
                CExpr2_ConvertCInt64ToUInt8(&b);
                break;
            case 2:
                CExpr2_ConvertCInt64ToUnsignedShort(&a);
                CExpr2_ConvertCInt64ToUnsignedShort(&b);
                break;
            case 4:
                CExpr2_ClearCInt64Hi(&a);
                CExpr2_ClearCInt64Hi(&b);
                break;
            case 8:
                break;
            default:
                CError_FATAL(0x1be);
        }
        switch (op) {
            case '*':
                a = CInt64_MulU(a, b);
                break;
            case '/': {
                Boolean z = (b.hi == 0) && (b.lo == 0);
                if (z) {
                    CError_Warning(ERR_DIVISION_BY_0);
                } else {
                    a = CInt64_DivU(a, b);
                }
            } break;
            case '%': {
                Boolean z = (b.hi == 0) && (b.lo == 0);
                if (z) {
                    CError_Warning(ERR_DIVISION_BY_0);
                } else {
                    a = CInt64_ModU(a, b);
                }
            } break;
            case '+':
                a = CInt64_Add(a, b);
                break;
            case '-':
                a = CInt64_Sub(a, b);
                break;
            case 0x17a:
                a = CInt64_Shl(a, b);
                break;
            case 0x17b:
                a = CInt64_ShrU(a, b);
                break;
            case '<': {
                SInt32 t = CInt64_LessU(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case '>': {
                SInt32 t = CInt64_GreaterU(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x178: {
                SInt32 t = CInt64_LessEqualU(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x179: {
                SInt32 t = CInt64_GreaterEqualU(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x176: {
                SInt32 t = CInt64_Equal(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x177: {
                SInt32 t = CInt64_NotEqual(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case '&':
                a = CInt64_And(a, b);
                break;
            case '^':
                a = xor_64(a, b);
                break;
            case '|':
                a = CExpr2_BitwiseOrCInt64(a, b);
                break;
            case 0x175: {
                SInt32 t = !ISZERO64(a) && !ISZERO64(b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x174: {
                SInt32 t = !ISZERO64(a) || !ISZERO64(b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            default:
                CError_ReportError(ERR_UNEXPECTED_TOKEN);
        }
        switch (type->size) {
            case 1:
                CExpr2_ConvertCInt64ToUInt8(&a);
                break;
            case 2:
                CExpr2_ConvertCInt64ToUnsignedShort(&a);
                break;
            case 4:
                CExpr2_ClearCInt64Hi(&a);
                break;
            case 8:
                break;
        }
    } else {
        switch (type->size) {
            case 1:
                CExpr2_SignExtendSignedChar(&a);
                CExpr2_SignExtendSignedChar(&b);
                break;
            case 2:
                CExpr2_SignExtendShort(&a);
                CExpr2_SignExtendShort(&b);
                break;
            case 4:
                CExpr2_SignExtendCInt64(&a);
                CExpr2_SignExtendCInt64(&b);
                break;
            case 8:
                break;
            default:
                CError_FATAL(0x1fc);
        }
        switch (op) {
            case '*':
                a = CInt64_Mul(a, b);
                break;
            case '/': {
                Boolean z = (b.hi == 0) && (b.lo == 0);
                if (z) {
                    CError_Warning(ERR_DIVISION_BY_0);
                } else {
                    a = CInt64_Div(a, b);
                }
            } break;
            case '%': {
                Boolean z = (b.hi == 0) && (b.lo == 0);
                if (z) {
                    CError_Warning(ERR_DIVISION_BY_0);
                } else {
                    a = CInt64_Mod(a, b);
                }
            } break;
            case '+':
                a = CInt64_Add(a, b);
                break;
            case '-':
                a = CInt64_Sub(a, b);
                break;
            case 0x17a:
                a = CInt64_Shl(a, b);
                break;
            case 0x17b:
                a = CInt64_Shr(a, b);
                break;
            case '<': {
                SInt32 t = CInt64_Less(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case '>': {
                SInt32 t = CInt64_Greater(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x178: {
                SInt32 t = CInt64_LessEqual(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x179: {
                SInt32 t = CInt64_GreaterEqual(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x176: {
                SInt32 t = CInt64_Equal(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x177: {
                SInt32 t = CInt64_NotEqual(a, b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case '&':
                a = CInt64_And(a, b);
                break;
            case '^':
                a = xor_64(a, b);
                break;
            case '|':
                a = CExpr2_BitwiseOrCInt64(a, b);
                break;
            case 0x175: {
                SInt32 t = !ISZERO64(a) && !ISZERO64(b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            case 0x174: {
                SInt32 t = !ISZERO64(a) || !ISZERO64(b);
                a.lo = t;
                a.hi = (t < 0) ? -1 : 0;
            } break;
            default:
                CError_ReportError(ERR_UNEXPECTED_TOKEN);
        }
        switch (type->size) {
            case 1:
                CExpr2_SignExtendSignedChar(&a);
                break;
            case 2:
                CExpr2_SignExtendShort(&a);
                break;
            case 4:
                CExpr2_SignExtendCInt64(&a);
                break;
            case 8:
                break;
        }
    }
    return a;
}

#pragma pack(push, 2)
typedef struct MachineOptionHeader {
    unsigned int field000;
    unsigned int field004;
    unsigned int field008;
} MachineOptionHeader;
typedef struct MachineOptions {
    MachineOptionHeader header;
    unsigned char field00c;
    unsigned char field00d;
    unsigned char field00e;
    unsigned char reserved0[1];
    unsigned short field010;
    unsigned char field012;
    unsigned char field013;
    unsigned char field014;
    unsigned char field015;
    unsigned char field016;
    unsigned char field017;
    unsigned char field018;
    unsigned char field019;
    unsigned short field01a;
    unsigned short field01c;
    unsigned char field01e;
    unsigned char field01f;
    unsigned char field020;
    unsigned char field021;
    unsigned char field022;
    unsigned char reserved1[1];
    unsigned int field024;
    unsigned int field028;
    unsigned char field02c;
    unsigned char field02d;
    unsigned char reserved2[2];
    unsigned char field030;
    unsigned char reserved3[1];
    unsigned char field032;
    unsigned char field033;
    unsigned char reserved4[28];
    unsigned int field050;
    unsigned int field054;
    unsigned char field058;
    unsigned char field059;
    unsigned char field05a;
    unsigned char field05b;
    unsigned char reserved5[1];
    unsigned char field05d;
    unsigned char field05e;
    unsigned char field05f;
    unsigned char field060;
    unsigned char field061;
    unsigned char field062;
    unsigned char reserved6[1];
    unsigned char field064;
    unsigned char field065;
    unsigned char field066;
    unsigned char field067;
    unsigned char reserved7[1];
    unsigned char field069;
    unsigned char field06a;
    unsigned char field06b;
    unsigned int field06c;
    unsigned int field070;
    unsigned char field074;
    unsigned char field075;
    unsigned char field076;
    unsigned char field077;
    unsigned char field078;
    unsigned char field079;
    unsigned char reserved8[1];
    unsigned char field07b;
    unsigned char field07c;
    unsigned char field07d;
    unsigned char field07e;
    unsigned char reserved9[2];
    unsigned char field081;
    unsigned char field082;
    unsigned char field083;
    unsigned char reserved10[353];
    unsigned char field1e5;
    unsigned char reserved11[3];
    unsigned char field1e9;
    unsigned char field1ea;
    unsigned char field1eb;
    unsigned char field1ec;
    unsigned char field1ed;
    unsigned char reserved12[70];
    unsigned char field234;
    unsigned char reserved13[3];
    unsigned char field238;
    unsigned char field239;
    unsigned char field23a;
    unsigned char reserved14[6];
    unsigned char field241;
    unsigned char reserved15[4];
    unsigned char field246;
    unsigned char field247;
    unsigned char field248;
    unsigned char reserved16[1];
    unsigned char field24a;
    unsigned char field24b;
    unsigned char field24c;
    unsigned char field24d;
    unsigned char field24e;
    unsigned char field24f;
    unsigned char field250;
    unsigned char field251;
    unsigned char field252;
    unsigned char field253;
    unsigned char field254;
    unsigned char field255;
    unsigned char field256;
    unsigned char field257;
    unsigned char field258;
    unsigned char field259;
    unsigned char field25a;
    unsigned char field25b;
    unsigned char field25c;
    unsigned char field25d;
    unsigned char field25e;
    unsigned char field25f;
    unsigned char field260;
    unsigned char field261;
    unsigned char field262;
    unsigned char field263;
    unsigned char field264;
    unsigned char field265;
    unsigned char field266;
    unsigned char field267;
    unsigned char field268;
    unsigned char field269;
    unsigned char field26a;
    unsigned char field26b;
    unsigned char field26c;
    unsigned char field26d;
    unsigned char field26e;
    unsigned char field26f;
    unsigned char field270;
    unsigned char field271;
    unsigned char reserved17[1];
    unsigned char field273;
    unsigned char field274;
    unsigned char field275;
    unsigned char field276;
    unsigned char field277;
    unsigned char field278;
    unsigned char field279;
    unsigned char field27a;
    unsigned char field27b;
    unsigned char field27c;
    unsigned char field27d;
    unsigned char field27e;
    unsigned char field27f;
    unsigned char field280;
    unsigned char field281;
    unsigned char field282;
    unsigned char field283;
    unsigned char field284;
    unsigned char field285;
    unsigned char field286;
    unsigned char field287;
    unsigned char field288;
    unsigned char field289;
    unsigned char field28a;
    unsigned char field28b;
    unsigned char field28c;
    unsigned char field28d;
    unsigned char field28e;
    unsigned char reserved18[14];
    unsigned char field29d;
} MachineOptions;
#pragma pack(pop)
#pragma pack(push, 2)
typedef struct MachineBackEndOptions {
    MachineOptionHeader header;
    unsigned char field00c;
    unsigned char field00d;
    unsigned char field00e;
    unsigned char field00f;
    unsigned char field010;
    unsigned char field011;
    unsigned char field012;
    unsigned char field013;
    unsigned char field014;
    unsigned char field015;
    unsigned char field016;
    unsigned char field017;
    unsigned char field018;
    unsigned char field019;
    unsigned char field01a;
    unsigned char field01b;
    unsigned char field01c;
    unsigned char field01d;
    unsigned char field01e;
    unsigned char field01f;
    unsigned char field020;
    unsigned char field021;
    unsigned char field022;
    unsigned char field023;
    unsigned char field024;
    unsigned char field025;
    unsigned char field026;
    unsigned char field027;
    unsigned char field028;
    unsigned char field029;
    unsigned char field02a;
    unsigned char field02b;
    unsigned char field02c;
    unsigned char field02d;
    unsigned char field02e;
    unsigned char field02f;
    unsigned char field030;
    unsigned char field031;
    unsigned char field032;
    unsigned char field033;
    unsigned char field034;
    unsigned char field035;
    unsigned char field036;
    unsigned char field037;
    unsigned char field038;
    unsigned char field039;
    unsigned char field03a;
    unsigned char field03b;
    unsigned char field03c;
    unsigned char field03d;
    unsigned char field03e;
    unsigned char field03f;
    unsigned char field040;
    unsigned char field041;
    unsigned char field042;
    unsigned char field043;
    unsigned char field044;
    unsigned char field045;
    unsigned char field046;
    unsigned char field047;
    unsigned char field048;
    unsigned char field049;
    unsigned char field04a;
    unsigned char field04b;
    unsigned char field04c;
    unsigned char field04d;
    unsigned char field04e;
    unsigned char field04f;
    unsigned char field050;
    unsigned char field051;
    unsigned char field052;
    unsigned char field053;
    unsigned char field054;
    unsigned char field055;
    unsigned char field056;
    unsigned char field057;
    unsigned char field058;
    unsigned char field059;
    unsigned char field05a;
    unsigned char field05b;
    unsigned char field05c;
    unsigned char field05d;
    unsigned char field05e;
    unsigned char field05f;
    unsigned char field060;
    unsigned char field061;
    unsigned short field062;
    unsigned char field064;
    unsigned char field065;
    unsigned char field066;
    unsigned char field067;
    unsigned char field068;
    unsigned char field069;
    unsigned char field06a;
    unsigned char field06b;
    unsigned short field06c;
    unsigned short field06e;
    unsigned char field070;
    unsigned char field071;
    unsigned char field072;
    unsigned char field073;
    unsigned char field074;
    unsigned char reserved0[1];
    unsigned int field076;
    unsigned int field07a;
    unsigned char field07e;
    unsigned char field07f;
    unsigned char reserved1[2];
    unsigned char field082;
    unsigned char reserved2[1];
    unsigned char field084;
    unsigned char field085;
    unsigned int field086;
    unsigned int field08a;
    unsigned char field08e;
    unsigned char field08f;
    unsigned char field090;
    unsigned char field091;
    unsigned char field092;
    unsigned char field093;
    unsigned char field094;
    unsigned char field095;
    unsigned char field096;
    unsigned char field097;
    unsigned char field098;
    unsigned char field099;
    unsigned char field09a;
    unsigned char field09b;
    unsigned char reserved3[1];
    unsigned char field09d;
    unsigned char field09e;
    unsigned char field09f;
    unsigned int field0a0;
    unsigned int field0a4;
    unsigned char field0a8;
    unsigned char field0a9;
    unsigned char field0aa;
    unsigned char field0ab;
    unsigned char field0ac;
    unsigned char field0ad;
    unsigned char field0ae;
    unsigned char field0af;
    unsigned char field0b0;
    unsigned char field0b1;
    unsigned char field0b2;
    unsigned char field0b3;
    unsigned char field0b4;
} MachineBackEndOptions;
#pragma pack(pop)
extern MachineOptions machineOptions;
void CMach_GetBackEndOptions(MachineBackEndOptions *options)
{
    options->field00c = machineOptions.field246;
    options->field00d = machineOptions.field247;
    options->field00e = machineOptions.field248;
    options->field010 = machineOptions.field238;
    options->field011 = machineOptions.field239;
    options->field012 = machineOptions.field23a;
    options->field013 = machineOptions.field241;
    options->field00f = machineOptions.field234;
    options->field014 = machineOptions.field29d;
    options->field015 = machineOptions.field1e5;
    options->field016 = machineOptions.field1e9;
    options->field017 = machineOptions.field1ea;
    options->field018 = machineOptions.field1eb;
    options->field019 = machineOptions.field1ec;
    options->field01a = machineOptions.field1ed;
    options->field01b = machineOptions.field24a;
    options->field01c = machineOptions.field24b;
    options->field01d = machineOptions.field24c;
    options->field01e = machineOptions.field24d;
    options->field01f = machineOptions.field24e;
    options->field020 = machineOptions.field24f;
    options->field021 = machineOptions.field250;
    options->field022 = machineOptions.field251;
    options->field023 = machineOptions.field252;
    options->field024 = machineOptions.field253;
    options->field025 = machineOptions.field254;
    options->field026 = machineOptions.field255;
    options->field027 = machineOptions.field256;
    options->field028 = machineOptions.field257;
    options->field029 = machineOptions.field258;
    options->field02a = machineOptions.field259;
    options->field02b = machineOptions.field25a;
    options->field02c = machineOptions.field25b;
    options->field02d = machineOptions.field25c;
    options->field02e = machineOptions.field25d;
    options->field02f = machineOptions.field25e;
    options->field030 = machineOptions.field25f;
    options->field031 = machineOptions.field260;
    options->field032 = machineOptions.field261;
    options->field033 = machineOptions.field262;
    options->field034 = machineOptions.field263;
    options->field035 = machineOptions.field264;
    options->field036 = machineOptions.field265;
    options->field037 = machineOptions.field266;
    options->field038 = machineOptions.field267;
    options->field039 = machineOptions.field268;
    options->field03a = machineOptions.field269;
    options->field03b = machineOptions.field26a;
    options->field03c = machineOptions.field26b;
    options->field03d = machineOptions.field26c;
    options->field03e = machineOptions.field26d;
    options->field03f = machineOptions.field26e;
    options->field040 = machineOptions.field26f;
    options->field041 = machineOptions.field270;
    options->field042 = machineOptions.field271;
    options->field043 = machineOptions.field273;
    options->field044 = machineOptions.field274;
    options->field045 = machineOptions.field275;
    options->field046 = machineOptions.field276;
    options->field047 = machineOptions.field277;
    options->field048 = machineOptions.field278;
    options->field049 = machineOptions.field279;
    options->field04a = machineOptions.field27a;
    options->field04b = machineOptions.field27b;
    options->field04c = machineOptions.field27c;
    options->field04d = machineOptions.field27d;
    options->field04e = machineOptions.field27e;
    options->field04f = machineOptions.field27f;
    options->field050 = machineOptions.field280;
    options->field051 = machineOptions.field281;
    options->field052 = machineOptions.field282;
    options->field053 = machineOptions.field283;
    options->field054 = machineOptions.field284;
    options->field055 = machineOptions.field285;
    options->field056 = machineOptions.field286;
    options->field057 = machineOptions.field287;
    options->field058 = machineOptions.field288;
    options->field059 = machineOptions.field289;
    options->field05a = machineOptions.field28a;
    options->field05b = machineOptions.field28b;
    options->field05c = machineOptions.field28c;
    options->field05d = machineOptions.field28d;
    options->field05e = machineOptions.field28e;
    options->header = machineOptions.header;
    options->field05f = machineOptions.field00c;
    options->field060 = machineOptions.field00d;
    options->field061 = machineOptions.field00e;
    options->field062 = machineOptions.field010;
    options->field064 = machineOptions.field012;
    options->field065 = machineOptions.field013;
    options->field066 = machineOptions.field014;
    options->field067 = machineOptions.field015;
    options->field068 = machineOptions.field016;
    options->field069 = machineOptions.field017;
    options->field06a = machineOptions.field018;
    options->field06b = machineOptions.field019;
    options->field06c = machineOptions.field01a;
    options->field06e = machineOptions.field01c;
    options->field070 = machineOptions.field01e;
    options->field071 = machineOptions.field01f;
    options->field072 = machineOptions.field020;
    options->field073 = machineOptions.field021;
    options->field074 = machineOptions.field022;
    options->field076 = machineOptions.field024;
    options->field07a = machineOptions.field028;
    options->field07e = machineOptions.field02c;
    options->field07f = machineOptions.field02d;
    options->field082 = machineOptions.field030;
    options->field084 = machineOptions.field032;
    options->field085 = machineOptions.field033;
    options->field086 = machineOptions.field050;
    options->field08a = machineOptions.field054;
    options->field08e = machineOptions.field058;
    options->field08f = machineOptions.field059;
    options->field090 = machineOptions.field05a;
    options->field091 = machineOptions.field05b;
    options->field092 = machineOptions.field05d;
    options->field093 = machineOptions.field05e;
    options->field094 = machineOptions.field05f;
    options->field095 = machineOptions.field060;
    options->field096 = machineOptions.field061;
    options->field097 = machineOptions.field062;
    options->field098 = machineOptions.field064;
    options->field099 = machineOptions.field065;
    options->field09a = machineOptions.field066;
    options->field09b = machineOptions.field067;
    options->field0a0 = machineOptions.field06c;
    options->field0a4 = machineOptions.field070;
    options->field09d = machineOptions.field069;
    options->field09e = machineOptions.field06a;
    options->field09f = machineOptions.field06b;
    options->field0a0 = machineOptions.field06c;
    options->field0a8 = machineOptions.field074;
    options->field0a9 = machineOptions.field075;
    options->field0aa = machineOptions.field076;
    options->field0ab = machineOptions.field077;
    options->field0ac = machineOptions.field078;
    options->field0ad = machineOptions.field079;
    options->field0ae = machineOptions.field07b;
    options->field0af = machineOptions.field07c;
    options->field0b0 = machineOptions.field07d;
    options->field0b1 = machineOptions.field07e;
    options->field0b2 = machineOptions.field081;
    options->field0b3 = machineOptions.field082;
    options->field0b4 = machineOptions.field083;
}
extern void *machineRuntimeName_0069a162;
extern void *machineRuntimeName_0069a198;
extern void *machineRuntimeName_0069a1ce;
extern void *machineRuntimeName_0069a174;
extern void *machineRuntimeName_0069a1aa;
extern void *machineRuntimeName_0069a1e0;
extern void *machineRuntimeName_0069a186;
extern void *machineRuntimeName_0069a1bc;
extern void *machineRuntimeName_0069a1f2;
extern void *machineRuntimeName_0069a204;
extern void *machineRuntimeName_0069a216;
extern void *machineRuntimeName_00699de0;
extern void *machineRuntimeName_00699dcc;
extern void *machineRuntimeName_00699db8;
extern void *machineRuntimeName_00699da4;
extern void *machineRuntimeName_00699d90;
extern void *machineRuntimeName_00699d7c;
extern void *machineRuntimeName_00699d68;
extern void *machineRuntimeName_00699d54;
extern void *machineRuntimeName_00699d40;
extern void *machineRuntimeName_00699d2c;
extern void *machineRuntimeName_00699d18;
extern void *machineRuntimeName_00699d04;
extern void *machineRuntimeName_00699cf0;
extern void *machineRuntimeName_00699cdc;
extern void *machineRuntimeName_00699cc8;
extern void *machineRuntimeName_00699cb4;
extern void *machineRuntimeName_00699f20;
extern void *machineRuntimeName_00699f0c;
extern void *machineRuntimeName_00699ef8;
extern void *machineRuntimeName_00699ee4;
extern void *machineRuntimeName_00699ed0;
extern void *machineRuntimeName_00699ebc;
extern void *machineRuntimeName_00699ea8;
extern void *machineRuntimeName_00699e94;
extern void *machineRuntimeName_00699e80;
extern void *machineRuntimeName_00699e6c;
extern void *machineRuntimeName_00699e58;
extern void *machineRuntimeName_00699e44;
extern void *machineRuntimeName_00699e30;
extern void *machineRuntimeName_00699e1c;
extern void *machineRuntimeName_00699e08;
extern void *machineRuntimeName_00699df4;
extern void *machineRuntimeName_00699fc0;
extern void *machineRuntimeName_00699fac;
extern void *machineRuntimeName_00699f98;
extern void *machineRuntimeName_00699f84;
extern void *machineRuntimeName_00699f70;
extern void *machineRuntimeName_00699f5c;
extern void *machineRuntimeName_00699f48;
extern void *machineRuntimeName_00699f34;
extern void *machineRuntimeName_0069a060;
extern void *machineRuntimeName_0069a04c;
extern void *machineRuntimeName_0069a038;
extern void *machineRuntimeName_0069a024;
extern void *machineRuntimeName_0069a010;
extern void *machineRuntimeName_00699ffc;
extern void *machineRuntimeName_00699fe8;
extern void *machineRuntimeName_00699fd4;
extern void *machineRuntimeName_0069a0b0;
extern void *machineRuntimeName_0069a09c;
extern void *machineRuntimeName_0069a088;
extern void *machineRuntimeName_0069a074;
extern void *machineRuntimeName_0069a100;
extern void *machineRuntimeName_0069a0ec;
extern void *machineRuntimeName_0069a0d8;
extern void *machineRuntimeName_0069a0c4;
extern void *machineRuntimeName_0069a150;
extern void *machineRuntimeName_0069a13c;
extern void *machineRuntimeName_0069a128;
extern void *machineRuntimeName_0069a114;
extern void *GetHashNameNode(const char *);
void CMach_ReInitRuntimeObjects(void)
{
    void *name1;
    void *name2;
    void *name3;
    void *name4;
    void *name5;
    void *name6;
    void *name7;
    void *name8;
    void *name9;
    void *name10;
    void *name11;
    void *name12;
    void *name13;
    void *name14;
    void *name15;
    void *name16;
    void *name17;
    void *name18;
    void *name19;
    void *name20;
    void *name21;
    void *name22;
    void *name23;
    void *name24;
    void *name25;
    void *name26;
    void *name27;
    name1 = GetHashNameNode("[0]");
    name2 = GetHashNameNode("[1]");
    name3 = GetHashNameNode("[2]");
    name4 = GetHashNameNode("[3]");
    name5 = GetHashNameNode("[4]");
    name6 = GetHashNameNode("[5]");
    name7 = GetHashNameNode("[6]");
    name8 = GetHashNameNode("[7]");
    name9 = GetHashNameNode("[8]");
    name10 = GetHashNameNode("[9]");
    name11 = GetHashNameNode("[10]");
    name12 = GetHashNameNode("[11]");
    name13 = GetHashNameNode("[12]");
    name14 = GetHashNameNode("[13]");
    name15 = GetHashNameNode("[14]");
    name16 = GetHashNameNode("[15]");
    name17 = GetHashNameNode("vector unsigned char");
    name18 = GetHashNameNode("vector unsigned short");
    name19 = GetHashNameNode("vector unsigned int");
    name20 = GetHashNameNode("vector signed char");
    name21 = GetHashNameNode("vector signed short");
    name22 = GetHashNameNode("vector signed int");
    name23 = GetHashNameNode("vector bool char");
    name24 = GetHashNameNode("vector bool short");
    name25 = GetHashNameNode("vector bool int");
    name26 = GetHashNameNode("vector float");
    name27 = GetHashNameNode("vector pixel");
    machineRuntimeName_0069a162 = name17;
    machineRuntimeName_0069a198 = name18;
    machineRuntimeName_0069a1ce = name19;
    machineRuntimeName_0069a174 = name20;
    machineRuntimeName_0069a1aa = name21;
    machineRuntimeName_0069a1e0 = name22;
    machineRuntimeName_0069a186 = name23;
    machineRuntimeName_0069a1bc = name24;
    machineRuntimeName_0069a1f2 = name25;
    machineRuntimeName_0069a204 = name26;
    machineRuntimeName_0069a216 = name27;
    machineRuntimeName_00699de0 = name1;
    machineRuntimeName_00699dcc = name2;
    machineRuntimeName_00699db8 = name3;
    machineRuntimeName_00699da4 = name4;
    machineRuntimeName_00699d90 = name5;
    machineRuntimeName_00699d7c = name6;
    machineRuntimeName_00699d68 = name7;
    machineRuntimeName_00699d54 = name8;
    machineRuntimeName_00699d40 = name9;
    machineRuntimeName_00699d2c = name10;
    machineRuntimeName_00699d18 = name11;
    machineRuntimeName_00699d04 = name12;
    machineRuntimeName_00699cf0 = name13;
    machineRuntimeName_00699cdc = name14;
    machineRuntimeName_00699cc8 = name15;
    machineRuntimeName_00699cb4 = name16;
    machineRuntimeName_00699f20 = name1;
    machineRuntimeName_00699f0c = name2;
    machineRuntimeName_00699ef8 = name3;
    machineRuntimeName_00699ee4 = name4;
    machineRuntimeName_00699ed0 = name5;
    machineRuntimeName_00699ebc = name6;
    machineRuntimeName_00699ea8 = name7;
    machineRuntimeName_00699e94 = name8;
    machineRuntimeName_00699e80 = name9;
    machineRuntimeName_00699e6c = name10;
    machineRuntimeName_00699e58 = name11;
    machineRuntimeName_00699e44 = name12;
    machineRuntimeName_00699e30 = name13;
    machineRuntimeName_00699e1c = name14;
    machineRuntimeName_00699e08 = name15;
    machineRuntimeName_00699df4 = name16;
    machineRuntimeName_00699fc0 = name1;
    machineRuntimeName_00699fac = name2;
    machineRuntimeName_00699f98 = name3;
    machineRuntimeName_00699f84 = name4;
    machineRuntimeName_00699f70 = name5;
    machineRuntimeName_00699f5c = name6;
    machineRuntimeName_00699f48 = name7;
    machineRuntimeName_00699f34 = name8;
    machineRuntimeName_0069a060 = name1;
    machineRuntimeName_0069a04c = name2;
    machineRuntimeName_0069a038 = name3;
    machineRuntimeName_0069a024 = name4;
    machineRuntimeName_0069a010 = name5;
    machineRuntimeName_00699ffc = name6;
    machineRuntimeName_00699fe8 = name7;
    machineRuntimeName_00699fd4 = name8;
    machineRuntimeName_0069a0b0 = name1;
    machineRuntimeName_0069a09c = name2;
    machineRuntimeName_0069a088 = name3;
    machineRuntimeName_0069a074 = name4;
    machineRuntimeName_0069a100 = name1;
    machineRuntimeName_0069a0ec = name2;
    machineRuntimeName_0069a0d8 = name3;
    machineRuntimeName_0069a0c4 = name4;
    machineRuntimeName_0069a150 = name1;
    machineRuntimeName_0069a13c = name2;
    machineRuntimeName_0069a128 = name3;
    machineRuntimeName_0069a114 = name4;
}

void fn_004e0df0(const MachineBackEndOptions *options)
{
    machineOptions.header = options->header;
    machineOptions.field246 = options->field00c;
    machineOptions.field247 = options->field00d;
    machineOptions.field248 = options->field00e;
    machineOptions.field238 = options->field010;
    machineOptions.field239 = options->field011;
    machineOptions.field23a = options->field012;
    machineOptions.field241 = options->field013;
    machineOptions.field234 = options->field00f;
    machineOptions.field29d = options->field014;
    machineOptions.field1e5 = options->field015;
    machineOptions.field1e9 = options->field016;
    machineOptions.field1ea = options->field017;
    machineOptions.field1eb = options->field018;
    machineOptions.field1ec = options->field019;
    machineOptions.field1ed = options->field01a;
    machineOptions.field24a = options->field01b;
    machineOptions.field24b = options->field01c;
    machineOptions.field24c = options->field01d;
    machineOptions.field24d = options->field01e;
    machineOptions.field24e = options->field01f;
    machineOptions.field24f = options->field020;
    machineOptions.field250 = options->field021;
    machineOptions.field251 = options->field022;
    machineOptions.field252 = options->field023;
    machineOptions.field253 = options->field024;
    machineOptions.field254 = options->field025;
    machineOptions.field255 = options->field026;
    machineOptions.field256 = options->field027;
    machineOptions.field257 = options->field028;
    machineOptions.field258 = options->field029;
    machineOptions.field259 = options->field02a;
    machineOptions.field25a = options->field02b;
    machineOptions.field25b = options->field02c;
    machineOptions.field25c = options->field02d;
    machineOptions.field25d = options->field02e;
    machineOptions.field25e = options->field02f;
    machineOptions.field25f = options->field030;
    machineOptions.field260 = options->field031;
    machineOptions.field261 = options->field032;
    machineOptions.field262 = options->field033;
    machineOptions.field263 = options->field034;
    machineOptions.field264 = options->field035;
    machineOptions.field265 = options->field036;
    machineOptions.field266 = options->field037;
    machineOptions.field267 = options->field038;
    machineOptions.field268 = options->field039;
    machineOptions.field269 = options->field03a;
    machineOptions.field26a = options->field03b;
    machineOptions.field26b = options->field03c;
    machineOptions.field26c = options->field03d;
    machineOptions.field26d = options->field03e;
    machineOptions.field26e = options->field03f;
    machineOptions.field26f = options->field040;
    machineOptions.field270 = options->field041;
    machineOptions.field271 = options->field042;
    machineOptions.field273 = options->field043;
    machineOptions.field274 = options->field044;
    machineOptions.field275 = options->field045;
    machineOptions.field276 = options->field046;
    machineOptions.field277 = options->field047;
    machineOptions.field278 = options->field048;
    machineOptions.field279 = options->field049;
    machineOptions.field27a = options->field04a;
    machineOptions.field27b = options->field04b;
    machineOptions.field27c = options->field04c;
    machineOptions.field27d = options->field04d;
    machineOptions.field27e = options->field04e;
    machineOptions.field27f = options->field04f;
    machineOptions.field280 = options->field050;
    machineOptions.field281 = options->field051;
    machineOptions.field282 = options->field052;
    machineOptions.field283 = options->field053;
    machineOptions.field284 = options->field054;
    machineOptions.field285 = options->field055;
    machineOptions.field286 = options->field056;
    machineOptions.field287 = options->field057;
    machineOptions.field288 = options->field058;
    machineOptions.field289 = options->field059;
    machineOptions.field28a = options->field05a;
    machineOptions.field28b = options->field05b;
    machineOptions.field28c = options->field05c;
    machineOptions.field28d = options->field05d;
    machineOptions.field28e = options->field05e;
    machineOptions.field00c = options->field05f;
    machineOptions.field00d = options->field060;
    machineOptions.field00e = options->field061;
    machineOptions.field010 = options->field062;
    machineOptions.field012 = options->field064;
    machineOptions.field013 = options->field065;
    machineOptions.field014 = options->field066;
    machineOptions.field015 = options->field067;
    machineOptions.field016 = options->field068;
    machineOptions.field017 = options->field069;
    machineOptions.field018 = options->field06a;
    machineOptions.field019 = options->field06b;
    machineOptions.field01a = options->field06c;
    machineOptions.field01c = options->field06e;
    machineOptions.field01e = options->field070;
    machineOptions.field01f = options->field071;
    machineOptions.field020 = options->field072;
    machineOptions.field021 = options->field073;
    machineOptions.field022 = options->field074;
    machineOptions.field024 = options->field076;
    machineOptions.field028 = options->field07a;
    machineOptions.field02c = options->field07e;
    machineOptions.field02d = options->field07f;
    machineOptions.field030 = options->field082;
    machineOptions.field032 = options->field084;
    machineOptions.field033 = options->field085;
    machineOptions.field050 = options->field086;
    machineOptions.field054 = options->field08a;
    machineOptions.field058 = options->field08e;
    machineOptions.field059 = options->field08f;
    machineOptions.field05a = options->field090;
    machineOptions.field05b = options->field091;
    machineOptions.field05d = options->field092;
    machineOptions.field05e = options->field093;
    machineOptions.field05f = options->field094;
    machineOptions.field060 = options->field095;
    machineOptions.field061 = options->field096;
    machineOptions.field062 = options->field097;
    machineOptions.field064 = options->field098;
    machineOptions.field065 = options->field099;
    machineOptions.field066 = options->field09a;
    machineOptions.field067 = options->field09b;
    machineOptions.field06c = options->field0a0;
    machineOptions.field070 = options->field0a4;
    machineOptions.field069 = options->field09d;
    machineOptions.field06a = options->field09e;
    machineOptions.field06b = options->field09f;
    machineOptions.field06c = options->field0a0;
    machineOptions.field074 = options->field0a8;
    machineOptions.field075 = options->field0a9;
    machineOptions.field076 = options->field0aa;
    machineOptions.field077 = options->field0ab;
    machineOptions.field078 = options->field0ac;
    machineOptions.field079 = options->field0ad;
    machineOptions.field07b = options->field0ae;
    machineOptions.field07c = options->field0af;
    machineOptions.field07d = options->field0b0;
    machineOptions.field07e = options->field0b1;
    machineOptions.field081 = options->field0b2;
    machineOptions.field082 = options->field0b3;
    machineOptions.field083 = options->field0b4;
}
