/* Native GC3 CException.cpp: explicit packed32-bit address conversions. */
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef byte undefined1;
typedef ushort undefined2;
typedef uint undefined4;
typedef byte undefined;
typedef byte bool;
#pragma pack(push, 2)
typedef struct NativeStatement
{
  uint words[8];
  ushort tail;
} NativeStatement;
#pragma pack(pop)
static byte cexcept_hasunknown;
static byte cexcept_hasrethrow;
static byte cexcept_hasthrow;
static byte cexcept_canthrow;
static byte cexcept_serialize;
static byte cexcept_hastrycatch;
static byte cexcept_expandtrycatch;
static uint *cexcept_eaafter;
static uint *cexcept_eabefore;
static uint *cexcept_prevstmt;
static uint *cexcept_dtortemps;
static uint *cexcept_uniqueobjs;
static char cexcept_filename[] = "CException.cpp";
static char cexcept_magic_name[] = "__exception_magic";
static char cexcept_offset_format[] = "%ld!";
static char cexcept_local_format[] = "__%08lx__local__";
static char cexcept_file_marker[] = "__file__";
static char cexcept_namespace_separator[] = "::";
extern byte DAT_006771c8[];
extern byte DAT_006771d6[];
extern byte DAT_00699c24[];
extern byte DAT_00699c44[];
extern byte DAT_00699c6c[];
extern uint **DAT_0070bc20;
extern uint DAT_0070bc24;
extern byte DAT_0070f1a8;
extern byte DAT_0070f1b3;
extern byte DAT_0070f1df;
extern byte DAT_0070f1e0;
extern byte DAT_0070f214;
extern byte DAT_0070f21e;
extern uint DAT_00710340;
extern uint *DAT_00710360;
extern uint DAT_00710858;
extern uint DAT_00710928;
extern uint *DAT_00710b30;
extern uint DAT_00711b00;
extern uint DAT_00711b1c;
extern uint DAT_00711b80;
extern uint *DAT_00711bac;
extern uint DAT_00711bb8;
extern uint DAT_00711be0;
extern uint DAT_00715c58;
extern uint DAT_00716c98;
extern uint DAT_00716c9c;
extern uint DAT_00716cd8;
extern uint DAT_00716d68;
extern byte DAT_0071726c[];
extern short DAT_00717466;
extern byte DAT_00725d96[];
extern byte DAT_00725e5d;
extern byte DAT_00725ed8;
void fn_0049c710(void);
undefined1 fn_0049c7a0(void);
undefined1 fn_0049c920(int param_1);
undefined1 fn_0049c9e0(int param_1);
void CExcept_CanThrowCheckCB(char *param_1);
undefined1 CExcept_CanThrowException(int param_1, char param_2);
undefined1 CExcept_SetupNoThrowFunction(uint param_1);
void CExcept_ExceptionTansform(undefined4 param_1);
void CExcept_InsertSpecificationActions(int *param_1, undefined4 *param_2);
void CExcept_TempTransform(undefined4 *param_1);
void CExcept_GenerateCatchTypeIDs(undefined4 *param_1);
void CExcept_DtorTransform(undefined4 *param_1, char param_2, char param_3);
int CExcept_CleanupExceptionActions(int param_1);
undefined1 *CExcept_TempTransExpr(undefined1 *param_1);
undefined1 *CExcept_TempTransExprCond(undefined1 *param_1);
undefined1 *CExcept_TempTransFuncCall(undefined1 *param_1, char param_2);
int CExcept_TransInitTryCatch(int param_1, char param_2);
uint CExcept_TransNewException(char *param_1, char param_2);
undefined1 *CExcept_TempTrans_ETEMP(undefined1 *param_1);
void CExcept_ScanTryBlock(undefined4 param_1, char param_2);
uint fn_0049eb00(int param_1, undefined4 param_2);
void CExcept_PatchDObjStack(int *param_1, int *param_2, int *param_3, undefined4 *param_4);
uint CExcept_ParseThrowExpression(void);
uint CExcept_ThrowExpression(int param_1);
void CExcept_SyncNoThrowUsage(uint type1, uint qualifiers1, uint type2, uint qualifiers2);
void CExcept_ScanExceptionSpecification(int param_1);
int CExcept_GetTypeID(char *param_1, undefined4 param_2, char param_3);
undefined4 *CExcept_GetBaseClassList(undefined4 *param_1, undefined4 param_2, int param_3, int param_4, char param_5, char param_6);
void CExcept_MakeBaseClassListAmbig(undefined4 *param_1, int param_2);
void CExcept_MangleClass(int param_1);
void CExcept_MangleNameSpaceName(undefined4 *param_1);
uint CExcept_ActionCleanup(uint *action, uint statement);
void CExcept_RegisterMemberArray(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6);
void CExcept_RegisterMember(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, int param_5, char param_6);
void CExcept_PatchConstructorAction(undefined4 *param_1, undefined4 *param_2);
void CExcept_RegisterDeleteObject(undefined4 param_1, undefined4 param_2);
void CExcept_RegisterVLA(int param_1, int param_2, undefined4 param_3);
void CExcept_RegisterLocalArray(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);
void CExcept_RegisterLocalObject(undefined4 param_1, undefined1 param_2);
undefined4 CExcept_RegisterDestructorObject(undefined4 param_1, int param_2, undefined4 param_3);
undefined1 CExcept_ActionNeedsDestruction(int param_1);
int CExcept_IsSubList(undefined4 *param_1, undefined4 *param_2);
bool CExcept_ActionCompare(int param_1, int param_2);
bool CExcept_IsCompatibleSpecificationList(undefined4 *param_1, undefined4 *param_2);
void CExcept_CompareSpecifications(undefined4 *param_1, undefined4 *param_2);
undefined4 fn_004a06d0(int param_1);
void CExcept_CheckStackRefs(undefined4 *param_1);
void CExcept_Setup(void);
extern uint AppendGListByte();
extern uint CABI_DestroyObject();
extern uint CABI_GetDestructorObject();
extern uint CABI_GetSizeTType();
extern uint CClass_Destructor();
extern uint CClass_FindVirtualBase();
extern uint CClass_IsDestructor();
extern uint CDecl_NewPointerType();
extern uint CDecl_ParseDeclarator();
extern uint CError_Internal();
extern uint CError_Warning();
extern uint CFunc_AppendStatement();
extern uint CFunc_InsertAfterStatement();
extern uint CFunc_ParseScopedStatement();
extern uint CMachine_FunctionRequiresMemoryReturn();
extern uint CMangler_MangleType();
extern uint COptimizer_GetFunctionObject();
extern uint CParser_GetDeclSpecs();
extern uint CParser_NewLocalDataObject();
extern uint CPrep_UpdateTokenLine();
extern uint CTemplateTools_IsDependentType();
extern uint CanAllocObject();
extern uint CompilerTools_AllocatePool();
extern uint GetHashNameNode();
extern uint create_objectrefnode();
extern uint create_temp_object();
extern uint fn_00420190();
extern uint fn_00447b70();
extern uint fn_0044dfb0();
extern uint fn_00452fe0();
extern uint fn_00453430();
extern uint fn_00455d00();
extern uint fn_0045a1e0();
extern uint fn_0045a490();
extern uint fn_0045c480();
extern uint fn_0046d530();
extern uint fn_00479c20();
extern uint fn_0047b230();
extern uint fn_004ea740();
extern uint fn_004eb140();
extern uint fn_005153b0();
extern uint fn_00520530();
extern uint fn_00521c20();
extern uint fn_00524320();
extern uint fn_00524350();
extern uint fn_005243b0();
extern uint fn_0052ec00();
extern uint fn_0052ec70();
extern uint fn_0052ee40();
extern uint fn_0052ef10();
extern uint fn_0052f930();
extern uint fn_0053d470();
extern uint fn_00542350();
extern uint fn_00543680();
extern uint fn_00544fc0();
extern uint fn_005480b0();
extern uint fn_005547e0();
extern uint fn_00559da0();
extern uint fn_0055b7f0();
extern uint fn_0055b9f0();
extern uint fn_0055bc20();
extern uint fn_00593320();
extern uint fn_005a12c0();
extern uint fn_005a1310();
extern uint fn_005a1740();
extern uint fn_005a1760();
extern uint fn_005a1780();
extern uint fn_005a6b30();
extern uint fn_005a8e20();
extern uint funccallexpr();
extern uint galloc();
extern uint intconstnode();
extern uint iscpp_typeequal();
extern uint makediadicnode();
extern uint makemonadicnode();
extern uint memclrw();
extern uint memcpy();
extern uint newlabel();
extern uint nullnode();
extern uint sprintf();
void fn_0049c710(void)
{
  undefined4 *puVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  if (DAT_0070f1df == '\0')
  {
    return;
  }
  iVar4 = (int) fn_0044dfb0();
  do
  {
    fn_005a1740();
    bVar2 = (bool) 0;
    for (puVar1 = (undefined4 *) DAT_00711bac; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      if ((*((char *) (((int) puVar1) + 0x1e))) == '\0')
      {
        uVar5 = (uint) fn_0044dfb0();
        if ((iVar4 + 0x3cU) < uVar5)
        {
          iVar4 = (int) fn_0044dfb0();
          iVar6 = (int) fn_00420190(*DAT_00710360);
          if (iVar6 != 0)
          {
            fn_0045a1e0();
          }
        }
        cVar3 = (char) fn_0049c9e0((int) puVar1);
        if (cVar3 != '\0')
        {
          bVar2 = (bool) 1;
        }
      }
    }

    cVar3 = (char) fn_0049c7a0();
    if (cVar3 != '\0')
    {
      bVar2 = (bool) 1;
    }
  }
  while (bVar2);
  return;
}

undefined1 fn_0049c7a0(void)
{
  undefined4 *puVar1;
  char *pcVar2;
  int *piVar3;
  bool bVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined1 uVar9;
  int *local_44[14];
  iVar6 = (int) fn_0044dfb0();
  do
  {
    fn_005a1760();
    bVar4 = (bool) 0;
    for (puVar1 = (undefined4 *) DAT_00711bac; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      if ((*((char *) (((int) puVar1) + 0x1e))) == '\0')
      {
        uVar7 = (uint) fn_0044dfb0();
        if ((iVar6 + 0x3cU) < uVar7)
        {
          iVar6 = (int) fn_0044dfb0();
          iVar8 = (int) fn_00420190(*DAT_00710360);
          if (iVar8 != 0)
          {
            fn_0045a1e0();
          }
        }
        cVar5 = (char) fn_0049c920((int) puVar1);
        if (cVar5 != '\0')
        {
          bVar4 = (bool) 1;
        }
      }
    }

  }
  while (bVar4);
  uVar9 = (undefined1) 0;
  for (puVar1 = (undefined4 *) DAT_00711bac; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    if (((((*((char *) (puVar1 + 7))) == '\x01') && ((cVar5 = (char) fn_005a1780(puVar1), cVar5 != '\0'))) && (puVar1[2] != 0)) && ((pcVar2 = (char *) (*((char **) (puVar1[2] + 0x10))), ((*pcVar2) == '\a') && (((*((uint *) (pcVar2 + 0x16))) & 0x400) == 0))))
    {
      if (((*((byte *) (((int) puVar1) + 0x1f))) & 7) == 0)
      {
        *((uint *) (pcVar2 + 0x16)) = (uint) ((*((uint *) (pcVar2 + 0x16))) | 0x400);
        uVar9 = (undefined1) 1;
        fn_005a1310(local_44, puVar1);
        bVar4 = (bool) 0;
        for (piVar3 = (int *) local_44[0]; ((uint) piVar3) != ((uint) ((int *) 0x0)); piVar3 = (int *) ((int *) (*piVar3)))
        {
          if ((*((int *) (((int) piVar3) + 0x12))) != 0)
          {
            *((undefined4 *) (((int) piVar3) + 0x12)) = (undefined4) 0;
            bVar4 = (bool) 1;
          }
          switch ((char) piVar3[1])
          {
            case '\f':

            case '\r':

            case '\x0e':
              *((undefined1 *) (piVar3 + 1)) = (undefined1) 1;
              bVar4 = (bool) 1;

          }

        }

        if (bVar4)
        {
          fn_00593320(puVar1[2], local_44[0]);
          fn_005a12c0(puVar1, local_44);
        }
        fn_00479c20();
      }
      else
        if ((((*((int *) (pcVar2 + 10))) != 0) && ((*((int *) ((*((int *) (pcVar2 + 10))) + 4))) == 0)) && (((*((byte *) (((int) puVar1) + 0x1f))) & 6) == 0))
      {
        *((uint *) (pcVar2 + 0x16)) = (uint) ((*((uint *) (pcVar2 + 0x16))) | 0x400);
        uVar9 = (undefined1) 1;
      }
    }
  }

  return (undefined1) uVar9;
}

undefined1 fn_0049c920(int param_1)
{
  undefined4 *puVar1;
  int iVar2;
  char *pcVar3;
  char cVar4;
  byte bVar5;
  undefined1 local_9;
  if ((*((char *) (param_1 + 0x1e))) != '\0')
  {
    return (undefined1) 0;
  }
  *((undefined1 *) (param_1 + 0x1e)) = (undefined1) 1;
  local_9 = (undefined1) 0;
  if ((*((char *) (param_1 + 0x1c))) == '\x01')
  {
    for (puVar1 = (undefined4 *) (*((undefined4 **) (param_1 + 0x10))); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      if (((*((char *) (puVar1[1] + 0x1c))) == '\x01') && ((cVar4 = (char) fn_0049c920((int) puVar1[1]), cVar4 != '\0')))
      {
        local_9 = (undefined1) 1;
      }
    }

    for (puVar1 = (undefined4 *) (*((undefined4 **) (param_1 + 0x10))); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      iVar2 = (int) puVar1[1];
      if (((((*((char *) (iVar2 + 0x1c))) == '\x01') && (puVar1[2] != 0)) && ((*((int *) (iVar2 + 8))) != 0)) && ((pcVar3 = (char *) (*((char **) ((*((int *) (iVar2 + 8))) + 0x10))), (((*pcVar3) == '\a') && (((*((uint *) (pcVar3 + 0x16))) & 0x400) == 0)) && ((bVar5 = (byte) ((*((byte *) (iVar2 + 0x1f))) & 7), (bVar5 != 0) && ((*((byte *) (param_1 + 0x1f))) != (bVar5 | (*((byte *) (param_1 + 0x1f))))))))))
      {
        *((byte *) (param_1 + 0x1f)) = (byte) ((*((byte *) (param_1 + 0x1f))) | bVar5);
        local_9 = (undefined1) 1;
      }
    }

  }
  return (undefined1) local_9;
}

undefined1 fn_0049c9e0(int param_1)
{
  uint *puVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  bool bVar5;
  char cVar6;
  undefined1 uVar7;
  undefined4 *local_44[14];
  if ((*((char *) (param_1 + 0x1e))) != '\0')
  {
    return (undefined1) 0;
  }
  *((undefined1 *) (param_1 + 0x1e)) = (undefined1) 1;
  uVar7 = (undefined1) 0;
  if ((*((char *) (param_1 + 0x1c))) == '\x01')
  {
    uVar7 = (undefined1) 0;
    for (puVar2 = (undefined4 *) (*((undefined4 **) (param_1 + 0x10))); ((uint) puVar2) != ((uint) ((undefined4 *) 0x0)); puVar2 = (undefined4 *) ((undefined4 *) (*puVar2)))
    {
      if (((*((char *) (puVar2[1] + 0x1c))) == '\x01') && ((cVar6 = (char) fn_0049c9e0((int) puVar2[1]), cVar6 != '\0')))
      {
        uVar7 = (undefined1) 1;
      }
    }

    cVar6 = (char) fn_005a1780(param_1);
    if (cVar6 == '\0')
    {
      iVar4 = (int) (*((int *) (param_1 + 8)));
      if ((((iVar4 != 0) && ((*(*((char **) (iVar4 + 0x10)))) == '\a')) && (((*((uint *) ((*((char **) (iVar4 + 0x10))) + 0x16))) & 0x400) == 0)) && ((iVar4 != DAT_00716d68) && (iVar4 != DAT_00716cd8)))
      {
        *((byte *) (param_1 + 0x1f)) = (byte) ((*((byte *) (param_1 + 0x1f))) | 4);
      }
    }
    else
      if ((((*((int *) (param_1 + 8))) != 0) && ((pcVar3 = (char *) (*((char **) ((*((int *) (param_1 + 8))) + 0x10))), (*pcVar3) == '\a'))) && (((*((uint *) (pcVar3 + 0x16))) & 0x400) == 0))
    {
      fn_005a1310(local_44, param_1);
      cexcept_canthrow = (byte) '\0';
      cexcept_hasthrow = (byte) '\0';
      cexcept_hasrethrow = (byte) '\0';
      cexcept_hasunknown = (byte) '\0';
      fn_0055bc20(local_44[0], CExcept_CanThrowCheckCB);
      if (cexcept_hasthrow != '\0')
      {
        *((byte *) (param_1 + 0x1f)) = (byte) ((*((byte *) (param_1 + 0x1f))) | 1);
      }
      if (cexcept_hasrethrow != '\0')
      {
        *((byte *) (param_1 + 0x1f)) = (byte) ((*((byte *) (param_1 + 0x1f))) | 2);
      }
      if (cexcept_hasunknown != '\0')
      {
        *((byte *) (param_1 + 0x1f)) = (byte) ((*((byte *) (param_1 + 0x1f))) | 4);
      }
      if (cexcept_canthrow == '\0')
      {
        puVar1 = (uint *) ((uint *) ((*((int *) ((*((int *) (param_1 + 8))) + 0x10))) + 0x16));
        *puVar1 = (uint) ((*puVar1) | 0x400);
        bVar5 = (bool) 0;
        for (puVar2 = (undefined4 *) local_44[0]; ((uint) puVar2) != ((uint) ((undefined4 *) 0x0)); puVar2 = (undefined4 *) ((undefined4 *) (*puVar2)))
        {
          if ((*((int *) (((int) puVar2) + 0x12))) != 0)
          {
            *((undefined4 *) (((int) puVar2) + 0x12)) = (undefined4) 0;
            bVar5 = (bool) 1;
          }
          switch (*((undefined1 *) (puVar2 + 1)))
          {
            case 0xc:

            case 0xd:

            case 0xe:
              *((undefined1 *) (puVar2 + 1)) = (undefined1) 1;
              bVar5 = (bool) 1;

          }

        }

        if (bVar5)
        {
          fn_00593320(*((undefined4 *) (param_1 + 8)), local_44[0]);
          fn_005a12c0(param_1, local_44);
        }
        uVar7 = (undefined1) 1;
      }
      fn_00479c20();
    }
  }
  return (undefined1) uVar7;
}

void CExcept_CanThrowCheckCB(char *param_1)
{
  uint *puVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  if (((byte) ((*param_1) - 0x39U)) > 1)
  {
    return;
  }
  if ((*(*((char **) (param_1 + 0x10)))) != ';')
  {
    cexcept_hasunknown = (byte) 1;
    cexcept_canthrow = (byte) 1;
    return;
  }
  iVar2 = (int) (*((int *) ((*((char **) (param_1 + 0x10))) + 0x10)));
  if (((*((char *) (iVar2 + 2))) == '\x04') && (((*((uint *) (param_1 + 8))) & 8) == 0))
  {
    cexcept_hasunknown = (byte) 1;
    cexcept_canthrow = (byte) 1;
    return;
  }
  if ((DAT_0070f1df != '\0') && ((*(*((char **) (iVar2 + 0x10)))) == '\a'))
  {
    if (((*((uint *) ((*((char **) (iVar2 + 0x10))) + 0x16))) & 0x400) != 0)
    {
      bVar4 = (bool) 0;
      goto LAB_0049cce2;
    }
    if ((((*((uint *) (iVar2 + 0x14))) & 0x80000) == 0) && (DAT_0070f1e0 != '\0'))
    {
      if ((((iVar2 == DAT_00716d68) || (((iVar2 == DAT_00710340) || (iVar2 == DAT_00710928)) || (iVar2 == DAT_00711bb8))) || (((iVar2 == DAT_00715c58) || (iVar2 == DAT_00710858)) || (iVar2 == DAT_00711b80))) || (((iVar2 == DAT_00711b00) || (iVar2 == DAT_00711b1c)) || (iVar2 == DAT_00716c98)))
      {
        bVar4 = (bool) 0;
      }
      else
      {
        puVar1 = (uint *) ((uint *) ((*((int *) (iVar2 + 0x10))) + 0x16));
        *puVar1 = (uint) ((*puVar1) | 0x400);
        bVar4 = (bool) 1;
      }
      if (bVar4)
      {
        bVar4 = (bool) 0;
        goto LAB_0049cce2;
      }
    }
  }
  bVar4 = (bool) 1;
  LAB_0049cce2:
  if (bVar4)
  {
    cexcept_canthrow = (byte) 1;
  }

  if (iVar2 == DAT_00716d68)
  {
    piVar3 = (int *) (*((int **) (param_1 + 0x14)));
    if ((((((uint) piVar3) == ((uint) ((int *) 0x0))) || ((*((char *) piVar3[1])) != '4')) || ((*piVar3) == 0)) || ((*(*((char **) ((*piVar3) + 4)))) != '4'))
    {
      cexcept_hasthrow = (byte) 1;
    }
    else
    {
      cexcept_hasrethrow = (byte) 1;
    }
  }
  return;
}

undefined1 CExcept_CanThrowException(int param_1, char param_2)
{
  uint *puVar1;
  bool bVar2;
  if (DAT_0070f1df == '\0')
  {
    return (undefined1) 1;
  }
  if ((*(*((char **) (param_1 + 0x10)))) != '\a')
  {
    return (undefined1) 1;
  }
  if (param_2 != '\0')
  {
    return (undefined1) 1;
  }
  if (((*((uint *) ((*((char **) (param_1 + 0x10))) + 0x16))) & 0x400) != 0)
  {
    return (undefined1) 0;
  }
  if ((((*((uint *) (param_1 + 0x14))) & 0x80000) == 0) && (DAT_0070f1e0 != '\0'))
  {
    if (((param_1 == DAT_00716d68) || ((((param_1 == DAT_00710340) || (param_1 == DAT_00710928)) || (param_1 == DAT_00711bb8)) || ((param_1 == DAT_00715c58) || (param_1 == DAT_00710858)))) || ((param_1 == DAT_00711b80) || (((param_1 == DAT_00711b00) || (param_1 == DAT_00711b1c)) || (param_1 == DAT_00716c98))))
    {
      bVar2 = (bool) 0;
    }
    else
    {
      puVar1 = (uint *) ((uint *) ((*((int *) (param_1 + 0x10))) + 0x16));
      *puVar1 = (uint) ((*puVar1) | 0x400);
      bVar2 = (bool) 1;
    }
    if (bVar2)
    {
      return (undefined1) 0;
    }
  }
  return (undefined1) 1;
}

undefined1 CExcept_SetupNoThrowFunction(uint param_1)
{
  uint *puVar1;
  if ((*(*((char **) (param_1 + 0x10)))) != '\a')
  {
    CError_Internal(cexcept_filename, 0xdfa);
  }
  if ((((((param_1 != DAT_00716d68) && (param_1 != DAT_00710340)) && (param_1 != DAT_00710928)) && ((param_1 != DAT_00711bb8) && (param_1 != DAT_00715c58))) && ((param_1 != DAT_00710858) && ((param_1 != DAT_00711b80) && (param_1 != DAT_00711b00)))) && ((param_1 != DAT_00711b1c) && (param_1 != DAT_00716c98)))
  {
    puVar1 = (uint *) ((uint *) ((*((int *) (param_1 + 0x10))) + 0x16));
    *puVar1 = (uint) ((*puVar1) | 0x400);
    return (undefined1) 1;
  }
  return (undefined1) 0;
}

void CExcept_ExceptionTansform(undefined4 param_1)
{
  uint *puVar1;
  int iVar2;
  cexcept_uniqueobjs = (uint *) 0;
  CExcept_TempTransform((undefined4 *) param_1);
  if (DAT_00716c9c != 0)
  {
    if ((*(*((char **) (DAT_00716c9c + 0x10)))) != '\a')
    {
      CError_Internal(cexcept_filename, 0xd68);
    }
    cexcept_canthrow = (byte) '\0';
    cexcept_hasthrow = (byte) 0;
    cexcept_hasrethrow = (byte) 0;
    cexcept_hasunknown = (byte) 0;
    fn_0055bc20(param_1, CExcept_CanThrowCheckCB);
    if (cexcept_canthrow == '\0')
    {
      puVar1 = (uint *) ((uint *) ((*((int *) (DAT_00716c9c + 0x10))) + 0x16));
      *puVar1 = (uint) ((*puVar1) | 0x400);
    }
    else
    {
      iVar2 = (int) (*((int *) ((*((int *) (DAT_00716c9c + 0x10))) + 10)));
      if ((iVar2 != 0) && (DAT_0070f21e != '\0'))
      {
        CExcept_InsertSpecificationActions((int *) param_1, (undefined4 *) iVar2);
      }
    }
  }
  return;
}

void CExcept_InsertSpecificationActions(int *param_1, undefined4 *param_2)
{
  int *piVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  char *pcVar8;
  int *piVar9;
  int iVar10;
  iVar4 = (int) CompilerTools_AllocatePool(0x1e);
  memclrw(iVar4, 0x1e);
  *((undefined1 *) (iVar4 + 0x1c)) = (undefined1) 0xf;
  piVar1 = (int *) param_1;
  do
  {
    if (((uint) piVar1) == ((uint) ((int *) 0x0)))
    {
      iVar5 = (int) (*param_1);
      while (iVar5 != 0)
      {
        param_1 = (int *) ((int *) (*param_1));
        iVar5 = (int) (*param_1);
      }

      if ((((char) param_1[1]) != '\x03') && (((char) param_1[1]) != '\b'))
      {
        param_1 = (int *) ((int *) CFunc_InsertAfterStatement(8, param_1));
        *((undefined4 *) (((int) param_1) + 10)) = (undefined4) 0;
        *((undefined4 *) (((int) param_1) + 0x12)) = (undefined4) 0;
        if ((((uint) (*((undefined4 **) ((*((int *) (DAT_00716c9c + 0x10))) + 0xe)))) != ((uint) (&DAT_00725d96))) && ((DAT_0070f214 != '\0') || (DAT_0070f1a8 != '\0')))
        {
          CError_Warning(0x27c8);
        }
      }
      iVar5 = (int) CFunc_InsertAfterStatement(2, param_1);
      uVar6 = (undefined4) newlabel();
      *((undefined4 *) (iVar5 + 0xe)) = (undefined4) uVar6;
      *((int *) ((*((int *) (iVar5 + 0xe))) + 4)) = (int) iVar5;
      *((undefined1 *) (iVar5 + 6)) = (undefined1) 1;
      *((undefined4 *) (iVar5 + 0x12)) = (undefined4) 0;
      uVar6 = (undefined4) create_temp_object(&DAT_0071726c);
      if (param_2[1] == 0)
      {
        param_2 = (undefined4 *) ((undefined4 *) 0x0);
      }
      iVar10 = (int) 0;
      for (puVar2 = (undefined4 *) param_2; ((uint) puVar2) != ((uint) ((undefined4 *) 0x0)); puVar2 = (undefined4 *) ((undefined4 *) (*puVar2)))
      {
        iVar10 = (int) (iVar10 + 1);
      }

      *((int *) (iVar4 + 4)) = (int) iVar10;
      uVar7 = (undefined4) galloc(iVar10 * 4);
      *((undefined4 *) (iVar4 + 8)) = (undefined4) uVar7;
      *((undefined4 *) (iVar4 + 0xc)) = (undefined4) (*((undefined4 *) (iVar5 + 0xe)));
      *((undefined4 *) (iVar4 + 0x10)) = (undefined4) uVar6;
      iVar10 = (int) 0;
      for (; ((uint) param_2) != ((uint) ((undefined4 *) 0x0)); param_2 = (undefined4 *) ((undefined4 *) (*param_2)))
      {
        pcVar8 = (char *) ((char *) CExcept_GetTypeID((char *) param_2[1], (undefined4) param_2[2], (char) 0));
        if ((*pcVar8) != '7')
        {
          CError_Internal(cexcept_filename, 0x548);
        }
        uVar7 = (undefined4) fn_0052f930(*((undefined4 *) (pcVar8 + 0x14)), *((undefined4 *) (pcVar8 + 0x10)), 0, 0);
        *((undefined4 *) ((*((int *) (iVar4 + 8))) + (iVar10 * 4))) = (undefined4) uVar7;
        iVar10 = (int) (iVar10 + 1);
      }

      iVar4 = (int) CFunc_InsertAfterStatement(4, iVar5);
      uVar7 = (undefined4) fn_00521c20(uVar6, 1);
      uVar7 = (undefined4) funccallexpr(DAT_00716cd8, uVar7, 0, 0, 0);
      *((undefined4 *) (iVar4 + 10)) = (undefined4) uVar7;
      iVar5 = (int) CompilerTools_AllocatePool(0x1e);
      memclrw(iVar5, 0x1e);
      *((undefined1 *) (iVar5 + 0x1c)) = (undefined1) 0xe;
      *((undefined4 *) (iVar5 + 4)) = (undefined4) uVar6;
      *((undefined1 *) (iVar5 + 8)) = (undefined1) 1;
      *((int *) (iVar4 + 0x12)) = (int) iVar5;
      iVar4 = (int) CFunc_InsertAfterStatement(2, iVar4);
      uVar6 = (undefined4) newlabel();
      *((undefined4 *) (iVar4 + 0xe)) = (undefined4) uVar6;
      *((int *) ((*((int *) (iVar4 + 0xe))) + 4)) = (int) iVar4;
      *((undefined4 *) (iVar4 + 0x12)) = (undefined4) 0;
      iVar4 = (int) CFunc_InsertAfterStatement(3, iVar4);
      *((undefined4 *) (iVar4 + 0xe)) = (undefined4) uVar6;
      return;
    }
    piVar3 = (int *) (*((int **) (((int) piVar1) + 0x12)));
    if (((uint) (*((int **) (((int) piVar1) + 0x12)))) == ((uint) ((int *) 0x0)))
    {
      *((int *) (((int) piVar1) + 0x12)) = (int) iVar4;
    }
    else
    {
      do
      {
        piVar9 = (int *) piVar3;
        if (((char) piVar9[7]) == '\x0f')
          goto LAB_0049d007;
        piVar3 = (int *) ((int *) (*piVar9));
      }
      while (((uint) ((int *) (*piVar9))) != ((uint) ((int *) 0x0)));
      *piVar9 = (int) iVar4;
    }
    LAB_0049d007:
    piVar1 = (int *) ((int *) (*piVar1));

  }
  while (1);
}

void CExcept_TempTransform(undefined4 *param_1)
{
  int iVar1;
  char cVar2;
  short sVar3;
  int *piVar4;
  char *pcVar5;
  bool bVar6;
  undefined4 uVar7;
  CExcept_GenerateCatchTypeIDs((undefined4 *) param_1);
  cexcept_prevstmt = (uint *) param_1;
  do
  {
    if (((uint) param_1) == ((uint) ((undefined4 *) 0x0)))
    {
      return;
    }
    cexcept_eaafter = (uint *) (*((int **) (((int) param_1) + 0x12)));
    cexcept_eabefore = (uint *) cexcept_eaafter;
    if (((*((byte *) (((int) param_1) + 6))) & 2) == 0)
    {
      if ((*((char *) (param_1 + 1))) == '\x04')
      {
        pcVar5 = (char *) (*((char **) (((int) param_1) + 10)));
        cVar2 = (char) (*pcVar5);
        while (cVar2 == ')')
        {
          pcVar5 = (char *) (*((char **) (pcVar5 + 0x10)));
          cVar2 = (char) (*pcVar5);
        }

        if (cVar2 == '\x04')
        {
          pcVar5 = (char *) (*((char **) (pcVar5 + 0x10)));
        }
        if (((((*pcVar5) == '9') && ((iVar1 = (int) (*((int *) (((int) param_1) + 0x12))), iVar1 != 0))) && ((*((char *) (iVar1 + 0x1c))) == '\x01')) && ((piVar4 = (int *) (*((int **) (pcVar5 + 0x14))), ((uint) piVar4) != ((uint) ((int *) 0x0)))))
        {
          if ((((*(*((char **) (pcVar5 + 0x10)))) == ';') && ((cVar2 = (char) CClass_IsDestructor(*((undefined4 *) ((*((char **) (pcVar5 + 0x10))) + 0x10))), cVar2 != '\0'))) && (((*((char *) piVar4[1])) == ';') && ((*((int *) (((char *) piVar4[1]) + 0x10))) == (*((int *) (iVar1 + 4))))))
          {
            cexcept_eabefore = (uint *) ((int *) (*cexcept_eabefore));
          }
          else
            if ((*((int *) ((*((int *) (pcVar5 + 0x18))) + 0xe))) == (*((int *) ((*((int *) (iVar1 + 4))) + 0x10))))
          {
            sVar3 = (short) fn_005547e0(*((int *) (pcVar5 + 0x18)));
            if ((sVar3 == 1) && ((piVar4 = (int *) ((int *) (*piVar4)), ((uint) piVar4) == ((uint) ((int *) 0x0)))))
            {
              CError_Internal(cexcept_filename, 0xccb);
            }
            if (((*((char *) piVar4[1])) == ';') && ((*((int *) (((char *) piVar4[1]) + 0x10))) == (*((int *) (iVar1 + 4)))))
            {
              cexcept_eabefore = (uint *) ((int *) (*cexcept_eabefore));
            }
          }
        }
      }
    }
    else
    {
      if (((uint) cexcept_eaafter) == ((uint) ((int *) 0x0)))
      {
        CError_Internal(cexcept_filename, 0xcac);
      }
      cexcept_eabefore = (uint *) ((int *) (*cexcept_eabefore));
      *((byte *) (((int) param_1) + 6)) = (byte) ((*((byte *) (((int) param_1) + 6))) & 0xfd);
    }
    switch (*((undefined1 *) (param_1 + 1)))
    {
      case 4:
        bVar6 = (bool) 0;
        uVar7 = (undefined4) 1;
        goto LAB_0049d2b7;

      case 5:

      case 6:

      case 7:
        bVar6 = (bool) 1;
        uVar7 = (undefined4) 0;
        LAB_0049d2b7:
      CExcept_DtorTransform((undefined4 *) param_1, (char) uVar7, (char) bVar6);

        break;

      case 8:
        if ((*((int *) (((int) param_1) + 10))) != 0)
      {
        cVar2 = (char) CMachine_FunctionRequiresMemoryReturn(*((undefined4 *) (DAT_00716c9c + 0x10)));
        bVar6 = (bool) (cVar2 != '\x01');
        uVar7 = (undefined4) 0;
        goto LAB_0049d2b7;
      }

    }

    *((int **) (((int) param_1) + 0x12)) = (int *) cexcept_eabefore;
    cexcept_prevstmt = (uint *) param_1;
    param_1 = (undefined4 *) ((undefined4 *) (*param_1));
  }
  while (1);
}

void CExcept_GenerateCatchTypeIDs(undefined4 *param_1)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  char *pcVar6;
  undefined4 uVar7;
  for (puVar5 = (undefined4 *) param_1; ((uint) puVar5) != ((uint) ((undefined4 *) 0x0)); puVar5 = (undefined4 *) ((undefined4 *) (*puVar5)))
  {
    cexcept_prevstmt = (uint *) param_1;
    for (puVar1 = (undefined4 *) (*((undefined4 **) (((int) puVar5) + 0x12))); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      if ((((*((char *) (puVar1 + 7))) == '\r') && (puVar1[5] != 0)) && (puVar1[4] == 0))
      {
        pcVar6 = (char *) ((char *) CExcept_GetTypeID((char *) puVar1[5], (undefined4) puVar1[6], (char) 0));
        if ((*pcVar6) != '7')
        {
          CError_Internal(cexcept_filename, 0x548);
        }
        uVar7 = (undefined4) fn_0052f930(*((undefined4 *) (pcVar6 + 0x14)), *((undefined4 *) (pcVar6 + 0x10)), 0, 0);
        puVar1[4] = (undefined4) uVar7;
        iVar3 = (int) puVar1[3];
        for (puVar2 = (undefined4 *) ((undefined4 *) (*puVar5)); ((uint) puVar2) != ((uint) ((undefined4 *) 0x0)); puVar2 = (undefined4 *) ((undefined4 *) (*puVar2)))
        {
          for (puVar4 = (undefined4 *) (*((undefined4 **) (((int) puVar5) + 0x12))); ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
          {
            if (((*((char *) (puVar4 + 7))) == '\r') && (puVar4[3] == iVar3))
            {
              puVar4[4] = (undefined4) uVar7;
            }
          }

        }

      }
    }

    param_1 = (undefined4 *) cexcept_prevstmt;
  }

  cexcept_prevstmt = (uint *) param_1;
  return;
}

void CExcept_DtorTransform(undefined4 *param_1, char param_2, char param_3)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  NativeStatement saved_statement;
  uint saved_object;
  puVar2 = (undefined4 *) cexcept_prevstmt;
  cexcept_dtortemps = (uint *) 0;
  cexcept_serialize = (byte) '\0';
  cexcept_expandtrycatch = (byte) 0;
  cexcept_hastrycatch = (byte) '\0';
  uVar4 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (((int) param_1) + 10))));
  *((undefined4 *) (((int) param_1) + 10)) = (undefined4) uVar4;
  puVar8 = (undefined4 *) param_1;
  if (cexcept_hastrycatch == '\0')
  {
    LAB_0049d4fb:
    if (((uint) cexcept_dtortemps) != ((uint) 0))
    {
      if (param_2 == '\0')
      {
        if (param_3 != '\0')
        {
          iVar6 = (int) (*((int *) (((int) param_1) + 10)));
          if (((*(*((char **) (iVar6 + 4)))) == '\x06') && ((iVar5 = (int) CClass_Destructor(*((char **) (iVar6 + 4))), iVar5 != 0)))
          {
            CError_Internal(cexcept_filename, 0xc5c);
          }
          saved_object = (uint) create_temp_object(*((undefined4 *) (iVar6 + 4)));
          uVar4 = (undefined4) create_objectrefnode(saved_object);
          uVar4 = (undefined4) fn_0055b9f0(uVar4);
          uVar4 = (undefined4) makediadicnode(uVar4, iVar6, 0x1e);
          *((undefined4 *) (((int) param_1) + 10)) = (undefined4) uVar4;
        }
        saved_statement = *((NativeStatement *) param_1);
        *((undefined1 *) (param_1 + 1)) = (undefined1) 4;
        uVar4 = (undefined4) CExcept_CleanupExceptionActions((int) puVar8);
        iVar6 = (int) CFunc_InsertAfterStatement(((byte *) (&saved_statement))[4], uVar4);
        *((undefined4 *) (iVar6 + 0xe)) = (undefined4) (*((uint *) (((byte *) (&saved_statement)) + 14)));
        if (param_3 == '\0')
        {
          uVar4 = (undefined4) nullnode();
          *((undefined4 *) (iVar6 + 10)) = (undefined4) uVar4;
        }
        else
        {
          uVar4 = (undefined4) create_objectrefnode(saved_object);
          uVar4 = (undefined4) fn_0055b9f0(uVar4);
          *((undefined4 *) (iVar6 + 10)) = (undefined4) uVar4;
        }
      }
      else
      {
        CExcept_CleanupExceptionActions((int) puVar8);
      }
    }

    return;
  }
  cexcept_expandtrycatch = (byte) 1;
  puVar7 = (undefined4 *) puVar2;
  if (cexcept_serialize != '\0')
  {
    puVar1 = (undefined4 *) ((undefined4 *) (*param_1));
    *((undefined4 *) (((int) param_1) + 0x12)) = (undefined4) cexcept_eabefore;
    fn_005480b0(param_1);
    cexcept_prevstmt = (uint *) param_1;
    puVar3 = (undefined4 *) param_1;
    do
    {
      puVar8 = (undefined4 *) puVar3;
      if (((uint) puVar8) == ((uint) ((undefined4 *) 0x0)))
      {
        CError_Internal(cexcept_filename, 0xc35);
      }
      puVar3 = (undefined4 *) ((undefined4 *) (*puVar8));
      puVar7 = (undefined4 *) cexcept_prevstmt;
    }
    while (((uint) ((undefined4 *) (*puVar8))) != ((uint) puVar1));
  }
  do
  {
    cexcept_prevstmt = (uint *) puVar7;
    puVar7 = (undefined4 *) puVar2;
    if (((uint) puVar7) == ((uint) ((undefined4 *) 0x0)))
    {
      CError_Internal(cexcept_filename, 0xc3d);
    }
    switch (*((undefined1 *) (puVar7 + 1)))
    {
      case 8:
        if ((*((int *) (((int) puVar7) + 10))) == 0)
      {
        CError_Internal(cexcept_filename, 0xc41);
      }

      case 4:

      case 5:

      case 6:

      case 7:
        uVar4 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (((int) puVar7) + 10))));
        *((undefined4 *) (((int) puVar7) + 10)) = (undefined4) uVar4;

    }

    if (((uint) puVar7) == ((uint) param_1))
      goto LAB_0049d4fb;
    puVar2 = (undefined4 *) ((undefined4 *) (*puVar7));
  }
  while (1);
}

int CExcept_CleanupExceptionActions(int param_1)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int unaff_EBX;
  for (puVar1 = (undefined4 *) cexcept_dtortemps; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    if (((((uint) cexcept_eaafter) == ((uint) ((undefined4 *) 0x0))) || (((byte) ((*((char *) (cexcept_eaafter + 7))) - 1U)) > 1)) || (cexcept_eaafter[1] != puVar1[1]))
    {
      CError_Internal(cexcept_filename, 0xbf6);
    }
    else
    {
      cexcept_eaafter = (uint *) ((undefined4 *) (*cexcept_eaafter));
    }
    if (puVar1[3] != 0)
    {
      param_1 = (int) CFunc_InsertAfterStatement(7, param_1);
      uVar2 = (undefined4) create_objectrefnode(puVar1[3]);
      uVar2 = (undefined4) fn_0055b9f0(uVar2);
      *((undefined4 *) (param_1 + 10)) = (undefined4) uVar2;
      *((undefined4 **) (param_1 + 0x12)) = (undefined4 *) cexcept_eaafter;
      uVar2 = (undefined4) newlabel();
      *((undefined4 *) (param_1 + 0xe)) = (undefined4) uVar2;
      unaff_EBX = (int) (*((int *) (param_1 + 0xe)));
    }
    param_1 = (int) CFunc_InsertAfterStatement(4, param_1);
    uVar2 = (undefined4) fn_00521c20(puVar1[1], 1);
    uVar2 = (undefined4) CABI_DestroyObject(puVar1[2], uVar2, 1, 1, 0);
    *((undefined4 *) (param_1 + 10)) = (undefined4) uVar2;
    *((undefined4 **) (param_1 + 0x12)) = (undefined4 *) cexcept_eaafter;
    if (puVar1[3] != 0)
    {
      param_1 = (int) CFunc_InsertAfterStatement(2, param_1);
      *((int *) (param_1 + 0xe)) = (int) unaff_EBX;
      *((int *) (unaff_EBX + 4)) = (int) param_1;
    }
  }

  return (int) param_1;
}

undefined1 *CExcept_TempTransExpr(undefined1 *param_1)
{
  undefined4 *puVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  switch (*param_1)
  {
    case 0:

    case 1:

    case 2:

    case 3:

    case 4:

    case 5:

    case 6:

    case 7:

    case 0x32:

    case 0x33:
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar3;
      return (undefined1 *) param_1;

    default:
      CError_Internal(cexcept_filename, 0xbda);
      return (undefined1 *) param_1;

    case 9:

    case 0xb:

    case 0xc:

    case 0xf:

    case 0x10:

    case 0x11:

    case 0x12:

    case 0x13:

    case 0x14:

    case 0x15:

    case 0x16:

    case 0x17:

    case 0x18:

    case 0x19:

    case 0x1a:

    case 0x1b:

    case 0x1e:

    case 0x1f:

    case 0x20:

    case 0x21:

    case 0x22:

    case 0x23:

    case 0x24:

    case 0x25:

    case 0x26:

    case 0x27:

    case 0x28:

    case 0x2a:

    case 0x2b:

    case 0x2d:

    case 0x2e:
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar3;
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar3;
      return (undefined1 *) param_1;

    case 0x1c:

    case 0x1d:

    case 0x29:
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar3;
      uVar3 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar3;
      return (undefined1 *) param_1;

    case 0x34:

    case 0x35:

    case 0x36:

    case 0x37:

    case 0x3b:

    case 0x3d:

    case 0x3e:

    case 0x40:

    case 0x41:

    case 0x43:

    case 0x51:

    case 0x52:

    case 0x53:

    case 0x57:
      return (undefined1 *) param_1;

    case 0x38:
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar3;
      uVar3 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar3;
      uVar3 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x18))));
      *((undefined4 *) (param_1 + 0x18)) = (undefined4) uVar3;
      return (undefined1 *) param_1;

    case 0x39:

    case 0x3a:
      puVar2 = (undefined1 *) ((undefined1 *) CExcept_TempTransFuncCall((undefined1 *) param_1, (char) 0));
      return (undefined1 *) puVar2;

    case 0x3c:
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar3;
      uVar3 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar3;
      return (undefined1 *) param_1;

    case 0x3f:
      for (puVar1 = (undefined4 *) (*((undefined4 **) (param_1 + 0x14))); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) puVar1[2]);
      puVar1[2] = (undefined4) uVar3;
    }

      for (puVar1 = (undefined4 *) (*((undefined4 **) (param_1 + 0x18))); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) puVar1[2]);
      puVar1[2] = (undefined4) uVar3;
    }

      return (undefined1 *) param_1;

    case 0x42:
      if ((*((int *) (param_1 + 0x10))) != 0)
    {
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((int *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar3;
    }
      return (undefined1 *) param_1;

    case 0x44:
      puVar2 = (undefined1 *) ((undefined1 *) CExcept_TempTrans_ETEMP((undefined1 *) param_1));
      return (undefined1 *) puVar2;

    case 0x48:

    case 0x49:
      puVar2 = (undefined1 *) ((undefined1 *) CExcept_TransNewException((char *) param_1, (char) 0));
      return (undefined1 *) puVar2;

    case 0x4a:
      puVar2 = (undefined1 *) ((undefined1 *) CExcept_TransInitTryCatch((int) param_1, (char) 0));
      return (undefined1 *) puVar2;

    case 0x4b:
      if ((*((int *) (param_1 + 0x24))) != 0)
    {
      uVar3 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((int *) (param_1 + 0x24))));
      *((undefined4 *) (param_1 + 0x24)) = (undefined4) uVar3;
    }
      return (undefined1 *) param_1;

  }

}

undefined1 *CExcept_TempTransExprCond(undefined1 *param_1)
{
  undefined1 *puVar1;
  undefined4 uVar2;
  switch (*param_1)
  {
    case 0:

    case 1:

    case 2:

    case 3:

    case 4:

    case 5:

    case 6:

    case 7:

    case 0x32:

    case 0x33:
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar2;
      return (undefined1 *) param_1;

    default:
      CError_Internal(cexcept_filename, 0xb3f);
      return (undefined1 *) param_1;

    case 9:

    case 0xb:

    case 0xc:

    case 0xf:

    case 0x10:

    case 0x11:

    case 0x12:

    case 0x13:

    case 0x14:

    case 0x15:

    case 0x16:

    case 0x17:

    case 0x18:

    case 0x19:

    case 0x1a:

    case 0x1b:

    case 0x1e:

    case 0x1f:

    case 0x20:

    case 0x21:

    case 0x22:

    case 0x23:

    case 0x24:

    case 0x25:

    case 0x26:

    case 0x27:

    case 0x28:

    case 0x29:

    case 0x2a:

    case 0x2b:

    case 0x2d:

    case 0x2e:
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar2;
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar2;
      return (undefined1 *) param_1;

    case 0x1c:

    case 0x1d:
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar2;
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar2;
      return (undefined1 *) param_1;

    case 0x34:

    case 0x35:

    case 0x36:

    case 0x37:

    case 0x3b:

    case 0x3d:

    case 0x3e:

    case 0x51:

    case 0x52:

    case 0x53:

    case 0x57:
      return (undefined1 *) param_1;

    case 0x38:
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar2;
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar2;
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x18))));
      *((undefined4 *) (param_1 + 0x18)) = (undefined4) uVar2;
      return (undefined1 *) param_1;

    case 0x39:

    case 0x3a:
      puVar1 = (undefined1 *) ((undefined1 *) CExcept_TempTransFuncCall((undefined1 *) param_1, (char) 1));
      return (undefined1 *) puVar1;

    case 0x3c:
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar2;
      uVar2 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar2;
      return (undefined1 *) param_1;

    case 0x44:
      puVar1 = (undefined1 *) ((undefined1 *) CExcept_TempTrans_ETEMP((undefined1 *) param_1));
      return (undefined1 *) puVar1;

    case 0x48:

    case 0x49:
      puVar1 = (undefined1 *) ((undefined1 *) CExcept_TransNewException((char *) param_1, (char) 1));
      return (undefined1 *) puVar1;

    case 0x4a:
      puVar1 = (undefined1 *) ((undefined1 *) CExcept_TransInitTryCatch((int) param_1, (char) 1));
      return (undefined1 *) puVar1;

  }

}

undefined1 *CExcept_TempTransFuncCall(undefined1 *param_1, char param_2)
{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  char *unaff_ESI;
  int *local_14;
  local_14 = (int *) ((int *) 0x0);
  piVar4 = (int *) (*((int **) (param_1 + 0x14)));
  if (((uint) piVar4) != ((uint) ((int *) 0x0)))
  {
    unaff_ESI = (char *) ((char *) piVar4[1]);
    if ((*unaff_ESI) == 'D')
    {
      if (unaff_ESI[0x18] != '\0')
      {
        local_14 = (int *) piVar4;
      }
    }
    else
    {
      piVar1 = (int *) ((int *) (*piVar4));
      if (((((uint) piVar1) != ((uint) ((int *) 0x0))) && ((unaff_ESI = (char *) ((char *) piVar1[1]), (*unaff_ESI) == 'D'))) && (unaff_ESI[0x18] != '\0'))
      {
        local_14 = (int *) piVar1;
      }
    }
  }
  if (((uint) local_14) == ((uint) ((int *) 0x0)))
  {
    if (param_2 == '\0')
    {
      for (; ((uint) piVar4) != ((uint) ((int *) 0x0)); piVar4 = (int *) ((int *) (*piVar4)))
      {
        iVar2 = (int) CExcept_TempTransExpr((undefined1 *) piVar4[1]);
        piVar4[1] = (int) iVar2;
      }

      uVar8 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar8;
    }
    else
    {
      iVar2 = (int) 0;
      for (; ((uint) piVar4) != ((uint) ((int *) 0x0)); piVar4 = (int *) ((int *) (*piVar4)))
      {
        iVar2 = (int) (iVar2 + 1);
      }

      iVar7 = (int) CompilerTools_AllocatePool(iVar2 * 4);
      iVar2 = (int) 0;
      for (puVar5 = (undefined4 *) (*((undefined4 **) (param_1 + 0x14))); ((uint) puVar5) != ((uint) ((undefined4 *) 0x0)); puVar5 = (undefined4 *) ((undefined4 *) (*puVar5)))
      {
        *((undefined4 **) (iVar7 + (iVar2 * 4))) = (undefined4 *) puVar5;
        iVar2 = (int) (iVar2 + 1);
      }

      while (iVar2 > 0)
      {
        iVar2 = (int) (iVar2 - 1);
        uVar8 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) ((*((int *) (iVar7 + (iVar2 * 4)))) + 4))));
        *((undefined4 *) ((*((int *) (iVar7 + (iVar2 * 4)))) + 4)) = (undefined4) uVar8;
      }

      uVar8 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar8;
    }
    return (undefined1 *) param_1;
  }
  if (param_2 == '\0')
  {
    for (; ((uint) piVar4) != ((uint) ((int *) 0x0)); piVar4 = (int *) ((int *) (*piVar4)))
    {
      if (((uint) piVar4) != ((uint) local_14))
      {
        iVar2 = (int) CExcept_TempTransExpr((undefined1 *) piVar4[1]);
        piVar4[1] = (int) iVar2;
      }
    }

  }
  else
  {
    iVar2 = (int) 0;
    for (; ((uint) piVar4) != ((uint) ((int *) 0x0)); piVar4 = (int *) ((int *) (*piVar4)))
    {
      iVar2 = (int) (iVar2 + 1);
    }

    iVar7 = (int) CompilerTools_AllocatePool(iVar2 * 4);
    iVar2 = (int) 0;
    for (puVar5 = (undefined4 *) (*((undefined4 **) (param_1 + 0x14))); ((uint) puVar5) != ((uint) ((undefined4 *) 0x0)); puVar5 = (undefined4 *) ((undefined4 *) (*puVar5)))
    {
      *((undefined4 **) (iVar7 + (iVar2 * 4))) = (undefined4 *) puVar5;
      iVar2 = (int) (iVar2 + 1);
    }

    while (iVar2 > 0)
    {
      iVar2 = (int) (iVar2 - 1);
      piVar4 = (int *) (*((int **) (iVar7 + (iVar2 * 4))));
      if (((uint) piVar4) != ((uint) local_14))
      {
        uVar8 = (undefined4) CExcept_TempTransExprCond((undefined1 *) piVar4[1]);
        *((undefined4 *) ((*((int *) (iVar7 + (iVar2 * 4)))) + 4)) = (undefined4) uVar8;
      }
    }

  }
  puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x10));
  *puVar3 = (undefined4) cexcept_dtortemps;
  iVar2 = (int) (*((int *) (unaff_ESI + 0x14)));
  puVar5 = (undefined4 *) cexcept_uniqueobjs;
  cexcept_dtortemps = (uint *) puVar3;
  if (iVar2 == 0)
  {
    uVar8 = (undefined4) create_temp_object(*((undefined4 *) (unaff_ESI + 0x10)));
  }
  else
  {
    for (; ((uint) puVar5) != ((uint) ((undefined4 *) 0x0)); puVar5 = (undefined4 *) ((undefined4 *) (*puVar5)))
    {
      if (puVar5[2] == iVar2)
      {
        unaff_ESI[0x18] = (char) '\0';
        uVar8 = (undefined4) puVar5[1];
        goto LAB_0049db0e;
      }
    }

    puVar5 = (undefined4 *) ((undefined4 *) galloc(0xc));
    *puVar5 = (undefined4) cexcept_uniqueobjs;
    cexcept_uniqueobjs = (uint *) puVar5;
    puVar5[2] = (undefined4) iVar2;
    uVar8 = (undefined4) create_temp_object(*((undefined4 *) (unaff_ESI + 0x10)));
    puVar5[1] = (undefined4) uVar8;
  }
  LAB_0049db0e:
  puVar3[1] = (undefined4) uVar8;

  puVar3[3] = (undefined4) 0;
  if ((*(*((char **) (unaff_ESI + 0x10)))) == '\x06')
  {
    uVar8 = (undefined4) CClass_Destructor(*((char **) (unaff_ESI + 0x10)));
    puVar3[2] = (undefined4) uVar8;
    if (puVar3[2] != 0)
      goto LAB_0049db35;
  }
  CError_Internal(cexcept_filename, 0xa76);
  LAB_0049db35:
  *unaff_ESI = (char) ';';

  *((undefined4 *) (unaff_ESI + 0x10)) = (undefined4) puVar3[1];
  if ((param_2 == '\0') && (cexcept_serialize == '\0'))
  {
    uVar8 = (undefined4) CExcept_TempTransExpr((undefined1 *) param_1);
    piVar4 = (int *) ((int *) CFunc_InsertAfterStatement(4, cexcept_prevstmt));
    iVar2 = (int) (*piVar4);
    *((undefined4 *) (((int) piVar4) + 0x16)) = (undefined4) (*((undefined4 *) (iVar2 + 0x16)));
    *((undefined4 *) (((int) piVar4) + 0x1a)) = (undefined4) (*((undefined4 *) (iVar2 + 0x1a)));
    *((undefined4 *) (((int) piVar4) + 0x1e)) = (undefined4) (*((undefined4 *) (iVar2 + 0x1e)));
    *((undefined4 **) (((int) piVar4) + 0x12)) = (undefined4 *) cexcept_eabefore;
    *((undefined4 *) (((int) piVar4) + 10)) = (undefined4) uVar8;
    cexcept_prevstmt = (uint *) piVar4;
    puVar5 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
    *puVar5 = (undefined4) cexcept_eabefore;
    cexcept_eabefore = (uint *) puVar5;
    *((undefined1 *) (puVar5 + 7)) = (undefined1) 1;
    puVar5[1] = (undefined4) puVar3[1];
    uVar8 = (undefined4) CABI_GetDestructorObject(puVar3[2], 1);
    puVar5[2] = (undefined4) uVar8;
    puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
    puVar5 = (undefined4 *) cexcept_eabefore;
    *puVar3 = (undefined4) (*cexcept_eabefore);
    puVar3[1] = (undefined4) puVar5[1];
    puVar3[2] = (undefined4) puVar5[2];
    puVar3[3] = (undefined4) puVar5[3];
    puVar3[4] = (undefined4) puVar5[4];
    puVar3[5] = (undefined4) puVar5[5];
    puVar3[6] = (undefined4) puVar5[6];
    *((undefined2 *) (puVar3 + 7)) = (undefined2) (*((undefined2 *) (puVar5 + 7)));
    *puVar3 = (undefined4) cexcept_eaafter;
    cexcept_eaafter = (uint *) puVar3;
    puVar6 = (undefined1 *) ((undefined1 *) fn_00524350(*((undefined4 *) (((int) piVar4) + 10))));
    *puVar6 = (undefined1) 0x3b;
    *((undefined4 *) (puVar6 + 0x10)) = (undefined4) (*((undefined4 *) (local_14[1] + 0x10)));
  }
  else
  {
    uVar8 = (undefined4) (*((undefined4 *) (param_1 + 4)));
    uVar9 = (undefined4) create_temp_object(&DAT_00699c24);
    puVar3[3] = (undefined4) uVar9;
    uVar9 = (undefined4) create_objectrefnode(puVar3[3]);
    uVar9 = (undefined4) fn_0055b9f0(uVar9);
    uVar10 = (undefined4) intconstnode(&DAT_00699c24, 1);
    uVar9 = (undefined4) makediadicnode(uVar9, uVar10, 0x1e);
    uVar9 = (undefined4) makediadicnode(param_1, uVar9, 0x29);
    uVar10 = (undefined4) fn_00521c20(puVar3[1], 1);
    puVar6 = (undefined1 *) ((undefined1 *) makediadicnode(uVar9, uVar10, 0x29));
    *((undefined4 *) (puVar6 + 4)) = (undefined4) uVar8;
    piVar4 = (int *) ((int *) CFunc_InsertAfterStatement(4, cexcept_prevstmt));
    iVar2 = (int) (*piVar4);
    *((undefined4 *) (((int) piVar4) + 0x16)) = (undefined4) (*((undefined4 *) (iVar2 + 0x16)));
    *((undefined4 *) (((int) piVar4) + 0x1a)) = (undefined4) (*((undefined4 *) (iVar2 + 0x1a)));
    *((undefined4 *) (((int) piVar4) + 0x1e)) = (undefined4) (*((undefined4 *) (iVar2 + 0x1e)));
    *((undefined4 **) (((int) piVar4) + 0x12)) = (undefined4 *) cexcept_eabefore;
    uVar8 = (undefined4) create_objectrefnode(puVar3[3]);
    uVar8 = (undefined4) fn_0055b9f0(uVar8);
    uVar9 = (undefined4) intconstnode(&DAT_00699c24, 0);
    uVar8 = (undefined4) makediadicnode(uVar8, uVar9, 0x1e);
    *((undefined4 *) (((int) piVar4) + 10)) = (undefined4) uVar8;
    cexcept_prevstmt = (uint *) piVar4;
    puVar5 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
    *puVar5 = (undefined4) cexcept_eabefore;
    cexcept_eabefore = (uint *) puVar5;
    *((undefined1 *) (puVar5 + 7)) = (undefined1) 2;
    puVar5[1] = (undefined4) puVar3[1];
    uVar8 = (undefined4) CABI_GetDestructorObject(puVar3[2], 1);
    puVar5[3] = (undefined4) uVar8;
    puVar5[2] = (undefined4) puVar3[3];
    puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
    puVar5 = (undefined4 *) cexcept_eabefore;
    *puVar3 = (undefined4) (*cexcept_eabefore);
    puVar3[1] = (undefined4) puVar5[1];
    puVar3[2] = (undefined4) puVar5[2];
    puVar3[3] = (undefined4) puVar5[3];
    puVar3[4] = (undefined4) puVar5[4];
    puVar3[5] = (undefined4) puVar5[5];
    puVar3[6] = (undefined4) puVar5[6];
    *((undefined2 *) (puVar3 + 7)) = (undefined2) (*((undefined2 *) (puVar5 + 7)));
    *puVar3 = (undefined4) cexcept_eaafter;
    cexcept_eaafter = (uint *) puVar3;
  }
  return (undefined1 *) puVar6;
}

int CExcept_TransInitTryCatch(int param_1, char param_2)
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 uVar8;
  cexcept_hastrycatch = (byte) 1;
  if (param_2 != '\0')
  {
    if (cexcept_expandtrycatch != '\0')
    {
      CError_Internal(cexcept_filename, 0x9c0);
    }
    cexcept_serialize = (byte) 1;
    uVar1 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
    *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar1;
    uVar1 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
    *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar1;
    uVar1 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x18))));
    *((undefined4 *) (param_1 + 0x18)) = (undefined4) uVar1;
    uVar1 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x1c))));
    *((undefined4 *) (param_1 + 0x1c)) = (undefined4) uVar1;
    return (int) param_1;
  }
  uVar1 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
  *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar1;
  uVar1 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
  *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar1;
  uVar1 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x18))));
  *((undefined4 *) (param_1 + 0x18)) = (undefined4) uVar1;
  uVar1 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x1c))));
  *((undefined4 *) (param_1 + 0x1c)) = (undefined4) uVar1;
  if (cexcept_expandtrycatch == '\0')
  {
    return (int) param_1;
  }
  iVar2 = (int) newlabel();
  iVar3 = (int) newlabel();
  iVar4 = (int) newlabel();
  uVar1 = (undefined4) create_temp_object(&DAT_0071726c);
  piVar5 = (int *) ((int *) CFunc_InsertAfterStatement(7, cexcept_prevstmt));
  iVar7 = (int) (*piVar5);
  *((undefined4 *) (((int) piVar5) + 0x16)) = (undefined4) (*((undefined4 *) (iVar7 + 0x16)));
  *((undefined4 *) (((int) piVar5) + 0x1a)) = (undefined4) (*((undefined4 *) (iVar7 + 0x1a)));
  *((undefined4 *) (((int) piVar5) + 0x1e)) = (undefined4) (*((undefined4 *) (iVar7 + 0x1e)));
  *((undefined4 *) (((int) piVar5) + 0x12)) = (undefined4) cexcept_eabefore;
  *((undefined4 *) (((int) piVar5) + 10)) = (undefined4) (*((undefined4 *) (param_1 + 0x10)));
  *((int *) (((int) piVar5) + 0xe)) = (int) iVar4;
  puVar6 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  memclrw(puVar6, 0x1e);
  *((undefined1 *) (puVar6 + 7)) = (undefined1) 0xd;
  puVar6[3] = (undefined4) iVar3;
  puVar6[2] = (undefined4) uVar1;
  *puVar6 = (undefined4) (*((undefined4 *) (((int) piVar5) + 0x12)));
  iVar7 = (int) CFunc_InsertAfterStatement(2, piVar5);
  *((undefined1 *) (iVar7 + 6)) = (undefined1) 1;
  *((int *) (iVar7 + 0xe)) = (int) iVar2;
  *((int *) (iVar2 + 4)) = (int) iVar7;
  *((undefined4 **) (iVar7 + 0x12)) = (undefined4 *) puVar6;
  iVar7 = (int) CFunc_InsertAfterStatement(0xc, iVar7);
  uVar8 = (undefined4) fn_00521c20(uVar1, 1);
  *((undefined4 *) (iVar7 + 10)) = (undefined4) uVar8;
  iVar7 = (int) CFunc_InsertAfterStatement(4, iVar7);
  *((undefined4 *) (iVar7 + 10)) = (undefined4) (*((undefined4 *) (param_1 + 0x14)));
  iVar7 = (int) CFunc_InsertAfterStatement(3, iVar7);
  *((int *) (iVar7 + 0xe)) = (int) iVar4;
  if (((uint) (*((undefined4 **) (iVar7 + 0x12)))) != ((uint) puVar6))
  {
    CError_Internal(cexcept_filename, 0x9f3);
  }
  *((undefined4 *) (iVar7 + 0x12)) = (undefined4) (*puVar6);
  puVar6 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  memclrw(puVar6, 0x1e);
  *((undefined1 *) (puVar6 + 7)) = (undefined1) 0xe;
  puVar6[1] = (undefined4) uVar1;
  *puVar6 = (undefined4) (*((undefined4 *) (iVar7 + 0x12)));
  iVar7 = (int) CFunc_InsertAfterStatement(2, iVar7);
  *((undefined1 *) (iVar7 + 6)) = (undefined1) 1;
  *((int *) (iVar7 + 0xe)) = (int) iVar3;
  *((int *) (iVar3 + 4)) = (int) iVar7;
  *((undefined4 **) (iVar7 + 0x12)) = (undefined4 *) puVar6;
  iVar7 = (int) CFunc_InsertAfterStatement(4, iVar7);
  *((undefined4 *) (iVar7 + 10)) = (undefined4) (*((undefined4 *) (param_1 + 0x18)));
  iVar7 = (int) CFunc_InsertAfterStatement(4, iVar7);
  uVar1 = (undefined4) funccallexpr(DAT_00716d68, nullnode(), nullnode(), nullnode(), 0);
  *((undefined4 *) (iVar7 + 10)) = (undefined4) uVar1;
  iVar7 = (int) CFunc_InsertAfterStatement(2, iVar7);
  *((int *) (iVar7 + 0xe)) = (int) iVar4;
  *((int *) (iVar4 + 4)) = (int) iVar7;
  if (((uint) (*((undefined4 **) (iVar7 + 0x12)))) != ((uint) puVar6))
  {
    CError_Internal(cexcept_filename, 0xa2b);
  }
  *((undefined4 *) (iVar7 + 0x12)) = (undefined4) (*puVar6);
  cexcept_prevstmt = (uint *) iVar7;
  return (int) (*((int *) (param_1 + 0x1c)));
}

uint CExcept_TransNewException(char *param_1, char param_2)
{
  undefined4 uVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  int unaff_EDI;
  bool bVar7;
  bVar7 = (bool) ((*param_1) != 'I');
  if ((*(*((char **) (param_1 + 0x18)))) != ';')
  {
    CError_Internal(cexcept_filename, 0x95d);
  }
  if (param_2 == '\0')
  {
    uVar1 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
    *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar1;
    uVar1 = (undefined4) CExcept_TempTransExpr((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
    *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar1;
    if (bVar7)
    {
      piVar2 = (int *) ((int *) CFunc_InsertAfterStatement(7, cexcept_prevstmt));
      iVar6 = (int) (*piVar2);
      *((undefined4 *) (((int) piVar2) + 0x16)) = (undefined4) (*((undefined4 *) (iVar6 + 0x16)));
      *((undefined4 *) (((int) piVar2) + 0x1a)) = (undefined4) (*((undefined4 *) (iVar6 + 0x1a)));
      *((undefined4 *) (((int) piVar2) + 0x1e)) = (undefined4) (*((undefined4 *) (iVar6 + 0x1e)));
      *((undefined4 **) (((int) piVar2) + 0x12)) = (undefined4 *) cexcept_eabefore;
      *((undefined4 *) (((int) piVar2) + 10)) = (undefined4) (*((undefined4 *) (param_1 + 0x10)));
      unaff_EDI = (int) newlabel();
      *((int *) (((int) piVar2) + 0xe)) = (int) unaff_EDI;
    }
    else
    {
      piVar2 = (int *) ((int *) CFunc_InsertAfterStatement(4, cexcept_prevstmt));
      iVar6 = (int) (*piVar2);
      *((undefined4 *) (((int) piVar2) + 0x16)) = (undefined4) (*((undefined4 *) (iVar6 + 0x16)));
      *((undefined4 *) (((int) piVar2) + 0x1a)) = (undefined4) (*((undefined4 *) (iVar6 + 0x1a)));
      *((undefined4 *) (((int) piVar2) + 0x1e)) = (undefined4) (*((undefined4 *) (iVar6 + 0x1e)));
      *((undefined4 **) (((int) piVar2) + 0x12)) = (undefined4 *) cexcept_eabefore;
      *((undefined4 *) (((int) piVar2) + 10)) = (undefined4) (*((undefined4 *) (param_1 + 0x10)));
    }
    piVar2 = (int *) ((int *) CFunc_InsertAfterStatement(4, piVar2));
    *((undefined4 *) (((int) piVar2) + 10)) = (undefined4) (*((undefined4 *) (param_1 + 0x14)));
    puVar5 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
    *puVar5 = (undefined4) cexcept_eabefore;
    *((undefined1 *) (puVar5 + 7)) = (undefined1) 10;
    puVar5[1] = (undefined4) (*((undefined4 *) ((*((int *) (param_1 + 0x18))) + 0x10)));
    puVar5[2] = (undefined4) (*((undefined4 *) (param_1 + 0x1c)));
    *((undefined4 **) (((int) piVar2) + 0x12)) = (undefined4 *) puVar5;
    if (bVar7)
    {
      piVar2 = (int *) ((int *) CFunc_InsertAfterStatement(2, piVar2));
      *((int *) (((int) piVar2) + 0xe)) = (int) unaff_EDI;
      *((int **) (unaff_EDI + 4)) = (int *) piVar2;
      *((undefined4 **) (((int) piVar2) + 0x12)) = (undefined4 *) cexcept_eabefore;
    }
    cexcept_prevstmt = (uint *) piVar2;
    uVar1 = (undefined4) create_objectrefnode(*((undefined4 *) ((*((int *) (param_1 + 0x18))) + 0x10)));
    iVar6 = (int) fn_0055b9f0(uVar1);
  }
  else
  {
    uVar1 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x10))));
    *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar1;
    uVar1 = (undefined4) CExcept_TempTransExprCond((undefined1 *) (*((undefined4 *) (param_1 + 0x14))));
    *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar1;
    uVar1 = (undefined4) create_temp_object(&DAT_00699c24);
    piVar2 = (int *) ((int *) CFunc_InsertAfterStatement(4, cexcept_prevstmt));
    iVar6 = (int) (*piVar2);
    *((undefined4 *) (((int) piVar2) + 0x16)) = (undefined4) (*((undefined4 *) (iVar6 + 0x16)));
    *((undefined4 *) (((int) piVar2) + 0x1a)) = (undefined4) (*((undefined4 *) (iVar6 + 0x1a)));
    *((undefined4 *) (((int) piVar2) + 0x1e)) = (undefined4) (*((undefined4 *) (iVar6 + 0x1e)));
    *((undefined4 **) (((int) piVar2) + 0x12)) = (undefined4 *) cexcept_eabefore;
    uVar3 = (undefined4) create_objectrefnode(uVar1);
    uVar3 = (undefined4) fn_0055b9f0(uVar3);
    uVar4 = (undefined4) intconstnode(&DAT_00699c24, 0);
    uVar3 = (undefined4) makediadicnode(uVar3, uVar4, 0x1e);
    *((undefined4 *) (((int) piVar2) + 10)) = (undefined4) uVar3;
    cexcept_prevstmt = (uint *) piVar2;
    puVar5 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
    *puVar5 = (undefined4) cexcept_eabefore;
    cexcept_eabefore = (uint *) puVar5;
    *((undefined1 *) (puVar5 + 7)) = (undefined1) 0xc;
    puVar5[1] = (undefined4) (*((undefined4 *) ((*((int *) (param_1 + 0x18))) + 0x10)));
    puVar5[2] = (undefined4) (*((undefined4 *) (param_1 + 0x1c)));
    puVar5[3] = (undefined4) uVar1;
    if (bVar7)
    {
      uVar3 = (undefined4) create_objectrefnode(uVar1);
      uVar3 = (undefined4) fn_0055b9f0(uVar3);
      uVar4 = (undefined4) intconstnode(&DAT_00699c24, 1);
      uVar3 = (undefined4) makediadicnode(uVar3, uVar4, 0x1e);
      uVar3 = (undefined4) makediadicnode(uVar3, *((undefined4 *) (param_1 + 0x14)), 0x29);
      uVar1 = (undefined4) create_objectrefnode(uVar1);
      uVar1 = (undefined4) fn_0055b9f0(uVar1);
      uVar4 = (undefined4) intconstnode(&DAT_00699c24, 0);
      uVar1 = (undefined4) makediadicnode(uVar1, uVar4, 0x1e);
      uVar1 = (undefined4) makediadicnode(uVar3, uVar1, 0x29);
      uVar1 = (undefined4) makediadicnode(*((undefined4 *) (param_1 + 0x10)), uVar1, 0x1c);
      uVar3 = (undefined4) create_objectrefnode(*((undefined4 *) ((*((int *) (param_1 + 0x18))) + 0x10)));
      uVar3 = (undefined4) fn_0055b9f0(uVar3);
      iVar6 = (int) makediadicnode(uVar1, uVar3, 0x29);
    }
    else
    {
      uVar3 = (undefined4) create_objectrefnode(uVar1);
      uVar3 = (undefined4) fn_0055b9f0(uVar3);
      uVar4 = (undefined4) intconstnode(&DAT_00699c24, 1);
      uVar3 = (undefined4) makediadicnode(uVar3, uVar4, 0x1e);
      uVar3 = (undefined4) makediadicnode(*((undefined4 *) (param_1 + 0x10)), uVar3, 0x29);
      uVar3 = (undefined4) makediadicnode(uVar3, *((undefined4 *) (param_1 + 0x14)), 0x29);
      uVar1 = (undefined4) create_objectrefnode(uVar1);
      uVar1 = (undefined4) fn_0055b9f0(uVar1);
      uVar4 = (undefined4) intconstnode(&DAT_00699c24, 0);
      uVar1 = (undefined4) makediadicnode(uVar1, uVar4, 0x1e);
      uVar1 = (undefined4) makediadicnode(uVar3, uVar1, 0x29);
      uVar3 = (undefined4) create_objectrefnode(*((undefined4 *) ((*((int *) (param_1 + 0x18))) + 0x10)));
      uVar3 = (undefined4) fn_0055b9f0(uVar3);
      iVar6 = (int) makediadicnode(uVar1, uVar3, 0x29);
    }
  }
  *((undefined4 *) (iVar6 + 4)) = (undefined4) (*((undefined4 *) (param_1 + 4)));
  return (uint) ((uint) iVar6);
}

undefined1 *CExcept_TempTrans_ETEMP(undefined1 *param_1)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  iVar1 = (int) (*((int *) (param_1 + 0x14)));
  puVar3 = (undefined4 *) cexcept_uniqueobjs;
  if (iVar1 == 0)
  {
    uVar2 = (undefined4) create_temp_object(*((undefined4 *) (param_1 + 0x10)));
  }
  else
  {
    for (; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
    {
      if (puVar3[2] == iVar1)
      {
        param_1[0x18] = (undefined1) 0;
        uVar2 = (undefined4) puVar3[1];
        goto LAB_0049e540;
      }
    }

    puVar3 = (undefined4 *) ((undefined4 *) galloc(0xc));
    *puVar3 = (undefined4) cexcept_uniqueobjs;
    cexcept_uniqueobjs = (uint *) puVar3;
    puVar3[2] = (undefined4) iVar1;
    uVar2 = (undefined4) create_temp_object(*((undefined4 *) (param_1 + 0x10)));
    puVar3[1] = (undefined4) uVar2;
    uVar2 = (undefined4) puVar3[1];
  }
  LAB_0049e540:
  if (param_1[0x18] == '\0')
    goto LAB_0049e546;

  puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x10));
  *puVar3 = (undefined4) cexcept_dtortemps;
  cexcept_dtortemps = (uint *) puVar3;
  puVar3[1] = (undefined4) uVar2;
  puVar3[3] = (undefined4) 0;
  if ((*(*((char **) (param_1 + 0x10)))) == '\x06')
  {
    uVar5 = (undefined4) CClass_Destructor(*((char **) (param_1 + 0x10)));
    puVar3[2] = (undefined4) uVar5;
    if (puVar3[2] == 0)
      goto LAB_0049e58e;
  }
  else
  {
    LAB_0049e58e:
    CError_Internal(cexcept_filename, 0x93f);

  }
  puVar4 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  *puVar4 = (undefined4) cexcept_eabefore;
  cexcept_eabefore = (uint *) puVar4;
  *((undefined1 *) (puVar4 + 7)) = (undefined1) 1;
  puVar4[1] = (undefined4) puVar3[1];
  uVar5 = (undefined4) CABI_GetDestructorObject(puVar3[2], 1);
  puVar4[2] = (undefined4) uVar5;
  puVar4 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  puVar3 = (undefined4 *) cexcept_eabefore;
  *puVar4 = (undefined4) (*cexcept_eabefore);
  puVar4[1] = (undefined4) puVar3[1];
  puVar4[2] = (undefined4) puVar3[2];
  puVar4[3] = (undefined4) puVar3[3];
  puVar4[4] = (undefined4) puVar3[4];
  puVar4[5] = (undefined4) puVar3[5];
  puVar4[6] = (undefined4) puVar3[6];
  *((undefined2 *) (puVar4 + 7)) = (undefined2) (*((undefined2 *) (puVar3 + 7)));
  *puVar4 = (undefined4) cexcept_eaafter;
  cexcept_eaafter = (uint *) puVar4;
  LAB_0049e546:
  *param_1 = (undefined1) 0x3b;

  *((undefined4 *) (param_1 + 0x10)) = (undefined4) uVar2;
  return (undefined1 *) param_1;
}

void CExcept_ScanTryBlock(undefined4 param_1, char param_2)
{
  byte decl[0x98];
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int local_bc;
  if (DAT_0070f21e == '\0')
  {
    fn_0045c480(0x280c);
  }
  iVar3 = (int) create_temp_object(&DAT_0071726c);
  if (DAT_00725ed8 != '\0')
  {
    uVar5 = (undefined4) GetHashNameNode(cexcept_magic_name);
    *((undefined4 *) (iVar3 + 0xc)) = (undefined4) uVar5;
    fn_004ea740(DAT_00711be0, *((undefined4 *) (iVar3 + 0xc)), iVar3);
  }
  iVar4 = (int) CFunc_AppendStatement(2);
  *((undefined1 *) (iVar4 + 6)) = (undefined1) 1;
  uVar5 = (undefined4) newlabel();
  *((undefined4 *) (iVar4 + 0xe)) = (undefined4) uVar5;
  *((int *) ((*((int *) (iVar4 + 0xe))) + 4)) = (int) iVar4;
  iVar4 = (int) CFunc_AppendStatement(0xc);
  uVar5 = (undefined4) fn_00521c20(iVar3, 1);
  *((undefined4 *) (iVar4 + 10)) = (undefined4) uVar5;
  if (DAT_00717466 != 0x7b)
  {
    fn_0045c480(0x2797);
    return;
  }
  CFunc_ParseScopedStatement(param_1);
  if (DAT_00717466 != 0x152)
  {
    fn_0045c480(0x2802);
    return;
  }
  iVar6 = (int) CFunc_AppendStatement(3);
  uVar5 = (undefined4) newlabel();
  *((undefined4 *) (iVar6 + 0xe)) = (undefined4) uVar5;
  iVar1 = (int) (*((int *) (iVar6 + 0xe)));
  iVar7 = (int) newlabel();
  local_bc = (int) 0;
  do
  {
    fn_0052ef10();
    iVar8 = (int) CFunc_AppendStatement(2);
    *((undefined1 *) (iVar8 + 6)) = (undefined1) 1;
    iVar9 = (int) newlabel();
    *((int *) (iVar8 + 0xe)) = (int) iVar9;
    *((int *) (iVar9 + 4)) = (int) iVar8;
    iVar9 = (int) 0;
    piVar10 = (int *) ((int *) CompilerTools_AllocatePool(0x1c));
    memclrw(piVar10, 0x1c);
    *piVar10 = (int) local_bc;
    piVar10[3] = (int) iVar8;
    piVar10[2] = (int) iVar3;
    DAT_00717466 = (short) fn_00447b70();
    if (DAT_00717466 != 0x28)
    {
      fn_0045c480(0x2782);
      LAB_0049e975:
      iVar3 = (int) CFunc_AppendStatement(2);

      *((int *) (iVar3 + 0xe)) = (int) iVar7;
      *((int *) (iVar7 + 4)) = (int) iVar3;
      CExcept_PatchDObjStack((int *) iVar4, (int *) iVar6, (int *) iVar3, (undefined4 *) piVar10);
      iVar3 = (int) CFunc_AppendStatement(2);
      *((int *) (iVar3 + 0xe)) = (int) iVar1;
      *((int *) (iVar1 + 4)) = (int) iVar3;
      return;
    }
    DAT_00717466 = (short) fn_00447b70();
    if (DAT_00717466 == 0x17f)
    {
      DAT_00717466 = (short) fn_00447b70();
    }
    else
    {
      memclrw(decl, 0x98);
      CParser_GetDeclSpecs(decl, 0);
      if ((*((char *) (decl + 0x5e))) != '\0')
      {
        fn_0045c480(0x2789);
      }
      if ((*((short *) (decl + 0x4e))) != 0)
      {
        fn_0045c480(0x27c1);
      }
      if ((*((short *) (decl + 0x80))) != 0)
      {
        fn_0045c480(0x28f5);
      }
      if ((*((char *) (decl + 0x76))) != '\0')
      {
        fn_0045c480(0x28f5);
      }
      if ((*((char *) (decl + 0x77))) != '\0')
      {
        fn_0045c480(0x28f5);
      }
      CDecl_ParseDeclarator(decl);
      if ((*(*((char **) decl))) == '\a')
      {
        *((char **) decl) = (char *) ((char *) CDecl_NewPointerType(*((char **) decl)));
      }
      else
        if ((*(*((char **) decl))) == '\r')
      {
        *((char **) decl) = (char *) ((char *) CDecl_NewPointerType(*((undefined4 *) ((*((char **) decl)) + 6))));
      }
      fn_00544fc0(*((char **) decl), *((uint *) (decl + 4)));
      CanAllocObject(*((char **) decl));
      if (((*(*((char **) decl))) == '\x06') && (((*((uint *) ((*((char **) decl)) + 0x22))) & 8) != 0))
      {
        fn_0045a490(*((char **) decl));
      }
      piVar10[5] = (int) ((int) (*((char **) decl)));
      piVar10[6] = (int) (*((uint *) (decl + 4)));
      if ((*((uint *) (decl + 0x18))) != 0)
      {
        iVar9 = (int) fn_0052ee40();
        iVar8 = (int) fn_004eb140(DAT_00711be0, *((uint *) (decl + 0x18)));
        if (iVar8 != 0)
        {
          fn_0045c480(0x278a, (*((uint *) (decl + 0x18))) + 10);
        }
        iVar8 = (int) CParser_NewLocalDataObject(decl, 1);
        fn_0052ec00(iVar8);
        fn_004ea740(DAT_00711be0, *((uint *) (decl + 0x18)), iVar8);
        piVar10[1] = (int) iVar8;
        cVar2 = (char) CTemplateTools_IsDependentType(*((undefined4 *) (iVar8 + 0x10)));
        if (cVar2 == '\0')
        {
          iVar11 = (int) fn_0049eb00((int) iVar8, (undefined4) piVar10[2]);
        }
        else
        {
          iVar11 = (int) fn_00524320(0x16);
          *((int *) (iVar11 + 0x10)) = (int) iVar8;
          *((int *) (iVar11 + 0x14)) = (int) piVar10[2];
        }
        iVar8 = (int) CFunc_AppendStatement(4);
        *((int *) (iVar8 + 10)) = (int) iVar11;
      }
    }
    if (DAT_00717466 != 0x29)
    {
      fn_0045c480(0x2783);
      goto LAB_0049e975;
    }
    DAT_00717466 = (short) fn_00447b70();
    if (DAT_00717466 != 0x7b)
    {
      fn_0045c480(0x2797);
      goto LAB_0049e975;
    }
    CFunc_ParseScopedStatement(param_1);
    if (param_2 != '\0')
    {
      iVar8 = (int) CFunc_AppendStatement(4);
      uVar5 = (undefined4) funccallexpr(DAT_00716d68, nullnode(), nullnode(), nullnode(), 0);
      *((undefined4 *) (iVar8 + 10)) = (undefined4) uVar5;
    }
    piVar10[4] = (int) iVar8;
    if (iVar9 != 0)
    {
      fn_0052ec70(iVar9);
    }
    if (DAT_00717466 != 0x152)
      goto LAB_0049e975;
    iVar8 = (int) CFunc_AppendStatement(3);
    *((int *) (iVar8 + 0xe)) = (int) iVar7;
    local_bc = (int) ((int) piVar10);
  }
  while (1);
}

uint fn_0049eb00(int param_1, undefined4 param_2)
{
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uVar3 = (undefined4) fn_00521c20(param_2, 1);
  uVar4 = (undefined4) intconstnode(&DAT_00699c6c, 0xc);
  iVar5 = (int) makediadicnode(uVar3, uVar4, 0xf);
  uVar3 = (undefined4) CDecl_NewPointerType(*((undefined4 *) (param_1 + 0x10)));
  uVar3 = (undefined4) CDecl_NewPointerType(uVar3);
  *((undefined4 *) (iVar5 + 4)) = (undefined4) uVar3;
  iVar5 = (int) makemonadicnode(iVar5, 4);
  uVar3 = (undefined4) CDecl_NewPointerType(*((undefined4 *) (param_1 + 0x10)));
  *((undefined4 *) (iVar5 + 4)) = (undefined4) uVar3;
  pcVar1 = (char *) (*((char **) (param_1 + 0x10)));
  if (((*pcVar1) == '\f') && (((*((uint *) (pcVar1 + 10))) & 0x20) != 0))
  {
    uVar3 = (undefined4) create_objectrefnode(param_1);
    return (uint) makediadicnode(uVar3, iVar5, 0x1e);
  }
  if ((*pcVar1) == '\x06')
  {
    cVar2 = (char) fn_00542350(pcVar1);
    if (cVar2 == '\0')
    {
      iVar6 = (int) CClass_Destructor(*((undefined4 *) (param_1 + 0x10)));
      if (iVar6 == 0)
      {
        uVar3 = (undefined4) fn_00521c20(param_1, 1);
      }
      else
      {
        uVar3 = (undefined4) CExcept_RegisterDestructorObject((undefined4) param_1, (int) 0, (undefined4) iVar6);
      }
      iVar5 = (int) makemonadicnode(iVar5, 4);
      *((undefined4 *) (iVar5 + 4)) = (undefined4) (*((undefined4 *) (param_1 + 0x10)));
      return (uint) fn_005a6b30(*((undefined4 *) (param_1 + 0x10)), uVar3, iVar5);
    }
  }
  iVar5 = (int) makemonadicnode(iVar5, 4);
  *((undefined4 *) (iVar5 + 4)) = (undefined4) (*((undefined4 *) (param_1 + 0x10)));
  uVar3 = (undefined4) create_objectrefnode(param_1);
  uVar3 = (undefined4) fn_0055b9f0(uVar3);
  return (uint) makediadicnode(uVar3, iVar5, 0x1e);
}

void CExcept_PatchDObjStack(int *param_1, int *param_2, int *param_3, undefined4 *param_4)
{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  char cVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  char local_19;
  int *local_18;
  iVar1 = (int) param_4[2];
  local_19 = (char) '\0';
  piVar2 = (int *) (*((int **) (((int) param_1) + 0x12)));
  local_18 = (int *) ((int *) 0x0);
  piVar7 = (int *) piVar2;
  for (; ((uint) param_4) != ((uint) ((undefined4 *) 0x0)); param_4 = (undefined4 *) ((undefined4 *) (*param_4)))
  {
    piVar5 = (int *) ((int *) CompilerTools_AllocatePool(0x1e));
    memclrw(piVar5, 0x1e);
    *piVar5 = (int) ((int) piVar7);
    if (((uint) local_18) == ((uint) ((int *) 0x0)))
    {
      local_18 = (int *) piVar5;
    }
    *((undefined1 *) (piVar5 + 7)) = (undefined1) 0xd;
    piVar5[1] = (int) param_4[1];
    piVar5[3] = (int) (*((int *) (param_4[3] + 0xe)));
    piVar5[2] = (int) iVar1;
    if (local_19 == '\0')
    {
      pcVar3 = (char *) ((char *) param_4[5]);
      if (((uint) pcVar3) == ((uint) ((char *) 0x0)))
      {
        cVar4 = (char) '\x01';
      }
      else
        if ((*pcVar3) == '\x06')
      {
        iVar6 = (int) CClass_Destructor(pcVar3);
        cVar4 = (char) (iVar6 != 0);
      }
      else
        if ((((*pcVar3) == '\f') && (((*((uint *) (pcVar3 + 10))) & 0x20) != 0)) && ((*(*((char **) (pcVar3 + 6)))) == '\x06'))
      {
        cVar4 = (char) '\x01';
      }
      else
      {
        cVar4 = (char) CTemplateTools_IsDependentType(pcVar3);
      }
      if (cVar4 != '\0')
      {
        local_19 = (char) '\x01';
      }
    }
    piVar5[5] = (int) param_4[5];
    piVar5[6] = (int) param_4[6];
    piVar7 = (int *) piVar5;
  }

  do
  {
    piVar5 = (int *) (*((int **) (((int) param_1) + 0x12)));
    if (((uint) (*((int **) (((int) param_1) + 0x12)))) == ((uint) piVar2))
    {
      *((int **) (((int) param_1) + 0x12)) = (int *) piVar7;
    }
    else
    {
      do
      {
        piVar8 = (int *) piVar5;
        if (((uint) piVar8) == ((uint) ((int *) 0x0)))
        {
          CError_Internal(cexcept_filename, 0x6b6);
        }
        piVar5 = (int *) ((int *) (*piVar8));
        if (((uint) piVar5) == ((uint) piVar7))
          goto LAB_0049ed20;
      }
      while (((uint) piVar5) != ((uint) piVar2));
      *piVar8 = (int) ((int) piVar7);
    }
    LAB_0049ed20:
    if (((uint) param_1) == ((uint) param_3))
    {
      DAT_00725e5d = (byte) 1;
      return;
    }

    if (((uint) param_1) == ((uint) param_2))
    {
      piVar7 = (int *) ((int *) CompilerTools_AllocatePool(0x1e));
      memclrw(piVar7, 0x1e);
      *piVar7 = (int) ((int) piVar2);
      *((undefined1 *) (piVar7 + 7)) = (undefined1) 0xe;
      piVar7[1] = (int) iVar1;
      *((char *) (piVar7 + 2)) = (char) local_19;
    }
    param_1 = (int *) ((int *) (*param_1));
    if (((uint) param_1) == ((uint) ((int *) 0x0)))
    {
      CError_Internal(cexcept_filename, 0x6cc);
    }
  }
  while (1);
}

uint CExcept_ParseThrowExpression(void)
{
  undefined4 uVar1;
  int iVar2;
  if (DAT_0070f21e == '\0')
  {
    fn_0045c480(0x280c);
  }
  DAT_00717466 = (short) fn_00447b70();
  switch (DAT_00717466)
  {
    case 0x29:

    case 0x2c:

    case 0x3a:

    case 0x3b:
      iVar2 = (int) funccallexpr(DAT_00716d68, nullnode(), nullnode(), nullnode(), 0);
      *((uint *) (iVar2 + 8)) = (uint) ((*((uint *) (iVar2 + 8))) | 2);
      return (uint) iVar2;

    default:
      uVar1 = (undefined4) fn_005153b0();
      return (uint) CExcept_ThrowExpression((int) uVar1);

  }

}

uint CExcept_ThrowExpression(int param_1)
{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  if (param_1 != 0)
  {
    cVar1 = (char) fn_0053d470(param_1);
    if (cVar1 != '\0')
    {
      iVar2 = (int) fn_00524320(0x15);
      *((int *) (iVar2 + 0x10)) = (int) param_1;
      *((uint *) (iVar2 + 8)) = (uint) ((*((uint *) (iVar2 + 8))) | 2);
      return (uint) iVar2;
    }
  }
  pcVar3 = (char *) ((char *) fn_0055b7f0(param_1));
  if (((*pcVar3) == 'K') && (pcVar3[0x29] != '\0'))
  {
    pcVar3 = (char *) ((char *) fn_00543680(pcVar3, 0, 0, 1, 0));
  }
  uVar6 = (undefined4) create_temp_object(*((undefined4 *) (pcVar3 + 4)));
  if ((*(*((char **) (pcVar3 + 4)))) == '\x06')
  {
    uVar4 = (undefined4) fn_00521c20(uVar6, 1);
    cVar1 = (char) fn_005a8e20(pcVar3, *((undefined4 *) (pcVar3 + 4)), uVar4, 0);
    if (cVar1 == '\0')
      goto LAB_0049ef00;
    iVar2 = (int) fn_00559da0(pcVar3, 0);
  }
  else
  {
    LAB_0049ef00:
    uVar4 = (undefined4) fn_00521c20(uVar6, 1);

    if ((*(*((char **) (pcVar3 + 4)))) == '\x06')
    {
      cVar1 = (char) fn_00542350(*((char **) (pcVar3 + 4)));
      if (cVar1 == '\0')
      {
        iVar2 = (int) fn_005a6b30(*((undefined4 *) (pcVar3 + 4)), uVar4, pcVar3);
        goto LAB_0049ef69;
      }
    }
    if ((*((int *) ((*((int *) (pcVar3 + 4))) + 2))) == 0)
    {
      fn_0045c480(0x27a2);
    }
    iVar2 = (int) makemonadicnode(uVar4, 4);
    *((undefined4 *) (iVar2 + 4)) = (undefined4) (*((undefined4 *) (pcVar3 + 4)));
    uVar4 = (undefined4) makediadicnode(iVar2, pcVar3, 0x1e);
    uVar6 = (undefined4) fn_00521c20(uVar6, 1);
    iVar2 = (int) makediadicnode(uVar4, uVar6, 0x29);
    *((undefined1 **) (iVar2 + 4)) = (undefined1 *) (&DAT_006771c8);
  }
  LAB_0049ef69:
  uVar6 = (undefined4) CExcept_GetTypeID((char *) (*((undefined4 *) (pcVar3 + 4))), (undefined4) ((*((uint *) (pcVar3 + 8))) & 0x1f200003), (char) 1);

  if ((*(*((char **) (pcVar3 + 4)))) == '\x06')
  {
    iVar5 = (int) CClass_Destructor(*((char **) (pcVar3 + 4)));
    if (iVar5 != 0)
    {
      uVar4 = (undefined4) CABI_GetDestructorObject(iVar5, 1);
      uVar4 = (undefined4) fn_00521c20(uVar4, 1);
      iVar2 = (int) funccallexpr(DAT_00716d68, uVar6, iVar2, uVar4, 0);
      goto LAB_0049efbc;
    }
  }
  uVar4 = (undefined4) nullnode();
  iVar2 = (int) funccallexpr(DAT_00716d68, uVar6, iVar2, uVar4, 0);
  LAB_0049efbc:
  *((uint *) (iVar2 + 8)) = (uint) ((*((uint *) (iVar2 + 8))) | 2);

  return (uint) ((uint) iVar2);
}

void CExcept_SyncNoThrowUsage(uint type1, uint qualifiers1, uint type2, uint qualifiers2)
{
  return;
}

void CExcept_ScanExceptionSpecification(int param_1)
{
  byte decl[0x98];
  undefined4 *puVar1;
  short sVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  puVar3 = (undefined4 *) ((undefined4 *) 0x0);
  sVar2 = (short) fn_00447b70();
  if (sVar2 != 0x28)
  {
    fn_0045c480(0x2782);
    return;
  }
  if ((DAT_0070f1b3 != '\0') && ((sVar2 = (short) CPrep_UpdateTokenLine(), sVar2 == 0x17f)))
  {
    fn_00447b70();
    DAT_00717466 = (short) fn_00447b70();
    if (DAT_00717466 == 0x29)
    {
      DAT_00717466 = (short) fn_00447b70();
    }
    else
    {
      fn_0045c480(0x2783);
    }
    *((undefined4 *) (param_1 + 10)) = (undefined4) 0;
    return;
  }
  DAT_00717466 = (short) fn_00447b70();
  if (DAT_00717466 != 0x29)
  {
    puVar4 = (undefined4 *) puVar3;
    while (1)
    {
      memclrw(decl, 0x98);
      CParser_GetDeclSpecs(decl, 0);
      if ((*((short *) (decl + 0x4e))) != 0)
      {
        fn_0045c480(0x27c1);
      }
      if ((*((short *) (decl + 0x80))) != 0)
      {
        fn_0045c480(0x28f5);
      }
      if ((*((char *) (decl + 0x76))) != '\0')
      {
        fn_0045c480(0x28f5);
      }
      if ((*((char *) (decl + 0x77))) != '\0')
      {
        fn_0045c480(0x28f5);
      }
      CDecl_ParseDeclarator(decl);
      if ((*((uint *) (decl + 0x18))) != 0)
      {
        fn_0045c480(0x27a2);
      }
      fn_00544fc0(*((int *) decl), ((int *) (decl + 4))[0]);
      *((int *) decl) = (int) fn_00453430(*((int *) decl), (int *) (decl + 4));
      for (puVar1 = (undefined4 *) puVar4; (((uint) puVar1) != ((uint) ((undefined4 *) 0x0))) && ((sVar2 = (short) iscpp_typeequal(puVar1[1], *((int *) decl)), (sVar2 == 0) || (puVar1[2] != ((int *) (decl + 4))[0]))); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
      {
      }

      puVar3 = (undefined4 *) puVar4;
      if (((uint) puVar1) == ((uint) ((undefined4 *) 0x0)))
      {
        puVar3 = (undefined4 *) ((undefined4 *) galloc(0xc));
        memclrw(puVar3, 0xc);
        *puVar3 = (undefined4) puVar4;
        puVar3[1] = (undefined4) (*((int *) decl));
        puVar3[2] = (undefined4) ((int *) (decl + 4))[0];
      }
      if (DAT_00717466 == 0x29)
        goto LAB_0049f0d8;
      if (DAT_00717466 != 0x2c)
        break;
      DAT_00717466 = (short) fn_00447b70();
      puVar4 = (undefined4 *) puVar3;
    }

    fn_0045c480(0x2783);
  }
  LAB_0049f0d8:
  if (((uint) puVar3) == ((uint) ((undefined4 *) 0x0)))
  {
    puVar3 = (undefined4 *) ((undefined4 *) galloc(0xc));
    memclrw(puVar3, 0xc);
  }

  *((undefined4 **) (param_1 + 10)) = (undefined4 *) puVar3;
  DAT_00717466 = (short) fn_00447b70();
  return;
}

int CExcept_GetTypeID(char *param_1, undefined4 param_2, char param_3)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_28[16];
  byte local_type[14];
  if (((*param_1) == '\f') && (((*((uint *) (param_1 + 10))) & 0x20) != 0))
  {
    param_1 = (char *) (*((char **) (param_1 + 6)));
  }
  cVar1 = (char) (*param_1);
  if ((cVar1 == '\x06') || ((cVar1 == '\f') && ((*(*((char **) (param_1 + 6)))) == '\x06')))
  {
    if (DAT_00716c9c != 0)
    {
      COptimizer_GetFunctionObject(DAT_00716c9c);
    }
    DAT_0070bc24 = (uint) 0;
    if ((*param_1) == '\f')
    {
      AppendGListByte(&DAT_0070bc20, 0x2a);
      param_1 = (char *) (*((char **) (param_1 + 6)));
    }
    else
    {
      AppendGListByte(&DAT_0070bc20, 0x21);
    }
    if (param_3 == '\0')
    {
      CExcept_MangleClass((int) param_1);
      AppendGListByte(&DAT_0070bc20, 0x21);
    }
    else
    {
      for (puVar4 = (undefined4 *) ((undefined4 *) CExcept_GetBaseClassList((undefined4 *) 0, (undefined4) param_1, (int) param_1, (int) 0, (char) 0, (char) 1)); ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
      {
        if (((*((char *) (((int) puVar4) + 0xd))) != '\0') && ((*((char *) (((int) puVar4) + 0xe))) == '\0'))
        {
          CExcept_MangleClass((int) puVar4[1]);
          AppendGListByte(&DAT_0070bc20, 0x21);
          if (puVar4[2] == 0)
          {
            AppendGListByte(&DAT_0070bc20, 0x21);
          }
          else
          {
            sprintf(local_28, cexcept_offset_format, puVar4[2]);
            fn_0046d530(&DAT_0070bc20, local_28);
          }
        }
      }

    }
  }
  else
  {
    if (cVar1 == '\f')
    {
      if (((*((uint *) (param_1 + 10))) & 3) != 0)
      {
        *((uint *) (local_type + 0)) = (uint) (*((uint *) param_1));
        *((uint *) (local_type + 4)) = (uint) (*((uint *) (param_1 + 4)));
        *((ushort *) (local_type + 8)) = (ushort) (*((ushort *) (param_1 + 8)));
        *((ushort *) (local_type + 10)) = (ushort) 0;
        *((ushort *) (local_type + 12)) = (ushort) 0;
        param_1 = (char *) ((char *) local_type);
      }
    }
    else
    {
      param_2 = (undefined4) 0;
    }
    CMangler_MangleType(param_1, param_2, 0);
  }
  AppendGListByte(&DAT_0070bc20, 0);
  iVar2 = (int) fn_005243b0(0x37);
  *((undefined4 *) (iVar2 + 4)) = (undefined4) ((uint) DAT_006771d6);
  *((undefined4 *) (iVar2 + 0x10)) = (undefined4) DAT_0070bc24;
  uVar3 = (undefined4) galloc(DAT_0070bc24);
  *((undefined4 *) (iVar2 + 0x14)) = (undefined4) uVar3;
  memcpy(*((undefined4 *) (iVar2 + 0x14)), *DAT_0070bc20, DAT_0070bc24);
  return (int) iVar2;
}

undefined4 *CExcept_GetBaseClassList(undefined4 *param_1, undefined4 param_2, int param_3, int param_4, char param_5, char param_6)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  undefined4 uVar6;
  puVar1 = (undefined4 *) param_1;
  while (1)
  {
    if (((uint) puVar1) == ((uint) ((undefined4 *) 0x0)))
    {
      puVar2 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x10));
      puVar2[1] = (undefined4) param_3;
      puVar2[2] = (undefined4) param_4;
      *((char *) (puVar2 + 3)) = (char) param_5;
      *((char *) (((int) puVar2) + 0xd)) = (char) param_6;
      *((undefined1 *) (((int) puVar2) + 0xe)) = (undefined1) 0;
      *puVar2 = (undefined4) param_1;
      for (puVar1 = (undefined4 *) (*((undefined4 **) (param_3 + 0xe))); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
      {
        bVar5 = (bool) 0;
        if (param_6 != '\0')
        {
          bVar5 = (bool) ((*((char *) (puVar1 + 4))) == '\0');
        }
        if ((*((char *) (((int) puVar1) + 0x11))) == '\0')
        {
          uVar3 = (uint) ((uint) bVar5);
          uVar6 = (undefined4) 0;
          iVar4 = (int) (param_4 + puVar1[2]);
        }
        else
        {
          uVar3 = (uint) ((uint) bVar5);
          uVar6 = (undefined4) 1;
          iVar4 = (int) CClass_FindVirtualBase(param_2, puVar1[1]);
          iVar4 = (int) (*((int *) (iVar4 + 8)));
        }
        puVar2 = (undefined4 *) ((undefined4 *) CExcept_GetBaseClassList((undefined4 *) puVar2, (undefined4) param_2, (int) puVar1[1], (int) iVar4, (char) uVar6, (char) uVar3));
      }

      return (undefined4 *) puVar2;
    }
    if (puVar1[1] == param_3)
      break;
    puVar1 = (undefined4 *) ((undefined4 *) (*puVar1));
  }

  if ((param_5 == '\0') || ((*((char *) (puVar1 + 3))) == '\0'))
  {
    CExcept_MakeBaseClassListAmbig((undefined4 *) param_1, (int) param_3);
  }
  else
    if (param_6 != '\0')
  {
    *((undefined1 *) (((int) puVar1) + 0xd)) = (undefined1) 1;
  }
  return (undefined4 *) param_1;
}

void CExcept_MakeBaseClassListAmbig(undefined4 *param_1, int param_2)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  for (puVar1 = (undefined4 *) param_1; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    if (puVar1[1] == param_2)
    {
      *((undefined1 *) (((int) puVar1) + 0xe)) = (undefined1) 1;
    }
  }

  for (puVar1 = (undefined4 *) (*((undefined4 **) (param_2 + 0xe))); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    if ((*((char *) (((int) puVar1) + 0x11))) == '\0')
    {
      iVar2 = (int) puVar1[1];
      for (puVar3 = (undefined4 *) param_1; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
      {
        if (puVar3[1] == iVar2)
        {
          *((undefined1 *) (((int) puVar3) + 0xe)) = (undefined1) 1;
        }
      }

      for (puVar3 = (undefined4 *) (*((undefined4 **) (iVar2 + 0xe))); ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
      {
        if ((*((char *) (((int) puVar3) + 0x11))) == '\0')
        {
          iVar2 = (int) puVar3[1];
          for (puVar4 = (undefined4 *) param_1; ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
          {
            if (puVar4[1] == iVar2)
            {
              *((undefined1 *) (((int) puVar4) + 0xe)) = (undefined1) 1;
            }
          }

          for (puVar4 = (undefined4 *) (*((undefined4 **) (iVar2 + 0xe))); ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
          {
            if ((*((char *) (((int) puVar4) + 0x11))) == '\0')
            {
              iVar2 = (int) puVar4[1];
              for (puVar5 = (undefined4 *) param_1; ((uint) puVar5) != ((uint) ((undefined4 *) 0x0)); puVar5 = (undefined4 *) ((undefined4 *) (*puVar5)))
              {
                if (puVar5[1] == iVar2)
                {
                  *((undefined1 *) (((int) puVar5) + 0xe)) = (undefined1) 1;
                }
              }

              for (puVar5 = (undefined4 *) (*((undefined4 **) (iVar2 + 0xe))); ((uint) puVar5) != ((uint) ((undefined4 *) 0x0)); puVar5 = (undefined4 *) ((undefined4 *) (*puVar5)))
              {
                if ((*((char *) (((int) puVar5) + 0x11))) == '\0')
                {
                  CExcept_MakeBaseClassListAmbig((undefined4 *) param_1, (int) puVar5[1]);
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

void CExcept_MangleClass(int param_1)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  undefined1 local_44[64];
  puVar1 = (undefined4 *) (*((undefined4 **) (param_1 + 6)));
  while (1)
  {
    if (((uint) puVar1) == ((uint) ((undefined4 *) 0x0)))
    {
      puVar1 = (undefined4 *) ((undefined4 *) (*(*((undefined4 **) (param_1 + 6)))));
      puVar2 = (undefined4 *) puVar1;
      while (1)
      {
        if (((uint) puVar2) == ((uint) ((undefined4 *) 0x0)))
        {
          CExcept_MangleNameSpaceName((undefined4 *) puVar1);
          fn_0046d530(&DAT_0070bc20, (*((int *) (param_1 + 10))) + 10);
          return;
        }
        if ((((*((char *) (((int) puVar2) + 0x1d))) == '\0') && ((*((char *) (((int) puVar2) + 0x1f))) == '\0')) && (puVar2[1] == 0))
          break;
        puVar2 = (undefined4 *) ((undefined4 *) (*puVar2));
      }

      if (DAT_00716c9c == 0)
      {
        CError_Internal(cexcept_filename, 0x459);
      }
      fn_0046d530(&DAT_0070bc20, (*((int *) (param_1 + 10))) + 10);
      sprintf(local_44, cexcept_local_format, param_1);
      fn_0046d530(&DAT_0070bc20, local_44);
      iVar4 = (int) COptimizer_GetFunctionObject(DAT_00716c9c);
      fn_0046d530(&DAT_0070bc20, iVar4 + 10);
      cVar3 = (char) fn_00452fe0(DAT_00716c9c);
      if (cVar3 != '\0')
      {
        fn_0046d530(&DAT_0070bc20, cexcept_file_marker);
        pcVar5 = (char *) ((char *) fn_00455d00());
        cVar3 = (char) (*pcVar5);
        while (cVar3 != '\0')
        {
          if ((((cVar3 < 'a') || (cVar3 > 'z')) && ((cVar3 < 'A') || (cVar3 > 'Z'))) && ((cVar3 < '0') || (cVar3 > '9')))
          {
            cVar3 = (char) '_';
          }
          AppendGListByte(&DAT_0070bc20, (int) cVar3);
          pcVar5 = (char *) (pcVar5 + 1);
          cVar3 = (char) (*pcVar5);
        }

      }
      return;
    }
    if ((puVar1[3] != 0) && (((*((uint *) (puVar1[3] + 0x22))) & 0x800) != 0))
      break;
    puVar1 = (undefined4 *) ((undefined4 *) (*puVar1));
  }

  CMangler_MangleType(param_1, 0, 1);
  return;
}

void CExcept_MangleNameSpaceName(undefined4 *param_1)
{
  for (; param_1; param_1 = (undefined4 *) ((undefined4 *) (*param_1)))
    if (param_1[1])
  {
    CExcept_MangleNameSpaceName((undefined4 *) ((undefined4 *) (*param_1)));
    fn_0046d530(&DAT_0070bc20, param_1[1] + 10);
    fn_0046d530(&DAT_0070bc20, cexcept_namespace_separator);
    return;
  }

}

uint CExcept_ActionCleanup(uint *action, uint statement)
{
  uint expression;
  uint destructor;
  uint address;
  uint count;
  uint size;
  uint condition;
  switch (((byte *) action)[28])
  {
    case 1:

    case 3:
      destructor = (uint) action[2];
      address = (uint) fn_00521c20(action[1], 1);
      if ((((byte *) action)[28] == 3) && action[3])
      address = (uint) makediadicnode(address, intconstnode(DAT_00699c6c, action[3]), 15);
      expression = (uint) CABI_DestroyObject(destructor, address, 1, 1, 0);
      if (((*((byte *) expression)) != 57) || ((*(*((byte **) (expression + 16)))) != 59))
      CError_Internal(cexcept_filename, 808);
      address = (uint) (*((uint *) (expression + 16)));
      if ((*((byte *) ((*((uint *) (address + 16))) + 2))) == 4)
      *((uint *) (address + 8)) |= 8;
      statement = (uint) CFunc_InsertAfterStatement(4, statement);
      *((uint *) (statement + 10)) = (uint) expression;
      *((uint *) (statement + 18)) = (uint) action[0];
      break;

    case 5:
      destructor = (uint) action[2];
      address = (uint) action[1];
      count = (uint) action[3];
      size = (uint) action[4];
      statement = (uint) CFunc_InsertAfterStatement(4, statement);
      if (destructor)
    {
      destructor = (uint) fn_00521c20(CABI_GetDestructorObject(destructor, 1), 1);
      address = (uint) fn_00521c20(address, 1);
      count = (uint) intconstnode(CABI_GetSizeTType(), count);
      size = (uint) intconstnode(CABI_GetSizeTType(), size);
      expression = (uint) funccallexpr(DAT_00711b80, address, destructor, size, count);
    }
    else
      expression = (uint) nullnode();
      *((uint *) (statement + 10)) = (uint) expression;
      *((uint *) (statement + 18)) = (uint) action[0];
      break;

    case 11:
      address = (uint) action[1];
      destructor = (uint) action[2];
      statement = (uint) CFunc_InsertAfterStatement(4, statement);
      *((uint *) (statement + 10)) = (uint) funccallexpr(destructor, create_objectrefnode(address), 0, 0, 0);
      *((uint *) (statement + 18)) = (uint) action[0];
      break;

    case 14:
      statement = (uint) CFunc_InsertAfterStatement(14, statement);
      *((uint *) (statement + 10)) = (uint) fn_00521c20(action[1], 1);
      *((uint *) (statement + 18)) = (uint) action[0];
      if (!((byte *) action)[8])
      *((byte *) (statement + 4)) = (byte) 13;
      break;

    case 21:
      address = (uint) action[1];
      condition = (uint) action[2];
      destructor = (uint) action[3];
      size = (uint) action[4];
      statement = (uint) CFunc_InsertAfterStatement(4, statement);
      if (destructor)
    {
      destructor = (uint) fn_00521c20(CABI_GetDestructorObject(destructor, 1), 1);
      count = (uint) intconstnode(CABI_GetSizeTType(), size);
      count = (uint) fn_00520530(create_objectrefnode(condition), count, 1);
      size = (uint) intconstnode(CABI_GetSizeTType(), size);
      address = (uint) create_objectrefnode(address);
      expression = (uint) funccallexpr(DAT_00711b80, address, destructor, size, count);
    }
    else
      expression = (uint) nullnode();
      *((uint *) (statement + 10)) = (uint) expression;
      *((uint *) (statement + 18)) = (uint) action[0];
      break;

    case 22:
      if (((byte *) action)[8])
    {
      expression = (uint) fn_00524320(25);
      *((uint *) (expression + 16)) = (uint) action[1];
      statement = (uint) CFunc_InsertAfterStatement(4, statement);
      *((uint *) (statement + 10)) = (uint) expression;
      *((uint *) (statement + 18)) = (uint) action[0];
    }
      break;

    case 2:

    case 4:

    case 6:

    case 7:

    case 8:

    case 9:

    case 10:

    case 12:

    case 13:

    case 15:

    case 16:

    case 17:

    case 18:

    case 19:

    case 20:
      break;

    default:
      CError_Internal(cexcept_filename, 1063);

  }

  return (uint) statement;
}

void CExcept_RegisterMemberArray(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6)
{
  int iVar1;
  undefined4 uVar2;
  iVar1 = (int) CompilerTools_AllocatePool(0x1e);
  memclrw(iVar1, 0x1e);
  *((undefined1 *) (iVar1 + 0x1c)) = (undefined1) 9;
  *((undefined4 *) (iVar1 + 4)) = (undefined4) param_2;
  uVar2 = (undefined4) CABI_GetDestructorObject(param_4, 1);
  *((undefined4 *) (iVar1 + 8)) = (undefined4) uVar2;
  *((undefined4 *) (iVar1 + 0xc)) = (undefined4) param_3;
  *((undefined4 *) (iVar1 + 0x10)) = (undefined4) param_5;
  *((undefined4 *) (iVar1 + 0x14)) = (undefined4) param_6;
  CExcept_PatchConstructorAction((undefined4 *) param_1, (undefined4 *) iVar1);
  *((byte *) (param_1 + 6)) |= 2;
  return;
}

void CExcept_RegisterMember(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, int param_5, char param_6)
{
  int iVar1;
  undefined4 uVar2;
  iVar1 = (int) CompilerTools_AllocatePool(0x1e);
  memclrw(iVar1, 0x1e);
  if (param_5 == 0)
  {
    if (param_6 == '\0')
    {
      *((undefined1 *) (iVar1 + 0x1c)) = (undefined1) 0x11;
    }
    else
    {
      *((undefined1 *) (iVar1 + 0x1c)) = (undefined1) 7;
    }
    uVar2 = (undefined4) CABI_GetDestructorObject(param_4, param_6 != '\0');
    *((undefined4 *) (iVar1 + 8)) = (undefined4) uVar2;
    *((undefined4 *) (iVar1 + 4)) = (undefined4) param_2;
    *((undefined4 *) (iVar1 + 0xc)) = (undefined4) param_3;
  }
  else
  {
    if (((uint) (*((undefined **) (param_5 + 0x10)))) != ((uint) (&DAT_00699c44)))
    {
      CError_Internal(cexcept_filename, 0x2ce);
    }
    *((undefined1 *) (iVar1 + 0x1c)) = (undefined1) 8;
    *((undefined4 *) (iVar1 + 4)) = (undefined4) param_2;
    *((int *) (iVar1 + 8)) = (int) param_5;
    uVar2 = (undefined4) CABI_GetDestructorObject(param_4, 1);
    *((undefined4 *) (iVar1 + 0xc)) = (undefined4) uVar2;
    *((undefined4 *) (iVar1 + 0x10)) = (undefined4) param_3;
  }
  CExcept_PatchConstructorAction((undefined4 *) param_1, (undefined4 *) iVar1);
  *((byte *) (param_1 + 6)) |= 2;
  return;
}

void CExcept_PatchConstructorAction(undefined4 *param_1, undefined4 *param_2)
{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 *puVar5;
  piVar4 = (int *) (*((int **) (((int) param_1) + 0x12)));
  do
  {
    if (((uint) piVar4) == ((uint) ((int *) 0x0)))
      goto switchD_004a001f_caseD_7;
    switch ((char) piVar4[7])
    {
      case '\a':

      case '\b':

      case '\t':

      case '\x0f':

      case '\x11':

      case '\x13':

      case '\x14':
        goto switchD_004a001f_caseD_7;

      default:
        piVar4 = (int *) ((int *) (*piVar4));
        break;

      case '\r':
        piVar2 = (int *) piVar4;
        while (piVar2 = (int *) ((int *) (*piVar2)), ((uint) piVar2) != ((uint) ((int *) 0x0)))
      {
        if ((*((char *) (piVar2 + 7))) != '\r')
        {
          CError_Internal(cexcept_filename, 0x224);
        }
      }

        switchD_004a001f_caseD_7:
      if (((uint) piVar4) == ((uint) ((int *) 0x0)))
      {
        for (; ((uint) param_1) != ((uint) ((undefined4 *) 0x0)); param_1 = (undefined4 *) ((undefined4 *) (*param_1)))
        {
          puVar3 = (undefined4 *) (*((undefined4 **) (((int) param_1) + 0x12)));
          if (((uint) (*((undefined4 **) (((int) param_1) + 0x12)))) == ((uint) ((undefined4 *) 0x0)))
          {
            *((undefined4 **) (((int) param_1) + 0x12)) = (undefined4 *) param_2;
          }
          else
          {
            do
            {
              puVar5 = (undefined4 *) puVar3;
              if (((uint) puVar5) == ((uint) param_2))
                goto LAB_004a00e0;
              puVar3 = (undefined4 *) ((undefined4 *) (*puVar5));
            }
            while (((uint) ((undefined4 *) (*puVar5))) != ((uint) ((undefined4 *) 0x0)));
            *puVar5 = (undefined4) param_2;
          }
          LAB_004a00e0:
          ;

        }

      }
      else
      {
        *param_2 = (undefined4) piVar4;
        for (; ((uint) param_1) != ((uint) ((undefined4 *) 0x0)); param_1 = (undefined4 *) ((undefined4 *) (*param_1)))
        {
          puVar3 = (undefined4 *) (*((undefined4 **) (((int) param_1) + 0x12)));
          cVar1 = (char) CExcept_ActionCompare((int) puVar3, (int) piVar4);
          if (cVar1 == '\0')
          {
            while (((uint) puVar3) != ((uint) param_2))
            {
              cVar1 = (char) CExcept_ActionCompare((int) (*puVar3), (int) piVar4);
              if (cVar1 != '\0')
              {
                *puVar3 = (undefined4) param_2;
                break;
              }
              puVar3 = (undefined4 *) ((undefined4 *) (*puVar3));
              if (((uint) puVar3) == ((uint) ((undefined4 *) 0x0)))
              {
                while ((((char) piVar4[7]) != '\r') || ((*piVar4) != 0))
                {
                  piVar4 = (int *) ((int *) (*piVar4));
                  if (((uint) piVar4) == ((uint) ((int *) 0x0)))
                  {
                    CError_Internal(cexcept_filename, 0x25b);
                  }
                }

                return;
              }
            }

          }
          else
          {
            *((undefined4 **) (((int) param_1) + 0x12)) = (undefined4 *) param_2;
          }
        }

      }

        return;

    }

  }
  while (1);
}

void CExcept_RegisterDeleteObject(undefined4 param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  puVar1 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  memclrw(puVar1, 0x1e);
  *puVar1 = (undefined4) DAT_00710b30;
  DAT_00710b30 = (uint *) puVar1;
  *((undefined1 *) (puVar1 + 7)) = (undefined1) 0xb;
  puVar1[1] = (undefined4) param_1;
  puVar1[2] = (undefined4) param_2;
  DAT_00725e5d = (byte) 1;
  return;
}

void CExcept_RegisterVLA(int param_1, int param_2, undefined4 param_3)
{
  undefined4 *puVar1;
  puVar1 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  memclrw(puVar1, 0x1e);
  *((undefined1 *) (puVar1 + 7)) = (undefined1) 0x15;
  puVar1[1] = (undefined4) (*((undefined4 *) (param_1 + 0xc)));
  puVar1[2] = (undefined4) (*((undefined4 *) (param_1 + 0x10)));
  puVar1[3] = (undefined4) param_3;
  puVar1[4] = (undefined4) (*((undefined4 *) (param_2 + 2)));
  *puVar1 = (undefined4) DAT_00710b30;
  DAT_00710b30 = (uint *) puVar1;
  return;
}

void CExcept_RegisterLocalArray(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  puVar1 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  memclrw(puVar1, 0x1e);
  *puVar1 = (undefined4) DAT_00710b30;
  DAT_00710b30 = (uint *) puVar1;
  uVar2 = (undefined4) CABI_GetDestructorObject(param_2, 1);
  *((undefined1 *) (puVar1 + 7)) = (undefined1) 5;
  puVar1[1] = (undefined4) param_1;
  puVar1[2] = (undefined4) uVar2;
  puVar1[3] = (undefined4) param_3;
  puVar1[4] = (undefined4) param_4;
  DAT_00725e5d = (byte) 1;
  return;
}

void CExcept_RegisterLocalObject(undefined4 param_1, undefined1 param_2)
{
  undefined4 *puVar1;
  puVar1 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  memclrw(puVar1, 0x1e);
  *puVar1 = (undefined4) DAT_00710b30;
  DAT_00710b30 = (uint *) puVar1;
  *((undefined1 *) (puVar1 + 7)) = (undefined1) 0x16;
  puVar1[1] = (undefined4) param_1;
  *((undefined1 *) (puVar1 + 2)) = (undefined1) param_2;
  DAT_00725e5d = (byte) 1;
  return;
}

undefined4 CExcept_RegisterDestructorObject(undefined4 param_1, int param_2, undefined4 param_3)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  puVar1 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(0x1e));
  memclrw(puVar1, 0x1e);
  *puVar1 = (undefined4) DAT_00710b30;
  DAT_00710b30 = (uint *) puVar1;
  uVar2 = (undefined4) fn_00521c20(param_1, 1);
  uVar4 = (undefined4) uVar2;
  uVar3 = (undefined4) CABI_GetDestructorObject(param_3, 1);
  if (param_2 == 0)
  {
    *((undefined1 *) (puVar1 + 7)) = (undefined1) 1;
    puVar1[1] = (undefined4) param_1;
    puVar1[2] = (undefined4) uVar3;
  }
  else
  {
    *((undefined1 *) (puVar1 + 7)) = (undefined1) 3;
    puVar1[1] = (undefined4) param_1;
    puVar1[2] = (undefined4) uVar3;
    puVar1[3] = (undefined4) param_2;
    uVar2 = (undefined4) intconstnode(&DAT_00699c6c, param_2);
    uVar2 = (undefined4) makediadicnode(uVar4, uVar2, 0xf);
  }
  DAT_00725e5d = (byte) 1;
  return (undefined4) uVar2;
}

undefined1 CExcept_ActionNeedsDestruction(int param_1)
{
  if (param_1 != 0)
  {
    switch (*((undefined1 *) (param_1 + 0x1c)))
    {
      case 0:

      case 4:

      case 7:

      case 8:

      case 9:

      case 0x10:

      case 0x11:

      case 0x12:

      case 0x13:

      case 0x14:
        goto switchD_004a0311_caseD_0;

      case 1:

      case 3:

      case 5:

      case 0xb:

      case 0xe:

      case 0x15:
        return (undefined1) 1;

      default:
        CError_Internal(cexcept_filename, 0x182);
        switchD_004a0311_caseD_0:
      return (undefined1) 0;


      case 0xd:
        return (undefined1) 0;

      case 0x16:
        return (undefined1) (*((undefined1 *) (param_1 + 8)));

    }

  }
  return (undefined1) 0;
}

int CExcept_IsSubList(undefined4 *param_1, undefined4 *param_2)
{
  undefined4 *puVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  if (((uint) param_1) == ((uint) param_2))
  {
    return (int) 0;
  }
  iVar5 = (int) 0;
  for (puVar1 = (undefined4 *) param_1; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    iVar5 = (int) (iVar5 + 1);
  }

  iVar4 = (int) 0;
  for (puVar1 = (undefined4 *) param_2; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    iVar4 = (int) (iVar4 + 1);
  }

  iVar4 = (int) (iVar4 - iVar5);
  if (iVar4 > (-1))
  {
    iVar5 = (int) 0;
    if (iVar4 > 0)
    {
      if (iVar4 > 8)
      {
        bVar2 = (bool) 0;
        if ((iVar4 > (-1)) && (iVar4 != 0x7fffffff))
        {
          bVar2 = (bool) 1;
        }
        if (bVar2)
        {
          do
          {
            iVar5 = (int) (iVar5 + 8);
            param_2 = (undefined4 *) (*((undefined4 **) (*(*((undefined4 **) (*(*((undefined4 **) (*(*((undefined4 **) (*param_2))))))))))));
          }
          while (iVar5 < (iVar4 - 8U));
        }
      }
      for (; iVar5 < iVar4; iVar5 = (int) (iVar5 + 1))
      {
        param_2 = (undefined4 *) ((undefined4 *) (*param_2));
      }

    }
    if (((uint) param_1) != ((uint) param_2))
    {
      do
      {
        if (((((uint) param_1) == ((uint) ((undefined4 *) 0x0))) || (((uint) param_2) == ((uint) ((undefined4 *) 0x0)))) || ((cVar3 = (char) CExcept_ActionCompare((int) param_1, (int) param_2), cVar3 == '\0')))
        {
          return (int) (-1);
        }
        param_1 = (undefined4 *) ((undefined4 *) (*param_1));
        param_2 = (undefined4 *) ((undefined4 *) (*param_2));
      }
      while (((uint) param_1) != ((uint) param_2));
    }
    return (int) iVar4;
  }
  return (int) (-1);
}

bool CExcept_ActionCompare(int param_1, int param_2)
{
  bool bVar1;
  if (param_1 == param_2)
  {
    return (bool) 1;
  }
  if ((param_1 != 0) && (param_2 != 0))
  {
    if ((*((char *) (param_1 + 0x1c))) == (*((char *) (param_2 + 0x1c))))
    {
      switch (*((char *) (param_1 + 0x1c)))
      {
        case '\x01':
          return (bool) ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))));

        case '\x02':
          return (bool) ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))));

        case '\x03':
          bVar1 = (bool) 0;
          if ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))))
        {
          bVar1 = (bool) ((*((int *) (param_1 + 0xc))) == (*((int *) (param_2 + 0xc))));
        }
          return (bool) bVar1;

        case '\x04':
          return (bool) ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))));

        case '\x05':
          return (bool) ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))));

        case '\x06':
          return (bool) ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))));

        case '\a':

        case '\x11':
          bVar1 = (bool) 0;
          if ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))))
        {
          bVar1 = (bool) ((*((int *) (param_1 + 0xc))) == (*((int *) (param_2 + 0xc))));
        }
          return (bool) bVar1;

        case '\b':
          bVar1 = (bool) 0;
          if ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))))
        {
          bVar1 = (bool) ((*((int *) (param_1 + 0x10))) == (*((int *) (param_2 + 0x10))));
        }
          return (bool) bVar1;

        case '\t':
          bVar1 = (bool) 0;
          if ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))))
        {
          bVar1 = (bool) ((*((int *) (param_1 + 0xc))) == (*((int *) (param_2 + 0xc))));
        }
          return (bool) bVar1;

        case '\n':

        case '\v':
          bVar1 = (bool) 0;
          if ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))))
        {
          bVar1 = (bool) ((*((int *) (param_1 + 8))) == (*((int *) (param_2 + 8))));
        }
          return (bool) bVar1;

        case '\f':
          return (bool) ((*((int *) (param_1 + 0xc))) == (*((int *) (param_2 + 0xc))));

        case '\r':
          return (bool) ((*((int *) (param_1 + 0xc))) == (*((int *) (param_2 + 0xc))));

        case '\x0e':
          return (bool) ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))));

        case '\x0f':
          return (bool) ((*((int *) (param_1 + 8))) == (*((int *) (param_2 + 8))));

        case '\x10':
          return (bool) 1;

        case '\x12':
          return (bool) ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))));

        case '\x13':

        case '\x14':
          bVar1 = (bool) 0;
          if ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))))
        {
          bVar1 = (bool) ((*((int *) (param_1 + 0x10))) == (*((int *) (param_2 + 0x10))));
        }
          return (bool) bVar1;

        case '\x15':
          return (bool) ((*((int *) (param_1 + 4))) == (*((int *) (param_2 + 4))));

        default:
          CError_Internal(cexcept_filename, 0x14b);

      }

    }
    return (bool) 0;
  }
  return (bool) 0;
}

bool CExcept_IsCompatibleSpecificationList(undefined4 *param_1, undefined4 *param_2)
{
  undefined4 *puVar1;
  if (((uint) param_1) == ((uint) ((undefined4 *) 0x0)))
  {
    return (bool) 1;
  }
  if (((uint) param_2) == ((uint) ((undefined4 *) 0x0)))
  {
    return (bool) 0;
  }
  if (param_1[1] == 0)
  {
    return (bool) (param_2[1] == 0);
  }
  if (param_2[1] != 0)
  {
    do
    {
      puVar1 = (undefined4 *) param_1;
      if (((uint) param_2) == ((uint) ((undefined4 *) 0x0)))
      {
        return (bool) 1;
      }
      while (1)
      {
        if (((uint) puVar1) == ((uint) ((undefined4 *) 0x0)))
        {
          return (bool) 0;
        }
        if ((param_2[1] == puVar1[1]) && (param_2[2] == puVar1[2]))
          break;
        puVar1 = (undefined4 *) ((undefined4 *) (*puVar1));
      }

      param_2 = (undefined4 *) ((undefined4 *) (*param_2));
    }
    while (1);
  }
  return (bool) 1;
}

void CExcept_CompareSpecifications(undefined4 *param_1, undefined4 *param_2)
{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  puVar2 = (undefined4 *) param_2;
  for (puVar3 = (undefined4 *) param_1; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
  {
    if (((uint) puVar2) == ((uint) ((undefined4 *) 0x0)))
      goto LAB_004a0668;
    puVar2 = (undefined4 *) ((undefined4 *) (*puVar2));
  }

  if (((uint) puVar2) == ((uint) ((undefined4 *) 0x0)))
  {
    if (param_1[1] == 0)
    {
      if (param_2[1] == 0)
      {
        return;
      }
    }
    else
    {
      puVar3 = (undefined4 *) param_1;
      if (param_2[1] != 0)
      {
        while (1)
        {
          puVar2 = (undefined4 *) param_2;
          if (((uint) puVar3) == ((uint) ((undefined4 *) 0x0)))
          {
            return;
          }
          for (; (((uint) puVar2) != ((uint) ((undefined4 *) 0x0))) && ((sVar1 = (short) iscpp_typeequal(puVar3[1], puVar2[1]), (sVar1 == 0) || (puVar3[2] != puVar2[2]))); puVar2 = (undefined4 *) ((undefined4 *) (*puVar2)))
          {
          }

          if (((uint) puVar2) == ((uint) ((undefined4 *) 0x0)))
            break;
          puVar3 = (undefined4 *) ((undefined4 *) (*puVar3));
        }

      }
    }
  }
  LAB_004a0668:
  fn_0045c480(0x2819, param_1, param_2);

  return;
}

undefined4 fn_004a06d0(int param_1)
{
  undefined4 uVar1;
  uVar1 = (undefined4) 0;
  if (((*((int *) (param_1 + 10))) != 0) && ((*((int *) ((*((int *) (param_1 + 10))) + 4))) == 0))
  {
    uVar1 = (undefined4) 1;
  }
  return (undefined4) uVar1;
}

void CExcept_CheckStackRefs(undefined4 *param_1)
{
  for (; ((uint) param_1) != ((uint) ((undefined4 *) 0x0)); param_1 = (undefined4 *) ((undefined4 *) (*param_1)))
  {
    switch (*((undefined1 *) (param_1 + 7)))
    {
      case 1:
        fn_0047b230(param_1[2]);
        break;

      case 2:
        fn_0047b230(param_1[3]);
        break;

      case 3:
        fn_0047b230(param_1[2]);
        break;

      case 4:
        fn_0047b230(param_1[2]);
        break;

      case 5:
        fn_0047b230(param_1[2]);
        break;

      case 6:
        fn_0047b230(param_1[3]);
        break;

      case 7:

      case 0x11:
        fn_0047b230(param_1[2]);
        break;

      case 8:
        fn_0047b230(param_1[3]);
        break;

      case 9:
        fn_0047b230(param_1[2]);
        break;

      case 10:

      case 0xb:
        fn_0047b230(param_1[2]);
        break;

      case 0xc:
        fn_0047b230(param_1[2]);
        break;

      case 0xd:

      case 0xe:

      case 0xf:

      case 0x10:

      case 0x12:
        break;

      case 0x13:

      case 0x14:
        fn_0047b230(param_1[2]);
        fn_0047b230(param_1[3]);
        break;

      case 0x15:
        fn_0047b230(param_1[3]);
        break;

      default:
        CError_Internal(cexcept_filename, 0x97);

    }

  }

  return;
}

void CExcept_Setup(void)
{
  DAT_00710b30 = (uint *) 0;
  cexcept_uniqueobjs = (uint *) 0;
  DAT_00725e5d = (byte) 0;
  DAT_00725ed8 = (byte) 0;
  return;
}
