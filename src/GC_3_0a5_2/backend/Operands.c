/* GC 3.0a5.2 native operand ABI.  See build/Operands-review.json for coverage. */
typedef unsigned char UInt8;
typedef short SInt16;
typedef unsigned short UInt16;
typedef int SInt32;
typedef unsigned int UInt32;
typedef unsigned long long UInt64;
#pragma pack(push, 2)
typedef struct Type { UInt8 type, pad; SInt32 size; UInt8 integral; } Type;
typedef struct Operand {
    UInt8 kind, pad;
    SInt16 reg, regHi, secondary_reg;
    SInt32 displacement, immediate;
    void *object;
    UInt64 flags;
} Operand;
typedef struct TypeBitfield {
    UInt8 type, pad; SInt32 size; Type *bitfieldtype;
    UInt8 offset, bitlength;
} TypeBitfield;
typedef struct ENode {
    UInt8 type, pad[3]; Type *rtype; UInt32 flags;
} ENode;
typedef struct ENodeInfo {
    UInt8 pad[14], flags, kind;
    SInt16 reg, regHi;
} ENodeInfo;
#pragma pack(pop)
extern int gUsedVirtualRegistersGPR, gUsedVirtualRegistersFPR;
extern signed char optimization_level;
extern UInt8 nativeByteOrder, operandsDebug;
extern SInt16 low_word_offset, high_word_offset;
extern Type stsignedint, stdouble;
extern void *floating_unsigned_helper;
UInt32 data_006ad568[5]={0,0,0,2,0};
UInt32 one_point_zero[2]={0x3ff00000,0};
extern void CError_FATAL(const char *, int);
extern void CABI_ReverseBitField(TypeBitfield *);
extern UInt8 Type_IsUnsigned(Type *);
extern void *emitpcode(SInt16, ...);
extern void *makepcode(SInt16, ...);
extern void PCode_InsertAfter(void *, void *);
extern void PCode_InsertBefore(void *, void *);
extern void *GetEnodeInfo(ENode *);
extern UInt8 CParserIsVolatileExpr(ENode *), CParserIsConstExpr(ENode *);
extern void memclrw(void *, int);
extern void *CodeGen_AllocateTemporaryObject(Type *);
extern void add_immediate(SInt16,SInt16,void *,SInt16);
extern void branch_subroutine(void *,int,void *);
extern void store_fpr(Type *,SInt16,SInt16,void *,SInt32);
extern void load_gpr(Type *,SInt16,SInt16,void *,SInt32);
extern void store_vr(SInt16,SInt16,void *,SInt32);
extern void store_vr_x(SInt16,SInt16,SInt16);
extern void store_fpr_x(Type *,SInt16,SInt16,SInt16);
extern void store_gpr(Type *,SInt16,SInt16,void *,SInt32);
extern void store_gpr_x(Type *,SInt16,SInt16,SInt16);
extern void setpcodeflags(UInt64);
extern void PPCError_FatalError(int);
extern signed char fn_00579560(Type *);
void coerce_to_addressable_before(void *,Operand *,SInt16);
void Coerce_to_register(Operand *,Type *,SInt16);

void load_address(SInt16 reg, Operand *operand)
{
    coerce_to_addressable_before(0, operand, -1);
    switch (operand->kind) {
    case 9:
        if (operand->displacement == 0 && operand->object == 0) {
            if (reg != operand->reg)
                emitpcode(0x8b, reg, operand->reg);
        } else add_immediate(reg, operand->reg, operand->object, (SInt16)operand->displacement);
        break;
    case 10:
        emitpcode(0x3c,reg,operand->reg,operand->secondary_reg);
        break;
    default: CError_FATAL("Operands.c",0x953);
    }
}
void insert_bitfield(SInt16 reg, Operand *operand, TypeBitfield *record)
{
    int width = record->bitlength, shift, end;
    TypeBitfield copy;
    if (nativeByteOrder) { copy=*record; record=&copy; CABI_ReverseBitField(record); }
    shift = 32 - record->bitfieldtype->size * 8 + record->offset;
    end = shift + width;
    emitpcode(0x69,operand->reg,reg,32-end,shift,end-1);
}
void extract_bitfield(Operand *operand, TypeBitfield *record, SInt16 reg, Operand *result)
{
    int width=record->bitlength, shift, temp, resultReg;
    TypeBitfield copy;
    resultReg=reg!=-1?reg:gUsedVirtualRegistersGPR++;
    if (nativeByteOrder) { copy=*record; record=&copy; CABI_ReverseBitField(record); }
    shift=32-record->bitfieldtype->size*8+record->offset;
    if (Type_IsUnsigned(record->bitfieldtype))
        emitpcode(0x67,resultReg,operand->reg,(shift+width)&31,32-width,31);
    else if (shift==0)
        emitpcode(0x6c,resultReg,operand->reg,32-width);
    else {
        temp=gUsedVirtualRegistersGPR++;
        emitpcode(0x67,temp,operand->reg,shift&31,0,width);
        emitpcode(0x6c,resultReg,temp,32-width);
    }
    result->kind=0; result->reg=resultReg;
}
void convert_floating_to_unsigned(Operand *op, SInt16 unused)
{
    int sourceReg=op->reg;
    if(sourceReg!=1) emitpcode(0x9e,1,sourceReg);
    branch_subroutine(floating_unsigned_helper,0,data_006ad568);
    op->kind=0; {int reg=gUsedVirtualRegistersGPR++;op->reg=reg;}
    emitpcode(0x8b,op->reg,3);
}
void convert_floating_to_integer(Operand *op, SInt16 requested)
{
    void *obj=CodeGen_AllocateTemporaryObject(&stdouble);
    Operand local;
    int freg; SInt16 reg;
    memclrw(&local,sizeof(local)); local.reg=-1; local.regHi=-1; local.kind=8; local.object=obj;
    coerce_to_addressable_before(0,&local,-1);
    freg=gUsedVirtualRegistersFPR++;
    emitpcode(0xb7,freg,op->reg);
    store_fpr(&stdouble,(SInt16)freg,local.reg,local.object,0);
    reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
    load_gpr(&stsignedint,reg,local.reg,local.object,low_word_offset);
    op->kind=0;op->reg=reg;
}
void store_v(SInt16 reg,Operand *op,Type *unused)
{
    coerce_to_addressable_before(0,op,-1);
    switch(op->kind) {
    case 9: store_vr(reg,op->reg,op->object,op->displacement); setpcodeflags(op->flags);break;
    case 10: store_vr_x(reg,op->reg,op->secondary_reg);setpcodeflags(op->flags);break;
    default:CError_FATAL("Operands.c",0x5f4);
    }
}
void store_fp(SInt16 reg,Operand *op,Type *type)
{
    if(operandsDebug && type->type==2 && type->integral<0x17) PPCError_FatalError(0x21);
    coerce_to_addressable_before(0,op,-1);
    switch(op->kind) {
    case 9:store_fpr(type,reg,op->reg,op->object,op->displacement);setpcodeflags(op->flags);break;
    case 10:store_fpr_x(type,reg,op->reg,op->secondary_reg);setpcodeflags(op->flags);break;
    default:CError_FATAL("Operands.c",0x5dc);
    }
}
void store_pair(SInt16 reg,SInt16 regHi,Operand *op,Type *type)
{
    int temp;
    if(!((operandsDebug && type->type==2 && type->integral<0x17 && type->size!=4) ||
         ((type->type==1 && type->integral<0x17) || type->type==4) && type->size==8))
        CError_FATAL("Operands.c",0x5ad);
    coerce_to_addressable_before(0,op,-1);
    switch(op->kind) {
    case 9:
        store_gpr(&stsignedint,reg,op->reg,op->object,op->displacement+low_word_offset);
        setpcodeflags(op->flags);
        store_gpr(&stsignedint,regHi,op->reg,op->object,op->displacement+high_word_offset);
        setpcodeflags(op->flags);break;
    case 10:
        temp=gUsedVirtualRegistersGPR++;
        emitpcode(0x3c,(SInt16)temp,op->reg,op->secondary_reg);
        store_gpr(&stsignedint,reg,(SInt16)temp,0,low_word_offset);setpcodeflags(op->flags);
        store_gpr(&stsignedint,regHi,(SInt16)temp,0,high_word_offset);setpcodeflags(op->flags);break;
    default:CError_FATAL("Operands.c",0x5c1);
    }
}
static int scalar_store_type(Type *type)
{
    return (type->type==1 && type->integral<0x17) || type->type==4 || type->type==12 ||
        type->type==13 || (type->type==11 && **(UInt8 **)((UInt8 *)type+6)!=7) ||
        (operandsDebug && type->type==2 && type->integral<0x17 && type->size==4);
}
void store(SInt16 reg,Operand *op,Type *type)
{
    coerce_to_addressable_before(0,op,-1);
    switch(op->kind) {
    case 9:
        if(!scalar_store_type(type)) CError_FATAL("Operands.c",0x593);
        store_gpr(type,reg,op->reg,op->object,op->displacement);setpcodeflags(op->flags);break;
    case 10:
        if(!scalar_store_type(type)) CError_FATAL("Operands.c",0x599);
        store_gpr_x(type,reg,op->reg,op->secondary_reg);setpcodeflags(op->flags);break;
    default:CError_FATAL("Operands.c",0x59e);
    }
}
void fn_00590c30(SInt16 reg,Operand *op,Type *type)
{
    coerce_to_addressable_before(0,op,-1);
    switch(fn_00579560(type)) {
    case 3:CError_FATAL("Operands.c",0x56a);break;
    case 4:
        switch(op->kind) {
        case 9:store_fpr(type,reg,op->reg,op->object,op->displacement);setpcodeflags(op->flags);break;
        case 10:store_fpr_x(type,reg,op->reg,op->secondary_reg);setpcodeflags(op->flags);break;
        default:CError_FATAL("Operands.c",0x57a);
        }break;
    default:CError_FATAL("Operands.c",0x582);
    }
}
void symbol_operand(Operand *op,ENode *e)
{
    ENodeInfo *info=GetEnodeInfo(e),*again;
    memclrw(op,sizeof(*op));op->reg=-1;op->regHi=-1;
    switch(info->kind) {
    case 2:
        again=GetEnodeInfo(e);
        if(again && (again->flags&6)==6) {op->kind=3;op->regHi=info->regHi;}
        else op->kind=0;
        break;
    case 3:op->kind=5;break;
    case 4:op->kind=6;break;
    default:CError_FATAL("Operands.c",0x166);
    }
    op->reg=info->reg;
}
void fn_00592b40(Operand *op,void *object)
{
    memclrw(op,sizeof(*op));op->reg=-1;op->regHi=-1;op->kind=8;op->object=object;
}
void set_op_flags(Operand *op,ENode *e)
{
    if(!op) CError_FATAL("Operands.c",0x128);
    if(e) {
        if(e->type==0x34) {
            op->flags=0;
            if(e->flags&2) op->flags|=0x80;
            if(e->flags&1) op->flags|=0x40;
        } else {
            op->flags=CParserIsVolatileExpr(e)?0x80:0;
            op->flags|=CParserIsConstExpr(e)?0x40:0;
        }
    } else op->flags=0;
}
void fn_00592c30(int reg,SInt32 value)
{
    int base=reg;
    if(value==(SInt16)value) emitpcode(0x89,(SInt16)reg,value);
    else {
        if(optimization_level>1 && (SInt16)value!=0) base=gUsedVirtualRegistersGPR++;
        emitpcode(0x8a,(SInt16)base,0,(SInt16)(value>>16));
        if((SInt16)value!=0) emitpcode(0x58,(SInt16)reg,(SInt16)base,(UInt16)value);
    }
}
void insert_add_immediate_after(void *pcode,int reg,SInt16 base,SInt32 value)
{
    void *first;int temp=reg;
    if(value==(SInt16)value) PCode_InsertAfter(pcode,makepcode(0x3f,(SInt16)reg,(SInt16)base,0,value));
    else {
        if(optimization_level>1 && (SInt16)value!=0) temp=gUsedVirtualRegistersGPR++;
        first=makepcode(0x42,(SInt16)temp,base,0,(SInt16)((value>>16)+((value>>15)&1)));
        PCode_InsertAfter(pcode,first);
        if((SInt16)value!=0) PCode_InsertAfter(first,makepcode(0x3f,(SInt16)reg,(SInt16)temp,0,(SInt16)value));
    }
}
void insert_load_immediate_before(void *pcode,int reg,SInt32 value)
{
    void *first;int temp=reg;
    if(value==(SInt16)value) PCode_InsertBefore(pcode,makepcode(0x89,(SInt16)reg,value));
    else {
        if(optimization_level>1 && (SInt16)value!=0) temp=gUsedVirtualRegistersGPR++;
        first=makepcode(0x8a,(SInt16)temp,0,(SInt16)((value>>16)+((value>>15)&1)));
        PCode_InsertBefore(pcode,first);
        if((SInt16)value!=0) PCode_InsertAfter(first,makepcode(0x3f,(SInt16)reg,(SInt16)temp,0,(SInt16)value));
    }
}
void insert_load_immediate_after(void *pcode,int reg,SInt32 value)
{
    void *first;int temp=reg;
    if(value==(SInt16)value) PCode_InsertAfter(pcode,makepcode(0x89,(SInt16)reg,value));
    else {
        if(optimization_level>1 && (SInt16)value!=0) temp=gUsedVirtualRegistersGPR++;
        first=makepcode(0x8a,(SInt16)temp,0,(SInt16)((value>>16)+((value>>15)&1)));
        PCode_InsertAfter(pcode,first);
        if((SInt16)value!=0) PCode_InsertAfter(first,makepcode(0x3f,(SInt16)reg,(SInt16)temp,0,(SInt16)value));
    }
}
void load_immediate(int reg,SInt32 value)
{
    int base=reg;
    if(value==(SInt16)value) emitpcode(0x89,(SInt16)reg,value);
    else {
        if(optimization_level>1 && (SInt16)value!=0) base=gUsedVirtualRegistersGPR++;
        emitpcode(0x8a,(SInt16)base,0,(SInt16)((value>>16)+((value>>15)&1)));
        if((SInt16)value!=0) emitpcode(0x3f,(SInt16)reg,(SInt16)base,0,(SInt16)value);
    }
}

extern int gUsedVirtualRegistersVR;
extern UInt8 conversion_enabled;
int conversion_slots_enabled, conversion_slot;
void *conversion_slots[2];
UInt32 int_to_float_cc[2]={0x43300000,0x80000000};
UInt32 uns_to_float_cc[2]={0x43300000,0};
extern void *fn_0046b9c0(Type *);
extern void *fn_00581920(Type *,void *);
extern void load_vr(SInt16,SInt16,void *,SInt32);
extern void load_vr_x(SInt16,SInt16,SInt16);
extern void load_fpr(Type *,SInt16,SInt16,void *,SInt32);
extern void load_fpr_x(Type *,SInt16,SInt16,SInt16);
void indirect(Operand *,ENode *);
void Coerce_to_fp_register(Operand *,Type *,SInt16);
void load_floating_constant(SInt16 reg,Type *type,void *value)
{
    Operand op;void *object;
    memclrw(&op,sizeof(op));op.reg=-1;op.regHi=-1;
    object=fn_00581920(type,value);
    memclrw(&op,sizeof(op));op.reg=-1;op.regHi=-1;op.kind=8;op.object=object;
    indirect(&op,0);
    if(op.kind!=5) Coerce_to_fp_register(&op,type,reg);
}
void fn_00590230(int count)
{
    Operand op;void *object;int reg;
    conversion_slots_enabled=0;conversion_slots[0]=0;conversion_slots[1]=0;conversion_slot=0;
    if(conversion_enabled && !operandsDebug && count>=4) {
        conversion_slots_enabled=1;
        object=fn_0046b9c0(&stdouble);conversion_slots[0]=object;
        memclrw(&op,sizeof(op));op.reg=-1;op.regHi=-1;op.kind=8;op.object=object;
        coerce_to_addressable_before(0,&op,-1);
        reg=gUsedVirtualRegistersGPR++;
        emitpcode(0x8a,reg,0,0x4330);
        store_gpr(&stsignedint,(SInt16)reg,op.reg,op.object,high_word_offset);
        object=fn_0046b9c0(&stdouble);conversion_slots[1]=object;
        memclrw(&op,sizeof(op));op.reg=-1;op.regHi=-1;op.kind=8;op.object=object;
        coerce_to_addressable_before(0,&op,-1);
        reg=gUsedVirtualRegistersGPR++;
        emitpcode(0x8a,reg,0,0x4330);
        store_gpr(&stsignedint,(SInt16)reg,op.reg,op.object,high_word_offset);
    }
}
void convert_unsigned_to_floating(Operand *op,char subtract,SInt16 requested)
{
    Operand local;void *object;int constantReg,loadReg,resultReg,temp;
    UInt32 constant[2];
    if(conversion_slots_enabled) {
        object=conversion_slots[conversion_slot];conversion_slot=(conversion_slot+1)&1;
    }else object=CodeGen_AllocateTemporaryObject(&stdouble);
    memclrw(&local,sizeof(local));local.reg=-1;local.regHi=-1;local.kind=8;local.object=object;
    coerce_to_addressable_before(0,&local,-1);
    constant[0]=uns_to_float_cc[0];constant[1]=uns_to_float_cc[1];
    constantReg=gUsedVirtualRegistersFPR++;
    load_floating_constant((SInt16)constantReg,&stdouble,constant);
    store_gpr(&stsignedint,op->reg,local.reg,local.object,low_word_offset);
    if(!conversion_slots_enabled) {
        temp=gUsedVirtualRegistersGPR++;
        emitpcode(0x8a,temp,0,0x4330);
        store_gpr(&stsignedint,(SInt16)temp,local.reg,local.object,high_word_offset);
    }
    loadReg=gUsedVirtualRegistersFPR++;
    load_fpr(&stdouble,(SInt16)loadReg,local.reg,local.object,0);
    resultReg=requested!=-1?requested:gUsedVirtualRegistersFPR++;
    emitpcode((SInt16)(subtract?0xa5:0xa4),resultReg,loadReg,constantReg);
    op->kind=5;op->reg=resultReg;
}
void convert_integer_to_floating(Operand *op,char subtract,SInt16 requested)
{
    Operand local;void *object;int constantReg,loadReg,resultReg,temp;
    UInt32 constant[2];
    if(conversion_slots_enabled) {
        object=conversion_slots[conversion_slot];conversion_slot=(conversion_slot+1)&1;
    }else object=CodeGen_AllocateTemporaryObject(&stdouble);
    memclrw(&local,sizeof(local));local.reg=-1;local.regHi=-1;local.kind=8;local.object=object;
    coerce_to_addressable_before(0,&local,-1);
    constant[0]=int_to_float_cc[0];constant[1]=int_to_float_cc[1];
    constantReg=gUsedVirtualRegistersFPR++;
    load_floating_constant((SInt16)constantReg,&stdouble,constant);
    temp=gUsedVirtualRegistersGPR++;
    emitpcode(0x5b,temp,op->reg,0x8000);
    store_gpr(&stsignedint,(SInt16)temp,local.reg,local.object,low_word_offset);
    if(!conversion_slots_enabled) {
        temp=gUsedVirtualRegistersGPR++;
        emitpcode(0x8a,temp,0,0x4330);
        store_gpr(&stsignedint,(SInt16)temp,local.reg,local.object,high_word_offset);
    }
    loadReg=gUsedVirtualRegistersFPR++;
    load_fpr(&stdouble,(SInt16)loadReg,local.reg,local.object,0);
    resultReg=requested!=-1?requested:gUsedVirtualRegistersFPR++;
    emitpcode((SInt16)(subtract?0xa5:0xa4),resultReg,loadReg,constantReg);
    op->kind=5;op->reg=resultReg;
}
void extendpair(Operand *op,Type *type,SInt16 low,SInt16 high)
{
    int hi,lo;
    if(op->kind!=0) Coerce_to_register(op,type,low);
    hi=high!=-1?high:gUsedVirtualRegistersGPR++;
    if((SInt16)hi==op->reg) {
        lo=low!=-1?low:gUsedVirtualRegistersGPR++;
        emitpcode(0x8b,(SInt16)lo,op->reg);op->reg=lo;
    }
    if(Type_IsUnsigned(type)) emitpcode(0x89,(SInt16)hi,0);
    else emitpcode(0x6c,(SInt16)hi,op->reg,31);
    op->kind=3;op->regHi=hi;
}
void Coerce_to_v_register(Operand *op,Type *type,SInt16 requested)
{
    int reg;
    coerce_to_addressable_before(0,op,-1);
    switch(op->kind) {
    case 6:reg=(UInt16)op->reg;break;
    case 9:
        reg=requested!=-1?requested:gUsedVirtualRegistersVR++;
        load_vr((SInt16)reg,op->reg,op->object,op->displacement);setpcodeflags(op->flags);break;
    case 10:
        reg=requested!=-1?requested:gUsedVirtualRegistersVR++;
        load_vr_x((SInt16)reg,op->reg,op->secondary_reg);setpcodeflags(op->flags);break;
    case 4:
        reg=requested!=-1?requested:gUsedVirtualRegistersVR++;
        switch(*(signed char *)((UInt8 *)type+16)) {
        case 4:case 5:case 6:emitpcode(0x160,(SInt16)reg,op->immediate);break;
        case 7:case 8:case 9:case 14:emitpcode(0x161,(SInt16)reg,op->immediate);break;
        case 10:case 11:case 12:case 13:emitpcode(0x162,(SInt16)reg,op->immediate);break;
        default:CError_FATAL("Operands.c",0x53c);
        }
        op->kind=6;op->reg=reg;setpcodeflags(op->flags);break;
    default:CError_FATAL("Operands.c",0x546);
    }
    op->kind=6;op->reg=reg;
}
void Coerce_to_fp_register(Operand *op,Type *type,SInt16 requested)
{
    int reg;
    if(operandsDebug && type->type==2 && type->integral<0x17) PPCError_FatalError(0x21);
    coerce_to_addressable_before(0,op,-1);
    switch(op->kind) {
    case 5:reg=(UInt16)op->reg;break;
    case 9:
        reg=requested!=-1?requested:gUsedVirtualRegistersFPR++;
        load_fpr(type,(SInt16)reg,op->reg,op->object,op->displacement);setpcodeflags(op->flags);break;
    case 10:
        reg=requested!=-1?requested:gUsedVirtualRegistersFPR++;
        load_fpr_x(type,(SInt16)reg,op->reg,op->secondary_reg);setpcodeflags(op->flags);break;
    default:CError_FATAL("Operands.c",0x4fe);
    }
    op->kind=5;op->reg=reg;
}

#pragma pack(push, 2)
typedef struct AddressCache {
    void *object; int reg, derived_reg;
    void *load, *derived_load;
    struct AddressCache *next;
} AddressCache;
#pragma pack(pop)
AddressCache *data_00710390;
extern void *data_007101cc;
extern void *lalloc(int);
extern void *op_absolute_ha(SInt16,SInt16,void *,SInt16,char);
extern void *add_immediate_lo(SInt16,SInt16,void *,SInt16,char);
extern UInt8 fn_00587380(void *);
extern SInt16 fn_00587230(void *);
extern UInt8 fn_00581be0(void *);
extern int fn_005ccff0(void *), fn_004c2b40(void *);
extern UInt8 fn_004c3f60(void *);
extern void add_immediate_before(void *,SInt16,SInt16,void *,SInt16);
extern void fn_00582aa0(void *,void *);
int fn_005924d0(void *before,SInt16 base,void *object)
{
    AddressCache *entry=data_00710390;
    char emit=before==0;
    while(entry) {
        if(entry->object==object && *(void **)((UInt8 *)entry->load+8)==data_007101cc) {
            if(base!=entry->reg) CError_FATAL("Operands.c",0x1e7);
            if(!entry->derived_reg) {int reg=gUsedVirtualRegistersGPR++;entry->derived_reg=reg;}
            entry->derived_load=add_immediate_lo((SInt16)entry->derived_reg,(SInt16)entry->reg,object,0,emit);
            if(!emit) PCode_InsertBefore(before,entry->derived_load);
            return entry->derived_reg;
        }
        entry=entry->next;
    }
    return -1;
}
int fn_00592590(void *before,void *object)
{
    AddressCache *entry=data_00710390;
    char emit=before==0;
    void *load;
    while(entry) {
        if(entry->object==object && *(void **)((UInt8 *)entry->load+8)==data_007101cc) {
            entry->load=op_absolute_ha((SInt16)entry->reg,0,object,0,emit);
            if(!emit) PCode_InsertBefore(before,entry->load);
            return entry->reg;
        }
        entry=entry->next;
    }
    entry=lalloc(sizeof(*entry));memclrw(entry,sizeof(*entry));
    entry->next=data_00710390;entry->object=object;{int reg=gUsedVirtualRegistersGPR++;entry->reg=reg;}
    load=op_absolute_ha((SInt16)entry->reg,0,object,0,emit);
    if(!emit) PCode_InsertBefore(before,load);
    entry->load=load;data_00710390=entry;
    return entry->reg;
}
void coerce_to_addressable_before(void *before,Operand *op,SInt16 unused)
{
    SInt16 indirectSymbol=0;
    int frame,addressReg,resultReg;
    UInt32 address;
    void *object=op->object,*pc;
    char emit=before==0;
    switch(op->kind) {
    case 11:indirectSymbol=1;
    case 8:
        if(*((UInt8 *)object+2)==1) {
            if(!fn_00587380(object)) {
                frame=gUsedVirtualRegistersGPR++;
                pc=op_absolute_ha((SInt16)frame,fn_00587230(object),object,0,emit);
                if(!emit) PCode_InsertBefore(before,pc);
                op->kind=1;op->reg=frame;op->object=object;
            }else {op->kind=1;op->reg=fn_00587230(object);op->object=object;}
        }else if(*((UInt8 *)object+2)==2) {
            address=*(UInt32 *)((UInt8 *)object+0x40);
            if(address==(SInt16)address) {op->reg=0;op->displacement=address;}
            else {
                op->reg=gUsedVirtualRegistersGPR++;
                pc=makepcode(0x8a,op->reg,0,(SInt16)((address>>16)+((address>>15)&1)));
                if(emit) fn_00582aa0(data_007101cc,pc);else PCode_InsertBefore(before,pc);
                op->displacement=(SInt16)address;
            }
            op->kind=1;op->object=0;
        }else {
            if(fn_00581be0(object)) frame=fn_005ccff0(object);
            else {
                frame=fn_004c2b40(object);
                if(!fn_004c3f60(object)) {
                    if(op->displacement==0) frame=fn_00592590(before,object);
                    else {
                        addressReg=gUsedVirtualRegistersGPR++;
                        resultReg=gUsedVirtualRegistersGPR++;
                        pc=op_absolute_ha((SInt16)addressReg,0,object,0,emit);
                        if(!emit) PCode_InsertBefore(before,pc);
                        pc=add_immediate_lo((SInt16)resultReg,(SInt16)addressReg,object,0,emit);
                        if(!emit) PCode_InsertBefore(before,pc);
                        frame=resultReg;op->object=0;
                    }
                }else if((SInt16)frame==0) {
                    frame=gUsedVirtualRegistersGPR++;
                    add_immediate_before(before,(SInt16)frame,0,object,0);op->object=0;
                }
            }
            op->kind=1;op->reg=frame;
        }
        if(indirectSymbol) {
            if(op->kind==1) op->kind=9;else CError_FATAL("Operands.c",0x380);
        }
        break;
    case 0:case 1:case 2:case 3:case 4:case 6:case 7:case 9:case 10:break;
    default:CError_FATAL("Operands.c",0x3ad);
    }
}
UInt8 last_matches_rlwinm_or_exts(Operand *op,SInt16 opcode,SInt16 mb,SInt16 me)
{
    UInt8 *pc;
    SInt16 last;
    if(*(SInt16 *)((UInt8 *)data_007101cc+0x28)<=0) return 0;
    pc=*(UInt8 **)((UInt8 *)data_007101cc+0x18);
    if(pc[0x2c]!=0 || pc[0x2d]!=4 || *(SInt16 *)(pc+0x30)!=op->reg) return 0;
    last=*(SInt16 *)(pc+0x28);
    if(last!=opcode && !(opcode==0x65 && last==0x64)) return 0;
    if(opcode==0x67 && (*(int *)(pc+0x4a)!=0 || *(int *)(pc+0x58)!=mb || *(int *)(pc+0x66)!=me)) return 0;
    return 1;
}
void extendgpr(Operand *op,Type *type,SInt16 requested)
{
    int alreadyExtended=op->kind>=9,reg;
    if(op->kind!=0) Coerce_to_register(op,type,requested);
    switch(type->size) {
    case 1:
        {extern Type stbool;if(type==&stbool)return;}
        if(Type_IsUnsigned(type)) {
            if(alreadyExtended || last_matches_rlwinm_or_exts(op,0x67,24,31))return;
            reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
            emitpcode(0x67,reg,op->reg,0,24,31);
        }else {
            reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
            if(last_matches_rlwinm_or_exts(op,0x64,0,0))return;
            emitpcode(0x64,reg,op->reg);
        }break;
    case 2:
        if(alreadyExtended)return;
        if(Type_IsUnsigned(type)) {
            if(last_matches_rlwinm_or_exts(op,0x67,16,31))return;
            reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
            emitpcode(0x67,reg,op->reg,0,16,31);
        }else {
            if(last_matches_rlwinm_or_exts(op,0x65,0,0))return;
            reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
            emitpcode(0x65,reg,op->reg);
        }break;
    case 4:return;
    default:CError_FATAL("Operands.c",0x69a);
    }
    op->kind=0;op->reg=reg;
}

void fn_0058f300(SInt16 low,SInt16 high,Operand *op,TypeBitfield *record)
{
    int width=record->bitlength,start,end,shift,tail;
    TypeBitfield copy;
    if(nativeByteOrder){copy=*record;record=&copy;CABI_ReverseBitField(record);}
    if(!(((record->bitfieldtype->type==1 && record->bitfieldtype->integral<0x17)||record->bitfieldtype->type==4)&&record->bitfieldtype->size==8))
        CError_FATAL("Operands.c",0xa0d);
    start=record->offset;end=start+width;
    if(end<=32) emitpcode(0x69,op->regHi,low,32-end,start,end-1);
    else if(start<32 && end>32) {
        if(width>32) {
            tail=end-32;shift=32-tail;width-=32;
            if(end==64) {
                if(shift!=0)CError_FATAL("Operands.c",0xa28);
                emitpcode(0x69,op->regHi,high,0,start,31);
                emitpcode(0x8b,op->reg,low);
            }else {
                if(shift==0)CError_FATAL("Operands.c",0xa2d);
                emitpcode(0x69,op->regHi,high,32-shift,tail,start+width-1);
                emitpcode(0x69,op->regHi,low,shift,32-shift,31);
                emitpcode(0x69,op->reg,low,shift,0,tail-1);
            }
        }else {
            tail=width-(32-start);shift=32-tail;
            emitpcode(0x69,op->regHi,low,shift,start,31);
            emitpcode(0x69,op->reg,low,shift,0,tail-1);
        }
    }else {
        start-=32;end=start+width;
        emitpcode(0x69,op->reg,low,32-end,start,end-1);
    }
}
void fn_0058f550(Operand *op,TypeBitfield *record,SInt16 low,SInt16 high,Operand *result)
{
    int width=record->bitlength,start,end,shift,tail,lo,hi,temp;
    TypeBitfield copy;
    lo=low!=-1?low:gUsedVirtualRegistersGPR++;
    hi=high!=-1?high:gUsedVirtualRegistersGPR++;
    if(nativeByteOrder){copy=*record;record=&copy;CABI_ReverseBitField(record);}
    if(!(((record->bitfieldtype->type==1 && record->bitfieldtype->integral<0x17)||record->bitfieldtype->type==4)&&record->bitfieldtype->size==8))
        CError_FATAL("Operands.c",0x96b);
    start=record->offset;end=start+width;
    if(end<=32) {
        if(Type_IsUnsigned(record->bitfieldtype)) {
            emitpcode(0x89,hi,0);
            emitpcode(0x67,lo,op->regHi,width&31,32-width,31);
        }else {
            if(start==0)emitpcode(0x6c,lo,op->regHi,32-width);
            else {
                temp=gUsedVirtualRegistersGPR++;
                emitpcode(0x67,temp,op->regHi,start&31,0,width);
                emitpcode(0x6c,lo,temp,32-width);
            }
            emitpcode(0x6c,hi,lo,31);
        }
    }else if(start<32 && end>32) {
        if(width>32) {
            shift=64-end;tail=width-32;width=32-shift;
            if(end==64) {
                if(shift!=0)CError_FATAL("Operands.c",0x9c7);
                if(Type_IsUnsigned(record->bitfieldtype))emitpcode(0x67,hi,op->regHi,0,start,31);
                else {
                    temp=gUsedVirtualRegistersGPR++;
                    emitpcode(0x67,temp,op->regHi,start&31,0,tail);
                    emitpcode(0x6c,hi,temp,32-tail);
                }
                emitpcode(0x8b,lo,op->reg);
            }else {
                if(shift==0)CError_FATAL("Operands.c",0x9d3);
                if(Type_IsUnsigned(record->bitfieldtype)) {
                    temp=(start+tail)&31;
                    emitpcode(0x67,hi,op->regHi,temp,32-tail,31);
                    emitpcode(0x67,lo,op->regHi,temp,0,shift);
                }else {
                    temp=start&31;
                    emitpcode(0x67,hi,op->regHi,temp,0,tail);
                    emitpcode(0x6c,hi,hi,32-tail);
                    emitpcode(0x67,lo,op->regHi,(start+tail)&31,0,shift);
                }
                emitpcode(0x69,lo,op->reg,width&31,shift,31);
            }
        }else {
            shift=32-start;tail=width-shift;
            if(Type_IsUnsigned(record->bitfieldtype)) {
                emitpcode(0x89,hi,0);
                emitpcode(0x67,lo,op->regHi,tail,32-width,31-tail);
                emitpcode(0x69,lo,op->reg,tail,32-tail,31);
            }else {
                temp=gUsedVirtualRegistersGPR++;
                emitpcode(0x67,temp,op->regHi,start&31,0,shift);
                emitpcode(0x6c,lo,temp,32-shift);
                emitpcode(0x6c,hi,lo,31);
            }
        }
    }else {
        shift=start-32;
        if(Type_IsUnsigned(record->bitfieldtype)) {
            emitpcode(0x89,hi,0);
            emitpcode(0x67,lo,op->reg,(shift+width)&31,32-width,31);
        }else {
            if(start==0)emitpcode(0x6c,lo,op->reg,32-width);
            else {
                temp=gUsedVirtualRegistersGPR++;
                emitpcode(0x67,temp,op->reg,shift&31,0,width);
                emitpcode(0x6c,lo,temp,32-width);
            }
            emitpcode(0x6c,hi,lo,31);
        }
    }
    result->kind=3;result->reg=lo;result->regHi=hi;
}

extern Type void_ptr;
extern void load_gpr_x(Type *,SInt16,SInt16,SInt16);
void coerce_to_register_pair(Operand *,Type *,SInt16,SInt16);
void Coerce_to_register(Operand *op,Type *type,SInt16 requested)
{
    int reg,base,value;SInt16 invert=0,bit=0;
    if((operandsDebug && type->type==2 && type->integral<0x17 && type->size!=4) ||
       (((type->type==1 && type->integral<0x17)||type->type==4)&&type->size==8)) {
        coerce_to_register_pair(op,type,requested,-1);return;
    }
    coerce_to_addressable_before(0,op,-1);
    switch(op->kind) {
    case 0:case 3:return;
    case 1:
        reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
        add_immediate((SInt16)reg,op->reg,op->object,(SInt16)op->displacement);break;
    case 2:
        reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
        emitpcode(0x3c,(SInt16)reg,op->reg,op->secondary_reg);break;
    case 4:
        reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
        value=op->immediate;
        if(value==(SInt16)value)emitpcode(0x89,(SInt16)reg,value);
        else {
            base=reg;
            if(optimization_level>1 && (SInt16)value!=0)base=gUsedVirtualRegistersGPR++;
            emitpcode(0x8a,(SInt16)base,0,(SInt16)((value>>16)+((value>>15)&1)));
            if((SInt16)value!=0)emitpcode(0x3f,(SInt16)reg,(SInt16)base,0,(SInt16)value);
        }break;
    case 9:
        reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
        load_gpr(type,(SInt16)reg,op->reg,op->object,op->displacement);setpcodeflags(op->flags);break;
    case 10:
        reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
        load_gpr_x(type,(SInt16)reg,op->reg,op->secondary_reg);setpcodeflags(op->flags);break;
    case 7:
        reg=requested!=-1?requested:gUsedVirtualRegistersGPR++;
        switch(op->secondary_reg) {
        case 0x18:invert=1;case 0x17:bit=2;break;
        case 0x16:invert=1;case 0x13:bit=0;break;
        case 0x15:invert=1;case 0x14:bit=1;break;
        default:CError_FATAL("Operands.c",0x431);
        }
        emitpcode(0x1ed,(SInt16)reg,op->reg,bit);
        if(invert)emitpcode(0x5a,(SInt16)reg,(SInt16)reg,1);
        break;
    default:CError_FATAL("Operands.c",0x43a);
    }
    op->kind=0;op->reg=reg;
}
void indirect(Operand *op,ENode *e)
{
    ENodeInfo *info;
    switch(op->kind) {
    case 3:case 5:CError_FATAL("Operands.c",0x177);break;
    case 7:case 9:case 10:case 11:
        if(op->kind!=0)Coerce_to_register(op,&void_ptr,-1);
    case 0:op->displacement=0;op->object=0;
    case 1:op->kind=9;set_op_flags(op,e);break;
    case 2:op->kind=10;set_op_flags(op,e);break;
    case 4:
        if(op->immediate==(SInt16)op->immediate) {op->reg=0;op->displacement=op->immediate;}
        else {
            op->reg=gUsedVirtualRegistersGPR++;
            emitpcode(0x8a,op->reg,0,(SInt16)((op->immediate>>16)+((op->immediate>>15)&1)));
            op->displacement=(SInt16)op->immediate;
        }
        op->object=0;op->kind=9;set_op_flags(op,e);break;
    case 8:
        info=GetEnodeInfo(op->object);
        if(info && (info->flags&2))symbol_operand(op,op->object);
        else {op->kind=11;set_op_flags(op,e);}break;
    default:CError_FATAL("Operands.c",0x1b1);
    }
}
void coerce_to_register_pair(Operand *op,Type *type,SInt16 first,SInt16 second)
{
    int secondRegister=-1,firstRegister,value,base;
    SInt16 targetFirst,targetSecond;
    if(!((operandsDebug && type->type==2 && type->integral<0x17 && type->size!=4) ||
       (((type->type==1 && type->integral<0x17)||type->type==4||type->type==5)&&type->size==8)))
        CError_FATAL("Operands.c",0x457);
    coerce_to_addressable_before(0,op,-1);
    switch(op->kind) {
    case 3:
        if(first!=-1 && second==-1)second=gUsedVirtualRegistersGPR++;
        if(second!=-1 && first==-1)first=gUsedVirtualRegistersGPR++;
        if(op->reg!=first || op->regHi!=second) {
            if(first==-1)first=op->reg;
            if(second==-1)second=op->regHi;
            if(first!=op->reg) {
                if(first==op->regHi) {
                    if(first==second)CError_FATAL("Operands.c",0x46f);
                    emitpcode(0x8b,second,op->regHi);
                    emitpcode(0x8b,first,op->reg);
                }else {
                    emitpcode(0x8b,first,op->reg);
                    if(op->regHi!=second)emitpcode(0x8b,second,op->regHi);
                }
            }else if(second!=op->regHi) {
                if(second==op->reg) {
                    if(first==second)CError_FATAL("Operands.c",0x47d);
                    emitpcode(0x8b,first,op->reg);
                    emitpcode(0x8b,second,op->regHi);
                }else {
                    emitpcode(0x8b,second,op->regHi);
                    if(op->reg!=first)emitpcode(0x8b,first,op->reg);
                }
            }
        }
        firstRegister=(UInt16)op->reg;secondRegister=(UInt16)op->regHi;break;
    case 0:CError_FATAL("Operands.c",0x48e);break;
    case 1:CError_FATAL("Operands.c",0x491);break;
    case 2:CError_FATAL("Operands.c",0x494);break;
    case 4:
        firstRegister=first!=-1?first:gUsedVirtualRegistersGPR++;
        value=op->immediate;
        if(value==(SInt16)value)emitpcode(0x89,(SInt16)firstRegister,value);
        else {
            base=firstRegister;
            if(optimization_level>1 && (SInt16)value!=0)base=gUsedVirtualRegistersGPR++;
            emitpcode(0x8a,(SInt16)base,0,(SInt16)((value>>16)+((value>>15)&1)));
            if((SInt16)value!=0)emitpcode(0x3f,(SInt16)firstRegister,(SInt16)base,0,(SInt16)value);
        }
        secondRegister=second!=-1?second:gUsedVirtualRegistersGPR++;
        if(Type_IsUnsigned(type) || value>=0)emitpcode(0x89,(SInt16)secondRegister,0);
        else emitpcode(0x89,(SInt16)secondRegister,-1);
        break;
    case 9:
        firstRegister=first!=-1?first:gUsedVirtualRegistersGPR++;
        secondRegister=second!=-1?second:gUsedVirtualRegistersGPR++;
        if(op->reg==(SInt16)secondRegister) {
            if(op->reg==(SInt16)firstRegister){CError_FATAL("Operands.c",0x4b4);break;}
            load_gpr(&stsignedint,(SInt16)firstRegister,op->reg,op->object,op->displacement+low_word_offset);setpcodeflags(op->flags);
            load_gpr(&stsignedint,(SInt16)secondRegister,op->reg,op->object,op->displacement+high_word_offset);setpcodeflags(op->flags);
        }else {
            load_gpr(&stsignedint,(SInt16)secondRegister,op->reg,op->object,op->displacement+high_word_offset);setpcodeflags(op->flags);
            load_gpr(&stsignedint,(SInt16)firstRegister,op->reg,op->object,op->displacement+low_word_offset);setpcodeflags(op->flags);
        }break;
    case 10:
        base=gUsedVirtualRegistersGPR++;
        firstRegister=first!=-1?first:gUsedVirtualRegistersGPR++;
        secondRegister=second!=-1?second:gUsedVirtualRegistersGPR++;
        emitpcode(0x3c,base,op->reg,op->secondary_reg);
        load_gpr(&stsignedint,(SInt16)secondRegister,(SInt16)base,0,high_word_offset);setpcodeflags(op->flags);
        load_gpr(&stsignedint,(SInt16)firstRegister,(SInt16)base,0,low_word_offset);setpcodeflags(op->flags);break;
    default:CError_FATAL("Operands.c",0x4cf);
    }
    if((SInt16)secondRegister==-1)CError_FATAL("Operands.c",0x4d3);
    else {op->kind=3;op->reg=firstRegister;op->regHi=secondRegister;}
}

extern SInt16 stack_base_reg, frame_base_reg;
extern UInt8 combine_optimization_disabled;
extern UInt8 fn_005870d0(void *,SInt32);
#define NEWREG(hint,avoid) ((hint)!=-1 && (hint)!=(avoid)?(hint):gUsedVirtualRegistersGPR++)
#define NEWREG0(hint) ((hint)!=-1?(hint):gUsedVirtualRegistersGPR++)
void combine(Operand *left,Operand *right,SInt16 hint,Operand *dest)
{
    Operand *swap;
    int reg,temp,value,sum;
    SInt16 high;
    UInt8 *pc;
    if(left->kind==8 || left->kind==11)coerce_to_addressable_before(0,left,-1);
    if(right->kind==8 || right->kind==11)coerce_to_addressable_before(0,right,-1);
    switch(left->kind*11+right->kind) {
    case 0:dest->kind=2;dest->reg=left->reg;dest->secondary_reg=right->reg;break;
    case 12:
        sum=left->displacement+right->displacement;
        if(left->object==0 && sum==(SInt16)sum)right->displacement+=left->displacement;
        else {
            reg=NEWREG(hint,right->reg);
            add_immediate((SInt16)reg,left->reg,left->object,(SInt16)left->displacement);left->reg=reg;
        }
    case 1:swap=left;left=right;right=swap;
    case 11:
        if(left->reg==stack_base_reg || left->reg==frame_base_reg) {
            dest->kind=2;dest->reg=NEWREG(hint,right->reg);dest->secondary_reg=right->reg;
            add_immediate(dest->reg,left->reg,left->object,(SInt16)left->displacement);
        }else if(right->reg==stack_base_reg || right->reg==frame_base_reg) {
            dest->kind=2;dest->reg=NEWREG(hint,left->reg);dest->secondary_reg=left->reg;
            add_immediate(dest->reg,right->reg,left->object,(SInt16)left->displacement);
        }else if(left->object) {
            dest->kind=2;dest->reg=gUsedVirtualRegistersGPR++;dest->secondary_reg=right->reg;
            add_immediate(dest->reg,left->reg,left->object,(SInt16)left->displacement);
        }else {
            dest->kind=1;dest->reg=gUsedVirtualRegistersGPR++;
            dest->displacement=left->displacement;dest->object=left->object;
            emitpcode(0x3c,dest->reg,left->reg,right->reg);
        }break;
    case 2:swap=left;left=right;right=swap;
    case 22:
        pc=0;
        if(!combine_optimization_disabled) pc=*(UInt8 **)((UInt8 *)data_007101cc+0x18);
        if(!combine_optimization_disabled && pc && pc[0x2c]==0 && pc[0x2d]==4 && left->reg==*(SInt16 *)(pc+0x30)) {
            dest->kind=2;dest->reg=left->reg;dest->secondary_reg=gUsedVirtualRegistersGPR++;
            emitpcode(0x3c,dest->secondary_reg,right->reg,left->secondary_reg);
        }else if(!combine_optimization_disabled && pc && pc[0x2c]==0 && pc[0x2d]==4 && left->secondary_reg==*(SInt16 *)(pc+0x30)) {
            dest->kind=2;dest->reg=left->secondary_reg;dest->secondary_reg=gUsedVirtualRegistersGPR++;
            emitpcode(0x3c,dest->secondary_reg,right->reg,left->reg);
        }else {
            dest->kind=2;dest->reg=right->reg;dest->secondary_reg=gUsedVirtualRegistersGPR++;
            emitpcode(0x3c,dest->secondary_reg,left->reg,left->secondary_reg);
        }break;
    case 13:swap=left;left=right;right=swap;
    case 23:
        if(right->object) {
            dest->kind=2;dest->reg=NEWREG(hint,right->reg);dest->secondary_reg=gUsedVirtualRegistersGPR++;
            emitpcode(0x3c,dest->reg,left->reg,left->secondary_reg);
            add_immediate(dest->secondary_reg,right->reg,right->object,(SInt16)right->displacement);
        }else {
            dest->kind=1;dest->displacement=right->displacement;dest->object=right->object;dest->reg=NEWREG(hint,right->reg);
            temp=gUsedVirtualRegistersGPR++;
            emitpcode(0x3c,temp,left->reg,left->secondary_reg);
            emitpcode(0x3c,dest->reg,temp,right->reg);
        }break;
    case 24:
        dest->kind=2;dest->reg=gUsedVirtualRegistersGPR++;dest->secondary_reg=gUsedVirtualRegistersGPR++;
        emitpcode(0x3c,dest->reg,left->reg,left->secondary_reg);
        emitpcode(0x3c,dest->secondary_reg,right->reg,right->secondary_reg);break;
    case 15:swap=left;left=right;right=swap;
    case 45:
        if(right->object==0) {
            dest->kind=1;dest->reg=right->reg;dest->displacement=right->displacement;dest->object=right->object;
            value=left->immediate;sum=dest->displacement+value;
            if(sum==(SInt16)sum)dest->displacement+=value;
            else {
                dest->reg=NEWREG0(hint);high=(value>>16)+((value>>15)&1);
                if(high==0)emitpcode(0x3f,dest->reg,right->reg,0,(SInt16)value);
                else {
                    sum=dest->displacement+(SInt16)value;
                    if(sum==(SInt16)sum) {
                        emitpcode(0x42,dest->reg,right->reg,0,high);
                        dest->displacement+=(SInt16)value;
                    }else {
                        temp=gUsedVirtualRegistersGPR++;
                        emitpcode(0x42,temp,right->reg,0,high);
                        emitpcode(0x3f,dest->reg,temp,0,(SInt16)value);
                    }
                }
            }break;
        }
        if(*((UInt8 *)right->object+2)==1 && fn_005870d0(right->object,right->displacement+left->immediate)) {
            dest->kind=1;dest->object=right->object;dest->reg=right->reg;
            dest->displacement=(SInt16)(right->displacement+left->immediate);break;
        }
        if(*((UInt8 *)right->object+2)==0 && !fn_004c3f60(right->object) && right->reg>0 && right->displacement==0)
            dest->reg=fn_005924d0(0,right->reg,right->object);
        else dest->reg=-1;
        if(dest->reg==-1) {
            dest->reg=gUsedVirtualRegistersGPR++;
            add_immediate(dest->reg,right->reg,right->object,(SInt16)right->displacement);
        }
        right->kind=0;right->reg=dest->reg;
        swap=left;left=right;right=swap;
    case 4:swap=left;left=right;right=swap;
    case 44:
        dest->kind=(SInt16)left->immediate!=0?1:0;
        dest->displacement=(SInt16)left->immediate;dest->object=0;
        if(left->immediate==(SInt16)left->immediate)dest->reg=right->reg;
        else {
            dest->reg=NEWREG0(hint);high=(left->immediate>>16)+((left->immediate>>15)&1);
            emitpcode(0x42,dest->reg,right->reg,0,high);
        }break;
    case 26:swap=left;left=right;right=swap;
    case 46:
        value=left->immediate;
        if(value==(SInt16)value) {
            dest->kind=1;dest->displacement=(SInt16)value;dest->reg=NEWREG(hint,right->reg);
            emitpcode(0x3c,dest->reg,right->reg,right->secondary_reg);
        }else {
            dest->kind=2;dest->reg=right->reg;dest->secondary_reg=NEWREG(hint,right->reg);
            high=(value>>16)+((value>>15)&1);
            if(high==0)emitpcode(0x3f,dest->secondary_reg,right->secondary_reg,0,(SInt16)value);
            else if((SInt16)value==0)emitpcode(0x42,dest->secondary_reg,right->secondary_reg,0,high);
            else {
                temp=gUsedVirtualRegistersGPR++;
                emitpcode(0x42,temp,right->secondary_reg,0,high);
                emitpcode(0x3f,dest->secondary_reg,temp,0,(SInt16)value);
            }
        }break;
    case 48:dest->kind=4;dest->immediate=left->immediate+right->immediate;break;
    default:CError_FATAL("Operands.c",0x2e4);
    }
}
