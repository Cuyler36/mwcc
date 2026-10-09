/* CleanUpIR.c: native member, ABI, layout and data review is recorded in the TU ledger. */
#include <string.h>
typedef unsigned char byte;
typedef byte undefined1;
typedef unsigned short undefined2;
typedef unsigned int uint;
typedef uint undefined4;
typedef struct {uint high,low;} NativeInt64;
#define native_int64(high,low) ((NativeInt64){high,low})
typedef byte bool;
typedef uint code();
#define true 1
#define false 0
extern uint DAT_00699b76,DAT_00699b7a,DAT_00704908,DAT_0070490c;
extern byte DAT_0070f260,DAT_0070f261;
extern code *DAT_0071016c,*DAT_007101c8,*DAT_00710854;
extern uint *DAT_00716cc8;
extern code *PTR_CompilerTools_AllocatePoolMemory_006b4ba0,*PTR_FUN_006b4ba4;
extern uint *newlabel(void);
extern void *CompilerTools_AllocatePool(uint);
extern void CError_Internal(const char *,int);
extern uint create_temp_object(uint);
extern uint FUN_00521c20(uint,byte);
extern void FUN_005e9f60(void *,uint);
extern uint FUN_005e9fd0(uint);
extern byte FUN_005e9fe0(uint,uint),FUN_0049cd70(uint,byte);
static char s_CleanUpIR_c_006b4bbc[]="CleanUpIR.c";
byte DAT_006eac68;
uint *DAT_006eac6a,*DAT_006eac6e,*DAT_006eac76;
uint DAT_006eac72;

uint *fn_005ea410(void);
void fn_005ea430(int param_1, int param_2);
uint *fn_005ea470(byte kind,uint value);
uint *fn_005ea4a0(byte kind);
uint *fn_005ea4d0(NativeInt64 value,uint type);
byte fn_005ea520(int statement);
byte fn_005ea570(int param_1);
undefined4 * fn_005ea640(undefined4 *param_1);
void fn_005ea7f0(char *param_1, undefined4 param_2, undefined1 param_3, char param_4);
void fn_005eb890(undefined4 *param_1, undefined4 param_2);
void fn_005eba10(undefined1 *param_1, undefined4 *param_2, undefined4 *param_3);
void fn_005ebbe0(undefined1 *param_1, undefined4 *param_2, undefined4 *param_3);
void fn_005ebdb0(int param_1, undefined4 *param_2);
void fn_005ebf00(int param_1, int *param_2);
void fn_005ec010(int param_1, int *param_2);
void fn_005ec120(int param_1, int *param_2);
void fn_005ec220(int param_1, undefined4 *param_2);
void fn_005ec3f0(undefined1 *param_1);
void fn_005ec530(undefined1 *param_1, char param_2);

/* Native 0x5ea410, 19 bytes. */
uint *fn_005ea410(void)
{
 uint *label=newlabel();
 *label=(uint)DAT_00716cc8;DAT_00716cc8=label;return label;
}

/* Native 0x5ea430, 52 bytes. */
void fn_005ea430(int param_1, int param_2)
{
  *(undefined4 *)(param_1 + 0x12) = *(undefined4 *)(param_2 + 0x12);
  *(undefined4 *)(param_1 + 0x16) = *(undefined4 *)(param_2 + 0x16);
  *(undefined4 *)(param_1 + 0x1a) = *(undefined4 *)(param_2 + 0x1a);
  *(undefined4 *)(param_1 + 0x1e) = *(undefined4 *)(param_2 + 0x1e);
  *(undefined2 *)(param_1 + 8) = *(undefined2 *)(param_2 + 8);
  *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_2 + 6);
  return;
}

/* Native 0x5ea470, 45 bytes. */
uint *fn_005ea470(byte kind,uint value)
{
 uint *statement=CompilerTools_AllocatePool(34);
 memset(statement,0,34);
 *((byte*)statement+4)=kind;*(uint*)((byte*)statement+10)=value;
 return statement;
}

/* Native 0x5ea4a0, 37 bytes. */
uint *fn_005ea4a0(byte kind)
{
 uint *node=CompilerTools_AllocatePool(46);
 memset(node,0,46);*(byte*)node=kind;return node;
}

/* Native 0x5ea4d0, 69 bytes. */
uint *fn_005ea4d0(NativeInt64 value,uint type)
{
 uint *node;
 FUN_005e9f60(&value,type);
 node=CompilerTools_AllocatePool(46);memset(node,0,46);
 *(byte*)node=0x34;*(NativeInt64 *)(node+4)=value;node[1]=type;
 return node;
}

/* Native 0x5ea520, 67 bytes. */
byte fn_005ea520(int statement)
{
 byte *node;
 if(*(byte*)(statement+4)==4 && (node=*(byte**)(statement+10))!=0 &&
   (*node==0x39 || *node==0x3a ||
    (*node==0x1e && (node=*(byte**)(node+20))!=0 && (byte)(*node-0x39)<2)))
  return fn_005ea570((int)(statement));
 return 0;
}

/* Native 0x5ea570, 190 bytes. */
byte fn_005ea570(int param_1)
{
 byte snapshot[306];byte *node,*callee;uint object=0;byte policy;
 if(*(byte *)(param_1+4)!=4)goto other;
 node=*(byte **)(param_1+10);
 if(!node)goto other;
 if(*node!=57 && *node!=58) {
  if(*node!=30)goto other;
  node=*(byte **)(node+20);
  if(!node || (byte)(*node-57)>1)goto other;
 }
 callee=*(byte **)(node+16);
 if(callee && *callee==59)object=*(uint *)(callee+16);
 if(object) {
  policy=*(byte *)(object+2)==4;
  if(policy)policy=(*(byte *)(param_1+6)&8)==0;
  if(!FUN_0049cd70(object,policy))return 0;
 }
 return 1;
other:
 if(*(byte *)(param_1+4)==16 && DAT_00710854) {
  DAT_00710854(param_1,snapshot);
  if(snapshot[4])return 1;
 }
 return 0;
}

/* Native 0x5ea640, 425 bytes. */
undefined4 * fn_005ea640(undefined4 *param_1)
{
  int iVar1;
  int iVar2;
  DAT_006eac6a = (undefined4 *)0x0;
  DAT_006eac6e = (undefined4 *)0x0;
  DAT_006eac72 = 0;
  do {
    if (param_1 == (undefined4 *)0x0) {
      return DAT_006eac6a;
    }
    DAT_006eac76 = 0;
    DAT_006eac68 = '\0';
    DAT_006eac72 = (uint)param_1;
    switch(*(undefined1 *)(param_1 + 1)) {
    case 1:
    case 2:
    case 3:
    case 10:
    case 0xb:
    case 0x10:
      break;
    case 5:
      fn_005ea7f0((char *)(*(undefined4 *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      break;
    case 6:
      fn_005ea7f0((char *)(*(undefined4 *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      break;
    case 7:
      fn_005ea7f0((char *)(*(undefined4 *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      break;
    case 8:
      if (*(int *)((int)param_1 + 10) != 0) {
        fn_005ea7f0((char *)(*(int *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      }
      break;
    case 9:
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x702);
    case 4:
      fn_005ea7f0((char *)(*(undefined4 *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      break;
    case 0xc:
      fn_005ea7f0((char *)(*(undefined4 *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      break;
    case 0xd:
      fn_005ea7f0((char *)(*(undefined4 *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      break;
    case 0xe:
      fn_005ea7f0((char *)(*(undefined4 *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      break;
    case 0xf:
      fn_005ea7f0((char *)(*(undefined4 *)((int)param_1 + 10)), (undefined4)(0), (undefined1)(0), (char)(0));
      break;
    default:
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x733);
    }
    iVar2 = (int)DAT_006eac76;
    while (iVar2 != 0) {
      iVar1 = *(int *)(iVar2 + 8);
      (*(code *)PTR_FUN_006b4ba4)(iVar2);
      iVar2 = iVar1;
    }
    DAT_006eac76 = 0;
    if (DAT_006eac68 == '\0') {
      DAT_006eac6e = param_1;
      if (DAT_006eac6a == (undefined4 *)0x0) {
        DAT_006eac6a = param_1;
      }
    }
    else if (DAT_006eac6e != (undefined4 *)0x0) {
      *DAT_006eac6e = *param_1;
    }
    param_1 = (undefined4 *)*param_1;
  } while( true );
}

/* Native 0x5ea7f0, 4255 bytes. */
void fn_005ea7f0(char *param_1, undefined4 param_2, undefined1 param_3, char param_4)
{
  undefined4 *puVar1;
  char *pcVar2;
  short sVar3;
  short sVar4;
  char cVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  bool bVar14;
  int iStack_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int iStack_14;
  cVar5 = *param_1;
  bVar14 = false;
  switch(cVar5) {
  case '\0':
  case '\x01':
  case '\x02':
  case '\x03':
  case '\x04':
  case '\x05':
  case '\x06':
  case '\a':
  case '\b':
  case '2':
  case '3':
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    if (*param_1 == '\b') {
      fn_005ebf00((int)(param_1), (int *)(&local_30));
      *param_1 = '\x04';
      uVar7 = FUN_00521c20(local_30, 1);
      *(undefined4 *)(param_1 + 0x10) = uVar7;
      if (**(char **)(param_1 + 4) == '\0') {
        CError_Internal(s_CleanUpIR_c_006b4bbc, 0x4ce);
      }
    }
    break;
  case '\x1c':
  case '\x1d':
    if (cVar5 == '\x1c') {
      uVar7 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
      local_18 = create_temp_object(uVar7);
      iVar8 = (uint)fn_005ea4a0((byte)(4));
      uVar7 = FUN_00521c20(local_18, 1);
      *(undefined4 *)(iVar8 + 0x10) = uVar7;
      if (**(char **)(param_1 + 4) == '\0') {
        CError_Internal(s_CleanUpIR_c_006b4bbc, 0x2b7);
      }
      else {
        *(undefined4 *)(iVar8 + 4) = *(undefined4 *)(local_18 + 0x10);
      }
      uVar7 = (uint)fn_005ea4d0(native_int64((uint)(DAT_00704908), (uint)(DAT_0070490c)), (uint)(*(undefined4 *)(local_18 + 0x10)));
      uVar6 = (uint)fn_005ea4a0((byte)(0x1e));
      puVar9 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar6));
      *(int *)(*(int *)((int)puVar9 + 10) + 0x10) = iVar8;
      *(undefined4 *)(*(int *)((int)puVar9 + 10) + 0x14) = uVar7;
      uVar7 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
      *(undefined4 *)(*(int *)((int)puVar9 + 10) + 4) = uVar7;
      fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
      if (DAT_006eac6e == (undefined4 *)0x0) {
        *puVar9 = 0;
        DAT_006eac6a = puVar9;
      }
      else {
        *puVar9 = *DAT_006eac6e;
        *DAT_006eac6e = (uint)puVar9;
      }
      DAT_006eac6e = puVar9;
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      local_2c = (uint)fn_005ea410();
      puVar9 = (undefined4 *)fn_005ea470((byte)(7), (uint)(*(undefined4 *)(param_1 + 0x10)));
      *(undefined4 *)((int)puVar9 + 0xe) = local_2c;
      fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
      if (DAT_006eac6e == (undefined4 *)0x0) {
        *puVar9 = 0;
        DAT_006eac6a = puVar9;
      }
      else {
        *puVar9 = *DAT_006eac6e;
        *DAT_006eac6e = (uint)puVar9;
      }
      DAT_006eac6e = puVar9;
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      fn_005ebbe0((undefined1 *)(param_1), (undefined4 *)(&local_18), (undefined4 *)(&local_2c));
    }
    else if (cVar5 == '\x1d') {
      uVar7 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
      local_1c = create_temp_object(uVar7);
      iVar8 = (uint)fn_005ea4a0((byte)(4));
      uVar7 = FUN_00521c20(local_1c, 1);
      *(undefined4 *)(iVar8 + 0x10) = uVar7;
      if (**(char **)(param_1 + 4) == '\0') {
        CError_Internal(s_CleanUpIR_c_006b4bbc, 0x2d2);
      }
      else {
        *(undefined4 *)(iVar8 + 4) = *(undefined4 *)(local_1c + 0x10);
      }
      uVar7 = (uint)fn_005ea4d0(native_int64((uint)(DAT_00699b76), (uint)(DAT_00699b7a)), (uint)(*(undefined4 *)(param_1 + 4)));
      uVar6 = (uint)fn_005ea4a0((byte)(0x1e));
      puVar9 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar6));
      *(int *)(*(int *)((int)puVar9 + 10) + 0x10) = iVar8;
      *(undefined4 *)(*(int *)((int)puVar9 + 10) + 0x14) = uVar7;
      *(undefined4 *)(*(int *)((int)puVar9 + 10) + 4) = *(undefined4 *)(local_1c + 0x10);
      fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
      if (DAT_006eac6e == (undefined4 *)0x0) {
        *puVar9 = 0;
        DAT_006eac6a = puVar9;
      }
      else {
        *puVar9 = *DAT_006eac6e;
        *DAT_006eac6e = (uint)puVar9;
      }
      DAT_006eac6e = puVar9;
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      local_28 = (uint)fn_005ea410();
      puVar9 = (undefined4 *)fn_005ea470((byte)(6), (uint)(*(undefined4 *)(param_1 + 0x10)));
      *(undefined4 *)((int)puVar9 + 0xe) = local_28;
      fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
      if (DAT_006eac6e == (undefined4 *)0x0) {
        *puVar9 = 0;
        DAT_006eac6a = puVar9;
      }
      else {
        *puVar9 = *DAT_006eac6e;
        *DAT_006eac6e = (uint)puVar9;
      }
      DAT_006eac6e = puVar9;
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      fn_005eba10((undefined1 *)(param_1), (undefined4 *)(&local_1c), (undefined4 *)(&local_28));
    }
    break;
  case '\x1e':
  case '\x1f':
  case ' ':
  case '!':
  case '\"':
  case '#':
  case '$':
  case '%':
  case '&':
  case '\'':
  case '(':
  case '/':
  case '1':
    bVar14 = true;
  case '\t':
  case '\n':
  case '\v':
  case '\f':
  case '\r':
  case '\x0e':
  case '\x0f':
  case '\x10':
  case '\x11':
  case '\x12':
  case '\x13':
  case '\x14':
  case '\x15':
  case '\x16':
  case '\x17':
  case '\x18':
  case '\x19':
  case '\x1a':
  case '\x1b':
  case ')':
  case '*':
  case '+':
  case ',':
  case '-':
  case '.':
  case '0':
  case 'M':
  case 'N':
    if (cVar5 == ')') {
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(1), (char)(0));
      puVar9 = (undefined4 *)fn_005ea470((byte)(4), (uint)(*(undefined4 *)(param_1 + 0x10)));
      fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
      if (DAT_006eac6e == (undefined4 *)0x0) {
        *puVar9 = 0;
        DAT_006eac6a = puVar9;
      }
      else {
        *puVar9 = *DAT_006eac6e;
        *DAT_006eac6e = (uint)puVar9;
      }
      DAT_006eac6e = puVar9;
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      fn_005ec530((undefined1 *)(param_1), (char)(param_3));
    }
    else if ((*(byte *)(*(int *)(param_1 + 0x10) + 1) <= *(byte *)(*(int *)(param_1 + 0x14) + 1)) ||
            (bVar14 && (DAT_0070f261 == '\0'))) {
      fn_005ea7f0((char *)(*(int *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      if ((DAT_0070f260 != '\0') && (DAT_007101c8 != (code *)0x0)) {
        *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x40;
      }
    }
    else {
      fn_005ea7f0((char *)(*(int *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    }
    break;
  case '4':
  case '5':
  case '6':
  case '7':
  case ';':
  case '>':
  case 'D':
  case 'G':
  case 'Q':
  case 'R':
  case 'S':
  case 'W':
    break;
  case '8':
    local_20 = 0;
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    uVar7 = (uint)fn_005ea410();
    puVar9 = (undefined4 *)fn_005ea470((byte)(7), (uint)(*(undefined4 *)(param_1 + 0x10)));
    *(undefined4 *)((int)puVar9 + 0xe) = uVar7;
    fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
    if (DAT_006eac6e == (undefined4 *)0x0) {
      *puVar9 = 0;
      DAT_006eac6a = puVar9;
    }
    else {
      *puVar9 = *DAT_006eac6e;
      *DAT_006eac6e = (uint)puVar9;
    }
    DAT_006eac6e = puVar9;
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ec120((int)(param_1), (int *)(&local_20));
    uVar6 = (uint)fn_005ea410();
    puVar9 = (undefined4 *)fn_005ea470((byte)(3), (uint)(0));
    *(undefined4 *)((int)puVar9 + 0xe) = uVar6;
    fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
    if (DAT_006eac6e == (undefined4 *)0x0) {
      *puVar9 = 0;
      DAT_006eac6a = puVar9;
    }
    else {
      *puVar9 = *DAT_006eac6e;
      *DAT_006eac6e = (uint)puVar9;
    }
    DAT_006eac6e = puVar9;
    puVar9 = (undefined4 *)fn_005ea470((byte)(2), (uint)(0));
    *(undefined4 *)((int)puVar9 + 0xe) = uVar7;
    *(undefined4 **)(*(int *)((int)puVar9 + 0xe) + 4) = puVar9;
    fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
    if (DAT_006eac6e == (undefined4 *)0x0) {
      *puVar9 = 0;
      DAT_006eac6a = puVar9;
    }
    else {
      *puVar9 = *DAT_006eac6e;
      *DAT_006eac6e = (uint)puVar9;
    }
    DAT_006eac6e = puVar9;
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x18)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ec010((int)(param_1), (int *)(&local_20));
    puVar9 = (undefined4 *)fn_005ea470((byte)(2), (uint)(0));
    *(undefined4 *)((int)puVar9 + 0xe) = uVar6;
    *(undefined4 **)(*(int *)((int)puVar9 + 0xe) + 4) = puVar9;
    fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
    if (DAT_006eac6e == (undefined4 *)0x0) {
      *puVar9 = 0;
      DAT_006eac6a = puVar9;
    }
    else {
      *puVar9 = *DAT_006eac6e;
      *DAT_006eac6e = (uint)puVar9;
    }
    DAT_006eac6e = puVar9;
    if (**(char **)(param_1 + 4) == '\0') {
      *param_1 = '4';
      uVar7 = DAT_0070490c;
      *(undefined4 *)(param_1 + 0x10) = DAT_00704908;
      *(undefined4 *)(param_1 + 0x14) = uVar7;
    }
    else {
      *param_1 = '\x04';
      uVar7 = FUN_00521c20(local_20, 1);
      *(undefined4 *)(param_1 + 0x10) = uVar7;
      if (**(char **)(param_1 + 4) == '\0') {
        CError_Internal(s_CleanUpIR_c_006b4bbc, 0x562);
      }
    }
    break;
  case '9':
  case ':':
    iVar8 = 0;
    for (puVar9 = *(undefined4 **)(param_1 + 0x14); puVar9 != (undefined4 *)0x0;
        puVar9 = (undefined4 *)*puVar9) {
      iVar8 = iVar8 + 1;
    }
    if (iVar8 != 0) {
      iStack_14 = (*(code *)PTR_CompilerTools_AllocatePoolMemory_006b4ba0)(iVar8 * 4);
      iVar8 = 0;
      for (puVar9 = *(undefined4 **)(param_1 + 0x14); puVar9 != (undefined4 *)0x0;
          puVar9 = (undefined4 *)*puVar9) {
        *(undefined4 *)(iStack_14 + iVar8 * 4) = puVar9[1];
        iVar8 = iVar8 + 1;
      }
      iVar10 = (*(code *)PTR_CompilerTools_AllocatePoolMemory_006b4ba0)(iVar8 * 2);
      if ((DAT_0070f260 == '\0') || (DAT_007101c8 == (code *)0x0)) {
        iVar12 = 0;
        if (iVar8 > 0) {
          sVar4 = (short)iVar8;
          if (iVar8 > 8) {
            bVar14 = false;
            if ((iVar8 > -1) && (iVar8 != 0x7fffffff)) {
              bVar14 = true;
            }
            iVar11 = iVar12;
            if (bVar14) {
              do {
                sVar3 = (short)iVar11;
                *(short *)(iVar10 + iVar11 * 2) = (sVar4 - sVar3) - 1;
                *(short *)(iVar10 + 2 + iVar11 * 2) = (-sVar3 - 2U) + sVar4;
                *(short *)(iVar10 + 4 + iVar11 * 2) = (sVar4 - (sVar3 + 2)) - 1;
                *(short *)(iVar10 + 6 + iVar11 * 2) = (sVar4 - (sVar3 + 3)) - 1;
                *(short *)(iVar10 + 8 + iVar11 * 2) = (sVar4 - (sVar3 + 4)) - 1;
                *(short *)(iVar10 + 10 + iVar11 * 2) = (sVar4 - (sVar3 + 5)) - 1;
                *(short *)(iVar10 + 0xc + iVar11 * 2) = (sVar4 - (sVar3 + 6)) - 1;
                iVar12 = iVar11 + 8;
                *(short *)(iVar10 + 0xe + iVar11 * 2) = (sVar4 - (sVar3 + 7)) - 1;
                iVar11 = iVar12;
              } while (iVar12 < iVar8 - 8U);
            }
          }
          for (; iVar12 < iVar8; iVar12 = iVar12 + 1) {
            *(short *)(iVar10 + iVar12 * 2) = (sVar4 - (short)iVar12) - 1;
          }
        }
      }
      else {
        (*DAT_007101c8)(param_1, iVar10);
      }
      if (DAT_0071016c != (code *)0x0) {
        iStack_34 = 0;
        if (iVar8 > 0) {
          do {
            cVar5 = (*DAT_0071016c)(*(undefined4 *)
                                     (iStack_14 + *(short *)(iVar10 + iStack_34 * 2) * 4), param_1);
            if (cVar5 != '\0') {
              fn_005ea7f0((char *)(*(undefined4 *)(iStack_14 + *(short *)(iVar10 + iStack_34 * 2) * 4)), (undefined4)(param_1), (undefined1)(0), (char)(1));
            }
            iStack_34 = iStack_34 + 1;
          } while (iStack_34 < iVar8);
        }
        if ((DAT_0070f260 != '\0') && (DAT_007101c8 != (code *)0x0)) {
          (*DAT_007101c8)(param_1, iVar10);
        }
      }
      iVar12 = 0;
      if (iVar8 > 0) {
        do {
          fn_005ea7f0((char *)(*(undefined4 *)(iStack_14 + *(short *)(iVar10 + iVar12 * 2) * 4)), (undefined4)(param_1), (undefined1)(0), (char)(0));
          iVar12 = iVar12 + 1;
        } while (iVar12 < iVar8);
      }
      if ((DAT_0070f260 == '\0') || (DAT_007101c8 == (code *)0x0)) {
        (*(code *)PTR_FUN_006b4ba4)(iVar10);
      }
      (*(code *)PTR_FUN_006b4ba4)(iStack_14);
    }
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    if (**(char **)(param_1 + 4) != '\0') {
      pcVar2 = *(char **)(param_1 + 0x10);
      iVar8 = 0;
      if ((pcVar2 != (char *)0x0) && (*pcVar2 == ';')) {
        iVar8 = *(int *)(pcVar2 + 0x10);
      }
      if (iVar8 != 0) {
        bVar14 = false;
        if (*(char *)(iVar8 + 2) == '\x04') {
          bVar14 = (*(byte *)(DAT_006eac72 + 6) & 8) == 0;
        }
        cVar5 = FUN_0049cd70(iVar8, bVar14);
        if (cVar5 == '\0') break;
      }
      uVar7 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
      iVar8 = create_temp_object(uVar7);
      iVar10 = (uint)fn_005ea4a0((byte)(4));
      uVar7 = FUN_00521c20(iVar8, 1);
      *(undefined4 *)(iVar10 + 0x10) = uVar7;
      *(undefined4 *)(iVar10 + 4) = *(undefined4 *)(iVar8 + 0x10);
      iVar12 = (uint)fn_005ea4a0((byte)(*param_1));
      memcpy((void *)iVar12, param_1, 46);
      uVar7 = (uint)fn_005ea4a0((byte)(0x1e));
      puVar9 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar7));
      *(int *)(*(int *)((int)puVar9 + 10) + 0x10) = iVar10;
      *(int *)(*(int *)((int)puVar9 + 10) + 0x14) = iVar12;
      uVar7 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
      *(undefined4 *)(*(int *)((int)puVar9 + 10) + 4) = uVar7;
      fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
      if (DAT_006eac6e == (undefined4 *)0x0) {
        *puVar9 = 0;
        DAT_006eac6a = puVar9;
      }
      else {
        *puVar9 = *DAT_006eac6e;
        *DAT_006eac6e = (uint)puVar9;
      }
      DAT_006eac6e = puVar9;
      *param_1 = '\x04';
      uVar7 = FUN_00521c20(iVar8, 1);
      *(undefined4 *)(param_1 + 0x10) = uVar7;
    }
    break;
  case '<':
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ec220((int)(param_1), (undefined4 *)(&local_24));
    iVar8 = (uint)fn_005ea4a0((byte)(4));
    uVar7 = FUN_00521c20(local_24, 1);
    *(undefined4 *)(iVar8 + 0x10) = uVar7;
    if (**(char **)(param_1 + 4) == '\0') {
      uVar7 = FUN_005e9fd0((uint)(*(undefined4 *)(*(int *)(param_1 + 0x10) + 4)));
      *(undefined4 *)(iVar8 + 4) = uVar7;
    }
    else {
      uVar7 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
      *(undefined4 *)(iVar8 + 4) = uVar7;
    }
    uVar7 = (uint)fn_005ea410();
    puVar9 = (undefined4 *)fn_005ea470((byte)(7), (uint)(iVar8));
    *(undefined4 *)((int)puVar9 + 0xe) = uVar7;
    fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
    if (DAT_006eac6e == (undefined4 *)0x0) {
      *puVar9 = 0;
      DAT_006eac6a = puVar9;
    }
    else {
      *puVar9 = *DAT_006eac6e;
      *DAT_006eac6e = (uint)puVar9;
    }
    DAT_006eac6e = puVar9;
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ebdb0((int)(param_1), (undefined4 *)(&local_24));
    puVar9 = (undefined4 *)fn_005ea470((byte)(2), (uint)(0));
    *(undefined4 *)((int)puVar9 + 0xe) = uVar7;
    *(undefined4 **)(*(int *)((int)puVar9 + 0xe) + 4) = puVar9;
    fn_005ea430((int)(puVar9), (int)(DAT_006eac72));
    if (DAT_006eac6e == (undefined4 *)0x0) {
      *puVar9 = 0;
      DAT_006eac6a = puVar9;
    }
    else {
      *puVar9 = *DAT_006eac6e;
      *DAT_006eac6e = (uint)puVar9;
    }
    DAT_006eac6e = puVar9;
    if (**(char **)(param_1 + 4) == '\0') {
      *param_1 = '4';
      uVar7 = DAT_0070490c;
      *(undefined4 *)(param_1 + 0x10) = DAT_00704908;
      *(undefined4 *)(param_1 + 0x14) = uVar7;
    }
    else {
      *param_1 = '\x04';
      uVar7 = FUN_00521c20(local_24, 1);
      *(undefined4 *)(param_1 + 0x10) = uVar7;
      if (**(char **)(param_1 + 4) == '\0') {
        CError_Internal(s_CleanUpIR_c_006b4bbc, 0x58f);
      }
    }
    break;
  case '=':
    piVar13 = (int *)DAT_006eac76;
    if (DAT_006eac76 != (uint *)0x0) {
      do {
        if (*piVar13 == *(int *)(param_1 + 0x10)) break;
        piVar13 = (int *)piVar13[2];
      } while (piVar13 != (int *)0x0);
    }
    if (piVar13 == (int *)0x0) {
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x321);
    }
    iVar8 = piVar13[1];
    *param_1 = '\x04';
    uVar7 = FUN_00521c20(iVar8, 1);
    *(undefined4 *)(param_1 + 0x10) = uVar7;
    if (**(char **)(param_1 + 4) == '\0') {
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x575);
    }
    break;
  case '?':
    for (puVar9 = *(undefined4 **)(param_1 + 0x14); puVar9 != (undefined4 *)0x0;
        puVar9 = (undefined4 *)*puVar9) {
      fn_005ea7f0((char *)(puVar9[2]), (undefined4)(param_1), (undefined1)(0), (char)(0));
    }
    for (puVar9 = *(undefined4 **)(param_1 + 0x18); puVar9 != (undefined4 *)0x0;
        puVar9 = (undefined4 *)*puVar9) {
      fn_005ea7f0((char *)(puVar9[2]), (undefined4)(param_1), (undefined1)(0), (char)(0));
    }
    break;
  case '@':
  case 'A':
    DAT_006eac68 = 1;
    break;
  case 'B':
    if (*(int *)(param_1 + 0x10) != 0) {
      fn_005ea7f0((char *)(*(int *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    }
    break;
  case 'C':
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    break;
  default:
    CError_Internal(s_CleanUpIR_c_006b4bbc, 0x6c5);
    break;
  case 'H':
  case 'I':
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    break;
  case 'J':
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x18)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x1c)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    break;
  case 'K':
    if ((param_1[0x29] != '\0') && (*(int *)(param_1 + 0x24) != 0)) {
      fn_005ea7f0((char *)(*(int *)(param_1 + 0x24)), (undefined4)(param_1), (undefined1)(0), (char)(0));
    }
    break;
  case 'L':
    switch(param_1[0x2c]) {
    case '\0':
    case '\x03':
    case '\x04':
    case '\b':
    case '\x16':
    case '\x19':
    case '\x1b':
      break;
    case '\x01':
      if (param_1[0x19] != '\0') {
        fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
      break;
    case '\x02':
      for (puVar9 = *(undefined4 **)(param_1 + 0x10); puVar9 != (undefined4 *)0x0;
          puVar9 = (undefined4 *)*puVar9) {
        fn_005ea7f0((char *)(puVar9[1]), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
      break;
    case '\x05':
      if (*(int *)(param_1 + 0x24) != 0) {
        fn_005ea7f0((char *)(*(int *)(param_1 + 0x24)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
      break;
    case '\x06':
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      break;
    case '\a':
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      for (puVar9 = *(undefined4 **)(param_1 + 0x14); puVar9 != (undefined4 *)0x0;
          puVar9 = (undefined4 *)*puVar9) {
        fn_005ea7f0((char *)(puVar9[1]), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
      break;
    case '\t':
    case '\n':
    case '\v':
    case '\x15':
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      break;
    case '\f':
      if (*(int *)(param_1 + 0x18) != 0) {
        fn_005ea7f0((char *)(*(int *)(param_1 + 0x18)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
      for (puVar9 = *(undefined4 **)(param_1 + 0x1c); puVar9 != (undefined4 *)0x0;
          puVar9 = (undefined4 *)*puVar9) {
        fn_005ea7f0((char *)(puVar9[1]), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
      for (puVar9 = *(undefined4 **)(param_1 + 0x20); puVar9 != (undefined4 *)0x0;
          puVar9 = (undefined4 *)*puVar9) {
        fn_005ea7f0((char *)(puVar9[1]), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
      break;
    case '\r':
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      break;
    case '\x0e':
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x14)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      break;
    case '\x0f':
    case '\x10':
    case '\x11':
    case '\x12':
    case '\x13':
      if (*(int *)(param_1 + 0x10) != 0) {
        fn_005ea7f0((char *)(*(int *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
      break;
    case '\x14':
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      break;
    case '\x17':
    case '\x18':
      puVar9 = *(undefined4 **)(param_1 + 0x14);
      if (puVar9 != (undefined4 *)0x0) {
        switch(*(undefined1 *)(puVar9 + 1)) {
        case 0:
          fn_005ea7f0((char *)(*puVar9), (undefined4)(param_1), (undefined1)(0), (char)(0));
          break;
        case 1:
          for (puVar9 = (undefined4 *)*puVar9; puVar9 != (undefined4 *)0x0;
              puVar9 = (undefined4 *)*puVar9) {
            fn_005ea7f0((char *)(puVar9[1]), (undefined4)(param_1), (undefined1)(0), (char)(0));
          }
          break;
        case 2:
          fn_005eb890((undefined4 *)(*puVar9), (undefined4)(param_1));
          break;
        default:
          CError_Internal(s_CleanUpIR_c_006b4bbc, 0x684);
        }
      }
      break;
    case '\x1a':
      fn_005ea7f0((char *)(*(undefined4 *)(param_1 + 0x10)), (undefined4)(param_1), (undefined1)(0), (char)(0));
      break;
    default:
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x68a);
    }
    break;
  case 'O':
    for (puVar9 = *(undefined4 **)(param_1 + 0x10); puVar9 != (undefined4 *)0x0;
        puVar9 = (undefined4 *)*puVar9) {
      if (*(char *)((int)puVar9 + 0xd) == '\0') {
        for (puVar1 = (undefined4 *)puVar9[1]; puVar1 != (undefined4 *)0x0;
            puVar1 = (undefined4 *)*puVar1) {
          fn_005ea7f0((char *)(puVar1[1]), (undefined4)(param_1), (undefined1)(0), (char)(0));
        }
      }
      else if (puVar9[1] != 0) {
        fn_005ea7f0((char *)(puVar9[1]), (undefined4)(param_1), (undefined1)(0), (char)(0));
      }
    }
  }
  if ((param_4 != '\0') && (DAT_0071016c != (code *)0x0) &&
     (cVar5 = (*DAT_0071016c)(param_1, param_2), cVar5 != '\0')) {
    fn_005ec3f0((undefined1 *)(param_1));
  }
  return;
}

/* Native 0x5eb890, 374 bytes. */
void fn_005eb890(undefined4 *param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  for (; param_1 != (undefined4 *)0x0; param_1 = (undefined4 *)*param_1) {
    if (param_1[2] != 0) {
      fn_005ea7f0((char *)(param_1[2]), (undefined4)(param_2), (undefined1)(0), (char)(0));
    }
    puVar1 = (undefined4 *)param_1[1];
    if (puVar1 != (undefined4 *)0x0) {
      for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
        if (puVar1[2] != 0) {
          fn_005ea7f0((char *)(puVar1[2]), (undefined4)(param_2), (undefined1)(0), (char)(0));
        }
        puVar2 = (undefined4 *)puVar1[1];
        if (puVar2 != (undefined4 *)0x0) {
          for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
            if (puVar2[2] != 0) {
              fn_005ea7f0((char *)(puVar2[2]), (undefined4)(param_2), (undefined1)(0), (char)(0));
            }
            puVar3 = (undefined4 *)puVar2[1];
            if (puVar3 != (undefined4 *)0x0) {
              for (; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3) {
                if (puVar3[2] != 0) {
                  fn_005ea7f0((char *)(puVar3[2]), (undefined4)(param_2), (undefined1)(0), (char)(0));
                }
                puVar4 = (undefined4 *)puVar3[1];
                if (puVar4 != (undefined4 *)0x0) {
                  for (; puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
                    if (puVar4[2] != 0) {
                      fn_005ea7f0((char *)(puVar4[2]), (undefined4)(param_2), (undefined1)(0), (char)(0));
                    }
                    puVar5 = (undefined4 *)puVar4[1];
                    if (puVar5 != (undefined4 *)0x0) {
                      for (; puVar5 != (undefined4 *)0x0; puVar5 = (undefined4 *)*puVar5) {
                        if (puVar5[2] != 0) {
                          fn_005ea7f0((char *)(puVar5[2]), (undefined4)(param_2), (undefined1)(0), (char)(0));
                        }
                        if (puVar5[1] != 0) {
                          fn_005eb890((undefined4 *)(puVar5[1]), (undefined4)(param_2));
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}

/* Native 0x5eba10, 451 bytes. */
void fn_005eba10(undefined1 *param_1, undefined4 *param_2, undefined4 *param_3)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  puVar1 = (undefined4 *)fn_005ea470((byte)(6), (uint)(*(undefined4 *)(param_1 + 0x14)));
  *(undefined4 *)((int)puVar1 + 0xe) = *param_3;
  fn_005ea430((int)(puVar1), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar1 = 0;
    DAT_006eac6a = puVar1;
  }
  else {
    *puVar1 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar1;
  }
  DAT_006eac6e = puVar1;
  iVar2 = (uint)fn_005ea4a0((byte)(4));
  uVar3 = FUN_00521c20(*param_2, 1);
  *(undefined4 *)(iVar2 + 0x10) = uVar3;
  if (**(char **)(param_1 + 4) == '\0') {
    CError_Internal(s_CleanUpIR_c_006b4bbc, 0x48b);
  }
  else {
    uVar3 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
    *(undefined4 *)(iVar2 + 4) = uVar3;
  }
  iVar4 = (uint)fn_005ea4d0(native_int64((uint)(DAT_00704908), (uint)(DAT_0070490c)), (uint)(*(undefined4 *)(param_1 + 4)));
  uVar3 = (uint)fn_005ea4a0((byte)(0x1e));
  puVar1 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar3));
  *(int *)(*(int *)((int)puVar1 + 10) + 0x10) = iVar2;
  *(int *)(*(int *)((int)puVar1 + 10) + 0x14) = iVar4;
  *(undefined4 *)(*(int *)((int)puVar1 + 10) + 4) = *(undefined4 *)(iVar4 + 4);
  fn_005ea430((int)(puVar1), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar1 = 0;
    DAT_006eac6a = puVar1;
  }
  else {
    *puVar1 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar1;
  }
  DAT_006eac6e = puVar1;
  puVar1 = (undefined4 *)fn_005ea470((byte)(2), (uint)(0));
  *(undefined4 *)((int)puVar1 + 0xe) = *param_3;
  *(undefined4 **)(*(int *)((int)puVar1 + 0xe) + 4) = puVar1;
  fn_005ea430((int)(puVar1), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar1 = 0;
    DAT_006eac6a = puVar1;
  }
  else {
    *puVar1 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar1;
  }
  DAT_006eac6e = puVar1;
  *param_1 = 4;
  uVar3 = FUN_00521c20(*param_2, 1);
  *(undefined4 *)(param_1 + 0x10) = uVar3;
  if (**(char **)(param_1 + 4) == '\0') {
    CError_Internal(s_CleanUpIR_c_006b4bbc, 0x4a3);
  }
  return;
}

/* Native 0x5ebbe0, 451 bytes. */
void fn_005ebbe0(undefined1 *param_1, undefined4 *param_2, undefined4 *param_3)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  puVar1 = (undefined4 *)fn_005ea470((byte)(7), (uint)(*(undefined4 *)(param_1 + 0x14)));
  *(undefined4 *)((int)puVar1 + 0xe) = *param_3;
  fn_005ea430((int)(puVar1), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar1 = 0;
    DAT_006eac6a = puVar1;
  }
  else {
    *puVar1 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar1;
  }
  DAT_006eac6e = puVar1;
  iVar2 = (uint)fn_005ea4a0((byte)(4));
  uVar3 = FUN_00521c20(*param_2, 1);
  *(undefined4 *)(iVar2 + 0x10) = uVar3;
  if (**(char **)(param_1 + 4) == '\0') {
    CError_Internal(s_CleanUpIR_c_006b4bbc, 0x43f);
  }
  else {
    uVar3 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
    *(undefined4 *)(iVar2 + 4) = uVar3;
  }
  iVar4 = (uint)fn_005ea4d0(native_int64((uint)(DAT_00699b76), (uint)(DAT_00699b7a)), (uint)(*(undefined4 *)(param_1 + 4)));
  uVar3 = (uint)fn_005ea4a0((byte)(0x1e));
  puVar1 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar3));
  *(int *)(*(int *)((int)puVar1 + 10) + 0x10) = iVar2;
  *(int *)(*(int *)((int)puVar1 + 10) + 0x14) = iVar4;
  *(undefined4 *)(*(int *)((int)puVar1 + 10) + 4) = *(undefined4 *)(iVar4 + 4);
  fn_005ea430((int)(puVar1), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar1 = 0;
    DAT_006eac6a = puVar1;
  }
  else {
    *puVar1 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar1;
  }
  DAT_006eac6e = puVar1;
  puVar1 = (undefined4 *)fn_005ea470((byte)(2), (uint)(0));
  *(undefined4 *)((int)puVar1 + 0xe) = *param_3;
  *(undefined4 **)(*(int *)((int)puVar1 + 0xe) + 4) = puVar1;
  fn_005ea430((int)(puVar1), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar1 = 0;
    DAT_006eac6a = puVar1;
  }
  else {
    *puVar1 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar1;
  }
  DAT_006eac6e = puVar1;
  *param_1 = 4;
  uVar3 = FUN_00521c20(*param_2, 1);
  *(undefined4 *)(param_1 + 0x10) = uVar3;
  if (**(char **)(param_1 + 4) == '\0') {
    CError_Internal(s_CleanUpIR_c_006b4bbc, 0x457);
  }
  return;
}

/* Native 0x5ebdb0, 328 bytes. */
void fn_005ebdb0(int param_1, undefined4 *param_2)
{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  if (**(char **)(*(int *)(param_1 + 0x14) + 4) == '\0') {
    puVar2 = (undefined4 *)fn_005ea470((byte)(4), (uint)(*(int *)(param_1 + 0x14)));
  }
  else {
    iVar3 = (uint)fn_005ea4a0((byte)(4));
    uVar4 = FUN_00521c20(*param_2, 1);
    *(undefined4 *)(iVar3 + 0x10) = uVar4;
    if (**(char **)(param_1 + 4) == '\0') {
      uVar4 = FUN_005e9fd0((uint)(*(undefined4 *)(*(int *)(param_1 + 0x10) + 4)));
      *(undefined4 *)(iVar3 + 4) = uVar4;
    }
    else {
      uVar4 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
      *(undefined4 *)(iVar3 + 4) = uVar4;
    }
    uVar4 = (uint)fn_005ea4a0((byte)(0x1e));
    puVar2 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar4));
    *(int *)(*(int *)((int)puVar2 + 10) + 0x10) = iVar3;
    *(undefined4 *)(*(int *)((int)puVar2 + 10) + 0x14) = *(undefined4 *)(param_1 + 0x14);
    cVar1 = FUN_005e9fe0(*(undefined4 *)(*(int *)(*(int *)((int)puVar2 + 10) + 0x10) + 4),
                         *(undefined4 *)(*(int *)(*(int *)((int)puVar2 + 10) + 0x14) + 4));
    if (cVar1 == '\0') {
      iVar3 = (uint)fn_005ea4a0((byte)(0x32));
      *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(*(int *)((int)puVar2 + 10) + 0x14);
      uVar4 = FUN_005e9fd0((uint)(*(undefined4 *)(*(int *)(*(int *)((int)puVar2 + 10) + 0x10) + 4)));
      *(undefined4 *)(iVar3 + 4) = uVar4;
      *(int *)(*(int *)((int)puVar2 + 10) + 0x14) = iVar3;
    }
    if (**(char **)(param_1 + 4) == '\0') {
      uVar4 = FUN_005e9fd0((uint)(*(undefined4 *)(*(int *)(param_1 + 0x10) + 4)));
      *(undefined4 *)(*(int *)((int)puVar2 + 10) + 4) = uVar4;
    }
    else {
      uVar4 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
      *(undefined4 *)(*(int *)((int)puVar2 + 10) + 4) = uVar4;
    }
  }
  fn_005ea430((int)(puVar2), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar2 = 0;
    DAT_006eac6a = puVar2;
  }
  else {
    *puVar2 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar2;
  }
  DAT_006eac6e = puVar2;
  return;
}

/* Native 0x5ebf00, 257 bytes. */
void fn_005ebf00(int param_1, int *param_2)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int temporaryNode;
  if (**(char **)(param_1 + 4) != '\0') {
    uVar3 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
    iVar2 = create_temp_object(uVar3);
    *param_2 = iVar2;
    temporaryNode = (int)fn_005ea4a0((byte)(4));
    uVar3 = FUN_00521c20(*param_2, 1);
    *(undefined4 *)(temporaryNode + 0x10) = uVar3;
    *(undefined4 *)(temporaryNode + 4) = *(undefined4 *)(*param_2 + 0x10);
    if (**(char **)(param_1 + 4) == '\0') {
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x3ab);
    }
  }
  puVar1 = (undefined4 *)fn_005ea470((byte)(4), (uint)(0));
  if (**(char **)(param_1 + 4) == '\0') {
    *(undefined4 *)((int)puVar1 + 10) = *(undefined4 *)(param_1 + 0x10);
  }
  else {
    iVar2 = (uint)fn_005ea4a0((byte)(0x1e));
    *(int *)((int)puVar1 + 10) = iVar2;
    *(int *)(iVar2 + 0x10) = temporaryNode;
    *(undefined4 *)(*(int *)((int)puVar1 + 10) + 0x14) = *(undefined4 *)(param_1 + 0x10);
    uVar3 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
    *(undefined4 *)(*(int *)((int)puVar1 + 10) + 4) = uVar3;
  }
  fn_005ea430((int)(puVar1), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar1 = 0;
    DAT_006eac6a = puVar1;
  }
  else {
    *puVar1 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar1;
  }
  DAT_006eac6e = puVar1;
  return;
}

/* Native 0x5ec010, 270 bytes. */
void fn_005ec010(int param_1, int *param_2)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int temporaryNode;
  if ((**(char **)(param_1 + 4) != '\0') && (**(char **)(*(int *)(param_1 + 0x18) + 4) != '\0')) {
    if (*param_2 == 0) {
      uVar1 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
      iVar3 = create_temp_object(uVar1);
      *param_2 = iVar3;
    }
    temporaryNode = (int)fn_005ea4a0((byte)(4));
    uVar1 = FUN_00521c20(*param_2, 1);
    *(undefined4 *)(temporaryNode + 0x10) = uVar1;
    uVar1 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
    *(undefined4 *)(temporaryNode + 4) = uVar1;
    if (**(char **)(param_1 + 4) == '\0') {
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x385);
    }
  }
  puVar2 = (undefined4 *)fn_005ea470((byte)(4), (uint)(0));
  if ((**(char **)(param_1 + 4) == '\0') || (**(char **)(*(int *)(param_1 + 0x18) + 4) == '\0')) {
    *(undefined4 *)((int)puVar2 + 10) = *(undefined4 *)(param_1 + 0x18);
  }
  else {
    uVar1 = (uint)fn_005ea4a0((byte)(0x1e));
    *(undefined4 *)((int)puVar2 + 10) = uVar1;
    *(int *)(*(int *)((int)puVar2 + 10) + 0x10) = temporaryNode;
    *(undefined4 *)(*(int *)((int)puVar2 + 10) + 0x14) = *(undefined4 *)(param_1 + 0x18);
    uVar1 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
    *(undefined4 *)(*(int *)((int)puVar2 + 10) + 4) = uVar1;
  }
  fn_005ea430((int)(puVar2), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar2 = 0;
    DAT_006eac6a = puVar2;
  }
  else {
    *puVar2 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar2;
  }
  DAT_006eac6e = puVar2;
  return;
}

/* Native 0x5ec120, 246 bytes. */
void fn_005ec120(int param_1, int *param_2)
{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int temporaryNode;
  if ((**(char **)(param_1 + 4) != '\0') && (**(char **)(*(int *)(param_1 + 0x14) + 4) != '\0')) {
    uVar1 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
    iVar2 = create_temp_object(uVar1);
    *param_2 = iVar2;
    temporaryNode = (int)fn_005ea4a0((byte)(4));
    uVar1 = FUN_00521c20(*param_2, 1);
    *(undefined4 *)(temporaryNode + 0x10) = uVar1;
    *(undefined4 *)(temporaryNode + 4) = *(undefined4 *)(*param_2 + 0x10);
    if (**(char **)(param_1 + 4) == '\0') {
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x35e);
    }
  }
  puVar3 = (undefined4 *)fn_005ea470((byte)(4), (uint)(0));
  if ((**(char **)(param_1 + 4) == '\0') || (**(char **)(*(int *)(param_1 + 0x14) + 4) == '\0')) {
    *(undefined4 *)((int)puVar3 + 10) = *(undefined4 *)(param_1 + 0x14);
  }
  else {
    iVar2 = (uint)fn_005ea4a0((byte)(0x1e));
    *(int *)((int)puVar3 + 10) = iVar2;
    *(int *)(iVar2 + 0x10) = temporaryNode;
    *(undefined4 *)(*(int *)((int)puVar3 + 10) + 0x14) = *(undefined4 *)(param_1 + 0x14);
    uVar1 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
    *(undefined4 *)(*(int *)((int)puVar3 + 10) + 4) = uVar1;
  }
  fn_005ea430((int)(puVar3), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar3 = 0;
    DAT_006eac6a = puVar3;
  }
  else {
    *puVar3 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar3;
  }
  DAT_006eac6e = puVar3;
  return;
}

/* Native 0x5ec220, 449 bytes. */
void fn_005ec220(int param_1, undefined4 *param_2)
{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  if (**(char **)(param_1 + 4) == '\0') {
    uVar2 = FUN_005e9fd0((uint)(*(undefined4 *)(*(int *)(param_1 + 0x10) + 4)));
    uVar2 = create_temp_object(uVar2);
    *param_2 = uVar2;
  }
  else {
    uVar2 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
    uVar2 = create_temp_object(uVar2);
    *param_2 = uVar2;
  }
  uVar2 = *param_2;
  puVar3 = (undefined4 *)(*(code *)PTR_CompilerTools_AllocatePoolMemory_006b4ba0)(0xc);
  *puVar3 = *(undefined4 *)(param_1 + 0x18);
  puVar3[1] = uVar2;
  puVar3[2] = 0;
  if (DAT_006eac76 != (undefined4 *)0x0) {
    puVar3[2] = (uint)DAT_006eac76;
  }
  DAT_006eac76 = puVar3;
  iVar4 = (uint)fn_005ea4a0((byte)(4));
  uVar2 = FUN_00521c20(*param_2, 1);
  *(undefined4 *)(iVar4 + 0x10) = uVar2;
  if (**(char **)(param_1 + 4) == '\0') {
    uVar2 = FUN_005e9fd0((uint)(*(undefined4 *)(*(int *)(param_1 + 0x10) + 4)));
    *(undefined4 *)(iVar4 + 4) = uVar2;
  }
  else {
    uVar2 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
    *(undefined4 *)(iVar4 + 4) = uVar2;
  }
  uVar2 = (uint)fn_005ea4a0((byte)(0x1e));
  puVar3 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar2));
  *(int *)(*(int *)((int)puVar3 + 10) + 0x10) = iVar4;
  *(undefined4 *)(*(int *)((int)puVar3 + 10) + 0x14) = *(undefined4 *)(param_1 + 0x10);
  cVar1 = FUN_005e9fe0(*(undefined4 *)(*(int *)(*(int *)((int)puVar3 + 10) + 0x10) + 4),
                       *(undefined4 *)(*(int *)(*(int *)((int)puVar3 + 10) + 0x14) + 4));
  if (cVar1 == '\0') {
    iVar4 = (uint)fn_005ea4a0((byte)(0x32));
    *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(*(int *)((int)puVar3 + 10) + 0x14);
    uVar2 = FUN_005e9fd0((uint)(*(undefined4 *)(*(int *)(*(int *)((int)puVar3 + 10) + 0x10) + 4)));
    *(undefined4 *)(iVar4 + 4) = uVar2;
    *(int *)(*(int *)((int)puVar3 + 10) + 0x14) = iVar4;
  }
  if (**(char **)(param_1 + 4) == '\0') {
    uVar2 = FUN_005e9fd0((uint)(*(undefined4 *)(*(int *)(param_1 + 0x10) + 4)));
    *(undefined4 *)(*(int *)((int)puVar3 + 10) + 4) = uVar2;
  }
  else {
    uVar2 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
    *(undefined4 *)(*(int *)((int)puVar3 + 10) + 4) = uVar2;
  }
  fn_005ea430((int)(puVar3), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar3 = 0;
    DAT_006eac6a = puVar3;
  }
  else {
    *puVar3 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar3;
  }
  DAT_006eac6e = puVar3;
  return;
}

/* Native 0x5ec3f0, 318 bytes. */
void fn_005ec3f0(undefined1 *param_1)
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  uVar1 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
  iVar2 = create_temp_object(uVar1);
  iVar3 = (uint)fn_005ea4a0((byte)(4));
  uVar1 = FUN_00521c20(iVar2, 1);
  *(undefined4 *)(iVar3 + 0x10) = uVar1;
  if (**(char **)(param_1 + 4) == '\0') {
    CError_Internal(s_CleanUpIR_c_006b4bbc, 0x26d);
  }
  else {
    *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar2 + 0x10);
  }
  iVar4 = (uint)fn_005ea4a0((byte)(*param_1));
  memcpy((void *)iVar4, param_1, 46);
  uVar1 = (uint)fn_005ea4a0((byte)(0x1e));
  puVar5 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar1));
  *(int *)(*(int *)((int)puVar5 + 10) + 0x10) = iVar3;
  *(int *)(*(int *)((int)puVar5 + 10) + 0x14) = iVar4;
  uVar1 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
  *(undefined4 *)(*(int *)((int)puVar5 + 10) + 4) = uVar1;
  fn_005ea430((int)(puVar5), (int)(DAT_006eac72));
  if (DAT_006eac6e == (undefined4 *)0x0) {
    *puVar5 = 0;
    DAT_006eac6a = puVar5;
  }
  else {
    *puVar5 = *DAT_006eac6e;
    *DAT_006eac6e = (uint)puVar5;
  }
  DAT_006eac6e = puVar5;
  *param_1 = 4;
  uVar1 = FUN_00521c20(iVar2, 1);
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  return;
}

/* Native 0x5ec530, 369 bytes. */
void fn_005ec530(undefined1 *param_1, char param_2)
{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  if ((**(char **)(param_1 + 4) == '\0') || (param_2 != '\0')) {
    puVar4 = (undefined4 *)fn_005ea470((byte)(4), (uint)(*(undefined4 *)(param_1 + 0x14)));
    fn_005ea430((int)(puVar4), (int)(DAT_006eac72));
    if (DAT_006eac6e == (undefined4 *)0x0) {
      *puVar4 = 0;
      DAT_006eac6a = puVar4;
    }
    else {
      *puVar4 = *DAT_006eac6e;
      *DAT_006eac6e = (uint)puVar4;
    }
    DAT_006eac6e = puVar4;
    *param_1 = 0x34;
    uVar1 = DAT_0070490c;
    *(undefined4 *)(param_1 + 0x10) = DAT_00704908;
    *(undefined4 *)(param_1 + 0x14) = uVar1;
  }
  else {
    uVar1 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
    uVar1 = create_temp_object(uVar1);
    iVar2 = (uint)fn_005ea4a0((byte)(4));
    uVar3 = FUN_00521c20(uVar1, 1);
    *(undefined4 *)(iVar2 + 0x10) = uVar3;
    if (**(char **)(param_1 + 4) == '\0') {
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x239);
    }
    else {
      uVar3 = FUN_005e9fd0((uint)(*(char **)(param_1 + 4)));
      *(undefined4 *)(iVar2 + 4) = uVar3;
    }
    uVar3 = (uint)fn_005ea4a0((byte)(0x1e));
    puVar4 = (undefined4 *)fn_005ea470((byte)(4), (uint)(uVar3));
    *(int *)(*(int *)((int)puVar4 + 10) + 0x10) = iVar2;
    *(undefined4 *)(*(int *)((int)puVar4 + 10) + 0x14) = *(undefined4 *)(param_1 + 0x14);
    uVar3 = FUN_005e9fd0((uint)(*(undefined4 *)(param_1 + 4)));
    *(undefined4 *)(*(int *)((int)puVar4 + 10) + 4) = uVar3;
    fn_005ea430((int)(puVar4), (int)(DAT_006eac72));
    if (DAT_006eac6e == (undefined4 *)0x0) {
      *puVar4 = 0;
      DAT_006eac6a = puVar4;
    }
    else {
      *puVar4 = *DAT_006eac6e;
      *DAT_006eac6e = (uint)puVar4;
    }
    DAT_006eac6e = puVar4;
    *param_1 = 4;
    uVar1 = FUN_00521c20(uVar1, 1);
    *(undefined4 *)(param_1 + 0x10) = uVar1;
    if (**(char **)(param_1 + 4) == '\0') {
      CError_Internal(s_CleanUpIR_c_006b4bbc, 0x24c);
    }
  }
  return;
}
