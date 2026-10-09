/* GC 3.0a5.2 CMiddleLayer.c. Native packed records and driver stdcall ABIs.
 * CMid names use supplied CSV plus native algorithm and caller corroboration.
 * Deferred dispatch preserves the GC1.2.5 queue architecture with five GC3 kinds.
 * Byte Boolean return, 46-byte ENode, 198-byte inline data, 38-byte pending node.
 */
#pragma pack(push,2)
typedef struct NativeExpr { unsigned int w[11]; unsigned short tail; } NativeExpr;
typedef struct NativeInline { unsigned int w[49]; unsigned short tail; } NativeInline;
/* Native GC3 CMiddleLayer.c: explicit packed32-bit address conversions. */
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef byte undefined1;
typedef ushort undefined2;
typedef uint undefined4;
typedef byte undefined;
typedef byte bool;
static uint cmid_currentstmt;
static byte cmid_restartstmt;
static byte cmid_hasforce;
static int cmid_firstfile;
static uint *cmid_dummyfuncs;
static uint *cmid_pendingclasses;
static uint *cmid_deferredinline;
static uint *cmid_pendingnodes;
static uint *cmid_objectrefs;
static char cmid_filename[] = "CMiddleLayer.c";
static char cmid_empty[] = "";
static char cmid_compute[] = "IPA Compute";
static char cmid_extension[] = ".irobj";
static char cmid_inlining[] = "IPA Inlining";
static char cmid_exceptions[] = "IPA Exceptions";
extern byte DAT_006771e4[];
extern byte DAT_00699c64[];
extern uint **DAT_00702cf8;
extern uint DAT_00702cfc;
extern uint DAT_00704908;
extern uint DAT_0070490c;
extern byte DAT_0070f1b3;
extern byte DAT_0070f1bb;
extern byte DAT_0070f1f4;
extern byte DAT_0070f1f7;
extern byte DAT_0070f208;
extern byte DAT_0070f220;
extern byte DAT_0070f229;
extern byte DAT_0070f287;
extern uint DAT_00710080;
extern uint DAT_00710140;
extern uint *DAT_00710148;
extern uint DAT_00710360;
extern uint *DAT_007107a8;
extern uint DAT_00710808;
extern uint DAT_0071080c;
extern uint DAT_00710810;
extern uint DAT_00710924;
extern uint DAT_00711b3c;
extern uint DAT_00711b40;
extern uint DAT_00711b44;
extern uint DAT_00711b70;
extern uint DAT_00711b74;
extern uint DAT_00711b78;
extern uint *DAT_00711bac;
extern uint DAT_00711bbc;
extern uint DAT_00711be0;
extern uint *DAT_00715c2c;
extern uint DAT_00715c48;
extern uint DAT_00715c4c;
extern uint DAT_00715c50;
extern uint *DAT_00716c24;
extern uint DAT_00716c9c;
extern uint DAT_00716ca0;
extern uint DAT_00716ca4;
extern uint DAT_00716ca8;
extern uint DAT_00716cfc;
extern uint DAT_00716d00;
extern uint DAT_00716d04;
extern uint DAT_00716d50;
extern uint DAT_00716ed2;
extern uint DAT_00716ed6;
extern uint DAT_0071701a;
extern byte DAT_0071701e[];
extern uint *DAT_00717284;
extern uint DAT_00717288;
extern byte DAT_0071728c;
extern byte DAT_0071728d;
extern uint DAT_0071728e;
extern uint DAT_00717292;
extern byte DAT_00725dfa;
extern byte DAT_00725e67;
extern byte DAT_00725ecb;
extern byte DAT_00725edf;
void fn_004795b0(void);
void fn_00479850(void);
undefined1 fn_004799e0(void);
void fn_00479c20(void);
void CMid_RegisterDummyCtorFunction(undefined4 param_1, undefined4 param_2);
void fn_00479ce0(undefined4 param_1, undefined4 param_2);
void fn_00479d10(undefined4 param_1);
void fn_00479d30(void);
undefined1 fn_00479f60(void);
void CMid_CompileEnded(void);
void CMid_GenerateMultiCallGraph(void);
void CMid_InitCodeMerge(void);
void CMid_GenerateCallGraphHelper(void);
void fn_0047a8b0(int param_1);
void fn_0047aa60(char param_1);
void fn_0047aaf0(int param_1);
void fn_0047acc0(void);
int fn_0047b020(int *param_1);
undefined1 CInline_DispatchNextDeferredNode(void);
void CMid_ObjectAddrRef(int param_1);
void fn_0047b5b0(uint function_object, uint definition, uint specialization);
void fn_0047b5c0(undefined4 param_1, undefined4 param_2);
void fn_0047b600(int param_1, undefined4 param_2, undefined4 *param_3, undefined4 param_4, undefined4 *param_5);
void fn_0047b6d0(int param_1);
void fn_0047b910(int param_1, undefined4 param_2, undefined4 *param_3, undefined4 param_4, char param_5, char param_6);
void fn_0047bb40(int param_1);
void fn_0047bb90(int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined1 param_5, char param_6);
int CMid_DefineThunkObject(int param_1, int param_2, int param_3, int param_4);
void CMid_DefineFunction(undefined4 *param_1);
void fn_0047c240(undefined4 *param_1);
void fn_0047c320(undefined1 *param_1);
void fn_0047c430(undefined4 *param_1);
void fn_0047c4e0(char *param_1);
undefined1 fn_0047c510(int param_1, undefined4 param_2);
void fn_0047c680(int param_1, int param_2);
void fn_0047c7d0(undefined1 *param_1);
void fn_0047c880(undefined4 *param_1);
void fn_0047cd90(char *param_1);
undefined4 fn_0047cde0(int param_1);
undefined4 fn_0047ce20(int param_1);
void fn_0047ce70(int param_1);
void fn_0047cf40(int param_1, int *param_2);
undefined4 fn_0047d080(int param_1);
void CMid_SetupIPA(char param_1);
void CMid_Cleanup(void);
void CMid_Setup(void);
extern uint CCallGraph_AddFunction();
extern uint CClass_GeneratePendingVTables();
extern uint CError_Internal();
extern uint CError_LongJump();
extern uint CError_ReportError();
extern uint CError_Warning();
extern uint CFunc_AppendStatement();
extern uint CFunc_FuncGenSetup();
extern uint CMangler_ThunkName();
extern uint CScope_RestoreScope();
extern uint CScope_SetFunctionScope();
extern uint CodeGen_GenThunk();
extern uint CodeGen_Generator();
extern uint CompilerTools_AllocatePool();
extern uint __stdcall fn_0041faa0(uint arg0, uint arg1);
extern uint __stdcall fn_0041faf0(uint arg0, uint arg1, uint arg2, uint arg3);
extern uint __stdcall fn_00420150(uint arg0, uint arg1, uint arg2);
extern uint __stdcall fn_00420190(uint arg0);
extern uint __stdcall fn_00420590(uint arg0, uint arg1, uint arg2, uint arg3);
extern uint __stdcall fn_00420630(uint arg0, uint arg1, uint arg2);
extern uint __stdcall fn_004206c0(uint arg0, uint arg1, uint arg2, uint arg3);
extern uint __stdcall fn_00420720(uint arg0, uint arg1);
extern uint __stdcall fn_00432340(uint arg0);
extern uint fn_00447700();
extern uint fn_00447910();
extern uint fn_0044d200();
extern uint fn_0044d580();
extern uint fn_0044d590();
extern uint fn_0044d730();
extern uint fn_0044d740();
extern uint fn_0044d7d0();
extern uint fn_0044d7f0();
extern uint fn_0044d810();
extern uint fn_0044d850();
extern uint fn_0044dd70();
extern uint fn_0044de10();
extern uint fn_0044dfb0();
extern uint fn_0044ea60();
extern uint fn_00452f10();
extern uint fn_00452f60();
extern uint fn_004531a0();
extern uint fn_00453290();
extern uint fn_004554b0();
extern uint fn_00455850();
extern uint fn_00456a50();
extern uint __stdcall fn_004587b0(uint arg0, uint arg1, uint arg2);
extern uint __stdcall fn_004587e0(uint arg0, uint arg1, uint arg2);
extern uint __stdcall fn_00458a70(uint arg0, uint arg1, uint arg2);
extern uint __stdcall fn_00458aa0(uint arg0, uint arg1, uint arg2);
extern uint fn_0045a1e0();
extern uint fn_00462e30();
extern uint fn_0046c550();
extern uint fn_0046c6e0();
extern uint fn_0046c730();
extern uint fn_0046c7b0();
extern uint fn_0046c800();
extern uint fn_0049c710();
extern uint fn_004a06f0();
extern uint fn_004bac40();
extern uint fn_004bad90();
extern uint fn_004bafe0();
extern uint fn_004c4190();
extern uint fn_004c4480();
extern uint fn_004c4ad0();
extern uint fn_004c4c40();
extern uint fn_004e0df0();
extern uint fn_004e1420();
extern uint fn_00509f00();
extern uint fn_00514e20();
extern uint fn_005243d0();
extern uint fn_00524500();
extern uint fn_00524750();
extern uint fn_00524820();
extern uint fn_00524ae0();
extern uint fn_0052df40();
extern uint fn_0052eee0();
extern uint fn_0052ef30();
extern uint fn_00530810();
extern uint fn_00537ee0();
extern uint fn_0053eae0();
extern uint fn_0053ebf0();
extern uint fn_0053ed70();
extern uint fn_0053ee10();
extern uint fn_00543c00();
extern uint fn_00545580();
extern uint fn_00545830();
extern uint fn_00547a20();
extern uint fn_00547e90();
extern uint fn_00547ed0();
extern uint fn_005480b0();
extern uint fn_00548e50();
extern uint fn_00549de0();
extern uint fn_00554600();
extern uint fn_00554630();
extern uint fn_00554650();
extern uint fn_00556b70();
extern uint fn_0055a640();
extern uint fn_0055bc20();
extern uint fn_0055bc70();
extern uint fn_0055c750();
extern uint fn_00593320();
extern uint fn_005a0e60();
extern uint fn_005a0f80();
extern uint fn_005a12c0();
extern uint fn_005a1310();
extern uint fn_005a13b0();
extern uint fn_005a1510();
extern uint fn_005a1780();
extern uint fn_005a17d0();
extern uint fn_005a1820();
extern uint fn_005a1840();
extern uint fn_005a1b90();
extern uint fn_005a1f80();
extern uint fn_005a3450();
extern uint galloc();
extern uint memclrw();
extern uint memcpy();
extern uint newlabel();
void fn_004795b0(void)
{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  undefined4 in_EAX;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  if ((DAT_00725ecb != '\0') && (DAT_0070f1f7 == '\0'))
  {
    return;
  }
  if ((*((char *) (DAT_00710360 + 600))) != '\0')
  {
    fn_00479850();
    return;
  }
  DAT_0070f1bb = (byte) 0;
  for (puVar1 = (undefined4 *) DAT_00716c24; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    if (((*((ushort *) (puVar1[1] + 0x1a))) & 4) == 0)
    {
      iVar2 = (int) puVar1[1];
      cVar3 = (char) fn_00453290(*((undefined4 *) (iVar2 + 0x10)), *((undefined4 *) (iVar2 + 0x14)), 0);
      fn_0047b910((int) iVar2, (undefined4) 0, (undefined4 *) 0, (undefined4) (*((undefined4 *) ((*((int *) (iVar2 + 0x10))) + 2))), (char) (cVar3 != '\0'), (char) 0);
    }
  }

  DAT_00716c24 = (uint *) ((undefined4 *) 0x0);
  fn_00479850();
  fn_0047acc0();
  fn_00479850();
  puVar1 = (undefined4 *) DAT_00715c2c;
  if (DAT_00725e67 == '\0')
  {
    for (; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      iVar2 = (int) puVar1[1];
      if (((*((char *) (iVar2 + 2))) != '\x03') && ((*((char *) (iVar2 + 2))) != '\x04'))
      {
        CError_Internal(cmid_filename, 0x166);
      }
      if (((*((uint *) (iVar2 + 0x14))) & 0x800000) == 0)
      {
        CError_Internal(cmid_filename, 0x167);
      }
      puVar5 = (undefined4 *) (*((undefined4 **) (iVar2 + 0x40)));
      *((ushort *) (iVar2 + 0x1a)) = (ushort) ((*((ushort *) (iVar2 + 0x1a))) | 4);
      CodeGen_GenThunk(iVar2, *puVar5, puVar5[1], puVar5[2], puVar5[3]);
    }

  }
  else
  {
    for (; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      CCallGraph_AddFunction(puVar1[1]);
    }

  }
  DAT_00715c2c = (uint *) ((undefined4 *) 0x0);
  puVar1 = (undefined4 *) (&DAT_00710148);
  puVar5 = (undefined4 *) DAT_00710148;
  do
  {
    if (((uint) puVar5) == ((uint) ((undefined4 *) 0x0)))
    {
      uVar4 = (undefined4) 0;
      if ((DAT_00725e67 != '\0') && ((DAT_00725ecb == '\0') || (DAT_0070f1f7 != '\0')))
      {
        DAT_00725e67 = (byte) '\0';
        fn_00537ee0();
        fn_00420150((uint) DAT_00716ed2, (uint) cmid_compute, (uint) cmid_empty);
        fn_005a0f80();
        fn_005a0e60();
        if (DAT_00725edf == '\x02')
        {
          fn_00479d30();
        }
        else
        {
          fn_0047aa60((char) 0);
          CMid_GenerateCallGraphHelper();
        }
      }
      return;
    }
    iVar2 = (int) puVar5[1];
    if (((*((ushort *) (iVar2 + 0x1a))) & 2) != 0)
    {
      switch (*((undefined1 *) (iVar2 + 2)))
      {
        default:
          iVar6 = (int) 0;
          break;

        case 3:

        case 4:
          CError_Internal(cmid_filename, 0x176);

        case 0:
          iVar6 = (int) (*((int *) (iVar2 + 0x4c)));

      }

      if (iVar6 == 0)
      {
        CError_Internal(cmid_filename, 0x62d);
      }
      fn_0047b910((int) iVar2, (undefined4) (*((undefined4 *) (iVar6 + 0xc))), (undefined4 *) (*((undefined4 *) (iVar6 + 0x10))), (undefined4) (*((undefined4 *) (iVar6 + 0x14))), (char) (*((undefined1 *) (iVar6 + 0x18))), (char) 0);
      *puVar1 = (undefined4) (*((undefined4 *) (*puVar1)));
      puVar5 = (undefined4 *) puVar1;
    }
    puVar1 = (undefined4 *) puVar5;
    puVar5 = (undefined4 *) ((undefined4 *) (*puVar5));
  }
  while (1);
}

void fn_00479850(void)
{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  char cVar4;
  undefined4 uVar5;
  bool bVar6;
  do
  {
    cVar4 = (char) fn_004799e0();
    bVar6 = (bool) (cVar4 != '\0');
    if (((*((char *) (DAT_00710360 + 600))) == '\0') && ((cVar4 = (char) CClass_GeneratePendingVTables(), cVar4 != '\0')))
    {
      puVar3 = (undefined4 *) cmid_pendingnodes;
      if (DAT_00725ecb == '\0')
      {
        for (; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
        {
          if ((*((char *) (puVar3 + 9))) == '\0')
          {
            bVar6 = (bool) 0;
            goto LAB_004798a8;
          }
        }

      }
      bVar6 = (bool) 1;
      LAB_004798a8:
      if (bVar6)
      {
        if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
        {
          for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
          {
            piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
            piVar2 = (int *) ((int *) (*piVar1));
            cVar4 = (char) (*((char *) (((int) piVar2) + 0x1d)));
            while (cVar4 == '\0')
            {
              *piVar1 = (int) (*piVar2);
              piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
              piVar2 = (int *) ((int *) (*piVar1));
              cVar4 = (char) (*((char *) (((int) piVar2) + 0x1d)));
            }

          }

          cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
        }
        fn_00514e20();
        fn_0046c550();
      }

      bVar6 = (bool) 1;
    }
    uVar5 = (undefined4) fn_005a1840();
    if (((char) uVar5) != '\0')
    {
      puVar3 = (undefined4 *) cmid_pendingnodes;
      if (DAT_00725ecb == '\0')
      {
        for (; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
        {
          if ((*((char *) (puVar3 + 9))) == '\0')
          {
            bVar6 = (bool) 0;
            goto LAB_00479948;
          }
        }

      }
      bVar6 = (bool) 1;
      LAB_00479948:
      if (bVar6)
      {
        if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
        {
          for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
          {
            piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
            piVar2 = (int *) ((int *) (*piVar1));
            cVar4 = (char) (*((char *) (((int) piVar2) + 0x1d)));
            while (cVar4 == '\0')
            {
              *piVar1 = (int) (*piVar2);
              piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
              piVar2 = (int *) ((int *) (*piVar1));
              cVar4 = (char) (*((char *) (((int) piVar2) + 0x1d)));
            }

          }

          cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
        }
        fn_00514e20();
        uVar5 = (undefined4) fn_0046c550();
      }

      bVar6 = (bool) 1;
    }
    if ((!bVar6) || ((DAT_00725ecb != '\0') && (DAT_0070f1f7 == '\0')))
    {
      return;
    }
  }
  while (1);
}

undefined1 fn_004799e0(void)
{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  undefined4 *puVar4;
  char cVar5;
  undefined1 uVar6;
  uVar6 = (undefined1) 0;
  puVar4 = (undefined4 *) cmid_pendingnodes;
  if (DAT_00725ecb == '\0')
  {
    for (; ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
    {
      if ((*((char *) (puVar4 + 9))) == '\0')
      {
        bVar3 = (bool) 0;
        goto LAB_00479a0a;
      }
    }

  }
  bVar3 = (bool) 1;
  LAB_00479a0a:
  if (bVar3)
  {
    if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
    {
      for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
      {
        piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
        piVar2 = (int *) ((int *) (*piVar1));
        cVar5 = (char) (*((char *) (((int) piVar2) + 0x1d)));
        while (cVar5 == '\0')
        {
          *piVar1 = (int) (*piVar2);
          piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
          piVar2 = (int *) ((int *) (*piVar1));
          cVar5 = (char) (*((char *) (((int) piVar2) + 0x1d)));
        }

      }

      cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
    }
    fn_00514e20();
    fn_0046c550();
  }

  if (((uint) cmid_dummyfuncs) != ((uint) ((undefined4 *) 0x0)))
  {
    uVar6 = (undefined1) 1;
    puVar4 = (undefined4 *) cmid_dummyfuncs;
    while (cmid_dummyfuncs = (uint *) puVar4, ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)))
    {
      cmid_dummyfuncs = (uint *) ((undefined4 *) (*puVar4));
      if (puVar4[3] == 0)
      {
        fn_00524820(puVar4[1], puVar4[2]);
      }
      else
      {
        fn_00524ae0(puVar4[1], puVar4[3]);
      }
      fn_0046c6e0(puVar4, 0x10);
      puVar4 = (undefined4 *) cmid_pendingnodes;
      if (DAT_00725ecb == '\0')
      {
        for (; ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
        {
          if ((*((char *) (puVar4 + 9))) == '\0')
          {
            bVar3 = (bool) 0;
            goto LAB_00479ad9;
          }
        }

      }
      bVar3 = (bool) 1;
      LAB_00479ad9:
      puVar4 = (undefined4 *) cmid_dummyfuncs;

      if (bVar3)
      {
        if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
        {
          for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
          {
            piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
            piVar2 = (int *) ((int *) (*piVar1));
            cVar5 = (char) (*((char *) (((int) piVar2) + 0x1d)));
            while (cVar5 == '\0')
            {
              *piVar1 = (int) (*piVar2);
              piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
              piVar2 = (int *) ((int *) (*piVar1));
              cVar5 = (char) (*((char *) (((int) piVar2) + 0x1d)));
            }

          }

          cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
        }
        fn_00514e20();
        fn_0046c550();
        puVar4 = (undefined4 *) cmid_dummyfuncs;
      }
    }

  }
  cVar5 = (char) CInline_DispatchNextDeferredNode();
  do
  {
    if (cVar5 == '\0')
    {
      return (undefined1) uVar6;
    }
    puVar4 = (undefined4 *) cmid_pendingnodes;
    if (DAT_00725ecb == '\0')
    {
      for (; ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
      {
        if ((*((char *) (puVar4 + 9))) == '\0')
        {
          bVar3 = (bool) 0;
          goto LAB_00479b78;
        }
      }

    }
    bVar3 = (bool) 1;
    LAB_00479b78:
    if (bVar3)
    {
      if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
      {
        for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
        {
          piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
          piVar2 = (int *) ((int *) (*piVar1));
          cVar5 = (char) (*((char *) (((int) piVar2) + 0x1d)));
          while (cVar5 == '\0')
          {
            *piVar1 = (int) (*piVar2);
            piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
            piVar2 = (int *) ((int *) (*piVar1));
            cVar5 = (char) (*((char *) (((int) piVar2) + 0x1d)));
          }

        }

        cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
      }
      fn_00514e20();
      fn_0046c550();
    }

    uVar6 = (undefined1) 1;
    cVar5 = (char) CInline_DispatchNextDeferredNode();
  }
  while (1);
}

void fn_00479c20(void)
{
  char cVar1;
  int *piVar2;
  int *piVar3;
  bool bVar4;
  undefined4 *puVar5;
  puVar5 = (undefined4 *) cmid_pendingnodes;
  if (DAT_00725ecb == '\0')
  {
    for (; ((uint) puVar5) != ((uint) ((undefined4 *) 0x0)); puVar5 = (undefined4 *) ((undefined4 *) (*puVar5)))
    {
      if ((*((char *) (puVar5 + 9))) == '\0')
      {
        bVar4 = (bool) 0;
        goto LAB_00479c48;
      }
    }

  }
  bVar4 = (bool) 1;
  LAB_00479c48:
  if (!bVar4)
  {
    return;
  }

  if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
  {
    for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
    {
      piVar2 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
      piVar3 = (int *) ((int *) (*piVar2));
      cVar1 = (char) (*((char *) (((int) piVar3) + 0x1d)));
      while (cVar1 == '\0')
      {
        *piVar2 = (int) (*piVar3);
        piVar2 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
        piVar3 = (int *) ((int *) (*piVar2));
        cVar1 = (char) (*((char *) (((int) piVar3) + 0x1d)));
      }

    }

    cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
  }
  fn_00514e20();
  fn_0046c550();
  return;
}

void CMid_RegisterDummyCtorFunction(undefined4 param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  puVar1 = (undefined4 *) ((undefined4 *) fn_0046c730(0x10));
  *puVar1 = (undefined4) cmid_dummyfuncs;
  puVar1[1] = (undefined4) param_1;
  puVar1[2] = (undefined4) param_2;
  puVar1[3] = (undefined4) 0;
  cmid_dummyfuncs = (uint *) puVar1;
  return;
}

void fn_00479ce0(undefined4 param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  puVar1 = (undefined4 *) ((undefined4 *) fn_0046c730(0x10));
  *puVar1 = (undefined4) cmid_dummyfuncs;
  puVar1[1] = (undefined4) param_1;
  puVar1[2] = (undefined4) 0;
  puVar1[3] = (undefined4) param_2;
  cmid_dummyfuncs = (uint *) puVar1;
  return;
}

void fn_00479d10(undefined4 param_1)
{
  undefined4 *puVar1;
  puVar1 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
  *puVar1 = (undefined4) cmid_pendingclasses;
  puVar1[1] = (undefined4) param_1;
  cmid_pendingclasses = (uint *) puVar1;
  return;
}

void fn_00479d30(void)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 local_110;
  undefined1 local_10c[260];
  undefined4 local_8;
  fn_004bac40();
  iVar1 = (int) fn_00420590((uint) DAT_00716ed2, (uint) DAT_00702cfc, (uint) 0, (uint) (&local_8));
  if (iVar1 == 0)
  {
    iVar1 = (int) fn_004206c0((uint) DAT_00716ed2, (uint) local_8, (uint) 0, (uint) (&local_110));
    if (iVar1 == 0)
      goto LAB_00479d80;
  }
  CError_Internal(cmid_filename, 0xaa2);
  LAB_00479d80:
  memcpy(local_110, *DAT_00702cf8, DAT_00702cfc);

  iVar1 = (int) fn_00420720((uint) DAT_00716ed2, (uint) local_8);
  if (iVar1 != 0)
  {
    CError_Internal(cmid_filename, 0xaa7);
  }
  iVar1 = (int) fn_00458aa0((uint) DAT_00716ed2, (uint) DAT_0071701a, (uint) local_10c);
  if (iVar1 != 0)
  {
    CError_ReportError(0x2878, &DAT_0071701e);
    return;
  }
  iVar1 = (int) fn_0044d590(local_10c, cmid_extension, 0);
  if (iVar1 != 0)
  {
    fn_00462e30();
    CError_ReportError(0x2878, local_10c);
    return;
  }
  iVar1 = (int) fn_0044d7f0(local_10c, &uStack_114, 0x43574945, 0x49524f62);
  if (iVar1 == 0)
  {
    iVar1 = (int) fn_004206c0((uint) DAT_00716ed2, (uint) local_8, (uint) 0, (uint) (&local_110));
    if (iVar1 == 0)
    {
      iVar1 = (int) fn_00420630((uint) DAT_00716ed2, (uint) local_8, (uint) (&uStack_118));
      if (iVar1 == 0)
      {
        iVar1 = (int) fn_0044d850(uStack_114, local_110, uStack_118);
        if (iVar1 == 0)
        {
          fn_0044d730(uStack_114);
          fn_00420720((uint) DAT_00716ed2, (uint) local_8);
          return;
        }
        fn_00462e30();
        uVar2 = (undefined4) fn_0044de10(iVar1);
        uVar2 = (undefined4) fn_0044d580(local_10c, uVar2);
        CError_ReportError(0x2904, uVar2);
        return;
      }
    }
    CError_LongJump();
    return;
  }
  fn_00462e30();
  uVar2 = (undefined4) fn_0044de10(iVar1);
  uVar2 = (undefined4) fn_0044d580(local_10c, uVar2);
  CError_ReportError(0x2904, uVar2);
  return;
}

undefined1 fn_00479f60(void)
{
  return (undefined1) 0;
}

void CMid_CompileEnded(void)
{
  int iVar1;
  CMid_GenerateMultiCallGraph();
  if ((DAT_00725edf != '\0') && (cmid_firstfile != (-1)))
  {
    fn_004c4c40();
    iVar1 = (int) fn_004587e0((uint) DAT_00716ed2, (uint) cmid_firstfile, (uint) (&DAT_00716ed6));
    if (iVar1 != 0)
    {
      CError_Internal(cmid_filename, 0xa75);
    }
    return;
  }
  return;
}

void CMid_GenerateMultiCallGraph(void)
{
  char cVar1;
  int *piVar2;
  int *piVar3;
  bool bVar4;
  bool bVar5;
  undefined4 *puVar6;
  char cVar7;
  short sVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined4 uVar12;
  char *pcVar13;
  int iVar14;
  char *pcVar15;
  char *pcVar16;
  char *pcVar17;
  undefined1 local_36c[4];
  int local_368;
  undefined4 uStack_364;
  int local_360;
  undefined4 uStack_35c;
  undefined1 auStack_358[260];
  undefined4 uStack_254;
  undefined4 uStack_250;
  undefined1 auStack_24c[272];
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  DAT_00725e67 = (byte) 0;
  DAT_00725edf = (byte) '\0';
  local_360 = (int) fn_0044dfb0();
  sVar8 = (short) fn_00432340((uint) local_36c);
  if (sVar8 != 0)
  {
    CError_Internal(cmid_filename, 0x9ac);
  }
  iVar9 = (int) fn_0041faa0((uint) DAT_00716ed2, (uint) (&local_368));
  if (iVar9 != 0)
  {
    CError_Internal(cmid_filename, 0x9b0);
  }
  iVar9 = (int) 0;
  if (local_368 > 0)
  {
    do
    {
      uVar10 = (uint) fn_0044dfb0();
      if ((local_360 + 0x3cU) < uVar10)
      {
        local_360 = (int) fn_0044dfb0();
        iVar11 = (int) fn_00420190((uint) DAT_00716ed2);
        if (iVar11 != 0)
        {
          fn_0045a1e0();
        }
      }
      iVar11 = (int) fn_0041faf0((uint) DAT_00716ed2, (uint) iVar9, (uint) 0, (uint) auStack_24c);
      if (iVar11 != 0)
      {
        CError_Internal(cmid_filename, 0x9c3);
      }
      uVar12 = (undefined4) fn_0044d580(auStack_24c);
      pcVar13 = (char *) ((char *) fn_0044d200(uVar12));
      iVar11 = (int) 7;
      pcVar16 = (char *) cmid_extension;
      do
      {
        pcVar15 = (char *) pcVar13;
        pcVar17 = (char *) pcVar16;
        if (iVar11 == 0)
          break;
        iVar11 = (int) (iVar11 - 1);
        pcVar17 = (char *) (pcVar16 + 1);
        pcVar15 = (char *) (pcVar13 + 1);
        cVar1 = (char) (*pcVar16);
        cVar7 = (char) (*pcVar13);
        pcVar13 = (char *) pcVar15;
        pcVar16 = (char *) pcVar17;
      }
      while (cVar7 == cVar1);
      if (pcVar15[-1] == pcVar17[-1])
      {
        iStack_18 = (int) 0;
        DAT_00725edf = (byte) '\x02';
        iVar11 = (int) fn_0044d7d0(auStack_24c, &iStack_18);
        if ((((iVar11 == 0) && ((iVar11 = (int) fn_0044d740(iStack_18, &uStack_364), iVar11 == 0))) && ((iVar11 = (int) fn_0046c800(uStack_364), iVar11 != 0))) && ((iVar14 = (int) fn_0044d810(iStack_18, iVar11, uStack_364), iVar14 == 0)))
        {
          fn_0044d730(iStack_18);
          if (cmid_firstfile == (-1))
          {
            cmid_firstfile = (int) iVar9;
          }
          fn_004bad90(iVar11, iVar9, 1, cmid_firstfile == iVar9);
          puVar6 = (undefined4 *) cmid_pendingnodes;
          if (DAT_00725ecb == '\0')
          {
            for (; ((uint) puVar6) != ((uint) ((undefined4 *) 0x0)); puVar6 = (undefined4 *) ((undefined4 *) (*puVar6)))
            {
              if ((*((char *) (puVar6 + 9))) == '\0')
              {
                bVar4 = (bool) 0;
                goto LAB_0047a3c9;
              }
            }

          }
          bVar4 = (bool) 1;
          LAB_0047a3c9:
          if (bVar4)
          {
            if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
            {
              for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
              {
                piVar2 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
                piVar3 = (int *) ((int *) (*piVar2));
                cVar7 = (char) (*((char *) (((int) piVar3) + 0x1d)));
                while (cVar7 == '\0')
                {
                  *piVar2 = (int) (*piVar3);
                  piVar2 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
                  piVar3 = (int *) ((int *) (*piVar2));
                  cVar7 = (char) (*((char *) (((int) piVar3) + 0x1d)));
                }

              }

              cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
            }
            fn_00514e20();
            fn_0046c550();
          }

          fn_0046c7b0(iVar11);
        }
        else
        {
          if (iStack_18 != 0)
          {
            fn_0044d730(iStack_18);
          }
          uVar12 = (undefined4) fn_0044d580(auStack_24c);
          CError_ReportError(0x27a7, uVar12);
        }
      }
      else
        if (auStack_24c[270] != '\0')
      {
        uStack_254 = (undefined4) 0;
        bVar4 = (bool) 1;
        iVar11 = (int) fn_004587b0((uint) DAT_00716ed2, (uint) iVar9, (uint) (&uStack_250));
        if (iVar11 != 0)
        {
          uVar12 = (undefined4) fn_0044d580(auStack_24c, iVar9);
          CError_ReportError(0x2917, iVar11, uVar12);
          return;
        }
        iVar11 = (int) fn_004206c0((uint) DAT_00716ed2, (uint) uStack_250, (uint) 1, (uint) (&iStack_14));
        if (iVar11 != 0)
        {
          CError_Internal(cmid_filename, 0xa07);
        }
        iVar11 = (int) fn_00420630((uint) DAT_00716ed2, (uint) uStack_250, (uint) (&uStack_35c));
        if (iVar11 != 0)
        {
          CError_Internal(cmid_filename, 0xa0b);
        }
        if (((iStack_14 == 0) || ((cVar7 = (char) fn_004bafe0(iStack_14, uStack_35c), cVar7 == '\0'))) && ((iVar11 = (int) fn_00458aa0((uint) DAT_00716ed2, (uint) iVar9, (uint) auStack_358), (iVar11 == 0) && ((iVar11 = (int) fn_0044d590(auStack_358, cmid_extension, 0), (iVar11 == 0) && ((iVar11 = (int) fn_0044dd70(auStack_358), iVar11 == 0)))))))
        {
          iStack_1c = (int) 0;
          iVar11 = (int) fn_0044d7d0(auStack_358, &iStack_1c);
          if ((iVar11 == 0) && ((iVar11 = (int) fn_0044d740(iStack_1c, &uStack_254), ((iVar11 == 0) && ((iStack_14 = (int) fn_0046c800(uStack_254), iStack_14 != 0))) && ((iVar11 = (int) fn_0044d810(iStack_1c, iStack_14, uStack_254), iVar11 == 0)))))
          {
            fn_0044d730(iStack_1c);
            uStack_35c = (undefined4) uStack_254;
            bVar4 = (bool) 0;
            iVar11 = (int) fn_00458a70((uint) DAT_00716ed2, (uint) iVar9, (uint) uStack_250);
            if (iVar11 != 0)
            {
              CError_Internal(cmid_filename, 0xa21);
            }
          }
          else
          {
            if (iStack_1c != 0)
            {
              fn_0044d730(iStack_1c);
            }
            CError_Internal(cmid_filename, 0xa27);
          }
        }
        if ((iStack_14 != 0) && ((cVar7 = (char) fn_004bafe0(iStack_14, uStack_35c), cVar7 != '\0')))
        {
          DAT_00725edf = (byte) '\x02';
          if (cmid_firstfile == (-1))
          {
            cmid_firstfile = (int) iVar9;
          }
          fn_004bad90(iStack_14, iVar9, 1, cmid_firstfile == iVar9);
          puVar6 = (undefined4 *) cmid_pendingnodes;
          if (DAT_00725ecb == '\0')
          {
            for (; ((uint) puVar6) != ((uint) ((undefined4 *) 0x0)); puVar6 = (undefined4 *) ((undefined4 *) (*puVar6)))
            {
              if ((*((char *) (puVar6 + 9))) == '\0')
              {
                bVar5 = (bool) 0;
                goto LAB_0047a218;
              }
            }

          }
          bVar5 = (bool) 1;
          LAB_0047a218:
          if (bVar5)
          {
            if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
            {
              for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
              {
                piVar2 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
                piVar3 = (int *) ((int *) (*piVar2));
                cVar7 = (char) (*((char *) (((int) piVar3) + 0x1d)));
                while (cVar7 == '\0')
                {
                  *piVar2 = (int) (*piVar3);
                  piVar2 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
                  piVar3 = (int *) ((int *) (*piVar2));
                  cVar7 = (char) (*((char *) (((int) piVar3) + 0x1d)));
                }

              }

              cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
            }
            fn_00514e20();
            fn_0046c550();
          }

        }
        if (bVar4)
        {
          iVar11 = (int) fn_00458a70((uint) DAT_00716ed2, (uint) iVar9, (uint) uStack_250);
          if (iVar11 != 0)
          {
            CError_Internal(cmid_filename, 0xa3f);
          }
        }
        else
        {
          fn_0046c7b0(iStack_14);
        }
      }
      iVar9 = (int) (iVar9 + 1);
    }
    while (iVar9 < local_368);
  }
  if (DAT_00725edf != '\0')
  {
    DAT_0070f1f4 = (byte) 0;
    CMid_InitCodeMerge();
    fn_00420150((uint) DAT_00716ed2, (uint) cmid_compute, (uint) cmid_empty);
    fn_005a0f80();
    fn_005a0e60();
    CMid_GenerateCallGraphHelper();
    return;
  }
  return;
}

void CMid_InitCodeMerge(void)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte state_a[56];
  byte state_b[56];
  puVar7 = (undefined4 *) ((undefined4 *) 0x0);
  puVar8 = (undefined4 *) DAT_00711bac;
  while (((uint) puVar8) != ((uint) ((undefined4 *) 0x0)))
  {
    if ((*((char *) (((int) puVar8) + 0x1d))) == '\0')
    {
      puVar8 = (undefined4 *) ((undefined4 *) (*puVar8));
    }
    else
      if (((uint) puVar7) == ((uint) ((undefined4 *) 0x0)))
    {
      puVar7 = (undefined4 *) puVar8;
      puVar8 = (undefined4 *) ((undefined4 *) (*puVar8));
    }
    else
    {
      fn_005a1310(state_a, puVar7);
      fn_005a1310(state_b, puVar8);
      piVar6 = (int *) ((int *) (*(*((int **) state_a))));
      piVar4 = (int *) (*((int **) state_a));
      while (piVar3 = (int *) piVar6, ((uint) piVar3) != ((uint) ((int *) 0x0)))
      {
        piVar4 = (int *) piVar3;
        piVar6 = (int *) ((int *) (*piVar3));
      }

      *piVar4 = (int) (*((int *) state_b));
      if (((uint) (*((uint **) (state_b + 14)))) != ((uint) ((undefined4 *) 0x0)))
      {
        if (((uint) (*((uint **) (state_a + 14)))) == ((uint) ((undefined4 *) 0x0)))
        {
          *((uint **) (state_a + 14)) = (uint *) (*((uint **) (state_b + 14)));
        }
        else
        {
          puVar5 = (undefined4 *) ((undefined4 *) (*(*((uint **) (state_a + 14)))));
          puVar1 = (undefined4 *) (*((uint **) (state_a + 14)));
          while (puVar2 = (undefined4 *) puVar5, ((uint) puVar2) != ((uint) ((undefined4 *) 0x0)))
          {
            puVar1 = (undefined4 *) puVar2;
            puVar5 = (undefined4 *) ((undefined4 *) (*puVar2));
          }

          *puVar1 = (undefined4) (*((uint **) (state_b + 14)));
        }
      }
      fn_005a12c0(puVar7, state_a);
      puVar1 = (undefined4 *) ((undefined4 *) (*puVar8));
      fn_005a13b0(puVar8);
      puVar8 = (undefined4 *) puVar1;
    }
  }

  return;
}

void CMid_GenerateCallGraphHelper(void)
{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  bool bVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  uint uVar11;
  uint uStack_14;
  DAT_00711bbc = (uint) fn_0044dfb0();
  fn_00420150((uint) DAT_00716ed2, (uint) cmid_inlining, (uint) cmid_empty);
  fn_00545580();
  DAT_00710140 = (uint) fn_0044dfb0();
  fn_00420150((uint) DAT_00716ed2, (uint) cmid_exceptions, (uint) cmid_empty);
  iVar6 = (int) fn_00420190((uint) DAT_00716ed2);
  if (iVar6 != 0)
  {
    fn_0045a1e0();
  }
  fn_0049c710();
  iVar6 = (int) fn_0044dfb0();
  uStack_14 = (uint) 0;
  DAT_00710080 = (uint) iVar6;
  puVar9 = (undefined4 *) DAT_00711bac;
  for (puVar1 = (undefined4 *) DAT_00711bac; DAT_00711bac = (uint *) puVar9, ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    if (((*((char *) (puVar1 + 7))) == '\x01') && ((cVar5 = (char) fn_005a1780(puVar1), cVar5 != '\0')))
    {
      uStack_14 = (uint) (uStack_14 + 1);
    }
    puVar9 = (undefined4 *) DAT_00711bac;
  }

  uVar11 = (uint) 0x65;
  if (((uint) puVar9) != ((uint) ((undefined4 *) 0x0)))
  {
    uVar10 = (uint) 0;
    do
    {
      cVar5 = (char) fn_005a1780(puVar9);
      if (cVar5 != '\0')
      {
        if ((*((char *) (puVar9 + 7))) == '\x01')
        {
          uVar7 = (uint) fn_0044dfb0();
          if ((iVar6 + 0x3cU) < uVar7)
          {
            iVar6 = (int) fn_0044dfb0();
            iVar8 = (int) fn_00420190((uint) DAT_00716ed2);
            if (iVar8 != 0)
            {
              fn_0045a1e0();
            }
            if ((uVar10 / uStack_14) != uVar11)
            {
              uVar11 = (uint) (uVar10 / uStack_14);
            }
          }
          uVar10 = (uint) (uVar10 + 100);
        }
        fn_0047a8b0((int) puVar9);
        puVar1 = (undefined4 *) cmid_pendingnodes;
        if (DAT_00725ecb == '\0')
        {
          for (; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
          {
            if ((*((char *) (puVar1 + 9))) == '\0')
            {
              bVar4 = (bool) 0;
              goto LAB_0047a7da;
            }
          }

        }
        bVar4 = (bool) 1;
        LAB_0047a7da:
        if (bVar4)
        {
          if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
          {
            for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
            {
              piVar2 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
              piVar3 = (int *) ((int *) (*piVar2));
              cVar5 = (char) (*((char *) (((int) piVar3) + 0x1d)));
              while (cVar5 == '\0')
              {
                *piVar2 = (int) (*piVar3);
                piVar2 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
                piVar3 = (int *) ((int *) (*piVar2));
                cVar5 = (char) (*((char *) (((int) piVar3) + 0x1d)));
              }

            }

            cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
          }
          fn_00514e20();
          fn_0046c550();
        }

      }
      puVar9 = (undefined4 *) ((undefined4 *) (*puVar9));
    }
    while (((uint) puVar9) != ((uint) ((undefined4 *) 0x0)));
  }
  return;
}

void fn_0047a8b0(int param_1)
{
  ushort *puVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  puVar1 = (ushort *) ((ushort *) ((*((int *) (param_1 + 8))) + 0x1a));
  *puVar1 = (ushort) ((*puVar1) | 6);
  switch (*((undefined1 *) (param_1 + 0x1c)))
  {
    case 1:
      fn_0047aaf0((int) param_1);
      break;

    case 2:
      iVar3 = (int) (*((int *) (param_1 + 8)));
      if (((*((char *) (iVar3 + 2))) != '\x03') && ((*((char *) (iVar3 + 2))) != '\x04'))
    {
      CError_Internal(cmid_filename, 0x166);
    }
      if (((*((uint *) (iVar3 + 0x14))) & 0x800000) == 0)
    {
      CError_Internal(cmid_filename, 0x167);
    }
      puVar8 = (undefined4 *) (*((undefined4 **) (iVar3 + 0x40)));
      *((ushort *) (iVar3 + 0x1a)) = (ushort) ((*((ushort *) (iVar3 + 0x1a))) | 4);
      uVar7 = (undefined4) CodeGen_GenThunk(iVar3, *puVar8, puVar8[1], puVar8[2], puVar8[3]);
      break;

    case 3:
      iVar3 = (int) (*((int *) (param_1 + 8)));
      switch (*((undefined1 *) (iVar3 + 2)))
    {
      default:
        puVar8 = (undefined4 *) ((undefined4 *) 0x0);
        break;

      case 3:

      case 4:
        CError_Internal(cmid_filename, 0x176);

      case 0:
        puVar8 = (undefined4 *) (*((undefined4 **) (iVar3 + 0x4c)));

    }

      if (((uint) puVar8) == ((uint) ((undefined4 *) 0x0)))
    {
      CError_Internal(cmid_filename, 0x8e4);
    }
      if (DAT_0070f287 != '\0')
    {
      DAT_00715c48 = (uint) (*puVar8);
      DAT_00715c4c = (uint) puVar8[1];
      DAT_00715c50 = (uint) puVar8[2];
      DAT_00716ca0 = (uint) DAT_00715c48;
      DAT_00716ca4 = (uint) DAT_00715c4c;
      DAT_00716ca8 = (uint) DAT_00715c50;
      fn_00447700(&DAT_00716ca0);
    }
      cVar2 = (char) (*((char *) (puVar8 + 6)));
      puVar4 = (undefined4 *) ((undefined4 *) puVar8[4]);
      uVar7 = (undefined4) puVar8[3];
      uVar5 = (undefined4) puVar8[5];
      iVar3 = (int) (*((int *) (param_1 + 8)));
      *((ushort *) (iVar3 + 0x1a)) = (ushort) ((*((ushort *) (iVar3 + 0x1a))) | 4);
      for (puVar8 = (undefined4 *) puVar4; ((uint) puVar8) != ((uint) ((undefined4 *) 0x0)); puVar8 = (undefined4 *) ((undefined4 *) (*puVar8)))
    {
      CMid_ObjectAddrRef((int) puVar8[1]);
    }

      uVar6 = (undefined4) (*((undefined4 *) (iVar3 + 0x14)));
      if (cVar2 == '\0')
    {
      uVar7 = (undefined4) fn_004c4480(iVar3, uVar7, puVar4, uVar5);
    }
    else
    {
      uVar7 = (undefined4) fn_004c4190(iVar3, uVar7, puVar4, uVar5);
    }
      *((undefined4 *) (iVar3 + 0x14)) = (undefined4) uVar6;
      break;

    default:
      uVar7 = (undefined4) CError_Internal(cmid_filename, 0x8f4);

  }

  return;
}

void fn_0047aa60(char param_1)
{
  uint uVar1;
  undefined4 *puVar2;
  char cVar3;
  for (puVar2 = (undefined4 *) DAT_00711bac; ((uint) puVar2) != ((uint) ((undefined4 *) 0x0)); puVar2 = (undefined4 *) ((undefined4 *) (*puVar2)))
  {
    switch (*((undefined1 *) (puVar2 + 7)))
    {
      case 1:

      case 3:
        if (((((*((short *) (puVar2[2] + 0x18))) == 0x102) && ((uVar1 = (uint) (*((uint *) (puVar2[2] + 0x14))), (uVar1 & 0x20000) == 0))) && ((uVar1 & 4) == 0)) && ((cVar3 = (char) fn_005a1780(puVar2), cVar3 == '\0')))
      {
        if (param_1 == '\0')
        {
          CError_Warning(0x2924, puVar2[2]);
        }
        else
        {
          CError_ReportError(0x2924, puVar2[2]);
        }
      }
        break;

      case 2:
        break;

      default:
        CError_Internal(cmid_filename, 0x8ca);

    }

  }

  return;
}

void fn_0047aaf0(int param_1)
{
  int iVar1;
  char cVar2;
  int *piVar3;
  undefined1 auStack_10c[56];
  undefined1 local_d4[184];
  undefined1 auStack_1c[16];
  if ((DAT_00725ecb == '\0') && (((*((char *) (param_1 + 0x1d))) != '\0') || ((cVar2 = (char) fn_00456a50(*((undefined4 *) (param_1 + 8))), cVar2 != '\0'))))
  {
    iVar1 = (int) (*((int *) (param_1 + 8)));
    cVar2 = (char) (*((char *) (iVar1 + 2)));
    if (cVar2 == '\x05')
    {
      piVar3 = (int *) ((int *) 0x0);
    }
    else
    {
      if ((cVar2 != '\x03') && (cVar2 != '\x04'))
      {
        CError_Internal(cmid_filename, 0x124);
      }
      if (((*((uint *) (iVar1 + 0x14))) & 0x800000) != 0)
      {
        CError_Internal(cmid_filename, 0x125);
      }
      if ((*(*((char **) (iVar1 + 0x10)))) != '\a')
      {
        CError_Internal(cmid_filename, 0x126);
      }
      if (((*((uint *) ((*((int *) (iVar1 + 0x10))) + 0x16))) & 0x100000) != 0)
      {
        CError_Internal(cmid_filename, 0x127);
      }
      if (((*((uint *) ((*((int *) (iVar1 + 0x10))) + 0x16))) & 0x200) == 0)
      {
        piVar3 = (int *) (*((int **) (iVar1 + 0x40)));
      }
      else
      {
        piVar3 = (int *) ((int *) 0x0);
      }
    }
    if (((uint) piVar3) == ((uint) ((int *) 0x0)))
    {
      CError_Internal(cmid_filename, 0x882);
    }
    if ((*piVar3) == 0)
    {
      CError_Internal(cmid_filename, 0x883);
    }
    fn_004e1420(local_d4);
    fn_004e0df0(piVar3 + 3);
    fn_004c4ad0();
    CScope_SetFunctionScope(*((undefined4 *) (param_1 + 8)), auStack_1c);
    fn_005a1310(auStack_10c, param_1);
    if (DAT_00725ecb == '\0')
    {
      fn_0047c240((undefined4 *) auStack_10c);
    }
    CScope_RestoreScope(auStack_1c);
    fn_004e0df0(local_d4);
  }
  iVar1 = (int) (*((int *) (param_1 + 8)));
  if ((((*((uint *) (iVar1 + 0x14))) & 0x10) == 0) && (((*((uint *) ((*((int *) (iVar1 + 0x10))) + 0x16))) & 0x800) == 0))
  {
    fn_0047ce70((int) iVar1);
  }
  return;
}

void fn_0047acc0(void)
{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  bool bVar4;
  char cVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  undefined1 local_fc[36];
  int local_d8[50];
  puVar7 = (undefined4 *) DAT_007107a8;
  if (((uint) DAT_007107a8) == ((uint) ((undefined4 *) 0x0)))
  {
    return;
  }
  for (; ((uint) puVar7) != ((uint) ((undefined4 *) 0x0)); puVar7 = (undefined4 *) ((undefined4 *) (*puVar7)))
  {
    fn_0047c510((int) 0, (undefined4) puVar7[1]);
  }

  cVar5 = (char) CInline_DispatchNextDeferredNode();
  do
  {
    if (cVar5 == '\0')
    {
      puVar6 = (undefined4 *) ((undefined4 *) CFunc_FuncGenSetup(0, local_fc, 0, 0));
      puVar7 = (undefined4 *) DAT_007107a8;
      while (((uint) puVar7) != ((uint) ((undefined4 *) 0x0)))
      {
        DAT_00711b3c = (uint) puVar7[3];
        DAT_00711b40 = (uint) puVar7[4];
        DAT_00711b44 = (uint) puVar7[5];
        if (((uint) puVar7) == ((uint) DAT_007107a8))
        {
          DAT_00711b70 = (uint) DAT_00711b3c;
          DAT_00711b74 = (uint) DAT_00711b40;
          DAT_00711b78 = (uint) DAT_00711b44;
          DAT_00716cfc = (uint) DAT_00711b3c;
          DAT_00716d00 = (uint) DAT_00711b40;
          DAT_00716d04 = (uint) DAT_00711b44;
        }
        DAT_00716ca0 = (uint) DAT_00711b3c;
        DAT_00716ca4 = (uint) DAT_00711b40;
        DAT_00716ca8 = (uint) DAT_00711b44;
        fn_00447910(&DAT_00711b3c);
        iVar8 = (int) (*((int *) ((*((int *) (puVar7[2] + 8))) + 0xc)));
        if ((iVar8 == 0) || (((*((uint *) (iVar8 + 0x22))) & 0x800) == 0))
        {
          iVar8 = (int) CFunc_AppendStatement(4);
          uVar9 = (undefined4) fn_00548e50(puVar7[1], 0);
          *((undefined4 *) (iVar8 + 10)) = (undefined4) uVar9;
          puVar7 = (undefined4 *) ((undefined4 *) (*puVar7));
        }
        else
        {
          puVar7 = (undefined4 *) ((undefined4 *) fn_0047b020((int *) puVar7));
        }
      }

      DAT_00716c9c = (uint) 0;
      DAT_00710808 = (uint) DAT_00716ca0;
      DAT_0071080c = (uint) DAT_00716ca4;
      DAT_00710810 = (uint) DAT_00716ca8;
      fn_0055bc20(local_fc, fn_0047c7d0);
      fn_0052df40(local_fc);
      memclrw(&DAT_00717284, 0x36);
      DAT_00717288 = (uint) 0;
      DAT_0071728e = (uint) DAT_00710924;
      DAT_00717292 = (uint) DAT_00716d50;
      DAT_0071728c = (byte) 0;
      DAT_0071728d = (byte) 1;
      DAT_00717284 = (uint *) local_fc;
      fn_0044ea60(0, 0, 0);
      if (DAT_00725e67 == '\0')
      {
        fn_00545830(&DAT_00717284);
        if (DAT_00725ecb == '\0')
        {
          fn_0047c240((undefined4 *) (&DAT_00717284));
        }
      }
      else
        if (DAT_00725ecb == '\0')
      {
        fn_00593320(DAT_00717288, DAT_00717284);
        fn_00547a20(&DAT_00717284, local_d8);
        fn_005a1510(local_d8);
        if (local_d8[0] == 0)
        {
          CError_Internal(cmid_filename, 0x440);
        }
        uVar3 = (uint) (*((uint *) (local_d8[0] + 0x14)));
        uVar10 = (uint) 0;
        puVar7 = (undefined4 *) ((undefined4 *) (local_d8[0] + 0x1a));
        if (uVar3 != 0)
        {
          do
          {
            if ((*((char *) (puVar7 + 1))) == '\x01')
            {
              CMid_ObjectAddrRef((int) (*puVar7));
            }
            uVar10 = (uint) (uVar10 + 1);
            puVar7 = (undefined4 *) (puVar7 + 2);
          }
          while (uVar10 < uVar3);
        }
      }
      DAT_00711be0 = (uint) (*puVar6);
      return;
    }
    puVar7 = (undefined4 *) cmid_pendingnodes;
    if (DAT_00725ecb == '\0')
    {
      for (; ((uint) puVar7) != ((uint) ((undefined4 *) 0x0)); puVar7 = (undefined4 *) ((undefined4 *) (*puVar7)))
      {
        if ((*((char *) (puVar7 + 9))) == '\0')
        {
          bVar4 = (bool) 0;
          goto LAB_0047ad38;
        }
      }

    }
    bVar4 = (bool) 1;
    LAB_0047ad38:
    if (bVar4)
    {
      if (((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)))
      {
        for (; ((uint) cmid_pendingclasses) != ((uint) ((undefined4 *) 0x0)); cmid_pendingclasses = (uint *) ((undefined4 *) (*cmid_pendingclasses)))
        {
          piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
          piVar2 = (int *) ((int *) (*piVar1));
          cVar5 = (char) (*((char *) (((int) piVar2) + 0x1d)));
          while (cVar5 == '\0')
          {
            *piVar1 = (int) (*piVar2);
            piVar1 = (int *) (*((int **) (cmid_pendingclasses[1] + 6)));
            piVar2 = (int *) ((int *) (*piVar1));
            cVar5 = (char) (*((char *) (((int) piVar2) + 0x1d)));
          }

        }

        cmid_pendingclasses = (uint *) ((undefined4 *) 0x0);
      }
      fn_00514e20();
      fn_0046c550();
    }

    cVar5 = (char) CInline_DispatchNextDeferredNode();
  }
  while (1);
}

int fn_0047b020(int *param_1)
{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  iVar5 = (int) param_1[2];
  fn_00556b70(iVar5);
  uVar1 = (undefined4) fn_00554650(iVar5);
  iVar2 = (int) CFunc_AppendStatement(6);
  uVar3 = (undefined4) fn_00554630(uVar1, 0);
  *((undefined4 *) (iVar2 + 10)) = (undefined4) uVar3;
  iVar4 = (int) newlabel();
  *((int *) (iVar2 + 0xe)) = (int) iVar4;
  do
  {
    iVar2 = (int) CFunc_AppendStatement(4);
    uVar3 = (undefined4) fn_00548e50(param_1[1], 0);
    *((undefined4 *) (iVar2 + 10)) = (undefined4) uVar3;
    param_1 = (int *) ((int *) (*param_1));
    if (((uint) param_1) == ((uint) ((int *) 0x0)))
      break;
  }
  while (param_1[2] == iVar5);
  iVar5 = (int) CFunc_AppendStatement(4);
  uVar1 = (undefined4) fn_00554600(uVar1, 0);
  *((undefined4 *) (iVar5 + 10)) = (undefined4) uVar1;
  iVar5 = (int) CFunc_AppendStatement(2);
  *((int *) (iVar5 + 0xe)) = (int) iVar4;
  *((int *) (iVar4 + 4)) = (int) iVar5;
  return (int) ((int) param_1);
}

undefined1 CInline_DispatchNextDeferredNode(void)
{
 uint *work;
 if (DAT_00725ecb && !DAT_0070f1f7) return 0;
 work=cmid_pendingnodes;
 if(work) {
  cmid_pendingnodes=(uint *)work[0];
  switch(*(byte *)((byte *)work+36)) {
  case 0:
   if(!(*(ushort *)(work[1]+26)&4))
    fn_00524500(work[1],work[8],work[2],work+6,work+3,0);
   break;
  case 1:
   if(!(*(uint *)(*(uint *)(work[1]+16)+22)&2))
    fn_005a1b90(work[3],work[4],work[5],work[2],work[1],0);
   break;
  case 2:
   if(!(*(uint *)(*(uint *)(work[1]+16)+22)&2) && !*(byte *)(*(uint *)(work[1]+72)+13))
    fn_005a1f80(fn_0053ee10(**(uint **)(work[1]+72),*(uint **)(work[1]+72),0));
   break;
  case 3:fn_00524750(work[1]);break;
  case 4:fn_005243d0(work[3],work[4]);break;
  default:CError_Internal(cmid_filename,0x7bd);
  }
  fn_0046c6e0(work,38);return 1;
 }
 if(cmid_deferredinline && !DAT_0070f1bb && !DAT_00725e67 && (!DAT_00725ecb || !DAT_0070f1f7)) {
  work=cmid_deferredinline;cmid_deferredinline=(uint *)work[0];
  fn_0047b6d0((int)work[1]);fn_0046c6e0(work,8);return 1;
 }
 return 0;
}


void CMid_ObjectAddrRef(int param_1)
{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  *((ushort *) (param_1 + 0x1a)) = (ushort) ((*((ushort *) (param_1 + 0x1a))) | 2);
  switch (*((undefined1 *) (param_1 + 2)))
  {
    case 0:
      if (((*((uint *) (param_1 + 0x14))) & 0x10000) != 0)
    {
      fn_0052ef30(param_1);
    }
      return;

    case 3:

    case 4:
      if (((*((ushort *) (param_1 + 0x1a))) & 4) == 0)
    {
      if (((*((uint *) (param_1 + 0x14))) & 0x10) != 0)
      {
        cVar1 = (char) (*((char *) (param_1 + 2)));
        if (cVar1 == '\x05')
        {
          iVar6 = (int) 0;
        }
        else
        {
          if ((cVar1 != '\x03') && (cVar1 != '\x04'))
          {
            CError_Internal(cmid_filename, 0x124);
          }
          if (((*((uint *) (param_1 + 0x14))) & 0x800000) != 0)
          {
            CError_Internal(cmid_filename, 0x125);
          }
          if ((*(*((char **) (param_1 + 0x10)))) != '\a')
          {
            CError_Internal(cmid_filename, 0x126);
          }
          if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x100000) != 0)
          {
            CError_Internal(cmid_filename, 0x127);
          }
          if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x200) == 0)
          {
            iVar6 = (int) (*((int *) (param_1 + 0x40)));
          }
          else
          {
            iVar6 = (int) 0;
          }
        }
        if ((iVar6 != 0) && (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x100000) == 0))
        {
          *((ushort *) (param_1 + 0x1a)) = (ushort) ((*((ushort *) (param_1 + 0x1a))) | 4);
          if ((*((char *) (DAT_00710360 + 600))) == '\0')
          {
            if (DAT_00725e67 == '\0')
            {
              puVar7 = (undefined4 *) ((undefined4 *) fn_0046c730(8));
              *puVar7 = (undefined4) cmid_deferredinline;
              puVar7[1] = (undefined4) param_1;
              cmid_deferredinline = (uint *) puVar7;
            }
            else
            {
              CCallGraph_AddFunction(param_1);
              cVar1 = (char) (*((char *) (param_1 + 2)));
              if (cVar1 == '\x05')
              {
                piVar4 = (int *) ((int *) 0x0);
              }
              else
              {
                if ((cVar1 != '\x03') && (cVar1 != '\x04'))
                {
                  CError_Internal(cmid_filename, 0x124);
                }
                if (((*((uint *) (param_1 + 0x14))) & 0x800000) != 0)
                {
                  CError_Internal(cmid_filename, 0x125);
                }
                if ((*(*((char **) (param_1 + 0x10)))) != '\a')
                {
                  CError_Internal(cmid_filename, 0x126);
                }
                if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x100000) != 0)
                {
                  CError_Internal(cmid_filename, 0x127);
                }
                if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x200) == 0)
                {
                  piVar4 = (int *) (*((int **) (param_1 + 0x40)));
                }
                else
                {
                  piVar4 = (int *) ((int *) 0x0);
                }
              }
              if (((uint) piVar4) != ((uint) ((int *) 0x0)))
              {
                if ((*piVar4) == 0)
                {
                  CError_Internal(cmid_filename, 0x440);
                }
                uVar2 = (uint) (*((uint *) ((*piVar4) + 0x14)));
                uVar5 = (uint) 0;
                puVar7 = (undefined4 *) ((undefined4 *) ((*piVar4) + 0x1a));
                if (uVar2 != 0)
                {
                  do
                  {
                    if ((*((char *) (puVar7 + 1))) == '\x01')
                    {
                      CMid_ObjectAddrRef((int) (*puVar7));
                    }
                    uVar5 = (uint) (uVar5 + 1);
                    puVar7 = (undefined4 *) (puVar7 + 2);
                  }
                  while (uVar5 < uVar2);
                }
              }
            }
          }
          else
          {
            CError_ReportError(0x2908, param_1);
          }
          return;
        }
      }
      if ((((*((uint *) (param_1 + 0x14))) & 0x400000) != 0) && ((*((int *) (param_1 + 100))) == 0))
      {
        uVar3 = (undefined4) fn_0053eae0();
        *((undefined4 *) (param_1 + 100)) = (undefined4) uVar3;
      }
      uVar2 = (uint) (*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16)));
      if (((uVar2 & 0x100) == 0) || ((puVar7 = (undefined4 *) cmid_pendingnodes, (uVar2 & 2) != 0)))
      {
        if ((*((int *) (param_1 + 0x48))) == 0)
        {
          return;
        }
        puVar7 = (undefined4 *) ((undefined4 *) fn_0046c730(0x26));
        memclrw(puVar7, 0x26);
        *puVar7 = (undefined4) cmid_pendingnodes;
        *((undefined1 *) (puVar7 + 9)) = (undefined1) 2;
        puVar7[1] = (undefined4) param_1;
        cmid_pendingnodes = (uint *) puVar7;
        return;
      }
      for (; ((uint) puVar7) != ((uint) ((undefined4 *) 0x0)); puVar7 = (undefined4 *) ((undefined4 *) (*puVar7)))
      {
        if (puVar7[1] == param_1)
          goto LAB_0047b424;
      }

      puVar7 = (undefined4 *) ((undefined4 *) fn_0046c730(0x26));
      memclrw(puVar7, 0x26);
      *puVar7 = (undefined4) cmid_pendingnodes;
      *((undefined1 *) (puVar7 + 9)) = (undefined1) 3;
      puVar7[1] = (undefined4) param_1;
      cmid_pendingnodes = (uint *) puVar7;
      LAB_0047b424:
      *((ushort *) (param_1 + 0x1a)) = (ushort) ((*((ushort *) (param_1 + 0x1a))) | 4);

      return;
    }
      break;

    case 6:
      CMid_ObjectAddrRef((int) (*((undefined4 *) (param_1 + 0x40))));
      return;

  }

  return;
}

void fn_0047b5b0(uint function_object, uint definition, uint specialization)
{
  return;
}

void fn_0047b5c0(undefined4 param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  puVar1 = (undefined4 *) ((undefined4 *) fn_0046c730(0x26));
  memclrw(puVar1, 0x26);
  *puVar1 = (undefined4) cmid_pendingnodes;
  *((undefined1 *) (puVar1 + 9)) = (undefined1) 4;
  puVar1[1] = (undefined4) 0;
  puVar1[3] = (undefined4) param_1;
  puVar1[4] = (undefined4) param_2;
  cmid_pendingnodes = (uint *) puVar1;
  return;
}

void fn_0047b600(int param_1, undefined4 param_2, undefined4 *param_3, undefined4 param_4, undefined4 *param_5)
{
  uint *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  puVar2 = (undefined4 *) cmid_pendingnodes;
  while (1)
  {
    if (((uint) puVar2) == ((uint) ((undefined4 *) 0x0)))
    {
      if ((*(*((char **) (param_1 + 0x10)))) != '\a')
      {
        CError_Internal(cmid_filename, 0x6b4);
      }
      puVar1 = (uint *) ((uint *) ((*((int *) (param_1 + 0x10))) + 0x16));
      *puVar1 = (uint) ((*puVar1) | 0x800000);
      puVar2 = (undefined4 *) ((undefined4 *) fn_0046c730(0x26));
      memclrw(puVar2, 0x26);
      *puVar2 = (undefined4) cmid_pendingnodes;
      *((undefined1 *) (puVar2 + 9)) = (undefined1) 0;
      puVar2[1] = (undefined4) param_1;
      if (((*((uint *) (param_1 + 0x14))) & 0x400000) != 0)
      {
        uVar3 = (undefined4) fn_0053eae0();
        puVar2[2] = (undefined4) uVar3;
      }
      puVar2[8] = (undefined4) param_2;
      puVar2[3] = (undefined4) (*param_3);
      puVar2[4] = (undefined4) param_3[1];
      puVar2[5] = (undefined4) param_3[2];
      uVar3 = (undefined4) param_5[1];
      puVar2[6] = (undefined4) (*param_5);
      puVar2[7] = (undefined4) uVar3;
      cmid_pendingnodes = (uint *) puVar2;
      return;
    }
    if (puVar2[1] == param_1)
      break;
    puVar2 = (undefined4 *) ((undefined4 *) (*puVar2));
  }

  CError_ReportError(0x285d, param_1);
  return;
}

void fn_0047b6d0(int param_1)
{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  undefined1 auStack_f4[16];
  undefined1 local_e4[184];
  undefined1 auStack_2c[36];
  cVar2 = (char) (*((char *) (param_1 + 2)));
  if (cVar2 == '\x05')
  {
    iVar3 = (int) 0;
  }
  else
  {
    if ((cVar2 != '\x03') && (cVar2 != '\x04'))
    {
      CError_Internal(cmid_filename, 0x124);
    }
    if (((*((uint *) (param_1 + 0x14))) & 0x800000) != 0)
    {
      CError_Internal(cmid_filename, 0x125);
    }
    if ((*(*((char **) (param_1 + 0x10)))) != '\a')
    {
      CError_Internal(cmid_filename, 0x126);
    }
    if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x100000) != 0)
    {
      CError_Internal(cmid_filename, 0x127);
    }
    if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x200) == 0)
    {
      iVar3 = (int) (*((int *) (param_1 + 0x40)));
    }
    else
    {
      iVar3 = (int) 0;
    }
  }
  if (iVar3 == 0)
  {
    CError_Internal(cmid_filename, 0x652);
  }
  fn_004e1420(local_e4);
  fn_004e0df0(iVar3 + 0xc);
  fn_004c4ad0();
  CScope_SetFunctionScope(param_1, auStack_f4);
  CFunc_FuncGenSetup(0, auStack_2c, param_1, 0);
  fn_00547ed0(param_1, iVar3, auStack_2c, 0);
  uVar1 = (undefined1) DAT_0070f287;
  if ((DAT_0070f229 != '\0') || (DAT_00711b70 == 0))
  {
    DAT_0070f287 = (byte) 0;
  }
  memclrw(&DAT_00717284, 0x36);
  DAT_00717284 = (uint *) auStack_2c;
  DAT_00717288 = (uint) param_1;
  DAT_0071728e = (uint) DAT_00710924;
  DAT_00717292 = (uint) DAT_00716d50;
  DAT_0071728c = (byte) fn_0052eee0(param_1);
  DAT_0071728d = (byte) 0;
  fn_0044ea60(0, 0, 0);
  fn_00545830(&DAT_00717284);
  if ((DAT_00725ecb == '\0') && ((cVar2 = (char) fn_00456a50(param_1), cVar2 != '\0')))
  {
    fn_0047c240((undefined4 *) (&DAT_00717284));
  }
  CScope_RestoreScope(auStack_f4);
  DAT_0070f287 = (byte) uVar1;
  fn_004e0df0(local_e4);
  if ((((*((uint *) (param_1 + 0x14))) & 0x10) == 0) && (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x800) == 0))
  {
    fn_0047ce70((int) param_1);
  }
  return;
}

void fn_0047b910(int param_1, undefined4 param_2, undefined4 *param_3, undefined4 param_4, char param_5, char param_6)
{
  int iVar1;
  undefined4 uVar2;
  char cVar3;
  undefined4 *in_EAX;
  undefined4 *puVar4;
  if (DAT_00725dfa != '\0')
  {
    *((ushort *) (param_1 + 0x1a)) = (ushort) ((*((ushort *) (param_1 + 0x1a))) | 4);
    return;
  }
  fn_00556b70(param_1);
  puVar4 = (undefined4 *) param_3;
  if (((uint) param_3) != ((uint) ((undefined4 *) 0x0)))
  {
    for (; ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
    {
      iVar1 = (int) puVar4[1];
      if (((*((char *) (iVar1 + 2))) == '\0') && ((*((char *) (iVar1 + 0x5a))) != '\0'))
      {
        *((undefined1 *) (iVar1 + 0x5a)) = (undefined1) 0;
      }
    }

  }
  puVar4 = (undefined4 *) DAT_00710148;
  if (param_6 != '\0')
  {
    while (1)
    {
      if (((uint) puVar4) == ((uint) ((undefined4 *) 0x0)))
      {
        fn_0047bb90((int) param_1, (int) param_2, (undefined4) param_3, (undefined4) param_4, (undefined1) param_5, (char) 1);
        return;
      }
      if (puVar4[1] == param_1)
        break;
      puVar4 = (undefined4 *) ((undefined4 *) (*puVar4));
    }

    return;
  }
  if ((*((char *) (DAT_00710360 + 600))) == '\0')
  {
    if (DAT_00725e67 == '\0')
    {
      if (DAT_0070f287 != '\0')
      {
        fn_00447700(&DAT_00716ca0);
      }
      *((ushort *) (param_1 + 0x1a)) = (ushort) ((*((ushort *) (param_1 + 0x1a))) | 4);
      for (puVar4 = (undefined4 *) param_3; ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
      {
        CMid_ObjectAddrRef((int) puVar4[1]);
      }

      uVar2 = (undefined4) (*((undefined4 *) (param_1 + 0x14)));
      if (param_5 == '\0')
      {
        puVar4 = (undefined4 *) ((undefined4 *) fn_004c4480(param_1, param_2, param_3, param_4));
      }
      else
      {
        puVar4 = (undefined4 *) ((undefined4 *) fn_004c4190(param_1, param_2, param_3, param_4));
      }
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar2;
      return;
    }
    *((ushort *) (param_1 + 0x1a)) = (ushort) ((*((ushort *) (param_1 + 0x1a))) | 4);
    for (puVar4 = (undefined4 *) param_3; ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
    {
      CMid_ObjectAddrRef((int) puVar4[1]);
    }

    fn_0047bb90((int) param_1, (int) param_2, (undefined4) param_3, (undefined4) param_4, (undefined1) param_5, (char) 0);
    puVar4 = (undefined4 *) ((undefined4 *) CCallGraph_AddFunction(param_1));
    return;
  }
  for (; ((uint) puVar4) != ((uint) ((undefined4 *) 0x0)); puVar4 = (undefined4 *) ((undefined4 *) (*puVar4)))
  {
    if (puVar4[1] == param_1)
    {
      return;
    }
  }

  if ((((*((short *) (param_1 + 0x18))) != 0x102) && (((*((uint *) (param_1 + 0x14))) & 0x60000) == 0)) && ((DAT_0070f1b3 == '\0') || ((cVar3 = (char) fn_004531a0(param_1), cVar3 == '\0'))))
  {
    puVar4 = (undefined4 *) ((undefined4 *) CError_ReportError(0x2908, param_1));
    return;
  }
  fn_0047bb90((int) param_1, (int) param_2, (undefined4) param_3, (undefined4) param_4, (undefined1) param_5, (char) 1);
  for (; ((uint) param_3) != ((uint) ((undefined4 *) 0x0)); param_3 = (undefined4 *) ((undefined4 *) (*param_3)))
  {
    CMid_ObjectAddrRef((int) param_3[1]);
  }

  CMid_ObjectAddrRef((int) param_1);
  return;
}

void fn_0047bb40(int param_1)
{
  undefined4 *puVar1;
  puVar1 = (undefined4 *) DAT_00716c24;
  while (1)
  {
    if (((uint) puVar1) == ((uint) ((undefined4 *) 0x0)))
    {
      puVar1 = (undefined4 *) ((undefined4 *) galloc(8));
      *puVar1 = (undefined4) DAT_00716c24;
      puVar1[1] = (undefined4) param_1;
      DAT_00716c24 = (uint *) puVar1;
      *((ushort *) (param_1 + 0x1a)) = (ushort) ((*((ushort *) (param_1 + 0x1a))) | 0x200);
      return;
    }
    if (puVar1[1] == param_1)
      break;
    puVar1 = (undefined4 *) ((undefined4 *) (*puVar1));
  }

  return;
}

void fn_0047bb90(int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined1 param_5, char param_6)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  puVar1 = (undefined4 *) ((undefined4 *) galloc(0x1a));
  memclrw(puVar1, 0x1a);
  if (DAT_0070f287 != '\0')
  {
    *puVar1 = (undefined4) DAT_00716ca0;
    puVar1[1] = (undefined4) DAT_00716ca4;
    puVar1[2] = (undefined4) DAT_00716ca8;
  }
  if (param_2 != 0)
  {
    uVar2 = (undefined4) galloc(param_4);
    puVar1[3] = (undefined4) uVar2;
    memcpy(puVar1[3], param_2, param_4);
  }
  uVar2 = (undefined4) fn_00455850(param_3);
  puVar1[4] = (undefined4) uVar2;
  puVar1[5] = (undefined4) param_4;
  *((undefined1 *) (puVar1 + 6)) = (undefined1) param_5;
  *((undefined4 **) (param_1 + 0x4c)) = (undefined4 *) puVar1;
  if (param_6 != '\0')
  {
    puVar1 = (undefined4 *) ((undefined4 *) galloc(8));
    *puVar1 = (undefined4) DAT_00710148;
    puVar1[1] = (undefined4) param_1;
    DAT_00710148 = (uint *) puVar1;
  }
  return;
}

int CMid_DefineThunkObject(int param_1, int param_2, int param_3, int param_4)
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int *unaff_ESI;
  CMid_ObjectAddrRef((int) param_1);
  puVar4 = (undefined4 *) DAT_00715c2c;
  while (1)
  {
    if (((uint) puVar4) == ((uint) ((undefined4 *) 0x0)))
    {
      piVar1 = (int *) ((int *) galloc(0x10));
      memclrw(piVar1, 0x10);
      *piVar1 = (int) param_1;
      piVar1[1] = (int) param_2;
      piVar1[2] = (int) param_3;
      piVar1[3] = (int) param_4;
      iVar2 = (int) fn_004554b0();
      uVar3 = (undefined4) CMangler_ThunkName(param_1, param_2, param_3, param_4);
      *((undefined4 *) (iVar2 + 0xc)) = (undefined4) uVar3;
      *((undefined **) (iVar2 + 0x10)) = (undefined *) (&DAT_006771e4);
      *((undefined2 *) (iVar2 + 0x18)) = (undefined2) 0x103;
      *((undefined4 *) (iVar2 + 0x14)) = (undefined4) 0x820000;
      *((undefined4 *) (iVar2 + 0x44)) = (undefined4) (*((undefined4 *) (iVar2 + 0xc)));
      *((int **) (iVar2 + 0x40)) = (int *) piVar1;
      puVar4 = (undefined4 *) ((undefined4 *) galloc(8));
      *puVar4 = (undefined4) DAT_00715c2c;
      puVar4[1] = (undefined4) iVar2;
      DAT_00715c2c = (uint *) puVar4;
      return (int) iVar2;
    }
    if ((((*((uint *) (puVar4[1] + 0x14))) & 0x800000) == 0) || ((unaff_ESI = (int *) (*((int **) (puVar4[1] + 0x40))), ((uint) unaff_ESI) == ((uint) ((int *) 0x0)))))
    {
      CError_Internal(cmid_filename, 0x523);
    }
    if ((((param_1 == (*unaff_ESI)) && (param_2 == unaff_ESI[1])) && (param_3 == unaff_ESI[2])) && (param_4 == unaff_ESI[3]))
      break;
    puVar4 = (undefined4 *) ((undefined4 *) (*puVar4));
  }

  return (int) puVar4[1];
}

void CMid_DefineFunction(undefined4 *param_1)
{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  char *pcVar5;
  undefined4 *puVar6;
  int *piVar7;
  uint uVar8;
  undefined1 local_d5;
  undefined1 local_d4[200];
  if (param_1[1] == 0)
  {
    CError_Internal(cmid_filename, 0x477);
  }
  DAT_00716c9c = (uint) param_1[1];
  puVar1 = (uint *) ((uint *) ((*((int *) (param_1[1] + 0x10))) + 0x16));
  *puVar1 = (uint) ((*puVar1) | 2);
  DAT_00710924 = (uint) (*((undefined4 *) (((int) param_1) + 10)));
  DAT_00716d50 = (uint) (*((undefined4 *) (((int) param_1) + 0xe)));
  fn_0055bc20(*param_1, fn_0047c7d0);
  *((undefined4 *) (((int) param_1) + 10)) = (undefined4) DAT_00710924;
  *((undefined4 *) (((int) param_1) + 0xe)) = (undefined4) DAT_00716d50;
  cVar4 = (char) fn_00549de0(param_1[1], *param_1, &local_d5);
  if (cVar4 == '\0')
  {
    fn_0047c510((int) (*param_1), (undefined4) 0);
    *((ushort *) (param_1[1] + 0x1a)) = (ushort) ((*((ushort *) (param_1[1] + 0x1a))) | 4);
    if (((((uint) cmid_pendingnodes) != ((uint) 0)) || (DAT_00725e67 != '\0')) || (DAT_0070f1bb != '\0'))
    {
      fn_00593320(param_1[1], *param_1);
      fn_00547e90(*param_1);
      fn_00547a20(param_1, local_d4);
      fn_0047cf40((int) param_1[1], (int *) local_d4);
      iVar2 = (int) param_1[1];
      if ((*((char *) (DAT_00710360 + 600))) == '\0')
      {
        if (DAT_00725e67 == '\0')
        {
          pcVar5 = (char *) ((char *) fn_0046c730(8));
          *((char **) pcVar5) = (char *) cmid_deferredinline;
          *((int *) (pcVar5 + 4)) = (int) iVar2;
          cmid_deferredinline = (uint *) pcVar5;
        }
        else
        {
          pcVar5 = (char *) ((char *) CCallGraph_AddFunction(iVar2));
          cVar4 = (char) (*((char *) (iVar2 + 2)));
          if (cVar4 == '\x05')
          {
            piVar7 = (int *) ((int *) 0x0);
          }
          else
          {
            if ((cVar4 != '\x03') && (cVar4 != '\x04'))
            {
              CError_Internal(cmid_filename, 0x124);
            }
            if (((*((uint *) (iVar2 + 0x14))) & 0x800000) != 0)
            {
              CError_Internal(cmid_filename, 0x125);
            }
            pcVar5 = (char *) (*((char **) (iVar2 + 0x10)));
            if ((*pcVar5) != '\a')
            {
              pcVar5 = (char *) ((char *) CError_Internal(cmid_filename, 0x126));
            }
            if (((*((uint *) ((*((int *) (iVar2 + 0x10))) + 0x16))) & 0x100000) != 0)
            {
              pcVar5 = (char *) ((char *) CError_Internal(cmid_filename, 0x127));
            }
            if (((*((uint *) ((*((int *) (iVar2 + 0x10))) + 0x16))) & 0x200) == 0)
            {
              piVar7 = (int *) (*((int **) (iVar2 + 0x40)));
            }
            else
            {
              piVar7 = (int *) ((int *) 0x0);
            }
          }
          if (((uint) piVar7) != ((uint) ((int *) 0x0)))
          {
            if ((*piVar7) == 0)
            {
              pcVar5 = (char *) ((char *) CError_Internal(cmid_filename, 0x440));
            }
            uVar3 = (uint) (*((uint *) ((*piVar7) + 0x14)));
            uVar8 = (uint) 0;
            puVar6 = (undefined4 *) ((undefined4 *) ((*piVar7) + 0x1a));
            if (uVar3 != 0)
            {
              do
              {
                if ((*((char *) (puVar6 + 1))) == '\x01')
                {
                  CMid_ObjectAddrRef((int) (*puVar6));
                }
                uVar8 = (uint) (uVar8 + 1);
                puVar6 = (undefined4 *) (puVar6 + 2);
              }
              while (uVar8 < uVar3);
            }
          }
        }
      }
      else
      {
        pcVar5 = (char *) ((char *) CError_ReportError(0x2908, iVar2));
      }
      return;
    }
  }
  else
  {
    fn_00593320(param_1[1], *param_1);
    fn_00547e90(*param_1);
    fn_00547a20(param_1, local_d4);
    fn_0047cf40((int) param_1[1], (int *) local_d4);
    fn_0047c510((int) (*param_1), (undefined4) 0);
    iVar2 = (int) param_1[1];
    if ((((*((uint *) ((*((char **) (iVar2 + 0x10))) + 0x16))) & 0x800) == 0) && (((*((ushort *) (iVar2 + 0x1a))) & 2) == 0))
    {
      return;
    }
    *((ushort *) (iVar2 + 0x1a)) = (ushort) ((*((ushort *) (iVar2 + 0x1a))) | 4);
    if (((((uint) cmid_pendingnodes) != ((uint) 0)) || (DAT_00725e67 != '\0')) || (DAT_0070f1bb != '\0'))
    {
      iVar2 = (int) param_1[1];
      if ((*((char *) (DAT_00710360 + 600))) == '\0')
      {
        if (DAT_00725e67 == '\0')
        {
          pcVar5 = (char *) ((char *) fn_0046c730(8));
          *((char **) pcVar5) = (char *) cmid_deferredinline;
          *((int *) (pcVar5 + 4)) = (int) iVar2;
          cmid_deferredinline = (uint *) pcVar5;
        }
        else
        {
          pcVar5 = (char *) ((char *) CCallGraph_AddFunction(iVar2));
          cVar4 = (char) (*((char *) (iVar2 + 2)));
          if (cVar4 == '\x05')
          {
            piVar7 = (int *) ((int *) 0x0);
          }
          else
          {
            if ((cVar4 != '\x03') && (cVar4 != '\x04'))
            {
              CError_Internal(cmid_filename, 0x124);
            }
            if (((*((uint *) (iVar2 + 0x14))) & 0x800000) != 0)
            {
              CError_Internal(cmid_filename, 0x125);
            }
            pcVar5 = (char *) (*((char **) (iVar2 + 0x10)));
            if ((*pcVar5) != '\a')
            {
              pcVar5 = (char *) ((char *) CError_Internal(cmid_filename, 0x126));
            }
            if (((*((uint *) ((*((int *) (iVar2 + 0x10))) + 0x16))) & 0x100000) != 0)
            {
              pcVar5 = (char *) ((char *) CError_Internal(cmid_filename, 0x127));
            }
            if (((*((uint *) ((*((int *) (iVar2 + 0x10))) + 0x16))) & 0x200) == 0)
            {
              piVar7 = (int *) (*((int **) (iVar2 + 0x40)));
            }
            else
            {
              piVar7 = (int *) ((int *) 0x0);
            }
          }
          if (((uint) piVar7) != ((uint) ((int *) 0x0)))
          {
            if ((*piVar7) == 0)
            {
              pcVar5 = (char *) ((char *) CError_Internal(cmid_filename, 0x440));
            }
            uVar3 = (uint) (*((uint *) ((*piVar7) + 0x14)));
            uVar8 = (uint) 0;
            puVar6 = (undefined4 *) ((undefined4 *) ((*piVar7) + 0x1a));
            if (uVar3 != 0)
            {
              do
              {
                if ((*((char *) (puVar6 + 1))) == '\x01')
                {
                  CMid_ObjectAddrRef((int) (*puVar6));
                }
                uVar8 = (uint) (uVar8 + 1);
                puVar6 = (undefined4 *) (puVar6 + 2);
              }
              while (uVar8 < uVar3);
            }
          }
        }
      }
      else
      {
        pcVar5 = (char *) ((char *) CError_ReportError(0x2908, iVar2));
      }
      return;
    }
  }
  if ((*((char *) (DAT_00710360 + 600))) != '\0')
  {
    pcVar5 = (char *) ((char *) CError_ReportError(0x2908, param_1[1]));
    return;
  }
  fn_00545830(param_1);
  pcVar5 = (char *) ((char *) fn_00456a50(param_1[1]));
  if ((((char) pcVar5) != '\0') && (DAT_00725ecb == '\0'))
  {
    fn_0047c240((undefined4 *) param_1);
  }
  return;
}

void fn_0047c240(undefined4 *param_1)
{
  undefined4 *puVar1;
  if ((*((char *) (DAT_00710360 + 600))) != '\0')
  {
    if (param_1[1] == 0)
    {
      CError_ReportError(0x27c4);
    }
    else
    {
      CError_ReportError(0x2908, param_1[1]);
    }
    return;
  }
  cmid_hasforce = (byte) '\0';
  DAT_00710924 = (uint) (*((undefined4 *) (((int) param_1) + 10)));
  DAT_00716d50 = (uint) (*((undefined4 *) (((int) param_1) + 0xe)));
  fn_0055bc20(*param_1, fn_0047c320);
  *((undefined4 *) (((int) param_1) + 10)) = (undefined4) DAT_00710924;
  *((undefined4 *) (((int) param_1) + 0xe)) = (undefined4) DAT_00716d50;
  if ((cmid_hasforce != '\0') && ((fn_0047c430((undefined4 *) (*param_1)), DAT_00725ecb != '\0')))
  {
    return;
  }
  for (puVar1 = (undefined4 *) ((undefined4 *) (*param_1)); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
  {
    if ((*((int *) (((int) puVar1) + 0x12))) != 0)
    {
      fn_004a06f0(*((undefined4 *) (((int) puVar1) + 0x12)));
    }
  }

  if (DAT_0070f287 != '\0')
  {
    fn_00447700(((int) param_1) + 0x12);
  }
  CodeGen_Generator(param_1);
  return;
}

void fn_0047c320(undefined1 *param_1)
{
  byte *pbVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined1 local_c[4];
  undefined1 local_8[4];
  switch (*param_1)
  {
    case 0x39:

    case 0x3a:
      pcVar2 = (char *) (*((char **) (param_1 + 0x10)));
      if ((((DAT_0070f208 != '\0') && (DAT_0070f220 == '\0')) && ((*pcVar2) == ';')) && (((((*((uint *) ((*((int *) (pcVar2 + 0x10))) + 0x14))) & 0x10) != 0) && ((*((char *) ((*((int *) (pcVar2 + 0x10))) + 2))) != '\x05')) && ((cVar3 = (char) fn_00452f60(*((undefined4 *) (pcVar2 + 0x10)), local_8, local_c), cVar3 == '\0'))))
    {
      CError_Warning(0x2866, *((undefined4 *) (pcVar2 + 0x10)), DAT_00716c9c);
    }
      break;

    case 0x3b:
      CMid_ObjectAddrRef((int) (*((undefined4 *) (param_1 + 0x10))));
      break;

    case 0x3e:
      if ((*((int *) ((*((int *) (param_1 + 0x10))) + 4))) != 0)
    {
      pbVar1 = (byte *) ((byte *) ((*((int *) ((*((int *) (param_1 + 0x10))) + 4))) + 6));
      *pbVar1 = (byte) ((*pbVar1) | 1);
    }
      break;

    case 0x3f:
      cmid_hasforce = (byte) 1;
      break;

    case 0x51:
      fn_00530810(param_1, 0);
      break;

    case 0x52:
      iVar4 = (int) fn_00543c00(*((undefined4 *) (param_1 + 0x10)), *((undefined4 *) (param_1 + 4)));
      *(NativeExpr *)param_1 = *(NativeExpr *)iVar4;

  }

  return;
}

void fn_0047c430(undefined4 *param_1)
{
  undefined4 *puVar1;
  cmid_hasforce = (byte) '\0';
  puVar1 = (undefined4 *) param_1;
  joined_r0x0047c444:
  do
  {
    if (((uint) puVar1) != ((uint) ((undefined4 *) 0x0)))
    {
      cmid_restartstmt = (byte) '\0';
      cmid_currentstmt = (uint) puVar1;
      switch (*((undefined1 *) (puVar1 + 1)))
      {
        case 1:

        case 2:

        case 3:

        case 0x10:
          break;

        case 4:

        case 5:

        case 6:

        case 7:

        case 0xc:

        case 0xd:

        case 0xe:

        case 0xf:
          switchD_0047c45f_caseD_4:
        fn_0055bc70(*((undefined4 *) (((int) puVar1) + 10)), fn_0047c4e0);

          break;

        case 8:
          if ((*((int *) (((int) puVar1) + 10))) != 0)
          goto switchD_0047c45f_caseD_4;
          break;

        default:
          CError_Internal(cmid_filename, 0x390);

      }

      if (cmid_restartstmt == '\0')
      {
        puVar1 = (undefined4 *) ((undefined4 *) (*puVar1));
        goto joined_r0x0047c444;
      }
      fn_005480b0(puVar1);
    }
    puVar1 = (undefined4 *) param_1;
    if (cmid_restartstmt == '\0')
    {
      if (cmid_hasforce != '\0')
      {
        for (; ((uint) param_1) != ((uint) ((undefined4 *) 0x0)); param_1 = (undefined4 *) ((undefined4 *) (*param_1)))
        {
          if (((*((char *) (param_1 + 1))) == '\x04') && ((*(*((char **) (((int) param_1) + 10)))) == '?'))
          {
            fn_005a3450(param_1);
          }
        }

      }
      return;
    }
  }
  while (1);

}

void fn_0047c4e0(char *node)
{ switch((byte)*node) { case 63:
 if(*(char **)(cmid_currentstmt+10)!=node) cmid_restartstmt=1;
 cmid_hasforce=1;
 } }


undefined1 fn_0047c510(int param_1, undefined4 param_2)
{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  char cVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 uVar7;
  cmid_objectrefs = (uint *) ((undefined4 *) 0x0);
  if (param_1 == 0)
  {
    fn_0055bc70(param_2, fn_0047cd90);
  }
  else
  {
    fn_0047c880((undefined4 *) param_1);
  }
  uVar7 = (undefined1) 0;
  puVar3 = (undefined4 *) cmid_objectrefs;
  do
  {
    if (((uint) puVar3) == ((uint) ((undefined4 *) 0x0)))
    {
      return (undefined1) uVar7;
    }
    iVar1 = (int) puVar3[1];
    puVar6 = (undefined4 *) cmid_pendingnodes;
    if (((byte) ((*((char *) (iVar1 + 2))) - 3U)) < 2)
    {
      for (; ((uint) puVar6) != ((uint) ((undefined4 *) 0x0)); puVar6 = (undefined4 *) ((undefined4 *) (*puVar6)))
      {
        if (puVar6[1] == iVar1)
        {
          uVar7 = (undefined1) 1;
          break;
        }
      }

      if (((uint) puVar6) == ((uint) ((undefined4 *) 0x0)))
      {
        if ((*(*((char **) (iVar1 + 0x10)))) != '\a')
        {
          CError_Internal(cmid_filename, 0x30a);
        }
        uVar2 = (uint) (*((uint *) ((*((int *) (iVar1 + 0x10))) + 0x16)));
        if ((uVar2 & 2) == 0)
        {
          if ((uVar2 & 0x100) == 0)
          {
            iVar5 = (int) fn_0053ebf0(iVar1);
            if (iVar5 == 0)
            {
              if ((((*((uint *) (iVar1 + 0x14))) & 0x10) != 0) && ((*((int *) (iVar1 + 0x48))) != 0))
              {
                puVar6 = (undefined4 *) ((undefined4 *) fn_0046c730(0x26));
                memclrw(puVar6, 0x26);
                *puVar6 = (undefined4) cmid_pendingnodes;
                puVar6[1] = (undefined4) iVar1;
                *((undefined1 *) (puVar6 + 9)) = (undefined1) 2;
                uVar7 = (undefined1) 1;
                cmid_pendingnodes = (uint *) puVar6;
              }
            }
            else
            {
              fn_0047c680((int) iVar1, (int) iVar5);
              uVar7 = (undefined1) 1;
            }
          }
          else
          {
            puVar6 = (undefined4 *) ((undefined4 *) fn_0046c730(0x26));
            memclrw(puVar6, 0x26);
            *puVar6 = (undefined4) cmid_pendingnodes;
            *((undefined1 *) (puVar6 + 9)) = (undefined1) 3;
            puVar6[1] = (undefined4) iVar1;
            uVar7 = (undefined1) 1;
            cmid_pendingnodes = (uint *) puVar6;
          }
        }
      }
    }
    else
      if ((DAT_00725e67 != '\0') && ((cVar4 = (char) fn_00452f10(iVar1), cVar4 != '\0')))
    {
      CMid_ObjectAddrRef((int) iVar1);
    }
    puVar3 = (undefined4 *) ((undefined4 *) (*puVar3));
  }
  while (1);
}

void fn_0047c680(int param_1, int param_2)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int local_18;
  int local_14;
  local_18 = (int) (*((int *) (param_2 + 4)));
  if (local_18 == 0)
  {
    if (((*(*((char **) (param_1 + 0x10)))) != '\a') || (((*((uint *) (param_1 + 0x14))) & 0x400000) == 0))
    {
      CError_Internal(cmid_filename, 699);
    }
    iVar3 = (int) (*((int *) (param_1 + 0x60)));
    if (((*((uint *) (iVar3 + 0x14))) & 0x10) == 0)
    {
      return;
    }
    if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x10) == 0)
    {
      CError_Internal(cmid_filename, 0x2c1);
    }
    local_18 = (int) fn_0053ed70(*((undefined4 *) ((*((int *) (param_1 + 0x10))) + 0x1e)));
    local_14 = (int) local_18;
    if (local_18 == 0)
    {
      CError_Internal(cmid_filename, 0x2c2);
    }
  }
  else
  {
    local_14 = (int) fn_0053ed70(local_18);
    iVar3 = (int) 0;
  }
  puVar1 = (undefined4 *) ((undefined4 *) fn_0046c730(0x26));
  memclrw(puVar1, 0x26);
  *puVar1 = (undefined4) cmid_pendingnodes;
  puVar1[1] = (undefined4) param_1;
  if (((*((uint *) (param_1 + 0x14))) & 0x400000) != 0)
  {
    uVar2 = (undefined4) fn_0053eae0();
    puVar1[2] = (undefined4) uVar2;
  }
  cmid_pendingnodes = (uint *) puVar1;
  if ((*((int *) (param_2 + 0x1c))) == 0)
  {
    *((undefined1 *) (puVar1 + 9)) = (undefined1) 0;
    puVar1[8] = (undefined4) local_18;
    puVar1[3] = (undefined4) (*((undefined4 *) (param_2 + 8)));
    puVar1[4] = (undefined4) (*((undefined4 *) (param_2 + 0xc)));
    puVar1[5] = (undefined4) (*((undefined4 *) (param_2 + 0x10)));
    uVar2 = (undefined4) (*((undefined4 *) (param_2 + 0x18)));
    puVar1[6] = (undefined4) (*((undefined4 *) (param_2 + 0x14)));
    puVar1[7] = (undefined4) uVar2;
  }
  else
  {
    *((undefined1 *) (puVar1 + 9)) = (undefined1) 1;
    puVar1[3] = (undefined4) local_14;
    puVar1[4] = (undefined4) param_2;
    puVar1[5] = (undefined4) iVar3;
  }
  return;
}

void fn_0047c7d0(undefined1 *param_1)
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  switch (*param_1)
  {
    case 0x3b:
      if ((*((char *) ((*((int *) (param_1 + 0x10))) + 2))) == '\x06')
    {
      fn_0055a640(param_1);
    }
      break;

    case 0x4b:
      if ((param_1[0x29] != '\0') && ((iVar1 = (int) (*((int *) (param_1 + 0x24))), iVar1 != 0)))
    {
      *(NativeExpr *)param_1 = *(NativeExpr *)iVar1;
      return;
    }

    case 0x43:
      *param_1 = (undefined1) 0x34;
      *((undefined4 *) (param_1 + 8)) = (undefined4) 0;
      *((undefined **) (param_1 + 4)) = (undefined *) (&DAT_00699c64);
      uVar2 = (undefined4) DAT_0070490c;
      *((undefined4 *) (param_1 + 0x10)) = (undefined4) DAT_00704908;
      *((undefined4 *) (param_1 + 0x14)) = (undefined4) uVar2;

  }

  return;
}

void fn_0047c880(undefined4 *param_1)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_1c[3];
  do
  {
    if (((uint) param_1) == ((uint) ((undefined4 *) 0x0)))
    {
      return;
    }
    for (puVar1 = (undefined4 *) (*((undefined4 **) (((int) param_1) + 0x12))); ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
    {
      switch (*((undefined1 *) (puVar1 + 7)))
      {
        case 1:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 2:
          iVar2 = (int) puVar1[3];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 3:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 4:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 5:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 6:
          iVar2 = (int) puVar1[3];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 7:

        case 0x11:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 8:
          iVar2 = (int) puVar1[3];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 9:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 10:

        case 0xb:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 0xc:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 0xd:

        case 0xe:

        case 0xf:

        case 0x10:

        case 0x12:
          break;

        case 0x13:

        case 0x14:
          iVar2 = (int) puVar1[2];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        case 0x15:
          iVar2 = (int) puVar1[3];
          switch (*((undefined1 *) (iVar2 + 2)))
        {
          case 0:

          case 3:

          case 4:
            for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
          {
            if (puVar3[1] == iVar2)
              goto switchD_0047c8b0_caseD_d;
          }

            puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
            puVar3[1] = (undefined4) iVar2;
            *puVar3 = (undefined4) cmid_objectrefs;
            cmid_objectrefs = (uint *) puVar3;

        }

          break;

        default:
          CError_Internal(cmid_filename, 0x1fe);

      }

      switchD_0047c8b0_caseD_d:
      ;

    }

    switch (*((undefined1 *) (param_1 + 1)))
    {
      case 1:

      case 2:

      case 3:

      case 0xc:

      case 0xd:

      case 0xe:
        break;

      case 4:

      case 5:

      case 6:

      case 7:

      case 0xf:
        switchD_0047cd7c_caseD_4:
      fn_0055bc70(*((undefined4 *) (((int) param_1) + 10)), fn_0047cd90);

        break;

      case 8:
        if ((*((int *) (((int) param_1) + 10))) != 0)
        goto switchD_0047cd7c_caseD_4;
        break;

      default:
        CError_Internal(cmid_filename, 0x226);
        break;

      case 0x10:
        fn_0055c750(param_1, local_1c);
        for (puVar1 = (undefined4 *) local_1c[2]; ((uint) puVar1) != ((uint) ((undefined4 *) 0x0)); puVar1 = (undefined4 *) ((undefined4 *) (*puVar1)))
      {
        if ((*((char *) (puVar1 + 2))) == '\0')
        {
          iVar2 = (int) (*((int *) (local_1c[0] + puVar1[1])));
          switch (*((undefined1 *) (iVar2 + 2)))
          {
            case 0:

            case 3:

            case 4:
              for (puVar3 = (undefined4 *) cmid_objectrefs; ((uint) puVar3) != ((uint) ((undefined4 *) 0x0)); puVar3 = (undefined4 *) ((undefined4 *) (*puVar3)))
            {
              if (puVar3[1] == iVar2)
                goto switchD_0047ccf8_caseD_1;
            }

              puVar3 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
              puVar3[1] = (undefined4) iVar2;
              *puVar3 = (undefined4) cmid_objectrefs;
              cmid_objectrefs = (uint *) puVar3;

          }

        }
        switchD_0047ccf8_caseD_1:
        ;

      }


    }

    param_1 = (undefined4 *) ((undefined4 *) (*param_1));
  }
  while (1);
}

void fn_0047cd90(char *param_1)
{
  int iVar1;
  undefined4 *puVar2;
  if ((*param_1) == ';')
  {
    iVar1 = (int) (*((int *) (param_1 + 0x10)));
    switch (*((undefined1 *) (iVar1 + 2)))
    {
      case 0:

      case 3:

      case 4:
        for (puVar2 = (undefined4 *) cmid_objectrefs; ((uint) puVar2) != ((uint) ((undefined4 *) 0x0)); puVar2 = (undefined4 *) ((undefined4 *) (*puVar2)))
      {
        if (puVar2[1] == iVar1)
        {
          return;
        }
      }

        puVar2 = (undefined4 *) ((undefined4 *) CompilerTools_AllocatePool(8));
        puVar2[1] = (undefined4) iVar1;
        *puVar2 = (undefined4) cmid_objectrefs;
        cmid_objectrefs = (uint *) puVar2;

    }

  }
  return;
}

undefined4 fn_0047cde0(int param_1)
{
  switch (*((undefined1 *) (param_1 + 2)))
  {
    case 0:
      break;

    default:
      return (undefined4) 0;

    case 2:
      return (undefined4) 0;

    case 3:

    case 4:
      CError_Internal(cmid_filename, 0x176);

  }

  return (undefined4) (*((undefined4 *) (param_1 + 0x4c)));
}

undefined4 fn_0047ce20(int param_1)
{
  if (((*((char *) (param_1 + 2))) != '\x03') && ((*((char *) (param_1 + 2))) != '\x04'))
  {
    CError_Internal(cmid_filename, 0x166);
  }
  if (((*((uint *) (param_1 + 0x14))) & 0x800000) == 0)
  {
    CError_Internal(cmid_filename, 0x167);
  }
  return (undefined4) (*((undefined4 *) (param_1 + 0x40)));
}

void fn_0047ce70(int param_1)
{
  if (((*((char *) (param_1 + 2))) != '\x03') && ((*((char *) (param_1 + 2))) != '\x04'))
  {
    CError_Internal(cmid_filename, 0x151);
  }
  if (((*((uint *) (param_1 + 0x14))) & 0x800000) != 0)
  {
    CError_Internal(cmid_filename, 0x152);
  }
  if ((*(*((char **) (param_1 + 0x10)))) != '\a')
  {
    CError_Internal(cmid_filename, 0x153);
  }
  if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x100000) != 0)
  {
    CError_Internal(cmid_filename, 0x154);
  }
  if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x200) != 0)
  {
    CError_Internal(cmid_filename, 0x155);
  }
  if (((uint) (*((undefined4 **) (param_1 + 0x40)))) != ((uint) ((undefined4 *) 0x0)))
  {
    fn_00509f00(*(*((undefined4 **) (param_1 + 0x40))));
    fn_0046c6e0(*((undefined4 *) (param_1 + 0x40)), 0xc6);
    *((undefined4 *) (param_1 + 0x40)) = (undefined4) 0;
  }
  return;
}

void fn_0047cf40(int param_1, int *param_2)
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  if (((*((char *) (param_1 + 2))) != '\x03') && ((*((char *) (param_1 + 2))) != '\x04'))
  {
    CError_Internal(cmid_filename, 0x136);
  }
  if (((*((uint *) (param_1 + 0x14))) & 0x800000) != 0)
  {
    CError_Internal(cmid_filename, 0x137);
  }
  if ((*(*((char **) (param_1 + 0x10)))) != '\a')
  {
    CError_Internal(cmid_filename, 0x138);
  }
  if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x100000) != 0)
  {
    CError_Internal(cmid_filename, 0x139);
  }
  if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x200) != 0)
  {
    CError_Internal(cmid_filename, 0x13a);
  }
  if (((uint) (*((int **) (param_1 + 0x40)))) == ((uint) ((int *) 0x0)))
  {
    uVar2 = (undefined4) fn_0046c730(0xc6);
    *((undefined4 *) (param_1 + 0x40)) = (undefined4) uVar2;
  }
  else
  {
    iVar1 = (int) (*(*((int **) (param_1 + 0x40))));
    if (iVar1 != (*param_2))
    {
      fn_00509f00(iVar1);
    }
  }
  iVar1 = (int) (*((int *) (param_1 + 0x40)));
  *(NativeInline *)iVar1 = *(NativeInline *)param_2;
  return;
}

undefined4 fn_0047d080(int param_1)
{
  char cVar1;
  cVar1 = (char) (*((char *) (param_1 + 2)));
  if (cVar1 == '\x05')
  {
    return (undefined4) 0;
  }
  if ((cVar1 != '\x03') && (cVar1 != '\x04'))
  {
    CError_Internal(cmid_filename, 0x124);
  }
  if (((*((uint *) (param_1 + 0x14))) & 0x800000) != 0)
  {
    CError_Internal(cmid_filename, 0x125);
  }
  if ((*(*((char **) (param_1 + 0x10)))) != '\a')
  {
    CError_Internal(cmid_filename, 0x126);
  }
  if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x100000) != 0)
  {
    CError_Internal(cmid_filename, 0x127);
  }
  if (((*((uint *) ((*((int *) (param_1 + 0x10))) + 0x16))) & 0x200) == 0)
  {
    return (undefined4) (*((undefined4 *) (param_1 + 0x40)));
  }
  return (undefined4) 0;
}

void CMid_SetupIPA(char param_1)
{
  DAT_00725e67 = (byte) (param_1 != '\0');
  DAT_00725edf = (byte) param_1;
  if (param_1 != '\0')
  {
    DAT_0070f1bb = (byte) 1;
  }
  return;
}

void CMid_Cleanup(void)
{
  fn_005a17d0();
  return;
}

void CMid_Setup(void)
{
  cmid_deferredinline = (uint *) 0;
  cmid_pendingnodes = (uint *) 0;
  DAT_00710148 = (uint *) 0;
  DAT_00716c24 = (uint *) 0;
  cmid_pendingclasses = (uint *) 0;
  cmid_dummyfuncs = (uint *) 0;
  DAT_00715c2c = (uint *) 0;
  cmid_firstfile = (int) 0xffffffff;
  fn_005a1820();
  return;
}



#pragma pack(pop)
