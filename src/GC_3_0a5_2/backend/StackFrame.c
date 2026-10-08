/* Native StackFrame.c records remain private while backend callers migrate. */
#include "compiler/common.h"
#include <stddef.h>
#include <string.h>
#pragma pack(push, 2)
typedef struct NativePCBlock NativePCBlock;
typedef struct NativePCInstruction NativePCInstruction;
typedef struct NativePCLabel NativePCLabel;
typedef struct NativePCObject {
    UInt8 kind, access, datatype, unknown03;
    UInt32 unknown04;
    void *nameSpace, *name;
    struct NativeFrameType *type;
    UInt32 qualifiers;
    UInt16 storageClass, flags;
    UInt8 unknown1c[0x24];
    void *localInfo;
    UInt8 unknown44[4];
    SInt32 displacement;
    UInt8 unknown4c[0x14];
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

#pragma pack(push, 2)
typedef struct NativeFrameType {
    UInt8 kind, unknown01;
    SInt32 size;
    UInt8 integral, unknown07[9];
    SInt8 vectorKind;
} NativeFrameType;
typedef struct NativeFrameVarInfo {
    UInt8 unknown00[9], used, unknown0a[4], flags, regClass;
    SInt16 reg, regHi;
} NativeFrameVarInfo;
typedef struct NativeFrameObjectList {
    struct NativeFrameObjectList *next;
    NativePCObject *object;
} NativeFrameObjectList;
typedef struct NativeFrameABI { SInt32 linkage, minimumParameters, minimumFrame, unknown0c, pointerSize, unknown14[3]; } NativeFrameABI;
#pragma pack(pop)
extern void CError_Internal(const char *, int);
extern NativeFrameVarInfo *Registers_GetVarInfo(NativePCObject *);
extern int CMach_AllocationAlignment(NativeFrameType *, UInt32), CMach_ArgumentAlignment(NativeFrameType *);
extern NativePCBlock *pcbasicblocks;
extern NativePCInstruction *emitpcode(SInt16, ...), *makepcode(SInt16, ...);
extern void appendpcode(NativePCBlock *, NativePCInstruction *), deletepcode(NativePCInstruction *);
extern void *galloc(SInt32), *lalloc(SInt32), *galloc2(SInt32);
extern void memclrw(void *, SInt32);
extern NativeFrameABI *fn_00716cf0;
extern SInt32 fn_00716cec;
extern UInt8 fn_0070f008, fn_00725dfb, fn_00725ee1;
extern SInt32 fn_00710394, fn_00716eb0;
extern SInt16 fn_00716ebe, fn_007172bc;
extern NativePCBlock *fn_0071071c;
extern UInt8 fn_006771c8[];
extern NativePCInstruction *make_load_gpr(void *, SInt16, SInt16, SInt32);
NativePCInstruction *storevrsave, *loadvrsave, *align_instr2, *align_instr1, *setup_caller_sp;
SInt16 vrsave_register;
UInt8 compressing_data_area, has_varargs, dynamic_align_stack;
NativePCObject *dummylocal;
SInt32 frame_size_estimate, frame_size;
SInt32 fn_006e5d76, fn_006e5d7a, fn_006e5d7e, fn_006e5d82, fn_006e5d86;
SInt32 nonvolatile_save_size, fn_006e5d8e, fn_006e5d92;
SInt32 fn_006e5d96[5], fn_006e5daa[5], fn_006e5dbe, fn_006e5dc2, fn_006e5dc6[5], fn_006e5dda[5], fn_006e5dee[5];
NativeFrameObjectList *local_objects_tail[3], *local_objects[3];
UInt8 fn_006e5e1a;
SInt32 large_data_far_size, large_data_near_size, local_data_limit, local_data_size;
SInt32 parameter_area_size_estimate, parameter_area_size, fn_006e5e34, fn_006e5e38;
SInt32 needed_abi_alignment, frame_alignment, in_param_alignment, in_parameter_size, out_param_alignment;
static inline int native_in_parameter_area(NativePCObject *object)
{
    NativeFrameVarInfo *info = Registers_GetVarInfo(object);
    if (info && (info->flags & 1)) return 1;
    return 0;
}
SInt32 local_offset_32(NativePCObject *object);
int align_bits(int alignment, UInt8 doubleword);

void no_frame_for_asm(void) { frame_size = 0; }

int align_bits(int alignment, UInt8 doubleword)
{
    int top = doubleword ? 32 : 31;
    switch (alignment) {
        case 2: return top - 1;
        case 4: return top - 2;
        case 8: return top - 3;
        case 16: return top - 4;
        case 32: return top - 5;
        case 64: return top - 6;
        case 128: return top - 7;
        case 256: return top - 8;
        case 512: return top - 9;
        case 1024: return top - 10;
        case 2048: return top - 11;
        case 4096: return top - 12;
        case 8192: return top - 13;
        default: CError_Internal("StackFrame.c", 3700); return top - 4;
    }
}

int update_frame_align(void)
{
    int alignment = frame_alignment;
    if (fn_0070f008) alignment = (alignment + 15) & ~15;
    if (fn_006e5e38) {
        if (fn_006e5e38 != alignment) CError_Internal("StackFrame.c", 3787);
    } else fn_006e5e38 = alignment;
    return align_bits(alignment, 0);
}

UInt8 can_add_displ_to_local(NativePCObject *object, int displacement)
{
    SInt32 narrowed;
    if (object->datatype == 1) {
        narrowed = (SInt16)local_offset_32(object);
        if (local_offset_32(object) == narrowed) {
            narrowed = (SInt16)(local_offset_32(object) + displacement);
            if (local_offset_32(object) + displacement == narrowed) return 1;
        }
    }
    return 0;
}

static inline SInt32 native_local_base_register(NativePCObject *object)
{
    if (native_in_parameter_area(object)) {
        if (fn_00710394 && fn_00716ebe == -1) {
            SInt32 reg = fn_00716eb0++;
            fn_00716ebe = reg;
            setup_caller_sp = make_load_gpr(fn_006771c8, fn_00716ebe, 1, 0);
            setup_caller_sp->flags |= 0x80;
            appendpcode(fn_0071071c, setup_caller_sp);
        }
        return fn_00716ebe;
    }
    return fn_007172bc;
}

SInt32 local_base_register(NativePCObject *object) { return native_local_base_register(object); }

SInt32 local_offset_32(NativePCObject *object)
{
    SInt32 alignment, value, base;
    if (native_in_parameter_area(object)) alignment = CMach_ArgumentAlignment(object->type);
    else alignment = CMach_AllocationAlignment(object->type, object->qualifiers);
    value = object->displacement;
    if (value > 32767) value = 32768 - value - ((object->type->size + (SInt16)alignment - 1) & ~((SInt16)alignment - 1));
    if (native_in_parameter_area(object)) {
        if (native_local_base_register(object) == fn_007172bc) {
            if (frame_size) base = fn_00716cf0->linkage + fn_00716cec;
            else base = fn_00716cf0->linkage;
        } else base = fn_00716cf0->linkage;
    } else {
        if (fn_00725dfb) base = ((fn_006e5e34 + frame_alignment - 1) & ~(frame_alignment - 1)) - fn_006e5e34;
        else if (fn_006e5e1a) base = parameter_area_size;
        else base = parameter_area_size_estimate;
        if (frame_size || dynamic_align_stack) base += fn_006e5e34;
        else base -= fn_00716cec;
    }
    return value + base;
}

SInt32 fn_005872d0(NativePCObject *object)
{
    SInt32 value = local_offset_32(object);
    if ((value & 3) || value / 4 != ((value / 4) & 0xfff)) CError_Internal("StackFrame.c", 3580);
    return value;
}
UInt8 fn_00587320(NativePCObject *object)
{
    SInt32 value = local_offset_32(object);
    return value == (value & 0xfff);
}
SInt32 fn_00587340(NativePCObject *object)
{
    SInt32 value = local_offset_32(object);
    if (value != (value & 0xfff)) CError_Internal("StackFrame.c", 3531);
    return value;
}
UInt8 local_is_16bit_offset(NativePCObject *object)
{
    SInt32 value = local_offset_32(object);
    return value == (SInt16)value;
}
SInt32 local_offset_16(NativePCObject *object)
{
    SInt32 value, result;
    result = (SInt16)(value = local_offset_32(object));
    if (value != result) CError_Internal("StackFrame.c", 3493);
    return result;
}
SInt32 local_offset_ha(NativePCObject *object, SInt32 addend)
{
    SInt32 value = local_offset_32(object) + addend;
    return (SInt16)((value >> 16) + ((value >> 15) & 1));
}
SInt32 local_offset_lo(NativePCObject *object, SInt32 addend)
{
    return (SInt16)(local_offset_32(object) + addend);
}
void update_out_param_align(SInt32 alignment)
{
    if (frame_alignment < alignment) frame_alignment = alignment;
    if (needed_abi_alignment < alignment) needed_abi_alignment = alignment;

}
SInt32 estimate_out_param_size(SInt32 size)
{
    if (parameter_area_size_estimate < size) parameter_area_size_estimate = size;
    return size;
}
void update_out_param_size(SInt32 size)
{
    if (size < fn_00716cf0->minimumParameters) size = fn_00716cf0->minimumParameters;
    if (parameter_area_size < size) parameter_area_size = size;
}
UInt8 needs_frame(void)
{
    return frame_size > fn_00716cf0->minimumFrame || fn_00725ee1 != 0;
}
SInt32 out_param_displ_to_offset(SInt32 displacement)
{
    return displacement + fn_00716cf0->linkage;
}
extern UInt8 fn_0070f002, fn_0070f04c, fn_0070f231, fn_0072605b, fn_00725ecc, fn_00726058, fn_0070eff6, fn_0070eff7, fn_00725ed7;
extern SInt16 fn_0070effa;
extern UInt16 fn_007171e0;
extern SInt32 fn_00716c8c, fn_00716c90, fn_00716c94;
extern int fn_004c07c0(void);
extern void fn_005829d0(NativePCInstruction *, NativePCInstruction *);
extern SInt32 colored_vrs_as_vrsave(NativePCBlock *);
extern NativePCBlock *fn_00710784;

UInt8 use_helper_function(SInt8 regClass)
{
    SInt32 count;
    UInt8 result = 0, eligible;
    if (fn_0070f002) return 0;
    switch (regClass) {
        case 4:
            if (fn_0070f04c && fn_004c07c0() && !fn_0072605b) {
                if (fn_00716c94) {
                    eligible = fn_00716c90 == 0 && fn_00716c8c == 0 && frame_alignment >= 16 &&
                        fn_0070f231 && fn_007171e0 == 0 && fn_0070f002 == 0 && !dynamic_align_stack &&
                        !fn_00725ecc && fn_00726058;
                    if (eligible) {
                        if (fn_0070eff6) result |= 8;
                        if (fn_0070eff7) result |= 8;
                    }
                }
                return result;
            }
            count = fn_00716c94;
            return count > 4 || (fn_0070f231 && count > 2);
        case 3:
            if (fn_0070effa == 22 && fn_0072605b) return 0;
            count = fn_00716c90;
            return count > 3 || (fn_0070f231 && count > 2);
        case 2:
            count = fn_00716c8c;
            return count > 3 || (fn_0070f231 && count > 2);
        default: CError_Internal("StackFrame.c", 3874); return 0;
    }
}

void check_dynamic_aligned_frame(void)
{
    NativePCInstruction *replacement;
    UInt8 helper;
    if (fn_00716c8c) {
        if (frame_alignment < 16) frame_alignment = 16;
        if (needed_abi_alignment < 16) needed_abi_alignment = 16;
        fn_00725ee1 = 1;
        fn_00725ed7 = 1;
    } else {
        helper = fn_00726058 || use_helper_function(3) || use_helper_function(4) || use_helper_function(2);
        if (helper && fn_007171e0 && (fn_007171e0 & 0x40)) {
            if (frame_alignment < 16) frame_alignment = 16;
            if (needed_abi_alignment < 16) needed_abi_alignment = 16;
            fn_00725ee1 = 1;
            fn_00725ed7 = 1;
        }
    }
    if (needed_abi_alignment > in_param_alignment) {
        dynamic_align_stack = 1;
        fn_00725ee1 = 1;
        fn_00725ed7 = 1;
        if (fn_00716ebe == fn_007172bc) CError_Internal("StackFrame.c", 2834);
    } else {
        dynamic_align_stack = 0;
        if (setup_caller_sp && setup_caller_sp->block) {
            replacement = makepcode(139, fn_00716ebe, fn_007172bc);
            fn_005829d0(setup_caller_sp, replacement);
            deletepcode(setup_caller_sp);
            setup_caller_sp = replacement;
        }
        fn_00716ebe = fn_007172bc;
    }
    fn_006e5d76 = 0;
    if (fn_0070f008) {
        fn_006e5d76 = colored_vrs_as_vrsave(pcbasicblocks);
        if (!fn_00725ee1 && fn_006e5d76) {
            vrsave_register = 11;
            loadvrsave = makepcode(34, 11, 1, 0, -4);
            appendpcode(fn_0071071c, loadvrsave);
            storevrsave = makepcode(49, 11, 1, 0, -4);
            appendpcode(fn_00710784, storevrsave);
        }
    }
}

SInt32 set_out_param_displ(SInt32 displacement, NativeFrameType *type, UInt8 align,
    SInt32 *output, SInt32 size)
{
    SInt32 alignment;
    if (!align) { *output = displacement; return displacement; }
    if (((type->kind == 1 && type->integral < 23) || type->kind == 4) && type->size == 8 ||
        (type->kind == 2 && type->integral < 23 && type->size != 4)) {
        if (out_param_alignment < 8) out_param_alignment = 8;
        if (frame_alignment < 8) frame_alignment = 8;
        if (needed_abi_alignment < 8) needed_abi_alignment = 8;
        displacement = (displacement + 7) & ~7;
    } else displacement = (displacement + 3) & ~3;
    if (type->kind == 5 && type->vectorKind > 3 && type->vectorKind < 15 && type->size == 16) {
        if (out_param_alignment < 16) out_param_alignment = 16;
        if (frame_alignment < 16) frame_alignment = 16;
        if (needed_abi_alignment < 16) needed_abi_alignment = 16;
        displacement = ((fn_00716cf0->linkage + displacement + 15) & ~15) - fn_00716cf0->linkage;
    } else if (type->kind == 13 || (type->kind == 5 && type->vectorKind > 3 && type->vectorKind < 15) ||
        type->kind == 6 || (type->kind == 11 && **(UInt8 **)((UInt8 *)type + 6) == 7) || type->kind == 3) {
        alignment = CMach_ArgumentAlignment(type);
        if (alignment > 4) {
            displacement = ((fn_00716cf0->linkage + displacement + alignment - 1) & ~(alignment - 1)) - fn_00716cf0->linkage;
            if (in_param_alignment < alignment) in_param_alignment = alignment;
        }
    }
    *output = displacement;
    return displacement + size;
}
#pragma pack(push, 2)
typedef struct NativeTraceback {
    UInt32 zero;
    UInt8 version, language;
    unsigned char a0 : 2, a2 : 1, a3 : 5;
    unsigned char b0 : 1, b1 : 1, b2 : 1, b3 : 3, b6 : 1, b7 : 1;
    unsigned char c0 : 1, c1 : 1, c2 : 6;
    unsigned char d0 : 1, d1 : 1, d2 : 6;
    UInt16 reserved;
} NativeTraceback;
typedef struct NativeTracebackVector {
    unsigned char registers : 6, optimized : 1, variadic : 1;
    unsigned char count : 7, used : 1;
} NativeTracebackVector;
typedef struct NativeFrameArgument {
    struct NativeFrameArgument *next;
    UInt8 unknown04[8];
    NativeFrameType *type;
} NativeFrameArgument;
typedef struct NativeFrameFixup {
    struct NativeFrameFixup *next;
    NativePCInstruction *instruction;
} NativeFrameFixup;
#pragma pack(pop)
extern UInt8 fn_0070f1a8;
extern SInt32 fn_00716c88;
extern NativeFrameArgument fn_007037c0;

extern char *strcpy(char *, const char *);
extern UInt32 CTool_EndianConvertWord32(UInt32);
extern UInt16 CTool_EndianConvertWord16(UInt16);
extern void setpcodeflags(unsigned long long);
extern void load_gpr(void *, SInt16, SInt16, NativePCObject *, int);
extern void add_immediate(SInt16, SInt16, NativePCObject *, SInt16);
extern NativePCBlock *fn_007101cc;
extern NativeFrameFixup *fn_00710878;

void *generate_traceback(UInt32 codeOffset, char *name, SInt32 *outSize, NativePCObject *function)
{
    SInt16 nameLength;
    SInt32 size;
    NativeTraceback *traceback;
    char *cursor;
    NativeFrameArgument *argument, *arguments;
    int isVariadic;
    UInt8 vectorArgumentCount;
    nameLength = strlen(name);
    size = (nameLength + 21 + (fn_00725ecc ? 1 : 0) + ((fn_00716c8c || fn_006e5d76) ? 2 : 0)) & ~3;
    traceback = galloc(size);
    memclrw(traceback, size);
    traceback->version = 0;
    traceback->language = fn_0070f1a8 ? 9 : 0;
    traceback->a2 = 1;
    traceback->b1 = 1;
    if (fn_00725ecc) traceback->b2 = 1;
    if (fn_00716c88) traceback->b6 = 1;
    if (fn_00726058 || use_helper_function(3) || use_helper_function(4) || use_helper_function(2)) traceback->b7 = 1;
    if (frame_size) traceback->c0 = 1;
    traceback->c2 = fn_00716c90;
    traceback->d2 = fn_00716c94;
    traceback->c1 = 0;
    traceback->d0 = 0;
    traceback->d1 = (fn_00716c8c || fn_006e5d76) ? 1 : 0;
    cursor = (char *)traceback + sizeof(NativeTraceback);
    *(UInt32 *)cursor = CTool_EndianConvertWord32(codeOffset);
    cursor += sizeof(UInt32);
    *(UInt16 *)cursor = CTool_EndianConvertWord16(nameLength);
    cursor += sizeof(UInt16);
    strcpy(cursor, name);
    cursor += nameLength;
    if (fn_00725ecc) *cursor++ = 31;
    if (fn_006e5d76 || fn_00716c8c) {
        NativeTracebackVector *extension = (NativeTracebackVector *)cursor;
        vectorArgumentCount = 0;
        arguments = *(NativeFrameArgument **)((UInt8 *)function->type + 6);
        argument = arguments;
        while (argument && argument != &fn_007037c0) argument = argument->next;
        isVariadic = argument == &fn_007037c0;
        for (argument = arguments; argument; argument = argument->next) {
            NativeFrameType *type = argument->type;
            if (type && type->kind == 5 && type->vectorKind > 3 && type->vectorKind < 15 && type->size == 16)
                vectorArgumentCount++;
        }
        extension->registers = fn_00716c8c;
        extension->optimized = fn_006e5d76 != 0;
        extension->variadic = isVariadic;
        extension->count = vectorArgumentCount;
        extension->used = fn_006e5d76 || fn_00716c8c;
    }
    *outSize = size;
    return traceback;
}

void change_dynamic_stack_space(int sizeRegister)
{
    SInt32 offset = (fn_00716cf0->linkage + parameter_area_size + frame_alignment - 1) & ~(frame_alignment - 1);
    NativeFrameFixup *fixup = galloc(8);
    emitpcode(50, 1, sizeRegister, 0, -offset);
    setpcodeflags(0x100ULL);
    fixup->instruction = fn_007101cc->last;
    fixup->next = fn_00710878;
    fn_00710878 = fixup;
    emitpcode(139, 1, sizeRegister);
    setpcodeflags(0x100ULL);
}

void do_allocate_dynamic_stack_space(UInt8 allocate, int scratchReg, int savedStackReg, SInt32 size)
{
    SInt32 negativeSize;
    SInt16 highSize;
    load_gpr(fn_006771c8, (SInt16)savedStackReg, 1, 0, 0);
    if (allocate) {
        size = (size + frame_alignment - 1) & ~(frame_alignment - 1);
        if (size < 32768) emitpcode(50, savedStackReg, 1, 0, -size);
        else {
            if (size < 32768) emitpcode(137, scratchReg, -size);
            else {
                negativeSize = -size;
                highSize = (negativeSize >> 16) + ((negativeSize >> 15) & 1);
                emitpcode(138, scratchReg, 0, highSize);
                if ((SInt16)negativeSize) emitpcode(63, scratchReg, scratchReg, 0, (SInt16)negativeSize);
            }
            emitpcode(52, savedStackReg, 1, scratchReg);
            setpcodeflags(0x180ULL);
        }
    } else {
        emitpcode(52, savedStackReg, 1, scratchReg);
        setpcodeflags(0x180ULL);
    }
}

void allocate_dynamic_stack_space(UInt8 allocate, int scratchReg, int savedStackReg, SInt32 size)
{
    if (fn_0070f008) {
        if (frame_alignment < 16) frame_alignment = 16;
        if (needed_abi_alignment < 16) needed_abi_alignment = 16;
    }
    do_allocate_dynamic_stack_space(allocate, scratchReg, savedStackReg, size);
    add_immediate((SInt16)scratchReg, 1, dummylocal, 0);
}

static inline void native_insert_local_object(NativePCObject *object, int list)
{
    NativeFrameObjectList *node;
    if (!compressing_data_area) {
        node = galloc(8); memclrw(node, 8); node->object = object;
        if (!local_objects[list]) local_objects[list] = node;
        if (local_objects_tail[list]) local_objects_tail[list]->next = node;
        local_objects_tail[list] = node;
    }
}
void assign_local_memory(NativePCObject *object)
{
    SInt16 alignment = CMach_AllocationAlignment(object->type, object->qualifiers);
    SInt32 start, total, size;
    NativeFrameVarInfo *info;
    if (!compressing_data_area && (((NativeFrameVarInfo *)object->localInfo)->flags & 0x20)) return;
    if (frame_alignment < alignment) frame_alignment = alignment;
    if (needed_abi_alignment < alignment) needed_abi_alignment = alignment;
    size = object->type->size;
    start = (local_data_size + alignment - 1) & ~(alignment - 1);
    total = start - local_data_size + ((size + alignment - 1) & ~(alignment - 1));
    if (local_data_size + total < local_data_limit) {
        local_data_size = start;
        info = Registers_GetVarInfo(object); info->flags &= ~2; info->flags |= 0x20;
        object->displacement = local_data_size;
        local_data_size += (object->type->size + alignment - 1) & ~(alignment - 1);
        native_insert_local_object(object, 0);
    } else if (!compressing_data_area && size > 32) {
        large_data_far_size = (large_data_far_size + alignment - 1) & ~(alignment - 1);
        info = Registers_GetVarInfo(object); info->flags &= ~2; info->flags |= 0x20;
        object->displacement = large_data_far_size + 65536;
        large_data_far_size += (object->type->size + alignment - 1) & ~(alignment - 1);
        native_insert_local_object(object, 2);
    } else {
        large_data_near_size = (large_data_near_size + alignment - 1) & ~(alignment - 1);
        info = Registers_GetVarInfo(object); info->flags &= ~2; info->flags |= 0x20;
        object->displacement = large_data_near_size + 32768;
        large_data_near_size += (object->type->size + alignment - 1) & ~(alignment - 1);
        native_insert_local_object(object, 1);
    }
}

extern UInt8 fn_00726061;
static inline int native_nonlocal(NativePCObject *object)
{
    NativeFrameVarInfo *info = Registers_GetVarInfo(object);
    return info && (info->flags & 2);
}
static inline int native_vector_type(NativeFrameType *type)
{
    return type->kind == 5 && type->vectorKind > 3 && type->vectorKind < 15 && type->size == 16;
}
void assign_locals_to_memory(NativeFrameObjectList *objects)
{
    int size;
    NativeFrameObjectList *node;
    NativePCObject *object;
    NativeFrameType *type;
    for (size = 1; size < 1024; size += size) {
        for (node = objects; node; node = node->next) {
            object = node->object;
            if (Registers_GetVarInfo(object)->used && !native_nonlocal(object) && object->type->size <= size)
                assign_local_memory(object);
        }
    }
    for (node = objects; node; node = node->next) {
        object = node->object;
        if (Registers_GetVarInfo(object)->used && !native_nonlocal(object)) assign_local_memory(node->object);
        type = object->type;
        if (type && type->kind == 13 && native_vector_type(*(NativeFrameType **)((char *)type + 6))) fn_00726061 = 1;
    }
}
extern UInt8 fn_0070f019, fn_0070f018;
extern NativePCObject *fn_00710818;
extern NativeFrameType fn_00699c24;
extern NativeFrameType *CDecl_NewArrayType(NativeFrameType *, SInt32);
extern void *GetHashNameNodeExport(const char *), *fn_0046bc00(void);
void fn_00586a30(void)
{
    int size = 0;
    if (!fn_0070f019 && fn_0070f018) size += 96; else size += 32;
    fn_00710818 = galloc(96); memclrw(fn_00710818, 96);
    fn_00710818->type = CDecl_NewArrayType(&fn_00699c24, size);
    fn_00710818->kind = 5;
    fn_00710818->name = GetHashNameNodeExport("<valocal>");
    fn_00710818->datatype = 1; fn_00710818->displacement = 0;
    fn_00710818->localInfo = fn_0046bc00();
    if (local_data_size) CError_Internal("StackFrame.c", 4116);
    assign_local_memory(fn_00710818);
}
void compress_data_area(void)
{
    SInt32 parameters, aligned, estimate;
    NativeFrameObjectList *node;
    NativePCBlock *block;
    NativePCInstruction *instruction;
    int i;
    compressing_data_area = 1;
    if (fn_00725dfb) parameters = 0;
    else parameters = parameter_area_size < fn_00716cf0->minimumParameters ? fn_00716cf0->minimumParameters : parameter_area_size;
    parameters += fn_006e5d8e;
    aligned = ((fn_00716cf0->linkage + parameters + frame_alignment - 1) & ~(frame_alignment - 1)) - fn_00716cf0->linkage;
    estimate = (fn_00716cf0->linkage * 2 + aligned + fn_006e5d7a + in_parameter_size + frame_alignment - 1) & ~(frame_alignment - 1);
    local_data_limit = 32768 - estimate - frame_alignment;
    if (local_objects_tail[0]) {
        if (local_objects[1]) { local_objects_tail[0]->next = local_objects[1]; local_objects_tail[0] = local_objects_tail[1]; }
        if (local_objects[2]) { local_objects_tail[0]->next = local_objects[2]; local_objects_tail[0] = local_objects_tail[2]; }
    } else if (local_objects_tail[1]) {
        local_objects[0] = local_objects[1]; local_objects_tail[0] = local_objects_tail[1];
        if (local_objects[2]) { local_objects_tail[0]->next = local_objects[2]; local_objects_tail[0] = local_objects_tail[2]; }
    } else { local_objects[0] = local_objects[2]; local_objects_tail[0] = local_objects_tail[2]; }
    for (node = local_objects[0]; node; node = node->next) Registers_GetVarInfo(node->object)->used = 0;
    for (block = pcbasicblocks; block; block = block->next) {
        for (instruction = block->first; instruction; instruction = instruction->next) {
            for (i = 0; i < instruction->operandCount; i++) {
                NativePCOperand *operand = &instruction->operands[i];
                if (operand->kind == 4 && operand->data.mem.object && operand->data.mem.object->datatype == 1)
                    Registers_GetVarInfo(operand->data.mem.object)->used = 1;
            }
        }
    }
    local_data_size = large_data_near_size = large_data_far_size = 0;
    for (node = local_objects[0]; node; node = node->next)
        if (Registers_GetVarInfo(node->object)->used) assign_local_memory(node->object);
}
void allocate_new_frame(int scratch, int saveStack)
{
    if (dynamic_align_stack) {
        emitpcode(103, scratch, 1, 0, align_bits(frame_alignment, 1), 31);
        if (frame_size > 32767) CError_Internal("StackFrame.c", 1453);
        else {
            emitpcode(79, scratch, scratch, -(frame_size ? frame_size : fn_00716cec));
            if (saveStack) emitpcode(139, saveStack, 1);
            emitpcode(52, 1, 1, scratch);
        }
    } else {
        if (frame_size > 32767) CError_Internal("StackFrame.c", 1490);
        else emitpcode(50, 1, 1, 0, -frame_size);
        if (saveStack) emitpcode(139, saveStack, 1);
    }
}
extern int strcmp(const char *, const char *), sprintf(char *, const char *, ...);
extern SInt32 fn_00716c84[5], fn_0071019c[5];
extern UInt32 fn_00710274[5];
extern void *fn_007101c4, *fn_00711be0;
extern UInt8 fn_00725d96[];
extern NativePCObject *CParser_NewRTFunc(void *, void *, int, int);
extern void *GetHashNameNode(const char *);
extern void MakeSymbolTableEntry(NativePCObject *);
void call_helper_function(const char *format, SInt8 regClass, int regFlags, UInt8 extraReg, UInt8 operands)
{
    char name[32];
    int mode, i;
    void *oldScope;
    NativePCObject *object;
    NativePCInstruction *instruction;
    NativePCOperand *operand;
    switch (regClass) {
        case 2: mode = 2; break;
        case 4: mode = extraReg ? 1 : 0; break;
        default: mode = 1; break;
    }
    if (!strcmp(format, "__restore_frame_and_exit") || !strcmp(format, "__create_frame")) sprintf(name, format);
    else sprintf(name, format, 32 - fn_00716c84[regClass]);
    if (fn_0071019c[regClass] < fn_00716c84[regClass]) CError_Internal("StackFrame.c", 3922);
    oldScope = fn_00711be0; fn_00711be0 = fn_007101c4;
    object = CParser_NewRTFunc(fn_00725d96, 0, 2, 0);
    object->flags |= 0x10;
    fn_00711be0 = oldScope;
    object->name = GetHashNameNode(name);
    MakeSymbolTableEntry(object);
    instruction = makepcode(1, fn_00716c84[regClass] + mode, object, 0);
    if (!operands) { instruction->opcode = 0; instruction->flags &= ~0x0080000000000000ULL; }
    operand = &instruction->operands[1];
    for (i = 1; (SInt16)i <= fn_00716c84[regClass]; i++) {
        operand->kind = 0; operand->arg = regClass;
        operand->data.reg.reg = (UInt16)fn_00710274[regClass] - i;
        operand->data.reg.flags = regFlags;
        operand++;
    }
    switch (regClass) {
        case 2:
            operand[1].kind = 0; operand[1].arg = 4; operand[1].data.reg.reg = 12; operand[1].data.reg.flags = 2;
            operand[2].kind = 0; operand[2].arg = 4; operand[2].data.reg.reg = 0; operand[2].data.reg.flags = 1;
            break;
        case 4: if (!extraReg) break;
        default:
            operand[1].kind = 0; operand[1].arg = 4; operand[1].data.reg.reg = 11; operand[1].data.reg.flags = 1;
            break;
    }
    appendpcode(fn_007101cc, instruction);
    setpcodeflags(0x100ULL);
}
extern UInt8 fn_00699c54[], fn_00699c94[], fn_00699ca4[];
extern void load_fpr(void *, SInt16, SInt16, NativePCObject *, int);
extern void load_fpr_x(void *, SInt16, SInt16, NativePCObject *);
void restore_nonvolatile_GPRs(int base, int offset, UInt8 allowExit)
{
    int i, total;
    UInt8 helper;
    offset += fn_006e5dee[4];
    helper = use_helper_function(4);
    if (!allowExit && (helper & 0x10)) helper = 0;
    if (helper) {
        if (helper & 0x10) {
            if (offset != frame_size - fn_006e5dda[4] * fn_00716c94) CError_Internal("StackFrame.c", 2484);
            call_helper_function("__restore_gpr_%d_exit", 4, 2, 1, 0);
        } else {
            total = offset + fn_00716c94 * 4;
            if (total) emitpcode(63, 11, base, 0, total); else emitpcode(139, 11, base);
            call_helper_function("_restgpr_%d", 4, 2, 1, 1);
        }
    } else if (fn_0070f04c && fn_004c07c0() && !fn_0072605b && (fn_00716c94 > 4 || (fn_0070f231 && fn_00716c94 > 1))) {
        emitpcode(39, fn_00716c94 - 1, 32 - fn_00716c94, base, 0, offset);
        setpcodeflags(0x80ULL);
    } else {
        for (i = 1; i <= fn_00716c94; i++) {
            load_gpr(fn_00699c54, (SInt16)(32 - i), (SInt16)base, 0, offset + (fn_00716c94 - i) * fn_006e5dda[4]);
            setpcodeflags(0x80ULL);
        }
    }
}
void save_nonvolatile_GPRs(int base, int offset, UInt8 allowCreate)
{
    int i, total;
    UInt8 helper;
    offset += fn_006e5dee[4];
    helper = use_helper_function(4);
    if ((helper & 8) && !allowCreate) helper = 0;
    if (helper) {
        if (helper & 8) {
            emitpcode(129, 0);
            emitpcode(137, 11, -frame_size);
            call_helper_function("__create_frame_and_save_gpr_%d", 4, 1, 1, 1);
        } else {
            total = offset + fn_00716c94 * 4;
            if (total) emitpcode(63, 11, base, 0, total); else emitpcode(139, 11, base);
            call_helper_function("_savegpr_%d", 4, 1, 1, 1);
        }
    } else if (fn_0070f04c && fn_004c07c0() && !fn_0072605b && (fn_00716c94 > 4 || (fn_0070f231 && fn_00716c94 > 1))) {
        emitpcode(54, fn_00716c94 - 1, 32 - fn_00716c94, base, 0, offset);
    } else {
        for (i = 1; i <= fn_00716c94; i++)
            emitpcode(49, 32 - i, base, 0, offset + (fn_00716c94 - i) * fn_006e5dda[4]);
    }
}
void restore_nonvolatile_FPRs(int base, int offset)
{
    int total, displacement;
    SInt16 i;
    offset += fn_006e5dee[3];
    if (use_helper_function(3)) {
        total = offset + fn_00716c90 * 8;
        if (total) emitpcode(63, 11, base, 0, total); else emitpcode(139, 11, base);
        call_helper_function("_restfpr_%d", 3, 2, 1, 1);
    } else {
        for (i = 1; i <= fn_00716c90; i++) {
            displacement = offset + (fn_00716c90 - i) * fn_006e5dda[3];
            if (fn_0070effa == 22 && fn_0072605b) {
                emitpcode(137, 0, displacement + 8); setpcodeflags(0x80ULL);
                load_fpr_x(fn_00699ca4, (SInt16)(32 - i), (SInt16)base, 0); setpcodeflags(0x80ULL);
            }
            load_fpr(fn_00699c94, (SInt16)(32 - i), (SInt16)base, 0, displacement);
            setpcodeflags(0x80ULL);
        }
    }
}
void save_nonvolatile_FPRs(int base, int offset)
{
    SInt16 i;
    int displacement, total, reg;
    offset += fn_006e5dee[3];
    if (use_helper_function(3)) {
        total = offset + fn_00716c90 * 8;
        if (total) emitpcode(63, 11, base, 0, total); else emitpcode(139, 11, base);
        call_helper_function("_savefpr_%d", 3, 1, 1, 1);
    } else for (i = 1; i <= fn_00716c90; i++) {
        reg = 32 - i;
        if (fn_0070effa == 22 && fn_0072605b) {
            displacement = offset + (fn_00716c90 - i) * fn_006e5dda[3];
            if (offset + fn_00716c90 * fn_006e5dda[3] < 4096) {
                emitpcode(154, reg, base, 0, displacement); setpcodeflags(0x80ULL);
                emitpcode(406, reg, base, 0, displacement + 8, 0, 0x390); setpcodeflags(0x80ULL);
            } else {
                emitpcode(137, 0, displacement + 8); setpcodeflags(0x80ULL);
                emitpcode(154, reg, base, 0, offset + (fn_00716c90 - i) * fn_006e5dda[3]); setpcodeflags(0x80ULL);
                emitpcode(408, reg, base, 0, 0, 0x390); setpcodeflags(0x80ULL);
            }
        } else {
            emitpcode(154, reg, base, 0, offset + (fn_00716c90 - i) * 8); setpcodeflags(0x80ULL);
        }
    }
}
extern UInt8 fn_00725f3b, fn_00725e6a, fn_0070f066, fn_0070f37f;
extern SInt8 fn_0070f068;
extern SInt32 fn_00715c7c, fn_00710284;
extern NativePCObject *fn_007107d8;
extern NativeFrameObjectList *fn_00716d50;
extern void fn_004c2bb0(NativePCObject *, int, int, int);
extern UInt16 fn_004c0c60(NativePCObject *);
extern void PPCError_ErrorTerm(int, int), fn_00594740(int, int, int);
NativeFrameABI fn_006ad19e = {8, 0, 0, 0, 4, {0, 0, 0}};
NativeFrameABI fn_006ad1be = {8, 0, 0, 0, 4, {0, 0, 0}};
void init_frame_sizes(void)
{
    int estimate, originalEstimate, alignment;
    NativeFrameObjectList *node;
    NativePCObject *object;
    estimate = fn_00716cf0->linkage * 2 + in_parameter_size + parameter_area_size_estimate + 2048;
    estimate += (fn_0070effa == 22 ? 16 : 8) * 18 + 268;
    originalEstimate = (estimate + frame_alignment - 1) & ~(frame_alignment - 1);
    frame_size_estimate = originalEstimate;
    for (node = fn_00716d50; node; node = node->next) {
        object = node->object;
        alignment = CMach_AllocationAlignment(object->type, object->qualifiers);
        frame_size_estimate = (frame_size_estimate + alignment - 1) & ~(alignment - 1);
        frame_size_estimate += object->type->size;
    }
    if (fn_007171e0) { fn_00725ee1 = 1; fn_00725ed7 = 1; frame_size_estimate += 512; }
    if (frame_size_estimate > 32767) { fn_00725ecc = 1; fn_00725dfb = 1; fn_00725ee1 = 1; fn_00725ed7 = 1; }
    local_data_limit = 32768 - originalEstimate - frame_alignment;
    if (fn_00725ecc) {
        fn_00725ee1 = 1; fn_00725ed7 = 1;
        dummylocal = lalloc(96); memclrw(dummylocal, 96);
        dummylocal->type = (NativeFrameType *)fn_00725d96;
        dummylocal->kind = 5; dummylocal->name = GetHashNameNodeExport("<dummy>"); dummylocal->datatype = 1;
        dummylocal->localInfo = fn_0046bc00();
        ((NativeFrameVarInfo *)dummylocal->localInfo)->flags |= 0x20;
        *((UInt8 *)dummylocal->localInfo + 8) = 1;
    }
    if (fn_00725ecc) {
        if (fn_00710284 > 31 && fn_0070f37f == 1) PPCError_ErrorTerm(120, 31);
        fn_00594740(0, 4, 31); fn_007172bc = 31;
    } else fn_007172bc = 1;
}
void init_stack_globals(NativePCObject *function)
{
    SInt8 i;
    UInt8 j, option;
    int alignment;
    fn_00725f3b = 0; fn_00725ee1 = 0; fn_00726058 = 0; fn_00725e6a = 0; fn_00725ecc = 0; fn_00725dfb = 0;
    fn_00715c7c = 0; fn_00725ed7 = 0; fn_0072605b = 0; vrsave_register = -1;
    dynamic_align_stack = 0; compressing_data_area = 0;
    align_instr1 = 0; align_instr2 = 0; setup_caller_sp = 0; loadvrsave = 0; storevrsave = 0;
    fn_00710878 = 0; local_data_size = 0; local_data_limit = 8192; large_data_near_size = 0; large_data_far_size = 0;
    frame_size_estimate = 0; in_parameter_size = 0; parameter_area_size = 0; parameter_area_size_estimate = 0;
    option = fn_0070f066;
    frame_alignment = option ? 16 : 8;
    if (fn_0070f008 && frame_alignment < 16) frame_alignment = 16;
    alignment = (SInt32)(1U << ((UInt8)fn_0070f068 & 31));
    if (frame_alignment < alignment) frame_alignment = alignment;
    needed_abi_alignment = option ? 16 : 8;
    out_param_alignment = option ? 16 : 8;
    in_param_alignment = option ? 16 : 8;
    fn_006e5e38 = 0; has_varargs = 0; fn_006e5e1a = 0; frame_size = 0; fn_00716cec = 0;
    fn_006e5d7a = -1; fn_006e5d82 = -1; fn_006e5d7e = -1;
    fn_00716cf0 = &fn_006ad19e;
    if (fn_0070effa == 22) fn_00716cf0 = &fn_006ad1be;
    for (i = 0; i < 5; i++) fn_006e5dee[i] = -1;
    fn_006e5dda[0] = 0; fn_006e5dda[1] = 0; fn_006e5dda[2] = 16; fn_006e5dda[3] = 8; fn_006e5dda[4] = 4;
    for (i = 0; i < 5; i++) { fn_006e5dc6[i] = -1; fn_006e5daa[i] = 0; fn_006e5d96[i] = 0; }
    nonvolatile_save_size = 0; fn_006e5d92 = -1;
    fn_006e5dda[0] = 0; fn_006e5dda[1] = 0; fn_006e5dda[2] = 16; fn_006e5dda[3] = 8;
    fn_006e5dc2 = -1; fn_006e5dbe = -1; fn_006e5d8e = 0; fn_006e5e34 = 0;
    fn_00710818 = 0; fn_007171e0 = 0; fn_007107d8 = 0; dummylocal = 0;
    for (j = 0; j < 3; j++) { local_objects[j] = 0; local_objects_tail[j] = 0; }
    if (function->qualifiers & 0x80000000UL) {
        fn_004c2bb0(function, 0, 0, 1);
        fn_007171e0 = fn_004c0c60(function);
        function->flags |= 0x800;
    }
}
extern UInt8 fn_0070f044, fn_0070efe8;
extern NativeFrameObjectList *fn_00710924;
extern void *fn_0046bbe0(void *);
void assign_arguments_to_memory(int unused1, int unused2, UInt8 varargs)
{
    int displacement = 0, gpr = 3, fpr = 1, vr = 2, alignment;
    UInt8 inParameters;
    NativeFrameObjectList *node;
    NativePCObject *object;
    NativeFrameType *type;
    if (varargs) fn_00586a30();
    for (node = fn_00710924; node; node = node->next) {
        object = node->object; type = object->type;
        if (native_vector_type(type)) {
            object->localInfo = fn_0046bbe0(object->localInfo);
            object->displacement = 0; object->datatype = 1;
            if ((SInt16)vr > 13) {
                displacement = ((displacement + fn_00716cf0->linkage + 15) & ~15) - fn_00716cf0->linkage;
                object->displacement = displacement; displacement += 16;
                if (in_param_alignment < 16) in_param_alignment = 16;
                Registers_GetVarInfo(object)->flags |= 1;
            } else {
                assign_local_memory(object);
                Registers_GetVarInfo(object)->flags &= ~1;
            }
            vr++;
        } else {
            UInt8 kind = type->kind;
            inParameters = 1;
            if ((((kind == 1 && type->integral < 23) || kind == 4) && type->size == 8) ||
                (fn_0070f019 && kind == 2 && type->integral < 23 && type->size != 4 && !fn_0070f044)) {
                if ((SInt16)gpr % 2 == 0) gpr++;
            }
            if (kind == 2 && type->integral < 23 && !fn_0070f019) {
                if ((SInt16)fpr <= 8) inParameters = 0;
                fpr++;
            } else {
                if ((SInt16)gpr <= 10) inParameters = 0;
                if ((fn_0070f019 && kind == 2 && type->integral < 23 && type->size != 4) ||
                    (((kind == 1 && type->integral < 23) || kind == 4) && type->size == 8)) gpr += 2;
                else if ((kind == 1 && type->integral < 23) || kind == 4 || kind == 12 ||
                    (kind == 11 && (*(NativeFrameType **)((char *)type + 6))->kind != 7) ||
                    (fn_0070f019 && kind == 2 && type->integral < 23 && type->size == 4)) gpr++;
                else gpr += (type->size >> 2) + ((type->size & 3) ? 1 : 0);
            }
            object->datatype = 1; object->localInfo = fn_0046bbe0(object->localInfo);
            if (inParameters) {
                kind = type->kind;
                if ((((kind == 1 && type->integral < 23) || kind == 4) && type->size == 8) ||
                    (kind == 2 && type->integral < 23 && type->size != 4)) displacement = (displacement + 7) & ~7;
                else displacement = (displacement + 3) & ~3;
                if (kind == 13 || kind == 5 || kind == 6 || kind == 3 ||
                    (kind == 11 && (*(NativeFrameType **)((char *)type + 6))->kind == 7)) {
                    alignment = CMach_ArgumentAlignment(type);
                    if (alignment > 4) {
                        displacement = (displacement + alignment - 1) & ~(alignment - 1);
                        if (in_param_alignment < alignment) in_param_alignment = alignment;
                    }
                }
                object->displacement = displacement;
                Registers_GetVarInfo(object)->flags |= 1;
                type = object->type;
                if (!fn_0070efe8 && ((type->kind == 1 && type->integral < 23) || type->kind == 4) && type->size < 4)
                    object->displacement += 4 - type->size;
                displacement += object->type->size;
            } else {
                object->displacement = 0; assign_local_memory(object);
            }
        }
        if (!native_nonlocal(object)) ((NativeFrameVarInfo *)object->localInfo)->flags |= 0x20;
    }
    if (in_parameter_size >= displacement) displacement = in_parameter_size;
    in_parameter_size = displacement;
    if (fn_007107d8) CError_Internal("StackFrame.c", 3220);
}
extern NativePCLabel *makepclabel(void);
extern void pcbranch(NativePCBlock *, NativePCLabel *, int), branch_label(NativePCLabel *);
void move_varargs_to_memory(void)
{
    NativePCLabel *end, *start;
    SInt16 i;
    has_varargs = 1;
    fn_007107d8 = lalloc(96); memclrw(fn_007107d8, 96);
    fn_007107d8->type = (NativeFrameType *)fn_00725d96; fn_007107d8->kind = 5;
    fn_007107d8->name = GetHashNameNodeExport("<vaparam>"); fn_007107d8->datatype = 1;
    fn_007107d8->localInfo = fn_0046bc00(); fn_007107d8->displacement = in_parameter_size;
    *((UInt8 *)fn_007107d8->localInfo + 8) = 1;
    Registers_GetVarInfo(fn_007107d8)->flags |= 1;
    native_local_base_register(fn_007107d8);
    if (fn_0070f018 && !fn_0070f019) {
        end = makepclabel(); start = makepclabel();
        emitpcode(8, 1, 2, end);
        pcbranch(fn_007101cc, end, 0); pcbranch(fn_007101cc, start, 0);
        branch_label(start);
        for (i = 1; i <= 8; i++) {
            emitpcode(154, (int)i, native_local_base_register(fn_00710818), fn_00710818, 32 + (i - 1) * 8);
            setpcodeflags(0x8020ULL);
        }
        branch_label(end);
    }
    for (i = 3; i <= 10; i++) {
        emitpcode(49, (int)i, native_local_base_register(fn_00710818), fn_00710818, (i - 3) * 4);
        setpcodeflags(0x8020ULL);
    }
    native_local_base_register(fn_007107d8);
}
void fn_00585520(void);
extern void fn_00579600(void), fn_0045c1a0(int);
void compute_frame_sizes(void)
{
    int offset, vectors, mask, adjustment, base;
    SInt8 regClass;
    fn_006e5dda[3] = fn_0070effa == 22 && fn_0072605b ? 16 : 8;
    if (fn_006e5e38 && fn_006e5e38 != frame_alignment) CError_Internal("StackFrame.c", 1179);
    if (fn_007171e0) {
        if (!(fn_007171e0 & 0x40) || !fn_0070f008) fn_006e5dda[2] = 0;
        if (!(fn_007171e0 & 0x20) || fn_0070f019 || !fn_0070f018) fn_006e5dda[3] = 0;
        fn_00585520();
        if (fn_006e5d8e) local_data_size += fn_006e5d8e;
    }
    fn_00579600();
    fn_006e5d7e = fn_00716cf0->pointerSize;
    fn_006e5dee[3] = -(fn_006e5dda[3] * fn_00716c90);
    offset = -(fn_006e5dda[4] * fn_00716c94 - fn_006e5dee[3]);
    fn_006e5dee[4] = offset;
    if (fn_00716c88 && !fn_007171e0) { offset -= 4; fn_006e5dee[1] = offset; }
    fn_006e5d7a = -offset;
    fn_006e5d82 = -1; fn_006e5dee[2] = -1;
    if (fn_0070f008) {
        if (fn_006e5d76) {
            fn_006e5d82 = fn_006e5dee[4] - 4;
            if (fn_00716c88 && !fn_007171e0) fn_006e5d82 -= 4;
            fn_006e5d7a += 4;
        }
        vectors = fn_00716c8c * 16;
        if (vectors > 0) fn_006e5d7a = (fn_006e5d7a + vectors + frame_alignment - 1) & ~(frame_alignment - 1);
    }
    if (parameter_area_size) { fn_00725ee1 = 1; fn_00725ed7 = 1; }
    compress_data_area();
    if (fn_006e5d8e) {
        if (frame_alignment < nonvolatile_save_size) frame_alignment = nonvolatile_save_size;
        if (needed_abi_alignment < nonvolatile_save_size) needed_abi_alignment = nonvolatile_save_size;
        local_data_size = (local_data_size + frame_alignment - 1) & ~(frame_alignment - 1);
        local_data_size += fn_006e5d8e;
    }
    mask = ~(frame_alignment - 1);
    local_data_size = (local_data_size + frame_alignment - 1) & mask;
    fn_006e5d7a = (fn_006e5d7a + frame_alignment - 1) & mask;
    if (!fn_00725ee1 && local_data_size + fn_006e5d7a <= fn_00716cf0->minimumFrame) {
        if (dynamic_align_stack) CError_Internal("StackFrame.c", 1311);
        fn_006e5e34 = 0; frame_size = 0; fn_00716cec = local_data_size + fn_006e5d7a;
    } else {
        fn_00725ee1 = 1; fn_00725ed7 = 1;
        if (parameter_area_size < fn_00716cf0->minimumParameters) parameter_area_size = fn_00716cf0->minimumParameters;
        parameter_area_size = ((parameter_area_size + fn_00716cf0->linkage + frame_alignment - 1) & mask) - fn_00716cf0->linkage;
        if (fn_00725dfb) {
            if (large_data_far_size) CError_Internal("StackFrame.c", 1326);
            large_data_near_size += parameter_area_size; parameter_area_size = 0;
        }
        fn_006e5e34 = fn_00716cf0->linkage;
        frame_size = fn_00716cf0->linkage + parameter_area_size + local_data_size + fn_006e5d7a;
        if (fn_0070f008 && fn_00716c8c) fn_006e5dee[2] = fn_00716cf0->linkage + parameter_area_size + local_data_size;
        adjustment = ((frame_size + 15) & ~15) - frame_size;
        frame_size += adjustment;
        frame_size = (frame_size + frame_alignment - 1) & ~(frame_alignment - 1);
        fn_00716cec = frame_size;
    }
    if (fn_007171e0) {
        if (!fn_00725ee1) CError_Internal("StackFrame.c", 1352);
        base = fn_00716cf0->linkage + parameter_area_size + local_data_size - fn_006e5d8e;
        fn_006e5d92 += base;
        for (regClass = 0; regClass < 5; regClass++)
            if (fn_006e5daa[regClass] > 0) fn_006e5dc6[regClass] += base;
        if (fn_006e5dbe != -1) fn_006e5dbe += fn_006e5dc6[4];
        if (fn_006e5dc2 != -1) fn_006e5dc2 += fn_006e5dc6[4];
    }
    if (!fn_00725dfb && frame_size > 32767) fn_0045c1a0(10210);
    fn_006e5e1a = 1;
}
UInt32 fn_006e5ad0[5][32];
extern SInt32 fn_0071003c[5], fn_0070eac0[5][32];
void fn_00585520(void)
{
    SInt8 regClass;
    int i, count, saved, stride, reg;
    UInt32 *order, modified;
    NativePCBlock *block;
    NativePCInstruction *instruction;
    memset(fn_006e5ad0, 0, 640);
    fn_006e5ad0[0][0] = 1; fn_006e5ad0[0][1] = 2; fn_006e5ad0[0][2] = 4;
    fn_006e5ad0[1][0] = 1; fn_006e5ad0[1][1] = 2; fn_006e5ad0[1][2] = 4; fn_006e5ad0[1][3] = 8;
    fn_006e5ad0[1][4] = 16; fn_006e5ad0[1][5] = 32; fn_006e5ad0[1][6] = 64; fn_006e5ad0[1][7] = 128;
    if (fn_00726058 || use_helper_function(3) || use_helper_function(4) || use_helper_function(2)) {
        for (regClass = 0; regClass < 5; regClass++) {
            switch (regClass) {
                case 0: fn_006e5daa[regClass] = 3; fn_006e5d96[regClass] = 7; break;
                case 1: fn_006e5daa[regClass] = 8; fn_006e5d96[regClass] = 255; break;
                default: if (fn_006e5dda[regClass] > 0) { fn_006e5daa[regClass] = fn_0071003c[regClass]; fn_006e5d96[regClass] = -1; } break;
            }
        }
        stride = fn_006e5dda[4];
        for (i = 0; i < fn_0071003c[4]; i++) {
            reg = fn_0070eac0[4][i];
            if (!reg) fn_006e5dbe = i * stride;
            else if (reg == 11 && (fn_00725ecc || dynamic_align_stack || (fn_007171e0 & 2))) fn_006e5dc2 = i * stride;
        }
    } else {
        for (block = pcbasicblocks; block; block = block->next) for (instruction = block->first; instruction; instruction = instruction->next)
            for (i = 0; i < instruction->operandCount; i++) {
                NativePCOperand *operand = &instruction->operands[i];
                if (operand->kind == 0 && (operand->data.reg.flags & 2))
                    fn_006e5d96[(SInt8)operand->arg] |= 1U << (operand->data.reg.reg & 31);
            }
        if (fn_00725ecc || dynamic_align_stack || (fn_007171e0 & 2)) fn_006e5d96[4] |= 0x801;
        if (fn_006e5d96[0] || fn_006e5d96[1]) fn_006e5d96[4] |= 1;
        for (regClass = 0; regClass < 5; regClass++) {
            switch (regClass) {
                case 0: count = 3; order = fn_006e5ad0[0]; break;
                case 1: count = 8; order = fn_006e5ad0[1]; break;
                default: count = fn_006e5dda[regClass] > 0 ? fn_0071003c[regClass] : 0; order = (UInt32 *)fn_0070eac0[regClass]; break;
            }
            modified = fn_006e5d96[regClass]; saved = 0;
            for (i = 0; i < count; i++) {
                reg = order[i];
                if (modified & (1U << (reg & 31))) {
                    if (regClass == 4) {
                        if (!reg) fn_006e5dbe = saved * fn_006e5dda[regClass];
                        else if (reg == 11 && (fn_00725ecc || dynamic_align_stack || (fn_007171e0 & 2))) fn_006e5dc2 = saved * fn_006e5dda[regClass];
                    }
                    fn_006e5daa[regClass]++; saved++;
                }
            }
        }
    }
    fn_006e5d92 = 0;
    if (fn_006e5daa[1]) fn_006e5daa[1] = 1;
    fn_006e5d8e = (fn_006e5daa[0] + fn_006e5daa[1]) * 4;
    if (fn_006e5daa[2] || fn_006e5daa[3]) fn_006e5d8e += 4;
    fn_006e5d86 = fn_006e5d8e;
    if (fn_007171e0 & 4) fn_006e5d8e += 8;
    if (fn_007171e0 & 8) fn_006e5d8e += 4;
    if (fn_007171e0 & 16) fn_006e5d8e += 4;
    fn_006e5d8e = (fn_006e5d8e + 3) & ~3;
    for (regClass = 0; regClass < 5; regClass++) {
        stride = fn_006e5dda[regClass];
        if (stride > 0 && (regClass != 2 || fn_0070f008)) {
            if (frame_alignment < stride) frame_alignment = stride;
            if (needed_abi_alignment < stride) needed_abi_alignment = stride;
            fn_006e5d8e = (fn_006e5d8e + stride - 1) & ~(stride - 1);
            if (nonvolatile_save_size < stride) nonvolatile_save_size = stride;
            fn_006e5dc6[regClass] = fn_006e5d8e;
            fn_006e5d8e += fn_006e5daa[regClass] * stride;
        }
    }
    if (frame_alignment < nonvolatile_save_size) frame_alignment = nonvolatile_save_size;
    if (needed_abi_alignment < nonvolatile_save_size) needed_abi_alignment = nonvolatile_save_size;
    local_data_size = (local_data_size + frame_alignment - 1) & ~(frame_alignment - 1);
    fn_006e5d8e = (fn_006e5d8e + frame_alignment - 1) & ~(frame_alignment - 1);
}
static inline void native_restore_spr(int spr)
{
    switch (spr) {
        case 1: emitpcode(119, 0); break;
        case 8: emitpcode(121, 0); break;
        case 9: case 256: emitpcode(120, 0); break;
        default: emitpcode(124, spr, 0); break;
    }
}
int fn_00585b50(void)
{
    int sprA = 26, sprB = 27, base = 1, offset, i, reg;
    UInt8 variant = 0;
    if (fn_007171e0 & 2) {
        emitpcode(125, 0); emitpcode(66, 11, 0, 0, 1); emitpcode(63, 11, 11, 0, -32766);
        emitpcode(98, 0, 0, 11); emitpcode(123, 0);
    }
    if (fn_00725ecc) { emitpcode(139, 11, 10); base = 11; setpcodeflags(0x100ULL); }
    if (fn_007171e0 & 0x200) { variant = 1; sprA = 58; sprB = 59; }
    else if (fn_007171e0 & 0x400) { variant = 2; sprA = 570; sprB = 571; }
    else if (fn_007171e0 & 0x800) { variant = 3; sprA = 574; sprB = 575; }
    offset = fn_006e5d92 + fn_006e5d86;
    if (fn_007171e0 & 4) {
        emitpcode(34, 0, base, 0, offset); native_restore_spr(sprA);
        emitpcode(34, 0, base, 0, offset + 4); native_restore_spr(sprB); offset += 8;
    }
    if (fn_007171e0 & 8) { emitpcode(34, 0, base, 0, offset); emitpcode(124, 19, 0); offset += 4; }
    if (fn_007171e0 & 16) { emitpcode(34, 0, base, 0, offset); emitpcode(124, 18, 0); }
    if (fn_006e5daa[3]) {
        offset = fn_006e5dc6[3];
        for (i = 0; i < fn_0071003c[3]; i++) {
            reg = fn_0070eac0[3][i];
            if (fn_006e5d96[3] & (1U << (reg & 31))) {
                emitpcode(146, reg, base, 0, offset); offset += fn_006e5dda[3];
            }
        }
    }
    if (fn_006e5daa[2]) {
        offset = fn_006e5dc6[2];
        for (i = 0; i < fn_0071003c[2]; i++) {
            reg = fn_0070eac0[2][i];
            if (fn_006e5d96[2] & (1U << (reg & 31))) {
                emitpcode(137, 0, offset); emitpcode(249, reg, base, 0); offset += fn_006e5dda[2];
            }
        }
    }
    if (fn_006e5daa[4]) {
        offset = fn_006e5dc6[4];
        for (i = 0; i < fn_0071003c[4]; i++) {
            reg = fn_0070eac0[4][i];
            if (fn_006e5d96[4] & (1U << (reg & 31))) {
                if (reg && (reg != 11 || fn_006e5dc2 == -1)) emitpcode(34, reg, base, 0, offset);
                offset += fn_006e5dda[4];
            }
        }
    }
    offset = fn_006e5d92;
    if (fn_006e5daa[0] && (fn_006e5d96[0] & 4)) { emitpcode(34, 0, base, 0, offset); emitpcode(120, 0); offset += 4; }
    if (fn_006e5daa[0] && (fn_006e5d96[0] & 1)) { emitpcode(34, 0, base, 0, offset); emitpcode(119, 0); offset += 4; }
    if (fn_006e5daa[1]) { emitpcode(34, 0, base, 0, offset); emitpcode(122, 255, 0); setpcodeflags(0x80ULL); offset += 4; }
    if (fn_006e5daa[0] && (fn_006e5d96[0] & 2)) { emitpcode(34, 0, base, 0, offset); emitpcode(121, 0); offset += 4; }
    if (fn_006e5daa[2] || fn_006e5daa[3]) { emitpcode(34, 0, base, 0, offset); emitpcode(123, 0); }
    if (fn_006e5dc2 != -1) {
        emitpcode(34, 0, base, 0, fn_006e5dbe); setpcodeflags(0x8000ULL);
        emitpcode(34, 11, base, 0, fn_006e5dc2); setpcodeflags(0x8000ULL);
    } else if (fn_006e5daa[4] && (fn_006e5d96[4] & 1)) {
        emitpcode(34, 0, base, 0, fn_006e5dbe); setpcodeflags(0x8000ULL);
    }
    if (fn_006e5daa[0] || fn_006e5daa[1] || fn_006e5daa[2] || fn_006e5daa[3] || fn_006e5daa[4]) {
        if (dynamic_align_stack || fn_00725ecc) emitpcode(34, 1, 1, 0, 0);
        else emitpcode(63, 1, 1, 0, frame_size);
        setpcodeflags(0x8100ULL);
    }
    return variant == 1 ? 228 : 136;
}
static inline int native_any_saved(void)
{
    return fn_006e5daa[0] || fn_006e5daa[1] || fn_006e5daa[2] || fn_006e5daa[3] || fn_006e5daa[4];
}
static inline void native_save_spr(int spr)
{
    switch (spr) {
        case 1: emitpcode(127, 0); break;
        case 8: emitpcode(129, 0); break;
        case 9: case 256: emitpcode(128, 0); break;
        default: emitpcode(126, 0, spr); break;
    }
}
void fn_005861b0(void)
{
    int offset, i, reg, sprA = 26, sprB = 27;
    if (native_any_saved()) { emitpcode(50, 1, 1, 0, -frame_size); setpcodeflags(0x8020ULL); }
    if (dynamic_align_stack) {
        if (fn_006e5dbe == -1 || fn_006e5dc2 == -1) CError_Internal("StackFrame.c", 4205);
        if (!native_any_saved()) CError_Internal("StackFrame.c", 4209);
        emitpcode(49, 0, 1, 0, fn_006e5dbe); setpcodeflags(0x8020ULL);
        emitpcode(49, 11, 1, 0, fn_006e5dc2); setpcodeflags(0x8020ULL);
        emitpcode(103, 0, 1, 0, align_bits(frame_alignment, 1), 31); setpcodeflags(0x8000ULL);
        emitpcode(75, 0, 0); setpcodeflags(0x8000ULL);
        emitpcode(63, 11, 1, 0, frame_size); setpcodeflags(0x8000ULL);
        emitpcode(52, 11, 1, 0); setpcodeflags(0x8000ULL);
        emitpcode(34, 0, 11, 0, fn_006e5dbe - frame_size); setpcodeflags(0x8000ULL);
        emitpcode(49, 0, 1, 0, fn_006e5dbe); setpcodeflags(0x8000ULL);
        emitpcode(34, 0, 11, 0, fn_006e5dc2 - frame_size); setpcodeflags(0x8000ULL);
        emitpcode(49, 0, 1, 0, fn_006e5dc2); setpcodeflags(0x8000ULL);
    } else if (fn_006e5dc2 != -1) {
        if (fn_006e5dbe == -1) CError_Internal("StackFrame.c", 4396);
        if (!native_any_saved()) CError_Internal("StackFrame.c", 4400);
        emitpcode(49, 0, 1, 0, fn_006e5dbe); setpcodeflags(0x8000ULL);
        emitpcode(49, 11, 1, 0, fn_006e5dc2); setpcodeflags(0x8020ULL);
    } else if (fn_006e5daa[4] && (fn_006e5d96[4] & 1)) {
        emitpcode(49, 0, 1, 0, fn_006e5dbe); setpcodeflags(0x8000ULL);
    }
    offset = fn_006e5d92;
    if (fn_006e5daa[0] && (fn_006e5d96[0] & 4)) { emitpcode(128, 0); emitpcode(49, 0, 1, 0, offset); offset += 4; }
    if (fn_006e5daa[0] && (fn_006e5d96[0] & 1)) { emitpcode(127, 0); emitpcode(49, 0, 1, 0, offset); offset += 4; }
    if (fn_006e5daa[1]) { emitpcode(130, 0); emitpcode(49, 0, 1, 0, offset); offset += 4; }
    if (fn_006e5daa[0] && (fn_006e5d96[0] & 2)) { emitpcode(129, 0); emitpcode(49, 0, 1, 0, offset); offset += 4; }
    if (fn_006e5daa[2] || fn_006e5daa[3]) { emitpcode(125, 0); emitpcode(49, 0, 1, 0, offset); }
    if (fn_006e5daa[4]) {
        offset = fn_006e5dc6[4];
        for (i = 0; i < fn_0071003c[4]; i++) {
            reg = fn_0070eac0[4][i];
            if (fn_006e5d96[4] & (1U << (reg & 31))) {
                if (reg && (reg != 11 || fn_006e5dc2 == -1)) emitpcode(49, reg, 1, 0, offset);
                offset += fn_006e5dda[4];
            }
        }
    }
    if (fn_006e5daa[2]) {
        emitpcode(125, 0); emitpcode(89, 0, 0, 512); emitpcode(123, 0); setpcodeflags(0x180ULL); emitpcode(135);
        offset = fn_006e5dc6[2];
        for (i = 0; i < fn_0071003c[2]; i++) {
            reg = fn_0070eac0[2][i];
            if (fn_006e5d96[2] & (1U << (reg & 31))) {
                emitpcode(137, 0, offset); emitpcode(254, reg, 1, 0); offset += fn_006e5dda[2];
            }
        }
    }
    if (fn_006e5daa[3]) {
        emitpcode(125, 0); emitpcode(88, 0, 0, 8192); emitpcode(123, 0); setpcodeflags(0x180ULL); emitpcode(135);
        offset = fn_006e5dc6[3];
        for (i = 0; i < fn_0071003c[3]; i++) {
            reg = fn_0070eac0[3][i];
            if (fn_006e5d96[3] & (1U << (reg & 31))) {
                emitpcode(154, reg, 1, 0, offset); offset += fn_006e5dda[3];
            }
        }
    }
    if (fn_007171e0 & 0x200) { sprA = 58; sprB = 59; }
    else if (fn_007171e0 & 0x400) { sprA = 570; sprB = 571; }
    else if (fn_007171e0 & 0x800) { sprA = 574; sprB = 575; }
    offset = fn_006e5d92 + fn_006e5d86;
    if (fn_007171e0 & 4) {
        native_save_spr(sprA); emitpcode(49, 0, 1, 0, offset);
        native_save_spr(sprB); emitpcode(49, 0, 1, 0, offset + 4); offset += 8;
    }
    if (fn_007171e0 & 8) { emitpcode(126, 0, 19); emitpcode(49, 0, 1, 0, offset); offset += 4; }
    if (fn_007171e0 & 16) { emitpcode(126, 0, 18); emitpcode(49, 0, 1, 0, offset); }
    if (fn_007171e0 & 2) { emitpcode(125, 0); emitpcode(88, 0, 0, 32770); emitpcode(123, 0); }
}
#pragma pack(push, 2)
typedef struct NativeFramePosition { UInt32 words[3]; } NativeFramePosition;
typedef struct NativeFrameSource { UInt8 unknown[22]; NativeFramePosition position; } NativeFrameSource;
#pragma pack(pop)
extern NativeFrameSource *fn_007109ac;
extern NativeFramePosition *fn_00710154;
extern UInt8 *fn_00710130;
extern void fn_005820e0(NativeFramePosition *);
extern UInt8 fn_0070eff6, fn_0070eff7;
extern UInt8 fn_00699c5c[];
void generate_epilogue(NativePCBlock *block, UInt8 emitReturn)
{
    NativePCBlock *oldBlock = fn_007101cc;
    NativeFrameSource *oldSource, source;
    UInt8 helper, calls;
    int base, offset, total, i, returnOpcode;
    calls = fn_00726058 || use_helper_function(3) || use_helper_function(4) || use_helper_function(2);
    if (emitReturn && calls && frame_size) {
        helper = use_helper_function(4);
        if (!helper && fn_0070eff7 && !fn_00716c94) {
            if (!fn_00716c90 && !fn_00716c8c && frame_alignment >= 16 && fn_0070f231 && !fn_007171e0 &&
                !fn_0070f002 && !dynamic_align_stack && !fn_00725ecc && fn_00726058) helper = 2;
        }
    } else helper = 0;
    oldSource = fn_007109ac;
    if (!oldSource) {
        if (fn_00710154 && fn_00710154->words[0]) source.position = *fn_00710154;
        else { source.position = *(NativeFramePosition *)(fn_00710130 + 42); fn_005820e0((NativeFramePosition *)(fn_00710130 + 42)); }
        fn_007109ac = &source;
    }
    fn_007101cc = block;
    if (fn_00716c8c) {
        offset = fn_006e5dee[2]; base = fn_007172bc;
        if (use_helper_function(2)) {
            total = offset + fn_00716c8c * 16;
            if (total) emitpcode(63, 0, base, 0, total); else emitpcode(139, 0, base);
            call_helper_function("_restvr%d", 2, 2, 1, 1);
        } else for (i = 1; (SInt16)i <= fn_00716c8c; i++) {
            emitpcode(137, 0, offset + (fn_00716c8c - (SInt16)i) * 16); setpcodeflags(0x80ULL);
            emitpcode(249, 32 - (SInt16)i, base, 0); setpcodeflags(0x80ULL);
        }
    }
    if (dynamic_align_stack) {
        if (helper & 0x1e) CError_Internal("StackFrame.c", 1869);
        if (fn_007171e0 && fn_00725ecc) { emitpcode(139, 8, (int)fn_007172bc); setpcodeflags(0x100ULL); }
        load_gpr(fn_006771c8, 10, 1, 0, 0); setpcodeflags(0x100ULL);
        offset = 0; base = 10;
    } else {
        if (fn_00725ecc) {
            if (helper & 0x1e) CError_Internal("StackFrame.c", 1883);
            emitpcode(139, 10, (int)fn_007172bc); base = 10;
        } else base = 1;
        offset = frame_size;
    }
    if (fn_00716c88 && !fn_007171e0) {
        load_gpr(fn_00699c5c, 12, (SInt16)base, 0, offset + fn_006e5dee[1]);
        emitpcode(122, 255, 12); setpcodeflags(0x80ULL);
    }
    if (fn_006e5d76) {
        if (!fn_00725ee1) emitpcode(124, 256, (int)vrsave_register);
        else { emitpcode(34, 11, base, 0, offset + fn_006e5d82); emitpcode(124, 256, 11); }
    }
    if (fn_00716c90) restore_nonvolatile_FPRs(base, offset);
    if (fn_00716c94) restore_nonvolatile_GPRs(base, offset, emitReturn && calls && frame_size != 0);
    if (!(helper & 0x1e)) {
        if (fn_007171e0) {
            if (fn_007171e0 && dynamic_align_stack && fn_00725ecc) { emitpcode(139, 10, 8); setpcodeflags(0x100ULL); }
            returnOpcode = fn_00585b50();
            if (emitReturn) { emitpcode((SInt16)returnOpcode); setpcodeflags(0x80ULL); }
        } else {
            if (dynamic_align_stack) {
                if (calls) { load_gpr(fn_006771c8, 0, (SInt16)base, 0, fn_00716cf0->pointerSize); emitpcode(121, 0); }
                emitpcode(139, 1, base); setpcodeflags(0x100ULL);
            } else if (fn_00725ecc) {
                if (calls) {
                    load_gpr(fn_006771c8, 10, 1, 0, 0); setpcodeflags(0x100ULL);
                    load_gpr(fn_006771c8, 0, 10, 0, fn_00716cf0->pointerSize);
                    emitpcode(139, 1, 10); setpcodeflags(0x100ULL); emitpcode(121, 0);
                } else { load_gpr(fn_006771c8, 1, 1, 0, 0); setpcodeflags(0x100ULL); }
            } else if (frame_size > 0) {
                if (calls) { emitpcode(34, 0, 1, 0, frame_size + fn_00716cf0->pointerSize); emitpcode(121, 0); }
                emitpcode(63, 1, 1, 0, frame_size); setpcodeflags(0x100ULL);
            }
            if (emitReturn) { emitpcode(17); setpcodeflags(0x80ULL); }
        }
    }
    if (helper == 2) call_helper_function("__restore_frame_and_exit", 4, 2, 1, 0);
    block->flags |= 2;
    fn_007101cc = oldBlock; fn_007109ac = oldSource;
}
void generate_prologue(NativePCBlock *block)
{
    NativePCBlock *oldBlock = fn_007101cc;
    NativeFrameSource *oldSource, source;
    NativeFrameFixup *fixup;
    int base = 1, offset = 0, i, displacement, high, low;
    UInt8 helper, calls;
    calls = fn_00726058 || use_helper_function(3) || use_helper_function(4) || use_helper_function(2);
    helper = calls && frame_size ? use_helper_function(4) : 0;
    oldSource = fn_007109ac;
    source.position = *(NativeFramePosition *)(fn_00710130 + 30);
    fn_005820e0((NativeFramePosition *)(fn_00710130 + 30));
    fn_007109ac = &source; fn_007101cc = block;
    for (fixup = fn_00710878; fixup; fixup = fixup->next) {
        displacement = (fn_00716cf0->linkage + parameter_area_size + frame_alignment - 1) & ~(frame_alignment - 1);
        if (fixup->instruction->operands[2].kind != 2) CError_Internal("StackFrame.c", 1566);
        fixup->instruction->operands[2].data.immediate = -displacement;
    }
    if (setup_caller_sp && setup_caller_sp->block) {
        if (setup_caller_sp->opcode == 139 && setup_caller_sp->operands[1].kind == 0 &&
            setup_caller_sp->operands[1].arg == 4 && setup_caller_sp->operands[1].data.reg.reg == fn_007172bc)
            CError_Internal("StackFrame.c", 1584);
        fn_00716ebe = setup_caller_sp->operands[0].data.reg.reg;
        deletepcode(setup_caller_sp); setup_caller_sp = 0;
    } else if (fn_00716ebe != fn_007172bc) {
        fn_00716ebe = -1;
        if (setup_caller_sp) setup_caller_sp->flags &= ~0x80ULL;
    }
    if (align_instr1 && align_instr1->block) { deletepcode(align_instr1); align_instr1 = 0; }
    if (align_instr2 && align_instr2->block) { deletepcode(align_instr2); align_instr2 = 0; }
    if (loadvrsave && loadvrsave->block) { deletepcode(loadvrsave); loadvrsave = 0; }
    if (storevrsave && storevrsave->block) { deletepcode(storevrsave); storevrsave = 0; }
    if (helper == 4) {
        if (calls) emitpcode(129, 0);
        emitpcode(137, 11, -frame_size);
        call_helper_function("__create_frame", 4, 1, 1, 1);
    }
    if (!(helper & 0x1e)) {
        if (fn_007171e0) {
            fn_005861b0();
            if (frame_size) { if (dynamic_align_stack) { base = 11; offset = 0; } else { base = 1; offset = frame_size; } }
        } else if (frame_size) {
            if (dynamic_align_stack) { offset = 0; base = 12; } else { base = 1; offset = frame_size; }
            allocate_new_frame(11, offset ? 0 : 12);
            if (calls) { emitpcode(129, 0); emitpcode(49, 0, (int)(SInt16)base, 0, fn_00716cf0->pointerSize + offset); }
        }
    }
    if (fn_00716c90) save_nonvolatile_FPRs((SInt16)base, offset);
    if (fn_00716c94) save_nonvolatile_GPRs((SInt16)base, offset, calls && frame_size != 0);
    if (fn_00716ebe > 0 && fn_00716ebe != fn_007172bc) {
        emitpcode(139, (int)fn_00716ebe, 12); offset = 0; base = (UInt16)fn_00716ebe;
    }
    if (fn_00716c88 && !fn_007171e0) { emitpcode(130, 0); emitpcode(49, 0, (int)(SInt16)base, 0, fn_006e5dee[1] + offset); }
    if (frame_size) {
        if (fn_006e5d76) {
            emitpcode(126, 0, 256); emitpcode(49, 0, (int)(SInt16)base, 0, fn_006e5d82 + offset); vrsave_register = 0;
        }
    } else {
        if (dynamic_align_stack) CError_Internal("StackFrame.c", 1767);
        if (fn_006e5d76) emitpcode(126, (int)vrsave_register, 256);
    }
    if (fn_006e5d76) {
        high = (UInt32)fn_006e5d76 >> 16; low = (UInt16)fn_006e5d76;
        if (fn_006e5d76 == -1) emitpcode(137, 0, -1);
        else {
            if ((UInt16)high) emitpcode(89, 0, (int)vrsave_register, (UInt16)high);
            if ((UInt16)low) emitpcode(88, 0, 0, (UInt16)low);
        }
        emitpcode(124, 256, 0);
    }
    if (fn_00716c8c) {
        displacement = fn_006e5dee[2];
        if (use_helper_function(2)) {
            displacement += fn_00716c8c * 16;
            if (displacement) emitpcode(63, 0, 1, 0, displacement); else emitpcode(139, 0, 1);
            call_helper_function("_savevr%d", 2, 1, 1, 1);
        } else for (i = 1; (SInt16)i <= fn_00716c8c; i++) {
            emitpcode(137, 0, displacement + (fn_00716c8c - (SInt16)i) * 16);
            emitpcode(254, 32 - (SInt16)i, 1, 0); setpcodeflags(0x80ULL);
        }
    }
    if (fn_00725ecc) emitpcode(139, 31, 1);
    if (fn_00725dfb) do_allocate_dynamic_stack_space(1, 11, 0, large_data_near_size);
    block->flags |= 1;
    fn_007101cc = oldBlock; fn_007109ac = oldSource;
    fn_005820e0(oldSource ? &oldSource->position : 0);
}

/* Layout checks are private to this native translation unit. */
typedef char NativeFrameObjectSize[sizeof(NativePCObject) == 96 ? 1 : -1];
typedef char NativeFrameObjectInfo[offsetof(NativePCObject, localInfo) == 64 ? 1 : -1];
typedef char NativeFrameObjectDisplacement[offsetof(NativePCObject, displacement) == 72 ? 1 : -1];
typedef char NativeFrameVarInfoSize[sizeof(NativeFrameVarInfo) == 20 ? 1 : -1];
typedef char NativeFrameObjectListSize[sizeof(NativeFrameObjectList) == 8 ? 1 : -1];
typedef char NativeFrameABISize[sizeof(NativeFrameABI) == 32 ? 1 : -1];
typedef char NativeFrameTracebackSize[sizeof(NativeTraceback) == 12 ? 1 : -1];
typedef char NativeFrameTracebackVectorSize[sizeof(NativeTracebackVector) == 2 ? 1 : -1];
typedef char NativeFrameSourcePositionOffset[offsetof(NativeFrameSource, position) == 22 ? 1 : -1];
