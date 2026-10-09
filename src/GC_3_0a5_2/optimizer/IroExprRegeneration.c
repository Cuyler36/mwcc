#include <string.h>

/* IroExprRegeneration.c: native member and data review is recorded in the TU ledger.
 * 32-bit x86 candidate. Offsets preserve the native two-byte-aligned optimizer records.
 * Native range, queue and 66-byte snapshot records are reviewed in frame-layout.json.
 */
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef byte bool;
typedef uint code();
#pragma options align=mac68k
typedef struct LinearRange { uint first; uint last; } LinearRange;
typedef struct NativeQueue { int buffer; short count; ushort head; } NativeQueue;
#pragma options align=reset
#define true 1
#define false 0
#define CONCAT22(hi,lo) (((uint)(ushort)(hi)<<16)|(ushort)(lo))

extern uint DAT_00699b76;
extern uint DAT_00699b7a;
extern uint DAT_00704908;
extern uint DAT_0070490c;
extern char DAT_0070f1a8;
extern char DAT_0070f234;
extern char DAT_0070f249;
extern char DAT_0070f24a;
extern char DAT_0070f24b;
extern uint DAT_00710084;
extern uint *DAT_0071015c;
extern uint DAT_00710170;
extern uint DAT_007101c4;
extern uint *DAT_00710358;
extern code *DAT_007108f4;
extern uint DAT_00710990;
extern uint DAT_00710998;
extern code *DAT_007109a4;
extern uint DAT_00710b54;
extern ushort DAT_007172c0;
extern byte DAT_00725ee2[];
extern char DAT_00725f3e;
extern char DAT_00725f43;
extern char DAT_007260c1;
extern char DAT_007260c2;
extern char DAT_007260c5;
extern void LAB_005f6240();
extern code *PTR_FUN_006ac972;
extern uint CDecl_NewPointerType();
extern uint CError_Internal();
extern uint CInt64_Equal();
extern uint CompilerTools_AllocatePoolMemory();
extern uint FUN_00455840();
extern uint FUN_004c53c0();
extern uint FUN_004c5480();
extern uint FUN_004eaa90();
extern uint FUN_00521c20();
extern uint FUN_005a9d80();
extern uint FUN_005a9ee0();
extern uint FUN_005abcd0();
extern uint FUN_005abf30();
extern uint FUN_005abfc0();
extern uint FUN_005ac1e0();
extern uint FUN_005ac320();
extern uint FUN_005ac770();
extern uint FUN_005acb80();
extern uint FUN_005acdf0();
extern uint FUN_005acf30();
extern uint FUN_005ad220();
extern uint FUN_005ad280();
extern uint FUN_005ad400();
extern uint FUN_005ad440();
extern uint FUN_005ad570();
extern uint FUN_005ad5c0();
extern uint FUN_005ad5e0();
extern uint FUN_005ae350();
extern uint FUN_005ae7b0();
extern uint FUN_005af0d0();
extern uint FUN_005af650();
extern uint FUN_005afcd0();
extern uint FUN_005b04a0();
extern uint FUN_005b07a0();
extern uint FUN_005b07f0();
extern uint FUN_005b53d0();
extern uint FUN_005b7d30();
extern uint FUN_005b7e20();
extern uint FUN_005b8d90();
extern uint FUN_005bd630();
extern uint FUN_005bd930();
extern uint FUN_005bdc90();
extern uint FUN_005be4b0();
extern uint FUN_005be690();
extern uint FUN_005bf760();
extern uint FUN_005bf940();
extern uint FUN_005bfae0();
extern uint FUN_005ed4c0();
extern uint FUN_005ed5e0();
extern uint FUN_005f6b80();
extern uint FUN_00605250();
extern uint IroUtil_FindNextUse();
extern uint create_temp_object();
extern uint is_volatile_object();

static char DAT_006b9f2b[] = "cos";
static char DAT_006b9f2f[] = "sin";
static char s_Examining_div_mod_at__d__d_006b9eaf[] = "Examining div+mod at %d,%d\n";
static char s_Examining_sin_cos_at__d__d_006b9f33[] = "Examining sin+cos at %d,%d\n";
static char s_GenerateCombinedOperations_006b9dfb[] = "GenerateCombinedOperations";
static char s_GenerateCondAssignments_006b9e97[] = "GenerateCondAssignments";
static char s_Generating_ECONDASSes_006b9e7f[] = "Generating ECONDASSes\n";
static char s_Generating_combined_DIV_MOD___SI_006b9dd3[] = "Generating combined DIV+MOD / SIN+COS\n";
static char s_IroExprRegeneration_c_006b9f6f[] = "IroExprRegeneration.c";
static char s_IroFlowgraph_h_006b9f87[] = "IroFlowgraph.h";
static char s_Not_combined_div_mod_at__d__d_006b9ecb[] = "Not combined div+mod at %d,%d\n";
static char s_Not_combined_sin_cos_at__d__d_006b9f4f[] = "Not combined sin+cos at %d,%d\n";
static char s_RebuildCondExpressions_006b9e67[] = "RebuildCondExpressions";
static char s_RebuildLogicalExpressions_006b9e37[] = "RebuildLogicalExpressions";
static char s_Rebuilding_ECONDs_006b9e53[] = "Rebuilding ECONDs\n";
static char s_Rebuilding_ELORs_and_ELANDs_006b9e17[] = "Rebuilding ELORs and ELANDs\n";
static char s_Replacing_div_mod_at__d__d____006b9eeb[] = "Replacing div/mod at %d/%d...\n";
static char s_Replacing_sin_cos_at__d__d____006b9f0b[] = "Replacing sin/cos at %d/%d...\n";

void IRO_RegenerateExpressions(void);
void GenerateCombinedOperations(void);
byte IsCombinedSinCos(char *param_1, char *param_2);
byte IsCosine(int param_1, uint *param_2);
byte IsSine(int param_1, uint *param_2);
int OrderByStatement(int *param_1, int *param_2);
void NewDualOperationRTCall(uint param_1, int param_2, uint param_3, int param_4,
                 uint param_5, uint param_6);
void GenerateCondAssignments(void);
byte GeneratePossibleCondAss(int param_1);
void RebuildLogicalExpressions(void);
byte RebuildPossibleLogicalExpression(uint param_1, uint param_2);
void AddNodeAndSuccessorsRecursively(int *param_1, ushort *param_2, ushort *param_3);
void fn_00609750(int *param_1, ushort param_2);
byte
CheckForTopLevelExpressions(int param_1, ushort *param_2, int param_3, char *param_4, char *param_5, char param_6);
void RebuildCondExpressions(void);
byte RebuildPossibleReturnCondExpression(int param_1);
byte RebuildPossibleCondExpression(ushort *param_1);
byte CheckThenOrElseBranch(ushort *param_1, uint param_2, char *param_3, char param_4);
char UsesAKilledVarBeforeUse(int param_1, int param_2, char *param_3, uint *param_4, char param_5);
void GetDependsOfStatement(int param_1, char param_2, uint param_3);
void fn_0060b3b0(byte *param_1, int param_2, uint *param_3, char *param_4);
char HasSideEffectsBeforeUse(int param_1, int param_2, int param_3, char param_4);
void StatementHasSideEffectBeforeUse(byte *param_1, int param_2, char *param_3);
char fn_0060b8e0(int param_1, int param_2, int param_3, char param_4);
void fn_0060ba20(byte *param_1, int param_2, char *param_3);
byte RewriteUse(int param_1, int param_2, int param_3, char param_4);

/* Native 0x606c40, 409 bytes. */
void IRO_RegenerateExpressions(void)
{
  if ((DAT_0070f24a != '\0') || (DAT_0070f249 != '\0') || (DAT_0070f24b != '\0') ||
     (DAT_007109a4 != 0 || (DAT_007108f4 != 0))) {
    FUN_005b8d90(DAT_00710170);
    FUN_005be690();
    FUN_005be4b0();
    FUN_00605250();
  }
  FUN_005bfae0(&DAT_0071015c, DAT_00710084 + 1);
  FUN_005bfae0(&DAT_00710358, DAT_00710084 + 1);
  if (DAT_0070f24a != '\0') {
    FUN_005ed4c0(s_Rebuilding_ELORs_and_ELANDs_006b9e17);
    RebuildLogicalExpressions();
    FUN_005ed5e0(s_RebuildLogicalExpressions_006b9e37, 0);
  }
  if (DAT_0070f249 != '\0') {
    FUN_005ed4c0(s_Rebuilding_ECONDs_006b9e53);
    RebuildCondExpressions();
    FUN_005ed5e0(s_RebuildCondExpressions_006b9e67, 0);
  }
  if (DAT_0070f24b != '\0') {
    FUN_005ed4c0(s_Generating_ECONDASSes_006b9e7f);
    GenerateCondAssignments();
    FUN_005ed5e0(s_GenerateCondAssignments_006b9e97, 0);
  }
  if ((DAT_007109a4 != 0) || (DAT_007108f4 != 0)) {
    FUN_005ed4c0(s_Generating_combined_DIV_MOD___SI_006b9dd3);
    GenerateCombinedOperations();
    FUN_005ed5e0(s_GenerateCombinedOperations_006b9dfb, 0);
  }
  if ((DAT_0070f24a != '\0') || (DAT_0070f249 != '\0') || (DAT_0070f24b != '\0')) {
    FUN_005b8d90(DAT_00710170);
  }
  return;
}

/* Native 0x606de0, 1476 bytes. */
void GenerateCombinedOperations(void)
{
  LinearRange uStack_44_range;
  LinearRange uStack_3c_range;
  LinearRange uStack_34_range;
  LinearRange uStack_2c_range;
  char cVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  uint uVar11;
  uint uVar12;

  int local_24;
  uint uStack_20;
  char *local_1c;
  int iStack_18;
  char *local_14;
  if (((DAT_00725f3e == '\0') || (DAT_007260c5 == '\0')) &&
     (DAT_00725f43 == '\0' || (DAT_007260c1 == '\0'))) {
    return;
  }
  local_24 = DAT_00710990;
  do {
    if ((local_24 == 0) || (*(int *)(local_24 + 0x14) == 0)) {
      FUN_005a9d80();
      return;
    }
    for (local_1c = *(char **)(local_24 + 0x10); local_1c != (char *)0x0;
        local_1c = *(char **)(local_1c + 0x3e)) {
      pcVar7 = *(char **)(local_1c + 0x3e);
      pcVar6 = local_1c;
      while (local_1c = pcVar6, local_14 = pcVar7, pcVar7 != (char *)0x0) {
        if ((DAT_00725f3e == '\0') || (DAT_007109a4 == (code *)0x0)) {
LAB_006070a0:;
          if ((DAT_00725f43 != '\0') &&
             (DAT_007108f4 != (code *)0x0 &&
             (cVar3 = IsCombinedSinCos((char *)(local_1c), (char *)(local_14)), cVar3 != '\0') &&
             (cVar3 = FUN_005ac320(local_1c), cVar3 == '\0')) &&
             (cVar3 = FUN_005ac320(local_14), cVar3 == '\0' &&
             (iStack_18 = (*DAT_007108f4)(local_1c, local_14), iStack_18 != 0))) {
            FUN_005ed4c0(s_Replacing_sin_cos_at__d__d____006b9f0b, *(uint *)(local_1c + 10),
                         *(uint *)(local_14 + 10));
            uStack_20 = OrderByStatement((int *)(&local_1c), (int *)(&local_14));
            pcVar7 = local_1c;
            if ((**(char **)(local_1c + 0x32) == '\x01') &&
               (*(char *)(*(int *)(local_1c + 0x32) + 1) == ';')) {
              iVar4 = *(int *)(*(int *)(*(int *)(local_1c + 0x32) + 0x2a) + 0x10);
              iVar5 = *(int *)(iVar4 + 0xc);
              iVar4 = *(int *)(iVar4 + 8);
              if ((DAT_0070f1a8 != '\0') && (cVar3 = FUN_004eaa90(iVar4), cVar3 == '\0') &&
                 (iVar4 != DAT_007101c4)) goto LAB_006071c0;
              iVar4 = memcmp((char *)(iVar5 + 10), DAT_006b9f2b, 4);
              if ((iVar4 != 0) || (*(short *)(pcVar7 + 0x2c) != 1) ||
                 (**(char **)(**(int **)(pcVar7 + 0x2e) + 0x12) != '\x02') ||
                 (**(char **)(pcVar7 + 0x12) != '\x02')) goto LAB_006071c0;
              bVar2 = true;
            }
            else {
LAB_006071c0:;
              bVar2 = false;
            }
            pcVar7 = local_14;
            pcVar6 = local_1c;
            if (!bVar2) {
              iVar4 = create_temp_object(*(uint *)(local_1c + 0x12));
              FUN_005b53d0(iVar4, 1, 1);
              *(uint *)(*(int *)(iVar4 + 0x40) + 4) = 2;
              iVar5 = create_temp_object(*(uint *)(pcVar6 + 0x12));
              FUN_005b53d0(iVar5, 1, 1);
              *(uint *)(*(int *)(iVar5 + 0x40) + 4) = 2;
              FUN_005ac770(pcVar6, iVar4, pcVar6);
              FUN_005ac770(pcVar7, iVar5, pcVar7);
              FUN_005ad280(&uStack_34_range.first);
              NewDualOperationRTCall((uint)(&uStack_34_range.first), (int)(iStack_18), (uint)(**(uint **)(pcVar6 + 0x2e)), (int)(0), (uint)(iVar4), (uint)(iVar5))
              ;
              uVar11 = uStack_34_range.first;
              uVar12 = uStack_34_range.last;
              goto LAB_00607318;
            }
            iVar4 = create_temp_object(*(uint *)(local_14 + 0x12));
            FUN_005b53d0(iVar4, 1, 1);
            *(uint *)(*(int *)(iVar4 + 0x40) + 4) = 2;
            iVar5 = create_temp_object(*(uint *)(pcVar7 + 0x12));
            FUN_005b53d0(iVar5, 1, 1);
            *(uint *)(*(int *)(iVar5 + 0x40) + 4) = 2;
            FUN_005ac770(pcVar7, iVar4, pcVar7);
            FUN_005ac770(pcVar6, iVar5, pcVar6);
            FUN_005ad280(&uStack_44_range.first);
            NewDualOperationRTCall((uint)(&uStack_44_range.first), (int)(iStack_18), (uint)(**(uint **)(pcVar7 + 0x2e)), (int)(0), (uint)(iVar4), (uint)(iVar5));
            FUN_005ad440(uStack_44_range.first, uStack_44_range.last, uStack_20);
            FUN_005ae7b0(pcVar7);
            goto LAB_00607328;
          }
        }
        else {
          if ((*pcVar6 == '\x03') && (*pcVar7 == '\x03') &&
             ((pcVar6[1] == '\v' && (pcVar7[1] == '\f')) ||
             (pcVar6[1] == '\f' && (pcVar7[1] == '\v')))) {
            FUN_005ed4c0(s_Examining_div_mod_at__d__d_006b9eaf, *(uint *)(pcVar6 + 10),
                         *(uint *)(pcVar7 + 10));
            cVar3 = FUN_005af650(*(uint *)(pcVar6 + 0x2a), *(uint *)(pcVar7 + 0x2a));
            if ((cVar3 == '\0') ||
               (cVar3 = FUN_005af650(*(uint *)(pcVar6 + 0x2e), *(uint *)(pcVar7 + 0x2e))
               , cVar3 == '\0')) {
              FUN_005ed4c0(s_Not_combined_div_mod_at__d__d_006b9ecb, *(uint *)(pcVar6 + 10),
                           *(uint *)(pcVar7 + 10));
              goto LAB_00606ef5;
            }
            bVar2 = true;
          }
          else {
LAB_00606ef5:;
            bVar2 = false;
          }
          if ((!bVar2) || (iStack_18 = (*DAT_007109a4)(local_1c, local_14), iStack_18 == 0))
          goto LAB_006070a0;
          FUN_005ed4c0(s_Replacing_div_mod_at__d__d____006b9eeb, *(uint *)(local_1c + 10),
                       *(uint *)(local_14 + 10));
          uStack_20 = OrderByStatement((int *)(&local_1c), (int *)(&local_14));
          pcVar6 = local_14;
          pcVar7 = local_1c;
          if (local_1c[1] == '\f') {
            iVar4 = create_temp_object(*(uint *)(local_14 + 0x12));
            FUN_005b53d0(iVar4, 1, 1);
            *(uint *)(*(int *)(iVar4 + 0x40) + 4) = 2;
            iVar5 = create_temp_object(*(uint *)(pcVar6 + 0x12));
            FUN_005b53d0(iVar5, 1, 1);
            *(uint *)(*(int *)(iVar5 + 0x40) + 4) = 2;
            FUN_005ac770(pcVar6, iVar4, pcVar6);
            FUN_005ac770(pcVar7, iVar5, pcVar7);
            FUN_005ad280(&uStack_2c_range.first);
            NewDualOperationRTCall((uint)(&uStack_2c_range.first), (int)(iStack_18), (uint)(*(uint *)(pcVar6 + 0x2a)), (int)(*(uint *)(pcVar6 + 0x2e)), (uint)(iVar4), (uint)(iVar5));
            uVar11 = uStack_2c_range.first;
            uVar12 = uStack_2c_range.last;
LAB_00607318:;
            FUN_005ad440(uVar11, uVar12, uStack_20);
            FUN_005ae7b0(pcVar6);
            pcVar6 = pcVar7;
          }
          else {
            iVar4 = create_temp_object(*(uint *)(local_1c + 0x12));
            FUN_005b53d0(iVar4, 1, 1);
            *(uint *)(*(int *)(iVar4 + 0x40) + 4) = 2;
            iVar5 = create_temp_object(*(uint *)(pcVar7 + 0x12));
            FUN_005b53d0(iVar5, 1, 1);
            *(uint *)(*(int *)(iVar5 + 0x40) + 4) = 2;
            FUN_005ac770(pcVar7, iVar4, pcVar7);
            FUN_005ac770(pcVar6, iVar5, pcVar6);
            FUN_005ad280(&uStack_3c_range.first);
            NewDualOperationRTCall((uint)(&uStack_3c_range.first), (int)(iStack_18), (uint)(*(uint *)(pcVar7 + 0x2a)), (int)(*(uint *)(pcVar7 + 0x2e)), (uint)(iVar4), (uint)(iVar5));
            FUN_005ad440(uStack_3c_range.first, uStack_3c_range.last, uStack_20);
            FUN_005ae7b0(pcVar7);
          }
LAB_00607328:;
          FUN_005ae7b0(pcVar6);
        }
        if (local_14 == *(char **)(local_24 + 0x14)) break;
        pcVar6 = local_1c;
        pcVar7 = *(char **)(local_14 + 0x3e);
      }
      if (local_1c == *(char **)(local_24 + 0x14)) break;
    }
    local_24 = *(int *)(local_24 + 0x30);
  } while( true );
}

/* Native 0x6073b0, 801 bytes. */
byte IsCombinedSinCos(char *param_1, char *param_2)
{
  char cVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  uint uVar10;
  uint local_14;
  if (*param_1 != '\a') {
    return 0;
  }
  if (*param_2 != '\a') {
    return 0;
  }
  pcVar6 = *(char **)(param_1 + 0x32);
  if ((*pcVar6 == '\x01') && (pcVar6[1] == ';')) {
    iVar2 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 0xc);
    iVar5 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 8);
    if ((DAT_0070f1a8 != '\0') &&
       (cVar3 = FUN_004eaa90(iVar5), cVar3 == '\0' && (iVar5 != DAT_007101c4))) goto LAB_00607695;
    iVar5 = memcmp((char *)(iVar2 + 10), DAT_006b9f2f, 4);
    if ((iVar5 != 0) || (*(short *)(param_1 + 0x2c) != 1) ||
       (**(char **)(**(int **)(param_1 + 0x2e) + 0x12) != '\x02') ||
       (**(char **)(param_1 + 0x12) != '\x02')) goto LAB_00607695;
    bVar4 = true;
  }
  else {
LAB_00607695:;
    bVar4 = false;
  }
  if (bVar4) {
    local_14 = **(uint **)(param_1 + 0x2e);
    pcVar6 = *(char **)(param_2 + 0x32);
    if ((*pcVar6 == '\x01') && (pcVar6[1] == ';')) {
      iVar2 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 0xc);
      iVar5 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 8);
      if ((DAT_0070f1a8 != '\0') &&
         (cVar3 = FUN_004eaa90(iVar5), cVar3 == '\0' && (iVar5 != DAT_007101c4))) goto LAB_006076a0;
      iVar5 = memcmp((char *)(iVar2 + 10), DAT_006b9f2b, 4);
      if ((iVar5 != 0) || (*(short *)(param_2 + 0x2c) != 1) ||
         (**(char **)(**(int **)(param_2 + 0x2e) + 0x12) != '\x02') ||
         (**(char **)(param_2 + 0x12) != '\x02')) goto LAB_006076a0;
      bVar4 = true;
    }
    else {
LAB_006076a0:;
      bVar4 = false;
    }
    if (bVar4) {
      uVar10 = **(uint **)(param_2 + 0x2e);
      goto LAB_00607666;
    }
  }
  pcVar6 = *(char **)(param_2 + 0x32);
  if ((*pcVar6 == '\x01') && (pcVar6[1] == ';')) {
    iVar2 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 0xc);
    iVar5 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 8);
    if ((DAT_0070f1a8 != '\0') &&
       (cVar3 = FUN_004eaa90(iVar5), cVar3 == '\0' && (iVar5 != DAT_007101c4))) goto LAB_006076a7;
    iVar5 = memcmp((char *)(iVar2 + 10), DAT_006b9f2f, 4);
    if ((iVar5 != 0) || (*(short *)(param_2 + 0x2c) != 1) ||
       (**(char **)(**(int **)(param_2 + 0x2e) + 0x12) != '\x02') ||
       (**(char **)(param_2 + 0x12) != '\x02')) goto LAB_006076a7;
    bVar4 = true;
  }
  else {
LAB_006076a7:;
    bVar4 = false;
  }
  if (!bVar4) {
    return 0;
  }
  uVar10 = **(uint **)(param_2 + 0x2e);
  pcVar6 = *(char **)(param_1 + 0x32);
  if ((*pcVar6 == '\x01') && (pcVar6[1] == ';')) {
    iVar2 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 0xc);
    iVar5 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 8);
    if ((DAT_0070f1a8 != '\0') &&
       (cVar3 = FUN_004eaa90(iVar5), cVar3 == '\0' && (iVar5 != DAT_007101c4)))
    goto LAB_006076b0;
    iVar5 = memcmp((char *)(iVar2 + 10), DAT_006b9f2b, 4);
    if ((iVar5 != 0) || (*(short *)(param_1 + 0x2c) != 1) ||
       (**(char **)(**(int **)(param_1 + 0x2e) + 0x12) != '\x02') ||
       (**(char **)(param_1 + 0x12) != '\x02')) goto LAB_006076b0;
    bVar4 = true;
  }
  else {
LAB_006076b0:;
    bVar4 = false;
  }
  if (!bVar4) {
    return 0;
  }
  local_14 = **(uint **)(param_1 + 0x2e);
LAB_00607666:;
  FUN_005ed4c0(s_Examining_sin_cos_at__d__d_006b9f33, *(uint *)(param_1 + 10),
               *(uint *)(param_2 + 10));
  cVar3 = FUN_005af650(local_14, uVar10);
  if (cVar3 == '\0') {
    FUN_005ed4c0(s_Not_combined_sin_cos_at__d__d_006b9f4f, *(uint *)(param_1 + 10),
                 *(uint *)(param_2 + 10));
    return 0;
  }
  return 1;
}

/* Native 0x6076e0, 156 bytes. */
byte IsCosine(int param_1, uint *param_2)
{
  char cVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  pcVar6 = *(char **)(param_1 + 0x32);
  if ((*pcVar6 == '\x01') && (pcVar6[1] == ';')) {
    iVar2 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 0xc);
    iVar5 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 8);
    if (DAT_0070f1a8 != '\0') {
      cVar4 = FUN_004eaa90(iVar5);
      if ((cVar4 == '\0') && (iVar5 != DAT_007101c4)) goto LAB_00607771;
    }
    iVar5 = memcmp((char *)(iVar2 + 10), DAT_006b9f2b, 4);
    if ((iVar5 == 0) && (*(short *)(param_1 + 0x2c) == 1) &&
       (**(char **)(**(int **)(param_1 + 0x2e) + 0x12) == '\x02') &&
       (**(char **)(param_1 + 0x12) == '\x02')) {
      bVar3 = true;
      goto LAB_0060775b;
    }
  }
LAB_00607771:;
  bVar3 = false;
LAB_0060775b:;
  if (bVar3) {
    if (param_2 != (uint *)0x0) {
      *param_2 = **(uint **)(param_1 + 0x2e);
    }
    return 1;
  }
  return 0;
}

/* Native 0x607780, 156 bytes. */
byte IsSine(int param_1, uint *param_2)
{
  char cVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  pcVar6 = *(char **)(param_1 + 0x32);
  if ((*pcVar6 == '\x01') && (pcVar6[1] == ';')) {
    iVar2 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 0xc);
    iVar5 = *(int *)(*(int *)(*(int *)(pcVar6 + 0x2a) + 0x10) + 8);
    if (DAT_0070f1a8 != '\0') {
      cVar4 = FUN_004eaa90(iVar5);
      if ((cVar4 == '\0') && (iVar5 != DAT_007101c4)) goto LAB_00607811;
    }
    iVar5 = memcmp((char *)(iVar2 + 10), DAT_006b9f2f, 4);
    if ((iVar5 == 0) && (*(short *)(param_1 + 0x2c) == 1) &&
       (**(char **)(**(int **)(param_1 + 0x2e) + 0x12) == '\x02') &&
       (**(char **)(param_1 + 0x12) == '\x02')) {
      bVar3 = true;
      goto LAB_006077fb;
    }
  }
LAB_00607811:;
  bVar3 = false;
LAB_006077fb:;
  if (bVar3) {
    if (param_2 != (uint *)0x0) {
      *param_2 = **(uint **)(param_1 + 0x2e);
    }
    return 1;
  }
  return 0;
}

/* Native 0x607820, 196 bytes. */
int OrderByStatement(int *param_1, int *param_2)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  iVar1 = *param_1;
  do {
    iVar4 = iVar1;
    iVar1 = IroUtil_FindNextUse(iVar4);
  } while (iVar1 != 0);
  if ((iVar4 == 0) || ((*(uint *)(iVar4 + 2) & 2) != 0)) {
    CError_Internal(s_IroExprRegeneration_c_006b9f6f, 0xd5b);
  }
  iVar1 = *param_2;
  do {
    iVar3 = iVar1;
    iVar1 = IroUtil_FindNextUse(iVar3);
  } while (iVar1 != 0);
  iVar1 = iVar4;
  if ((iVar3 == 0) || ((*(uint *)(iVar3 + 2) & 2) != 0)) {
    CError_Internal(s_IroExprRegeneration_c_006b9f6f, 0xd65);
  }
  for (; iVar1 != iVar3 && (iVar1 != 0); iVar1 = *(int *)(iVar1 + 0x3e)) {
  }
  iVar2 = iVar3;
  if (iVar1 != 0) {
    return iVar4;
  }
  for (; iVar2 != iVar4 && (iVar2 != 0); iVar2 = *(int *)(iVar2 + 0x3e)) {
  }
  if (iVar2 == 0) {
    CError_Internal(s_IroExprRegeneration_c_006b9f6f, 0xd70);
  }
  iVar1 = *param_2;
  *param_1 = iVar1;
  *param_2 = iVar1;
  return iVar3;
}

/* Native 0x6078f0, 298 bytes. */
void NewDualOperationRTCall(uint param_1, int param_2, uint param_3, int param_4,
                 uint param_5, uint param_6)
{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  puVar2 = (uint *)CompilerTools_AllocatePoolMemory(0x10);
  uVar3 = FUN_005acf30(param_3, param_1);
  iVar6 = 1;
  *puVar2 = uVar3;
  if (param_4 != 0) {
    uVar3 = FUN_005acf30(param_4, param_1);
    puVar2[1] = uVar3;
    iVar6 = 2;
  }
  iVar4 = FUN_005acdf0(param_5);
  puVar2[iVar6] = iVar4;
  puVar1 = (uint *)(*(int *)(iVar4 + 0x2a) + 2);
  *puVar1 = *puVar1 | 6;
  *(uint *)(puVar2[iVar6] + 2) = *(uint *)(puVar2[iVar6] + 2) | 6;
  FUN_005ad220(puVar2[iVar6], param_1);
  iVar4 = iVar6 + 1;
  iVar5 = FUN_005acdf0(param_6);
  puVar2[iVar4] = iVar5;
  puVar1 = (uint *)(*(int *)(iVar5 + 0x2a) + 2);
  *puVar1 = *puVar1 | 6;
  *(uint *)(puVar2[iVar4] + 2) = *(uint *)(puVar2[iVar4] + 2) | 6;
  FUN_005ad220(puVar2[iVar4], param_1);
  iVar4 = FUN_005bd630(1);
  *(byte *)(iVar4 + 1) = 0x3b;
  uVar3 = FUN_00521c20(param_2, 1);
  *(uint *)(iVar4 + 0x2a) = uVar3;
  *(uint *)(iVar4 + 0x12) = *(uint *)(*(int *)(param_2 + 0x10) + 0xe);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 2;
  FUN_005ad220(iVar4, param_1);
  iVar5 = FUN_005bd630(7);
  *(uint *)(iVar5 + 6) = 0;
  *(byte *)(iVar5 + 0x2a) = 0;
  *(short *)(iVar5 + 0x2c) = (short)iVar6 + 2;
  *(uint **)(iVar5 + 0x2e) = puVar2;
  *(int *)(iVar5 + 0x32) = iVar4;
  *(uint *)(iVar5 + 0x36) = *(uint *)(param_2 + 0x10);
  *(uint *)(iVar5 + 0x12) = *(uint *)(iVar4 + 0x12);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar5 + 10) = DAT_00710998;
  FUN_005ad220(iVar5, param_1);
  return;
}

/* Native 0x607a20, 92 bytes. */
void GenerateCondAssignments(void)
{
  char *pcVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  iVar5 = DAT_00710990;
  while ((iVar5 != 0 && (pcVar1 = *(char **)(iVar5 + 0x14), pcVar1 != (char *)0x0))) {
    bVar3 = false;
    if ((*(short *)(iVar5 + 2) == 2) && (pcVar1 != (char *)0x0)) {
      bVar2 = true;
      if ((*pcVar1 != '\n') && (*pcVar1 != '\v')) {
        bVar2 = false;
      }
      if (bVar2) {
        bVar3 = true;
      }
    }
    if (bVar3) {
      cVar4 = GeneratePossibleCondAss((int)(iVar5));
      if (cVar4 == '\0') {
        iVar5 = *(int *)(iVar5 + 0x30);
      }
    }
    else {
      iVar5 = *(int *)(iVar5 + 0x30);
    }
  }
  FUN_005a9d80();
  return;
}

/* Native 0x607a80, 2571 bytes. */
byte GeneratePossibleCondAss(int param_1)
{
  LinearRange prepared;
  uint *puVar1;
  ushort *puVar2;
  char cVar3;
  bool bVar4;
  byte *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  char *pcVar12;
  char *pcVar13;

  char local_2e;
  char local_2d;
  int iStack_2c;
  uint uStack_28;
  int local_24;
  char local_1e;
  char local_1d;
  uint local_1c;
  int local_18;
  char *local_14;
  if ((param_1 != 0) && (*(short *)(param_1 + 2) == 2) &&
     (pcVar11 = *(char **)(param_1 + 0x14), pcVar11 != (char *)0x0)) {
    if ((*pcVar11 == '\n') || (*pcVar11 == '\v')) {
      local_1c = *(uint *)(pcVar11 + 0xe);
      puVar2 = *(ushort **)(param_1 + 4);
      iVar10 = *(int *)(DAT_00710b54 + (uint)*puVar2 * 4);
      if ((iVar10 == 0) || (pcVar13 = *(char **)(iVar10 + 0x10), pcVar13 == (char *)0x0) ||
         (*pcVar13 != '\r' || (*(int *)(pcVar13 + 0x2a) != *(int *)(pcVar11 + 0x2a)))) {
        iVar9 = *(int *)(DAT_00710b54 + (uint)puVar2[1] * 4);
        if ((iVar9 == 0) || (pcVar13 = *(char **)(iVar9 + 0x10), pcVar13 == (char *)0x0) ||
           (*pcVar13 != '\r') || (*(int *)(pcVar13 + 0x2a) != *(int *)(pcVar11 + 0x2a))) {
          return 0;
        }
      }
      else {
        iVar9 = iVar10;
        iVar10 = *(int *)(DAT_00710b54 + (uint)puVar2[1] * 4);
      }
      if ((iVar10 != 0) && (*(short *)(iVar10 + 8) == 1) && (*(short *)(iVar10 + 2) == 1)) {
        if (*(int *)(*(int *)(iVar10 + 0x14) + 0x3e) == *(int *)(iVar9 + 0x10)) {
          iVar8 = *(int *)(DAT_00710b54 + (uint)**(ushort **)(iVar10 + 4) * 4);
          if (iVar8 == iVar9) {
            local_1e = '\0';
          }
          else {
            if ((*(short *)(iVar9 + 8) != 1) || (*(short *)(iVar9 + 2) != 1) ||
               (**(ushort **)(iVar10 + 4) != **(ushort **)(iVar9 + 4) ||
               (iVar8 == 0 || (*(int *)(*(int *)(iVar9 + 0x14) + 0x3e) != *(int *)(iVar8 + 0x10)))))
            {
              return 0;
            }
            local_1e = '\x01';
            local_24 = iVar8;
          }
          pcVar11 = (char *)0x0;
          if (*(int *)(iVar10 + 0x14) != 0) {
            for (pcVar13 = *(char **)(iVar10 + 0x10); pcVar13 != (char *)0x0 &&
                (pcVar13 != *(char **)(*(int *)(iVar10 + 0x14) + 0x3e));
                pcVar13 = *(char **)(pcVar13 + 0x3e)) {
              cVar3 = FUN_005b07a0(pcVar13);
              if (((cVar3 == '\0') ||
                  ((*(uint *)(pcVar13 + 2) & 2) != 0 || (pcVar12 = pcVar13, pcVar11 != (char *)0x0))
                  ) && (cVar3 = *pcVar13, pcVar12 = pcVar11, cVar3 != '\0') &&
                 (cVar3 != '\r' && (cVar3 != '\b') && ((*(uint *)(pcVar13 + 2) & 2) == 0))) {
                return 0;
              }
              pcVar11 = pcVar12;
            }
          }
          if ((pcVar11 == (char *)0x0) ||
             (pcVar11[1] != '\x1e' && (cVar3 = FUN_005a9ee0(pcVar11), cVar3 == '\0')) ||
             (pcVar13 = *(char **)(pcVar11 + 0x2a), pcVar13 == (char *)0x0 ||
             (*pcVar13 != '\x02' || (pcVar13[1] != '\x04') ||
             (pcVar13 = *(char **)(pcVar13 + 0x2a), pcVar13 == (char *)0x0 ||
             (*pcVar13 != '\x01' || (pcVar13 = *(char **)(pcVar13 + 0x2a), pcVar13 == (char *)0x0)
             || (*pcVar13 != ';'))) ||
             (*(char **)(pcVar13 + 4) == (char *)0x0 || (**(char **)(pcVar13 + 4) != '\f')))) ||
             (*(int *)(pcVar13 + 0x10) == 0)) {
            return 0;
          }
          uVar7 = *(uint *)(pcVar11 + 0xe);
          if ((local_1c != uVar7) &&
             (local_1c == 0 || (uVar7 == 0) ||
             (cVar3 = FUN_005afcd0(local_1c, uVar7), cVar3 == '\0'))) {
            return 0;
          }
          if (local_1e != '\0') {
            local_14 = (char *)0x0;
            if (*(int *)(iVar9 + 0x14) != 0) {
              for (pcVar13 = *(char **)(iVar9 + 0x10); pcVar13 != (char *)0x0 &&
                  (pcVar13 != *(char **)(*(int *)(iVar9 + 0x14) + 0x3e));
                  pcVar13 = *(char **)(pcVar13 + 0x3e)) {
                cVar3 = FUN_005b07a0(pcVar13);
                if (((cVar3 == '\0') ||
                    ((*(uint *)(pcVar13 + 2) & 2) != 0 ||
                    (pcVar12 = pcVar13, local_14 != (char *)0x0))) &&
                   (cVar3 = *pcVar13, pcVar12 = local_14, cVar3 != '\0' &&
                   (cVar3 != '\r' && (cVar3 != '\b') && ((*(uint *)(pcVar13 + 2) & 2) == 0)))) {
                  return 0;
                }
                local_14 = pcVar12;
              }
            }
            if ((local_14 == (char *)0x0) ||
               (local_14[1] != '\x1e' && (cVar3 = FUN_005a9ee0(local_14), cVar3 == '\0')) ||
               (pcVar13 = *(char **)(local_14 + 0x2a), pcVar13 == (char *)0x0) ||
               (*pcVar13 != '\x02' || (pcVar13[1] != '\x04') ||
               (pcVar13 = *(char **)(pcVar13 + 0x2a), pcVar13 == (char *)0x0 ||
               (*pcVar13 != '\x01' || (pcVar13 = *(char **)(pcVar13 + 0x2a), pcVar13 == (char *)0x0)
               || (*pcVar13 != ';') ||
               (*(char **)(pcVar13 + 4) == (char *)0x0 || (**(char **)(pcVar13 + 4) != '\f')) ||
               (*(int *)(pcVar13 + 0x10) == 0))))) {
              return 0;
            }
            uVar7 = *(uint *)(local_14 + 0xe);
            if ((local_1c != uVar7) &&
               (local_1c == 0 || (uVar7 == 0) ||
               (cVar3 = FUN_005afcd0(local_1c, uVar7), cVar3 == '\0'))) {
              return 0;
            }
            local_2e = FUN_005b04a0(*(uint *)(pcVar11 + 0x2a),
                                    *(uint *)(local_14 + 0x2a));
          }
          local_2d = **(char **)(param_1 + 0x14) == '\n';
          local_18 = *(int *)(*(char **)(param_1 + 0x14) + 0x2e);
          local_1d = '\0';
          if ((local_1e != '\0') && (DAT_0070f234 != '\0') && (PTR_FUN_006ac972 != (code *)0x0)
             && (cVar3 = (*(code *)PTR_FUN_006ac972)(local_18), cVar3 != '\0')) {
            local_1d = '\x01';
          }
          if (local_1d != '\0') {
            FUN_005f6b80(local_18, 0, 1, 1);
            local_1d = DAT_007260c2 == '\0';
          }
          if (local_1e != '\0') {
            if ((DAT_0070f249 == '\0') || (local_2e == '\0')) {
              iVar8 = FUN_005ac1e0(local_18);
              if ((iVar8 == 0) && (cVar3 = FUN_005ac320(local_18), cVar3 == '\0')) {
                FUN_005f6b80(local_18, 0, 0, 1);
                FUN_005bf760(DAT_00710358);
                FUN_005ae350(pcVar11, &LAB_005f6240, 0);
                local_1c = *DAT_00710358;
                if (*DAT_0071015c < local_1c) {
                  local_1c = *DAT_0071015c;
                }
                uVar7 = 0;
                if (local_1c != 0) {
                  do {
                    if ((DAT_00710358[uVar7 + 1] & DAT_0071015c[uVar7 + 1]) != 0) {
                      bVar4 = true;
                      goto LAB_0060813e;
                    }
                    uVar7 = uVar7 + 1;
                  } while (uVar7 < local_1c);
                }
                bVar4 = false;
LAB_0060813e:;
                if (bVar4) {
                  local_1d = '\x01';
                }
              }
              else {
                local_1d = '\x01';
              }
            }
            else {
              local_1d = '\0';
            }
            if ((local_1d != '\0') && (DAT_0070f234 == '\0')) {
              return 0;
            }
          }
          if (local_1d != '\0') {
            FUN_005ad280(&prepared.first);
            uVar6 = FUN_005b7d30(*(uint *)(local_18 + 0x12));
            uStack_28 = create_temp_object(uVar6);
            FUN_005b53d0(uStack_28, 1, 1);
            iVar8 = FUN_005bd630(3);
            uVar6 = FUN_005acdf0(uStack_28);
            *(uint *)(iVar8 + 0x2a) = uVar6;
            FUN_005ad220(*(uint *)(*(int *)(iVar8 + 0x2a) + 0x2a), &prepared.first);
            uVar6 = FUN_005b7d30(*(uint *)(local_18 + 0x12));
            *(uint *)(iVar8 + 0x12) = uVar6;
            *(byte *)(iVar8 + 1) = 0x1e;
            DAT_00710998 = DAT_00710998 + 1;
            *(int *)(iVar8 + 10) = DAT_00710998;
            puVar1 = (uint *)(*(int *)(iVar8 + 0x2a) + 2);
            *puVar1 = *puVar1 | 0x26;
            puVar1 = (uint *)(*(int *)(*(int *)(iVar8 + 0x2a) + 0x2a) + 2);
            *puVar1 = *puVar1 | 0x24;
            *(int *)(iVar8 + 0x2e) = local_18;
            FUN_005ad220(iVar8, &prepared.first);
            FUN_005ad400(prepared.first, prepared.last, local_18);
          }
          iStack_2c = *(int *)(pcVar11 + 0x2a);
          local_1c = *(uint *)(pcVar11 + 0x2e);
          **(byte **)(param_1 + 0x14) = 0;
          *(uint *)(*(int *)(param_1 + 0x14) + 0x1a) = 0;
          if (**(char **)(iVar10 + 0x14) == '\b') {
            **(char **)(iVar10 + 0x14) = '\0';
            *(uint *)(*(int *)(iVar10 + 0x14) + 0x1a) = 0;
          }
          if ((local_1e != '\0') || (*(short *)(iVar9 + 8) == 2)) {
            **(byte **)(iVar9 + 0x10) = 0;
            *(uint *)(*(int *)(iVar9 + 0x10) + 0x1a) = 0;
          }
          if ((DAT_0070f249 == '\0') || (local_1e == '\0') || (local_2e == '\0')) {
            *pcVar11 = '\x04';
            pcVar11[1] = 'X';
            if (local_1d != '\0') {
              FUN_005ad280(&prepared.first);
              local_18 = FUN_005acdf0(uStack_28);
              FUN_005ad220(*(uint *)(local_18 + 0x2a), &prepared.first);
              FUN_005ad440(prepared.first, prepared.last, pcVar11);
            }
            if ((local_1e != '\0') && (local_1d == '\0')) {
              FUN_005ad280(&prepared.first);
              FUN_005acf30(local_18, &prepared.first);
              FUN_005ad440(prepared.first, prepared.last, local_14);
            }
            if (local_2d != '\0') {
              local_18 = FUN_005af0d0(local_18, 1);
            }
            *(uint *)(local_18 + 2) = *(uint *)(local_18 + 2) | 2;
            *(int *)(pcVar11 + 0x2a) = local_18;
            *(int *)(pcVar11 + 0x2e) = iStack_2c;
            *(uint *)(pcVar11 + 0x32) = local_1c;
            if (local_1e != '\0') {
              iStack_2c = *(int *)(local_14 + 0x2a);
              local_18 = *(int *)(local_14 + 0x2e);
              if (**(char **)(iVar9 + 0x14) == '\b') {
                **(char **)(iVar9 + 0x14) = '\0';
                *(uint *)(*(int *)(iVar9 + 0x14) + 0x1a) = 0;
              }
              if (*(short *)(local_24 + 8) == 2) {
                **(byte **)(local_24 + 0x10) = 0;
                *(uint *)(*(int *)(local_24 + 0x10) + 0x1a) = 0;
              }
              *local_14 = '\x04';
              local_14[1] = 'X';
              if (local_1d != '\0') {
                FUN_005ad280(&prepared.first);
                iVar8 = FUN_005acdf0(uStack_28);
                FUN_005ad220(*(uint *)(iVar8 + 0x2a), &prepared.first);
                FUN_005ad440(prepared.first, prepared.last, local_14);
                prepared.last = iVar8;
              }
              if (local_2d == '\0') {
                prepared.last = FUN_005af0d0(prepared.last, 1);
              }
              *(uint *)(prepared.last + 2) = *(uint *)(prepared.last + 2) | 2;
              *(int *)(local_14 + 0x2a) = prepared.last;
              *(int *)(local_14 + 0x2e) = iStack_2c;
              *(int *)(local_14 + 0x32) = local_18;
            }
          }
          else {
            if (**(char **)(iVar9 + 0x14) == '\b') {
              **(char **)(iVar9 + 0x14) = '\0';
              *(uint *)(*(int *)(iVar9 + 0x14) + 0x1a) = 0;
            }
            if (*(short *)(local_24 + 8) == 2) {
              **(byte **)(local_24 + 0x10) = 0;
              *(uint *)(*(int *)(local_24 + 0x10) + 0x1a) = 0;
            }
            puVar5 = (byte *)FUN_005bd630(4);
            iVar8 = 0;
            do {
              *(uint *)(puVar5 + iVar8) = *(uint *)(pcVar11 + iVar8);
              *(uint *)(puVar5 + iVar8 + 4) = *(uint *)(pcVar11 + iVar8 + 4);
              *(uint *)(puVar5 + iVar8 + 8) = *(uint *)(pcVar11 + iVar8 + 8);
              *(uint *)(puVar5 + iVar8 + 0xc) = *(uint *)(pcVar11 + iVar8 + 0xc);
              iVar8 = iVar8 + 0x10;
            } while (iVar8 < 0x40);
            *(ushort *)(puVar5 + 0x40) = *(ushort *)(pcVar11 + 0x40);
            *puVar5 = 4;
            puVar5[1] = 0x38;
            *(int *)(puVar5 + 10) = DAT_00710998;
            DAT_00710998 = DAT_00710998 + 1;
            uVar6 = FUN_005b7d30(*(uint *)(iStack_2c + 0x12));
            *(uint *)(puVar5 + 0x12) = uVar6;
            *(uint *)(puVar5 + 2) = *(uint *)(puVar5 + 2) | 2;
            if (local_1d != '\0') {
              FUN_005ad280(&prepared.first);
              local_18 = FUN_005acdf0(uStack_28);
              FUN_005ad220(*(uint *)(local_18 + 0x2a), &prepared.first);
              FUN_005ad440(prepared.first, prepared.last, local_14);
            }
            *(uint *)(local_18 + 2) = *(uint *)(local_18 + 2) | 2;
            *(int *)(puVar5 + 0x2a) = local_18;
            if (local_2d == '\0') {
              *(uint *)(puVar5 + 0x2e) = local_1c;
              *(uint *)(puVar5 + 0x32) = *(uint *)(local_14 + 0x2e);
            }
            else {
              *(uint *)(puVar5 + 0x2e) = *(uint *)(local_14 + 0x2e);
              *(uint *)(puVar5 + 0x32) = local_1c;
            }
            *pcVar11 = '\0';
            pcVar11[0x1a] = '\0';
            pcVar11[0x1b] = '\0';
            pcVar11[0x1c] = '\0';
            pcVar11[0x1d] = '\0';
            FUN_005ae7b0(*(uint *)(pcVar11 + 0x2a));
            FUN_005ad440(puVar5, puVar5, local_14);
            *(byte **)(local_14 + 0x2e) = puVar5;
          }
          iVar8 = FUN_005bdc90(param_1, iVar10);
          if (iVar8 != 0) {
            iVar10 = param_1;
          }
          if (((local_1e != '\0') || (*(short *)(iVar9 + 8) == 1)) &&
             (iVar8 = FUN_005bdc90(iVar10, iVar9), iVar8 != 0)) {
            iVar9 = iVar10;
          }
          if ((local_1e != '\0') && (*(short *)(local_24 + 8) == 1)) {
            FUN_005bdc90(iVar9, local_24);
          }
          return 1;
        }
      }
      return 0;
    }
  }
  return 0;
}

/* Native 0x608490, 400 bytes. */
void RebuildLogicalExpressions(void)
{
  char *pcVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  char *pcVar8;
  int iVar9;
  do {
    bVar6 = false;
    for (iVar9 = DAT_00710990; iVar9 != 0 && (*(int *)(iVar9 + 0x14) != 0);
        iVar9 = *(int *)(iVar9 + 0x30)) {
      for (pcVar8 = *(char **)(iVar9 + 0x10); pcVar8 != (char *)0x0 &&
          (pcVar1 = *(char **)(iVar9 + 0x14), pcVar8 != *(char **)(pcVar1 + 0x3e));
          pcVar8 = *(char **)(pcVar8 + 0x3e)) {
        bVar5 = false;
        bVar4 = false;
        if ((*(short *)(iVar9 + 2) == 2) && (pcVar1 != (char *)0x0)) {
          bVar3 = true;
          if ((*pcVar1 != '\n') && (*pcVar1 != '\v')) {
            bVar3 = false;
          }
          if (bVar3) {
            bVar4 = true;
          }
        }
        if ((bVar4) && (*pcVar8 == '\x03') && (pcVar8[1] == '\x1e') &&
           (pcVar1 = *(char **)(pcVar8 + 0x2a), pcVar1 != (char *)0x0 &&
           (iVar2 = *(int *)(pcVar8 + 0x2e), iVar2 != 0))) {
          cVar7 = FUN_005b07f0(iVar2);
          if (cVar7 != '\0') {
            cVar7 = CInt64_Equal(*(uint *)(*(int *)(iVar2 + 0x2a) + 0x10),
                                 *(uint *)(*(int *)(iVar2 + 0x2a) + 0x14), DAT_00699b76,
                                 DAT_00699b7a);
            if (cVar7 == '\0') {
              cVar7 = CInt64_Equal(*(uint *)(*(int *)(iVar2 + 0x2a) + 0x10),
                                   *(uint *)(*(int *)(iVar2 + 0x2a) + 0x14), DAT_00704908,
                                   DAT_0070490c);
              if (cVar7 == '\0') goto LAB_006085d8;
            }
            if ((*pcVar1 == '\x02') && (pcVar1[1] == '\x04') &&
               (*(int *)(pcVar1 + 0x2a) != 0 &&
               (**(char **)(*(int *)(pcVar1 + 0x2a) + 0x12) == '\f' &&
               (**(char **)(pcVar1 + 0x2a) == '\x01') &&
               (*(int *)(*(int *)(pcVar1 + 0x2a) + 0x2a) != 0) &&
               (**(char **)(*(int *)(pcVar1 + 0x2a) + 0x2a) == ';' &&
               (*(int *)(*(int *)(*(int *)(pcVar1 + 0x2a) + 0x2a) + 0x10) != 0)))) &&
               (*(char *)(*(int *)(*(int *)(*(int *)(pcVar1 + 0x2a) + 0x2a) + 0x10) + 2) == '\x01'))
            {
              bVar5 = true;
            }
          }
        }
LAB_006085d8:;
        if (bVar5) {
          cVar7 = RebuildPossibleLogicalExpression((uint)(iVar9), (uint)(pcVar8));
          if (cVar7 != '\0') {
            bVar6 = true;
          }
        }
      }
    }
    if (!bVar6) {
      FUN_005a9d80();
      return;
    }
  } while( true );
}

/* Native 0x608620, 3902 bytes. */
byte RebuildPossibleLogicalExpression(uint param_1, uint param_2)
{
  ushort uVar1;
  char *pcVar2;
  ushort *puVar3;
  uint *puVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint *puVar10;
  byte uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  char local_55;
  int local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint *local_44;
  int local_40;
  uint *local_3c;
  char *local_38;
  char *local_34;
  char local_2d;
  uint *local_2c;
  uint *local_28;
  uint *local_24;
  uint *local_20;
  char *local_1c;
  int local_18;
  char *local_14;
  local_18 = *(int *)(*(int *)(*(int *)(param_2 + 0x2a) + 0x2a) + 0x2a);
  if (*(int *)(*(int *)(local_18 + 0x10) + 0x20) == 0) {
    return 0;
  }
  iVar15 = *(int *)(*(int *)(param_2 + 0x2e) + 0x2a);
  cVar5 = CInt64_Equal(*(uint *)(iVar15 + 0x10), *(uint *)(iVar15 + 0x14), DAT_00704908,
                       DAT_0070490c);
  if (cVar5 == '\0') {
    local_55 = '\n';
    uVar14 = DAT_00704908;
    uVar16 = DAT_0070490c;
  }
  else {
    local_55 = '\v';
    uVar14 = DAT_00699b76;
    uVar16 = DAT_00699b7a;
  }
  local_28 = (uint *)0x0;
  local_2c = (uint *)0x0;
  iVar15 = *(int *)(*(int *)(local_18 + 0x10) + 0x20);
  puVar10 = *(uint **)(iVar15 + 0x14);
  while ((puVar10 != (uint *)0x0 && (local_2c == (uint *)0x0))) {
    if ((puVar10[6] != 0) && (puVar10[2] == param_2)) {
      local_2c = puVar10;
    }
    puVar10 = (uint *)puVar10[5];
  }
  if (local_2c != (uint *)0x0) {
    for (iVar15 = *(int *)(iVar15 + 0x18); iVar15 != 0; iVar15 = *(int *)(iVar15 + 0x14)) {
      if (*(int *)(iVar15 + 0x1c) == 2) {
        bVar6 = false;
        uVar12 = *local_2c >> 5;
        if ((uVar12 < **(uint **)(iVar15 + 0x18)) &&
           (((*(uint **)(iVar15 + 0x18))[uVar12 + 1] & 1 << ((byte)*local_2c & 0x1f)) != 0)) {
          bVar6 = true;
        }
        if (bVar6) {
          if (local_28 == (uint *)0x0) {
            local_28 = *(uint **)(iVar15 + 4);
          }
          else {
            uVar1 = (ushort)**(uint **)(iVar15 + 4);
            bVar6 = false;
            uVar12 = (uint)(uVar1 >> 5);
            if ((uVar12 < *(uint *)local_28[0xb]) &&
               ((((uint *)local_28[0xb])[uVar12 + 1] & 1 << ((byte)uVar1 & 0x1f)) != 0)) {
              bVar6 = true;
            }
            if (bVar6) {
              local_28 = *(uint **)(iVar15 + 4);
            }
          }
        }
      }
    }
    if (local_28 != (uint *)0x0) {
      for (iVar15 = *(int *)(*(int *)(*(int *)(local_18 + 0x10) + 0x20) + 0x18); iVar15 != 0;
          iVar15 = *(int *)(iVar15 + 0x14)) {
        if ((*(uint **)(iVar15 + 4) != local_28) && (*(int *)(iVar15 + 0x1c) == 2)) {
          bVar6 = false;
          uVar12 = *local_2c >> 5;
          if ((uVar12 < **(uint **)(iVar15 + 0x18)) &&
             (((*(uint **)(iVar15 + 0x18))[uVar12 + 1] & 1 << ((byte)*local_2c & 0x1f)) != 0)) {
            bVar6 = true;
          }
          if (bVar6) {
            puVar10 = (uint *)(*(uint **)(iVar15 + 4))[0xb];
            bVar6 = false;
            uVar12 = (uint)(ushort)((ushort)*local_28 >> 5);
            if ((uVar12 < *puVar10) &&
               ((puVar10[uVar12 + 1] & 1 << ((byte)(ushort)*local_28 & 0x1f)) != 0)) {
              bVar6 = true;
            }
            if (!bVar6) {
              local_28 = (uint *)0x0;
              break;
            }
          }
        }
      }
    }
  }
  if ((local_28 == (uint *)0x0) || (pcVar2 = (char *)local_28[4], pcVar2 == (char *)0x0) ||
     (*pcVar2 != '\r') ||
     (local_20 = *(uint **)(pcVar2 + 0x2a), local_20 == (uint *)0x0 || ((ushort)local_28[2] != 3)))
  {
    return 0;
  }
  puVar3 = *(ushort **)((int)local_28 + 10);
  puVar10 = *(uint **)(DAT_00710b54 + (uint)*puVar3 * 4);
  local_24 = *(uint **)(DAT_00710b54 + (uint)puVar3[1] * 4);
  bVar6 = false;
  uVar12 = (uint)(ushort)((ushort)*local_24 >> 5);
  if ((uVar12 < *(uint *)puVar10[0xb]) &&
     ((((uint *)puVar10[0xb])[uVar12 + 1] & 1 << ((byte)(ushort)*local_24 & 0x1f)) != 0)) {
    bVar6 = true;
  }
  if (!bVar6) {
    bVar6 = false;
    uVar12 = (uint)(ushort)((ushort)*puVar10 >> 5);
    if ((uVar12 < *(uint *)local_24[0xb]) &&
       ((((uint *)local_24[0xb])[uVar12 + 1] & 1 << ((byte)(ushort)*puVar10 & 0x1f)) != 0)) {
      bVar6 = true;
    }
    local_24 = puVar10;
    if (!bVar6) {
      return 0;
    }
  }
  puVar10 = *(uint **)(DAT_00710b54 + (uint)puVar3[2] * 4);
  bVar6 = false;
  uVar12 = (uint)(ushort)((ushort)*puVar10 >> 5);
  if ((uVar12 < *(uint *)local_24[0xb]) &&
     ((((uint *)local_24[0xb])[uVar12 + 1] & 1 << ((byte)(ushort)*puVar10 & 0x1f)) != 0)) {
    bVar6 = true;
  }
  if (!bVar6) {
    bVar6 = false;
    uVar12 = (uint)(ushort)((ushort)*local_24 >> 5);
    if ((uVar12 < *(uint *)puVar10[0xb]) &&
       ((((uint *)puVar10[0xb])[uVar12 + 1] & 1 << ((byte)(ushort)*local_24 & 0x1f)) != 0)) {
      bVar6 = true;
    }
    puVar10 = local_24;
    if (!bVar6) {
      return 0;
    }
  }
  local_24 = puVar10;
  if ((local_24 == (uint *)0x0) || (local_38 = (char *)local_24[5], local_38 == (char *)0x0) ||
     (*local_38 != local_55) || ((uint *)*(int *)(local_38 + 0x2a) != local_20)) {
    return 0;
  }
  local_40 = *(int *)(local_38 + 0xe);
  cVar5 = FUN_005bd930(*(int *)(local_38 + 0x2a), &local_28, &local_44, uVar14, uVar16);
  if ((cVar5 != '\0') && (local_44 != (uint *)0x0) &&
     ((ushort)local_44[2] == 1 &&
     (local_20 = *(uint **)(DAT_00710b54 + (uint)**(ushort **)((int)local_44 + 10) * 4),
     local_20 != (uint *)0x0 && (local_34 = (char *)local_20[5], local_34 != (char *)0x0))) &&
     (*local_34 == local_55) && (*(int *)(local_34 + 0x2a) == *(int *)(local_38 + 0x2a))) {
    local_14 = (char *)0x0;
    local_1c = local_14;
    for (pcVar2 = (char *)local_44[4]; pcVar2 != *(char **)(local_44[5] + 0x3e);
        pcVar2 = *(char **)(pcVar2 + 0x3e)) {
      local_14 = local_1c;
      if ((*pcVar2 == '\x03') && (local_14 = local_1c, pcVar2[1] == '\x1e') &&
         (local_14 = local_1c, (*(uint *)(pcVar2 + 2) & 2) == 0)) {
        local_14 = pcVar2;
      }
      local_1c = local_14;
    }
    if ((local_1c != (char *)0x0) && (*local_1c == '\x03') &&
       (local_1c[1] == '\x1e' &&
       (pcVar2 = *(char **)(local_1c + 0x2a), pcVar2 != (char *)0x0 &&
       (iVar15 = *(int *)(local_1c + 0x2e), iVar15 != 0)) &&
       (local_14 = local_1c, cVar5 = FUN_005b07f0(iVar15), cVar5 != '\0')) &&
       ((cVar5 = CInt64_Equal(*(uint *)(*(int *)(iVar15 + 0x2a) + 0x10),
                              *(uint *)(*(int *)(iVar15 + 0x2a) + 0x14), DAT_00699b76,
                              DAT_00699b7a), cVar5 != '\0' ||
        (cVar5 = CInt64_Equal(*(uint *)(*(int *)(iVar15 + 0x2a) + 0x10),
                              *(uint *)(*(int *)(iVar15 + 0x2a) + 0x14), DAT_00704908,
                              DAT_0070490c), cVar5 != '\0')) && (*pcVar2 == '\x02') &&
       (pcVar2[1] == '\x04' && (*(int *)(pcVar2 + 0x2a) != 0)) &&
       (**(char **)(*(int *)(pcVar2 + 0x2a) + 0x12) == '\f') &&
       (**(char **)(pcVar2 + 0x2a) == '\x01' && (*(int *)(*(int *)(pcVar2 + 0x2a) + 0x2a) != 0) &&
       (**(char **)(*(int *)(pcVar2 + 0x2a) + 0x2a) == ';' &&
       (*(int *)(*(int *)(*(int *)(pcVar2 + 0x2a) + 0x2a) + 0x10) != 0 &&
       (*(char *)(*(int *)(*(int *)(*(int *)(pcVar2 + 0x2a) + 0x2a) + 0x10) + 2) == '\x01') &&
       (cVar5 = FUN_00455840(*(uint *)
                              (*(int *)(*(int *)(*(int *)(local_14 + 0x2a) + 0x2a) + 0x2a) + 0x10),
                             *(uint *)(local_18 + 0x10)), cVar5 != '\0')))) &&
       (cVar5 = CInt64_Equal(uVar14, uVar16,
                             *(uint *)(*(int *)(*(int *)(local_14 + 0x2e) + 0x2a) + 0x10),
                             *(uint *)(*(int *)(*(int *)(local_14 + 0x2e) + 0x2a) + 0x14)),
       cVar5 != '\0'))) {
      if ((*(int *)(local_14 + 0x12) == *(int *)(param_2 + 0x12)) ||
         (cVar5 = FUN_005b7e20(*(int *)(local_14 + 0x12), *(int *)(param_2 + 0x12)), cVar5 != '\0'))
      {
        iVar15 = *(int *)(local_34 + 0xe);
        if ((local_40 != iVar15) &&
           (local_40 == 0 || (iVar15 == 0) ||
           (cVar5 = FUN_005afcd0(local_40, iVar15), cVar5 == '\0'))) {
          return 0;
        }
        cVar5 = CheckForTopLevelExpressions((int)(param_1), (ushort *)(param_1), (int)(local_24), (char *)(*(uint *)(param_2 + 0x3e)), (char *)(local_38), (char)(1));
        if (cVar5 == '\0') {
          uVar12 = local_24[0xc];
          cVar5 = CheckForTopLevelExpressions((int)(uVar12), (ushort *)(uVar12), (int)(local_20), (char *)(*(uint *)(uVar12 + 0x10)), (char *)(local_34), (char)(1));
          if ((cVar5 == '\0') &&
             (cVar5 = CheckForTopLevelExpressions((int)(local_20[0xc]), (ushort *)(local_20[0xc]), (int)(local_44), (char *)(*(uint *)(local_34 + 0x3e)), (char *)(local_14), (char)(1)), cVar5 == '\0') &&
             (cVar5 = CheckForTopLevelExpressions((int)(local_44), (ushort *)(local_44), (int)(local_44), (char *)(*(uint *)(local_14 + 0x3e)), (char *)(local_28[4]), (char)(1)), cVar5 == '\0')) {
            local_54 = 0;
            iVar15 = 0;
            local_2d = '\0';
            iVar7 = *(int *)(*(int *)(local_18 + 0x10) + 0x20);
            if ((iVar7 == 0) || (iVar13 = *(int *)(iVar7 + 0x18), iVar13 == 0) ||
               (puVar10 = *(uint **)(iVar7 + 0x14), puVar10 == (uint *)0x0)) {
              local_18 = 0;
            }
            else {
              local_3c = (uint *)0x0;
              local_2c = (uint *)0x0;
              while ((puVar10 != (uint *)0x0 &&
                     (local_2c == (uint *)0x0 || (local_3c == (uint *)0x0)))) {
                if (((puVar10[6] == 0) || (puVar4 = puVar10, puVar10[2] != param_2)) &&
                   (puVar4 = local_2c, puVar10[6] != 0 && ((char *)puVar10[2] == local_1c))) {
                  local_3c = puVar10;
                }
                local_2c = puVar4;
                puVar10 = (uint *)puVar10[5];
              }
              if ((local_2c == (uint *)0x0) || (local_3c == (uint *)0x0)) {
                local_18 = 0;
              }
              else {
                for (; local_18 != 0 && (iVar13 != 0); iVar13 = *(int *)(iVar13 + 0x14)) {
                  if (*(int *)(iVar13 + 0x1c) != 0) {
                    iVar15 = iVar15 + 1;
                    local_64 = *local_2c;
                    puVar10 = *(uint **)(iVar13 + 0x18);
                    local_50 = 0;
                    local_48 = *puVar10;
                    uVar12 = local_64 >> 5;
                    if ((uVar12 < local_48) &&
                       ((puVar10[uVar12 + 1] & 1 << ((byte)local_64 & 0x1f)) != 0)) {
                      local_50 = 1;
                    }
                    local_4c = local_64;
                    if ((char)local_50 != '\0') {
                      local_60 = *local_3c;
                      local_50 = 0;
                      if ((local_60 >> 5 < local_48) &&
                         ((puVar10[(local_60 >> 5) + 1] & 1 << ((byte)local_60 & 0x1f)) != 0)) {
                        local_50 = 1;
                      }
                      if ((char)local_50 != '\0') {
                        for (uVar12 = 0; local_18 != 0 && (uVar12 < local_48); uVar12 = uVar12 + 1)
                        {
                          if ((uVar12 != local_64) && (uVar12 != local_60)) {
                            bVar6 = false;
                            if ((uVar12 >> 5 < local_48) &&
                               ((puVar10[(uVar12 >> 5) + 1] & 1 << ((byte)uVar12 & 0x1f)) != 0)) {
                              bVar6 = true;
                            }
                            if (bVar6) {
                              local_18 = 0;
                            }
                          }
                        }
                        if (local_18 != 0) {
                          puVar10 = *(uint **)(*(int *)(iVar13 + 4) + 0x2c);
                          bVar6 = false;
                          uVar12 = (uint)(ushort)((ushort)*local_28 >> 5);
                          if ((uVar12 < *puVar10) &&
                             ((puVar10[uVar12 + 1] & 1 << ((byte)(ushort)*local_28 & 0x1f)) != 0)) {
                            bVar6 = true;
                          }
                          if (!bVar6) {
                            local_18 = 0;
                          }
                        }
                        if (local_18 != 0) {
                          cVar5 = RewriteUse((int)(iVar13), (int)(local_18), (int)(local_1c), (char)(0));
                          if (cVar5 == '\0') {
                            local_18 = 0;
                          }
                          else {
                            local_54 = local_54 + 1;
                          }
                        }
                        if (local_18 != 0) {
                          if (local_2d == '\0') {
                            local_2d = fn_0060b8e0((int)(local_28), (int)(*(uint *)(iVar13 + 4)), (int)(*(uint *)(iVar13 + 8)), (char)(1));
                          }
                          if ((local_2d == '\0') &&
                             (cVar5 = FUN_005ac320(*(uint *)(local_38 + 0x2e)), cVar5 != '\0'
                             || (cVar5 = FUN_005ac320(*(uint *)(local_34 + 0x2e)),
                                cVar5 != '\0'))) {
                            local_2d = HasSideEffectsBeforeUse((int)(local_28), (int)(*(uint *)(iVar13 + 4)), (int)(*(uint *)(iVar13 + 8)), (char)(1));
                          }
                          if ((local_2d == '\0') &&
                             (iVar7 = FUN_005ac1e0(*(uint *)(local_38 + 0x2e)), iVar7 != 0 ||
                             (iVar7 = FUN_005ac1e0(*(uint *)(local_34 + 0x2e)), iVar7 != 0)))
                          {
                            iVar7 = *(int *)(iVar13 + 8);
                            iVar8 = IroUtil_FindNextUse(iVar7);
                            if (iVar8 != 0) {
                              FUN_005bfae0(&local_5c, DAT_00710084 + 1);
                              FUN_005bfae0(&local_68, DAT_00710084 + 1);
                              FUN_005bf760(DAT_00710358);
                              FUN_005ae350(*(uint *)(local_38 + 0x2e), &LAB_005f6240, 0);
                              FUN_005ae350(*(uint *)(local_34 + 0x2e), &LAB_005f6240, 0);
                              FUN_005bf940(DAT_00710358, local_5c);
                              while ((iVar8 != 0 && (local_2d == '\0'))) {
                                FUN_005abcd0(iVar8, iVar7, local_5c, local_68, &local_2d);
                                iVar9 = IroUtil_FindNextUse(iVar8);
                                iVar7 = iVar8;
                                iVar8 = iVar9;
                              }
                            }
                            if (local_2d == '\0') {
                              local_2d = UsesAKilledVarBeforeUse((int)(local_28), (int)(*(uint *)(iVar13 + 4)), (char *)(*(uint *)(iVar13 + 8)), (uint *)(local_5c), (char)(1));
                            }
                          }
                        }
                        goto LAB_00609500;
                      }
                    }
                    if ((local_48 <= uVar12) ||
                       ((puVar10[uVar12 + 1] & 1 << ((byte)local_64 & 0x1f)) == 0)) {
                      local_4c = 0;
                      uVar12 = *local_3c >> 5;
                      if ((uVar12 < local_48) &&
                         ((puVar10[uVar12 + 1] & 1 << ((byte)*local_3c & 0x1f)) != 0)) {
                        local_4c = 1;
                      }
                      if ((char)local_4c == '\0') goto LAB_00609500;
                    }
                    local_18 = 0;
                  }
LAB_00609500:;
                }
              }
            }
            if (local_18 == 0) {
              return 0;
            }
            if ((local_54 == 1) && (local_2d == '\0') &&
               (iVar7 = *(int *)(*(int *)(local_18 + 0x10) + 0x20), *(char *)(iVar7 + 0xd) == '\0'))
            {
              for (iVar7 = *(int *)(iVar7 + 0x18); iVar7 != 0; iVar7 = *(int *)(iVar7 + 0x14)) {
                if (*(int *)(iVar7 + 0x1c) != 0) {
                  puVar10 = *(uint **)(iVar7 + 0x18);
                  bVar6 = false;
                  uVar12 = *local_2c >> 5;
                  if ((uVar12 < *puVar10) &&
                     ((puVar10[uVar12 + 1] & 1 << ((byte)*local_2c & 0x1f)) != 0)) {
                    bVar6 = true;
                  }
                  if (bVar6) {
                    bVar6 = false;
                    uVar12 = *local_3c >> 5;
                    if ((uVar12 < *puVar10) &&
                       ((puVar10[uVar12 + 1] & 1 << ((byte)*local_3c & 0x1f)) != 0)) {
                      bVar6 = true;
                    }
                    if ((bVar6) &&
                       (cVar5 = RewriteUse((int)(iVar7), (int)(local_18), (int)(local_1c), (char)(0)), cVar5 != '\0') &&
                       (iVar13 = *(int *)(*(int *)(iVar7 + 8) + 0xe), local_40 != iVar13) &&
                       (local_40 == 0 || (iVar13 == 0) ||
                       (cVar5 = FUN_005afcd0(local_40, iVar13), cVar5 == '\0'))) {
                      local_2d = '\x01';
                    }
                  }
                }
              }
            }
            *local_38 = '\0';
            *local_34 = '\0';
            local_38[0x1a] = '\0';
            local_38[0x1b] = '\0';
            local_38[0x1c] = '\0';
            local_38[0x1d] = '\0';
            local_34[0x1a] = '\0';
            local_34[0x1b] = '\0';
            local_34[0x1c] = '\0';
            local_34[0x1d] = '\0';
            FUN_005ae7b0(param_2);
            local_1c = (char *)FUN_005bd630(3);
            iVar7 = 0;
            do {
              *(uint *)(iVar7 + (int)local_1c) = *(uint *)(local_14 + iVar7);
              *(uint *)(iVar7 + 4 + (int)local_1c) = *(uint *)(local_14 + iVar7 + 4);
              *(uint *)(iVar7 + 8 + (int)local_1c) = *(uint *)(local_14 + iVar7 + 8);
              *(uint *)(iVar7 + 0xc + (int)local_1c) = *(uint *)(local_14 + iVar7 + 0xc)
              ;
              iVar7 = iVar7 + 0x10;
            } while (iVar7 < 0x40);
            *(ushort *)((int)local_1c + 0x40) = *(ushort *)(local_14 + 0x40);
            if (local_55 == '\n') {
              uVar11 = 0x1d;
            }
            else {
              uVar11 = 0x1c;
            }
            *(byte *)((int)local_1c + 1) = uVar11;
            *(int *)((int)local_1c + 10) = DAT_00710998;
            DAT_00710998 = DAT_00710998 + 1;
            *(uint *)((int)local_1c + 0x2a) = *(uint *)(local_38 + 0x2e);
            *(uint *)((int)local_1c + 0x2e) = *(uint *)(local_34 + 0x2e);
            *(uint *)((int)local_1c + 2) = *(uint *)((int)local_1c + 2) | 2;
            FUN_005ad440(local_1c, local_1c, local_14);
            if ((local_54 == 1) && (local_2d == '\0') &&
               (iVar7 = *(int *)(*(int *)(local_18 + 0x10) + 0x20), *(char *)(iVar7 + 0xd) == '\0'))
            {
              for (iVar7 = *(int *)(iVar7 + 0x18); iVar7 != 0; iVar7 = *(int *)(iVar7 + 0x14)) {
                if (*(int *)(iVar7 + 0x1c) != 0) {
                  puVar10 = *(uint **)(iVar7 + 0x18);
                  bVar6 = false;
                  uVar12 = *local_2c >> 5;
                  if ((uVar12 < *puVar10) &&
                     ((puVar10[uVar12 + 1] & 1 << ((byte)*local_2c & 0x1f)) != 0)) {
                    bVar6 = true;
                  }
                  if (bVar6) {
                    bVar6 = false;
                    uVar12 = *local_3c >> 5;
                    if ((uVar12 < *puVar10) &&
                       ((puVar10[uVar12 + 1] & 1 << ((byte)*local_3c & 0x1f)) != 0)) {
                      bVar6 = true;
                    }
                    if (bVar6) {
                      RewriteUse((int)(iVar7), (int)(local_18), (int)(local_1c), (char)(1));
                    }
                  }
                }
              }
              if ((iVar15 == 1) &&
                 (iVar15 = *(int *)(*(int *)(local_18 + 0x10) + 0x40), iVar15 != 0)) {
                *(uint *)(iVar15 + 4) = 0;
                *(byte *)(*(int *)(*(int *)(local_18 + 0x10) + 0x40) + 9) = 0;
              }
              FUN_005ae7b0(local_14);
              local_2c[6] = 0;
              local_3c[6] = 0;
            }
            else {
              FUN_005ae7b0(*(uint *)(local_14 + 0x2e));
              *(char **)(local_14 + 0x2e) = local_1c;
              local_2c[6] = 0;
            }
            if (((ushort)local_20[2] == 1) &&
               (*(uint **)(DAT_00710b54 + (uint)**(ushort **)((int)local_20 + 10) * 4) == local_24)
               && (iVar15 = FUN_005bdc90(local_24, local_20), iVar15 != 0)) {
              local_20 = local_24;
            }
            if (((ushort)local_44[2] == 1) &&
               (*(uint **)(DAT_00710b54 + (uint)**(ushort **)((int)local_44 + 10) * 4) == local_20)
               && (iVar15 = FUN_005bdc90(local_20, local_44), iVar15 != 0)) {
              local_44 = local_20;
            }
            if (((ushort)local_28[2] == 1) && (local_20 == local_24) && (local_44 == local_20)) {
              FUN_005bdc90(local_44, local_28);
            }
            return 1;
          }
        }
        return 0;
      }
    }
  }
  return 0;
}

/* Native 0x609560, 486 bytes. */
void AddNodeAndSuccessorsRecursively(int *param_1, ushort *param_2, ushort *param_3)
{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort *puVar4;
  ushort uVar5;
  if ((param_2 != (ushort *)0x0) && (*(char *)((int)param_2 + 0x3d) == '\0')) {
    *(byte *)((int)param_2 + 0x3d) = 1;
    if (*(ushort *)(param_1 + 1) < DAT_007172c0) {
      *(ushort *)
       (*param_1 +
       (int)((int)((uint)*(ushort *)(param_1 + 1) + (uint)*(ushort *)((int)param_1 + 6)) %
            (int)(uint)DAT_007172c0) * 2) = *param_2;
      *(short *)(param_1 + 1) = (short)param_1[1] + 1;
    }
    else {
      CError_Internal(s_IroFlowgraph_h_006b9f87, 0x7f);
    }
    if ((param_2 != param_3) && (uVar2 = 0, param_2[1] != 0)) {
      do {
        puVar3 = *(ushort **)
                  (DAT_00710b54 + (uint)*(ushort *)(*(int *)(param_2 + 2) + (uint)uVar2 * 2) * 4);
        if ((puVar3 != (ushort *)0x0) && (*(char *)((int)puVar3 + 0x3d) == '\0')) {
          *(byte *)((int)puVar3 + 0x3d) = 1;
          if (*(ushort *)(param_1 + 1) < DAT_007172c0) {
            *(ushort *)
             (*param_1 +
             (int)((int)((uint)*(ushort *)(param_1 + 1) + (uint)*(ushort *)((int)param_1 + 6))
                  % (int)(uint)DAT_007172c0) * 2) = *puVar3;
            *(short *)(param_1 + 1) = (short)param_1[1] + 1;
          }
          else {
            CError_Internal(s_IroFlowgraph_h_006b9f87, 0x7f);
          }
          if ((puVar3 != param_3) && (uVar1 = 0, puVar3[1] != 0)) {
            do {
              puVar4 = *(ushort **)
                        (DAT_00710b54 +
                        (uint)*(ushort *)(*(int *)(puVar3 + 2) + (uint)uVar1 * 2) * 4);
              if ((puVar4 != (ushort *)0x0) && (*(char *)((int)puVar4 + 0x3d) == '\0')) {
                *(byte *)((int)puVar4 + 0x3d) = 1;
                fn_00609750((int *)(param_1), (ushort)(*puVar4));
                if (puVar4 != param_3) {
                  uVar5 = 0;
                  if (puVar4[1] != 0) {
                    do {
                      AddNodeAndSuccessorsRecursively((int *)(param_1), (ushort *)(*(uint *)
                                             (DAT_00710b54 +
                                             (uint)*(ushort *)
                                                    (*(int *)(puVar4 + 2) + (uint)uVar5 * 2) * 4)), (ushort *)(param_3));
                      uVar5 = uVar5 + 1;
                    } while (uVar5 < (ushort)puVar4[1]);
                  }
                }
              }
              uVar1 = uVar1 + 1;
            } while (uVar1 < (ushort)puVar3[1]);
          }
        }
        uVar2 = uVar2 + 1;
      } while (uVar2 < (ushort)param_2[1]);
    }
  }
  return;
}

/* Native 0x609750, 80 bytes. */
void fn_00609750(int *param_1, ushort param_2)
{
  if (*(ushort *)(param_1 + 1) < DAT_007172c0) {
    *(ushort *)
     (*param_1 +
     (int)((int)((uint)*(ushort *)(param_1 + 1) + (uint)*(ushort *)((int)param_1 + 6)) %
          (int)(uint)DAT_007172c0) * 2) = param_2;
    *(short *)(param_1 + 1) = (short)param_1[1] + 1;
  }
  else {
    CError_Internal(s_IroFlowgraph_h_006b9f87, 0x7f);
  }
  return;
}

/* Native 0x6097a0, 319 bytes. */
byte
CheckForTopLevelExpressions(int param_1, ushort *param_2, int param_3, char *param_4, char *param_5, char param_6)
{
  int iVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  ushort uVar5;
  if (param_1 != param_3) {
    bVar2 = false;
    uVar4 = (uint)(*param_2 >> 5);
    if ((uVar4 < **(uint **)(param_1 + 0x2c)) &&
       (((*(uint **)(param_1 + 0x2c))[uVar4 + 1] & 1 << ((byte)*param_2 & 0x1f)) != 0)) {
      bVar2 = true;
    }
    if (!bVar2) {
      return 1;
    }
    iVar1 = DAT_00710990;
    if (param_6 == '\0') {
      if (*(char *)(param_1 + 0x3d) != '\0') {
        return 0;
      }
    }
    else {
      for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
        *(byte *)(iVar1 + 0x3d) = 0;
      }
    }
    *(byte *)(param_1 + 0x3d) = 1;
    uVar5 = 0;
    if (*(short *)(param_1 + 2) != 0) {
      do {
        iVar1 = *(int *)(DAT_00710b54 +
                        (uint)*(ushort *)(*(int *)(param_1 + 4) + (uint)uVar5 * 2) * 4);
        cVar3 = CheckForTopLevelExpressions((int)(iVar1), (ushort *)(param_2), (int)(param_3), (char *)(*(uint *)(iVar1 + 0x10)), (char *)(param_5), (char)(0));
        if (cVar3 != '\0') {
          return 1;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < *(ushort *)(param_1 + 2));
    }
  }
  while( true ) {
    if ((param_4 == (char *)0x0) || (param_4 == *(char **)(*(int *)(param_1 + 0x14) + 0x3e))) {
      return 0;
    }
    if (param_4 == param_5) {
      return 0;
    }
    if ((*param_4 != '\0') && (*param_4 != '\r') && ((*(uint *)(param_4 + 2) & 2) == 0)) break;
    param_4 = *(char **)(param_4 + 0x3e);
  }
  return 1;
}

/* Native 0x6098e0, 106 bytes. */
void RebuildCondExpressions(void)
{
  int iVar1;
  bool bVar2;
  char cVar3;
  do {
    bVar2 = false;
    for (iVar1 = DAT_00710990; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
      if (*(short *)(iVar1 + 8) == 2) {
        if ((*(char **)(iVar1 + 0x10) != (char *)0x0) && (**(char **)(iVar1 + 0x10) == '\r')) {
          cVar3 = RebuildPossibleCondExpression((ushort *)(iVar1));
LAB_00609930:;
          if (cVar3 != '\0') {
            bVar2 = true;
          }
        }
      }
      else if ((*(short *)(iVar1 + 2) == 2) && (*(char **)(iVar1 + 0x14) != (char *)0x0) &&
              ((byte)(**(char **)(iVar1 + 0x14) - 10U) < 2)) {
        cVar3 = RebuildPossibleReturnCondExpression((int)(iVar1));
        goto LAB_00609930;
      }
    }
    if (!bVar2) {
      FUN_005a9d80();
      return;
    }
  } while( true );
}

/* Native 0x609950, 746 bytes. */
byte RebuildPossibleReturnCondExpression(int param_1)
{
  LinearRange prepared;
  char *pcVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  byte *puVar10;
  int iVar11;

  uint local_1c;
  char local_15;
  uint local_14;
  if ((param_1 == 0) || (*(short *)(param_1 + 2) != 2) ||
     (pcVar1 = *(char **)(param_1 + 0x14), pcVar1 == (char *)0x0) ||
     (*pcVar1 != '\n' && (*pcVar1 != '\v'))) {
    return 0;
  }
  iVar11 = *(int *)(DAT_00710b54 + (uint)**(ushort **)(param_1 + 4) * 4);
  uVar2 = *(uint *)(pcVar1 + 0xe);
  iVar3 = *(int *)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 4))[1] * 4);
  if ((iVar11 == 0) || (iVar3 == 0) ||
     (*(short *)(iVar11 + 2) != 0 ||
     (*(short *)(iVar11 + 8) != 1 || (*(short *)(iVar3 + 2) != 0) || (*(short *)(iVar3 + 8) != 1))))
  {
    return 0;
  }
  pcVar4 = *(char **)(iVar11 + 0x10);
  if (((pcVar4 == (char *)0x0) || (*pcVar4 != '\r') ||
      (pcVar7 = *(char **)(pcVar1 + 0x2a), *(char **)(pcVar4 + 0x2a) != pcVar7)) &&
     (pcVar7 = *(char **)(iVar3 + 0x10), pcVar7 == (char *)0x0 || (*pcVar7 != '\r') ||
     (iVar11 = iVar3, *(int *)(pcVar7 + 0x2a) != *(int *)(pcVar1 + 0x2a)))) {
    return 0;
  }
  if (*(short *)(iVar11 + 8) != 1) {
    return 0;
  }
  uVar8 = CheckThenOrElseBranch((ushort *)(*(uint *)(param_1 + 0x30)), (uint)(*(uint *)(param_1 + 0x30)), (char *)(0), (char)(1));
  if (((char)uVar8 != '\0') && (uVar8 = CheckThenOrElseBranch((ushort *)(iVar11), (uint)(iVar11), (char *)(0), (char)(1)), (char)uVar8 != '\0')) {
    uVar8 = *(uint *)(param_1 + 0x30);
    pcVar1 = *(char **)(uVar8 + 0x14);
    if ((pcVar1 != (char *)0x0) &&
       (*pcVar1 == '\f' && (*(int *)(pcVar1 + 0x2a) != 0) &&
       (pcVar4 = *(char **)(iVar11 + 0x14), pcVar4 != (char *)0x0) && (*pcVar4 == '\f'))) {
      uVar8 = 0;
      if ((*(int *)(pcVar4 + 0x2a) != 0) &&
         (uVar8 = FUN_005b7e20(*(uint *)(*(int *)(pcVar1 + 0x2a) + 0x12),
                               *(uint *)(*(int *)(pcVar4 + 0x2a) + 0x12)), (char)uVar8 != '\0'
         )) {
        uVar8 = *(uint *)(*(int *)(*(int *)(param_1 + 0x30) + 0x14) + 0xe);
        if ((uVar2 != uVar8) &&
           (uVar2 == 0 || (uVar8 == 0) || (uVar8 = FUN_005afcd0(uVar2, uVar8), (char)uVar8 == '\0'))
           ) {
          return 0;
        }
        uVar5 = *(uint *)(*(int *)(iVar11 + 0x14) + 0xe);
        if ((uVar2 != uVar5) &&
           (uVar2 == 0 || (uVar5 == 0) || (uVar8 = FUN_005afcd0(uVar2, uVar5), (char)uVar8 == '\0'))
           ) {
          return 0;
        }
        local_15 = **(char **)(param_1 + 0x14) == '\n';
        local_1c = *(uint *)(*(char **)(param_1 + 0x14) + 0x2e);
        iVar3 = *(int *)(*(int *)(*(int *)(param_1 + 0x30) + 0x14) + 0x2a);
        uVar6 = *(uint *)(*(int *)(iVar11 + 0x14) + 0x2a);
        local_14 = FUN_005b7d30(*(uint *)(iVar3 + 0x12));
        **(byte **)(param_1 + 0x14) = 0;
        *(uint *)(*(int *)(param_1 + 0x14) + 0x1a) = 0;
        **(byte **)(iVar11 + 0x14) = 0;
        *(uint *)(*(int *)(iVar11 + 0x14) + 0x1a) = 0;
        **(byte **)(iVar11 + 0x10) = 0;
        *(uint *)(*(int *)(iVar11 + 0x10) + 0x1a) = 0;
        FUN_005ad280(&prepared.first);
        uVar9 = FUN_005acf30(uVar6, &prepared.first);
        FUN_005ae7b0(uVar6);
        FUN_005ad440(prepared.first, prepared.last, *(uint *)(*(int *)(param_1 + 0x30) + 0x14));
        puVar10 = (byte *)FUN_005bd630(4);
        iVar11 = 0;
        do {
          *(uint *)(puVar10 + iVar11) = *(uint *)(iVar11 + iVar3);
          *(uint *)(puVar10 + iVar11 + 4) = *(uint *)(iVar11 + 4 + iVar3);
          *(uint *)(puVar10 + iVar11 + 8) = *(uint *)(iVar11 + 8 + iVar3);
          *(uint *)(puVar10 + iVar11 + 0xc) = *(uint *)(iVar11 + 0xc + iVar3);
          iVar11 = iVar11 + 0x10;
        } while (iVar11 < 0x40);
        *(ushort *)(puVar10 + 0x40) = *(ushort *)(iVar3 + 0x40);
        *puVar10 = 4;
        puVar10[1] = 0x38;
        *(int *)(puVar10 + 10) = DAT_00710998;
        DAT_00710998 = DAT_00710998 + 1;
        *(uint *)(puVar10 + 0x2a) = local_1c;
        *(uint *)(puVar10 + 0x12) = local_14;
        FUN_005ad440(puVar10, puVar10, *(uint *)(*(int *)(param_1 + 0x30) + 0x14));
        if (local_15 == '\0') {
          *(int *)(puVar10 + 0x2e) = iVar3;
          *(uint *)(puVar10 + 0x32) = uVar9;
        }
        else {
          *(uint *)(puVar10 + 0x2e) = uVar9;
          *(int *)(puVar10 + 0x32) = iVar3;
        }
        iVar11 = *(int *)(*(int *)(param_1 + 0x30) + 0x14);
        *(byte **)(iVar11 + 0x2a) = puVar10;
        return 1;
      }
    }
    return 0;
  }
  return 0;
}

/* Native 0x609c40, 4931 bytes. */
byte RebuildPossibleCondExpression(ushort *param_1)
{
  byte firstSnapshot[66];
  byte secondSnapshot[66];
  char *pcVar1;
  ushort *puVar2;
  uint uVar3;
  uint *puVar4;
  bool bVar5;
  char *pcVar6;
  char cVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  byte bVar13;
  byte bVar14;
  uint uVar15;
  uint uVar16;
  char *pcVar17;
  uint *puVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  uint local_e4;
  int local_e0;
  int local_d8;
  uint *local_cc;

  char *local_84;

  uint local_3c;
  uint *local_38;
  int local_34;
  bool local_2d;
  uint local_2c;
  ushort *local_28;
  uint local_24;
  char *local_20;
  int local_1c;
  char *local_18;
  char *local_14;
  if ((param_1 == (ushort *)0x0) || (param_1[4] != 2) || (*(char **)(param_1 + 8) == (char *)0x0) ||
     (**(char **)(param_1 + 8) != '\r')) {
    return 0;
  }
  uVar19 = *(uint *)(DAT_00710b54 + (uint)**(ushort **)(param_1 + 5) * 4);
  local_84 = *(char **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 5))[1] * 4);
  if ((uVar19 == 0) || (local_84 == (char *)0x0) ||
     (*(short *)(uVar19 + 2) != 1 || (*(short *)((int)local_84 + 2) != 1))) {
    return 0;
  }
  uVar8 = (uint)DAT_007172c0;
  local_34 = 0;
  local_3c = 0;
  if (uVar8 != 0) {
    do {
      bVar5 = false;
      if ((local_3c >> 5 < **(uint **)(param_1 + 0x16)) &&
         (((*(uint **)(param_1 + 0x16))[(local_3c >> 5) + 1] & 1 << ((byte)local_3c & 0x1f)) != 0))
      {
        bVar5 = true;
      }
      local_24 = uVar8;
      if ((bVar5) && (local_34 = *(int *)(DAT_00710b54 + local_3c * 4), local_34 != 0) &&
         (pcVar1 = *(char **)(local_34 + 0x14), pcVar1 != (char *)0x0) &&
         ((byte)(*pcVar1 - 10U) < 2 && (*(int *)(pcVar1 + 0x2a) != 0) &&
         (*(short *)(local_34 + 2) == 2))) {
        puVar18 = *(uint **)(uVar19 + 0x2c);
        puVar2 = *(ushort **)(local_34 + 4);
        uVar3 = *puVar18;
        bVar5 = false;
        uVar16 = (uint)(*puVar2 >> 5);
        bVar14 = (byte)*puVar2;
        if ((uVar16 < uVar3) && ((puVar18[uVar16 + 1] & 1 << (bVar14 & 0x1f)) != 0)) {
          bVar5 = true;
        }
        if (bVar5) {
          puVar4 = *(uint **)((int)local_84 + 0x2c);
          bVar5 = false;
          if ((uVar16 < *puVar4) && ((puVar4[uVar16 + 1] & 1 << (bVar14 & 0x1f)) != 0)) {
            bVar5 = true;
          }
          if (!bVar5) {
            bVar5 = false;
            uVar15 = (uint)(puVar2[1] >> 5);
            bVar13 = (byte)puVar2[1];
            if ((uVar15 < *puVar4) && ((puVar4[uVar15 + 1] & 1 << (bVar13 & 0x1f)) != 0)) {
              bVar5 = true;
            }
            if ((bVar5) && (uVar3 <= uVar15 || ((puVar18[uVar15 + 1] & 1 << (bVar13 & 0x1f)) == 0)))
            break;
          }
        }
        puVar4 = *(uint **)((int)local_84 + 0x2c);
        bVar5 = false;
        if ((uVar16 < *puVar4) && ((puVar4[uVar16 + 1] & 1 << (bVar14 & 0x1f)) != 0)) {
          bVar5 = true;
        }
        if ((bVar5) && (uVar3 <= uVar16 || ((puVar18[uVar16 + 1] & 1 << (bVar14 & 0x1f)) == 0))) {
          bVar5 = false;
          uVar16 = (uint)(puVar2[1] >> 5);
          bVar14 = (byte)puVar2[1];
          if ((uVar16 < uVar3) && ((puVar18[uVar16 + 1] & 1 << (bVar14 & 0x1f)) != 0)) {
            bVar5 = true;
          }
          if ((bVar5) && (*puVar4 <= uVar16 || ((puVar4[uVar16 + 1] & 1 << (bVar14 & 0x1f)) == 0)))
          break;
        }
      }
      local_3c = local_3c + 1;
    } while (local_3c < uVar8);
  }
  if (uVar8 <= local_3c) {
    return 0;
  }
  iVar9 = *(int *)(local_34 + 0x14);
  local_1c = *(int *)(iVar9 + 0xe);
  local_28 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(local_34 + 4) * 4);
  if (((local_28 == (ushort *)0x0) || (local_28[4] != 1) ||
      (pcVar1 = *(char **)(local_28 + 8), pcVar1 == (char *)0x0) ||
      (*pcVar1 != '\r' || (*(int *)(pcVar1 + 0x2a) != *(int *)(iVar9 + 0x2a)))) &&
     (local_28 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(local_34 + 4))[1] * 4),
     local_28 == (ushort *)0x0 ||
     (local_28[4] != 1 || (pcVar1 = *(char **)(local_28 + 8), pcVar1 == (char *)0x0)) ||
     (*pcVar1 != '\r') || (*(int *)(pcVar1 + 0x2a) != *(int *)(iVar9 + 0x2a)))) {
    return 0;
  }
  bVar5 = false;
  uVar8 = (uint)(*local_28 >> 5);
  if ((uVar8 < **(uint **)(uVar19 + 0x2c)) &&
     (((*(uint **)(uVar19 + 0x2c))[uVar8 + 1] & 1 << ((byte)*local_28 & 0x1f)) != 0)) {
    bVar5 = true;
  }
  uVar8 = uVar19;
  local_2c = (uint)local_84;
  if (bVar5) {
    uVar8 = (uint)local_84;
    local_2c = uVar19;
  }
  local_20 = (char *)0x0;
  pcVar6 = local_20;
  for (pcVar1 = *(char **)(uVar8 + 0x10); local_20 = pcVar6,
      pcVar1 != *(char **)(*(int *)(uVar8 + 0x14) + 0x3e); pcVar1 = *(char **)(pcVar1 + 0x3e)) {
    if ((*pcVar1 == '\x03') && (pcVar1[1] == '\x1e') && ((*(uint *)(pcVar1 + 2) & 2) == 0)) {
      local_20 = pcVar1;
    }
    pcVar6 = local_20;
  }
  if ((pcVar6 == (char *)0x0) || (*pcVar6 != '\x03') ||
     (pcVar1 = *(char **)(pcVar6 + 0x2a), pcVar1 == (char *)0x0 ||
     (*pcVar1 != '\x02' || (pcVar1[1] != '\x04'))) ||
     (pcVar1 = *(char **)(pcVar1 + 0x2a), pcVar1 == (char *)0x0) ||
     (*pcVar1 != '\x01' || (local_18 = *(char **)(pcVar1 + 0x2a), local_18 == (char *)0x0) ||
     (*local_18 != ';') ||
     (*(char **)(local_18 + 4) == (char *)0x0 || (**(char **)(local_18 + 4) != '\f')) ||
     (*(int *)(local_18 + 0x10) == 0) ||
     (cVar7 = is_volatile_object(*(uint *)(local_18 + 0x10)), cVar7 != '\0' ||
     (*(char *)(*(int *)(local_18 + 0x10) + 2) != '\x01')))) {
    local_18 = (char *)0x0;
  }
  if ((local_18 != (char *)0x0) && (iVar9 = *(int *)(local_20 + 0xe), local_1c != iVar9) &&
     (local_1c == 0 || (iVar9 == 0 || (cVar7 = FUN_005afcd0(local_1c, iVar9), cVar7 == '\0')))) {
    local_18 = (char *)0x0;
  }
  if (local_18 != (char *)0x0) {
    pcVar17 = (char *)0x0;
    for (pcVar1 = *(char **)(local_2c + 0x10);
        pcVar1 != *(char **)(*(int *)(local_2c + 0x14) + 0x3e); pcVar1 = *(char **)(pcVar1 + 0x3e))
    {
      if ((*pcVar1 == '\x03') && (pcVar1[1] == '\x1e') && ((*(uint *)(pcVar1 + 2) & 2) == 0)) {
        pcVar17 = pcVar1;
      }
    }
    local_14 = pcVar17;
    if ((pcVar17 == (char *)0x0) || (*pcVar17 != '\x03') ||
       (pcVar1 = *(char **)(pcVar17 + 0x2a), pcVar1 == (char *)0x0 ||
       (*pcVar1 != '\x02' || (pcVar1[1] != '\x04'))) ||
       (pcVar1 = *(char **)(pcVar1 + 0x2a), pcVar1 == (char *)0x0 ||
       (*pcVar1 != '\x01' || (pcVar1 = *(char **)(pcVar1 + 0x2a), pcVar1 == (char *)0x0) ||
       (*(char **)(pcVar1 + 4) == (char *)0x0) ||
       (**(char **)(pcVar1 + 4) != '\f' || (*pcVar1 != ';') ||
       (cVar7 = FUN_00455840(*(uint *)(pcVar1 + 0x10), *(uint *)(local_18 + 0x10)),
       cVar7 == '\0' ||
       (cVar7 = FUN_005b7e20(*(uint *)(pcVar17 + 0x12), *(uint *)(local_20 + 0x12)),
       cVar7 == '\0')))))) {
      local_18 = (char *)0x0;
    }
  }
  if ((local_18 != (char *)0x0) && (iVar9 = *(int *)(local_14 + 0xe), local_1c != iVar9) &&
     (local_1c == 0 || (iVar9 == 0 || (cVar7 = FUN_005afcd0(local_1c, iVar9), cVar7 == '\0')))) {
    local_18 = (char *)0x0;
  }
  if (local_18 != (char *)0x0) {
    cVar7 = CheckThenOrElseBranch((ushort *)(*(uint *)(local_34 + 0x30)), (uint)(uVar8), (char *)(local_20), (char)(0));
    if ((cVar7 == '\0') || (cVar7 = CheckThenOrElseBranch((ushort *)(local_28), (uint)(local_2c), (char *)(local_14), (char)(0)), cVar7 == '\0')) {
      return 0;
    }
    local_e0 = 0;
    local_d8 = 0;
    local_2d = false;
    iVar9 = *(int *)(*(int *)(local_18 + 0x10) + 0x20);
    if ((iVar9 == 0) || (local_24 = *(uint *)(iVar9 + 0x18), local_24 == 0) ||
       (puVar18 = *(uint **)(iVar9 + 0x14), puVar18 == (uint *)0x0)) {
      local_18 = (char *)0x0;
    }
    else {
      local_38 = (uint *)0x0;
      local_cc = (uint *)0x0;
      while ((puVar18 != (uint *)0x0 && (local_cc == (uint *)0x0 || (local_38 == (uint *)0x0)))) {
        if (((puVar18[6] == 0) || (puVar4 = puVar18, (char *)puVar18[2] != pcVar6)) &&
           (puVar4 = local_cc, puVar18[6] != 0 && ((char *)puVar18[2] == local_14))) {
          local_38 = puVar18;
        }
        local_cc = puVar4;
        puVar18 = (uint *)puVar18[5];
      }
      if ((local_cc == (uint *)0x0) || (local_38 == (uint *)0x0)) {
        local_18 = (char *)0x0;
      }
      else {
        for (; local_18 != (char *)0x0 && (local_24 != 0); local_24 = *(uint *)(local_24 + 0x14)) {
          if (*(int *)(local_24 + 0x1c) != 0) {
            local_d8 = local_d8 + 1;
            puVar18 = *(uint **)(local_24 + 0x18);
            local_3c = *local_cc;
            uVar19 = *puVar18;
            bVar5 = false;
            uVar8 = local_3c >> 5;
            if ((uVar8 < uVar19) && ((puVar18[uVar8 + 1] & 1 << ((byte)local_3c & 0x1f)) != 0)) {
              bVar5 = true;
            }
            if (bVar5) {
              uVar3 = *local_38;
              bVar5 = false;
              if ((uVar3 >> 5 < uVar19) &&
                 ((puVar18[(uVar3 >> 5) + 1] & 1 << ((byte)uVar3 & 0x1f)) != 0)) {
                bVar5 = true;
              }
              if (bVar5) {
                for (uVar8 = 0; local_18 != (char *)0x0 && (uVar8 < uVar19); uVar8 = uVar8 + 1) {
                  if ((uVar8 != local_3c) && (uVar8 != uVar3)) {
                    bVar5 = false;
                    if ((uVar8 >> 5 < uVar19) &&
                       ((puVar18[(uVar8 >> 5) + 1] & 1 << ((byte)uVar8 & 0x1f)) != 0)) {
                      bVar5 = true;
                    }
                    if (bVar5) {
                      local_18 = (char *)0x0;
                    }
                  }
                }
                if (local_18 != (char *)0x0) {
                  puVar18 = *(uint **)(*(int *)(local_24 + 4) + 0x2c);
                  bVar5 = false;
                  uVar19 = (uint)(*param_1 >> 5);
                  if ((uVar19 < *puVar18) &&
                     ((puVar18[uVar19 + 1] & 1 << ((byte)*param_1 & 0x1f)) != 0)) {
                    bVar5 = true;
                  }
                  if (!bVar5) {
                    local_18 = (char *)0x0;
                  }
                }
                if (local_18 != (char *)0x0) {
                  cVar7 = RewriteUse((int)(local_24), (int)(local_18), (int)(local_14), (char)(0));
                  if (cVar7 == '\0') {
                    local_18 = (char *)0x0;
                  }
                  else {
                    local_e0 = local_e0 + 1;
                  }
                }
                if ((local_18 != (char *)0x0) && (!local_2d)) {
                  local_2d = (bool)fn_0060b8e0((int)(param_1), (int)(*(uint *)(local_24 + 4)), (int)(*(uint *)(local_24 + 8)), (char)(1));
                }
                if ((local_18 != (char *)0x0) && (!local_2d) &&
                   (cVar7 = FUN_005ac320(*(uint *)(*(int *)(local_34 + 0x14) + 0x2e)),
                   cVar7 != '\0' ||
                   (cVar7 = FUN_005ac320(*(uint *)(pcVar6 + 0x2e)), cVar7 != '\0' ||
                   (cVar7 = FUN_005ac320(*(uint *)(local_14 + 0x2e)), cVar7 != '\0')))) {
                  local_2d = (bool)HasSideEffectsBeforeUse((int)(param_1), (int)(*(uint *)(local_24 + 4)), (int)(*(uint *)(local_24 + 8)), (char)(1));
                }
                if ((local_18 != (char *)0x0) && (!local_2d) &&
                   (iVar9 = FUN_005ac1e0(*(uint *)(*(int *)(local_34 + 0x14) + 0x2e)),
                   iVar9 != 0 ||
                   (iVar9 = FUN_005ac1e0(*(uint *)(pcVar6 + 0x2e)), iVar9 != 0 ||
                   (iVar9 = FUN_005ac1e0(*(uint *)(local_14 + 0x2e)), iVar9 != 0)))) {
                  local_2d = true;
                }
                goto LAB_0060a79b;
              }
            }
            if ((uVar19 <= uVar8) || ((puVar18[uVar8 + 1] & 1 << ((byte)local_3c & 0x1f)) == 0)) {
              bVar5 = false;
              uVar8 = *local_38 >> 5;
              if ((uVar8 < uVar19) && ((puVar18[uVar8 + 1] & 1 << ((byte)*local_38 & 0x1f)) != 0)) {
                bVar5 = true;
              }
              if (!bVar5) goto LAB_0060a79b;
            }
            local_18 = (char *)0x0;
          }
LAB_0060a79b:;
        }
      }
    }
  }
  if (local_18 == (char *)0x0) {
    return 0;
  }
  if ((local_e0 == 1) && (!local_2d) &&
     (*(char *)(*(int *)(*(int *)(local_18 + 0x10) + 0x20) + 0xd) == '\0')) {
    for (iVar9 = *(int *)(*(int *)(*(int *)(local_18 + 0x10) + 0x20) + 0x18); iVar9 != 0;
        iVar9 = *(int *)(iVar9 + 0x14)) {
      if (*(int *)(iVar9 + 0x1c) != 0) {
        puVar18 = *(uint **)(iVar9 + 0x18);
        bVar5 = false;
        uVar19 = *local_cc >> 5;
        if ((uVar19 < *puVar18) && ((puVar18[uVar19 + 1] & 1 << ((byte)*local_cc & 0x1f)) != 0)) {
          bVar5 = true;
        }
        if (bVar5) {
          bVar5 = false;
          uVar19 = *local_38 >> 5;
          if ((uVar19 < *puVar18) && ((puVar18[uVar19 + 1] & 1 << ((byte)*local_38 & 0x1f)) != 0)) {
            bVar5 = true;
          }
          if ((bVar5) && (cVar7 = RewriteUse((int)(iVar9), (int)(local_18), (int)(local_14), (char)(0)), cVar7 != '\0') &&
             (iVar21 = *(int *)(*(int *)(iVar9 + 8) + 0xe), local_1c != iVar21) &&
             (local_1c == 0 || (iVar21 == 0) ||
             (cVar7 = FUN_005afcd0(local_1c, iVar21), cVar7 == '\0'))) {
            local_2d = true;
          }
        }
      }
    }
  }
  cVar7 = **(char **)(local_34 + 0x14);
  iVar9 = *(int *)(local_20 + 0x2e);
  local_1c = *(int *)(local_14 + 0x2e);
  iVar21 = *(int *)(*(char **)(local_34 + 0x14) + 0x2e);
  local_84 = local_14;
  local_24 = FUN_005b7d30(*(uint *)(local_14 + 0x12));
  iVar10 = 0;
  do {
    *(uint *)((int)((uint *)firstSnapshot) + iVar10) = *(uint *)(iVar10 + iVar9);
    *(uint *)((int)((uint *)firstSnapshot) + iVar10 + 4) = *(uint *)(iVar10 + 4 + iVar9);
    *(uint *)((int)((uint *)firstSnapshot) + iVar10 + 8) = *(uint *)(iVar10 + 8 + iVar9);
    *(uint *)((int)((uint *)firstSnapshot) + iVar10 + 0xc) = *(uint *)(iVar10 + 0xc + iVar9);
    iVar10 = iVar10 + 0x10;
  } while (iVar10 < 0x40);
  (*(ushort *)(firstSnapshot+64)) = *(ushort *)(iVar9 + 0x40);
  iVar10 = 0;
  do {
    *(uint *)((int)((uint *)secondSnapshot) + iVar10) = *(uint *)(local_14 + iVar10);
    *(uint *)((int)((uint *)secondSnapshot) + iVar10 + 4) = *(uint *)(local_14 + iVar10 + 4);
    *(uint *)((secondSnapshot+8) + iVar10) = *(uint *)(local_14 + iVar10 + 8);
    *(uint *)((int)((uint *)(secondSnapshot+12)) + iVar10) = *(uint *)(local_14 + iVar10 + 0xc);
    iVar10 = iVar10 + 0x10;
  } while (iVar10 < 0x40);
  (*(uint *)(secondSnapshot+62)) = CONCAT22(*(ushort *)(local_14 + 0x40), (ushort)(*(uint *)(secondSnapshot+62)));
  **(byte **)(local_34 + 0x14) = 0;
  *(uint *)(*(int *)(local_34 + 0x14) + 0x1a) = 0;
  **(byte **)(local_28 + 8) = 0;
  *(uint *)(*(int *)(local_28 + 8) + 0x1a) = 0;
  if (**(char **)(local_2c + 0x14) == '\b') {
    **(char **)(local_2c + 0x14) = '\0';
    *(uint *)(*(int *)(local_2c + 0x14) + 0x1a) = 0;
  }
  if (local_18 != (char *)0x0) {
    FUN_005ae7b0(*(uint *)(local_20 + 0x2a));
    *local_20 = '\0';
    local_20[0x1a] = '\0';
    local_20[0x1b] = '\0';
    local_20[0x1c] = '\0';
    local_20[0x1d] = '\0';
  }
  iVar10 = 0;
  do {
    *(uint *)(local_14 + iVar10) = *(uint *)((int)((uint *)firstSnapshot) + iVar10);
    *(uint *)(local_14 + iVar10 + 4) = *(uint *)((int)((uint *)firstSnapshot) + iVar10 + 4);
    *(uint *)(local_14 + iVar10 + 8) = *(uint *)((int)((uint *)firstSnapshot) + iVar10 + 8);
    *(uint *)(local_14 + iVar10 + 0xc) = *(uint *)((int)((uint *)firstSnapshot) + iVar10 + 0xc);
    iVar10 = iVar10 + 0x10;
  } while (iVar10 < 0x40);
  *(ushort *)(local_14 + 0x40) = (*(ushort *)(firstSnapshot+64));
  *local_14 = '\x04';
  local_14[1] = '8';
  *(uint *)(local_14 + 10) = (*(uint *)(secondSnapshot+10));
  *(int *)(local_14 + 0x2a) = iVar21;
  uVar12 = FUN_005b7d30(local_24);
  *(uint *)(local_14 + 0x12) = uVar12;
  *(uint *)(local_14 + 0x3e) = (*(uint *)(secondSnapshot+62));
  if (cVar7 == '\n') {
    *(int *)(local_14 + 0x2e) = local_1c;
    *(int *)(local_14 + 0x32) = iVar9;
  }
  else {
    *(int *)(local_14 + 0x2e) = iVar9;
    *(int *)(local_14 + 0x32) = local_1c;
  }
  *(uint *)(local_14 + 2) = *(uint *)(local_14 + 2) | 2;
  if ((local_e0 != 1) || (local_2d) ||
     (*(char *)(*(int *)(*(int *)(local_18 + 0x10) + 0x20) + 0xd) != '\0')) {
    iVar9 = FUN_005bd630(3);
    iVar21 = 0;
    do {
      *(uint *)(iVar21 + iVar9) = *(uint *)((int)((uint *)secondSnapshot) + iVar21);
      *(uint *)(iVar21 + 4 + iVar9) = *(uint *)((int)((uint *)secondSnapshot) + iVar21 + 4);
      *(uint *)(iVar21 + 8 + iVar9) = *(uint *)((secondSnapshot+8) + iVar21);
      *(uint *)(iVar21 + 0xc + iVar9) = *(uint *)((int)((uint *)(secondSnapshot+12)) + iVar21);
      iVar21 = iVar21 + 0x10;
    } while (iVar21 < 0x40);
    *(ushort *)(iVar9 + 0x40) = (*(ushort *)(secondSnapshot+64));
    *(int *)(iVar9 + 10) = DAT_00710998;
    DAT_00710998 = DAT_00710998 + 1;
    *(char **)(iVar9 + 0x2e) = local_14;
    FUN_005ad400(iVar9, iVar9, *(uint *)(param_1 + 8));
    local_cc[6] = 0;
    local_38[2] = *(uint *)(param_1 + 8);
  }
  else {
    local_2d = false;
    for (iVar9 = *(int *)(*(int *)(*(int *)(local_18 + 0x10) + 0x20) + 0x18); iVar9 != 0;
        iVar9 = *(int *)(iVar9 + 0x14)) {
      if (*(int *)(iVar9 + 0x1c) != 0) {
        puVar18 = *(uint **)(iVar9 + 0x18);
        local_2c = *puVar18;
        bVar5 = false;
        uVar19 = *local_cc >> 5;
        if ((uVar19 < local_2c) && ((puVar18[uVar19 + 1] & 1 << ((byte)*local_cc & 0x1f)) != 0)) {
          bVar5 = true;
        }
        if (bVar5) {
          bVar5 = false;
          uVar19 = *local_38 >> 5;
          if ((uVar19 < local_2c) && ((puVar18[uVar19 + 1] & 1 << ((byte)*local_38 & 0x1f)) != 0)) {
            bVar5 = true;
          }
          if (bVar5) {
            RewriteUse((int)(iVar9), (int)(local_18), (int)(local_84), (char)(1));
            local_2d = (*(uint *)(*(int *)(iVar9 + 8) + 2) & 0x4000) != 0;
            if (local_2d) {
              iVar10 = FUN_005ac1e0(iVar21);
              local_2d = iVar10 != 0;
            }
            if (local_2d != false) {
              iVar11 = FUN_005bd630(0);
              iVar10 = *(int *)((*(int *)(secondSnapshot+42)) + 0x2a);
              iVar20 = 0;
              do {
                *(uint *)(iVar20 + iVar11) = *(uint *)(iVar20 + iVar10);
                *(uint *)(iVar20 + 4 + iVar11) = *(uint *)(iVar20 + 4 + iVar10);
                *(uint *)(iVar20 + 8 + iVar11) = *(uint *)(iVar20 + 8 + iVar10);
                *(uint *)(iVar20 + 0xc + iVar11) = *(uint *)(iVar20 + 0xc + iVar10);
                iVar20 = iVar20 + 0x10;
              } while (iVar20 < 0x40);
              *(ushort *)(iVar11 + 0x40) = *(ushort *)(iVar10 + 0x40);
              *(byte *)(iVar11 + 1) = 0x3b;
              *(int *)(iVar11 + 10) = DAT_00710998;
              DAT_00710998 = DAT_00710998 + 1;
              uVar12 = FUN_005b7d30(*(uint *)(iVar21 + 0x12));
              *(uint *)(iVar11 + 0x12) = uVar12;
              if (local_d8 == 1) {
                *(uint *)(*(int *)(*(int *)(iVar11 + 0x2a) + 0x10) + 0x10) =
                     *(uint *)(iVar11 + 0x12);
                uVar12 = CDecl_NewPointerType(*(uint *)(iVar11 + 0x12));
                *(uint *)(*(int *)(iVar11 + 0x2a) + 4) = uVar12;
              }
              else {
                local_e4 = create_temp_object(*(uint *)(iVar11 + 0x12));
                FUN_005b53d0(local_e4, 1, 1);
                uVar12 = FUN_00521c20(local_e4, 1);
                *(uint *)(iVar11 + 0x2a) = uVar12;
              }
              *(uint *)(iVar11 + 0x12) = *(uint *)(*(int *)(iVar11 + 0x2a) + 4);
              FUN_005ad400(iVar11, iVar11, iVar21);
              iVar10 = FUN_005bd630(2);
              iVar11 = 0;
              do {
                *(uint *)(iVar11 + iVar10) = *(uint *)(iVar11 + (*(int *)(secondSnapshot+42)));
                *(uint *)(iVar11 + 4 + iVar10) = *(uint *)(iVar11 + 4 + (*(int *)(secondSnapshot+42)));
                *(uint *)(iVar11 + 8 + iVar10) = *(uint *)(iVar11 + 8 + (*(int *)(secondSnapshot+42)));
                *(uint *)(iVar11 + 0xc + iVar10) = *(uint *)(iVar11 + 0xc + (*(int *)(secondSnapshot+42)));
                iVar11 = iVar11 + 0x10;
              } while (iVar11 < 0x40);
              *(ushort *)(iVar10 + 0x40) = *(ushort *)((*(int *)(secondSnapshot+42)) + 0x40);
              *(int *)(iVar10 + 10) = DAT_00710998;
              DAT_00710998 = DAT_00710998 + 1;
              *(uint *)(iVar10 + 0x2a) = *(uint *)(iVar21 + 0x3e);
              uVar12 = FUN_005b7d30(*(uint *)(iVar21 + 0x12));
              *(uint *)(iVar10 + 0x12) = uVar12;
              FUN_005ad400(iVar10, iVar10, *(uint *)(iVar21 + 0x3e));
              iVar10 = FUN_005bd630(3);
              iVar11 = 0;
              do {
                *(uint *)(iVar11 + iVar10) = *(uint *)((int)((uint *)secondSnapshot) + iVar11);
                *(uint *)(iVar11 + 4 + iVar10) = *(uint *)((int)((uint *)secondSnapshot) + iVar11 + 4)
                ;
                *(uint *)(iVar11 + 8 + iVar10) = *(uint *)((secondSnapshot+8) + iVar11);
                *(uint *)(iVar11 + 0xc + iVar10) = *(uint *)((int)((uint *)(secondSnapshot+12)) + iVar11);
                iVar11 = iVar11 + 0x10;
              } while (iVar11 < 0x40);
              *(ushort *)(iVar10 + 0x40) = (*(ushort *)(secondSnapshot+64));
              *(int *)(iVar10 + 10) = DAT_00710998;
              DAT_00710998 = DAT_00710998 + 1;
              *(int *)(iVar10 + 0x2e) = iVar21;
              *(uint *)(iVar10 + 0x2a) = *(uint *)(*(int *)(iVar21 + 0x3e) + 0x3e);
              uVar12 = FUN_005b7d30(*(uint *)(iVar21 + 0x12));
              *(uint *)(iVar10 + 0x12) = uVar12;
              FUN_005ad400(iVar10, iVar10, *(uint *)(*(int *)(iVar21 + 0x3e) + 0x3e));
              if (local_d8 != 1) {
                iVar10 = *(int *)((*(int *)(secondSnapshot+42)) + 0x2a);
                uVar12 = FUN_00521c20(local_e4, 1);
                *(uint *)(iVar10 + 0x2a) = uVar12;
              }
              *(int *)(local_84 + 0x2a) = (*(int *)(secondSnapshot+42));
              uVar12 = FUN_005b7d30(*(uint *)(iVar21 + 0x12));
              *(uint *)(*(int *)(local_84 + 0x2a) + 0x12) = uVar12;
              if (local_d8 == 1) {
                local_38[2] = *(uint *)(*(int *)(iVar21 + 0x3e) + 0x3e);
              }
            }
          }
        }
      }
    }
    if (local_2d == false) {
      if ((local_d8 == 1) && (*(int *)(*(int *)(local_18 + 0x10) + 0x40) != 0)) {
        *(uint *)(*(int *)(*(int *)(local_18 + 0x10) + 0x40) + 4) = 0;
        *(byte *)(*(int *)(*(int *)(local_18 + 0x10) + 0x40) + 9) = 0;
      }
      local_cc[6] = 0;
      FUN_005ae7b0((*(int *)(secondSnapshot+42)));
      local_38[6] = 0;
    }
  }
  return 1;
}

/* Native 0x60af90, 360 bytes. */
byte CheckThenOrElseBranch(ushort *param_1, uint param_2, char *param_3, char param_4)
{
  NativeQueue queue;
  char cVar1;
  int iVar2;
  bool bVar3;
  uint uVar4;
  byte uVar5;
  char *pcVar6;

  queue.buffer = FUN_004c5480((uint)DAT_007172c0 * 2);
  queue.count = 0;
  queue.head = 0;
  for (iVar2 = DAT_00710990; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x30)) {
    *(byte *)(iVar2 + 0x3d) = 0;
  }
  AddNodeAndSuccessorsRecursively((int *)(&queue.buffer), (ushort *)(param_1), (ushort *)(param_2));
  do {
    do {
      if (queue.count == 0) {
        uVar5 = 1;
LAB_0060b095:;
        FUN_004c53c0(queue.buffer);
        return uVar5;
      }
      uVar4 = 0xffffffff;
      if (queue.count != 0) {
        uVar4 = (uint)*(ushort *)(queue.buffer + (uint)queue.head * 2);
        queue.head = (ushort)((int)(queue.head + 1) %
                            (int)(uint)DAT_007172c0);
        queue.count = queue.count - 1;
      }
      iVar2 = *(int *)(DAT_00710b54 + (uVar4 & 0xffff) * 4);
    } while (iVar2 == 0);
    bVar3 = false;
    uVar4 = (uint)(*param_1 >> 5);
    if ((uVar4 < **(uint **)(iVar2 + 0x2c)) &&
       (((*(uint **)(iVar2 + 0x2c))[uVar4 + 1] & 1 << ((byte)*param_1 & 0x1f)) != 0)) {
      bVar3 = true;
    }
    if (!bVar3) {
      uVar5 = 0;
      goto LAB_0060b095;
    }
    for (pcVar6 = *(char **)(iVar2 + 0x10); pcVar6 != (char *)0x0 &&
        (pcVar6 != *(char **)(*(int *)(iVar2 + 0x14) + 0x3e)); pcVar6 = *(char **)(pcVar6 + 0x3e)) {
      if (((param_3 == (char *)0x0) || (pcVar6 != param_3)) &&
         (param_4 == '\0' || (*pcVar6 != '\f'))) {
        if ((*(short *)(iVar2 + 8) == 2) && (*pcVar6 == '\r')) {
          RebuildPossibleCondExpression((ushort *)(iVar2));
        }
        cVar1 = *pcVar6;
        if ((cVar1 != '\0') && (cVar1 != '\r') && (cVar1 != '\b') &&
           ((*(uint *)(pcVar6 + 2) & 2) == 0)) {
          uVar5 = 0;
          goto LAB_0060b095;
        }
      }
    }
  } while( true );
}

/* Native 0x60b100, 551 bytes. */
char UsesAKilledVarBeforeUse(int param_1, int param_2, char *param_3, uint *param_4, char param_5)
{
  bool bVar1;
  int iVar2;
  uint *puVar3;
  char cVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  ushort uVar9;
  uint *local_18;
  char local_11;
  if (param_1 != param_2) {
    iVar2 = DAT_00710990;
    if (param_5 == '\0') {
      if (*(char *)(param_1 + 0x3d) != '\0') {
        return '\0';
      }
    }
    else {
      for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x30)) {
        *(byte *)(iVar2 + 0x3d) = 0;
      }
    }
    *(byte *)(param_1 + 0x3d) = 1;
  }
  pcVar6 = *(char **)(param_1 + 0x10);
  do {
    if ((pcVar6 == (char *)0x0) || (pcVar6 == *(char **)(*(int *)(param_1 + 0x14) + 0x3e))) {
      if ((param_1 != param_2) && (uVar9 = 0, *(short *)(param_1 + 2) != 0)) {
        do {
          cVar4 = UsesAKilledVarBeforeUse((int)(*(uint *)
                                (DAT_00710b54 +
                                (uint)*(ushort *)(*(int *)(param_1 + 4) + (uint)uVar9 * 2) * 4)), (int)(param_2), (char *)(param_3), (uint *)(param_4), (char)(0));
          if (cVar4 != '\0') {
            return '\x01';
          }
          uVar9 = uVar9 + 1;
        } while (uVar9 < *(ushort *)(param_1 + 2));
      }
      return '\0';
    }
    if ((*(uint *)(pcVar6 + 2) & 2) == 0) {
      cVar4 = FUN_005abfc0(pcVar6, param_3);
      if (cVar4 != '\0') {
        local_11 = '\0';
        if (pcVar6 != param_3) {
          pcVar6 = (char *)IroUtil_FindNextUse(param_3);
          while ((pcVar7 = pcVar6, pcVar7 != (char *)0x0 && (local_11 == '\0'))) {
            fn_0060b3b0((byte *)(pcVar7), (int)(param_3), (uint *)(param_4), (char *)(&local_11));
            pcVar6 = (char *)IroUtil_FindNextUse(pcVar7);
            param_3 = pcVar7;
          }
        }
        return local_11;
      }
      FUN_005bfae0(&local_18, DAT_00710084 + 1);
      puVar3 = local_18;
      if (*pcVar6 == '\x14') {
        cVar4 = FUN_005b07a0(pcVar6);
        if (((cVar4 == '\0') || (*(int *)(pcVar6 + 0x2a) == 0) ||
            ((*(uint *)(*(int *)(pcVar6 + 0x2a) + 2) & 0x10) != 0)) &&
           ((*(uint *)(pcVar6 + 2) & 4) == 0 || ((*(uint *)(pcVar6 + 2) & 0x10) != 0))) {
          FUN_005f6b80(pcVar6, 0, 0, 1);
          FUN_005bf940(DAT_0071015c, puVar3);
        }
        else {
          FUN_005ad5e0(pcVar6, &GetDependsOfStatement, puVar3);
        }
      }
      else {
        FUN_005ad5c0(pcVar6, &GetDependsOfStatement, local_18);
      }
      uVar8 = *param_4;
      if (*local_18 < uVar8) {
        uVar8 = *local_18;
      }
      if (uVar8 != 0) {
        uVar5 = 0;
        do {
          if ((param_4[uVar5 + 1] & local_18[uVar5 + 1]) != 0) {
            bVar1 = true;
            goto LAB_0060b229;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < uVar8);
      }
      bVar1 = false;
LAB_0060b229:;
      if (bVar1) {
        return '\x01';
      }
      if (local_18 != (uint *)0x0) {
        FUN_004c53c0(local_18);
        local_18 = (uint *)0x0;
      }
    }
    pcVar6 = *(char **)(pcVar6 + 0x3e);
  } while( true );
}

/* Native 0x60b330, 114 bytes. */
void GetDependsOfStatement(int param_1, char param_2, uint param_3)
{
  char cVar1;
  if (param_2 != '\0') {
    cVar1 = FUN_005b07a0(param_1);
    if (((cVar1 == '\0') || (*(int *)(param_1 + 0x2a) == 0) ||
        ((*(uint *)(*(int *)(param_1 + 0x2a) + 2) & 0x10) != 0)) &&
       ((*(uint *)(param_1 + 2) & 4) == 0 || ((*(uint *)(param_1 + 2) & 0x10) != 0))) {
      FUN_005f6b80(param_1, 0, 0, 1);
      FUN_005bf940(DAT_0071015c, param_3);
    }
    else {
      FUN_005ad5e0(param_1, GetDependsOfStatement, param_3);
    }
  }
  return;
}

/* Native 0x60b3b0, 702 bytes. */
void fn_0060b3b0(byte *param_1, int param_2, uint *param_3, char *param_4)
{
  char cVar1;
  int iVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  int local_14;
  switch(*param_1) {
  case 3:
    if (*(int *)(param_1 + 0x2a) != param_2) {
      FUN_005f6b80(*(int *)(param_1 + 0x2a), 0, 0, 1);
      uVar4 = *param_3;
      if (*DAT_0071015c < uVar4) {
        uVar4 = *DAT_0071015c;
      }
      uVar5 = 0;
      if (uVar4 != 0) {
        do {
          if ((param_3[uVar5 + 1] & DAT_0071015c[uVar5 + 1]) != 0) {
            bVar3 = true;
            goto LAB_0060b41d;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < uVar4);
      }
      bVar3 = false;
LAB_0060b41d:;
      if (bVar3) {
        *param_4 = '\x01';
      }
    }
    cVar1 = param_1[1];
    if ((cVar1 != '\x1c') && (cVar1 != '\x1d') && (cVar1 != ')') &&
       (*(int *)(param_1 + 0x2e) != param_2)) {
      FUN_005f6b80(*(int *)(param_1 + 0x2e), 0, 0, 1);
      uVar4 = *param_3;
      if (*DAT_0071015c < uVar4) {
        uVar4 = *DAT_0071015c;
      }
      uVar5 = 0;
      if (uVar4 != 0) {
        do {
          if ((param_3[uVar5 + 1] & DAT_0071015c[uVar5 + 1]) != 0) {
            bVar3 = true;
            goto LAB_0060b489;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < uVar4);
      }
      bVar3 = false;
LAB_0060b489:;
      if (bVar3) {
        *param_4 = '\x01';
      }
    }
    break;
  case 4:
    if (*(int *)(param_1 + 0x2a) != param_2) {
      FUN_005f6b80(*(int *)(param_1 + 0x2a), 0, 0, 1);
      uVar4 = *param_3;
      if (*DAT_0071015c < uVar4) {
        uVar4 = *DAT_0071015c;
      }
      uVar5 = 0;
      if (uVar4 != 0) {
        do {
          if ((param_3[uVar5 + 1] & DAT_0071015c[uVar5 + 1]) != 0) {
            bVar3 = true;
            goto LAB_0060b4de;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < uVar4);
      }
      bVar3 = false;
LAB_0060b4de:;
      if (bVar3) {
        *param_4 = '\x01';
      }
    }
    if ((param_1[1] != '8') && (param_1[1] != 'X')) {
      if (*(int *)(param_1 + 0x2e) != param_2) {
        FUN_005f6b80(*(int *)(param_1 + 0x2e), 0, 0, 1);
        uVar4 = *param_3;
        if (*DAT_0071015c < uVar4) {
          uVar4 = *DAT_0071015c;
        }
        uVar5 = 0;
        if (uVar4 != 0) {
          do {
            if ((param_3[uVar5 + 1] & DAT_0071015c[uVar5 + 1]) != 0) {
              bVar3 = true;
              goto LAB_0060b549;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < uVar4);
        }
        bVar3 = false;
LAB_0060b549:;
        if (bVar3) {
          *param_4 = '\x01';
        }
      }
      if (*(int *)(param_1 + 0x32) != param_2) {
        FUN_005f6b80(*(int *)(param_1 + 0x32), 0, 0, 1);
        uVar4 = *param_3;
        if (*DAT_0071015c < uVar4) {
          uVar4 = *DAT_0071015c;
        }
        uVar5 = 0;
        if (uVar4 != 0) {
          do {
            if ((param_3[uVar5 + 1] & DAT_0071015c[uVar5 + 1]) != 0) {
              bVar3 = true;
              goto LAB_0060b599;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < uVar4);
        }
        bVar3 = false;
LAB_0060b599:;
        if (bVar3) {
          *param_4 = '\x01';
        }
      }
    }
    break;
  case 7:
    if (*(int *)(param_1 + 0x32) != param_2) {
      FUN_005f6b80(*(int *)(param_1 + 0x32), 0, 0, 1);
      uVar4 = *param_3;
      if (*DAT_0071015c < uVar4) {
        uVar4 = *DAT_0071015c;
      }
      uVar5 = 0;
      if (uVar4 != 0) {
        do {
          if ((param_3[uVar5 + 1] & DAT_0071015c[uVar5 + 1]) != 0) {
            bVar3 = true;
            goto LAB_0060b5ed;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < uVar4);
      }
      bVar3 = false;
LAB_0060b5ed:;
      if (bVar3) {
        *param_4 = '\x01';
      }
    }
    for (local_14 = 0; *param_4 == '\0' && (local_14 < *(short *)(param_1 + 0x2c));
        local_14 = local_14 + 1) {
      iVar2 = *(int *)(*(int *)(param_1 + 0x2e) + local_14 * 4);
      if (iVar2 != param_2) {
        FUN_005f6b80(iVar2, 0, 0, 1);
        uVar4 = *param_3;
        if (*DAT_0071015c < uVar4) {
          uVar4 = *DAT_0071015c;
        }
        uVar5 = 0;
        if (uVar4 != 0) {
          do {
            if ((param_3[uVar5 + 1] & DAT_0071015c[uVar5 + 1]) != 0) {
              bVar3 = true;
              goto LAB_0060b659;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < uVar4);
        }
        bVar3 = false;
LAB_0060b659:;
        if (bVar3) {
          *param_4 = '\x01';
        }
      }
    }
  }
  return;
}

/* Native 0x60b670, 323 bytes. */
char HasSideEffectsBeforeUse(int param_1, int param_2, int param_3, char param_4)
{
  char cVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  char local_11;
  if (param_1 != param_2) {
    iVar3 = DAT_00710990;
    if (param_4 == '\0') {
      if (*(char *)(param_1 + 0x3d) != '\0') {
        return '\0';
      }
    }
    else {
      for (; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x30)) {
        *(byte *)(iVar3 + 0x3d) = 0;
      }
    }
    *(byte *)(param_1 + 0x3d) = 1;
  }
  iVar3 = *(int *)(param_1 + 0x10);
  do {
    if ((iVar3 == 0) || (iVar3 == *(int *)(*(int *)(param_1 + 0x14) + 0x3e))) {
      if ((param_1 != param_2) && (uVar4 = 0, *(short *)(param_1 + 2) != 0)) {
        do {
          cVar1 = HasSideEffectsBeforeUse((int)(*(uint *)
                                (DAT_00710b54 +
                                (uint)*(ushort *)(*(int *)(param_1 + 4) + (uint)uVar4 * 2) * 4)), (int)(param_2), (int)(param_3), (char)(0));
          if (cVar1 != '\0') {
            return '\x01';
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(ushort *)(param_1 + 2));
      }
      return '\0';
    }
    if ((*(uint *)(iVar3 + 2) & 2) == 0) {
      cVar1 = FUN_005abfc0(iVar3, param_3);
      if (cVar1 != '\0') {
        local_11 = '\0';
        if (iVar3 != param_3) {
          iVar3 = IroUtil_FindNextUse(param_3);
          while ((iVar2 = iVar3, iVar2 != 0 && (local_11 == '\0'))) {
            StatementHasSideEffectBeforeUse((byte *)(iVar2), (int)(param_3), (char *)(&local_11));
            iVar3 = IroUtil_FindNextUse(iVar2);
            param_3 = iVar2;
          }
        }
        return local_11;
      }
      iVar2 = FUN_005ad570(iVar3);
      if ((iVar2 != 0) && (cVar1 = FUN_005ac320(iVar2), cVar1 != '\0')) {
        return '\x01';
      }
    }
    iVar3 = *(int *)(iVar3 + 0x3e);
  } while( true );
}

/* Native 0x60b7c0, 277 bytes. */
void StatementHasSideEffectBeforeUse(byte *param_1, int param_2, char *param_3)
{
  int iVar1;
  char cVar2;
  int iVar3;
  switch(*param_1) {
  case 3:
    if ((*(int *)(param_1 + 0x2a) != param_2) &&
       (cVar2 = FUN_005ac320(*(int *)(param_1 + 0x2a)), cVar2 != '\0')) {
      *param_3 = '\x01';
    }
    cVar2 = param_1[1];
    if ((cVar2 != '\x1c') && (cVar2 != '\x1d') && (cVar2 != ')') &&
       (*(int *)(param_1 + 0x2e) != param_2 &&
       (cVar2 = FUN_005ac320(*(int *)(param_1 + 0x2e)), cVar2 != '\0'))) {
      *param_3 = '\x01';
    }
    break;
  case 4:
    if ((*(int *)(param_1 + 0x2a) != param_2) &&
       (cVar2 = FUN_005ac320(*(int *)(param_1 + 0x2a)), cVar2 != '\0')) {
      *param_3 = '\x01';
    }
    if ((param_1[1] != '8') && (param_1[1] != 'X')) {
      if ((*(int *)(param_1 + 0x2e) != param_2) &&
         (cVar2 = FUN_005ac320(*(int *)(param_1 + 0x2e)), cVar2 != '\0')) {
        *param_3 = '\x01';
      }
      if ((*(int *)(param_1 + 0x32) != param_2) &&
         (cVar2 = FUN_005ac320(*(int *)(param_1 + 0x32)), cVar2 != '\0')) {
        *param_3 = '\x01';
      }
    }
    break;
  case 7:
    if ((*(int *)(param_1 + 0x32) != param_2) &&
       (cVar2 = FUN_005ac320(*(int *)(param_1 + 0x32)), cVar2 != '\0')) {
      *param_3 = '\x01';
    }
    for (iVar3 = 0; *param_3 == '\0' && (iVar3 < *(short *)(param_1 + 0x2c)); iVar3 = iVar3 + 1) {
      iVar1 = *(int *)(*(int *)(param_1 + 0x2e) + iVar3 * 4);
      if ((iVar1 != param_2) && (cVar2 = FUN_005ac320(iVar1), cVar2 != '\0')) {
        *param_3 = '\x01';
      }
    }
  }
  return;
}

/* Native 0x60b8e0, 307 bytes. */
char fn_0060b8e0(int param_1, int param_2, int param_3, char param_4)
{
  char cVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  char local_11;
  if (param_1 != param_2) {
    iVar2 = DAT_00710990;
    if (param_4 == '\0') {
      if (*(char *)(param_1 + 0x3d) != '\0') {
        return '\0';
      }
    }
    else {
      for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x30)) {
        *(byte *)(iVar2 + 0x3d) = 0;
      }
    }
    *(byte *)(param_1 + 0x3d) = 1;
  }
  iVar2 = *(int *)(param_1 + 0x10);
  do {
    if ((iVar2 == 0) || (iVar2 == *(int *)(*(int *)(param_1 + 0x14) + 0x3e))) {
      if ((param_1 != param_2) && (uVar4 = 0, *(short *)(param_1 + 2) != 0)) {
        do {
          cVar1 = fn_0060b8e0((int)(*(uint *)
                                (DAT_00710b54 +
                                (uint)*(ushort *)(*(int *)(param_1 + 4) + (uint)uVar4 * 2) * 4)), (int)(param_2), (int)(param_3), (char)(0));
          if (cVar1 != '\0') {
            return '\x01';
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(ushort *)(param_1 + 2));
      }
      return '\0';
    }
    if ((*(uint *)(iVar2 + 2) & 2) == 0) {
      cVar1 = FUN_005abfc0(iVar2, param_3);
      if (cVar1 != '\0') {
        local_11 = '\0';
        if (iVar2 != param_3) {
          iVar2 = IroUtil_FindNextUse(param_3);
          while ((iVar3 = iVar2, iVar3 != 0 && (local_11 == '\0'))) {
            fn_0060ba20((byte *)(iVar3), (int)(param_3), (char *)(&local_11));
            iVar2 = IroUtil_FindNextUse(iVar3);
            param_3 = iVar3;
          }
        }
        return local_11;
      }
      cVar1 = FUN_005abf30(iVar2);
      if (cVar1 != '\0') {
        return '\x01';
      }
    }
    iVar2 = *(int *)(iVar2 + 0x3e);
  } while( true );
}

/* Native 0x60ba20, 277 bytes. */
void fn_0060ba20(byte *param_1, int param_2, char *param_3)
{
  char cVar1;
  int iVar2;
  int iVar3;
  switch(*param_1) {
  case 3:
    if ((*(int *)(param_1 + 0x2a) != param_2) &&
       (iVar2 = FUN_005ac1e0(*(int *)(param_1 + 0x2a)), iVar2 != 0)) {
      *param_3 = '\x01';
    }
    cVar1 = param_1[1];
    if ((cVar1 != '\x1c') && (cVar1 != '\x1d') && (cVar1 != ')') &&
       (*(int *)(param_1 + 0x2e) != param_2 &&
       (iVar2 = FUN_005ac1e0(*(int *)(param_1 + 0x2e)), iVar2 != 0))) {
      *param_3 = '\x01';
    }
    break;
  case 4:
    if ((*(int *)(param_1 + 0x2a) != param_2) &&
       (iVar2 = FUN_005ac1e0(*(int *)(param_1 + 0x2a)), iVar2 != 0)) {
      *param_3 = '\x01';
    }
    if ((param_1[1] != '8') && (param_1[1] != 'X')) {
      if ((*(int *)(param_1 + 0x2e) != param_2) &&
         (iVar2 = FUN_005ac1e0(*(int *)(param_1 + 0x2e)), iVar2 != 0)) {
        *param_3 = '\x01';
      }
      if ((*(int *)(param_1 + 0x32) != param_2) &&
         (iVar2 = FUN_005ac1e0(*(int *)(param_1 + 0x32)), iVar2 != 0)) {
        *param_3 = '\x01';
      }
    }
    break;
  case 7:
    if ((*(int *)(param_1 + 0x32) != param_2) &&
       (iVar2 = FUN_005ac1e0(*(int *)(param_1 + 0x32)), iVar2 != 0)) {
      *param_3 = '\x01';
    }
    for (iVar2 = 0; *param_3 == '\0' && (iVar2 < *(short *)(param_1 + 0x2c)); iVar2 = iVar2 + 1) {
      iVar3 = *(int *)(*(int *)(param_1 + 0x2e) + iVar2 * 4);
      if ((iVar3 != param_2) && (iVar3 = FUN_005ac1e0(iVar3), iVar3 != 0)) {
        *param_3 = '\x01';
      }
    }
  }
  return;
}

/* Native 0x60bb40, 187 bytes. */
byte RewriteUse(int param_1, int param_2, int param_3, char param_4)
{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x1c) != 0) &&
     (pcVar2 = *(char **)(param_1 + 8), pcVar2 != (char *)0x0) &&
     (*pcVar2 == '\x01' && (**(char **)(pcVar2 + 0x2a) == ';'))) {
    cVar1 = FUN_00455840(*(uint *)(*(char **)(pcVar2 + 0x2a) + 0x10),
                         *(uint *)(param_2 + 0x10));
    if (cVar1 != '\0') {
      pcVar2 = (char *)IroUtil_FindNextUse(*(uint *)(param_1 + 8));
      if ((pcVar2 != (char *)0x0) && (*pcVar2 == '\x02') && (pcVar2[1] == '\x04')) {
        cVar1 = FUN_005b7e20(*(uint *)(pcVar2 + 0x12), *(uint *)(param_3 + 0x12));
        if (cVar1 != '\0') {
          pcVar3 = (char *)IroUtil_FindNextUse(pcVar2);
          if ((pcVar3 != (char *)0x0) &&
             ((*pcVar3 != '\x02' && (*pcVar3 != '\x03')) ||
             ((DAT_00725ee2)[(byte)pcVar3[1]] == '\0'))) {
            if (param_4 != '\0') {
              FUN_005acb80(pcVar2, param_3);
            }
            return 1;
          }
        }
      }
    }
  }
  return 0;
}
