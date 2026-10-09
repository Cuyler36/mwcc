/* Native backend LiveRegisters.c. Dataflow architecture follows the older
 * LiveVariables/Peephole algorithms; records use the Windows PCode ABI. */
#include "compiler/common.h"
#pragma pack(push,2)
typedef struct LiveInstruction LiveInstruction;
typedef struct LiveBlock LiveBlock;
typedef struct LiveEdge LiveEdge;
typedef struct LiveOperand { UInt8 kind;SInt8 cls;UInt16 flags;SInt16 reg;UInt8 rest[8]; } LiveOperand;
struct LiveInstruction { LiveInstruction *next,*previous;LiveBlock *block;UInt32 flags,flags2;UInt8 rest[20];SInt16 opcode,count;LiveOperand operands[1]; };
struct LiveEdge { LiveEdge *hash,*nextSuccessor,*nextPredecessor;LiveBlock *from,*to; };
struct LiveBlock { LiveBlock *next,*previous;void *labels;LiveEdge *predecessors,*successors;LiveInstruction *first,*last;SInt32 number,offset,version;SInt16 instructionCount;UInt16 flags; };
typedef struct LiveSet { UInt32 *use,*def,*in,*out; } LiveSet;
typedef struct LiveClass { SInt32 nregs;LiveSet *blocks;UInt32 *current; } LiveClass;
typedef struct ReturnRegister { SInt8 cls;UInt8 pad;SInt16 reg; } ReturnRegister;
typedef struct ReturnRegisters { SInt32 count;ReturnRegister entries[1]; } ReturnRegisters;
typedef struct FlagSet { UInt32 use,def,in,out; } FlagSet;
#pragma pack(pop)
typedef char LiveOperandSize[(sizeof(LiveOperand)==14)?1:-1];
typedef char LiveClassSize[(sizeof(LiveClass)==12)?1:-1];
typedef char LiveSetSize[(sizeof(LiveSet)==16)?1:-1];
extern LiveBlock *pcbasicblocks,*epilogue,**depthfirstordering;
extern SInt32 pcblockcount,used_registers[],first_virtual[];
extern SInt8 optimization_level;
extern void *aalloc(SInt32);
extern void computedepthfirstordering(void),memclrw(void *,SInt32);
extern void CError_Internal(const char *,SInt32);
extern void bitvectorinitialize(UInt32 *,SInt32,UInt32);
extern void bitvectorcopy(UInt32 *,const UInt32 *,SInt32);
extern void bitvectorunion(UInt32 *,const UInt32 *,SInt32);
extern void bitvectorintersect(UInt32 *,const UInt32 *,SInt32);
extern SInt32 fn_005945f0(SInt8,SInt32);
LiveClass liveclasses[5];
static ReturnRegisters *output_regs;
static char filename[]="LiveRegisters.c";
void fn_006210c0(SInt8);
SInt32 fn_00621260(LiveInstruction *);
void fn_00621360(LiveInstruction *);
void fn_00621400(LiveBlock *);
void fn_00621440(void);
void fn_00621600(void);
void fn_00621770(SInt8);
void fn_00621990(SInt8);
void fn_00621b40(SInt8);
void initialize_live_registers(ReturnRegisters *);

void fn_006210c0(SInt8 cls)
{
 SInt32 nregs,bytes,i;LiveSet *set;LiveBlock *last,*next;ReturnRegister *r;
 computedepthfirstordering();
 liveclasses[cls].nregs=nregs=used_registers[cls];
 liveclasses[cls].blocks=aalloc(pcblockcount*16);bytes=((UInt32)nregs+31U>>5)*4;
 liveclasses[cls].current=aalloc(bytes);
 for(i=0;i<pcblockcount;i++){
  set=&liveclasses[cls].blocks[i];
  bitvectorinitialize(set->use=aalloc(bytes),nregs,0);
  bitvectorinitialize(set->def=aalloc(bytes),nregs,0);
  bitvectorinitialize(set->in=aalloc(bytes),nregs,0);
  bitvectorinitialize(set->out=aalloc(bytes),nregs,0);
 }
 fn_00621b40(cls);
 last=epilogue;while((next=last->next)!=0)last=next;
 for(i=0;i<output_regs->count;i++){
  r=&output_regs->entries[i];
  if(cls==r->cls)liveclasses[cls].blocks[last->number].use[r->reg>>5]|=1U<<(r->reg&31);
 }
 fn_00621990(cls);fn_00621770(cls);fn_00621600();
}
SInt32 fn_00621260(LiveInstruction *instruction)
{
 LiveOperand *operand;UInt32 count;SInt16 reg;
 if(instruction->flags&0x14098d)return 0;
 if(!instruction->block)CError_Internal(filename,553);
 if(instruction->block->flags&3)return 0;
 if(!instruction->block->predecessors)return 1;
 operand=instruction->operands;count=instruction->count;
 while(count--){
  if(operand->kind==0 && (operand->flags&2)){
   reg=operand->reg;
   if((liveclasses[operand->cls].current[reg>>5]>>(reg&31))&1)return 0;
   if(!fn_005945f0(operand->cls,reg) && optimization_level<=0)return 0;
  }
  operand++;
 }
 return 1;
}
void fn_00621360(LiveInstruction *instruction)
{
 LiveOperand *operand;UInt32 count;
 operand=instruction->operands;count=instruction->count;
 while(count--){if(operand->kind==0 && (operand->flags&2))liveclasses[operand->cls].current[operand->reg>>5]&=~(1U<<(operand->reg&31));operand++;}
 operand=instruction->operands;count=instruction->count;
 while(count--){if(operand->kind==0 && (operand->flags&1))liveclasses[operand->cls].current[operand->reg>>5]|=1U<<(operand->reg&31);operand++;}
}
void fn_00621400(LiveBlock *block)
{
 SInt8 cls=0;LiveClass *data=liveclasses;
 while(cls<5){bitvectorcopy(data->current,data->blocks[block->number].out,data->nregs);cls++;data++;}
}
void fn_00621440(void)
{
 SInt8 cls;SInt32 nregs,bytes,i;LiveSet *set;LiveBlock *last,*next;ReturnRegister *r;
 computedepthfirstordering();
 cls=0;while(cls<5){
  liveclasses[cls].nregs=nregs=used_registers[cls];
  liveclasses[cls].blocks=aalloc(pcblockcount*16);bytes=((UInt32)nregs+31U>>5)*4;
  liveclasses[cls].current=aalloc(bytes);
  for(i=0;i<pcblockcount;i++){
   set=&liveclasses[cls].blocks[i];
   bitvectorinitialize(set->use=aalloc(bytes),nregs,0);
   bitvectorinitialize(set->def=aalloc(bytes),nregs,0);
   bitvectorinitialize(set->in=aalloc(bytes),nregs,0);
   bitvectorinitialize(set->out=aalloc(bytes),nregs,0);
  }
  cls++;
 }
 fn_00621b40(-1);
 last=epilogue;while((next=last->next)!=0)last=next;
 for(i=0;i<output_regs->count;i++){
  liveclasses[output_regs->entries[i].cls].blocks[last->number].use[output_regs->entries[i].reg>>5]|=1U<<(output_regs->entries[i].reg&31);
 }
 cls=0;while(cls<5){fn_00621990(cls);cls++;}
 fn_00621600();
}
void fn_00621600(void)
{
 FlagSet *data,*set;LiveBlock *block,*ordered;LiveInstruction *instruction;LiveEdge *edge;UInt32 value;SInt32 count,live,changed;
 data=aalloc(pcblockcount*16);memclrw(data,pcblockcount*16);
 for(block=pcbasicblocks;block;block=block->next){
  set=&data[block->number];
  for(instruction=block->first;instruction;instruction=instruction->next){
   if((instruction->flags&0x400) && !set->def)set->use=1;
   if((instruction->flags&0x200) && !set->use)set->def=1;
  }
 }
 do{
  changed=0;count=pcblockcount;
  while(count){
   ordered=depthfirstordering[--count];if(ordered){
    edge=ordered->successors;set=&data[ordered->number];
    if(edge){set->out=data[edge->to->number].in;for(edge=edge->nextSuccessor;edge;edge=edge->nextSuccessor)set->out|=data[edge->to->number].in;}
    value=((UInt32)(set->def==0)&set->out)|set->use;
    if(value!=set->in){set->in=value;changed=1;}
   }
  }
 }while(changed);
 for(block=pcbasicblocks;block;block=block->next){
  live=data[block->number].out;
  if(!live)block->flags&=~0x40;else block->flags|=0x40;
  for(instruction=block->last;instruction;instruction=instruction->previous){
   if(instruction->flags&0x200){if(!live)instruction->flags&=~0x800;else instruction->flags|=0x800;live=0;}
   if(instruction->flags&0x400)live=1;
  }
 }
}
void fn_00621770(SInt8 cls)
{
 LiveSet *sets,*set;SInt32 nregs,reg;UInt32 words,i,value;UInt32 *use,*def,*in,*out,*temp;LiveBlock *block;LiveEdge *edge;
 sets=liveclasses[cls].blocks;nregs=liveclasses[cls].nregs;words=((UInt32)nregs+31)>>5;
 set=&sets[pcbasicblocks->number];def=set->def;out=set->out;in=set->in;
 temp=aalloc(words*4);bitvectorinitialize(temp,nregs,0);
 for(reg=0;reg<first_virtual[cls];reg++)if((in[reg>>5]>>(reg&31))&1)temp[reg>>5]|=1U<<(reg&31);
 bitvectorcopy(in,temp,nregs);
 for(i=0;i<words;i++){value=(*in|*def)&*out;if(value!=*out)*out=value;in++;out++;def++;}
 for(block=pcbasicblocks->next;block;block=block->next){
  set=&sets[block->number];edge=block->predecessors;in=set->in;def=set->def;
  if(edge){
   out=set->out;
   bitvectorcopy(temp,sets[edge->from->number].out,nregs);
   /* Native uses from for the first predecessor and to for later ones. */
   for(edge=edge->nextPredecessor;edge;edge=edge->nextPredecessor)bitvectorunion(temp,sets[edge->to->number].out,nregs);
   bitvectorintersect(in,temp,nregs);
   for(i=0;i<words;i++){value=(*in|*def)&*out;if(value!=*out)*out=value;in++;out++;def++;}
  }
 }
}
void fn_00621990(SInt8 cls)
{
 SInt32 nregs,count,i,changed;LiveSet *sets,*set;UInt32 words,j,value,*use,*def,*in,*out;LiveBlock *block;LiveEdge *edge;ReturnRegister *r;
 nregs=liveclasses[cls].nregs;sets=liveclasses[cls].blocks;words=((UInt32)nregs+31)>>5;
 do{
  changed=0;count=pcblockcount;
  while(count){
   block=depthfirstordering[--count];if(block){
    set=&sets[block->number];edge=block->successors;
    if(!edge){
     for(i=0;i<output_regs->count;i++){r=&output_regs->entries[i];if(cls==r->cls)liveclasses[cls].blocks[block->number].out[r->reg>>5]|=1U<<(r->reg&31);}
    }else{
     out=set->out;bitvectorcopy(out,sets[edge->to->number].in,nregs);
     for(edge=edge->nextSuccessor;edge;edge=edge->nextSuccessor)bitvectorunion(out,sets[edge->to->number].in,nregs);
    }
    out=set->out;in=set->in;use=set->use;def=set->def;
    for(j=0;j<words;j++){value=(~*def&*out)|*use;if(value!=*in){*in=value;changed=1;}in++;out++;use++;def++;}
   }
  }
 }while(changed);
}
void fn_00621b40(SInt8 cls)
{
 LiveBlock *block;LiveInstruction *instruction;LiveOperand *operand;UInt32 count,bit;SInt32 reg;LiveSet *set;
 for(block=pcbasicblocks;block;block=block->next){
  for(instruction=block->first;instruction;instruction=instruction->next){
   if(instruction->opcode!=0x82 || cls!=1){
    operand=instruction->operands;count=instruction->count;
    while(count--){
     if(operand->kind==0 && (cls==-1 || operand->cls==cls) && (operand->flags&1)){
      reg=operand->reg;bit=1U<<(reg&31);set=&liveclasses[operand->cls].blocks[block->number];
      if(!((set->def[reg>>5]>>(reg&31))&1))set->use[reg>>5]|=bit;
     }
     operand++;
    }
    operand=instruction->operands;count=instruction->count;
    while(count--){
     if(operand->kind==0 && (cls==-1 || operand->cls==cls) && (operand->flags&2)){
      reg=operand->reg;bit=1U<<(reg&31);set=&liveclasses[operand->cls].blocks[block->number];
      if(!((set->def[reg>>5]>>(reg&31))&1))set->def[reg>>5]|=bit;
     }
     operand++;
    }
   }
  }
 }
}
void initialize_live_registers(ReturnRegisters *registers)
{
 output_regs=registers;
}
