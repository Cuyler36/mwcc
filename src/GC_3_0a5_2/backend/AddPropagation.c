/* Native AddPropagation.c: descriptor-driven PCode add propagation. */
#include "compiler/common.h"
#pragma pack(push,2)
typedef struct AddInstruction AddInstruction;
typedef struct AddBlock AddBlock;
typedef struct AddOperand {
 UInt8 kind;SInt8 cls;UInt16 flags;SInt16 reg;UInt8 rest[8];
} AddOperand;
struct AddInstruction {
 AddInstruction *next,*previous;AddBlock *block;UInt32 flags,flags2;
 UInt8 reserved20[8];void *alias;UInt8 reserved32[8];SInt16 opcode,count;
 AddOperand operands[1];
};
struct AddBlock {
 AddBlock *next,*previous;void *labels,*predecessors,*successors;
 AddInstruction *first,*last;SInt32 number,offset,version;SInt16 count;UInt16 flags;
};
typedef struct AddUse {struct AddUse *next;SInt32 index;} AddUse;
typedef struct AddEntry {AddInstruction *instruction;AddUse *uses;} AddEntry;
typedef struct AddUseEntry {AddInstruction *instruction;UInt8 rest[6];} AddUseEntry;
typedef struct AddBits {UInt32 *gen,*kill,*in,*out;} AddBits;
typedef struct AddClient {
 SInt32 (*eligible)(AddInstruction *);SInt32 (*canPropagate)(SInt32,SInt32);void (*propagate)(SInt32);
 char *name,*plural,*format;UInt32 filterLow,filterHigh;UInt8 resetBefore;
} AddClient;
#pragma pack(pop)
typedef char AddOperandSize[(sizeof(AddOperand)==14)?1:-1];
typedef char AddUseEntrySize[(sizeof(AddUseEntry)==10)?1:-1];
typedef char AddClientSize[(sizeof(AddClient)==34)?1:-1];
extern AddEntry *add_entries;
extern AddUseEntry *add_use_entries;
extern AddBits *add_block_bits;
extern SInt32 add_entry_count,add_client_changed,add_client_retry;
extern AddBlock *pcbasicblocks;
extern SInt32 first_virtual[];
extern SInt8 optimization_level;
extern void fn_00642be0(void *,AddClient *,SInt32,UInt8);
extern void *fn_005a05d0(void *,SInt32,SInt32);
extern void deletepcode(AddInstruction *),change_opcode(AddInstruction *,SInt16),change_num_operands(AddInstruction *,SInt32);
extern SInt32 nbytes_loaded_or_stored_by(AddInstruction *),fn_00627050(AddInstruction *,AddInstruction *);
extern UInt8 can_add_displ_to_local(void *,SInt32);
extern void CError_Internal(const char *,SInt32);
SInt32 is_add(AddInstruction *),addpropagatestouse(SInt32,SInt32);
void propagateandremoveadd(SInt32),propagateaddinstructions(void *);
static char add_name[]="ADD",add_plural[]="ADDS",add_format[]="a%ld";
static AddClient add_prop={is_add,addpropagatestouse,propagateandremoveadd,add_name,add_plural,add_format,0x100,0x100000,0};
static char filename[]="AddPropagation.c";
SInt32 propagatedadds;

static inline SInt32 add_symbol_class(UInt8 cls)
{
 UInt8 index=cls-1;
 return index<=12 && ((1U<<index)&0x1801);
}
static inline SInt32 add_symbol_operand(AddOperand *operand)
{
 return operand->kind==4 && add_symbol_class(operand->cls);
}
static inline SInt32 add_immediate_operand(AddOperand *operand)
{
 return operand->kind==2 || add_symbol_operand(operand);
}
static inline SInt32 add_opcode(AddInstruction *instruction)
{
 return instruction->opcode==0x3c || (instruction->opcode==0x3f && add_immediate_operand(&instruction->operands[2]));
}
static inline SInt32 add_unbarriered(AddInstruction *instruction)
{
 return !((instruction->flags&0x180)|(instruction->flags2&0x100000)) && add_opcode(instruction);
}
inline SInt32 is_add(AddInstruction *instruction)
{
 return add_unbarriered(instruction) && instruction->operands[0].reg>=first_virtual[instruction->operands[0].cls];
}
void propagateaddinstructions(void *context)
{
 SInt32 iterations;
 if(optimization_level>=4)iterations=4;else iterations=1;
 fn_00642be0(context,&add_prop,iterations,1);
 propagatedadds=add_client_changed;
}
void propagateandremoveadd(SInt32 index)
{
 AddInstruction *source=add_entries[index].instruction,*destination;AddUse *use;AddBlock *block;
 SInt32 sourceReg=source->operands[1].reg,i;UInt32 sum;
 if(source->opcode==0x3f && source->operands[2].kind==4)
  source->alias=fn_005a05d0(*(void **)((char*)&source->operands[2]+6),*(SInt32*)((char*)&source->operands[2]+2),1);
 for(use=add_entries[index].uses;use;use=use->next){
  destination=add_use_entries[use->index].instruction;
  if(is_add(destination) && destination->operands[0].reg!=sourceReg){
   for(i=0;i<add_entry_count;i++){
    if(add_entries[i].instruction==destination){
     for(block=pcbasicblocks;block;block=block->next)add_block_bits[block->number].in[i>>5]&=~(1U<<(i&31));
     break;
    }
   }
  }
  if(source->opcode==0x3c){
   if(destination->flags&6){
    if(destination->operands[2].kind){change_opcode(destination,destination->opcode+2);destination->flags|=0x20;}
    destination->operands[1]=source->operands[1];destination->operands[2]=source->operands[2];destination->alias=source->alias;
   }else if(destination->opcode==0x3f){
    if(*(SInt32*)((char*)&destination->operands[2]+2))CError_Internal(filename,417);
    change_opcode(destination,0x3c);destination->operands[1]=source->operands[1];destination->operands[2]=source->operands[2];destination->alias=source->alias;
   }else if(destination->opcode==0x8b){
    change_opcode(destination,0x3c);destination->flags=source->flags;destination->flags2=source->flags2;change_num_operands(destination,3);
    destination->operands[1]=source->operands[1];destination->operands[2]=source->operands[2];destination->alias=source->alias;
   }else CError_Internal(filename,431);
  }else if(destination->opcode==0x8b){
   change_opcode(destination,0x3f);destination->flags=source->flags;destination->flags2=source->flags2;destination->alias=source->alias;change_num_operands(destination,3);
   destination->operands[1]=source->operands[1];destination->operands[2]=source->operands[2];
  }else{
   destination->operands[1]=source->operands[1];
   if(source->operands[2].kind==2){
    sum=*(UInt32*)((char*)&destination->operands[2]+2)+*(UInt32*)((char*)&source->operands[2]+2);
    destination->operands[2]=source->operands[2];*(UInt32*)((char*)&destination->operands[2]+2)=sum;destination->flags|=0x20;
   }else if(source->operands[2].kind==4){
    sum=*(UInt32*)((char*)&destination->operands[2]+2)+*(UInt32*)((char*)&source->operands[2]+2);
    destination->operands[2]=source->operands[2];*(UInt32*)((char*)&destination->operands[2]+2)=sum;destination->flags&=~0x20;
    if(destination->flags&0x60006)destination->alias=fn_005a05d0(*(void **)((char*)&destination->operands[2]+6),sum,nbytes_loaded_or_stored_by(destination));
   }else CError_Internal(filename,461);
  }
 }
 deletepcode(source);add_client_changed=1;
}
SInt32 addpropagatestouse(SInt32 index,SInt32 useIndex)
{
 AddInstruction *source=add_entries[index].instruction,*destination=add_use_entries[useIndex].instruction,*scan;
 SInt32 sourceDest=source->operands[0].reg,sourceReg=source->operands[1].reg,otherReg=sourceReg,offset;void *object;
 AddOperand *operand;UInt32 count;
 if(!destination->block){add_client_retry=1;return 0;}
 if(destination->flags&6){if(destination->flags2&0x8000)return 0;}
 else if(destination->opcode==0x3f){if(destination->operands[2].kind!=2)return 0;}
 else if(destination->opcode!=0x8b)return 0;
 if(source->opcode==0x3c){
  if(destination->count<3){if(destination->opcode!=0x8b)return 0;}
  else if(destination->operands[2].kind==2){if(*(SInt32*)((char*)&destination->operands[2]+2))return 0;}
  else{
   if(destination->operands[2].kind)return 0;
   if(destination->operands[1].kind || destination->operands[2].reg!=sourceDest || destination->operands[1].reg)return 0;
  }
  otherReg=source->operands[2].reg;
 }else{
  if(source->opcode!=0x3f){CError_Internal(filename,270);return 0;}
  if(source->operands[2].kind==4){object=*(void **)((char*)&source->operands[2]+6);offset=*(SInt32*)((char*)&source->operands[2]+2);}
  else if(source->operands[2].kind==2){object=0;offset=*(SInt32*)((char*)&source->operands[2]+2);}
  else return 0;
  if(destination->count<3){if(destination->opcode!=0x8b)return 0;}
  else{
   if(destination->operands[2].kind!=2)return 0;
   offset=(SInt32)((UInt32)offset+*(UInt32*)((char*)&destination->operands[2]+2));
   if(!object){
    switch(destination->opcode){case 0x192:case 0x193:case 0x196:case 0x197:if(offset<-2048 || offset>2047)return 0;}
    if(offset!=(SInt16)offset)return 0;
   }else if(*((UInt8*)object+2)==1){if(!can_add_displ_to_local(object,offset))return 0;}
   else if(*(SInt32*)((char*)&destination->operands[2]+2))return 0;
  }
 }
 if((destination->flags&4) && !destination->operands[0].kind && destination->operands[0].cls==4 && destination->operands[0].reg==sourceDest)return 0;
 if(destination->operands[1].reg!=sourceDest)return 0;
 if(source->block==destination->block && fn_00627050(source,destination)){
  scan=source->next;
 for(;scan && scan!=destination;scan=scan->next){
  operand=scan->operands;count=scan->count;
  while(count--){
   if(!operand->kind && operand->cls==4 && (operand->flags&2) && (operand->reg==sourceReg || operand->reg==otherReg))return 0;
   operand++;
  }
 }
 return 1;
 }else{
  if(!((add_block_bits[destination->block->number].in[index>>5]>>(index&31))&1))return 0;
  scan=destination->block->first;
 for(;scan && scan!=destination;scan=scan->next){
  operand=scan->operands;count=scan->count;
  while(count--){
   if(!operand->kind && operand->cls==4 && (operand->flags&2) && (operand->reg==sourceReg || operand->reg==otherReg))return 0;
   operand++;
  }
 }
 return 1;
 }
}
