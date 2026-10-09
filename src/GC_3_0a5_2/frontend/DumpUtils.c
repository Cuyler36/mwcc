/* GC 3.0a5.2 DumpUtils.c, recovered from native calls and filename assertions.
 * Native display and memory-node layouts preserve 32-bit pointer fields.
 * The 0x1234-byte dump record and five-word memory-file nodes use native offsets.
 */
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned int uint;
typedef unsigned char bool;
typedef struct NativeDumpNode { uint *handle; char *buffer; int capacity; int used; struct NativeDumpNode *next; } NativeDumpNode;
typedef char NativeDumpNodeSizeCheck[sizeof(NativeDumpNode)==20 ? 1 : -1];
extern uint __builtin_strlen(const char *);
typedef struct NativeDisplayRecord { uint filename; uint handle; undefined1 flags; } NativeDisplayRecord;
extern void *__builtin_memset(void *, int, unsigned int);
#define true 1
#define false 0
static char dump_out_of_memory[] = "<out of memory>";
static char dump_filename[] = "DumpUtils.c";
static char dump_memfile_assertion[] = "!dump->memfile->next";
static char dump_env_primary[] = "TEMP";
static char dump_env_secondary[] = "TMP";

extern unsigned int fn_00404050(int, int);
extern unsigned int fn_00404070(int, int, int);
extern unsigned int fn_00404850(int, int, int);
extern unsigned int fn_004057a0(int);
extern unsigned int fn_004057b0(int);
extern unsigned int fn_00405820(int, int);
extern unsigned int fn_00407f50(int, int, int, int);
extern unsigned int fn_0040f1f0(int);
extern unsigned int __stdcall fn_00420490(int, int);
extern unsigned int __stdcall fn_004204e0(int, int, int, int);
extern unsigned int __stdcall fn_00420540(int, int, int);
extern unsigned int __stdcall fn_004205f0(int, int);
extern unsigned int __stdcall fn_00420680(int, int, int);
extern unsigned int __stdcall fn_004208e0(int, int);
extern void CLIO_ReportAssertionFailure(const char *, const char *, int, int);
extern unsigned int fn_0044ceb0(int);
extern unsigned int fn_0044cec0(int);
extern unsigned int fn_0044ced0(int);
extern unsigned int fn_0044cf40(int, int);
extern unsigned int fn_0044cfe0(int);
extern unsigned int fn_0044d0a0(int);
extern unsigned int fn_0044d170(int);
extern unsigned int fn_0044d1b0(int);
extern unsigned int fn_0044d3f0(int, int, int);
extern unsigned int fn_0044d730(int);
extern unsigned int fn_0044d740(int, int);
extern unsigned int fn_0044d7d0(int, int);
extern unsigned int fn_0044d7f0(int, int, int, int);
extern unsigned int fn_0044d810(int, int, int);
extern unsigned int fn_0044d850(int, int, int);
extern unsigned int fn_0044d890(int, int);
extern unsigned int fn_0044d8e0(int);
extern unsigned int fn_0044d9f0(int, int);
extern unsigned int fn_0044dea0(int, int, int);
extern unsigned int fn_0044e080(int);

void Dump_Printf(unsigned int dump, const char *format, ...);
void fn_004eb740(undefined4 *param_1, undefined4 param_2, undefined4 param_3);
char *fn_004eb7d0(uint *, char *, int, const char *, char *);
int fn_004eb8e0(int param_1, int param_2, int param_3);
undefined4 Dump_CloseToWindow(undefined4 *param_1, char param_2);
int fn_004ebe40(int param_1, undefined4 *param_2);
int Dump_CloseToFile(int param_1);
int fn_004ebfc0(int param_1);
int fn_004ec320(int param_1);
int Dump_Open(int param_1, int param_2);
void Dump_FreeHandle(int *param_1);
undefined4 * Dump_NewHandle(undefined4 param_1);
int fn_004ec700(int param_1);
NativeDumpNode *fn_004ec860(int capacity);

void Dump_Printf(unsigned int dump, const char *format, ...)
{
    /* MSL_Common/Include/cstdarg, __INTEL__ __va_start expression. */
    char *args = (char *)((long)(&format) +
        ((((long)(&format + 1) - (long)(&format)) + 3) / 4 * 4));
    fn_004eb740((undefined4 *)dump, (undefined4)format, (undefined4)args);
}

void fn_004eb740(undefined4 *dump, undefined4 format, undefined4 args)
{
    char buffer[1024];
    char *allocation;
    if (!dump || (!dump[0x88] && !dump[0x48a]))
        return;
    allocation = fn_004eb7d0(dump, buffer, sizeof(buffer), (const char *)format, (char *)args);
    /* Native writes the original stack buffer even after allocating a larger one. */
    fn_004eb8e0((int)dump, (int)buffer, __builtin_strlen(buffer));
    if (allocation != buffer)
        fn_00420540(*dump, (int)allocation, 0);
}

char *fn_004eb7d0(uint *dump, char *buffer, int capacity, const char *format, char *args)
{
    char *allocation;
    int limit;
    int count;
    if (!buffer)
        return 0;
    limit = capacity - 1;
    allocation = buffer;
    count = (int)fn_00407f50((int)buffer, limit, (int)format, (int)args);
    if (count < 0) {
        do {
            if (allocation != buffer)
                fn_00420540(*dump, (int)allocation, 0);
            limit *= 2;
            if (fn_004204e0(*dump, limit, 0, (int)&allocation) || !allocation)
                return (char *)fn_00404070((int)buffer, (int)dump_out_of_memory, capacity);
            count = (int)fn_00407f50((int)allocation, limit, (int)format, (int)args);
        } while (count < 0);
    } else if (limit < count) {
        int required = count + 1;
        if (fn_004204e0(*dump, required, 0, (int)&allocation) || !allocation)
            return (char *)fn_00404070((int)buffer, (int)dump_out_of_memory, capacity);
        fn_00407f50((int)allocation, required, (int)format, (int)args);
    }
    return allocation;
}

int fn_004eb8e0(int param_1, int param_2, int param_3)
{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  int local_1c;
  int local_18;
  int local_14;

  local_14 = (int)(0);
  if ((param_1 == 0) || (*(int *)(param_1 + 0x220) == 0 && (*(int *)(param_1 + 0x1228) == 0))) {
    return -1;
  }
  if (*(char *)(param_1 + 0x219) != '\0') {
    return 0;
  }
  local_1c = (int)(fn_004057a0((int)(param_3 * 2 + 1)));
  if (local_1c == 0) {
    local_1c = (int)(param_2);
  }
  else {
    iVar6 = (int)(0);
    iVar7 = (int)(0);
    if (param_3 > 0) {
      do {
        cVar1 = (char)(*(char *)(param_2 + iVar6));
        if ((cVar1 == '\r') || (cVar1 == '\n')) {
          bVar8 = (bool)(false);
          if (cVar1 == '\r') {
            bVar8 = (bool)(*(char *)(param_2 + iVar6 + 1) == '\n');
          }
          *(undefined1 *)(local_1c + iVar7) = 10;
          iVar6 = (int)(iVar6 + bVar8 + 1);
          local_14 = (int)(local_14 + 1);
        }
        else {
          *(char *)(local_1c + iVar7) = cVar1;
          iVar6 = (int)(iVar6 + 1);
        }
        iVar7 = (int)(iVar7 + 1);
      } while (iVar6 < param_3);
    }
    *(undefined1 *)(local_1c + iVar7) = 0;
    param_3 = (int)(iVar7);
  }
LAB_004eb9b5:
  if (*(int *)(param_1 + 0x220) == 0) {
    if (*(int *)(param_1 + 0x1228) == 0) {
      local_14 = (int)(-1);
    }
    else {
      if ((*(int *)(param_1 + 0x1230) != 0) &&
         (*(int *)(param_1 + 0x1230) <= *(int *)(param_1 + 0x21c) + param_3)) {
        iVar6 = (int)(fn_004ec320((int)(param_1)));
        if (iVar6 != 0) goto LAB_004eb9b5;
        *(int *)(param_1 + 0x1230) = *(int *)(param_1 + 0x1230) << 1;
      }
      iVar6 = (int)(*(int *)(param_1 + 0x122c));
      iVar7 = (int)(iVar6);
      if (iVar6 == 0) {
        iVar7 = (int)(*(int *)(param_1 + 0x1228));
      }
      local_18 = (int)(0);
      if (param_3 > 0) {
        do {
          if (iVar7 == 0) {
            iVar5 = (int)(0);
          }
          else {
            iVar5 = (int)(0);
            iVar4 = (int)(iVar7);
            while ((iVar7 = iVar4, iVar7 != 0 && (iVar5 == 0))) {
              iVar5 = (int)(*(int *)(iVar7 + 8) - *(int *)(iVar7 + 0xc));
              if (param_3 < iVar5) {
                iVar5 = (int)(param_3);
              }
              if (iVar5 != 0) break;
              iVar4 = (int)(*(int *)(iVar7 + 0x10));
              iVar6 = (int)(iVar7);
            }
          }
          if (iVar5 == 0) {
            iVar7 = (int)(param_3);
            if (param_3 < 0x10001) {
              iVar7 = (int)(0x10000);
            }
            iVar7 = (int)(fn_004ec860((int)(iVar7)));
            if (iVar7 == 0) goto LAB_004ebc41;
            *(undefined4 *)(iVar7 + 0xc) = 0;
            if (iVar6 == 0) {
              *(int *)(param_1 + 0x1228) = iVar7;
            }
            else {
              *(int *)(iVar6 + 0x10) = iVar7;
            }
            *(int *)(param_1 + 0x122c) = iVar7;
            iVar5 = (int)(param_3);
          }
          fn_00404850((int)(*(int *)(iVar7 + 4) + *(int *)(iVar7 + 0xc)), (int)(local_1c + local_18), (int)(iVar5));
          *(int *)(iVar7 + 0xc) = *(int *)(iVar7 + 0xc) + iVar5;
          *(int *)(param_1 + 0x21c) = *(int *)(param_1 + 0x21c) + iVar5;
          local_18 = (int)(local_18 + iVar5);
          param_3 = (int)(param_3 - iVar5);
          if (param_3 < 1) break;
        } while( true );
      }
    }
  }
  else {
    iVar6 = (int)(param_3);
    iVar7 = (int)(local_1c);
    if (*(char *)(param_1 + 0x21a) == '\0') {
      uVar3 = (undefined4)(fn_0044d850((int)(*(int *)(param_1 + 0x220)), (int)(local_1c), (int)(param_3)));
      *(undefined4 *)(param_1 + 0x214) = uVar3;
      bVar8 = (bool)(*(int *)(param_1 + 0x214) == 0);
    }
    else {
      for (; iVar6 > 0; iVar6 = iVar6 - iVar4) {
        iVar5 = (int)(*(int *)(param_1 + 0x1224));
        iVar4 = (int)(iVar6);
        if ((uint)(iVar5 + iVar6) > 0x1000) {
          iVar4 = (int)(0x1000 - iVar5);
        }
        fn_00404850((int)(iVar5 + 0x224 + param_1), (int)(iVar7), (int)(iVar4));
        *(int *)(param_1 + 0x1224) = *(int *)(param_1 + 0x1224) + iVar4;
        uVar2 = (uint)(*(uint *)(param_1 + 0x1224));
        if (uVar2 > 0xfff) {
          if ((*(char *)(param_1 + 0x21a) != '\0') && (uVar2 != 0)) {
            uVar3 = (undefined4)(fn_0044d850((int)(*(undefined4 *)(param_1 + 0x220)), (int)(param_1 + 0x224), (int)(uVar2)));
            *(undefined4 *)(param_1 + 0x214) = uVar3;
            *(undefined4 *)(param_1 + 0x1224) = 0;
          }
          if (*(int *)(param_1 + 0x214) != 0) {
            bVar8 = (bool)(false);
            goto LAB_004eba78;
          }
        }
        iVar7 = (int)(iVar7 + iVar4);
      }
      bVar8 = (bool)(true);
    }
LAB_004eba78:
    if (!bVar8) {
      fn_0044d730((int)(*(undefined4 *)(param_1 + 0x220)));
      *(undefined4 *)(param_1 + 0x220) = 0;
      iVar6 = (int)(fn_004ebfc0((int)(param_1)));
      if (iVar6 == 0) {
        *(undefined1 *)(param_1 + 0x219) = 1;
        return 0;
      }
      goto LAB_004eb9b5;
    }
    *(int *)(param_1 + 0x21c) = *(int *)(param_1 + 0x21c) + param_3;
  }
  if ((local_1c != 0) && (local_1c != param_2)) {
    fn_004057b0((int)(local_1c));
  }
  return local_14;
LAB_004ebc41:
  iVar6 = (int)(fn_004ec320((int)(param_1)));
  if (iVar6 == 0) {
    *(undefined1 *)(param_1 + 0x219) = 1;
    return 0;
  }
  goto LAB_004eb9b5;
}

undefined4 Dump_CloseToWindow(undefined4 *param_1, char param_2)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int local_120;
  undefined1 local_11c [260];
  NativeDisplayRecord display;

  uVar3 = (undefined4)(0);
  if ((param_1 != (undefined4 *)0x0) && (param_1[0x88] != 0 || (param_1[0x48a] != 0))) {
    iVar1 = (int)(fn_004ebe40((int)(param_1), (undefined4 *)(&display.handle)));
    if (iVar1 == 0) {
      if (param_1[0x88] != 0) {
        if ((*(char *)((int)param_1 + 0x21a) != '\0') && (param_1[0x489] != 0)) {
          uVar2 = (undefined4)(fn_0044d850((int)(param_1[0x88]), (int)(param_1 + 0x89), (int)(param_1[0x489])));
          param_1[0x85] = (undefined4)(uVar2);
          param_1[0x489] = (undefined4)(0);
        }
        fn_0044d740((int)(param_1[0x88]), (int)(&local_120));
        fn_0044d730((int)(param_1[0x88]));
        param_1[0x88] = (undefined4)(0);
        if ((param_2 != '\0') || (local_120 != 0)) {
          fn_0044d9f0((int)(local_11c), (int)(param_1 + 1));
          uVar3 = (undefined4)(fn_004208e0((int)(*param_1), (int)(local_11c)));
        }
        param_1[0x88] = (undefined4)(0);
      }
    }
    else {
      param_1[0x48b] = (undefined4)(0);
      param_1[0x48a] = (undefined4)(param_1[0x48b]);
      fn_0044d8e0((int)(param_1 + 0x42));
      iVar1 = (int)(fn_00420680((int)(*param_1), (int)(display.handle), (int)(param_1[0x87])));
      if (iVar1 != 0) {
        fn_004205f0((int)(*param_1), (int)(display.handle));
        return 2;
      }
      if ((param_2 == '\0') && (param_1[0x87] == 0)) {
        fn_004205f0((int)(*param_1), (int)(display.handle));
      }
      else {
        if (*(char *)(param_1 + 0x86) == '\0') {
          display.filename = (uint)((undefined4*)(param_1 + 1));
        }
        else {
          display.filename = (uint)((undefined4*)((undefined4 *)0x0));
        }
        display.flags = (undefined1)(0);
        uVar3 = (undefined4)(fn_00420490((int)(*param_1), (int)(&display)));
      }
    }
    return uVar3;
  }
  return 2;
}

int fn_004ebe40(int param_1, undefined4 *param_2)
{
  int iVar1;
  undefined4 uVar2;

  if ((param_1 == 0) || (*(int *)(param_1 + 0x220) == 0 && (*(int *)(param_1 + 0x1228) == 0))) {
    return 0;
  }
  iVar1 = (int)(fn_004ebfc0((int)(param_1)));
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = (int)(fn_004ec700((int)(param_1)));
  if (iVar1 != 0) {
    if (*(int *)(*(int *)(param_1 + 0x1228) + 0x10) != 0) {
      CLIO_ReportAssertionFailure(dump_memfile_assertion, dump_filename, (int)(0), (int)(0x2c1));
    }
    fn_0044d0a0((int)(**(undefined4 **)(param_1 + 0x1228)));
    fn_0044cf40((int)(**(undefined4 **)(param_1 + 0x1228)), (int)(*(undefined4 *)(param_1 + 0x21c)));
    uVar2 = (undefined4)(fn_0044d170((int)(*(undefined4 *)(param_1 + 0x1228))));
    *param_2 = (undefined4)(uVar2);
    fn_0044d8e0((int)(param_1 + 0x108));
    fn_004057b0((int)(*(undefined4 *)(param_1 + 0x1228)));
    *(undefined4 *)(param_1 + 0x122c) = 0;
    *(undefined4 *)(param_1 + 0x1228) = *(undefined4 *)(param_1 + 0x122c);
    uVar2 = (undefined4)(fn_0044d1b0((int)(param_1 + 4)));
    fn_00404050((int)(param_1 + 4), (int)(uVar2));
    return param_1;
  }
  return 0;
}

int Dump_CloseToFile(int param_1)
{
  int iVar1;
  undefined4 uVar2;

  if ((param_1 != 0) && (*(int *)(param_1 + 0x220) != 0 || (*(int *)(param_1 + 0x1228) != 0))) {
    iVar1 = (int)(fn_004ec320((int)(param_1)));
    if (iVar1 != 0) {
      if ((*(char *)(param_1 + 0x21a) != '\0') && (*(int *)(param_1 + 0x1224) != 0)) {
        uVar2 = (undefined4)(fn_0044d850((int)(*(undefined4 *)(param_1 + 0x220)), (int)(param_1 + 0x224), (int)(*(int *)(param_1 + 0x1224))));
        *(undefined4 *)(param_1 + 0x214) = uVar2;
        *(undefined4 *)(param_1 + 0x1224) = 0;
      }
      fn_0044d730((int)(*(undefined4 *)(param_1 + 0x220)));
      *(undefined4 *)(param_1 + 0x220) = 0;
      return param_1;
    }
    return 0;
  }
  return 0;
}

int fn_004ebfc0(int param_1)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  char unaff_BL;
  undefined4 *unaff_ESI;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int local_18;
  undefined4 local_14;

  if (param_1 == 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x1228) != 0) {
    return param_1;
  }
  if (*(char *)(param_1 + 0x219) != '\0') {
    return 0;
  }
  local_18 = (int)(*(int *)(param_1 + 0x21c));
  if (local_18 == 0) {
    local_18 = (int)(0x10000);
  }
  puVar7 = (undefined4*)((undefined4 *)0x0);
  for (; local_18 > 0; local_18 = local_18 - puVar2[2]) {
    puVar2 = (undefined4*)((undefined4 *)fn_004ec860((int)(local_18)));
    if (puVar2 == (undefined4 *)0x0) goto joined_r0x004ec101;
    puVar5 = (undefined4*)(puVar2);
    puVar6 = (undefined4*)(puVar2);
    if (puVar7 != (undefined4 *)0x0) {
      unaff_ESI[4] = (undefined4)(puVar2);
      puVar5 = (undefined4*)((undefined4 *)unaff_ESI[4]);
      puVar6 = (undefined4*)(puVar7);
    }
    puVar2[3] = (undefined4)(0);
    puVar7 = (undefined4*)(puVar6);
    unaff_ESI = (undefined4*)(puVar5);
  }
LAB_004ec00a:
  *(undefined4 **)(param_1 + 0x122c) = puVar7;
  *(undefined4 *)(param_1 + 0x1228) = *(undefined4 *)(param_1 + 0x122c);
  if (*(int *)(param_1 + 0x1228) == 0) {
    *(undefined4 *)(param_1 + 0x214) = 8;
    return 0;
  }
  if ((*(int *)(param_1 + 0x220) == 0) &&
     (iVar3 = fn_0044d7d0((int)(param_1 + 0x108), (int)(param_1 + 0x220)), iVar3 != 0)) {
    *(undefined4 *)(param_1 + 0x220) = 0;
  }
  if (*(int *)(param_1 + 0x220) == 0) {
    return param_1;
  }
  if ((*(char *)(param_1 + 0x21a) != '\0') && (*(int *)(param_1 + 0x1224) != 0)) {
    uVar1 = (undefined4)(fn_0044d850((int)(*(int *)(param_1 + 0x220)), (int)(param_1 + 0x224), (int)(*(int *)(param_1 + 0x1224))));
    *(undefined4 *)(param_1 + 0x214) = uVar1;
    *(undefined4 *)(param_1 + 0x1224) = 0;
  }
  if (*(int *)(param_1 + 0x214) == 0) {
    uVar1 = (undefined4)(fn_0044d890((int)(*(undefined4 *)(param_1 + 0x220)), (int)(0)));
    *(undefined4 *)(param_1 + 0x214) = uVar1;
    if (*(int *)(param_1 + 0x214) == 0) {
      iVar3 = (int)(*(int *)(param_1 + 0x1228));
      while( true ) {
        if (iVar3 == 0) {
          *(undefined4 *)(param_1 + 0x122c) = 0;
          fn_0044d730((int)(*(undefined4 *)(param_1 + 0x220)));
          *(undefined4 *)(param_1 + 0x220) = 0;
          return param_1;
        }
        if (*(int *)(param_1 + 0x214) == 0) {
          uVar1 = (undefined4)(fn_0044d810((int)(*(undefined4 *)(param_1 + 0x220)), (int)(*(undefined4 *)(iVar3 + 4)), (int)(*(undefined4 *)(iVar3 + 8))));
          *(undefined4 *)(param_1 + 0x214) = uVar1;
          unaff_BL = (char)(*(int *)(param_1 + 0x214) != 0);
        }
        else {
          iVar4 = (int)(fn_0044d740((int)(*(undefined4 *)(param_1 + 0x220)), (int)(&local_14)));
          if ((iVar4 != 0) ||
             (iVar4 = fn_0044d810((int)(*(undefined4 *)(param_1 + 0x220)), (int)(*(undefined4 *)(iVar3 + 4)), (int)(local_14)), iVar4 != 0)) {
            unaff_BL = (char)('\x01');
          }
          *(undefined4 *)(iVar3 + 8) = local_14;
          *(undefined4 *)(param_1 + 0x1230) = 0;
        }
        if (unaff_BL != '\0') break;
        *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(iVar3 + 8);
        iVar3 = (int)(*(int *)(iVar3 + 0x10));
      }
      puVar7 = (undefined4*)(*(undefined4 **)(param_1 + 0x1228));
      while (puVar7 != (undefined4 *)0x0) {
        fn_0044ced0((int)(*puVar7));
        *puVar7 = (undefined4)(0);
        puVar2 = (undefined4*)((undefined4 *)puVar7[4]);
        fn_004057b0((int)(puVar7));
        puVar7 = (undefined4*)(puVar2);
      }
      *(undefined4 *)(param_1 + 0x122c) = 0;
      *(undefined4 *)(param_1 + 0x1228) = *(undefined4 *)(param_1 + 0x122c);
      fn_0044d730((int)(*(undefined4 *)(param_1 + 0x220)));
      *(undefined4 *)(param_1 + 0x220) = 0;
      return 0;
    }
  }
  puVar7 = (undefined4*)(*(undefined4 **)(param_1 + 0x1228));
  while (puVar7 != (undefined4 *)0x0) {
    fn_0044ced0((int)(*puVar7));
    *puVar7 = (undefined4)(0);
    puVar2 = (undefined4*)((undefined4 *)puVar7[4]);
    fn_004057b0((int)(puVar7));
    puVar7 = (undefined4*)(puVar2);
  }
  *(undefined4 *)(param_1 + 0x122c) = 0;
  *(undefined4 *)(param_1 + 0x1228) = *(undefined4 *)(param_1 + 0x122c);
  return 0;
joined_r0x004ec101:
  while (puVar7 != (undefined4 *)0x0) {
    fn_0044ced0((int)(*puVar7));
    *puVar7 = (undefined4)(0);
    puVar2 = (undefined4*)((undefined4 *)puVar7[4]);
    fn_004057b0((int)(puVar7));
    puVar7 = (undefined4*)(puVar2);
  }
  puVar7 = (undefined4*)((undefined4 *)0x0);
  goto LAB_004ec00a;
}

int fn_004ec320(int param_1)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;

  if (param_1 == 0) {
    return param_1;
  }
  if (*(int *)(param_1 + 0x220) != 0) {
    return param_1;
  }
  if (*(char *)(param_1 + 0x219) != '\0') {
    return 0;
  }
  uVar4 = (undefined4)(fn_0044d9f0((int)(param_1 + 0x108), (int)(param_1 + 4)));
  *(undefined4 *)(param_1 + 0x214) = uVar4;
  if (*(int *)(param_1 + 0x214) == 0) {
    uVar4 = (undefined4)(fn_0044d7f0((int)(param_1 + 0x108), (int)(param_1 + 0x220), (int)(*(undefined4 *)(param_1 + 0x20c)), (int)(*(undefined4 *)(param_1 + 0x210))));
    *(undefined4 *)(param_1 + 0x214) = uVar4;
    if (*(int *)(param_1 + 0x214) == 0) {
      iVar1 = (int)(*(int *)(param_1 + 0x1228));
      if (iVar1 != 0) {
        for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x10)) {
          if (*(int *)(iVar1 + 0xc) != 0) {
            uVar4 = (undefined4)(fn_0044d850((int)(*(undefined4 *)(param_1 + 0x220)), (int)(*(undefined4 *)(iVar1 + 4)), (int)(*(int *)(iVar1 + 0xc))));
            *(undefined4 *)(param_1 + 0x214) = uVar4;
            if (*(int *)(param_1 + 0x214) != 0) {
              fn_0044d730((int)(*(undefined4 *)(param_1 + 0x220)));
              fn_0044d8e0((int)(param_1 + 0x108));
              *(undefined4 *)(param_1 + 0x220) = 0;
              return 0;
            }
          }
        }
        puVar3 = (undefined4*)(*(undefined4 **)(param_1 + 0x1228));
        while (puVar3 != (undefined4 *)0x0) {
          fn_0044ced0((int)(*puVar3));
          *puVar3 = (undefined4)(0);
          puVar2 = (undefined4*)((undefined4 *)puVar3[4]);
          fn_004057b0((int)(puVar3));
          puVar3 = (undefined4*)(puVar2);
        }
        *(undefined4 *)(param_1 + 0x122c) = 0;
        *(undefined4 *)(param_1 + 0x1228) = *(undefined4 *)(param_1 + 0x122c);
      }
      if ((param_1 != 0) && (*(int *)(param_1 + 0x220) != 0 || (*(int *)(param_1 + 0x1228) != 0))) {
        *(undefined1 *)(param_1 + 0x21a) = *(undefined1 *)(param_1 + 0x21a);
        *(undefined4 *)(param_1 + 0x1224) = 0;
      }
      return param_1;
    }
  }
  return 0;
}

int Dump_Open(int param_1, int param_2)
{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_10c [260];

  if (param_1 == 0) {
    return 0;
  }
  *(undefined4 *)(param_1 + 0x20c) = 0x43574945;
  *(undefined4 *)(param_1 + 0x210) = 0x54455854;
  if (param_2 == 0) {
    iVar1 = (int)(fn_0044e080((int)(&dump_env_primary)));
    if (iVar1 == 0) {
      iVar1 = (int)(fn_0044e080((int)(&dump_env_secondary)));
    }
    if (iVar1 == 0) {
      fn_0040f1f0((int)(param_1 + 4));
      uVar2 = (undefined4)(fn_0044d9f0((int)(param_1 + 0x108), (int)(param_1 + 4)));
      *(undefined4 *)(param_1 + 0x214) = uVar2;
      if (*(int *)(param_1 + 0x214) != 0) {
        return 0;
      }
      fn_0044dea0((int)(param_1 + 4), (int)(param_1 + 0x108), (int)(0));
    }
    else {
      fn_0040f1f0((int)(param_1 + 4));
      uVar2 = (undefined4)(fn_0044d9f0((int)(local_10c), (int)(iVar1)));
      *(undefined4 *)(param_1 + 0x214) = uVar2;
      if (*(int *)(param_1 + 0x214) != 0) {
        return 0;
      }
      uVar2 = (undefined4)(fn_0044d3f0((int)(param_1 + 0x108), (int)(local_10c), (int)(param_1 + 4)));
      *(undefined4 *)(param_1 + 0x214) = uVar2;
      if (*(int *)(param_1 + 0x214) != 0) {
        return 0;
      }
      fn_0044dea0((int)(param_1 + 4), (int)(param_1 + 0x108), (int)(0));
    }
    *(undefined1 *)(param_1 + 0x218) = 1;
  }
  else {
    fn_00404070((int)(param_1 + 4), (int)(param_2), (int)(0x103));
    *(undefined1 *)(param_1 + 0x107) = 0;
  }
  fn_0044d8e0((int)(param_1 + 0x108));
  *(undefined1 *)(param_1 + 0x21a) = 1;
  *(undefined4 *)(param_1 + 0x21c) = 0;
  *(undefined4 *)(param_1 + 0x1230) = 0x4000000;
  if ((param_1 != 0) &&
     ((*(int *)(param_1 + 0x220) != 0 || (*(int *)(param_1 + 0x1228) != 0)) &&
     (*(int *)(param_1 + 0x1230) != 0)) && (*(int *)(param_1 + 0x1230) <= *(int *)(param_1 + 0x21c))
     ) {
    fn_004ec320((int)(param_1));
  }
  iVar1 = (int)(fn_004ebfc0((int)(param_1)));
  if (iVar1 == 0) {
    iVar1 = (int)(fn_004ec320((int)(param_1)));
    return iVar1;
  }
  return param_1;
}

void Dump_FreeHandle(int *dump)
{
    if (dump && *dump) {
        __builtin_memset(dump, 0, 0x1234);
        /* Native passes the cleared context word; preserve that behavior. */
        fn_00420540(*dump, (int)&dump, 0);
    }
}

undefined4 *Dump_NewHandle(undefined4 context)
{
    undefined4 *dump;
    if (fn_004204e0(context, 0x1234, 0, (int)&dump))
        return 0;
    __builtin_memset(dump, 0, 0x1234);
    *dump = context;
    return dump;
}

int fn_004ec700(int param_1)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 *puVar8;
  bool bVar9;
  int local_14;

  do {
    while( true ) {
      iVar4 = (int)(*(int *)(param_1 + 0x1228));
      if ((iVar4 == 0) || (*(int *)(iVar4 + 0x10) == 0)) {
        bVar9 = (bool)(false);
        if (iVar4 != 0) {
          bVar9 = (bool)(*(int *)(iVar4 + 0x10) == 0);
        }
        return bVar9;
      }
      iVar5 = (int)(0);
      for (; iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x10)) {
        iVar5 = (int)(iVar5 + 1);
      }
      if (iVar5 > 1) break;
LAB_004ec7eb:
      if (iVar5 < 2) {
        *(undefined4 *)(param_1 + 0x122c) = 0;
        return false;
      }
    }
LAB_004ec745:
    iVar7 = (int)(0);
    iVar4 = (int)(0);
    puVar1 = (undefined4*)(*(undefined4 **)(param_1 + 0x1228));
    for (puVar8 = (undefined4*)(puVar1); iVar4 < iVar5 && (puVar8 != (undefined4 *)0x0);
        puVar8 = (undefined4 *)puVar8[4]) {
      iVar7 = (int)(iVar7 + puVar8[3]);
      iVar4 = (int)(iVar4 + 1);
    }
    fn_0044d0a0((int)(*puVar1));
    cVar3 = (char)(fn_0044cf40((int)(*puVar1), (int)(iVar7)));
    if (cVar3 == '\0') {
LAB_004ec7d0:
      fn_0044cfe0((int)(*puVar1));
      iVar5 = (int)(iVar5 - 1);
      puVar1[1] = (undefined4)(*(undefined4 *)*puVar1);
      if (iVar5 < 2) goto LAB_004ec7eb;
      goto LAB_004ec745;
    }
    fn_0044cfe0((int)(*puVar1));
    puVar1[1] = (undefined4)(*(undefined4 *)*puVar1);
    if (puVar1[1] == 0) goto LAB_004ec7d0;
    puVar1[2] = (undefined4)(iVar7);
    local_14 = (int)(puVar1[3]);
    for (puVar6 = (undefined4*)((undefined4 *)puVar1[4]); local_14 < iVar7 && (puVar6 != puVar8);
        puVar6 = (undefined4 *)puVar6[4]) {
      fn_00404850((int)(puVar1[1] + local_14), (int)(puVar6[1]), (int)(puVar6[3]));
      local_14 = (int)(local_14 + puVar6[3]);
    }
    puVar1[3] = (undefined4)(local_14);
    puVar6 = (undefined4*)((undefined4 *)puVar1[4]);
    while (puVar6 != (undefined4 *)0x0) {
      fn_0044ced0((int)(*puVar6));
      *puVar6 = (undefined4)(0);
      puVar2 = (undefined4*)((undefined4 *)puVar6[4]);
      fn_004057b0((int)(puVar6));
      puVar6 = (undefined4*)(puVar2);
    }
    puVar1[4] = (undefined4)(puVar8);
  } while( true );
}

NativeDumpNode *fn_004ec860(int capacity)
{
    NativeDumpNode *node = (NativeDumpNode *)fn_00405820(20, 1);
    if (!node)
        return 0;
    while (capacity > 0) {
        node->handle = (uint *)fn_0044cec0(capacity);
        if (!node->handle)
            node->handle = (uint *)fn_0044ceb0(capacity);
        if (node->handle) {
            fn_0044cfe0((int)node->handle);
            if (*node->handle)
                break;
            fn_0044ced0((int)node->handle);
        }
        capacity >>= 1;
    }
    if (!capacity) {
        fn_004057b0((int)node);
        node = 0;
    } else {
        node->buffer = (char *)*node->handle;
        node->capacity = capacity;
    }
    return node;
}
