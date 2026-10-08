/* Native structure-copy emitters, adapted from the 1.2.5 architecture. */
#include "compiler/common.h"
typedef unsigned long long UInt64;
#pragma pack(push,2)
typedef struct NativeOperand {
 UInt8 kind,unknown01;SInt16 reg,regHi,secondaryReg;
 SInt32 displacement,immediate;void *object;UInt64 flags;
} NativeOperand;
#pragma pack(pop)
typedef char NativeOperandSize[(sizeof(NativeOperand)==28)?1:-1];
extern SInt32 gUsedVirtualRegistersGPR,gUsedVirtualRegistersFPR;
extern UInt8 nativeStrictAlignment,nativeDisableFPU,nativeUseFPU,nativeOperandsDebug,nativeLimitUnroll;
extern char nativeByteType[],nativeHalfType[],nativeWordType[],nativeLongType[],nativeDoubleType[],nativeErrorType[];
extern void CError_Internal(const char *,SInt32);
extern void coerce_to_addressable_before(void *,NativeOperand *,SInt16);
extern void load_address(SInt16,NativeOperand *),setpcodeflags(UInt64);
extern void load_gpr(void *,SInt16,SInt16,void *,SInt32),load_gpr_u(void *,SInt16,SInt16,void *,SInt32);
extern void store_gpr(void *,SInt16,SInt16,void *,SInt32),store_gpr_u(void *,SInt16,SInt16,void *,SInt32);
extern void load_fpr(void *,SInt16,SInt16,void *,SInt32),store_fpr(void *,SInt16,SInt16,void *,SInt32);
extern void load_gpr_x(void *,SInt16,SInt16,SInt16),store_gpr_x(void *,SInt16,SInt16,SInt16);
extern void load_fpr_x(void *,SInt16,SInt16,SInt16),store_fpr_x(void *,SInt16,SInt16,SInt16);
extern void add_immediate(SInt16,SInt16,void *,SInt16);
extern void *makepclabel(void),*emitpcode(SInt16,...);
extern void load_immediate(SInt16,SInt32),branch_label(void *),branch_decrement_always(SInt16,void *);
extern UInt8 fn_00587380(void *),fn_00581be0(void *),fn_004c3f60(void *);
static char filename[]="StructMoves.c";
static char widthFilename[]="StructMoves.c";
void StructMoves_EmitCopy(NativeOperand *,NativeOperand *,SInt32,SInt32);
void emit_pair_copy_loop(NativeOperand *,NativeOperand *,SInt32,SInt32);
void emit_unrolled_copy(NativeOperand *,NativeOperand *,SInt32,SInt32);
void emit_load_store_copy(NativeOperand *,NativeOperand *,SInt32,SInt32);
void fn_0059f7f0(NativeOperand *,SInt32);
void fn_0059f8e0(NativeOperand *,SInt32);
SInt32 fn_0059f950(NativeOperand *);

static inline SInt32 copy_width(SInt32 size,SInt32 alignment)
{
 if(!nativeStrictAlignment && alignment<4) {
  if(alignment<=0)alignment=1;
  if(alignment<size)size=alignment;
 }
 if(size>=4)return 4;
 if(size>=4)return 4;
 if(size>=2)return 2;
 return 1;
}
static inline void *copy_type(SInt32 width)
{
 switch(width) {
 case 1:return nativeByteType;
 case 2:return nativeHalfType;
 case 4:return nativeWordType;
 case 8:return nativeLongType;
 default:CError_Internal(widthFilename,64);return nativeErrorType;
 }
}
static inline void prepare_operand(NativeOperand *operand,SInt32 size)
{
 SInt32 reg;
 if(operand->kind==11)coerce_to_addressable_before(0,operand,-1);
 if(operand->kind!=9 || operand->displacement+size>32767 || !fn_0059f950(operand)) {
  reg=gUsedVirtualRegistersGPR++;load_address((SInt16)reg,operand);
  operand->kind=9;operand->reg=(SInt16)reg;operand->object=0;operand->displacement=0;
 }
}
void StructMoves_EmitCopy(NativeOperand *source,NativeOperand *target,SInt32 size,SInt32 alignment)
{
 NativeOperand copy=*source;
 if(copy.kind<9)CError_Internal(filename,542);
 if(target->kind<9)CError_Internal(filename,544);
 if(size==1 || size==2 || size==4)emit_load_store_copy(&copy,target,size,alignment);
 else if(!nativeDisableFPU && nativeUseFPU && !nativeOperandsDebug && size==8 && alignment==8)emit_load_store_copy(&copy,target,size,alignment);
 else if(size<=16 || (!nativeLimitUnroll && size<=64))emit_unrolled_copy(&copy,target,size,alignment);
 else emit_pair_copy_loop(&copy,target,size,alignment);
}
void emit_pair_copy_loop(NativeOperand *dest,NativeOperand *src,SInt32 size,SInt32 alignment)
{
 void *label=makepclabel();SInt32 width=copy_width(size,alignment),pair,first,second;void *type=copy_type(width);
 fn_0059f7f0(dest,-width);fn_0059f7f0(src,-width);
 if(size/width==0)CError_Internal(filename,474);
 pair=width*2;first=gUsedVirtualRegistersGPR++;
 load_immediate((SInt16)first,size/pair);emitpcode(0x78,first);branch_label(label);
 first=gUsedVirtualRegistersGPR++;second=gUsedVirtualRegistersGPR++;
 load_gpr(type,(SInt16)first,src->reg,0,width);setpcodeflags(src->flags);
 load_gpr_u(type,(SInt16)second,src->reg,0,pair);setpcodeflags(src->flags);
 store_gpr(type,(SInt16)first,dest->reg,0,width);setpcodeflags(dest->flags);
 store_gpr_u(type,(SInt16)second,dest->reg,0,pair);setpcodeflags(dest->flags);
 branch_decrement_always(0xb,label);
 for(size&=pair-1;size;size-=pair) {
  pair=copy_width(size,alignment);type=copy_type(pair);first=gUsedVirtualRegistersGPR++;
  load_gpr(type,(SInt16)first,src->reg,0,width);setpcodeflags(src->flags);
  store_gpr(type,(SInt16)first,dest->reg,0,width);setpcodeflags(dest->flags);width+=pair;
 }
}
void emit_unrolled_copy(NativeOperand *dest,NativeOperand *src,SInt32 size,SInt32 alignment)
{
 SInt32 offset=0,width,first,second,chunk;void *type;
 prepare_operand(dest,size);prepare_operand(src,size);
 if(!nativeDisableFPU && nativeUseFPU && !nativeOperandsDebug && alignment%8==0)
  while(size>=16) {
   first=gUsedVirtualRegistersFPR;gUsedVirtualRegistersFPR+=2;second=first+1;
   load_fpr(nativeDoubleType,(SInt16)first,src->reg,src->object,src->displacement+offset);setpcodeflags(src->flags);
   load_fpr(nativeDoubleType,(SInt16)second,src->reg,src->object,src->displacement+offset+8);setpcodeflags(src->flags);
   store_fpr(nativeDoubleType,(SInt16)first,dest->reg,dest->object,dest->displacement+offset);setpcodeflags(dest->flags);
   store_fpr(nativeDoubleType,(SInt16)second,dest->reg,dest->object,dest->displacement+offset+8);setpcodeflags(dest->flags);
   offset+=16;size-=16;
  }
 while(size>=8) {
  if(!nativeDisableFPU && nativeUseFPU && !nativeOperandsDebug && alignment%8==0) {
   first=gUsedVirtualRegistersFPR++;
   load_fpr(nativeDoubleType,(SInt16)first,src->reg,src->object,src->displacement+offset);setpcodeflags(src->flags);
   store_fpr(nativeDoubleType,(SInt16)first,dest->reg,dest->object,dest->displacement+offset);setpcodeflags(dest->flags);
   offset+=8;size-=8;
  }else {
   width=copy_width(size,alignment);type=copy_type(width);chunk=0;
   do {
    first=gUsedVirtualRegistersGPR;gUsedVirtualRegistersGPR+=2;second=first+1;
    load_gpr(type,(SInt16)first,src->reg,src->object,src->displacement+offset);setpcodeflags(src->flags);
    load_gpr(type,(SInt16)second,src->reg,src->object,src->displacement+offset+width);setpcodeflags(src->flags);
    store_gpr(type,(SInt16)first,dest->reg,dest->object,dest->displacement+offset);setpcodeflags(dest->flags);
    store_gpr(type,(SInt16)second,dest->reg,dest->object,dest->displacement+offset+width);setpcodeflags(dest->flags);
    offset+=width*2;size-=width*2;chunk+=width*2;
   }while(chunk<8);
  }
 }
 while(size) {
  width=copy_width(size,alignment);type=copy_type(width);first=gUsedVirtualRegistersGPR++;
  load_gpr(type,(SInt16)first,src->reg,src->object,src->displacement+offset);setpcodeflags(src->flags);
  store_gpr(type,(SInt16)first,dest->reg,dest->object,dest->displacement+offset);setpcodeflags(dest->flags);
  offset+=width;size-=width;
 }
}
void emit_load_store_copy(NativeOperand *dest,NativeOperand *src,SInt32 size,SInt32 alignment)
{
 SInt32 reg,width,offset;void *type;
 prepare_operand(dest,size);prepare_operand(src,size);
 if(!nativeDisableFPU && nativeUseFPU && !nativeOperandsDebug && size==8 && alignment%8==0) {
  reg=gUsedVirtualRegistersFPR++;
  if(src->kind==9)load_fpr(nativeDoubleType,(SInt16)reg,src->reg,src->object,src->displacement);
  else if(src->kind==10)load_fpr_x(nativeDoubleType,(SInt16)reg,src->reg,src->secondaryReg);
  else CError_Internal(filename,248);
  setpcodeflags(src->flags);
  if(dest->kind==9)store_fpr(nativeDoubleType,(SInt16)reg,dest->reg,dest->object,dest->displacement);
  else if(dest->kind==10)store_fpr_x(nativeDoubleType,(SInt16)reg,dest->reg,dest->secondaryReg);
  else CError_Internal(filename,260);
  setpcodeflags(dest->flags);
 }else {
  width=copy_width(size,alignment);
  if(width!=size) {
   if(dest->kind==10)prepare_operand(dest,size);
   if(src->kind==10)prepare_operand(src,size);
  }
  type=copy_type(width);offset=0;
  while(size) {
   reg=gUsedVirtualRegistersGPR++;
   if(src->kind==9)load_gpr(type,(SInt16)reg,src->reg,src->object,src->displacement+offset);
   else if(src->kind==10)load_gpr_x(type,(SInt16)reg,src->reg,src->secondaryReg);
   else CError_Internal(filename,284);
   setpcodeflags(src->flags);
   if(dest->kind==9)store_gpr(type,(SInt16)reg,dest->reg,dest->object,dest->displacement+offset);
   else if(dest->kind==10)store_gpr_x(type,(SInt16)reg,dest->reg,dest->secondaryReg);
   else CError_Internal(filename,296);
   setpcodeflags(dest->flags);offset+=width;size-=width;
  }
 }
}
void fn_0059f7f0(NativeOperand *operand,SInt32 offset)
{
 SInt32 reg=gUsedVirtualRegistersGPR++;
 if(operand->kind==11)coerce_to_addressable_before(0,operand,-1);
 if(operand->kind==9) {
  offset+=operand->displacement;
  if(offset!=(SInt16)offset) {
   add_immediate((SInt16)reg,operand->reg,operand->object,(SInt16)operand->displacement);
   emitpcode(0x3f,reg,reg,0,offset-operand->displacement);
  }else add_immediate((SInt16)reg,operand->reg,operand->object,(SInt16)offset);
 }else if(operand->kind==10) {
  emitpcode(0x3c,reg,operand->reg,operand->secondaryReg);emitpcode(0x3f,reg,reg,0,offset);
 }else CError_Internal(filename,182);
 operand->kind=9;operand->reg=(SInt16)reg;operand->object=0;operand->displacement=0;
}
void fn_0059f8e0(NativeOperand *operand,SInt32 size)
{
 prepare_operand(operand,size);
}
SInt32 fn_0059f950(NativeOperand *operand)
{
 char *object=operand->object;
 switch(operand->kind) {
 case 1:case 9:
  if(!object)return 1;
  if(object[2]==1)return fn_00587380(object);
  if(object[2]==2) {
   if(*(SInt32 *)(object+64)==(SInt16)*(SInt32 *)(object+64))return 1;
   return 0;
  }
  if(!fn_00581be0(object) && !fn_004c3f60(object))return 0;
  return 1;
 case 0:case 2:case 10:return 1;
 default:return 0;
 }
}

/* Additional native StructMoves.c zeroing and partial-register moves. */
#pragma pack(push,2)
typedef struct NativeScalarType { UInt8 kind,pad; SInt32 size; } NativeScalarType;
#pragma pack(pop)
extern UInt8 nativeScheduleLevel;
extern SInt16 nativeHighWordOffset,nativeLowWordOffset;
extern UInt8 is_unsigned(void *);
void fn_0059ce20(NativeOperand *,SInt32,SInt32);
void fn_0059cef0(NativeOperand *,SInt32,SInt32);
void fn_0059d1e0(NativeOperand *,SInt32,SInt32);
void fn_0059d390(NativeOperand *,SInt32,SInt32);
void fn_0059d5f0(SInt16,SInt16,NativeOperand *,NativeScalarType *,SInt32);
void fn_0059d6b0(SInt16,NativeOperand *,NativeScalarType *,SInt32);
void fn_0059d730(SInt16,SInt16,NativeOperand *,SInt32,SInt32,SInt32);
void fn_0059db10(SInt16,SInt16,NativeOperand *,NativeScalarType *,SInt32);
void fn_0059e030(SInt16,NativeOperand *,NativeScalarType *,SInt32);
void fn_0059e250(SInt16,SInt16,NativeOperand *,SInt32,SInt32,SInt32);

void fn_0059ce20(NativeOperand *operand,SInt32 size,SInt32 alignment)
{
 NativeOperand copy=*operand;
 if(copy.kind<9)CError_Internal(filename,1197);
 if(size==1 || size==2 || size==4)fn_0059d390(&copy,size,alignment);
 else if(size<=16 || (!nativeLimitUnroll && size<=64))fn_0059d1e0(&copy,size,alignment);
 else fn_0059cef0(&copy,size,alignment);
}
void fn_0059cef0(NativeOperand *operand,SInt32 size,SInt32 alignment)
{
 void *label=makepclabel();SInt32 width=copy_width(size,alignment),pair=width*2,first,zero;
 gUsedVirtualRegistersGPR++;
 fn_0059f7f0(operand,-width);
 zero=(SInt16)gUsedVirtualRegistersGPR++;
 load_immediate((SInt16)zero,0);
 first=gUsedVirtualRegistersGPR;
 if(pair<size) {
  gUsedVirtualRegistersGPR++;
  load_immediate((SInt16)first,size/pair);emitpcode(0x78,first);branch_label(label);
  store_gpr(copy_type(width),(SInt16)zero,operand->reg,0,width);setpcodeflags(operand->flags);
  store_gpr_u(copy_type(width),(SInt16)zero,operand->reg,0,pair);setpcodeflags(operand->flags);
  branch_decrement_always(0xb,label);
 }
 for(size&=pair-1;size;size-=pair) {
  pair=copy_width(size,alignment);
  store_gpr(copy_type(pair),(SInt16)zero,operand->reg,0,width);setpcodeflags(operand->flags);
  width+=pair;
 }
}
void fn_0059d1e0(NativeOperand *operand,SInt32 size,SInt32 alignment)
{
 SInt32 offset=0,width;SInt16 zero;
 prepare_operand(operand,size);
 zero=(SInt16)gUsedVirtualRegistersGPR++;
 load_immediate(zero,0);
 while(size) {
  width=copy_width(size,alignment);
  store_gpr(copy_type(width),zero,operand->reg,operand->object,operand->displacement+offset);setpcodeflags(operand->flags);
  offset+=width;size-=width;
 }
}
void fn_0059d390(NativeOperand *operand,SInt32 size,SInt32 alignment)
{
 SInt32 width,offset=0;SInt16 zero;
 if(operand->kind==11)coerce_to_addressable_before(0,operand,-1);
 width=copy_width(size,alignment);
 if(width!=size && operand->kind==10)prepare_operand(operand,size);
 while(size) {
  zero=(SInt16)gUsedVirtualRegistersGPR++;load_immediate(zero,0);
  if(operand->kind==9){store_gpr(copy_type(width),zero,operand->reg,operand->object,operand->displacement+offset);setpcodeflags(operand->flags);}
  else if(operand->kind==10){store_gpr_x(copy_type(width),zero,operand->reg,operand->secondaryReg);setpcodeflags(operand->flags);}
  else CError_Internal(filename,1050);
  offset+=width;size-=width;
 }
}
static inline void partial_operand(NativeOperand *operand)
{
 SInt32 reg;
 coerce_to_addressable_before(0,operand,-1);
 if(operand->kind==10){reg=gUsedVirtualRegistersGPR++;load_address((SInt16)reg,operand);operand->kind=9;operand->reg=(SInt16)reg;operand->object=0;operand->displacement=0;}
}
void fn_0059d5f0(SInt16 high,SInt16 low,NativeOperand *operand,NativeScalarType *type,SInt32 alignment)
{
 partial_operand(operand);if(nativeStrictAlignment)alignment=4;
 fn_0059d730(high,operand->reg,operand,nativeHighWordOffset+operand->displacement,type->size-4,alignment);
 fn_0059d730(low,operand->reg,operand,nativeLowWordOffset+operand->displacement,4,alignment);
}
void fn_0059d6b0(SInt16 reg,NativeOperand *operand,NativeScalarType *type,SInt32 alignment)
{
 partial_operand(operand);if(nativeStrictAlignment)alignment=4;
 fn_0059d730(reg,operand->reg,operand,operand->displacement,type->size,alignment);
}
void fn_0059d730(SInt16 reg,SInt16 base,NativeOperand *operand,SInt32 offset,SInt32 size,SInt32 alignment)
{
 SInt16 temporary=(SInt16)gUsedVirtualRegistersGPR;
 switch(size) {
 case 1:
  gUsedVirtualRegistersGPR++;emitpcode(0x67,temporary,reg,8,24,31);setpcodeflags(operand->flags);
  store_gpr(nativeByteType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);break;
 case 2:case 3:
  gUsedVirtualRegistersGPR++;
  if(alignment<2){
   emitpcode(0x67,temporary,reg,8,24,31);setpcodeflags(operand->flags);
   store_gpr(nativeByteType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);
   emitpcode(0x67,temporary,reg,16,24,31);setpcodeflags(operand->flags);
   store_gpr(nativeByteType,temporary,base,operand->object,offset+1);setpcodeflags(operand->flags);
  }else{
   emitpcode(0x67,temporary,reg,16,16,31);setpcodeflags(operand->flags);
   store_gpr(nativeHalfType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);
  }
  if(size==3){emitpcode(0x67,temporary,reg,24,24,31);setpcodeflags(operand->flags);store_gpr(nativeByteType,temporary,base,operand->object,offset+2);setpcodeflags(operand->flags);}
  break;
 case 4:
  if(alignment>2){store_gpr(nativeWordType,reg,base,operand->object,offset);setpcodeflags(operand->flags);}
  else if(alignment>1){
   gUsedVirtualRegistersGPR++;emitpcode(0x67,temporary,reg,16,16,31);setpcodeflags(operand->flags);
   store_gpr(nativeHalfType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);
   store_gpr(nativeHalfType,reg,base,operand->object,offset+2);setpcodeflags(operand->flags);
  }else{
   gUsedVirtualRegistersGPR++;emitpcode(0x67,temporary,reg,8,24,31);setpcodeflags(operand->flags);
   store_gpr(nativeByteType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);
   emitpcode(0x67,temporary,reg,16,24,31);setpcodeflags(operand->flags);
   store_gpr(nativeByteType,temporary,base,operand->object,offset+1);setpcodeflags(operand->flags);
   emitpcode(0x67,temporary,reg,24,24,31);setpcodeflags(operand->flags);
   store_gpr(nativeByteType,temporary,base,operand->object,offset+2);setpcodeflags(operand->flags);
   store_gpr(nativeByteType,reg,base,operand->object,offset+3);setpcodeflags(operand->flags);
  }
 }
}
void fn_0059db10(SInt16 high,SInt16 low,NativeOperand *operand,NativeScalarType *type,SInt32 alignment)
{
 SInt16 resultLow=-1,resultHigh,temp;SInt32 value;SInt16 lower;
 partial_operand(operand);if(nativeStrictAlignment)alignment=4;
 switch(operand->kind){
 case 0:CError_Internal(filename,810);break;
 case 1:CError_Internal(filename,813);break;
 case 2:CError_Internal(filename,816);break;
 case 3:
  if(high && !low)low=(SInt16)gUsedVirtualRegistersGPR++;
  if(low && !high)high=(SInt16)gUsedVirtualRegistersGPR++;
  resultHigh=operand->reg;
  if(resultHigh!=high || operand->regHi!=low){
   if(!high)high=resultHigh;if(!low)low=operand->regHi;
   if(high==resultHigh){
    if(low!=operand->regHi){
     if(low==resultHigh){if(high==low)CError_Internal(filename,793);emitpcode(0x8b,high,operand->reg);emitpcode(0x8b,low,operand->regHi);}
     else{emitpcode(0x8b,low,operand->regHi);if(operand->reg!=high)emitpcode(0x8b,high,operand->reg);}
    }
   }else if(high==operand->regHi){if(high==low)CError_Internal(filename,779);emitpcode(0x8b,low,operand->regHi);emitpcode(0x8b,high,operand->reg);}
   else{emitpcode(0x8b,high,resultHigh);if(operand->regHi!=low)emitpcode(0x8b,low,operand->regHi);}
  }
  resultHigh=operand->reg;resultLow=operand->regHi;break;
 case 4:
  resultHigh=high?high:(SInt16)gUsedVirtualRegistersGPR++;
  value=operand->immediate;lower=(SInt16)value;temp=resultHigh;
  if(value==lower)emitpcode(0x89,resultHigh,value);
  else{
   if(nativeScheduleLevel>1 && lower)temp=(SInt16)gUsedVirtualRegistersGPR++;
   emitpcode(0x8a,temp,0,(SInt16)(((UInt32)value>>16)+(((UInt32)value>>15)&1)));
   if(lower)emitpcode(0x3f,resultHigh,temp,0,lower);
  }
  resultLow=low?low:(SInt16)gUsedVirtualRegistersGPR++;
  load_immediate(resultLow,!is_unsigned(type)&&value<0?-1:0);break;
 case 9:
  resultHigh=high?high:(SInt16)gUsedVirtualRegistersGPR++;
  resultLow=low?low:(SInt16)gUsedVirtualRegistersGPR++;
  if(operand->reg==resultLow){
   if(operand->reg==resultHigh)CError_Internal(filename,848);
   else{
    fn_0059e250(resultHigh,operand->reg,operand,nativeHighWordOffset+operand->displacement,type->size-4,alignment);
    fn_0059e250(resultLow,operand->reg,operand,nativeLowWordOffset+operand->displacement,4,alignment);
   }
  }else{
   fn_0059e250(resultLow,operand->reg,operand,nativeLowWordOffset+operand->displacement,4,alignment);
   fn_0059e250(resultHigh,operand->reg,operand,nativeHighWordOffset+operand->displacement,type->size-4,alignment);
  }break;
 default:CError_Internal(filename,859);break;
 }
 if(resultLow==-1)CError_Internal(filename,863);
 else{operand->kind=3;operand->reg=resultHigh;operand->regHi=resultLow;}
}
void fn_0059e030(SInt16 reg,NativeOperand *operand,NativeScalarType *type,SInt32 alignment)
{
 SInt16 result,temp,lower;SInt32 value;
 partial_operand(operand);if(nativeStrictAlignment)alignment=4;
 switch(operand->kind){
 case 0:return;
 case 1:
  result=reg?reg:(SInt16)gUsedVirtualRegistersGPR++;
  add_immediate(result,operand->reg,operand->object,(SInt16)operand->displacement);break;
 case 2:
  result=reg?reg:(SInt16)gUsedVirtualRegistersGPR++;
  emitpcode(0x3c,result,operand->reg,operand->secondaryReg);break;
 case 3:return;
 case 4:
  result=reg?reg:(SInt16)gUsedVirtualRegistersGPR++;
  value=operand->immediate;lower=(SInt16)value;
  if(value==lower)emitpcode(0x89,result,value);
  else{
   temp=result;if(nativeScheduleLevel>1 && lower)temp=(SInt16)gUsedVirtualRegistersGPR++;
   emitpcode(0x8a,temp,0,(SInt16)(((UInt32)value>>16)+(((UInt32)value>>15)&1)));
   if(lower)emitpcode(0x3f,result,temp,0,lower);
  }break;
 case 9:
  result=reg?reg:(SInt16)gUsedVirtualRegistersGPR++;
  fn_0059e250(result,operand->reg,operand,operand->displacement,type->size,alignment);break;
 default:CError_Internal(filename,732);break;
 }
 operand->kind=0;operand->reg=result;
}
void fn_0059e250(SInt16 reg,SInt16 base,NativeOperand *operand,SInt32 offset,SInt32 size,SInt32 alignment)
{
 SInt16 temporary=(SInt16)gUsedVirtualRegistersGPR,result;SInt32 delta=0;
 switch(size){
 case 1:
  gUsedVirtualRegistersGPR++;load_gpr(nativeByteType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);
  emitpcode(0x67,reg,temporary,24,0,7);setpcodeflags(operand->flags);return;
 case 2:case 3:
  gUsedVirtualRegistersGPR++;result=reg;
  if(reg==base)result=(SInt16)gUsedVirtualRegistersGPR++;
  if(alignment<2){
   temporary=(SInt16)gUsedVirtualRegistersGPR++;load_gpr(nativeByteType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);
   emitpcode(0x67,result,temporary,24,0,7);setpcodeflags(operand->flags);
   load_gpr(nativeByteType,temporary,base,operand->object,offset+1);delta+=2;setpcodeflags(operand->flags);
   emitpcode(0x69,result,temporary,16,8,15);setpcodeflags(operand->flags);
  }else{
   temporary=(SInt16)gUsedVirtualRegistersGPR++;load_gpr(nativeHalfType,temporary,base,operand->object,offset);delta+=2;setpcodeflags(operand->flags);
   emitpcode(0x67,result,temporary,16,0,15);setpcodeflags(operand->flags);
  }
  if(size==3){load_gpr(nativeByteType,temporary,base,operand->object,offset+(SInt16)delta);setpcodeflags(operand->flags);emitpcode(0x69,result,temporary,8,16,23);setpcodeflags(operand->flags);}
  break;
 case 4:
  if(alignment>2){load_gpr(nativeWordType,reg,base,operand->object,offset);setpcodeflags(operand->flags);return;}
  gUsedVirtualRegistersGPR++;result=reg;
  if(reg==base)result=(SInt16)gUsedVirtualRegistersGPR++;
  if(alignment<2){
   load_gpr(nativeByteType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);
   emitpcode(0x67,result,temporary,24,0,7);setpcodeflags(operand->flags);
   load_gpr(nativeByteType,temporary,base,operand->object,offset+1);setpcodeflags(operand->flags);
   emitpcode(0x69,result,temporary,16,8,15);setpcodeflags(operand->flags);
   load_gpr(nativeByteType,temporary,base,operand->object,offset+2);setpcodeflags(operand->flags);
   emitpcode(0x69,result,temporary,8,16,23);setpcodeflags(operand->flags);
   load_gpr(nativeByteType,temporary,base,operand->object,offset+3);setpcodeflags(operand->flags);
   emitpcode(0x69,result,temporary,0,24,31);setpcodeflags(operand->flags);
  }else{
   load_gpr(nativeHalfType,temporary,base,operand->object,offset);setpcodeflags(operand->flags);
   emitpcode(0x67,result,temporary,16,0,15);setpcodeflags(operand->flags);
   load_gpr(nativeHalfType,temporary,base,operand->object,offset+2);setpcodeflags(operand->flags);
   emitpcode(0x69,result,temporary,0,16,31);setpcodeflags(operand->flags);
  }break;
 default:return;
 }
 if(result!=reg)emitpcode(0x8b,reg,result);
}
