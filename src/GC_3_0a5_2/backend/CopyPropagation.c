/* Native COPY client family, attributed to CopyPropagation.c by architecture. */
#include "compiler/common.h"
#pragma pack(push,2)
typedef struct CopyInstruction CopyInstruction;
typedef struct CopyBlock CopyBlock;
typedef struct CopyOperand {UInt8 kind;SInt8 cls;UInt16 flags;SInt16 reg;UInt8 rest[8];} CopyOperand;
struct CopyInstruction {
 CopyInstruction *next,*previous;CopyBlock *block;UInt32 flags,flags2;
 UInt8 reserved20[8];void *alias;UInt8 reserved32[8];SInt16 opcode,count;CopyOperand operands[1];
};
struct CopyBlock {
 CopyBlock *next,*previous;void *labels,*predecessors,*successors;CopyInstruction *first,*last;
 SInt32 number,offset,version;SInt16 count;UInt16 flags;
};
typedef struct CopyUse {struct CopyUse *next;SInt32 index;} CopyUse;
typedef struct CopyEntry {CopyInstruction *instruction;CopyUse *uses;} CopyEntry;
typedef struct CopyUseEntry {CopyInstruction *instruction;UInt8 rest[6];} CopyUseEntry;
typedef struct CopyBits {UInt32 *gen,*kill,*in,*out;} CopyBits;
typedef struct CopyClient {
 SInt32 (*eligible)(CopyInstruction *);SInt32 (*canPropagate)(SInt32,SInt32);void (*propagate)(SInt32);
 char *name,*plural,*format;UInt32 filterLow,filterHigh;UInt8 resetBefore;
} CopyClient;
#pragma pack(pop)
typedef char CopyOperandSize[(sizeof(CopyOperand)==14)?1:-1];
typedef char CopyUseEntrySize[(sizeof(CopyUseEntry)==10)?1:-1];
typedef char CopyClientSize[(sizeof(CopyClient)==34)?1:-1];
extern CopyEntry *copy_entries;
extern CopyUseEntry *copy_use_entries;
extern CopyBits *copy_block_bits;
extern SInt32 copy_client_changed,first_virtual[];
extern void fn_00642be0(void *,CopyClient *,SInt32,UInt8);
extern SInt32 fn_00626f40(CopyInstruction *,SInt32,SInt32,CopyInstruction *,UInt32 *,SInt8);
extern void deletepcode(CopyInstruction *);
SInt32 is_copy(CopyInstruction *),copypropagatestouse(SInt32,SInt32),fn_00621d80(SInt32,SInt32);
void propagateandremovecopy(SInt32),fn_00621d40(SInt32),propagatecopyinstructions(void *,SInt32);
static char copy_name[]="COPY",copy_plural[]="COPIES",copy_format[]="c%ld";
static CopyClient copy_prop={is_copy,copypropagatestouse,propagateandremovecopy,copy_name,copy_plural,copy_format,0x180,0,0};
static CopyClient copy_selective_prop={is_copy,fn_00621d80,fn_00621d40,copy_name,copy_plural,copy_format,0x180,0,0};
SInt32 copy_valid,copy_index,copy_mode,propagatedcopies;

void propagatecopyinstructions(void *context,SInt32 mode)
{
 copy_mode=mode;
 if(mode)fn_00642be0(context,&copy_selective_prop,1,0);
 else fn_00642be0(context,&copy_prop,1,0);
 propagatedcopies=copy_client_changed;
}
void fn_00621d40(SInt32 index)
{
 CopyEntry *entry=&copy_entries[index];
 if(copy_index==index && copy_valid){deletepcode(entry->instruction);copy_client_changed=1;}
 copy_index=-1;
}
SInt32 fn_00621d80(SInt32 index,SInt32 useIndex)
{
 CopyInstruction *source,*destination;CopyOperand *operand;
 SInt32 sourceReg,replacementReg;UInt32 count;SInt8 cls;
 if(!copypropagatestouse(index,useIndex)){
  copy_valid=0;if(copy_index!=index)copy_index=index;
 }else{
  source=copy_entries[index].instruction;destination=copy_use_entries[useIndex].instruction;
  sourceReg=source->operands[0].reg;cls=source->operands[0].cls;replacementReg=source->operands[1].reg;
  operand=destination->operands;count=destination->count;
  while(count--){
   if(!operand->kind && operand->cls==cls && operand->reg==sourceReg && (operand->flags&1)){
    if(operand->flags&2){copy_valid=0;if(copy_index!=index)copy_index=index;}
    else{
     operand->reg=replacementReg;copy_client_changed=1;
     if(copy_index!=index){copy_index=index;copy_valid=1;}
    }
   }
   operand++;
  }
 }
 return 1;
}
void propagateandremovecopy(SInt32 index)
{
 CopyEntry *entry=&copy_entries[index];CopyInstruction *source=entry->instruction,*destination;
 SInt8 cls=source->operands[0].cls;SInt32 sourceReg=source->operands[0].reg,replacementReg=source->operands[1].reg;
 UInt32 count;CopyUse *use;CopyOperand *operand;
 if(!copy_mode && replacementReg<first_virtual[cls])return;
 for(use=entry->uses;use;use=use->next){
  destination=copy_use_entries[use->index].instruction;operand=destination->operands;count=destination->count;
  while(count--){
   if(!operand->kind && operand->cls==cls && operand->reg==sourceReg && (operand->flags&1))operand->reg=replacementReg;
   operand++;
  }
 }
 deletepcode(entry->instruction);copy_client_changed=1;
}
SInt32 copypropagatestouse(SInt32 index,SInt32 useIndex)
{
 CopyInstruction *source=copy_entries[index].instruction,*destination=copy_use_entries[useIndex].instruction;
 SInt8 cls=source->operands[0].cls;SInt32 sourceReg=source->operands[0].reg,replacementReg=source->operands[1].reg;
 CopyOperand *operand;UInt32 count;
 if(destination->flags&0x10)return 0;
 operand=destination->operands;count=destination->count;
 while(count--){
  if(!operand->kind && operand->cls==cls && operand->reg==sourceReg && ((operand->flags&8)||((operand->flags&3)==3)))return 0;
  operand++;
 }
 if(fn_00626f40(source,index,replacementReg,destination,copy_block_bits[destination->block->number].in,cls))return 1;
 return 0;
}
SInt32 is_copy(CopyInstruction *instruction)
{
 SInt32 result=(instruction->flags&0x10)!=0;
 if(result)result=instruction->operands[0].reg>=first_virtual[instruction->operands[0].cls];
 return result;
}
