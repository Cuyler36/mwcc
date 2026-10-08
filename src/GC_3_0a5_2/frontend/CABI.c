/* Native GC 3.0a5.2 CABI records, kept private until callers are ported. */
#include "compiler/common.h"
#pragma pack(push, 2)
typedef struct NativeType {
    UInt8 kind, padding;
    SInt32 size;
} NativeType;
typedef struct NativeBitField {
    NativeType type;
    NativeType *base;
    UInt8 offset, width;
} NativeBitField;
typedef struct NativeObject {
    UInt8 unknown_00[12];
    void *name;
    NativeType *type;
    UInt32 flags;
    UInt16 storageClass, objectFlags;
} NativeObject;
typedef struct NativeResultInfo {
    SInt32 size, offset, alignment;
} NativeResultInfo;
#pragma pack(pop)
extern NativeType stsignedlong, stunsignedlong, stunsignedchar;
extern void CError_Internal(const char *, int);
extern SInt16 CMach_GetTypeAlign(NativeType *, SInt32);
extern UInt8 CClass_ReferenceArgument(NativeType *), CMach_PassAddressOf(NativeType *);
extern NativeObject *CParser_NewCompilerDefDataObject(void);
extern void *CParser_GetUniqueName(void);
extern void CParser_UpdateObject(NativeObject *, int);
extern void CMangler_SetupGuardVarName(NativeObject *, NativeObject *);
extern void CInit_DeclareData(NativeObject *, void *, void *, SInt32);
extern void *create_objectrefnode(NativeObject *);
extern void *checkreference(void *);
extern void *intconstnode(NativeType *, SInt32);
extern void *makediadicnode(void *, void *, int);

void CABI_ReverseBitField(NativeBitField *field)
{
    UInt32 bits;
    switch (field->base->size) {
        case 1: bits = 8; break;
        case 2: bits = 16; break;
        case 4: bits = 32; break;
        case 8: bits = 64; break;
        default: CError_Internal("CABI.c", 330); break;
    }
    field->offset = bits - field->offset - field->width;
}

SInt16 CABI_StructSizeAlignValue(NativeType *type, SInt32 mode, SInt32 mask)
{
    SInt32 alignment = CMach_GetTypeAlign(type, mode);
    if (alignment > 1)
        return (alignment - (mask & (alignment - 1U))) & (alignment - 1U);
    return 0;
}

UInt8 CABI_PassedByReference(NativeType *type)
{
    if (type->kind == 6 && CClass_ReferenceArgument(type)) return 1;
    if (CMach_PassAddressOf(type)) return 1;
    return 0;
}

void CABI_GetVTableHeaderInfo(NativeResultInfo *result)
{
    result->size = stsignedlong.size + 4;
    result->offset = 0;
    result->alignment = 4;
}

NativeType *CABI_GetPtrDiffTType(void) { return &stsignedlong; }
NativeType *CABI_GetSizeTType(void) { return &stunsignedlong; }
int CABI_GetStructResultArgumentIndex(void) { return 0; }

NativeObject *CABI_NewGuardVariable(NativeObject *object)
{
    NativeObject *guard;
    if (!object) CError_Internal("CABI.c", 344);
    guard = CParser_NewCompilerDefDataObject();
    guard->type = &stunsignedchar;
    guard->name = CParser_GetUniqueName();
    guard->storageClass = object->storageClass;
    guard->flags |= object->flags & 0x60000;
    CParser_UpdateObject(guard, 0);
    CMangler_SetupGuardVarName(guard, object);
    CInit_DeclareData(guard, 0, 0, guard->type->size);
    return guard;
}

void *CABI_AcquireGuardVariable(NativeObject *object)
{
    return checkreference(create_objectrefnode(object));
}

void *CABI_ReleaseGuardVariable(NativeObject *object)
{
    void *expr = checkreference(create_objectrefnode(object));
    return makediadicnode(expr, intconstnode(&stunsignedchar, 1), 30);
}

int CABI_GetVTableOffset(void) { return 0; }
int CABI_ComputeNewArrayPadding(void) { return 16; }
UInt8 CABI_DestructorReturnsThis(void) { return 1; }
UInt8 CABI_ConstructorReturnsThis(void) { return 1; }
NativeObject *CABI_GetDestructorObject(NativeObject *object, UInt8 mode) { return object; }

#pragma pack(push, 2)
typedef struct NativeClass NativeClass;
typedef struct NativeBase {
    struct NativeBase *next;
    NativeClass *base;
    SInt32 offset, vOffset;
    UInt8 access, isVirtual;
} NativeBase;
struct NativeClass {
    NativeType type;
    void *nameSpace;
    UInt8 unknown_0a[4];
    NativeBase *bases;
    void *vBases, *members, *vTable;
    UInt8 unknown_1e[4];
    UInt32 flags;
    SInt32 baseSize;
    UInt16 align, eflags;
    UInt8 unknown_2e, state;
};
typedef struct NativeObjectList {
    struct NativeObjectList *next;
    NativeObject *object;
} NativeObjectList;
typedef struct NativeNode {
    UInt8 kind, padding[3];
    NativeType *type;
    UInt32 flags;
    UInt8 unknown_0c[4];
    struct NativeNode *function;
    void *args;
    NativeType *functionType;
} NativeNode;
#pragma pack(pop)
extern NativeObjectList *arguments;
extern NativeType void_ptr;
extern void *galloc(SInt32), *lalloc(SInt32);
extern void memclrw(void *, SInt32);
extern NativeObjectList *CScope_FindName(void *, void *);
extern UInt8 CClass_GetOverrideKind(NativeObject *, NativeObject *, int);
extern void *makemonadicnode(void *, int);

void CABI_AddVTable(NativeClass *tclass)
{
    tclass->vTable = galloc(16);
    memclrw(tclass->vTable, 16);
}

NativeObject *CABI_FindSharedVTableMember(NativeClass *tclass, NativeObject *key)
{
    NativeObjectList *entry;
    NativeObject *object, *result;
    NativeBase *base;
    for (entry = CScope_FindName(tclass->nameSpace, key->name); entry; entry = entry->next) {
        object = entry->object;
        if (*(UInt8 *)object == 5) {
            if (*((UInt8 *)object + 2) == 4 && CClass_GetOverrideKind(object, key, 0) == 1)
                return object;
        }
    }
    for (base = tclass->bases; base; base = base->next)
        if (!base->isVirtual && !base->offset && !base->vOffset && base->base->vTable) {
            result = CABI_FindSharedVTableMember(base->base, key);
            if (result) return result;
        }
    return 0;
}

NativeObject *CABI_ThisArg(void)
{
    if (!(arguments && arguments->object->type->kind == 12))
        CError_Internal("CABI.c", 1539);
    return arguments->object;
}

static inline NativeObject *native_this_arg(void)
{
    if (!(arguments && arguments->object->type->kind == 12))
        CError_Internal("CABI.c", 1539);
    return arguments->object;
}

NativeNode *CABI_MakeThisExpr(NativeClass *tclass, SInt32 offset)
{
    NativeNode *expr;
    if (tclass) {
        expr = checkreference(create_objectrefnode(native_this_arg()));
        if (tclass->flags & 1) expr = makemonadicnode(expr, 4);
    } else {
        expr = checkreference(create_objectrefnode(native_this_arg()));
        expr->type = &void_ptr;
    }
    if (offset) expr = makediadicnode(expr, intconstnode(&stunsignedlong, offset), 15);
    return expr;
}

SInt32 CABI_FindNVBase(NativeClass *tclass, NativeClass *baseClass, SInt32 offset)
{
    NativeBase *base;
    SInt32 found;
    if (tclass == baseClass) return offset;
    for (base = tclass->bases; base; base = base->next)
        if (!base->isVirtual && (found = CABI_FindNVBase(base->base, baseClass, offset + base->offset)) >= 0)
            return found;
    return -1;
}

#pragma pack(push, 2)
typedef struct NativeNodeList {
    struct NativeNodeList *next;
    NativeNode *node;
} NativeNodeList;
#pragma pack(pop)
extern NativeNode *CExpr_NewENode(UInt8);
extern NativeNode *CExpr_New_EOBJREF_Node(NativeObject *, UInt8);
extern NativeType stvoid, stsignedshort;

NativeNode *CABI_DestroyObject(NativeObject *dtor, NativeNode *objectExpr, UInt8 mode, UInt8 flag1, UInt8 flag2)
{
    NativeNode *expr;
    NativeNodeList *list;
    SInt16 value;
    switch (mode) {
        case 2: case 3: value = flag2 ? 1 : -1; break;
        case 1: value = -1; break;
        case 0: value = 0; break;
        default: CError_Internal("CABI.c", 4559); break;
    }
    expr = CExpr_NewENode(0x39);
    expr->padding[0] = 200;
    expr->type = &stvoid;
    expr->function = CExpr_New_EOBJREF_Node(dtor, 1);
    if (flag1) expr->function->flags |= 8;
    expr->functionType = dtor->type;
    dtor->objectFlags |= 1;
    list = lalloc(8);
    list->node = objectExpr;
    expr->args = list;
    list->next = lalloc(8);
    list = list->next;
    list->next = 0;
    list->node = intconstnode(&stsignedshort, value);
    return expr;
}

extern UInt8 structure_alignment;
extern SInt16 CMach_MemberAlignValue(NativeType *, SInt32);
SInt32 CABI_GetCtorOffsetOffset(NativeClass *tclass, NativeClass *baseClass)
{
    SInt32 size = tclass->baseSize, baseSize;
    UInt8 saved;
    if (baseClass) {
        baseSize = CABI_FindNVBase(tclass, baseClass, 0);
        if (baseSize < 0) CError_Internal("CABI.c", 1788);
        size -= baseSize;
    }
    saved = structure_alignment;
    if (tclass->eflags & 0xf0) structure_alignment = ((tclass->eflags & 0xf0) >> 4) - 1;
    size += CMach_MemberAlignValue(&stunsignedlong, size);
    structure_alignment = saved;
    return size;
}

#pragma pack(push, 2)
typedef struct NativeOffsetPath {
    struct NativeOffsetPath *next;
    SInt32 offset;
} NativeOffsetPath;
#pragma pack(pop)

NativeOffsetPath *CABI_GetVBasePath(NativeClass *tclass, NativeClass *target)
{
    NativeBase *directBase, *base;
    NativeOffsetPath *path, *best, *step, *result;
    int length;
    SInt16 bestLength;
    for (directBase = tclass->bases; directBase; directBase = directBase->next)
        if (directBase->base == target && directBase->isVirtual) {
            result = lalloc(8);
            result->next = 0;
            result->offset = directBase->offset;
            return result;
        }
    best = 0;
    for (base = tclass->bases; base; base = base->next) {
        path = CABI_GetVBasePath(base->base, target);
        if (path) {
            length = 1;
            for (step = path->next; step; step = step->next) length++;
            if (base->isVirtual) length++;
            if (!best || (SInt16)length < bestLength) {
                if (base->isVirtual) {
                    best = lalloc(8);
                    best->next = path;
                    best->offset = base->offset;
                } else {
                    best = path;
                    path->offset += base->offset;
                }
                bestLength = length;
            }
        }
    }
    return best;
}

#pragma pack(push, 2)
typedef struct NativeVBase {
    struct NativeVBase *next;
    NativeClass *base;
    SInt32 offset;
} NativeVBase;
typedef struct NativeStatement {
    struct NativeStatement *next;
    UInt8 kind, unknown_05[5];
    NativeNode *expr;
    UInt8 unknown_0e[20];
} NativeStatement;
typedef struct NativeVTableOffset {
    struct NativeVTableOffset *next;
    SInt32 offset;
    UInt8 flag, padding;
} NativeVTableOffset;
#pragma pack(pop)
NativeVTableOffset *trans_vtboffsets;
extern NativeVBase *CClass_FindVirtualBase(NativeClass *, NativeClass *);
extern NativeStatement *CFunc_InsertStatement(UInt8, NativeStatement *);

static inline UInt8 native_seen_vtable_offset(SInt32 offset, UInt8 flag)
{
    NativeVTableOffset *entry;
    for (entry = trans_vtboffsets; entry; entry = entry->next)
        if (entry->offset == offset && entry->flag == flag) return 1;
    entry = lalloc(10);
    entry->next = trans_vtboffsets;
    entry->offset = offset;
    entry->flag = flag;
    trans_vtboffsets = entry;
    return 0;
}

NativeNode *CABI_InitVBasePtr1(NativeNode *expr, NativeClass *root, NativeClass *tclass,
    NativeClass *target, SInt32 offset)
{
    NativeBase *base;
    NativeNode *pointer;
    SInt32 delta;
    for (base = tclass->bases; base; base = base->next) {
        if (base->base == target && base->isVirtual) {
            delta = offset + base->offset;
            if (!native_seen_vtable_offset(delta, 0)) {
                pointer = checkreference(create_objectrefnode(native_this_arg()));
                pointer->type = &void_ptr;
                if (delta) pointer = makediadicnode(pointer, intconstnode(&stunsignedlong, delta), 15);
                expr = makediadicnode(makemonadicnode(pointer, 4), expr, 30);
            }
        }
        if (base->isVirtual) delta = CClass_FindVirtualBase(root, base->base)->offset;
        else delta = offset + base->offset;
        expr = CABI_InitVBasePtr1(expr, root, base->base, target, delta);
    }
    return expr;
}

NativeStatement *CABI_InitVBasePtrs(NativeStatement *stmt, NativeClass *tclass)
{
    NativeVBase *base;
    NativeNode *expr, *pointer;
    trans_vtboffsets = 0;
    for (base = tclass->vBases; base; base = base->next) {
        pointer = checkreference(create_objectrefnode(native_this_arg()));
        pointer->type = &void_ptr;
        if (base->offset) pointer = makediadicnode(pointer, intconstnode(&stunsignedlong, base->offset), 15);
        expr = CABI_InitVBasePtr1(pointer, tclass, tclass, base->base, 0);
        stmt = CFunc_InsertStatement(4, stmt);
        stmt->expr = expr;
    }
    return stmt;
}

#pragma pack(push, 2)
typedef struct NativeCopyRegion {
    struct NativeCopyRegion *next;
    NativeType *type;
    SInt32 start, end;
    UInt8 flag, padding;
} NativeCopyRegion;
typedef struct NativeFuncArg {
    struct NativeFuncArg *next;
    UInt8 unknown_04[4];
    void *defaultExpr;
    NativeType *type;
    UInt32 qualifiers;
    UInt8 unknown_14[3], ellipsis;
} NativeFuncArg;
typedef struct NativeTypeFunc {
    NativeType type;
    NativeFuncArg *args;
    UInt8 unknown_0a[4];
    NativeType *returnType;
    UInt8 unknown_12[4];
    UInt32 flags;
    UInt8 unknown_1a[4];
    NativeClass *tclass;
    UInt8 unknown_22[8];
    UInt8 explicitArgs, padding;
} NativeTypeFunc;
typedef struct NativeScopeResult {
    UInt8 unknown_00[8];
    NativeObject *object;
    NativeObjectList *objects;
    UInt8 unknown_10[32];
} NativeScopeResult;
#pragma pack(pop)
extern UInt8 CScope_FindClassMemberObject(NativeClass *, NativeScopeResult *, void *);
extern void *CMangler_OperatorName(SInt32);
extern NativeObject *newh_func;

NativeCopyRegion *CABI_AppendCopyRegion(NativeCopyRegion *list, NativeType *type,
    SInt32 offset, UInt8 flag)
{
    NativeCopyRegion *entry;
    SInt32 end;
    if (type->kind == 8) type = ((NativeBitField *)type)->base;
    end = offset + type->size;
    if (flag) {
        for (entry = list; entry; entry = entry->next) {
            if (entry->flag) {
                if (entry->start <= offset && entry->end >= end) return list;
                if (entry->start >= offset && entry->end <= end) {
                    entry->type = type;
                    entry->start = offset;
                    entry->end = end;
                    for (entry = entry->next; entry; entry = entry->next)
                        if (entry->start >= offset && entry->end <= end)
                            entry->end = entry->start;
                    return list;
                }
            }
        }
    }
    if (list) {
        for (entry = list; entry->next; entry = entry->next) ;
        entry->next = lalloc(sizeof(NativeCopyRegion));
        entry = entry->next;
    } else list = entry = lalloc(sizeof(NativeCopyRegion));
    entry->next = 0;
    entry->type = type;
    entry->start = offset;
    entry->end = end;
    entry->flag = flag;
    return list;
}

static inline UInt8 native_is_operator_new(NativeObject *object)
{
    return *(UInt8 *)object == 5 && object->type->kind == 7 &&
        ((NativeTypeFunc *)object->type)->args &&
        ((NativeTypeFunc *)object->type)->args->type == &stunsignedlong &&
        !((NativeTypeFunc *)object->type)->args->next;
}

NativeObject *CABI_ConstructorCallsNew(NativeClass *tclass)
{
    NativeScopeResult result;
    NativeObjectList *entry;
    if (tclass->flags & 1) {
        if (CScope_FindClassMemberObject(tclass, &result, CMangler_OperatorName(0x155))) {
            if (result.object) {
                if (native_is_operator_new(result.object)) return result.object;
            } else {
                for (entry = result.objects; entry; entry = entry->next)
                    if (native_is_operator_new(entry->object)) return entry->object;
            }
        }
        return newh_func;
    }
    return 0;
}

NativeFuncArg *CABI_GetFirstRealArgument(NativeTypeFunc *type)
{
    NativeFuncArg *arg;
    NativeClass *tclass;
    if (type->type.kind != 7) CError_Internal("CABI.c", 2236);
    arg = type->args;
    if ((type->flags & 0x10) && !type->explicitArgs) {
        tclass = type->tclass;
        if (!arg) CError_Internal("CABI.c", 2244);
        arg = arg->next;
        if (type->flags & 0x2000) return 0;
        if ((tclass->flags & 0x20) && (type->flags & 0x1000)) {
            if (!arg) CError_Internal("CABI.c", 2264);
            arg = arg->next;
        }
    }
    return arg;
}

void *CABI_GetVBaseCTorArg(NativeClass *tclass, void *unused, UInt8 flag)
{
    if (tclass->flags & 0x20) return intconstnode(&stsignedshort, flag ? 1 : 0);
    return 0;
}

void *fn_00550090(NativeObject *object)
{
    return checkreference(create_objectrefnode(object));
}

#pragma pack(push, 2)
typedef struct NativeMember {
    UInt8 kind, access, subtype, padding;
    struct NativeMember *next;
    void *name;
    NativeType *type;
    UInt32 qualifiers;
    SInt32 offset;
} NativeMember;
typedef struct NativeLayoutBases {
    struct NativeLayoutBases *next;
    NativeBase *nonvirtual, *virtualBase;
    UInt8 useZero, occupied;
} NativeLayoutBases;
typedef struct NativeClassLayout {
    void **entries;
    NativeMember *zeroVPtr;
    UInt16 count, zeroVPtrIndex;
    UInt8 needsVTable;
} NativeClassLayout;
typedef struct NativeVTable {
    NativeObject *object;
    SInt32 size, baseSize;
    SInt32 zeroVPtrOffset;
} NativeVTable;
#pragma pack(pop)
extern void *vptr_name;
extern void *CMangler_VTableName(NativeClass *);
extern NativeType *CDecl_NewOpaqueType(SInt32, SInt32);

void CABI_AllocateZeroVTablePointer(NativeLayoutBases *bases,
    NativeClassLayout *layout, NativeClass *tclass)
{
    NativeClass *base;
    NativeMember *member;
    SInt32 index;
    if (!tclass->vTable) {
        tclass->vTable = galloc(sizeof(NativeVTable));
        memclrw(tclass->vTable, sizeof(NativeVTable));
        layout->zeroVPtrIndex = layout->count - 1;
    }
    if (bases && bases->useZero) {
        if (!bases->nonvirtual) CError_Internal("CABI.c", 1386);
        base = bases->nonvirtual->base;
    } else base = 0;
    if (base) {
        ((NativeVTable *)tclass->vTable)->zeroVPtrOffset = ((NativeVTable *)base->vTable)->zeroVPtrOffset;
        layout->zeroVPtr = 0;
    } else {
        member = galloc(sizeof(NativeMember));
        memclrw(member, sizeof(NativeMember));
        member->kind = 4;
        member->access = 0;
        member->name = vptr_name;
        member->type = &void_ptr;
        layout->zeroVPtr = member;
        index = layout->zeroVPtrIndex;
        for (;;) {
            if (index < 0) {
                member->next = tclass->members;
                tclass->members = member;
                break;
            }
            if (!layout->entries[index]) CError_Internal("CABI.c", 1418);
            if (*(UInt8 *)layout->entries[index] == 4) {
                member->next = ((NativeMember *)layout->entries[index])->next;
                ((NativeMember *)layout->entries[index])->next = member;
                break;
            }
            --index;
        }
    }
}

void CABI_AllocateVTable(NativeLayoutBases *bases, NativeClassLayout *layout,
    NativeClass *tclass)
{
    SInt32 size = 0;
    SInt32 baseSize = stsignedlong.size + 4;
    SInt32 index;
    NativeClass *firstBase;
    NativeLayoutBases *entry;
    NativeObject *member, *inherited, *object;
    if (bases && bases->useZero) {
        if (!bases->nonvirtual) CError_Internal("CABI.c", 1455);
        firstBase = bases->nonvirtual->base;
    } else {
        firstBase = 0;
        if (tclass->flags & 0x2010) size = void_ptr.size;
        else size = baseSize;
    }
    for (entry = bases; entry; entry = entry->next) {
        if (entry->nonvirtual && entry->nonvirtual->base->vTable) {
            entry->nonvirtual->vOffset = size;
            size += ((NativeVTable *)entry->nonvirtual->base->vTable)->baseSize;
        }
    }
    for (index = 0; index < layout->count; ++index) {
        member = layout->entries[index];
        if (!member) CError_Internal("CABI.c", 1486);
        if (*(UInt8 *)member == 5 && *((UInt8 *)member + 2) == 4) {
            if (firstBase && (inherited = CABI_FindSharedVTableMember(firstBase, member))) {
                *(SInt32 *)((UInt8 *)member->type + 0x22) =
                    *(SInt32 *)((UInt8 *)inherited->type + 0x22);
            } else {
                *(SInt32 *)((UInt8 *)member->type + 0x22) = size;
                size += 4;
            }
        }
    }
    ((NativeVTable *)tclass->vTable)->baseSize = size;
    for (entry = bases; entry; entry = entry->next) {
        if (entry->virtualBase && entry->virtualBase->base->vTable) {
            entry->virtualBase->vOffset = size;
            size += ((NativeVTable *)entry->virtualBase->base->vTable)->baseSize;
        }
    }
    object = CParser_NewCompilerDefDataObject();
    if (tclass->eflags & 1) object->objectFlags |= 0x10;
    if (tclass->eflags & 2) object->objectFlags |= 0x20;
    if (tclass->eflags & 4) object->objectFlags |= 0x40;
    object->name = CMangler_VTableName(tclass);
    object->type = CDecl_NewOpaqueType(size, 4);
    object->flags = 1;
    *(void **)((UInt8 *)object + 8) = tclass->nameSpace;
    switch ((SInt8)tclass->state) {
        case 0:
            object->storageClass = 0x102;
            object->flags |= 0x20000;
            break;
    }
    CParser_UpdateObject(object, 0);
    ((NativeVTable *)tclass->vTable)->object = object;
    ((NativeVTable *)tclass->vTable)->size = size;
}

extern UInt8 anyerrors, filesyminfo;
extern NativeClass *current_class;
extern void *CTemplTool_PushInstance(int, NativeObject *);
extern void CTemplTool_PopInstance(void *);
extern void CScope_SetFunctionScope(NativeObject *, void *), CScope_RestoreScope(void *);
extern void CFunc_FuncGenSetup(int, NativeStatement *, NativeObject *, int);
extern void CFunc_SetupNewFuncArgs(int, NativeObject *, NativeFuncArg *);
extern void CFunc_ErrorCheck(NativeObject *, NativeStatement *);
extern void CFunc_DestructorCleanup(NativeStatement *), CFunc_CodeCleanup(NativeStatement *);
extern void CFunc_Gen(NativeStatement *, NativeObject *);
extern void CABI_TransDestructor(NativeObject *, NativeObject *, NativeStatement *, NativeClass *, UInt8);
extern void CABI_TransConstructor(NativeObject *, NativeStatement *, NativeClass *, UInt8, UInt8);

static inline void native_apply_class_flags(NativeObject *object, UInt8 flags)
{
    if (flags & 1) object->objectFlags |= 0x10;
    if (flags & 2) object->objectFlags |= 0x20;
    if (flags & 4) object->objectFlags |= 0x40;
}

void CABI_MakeDefaultDestructor(NativeClass *tclass, NativeObject *func)
{
    UInt8 savedebug;
    UInt8 savedscope[16];
    NativeStatement firststmt, returnstmt;
    void *savedstate;
    if (anyerrors || *((UInt8 *)func + 1) == 3) return;
    native_apply_class_flags(func, tclass->eflags);
    savedstate = CTemplTool_PushInstance(0, func);
    CScope_SetFunctionScope(func, savedscope);
    CFunc_FuncGenSetup(0, &firststmt, func, 0);
    savedebug = filesyminfo;
    filesyminfo = 0;
    CFunc_SetupNewFuncArgs(0, func, ((NativeTypeFunc *)func->type)->args);
    firststmt.next = &returnstmt;
    memclrw(&returnstmt, sizeof(NativeStatement));
    returnstmt.kind = 8;
    CABI_TransDestructor(func, func, &firststmt, tclass, 0);
    CFunc_CodeCleanup(&firststmt);
    CFunc_Gen(&firststmt, func);
    CScope_RestoreScope(savedscope);
    CTemplTool_PopInstance(savedstate);
    filesyminfo = savedebug;
}

void CABI_FinishDestructor(NativeObject *func, NativeStatement *stmt, NativeClass *tclass,
    UInt8 cleanup)
{
    CABI_TransDestructor(func, func, stmt, tclass, 0);
    if (cleanup) CFunc_ErrorCheck(func, stmt);
    CFunc_DestructorCleanup(stmt);
    CFunc_CodeCleanup(stmt);
    CFunc_Gen(stmt, func);
}

static inline void native_default_constructor(NativeClass *tclass, NativeObject *func,
    UInt8 copy)
{
    UInt8 savedebug;
    UInt8 savedscope[16];
    NativeStatement firststmt, returnstmt;
    void *savedstate;
    if (anyerrors || *((UInt8 *)func + 1) == 3) return;
    native_apply_class_flags(func, tclass->eflags);
    savedstate = CTemplTool_PushInstance(0, func);
    CScope_SetFunctionScope(func, savedscope);
    CFunc_FuncGenSetup(0, &firststmt, func, 0);
    savedebug = filesyminfo;
    filesyminfo = 0;
    CFunc_SetupNewFuncArgs(0, func, ((NativeTypeFunc *)func->type)->args);
    if (tclass->flags & 0x20) arguments->next->object->name = CParser_GetUniqueName();
    firststmt.next = &returnstmt;
    memclrw(&returnstmt, sizeof(NativeStatement));
    returnstmt.kind = 8;
    CABI_TransConstructor(func, &firststmt, current_class, copy, 0);
    CFunc_DestructorCleanup(&firststmt);
    CFunc_CodeCleanup(&firststmt);
    CFunc_Gen(&firststmt, func);
    CScope_RestoreScope(savedscope);
    CTemplTool_PopInstance(savedstate);
    filesyminfo = savedebug;
}

void CABI_MakeDefaultConstructor(NativeClass *tclass, NativeObject *func)
{
    native_default_constructor(tclass, func, 0);
}

void CABI_MakeDefaultCopyConstructor(NativeClass *tclass, NativeObject *func)
{
    native_default_constructor(tclass, func, 1);
}

void CABI_FinishConstructor(NativeObject *func, NativeStatement *stmt, void *unused,
    UInt8 copy, UInt8 cleanup, UInt8 mode)
{
    if (!current_class) CError_Internal("CABI.c", 2993);
    CABI_TransConstructor(func, stmt, current_class, copy, mode);
    if (cleanup) CFunc_ErrorCheck(func, stmt);
    CFunc_DestructorCleanup(stmt);
    CFunc_CodeCleanup(stmt);
    CFunc_Gen(stmt, func);
}

extern NativeObject *CClass_Destructor(NativeClass *);
extern void CClass_NewAccessCheck(int, NativeObject *, NativeClass *, UInt8, NativeObject *, int);

NativeStatement *CABI_DestroyBases(NativeObject *func, NativeStatement *stmt,
    NativeBase *base, UInt8 flag)
{
    NativeObject *dtor;
    for (; base; base = base->next) {
        if (!base->isVirtual && (dtor = CClass_Destructor(base->base))) {
            CClass_NewAccessCheck(0, func, base->base, *((UInt8 *)dtor + 1), dtor, 0);
            stmt = CABI_DestroyBases(func, stmt, base->next, flag);
            stmt = CFunc_InsertStatement(4, stmt);
            stmt->expr = CABI_DestroyObject(dtor, CABI_MakeThisExpr(0, base->offset), 0, 1, 0);
            break;
        }
    }
    return stmt;
}

NativeStatement *CABI_DestroyVBases(NativeObject *func, NativeStatement *stmt,
    NativeVBase *base)
{
    NativeObject *dtor;
    for (; base; base = base->next) {
        if ((dtor = CClass_Destructor(base->base))) {
            stmt = CABI_DestroyVBases(func, stmt, base->next);
            CClass_NewAccessCheck(0, func, base->base, *((UInt8 *)dtor + 1), dtor, 0);
            stmt = CFunc_InsertStatement(4, stmt);
            stmt->expr = CABI_DestroyObject(dtor, CABI_MakeThisExpr(0, base->offset), 0, 1, 0);
            break;
        }
    }
    return stmt;
}

extern NativeObject *destroyarray_func;
extern NativeNode *funccallexpr(NativeObject *, NativeNode *, NativeNode *, NativeNode *, NativeNode *);

NativeStatement *CABI_DestroyMembers(NativeStatement *stmt, NativeMember *member,
    NativeClass *tclass)
{
    NativeType *type;
    NativeObject *dtor;
    NativeNode *ref, *object;
    SInt32 count;
    for (; member; member = member->next) {
        type = member->type;
        if (type->kind == 13) {
            if (!type->size) return stmt;
            do type = *(NativeType **)((UInt8 *)type + 6); while (type->kind == 13);
            if (type->kind == 6 && (dtor = CClass_Destructor((NativeClass *)type))) {
                CClass_NewAccessCheck(0, (NativeObject *)type, (NativeClass *)type, *((UInt8 *)dtor + 1), dtor, 0);
                stmt = CABI_DestroyMembers(stmt, member->next, tclass);
                ref = CExpr_New_EOBJREF_Node(dtor, 1);
                ref->flags |= 8;
                stmt = CFunc_InsertStatement(4, stmt);
                object = CABI_MakeThisExpr(tclass, member->offset);
                count = member->type->size / type->size;
                stmt->expr = funccallexpr(destroyarray_func, object, ref,
                    intconstnode(&stsignedlong, type->size), intconstnode(&stsignedlong, count));
                return stmt;
            }
        } else if (type->kind == 6 && (dtor = CClass_Destructor((NativeClass *)type))) {
            CClass_NewAccessCheck(0, (NativeObject *)type, (NativeClass *)type, *((UInt8 *)dtor + 1), dtor, 0);
            stmt = CABI_DestroyMembers(stmt, member->next, tclass);
            stmt = CFunc_InsertStatement(4, stmt);
            stmt->expr = CABI_DestroyObject(dtor, CABI_MakeThisExpr(tclass, member->offset), 1, 1, 0);
            return stmt;
        }
    }
    return stmt;
}

extern NativeObject *CFunc_CreateTempObject(NativeType *);

NativeStatement *CABI_InitVBaseCtorOffsets(NativeStatement *stmt, NativeClass *tclass)
{
    NativeVBase *base;
    NativeObject *temp = 0;
    NativeOffsetPath *path;
    NativeNode *object, *expr, *target;
    SInt32 baseOffset, ctorOffset;
    for (base = tclass->vBases; base; base = base->next) {
        if (*((UInt8 *)base + 16)) {
            if (!temp) temp = CFunc_CreateTempObject(&void_ptr);
            baseOffset = CClass_FindVirtualBase(tclass, base->base)->offset;
            ctorOffset = CABI_GetCtorOffsetOffset(base->base, 0);
            path = CABI_GetVBasePath(tclass, base->base);
            if (!path) CError_Internal("CABI.c", 1737);
            object = checkreference(create_objectrefnode(native_this_arg()));
            object->type = &void_ptr;
            if (path->offset) object = makediadicnode(object, intconstnode(&stunsignedlong, path->offset), 15);
            object = makemonadicnode(object, 4);
            while ((path = path->next)) {
                if (path->offset) object = makediadicnode(object, intconstnode(&stunsignedlong, path->offset), 15);
                object = makemonadicnode(object, 4);
            }
            if (!object) CError_Internal("CABI.c", 1825);
            expr = makediadicnode(checkreference(create_objectrefnode(temp)), object, 30);
            stmt = CFunc_InsertStatement(4, stmt);
            stmt->expr = expr;
            target = makemonadicnode(makediadicnode(checkreference(create_objectrefnode(temp)),
                intconstnode(&stunsignedlong, ctorOffset), 15), 4);
            target->type = &stunsignedlong;
            expr = checkreference(create_objectrefnode(temp));
            object = checkreference(create_objectrefnode(native_this_arg()));
            object->type = &void_ptr;
            if (baseOffset) object = makediadicnode(object, intconstnode(&stunsignedlong, baseOffset), 15);
            expr = makediadicnode(target, makediadicnode(object, expr, 16), 30);
            stmt = CFunc_InsertStatement(4, stmt);
            stmt->expr = expr;
        }
    }
    return stmt;
}

#pragma pack(push, 2)
typedef struct NativeVTableInit {
    NativeClass *root, *tclass;
    void *baseReference;
    void *path;
    NativeClass *baseClass;
    SInt32 offset, vOffset;
    UInt8 direct, virtualBase;
} NativeVTableInit;
#pragma pack(pop)
extern NativeType signedlong_ptr;
extern NativeNode *fn_00520110(NativeNode *, NativeNode *);
extern NativeNode *CClass_AccessPathCast(void *, NativeNode *, int);

NativeStatement *CABI_InitVTablePtrs(NativeStatement *stmt, NativeVTableInit *info,
    UInt8 flag, UInt8 emit)
{
    NativeNode *value, *object, *target;
    NativeBase *base;
    NativeVBase *virtualBase;
    NativeVTableInit child;
    SInt32 offset = info->offset + ((NativeVTable *)info->tclass->vTable)->zeroVPtrOffset;
    if (emit && !native_seen_vtable_offset(offset, flag)) {
        value = CExpr_New_EOBJREF_Node(((NativeVTable *)info->root->vTable)->object, 1);
        value->type = &signedlong_ptr;
        if (info->vOffset) value = fn_00520110(value, intconstnode(&stsignedlong, info->vOffset));
        value->type = &void_ptr;
        object = CABI_MakeThisExpr(info->root, 0);
        if (info->virtualBase && !info->direct) {
            object = CClass_AccessPathCast(info->baseReference, object, 0);
            object->type = &signedlong_ptr;
            offset = ((NativeVTable *)info->tclass->vTable)->zeroVPtrOffset;
            if (offset) object = fn_00520110(object, intconstnode(&stsignedlong, offset));
        } else {
            object->type = &signedlong_ptr;
            if (offset) object = fn_00520110(object, intconstnode(&stsignedlong, offset));
        }
        target = makemonadicnode(object, 4);
        target->type = &void_ptr;
        stmt = CFunc_InsertStatement(4, stmt);
        stmt->expr = makediadicnode(target, value, 30);
    }
    for (base = info->tclass->bases; base; base = base->next) {
        if (base->base->vTable) {
            child = *info;
            child.tclass = base->base;
            info->path = &child.path;
            child.baseClass = base->base;
            child.path = 0;
            if (base->isVirtual) {
                virtualBase = CClass_FindVirtualBase(info->root, base->base);
                child.offset = virtualBase->offset;
                child.vOffset = *(SInt32 *)((UInt8 *)virtualBase + 12);
                child.virtualBase = 1;
                emit = 1;
            } else {
                child.offset += base->offset;
                child.vOffset += base->vOffset;
                emit = !*((UInt8 *)base + 18);
            }
            stmt = CABI_InitVTablePtrs(stmt, &child, 0, emit);
            info->path = 0;
        }
    }
    return stmt;
}

extern void *newlabel(void);
extern UInt8 CABI_IsSimpleCtorDtor(NativeStatement *, UInt8);
extern NativeNode *fn_0051f620(NativeNode *, NativeNode *);
extern UInt8 fn_0070f1e7;
extern NativeObject *rt_unreg_class;
extern NativeObject *fn_004550c0(NativeClass *, void *, void *, void *, UInt8 *);

static inline void native_set_target(NativeStatement *stmt, void *label)
{
    *(void **)((UInt8 *)stmt + 14) = label;
}
static inline void native_bind_label(void *label, NativeStatement *stmt)
{
    *(NativeStatement **)((UInt8 *)label + 4) = stmt;
}
static inline NativeNode *native_flag_expr(void)
{
    if (!(arguments && arguments->next && arguments->next->object->type->kind == 1))
        CError_Internal("CABI.c", 1580);
    return checkreference(create_objectrefnode(arguments->next->object));
}

void CABI_TransDestructor(NativeObject *func, NativeObject *func2,
    NativeStatement *firststmt, NativeClass *tclass, UInt8 unused)
{
    UInt8 empty, sized;
    NativeStatement *stmt, *current;
    void *endLabel, *deleteLabel, *vBaseLabel;
    NativeNode *expr;
    NativeVTableInit info;
    NativeObject *deleteFunc;
    empty = CABI_IsSimpleCtorDtor(firststmt, 0);
    endLabel = newlabel();
    for (stmt = firststmt; stmt; stmt = stmt->next) {
        if (stmt->kind == 8) {
            if (stmt->expr) CError_Internal("CABI.c", 3937);
            stmt->kind = 3;
            native_set_target(stmt, endLabel);
        }
        current = stmt->next;
        if (current && current->kind == 8 && !current->next) {
            if (current->expr) CError_Internal("CABI.c", 3942);
            stmt->next = 0;
            break;
        }
    }
    deleteLabel = newlabel();
    current = CFunc_InsertStatement(7, firststmt);
    current->expr = CABI_MakeThisExpr(0, 0);
    native_set_target(current, deleteLabel);
    if (!empty && tclass->vTable && !(tclass->flags & 0x4000) && ((NativeVTable *)tclass->vTable)->object) {
        memclrw(&info, sizeof(NativeVTableInit));
        info.baseReference = &info.path;
        info.root = tclass;
        info.tclass = tclass;
        info.baseClass = tclass;
        info.direct = 0;
        trans_vtboffsets = 0;
        current = CABI_InitVTablePtrs(current, &info, 0, 1);
    }
    if (tclass->flags & 0x8000) current = CABI_InitVBaseCtorOffsets(current, tclass);
    for (stmt = firststmt; stmt->next; stmt = stmt->next) ;
    current = CFunc_InsertStatement(2, stmt);
    native_set_target(current, endLabel);
    *(void **)((UInt8 *)current + 18) = 0;
    native_bind_label(endLabel, current);
    if (!(tclass->flags & 1)) current = CABI_DestroyMembers(current, tclass->members, tclass);
    if (tclass->bases) current = CABI_DestroyBases((NativeObject *)tclass, current, tclass->bases, 1);
    if (tclass->flags & 0x20) {
        vBaseLabel = newlabel();
        current = CFunc_InsertStatement(7, current);
        current->expr = native_flag_expr();
        native_set_target(current, vBaseLabel);
        current = CABI_DestroyVBases((NativeObject *)tclass, current, tclass->vBases);
        current = CFunc_InsertStatement(2, current);
        native_set_target(current, vBaseLabel);
        native_bind_label(vBaseLabel, current);
    }
    current = CFunc_InsertStatement(6, current);
    current->expr = fn_0051f620(native_flag_expr(), intconstnode(&stsignedshort, 0));
    native_set_target(current, deleteLabel);
    if (fn_0070f1e7) {
        current = CFunc_InsertStatement(4, current);
        current->expr = funccallexpr(rt_unreg_class, CABI_MakeThisExpr(0, 0), 0, 0, 0);
    }
    deleteFunc = fn_004550c0(tclass, 0, 0, 0, &sized);
    current = CFunc_InsertStatement(4, current);
    expr = CABI_MakeThisExpr(0, 0);
    if (sized) current->expr = funccallexpr(deleteFunc, expr, intconstnode(&stunsignedlong, tclass->type.size), 0, 0);
    else current->expr = funccallexpr(deleteFunc, expr, 0, 0, 0);
    current = CFunc_InsertStatement(2, current);
    native_set_target(current, deleteLabel);
    native_bind_label(deleteLabel, current);
    current = CFunc_InsertStatement(8, current);
    current->expr = CABI_MakeThisExpr(0, 0);
}

extern UInt8 CExpr_HasFuncCall(NativeNode *);
UInt8 CABI_IsSimpleCtorDtor(NativeStatement *stmt, UInt8 flag)
{
    if (flag) return 0;
    for (; stmt; stmt = stmt->next) {
        switch (stmt->kind) {
            case 1: case 2: case 3: case 10: case 11: break;
            case 4: case 5: case 6: case 7: case 15:
                if (CExpr_HasFuncCall(stmt->expr)) return 0;
                break;
            case 8:
                if (stmt->expr && CExpr_HasFuncCall(stmt->expr)) return 0;
                break;
            case 12: case 13: case 14: case 16: return 0;
            default: CError_Internal("CABI.c", 2559); break;
        }
    }
    return 1;
}

#pragma pack(push, 2)
typedef struct NativePlacedClass {
    struct NativePlacedClass *next;
    NativeClass *tclass;
    SInt32 offset;
} NativePlacedClass;
#pragma pack(pop)

UInt8 CABI_ClassAllocConflict(NativeClass *type, SInt32 offset, NativeClass *container,
    SInt32 containerOffset)
{
    NativeBase *base;
    NativeMember *member;
    if (type == container && offset == containerOffset) return 1;
    for (base = container->bases; base; base = base->next)
        if (!base->isVirtual && CABI_ClassAllocConflict(type, offset, base->base, containerOffset + base->offset)) return 1;
    for (member = container->members; member; member = member->next)
        if (member->type->kind == 6 && CABI_ClassAllocConflict(type, offset, (NativeClass *)member->type,
            containerOffset + member->offset)) return 1;
    return 0;
}

UInt8 CABI_BaseClassAllocConflict(NativeClass *type, SInt32 offset, NativePlacedClass *placed)
{
    NativePlacedClass *entry;
    NativeBase *base;
    NativeMember *member;
    for (entry = placed; entry; entry = entry->next)
        if (CABI_ClassAllocConflict(type, offset, entry->tclass, entry->offset)) return 1;
    for (base = type->bases; base; base = base->next)
        if (!base->isVirtual && CABI_BaseClassAllocConflict(base->base, offset, placed)) return 1;
    for (member = type->members; member; member = member->next)
        if (member->type->kind == 6 && CABI_BaseClassAllocConflict((NativeClass *)member->type, offset, placed)) return 1;
    return 0;
}

NativeLayoutBases *CABI_GetBaseAllocationOrderList(NativeClass *tclass, UInt8 unused)
{
    NativeLayoutBases *list = 0, *entry, *last;
    NativeBase *base;
    NativeVBase *vbase;
    UInt8 first = 1;
    int useZero;
    for (base = tclass->bases; base; base = base->next) {
        if (!base->isVirtual) {
            useZero = first != 0;
            if (useZero) useZero = base->base->vTable != 0;
            entry = lalloc(sizeof(NativeLayoutBases));
            entry->next = 0;
            entry->nonvirtual = base;
            entry->virtualBase = 0;
            entry->useZero = useZero;
            entry->occupied = 0;
            if (list) {
                for (last = list; last->next; last = last->next) ;
                last->next = entry;
            } else list = entry;
            first = 0;
        }
    }
    for (vbase = tclass->vBases; vbase; vbase = vbase->next) {
        entry = lalloc(sizeof(NativeLayoutBases));
        entry->next = 0;
        entry->nonvirtual = 0;
        entry->virtualBase = (NativeBase *)vbase;
        entry->useZero = 0;
        entry->occupied = 0;
        if (list) {
            for (last = list; last->next; last = last->next) ;
            last->next = entry;
        } else list = entry;
    }
    return list;
}

extern void *constructor_name;
extern void CError_OverloadedFunctionError(NativeObject *, NativeObjectList *);
extern void CError_Error(int, ...);
extern void *GetHashNameNodeExport(const char *);
extern void CDecl_SetFuncFlags(NativeTypeFunc *, int);
extern void CDecl_AddArgument(NativeTypeFunc *, NativeType *);
extern void CDecl_AddThisPointerArgument(NativeTypeFunc *, NativeClass *);
extern NativeObject *CParser_NewCompilerDefFunctionObject(void);
extern void CScope_AddObject(void *, void *, NativeObject *);
extern void CMid_RegisterDummyCtorFunction(NativeObject *, NativeObject *);
extern NativeNode *CExpr_CallFunction(NativeClass *, NativeNode *, NativeObject *, int, NativeNodeList *, int);
extern NativeType *CDecl_NewPointerType(NativeClass *);

NativeObject *CABI_DummyDefaultConstructor(NativeClass *tclass)
{
    NativeObjectList *entry, ambiguity;
    NativeObject *candidate = 0, *object;
    NativeFuncArg *arg;
    NativeTypeFunc *type;
    void *name;
    for (entry = CScope_FindName(tclass->nameSpace, constructor_name); entry; entry = entry->next) {
        object = entry->object;
        if (*(UInt8 *)object != 5 || object->type->kind != 7 ||
            (((NativeTypeFunc *)object->type)->flags & 0x100000)) continue;
        arg = CABI_GetFirstRealArgument((NativeTypeFunc *)object->type);
        if (!arg) CError_Internal("CABI.c", 2295);
        if (!arg || arg->defaultExpr || arg->ellipsis) {
            if (!candidate) candidate = object;
            else {
                ambiguity.next = 0;
                ambiguity.object = object;
                CError_OverloadedFunctionError(candidate, &ambiguity);
                break;
            }
        }
    }
    if (!candidate) {
        CError_Error(0x27db);
        return 0;
    }
    name = GetHashNameNodeExport("__defctor");
    entry = CScope_FindName(tclass->nameSpace, name);
    if (entry) {
        object = entry->object;
        if (!(*(UInt8 *)object == 5 && object->type->kind == 7)) CError_Internal("CABI.c", 2322);
        return object;
    }
    type = galloc(sizeof(NativeTypeFunc));
    memclrw(type, sizeof(NativeTypeFunc));
    type->type.kind = 7;
    type->returnType = &void_ptr;
    type->flags = 0x10;
    type->tclass = tclass;
    CDecl_SetFuncFlags(type, 0);
    if (tclass->flags & 0x20) CDecl_AddArgument(type, &stsignedshort);
    CDecl_AddThisPointerArgument(type, tclass);
    object = CParser_NewCompilerDefFunctionObject();
    object->type = (NativeType *)type;
    object->flags = 0x80010;
    *(void **)((UInt8 *)object + 8) = tclass->nameSpace;
    object->name = name;
    CScope_AddObject(tclass->nameSpace, name, object);
    CMid_RegisterDummyCtorFunction(object, candidate);
    return object;
}

NativeNode *CABI_DefaultConstructorCall(NativeClass *tclass, NativeObject *caller, NativeNode *expr,
    UInt8 baseFlag, UInt8 checkAccess, UInt8 unused, UInt8 *notFound)
{
    NativeObjectList *entry, ambiguity;
    NativeObject *candidate = 0, *object;
    NativeFuncArg *arg;
    NativeNodeList *args = 0;
    NativeNode *flag, *call;
    *notFound = 0;
    entry = CScope_FindName(tclass->nameSpace, constructor_name);
    if (!entry) return 0;
    for (; entry; entry = entry->next) {
        object = entry->object;
        if (*(UInt8 *)object != 5 || object->type->kind != 7 ||
            (((NativeTypeFunc *)object->type)->flags & 0x100000)) continue;
        arg = CABI_GetFirstRealArgument((NativeTypeFunc *)object->type);
        if (arg && !arg->defaultExpr && !arg->ellipsis) continue;
        if (!candidate) candidate = object;
        else {
            ambiguity.next = 0;
            ambiguity.object = object;
            CError_OverloadedFunctionError(candidate, &ambiguity);
            break;
        }
    }
    if (!candidate) {
        *notFound = 1;
        return 0;
    }
    if (checkAccess) CClass_NewAccessCheck(0, caller ? caller : (NativeObject *)tclass, tclass,
        *((UInt8 *)candidate + 1), candidate, 0);
    if (tclass->flags & 0x20) {
        flag = intconstnode(&stsignedshort, baseFlag ? 1 : 0);
        if (flag) {
            args = lalloc(sizeof(NativeNodeList));
            args->next = 0;
            args->node = flag;
        }
    }
    if (expr->type->kind != 12) CError_Internal("CABI.c", 2523);
    expr = makemonadicnode(expr, 4);
    expr->type = (NativeType *)tclass;
    call = CExpr_CallFunction(tclass, expr, candidate, 0, args, 0);
    if (call->kind == 0x39 || call->kind == 0x3a) call->type = CDecl_NewPointerType(tclass);
    return call;
}

UInt8 cabi_loop_construct;
NativeClass *cabi_loop_class;
extern NativeObject *CClass_AssignmentOperator(NativeClass *);
extern NativeNode *argumentpromotion(NativeNode *, NativeType *, UInt32, int);
extern NativeNode *CExpr_CopyClassObject(NativeClass *, NativeNode *, NativeNode *);
extern UInt8 CClass_HasCopyConstructor(NativeClass *, int);
extern void *CClass_DirectBasePointerCast(void *, NativeClass *, NativeClass *);
extern NativeNode *CExpr_ConstructObject(NativeClass *, NativeObject *, NativeNode *, NativeNodeList *,
    void *, void *, void *, UInt8, UInt8);

NativeNode *CABI_ClassInitLoopCallBack(NativeNode *dest, NativeNode *source)
{
    NativeObject *ctor;
    NativeFuncArg *arg;
    if (cabi_loop_class->type.kind != 6) CError_Internal("CABI.c", 3245);
    source = makemonadicnode(source, 4);
    source->type = (NativeType *)cabi_loop_class;
    if (cabi_loop_construct) return CExpr_CopyClassObject(cabi_loop_class, dest, source);
    ctor = CClass_AssignmentOperator(cabi_loop_class);
    if (ctor) {
        if (ctor->type->kind != 7 || !((NativeTypeFunc *)ctor->type)->args ||
            !(arg = ((NativeTypeFunc *)ctor->type)->args->next)) CError_Internal("CABI.c", 3135);
        CClass_NewAccessCheck(0, (NativeObject *)cabi_loop_class, cabi_loop_class,
            *((UInt8 *)ctor + 1), ctor, 0);
        return funccallexpr(ctor, dest, argumentpromotion(source, arg->type, arg->qualifiers, 1), 0, 0);
    }
    dest = makemonadicnode(dest, 4);
    dest->type = (NativeType *)cabi_loop_class;
    return makediadicnode(dest, source, 30);
}

NativeNode *CABI_CopyAssignBase(NativeClass *root, NativeClass *tclass, SInt32 offset,
    UInt8 construct, NativeObject *caller, UInt8 mode)
{
    NativeObjectList *entry;
    NativeNode *source, *dest, *call;
    NativeObject *ctor;
    NativeFuncArg *arg;
    NativeNodeList *args;
    void *nameSpace;
    if (tclass->flags & 0x1000) {
        if (construct && !CClass_HasCopyConstructor(tclass, 0)) return 0;
        if (!construct && !CClass_AssignmentOperator(tclass)) return 0;
    }
    entry = arguments;
    if (!entry) CError_Internal("CABI.c", 1610);
    entry = entry->next;
    if (!entry) CError_Internal("CABI.c", 1611);
    if (construct && (root->flags & 0x20)) {
        entry = entry->next;
        if (!entry) CError_Internal("CABI.c", 1615);
    }
    if (entry->object->type->kind != 12) CError_Internal("CABI.c", 1617);
    source = checkreference(create_objectrefnode(entry->object));
    source->type = (NativeType *)tclass;
    source->function = CClass_DirectBasePointerCast(source->function, root, tclass);
    if (construct) {
        args = lalloc(sizeof(NativeNodeList));
        args->next = 0;
        args->node = source;
        dest = CABI_MakeThisExpr(0, offset);
        call = CExpr_ConstructObject(tclass, caller, dest, args, 0, 0, 0, 1, mode);
        if (call->kind == 0x39 && call->function->kind == 0x3b) {
            ctor = (NativeObject *)call->function->function;
            nameSpace = *(void **)((UInt8 *)ctor + 8);
            if (nameSpace && *(NativeClass **)((UInt8 *)nameSpace + 12) == tclass)
                CClass_NewAccessCheck((int)root, (NativeObject *)root, tclass, *((UInt8 *)ctor + 1), ctor, 0);
        }
        return call;
    }
    dest = CABI_MakeThisExpr(0, 0);
    dest = CClass_DirectBasePointerCast(dest, root, tclass);
    ctor = CClass_AssignmentOperator(tclass);
    if (ctor) {
        if (ctor->type->kind != 7 || !((NativeTypeFunc *)ctor->type)->args ||
            !(arg = ((NativeTypeFunc *)ctor->type)->args->next)) CError_Internal("CABI.c", 3135);
        CClass_NewAccessCheck(0, (NativeObject *)root, tclass, *((UInt8 *)ctor + 1), ctor, 0);
        return funccallexpr(ctor, dest, argumentpromotion(source, arg->type, arg->qualifiers, 1), 0, 0);
    }
    dest = makemonadicnode(dest, 4);
    dest->type = (NativeType *)tclass;
    return makediadicnode(dest, source, 30);
}

extern void CMach_StructLayoutInitOffset(SInt32, SInt32, UInt8);
extern SInt32 fn_004e2540(NativeType *, UInt32), fn_004e2b40(NativeType *, UInt32);
extern SInt32 fn_004e2be0(void);
extern void *unnamed_name;
extern void *CParser_AppendUniqueName(const char *);
extern UInt8 fn_0070f1c9;

void CABI_AllocateMembers(NativeClassLayout *layout, NativeClass *tclass, void *unused)
{
    SInt32 initialSize, maximumSize, size, unionOffset, offset;
    NativeClass *unionType = 0;
    NativeMember *member, *node, **link;
    UInt8 removeUnnamed = 0;
    initialSize = maximumSize = tclass->type.size;
    CMach_StructLayoutInitOffset(initialSize, tclass->align, (tclass->flags & 0x400000) != 0);
    for (member = tclass->members; member; member = member->next) {
        if (!member->subtype) {
            if (member->offset >= 0) {
                if (tclass->unknown_2e == 1)
                    CMach_StructLayoutInitOffset(initialSize, tclass->align, (tclass->flags & 0x400000) != 0);
                if (member->type->kind == 8) member->offset = fn_004e2540(member->type, member->qualifiers);
                else member->offset = fn_004e2b40(member->type, member->qualifiers);
                if (tclass->unknown_2e == 1 && (size = fn_004e2be0()) > maximumSize) maximumSize = size;
                unionType = 0;
            } else {
                if (!unionType) CError_Internal("CABI.c", 5248);
                if (!member->name) offset = 0;
                else {
                    for (node = unionType->members;; node = node->next) {
                        if (node->name == member->name) {
                            offset = node->offset;
                            break;
                        }
                        if (!node->next) CError_Internal("CABI.c", 5141);
                    }
                }
                member->offset = unionOffset + offset;
                member->subtype = 1;
            }
            if (member->name == unnamed_name || !member->name) removeUnnamed = 1;
        } else {
            if (member->type->kind != 6) CError_Internal("CABI.c", 5256);
            if (tclass->unknown_2e == 1)
                CMach_StructLayoutInitOffset(initialSize, tclass->align, (tclass->flags & 0x400000) != 0);
            unionOffset = fn_004e2b40(member->type, member->qualifiers);
            member->offset = unionOffset;
            unionType = (NativeClass *)member->type;
            if (tclass->unknown_2e == 1 && (size = fn_004e2be0()) > maximumSize) maximumSize = size;
            removeUnnamed = 1;
        }
        if (layout->zeroVPtr == member) ((NativeVTable *)tclass->vTable)->zeroVPtrOffset = member->offset;
    }
    if (removeUnnamed) {
        link = (NativeMember **)&tclass->members;
        while ((node = *link)) {
            if (node->name == unnamed_name || (!node->name && !node->subtype)) *link = node->next;
            else {
                if (!node->name) {
                    node->name = CParser_AppendUniqueName("__anon");
                    node->subtype = 0;
                }
                link = &node->next;
            }
        }
    }
    if (tclass->unknown_2e == 1) tclass->type.size = maximumSize;
    else tclass->type.size = fn_004e2be0();
    if (fn_0070f1c9)
        for (member = tclass->members; member; member = member->next)
            if (member->type->kind == 8) CABI_ReverseBitField((NativeBitField *)member->type);
}

extern UInt8 fn_0070f22c;
extern NativeStatement *native_current_statement;
extern UInt8 CClass_IsTrivialCopyAssignClass(NativeClass *);
extern NativeStatement *CABI_CopyAssignMembers(NativeStatement *, NativeClass *, UInt8, NativeObject *);

void CABI_MakeDefaultAssignmentOperator(NativeClass *tclass, NativeObject *func)
{
    UInt8 savedebug;
    UInt8 savedscope[16];
    NativeStatement firststmt, *stmt;
    void *savedstate;
    NativeBase *base;
    NativeVBase *vbase;
    NativeObjectList *sourceArg;
    NativeNode *source, *dest, *expr;
    if (anyerrors || *((UInt8 *)func + 1) == 3) return;
    native_apply_class_flags(func, tclass->eflags);
    savedstate = CTemplTool_PushInstance(0, func);
    CScope_SetFunctionScope(func, savedscope);
    CFunc_FuncGenSetup(0, &firststmt, func, 0);
    savedebug = filesyminfo;
    filesyminfo = 0;
    CFunc_SetupNewFuncArgs(0, func, ((NativeTypeFunc *)func->type)->args);
    stmt = native_current_statement;
    if (tclass->unknown_2e == 1 || (fn_0070f22c && CClass_IsTrivialCopyAssignClass(tclass))) {
        dest = makemonadicnode(CABI_MakeThisExpr(tclass, 0), 4);
        dest->type = (NativeType *)tclass;
        sourceArg = arguments;
        if (!sourceArg) CError_Internal("CABI.c", 1610);
        sourceArg = sourceArg->next;
        if (!sourceArg) CError_Internal("CABI.c", 1611);
        if (sourceArg->object->type->kind != 12) CError_Internal("CABI.c", 1617);
        source = checkreference(create_objectrefnode(sourceArg->object));
        source->type = (NativeType *)tclass;
        if (dest->type->size) {
            stmt = CFunc_InsertStatement(4, stmt);
            stmt->expr = makediadicnode(dest, source, 30);
        }
    } else {
        for (vbase = tclass->vBases; vbase; vbase = vbase->next) {
            expr = CABI_CopyAssignBase(tclass, vbase->base, vbase->offset, 0, 0, 1);
            if (expr) {
                stmt = CFunc_InsertStatement(4, stmt);
                stmt->expr = expr;
            }
        }
        for (base = tclass->bases; base; base = base->next) {
            if (!base->isVirtual) {
                expr = CABI_CopyAssignBase(tclass, base->base, base->offset, 0, 0, 0);
                if (expr) {
                    stmt = CFunc_InsertStatement(4, stmt);
                    stmt->expr = expr;
                }
            }
        }
        stmt = CABI_CopyAssignMembers(stmt, tclass, 0, 0);
    }
    stmt = CFunc_InsertStatement(8, stmt);
    stmt->expr = CABI_MakeThisExpr(0, 0);
    CFunc_CodeCleanup(&firststmt);
    CFunc_Gen(&firststmt, func);
    CScope_RestoreScope(savedscope);
    CTemplTool_PopInstance(savedstate);
    filesyminfo = savedebug;
}

extern SInt16 fn_004e3190(NativeClass *);
extern void CClass_ComputeClassPopertyBits(NativeClass *);
extern UInt8 CClass_IsPODClass(NativeClass *), fn_0070f1ef;

static inline SInt32 native_place_class(NativeClass *tclass, SInt32 *offset,
    SInt32 size, NativePlacedClass **placed)
{
    NativePlacedClass *entry;
    SInt32 end = size;
    if (tclass->flags & 0x1000) {
        while (CABI_BaseClassAllocConflict(tclass, end, *placed)) ++end;
        *offset = end;
    } else {
        *offset = size + CMach_MemberAlignValue((NativeType *)tclass, size);
        end = *offset + tclass->baseSize;
    }
    entry = lalloc(sizeof(NativePlacedClass));
    entry->next = *placed;
    entry->tclass = tclass;
    entry->offset = *offset;
    *placed = entry;
    return end;
}

void CABI_LayoutClass(NativeClassLayout *layout, NativeClass *tclass)
{
    UInt8 savedalign;
    NativePlacedClass *placed = 0;
    NativeLayoutBases *list, *entry;
    NativeBase *base;
    NativeVBase *vbase;
    SInt32 size;
    tclass->type.size = 0;
    savedalign = structure_alignment;
    list = CABI_GetBaseAllocationOrderList(tclass, layout->needsVTable);
    entry = list;
    if (entry && entry->useZero) {
        if (tclass->type.size) CError_Internal("CABI.c", 5492);
        entry->occupied = 1;
        if (entry->nonvirtual)
            tclass->type.size = native_place_class(entry->nonvirtual->base,
                &entry->nonvirtual->offset, 0, &placed);
        else {
            if (!entry->virtualBase) CError_Internal("CABI.c", 5501);
            tclass->type.size = native_place_class(entry->virtualBase->base,
                &entry->virtualBase->offset, 0, &placed);
        }
        entry = entry->next;
    }
    for (; entry && entry->nonvirtual; entry = entry->next) {
        tclass->type.size = native_place_class(entry->nonvirtual->base,
            &entry->nonvirtual->offset, tclass->type.size, &placed);
        entry->occupied = 1;
    }
    if (tclass->flags & 0x20) {
        size = tclass->type.size;
        for (base = tclass->bases; base; base = base->next) {
            if (base->isVirtual) {
                base->offset = size + CMach_MemberAlignValue(&void_ptr, size);
                size = base->offset + void_ptr.size;
            }
        }
        tclass->type.size = size;
    }
    if (layout->needsVTable) CABI_AllocateZeroVTablePointer(list, layout, tclass);
    CABI_AllocateMembers(layout, tclass, &placed);
    tclass->baseSize = tclass->type.size;
    if (tclass->flags & 0x20) {
        size = tclass->type.size;
        for (entry = list; entry; entry = entry->next) {
            if (entry->virtualBase && !entry->useZero) {
                vbase = (NativeVBase *)entry->virtualBase;
                vbase->offset = size + CMach_MemberAlignValue((NativeType *)vbase->base, size);
                size = vbase->offset + vbase->base->baseSize;
                if (*((UInt8 *)vbase + 16)) size += CMach_MemberAlignValue(&stunsignedlong, size) + 4;
                entry->occupied = 1;
            }
        }
        tclass->type.size = size;
    }
    if (layout->needsVTable) CABI_AllocateVTable(list, layout, tclass);
    for (entry = list; entry; entry = entry->next)
        if (!entry->occupied) CError_Internal("CABI.c", 5585);
    tclass->align = fn_004e3190(tclass);
    if (!tclass->type.size) {
        tclass->type.size = 1;
        tclass->flags |= 0x1000;
    } else tclass->type.size += CABI_StructSizeAlignValue((NativeType *)tclass, 0, tclass->type.size);
    tclass->flags |= 2;
    CClass_ComputeClassPopertyBits(tclass);
    if (CClass_IsPODClass(tclass) && !fn_0070f1ef) tclass->baseSize = tclass->type.size;
    structure_alignment = savedalign;
}

extern UInt8 CParser_IsConst(NativeType *, UInt32);
extern SInt16 canadd(void *, SInt32);
extern void optimizecomm(void *);
extern void fn_0049fd80(NativeStatement *, NativeObject *, SInt32, NativeObject *, void *, UInt8);
extern void fn_0049fd20(NativeStatement *, NativeObject *, SInt32, NativeObject *, SInt32, SInt32);
extern NativeStatement *CFunc_GenerateLoop(NativeStatement *, NativeType *, NativeNode *, NativeNode *, NativeNode *,
    NativeNode *, NativeNode *(*)(NativeNode *, NativeNode *));

static inline NativeNode *native_source_arg(NativeClass *tclass, UInt8 construct)
{
    NativeObjectList *entry = arguments;
    if (!entry) CError_Internal("CABI.c", 1610);
    entry = entry->next;
    if (!entry) CError_Internal("CABI.c", 1611);
    if (construct && (tclass->flags & 0x20)) {
        entry = entry->next;
        if (!entry) CError_Internal("CABI.c", 1615);
    }
    if (entry->object->type->kind != 12) CError_Internal("CABI.c", 1617);
    return checkreference(create_objectrefnode(entry->object));
}

static inline NativeNode *native_source_at(NativeClass *tclass, UInt8 construct,
    NativeType *type, SInt32 offset)
{
    NativeNode *source = native_source_arg(tclass, construct);
    source->type = type;
    if (!canadd(source->function, offset)) {
        source->function = makediadicnode(source->function, intconstnode(&stunsignedlong, offset), 15);
        optimizecomm(source->function);
    }
    return source;
}

static inline NativeNode *native_assign_class(NativeClass *tclass, NativeNode *dest, NativeNode *source)
{
    NativeObject *func = CClass_AssignmentOperator(tclass);
    NativeFuncArg *arg;
    if (func) {
        if (func->type->kind != 7 || !((NativeTypeFunc *)func->type)->args ||
            !(arg = ((NativeTypeFunc *)func->type)->args->next)) CError_Internal("CABI.c", 3135);
        CClass_NewAccessCheck(0, (NativeObject *)tclass, tclass, *((UInt8 *)func + 1), func, 0);
        return funccallexpr(func, dest, argumentpromotion(source, arg->type, arg->qualifiers, 1), 0, 0);
    }
    dest = makemonadicnode(dest, 4);
    dest->type = (NativeType *)tclass;
    return makediadicnode(dest, source, 30);
}

NativeStatement *CABI_CopyAssignMembers(NativeStatement *stmt, NativeClass *tclass,
    UInt8 construct, NativeObject *unused)
{
    NativeMember *member;
    NativeCopyRegion *regions = 0, *region;
    NativeType *type;
    NativeNode *source, *dest, *end, *sourcePtr;
    NativeObject *dtor;
    SInt32 count, index, offset;
    UInt8 checkConst = !construct, raw;
    for (member = tclass->members; member; member = member->next) {
        if (member->name == vptr_name) continue;
        type = member->type;
        if (checkConst && (CParser_IsConst(type, member->qualifiers) ||
            (type->kind == 12 && (*(UInt32 *)((UInt8 *)type + 10) & 0x20)))) {
            CError_Error(0x2893, tclass, 0);
            checkConst = 0;
        }
        raw = 1;
        if (type->kind == 13) {
            if (!type->size) continue;
            do type = *(NativeType **)((UInt8 *)type + 6); while (type->kind == 13);
        }
        if (type->kind == 6) {
            if (construct) raw = !CClass_HasCopyConstructor((NativeClass *)type, 0);
            else raw = CClass_IsTrivialCopyAssignClass((NativeClass *)type) != 0;
        }
        regions = CABI_AppendCopyRegion(regions, member->type, member->offset, raw);
    }
    for (region = regions; region; region = region->next) {
        if (region->start >= region->end) continue;
        type = region->type;
        source = native_source_at(tclass, construct, type, region->start);
        if (!region->flag) {
            if (type->kind == 13) {
                do type = *(NativeType **)((UInt8 *)type + 6); while (type->kind == 13);
                if (type->kind != 6) CError_Internal("CABI.c", 3413);
                if (!type->size) continue;
                count = region->type->size / type->size;
                if (count > 4) {
                    dest = CABI_MakeThisExpr(tclass, region->start);
                    end = CABI_MakeThisExpr(tclass, region->start + region->type->size);
                    sourcePtr = native_source_arg(tclass, construct)->function;
                    if (!canadd(sourcePtr, region->start)) {
                        sourcePtr = makediadicnode(sourcePtr, intconstnode(&stunsignedlong, region->start), 15);
                        optimizecomm(sourcePtr);
                    }
                    cabi_loop_class = (NativeClass *)type;
                    cabi_loop_construct = construct;
                    stmt = CFunc_GenerateLoop(stmt, CDecl_NewPointerType((NativeClass *)type), dest, end,
                        intconstnode(&stunsignedlong, type->size), sourcePtr, CABI_ClassInitLoopCallBack);
                } else {
                    for (index = 0, offset = region->start; index < count; ++index, offset += type->size) {
                        source = native_source_at(tclass, construct, type, offset);
                        stmt = CFunc_InsertStatement(4, stmt);
                        dest = CABI_MakeThisExpr(tclass, offset);
                        if (construct) stmt->expr = CExpr_CopyClassObject((NativeClass *)type, dest, source);
                        else stmt->expr = native_assign_class((NativeClass *)type, dest, source);
                    }
                }
                if (construct && (dtor = CClass_Destructor((NativeClass *)type)))
                    fn_0049fd20(stmt, native_this_arg(), region->start, dtor, count, type->size);
                continue;
            }
            if (type->kind != 6) CError_Internal("CABI.c", 3473);
            stmt = CFunc_InsertStatement(4, stmt);
            dest = CABI_MakeThisExpr(tclass, region->start);
            if (construct) {
                stmt->expr = CExpr_CopyClassObject((NativeClass *)type, dest, source);
                if (dtor = CClass_Destructor((NativeClass *)type))
                    fn_0049fd80(stmt, native_this_arg(), region->start, dtor, 0, 1);
            } else stmt->expr = native_assign_class((NativeClass *)type, dest, source);
        } else {
            if (type->kind == 13) {
                type = CDecl_NewOpaqueType(type->size, CMach_GetTypeAlign(type, 0));
                source->type = type;
            }
            dest = makemonadicnode(CABI_MakeThisExpr(tclass, region->start), 4);
            dest->type = type;
            stmt = CFunc_InsertStatement(4, stmt);
            stmt->expr = makediadicnode(dest, source, 30);
        }
    }
    return stmt;
}

#pragma pack(push, 2)
typedef struct NativeCtorInit {
    struct NativeCtorInit *next;
    NativeNode *expr;
    void *key;
    UInt8 kind, valid;
} NativeCtorInit;
#pragma pack(pop)
extern NativeNode *fn_0051ed90(NativeNode *, NativeNode *);
extern NativeObject *CClass_Constructor(NativeClass *), *CClass_DefaultConstructor(NativeClass *);
extern NativeStatement *CInit_ConstructClassArray(NativeStatement *, NativeClass *, NativeObject *,
    NativeObject *, NativeNode *, NativeNode *);
extern NativeNode *nullnode(void);

void CABI_TransConstructor(NativeObject *func, NativeStatement *firststmt, NativeClass *tclass,
    UInt8 copy, UInt8 hasTry)
{
    NativeStatement *stmt, *scan;
    NativeCtorInit *initializers, *initializer;
    NativeNode *expr, *call;
    NativeObject *function, *dtor;
    NativeBase *base;
    NativeVBase *vbase;
    NativeMember *member;
    NativeType *type;
    NativeVTableInit info;
    void *label;
    UInt8 notFound;
    SInt32 count;
    initializers = 0;
    for (scan = firststmt; scan; scan = scan->next) {
        if (scan->kind == 4 && scan->expr->kind == 0x4f) {
            scan->kind = 1;
            initializers = (NativeCtorInit *)scan->expr->function;
            break;
        }
    }
    stmt = firststmt;
    if (function = CABI_ConstructorCallsNew(tclass)) {
        label = newlabel();
        stmt = CFunc_InsertStatement(6, stmt);
        stmt->expr = CABI_MakeThisExpr(0, 0);
        native_set_target(stmt, label);
        expr = funccallexpr(function, intconstnode(&stunsignedlong, tclass->type.size), 0, 0, 0);
        expr = makediadicnode(CABI_MakeThisExpr(0, 0), expr, 30);
        stmt = CFunc_InsertStatement(6, stmt);
        stmt->expr = expr;
        native_set_target(stmt, label);
        stmt = CFunc_InsertStatement(8, stmt);
        stmt->expr = 0;
        stmt = CFunc_InsertStatement(2, stmt);
        native_set_target(stmt, label);
        native_bind_label(label, stmt);
    }
    if (hasTry) {
        for (stmt = firststmt;; stmt = stmt->next) {
            if (!stmt) CError_Internal("CABI.c", 2714);
            if (stmt->kind == 12) break;
        }
    }
    if (tclass->flags & 0x20) {
        label = newlabel();
        stmt = CFunc_InsertStatement(6, stmt);
        stmt->expr = fn_0051ed90(native_flag_expr(), intconstnode(&stsignedshort, 0));
        native_set_target(stmt, label);
        stmt = CABI_InitVBasePtrs(stmt, tclass);
        for (vbase = tclass->vBases; vbase; vbase = vbase->next) {
            if (copy) call = CABI_CopyAssignBase(tclass, vbase->base, vbase->offset, 1, 0, 1);
            else {
                for (initializer = initializers; initializer; initializer = initializer->next)
                    if (initializer->key == vbase->base) break;
                if (initializer) {
                    if (!initializer->valid) CError_Internal("CABI.c", 2761);
                    call = initializer->expr;
                } else {
                    call = CABI_DefaultConstructorCall(vbase->base, func, CABI_MakeThisExpr(0, vbase->offset), 0, 1, 1, &notFound);
                    if (!call && notFound) CError_Error(0x27e5, tclass, 0, vbase->base, 0);
                }
            }
            if (call) {
                stmt = CFunc_InsertStatement(4, stmt);
                stmt->expr = call;
            }
            if (dtor = CClass_Destructor(vbase->base)) {
                NativeObject *flagArg;
                if (!(arguments && arguments->next && arguments->next->object->type->kind == 1))
                    CError_Internal("CABI.c", 1580);
                flagArg = arguments->next->object;
                fn_0049fd80(stmt, native_this_arg(), vbase->offset, dtor, flagArg, 0);
            }
        }
        stmt = CFunc_InsertStatement(2, stmt);
        native_set_target(stmt, label);
        native_bind_label(label, stmt);
    }
    for (base = tclass->bases; base; base = base->next) {
        if (!base->isVirtual) {
            if (copy) call = CABI_CopyAssignBase(tclass, base->base, base->offset, 1, 0, 0);
            else {
                for (initializer = initializers; initializer; initializer = initializer->next)
                    if (initializer->key == base->base) break;
                if (initializer) {
                    if (!initializer->valid) CError_Internal("CABI.c", 2800);
                    call = initializer->expr;
                } else {
                    call = CABI_DefaultConstructorCall(base->base, func, CABI_MakeThisExpr(0, base->offset), 0, 1, 0, &notFound);
                    if (!call && notFound) CError_Error(0x27e5, tclass, 0, base->base, 0);
                }
            }
            if (call) {
                stmt = CFunc_InsertStatement(4, stmt);
                stmt->expr = call;
            }
            if (dtor = CClass_Destructor(base->base))
                fn_0049fd80(stmt, native_this_arg(), base->offset, dtor, 0, 0);
        }
    }
    if (tclass->vTable && !(tclass->flags & 0x4000) && ((NativeVTable *)tclass->vTable)->object) {
        memclrw(&info, sizeof(NativeVTableInit));
        info.root = tclass;
        info.tclass = tclass;
        info.baseReference = &info.path;
        info.baseClass = tclass;
        info.direct = 0;
        trans_vtboffsets = 0;
        stmt = CABI_InitVTablePtrs(stmt, &info, 0, 1);
    }
    if (tclass->flags & 0x8000) stmt = CABI_InitVBaseCtorOffsets(stmt, tclass);
    if (copy) stmt = CABI_CopyAssignMembers(stmt, tclass, 1, 0);
    else {
        for (member = tclass->members; member; member = member->next) {
            for (initializer = initializers; initializer; initializer = initializer->next)
                if (initializer->key == member) break;
            if (initializer && initializer->expr) {
                if (!initializer->valid || !initializer->expr) CError_Internal("CABI.c", 2930);
                stmt = CFunc_InsertStatement(4, stmt);
                stmt->expr = initializer->expr;
                type = member->type;
                if (type->kind == 13) {
                    if (!type->size) continue;
                    do type = *(NativeType **)((UInt8 *)type + 6); while (type->kind == 13);
                    if (type->kind == 6 && (dtor = CClass_Destructor((NativeClass *)type))) {
                        if (!type->size) CError_Internal("CABI.c", 2944);
                        count = member->type->size / type->size;
                        fn_0049fd20(stmt, native_this_arg(), member->offset, dtor, count, type->size);
                    }
                } else if (type->kind == 6 && (dtor = CClass_Destructor((NativeClass *)type)))
                    fn_0049fd80(stmt, native_this_arg(), member->offset, dtor, 0, 1);
            } else {
                type = member->type;
                if (type->kind == 13) {
                    if (!type->size) continue;
                    do type = *(NativeType **)((UInt8 *)type + 6); while (type->kind == 13);
                    if (type->kind == 6 && CClass_Constructor((NativeClass *)type)) {
                        function = CClass_DefaultConstructor((NativeClass *)type);
                        if (!function) function = CABI_DummyDefaultConstructor((NativeClass *)type);
                        if (function) {
                            dtor = CClass_Destructor((NativeClass *)type);
                            expr = CABI_MakeThisExpr(tclass, member->offset);
                            count = member->type->size / type->size;
                            stmt = CInit_ConstructClassArray(stmt, (NativeClass *)type, function, dtor,
                                expr, intconstnode(&stunsignedlong, count));
                            if (dtor) fn_0049fd20(stmt, native_this_arg(), member->offset, dtor,
                                member->type->size / type->size, type->size);
                        } else CError_Error(0x27e6, tclass, 0, (UInt8 *)member->name + 10);
                    }
                } else if (type->kind == 6) {
                    call = CABI_DefaultConstructorCall((NativeClass *)type, 0, CABI_MakeThisExpr(tclass, member->offset), 1, 1, 0, &notFound);
                    if (call) {
                        stmt = CFunc_InsertStatement(4, stmt);
                        stmt->expr = call;
                    } else if (notFound) CError_Error(0x27e6, tclass, 0, (UInt8 *)member->name + 10);
                    if (dtor = CClass_Destructor((NativeClass *)type)) {
                        if (!call) {
                            stmt = CFunc_InsertStatement(4, stmt);
                            stmt->expr = nullnode();
                        }
                        fn_0049fd80(stmt, native_this_arg(), member->offset, dtor, 0, 1);
                    }
                }
            }
        }
    }
    for (scan = firststmt->next; scan; scan = scan->next) {
        if (scan->kind == 8) {
            if (scan->expr) CError_Internal("CABI.c", 2975);
            scan->expr = CABI_MakeThisExpr(0, 0);
        }
    }
}
