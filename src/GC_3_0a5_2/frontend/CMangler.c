/* CMangler.c: native member, ABI, layout and data review is recorded in the TU ledger. */
#include <string.h>
#include <stdio.h>
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef byte undefined1;
typedef ushort undefined2;
typedef uint undefined4;
typedef byte bool;
#define true 1
#define false 0
#pragma pack(push,2)
typedef struct NativePointerType { ushort kind; uint size; uint target; uint qual; } NativePointerType;
#pragma pack(pop)
typedef struct NativeGList { char **data; int size; int capacity; int increment; } NativeGList;
extern NativeGList name_mangle_list;
extern uint constructor_name,destructor_name,assignment_operator_name;
extern byte DAT_0070f1e1,DAT_0070f1ee;
extern byte DAT_007037c0[],DAT_0070bb08[];
extern uint DAT_007101c4;
extern void CError_Internal(const char *,int);
extern byte FUN_00452f10(uint),FUN_0053d470(uint),CTemplateTools_IsDependentType(uint),is_pascal_object(uint),CParser_IsNullOrAtOrDollarPrefixedName(uint);
extern void FUN_0044cfe0(char **),FUN_0044d0a0(char **);
extern void FUN_0046d530(NativeGList *,const char *),FUN_0046d5a0(NativeGList *,const char *);
extern void AppendGListByte(NativeGList *,int),CompilerTools_AppendGListData(NativeGList *,const void *,uint);
extern uint GetHashNameNode(const char *);
extern uint *FUN_00553440(uint);
extern void FUN_004d8810(char *,uint,uint);
static char literal_0069ac14[]="@STRING@";
static char literal_0069ac20[]="%ld";
static char literal_0069ac24[]="CMangler.c";
static char literal_0069ac30[]="@GUARD@";
static char literal_0069ac38[]="@LOCAL@";
static char literal_0069ac40[]="";
static char literal_0069ac44[]="__";
static char literal_0069ac48[]="@@";
static char literal_0069ac4c[]="main";
static char literal_0069ac54[]="__op";
static char literal_0069ac5c[]="Fv";
static char literal_0069ac60[]="Uc";
static char literal_0069ac64[]="Sc";
static char literal_0069ac68[]="Us";
static char literal_0069ac6c[]="Ui";
static char literal_0069ac70[]="Ul";
static char literal_0069ac74[]="Ux";
static char literal_0069ac78[]="16_Imaginary float";
static char literal_0069ac8c[]="17_Imaginary double";
static char literal_0069aca0[]="22_Imaginary long double";
static char literal_0069acbc[]="14_Complex float";
static char literal_0069acd0[]="15_Complex double";
static char literal_0069ace4[]="20_Complex long double";
static char literal_0069acfc[]="XUc";
static char literal_0069ad00[]="Xc";
static char literal_0069ad04[]="XC";
static char literal_0069ad08[]="XUs";
static char literal_0069ad0c[]="Xs";
static char literal_0069ad10[]="XS";
static char literal_0069ad14[]="XUi";
static char literal_0069ad18[]="Xi";
static char literal_0069ad1c[]="XI";
static char literal_0069ad20[]="Xf";
static char literal_0069ad24[]="Xp";
static char literal_0069ad28[]="1T";
static char literal_0069ad2c[]="enum";
static char literal_0069ad34[]="3<T>";
static char literal_0069ad3c[]="class";
static char literal_0069ad44[]="%d";
static char literal_0069ad48[]="struct";
static char literal_0069ad50[]="union";
static char literal_0069ad58[]="@%ld@%ld@";
static char literal_0069ad64[]="@%ld@";
static char literal_0069ad6c[]="@%ld@%ld@%ld@";
static char literal_0069ad7c[]="__RTTI__";
static char literal_0069ad88[]="__vt__";
static char literal_0069ad90[]="__nw";
static char literal_0069ad98[]="__dl";
static char literal_0069ada0[]="__nwa";
static char literal_0069ada8[]="__dla";
static char literal_0069adb0[]="__pl";
static char literal_0069adb8[]="__mi";
static char literal_0069adc0[]="__ml";
static char literal_0069adc8[]="__dv";
static char literal_0069add0[]="__md";
static char literal_0069add8[]="__er";
static char literal_0069ade0[]="__ad";
static char literal_0069ade8[]="__or";
static char literal_0069adf0[]="__co";
static char literal_0069adf8[]="__nt";
static char literal_0069ae00[]="__lt";
static char literal_0069ae08[]="__gt";
static char literal_0069ae10[]="__apl";
static char literal_0069ae18[]="__ami";
static char literal_0069ae20[]="__amu";
static char literal_0069ae28[]="__adv";
static char literal_0069ae30[]="__amd";
static char literal_0069ae38[]="__aer";
static char literal_0069ae40[]="__aad";
static char literal_0069ae48[]="__aor";
static char literal_0069ae50[]="__ls";
static char literal_0069ae58[]="__rs";
static char literal_0069ae60[]="__min";
static char literal_0069ae68[]="__max";
static char literal_0069ae70[]="__als";
static char literal_0069ae78[]="__ars";
static char literal_0069ae80[]="__eq";
static char literal_0069ae88[]="__ne";
static char literal_0069ae90[]="__le";
static char literal_0069ae98[]="__ge";
static char literal_0069aea0[]="__aa";
static char literal_0069aea8[]="__oo";
static char literal_0069aeb0[]="__pp";
static char literal_0069aeb8[]="__mm";
static char literal_0069aec0[]="__cm";
static char literal_0069aec8[]="__rm";
static char literal_0069aed0[]="__rf";
static char literal_0069aed8[]="__cl";
static char literal_0069aee0[]="__vc";
static char literal_0069aee8[]="operator new";
static char literal_0069aef8[]="operator=";
static char literal_0069af04[]="operator delete";
static char literal_0069af14[]="operator new[]";
static char literal_0069af24[]="operator delete[]";
static char literal_0069af38[]="operator+";
static char literal_0069af44[]="operator-";
static char literal_0069af50[]="operator*";
static char literal_0069af5c[]="operator/";
static char literal_0069af68[]="operator%";
static char literal_0069af74[]="operator^";
static char literal_0069af80[]="operator&";
static char literal_0069af8c[]="operator|";
static char literal_0069af98[]="operator~";
static char literal_0069afa4[]="operator!";
static char literal_0069afb0[]="operator<";
static char literal_0069afbc[]="operator>";
static char literal_0069afc8[]="operator+=";
static char literal_0069afd4[]="operator-=";
static char literal_0069afe0[]="operator*=";
static char literal_0069afec[]="operator/=";
static char literal_0069aff8[]="operator%=";
static char literal_0069b004[]="operator^=";
static char literal_0069b010[]="operator&=";
static char literal_0069b01c[]="operator|=";
static char literal_0069b028[]="operator<<";
static char literal_0069b034[]="operator>>";
static char literal_0069b040[]="operator<<=";
static char literal_0069b04c[]="operator>>=";
static char literal_0069b058[]="operator==";
static char literal_0069b064[]="operator!=";
static char literal_0069b070[]="operator<=";
static char literal_0069b07c[]="operator>=";
static char literal_0069b088[]="operator&&";
static char literal_0069b094[]="operator||";
static char literal_0069b0a0[]="operator++";
static char literal_0069b0ac[]="operator--";
static char literal_0069b0b8[]="operator,";
static char literal_0069b0c4[]="operator->*";
static char literal_0069b0d0[]="operator()";
static char literal_0069b0dc[]="operator[]";
static char literal_0069b0e8[]="__ct";
static char literal_0069b0f0[]="__dt";
static char literal_0069b0f8[]="__as";
void CMangler_SetupLocalStringName(int param_1, int param_2, int param_3);
void CMangler_SetupGuardVarName(int param_1, int param_2);
void CMangler_SetupLocalVarName(int param_1, int param_2, int param_3);
undefined4 COptimizer_GetFunctionObject(int param_1);
undefined4 get_object_link_name(int param_1);
undefined4 CMangler_GetCovariantFunctionName(int param_1, undefined4 param_2);
undefined4 CMangler_GetLinkName(int param_1);
undefined4 CMangler_ConversionFuncName(undefined4 param_1, undefined4 param_2);
void mangle_function_name(int param_1, undefined4 *param_2);
void mangle_args(undefined4 *param_1);
void CMangler_MangleType(undefined4 param_1, undefined4 param_2, char param_3);
void mangle_type(char *param_1, uint param_2);
void mangle_qualified_name(undefined4 *param_1, int param_2);
undefined4 CMangler_TemplateInstanceName(int param_1, undefined4 param_2);
void fn_00557c30(int *param_1);
void fn_00557f50(undefined4 *param_1);
undefined4 CMangler_ThunkName(int param_1, int param_2, int param_3, int param_4);
undefined4 CMangler_RTTIObjectName(undefined4 param_1, undefined4 param_2);
struct NativeMangleClass;
undefined4 CMangler_VTableName(struct NativeMangleClass *entry);
undefined4 CMangler_OperatorName(short param_1);
char * CMangler_GetOperator(int param_1);
void CMangler_Setup(void);

void CMangler_SetupLocalStringName(int param_1, int param_2, int param_3)
{
  undefined4 *puVar1;
  char cVar2;
  undefined4 uVar3;
  char local_50[64];
  cVar2 = FUN_00452f10((uint)(param_1));
  if (cVar2 == '\0') {
    CError_Internal(literal_0069ac24, 0x4d2);
  }
  if (*(int *)(param_2 + 0x48) != 0) {
    fn_00557f50((undefined4 *)(*(undefined4 *)(*(int *)(param_2 + 0x48) + 8)));
  }
  for (puVar1 = *(undefined4 **)(param_2 + 8); puVar1 != (undefined4 *)0x0 && (puVar1[1] == 0);
      puVar1 = (undefined4 *)*puVar1) {
  }
  name_mangle_list.size = 0;
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac14));
  mangle_function_name((int)(param_2), (undefined4 *)(puVar1));
  if (param_3 > 0) {
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x40));
    param_3 = param_3 - 1;
    if (param_3 < 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x6e));
      param_3 = -param_3;
    }
    sprintf(local_50, literal_0069ac20, param_3);
    FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(local_50));
  }
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0));
  FUN_0044cfe0((char **)(name_mangle_list.data));
  uVar3 = GetHashNameNode((const char *)(*name_mangle_list.data));
  FUN_0044d0a0((char **)(name_mangle_list.data));
  *(undefined4 *)(param_1 + 0x48) = uVar3;
  return;
}

void CMangler_SetupGuardVarName(int param_1, int param_2)
{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  char *pcVar4;
  cVar1 = FUN_00452f10((uint)(param_1));
  if (cVar1 == '\0') {
    CError_Internal(literal_0069ac24, 0x4a9);
  }
  cVar1 = FUN_00452f10((uint)(param_2));
  if ((cVar1 == '\0') || (*(int *)(param_2 + 0x48) == 0)) {
    CError_Internal(literal_0069ac24, 0x4aa);
  }
  pcVar3 = (char *)(*(int *)(param_2 + 0x48) + 10);
  pcVar4 = pcVar3;
  do {
    if (*pcVar4 == '\0') {
LAB_00556970:
      name_mangle_list.size = 0;
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac30));
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(pcVar3));
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0));
      FUN_0044cfe0((char **)(name_mangle_list.data));
      uVar2 = GetHashNameNode((const char *)(*name_mangle_list.data));
      FUN_0044d0a0((char **)(name_mangle_list.data));
      *(undefined4 *)(param_1 + 0x48) = uVar2;
      return;
    }
    if (*pcVar4 == '@') {
      if ((pcVar4[1] == 'L') && (pcVar4[2] == 'O') && (pcVar4[3] == 'C') &&
         (pcVar4[4] == 'A' && (pcVar4[5] == 'L') && (pcVar4[6] == '@'))) {
        pcVar3 = pcVar4 + 7;
      }
      goto LAB_00556970;
    }
    pcVar4 = pcVar4 + 1;
  } while( true );
}

void CMangler_SetupLocalVarName(int param_1, int param_2, int param_3)
{
  undefined4 *puVar1;
  char cVar2;
  undefined4 uVar3;
  char local_50[64];
  cVar2 = FUN_00452f10((uint)(param_1));
  if (cVar2 == '\0') {
    CError_Internal(literal_0069ac24, 0x485);
  }
  if (*(int *)(param_2 + 0x48) != 0) {
    fn_00557f50((undefined4 *)(*(undefined4 *)(*(int *)(param_2 + 0x48) + 8)));
  }
  for (puVar1 = *(undefined4 **)(param_2 + 8); puVar1 != (undefined4 *)0x0 && (puVar1[1] == 0);
      puVar1 = (undefined4 *)*puVar1) {
  }
  name_mangle_list.size = 0;
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac38));
  mangle_function_name((int)(param_2), (undefined4 *)(puVar1));
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x40));
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(*(int *)(param_1 + 0xc) + 10));
  if (param_3 > 0) {
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x40));
    param_3 = param_3 - 1;
    if (param_3 < 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x6e));
      param_3 = -param_3;
    }
    sprintf(local_50, literal_0069ac20, param_3);
    FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(local_50));
  }
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0));
  FUN_0044cfe0((char **)(name_mangle_list.data));
  uVar3 = GetHashNameNode((const char *)(*name_mangle_list.data));
  FUN_0044d0a0((char **)(name_mangle_list.data));
  *(undefined4 *)(param_1 + 0x48) = uVar3;
  return;
}

undefined4 COptimizer_GetFunctionObject(int param_1)
{
  char cVar1;
  undefined4 uVar2;
  cVar1 = *(char *)(param_1 + 2);
  while (cVar1 == '\x06') {
    param_1 = *(int *)(param_1 + 0x40);
    cVar1 = *(char *)(param_1 + 2);
  }
  switch(cVar1) {
  case '\0':
    if (*(int *)(param_1 + 0x48) == 0) {
      uVar2 = get_object_link_name((int)(param_1));
      *(undefined4 *)(param_1 + 0x48) = uVar2;
    }
    return *(undefined4 *)(param_1 + 0x48);
  case '\x01':
  case '\x02':
  case '\b':
    return *(undefined4 *)(param_1 + 0xc);
  case '\x03':
  case '\x04':
    if (*(int *)(param_1 + 0x44) == 0) {
      uVar2 = CMangler_GetLinkName((int)(param_1));
      *(undefined4 *)(param_1 + 0x44) = uVar2;
    }
    return *(undefined4 *)(param_1 + 0x44);
  case '\x05':
    uVar2 = CMangler_GetLinkName((int)(param_1));
    return uVar2;
  default:
    CError_Internal(literal_0069ac24, 0x465);
    return 0;
  }
}

undefined4 get_object_link_name(int param_1)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  for (puVar2 = *(undefined4 **)(param_1 + 8); puVar2 != (undefined4 *)0x0 && (puVar2[1] == 0);
      puVar2 = (undefined4 *)*puVar2) {
  }
  name_mangle_list.size = 0;
  if (puVar2 != (undefined4 *)0x0) {
    CompilerTools_AppendGListData((NativeGList *)(&name_mangle_list), (const void *)(literal_0069ac40), (uint)(0));
    FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(*(int *)(param_1 + 0xc) + 10));
    for (; puVar2 != (undefined4 *)0x0 && (puVar2[1] == 0); puVar2 = (undefined4 *)*puVar2) {
    }
    if ((puVar2 != (undefined4 *)0x0) && ((*(uint *)(param_1 + 0x14) & 0x80000) != 0)) {
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac44));
      mangle_qualified_name((undefined4 *)(*puVar2), (int)(puVar2[1] + 10));
    }
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0));
    FUN_0044cfe0((char **)(name_mangle_list.data));
    uVar1 = GetHashNameNode((const char *)(*name_mangle_list.data));
    FUN_0044d0a0((char **)(name_mangle_list.data));
    return uVar1;
  }
  return *(undefined4 *)(param_1 + 0xc);
}

undefined4 CMangler_GetCovariantFunctionName(int param_1, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  cVar1 = *(char *)(param_1 + 2);
  while (cVar1 == '\x06') {
    param_1 = *(int *)(param_1 + 0x40);
    cVar1 = *(char *)(param_1 + 2);
  }
  switch(*(undefined1 *)(param_1 + 2)) {
  case 0:
    if (*(int *)(param_1 + 0x48) == 0) {
      uVar3 = get_object_link_name((int)(param_1));
      *(undefined4 *)(param_1 + 0x48) = uVar3;
    }
    iVar2 = *(int *)(param_1 + 0x48);
    break;
  case 1:
  case 2:
  case 8:
    iVar2 = *(int *)(param_1 + 0xc);
    break;
  case 3:
  case 4:
    if (*(int *)(param_1 + 0x44) == 0) {
      uVar3 = CMangler_GetLinkName((int)(param_1));
      *(undefined4 *)(param_1 + 0x44) = uVar3;
    }
    iVar2 = *(int *)(param_1 + 0x44);
    break;
  case 5:
    iVar2 = CMangler_GetLinkName((int)(param_1));
    break;
  default:
    CError_Internal(literal_0069ac24, 0x465);
    iVar2 = 0;
  }
  name_mangle_list.size = 0;
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(iVar2 + 10));
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac48));
  mangle_type((char *)(param_2), (uint)(0));
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0));
  FUN_0044cfe0((char **)(name_mangle_list.data));
  uVar3 = GetHashNameNode((const char *)(*name_mangle_list.data));
  FUN_0044d0a0((char **)(name_mangle_list.data));
  return uVar3;
}

undefined4 CMangler_GetLinkName(int object)
{
 undefined4 *scope;
 uint result;
 if(*(byte *)(object+2)!=5 && *(uint *)(object+72)!=0)
  fn_00557f50((uint *)*(uint *)(*(uint *)(object+72)+8));
 scope=*(uint **)(object+8);
 while(scope!=0 && scope[1]==0)scope=(uint *)*scope;
 name_mangle_list.size=0;
 if(is_pascal_object(object) && (scope==0 || scope[3]==0))return *(uint *)(object+12);
 if((*(uint *)(object+20)&0x80000)!=0 &&
    (memcmp(literal_0069ac4c,(char *)(*(uint *)(object+12)+10),5)!=0 || *(uint *)(object+8)!=DAT_007101c4)){
  mangle_function_name(object,scope);
  AppendGListByte(&name_mangle_list,0);
  AppendGListByte(&name_mangle_list,0);
 }else return *(uint *)(object+12);
 FUN_0044cfe0(name_mangle_list.data);
 result=GetHashNameNode(*name_mangle_list.data);
 FUN_0044d0a0(name_mangle_list.data);
 return result;
}

undefined4 CMangler_ConversionFuncName(undefined4 param_1, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  cVar1 = CTemplateTools_IsDependentType((uint)(param_1));
  if (cVar1 != '\0') {
    uVar2 = GetHashNameNode((const char *)(literal_0069ac54));
    return uVar2;
  }
  name_mangle_list.size = 0;
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac54));
  mangle_type((char *)(param_1), (uint)(param_2));
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0));
  FUN_0044cfe0((char **)(name_mangle_list.data));
  uVar2 = GetHashNameNode((const char *)(*name_mangle_list.data));
  FUN_0044d0a0((char **)(name_mangle_list.data));
  return uVar2;
}

void mangle_function_name(int param_1, undefined4 *param_2)
{
  int iVar1;
  uint uVar2;
  int *piVar3;
  iVar1 = *(int *)(param_1 + 0x10);
  piVar3 = *(int **)(iVar1 + 6);
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(*(int *)(param_1 + 0xc) + 10));
  if (*(int *)(param_1 + 0x48) != 0) {
    if ((*(uint *)(iVar1 + 0x16) & 0x40) != 0) {
      mangle_type((char *)(*(undefined4 *)(iVar1 + 0xe)), (uint)(*(undefined4 *)(iVar1 + 0x12)));
    }
    fn_00557c30((int *)(*(undefined4 *)(*(int *)(param_1 + 0x48) + 8)));
  }
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac44));
  for (; param_2 != (undefined4 *)0x0 && (param_2[1] == 0); param_2 = (undefined4 *)*param_2) {
  }
  if (param_2 != (undefined4 *)0x0) {
    mangle_qualified_name((undefined4 *)(*param_2), (int)(param_2[1] + 10));
    if (param_2[3] != 0) {
      if (*(int *)(param_1 + 0xc) == destructor_name) {
        FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac5c));
        return;
      }
      if (piVar3 != (int *)0x0) {
        if (*(int *)(param_1 + 0xc) == constructor_name) {
          piVar3 = (int *)FUN_00553440((uint)(iVar1));
        }
        else if (((*(uint *)(iVar1 + 0x16) & 0x10) != 0) && (*(char *)(iVar1 + 0x2a) == '\0')) {
          uVar2 = piVar3[4];
          if ((uVar2 & 1) != 0) {
            AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
          }
          if ((uVar2 & 2) != 0) {
            AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
          }
          piVar3 = (int *)*piVar3;
        }
      }
    }
  }
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x46));
  mangle_args((undefined4 *)(piVar3));
  if ((*(int *)(param_1 + 0x48) != 0) && (DAT_0070f1e1 != '\0')) {
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x5f));
    mangle_type((char *)(*(undefined4 *)(iVar1 + 0xe)), (uint)(*(undefined4 *)(iVar1 + 0x12)));
  }
  return;
}

void mangle_args(undefined4 *args)
{
 NativePointerType pointer_type;
 char *type;
 if(args!=0){
  if(args[3]!=0){
   while(args!=0){
    if(args!=(undefined4 *)DAT_007037c0 && args!=(undefined4 *)DAT_0070bb08){
     type=(char *)args[3];
     if(*type==12){
      pointer_type=*(NativePointerType *)type;
      pointer_type.qual&=~3;
      mangle_type((char *)&pointer_type,args[4]);
     }else mangle_type(type,0);
    }else AppendGListByte(&name_mangle_list,'e');
    args=(undefined4 *)*args;
   }
  }else AppendGListByte(&name_mangle_list,'e');
 }else AppendGListByte(&name_mangle_list,'v');
}

void CMangler_MangleType(undefined4 param_1, undefined4 param_2, char param_3)
{
  if (param_3 == '\0') {
    name_mangle_list.size = 0;
  }
  mangle_type((char *)(param_1), (uint)(param_2));
  return;
}

void mangle_type(char *param_1, uint param_2)
{
  uint uVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  char local_2c[16];
  char local_1c[16];
  switch(*param_1) {
  case '\0':
    if ((param_2 & 1) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
    }
    if ((param_2 & 2) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
    }
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x76));
    return;
  case '\x01':
  case '\x02':
    if ((param_2 & 1) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
    }
    if ((param_2 & 2) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
    }
    switch(param_1[6]) {
    case '\0':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x62));
      return;
    case '\x01':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(99));
      return;
    case '\x02':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac64));
      return;
    case '\x03':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac60));
      return;
    case '\x04':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x77));
      return;
    case '\x05':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x73));
      return;
    case '\x06':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac68));
      return;
    case '\a':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x69));
      return;
    case '\b':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac6c));
      return;
    case '\t':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x6c));
      return;
    case '\n':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac70));
      return;
    case '\v':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x78));
      return;
    case '\f':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac74));
      return;
    case '\r':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x66));
      return;
    case '\x0e':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x44));
      return;
    case '\x0f':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(100));
      return;
    case '\x10':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x72));
      return;
    case '\x11':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac78));
      return;
    case '\x12':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac8c));
      return;
    case '\x13':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069aca0));
      return;
    case '\x14':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069acbc));
      return;
    case '\x15':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069acd0));
      return;
    case '\x16':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ace4));
      return;
    case '\x17':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x30));
      return;
    case '\x18':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x31));
      return;
    case '\x19':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x32));
      return;
    case '\x1a':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x33));
      return;
    case '\x1b':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x34));
      return;
    case '\x1c':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x35));
      return;
    case '\x1d':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x36));
      return;
    case '\x1e':
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x37));
      return;
    default:
      CError_Internal(literal_0069ac24, 0x286);
    }
  case '\x04':
    if ((param_2 & 1) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
    }
    if ((param_2 & 2) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
    }
    if (*(int *)(param_1 + 0x12) == 0) {
      mangle_qualified_name((undefined4 *)(*(undefined4 *)(param_1 + 6)), (int)(literal_0069ad2c));
    }
    else {
      mangle_qualified_name((undefined4 *)(*(undefined4 *)(param_1 + 6)), (int)(*(int *)(param_1 + 0x12) + 10));
    }
    return;
  default:
    CError_Internal(literal_0069ac24, 0x2f1);
    return;
  case '\x05':
    break;
  case '\x06':
    if ((param_2 & 1) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
    }
    if ((param_2 & 2) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
    }
    if (*(int *)(param_1 + 10) == 0) {
      mangle_qualified_name((undefined4 *)(**(undefined4 **)(param_1 + 6)), (int)(literal_0069ad3c));
    }
    else {
      mangle_qualified_name((undefined4 *)(**(undefined4 **)(param_1 + 6)), (int)((*(undefined4 **)(param_1 + 6))[1] + 10))
      ;
    }
    return;
  case '\a':
    if ((param_2 & 1) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
    }
    if ((param_2 & 2) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
    }
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x46));
    mangle_args((undefined4 *)(*(undefined4 *)(param_1 + 6)));
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x5f));
    mangle_type((char *)(*(undefined4 *)(param_1 + 0xe)), (uint)(*(undefined4 *)(param_1 + 0x12)));
    return;
  case '\n':
    FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad28));
    return;
  case '\v':
    if (**(char **)(param_1 + 10) == '\x06') {
      uVar1 = *(uint *)(param_1 + 0xe);
      if ((uVar1 & 1) != 0) {
        AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
      }
      if ((uVar1 & 2) != 0) {
        AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
      }
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x4d));
      iVar5 = *(int *)(param_1 + 10);
      if (*(int *)(iVar5 + 10) == 0) {
        mangle_qualified_name((undefined4 *)(**(undefined4 **)(iVar5 + 6)), (int)(literal_0069ad3c));
      }
      else {
        mangle_qualified_name((undefined4 *)(**(undefined4 **)(iVar5 + 6)), (int)((*(undefined4 **)(iVar5 + 6))[1] + 10));
      }
      mangle_type((char *)(*(undefined4 *)(param_1 + 6)), (uint)(param_2));
      return;
    }
    FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad34));
    return;
  case '\f':
    uVar1 = *(uint *)(param_1 + 10);
    if ((uVar1 & 1) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
    }
    if ((uVar1 & 2) != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
    }
    if ((*(uint *)(param_1 + 10) & 0x20) == 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x50));
    }
    else {
      if ((DAT_0070f1ee == '\0') || (*param_1 != '\f') || ((*(uint *)(param_1 + 10) & 0xa0) != 0xa0)
         ) {
        uVar3 = 0x52;
      }
      else {
        uVar3 = 0x4f;
      }
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(uVar3));
    }
    mangle_type((char *)(*(undefined4 *)(param_1 + 6)), (uint)(param_2));
    return;
  case '\r':
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x41));
    if (*(int *)(*(int *)(param_1 + 6) + 2) == 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x30));
    }
    else {
      sprintf(local_1c, literal_0069ac20, *(int *)(param_1 + 2) / *(int *)(*(int *)(param_1 + 6) + 2));
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(local_1c));
    }
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x5f));
    mangle_type((char *)(*(undefined4 *)(param_1 + 6)), (uint)(param_2));
    return;
  }
  if ((param_2 & 1) != 0) {
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x43));
  }
  if ((param_2 & 2) != 0) {
    AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x56));
  }
  iVar5 = (int)param_1[0x10];
  if ((iVar5 > 3) && (iVar5 < 0xf) && (*(int *)(param_1 + 2) == 0x10)) {
    switch(iVar5) {
    case 4:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069acfc));
      return;
    case 5:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad00));
      return;
    case 6:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad04));
      return;
    case 7:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad08));
      return;
    case 8:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad0c));
      return;
    case 9:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad10));
      return;
    case 10:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad14));
      return;
    case 0xb:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad18));
      return;
    case 0xc:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad1c));
      return;
    case 0xd:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad20));
      return;
    case 0xe:
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad24));
      return;
    }
  }
  if ((*(int *)(param_1 + 6) == 0) ||
     (cVar2 = CParser_IsNullOrAtOrDollarPrefixedName((uint)(*(int *)(param_1 + 6))), cVar2 != '\0')) {
    switch(param_1[0x10]) {
    case '\0':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad48));
      return;
    case '\x01':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad50));
      return;
    case '\x02':
      FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad3c));
      return;
    default:
      CError_Internal(literal_0069ac24, 0x2e2);
    }
  }
  else {
    iVar5 = *(int *)(param_1 + 6);
    iVar4 = -1;
    pcVar6 = (char *)(iVar5 + 10);
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 - 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar2 != '\0');
    sprintf(local_2c, literal_0069ad44, -iVar4 - 2);
    FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(local_2c));
    FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)((char *)(iVar5 + 10)));
  }
  return;
}

void mangle_qualified_name(undefined4 *scope,int name)
{
 int count=1,length;
 const char *parts[10],*part;
 char lengthBuffer[16];
 parts[0]=(const char *)name;
 if(scope!=0){
  do{
   if(scope[1]!=0){
    parts[count]=(const char *)(scope[1]+10);
    ++count;
    if(count>=9)break;
   }
   scope=(undefined4 *)*scope;
  }while(scope!=0);
 }
 if(count>1){
  AppendGListByte(&name_mangle_list,'Q');
  AppendGListByte(&name_mangle_list,(char)(count+'0'));
 }
 while(--count>=0){
  part=parts[count];
  length=strlen(part);
  sprintf(lengthBuffer,literal_0069ad44,length);
  FUN_0046d530(&name_mangle_list,lengthBuffer);
  FUN_0046d530(&name_mangle_list,part);
 }
}

undefined4 CMangler_TemplateInstanceName(int param_1, undefined4 param_2)
{
  undefined4 uVar1;
  fn_00557f50((undefined4 *)(param_2));
  name_mangle_list.size = 0;
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(param_1 + 10));
  fn_00557c30((int *)(param_2));
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0));
  FUN_0044cfe0((char **)(name_mangle_list.data));
  uVar1 = GetHashNameNode((const char *)(*name_mangle_list.data));
  FUN_0044d0a0((char **)(name_mangle_list.data));
  return uVar1;
}

void fn_00557c30(int *param_1)
{
  char *pcVar1;
  undefined1 *puVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  char auStack_2c[32];
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x3c));
  for (; param_1 != (int *)0x0; param_1 = (int *)*param_1) {
    cVar3 = *(char *)((int)param_1 + 7);
    if (cVar3 == '\x01') {
      pcVar1 = (char *)param_1[2];
      if (pcVar1 == (char *)0x0) {
        CError_Internal(literal_0069ac24, 0x1b4);
      }
      cVar3 = FUN_0053d470((uint)(pcVar1));
      if (cVar3 == '\0') {
        cVar3 = *pcVar1;
        if (cVar3 == '4') {
          FUN_004d8810((char *)(auStack_2c), (uint)(*(undefined4 *)(pcVar1 + 0x10)), (uint)(*(undefined4 *)(pcVar1 + 0x14)));
          FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(auStack_2c));
        }
        else if (cVar3 == ';') {
          AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x26));
          iVar4 = *(int *)(pcVar1 + 0x10);
          cVar3 = *(char *)(iVar4 + 2);
          while (cVar3 == '\x06') {
            iVar4 = *(int *)(iVar4 + 0x40);
            cVar3 = *(char *)(iVar4 + 2);
          }
          switch(cVar3) {
          case '\0':
            if (*(int *)(iVar4 + 0x48) == 0) {
              uVar5 = get_object_link_name((int)(iVar4));
              *(undefined4 *)(iVar4 + 0x48) = uVar5;
            }
            iVar4 = *(int *)(iVar4 + 0x48);
            break;
          case '\x01':
          case '\x02':
          case '\b':
            iVar4 = *(int *)(iVar4 + 0xc);
            break;
          case '\x03':
          case '\x04':
            if (*(int *)(iVar4 + 0x44) == 0) {
              uVar5 = CMangler_GetLinkName((int)(iVar4));
              *(undefined4 *)(iVar4 + 0x44) = uVar5;
            }
            iVar4 = *(int *)(iVar4 + 0x44);
            break;
          case '\x05':
            iVar4 = CMangler_GetLinkName((int)(iVar4));
            break;
          default:
            CError_Internal(literal_0069ac24, 0x465);
            iVar4 = 0;
          }
          FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(iVar4 + 10));
        }
        else if (cVar3 == 'K') {
          AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x26));
          puVar2 = *(undefined1 **)(*(int *)(pcVar1 + 0x10) + 4);
          switch(*puVar2) {
          case 4:
            FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(*(int *)(puVar2 + 8) + 10));
            FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ac44));
            if (*(int *)(pcVar1 + 0x14) == 0) {
              CError_Internal(literal_0069ac24, 0x1cb);
            }
            mangle_qualified_name
                      ((undefined4 *)(**(undefined4 **)(*(int *)(pcVar1 + 0x14) + 6)), (int)((*(undefined4 **)(*(int *)(pcVar1 + 0x14) + 6))[1] + 10));
            break;
          case 5:
            cVar3 = puVar2[2];
            while (cVar3 == '\x06') {
              puVar2 = *(undefined1 **)(puVar2 + 0x40);
              cVar3 = puVar2[2];
            }
            switch(cVar3) {
            case '\0':
              if (*(int *)(puVar2 + 0x48) == 0) {
                uVar5 = get_object_link_name((int)(puVar2));
                *(undefined4 *)(puVar2 + 0x48) = uVar5;
              }
              iVar4 = *(int *)(puVar2 + 0x48);
              break;
            case '\x01':
            case '\x02':
            case '\b':
              iVar4 = *(int *)(puVar2 + 0xc);
              break;
            case '\x03':
            case '\x04':
              if (*(int *)(puVar2 + 0x44) == 0) {
                uVar5 = CMangler_GetLinkName((int)(puVar2));
                *(undefined4 *)(puVar2 + 0x44) = uVar5;
              }
              iVar4 = *(int *)(puVar2 + 0x44);
              break;
            case '\x05':
              iVar4 = CMangler_GetLinkName((int)(puVar2));
              break;
            default:
              CError_Internal(literal_0069ac24, 0x465);
              iVar4 = 0;
            }
            FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(iVar4 + 10));
            break;
          default:
            CError_Internal(literal_0069ac24, 0x1d7);
          }
        }
        else {
          CError_Internal(literal_0069ac24, 0x1dc);
        }
      }
      else {
        AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x54));
      }
    }
    else if (cVar3 == '\0') {
      mangle_type((char *)(param_1[2]), (uint)(param_1[3]));
    }
    else {
      if (cVar3 != '\x02') {
        CError_Internal(literal_0069ac24, 0x1ea);
      }
      mangle_type((char *)(param_1[2]), (uint)(0));
    }
    if (*param_1 != 0) {
      AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x2c));
    }
  }
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0x3e));
  return;
}

static inline void ensure_object_link_name(int object)
{
 byte datatype;
 while((datatype=*(byte *)(object+2))==6)object=*(int *)(object+64);
 switch(datatype){
 case 0:
  if(*(uint *)(object+72)==0)*(uint *)(object+72)=get_object_link_name(object);
  break;
 case 3:case 4:
  if(*(uint *)(object+68)==0)*(uint *)(object+68)=CMangler_GetLinkName(object);
  break;
 case 5:CMangler_GetLinkName(object);break;
 case 1:case 2:case 8:break;
 default:CError_Internal(literal_0069ac24,0x465);break;
 }
}
void fn_00557f50(undefined4 *list)
{
 char *expression,*member;
 for(;list!=0;list=(uint *)*list){
  if(*((byte *)list+7)==1){
   expression=(char *)list[2];
   if(expression==0)CError_Internal(literal_0069ac24,0x189);
   if(FUN_0053d470((uint)expression)==0){
    switch((byte)*expression){
    case 52:break;
    case 59:ensure_object_link_name(*(int *)(expression+16));break;
    case 75:
     member=*(char **)(*(int *)(expression+16)+4);
     if(*member==5)ensure_object_link_name((int)member);
     break;
    default:CError_Internal(literal_0069ac24,0x19e);break;
    }
   }
  }
 }
}


undefined4 CMangler_ThunkName(int param_1, int param_2, int param_3, int param_4)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char local_50[64];
  cVar1 = *(char *)(param_1 + 2);
  while (cVar1 == '\x06') {
    param_1 = *(int *)(param_1 + 0x40);
    cVar1 = *(char *)(param_1 + 2);
  }
  switch(*(undefined1 *)(param_1 + 2)) {
  case 0:
    if (*(int *)(param_1 + 0x48) == 0) {
      uVar2 = get_object_link_name((int)(param_1));
      *(undefined4 *)(param_1 + 0x48) = uVar2;
    }
    iVar3 = *(int *)(param_1 + 0x48);
    break;
  case 1:
  case 2:
  case 8:
    iVar3 = *(int *)(param_1 + 0xc);
    break;
  case 3:
  case 4:
    if (*(int *)(param_1 + 0x44) == 0) {
      uVar2 = CMangler_GetLinkName((int)(param_1));
      *(undefined4 *)(param_1 + 0x44) = uVar2;
    }
    iVar3 = *(int *)(param_1 + 0x44);
    break;
  case 5:
    iVar3 = CMangler_GetLinkName((int)(param_1));
    break;
  default:
    CError_Internal(literal_0069ac24, 0x465);
    iVar3 = 0;
  }
  name_mangle_list.size = 0;
  if (param_3 == 0) {
    if (param_4 < 0) {
      sprintf(local_50, literal_0069ad64, -param_2);
    }
    else {
      sprintf(local_50, literal_0069ad58, -param_2, param_4);
    }
  }
  else {
    sprintf(local_50, literal_0069ad6c, -param_2, param_4, param_3);
  }
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(local_50));
  FUN_0046d5a0((NativeGList *)(&name_mangle_list), (const char *)(iVar3 + 10));
  FUN_0044cfe0((char **)(name_mangle_list.data));
  uVar2 = GetHashNameNode((const char *)(*name_mangle_list.data));
  FUN_0044d0a0((char **)(name_mangle_list.data));
  return uVar2;
}

undefined4 CMangler_RTTIObjectName(undefined4 param_1, undefined4 param_2)
{
  undefined4 uVar1;
  name_mangle_list.size = 0;
  FUN_0046d530((NativeGList *)(&name_mangle_list), (const char *)(literal_0069ad7c));
  mangle_type((char *)(param_1), (uint)(param_2));
  AppendGListByte((NativeGList *)(&name_mangle_list), (int)(0));
  FUN_0044cfe0((char **)(name_mangle_list.data));
  uVar1 = GetHashNameNode((const char *)(*name_mangle_list.data));
  FUN_0044d0a0((char **)(name_mangle_list.data));
  return uVar1;
}

#pragma pack(push,2)
typedef struct NativeMangleName { byte unknown00[10]; char text[1]; } NativeMangleName;
typedef struct NativeMangleNamespace { struct NativeMangleNamespace *parent; NativeMangleName *name; } NativeMangleNamespace;
typedef struct NativeMangleClass { ushort kind; uint size; NativeMangleNamespace *nspace; void *classname; } NativeMangleClass;
#pragma pack(pop)
undefined4 CMangler_VTableName(NativeMangleClass *entry)
{
    char **buffer;
    char **current;
    char **resultBuffer;
    uint name;
    name_mangle_list.size = 0;
    FUN_0046d530(&name_mangle_list, literal_0069ad88);
    if (entry->classname == 0)
        mangle_qualified_name((undefined4 *)entry->nspace->parent, (int)literal_0069ad3c);
    else
        mangle_qualified_name((undefined4 *)entry->nspace->parent, (int)entry->nspace->name->text);
    AppendGListByte(&name_mangle_list, 0);
    buffer = name_mangle_list.data;
    FUN_0044cfe0(buffer);
    current = name_mangle_list.data;
    name = GetHashNameNode(*current);
    resultBuffer = name_mangle_list.data;
    FUN_0044d0a0(resultBuffer);
    return name;
}

uint CMangler_OperatorName(short param_1)
{
 switch(param_1){
 case 0x21: return GetHashNameNode(literal_0069adf8);
 case 0x25: return GetHashNameNode(literal_0069add0);
 case 0x26: return GetHashNameNode(literal_0069ade0);
 case 0x28: return GetHashNameNode(literal_0069aed8);
 case 0x2a: return GetHashNameNode(literal_0069adc0);
 case 0x2b: return GetHashNameNode(literal_0069adb0);
 case 0x2c: return GetHashNameNode(literal_0069aec0);
 case 0x2d: return GetHashNameNode(literal_0069adb8);
 case 0x2f: return GetHashNameNode(literal_0069adc8);
 case 0x3c: return GetHashNameNode(literal_0069ae00);
 case 0x3d: return assignment_operator_name;
 case 0x3e: return GetHashNameNode(literal_0069ae08);
 case 0x5b: return GetHashNameNode(literal_0069aee0);
 case 0x5e: return GetHashNameNode(literal_0069add8);
 case 0x7c: return GetHashNameNode(literal_0069ade8);
 case 0x7e: return GetHashNameNode(literal_0069adf0);
 case 0x153: return GetHashNameNode(literal_0069ad98);
 case 0x155: return GetHashNameNode(literal_0069ad90);
 case 0x16a: return GetHashNameNode(literal_0069ae20);
 case 0x16b: return GetHashNameNode(literal_0069ae28);
 case 0x16c: return GetHashNameNode(literal_0069ae30);
 case 0x16d: return GetHashNameNode(literal_0069ae10);
 case 0x16e: return GetHashNameNode(literal_0069ae18);
 case 0x16f: return GetHashNameNode(literal_0069ae70);
 case 0x170: return GetHashNameNode(literal_0069ae78);
 case 0x171: return GetHashNameNode(literal_0069ae40);
 case 0x172: return GetHashNameNode(literal_0069ae38);
 case 0x173: return GetHashNameNode(literal_0069ae48);
 case 0x174: return GetHashNameNode(literal_0069aea8);
 case 0x175: return GetHashNameNode(literal_0069aea0);
 case 0x176: return GetHashNameNode(literal_0069ae80);
 case 0x177: return GetHashNameNode(literal_0069ae88);
 case 0x178: return GetHashNameNode(literal_0069ae90);
 case 0x179: return GetHashNameNode(literal_0069ae98);
 case 0x17a: return GetHashNameNode(literal_0069ae50);
 case 0x17b: return GetHashNameNode(literal_0069ae58);
 case 0x17c: return GetHashNameNode(literal_0069aeb0);
 case 0x17d: return GetHashNameNode(literal_0069aeb8);
 case 0x17e: return GetHashNameNode(literal_0069aed0);
 case 0x181: return GetHashNameNode(literal_0069aec8);
 case 0x183: return GetHashNameNode(literal_0069ae60);
 case 0x184: return GetHashNameNode(literal_0069ae68);
 case 0x192: return GetHashNameNode(literal_0069ada0);
 case 0x193: return GetHashNameNode(literal_0069ada8);
 }
 return 0;
}

char * CMangler_GetOperator(int param_1)
{
 const char *p=(char *)(param_1+10);
 if(param_1==assignment_operator_name)return literal_0069aef8;
 if(memcmp(p,literal_0069ad90,5)==0)return literal_0069aee8;
 if(memcmp(p,literal_0069ad98,5)==0)return literal_0069af04;
 if(memcmp(p,literal_0069ada0,6)==0)return literal_0069af14;
 if(memcmp(p,literal_0069ada8,6)==0)return literal_0069af24;
 if(memcmp(p,literal_0069adb0,5)==0)return literal_0069af38;
 if(memcmp(p,literal_0069adb8,5)==0)return literal_0069af44;
 if(memcmp(p,literal_0069adc0,5)==0)return literal_0069af50;
 if(memcmp(p,literal_0069adc8,5)==0)return literal_0069af5c;
 if(memcmp(p,literal_0069add0,5)==0)return literal_0069af68;
 if(memcmp(p,literal_0069add8,5)==0)return literal_0069af74;
 if(memcmp(p,literal_0069ade0,5)==0)return literal_0069af80;
 if(memcmp(p,literal_0069ade8,5)==0)return literal_0069af8c;
 if(memcmp(p,literal_0069adf0,5)==0)return literal_0069af98;
 if(memcmp(p,literal_0069adf8,5)==0)return literal_0069afa4;
 if(memcmp(p,literal_0069ae00,5)==0)return literal_0069afb0;
 if(memcmp(p,literal_0069ae08,5)==0)return literal_0069afbc;
 if(memcmp(p,literal_0069ae10,6)==0)return literal_0069afc8;
 if(memcmp(p,literal_0069ae18,6)==0)return literal_0069afd4;
 if(memcmp(p,literal_0069ae20,6)==0)return literal_0069afe0;
 if(memcmp(p,literal_0069ae28,6)==0)return literal_0069afec;
 if(memcmp(p,literal_0069ae30,6)==0)return literal_0069aff8;
 if(memcmp(p,literal_0069ae38,6)==0)return literal_0069b004;
 if(memcmp(p,literal_0069ae40,6)==0)return literal_0069b010;
 if(memcmp(p,literal_0069ae48,6)==0)return literal_0069b01c;
 if(memcmp(p,literal_0069ae50,5)==0)return literal_0069b028;
 if(memcmp(p,literal_0069ae58,5)==0)return literal_0069b034;
 if(memcmp(p,literal_0069ae70,6)==0)return literal_0069b040;
 if(memcmp(p,literal_0069ae78,6)==0)return literal_0069b04c;
 if(memcmp(p,literal_0069ae80,5)==0)return literal_0069b058;
 if(memcmp(p,literal_0069ae88,5)==0)return literal_0069b064;
 if(memcmp(p,literal_0069ae90,5)==0)return literal_0069b070;
 if(memcmp(p,literal_0069ae98,5)==0)return literal_0069b07c;
 if(memcmp(p,literal_0069aea0,5)==0)return literal_0069b088;
 if(memcmp(p,literal_0069aea8,5)==0)return literal_0069b094;
 if(memcmp(p,literal_0069aeb0,5)==0)return literal_0069b0a0;
 if(memcmp(p,literal_0069aeb8,5)==0)return literal_0069b0ac;
 if(memcmp(p,literal_0069aec0,5)==0)return literal_0069b0b8;
 if(memcmp(p,literal_0069aec8,5)==0)return literal_0069b0c4;
 if(memcmp(p,literal_0069aed0,5)==0)return literal_0069af50;
 if(memcmp(p,literal_0069aed8,5)==0)return literal_0069b0d0;
 if(memcmp(p,literal_0069aee0,5)==0)return literal_0069b0dc;
 return 0;
}

void CMangler_Setup(void)
{
  constructor_name = GetHashNameNode((const char *)(literal_0069b0e8));
  destructor_name = GetHashNameNode((const char *)(literal_0069b0f0));
  assignment_operator_name = GetHashNameNode((const char *)(literal_0069b0f8));
  return;
}
