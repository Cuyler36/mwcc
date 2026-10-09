#include <string.h>

/* Provisional IroBlockReordering.c architecture candidate; original filename is unproved.
 * Native membership, ABI, layout and data review is recorded in the family ledger.
 */
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef byte bool;
typedef uint code();
#define true 1
#define false 0
#pragma options align=mac68k
typedef struct ReorderContext { ushort count; ushort loops; int records; } ReorderContext;
#pragma options align=reset

extern uint DAT_00710084;
extern char *DAT_00710170;
extern uint *DAT_00710358;
extern ushort *DAT_00710990;
extern uint DAT_00710998;
extern uint DAT_00710b54;
extern code *DAT_00711b98;
extern uint DAT_00716ce0;
extern ushort DAT_007172c0;
extern char s_BitVector_h_00698a16[];
extern byte nativeEffectTemplate[306];
extern void CError_Internal();
extern uint FUN_004c53c0();
extern uint FUN_004c5480();
extern uint FUN_005a9cc0();
extern uint FUN_005ac1e0();
extern uint FUN_005ad400();
extern uint FUN_005ad440();
extern uint FUN_005ae350();
extern uint FUN_005ae7b0();
extern uint FUN_005aecc0();
extern uint FUN_005afd00();
extern uint FUN_005b07a0();
extern uint FUN_005b0990();
extern uint FUN_005bd630();
extern uint FUN_005bd690();
extern uint FUN_005be190();
extern uint FUN_005bf6c0();
extern uint FUN_005bf740();
extern uint FUN_005bf760();
extern uint FUN_005bf780();
extern uint FUN_005bf7f0();
extern uint FUN_005bf890();
extern uint FUN_005bf9d0();
extern uint FUN_005bfae0();
extern uint FUN_005c3060();
extern uint FUN_005c3330();
extern uint FUN_005c5920();
extern uint FUN_005c59c0();
extern uint FUN_005c5dd0();
extern uint FUN_005c5e00();
extern uint FUN_005ed4c0();
extern uint FUN_005f6260();

static char DAT_006b9fab[] = "%s\n";
static char DAT_006b9fb7[] = "\n";
static char s_Call_Heuristic_predicts__ld_to___006ba00f[] = "Call Heuristic predicts %ld to %ld.\n";
static char s_Guard_Heuristic_predicts__ld_to___006ba0d7[] = "Guard Heuristic predicts %ld to %ld.\n";
static char s_Loop_Branch_Heuristic_predicts___006b9fbb[] = "Loop Branch Heuristic predicts %ld to %ld.\n";
static char s_Loop_Heuristic_predicts__ld_to___006ba0af[] = "Loop Heuristic predicts %ld to %ld.\n";
static char s_Opcode_Heuristic_predicts__ld_to_006ba037[] = "Opcode Heuristic predicts %ld to %ld.\n";
static char s_Pointer_Heuristic_predicts__ld_t_006b9fe7[] = "Pointer Heuristic predicts %ld to %ld.\n";
static char s_Return_Heuristic_predicts__ld_to_006ba05f[] = "Return Heuristic predicts %ld to %ld.\n";
static char s_Store_Heuristic_predicts__ld_to___006ba087[] = "Store Heuristic predicts %ld to %ld.\n";
static char s__5ld_006b9faf[] = " %5ld\n";
static char s_new_node_ordering__006b9f97[] = "new node ordering: ";

void fn_0060bc00(void);
void fn_0060bce0(int *param_1);
void fn_0060bd80(int param_1, int param_2, int param_3);
void fn_0060be90(int param_1);
int fn_0060c190(ushort *param_1, int *param_2, int *param_3, int param_4, int param_5, int param_6);
ushort * fn_0060c9b0(ushort *param_1, int param_2, uint *param_3);
ushort * fn_0060cc30(int param_1, uint param_2, uint *param_3);
ushort * fn_0060ce40(ushort *param_1, int param_2, uint *param_3);
ushort * fn_0060d000(ushort *param_1, int param_2, uint *param_3);
void fn_0060d350(int param_1, char param_2, uint *param_3);
ushort * fn_0060d3c0(ushort *param_1, int param_2, uint *param_3);
ushort * fn_0060d630(ushort *param_1, int param_2, uint *param_3);
ushort * fn_0060d8a0(int param_1, uint param_2, uint *param_3);
ushort * fn_0060da70(ushort *param_1, int param_2, uint *param_3);
void fn_0060dbc0(ushort *param_1, ushort param_2);
void fn_0060dd40(int param_1, int param_2, ushort param_3);
void fn_0060df60(int param_1, uint *param_2, int param_3, ushort param_4);
void fn_0060e120(ushort *param_1);
void fn_0060e3d0(uint *param_1, ushort *param_2);

/* Native 0x60bc00, 219 bytes. */
void fn_0060bc00(void)
{
  byte snapshot[306];
  char *pcVar1;
  bool bVar2;
  byte *puVar3;
  int iVar4;
  byte *puVar5;
  pcVar1 = DAT_00710170;
  do {
    if (pcVar1 == (char *)0x0) {
      bVar2 = true;
LAB_0060bc21:;
      if (bVar2) {
        iVar4 = (uint)DAT_007172c0 * 8;
        puVar3 = (byte *)FUN_004c5480(iVar4);
        puVar5 = puVar3;
        memset(puVar5, 0, iVar4);
  puVar5 += iVar4;
  iVar4 = 0;
        fn_0060be90((int)(puVar3));
        fn_0060bce0((int *)(puVar3));
        FUN_004c53c0(puVar3);
      }
      return;
    }
    if ((*pcVar1 == '\x14') && (DAT_00711b98 != (code *)0x0) && (*(int *)(pcVar1 + 0x2a) != 0)) {
      memcpy(snapshot, nativeEffectTemplate, 306);
      (*DAT_00711b98)(*(uint *)(pcVar1 + 0x2a), snapshot);
      if (snapshot[7] != '\0') {
        bVar2 = false;
        goto LAB_0060bc21;
      }
    }
    pcVar1 = *(char **)(pcVar1 + 0x3e);
  } while( true );
}

/* Native 0x60bce0, 150 bytes. */
void fn_0060bce0(int *param_1)
{
  int iVar1;
  int iVar2;
  iVar2 = 0;
  iVar1 = *param_1;
  while (iVar1 != 0) {
    fn_0060bd80((int)(iVar1), (int)(*(uint *)(iVar1 + 0x30)), (int)(param_1[iVar2 + 1]));
    iVar2 = iVar2 + 1;
    iVar1 = param_1[iVar2];
  }
  iVar1 = *param_1;
  if (iVar1 == 0) {
    DAT_00710170 = 0;
    DAT_00716ce0 = 0;
  }
  else {
    DAT_00710170 = (char *)*(uint *)(iVar1 + 0x10);
    DAT_00716ce0 = *(int *)(iVar1 + 0x14);
    iVar2 = 1;
    iVar1 = param_1[1];
    while (iVar1 != 0) {
      iVar2 = iVar2 + 1;
      *(uint *)(DAT_00716ce0 + 0x3e) = *(uint *)(iVar1 + 0x10);
      DAT_00716ce0 = *(int *)(iVar1 + 0x14);
      iVar1 = param_1[iVar2];
    }
    if (DAT_00716ce0 != 0) {
      *(uint *)(DAT_00716ce0 + 0x3e) = 0;
    }
  }
  FUN_005be190(DAT_00710170);
  return;
}

/* Native 0x60bd80, 260 bytes. */
void fn_0060bd80(int param_1, int param_2, int param_3)
{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  if (param_2 == 0) {
LAB_0060be74:;
    param_2 = 0;
  }
  else {
    cVar3 = FUN_005bd690(param_1, param_2);
    if (cVar3 == '\0') goto LAB_0060be74;
  }
  if ((param_2 != 0) && (param_2 != param_3)) {
    if ((*(char **)(param_2 + 0x10) != (char *)0x0) && (**(char **)(param_2 + 0x10) != '\r')) {
      iVar4 = FUN_005a9cc0();
      *(int *)(iVar4 + 4) = param_2;
      iVar5 = FUN_005bd630(0xd);
      *(int *)(iVar5 + 10) = DAT_00710998;
      DAT_00710998 = DAT_00710998 + 1;
      *(int *)(iVar5 + 0x2a) = iVar4;
      *(uint *)(iVar5 + 2) = *(uint *)(iVar5 + 2) | 1;
      FUN_005ad440(iVar5, iVar5, *(uint *)(param_2 + 0x10));
    }
    iVar4 = FUN_005bd630(8);
    *(int *)(iVar4 + 10) = DAT_00710998;
    DAT_00710998 = DAT_00710998 + 1;
    *(uint *)(iVar4 + 0x2a) = *(uint *)(*(int *)(param_2 + 0x10) + 0x2a);
    FUN_005ad400(iVar4, iVar4, *(uint *)(param_1 + 0x14));
  }
  if (param_3 != 0) {
    cVar3 = FUN_005bd690(param_1, param_3);
    if (cVar3 != '\0') goto LAB_0060be32;
  }
  param_3 = 0;
LAB_0060be32:;
  if ((param_3 != 0) && (pcVar1 = *(char **)(param_1 + 0x14), pcVar1 != (char *)0x0) &&
     (*pcVar1 == '\b') &&
     (pcVar2 = *(char **)(param_3 + 0x10), pcVar2 != (char *)0x0 && (*pcVar2 == '\r') &&
     (*(int *)(pcVar1 + 0x2a) == *(int *)(pcVar2 + 0x2a)))) {
    if (*(short *)(param_3 + 8) == 1) {
      FUN_005ae7b0(pcVar2);
    }
    FUN_005ae7b0(*(uint *)(param_1 + 0x14));
  }
  return;
}

/* Native 0x60be90, 756 bytes. */
void fn_0060be90(int param_1)
{
  int *piVar1;
  ushort *puVar2;
  int iVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  byte *puVar10;
  ReorderContext context;
  byte *local_20;
  uint local_1c;
  uint *local_18;
  uint *local_14;
  uVar5 = (uint)DAT_007172c0;
  local_1c = uVar5 * 2;
  iVar8 = uVar5 * 4;
  local_20 = (byte *)FUN_004c5480(iVar8);
  puVar10 = local_20;
  memset(puVar10, 0, iVar8);
  puVar10 += iVar8;
  iVar8 = 0;
  local_14 = (uint *)FUN_004c5480(0x14);
  local_18 = (uint *)FUN_004c5480(0x14);
  sVar7 = 1;
  for (puVar2 = DAT_00710990; puVar2 != (ushort *)0x0; puVar2 = *(ushort **)(puVar2 + 0x18)) {
    *(short *)(local_20 + (uint)*puVar2 * 2) = sVar7;
    sVar7 = sVar7 + 1;
  }
  *local_14 = 0;
  local_14[1] = 0;
  local_14[2] = local_1c;
  iVar8 = uVar5 * 0x18;
  uVar6 = FUN_004c5480(iVar8);
  local_14[3] = uVar6;
  puVar10 = (byte *)local_14[3];
  for (iVar9 = iVar8; iVar9 != 0; iVar9 = iVar9 - 1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  local_14[4] = (uint)local_20;
  *local_18 = 0;
  local_18[1] = 0;
  local_18[2] = local_1c;
  uVar6 = FUN_004c5480(iVar8);
  local_18[3] = uVar6;
  puVar10 = (byte *)local_18[3];
  memset(puVar10, 0, iVar8);
  puVar10 += iVar8;
  iVar8 = 0;
  local_18[4] = (uint)local_20;
  fn_0060dbc0((ushort *)((&context)), (ushort)(local_1c & 0xffff));
  for (puVar2 = DAT_00710990; puVar2 != (ushort *)0x0; puVar2 = *(ushort **)(puVar2 + 0x18)) {
    *(byte *)((int)puVar2 + 0x3d) = 0;
  }
  iVar8 = fn_0060c190((ushort *)(DAT_00710990), (int *)(local_14), (int *)(local_18), (int)((&context)), (int)(param_1), (int)(0));
  local_1c = 0;
  if (context.count != 0) {
    iVar9 = 0;
    do {
      if (*(int *)(context.records + iVar9) != 0) {
        piVar1 = (int *)(iVar9 + context.records);
        iVar3 = *piVar1;
        if (iVar3 != 0) {
          FUN_004c53c0(iVar3);
          *piVar1 = 0;
        }
      }
      if (*(int *)(context.records + 4 + iVar9) != 0) {
        piVar1 = (int *)(iVar9 + 4 + context.records);
        iVar3 = *piVar1;
        if (iVar3 != 0) {
          FUN_004c53c0(iVar3);
          *piVar1 = 0;
        }
      }
      iVar9 = iVar9 + 0xe;
      local_1c = local_1c + 1;
    } while ((ushort)local_1c < context.count);
  }
  FUN_004c53c0(context.records);
  context.records = 0;
  context.count = 0;
  local_18[4] = 0;
  FUN_004c53c0(local_18[3]);
  local_18[3] = 0;
  local_18[2] = 0;
  local_18[1] = 0;
  *local_18 = 0;
  local_14[4] = 0;
  FUN_004c53c0(local_14[3]);
  local_14[3] = 0;
  local_14[2] = 0;
  local_14[1] = 0;
  *local_14 = 0;
  FUN_004c53c0(local_18);
  FUN_004c53c0(local_14);
  FUN_004c53c0(local_20);
  for (puVar2 = DAT_00710990; puVar2 != (ushort *)0x0; puVar2 = *(ushort **)(puVar2 + 0x18)) {
    if (*(char *)((int)puVar2 + 0x3d) == '\0') {
      *(ushort **)(param_1 + iVar8 * 4) = puVar2;
      iVar8 = iVar8 + 1;
      *(byte *)((int)puVar2 + 0x3d) = 1;
    }
  }
  FUN_005ed4c0(DAT_006b9fab, s_new_node_ordering__006b9f97);
  uVar5 = (uint)DAT_007172c0;
  iVar8 = 0;
  if (uVar5 != 0) {
    do {
      puVar4 = *(ushort **)(param_1 + iVar8 * 4);
      if (puVar4 != (ushort *)0x0) {
        FUN_005ed4c0(s__5ld_006b9faf, *puVar4);
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < (int)(uVar5 * 2));
  }
  FUN_005ed4c0(DAT_006b9fb7);
  return;
}

/* Native 0x60c190, 2072 bytes. */
int fn_0060c190(ushort *param_1, int *param_2, int *param_3, int param_4, int param_5, int param_6)
{
  char cVar1;
  ushort *puVar2;
  uint *puVar3;
  bool bVar4;
  ushort uVar5;
  ushort uVar6;
  short sVar7;
  uint uVar8;
  ushort *local_2c;
  ushort *local_14;
  do {
    sVar7 = 0;
    local_2c = (ushort *)0x0;
    uVar5 = 0;
    if (param_1[1] != 0) {
      do {
        puVar2 = *(ushort **)
                  (DAT_00710b54 + (uint)*(ushort *)(*(int *)(param_1 + 2) + (uint)uVar5 * 2) * 4);
        if (*(char *)((int)puVar2 + 0x3d) == '\0') {
          bVar4 = false;
          uVar8 = (uint)(*param_1 >> 5);
          if ((uVar8 < **(uint **)(puVar2 + 0x16)) &&
             (((*(uint **)(puVar2 + 0x16))[uVar8 + 1] & 1 << ((byte)*param_1 & 0x1f)) != 0)) {
            bVar4 = true;
          }
          if (bVar4) {
            sVar7 = sVar7 + 1;
            local_2c = puVar2;
          }
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < param_1[1]);
    }
    cVar1 = *(char *)(*(int *)(param_4 + 4) + 9 + (uint)*param_1 * 0xe);
    if ((cVar1 == '\0') && (sVar7 == 0)) {
      if (*(char *)((int)param_1 + 0x3d) == '\0') {
        *(ushort **)(param_5 + param_6 * 4) = param_1;
        param_6 = param_6 + 1;
        *(byte *)((int)param_1 + 0x3d) = 1;
      }
      uVar6 = 0;
      uVar5 = 0;
      if (param_1[1] != 0) {
        do {
          puVar2 = *(ushort **)
                    (DAT_00710b54 + (uint)*(ushort *)(*(int *)(param_1 + 2) + (uint)uVar6 * 2) * 4);
          if ((puVar2 != (ushort *)0x0) && (*(char *)((int)puVar2 + 0x3d) == '\0')) {
            if ((*(char *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) == '\0') &&
               (*(char *)(*(int *)(param_4 + 4) + 0xd + (uint)*puVar2 * 0xe) == '\0')) {
              fn_0060e3d0((uint *)(param_2), (ushort *)(puVar2));
              *(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) = 1;
            }
          }
          uVar6 = uVar6 + 1;
          uVar5 = param_1[1];
        } while (uVar6 < uVar5);
      }
      uVar6 = 0;
      sVar7 = 0;
      if (uVar5 != 0) {
        do {
          puVar2 = *(ushort **)
                    (DAT_00710b54 + (uint)*(ushort *)(*(int *)(param_1 + 2) + (uint)uVar6 * 2) * 4);
          if (*(char *)((int)puVar2 + 0x3d) == '\0') {
            sVar7 = sVar7 + 1;
            local_2c = puVar2;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < uVar5);
      }
      if (sVar7 == 1) {
        sVar7 = 0;
        uVar5 = 0;
        if (local_2c[4] != 0) {
          sVar7 = 0;
          do {
            if (*(char *)(*(int *)(DAT_00710b54 +
                                  (uint)*(ushort *)(*(int *)(local_2c + 5) + (uint)uVar5 * 2) * 4) +
                         0x3d) == '\0') {
              sVar7 = sVar7 + 1;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < local_2c[4]);
        }
        if (sVar7 == 0) goto LAB_0060c389;
      }
LAB_0060c317:;
      do {
        puVar3 = (uint *)*param_2;
        if (puVar3 == (uint *)0x0) {
          local_2c = (ushort *)0x0;
        }
        else {
          *param_2 = puVar3[1];
          if (*param_2 == 0) {
            param_2[1] = 0;
          }
          else {
            *(uint *)(*param_2 + 8) = 0;
          }
          local_2c = (ushort *)*puVar3;
          *puVar3 = 0;
          puVar3[1] = 0;
          puVar3[2] = 0;
        }
      } while ((local_2c != (ushort *)0x0) &&
              (*(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*local_2c * 0xe) = 0,
              *(char *)((int)local_2c + 0x3d) == '\x01'));
      if (local_2c == (ushort *)0x0) {
        do {
          puVar3 = (uint *)*param_3;
          if (puVar3 == (uint *)0x0) {
            local_2c = (ushort *)0x0;
          }
          else {
            *param_3 = puVar3[1];
            if (*param_3 == 0) {
              param_3[1] = 0;
            }
            else {
              *(uint *)(*param_3 + 8) = 0;
            }
            local_2c = (ushort *)*puVar3;
            *puVar3 = 0;
            puVar3[1] = 0;
            puVar3[2] = 0;
          }
        } while ((local_2c != (ushort *)0x0) &&
                (*(byte *)(*(int *)(param_4 + 4) + 0xd + (uint)*local_2c * 0xe) = 0,
                *(char *)((int)local_2c + 0x3d) == '\x01'));
        if (param_1 == local_2c) {
          if (*(char *)((int)param_1 + 0x3d) == '\0') {
            *(ushort **)(param_5 + param_6 * 4) = param_1;
            param_6 = param_6 + 1;
            *(byte *)((int)param_1 + 0x3d) = 1;
          }
          uVar5 = 0;
          if (param_1[1] != 0) {
            do {
              puVar2 = *(ushort **)
                        (DAT_00710b54 +
                        (uint)*(ushort *)(*(int *)(param_1 + 2) + (uint)uVar5 * 2) * 4);
              if ((puVar2 != (ushort *)0x0) && (*(char *)((int)puVar2 + 0x3d) == '\0')) {
                if ((*(char *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) == '\0') &&
                   (*(char *)(*(int *)(param_4 + 4) + 0xd + (uint)*puVar2 * 0xe) == '\0')) {
                  fn_0060e3d0((uint *)(param_2), (ushort *)(puVar2));
                  *(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) = 1;
                }
              }
              uVar5 = uVar5 + 1;
            } while (uVar5 < param_1[1]);
          }
          puVar3 = (uint *)*param_3;
          if (puVar3 == (uint *)0x0) {
            local_2c = (ushort *)0x0;
          }
          else {
            *param_3 = puVar3[1];
            if (*param_3 == 0) {
              param_3[1] = 0;
            }
            else {
              *(uint *)(*param_3 + 8) = 0;
            }
            local_2c = (ushort *)*puVar3;
            *puVar3 = 0;
            puVar3[1] = 0;
            puVar3[2] = 0;
          }
          if (local_2c != (ushort *)0x0) {
            *(byte *)(*(int *)(param_4 + 4) + 0xd + (uint)*local_2c * 0xe) = 0;
          }
        }
      }
      else if (param_1 == local_2c) {
        if (*(char *)((int)param_1 + 0x3d) == '\0') {
          *(ushort **)(param_5 + param_6 * 4) = param_1;
          param_6 = param_6 + 1;
          *(byte *)((int)param_1 + 0x3d) = 1;
        }
        uVar5 = 0;
        if (param_1[1] != 0) {
          do {
            puVar2 = *(ushort **)
                      (DAT_00710b54 + (uint)*(ushort *)(*(int *)(param_1 + 2) + (uint)uVar5 * 2) * 4
                      );
            if ((puVar2 != (ushort *)0x0) && (*(char *)((int)puVar2 + 0x3d) == '\0')) {
              if ((*(char *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) == '\0') &&
                 (*(char *)(*(int *)(param_4 + 4) + 0xd + (uint)*puVar2 * 0xe) == '\0')) {
                fn_0060e3d0((uint *)(param_2), (ushort *)(puVar2));
                *(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) = 1;
              }
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < param_1[1]);
        }
        puVar3 = (uint *)*param_2;
        if (puVar3 == (uint *)0x0) {
          local_2c = (ushort *)0x0;
        }
        else {
          *param_2 = puVar3[1];
          if (*param_2 == 0) {
            param_2[1] = 0;
          }
          else {
            *(uint *)(*param_2 + 8) = 0;
          }
          local_2c = (ushort *)*puVar3;
          *puVar3 = 0;
          puVar3[1] = 0;
          puVar3[2] = 0;
        }
        if (local_2c != (ushort *)0x0) {
          *(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*local_2c * 0xe) = 0;
        }
      }
    }
    else {
      if ((cVar1 != '\0') || (sVar7 != 1)) {
        if ((cVar1 == '\0') &&
           (local_2c = (ushort *)fn_0060c9b0((ushort *)(param_1), (int)(param_4), (uint *)(&local_14)),
           local_2c != (ushort *)0x0)) {
          if (param_1 == local_2c) {
            if (*(char *)((int)param_1 + 0x3d) == '\0') {
              *(ushort **)(param_5 + param_6 * 4) = param_1;
              param_6 = param_6 + 1;
              *(byte *)((int)param_1 + 0x3d) = 1;
            }
            cVar1 = *(char *)((int)local_14 + 0x3d);
            local_2c = local_14;
          }
          else {
            if (*(char *)((int)local_14 + 0x3d) == '\0') {
              if ((*(char *)(*(int *)(param_4 + 4) + 0xc + (uint)*local_14 * 0xe) == '\0') &&
                 (*(char *)(*(int *)(param_4 + 4) + 0xd + (uint)*local_14 * 0xe) == '\0')) {
                fn_0060e3d0((uint *)(param_3), (ushort *)(local_14));
                *(byte *)(*(int *)(param_4 + 4) + 0xd + (uint)*local_14 * 0xe) = 1;
              }
            }
            if (*(char *)((int)param_1 + 0x3d) == '\0') {
              *(ushort **)(param_5 + param_6 * 4) = param_1;
              param_6 = param_6 + 1;
              *(byte *)((int)param_1 + 0x3d) = 1;
            }
            uVar5 = 0;
            if (param_1[1] != 0) {
              do {
                puVar2 = *(ushort **)
                          (DAT_00710b54 +
                          (uint)*(ushort *)(*(int *)(param_1 + 2) + (uint)uVar5 * 2) * 4);
                if ((puVar2 != local_2c) && (*(char *)((int)puVar2 + 0x3d) == '\0')) {
                  if ((*(char *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) == '\0') &&
                     (*(char *)(*(int *)(param_4 + 4) + 0xd + (uint)*puVar2 * 0xe) == '\0')) {
                    fn_0060e3d0((uint *)(param_2), (ushort *)(puVar2));
                    *(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) = 1;
                  }
                }
                uVar5 = uVar5 + 1;
              } while (uVar5 < param_1[1]);
            }
            cVar1 = *(char *)((int)local_2c + 0x3d);
          }
          if (cVar1 == '\0') goto LAB_0060c389;
        }
        else {
          if ((*(char *)(*(int *)(param_4 + 4) + 0xc + (uint)*param_1 * 0xe) == '\0') &&
             (*(char *)(*(int *)(param_4 + 4) + 0xd + (uint)*param_1 * 0xe) == '\0')) {
            fn_0060e3d0((uint *)(param_2), (ushort *)(param_1));
            *(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*param_1 * 0xe) = 1;
          }
          uVar5 = 0;
          if (param_1[1] != 0) {
            do {
              puVar2 = *(ushort **)
                        (DAT_00710b54 +
                        (uint)*(ushort *)(*(int *)(param_1 + 2) + (uint)uVar5 * 2) * 4);
              if ((puVar2 != (ushort *)0x0) && (*(char *)((int)puVar2 + 0x3d) == '\0')) {
                if ((*(char *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) == '\0') &&
                   (*(char *)(*(int *)(param_4 + 4) + 0xd + (uint)*puVar2 * 0xe) == '\0')) {
                  fn_0060e3d0((uint *)(param_2), (ushort *)(puVar2));
                  *(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) = 1;
                }
              }
              uVar5 = uVar5 + 1;
            } while (uVar5 < param_1[1]);
          }
        }
        goto LAB_0060c317;
      }
      if (*(char *)((int)param_1 + 0x3d) == '\0') {
        *(ushort **)(param_5 + param_6 * 4) = param_1;
        param_6 = param_6 + 1;
        *(byte *)((int)param_1 + 0x3d) = 1;
      }
      uVar5 = 0;
      if (param_1[1] != 0) {
        do {
          puVar2 = *(ushort **)
                    (DAT_00710b54 + (uint)*(ushort *)(*(int *)(param_1 + 2) + (uint)uVar5 * 2) * 4);
          if ((puVar2 != local_2c) && (*(char *)((int)puVar2 + 0x3d) == '\0')) {
            if ((*(char *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) == '\0') &&
               (*(char *)(*(int *)(param_4 + 4) + 0xd + (uint)*puVar2 * 0xe) == '\0')) {
              fn_0060e3d0((uint *)(param_2), (ushort *)(puVar2));
              *(byte *)(*(int *)(param_4 + 4) + 0xc + (uint)*puVar2 * 0xe) = 1;
            }
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < param_1[1]);
      }
      if (*(char *)((int)local_2c + 0x3d) != '\0') goto LAB_0060c317;
    }
LAB_0060c389:;
    param_1 = local_2c;
    if (local_2c == (ushort *)0x0) {
      return param_6;
    }
  } while( true );
}

/* Native 0x60c9b0, 626 bytes. */
ushort * fn_0060c9b0(ushort *param_1, int param_2, uint *param_3)
{
  ushort *puVar1;
  int iVar2;
  ushort *puVar3;
  ushort *puVar4;
  char local_18;
  char local_11;
  *param_3 = 0;
  puVar4 = (ushort *)fn_0060da70((ushort *)(param_1), (int)(param_2), (uint *)(param_3));
  if (puVar4 != (ushort *)0x0) {
    FUN_005ed4c0(s_Loop_Branch_Heuristic_predicts___006b9fbb, *param_1, *puVar4);
    return puVar4;
  }
  puVar4 = (ushort *)fn_0060cc30((int)(param_1), (uint)(param_2), (uint *)(param_3));
  if (puVar4 != (ushort *)0x0) {
    FUN_005ed4c0(s_Pointer_Heuristic_predicts__ld_t_006b9fe7, *param_1, *puVar4);
    return puVar4;
  }
  puVar4 = (ushort *)fn_0060d3c0((ushort *)(param_1), (int)(param_2), (uint *)(param_3));
  if (puVar4 != (ushort *)0x0) {
    FUN_005ed4c0(s_Call_Heuristic_predicts__ld_to___006ba00f, *param_1, *puVar4);
    return puVar4;
  }
  puVar4 = (ushort *)fn_0060d8a0((int)(param_1), (uint)(param_2), (uint *)(param_3));
  if (puVar4 != (ushort *)0x0) {
    FUN_005ed4c0(s_Opcode_Heuristic_predicts__ld_to_006ba037, *param_1, *puVar4);
    return puVar4;
  }
  if (param_1[1] == 2) {
    puVar4 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(param_1 + 2) * 4);
    puVar1 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 2))[1] * 4);
    local_18 = '\x01';
    iVar2 = *(int *)(param_2 + 4);
    if ((*(char *)(iVar2 + 0xb + (uint)*puVar4 * 0xe) == '\0') &&
       (puVar4[1] != 1 ||
       (puVar3 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(puVar4 + 2) * 4),
       puVar3 == (ushort *)0x0) || (*(char *)(iVar2 + 0xb + (uint)*puVar3 * 0xe) == '\0'))) {
      local_18 = '\0';
    }
    local_11 = '\x01';
    if ((*(char *)(iVar2 + 0xb + (uint)*puVar1 * 0xe) == '\0') &&
       (puVar1[1] != 1 ||
       (puVar3 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(puVar1 + 2) * 4),
       puVar3 == (ushort *)0x0) || (*(char *)(iVar2 + 0xb + (uint)*puVar3 * 0xe) == '\0'))) {
      local_11 = '\0';
    }
    if (local_18 != local_11) {
      if (local_18 == '\0') {
        *param_3 = (uint)puVar1;
      }
      else {
        *param_3 = (uint)puVar4;
        puVar4 = puVar1;
      }
      goto LAB_0060cb64;
    }
  }
  puVar4 = (ushort *)0x0;
LAB_0060cb64:;
  if (puVar4 != (ushort *)0x0) {
    FUN_005ed4c0(s_Return_Heuristic_predicts__ld_to_006ba05f, *param_1, *puVar4);
    return puVar4;
  }
  puVar4 = (ushort *)fn_0060ce40((ushort *)(param_1), (int)(param_2), (uint *)(param_3));
  if (puVar4 != (ushort *)0x0) {
    FUN_005ed4c0(s_Store_Heuristic_predicts__ld_to___006ba087, *param_1, *puVar4);
    return puVar4;
  }
  puVar4 = (ushort *)fn_0060d630((ushort *)(param_1), (int)(param_2), (uint *)(param_3));
  if (puVar4 != (ushort *)0x0) {
    FUN_005ed4c0(s_Loop_Heuristic_predicts__ld_to___006ba0af, *param_1, *puVar4);
    return puVar4;
  }
  puVar4 = (ushort *)fn_0060d000((ushort *)(param_1), (int)(param_2), (uint *)(param_3));
  if (puVar4 != (ushort *)0x0) {
    FUN_005ed4c0(s_Guard_Heuristic_predicts__ld_to___006ba0d7, *param_1, *puVar4);
    return puVar4;
  }
  return (ushort *)0x0;
}

/* Native 0x60cc30, 522 bytes. */
ushort * fn_0060cc30(int param_1, uint param_2, uint *param_3)
{
  char cVar1;
  char cVar2;
  ushort uVar3;
  char *pcVar4;
  ushort *puVar5;
  int iVar6;
  char cVar7;
  int iVar8;
  ushort *puVar9;
  pcVar4 = *(char **)(param_1 + 0x14);
  if ((pcVar4 != (char *)0x0) && (cVar1 = *pcVar4, cVar1 == '\n' || (cVar1 == '\v'))) {
    pcVar4 = *(char **)(pcVar4 + 0x2e);
    cVar2 = pcVar4[1];
    puVar5 = *(ushort **)(param_1 + 0x30);
    uVar3 = **(ushort **)(param_1 + 4);
    if (uVar3 == *puVar5) {
      puVar9 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 4))[1] * 4);
    }
    else {
      puVar9 = *(ushort **)(DAT_00710b54 + (uint)uVar3 * 4);
    }
    if (*pcVar4 == '\x03') {
      iVar8 = *(int *)(pcVar4 + 0x2a);
      iVar6 = *(int *)(pcVar4 + 0x2e);
      if ((**(char **)(iVar8 + 0x12) == '\f') || (**(char **)(iVar6 + 0x12) == '\f')) {
        cVar7 = FUN_005afd00(iVar8, iVar6);
        if ((cVar7 == '\0') ||
           (iVar8 = FUN_005ac1e0(iVar8), iVar8 != 0 || (iVar8 = FUN_005ac1e0(iVar6), iVar8 != 0))) {
          if (cVar2 == '\x17') {
            if (cVar1 != '\n') {
              *param_3 = (uint)puVar5;
              return puVar9;
            }
            *param_3 = (uint)puVar9;
            return puVar5;
          }
          if (cVar2 == '\x18') {
            if (cVar1 != '\n') {
              *param_3 = (uint)puVar9;
              return puVar5;
            }
            *param_3 = (uint)puVar5;
            return puVar9;
          }
        }
        else {
          if (cVar2 == '\x17') {
            if (cVar1 != '\n') {
              *param_3 = (uint)puVar9;
              return puVar5;
            }
            *param_3 = (uint)puVar5;
            return puVar9;
          }
          if (cVar2 == '\x18') {
            if (cVar1 != '\n') {
              *param_3 = (uint)puVar5;
              return puVar9;
            }
            *param_3 = (uint)puVar9;
            return puVar5;
          }
        }
      }
    }
    else if (*pcVar4 == '\x02') {
      if ((cVar2 == '\a') && (iVar8 = *(int *)(pcVar4 + 0x2a), iVar8 != 0) &&
         (**(char **)(iVar8 + 0x12) == '\f') && (iVar8 = FUN_005b0990(iVar8), iVar8 != 0)) {
        if (cVar1 != '\n') {
          *param_3 = (uint)puVar5;
          return puVar9;
        }
        *param_3 = (uint)puVar9;
        return puVar5;
      }
      if ((**(char **)(pcVar4 + 0x12) == '\f') && (iVar8 = FUN_005b0990(pcVar4), iVar8 != 0)) {
        if (cVar1 != '\n') {
          *param_3 = (uint)puVar9;
          return puVar5;
        }
        *param_3 = (uint)puVar5;
        return puVar9;
      }
    }
  }
  return (ushort *)0x0;
}

/* Native 0x60ce40, 442 bytes. */
ushort * fn_0060ce40(ushort *param_1, int param_2, uint *param_3)
{
  ushort *puVar1;
  ushort *puVar2;
  uint *puVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  char cVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  if (param_1[1] == 2) {
    puVar1 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(param_1 + 2) * 4);
    puVar2 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 2))[1] * 4);
    puVar3 = *(uint **)(*(int *)(param_2 + 4) + (uint)*param_1 * 0xe);
    bVar7 = false;
    uVar10 = (uint)(*puVar1 >> 5);
    if ((uVar10 < *puVar3) && ((puVar3[uVar10 + 1] & 1 << ((byte)*puVar1 & 0x1f)) != 0)) {
      bVar7 = true;
    }
    bVar4 = false;
    uVar10 = (uint)(*puVar2 >> 5);
    if ((uVar10 < *puVar3) && ((puVar3[uVar10 + 1] & 1 << ((byte)*puVar2 & 0x1f)) != 0)) {
      bVar4 = true;
    }
    bVar5 = false;
    iVar11 = *(int *)(puVar1 + 8);
    if ((iVar11 != 0) && (*(int *)(puVar1 + 10) != 0) &&
       (iVar11 != *(int *)(*(int *)(puVar1 + 10) + 0x3e))) {
      do {
        cVar8 = FUN_005b07a0(iVar11);
        if ((cVar8 != '\0') && (*(int *)(iVar11 + 0x2a) != 0) &&
           (iVar9 = FUN_005b0990(*(int *)(iVar11 + 0x2a)), iVar9 == 0 ||
           (*(char *)(iVar9 + 2) != '\x01' || (*(int *)(iVar9 + 0x40) == 0)) ||
           (*(char *)(*(int *)(iVar9 + 0x40) + 8) != '\0'))) {
          bVar5 = true;
          break;
        }
        iVar11 = *(int *)(iVar11 + 0x3e);
      } while (iVar11 != *(int *)(*(int *)(puVar1 + 10) + 0x3e));
    }
    bVar6 = false;
    iVar11 = *(int *)(puVar2 + 8);
    if ((iVar11 != 0) && (*(int *)(puVar2 + 10) != 0) &&
       (iVar11 != *(int *)(*(int *)(puVar2 + 10) + 0x3e))) {
      do {
        cVar8 = FUN_005b07a0(iVar11);
        if ((cVar8 != '\0') && (*(int *)(iVar11 + 0x2a) != 0) &&
           (iVar9 = FUN_005b0990(*(int *)(iVar11 + 0x2a)), iVar9 == 0 ||
           (*(char *)(iVar9 + 2) != '\x01' || (*(int *)(iVar9 + 0x40) == 0)) ||
           (*(char *)(*(int *)(iVar9 + 0x40) + 8) != '\0'))) {
          bVar6 = true;
          break;
        }
        iVar11 = *(int *)(iVar11 + 0x3e);
      } while (iVar11 != *(int *)(*(int *)(puVar2 + 10) + 0x3e));
    }
    if ((bVar7) || (!bVar5)) {
      if ((!bVar4) && (bVar6)) {
        *param_3 = (uint)puVar2;
        return puVar1;
      }
    }
    else if ((bVar4) || (!bVar6)) {
      *param_3 = (uint)puVar1;
      return puVar2;
    }
  }
  return (ushort *)0x0;
}

/* Native 0x60d000, 848 bytes. */
ushort * fn_0060d000(ushort *param_1, int param_2, uint *param_3)
{
  char *pcVar1;
  uint *puVar2;
  bool bVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint *local_30;
  uint *local_2c;
  char local_25;
  uint local_24;
  uint local_20;
  uint local_1c;
  ushort *local_18;
  ushort *local_14;
  pcVar1 = *(char **)(param_1 + 10);
  if ((pcVar1 != (char *)0x0) && (*pcVar1 == '\n' || (*pcVar1 == '\v'))) {
    local_1c = *(uint *)(pcVar1 + 0x2e);
    local_14 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(param_1 + 2) * 4);
    local_18 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 2))[1] * 4);
    puVar2 = *(uint **)(*(int *)(param_2 + 4) + (uint)*param_1 * 0xe);
    local_24 = 0;
    uVar8 = (uint)(*local_14 >> 5);
    if ((uVar8 < *puVar2) && ((puVar2[uVar8 + 1] & 1 << ((byte)*local_14 & 0x1f)) != 0)) {
      local_24 = 1;
    }
    uVar8 = (uint)(*local_18 >> 5);
    local_20 = 0;
    if ((uVar8 < *puVar2) && ((puVar2[uVar8 + 1] & 1 << ((byte)*local_18 & 0x1f)) != 0)) {
      local_20 = 1;
    }
    FUN_005bfae0(&local_30, DAT_00710084 + 1);
    local_2c = DAT_00710358;
    FUN_005bfae0(&DAT_00710358, DAT_00710084 + 1);
    FUN_005ae350(local_1c, &fn_0060d350, local_30);
    local_25 = '\0';
    iVar6 = *(int *)(local_14 + 8);
    if ((iVar6 != 0) && (*(int *)(local_14 + 10) != 0) &&
       (iVar6 != *(int *)(*(int *)(local_14 + 10) + 0x3e))) {
      do {
        FUN_005f6260(iVar6);
        iVar4 = FUN_005b0990(iVar6);
        if ((iVar4 != 0) &&
           ((*(uint *)(iVar6 + 2) & 4) == 0 || ((*(uint *)(iVar6 + 2) & 0x10) != 0)) &&
           (*(uint **)(iVar4 + 0x20) != (uint *)0x0)) {
          uVar8 = **(uint **)(iVar4 + 0x20);
          bVar3 = false;
          uVar7 = uVar8 >> 5;
          bVar5 = (byte)uVar8;
          if ((uVar7 < *local_30) && ((local_30[uVar7 + 1] & 1 << (bVar5 & 0x1f)) != 0)) {
            bVar3 = true;
          }
          if ((bVar3) &&
             (*DAT_00710358 <= uVar7 || ((DAT_00710358[uVar7 + 1] & 1 << (bVar5 & 0x1f)) == 0))) {
            local_25 = '\x01';
            break;
          }
        }
        iVar6 = *(int *)(iVar6 + 0x3e);
      } while (iVar6 != *(int *)(*(int *)(local_14 + 10) + 0x3e));
    }
    FUN_005bf760(DAT_00710358);
    local_1c = 0;
    iVar6 = *(int *)(local_18 + 8);
    if ((iVar6 != 0) && (*(int *)(local_18 + 10) != 0) &&
       (iVar6 != *(int *)(*(int *)(local_18 + 10) + 0x3e))) {
      do {
        FUN_005f6260(iVar6);
        iVar4 = FUN_005b0990(iVar6);
        if ((iVar4 != 0) &&
           ((*(uint *)(iVar6 + 2) & 4) == 0 || ((*(uint *)(iVar6 + 2) & 0x10) != 0)) &&
           (*(uint **)(iVar4 + 0x20) != (uint *)0x0)) {
          uVar8 = **(uint **)(iVar4 + 0x20);
          bVar3 = false;
          uVar7 = uVar8 >> 5;
          bVar5 = (byte)uVar8;
          if ((uVar7 < *local_30) && ((local_30[uVar7 + 1] & 1 << (bVar5 & 0x1f)) != 0)) {
            bVar3 = true;
          }
          if ((bVar3) &&
             (*DAT_00710358 <= uVar7 || ((DAT_00710358[uVar7 + 1] & 1 << (bVar5 & 0x1f)) == 0))) {
            local_1c = 1;
            break;
          }
        }
        iVar6 = *(int *)(iVar6 + 0x3e);
      } while (iVar6 != *(int *)(*(int *)(local_18 + 10) + 0x3e));
    }
    if (DAT_00710358 != (uint *)0x0) {
      FUN_004c53c0(DAT_00710358);
    }
    DAT_00710358 = local_2c;
    if (local_30 != (uint *)0x0) {
      FUN_004c53c0(local_30);
    }
    if (((char)local_24 == '\0') && (local_25 != '\0')) {
      if (((char)local_20 != '\0') || ((char)local_1c == '\0')) {
        *param_3 = (uint)local_18;
        return local_14;
      }
    }
    else if (((char)local_20 == '\0') && ((char)local_1c != '\0')) {
      *param_3 = (uint)local_14;
      return local_18;
    }
  }
  return (ushort *)0x0;
}

/* Native 0x60d350, 97 bytes. */
void fn_0060d350(int param_1, char param_2, uint *param_3)
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  if (param_2 != '\0') {
    iVar2 = FUN_005b0990(param_1);
    if ((iVar2 != 0) &&
       (((*(uint *)(param_1 + 2) & 4) == 0 || ((*(uint *)(param_1 + 2) & 0x10) != 0)) &&
       (*(uint **)(iVar2 + 0x20) != (uint *)0x0))) {
      uVar1 = **(uint **)(iVar2 + 0x20);
      uVar3 = uVar1 >> 5;
      if (uVar3 < *param_3) {
        param_3[uVar3 + 1] = param_3[uVar3 + 1] | 1 << ((byte)uVar1 & 0x1f);
      }
      else {
        CError_Internal(s_BitVector_h_00698a16, 0x52);
      }
    }
  }
  return;
}

/* Native 0x60d3c0, 618 bytes. */
ushort * fn_0060d3c0(ushort *param_1, int param_2, uint *param_3)
{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort *puVar4;
  int iVar5;
  uint *puVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  ushort *unaff_ESI;
  char local_24;
  char local_18;
  if (param_1[1] == 2) {
    puVar3 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(param_1 + 2) * 4);
    puVar4 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 2))[1] * 4);
    local_24 = '\x01';
    uVar1 = *puVar3;
    iVar5 = *(int *)(param_2 + 4);
    if (*(char *)(iVar5 + 10 + (uint)uVar1 * 0xe) == '\0') {
      bVar9 = false;
      bVar8 = false;
      if ((puVar3[1] == 1) &&
         (unaff_ESI = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(puVar3 + 2) * 4),
         unaff_ESI != (ushort *)0x0)) {
        bVar7 = false;
        if (((uint)(uVar1 >> 5) < **(uint **)(unaff_ESI + 0x16)) &&
           (((*(uint **)(unaff_ESI + 0x16))[(uVar1 >> 5) + 1] & 1 << ((byte)uVar1 & 0x1f)) != 0)) {
          bVar7 = true;
        }
        if (bVar7) {
          bVar8 = true;
        }
      }
      if ((bVar8) && (*(char *)(iVar5 + 10 + (uint)*unaff_ESI * 0xe) != '\0')) {
        bVar9 = true;
      }
      if (!bVar9) {
        local_24 = '\0';
      }
    }
    local_18 = '\x01';
    uVar2 = *puVar4;
    if (*(char *)(iVar5 + 10 + (uint)uVar2 * 0xe) == '\0') {
      bVar9 = false;
      bVar8 = false;
      if ((puVar4[1] == 1) &&
         (unaff_ESI = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(puVar4 + 2) * 4),
         unaff_ESI != (ushort *)0x0)) {
        bVar7 = false;
        if (((uint)(uVar2 >> 5) < **(uint **)(unaff_ESI + 0x16)) &&
           (((*(uint **)(unaff_ESI + 0x16))[(uVar2 >> 5) + 1] & 1 << ((byte)uVar2 & 0x1f)) != 0)) {
          bVar7 = true;
        }
        if (bVar7) {
          bVar8 = true;
        }
      }
      if ((bVar8) && (*(char *)(iVar5 + 10 + (uint)*unaff_ESI * 0xe) != '\0')) {
        bVar9 = true;
      }
      if (!bVar9) {
        local_18 = '\0';
      }
    }
    if (local_24 != local_18) {
      puVar6 = *(uint **)(iVar5 + (uint)*param_1 * 0xe);
      if (local_24 == '\0') {
        bVar8 = false;
        if (((uint)(uVar2 >> 5) < *puVar6) &&
           ((puVar6[(uVar2 >> 5) + 1] & 1 << ((byte)uVar2 & 0x1f)) != 0)) {
          bVar8 = true;
        }
        if (!bVar8) {
          *param_3 = (uint)puVar4;
          return puVar3;
        }
      }
      else {
        bVar8 = false;
        if (((uint)(uVar1 >> 5) < *puVar6) &&
           ((puVar6[(uVar1 >> 5) + 1] & 1 << ((byte)uVar1 & 0x1f)) != 0)) {
          bVar8 = true;
        }
        if (!bVar8) {
          *param_3 = (uint)puVar3;
          return puVar4;
        }
      }
    }
  }
  return (ushort *)0x0;
}

/* Native 0x60d630, 620 bytes. */
ushort * fn_0060d630(ushort *param_1, int param_2, uint *param_3)
{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  int iVar4;
  ushort *puVar5;
  uint *puVar6;
  uint uVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  uint uVar14;
  ushort *unaff_ESI;
  if (param_1[1] == 2) {
    puVar3 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(param_1 + 2) * 4);
    iVar4 = *(int *)(param_2 + 4);
    puVar5 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 2))[1] * 4);
    puVar6 = *(uint **)(iVar4 + (uint)*param_1 * 0xe);
    uVar1 = *puVar3;
    bVar11 = false;
    uVar14 = (uint)(uVar1 >> 5);
    if ((uVar14 < *puVar6) && ((puVar6[uVar14 + 1] & 1 << ((byte)uVar1 & 0x1f)) != 0)) {
      bVar11 = true;
    }
    uVar2 = *puVar5;
    bVar13 = false;
    uVar7 = (uint)(uVar2 >> 5);
    if ((uVar7 < *puVar6) && ((puVar6[uVar7 + 1] & 1 << ((byte)uVar2 & 0x1f)) != 0)) {
      bVar13 = true;
    }
    bVar12 = true;
    if (*(char *)(iVar4 + 8 + (uint)uVar1 * 0xe) == '\0') {
      bVar9 = false;
      bVar8 = false;
      if ((puVar3[1] == 1) &&
         (unaff_ESI = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(puVar3 + 2) * 4),
         unaff_ESI != (ushort *)0x0) && (uVar14 < **(uint **)(unaff_ESI + 0x16)) &&
         (((*(uint **)(unaff_ESI + 0x16))[uVar14 + 1] & 1 << ((byte)uVar1 & 0x1f)) != 0)) {
        bVar8 = true;
      }
      if ((bVar8) && (*(char *)(iVar4 + 8 + (uint)*unaff_ESI * 0xe) != '\0')) {
        bVar9 = true;
      }
      if (!bVar9) {
        bVar12 = false;
      }
    }
    bVar8 = true;
    if (*(char *)(iVar4 + 8 + (uint)uVar2 * 0xe) == '\0') {
      bVar10 = false;
      bVar9 = false;
      if ((puVar5[1] == 1) &&
         (unaff_ESI = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(puVar5 + 2) * 4),
         unaff_ESI != (ushort *)0x0) &&
         (uVar7 < **(uint **)(unaff_ESI + 0x16) &&
         (((*(uint **)(unaff_ESI + 0x16))[uVar7 + 1] & 1 << ((byte)uVar2 & 0x1f)) != 0))) {
        bVar9 = true;
      }
      if ((bVar9) && (*(char *)(iVar4 + 8 + (uint)*unaff_ESI * 0xe) != '\0')) {
        bVar10 = true;
      }
      if (!bVar10) {
        bVar8 = false;
      }
    }
    if ((bVar11) || (!bVar12)) {
      if ((!bVar13) && (bVar8)) {
        *param_3 = (uint)puVar3;
        return puVar5;
      }
    }
    else if ((bVar13) || (!bVar8)) {
      *param_3 = (uint)puVar5;
      return puVar3;
    }
  }
  return (ushort *)0x0;
}

/* Native 0x60d8a0, 451 bytes. */
ushort * fn_0060d8a0(int param_1, uint param_2, uint *param_3)
{
  char cVar1;
  char cVar2;
  ushort uVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  char cVar8;
  char cVar9;
  ushort *local_20;
  pcVar4 = *(char **)(param_1 + 0x14);
  if ((pcVar4 != (char *)0x0) &&
     ((cVar1 = *pcVar4, cVar1 == '\n' || (cVar1 == '\v')) &&
     (pcVar4 = *(char **)(pcVar4 + 0x2e), *pcVar4 == '\x03'))) {
    cVar2 = pcVar4[1];
    iVar5 = *(int *)(pcVar4 + 0x2a);
    iVar6 = *(int *)(pcVar4 + 0x2e);
    puVar7 = *(ushort **)(param_1 + 0x30);
    uVar3 = **(ushort **)(param_1 + 4);
    if (uVar3 == *puVar7) {
      local_20 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 4))[1] * 4);
    }
    else {
      local_20 = *(ushort **)(DAT_00710b54 + (uint)uVar3 * 4);
    }
    if ((**(char **)(iVar5 + 0x12) == '\x01') && ((byte)(*(char **)(iVar5 + 0x12))[6] < 0x17) &&
       (**(char **)(iVar6 + 0x12) == '\x01' && ((byte)(*(char **)(iVar6 + 0x12))[6] < 0x17))) {
      cVar8 = FUN_005aecc0(iVar6);
      cVar9 = FUN_005aecc0(iVar5);
      if (cVar9 != cVar8) {
        if ((cVar2 == '\x13') || (cVar2 == '\x15')) {
          if ((cVar1 == '\n') == (cVar9 == '\0')) {
            *param_3 = (uint)local_20;
            return puVar7;
          }
          *param_3 = (uint)puVar7;
          return local_20;
        }
        if ((cVar2 != '\x14') && (cVar2 != '\x16')) {
          return (ushort *)0x0;
        }
        if ((cVar1 == '\n') == (cVar9 == '\0')) {
          *param_3 = (uint)puVar7;
          return local_20;
        }
        *param_3 = (uint)local_20;
        return puVar7;
      }
    }
    if ((**(char **)(iVar5 + 0x12) == '\x02') && (**(char **)(iVar6 + 0x12) == '\x02')) {
      if (cVar2 == '\x17') {
        if (cVar1 == '\n') {
          *param_3 = (uint)local_20;
          return puVar7;
        }
        *param_3 = (uint)puVar7;
        return local_20;
      }
      if (cVar2 == '\x18') {
        if (cVar1 == '\n') {
          *param_3 = (uint)puVar7;
          return local_20;
        }
        *param_3 = (uint)local_20;
        return puVar7;
      }
    }
  }
  return (ushort *)0x0;
}

/* Native 0x60da70, 330 bytes. */
ushort * fn_0060da70(ushort *param_1, int param_2, uint *param_3)
{
  ushort *puVar1;
  ushort *puVar2;
  char cVar3;
  int local_20;
  uint local_1c;
  int local_18;
  uint local_14;
  if (param_1[1] == 2) {
    local_18 = *(int *)(*(int *)(param_2 + 4) + 4 + (uint)*param_1 * 0xe);
    if (local_18 != 0) {
      cVar3 = FUN_005bf6c0(local_18);
      if (cVar3 == '\0') {
        puVar1 = *(ushort **)(DAT_00710b54 + (uint)**(ushort **)(param_1 + 2) * 4);
        puVar2 = *(ushort **)(DAT_00710b54 + (uint)(*(ushort **)(param_1 + 2))[1] * 4);
        local_14 = *(uint *)(*(int *)(param_2 + 4) + 4 + (uint)*puVar1 * 0xe);
        local_1c = *(uint *)(*(int *)(param_2 + 4) + 4 + (uint)*puVar2 * 0xe);
        FUN_005bfae0(&local_20, *(ushort *)(param_2 + 2));
        FUN_005bf780(local_18, local_20);
        FUN_005bf7f0(local_14, local_20);
        cVar3 = FUN_005bf6c0(local_20);
        local_14 = (cVar3 == '\0');
        FUN_005bf780(local_18, local_20);
        FUN_005bf7f0(local_1c, local_20);
        cVar3 = FUN_005bf6c0(local_20);
        if (local_20 != 0) {
          FUN_004c53c0(local_20);
        }
        if ((bool)(char)local_14 != (cVar3 == '\0')) {
          if ((char)local_14 != '\0') {
            *param_3 = (uint)puVar1;
            return puVar2;
          }
          *param_3 = (uint)puVar2;
          return puVar1;
        }
      }
    }
  }
  return (ushort *)0x0;
}

/* Native 0x60dbc0, 374 bytes. */
void fn_0060dbc0(ushort *param_1, ushort param_2)
{
  uint *puVar1;
  ushort *puVar2;
  uint uVar3;
  uint *puVar4;
  char *pcVar5;
  int iVar6;
  short sVar7;
  char *pcVar8;
  ushort uVar9;
  byte *puVar10;
  iVar6 = (uint)param_2 * 0xe;
  *param_1 = param_2;
  uVar3 = FUN_004c5480(iVar6);
  *(uint *)(param_1 + 2) = uVar3;
  puVar10 = *(byte **)(param_1 + 2);
  memset(puVar10, 0, iVar6);
  puVar10 += iVar6;
  iVar6 = 0;
  fn_0060e120((ushort *)(param_1));
  puVar4 = (uint *)FUN_005c59c0();
  uVar9 = 0;
  for (puVar1 = puVar4; puVar2 = DAT_00710990, puVar1 != (uint *)0x0;
      puVar1 = *(uint **)((int)puVar1 + 0x6a)) {
    uVar9 = uVar9 + 1;
  }
  for (; puVar2 != (ushort *)0x0; puVar2 = *(ushort **)(puVar2 + 0x18)) {
    FUN_005bfae0((uint)*puVar2 * 0xe + *(int *)(param_1 + 2) + 4, uVar9);
  }
  param_1[1] = uVar9;
  sVar7 = 0;
  for (puVar1 = puVar4; puVar1 != (uint *)0x0; puVar1 = *(uint **)((int)puVar1 + 0x6a)) {
    *(byte *)(*(int *)(param_1 + 2) + 8 + (uint)*(ushort *)puVar1[5] * 0xe) = 1;
    fn_0060dd40((int)(puVar1), (int)(param_1), (ushort)(sVar7));
    FUN_005c3330(puVar1);
    FUN_005c3060(puVar1);
    if ((*puVar1 & 0x200000) == 0) {
      if (((ushort *)puVar1[4] == (ushort *)puVar1[5]) &&
         ((ushort *)puVar1[4] != (ushort *)puVar1[8])) {
        *(byte *)(*(int *)(param_1 + 2) + 9 + (uint)*(ushort *)puVar1[5] * 0xe) = 1;
      }
    }
    sVar7 = sVar7 + 1;
  }
  FUN_005c5920(puVar4);
  for (puVar2 = DAT_00710990; puVar2 != (ushort *)0x0; puVar2 = *(ushort **)(puVar2 + 0x18)) {
    pcVar5 = *(char **)(puVar2 + 8);
    if ((pcVar5 != (char *)0x0) && (pcVar8 = *(char **)(puVar2 + 10), pcVar8 != (char *)0x0)) {
      if (pcVar5 != *(char **)(pcVar8 + 0x3e)) {
        do {
          if (*pcVar5 == '\a') {
            *(byte *)(*(int *)(param_1 + 2) + 10 + (uint)*puVar2 * 0xe) = 1;
          }
          pcVar5 = *(char **)(pcVar5 + 0x3e);
          pcVar8 = *(char **)(puVar2 + 10);
        } while (pcVar5 != *(char **)(pcVar8 + 0x3e));
      }
      if (*pcVar8 == '\f') {
        *(byte *)(*(int *)(param_1 + 2) + 0xb + (uint)*puVar2 * 0xe) = 1;
      }
    }
  }
  return;
}

/* Native 0x60dd40, 534 bytes. */
void fn_0060dd40(int param_1, int param_2, ushort param_3)
{
  int iVar1;
  ushort *puVar2;
  uint *puVar3;
  ushort *puVar4;
  uint uVar5;
  uint *local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  iVar1 = *(int *)(param_1 + 8);
  if ((iVar1 != 0) && (iVar1 != 0)) {
    FUN_004c53c0(iVar1);
    *(uint *)(param_1 + 8) = 0;
  }
  puVar2 = *(ushort **)(param_1 + 0x14);
  FUN_005bfae0(&local_24, DAT_007172c0 + 1);
  FUN_005bf760(local_24);
  uVar5 = (uint)(*puVar2 >> 5);
  if (uVar5 < *local_24) {
    local_24[uVar5 + 1] = local_24[uVar5 + 1] | 1 << ((byte)*puVar2 & 0x1f);
  }
  else {
    CError_Internal(s_BitVector_h_00698a16, 0x52);
  }
  puVar3 = *(uint **)(*(int *)(param_2 + 4) + 4 + (uint)*puVar2 * 0xe);
  local_14 = (uint)param_3;
  local_18 = (uint)(param_3 >> 5);
  if (local_18 < *puVar3) {
    puVar3 = puVar3 + local_18 + 1;
    *puVar3 = *puVar3 | 1 << ((byte)param_3 & 0x1f);
  }
  else {
    CError_Internal(s_BitVector_h_00698a16, 0x52);
  }
  local_1c = 0;
  if (puVar2[4] != 0) {
    local_20 = 1 << ((byte)local_14 & 0x1f);
    do {
      puVar4 = *(ushort **)
                (DAT_00710b54 +
                (uint)*(ushort *)(*(int *)(puVar2 + 5) + (local_1c & 0xffff) * 2) * 4);
      local_14 = 0;
      uVar5 = (uint)(*puVar2 >> 5);
      if ((uVar5 < **(uint **)(puVar4 + 0x16)) &&
         (((*(uint **)(puVar4 + 0x16))[uVar5 + 1] & 1 << ((byte)*puVar2 & 0x1f)) != 0)) {
        local_14 = 1;
      }
      if ((char)local_14 != '\0') {
        uVar5 = (uint)(*puVar4 >> 5);
        if (uVar5 < *local_24) {
          local_24[uVar5 + 1] = local_24[uVar5 + 1] | 1 << ((byte)*puVar4 & 0x1f);
        }
        else {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
        puVar3 = *(uint **)(*(int *)(param_2 + 4) + 4 + (uint)*puVar4 * 0xe);
        if (local_18 < *puVar3) {
          puVar3 = puVar3 + local_18 + 1;
          *puVar3 = *puVar3 | local_20;
        }
        else {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
        if (puVar4 != puVar2) {
          fn_0060df60((int)(puVar4), (uint *)(local_24), (int)(param_2), (ushort)(param_3));
        }
      }
      local_1c = local_1c + 1;
    } while ((ushort)local_1c < puVar2[4]);
  }
  *(uint **)(param_1 + 8) = local_24;
  return;
}

/* Native 0x60df60, 445 bytes. */
void fn_0060df60(int param_1, uint *param_2, int param_3, ushort param_4)
{
  ushort uVar1;
  ushort *puVar2;
  uint *puVar3;
  ushort *puVar4;
  bool bVar5;
  char cVar6;
  uint uVar7;
  byte bVar8;
  uint uVar9;
  ushort uVar10;
  uVar1 = 0;
  if (*(short *)(param_1 + 8) != 0) {
    uVar7 = (uint)param_4;
    do {
      puVar2 = *(ushort **)
                (DAT_00710b54 + (uint)*(ushort *)(*(int *)(param_1 + 10) + (uint)uVar1 * 2) * 4);
      bVar5 = false;
      uVar9 = (uint)(*puVar2 >> 5);
      bVar8 = (byte)*puVar2;
      if ((uVar9 < *param_2) && ((param_2[uVar9 + 1] & 1 << (bVar8 & 0x1f)) != 0)) {
        bVar5 = true;
      }
      if (!bVar5) {
        if (uVar9 < *param_2) {
          param_2[uVar9 + 1] = param_2[uVar9 + 1] | 1 << (bVar8 & 0x1f);
        }
        else {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
        puVar3 = *(uint **)(*(int *)(param_3 + 4) + 4 + (uint)*puVar2 * 0xe);
        if ((uint)(param_4 >> 5) < *puVar3) {
          puVar3 = puVar3 + (param_4 >> 5) + 1;
          *puVar3 = *puVar3 | 1 << ((byte)param_4 & 0x1f);
        }
        else {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
        uVar10 = 0;
        if (puVar2[4] != 0) {
          do {
            puVar4 = *(ushort **)
                      (DAT_00710b54 + (uint)*(ushort *)(*(int *)(puVar2 + 5) + (uint)uVar10 * 2) * 4
                      );
            cVar6 = FUN_005c5e00(*puVar4, param_2);
            if (cVar6 == '\0') {
              FUN_005c5dd0(*puVar4, param_2);
              FUN_005c5dd0(uVar7, *(uint *)(*(int *)(param_3 + 4) + 4 + (uint)*puVar4 * 0xe));
              fn_0060df60((int)(puVar4), (uint *)(param_2), (int)(param_3), (ushort)(param_4));
            }
            uVar10 = uVar10 + 1;
          } while (uVar10 < puVar2[4]);
        }
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(ushort *)(param_1 + 8));
  }
  return;
}

/* Native 0x60e120, 682 bytes. */
void fn_0060e120(ushort *param_1)
{
  int *piVar1;
  int iVar2;
  uint *puVar3;
  ushort *puVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  ushort uVar9;
  uint *local_14;
  uVar9 = 0;
  puVar4 = DAT_00710990;
  if (*param_1 != 0) {
    iVar7 = 0;
    do {
      if (*(int *)(*(int *)(param_1 + 2) + iVar7) != 0) {
        piVar1 = (int *)(iVar7 + *(int *)(param_1 + 2));
        iVar2 = *piVar1;
        if (iVar2 != 0) {
          FUN_004c53c0(iVar2);
          *piVar1 = 0;
        }
      }
      uVar9 = uVar9 + 1;
      iVar7 = iVar7 + 0xe;
      puVar4 = DAT_00710990;
    } while (uVar9 < *param_1);
  }
  for (; puVar4 != (ushort *)0x0; puVar4 = *(ushort **)(puVar4 + 0x18)) {
    if (puVar4[1] == 0) {
      bVar5 = false;
      uVar8 = (uint)(*DAT_00710990 >> 5);
      if ((uVar8 < **(uint **)(puVar4 + 0x16)) &&
         (((*(uint **)(puVar4 + 0x16))[uVar8 + 1] & 1 << ((byte)*DAT_00710990 & 0x1f)) != 0)) {
        bVar5 = true;
      }
      if (bVar5) {
        FUN_005bfae0((uint)*puVar4 * 0xe + *(int *)(param_1 + 2), DAT_007172c0);
        uVar9 = *puVar4;
        puVar3 = *(uint **)(*(int *)(param_1 + 2) + (uint)uVar9 * 0xe);
        if ((uint)(uVar9 >> 5) < *puVar3) {
          puVar3 = puVar3 + (uVar9 >> 5) + 1;
          *puVar3 = *puVar3 | 1 << ((byte)uVar9 & 0x1f);
        }
        else {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
      }
    }
  }
  for (puVar4 = DAT_00710990; puVar4 != (ushort *)0x0; puVar4 = *(ushort **)(puVar4 + 0x18)) {
    if (*(int *)(*(int *)(param_1 + 2) + (uint)*puVar4 * 0xe) == 0) {
      FUN_005bfae0((uint)*puVar4 * 0xe + *(int *)(param_1 + 2), DAT_007172c0);
      FUN_005bf740(*(uint *)(*(int *)(param_1 + 2) + (uint)*puVar4 * 0xe));
    }
  }
  FUN_005bfae0(&local_14, DAT_007172c0);
  do {
    bVar5 = false;
    for (puVar4 = DAT_00710990; puVar4 != (ushort *)0x0; puVar4 = *(ushort **)(puVar4 + 0x18)) {
      if (puVar4[1] == 0) {
        FUN_005bf760(local_14);
        uVar8 = (uint)(*puVar4 >> 5);
        if (uVar8 < *local_14) {
          local_14[uVar8 + 1] = local_14[uVar8 + 1] | 1 << ((byte)*puVar4 & 0x1f);
        }
        else {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
      }
      else {
        FUN_005bf740(local_14);
        uVar9 = 0;
        if (puVar4[1] != 0) {
          do {
            FUN_005bf9d0(*(uint *)
                          (*(int *)(param_1 + 2) +
                          (uint)**(ushort **)
                                  (DAT_00710b54 +
                                  (uint)*(ushort *)(*(int *)(puVar4 + 2) + (uint)uVar9 * 2) * 4) *
                          0xe), local_14);
            uVar9 = uVar9 + 1;
          } while (uVar9 < puVar4[1]);
        }
        uVar8 = (uint)(*puVar4 >> 5);
        if (uVar8 < *local_14) {
          local_14[uVar8 + 1] = local_14[uVar8 + 1] | 1 << ((byte)*puVar4 & 0x1f);
        }
        else {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
      }
      cVar6 = FUN_005bf890(local_14, *(uint *)(*(int *)(param_1 + 2) + (uint)*puVar4 * 0xe));
      if (cVar6 == '\0') {
        FUN_005bf780(local_14, *(uint *)(*(int *)(param_1 + 2) + (uint)*puVar4 * 0xe));
        bVar5 = true;
      }
    }
  } while (bVar5);
  return;
}

/* Native 0x60e3d0, 335 bytes. */
void fn_0060e3d0(uint *param_1, ushort *param_2)
{
  uint *puVar1;
  ushort uVar2;
  int iVar3;
  ushort uVar4;
  short sVar5;
  uint *puVar6;
  int iVar7;
  ushort uVar8;
  uVar2 = *(ushort *)(param_1[4] + (uint)*param_2 * 2);
  puVar1 = (uint *)((uint)uVar2 * 0xc + param_1[3]);
  *puVar1 = (uint)param_2;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar6 = (uint *)0x0;
  uVar4 = 1;
  if ((int)param_1[2] > 1) {
    do {
      if (puVar6 != (uint *)0x0) break;
      iVar7 = -1;
      sVar5 = -uVar4;
      do {
        uVar8 = uVar2 + sVar5;
        if ((int)(uint)uVar8 < (int)param_1[2]) {
          iVar3 = (uint)uVar8 * 0xc;
          if (*(int *)(param_1[3] + iVar3) != 0) {
            puVar6 = (uint *)(iVar3 + param_1[3]);
            break;
          }
        }
        iVar7 = iVar7 + 2;
        sVar5 = sVar5 + uVar4 * 2;
      } while (iVar7 < 2);
      uVar4 = uVar4 + 1;
    } while ((int)(uint)uVar4 < (int)param_1[2]);
  }
  if (puVar6 == (uint *)0x0) {
    *param_1 = (uint)puVar1;
    param_1[1] = (uint)puVar1;
  }
  else if (puVar6 < puVar1) {
    puVar1[2] = (uint)puVar6;
    puVar1[1] = puVar6[1];
    if (puVar1[1] == 0) {
      param_1[1] = (uint)puVar1;
    }
    else {
      *(uint **)(puVar1[1] + 8) = puVar1;
    }
    puVar6[1] = (uint)puVar1;
  }
  else {
    puVar1[1] = (uint)puVar6;
    puVar1[2] = puVar6[2];
    if (puVar1[2] == 0) {
      *param_1 = (uint)puVar1;
    }
    else {
      *(uint **)(puVar1[2] + 4) = puVar1;
    }
    puVar6[2] = (uint)puVar1;
  }
  return;
}
