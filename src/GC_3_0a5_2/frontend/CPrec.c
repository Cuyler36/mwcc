/* GC 3.0a5.2 CPrec native serialization family. */
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned char bool;
#define true 1
#define false 0
#define CONCAT11(a,b) (((ushort)(byte)(a)<<8)|(byte)(b))
#define CONCAT21(a,b) (((uint)(ushort)(a)<<8)|(byte)(b))
#define CONCAT31(a,b) (((uint)(a)<<8)|(byte)(b))
#define CONCAT22(a,b) (((uint)(ushort)(a)<<16)|(ushort)(b))
#define AT32(p,o) (*(uint *)((byte *)(p)+(o)))
#define AT16(p,o) (*(ushort *)((byte *)(p)+(o)))
#pragma options align=mac68k
typedef struct NativeBucketEntry { struct NativeBucketEntry *next; uint offset; } NativeBucketEntry;
typedef struct NativeBucket { uint original,offset; NativeBucketEntry *list; } NativeBucket;
#pragma options align=reset
extern NativeBucket *NativeBuckets;

#pragma options align=mac68k
typedef struct NativeHeaderCopy { uint words[0x1436]; ushort last; } NativeHeaderCopy;
typedef struct NativeIncludedFile { uint file; byte flag,pad; struct NativeIncludedFile *next; } NativeIncludedFile;
#pragma options align=reset
extern NativeIncludedFile *NativeIncludedHead, *NativeIncludedTail;

extern uint DAT_006771bc;
extern uint DAT_006771c2;
extern uint DAT_006771c8;
extern uint DAT_006771e4;
static char DAT_0067dccc[]="\"\r\n";
static char DAT_0067dd50[]="";
extern uint DAT_00699c1c;
extern uint DAT_00699c1e;
extern uint DAT_00699c24;
extern uint DAT_00699c2c;
extern uint DAT_00699c34;
extern uint DAT_00699c3c;
extern uint DAT_00699c3e;
extern uint DAT_00699c44;
extern uint DAT_00699c4c;
extern uint DAT_00699c54;
extern uint DAT_00699c5c;
extern uint DAT_00699c64;
extern uint DAT_00699c6c;
extern uint DAT_00699c74;
extern uint DAT_00699c7c;
extern uint DAT_00699c84;
extern uint DAT_00699c8c;
extern uint DAT_00699c94;
extern uint DAT_00699c9c;
extern uint DAT_00699ca4;
extern uint DAT_0069a15c;
extern uint DAT_0069a16e;
extern uint DAT_0069a180;
extern uint DAT_0069a192;
extern uint DAT_0069a1a4;
extern uint DAT_0069a1b6;
extern uint DAT_0069a1c8;
extern uint DAT_0069a1da;
extern uint DAT_0069a1ec;
extern uint DAT_0069a1fe;
extern uint DAT_0069a210;
extern uint DAT_006daed0;
extern uint DAT_006daed4;
extern uint DAT_006daed8;
extern uint DAT_006daedc;
extern uint DAT_006daee0;
extern byte DAT_006daee5;
extern uint DAT_006daee6;
extern uint DAT_006daeea;
extern uint DAT_006daeee;
extern uint DAT_006daef6;
extern int DAT_006daefa;
extern uint DAT_006daefe;
extern uint DAT_006daf02;
extern uint DAT_006daf06;
extern uint DAT_006daf0a;
extern uint DAT_006daf0e;
extern uint DAT_006daf12;
extern uint DAT_006daf16;
extern uint *DAT_006daf1a;
extern int DAT_006daf1e;
extern uint DAT_006daf2a;
extern uint DAT_006daf2e;
extern uint DAT_007037c0;
extern uint DAT_00704910;
extern uint DAT_0070bb08;
extern uint DAT_0070c6a0;
extern byte DAT_0070f08c;
extern byte DAT_0070f1a8;
extern byte DAT_0070f1af;
extern byte DAT_0070f1c5;
extern byte DAT_0070f1fa;
extern uint DAT_0070f290;
extern uint DAT_0070f294;
extern uint DAT_0070f848;
extern uint DAT_0071008c;
extern uint DAT_00710144;
extern uint DAT_00710148;
extern uint DAT_007101c4;
extern uint DAT_007102c8;
extern uint DAT_00710330;
extern uint DAT_00710340;
extern uint DAT_0071034c;
extern uint DAT_00710360;
extern uint DAT_007107a8;
extern uint DAT_007107ac;
extern uint DAT_007107b8;
extern uint DAT_0071081c;
extern uint DAT_00710858;
extern uint DAT_007108b4;
extern uint DAT_007108c0;
extern uint DAT_00710928;
extern uint DAT_0071092c;
extern uint DAT_007109c4;
extern uint DAT_00710b38;
extern uint DAT_00711af8;
extern uint DAT_00711b00;
extern uint DAT_00711b1c;
extern uint DAT_00711b24;
extern uint DAT_00711b80;
extern uint DAT_00711bb8;
extern uint DAT_00711be0;
extern uint DAT_00715c00;
extern uint DAT_00715c04;
extern uint *DAT_00715c08;
extern uint DAT_00715c18;
extern uint DAT_00715c2c;
extern uint DAT_00715c58;
extern uint DAT_00716c1c;
extern uint DAT_00716c24;
extern uint DAT_00716c98;
extern uint DAT_00716cac;
extern uint DAT_00716cd8;
extern uint DAT_00716ce4;
extern uint DAT_00716d18;
extern uint DAT_00716d3c;
extern uint DAT_00716d60;
extern uint DAT_00716d68;
extern uint DAT_00716ed2;
extern uint DAT_0071726c;
extern uint DAT_00725d96;
extern byte DAT_00725e5e;
extern byte DAT_00725ffe;
extern uint _DAT_006daef2;
static char s_CPrec_c_0067dd1c[]="CPrec.c";
static char s__C_C___Preprocessor_Panel__0067dd24[]="(C-C++ Preprocessor Panel)";
static char s___tmpfile_mch_0067dd40[]="$$tmpfile.mch";
static char s__bool__size_mismatch_0067dce8[]="'bool' size mismatch";
static char s__command_line_defines__0067dd54[]="(command-line defines)";
static char s__include___0067dcc0[]="#include \"";
static char s__include__c_s_c_0067dd6c[]="#include %c%s%c\n";
static char s__wchar_t__size_mismatch_0067dcd0[]="'wchar_t' size mismatch";
static char s_runtime_objects_mismatch_0067dd00[]="runtime objects mismatch";
extern uint *NativeHeaderWords;
extern uint *NativeContextWords;
extern uint *NativeHashNameWords;
extern uint AppendGListByte();
extern uint AppendGListLong();
extern uint AppendGListWord();
extern uint CError_Internal();
extern uint CError_LongJump();
extern uint CError_ReportError();
extern uint CError_Warning();
extern uint CParser_ReInitRuntimeObjects();
extern uint CompilerTools_AllocateBlock();
extern uint CompilerTools_AllocatePool();
extern uint CompilerTools_AppendGListData();
extern uint FUN_004047c0();
extern uint __stdcall FUN_00420060(uint, uint, uint, uint, uint, uint);
extern uint __stdcall FUN_00420190(uint);
extern uint __stdcall FUN_00420330(uint, uint, uint, uint);
extern uint __stdcall FUN_00420590(uint, uint, uint, uint);
extern uint __stdcall FUN_004206c0(uint, uint, uint, uint);
extern uint __stdcall FUN_00420720(uint, uint);
extern uint FUN_00447970();
extern uint FUN_00447990();
extern uint FUN_004490c0();
extern uint FUN_004490d0();
extern uint FUN_0044b8d0();
extern uint FUN_0044ba70();
extern uint FUN_0044c0e0();
extern uint FUN_0044c4d0();
extern uint FUN_0044cab0();
extern uint FUN_0044cfe0();
extern uint FUN_0044d0a0();
extern uint FUN_0044d1b0();
extern uint FUN_0044d3f0();
extern uint FUN_0044d580();
extern uint FUN_0044d600();
extern uint FUN_0044d730();
extern uint FUN_0044d740();
extern uint FUN_0044d7d0();
extern uint FUN_0044d7f0();
extern uint FUN_0044d810();
extern uint FUN_0044d850();
extern uint FUN_0044d890();
extern uint FUN_0044d8b0();
extern uint FUN_0044d8e0();
extern uint FUN_0044d9f0();
extern uint FUN_0044dd40();
extern uint FUN_0044dda0();
extern uint FUN_0044de10();
extern undefined8 FUN_0044dfd0();
extern uint FUN_00455e90();
extern uint FUN_00455f20();
extern uint FUN_00456ba0();
extern uint __stdcall FUN_00458b80(uint, uint, uint);
extern uint __stdcall FUN_00458cc0(uint, uint, uint, uint);
extern uint FUN_0045a1e0();
extern uint FUN_0046bc90();
extern uint FUN_0046c550();
extern uint FUN_0046c620();
extern uint FUN_0046d880();
extern uint FUN_0046d950();
extern uint FUN_0046d960();
extern uint FUN_0046db20();
extern uint FUN_0047ecc0();
extern uint FUN_004be110();
extern uint FUN_004be1f0();
extern uint FUN_004be300();
extern uint FUN_004c0120();
extern uint FUN_004d42d0();
extern uint FUN_004d8380();
extern uint FUN_004eb250();
extern uint FUN_0053ed70();
extern uint FUN_0053edb0();
extern uint FUN_0053ede0();
extern uint FUN_0053ee10();
extern uint FUN_0053ee70();
extern uint FUN_0053eea0();
extern uint FUN_00544130();
extern uint FUN_00544180();
extern uint FUN_005441e0();
extern uint FUN_005442b0();
extern uint FreeGList();
extern uint GetHashNameNode();
extern uint InitGList();
extern uint __stdcall fn_0041b8d0(uint, uint, uint);
extern uint galloc();
extern uint longjmp();
extern uint memclrw();
extern uint memcpy();
extern uint snprintf();
extern uint sprintf();
extern uint g_pPendingVTableClasses;
extern void LAB_00449230(void);
static byte NativeCPrecState[99];

void PrecompilerExpand(uint *fileInfo, uint file, byte *memory, uint length, uint *output);
byte PrecompilerCheckCompressed(byte *object, uint file, byte *memory, uint length);
void fn_0046e160(undefined4 param_1, int *param_2, uint param_3);
void PrecompilerRead(int *param_1, int param_2, int *param_3, uint length);
bool PrecompilerCheck(int param_1, undefined4 param_2, int *param_3, int param_4);
void fn_0046eb90(void);
void fn_0046ed70(int *param_1);
void fn_0046ee50(void);
void fn_0046ef30(void);
void fn_0046f090(void);
int fn_0046f2d0(void);
int fn_0046f600(void);
int fn_0046fd40(void);
void CPrec_FileIncludedCallback(uint file, byte flag);
int fn_00470020(char param_1);
int fn_00470f50(void);
int fn_00471090(char *param_1, int param_2);
void fn_00471180(void);
uint fn_00471260(int *param_1);
uint fn_00471380(int *param_1);
void fn_00471580(void);
uint fn_00471720(int *param_1);
uint fn_00471a60(uint *param_1, char param_2);
uint fn_00471db0(uint *param_1);
uint fn_00471ff0(int *param_1);
uint fn_00472180(undefined1 *param_1);
uint fn_004721e0(uint param_1);
uint fn_004728b0(uint param_1);
uint fn_00472b80(uint param_1);
uint fn_00472cb0(uint param_1);
uint fn_00472de0(uint param_1);
uint fn_00472f10(uint param_1);
uint fn_004731a0(int *param_1);
uint fn_00473300(undefined4 *param_1);
uint fn_00473510(char *param_1);
uint fn_00474430(int *param_1);
uint fn_004745c0(int *param_1);
uint fn_00474790(int *param_1);
uint fn_00474960(int *param_1);
uint fn_00474b70(int *param_1);
void fn_00474dc0(int *param_1, int param_2);
uint fn_00474e70(int *param_1);
uint fn_00475030(char *param_1);
uint fn_00475390(char *param_1);
uint fn_004755d0(uint param_1);
uint fn_00475960(uint param_1);
uint fn_00475ca0(int *param_1);
uint fn_00476020(int *param_1);
uint fn_00476240(int *param_1);
uint fn_00476380(int *param_1);
uint fn_00476490(int *param_1);
uint fn_00476670(int *param_1);
uint fn_00476950(short *param_1, int param_2);
uint fn_00476c20(int *param_1);
uint fn_00476dd0(int *param_1);
uint fn_00476f20(int *param_1);
uint fn_00476fb0(int *param_1);
uint fn_004771c0(int *param_1);
uint fn_004772b0(uint *param_1);
uint fn_00477490(uint param_1);
uint fn_004776f0(uint param_1);
uint fn_00477940(uint *param_1, char param_2);
uint fn_00477bb0(uint param_1);
uint fn_00477d80(uint param_1);
uint fn_00477eb0(uint param_1);
uint fn_00478080(undefined4 *param_1);
uint fn_004781b0(int *param_1);
void fn_00478580(void);
void fn_004787f0(void);
void fn_00478bb0(undefined4 param_1, int param_2);
void fn_00478bd0(int param_1, uint param_2);
void fn_00478cc0(int param_1, uint param_2);
void fn_00478d90(void);
void CleanupPrecompiler(void);
void SetupPrecompiler(void);

void PrecompilerExpand(uint *fileInfo, uint file, byte *memory, uint length, uint *output)
{
    NativeHeaderCopy header;
    byte *input, *end, *dest, *expected;
    uint dataOffset, compressedSize, dataSize, tailSize, oldSize, i, token, offsets[6];
    int count;
    DAT_006daf2a = (uint )((uint )(file));
    DAT_006daeee = (uint )((uint )((uint)memory));
    DAT_006daed8 = (uint )((uint )(FUN_0044d1b0(*fileInfo + 10)));
    if (memory) header = *(NativeHeaderCopy *)memory;
    else {
        if (FUN_0044d890(file, 0) || FUN_0044d810(file, &header, sizeof(header))) goto readError;
    }
    dataSize = AT32(&header,0x32);
    compressedSize = AT32(&header,0x36);
    dataOffset = (uint)((uint)(AT32(&header,0x3a)));
    offsets[0]=0x2e; offsets[1]=0x46; offsets[2]=0x4e;
    offsets[3]=0x56; offsets[4]=0xce; offsets[5]=0xd6;
    for (i=0; i<6; ++i)
        if (AT32(&header,offsets[i]) >= dataOffset + compressedSize)
            AT32(&header,offsets[i]) += dataSize - compressedSize;
    AT32(&header,0x36)=dataSize;
    CompilerTools_AppendGListData(output, &header, sizeof(header));
    if (memory) CompilerTools_AppendGListData(output, memory+sizeof(header), dataOffset-sizeof(header));
    else {
        oldSize=output[1];
        FUN_0046d880(output,dataOffset-sizeof(header));
        FUN_0046d960(output);
        dest=(byte *)*(uint *)output[0]+oldSize;
        if (FUN_0044d890(file,sizeof(header)) || FUN_0044d810(file,dest,dataOffset-sizeof(header))) goto readError;
        FUN_0046d950(output);
    }
    if (memory) input=memory+dataOffset;
    else {
        input = (byte *)((byte *)((byte *)FUN_0046c620(compressedSize)));
        if (FUN_0044d890(file,dataOffset) || FUN_0044d810(file,input,compressedSize)) goto readError;
    }
    end=input+compressedSize;
    oldSize=output[1];
    FUN_0046d880(output,dataSize);
    dest=(byte *)*(uint *)output[0]+oldSize;
    expected=dest+dataSize;
    while (input<end) {
        token=*input++;
        if (token>=0xe0) { count=(int)token-0xe0; do { *dest++=0; --count; } while (count>=0); }
        else { count=(int)token; do { *dest++=*input++; --count; } while (count>=0); }
    }
    if (input!=end || dest!=expected) goto readError;
    tailSize=length-dataOffset-compressedSize;
    if (memory) CompilerTools_AppendGListData(output, memory+dataOffset+compressedSize, tailSize);
    else {
        oldSize=output[1];
        FUN_0046d880(output,tailSize);
        FUN_0046d960(output);
        dest=(byte *)*(uint *)output[0]+oldSize;
        if (FUN_0044d890(file,dataOffset+compressedSize) || FUN_0044d810(file,dest,tailSize)) goto readError;
        FUN_0046d950(output);
    }
    return;
readError:
    if (DAT_006daf2a) FUN_0044d730(DAT_006daf2a);
    FUN_00447990(0x27c5,DAT_006daed8);
    longjmp(&DAT_00704910,1);
}


byte PrecompilerCheckCompressed(byte *object, uint file, byte *memory, uint length)
{
    NativeHeaderCopy header;
    if (object[8] == 0 && ((object[0x32] >> 1) & 1)) return 0;
    if (length < sizeof(header)) return 0;
    if (memory) header = *(NativeHeaderCopy *)memory;
    else if (FUN_0044d600(file, 0, &header, sizeof(header))) return 0;
    return AT32(&header,0) == 0xbeefface && AT16(&header,4) == 0x42d &&
        AT32(&header,0x36) != AT32(&header,0x32);
}


void fn_0046e160(undefined4 param_1, int *param_2, uint param_3)
{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  if (*param_2 != -0x41100532) {
    return;
  }
  if (*(ushort *)(param_2 + 1) < 0x428) {
    return;
  }
  if (param_3 < (uint)(*(int *)((int)param_2 + 0x2e) + *(int *)((int)param_2 + 0x2a))) {
    return;
  }
  pcVar4 = (char *)((char *)((int)param_2 + *(int *)((int)param_2 + 0x2e)));
  iVar2 = (int)(-1);
  pcVar6 = (char *)(pcVar4);
  do {
    if (iVar2 == 0) break;
    iVar2 = (int)(iVar2 - 1);
    cVar1 = (char)(*pcVar6);
    pcVar6 = (char *)(pcVar6 + 1);
  } while (cVar1 != '\0');
  pcVar5 = (char *)(pcVar4 + -iVar2 + -1);
  iVar2 = (int)(-1);
  pcVar6 = (char *)(pcVar5);
  do {
    if (iVar2 == 0) break;
    iVar2 = (int)(iVar2 - 1);
    cVar1 = (char)(*pcVar6);
    pcVar6 = (char *)(pcVar6 + 1);
  } while (cVar1 != '\0');
  iVar3 = (int)(-1);
  pcVar6 = (char *)(pcVar5 + -iVar2 + -1);
  do {
    if (iVar3 == 0) break;
    iVar3 = (int)(iVar3 - 1);
    cVar1 = (char)(*pcVar6);
    pcVar6 = (char *)(pcVar6 + 1);
  } while (cVar1 != '\0');
  if ((char *)((int)param_2 + param_3) < pcVar5 + -iVar2 + -1 + (-iVar3 - 2)) {
    return;
  }
  FUN_0046bc90(param_1, pcVar5);
  FUN_0046bc90(param_1, s__include___0067dcc0);
  FUN_0046bc90(param_1, pcVar4);
  FUN_0046bc90(param_1, &DAT_0067dccc);
  return;
}

void PrecompilerRead(int *param_1, int param_2, int *param_3, uint length)
{
  undefined4 *puVar1;
  char cVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  DAT_006daed8 = (uint )(FUN_0044d1b0(*param_1 + 10));
  DAT_006daf2a = (uint )(param_2);
  DAT_006daeee = (uint )(param_3);
  FUN_004490c0();
  cVar2 = (char)(FUN_004eb250());
  if (cVar2 == '\0') {
    if (DAT_006daf2a != 0) {
      FUN_0044d730(DAT_006daf2a);
    }
    FUN_00447970(0x27c4);
  }
  if (DAT_006daeee == 0) {
    piVar3 = (int *)((int *)galloc(0x50da));
    NativeHeaderWords = (uint *)(piVar3);
    iVar7 = (int)(FUN_0044d890(DAT_006daf2a, 0));
    if ((iVar7 != 0) || (iVar7 = FUN_0044d810(DAT_006daf2a, piVar3, 0x50da), iVar7 != 0)) {
      uVar5 = (undefined4)(DAT_006daed8);
      if (DAT_006daf2a != 0) {
        FUN_0044d730(DAT_006daf2a);
      }
      FUN_00447990(0x27c5, uVar5);
                    /* WARNING: Subroutine does not return */
      longjmp(&DAT_00704910, 1);
    }
  }
  else {
    NativeHeaderWords = (uint *)(DAT_006daeee);
  }
  uVar5 = (undefined4)(DAT_006daed8);
  if (*NativeHeaderWords != -0x41100532) {
    if (DAT_006daf2a != 0) {
      FUN_0044d730(DAT_006daf2a);
    }
    FUN_00447990(0x27c5, uVar5);
                    /* WARNING: Subroutine does not return */
    longjmp(&DAT_00704910, 1);
  }
  if ((short)NativeHeaderWords[1] != 0x42d) {
    if (DAT_006daf2a != 0) {
      FUN_0044d730(DAT_006daf2a);
    }
    FUN_00447990(0x27ee, uVar5);
                    /* WARNING: Subroutine does not return */
    longjmp(&DAT_00704910, 1);
  }
  if ((short)NativeHeaderWords[2] != -0x29d7) {
    if (DAT_006daf2a != 0) {
      FUN_0044d730(DAT_006daf2a);
    }
    FUN_00447990(0x27ee, uVar5);
                    /* WARNING: Subroutine does not return */
    longjmp(&DAT_00704910, 1);
  }
  if (*(char *)((int)NativeHeaderWords + 10) != '\x02') {
    if (DAT_006daf2a != 0) {
      FUN_0044d730(DAT_006daf2a);
    }
    FUN_00447990(0x27ef, uVar5);
                    /* WARNING: Subroutine does not return */
    longjmp(&DAT_00704910, 1);
  }
  if (*(char *)((int)NativeHeaderWords + 0x11) != DAT_00699c3e) {
    if (DAT_006daf2a != 0) {
      FUN_0044d730(DAT_006daf2a);
    }
    FUN_00447990(0x27ef, s__wchar_t__size_mismatch_0067dcd0);
                    /* WARNING: Subroutine does not return */
    longjmp(&DAT_00704910, 1);
  }
  if (*(char *)((int)NativeHeaderWords + 0x12) != DAT_00699c1e) {
    if (DAT_006daf2a != 0) {
      FUN_0044d730(DAT_006daf2a);
    }
    FUN_00447990(0x27ef, s__bool__size_mismatch_0067dce8);
                    /* WARNING: Subroutine does not return */
    longjmp(&DAT_00704910, 1);
  }
  if (*(char *)((int)NativeHeaderWords + 0x13) != '\0') {
    DAT_00725e5e = (byte )(1);
  }
  DAT_0070f1fa = (byte )(*(undefined1 *)((int)NativeHeaderWords + 0xb));
  if (DAT_00725ffe != '\0') {
    if (DAT_006daeee == 0) {
      uVar4 = (undefined4)(CompilerTools_AllocateBlock(*(undefined4 *)((int)NativeHeaderWords + 0x2a)));
      uVar5 = (undefined4)(*(undefined4 *)((int)NativeHeaderWords + 0x2a));
      iVar7 = (int)(FUN_0044d890(DAT_006daf2a, *(undefined4 *)((int)NativeHeaderWords + 0x2e)));
      if ((iVar7 != 0) || (iVar7 = FUN_0044d810(DAT_006daf2a, uVar4, uVar5), iVar7 != 0)) {
        uVar5 = (undefined4)(DAT_006daed8);
        if (DAT_006daf2a != 0) {
          FUN_0044d730(DAT_006daf2a);
        }
        FUN_00447990(0x27c5, uVar5);
                    /* WARNING: Subroutine does not return */
        longjmp(&DAT_00704910, 1);
      }
    }
    FUN_004d8380(param_1);
  }
  fn_0046f090();
  fn_0046ef30();
  fn_0046ee50();
  iVar7 = (int)(DAT_006daeea);
  piVar6 = (int *)((int *)((int)NativeHeaderWords + 0xda));
  iVar8 = (int)(0);
  piVar3 = (int *)(NativeHashNameWords);
  do {
    if (*piVar6 == 0) {
      *piVar3 = (uint)(0);
    }
    else {
      *piVar3 = (uint)(*piVar6 + iVar7);
    }
    iVar8 = (int)(iVar8 + 1);
    piVar6 = (int *)(piVar6 + 1);
    piVar3 = (int *)(piVar3 + 1);
  } while (iVar8 < 0x800);
  iVar7 = (int)(0);
  do {
    for (puVar1 = (undefined4 *)NativeHashNameWords[iVar7]; puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      puVar1[1] = (uint)(0xffffffff);
    }
    iVar7 = (int)(iVar7 + 1);
  } while (iVar7 < 0x800);
  fn_0046eb90();
  iVar7 = (int)(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0xce));
  while (iVar7 != 0) {
    iVar8 = (int)(*(int *)(iVar7 + 4));
    fn_0046ed70((int *)(iVar7));
    FUN_0044b8d0(iVar7);
    iVar7 = (int)(iVar8);
  }
  if ((*(int *)((int)NativeHeaderWords + 0x52) != 0) && (DAT_006daeee == 0)) {
    uVar4 = (undefined4)(CompilerTools_AllocatePool(*(int *)((int)NativeHeaderWords + 0x52)));
    uVar5 = (undefined4)(*(undefined4 *)((int)NativeHeaderWords + 0x52));
    iVar7 = (int)(FUN_0044d890(DAT_006daf2a, *(undefined4 *)((int)NativeHeaderWords + 0x56)));
    if ((iVar7 != 0) || (iVar7 = FUN_0044d810(DAT_006daf2a, uVar4, uVar5), iVar7 != 0)) {
      uVar5 = (undefined4)(DAT_006daed8);
      if (DAT_006daf2a != 0) {
        FUN_0044d730(DAT_006daf2a);
      }
      FUN_00447990(0x27c5, uVar5);
                    /* WARNING: Subroutine does not return */
      longjmp(&DAT_00704910, 1);
    }
  }
  if (*(char *)(DAT_007101c4 + 0x1c) == '\0') {
    CError_Internal(s_CPrec_c_0067dd1c, 0x184d);
  }
  iVar8 = (int)(DAT_007101c4);
  piVar3 = (int *)(NativeHeaderWords);
  *(undefined4 *)(DAT_007101c4 + 0x18) = *(undefined4 *)((int)NativeHeaderWords + 0x5a);
  iVar7 = (int)(DAT_006daeea);
  piVar6 = (int *)(*(int **)(iVar8 + 0x14));
  piVar3 = (int *)((int *)((int)piVar3 + 0x40da));
  iVar8 = (int)(0);
  do {
    if (*piVar3 == 0) {
      *piVar6 = (uint)(0);
    }
    else {
      *piVar6 = (uint)(*piVar3 + iVar7);
    }
    iVar8 = (int)(iVar8 + 1);
    piVar3 = (int *)(piVar3 + 1);
    piVar6 = (int *)(piVar6 + 1);
  } while (iVar8 < 0x400);
  if (*(int *)((int)NativeHeaderWords + 0x5e) == 0) {
    *(undefined4 *)(DAT_007101c4 + 8) = 0;
  }
  else {
    *(int *)(DAT_007101c4 + 8) = DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x5e);
  }
  if (*(int *)((int)NativeHeaderWords + 0x62) == 0) {
    DAT_00710b38 = (uint )(0);
  }
  else {
    DAT_00710b38 = (uint )(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x62));
  }
  if (*(int *)((int)NativeHeaderWords + 0x7a) == 0) {
    DAT_00711af8 = (uint )(0);
  }
  else {
    DAT_00711af8 = (uint )(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x7a));
  }
  if (*(int *)((int)NativeHeaderWords + 0x6a) == 0) {
    DAT_00710148 = (uint )(0);
  }
  else {
    DAT_00710148 = (uint )(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x6a));
  }
  if (*(int *)((int)NativeHeaderWords + 0x76) == 0) {
    DAT_007107a8 = (uint )(0);
  }
  else {
    DAT_007107a8 = (uint )(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x76));
  }
  if (*(int *)((int)NativeHeaderWords + 0x7e) == 0) {
    DAT_00716c24 = (uint )(0);
  }
  else {
    DAT_00716c24 = (uint )(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x7e));
  }
  if (*(int *)((int)NativeHeaderWords + 0x86) == 0) {
    DAT_00715c2c = (uint )(0);
  }
  else {
    DAT_00715c2c = (uint )(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x86));
  }
  if (*(int *)((int)NativeHeaderWords + 0x82) == 0) {
    DAT_00716d18 = (uint )(0);
  }
  else {
    DAT_00716d18 = (uint )(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x82));
  }
  if (*(int *)((int)NativeHeaderWords + 0x72) == 0) {
    g_pPendingVTableClasses = (uint )((void *)0x0);
  }
  else {
    g_pPendingVTableClasses = (uint )((void *)(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x72)));
  }
  if (*(int *)((int)NativeHeaderWords + 0x8a) == 0) {
    DAT_0071034c = (uint )(0);
  }
  else {
    DAT_0071034c = (uint )(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x8a));
  }
  FUN_00455e90(*(undefined4 *)((int)NativeHeaderWords + 0x6e));
  if (*(int *)((int)NativeHeaderWords + 0xd2) != 0) {
    if (DAT_006daeee == 0) {
      iVar7 = (int)(CompilerTools_AllocateBlock(*(int *)((int)NativeHeaderWords + 0xd2)));
      uVar5 = (undefined4)(*(undefined4 *)((int)NativeHeaderWords + 0xd2));
      iVar8 = (int)(FUN_0044d890(DAT_006daf2a, *(undefined4 *)((int)NativeHeaderWords + 0xd6)));
      if ((iVar8 != 0) || (iVar8 = FUN_0044d810(DAT_006daf2a, iVar7, uVar5), iVar8 != 0)) {
        uVar5 = (undefined4)(DAT_006daed8);
        if (DAT_006daf2a != 0) {
          FUN_0044d730(DAT_006daf2a);
        }
        FUN_00447990(0x27c5, uVar5);
                    /* WARNING: Subroutine does not return */
        longjmp(&DAT_00704910, 1);
      }
    }
    else {
      iVar7 = (int)((int)DAT_006daeee + *(int *)((int)NativeHeaderWords + 0xd6));
    }
    FUN_004be300(iVar7, *(undefined4 *)((int)NativeHeaderWords + 0xd2));
  }
  if (*(int *)((int)NativeHeaderWords + 0x8e) == 0) {
    DAT_006daed4 = (uint )((undefined4 *)0x0);
    puVar1 = (undefined4 *)(DAT_006daed4);
  }
  else {
    DAT_006daed4 = (uint )((undefined4 *)(DAT_006daeea + *(int *)((int)NativeHeaderWords + 0x8e)));
    puVar1 = (undefined4 *)(DAT_006daed4);
  }
  for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    iVar7 = (int)(FUN_004be1f0(puVar1[1], puVar1 + 3, puVar1[2]));
    if (puVar1[1] != iVar7) {
      CError_Internal(s_CPrec_c_0067dd1c, 0x3ff);
    }
  }
  DAT_006daf2a = (uint )(0);
  if (DAT_006daf1a != 0) {
    FreeGList(&DAT_006daf1a);
  }
  DAT_00711be0 = (uint )(DAT_007101c4);
  cVar2 = (char)(CParser_ReInitRuntimeObjects(1));
  if (cVar2 != '\0') {
    FUN_004490d0(&DAT_00716ed2, &LAB_00449230);
    FUN_0044cab0();
    if (DAT_00715c08 != (undefined4 *)0x0) {
      uVar5 = (undefined4)(GetHashNameNode(s__C_C___Preprocessor_Panel__0067dd24));
      *DAT_00715c08 = uVar5;
    }
    FUN_00456ba0();
    return;
  }
  if (DAT_006daf2a != 0) {
    FUN_0044d730(DAT_006daf2a);
  }
  FUN_00447990(0x27c5, s_runtime_objects_mismatch_0067dd00);
                    /* WARNING: Subroutine does not return */
  longjmp(&DAT_00704910, 1);
}

bool PrecompilerCheck(int param_1, undefined4 param_2, int *param_3, int param_4)
{
  byte nativeFrame[4];
#define local_4 (*(int *)(nativeFrame+0))

  int iVar1;
  if (*(char *)(param_1 + 8) == '\0') {
    if ((*(byte *)(param_1 + 0x32) >> 1 & 1) != 0) {
      return false;
    }
  }
  if (param_4 > 3) {
    if (param_3 == (int *)0x0) {
      iVar1 = (int)(FUN_0044d600(param_2, 0, &local_4, 4));
      if (iVar1 != 0) {
        return false;
      }
    }
    else {
      local_4 = (int)(*param_3);
    }
    return local_4 == -0x41100532;
  }
  return false;
}
#undef local_4


void fn_0046eb90(void)
{
  byte nativeFrame[20];
#define local_24 (*(int * *)(nativeFrame+0))
#define local_1c (*(int *)(nativeFrame+8))
#define local_14 (*(int * *)(nativeFrame+16))

  int *piVar1;
  char cVar2;
  char cVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  int *piVar9;
  int *piVar10;
  int iVar11;
  char *pcVar12;
  char *pcVar13;
  char *pcVar14;
  char *pcVar15;
  iVar6 = (int)(DAT_006daeea);
  local_14 = (int *)((int *)(DAT_006daf16 + 0x20da));
  local_24 = (int *)(&DAT_0070c6a0);
  local_1c = (int)(0);
  do {
    puVar4 = (undefined4 *)((undefined4 *)*local_24);
    if (puVar4 == (undefined4 *)0x0) {
      if (*local_14 != 0) {
        *local_24 = iVar6 + *local_14;
      }
    }
    else {
      for (; puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
        uVar8 = (undefined4)(GetHashNameNode(puVar4[1] + 10));
        puVar4[1] = (uint)(uVar8);
        iVar11 = (int)(1);
        if (*(ushort *)(puVar4 + 7) > 1) {
          do {
            uVar8 = (undefined4)(GetHashNameNode(puVar4[iVar11 + 7] + 10));
            puVar4[iVar11 + 7] = (uint)(uVar8);
            iVar11 = (int)(iVar11 + 1);
          } while (iVar11 < (int)(uint)*(ushort *)(puVar4 + 7));
        }
        if (((int *)puVar4[4] != (int *)0x0) && (iVar11 = *(int *)puVar4[4], iVar11 != 0)) {
          uVar8 = (undefined4)(GetHashNameNode(iVar11 + 10));
          *(undefined4 *)puVar4[4] = uVar8;
        }
      }
      if (*local_14 != 0) {
        piVar1 = (int *)((int *)(iVar6 + *local_14));
        piVar7 = (int *)(local_24);
LAB_0046ec34:
        piVar10 = (int *)(piVar7);
        piVar5 = (int *)((int *)*piVar10);
        if (piVar5 != (int *)0x0) {
          piVar9 = (int *)(piVar1);
          do {
            if (piVar9[1] == piVar5[1]) {
              *piVar10 = (uint)(*piVar5);
              piVar7 = (int *)(piVar10);
              if (DAT_0070f08c == '\0') {
                if (((short)piVar9[7] != (short)piVar5[7]) ||
                   (iVar11 = piVar5[3], piVar9[3] != iVar11)) goto LAB_0046ed40;
                pcVar12 = (char *)((char *)piVar9[2]);
                pcVar14 = (char *)((char *)piVar5[2]);
                if (iVar11 != 0) goto LAB_0046ec91;
                iVar11 = (int)(0);
                goto LAB_0046ec9d;
              }
              break;
            }
            piVar9 = (int *)((int *)*piVar9);
            piVar7 = (int *)(piVar5);
          } while (piVar9 != (int *)0x0);
          goto LAB_0046ec34;
        }
        *piVar10 = (uint)((int)piVar1);
      }
    }
    local_14 = (int *)(local_14 + 1);
    local_24 = (int *)(local_24 + 1);
    local_1c = (int)(local_1c + 1);
    if (local_1c > 0x7ff) {
      return;
    }
  } while( true );
  while( true ) {
    iVar11 = (int)(iVar11 - 1);
    pcVar15 = (char *)(pcVar14 + 1);
    pcVar13 = (char *)(pcVar12 + 1);
    cVar3 = (char)(*pcVar14);
    cVar2 = (char)(*pcVar12);
    pcVar12 = (char *)(pcVar13);
    pcVar14 = (char *)(pcVar15);
    if (cVar2 != cVar3) break;
LAB_0046ec91:
    pcVar13 = (char *)(pcVar12);
    pcVar15 = (char *)(pcVar14);
    if (iVar11 == 0) break;
  }
  iVar11 = (int)((uint)(byte)pcVar13[-1] - (uint)(byte)pcVar15[-1]);
LAB_0046ec9d:
  if (iVar11 != 0) {
LAB_0046ed40:
    if (DAT_0070f1af == '\0') {
      CError_ReportError(0x277c, piVar9[1] + 10);
    }
    else {
      CError_Warning(0x277c, piVar9[1] + 10);
    }
  }
  goto LAB_0046ec34;
}
#undef local_24
#undef local_1c
#undef local_14


void fn_0046ed70(int *param_1)
{
  undefined4 uVar1;
  *(undefined4 *)((int)param_1 + 10) = 0;
  *(undefined4 *)((int)param_1 + 0xe) = 0;
  { uint nativeSwitch1Value=(uint)((char)param_1[2]);
if(nativeSwitch1Value==(uint)('\0')) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)('\x03')) goto nativeSwitch1Case1;
goto nativeSwitch1End;

  nativeSwitch1Case0:
    if (*(int *)((int)param_1 + 0x16) == 0x7fffffff) {
      uVar1 = (undefined4)(galloc(0x104));
      *(undefined4 *)((int)param_1 + 0x16) = uVar1;
      if (*(char *)(DAT_00710360 + 0x30a) != '\0') {
        CError_Internal(s_CPrec_c_0067dd1c, 0x1779);
      }
      FUN_0044d9f0(*(undefined4 *)((int)param_1 + 0x16), *param_1 + 10);
    }
    *(undefined4 *)((int)param_1 + 0x2e) = 0;
    if (*(int *)((int)param_1 + 0x2a) != 0) {
      *(undefined1 *)(*(int *)((int)param_1 + 0x2a) + 0x10) = 1;
    }
    *(undefined2 *)((int)param_1 + 0x1a) = 0;
    *(byte *)((int)param_1 + 0x32) = *(byte *)((int)param_1 + 0x32) & 0xfe;
    *(byte *)((int)param_1 + 0x32) = *(byte *)((int)param_1 + 0x32) & 0xfd;
    *(byte *)((int)param_1 + 0x32) = *(byte *)((int)param_1 + 0x32) & 0xfb;
    *(undefined4 *)((int)param_1 + 0x26) = 0;
    goto nativeSwitch1End;
  nativeSwitch1Case1:
    if (*(int *)((int)param_1 + 0x26) != 0) {
      uVar1 = (undefined4)(FUN_004d42d0(*(int *)((int)param_1 + 0x26)));
      *(undefined4 *)((int)param_1 + 0x26) = uVar1;
    }
    *(undefined4 *)((int)param_1 + 0x2e) = 0;
    *(undefined4 *)((int)param_1 + 0x2a) = *(undefined4 *)((int)param_1 + 0x2e);

nativeSwitch1End:;
}
  return;
}

void fn_0046ee50(void)
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  if (*(int *)(DAT_006daf16 + 0x4a) != 0) {
    fn_00478d90();
    if (DAT_006daeee == 0) {
      piVar4 = (int *)((int *)CompilerTools_AllocatePool(*(undefined4 *)(DAT_006daf16 + 0x4a)));
      uVar1 = (undefined4)(*(undefined4 *)(DAT_006daf16 + 0x4a));
      iVar3 = (int)(FUN_0044d890(DAT_006daf2a, *(undefined4 *)(DAT_006daf16 + 0x4e)));
      if ((iVar3 != 0) ||
         (iVar5 = FUN_0044d810(DAT_006daf2a, piVar4, uVar1), iVar3 = DAT_006daeea, iVar5 != 0)) {
        uVar1 = (undefined4)(DAT_006daed8);
        if (DAT_006daf2a != 0) {
          FUN_0044d730(DAT_006daf2a);
        }
        FUN_00447990(0x27c5, uVar1);
                    /* WARNING: Subroutine does not return */
        longjmp(&DAT_00704910, 1);
      }
    }
    else {
      piVar4 = (int *)((int *)(DAT_006daeee + *(int *)(DAT_006daf16 + 0x4e)));
      iVar3 = (int)(DAT_006daeea);
    }
    while( true ) {
      iVar5 = (int)(*piVar4);
      if (iVar5 == 0) break;
      uVar1 = (undefined4)(*(undefined4 *)(DAT_006daefe + piVar4[1] * 4));
      piVar4 = (int *)(piVar4 + 2);
      do {
        iVar2 = (int)(*piVar4);
        piVar4 = (int *)(piVar4 + 1);
        iVar5 = (int)(iVar5 - 1);
        *(undefined4 *)(iVar3 + iVar2) = uVar1;
      } while (iVar5 != 0);
    }
  }
  return;
}

void fn_0046ef30(void)
{
  byte nativeFrame[4];
#define local_18 (*(int *)(nativeFrame+0))

  int *piVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  iVar6 = (int)(*(int *)(DAT_006daf16 + 0x3e));
  if (iVar6 != 0) {
    if (DAT_006daeee == 0) {
      pbVar7 = (byte *)((byte *)CompilerTools_AllocatePool(*(undefined4 *)(DAT_006daf16 + 0x42)));
      uVar3 = (undefined4)(*(undefined4 *)(DAT_006daf16 + 0x42));
      iVar4 = (int)(FUN_0044d890(DAT_006daf2a, *(undefined4 *)(DAT_006daf16 + 0x46)));
      if ((iVar4 != 0) || (iVar4 = FUN_0044d810(DAT_006daf2a, pbVar7, uVar3), iVar4 != 0)) {
        uVar3 = (undefined4)(DAT_006daed8);
        if (DAT_006daf2a != 0) {
          FUN_0044d730(DAT_006daf2a);
        }
        FUN_00447990(0x27c5, uVar3);
                    /* WARNING: Subroutine does not return */
        longjmp(&DAT_00704910, 1);
      }
    }
    else {
      pbVar7 = (byte *)((byte *)(DAT_006daeee + *(int *)(DAT_006daf16 + 0x46)));
    }
    iVar4 = (int)(DAT_006daeea);
    local_18 = (int)(0);
    pbVar5 = (byte *)(pbVar7);
    do {
      bVar2 = (byte)(*pbVar5);
      if ((bVar2 & 0x80) == 0) {
        local_18 = (int)(CONCAT31(CONCAT21(CONCAT11(bVar2, pbVar5[1]), pbVar5[2]), pbVar5[3]));
        pbVar5 = (byte *)(pbVar5 + 4);
      }
      else {
        local_18 = (int)(local_18 + (char)(bVar2 * '\x02'));
        pbVar5 = (byte *)(pbVar5 + 1);
      }
      iVar6 = (int)(iVar6 - 1);
      piVar1 = (int *)((int *)(iVar4 + local_18));
      *piVar1 = (uint)(*piVar1 + iVar4);
    } while (iVar6 > 0);
    FUN_0046c550();
    uVar3 = (undefined4)(DAT_006daed8);
    if (pbVar5 != pbVar7 + *(int *)(DAT_006daf16 + 0x42)) {
      if (DAT_006daf2a != 0) {
        FUN_0044d730(DAT_006daf2a);
      }
      FUN_00447990(0x27c5, uVar3);
                    /* WARNING: Subroutine does not return */
      longjmp(&DAT_00704910, 1);
    }
  }
  return;
}
#undef local_18


void fn_0046f090(void)
{
  undefined4 uVar1;
  byte *pbVar2;
  byte *pbVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  if (DAT_006daeee == 0) {
    uVar5 = (uint)(*(uint *)(DAT_006daf16 + 0x32));
    if (uVar5 == *(uint *)(DAT_006daf16 + 0x36)) {
      uVar4 = (undefined4)(galloc(*(uint *)(DAT_006daf16 + 0x36)));
      uVar1 = (undefined4)(*(undefined4 *)(DAT_006daf16 + 0x36));
      DAT_006daeea = (uint )((byte *)uVar4);
      iVar6 = (int)(FUN_0044d890(DAT_006daf2a, *(undefined4 *)(DAT_006daf16 + 0x3a)));
      if ((iVar6 == 0) && (iVar6 = FUN_0044d810(DAT_006daf2a, uVar4, uVar1), iVar6 == 0)) {
        return;
      }
      uVar1 = (undefined4)(DAT_006daed8);
      if (DAT_006daf2a != 0) {
        FUN_0044d730(DAT_006daf2a);
      }
      FUN_00447990(0x27c5, uVar1);
                    /* WARNING: Subroutine does not return */
      longjmp(&DAT_00704910, 1);
    }
    iVar9 = (int)((uVar5 >> 7) + uVar5 + 0x40);
    pbVar2 = (byte *)((byte *)galloc(iVar9));
    iVar6 = (int)(*(int *)(DAT_006daf16 + 0x36));
    pbVar7 = (byte *)(pbVar2 + (iVar9 - iVar6));
    DAT_006daeea = (uint )(pbVar2);
    iVar9 = (int)(FUN_0044d890(DAT_006daf2a, *(undefined4 *)(DAT_006daf16 + 0x3a)));
    if ((iVar9 != 0) || (iVar6 = FUN_0044d810(DAT_006daf2a, pbVar7, iVar6), iVar6 != 0)) {
      uVar1 = (undefined4)(DAT_006daed8);
      if (DAT_006daf2a != 0) {
        FUN_0044d730(DAT_006daf2a);
      }
      FUN_00447990(0x27c5, uVar1);
                    /* WARNING: Subroutine does not return */
      longjmp(&DAT_00704910, 1);
    }
  }
  else {
    pbVar2 = (byte *)((byte *)galloc(*(undefined4 *)(DAT_006daf16 + 0x32)));
    pbVar7 = (byte *)((byte *)(DAT_006daeee + *(int *)(DAT_006daf16 + 0x3a)));
    DAT_006daeea = (uint )(pbVar2);
    if (*(int *)(DAT_006daf16 + 0x32) == *(int *)(DAT_006daf16 + 0x36)) {
      FUN_004047c0(pbVar2, pbVar7, *(int *)(DAT_006daf16 + 0x32));
      return;
    }
  }
  pbVar8 = (byte *)(pbVar7 + *(int *)(DAT_006daf16 + 0x36));
  pbVar3 = (byte *)(pbVar2 + *(int *)(DAT_006daf16 + 0x32));
  uVar1 = (undefined4)(DAT_006daed8);
  while (DAT_006daed8 = uVar1, pbVar7 < pbVar8) {
    uVar5 = (uint)((uint)*pbVar7);
    pbVar7 = (byte *)(pbVar7 + 1);
    if (uVar5 < 0xe0) {
      do {
        uVar5 = (uint)(uVar5 - 1);
        *pbVar2 = *pbVar7;
        pbVar7 = (byte *)(pbVar7 + 1);
        pbVar2 = (byte *)(pbVar2 + 1);
        uVar1 = (undefined4)(DAT_006daed8);
      } while ((int)uVar5 > -1);
    }
    else {
      iVar6 = (int)(uVar5 - 0xe0);
      do {
        iVar6 = (int)(iVar6 - 1);
        *pbVar2 = 0;
        pbVar2 = (byte *)(pbVar2 + 1);
        uVar1 = (undefined4)(DAT_006daed8);
      } while (iVar6 > -1);
    }
  }
  if ((pbVar7 == pbVar8) && (pbVar2 == pbVar3)) {
    return;
  }
  if (DAT_006daf2a != 0) {
    FUN_0044d730(DAT_006daf2a);
  }
  FUN_00447990(0x27c5, uVar1);
                    /* WARNING: Subroutine does not return */
  longjmp(&DAT_00704910, 1);
}

int fn_0046f2d0(void)
{
  byte nativeFrame[668];
#define local_2a4 (*(undefined4 *)(nativeFrame+0))
#define local_2a0 ((undefined1 *)(nativeFrame+4))
#define local_220 ((undefined1 *)(nativeFrame+132))
#define local_11c (*(undefined4 *)(nativeFrame+392))
#define local_118 (*(undefined4 *)(nativeFrame+396))
#define local_114 (*(undefined8 *)(nativeFrame+400))
#define local_10c ((undefined4 *)(nativeFrame+408))

  undefined4 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  iVar3 = (int)(0);
  if (*(char *)((int)NativeContextWords + 0x30a) == '\0') {
    iVar4 = (int)(0);
    do {
      *(undefined4 *)((int)local_10c + iVar4) = *(undefined4 *)(iVar4 + 0x14c + (int)NativeContextWords);
      *(undefined4 *)((int)local_10c + iVar4 + 4) =
           *(undefined4 *)(iVar4 + 0x150 + (int)NativeContextWords);
      *(undefined4 *)((int)local_10c + iVar4 + 8) =
           *(undefined4 *)(iVar4 + 0x154 + (int)NativeContextWords);
      *(undefined4 *)((int)local_10c + iVar4 + 0xc) =
           *(undefined4 *)(iVar4 + 0x158 + (int)NativeContextWords);
      iVar4 = (int)(iVar4 + 0x10);
    } while (iVar4 < 0x100);
    local_10c[0x40] = NativeContextWords[0x93];
    iVar4 = (int)(FUN_00458b80((uint)(*NativeContextWords), (uint)(local_10c), (uint)(DAT_00715c04)));
    if (iVar4 != 0) {
      return iVar4;
    }
  }
  else {
    iVar3 = (int)(FUN_0044dd40(local_220));
    if (iVar3 == 0) {
      iVar3 = (int)(FUN_0044d3f0(local_10c, local_220, s___tmpfile_mch_0067dd40));
    }
  }
  uVar2 = (undefined2)(3);
  iVar4 = (int)(iVar3);
  if (iVar3 == 0) {
    iVar4 = (int)(FUN_0044d7f0(local_10c, &DAT_006daf2a, DAT_0070f290, DAT_0070f294));
    uVar2 = (undefined2)(3);
    if (iVar4 == 0) {
      uVar2 = (undefined2)(4);
      iVar4 = (int)(fn_0046f600());
    }
    iVar3 = (int)(iVar4);
    if (DAT_006daf2a != 0) {
      iVar3 = (int)(FUN_0044d730(DAT_006daf2a));
      DAT_006daf2a = (uint )(0);
    }
    if (DAT_006daf1a != 0) {
      iVar3 = (int)(FreeGList(&DAT_006daf1a));
    }
  }
  if (iVar4 != 0) goto LAB_0046f492;
  if (*(char *)((int)NativeContextWords + 0x30a) == '\0') {
    iVar3 = (int)(FUN_0044dda0(local_10c, &local_114));
    if (iVar3 != 0) {
      local_114 = (undefined8)(FUN_0044dfd0());
    }
    iVar3 = (int)(FUN_00420330((uint)(*NativeContextWords), (uint)(local_10c), (uint)(&local_114), (uint)(1)));
  }
  else {
    iVar3 = (int)(FUN_0044d7d0(local_10c, &DAT_006daf2a));
    iVar4 = (int)(iVar3);
    if (iVar3 != 0) goto LAB_0046f492;
    iVar3 = (int)(FUN_0044d740(DAT_006daf2a, &local_11c));
    iVar4 = (int)(iVar3);
    if (iVar3 != 0) goto LAB_0046f492;
    iVar3 = (int)(FUN_00420590((uint)(*NativeContextWords), (uint)(local_11c), (uint)(0), (uint)(&local_118)));
    iVar4 = (int)(8);
    if (iVar3 != 0) goto LAB_0046f492;
    iVar3 = (int)(FUN_004206c0((uint)(*NativeContextWords), (uint)(local_118), (uint)(0), (uint)(&local_2a4)));
    iVar4 = (int)(8);
    if (iVar3 != 0) goto LAB_0046f492;
    iVar3 = (int)(FUN_0044d810(DAT_006daf2a, local_2a4, local_11c));
    iVar4 = (int)(iVar3);
    if (iVar3 != 0) goto LAB_0046f492;
    FUN_00420720((uint)(*NativeContextWords), (uint)(local_118));
    FUN_0044d730(DAT_006daf2a);
    FUN_0044d8e0(local_10c);
    iVar3 = (int)(FUN_00458cc0((uint)(*NativeContextWords), (uint)(DAT_00715c04), (uint)(DAT_0070f294), (uint)(local_118)));
    if (iVar3 != 0) {
      iVar4 = (int)(2);
      goto LAB_0046f492;
    }
  }
  iVar4 = (int)(0);
LAB_0046f492:
  if (iVar4 != 0) {
    FUN_0046db20(uVar2, local_2a0);
    sprintf(&DAT_0070f848, local_2a0, iVar4);
    uVar6 = (undefined4)(0);
    uVar5 = (undefined4)(2);
    uVar1 = (undefined4)(FUN_0044de10(iVar4, 2, 0));
    iVar3 = (int)(FUN_00420060((uint)(*NativeContextWords), (uint)(0), (uint)(&DAT_0070f848), (uint)(uVar1), (uint)(uVar5), (uint)(uVar6)));
  }
  return iVar3;
}
#undef local_2a4
#undef local_2a0
#undef local_220
#undef local_11c
#undef local_118
#undef local_114
#undef local_10c


int fn_0046f600(void)
{
  byte nativeFrame[152];
#define local_a4 (*(undefined4 *)(nativeFrame+0))
#define auStack_a0 ((undefined1 *)(nativeFrame+4))
#define local_98 (*(undefined4 *)(nativeFrame+12))
#define local_94 ((undefined1 *)(nativeFrame+16))
#define uStack_14 (*(uint *)(nativeFrame+144))
#define local_10 (*(int *)(nativeFrame+148))

  char cVar1;
  short sVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  DAT_006daed4 = (uint )(0);
  iVar5 = (int)(0);
  puVar6 = (undefined4 *)(&DAT_006daed4);
  while (cVar1 = FUN_004be110(iVar5, &local_98, &local_a4, &local_10), cVar1 != '\0') {
    puVar3 = (undefined4 *)((undefined4 *)galloc(local_10 + 0xc));
    *puVar6 = (uint)(puVar3);
    *puVar3 = (uint)(0);
    puVar3[1] = (uint)(local_98);
    puVar3[2] = (uint)(local_10);
    memcpy(puVar3 + 3, local_a4, local_10);
    iVar5 = (int)(iVar5 + 1);
    puVar6 = (undefined4 *)(puVar3);
  }
  sVar2 = (short)(InitGList(&DAT_006daf1a, 0x40000));
  if (sVar2 != 0) {
    CError_LongJump();
  }
  FUN_0046db20(10, local_94);
  fn_0041b8d0((uint)(DAT_00716ed2), (uint)(local_94), (uint)(&DAT_0067dd50));
  FUN_004490c0();
  for (iVar5 = DAT_0071008c; iVar5 != 0; iVar5 = *(int *)(iVar5 + 4)) {
    if (*(char *)(iVar5 + 8) == '\0') {
      if (*(int *)(iVar5 + 0x16) != 0) {
        uVar4 = (undefined4)(FUN_0044d580(*(int *)(iVar5 + 0x16)));
        GetHashNameNode(uVar4);
      }
      if (*(int *)(iVar5 + 0x2a) != 0) {
        uVar4 = (undefined4)(GetHashNameNode(*(int *)(*(int *)(iVar5 + 0x2a) + 4) + 10));
        *(undefined4 *)(*(int *)(iVar5 + 0x2a) + 4) = uVar4;
      }
    }
  }
  iVar5 = (int)(0);
  do {
    for (puVar6 = *(undefined4 **)(DAT_00710144 + iVar5 * 4); puVar6 != (undefined4 *)0x0;
        puVar6 = (undefined4 *)*puVar6) {
      puVar6[1] = (uint)(0);
    }
    iVar5 = (int)(iVar5 + 1);
  } while (iVar5 < 0x800);
  iVar5 = (int)(fn_00470020((char)(0)));
  if (iVar5 != 0) {
    return iVar5;
  }
  FUN_0046db20(0xb, local_94);
  fn_0041b8d0((uint)(DAT_00716ed2), (uint)(local_94), (uint)(&DAT_0067dd50));
  NativeHeaderWords = (uint *)((undefined4 *)galloc(0x50da));
  memclrw(NativeHeaderWords, 0x50da);
  *NativeHeaderWords = 0xbeefface;
  *(undefined2 *)(NativeHeaderWords + 1) = 0x42d;
  *(undefined2 *)(NativeHeaderWords + 2) = 0xd629;
  *(undefined1 *)((int)NativeHeaderWords + 10) = 2;
  *(undefined1 *)((int)NativeHeaderWords + 0xb) = DAT_0070f1fa;
  *(undefined1 *)(NativeHeaderWords + 3) = DAT_0070f1a8;
  uVar4 = (undefined4)(FUN_00455f20());
  *(undefined4 *)((int)NativeHeaderWords + 0x6e) = uVar4;
  *(undefined1 *)((int)NativeHeaderWords + 0x11) = (undefined1)DAT_00699c3e;
  *(undefined1 *)((int)NativeHeaderWords + 0x12) = (undefined1)DAT_00699c1e;
  *(undefined1 *)((int)NativeHeaderWords + 0x13) = DAT_00725e5e;
  iVar5 = (int)(FUN_0044d850(DAT_006daf2a, NativeHeaderWords, 0x50da));
  if (iVar5 != 0) {
    return iVar5;
  }
  uStack_14 = (uint)(0x50da);
  *(undefined4 *)((int)NativeHeaderWords + 0x2e) = 0x50da;
  iVar5 = (int)(fn_0046fd40());
  if (iVar5 != 0) {
    return iVar5;
  }
  iVar5 = (int)(FUN_0044d8b0(DAT_006daf2a, &uStack_14));
  if (iVar5 != 0) {
    return iVar5;
  }
  *(uint *)((int)NativeHeaderWords + 0x2a) = uStack_14 - *(int *)((int)NativeHeaderWords + 0x2e);
  iVar5 = (int)(fn_00470020((char)(1)));
  if (iVar5 != 0) {
    return iVar5;
  }
  *(int *)((int)NativeHeaderWords + 0x32) = DAT_006daef6;
  *(uint *)((int)NativeHeaderWords + 0x3a) = uStack_14;
  iVar5 = (int)(FUN_0044d8b0(DAT_006daf2a, &uStack_14));
  if (iVar5 != 0) {
    return iVar5;
  }
  *(uint *)((int)NativeHeaderWords + 0x36) = uStack_14 - *(int *)((int)NativeHeaderWords + 0x3a);
  if (*(int *)((int)NativeHeaderWords + 0x36) == *(int *)((int)NativeHeaderWords + 0x32)) {
    CError_Internal(s_CPrec_c_0067dd1c, 0x15c7);
  }
  uVar4 = (undefined4)(fn_00470f50());
  *(undefined4 *)((int)NativeHeaderWords + 0x3e) = uVar4;
  *(int *)((int)NativeHeaderWords + 0x42) = DAT_006daf1e;
  *(uint *)((int)NativeHeaderWords + 0x46) = uStack_14;
  if (*(int *)((int)NativeHeaderWords + 0x3e) != 0) {
    iVar5 = (int)(FUN_0044d850(DAT_006daf2a, *DAT_006daf1a, DAT_006daf1e));
    if (iVar5 != 0) {
      return iVar5;
    }
    uStack_14 = (uint)(uStack_14 + DAT_006daf1e);
  }
  uVar4 = (undefined4)(DAT_006daf2a);
  uVar8 = (uint)(uStack_14 & 7);
  if (uVar8 == 0) {
    iVar5 = (int)(0);
  }
  else {
    memclrw(auStack_a0, 8);
    iVar7 = (int)(8 - uVar8);
    iVar5 = (int)(FUN_0044d850(uVar4, auStack_a0, iVar7));
    uStack_14 = (uint)(uStack_14 + iVar7);
  }
  if (iVar5 == 0) {
    DAT_006daf1e = (int )(0);
    fn_00471180();
    *(int *)((int)NativeHeaderWords + 0x4a) = DAT_006daf1e;
    *(uint *)((int)NativeHeaderWords + 0x4e) = uStack_14;
    iVar5 = (int)(FUN_0044d850(DAT_006daf2a, *DAT_006daf1a, DAT_006daf1e));
    if (iVar5 != 0) {
      return iVar5;
    }
    uStack_14 = (uint)(uStack_14 + DAT_006daf1e);
    if (DAT_006daf06 != 0) {
      DAT_006daf1e = (int )(0);
      for (puVar6 = (uint *)DAT_006daf06; puVar6 != (undefined4 *)0x0; puVar6 = (undefined4 *)*puVar6) {
        if (DAT_006daee5 != '\0') {
          AppendGListLong(&DAT_006daf1a, puVar6[1]);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + 4);
        if (DAT_006daee5 != '\0') {
          AppendGListLong(&DAT_006daf1a, puVar6[2]);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + 4);
      }
      if (DAT_006daee5 != '\0') {
        AppendGListLong(&DAT_006daf1a, 0);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 4);
      *(int *)((int)NativeHeaderWords + 0x52) = DAT_006daf1e;
      *(uint *)((int)NativeHeaderWords + 0x56) = uStack_14;
      iVar5 = (int)(FUN_0044d850(DAT_006daf2a, *DAT_006daf1a, DAT_006daf1e));
      if (iVar5 != 0) {
        return iVar5;
      }
      uStack_14 = (uint)(uStack_14 + DAT_006daf1e);
    }
    if (DAT_006daf02 != 0) {
      DAT_006daf1e = (int )(0);
      for (puVar6 = (uint *)DAT_006daf02; puVar6 != (undefined4 *)0x0; puVar6 = (undefined4 *)*puVar6) {
        if (DAT_006daee5 != '\0') {
          AppendGListLong(&DAT_006daf1a, puVar6[1]);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + 4);
      }
      if (DAT_006daee5 != '\0') {
        AppendGListLong(&DAT_006daf1a, 0);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 4);
      iVar5 = (int)(FUN_0044d850(DAT_006daf2a, *DAT_006daf1a, DAT_006daf1e));
      if (iVar5 != 0) {
        return iVar5;
      }
      *(uint *)((int)NativeHeaderWords + 0xce) = uStack_14;
      uStack_14 = (uint)(uStack_14 + DAT_006daf1e);
    }
    DAT_006daf1e = (int )(0);
    FUN_004c0120(&DAT_006daf1a);
    *(uint *)((int)NativeHeaderWords + 0xd6) = uStack_14;
    *(int *)((int)NativeHeaderWords + 0xd2) = DAT_006daf1e;
    iVar5 = (int)(FUN_0044d850(DAT_006daf2a, *DAT_006daf1a, DAT_006daf1e));
    if (iVar5 != 0) {
      return iVar5;
    }
    uStack_14 = (uint)(uStack_14 + DAT_006daf1e);
    iVar5 = (int)(FUN_0044d890(DAT_006daf2a, 0));
    if (iVar5 == 0) {
      iVar5 = (int)(FUN_0044d850(DAT_006daf2a, NativeHeaderWords, 0x50da));
      if (iVar5 == 0) {
        return 0;
      }
      return iVar5;
    }
    return iVar5;
  }
  return iVar5;
}
#undef local_a4
#undef auStack_a0
#undef local_98
#undef local_94
#undef uStack_14
#undef local_10


int fn_0046fd40(void)
{
  byte nativeFrame[1036];
#define local_420 (*(undefined4 *)(nativeFrame+0))
#define acStack_41c ((char *)(nativeFrame+4))
#define puStack_1c (*(undefined4 * *)(nativeFrame+1028))
#define iStack_18 (*(int *)(nativeFrame+1032))

  undefined4 *puVar1;
  char cVar2;
  short sVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  char *pcVar9;
  uint uVar10;
  local_420 = (undefined4)(0);
  piVar4 = (int *)((int *)FUN_0044c0e0());
  if (piVar4 == (int *)0x0) {
    CError_Internal(s_CPrec_c_0067dd1c, 0x152a);
  }
  iVar7 = (int)(-1);
  pcVar9 = (char *)((char *)(*piVar4 + 10));
  do {
    if (iVar7 == 0) break;
    iVar7 = (int)(iVar7 - 1);
    cVar2 = (char)(*pcVar9);
    pcVar9 = (char *)(pcVar9 + 1);
  } while (cVar2 != '\0');
  iVar7 = (int)(FUN_0044d850(DAT_006daf2a, *piVar4 + 10, -iVar7 + -1));
  if (iVar7 != 0) {
    return iVar7;
  }
  iVar7 = (int)(-1);
  pcVar9 = (char *)((char *)(*piVar4 + 10));
  do {
    if (iVar7 == 0) break;
    iVar7 = (int)(iVar7 - 1);
    cVar2 = (char)(*pcVar9);
    pcVar9 = (char *)(pcVar9 + 1);
  } while (cVar2 != '\0');
  iVar7 = (int)(-iVar7 + -1);
  uVar5 = (undefined4)(GetHashNameNode(s__command_line_defines__0067dd54));
  iVar6 = (int)(FUN_0044c4d0(uVar5, 0, 0, 0, 0));
  if ((iVar6 != 0) && (cVar2 = FUN_0044ba70(iVar6), cVar2 != '\0')) {
    sVar3 = (short)(InitGList(&puStack_1c, 0));
    if (sVar3 != 0) {
      return 7;
    }
    FUN_0047ecc0(&puStack_1c, *(undefined4 *)(iVar6 + 10), 0, 0, *(undefined4 *)(iVar6 + 0xe));
    iVar6 = (int)(FUN_0044d850(DAT_006daf2a, *puStack_1c, iStack_18));
    iVar7 = (int)(iVar7 + iStack_18);
    FreeGList(&puStack_1c);
    if (iVar6 != 0) {
      return iVar6;
    }
  }
  iVar6 = (int)(FUN_0044d850(DAT_006daf2a, &local_420, 1));
  if (iVar6 != 0) {
    return iVar6;
  }
  iVar7 = (int)(iVar7 + 1);
  puVar1 = (undefined4 *)(DAT_006daee0);
  do {
    if (puVar1 == (undefined4 *)0x0) {
      iVar6 = (int)(FUN_0044d850(DAT_006daf2a, &local_420, 1));
      if (iVar6 != 0) {
        return iVar6;
      }
      uVar10 = (uint)(iVar7 + 1U & 3);
      if (uVar10 == 0) {
        iVar7 = (int)(0);
      }
      else {
        iVar7 = (int)(4 - uVar10);
      }
      if ((iVar7 != 0) && (iVar7 = FUN_0044d850(DAT_006daf2a, &local_420, iVar7), iVar7 != 0)) {
        return iVar7;
      }
      return 0;
    }
    if (*(char *)(puVar1 + 1) == '\0') {
      uVar5 = (undefined4)(0x22);
      uVar8 = (undefined4)(0x22);
    }
    else {
      uVar5 = (undefined4)(0x3e);
      uVar8 = (undefined4)(0x3c);
    }
    snprintf(acStack_41c, 0x400, s__include__c_s_c_0067dd6c, uVar8, *(int *)*puVar1 + 10, uVar5);
    iVar6 = (int)(-1);
    pcVar9 = (char *)(acStack_41c);
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar2 = (char)(*pcVar9);
      pcVar9 = (char *)(pcVar9 + 1);
    } while (cVar2 != '\0');
    iVar6 = (int)(FUN_0044d850(DAT_006daf2a, acStack_41c, -iVar6 - 2));
    if (iVar6 != 0) {
      return iVar6;
    }
    iVar6 = (int)(-1);
    pcVar9 = (char *)(acStack_41c);
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar2 = (char)(*pcVar9);
      pcVar9 = (char *)(pcVar9 + 1);
    } while (cVar2 != '\0');
    puVar1 = (undefined4 *)(*(undefined4 **)((int)puVar1 + 6));
    iVar7 = (int)(iVar7 + (-iVar6 - 2U));
  } while( true );
}
#undef local_420
#undef acStack_41c
#undef puStack_1c
#undef iStack_18


void CPrec_FileIncludedCallback(uint file, byte flag)
{
 NativeIncludedFile *node=(NativeIncludedFile *)galloc(10);
 node->next=0;
 node->file=file;
 node->flag=flag;
 if (NativeIncludedTail) NativeIncludedTail = NativeIncludedTail->next = node; else NativeIncludedHead = NativeIncludedTail = node;
}


int fn_00470020(char param_1)
{
  byte nativeFrame[12];
#define local_20 (*(uint *)(nativeFrame+0))
#define local_18 (*(uint *)(nativeFrame+8))

  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint uVar9;
  FUN_0046c550();
  DAT_006daf12 = (uint )(CompilerTools_AllocatePool(0x10000));
  memclrw(DAT_006daf12, 0x10000);
  FUN_005442b0(&DAT_006daf2e, 0);
  DAT_006daf0e = (uint )(0);
  DAT_006daf06 = (uint )(0);
  DAT_006daf02 = (uint )(0);
  DAT_006daef6 = (uint )(0);
  _DAT_006daef2 = (uint )(0);
  DAT_006daee5 = (byte )(param_1);
  DAT_006daee6 = (uint )(0);
  fn_00478d90();
  DAT_006daf0a = (uint )(CompilerTools_AllocatePool(DAT_006daefa * 0xc));
  memclrw(DAT_006daf0a, DAT_006daefa * 0xc);
  local_18 = (uint)(0);
  if (DAT_006daefa > 0) {
    iVar2 = (int)(0);
    do {
      *(undefined4 *)(DAT_006daf0a + iVar2) = *(undefined4 *)(DAT_006daefe + local_18 * 4);
      *(uint *)(DAT_006daf0a + 4 + iVar2) = ~local_18;
      uVar4 = (undefined4)(*(undefined4 *)(DAT_006daf0a + 4 + iVar2));
      uVar8 = (uint)(*(uint *)(DAT_006daf0a + iVar2));
      puVar7 = (undefined4 *)((undefined4 *)
               (((uVar8 & 0xff) + uVar8 + (uVar8 >> 8 & 0xff) + (uVar8 >> 0x10 & 0xff) +
                 (uVar8 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
      puVar5 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
      puVar5[1] = (uint)(uVar8);
      puVar5[2] = (uint)(uVar4);
      *puVar5 = (uint)(*puVar7);
      *puVar7 = (uint)(puVar5);
      iVar2 = (int)(iVar2 + 0xc);
      local_18 = (uint)(local_18 + 1);
    } while ((int)local_18 < DAT_006daefa);
  }
  if (DAT_006daee5 != '\0') {
    AppendGListLong(&DAT_006daf1a, 0);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 4);
  fn_004787f0();
  if (DAT_006daee5 == '\0') {
    iVar2 = (int)(0);
  }
  else {
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
    FUN_0044cfe0(DAT_006daf1a);
    iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
    FUN_0044d0a0(DAT_006daf1a);
    DAT_006daf1e = (int )(0);
  }
  if (iVar2 != 0) {
    return iVar2;
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  iVar2 = (int)(DAT_0071008c);
  if (DAT_006daee5 != '\0') {
    uVar8 = (uint)(DAT_006daef6);
    if (DAT_0071008c == 0) {
      uVar8 = (uint)(0);
    }
    *(uint *)(DAT_006daf16 + 0xce) = uVar8;
    iVar2 = (int)(DAT_0071008c);
  }
  for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
    iVar3 = (int)(fn_004781b0((int *)(iVar2)));
    if (*(int *)(iVar2 + 4) != 0) {
      uVar4 = (undefined4)(fn_004781b0((int *)(*(undefined4 *)(iVar2 + 4))));
      fn_00478cc0((int)(iVar3 + 4), (uint)(uVar4));
    }
  }
  if (DAT_006daee5 == '\0') {
    iVar2 = (int)(0);
  }
  else {
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
    FUN_0044cfe0(DAT_006daf1a);
    iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
    FUN_0044d0a0(DAT_006daf1a);
    DAT_006daf1e = (int )(0);
  }
  if (iVar2 != 0) {
    return iVar2;
  }
  fn_00478580();
  if (DAT_006daee5 == '\0') {
    iVar2 = (int)(0);
  }
  else {
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
    FUN_0044cfe0(DAT_006daf1a);
    iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
    FUN_0044d0a0(DAT_006daf1a);
    DAT_006daf1e = (int )(0);
  }
  if (iVar2 != 0) {
    return iVar2;
  }
  fn_00471580();
  if (param_1 != '\0') {
    if (DAT_006daee6 != 0) {
      return DAT_006daee6;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (DAT_00710b38 != 0) {
    uVar4 = (undefined4)(fn_004755d0((uint)(DAT_00710b38)));
    if (param_1 != '\0') {
      *(undefined4 *)(DAT_006daf16 + 0x62) = uVar4;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (DAT_00711af8 != 0) {
    uVar4 = (undefined4)(fn_00475ca0((int *)(DAT_00711af8)));
    if (param_1 != '\0') {
      *(undefined4 *)(DAT_006daf16 + 0x7a) = uVar4;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (DAT_00710148 != 0) {
    uVar4 = (undefined4)(fn_00471ff0((int *)(DAT_00710148)));
    if (param_1 != '\0') {
      *(undefined4 *)(DAT_006daf16 + 0x6a) = uVar4;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (DAT_007107a8 != 0) {
    uVar4 = (undefined4)(fn_00471260((int *)(DAT_007107a8)));
    if (param_1 != '\0') {
      *(undefined4 *)(DAT_006daf16 + 0x76) = uVar4;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (DAT_00716c24 != 0) {
    uVar4 = (undefined4)(fn_00471ff0((int *)(DAT_00716c24)));
    if (param_1 != '\0') {
      *(undefined4 *)(DAT_006daf16 + 0x7e) = uVar4;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (DAT_00715c2c != 0) {
    uVar4 = (undefined4)(fn_00471ff0((int *)(DAT_00715c2c)));
    if (param_1 != '\0') {
      *(undefined4 *)(DAT_006daf16 + 0x86) = uVar4;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (DAT_00716d18 != 0) {
    uVar4 = (undefined4)(fn_00476fb0((int *)(DAT_00716d18)));
    if (param_1 != '\0') {
      *(undefined4 *)(DAT_006daf16 + 0x82) = uVar4;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  piVar6 = (int *)(g_pPendingVTableClasses);
  if (g_pPendingVTableClasses != 0) {
    uVar9 = (uint)(DAT_006daef6);
    uVar8 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      while (DAT_006daef6 = uVar9, uVar8 = uVar9, (uVar9 & 3) != 0) {
        AppendGListByte(&DAT_006daf1a, 0);
        DAT_006daef6 = (uint )(DAT_006daef6 + 1);
        uVar9 = (uint)(DAT_006daef6);
      }
    }
    while( true ) {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, piVar6, 10);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 10);
      uVar4 = (undefined4)(fn_00475390((char *)(piVar6[1])));
      fn_00478cc0((int)(uVar9 + 4), (uint)(uVar4));
      if (*piVar6 == 0) break;
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar1 = (uint)(DAT_006daef6);
      fn_00478cc0((int)(uVar9), (uint)(DAT_006daef6));
      piVar6 = (int *)((int *)*piVar6);
      uVar9 = (uint)(uVar1);
    }
    if (param_1 != '\0') {
      *(uint *)(DAT_006daf16 + 0x72) = uVar8;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  if (DAT_0071034c != 0) {
    uVar4 = (undefined4)(fn_00471ff0((int *)(DAT_0071034c)));
    if (param_1 != '\0') {
      *(undefined4 *)(DAT_006daf16 + 0x8a) = uVar4;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  piVar6 = (int *)(DAT_006daed4);
  if (DAT_006daed4 != 0) {
    if (DAT_006daed4 == 0) {
      local_20 = (uint)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar8 = (uint)(DAT_006daef6);
      local_20 = (uint)(DAT_006daef6);
      puVar7 = (undefined4 *)((undefined4 *)
               (((int)piVar6 +
                 ((uint)piVar6 >> 0x18) +
                 ((uint)piVar6 >> 0x10 & 0xff) + ((uint)piVar6 >> 8 & 0xff) + ((uint)piVar6 & 0xff)
                & 0x3fff) * 4 + DAT_006daf12));
      puVar5 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
      puVar5[1] = (uint)(piVar6);
      puVar5[2] = (uint)(uVar8);
      *puVar5 = (uint)(*puVar7);
      *puVar7 = (uint)(puVar5);
      while( true ) {
        iVar2 = (int)(piVar6[2]);
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, piVar6, iVar2 + 0xc);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + iVar2 + 0xc);
        if (*piVar6 == 0) break;
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar9 = (uint)(DAT_006daef6);
        fn_00478cc0((int)(uVar8), (uint)(DAT_006daef6));
        piVar6 = (int *)((int *)*piVar6);
        uVar8 = (uint)(uVar9);
      }
    }
    if (param_1 != '\0') {
      *(uint *)(DAT_006daf16 + 0x8e) = local_20;
    }
    if (DAT_006daee5 == '\0') {
      iVar2 = (int)(0);
    }
    else {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
      FUN_0044cfe0(DAT_006daf1a);
      iVar2 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
      FUN_0044d0a0(DAT_006daf1a);
      DAT_006daf1e = (int )(0);
    }
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  return 0;
}
#undef local_20
#undef local_18


int fn_00470f50(void)
{
  byte nativeFrame[4];
#define local_10 (*(char *)(nativeFrame+0))
#define cStack_f (*(char *)(nativeFrame+1))
#define cStack_e (*(char *)(nativeFrame+2))
#define cStack_d (*(char *)(nativeFrame+3))

  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  iVar3 = (int)(0);
  DAT_006daf1e = (int )(0);
  iVar4 = (int)(0);
  for (puVar2 = (uint *)DAT_006daf0e; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
    if ((puVar2[1] & 0x80000001) != 0) {
      CError_Internal(s_CPrec_c_0067dd1c, 0x141e);
    }
    iVar1 = (int)(puVar2[1]);
    iVar3 = (int)(iVar1 - iVar3);
    if ((iVar3 < -0x80) || (iVar3 > 0x7e)) {
      cStack_d = (char)((char)((uint)iVar1 >> 0x18));
      if (DAT_006daee5 != '\0') {
        AppendGListByte(&DAT_006daf1a, (int)cStack_d);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      cStack_e = (char)((char)((uint)iVar1 >> 0x10));
      if (DAT_006daee5 != '\0') {
        AppendGListByte(&DAT_006daf1a, (int)cStack_e);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      cStack_f = (char)((char)((uint)iVar1 >> 8));
      if (DAT_006daee5 != '\0') {
        AppendGListByte(&DAT_006daf1a, (int)cStack_f);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      if (DAT_006daee5 != '\0') {
        local_10 = (char)((char)iVar1);
        AppendGListByte(&DAT_006daf1a, (int)local_10);
      }
    }
    else if (DAT_006daee5 != '\0') {
      AppendGListByte(&DAT_006daf1a, (int)(char)((byte)(iVar3 >> 1) | 0x80));
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 1);
    iVar3 = (int)(puVar2[1]);
    iVar4 = (int)(iVar4 + 1);
  }
  return iVar4;
}
#undef local_10
#undef cStack_f
#undef cStack_e
#undef cStack_d


int fn_00471090(char *param_1, int param_2)
{
  byte nativeFrame[2304];
#define local_90c ((char *)(nativeFrame+0))

  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  pcVar4 = (char *)(param_1 + param_2);
  iVar1 = (int)(0);
  while( true ) {
    do {
      if (param_1 < pcVar4) {
        if (*param_1 == '\0') {
          for (iVar3 = 0xe0; *param_1 == '\0' && (param_1 < pcVar4) && (iVar3 < 0x100);
              iVar3 = iVar3 + 1) {
            param_1 = (char *)(param_1 + 1);
          }
          local_90c[iVar1] = (char)iVar3 - 1;
          iVar1 = (int)(iVar1 + 1);
        }
        else {
          iVar2 = (int)(0);
          iVar3 = (int)(iVar1);
          for (; param_1 < pcVar4 && (iVar2 < 0xe0) && (*param_1 != '\0' || (param_1[1] != '\0'));
              param_1 = param_1 + 1) {
            local_90c[iVar3 + 1] = *param_1;
            iVar2 = (int)(iVar2 + 1);
            iVar3 = (int)(iVar3 + 1);
          }
          local_90c[iVar1] = (char)iVar2 - 1;
          iVar1 = (int)(iVar3 + 1);
        }
      }
    } while ((param_1 < pcVar4) && (iVar1 < 0x801));
    iVar1 = (int)(FUN_0044d850(DAT_006daf2a, local_90c, iVar1));
    if (iVar1 != 0) break;
    if (pcVar4 <= param_1) {
      return 0;
    }
    iVar1 = (int)(0);
  }
  return iVar1;
}
#undef local_90c


void fn_00471180(void)
{
    NativeBucketEntry *entry;
    unsigned int value;
    int entryCount;
    int bucketIndex;

    bucketIndex = (int)(0);
    if (0 < DAT_006daefa) {
        do {
            entryCount = (int)(0);
            entry = NativeBuckets[bucketIndex].list;
            while (entry != 0) {
                entry = entry->next;
                entryCount = (int)(entryCount + 1);
            }
            if (entryCount != 0) {
                if (DAT_006daee5 != '\0') {
                    AppendGListLong(&DAT_006daf1a, entryCount);
                }
                DAT_006daef6 += 4;
                if (DAT_006daee5 != '\0') {
                    AppendGListLong(&DAT_006daf1a, bucketIndex);
                }
                DAT_006daef6 += 4;
                for (entry = NativeBuckets[bucketIndex].list; entry != 0; entry = entry->next) {
                    value = (int)(entry->offset);
                    if (DAT_006daee5 != '\0') {
                        AppendGListLong(&DAT_006daf1a, value);
                    }
                    DAT_006daef6 += 4;
                }
            }
            bucketIndex = (int)(bucketIndex + 1);
        } while (bucketIndex < DAT_006daefa);
    }
    if (DAT_006daee5 != '\0') {
        AppendGListLong(&DAT_006daf1a, 0);
    }
    DAT_006daef6 += 4;
}


uint fn_00471260(int *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uVar4 = (uint)(DAT_006daef6);
  uVar1 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar4, uVar1 = uVar4, (uVar4 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar4 = (uint)(DAT_006daef6);
    }
  }
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x18);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x18);
    uVar3 = (undefined4)(fn_004721e0((uint)(param_1[2])));
    fn_00478cc0((int)(uVar4 + 8), (uint)(uVar3));
    uVar3 = (undefined4)(fn_00473510((char *)(param_1[1])));
    fn_00478cc0((int)(uVar4 + 4), (uint)(uVar3));
    if (param_1[3] != 0) {
      uVar3 = (undefined4)(fn_004781b0((int *)(param_1[3])));
      fn_00478cc0((int)(uVar4 + 0xc), (uint)(uVar3));
    }
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar4), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar4 = (uint)(uVar2);
  }
  return uVar1;
}

uint fn_00471380(int *param_1)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  int *piVar8;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar4 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x1a);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x1a);
  if (*param_1 != 0) {
    uVar6 = (undefined4)(fn_004781b0((int *)(*param_1)));
    fn_00478cc0((int)(uVar4), (uint)(uVar6));
  }
  iVar1 = (int)(param_1[3]);
  if (iVar1 != 0) {
    iVar2 = (int)(param_1[5]);
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar3 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, iVar1, iVar2);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + iVar2);
    fn_00478cc0((int)(uVar4 + 0xc), (uint)(uVar3));
  }
  piVar8 = (int *)((int *)param_1[4]);
  if (piVar8 != (int *)0x0) {
    uVar7 = (uint)(DAT_006daef6);
    uVar3 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      while (DAT_006daef6 = uVar7, uVar3 = uVar7, (uVar7 & 3) != 0) {
        AppendGListByte(&DAT_006daf1a, 0);
        DAT_006daef6 = (uint )(DAT_006daef6 + 1);
        uVar7 = (uint)(DAT_006daef6);
      }
    }
    while( true ) {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, piVar8, 0x10);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 0x10);
      uVar6 = (undefined4)(fn_004721e0((uint)(piVar8[1])));
      fn_00478cc0((int)(uVar7 + 4), (uint)(uVar6));
      if (*piVar8 == 0) break;
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar5 = (uint)(DAT_006daef6);
      fn_00478cc0((int)(uVar7), (uint)(DAT_006daef6));
      piVar8 = (int *)((int *)*piVar8);
      uVar7 = (uint)(uVar5);
    }
    fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
  }
  return uVar4;
}

void fn_00471580(void)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  if (*(char *)(DAT_007101c4 + 0x1c) == '\0') {
    CError_Internal(s_CPrec_c_0067dd1c, 0x12b8);
  }
  piVar5 = (int *)(*(int **)(DAT_007101c4 + 8));
  if (piVar5 != (int *)0x0) {
    uVar7 = (uint)(DAT_006daef6);
    uVar2 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      while (DAT_006daef6 = uVar7, uVar2 = uVar7, (uVar7 & 3) != 0) {
        AppendGListByte(&DAT_006daf1a, 0);
        DAT_006daef6 = (uint )(DAT_006daef6 + 1);
        uVar7 = (uint)(DAT_006daef6);
      }
    }
    while( true ) {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, piVar5, 8);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 8);
      uVar4 = (undefined4)(fn_00471720((int *)(piVar5[1])));
      fn_00478cc0((int)(uVar7 + 4), (uint)(uVar4));
      if (*piVar5 == 0) break;
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar3 = (uint)(DAT_006daef6);
      fn_00478cc0((int)(uVar7), (uint)(DAT_006daef6));
      piVar5 = (int *)((int *)*piVar5);
      uVar7 = (uint)(uVar3);
    }
    if (DAT_006daee5 != '\0') {
      *(uint *)(DAT_006daf16 + 0x5e) = uVar2;
    }
  }
  if (DAT_006daee5 != '\0') {
    *(undefined4 *)(DAT_006daf16 + 0x5a) = *(undefined4 *)(DAT_007101c4 + 0x18);
  }
  iVar6 = (int)(0);
  do {
    iVar1 = (int)(*(int *)(*(int *)(DAT_007101c4 + 0x14) + iVar6 * 4));
    if ((iVar1 != 0) && (uVar4 = fn_00471a60((uint *)(iVar1), (char)(1)), DAT_006daee5 != '\0')) {
      if (DAT_006daee6 != 0) {
        return;
      }
      *(undefined4 *)(DAT_006daf16 + 0x40da + iVar6 * 4) = uVar4;
    }
    iVar6 = (int)(iVar6 + 1);
  } while (iVar6 < 0x400);
  return;
}

uint fn_00471720(int *param_1)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  for (puVar10 = *(undefined4 **)
                  (DAT_006daf12 +
                  ((int)param_1 +
                   ((uint)param_1 >> 0x18) +
                   ((uint)param_1 >> 0x10 & 0xff) +
                   ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar10 != (undefined4 *)0x0; puVar10 = (undefined4 *)*puVar10) {
    if ((int *)puVar10[1] == param_1) goto LAB_00471772;
  }
  puVar10 = (undefined4 *)((undefined4 *)0x0);
LAB_00471772:
  if (puVar10 != (undefined4 *)0x0) {
    return puVar10[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  puVar6 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar10 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar10[1] = (uint)(param_1);
  puVar10[2] = (uint)(uVar3);
  *puVar10 = (uint)(*puVar6);
  *puVar6 = (uint)(puVar10);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x22);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x22);
  if (*param_1 != 0) {
    uVar5 = (undefined4)(fn_00471720((int *)(*param_1)));
    fn_00478cc0((int)(uVar3), (uint)(uVar5));
  }
  iVar9 = (int)(param_1[1]);
  if (iVar9 != 0) {
    *(undefined4 *)(iVar9 + 4) = 1;
    fn_00478bd0((int)(uVar3 + 4), (uint)(iVar9));
  }
  piVar7 = (int *)((int *)param_1[2]);
  if (piVar7 != (int *)0x0) {
    uVar8 = (uint)(DAT_006daef6);
    uVar2 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      while (DAT_006daef6 = uVar8, uVar2 = uVar8, (uVar8 & 3) != 0) {
        AppendGListByte(&DAT_006daf1a, 0);
        DAT_006daef6 = (uint )(DAT_006daef6 + 1);
        uVar8 = (uint)(DAT_006daef6);
      }
    }
    while( true ) {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, piVar7, 8);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 8);
      uVar5 = (undefined4)(fn_00471720((int *)(piVar7[1])));
      fn_00478cc0((int)(uVar8 + 4), (uint)(uVar5));
      if (*piVar7 == 0) break;
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar4 = (uint)(DAT_006daef6);
      fn_00478cc0((int)(uVar8), (uint)(DAT_006daef6));
      piVar7 = (int *)((int *)*piVar7);
      uVar8 = (uint)(uVar4);
    }
    fn_00478cc0((int)(uVar3 + 8), (uint)(uVar2));
  }
  if (param_1[3] != 0) {
    uVar5 = (undefined4)(fn_00475390((char *)(param_1[3])));
    fn_00478cc0((int)(uVar3 + 0xc), (uint)(uVar5));
  }
  if ((char)param_1[7] == '\0') {
    if (param_1[5] != 0) {
      uVar5 = (undefined4)(fn_00471a60((uint *)(param_1[5]), (char)(0)));
      fn_00478cc0((int)(uVar3 + 0x14), (uint)(uVar5));
    }
  }
  else {
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar8 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar3 + 0x14), (uint)(DAT_006daef6));
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1[5], 0x1000);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x1000);
    iVar9 = (int)(0);
    do {
      iVar1 = (int)(*(int *)(param_1[5] + iVar9 * 4));
      if (iVar1 != 0) {
        uVar5 = (undefined4)(fn_00471a60((uint *)(iVar1), (char)(0)));
        fn_00478cc0((int)(uVar8 + iVar9 * 4), (uint)(uVar5));
      }
      iVar9 = (int)(iVar9 + 1);
    } while (iVar9 < 0x400);
  }
  return uVar3;
}

uint fn_00471a60(uint *param_1, char param_2)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  for (puVar6 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar6 != (undefined4 *)0x0; puVar6 = (undefined4 *)*puVar6) {
    if ((uint *)puVar6[1] == param_1) goto LAB_00471ab1;
  }
  puVar6 = (undefined4 *)((undefined4 *)0x0);
LAB_00471ab1:
  if (puVar6 != (undefined4 *)0x0) {
    return puVar6[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar2 = (uint)(DAT_006daef6);
  puVar7 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar6 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar6[1] = (uint)(param_1);
  puVar6[2] = (uint)(uVar2);
  *puVar6 = (uint)(*puVar7);
  *puVar7 = (uint)(puVar6);
  uVar8 = (uint)(uVar2);
  do {
    do {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x10);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 0x10);
      uVar1 = (uint)(param_1[1]);
      *(undefined4 *)(uVar1 + 4) = 1;
      fn_00478bd0((int)(uVar8 + 4), (uint)(uVar1));
      uVar4 = (undefined4)(fn_00472180((undefined1 *)(param_1[3])));
      fn_00478cc0((int)(uVar8 + 0xc), (uint)(uVar4));
      if (param_1[2] != 0) {
        uVar4 = (undefined4)(fn_00471db0((uint *)(param_1[2])));
        fn_00478cc0((int)(uVar8 + 8), (uint)(uVar4));
      }
      uVar1 = (uint)(*param_1);
      if (uVar1 == 0) {
        return uVar2;
      }
      for (puVar6 = *(undefined4 **)
                     (DAT_006daf12 +
                     ((uVar1 & 0xff) + uVar1 + (uVar1 >> 8 & 0xff) + (uVar1 >> 0x10 & 0xff) +
                      (uVar1 >> 0x18) & 0x3fff) * 4); puVar6 != (undefined4 *)0x0;
          puVar6 = (undefined4 *)*puVar6) {
        if (puVar6[1] == uVar1) goto LAB_00471bff;
      }
      puVar6 = (undefined4 *)((undefined4 *)0x0);
LAB_00471bff:
      if (puVar6 != (undefined4 *)0x0) {
        fn_00478cc0((int)(uVar8), (uint)(puVar6[2]));
        return uVar2;
      }
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar1 = (uint)(DAT_006daef6);
      fn_00478cc0((int)(uVar8), (uint)(DAT_006daef6));
      param_1 = (uint *)((uint *)*param_1);
      puVar7 = (undefined4 *)((undefined4 *)
               (((int)param_1 +
                 ((uint)param_1 >> 0x18) +
                 ((uint)param_1 >> 0x10 & 0xff) +
                 ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4 + DAT_006daf12));
      puVar6 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
      puVar6[1] = (uint)(param_1);
      puVar6[2] = (uint)(uVar1);
      *puVar6 = (uint)(*puVar7);
      *puVar7 = (uint)(puVar6);
      uVar8 = (uint)(uVar1);
    } while ((param_2 == '\0') || (DAT_006daee5 == '\0'));
    if (DAT_006daed0 < DAT_006daf1e) {
      DAT_006daed0 = (uint )(DAT_006daf1e);
    }
    if (DAT_006daf1e < 0x2711) {
LAB_00471d74:
      iVar5 = (int)(0);
      iVar3 = (int)(DAT_006daee6);
    }
    else {
      if (DAT_006daee5 == '\0') {
        iVar5 = (int)(0);
      }
      else {
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        _DAT_006daef2 = (uint )(_DAT_006daef2 + DAT_006daf1e);
        FUN_0044cfe0(DAT_006daf1a);
        iVar5 = (int)(fn_00471090((char *)(*DAT_006daf1a), (int)(DAT_006daf1e)));
        FUN_0044d0a0(DAT_006daf1a);
        DAT_006daf1e = (int )(0);
      }
      iVar3 = (int)(iVar5);
      if (iVar5 == 0) goto LAB_00471d74;
    }
    DAT_006daee6 = (uint )(iVar3);
    if (iVar5 != 0) {
      return uVar2;
    }
  } while( true );
}

uint fn_00471db0(uint *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint uVar6;
  for (puVar3 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3) {
    if ((uint *)puVar3[1] == param_1) goto LAB_00471e01;
  }
  puVar3 = (undefined4 *)((undefined4 *)0x0);
LAB_00471e01:
  if (puVar3 != (undefined4 *)0x0) {
    return puVar3[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar2 = (uint)(DAT_006daef6);
  puVar5 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar3[1] = (uint)(param_1);
  puVar3[2] = (uint)(uVar2);
  *puVar3 = (uint)(*puVar5);
  *puVar5 = (uint)(puVar3);
  uVar6 = (uint)(uVar2);
  do {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 8);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 8);
    uVar4 = (undefined4)(fn_00472180((undefined1 *)(param_1[1])));
    fn_00478cc0((int)(uVar6 + 4), (uint)(uVar4));
    uVar1 = (uint)(*param_1);
    if (uVar1 == 0) {
      return uVar2;
    }
    for (puVar3 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar1 & 0xff) + uVar1 + (uVar1 >> 8 & 0xff) + (uVar1 >> 0x10 & 0xff) +
                    (uVar1 >> 0x18) & 0x3fff) * 4); puVar3 != (undefined4 *)0x0;
        puVar3 = (undefined4 *)*puVar3) {
      if (puVar3[1] == uVar1) goto LAB_00471f1f;
    }
    puVar3 = (undefined4 *)((undefined4 *)0x0);
LAB_00471f1f:
    if (puVar3 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar6), (uint)(puVar3[2]));
      return uVar2;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar1 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar6), (uint)(DAT_006daef6));
    param_1 = (uint *)((uint *)*param_1);
    puVar5 = (undefined4 *)((undefined4 *)
             (((int)param_1 +
               ((uint)param_1 >> 0x18) +
               ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)
              & 0x3fff) * 4 + DAT_006daf12));
    puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar3[1] = (uint)(param_1);
    puVar3[2] = (uint)(uVar1);
    *puVar3 = (uint)(*puVar5);
    *puVar5 = (uint)(puVar3);
    uVar6 = (uint)(uVar1);
  } while( true );
}

uint fn_00471ff0(int *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  for (puVar4 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
    if ((int *)puVar4[1] == param_1) goto LAB_00472040;
  }
  puVar4 = (undefined4 *)((undefined4 *)0x0);
LAB_00472040:
  if (puVar4 != (undefined4 *)0x0) {
    return puVar4[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  puVar5 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar4 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar4[1] = (uint)(param_1);
  puVar4[2] = (uint)(uVar1);
  *puVar4 = (uint)(*puVar5);
  *puVar5 = (uint)(puVar4);
  uVar6 = (uint)(uVar1);
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 8);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 8);
    uVar3 = (undefined4)(fn_004721e0((uint)(param_1[1])));
    fn_00478cc0((int)(uVar6 + 4), (uint)(uVar3));
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar6), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar6 = (uint)(uVar2);
  }
  return uVar1;
}

uint fn_00472180(undefined1 *param_1)
{
  { uint nativeSwitch1Value=(uint)(*param_1);
if(nativeSwitch1Value==(uint)(0)) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)(1)) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)(2)) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)(3)) goto nativeSwitch1Case3;
if(nativeSwitch1Value==(uint)(4)) goto nativeSwitch1Case4;
if(nativeSwitch1Value==(uint)(5)) goto nativeSwitch1Case5;
goto nativeSwitch1Case6;

  nativeSwitch1Case0:
    goto nativeSwitch1End;
  nativeSwitch1Case1:
    return fn_00472de0((uint)(param_1));
  nativeSwitch1Case2:
    return fn_00472cb0((uint)(param_1));
  nativeSwitch1Case3:
    return fn_00472b80((uint)(param_1));
  nativeSwitch1Case4:
    return fn_004728b0((uint)(param_1));
  nativeSwitch1Case5:
    return fn_004721e0((uint)(param_1));
  nativeSwitch1Case6:
    CError_Internal(s_CPrec_c_0067dd1c, 0x11e5);

nativeSwitch1End:;
}
  return fn_00472f10((uint)(param_1));
}

uint fn_004721e0(uint param_1)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *puVar6;
  int *piVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  iVar3 = (int)(FUN_00420190((uint)(DAT_00716ed2)));
  if (iVar3 != 0) {
    FUN_0045a1e0();
  }
  for (puVar9 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
                  (param_1 >> 0x18) & 0x3fff) * 4); puVar9 != (undefined4 *)0x0;
      puVar9 = (undefined4 *)*puVar9) {
    if (puVar9[1] == param_1) goto LAB_00472242;
  }
  puVar9 = (undefined4 *)((undefined4 *)0x0);
LAB_00472242:
  if (puVar9 != (undefined4 *)0x0) {
    return puVar9[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  puVar6 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar9 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar9[1] = (uint)(param_1);
  puVar9[2] = (uint)(uVar1);
  *puVar9 = (uint)(*puVar6);
  *puVar6 = (uint)(puVar9);
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  if (((*(uint *)(param_1 + 0x14) & 0x400000) == 0) || (*(char *)(param_1 + 2) == '\x06')) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x60);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x60);
  }
  else {
    *(undefined4 *)(param_1 + 100) = 0;
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x6a);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x6a);
    uVar4 = (undefined4)(fn_004721e0((uint)(*(undefined4 *)(param_1 + 0x60))));
    fn_00478cc0((int)(uVar1 + 0x60), (uint)(uVar4));
  }
  if (*(int *)(param_1 + 8) != 0) {
    if (*(char *)(param_1 + 2) == '\x01') {
      CError_Internal(s_CPrec_c_0067dd1c, 0x114b);
    }
    uVar4 = (undefined4)(fn_00471720((int *)(*(undefined4 *)(param_1 + 8))));
    fn_00478cc0((int)(uVar1 + 8), (uint)(uVar4));
  }
  iVar3 = (int)(*(int *)(param_1 + 0xc));
  if (iVar3 != 0) {
    *(undefined4 *)(iVar3 + 4) = 1;
    fn_00478bd0((int)(uVar1 + 0xc), (uint)(iVar3));
  }
  uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 0x10))));
  uVar10 = (uint)(uVar1);
  fn_00478cc0((int)(uVar1 + 0x10), (uint)(uVar4));
  { uint nativeSwitch2Value=(uint)(*(undefined1 *)(param_1 + 2));
if(nativeSwitch2Value==(uint)(0)) goto nativeSwitch2Case0;
if(nativeSwitch2Value==(uint)(1)) goto nativeSwitch2Case1;
if(nativeSwitch2Value==(uint)(2)) goto nativeSwitch2Case2;
if(nativeSwitch2Value==(uint)(3)) goto nativeSwitch2Case3;
if(nativeSwitch2Value==(uint)(4)) goto nativeSwitch2Case4;
if(nativeSwitch2Value==(uint)(5)) goto nativeSwitch2Case5;
if(nativeSwitch2Value==(uint)(6)) goto nativeSwitch2Case6;
goto nativeSwitch2Case7;

  nativeSwitch2Case0:
    if (*(int *)(param_1 + 0x54) != 0) {
      CError_Internal(s_CPrec_c_0067dd1c, 0x1191);
    }
    if ((*(uint *)(param_1 + 0x14) & 0x10000) != 0) {
      { uint nativeSwitch1Value=(uint)(**(undefined1 **)(param_1 + 0x10));
if(nativeSwitch1Value==(uint)(1)) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)(4)) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)(0xc)) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)(2)) goto nativeSwitch1Case3;
goto nativeSwitch1Case4;

      nativeSwitch1Case0:
      nativeSwitch1Case1:
      nativeSwitch1Case2:
        goto nativeSwitch1End;
      nativeSwitch1Case3:
        uVar4 = (undefined4)(*(undefined4 *)(param_1 + 0x40));
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar5 = (uint)(DAT_006daef6);
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, uVar4, 8);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + 8);
        fn_00478cc0((int)(uVar10 + 0x40), (uint)(uVar5));
        goto nativeSwitch1End;
      nativeSwitch1Case4:
        CError_Internal(s_CPrec_c_0067dd1c, 0x11a1);

nativeSwitch1End:;
}
    }
    iVar3 = (int)(*(int *)(param_1 + 0x48));
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 4) = 1;
      fn_00478bd0((int)(uVar10 + 0x48), (uint)(iVar3));
    }
    if (*(int *)(param_1 + 0x4c) != 0) {
      uVar4 = (undefined4)(fn_00471380((int *)(*(int *)(param_1 + 0x4c))));
      fn_00478cc0((int)(uVar10 + 0x4c), (uint)(uVar4));
    }
    iVar3 = (int)(*(int *)(param_1 + 0x50));
    if ((iVar3 != 0) && (iVar3 != 0)) {
      uVar4 = (undefined4)(fn_00476490((int *)(iVar3)));
      fn_00478cc0((int)(uVar10 + 0x50), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case1:
  nativeSwitch2Case2:
    goto nativeSwitch2End;
  nativeSwitch2Case3:
  nativeSwitch2Case4:
    if (**(char **)(param_1 + 0x10) == '\a') {
      uVar5 = (uint)(*(uint *)(*(char **)(param_1 + 0x10) + 0x16));
      if ((uVar5 & 0x100000) == 0) {
        if ((uVar5 & 0x200) != 0) goto LAB_004727e8;
        if ((*(uint *)(param_1 + 0x14) & 0x800000) == 0) {
          if (((*(uint *)(param_1 + 0x14) & 0x10) == 0) || (*(int *)(param_1 + 0x40) == 0))
          goto LAB_004727e8;
          uVar5 = (uint)(fn_004731a0((int *)(*(int *)(param_1 + 0x40))));
          iVar3 = (int)(uVar10 + 0x40);
        }
        else {
          puVar9 = (undefined4 *)(*(undefined4 **)(param_1 + 0x40));
          if (DAT_006daee5 != '\0') {
            for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
              AppendGListByte(&DAT_006daf1a, 0);
            }
          }
          uVar5 = (uint)(DAT_006daef6);
          if (DAT_006daee5 != '\0') {
            CompilerTools_AppendGListData(&DAT_006daf1a, puVar9, 0x10);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 0x10);
          uVar4 = (undefined4)(fn_004721e0((uint)(*puVar9)));
          fn_00478cc0((int)(uVar5), (uint)(uVar4));
          iVar3 = (int)(uVar10 + 0x40);
        }
      }
      else {
        uVar5 = (uint)(fn_00475ca0((int *)(*(undefined4 *)(param_1 + 0x40))));
        iVar3 = (int)(uVar10 + 0x40);
      }
      fn_00478cc0((int)(iVar3), (uint)(uVar5));
    }
LAB_004727e8:
    if (*(int *)(param_1 + 0x50) != 0) {
      uVar4 = (undefined4)(fn_004721e0((uint)(*(int *)(param_1 + 0x50))));
      fn_00478cc0((int)(uVar10 + 0x50), (uint)(uVar4));
    }
    iVar3 = (int)(*(int *)(param_1 + 0x44));
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 4) = 1;
      fn_00478bd0((int)(uVar10 + 0x44), (uint)(iVar3));
    }
    if (*(int *)(param_1 + 0x48) != 0) {
      uVar4 = (undefined4)(fn_00476670((int *)(*(int *)(param_1 + 0x48))));
      fn_00478cc0((int)(uVar10 + 0x48), (uint)(uVar4));
    }
    iVar3 = (int)(*(int *)(param_1 + 0x4c));
    if ((iVar3 != 0) && (iVar3 != 0)) {
      uVar4 = (undefined4)(fn_00476490((int *)(iVar3)));
      fn_00478cc0((int)(uVar10 + 0x4c), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case5:
    iVar3 = (int)(*(int *)(param_1 + 0x44));
    uVar4 = (undefined4)(*(undefined4 *)(param_1 + 0x40));
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar5 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, uVar4, iVar3);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + iVar3);
    fn_00478cc0((int)(uVar10 + 0x40), (uint)(uVar5));
    piVar7 = (int *)(*(int **)(param_1 + 0x48));
    if (piVar7 != (int *)0x0) {
      uVar8 = (uint)(DAT_006daef6);
      uVar5 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        while (DAT_006daef6 = uVar8, uVar5 = uVar8, (uVar8 & 3) != 0) {
          AppendGListByte(&DAT_006daf1a, 0);
          DAT_006daef6 = (uint )(DAT_006daef6 + 1);
          uVar8 = (uint)(DAT_006daef6);
        }
      }
      while( true ) {
        iVar3 = (int)((*(ushort *)((int)piVar7 + 10) - 1) * 8 + 0x14);
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, piVar7, iVar3);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + iVar3);
        uVar4 = (undefined4)(fn_004721e0((uint)(piVar7[1])));
        fn_00478cc0((int)(uVar8 + 4), (uint)(uVar4));
        if (*piVar7 == 0) break;
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar2 = (uint)(DAT_006daef6);
        fn_00478cc0((int)(uVar8), (uint)(DAT_006daef6));
        piVar7 = (int *)((int *)*piVar7);
        uVar8 = (uint)(uVar2);
      }
      fn_00478cc0((int)(uVar10 + 0x48), (uint)(uVar5));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case6:
    uVar4 = (undefined4)(fn_004721e0((uint)(*(undefined4 *)(param_1 + 0x40))));
    fn_00478cc0((int)(uVar10 + 0x40), (uint)(uVar4));
    if (*(int *)(param_1 + 0x44) != 0) {
      uVar4 = (undefined4)(fn_00475030((char *)(*(int *)(param_1 + 0x44))));
      fn_00478cc0((int)(uVar10 + 0x44), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case7:
    CError_Internal(s_CPrec_c_0067dd1c, 0x11d4);

nativeSwitch2End:;
}
  if (DAT_006daee5 != '\0') {
    *(undefined1 *)(param_1 + 2) = 0xff;
  }
  return uVar1;
}

uint fn_004728b0(uint param_1)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  for (puVar6 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
                  (param_1 >> 0x18) & 0x3fff) * 4); puVar6 != (undefined4 *)0x0;
      puVar6 = (undefined4 *)*puVar6) {
    if (puVar6[1] == param_1) goto LAB_00472901;
  }
  puVar6 = (undefined4 *)((undefined4 *)0x0);
LAB_00472901:
  if (puVar6 != (undefined4 *)0x0) {
    return puVar6[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  puVar5 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar6 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar6[1] = (uint)(param_1);
  puVar6[2] = (uint)(uVar3);
  *puVar6 = (uint)(*puVar5);
  *puVar5 = (uint)(puVar6);
  uVar7 = (uint)(uVar3);
  do {
    if (*(char *)(param_1 + 3) == '\0') {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x18);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 0x18);
    }
    else {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x20);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 0x20);
      if (*(int *)(param_1 + 0x18) != 0) {
        uVar4 = (undefined4)(fn_00475390((char *)(*(int *)(param_1 + 0x18))));
        fn_00478cc0((int)(uVar7 + 0x18), (uint)(uVar4));
      }
      if (*(int *)(param_1 + 0x1c) != 0) {
        uVar4 = (undefined4)(fn_004728b0((uint)(*(int *)(param_1 + 0x1c))));
        fn_00478cc0((int)(uVar7 + 0x1c), (uint)(uVar4));
      }
    }
    iVar1 = (int)(*(int *)(param_1 + 8));
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 4) = 1;
      fn_00478bd0((int)(uVar7 + 8), (uint)(iVar1));
    }
    uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 0xc))));
    fn_00478cc0((int)(uVar7 + 0xc), (uint)(uVar4));
    uVar2 = (uint)(*(uint *)(param_1 + 4));
    if (uVar2 == 0) {
      return uVar3;
    }
    for (puVar6 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar2 & 0xff) + uVar2 + (uVar2 >> 8 & 0xff) + (uVar2 >> 0x10 & 0xff) +
                    (uVar2 >> 0x18) & 0x3fff) * 4); puVar6 != (undefined4 *)0x0;
        puVar6 = (undefined4 *)*puVar6) {
      if (puVar6[1] == uVar2) goto LAB_00472a7e;
    }
    puVar6 = (undefined4 *)((undefined4 *)0x0);
LAB_00472a7e:
    if (puVar6 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar7 + 4), (uint)(puVar6[2]));
      return uVar3;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar7 + 4), (uint)(DAT_006daef6));
    param_1 = (uint)(*(uint *)(param_1 + 4));
    puVar5 = (undefined4 *)((undefined4 *)
             (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
               (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
    puVar6 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar6[1] = (uint)(param_1);
    puVar6[2] = (uint)(uVar2);
    *puVar6 = (uint)(*puVar5);
    *puVar5 = (uint)(puVar6);
    uVar7 = (uint)(uVar2);
  } while( true );
}

uint fn_00472b80(uint param_1)
{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  for (puVar3 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
                  (param_1 >> 0x18) & 0x3fff) * 4); puVar3 != (undefined4 *)0x0;
      puVar3 = (undefined4 *)*puVar3) {
    if (puVar3[1] == param_1) goto LAB_00472bd3;
  }
  puVar3 = (undefined4 *)((undefined4 *)0x0);
LAB_00472bd3:
  if (puVar3 != (undefined4 *)0x0) {
    return puVar3[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  puVar4 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar3[1] = (uint)(param_1);
  puVar3[2] = (uint)(uVar1);
  *puVar3 = (uint)(*puVar4);
  *puVar4 = (uint)(puVar3);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 6);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 6);
  uVar2 = (undefined4)(fn_00471720((int *)(*(undefined4 *)(param_1 + 2))));
  fn_00478cc0((int)(uVar1 + 2), (uint)(uVar2));
  return uVar1;
}

uint fn_00472cb0(uint param_1)
{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  for (puVar3 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
                  (param_1 >> 0x18) & 0x3fff) * 4); puVar3 != (undefined4 *)0x0;
      puVar3 = (undefined4 *)*puVar3) {
    if (puVar3[1] == param_1) goto LAB_00472d03;
  }
  puVar3 = (undefined4 *)((undefined4 *)0x0);
LAB_00472d03:
  if (puVar3 != (undefined4 *)0x0) {
    return puVar3[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  puVar4 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar3[1] = (uint)(param_1);
  puVar3[2] = (uint)(uVar1);
  *puVar3 = (uint)(*puVar4);
  *puVar4 = (uint)(puVar3);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 6);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 6);
  uVar2 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 2))));
  fn_00478cc0((int)(uVar1 + 2), (uint)(uVar2));
  return uVar1;
}

uint fn_00472de0(uint param_1)
{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  for (puVar3 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
                  (param_1 >> 0x18) & 0x3fff) * 4); puVar3 != (undefined4 *)0x0;
      puVar3 = (undefined4 *)*puVar3) {
    if (puVar3[1] == param_1) goto LAB_00472e33;
  }
  puVar3 = (undefined4 *)((undefined4 *)0x0);
LAB_00472e33:
  if (puVar3 != (undefined4 *)0x0) {
    return puVar3[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  puVar4 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar3[1] = (uint)(param_1);
  puVar3[2] = (uint)(uVar1);
  *puVar3 = (uint)(*puVar4);
  *puVar4 = (uint)(puVar3);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 10);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 10);
  uVar2 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 2))));
  fn_00478cc0((int)(uVar1 + 2), (uint)(uVar2));
  return uVar1;
}

uint fn_00472f10(uint param_1)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  for (puVar6 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
                  (param_1 >> 0x18) & 0x3fff) * 4); puVar6 != (undefined4 *)0x0;
      puVar6 = (undefined4 *)*puVar6) {
    if (puVar6[1] == param_1) goto LAB_00472f61;
  }
  puVar6 = (undefined4 *)((undefined4 *)0x0);
LAB_00472f61:
  if (puVar6 != (undefined4 *)0x0) {
    return puVar6[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  puVar5 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar6 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar6[1] = (uint)(param_1);
  puVar6[2] = (uint)(uVar3);
  *puVar6 = (uint)(*puVar5);
  *puVar5 = (uint)(puVar6);
  uVar7 = (uint)(uVar3);
  do {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x16);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x16);
    if (DAT_006daee5 != '\0') {
      if (*(char *)(param_1 + 1) == -1) {
        CError_Internal(s_CPrec_c_0067dd1c, 0x1067);
      }
      *(undefined1 *)(param_1 + 1) = 0xff;
    }
    iVar1 = (int)(*(int *)(param_1 + 6));
    *(undefined4 *)(iVar1 + 4) = 1;
    fn_00478bd0((int)(uVar7 + 6), (uint)(iVar1));
    uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 10))));
    fn_00478cc0((int)(uVar7 + 10), (uint)(uVar4));
    uVar2 = (uint)(*(uint *)(param_1 + 2));
    if (uVar2 == 0) {
      return uVar3;
    }
    for (puVar6 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar2 & 0xff) + uVar2 + (uVar2 >> 8 & 0xff) + (uVar2 >> 0x10 & 0xff) +
                    (uVar2 >> 0x18) & 0x3fff) * 4); puVar6 != (undefined4 *)0x0;
        puVar6 = (undefined4 *)*puVar6) {
      if (puVar6[1] == uVar2) goto LAB_004730a1;
    }
    puVar6 = (undefined4 *)((undefined4 *)0x0);
LAB_004730a1:
    if (puVar6 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar7 + 2), (uint)(puVar6[2]));
      return uVar3;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar7 + 2), (uint)(DAT_006daef6));
    param_1 = (uint)(*(uint *)(param_1 + 2));
    puVar5 = (undefined4 *)((undefined4 *)
             (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
               (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
    puVar6 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar6[1] = (uint)(param_1);
    puVar6[2] = (uint)(uVar2);
    *puVar6 = (uint)(*puVar5);
    *puVar5 = (uint)(puVar6);
    uVar7 = (uint)(uVar2);
  } while( true );
}

uint fn_004731a0(int *param_1)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  for (puVar4 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
    if ((int *)puVar4[1] == param_1) goto LAB_004731ef;
  }
  puVar4 = (undefined4 *)((undefined4 *)0x0);
LAB_004731ef:
  if (puVar4 != (undefined4 *)0x0) {
    return puVar4[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  puVar6 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar4 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar4[1] = (uint)(param_1);
  puVar4[2] = (uint)(uVar3);
  *puVar4 = (uint)(*puVar6);
  *puVar6 = (uint)(puVar4);
  iVar1 = (int)(param_1[1]);
  iVar2 = (int)(param_1[0x31]);
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 0x31) = 1;
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0xc6);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0xc6);
  param_1[1] = iVar1;
  *(char *)(param_1 + 0x31) = (char)iVar2;
  if (*param_1 != 0) {
    uVar5 = (undefined4)(fn_00473300((undefined4 *)(*param_1)));
    fn_00478cc0((int)(uVar3), (uint)(uVar5));
  }
  return uVar3;
}

uint fn_00473300(undefined4 *param_1)
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  *(undefined1 *)(param_1 + 6) = 0;
  iVar6 = (int)(param_1[5] * 8 + 0x1a);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, iVar6);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + iVar6);
  uVar4 = (undefined4)(*param_1);
  iVar6 = (int)(param_1[1]);
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, uVar4, iVar6);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + iVar6);
  fn_00478cc0((int)(uVar3), (uint)(uVar1));
  uVar1 = (uint)(param_1[5]);
  iVar6 = (int)(uVar3 + 0x1a);
  uVar5 = (uint)(0);
  piVar7 = (int *)((int *)((int)param_1 + 0x1a));
  if (uVar1 != 0) {
    do {
      { uint nativeSwitch1Value=(uint)((char)piVar7[1]);
if(nativeSwitch1Value==(uint)('\0')) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)('\x01')) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)('\x02')) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)('\x03')) goto nativeSwitch1Case3;
if(nativeSwitch1Value==(uint)('\x04')) goto nativeSwitch1Case4;
if(nativeSwitch1Value==(uint)('\x05')) goto nativeSwitch1Case5;
if(nativeSwitch1Value==(uint)('\x06')) goto nativeSwitch1Case6;
if(nativeSwitch1Value==(uint)('\a')) goto nativeSwitch1Case7;
if(nativeSwitch1Value==(uint)('\b')) goto nativeSwitch1Case8;
goto nativeSwitch1Case9;

      nativeSwitch1Case0:
        uVar4 = (undefined4)(fn_00475030((char *)(*piVar7)));
        fn_00478cc0((int)(iVar6), (uint)(uVar4));
        goto nativeSwitch1End;
      nativeSwitch1Case1:
        uVar4 = (undefined4)(fn_004721e0((uint)(*piVar7)));
        fn_00478cc0((int)(iVar6), (uint)(uVar4));
        goto nativeSwitch1End;
      nativeSwitch1Case2:
        uVar4 = (undefined4)(fn_004781b0((int *)(*piVar7)));
        fn_00478cc0((int)(iVar6), (uint)(uVar4));
        goto nativeSwitch1End;
      nativeSwitch1Case3:
        if (*piVar7 != 0) {
          uVar4 = (undefined4)(fn_00472de0((uint)(*piVar7)));
          fn_00478cc0((int)(iVar6), (uint)(uVar4));
        }
        goto nativeSwitch1End;
      nativeSwitch1Case4:
        iVar2 = (int)(*piVar7);
        *(undefined4 *)(iVar2 + 4) = 1;
        fn_00478bd0((int)(iVar6), (uint)(iVar2));
        goto nativeSwitch1End;
      nativeSwitch1Case5:
        uVar4 = (undefined4)(fn_00471db0((uint *)(*piVar7)));
        fn_00478cc0((int)(iVar6), (uint)(uVar4));
        goto nativeSwitch1End;
      nativeSwitch1Case6:
        uVar4 = (undefined4)(fn_00476dd0((int *)(*piVar7)));
        fn_00478cc0((int)(iVar6), (uint)(uVar4));
        goto nativeSwitch1End;
      nativeSwitch1Case7:
        uVar4 = (undefined4)(fn_00474e70((int *)(*piVar7)));
        fn_00478cc0((int)(iVar6), (uint)(uVar4));
        goto nativeSwitch1End;
      nativeSwitch1Case8:
        uVar4 = (undefined4)(fn_004728b0((uint)(*piVar7)));
        fn_00478cc0((int)(iVar6), (uint)(uVar4));
        goto nativeSwitch1End;
      nativeSwitch1Case9:
        CError_Internal(s_CPrec_c_0067dd1c, 0xffa);

nativeSwitch1End:;
}
      uVar5 = (uint)(uVar5 + 1);
      piVar7 = (int *)(piVar7 + 2);
      iVar6 = (int)(iVar6 + 8);
    } while (uVar5 < uVar1);
  }
  return uVar3;
}

uint fn_00473510(char *param_1)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  int *piVar9;
  char *pcVar10;
  uint uVar11;
  uint uVar12;
  do {
    pcVar8 = (char *)(param_1);
    if ((*pcVar8 != 'L') || (pcVar8[0x2c] != '\x06')) goto LAB_004742a0;
    param_1 = (char *)(*(char **)(pcVar8 + 0x10));
  } while (**(char **)(pcVar8 + 0x10) == 'L');
  memclrw(pcVar8 + 0x14, 0xc);
LAB_004742a0:
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar11 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, pcVar8, 0x2e);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x2e);
  uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(pcVar8 + 4))));
  uVar12 = (uint)(uVar11);
  fn_00478cc0((int)(uVar11 + 4), (uint)(uVar4));
  { uint nativeSwitch2Value=(uint)(*pcVar8);
if(nativeSwitch2Value==(uint)('\0')) goto nativeSwitch2Case0;
if(nativeSwitch2Value==(uint)('\x01')) goto nativeSwitch2Case1;
if(nativeSwitch2Value==(uint)('\x02')) goto nativeSwitch2Case2;
if(nativeSwitch2Value==(uint)('\x03')) goto nativeSwitch2Case3;
if(nativeSwitch2Value==(uint)('\x04')) goto nativeSwitch2Case4;
if(nativeSwitch2Value==(uint)('\x05')) goto nativeSwitch2Case5;
if(nativeSwitch2Value==(uint)('\x06')) goto nativeSwitch2Case6;
if(nativeSwitch2Value==(uint)('\a')) goto nativeSwitch2Case7;
if(nativeSwitch2Value==(uint)('\b')) goto nativeSwitch2Case8;
if(nativeSwitch2Value==(uint)('2')) goto nativeSwitch2Case9;
if(nativeSwitch2Value==(uint)('3')) goto nativeSwitch2Case10;
if(nativeSwitch2Value==(uint)('\t')) goto nativeSwitch2Case11;
if(nativeSwitch2Value==(uint)('\n')) goto nativeSwitch2Case12;
if(nativeSwitch2Value==(uint)('\v')) goto nativeSwitch2Case13;
if(nativeSwitch2Value==(uint)('\f')) goto nativeSwitch2Case14;
if(nativeSwitch2Value==(uint)('\r')) goto nativeSwitch2Case15;
if(nativeSwitch2Value==(uint)('\x0e')) goto nativeSwitch2Case16;
if(nativeSwitch2Value==(uint)('\x0f')) goto nativeSwitch2Case17;
if(nativeSwitch2Value==(uint)('\x10')) goto nativeSwitch2Case18;
if(nativeSwitch2Value==(uint)('\x11')) goto nativeSwitch2Case19;
if(nativeSwitch2Value==(uint)('\x12')) goto nativeSwitch2Case20;
if(nativeSwitch2Value==(uint)('\x13')) goto nativeSwitch2Case21;
if(nativeSwitch2Value==(uint)('\x14')) goto nativeSwitch2Case22;
if(nativeSwitch2Value==(uint)('\x15')) goto nativeSwitch2Case23;
if(nativeSwitch2Value==(uint)('\x16')) goto nativeSwitch2Case24;
if(nativeSwitch2Value==(uint)('\x17')) goto nativeSwitch2Case25;
if(nativeSwitch2Value==(uint)('\x18')) goto nativeSwitch2Case26;
if(nativeSwitch2Value==(uint)('\x19')) goto nativeSwitch2Case27;
if(nativeSwitch2Value==(uint)('\x1a')) goto nativeSwitch2Case28;
if(nativeSwitch2Value==(uint)('\x1b')) goto nativeSwitch2Case29;
if(nativeSwitch2Value==(uint)('\x1c')) goto nativeSwitch2Case30;
if(nativeSwitch2Value==(uint)('\x1d')) goto nativeSwitch2Case31;
if(nativeSwitch2Value==(uint)('\x1e')) goto nativeSwitch2Case32;
if(nativeSwitch2Value==(uint)('\x1f')) goto nativeSwitch2Case33;
if(nativeSwitch2Value==(uint)(' ')) goto nativeSwitch2Case34;
if(nativeSwitch2Value==(uint)('!')) goto nativeSwitch2Case35;
if(nativeSwitch2Value==(uint)('\"')) goto nativeSwitch2Case36;
if(nativeSwitch2Value==(uint)('#')) goto nativeSwitch2Case37;
if(nativeSwitch2Value==(uint)('$')) goto nativeSwitch2Case38;
if(nativeSwitch2Value==(uint)('%')) goto nativeSwitch2Case39;
if(nativeSwitch2Value==(uint)('&')) goto nativeSwitch2Case40;
if(nativeSwitch2Value==(uint)('\'')) goto nativeSwitch2Case41;
if(nativeSwitch2Value==(uint)('(')) goto nativeSwitch2Case42;
if(nativeSwitch2Value==(uint)(')')) goto nativeSwitch2Case43;
if(nativeSwitch2Value==(uint)('*')) goto nativeSwitch2Case44;
if(nativeSwitch2Value==(uint)('+')) goto nativeSwitch2Case45;
if(nativeSwitch2Value==(uint)(',')) goto nativeSwitch2Case46;
if(nativeSwitch2Value==(uint)('-')) goto nativeSwitch2Case47;
if(nativeSwitch2Value==(uint)('.')) goto nativeSwitch2Case48;
if(nativeSwitch2Value==(uint)('/')) goto nativeSwitch2Case49;
if(nativeSwitch2Value==(uint)('0')) goto nativeSwitch2Case50;
if(nativeSwitch2Value==(uint)('1')) goto nativeSwitch2Case51;
if(nativeSwitch2Value==(uint)('M')) goto nativeSwitch2Case52;
if(nativeSwitch2Value==(uint)('N')) goto nativeSwitch2Case53;
if(nativeSwitch2Value==(uint)('4')) goto nativeSwitch2Case54;
if(nativeSwitch2Value==(uint)('5')) goto nativeSwitch2Case55;
if(nativeSwitch2Value==(uint)('=')) goto nativeSwitch2Case56;
if(nativeSwitch2Value==(uint)('>')) goto nativeSwitch2Case57;
if(nativeSwitch2Value==(uint)('S')) goto nativeSwitch2Case58;
if(nativeSwitch2Value==(uint)('W')) goto nativeSwitch2Case59;
if(nativeSwitch2Value==(uint)('7')) goto nativeSwitch2Case61;
if(nativeSwitch2Value==(uint)('8')) goto nativeSwitch2Case62;
if(nativeSwitch2Value==(uint)('9')) goto nativeSwitch2Case63;
if(nativeSwitch2Value==(uint)(':')) goto nativeSwitch2Case64;
if(nativeSwitch2Value==(uint)(';')) goto nativeSwitch2Case65;
if(nativeSwitch2Value==(uint)('@')) goto nativeSwitch2Case66;
if(nativeSwitch2Value==(uint)('A')) goto nativeSwitch2Case67;
if(nativeSwitch2Value==(uint)('R')) goto nativeSwitch2Case68;
if(nativeSwitch2Value==(uint)('<')) goto nativeSwitch2Case69;
if(nativeSwitch2Value==(uint)('?')) goto nativeSwitch2Case70;
if(nativeSwitch2Value==(uint)('B')) goto nativeSwitch2Case71;
if(nativeSwitch2Value==(uint)('C')) goto nativeSwitch2Case72;
if(nativeSwitch2Value==(uint)('D')) goto nativeSwitch2Case73;
if(nativeSwitch2Value==(uint)('H')) goto nativeSwitch2Case74;
if(nativeSwitch2Value==(uint)('I')) goto nativeSwitch2Case75;
if(nativeSwitch2Value==(uint)('J')) goto nativeSwitch2Case76;
if(nativeSwitch2Value==(uint)('K')) goto nativeSwitch2Case77;
if(nativeSwitch2Value==(uint)('L')) goto nativeSwitch2Case78;
if(nativeSwitch2Value==(uint)('O')) goto nativeSwitch2Case79;
if(nativeSwitch2Value==(uint)('Q')) goto nativeSwitch2Case80;
goto nativeSwitch2Case60;

  nativeSwitch2Case0:
  nativeSwitch2Case1:
  nativeSwitch2Case2:
  nativeSwitch2Case3:
  nativeSwitch2Case4:
  nativeSwitch2Case5:
  nativeSwitch2Case6:
  nativeSwitch2Case7:
  nativeSwitch2Case8:
  nativeSwitch2Case9:
  nativeSwitch2Case10:
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
    fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    goto nativeSwitch2End;
  nativeSwitch2Case11:
  nativeSwitch2Case12:
  nativeSwitch2Case13:
  nativeSwitch2Case14:
  nativeSwitch2Case15:
  nativeSwitch2Case16:
  nativeSwitch2Case17:
  nativeSwitch2Case18:
  nativeSwitch2Case19:
  nativeSwitch2Case20:
  nativeSwitch2Case21:
  nativeSwitch2Case22:
  nativeSwitch2Case23:
  nativeSwitch2Case24:
  nativeSwitch2Case25:
  nativeSwitch2Case26:
  nativeSwitch2Case27:
  nativeSwitch2Case28:
  nativeSwitch2Case29:
  nativeSwitch2Case30:
  nativeSwitch2Case31:
  nativeSwitch2Case32:
  nativeSwitch2Case33:
  nativeSwitch2Case34:
  nativeSwitch2Case35:
  nativeSwitch2Case36:
  nativeSwitch2Case37:
  nativeSwitch2Case38:
  nativeSwitch2Case39:
  nativeSwitch2Case40:
  nativeSwitch2Case41:
  nativeSwitch2Case42:
  nativeSwitch2Case43:
  nativeSwitch2Case44:
  nativeSwitch2Case45:
  nativeSwitch2Case46:
  nativeSwitch2Case47:
  nativeSwitch2Case48:
  nativeSwitch2Case49:
  nativeSwitch2Case50:
  nativeSwitch2Case51:
  nativeSwitch2Case52:
  nativeSwitch2Case53:
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
    fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x14))));
    fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
    goto nativeSwitch2End;
  nativeSwitch2Case54:
  nativeSwitch2Case55:
  nativeSwitch2Case56:
  nativeSwitch2Case57:
  nativeSwitch2Case58:
  nativeSwitch2Case59:
    goto nativeSwitch2End;
  nativeSwitch2Case60:
    uVar4 = (undefined4)(0xf0b);
LAB_00474285:
    CError_Internal(s_CPrec_c_0067dd1c, uVar4);
    goto nativeSwitch2End;
  nativeSwitch2Case61:
    iVar2 = (int)(*(int *)(pcVar8 + 0x10));
    uVar4 = (undefined4)(*(undefined4 *)(pcVar8 + 0x14));
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar7 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, uVar4, iVar2);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + iVar2);
    fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar7));
    goto nativeSwitch2End;
  nativeSwitch2Case62:
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
    fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x14))));
    fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x18))));
    fn_00478cc0((int)(uVar11 + 0x18), (uint)(uVar4));
    goto nativeSwitch2End;
  nativeSwitch2Case63:
  nativeSwitch2Case64:
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
    fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(pcVar8 + 0x18))));
    fn_00478cc0((int)(uVar11 + 0x18), (uint)(uVar4));
    piVar9 = (int *)(*(int **)(pcVar8 + 0x14));
    if (piVar9 != (int *)0x0) {
      uVar7 = (uint)(DAT_006daef6);
      uVar6 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        while (DAT_006daef6 = uVar7, uVar6 = uVar7, (uVar7 & 3) != 0) {
          AppendGListByte(&DAT_006daf1a, 0);
          DAT_006daef6 = (uint )(DAT_006daef6 + 1);
          uVar7 = (uint)(DAT_006daef6);
        }
      }
      while( true ) {
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, piVar9, 8);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + 8);
        uVar4 = (undefined4)(fn_00473510((char *)(piVar9[1])));
        fn_00478cc0((int)(uVar7 + 4), (uint)(uVar4));
        if (*piVar9 == 0) break;
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar3 = (uint)(DAT_006daef6);
        fn_00478cc0((int)(uVar7), (uint)(DAT_006daef6));
        piVar9 = (int *)((int *)*piVar9);
        uVar7 = (uint)(uVar3);
      }
      fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar6));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case65:
  nativeSwitch2Case66:
  nativeSwitch2Case67:
  nativeSwitch2Case68:
    if ((*(uint *)(pcVar8 + 8) & 0x400) == 0) {
      uVar4 = (undefined4)(fn_004721e0((uint)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case69:
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
    fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x14))));
    fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
    goto nativeSwitch2End;
  nativeSwitch2Case70:
    iVar2 = (int)(*(int *)(pcVar8 + 0x10));
    if (iVar2 != 0) {
      iVar5 = (int)(-1);
      pcVar10 = (char *)(*(char **)(pcVar8 + 0x10));
      do {
        if (iVar5 == 0) break;
        iVar5 = (int)(iVar5 - 1);
        cVar1 = (char)(*pcVar10);
        pcVar10 = (char *)(pcVar10 + 1);
      } while (cVar1 != '\0');
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar7 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, iVar2, -iVar5 + -1);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + -iVar5 + -1);
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar7));
    }
    iVar2 = (int)(*(int *)(pcVar8 + 0x14));
    if ((iVar2 != 0) && (iVar2 != 0)) {
      uVar4 = (undefined4)(fn_004745c0((int *)(iVar2)));
      fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
    }
    iVar2 = (int)(*(int *)(pcVar8 + 0x18));
    if ((iVar2 != 0) && (iVar2 != 0)) {
      uVar4 = (undefined4)(fn_004745c0((int *)(iVar2)));
      fn_00478cc0((int)(uVar11 + 0x18), (uint)(uVar4));
    }
    iVar2 = (int)(*(int *)(pcVar8 + 0x1c));
    if ((iVar2 != 0) && (iVar2 != 0)) {
      uVar4 = (undefined4)(fn_00474430((int *)(iVar2)));
      fn_00478cc0((int)(uVar11 + 0x1c), (uint)(uVar4));
    }
    if ((*(int *)(pcVar8 + 0x22) != 0) && (*(int *)(pcVar8 + 0x22) != 0)) {
      uVar4 = (undefined4)(fn_00478080((undefined4 *)(*(undefined4 *)(pcVar8 + 0x22))));
      fn_00478cc0((int)(uVar11 + 0x22), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case71:
    iVar2 = (int)(*(int *)(pcVar8 + 0x10));
    if ((iVar2 != 0) && (iVar2 != 0)) {
      uVar4 = (undefined4)(fn_00473510((char *)(iVar2)));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case72:
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
    fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x14))));
    fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
    goto nativeSwitch2End;
  nativeSwitch2Case73:
    uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(pcVar8 + 0x10))));
    fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    goto nativeSwitch2End;
  nativeSwitch2Case74:
  nativeSwitch2Case75:
    if (*(int *)(pcVar8 + 0x10) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    }
    if (*(int *)(pcVar8 + 0x14) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x14))));
      fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
    }
    if (*(int *)(pcVar8 + 0x18) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x18))));
      fn_00478cc0((int)(uVar11 + 0x18), (uint)(uVar4));
    }
    if (*(int *)(pcVar8 + 0x1c) != 0) {
      uVar4 = (undefined4)(fn_004721e0((uint)(*(int *)(pcVar8 + 0x1c))));
      fn_00478cc0((int)(uVar11 + 0x1c), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case76:
    if (*(int *)(pcVar8 + 0x10) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    }
    if (*(int *)(pcVar8 + 0x14) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x14))));
      fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
    }
    if (*(int *)(pcVar8 + 0x18) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x18))));
      fn_00478cc0((int)(uVar11 + 0x18), (uint)(uVar4));
    }
    if (*(int *)(pcVar8 + 0x1c) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x1c))));
      fn_00478cc0((int)(uVar11 + 0x1c), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case77:
    fn_00474dc0((int *)(pcVar8 + 0x10), (int)(uVar11 + 0x10));
    goto nativeSwitch2End;
  nativeSwitch2Case78:
    { uint nativeSwitch1Value=(uint)(pcVar8[0x2c]);
if(nativeSwitch1Value==(uint)('\0')) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)('\x01')) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)('\x02')) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)('\x03')) goto nativeSwitch1Case3;
if(nativeSwitch1Value==(uint)('\x04')) goto nativeSwitch1Case4;
if(nativeSwitch1Value==(uint)('\x05')) goto nativeSwitch1Case5;
if(nativeSwitch1Value==(uint)('\x06')) goto nativeSwitch1Case6;
if(nativeSwitch1Value==(uint)('\a')) goto nativeSwitch1Case7;
if(nativeSwitch1Value==(uint)('\b')) goto nativeSwitch1Case8;
if(nativeSwitch1Value==(uint)('\x19')) goto nativeSwitch1Case9;
if(nativeSwitch1Value==(uint)('\t')) goto nativeSwitch1Case10;
if(nativeSwitch1Value==(uint)('\n')) goto nativeSwitch1Case11;
if(nativeSwitch1Value==(uint)('\v')) goto nativeSwitch1Case12;
if(nativeSwitch1Value==(uint)('\x15')) goto nativeSwitch1Case13;
if(nativeSwitch1Value==(uint)('\f')) goto nativeSwitch1Case14;
if(nativeSwitch1Value==(uint)('\r')) goto nativeSwitch1Case15;
if(nativeSwitch1Value==(uint)('\x0e')) goto nativeSwitch1Case16;
if(nativeSwitch1Value==(uint)('\x0f')) goto nativeSwitch1Case17;
if(nativeSwitch1Value==(uint)('\x10')) goto nativeSwitch1Case18;
if(nativeSwitch1Value==(uint)('\x11')) goto nativeSwitch1Case19;
if(nativeSwitch1Value==(uint)('\x12')) goto nativeSwitch1Case20;
if(nativeSwitch1Value==(uint)('\x13')) goto nativeSwitch1Case21;
if(nativeSwitch1Value==(uint)('\x14')) goto nativeSwitch1Case22;
if(nativeSwitch1Value==(uint)('\x16')) goto nativeSwitch1Case23;
if(nativeSwitch1Value==(uint)('\x17')) goto nativeSwitch1Case24;
if(nativeSwitch1Value==(uint)('\x18')) goto nativeSwitch1Case25;
if(nativeSwitch1Value==(uint)('\x1a')) goto nativeSwitch1Case26;
if(nativeSwitch1Value==(uint)('\x1b')) goto nativeSwitch1Case27;
goto nativeSwitch1Case28;

    nativeSwitch1Case0:
      goto nativeSwitch1End;
    nativeSwitch1Case1:
      if (pcVar8[0x19] == '\0') {
        uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(pcVar8 + 0x10))));
        fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      }
      else {
        uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
        fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case2:
      piVar9 = (int *)(*(int **)(pcVar8 + 0x10));
      if (piVar9 != (int *)0x0) {
        uVar7 = (uint)(DAT_006daef6);
        uVar6 = (uint)(DAT_006daef6);
        if (DAT_006daee5 != '\0') {
          while (DAT_006daef6 = uVar7, uVar6 = uVar7, (uVar7 & 3) != 0) {
            AppendGListByte(&DAT_006daf1a, 0);
            DAT_006daef6 = (uint )(DAT_006daef6 + 1);
            uVar7 = (uint)(DAT_006daef6);
          }
        }
        while( true ) {
          if (DAT_006daee5 != '\0') {
            CompilerTools_AppendGListData(&DAT_006daf1a, piVar9, 8);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 8);
          uVar4 = (undefined4)(fn_00473510((char *)(piVar9[1])));
          fn_00478cc0((int)(uVar7 + 4), (uint)(uVar4));
          if (*piVar9 == 0) break;
          if (DAT_006daee5 != '\0') {
            for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
              AppendGListByte(&DAT_006daf1a, 0);
            }
          }
          uVar3 = (uint)(DAT_006daef6);
          fn_00478cc0((int)(uVar7), (uint)(DAT_006daef6));
          piVar9 = (int *)((int *)*piVar9);
          uVar7 = (uint)(uVar3);
        }
        fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar6));
      }
      uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(pcVar8 + 0x14))));
      fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case3:
      iVar2 = (int)(*(int *)(pcVar8 + 0x14));
      *(undefined4 *)(iVar2 + 4) = 1;
      fn_00478bd0((int)(uVar11 + 0x14), (uint)(iVar2));
      uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case4:
      uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      iVar2 = (int)(*(int *)(pcVar8 + 0x14));
      if (iVar2 != 0) {
        *(undefined4 *)(iVar2 + 4) = 1;
        fn_00478bd0((int)(uVar11 + 0x14), (uint)(iVar2));
      }
      if (*(int *)(pcVar8 + 0x18) != 0) {
        uVar4 = (undefined4)(fn_00476dd0((int *)(*(int *)(pcVar8 + 0x18))));
        fn_00478cc0((int)(uVar11 + 0x18), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case5:
      fn_00474dc0((int *)(pcVar8 + 0x10), (int)(uVar11 + 0x10));
      goto nativeSwitch1End;
    nativeSwitch1Case6:
      uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case7:
      uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      piVar9 = (int *)(*(int **)(pcVar8 + 0x14));
      if (piVar9 != (int *)0x0) {
        uVar6 = (uint)(DAT_006daef6);
        uVar7 = (uint)(DAT_006daef6);
        if (DAT_006daee5 != '\0') {
          while (DAT_006daef6 = uVar6, uVar7 = uVar6, (uVar6 & 3) != 0) {
            AppendGListByte(&DAT_006daf1a, 0);
            DAT_006daef6 = (uint )(DAT_006daef6 + 1);
            uVar6 = (uint)(DAT_006daef6);
          }
        }
        while( true ) {
          if (DAT_006daee5 != '\0') {
            CompilerTools_AppendGListData(&DAT_006daf1a, piVar9, 8);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 8);
          uVar4 = (undefined4)(fn_00473510((char *)(piVar9[1])));
          fn_00478cc0((int)(uVar6 + 4), (uint)(uVar4));
          if (*piVar9 == 0) break;
          if (DAT_006daee5 != '\0') {
            for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
              AppendGListByte(&DAT_006daf1a, 0);
            }
          }
          uVar3 = (uint)(DAT_006daef6);
          fn_00478cc0((int)(uVar6), (uint)(DAT_006daef6));
          piVar9 = (int *)((int *)*piVar9);
          uVar6 = (uint)(uVar3);
        }
        fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar7));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case8:
    nativeSwitch1Case9:
      uVar4 = (undefined4)(fn_004721e0((uint)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case10:
    nativeSwitch1Case11:
    nativeSwitch1Case12:
    nativeSwitch1Case13:
      uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case14:
      uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      if (*(int *)(pcVar8 + 0x18) != 0) {
        uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x18))));
        fn_00478cc0((int)(uVar11 + 0x18), (uint)(uVar4));
      }
      piVar9 = (int *)(*(int **)(pcVar8 + 0x1c));
      if (piVar9 != (int *)0x0) {
        uVar7 = (uint)(DAT_006daef6);
        uVar6 = (uint)(DAT_006daef6);
        if (DAT_006daee5 != '\0') {
          while (DAT_006daef6 = uVar7, uVar6 = uVar7, (uVar7 & 3) != 0) {
            AppendGListByte(&DAT_006daf1a, 0);
            DAT_006daef6 = (uint )(DAT_006daef6 + 1);
            uVar7 = (uint)(DAT_006daef6);
          }
        }
        while( true ) {
          if (DAT_006daee5 != '\0') {
            CompilerTools_AppendGListData(&DAT_006daf1a, piVar9, 8);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 8);
          uVar4 = (undefined4)(fn_00473510((char *)(piVar9[1])));
          fn_00478cc0((int)(uVar7 + 4), (uint)(uVar4));
          if (*piVar9 == 0) break;
          if (DAT_006daee5 != '\0') {
            for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
              AppendGListByte(&DAT_006daf1a, 0);
            }
          }
          uVar3 = (uint)(DAT_006daef6);
          fn_00478cc0((int)(uVar7), (uint)(DAT_006daef6));
          piVar9 = (int *)((int *)*piVar9);
          uVar7 = (uint)(uVar3);
        }
        fn_00478cc0((int)(uVar11 + 0x1c), (uint)(uVar6));
      }
      piVar9 = (int *)(*(int **)(pcVar8 + 0x20));
      if (piVar9 != (int *)0x0) {
        uVar7 = (uint)(DAT_006daef6);
        uVar6 = (uint)(DAT_006daef6);
        if (DAT_006daee5 != '\0') {
          while (DAT_006daef6 = uVar7, uVar6 = uVar7, (uVar7 & 3) != 0) {
            AppendGListByte(&DAT_006daf1a, 0);
            DAT_006daef6 = (uint )(DAT_006daef6 + 1);
            uVar7 = (uint)(DAT_006daef6);
          }
        }
        while( true ) {
          if (DAT_006daee5 != '\0') {
            CompilerTools_AppendGListData(&DAT_006daf1a, piVar9, 8);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 8);
          uVar4 = (undefined4)(fn_00473510((char *)(piVar9[1])));
          fn_00478cc0((int)(uVar7 + 4), (uint)(uVar4));
          if (*piVar9 == 0) break;
          if (DAT_006daee5 != '\0') {
            for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
              AppendGListByte(&DAT_006daf1a, 0);
            }
          }
          uVar3 = (uint)(DAT_006daef6);
          fn_00478cc0((int)(uVar7), (uint)(DAT_006daef6));
          piVar9 = (int *)((int *)*piVar9);
          uVar7 = (uint)(uVar3);
        }
        fn_00478cc0((int)(uVar11 + 0x20), (uint)(uVar6));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case15:
      uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case16:
      uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x14))));
      fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case17:
    nativeSwitch1Case18:
    nativeSwitch1Case19:
    nativeSwitch1Case20:
    nativeSwitch1Case21:
      if (*(int *)(pcVar8 + 0x10) != 0) {
        uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(pcVar8 + 0x10))));
        fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      }
      if (*(int *)(pcVar8 + 0x14) != 0) {
        uVar4 = (undefined4)(fn_00475030((char *)(*(int *)(pcVar8 + 0x14))));
        fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case22:
      uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      if (*(int *)(pcVar8 + 0x14) != 0) {
        uVar4 = (undefined4)(fn_00474e70((int *)(*(int *)(pcVar8 + 0x14))));
        fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case23:
      uVar4 = (undefined4)(fn_004721e0((uint)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      uVar4 = (undefined4)(fn_004721e0((uint)(*(undefined4 *)(pcVar8 + 0x14))));
      fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case24:
    nativeSwitch1Case25:
      uVar4 = (undefined4)(fn_004721e0((uint)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      if (*(int *)(pcVar8 + 0x14) != 0) {
        uVar4 = (undefined4)(fn_00474790((int *)(*(int *)(pcVar8 + 0x14))));
        fn_00478cc0((int)(uVar11 + 0x14), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case26:
      uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      iVar2 = (int)(*(int *)(pcVar8 + 0x14));
      *(undefined4 *)(iVar2 + 4) = 1;
      fn_00478bd0((int)(uVar11 + 0x14), (uint)(iVar2));
      goto nativeSwitch1End;
    nativeSwitch1Case27:
      uVar4 = (undefined4)(fn_00474e70((int *)(*(undefined4 *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
      goto nativeSwitch1End;
    nativeSwitch1Case28:
      uVar4 = (undefined4)(0xf05);
      goto LAB_00474285;

nativeSwitch1End:;
}
    goto nativeSwitch2End;
  nativeSwitch2Case79:
    if (*(int *)(pcVar8 + 0x10) != 0) {
      uVar4 = (undefined4)(fn_00474b70((int *)(*(int *)(pcVar8 + 0x10))));
      fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar4));
    }
    goto nativeSwitch2End;
  nativeSwitch2Case80:
    iVar2 = (int)(*(int *)(pcVar8 + 0x14));
    uVar4 = (undefined4)(*(undefined4 *)(pcVar8 + 0x10));
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar7 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, uVar4, iVar2);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + iVar2);
    fn_00478cc0((int)(uVar11 + 0x10), (uint)(uVar7));
    piVar9 = (int *)(*(int **)(pcVar8 + 0x18));
    if (piVar9 != (int *)0x0) {
      uVar6 = (uint)(DAT_006daef6);
      uVar7 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        while (DAT_006daef6 = uVar6, uVar7 = uVar6, (uVar6 & 3) != 0) {
          AppendGListByte(&DAT_006daf1a, 0);
          DAT_006daef6 = (uint )(DAT_006daef6 + 1);
          uVar6 = (uint)(DAT_006daef6);
        }
      }
      while( true ) {
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, piVar9, 0x10);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + 0x10);
        uVar4 = (undefined4)(fn_004721e0((uint)(piVar9[1])));
        fn_00478cc0((int)(uVar6 + 4), (uint)(uVar4));
        if (*piVar9 == 0) break;
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar3 = (uint)(DAT_006daef6);
        fn_00478cc0((int)(uVar6), (uint)(DAT_006daef6));
        piVar9 = (int *)((int *)*piVar9);
        uVar6 = (uint)(uVar3);
      }
      fn_00478cc0((int)(uVar11 + 0x18), (uint)(uVar7));
    }

nativeSwitch2End:;
}
  return uVar12;
}

uint fn_00474430(int *param_1)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  uVar7 = (uint)(DAT_006daef6);
  uVar3 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar7, uVar3 = uVar7, (uVar7 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar7 = (uint)(DAT_006daef6);
    }
  }
  do {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0xc);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0xc);
    iVar2 = (int)(param_1[1]);
    if (iVar2 != 0) {
      iVar6 = (int)(-1);
      pcVar8 = (char *)((char *)param_1[1]);
      do {
        if (iVar6 == 0) break;
        iVar6 = (int)(iVar6 - 1);
        cVar1 = (char)(*pcVar8);
        pcVar8 = (char *)(pcVar8 + 1);
      } while (cVar1 != '\0');
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar4 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, iVar2, -iVar6 + -1);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + -iVar6 + -1);
      fn_00478cc0((int)(uVar7 + 4), (uint)(uVar4));
    }
    if ((param_1[2] != 0) && (param_1[2] != 0)) {
      uVar5 = (undefined4)(fn_00478080((undefined4 *)(param_1[2])));
      fn_00478cc0((int)(uVar7 + 8), (uint)(uVar5));
    }
    if (*param_1 == 0) {
      return uVar3;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar4 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar7), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar7 = (uint)(uVar4);
  } while( true );
}

uint fn_004745c0(int *param_1)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  uVar7 = (uint)(DAT_006daef6);
  uVar3 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar7, uVar3 = uVar7, (uVar7 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar7 = (uint)(DAT_006daef6);
    }
  }
  do {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x14);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x14);
    iVar2 = (int)(param_1[1]);
    if (iVar2 != 0) {
      iVar6 = (int)(-1);
      pcVar8 = (char *)((char *)param_1[1]);
      do {
        if (iVar6 == 0) break;
        iVar6 = (int)(iVar6 - 1);
        cVar1 = (char)(*pcVar8);
        pcVar8 = (char *)(pcVar8 + 1);
      } while (cVar1 != '\0');
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar4 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, iVar2, -iVar6 + -1);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + -iVar6 + -1);
      fn_00478cc0((int)(uVar7 + 4), (uint)(uVar4));
    }
    iVar2 = (int)(param_1[2]);
    if ((iVar2 != 0) && (iVar2 != 0)) {
      uVar5 = (undefined4)(fn_00473510((char *)(iVar2)));
      fn_00478cc0((int)(uVar7 + 8), (uint)(uVar5));
    }
    iVar2 = (int)(param_1[3]);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 4) = 1;
      fn_00478bd0((int)(uVar7 + 0xc), (uint)(iVar2));
    }
    if ((param_1[4] != 0) && (param_1[4] != 0)) {
      uVar5 = (undefined4)(fn_00478080((undefined4 *)(param_1[4])));
      fn_00478cc0((int)(uVar7 + 0x10), (uint)(uVar5));
    }
    if (*param_1 == 0) {
      return uVar3;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar4 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar7), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar7 = (uint)(uVar4);
  } while( true );
}

uint fn_00474790(int *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 6);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 6);
  { uint nativeSwitch1Value=(uint)((char)param_1[1]);
if(nativeSwitch1Value==(uint)('\0')) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)('\x01')) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)('\x02')) goto nativeSwitch1Case2;
goto nativeSwitch1Case3;

  nativeSwitch1Case0:
    if (*param_1 != 0) {
      uVar3 = (undefined4)(fn_00473510((char *)(*param_1)));
      fn_00478cc0((int)(uVar1), (uint)(uVar3));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case1:
    param_1 = (int *)((int *)*param_1);
    if (param_1 != (int *)0x0) {
      uVar4 = (uint)(DAT_006daef6);
      uVar5 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        while (DAT_006daef6 = uVar4, uVar5 = uVar4, (uVar4 & 3) != 0) {
          AppendGListByte(&DAT_006daf1a, 0);
          DAT_006daef6 = (uint )(DAT_006daef6 + 1);
          uVar4 = (uint)(DAT_006daef6);
        }
      }
      while( true ) {
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 8);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + 8);
        uVar3 = (undefined4)(fn_00473510((char *)(param_1[1])));
        fn_00478cc0((int)(uVar4 + 4), (uint)(uVar3));
        if (*param_1 == 0) break;
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar2 = (uint)(DAT_006daef6);
        fn_00478cc0((int)(uVar4), (uint)(DAT_006daef6));
        param_1 = (int *)((int *)*param_1);
        uVar4 = (uint)(uVar2);
      }
      fn_00478cc0((int)(uVar1), (uint)(uVar5));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case2:
    if (*param_1 != 0) {
      uVar3 = (undefined4)(fn_00474960((int *)(*param_1)));
      fn_00478cc0((int)(uVar1), (uint)(uVar3));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case3:
    CError_Internal(s_CPrec_c_0067dd1c, 0xd57);

nativeSwitch1End:;
}
  return uVar1;
}

uint fn_00474960(int *param_1)
{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uVar6 = (uint)(DAT_006daef6);
  uVar3 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar6, uVar3 = uVar6, (uVar6 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar6 = (uint)(DAT_006daef6);
    }
  }
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x1c);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x1c);
    if (param_1[4] != 0) {
      uVar5 = (undefined4)(fn_004781b0((int *)(param_1[4])));
      fn_00478cc0((int)(uVar6 + 0x10), (uint)(uVar5));
    }
    if (param_1[1] != 0) {
      uVar5 = (undefined4)(fn_00474960((int *)(param_1[1])));
      fn_00478cc0((int)(uVar6 + 4), (uint)(uVar5));
    }
    if (param_1[2] != 0) {
      uVar5 = (undefined4)(fn_00473510((char *)(param_1[2])));
      fn_00478cc0((int)(uVar6 + 8), (uint)(uVar5));
    }
    piVar1 = (int *)((int *)param_1[3]);
    if (piVar1 != (int *)0x0) {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar4 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, piVar1, 0xc);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 0xc);
      if (*piVar1 != 0) {
        uVar5 = (undefined4)(fn_00473510((char *)(*piVar1)));
        fn_00478cc0((int)(uVar4), (uint)(uVar5));
      }
      if (piVar1[1] != 0) {
        uVar5 = (undefined4)(fn_00473510((char *)(piVar1[1])));
        fn_00478cc0((int)(uVar4 + 4), (uint)(uVar5));
      }
      iVar2 = (int)(piVar1[2]);
      if (iVar2 != 0) {
        *(undefined4 *)(iVar2 + 4) = 1;
        fn_00478bd0((int)(uVar4 + 8), (uint)(iVar2));
      }
      fn_00478cc0((int)(uVar6 + 0xc), (uint)(uVar4));
    }
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar4 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar6), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar6 = (uint)(uVar4);
  }
  return uVar3;
}

uint fn_00474b70(int *param_1)
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uVar5 = (uint)(DAT_006daef6);
  uVar6 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    for (; uVar5 = DAT_006daef6, uVar6 = DAT_006daef6, (DAT_006daef6 & 3) != 0;
        DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  do {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0xe);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0xe);
    if ((char)param_1[3] == '\0') {
      if (param_1[2] != 0) {
        uVar2 = (undefined4)(fn_00475030((char *)(param_1[2])));
        goto LAB_00474c0a;
      }
    }
    else if (param_1[2] != 0) {
      uVar2 = (undefined4)(fn_004728b0((uint)(param_1[2])));
LAB_00474c0a:
      fn_00478cc0((int)(uVar5 + 8), (uint)(uVar2));
    }
    if (*(char *)((int)param_1 + 0xd) == '\0') {
      piVar4 = (int *)((int *)param_1[1]);
      if ((piVar4 != (int *)0x0) && (piVar4 != (int *)0x0)) {
        uVar3 = (uint)(DAT_006daef6);
        uVar7 = (uint)(DAT_006daef6);
        if (DAT_006daee5 != '\0') {
          while (DAT_006daef6 = uVar3, uVar7 = uVar3, (uVar3 & 3) != 0) {
            AppendGListByte(&DAT_006daf1a, 0);
            DAT_006daef6 = (uint )(DAT_006daef6 + 1);
            uVar3 = (uint)(DAT_006daef6);
          }
        }
        while( true ) {
          if (DAT_006daee5 != '\0') {
            CompilerTools_AppendGListData(&DAT_006daf1a, piVar4, 8);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 8);
          uVar2 = (undefined4)(fn_00473510((char *)(piVar4[1])));
          fn_00478cc0((int)(uVar3 + 4), (uint)(uVar2));
          if (*piVar4 == 0) break;
          if (DAT_006daee5 != '\0') {
            for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
              AppendGListByte(&DAT_006daf1a, 0);
            }
          }
          uVar1 = (uint)(DAT_006daef6);
          fn_00478cc0((int)(uVar3), (uint)(DAT_006daef6));
          piVar4 = (int *)((int *)*piVar4);
          uVar3 = (uint)(uVar1);
        }
        fn_00478cc0((int)(uVar5 + 4), (uint)(uVar7));
      }
    }
    else if (param_1[1] != 0) {
      uVar2 = (undefined4)(fn_00473510((char *)(param_1[1])));
      fn_00478cc0((int)(uVar5 + 4), (uint)(uVar2));
    }
    if (*param_1 == 0) {
      return uVar6;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar3 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar5), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar5 = (uint)(uVar3);
  } while( true );
}

void fn_00474dc0(int *param_1, int param_2)
{
  int iVar1;
  undefined4 uVar2;
  if (param_1[1] != 0) {
    uVar2 = (undefined4)(fn_00475390((char *)(param_1[1])));
    fn_00478cc0((int)(param_2 + 4), (uint)(uVar2));
  }
  if (param_1[2] != 0) {
    uVar2 = (undefined4)(fn_00475390((char *)(param_1[2])));
    fn_00478cc0((int)(param_2 + 8), (uint)(uVar2));
  }
  if (param_1[5] != 0) {
    uVar2 = (undefined4)(fn_00473510((char *)(param_1[5])));
    fn_00478cc0((int)(param_2 + 0x14), (uint)(uVar2));
  }
  if (param_1[3] != 0) {
    uVar2 = (undefined4)(fn_00476dd0((int *)(param_1[3])));
    fn_00478cc0((int)(param_2 + 0xc), (uint)(uVar2));
  }
  iVar1 = (int)(param_1[4]);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 4) = 1;
    fn_00478bd0((int)(param_2 + 0x10), (uint)(iVar1));
  }
  if (*param_1 != 0) {
    uVar2 = (undefined4)(fn_00471db0((uint *)(*param_1)));
    fn_00478cc0((int)(param_2), (uint)(uVar2));
  }
  return;
}

uint fn_00474e70(int *param_1)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uVar5 = (uint)(DAT_006daef6);
  uVar2 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar5, uVar2 = uVar5, (uVar5 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar5 = (uint)(DAT_006daef6);
    }
  }
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0xe);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0xe);
    { uint nativeSwitch1Value=(uint)((char)param_1[3]);
if(nativeSwitch1Value==(uint)('\0')) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)('\x02')) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)('\x04')) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)('\x01')) goto nativeSwitch1Case3;
if(nativeSwitch1Value==(uint)('\x03')) goto nativeSwitch1Case4;
if(nativeSwitch1Value==(uint)('\x05')) goto nativeSwitch1Case5;
if(nativeSwitch1Value==(uint)('\x06')) goto nativeSwitch1Case6;
goto nativeSwitch1Case7;

    nativeSwitch1Case0:
    nativeSwitch1Case1:
    nativeSwitch1Case2:
      iVar1 = (int)(param_1[1]);
      *(undefined4 *)(iVar1 + 4) = 1;
      fn_00478bd0((int)(uVar5 + 4), (uint)(iVar1));
      goto nativeSwitch1End;
    nativeSwitch1Case3:
      if (param_1[1] != 0) {
        uVar4 = (undefined4)(fn_00475030((char *)(param_1[1])));
        fn_00478cc0((int)(uVar5 + 4), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case4:
      if (param_1[1] != 0) {
        uVar4 = (undefined4)(fn_00471720((int *)(param_1[1])));
        fn_00478cc0((int)(uVar5 + 4), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case5:
      iVar1 = (int)(param_1[1]);
      *(undefined4 *)(iVar1 + 4) = 1;
      fn_00478bd0((int)(uVar5 + 4), (uint)(iVar1));
      if (param_1[2] != 0) {
        uVar4 = (undefined4)(fn_00476dd0((int *)(param_1[2])));
        fn_00478cc0((int)(uVar5 + 8), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case6:
      iVar1 = (int)(param_1[1]);
      *(undefined4 *)(iVar1 + 4) = 1;
      fn_00478bd0((int)(uVar5 + 4), (uint)(iVar1));
      if (param_1[2] != 0) {
        uVar4 = (undefined4)(fn_00475030((char *)(param_1[2])));
        fn_00478cc0((int)(uVar5 + 8), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case7:
      CError_Internal(s_CPrec_c_0067dd1c, 0xc8e);

nativeSwitch1End:;
}
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar3 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar5), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar5 = (uint)(uVar3);
  }
  return uVar2;
}

uint fn_00475030(char *param_1)
{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  if (*param_1 == '\x06') {
    uVar2 = (uint)(fn_00475390((char *)(param_1)));
    return uVar2;
  }
  for (puVar1 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((uint)(param_1 +
                        ((uint)param_1 >> 0x18) +
                        ((uint)param_1 >> 0x10 & 0xff) +
                        ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)) & 0x3fff) * 4);
      puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    if ((char *)puVar1[1] == param_1) goto LAB_00475081;
  }
  puVar1 = (undefined4 *)((undefined4 *)0x0);
LAB_00475081:
  if (puVar1 != (undefined4 *)0x0) {
    return puVar1[2];
  }
  { uint nativeSwitch1Value=(uint)(*param_1);
if(nativeSwitch1Value==(uint)('\x04')) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)('\x05')) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)('\a')) goto nativeSwitch1Case3;
if(nativeSwitch1Value==(uint)('\b')) goto nativeSwitch1Case4;
if(nativeSwitch1Value==(uint)('\n')) goto nativeSwitch1Case5;
if(nativeSwitch1Value==(uint)('\v')) goto nativeSwitch1Case6;
if(nativeSwitch1Value==(uint)('\f')) goto nativeSwitch1Case7;
if(nativeSwitch1Value==(uint)('\r')) goto nativeSwitch1Case8;
goto nativeSwitch1Case0;

  nativeSwitch1Case0:
    CError_Internal(s_CPrec_c_0067dd1c, 0xbd0);
    return 0;
  nativeSwitch1Case1:
    uVar2 = (uint)(fn_00477d80((uint)(param_1)));
    return uVar2;
  nativeSwitch1Case2:
    uVar2 = (uint)(fn_00477bb0((uint)(param_1)));
    return uVar2;
  nativeSwitch1Case3:
    uVar2 = (uint)(fn_004776f0((uint)(param_1)));
    return uVar2;
  nativeSwitch1Case4:
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    puVar4 = (undefined4 *)((undefined4 *)
             (((uint)(param_1 +
                     ((uint)param_1 >> 0x18) +
                     ((uint)param_1 >> 0x10 & 0xff) +
                     ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)) & 0x3fff) * 4 +
             DAT_006daf12));
    puVar1 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar1[1] = (uint)(param_1);
    puVar1[2] = (uint)(uVar2);
    *puVar1 = (uint)(*puVar4);
    *puVar4 = (uint)(puVar1);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0xc);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0xc);
    uVar3 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 6))));
    fn_00478cc0((int)(uVar2 + 6), (uint)(uVar3));
    return uVar2;
  nativeSwitch1Case5:
    uVar2 = (uint)(fn_00477490((uint)(param_1)));
    return uVar2;
  nativeSwitch1Case6:
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    puVar4 = (undefined4 *)((undefined4 *)
             (((uint)(param_1 +
                     ((uint)param_1 >> 0x18) +
                     ((uint)param_1 >> 0x10 & 0xff) +
                     ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)) & 0x3fff) * 4 +
             DAT_006daf12));
    puVar1 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar1[1] = (uint)(param_1);
    puVar1[2] = (uint)(uVar2);
    *puVar1 = (uint)(*puVar4);
    *puVar4 = (uint)(puVar1);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x12);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x12);
    uVar3 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 6))));
    fn_00478cc0((int)(uVar2 + 6), (uint)(uVar3));
    uVar3 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 10))));
    fn_00478cc0((int)(uVar2 + 10), (uint)(uVar3));
    return uVar2;
  nativeSwitch1Case7:
    uVar2 = (uint)(fn_00477eb0((uint)(param_1)));
    return uVar2;
  nativeSwitch1Case8:
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    puVar4 = (undefined4 *)((undefined4 *)
             (((uint)(param_1 +
                     ((uint)param_1 >> 0x18) +
                     ((uint)param_1 >> 0x10 & 0xff) +
                     ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)) & 0x3fff) * 4 +
             DAT_006daf12));
    puVar1 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar1[1] = (uint)(param_1);
    puVar1[2] = (uint)(uVar2);
    *puVar1 = (uint)(*puVar4);
    *puVar4 = (uint)(puVar1);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x14);
    }

nativeSwitch1End:;
}
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x14);
  uVar3 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 6))));
  fn_00478cc0((int)(uVar2 + 6), (uint)(uVar3));
  return uVar2;
}

uint fn_00475390(char *param_1)
{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  if (*param_1 != '\x06') {
    CError_Internal(s_CPrec_c_0067dd1c, 0xb9d);
  }
  if ((*(uint *)(param_1 + 0x22) & 0x100) != 0) {
    uVar3 = (undefined4)(FUN_0053edb0(param_1));
    uVar2 = (uint)(fn_004755d0((uint)(uVar3)));
    return uVar2;
  }
  if ((*(uint *)(param_1 + 0x22) & 0x800) != 0) {
    uVar3 = (undefined4)(FUN_0053ed70(param_1));
    uVar2 = (uint)(fn_00475960((uint)(uVar3)));
    return uVar2;
  }
  for (puVar1 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((uint)(param_1 +
                        ((uint)param_1 >> 0x18) +
                        ((uint)param_1 >> 0x10 & 0xff) +
                        ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)) & 0x3fff) * 4);
      puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    if ((char *)puVar1[1] == param_1) goto LAB_004753fd;
  }
  puVar1 = (undefined4 *)((undefined4 *)0x0);
LAB_004753fd:
  if (puVar1 == (undefined4 *)0x0) {
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    puVar4 = (undefined4 *)((undefined4 *)
             (((uint)(param_1 +
                     ((uint)param_1 >> 0x18) +
                     ((uint)param_1 >> 0x10 & 0xff) +
                     ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)) & 0x3fff) * 4 +
             DAT_006daf12));
    puVar1 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar1[1] = (uint)(param_1);
    puVar1[2] = (uint)(uVar2);
    *puVar1 = (uint)(*puVar4);
    *puVar4 = (uint)(puVar1);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x30);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x30);
    if (*(int *)(param_1 + 6) != 0) {
      uVar3 = (undefined4)(fn_00471720((int *)(*(int *)(param_1 + 6))));
      fn_00478cc0((int)(uVar2 + 6), (uint)(uVar3));
    }
    if (*(int *)(param_1 + 10) != 0) {
      fn_00478bb0((undefined4)(uVar2 + 10), (int)(*(int *)(param_1 + 10)));
    }
    if (*(int *)(param_1 + 0xe) != 0) {
      uVar3 = (undefined4)(fn_004772b0((uint *)(*(int *)(param_1 + 0xe))));
      fn_00478cc0((int)(uVar2 + 0xe), (uint)(uVar3));
    }
    if (*(int *)(param_1 + 0x12) != 0) {
      uVar3 = (undefined4)(fn_004771c0((int *)(*(int *)(param_1 + 0x12))));
      fn_00478cc0((int)(uVar2 + 0x12), (uint)(uVar3));
    }
    if (*(int *)(param_1 + 0x16) != 0) {
      uVar3 = (undefined4)(fn_004728b0((uint)(*(int *)(param_1 + 0x16))));
      fn_00478cc0((int)(uVar2 + 0x16), (uint)(uVar3));
    }
    if (*(int *)(param_1 + 0x1a) != 0) {
      uVar3 = (undefined4)(fn_00476f20((int *)(*(int *)(param_1 + 0x1a))));
      fn_00478cc0((int)(uVar2 + 0x1a), (uint)(uVar3));
    }
    if (*(int *)(param_1 + 0x1e) != 0) {
      uVar3 = (undefined4)(fn_004721e0((uint)(*(int *)(param_1 + 0x1e))));
      fn_00478cc0((int)(uVar2 + 0x1e), (uint)(uVar3));
    }
    return uVar2;
  }
  return puVar1[2];
}

uint fn_004755d0(uint param_1)
{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  for (puVar7 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
                  (param_1 >> 0x18) & 0x3fff) * 4); puVar7 != (undefined4 *)0x0;
      puVar7 = (undefined4 *)*puVar7) {
    if (puVar7[1] == param_1) goto LAB_0047561d;
  }
  puVar7 = (undefined4 *)((undefined4 *)0x0);
LAB_0047561d:
  if (puVar7 != (undefined4 *)0x0) {
    return puVar7[2];
  }
  uVar8 = (uint)(DAT_006daef6);
  uVar3 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar8, uVar3 = uVar8, (uVar8 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar8 = (uint)(DAT_006daef6);
    }
  }
  do {
    puVar6 = (undefined4 *)((undefined4 *)
             (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
               (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
    puVar7 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar7[1] = (uint)(param_1);
    puVar7[2] = (uint)(uVar8);
    *puVar7 = (uint)(*puVar6);
    *puVar6 = (uint)(puVar7);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x56);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x56);
    if (*(int *)(param_1 + 6) != 0) {
      uVar4 = (undefined4)(fn_00471720((int *)(*(int *)(param_1 + 6))));
      fn_00478cc0((int)(uVar8 + 6), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 10) != 0) {
      fn_00478bb0((undefined4)(uVar8 + 10), (int)(*(int *)(param_1 + 10)));
    }
    if (*(int *)(param_1 + 0xe) != 0) {
      uVar4 = (undefined4)(fn_004772b0((uint *)(*(int *)(param_1 + 0xe))));
      fn_00478cc0((int)(uVar8 + 0xe), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x12) != 0) {
      uVar4 = (undefined4)(fn_004771c0((int *)(*(int *)(param_1 + 0x12))));
      fn_00478cc0((int)(uVar8 + 0x12), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x16) != 0) {
      uVar4 = (undefined4)(fn_004728b0((uint)(*(int *)(param_1 + 0x16))));
      fn_00478cc0((int)(uVar8 + 0x16), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x1a) != 0) {
      uVar4 = (undefined4)(fn_00476f20((int *)(*(int *)(param_1 + 0x1a))));
      fn_00478cc0((int)(uVar8 + 0x1a), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x1e) != 0) {
      uVar4 = (undefined4)(fn_004721e0((uint)(*(int *)(param_1 + 0x1e))));
      fn_00478cc0((int)(uVar8 + 0x1e), (uint)(uVar4));
    }
    iVar5 = (int)(*(int *)(param_1 + 0x34));
    if (iVar5 != 0) {
      if (*(char *)(iVar5 + 0xc) == '\0') {
        uVar4 = (undefined4)(FUN_0053ee10(iVar5));
        iVar5 = (int)(fn_00475ca0((int *)(uVar4)));
      }
      else {
        uVar4 = (undefined4)(FUN_0053ee70(iVar5));
        iVar5 = (int)(fn_004755d0((uint)(uVar4)));
        iVar5 = (int)(iVar5 + 0x34);
      }
      fn_00478cc0((int)(uVar8 + 0x34), (uint)(iVar5));
    }
    piVar1 = (int *)(*(int **)(param_1 + 0x38));
    if (piVar1 != (int *)0x0) {
      if (*(char *)(*piVar1 + 0xc) == '\0') {
        uVar4 = (undefined4)(FUN_0053ede0(piVar1));
        iVar5 = (int)(fn_00476670((int *)(uVar4)));
      }
      else {
        uVar4 = (undefined4)(FUN_0053eea0(piVar1));
        iVar5 = (int)(fn_00475960((uint)(uVar4)));
        iVar5 = (int)(iVar5 + 0x34);
      }
      fn_00478cc0((int)(uVar8 + 0x38), (uint)(iVar5));
    }
    if (*(int *)(param_1 + 0x3c) != 0) {
      uVar4 = (undefined4)(fn_00476c20((int *)(*(int *)(param_1 + 0x3c))));
      fn_00478cc0((int)(uVar8 + 0x3c), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x42) != 0) {
      uVar4 = (undefined4)(fn_00475960((uint)(*(int *)(param_1 + 0x42))));
      fn_00478cc0((int)(uVar8 + 0x42), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x46) != 0) {
      uVar4 = (undefined4)(fn_004755d0((uint)(*(int *)(param_1 + 0x46))));
      fn_00478cc0((int)(uVar8 + 0x46), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x4a) != 0) {
      uVar4 = (undefined4)(fn_00476380((int *)(*(int *)(param_1 + 0x4a))));
      fn_00478cc0((int)(uVar8 + 0x4a), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x4e) != 0) {
      uVar4 = (undefined4)(fn_00476020((int *)(*(int *)(param_1 + 0x4e))));
      fn_00478cc0((int)(uVar8 + 0x4e), (uint)(uVar4));
    }
    uVar2 = (uint)(*(uint *)(param_1 + 0x30));
    if (uVar2 == 0) {
      return uVar3;
    }
    for (puVar7 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar2 & 0xff) + uVar2 + (uVar2 >> 8 & 0xff) + (uVar2 >> 0x10 & 0xff) +
                    (uVar2 >> 0x18) & 0x3fff) * 4); puVar7 != (undefined4 *)0x0;
        puVar7 = (undefined4 *)*puVar7) {
      if (puVar7[1] == uVar2) goto LAB_004758cd;
    }
    puVar7 = (undefined4 *)((undefined4 *)0x0);
LAB_004758cd:
    if (puVar7 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar8 + 0x30), (uint)(puVar7[2]));
      return uVar3;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar8 + 0x30), (uint)(DAT_006daef6));
    param_1 = (uint)(*(uint *)(param_1 + 0x30));
    uVar8 = (uint)(uVar2);
  } while( true );
}

uint fn_00475960(uint param_1)
{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  for (puVar7 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
                  (param_1 >> 0x18) & 0x3fff) * 4); puVar7 != (undefined4 *)0x0;
      puVar7 = (undefined4 *)*puVar7) {
    if (puVar7[1] == param_1) goto LAB_004759ad;
  }
  puVar7 = (undefined4 *)((undefined4 *)0x0);
LAB_004759ad:
  if (puVar7 != (undefined4 *)0x0) {
    return puVar7[2];
  }
  uVar8 = (uint)(DAT_006daef6);
  uVar3 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar8, uVar3 = uVar8, (uVar8 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar8 = (uint)(DAT_006daef6);
    }
  }
  do {
    puVar6 = (undefined4 *)((undefined4 *)
             (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
               (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
    puVar7 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar7[1] = (uint)(param_1);
    puVar7[2] = (uint)(uVar8);
    *puVar7 = (uint)(*puVar6);
    *puVar6 = (uint)(puVar7);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x48);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x48);
    if (*(int *)(param_1 + 6) != 0) {
      uVar4 = (undefined4)(fn_00471720((int *)(*(int *)(param_1 + 6))));
      fn_00478cc0((int)(uVar8 + 6), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 10) != 0) {
      fn_00478bb0((undefined4)(uVar8 + 10), (int)(*(int *)(param_1 + 10)));
    }
    if (*(int *)(param_1 + 0xe) != 0) {
      uVar4 = (undefined4)(fn_004772b0((uint *)(*(int *)(param_1 + 0xe))));
      fn_00478cc0((int)(uVar8 + 0xe), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x12) != 0) {
      uVar4 = (undefined4)(fn_004771c0((int *)(*(int *)(param_1 + 0x12))));
      fn_00478cc0((int)(uVar8 + 0x12), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x16) != 0) {
      uVar4 = (undefined4)(fn_004728b0((uint)(*(int *)(param_1 + 0x16))));
      fn_00478cc0((int)(uVar8 + 0x16), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x1a) != 0) {
      uVar4 = (undefined4)(fn_00476f20((int *)(*(int *)(param_1 + 0x1a))));
      fn_00478cc0((int)(uVar8 + 0x1a), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x1e) != 0) {
      uVar4 = (undefined4)(fn_004721e0((uint)(*(int *)(param_1 + 0x1e))));
      fn_00478cc0((int)(uVar8 + 0x1e), (uint)(uVar4));
    }
    iVar5 = (int)(*(int *)(param_1 + 0x34));
    if (iVar5 != 0) {
      if (*(char *)(iVar5 + 0xc) == '\0') {
        uVar4 = (undefined4)(FUN_0053ee10(iVar5));
        iVar5 = (int)(fn_00475ca0((int *)(uVar4)));
      }
      else {
        uVar4 = (undefined4)(FUN_0053ee70(iVar5));
        iVar5 = (int)(fn_004755d0((uint)(uVar4)));
        iVar5 = (int)(iVar5 + 0x34);
      }
      fn_00478cc0((int)(uVar8 + 0x34), (uint)(iVar5));
    }
    piVar1 = (int *)(*(int **)(param_1 + 0x38));
    if (piVar1 != (int *)0x0) {
      if (*(char *)(*piVar1 + 0xc) == '\0') {
        uVar4 = (undefined4)(FUN_0053ede0(piVar1));
        iVar5 = (int)(fn_00476670((int *)(uVar4)));
      }
      else {
        uVar4 = (undefined4)(FUN_0053eea0(piVar1));
        iVar5 = (int)(fn_00475960((uint)(uVar4)));
        iVar5 = (int)(iVar5 + 0x34);
      }
      fn_00478cc0((int)(uVar8 + 0x38), (uint)(iVar5));
    }
    if (*(int *)(param_1 + 0x3c) != 0) {
      uVar4 = (undefined4)(fn_00476dd0((int *)(*(int *)(param_1 + 0x3c))));
      fn_00478cc0((int)(uVar8 + 0x3c), (uint)(uVar4));
    }
    if (*(int *)(param_1 + 0x44) != 0) {
      uVar4 = (undefined4)(fn_00476dd0((int *)(*(int *)(param_1 + 0x44))));
      fn_00478cc0((int)(uVar8 + 0x44), (uint)(uVar4));
    }
    uVar2 = (uint)(*(uint *)(param_1 + 0x30));
    if (uVar2 == 0) {
      return uVar3;
    }
    for (puVar7 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar2 & 0xff) + uVar2 + (uVar2 >> 8 & 0xff) + (uVar2 >> 0x10 & 0xff) +
                    (uVar2 >> 0x18) & 0x3fff) * 4); puVar7 != (undefined4 *)0x0;
        puVar7 = (undefined4 *)*puVar7) {
      if (puVar7[1] == uVar2) goto LAB_00475c0d;
    }
    puVar7 = (undefined4 *)((undefined4 *)0x0);
LAB_00475c0d:
    if (puVar7 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar8 + 0x30), (uint)(puVar7[2]));
      return uVar3;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar8 + 0x30), (uint)(DAT_006daef6));
    param_1 = (uint)(*(uint *)(param_1 + 0x30));
    uVar8 = (uint)(uVar2);
  } while( true );
}

uint fn_00475ca0(int *param_1)
{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  for (puVar8 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar8 != (undefined4 *)0x0; puVar8 = (undefined4 *)*puVar8) {
    if ((int *)puVar8[1] == param_1) goto LAB_00475cf1;
  }
  puVar8 = (undefined4 *)((undefined4 *)0x0);
LAB_00475cf1:
  if (puVar8 != (undefined4 *)0x0) {
    return puVar8[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  puVar6 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar8 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar8[1] = (uint)(param_1);
  puVar8[2] = (uint)(uVar3);
  *puVar8 = (uint)(*puVar6);
  *puVar6 = (uint)(puVar8);
  uVar7 = (uint)(uVar3);
  do {
    *(undefined4 *)((int)param_1 + 0x36) = 0;
    *(undefined4 *)((int)param_1 + 0x3a) = 0;
    *(undefined4 *)((int)param_1 + 0x3e) = 0;
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x42);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x42);
    if (*(int *)((int)param_1 + 0x1e) != 0) {
      uVar4 = (undefined4)(fn_004781b0((int *)(*(undefined4 *)((int)param_1 + 0x1e))));
      fn_00478cc0((int)(uVar7 + 0x1e), (uint)(uVar4));
    }
    iVar5 = (int)(*param_1);
    if (iVar5 != 0) {
      if (*(char *)(iVar5 + 0xc) == '\0') {
        uVar4 = (undefined4)(FUN_0053ee10(iVar5));
        iVar5 = (int)(fn_00475ca0((int *)(uVar4)));
      }
      else {
        uVar4 = (undefined4)(FUN_0053ee70(iVar5));
        iVar5 = (int)(fn_004755d0((uint)(uVar4)));
        iVar5 = (int)(iVar5 + 0x34);
      }
      fn_00478cc0((int)(uVar7), (uint)(iVar5));
    }
    piVar1 = (int *)((int *)param_1[1]);
    if (piVar1 != (int *)0x0) {
      if (*(char *)(*piVar1 + 0xc) == '\0') {
        uVar4 = (undefined4)(FUN_0053ede0(piVar1));
        iVar5 = (int)(fn_00476670((int *)(uVar4)));
      }
      else {
        uVar4 = (undefined4)(FUN_0053eea0(piVar1));
        iVar5 = (int)(fn_00475960((uint)(uVar4)));
        iVar5 = (int)(iVar5 + 0x34);
      }
      fn_00478cc0((int)(uVar7 + 4), (uint)(iVar5));
    }
    if (param_1[2] != 0) {
      uVar4 = (undefined4)(fn_00476c20((int *)(param_1[2])));
      fn_00478cc0((int)(uVar7 + 8), (uint)(uVar4));
    }
    iVar5 = (int)(*(int *)((int)param_1 + 0x12));
    *(undefined4 *)(iVar5 + 4) = 1;
    fn_00478bd0((int)(uVar7 + 0x12), (uint)(iVar5));
    if (*(int *)((int)param_1 + 0x1a) != 0) {
      uVar4 = (undefined4)(fn_00476950((short *)(*(int *)((int)param_1 + 0x1a)), (int)(*(undefined4 *)((int)param_1 + 0x16))));
      fn_00478cc0((int)(uVar7 + 0x1a), (uint)(uVar4));
    }
    if (*(int *)((int)param_1 + 0x2a) != 0) {
      uVar4 = (undefined4)(fn_004731a0((int *)(*(int *)((int)param_1 + 0x2a))));
      fn_00478cc0((int)(uVar7 + 0x2a), (uint)(uVar4));
    }
    uVar4 = (undefined4)(fn_004721e0((uint)(*(undefined4 *)((int)param_1 + 0x2e))));
    fn_00478cc0((int)(uVar7 + 0x2e), (uint)(uVar4));
    if (*(int *)((int)param_1 + 0x32) != 0) {
      uVar4 = (undefined4)(fn_00476670((int *)(*(int *)((int)param_1 + 0x32))));
      fn_00478cc0((int)(uVar7 + 0x32), (uint)(uVar4));
    }
    uVar2 = (uint)(*(uint *)((int)param_1 + 0xe));
    if (uVar2 == 0) {
      return uVar3;
    }
    for (puVar8 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar2 & 0xff) + uVar2 + (uVar2 >> 8 & 0xff) + (uVar2 >> 0x10 & 0xff) +
                    (uVar2 >> 0x18) & 0x3fff) * 4); puVar8 != (undefined4 *)0x0;
        puVar8 = (undefined4 *)*puVar8) {
      if (puVar8[1] == uVar2) goto LAB_00475f1d;
    }
    puVar8 = (undefined4 *)((undefined4 *)0x0);
LAB_00475f1d:
    if (puVar8 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar7 + 0xe), (uint)(puVar8[2]));
      return uVar3;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar7 + 0xe), (uint)(DAT_006daef6));
    param_1 = (int *)(*(int **)((int)param_1 + 0xe));
    puVar6 = (undefined4 *)((undefined4 *)
             (((int)param_1 +
               ((uint)param_1 >> 0x18) +
               ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)
              & 0x3fff) * 4 + DAT_006daf12));
    puVar8 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar8[1] = (uint)(param_1);
    puVar8[2] = (uint)(uVar2);
    *puVar8 = (uint)(*puVar6);
    *puVar6 = (uint)(puVar8);
    uVar7 = (uint)(uVar2);
  } while( true );
}

uint fn_00476020(int *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uVar4 = (uint)(DAT_006daef6);
  uVar1 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar4, uVar1 = uVar4, (uVar4 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar4 = (uint)(DAT_006daef6);
    }
  }
  while( true ) {
    memclrw(param_1 + 1, 0xc);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x1c);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x1c);
    { uint nativeSwitch1Value=(uint)(*(undefined1 *)((int)param_1 + 0x1a));
if(nativeSwitch1Value==(uint)(0)) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)(1)) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)(2)) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)(3)) goto nativeSwitch1Case3;
if(nativeSwitch1Value==(uint)(4)) goto nativeSwitch1Case4;
if(nativeSwitch1Value==(uint)(5)) goto nativeSwitch1Case5;
if(nativeSwitch1Value==(uint)(6)) goto nativeSwitch1Case6;
if(nativeSwitch1Value==(uint)(7)) goto nativeSwitch1Case7;
if(nativeSwitch1Value==(uint)(8)) goto nativeSwitch1Case8;
goto nativeSwitch1Case9;

    nativeSwitch1Case0:
      uVar3 = (undefined4)(fn_004755d0((uint)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      goto nativeSwitch1End;
    nativeSwitch1Case1:
      uVar3 = (undefined4)(fn_00475030((char *)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      goto nativeSwitch1End;
    nativeSwitch1Case2:
      uVar3 = (undefined4)(fn_00476240((int *)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      goto nativeSwitch1End;
    nativeSwitch1Case3:
      uVar3 = (undefined4)(fn_00475030((char *)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      if (param_1[5] != 0) {
        uVar3 = (undefined4)(fn_004772b0((uint *)(param_1[5])));
        fn_00478cc0((int)(uVar4 + 0x14), (uint)(uVar3));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case4:
      uVar3 = (undefined4)(fn_004721e0((uint)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      uVar3 = (undefined4)(fn_00473510((char *)(param_1[5])));
      fn_00478cc0((int)(uVar4 + 0x14), (uint)(uVar3));
      goto nativeSwitch1End;
    nativeSwitch1Case5:
      uVar3 = (undefined4)(fn_00477490((uint)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      goto nativeSwitch1End;
    nativeSwitch1Case6:
      uVar3 = (undefined4)(fn_00472180((undefined1 *)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      goto nativeSwitch1End;
    nativeSwitch1Case7:
      uVar3 = (undefined4)(fn_00473510((char *)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      goto nativeSwitch1End;
    nativeSwitch1Case8:
      uVar3 = (undefined4)(fn_00475ca0((int *)(param_1[4])));
      fn_00478cc0((int)(uVar4 + 0x10), (uint)(uVar3));
      goto nativeSwitch1End;
    nativeSwitch1Case9:
      CError_Internal(s_CPrec_c_0067dd1c, 0xaae);

nativeSwitch1End:;
}
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar4), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar4 = (uint)(uVar2);
  }
  return uVar1;
}

uint fn_00476240(int *param_1)
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar2 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x34);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x34);
  if (param_1[7] != 0) {
    uVar3 = (undefined4)(fn_004781b0((int *)(param_1[7])));
    fn_00478cc0((int)(uVar2 + 0x1c), (uint)(uVar3));
  }
  if (*param_1 != 0) {
    uVar3 = (undefined4)(fn_00475030((char *)(*param_1)));
    fn_00478cc0((int)(uVar2), (uint)(uVar3));
  }
  if (param_1[2] != 0) {
    uVar3 = (undefined4)(fn_00471720((int *)(param_1[2])));
    fn_00478cc0((int)(uVar2 + 8), (uint)(uVar3));
  }
  iVar1 = (int)(param_1[3]);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 4) = 1;
    fn_00478bd0((int)(uVar2 + 0xc), (uint)(iVar1));
  }
  if (param_1[4] != 0) {
    uVar3 = (undefined4)(fn_00476dd0((int *)(param_1[4])));
    fn_00478cc0((int)(uVar2 + 0x10), (uint)(uVar3));
  }
  if (param_1[0xb] != 0) {
    uVar3 = (undefined4)(fn_00476950((short *)(param_1[0xb]), (int)(param_1[10])));
    fn_00478cc0((int)(uVar2 + 0x2c), (uint)(uVar3));
  }
  if (param_1[0xc] != 0) {
    uVar3 = (undefined4)(fn_004731a0((int *)(param_1[0xc])));
    fn_00478cc0((int)(uVar2 + 0x30), (uint)(uVar3));
  }
  return uVar2;
}

uint fn_00476380(int *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uVar4 = (uint)(DAT_006daef6);
  uVar1 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar4, uVar1 = uVar4, (uVar4 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar4 = (uint)(DAT_006daef6);
    }
  }
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0xc);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0xc);
    if (param_1[1] != 0) {
      uVar3 = (undefined4)(fn_004755d0((uint)(param_1[1])));
      fn_00478cc0((int)(uVar4 + 4), (uint)(uVar3));
    }
    if (param_1[2] != 0) {
      uVar3 = (undefined4)(fn_00476dd0((int *)(param_1[2])));
      fn_00478cc0((int)(uVar4 + 8), (uint)(uVar3));
    }
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar4), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar4 = (uint)(uVar2);
  }
  return uVar1;
}

uint fn_00476490(int *param_1)
{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  for (puVar3 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3) {
    if ((int *)puVar3[1] == param_1) goto LAB_004764e2;
  }
  puVar3 = (undefined4 *)((undefined4 *)0x0);
LAB_004764e2:
  if (puVar3 != (undefined4 *)0x0) {
    return puVar3[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  puVar4 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar3[1] = (uint)(param_1);
  puVar3[2] = (uint)(uVar1);
  *puVar3 = (uint)(*puVar4);
  *puVar4 = (uint)(puVar3);
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x30);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x30);
  if (param_1[2] != 0) {
    uVar2 = (undefined4)(fn_004781b0((int *)(param_1[2])));
    fn_00478cc0((int)(uVar1 + 8), (uint)(uVar2));
  }
  if (*param_1 != 0) {
    uVar2 = (undefined4)(fn_00476c20((int *)(*param_1)));
    fn_00478cc0((int)(uVar1), (uint)(uVar2));
  }
  if (param_1[1] != 0) {
    uVar2 = (undefined4)(fn_00475390((char *)(param_1[1])));
    fn_00478cc0((int)(uVar1 + 4), (uint)(uVar2));
  }
  if (param_1[6] != 0) {
    uVar2 = (undefined4)(fn_00476950((short *)(param_1[6]), (int)(param_1[5])));
    fn_00478cc0((int)(uVar1 + 0x18), (uint)(uVar2));
  }
  if (param_1[7] != 0) {
    uVar2 = (undefined4)(fn_004731a0((int *)(param_1[7])));
    fn_00478cc0((int)(uVar1 + 0x1c), (uint)(uVar2));
  }
  if (param_1[8] != 0) {
    uVar2 = (undefined4)(fn_00474790((int *)(param_1[8])));
    fn_00478cc0((int)(uVar1 + 0x20), (uint)(uVar2));
  }
  return uVar1;
}

uint fn_00476670(int *param_1)
{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  for (puVar4 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
    if ((int *)puVar4[1] == param_1) goto LAB_004766c1;
  }
  puVar4 = (undefined4 *)((undefined4 *)0x0);
LAB_004766c1:
  if (puVar4 != (undefined4 *)0x0) {
    return puVar4[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  puVar7 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar4 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar4[1] = (uint)(param_1);
  puVar4[2] = (uint)(uVar3);
  *puVar4 = (uint)(*puVar7);
  *puVar7 = (uint)(puVar4);
  uVar8 = (uint)(uVar3);
  do {
    param_1[5] = 0;
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x1c);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x1c);
    iVar6 = (int)(*param_1);
    if (iVar6 != 0) {
      if (*(char *)(iVar6 + 0xc) == '\0') {
        uVar5 = (undefined4)(FUN_0053ee10(iVar6));
        iVar6 = (int)(fn_00475ca0((int *)(uVar5)));
      }
      else {
        uVar5 = (undefined4)(FUN_0053ee70(iVar6));
        iVar6 = (int)(fn_004755d0((uint)(uVar5)));
        iVar6 = (int)(iVar6 + 0x34);
      }
      fn_00478cc0((int)(uVar8), (uint)(iVar6));
    }
    piVar1 = (int *)((int *)param_1[1]);
    if (piVar1 != (int *)0x0) {
      if (*(char *)(*piVar1 + 0xc) == '\0') {
        uVar5 = (undefined4)(FUN_0053ede0(piVar1));
        iVar6 = (int)(fn_00476670((int *)(uVar5)));
      }
      else {
        uVar5 = (undefined4)(FUN_0053eea0(piVar1));
        iVar6 = (int)(fn_00475960((uint)(uVar5)));
        iVar6 = (int)(iVar6 + 0x34);
      }
      fn_00478cc0((int)(uVar8 + 4), (uint)(iVar6));
    }
    if (param_1[2] != 0) {
      uVar5 = (undefined4)(fn_00476dd0((int *)(param_1[2])));
      fn_00478cc0((int)(uVar8 + 8), (uint)(uVar5));
    }
    uVar5 = (undefined4)(fn_004721e0((uint)(param_1[6])));
    fn_00478cc0((int)(uVar8 + 0x18), (uint)(uVar5));
    uVar2 = (uint)(param_1[4]);
    if (uVar2 == 0) {
      return uVar3;
    }
    for (puVar4 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar2 & 0xff) + uVar2 + (uVar2 >> 8 & 0xff) + (uVar2 >> 0x10 & 0xff) +
                    (uVar2 >> 0x18) & 0x3fff) * 4); puVar4 != (undefined4 *)0x0;
        puVar4 = (undefined4 *)*puVar4) {
      if (puVar4[1] == uVar2) goto LAB_00476874;
    }
    puVar4 = (undefined4 *)((undefined4 *)0x0);
LAB_00476874:
    if (puVar4 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar8 + 0x10), (uint)(puVar4[2]));
      return uVar3;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar8 + 0x10), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)param_1[4]);
    puVar7 = (undefined4 *)((undefined4 *)
             (((int)param_1 +
               ((uint)param_1 >> 0x18) +
               ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)
              & 0x3fff) * 4 + DAT_006daf12));
    puVar4 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar4[1] = (uint)(param_1);
    puVar4[2] = (uint)(uVar2);
    *puVar4 = (uint)(*puVar7);
    *puVar7 = (uint)(puVar4);
    uVar8 = (uint)(uVar2);
  } while( true );
}

uint fn_00476950(short *param_1, int param_2)
{
  byte nativeFrame[38];
#define sStack_36 (*(short *)(nativeFrame+0))
#define local_2c (*(short *)(nativeFrame+10))
#define uStack_2a (*(undefined2 *)(nativeFrame+12))
#define local_28 (*(undefined2 *)(nativeFrame+14))
#define uStack_26 (*(undefined2 *)(nativeFrame+16))
#define local_24 (*(undefined2 *)(nativeFrame+18))
#define uStack_22 (*(undefined2 *)(nativeFrame+20))
#define local_20 (*(undefined2 *)(nativeFrame+22))
#define local_14 (*(int *)(nativeFrame+34))

  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  short *psVar9;
  iVar7 = (int)(0);
  psVar9 = (short *)(param_1);
  if (param_2 > 0) {
    do {
      uVar6 = (undefined4)(*(undefined4 *)psVar9);
      sStack_36 = (short)((short)((uint)uVar6 >> 0x10));
      uVar1 = (undefined4)(*(undefined4 *)(psVar9 + 2));
      uVar2 = (undefined4)(*(undefined4 *)(psVar9 + 4));
      local_2c = (short)((short)*(undefined4 *)(psVar9 + 6));
      uStack_2a = (undefined2)((undefined2)((uint)*(undefined4 *)(psVar9 + 6) >> 0x10));
      local_28 = (undefined2)((undefined2)*(undefined4 *)(psVar9 + 8));
      uStack_26 = (undefined2)((undefined2)((uint)*(undefined4 *)(psVar9 + 8) >> 0x10));
      local_24 = (undefined2)((undefined2)*(undefined4 *)(psVar9 + 10));
      uStack_22 = (undefined2)((undefined2)((uint)*(undefined4 *)(psVar9 + 10) >> 0x10));
      local_20 = (undefined2)((undefined2)*(undefined4 *)(psVar9 + 0xc));
      memclrw(psVar9, 0x1c);
      *(uint *)(psVar9 + 7) = CONCAT22(local_28, uStack_2a);
      *(uint *)(psVar9 + 9) = CONCAT22(local_24, uStack_26);
      *(uint *)(psVar9 + 0xb) = CONCAT22(local_20, uStack_22);
      *psVar9 = (short)uVar6;
      { uint nativeSwitch2Value=(uint)(*psVar9);
if(nativeSwitch2Value==(uint)(-5)) goto nativeSwitch2Case0;
if(nativeSwitch2Value==(uint)(-4)) goto nativeSwitch2Case1;
if(nativeSwitch2Value==(uint)(-3)) goto nativeSwitch2Case2;
if(nativeSwitch2Value==(uint)(-2)) goto nativeSwitch2Case3;
if(nativeSwitch2Value==(uint)(-1)) goto nativeSwitch2Case4;
goto nativeSwitch2End;

      nativeSwitch2Case0:
      nativeSwitch2Case1:
        psVar9[1] = sStack_36;
        *(undefined4 *)(psVar9 + 2) = uVar1;
        *(undefined4 *)(psVar9 + 4) = uVar2;
        psVar9[6] = local_2c;
        goto nativeSwitch2End;
      nativeSwitch2Case2:
        *(undefined4 *)(psVar9 + 2) = uVar1;
        goto nativeSwitch2End;
      nativeSwitch2Case3:
        psVar9[1] = sStack_36;
        *(undefined4 *)(psVar9 + 2) = uVar1;
        *(undefined4 *)(psVar9 + 4) = uVar2;
        goto nativeSwitch2End;
      nativeSwitch2Case4:
        psVar9[1] = sStack_36;
        *(undefined4 *)(psVar9 + 2) = uVar1;
        *(undefined4 *)(psVar9 + 4) = uVar2;

nativeSwitch2End:;
}
      iVar7 = (int)(iVar7 + 1);
      psVar9 = (short *)(psVar9 + 0xe);
    } while (iVar7 < param_2);
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, param_2 * 0x1c);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + param_2 * 0x1c);
  if (DAT_006daee5 != '\0') {
    puVar5 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar5[1] = (uint)(uVar3);
    puVar5[2] = (uint)(param_2);
    *puVar5 = (uint)(DAT_006daf06);
    DAT_006daf06 = (uint )(puVar5);
  }
  local_14 = (int)(0);
  uVar8 = (uint)(uVar3);
  if (param_2 > 0) {
    do {
      if (*(int *)(param_1 + 7) != 0) {
        uVar6 = (undefined4)(fn_004781b0((int *)(*(undefined4 *)(param_1 + 7))));
        fn_00478cc0((int)(uVar8 + 0xe), (uint)(uVar6));
      }
      { uint nativeSwitch1Value=(uint)(*param_1);
if(nativeSwitch1Value==(uint)(-7)) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)(-2)) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)(-1)) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)(-5)) goto nativeSwitch1Case4;
if(nativeSwitch1Value==(uint)(-4)) goto nativeSwitch1Case5;
if(nativeSwitch1Value==(uint)(-3)) goto nativeSwitch1Case6;
goto nativeSwitch1Case3;

      nativeSwitch1Case0:
      nativeSwitch1Case1:
      nativeSwitch1Case2:
        goto nativeSwitch1End;
      nativeSwitch1Case3:
        if (*param_1 < 0) {
          CError_Internal(s_CPrec_c_0067dd1c, 0x96a);
        }
        goto nativeSwitch1End;
      nativeSwitch1Case4:
      nativeSwitch1Case5:
        uVar6 = (undefined4)(*(undefined4 *)(param_1 + 2));
        iVar7 = (int)(*(int *)(param_1 + 4) * 2 >> 1);
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar4 = (uint)(DAT_006daef6);
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, uVar6, iVar7);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + iVar7);
        fn_00478cc0((int)(uVar8 + 4), (uint)(uVar4));
        goto nativeSwitch1End;
      nativeSwitch1Case6:
        iVar7 = (int)(*(int *)(param_1 + 2));
        *(undefined4 *)(iVar7 + 4) = 1;
        fn_00478bd0((int)(uVar8 + 4), (uint)(iVar7));

nativeSwitch1End:;
}
      local_14 = (int)(local_14 + 1);
      param_1 = (short *)(param_1 + 0xe);
      uVar8 = (uint)(uVar8 + 0x1c);
    } while (local_14 < param_2);
  }
  return uVar3;
}
#undef sStack_36
#undef local_2c
#undef uStack_2a
#undef local_28
#undef uStack_26
#undef local_24
#undef uStack_22
#undef local_20
#undef local_14


uint fn_00476c20(int *param_1)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uVar5 = (uint)(DAT_006daef6);
  uVar2 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar5, uVar2 = uVar5, (uVar5 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar5 = (uint)(DAT_006daef6);
    }
  }
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x18);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x18);
    iVar1 = (int)(param_1[1]);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 4) = 1;
      fn_00478bd0((int)(uVar5 + 4), (uint)(iVar1));
    }
    { uint nativeSwitch1Value=(uint)(*(undefined1 *)((int)param_1 + 0xb));
if(nativeSwitch1Value==(uint)(0)) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)(1)) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)(2)) goto nativeSwitch1Case2;
goto nativeSwitch1Case3;

    nativeSwitch1Case0:
      if (param_1[3] != 0) {
        uVar4 = (undefined4)(fn_00475030((char *)(param_1[3])));
        fn_00478cc0((int)(uVar5 + 0xc), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case1:
      uVar4 = (undefined4)(fn_00475030((char *)(param_1[3])));
      fn_00478cc0((int)(uVar5 + 0xc), (uint)(uVar4));
      if (param_1[5] != 0) {
        uVar4 = (undefined4)(fn_00473510((char *)(param_1[5])));
        fn_00478cc0((int)(uVar5 + 0x14), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case2:
      if (param_1[3] != 0) {
        uVar4 = (undefined4)(fn_00476c20((int *)(param_1[3])));
        fn_00478cc0((int)(uVar5 + 0xc), (uint)(uVar4));
      }
      if (param_1[4] != 0) {
        uVar4 = (undefined4)(fn_00475030((char *)(param_1[4])));
        fn_00478cc0((int)(uVar5 + 0x10), (uint)(uVar4));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case3:
      CError_Internal(s_CPrec_c_0067dd1c, 0x90d);

nativeSwitch1End:;
}
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar3 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar5), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar5 = (uint)(uVar3);
  }
  return uVar2;
}

uint fn_00476dd0(int *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uVar4 = (uint)(DAT_006daef6);
  uVar1 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar4, uVar1 = uVar4, (uVar4 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar4 = (uint)(DAT_006daef6);
    }
  }
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x12);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x12);
    { uint nativeSwitch1Value=(uint)(*(undefined1 *)((int)param_1 + 7));
if(nativeSwitch1Value==(uint)(0)) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)(1)) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)(2)) goto nativeSwitch1Case2;
goto nativeSwitch1Case3;

    nativeSwitch1Case0:
      if (param_1[2] != 0) {
        uVar3 = (undefined4)(fn_00475030((char *)(param_1[2])));
        fn_00478cc0((int)(uVar4 + 8), (uint)(uVar3));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case1:
      if (param_1[2] != 0) {
        uVar3 = (undefined4)(fn_00473510((char *)(param_1[2])));
        fn_00478cc0((int)(uVar4 + 8), (uint)(uVar3));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case2:
      if (param_1[2] != 0) {
        uVar3 = (undefined4)(fn_00475030((char *)(param_1[2])));
        fn_00478cc0((int)(uVar4 + 8), (uint)(uVar3));
      }
      goto nativeSwitch1End;
    nativeSwitch1Case3:
      CError_Internal(s_CPrec_c_0067dd1c, 0x8d1);

nativeSwitch1End:;
}
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar4), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar4 = (uint)(uVar2);
  }
  return uVar1;
}

uint fn_00476f20(int *param_1)
{
  uint uVar1;
  undefined4 uVar2;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x10);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x10);
  if (*param_1 != 0) {
    uVar2 = (undefined4)(fn_004721e0((uint)(*param_1)));
    fn_00478cc0((int)(uVar1), (uint)(uVar2));
  }
  return uVar1;
}

uint fn_00476fb0(int *param_1)
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uVar5 = (uint)(DAT_006daef6);
  uVar6 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    for (; uVar5 = DAT_006daef6, uVar6 = DAT_006daef6, (DAT_006daef6 & 3) != 0;
        DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x10);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x10);
    uVar2 = (undefined4)(fn_00475390((char *)(param_1[1])));
    fn_00478cc0((int)(uVar5 + 4), (uint)(uVar2));
    piVar4 = (int *)((int *)param_1[3]);
    if (piVar4 != (int *)0x0) {
      uVar3 = (uint)(DAT_006daef6);
      uVar7 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        while (DAT_006daef6 = uVar3, uVar7 = uVar3, (uVar3 & 3) != 0) {
          AppendGListByte(&DAT_006daf1a, 0);
          DAT_006daef6 = (uint )(DAT_006daef6 + 1);
          uVar3 = (uint)(DAT_006daef6);
        }
      }
      while( true ) {
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, piVar4, 8);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + 8);
        uVar2 = (undefined4)(fn_00475390((char *)(piVar4[1])));
        fn_00478cc0((int)(uVar3 + 4), (uint)(uVar2));
        if (*piVar4 == 0) break;
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar1 = (uint)(DAT_006daef6);
        fn_00478cc0((int)(uVar3), (uint)(DAT_006daef6));
        piVar4 = (int *)((int *)*piVar4);
        uVar3 = (uint)(uVar1);
      }
      fn_00478cc0((int)(uVar5 + 0xc), (uint)(uVar7));
    }
    if (param_1[2] != 0) {
      uVar2 = (undefined4)(fn_00471ff0((int *)(param_1[2])));
      fn_00478cc0((int)(uVar5 + 8), (uint)(uVar2));
    }
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar7 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar5), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar5 = (uint)(uVar7);
  }
  return uVar6;
}

uint fn_004771c0(int *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uVar4 = (uint)(DAT_006daef6);
  uVar1 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar4, uVar1 = uVar4, (uVar4 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar4 = (uint)(DAT_006daef6);
    }
  }
  while( true ) {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x12);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x12);
    uVar3 = (undefined4)(fn_00475390((char *)(param_1[1])));
    fn_00478cc0((int)(uVar4 + 4), (uint)(uVar3));
    if (*param_1 == 0) break;
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar2 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar4), (uint)(DAT_006daef6));
    param_1 = (int *)((int *)*param_1);
    uVar4 = (uint)(uVar2);
  }
  return uVar1;
}

uint fn_004772b0(uint *param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  for (puVar4 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
    if ((uint *)puVar4[1] == param_1) goto LAB_00477301;
  }
  puVar4 = (undefined4 *)((undefined4 *)0x0);
LAB_00477301:
  if (puVar4 != (undefined4 *)0x0) {
    return puVar4[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar2 = (uint)(DAT_006daef6);
  puVar5 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar4 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar4[1] = (uint)(param_1);
  puVar4[2] = (uint)(uVar2);
  *puVar4 = (uint)(*puVar5);
  *puVar5 = (uint)(puVar4);
  uVar6 = (uint)(uVar2);
  do {
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x14);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x14);
    uVar3 = (undefined4)(fn_00475390((char *)(param_1[1])));
    fn_00478cc0((int)(uVar6 + 4), (uint)(uVar3));
    uVar1 = (uint)(*param_1);
    if (uVar1 == 0) {
      return uVar2;
    }
    for (puVar4 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar1 & 0xff) + uVar1 + (uVar1 >> 8 & 0xff) + (uVar1 >> 0x10 & 0xff) +
                    (uVar1 >> 0x18) & 0x3fff) * 4); puVar4 != (undefined4 *)0x0;
        puVar4 = (undefined4 *)*puVar4) {
      if (puVar4[1] == uVar1) goto LAB_0047741f;
    }
    puVar4 = (undefined4 *)((undefined4 *)0x0);
LAB_0047741f:
    if (puVar4 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar6), (uint)(puVar4[2]));
      return uVar2;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar1 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar6), (uint)(DAT_006daef6));
    param_1 = (uint *)((uint *)*param_1);
    uVar6 = (uint)(uVar1);
  } while( true );
}

uint fn_00477490(uint param_1)
{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar2 = (uint)(DAT_006daef6);
  puVar5 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar3[1] = (uint)(param_1);
  puVar3[2] = (uint)(uVar2);
  *puVar3 = (uint)(*puVar5);
  *puVar5 = (uint)(puVar3);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x10);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x10);
  { uint nativeSwitch1Value=(uint)(*(undefined1 *)(param_1 + 6));
if(nativeSwitch1Value==(uint)(0)) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)(1)) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)(2)) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)(3)) goto nativeSwitch1Case3;
if(nativeSwitch1Value==(uint)(4)) goto nativeSwitch1Case4;
if(nativeSwitch1Value==(uint)(5)) goto nativeSwitch1Case5;
if(nativeSwitch1Value==(uint)(6)) goto nativeSwitch1Case6;
if(nativeSwitch1Value==(uint)(7)) goto nativeSwitch1Case7;
if(nativeSwitch1Value==(uint)(8)) goto nativeSwitch1Case8;
if(nativeSwitch1Value==(uint)(9)) goto nativeSwitch1Case9;
if(nativeSwitch1Value==(uint)(10)) goto nativeSwitch1Case10;
if(nativeSwitch1Value==(uint)(0xb)) goto nativeSwitch1Case11;
goto nativeSwitch1Case12;

  nativeSwitch1Case0:
    goto nativeSwitch1End;
  nativeSwitch1Case1:
    uVar4 = (undefined4)(fn_00477490((uint)(*(undefined4 *)(param_1 + 8))));
    fn_00478cc0((int)(uVar2 + 8), (uint)(uVar4));
    iVar1 = (int)(*(int *)(param_1 + 0xc));
    *(undefined4 *)(iVar1 + 4) = 1;
    fn_00478bd0((int)(uVar2 + 0xc), (uint)(iVar1));
    goto nativeSwitch1End;
  nativeSwitch1Case2:
    uVar4 = (undefined4)(fn_004755d0((uint)(*(undefined4 *)(param_1 + 8))));
    fn_00478cc0((int)(uVar2 + 8), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00476dd0((int *)(*(undefined4 *)(param_1 + 0xc))));
    fn_00478cc0((int)(uVar2 + 0xc), (uint)(uVar4));
    goto nativeSwitch1End;
  nativeSwitch1Case3:
    uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 8))));
    fn_00478cc0((int)(uVar2 + 8), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(param_1 + 0xc))));
    fn_00478cc0((int)(uVar2 + 0xc), (uint)(uVar4));
    goto nativeSwitch1End;
  nativeSwitch1Case4:
    uVar4 = (undefined4)(fn_00477490((uint)(*(undefined4 *)(param_1 + 8))));
    fn_00478cc0((int)(uVar2 + 8), (uint)(uVar4));
    if (*(int *)(param_1 + 0xc) != 0) {
      uVar4 = (undefined4)(fn_00476dd0((int *)(*(int *)(param_1 + 0xc))));
      fn_00478cc0((int)(uVar2 + 0xc), (uint)(uVar4));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case5:
  nativeSwitch1Case6:
    uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 8))));
    fn_00478cc0((int)(uVar2 + 8), (uint)(uVar4));
    uVar4 = (undefined4)(fn_00473510((char *)(*(undefined4 *)(param_1 + 0xc))));
    fn_00478cc0((int)(uVar2 + 0xc), (uint)(uVar4));
    goto nativeSwitch1End;
  nativeSwitch1Case7:
    uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 8))));
    fn_00478cc0((int)(uVar2 + 8), (uint)(uVar4));
    goto nativeSwitch1End;
  nativeSwitch1Case8:
    uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 8))));
    fn_00478cc0((int)(uVar2 + 8), (uint)(uVar4));
    if (*(int *)(param_1 + 0xc) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(param_1 + 0xc))));
      fn_00478cc0((int)(uVar2 + 0xc), (uint)(uVar4));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case9:
  nativeSwitch1Case10:
    if (*(int *)(param_1 + 8) != 0) {
      uVar4 = (undefined4)(fn_00473510((char *)(*(int *)(param_1 + 8))));
      fn_00478cc0((int)(uVar2 + 8), (uint)(uVar4));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case11:
    uVar4 = (undefined4)(fn_00476c20((int *)(*(undefined4 *)(param_1 + 0xc))));
    fn_00478cc0((int)(uVar2 + 0xc), (uint)(uVar4));
    goto nativeSwitch1End;
  nativeSwitch1Case12:
    CError_Internal(s_CPrec_c_0067dd1c, 0x62c);

nativeSwitch1End:;
}
  return uVar2;
}

uint fn_004776f0(uint param_1)
{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  int iVar10;
  uint uVar11;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar4 = (uint)(DAT_006daef6);
  puVar9 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar7 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar7[1] = (uint)(param_1);
  puVar7[2] = (uint)(uVar4);
  *puVar7 = (uint)(*puVar9);
  *puVar9 = (uint)(puVar7);
  if ((*(uint *)(param_1 + 0x16) & 0x10) == 0) {
    iVar10 = (int)(0x1e);
  }
  else {
    iVar10 = (int)(0x2c);
  }
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, iVar10);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + iVar10);
  uVar8 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 0xe))));
  uVar11 = (uint)(uVar4);
  fn_00478cc0((int)(uVar4 + 0xe), (uint)(uVar8));
  if (*(int *)(param_1 + 6) != 0) {
    uVar8 = (undefined4)(fn_00477940((uint *)(*(int *)(param_1 + 6)), (char)((*(uint *)(param_1 + 0x16) & 0x900000) != 0)));
    fn_00478cc0((int)(uVar11 + 6), (uint)(uVar8));
  }
  piVar1 = (int *)(*(int **)(param_1 + 10));
  if (piVar1 != (int *)0x0) {
    uVar2 = (uint)(DAT_006daef6);
    uVar3 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      for (; uVar2 = DAT_006daef6, uVar3 = DAT_006daef6, (DAT_006daef6 & 3) != 0;
          DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    for (; uVar5 = DAT_006daef6, DAT_006daef6 = uVar2, piVar1 != (int *)0x0; piVar1 = (int *)*piVar1
        ) {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, piVar1, 0xc);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 0xc);
      if (piVar1[1] != 0) {
        uVar8 = (undefined4)(fn_00475030((char *)(piVar1[1])));
        fn_00478cc0((int)(uVar3 + 4), (uint)(uVar8));
      }
      if (*piVar1 == 0) break;
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar6 = (uint)(DAT_006daef6);
      fn_00478cc0((int)(uVar3), (uint)(DAT_006daef6));
      uVar2 = (uint)(DAT_006daef6);
      uVar3 = (uint)(uVar6);
      DAT_006daef6 = (uint )(uVar5);
    }
    fn_00478cc0((int)(uVar11 + 10), (uint)(uVar5));
  }
  if ((*(uint *)(param_1 + 0x16) & 0x10) != 0) {
    uVar8 = (undefined4)(fn_00475390((char *)(*(undefined4 *)(param_1 + 0x1e))));
    fn_00478cc0((int)(uVar11 + 0x1e), (uint)(uVar8));
  }
  return uVar4;
}

uint fn_00477940(uint *param_1, char param_2)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  for (puVar6 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar6 != (undefined4 *)0x0; puVar6 = (undefined4 *)*puVar6) {
    if ((uint *)puVar6[1] == param_1) goto LAB_0047798d;
  }
  puVar6 = (undefined4 *)((undefined4 *)0x0);
LAB_0047798d:
  if (puVar6 != (undefined4 *)0x0) {
    return puVar6[2];
  }
  uVar5 = (uint)(DAT_006daef6);
  uVar2 = (uint)(DAT_006daef6);
  if (DAT_006daee5 != '\0') {
    while (DAT_006daef6 = uVar5, uVar2 = uVar5, (uVar5 & 3) != 0) {
      AppendGListByte(&DAT_006daf1a, 0);
      DAT_006daef6 = (uint )(DAT_006daef6 + 1);
      uVar5 = (uint)(DAT_006daef6);
    }
  }
  do {
    if (param_2 == '\0') {
      param_1[1] = 0;
    }
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x18);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x18);
    if ((param_2 != '\0') && (uVar1 = param_1[1], uVar1 != 0)) {
      *(undefined4 *)(uVar1 + 4) = 1;
      fn_00478bd0((int)(uVar5 + 4), (uint)(uVar1));
    }
    if (param_1[2] != 0) {
      uVar3 = (undefined4)(fn_00473510((char *)(param_1[2])));
      fn_00478cc0((int)(uVar5 + 8), (uint)(uVar3));
    }
    if (param_1[3] == 0) {
      CError_Internal(s_CPrec_c_0067dd1c, 0x594);
    }
    else {
      uVar3 = (undefined4)(fn_00475030((char *)(param_1[3])));
      fn_00478cc0((int)(uVar5 + 0xc), (uint)(uVar3));
    }
    uVar1 = (uint)(*param_1);
    if (uVar1 == 0) {
      return uVar2;
    }
    for (puVar6 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((uVar1 & 0xff) + uVar1 + (uVar1 >> 8 & 0xff) + (uVar1 >> 0x10 & 0xff) +
                    (uVar1 >> 0x18) & 0x3fff) * 4); puVar6 != (undefined4 *)0x0;
        puVar6 = (undefined4 *)*puVar6) {
      if (puVar6[1] == uVar1) goto LAB_00477aa2;
    }
    puVar6 = (undefined4 *)((undefined4 *)0x0);
LAB_00477aa2:
    if (puVar6 != (undefined4 *)0x0) {
      fn_00478cc0((int)(uVar5), (uint)(puVar6[2]));
      return uVar2;
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar1 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar5), (uint)(DAT_006daef6));
    param_1 = (uint *)((uint *)*param_1);
    puVar4 = (undefined4 *)((undefined4 *)
             (((int)param_1 +
               ((uint)param_1 >> 0x18) +
               ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff)
              & 0x3fff) * 4 + DAT_006daf12));
    puVar6 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar6[1] = (uint)(param_1);
    puVar6[2] = (uint)(uVar1);
    *puVar6 = (uint)(*puVar4);
    *puVar4 = (uint)(puVar6);
    uVar5 = (uint)(uVar1);
  } while( true );
}

uint fn_00477bb0(uint param_1)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int *piVar7;
  uint uVar8;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar2 = (uint)(DAT_006daef6);
  puVar6 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar4 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar4[1] = (uint)(param_1);
  puVar4[2] = (uint)(uVar2);
  *puVar4 = (uint)(*puVar6);
  *puVar6 = (uint)(puVar4);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x12);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x12);
  iVar1 = (int)(*(int *)(param_1 + 6));
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 4) = 1;
    fn_00478bd0((int)(uVar2 + 6), (uint)(iVar1));
  }
  piVar7 = (int *)(*(int **)(param_1 + 10));
  if (piVar7 != (int *)0x0) {
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar8 = (uint)(DAT_006daef6);
    fn_00478cc0((int)(uVar2 + 10), (uint)(DAT_006daef6));
    while( true ) {
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, piVar7, 0x14);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + 0x14);
      uVar5 = (undefined4)(fn_00475030((char *)(piVar7[1])));
      fn_00478cc0((int)(uVar8 + 4), (uint)(uVar5));
      iVar1 = (int)(piVar7[2]);
      *(undefined4 *)(iVar1 + 4) = 1;
      fn_00478bd0((int)(uVar8 + 8), (uint)(iVar1));
      if (*piVar7 == 0) break;
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar3 = (uint)(DAT_006daef6);
      fn_00478cc0((int)(uVar8), (uint)(DAT_006daef6));
      piVar7 = (int *)((int *)*piVar7);
      uVar8 = (uint)(uVar3);
    }
  }
  return uVar2;
}

uint fn_00477d80(uint param_1)
{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar2 = (uint)(DAT_006daef6);
  puVar5 = (undefined4 *)((undefined4 *)
           (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
             (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
  puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar3[1] = (uint)(param_1);
  puVar3[2] = (uint)(uVar2);
  *puVar3 = (uint)(*puVar5);
  *puVar5 = (uint)(puVar3);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0x16);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x16);
  if (*(int *)(param_1 + 6) != 0) {
    uVar4 = (undefined4)(fn_00471720((int *)(*(int *)(param_1 + 6))));
    fn_00478cc0((int)(uVar2 + 6), (uint)(uVar4));
  }
  if (*(int *)(param_1 + 10) != 0) {
    uVar4 = (undefined4)(fn_00472f10((uint)(*(int *)(param_1 + 10))));
    fn_00478cc0((int)(uVar2 + 10), (uint)(uVar4));
  }
  uVar4 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 0xe))));
  fn_00478cc0((int)(uVar2 + 0xe), (uint)(uVar4));
  iVar1 = (int)(*(int *)(param_1 + 0x12));
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 4) = 1;
    fn_00478bd0((int)(uVar2 + 0x12), (uint)(iVar1));
  }
  return uVar2;
}

uint fn_00477eb0(uint param_1)
{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  if ((DAT_0070f1c5 == '\0') && (DAT_006daee5 != '\0') && (*(int *)(param_1 + 2) > 0)) {
    uVar1 = (undefined4)(FUN_005441e0(param_1));
    iVar2 = (int)(FUN_00544180(&DAT_006daf2e, param_1, uVar1));
    if (iVar2 != 0) {
      return *(uint *)(iVar2 + 8);
    }
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar5 = (uint)(DAT_006daef6);
    puVar4 = (undefined4 *)((undefined4 *)
             (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
               (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
    uVar6 = (uint)(DAT_006daef6);
    uVar7 = (uint)(DAT_006daef6);
    puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar3[1] = (uint)(param_1);
    puVar3[2] = (uint)(uVar6);
    *puVar3 = (uint)(*puVar4);
    *puVar4 = (uint)(puVar3);
    FUN_00544130(&DAT_006daf2e, param_1, uVar1, uVar7);
  }
  else {
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar5 = (uint)(DAT_006daef6);
    puVar4 = (undefined4 *)((undefined4 *)
             (((param_1 & 0xff) + param_1 + (param_1 >> 8 & 0xff) + (param_1 >> 0x10 & 0xff) +
               (param_1 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
    puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
    puVar3[1] = (uint)(param_1);
    puVar3[2] = (uint)(uVar5);
    *puVar3 = (uint)(*puVar4);
    *puVar4 = (uint)(puVar3);
  }
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0xe);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0xe);
  uVar1 = (undefined4)(fn_00475030((char *)(*(undefined4 *)(param_1 + 6))));
  fn_00478cc0((int)(uVar5 + 6), (uint)(uVar1));
  return uVar5;
}

uint fn_00478080(undefined4 *param_1)
{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  for (puVar3 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3) {
    if ((undefined4 *)puVar3[1] == param_1) goto LAB_004780d2;
  }
  puVar3 = (undefined4 *)((undefined4 *)0x0);
LAB_004780d2:
  if (puVar3 != (undefined4 *)0x0) {
    return puVar3[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar1 = (uint)(DAT_006daef6);
  puVar4 = (undefined4 *)((undefined4 *)
           (((int)param_1 +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar3[1] = (uint)(param_1);
  puVar3[2] = (uint)(uVar1);
  *puVar3 = (uint)(*puVar4);
  *puVar4 = (uint)(puVar3);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, param_1, 0xc);
  }
  DAT_006daef6 = (uint )(DAT_006daef6 + 0xc);
  uVar2 = (undefined4)(fn_004781b0((int *)(*param_1)));
  fn_00478cc0((int)(uVar1), (uint)(uVar2));
  return uVar1;
}

uint fn_004781b0(int *param_1)
{
  byte nativeFrame[68];
#define local_54 ((int *)(nativeFrame+0))
#define local_4a ((undefined1 *)(nativeFrame+10))
#define auStack_48 ((undefined1 *)(nativeFrame+12))
#define local_46 (*(undefined4 *)(nativeFrame+14))
#define local_42 (*(undefined4 *)(nativeFrame+18))
#define local_24 (*(int *)(nativeFrame+48))
#define local_20 (*(uint *)(nativeFrame+52))
#define local_1c (*(int * *)(nativeFrame+56))
#define local_18 (*(int * *)(nativeFrame+60))
#define local_14 (*(int * *)(nativeFrame+64))

  char cVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  char *pcVar10;
  iVar8 = (int)(0);
  do {
    *(undefined4 *)((int)local_54 + iVar8) = *(undefined4 *)(iVar8 + (int)param_1);
    *(undefined4 *)((int)local_54 + iVar8 + 4) = *(undefined4 *)(iVar8 + 4 + (int)param_1);
    *(undefined4 *)(((byte *)local_54+8) + iVar8) = *(undefined4 *)(iVar8 + 8 + (int)param_1);
    *(undefined4 *)(local_4a + iVar8 + 2) = *(undefined4 *)(iVar8 + 0xc + (int)param_1);
    iVar8 = (int)(iVar8 + 0x10);
  } while (iVar8 < 0x30);
  local_24 = (int)(param_1[0xc]);
  local_18 = (int *)(param_1);
  local_1c = (int *)(param_1);
  for (puVar9 = *(undefined4 **)
                 (DAT_006daf12 +
                 ((int)param_1 +
                  ((uint)param_1 >> 0x18) +
                  ((uint)param_1 >> 0x10 & 0xff) +
                  ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) & 0x3fff) * 4);
      puVar9 != (undefined4 *)0x0; puVar9 = (undefined4 *)*puVar9) {
    if ((int *)puVar9[1] == param_1) goto LAB_00478232;
  }
  puVar9 = (undefined4 *)((undefined4 *)0x0);
LAB_00478232:
  if (puVar9 != (undefined4 *)0x0) {
    return puVar9[2];
  }
  if (DAT_006daee5 != '\0') {
    for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
      AppendGListByte(&DAT_006daf1a, 0);
    }
  }
  uVar3 = (uint)(DAT_006daef6);
  local_14 = (int *)(param_1);
  local_20 = (uint)(DAT_006daef6);
  puVar7 = (undefined4 *)((undefined4 *)
           (((int)local_1c +
             ((uint)param_1 >> 0x18) +
             ((uint)param_1 >> 0x10 & 0xff) + ((uint)param_1 >> 8 & 0xff) + ((uint)param_1 & 0xff) &
            0x3fff) * 4 + DAT_006daf12));
  puVar9 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
  puVar9[1] = (uint)(param_1);
  puVar9[2] = (uint)(uVar3);
  *puVar9 = (uint)(*puVar7);
  *puVar7 = (uint)(puVar9);
  if (local_54[0] == 0) {
    CError_Internal(s_CPrec_c_0067dd1c, 0x430);
  }
  local_42 = (undefined4)(0);
  local_54[1] = 0;
  (*(uint *)local_4a) = 0;
  local_46 = (undefined4)(0);
  if (DAT_006daee5 != '\0') {
    CompilerTools_AppendGListData(&DAT_006daf1a, local_54, 0x34);
  }
  uVar3 = (uint)(local_20);
  DAT_006daef6 = (uint )(DAT_006daef6 + 0x34);
  iVar8 = (int)(*param_1);
  *(undefined4 *)(iVar8 + 4) = 1;
  fn_00478bd0((int)(local_20), (uint)(iVar8));
  { uint nativeSwitch1Value=(uint)((char)param_1[2]);
if(nativeSwitch1Value==(uint)('\0')) goto nativeSwitch1Case0;
if(nativeSwitch1Value==(uint)('\x01')) goto nativeSwitch1Case1;
if(nativeSwitch1Value==(uint)('\x02')) goto nativeSwitch1Case2;
if(nativeSwitch1Value==(uint)('\x03')) goto nativeSwitch1Case3;
goto nativeSwitch1End;

  nativeSwitch1Case0:
    uVar5 = (undefined4)(*(undefined4 *)((int)param_1 + 0x16));
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar4 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, uVar5, 0x104);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x104);
    fn_00478cc0((int)(uVar3 + 0x16), (uint)(uVar4));
    piVar2 = (int *)(*(int **)((int)param_1 + 0x2a));
    if (DAT_006daee5 != '\0') {
      for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
        AppendGListByte(&DAT_006daf1a, 0);
      }
    }
    uVar4 = (uint)(DAT_006daef6);
    if (DAT_006daee5 != '\0') {
      CompilerTools_AppendGListData(&DAT_006daf1a, piVar2, 0x12);
    }
    DAT_006daef6 = (uint )(DAT_006daef6 + 0x12);
    fn_00478cc0((int)(uVar3 + 0x2a), (uint)(uVar4));
    if (*piVar2 != 0) {
      uVar5 = (undefined4)(fn_004781b0((int *)(*piVar2)));
      fn_00478cc0((int)(uVar4), (uint)(uVar5));
    }
    iVar8 = (int)(piVar2[1]);
    *(undefined4 *)(iVar8 + 4) = 1;
    fn_00478bd0((int)(uVar4 + 4), (uint)(iVar8));
    iVar8 = (int)(piVar2[2]);
    if (iVar8 != 0) {
      iVar6 = (int)(-1);
      pcVar10 = (char *)((char *)piVar2[2]);
      do {
        if (iVar6 == 0) break;
        iVar6 = (int)(iVar6 - 1);
        cVar1 = (char)(*pcVar10);
        pcVar10 = (char *)(pcVar10 + 1);
      } while (cVar1 != '\0');
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar3 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        CompilerTools_AppendGListData(&DAT_006daf1a, iVar8, -iVar6 + -1);
      }
      DAT_006daef6 = (uint )(DAT_006daef6 + -iVar6 + -1);
      fn_00478cc0((int)(uVar4 + 8), (uint)(uVar3));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case1:
    if (*(int *)((int)param_1 + 0x22) != 0) {
      uVar5 = (undefined4)(fn_004781b0((int *)(*(int *)((int)param_1 + 0x22))));
      fn_00478cc0((int)(uVar3 + 0x22), (uint)(uVar5));
    }
    if (*(int *)((int)param_1 + 0x16) != 0) {
      uVar5 = (undefined4)(fn_004781b0((int *)(*(int *)((int)param_1 + 0x16))));
      fn_00478cc0((int)(uVar3 + 0x16), (uint)(uVar5));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case2:
    if (*(int *)((int)param_1 + 0x16) != 0) {
      uVar5 = (undefined4)(fn_004781b0((int *)(*(int *)((int)param_1 + 0x16))));
      fn_00478cc0((int)(uVar3 + 0x16), (uint)(uVar5));
    }
    goto nativeSwitch1End;
  nativeSwitch1Case3:
    if (*(int *)((int)param_1 + 0x16) != 0) {
      uVar5 = (undefined4)(fn_004781b0((int *)(*(int *)((int)param_1 + 0x16))));
      fn_00478cc0((int)(uVar3 + 0x16), (uint)(uVar5));
    }
    iVar8 = (int)(*(int *)(*(int *)((int)param_1 + 0x26) + 4));
    *(undefined4 *)(iVar8 + 4) = 1;
    fn_00478bd0((int)(uVar3 + 0x26), (uint)(iVar8));

nativeSwitch1End:;
}
  return local_20;
}
#undef local_54
#undef local_4a
#undef auStack_48
#undef local_46
#undef local_42
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14


void fn_00478580(void)
{
  byte nativeFrame[4];
#define local_14 (*(int *)(nativeFrame+0))

  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  local_14 = (int)(0);
  do {
    uVar9 = (uint)(DAT_006daef6);
    for (puVar1 = (undefined4 *)(&DAT_0070c6a0)[local_14]; DAT_006daef6 = uVar9,
        puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
      uVar2 = (uint)(puVar1[2]);
      if (uVar2 != 0) {
        puVar6 = (undefined4 *)((undefined4 *)
                 (((uVar2 & 0xff) + uVar2 + (uVar2 >> 8 & 0xff) + (uVar2 >> 0x10 & 0xff) +
                   (uVar2 >> 0x18) & 0x3fff) * 4 + DAT_006daf12));
        puVar4 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
        puVar4[1] = (uint)(uVar2);
        puVar4[2] = (uint)(uVar9);
        *puVar4 = (uint)(*puVar6);
        *puVar6 = (uint)(puVar4);
        iVar8 = (int)(puVar1[3]);
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, puVar1[2], iVar8 + 2);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + iVar8 + 2);
      }
      uVar9 = (uint)(DAT_006daef6);
    }
    local_14 = (int)(local_14 + 1);
  } while (local_14 < 0x800);
  iVar8 = (int)(0);
  do {
    piVar7 = (int *)((int *)(&DAT_0070c6a0)[iVar8]);
    if (piVar7 != (int *)0x0) {
      if (DAT_006daee5 != '\0') {
        for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
          AppendGListByte(&DAT_006daf1a, 0);
        }
      }
      uVar9 = (uint)(DAT_006daef6);
      if (DAT_006daee5 != '\0') {
        *(uint *)(DAT_006daf16 + 0x20da + iVar8 * 4) = DAT_006daef6;
      }
      while( true ) {
        if (*(ushort *)(piVar7 + 7) == 0) {
          iVar10 = (int)(0x20);
        }
        else {
          iVar10 = (int)((*(ushort *)(piVar7 + 7) - 2) * 4 + 0x24);
        }
        if (DAT_006daee5 != '\0') {
          CompilerTools_AppendGListData(&DAT_006daf1a, piVar7, iVar10);
        }
        DAT_006daef6 = (uint )(DAT_006daef6 + iVar10);
        iVar10 = (int)(piVar7[1]);
        *(undefined4 *)(iVar10 + 4) = 1;
        fn_00478bd0((int)(uVar9 + 4), (uint)(iVar10));
        if (piVar7[2] != 0) {
          fn_00478bd0((int)(uVar9 + 8), (uint)(piVar7[2]));
        }
        iVar10 = (int)(1);
        if (*(ushort *)(piVar7 + 7) > 1) {
          do {
            iVar3 = (int)(piVar7[iVar10 + 7]);
            *(undefined4 *)(iVar3 + 4) = 1;
            fn_00478bd0((int)(uVar9 + 0x20 + (iVar10 - 1U) * 4), (uint)(iVar3));
            iVar10 = (int)(iVar10 + 1);
          } while (iVar10 < (int)(uint)*(ushort *)(piVar7 + 7));
        }
        if (piVar7[4] != 0) {
          uVar5 = (undefined4)(fn_004781b0((int *)(piVar7[4])));
          fn_00478cc0((int)(uVar9 + 0x10), (uint)(uVar5));
        }
        piVar7 = (int *)((int *)*piVar7);
        if (piVar7 == (int *)0x0) break;
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar2 = (uint)(DAT_006daef6);
        fn_00478cc0((int)(uVar9), (uint)(DAT_006daef6));
        uVar9 = (uint)(uVar2);
      }
    }
    iVar8 = (int)(iVar8 + 1);
  } while (iVar8 < 0x800);
  return;
}
#undef local_14


void fn_004787f0(void)
{
  byte nativeFrame[4];
#define local_1c (*(int *)(nativeFrame+0))

  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  uint uVar8;
  char *pcVar9;
  if (DAT_006daee5 == '\0') {
    local_1c = (int)(0);
    do {
      piVar7 = (int *)(*(int **)(DAT_00710144 + local_1c * 4));
      if (piVar7 != (int *)0x0) {
        uVar8 = (uint)(DAT_006daef6);
        if (DAT_006daee5 != '\0') {
          while (DAT_006daef6 = uVar8, (uVar8 & 3) != 0) {
            AppendGListByte(&DAT_006daf1a, 0);
            DAT_006daef6 = (uint )(DAT_006daef6 + 1);
            uVar8 = (uint)(DAT_006daef6);
          }
        }
        do {
          puVar4 = (undefined4 *)((undefined4 *)
                   (((int)piVar7 +
                     ((uint)piVar7 >> 0x18) +
                     ((uint)piVar7 >> 0x10 & 0xff) +
                     ((uint)piVar7 >> 8 & 0xff) + ((uint)piVar7 & 0xff) & 0x3fff) * 4 + DAT_006daf12
                   ));
          puVar3 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
          puVar3[1] = (uint)(piVar7);
          puVar3[2] = (uint)(uVar8);
          *puVar3 = (uint)(*puVar4);
          *puVar4 = (uint)(puVar3);
          if (DAT_006daee5 != '\0') {
            AppendGListLong(&DAT_006daf1a, 0);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 4);
          if (DAT_006daee5 != '\0') {
            AppendGListLong(&DAT_006daf1a, 0);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 4);
          if (DAT_006daee5 != '\0') {
            AppendGListWord(&DAT_006daf1a, (int)(short)piVar7[2]);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 2);
          iVar5 = (int)(-1);
          pcVar9 = (char *)((char *)((int)piVar7 + 10));
          do {
            if (iVar5 == 0) break;
            iVar5 = (int)(iVar5 - 1);
            cVar1 = (char)(*pcVar9);
            pcVar9 = (char *)(pcVar9 + 1);
          } while (cVar1 != '\0');
          if (DAT_006daee5 != '\0') {
            CompilerTools_AppendGListData(&DAT_006daf1a, (int)piVar7 + 10, -iVar5 + -1);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + -iVar5 + -1);
          piVar7 = (int *)((int *)*piVar7);
          if (piVar7 == (int *)0x0) break;
          if (DAT_006daee5 != '\0') {
            for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
              AppendGListByte(&DAT_006daf1a, 0);
            }
          }
          uVar2 = (uint)(DAT_006daef6);
          fn_00478cc0((int)(uVar8), (uint)(DAT_006daef6));
          uVar8 = (uint)(uVar2);
        } while( true );
      }
      local_1c = (int)(local_1c + 1);
    } while (local_1c < 0x800);
  }
  else {
    local_1c = (int)(0);
    do {
      for (puVar3 = *(undefined4 **)(DAT_00710144 + local_1c * 4); puVar3 != (undefined4 *)0x0 &&
          (puVar3[1] == 0); puVar3 = (undefined4 *)*puVar3) {
      }
      if (puVar3 != (undefined4 *)0x0) {
        if (DAT_006daee5 != '\0') {
          for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
            AppendGListByte(&DAT_006daf1a, 0);
          }
        }
        uVar8 = (uint)(DAT_006daef6);
        *(uint *)(DAT_006daf16 + 0xda + local_1c * 4) = DAT_006daef6;
        do {
          puVar6 = (undefined4 *)((undefined4 *)
                   (((int)puVar3 +
                     ((uint)puVar3 >> 0x18) +
                     ((uint)puVar3 >> 0x10 & 0xff) +
                     ((uint)puVar3 >> 8 & 0xff) + ((uint)puVar3 & 0xff) & 0x3fff) * 4 + DAT_006daf12
                   ));
          puVar4 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(0xc));
          puVar4[1] = (uint)(puVar3);
          puVar4[2] = (uint)(uVar8);
          *puVar4 = (uint)(*puVar6);
          *puVar6 = (uint)(puVar4);
          if (DAT_006daee5 != '\0') {
            AppendGListLong(&DAT_006daf1a, 0);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 4);
          if (DAT_006daee5 != '\0') {
            AppendGListLong(&DAT_006daf1a, 0);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 4);
          if (DAT_006daee5 != '\0') {
            AppendGListWord(&DAT_006daf1a, (int)*(short *)(puVar3 + 2));
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + 2);
          iVar5 = (int)(-1);
          pcVar9 = (char *)((char *)((int)puVar3 + 10));
          do {
            if (iVar5 == 0) break;
            iVar5 = (int)(iVar5 - 1);
            cVar1 = (char)(*pcVar9);
            pcVar9 = (char *)(pcVar9 + 1);
          } while (cVar1 != '\0');
          if (DAT_006daee5 != '\0') {
            CompilerTools_AppendGListData(&DAT_006daf1a, (int)puVar3 + 10, -iVar5 + -1);
          }
          DAT_006daef6 = (uint )(DAT_006daef6 + -iVar5 + -1);
          for (puVar3 = (undefined4 *)*puVar3; puVar3 != (undefined4 *)0x0 && (puVar3[1] == 0);
              puVar3 = (undefined4 *)*puVar3) {
          }
          if (puVar3 == (undefined4 *)0x0) break;
          if (DAT_006daee5 != '\0') {
            for (; (DAT_006daef6 & 3) != 0; DAT_006daef6 = DAT_006daef6 + 1) {
              AppendGListByte(&DAT_006daf1a, 0);
            }
          }
          uVar2 = (uint)(DAT_006daef6);
          fn_00478cc0((int)(uVar8), (uint)(DAT_006daef6));
          uVar8 = (uint)(uVar2);
        } while( true );
      }
      local_1c = (int)(local_1c + 1);
    } while (local_1c < 0x800);
  }
  return;
}
#undef local_1c


void fn_00478bb0(undefined4 param_1, int param_2)
{
  *(undefined4 *)(param_2 + 4) = 1;
  fn_00478bd0((int)(param_1), (uint)(param_2));
  return;
}

void fn_00478bd0(int param_1, uint param_2)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  if (DAT_006daee5 != '\0') {
    for (puVar2 = *(undefined4 **)
                   (DAT_006daf12 +
                   ((param_2 & 0xff) + param_2 + (param_2 >> 8 & 0xff) + (param_2 >> 0x10 & 0xff) +
                    (param_2 >> 0x18) & 0x3fff) * 4); puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)*puVar2) {
      if (puVar2[1] == param_2) goto LAB_00478c2d;
    }
    puVar2 = (undefined4 *)((undefined4 *)0x0);
LAB_00478c2d:
    if (puVar2 == (undefined4 *)0x0) {
      CError_Internal(s_CPrec_c_0067dd1c, 0x24f);
    }
    puVar1 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(8));
    puVar1[1] = (uint)(param_1);
    *puVar1 = (uint)(DAT_006daf0e);
    DAT_006daf0e = (uint )(puVar1);
    if ((puVar1[1] & 0x80000001) != 0) {
      CError_Internal(s_CPrec_c_0067dd1c, 0x254);
    }
    param_1 = (int)(param_1 - _DAT_006daef2);
    if ((param_1 < 0) || (DAT_006daf1e < param_1)) {
      CError_Internal(s_CPrec_c_0067dd1c, 600);
    }
    *(undefined4 *)(*DAT_006daf1a + param_1) = puVar2[2];
  }
  return;
}

void fn_00478cc0(int param_1, uint param_2)
{
  int iVar1;
  undefined4 *puVar2;
  if (DAT_006daee5 != '\0') {
    puVar2 = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(8));
    puVar2[1] = (uint)(param_1);
    if ((puVar2[1] & 0x80000001) != 0) {
      CError_Internal(s_CPrec_c_0067dd1c, 0x22b);
    }
    if ((int)param_2 < 0) {
      if (DAT_006daefa <= (int)~param_2) {
        CError_Internal(s_CPrec_c_0067dd1c, 0x231);
      }
      iVar1 = (int)(~param_2 * 0xc);
      *puVar2 = (uint)(*(undefined4 *)(iVar1 + 8 + DAT_006daf0a));
      param_2 = (uint)(0);
      *(undefined4 **)(iVar1 + 8 + DAT_006daf0a) = puVar2;
    }
    else {
      *puVar2 = (uint)(DAT_006daf0e);
      DAT_006daf0e = (uint )(puVar2);
    }
    param_1 = (int)(param_1 - _DAT_006daef2);
    if ((param_1 < 0) || (DAT_006daf1e < param_1)) {
      CError_Internal(s_CPrec_c_0067dd1c, 0x23d);
    }
    *(uint *)(*DAT_006daf1a + param_1) = param_2;
  }
  return;
}

void fn_00478d90(void)
{
  bool bVar1;
  undefined4 *in_EAX;
  int iVar2;
  iVar2 = (int)(0);
  bVar1 = true;
  while (bVar1) {
    iVar2 = (int)(iVar2 + 0x44);
    in_EAX = (undefined4 *)((undefined4 *)CompilerTools_AllocatePool(iVar2 * 4));
    bVar1 = false;
    DAT_006daefa = (int )(iVar2);
    DAT_006daefe = (uint )(in_EAX);
  }
  *in_EAX = DAT_007101c4;
  in_EAX[1] = (uint)(&DAT_00725d96);
  in_EAX[2] = (uint)(&DAT_00699c1c);
  in_EAX[3] = (uint)(&DAT_00699c24);
  in_EAX[4] = (uint)(&DAT_00699c2c);
  in_EAX[5] = (uint)(&DAT_00699c34);
  in_EAX[6] = (uint)(&DAT_00699c3c);
  in_EAX[7] = (uint)(&DAT_00699c44);
  in_EAX[8] = (uint)(&DAT_00699c4c);
  in_EAX[9] = (uint)(&DAT_00699c54);
  in_EAX[10] = (uint)(&DAT_00699c5c);
  in_EAX[0xb] = (uint)(&DAT_00699c64);
  in_EAX[0xc] = (uint)(&DAT_00699c6c);
  in_EAX[0xd] = (uint)(&DAT_00699c74);
  in_EAX[0xe] = (uint)(&DAT_00699c7c);
  in_EAX[0xf] = (uint)(&DAT_00699c84);
  in_EAX[0x10] = (uint)(&DAT_00699c8c);
  in_EAX[0x11] = (uint)(&DAT_00699c94);
  in_EAX[0x12] = (uint)(&DAT_00699c9c);
  in_EAX[0x13] = (uint)(&DAT_007037c0);
  in_EAX[0x14] = (uint)(&DAT_0070bb08);
  in_EAX[0x15] = (uint)(&DAT_006771c2);
  in_EAX[0x16] = (uint)(&DAT_006771bc);
  in_EAX[0x17] = (uint)(&DAT_00725d96);
  in_EAX[0x18] = (uint)(&DAT_006771c8);
  in_EAX[0x19] = (uint)(0x6771d6);
  in_EAX[0x1a] = (uint)(&DAT_006771e4);
  in_EAX[0x1b] = (uint)(&DAT_0071726c);
  in_EAX[0x1c] = (uint)(&DAT_0069a15c);
  in_EAX[0x1d] = (uint)(&DAT_0069a16e);
  in_EAX[0x1e] = (uint)(&DAT_0069a180);
  in_EAX[0x1f] = (uint)(&DAT_0069a192);
  in_EAX[0x20] = (uint)(&DAT_0069a1a4);
  in_EAX[0x21] = (uint)(&DAT_0069a1b6);
  in_EAX[0x22] = (uint)(&DAT_0069a1c8);
  in_EAX[0x23] = (uint)(&DAT_0069a1da);
  in_EAX[0x24] = (uint)(&DAT_0069a1ec);
  in_EAX[0x25] = (uint)(&DAT_0069a1fe);
  in_EAX[0x26] = (uint)(&DAT_0069a210);
  in_EAX[0x27] = (uint)(&DAT_00699ca4);
  in_EAX[0x28] = (uint)(DAT_0071092c);
  in_EAX[0x29] = (uint)(DAT_007108c0);
  in_EAX[0x2a] = (uint)(DAT_00711b24);
  in_EAX[0x2b] = (uint)(DAT_00716d3c);
  in_EAX[0x2c] = (uint)(DAT_0071081c);
  in_EAX[0x2d] = (uint)(DAT_007107b8);
  in_EAX[0x2e] = (uint)(DAT_007102c8);
  in_EAX[0x2f] = (uint)(DAT_007107ac);
  in_EAX[0x30] = (uint)(DAT_00710340);
  in_EAX[0x31] = (uint)(DAT_00710928);
  in_EAX[0x32] = (uint)(DAT_007108b4);
  in_EAX[0x33] = (uint)(DAT_00716cac);
  in_EAX[0x34] = (uint)(DAT_00711bb8);
  in_EAX[0x35] = (uint)(DAT_00715c58);
  in_EAX[0x36] = (uint)(DAT_00710858);
  in_EAX[0x37] = (uint)(DAT_00711b80);
  in_EAX[0x38] = (uint)(DAT_00711b00);
  in_EAX[0x39] = (uint)(DAT_00711b1c);
  in_EAX[0x3a] = (uint)(DAT_00716c98);
  in_EAX[0x3b] = (uint)(DAT_00715c18);
  in_EAX[0x3c] = (uint)(DAT_00716d68);
  in_EAX[0x3d] = (uint)(DAT_00716ce4);
  in_EAX[0x3e] = (uint)(DAT_00716d60);
  in_EAX[0x3f] = (uint)(DAT_00716cd8);
  in_EAX[0x40] = (uint)(DAT_00710330);
  in_EAX[0x41] = (uint)(DAT_00716c1c);
  in_EAX[0x42] = (uint)(DAT_00715c00);
  in_EAX[0x43] = (uint)(DAT_007109c4);
  return;
}

void CleanupPrecompiler(void)
{
  if (DAT_006daf2a != 0) {
    FUN_0044d730(DAT_006daf2a);
    DAT_006daf2a = (uint )(0);
  }
  if (DAT_006daf1a != 0) {
    FreeGList(&DAT_006daf1a);
  }
  return;
}

void SetupPrecompiler(void)
{
  DAT_006daf2a = (uint )(0);
  DAT_006daf1a = (uint *)(0);
  DAT_006daf16 = (uint )(0);
  DAT_006daee6 = (uint )(0);
  DAT_006daee0 = (uint )(0);
  DAT_006daedc = (uint )(0);
  return;
}
