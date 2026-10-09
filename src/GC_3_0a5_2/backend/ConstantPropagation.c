/* Native ConstantPropagation.c: class-indexed reaching-definition caches. */
#include "compiler/common.h"
typedef UInt32 uint;
typedef UInt16 ushort;
typedef UInt8 byte;
typedef UInt8 undefined1;
typedef UInt16 undefined2;
typedef UInt32 undefined4;
#define false 0
#define true 1
#pragma pack(push,2)
typedef struct ConstantInstruction ConstantInstruction;
typedef struct ConstantBlock ConstantBlock;
typedef struct ConstantOperand {UInt8 kind;SInt8 cls;UInt16 flags;SInt16 reg;UInt8 rest[8];} ConstantOperand;
struct ConstantInstruction {
 ConstantInstruction *next,*previous;ConstantBlock *block;UInt32 flags,flags2;
 UInt8 reserved20[8];void *alias;UInt8 reserved32[8];SInt16 opcode,count;ConstantOperand operands[1];
};
struct ConstantBlock {
 ConstantBlock *next,*previous;void *labels,*predecessors,*successors;ConstantInstruction *first,*last;
 SInt32 number,offset,version;SInt16 count;UInt16 flags;
};
typedef struct ConstantDefinitionLink {struct ConstantDefinitionLink *next;SInt32 index;} ConstantDefinitionLink;
typedef struct ConstantDefinitionSlot {ConstantInstruction *instruction;UInt8 rest[6];} ConstantDefinitionSlot;
typedef struct ConstantReachingBlock {UInt8 reserved[24];UInt32 *in;UInt8 rest[20];} ConstantReachingBlock;
typedef union ConstantScratch {UInt32 word;struct {SInt16 value,maskBegin;} parts;} ConstantScratch;
#pragma pack(pop)
typedef char ConstantOperandSize[(sizeof(ConstantOperand)==14)?1:-1];
typedef char ConstantSlotSize[(sizeof(ConstantDefinitionSlot)==10)?1:-1];
typedef char ConstantReachingSize[(sizeof(ConstantReachingBlock)==48)?1:-1];
extern ConstantDefinitionLink **constant_definition_heads[5];
extern ConstantDefinitionSlot *constant_definition_slots;
extern ConstantReachingBlock *constant_reaching_blocks;
extern SInt32 used_virtual_registers[5],first_virtual[5],constant_block_count;
extern ConstantBlock **constant_block_order;
extern SInt16 stack_base_reg,alternate_stack_base_reg;
extern void *aalloc(UInt32);
extern void freeaheap(void);
extern SInt32 fn_00627080(SInt32);
extern SInt32 fn_00626f40(ConstantInstruction *,SInt32,SInt32,ConstantInstruction *,UInt32 *,SInt8);
extern UInt8 can_add_displ_to_local(void *,SInt32);
extern void CError_Internal(const char *,SInt32);
extern void change_opcode(void *,SInt16),change_num_operands(void *,SInt32),pcsetrecordbit(void *),fn_00596280(void *);
extern SInt32 nbytes_loaded_or_stored_by(void *),InstrSelection_GetMaskRange(UInt32,SInt16 *,SInt16 *);
extern void *fn_005a05d0(void *,SInt32,SInt32);
static inline UInt32 constant_alias(UInt32 object,SInt32 offset,SInt32 size){return (UInt32)fn_005a05d0((void *)object,offset,size);}
static char filename[]="ConstantPropagation.c";
ConstantInstruction **constant_definitions[5];
SInt32 constant_changed,propagatedconstants;
void propagateconstants(void),propagateconstantstoblock(ConstantBlock *),computedefininginstructions(ConstantBlock *);
UInt32 issignedloadoperand(ConstantInstruction *,SInt32,SInt32),isunsignedloadoperand(ConstantInstruction *,SInt32);
ConstantInstruction *isstackoperand(ConstantOperand *,SInt16 *,SInt16);
#define CONCAT22(hi,lo) (((UInt32)(UInt16)(hi)<<16)|(UInt16)(lo))

void propagateconstants(void)
{
 /* Declaration order preserves the selected compiler's native call-site EBX
    index, which the block transform's upper-half AND fallback can observe. */
 ConstantBlock *block;SInt32 blockIndex;SInt8 cls;
 propagatedconstants=0;fn_00627080(0);
 for(cls=0;cls<5;cls++)constant_definitions[cls]=(ConstantInstruction **)aalloc(used_virtual_registers[cls]*4);
 do{
  constant_changed=0;
  for(blockIndex=0;blockIndex<constant_block_count;blockIndex++)if((block=constant_block_order[blockIndex])!=0){computedefininginstructions(block);propagateconstantstoblock(block);}
 }while(constant_changed);
 freeaheap();
}
void computedefininginstructions(ConstantBlock *block)
{
 SInt8 cls;SInt32 reg,index;ConstantInstruction *result;ConstantDefinitionLink *definition;
 for(cls=0;cls<5;cls++)for(reg=0;reg<used_virtual_registers[cls];reg++){
  result=0;
  for(definition=constant_definition_heads[cls][reg];definition;definition=definition->next){
   index=definition->index;
   if((constant_reaching_blocks[block->number].in[index>>5]>>(index&31))&1){
    if(result){result=0;break;}
    result=constant_definition_slots[index].instruction;
   }
  }
  constant_definitions[cls][reg]=result;
 }
}
ConstantInstruction *isstackoperand(ConstantOperand *operand,SInt16 *displacementOut,SInt16 addedDisplacement)
{
 ConstantInstruction *definition=constant_definitions[4][operand->reg];void *object;
 if(!definition || definition->opcode!=0x3f)return 0;
 if(definition->operands[2].kind==4 && (definition->operands[1].reg==stack_base_reg || definition->operands[1].reg==alternate_stack_base_reg)){
  object=*(void **)((char*)&definition->operands[2]+6);
  if(*(UInt8*)((char*)object+2)==1 && can_add_displ_to_local(object,addedDisplacement)){
   *displacementOut=*(SInt16*)((char*)&definition->operands[2]+2);return definition;
  }
 }
 return 0;
}
UInt32 issignedloadoperand(ConstantInstruction *instruction,SInt32 operandIndex,SInt32 depth)
{
 ConstantOperand *operand=&instruction->operands[operandIndex];SInt8 cls;SInt32 reg,classification,shift;
 ConstantDefinitionLink *link;ConstantInstruction *definition;UInt32 result=0,mask,value;
 if(operand->kind){CError_Internal(filename,578);return 0;}
 reg=operand->reg;cls=operand->cls;
 if(depth>4)return 4;
 if(reg<first_virtual[cls])return 0;
 for(link=constant_definition_heads[cls][reg];link;link=link->next){
  definition=constant_definition_slots[link->index].instruction;
  if(fn_00626f40(definition,link->index,reg,instruction,constant_reaching_blocks[instruction->block->number].in,cls)){
   if(definition==instruction)return 0;
   if(definition->flags&2){if(definition->opcode<0x1d || definition->opcode>0x20)return 0;classification=2;}
   else switch(definition->opcode){
    case 0x64:classification=1;break;
    case 0x65:classification=2;break;
    case 0x56:mask=*(UInt32*)((char*)&definition->operands[2]+2);if(mask&0xff80){if(mask&0x8000)return 0;classification=2;}else classification=1;break;
    case 0x67:
     if(*(SInt32*)((char*)&definition->operands[3]+2)==0x19 && *(SInt32*)((char*)&definition->operands[4]+2)>=0x19)classification=1;
     else if(*(SInt32*)((char*)&definition->operands[3]+2)==0x11 && *(SInt32*)((char*)&definition->operands[4]+2)>=0x11)classification=2;else return 0;break;
    case 0x58:case 0x5a:
     mask=*(UInt32*)((char*)&definition->operands[2]+2);
     if(definition->operands[0].reg==definition->operands[1].reg)return 0;
     classification=issignedloadoperand(definition,1,depth+1);
     if(classification==2 && !(mask&0x8000))classification=2;
     else if(classification==1 && !(mask&0xff80))classification=1;else return 0;break;
    case 0x89:value=*(UInt32*)((char*)&definition->operands[1]+2);classification=(SInt32)value==(SInt8)value?1:2;break;
    case 0x6c:
     shift=*(SInt32*)((char*)&definition->operands[2]+2);classification=issignedloadoperand(definition,1,depth+1)-shift/8;
     classification=classification<2?1:classification<3?2:4;break;
    default:return 0;
   }
   if(result<(UInt32)classification)result=classification;
  }
 }
 return result;
}
UInt32 isunsignedloadoperand(ConstantInstruction *instruction,SInt32 operandIndex)
{
 ConstantOperand *operand=&instruction->operands[operandIndex];SInt8 cls;SInt32 reg,classification;
 ConstantDefinitionLink *link;ConstantInstruction *definition;UInt32 result=0,mask,value;
 if(operand->kind){CError_Internal(filename,373);return 0;}
 reg=operand->reg;cls=operand->cls;
 if(reg<first_virtual[cls])return 0;
 for(link=constant_definition_heads[cls][reg];link;link=link->next){
  definition=constant_definition_slots[link->index].instruction;
  if(definition==instruction)return 0;
  if(fn_00626f40(definition,link->index,reg,instruction,constant_reaching_blocks[instruction->block->number].in,cls)){
   if(definition->flags&2){if(definition->opcode>=0x19 && definition->opcode<=0x1c)classification=2;else if(definition->opcode>=0x15 && definition->opcode<=0x18)classification=1;else return 0;}
   else switch(definition->opcode){
    case 0x67:
     if(*(SInt32*)((char*)&definition->operands[3]+2)==0x18 && *(SInt32*)((char*)&definition->operands[4]+2)>=0x18)classification=1;
     else if(*(SInt32*)((char*)&definition->operands[3]+2)==0x10 && *(SInt32*)((char*)&definition->operands[4]+2)>=0x10)classification=2;else return 0;break;
    case 0x56:classification=(*(UInt32*)((char*)&definition->operands[2]+2)&0xff00)?2:1;break;
    case 0x58:case 0x5a:
     mask=*(UInt32*)((char*)&definition->operands[2]+2);classification=isunsignedloadoperand(definition,1);
     if(classification==2)classification=2;else if(classification==1 && !(mask&0xff00))classification=1;else return 0;break;
    case 0x89:value=*(UInt32*)((char*)&definition->operands[1]+2);if(value&0x8000)return 0;classification=(value&0x7f00)?2:1;break;
    default:return 0;
   }
   if(result<(UInt32)classification)result=classification;
  }
 }
 return result;
}

void propagateconstantstoblock(ConstantBlock *block)

{
  SInt32 param_1;
  ushort uVar1;
  undefined4 *instructionWords;
  bool bVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  short sVar7;
  uint secondaryConstant;
  uint firstConstant;
  uint uVar8;
  uint uVar9;
  int iVar10;
  SInt8 *operandBytes;
  ConstantScratch constant_scratch;
  short local_26;
  uint local_24;
  uint local_20;
  uint local_1c;
  short local_18;
  short local_16;
  uint local_14;

  /* The native upper-half AND fallback at 0x623de8 reads BX even when no
     constant recognition assigned it. Preserve incoming EBX and its six later
     source assignments across instructions; an uninitialized C local does not
     reproduce this observed machine behavior. See the native register audit. */
  asm { mov secondaryConstant, ebx }
  param_1=(SInt32)block;
  constant_scratch.word=0;
  firstConstant=0;
  instructionWords = *(undefined4 **)(param_1 + 0x14);
  uVar9 = constant_scratch.word;
  do {
    if (instructionWords == (undefined4 *)0x0) {
      return;
    }
    uVar8 = instructionWords[4];
    if ((instructionWords[3] & 0x80) != 0) goto LAB_0062456d;
    sVar7 = *(short *)(instructionWords + 10);
    constant_scratch.word = uVar9;
    if (sVar7 == 0x15) {
LAB_00624420:
      if (*(char *)(instructionWords + 0x12) == '\x02') {
        sVar7 = *(short *)((int)instructionWords + 0x4a);
        iVar5 = (SInt32)isstackoperand((ConstantOperand*)((char*)instructionWords+0x3a), &constant_scratch.parts.value, (int)sVar7);
        uVar9 = constant_scratch.word;
        if (iVar5 != 0) {
          *(undefined4 *)((int)instructionWords + 0x3a) = *(undefined4 *)(iVar5 + 0x3a);
          *(undefined4 *)((int)instructionWords + 0x3e) = *(undefined4 *)(iVar5 + 0x3e);
          *(undefined4 *)((int)instructionWords + 0x42) = *(undefined4 *)(iVar5 + 0x42);
          *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(iVar5 + 0x46);
          instructionWords[0x12] = *(undefined4 *)(iVar5 + 0x48);
          instructionWords[0x13] = *(undefined4 *)(iVar5 + 0x4c);
          instructionWords[0x14] = *(undefined4 *)(iVar5 + 0x50);
          *(undefined2 *)(instructionWords + 0x15) = *(undefined2 *)(iVar5 + 0x54);
          *(int *)((int)instructionWords + 0x4a) = (int)sVar7 + (int)(short)(ushort)constant_scratch.word;
          if ((instructionWords[3] & 0x60006) != 0) {
            uVar6 = nbytes_loaded_or_stored_by(instructionWords);
            uVar6 = constant_alias(*(undefined4 *)((int)instructionWords + 0x4e),
                                 *(undefined4 *)((int)instructionWords + 0x4a), uVar6);
            instructionWords[7] = uVar6;
          }
          propagatedconstants = 1;
          constant_changed = 1;
          uVar9 = constant_scratch.word;
        }
      }
      goto LAB_0062456d;
    }
    constant_scratch.parts.maskBegin = (ushort)(uVar9 >> 0x10);
    uVar1 = constant_scratch.parts.maskBegin;
    if (sVar7 == 0x17) {
LAB_006244b4:
      iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
      if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) || (*(char *)(iVar5 + 0x3a) != '\x02'))
      {
        bVar3 = false;
      }
      else {
        constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
        bVar3 = true;
      }
      if (bVar3) {
        *(short *)(instructionWords + 10) = *(short *)(instructionWords + 10) - 2;
        *(undefined1 *)(instructionWords + 0x12) = 2;
        *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
        propagatedconstants = 1;
        constant_changed = 1;
        uVar9 = constant_scratch.word;
      }
      else {
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        uVar9 = constant_scratch.word;
        if (bVar3) {
          *(short *)(instructionWords + 10) = *(short *)(instructionWords + 10) - 2;
          *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
          *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
          *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
          *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
          *(undefined1 *)(instructionWords + 0x12) = 2;
          *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
          propagatedconstants = 1;
          constant_changed = 1;
        }
      }
      goto LAB_0062456d;
    }
    if (sVar7 == 0x19) goto LAB_00624420;
    if (sVar7 == 0x1b) goto LAB_006244b4;
    if (sVar7 == 0x1d) goto LAB_00624420;
    if (sVar7 == 0x1f) goto LAB_006244b4;
    if (sVar7 == 0x22) goto LAB_00624420;
    if (sVar7 == 0x24) goto LAB_006244b4;
    if (sVar7 == 0x28) goto LAB_00624420;
    if (sVar7 == 0x2a) goto LAB_006244b4;
    if (sVar7 == 0x2c) goto LAB_00624420;
    if (sVar7 == 0x2e) goto LAB_006244b4;
    if (sVar7 == 0x31) goto LAB_00624420;
    if (sVar7 == 0x33) goto LAB_006244b4;
    if (sVar7 == 0x3c) {
      if ((uVar8 & 0x100000) == 0) {
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if ((bVar3) && (*(short *)((int)instructionWords + 0x3e) != 0)) {
          if ((ushort)constant_scratch.word == 0) {
            change_opcode(instructionWords, 0x8b);
            change_num_operands(instructionWords, 2);
          }
          else {
            change_opcode(instructionWords, 0x3f);
            *(undefined1 *)(instructionWords + 0x12) = 2;
            *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
          }
          propagatedconstants = 1;
          constant_changed = 1;
          firstConstant = constant_scratch.word;
        }
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          if ((*(short *)(instructionWords + 10) == 0x3f) || (*(short *)(instructionWords + 10) == 0x8b)) {
            iVar5 = (int)(short)(ushort)constant_scratch.word + (int)(short)firstConstant;
            if (iVar5 == (short)iVar5) {
              change_opcode(instructionWords, 0x89);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = (int)(short)(ushort)constant_scratch.word + (int)(short)firstConstant;
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
            }
          }
          else if ((ushort)constant_scratch.word == 0) {
            *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
            *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
            *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
            *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
            change_opcode(instructionWords, 0x8b);
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
          }
          else if (*(short *)(instructionWords + 0x13) != 0) {
            *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
            *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
            *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
            *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
            change_opcode(instructionWords, 0x3f);
            *(undefined1 *)(instructionWords + 0x12) = 2;
            *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
            propagatedconstants = 1;
            constant_changed = 1;
          }
        }
        uVar9 = constant_scratch.word;
        if (constant_changed != 0) {
          if (*(short *)(instructionWords + 10) == 0x8b) {
            iVar5 = (SInt32)isstackoperand((ConstantOperand*)((char*)instructionWords+0x3a), &constant_scratch.parts.value, 0);
            uVar9 = constant_scratch.word;
            if (iVar5 != 0) {
              change_opcode(instructionWords, 0x3f);
              instructionWords[3] = *(undefined4 *)(iVar5 + 0xc);
              instructionWords[4] = *(undefined4 *)(iVar5 + 0x10);
              *(undefined4 *)((int)instructionWords + 0x3a) = *(undefined4 *)(iVar5 + 0x3a);
              *(undefined4 *)((int)instructionWords + 0x3e) = *(undefined4 *)(iVar5 + 0x3e);
              *(undefined4 *)((int)instructionWords + 0x42) = *(undefined4 *)(iVar5 + 0x42);
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(iVar5 + 0x46);
              instructionWords[0x12] = *(undefined4 *)(iVar5 + 0x48);
              instructionWords[0x13] = *(undefined4 *)(iVar5 + 0x4c);
              instructionWords[0x14] = *(undefined4 *)(iVar5 + 0x50);
              *(undefined2 *)(instructionWords + 0x15) = *(undefined2 *)(iVar5 + 0x54);
              change_num_operands(instructionWords, 3);
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
          }
          else if ((*(short *)(instructionWords + 10) == 0x3f) && (*(char *)(instructionWords + 0x12) == '\x02')) {
            local_1c = (uint)*(ushort *)((int)instructionWords + 0x4a);
            iVar5 = (SInt32)isstackoperand((ConstantOperand*)((char*)instructionWords+0x3a), &constant_scratch.parts.value,
                                 (int)(short)*(ushort *)((int)instructionWords + 0x4a));
            uVar9 = constant_scratch.word;
            if (iVar5 != 0) {
              change_opcode(instructionWords, 0x3f);
              instructionWords[3] = *(undefined4 *)(iVar5 + 0xc);
              instructionWords[4] = *(undefined4 *)(iVar5 + 0x10);
              *(undefined4 *)((int)instructionWords + 0x3a) = *(undefined4 *)(iVar5 + 0x3a);
              *(undefined4 *)((int)instructionWords + 0x3e) = *(undefined4 *)(iVar5 + 0x3e);
              *(undefined4 *)((int)instructionWords + 0x42) = *(undefined4 *)(iVar5 + 0x42);
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(iVar5 + 0x46);
              instructionWords[0x12] = *(undefined4 *)(iVar5 + 0x48);
              instructionWords[0x13] = *(undefined4 *)(iVar5 + 0x4c);
              instructionWords[0x14] = *(undefined4 *)(iVar5 + 0x50);
              *(undefined2 *)(instructionWords + 0x15) = *(undefined2 *)(iVar5 + 0x54);
              *(int *)((int)instructionWords + 0x4a) = (int)(short)local_1c + (int)(short)(ushort)constant_scratch.word;
              if ((instructionWords[3] & 0x60006) != 0) {
                uVar6 = constant_alias(*(undefined4 *)((int)instructionWords + 0x4e),
                                     *(undefined4 *)((int)instructionWords + 0x4a), 1);
                instructionWords[7] = uVar6;
              }
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
          }
        }
      }
    }
    else if (sVar7 == 0x3f) {
      if (((uVar8 & 0x100000) == 0) && ((*(ushort *)(instructionWords + 0xf) & 1) != 0) &&
         (*(char *)(instructionWords + 0x12) == '\x02')) {
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        uVar1 = *(ushort *)((int)instructionWords + 0x4a);
        firstConstant = (uint)uVar1;
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          iVar5 = (int)(short)(ushort)constant_scratch.word + (int)(short)uVar1;
          if (iVar5 == (short)iVar5) {
            change_opcode(instructionWords, 0x89);
            *(undefined1 *)((int)instructionWords + 0x3a) = 2;
            instructionWords[0xf] = (int)(short)(ushort)constant_scratch.word + (int)(short)uVar1;
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
            goto LAB_0062456d;
          }
        }
        uVar9 = constant_scratch.word;
        if (uVar1 == 0) {
          change_opcode(instructionWords, 0x8b);
          change_num_operands(instructionWords, 2);
          propagatedconstants = 1;
          constant_changed = 1;
          uVar9 = constant_scratch.word;
        }
      }
    }
    else if (sVar7 == 0x4c) {
      if ((uVar8 & 0x100000) != 0) goto LAB_0062456d;
      iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
      if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) || (*(char *)(iVar5 + 0x3a) != '\x02'))
      {
        bVar3 = false;
      }
      else {
        constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
        bVar3 = true;
      }
      if (bVar3) {
        if (-(int)(short)-(ushort)constant_scratch.word == (int)(short)(ushort)constant_scratch.word) {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
             (*(char *)(iVar5 + 0x3a) != '\x02')) {
            bVar3 = false;
          }
          else {
            local_20 = (uint)*(ushort *)(iVar5 + 0x3c);
            bVar3 = true;
          }
          if (bVar3) {
            iVar10 = (int)(short)local_20;
            iVar5 = iVar10 - (short)(ushort)constant_scratch.word;
            if (iVar5 != (short)iVar5) goto LAB_00624301;
            change_opcode(instructionWords, 0x89);
            *(undefined1 *)((int)instructionWords + 0x3a) = 2;
            instructionWords[0xf] = iVar10 - (short)(ushort)constant_scratch.word;
            change_num_operands(instructionWords, 2);
          }
          else {
LAB_00624301:
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x8b);
              *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
              *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
              *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
              change_num_operands(instructionWords, 2);
            }
            else {
              change_opcode(instructionWords, 0x3f);
              *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
              *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
              *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = -(int)(short)(ushort)constant_scratch.word;
            }
          }
          propagatedconstants = 1;
          constant_changed = 1;
          local_20 = constant_scratch.word;
          uVar9 = constant_scratch.word;
          goto LAB_0062456d;
        }
      }
      iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
      if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) || (*(char *)(iVar5 + 0x3a) != '\x02'))
      {
        bVar3 = false;
      }
      else {
        constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
        bVar3 = true;
      }
      uVar9 = constant_scratch.word;
      if ((bVar3) && (-(int)(short)-(ushort)constant_scratch.word == (int)(short)(ushort)constant_scratch.word)) {
        if ((ushort)constant_scratch.word == 0) {
          change_opcode(instructionWords, 0x4b);
          change_num_operands(instructionWords, 2);
        }
        else {
          change_opcode(instructionWords, 0x4f);
          *(undefined1 *)(instructionWords + 0x12) = 2;
          *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
          *(undefined1 *)((int)instructionWords + 0x56) = 0;
          *(undefined1 *)((int)instructionWords + 0x57) = 0;
          *(undefined2 *)((int)instructionWords + 0x5a) = 0;
          *(undefined2 *)(instructionWords + 0x16) = 2;
          change_num_operands(instructionWords, 4);
        }
        propagatedconstants = 1;
        constant_changed = 1;
        uVar9 = constant_scratch.word;
      }
    }
    else if (sVar7 == 0x5c) {
      if ((uVar8 & 0x100000) == 0) {
        constant_scratch.word = (uint)constant_scratch.parts.maskBegin << 0x10;
        firstConstant = constant_scratch.word;
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(uVar1, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
             (*(char *)(iVar5 + 0x3a) != '\x02' ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff)))) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
            secondaryConstant = uVar9;
          }
          if (bVar3) {
            sVar7 = (short)secondaryConstant;
            if (sVar7 == 0) {
              change_opcode(instructionWords, 0x89);
              change_num_operands(instructionWords, 2);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = 0;
            }
            else {
              iVar5 = InstrSelection_GetMaskRange((int)sVar7, &constant_scratch.parts.maskBegin, &local_26);
              if (iVar5 != 0) {
                change_opcode(instructionWords, 0x67);
                change_num_operands(instructionWords, 5);
                *(undefined1 *)(instructionWords + 0x12) = 2;
                *(undefined4 *)((int)instructionWords + 0x4a) = 0;
                *(undefined1 *)((int)instructionWords + 0x56) = 2;
                instructionWords[0x16] = (int)(short)constant_scratch.parts.maskBegin;
                *(undefined1 *)(instructionWords + 0x19) = 2;
                *(int *)((int)instructionWords + 0x66) = (int)local_26;
                propagatedconstants = 1;
                constant_changed = 1;
                uVar9 = constant_scratch.word;
                goto LAB_0062456d;
              }
              change_opcode(instructionWords, 0x56);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = (int)sVar7;
              change_num_operands(instructionWords, 4);
              *(undefined1 *)((int)instructionWords + 0x56) = 0;
              *(undefined1 *)((int)instructionWords + 0x57) = 1;
              *(undefined2 *)((int)instructionWords + 0x5a) = 0;
              *(undefined2 *)(instructionWords + 0x16) = 2;
              pcsetrecordbit(instructionWords);
            }
            constant_changed = 1;
            propagatedconstants = 1;
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, sVar7);
            firstConstant = constant_scratch.word;
          }
          else {
            firstConstant = constant_scratch.word;
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x89);
              change_num_operands(instructionWords, 2);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = 0;
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
          }
        }
        else {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x8a) ||
             (*(char *)(iVar5 + 0x3a) != '\x02' ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff)))) {
            bVar3 = false;
          }
          else {
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, (short)uVar9);
            bVar3 = true;
          }
          if (bVar3) {
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x89);
              change_num_operands(instructionWords, 2);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = 0;
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
            else {
              iVar5 = InstrSelection_GetMaskRange((int)(short)(ushort)constant_scratch.word << 0x10, &local_18, &local_16);
              if (iVar5 != 0) {
                change_opcode(instructionWords, 0x67);
                change_num_operands(instructionWords, 5);
                *(undefined1 *)(instructionWords + 0x12) = 2;
                *(undefined4 *)((int)instructionWords + 0x4a) = 0;
                *(undefined1 *)((int)instructionWords + 0x56) = 2;
                instructionWords[0x16] = (int)local_18;
                *(undefined1 *)(instructionWords + 0x19) = 2;
                *(int *)((int)instructionWords + 0x66) = (int)local_16;
                propagatedconstants = 1;
                constant_changed = 1;
                uVar9 = constant_scratch.word;
                goto LAB_0062456d;
              }
              change_opcode(instructionWords, 0x57);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
              change_num_operands(instructionWords, 4);
              *(undefined1 *)((int)instructionWords + 0x56) = 0;
              *(undefined1 *)((int)instructionWords + 0x57) = 1;
              *(undefined2 *)((int)instructionWords + 0x5a) = 0;
              *(undefined2 *)(instructionWords + 0x16) = 2;
              pcsetrecordbit(instructionWords);
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
          }
        }
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
             (*(char *)(iVar5 + 0x3a) != '\x02') ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff))) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
            secondaryConstant = uVar9;
          }
          if (bVar3) {
            if (*(short *)(instructionWords + 10) == 0x56) {
              fn_00596280(instructionWords);
              change_opcode(instructionWords, 0x89);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = (int)(short)((ushort)constant_scratch.word & (ushort)firstConstant);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
            else if (*(short *)(instructionWords + 10) == 0x57) {
              fn_00596280(instructionWords);
              change_opcode(instructionWords, 0x89);
              change_num_operands(instructionWords, 2);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = 0;
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
            else {
              sVar7 = (short)secondaryConstant;
              if (sVar7 == 0) {
                change_opcode(instructionWords, 0x89);
                *(undefined1 *)((int)instructionWords + 0x3a) = 2;
                instructionWords[0xf] = 0;
                change_num_operands(instructionWords, 2);
                propagatedconstants = 1;
                constant_changed = 1;
                uVar9 = constant_scratch.word;
              }
              else {
                iVar5 = InstrSelection_GetMaskRange((int)sVar7, &local_18, &local_16);
                if (iVar5 == 0) {
                  change_opcode(instructionWords, 0x56);
                  *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                  *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                  *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                  *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                  *(undefined1 *)(instructionWords + 0x12) = 2;
                  *(int *)((int)instructionWords + 0x4a) = (int)sVar7;
                  change_num_operands(instructionWords, 4);
                  *(undefined1 *)((int)instructionWords + 0x56) = 0;
                  *(undefined1 *)((int)instructionWords + 0x57) = 1;
                  *(undefined2 *)((int)instructionWords + 0x5a) = 0;
                  *(undefined2 *)(instructionWords + 0x16) = 2;
                  pcsetrecordbit(instructionWords);
                  propagatedconstants = 1;
                  constant_changed = 1;
                  uVar9 = constant_scratch.word;
                }
                else {
                  change_opcode(instructionWords, 0x67);
                  change_num_operands(instructionWords, 5);
                  *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                  *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                  *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                  *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                  *(undefined1 *)(instructionWords + 0x12) = 2;
                  *(undefined4 *)((int)instructionWords + 0x4a) = 0;
                  *(undefined1 *)((int)instructionWords + 0x56) = 2;
                  instructionWords[0x16] = (int)local_18;
                  *(undefined1 *)(instructionWords + 0x19) = 2;
                  *(int *)((int)instructionWords + 0x66) = (int)local_16;
                  propagatedconstants = 1;
                  constant_changed = 1;
                  uVar9 = constant_scratch.word;
                }
              }
            }
          }
          else {
            uVar9 = constant_scratch.word;
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x89);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = 0;
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
          }
        }
        else {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x8a) ||
             (*(char *)(iVar5 + 0x3a) != '\x02' ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff)))) {
            bVar3 = false;
          }
          else {
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, (short)uVar9);
            bVar3 = true;
          }
          uVar9 = constant_scratch.word;
          if (bVar3) {
            if (((ushort)constant_scratch.word == 0) || (*(short *)(instructionWords + 10) == 0x56)) {
              if (*(short *)(instructionWords + 10) == 0x56) {
                fn_00596280(instructionWords);
              }
              change_opcode(instructionWords, 0x89);
              *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
              *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
              *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
            else if (*(short *)(instructionWords + 10) == 0x57) {
              fn_00596280(instructionWords);
              change_opcode(instructionWords, 0x8a);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = (int)(short)((ushort)constant_scratch.word & (ushort)firstConstant);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
            else {
              iVar5 = InstrSelection_GetMaskRange((int)(short)(ushort)constant_scratch.word << 0x10, &local_18, &local_16);
              if (iVar5 == 0) {
                change_opcode(instructionWords, 0x57);
                *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                *(undefined1 *)(instructionWords + 0x12) = 2;
                *(int *)((int)instructionWords + 0x4a) = (int)(short)secondaryConstant;
                change_num_operands(instructionWords, 4);
                *(undefined1 *)((int)instructionWords + 0x56) = 0;
                *(undefined1 *)((int)instructionWords + 0x57) = 1;
                *(undefined2 *)((int)instructionWords + 0x5a) = 0;
                *(undefined2 *)(instructionWords + 0x16) = 2;
                pcsetrecordbit(instructionWords);
                propagatedconstants = 1;
                constant_changed = 1;
                uVar9 = constant_scratch.word;
              }
              else {
                change_opcode(instructionWords, 0x67);
                change_num_operands(instructionWords, 5);
                *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                *(undefined1 *)(instructionWords + 0x12) = 2;
                *(undefined4 *)((int)instructionWords + 0x4a) = 0;
                *(undefined1 *)((int)instructionWords + 0x56) = 2;
                instructionWords[0x16] = (int)local_18;
                *(undefined1 *)(instructionWords + 0x19) = 2;
                *(int *)((int)instructionWords + 0x66) = (int)local_16;
                propagatedconstants = 1;
                constant_changed = 1;
                uVar9 = constant_scratch.word;
              }
            }
          }
        }
      }
    }
    else if (sVar7 == 0x5d) {
      if ((uVar8 & 0x100000) == 0) {
        constant_scratch.word = (uint)constant_scratch.parts.maskBegin << 0x10;
        firstConstant = constant_scratch.word;
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(uVar1, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
             (*(char *)(iVar5 + 0x3a) != '\x02') ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff))) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
            secondaryConstant = uVar9;
          }
          if (bVar3) {
            sVar7 = (short)secondaryConstant;
            if (sVar7 == 0) {
              change_opcode(instructionWords, 0x8b);
              change_num_operands(instructionWords, 2);
            }
            else {
              change_opcode(instructionWords, 0x58);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = (int)sVar7;
            }
            constant_changed = 1;
            propagatedconstants = 1;
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, sVar7);
            firstConstant = constant_scratch.word;
          }
          else {
            firstConstant = constant_scratch.word;
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x8b);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
          }
        }
        else {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x8a) ||
             (*(char *)(iVar5 + 0x3a) != '\x02' ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff)))) {
            bVar3 = false;
          }
          else {
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, (short)uVar9);
            bVar3 = true;
          }
          if (bVar3) {
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x8b);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
            else {
              change_opcode(instructionWords, 0x59);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
          }
        }
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          sVar7 = *(short *)(instructionWords + 10);
          if ((sVar7 == 0x58) || (sVar7 == 0x8b)) {
            change_opcode(instructionWords, 0x89);
            *(undefined1 *)((int)instructionWords + 0x3a) = 2;
            instructionWords[0xf] = (int)(short)((ushort)constant_scratch.word | (ushort)firstConstant);
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
          }
          else {
            uVar9 = constant_scratch.word;
            if (sVar7 != 0x59) {
              iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
              if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
                 (*(char *)(iVar5 + 0x3a) != '\x02') ||
                 (uVar8 = *(uint *)(iVar5 + 0x3c), uVar8 != (uVar8 & 0xffff))) {
                bVar3 = false;
              }
              else {
                bVar3 = true;
                secondaryConstant = uVar8;
              }
              if (bVar3) {
                if ((short)secondaryConstant == 0) {
                  change_opcode(instructionWords, 0x8b);
                  *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                  *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                  *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                  *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                  change_num_operands(instructionWords, 2);
                  propagatedconstants = 1;
                  constant_changed = 1;
                  uVar9 = constant_scratch.word;
                }
                else {
                  change_opcode(instructionWords, 0x58);
                  *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                  *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                  *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                  *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                  *(undefined1 *)(instructionWords + 0x12) = 2;
                  *(int *)((int)instructionWords + 0x4a) = (int)(short)secondaryConstant;
                  propagatedconstants = 1;
                  constant_changed = 1;
                  uVar9 = constant_scratch.word;
                }
              }
              else if ((ushort)constant_scratch.word == 0) {
                change_opcode(instructionWords, 0x8b);
                *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                change_num_operands(instructionWords, 2);
                propagatedconstants = 1;
                constant_changed = 1;
                uVar9 = constant_scratch.word;
              }
            }
          }
        }
        else {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x8a) ||
             (*(char *)(iVar5 + 0x3a) != '\x02' ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff)))) {
            bVar3 = false;
          }
          else {
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, (short)uVar9);
            bVar3 = true;
          }
          uVar9 = constant_scratch.word;
          if (bVar3) {
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x8b);
              *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
              *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
              *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
            else {
              change_opcode(instructionWords, 0x59);
              *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
              *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
              *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
          }
        }
      }
    }
    else if (sVar7 == 0x5e) {
      if ((uVar8 & 0x100000) == 0) {
        constant_scratch.word = (uint)constant_scratch.parts.maskBegin << 0x10;
        firstConstant = constant_scratch.word;
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(uVar1, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
             (*(char *)(iVar5 + 0x3a) != '\x02') ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff))) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
            secondaryConstant = uVar9;
          }
          if (bVar3) {
            sVar7 = (short)secondaryConstant;
            if (sVar7 == 0) {
              change_opcode(instructionWords, 0x8b);
              change_num_operands(instructionWords, 2);
            }
            else {
              change_opcode(instructionWords, 0x5a);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = (int)sVar7;
            }
            constant_changed = 1;
            propagatedconstants = 1;
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, sVar7);
            firstConstant = constant_scratch.word;
          }
          else {
            firstConstant = constant_scratch.word;
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x8b);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
          }
        }
        else {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)(instructionWords + 0x13) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x8a) ||
             (*(char *)(iVar5 + 0x3a) != '\x02' ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff)))) {
            bVar3 = false;
          }
          else {
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, (short)uVar9);
            bVar3 = true;
          }
          if (bVar3) {
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x8b);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
            else {
              change_opcode(instructionWords, 0x5b);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
              propagatedconstants = 1;
              constant_changed = 1;
              firstConstant = constant_scratch.word;
            }
          }
        }
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          sVar7 = *(short *)(instructionWords + 10);
          if ((sVar7 == 0x5a) || (sVar7 == 0x8b)) {
            change_opcode(instructionWords, 0x89);
            *(undefined1 *)((int)instructionWords + 0x3a) = 2;
            instructionWords[0xf] = (int)(short)((ushort)constant_scratch.word ^ (ushort)firstConstant);
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
          }
          else {
            uVar9 = constant_scratch.word;
            if (sVar7 != 0x5b) {
              iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
              if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
                 (*(char *)(iVar5 + 0x3a) != '\x02') ||
                 (uVar8 = *(uint *)(iVar5 + 0x3c), uVar8 != (uVar8 & 0xffff))) {
                bVar3 = false;
              }
              else {
                bVar3 = true;
                secondaryConstant = uVar8;
              }
              if (bVar3) {
                if ((short)secondaryConstant == 0) {
                  change_opcode(instructionWords, 0x8b);
                  *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                  *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                  *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                  *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                  change_num_operands(instructionWords, 2);
                  propagatedconstants = 1;
                  constant_changed = 1;
                  uVar9 = constant_scratch.word;
                }
                else {
                  change_opcode(instructionWords, 0x5a);
                  *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                  *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                  *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                  *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                  *(undefined1 *)(instructionWords + 0x12) = 2;
                  *(int *)((int)instructionWords + 0x4a) = (int)(short)secondaryConstant;
                  propagatedconstants = 1;
                  constant_changed = 1;
                  uVar9 = constant_scratch.word;
                }
              }
              else if ((ushort)constant_scratch.word == 0) {
                change_opcode(instructionWords, 0x8b);
                *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
                *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
                *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
                *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
                change_num_operands(instructionWords, 2);
                propagatedconstants = 1;
                constant_changed = 1;
                uVar9 = constant_scratch.word;
              }
            }
          }
        }
        else {
          iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
          if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x8a) ||
             (*(char *)(iVar5 + 0x3a) != '\x02' ||
             (uVar9 = *(uint *)(iVar5 + 0x3c), uVar9 != (uVar9 & 0xffff)))) {
            bVar3 = false;
          }
          else {
            constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, (short)uVar9);
            bVar3 = true;
          }
          uVar9 = constant_scratch.word;
          if (bVar3) {
            if ((*(short *)(instructionWords + 10) == 0x5b) || (*(short *)(instructionWords + 10) == 0x8b)) {
              change_opcode(instructionWords, 0x8a);
              *(undefined1 *)((int)instructionWords + 0x3a) = 2;
              instructionWords[0xf] = (int)(short)((ushort)constant_scratch.word ^ (ushort)firstConstant);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
            }
            if ((ushort)constant_scratch.word == 0) {
              change_opcode(instructionWords, 0x8b);
              *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
              *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
              *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
              change_num_operands(instructionWords, 2);
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
            else {
              change_opcode(instructionWords, 0x5b);
              *(undefined4 *)((int)instructionWords + 0x3a) = instructionWords[0x12];
              *(undefined4 *)((int)instructionWords + 0x3e) = instructionWords[0x13];
              *(undefined4 *)((int)instructionWords + 0x42) = instructionWords[0x14];
              *(undefined2 *)((int)instructionWords + 0x46) = *(undefined2 *)(instructionWords + 0x15);
              *(undefined1 *)(instructionWords + 0x12) = 2;
              *(int *)((int)instructionWords + 0x4a) = (int)(short)(ushort)constant_scratch.word;
              propagatedconstants = 1;
              constant_changed = 1;
              uVar9 = constant_scratch.word;
            }
          }
        }
      }
    }
    else if (sVar7 == 100) {
      if ((uVar8 & 0x100000) == 0) {
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          change_opcode(instructionWords, 0x89);
          *(undefined1 *)((int)instructionWords + 0x3a) = 2;
          instructionWords[0xf] = (int)(char)constant_scratch.word;
          change_num_operands(instructionWords, 2);
          propagatedconstants = 1;
          constant_changed = 1;
          uVar9 = constant_scratch.word;
        }
        else {
          iVar5 = issignedloadoperand((ConstantInstruction*)instructionWords, 1, 0);
          uVar9 = constant_scratch.word;
          if (iVar5 == 1) {
            change_opcode(instructionWords, 0x8b);
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
          }
        }
      }
    }
    else if (sVar7 == 0x65) {
      if ((uVar8 & 0x100000) == 0) {
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        if (bVar3) {
          change_opcode(instructionWords, 0x89);
          *(undefined1 *)((int)instructionWords + 0x3a) = 2;
          instructionWords[0xf] = (int)(short)(ushort)constant_scratch.word;
          change_num_operands(instructionWords, 2);
          propagatedconstants = 1;
          constant_changed = 1;
          uVar9 = constant_scratch.word;
        }
        else {
          iVar5 = issignedloadoperand((ConstantInstruction*)instructionWords, 1, 0);
          uVar9 = constant_scratch.word;
          if (iVar5 - 1U < 2) {
            change_opcode(instructionWords, 0x8b);
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
          }
        }
      }
    }
    else if (sVar7 == 0x67) {
      if ((uVar8 & 0x100000) == 0) {
        iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          bVar3 = true;
        }
        uVar9 = constant_scratch.word;
        if (bVar3) {
          iVar5 = *(int *)((int)instructionWords + 0x66);
          iVar10 = instructionWords[0x16];
          if (iVar5 < iVar10) {
            if (iVar5 + 1 < 0x20) {
              uVar8 = 0xffffffff >> ((byte)(iVar5 + 1) & 0x1f);
            }
            else {
              uVar8 = 0;
            }
            if (iVar10 < 0x20) {
              uVar4 = 0xffffffff >> ((byte)iVar10 & 0x1f);
            }
            else {
              uVar4 = 0;
            }
            uVar4 = ~uVar8 | uVar4;
          }
          else {
            if (iVar5 + 1 < 0x20) {
              uVar8 = 0xffffffff >> ((byte)(iVar5 + 1) & 0x1f);
            }
            else {
              uVar8 = 0;
            }
            if (iVar10 < 0x20) {
              uVar4 = 0xffffffff >> ((byte)iVar10 & 0x1f);
            }
            else {
              uVar4 = 0;
            }
            uVar4 = ~uVar8 & uVar4;
          }
          local_1c = *(uint *)((int)instructionWords + 0x4a);
          uVar4 = ((uint)(int)(short)(ushort)constant_scratch.word >> (0x20 - (byte)local_1c & 0x1f) |
                  (int)(short)(ushort)constant_scratch.word << ((byte)local_1c & 0x1f)) & uVar4;
          if (uVar4 == (int)(short)uVar4) {
            change_opcode(instructionWords, 0x89);
            *(undefined1 *)((int)instructionWords + 0x3a) = 2;
            instructionWords[0xf] = uVar4;
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
          }
          else if ((uVar4 & 0xffff) == 0) {
            change_opcode(instructionWords, 0x8a);
            *(undefined1 *)((int)instructionWords + 0x3a) = 2;
            instructionWords[0xf] = (int)(short)(uVar4 >> 0x10);
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
          }
        }
        else if ((*(int *)((int)instructionWords + 0x4a) == 0) && (*(int *)((int)instructionWords + 0x66) == 0x1f)) {
          iVar5 = isunsignedloadoperand((ConstantInstruction*)instructionWords, 1);
          if (((iVar5 == 2) && ((int)instructionWords[0x16] < 0x11)) ||
             (iVar5 == 1 && ((int)instructionWords[0x16] < 0x19))) {
            change_opcode(instructionWords, 0x8b);
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
          }
          else {
            iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
            if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x67)) {
              bVar3 = false;
            }
            else {
              iVar10 = *(int *)(iVar5 + 0x66);
              iVar5 = *(int *)(iVar5 + 0x58);
              if (iVar10 < iVar5) {
                if (iVar10 + 1 < 0x20) {
                  uVar9 = 0xffffffff >> ((byte)(iVar10 + 1) & 0x1f);
                }
                else {
                  uVar9 = 0;
                }
                if (iVar5 < 0x20) {
                  local_14 = 0xffffffff >> ((byte)iVar5 & 0x1f);
                }
                else {
                  local_14 = 0;
                }
                local_14 = ~uVar9 | local_14;
              }
              else {
                if (iVar10 + 1 < 0x20) {
                  uVar9 = 0xffffffff >> ((byte)(iVar10 + 1) & 0x1f);
                }
                else {
                  uVar9 = 0;
                }
                if (iVar5 < 0x20) {
                  local_14 = 0xffffffff >> ((byte)iVar5 & 0x1f);
                }
                else {
                  local_14 = 0;
                }
                local_14 = ~uVar9 & local_14;
              }
              bVar3 = true;
            }
            uVar9 = constant_scratch.word;
            if (bVar3) {
              iVar5 = *(int *)((int)instructionWords + 0x66);
              iVar10 = instructionWords[0x16];
              if (iVar5 < iVar10) {
                if (iVar5 + 1 < 0x20) {
                  uVar8 = 0xffffffff >> ((byte)(iVar5 + 1) & 0x1f);
                }
                else {
                  uVar8 = 0;
                }
                if (iVar10 < 0x20) {
                  uVar4 = 0xffffffff >> ((byte)iVar10 & 0x1f);
                }
                else {
                  uVar4 = 0;
                }
                uVar4 = ~uVar8 | uVar4;
              }
              else {
                if (iVar5 + 1 < 0x20) {
                  uVar8 = 0xffffffff >> ((byte)(iVar5 + 1) & 0x1f);
                }
                else {
                  uVar8 = 0;
                }
                if (iVar10 < 0x20) {
                  uVar4 = 0xffffffff >> ((byte)iVar10 & 0x1f);
                }
                else {
                  uVar4 = 0;
                }
                uVar4 = ~uVar8 & uVar4;
              }
              if (local_14 == (local_14 & uVar4)) {
                change_opcode(instructionWords, 0x8b);
                change_num_operands(instructionWords, 2);
                propagatedconstants = 1;
                constant_changed = 1;
                uVar9 = constant_scratch.word;
              }
            }
          }
        }
      }
    }
    else if (sVar7 == 0x8b) {
      iVar5 = *(int *)(((UInt32)constant_definitions[4]) + *(short *)((int)instructionWords + 0x3e) * 4);
      if ((iVar5 == 0) || (*(short *)(iVar5 + 0x28) != 0x89) || (*(char *)(iVar5 + 0x3a) != '\x02'))
      {
        bVar3 = false;
      }
      else {
        constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
        bVar3 = true;
      }
      uVar9 = constant_scratch.word;
      if (bVar3) {
        change_opcode(instructionWords, 0x89);
        *(undefined1 *)((int)instructionWords + 0x3a) = 2;
        instructionWords[0xf] = (int)(short)(ushort)constant_scratch.word;
        propagatedconstants = 1;
        constant_changed = 1;
        uVar9 = constant_scratch.word;
      }
    }
    else {
      if (sVar7 == 0x8e) goto LAB_00624420;
      if (sVar7 == 0x90) goto LAB_006244b4;
      if (sVar7 == 0x92) goto LAB_00624420;
      if (sVar7 == 0x94) goto LAB_006244b4;
      if (sVar7 == 0x96) goto LAB_00624420;
      if (sVar7 == 0x98) goto LAB_006244b4;
      if (sVar7 == 0x9a) goto LAB_00624420;
      if (sVar7 == 0x9c) goto LAB_006244b4;
      if (sVar7 == 0xb5) {
        if ((uVar8 & 0x100000) == 0) {
          iVar5 = *(int *)(((UInt32)constant_definitions[3]) + *(short *)((int)instructionWords + 0x3e) * 4);
          if (iVar5 == 0) {
switchD_0062314a_caseD_92:
            bVar3 = false;
          }
          else {
            switch(*(undefined2 *)(iVar5 + 0x28)) {
            case 0x8e:
            case 0x8f:
            case 0x90:
            case 0x91:
            case 0xa3:
            case 0xa5:
            case 0xa7:
            case 0xa9:
            case 0xab:
            case 0xad:
            case 0xaf:
            case 0xb1:
            case 0xb5:
            case 0xd1:
              bVar3 = true;
              break;
            default:
              goto switchD_0062314a_caseD_92;
            }
          }
          if (bVar3) {
            change_opcode(instructionWords, 0x9e);
            change_num_operands(instructionWords, 2);
            propagatedconstants = 1;
            constant_changed = 1;
            uVar9 = constant_scratch.word;
          }
        }
      }
      else if (sVar7 == 400) {
        iVar5 = *(int *)(((UInt32)constant_definitions[2]) + *(short *)((int)instructionWords + 0x3e) * 4);
        if ((iVar5 == 0) || ((ushort)(*(short *)(iVar5 + 0x28) - 0x160U) > 2) ||
           (*(char *)(iVar5 + 0x3a) != '\x02')) {
          bVar3 = false;
        }
        else {
          constant_scratch.word = CONCAT22(constant_scratch.parts.maskBegin, *(undefined2 *)(iVar5 + 0x3c));
          local_24 = (uint)*(ushort *)(iVar5 + 0x28);
          bVar3 = true;
        }
        uVar9 = constant_scratch.word;
        if (bVar3) {
          change_opcode(instructionWords, (int)(short)local_24);
          *(undefined1 *)((int)instructionWords + 0x3a) = 2;
          instructionWords[0xf] = (int)(short)(ushort)constant_scratch.word;
          propagatedconstants = 1;
          constant_changed = 1;
          uVar9 = constant_scratch.word;
        }
      }
    }
LAB_0062456d:
    constant_scratch.word = uVar9;
    operandBytes = (SInt8 *)(instructionWords + 0xb);
    if (*(short *)((int)instructionWords + 0x2a) > 0) {
      iVar5 = 0;
      do {
        if ((*operandBytes == '\0') && ((*(ushort *)(operandBytes + 2) & 2) != 0)) {
          *(undefined4 **)(*(int *)((char *)constant_definitions + operandBytes[1] * 4) + *(short *)(operandBytes + 4) * 4) =
               instructionWords;
        }
        iVar5 = iVar5 + 1;
        operandBytes = operandBytes + 0xe;
      } while (iVar5 < *(short *)((int)instructionWords + 0x2a));
    }
    instructionWords = (undefined4 *)*instructionWords;
    uVar9 = constant_scratch.word;
  } while( true );
}
