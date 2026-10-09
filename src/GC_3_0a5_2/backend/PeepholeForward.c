/* Native PeepholeForward.c; forward PCode rewrites and mask analysis. */
#include "compiler/common.h"
#pragma pack(push,2)
typedef struct ForwardInstruction ForwardInstruction;
typedef struct ForwardBlock ForwardBlock;
typedef struct ForwardOperand {
 UInt8 kind;SInt8 cls;UInt16 flags;
 union { SInt16 reg;SInt32 immediate;void *pointer; } value;
 UInt8 tail[6];
} ForwardOperand;
struct ForwardInstruction {
 ForwardInstruction *next,*previous;ForwardBlock *block;
 UInt32 flags,flags2;UInt8 rest[20];SInt16 opcode,count;
 ForwardOperand operands[1];
};
struct ForwardBlock {
 ForwardBlock *next,*previous;void *labels,*predecessors,*successors;
 ForwardInstruction *first,*last;SInt32 number,offset,version;
 SInt16 count;UInt16 flags;
};
#pragma pack(pop)
typedef char OperandSize[(sizeof(ForwardOperand)==14)?1:-1];
extern ForwardBlock *pcbasicblocks;
extern SInt32 first_virtual[];
extern UInt8 forward_floating_option;
extern void CError_Internal(const char *,SInt32);
extern ForwardInstruction *makepcode(SInt16,...),*copypcode(ForwardInstruction *);
extern void insertpcodebefore(ForwardInstruction *,ForwardInstruction *),insertpcodeafter(ForwardInstruction *,ForwardInstruction *),deletepcode(ForwardInstruction *),appendpcode(ForwardBlock *,ForwardInstruction *);
extern void change_opcode(ForwardInstruction *,SInt16),change_num_operands(ForwardInstruction *,SInt32),pcsetrecordbit(ForwardInstruction *);
extern SInt32 is_valid_displ(ForwardInstruction *,void *,SInt32),nbytes_loaded_or_stored_by(ForwardInstruction *),fn_0058b910(ForwardInstruction *,ForwardInstruction *);
extern ForwardInstruction *makecopyforload(ForwardInstruction *,SInt32,ForwardOperand *,ForwardOperand *);
extern SInt32 InstrSelection_GetMaskRange(UInt32,SInt16 *,SInt16 *),fn_00596bd0(ForwardInstruction *,ForwardInstruction *,ForwardOperand *);
static char filename[]="PeepholeForward.c";
void peepholeoptimizeforward(void *,SInt32);
void adjustforward(ForwardBlock *,SInt32);
void fn_0059ba30(ForwardInstruction *),fn_0059bbb0(ForwardInstruction *),fn_0059bde0(ForwardInstruction *);
void adjustorimmediateforward(ForwardInstruction *),adjuststoreloadforward(ForwardInstruction *);
SInt32 canuseinsert(ForwardInstruction *,ForwardInstruction *,SInt16),fn_0059cd90(ForwardInstruction *,SInt32);
UInt32 fillmaskholes(UInt32),computepossiblemask(ForwardInstruction *,SInt16);

/* PowerPC masks number bit0 at the most significant end. */
static inline UInt32 forward_mask(SInt32 begin,SInt32 end)
{
 UInt32 low,high;
 if(begin<=end){
  if(end+1>31)high=0;else high=0xffffffffU>>((end+1)&31);
  if(begin>31)low=0;else low=0xffffffffU>>(begin&31);
  return ~high&low;
 }else{
  if(end+1>31)high=0;else high=0xffffffffU>>((end+1)&31);
  if(begin>31)low=0;else low=0xffffffffU>>(begin&31);
  return ~high|low;
 }
}
static inline UInt32 forward_rotate(UInt32 value,UInt32 count)
{
 return (value>>((32-count)&31))|(value<<(count&31));
}
void peepholeoptimizeforward(void *context,SInt32 mode)
{
 ForwardBlock *block;
 for(block=pcbasicblocks;block;block=block->next)
  if(block->count>=2)adjustforward(block,mode);
}
void fn_0059ba30(ForwardInstruction *instruction)
{
 SInt16 dest,a,b,c,opcode;ForwardInstruction *scan,*replacement;ForwardOperand *operand;UInt32 count;
 if(instruction->flags&0x180)return;
 dest=instruction->operands[0].value.reg;a=instruction->operands[1].value.reg;
 b=instruction->operands[2].value.reg;c=instruction->operands[3].value.reg;
 if(dest==a || dest==b || dest==c)return;
 switch(instruction->opcode){
 case 0xaa:opcode=0xae;break;case 0xac:opcode=0xb0;break;
 case 0xab:opcode=0xaf;break;case 0xad:opcode=0xb1;break;
 default:CError_Internal(filename,792);
 }
 for(scan=instruction->next;scan;scan=scan->next){
  if(scan->flags&0x180)return;
  if(scan->opcode==0xa0 && scan->operands[1].value.reg==a){
   replacement=makepcode(opcode,scan->operands[0].value.reg,a,b,scan->operands[2].value.reg);
   insertpcodebefore(scan,replacement);deletepcode(scan);scan=replacement;
  }
  count=scan->count;operand=scan->operands;
  while(count--){
   if(!operand->kind && operand->cls==3 && (operand->flags&2) &&
    (operand->value.reg==dest || operand->value.reg==a || operand->value.reg==b || operand->value.reg==c))return;
   operand++;
  }
 }
}
void fn_0059bbb0(ForwardInstruction *instruction)
{
 SInt16 dest,a,b,add,sub,fadd,fsub;ForwardInstruction *scan,*replacement;ForwardOperand *operand;UInt32 count;
 if(instruction->flags&0x180)return;
 dest=instruction->operands[0].value.reg;a=instruction->operands[1].value.reg;b=instruction->operands[2].value.reg;
 if(dest==a || dest==b)return;
 switch(instruction->opcode){
 case 0xa6:add=0xa2;sub=0xa4;fadd=0xaa;fsub=0xac;break;
 case 0xa7:add=0xa3;sub=0xa5;fadd=0xab;fsub=0xad;break;
 default:CError_Internal(filename,701);
 }
 for(scan=instruction->next;scan;scan=scan->next){
  if(scan->flags&0x180)return;
  replacement=scan;
  if(scan->opcode==add){
   if(scan->operands[1].value.reg==dest)replacement=makepcode(fadd,scan->operands[0].value.reg,a,b,scan->operands[2].value.reg);
   else if(scan->operands[2].value.reg==dest)replacement=makepcode(fadd,scan->operands[0].value.reg,a,b,scan->operands[1].value.reg);
  }else if(scan->opcode==sub && scan->operands[2].value.reg==dest)
   replacement=makepcode(fsub,scan->operands[0].value.reg,a,b,scan->operands[1].value.reg);
  if(replacement!=scan){insertpcodebefore(scan,replacement);deletepcode(scan);scan=replacement;}
  count=scan->count;operand=scan->operands;
  while(count--){
   if(!operand->kind && operand->cls==3 && (operand->flags&2) &&
    (operand->value.reg==dest || operand->value.reg==a || operand->value.reg==b))return;
   operand++;
  }
 }
}
void fn_0059bde0(ForwardInstruction *instruction)
{
 ForwardInstruction *scan,*use;ForwardOperand *operand;UInt32 count;SInt16 original,redundant;SInt32 immediate;
 if((instruction->flags&0x180)||(instruction->flags2&0x8000)||instruction->operands[1].kind!=2)return;
 original=instruction->operands[0].value.reg;
 immediate=*(SInt32*)((char*)&instruction->operands[1]+2);
 for(scan=instruction->next;scan;scan=scan->next){
  if((scan->flags&0x180)||(scan->flags2&0x8000))return;
  count=scan->count;operand=scan->operands;
  while(count--){if(!operand->kind && operand->cls==4 && (operand->flags&2) && operand->value.reg==original)return;operand++;}
  if(scan->opcode==instruction->opcode && scan->operands[1].kind==2 && *(SInt32*)((char*)&scan->operands[1]+2)==immediate){
   redundant=scan->operands[0].value.reg;
   for(use=scan->next;use;use=use->next){
    if((use->flags&0x180)||(use->flags2&0x8000))break;
    count=use->count;operand=use->operands;
    while(count--){if(!operand->kind && operand->cls==4 && (operand->flags&3)==1 && operand->value.reg==redundant)operand->value.reg=original;operand++;}
    count=use->count;operand=use->operands;
    while(count--){if(!operand->kind && operand->cls==4 && (operand->flags&2) && (operand->value.reg==original || operand->value.reg==redundant)){use=0;break;}operand++;}
    if(!use)break;
   }
  }
 }
}
void adjustorimmediateforward(ForwardInstruction *instruction)
{
 ForwardInstruction *scan;ForwardOperand *operand;UInt32 count,immediate;SInt16 dest,source;SInt32 used=0;
 if((instruction->flags&0x180)||(instruction->flags2&0x8000)||instruction->operands[2].kind!=2)return;
 dest=instruction->operands[0].value.reg;source=instruction->operands[1].value.reg;
 immediate=*(UInt32*)((char*)&instruction->operands[2]+2);
 for(scan=instruction->next;scan;scan=scan->next){
  if((scan->flags&0x180)||(scan->flags2&0x8000))return;
  if(scan->opcode==instruction->opcode && scan->operands[1].value.reg==dest){
   if(dest==source){
    if(scan->operands[0].value.reg==dest && !used){
     deletepcode(instruction);
     if((UInt16)(instruction->opcode-0x5a)<2)*(UInt32*)((char*)&scan->operands[2]+2)^=immediate;
     else if((UInt16)(instruction->opcode-0x58)<2)*(UInt32*)((char*)&scan->operands[2]+2)|=immediate;
     else CError_Internal(filename,546);
    }
    return;
   }
   scan->operands[1].value.reg=source;
   if((UInt16)(instruction->opcode-0x5a)<2)*(UInt32*)((char*)&scan->operands[2]+2)^=immediate;
   else if((UInt16)(instruction->opcode-0x58)<2)*(UInt32*)((char*)&scan->operands[2]+2)|=immediate;
   else CError_Internal(filename,557);
  }
  count=scan->count;operand=scan->operands;
  while(count--){
   if(!operand->kind && operand->cls==4){
    if((operand->flags&2) && (operand->value.reg==dest || operand->value.reg==source))return;
    if((operand->flags&1) && operand->value.reg==dest)used=1;
   }
   operand++;
  }
 }
}
void adjuststoreloadforward(ForwardInstruction *instruction)
{
 ForwardInstruction *scan,*replacement;ForwardOperand *operand;UInt32 count;SInt32 size,otherSize,offset,otherOffset,category,changed=0,used=0,end;
 SInt16 base,dest,index;SInt8 cls;void *object,*otherObject;
 size=nbytes_loaded_or_stored_by(instruction);
 if((instruction->flags&0x180)||(instruction->flags2&0x8000))return;
 if(instruction->operands[1].kind!=0 || instruction->operands[1].cls!=4)return;
 base=instruction->operands[1].value.reg;dest=instruction->operands[0].value.reg;cls=instruction->operands[0].cls;
 if(instruction->operands[2].kind==0 && instruction->operands[2].cls==4){
  index=instruction->operands[2].value.reg;
  for(scan=instruction->next;scan;scan=scan->next){
   if(scan->flags&0x180)return;
   if(scan->flags&2){
    if(scan->operands[2].kind==0 && scan->operands[1].value.reg==base && scan->operands[2].value.reg==index){
     category=fn_0058b910(instruction,scan);
     if(used || !category)changed=1;
     else{replacement=makecopyforload(scan,category,&instruction->operands[0],&scan->operands[0]);insertpcodebefore(scan,replacement);deletepcode(scan);scan=replacement;}
    }else changed=1;
   }else if(scan->flags&4){
    if(!changed && scan->opcode==instruction->opcode && scan->operands[2].kind==0 && scan->operands[1].value.reg==base && scan->operands[2].value.reg==index)deletepcode(instruction);
    return;
   }
   count=scan->count;operand=scan->operands;
   while(count--){
    if(!operand->kind && (operand->flags&2)){
     if(operand->cls==4 && (operand->value.reg==base || operand->value.reg==index))return;
     if(operand->cls==cls && operand->value.reg==dest)used=1;
    }operand++;
   }
   if(used && changed)return;
  }
 }else{
  if(instruction->operands[2].kind==4){offset=*(SInt32*)((char*)&instruction->operands[2]+2);object=*(void**)((char*)&instruction->operands[2]+6);}
  else if(instruction->operands[2].kind==2){offset=*(SInt32*)((char*)&instruction->operands[2]+2);object=0;}
  else return;
  end=(UInt32)offset+(UInt32)size;
  for(scan=instruction->next;scan;scan=scan->next){
   /* The native barrier test deliberately reloads the original instruction. */
   if(instruction->flags&0x180)return;
   if(scan->flags&6){
    otherSize=nbytes_loaded_or_stored_by(scan);
    if(scan->operands[2].kind==4){otherOffset=*(SInt32*)((char*)&scan->operands[2]+2);otherObject=*(void**)((char*)&scan->operands[2]+6);}
    else if(scan->operands[2].kind==2){otherOffset=*(SInt32*)((char*)&scan->operands[2]+2);otherObject=0;}
    else return;
   }
   if(scan->flags&2){
    if(scan->operands[1].value.reg==base && scan->operands[2].kind==instruction->operands[2].kind && otherObject==object){
     if(otherOffset==offset && size==otherSize){
      category=fn_0058b910(instruction,scan);
      if(used || !category)changed=1;
      else{replacement=makecopyforload(scan,category,&instruction->operands[0],&scan->operands[0]);insertpcodebefore(scan,replacement);deletepcode(scan);scan=replacement;}
     }else if(offset<(SInt32)((UInt32)otherOffset+(UInt32)otherSize) && otherOffset<end)changed=1;
    }else if(instruction->operands[2].kind!=4 || scan->operands[2].kind!=4)changed=1;
   }else if(scan->flags&4){
    if(scan->operands[2].kind==0 || scan->operands[1].value.reg!=base || scan->operands[2].kind!=instruction->operands[2].kind)return;
    if(otherObject==object){
     if(!changed && otherOffset==offset && otherSize==size){if(scan->opcode==instruction->opcode)deletepcode(instruction);return;}
     if(offset<(SInt32)((UInt32)otherOffset+(UInt32)otherSize) && otherOffset<end)return;
    }else if(scan->operands[2].kind==2)return;
   }
   count=scan->count;operand=scan->operands;
   while(count--){
    if(!operand->kind && (operand->flags&2)){
     if(operand->cls==4 && operand->value.reg==base)return;
     if(operand->cls==cls && operand->value.reg==dest)used=1;
    }operand++;
   }
   if(used && changed)return;
  }
 }
}
SInt32 canuseinsert(ForwardInstruction *instruction,ForwardInstruction *scan,SInt16 reg)
{
 ForwardInstruction *def;ForwardOperand *operand;SInt32 i;UInt32 a,b;
 for(def=scan;def;def=def->previous){
  for(i=0;i<def->count;i++){
   operand=&def->operands[i];
   if(!operand->kind && operand->cls==4 && operand->value.reg==reg && (operand->flags&2))goto found;
  }
 }
 return 0;
found:
 if(def->opcode!=0x67 || def->operands[1].value.reg!=instruction->operands[1].value.reg ||
  *(SInt32*)((char*)&def->operands[2]+2)!=*(SInt32*)((char*)&instruction->operands[2]+2))return 0;
 a=forward_mask(*(SInt32*)((char*)&instruction->operands[3]+2),*(SInt32*)((char*)&instruction->operands[4]+2));
 b=forward_mask(*(SInt32*)((char*)&def->operands[3]+2),*(SInt32*)((char*)&def->operands[4]+2));
 if(a!=~b || fn_00596bd0(scan,instruction,&instruction->operands[1]) || fn_00596bd0(scan,def,&instruction->operands[1]))return 0;
 return 1;
}
UInt32 fillmaskholes(UInt32 value)
{
 UInt32 result,bit,remaining;
 bit=1;remaining=0xffffffff;result=0;
 if((value&1) && (value&0x80000000)){
  result=0xffffffff;while((value&bit)==1)bit<<=1;
  while(!(value&bit)){result&=~bit;bit<<=1;}
  return result;
 }
 while(!(value&bit) && (value&remaining)){bit<<=1;remaining<<=1;}
 while(value&remaining){result|=bit;bit<<=1;remaining<<=1;}
 return result;
}
UInt32 computepossiblemask(ForwardInstruction *instruction,SInt16 reg)
{
 ForwardOperand *operand;UInt32 count,result=0xffffffff,value,mask,shift;
 while(instruction){
  count=instruction->count;operand=instruction->operands;
  while(count--){
   if(!operand->kind && operand->cls==4 && operand->value.reg==reg && (operand->flags&2)){
    switch(instruction->opcode){
    case 0x15:case 0x16:case 0x17:case 0x18:result=0xff;break;
    case 0x19:case 0x1a:case 0x1b:case 0x1c:result=0xffff;break;
    case 0x89:result=*(UInt32*)((char*)&instruction->operands[1]+2);break;
    case 0x8a:result=*(UInt32*)((char*)&instruction->operands[1]+2)<<16;break;
    case 0x6c:result=(SInt32)computepossiblemask(instruction->previous,instruction->operands[1].value.reg)>>(*(UInt32*)((char*)&instruction->operands[2]+2)&31);break;
    case 0x67:
     value=computepossiblemask(instruction->previous,instruction->operands[1].value.reg);shift=*(UInt32*)((char*)&instruction->operands[2]+2);
     mask=forward_mask(*(SInt32*)((char*)&instruction->operands[3]+2),*(SInt32*)((char*)&instruction->operands[4]+2));
     result=forward_rotate(value,shift)&mask;
     break;
    case 0x69:
     value=computepossiblemask(instruction->previous,instruction->operands[1].value.reg);shift=*(UInt32*)((char*)&instruction->operands[2]+2);
     mask=forward_mask(*(SInt32*)((char*)&instruction->operands[3]+2),*(SInt32*)((char*)&instruction->operands[4]+2));
     result=forward_rotate(value,shift)&mask;
     mask=forward_mask(*(SInt32*)((char*)&instruction->operands[3]+2),*(SInt32*)((char*)&instruction->operands[4]+2));
     result|=~mask&computepossiblemask(instruction->previous,instruction->operands[0].value.reg);
     break;
    case 0x5d:case 0x5e:result=computepossiblemask(instruction->previous,instruction->operands[2].value.reg)|computepossiblemask(instruction->previous,instruction->operands[1].value.reg);break;
    case 0x58:case 0x5a:result=computepossiblemask(instruction->previous,instruction->operands[1].value.reg)|*(UInt32*)((char*)&instruction->operands[2]+2);break;
    case 0x59:case 0x5b:result=computepossiblemask(instruction->previous,instruction->operands[1].value.reg)|(*(UInt32*)((char*)&instruction->operands[2]+2)<<16);break;
    case 0x5c:result=computepossiblemask(instruction->previous,instruction->operands[2].value.reg)&computepossiblemask(instruction->previous,instruction->operands[1].value.reg);break;
    case 0x56:result=computepossiblemask(instruction->previous,instruction->operands[1].value.reg)&*(UInt32*)((char*)&instruction->operands[2]+2);break;
    case 0x57:result=computepossiblemask(instruction->previous,instruction->operands[1].value.reg)&(*(UInt32*)((char*)&instruction->operands[2]+2)<<16);break;
    case 0x8b:result=computepossiblemask(instruction->previous,instruction->operands[1].value.reg);break;
    case 0x66:result=0x3f;break;
    }
    return result;
   }
   operand++;
  }
  instruction=instruction->previous;
 }
 return 0xffffffff;
}

/* The two OR operand positions share the rewrite architecture. Each expansion
 * retains the native position-specific calls and operand copies. */
#define FORWARD_OR(SIDE) do { \
 if(scan->operands[(SIDE)?2:1].value.reg==dest){ \
  other=scan->operands[(SIDE)?1:2].value.reg; \
  mask=fillmaskholes(computepossiblemask(instruction,instruction->operands[0].value.reg)); \
  possible=computepossiblemask(scan,other); \
  if(mask && possible && !(mask&possible)){ \
   if(SIDE){computepossiblemask(scan,other);computepossiblemask(instruction,instruction->operands[0].value.reg);} \
   if(!canuseinsert(instruction,scan,scan->operands[2].value.reg)){ \
    if(computepossiblemask((SIDE)?scan:instruction,(SIDE)?other:dest)==0){ \
     change_opcode(scan,0x8b); \
     scan->operands[1]=scan->operands[(SIDE)?1:2]; \
     change_num_operands(scan,2); \
    }else if(computepossiblemask((SIDE)?instruction:scan,(SIDE)?dest:other)==0){ \
     change_opcode(scan,0x8b);change_num_operands(scan,2); \
    }else{ \
     def=scan->previous; \
     while(def){ \
      for(i=0;i<def->count;i++){ \
       operand=&def->operands[i]; \
       if(!operand->kind && operand->cls==4 && operand->value.reg==other && (operand->flags&2))goto found_or_def_##SIDE; \
      } \
      def=def->previous; \
     } \
found_or_def_##SIDE: \
     if(def && def->opcode==0x67 && !fn_00596bd0(scan,def,&def->operands[1])){ \
      change_num_operands(scan,5);scan->operands[1]=def->operands[1];scan->operands[2]=def->operands[2]; \
      scan->operands[3]=def->operands[3];scan->operands[4]=def->operands[4];change_opcode(scan,0x67); \
     }else if(def && def->opcode==0x5d && !fn_00596bd0(scan,def,&def->operands[1]) && !fn_00596bd0(scan,def,&def->operands[2])){ \
      scan->operands[1]=def->operands[1];scan->operands[2]=def->operands[2]; \
     }else{change_opcode(scan,0x8b);scan->operands[1]=scan->operands[(SIDE)?1:2];change_num_operands(scan,2);} \
     clone=copypcode(instruction);change_opcode(clone,0x69);clone->operands[0]=scan->operands[0];clone->operands[0].flags|=1; \
     if(InstrSelection_GetMaskRange(fillmaskholes(computepossiblemask(instruction,instruction->operands[0].value.reg)),&mergedBegin,&mergedEnd)){ \
      *(SInt32*)((char*)&clone->operands[3]+2)=mergedBegin;*(SInt32*)((char*)&clone->operands[4]+2)=mergedEnd; \
     } \
     insertpcodeafter(scan,clone); \
    } \
   }else{ \
    change_opcode(scan,0x67);change_num_operands(scan,5); \
    scan->operands[1]=instruction->operands[1];scan->operands[2]=instruction->operands[2]; \
    scan->operands[3]=instruction->operands[3];scan->operands[4]=instruction->operands[4]; \
    *(SInt32*)((char*)&scan->operands[2]+2)=0;*(SInt32*)((char*)&scan->operands[4]+2)=31; \
   } \
   goto done_rotate_scan; \
  } \
 } \
}while(0)

void adjustforward(ForwardBlock *block,SInt32 mode)
{
 ForwardInstruction *instruction,*scan,*previous,*clone,*def;ForwardOperand *operand;
 SInt16 dest,source,other,mergedBegin,mergedEnd;SInt32 begin,end,shift,scanBegin,scanEnd,scanShift,i;
 UInt32 count,possible,mask,otherMask,addend;SInt32 sourceChanged,conditionUsed,used,passedNonAdd,width;
 instruction=block->first;
 while(instruction){
  if(instruction->opcode==0x67){
   conditionUsed=0;sourceChanged=0;
   dest=instruction->operands[0].value.reg;source=instruction->operands[1].value.reg;
   shift=*(SInt32*)((char*)&instruction->operands[2]+2);
   begin=*(SInt32*)((char*)&instruction->operands[3]+2);end=*(SInt32*)((char*)&instruction->operands[4]+2);
   possible=computepossiblemask(instruction->previous,source);
   if(!(instruction->flags&0x180) && !(instruction->flags2&0x100000) && !shift && !(possible&~forward_mask(begin,end))){
    change_opcode(instruction,0x8b);instruction->flags|=0x10;change_num_operands(instruction,2);
    instruction=instruction->next;continue;
   }
   for(scan=instruction->next;scan;scan=scan->next){
    if(scan->opcode==0x67 && scan->operands[1].value.reg==dest){
     scanBegin=*(SInt32*)((char*)&scan->operands[3]+2);scanEnd=*(SInt32*)((char*)&scan->operands[4]+2);scanShift=*(SInt32*)((char*)&scan->operands[2]+2);
     if(scanBegin==begin && scanEnd==end && !scanShift){
      if(!(scan->flags2&0x100000)){change_opcode(scan,0x8b);change_num_operands(scan,2);}
      else if(!conditionUsed){pcsetrecordbit(instruction);change_opcode(scan,0x8b);scan->flags2&=~0x100000;scan->flags|=0x10;change_num_operands(scan,2);}
      else{change_opcode(scan,0x8b);scan->operands[2]=scan->operands[5];change_num_operands(scan,3);}
     }else if(dest!=source && !sourceChanged && InstrSelection_GetMaskRange(forward_rotate(forward_mask(begin,end),scanShift)&forward_mask(scanBegin,scanEnd),&mergedBegin,&mergedEnd)){
      scan->operands[1].value.reg=source;
      *(UInt32*)((char*)&scan->operands[2]+2)=(*(UInt32*)((char*)&scan->operands[2]+2)+*(UInt32*)((char*)&instruction->operands[2]+2))&31;
      *(SInt32*)((char*)&scan->operands[3]+2)=mergedBegin;*(SInt32*)((char*)&scan->operands[4]+2)=mergedEnd;
     }
    }else{
     if(scan->opcode==0x6c && scan->operands[1].value.reg==dest && dest!=source && !*(SInt32*)((char*)&instruction->operands[2]+2) &&
      !(computepossiblemask(instruction,dest)&0x80000000) && !sourceChanged){
      scanShift=*(SInt32*)((char*)&scan->operands[2]+2);
      otherMask=(scanShift<32)?0xffffffffU>>(scanShift&31):0xffffffffU;
      if(InstrSelection_GetMaskRange(forward_rotate(forward_mask(begin,end),32-scanShift)&otherMask,&mergedBegin,&mergedEnd) && !fn_0059cd90(scan,0)){
       if(!*(SInt32*)((char*)&scan->operands[2]+2))clone=makepcode(0x8b,scan->operands[0].value.reg,source);
       else clone=makepcode(0x67,scan->operands[0].value.reg,source,(32-*(UInt32*)((char*)&scan->operands[2]+2))&31,mergedBegin,mergedEnd);
       insertpcodeafter(scan,clone);if(scan->flags2&0x100000)pcsetrecordbit(scan->next);deletepcode(scan);
       goto inspect_rotate_operands;
      }
     }
     if(scan->opcode==0x5d && !sourceChanged && dest!=source && !(scan->flags2&0x100000) && !(instruction->flags2&0x100000) && scan->operands[0].value.reg!=instruction->operands[1].value.reg){
      FORWARD_OR(0);FORWARD_OR(1);
     }else if(!sourceChanged && dest!=source && end==31 && !*(SInt32*)((char*)&instruction->operands[2]+2) &&
      (((scan->opcode==0x28 || scan->opcode==0x2a) && begin<25)||((scan->opcode==0x2c || scan->opcode==0x2e)&&begin<17)) && scan->operands[0].value.reg==dest)
       scan->operands[0].value.reg=source;
     else if(scan->opcode==0x65 && scan->operands[1].value.reg==dest && !shift && begin>16 && begin<end){
      change_opcode(scan,0x8b);if((scan->flags2&0x100000) && !conditionUsed){pcsetrecordbit(instruction);scan->flags2&=~0x100000;scan->flags|=0x10;change_num_operands(scan,2);}
     }else if(scan->opcode==0x64 && scan->operands[1].value.reg==dest && !shift && begin>24 && begin<end){
      change_opcode(scan,0x8b);if((scan->flags2&0x100000) && !conditionUsed){pcsetrecordbit(instruction);scan->flags2&=~0x100000;scan->flags|=0x10;change_num_operands(scan,2);}
     }
    }
inspect_rotate_operands:
    count=scan->count;operand=scan->operands;
    while(count--){
     if(!operand->kind && operand->cls==4 && operand->value.reg==dest && (operand->flags&2)){scan=block->last;break;}
     if(!operand->kind && operand->cls==4 && operand->value.reg==source && (operand->flags&2))sourceChanged=1;
     if(!operand->kind && operand->cls==1 && !operand->value.reg)conditionUsed=1;
     operand++;
    }
   }
done_rotate_scan:
   if(mode && !(instruction->flags2&0x100000) && (instruction->flags&0x8100)==0x8000 && instruction->operands[1].value.reg<first_virtual[4] &&
    !*(SInt32*)((char*)&instruction->operands[2]+2) && (*(SInt32*)((char*)&instruction->operands[3]+2)==16 || *(SInt32*)((char*)&instruction->operands[3]+2)==24) && *(SInt32*)((char*)&instruction->operands[4]+2)==31){
    change_opcode(instruction,0x8b);instruction->flags&=~0x8000;change_num_operands(instruction,2);
   }
  }else if((instruction->opcode==0x64 || instruction->opcode==0x65) && instruction->operands[0].value.reg!=instruction->operands[1].value.reg){
   dest=instruction->operands[0].value.reg;source=instruction->operands[1].value.reg;conditionUsed=0;width=instruction->opcode==0x64?8:16;
   for(scan=instruction->next;scan;scan=scan->next){
    if(((scan->opcode>=0x28 && scan->opcode<=0x2b)||(width==16 && scan->opcode>=0x2c && scan->opcode<=0x2f)) && scan->operands[0].value.reg==dest)
     scan->operands[0].value.reg=source;
    else{
     if(scan->opcode==0x67 || scan->opcode==0x69){
      scanShift=*(SInt32*)((char*)&scan->operands[2]+2);scanBegin=*(SInt32*)((char*)&scan->operands[3]+2);scanEnd=*(SInt32*)((char*)&scan->operands[4]+2);
      mask=forward_mask(scanBegin,scanEnd);
      mask=(mask<<((32-scanShift)&31))|(mask>>(scanShift&31));
      if(!(mask&(width==8?0xffffff00:0xffff0000)) && scan->operands[1].value.reg==dest){scan->operands[1].value.reg=source;goto inspect_extension_operands;}
     }
     if(((width==8 && (UInt16)(scan->opcode-0x64)<2)||(width==16 && scan->opcode==0x65)) && scan->operands[1].value.reg==dest){
      change_opcode(scan,0x8b);
      if((scan->flags2&0x100000) && !conditionUsed){pcsetrecordbit(instruction);scan->flags2&=~0x100000;scan->flags|=0x10;change_num_operands(scan,2);}
     }
    }
inspect_extension_operands:
    count=scan->count;operand=scan->operands;
    while(count--){
     if(!operand->kind && operand->cls==4 && (operand->flags&2) && (operand->value.reg==dest || operand->value.reg==source)){scan=block->last;break;}
     if(!operand->kind && operand->cls==1 && !operand->value.reg)conditionUsed=1;
     operand++;
    }
   }
   if(mode && !(instruction->flags2&0x100000) && (instruction->flags&0x8100)==0x8000 && instruction->operands[1].value.reg<first_virtual[4]){
    change_opcode(instruction,0x8b);instruction->flags&=~0x8000;
   }
  }else if(instruction->opcode==0x3f && instruction->operands[2].kind==2){
   source=instruction->operands[1].value.reg;
   if(!source && !(instruction->operands[1].flags&1)){
    if(instruction->count==2 && !(instruction->flags&0x100) && !(instruction->flags2&0x100000)){
     instruction->operands[1]=instruction->operands[2];change_opcode(instruction,0x89);change_num_operands(instruction,2);
    }
   }else{
    addend=*(UInt32*)((char*)&instruction->operands[2]+2);
    if(!addend && !(instruction->flags&0x100) && !(instruction->flags2&0x100000)){
     if(instruction->operands[0].value.reg==source)deletepcode(instruction);
     else{change_opcode(instruction,0x8b);change_num_operands(instruction,2);}
    }else if(instruction->operands[0].value.reg==source){
     dest=instruction->operands[0].value.reg;used=0;passedNonAdd=0;
     for(scan=instruction->next;scan;scan=scan->next){
      if((scan->flags&4) && scan->operands[0].value.reg==dest)break;
      if((scan->flags&6) && scan->operands[1].value.reg==dest && scan->operands[2].kind==2 && is_valid_displ(scan,0,addend+*(UInt32*)((char*)&scan->operands[2]+2))){
       *(UInt32*)((char*)&scan->operands[2]+2)+=addend;previous=instruction->previous;deletepcode(instruction);
       if(!(scan->flags&2)||scan->operands[0].value.reg!=dest||scan->operands[0].kind!=0||scan->operands[0].cls!=4)insertpcodeafter(scan,instruction);
       instruction=previous;break;
      }
      if(scan->opcode==0x3f && scan->operands[1].value.reg==dest && scan->operands[2].kind==2 && is_valid_displ(scan,0,addend+*(UInt32*)((char*)&scan->operands[2]+2))){
       *(UInt32*)((char*)&scan->operands[2]+2)+=addend;previous=instruction->previous;deletepcode(instruction);
       if(scan->operands[0].value.reg!=dest)insertpcodeafter(scan,instruction);
       instruction=previous;break;
      }
      if(scan->flags&9){if(passedNonAdd && scan->previous!=instruction){previous=instruction->previous;deletepcode(instruction);insertpcodebefore(scan,instruction);instruction=previous;}break;}
      count=scan->count;operand=scan->operands;
      while(count--){
       if(!operand->kind && operand->cls==4 && operand->value.reg==dest && (operand->flags&3)){
        if(passedNonAdd && scan->previous!=instruction){previous=instruction->previous;deletepcode(instruction);insertpcodebefore(scan,instruction);instruction=previous;}
        used=1;break;
       }operand++;
      }
      if(used)break;
      if(scan->opcode!=0x3f)passedNonAdd=1;
      if(passedNonAdd && !scan->next){previous=instruction->previous;deletepcode(instruction);appendpcode(block,instruction);instruction=previous;break;}
     }
    }
   }
  }else if(instruction->flags&4)adjuststoreloadforward(instruction);
  else if((UInt16)(instruction->opcode-0x58)<4)adjustorimmediateforward(instruction);
  else if((UInt16)(instruction->opcode-0x89)<2)fn_0059bde0(instruction);
  else if((UInt16)(instruction->opcode-0xa6)<2){if(forward_floating_option)fn_0059bbb0(instruction);}
  else if((UInt16)(instruction->opcode-0xaa)<4 && forward_floating_option)fn_0059ba30(instruction);
  instruction=instruction?instruction->next:block->first;
 }
}
#undef FORWARD_OR
SInt32 fn_0059cd90(ForwardInstruction *list,SInt32 reg)
{
 char *node=(char*)list->next,*operand;UInt32 count;
 while(node){
  count=*(SInt16*)(node+42);operand=node+44;
  while(count--){
   if(!operand[0] && !operand[1] && *(SInt16*)(operand+4)==reg && (*(UInt16*)(operand+2)&1))return 1;
   if(!operand[0] && !operand[1] && *(SInt16*)(operand+4)==reg && (*(UInt16*)(operand+2)&2))return 0;
   operand+=14;
  }
  node=*(char**)node;
 }
 return 0;
}
