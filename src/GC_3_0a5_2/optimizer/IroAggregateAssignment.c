/* Native IroAggregateAssignment.c. The Windows IR/type records differ from
 * the older shared headers, so their packed offsets remain explicit here.
 * Private names are address-based until a native name is corroborated. */
#include "compiler/common.h"
typedef UInt32 uint;
extern void *__builtin_memset(void *,int,uint);
extern double __builtin_fabs(double);
typedef UInt16 ushort;
typedef UInt8 byte,undefined1,undefined;
typedef UInt32 undefined4;
typedef UInt8 bool;
enum {false=0,true=1};
static inline double words_as_double(uint high,uint low) {
  union {struct {uint low,high;} words;double value;} bits;
  bits.words.low=low;bits.words.high=high;return bits.value;
}
static inline double native_abs(double value) {
  return __builtin_fabs(value);
}
static char aggregate_filename[]="IroAggregateAssignment.c";
static char aggregate_adding_message[]="adding assignment before %d for use at %d\n";
static char aggregate_nopping_message[]="nopping assignment at %d\n";
static double aggregate_zero=0.0,aggregate_epsilon=0.1,aggregate_scale=10.0;
static int *aggregate_source_cache;
static uint *aggregate_temp_bitmap;
static byte *aggregate_block_bitmaps;
static int aggregate_queue_count;
static uint *aggregate_queue_tail,*aggregate_queue_head;
extern int DAT_00710674;
extern uint *DAT_007107a0;
extern int *DAT_00710088;
extern ushort *DAT_00710990;
extern ushort DAT_007172c0;
extern int DAT_00710b54;
extern uint DAT_00710998;
extern byte DAT_0070f22d;
extern char s_BitVector_h_00698a16[];
extern byte DAT_00699c34;
extern int DAT_00699c36;
extern byte DAT_00699c4c;
extern int DAT_00699c4e;
extern byte DAT_00699c5c;
extern int DAT_00699c5e;
extern byte DAT_00699c6c;
extern int DAT_00699c6e;
extern byte DAT_00699c7c;
extern int DAT_00699c7e;
extern void fn_004c53c0(int);
extern int fn_004c5480(int);
extern uint fn_005bf3e0(uint);
extern void fn_005bfae0(void *,uint);
extern byte fn_005bf6c0(uint);
extern void fn_005bf780(uint,uint);
extern void fn_005bf7f0(uint,uint);
extern void fn_005bf940(uint,uint);
extern void fn_005bf9d0(uint,uint);
extern void IroBitVect_ClearBitVector(uint);
extern void IroBitVect_SetAllBits(uint);
extern void IroBitVect_ClearBit(uint,uint);
extern int fn_005c59c0(void);
extern void fn_005c5920(int);
extern byte fn_00603030(void);
extern void fn_006061f0(void);
extern int fn_005ad570(int);
extern uint fn_005ac4b0(int);
extern byte fn_005c5e00(uint,uint *);
extern void fn_005c5dd0(uint,uint *);
extern void fn_00558d70(void *,uint,int,int (*)(int *,int *));
extern int fn_00521c20(int,byte);
extern int fn_005ab970(uint,uint,uint);
extern int fn_005b34b0(uint);
extern int fn_005b34c0(uint);
extern byte fn_00542340(char *);
extern byte fn_005b3050(uint,int,int *,int *);
extern void fn_005ad280(void *);
extern void fn_005ad440(uint,uint,uint);
extern void fn_005ae7b0(uint);
extern void fn_005ad220(uint,void *);
extern int fn_005ac9f0(uint,uint);
extern uint fn_005b7d30(uint);
extern uint fn_005b5760(void);
extern byte fn_005b7e20(uint,uint);
extern int fn_005bd630(int);
extern void fn_005ed4c0(const char *,...);
extern void CError_Internal(const char *,int);
extern void * galloc(int);
extern void memclrw(void *,int);
extern int IroUtil_FindNextUse(int);
extern void IroVars_CheckTimedLongjmp(void);
extern void * CDecl_NewOpaqueType(int,int);
extern void fn_0060efc0(void);
extern void fn_0060f260(uint *param_1, uint *param_2, int param_3, undefined4 param_4, int param_5);
extern void fn_0060f920(void);
extern byte fn_0060f9e0(ushort *param_1, int param_2, uint *param_3, uint unused_4, uint unused_5);
extern byte fn_0060faf0(int param_1, int param_2, uint *param_3, ushort *param_4);
extern void fn_0060fc60(void);
extern void fn_0060fd20(int param_1, ushort param_2);
extern void fn_0060ff20(int param_1, uint *param_2, ushort param_3);
extern void fn_006100c0(void);
extern void fn_00610140(int param_1);
extern void fn_006106f0(int param_1, int param_2, int param_3, int param_4, undefined4 param_5,
                 int param_6);
extern void fn_00610b40(int param_1, int param_2, int param_3, int param_4, undefined4 param_5,
                 int param_6);
extern int fn_00610f10(int *param_1, int *param_2);
extern void fn_00611dc0(int param_1);
extern void fn_006120b0(int param_1);
extern void fn_006121c0(int param_1, int param_2, int param_3, uint param_4);
extern int fn_006122c0(char *param_1, int param_2, int param_3, char param_4);
extern void fn_00612570(char *param_1, undefined4 param_2, int param_3);
extern undefined4 *
fn_00612810(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8,
            undefined4 param_9);


void fn_0060efc0(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  char cVar6;
  undefined4 *puVar7;
  int iVar8;
  ushort uVar9;

  fn_0060fc60();
  cVar6 = fn_00603030();
  if (cVar6 != '\0') {
    fn_0060f920();
    for (iVar8 = DAT_00710674; iVar2 = (int)DAT_007107a0, iVar8 != 0; iVar8 = *(int *)(iVar8 + 0x10)) {
      *(undefined4 *)(iVar8 + 0x24) = 0;
    }
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x10)) {
      iVar8 = *(int *)(iVar2 + 0xc);
      if ((*(char *)(iVar8 + 0xe) == '\0') && (*(int *)(iVar8 + 0x24) == 0)) {
        bVar5 = true;
        if ((*(int *)(iVar8 + 4) == 0) || (iVar3 = *(int *)(*(int *)(iVar8 + 4) + 0x10), iVar3 == 0)
           ) {
          bVar5 = false;
        }
        else {
          for (iVar4 = *(int *)(iVar8 + 0x14); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x14)) {
            if (((int)*(uint *)(iVar4 + 0x3a) < 0) ||
               ((uint)(*(int *)(iVar3 + 2) * 8) <= *(uint *)(iVar4 + 0x3a))) {
              bVar5 = false;
              break;
            }
          }
        }
        if (bVar5) {
          puVar7 = (undefined4 *)fn_004c5480((int)(0x10));
          *puVar7 = 0;
          puVar7[1] = 0;
          puVar7[2] = 0;
          puVar7[3] = 0;
          *(undefined4 **)(iVar8 + 0x24) = puVar7;
          if ((*(int *)(iVar8 + 4) == 0) || (*(int *)(*(int *)(iVar8 + 4) + 0x10) == 0)) {
            CError_Internal((const char *)(aggregate_filename), (int)(0x69b));
          }
          fn_005bfae0((void *)(puVar7), (uint)(*(int *)(*(int *)(*(int *)(iVar8 + 4) + 0x10) + 2) * 8));
          puVar7[1] = 0;
          fn_005bfae0((void *)(puVar7 + 2), (uint)(*(int *)(*(int *)(*(int *)(iVar8 + 4) + 0x10) + 2) * 8));
          *(undefined1 *)(puVar7 + 3) = 0;
          *(undefined1 *)((int)puVar7 + 0xd) = 0;
          *(undefined1 *)((int)puVar7 + 0xe) = 0;
        }
      }
    }
    aggregate_queue_count = 0;
    for (puVar7 = (undefined4 *)DAT_00710088; puVar7 != (undefined4 *)0x0; puVar7 = (undefined4 *)puVar7[4]) {
      fn_0060f260((uint *)(*(undefined4 *)((int)puVar7 + 0x22)), (uint *)(*(undefined4 *)((int)puVar7 + 0x26)), (int)(puVar7[2]), (undefined4)(puVar7[1]), (int)(*puVar7));
    }
    fn_006100c0();
    iVar8 = (int)aggregate_queue_head;
    while (iVar8 != 0) {
      iVar2 = *(int *)(iVar8 + 0x24);
      fn_004c53c0((int)(iVar8));
      iVar8 = iVar2;
    }
    aggregate_queue_head = 0;
    aggregate_queue_tail = 0;
    for (iVar8 = DAT_00710674; iVar8 != 0; iVar8 = *(int *)(iVar8 + 0x10)) {
      piVar1 = *(int **)(iVar8 + 0x24);
      if (piVar1 != (int *)0x0) {
        iVar2 = *piVar1;
        if ((iVar2 != 0) && (iVar2 != 0)) {
          fn_004c53c0((int)(iVar2));
          *piVar1 = 0;
        }
        iVar2 = piVar1[2];
        if ((iVar2 != 0) && (iVar2 != 0)) {
          fn_004c53c0((int)(iVar2));
          piVar1[2] = 0;
        }
        fn_004c53c0((int)(piVar1));
        *(undefined4 *)(iVar8 + 0x24) = 0;
      }
    }
    fn_006061f0();
  }
  uVar9 = 0;
  if (DAT_007172c0 != 0) {
    iVar8 = 0;
    do {
      if (*(int *)(aggregate_block_bitmaps + (uint)uVar9 * 4) != 0) {
        piVar1 = (int *)(iVar8 + aggregate_block_bitmaps);
        iVar2 = *piVar1;
        if (iVar2 != 0) {
          fn_004c53c0((int)(iVar2));
          *piVar1 = 0;
        }
      }
      uVar9 = uVar9 + 1;
      iVar8 = iVar8 + 4;
    } while (uVar9 < DAT_007172c0);
  }
  fn_004c53c0((int)(aggregate_block_bitmaps));
  aggregate_block_bitmaps = 0;
  if ((aggregate_temp_bitmap != 0) && (aggregate_temp_bitmap != 0)) {
    fn_004c53c0((int)(aggregate_temp_bitmap));
    aggregate_temp_bitmap = 0;
  }
  return;
}

void fn_0060f260(uint *param_1, uint *param_2, int param_3, undefined4 param_4, int param_5)

{
  undefined4 *puVar1;
  uint *puVar2;
  undefined4 *puVar3;
  uint *puVar4;
  int iVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  byte bVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint *puVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  bool bVar19;
  uint local_18;

  aggregate_source_cache = 0;
  for (puVar16 = DAT_007107a0; puVar2 = DAT_007107a0, puVar16 != (uint *)0x0;
      puVar16 = (uint *)puVar16[4]) {
    uVar15 = puVar16[3];
    iVar8 = *(int *)((int)puVar16 + 0x22);
    puVar1 = *(undefined4 **)(uVar15 + 0x24);
    if ((iVar8 != 0) && (puVar1 != (undefined4 *)0x0) && (*(char *)(iVar8 + 0xe) == '\0')) {
      bVar19 = false;
      uVar12 = *puVar16 >> 5;
      if ((uVar12 < *param_2) && ((param_2[uVar12 + 1] & 1 << ((byte)*puVar16 & 0x1f)) != 0)) {
        bVar19 = true;
      }
      if (bVar19) {
        if (*(char *)((int)puVar1 + 0xd) == '\0') {
          uVar10 = *puVar1;
          IroBitVect_SetAllBits((uint)(uVar10));
          fn_00612570((char *)(*(undefined4 *)(*(int *)(uVar15 + 4) + 0x10)), (undefined4)(uVar10), (int)(0));
          *(undefined1 *)((int)puVar1 + 0xd) = 1;
        }
        fn_006121c0((int)(uVar15), (int)(puVar1), (int)(iVar8), (uint)(*(undefined4 *)((int)puVar16 + 0x3a)));
        if (*(char *)(puVar1 + 3) == '\0') {
          IroBitVect_ClearBitVector((uint)(puVar1[2]));
          *(undefined1 *)(puVar1 + 3) = 1;
        }
      }
    }
  }
  for (; puVar16 = DAT_007107a0, puVar2 != (uint *)0x0; puVar2 = (uint *)puVar2[4]) {
    iVar8 = *(int *)((int)puVar2 + 0x22);
    iVar9 = *(int *)(puVar2[3] + 0x24);
    bVar19 = false;
    uVar15 = *puVar2 >> 5;
    if ((uVar15 < *param_1) && ((param_1[uVar15 + 1] & 1 << ((byte)*puVar2 & 0x1f)) != 0)) {
      bVar19 = true;
    }
    if ((bVar19) && (iVar9 != 0) &&
       (*(undefined1 *)(iVar9 + 0xe) = 0, iVar8 == 0 || (puVar2[2] == 0))) {
      uVar15 = *(uint *)((int)puVar2 + 0x3a) >> 5;
      if (uVar15 < **(uint **)(iVar9 + 8)) {
        puVar16 = *(uint **)(iVar9 + 8) + uVar15 + 1;
        *puVar16 = *puVar16 | 1 << ((byte)*(uint *)((int)puVar2 + 0x3a) & 0x1f);
      }
      else {
        CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
      }
    }
  }
  for (; iVar8 = param_3, puVar16 != (uint *)0x0; puVar16 = (uint *)puVar16[4]) {
    uVar10 = *(undefined4 *)((int)puVar16 + 0x22);
    uVar15 = puVar16[3];
    iVar8 = *(int *)(uVar15 + 0x24);
    bVar19 = false;
    uVar12 = *puVar16 >> 5;
    bVar11 = (byte)*puVar16;
    if ((uVar12 < *param_1) && ((param_1[uVar12 + 1] & 1 << (bVar11 & 0x1f)) != 0)) {
      bVar19 = true;
    }
    if ((bVar19) && (iVar8 != 0)) {
      bVar19 = false;
      uVar13 = *(uint *)((int)puVar16 + 0x3a) >> 5;
      if ((uVar13 < **(uint **)(iVar8 + 8)) &&
         (((*(uint **)(iVar8 + 8))[uVar13 + 1] & 1 << ((byte)*(uint *)((int)puVar16 + 0x3a) & 0x1f))
          != 0)) {
        bVar19 = true;
      }
      if ((!bVar19) &&
         (*(int *)((int)puVar16 + 0x32) != 1 || (*(int **)((int)puVar16 + 0x36) == (int *)0x0) ||
         (**(int **)((int)puVar16 + 0x36) != param_5) ||
         (*param_2 <= uVar12 || ((param_2[uVar12 + 1] & 1 << (bVar11 & 0x1f)) == 0)) ||
         (cVar7 = fn_0060faf0((int)(uVar10), (int)(puVar16), (uint *)(param_1), (ushort *)(param_4)), cVar7 == '\0' ||
         (cVar7 = fn_0060f9e0((ushort *)(param_4), (int)(param_5), (uint *)(puVar16), (uint)(uVar15), (uint)(uVar10)), cVar7 == '\0')))) {
        for (iVar9 = *(int *)(puVar16[2] + 0x22); iVar9 != 0; iVar9 = *(int *)(iVar9 + 0x2a)) {
          uVar15 = *(uint *)(iVar9 + 0x3a) >> 5;
          if (uVar15 < **(uint **)(iVar8 + 8)) {
            puVar2 = *(uint **)(iVar8 + 8) + uVar15 + 1;
            *puVar2 = *puVar2 | 1 << ((byte)*(uint *)(iVar9 + 0x3a) & 0x1f);
          }
          else {
            CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
          }
        }
      }
    }
  }
  do {
    iVar9 = iVar8;
    iVar8 = IroUtil_FindNextUse((int)(iVar9));
  } while (iVar8 != 0);
  iVar8 = fn_005ad570((int)(iVar9));
  if (iVar8 != 0) {
    iVar9 = fn_005ad570((int)(iVar9));
  }
  uVar10 = fn_005ac4b0((int)(iVar9));
  for (puVar16 = DAT_007107a0; puVar16 != (uint *)0x0; puVar16 = (uint *)puVar16[4]) {
    uVar15 = puVar16[3];
    puVar1 = *(undefined4 **)(uVar15 + 0x24);
    if ((*(int *)((int)puVar16 + 0x22) != 0) && (puVar1 != (undefined4 *)0x0)) {
      bVar19 = false;
      uVar12 = *puVar16 >> 5;
      if ((uVar12 < *param_2) && ((param_2[uVar12 + 1] & 1 << ((byte)*puVar16 & 0x1f)) != 0)) {
        bVar19 = true;
      }
      if ((bVar19) && (*(undefined1 *)(puVar1 + 3) = 0, *(char *)((int)puVar1 + 0xd) != '\0') &&
         (*(char *)((int)puVar1 + 0xe) == '\0')) {
        puVar2 = (uint *)*puVar1;
        uVar18 = puVar1[2];
        for (puVar3 = (undefined4 *)puVar1[1]; puVar3 != (undefined4 *)0x0;
            puVar3 = (undefined4 *)puVar3[2]) {
          puVar4 = (uint *)puVar3[1];
          uVar17 = *puVar3;
          fn_005bf7f0((uint)(uVar18), (uint)(puVar4));
          fn_005bf940((uint)(puVar2), (uint)(puVar4));
          uVar12 = *(int *)(*(int *)(*(int *)(uVar15 + 4) + 0x10) + 2) * 8;
          uVar13 = 0;
          bVar19 = true;
          if ((int)uVar12 > 0) {
            do {
              bVar6 = false;
              if ((uVar13 >> 5 < *puVar4) &&
                 ((puVar4[(uVar13 >> 5) + 1] & 1 << ((byte)uVar13 & 0x1f)) != 0)) {
                bVar6 = true;
              }
              if (!bVar6) {
                bVar19 = false;
              }
              uVar13 = uVar13 + 1;
            } while ((int)uVar13 < (int)uVar12);
          }
          if (!bVar19) {
            bVar19 = false;
            local_18 = 0;
            if ((int)uVar12 > 0) {
              do {
                bVar6 = false;
                uVar13 = local_18 >> 5;
                if ((uVar13 < *puVar4) && ((puVar4[uVar13 + 1] & 1 << ((byte)local_18 & 0x1f)) != 0)
                   ) {
                  bVar6 = true;
                }
                if (bVar6) {
                  if ((uVar13 < *puVar2) &&
                     ((puVar2[uVar13 + 1] & 1 << ((byte)local_18 & 0x1f)) != 0)) {
                    if (!bVar19) {
                      IroBitVect_ClearBit((uint)(local_18), (uint)(puVar4));
                    }
                  }
                  else {
                    bVar19 = true;
                  }
                }
                else {
                  bVar19 = false;
                }
                local_18 = local_18 + 1;
              } while ((int)local_18 < (int)uVar12);
            }
            bVar19 = false;
            uVar13 = uVar12;
            while (uVar13 = uVar13 - 1, (int)uVar13 > -1) {
              bVar6 = false;
              uVar14 = uVar13 >> 5;
              if ((uVar14 < *puVar4) && ((puVar4[uVar14 + 1] & 1 << ((byte)uVar13 & 0x1f)) != 0)) {
                bVar6 = true;
              }
              if (bVar6) {
                if ((uVar14 < *puVar2) && ((puVar2[uVar14 + 1] & 1 << ((byte)uVar13 & 0x1f)) != 0))
                {
                  if (!bVar19) {
                    IroBitVect_ClearBit((uint)(uVar13), (uint)(puVar4));
                  }
                }
                else {
                  bVar19 = true;
                }
              }
              else {
                bVar19 = false;
              }
            }
          }
          iVar8 = 0;
          uVar13 = 0;
          if ((int)uVar12 > 0) {
            do {
              bVar19 = false;
              if ((uVar13 >> 5 < *puVar4) &&
                 ((puVar4[(uVar13 >> 5) + 1] & 1 << ((byte)uVar13 & 0x1f)) != 0)) {
                bVar19 = true;
              }
              if (bVar19) {
                iVar8 = iVar8 + 1;
              }
              else {
                if (iVar8 != 0) {
                  fn_00612810((undefined4)(param_5), (undefined4)(param_4), (undefined4)(param_3), (undefined4)(param_2), (undefined4)(uVar10), (undefined4)(uVar15), (undefined4)(uVar17), (undefined4)(uVar13 - iVar8), (undefined4)(iVar8));
                }
                iVar8 = 0;
              }
              uVar13 = uVar13 + 1;
            } while ((int)uVar13 < (int)uVar12);
          }
          if (iVar8 != 0) {
            fn_00612810((undefined4)(param_5), (undefined4)(param_4), (undefined4)(param_3), (undefined4)(param_2), (undefined4)(uVar10), (undefined4)(uVar15), (undefined4)(uVar17), (undefined4)(uVar12 - iVar8), (undefined4)(iVar8));
          }
        }
        iVar8 = puVar1[1];
        while (iVar8 != 0) {
          iVar9 = *(int *)(iVar8 + 4);
          iVar5 = *(int *)(iVar8 + 8);
          if (iVar9 != 0) {
            fn_004c53c0((int)(iVar9));
            *(int *)(iVar8 + 4) = 0;
          }
          fn_004c53c0((int)(iVar8));
          iVar8 = iVar5;
        }
        puVar1[1] = 0;
        *(undefined1 *)((int)puVar1 + 0xe) = 1;
      }
    }
  }
  return;
}

void fn_0060f920(void)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  char cVar10;

  for (iVar4 = (int)DAT_007107a0; iVar2 = (int)DAT_007107a0, iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x10)) {
    iVar2 = *(int *)(iVar4 + 8);
    if ((iVar2 != 0) && ((*(uint *)(iVar2 + 2) & 0x200000) == 0)) {
      iVar7 = *(int *)(iVar4 + 0x3a);
      cVar10 = *(char *)(iVar4 + 0x1e);
      iVar8 = iVar7;
      for (iVar3 = *(int *)(iVar4 + 0x10); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x10)) {
        if (*(int *)(iVar3 + 8) == iVar2) {
          iVar5 = *(int *)(iVar3 + 0x3a);
          if (iVar5 < iVar7) {
            iVar7 = iVar5;
          }
          if (iVar8 < iVar5) {
            iVar8 = iVar5;
          }
          bVar9 = cVar10 != '\0';
          cVar10 = '\0';
          if (bVar9) {
            cVar10 = *(char *)(iVar3 + 0x1e) != '\0';
          }
        }
      }
      uVar6 = fn_006122c0((char *)(iVar2), (int)(iVar7), (int)((iVar8 + 1) - iVar7), (char)(cVar10));
      for (iVar7 = iVar4; iVar7 != 0; iVar7 = *(int *)(iVar7 + 0x10)) {
        if (*(int *)(iVar7 + 8) == iVar2) {
          *(undefined4 *)(iVar7 + 0x22) = uVar6;
          puVar1 = (uint *)(*(int *)(iVar7 + 8) + 2);
          *puVar1 = *puVar1 | 0x200000;
        }
      }
    }
  }
  for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x10)) {
    if (*(int *)(iVar2 + 8) != 0) {
      puVar1 = (uint *)(*(int *)(iVar2 + 8) + 2);
      *puVar1 = *puVar1 & 0xffdfffff;
    }
  }
  return;
}

byte fn_0060f9e0(ushort *param_1, int param_2, uint *param_3, uint unused_4, uint unused_5)

{
  ushort uVar1;
  uint *puVar2;
  int *piVar3;
  bool bVar4;
  char cVar5;
  uint uVar6;

  piVar3 = DAT_00710088;
  do {
    if (piVar3 == (int *)0x0) {
      return 1;
    }
    if (*piVar3 != param_2) {
      bVar4 = false;
      uVar6 = *param_3 >> 5;
      if ((uVar6 < *(uint *)piVar3[6]) &&
         ((((uint *)piVar3[6])[uVar6 + 1] & 1 << ((byte)*param_3 & 0x1f)) != 0)) {
        bVar4 = true;
      }
      if (bVar4) {
        if (param_1 == (ushort *)piVar3[1]) {
          return 0;
        }
        uVar1 = *param_1;
        puVar2 = *(uint **)((ushort *)piVar3[1] + 0x16);
        bVar4 = false;
        if (((uint)(uVar1 >> 5) < *puVar2) &&
           ((puVar2[(uVar1 >> 5) + 1] & 1 << ((byte)uVar1 & 0x1f)) != 0)) {
          bVar4 = true;
        }
        if (!bVar4) {
          return 0;
        }
        fn_005bf780((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)uVar1 * 4)), (uint)(aggregate_temp_bitmap));
        fn_005bf9d0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)*(ushort *)piVar3[1] * 4)), (uint)(aggregate_temp_bitmap));
        cVar5 = fn_005bf6c0((uint)(aggregate_temp_bitmap));
        if (cVar5 == '\0') {
          return 0;
        }
      }
    }
    piVar3 = (int *)piVar3[4];
  } while( true );
}

byte fn_0060faf0(int param_1, int param_2, uint *param_3, ushort *param_4)

{
  bool bVar1;
  uint *puVar2;
  uint *puVar3;
  char cVar4;
  undefined4 uVar5;
  byte bVar6;
  uint *puVar7;
  uint uVar8;
  uint *local_1c;

  local_1c = (uint *)0x0;
  puVar7 = *(uint **)(param_1 + 0x14);
  if (puVar7 != (uint *)0x0) {
    do {
      if (*(int *)((int)puVar7 + 0x3a) == *(int *)(param_2 + 0x3a)) {
        bVar1 = false;
        uVar8 = *puVar7 >> 5;
        bVar6 = (byte)*puVar7;
        if ((uVar8 < *param_3) && ((param_3[uVar8 + 1] & 1 << (bVar6 & 0x1f)) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          if ((uVar8 < **(uint **)(param_2 + 0x26)) &&
             (puVar3 = puVar7, puVar2 = local_1c,
             ((*(uint **)(param_2 + 0x26))[uVar8 + 1] & 1 << (bVar6 & 0x1f)) != 0))
          goto joined_r0x0060fb8f;
LAB_0060fba6:
          local_1c = (uint *)0x0;
          break;
        }
        if (uVar8 < **(uint **)(param_2 + 0x26)) {
          puVar3 = local_1c;
          puVar2 = (uint *)((*(uint **)(param_2 + 0x26))[uVar8 + 1] & 1 << (bVar6 & 0x1f));
joined_r0x0060fb8f:
          local_1c = puVar3;
          if (puVar2 != (uint *)0x0) goto LAB_0060fba6;
        }
      }
      puVar7 = (uint *)puVar7[5];
    } while (puVar7 != (uint *)0x0);
  }
  if (local_1c == (uint *)0x0) {
    return 0;
  }
  if (local_1c[1] == 0) {
    return 1;
  }
  fn_005bf780((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)**(ushort **)(param_2 + 4) * 4)), (uint)(aggregate_temp_bitmap));
  fn_005bf9d0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)*(ushort *)local_1c[1] * 4)), (uint)(aggregate_temp_bitmap));
  cVar4 = fn_005bf6c0((uint)(aggregate_temp_bitmap));
  if (cVar4 == '\0') {
    fn_005bf7f0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)*param_4 * 4)), (uint)(aggregate_temp_bitmap));
    uVar5 = fn_005bf6c0((uint)(aggregate_temp_bitmap));
    return uVar5;
  }
  return 1;
}

void fn_0060fc60(void)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  ushort sVar4; /* Native loop counts are zero-extended from BP/SI. */
  undefined1 *puVar5;

  iVar2 = fn_005c59c0();
  sVar4 = 0;
  for (iVar3 = iVar2; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x6a)) {
    sVar4 = sVar4 + 1;
  }
  aggregate_block_bitmaps = (undefined1 *)fn_004c5480((int)((uint)DAT_007172c0 * 4));
  __builtin_memset(aggregate_block_bitmaps,0,(uint)DAT_007172c0*4);
  puVar1=DAT_00710990;
  for (; puVar1 != (ushort *)0x0; puVar1 = *(ushort **)(puVar1 + 0x18)) {
    fn_005bfae0((void *)(aggregate_block_bitmaps + (uint)*puVar1 * 4), (uint)(sVar4));
  }
  fn_005bfae0((void *)(&aggregate_temp_bitmap), (uint)(sVar4));
  sVar4 = 0;
  for (iVar3 = iVar2; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x6a)) {
    fn_0060fd20((int)(iVar3), (ushort)(sVar4));
    sVar4 = sVar4 + 1;
  }
  fn_005c5920((int)(iVar2));
  IroVars_CheckTimedLongjmp();
  return;
}

void fn_0060fd20(int param_1, ushort param_2)

{
  int iVar1;
  ushort *puVar2;
  uint *puVar3;
  ushort *puVar4;
  bool bVar5;
  uint uVar6;
  uint *local_20;
  uint local_1c;
  uint local_18;
  uint local_14;

  iVar1 = *(int *)(param_1 + 8);
  if ((iVar1 != 0) && (iVar1 != 0)) {
    fn_004c53c0((int)(iVar1));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  puVar2 = *(ushort **)(param_1 + 0x14);
  fn_005bfae0((void *)(&local_20), (uint)(DAT_007172c0 + 1));
  IroBitVect_ClearBitVector((uint)(local_20));
  uVar6 = (uint)(*puVar2 >> 5);
  if (uVar6 < *local_20) {
    local_20[uVar6 + 1] = local_20[uVar6 + 1] | 1 << ((byte)*puVar2 & 0x1f);
  }
  else {
    CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
  }
  puVar3 = *(uint **)(aggregate_block_bitmaps + (uint)*puVar2 * 4);
  local_14 = (uint)(param_2 >> 5);
  if (local_14 < *puVar3) {
    puVar3 = puVar3 + local_14 + 1;
    *puVar3 = *puVar3 | 1 << ((byte)param_2 & 0x1f);
  }
  else {
    CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
  }
  local_18 = 0;
  if (puVar2[4] != 0) {
    local_1c = 1 << ((byte)param_2 & 0x1f);
    do {
      puVar4 = *(ushort **)
                (DAT_00710b54 +
                (uint)*(ushort *)(*(int *)(puVar2 + 5) + (local_18 & 0xffff) * 2) * 4);
      bVar5 = false;
      uVar6 = (uint)(*puVar2 >> 5);
      if ((uVar6 < **(uint **)(puVar4 + 0x16)) &&
         (((*(uint **)(puVar4 + 0x16))[uVar6 + 1] & 1 << ((byte)*puVar2 & 0x1f)) != 0)) {
        bVar5 = true;
      }
      if (bVar5) {
        uVar6 = (uint)(*puVar4 >> 5);
        if (uVar6 < *local_20) {
          local_20[uVar6 + 1] = local_20[uVar6 + 1] | 1 << ((byte)*puVar4 & 0x1f);
        }
        else {
          CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
        }
        puVar3 = *(uint **)(aggregate_block_bitmaps + (uint)*puVar4 * 4);
        if (local_14 < *puVar3) {
          puVar3 = puVar3 + local_14 + 1;
          *puVar3 = *puVar3 | local_1c;
        }
        else {
          CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
        }
        if (puVar4 != puVar2) {
          fn_0060ff20((int)(puVar4), (uint *)(local_20), (ushort)(param_2));
        }
      }
      local_18 = local_18 + 1;
    } while ((ushort)local_18 < puVar2[4]);
  }
  *(uint **)(param_1 + 8) = local_20;
  return;
}

void fn_0060ff20(int param_1, uint *param_2, ushort param_3)

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
    uVar7 = (uint)param_3;
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
          CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
        }
        puVar3 = *(uint **)(aggregate_block_bitmaps + (uint)*puVar2 * 4);
        if ((uint)(param_3 >> 5) < *puVar3) {
          puVar3 = puVar3 + (param_3 >> 5) + 1;
          *puVar3 = *puVar3 | 1 << ((byte)param_3 & 0x1f);
        }
        else {
          CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
        }
        uVar10 = 0;
        if (puVar2[4] != 0) {
          do {
            puVar4 = *(ushort **)
                      (DAT_00710b54 + (uint)*(ushort *)(*(int *)(puVar2 + 5) + (uint)uVar10 * 2) * 4
                      );
            cVar6 = fn_005c5e00((uint)(*puVar4), (uint *)(param_2));
            if (cVar6 == '\0') {
              fn_005c5dd0((uint)(*puVar4), (uint *)(param_2));
              fn_005c5dd0((uint)(uVar7), (uint *)(*(undefined4 *)(aggregate_block_bitmaps + (uint)*puVar4 * 4)));
              fn_0060ff20((int)(puVar4), (uint *)(param_2), (ushort)(param_3));
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

void fn_006100c0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;

  if (aggregate_queue_count > 0) {
    iVar1 = fn_004c5480((int)(aggregate_queue_count * 4));
    iVar2 = 0;
    for (iVar3 = (int)aggregate_queue_head; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x24)) {
      *(int *)(iVar1 + iVar2 * 4) = iVar3;
      iVar2 = iVar2 + 1;
    }
    fn_00558d70((void *)(iVar1), (uint)(aggregate_queue_count), (int)(4), (int (*)(int *,int *))(fn_00610f10));
    iVar3 = 0;
    if (aggregate_queue_count > 0) {
      do {
        fn_00610140((int)(*(undefined4 *)(iVar1 + iVar3 * 4)));
        iVar3 = iVar3 + 1;
      } while (iVar3 < aggregate_queue_count);
    }
    fn_004c53c0((int)(iVar1));
  }
  return;
}

void fn_00610140(int param_1)

{
  uint *puVar1;
  uint *puVar2;
  char *pcVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  struct {uint head,tail;} assignment_list;
  uint local_38;
  undefined4 local_34;
  int local_30;
  uint local_2c;
  uint *local_28;
  int local_24;
  uint local_20;
  undefined4 uStack_1c;
  int local_18;
  int local_14;

  if (*(char *)(param_1 + 0x28) == '\0') {
    fn_006120b0((int)(param_1));
  }
  if (*(int *)(param_1 + 0x20) ==
      *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_00610177:
    local_20 = *(undefined4 *)(param_1 + 0x2a);
    uStack_1c = *(undefined4 *)(param_1 + 0x2e);
  }
  else {
    if (DAT_0070f22d == '\0') {
      iVar5 = 0x20;
    }
    else {
      iVar5 = 0x40;
    }
    if (*(int *)(param_1 + 0x20) <= iVar5) goto LAB_00610177;
    if (*(char *)(param_1 + 0x36) == '\0') {
      fn_00611dc0((int)(param_1));
    }
    uStack_1c = *(undefined4 *)(param_1 + 0x48);
    local_20 = *(undefined4 *)(param_1 + 0x44);
  }
  local_14 = fn_005bf3e0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)**(ushort **)(param_1 + 4) * 4)));
  if (aggregate_zero < (double)local_14 - words_as_double(uStack_1c,local_20)) {
    return;
  }
  local_28 = *(uint **)(param_1 + 0xc);
  local_24 = *(int *)(param_1 + 0x14);
  local_18 = *(int *)(param_1 + 0x18);
  if (*(int *)(param_1 + 0x20) == *(int *)(*(int *)(*(int *)(local_24 + 4) + 0x10) + 2) * 8) {
LAB_00610230:
    local_20 = *(uint *)(param_1 + 0x1c);
  }
  else {
    if (DAT_0070f22d == '\0') {
      iVar5 = 0x20;
    }
    else {
      iVar5 = 0x40;
    }
    if (*(int *)(param_1 + 0x20) <= iVar5) goto LAB_00610230;
    if (*(char *)(param_1 + 0x36) == '\0') {
      fn_00611dc0((int)(param_1));
    }
    local_20 = *(uint *)(param_1 + 0x3c);
  }
  local_2c = local_20;
  local_38 = local_20;
  local_14 = *(int *)(param_1 + 0x20);
  if (local_14 != *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x14) + 4) + 0x10) + 2) * 8) {
    if (DAT_0070f22d == '\0') {
      iVar5 = 0x20;
    }
    else {
      iVar5 = 0x40;
    }
    if (iVar5 < local_14) {
      if (*(char *)(param_1 + 0x36) == '\0') {
        fn_00611dc0((int)(param_1));
      }
      local_14 = *(int *)(param_1 + 0x40);
    }
  }
  local_30 = local_20 + local_14;
  if (local_14 == 0) {
    return;
  }
  puVar1 = *(uint **)(local_24 + 0x14);
  for (puVar2 = puVar1; puVar2 != (uint *)0x0; puVar2 = (uint *)puVar2[5]) {
    if (((char *)puVar2[2] != (char *)0x0) && (*(int *)((int)puVar2 + 0x22) == local_18)) {
      local_34 = 0;
      uVar8 = *puVar2 >> 5;
      if ((uVar8 < *local_28) && ((local_28[uVar8 + 1] & 1 << ((byte)*puVar2 & 0x1f)) != 0)) {
        local_34 = 1;
      }
      if (((char)local_34 != '\0') && ((int)local_2c <= *(int *)((int)puVar2 + 0x3a)) &&
         (*(int *)((int)puVar2 + 0x3a) < local_30) && (*(char *)puVar2[2] == '\0')) {
        return;
      }
    }
  }
  iVar5 = 0;
  local_2c = local_2c & 0xffffff00;
  for (; puVar1 != (uint *)0x0; puVar1 = (uint *)puVar1[5]) {
    if (*(int *)((int)puVar1 + 0x22) == local_18) {
      bVar4 = false;
      uVar8 = *puVar1 >> 5;
      if ((uVar8 < *local_28) && ((local_28[uVar8 + 1] & 1 << ((byte)*puVar1 & 0x1f)) != 0)) {
        bVar4 = true;
      }
      if ((bVar4) && ((int)local_38 <= *(int *)((int)puVar1 + 0x3a)) &&
         (*(int *)((int)puVar1 + 0x3a) < local_30)) {
        pcVar3 = (char *)puVar1[2];
        iVar7 = *(int *)(pcVar3 + 0xe);
        if (iVar7 != 0) {
          if ((char)local_2c == '\0') {
            uVar8 = local_2c >> 8;
            local_2c = ((uVar8 << 8) | 1);
            iVar5 = iVar7;
          }
          else if (iVar5 != iVar7) {
            iVar5 = 0;
          }
        }
        if (*pcVar3 != '\0') {
          fn_005ed4c0((const char *)(aggregate_nopping_message), *(undefined4 *)(pcVar3 + 10));
          if ((*(uint *)(pcVar3 + 2) & 2) == 0) {
            fn_005ae7b0((uint)(pcVar3));
          }
          else {
            if (*pcVar3 == '\x02') {
              uVar11 = 0;
            }
            else {
              uVar11 = *(undefined4 *)(pcVar3 + 0x2e);
            }
            fn_005ae7b0((uint)(*(undefined4 *)(pcVar3 + 0x2a)));
            fn_005ac9f0((uint)(pcVar3), (uint)(uVar11));
            *pcVar3 = '\0';
            pcVar3[0x1a] = '\0';
            pcVar3[0x1b] = '\0';
            pcVar3[0x1c] = '\0';
            pcVar3[0x1d] = '\0';
          }
        }
      }
    }
  }
  fn_005ed4c0((const char *)(aggregate_adding_message), *(undefined4 *)(*(int *)(param_1 + 0x10) + 10), *(undefined4 *)(*(int *)(param_1 + 8) + 10));
  fn_005ad280((void *)(&assignment_list.head));
  if (local_14 == *(int *)(*(int *)(*(int *)(local_24 + 4) + 0x10) + 2) * 8) {
    fn_00610b40((int)(*(int *)(local_24 + 4)), (int)(*(undefined4 *)(local_18 + 4)), (int)(0), (int)(local_14), (undefined4)(iVar5), (int)(&assignment_list.head));
    goto LAB_0061052e;
  }
  if (*(int *)(param_1 + 0x20) ==
      *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_0061048b:
    iVar7 = *(int *)(param_1 + 0x1c);
  }
  else {
    if (DAT_0070f22d == '\0') {
      iVar7 = 0x20;
    }
    else {
      iVar7 = 0x40;
    }
    if (*(int *)(param_1 + 0x20) <= iVar7) goto LAB_0061048b;
    if (*(char *)(param_1 + 0x36) == '\0') {
      fn_00611dc0((int)(param_1));
    }
    iVar7 = *(int *)(param_1 + 0x3c);
  }
  iVar6 = *(int *)(param_1 + 0x20);
  if (iVar6 != *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x14) + 4) + 0x10) + 2) * 8) {
    if (DAT_0070f22d == '\0') {
      iVar10 = 0x20;
    }
    else {
      iVar10 = 0x40;
    }
    if (iVar10 < iVar6) {
      if (*(char *)(param_1 + 0x36) == '\0') {
        fn_00611dc0((int)(param_1));
      }
      iVar6 = *(int *)(param_1 + 0x40);
    }
  }
  uVar8 = iVar7 >> 0x1f & 7;
  iVar10 = 8 - ((iVar7 + uVar8 & 7) - uVar8);
  uVar8 = iVar10 >> 0x1f & 7;
  uVar9 = iVar6 + iVar7 >> 0x1f & 7;
  if (((iVar10 + uVar8 & 7) - uVar8) + ((iVar6 + iVar7 + uVar9 & 7) - uVar9) == 0) {
    fn_00610b40((int)(*(undefined4 *)(local_24 + 4)), (int)(*(undefined4 *)(local_18 + 4)), (int)(local_20), (int)(local_14), (undefined4)(iVar5), (int)(&assignment_list.head));
  }
  else {
    if (DAT_0070f22d == '\0') {
      iVar7 = 0x20;
    }
    else {
      iVar7 = 0x40;
    }
    if (local_14 <= iVar7) {
      fn_006106f0((int)(*(undefined4 *)(local_24 + 4)), (int)(*(undefined4 *)(local_18 + 4)), (int)(local_20), (int)(local_14), (undefined4)(iVar5), (int)(&assignment_list.head));
    }
  }
LAB_0061052e:
  fn_005ad440((uint)(assignment_list.head), (uint)(assignment_list.tail), (uint)(*(undefined4 *)(param_1 + 0x10)));
  return;
}

void fn_006106f0(int param_1, int param_2, int param_3, int param_4, undefined4 param_5,
                 int param_6)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int local_18;
  undefined *local_14;

  uVar6 = param_3 >> 0x1f & 7;
  iVar1 = (param_3 + uVar6 & 7) - uVar6;
  iVar7 = param_4 + iVar1;
  if (DAT_00699c6e * 8 < iVar7) {
    local_14 = &DAT_00699c7c;
  }
  else if (DAT_00699c5e * 8 < iVar7) {
    local_14 = &DAT_00699c6c;
  }
  else if (DAT_00699c4e * 8 < iVar7) {
    local_14 = &DAT_00699c5c;
  }
  else if (DAT_00699c36 * 8 < iVar7) {
    local_14 = &DAT_00699c4c;
  }
  else if (iVar7 > 0) {
    local_14 = &DAT_00699c34;
  }
  puVar2 = (undefined1 *)galloc((int)(0xc));
  memclrw((void *)(puVar2), (int)(0xc));
  *puVar2 = 8;
  *(undefined4 *)(puVar2 + 2) = *(undefined4 *)(local_14 + 2);
  *(undefined **)(puVar2 + 6) = local_14;
  puVar2[10] = (char)iVar1;
  puVar2[0xb] = (undefined1)param_4;
  iVar1 = (int)(param_3 + (param_3 >> 0x1f & 7U)) >> 3;
  if (iVar1 != 0) {
    if (iVar1 < 0) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 0;
    }
    uVar5 = fn_005b5760();
    local_18 = fn_005ab970((uint)(uVar3), (uint)(iVar1), (uint)(uVar5));
    *(uint *)(local_18 + 2) = *(uint *)(local_18 + 2) | 2;
    fn_005ad220((uint)(local_18), (void *)(param_6));
  }
  iVar7 = fn_005bd630((int)(1));
  *(undefined1 *)(iVar7 + 1) = 0x3b;
  uVar3 = fn_00521c20((int)(param_2), (byte)(1));
  *(undefined4 *)(iVar7 + 0x2a) = uVar3;
  uVar3 = fn_005b7d30((uint)(*(undefined4 *)(*(int *)(iVar7 + 0x2a) + 4)));
  *(undefined4 *)(iVar7 + 0x12) = uVar3;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar7 + 10) = DAT_00710998;
  *(uint *)(iVar7 + 2) = *(uint *)(iVar7 + 2) | 0x22;
  fn_005ad220((uint)(iVar7), (void *)(param_6));
  if (iVar1 != 0) {
    iVar7 = fn_005bd630((int)(3));
    *(undefined1 *)(iVar7 + 1) = 0xf;
    uVar3 = fn_005b7d30((uint)(*(undefined4 *)(*(int *)(param_6 + 4) + 0x12)));
    *(undefined4 *)(iVar7 + 0x12) = uVar3;
    *(undefined4 *)(iVar7 + 0x2a) = *(undefined4 *)(param_6 + 4);
    *(int *)(iVar7 + 0x2e) = local_18;
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar7 + 10) = DAT_00710998;
    *(uint *)(iVar7 + 2) = *(uint *)(iVar7 + 2) | 2;
    fn_005ad220((uint)(iVar7), (void *)(param_6));
  }
  iVar7 = fn_005bd630((int)(2));
  *(undefined1 *)(iVar7 + 1) = 0x33;
  uVar3 = fn_005b7d30((uint)(puVar2));
  *(undefined4 *)(iVar7 + 0x12) = uVar3;
  *(undefined4 *)(iVar7 + 0x2a) = *(undefined4 *)(param_6 + 4);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar7 + 10) = DAT_00710998;
  *(uint *)(iVar7 + 2) = *(uint *)(iVar7 + 2) | 0x22;
  fn_005ad220((uint)(iVar7), (void *)(param_6));
  iVar7 = fn_005bd630((int)(2));
  *(undefined1 *)(iVar7 + 1) = 4;
  uVar3 = fn_005b7d30((uint)(local_14));
  *(undefined4 *)(iVar7 + 0x12) = uVar3;
  *(undefined4 *)(iVar7 + 0x2a) = *(undefined4 *)(param_6 + 4);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar7 + 10) = DAT_00710998;
  *(uint *)(iVar7 + 2) = *(uint *)(iVar7 + 2) | 2;
  fn_005ad220((uint)(iVar7), (void *)(param_6));
  if (iVar1 != 0) {
    if (iVar1 < 0) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 0;
    }
    iVar4 = iVar1;
    uVar5 = fn_005b5760();
    local_18 = fn_005ab970((uint)(uVar3), (uint)(iVar4), (uint)(uVar5));
    *(uint *)(local_18 + 2) = *(uint *)(local_18 + 2) | 2;
    fn_005ad220((uint)(local_18), (void *)(param_6));
  }
  iVar4 = fn_005bd630((int)(1));
  *(undefined1 *)(iVar4 + 1) = 0x3b;
  uVar3 = fn_00521c20((int)(param_1), (byte)(1));
  *(undefined4 *)(iVar4 + 0x2a) = uVar3;
  uVar3 = fn_005b7d30((uint)(*(undefined4 *)(*(int *)(iVar4 + 0x2a) + 4)));
  *(undefined4 *)(iVar4 + 0x12) = uVar3;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 0x26;
  fn_005ad220((uint)(iVar4), (void *)(param_6));
  if (iVar1 != 0) {
    iVar1 = fn_005bd630((int)(3));
    *(undefined1 *)(iVar1 + 1) = 0xf;
    uVar3 = fn_005b7d30((uint)(*(undefined4 *)(*(int *)(param_6 + 4) + 0x12)));
    *(undefined4 *)(iVar1 + 0x12) = uVar3;
    *(undefined4 *)(iVar1 + 0x2a) = *(undefined4 *)(param_6 + 4);
    *(int *)(iVar1 + 0x2e) = local_18;
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar1 + 10) = DAT_00710998;
    *(uint *)(iVar1 + 2) = *(uint *)(iVar1 + 2) | 2;
    fn_005ad220((uint)(iVar1), (void *)(param_6));
  }
  iVar1 = fn_005bd630((int)(2));
  *(undefined1 *)(iVar1 + 1) = 0x33;
  uVar3 = fn_005b7d30((uint)(puVar2));
  *(undefined4 *)(iVar1 + 0x12) = uVar3;
  *(undefined4 *)(iVar1 + 0x2a) = *(undefined4 *)(param_6 + 4);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar1 + 10) = DAT_00710998;
  *(uint *)(iVar1 + 2) = *(uint *)(iVar1 + 2) | 0x22;
  fn_005ad220((uint)(iVar1), (void *)(param_6));
  iVar1 = fn_005bd630((int)(2));
  *(undefined1 *)(iVar1 + 1) = 4;
  uVar3 = fn_005b7d30((uint)(local_14));
  *(undefined4 *)(iVar1 + 0x12) = uVar3;
  *(undefined4 *)(iVar1 + 0x2a) = *(undefined4 *)(param_6 + 4);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar1 + 10) = DAT_00710998;
  *(uint *)(iVar1 + 2) = *(uint *)(iVar1 + 2) | 6;
  fn_005ad220((uint)(iVar1), (void *)(param_6));
  iVar1 = fn_005bd630((int)(3));
  *(undefined1 *)(iVar1 + 1) = 0x1e;
  *(undefined4 *)(iVar1 + 0x2a) = *(undefined4 *)(param_6 + 4);
  *(int *)(iVar1 + 0x2e) = iVar7;
  uVar3 = fn_005b7d30((uint)(local_14));
  *(undefined4 *)(iVar1 + 0x12) = uVar3;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar1 + 10) = DAT_00710998;
  *(undefined4 *)(iVar1 + 0xe) = param_5;
  fn_005ad220((uint)(iVar1), (void *)(param_6));
  return;
}

void fn_00610b40(int param_1, int param_2, int param_3, int param_4, undefined4 param_5,
                 int param_6)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int local_18;

  puVar6 = *(undefined **)(param_1 + 0x10);
  if (param_4 != *(int *)(puVar6 + 2) * 8) {
    if (param_4 == DAT_00699c36 * 8) {
      puVar6 = &DAT_00699c34;
    }
    else if (param_4 == DAT_00699c4e * 8) {
      puVar6 = &DAT_00699c4c;
    }
    else if (param_4 == DAT_00699c5e * 8) {
      puVar6 = &DAT_00699c5c;
    }
    else if (param_4 == DAT_00699c6e * 8) {
      puVar6 = &DAT_00699c6c;
    }
    else if (param_4 == DAT_00699c7e * 8) {
      puVar6 = &DAT_00699c7c;
    }
    else {
      puVar6 = (undefined *)CDecl_NewOpaqueType((int)((int)(param_4 + (param_4 >> 0x1f & 7U)) >> 3), (int)(1));
    }
  }
  iVar1 = (int)(param_3 + (param_3 >> 0x1f & 7U)) >> 3;
  if (iVar1 != 0) {
    if (iVar1 < 0) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 0;
    }
    iVar2 = iVar1;
    uVar5 = fn_005b5760();
    local_18 = fn_005ab970((uint)(uVar3), (uint)(iVar2), (uint)(uVar5));
    *(uint *)(local_18 + 2) = *(uint *)(local_18 + 2) | 2;
    fn_005ad220((uint)(local_18), (void *)(param_6));
  }
  iVar2 = fn_005bd630((int)(1));
  *(undefined1 *)(iVar2 + 1) = 0x3b;
  uVar3 = fn_00521c20((int)(param_2), (byte)(1));
  *(undefined4 *)(iVar2 + 0x2a) = uVar3;
  uVar3 = fn_005b7d30((uint)(*(undefined4 *)(*(int *)(iVar2 + 0x2a) + 4)));
  *(undefined4 *)(iVar2 + 0x12) = uVar3;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar2 + 10) = DAT_00710998;
  *(uint *)(iVar2 + 2) = *(uint *)(iVar2 + 2) | 0x22;
  fn_005ad220((uint)(iVar2), (void *)(param_6));
  if (iVar1 != 0) {
    iVar2 = fn_005bd630((int)(3));
    *(undefined1 *)(iVar2 + 1) = 0xf;
    uVar3 = fn_005b7d30((uint)(*(undefined4 *)(*(int *)(param_6 + 4) + 0x12)));
    *(undefined4 *)(iVar2 + 0x12) = uVar3;
    *(undefined4 *)(iVar2 + 0x2a) = *(undefined4 *)(param_6 + 4);
    *(int *)(iVar2 + 0x2e) = local_18;
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar2 + 10) = DAT_00710998;
    *(uint *)(iVar2 + 2) = *(uint *)(iVar2 + 2) | 2;
    fn_005ad220((uint)(iVar2), (void *)(param_6));
  }
  iVar2 = fn_005bd630((int)(2));
  *(undefined1 *)(iVar2 + 1) = 4;
  uVar3 = fn_005b7d30((uint)(puVar6));
  *(undefined4 *)(iVar2 + 0x12) = uVar3;
  *(undefined4 *)(iVar2 + 0x2a) = *(undefined4 *)(param_6 + 4);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar2 + 10) = DAT_00710998;
  *(uint *)(iVar2 + 2) = *(uint *)(iVar2 + 2) | 2;
  fn_005ad220((uint)(iVar2), (void *)(param_6));
  if (iVar1 != 0) {
    if (iVar1 < 0) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 0;
    }
    uVar5 = fn_005b5760();
    local_18 = fn_005ab970((uint)(uVar3), (uint)(iVar1), (uint)(uVar5));
    *(uint *)(local_18 + 2) = *(uint *)(local_18 + 2) | 2;
    fn_005ad220((uint)(local_18), (void *)(param_6));
  }
  iVar4 = fn_005bd630((int)(1));
  *(undefined1 *)(iVar4 + 1) = 0x3b;
  uVar3 = fn_00521c20((int)(param_1), (byte)(1));
  *(undefined4 *)(iVar4 + 0x2a) = uVar3;
  uVar3 = fn_005b7d30((uint)(*(undefined4 *)(*(int *)(iVar4 + 0x2a) + 4)));
  *(undefined4 *)(iVar4 + 0x12) = uVar3;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar4 + 10) = DAT_00710998;
  *(uint *)(iVar4 + 2) = *(uint *)(iVar4 + 2) | 0x26;
  fn_005ad220((uint)(iVar4), (void *)(param_6));
  if (iVar1 != 0) {
    iVar1 = fn_005bd630((int)(3));
    *(undefined1 *)(iVar1 + 1) = 0xf;
    uVar3 = fn_005b7d30((uint)(*(undefined4 *)(*(int *)(param_6 + 4) + 0x12)));
    *(undefined4 *)(iVar1 + 0x12) = uVar3;
    *(undefined4 *)(iVar1 + 0x2a) = *(undefined4 *)(param_6 + 4);
    *(int *)(iVar1 + 0x2e) = local_18;
    DAT_00710998 = DAT_00710998 + 1;
    *(int *)(iVar1 + 10) = DAT_00710998;
    *(uint *)(iVar1 + 2) = *(uint *)(iVar1 + 2) | 2;
    fn_005ad220((uint)(iVar1), (void *)(param_6));
  }
  iVar1 = fn_005bd630((int)(2));
  *(undefined1 *)(iVar1 + 1) = 4;
  uVar3 = fn_005b7d30((uint)(puVar6));
  *(undefined4 *)(iVar1 + 0x12) = uVar3;
  *(undefined4 *)(iVar1 + 0x2a) = *(undefined4 *)(param_6 + 4);
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar1 + 10) = DAT_00710998;
  *(uint *)(iVar1 + 2) = *(uint *)(iVar1 + 2) | 6;
  fn_005ad220((uint)(iVar1), (void *)(param_6));
  iVar1 = fn_005bd630((int)(3));
  *(undefined1 *)(iVar1 + 1) = 0x1e;
  *(undefined4 *)(iVar1 + 0x2a) = *(undefined4 *)(param_6 + 4);
  *(int *)(iVar1 + 0x2e) = iVar2;
  uVar3 = fn_005b7d30((uint)(puVar6));
  *(undefined4 *)(iVar1 + 0x12) = uVar3;
  DAT_00710998 = DAT_00710998 + 1;
  *(int *)(iVar1 + 10) = DAT_00710998;
  *(undefined4 *)(iVar1 + 0xe) = param_5;
  fn_005ad220((uint)(iVar1), (void *)(param_6));
  return;
}

int fn_00610f10(int *param_1, int *param_2)

{
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  bool bVar15;
  undefined4 local_30;
  undefined4 uStack_2c;
  volatile double benefit_right,benefit_left;
  double local_28;
  double local_20;
  int local_18;
  undefined4 uStack_14;

  iVar5 = *param_2;
  iVar4 = *param_1;
  if (*(char *)(iVar5 + 0x28) == '\0') {
    fn_006120b0((int)(iVar5));
  }
  if (*(int *)(iVar5 + 0x20) ==
      *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_00610f4b:
    local_28 = *(double *)(iVar5 + 0x2a);
  }
  else {
    if (DAT_0070f22d == '\0') {
      iVar2 = 0x20;
    }
    else {
      iVar2 = 0x40;
    }
    if (*(int *)(iVar5 + 0x20) <= iVar2) goto LAB_00610f4b;
    if (*(char *)(iVar5 + 0x36) == '\0') {
      fn_00611dc0((int)(iVar5));
    }
    local_28 = *(double *)(iVar5 + 0x44);
  }
  iVar2 = fn_005bf3e0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)**(ushort **)(iVar5 + 4) * 4)));
  benefit_right = (double)iVar2-local_28;
  if (*(char *)(iVar4 + 0x28) == '\0') {
    fn_006120b0((int)(iVar4));
  }
  if (*(int *)(iVar4 + 0x20) ==
      *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_00610fae:
    local_20 = *(double *)(iVar4 + 0x2a);
  }
  else {
    if (DAT_0070f22d == '\0') {
      iVar3 = 0x20;
    }
    else {
      iVar3 = 0x40;
    }
    if (*(int *)(iVar4 + 0x20) <= iVar3) goto LAB_00610fae;
    if (*(char *)(iVar4 + 0x36) == '\0') {
      fn_00611dc0((int)(iVar4));
    }
    local_20 = *(double *)(iVar4 + 0x44);
  }
  iVar3 = fn_005bf3e0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)**(ushort **)(iVar4 + 4) * 4)));
  /* Native unordered x87 results take the tie branch as well. */
  if (!(native_abs(benefit_right - ((double)iVar3 - local_20)) > aggregate_epsilon)) {
    if (*(char *)(iVar5 + 0x28) == '\0') {
      fn_006120b0((int)(iVar5));
    }
    if (*(int *)(iVar5 + 0x20) ==
        *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_00611150:
      iVar2 = *(int *)(iVar5 + 0x32);
    }
    else {
      if (DAT_0070f22d == '\0') {
        iVar2 = 0x20;
      }
      else {
        iVar2 = 0x40;
      }
      if (*(int *)(iVar5 + 0x20) <= iVar2) goto LAB_00611150;
      if (*(char *)(iVar5 + 0x36) == '\0') {
        fn_00611dc0((int)(iVar5));
      }
      iVar2 = *(int *)(iVar5 + 0x38);
    }
    if (*(char *)(iVar4 + 0x28) == '\0') {
      fn_006120b0((int)(iVar4));
    }
    if (*(int *)(iVar4 + 0x20) ==
        *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_0061117b:
      iVar3 = *(int *)(iVar4 + 0x32);
    }
    else {
      if (DAT_0070f22d == '\0') {
        iVar3 = 0x20;
      }
      else {
        iVar3 = 0x40;
      }
      if (*(int *)(iVar4 + 0x20) <= iVar3) goto LAB_0061117b;
      if (*(char *)(iVar4 + 0x36) == '\0') {
        fn_00611dc0((int)(iVar4));
      }
      iVar3 = *(int *)(iVar4 + 0x38);
    }
    if (iVar2 == iVar3) {
      if (*(int *)(iVar5 + 0x20) ==
          *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_00611234:
        iVar2 = *(int *)(iVar5 + 0x1c);
      }
      else {
        if (DAT_0070f22d == '\0') {
          iVar2 = 0x20;
        }
        else {
          iVar2 = 0x40;
        }
        if (*(int *)(iVar5 + 0x20) <= iVar2) goto LAB_00611234;
        if (*(char *)(iVar5 + 0x36) == '\0') {
          fn_00611dc0((int)(iVar5));
        }
        iVar2 = *(int *)(iVar5 + 0x3c);
      }
      iVar3 = *(int *)(iVar5 + 0x20);
      if (iVar3 != *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar8 = 0x20;
        }
        else {
          iVar8 = 0x40;
        }
        if (iVar8 < iVar3) {
          if (*(char *)(iVar5 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar5));
          }
          iVar3 = *(int *)(iVar5 + 0x40);
        }
      }
      uVar7 = iVar2 >> 0x1f & 7;
      iVar8 = 8 - ((iVar2 + uVar7 & 7) - uVar7);
      uVar7 = iVar8 >> 0x1f & 7;
      uVar9 = iVar3 + iVar2 >> 0x1f & 7;
      if (((iVar8 + uVar7 & 7) - uVar7) + ((iVar3 + iVar2 + uVar9 & 7) - uVar9) == 0) {
        if (*(int *)(iVar4 + 0x20) ==
            *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_006112ac:
          iVar2 = *(int *)(iVar4 + 0x1c);
        }
        else {
          if (DAT_0070f22d == '\0') {
            iVar2 = 0x20;
          }
          else {
            iVar2 = 0x40;
          }
          if (*(int *)(iVar4 + 0x20) <= iVar2) goto LAB_006112ac;
          if (*(char *)(iVar4 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar4));
          }
          iVar2 = *(int *)(iVar4 + 0x3c);
        }
        iVar3 = *(int *)(iVar4 + 0x20);
        if (iVar3 != *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
          if (DAT_0070f22d == '\0') {
            iVar8 = 0x20;
          }
          else {
            iVar8 = 0x40;
          }
          if (iVar8 < iVar3) {
            if (*(char *)(iVar4 + 0x36) == '\0') {
              fn_00611dc0((int)(iVar4));
            }
            iVar3 = *(int *)(iVar4 + 0x40);
          }
        }
        uVar7 = iVar2 >> 0x1f & 7;
        iVar8 = 8 - ((iVar2 + uVar7 & 7) - uVar7);
        uVar7 = iVar8 >> 0x1f & 7;
        uVar9 = iVar3 + iVar2 >> 0x1f & 7;
        if (((iVar8 + uVar7 & 7) - uVar7) + ((iVar3 + iVar2 + uVar9 & 7) - uVar9) != 0) {
          return (1);
        }
      }
      if (*(int *)(iVar5 + 0x20) ==
          *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_0061132e:
        iVar2 = *(int *)(iVar5 + 0x1c);
      }
      else {
        if (DAT_0070f22d == '\0') {
          iVar2 = 0x20;
        }
        else {
          iVar2 = 0x40;
        }
        if (*(int *)(iVar5 + 0x20) <= iVar2) goto LAB_0061132e;
        if (*(char *)(iVar5 + 0x36) == '\0') {
          fn_00611dc0((int)(iVar5));
        }
        iVar2 = *(int *)(iVar5 + 0x3c);
      }
      iVar3 = *(int *)(iVar5 + 0x20);
      if (iVar3 != *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar8 = 0x20;
        }
        else {
          iVar8 = 0x40;
        }
        if (iVar8 < iVar3) {
          if (*(char *)(iVar5 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar5));
          }
          iVar3 = *(int *)(iVar5 + 0x40);
        }
      }
      uVar7 = iVar2 >> 0x1f & 7;
      iVar8 = 8 - ((iVar2 + uVar7 & 7) - uVar7);
      uVar7 = iVar8 >> 0x1f & 7;
      uVar9 = iVar3 + iVar2 >> 0x1f & 7;
      if (((iVar8 + uVar7 & 7) - uVar7) + ((iVar3 + iVar2 + uVar9 & 7) - uVar9) != 0) {
        if (*(int *)(iVar4 + 0x20) ==
            *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_006113a2:
          iVar2 = *(int *)(iVar4 + 0x1c);
        }
        else {
          if (DAT_0070f22d == '\0') {
            iVar2 = 0x20;
          }
          else {
            iVar2 = 0x40;
          }
          if (*(int *)(iVar4 + 0x20) <= iVar2) goto LAB_006113a2;
          if (*(char *)(iVar4 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar4));
          }
          iVar2 = *(int *)(iVar4 + 0x3c);
        }
        iVar3 = *(int *)(iVar4 + 0x20);
        if (iVar3 != *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
          if (DAT_0070f22d == '\0') {
            iVar8 = 0x20;
          }
          else {
            iVar8 = 0x40;
          }
          if (iVar8 < iVar3) {
            if (*(char *)(iVar4 + 0x36) == '\0') {
              fn_00611dc0((int)(iVar4));
            }
            iVar3 = *(int *)(iVar4 + 0x40);
          }
        }
        uVar7 = iVar2 >> 0x1f & 7;
        iVar8 = 8 - ((iVar2 + uVar7 & 7) - uVar7);
        uVar7 = iVar8 >> 0x1f & 7;
        uVar9 = iVar3 + iVar2 >> 0x1f & 7;
        if (((iVar8 + uVar7 & 7) - uVar7) + ((iVar3 + iVar2 + uVar9 & 7) - uVar9) == 0) {
          return (0xffffffff);
        }
      }
      iVar2 = *(int *)(iVar5 + 0x20);
      if (iVar2 != *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar3 = 0x20;
        }
        else {
          iVar3 = 0x40;
        }
        if (iVar3 < iVar2) {
          if (*(char *)(iVar5 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar5));
          }
          iVar2 = *(int *)(iVar5 + 0x40);
        }
      }
      iVar3 = *(int *)(iVar4 + 0x20);
      if (iVar3 != *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar8 = 0x20;
        }
        else {
          iVar8 = 0x40;
        }
        if (iVar8 < iVar3) {
          if (*(char *)(iVar4 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar4));
          }
          iVar3 = *(int *)(iVar4 + 0x40);
        }
      }
      if (iVar2 != iVar3) {
        iVar2 = *(int *)(iVar5 + 0x20);
        if (iVar2 != *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
          if (DAT_0070f22d == '\0') {
            iVar3 = 0x20;
          }
          else {
            iVar3 = 0x40;
          }
          if (iVar3 < iVar2) {
            if (*(char *)(iVar5 + 0x36) == '\0') {
              fn_00611dc0((int)(iVar5));
            }
            iVar2 = *(int *)(iVar5 + 0x40);
          }
        }
        iVar5 = *(int *)(*(int *)(iVar4 + 0x14) + 4);
        iVar3 = *(int *)(iVar4 + 0x20);
        if (iVar3 != *(int *)(*(int *)(iVar5 + 0x10) + 2) * 8) {
          if (DAT_0070f22d == '\0') {
            iVar8 = 0x20;
          }
          else {
            iVar8 = 0x40;
          }
          if (iVar8 < iVar3) {
            if (*(char *)(iVar4 + 0x36) == '\0') {
              fn_00611dc0((int)(iVar4));
            }
            iVar3 = *(int *)(iVar4 + 0x40);
          }
        }
        return (iVar2 - iVar3);
      }
      if (*(int *)(iVar5 + 0x20) ==
          *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_006114d0:
        iVar2 = *(int *)(iVar5 + 0x1c);
      }
      else {
        if (DAT_0070f22d == '\0') {
          iVar2 = 0x20;
        }
        else {
          iVar2 = 0x40;
        }
        if (*(int *)(iVar5 + 0x20) <= iVar2) goto LAB_006114d0;
        if (*(char *)(iVar5 + 0x36) == '\0') {
          fn_00611dc0((int)(iVar5));
        }
        iVar2 = *(int *)(iVar5 + 0x3c);
      }
      iVar3 = *(int *)(iVar5 + 0x20);
      if (iVar3 != *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar8 = 0x20;
        }
        else {
          iVar8 = 0x40;
        }
        if (iVar8 < iVar3) {
          if (*(char *)(iVar5 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar5));
          }
          iVar3 = *(int *)(iVar5 + 0x40);
        }
      }
      uVar7 = iVar2 >> 0x1f & 7;
      iVar8 = 8 - ((iVar2 + uVar7 & 7) - uVar7);
      uVar7 = iVar8 >> 0x1f & 7;
      uVar9 = iVar3 + iVar2 >> 0x1f & 7;
      if (*(int *)(iVar4 + 0x20) ==
          *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_00611542:
        local_18 = *(int *)(iVar4 + 0x1c);
      }
      else {
        if (DAT_0070f22d == '\0') {
          iVar14 = 0x20;
        }
        else {
          iVar14 = 0x40;
        }
        if (*(int *)(iVar4 + 0x20) <= iVar14) goto LAB_00611542;
        if (*(char *)(iVar4 + 0x36) == '\0') {
          fn_00611dc0((int)(iVar4));
        }
        local_18 = *(int *)(iVar4 + 0x3c);
      }
      iVar14 = *(int *)(iVar4 + 0x20);
      if (iVar14 != *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar11 = 0x20;
        }
        else {
          iVar11 = 0x40;
        }
        if (iVar11 < iVar14) {
          if (*(char *)(iVar4 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar4));
          }
          iVar14 = *(int *)(iVar4 + 0x40);
        }
      }
      uVar10 = local_18 >> 0x1f & 7;
      iVar11 = 8 - ((local_18 + uVar10 & 7) - uVar10);
      uVar10 = iVar11 >> 0x1f & 7;
      uVar12 = local_18 + iVar14 >> 0x1f & 7;
      if (((iVar8 + uVar7 & 7) - uVar7) + ((iVar3 + iVar2 + uVar9 & 7) - uVar9) ==
          ((iVar11 + uVar10 & 7) - uVar10) + ((local_18 + iVar14 + uVar12 & 7) - uVar12)) {
        return 0;
      }
      if (*(int *)(iVar4 + 0x20) ==
          *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_006115c5:
        iVar2 = *(int *)(iVar4 + 0x1c);
      }
      else {
        if (DAT_0070f22d == '\0') {
          iVar2 = 0x20;
        }
        else {
          iVar2 = 0x40;
        }
        if (*(int *)(iVar4 + 0x20) <= iVar2) goto LAB_006115c5;
        if (*(char *)(iVar4 + 0x36) == '\0') {
          fn_00611dc0((int)(iVar4));
        }
        iVar2 = *(int *)(iVar4 + 0x3c);
      }
      iVar3 = *(int *)(iVar4 + 0x20);
      if (iVar3 != *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar8 = 0x20;
        }
        else {
          iVar8 = 0x40;
        }
        if (iVar8 < iVar3) {
          if (*(char *)(iVar4 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar4));
          }
          iVar3 = *(int *)(iVar4 + 0x40);
        }
      }
      uVar7 = iVar2 >> 0x1f & 7;
      iVar4 = 8 - ((iVar2 + uVar7 & 7) - uVar7);
      uVar7 = iVar4 >> 0x1f & 7;
      uVar9 = iVar3 + iVar2 >> 0x1f & 7;
      if (*(int *)(iVar5 + 0x20) !=
          *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar8 = 0x20;
        }
        else {
          iVar8 = 0x40;
        }
        if (iVar8 < *(int *)(iVar5 + 0x20)) {
          if (*(char *)(iVar5 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar5));
          }
          iVar8 = *(int *)(iVar5 + 0x3c);
          goto LAB_0061163a;
        }
      }
      iVar8 = *(int *)(iVar5 + 0x1c);
LAB_0061163a:
      iVar14 = *(int *)(iVar5 + 0x20);
      if (iVar14 != *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
        if (DAT_0070f22d == '\0') {
          iVar11 = 0x20;
        }
        else {
          iVar11 = 0x40;
        }
        if (iVar11 < iVar14) {
          if (*(char *)(iVar5 + 0x36) == '\0') {
            fn_00611dc0((int)(iVar5));
          }
          iVar14 = *(int *)(iVar5 + 0x40);
        }
      }
      uVar10 = iVar8 >> 0x1f & 7;
      iVar5 = 8 - ((iVar8 + uVar10 & 7) - uVar10);
      uVar10 = iVar5 >> 0x1f & 7;
      uVar12 = iVar14 + iVar8 >> 0x1f;
      uVar13 = uVar12 & 7;
      return ((uint)(((iVar4 + uVar7 & 7) - uVar7) +
                                     ((iVar3 + iVar2 + uVar9 & 7) - uVar9) !=
                                    ((iVar5 + uVar10 & 7) - uVar10) +
                                    ((iVar14 + iVar8 + uVar13 & 7) - uVar13)));
    }
    if (*(char *)(iVar5 + 0x28) == '\0') {
      fn_006120b0((int)(iVar5));
    }
    if (*(int *)(iVar5 + 0x20) ==
        *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_006111ae:
      iVar5 = *(int *)(iVar5 + 0x32);
    }
    else {
      if (DAT_0070f22d == '\0') {
        iVar2 = 0x20;
      }
      else {
        iVar2 = 0x40;
      }
      if (*(int *)(iVar5 + 0x20) <= iVar2) goto LAB_006111ae;
      if (*(char *)(iVar5 + 0x36) == '\0') {
        fn_00611dc0((int)(iVar5));
      }
      iVar5 = *(int *)(iVar5 + 0x38);
    }
    if (*(char *)(iVar4 + 0x28) == '\0') {
      fn_006120b0((int)(iVar4));
    }
    iVar2 = *(int *)(*(int *)(iVar4 + 0x14) + 4);
    if (*(int *)(iVar4 + 0x20) != *(int *)(*(int *)(iVar2 + 0x10) + 2) * 8) {
      if (DAT_0070f22d == '\0') {
        iVar3 = 0x20;
      }
      else {
        iVar3 = 0x40;
      }
      if (iVar3 < *(int *)(iVar4 + 0x20)) {
        if (*(char *)(iVar4 + 0x36) == '\0') {
          fn_00611dc0((int)(iVar4));
        }
        iVar4 = *(int *)(iVar4 + 0x38);
        goto LAB_0061120a;
      }
    }
    iVar4 = *(int *)(iVar4 + 0x32);
LAB_0061120a:
    return (iVar5 - iVar4);
  }
  if (*(char *)(iVar4 + 0x28) == '\0') {
    fn_006120b0((int)(iVar4));
  }
  if (*(int *)(iVar4 + 0x20) ==
      *(int *)(*(int *)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 0x10) + 2) * 8) {
LAB_00611022:
    uStack_14 = *(undefined4 *)(iVar4 + 0x2e);
    local_18 = *(undefined4 *)(iVar4 + 0x2a);
  }
  else {
    if (DAT_0070f22d == '\0') {
      iVar2 = 0x20;
    }
    else {
      iVar2 = 0x40;
    }
    if (*(int *)(iVar4 + 0x20) <= iVar2) goto LAB_00611022;
    if (*(char *)(iVar4 + 0x36) == '\0') {
      fn_00611dc0((int)(iVar4));
    }
    uStack_14 = *(undefined4 *)(iVar4 + 0x48);
    local_18 = *(undefined4 *)(iVar4 + 0x44);
  }
  iVar4 = fn_005bf3e0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)**(ushort **)(iVar4 + 4) * 4)));
  benefit_left = (double)iVar4-words_as_double(uStack_14,local_18);
  if (*(char *)(iVar5 + 0x28) == '\0') {
    fn_006120b0((int)(iVar5));
  }
  if (*(int *)(iVar5 + 0x20) !=
      *(int *)(*(int *)(*(int *)(*(int *)(iVar5 + 0x14) + 4) + 0x10) + 2) * 8) {
    if (DAT_0070f22d == '\0') {
      iVar2 = 0x20;
    }
    else {
      iVar2 = 0x40;
    }
    if (iVar2 < *(int *)(iVar5 + 0x20)) {
      if (*(char *)(iVar5 + 0x36) == '\0') {
        fn_00611dc0((int)(iVar5));
      }
      uStack_2c = *(undefined4 *)(iVar5 + 0x48);
      local_30 = *(undefined4 *)(iVar5 + 0x44);
      goto LAB_006110b9;
    }
  }
  uStack_2c = *(undefined4 *)(iVar5 + 0x2e);
  local_30 = *(undefined4 *)(iVar5 + 0x2a);
LAB_006110b9:
  iVar5 = fn_005bf3e0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)**(ushort **)(iVar5 + 4) * 4)));
  return (int)((benefit_left -
                 ((double)iVar5 - words_as_double(uStack_2c,local_30))) * aggregate_scale);
}

void fn_00611dc0(int param_1)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  short sVar8;
  uint uVar9;
  ushort uVar10;
  int iVar11;
  int local_28;
  int local_18;

  iVar2 = *(int *)(param_1 + 0x14);
  puVar3 = *(uint **)(param_1 + 0xc);
  iVar11 = *(int *)(param_1 + 0x18);
  local_28 = *(int *)(param_1 + 0x1c);
  local_18 = local_28 + *(int *)(param_1 + 0x20);
  while ((local_28 < local_18 && (uVar9 = local_28 >> 0x1f & 7, (local_28 + uVar9 & 7) != uVar9))) {
    for (puVar4 = *(uint **)(iVar2 + 0x14); puVar4 != (uint *)0x0; puVar4 = (uint *)puVar4[5]) {
      if ((puVar4[2] != 0) && (*(int *)((int)puVar4 + 0x22) == iVar11)) {
        bVar7 = false;
        uVar9 = *puVar4 >> 5;
        if ((uVar9 < *puVar3) && ((puVar3[uVar9 + 1] & 1 << ((byte)*puVar4 & 0x1f)) != 0)) {
          bVar7 = true;
        }
        if ((bVar7) && (*(int *)((int)puVar4 + 0x3a) == local_28)) {
          puVar1 = (uint *)(puVar4[2] + 2);
          *puVar1 = *puVar1 | 0x200000;
        }
      }
    }
    iVar5 = *(int *)(iVar2 + 0x14);
    for (iVar6 = iVar5; iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x14)) {
      if ((*(int *)(iVar6 + 8) != 0) && ((*(uint *)(*(int *)(iVar6 + 8) + 2) & 0x200000) != 0) &&
         (local_28 <= *(int *)(iVar6 + 0x3a))) {
        local_28 = *(int *)(iVar6 + 0x3a) + 1;
      }
    }
    for (; iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x14)) {
      if (*(int *)(iVar5 + 8) != 0) {
        puVar4 = (uint *)(*(int *)(iVar5 + 8) + 2);
        *puVar4 = *puVar4 & 0xffdfffff;
      }
    }
  }
  while ((local_28 < local_18 && (uVar9 = local_18 >> 0x1f & 7, (local_18 + uVar9 & 7) != uVar9))) {
    for (puVar4 = *(uint **)(iVar2 + 0x14); puVar4 != (uint *)0x0; puVar4 = (uint *)puVar4[5]) {
      if ((puVar4[2] != 0) && (*(int *)((int)puVar4 + 0x22) == iVar11)) {
        bVar7 = false;
        uVar9 = *puVar4 >> 5;
        if ((uVar9 < *puVar3) && ((puVar3[uVar9 + 1] & 1 << ((byte)*puVar4 & 0x1f)) != 0)) {
          bVar7 = true;
        }
        if ((bVar7) && (*(int *)((int)puVar4 + 0x3a) == local_18 - 1U)) {
          puVar1 = (uint *)(puVar4[2] + 2);
          *puVar1 = *puVar1 | 0x200000;
        }
      }
    }
    iVar5 = *(int *)(iVar2 + 0x14);
    for (iVar6 = iVar5; iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x14)) {
      if ((*(int *)(iVar6 + 8) != 0) && ((*(uint *)(*(int *)(iVar6 + 8) + 2) & 0x200000) != 0) &&
         (*(int *)(iVar6 + 0x3a) < local_18)) {
        local_18 = *(int *)(iVar6 + 0x3a);
      }
    }
    for (; iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x14)) {
      if (*(int *)(iVar5 + 8) != 0) {
        puVar4 = (uint *)(*(int *)(iVar5 + 8) + 2);
        *puVar4 = *puVar4 & 0xffdfffff;
      }
    }
  }
  *(int *)(param_1 + 0x3c) = local_28;
  *(int *)(param_1 + 0x40) = local_18 - local_28;
  for (puVar4 = *(uint **)(iVar2 + 0x14); puVar4 != (uint *)0x0; puVar4 = (uint *)puVar4[5]) {
    if ((puVar4[2] != 0) && (*(int *)((int)puVar4 + 0x22) == iVar11)) {
      bVar7 = false;
      uVar9 = *puVar4 >> 5;
      if ((uVar9 < *puVar3) && ((puVar3[uVar9 + 1] & 1 << ((byte)*puVar4 & 0x1f)) != 0)) {
        bVar7 = true;
      }
      if ((bVar7) && (local_28 <= *(int *)((int)puVar4 + 0x3a)) &&
         (*(int *)((int)puVar4 + 0x3a) < local_18)) {
        puVar1 = (uint *)(puVar4[2] + 2);
        *puVar1 = *puVar1 | 0x200000;
      }
    }
  }
  iVar11 = 0;
  uVar10 = 0;
  for (iVar2 = *(int *)(iVar2 + 0x14); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x14)) {
    if ((*(int *)(iVar2 + 8) != 0) && ((*(uint *)(*(int *)(iVar2 + 8) + 2) & 0x200000) != 0)) {
      sVar8 = fn_005bf3e0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)**(ushort **)(iVar2 + 4) * 4)));
      uVar10 = uVar10 + sVar8;
      iVar11 = iVar11 + 1;
      puVar3 = (uint *)(*(int *)(iVar2 + 8) + 2);
      *puVar3 = *puVar3 & 0xffdfffff;
    }
  }
  *(int *)(param_1 + 0x38) = iVar11;
  *(double *)(param_1 + 0x44) = (double)uVar10 / (double)iVar11;
  *(undefined1 *)(param_1 + 0x36) = 1;
  return;
}

void fn_006120b0(int param_1)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  bool bVar7;
  short sVar8;
  uint uVar9;
  int iVar10;
  ushort uVar11;

  iVar2 = *(int *)(param_1 + 0x14);
  puVar3 = *(uint **)(param_1 + 0xc);
  iVar10 = *(int *)(param_1 + 0x18);
  iVar4 = *(int *)(param_1 + 0x1c);
  iVar5 = *(int *)(param_1 + 0x20);
  for (puVar6 = *(uint **)(iVar2 + 0x14); puVar6 != (uint *)0x0; puVar6 = (uint *)puVar6[5]) {
    if ((puVar6[2] != 0) && (*(int *)((int)puVar6 + 0x22) == iVar10)) {
      bVar7 = false;
      uVar9 = *puVar6 >> 5;
      if ((uVar9 < *puVar3) && ((puVar3[uVar9 + 1] & 1 << ((byte)*puVar6 & 0x1f)) != 0)) {
        bVar7 = true;
      }
      if ((bVar7) && (iVar4 <= *(int *)((int)puVar6 + 0x3a)) &&
         (*(int *)((int)puVar6 + 0x3a) < iVar4 + iVar5)) {
        puVar1 = (uint *)(puVar6[2] + 2);
        *puVar1 = *puVar1 | 0x200000;
      }
    }
  }
  iVar10 = 0;
  uVar11 = 0;
  for (iVar2 = *(int *)(iVar2 + 0x14); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x14)) {
    if ((*(int *)(iVar2 + 8) != 0) && ((*(uint *)(*(int *)(iVar2 + 8) + 2) & 0x200000) != 0)) {
      sVar8 = fn_005bf3e0((uint)(*(undefined4 *)(aggregate_block_bitmaps + (uint)**(ushort **)(iVar2 + 4) * 4)));
      uVar11 = uVar11 + sVar8;
      iVar10 = iVar10 + 1;
      puVar3 = (uint *)(*(int *)(iVar2 + 8) + 2);
      *puVar3 = *puVar3 & 0xffdfffff;
    }
  }
  *(int *)(param_1 + 0x32) = iVar10;
  *(double *)(param_1 + 0x2a) = (double)uVar11 / (double)iVar10;
  *(undefined1 *)(param_1 + 0x28) = 1;
  return;
}

void fn_006121c0(int param_1, int param_2, int param_3, uint param_4)

{
  int *piVar1;
  uint *local_14;

  local_14 = (uint *)0x0;
  if ((aggregate_source_cache == (int *)0x0) || (*aggregate_source_cache != param_3)) {
    for (piVar1 = *(int **)(param_2 + 4); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[2]) {
      if (*piVar1 == param_3) {
        local_14 = (uint *)piVar1[1];
        aggregate_source_cache = piVar1;
        break;
      }
    }
  }
  else {
    local_14 = (uint *)aggregate_source_cache[1];
  }
  if (local_14 == (uint *)0x0) {
    piVar1 = (int *)fn_004c5480((int)(0xc));
    *piVar1 = 0;
    piVar1[1] = 0;
    piVar1[2] = 0;
    *piVar1 = param_3;
    fn_005bfae0((void *)(&local_14), (uint)(*(int *)(*(int *)(*(int *)(param_1 + 4) + 0x10) + 2) * 8));
    piVar1[1] = (int)local_14;
    piVar1[2] = *(int *)(param_2 + 4);
    *(int **)(param_2 + 4) = piVar1;
    aggregate_source_cache = piVar1;
  }
  if (param_4 >> 5 < *local_14) {
    local_14[(param_4 >> 5) + 1] = local_14[(param_4 >> 5) + 1] | 1 << ((byte)param_4 & 0x1f);
  }
  else {
    CError_Internal((const char *)(s_BitVector_h_00698a16), (int)(0x52));
  }
  return;
}

int fn_006122c0(char *param_1, int param_2, int param_3, char param_4)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  bool bVar7;
  int local_1c;
  int local_18;
  int local_14;

  if (param_1 == (char *)0x0) {
    return 0;
  }
  if (*param_1 != '\x03') {
    return 0;
  }
  if (param_1[1] != '\x1e') {
    return 0;
  }
  pcVar6 = *(char **)(param_1 + 0x12);
  if ((*pcVar6 == '\x05') || (*pcVar6 == '\x06' && (cVar2 = fn_00542340((char *)(pcVar6)), cVar2 != '\0'))) {
    if (*pcVar6 == '\x05') {
      if (*(int *)(pcVar6 + 10) == 0) {
LAB_00612450:
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(*(int *)(pcVar6 + 10) + 4);
      }
    }
    else if (*(int *)(pcVar6 + 0xe) == 0) {
      if (*(int *)(pcVar6 + 0x16) == 0) goto LAB_00612450;
      iVar3 = *(int *)(*(int *)(pcVar6 + 0x16) + 0xc);
    }
    else {
      iVar3 = *(int *)(*(int *)(pcVar6 + 0xe) + 4);
    }
    bVar7 = iVar3 != 0;
  }
  else {
    bVar7 = false;
  }
  if (bVar7) {
    return 0;
  }
  if (*param_1 == '\x02') {
    pcVar6 = (char *)0x0;
  }
  else {
    pcVar6 = *(char **)(param_1 + 0x2e);
  }
  if (pcVar6 == (char *)0x0) {
    return 0;
  }
  if (*pcVar6 != '\x02') {
    return 0;
  }
  if (pcVar6[1] != '\x04') {
    return 0;
  }
  iVar3 = fn_005b34b0((uint)(*(undefined4 *)(pcVar6 + 0x2a)));
  if (iVar3 == 0) {
    return 0;
  }
  iVar4 = fn_005b34c0((uint)(param_1));
  if (iVar4 == 0) {
    return 0;
  }
  if (iVar3 == iVar4) {
    return 0;
  }
  pcVar1 = *(char **)(*(int *)(iVar3 + 4) + 0x10);
  if ((*pcVar1 == '\x05') || (*pcVar1 == '\x06' && (cVar2 = fn_00542340((char *)(pcVar1)), cVar2 != '\0'))) {
    if (*pcVar1 == '\x05') {
      if (*(int *)(pcVar1 + 10) == 0) {
LAB_006124c5:
        iVar5 = 0;
      }
      else {
        iVar5 = *(int *)(*(int *)(pcVar1 + 10) + 4);
      }
    }
    else if (*(int *)(pcVar1 + 0xe) == 0) {
      if (*(int *)(pcVar1 + 0x16) == 0) goto LAB_006124c5;
      iVar5 = *(int *)(*(int *)(pcVar1 + 0x16) + 0xc);
    }
    else {
      iVar5 = *(int *)(*(int *)(pcVar1 + 0xe) + 4);
    }
    bVar7 = iVar5 != 0;
  }
  else {
    bVar7 = false;
  }
  if (!bVar7) {
    return 0;
  }
  pcVar1 = *(char **)(*(int *)(iVar4 + 4) + 0x10);
  if ((*pcVar1 != '\x05') && (*pcVar1 != '\x06' || (cVar2 = fn_00542340((char *)(pcVar1)), cVar2 == '\0'))) {
    bVar7 = false;
    goto LAB_00612399;
  }
  if (*pcVar1 == '\x05') {
    if (*(int *)(pcVar1 + 10) == 0) {
LAB_00612530:
      iVar5 = 0;
    }
    else {
      iVar5 = *(int *)(*(int *)(pcVar1 + 10) + 4);
    }
  }
  else {
    local_14 = *(int *)(pcVar1 + 0xe);
    if (local_14 == 0) {
      if (*(int *)(pcVar1 + 0x16) == 0) goto LAB_00612530;
      iVar5 = *(int *)(*(int *)(pcVar1 + 0x16) + 0xc);
    }
    else {
      iVar5 = *(int *)(local_14 + 4);
    }
  }
  bVar7 = iVar5 != 0;
LAB_00612399:
  if ((bVar7) &&
     (cVar2 = fn_005b7e20((uint)(*(undefined4 *)(*(int *)(iVar3 + 4) + 0x10)), (uint)(*(undefined4 *)(*(int *)(iVar4 + 4) + 0x10))), cVar2 != '\0') &&
     (cVar2 = fn_005b3050((uint)(*(undefined4 *)(pcVar6 + 0x2a)), (int)(iVar3), (int *)(&local_1c), (int *)(&local_18)),
     cVar2 != '\0') && (local_1c == param_2 && (local_18 == param_3) && (param_4 != '\0'))) {
    return iVar3;
  }
  return 0;
}

void fn_00612570(char *param_1, undefined4 param_2, int param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  bool bVar7;
  undefined4 *local_18;

  if ((*param_1 != '\x05') && (*param_1 != '\x06' || (cVar1 = fn_00542340((char *)(param_1)), cVar1 == '\0'))
     ) {
    bVar7 = false;
    goto LAB_00612596;
  }
  if (*param_1 == '\x05') {
    if (*(int *)(param_1 + 10) == 0) {
LAB_00612721:
      iVar5 = 0;
    }
    else {
      iVar5 = *(int *)(*(int *)(param_1 + 10) + 4);
    }
  }
  else if (*(int *)(param_1 + 0xe) == 0) {
    if (*(int *)(param_1 + 0x16) == 0) goto LAB_00612721;
    iVar5 = *(int *)(*(int *)(param_1 + 0x16) + 0xc);
  }
  else {
    iVar5 = *(int *)(*(int *)(param_1 + 0xe) + 4);
  }
  bVar7 = iVar5 != 0;
LAB_00612596:
  if (bVar7) {
    cVar1 = *param_1;
    if (cVar1 == '\x05') {
      puVar6 = *(undefined4 **)(param_1 + 10);
    }
    else {
      local_18 = *(undefined4 **)(param_1 + 0xe);
      puVar6 = *(undefined4 **)(param_1 + 0x16);
    }
LAB_006125c0:
    if (cVar1 == '\x05') {
      if (puVar6 == (undefined4 *)0x0) {
LAB_006125e2:
        pcVar4 = (char *)0x0;
      }
      else {
        pcVar4 = (char *)puVar6[1];
      }
    }
    else if (local_18 == (undefined4 *)0x0) {
      if (puVar6 == (undefined4 *)0x0) goto LAB_006125e2;
      pcVar4 = (char *)puVar6[3];
    }
    else {
      pcVar4 = (char *)local_18[1];
    }
    if (pcVar4 != (char *)0x0) {
      if (cVar1 == '\x05') {
        if (puVar6 == (undefined4 *)0x0) {
LAB_00612612:
          iVar5 = 0;
        }
        else {
          iVar5 = puVar6[3];
        }
      }
      else if (local_18 == (undefined4 *)0x0) {
        if (puVar6 == (undefined4 *)0x0) goto LAB_00612612;
        iVar5 = puVar6[5];
      }
      else {
        iVar5 = local_18[2];
      }
      iVar5 = iVar5 * 8;
      if ((*pcVar4 == '\x05') ||
         (*pcVar4 == '\x06' && (cVar1 = fn_00542340((char *)(pcVar4)), cVar1 != '\0'))) {
        if (*pcVar4 == '\x05') {
          if (*(int *)(pcVar4 + 10) == 0) {
LAB_006127a0:
            iVar3 = 0;
          }
          else {
            iVar3 = *(int *)(*(int *)(pcVar4 + 10) + 4);
          }
        }
        else if (*(int *)(pcVar4 + 0xe) == 0) {
          if (*(int *)(pcVar4 + 0x16) == 0) goto LAB_006127a0;
          iVar3 = *(int *)(*(int *)(pcVar4 + 0x16) + 0xc);
        }
        else {
          iVar3 = *(int *)(*(int *)(pcVar4 + 0xe) + 4);
        }
        bVar7 = iVar3 != 0;
      }
      else {
        bVar7 = false;
      }
      if (bVar7) {
        fn_00612570((char *)(pcVar4), (undefined4)(param_2), (int)(iVar5 + param_3));
      }
      else {
        if (*pcVar4 == '\b') {
          iVar5 = iVar5 + (uint)(byte)pcVar4[10];
          uVar2 = (uint)(byte)pcVar4[0xb];
        }
        else {
          uVar2 = *(int *)(pcVar4 + 2) * 8;
        }
        iVar3 = uVar2 + iVar5;
        for (; iVar5 < iVar3; iVar5 = iVar5 + 1) {
          IroBitVect_ClearBit((uint)(iVar5 + param_3), (uint)(param_2));
        }
      }
      cVar1 = *param_1;
      if (cVar1 == '\x05') {
        if (puVar6 != (undefined4 *)0x0) {
          puVar6 = (undefined4 *)*puVar6;
        }
      }
      else if (local_18 == (undefined4 *)0x0) {
        if (puVar6 != (undefined4 *)0x0) {
          puVar6 = (undefined4 *)puVar6[1];
        }
      }
      else {
        local_18 = (undefined4 *)*local_18;
      }
      goto LAB_006125c0;
    }
  }
  else {
    iVar5 = *(int *)(param_1 + 2);
    for (iVar3 = param_3; iVar3 < param_3 + iVar5 * 8; iVar3 = iVar3 + 1) {
      IroBitVect_ClearBit((uint)(iVar3 + param_3), (uint)(param_2));
    }
  }
  return;
}

undefined4 *
fn_00612810(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8,
            undefined4 param_9)

{
  uint *entry=(uint *)fn_004c5480((int)(76));
  __builtin_memset(entry,0,76);
  entry[0]=param_1;entry[1]=param_2;entry[2]=param_3;entry[3]=param_4;
  entry[4]=param_5;entry[5]=param_6;entry[6]=param_7;entry[7]=param_8;entry[8]=param_9;
  entry[9]=0;
  if(aggregate_queue_head)aggregate_queue_tail[9]=(uint)entry;
  else aggregate_queue_head=entry;
  aggregate_queue_tail=entry;++aggregate_queue_count;return entry;
}
