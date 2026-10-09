/* Native IroUnrollLoop supported family; private native layouts and calling contracts. */
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef unsigned char undefined;
typedef unsigned char bool;
typedef uint code();
#pragma options align=mac68k
typedef struct NativePair { int first; uint second; } NativePair;
#pragma options align=reset
typedef struct NativeRange { uint first,last; } NativeRange;
static inline NativePair NativeWords(uint first,uint second) { NativePair result;result.first=first;result.second=second;return result; }
extern NativePair NativeMultiply(NativePair,NativePair);
extern uint NativeConstant(NativePair,uint);
extern NativePair NativeZero,NativeOne;
extern byte NativeLess(NativePair,NativePair),NativeNotEqual(NativePair,NativePair);
extern NativePair NativeShift(NativePair,NativePair),NativeAnd(NativePair,NativePair),NativeOr(NativePair,NativePair),NativeAdd(NativePair,NativePair);
#define true 1
#define false 0
static inline undefined8 NativePack(uint first,uint second) { union { struct { uint first,second; } words; undefined8 bits; } value;value.words.first=first;value.words.second=second;return value.bits; }
#define PACK(first,second) NativePack((uint)(first),(uint)(second))
#define CONCAT44(hi,lo) PACK(lo,hi)
#define WORD0(value) ((uint)(value))
#define WORD1(value) ((uint)((undefined8)(value)>>32))
#define FIELD8(value,offset) (*(byte *)((byte *)&(value)+(offset)))
#define FIELD16(value,offset) (*(ushort *)((byte *)&(value)+(offset)))
#define FIELD32(value,offset) (*(uint *)((byte *)&(value)+(offset)))

extern uint DAT_00699b6e;
extern uint DAT_00699b72;
extern uint DAT_00699b76;
extern uint DAT_00699b7a;
static char DAT_006b9156[]="\n";
extern uint DAT_00704908;
extern uint DAT_0070490c;
extern signed char DAT_0070f242;
extern signed char DAT_0070f243;
extern signed char DAT_0070f244;
extern signed char DAT_0070f251;
extern signed char DAT_0070f252;
extern signed char DAT_0070f253;
extern signed char DAT_0070f266;
extern signed char DAT_0070f26c;
extern uint DAT_00710170;
extern uint DAT_0071067c;
extern ushort *DAT_00710990;
extern uint DAT_00710998;
extern code *PTR_FUN_006ac982;
static char s_IRO_LoopUnroller_Found_loop_with_006b997e[]="IRO_LoopUnroller:Found loop with header %d\n";
static char s_IroUnrollLoop_c_006b8ea6[]="IroUnrollLoop.c";
static char s_IsLoopUnrollable_No_because_Loop_006b90ce[]="IsLoopUnrollable:No because Loop Upper Bound is Variant in the loop\n";
static char s_IsLoopUnrollable_No_because_Loop_006b92a6[]="IsLoopUnrollable:No because Loop Upper Bound is has a side effect\n";
static char s_IsLoopUnrollable_No_because_Loop_006b938e[]="IsLoopUnrollable:No because Loop lower bound is has a side effect\n";
static char s_IsLoopUnrollable_No_because_a_un_006b919e[]="IsLoopUnrollable:No because a unique preheader could not be found\n";
static char s_IsLoopUnrollable_No_because_can__006b93d2[]="IsLoopUnrollable:No because can't figure out an iteration count\n";
static char s_IsLoopUnrollable_No_because_init_006b933e[]="IsLoopUnrollable:No because initial value of induction stored through pointer\n";
static char s_IsLoopUnrollable_No_because_loop_006b9226[]="IsLoopUnrollable:No because loop size greater than threshold\n";
static char s_IsLoopUnrollable_No_because_loop_006b9266[]="IsLoopUnrollable:No because loop test operator is unsupported\n";
static char s_IsLoopUnrollable_No_because_the_l_006b908a[]="IsLoopUnrollable:No because the loop form is currently unsupported\n";
static char s_IsLoopUnrollable_No_because_the_l_006b91e2[]="IsLoopUnrollable:No because the loop has already been vectorized\n";
static char s_IsLoopUnrollable_No_because_ther_006b92ea[]="IsLoopUnrollable:No because there is no initialization of loop index in PreHeader\n";
static char s_IsLoopUnrollable_No_due_to_prohi_006b9116[]="IsLoopUnrollable:No due to prohibited loop flags that are set ";
static char s_IsLoopUnrollable_No_due_to_requi_006b915a[]="IsLoopUnrollable:No due to required loop flags that are not set ";
static char s_IsWhileLoopUnrollable_No_because_006b9416[]="IsWhileLoopUnrollable:No because the loop form is currently unsupported\n";
static char s_IsWhileLoopUnrollable_No_because_006b9462[]="IsWhileLoopUnrollable:No because the preheader does not precede the InLoopHeaderTarget\n";
static char s_IsWhileLoopUnrollable_No_because_006b94ba[]="IsWhileLoopUnrollable:No because the preheader does not end with a goto\n";
static char s_IsWhileLoopUnrollable_No_because_006b9506[]="IsWhileLoopUnrollable:No because the InLoopHeaderTarget is the loop header\n";
static char s_IsWhileLoopUnrollable_No_because_006b9552[]="IsWhileLoopUnrollable:No because the while loop induction is signed\n";
static char s_IsWhileLoopUnrollable_No_because_006b959a[]="IsWhileLoopUnrollable:No because the while loop induction is not integral\n";
static char s_IsWhileLoopUnrollable_No_because_006b95e6[]="IsWhileLoopUnrollable:No because the while loop operator is not of decrement form\n";
static char s_IsWhileLoopUnrollable__No_becaus_006b963a[]="IsWhileLoopUnrollable: No because LP_IF_EXPR_NONCANONICAL \n";
static char s_IsWhileLoopUnrollable__No_becaus_006b9676[]="IsWhileLoopUnrollable: No because LP_IND_USED_IN_LOOP \n";
static char s_IsWhileLoopUnrollable__No_becaus_006b96ae[]="IsWhileLoopUnrollable: No because LP_HAS_MULTIPLE_EXITS \n";
static char s_IsWhileLoopUnrollable__No_becaus_006b96ea[]="IsWhileLoopUnrollable: No because LP_HAS_MULTIPLE_INDUCTIONS is not set \n";
static char s_IsWhileLoopUnrollable__No_becaus_006b9736[]="IsWhileLoopUnrollable: No because induction assignment operator is bad\n";
static char s_IsWhileLoopUnrollable__No_becaus_006b977e[]="IsWhileLoopUnrollable: No because PatternMatchWhileLoop returned false\n";
static char s_IsWhileLoopUnrollable__No_becaus_006b97c6[]="IsWhileLoopUnrollable: No because could not find induction with MOD and DIV operation\n";
static char s_IsWhileLoopUnrollable__No_becaus_006b981e[]="IsWhileLoopUnrollable: No because induction is signed\n";
static char s_IsWhileLoopUnrollable__No_becaus_006b9856[]="IsWhileLoopUnrollable: No because induction step is not one\n";
static char s_IsWhileLoopUnrollable__No_becaus_006b9896[]="IsWhileLoopUnrollable: No because induction EASS doesn't match pattern\n";
static char s_IsWhileLoopUnrollable__No_becaus_006b98de[]="IsWhileLoopUnrollable: No because induction assignment doesn't match pattern\n";
static char s_IsWhileLoopUnrollable__No_becaus_006b992e[]="IsWhileLoopUnrollable: No because NumberOfMatches or NumberOfAssigns is bad\n";
static char s_LeftOver____d__NeedOrigLoop____d_006b8eb6[]="\tLeftOver = %d, NeedOrigLoop = %d, NeedUnrollBodyTest = %d, ResetUnrolledFinalValue = %d\n";
static char s_Loop_includes__006b99aa[]="Loop includes: ";
static char s_UnrollForLoop_Aborting_due_to_fa_006b8fda[]="UnrollForLoop:Aborting due to failure of IRO_CopyLoopTestToLoopPreheaderAndBranchToSuccNode.\n";
static char s_UnrollForLoop_Aborting_due_to_no_006b8fa6[]="UnrollForLoop:Aborting due to no unique successor.\n";
static char s_UnrollForLoop_Aborting_due_unrol_006b8f76[]="UnrollForLoop:Aborting due unrollFactor == 0.";
static char s_Unrolling_loop_with_constant_ite_006b8f12[]="Unrolling loop with constant iteration count.\n";
static char s_Unrolling_loop_with_nonconstant_i_006b8f42[]="Unrolling loop with nonconstant iteration count.\n";
static char s______IterCount____d__VectorStrid_006b903a[]="---- IterCount = %d, VectorStride = %d, unrollFactor = %d\n";
static char s_while_n____loop_006b9076[]="while(n--) loop \n";
extern uint CError_Internal();
extern undefined8 CInt64_Add(undefined8, undefined8);
extern undefined8 CInt64_And(undefined8, undefined8);
extern byte CInt64_Equal(undefined8, undefined8);
extern byte CInt64_GreaterEqualU(undefined8, undefined8);
extern byte CInt64_Less(undefined8, undefined8);
extern byte CInt64_LessEqualU(undefined8, undefined8);
extern byte CInt64_LessU(undefined8, undefined8);
extern undefined8 CInt64_Mul(undefined8, undefined8);
extern undefined8 CInt64_MulU(undefined8, undefined8);
extern undefined8 CInt64_Neg(undefined8);
extern undefined8 CInt64_Not(undefined8);
extern undefined8 CInt64_Shl(undefined8, undefined8);
extern undefined8 CInt64_ShrU(undefined8, undefined8);
extern undefined8 CInt64_Sub(undefined8, undefined8);
extern uint FUN_00454260();
extern uint FUN_00455840();
extern undefined8 FUN_004d9a70(undefined8, undefined8);
extern undefined8 FUN_004d9aa0(undefined8, undefined8);
extern undefined8 FUN_004d9c50(undefined8, undefined8);
extern uint FUN_005a9cc0();
extern uint FUN_005a9d80();
extern uint FUN_005ab970(undefined8, uint);
extern uint FUN_005ac1e0();
extern uint FUN_005ac9f0();
extern uint FUN_005acdf0();
extern uint FUN_005acf30();
extern uint FUN_005ad1e0();
extern uint FUN_005ad220();
extern uint FUN_005ad280();
extern uint FUN_005ad400();
extern uint FUN_005ad440();
extern uint FUN_005ae7b0();
extern uint FUN_005aeed0();
extern uint FUN_005aef20();
extern uint FUN_005b07f0();
extern uint FUN_005b0850();
extern uint FUN_005b0960();
extern uint FUN_005b0990();
extern uint FUN_005b53d0();
extern uint FUN_005b5760();
extern uint FUN_005b5770();
extern uint FUN_005b7af0();
extern uint FUN_005b7d30();
extern uint FUN_005b7ea0();
extern uint FUN_005b7f10();
extern uint FUN_005b8d90();
extern uint FUN_005b9020();
extern uint FUN_005b9f10();
extern uint FUN_005bacc0();
extern uint FUN_005bd630();
extern uint FUN_005be150();
extern uint FUN_005be190();
extern uint FUN_005be430();
extern uint FUN_005be4b0();
extern uint FUN_005be690();
extern uint FUN_005bf2c0();
extern uint FUN_005bfb20();
extern undefined8 FUN_005bfdc0();
extern uint FUN_005c0470();
extern uint FUN_005c3060();
extern uint FUN_005c3130();
extern uint FUN_005c44a0();
extern uint FUN_005c44d0();
extern uint FUN_005c4510();
extern uint FUN_005c4550();
extern uint FUN_005c45f0();
extern uint FUN_005c4630();
extern uint FUN_005c46c0();
extern uint FUN_005c4710();
extern uint FUN_005c4830();
extern uint FUN_005c57e0();
extern uint FUN_005c5920();
extern uint FUN_005c59c0();
extern uint FUN_005c5e30();
extern uint FUN_005c5f40();
extern uint FUN_005ed4c0();
extern uint FUN_00613b50();
extern uint IroUtil_FindNextUse();
extern uint create_temp_object();
extern uint fn_0045faa0();

undefined4 fn_005ed720(int loop, NativePair count, undefined4 insertion);
void fn_005ed810(int param_1, int param_2, int param_3, undefined4 param_4, undefined4 param_5,
                 undefined4 param_6);
void fn_005ed930(undefined4 param_1, undefined4 *param_2);
void fn_005ed9f0(uint *param_1);
void fn_005edac0(uint *param_1, undefined8 nativeFactor);
void fn_005ee5d0(undefined4 param_1, int param_2, undefined4 param_3, undefined4 param_4);
void fn_005ee6e0(int param_1, undefined4 param_2, undefined8 *param_3, char param_4);
void fn_005ee810(int param_1, int param_2, undefined4 param_3, undefined4 param_4, int param_5);
undefined4
fn_005eef80(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, int param_7);
undefined4 fn_005ef150(int param_1, int param_2, int param_3, int param_4);
void fn_005ef6c0(int param_1, int param_2, int *param_3);
void fn_005efc20(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);
void fn_005f0590(int param_1, int *param_2);
undefined4
fn_005f09e0(int param_1, undefined4 param_2, undefined4 param_3, int param_4, int param_5);
undefined4
fn_005f0b60(int param_1, undefined4 param_2, undefined4 param_3, int param_4, int param_5);
undefined4 fn_005f0d50(int param_1, undefined4 param_2, undefined4 param_3, int param_4);
undefined4 fn_005f0f10(undefined4 param_1, int param_2);
byte IsLoopUnrollable(uint *param_1, undefined4 param_2, undefined4 param_3);
byte fn_005f12a0(uint *param_1, undefined4 param_2, undefined4 *param_3);
byte
fn_005f16b0(int param_1, undefined4 param_2, int param_3, undefined8 *param_4, int *param_5,
            int *param_6, int *param_7);
/* Baseline algorithm with the verified native AL Boolean return contract. */
byte fn_005f1bd0(NativePair a, NativePair b, NativePair *out);
void IRO_LoopUnroller(void);

undefined4 fn_005ed720(int loop, NativePair count, undefined4 insertion)
{
    NativeRange range;
    uint induction, linear, type, constantType, constant, copied, result;
    FUN_005ad280(&range);
    induction=*(uint *)(loop+0x2c);
    linear=*(uint *)(induction+10);
    type=FUN_005b7d30(*(uint *)(linear+0x12));
    constantType=type;
    if(*(byte *)type==12)constantType=FUN_005b5760();
    constant=NativeConstant(NativeMultiply(count,*(NativePair *)(*(uint *)(loop+0x2c)+0x30)),constantType);
    FUN_005ad220(constant,&range);
    copied=FUN_005acf30(*(uint *)(linear+0x2a),&range);
    result=FUN_005bd630(3);
    DAT_00710998++;
    *(uint *)(result+10)=DAT_00710998;
    if(*(byte *)(*(uint *)(loop+0x2c))&4)*(byte *)(result+1)=0x23;
    else *(byte *)(result+1)=0x22;
    *(uint *)(result+0x2a)=copied;
    *(uint *)(result+0x2e)=constant;
    *(uint *)(result+0x12)=type;
    FUN_005ad220(result,&range);
    FUN_005ad440(range.first,range.last,insertion);
    return range.last;
}


void fn_005ed810(int param_1, int param_2, int param_3, undefined4 param_4, undefined4 param_5,
                 undefined4 param_6)

{
  unsigned char nativeFrame[16];
#define local_20 ((undefined4 *)(nativeFrame+0))
#define local_18 (*(int *)(nativeFrame+8))
#define local_14 (*(undefined4 *)(nativeFrame+12))

  uint *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uVar2 = FUN_005b7d30(*(undefined4 *)(param_3 + 0x12));
  local_18 = FUN_005ab970(PACK(param_4,param_5), (uint)(uVar2));
  FUN_005ad220(local_18, param_2);
  local_14 = FUN_005acf30(param_3, param_2);
  iVar3 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar3 + 10) = DAT_00710998;
  *(undefined1 *)(iVar3 + 1) = 0x14;
  *(undefined4 *)(iVar3 + 0x2a) = local_14;
  *(int *)(iVar3 + 0x2e) = local_18;
  *(uint *)(local_18 + 2) = *(uint *)(local_18 + 2) | 2;
  *(undefined4 *)(iVar3 + 0x12) = uVar2;
  FUN_005ad220(iVar3, param_2);
  iVar4 = FUN_005bd630(0xb);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(int *)(iVar4 + 0x2e) = iVar3;
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2e) + 2);
  *puVar1 = *puVar1 | 2;
  *(undefined4 *)(iVar4 + 0x12) = uVar2;
  *(undefined4 *)(iVar4 + 0x2a) = param_6;
  FUN_005ad220(iVar4, param_2);
  if ((*(char *)(param_1 + 0x34) != '\0') && (*(int *)(param_1 + 0x4a) != 0)) {
    fn_005ed930((uint)(*(int *)(param_1 + 0x4a)), (uint *)(local_20));
    FUN_005ad220(local_20[0], param_2);
    iVar3 = FUN_005bd630(0xb);
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar3 + 10) = DAT_00710998;
    *(undefined4 *)(iVar3 + 0x2e) = *(undefined4 *)(param_2 + 4);
    puVar1 = (uint *)(*(int *)(iVar3 + 0x2e) + 2);
    *puVar1 = *puVar1 | 2;
    *(undefined4 *)(iVar3 + 0x12) = uVar2;
    *(undefined4 *)(iVar3 + 0x2a) = param_6;
    FUN_005ad220(iVar3, param_2);
  }
  return;
}
#undef local_20
#undef local_18
#undef local_14


void fn_005ed930(undefined4 param_1, undefined4 *param_2)

{
  unsigned char nativeFrame[40];
#define local_34 ((undefined1 *)(nativeFrame+0))

  byte *pbVar1;
  undefined4 uVar2;
  int iVar3;
  byte *unaff_EBX;
  FUN_005b7f10(local_34);
  FUN_005ad280(param_2);
  uVar2 = FUN_005bd630(0);
  FUN_005ad220(uVar2, param_2);
  FUN_005acf30(param_1, param_2);
  iVar3 = FUN_005b9020(0, *param_2);
  if (iVar3 == 0) {
    CError_Internal(s_IroUnrollLoop_c_006b8ea6, 0xe21);
  }
  uVar2 = FUN_005bacc0(iVar3);
  FUN_005b9f10(uVar2);
  FUN_005ad280(param_2);
  pbVar1 = *(byte **)(DAT_00710170 + 0x3e);
  *param_2 = (uint)pbVar1;
  for (; pbVar1 != (byte *)0x0; pbVar1 = *(byte **)(pbVar1 + 0x3e)) {
    if ((*pbVar1 != 0) && (*pbVar1 < 8)) {
      unaff_EBX = pbVar1;
    }
  }
  param_2[1] = (uint)unaff_EBX;
  *(undefined4 *)(param_2[1] + 0x3e) = 0;
  FUN_005b7ea0(local_34);
  return;
}
#undef local_34


void fn_005ed9f0(uint *param_1)

{
  unsigned char nativeFrame[52];
#define local_38 ((undefined1 *)(nativeFrame+0))
#define local_14 (*(undefined4 *)(nativeFrame+36))
#define local_10 (*(int *)(nativeFrame+40))
#define local_c (*(undefined4 *)(nativeFrame+44))
#define local_8 (*(int *)(nativeFrame+48))

  char cVar1;
  fn_0045faa0(param_1);
  if ((*param_1 & 0x8000) == 0) {
    FUN_005c0470(param_1, 1);
  }
  FUN_005c4630(param_1);
  FUN_005c4510(param_1);
  FUN_005c3060(param_1);
  local_10 = (int)DAT_0070f242;
  if (local_10 < 0) {
    local_14 = 0xffffffff;
  }
  else {
    local_14 = 0;
  }
  local_c = local_14;
  local_8 = local_10;
  cVar1 = IsLoopUnrollable((uint *)(param_1), (uint)(&local_14), (uint)(local_38));
  if (cVar1 != '\0') {
    if ((*param_1 & 0x8000) == 0) {
      fn_005edac0((uint *)(param_1), (undefined8)(PACK(local_14,local_10)));
    }
    else {
      fn_005efc20((int)(param_1), (uint)(local_14), (uint)(local_10), (uint)(local_38));
    }
    FUN_005be430();
    FUN_005be690();
    FUN_005be4b0();
  }
  FUN_005c45f0(param_1);
  FUN_005c44d0(param_1);
  return;
}
#undef local_38
#undef local_14
#undef local_10
#undef local_c
#undef local_8


void fn_005edac0(uint *param_1, undefined8 nativeFactor)

{
#define param_2 FIELD32(nativeFactor,0)
#define param_3 FIELD32(nativeFactor,4)

  unsigned char nativeFrame[128];
#define auStack_90 ((undefined1 *)(nativeFrame+0))
#define iStack_8c (*(int *)(nativeFrame+4))
#define iStack_88 (*(int *)(nativeFrame+8))
#define local_84 (*(uint *)(nativeFrame+12))
#define local_80 (*(int *)(nativeFrame+16))
#define uStack_7c (*(undefined8 *)(nativeFrame+20))
#define uStack_74 (*(undefined8 *)(nativeFrame+28))
#define uStack_6c (*(undefined4 *)(nativeFrame+36))
#define uStack_68 (*(undefined4 *)(nativeFrame+40))
#define local_64 (*(undefined8 *)(nativeFrame+44))
#define uStack_5c (*(undefined8 *)(nativeFrame+52))
#define auStack_54 ((undefined1 *)(nativeFrame+60))
#define bStack_4d (*(bool *)(nativeFrame+67))
#define iStack_4c (*(int *)(nativeFrame+68))
#define uStack_48 (*(undefined4 *)(nativeFrame+72))
#define local_42 (*(bool *)(nativeFrame+78))
#define local_41 (*(char *)(nativeFrame+79))
#define iStack_40 (*(int *)(nativeFrame+80))
#define local_39 (*(bool *)(nativeFrame+87))
#define local_38 (*(int *)(nativeFrame+88))
#define iStack_34 (*(int *)(nativeFrame+92))
#define iStack_30 (*(int *)(nativeFrame+96))
#define iStack_2c (*(int *)(nativeFrame+100))
#define puStack_28 (*(undefined1 * *)(nativeFrame+104))
#define uStack_24 (*(uint *)(nativeFrame+108))
#define uStack_20 (*(uint *)(nativeFrame+112))
#define uStack_1c (*(undefined4 *)(nativeFrame+116))
#define iStack_18 (*(int *)(nativeFrame+120))
#define iStack_14 (*(int *)(nativeFrame+124))

  uint *puVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  char *unaff_EBP;
  undefined8 uVar10;
  longlong lVar11;
  char *pcVar12;
  int *piVar13;
  if ((param_1[4] == param_1[5]) && (param_1[4] != param_1[8])) {
    *(byte *)&local_38 = 0;
  }
  else {
    *(byte *)&local_38 = 1;
  }
  local_42 = (char)param_1[0xd] != '\0';
  if (local_42) {
    cVar3 = CInt64_Equal(PACK(*(undefined4 *)((int)param_1 + 0x36),*(undefined4 *)((int)param_1 + 0x3a)), PACK(DAT_00699b6e,DAT_00699b72));
    local_42 = cVar3 == '\0';
  }
  if ((local_42 != false) && ((char)local_38 != '\0')) {
    uVar10 = CInt64_Sub(PACK(*(undefined4 *)((int)param_1 + 0x36),*(undefined4 *)((int)param_1 + 0x3a)), PACK(DAT_00699b76,DAT_00699b7a));
    *(undefined8 *)((int)param_1 + 0x36) = uVar10;
  }
  if (PTR_FUN_006ac982 == 0) {
    fn_005ef6c0((int)(param_1), (int)(1), (int *)(&param_2));
  }
  else {
    (*(code *)PTR_FUN_006ac982)(param_1, 1, &param_2);
  }
  if ((param_2 == 0) && (param_3 == 0)) {
    FUN_005ed4c0(s_UnrollForLoop_Aborting_due_unrol_006b8f76);
    return;
  }
  local_84 = param_2;
  local_80 = param_3;
  if ((char)param_1[0xd] == '\0') {
    local_39 = true;
    local_41 = '\x01';
    lVar11 = CONCAT44(DAT_0070490c, DAT_00704908);
  }
  else {
    uStack_68 = 1;
    uStack_6c = 0;
    uStack_74 = CInt64_MulU(PACK(param_2,param_3), PACK(0,1));
    local_64 = FUN_004d9a70(PACK(*(undefined4 *)((int)param_1 + 0x36),*(undefined4 *)((int)param_1 + 0x3a)), PACK(WORD0(uStack_74),WORD1(uStack_74)));
    local_39 = local_64 != 0;
    local_41 = CInt64_LessU(PACK(WORD0(uStack_74),WORD1(uStack_74)), PACK(*(undefined4 *)((int)param_1 + 0x36),*(undefined4 *)((int)param_1 + 0x3a)));
    lVar11 = local_64;
  }
  FIELD32(local_64,4) = (undefined4)((ulonglong)lVar11 >> 0x20);
  bStack_4d = !local_39 || local_41 == '\0';
  FUN_005ed4c0(s_LeftOver____d__NeedOrigLoop____d_006b8eb6, FIELD32(local_64,4), local_39, local_41,
               bStack_4d);
  local_64 = lVar11;
  if (local_42) {
    pcVar12 = s_Unrolling_loop_with_constant_ite_006b8f12;
  }
  else {
    pcVar12 = s_Unrolling_loop_with_nonconstant_i_006b8f42;
  }
  FUN_005ed4c0(pcVar12);
  FUN_005c5e30(param_1, &iStack_18, auStack_54);
  if (iStack_18 == 0) {
    FUN_005ed4c0(s_UnrollForLoop_Aborting_due_to_no_006b8fa6);
    return;
  }
  cVar3 = FUN_005c5f40(param_1, auStack_90, iStack_18, &iStack_30, 0);
  if (cVar3 == '\0') {
    FUN_005ed4c0(s_UnrollForLoop_Aborting_due_to_fa_006b8fda);
    return;
  }
  uStack_1c = *(undefined4 *)(*(int *)(param_1[8] + 0x10) + 0x2a);
  uVar5 = param_1[7];
  uStack_48 = FUN_005a9cc0();
  if(**(undefined1 **)(uVar5 + 0x14)!=8 && **(undefined1 **)(uVar5 + 0x14)!=9 && **(undefined1 **)(uVar5 + 0x14)!=10 && **(undefined1 **)(uVar5 + 0x14)!=11 && **(undefined1 **)(uVar5 + 0x14)!=14) {
    uVar8 = param_1[4];
    if (uVar8 == param_1[5]) {
      for (pcVar12 = *(char **)(uVar8 + 0x10); pcVar12 != *(char **)(uVar8 + 0x14);
          pcVar12 = *(char **)(pcVar12 + 0x3e)) {
        if ((*pcVar12 != '\0') && ((*(uint *)(pcVar12 + 2) & 2) == 0)) {
          unaff_EBP = pcVar12;
        }
      }
      uVar8 = FUN_005be150();
      param_1[4] = uVar8;
      *(undefined4 *)(param_1[4] + 0x10) = *(undefined4 *)(unaff_EBP + 0x3e);
      *(undefined4 *)(param_1[4] + 0x14) = *(undefined4 *)(param_1[5] + 0x14);
      *(char **)(param_1[5] + 0x14) = unaff_EBP;
      *(undefined4 *)(param_1[4] + 0x30) = *(undefined4 *)(param_1[5] + 0x30);
      *(uint *)(param_1[5] + 0x30) = param_1[4];
    }
    if (**(char **)(param_1[4] + 0x10) == '\r') {
      uVar6 = *(undefined4 *)(*(char **)(param_1[4] + 0x10) + 0x2a);
    }
    else {
      uVar6 = FUN_005a9cc0();
      iVar4 = FUN_005bd630(0xd);
      *(int *)(iVar4 + 10) = DAT_00710998;
      DAT_00710998 = DAT_00710998 + 1;
      *(undefined4 *)(iVar4 + 0x2a) = uVar6;
      *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 1;
      FUN_005ad440(iVar4, iVar4, *(undefined4 *)(param_1[4] + 0x10));
    }
    iVar4 = FUN_005bd630(8);
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar4 + 10) = DAT_00710998;
    *(undefined4 *)(iVar4 + 0x2a) = uVar6;
    FUN_005ad400(iVar4, iVar4, *(undefined4 *)(uVar5 + 0x14));
  }
  pcVar12 = *(char **)(param_1[5] + 0x10);
  cVar3 = *pcVar12;
  while (cVar3 == '\r') {
    pcVar12 = *(char **)(pcVar12 + 0x3e);
    cVar3 = *pcVar12;
  }
  puStack_28 = *(undefined1 **)(iStack_30 + 0x14);
  FUN_005ad280(&iStack_8c);
  if ((char)local_38 == '\0') {
    uStack_5c = CONCAT44(DAT_0070490c, DAT_00704908);
  }
  else {
    uStack_5c = FUN_005bfdc0(param_1[0xb]);
  }
  iVar4 = fn_005ef150((int)(&iStack_8c), (int)(param_1), (int)(WORD0(uStack_5c)), (int)(WORD1(uStack_5c)));
  FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
  FIELD32(uStack_74,0) = iStack_8c;
  pcVar12 = (char *)IroUtil_FindNextUse(iVar4);
  if ((pcVar12 != (char *)0x0) && (*pcVar12 == '\x03') && (pcVar12[1] == '\x1e') &&
     (*(int *)(pcVar12 + 0x2a) == iVar4)) {
    cVar3 = FUN_005b07f0(*(undefined4 *)(pcVar12 + 0x2e));
    if (cVar3 != '\0') {
      iVar4 = *(int *)(pcVar12 + 0x2e);
    }
  }
  FUN_005ad280(&iStack_8c);
  local_84 = fn_005eef80((uint)(iVar4), (uint)(param_2), (uint)(param_3), (uint)(WORD0(local_64)), (uint)(WORD1(local_64)), (uint)(&iStack_8c), (int)(param_1));
  FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
  pcVar12 = (char *)IroUtil_FindNextUse(local_84);
  if ((pcVar12 != (char *)0x0) && (*pcVar12 == '\x03') &&
     (pcVar12[1] == '\x1e' && (*(int *)(pcVar12 + 0x2a) == local_84))) {
    cVar3 = FUN_005b07f0(*(undefined4 *)(pcVar12 + 0x2e));
    if (cVar3 != '\0') {
      local_84 = *(uint *)(pcVar12 + 0x2e);
    }
  }
  FUN_005ad280(&iStack_8c);
  fn_005ed810((int)(param_1), (int)(&iStack_8c), (int)(iVar4), (uint)(param_2), (uint)(param_3), (uint)(uStack_48));
  FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
  uStack_24 = iStack_88;
  uVar6 = FUN_005a9cc0();
  if (DAT_0070f266 != '\0') {
    FUN_005ad280(&iStack_8c);
    iStack_40 = FUN_005bd630(8);
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iStack_40 + 10) = DAT_00710998;
    *(undefined4 *)(iStack_40 + 0x2a) = uVar6;
    FUN_005ad220(iStack_40, &iStack_8c);
    FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
    iStack_14 = iStack_40;
  }
  FUN_005ad280(&iStack_8c);
  uVar7 = FUN_005aef20();
  FUN_005ad220(uVar7, &iStack_8c);
  iStack_4c = *(undefined4 *)(iStack_88 + 0x2a);
  FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
  local_38 = iStack_8c;
  FIELD32(uStack_5c,0) = DAT_00704908;
  FIELD32(uStack_5c,4) = DAT_0070490c;
  FIELD32(uStack_7c,4) = DAT_0070490c;
  FIELD32(uStack_7c,0) = DAT_00704908;
  cVar3 = CInt64_Less(PACK(DAT_00704908,DAT_0070490c), PACK(param_2,param_3));
  while (cVar3 != '\0') {
    fn_005ee6e0((int)(param_1), (uint)(*(undefined4 *)(uVar5 + 0x14)), (undefined8 *)(&uStack_5c), (char)(uStack_7c != 0));
    lVar11 = CInt64_Add(PACK(WORD0(uStack_7c),WORD1(uStack_7c)), PACK(DAT_00699b76,DAT_00699b7a));
    uStack_7c = lVar11;
    cVar3 = CInt64_Less(PACK(WORD0(lVar11),WORD1(lVar11)), PACK(param_2,param_3));
  }
  uStack_20 = fn_005ed720((int)(param_1), NativeWords(param_2,param_3), (uint)(*(undefined4 *)(uVar5 + 0x14)));
  FUN_005ad280(&iStack_8c);
  iStack_34 = FUN_005bd630(0xd);
  *(int *)(iStack_34 + 10) = DAT_00710998;
  DAT_00710998 = DAT_00710998 + 1;
  *(undefined4 *)(iStack_34 + 0x2a) = uVar6;
  *(uint *)(iStack_34 + 2) = *(uint *)(iStack_34 + 2) | 1;
  FUN_005ad220(iStack_34, &iStack_8c);
  FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
  FUN_005ad280(&iStack_8c);
  uVar6 = FUN_005c46c0(param_1);
  FUN_005acf30(uVar6, &iStack_8c);
  iStack_2c = iStack_88;
  if (bStack_4d) {
    piVar13 = &iStack_8c;
    uVar8 = FUN_005c4710(param_1);
  }
  else {
    piVar13 = &iStack_8c;
    uVar8 = local_84;
  }
  FUN_005acf30(uVar8, piVar13);
  iVar4 = FUN_005bd630(*(undefined1 *)param_1[9]);
  uVar8 = param_1[9];
  iVar9 = 0;
  do {
    *(undefined4 *)(iVar9 + iVar4) = *(undefined4 *)(iVar9 + uVar8);
    *(undefined4 *)(iVar9 + 4 + iVar4) = *(undefined4 *)(iVar9 + 4 + uVar8);
    *(undefined4 *)(iVar9 + 8 + iVar4) = *(undefined4 *)(iVar9 + 8 + uVar8);
    *(undefined4 *)(iVar9 + 0xc + iVar4) = *(undefined4 *)(iVar9 + 0xc + uVar8);
    iVar9 = iVar9 + 0x10;
  } while (iVar9 < 0x40);
  *(undefined2 *)(iVar4 + 0x40) = *(undefined2 *)(uVar8 + 0x40);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(undefined4 *)(iVar4 + 0x3e) = 0;
  *(undefined4 *)(iVar4 + 0x1a) = 0;
  if ((*param_1 & 1) == 0) {
    *(int *)(iVar4 + 0x2a) = iStack_88;
    *(int *)(iVar4 + 0x2e) = iStack_2c;
  }
  else {
    *(int *)(iVar4 + 0x2a) = iStack_2c;
    *(int *)(iVar4 + 0x2e) = iStack_88;
  }
  FUN_005ad220(iVar4, &iStack_8c);
  FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
  local_84 = iStack_88;
  FUN_005ad280(&iStack_8c);
  iVar4 = FUN_005bd630(**(undefined1 **)(param_1[4] + 0x14));
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  FUN_005ad220(iVar4, &iStack_8c);
  *(int *)(iVar4 + 0x2a) = iStack_4c;
  *(uint *)(iVar4 + 0x2e) = local_84;
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2e) + 2);
  *puVar1 = *puVar1 | 2;
  uVar6 = FUN_005b7d30(*(undefined4 *)(*(int *)(param_1[4] + 0x14) + 0x12));
  *(undefined4 *)(iVar4 + 0x12) = uVar6;
  FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
  iStack_4c = iStack_88;
  FUN_005ad280(&iStack_8c);
  iStack_2c = FUN_005bd630(0xd);
  *(int *)(iStack_2c + 10) = DAT_00710998;
  DAT_00710998 = DAT_00710998 + 1;
  *(undefined4 *)(iStack_2c + 0x2a) = uStack_48;
  *(uint *)(iStack_2c + 2) = *(uint *)(iStack_2c + 2) | 1;
  FUN_005ad220(iStack_2c, &iStack_8c);
  FUN_005ad440(iStack_8c, iStack_88, *(undefined4 *)(uVar5 + 0x14));
  local_84 = *(uint *)(uVar5 + 0x14);
  uStack_48 = *(undefined4 *)(uVar5 + 0x30);
  *(int *)(uVar5 + 0x10) = (int)uStack_74;
  *(uint *)(uVar5 + 0x14) = uStack_24;
  uStack_24 = 0;
  if (DAT_0070f266 != '\0') {
    uStack_24 = FUN_005be150();
    *(int *)(uStack_24 + 0x10) = iStack_14;
    *(int *)(uStack_24 + 0x14) = iStack_40;
    *(uint *)(uVar5 + 0x30) = uStack_24;
  }
  iVar4 = FUN_005be150();
  *(int *)(iVar4 + 0x10) = local_38;
  *(uint *)(iVar4 + 0x14) = uStack_20;
  *(int *)(*(int *)(local_38 + 0x2a) + 4) = iVar4;
  if (uStack_24 == 0) {
    *(int *)(uVar5 + 0x30) = iVar4;
  }
  else {
    *(int *)(uStack_24 + 0x30) = iVar4;
  }
  uStack_20 = FUN_005be150();
  *(int *)(uStack_20 + 0x10) = iStack_34;
  *(int *)(uStack_20 + 0x14) = iStack_4c;
  *(uint *)(*(int *)(iStack_34 + 0x2a) + 4) = uStack_20;
  *(uint *)(iVar4 + 0x30) = uStack_20;
  uVar8 = FUN_005be150();
  *(int *)(uVar8 + 0x10) = iStack_2c;
  *(uint *)(uVar8 + 0x14) = local_84;
  *(uint *)(uStack_20 + 0x30) = uVar8;
  *(undefined4 *)(uVar8 + 0x30) = uStack_48;
  if (DAT_0071067c == uVar5) {
    DAT_0071067c = uVar8;
  }
  if ((DAT_0070f253 != '\0') && (local_42) && (local_64 != 0)) {
    fn_005ee5d0((uint)(param_1), (int)(uStack_20), (uint)(WORD0(local_64)), (uint)(WORD1(local_64)));
    local_39 = false;
  }
  if (!local_39) {
    for (uVar8 = param_1[8]; uVar8 != 0 && (uVar8 != *(uint *)(param_1[4] + 0x30));
        uVar8 = *(uint *)(uVar8 + 0x30)) {
      pcVar2 = *(char **)(uVar8 + 0x14);
      for (pcVar12 = *(char **)(uVar8 + 0x10); pcVar12 != (char *)0x0;
          pcVar12 = *(char **)(pcVar12 + 0x3e)) {
        if (*pcVar12 != '\r') {
          *pcVar12 = '\0';
        }
        if (pcVar12 == pcVar2) break;
      }
    }
    pcVar2 = *(char **)(*(int *)(param_1[0xb] + 6) + 0x14);
    for (pcVar12 = *(char **)(*(int *)(param_1[0xb] + 6) + 0x10); pcVar12 != (char *)0x0;
        pcVar12 = *(char **)(pcVar12 + 0x3e)) {
      if (*pcVar12 != '\r') {
        *pcVar12 = '\0';
      }
      if (pcVar12 == pcVar2) break;
    }
    FUN_005ae7b0(*(undefined4 *)(*(int *)(uVar5 + 0x14) + 0x2e));
    **(undefined1 **)(uVar5 + 0x14) = 0;
    *(undefined4 *)(local_84 + 0x2a) = uStack_1c;
    uVar8 = local_84;
  }
  if (local_41 == '\0') {
    FUN_005ae7b0(*(undefined4 *)(puStack_28 + 0x2e));
    *puStack_28 = 0;
    FUN_005ae7b0(*(undefined4 *)(*(int *)(uStack_20 + 0x14) + 0x2e));
    **(undefined1 **)(uStack_20 + 0x14) = 0;
    uVar8 = uStack_20;
    if (uStack_24 != 0) {
      **(undefined1 **)(uStack_24 + 0x14) = 0;
      uVar8 = uStack_24;
    }
    for (iVar4 = *(int *)(uVar5 + 0x10); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x3e)) {
      if ((*(uint *)(iVar4 + 2) & 2) == 0) {
        FUN_005ae7b0(iVar4);
      }
      if (iVar4 == *(int *)(uVar5 + 0x14)) {
        return;
      }
    }
  }
  return;
}
#undef auStack_90
#undef iStack_8c
#undef iStack_88
#undef local_84
#undef local_80
#undef uStack_7c
#undef uStack_74
#undef uStack_6c
#undef uStack_68
#undef local_64
#undef uStack_5c
#undef auStack_54
#undef bStack_4d
#undef iStack_4c
#undef uStack_48
#undef local_42
#undef local_41
#undef iStack_40
#undef local_39
#undef local_38
#undef iStack_34
#undef iStack_30
#undef iStack_2c
#undef puStack_28
#undef uStack_24
#undef uStack_20
#undef uStack_1c
#undef iStack_18
#undef iStack_14
#undef param_2
#undef param_3


void fn_005ee5d0(undefined4 param_1, int param_2, undefined4 param_3, undefined4 param_4)

{
  unsigned char nativeFrame[8];
#define local_14 (*(int *)(nativeFrame+0))
#define local_10 (*(undefined4 *)(nativeFrame+4))

  char cVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  undefined4 uVar5;
  iVar2 = FUN_005be150();
  iVar3 = FUN_005bd630(0);
  *(int *)(iVar3 + 10) = DAT_00710998;
  DAT_00710998 = DAT_00710998 + 1;
  *(undefined4 *)(iVar3 + 0x3e) = 0;
  *(uint *)(iVar3 + 2) = *(uint *)(iVar3 + 2) | 1;
  *(int *)(iVar2 + 0x14) = iVar3;
  *(undefined4 *)(iVar2 + 0x10) = *(undefined4 *)(iVar2 + 0x14);
  *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(param_2 + 0x30);
  *(int *)(param_2 + 0x30) = iVar2;
  *(undefined4 *)(iVar3 + 0x3e) = *(undefined4 *)(*(int *)(param_2 + 0x14) + 0x3e);
  *(int *)(*(int *)(param_2 + 0x14) + 0x3e) = iVar3;
  local_14 = DAT_00704908;
  local_10 = DAT_0070490c;
  iVar3 = DAT_00704908;
  uVar5 = DAT_0070490c;
  cVar1 = CInt64_Less(PACK(DAT_00704908,DAT_0070490c), PACK(param_3,param_4));
  lVar4 = CONCAT44(uVar5, iVar3);
  while (cVar1 != '\0') {
    fn_005ee6e0((int)(param_1), (uint)(*(undefined4 *)(iVar2 + 0x14)), (undefined8 *)(&local_14), (char)(lVar4 != 0));
    lVar4 = CInt64_Add(PACK(WORD0(lVar4),WORD1(lVar4)), PACK(DAT_00699b76,DAT_00699b7a));
    cVar1 = CInt64_Less(PACK(WORD0(lVar4),WORD1(lVar4)), PACK(param_3,param_4));
  }
  fn_005ed720((int)(param_1), NativeWords(param_3,param_4), (uint)(*(undefined4 *)(iVar2 + 0x14)));
  return;
}
#undef local_14
#undef local_10


void fn_005ee6e0(int param_1, undefined4 param_2, undefined8 *param_3, char param_4)

{
  unsigned char nativeFrame[16];
#define local_20 (*(int *)(nativeFrame+0))
#define local_1c (*(int *)(nativeFrame+4))
#define local_18 (*(char * *)(nativeFrame+8))
#define local_14 (*(int *)(nativeFrame+12))

  byte *pbVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined8 uVar6;
  iVar5 = 0;
  iVar3 = 0;
  for (local_14 = *(int *)(param_1 + 0x20); local_14 != 0 &&
      (local_14 != *(int *)(*(int *)(param_1 + 0x10) + 0x30)); local_14 = *(int *)(local_14 + 0x30))
  {
    FUN_005ad280(&local_20);
    local_18 = *(char **)(*(int *)(local_14 + 0x14) + 0x3e);
    pcVar4 = *(char **)(local_14 + 0x10);
    if (pcVar4 != local_18) {
      do {
        cVar2 = FUN_005c44a0(param_1, pcVar4);
        if (cVar2 == '\0') {
          if (*(int *)(pcVar4 + 0xe) != 0) {
            pbVar1 = (byte *)(*(int *)(pcVar4 + 0xe) + 6);
            *pbVar1 = *pbVar1 | 0x10;
          }
          cVar2 = FUN_005c4550(param_1, pcVar4);
          if ((cVar2 == '\0') && (*pcVar4 != '\r') && ((*(uint *)(pcVar4 + 2) & 2) == 0) &&
             (FUN_005acf30(pcVar4, &local_20), iVar3 = local_1c, iVar5 == 0)) {
            iVar5 = local_20;
          }
        }
        pcVar4 = *(char **)(pcVar4 + 0x3e);
      } while (pcVar4 != local_18);
    }
    if ((local_20 != 0) && (local_1c != 0)) {
      FUN_005ad440(local_20, local_1c, param_2);
    }
  }
  if (param_4 != '\0') {
    uVar6 = FUN_005bfdc0(*(undefined4 *)(param_1 + 0x2c));
    uVar6 = CInt64_Add(PACK(*(undefined4 *)param_3,*(undefined4 *)((int)param_3 + 4)), PACK(WORD0(uVar6),WORD1(uVar6)));
    *param_3 = uVar6;
    fn_005ee810((int)(iVar5), (int)(iVar3), (uint)(*(undefined4 *)param_3), (uint)(*(undefined4 *)((int)param_3 + 4)), (int)(param_1));
  }
  return;
}
#undef local_20
#undef local_1c
#undef local_18
#undef local_14


void fn_005ee810(int param_1, int param_2, undefined4 param_3, undefined4 param_4, int param_5)

{
  unsigned char nativeFrame[96];
#define local_70 (*(undefined4 *)(nativeFrame+0))
#define local_6c (*(undefined4 *)(nativeFrame+4))
#define local_68 (*(undefined8 *)(nativeFrame+8))
#define local_60 (*(undefined4 *)(nativeFrame+16))
#define local_5c (*(undefined4 *)(nativeFrame+20))
#define local_58 (*(undefined4 *)(nativeFrame+24))
#define local_54 (*(undefined4 *)(nativeFrame+28))
#define local_50 (*(undefined8 *)(nativeFrame+32))
#define local_48 (*(undefined8 *)(nativeFrame+40))
#define local_40 (*(undefined8 *)(nativeFrame+48))
#define local_38 (*(undefined8 *)(nativeFrame+56))
#define local_30 (*(undefined8 *)(nativeFrame+64))
#define local_28 (*(int *)(nativeFrame+72))
#define local_24 (*(char * *)(nativeFrame+76))
#define local_20 (*(int *)(nativeFrame+80))
#define local_1c (*(char * *)(nativeFrame+84))
#define local_18 (*(char * *)(nativeFrame+88))
#define local_14 (*(char *)(nativeFrame+92))
#define local_13 (*(char *)(nativeFrame+93))
#define local_12 (*(char *)(nativeFrame+94))
#define local_11 (*(char *)(nativeFrame+95))

  uint *puVar1;
  undefined8 *puVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  undefined4 uVar9;
  bool bVar10;
  undefined8 uVar11;
  local_1c = (char *)FUN_005b7d30(*(undefined4 *)(*(int *)(*(int *)(param_5 + 0x2c) + 10) + 0x12));
  local_14 = FUN_00454260(local_1c);
  local_28 = param_1;
  do {
    if (local_28 == 0) {
      return;
    }
    local_20 = *(int *)(local_28 + 0x3e);
    iVar4 = FUN_005b0990(local_28);
    if (iVar4 != 0) {
      cVar3 = FUN_00455840(*(undefined4 *)(*(int *)(*(int *)(param_5 + 0x2c) + 2) + 4), iVar4);
      if (cVar3 != '\0') {
        iVar4 = FUN_005bd630(3);
        DAT_00710998 = DAT_00710998 + 1;
        *(int *)(iVar4 + 10) = DAT_00710998;
        *(undefined1 *)(iVar4 + 1) = 0xf;
        *(char **)(iVar4 + 0x12) = local_1c;
        pcVar5 = (char *)IroUtil_FindNextUse(local_28);
        local_11 = '\0';
        local_12 = '\x01';
        if ((pcVar5 != (char *)0x0) && (*pcVar5 == '\x02') && (pcVar5[1] == '2')) {
          local_24 = (char *)FUN_005b7d30(*(undefined4 *)(pcVar5 + 0x12));
          pcVar5 = (char *)IroUtil_FindNextUse(pcVar5);
          local_11 = '\x01';
          if ((*local_24 != **(char **)(local_28 + 0x12)) ||
             (*(int *)(local_24 + 2) < *(int *)(*(char **)(local_28 + 0x12) + 2))) {
            local_12 = '\0';
          }
        }
        local_13 = '\0';
        if ((DAT_0070f26c == '\0') || (local_12 == '\0') ||
           (pcVar5 == (char *)0x0 || (*pcVar5 != '\x03' || (pcVar5[1] != '\x0f')))) {
          if ((DAT_0070f26c != '\0') &&
             (local_12 != '\0' && (pcVar5 != (char *)0x0) && (*pcVar5 == '\x03') &&
             (pcVar5[1] == '\t'))) {
            cVar3 = FUN_005b07f0(*(undefined4 *)(pcVar5 + 0x2e));
            if (cVar3 != '\0') {
              pcVar6 = (char *)IroUtil_FindNextUse(pcVar5);
              if ((pcVar6 != (char *)0x0) && (*pcVar6 == '\x03') && (pcVar6[1] == '\x0f')) {
                pcVar6 = (char *)IroUtil_FindNextUse(pcVar6);
                if ((pcVar6 != (char *)0x0) && (*pcVar6 == '\x03') && (pcVar6[1] == '\x11')) {
                  cVar3 = FUN_005b07f0(*(undefined4 *)(pcVar6 + 0x2e));
                  if (cVar3 != '\0') {
                    pcVar7 = (char *)IroUtil_FindNextUse(pcVar6);
                    if ((pcVar7 != (char *)0x0) && (*pcVar7 == '\x03') && (pcVar7[1] == '\x0f') &&
                       (*(char **)(pcVar7 + 0x2e) == pcVar6)) {
                      FUN_005ad280(&local_58);
                      uVar11 = CInt64_Shl(PACK(DAT_00699b76,DAT_00699b7a), PACK(*(undefined4 *)
                                           (*(int *)(*(int *)(pcVar6 + 0x2e) + 0x2a) + 0x10),*(undefined4 *)
                                           (*(int *)(*(int *)(pcVar6 + 0x2e) + 0x2a) + 0x14)));
                      local_38 = uVar11;
                      if (local_14 == '\0') {
                        uVar11 = CInt64_Mul(PACK(WORD0(uVar11),WORD1(uVar11)), PACK(param_3,param_4));
                      }
                      else {
                        uVar11 = CInt64_MulU(PACK(WORD0(uVar11),WORD1(uVar11)), PACK(param_3,param_4));
                      }
                      local_30 = uVar11;
                      if (local_14 == '\0') {
                        uVar11 = CInt64_Mul(PACK(*(undefined4 *)
                                             (*(int *)(*(int *)(pcVar5 + 0x2e) + 0x2a) + 0x10),*(undefined4 *)
                                             (*(int *)(*(int *)(pcVar5 + 0x2e) + 0x2a) + 0x14)), PACK(WORD0(uVar11),WORD1(uVar11)));
                      }
                      else {
                        uVar11 = CInt64_MulU(PACK(*(undefined4 *)
                                              (*(int *)(*(int *)(pcVar5 + 0x2e) + 0x2a) + 0x10),*(undefined4 *)
                                              (*(int *)(*(int *)(pcVar5 + 0x2e) + 0x2a) + 0x14)), PACK(WORD0(uVar11),WORD1(uVar11)));
                      }
                      local_18 = *(char **)(pcVar7 + 0x12);
                      if (*local_18 == '\f') {
                        local_50 = uVar11;
                        pcVar5 = (char *)FUN_005b5760();
                        uVar11 = local_50;
                      }
                      else {
                        pcVar5 = local_1c;
                        if (local_11 != '\0') {
                          pcVar5 = local_24;
                        }
                      }
                      local_50 = uVar11;
                      iVar8 = FUN_005ab970(uVar11, (uint)(pcVar5));
                      FUN_005ad220(iVar8, &local_58);
                      *(int *)(pcVar7 + 0x2e) = iVar8;
                      *(uint *)(iVar8 + 2) = *(uint *)(iVar8 + 2) | 2;
                      FUN_005ad440(local_58, local_54, pcVar7);
                      FUN_005ad280(&local_58);
                      *(char **)(iVar4 + 0x2a) = pcVar7;
                      *(char **)(iVar4 + 0x2e) = pcVar6;
                      *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
                      *(undefined4 *)(iVar4 + 0x12) = *(undefined4 *)(pcVar7 + 0x12);
                      FUN_005ac9f0(pcVar7, iVar4);
                      FUN_005ad220(iVar4, &local_58);
                      FUN_005ad400(local_58, local_54, pcVar7);
                      local_13 = '\x01';
                    }
                  }
                }
              }
              goto LAB_005eeb86;
            }
          }
          if ((local_12 != '\0') && (pcVar5 != (char *)0x0) &&
             (*pcVar5 == '\x03' && (pcVar5[1] == '\x11' || (pcVar5[1] == '\t')))) {
            cVar3 = FUN_005b07f0(*(undefined4 *)(pcVar5 + 0x2e));
            if (cVar3 != '\0') {
              pcVar6 = (char *)IroUtil_FindNextUse(pcVar5);
              if ((pcVar6 != (char *)0x0) && (*pcVar6 == '\x03') && (pcVar6[1] == '\x0f') &&
                 (*(char **)(pcVar6 + 0x2e) == pcVar5)) {
                iVar8 = IroUtil_FindNextUse(pcVar6);
                if (iVar8 != 0) {
                  FUN_005ad280(&local_60);
                  puVar2 = (undefined8 *)(*(int *)(*(int *)(pcVar5 + 0x2e) + 0x2a) + 0x10);
                  uVar11 = *puVar2;
                  if (pcVar5[1] == '\x11') {
                    uVar11 = CInt64_Shl(PACK(DAT_00699b76,DAT_00699b7a), PACK(*(undefined4 *)puVar2,*(undefined4 *)
                                         (*(int *)(*(int *)(pcVar5 + 0x2e) + 0x2a) + 0x14)));
                  }
                  if (local_14 == '\0') {
                    uVar11 = CInt64_Mul(PACK(WORD0(uVar11),WORD1(uVar11)), PACK(param_3,param_4));
                  }
                  else {
                    uVar11 = CInt64_MulU(PACK(WORD0(uVar11),WORD1(uVar11)), PACK(param_3,param_4));
                  }
                  local_18 = *(char **)(pcVar6 + 0x12);
                  if (*local_18 == '\f') {
                    local_40 = uVar11;
                    pcVar5 = (char *)FUN_005b5760();
                    uVar11 = local_40;
                  }
                  else {
                    pcVar5 = local_1c;
                    if (local_11 != '\0') {
                      pcVar5 = local_24;
                    }
                  }
                  local_40 = uVar11;
                  uVar9 = FUN_005ab970(uVar11, (uint)(pcVar5));
                  FUN_005ad220(uVar9, &local_60);
                  FUN_005ad220(iVar4, &local_60);
                  *(undefined4 *)(iVar4 + 0x2e) = uVar9;
                  FUN_005ad440(local_60, local_5c, iVar8);
                  FUN_005ac9f0(pcVar6, iVar4);
                  *(char **)(iVar4 + 0x2a) = pcVar6;
                  uVar9 = FUN_005b7d30(*(undefined4 *)(pcVar6 + 0x12));
                  *(undefined4 *)(iVar4 + 0x12) = uVar9;
                  local_13 = '\x01';
                }
              }
            }
          }
        }
        else {
          pcVar5 = (char *)IroUtil_FindNextUse(pcVar5);
          if ((pcVar5 != (char *)0x0) && (*pcVar5 == '\x03') && (pcVar5[1] == '\x11')) {
            cVar3 = FUN_005b07f0(*(undefined4 *)(pcVar5 + 0x2e));
            if (cVar3 != '\0') {
              pcVar6 = (char *)IroUtil_FindNextUse(pcVar5);
              if ((pcVar6 != (char *)0x0) && (*pcVar6 == '\x03') &&
                 (pcVar6[1] == '\x0f' && (*(char **)(pcVar6 + 0x2e) == pcVar5))) {
                FUN_005ad280(&local_70);
                uVar11 = CInt64_Shl(PACK(DAT_00699b76,DAT_00699b7a), PACK(*(undefined4 *)(*(int *)(*(int *)(pcVar5 + 0x2e) + 0x2a) + 0x10),*(undefined4 *)
                                       (*(int *)(*(int *)(pcVar5 + 0x2e) + 0x2a) + 0x14)));
                local_68 = uVar11;
                if (local_14 == '\0') {
                  uVar11 = CInt64_Mul(PACK(WORD0(uVar11),WORD1(uVar11)), PACK(param_3,param_4));
                }
                else {
                  uVar11 = CInt64_MulU(PACK(WORD0(uVar11),WORD1(uVar11)), PACK(param_3,param_4));
                }
                local_18 = *(char **)(pcVar6 + 0x12);
                if (*local_18 == '\f') {
                  local_48 = uVar11;
                  pcVar7 = (char *)FUN_005b5760();
                  uVar11 = local_48;
                }
                else {
                  pcVar7 = local_1c;
                  if (local_11 != '\0') {
                    pcVar7 = local_24;
                  }
                }
                local_48 = uVar11;
                iVar8 = FUN_005ab970(uVar11, (uint)(pcVar7));
                FUN_005ad220(iVar8, &local_70);
                *(int *)(pcVar6 + 0x2e) = iVar8;
                *(uint *)(iVar8 + 2) = *(uint *)(iVar8 + 2) | 2;
                FUN_005ad440(local_70, local_6c, pcVar6);
                FUN_005ad280(&local_70);
                *(char **)(iVar4 + 0x2a) = pcVar6;
                *(char **)(iVar4 + 0x2e) = pcVar5;
                *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
                uVar9 = FUN_005b7d30(*(undefined4 *)(pcVar6 + 0x12));
                *(undefined4 *)(iVar4 + 0x12) = uVar9;
                FUN_005ac9f0(pcVar6, iVar4);
                FUN_005ad220(iVar4, &local_70);
                FUN_005ad400(local_70, local_6c, pcVar6);
                local_13 = '\x01';
              }
            }
          }
        }
LAB_005eeb86:
        if (local_13 == '\0') {
          pcVar5 = local_1c;
          if (*local_1c == '\f') {
            pcVar5 = (char *)FUN_005b5760();
          }
          iVar8 = FUN_005ab970(PACK(param_3,param_4), (uint)(pcVar5));
          *(int *)(iVar4 + 0x2e) = iVar8;
          puVar1 = (uint *)(*(int *)(iVar4 + 0x2e) + 2);
          *puVar1 = *puVar1 | 2;
          *(int *)(iVar8 + 0x3e) = iVar4;
          *(int *)(iVar4 + 0x2a) = local_28;
          FUN_005ac9f0(local_28, iVar4);
          *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
          *(int *)(local_28 + 0x3e) = iVar8;
          *(int *)(iVar4 + 0x3e) = local_20;
        }
      }
    }
    bVar10 = local_28 == param_2;
    local_28 = local_20;
    if (bVar10) {
      return;
    }
  } while( true );
}
#undef local_70
#undef local_6c
#undef local_68
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_48
#undef local_40
#undef local_38
#undef local_30
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_13
#undef local_12
#undef local_11


undefined4
fn_005eef80(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, int param_7)

{
  uint *puVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  char *pcVar7;
  undefined8 uVar8;

  iVar2 = FUN_005c4710(param_7);
  pcVar3 = (char *)FUN_005b7d30(*(undefined4 *)(iVar2 + 0x12));
  if (*(char *)(*(int *)(param_7 + 0x24) + 1) == '\x18') {
    pcVar7 = pcVar3;
    if (*pcVar3 == '\f') {
      pcVar7 = (char *)FUN_005b5760();
    }
    uVar8 = FUN_005bfdc0(*(undefined4 *)(param_7 + 0x2c));
    uVar8 = CInt64_Mul(PACK(WORD0(uVar8),WORD1(uVar8)), PACK(param_4,param_5));
    uVar4 = FUN_005ab970(uVar8, (uint)(pcVar7));
    FUN_005ad220(uVar4, param_6);
    uVar5 = FUN_005c4710(param_7);
    uVar5 = FUN_005acf30(uVar5, param_6);
    iVar2 = FUN_005bd630(3);
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar2 + 10) = DAT_00710998;
    *(undefined1 *)(iVar2 + 1) = 0x10;
    *(undefined4 *)(iVar2 + 0x2a) = uVar5;
    *(undefined4 *)(iVar2 + 0x2e) = uVar4;
  }
  else {
    pcVar7 = pcVar3;
    if (*pcVar3 == '\f') {
      pcVar7 = (char *)FUN_005b5760();
    }
    uVar8 = FUN_005bfdc0(*(undefined4 *)(param_7 + 0x2c));
    uVar8 = CInt64_Mul(PACK(WORD0(uVar8),WORD1(uVar8)), PACK(param_2,param_3));
    uVar4 = FUN_005ab970(uVar8, (uint)(pcVar7));
    FUN_005ad220(uVar4, param_6);
    uVar5 = FUN_005c4710(param_7);
    uVar5 = FUN_005acf30(uVar5, param_6);
    iVar2 = FUN_005bd630(3);
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar2 + 10) = DAT_00710998;
    *(undefined1 *)(iVar2 + 1) = 0x10;
    *(undefined4 *)(iVar2 + 0x2a) = uVar5;
    *(undefined4 *)(iVar2 + 0x2e) = uVar4;
  }
  *(char **)(iVar2 + 0x12) = pcVar3;
  FUN_005ad220(iVar2, param_6);
  FUN_00613b50(iVar2);
  uVar4 = create_temp_object(pcVar3);
  FUN_005b53d0(uVar4, 1, 1);
  iVar6 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar6 + 10) = DAT_00710998;
  *(undefined1 *)(iVar6 + 1) = 0x1e;
  uVar4 = FUN_005acdf0(uVar4);
  *(undefined4 *)(iVar6 + 0x2a) = uVar4;
  FUN_005ad220(*(undefined4 *)(*(int *)(iVar6 + 0x2a) + 0x2a), param_6);
  puVar1 = (uint *)(*(int *)(iVar6 + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x26;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar6 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x24;
  *(int *)(iVar6 + 0x2e) = iVar2;
  puVar1 = (uint *)(*(int *)(iVar6 + 0x2e) + 2);
  *puVar1 = *puVar1 | 2;
  *(char **)(iVar6 + 0x12) = pcVar3;
  FUN_005ad220(iVar6, param_6);
  return *(undefined4 *)(iVar6 + 0x2a);
}



undefined4 fn_005ef150(int param_1, int param_2, int param_3, int param_4)

{
  unsigned char nativeFrame[16];
#define local_20 (*(int *)(nativeFrame+0))
#define local_1c (*(undefined4 *)(nativeFrame+4))
#define local_18 (*(undefined4 *)(nativeFrame+8))
#define local_11 (*(bool *)(nativeFrame+15))

  uint *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  bool bVar9;
  undefined8 uVar10;
  iVar3 = FUN_005c4830(param_2, *(undefined4 *)(param_2 + 0x2c));
  iVar4 = FUN_005c4710(param_2);
  local_1c = FUN_005b7d30(*(undefined4 *)(iVar4 + 0x12));
  bVar9 = false;
  if (**(char **)(iVar4 + 0x12) == '\f') {
    bVar9 = **(char **)(iVar3 + 0x12) == '\f';
  }
  if (*(char *)(param_2 + 0x34) == '\0') {
    cVar2 = FUN_005b07f0(iVar3);
    local_11 = cVar2 != '\0';
    if (local_11) {
      uVar10 = CInt64_Neg(PACK(param_3,param_4));
      cVar2 = CInt64_Equal(PACK(*(undefined4 *)(*(int *)(iVar3 + 0x2a) + 0x10),*(undefined4 *)(*(int *)(iVar3 + 0x2a) + 0x14)), PACK(WORD0(uVar10),WORD1(uVar10)));
      local_11 = cVar2 != '\0';
    }
    if ((local_11 == false) &&
       (iVar6 = FUN_005acf30(iVar3, param_1), param_3 != 0 || (iVar3 = iVar6, param_4 != 0))) {
      pcVar8 = *(char **)(iVar6 + 0x12);
      if (*pcVar8 == '\f') {
        pcVar8 = (char *)FUN_005b5760();
      }
      local_18 = FUN_005ab970(PACK(param_3,param_4), (uint)(pcVar8));
      FUN_005ad220(local_18, param_1);
      iVar3 = FUN_005bd630(3);
      DAT_00710998 = DAT_00710998 + 1;
      *(int *)(iVar3 + 10) = DAT_00710998;
      *(undefined1 *)(iVar3 + 1) = 0xf;
      *(int *)(iVar3 + 0x2a) = iVar6;
      *(undefined4 *)(iVar3 + 0x2e) = local_18;
      *(undefined4 *)(iVar3 + 0x12) = *(undefined4 *)(iVar6 + 0x12);
      FUN_005ad220(iVar3, param_1);
    }
    iVar4 = FUN_005acf30(iVar4, param_1);
    if (*(int *)(param_2 + 0x2c) == 0) {
      CError_Internal(s_IroUnrollLoop_c_006b8ea6, 0x821);
    }
    if ((*(int *)(*(int *)(param_2 + 0x2c) + 0x30) == 0) &&
       (*(int *)(*(int *)(param_2 + 0x2c) + 0x34) == 0)) {
      CError_Internal(s_IroUnrollLoop_c_006b8ea6, 0x826);
    }
    if (local_11) {
      iVar6 = iVar4;
      if (bVar9) {
        uVar5 = FUN_005b5770();
        *(undefined4 *)(iVar4 + 0x12) = uVar5;
      }
    }
    else {
      iVar6 = FUN_005bd630(3);
      DAT_00710998 = DAT_00710998 + 1;
      *(int *)(iVar6 + 10) = DAT_00710998;
      *(undefined1 *)(iVar6 + 1) = 0x10;
      *(int *)(iVar6 + 0x2a) = iVar4;
      *(int *)(iVar6 + 0x2e) = iVar3;
      if (bVar9) {
        uVar5 = FUN_005b5770();
        *(undefined4 *)(iVar6 + 0x12) = uVar5;
      }
      else {
        *(undefined4 *)(iVar6 + 0x12) = local_1c;
      }
      FUN_005ad220(iVar6, param_1);
    }
    uVar10 = FUN_005bfdc0(*(undefined4 *)(param_2 + 0x2c));
    uVar5 = FUN_005ab970(uVar10, (uint)(*(undefined4 *)(iVar4 + 0x12)));
    FUN_005ad220(uVar5, param_1);
    iVar3 = FUN_005bd630(3);
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar3 + 10) = DAT_00710998;
    *(undefined1 *)(iVar3 + 1) = 0xf;
    *(int *)(iVar3 + 0x2a) = iVar6;
    *(undefined4 *)(iVar3 + 0x2e) = uVar5;
    uVar5 = FUN_005b7d30(*(undefined4 *)(iVar6 + 0x12));
    *(undefined4 *)(iVar3 + 0x12) = uVar5;
    FUN_005ad220(iVar3, param_1);
    pcVar8 = *(char **)(param_2 + 0x24);
    if ((*pcVar8 == '\x03') && (pcVar8[1] == '\x13')) {
      uVar5 = FUN_005ab970(PACK(DAT_00699b6e,DAT_00699b72), (uint)(*(undefined4 *)(iVar3 + 0x12)));
      FUN_005ad220(uVar5, param_1);
      iVar4 = FUN_005bd630(3);
      DAT_00710998 = DAT_00710998 + 1;
      *(int *)(iVar4 + 10) = DAT_00710998;
      *(undefined1 *)(iVar4 + 1) = 0xf;
      *(int *)(iVar4 + 0x2a) = iVar3;
      *(undefined4 *)(iVar4 + 0x2e) = uVar5;
      uVar5 = FUN_005b7d30(*(undefined4 *)(iVar3 + 0x12));
      *(undefined4 *)(iVar4 + 0x12) = uVar5;
      FUN_005ad220(iVar4, param_1);
    }
    else {
      iVar4 = iVar3;
      if ((*pcVar8 == '\x03') && (pcVar8[1] == '\x14')) {
        uVar5 = FUN_005ab970(PACK(DAT_00699b76,DAT_00699b7a), (uint)(*(undefined4 *)(iVar3 + 0x12)));
        FUN_005ad220(uVar5, param_1);
        iVar4 = FUN_005bd630(3);
        DAT_00710998 = DAT_00710998 + 1;
        *(int *)(iVar4 + 10) = DAT_00710998;
        *(undefined1 *)(iVar4 + 1) = 0xf;
        *(int *)(iVar4 + 0x2a) = iVar3;
        *(undefined4 *)(iVar4 + 0x2e) = uVar5;
        uVar5 = FUN_005b7d30(*(undefined4 *)(iVar3 + 0x12));
        *(undefined4 *)(iVar4 + 0x12) = uVar5;
        FUN_005ad220(iVar4, param_1);
      }
    }
    uVar10 = FUN_005bfdc0(*(undefined4 *)(param_2 + 0x2c));
    iVar3 = FUN_005ab970(uVar10, (uint)(*(undefined4 *)(iVar4 + 0x12)));
    cVar2 = CInt64_Equal(PACK(*(undefined4 *)(*(int *)(iVar3 + 0x2a) + 0x10),*(undefined4 *)(*(int *)(iVar3 + 0x2a) + 0x14)), PACK(DAT_00699b76,DAT_00699b7a))
    ;
    if (cVar2 == '\0') {
      if ((**(char **)(iVar3 + 0x12) == '\x01') && ((byte)(*(char **)(iVar3 + 0x12))[6] < 0x17) &&
         (cVar2 = FUN_005b0850(iVar3, &local_20), cVar2 != '\0') && (local_20 > 0)) {
        iVar7 = FUN_005bd630(3);
        DAT_00710998 = DAT_00710998 + 1;
        *(int *)(iVar7 + 10) = DAT_00710998;
        *(undefined1 *)(iVar7 + 1) = 0x12;
        *(int *)(iVar7 + 0x2a) = iVar4;
        *(int *)(iVar7 + 0x2e) = iVar3;
        iVar6 = *(int *)(iVar3 + 0x2a);
        *(int *)(iVar6 + 0x14) = local_20;
        if (local_20 < 0) {
          uVar5 = 0xffffffff;
        }
        else {
          uVar5 = 0;
        }
        *(undefined4 *)(iVar6 + 0x10) = uVar5;
        *(undefined4 *)(iVar7 + 0x12) = *(undefined4 *)(iVar4 + 0x12);
        FUN_005ad220(iVar3, param_1);
        FUN_005ad220(iVar7, param_1);
        iVar4 = iVar7;
      }
      else {
        iVar6 = FUN_005bd630(3);
        DAT_00710998 = DAT_00710998 + 1;
        *(int *)(iVar6 + 10) = DAT_00710998;
        *(undefined1 *)(iVar6 + 1) = 0xb;
        *(int *)(iVar6 + 0x2a) = iVar4;
        *(int *)(iVar6 + 0x2e) = iVar3;
        *(undefined4 *)(iVar6 + 0x12) = *(undefined4 *)(iVar4 + 0x12);
        FUN_005ad220(iVar3, param_1);
        FUN_005ad220(iVar6, param_1);
        iVar4 = iVar6;
      }
    }
  }
  else {
    cVar2 = CInt64_Equal(PACK(*(undefined4 *)(param_2 + 0x36),*(undefined4 *)(param_2 + 0x3a)), PACK(DAT_00699b6e,DAT_00699b72));
    if (cVar2 == '\0') {
      uVar5 = local_1c;
      if (bVar9) {
        uVar5 = FUN_005b5770();
      }
      iVar4 = FUN_005ab970(PACK(*(undefined4 *)(param_2 + 0x36),*(undefined4 *)(param_2 + 0x3a)), (uint)(uVar5));
      FUN_005ad220(iVar4, param_1);
    }
    else {
      FUN_005acf30(*(undefined4 *)(param_2 + 0x42), param_1);
      iVar4 = *(int *)(param_1 + 4);
    }
  }
  FUN_00613b50(iVar4);
  uVar5 = create_temp_object(*(undefined4 *)(iVar4 + 0x12));
  FUN_005b53d0(uVar5, 1, 1);
  iVar3 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar3 + 10) = DAT_00710998;
  *(undefined1 *)(iVar3 + 1) = 0x1e;
  uVar5 = FUN_005acdf0(uVar5);
  *(undefined4 *)(iVar3 + 0x2a) = uVar5;
  FUN_005ad220(*(undefined4 *)(*(int *)(iVar3 + 0x2a) + 0x2a), param_1);
  puVar1 = (uint *)(*(int *)(iVar3 + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x26;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar3 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x24;
  *(int *)(iVar3 + 0x2e) = iVar4;
  puVar1 = (uint *)(*(int *)(iVar3 + 0x2e) + 2);
  *puVar1 = *puVar1 | 2;
  *(undefined4 *)(iVar3 + 0x12) = *(undefined4 *)(iVar4 + 0x12);
  FUN_005ad220(iVar3, param_1);
  return *(undefined4 *)(iVar3 + 0x2a);
}
#undef local_20
#undef local_1c
#undef local_18
#undef local_11


void fn_005ef6c0(int param_1, int param_2, int *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  char cVar7;
  int iVar8;
  undefined4 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined4 uVar14;

  uVar1 = *(undefined4 *)(param_1 + 0x3a);
  uVar2 = *(undefined4 *)(param_1 + 0x36);
  uVar10 = *(undefined8 *)(param_1 + 0x36);
  if ((*(char *)(param_1 + 0x34) != '\0') &&
     (cVar7 = CInt64_Equal(PACK(uVar2,uVar1), PACK(DAT_00699b6e,DAT_00699b72)), cVar7 == '\0')) {
    iVar8 = FUN_005c4710(param_1);
    uVar9 = FUN_005b7d30(*(undefined4 *)(iVar8 + 0x12));
    cVar7 = FUN_00454260(uVar9);
    if (param_2 == 0) {
      CError_Internal(s_IroUnrollLoop_c_006b8ea6, 0x748);
    }
    if (param_2 < 0) {
      uVar9 = 0xffffffff;
    }
    else {
      uVar9 = 0;
    }
    uVar14 = uVar9;
    iVar8 = param_2;
    if (cVar7 == '\0') {
      cVar7 = CInt64_Less(PACK(uVar2,uVar1), PACK(uVar9,param_2));
    }
    else {
      cVar7 = CInt64_LessU(PACK(uVar2,uVar1), PACK(uVar9,param_2));
    }
    uVar5 = CONCAT44(DAT_0070490c, DAT_00704908);
    if (cVar7 == '\0') {
      if(param_2==1) {} else if(param_2==2) {uVar10 = CInt64_ShrU(PACK(uVar2,uVar1), PACK(DAT_00699b76,DAT_00699b7a));} else if(param_2==4) {uVar10 = CInt64_ShrU(PACK(uVar2,uVar1), PACK(0,2));} else if(param_2==8) {uVar10 = CInt64_ShrU(PACK(uVar2,uVar1), PACK(0,3));} else if(param_2==0x10) {uVar10 = CInt64_ShrU(PACK(uVar2,uVar1), PACK(0,4));} else {uVar10 = FUN_004d9c50(PACK(uVar2,uVar1), PACK(uVar9,param_2));}
      cVar7 = CInt64_LessU(PACK(WORD0(uVar10),WORD1(uVar10)), PACK(*param_3,param_3[1]));
      if (cVar7 != '\0') {
        *(undefined8 *)param_3 = uVar10;
      }
      iVar3 = param_3[1];
      iVar4 = *param_3;
      uVar13 = *(undefined8 *)param_3;
      if(param_2==1) {uVar11 = CONCAT44(DAT_0070490c, DAT_00704908);} else if(param_2==2) {uVar11 = CInt64_And(PACK(uVar2,uVar1), PACK(DAT_00699b76,DAT_00699b7a));} else if(param_2==4) {uVar11 = CInt64_And(PACK(uVar2,uVar1), PACK(0,3));} else if(param_2==8) {uVar11 = CInt64_And(PACK(uVar2,uVar1), PACK(0,7));} else if(param_2==0x10) {uVar11 = CInt64_And(PACK(uVar2,uVar1), PACK(0,0xf));} else {uVar11 = FUN_004d9aa0(PACK(uVar2,uVar1), PACK(uVar9,param_2));}
      cVar7 = CInt64_LessEqualU(PACK(WORD0(uVar10),WORD1(uVar10)), PACK(0,(int)DAT_0070f243));
      uVar5 = uVar10;
      if (cVar7 == '\0') {
        if ((iVar4 == 0) && (iVar3 == 0)) {
          uVar6 = CONCAT44(DAT_0070490c, DAT_00704908);
        }
        else {
          uVar6 = 0x7fffffff00000000;
          uVar5 = 0x7fffffff00000000;
          do {
            uVar12 = FUN_004d9aa0(PACK(WORD0(uVar10),WORD1(uVar10)), PACK(WORD0(uVar13),WORD1(uVar13)));
            uVar12 = CInt64_Mul(PACK(WORD0(uVar12),WORD1(uVar12)), PACK(uVar14,iVar8));
            uVar12 = CInt64_Add(PACK(WORD0(uVar12),WORD1(uVar12)), PACK(WORD0(uVar11),WORD1(uVar11)));
            cVar7 = CInt64_Less(PACK(WORD0(uVar12),WORD1(uVar12)), PACK(WORD0(uVar5),WORD1(uVar5)));
            if (cVar7 != '\0') {
              uVar5 = uVar12;
              uVar6 = uVar13;
            }
            if (((DAT_0070f251 == '\0') && (param_2 == 1)) ||
               (DAT_0070f252 == '\0' && (param_2 > 1))) break;
            uVar13 = CInt64_Add(PACK(WORD0(uVar13),WORD1(uVar13)), PACK(DAT_00699b6e,DAT_00699b72));
            uVar12 = CInt64_Mul(PACK(WORD0(uVar13),WORD1(uVar13)), PACK(WORD0(uVar13),WORD1(uVar13)));
            cVar7 = CInt64_GreaterEqualU(PACK(WORD0(uVar12),WORD1(uVar12)), PACK(WORD0(uVar10),WORD1(uVar10)));
          } while (cVar7 != '\0');
        }
        *(undefined8 *)param_3 = uVar6;
        goto LAB_005efa8b;
      }
    }
    *(undefined8 *)param_3 = uVar5;
  }
LAB_005efa8b:
  FUN_005ed4c0(s______IterCount____d__VectorStrid_006b903a, uVar1, param_2, param_3[1]);
  return;
}



void fn_005efc20(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)

{
  unsigned char nativeFrame[76];
#define local_5c (*(int *)(nativeFrame+0))
#define local_58 (*(int *)(nativeFrame+4))
#define local_54 (*(undefined4 *)(nativeFrame+8))
#define local_50 (*(undefined4 *)(nativeFrame+12))
#define local_4c (*(undefined4 *)(nativeFrame+16))
#define local_48 (*(int *)(nativeFrame+20))
#define local_44 (*(int *)(nativeFrame+24))
#define local_40 (*(undefined4 *)(nativeFrame+28))
#define local_3c (*(int *)(nativeFrame+32))
#define local_38 (*(int *)(nativeFrame+36))
#define local_34 (*(int *)(nativeFrame+40))
#define local_30 (*(int *)(nativeFrame+44))
#define local_2c (*(int *)(nativeFrame+48))
#define local_28 (*(undefined4 *)(nativeFrame+52))
#define local_24 (*(int *)(nativeFrame+56))
#define local_20 (*(int *)(nativeFrame+60))
#define local_1c (*(undefined1 * *)(nativeFrame+64))
#define local_18 (*(undefined1 * *)(nativeFrame+68))
#define local_14 (*(int *)(nativeFrame+72))

  byte *pbVar1;
  uint *puVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  undefined8 uVar10;
  FUN_005ed4c0(s_while_n____loop_006b9076);
  local_20 = *(int *)(param_1 + 0x1c);
  local_24 = *(int *)(param_1 + 0x2c);
  local_1c = *(undefined1 **)(*(int *)(local_20 + 0x14) + 0x2a);
  iVar4 = FUN_005aeed0(local_1c, *(int *)(local_20 + 0x14));
  FUN_005ad280(&local_5c);
  FUN_005ad1e0(*(undefined4 *)(iVar4 + 0x3e), *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x2a),
               &local_5c);
  FUN_005acf30(*(undefined4 *)(param_1 + 0x24), &local_5c);
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  iVar4 = local_58;
  FUN_005ad280(&local_5c);
  pcVar3 = *(char **)(*(int *)(param_1 + 0x10) + 0x14);
  local_18 = (undefined1 *)FUN_005bd630(0);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(local_18 + 10) = DAT_00710998;
  if (*pcVar3 == '\n') {
    *local_18 = 0xb;
  }
  else {
    *local_18 = 10;
  }
  FUN_005ad220(local_18, &local_5c);
  local_2c = FUN_005a9cc0();
  *(int *)(local_18 + 0x2a) = local_2c;
  *(int *)(local_18 + 0x2e) = iVar4;
  *(uint *)(*(int *)(local_18 + 0x2e) + 2) = *(uint *)(*(int *)(local_18 + 0x2e) + 2) | 2;
  uVar5 = FUN_005b7d30(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x12));
  *(undefined4 *)(local_18 + 0x12) = uVar5;
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  FUN_005ad280(&local_5c);
  uVar5 = fn_005f0f10((uint)(&local_5c), (int)(param_1));
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  local_48 = local_5c;
  FUN_005ad280(&local_5c);
  local_34 = fn_005f0d50((int)(local_24), (uint)(param_2), (uint)(param_3), (int)(&local_5c));
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  FUN_005ad280(&local_5c);
  local_30 = fn_005f0b60((int)(uVar5), (uint)(param_2), (uint)(param_3), (int)(&local_5c), (int)(param_1));
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  FUN_005ad280(&local_5c);
  local_4c = fn_005f09e0((int)(uVar5), (uint)(param_2), (uint)(param_3), (int)(&local_5c), (int)(param_1));
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  FUN_005ad280(&local_5c);
  fn_005ed810((int)(param_1), (int)(&local_5c), (int)(uVar5), (uint)(param_2), (uint)(param_3), (uint)(local_1c));
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  local_44 = local_58;
  FUN_005ad280(&local_5c);
  uVar5 = FUN_005aef20();
  FUN_005ad220(uVar5, &local_5c);
  local_28 = *(undefined4 *)(local_58 + 0x2a);
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  local_3c = local_5c;
  iVar9 = 0;
  for (iVar4 = *(int *)(param_1 + 0x20); iVar4 != 0 && (iVar4 != *(int *)(param_1 + 0x10));
      iVar4 = *(int *)(iVar4 + 0x30)) {
    FUN_005ad280(&local_5c);
    pcVar3 = *(char **)(iVar4 + 0x14);
    pcVar8 = *(char **)(iVar4 + 0x10);
    while( true ) {
      if (*(int *)(pcVar8 + 0xe) != 0) {
        pbVar1 = (byte *)(*(int *)(pcVar8 + 0xe) + 6);
        *pbVar1 = *pbVar1 | 0x10;
      }
      if ((*pcVar8 != '\r') && ((*(uint *)(pcVar8 + 2) & 2) == 0)) {
        FUN_005acf30(pcVar8, &local_5c);
        if (iVar9 == 0) {
          iVar9 = local_5c;
        }
      }
      if (pcVar8 == pcVar3) break;
      pcVar8 = *(char **)(pcVar8 + 0x3e);
    }
    if ((local_5c != 0) && (local_58 != 0)) {
      FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
    }
  }
  FUN_005ad280(&local_5c);
  FUN_005acf30(*(undefined4 *)(*(int *)(local_24 + 10) + 0x2a), &local_5c);
  iVar4 = local_58;
  *(uint *)(local_58 + 2) = *(uint *)(local_58 + 2) & 0xfffffffb;
  FUN_005acf30(local_34, &local_5c);
  *(uint *)(local_58 + 2) = *(uint *)(local_58 + 2) & 0xfffffffb;
  iVar9 = FUN_005bd630(3);
  *(undefined1 *)(iVar9 + 1) = 0x13;
  uVar5 = FUN_005b7af0();
  *(undefined4 *)(iVar9 + 0x12) = uVar5;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar9 + 10) = DAT_00710998;
  *(undefined4 *)(iVar9 + 0x3e) = 0;
  *(int *)(iVar9 + 0x2a) = iVar4;
  *(int *)(iVar9 + 0x2e) = local_58;
  FUN_005ad220(iVar9, &local_5c);
  *(uint *)(iVar9 + 2) = *(uint *)(iVar9 + 2) | 2;
  iVar4 = FUN_005bd630(**(undefined1 **)(*(int *)(param_1 + 0x10) + 0x14));
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  FUN_005ad220(iVar4, &local_5c);
  *(undefined4 *)(iVar4 + 0x2a) = local_28;
  *(int *)(iVar4 + 0x2e) = iVar9;
  puVar2 = (uint *)(*(int *)(iVar4 + 0x2e) + 2);
  *puVar2 = *puVar2 | 2;
  *(undefined4 *)(iVar4 + 0x12) = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x12);
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  local_14 = local_58;
  FUN_005ad280(&local_5c);
  uVar5 = FUN_005a9cc0();
  local_1c = (undefined1 *)FUN_005bd630(2);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(local_1c + 10) = DAT_00710998;
  *local_1c = 8;
  *(undefined4 *)(local_1c + 0x2a) = uVar5;
  FUN_005ad220(local_1c, &local_5c);
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  FUN_005ad280(&local_5c);
  uVar6 = FUN_005aef20();
  FUN_005ad220(uVar6, &local_5c);
  local_28 = *(undefined4 *)(local_58 + 0x2a);
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  local_38 = local_5c;
  fn_005f0590((int)(param_1), (int *)(param_4));
  local_50 = 8;
  local_54 = 0;
  uVar10 = CInt64_Mul(PACK(param_2,param_3), PACK(0,8));
  local_40 = fn_005ed720((int)(param_1), NativeWords(WORD0(uVar10),WORD1(uVar10)), (uint)(*(undefined4 *)(local_20 + 0x14)));
  FUN_005ad280(&local_5c);
  local_34 = FUN_005bd630(0xd);
  *(int *)(local_34 + 10) = DAT_00710998;
  DAT_00710998 = DAT_00710998 + 1;
  *(undefined4 *)(local_34 + 0x2a) = uVar5;
  *(uint *)(local_34 + 2) = *(uint *)(local_34 + 2) | 1;
  FUN_005ad220(local_34, &local_5c);
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  FUN_005ad280(&local_5c);
  FUN_005acf30(*(undefined4 *)(*(int *)(local_24 + 10) + 0x2a), &local_5c);
  iVar4 = local_58;
  *(uint *)(local_58 + 2) = *(uint *)(local_58 + 2) & 0xfffffffb;
  FUN_005acf30(local_30, &local_5c);
  *(uint *)(local_58 + 2) = *(uint *)(local_58 + 2) & 0xfffffffb;
  iVar9 = FUN_005bd630(3);
  *(undefined1 *)(iVar9 + 1) = 0x13;
  uVar5 = FUN_005b7af0();
  *(undefined4 *)(iVar9 + 0x12) = uVar5;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar9 + 10) = DAT_00710998;
  *(undefined4 *)(iVar9 + 0x3e) = 0;
  *(int *)(iVar9 + 0x2a) = iVar4;
  *(int *)(iVar9 + 0x2e) = local_58;
  FUN_005ad220(iVar9, &local_5c);
  *(uint *)(iVar9 + 2) = *(uint *)(iVar9 + 2) | 2;
  iVar4 = FUN_005bd630(**(undefined1 **)(*(int *)(param_1 + 0x10) + 0x14));
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  FUN_005ad220(iVar4, &local_5c);
  *(undefined4 *)(iVar4 + 0x2a) = local_28;
  *(int *)(iVar4 + 0x2e) = iVar9;
  puVar2 = (uint *)(*(int *)(iVar4 + 0x2e) + 2);
  *puVar2 = *puVar2 | 2;
  *(undefined4 *)(iVar4 + 0x12) = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x12);
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(local_20 + 0x14));
  local_30 = local_58;
  local_28 = *(undefined4 *)(local_20 + 0x14);
  FUN_005ad280(&local_5c);
  FUN_005acf30(*(undefined4 *)(*(int *)(local_24 + 10) + 0x2a), &local_5c);
  iVar4 = local_58;
  *(uint *)(local_58 + 2) = *(uint *)(local_58 + 2) & 0xfffffffb;
  FUN_005acf30(local_4c, &local_5c);
  *(uint *)(local_58 + 2) = *(uint *)(local_58 + 2) & 0xfffffffb;
  iVar9 = FUN_005bd630(3);
  *(undefined1 *)(iVar9 + 1) = 0x13;
  uVar5 = FUN_005b7af0();
  *(undefined4 *)(iVar9 + 0x12) = uVar5;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar9 + 10) = DAT_00710998;
  *(undefined4 *)(iVar9 + 0x3e) = 0;
  *(int *)(iVar9 + 0x2a) = iVar4;
  *(int *)(iVar9 + 0x2e) = local_58;
  FUN_005ad220(iVar9, &local_5c);
  *(uint *)(iVar9 + 2) = *(uint *)(iVar9 + 2) | 2;
  iVar4 = *(int *)(param_1 + 0x24);
  FUN_005ad440(local_5c, local_58, *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x14));
  *(int *)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x2e) = local_58;
  *(int *)(param_1 + 0x24) = local_58;
  FUN_005ad280(&local_5c);
  local_24 = FUN_005ab970(PACK(DAT_00704908,DAT_0070490c), (uint)(*(undefined4 *)(*(int *)(iVar4 + 0x2a) + 0x12)));
  FUN_005ad220(local_24, &local_5c);
  *(uint *)(local_24 + 2) = *(uint *)(local_24 + 2) | 2;
  FUN_005acf30(*(undefined4 *)(iVar4 + 0x2a), &local_5c);
  iVar9 = FUN_005bd630(3);
  *(undefined1 *)(iVar9 + 1) = 0x1e;
  *(undefined4 *)(iVar9 + 0x12) = *(undefined4 *)(local_58 + 0x12);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar9 + 10) = DAT_00710998;
  *(undefined4 *)(iVar9 + 0x3e) = 0;
  *(int *)(iVar9 + 0x2a) = local_58;
  *(int *)(iVar9 + 0x2e) = local_24;
  FUN_005ad220(iVar9, &local_5c);
  *(uint *)(iVar9 + 2) = *(uint *)(iVar9 + 2) | 4;
  FUN_005ae7b0(iVar4);
  uVar5 = *(undefined4 *)(local_20 + 0x30);
  *(undefined1 **)(local_20 + 0x14) = local_18;
  iVar4 = FUN_005be150();
  *(int *)(local_20 + 0x30) = iVar4;
  *(int *)(iVar4 + 0x10) = local_48;
  *(int *)(iVar4 + 0x14) = local_44;
  iVar9 = FUN_005be150();
  *(int *)(iVar9 + 0x10) = local_3c;
  *(int *)(iVar9 + 0x14) = local_14;
  *(int *)(*(int *)(local_3c + 0x2a) + 4) = iVar9;
  *(int *)(iVar4 + 0x30) = iVar9;
  iVar4 = FUN_005be150();
  *(undefined1 **)(iVar4 + 0x10) = local_1c;
  *(undefined1 **)(iVar4 + 0x14) = local_1c;
  *(int *)(iVar9 + 0x30) = iVar4;
  iVar9 = FUN_005be150();
  *(int *)(iVar9 + 0x10) = local_38;
  *(undefined4 *)(iVar9 + 0x14) = local_40;
  *(int *)(*(int *)(local_38 + 0x2a) + 4) = iVar9;
  *(int *)(iVar4 + 0x30) = iVar9;
  iVar4 = FUN_005be150();
  *(int *)(iVar4 + 0x10) = local_34;
  *(int *)(iVar4 + 0x14) = local_30;
  *(int *)(*(int *)(local_34 + 0x2a) + 4) = iVar4;
  *(int *)(iVar9 + 0x30) = iVar4;
  iVar9 = FUN_005be150();
  *(undefined4 *)(iVar9 + 0x10) = local_28;
  *(undefined4 *)(iVar9 + 0x14) = local_28;
  *(int *)(iVar4 + 0x30) = iVar9;
  *(undefined4 *)(iVar9 + 0x30) = uVar5;
  iVar4 = FUN_005be150();
  *(int *)(iVar4 + 0x10) = local_5c;
  *(int *)(iVar4 + 0x14) = local_58;
  *(undefined4 *)(local_58 + 0x3e) =
       *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x3e);
  *(int *)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x3e) = local_5c;
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x30);
  *(int *)(*(int *)(param_1 + 0x10) + 0x30) = iVar4;
  iVar9 = FUN_005be150();
  iVar7 = FUN_005bd630(0xd);
  *(int *)(iVar7 + 10) = DAT_00710998;
  DAT_00710998 = DAT_00710998 + 1;
  *(undefined4 *)(iVar7 + 0x3e) = 0;
  *(int *)(iVar7 + 0x2a) = local_2c;
  *(uint *)(iVar7 + 2) = *(uint *)(iVar7 + 2) | 1;
  *(int *)(local_2c + 4) = iVar9;
  *(int *)(iVar9 + 0x10) = iVar7;
  *(int *)(iVar9 + 0x14) = iVar7;
  *(undefined4 *)(iVar7 + 0x3e) = *(undefined4 *)(*(int *)(iVar4 + 0x14) + 0x3e);
  *(int *)(*(int *)(iVar4 + 0x14) + 0x3e) = iVar7;
  *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar4 + 0x30);
  *(int *)(iVar4 + 0x30) = iVar9;
  return;
}
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14


void fn_005f0590(int param_1, int *param_2)

{
  unsigned char nativeFrame[64];
#define local_50 (*(int *)(nativeFrame+0))
#define iStack_4c (*(int *)(nativeFrame+4))
#define uStack_48 (*(undefined4 *)(nativeFrame+8))
#define iStack_44 (*(int *)(nativeFrame+12))
#define uStack_40 (*(undefined4 *)(nativeFrame+16))
#define iStack_3c (*(int *)(nativeFrame+20))
#define uStack_38 (*(undefined8 *)(nativeFrame+24))
#define uStack_30 (*(undefined4 *)(nativeFrame+32))
#define uStack_2c (*(undefined4 *)(nativeFrame+36))
#define local_28 (*(int *)(nativeFrame+40))
#define iStack_24 (*(int *)(nativeFrame+44))
#define local_20 (*(int *)(nativeFrame+48))
#define local_1c (*(char * *)(nativeFrame+52))
#define local_18 (*(int *)(nativeFrame+56))
#define local_14 (*(int *)(nativeFrame+60))

  byte *pbVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined8 uVar10;
  local_20 = 0;
  do {
    local_28 = 0;
    local_14 = local_20;
    iVar5 = local_20;
    local_18 = *(int *)(param_1 + 0x20);
LAB_005f05c0:
    if ((local_18 != 0) && (iVar5 = param_1, local_18 != *(int *)(param_1 + 0x10))) {
      FUN_005ad280(&local_50);
      local_1c = *(char **)(local_18 + 0x14);
      pcVar9 = *(char **)(local_18 + 0x10);
      do {
        if (*(int *)(pcVar9 + 0xe) != 0) {
          pbVar1 = (byte *)(*(int *)(pcVar9 + 0xe) + 6);
          *pbVar1 = *pbVar1 | 0x10;
        }
        cVar3 = FUN_005c4550(param_1, pcVar9);
        if ((cVar3 == '\0') && (*pcVar9 != '\r') && (*pcVar9 != '\0') &&
           ((*(uint *)(pcVar9 + 2) & 2) == 0)) {
          cVar3 = pcVar9[1];
          if ((cVar3 != '(') && (cVar3 != '&') && (cVar3 != '\'')) {
            CError_Internal(s_IroUnrollLoop_c_006b8ea6, 0x4c8);
          }
          FUN_005acf30(*param_2, &local_50);
          iStack_24 = iStack_4c;
          uStack_30 = DAT_00699b76;
          uStack_2c = DAT_00699b7a;
          uVar10 = CInt64_Shl(PACK(DAT_00699b76,DAT_00699b7a), PACK(param_2[7],param_2[8]));
          iStack_44 = local_14;
          uStack_48 = 0;
          uStack_38 = uVar10;
          uVar10 = CInt64_Mul(PACK(0,local_14), PACK(WORD0(uVar10),WORD1(uVar10)));
          uVar4 = FUN_005ab970(uVar10, (uint)(*(undefined4 *)(*param_2 + 0x12)));
          FUN_005ad220(uVar4, &local_50);
          FUN_005acf30(param_2[1], &local_50);
          iVar5 = FUN_005bd630(3);
          DAT_00710998 = DAT_00710998 + 1;
          *(int *)(iVar5 + 10) = DAT_00710998;
          *(undefined1 *)(iVar5 + 1) = 0xf;
          uVar6 = FUN_005b7d30(param_2[2]);
          *(undefined4 *)(iVar5 + 0x12) = uVar6;
          *(int *)(iVar5 + 0x2a) = iStack_4c;
          *(undefined4 *)(iVar5 + 0x2e) = uVar4;
          FUN_005ad220(iVar5, &local_50);
          iVar7 = FUN_005bd630(3);
          DAT_00710998 = DAT_00710998 + 1;
          *(int *)(iVar7 + 10) = DAT_00710998;
          *(undefined1 *)(iVar7 + 1) = 0xf;
          uVar4 = FUN_005b7d30(param_2[2]);
          *(undefined4 *)(iVar7 + 0x12) = uVar4;
          *(int *)(iVar7 + 0x2a) = iVar5;
          *(int *)(iVar7 + 0x2e) = iStack_24;
          FUN_005ad220(iVar7, &local_50);
          iVar5 = FUN_005bd630(2);
          DAT_00710998 = DAT_00710998 + 1;
          *(int *)(iVar5 + 10) = DAT_00710998;
          *(undefined1 *)(iVar5 + 1) = 4;
          uVar4 = FUN_005b7d30(*(undefined4 *)(pcVar9 + 0x12));
          *(undefined4 *)(iVar5 + 0x12) = uVar4;
          *(int *)(iVar5 + 0x2a) = iVar7;
          FUN_005ad220(iVar5, &local_50);
          iVar5 = FUN_005bd630(3);
          iVar7 = 0;
          do {
            *(undefined4 *)(iVar7 + iVar5) = *(undefined4 *)(pcVar9 + iVar7);
            *(undefined4 *)(iVar7 + 4 + iVar5) = *(undefined4 *)(pcVar9 + iVar7 + 4);
            *(undefined4 *)(iVar7 + 8 + iVar5) = *(undefined4 *)(pcVar9 + iVar7 + 8);
            *(undefined4 *)(iVar7 + 0xc + iVar5) = *(undefined4 *)(pcVar9 + iVar7 + 0xc);
            iVar7 = iVar7 + 0x10;
          } while (iVar7 < 0x40);
          *(undefined2 *)(iVar5 + 0x40) = *(undefined2 *)(pcVar9 + 0x40);
          DAT_00710998 = DAT_00710998 + 1;
          *(int *)(iVar5 + 10) = DAT_00710998;
          *(int *)(iVar5 + 0x2a) = iStack_4c;
          *(undefined4 *)(iVar5 + 0x3e) = 0;
          iStack_24 = FUN_005ab970(PACK(param_2[5],param_2[6]), (uint)(*(undefined4 *)(param_2[3] + 0x12)));
          if ((*pcVar9 == '\x03') && (pcVar9[1] == '&')) {
            cVar3 = CInt64_Equal(PACK(param_2[5],param_2[6]), PACK(DAT_00704908,DAT_0070490c));
            if (cVar3 == '\0') goto LAB_005f068c;
LAB_005f06e2:
            *(undefined1 *)(iVar5 + 1) = 0x1e;
          }
          else {
LAB_005f068c:
            if ((*pcVar9 == '\x03') && (pcVar9[1] == '(')) {
              iStack_3c = param_2[6];
              uStack_40 = 0;
              cVar3 = CInt64_Equal(PACK(param_2[5],param_2[6]), PACK(0,iStack_3c));
              if (cVar3 != '\0') {
                iVar7 = *(int *)(*(int *)(pcVar9 + 0x12) + 2);
                iVar2 = param_2[6];
                if (((iVar7 == 1) && (iVar2 == 0xff)) || (iVar7 == 2 && (iVar2 == 0xffff)) ||
                   (iVar7 == 4 && (iVar2 == -1))) goto LAB_005f06e2;
              }
            }
          }
          FUN_005ad220(iStack_24, &local_50);
          iVar7 = iStack_24;
          if ((*(char *)param_2[4] == '\x02') && (((char *)param_2[4])[1] == '2')) {
            iVar7 = FUN_005bd630(2);
            iVar2 = param_2[4];
            iVar8 = 0;
            do {
              *(undefined4 *)(iVar8 + iVar7) = *(undefined4 *)(iVar8 + iVar2);
              *(undefined4 *)(iVar8 + 4 + iVar7) = *(undefined4 *)(iVar8 + 4 + iVar2);
              *(undefined4 *)(iVar8 + 8 + iVar7) = *(undefined4 *)(iVar8 + 8 + iVar2);
              *(undefined4 *)(iVar8 + 0xc + iVar7) = *(undefined4 *)(iVar8 + 0xc + iVar2);
              iVar8 = iVar8 + 0x10;
            } while (iVar8 < 0x40);
            *(undefined2 *)(iVar7 + 0x40) = *(undefined2 *)(iVar2 + 0x40);
            DAT_00710998 = DAT_00710998 + 1;
            *(int *)(iVar7 + 10) = DAT_00710998;
            *(int *)(iVar7 + 0x2a) = iStack_24;
            *(undefined4 *)(iVar7 + 0x3e) = 0;
            FUN_005ad220(iVar7, &local_50);
          }
          *(int *)(iVar5 + 0x2e) = iVar7;
          FUN_005ad220(iVar5, &local_50);
          if (local_28 == 0) {
            local_28 = local_50;
          }
        }
        if (pcVar9 == local_1c) goto LAB_005f0990;
        pcVar9 = *(char **)(pcVar9 + 0x3e);
      } while( true );
    }
    local_20 = local_20 + 1;
    if (local_20 > 7) {
      return;
    }
  } while( true );
LAB_005f0990:
  if ((local_50 != 0) && (iStack_4c != 0)) {
    FUN_005ad440(local_50, iStack_4c, *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x14));
  }
  iVar5 = local_18;
  local_18 = *(int *)(local_18 + 0x30);
  goto LAB_005f05c0;
}
#undef local_50
#undef iStack_4c
#undef uStack_48
#undef iStack_44
#undef uStack_40
#undef iStack_3c
#undef uStack_38
#undef uStack_30
#undef uStack_2c
#undef local_28
#undef iStack_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14


undefined4
fn_005f09e0(int param_1, undefined4 param_2, undefined4 param_3, int param_4, int param_5)

{
  uint *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;

  uVar2 = FUN_005b7d30(*(undefined4 *)(param_1 + 0x12));
  iVar3 = FUN_005ab970(PACK(*(undefined4 *)(*(int *)(param_5 + 0x2c) + 0x30),*(undefined4 *)(*(int *)(param_5 + 0x2c) + 0x34)), (uint)(uVar2));
  FUN_005ad220(iVar3, param_4);
  *(uint *)(iVar3 + 2) = *(uint *)(iVar3 + 2) | 2;
  iVar4 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(undefined1 *)(iVar4 + 1) = 9;
  uVar5 = FUN_005acf30(param_1, param_4);
  *(undefined4 *)(iVar4 + 0x2a) = uVar5;
  *(int *)(iVar4 + 0x2e) = iVar3;
  *(undefined4 *)(iVar4 + 0x12) = uVar2;
  FUN_005ad220(iVar4, param_4);
  *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar4 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  FUN_005acf30(*(undefined4 *)(*(int *)(*(int *)(param_5 + 0x2c) + 10) + 0x2a), param_4);
  puVar1 = (uint *)(*(int *)(param_4 + 4) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  puVar1 = (uint *)(*(int *)(*(int *)(param_4 + 4) + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  iVar3 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar3 + 10) = DAT_00710998;
  *(undefined1 *)(iVar3 + 1) = 0xf;
  *(int *)(iVar3 + 0x2a) = iVar4;
  *(undefined4 *)(iVar3 + 0x2e) = *(undefined4 *)(param_4 + 4);
  *(undefined4 *)(iVar3 + 0x12) = uVar2;
  FUN_005ad220(iVar3, param_4);
  *(uint *)(iVar3 + 2) = *(uint *)(iVar3 + 2) | 2;
  uVar5 = create_temp_object(uVar2);
  FUN_005b53d0(uVar5, 1, 1);
  iVar4 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(undefined1 *)(iVar4 + 1) = 0x1e;
  uVar5 = FUN_005acdf0(uVar5);
  *(undefined4 *)(iVar4 + 0x2a) = uVar5;
  FUN_005ad220(*(undefined4 *)(*(int *)(iVar4 + 0x2a) + 0x2a), param_4);
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x26;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar4 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x24;
  *(int *)(iVar4 + 0x2e) = iVar3;
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2e) + 2);
  *puVar1 = *puVar1 | 2;
  *(undefined4 *)(iVar4 + 0x12) = uVar2;
  FUN_005ad220(iVar4, param_4);
  return *(undefined4 *)(iVar4 + 0x2a);
}



undefined4
fn_005f0b60(int param_1, undefined4 param_2, undefined4 param_3, int param_4, int param_5)

{
  uint *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 uVar7;

  uVar2 = FUN_005b7d30(*(undefined4 *)(param_1 + 0x12));
  uVar7 = CInt64_Mul(PACK(*(undefined4 *)(*(int *)(param_5 + 0x2c) + 0x30),*(undefined4 *)(*(int *)(param_5 + 0x2c) + 0x34)), PACK(param_2,param_3));
  iVar3 = FUN_005ab970(uVar7, (uint)(uVar2));
  FUN_005ad220(iVar3, param_4);
  *(uint *)(iVar3 + 2) = *(uint *)(iVar3 + 2) | 2;
  iVar4 = FUN_005ab970(PACK(*(undefined4 *)(*(int *)(param_5 + 0x2c) + 0x30),*(undefined4 *)(*(int *)(param_5 + 0x2c) + 0x34)), (uint)(uVar2));
  FUN_005ad220(iVar4, param_4);
  *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
  iVar5 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar5 + 10) = DAT_00710998;
  *(undefined1 *)(iVar5 + 1) = 9;
  uVar6 = FUN_005acf30(param_1, param_4);
  *(undefined4 *)(iVar5 + 0x2a) = uVar6;
  *(int *)(iVar5 + 0x2e) = iVar4;
  *(undefined4 *)(iVar5 + 0x12) = uVar2;
  FUN_005ad220(iVar5, param_4);
  *(uint *)(iVar5 + 2) = *(uint *)(iVar5 + 2) | 2;
  puVar1 = (uint *)(*(int *)(iVar5 + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar5 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  iVar4 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(undefined1 *)(iVar4 + 1) = 0x10;
  *(int *)(iVar4 + 0x2a) = iVar5;
  *(int *)(iVar4 + 0x2e) = iVar3;
  *(undefined4 *)(iVar4 + 0x12) = uVar2;
  FUN_005ad220(iVar4, param_4);
  *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
  FUN_005acf30(*(undefined4 *)(*(int *)(*(int *)(param_5 + 0x2c) + 10) + 0x2a), param_4);
  puVar1 = (uint *)(*(int *)(param_4 + 4) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  puVar1 = (uint *)(*(int *)(*(int *)(param_4 + 4) + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  iVar3 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar3 + 10) = DAT_00710998;
  *(undefined1 *)(iVar3 + 1) = 0xf;
  *(int *)(iVar3 + 0x2a) = iVar4;
  *(undefined4 *)(iVar3 + 0x2e) = *(undefined4 *)(param_4 + 4);
  *(undefined4 *)(iVar3 + 0x12) = uVar2;
  FUN_005ad220(iVar3, param_4);
  *(uint *)(iVar3 + 2) = *(uint *)(iVar3 + 2) | 2;
  uVar6 = create_temp_object(uVar2);
  FUN_005b53d0(uVar6, 1, 1);
  iVar4 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(undefined1 *)(iVar4 + 1) = 0x1e;
  uVar6 = FUN_005acdf0(uVar6);
  *(undefined4 *)(iVar4 + 0x2a) = uVar6;
  FUN_005ad220(*(undefined4 *)(*(int *)(iVar4 + 0x2a) + 0x2a), param_4);
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x26;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar4 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x24;
  *(int *)(iVar4 + 0x2e) = iVar3;
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2e) + 2);
  *puVar1 = *puVar1 | 2;
  *(undefined4 *)(iVar4 + 0x12) = uVar2;
  FUN_005ad220(iVar4, param_4);
  return *(undefined4 *)(iVar4 + 0x2a);
}



undefined4 fn_005f0d50(int param_1, undefined4 param_2, undefined4 param_3, int param_4)

{
  uint *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  iVar4 = *(int *)(param_1 + 10);
  uVar2 = FUN_005b7d30(*(undefined4 *)(iVar4 + 0x12));
  uVar3 = FUN_005ab970(PACK(param_2,param_3), (uint)(uVar2));
  FUN_005ad220(uVar3, param_4);
  FUN_005acf30(*(undefined4 *)(iVar4 + 0x2a), param_4);
  puVar1 = (uint *)(*(int *)(param_4 + 4) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  puVar1 = (uint *)(*(int *)(*(int *)(param_4 + 4) + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  iVar4 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(undefined1 *)(iVar4 + 1) = 0xb;
  *(undefined4 *)(iVar4 + 0x2a) = *(undefined4 *)(param_4 + 4);
  *(undefined4 *)(iVar4 + 0x2e) = uVar3;
  *(undefined4 *)(iVar4 + 0x12) = uVar2;
  FUN_005ad220(iVar4, param_4);
  *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
  iVar5 = FUN_005ab970(PACK(DAT_00699b76,DAT_00699b7a), (uint)(uVar2));
  FUN_005ad220(iVar5, param_4);
  *(uint *)(iVar5 + 2) = *(uint *)(iVar5 + 2) | 2;
  iVar6 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar6 + 10) = DAT_00710998;
  *(undefined1 *)(iVar6 + 1) = 0xf;
  *(int *)(iVar6 + 0x2a) = iVar4;
  *(int *)(iVar6 + 0x2e) = iVar5;
  *(undefined4 *)(iVar6 + 0x12) = uVar2;
  FUN_005ad220(iVar6, param_4);
  *(uint *)(iVar6 + 2) = *(uint *)(iVar6 + 2) | 2;
  FUN_005acf30(uVar3, param_4);
  iVar4 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(undefined1 *)(iVar4 + 1) = 9;
  *(int *)(iVar4 + 0x2a) = iVar6;
  *(undefined4 *)(iVar4 + 0x2e) = *(undefined4 *)(param_4 + 4);
  *(undefined4 *)(iVar4 + 0x12) = uVar2;
  FUN_005ad220(iVar4, param_4);
  *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
  uVar3 = create_temp_object(uVar2);
  FUN_005b53d0(uVar3, 1, 1);
  iVar5 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar5 + 10) = DAT_00710998;
  *(undefined1 *)(iVar5 + 1) = 0x1e;
  uVar3 = FUN_005acdf0(uVar3);
  *(undefined4 *)(iVar5 + 0x2a) = uVar3;
  FUN_005ad220(*(undefined4 *)(*(int *)(iVar5 + 0x2a) + 0x2a), param_4);
  puVar1 = (uint *)(*(int *)(iVar5 + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x26;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar5 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x24;
  *(int *)(iVar5 + 0x2e) = iVar4;
  puVar1 = (uint *)(*(int *)(iVar5 + 0x2e) + 2);
  *puVar1 = *puVar1 | 2;
  *(undefined4 *)(iVar5 + 0x12) = uVar2;
  FUN_005ad220(iVar5, param_4);
  return *(undefined4 *)(iVar5 + 0x2a);
}



undefined4 fn_005f0f10(undefined4 param_1, int param_2)

{
  uint *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;

  uVar2 = FUN_005b7d30(*(undefined4 *)(*(int *)(*(int *)(param_2 + 0x24) + 0x2a) + 0x12));
  iVar3 = FUN_005ab970(PACK(DAT_00699b76,DAT_00699b7a), (uint)(uVar2));
  FUN_005ad220(iVar3, param_1);
  *(uint *)(iVar3 + 2) = *(uint *)(iVar3 + 2) | 2;
  iVar4 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(undefined1 *)(iVar4 + 1) = 0xf;
  *(undefined4 *)(iVar4 + 0x12) = uVar2;
  uVar5 = FUN_005acf30(*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x2a), param_1);
  *(undefined4 *)(iVar4 + 0x2a) = uVar5;
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2a) + 2);
  *puVar1 = *puVar1 | 2;
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar4 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 & 0xfffffffb;
  *(int *)(iVar4 + 0x2e) = iVar3;
  FUN_005ad220(iVar4, param_1);
  uVar5 = create_temp_object(uVar2);
  FUN_005b53d0(uVar5, 1, 1);
  iVar3 = FUN_005bd630(3);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar3 + 10) = DAT_00710998;
  *(undefined1 *)(iVar3 + 1) = 0x1e;
  uVar5 = FUN_005acdf0(uVar5);
  *(undefined4 *)(iVar3 + 0x2a) = uVar5;
  FUN_005ad220(*(undefined4 *)(*(int *)(iVar3 + 0x2a) + 0x2a), param_1);
  puVar1 = (uint *)(*(int *)(iVar3 + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x26;
  puVar1 = (uint *)(*(int *)(*(int *)(iVar3 + 0x2a) + 0x2a) + 2);
  *puVar1 = *puVar1 | 0x24;
  *(int *)(iVar3 + 0x2e) = iVar4;
  *(undefined4 *)(iVar3 + 0x12) = uVar2;
  FUN_005ad220(iVar3, param_1);
  return *(undefined4 *)(iVar3 + 0x2a);
}



byte IsLoopUnrollable(uint *param_1, undefined4 param_2, undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  undefined4 uVar8;

  uVar1 = *param_1;
  if ((uVar1 & 0x244016) != 0) {
    FUN_005ed4c0(s_IsLoopUnrollable_No_due_to_prohi_006b9116);
    FUN_005bfb20(*param_1 & 0x244016);
    FUN_005ed4c0(&DAT_006b9156);
    return 0;
  }
  if ((uVar1 & 0x100) != 0x100) {
    FUN_005ed4c0(s_IsLoopUnrollable_No_due_to_requi_006b915a);
    FUN_005bfb20(*param_1 & 0x100 ^ 0x100);
    FUN_005ed4c0(&DAT_006b9156);
    return 0;
  }
  uVar2 = param_1[5];
  uVar3 = param_1[4];
  if ((uVar3 == uVar2) && (uVar3 != param_1[8])) {
    bVar5 = false;
  }
  else {
    bVar5 = true;
  }
  if ((!bVar5) && (uVar3 != uVar2)) {
    FUN_005ed4c0(s_IsLoopUnrollable_No_because_the_l_006b908a);
    return 0;
  }
  if (param_1[7] == 0) {
    FUN_005ed4c0(s_IsLoopUnrollable_No_because_a_un_006b919e);
    return 0;
  }
  if ((*(uint *)(*(int *)(uVar2 + 0x10) + 2) & 0x10000) != 0) {
    FUN_005ed4c0(s_IsLoopUnrollable_No_because_the_l_006b91e2);
    return 0;
  }
  if ((int)DAT_0070f244 < *(int *)((int)param_1 + 0x4e)) {
    FUN_005ed4c0(s_IsLoopUnrollable_No_because_loop_006b9226);
    return 0;
  }
  if ((uVar1 & 0x8000) == 0) {
    iVar7 = FUN_005c4710(param_1);
    cVar6 = FUN_005b07f0(iVar7);
    if ((cVar6 == '\0') && ((*(uint *)(iVar7 + 2) & 0x100) == 0)) {
      FUN_005ed4c0(s_IsLoopUnrollable_No_because_Loop_006b90ce);
      return 0;
    }
    iVar7 = FUN_005ac1e0(iVar7);
    if (iVar7 != 0) {
      FUN_005ed4c0(s_IsLoopUnrollable_No_because_Loop_006b92a6);
      return 0;
    }
    if (*(int *)(param_1[0xb] + 0xe) == 0) {
      FUN_005ed4c0(s_IsLoopUnrollable_No_because_ther_006b92ea);
      return 0;
    }
    iVar7 = FUN_005b0990(*(undefined4 *)(*(int *)(param_1[0xb] + 0xe) + 0x2a));
    if (iVar7 == 0) {
      FUN_005ed4c0(s_IsLoopUnrollable_No_because_init_006b933e);
      return 0;
    }
    uVar8 = FUN_005c4830(param_1, param_1[0xb]);
    iVar7 = FUN_005ac1e0(uVar8);
    if (iVar7 != 0) {
      FUN_005ed4c0(s_IsLoopUnrollable_No_because_Loop_006b938e);
      return 0;
    }
    if ((char)param_1[0xd] == '\0') {
      FUN_005ed4c0(s_IsLoopUnrollable_No_because_can__006b93d2);
      return 0;
    }
    if ((*param_1 & 0x20) != 0) {
      pcVar4 = (char *)param_1[9];
      if ((pcVar4 != (char *)0x0) && (*pcVar4 == '\x03') && (pcVar4[1] == '\x18') &&
         ((char)param_1[0xd] != '\0' &&
         (cVar6 = CInt64_Equal(PACK(*(undefined4 *)((int)param_1 + 0x36),*(undefined4 *)((int)param_1 + 0x3a)), PACK(DAT_00699b6e,DAT_00699b72)),
         cVar6 == '\0'))) {
        return 1;
      }
      FUN_005ed4c0(s_IsLoopUnrollable_No_because_loop_006b9266);
      return 0;
    }
  }
  else {
    cVar6 = fn_005f12a0((uint *)(param_1), (uint)(param_2), (uint *)(param_3));
    if (cVar6 == '\0') {
      return 0;
    }
  }
  return 1;
}



byte fn_005f12a0(uint *param_1, undefined4 param_2, undefined4 *param_3)

{
  unsigned char nativeFrame[8];
#define local_18 (*(int *)(nativeFrame+0))
#define local_14 (*(int *)(nativeFrame+4))

  char *pcVar1;
  byte *pbVar2;
  ushort *puVar3;
  bool bVar4;
  char cVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  if (param_1[4] != param_1[5]) {
    FUN_005ed4c0(s_IsWhileLoopUnrollable_No_because_006b9416);
    return 0;
  }
  pcVar1 = *(char **)(param_1[7] + 0x14);
  if ((pcVar1 == (char *)0x0) || (*pcVar1 != '\b')) {
    FUN_005ed4c0(s_IsWhileLoopUnrollable_No_because_006b94ba);
    return 0;
  }
  if (*(uint *)(param_1[7] + 0x30) != param_1[8]) {
    FUN_005ed4c0(s_IsWhileLoopUnrollable_No_because_006b9462);
    return 0;
  }
  if (param_1[8] == param_1[4]) {
    FUN_005ed4c0(s_IsWhileLoopUnrollable_No_because_006b9506);
    return 0;
  }
  cVar5 = FUN_00454260(*(undefined4 *)(*(int *)(param_1[9] + 0x2a) + 0x12));
  if (cVar5 == '\0') {
    FUN_005ed4c0(s_IsWhileLoopUnrollable_No_because_006b9552);
    return 0;
  }
  pcVar1 = *(char **)(*(int *)(param_1[9] + 0x2a) + 0x12);
  if ((*pcVar1 != '\x01') || ((byte)pcVar1[6] > 0x16)) {
    FUN_005ed4c0(s_IsWhileLoopUnrollable_No_because_006b959a);
    return 0;
  }
  uVar8 = *param_1;
  if ((uVar8 & 0x1000) == 0) {
    FUN_005ed4c0(s_IsWhileLoopUnrollable_No_because_006b95e6);
    return 0;
  }
  if ((uVar8 & 0x20) == 0) {
    if ((uVar8 & 0x400) != 0) {
      FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b9676);
      return 0;
    }
    if ((uVar8 & 0x800) != 0) {
      FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b96ae);
      return 0;
    }
    if ((uVar8 & 0x40) == 0) {
      FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b96ea);
      return 0;
    }
    for (pbVar2 = *(byte **)((int)param_1 + 0x66); pbVar2 != (byte *)0x0 &&
        ((*pbVar2 & 1) == 0 || ((*pbVar2 & 2) == 0)); pbVar2 = *(byte **)(pbVar2 + 0x3c)) {
    }
    if (pbVar2 != (byte *)0x0) {
      cVar5 = FUN_00454260(*(undefined4 *)(*(int *)(pbVar2 + 10) + 0x12));
      if (cVar5 == '\0') {
        FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b981e);
        return 0;
      }
      pcVar1 = *(char **)(pbVar2 + 10);
      if (*pcVar1 == '\x03') {
        if ((pcVar1[1] == '\"') &&
           (cVar5 = FUN_005b0960(*(undefined4 *)(pcVar1 + 0x2e)), cVar5 != '\0')) {
          if ((*(int *)(pbVar2 + 0x30) != 0) || (*(int *)(pbVar2 + 0x34) != 1)) {
            FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b9856);
            return 0;
          }
        }
        else {
          if (*(char *)(*(int *)(pbVar2 + 10) + 1) != '\x1e') {
            FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b98de);
            return 0;
          }
          pcVar1 = *(char **)(*(int *)(pbVar2 + 10) + 0x2e);
          if ((*pcVar1 != '\x03') || (pcVar1[1] != '\x0f') ||
             (cVar5 = FUN_005b0960(*(undefined4 *)(pcVar1 + 0x2e)), cVar5 == '\0')) {
            FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b9896);
            return 0;
          }
          if ((*(int *)(pbVar2 + 0x30) != 0) || (*(int *)(pbVar2 + 0x34) != 1)) {
            FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b9856);
            return 0;
          }
        }
      }
      else if ((*pcVar1 == '\x02') && (pcVar1[1] != '\x02') && (pcVar1[1] != '\0')) {
        FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b9736);
        return 0;
      }
      FUN_005c45f0(param_1);
      param_1[0xb] = (uint)pbVar2;
      FUN_005c4630(param_1);
      puVar3 = DAT_00710990;
      puVar7 = param_3;
      for (iVar6 = 9; iVar6 != 0; iVar6 = iVar6 - 1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      while( true ) {
        if (puVar3 == (ushort *)0x0) {
          if ((local_18 < 2) && (local_14 < 2)) {
            return 1;
          }
          FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b992e);
          return 0;
        }
        bVar4 = false;
        uVar8 = (uint)(*puVar3 >> 5);
        if ((uVar8 < *(uint *)param_1[2]) &&
           ((((uint *)param_1[2])[uVar8 + 1] & 1 << ((byte)*puVar3 & 0x1f)) != 0)) {
          bVar4 = true;
        }
        if ((bVar4) && (puVar3 != (ushort *)param_1[5]) &&
           (cVar5 = fn_005f16b0((int)(puVar3), (uint)(param_1), (int)(pbVar2), (undefined8 *)(param_2), (int *)(&local_18), (int *)(&local_14), (int *)(param_3)),
           cVar5 == '\0')) break;
        puVar3 = *(ushort **)(puVar3 + 0x18);
      }
      FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b977e);
      return 0;
    }
    FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b97c6);
    return 0;
  }
  FUN_005ed4c0(s_IsWhileLoopUnrollable__No_becaus_006b963a);
  return 0;
}
#undef local_18
#undef local_14


byte
fn_005f16b0(int param_1, undefined4 param_2, int param_3, undefined8 *param_4, int *param_5,
            int *param_6, int *param_7)

{
  unsigned char nativeFrame[8];
#define local_38 (*(undefined4 *)(nativeFrame+0))
#define local_34 (*(undefined4 *)(nativeFrame+4))

  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  undefined8 uVar9;
  *param_5 = 0;
  *param_6 = 0;
  pcVar6 = *(char **)(param_1 + 0x10);
  if (pcVar6 != (char *)0x0) {
    while( true ) {
      cVar2 = FUN_005c4550(param_2, pcVar6);
      if ((cVar2 == '\0') && ((*(uint *)(pcVar6 + 2) & 2) == 0) && (cVar2 = *pcVar6, cVar2 != '\0')
         && (cVar2 != '\r')) {
        if ((cVar2 != '\x03') || ((byte)(pcVar6[1] - 0x26U) > 2)) {
          return 0;
        }
        *param_6 = *param_6 + 1;
        pcVar7 = *(char **)(pcVar6 + 0x2a);
        if ((*pcVar7 != '\x02') || (pcVar7[1] != '\x04')) {
          return 0;
        }
        pcVar7 = *(char **)(pcVar7 + 0x2a);
        if ((*pcVar7 != '\x03') || (pcVar7[1] != '\x0f')) {
          return 0;
        }
        param_7[1] = *(int *)(pcVar7 + 0x2a);
        param_7[2] = *(int *)(pcVar7 + 0x12);
        iVar3 = FUN_005b0990(*(undefined4 *)(pcVar7 + 0x2a));
        if (iVar3 == 0) {
          return 0;
        }
        *param_7 = *(int *)(pcVar7 + 0x2e);
        pcVar7 = (char *)*param_7;
        if ((*pcVar7 == '\x03') && (pcVar7[1] == '\x11') &&
           (cVar2 = FUN_005b0960(*(undefined4 *)(pcVar7 + 0x2e)), cVar2 != '\0')) {
          iVar3 = *(int *)(*(int *)(*param_7 + 0x2e) + 0x2a);
          iVar1 = *(int *)(iVar3 + 0x14);
          param_7[7] = *(int *)(iVar3 + 0x10);
          param_7[8] = iVar1;
          pcVar7 = *(char **)(*param_7 + 0x2a);
        }
        else {
          iVar3 = DAT_0070490c;
          param_7[7] = DAT_00704908;
          param_7[8] = iVar3;
          pcVar7 = (char *)*param_7;
        }
        param_7[4] = *(int *)(pcVar6 + 0x2e);
        pcVar8 = (char *)param_7[4];
        cVar2 = *pcVar8;
        if ((cVar2 == '\x02') && (pcVar8[1] == '2')) {
          if ((*pcVar6 == '\x03') && (pcVar6[1] == '&')) {
            pcVar8 = *(char **)(pcVar8 + 0x2a);
            if ((*pcVar8 != '\x02') || (pcVar8[1] != '\x06')) {
              return 0;
            }
            param_7[3] = *(int *)(pcVar8 + 0x2a);
          }
          else {
            param_7[3] = *(int *)(pcVar8 + 0x2a);
          }
          pcVar8 = (char *)param_7[3];
          if ((*pcVar8 != '\x03') || (pcVar8[1] != '\x11') ||
             (cVar2 = FUN_005b0960(*(undefined4 *)(pcVar8 + 0x2a)), cVar2 == '\0')) {
            return 0;
          }
          iVar3 = *(int *)(*(int *)(param_7[3] + 0x2a) + 0x2a);
          local_34 = *(undefined4 *)(iVar3 + 0x14);
          local_38 = *(undefined4 *)(iVar3 + 0x10);
          pcVar8 = *(char **)(param_7[3] + 0x2e);
        }
        else if ((cVar2 == '\x03') && (pcVar8[1] == '\x11' && (*pcVar6 == '\x03')) &&
                ((byte)(pcVar6[1] - 0x27U) < 2)) {
          param_7[3] = (int)pcVar8;
          cVar2 = FUN_005b0960(*(undefined4 *)(param_7[3] + 0x2a));
          if (cVar2 == '\0') {
            return 0;
          }
          iVar3 = *(int *)(*(int *)(param_7[3] + 0x2a) + 0x2a);
          local_34 = *(undefined4 *)(iVar3 + 0x14);
          local_38 = *(undefined4 *)(iVar3 + 0x10);
          pcVar8 = *(char **)(param_7[3] + 0x2e);
        }
        else {
          if ((cVar2 != '\x02') || (pcVar8[1] != '\x06') || (*pcVar6 != '\x03') ||
             (pcVar6[1] != '&')) {
            return 0;
          }
          param_7[3] = *(int *)(pcVar8 + 0x2a);
          pcVar8 = (char *)param_7[3];
          if ((*pcVar8 != '\x03') || (pcVar8[1] != '\x11') ||
             (cVar2 = FUN_005b0960(*(undefined4 *)(pcVar8 + 0x2a)), cVar2 == '\0')) {
            return 0;
          }
          iVar3 = *(int *)(*(int *)(param_7[3] + 0x2a) + 0x2a);
          local_34 = *(undefined4 *)(iVar3 + 0x14);
          local_38 = *(undefined4 *)(iVar3 + 0x10);
          pcVar8 = *(char **)(param_7[3] + 0x2e);
        }
        if ((*pcVar8 != '\x03') || (pcVar8[1] != '\x19') ||
           (*pcVar7 != '\x03' || (pcVar7[1] != '\x12'))) {
          return 0;
        }
        uVar5 = *(undefined4 *)(pcVar8 + 0x2a);
        uVar4 = FUN_005b0990(*(undefined4 *)(pcVar7 + 0x2a));
        uVar5 = FUN_005b0990(uVar5);
        cVar2 = FUN_00455840(uVar4, uVar5);
        if ((cVar2 == '\0') ||
           (cVar2 = FUN_00455840(uVar4, *(undefined4 *)(*(int *)(param_3 + 2) + 4)), cVar2 == '\0'))
        {
          return 0;
        }
        iVar3 = *(int *)(pcVar7 + 0x2e);
        iVar1 = *(int *)(pcVar8 + 0x2e);
        cVar2 = FUN_005b0960(iVar3);
        if ((cVar2 == '\0') || (cVar2 = FUN_005b0960(iVar1), cVar2 == '\0')) {
          return 0;
        }
        iVar3 = *(int *)(iVar3 + 0x2a);
        uVar9 = CInt64_Shl(PACK(DAT_00699b76,DAT_00699b7a), PACK(*(undefined4 *)(iVar3 + 0x10),*(undefined4 *)(iVar3 + 0x14)));
        uVar9 = CInt64_Sub(PACK(WORD0(uVar9),WORD1(uVar9)), PACK(DAT_00699b76,DAT_00699b7a));
        uVar4 = (undefined4)((ulonglong)uVar9 >> 0x20);
        uVar5 = (undefined4)uVar9;
        iVar3 = *(int *)(iVar1 + 0x2a);
        cVar2 = CInt64_Equal(PACK(WORD0(uVar9),WORD1(uVar9)), PACK(*(undefined4 *)(iVar3 + 0x10),*(undefined4 *)(iVar3 + 0x14)));
        if (cVar2 == '\0') {
          return 0;
        }
        cVar2 = CInt64_Equal(PACK(uVar5,uVar4), PACK(0,uVar4));
        if (cVar2 == '\0') {
          return 0;
        }
        uVar9 = CInt64_Add(PACK(uVar5,uVar4), PACK(DAT_00699b76,DAT_00699b7a));
        *param_4 = uVar9;
        uVar9 = CInt64_Add(PACK(uVar5,uVar4), PACK(DAT_00699b76,DAT_00699b7a));
        cVar2 = fn_005f1bd0(NativeWords(WORD0(uVar9),WORD1(uVar9)), NativeWords(local_38,local_34), (NativePair *)(param_7 + 5));
        if ((cVar2 != '\0') && (*param_5 = *param_5 + 1, *pcVar6 == '\x03') && (pcVar6[1] == '&')) {
          uVar9 = CInt64_Not(PACK(param_7[5],param_7[6]));
          *(undefined8 *)(param_7 + 5) = uVar9;
        }
      }
      if (pcVar6 == *(char **)(param_1 + 0x14)) break;
      pcVar6 = *(char **)(pcVar6 + 0x3e);
    }
  }
  return 1;
}
#undef local_38
#undef local_34


/* Baseline algorithm with the verified native AL Boolean return contract. */
byte fn_005f1bd0(NativePair a, NativePair b, NativePair *out)
{
    NativePair term;
    NativePair index=NativeZero;
    NativePair overlap;
    NativePair result=NativeZero;
    if(NativeLess(NativeZero,a)) {
        do {
            term=NativeShift(b,index);
            overlap=NativeAnd(term,result);
            if(NativeNotEqual(overlap,NativeZero))return 0;
            result=NativeOr(term,result);
            index=NativeAdd(index,NativeOne);
        }while(NativeLess(index,a));
    }
    *out=result;
    return 1;
}


void IRO_LoopUnroller(void)
{
    uint *head;
    uint *loop;
    head=(uint *)FUN_005c59c0();
    for(loop=head;loop;loop=*(uint **)((byte *)loop+0x6a))FUN_005c57e0(loop);
    FUN_005c3130(head);
    for(loop=head;loop;loop=*(uint **)((byte *)loop+0x6a)) {
        if(*loop&0x80000) {
            FUN_005ed4c0(s_IRO_LoopUnroller_Found_loop_with_006b997e,*(ushort *)loop[5]);
            FUN_005bf2c0(s_Loop_includes__006b99aa,loop[2]);
            fn_005ed9f0(loop);
            FUN_005b8d90(DAT_00710170);
        }
    }
    FUN_005c5920(head);
    FUN_005be190(DAT_00710170);
    FUN_005a9d80();
}
