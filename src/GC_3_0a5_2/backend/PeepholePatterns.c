/* PeepholePatterns.c supported native family port. */
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char bool;
#define true 1
#define false 0

/* GC 3.0 embeds reaching definitions in its 14-byte operands. The 1.2.5
 * parallel reaching-definition table must not be reused with this layout. */
#pragma pack(push, 2)
typedef struct PeepholeInstruction PeepholeInstruction;
typedef struct PeepholeOperand {
    unsigned char kind, registerClass;
    union {
        struct { unsigned short flags; short number;
                 PeepholeInstruction *definition; unsigned int tail; } reg;
        struct { int value; void *object; unsigned int tail; } immediate;
    } payload;
} PeepholeOperand;
struct PeepholeInstruction {
    PeepholeInstruction *next, *previous;
    void *block;
    unsigned int flags, recordFlags;
    unsigned char unknown14[20];
    short opcode, operandCount;
    PeepholeOperand operands[6];
};
typedef struct PeepholeRegisterReference {
    unsigned char kind, registerClass;
    unsigned short flags;
    short number;
} PeepholeRegisterReference;
#pragma pack(pop)
typedef char PeepholeOperandSizeCheck[sizeof(PeepholeOperand)==14 ? 1 : -1];
typedef char PeepholeRegisterReferenceSizeCheck[sizeof(PeepholeRegisterReference)==6 ? 1 : -1];

static char peepholeFilename[] = "PeepholePatterns.c";
extern unsigned int native_context_word;
extern int native_extended_mode;
extern unsigned int native_liveness_bank0;
extern unsigned int native_liveness_mask0;
extern unsigned int native_liveness_bank2;
extern unsigned int native_liveness_bank3;
extern unsigned int native_liveness_bank4;
extern unsigned char native_target_flag;
extern void CError_Internal(const char *, int);
extern unsigned char fn_004c3f60(int);
extern int InstrSelection_GetMaskRange(int, int, int);
extern void fn_00582100(int, int);
extern void insertpcodeafter(int, int);
extern void deletepcode(int);
extern PeepholeInstruction *makepcode(short, ...);
extern int local_offset_32(int);
extern unsigned int fn_0058aec0(int);
extern int is_valid_displ(int, int, int);
extern void change_opcode(int, short);
extern void change_num_operands(int, int);
extern int nbytes_loaded_or_stored_by(int);
extern int fn_005960b0(int);
extern void pcsetrecordbit(int);
extern void fn_00596280(int);
extern void AddPeepholeRule(short, int);
extern int fn_00596b50(int, int, int);
extern int fn_00596bd0(int, int, int);
extern int fn_005994f0(int);
extern void *fn_005a05d0(int, int, int);
void register_peephole_rules(void);
uint fn_00632ea0(int param_1, short param_2);
undefined4 fn_00633240(int param_1);
undefined4 fn_00633380(int param_1);
undefined4 fn_00633600(int param_1);
undefined4 fn_006339b0(int param_1);
undefined4 fn_00633e40(int param_1);
undefined4 fn_00634050(int param_1);
undefined4 fn_006341a0(int *param_1);
undefined4 fn_00634260(int param_1);
undefined4 fn_00634340(int param_1);
undefined4 fn_00634430(int param_1);
undefined4 fn_00634500(int param_1);
undefined4 fn_006347c0(int param_1);
undefined4 fn_00634ae0(int param_1);
undefined4 fn_006350e0(int param_1);
undefined4 fn_00635700(int param_1);
undefined4 fn_006357b0(int param_1);
undefined4 fn_00635860(int param_1);
undefined4 fn_00635920(int param_1);
undefined4 fn_00635a20(int param_1);
undefined4 fn_00635ae0(int param_1);
undefined4 fn_00635c20(int param_1);
undefined4 fn_00635ce0(int param_1);
undefined4 fn_00635e30(undefined4 *param_1);
undefined4 fn_00636050(undefined4 *param_1);
undefined4 fn_00636220(int param_1);
undefined4 fn_00636310(undefined4 *param_1);
undefined4 fn_00636700(int param_1);
undefined4 fn_006368c0(undefined4 *param_1);
undefined4 fn_00636cc0(int param_1);
undefined4 fn_00636db0(int param_1);
undefined4 fn_006370d0(int param_1);
undefined4 fn_00637170(int param_1);
undefined4 fn_006374b0(int param_1);
undefined4 fn_006375b0(int param_1);
undefined4 fn_00637740(int param_1);
undefined4 fn_00637800(int param_1);
undefined4 fn_006378c0(int param_1);
undefined4 fn_00637a10(int param_1);
undefined4 fn_00637b60(int param_1);
undefined4 fn_00637e10(int param_1);
undefined4 fn_006380d0(int param_1);
undefined4 fn_006382b0(int *param_1);
undefined4 fn_00638400(int param_1);
undefined4 fn_00638460(int param_1);
undefined4 fn_006384c0(int param_1);
undefined4 fn_00638520(int param_1);
undefined4 fn_00638560(int param_1);
undefined4 fn_006385a0(int param_1);
undefined4 fn_006385e0(undefined4 *param_1);
undefined4
fn_00638690(int param_1, undefined4 *param_2, int param_3, int param_4, int param_5, int param_6,
            int param_7);

void register_peephole_rules(void)

{
  if (native_extended_mode != 0) {
    AddPeepholeRule((short)(0x5c), (int)(fn_00635a20));
    AddPeepholeRule((short)(0x8b), (int)(fn_00635920));
    AddPeepholeRule((short)(400), (int)(fn_00635860));
    AddPeepholeRule((short)(0x67), (int)(fn_006347c0));
    AddPeepholeRule((short)(0x69), (int)(fn_00634ae0));
    AddPeepholeRule((short)(0x69), (int)(fn_00634500));
    AddPeepholeRule((short)(0x67), (int)(fn_00634ae0));
    AddPeepholeRule((short)(0x67), (int)(fn_00637a10));
    AddPeepholeRule((short)(0x67), (int)(fn_006378c0));
    AddPeepholeRule((short)(0x67), (int)(fn_00637800));
    AddPeepholeRule((short)(0x67), (int)(fn_00637740));
    AddPeepholeRule((short)(0x65), (int)(fn_006375b0));
    AddPeepholeRule((short)(0x31), (int)(fn_006339b0));
    AddPeepholeRule((short)(0x33), (int)(fn_006339b0));
    AddPeepholeRule((short)(0x2c), (int)(fn_00633600));
    AddPeepholeRule((short)(0x2e), (int)(fn_00633600));
    AddPeepholeRule((short)(0x67), (int)(fn_00634ae0));
    AddPeepholeRule((short)(0x49), (int)(fn_00634430));
    AddPeepholeRule((short)(0x3f), (int)(fn_00634340));
    AddPeepholeRule((short)(0x6c), (int)(fn_00634260));
    AddPeepholeRule((short)(0x5d), (int)(fn_00633e40));
    AddPeepholeRule((short)(0x69), (int)(fn_00633380));
    AddPeepholeRule((short)(0x58), (int)(fn_00633240));
    if (native_target_flag != '\0') {
      AddPeepholeRule((short)(5), (int)(fn_00637e10));
      AddPeepholeRule((short)(8), (int)(fn_00637e10));
      AddPeepholeRule((short)(5), (int)(fn_00635ce0));
      AddPeepholeRule((short)(8), (int)(fn_00635ce0));
      AddPeepholeRule((short)(0xed), (int)(fn_00637b60));
      AddPeepholeRule((short)(0xed), (int)(fn_00636db0));
      AddPeepholeRule((short)(0xed), (int)(fn_006370d0));
      AddPeepholeRule((short)(0x3f), (int)(fn_00636cc0));
    }
    return;
  }
  AddPeepholeRule((short)(0x67), (int)(fn_006347c0));
  AddPeepholeRule((short)(0x69), (int)(fn_00634ae0));
  AddPeepholeRule((short)(0x69), (int)(fn_00634500));
  AddPeepholeRule((short)(0x67), (int)(fn_00634ae0));
  AddPeepholeRule((short)(0x67), (int)(fn_00637a10));
  AddPeepholeRule((short)(0x67), (int)(fn_006378c0));
  AddPeepholeRule((short)(0x67), (int)(fn_00637800));
  AddPeepholeRule((short)(0x67), (int)(fn_00637740));
  AddPeepholeRule((short)(0x65), (int)(fn_006375b0));
  AddPeepholeRule((short)(0x31), (int)(fn_006339b0));
  AddPeepholeRule((short)(0x33), (int)(fn_006339b0));
  AddPeepholeRule((short)(0x2c), (int)(fn_00633600));
  AddPeepholeRule((short)(0x2e), (int)(fn_00633600));
  AddPeepholeRule((short)(0x5c), (int)(fn_00635a20));
  AddPeepholeRule((short)(0x8b), (int)(fn_006357b0));
  AddPeepholeRule((short)(0x9e), (int)(fn_00635700));
  AddPeepholeRule((short)(0x8b), (int)(fn_006384c0));
  AddPeepholeRule((short)(0x8b), (int)(fn_00635920));
  AddPeepholeRule((short)(0x8b), (int)(fn_006385a0));
  AddPeepholeRule((short)(0x9e), (int)(fn_00638460));
  AddPeepholeRule((short)(0x9e), (int)(fn_00638560));
  AddPeepholeRule((short)(400), (int)(fn_006382b0));
  AddPeepholeRule((short)(400), (int)(fn_00638400));
  AddPeepholeRule((short)(400), (int)(fn_00638520));
  AddPeepholeRule((short)(400), (int)(fn_00635860));
  AddPeepholeRule((short)(0x52), (int)(fn_006380d0));
  AddPeepholeRule((short)(0x67), (int)(fn_00634050));
  AddPeepholeRule((short)(0x15), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x19), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x1d), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x22), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x28), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x2c), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x31), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x8e), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x92), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x96), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x9a), (int)(fn_006374b0));
  AddPeepholeRule((short)(0x194), (int)(fn_00637170));
  AddPeepholeRule((short)(0x195), (int)(fn_00637170));
  AddPeepholeRule((short)(0x198), (int)(fn_00637170));
  AddPeepholeRule((short)(0x199), (int)(fn_00637170));
  AddPeepholeRule((short)(0xed), (int)(fn_006370d0));
  AddPeepholeRule((short)(0xed), (int)(fn_00636db0));
  AddPeepholeRule((short)(0x15), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x19), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x1d), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x22), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x28), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x2c), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x31), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x8e), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x92), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x96), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x9a), (int)(fn_006368c0));
  AddPeepholeRule((short)(0x194), (int)(fn_00636700));
  AddPeepholeRule((short)(0x198), (int)(fn_00636700));
  AddPeepholeRule((short)(0x16), (int)(fn_00636220));
  AddPeepholeRule((short)(0x1a), (int)(fn_00636220));
  AddPeepholeRule((short)(0x1e), (int)(fn_00636220));
  AddPeepholeRule((short)(0x23), (int)(fn_00636220));
  AddPeepholeRule((short)(0x29), (int)(fn_00636220));
  AddPeepholeRule((short)(0x2d), (int)(fn_00636220));
  AddPeepholeRule((short)(0x32), (int)(fn_00636220));
  AddPeepholeRule((short)(0x8f), (int)(fn_00636220));
  AddPeepholeRule((short)(0x93), (int)(fn_00636220));
  AddPeepholeRule((short)(0x97), (int)(fn_00636220));
  AddPeepholeRule((short)(0x9b), (int)(fn_00636220));
  AddPeepholeRule((short)(0x15), (int)(fn_00636050));
  AddPeepholeRule((short)(0x19), (int)(fn_00636050));
  AddPeepholeRule((short)(0x1d), (int)(fn_00636050));
  AddPeepholeRule((short)(0x22), (int)(fn_00636050));
  AddPeepholeRule((short)(0x28), (int)(fn_00636050));
  AddPeepholeRule((short)(0x2c), (int)(fn_00636050));
  AddPeepholeRule((short)(0x31), (int)(fn_00636050));
  AddPeepholeRule((short)(0x8e), (int)(fn_00636050));
  AddPeepholeRule((short)(0x92), (int)(fn_00636050));
  AddPeepholeRule((short)(0x96), (int)(fn_00636050));
  AddPeepholeRule((short)(0x9a), (int)(fn_00636050));
  AddPeepholeRule((short)(0x15), (int)(fn_00636310));
  AddPeepholeRule((short)(0x19), (int)(fn_00636310));
  AddPeepholeRule((short)(0x1d), (int)(fn_00636310));
  AddPeepholeRule((short)(0x22), (int)(fn_00636310));
  AddPeepholeRule((short)(0x28), (int)(fn_00636310));
  AddPeepholeRule((short)(0x2c), (int)(fn_00636310));
  AddPeepholeRule((short)(0x31), (int)(fn_00636310));
  AddPeepholeRule((short)(0x8e), (int)(fn_00636310));
  AddPeepholeRule((short)(0x92), (int)(fn_00636310));
  AddPeepholeRule((short)(0x96), (int)(fn_00636310));
  AddPeepholeRule((short)(0x9a), (int)(fn_00636310));
  AddPeepholeRule((short)(0x196), (int)(fn_00635e30));
  AddPeepholeRule((short)(0x192), (int)(fn_00635e30));
  AddPeepholeRule((short)(0x28), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x2c), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x31), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x96), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x9a), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x2a), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x2e), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x33), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x98), (int)(fn_006350e0));
  AddPeepholeRule((short)(0x9c), (int)(fn_006350e0));
  AddPeepholeRule((short)(5), (int)(fn_00635ae0));
  AddPeepholeRule((short)(8), (int)(fn_00635ae0));
  AddPeepholeRule((short)(5), (int)(fn_00635c20));
  AddPeepholeRule((short)(8), (int)(fn_00635c20));
  AddPeepholeRule((short)(5), (int)(fn_00635ce0));
  AddPeepholeRule((short)(8), (int)(fn_00635ce0));
  AddPeepholeRule((short)(0x67), (int)(fn_00634ae0));
  AddPeepholeRule((short)(0x49), (int)(fn_00634430));
  AddPeepholeRule((short)(0x3f), (int)(fn_00634340));
  AddPeepholeRule((short)(0x69), (int)(fn_00633380));
  AddPeepholeRule((short)(0x58), (int)(fn_00633240));
  if ((*(unsigned short *)((char *)&native_context_word+2)) == 8) {
    AddPeepholeRule((short)(0x8b), (int)(fn_006341a0));
  }
  AddPeepholeRule((short)(0x6c), (int)(fn_00634260));
  AddPeepholeRule((short)(0x5d), (int)(fn_00633e40));
  return;
}

/* Ported from 1.2.5 compute_register_mask. GC 3.0 adds high-half
 * immediates, XOR's conservative union, CNTLZW and LIS; RLWIMI now preserves
 * only the destination bits outside the insertion mask. Native register
 * operands use kind 0/class 4 and carry their own reaching definitions. */
uint fn_00632ea0(int param_1, short registerNumber)
{
    PeepholeInstruction *node = (PeepholeInstruction *)param_1;
    PeepholeOperand *entry;
    unsigned int entryCount;
    unsigned int result = 0xffffffffU, value, other, afterEnd, fromStart, mask;
    int begin, end, rotation;
    while (node != 0) {
        entryCount = node->operandCount;
        entry = node->operands;
        while (entryCount--) {
            if (entry->kind == 0 && entry->registerClass == 4 &&
                entry->payload.reg.number == registerNumber && (entry->payload.reg.flags & 2)) {
                switch (node->opcode) {
                case 0x15: case 0x16: case 0x17: case 0x18: result = 0xff; break;
                case 0x19: case 0x1a: case 0x1b: case 0x1c: result = 0xffff; break;
                case 0x56: case 0x57:
                    value = fn_00632ea0((int)node->previous, node->operands[1].payload.reg.number);
                    other = node->operands[2].payload.immediate.value;
                    if (node->opcode == 0x57) other <<= 16;
                    result = value & other;
                    break;
                case 0x58: case 0x59: case 0x5a: case 0x5b:
                    value = fn_00632ea0((int)node->previous, node->operands[1].payload.reg.number);
                    other = node->operands[2].payload.immediate.value;
                    if (node->opcode == 0x59 || node->opcode == 0x5b) other <<= 16;
                    result = value | other;
                    break;
                case 0x5c:
                    value = fn_00632ea0((int)node->previous, node->operands[2].payload.reg.number);
                    other = fn_00632ea0((int)node->previous, node->operands[1].payload.reg.number);
                    result = value & other;
                    break;
                case 0x5d: case 0x5e:
                    value = fn_00632ea0((int)node->previous, node->operands[2].payload.reg.number);
                    other = fn_00632ea0((int)node->previous, node->operands[1].payload.reg.number);
                    result = value | other;
                    break;
                case 0x66: result = 0x3f; break;
                case 0x67: case 0x69:
                    value = fn_00632ea0((int)node->previous, node->operands[1].payload.reg.number);
                    begin = node->operands[3].payload.immediate.value;
                    end = node->operands[4].payload.immediate.value;
                    rotation = node->operands[2].payload.immediate.value;
                    afterEnd = end + 1 < 32 ? 0xffffffffU >> ((end + 1) & 31) : 0;
                    fromStart = begin < 32 ? 0xffffffffU >> (begin & 31) : 0;
                    mask = end < begin ? ~afterEnd | fromStart : ~afterEnd & fromStart;
                    result = ((value >> ((32 - rotation) & 31)) | (value << (rotation & 31))) & mask;
                    if (node->opcode == 0x69) {
                        other = fn_00632ea0((int)node->previous, node->operands[0].payload.reg.number);
                        result |= other & ~mask;
                    }
                    break;
                case 0x6c:
                    value = fn_00632ea0((int)node->previous, node->operands[1].payload.reg.number);
                    result = (int)value >> (node->operands[2].payload.immediate.value & 31);
                    break;
                case 0x89: result = node->operands[1].payload.immediate.value; break;
                case 0x8a: result = (unsigned int)node->operands[1].payload.immediate.value << 16; break;
                case 0x8b: result = fn_00632ea0((int)node->previous, node->operands[1].payload.reg.number); break;
                }
                return result;
            }
            ++entry;
        }
        node = node->previous;
    }
    return 0xffffffffU;
}


undefined4 fn_00633240(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar3 = (int)(*(int *)(param_1 + 0x40));
  if ((*(uint *)(param_1 + 0xc) & 0x180) != 0 || (*(uint *)(param_1 + 0x10) & 0x100000) != 0) {
    return 0;
  }
  sVar1 = (short)(*(short *)(param_1 + 0x3e));
  iVar5 = (int)((int)sVar1);
  sVar2 = (short)(*(short *)(param_1 + 0x30));
  if (*(short *)(iVar3 + 0x28) == *(short *)(param_1 + 0x28)) {
    if (iVar5 == *(short *)(iVar3 + 0x3e)) {
      iVar4 = (int)(fn_00596b50((int)(param_1), (int)(iVar3), (int)(param_1 + 0x3a)));
      if ((iVar4 == 0) &&
         ((*(uint *)(native_liveness_bank4 + (iVar5 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0 ||
         (iVar5 == sVar2))) {
        iVar5 = (int)(*(int *)(iVar3 + 0x40));
        if (iVar5 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)(param_1 + 0x40) = iVar5;
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(iVar3 + 0x3a);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(iVar3 + 0x3e);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(iVar3 + 0x42);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(iVar3 + 0x46);
        *(uint *)(param_1 + 0x4a) = *(uint *)(param_1 + 0x4a) | *(uint *)(iVar3 + 0x4a);
        deletepcode((int)(iVar3));
        return 1;
      }
    }
    else {
      iVar5 = (int)(fn_00596bd0((int)(param_1), (int)(iVar3), (int)(iVar3 + 0x3a)));
      if (iVar5 == 0) {
        iVar5 = (int)(*(int *)(iVar3 + 0x40));
        if (iVar5 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)(param_1 + 0x40) = iVar5;
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(iVar3 + 0x3a);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(iVar3 + 0x3e);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(iVar3 + 0x42);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(iVar3 + 0x46);
        *(uint *)(param_1 + 0x4a) = *(uint *)(param_1 + 0x4a) | *(uint *)(iVar3 + 0x4a);
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_00633380(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;

  uint uVar4;
  uint uVar5;
  short local_10;
  short sStack_e;

  if ((*(short *)(*(int *)(param_1 + 0x40) + 0x28) == 0x89) && (*(char *)(param_1 + 0x48) == '\x02')
     && (*(short *)(param_1 + 0x30) != *(short *)(param_1 + 0x3e))) {
    local_10 = (short)(*(short *)(param_1 + 0x58));
    uVar3 = (uint)(*(uint *)(*(int *)(param_1 + 0x40) + 0x3c));
    sStack_e = (short)(*(short *)(param_1 + 0x66));
    if (sStack_e < local_10) {
      if (sStack_e + 1 < 0x20) {
        uVar4 = (uint)(0xffffffff >> ((byte)(sStack_e + 1) & 0x1f));
      }
      else {
        uVar4 = (uint)(0);
      }
      if (local_10 < 0x20) {
        uVar5 = (uint)(0xffffffff >> ((byte)local_10 & 0x1f));
      }
      else {
        uVar5 = (uint)(0);
      }
      uVar5 = (uint)(~uVar4 | uVar5);
    }
    else {
      if (sStack_e + 1 < 0x20) {
        uVar4 = (uint)(0xffffffff >> ((byte)(sStack_e + 1) & 0x1f));
      }
      else {
        uVar4 = (uint)(0);
      }
      if (local_10 < 0x20) {
        uVar5 = (uint)(0xffffffff >> ((byte)local_10 & 0x1f));
      }
      else {
        uVar5 = (uint)(0);
      }
      uVar5 = (uint)(~uVar4 & uVar5);
    }
    bVar1 = (byte)((byte)*(undefined2 *)(param_1 + 0x4a));
    uVar3 = (uint)((uVar3 >> (0x20 - bVar1 & 0x1f) | uVar3 << (bVar1 & 0x1f)) & uVar5);
    if (uVar3 == 0) {
      *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(param_1 + 0x2c);
      *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(param_1 + 0x34);
      *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(param_1 + 0x38);
      *(ushort *)(param_1 + 0x3c) = *(ushort *)(param_1 + 0x3c) & 0xfffd;
      iVar2 = (int)(*(int *)(param_1 + 0x32));
      if (iVar2 == 0) {
        CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
      }
      *(int *)(param_1 + 0x40) = iVar2;
      *(ushort *)(param_1 + 0x2e) = *(ushort *)(param_1 + 0x2e) & 0xfffe;
      *(undefined4 *)(param_1 + 0x4a) = 0;
      iVar2 = (int)(InstrSelection_GetMaskRange((int)(~uVar5), (int)(&local_10), (int)(&sStack_e)));
      if (iVar2 == 0) {
        CError_Internal((const char *)(peepholeFilename), (int)(0x10ad));
      }
      *(int *)(param_1 + 0x58) = (int)local_10;
      *(int *)(param_1 + 0x66) = (int)sStack_e;
      change_opcode((int)(param_1), (short)(0x67));
      return 1;
    }
    if (uVar5 == uVar3) {
      if ((*(uint *)(param_1 + 0xc) & 0x180) != 0 || (*(uint *)(param_1 + 0x10) & 0x100000) != 0) {
        return 0;
      }
      if (uVar5 == (uVar5 & 0xffff)) {
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(param_1 + 0x2c);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(param_1 + 0x30);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(param_1 + 0x34);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(param_1 + 0x38);
        *(ushort *)(param_1 + 0x3c) = *(ushort *)(param_1 + 0x3c) & 0xfffd;
        *(ushort *)(param_1 + 0x2e) = *(ushort *)(param_1 + 0x2e) & 0xfffe;
        *(undefined1 *)(param_1 + 0x48) = 2;
        *(uint *)(param_1 + 0x4a) = uVar5;
        change_num_operands((int)(param_1), (int)(3));
        change_opcode((int)(param_1), (short)(0x58));
        return 1;
      }
      if (uVar5 == (uVar5 & 0xffff0000)) {
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(param_1 + 0x2c);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(param_1 + 0x30);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(param_1 + 0x34);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(param_1 + 0x38);
        *(ushort *)(param_1 + 0x3c) = *(ushort *)(param_1 + 0x3c) & 0xfffd;
        *(ushort *)(param_1 + 0x2e) = *(ushort *)(param_1 + 0x2e) & 0xfffe;
        *(undefined1 *)(param_1 + 0x48) = 2;
        *(uint *)(param_1 + 0x4a) = uVar5 >> 0x10;
        change_num_operands((int)(param_1), (int)(3));
        change_opcode((int)(param_1), (short)(0x59));
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_00633600(int param_1)

{
  uint *puVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int local_1c [2];
  char local_11;

  bVar3 = (bool)(false);
  bVar2 = (bool)(false);
  local_11 = (char)('\0');
  if (*(short *)(param_1 + 0x3c) == 0) {
    return 0;
  }
  if ((*(short *)(param_1 + 0x28) == 0x2c) && (*(char *)(param_1 + 0x48) == '\x02') &&
     (*(int *)(param_1 + 0x4a) == 0)) {
    local_11 = (char)('\x01');
  }
  iVar5 = (int)(0);
  iVar4 = (int)(param_1);
  do {
    if (*(short *)(iVar4 + 0x28) == 0x67) {
      local_1c[iVar5] = *(int *)(iVar4 + 0x40);
    }
    else {
      local_1c[iVar5] = *(int *)(iVar4 + 0x32);
    }
    iVar4 = (int)(local_1c[iVar5]);
    if (*(short *)(local_1c[0] + 0x3e) != *(short *)(iVar4 + 0x3e)) {
      return 0;
    }
    if (iVar5 < 1) {
      if (*(short *)(iVar4 + 0x28) != 0x69) {
        return 0;
      }
    }
    else if (*(short *)(iVar4 + 0x28) != 0x67) {
      return 0;
    }
    if (*(int *)(iVar4 + 0x4a) == 8) {
      if ((*(int *)(iVar4 + 0x58) != 0x10) || (*(int *)(iVar4 + 0x66) != 0x17)) {
        return 0;
      }
      if (bVar3) {
        return 0;
      }
      bVar3 = (bool)(true);
    }
    else {
      if (*(int *)(iVar4 + 0x4a) != 0x18) {
        return 0;
      }
      if ((*(int *)(iVar4 + 0x58) != 0x18) || (*(int *)(iVar4 + 0x66) != 0x1f)) {
        return 0;
      }
      if (bVar2) {
        return 0;
      }
      bVar2 = (bool)(true);
    }
    iVar5 = (int)(iVar5 + 1);
  } while (iVar5 < 2);
  iVar4 = (int)(fn_00596bd0((int)(param_1), (int)(local_1c[1]), (int)(local_1c[0] + 0x3a)));
  if (iVar4 != 0) {
    return 0;
  }
  if (*(short *)(param_1 + 0x28) != 0x2e) {
    if (*(short *)(param_1 + 0x28) != 0x2c) {
      return 0;
    }
    iVar4 = (int)(*(int *)(local_1c[1] + 0x40));
    if (iVar4 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    *(int *)(param_1 + 0x32) = iVar4;
    if (local_11 == '\0') {
      if ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(local_1c[0] + 0x30) >> 5) * 4) >>
           ((byte)*(short *)(local_1c[0] + 0x30) & 0x1f) & 1) != 0) {
        return 0;
      }
      iVar4 = (int)(fn_00596b50((int)(local_1c[0]), (int)(local_1c[1]), (int)(local_1c[0] + 0x2c)));
      if (iVar4 != 0) {
        return 0;
      }
      iVar4 = (int)(fn_00596b50((int)(param_1), (int)(local_1c[0]), (int)(local_1c[0] + 0x2c)));
      if (iVar4 != 0) {
        return 0;
      }
      iVar4 = (int)(makepcode((short)(0x30), (int)((int)*(short *)(local_1c[1] + 0x3e)), (int)(0), (int)((int)*(short *)(param_1 + 0x30))));
      *(undefined4 *)(iVar4 + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
      change_opcode((int)(param_1), (short)(0x3f));
      *(ushort *)(param_1 + 0x2e) = *(ushort *)(param_1 + 0x2e) & 0xfffe;
      *(ushort *)(param_1 + 0x2e) = *(ushort *)(param_1 + 0x2e) | 2;
      *(int *)(param_1 + 0x32) = param_1;
      insertpcodeafter((int)(param_1), (int)(iVar4));
      puVar1 = (uint*)((uint *)(native_liveness_bank4 + ((int)*(short *)(iVar4 + 0x30) >> 5) * 4));
      *puVar1 = (uint)(*puVar1 | 1 << ((byte)*(short *)(iVar4 + 0x30) & 0x1f));
      puVar1 = (uint*)((uint *)(native_liveness_bank4 + ((int)*(short *)(iVar4 + 0x4c) >> 5) * 4));
      *puVar1 = (uint)(*puVar1 | 1 << ((byte)*(short *)(iVar4 + 0x4c) & 0x1f));
      deletepcode((int)(local_1c[0]));
      deletepcode((int)(local_1c[1]));
    }
    else {
      change_opcode((int)(param_1), (short)(0x30));
      *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(local_1c[0] + 0x3a);
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(local_1c[0] + 0x3e);
      *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(local_1c[0] + 0x42);
      *(undefined2 *)(param_1 + 0x38) = *(undefined2 *)(local_1c[0] + 0x46);
      *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3a);
      *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x3e);
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x42);
      *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(param_1 + 0x46);
      iVar4 = (int)(*(int *)(param_1 + 0x40));
      if (iVar4 == 0) {
        CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
      }
      *(int *)(param_1 + 0x4e) = iVar4;
      *(undefined1 *)(param_1 + 0x3a) = 0;
      *(undefined1 *)(param_1 + 0x3b) = 4;
      *(undefined2 *)(param_1 + 0x3e) = 0;
      *(undefined2 *)(param_1 + 0x3c) = 0;
    }
    return 1;
  }
  change_opcode((int)(param_1), (short)(0x30));
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(local_1c[0] + 0x3a);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(local_1c[0] + 0x3e);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(local_1c[0] + 0x42);
  *(undefined2 *)(param_1 + 0x38) = *(undefined2 *)(local_1c[0] + 0x46);
  iVar4 = (int)(*(int *)(local_1c[1] + 0x40));
  if (iVar4 == 0) {
    CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
  }
  *(int *)(param_1 + 0x32) = iVar4;
  return 1;
}

undefined4 fn_006339b0(int param_1)

{
  uint *puVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_24 [4];
  char local_11;

  bVar5 = (bool)(false);
  bVar4 = (bool)(false);
  bVar3 = (bool)(false);
  bVar2 = (bool)(false);
  local_11 = (char)('\0');
  if ((*(short *)(param_1 + 0x28) == 0x31) && (*(char *)(param_1 + 0x48) == '\x02') &&
     (*(int *)(param_1 + 0x4a) == 0)) {
    local_11 = (char)('\x01');
  }
  iVar8 = (int)(0);
  iVar7 = (int)(param_1);
  do {
    if (*(short *)(iVar7 + 0x28) == 0x67) {
      local_24[iVar8] = *(int *)(iVar7 + 0x40);
    }
    else {
      local_24[iVar8] = *(int *)(iVar7 + 0x32);
    }
    iVar7 = (int)(local_24[iVar8]);
    if (*(short *)(local_24[0] + 0x3e) != *(short *)(iVar7 + 0x3e)) {
      return 0;
    }
    if (iVar8 < 3) {
      if (*(short *)(iVar7 + 0x28) != 0x69) {
        return 0;
      }
    }
    else if (*(short *)(iVar7 + 0x28) != 0x67) {
      return 0;
    }
    if (*(int *)(iVar7 + 0x4a) == 8) {
      if ((*(int *)(iVar7 + 0x58) == 0x18) && (*(int *)(iVar7 + 0x66) == 0x1f)) {
        if (bVar4) {
          return 0;
        }
        bVar4 = (bool)(true);
      }
      else {
        if ((*(int *)(iVar7 + 0x58) != 8) || (*(int *)(iVar7 + 0x66) != 0xf)) {
          return 0;
        }
        if (bVar3) {
          return 0;
        }
        bVar3 = (bool)(true);
      }
    }
    else {
      if (*(int *)(iVar7 + 0x4a) != 0x18) {
        return 0;
      }
      if ((*(int *)(iVar7 + 0x58) == 0) && (*(int *)(iVar7 + 0x66) == 7)) {
        if (bVar5) {
          return 0;
        }
        bVar5 = (bool)(true);
      }
      else {
        if ((*(int *)(iVar7 + 0x58) != 0x10) || (*(int *)(iVar7 + 0x66) != 0x17)) {
          return 0;
        }
        if (bVar2) {
          return 0;
        }
        bVar2 = (bool)(true);
      }
    }
    iVar8 = (int)(iVar8 + 1);
  } while (iVar8 < 4);
  iVar8 = (int)(fn_00596bd0((int)(param_1), (int)(local_24[3]), (int)(local_24[0] + 0x3a)));
  iVar7 = (int)(local_24[2]);
  if (iVar8 != 0) {
    return 0;
  }
  if (*(short *)(param_1 + 0x28) == 0x33) {
    change_opcode((int)(param_1), (short)(0x35));
    *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(local_24[0] + 0x3a);
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(local_24[0] + 0x3e);
    *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(local_24[0] + 0x42);
    *(undefined2 *)(param_1 + 0x38) = *(undefined2 *)(local_24[0] + 0x46);
    iVar7 = (int)(*(int *)(local_24[3] + 0x40));
    if (iVar7 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    *(int *)(param_1 + 0x32) = iVar7;
    return 1;
  }
  if (*(short *)(param_1 + 0x28) != 0x31) {
    return 0;
  }
  if (local_11 == '\0') {
    if ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(local_24[0] + 0x30) >> 5) * 4) >>
         ((byte)*(short *)(local_24[0] + 0x30) & 0x1f) & 1) != 0) {
      return 0;
    }
    iVar6 = (int)(fn_00596b50((int)(local_24[2]), (int)(local_24[3]), (int)(local_24[0] + 0x2c)));
    iVar8 = (int)(local_24[1]);
    if (iVar6 != 0) {
      return 0;
    }
    iVar7 = (int)(fn_00596b50((int)(local_24[1]), (int)(iVar7), (int)(local_24[0] + 0x2c)));
    if (iVar7 != 0) {
      return 0;
    }
    iVar7 = (int)(fn_00596b50((int)(local_24[0]), (int)(iVar8), (int)(local_24[0] + 0x2c)));
    if (iVar7 != 0) {
      return 0;
    }
    iVar7 = (int)(fn_00596b50((int)(param_1), (int)(local_24[0]), (int)(local_24[0] + 0x2c)));
    if (iVar7 != 0) {
      return 0;
    }
  }
  iVar7 = (int)(*(int *)(local_24[3] + 0x40));
  if (iVar7 == 0) {
    CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
  }
  *(int *)(param_1 + 0x32) = iVar7;
  if (local_11 == '\0') {
    iVar7 = (int)(makepcode((short)(0x35), (int)((int)*(short *)(local_24[3] + 0x3e)), (int)(0), (int)((int)*(short *)(param_1 + 0x30))));
    *(undefined4 *)(iVar7 + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
    change_opcode((int)(param_1), (short)(0x3f));
    insertpcodeafter((int)(param_1), (int)(iVar7));
    puVar1 = (uint*)((uint *)(native_liveness_bank4 + ((int)*(short *)(iVar7 + 0x30) >> 5) * 4));
    *puVar1 = (uint)(*puVar1 | 1 << ((byte)*(short *)(iVar7 + 0x30) & 0x1f));
    puVar1 = (uint*)((uint *)(native_liveness_bank4 + ((int)*(short *)(iVar7 + 0x4c) >> 5) * 4));
    *puVar1 = (uint)(*puVar1 | 1 << ((byte)*(short *)(iVar7 + 0x4c) & 0x1f));
    *(ushort *)(param_1 + 0x2e) = *(ushort *)(param_1 + 0x2e) & 0xfffe;
    *(ushort *)(param_1 + 0x2e) = *(ushort *)(param_1 + 0x2e) | 2;
    *(int *)(param_1 + 0x32) = param_1;
    deletepcode((int)(local_24[0]));
    deletepcode((int)(local_24[1]));
    deletepcode((int)(local_24[2]));
    deletepcode((int)(local_24[3]));
  }
  else {
    change_opcode((int)(param_1), (short)(0x35));
    *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(local_24[0] + 0x3a);
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(local_24[0] + 0x3e);
    *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(local_24[0] + 0x42);
    *(undefined2 *)(param_1 + 0x38) = *(undefined2 *)(local_24[0] + 0x46);
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3a);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x3e);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x42);
    *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(param_1 + 0x46);
    iVar7 = (int)(*(int *)(param_1 + 0x40));
    if (iVar7 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    *(int *)(param_1 + 0x4e) = iVar7;
    iVar7 = (int)(*(int *)(local_24[1] + 0x40));
    if (iVar7 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    *(int *)(param_1 + 0x32) = iVar7;
    *(undefined1 *)(param_1 + 0x3a) = 0;
    *(undefined1 *)(param_1 + 0x3b) = 4;
    *(undefined2 *)(param_1 + 0x3e) = 0;
    *(undefined2 *)(param_1 + 0x3c) = 0;
  }
  return 1;
}

undefined4 fn_00633e40(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar3 = (int)(*(int *)(param_1 + 0x40));
  iVar2 = (int)(*(int *)(param_1 + 0x4e));
  if ((*(uint *)(param_1 + 0xc) & 0x180) != 0 || (*(uint *)(param_1 + 0x10) & 0x100000) != 0) {
    return 0;
  }
  if (((*(short *)(iVar3 + 0x28) != 0x6b) ||
      (iVar4 = iVar3, iVar5 = iVar2, *(short *)(iVar2 + 0x28) != 0x6a)) &&
     (*(short *)(iVar3 + 0x28) != 0x6a ||
     (iVar4 = iVar2, iVar5 = iVar3, *(short *)(iVar2 + 0x28) != 0x6b))) {
    return 0;
  }
  if (*(short *)(iVar5 + 0x3e) != *(short *)(iVar4 + 0x3e)) {
    return 0;
  }
  if (*(int *)(iVar5 + 0x40) == *(int *)(iVar4 + 0x40)) {
    sVar1 = (short)(*(short *)(iVar5 + 0x30));
    if (((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) != 0) &&
       (sVar1 != *(short *)(param_1 + 0x30))) {
      return 0;
    }
    iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar5), (int)(iVar5 + 0x2c)));
    if (iVar3 != 0) {
      return 0;
    }
    iVar3 = (int)(*(int *)(iVar5 + 0x4e));
    if (((*(short *)(iVar3 + 0x28) != 0x4f) ||
        (*(short *)(iVar3 + 0x3e) != *(short *)(iVar4 + 0x4c)) || (*(int *)(iVar3 + 0x4a) != 0x20))
       && (iVar3 = *(int *)(iVar4 + 0x4e), *(short *)(iVar3 + 0x28) != 0x4f ||
          (*(short *)(iVar3 + 0x3e) != *(short *)(iVar5 + 0x4c)) || (*(int *)(iVar3 + 0x4a) != 0x20)
          )) {
      return 0;
    }
    change_opcode((int)(iVar5), (short)(0x68));
    change_num_operands((int)(iVar5), (int)(5));
    *(undefined1 *)(iVar5 + 0x56) = 2;
    *(undefined4 *)(iVar5 + 0x58) = 0;
    *(undefined1 *)(iVar5 + 100) = 2;
    *(undefined4 *)(iVar5 + 0x66) = 0x1f;
    iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar5), (int)(param_1 + 0x2c)));
    if ((iVar3 == 0) && (iVar3 = fn_00596bd0((int)(param_1), (int)(iVar5), (int)(param_1 + 0x2c)), iVar3 == 0)) {
      *(undefined4 *)(iVar5 + 0x2c) = *(undefined4 *)(param_1 + 0x2c);
      *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(iVar5 + 0x34) = *(undefined4 *)(param_1 + 0x34);
      *(undefined2 *)(iVar5 + 0x38) = *(undefined2 *)(param_1 + 0x38);
      deletepcode((int)(param_1));
    }
    else {
      change_opcode((int)(param_1), (short)(0x8b));
      if (iVar5 == iVar2) {
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(param_1 + 0x48);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(param_1 + 0x4c);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(param_1 + 0x50);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(param_1 + 0x54);
      }
      change_num_operands((int)(param_1), (int)(2));
      *(int *)(param_1 + 0x40) = iVar5;
    }
    return 1;
  }
  return 0;
}

undefined4 fn_00634050(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;

  if (*(int *)(param_1 + 0x4a) != 0) {
    return 0;
  }
  iVar1 = (int)(*(int *)(param_1 + 0x66));
  iVar2 = (int)(*(int *)(param_1 + 0x58));
  if (iVar1 < iVar2) {
    if (iVar1 + 1 < 0x20) {
      uVar3 = (uint)(0xffffffff >> ((byte)(iVar1 + 1) & 0x1f));
    }
    else {
      uVar3 = (uint)(0);
    }
    if (iVar2 < 0x20) {
      uVar4 = (uint)(0xffffffff >> ((byte)iVar2 & 0x1f));
    }
    else {
      uVar4 = (uint)(0);
    }
    uVar4 = (uint)(~uVar3 | uVar4);
  }
  else {
    if (iVar1 + 1 < 0x20) {
      uVar3 = (uint)(0xffffffff >> ((byte)(iVar1 + 1) & 0x1f));
    }
    else {
      uVar3 = (uint)(0);
    }
    if (iVar2 < 0x20) {
      uVar4 = (uint)(0xffffffff >> ((byte)iVar2 & 0x1f));
    }
    else {
      uVar4 = (uint)(0);
    }
    uVar4 = (uint)(~uVar3 & uVar4);
  }
  if (((*(unsigned short *)((char *)&native_context_word+2)) == 0x18) && ((*(uint *)(param_1 + 0x10) & 0x100000) != 0)) {
    if ((uVar4 & 0xffff0000) == 0) {
      *(undefined1 *)(param_1 + 0x48) = 2;
      *(uint *)(param_1 + 0x4a) = uVar4;
      *(undefined4 *)(param_1 + 0x56) = *(undefined4 *)(param_1 + 0x72);
      *(undefined4 *)(param_1 + 0x5a) = *(undefined4 *)(param_1 + 0x76);
      *(undefined4 *)(param_1 + 0x5e) = *(undefined4 *)(param_1 + 0x7a);
      *(undefined2 *)(param_1 + 0x62) = *(undefined2 *)(param_1 + 0x7e);
      change_opcode((int)(param_1), (short)(0x56));
      change_num_operands((int)(param_1), (int)(4));
      return 1;
    }
    if ((uVar4 & 0xffff) == 0) {
      *(undefined1 *)(param_1 + 0x48) = 2;
      *(uint *)(param_1 + 0x4a) = uVar4 >> 0x10;
      *(undefined4 *)(param_1 + 0x56) = *(undefined4 *)(param_1 + 0x72);
      *(undefined4 *)(param_1 + 0x5a) = *(undefined4 *)(param_1 + 0x76);
      *(undefined4 *)(param_1 + 0x5e) = *(undefined4 *)(param_1 + 0x7a);
      *(undefined2 *)(param_1 + 0x62) = *(undefined2 *)(param_1 + 0x7e);
      change_opcode((int)(param_1), (short)(0x57));
      change_num_operands((int)(param_1), (int)(4));
      return 1;
    }
  }
  return 0;
}

undefined4 fn_006341a0(int *param_1)

{
  bool bVar1;
  bool bVar2;

  bVar1 = (bool)(false);
  bVar2 = (bool)(false);
  if ((*(unsigned short *)((char *)&native_context_word+2)) == 8) {
    if ((param_1[1] != 0) &&
       (bVar1 = false, (*(uint *)(param_1[1] + 0x10) & 0xe0000000) == 0x80000000)) {
      bVar1 = (bool)(true);
    }
    if ((*param_1 != 0) && (bVar2 = false, (*(uint *)(*param_1 + 0x10) & 0xe0000000) == 0x80000000))
    {
      bVar2 = (bool)(true);
    }
    if (((param_1[3] & 0x180U) == 0 && (param_1[4] & 0x100000U) == 0) &&
       (*(short *)((int)param_1 + 0x2a) > 1) && (*(short *)((int)param_1 + 0x3e) != 0) &&
       (bVar1 || (bVar2))) {
      *(undefined1 *)(param_1 + 0x12) = 2;
      *(undefined4 *)((int)param_1 + 0x4a) = 0;
      change_opcode((int)(param_1), (short)(0x3f));
      change_num_operands((int)(param_1), (int)(3));
      return 1;
    }
  }
  return 0;
}

undefined4 fn_00634260(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if ((*(short *)(iVar2 + 0x28) == 0x6c) &&
     ((sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
      ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
     ((*(uint *)(iVar2 + 0xc) & 0x180) == 0 && (*(uint *)(iVar2 + 0x10) & 0x100000) == 0))) {
    iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)));
    if (iVar3 == 0) {
      iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
      if ((iVar3 == 0) && (*(char *)(param_1 + 0x48) == '\x02') &&
         (*(char *)(iVar2 + 0x48) == '\x02' &&
         (iVar3 = *(int *)(param_1 + 0x4a) + *(int *)(iVar2 + 0x4a), iVar3 < 0x20 && (iVar3 > 0))))
      {
        *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
        iVar3 = (int)(*(int *)(iVar2 + 0x40));
        if (iVar3 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)(param_1 + 0x40) = iVar3;
        *(int *)(param_1 + 0x4a) = *(int *)(param_1 + 0x4a) + *(int *)(iVar2 + 0x4a);
        deletepcode((int)(iVar2));
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_00634340(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if (iVar2 == 0) {
    return 0;
  }
  if ((*(short *)(iVar2 + 0x28) == 0x3f) &&
     ((sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
      ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
     ((*(uint *)(iVar2 + 0xc) & 0x180) == 0 && (*(uint *)(iVar2 + 0x10) & 0x100000) == 0) &&
     (iVar3 = fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)), iVar3 == 0 &&
     (iVar3 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)), iVar3 == 0))) &&
     (*(char *)(param_1 + 0x48) == '\x02') &&
     (*(char *)(iVar2 + 0x48) == '\x02' &&
     (iVar3 = *(int *)(param_1 + 0x4a) + *(int *)(iVar2 + 0x4a), iVar3 == (short)iVar3))) {
    *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
    iVar3 = (int)(*(int *)(iVar2 + 0x40));
    if (iVar3 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    *(int *)(param_1 + 0x40) = iVar3;
    *(int *)(param_1 + 0x4a) = *(int *)(param_1 + 0x4a) + *(int *)(iVar2 + 0x4a);
    deletepcode((int)(iVar2));
    return 1;
  }
  return 0;
}

undefined4 fn_00634430(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if ((*(short *)(iVar2 + 0x28) == 0x49) &&
     ((sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
      ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
     ((*(uint *)(iVar2 + 0xc) & 0x180) == 0 && (*(uint *)(iVar2 + 0x10) & 0x100000) == 0))) {
    iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)));
    if (iVar3 == 0) {
      iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
      if ((iVar3 == 0) &&
         (iVar3 = *(int *)(param_1 + 0x4a) * *(int *)(iVar2 + 0x4a), iVar3 - (short)iVar3 == 0)) {
        *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
        iVar3 = (int)(*(int *)(iVar2 + 0x40));
        if (iVar3 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)(param_1 + 0x40) = iVar3;
        *(int *)(param_1 + 0x4a) = *(int *)(param_1 + 0x4a) * *(int *)(iVar2 + 0x4a);
        deletepcode((int)(iVar2));
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_00634500(int param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  short local_14;
  short local_12;

  iVar1 = (int)(*(int *)(param_1 + 0x32));
  if ((*(uint *)(param_1 + 0xc) & 0x180) != 0) {
    return 0;
  }
  if (*(short *)(iVar1 + 0x28) != 0x67) {
    return 0;
  }
  if ((*(uint *)(iVar1 + 0x10) & 0x100000) == 0) {
    bVar3 = (bool)(false);
  }
  else {
    iVar4 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x72)));
    if (iVar4 == 0) {
      bVar3 = (bool)(false);
    }
    else {
      bVar3 = (bool)(true);
    }
  }
  if (bVar3) {
    return 0;
  }
  if ((*(uint *)(iVar1 + 0xc) & 0x180) != 0 || (*(uint *)(iVar1 + 0x10) & 0x100000) != 0) {
    return 0;
  }
  if (*(short *)(iVar1 + 0x3e) == *(short *)(param_1 + 0x3e)) {
    if (*(int *)(iVar1 + 0x4a) != *(int *)(param_1 + 0x4a)) {
      return 0;
    }
    iVar4 = (int)(fn_00596bd0((int)(param_1), (int)(iVar1), (int)(param_1 + 0x3a)));
    if (iVar4 != 0) {
      return 0;
    }
    iVar4 = (int)(*(int *)(iVar1 + 0x66));
    iVar2 = (int)(*(int *)(iVar1 + 0x58));
    if (iVar4 < iVar2) {
      if (iVar4 + 1 < 0x20) {
        uVar7 = (uint)(0xffffffff >> ((byte)(iVar4 + 1) & 0x1f));
      }
      else {
        uVar7 = (uint)(0);
      }
      if (iVar2 < 0x20) {
        uVar5 = (uint)(0xffffffff >> ((byte)iVar2 & 0x1f));
      }
      else {
        uVar5 = (uint)(0);
      }
      uVar5 = (uint)(~uVar7 | uVar5);
    }
    else {
      if (iVar4 + 1 < 0x20) {
        uVar7 = (uint)(0xffffffff >> ((byte)(iVar4 + 1) & 0x1f));
      }
      else {
        uVar7 = (uint)(0);
      }
      if (iVar2 < 0x20) {
        uVar5 = (uint)(0xffffffff >> ((byte)iVar2 & 0x1f));
      }
      else {
        uVar5 = (uint)(0);
      }
      uVar5 = (uint)(~uVar7 & uVar5);
    }
    iVar4 = (int)(*(int *)(param_1 + 0x66));
    iVar2 = (int)(*(int *)(param_1 + 0x58));
    if (iVar4 < iVar2) {
      if (iVar4 + 1 < 0x20) {
        uVar7 = (uint)(0xffffffff >> ((byte)(iVar4 + 1) & 0x1f));
      }
      else {
        uVar7 = (uint)(0);
      }
      if (iVar2 < 0x20) {
        uVar6 = (uint)(0xffffffff >> ((byte)iVar2 & 0x1f));
      }
      else {
        uVar6 = (uint)(0);
      }
      uVar6 = (uint)(~uVar7 | uVar6);
    }
    else {
      if (iVar4 + 1 < 0x20) {
        uVar7 = (uint)(0xffffffff >> ((byte)(iVar4 + 1) & 0x1f));
      }
      else {
        uVar7 = (uint)(0);
      }
      if (iVar2 < 0x20) {
        uVar6 = (uint)(0xffffffff >> ((byte)iVar2 & 0x1f));
      }
      else {
        uVar6 = (uint)(0);
      }
      uVar6 = (uint)(~uVar7 & uVar6);
    }
    iVar4 = (int)(InstrSelection_GetMaskRange((int)(uVar5 | uVar6), (int)(&local_12), (int)(&local_14)));
    if (iVar4 == 0) {
      return 0;
    }
    if (((*(uint *)(param_1 + 0x10) & 0x100000) == 0) || ((*(uint *)native_liveness_mask0 & 1) == 0)) {
      bVar3 = (bool)(false);
    }
    else {
      bVar3 = (bool)(true);
    }
    if (bVar3) {
      iVar4 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(param_1 + 0x72)));
      if (iVar4 != 0) {
        return 0;
      }
      iVar4 = (int)(fn_00596bd0((int)(param_1), (int)(iVar1), (int)(param_1 + 0x72)));
      if (iVar4 != 0) {
        return 0;
      }
      pcsetrecordbit((int)(iVar1));
    }
    *(int *)(iVar1 + 0x58) = (int)local_12;
    *(int *)(iVar1 + 0x66) = (int)local_14;
    deletepcode((int)(param_1));
    return 1;
  }
  return 0;
}

undefined4 fn_006347c0(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint local_14;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if (*(short *)(iVar2 + 0x28) == 0x6c) {
    if ((*(uint *)(iVar2 + 0xc) & 0x180) != 0) {
      return 0;
    }
    if ((*(uint *)(iVar2 + 0x10) & 0x100000) == 0) {
      bVar4 = (bool)(false);
    }
    else {
      iVar5 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 100)));
      if (iVar5 == 0) {
        bVar4 = (bool)(false);
      }
      else {
        bVar4 = (bool)(true);
      }
    }
    if (bVar4) {
      return 0;
    }
    iVar5 = (int)(fn_006385e0((undefined4 *)(iVar2)));
    if (iVar5 != 0) {
      return 0;
    }
    iVar5 = (int)(*(int *)(iVar2 + 0x4a));
    if (iVar5 > 0) {
      if (iVar5 - 1U < 0) {
        local_14 = (uint)(0xffffffff);
      }
      else {
        if (iVar5 < 0x20) {
          local_14 = (uint)(0xffffffff >> ((byte)iVar5 & 0x1f));
        }
        else {
          local_14 = (uint)(0);
        }
        local_14 = (uint)(~local_14);
      }
      iVar5 = (int)(*(int *)(param_1 + 0x66));
      iVar3 = (int)(*(int *)(param_1 + 0x58));
      bVar7 = (byte)((byte)iVar3);
      if (iVar5 < iVar3) {
        if (iVar5 + 1 < 0x20) {
          uVar6 = (uint)(0xffffffff >> ((byte)(iVar5 + 1) & 0x1f));
        }
        else {
          uVar6 = (uint)(0);
        }
        if (iVar3 < 0x20) {
          uVar8 = (uint)(0xffffffff >> (bVar7 & 0x1f));
        }
        else {
          uVar8 = (uint)(0);
        }
        uVar8 = (uint)(~uVar6 | uVar8);
      }
      else {
        if (iVar5 + 1 < 0x20) {
          uVar6 = (uint)(0xffffffff >> ((byte)(iVar5 + 1) & 0x1f));
        }
        else {
          uVar6 = (uint)(0);
        }
        if (iVar3 < 0x20) {
          uVar8 = (uint)(0xffffffff >> (bVar7 & 0x1f));
        }
        else {
          uVar8 = (uint)(0);
        }
        uVar8 = (uint)(~uVar6 & uVar8);
      }
      iVar9 = (int)(iVar5 + 1);
      if (iVar5 < iVar3) {
        if (iVar9 < 0x20) {
          uVar6 = (uint)(0xffffffff >> ((byte)iVar9 & 0x1f));
        }
        else {
          uVar6 = (uint)(0);
        }
        if (iVar3 < 0x20) {
          uVar10 = (uint)(0xffffffff >> (bVar7 & 0x1f));
        }
        else {
          uVar10 = (uint)(0);
        }
        uVar10 = (uint)(~uVar6 | uVar10);
      }
      else {
        if (iVar9 < 0x20) {
          uVar6 = (uint)(0xffffffff >> ((byte)iVar9 & 0x1f));
        }
        else {
          uVar6 = (uint)(0);
        }
        if (iVar3 < 0x20) {
          uVar10 = (uint)(0xffffffff >> (bVar7 & 0x1f));
        }
        else {
          uVar10 = (uint)(0);
        }
        uVar10 = (uint)(~uVar6 & uVar10);
      }
      bVar7 = (byte)((byte)*(undefined4 *)(param_1 + 0x4a));
      if ((local_14 & (uVar8 << (0x20 - bVar7 & 0x1f) | uVar10 >> (bVar7 & 0x1f))) == 0) {
        if (*(short *)(iVar2 + 0x30) != *(short *)(iVar2 + 0x3e)) {
          iVar5 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)));
          if (iVar5 == 0) {
            *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
            iVar5 = (int)(*(int *)(iVar2 + 0x40));
            if (iVar5 == 0) {
              CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
            }
            *(int *)(param_1 + 0x40) = iVar5;
            *(uint *)(param_1 + 0x4a) = *(int *)(param_1 + 0x4a) - *(int *)(iVar2 + 0x4a) & 0x1f;
            iVar5 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
            if ((iVar5 == 0) &&
               ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar2 + 0x30) >> 5) * 4) >>
                 ((byte)*(short *)(iVar2 + 0x30) & 0x1f) & 1) == 0)) {
              deletepcode((int)(iVar2));
            }
            return 1;
          }
        }
        sVar1 = (short)(*(short *)(iVar2 + 0x30));
        if ((sVar1 == *(short *)(param_1 + 0x30)) &&
           ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) {
          iVar5 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
          if (iVar5 == 0) {
            *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
            iVar5 = (int)(*(int *)(iVar2 + 0x40));
            if (iVar5 == 0) {
              CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
            }
            *(int *)(param_1 + 0x40) = iVar5;
            *(uint *)(param_1 + 0x4a) = *(int *)(param_1 + 0x4a) - *(int *)(iVar2 + 0x4a) & 0x1f;
            deletepcode((int)(iVar2));
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

undefined4 fn_00634ae0(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  short local_18;
  short local_16;
  undefined4 local_14;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if ((*(short *)(iVar2 + 0x28) == 0x67) && ((*(uint *)(iVar2 + 0xc) & 0x180) == 0)) {
    if ((*(uint *)(iVar2 + 0x10) & 0x100000) == 0) {
      bVar6 = (bool)(false);
    }
    else {
      iVar7 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x72)));
      if (iVar7 == 0) {
        bVar6 = (bool)(false);
      }
      else {
        bVar6 = (bool)(true);
      }
    }
    if ((!bVar6) && (iVar7 = fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)), iVar7 == 0) &&
       (sVar1 = *(short *)(iVar2 + 0x30), sVar1 != *(short *)(iVar2 + 0x3e) ||
       ((sVar1 == *(short *)(param_1 + 0x30) ||
        ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
       (iVar7 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)), iVar7 == 0)))) {
      iVar7 = (int)(*(int *)(param_1 + 0x58));
      iVar3 = (int)(*(int *)(param_1 + 0x66));
      local_14 = (undefined4)(*(undefined4 *)(param_1 + 0x4a));
      iVar4 = (int)(*(int *)(iVar2 + 0x66));
      iVar5 = (int)(*(int *)(iVar2 + 0x58));
      if (iVar4 < iVar5) {
        if (iVar4 + 1 < 0x20) {
          uVar10 = (uint)(0xffffffff >> ((char)iVar4 + 1U & 0x1f));
        }
        else {
          uVar10 = (uint)(0);
        }
        if (iVar5 < 0x20) {
          uVar9 = (uint)(0xffffffff >> ((byte)iVar5 & 0x1f));
        }
        else {
          uVar9 = (uint)(0);
        }
        uVar9 = (uint)(~uVar10 | uVar9);
      }
      else {
        if (iVar4 + 1 < 0x20) {
          uVar10 = (uint)(0xffffffff >> ((char)iVar4 + 1U & 0x1f));
        }
        else {
          uVar10 = (uint)(0);
        }
        if (iVar5 < 0x20) {
          uVar9 = (uint)(0xffffffff >> ((byte)iVar5 & 0x1f));
        }
        else {
          uVar9 = (uint)(0);
        }
        uVar9 = (uint)(~uVar10 & uVar9);
      }
      if (iVar3 < iVar7) {
        if (iVar3 + 1 < 0x20) {
          uVar10 = (uint)(0xffffffff >> ((char)iVar3 + 1U & 0x1f));
        }
        else {
          uVar10 = (uint)(0);
        }
        if (iVar7 < 0x20) {
          uVar8 = (uint)(0xffffffff >> ((byte)iVar7 & 0x1f));
        }
        else {
          uVar8 = (uint)(0);
        }
        uVar8 = (uint)(~uVar10 | uVar8);
      }
      else {
        if (iVar3 + 1 < 0x20) {
          uVar10 = (uint)(0xffffffff >> ((char)iVar3 + 1U & 0x1f));
        }
        else {
          uVar10 = (uint)(0);
        }
        if (iVar7 < 0x20) {
          uVar8 = (uint)(0xffffffff >> ((byte)iVar7 & 0x1f));
        }
        else {
          uVar8 = (uint)(0);
        }
        uVar8 = (uint)(~uVar10 & uVar8);
      }
      iVar7 = InstrSelection_GetMaskRange((int)((uVar9 >> (0x20 - (byte)local_14 & 0x1f) |
                           uVar9 << ((byte)local_14 & 0x1f)) & uVar8), (int)(&local_18), (int)(&local_16));
      if (iVar7 != 0) {
        if (*(short *)(param_1 + 0x28) == 0x69) {
          if (*(short *)(param_1 + 0x30) == *(short *)(iVar2 + 0x30)) {
            return 0;
          }
          if (((int)local_18 != *(int *)(param_1 + 0x58)) ||
             ((int)local_16 != *(int *)(param_1 + 0x66))) {
            return 0;
          }
        }
        *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
        iVar7 = (int)(*(int *)(iVar2 + 0x40));
        if (iVar7 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)(param_1 + 0x40) = iVar7;
        *(uint *)(param_1 + 0x4a) = *(int *)(param_1 + 0x4a) + *(int *)(iVar2 + 0x4a) & 0x1f;
        *(int *)(param_1 + 0x58) = (int)local_18;
        *(int *)(param_1 + 0x66) = (int)local_16;
        sVar1 = (short)(*(short *)(iVar2 + 0x30));
        if (((sVar1 == *(short *)(param_1 + 0x30)) ||
            ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
           (iVar7 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)), iVar7 == 0)) {
          deletepcode((int)(iVar2));
        }
        return 1;
      }
    }
  }
  if ((*(short *)(iVar2 + 0x28) == 0x8b) && (*(short *)(param_1 + 0x28) == 0x67) &&
     (iVar7 = fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)), iVar7 == 0)) {
    *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
    iVar7 = (int)(*(int *)(iVar2 + 0x40));
    if (iVar7 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    *(int *)(param_1 + 0x40) = iVar7;
    sVar1 = (short)(*(short *)(iVar2 + 0x30));
    if (((sVar1 == *(short *)(param_1 + 0x30)) ||
        ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
       ((*(uint *)(iVar2 + 0xc) & 0x180) == 0)) {
      if ((*(uint *)(iVar2 + 0x10) & 0x100000) == 0) {
        bVar6 = (bool)(false);
      }
      else {
        iVar7 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x72)));
        if (iVar7 == 0) {
          bVar6 = (bool)(false);
        }
        else {
          bVar6 = (bool)(true);
        }
      }
      if ((!bVar6) && (iVar7 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)), iVar7 == 0)) {
        deletepcode((int)(iVar2));
      }
    }
    return 1;
  }
  if ((*(short *)(param_1 + 0x28) == 0x67) && (*(short *)(iVar2 + 0x28) != 0x8c) &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0) && (*(int *)(param_1 + 0x4a) == 0)) {
    iVar7 = (int)(*(int *)(param_1 + 0x66));
    iVar3 = (int)(*(int *)(param_1 + 0x58));
    if (iVar7 < iVar3) {
      if (iVar7 + 1 < 0x20) {
        uVar10 = (uint)(0xffffffff >> ((byte)(iVar7 + 1) & 0x1f));
      }
      else {
        uVar10 = (uint)(0);
      }
      if (iVar3 < 0x20) {
        uVar9 = (uint)(0xffffffff >> ((byte)iVar3 & 0x1f));
      }
      else {
        uVar9 = (uint)(0);
      }
      uVar9 = (uint)(~uVar10 | uVar9);
    }
    else {
      if (iVar7 + 1 < 0x20) {
        uVar10 = (uint)(0xffffffff >> ((byte)(iVar7 + 1) & 0x1f));
      }
      else {
        uVar10 = (uint)(0);
      }
      if (iVar3 < 0x20) {
        uVar9 = (uint)(0xffffffff >> ((byte)iVar3 & 0x1f));
      }
      else {
        uVar9 = (uint)(0);
      }
      uVar9 = (uint)(~uVar10 & uVar9);
    }
    uVar10 = (uint)(fn_00632ea0((int)(iVar2), (short)((int)*(short *)(param_1 + 0x3e))));
    if ((~uVar9 & uVar10) == 0) {
      if (((*(uint *)(native_liveness_bank4 + ((int)*(short *)(param_1 + 0x3e) >> 5) * 4) >>
            ((byte)*(short *)(param_1 + 0x3e) & 0x1f) & 1) == 0) &&
         (iVar7 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(param_1 + 0x3a)), iVar7 == 0) &&
         (iVar7 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)), iVar7 == 0 &&
         (iVar7 = fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)), iVar7 == 0 &&
         ((*(uint *)(iVar2 + 0xc) & 0x180) == 0))) && ((*(uint *)(param_1 + 0x10) & 0x100000) == 0)
         && (*(short *)(iVar2 + 0x28) != 0x69 && ((*(ushort *)(iVar2 + 0x2e) & 1) == 0))) {
        *(undefined4 *)(iVar2 + 0x2c) = *(undefined4 *)(param_1 + 0x2c);
        *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(param_1 + 0x30);
        *(undefined4 *)(iVar2 + 0x34) = *(undefined4 *)(param_1 + 0x34);
        *(undefined2 *)(iVar2 + 0x38) = *(undefined2 *)(param_1 + 0x38);
        deletepcode((int)(param_1));
      }
      else {
        change_opcode((int)(param_1), (short)(0x8b));
        uVar10 = (uint)(*(uint *)(param_1 + 0x10) & 0x100000);
        if (uVar10 == 0) {
          change_num_operands((int)(param_1), (int)(2));
          *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x10;
        }
        else {
          if ((uVar10 == 0) || ((*(uint *)native_liveness_mask0 & 1) == 0)) {
            bVar6 = (bool)(false);
          }
          else {
            bVar6 = (bool)(true);
          }
          if (bVar6) {
            *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x72);
            *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x76);
            *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x7a);
            *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(param_1 + 0x7e);
            change_num_operands((int)(param_1), (int)(3));
          }
          else {
            fn_00596280((int)(param_1));
            change_num_operands((int)(param_1), (int)(2));
            *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x10;
          }
        }
      }
      return 1;
    }
  }
  return 0;
}

undefined4 fn_006350e0(int param_1)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  int interveningOffset;
  int loadOffset;
  int loadSize;

  /* Native 0x635688 reaches the overlap check without assigning ESI/EDI
   * when memory objects differ. These values persist between intervening
   * stores. Snapshot the incoming registers, then retain the native conditional
   * assignments below; uninitialized C locals do not preserve this behavior. */
  asm { mov interveningOffset, esi }
  asm { mov loadOffset, edi }

  iVar2 = (int)(*(int *)(param_1 + 0x32));
  if (iVar2 == 0) {
    return 0;
  }
  if ((*(uint *)(param_1 + 0xc) & 0x180) != 0 || (*(uint *)(param_1 + 0x10) & 0x8000) != 0) {
    return 0;
  }
  if ((*(uint *)(iVar2 + 0xc) & 0x180) != 0 || (*(uint *)(iVar2 + 0x10) & 0x8000) != 0) {
    return 0;
  }
  if (((*(uint *)(iVar2 + 0xc) & 2) == 0) || (*(char *)(iVar2 + 0x3a) != '\0') ||
     (*(char *)(iVar2 + 0x3b) != '\x04') ||
     (*(short *)(iVar2 + 0x3e) != *(short *)(param_1 + 0x3e) ||
     (*(char *)(iVar2 + 0x48) != *(char *)(param_1 + 0x48)) ||
     (iVar6 = fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x3a)), iVar6 != 0))) {
    return 0;
  }
  cVar1 = (char)(*(char *)(param_1 + 0x48));
  if (cVar1 == '\x02') {
    if (*(int *)(param_1 + 0x4a) != *(int *)(iVar2 + 0x4a)) {
      return 0;
    }
  }
  else if (cVar1 == '\x04') {
    if ((*(int *)(param_1 + 0x4a) != *(int *)(iVar2 + 0x4a)) ||
       (*(int *)(param_1 + 0x4e) != *(int *)(iVar2 + 0x4e))) {
      return 0;
    }
  }
  else {
    if ((cVar1 != '\0') || (*(char *)(param_1 + 0x49) != '\x04')) {
      return 0;
    }
    if ((*(short *)(param_1 + 0x4c) != *(short *)(iVar2 + 0x4c)) ||
       (iVar6 = fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x48)), iVar6 != 0)) {
      return 0;
    }
  }
  bVar5 = (bool)(false);
  iVar6 = (int)((int)*(short *)(iVar2 + 0x28));
  bVar3 = (bool)(false);
  bVar4 = (bool)(false);
  if (iVar6 == 0x15) {
label_00635265:
    loadSize = (int)(1);
  }
  else {
    if (iVar6 == 0x17) {
      bVar3 = (bool)(true);
      goto label_00635265;
    }
    if (iVar6 == 0x19) {
label_00635275:
      loadSize = (int)(2);
    }
    else {
      if (iVar6 == 0x1b) {
label_00635270:
        bVar3 = (bool)(true);
        goto label_00635275;
      }
      if (iVar6 == 0x1d) goto label_00635275;
      if (iVar6 == 0x1f) goto label_00635270;
      if (iVar6 == 0x22) {
label_00635285:
        loadSize = (int)(4);
      }
      else {
        if (iVar6 == 0x24) {
          bVar3 = (bool)(true);
          goto label_00635285;
        }
        if (iVar6 == 0x8e) {
label_00635295:
          bVar4 = (bool)(true);
          loadSize = (int)(4);
        }
        else {
          if (iVar6 == 0x90) {
            bVar3 = (bool)(true);
            goto label_00635295;
          }
          if (iVar6 == 0x92) {
label_006352a8:
            bVar4 = (bool)(true);
            loadSize = (int)(8);
          }
          else {
            if (iVar6 == 0x94) {
              bVar3 = (bool)(true);
              goto label_006352a8;
            }
            if (iVar6 - 0xf9U > 1) {
              return 0;
            }
            bVar3 = (bool)(true);
            bVar5 = (bool)(true);
            loadSize = (int)(0x10);
          }
        }
      }
    }
  }
  iVar6 = (int)((int)*(short *)(param_1 + 0x28));
  if (iVar6 != 0x28) {
    if (iVar6 != 0x2a) {
      if (iVar6 != 0x2c) {
        if (iVar6 != 0x2e) {
          if (iVar6 != 0x31) {
            if (iVar6 != 0x33) {
              if (iVar6 != 0x96) {
                if (iVar6 != 0x98) {
                  if (iVar6 != 0x9a) {
                    if (iVar6 != 0x9c) {
                      if (iVar6 - 0xfeU > 1) {
                        return 0;
                      }
                      if (!bVar3) {
                        return 0;
                      }
                      if (!bVar5) {
                        return 0;
                      }
                      if (loadSize != 0x10) {
                        return 0;
                      }
                      goto label_00635450;
                    }
                    if (!bVar3) {
                      return 0;
                    }
                  }
                  if (!bVar4) {
                    return 0;
                  }
                  if (loadSize != 8) {
                    return 0;
                  }
                  goto label_00635450;
                }
                if (!bVar3) {
                  return 0;
                }
              }
              if (!bVar4) {
                return 0;
              }
              if (loadSize != 4) {
                return 0;
              }
              goto label_00635450;
            }
            if (!bVar3) {
              return 0;
            }
          }
          if (bVar4) {
            return 0;
          }
          if (loadSize != 4) {
            return 0;
          }
          goto label_00635450;
        }
        if (!bVar3) {
          return 0;
        }
      }
      if (bVar4) {
        return 0;
      }
      if (loadSize != 2) {
        return 0;
      }
      goto label_00635450;
    }
    if (!bVar3) {
      return 0;
    }
  }
  if (bVar4) {
    return 0;
  }
  if (loadSize != 1) {
    return 0;
  }
label_00635450:
  iVar6 = (int)(*(int *)(param_1 + 4));
  do {
    if ((iVar6 == 0) || (iVar6 == iVar2)) {
      deletepcode((int)(param_1));
      return 1;
    }
    if ((*(uint *)(iVar6 + 0xc) & 0x100) != 0) {
      return 0;
    }
    if ((*(uint *)(iVar6 + 0xc) & 4) != 0) {
      if (*(short *)(iVar6 + 0x3e) != *(short *)(param_1 + 0x3e)) {
        return 0;
      }
      cVar1 = (char)(*(char *)(iVar6 + 0x48));
      if (cVar1 != *(char *)(iVar2 + 0x48)) {
        return 0;
      }
      if (cVar1 == '\x04') {
        if (*(int *)(param_1 + 0x4e) == *(int *)(iVar6 + 0x4e)) {
          loadOffset = (int)(*(int *)(iVar2 + 0x4a));
          if (*(int *)(param_1 + 0x4a) == loadOffset) {
            return 0;
          }
          interveningOffset = (int)(*(int *)(iVar6 + 0x4a));
        }
      }
      else {
        if (cVar1 != '\x02') {
          return 0;
        }
        if (*(short *)(param_1 + 0x3e) != *(short *)(iVar6 + 0x3e)) {
          return 0;
        }
        interveningOffset = (int)(*(int *)(iVar6 + 0x4a));
        if (*(int *)(param_1 + 0x4a) == interveningOffset) {
          return 0;
        }
        loadOffset = (int)(*(int *)(iVar2 + 0x4a));
      }
      iVar7 = (int)((int)*(short *)(iVar6 + 0x28));
      if ((iVar7 == 0x28) || (iVar7 == 0x2a)) {
        iVar7 = (int)(1);
      }
      else if ((iVar7 == 0x2c) || (iVar7 == 0x2e)) {
        iVar7 = (int)(2);
      }
      else if ((iVar7 == 0x31) || (iVar7 == 0x33) || (iVar7 == 0x96) || (iVar7 == 0x98)) {
        iVar7 = (int)(4);
      }
      else if ((iVar7 == 0x9a) || (iVar7 == 0x9c)) {
        iVar7 = (int)(8);
      }
      else {
        if (iVar7 - 0xfeU > 1) {
          return 0;
        }
        iVar7 = (int)(0x10);
      }
      if (interveningOffset < loadOffset) {
        if (loadOffset < iVar7 + interveningOffset) {
          return 0;
        }
      }
      else if (interveningOffset < loadOffset + loadSize) {
        return 0;
      }
    }
    iVar6 = (int)(*(int *)(iVar6 + 4));
  } while( true );
}

undefined4 fn_00635700(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if (((*(uint *)(iVar2 + 0xc) & 2) != 0) && (*(char *)(iVar2 + 0x2d) == '\x03') &&
     (sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x3e)) &&
     ((*(uint *)(native_liveness_bank3 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0 &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0 && (*(uint *)(param_1 + 0x10) & 0x100000) == 0))) {
    iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
    if (iVar3 == 0) {
      iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
      if (iVar3 == 0) {
        iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
        if (iVar3 == 0) {
          *(undefined2 *)(iVar2 + 0x30) = *(undefined2 *)(param_1 + 0x30);
          deletepcode((int)(param_1));
          return 1;
        }
      }
    }
  }
  return 0;
}

undefined4 fn_006357b0(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if (((*(uint *)(iVar2 + 0xc) & 2) != 0) && (*(char *)(iVar2 + 0x2d) == '\x04') &&
     (sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x3e)) &&
     ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0 &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0 && (*(uint *)(param_1 + 0x10) & 0x100000) == 0))) {
    iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
    if (iVar3 == 0) {
      iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
      if (iVar3 == 0) {
        iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
        if (iVar3 == 0) {
          *(undefined2 *)(iVar2 + 0x30) = *(undefined2 *)(param_1 + 0x30);
          deletepcode((int)(param_1));
          return 1;
        }
      }
    }
  }
  return 0;
}

undefined4 fn_00635860(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  sVar1 = (short)(*(short *)(iVar2 + 0x28));
  if ((*(uint *)(iVar2 + 0xc) & 0x180) != 0) {
    return 0;
  }
  if (((ushort)(sVar1 - 0x160U) < 3) &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0 && (*(uint *)(param_1 + 0x10) & 0x100000) == 0)) {
    *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(iVar2 + 0x3a);
    *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(iVar2 + 0x3e);
    *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(iVar2 + 0x42);
    *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(iVar2 + 0x46);
    change_opcode((int)(param_1), (short)((int)sVar1));
    if ((*(uint *)(native_liveness_bank2 + ((int)*(short *)(iVar2 + 0x30) >> 5) * 4) >>
         ((byte)*(short *)(iVar2 + 0x30) & 0x1f) & 1) == 0) {
      iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
      if (iVar3 == 0) {
        deletepcode((int)(iVar2));
      }
    }
    return 1;
  }
  return 0;
}

undefined4 fn_00635920(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if (iVar2 == 0) {
    CError_Internal((const char *)(peepholeFilename), (int)(0x97f));
  }
  if ((*(char *)(iVar2 + 0x2c) == '\0') && (*(char *)(iVar2 + 0x2d) == '\x04') &&
     (sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
     ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
     ((*(ushort *)(iVar2 + 0x2e) & 3) == 2 && ((*(uint *)(iVar2 + 0xc) & 0x180) == 0) &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0 && (*(uint *)(param_1 + 0x10) & 0x100000) == 0) &&
     (iVar3 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)), iVar3 == 0 &&
     (iVar3 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)), iVar3 == 0))) &&
     (iVar3 = fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)), iVar3 == 0)) {
    *(undefined4 *)(iVar2 + 0x2c) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(iVar2 + 0x34) = *(undefined4 *)(param_1 + 0x34);
    *(undefined2 *)(iVar2 + 0x38) = *(undefined2 *)(param_1 + 0x38);
    deletepcode((int)(param_1));
    return 1;
  }
  return 0;
}

undefined4 fn_00635a20(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x4e));
  if ((*(short *)(iVar2 + 0x28) == 0x8d) &&
     ((sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
      ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
     ((*(uint *)(iVar2 + 0xc) & 0x180) == 0 && (*(uint *)(iVar2 + 0x10) & 0x100000) == 0))) {
    iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)));
    if (iVar3 == 0) {
      iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
      if (iVar3 == 0) {
        *(undefined2 *)(param_1 + 0x4c) = *(undefined2 *)(iVar2 + 0x3e);
        iVar3 = (int)(*(int *)(iVar2 + 0x40));
        if (iVar3 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)(param_1 + 0x4e) = iVar3;
        change_opcode((int)(param_1), (short)(0x62));
        deletepcode((int)(iVar2));
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_00635ae0(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  if (*(int *)(param_1 + 0x3c) == 2) {
    iVar2 = (int)(*(int *)(param_1 + 0x32));
    sVar1 = (short)(*(short *)(iVar2 + 0x28));
    if (((((sVar1 == 0x52) || (sVar1 == 0x54)) && (*(int *)(iVar2 + 0x4a) > -1) &&
         (*(int *)(iVar2 + 0x4a) < 0x80)) ||
        ((ushort)(sVar1 - 100U) < 2 && ((*(uint *)(iVar2 + 0x10) & 0x100000) != 0))) &&
       (iVar3 = *(int *)(iVar2 + 0x40), *(short *)(iVar3 + 0x28) == 100 &&
       (*(short *)(*(int *)(iVar3 + 0x40) + 0x28) == 0x15 &&
       ((*(uint *)((&native_liveness_bank0)[*(char *)(param_1 + 0x2d) * 3] +
                  ((int)*(short *)(param_1 + 0x30) >> 5) * 4) >>
         ((byte)*(short *)(param_1 + 0x30) & 0x1f) & 1) == 0)) &&
       ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar3 + 0x30) >> 5) * 4) >>
         ((byte)*(short *)(iVar3 + 0x30) & 0x1f) & 1) == 0 &&
       (iVar4 = fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar3 + 0x2c)), iVar4 == 0 &&
       (iVar4 = fn_00596b50((int)(iVar2), (int)(iVar3), (int)(iVar3 + 0x2c)), iVar4 == 0) &&
       (iVar4 = fn_00596bd0((int)(iVar2), (int)(iVar3), (int)(iVar3 + 0x3a)), iVar4 == 0))))) {
      *(undefined2 *)(iVar2 + 0x3e) = *(undefined2 *)(iVar3 + 0x3e);
      iVar4 = (int)(*(int *)(iVar3 + 0x40));
      if (iVar4 == 0) {
        CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
      }
      *(int *)(iVar2 + 0x40) = iVar4;
      deletepcode((int)(iVar3));
      return 1;
    }
  }
  return 0;
}

undefined4 fn_00635c20(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;

  if ((*(int *)(param_1 + 0x3c) == 2) &&
     (iVar1 = *(int *)(param_1 + 0x32), *(short *)(iVar1 + 0x28) == 0x54) &&
     (*(short *)(iVar1 + 0x30) == 0) &&
     (*(int *)(iVar1 + 0x4a) == 0 &&
     (uVar2 = *(undefined4 *)(iVar1 + 0x40), (*(uint *)(iVar1 + 0x10) & 0xe0000000) == 0x80000000))
     && (iVar3 = fn_005960b0((int)(uVar2)), iVar3 != 0 &&
        (iVar3 = fn_00596b50((int)(iVar1), (int)(uVar2), (int)(iVar1 + 0x2c)), iVar3 == 0 &&
        (iVar3 = fn_00596bd0((int)(iVar1), (int)(uVar2), (int)(iVar1 + 0x2c)), iVar3 == 0)))) {
    pcsetrecordbit((int)(uVar2));
    iVar3 = (int)(*(int *)(iVar1 + 0x40));
    if (iVar3 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    *(int *)(param_1 + 0x32) = iVar3;
    deletepcode((int)(iVar1));
    return 1;
  }
  return 0;
}

undefined4 fn_00635ce0(int param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;

  if ((*(int *)(param_1 + 0x3c) == 2) &&
     (iVar3 = *(int *)(param_1 + 0x32), *(short *)(iVar3 + 0x30) == *(short *)(param_1 + 0x30))) {
    switch(*(undefined2 *)(iVar3 + 0x28)) {
    case 0x52:
      uVar4 = (uint)((uint)*(short *)(iVar3 + 0x4a));
      break;
    default:
      return 0;
    case 0x54:
      uVar4 = (uint)((uint)*(ushort *)(iVar3 + 0x4a));
    }
    iVar3 = (int)(*(int *)(iVar3 + 0x40));
    if ((*(short *)(iVar3 + 0x28) == 0x89) && (*(char *)(iVar3 + 0x3a) == '\x02')) {
      uVar2 = (uint)((uint)*(short *)(iVar3 + 0x3c));
      sVar1 = (short)(*(short *)(param_1 + 0x28));
      if (((sVar1 == 5) && (uVar4 == uVar2)) || (sVar1 == 8 && (uVar4 != uVar2))) {
        *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x48);
        *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x4c);
        *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x50);
        *(undefined2 *)(param_1 + 0x38) = *(undefined2 *)(param_1 + 0x54);
        change_num_operands((int)(param_1), (int)(1));
        change_opcode((int)(param_1), (short)(0));
        iVar3 = (int)(**(int **)(param_1 + 8));
        if (iVar3 != *(int *)(*(int *)(param_1 + 0x2e) + 4)) {
          fn_00582100((int)(*(int **)(param_1 + 8)), (int)(iVar3));
        }
        return 1;
      }
      if ((((sVar1 == 5) && (uVar4 != uVar2)) || (sVar1 == 8 && (uVar4 == uVar2))) &&
         (iVar3 = fn_0058aec0((int)(param_1)), iVar3 != 0 && (*(int *)(iVar3 + 2) != 0))) {
        iVar3 = (int)(*(int *)(*(int *)(iVar3 + 2) + 4));
        if (**(int **)(param_1 + 8) != iVar3) {
          fn_00582100((int)(*(int **)(param_1 + 8)), (int)(iVar3));
        }
        deletepcode((int)(param_1));
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_00635e30(undefined4 *param_1)

{
  short sVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;

  if (*(char *)(param_1 + 0x12) != '\x02') {
    return 0;
  }
  sVar1 = (short)(*(short *)((int)param_1 + 0x3e));
  iVar4 = (int)(fn_00638690((int)(param_1[2]), (undefined4 *)(*param_1), (int)(0), (int)(0), (int)(0), (int)(0), (int)(0)));
  if (iVar4 == 0) {
    return 0;
  }
  uVar2 = (uint)(*(uint *)((int)param_1 + 0x4a));
  if (uVar2 != (uVar2 & 0xfff)) {
    return 0;
  }
  puVar3 = (undefined4*)((undefined4 *)*param_1);
  do {
    if (puVar3 == (undefined4 *)0x0) {
      return 0;
    }
    iVar4 = (int)((int)*(short *)((int)puVar3 + 0x2a));
    pcVar5 = (char*)((char *)(puVar3 + 0xb));
    while (iVar4 != 0) {
      iVar4 = (int)(iVar4 - 1);
      if ((*pcVar5 == '\0') && (pcVar5[1] == '\x04') && (*(short *)(pcVar5 + 4) == sVar1) &&
         ((*(ushort *)(pcVar5 + 2) & 1) != 0)) {
        return 0;
      }
      if ((*pcVar5 == '\0') && (pcVar5[1] == '\x04') &&
         (*(short *)(pcVar5 + 4) == sVar1 && ((*(ushort *)(pcVar5 + 2) & 2) != 0))) {
        if (*(short *)(puVar3 + 10) != 0x3f) {
          return 0;
        }
        if (*(char *)(puVar3 + 0x12) == '\x02') {
          if ((uVar2 == *(uint *)((int)puVar3 + 0x4a)) &&
             (sVar1 = *(short *)(puVar3 + 0xc), sVar1 == *(short *)((int)puVar3 + 0x3e)) &&
             (*(char *)((int)param_1 + 0x2d) != *(char *)((int)param_1 + 0x3b) ||
             (*(short *)(param_1 + 0xc) != *(short *)((int)param_1 + 0x3e)))) {
            if ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)
            {
              param_1[0x12] = (undefined4)(puVar3[0x12]);
              param_1[0x13] = (undefined4)(puVar3[0x13]);
              param_1[0x14] = (undefined4)(puVar3[0x14]);
              *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(puVar3 + 0x15);
            }
            else {
              *(ushort *)(param_1 + 0xf) = *(ushort *)(param_1 + 0xf) | 2;
              param_1[0x12] = (undefined4)(puVar3[0x12]);
              param_1[0x13] = (undefined4)(puVar3[0x13]);
              param_1[0x14] = (undefined4)(puVar3[0x14]);
              *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(puVar3 + 0x15);
              change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 1)));
            }
            change_opcode((int)(puVar3), (short)(0x8c));
            change_num_operands((int)(puVar3), (int)(0));
            deletepcode((int)(puVar3));
            return 1;
          }
          return 0;
        }
        return 0;
      }
      pcVar5 = (char*)(pcVar5 + 0xe);
    }
    puVar3 = (undefined4*)((undefined4 *)*puVar3);
  } while( true );
}

undefined4 fn_00636050(undefined4 *param_1)

{
  short sVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;

  if (*(char *)(param_1 + 0x12) != '\x02') {
    return 0;
  }
  sVar1 = (short)(*(short *)((int)param_1 + 0x3e));
  iVar3 = (int)(fn_00638690((int)(param_1[2]), (undefined4 *)(*param_1), (int)(0), (int)(0), (int)(0), (int)(0), (int)(0)));
  if (iVar3 == 0) {
    return 0;
  }
  puVar2 = (undefined4*)((undefined4 *)*param_1);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      return 0;
    }
    iVar3 = (int)((int)*(short *)((int)puVar2 + 0x2a));
    pcVar4 = (char*)((char *)(puVar2 + 0xb));
    while (iVar3 != 0) {
      iVar3 = (int)(iVar3 - 1);
      if ((*pcVar4 == '\0') && (pcVar4[1] == '\x04') && (*(short *)(pcVar4 + 4) == sVar1) &&
         ((*(ushort *)(pcVar4 + 2) & 1) != 0)) {
        return 0;
      }
      if ((*pcVar4 == '\0') && (pcVar4[1] == '\x04') &&
         (*(short *)(pcVar4 + 4) == sVar1 && ((*(ushort *)(pcVar4 + 2) & 2) != 0))) {
        if (*(short *)(puVar2 + 10) != 0x3f) {
          return 0;
        }
        if (*(char *)(puVar2 + 0x12) == '\x02') {
          if ((*(int *)((int)param_1 + 0x4a) == *(int *)((int)puVar2 + 0x4a)) &&
             (sVar1 = *(short *)(puVar2 + 0xc), sVar1 == *(short *)((int)puVar2 + 0x3e)) &&
             (*(char *)((int)param_1 + 0x2d) != *(char *)((int)param_1 + 0x3b) ||
             (*(short *)(param_1 + 0xc) != *(short *)((int)param_1 + 0x3e)))) {
            if ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)
            {
              param_1[0x12] = (undefined4)(puVar2[0x12]);
              param_1[0x13] = (undefined4)(puVar2[0x13]);
              param_1[0x14] = (undefined4)(puVar2[0x14]);
              *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(puVar2 + 0x15);
            }
            else {
              *(ushort *)(param_1 + 0xf) = *(ushort *)(param_1 + 0xf) | 2;
              param_1[0x12] = (undefined4)(puVar2[0x12]);
              param_1[0x13] = (undefined4)(puVar2[0x13]);
              param_1[0x14] = (undefined4)(puVar2[0x14]);
              *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(puVar2 + 0x15);
              change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 1)));
            }
            change_opcode((int)(puVar2), (short)(0x8c));
            change_num_operands((int)(puVar2), (int)(0));
            deletepcode((int)(puVar2));
            return 1;
          }
          return 0;
        }
        return 0;
      }
      pcVar4 = (char*)(pcVar4 + 0xe);
    }
    puVar2 = (undefined4*)((undefined4 *)*puVar2);
  } while( true );
}

undefined4 fn_00636220(int param_1)

{
  int iVar1;
  int iVar2;

  iVar1 = (int)(*(int *)(param_1 + 0x40));
  if (iVar1 == 0) {
    return 0;
  }
  if ((*(char *)(param_1 + 0x48) == '\x02') && (*(char *)(iVar1 + 0x48) == '\x02') &&
     (*(short *)(iVar1 + 0x28) == 0x3f) &&
     (*(short *)(iVar1 + 0x30) == *(short *)(iVar1 + 0x3e) &&
     (*(char *)(param_1 + 0x2d) != *(char *)(param_1 + 0x3b) ||
     (*(short *)(param_1 + 0x30) != *(short *)(param_1 + 0x3e)))) &&
     (iVar2 = fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)), iVar2 == 0 &&
     (iVar2 = is_valid_displ((int)(param_1), (int)(0), (int)(*(int *)(param_1 + 0x4a) + *(int *)(iVar1 + 0x4a))),
     iVar2 != 0))) {
    if (*(int *)(param_1 + 0x4a) + *(int *)(iVar1 + 0x4a) == 0) {
      *(ushort *)(param_1 + 0x3c) = *(ushort *)(param_1 + 0x3c) & 0xfffd;
      *(undefined4 *)(param_1 + 0x4a) = 0;
      change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 0x28) - 1)));
    }
    else {
      *(int *)(param_1 + 0x4a) = *(int *)(param_1 + 0x4a) + *(int *)(iVar1 + 0x4a);
    }
    iVar2 = (int)(*(int *)(iVar1 + 0x40));
    if (iVar2 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    *(int *)(param_1 + 0x40) = iVar2;
    deletepcode((int)(iVar1));
    return 1;
  }
  return 0;
}

undefined4 fn_00636310(undefined4 *param_1)

{
  int iVar1;
  int iVar2;

  iVar1 = (int)(param_1[0x10]);
  if (iVar1 == 0) {
    return 0;
  }
  if ((param_1[4] & 0x800) != 0) {
    CError_Internal((const char *)(peepholeFilename), (int)(0x77b));
  }
  if ((*(char *)(param_1 + 0x12) != '\x02') || (*(int *)((int)param_1 + 0x4a) != 0)) {
    return 0;
  }
  if ((*(uint *)(iVar1 + 0xc) & 0x180) != 0 || (*(uint *)(iVar1 + 0x10) & 0x100000) != 0) {
    return 0;
  }
  if ((*(short *)(iVar1 + 0x28) == 0x3c) &&
     ((*(char *)(param_1 + 0xb) != '\0' || (*(char *)((int)param_1 + 0x2d) != '\x04') ||
      (*(short *)(param_1 + 0xc) != *(short *)((int)param_1 + 0x3e))) &&
     (iVar2 = fn_00596bd0((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x48)), iVar2 == 0 &&
     (iVar2 = fn_00596bd0((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x3a)), iVar2 == 0)))) {
    if (*(short *)(iVar1 + 0x30) == *(short *)(iVar1 + 0x3e)) {
      iVar2 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)));
      if ((iVar2 == 0) &&
         ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
           ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0 ||
         (iVar2 = fn_00638690((int)(param_1[2]), (undefined4 *)(*param_1), (int)(0), (int)(0), (int)(0), (int)(0), (int)(0)), iVar2 != 0))) {
        change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 2)));
        if ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
             ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0) {
          param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x48));
          param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x4c));
          param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x50));
          *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x54);
        }
        else {
          change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 1)));
          *(ushort *)(param_1 + 0xf) = *(ushort *)(param_1 + 0xf) | 2;
          param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x48));
          param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x4c));
          param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x50));
          *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x54);
        }
        iVar2 = (int)(*(int *)(iVar1 + 0x40));
        if (iVar2 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        param_1[0x10] = (undefined4)(iVar2);
        iVar2 = (int)(*(int *)(iVar1 + 0x4e));
        if (iVar2 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)((int)param_1 + 0x4e) = iVar2;
        deletepcode((int)(iVar1));
        return 1;
      }
    }
    else {
      if (*(short *)(iVar1 + 0x30) != *(short *)(iVar1 + 0x4c)) {
        if (*(short *)(iVar1 + 0x3e) == 0) {
          if (*(short *)(iVar1 + 0x4c) == 0) {
            return 0;
          }
          *(undefined4 *)((int)param_1 + 0x3a) = *(undefined4 *)(iVar1 + 0x48);
          *(undefined4 *)((int)param_1 + 0x3e) = *(undefined4 *)(iVar1 + 0x4c);
          *(undefined4 *)((int)param_1 + 0x42) = *(undefined4 *)(iVar1 + 0x50);
          *(undefined2 *)((int)param_1 + 0x46) = *(undefined2 *)(iVar1 + 0x54);
          param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x3a));
          param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x3e));
          param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x42));
          *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x46);
          change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 2)));
        }
        else {
          *(undefined4 *)((int)param_1 + 0x3a) = *(undefined4 *)(iVar1 + 0x3a);
          *(undefined4 *)((int)param_1 + 0x3e) = *(undefined4 *)(iVar1 + 0x3e);
          *(undefined4 *)((int)param_1 + 0x42) = *(undefined4 *)(iVar1 + 0x42);
          *(undefined2 *)((int)param_1 + 0x46) = *(undefined2 *)(iVar1 + 0x46);
          param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x48));
          param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x4c));
          param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x50));
          *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x54);
          change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 2)));
        }
        iVar2 = (int)(*(int *)(iVar1 + 0x40));
        if (iVar2 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        param_1[0x10] = (undefined4)(iVar2);
        iVar1 = (int)(*(int *)(iVar1 + 0x4e));
        if (iVar1 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)((int)param_1 + 0x4e) = iVar1;
        return 1;
      }
      iVar2 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)));
      if ((iVar2 == 0) &&
         ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
           ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0 ||
         (iVar2 = fn_00638690((int)(param_1[2]), (undefined4 *)(*param_1), (int)(0), (int)(0), (int)(0), (int)(0), (int)(0)), iVar2 != 0))) {
        change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 2)));
        if ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
             ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0) {
          param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x3a));
          param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x3e));
          param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x42));
          *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x46);
        }
        else {
          change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 1)));
          *(ushort *)(param_1 + 0xf) = *(ushort *)(param_1 + 0xf) | 2;
          param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x3a));
          param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x3e));
          param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x42));
          *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x46);
        }
        iVar2 = (int)(*(int *)(iVar1 + 0x4e));
        if (iVar2 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        param_1[0x10] = (undefined4)(iVar2);
        iVar2 = (int)(*(int *)(iVar1 + 0x40));
        if (iVar2 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)((int)param_1 + 0x4e) = iVar2;
        deletepcode((int)(iVar1));
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_00636700(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar1 = (int)(*(int *)(param_1 + 0x4e));
  if (iVar1 == 0) {
    return 0;
  }
  if ((*(short *)(iVar1 + 0x28) == 0x3f) && (*(short *)(param_1 + 0x3e) == 0) &&
     (*(short *)(iVar1 + 0x30) == *(short *)(param_1 + 0x4c))) {
    iVar2 = (int)(fn_00596bd0((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x3a)));
    if (iVar2 == 0) {
      if (*(char *)(iVar1 + 0x48) == '\x04') {
        if (*(char *)(*(int *)(iVar1 + 0x4e) + 2) == '\x01') {
          iVar3 = (int)(local_offset_32((int)(*(int *)(iVar1 + 0x4e))));
          iVar2 = (int)(*(int *)(iVar1 + 0x4a));
          iVar4 = (int)(local_offset_32((int)(*(undefined4 *)(iVar1 + 0x4e))));
          if ((iVar4 + *(int *)(iVar1 + 0x4a) & 0xfffU) == iVar3 + iVar2) {
            *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(iVar1 + 0x3a);
            *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(iVar1 + 0x3e);
            *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(iVar1 + 0x42);
            *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(iVar1 + 0x46);
            *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(iVar1 + 0x48);
            *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar1 + 0x4c);
            *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar1 + 0x50);
            *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(iVar1 + 0x54);
            *(undefined1 *)(param_1 + 0x49) = 0xf;
            change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 0x28) - 2)));
            iVar2 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)));
            if ((iVar2 == 0) &&
               ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
                 ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0)) {
              deletepcode((int)(iVar1));
            }
            return 1;
          }
        }
      }
      else if (*(uint *)(iVar1 + 0x4a) == (*(uint *)(iVar1 + 0x4a) & 0xfff)) {
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(iVar1 + 0x3a);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(iVar1 + 0x3e);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(iVar1 + 0x42);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(iVar1 + 0x46);
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(iVar1 + 0x48);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar1 + 0x4c);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar1 + 0x50);
        *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(iVar1 + 0x54);
        change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 0x28) - 2)));
        iVar2 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)));
        if ((iVar2 == 0) &&
           ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
             ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0)) {
          deletepcode((int)(iVar1));
        }
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_006368c0(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;

  iVar1 = (int)(param_1[0x10]);
  if (iVar1 == 0) {
    return 0;
  }
  if ((param_1[4] & 0x800) != 0) {
    CError_Internal((const char *)(peepholeFilename), (int)(0x679));
  }
  if ((*(short *)(iVar1 + 0x28) == 0x3f) && (*(char *)(param_1 + 0x12) == '\x02')) {
    if ((*(int *)((int)param_1 + 0x4a) == 0) &&
       (*(short *)(iVar1 + 0x30) == *(short *)(iVar1 + 0x3e)) &&
       (iVar2 = fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)), iVar2 == 0 &&
       ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
         ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0 ||
       (iVar2 = fn_00638690((int)(param_1[2]), (undefined4 *)(*param_1), (int)(0), (int)(0), (int)(0), (int)(0), (int)(0)), iVar2 != 0))) &&
       (*(char *)(param_1 + 0xb) != '\0' ||
       (*(char *)((int)param_1 + 0x2d) != '\x04' ||
       (*(short *)(param_1 + 0xc) != *(short *)((int)param_1 + 0x3e))))) {
      if ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
           ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0) {
        param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x48));
        param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x4c));
        param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x50));
        *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x54);
      }
      else {
        *(ushort *)(param_1 + 0xf) = *(ushort *)(param_1 + 0xf) | 2;
        param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x48));
        param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x4c));
        param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x50));
        *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x54);
        change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 10) + 1)));
      }
      iVar2 = (int)(*(int *)(iVar1 + 0x40));
      if (iVar2 == 0) {
        CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
      }
      param_1[0x10] = (undefined4)(iVar2);
      deletepcode((int)(iVar1));
      return 1;
    }
    iVar2 = (int)(*(int *)((int)param_1 + 0x4a));
    iVar5 = (int)(0x1ffff);
    if (*(char *)(iVar1 + 0x48) == '\x02') {
      iVar5 = (int)(*(int *)(iVar1 + 0x4a));
    }
    else if (*(char *)(iVar1 + 0x48) == '\x04') {
      if (*(char *)(*(int *)(iVar1 + 0x4e) + 2) == '\x01') {
        iVar5 = (int)(*(int *)(iVar1 + 0x4a) + *(int *)(*(int *)(iVar1 + 0x4e) + 0x48));
      }
      else {
        if (iVar2 != 0) {
          return 0;
        }
        iVar5 = (int)(0);
      }
    }
    iVar5 = (int)(iVar5 + iVar2);
    iVar3 = (int)(is_valid_displ((int)(param_1), (int)(0), (int)(iVar5)));
    if (iVar3 == 0) {
      return 0;
    }
    if (((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
          ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0) &&
       (iVar3 = fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)), iVar3 == 0) &&
       (iVar3 = fn_00596bd0((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x3a)), iVar3 == 0)) {
      *(undefined2 *)((int)param_1 + 0x3e) = *(undefined2 *)(iVar1 + 0x3e);
      iVar3 = (int)(*(int *)(iVar1 + 0x40));
      if (iVar3 == 0) {
        CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
      }
      param_1[0x10] = (undefined4)(iVar3);
      if (*(char *)(iVar1 + 0x48) == '\x04') {
        param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x48));
        param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x4c));
        param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x50));
        *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x54);
        *(int *)((int)param_1 + 0x4a) = *(int *)((int)param_1 + 0x4a) + iVar2;
        if ((param_1[3] & 0x60006) != 0) {
          uVar4 = (undefined4)(nbytes_loaded_or_stored_by((int)(param_1)));
          uVar4 = (undefined4)(fn_005a05d0((int)(*(undefined4 *)((int)param_1 + 0x4e)), (int)(*(undefined4 *)((int)param_1 + 0x4a)), (int)(uVar4)));
          param_1[7] = (undefined4)(uVar4);
        }
      }
      else {
        *(int *)((int)param_1 + 0x4a) = iVar5;
      }
      deletepcode((int)(iVar1));
      return 1;
    }
    if ((*(short *)((int)param_1 + 0x3e) != *(short *)(iVar1 + 0x3e)) &&
       (iVar3 = fn_00596bd0((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x3a)), iVar3 == 0)) {
      if ((*(char *)(iVar1 + 0x48) == '\x04') && (*(char *)(*(int *)(iVar1 + 0x4e) + 2) != '\x01'))
      {
        return 0;
      }
      *(undefined2 *)((int)param_1 + 0x3e) = *(undefined2 *)(iVar1 + 0x3e);
      iVar3 = (int)(*(int *)(iVar1 + 0x40));
      if (iVar3 == 0) {
        CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
      }
      param_1[0x10] = (undefined4)(iVar3);
      if (*(char *)(iVar1 + 0x48) == '\x04') {
        param_1[0x12] = (undefined4)(*(undefined4 *)(iVar1 + 0x48));
        param_1[0x13] = (undefined4)(*(undefined4 *)(iVar1 + 0x4c));
        param_1[0x14] = (undefined4)(*(undefined4 *)(iVar1 + 0x50));
        *(undefined2 *)(param_1 + 0x15) = *(undefined2 *)(iVar1 + 0x54);
        *(int *)((int)param_1 + 0x4a) = *(int *)((int)param_1 + 0x4a) + iVar2;
        if ((param_1[3] & 0x60006) != 0) {
          uVar4 = (undefined4)(nbytes_loaded_or_stored_by((int)(param_1)));
          uVar4 = (undefined4)(fn_005a05d0((int)(*(undefined4 *)((int)param_1 + 0x4e)), (int)(*(undefined4 *)((int)param_1 + 0x4a)), (int)(uVar4)));
          param_1[7] = (undefined4)(uVar4);
        }
      }
      else {
        *(int *)((int)param_1 + 0x4a) = iVar5;
      }
      return 1;
    }
  }
  else if ((*(short *)(iVar1 + 0x28) == 0x8b) &&
          (*(char *)(iVar1 + 0x3a) == '\0' && (*(char *)(iVar1 + 0x3b) == '\x04') &&
          (*(short *)(iVar1 + 0x3e) != 0)) &&
          (iVar2 = fn_00596bd0((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x3a)), iVar2 == 0)) {
    *(undefined2 *)((int)param_1 + 0x3e) = *(undefined2 *)(iVar1 + 0x3e);
    iVar1 = (int)(*(int *)(iVar1 + 0x40));
    if (iVar1 == 0) {
      CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
    }
    param_1[0x10] = (undefined4)(iVar1);
  }
  return 0;
}

undefined4 fn_00636cc0(int param_1)

{
  int iVar1;
  int iVar2;

  iVar1 = (int)(*(int *)(param_1 + 0x40));
  if (iVar1 == 0) {
    return 0;
  }
  if ((*(short *)(iVar1 + 0x28) != 0x42) && (*(short *)(iVar1 + 0x28) != 0x8a)) {
    return 0;
  }
  if (*(short *)(param_1 + 0x30) == *(short *)(param_1 + 0x3e)) {
    return 0;
  }
  if ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
       ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) != 0) {
    return 0;
  }
  iVar2 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(param_1 + 0x2c)));
  if (iVar2 != 0) {
    return 0;
  }
  iVar2 = (int)(fn_00596bd0((int)(param_1), (int)(iVar1), (int)(param_1 + 0x2c)));
  if (iVar2 != 0) {
    return 0;
  }
  iVar2 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(param_1 + 0x3a)));
  if (iVar2 != 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0x48) == '\x04') {
    if (*(char *)(iVar1 + 0x3a) != '\x04') {
      return 0;
    }
    if (*(int *)(iVar1 + 0x40) != *(int *)(param_1 + 0x4e)) {
      return 0;
    }
    *(undefined2 *)(iVar1 + 0x30) = *(undefined2 *)(param_1 + 0x30);
    *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(param_1 + 0x30);
    return 1;
  }
  return 0;
}

undefined4 fn_00636db0(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  PeepholeRegisterReference reference;




  iVar2 = (int)(*(int *)(param_1 + 0x5c));
  switch(*(undefined2 *)(iVar2 + 0x28)) {
  case 0x52:
    uVar6 = (uint)((uint)*(short *)(iVar2 + 0x4a));
    break;
  default:
    return 0;
  case 0x54:
    uVar6 = (uint)((uint)*(ushort *)(iVar2 + 0x4a));
  }
  iVar3 = (int)(*(int *)(iVar2 + 0x40));
  if (*(short *)(iVar3 + 0x28) == 0x8c) {
    return 0;
  }
  if (*(int *)(param_1 + 0x66) == 2) {
    sVar1 = (short)(*(short *)(param_1 + 0x5a));
    if ((*(short *)(iVar2 + 0x30) == sVar1) && (*(short *)(iVar3 + 0x28) == 0x89) &&
       (*(char *)(iVar3 + 0x3a) == '\x02')) {
      if (uVar6 == (int)*(short *)(iVar3 + 0x3c)) {
        bVar5 = (byte)((byte)sVar1 & 0x1f);
        ((uint *)native_liveness_mask0)[(int)sVar1 >> 5] =
             ((uint *)native_liveness_mask0)[(int)sVar1 >> 5] & (-2 << bVar5 | 0xfffffffeU >> 0x20 - bVar5);
        sVar1 = (short)(*(short *)(param_1 + 0x4c));
        if (sVar1 != *(short *)(param_1 + 0x30)) {
          bVar5 = (byte)((byte)sVar1 & 0x1f);
          ((uint *)native_liveness_bank4)[(int)sVar1 >> 5] =
               ((uint *)native_liveness_bank4)[(int)sVar1 >> 5] & (-2 << bVar5 | 0xfffffffeU >> 0x20 - bVar5);
        }
        if (*(short *)(param_1 + 0x3e) == 0) {
          *(uint *)native_liveness_bank4 = *(uint *)native_liveness_bank4 & 0xfffffffe;
          change_num_operands((int)(param_1), (int)(2));
          *(undefined1 *)(param_1 + 0x3a) = 2;
          *(undefined4 *)(param_1 + 0x3c) = 0;
          change_opcode((int)(param_1), (short)(0x89));
        }
        else {
          change_opcode((int)(param_1), (short)(0x8b));
          change_num_operands((int)(param_1), (int)(2));
        }
        return 1;
      }
      if (uVar6 != (int)*(short *)(iVar3 + 0x3c)) {
        bVar5 = (byte)((byte)sVar1 & 0x1f);
        ((uint *)native_liveness_mask0)[(int)sVar1 >> 5] =
             ((uint *)native_liveness_mask0)[(int)sVar1 >> 5] & (-2 << bVar5 | 0xfffffffeU >> 0x20 - bVar5);
        sVar1 = (short)(*(short *)(param_1 + 0x3e));
        if (sVar1 != *(short *)(param_1 + 0x30)) {
          bVar5 = (byte)((byte)sVar1 & 0x1f);
          ((uint *)native_liveness_bank4)[(int)sVar1 >> 5] =
               ((uint *)native_liveness_bank4)[(int)sVar1 >> 5] & (-2 << bVar5 | 0xfffffffeU >> 0x20 - bVar5);
        }
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(param_1 + 0x48);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(param_1 + 0x4c);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(param_1 + 0x50);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(param_1 + 0x54);
        change_opcode((int)(param_1), (short)(0x8b));
        change_num_operands((int)(param_1), (int)(2));
        return 1;
      }
    }
  }
  else if (uVar6 == 0) {
    iVar4 = (int)(fn_005960b0((int)(iVar3)));
    if ((iVar4 != 0) && ((*(uint *)(iVar3 + 0x10) & 0xe0000000) == 0x80000000) &&
       ((*(uint *)(iVar3 + 0xc) & 0x100) == 0)) {
      if (*(short *)(iVar2 + 0x30) == 0) {
        iVar4 = (int)(fn_00596bd0((int)(iVar2), (int)(iVar3), (int)(iVar2 + 0x2c)));
        if ((iVar4 != 0) && (iVar4 = fn_00596b50((int)(iVar2), (int)(iVar3), (int)(iVar2 + 0x2c)), iVar4 != 0)) {
          pcsetrecordbit((int)(iVar3));
          deletepcode((int)(iVar2));
          *(int *)(param_1 + 0x5c) = iVar3;
          return 1;
        }
      }
      else {
        reference.kind = (undefined1)(0);
        reference.registerClass = (undefined1)(1);
        reference.number = (undefined2)(0);
        reference.flags = (undefined2)(1);
        if (((native_extended_mode == 0) || (native_target_flag != '\0')) && ((*(uint *)native_liveness_mask0 & 1) == 0)) {
          iVar4 = (int)(fn_00596b50((int)(param_1), (int)(iVar3), (int)(&reference.kind)));
          if ((iVar4 == 0) && (iVar4 = fn_00596bd0((int)(param_1), (int)(iVar3), (int)(&reference.kind)), iVar4 == 0)) {
            *(undefined1 *)(param_1 + 0x56) = 0;
            *(undefined1 *)(param_1 + 0x57) = 1;
            *(undefined2 *)(param_1 + 0x5a) = 0;
            *(undefined2 *)(param_1 + 0x58) = 1;
            pcsetrecordbit((int)(iVar3));
            deletepcode((int)(iVar2));
            *(int *)(param_1 + 0x5c) = iVar3;
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

undefined4 fn_006370d0(int param_1)

{
  int iVar1;
  int iVar2;

  iVar1 = (int)(*(int *)(param_1 + 0x40));
  if (iVar1 == 0) {
    return 0;
  }
  if ((*(short *)(iVar1 + 0x28) == 0x89) && (*(char *)(iVar1 + 0x3a) == '\x02') &&
     (*(int *)(iVar1 + 0x3c) == 0) && (*(short *)(iVar1 + 0x30) == *(short *)(param_1 + 0x3e))) {
    iVar2 = (int)(fn_00596bd0((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)));
    if (iVar2 == 0) {
      *(undefined2 *)(param_1 + 0x3e) = 0;
      *(ushort *)(param_1 + 0x3c) = *(ushort *)(param_1 + 0x3c) & 0xfffc;
      *(undefined4 *)(param_1 + 0x40) = 0;
      iVar2 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)));
      if ((iVar2 == 0) &&
         ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
           ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0)) {
        deletepcode((int)(iVar1));
      }
      return 1;
    }
  }
  return 0;
}

undefined4 fn_00637170(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar4 = (int)(*(int *)(param_1 + 0x40));
  iVar5 = (int)(*(int *)(param_1 + 0x4e));
  if (iVar4 == 0) {
    return 0;
  }
  if ((*(short *)(iVar5 + 0x28) == 0x89) && (*(short *)(iVar5 + 0x30) == *(short *)(param_1 + 0x4c))
     ) {
    iVar1 = (int)(fn_00596bd0((int)(param_1), (int)(iVar5), (int)(iVar5 + 0x2c)));
    if (iVar1 == 0) {
      if ((*(char *)(iVar5 + 0x3a) == '\x02') &&
         (*(uint *)(iVar5 + 0x3c) == (*(uint *)(iVar5 + 0x3c) & 0xfff))) {
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(iVar5 + 0x3a);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar5 + 0x3e);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar5 + 0x42);
        *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(iVar5 + 0x46);
        change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 0x28) - 2)));
        iVar4 = (int)(fn_00596b50((int)(param_1), (int)(iVar5), (int)(iVar5 + 0x2c)));
        if ((iVar4 == 0) &&
           ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar5 + 0x30) >> 5) * 4) >>
             ((byte)*(short *)(iVar5 + 0x30) & 0x1f) & 1) == 0)) {
          deletepcode((int)(iVar5));
        }
        return 1;
      }
      if ((*(char *)(iVar5 + 0x3a) == '\x04') && (*(char *)(*(int *)(iVar5 + 0x4e) + 2) == '\x01'))
      {
        iVar2 = (int)(local_offset_32((int)(*(int *)(iVar5 + 0x4e))));
        iVar1 = (int)(*(int *)(iVar5 + 0x4a));
        iVar3 = (int)(local_offset_32((int)(*(undefined4 *)(iVar5 + 0x4e))));
        if ((iVar3 + *(int *)(iVar5 + 0x4a) & 0xfffU) == iVar2 + iVar1) {
          *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(iVar5 + 0x3a);
          *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar5 + 0x3e);
          *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar5 + 0x42);
          *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(iVar5 + 0x46);
          *(undefined1 *)(param_1 + 0x49) = 0xf;
          change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 0x28) - 2)));
          iVar4 = (int)(fn_00596b50((int)(param_1), (int)(iVar5), (int)(iVar5 + 0x2c)));
          if ((iVar4 == 0) &&
             ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar5 + 0x30) >> 5) * 4) >>
               ((byte)*(short *)(iVar5 + 0x30) & 0x1f) & 1) == 0)) {
            deletepcode((int)(iVar5));
          }
          return 1;
        }
      }
    }
  }
  if (((*(uint *)(param_1 + 0x10) & 0x8000) == 0) && (*(short *)(iVar4 + 0x28) == 0x89) &&
     (*(short *)(iVar4 + 0x30) == *(short *)(param_1 + 0x3e))) {
    iVar5 = (int)(fn_00596bd0((int)(param_1), (int)(iVar4), (int)(iVar4 + 0x2c)));
    if (iVar5 == 0) {
      if ((*(char *)(iVar4 + 0x3a) == '\x02') &&
         (*(uint *)(iVar4 + 0x3c) == (*(uint *)(iVar4 + 0x3c) & 0xfff))) {
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(param_1 + 0x48);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(param_1 + 0x4c);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(param_1 + 0x50);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(param_1 + 0x54);
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(iVar4 + 0x3a);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar4 + 0x3e);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar4 + 0x42);
        *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(iVar4 + 0x46);
        change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 0x28) - 2)));
        iVar5 = (int)(fn_00596b50((int)(param_1), (int)(iVar4), (int)(iVar4 + 0x2c)));
        if ((iVar5 == 0) &&
           ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar4 + 0x30) >> 5) * 4) >>
             ((byte)*(short *)(iVar4 + 0x30) & 0x1f) & 1) == 0)) {
          deletepcode((int)(iVar4));
        }
        return 1;
      }
      if ((*(char *)(iVar4 + 0x3a) == '\x04') && (*(char *)(*(int *)(iVar4 + 0x4e) + 2) == '\x01'))
      {
        iVar1 = (int)(local_offset_32((int)(*(int *)(iVar4 + 0x4e))));
        iVar5 = (int)(*(int *)(iVar4 + 0x4a));
        iVar2 = (int)(local_offset_32((int)(*(undefined4 *)(iVar4 + 0x4e))));
        if ((iVar2 + *(int *)(iVar4 + 0x4a) & 0xfffU) == iVar1 + iVar5) {
          *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(param_1 + 0x48);
          *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(param_1 + 0x4c);
          *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(param_1 + 0x50);
          *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(param_1 + 0x54);
          *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(iVar4 + 0x3a);
          *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar4 + 0x3e);
          *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar4 + 0x42);
          *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(iVar4 + 0x46);
          change_opcode((int)(param_1), (short)((int)(short)(*(short *)(param_1 + 0x28) - 2)));
          *(undefined1 *)(param_1 + 0x49) = 0xf;
          iVar5 = (int)(fn_00596b50((int)(param_1), (int)(iVar4), (int)(iVar4 + 0x2c)));
          if ((iVar5 == 0) &&
             ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar4 + 0x30) >> 5) * 4) >>
               ((byte)*(short *)(iVar4 + 0x30) & 0x1f) & 1) == 0)) {
            deletepcode((int)(iVar4));
          }
          return 1;
        }
      }
    }
  }
  return 0;
}

undefined4 fn_006374b0(int param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;

  iVar1 = (int)(*(int *)(param_1 + 0x40));
  if (iVar1 == 0) {
    return 0;
  }
  if ((*(short *)(iVar1 + 0x28) == 0x89) && (*(char *)(iVar1 + 0x3a) == '\x04') &&
     (*(char *)(param_1 + 0x48) == '\x02') && (*(int *)(param_1 + 0x4a) == 0)) {
    cVar2 = (char)(fn_004c3f60((int)(*(undefined4 *)(iVar1 + 0x40))));
    if ((cVar2 != '\0') && (*(short *)(iVar1 + 0x30) == *(short *)(param_1 + 0x3e))) {
      iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)));
      if (iVar3 == 0) {
        *(undefined2 *)(param_1 + 0x3e) = 0;
        *(ushort *)(param_1 + 0x3c) = *(ushort *)(param_1 + 0x3c) & 0xfffc;
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(iVar1 + 0x3a);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar1 + 0x3e);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar1 + 0x42);
        *(undefined2 *)(param_1 + 0x54) = *(undefined2 *)(iVar1 + 0x46);
        iVar3 = (int)(*(int *)(iVar1 + 0x40));
        if (iVar3 == 0) {
          CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
        }
        *(int *)(param_1 + 0x40) = iVar3;
        iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(iVar1 + 0x2c)));
        if ((iVar3 == 0) &&
           ((*(uint *)(native_liveness_bank4 + ((int)*(short *)(iVar1 + 0x30) >> 5) * 4) >>
             ((byte)*(short *)(iVar1 + 0x30) & 0x1f) & 1) == 0)) {
          deletepcode((int)(iVar1));
        }
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_006375b0(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if ((*(short *)(iVar2 + 0x28) == 0x1d) &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0 && (*(uint *)(param_1 + 0x10) & 0x100000) == 0) &&
     (sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
     ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0))) {
    iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
    if (iVar3 == 0) {
      iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
      if (iVar3 == 0) {
        iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
        if (iVar3 == 0) {
          *(undefined2 *)(iVar2 + 0x30) = *(undefined2 *)(param_1 + 0x30);
          deletepcode((int)(param_1));
          return 1;
        }
      }
    }
  }
  if ((*(short *)(iVar2 + 0x28) == 100) &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0 && (*(uint *)(param_1 + 0x10) & 0x100000) == 0)) {
    sVar1 = (short)(*(short *)(iVar2 + 0x30));
    if (sVar1 != *(short *)(iVar2 + 0x3e)) {
      iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)));
      if (iVar3 == 0) {
        change_opcode((int)(param_1), (short)(100));
        *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(iVar2 + 0x3a);
        *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(iVar2 + 0x3e);
        *(undefined4 *)(param_1 + 0x42) = *(undefined4 *)(iVar2 + 0x42);
        *(undefined2 *)(param_1 + 0x46) = *(undefined2 *)(iVar2 + 0x46);
      }
      else {
        change_opcode((int)(param_1), (short)(0x8b));
      }
      return 1;
    }
    if ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0) {
      iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
      if (iVar3 == 0) {
        change_opcode((int)(param_1), (short)(100));
        deletepcode((int)(iVar2));
        return 1;
      }
    }
  }
  return 0;
}

undefined4 fn_00637740(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if (((*(short *)(iVar2 + 0x28) == 0x19) || (*(short *)(iVar2 + 0x28) == 0x1b)) &&
     (*(int *)(param_1 + 0x4a) == 0) &&
     (*(int *)(param_1 + 0x58) < 0x11 && (*(int *)(param_1 + 0x66) == 0x1f)) &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0 && (*(uint *)(param_1 + 0x10) & 0x100000) == 0 &&
     (sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
     ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)))) {
    iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
    if (iVar3 == 0) {
      iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
      if (iVar3 == 0) {
        iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
        if (iVar3 == 0) {
          *(undefined2 *)(iVar2 + 0x30) = *(undefined2 *)(param_1 + 0x30);
          deletepcode((int)(param_1));
          return 1;
        }
      }
    }
  }
  return 0;
}

undefined4 fn_00637800(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if (((*(short *)(iVar2 + 0x28) == 0x15) || (*(short *)(iVar2 + 0x28) == 0x17)) &&
     (*(int *)(param_1 + 0x4a) == 0) &&
     (*(int *)(param_1 + 0x58) < 0x19 && (*(int *)(param_1 + 0x66) == 0x1f)) &&
     ((*(uint *)(param_1 + 0xc) & 0x180) == 0 && (*(uint *)(param_1 + 0x10) & 0x100000) == 0 &&
     (sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
     ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)))) {
    iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
    if (iVar3 == 0) {
      iVar3 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
      if (iVar3 == 0) {
        iVar3 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(param_1 + 0x2c)));
        if (iVar3 == 0) {
          *(undefined2 *)(iVar2 + 0x30) = *(undefined2 *)(param_1 + 0x30);
          deletepcode((int)(param_1));
          return 1;
        }
      }
    }
  }
  return 0;
}

undefined4 fn_006378c0(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if ((*(short *)(iVar2 + 0x28) == 0x65) &&
     ((sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
      ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
     ((*(uint *)(iVar2 + 0xc) & 0x180) == 0 && (*(uint *)(iVar2 + 0x10) & 0x100000) == 0))) {
    iVar5 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)));
    if (iVar5 == 0) {
      iVar5 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
      if (iVar5 == 0) {
        iVar5 = (int)(*(int *)(param_1 + 0x58));
        iVar3 = (int)(*(int *)(param_1 + 0x66));
        if (iVar3 < iVar5) {
          if (iVar3 + 1 < 0x20) {
            uVar7 = (uint)(0xffffffff >> ((char)iVar3 + 1U & 0x1f));
          }
          else {
            uVar7 = (uint)(0);
          }
          if (iVar5 < 0x20) {
            uVar6 = (uint)(0xffffffff >> ((byte)iVar5 & 0x1f));
          }
          else {
            uVar6 = (uint)(0);
          }
          uVar6 = (uint)(~uVar7 | uVar6);
        }
        else {
          if (iVar3 + 1 < 0x20) {
            uVar7 = (uint)(0xffffffff >> ((char)iVar3 + 1U & 0x1f));
          }
          else {
            uVar7 = (uint)(0);
          }
          if (iVar5 < 0x20) {
            uVar6 = (uint)(0xffffffff >> ((byte)iVar5 & 0x1f));
          }
          else {
            uVar6 = (uint)(0);
          }
          uVar6 = (uint)(~uVar7 & uVar6);
        }
        bVar4 = (byte)((byte)*(undefined4 *)(param_1 + 0x4a));
        if (((uVar6 << (0x20 - bVar4 & 0x1f) | uVar6 >> (bVar4 & 0x1f)) & 0xffff0000) == 0) {
          *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
          iVar5 = (int)(*(int *)(iVar2 + 0x40));
          if (iVar5 == 0) {
            CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
          }
          *(int *)(param_1 + 0x40) = iVar5;
          deletepcode((int)(iVar2));
          return 1;
        }
      }
    }
  }
  return 0;
}

undefined4 fn_00637a10(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;

  iVar2 = (int)(*(int *)(param_1 + 0x40));
  if ((*(short *)(iVar2 + 0x28) == 100) &&
     ((sVar1 = *(short *)(iVar2 + 0x30), sVar1 == *(short *)(param_1 + 0x30) ||
      ((*(uint *)(native_liveness_bank4 + ((int)sVar1 >> 5) * 4) >> ((byte)sVar1 & 0x1f) & 1) == 0)) &&
     ((*(uint *)(iVar2 + 0xc) & 0x180) == 0 && (*(uint *)(iVar2 + 0x10) & 0x100000) == 0))) {
    iVar5 = (int)(fn_00596bd0((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x3a)));
    if (iVar5 == 0) {
      iVar5 = (int)(fn_00596b50((int)(param_1), (int)(iVar2), (int)(iVar2 + 0x2c)));
      if (iVar5 == 0) {
        iVar5 = (int)(*(int *)(param_1 + 0x58));
        iVar3 = (int)(*(int *)(param_1 + 0x66));
        if (iVar3 < iVar5) {
          if (iVar3 + 1 < 0x20) {
            uVar7 = (uint)(0xffffffff >> ((char)iVar3 + 1U & 0x1f));
          }
          else {
            uVar7 = (uint)(0);
          }
          if (iVar5 < 0x20) {
            uVar6 = (uint)(0xffffffff >> ((byte)iVar5 & 0x1f));
          }
          else {
            uVar6 = (uint)(0);
          }
          uVar6 = (uint)(~uVar7 | uVar6);
        }
        else {
          if (iVar3 + 1 < 0x20) {
            uVar7 = (uint)(0xffffffff >> ((char)iVar3 + 1U & 0x1f));
          }
          else {
            uVar7 = (uint)(0);
          }
          if (iVar5 < 0x20) {
            uVar6 = (uint)(0xffffffff >> ((byte)iVar5 & 0x1f));
          }
          else {
            uVar6 = (uint)(0);
          }
          uVar6 = (uint)(~uVar7 & uVar6);
        }
        bVar4 = (byte)((byte)*(undefined4 *)(param_1 + 0x4a));
        if (((uVar6 << (0x20 - bVar4 & 0x1f) | uVar6 >> (bVar4 & 0x1f)) & 0xffffff00) == 0) {
          *(undefined2 *)(param_1 + 0x3e) = *(undefined2 *)(iVar2 + 0x3e);
          iVar5 = (int)(*(int *)(iVar2 + 0x40));
          if (iVar5 == 0) {
            CError_Internal((const char *)(peepholeFilename), (int)(0x5b));
          }
          *(int *)(param_1 + 0x40) = iVar5;
          deletepcode((int)(iVar2));
          return 1;
        }
      }
    }
  }
  return 0;
}

undefined4 fn_00637b60(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  PeepholeRegisterReference reference;




  iVar2 = (int)(*(int *)(param_1 + 0x5c));
  if ((iVar2 == 0) || (*(short *)(iVar2 + 0x28) == 0x8c)) {
    return 0;
  }
  iVar3 = (int)(*(int *)(iVar2 + 0x40));
  if ((iVar3 != 0) && (sVar1 = *(short *)(iVar3 + 0x28), sVar1 != 0x8c)) {
    if (*(int *)(param_1 + 0x66) != 2) {
      return 0;
    }
    if (*(short *)(iVar2 + 0x30) != *(short *)(param_1 + 0x5a)) {
      return 0;
    }
    switch(*(short *)(iVar2 + 0x28)) {
    case 0x52:
    case 0x54:
      goto switchD_00637bc1_caseD_52;
    default:
      return 0;
    }
  }
  return 0;
switchD_00637bc1_caseD_52:
  if (sVar1 == 0x8c) {
    return 0;
  }
  if ((native_extended_mode != 0) && (sVar1 == 0x8b)) {
    return 0;
  }
  if (*(short *)(iVar2 + 0x30) == 0) {
    iVar4 = (int)(fn_00596b50((int)(iVar2), (int)(iVar3), (int)(iVar2 + 0x2c)));
    if ((iVar4 != 0) || (iVar4 = fn_00596bd0((int)(iVar2), (int)(iVar3), (int)(iVar2 + 0x2c)), iVar4 != 0)) {
      return 0;
    }
  }
  else {
    if ((native_extended_mode == 0) || (native_target_flag == '\0')) {
      return 0;
    }
    if ((*(uint *)native_liveness_mask0 & 1) != 0) {
      return 0;
    }
    reference.kind = (undefined1)(0);
    reference.registerClass = (undefined1)(1);
    reference.number = (undefined2)(0);
    reference.flags = (undefined2)(0);
    iVar4 = (int)(fn_00596b50((int)(param_1), (int)(iVar3), (int)(&reference.kind)));
    if ((iVar4 != 0) || (iVar4 = fn_00596bd0((int)(param_1), (int)(iVar3), (int)(&reference.kind)), iVar4 != 0)) {
      return 0;
    }
  }
  if ((*(int *)(iVar2 + 0x4a) != 0) || ((*(uint *)(iVar3 + 0x10) & 0xe0000000) != 0x80000000) ||
     ((*(uint *)(iVar3 + 0xc) & 0x100) != 0)) {
    return 0;
  }
  iVar4 = (int)(fn_005960b0((int)(iVar3)));
  if (iVar4 == 0) {
    return 0;
  }
  if ((*(short *)(iVar3 + 0x28) == 0x3f) && (iVar4 = fn_006385e0((undefined4 *)(iVar3)), iVar4 != 0)) {
    return 0;
  }
  if ((*(uint *)(iVar3 + 0x10) & 0x100000) == 0) {
    pcsetrecordbit((int)(iVar3));
  }
  if (*(short *)(param_1 + 0x5a) != 0) {
    *(undefined1 *)(param_1 + 0x56) = 0;
    *(undefined1 *)(param_1 + 0x57) = 1;
    *(undefined2 *)(param_1 + 0x5a) = 0;
    *(undefined2 *)(param_1 + 0x58) = 1;
  }
  *(int *)(param_1 + 0x5c) = iVar3;
  if (*(short *)(iVar2 + 0x30) == 0) {
    deletepcode((int)(iVar2));
  }
  else {
    change_opcode((int)(iVar2), (short)(0x76));
    change_num_operands((int)(iVar2), (int)(2));
    *(undefined1 *)(iVar2 + 0x3a) = 0;
    *(undefined1 *)(iVar2 + 0x3b) = 1;
    *(undefined2 *)(iVar2 + 0x3e) = 0;
    *(undefined2 *)(iVar2 + 0x3c) = 1;
    *(int *)(iVar2 + 0x40) = iVar3;
  }
  return 1;
}

undefined4 fn_00637e10(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  PeepholeRegisterReference reference;




  iVar3 = (int)(*(int *)(param_1 + 0x32));
  if ((iVar3 == 0) || (*(short *)(iVar3 + 0x28) == 0x8c)) {
    return 0;
  }
  iVar4 = (int)(*(int *)(iVar3 + 0x40));
  if ((iVar4 != 0) && (sVar1 = *(short *)(iVar4 + 0x28), sVar1 != 0x8c)) {
    if (*(int *)(param_1 + 0x3c) != 2) {
      return 0;
    }
    sVar2 = (short)(*(short *)(iVar3 + 0x30));
    if (sVar2 != *(short *)(param_1 + 0x30)) {
      return 0;
    }
    switch(*(short *)(iVar3 + 0x28)) {
    case 0x52:
    case 0x54:
      goto switchD_00637e75_caseD_52;
    default:
      return 0;
    }
  }
  return 0;
switchD_00637e75_caseD_52:
  if (sVar1 == 0x8c) {
    return 0;
  }
  if ((native_extended_mode != 0) && (sVar1 == 0x8b)) {
    return 0;
  }
  if (sVar2 == 0) {
    iVar5 = (int)(fn_00596b50((int)(iVar3), (int)(iVar4), (int)(iVar3 + 0x2c)));
    if ((iVar5 != 0) || (iVar5 = fn_00596bd0((int)(iVar3), (int)(iVar4), (int)(iVar3 + 0x2c)), iVar5 != 0)) {
      return 0;
    }
  }
  else {
    if ((native_extended_mode == 0) || (native_target_flag == '\0')) {
      return 0;
    }
    if ((*(uint *)(native_liveness_mask0 + ((int)sVar2 >> 5) * 4) >> ((byte)sVar2 & 0x1f) & 1) != 0) {
      return 0;
    }
    reference.kind = (undefined1)(0);
    reference.registerClass = (undefined1)(1);
    reference.number = (undefined2)(0);
    reference.flags = (undefined2)(0);
    iVar5 = (int)(fn_00596b50((int)(param_1), (int)(iVar4), (int)(&reference.kind)));
    if ((iVar5 != 0) || (iVar5 = fn_00596bd0((int)(param_1), (int)(iVar4), (int)(&reference.kind)), iVar5 != 0)) {
      return 0;
    }
  }
  if ((*(int *)(iVar3 + 0x4a) != 0) || ((*(uint *)(iVar4 + 0x10) & 0xe0000000) != 0x80000000) ||
     ((*(uint *)(iVar4 + 0xc) & 0x100) != 0)) {
    return 0;
  }
  iVar5 = (int)(fn_005960b0((int)(iVar4)));
  if (iVar5 == 0) {
    return 0;
  }
  if ((*(short *)(iVar4 + 0x28) == 0x3f) && (iVar5 = fn_006385e0((undefined4 *)(iVar4)), iVar5 != 0)) {
    return 0;
  }
  if ((*(uint *)(iVar4 + 0x10) & 0x100000) == 0) {
    pcsetrecordbit((int)(iVar4));
  }
  if (*(short *)(param_1 + 0x30) != 0) {
    *(undefined1 *)(param_1 + 0x2c) = 0;
    *(undefined1 *)(param_1 + 0x2d) = 1;
    *(undefined2 *)(param_1 + 0x30) = 0;
    *(undefined2 *)(param_1 + 0x2e) = 1;
  }
  *(int *)(param_1 + 0x32) = iVar4;
  if (*(short *)(iVar3 + 0x30) == 0) {
    deletepcode((int)(iVar3));
  }
  else {
    change_opcode((int)(iVar3), (short)(0x76));
    change_num_operands((int)(iVar3), (int)(2));
    *(undefined1 *)(iVar3 + 0x3a) = 0;
    *(undefined1 *)(iVar3 + 0x3b) = 1;
    *(undefined2 *)(iVar3 + 0x3e) = 0;
    *(undefined2 *)(iVar3 + 0x3c) = 1;
    *(int *)(iVar3 + 0x40) = iVar4;
  }
  return 1;
}

undefined4 fn_006380d0(int param_1)

{
  int iVar1;
  int iVar2;
  PeepholeRegisterReference reference;




  iVar1 = (int)(*(int *)(param_1 + 0x40));
  if (*(short *)(iVar1 + 0x28) == 0x8c) {
    return 0;
  }
  if ((native_extended_mode != 0) && (*(short *)(iVar1 + 0x28) == 0x8b)) {
    return 0;
  }
  if (*(short *)(param_1 + 0x30) != 0) {
    if ((native_extended_mode == 0) || (native_target_flag == '\0')) {
      return 0;
    }
    if ((*(uint *)native_liveness_mask0 & 1) != 0) {
      return 0;
    }
    reference.kind = (undefined1)(0);
    reference.registerClass = (undefined1)(1);
    reference.number = (undefined2)(0);
    reference.flags = (undefined2)(0);
    iVar2 = (int)(fn_00596b50((int)(param_1), (int)(iVar1), (int)(&reference.kind)));
    if ((iVar2 != 0) || (iVar2 = fn_00596bd0((int)(param_1), (int)(iVar1), (int)(&reference.kind)), iVar2 != 0)) {
      return 0;
    }
  }
  if ((*(int *)(param_1 + 0x4a) != 0) || ((*(uint *)(iVar1 + 0x10) & 0xe0000000) != 0x80000000) ||
     ((*(uint *)(iVar1 + 0xc) & 0x100) != 0) ||
     (iVar2 = fn_00596b50((int)(param_1), (int)(iVar1), (int)(param_1 + 0x2c)), iVar2 != 0 ||
     (iVar2 = fn_00596bd0((int)(param_1), (int)(iVar1), (int)(param_1 + 0x2c)), iVar2 != 0))) {
    return 0;
  }
  iVar2 = (int)(fn_005960b0((int)(iVar1)));
  if (iVar2 == 0) {
    return 0;
  }
  if ((*(short *)(iVar1 + 0x28) == 0x3f) && (iVar2 = fn_006385e0((undefined4 *)(iVar1)), iVar2 != 0)) {
    return 0;
  }
  if ((*(uint *)(iVar1 + 0x10) & 0x100000) == 0) {
    pcsetrecordbit((int)(iVar1));
  }
  if (*(short *)(param_1 + 0x30) == 0) {
    deletepcode((int)(param_1));
  }
  else {
    change_opcode((int)(param_1), (short)(0x76));
    change_num_operands((int)(param_1), (int)(2));
    *(undefined1 *)(param_1 + 0x3a) = 0;
    *(undefined1 *)(param_1 + 0x3b) = 1;
    *(undefined2 *)(param_1 + 0x3e) = 0;
    *(undefined2 *)(param_1 + 0x3c) = 1;
    *(int *)(param_1 + 0x40) = iVar1;
  }
  return 1;
}

undefined4 fn_006382b0(int *param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  int local_18;
  int local_14;

  iVar1 = (int)(param_1[1]);
  iVar2 = (int)(*param_1);
  bVar3 = (bool)(false);
  local_18 = (int)(0);
  bVar4 = (bool)(false);
  local_14 = (int)(0);
  if (iVar1 != 0) {
    bVar3 = (bool)((*(uint *)(iVar1 + 0x10) & 0xe0000000) == 0x20000000);
    local_18 = (int)(fn_005994f0((int)(iVar1)));
  }
  if (iVar2 != 0) {
    bVar4 = (bool)((*(uint *)(iVar2 + 0x10) & 0xe0000000) == 0x20000000);
    local_14 = (int)(fn_005994f0((int)(iVar2)));
  }
  if (iVar1 == 0) {
    if ((iVar2 != 0) && (bVar4) && (local_14 == 0)) {
      change_opcode((int)(param_1), (short)(0x191));
      return 1;
    }
  }
  else if (iVar2 == 0) {
    if ((bVar3) && (local_18 == 0)) {
      change_opcode((int)(param_1), (short)(0x191));
      return 1;
    }
  }
  else if ((bVar3) && (local_18 == 0)) {
    if (!bVar4) {
      change_opcode((int)(param_1), (short)(0x191));
      return 1;
    }
    if (local_14 == 0) {
      change_opcode((int)(param_1), (short)(0x191));
      return 1;
    }
  }
  return 0;
}

/* Ported structure from 1.2.5's corresponding move-elimination callback;
 * GC 3.0 definition location, opcode and both flag words are native-verified. */
undefined4 fn_00638400(int param_1)
{
    PeepholeInstruction *p = (PeepholeInstruction *)param_1;
    PeepholeInstruction *definition = p->operands[1].payload.reg.definition;
    if (definition->opcode == 0x190 &&
        p->operands[0].payload.reg.number == definition->operands[1].payload.reg.number &&
        ((p->recordFlags & 0x100000U) | (p->flags & 0x180U)) == 0 &&
        fn_00596bd0((int)p, (int)definition, (int)&p->operands[0]) == 0) {
        deletepcode((int)p);
        return 1;
    }
    return 0;
}

/* Ported structure from 1.2.5's corresponding move-elimination callback;
 * GC 3.0 definition location, opcode and both flag words are native-verified. */
undefined4 fn_00638460(int param_1)
{
    PeepholeInstruction *p = (PeepholeInstruction *)param_1;
    PeepholeInstruction *definition = p->operands[1].payload.reg.definition;
    if (definition->opcode == 0x9e &&
        p->operands[0].payload.reg.number == definition->operands[1].payload.reg.number &&
        ((p->recordFlags & 0x100000U) | (p->flags & 0x180U)) == 0 &&
        fn_00596bd0((int)p, (int)definition, (int)&p->operands[0]) == 0) {
        deletepcode((int)p);
        return 1;
    }
    return 0;
}

/* Ported structure from 1.2.5's corresponding move-elimination callback;
 * GC 3.0 definition location, opcode and both flag words are native-verified. */
undefined4 fn_006384c0(int param_1)
{
    PeepholeInstruction *p = (PeepholeInstruction *)param_1;
    PeepholeInstruction *definition = p->operands[1].payload.reg.definition;
    if (definition->opcode == 0x8b &&
        p->operands[0].payload.reg.number == definition->operands[1].payload.reg.number &&
        fn_00596bd0((int)p, (int)definition, (int)&p->operands[0]) == 0 &&
        ((p->recordFlags & 0x100000U) | (p->flags & 0x180U)) == 0) {
        deletepcode((int)p);
        return 1;
    }
    return 0;
}

/* 1.2.5 same-register move structure with GC 3.0's extra flag guards. */
undefined4 fn_00638520(int param_1)
{
    PeepholeInstruction *p = (PeepholeInstruction *)param_1;
    if (p->operands[0].payload.reg.number == p->operands[1].payload.reg.number &&
        ((p->recordFlags & 0x100000U) | (p->flags & 0x180U)) == 0) {
        deletepcode((int)p);
        return 1;
    }
    return 0;
}

/* 1.2.5 same-register move structure with GC 3.0's extra flag guards. */
undefined4 fn_00638560(int param_1)
{
    PeepholeInstruction *p = (PeepholeInstruction *)param_1;
    if (p->operands[0].payload.reg.number == p->operands[1].payload.reg.number &&
        ((p->recordFlags & 0x100000U) | (p->flags & 0x180U)) == 0) {
        deletepcode((int)p);
        return 1;
    }
    return 0;
}

/* 1.2.5 same-register move structure with GC 3.0's extra flag guards. */
undefined4 fn_006385a0(int param_1)
{
    PeepholeInstruction *p = (PeepholeInstruction *)param_1;
    if (p->operands[0].payload.reg.number == p->operands[1].payload.reg.number &&
        ((p->recordFlags & 0x100000U) | (p->flags & 0x180U)) == 0) {
        deletepcode((int)p);
        return 1;
    }
    return 0;
}

undefined4 fn_006385e0(undefined4 *param_1)

{
  char *pcVar1;
  int iVar2;

  param_1 = (undefined4*)((undefined4 *)*param_1);
  while( true ) {
    if (param_1 == (undefined4 *)0x0) {
      return 0;
    }
    if ((param_1[4] & 0x40000) != 0) break;
    if ((param_1[4] & 0x80000) != 0) {
      return 0;
    }
    iVar2 = (int)((int)*(short *)((int)param_1 + 0x2a));
    pcVar1 = (char*)((char *)(param_1 + 0xb));
    while (iVar2 != 0) {
      iVar2 = (int)(iVar2 - 1);
      if ((*pcVar1 == '\0') && (pcVar1[1] == '\0') && (*(short *)(pcVar1 + 4) == 0) &&
         ((*(ushort *)(pcVar1 + 2) & 1) != 0)) {
        return 1;
      }
      if ((*pcVar1 == '\0') && (pcVar1[1] == '\0') &&
         (*(short *)(pcVar1 + 4) == 0 && ((*(ushort *)(pcVar1 + 2) & 3) == 2))) {
        return 0;
      }
      pcVar1 = (char*)(pcVar1 + 0xe);
    }
    param_1 = (undefined4*)((undefined4 *)*param_1);
  }
  return 1;
}

undefined4
fn_00638690(int param_1, undefined4 *param_2, int param_3, int param_4, int param_5, int param_6,
            int param_7)

{
  int iVar1;
  int iVar2;

  do {
    if (param_2 == (undefined4 *)0x0) {
      iVar2 = (int)(*(int *)(param_1 + 0x10));
      while( true ) {
        if (iVar2 == 0) {
          return 1;
        }
        iVar1 = (int)(fn_00638690((int)(*(int *)(iVar2 + 0x10)), (undefined4 *)(*(undefined4 *)(*(int *)(iVar2 + 0x10) + 0x14)), (int)(param_3), (int)(param_4), (int)(param_5), (int)(param_6), (int)(param_7)));
        if (iVar1 == 0) break;
        iVar2 = (int)(*(int *)(iVar2 + 4));
      }
      return 0;
    }
    param_3 = (int)(param_3 + 1);
    if (param_3 > 0x11) {
      return 1;
    }
    iVar2 = (int)((int)*(short *)(param_2 + 10));
    if (iVar2 - 0x45U < 6) {
      if (param_5 == 0) {
        return 1;
      }
      return 0;
    }
    if (iVar2 - 0x6eU < 9) {
      param_7 = (int)(param_7 + 1);
      if (param_7 > 1) {
        return 1;
      }
    }
    else if ((iVar2 - 0x77U < 0xc) || (iVar2 - 0xc1U < 0xf) || (iVar2 - 0xd2U < 8) ||
            (iVar2 - 0xdbU < 3)) {
      return 1;
    }
    if ((param_2[3] & 6) == 0) {
      if ((param_2[3] & 1) != 0) {
        param_4 = (int)(param_4 + 1);
        if (param_4 > 2) {
          return 1;
        }
        iVar2 = (int)(0);
        if (*(short *)((int)param_2 + 0x2a) > 0) {
          iVar1 = (int)(0);
          do {
            if ((*(char *)((int)param_2 + iVar1 + 0x2c) == '\0') &&
               (*(char *)((int)param_2 + iVar1 + 0x2d) == '\x01')) {
              param_5 = (int)(param_5 + 1);
              break;
            }
            iVar2 = (int)(iVar2 + 1);
            iVar1 = (int)(iVar1 + 0xe);
          } while (iVar2 < *(short *)((int)param_2 + 0x2a));
        }
      }
    }
    else {
      param_6 = (int)(param_6 + 1);
      if (param_6 > 1) {
        return 1;
      }
    }
    param_2 = (undefined4*)((undefined4 *)*param_2);
  } while( true );
}
