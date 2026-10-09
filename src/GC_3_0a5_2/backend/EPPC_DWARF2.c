/* EPPC_DWARF2.c: recovered GC 3.0a5.2 DWARF2 family. */
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char bool;
#define true 1
#define false 0
undefined4 * typeCache[512];
int * abbreviationCache[37];
int abbreviationAttributes[160];
static char literal_006b49de[] = ".dwarf.";
#define native_006b49de (literal_006b49de[0])
char native_006b4af6 = 1;
static char literal_006b4b07[] = "main";
#define native_006b4b07 (literal_006b4b07[0])
static char literal_006b4b27[] = "::";
#define native_006b4b27 (literal_006b4b27[0])
char dwarfPath006e9870[1024];
#define native_006e9870 (dwarfPath006e9870[0])
#define native_006e9871 (dwarfPath006e9870[1])
char dwarfPath006e9c70[1024];
#define native_006e9c70 (dwarfPath006e9c70[0])
#define native_006ea078 (typeCache[0])
#define native_006ea07c (typeCache[1])
#define native_006ea080 (typeCache[2])
#define native_006ea084 (typeCache[3])
#define native_006ea088 (typeCache[4])
#define native_006ea08c (typeCache[5])
#define native_006ea090 (typeCache[6])
#define native_006ea094 (typeCache[7])
int native_006ea878;
int native_006ea87c;
int native_006ea884;
int native_006ea88c;
int native_006ea890;
int native_006ea894;
#define native_006ea89c (abbreviationCache[0])
#define native_006ea8a0 (abbreviationCache[1])
#define native_006ea8a4 (abbreviationCache[2])
#define native_006ea8a8 (abbreviationCache[3])
#define native_006ea8ac (abbreviationCache[4])
#define native_006ea8b0 (abbreviationCache[5])
#define native_006ea8b4 (abbreviationCache[6])
int native_006ea934;
char native_006ea938;
int native_006ea93a;
int native_006ea93e;
#define native_006ea946 (abbreviationAttributes[0])
#define native_006ea94a (abbreviationAttributes[1])
#define native_006ea94e (abbreviationAttributes[2])
#define native_006ea952 (abbreviationAttributes[3])
#define native_006ea956 (abbreviationAttributes[4])
#define native_006ea95a (abbreviationAttributes[5])
#define native_006ea95e (abbreviationAttributes[6])
#define native_006ea962 (abbreviationAttributes[7])
#define native_006ea966 (abbreviationAttributes[8])
#define native_006ea96a (abbreviationAttributes[9])
#define native_006ea96e (abbreviationAttributes[10])
#define native_006ea972 (abbreviationAttributes[11])
#define native_006ea976 (abbreviationAttributes[12])
#define native_006ea97a (abbreviationAttributes[13])
#define native_006ea97e (abbreviationAttributes[14])
#define native_006ea982 (abbreviationAttributes[15])
int native_006eabc6;
int native_006eabca;
int native_006eabce;
int native_006eabd2;
int native_006eabd6;
int native_006eabde;
int native_006eabee;
int native_006eabf2;
int native_006eabf6;
int native_006eabfa;
int native_006eabfe;
undefined4 * native_006eac02;
int native_006eac06;
int native_006eac0e;
int native_006eac12;
int * native_006eac16;
int native_006eac1a;
undefined4 * native_006eac22;
undefined4 * native_006eac26;
char native_006eac2a;
int native_006eac2c;
char native_006eac30;
undefined4 * native_006eac32;
extern int native_007037c0;
extern int native_0070bb08;
extern char ** native_0070bc20;
extern int native_0070bc24;
extern int native_0070efe8;
extern int native_0070eff8;
extern char native_0070f019;
extern char native_0070f054;
extern char native_0070f06e;
extern char native_0070f1a8;
extern char native_0070f287;
extern char native_0070f28d;
extern int native_0071008c;
extern int native_00710110;
extern int native_00710124;
extern int native_00710220;
extern int native_00710324;
extern int native_00710710;
extern int native_00710750;
extern int native_007107f4;
extern int * native_007108c8;
extern int native_007108d0;
extern int native_007108dc;
extern int native_00710924;
extern int native_00710b3c;
extern int native_00711b64;
extern int native_00711be4;
extern int * native_00715bfc;
extern int native_00715c48;
extern int native_00715c4c;
extern int native_00715c50;
extern int native_00715c64;
extern undefined4 * native_00716cc0;
extern int * native_00716ccc;
extern int native_00716cd0;
extern int * native_00716ce8;
extern int * native_00716d50;
extern int native_00716d7c;
extern short native_007172bc;
extern char native_00725eda;
int native_006ea880;
int native_006ea888;
int native_006ea898;
int native_006ea930;
int native_006ea942;
int native_006eabda;
int native_006eabe2;
int native_006eac1e;
extern int native_00710380;
static char literal_006b4af7[] = "EPPC_DWARF2.c";
static char literal_006b4b0f[] = "MW EABI PPC C-Compiler";
static char literal_006b4ae8[] = ".debug_abbrev";
static char literal_006b4ac9[] = ".debug_aranges";
static char literal_006b4a65[] = ".debug_info";
static char literal_006b4a92[] = ".debug_line";
static char literal_006b4abe[] = ".debug_loc";
static char literal_006b4aaf[] = ".debug_macinfo";
static char literal_006b4ad8[] = ".debug_pubnames";
static char literal_006b49e6[] = ".dwarf_header.";
static char literal_006b49c5[] = ".dwarf_line.";
static char literal_006b4a4f[] = ".dwarf_line_prologue.";
static char literal_006b49d2[] = ".dwarf_loc.";
static char literal_006b4a42[] = ".dwarf_null.";
static char literal_006b4a01[] = ".dwarf_pubnames.";
static char literal_006b4a2c[] = ".dwarf_pubnames_null.";
static char literal_006b4a12[] = ".dwarf_pubnames_prologue.";
static char literal_006b49f5[] = ".dwarf_tcu.";
static char literal_006b49b8[] = ".dwarf_type.";
static char literal_006b4a71[] = ".rela.debug_info";
static char literal_006b4a9e[] = ".rela.debug_line";
static char literal_006b4a82[] = ".rela.debug_loc";
extern char * strcpy(char *, char *);
extern char * strncpy(char *, char *, int);
extern int strcmp(byte *, byte *);
extern char * strchr(char *, char);
extern void fn_00447910(int *);
extern void fn_0044cfe0(int);
extern void fn_0044d0a0(int);
extern unsigned char fn_00452fe0(int);
extern unsigned char fn_00454260(char *);
extern undefined1 CParser_IsNullOrAtOrDollarPrefixedName(int);
extern void fn_00455ea0(char *);
extern void fn_004561d0(undefined4);
extern void CError_Internal(undefined4, undefined4);
extern undefined1 * fn_0045df60(undefined4);
extern undefined1 * fn_0045ede0(undefined4, undefined4, char);
extern undefined4 CTool_EndianConvertWord32(undefined4);
extern void memclrw(undefined1 *, int);
extern int CompilerTools_AllocatePool(int);
extern int galloc(int);
extern undefined4 * GetHashNameNode(char *);
extern undefined4 * fn_0046d340(char *);
extern void fn_0046d530(undefined4 *, char *);
extern void fn_0046d5a0(undefined4 *, char *);
extern void fn_004c3010(void);
extern void fn_004da500(int);
extern void DWARF_CreateObjectDebugEntry(int);
extern void CABI_ReverseBitField(int);
extern void fn_00554830(int, int, undefined1);
extern void fn_00554850(int, int, ushort);
extern void fn_00554890(int, int, uint);
extern undefined4 fn_005548f0(int, char *);
extern int fn_00554930(int, undefined1);
extern int fn_00554960(int, undefined2);
extern int fn_005549c0(int, uint);
extern void fn_00554a70(undefined4, int, undefined4, undefined4, undefined4);
extern void fn_00555920(void);
extern int fn_00555930(char *, undefined4, undefined4);
extern undefined4 COptimizer_GetFunctionObject(int);
extern undefined4 Registers_GetInfo(int);
extern int fn_0057a790(int);
extern int fn_00587230(undefined4);
extern void fn_005cce90(undefined4, undefined4 *, undefined4 *, undefined4 *);
extern void fn_005cceb0(int *, undefined4 *);
extern unsigned int fn_005ccee0(undefined4);
extern int fn_005cd470(undefined4, int, char, undefined4, undefined4);
extern unsigned int fn_005cd660(undefined4);
extern int * fn_005cd6a0(undefined4, undefined4, byte, undefined4, undefined4, int);
extern void fn_005ce570(int);
extern void fn_0046d190(void);
extern int fn_005cd510(int);
extern undefined4 * fn_005cd5f0(int);
void fn_005ce5e0(void);
void fn_005cefc0(void);
void fn_005cf400(int param_1, undefined4 param_2, undefined4 param_3);
void fn_005cf6d0(int param_1, int *param_2, undefined4 param_3, int param_4, undefined4 param_5,
                 undefined4 param_6);
int * fn_005d0020(void);
void fn_005d00e0(undefined4 *param_1, undefined4 param_2, undefined4 param_3, char param_4);
undefined4 fn_005d0320(int param_1);
void fn_005d03a0(int param_1, undefined4 param_2);
void fn_005d05a0(int param_1);
void fn_005d0820(int param_1);
void fn_005d0b20(void);
void fn_005d0ce0(void);
void fn_005d10f0(int param_1, char param_2);
void fn_005d1190(uint param_1, int param_2, int param_3, char param_4, char param_5);
void fn_005d1400(int param_1);
void fn_005d2440(int param_1);
undefined4 fn_005d2c80(int param_1);
void fn_005d2ce0(int param_1);
void fn_005d5930(void);
int fn_005d5b00(char param_1);
int fn_005d5f30(char *param_1, char param_2);
int fn_005d6010(int param_1, int param_2);
int fn_005d63f0(int param_1, int param_2);
undefined4 fn_005d6b40(void);
undefined4 fn_005d6c80(void);
void fn_005d6dd0(undefined4 param_1, int param_2, uint param_3);
void fn_005d6e70(int param_1);
int fn_005d6ff0(int param_1);
int fn_005d7200(int param_1);
void fn_005d7400(int param_1, char param_2, int param_3);
int fn_005d7640(char *param_1);
void fn_005d7870(int param_1);
int fn_005d7a10(char *param_1);
int fn_005d7de0(int param_1);
int fn_005d7f70(int param_1);
void fn_005d80f0(undefined4 param_1, undefined4 param_2, int param_3);
undefined4 * fn_005d8180(undefined1 *param_1);
int fn_005d82b0(undefined4 *param_1, int param_2);
void fn_005d8330(undefined4 *param_1);
void fn_005d84f0(int param_1);
void fn_005d85a0(void);
void fn_005d85c0(void);
void fn_005d8640(undefined4 param_1, char *param_2);
bool fn_005d86b0(int param_1, int param_2);

void fn_005ce5e0(void)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  undefined1 local_6c [16];
  undefined1 auStack_5c [16];
  undefined1 auStack_4c [16];
  undefined1 auStack_3c [16];
  int local_2c;
  int iStack_28;
  uint uStack_24;
  int iStack_20;
  int local_1c;
  int *local_18;
  undefined4 *puStack_14;

  native_006eac12 = (int)(native_006eac0e);
  if ((native_0070f287 == '\0') || (native_006eac0e == 0)) {
    return;
  }
  fn_005d85c0();
  for (puVar2 = (undefined4*)(native_006eac06); puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
    if (*(char *)(puVar2 + 3) == '\0') {
      fn_005d6e70((int)(puVar2));
    }
  }
  local_18 = (int*)((int *)((int *)native_006eac12)[1]);
  fn_0046d190();
  fn_005549c0((int)(native_006eabfe), (uint)(0));
  fn_00554960((int)(native_006eabfe), (undefined2)(2));
  fn_005549c0((int)(native_006eabfe), (uint)(0));
  fn_00554930((int)(native_006eabfe), (undefined1)(4));
  local_1c = (int)(*(undefined4 *)(native_006eabfe + 0x2c));
  local_2c = (int)(native_006eabfe);
  native_0070bc24 = (int)(0);
  fn_00455ea0((char *)(local_6c));
  fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_6c));
  fn_0044cfe0((int)(native_0070bc20));
  iVar4 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
  fn_0044d0a0((int)(native_0070bc20));
  iVar7 = (int)(-1);
  pcVar10 = (char*)(literal_006b49e6);
  do {
    if (iVar7 == 0) break;
    iVar7 = (int)(iVar7 - 1);
    cVar1 = (char)(*pcVar10);
    pcVar10 = (char*)(pcVar10 + 1);
  } while (cVar1 != '\0');
  iVar7 = (int)(-iVar7 - 2);
  iVar8 = (int)(-1);
  pcVar10 = (char*)((char *)(iVar4 + 10));
  do {
    if (iVar8 == 0) break;
    iVar8 = (int)(iVar8 - 1);
    cVar1 = (char)(*pcVar10);
    pcVar10 = (char*)(pcVar10 + 1);
  } while (cVar1 != '\0');
  iVar9 = (int)(-iVar8 - 2);
  iVar5 = (int)(galloc((int)(-iVar8 + -1 + iVar7)));
  iVar8 = (int)(0);
  for (; iVar7 != 0; iVar7 = iVar7 - 1) {
    *(char *)(iVar5 + iVar8) = literal_006b49e6[iVar8];
    iVar8 = (int)(iVar8 + 1);
  }
  iVar7 = (int)(0);
  for (; iVar9 != 0; iVar9 = iVar9 - 1) {
    *(undefined1 *)(iVar5 + iVar8) = *(undefined1 *)(iVar4 + 10 + iVar7);
    iVar8 = (int)(iVar8 + 1);
    iVar7 = (int)(iVar7 + 1);
  }
  *(undefined1 *)(iVar5 + iVar8) = 0;
  fn_005cd6a0((undefined4)(iVar5), (undefined4)(local_2c), (byte)(0), (undefined4)(1), (undefined4)(local_1c), (int)(0));
  fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(6), (undefined4)(native_00716cd0), (undefined4)(0));
  fn_005d0ce0();
  for (piVar3 = (int*)(native_006eac1a); piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
    native_006eac12 = (int)(piVar3);
    if ((short)piVar3[3] == 2) {
      iVar4 = (int)(piVar3[1]);
      if (*piVar3 != 0) {
        *(undefined4 *)(iVar4 + 0x52) = *(undefined4 *)(*piVar3 + 4);
      }
      fn_005d05a0((int)(iVar4));
    }
    for (puVar2 = (undefined4*)((undefined4 *)piVar3[1]); puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)*puVar2) {
      fn_005d2ce0((int)(puVar2));
    }
    for (puVar2 = (undefined4*)((undefined4 *)piVar3[1]); puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)*puVar2) {
      fn_005d1400((int)(puVar2));
    }
    for (puVar2 = (undefined4*)((undefined4 *)piVar3[1]); puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)*puVar2) {
      fn_005d2440((int)(puVar2));
    }
  }
  native_006eac12 = (int)(native_006eac0e);
  iVar4 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar4), (int)(0x7a));
  *(undefined2 *)(iVar4 + 0x14) = 0xffff;
  piVar3 = (int*)(native_006eac12);
  if ((int *)((int *)native_006eac12)[2] == (int *)0x0) {
    ((int *)native_006eac12)[2] = iVar4;
    piVar3[1] = (int)(piVar3[2]);
  }
  else {
    *(int *)((int *)native_006eac12)[2] = iVar4;
    *(int *)(iVar4 + 4) = ((int *)native_006eac12)[2];
    ((int *)native_006eac12)[2] = iVar4;
  }
  piVar3 = (int*)(native_006eac12);
  ((int *)native_006eac12)[2] = iVar4;
  iVar4 = (int)(piVar3[2]);
  fn_005d2ce0((int)(iVar4));
  local_1c = (int)(*(undefined4 *)(iVar4 + 8));
  iStack_28 = (int)(native_006eabfe);
  native_0070bc24 = (int)(0);
  fn_00455ea0((char *)(auStack_5c));
  fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(auStack_5c));
  fn_0044cfe0((int)(native_0070bc20));
  iVar4 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
  fn_0044d0a0((int)(native_0070bc20));
  iVar7 = (int)(-1);
  pcVar10 = (char*)(literal_006b4a42);
  do {
    if (iVar7 == 0) break;
    iVar7 = (int)(iVar7 - 1);
    cVar1 = (char)(*pcVar10);
    pcVar10 = (char*)(pcVar10 + 1);
  } while (cVar1 != '\0');
  iVar7 = (int)(-iVar7 - 2);
  iVar8 = (int)(-1);
  pcVar10 = (char*)((char *)(iVar4 + 10));
  do {
    if (iVar8 == 0) break;
    iVar8 = (int)(iVar8 - 1);
    cVar1 = (char)(*pcVar10);
    pcVar10 = (char*)(pcVar10 + 1);
  } while (cVar1 != '\0');
  iVar9 = (int)(-iVar8 - 2);
  iVar5 = (int)(galloc((int)(-iVar8 + -1 + iVar7)));
  iVar8 = (int)(0);
  for (; iVar7 != 0; iVar7 = iVar7 - 1) {
    *(char *)(iVar5 + iVar8) = literal_006b4a42[iVar8];
    iVar8 = (int)(iVar8 + 1);
  }
  iVar7 = (int)(0);
  for (; iVar9 != 0; iVar9 = iVar9 - 1) {
    *(undefined1 *)(iVar5 + iVar8) = *(undefined1 *)(iVar4 + 10 + iVar7);
    iVar8 = (int)(iVar8 + 1);
    iVar7 = (int)(iVar7 + 1);
  }
  *(undefined1 *)(iVar5 + iVar8) = 0;
  iStack_28 = (int)(fn_005cd6a0((undefined4)(iVar5), (undefined4)(iStack_28), (byte)(0), (undefined4)(1), (undefined4)(1), (int)(local_1c)));
  for (piVar3 = (int*)(native_006eac1a); piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
    native_006eac12 = (int)(piVar3);
    if ((short)piVar3[3] == 2) {
      iVar4 = (int)(piVar3[1]);
      if (*(int *)(iVar4 + 0x6a) == 0) {
        iVar7 = (int)(*(int *)(iVar4 + 0xc));
      }
      else {
        iVar7 = (int)((*(int *)(*(int *)(iVar4 + 0x6a) + 8) - *(int *)(iVar4 + 8)) + 1);
      }
      iVar8 = (int)(*(int *)(iVar4 + 0x56));
      iVar9 = (int)(iVar7);
      if (native_006b4af6 == '\0') {
        iVar9 = (int)(0);
      }
      fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar8), (undefined4)(*(undefined4 *)(iVar4 + 0x2a)), (undefined4)(iVar9));
      if (native_006b4af6 == '\0') {
        uVar6 = (undefined4)(CTool_EndianConvertWord32((undefined4)(iVar7)));
        *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar8) = uVar6;
      }
    }
  }
  if ((native_00711be4 != 0) && (native_006eac2a == '\0')) {
    uVar6 = (undefined4)(fn_005cd5f0((int)(*(undefined4 *)(*(int *)(native_00711be4 + 0x26) + 4))));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(*(undefined4 *)((int)local_18 + 0x1a)), (undefined4)(uVar6), (undefined4)(0));
    uVar6 = (undefined4)(fn_005cd510((int)(*(undefined4 *)(*(int *)(native_00711be4 + 0x26) + 4))));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(*(undefined4 *)((int)local_18 + 0x1e)), (undefined4)(uVar6), (undefined4)(0));
  }
  iVar4 = (int)(*(int *)((int)local_18 + 0x16));
  fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar4), (undefined4)(native_00710324), (undefined4)(0));
  if (native_006b4af6 == '\0') {
    uVar6 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
    *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar4) = uVar6;
  }
  fn_005d5930();
  fn_00554890((int)(native_006eabf2), (int)(native_006ea878), (uint)(*(int *)(native_006eabf2 + 0x2c) - 4));
  fn_005549c0((int)(native_006eabd6), (uint)(0));
  fn_00554960((int)(native_006eabd6), (undefined2)(2));
  fn_005549c0((int)(native_006eabd6), (uint)(0));
  fn_005549c0((int)(native_006eabd6), (uint)(0));
  local_1c = (int)(*(int *)(native_006eabd6 + 0x2c));
  local_2c = (int)(native_006eabd6);
  native_0070bc24 = (int)(0);
  fn_00455ea0((char *)(auStack_4c));
  fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(auStack_4c));
  fn_0044cfe0((int)(native_0070bc20));
  iVar4 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
  fn_0044d0a0((int)(native_0070bc20));
  iVar7 = (int)(-1);
  pcVar10 = (char*)(literal_006b4a12);
  do {
    if (iVar7 == 0) break;
    iVar7 = (int)(iVar7 - 1);
    cVar1 = (char)(*pcVar10);
    pcVar10 = (char*)(pcVar10 + 1);
  } while (cVar1 != '\0');
  iVar7 = (int)(-iVar7 - 2);
  iVar8 = (int)(-1);
  pcVar10 = (char*)((char *)(iVar4 + 10));
  do {
    if (iVar8 == 0) break;
    iVar8 = (int)(iVar8 - 1);
    cVar1 = (char)(*pcVar10);
    pcVar10 = (char*)(pcVar10 + 1);
  } while (cVar1 != '\0');
  iVar9 = (int)(-iVar8 - 2);
  iVar5 = (int)(galloc((int)(-iVar8 + -1 + iVar7)));
  iVar8 = (int)(0);
  for (; iVar7 != 0; iVar7 = iVar7 - 1) {
    *(char *)(iVar5 + iVar8) = literal_006b4a12[iVar8];
    iVar8 = (int)(iVar8 + 1);
  }
  iVar7 = (int)(0);
  for (; iVar9 != 0; iVar9 = iVar9 - 1) {
    *(undefined1 *)(iVar5 + iVar8) = *(undefined1 *)(iVar4 + 10 + iVar7);
    iVar8 = (int)(iVar8 + 1);
    iVar7 = (int)(iVar7 + 1);
  }
  *(undefined1 *)(iVar5 + iVar8) = 0;
  fn_005cd6a0((undefined4)(iVar5), (undefined4)(local_2c), (byte)(0), (undefined4)(1), (undefined4)(local_1c), (int)(0));
  fn_00554a70((undefined4)(0x18), (int)(native_00710750), (undefined4)(6), (undefined4)(native_007108d0), (undefined4)(0));
  for (local_18 = (int*)(native_006eac1a); local_18 != (int *)0x0; local_18 = (int *)*local_18) {
    native_006eac12 = (int)(local_18);
    for (puStack_14 = (undefined4*)((undefined4 *)local_18[1]); puStack_14 != (undefined4 *)0x0;
        puStack_14 = (undefined4 *)*puStack_14) {
      if ((*(short *)(puStack_14 + 5) == 0x34) &&
         (uStack_24 = (uint)*(byte *)((int)puStack_14 + 0x66),
         *(byte *)((int)puStack_14 + 0x66) != 0) && (*(char *)((int)puStack_14 + 0x67) == '\0')) {
        iVar4 = (int)(*(int *)((int)puStack_14 + 0x1a));
        if (*(int *)(iVar4 + 4) != native_006eabca) {
          local_1c = (int)(*(int *)(native_006eabd6 + 0x2c));
          fn_005549c0((int)(native_006eabd6), (uint)(puStack_14[2]));
          fn_005548f0((int)(native_006eabd6), (char *)(iVar4 + 10));
          iStack_20 = (int)(*(int *)(native_006eabd6 + 0x2c) - local_1c);
          local_2c = (int)(native_006eabd6);
          iVar7 = (int)(-1);
          pcVar10 = (char*)(literal_006b4a01);
          do {
            if (iVar7 == 0) break;
            iVar7 = (int)(iVar7 - 1);
            cVar1 = (char)(*pcVar10);
            pcVar10 = (char*)(pcVar10 + 1);
          } while (cVar1 != '\0');
          iVar7 = (int)(-iVar7 - 2);
          iVar8 = (int)(-1);
          pcVar10 = (char*)((char *)(iVar4 + 10));
          do {
            if (iVar8 == 0) break;
            iVar8 = (int)(iVar8 - 1);
            cVar1 = (char)(*pcVar10);
            pcVar10 = (char*)(pcVar10 + 1);
          } while (cVar1 != '\0');
          iVar9 = (int)(-iVar8 - 2);
          iVar5 = (int)(galloc((int)(-iVar8 + -1 + iVar7)));
          iVar8 = (int)(0);
          for (; iVar7 != 0; iVar7 = iVar7 - 1) {
            *(char *)(iVar5 + iVar8) = literal_006b4a01[iVar8];
            iVar8 = (int)(iVar8 + 1);
          }
          iVar7 = (int)(0);
          for (; iVar9 != 0; iVar9 = iVar9 - 1) {
            *(undefined1 *)(iVar5 + iVar8) = *(undefined1 *)(iVar4 + 10 + iVar7);
            iVar8 = (int)(iVar8 + 1);
            iVar7 = (int)(iVar7 + 1);
          }
          *(undefined1 *)(iVar5 + iVar8) = 0;
          fn_005cd6a0((undefined4)(iVar5), (undefined4)(local_2c), (byte)(uStack_24 & 0xff), (undefined4)(1), (undefined4)(iStack_20), (int)(local_1c));
        }
      }
      if ((*(short *)(puStack_14 + 5) == 0x2e) &&
         (uStack_24 = (uint)*(byte *)((int)puStack_14 + 0x6e),
         *(byte *)((int)puStack_14 + 0x6e) != 0)) {
        iVar4 = (int)(*(int *)((int)puStack_14 + 0x1a));
        if (*(int *)(iVar4 + 4) != native_006eabca) {
          local_1c = (int)(*(int *)(native_006eabd6 + 0x2c));
          fn_005549c0((int)(native_006eabd6), (uint)(puStack_14[2]));
          fn_005548f0((int)(native_006eabd6), (char *)(iVar4 + 10));
          iStack_20 = (int)(*(int *)(native_006eabd6 + 0x2c) - local_1c);
          local_2c = (int)(native_006eabd6);
          iVar7 = (int)(-1);
          pcVar10 = (char*)(literal_006b4a01);
          do {
            if (iVar7 == 0) break;
            iVar7 = (int)(iVar7 - 1);
            cVar1 = (char)(*pcVar10);
            pcVar10 = (char*)(pcVar10 + 1);
          } while (cVar1 != '\0');
          iVar7 = (int)(-iVar7 - 2);
          iVar8 = (int)(-1);
          pcVar10 = (char*)((char *)(iVar4 + 10));
          do {
            if (iVar8 == 0) break;
            iVar8 = (int)(iVar8 - 1);
            cVar1 = (char)(*pcVar10);
            pcVar10 = (char*)(pcVar10 + 1);
          } while (cVar1 != '\0');
          iVar9 = (int)(-iVar8 - 2);
          iVar5 = (int)(galloc((int)(-iVar8 + -1 + iVar7)));
          iVar8 = (int)(0);
          for (; iVar7 != 0; iVar7 = iVar7 - 1) {
            *(char *)(iVar5 + iVar8) = literal_006b4a01[iVar8];
            iVar8 = (int)(iVar8 + 1);
          }
          iVar7 = (int)(0);
          for (; iVar9 != 0; iVar9 = iVar9 - 1) {
            *(undefined1 *)(iVar5 + iVar8) = *(undefined1 *)(iVar4 + 10 + iVar7);
            iVar8 = (int)(iVar8 + 1);
            iVar7 = (int)(iVar7 + 1);
          }
          *(undefined1 *)(iVar5 + iVar8) = 0;
          fn_005cd6a0((undefined4)(iVar5), (undefined4)(local_2c), (byte)(uStack_24 & 0xff), (undefined4)(1), (undefined4)(iStack_20), (int)(local_1c));
        }
      }
    }
    puStack_14 = (undefined4*)((undefined4 *)0x0);
  }
  fn_005549c0((int)(native_006eabd6), (uint)(0));
  local_1c = (int)(*(int *)(native_006eabd6 + 0x2c) - 4);
  local_18 = (int*)((int *)native_006eabd6);
  native_0070bc24 = (int)(0);
  fn_00455ea0((char *)(auStack_3c));
  fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(auStack_3c));
  fn_0044cfe0((int)(native_0070bc20));
  iVar4 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
  fn_0044d0a0((int)(native_0070bc20));
  iVar7 = (int)(-1);
  pcVar10 = (char*)(literal_006b4a2c);
  do {
    if (iVar7 == 0) break;
    iVar7 = (int)(iVar7 - 1);
    cVar1 = (char)(*pcVar10);
    pcVar10 = (char*)(pcVar10 + 1);
  } while (cVar1 != '\0');
  iVar7 = (int)(-iVar7 - 2);
  iVar8 = (int)(-1);
  pcVar10 = (char*)((char *)(iVar4 + 10));
  do {
    if (iVar8 == 0) break;
    iVar8 = (int)(iVar8 - 1);
    cVar1 = (char)(*pcVar10);
    pcVar10 = (char*)(pcVar10 + 1);
  } while (cVar1 != '\0');
  iVar9 = (int)(-iVar8 - 2);
  iVar5 = (int)(galloc((int)(-iVar8 + -1 + iVar7)));
  iVar8 = (int)(0);
  for (; iVar7 != 0; iVar7 = iVar7 - 1) {
    *(char *)(iVar5 + iVar8) = literal_006b4a2c[iVar8];
    iVar8 = (int)(iVar8 + 1);
  }
  iVar7 = (int)(0);
  for (; iVar9 != 0; iVar9 = iVar9 - 1) {
    *(undefined1 *)(iVar5 + iVar8) = *(undefined1 *)(iVar4 + 10 + iVar7);
    iVar8 = (int)(iVar8 + 1);
    iVar7 = (int)(iVar7 + 1);
  }
  *(undefined1 *)(iVar5 + iVar8) = 0;
  fn_005cd6a0((undefined4)(iVar5), (undefined4)(local_18), (byte)(0), (undefined4)(1), (undefined4)(4), (int)(local_1c));
  fn_00554890((int)(native_006eabfe), (int)(0), (uint)(*(int *)(native_006eabfe + 0x2c) - 4));
  fn_00554890((int)(native_006eabd6), (int)(0), (uint)(*(int *)(native_006eabd6 + 0x2c) - 4));
  fn_00554a70((undefined4)(0x18), (int)(native_00710750), (undefined4)(10), (undefined4)(iStack_28), (undefined4)(1));
  return;
}

void fn_005cefc0(void)

{
  int iVar1;
  int iVar2;

  if (native_0070f287 != '\0') {
    native_00725eda = (char)(1);
    native_006eac1a = (int)(0);
    native_006eac16 = (int *)((int *)0x0);
    native_006eac12 = (int)(0);
    native_006eabca = (int)(0);
    native_006eac1e = (int)(0);
    native_006eac2a = (char)(0);
    native_006eabce = (int)(0);
    iVar1 = (int)(galloc((int)(0x12)));
    memclrw((undefined1 *)(iVar1), (int)(0x12));
    *(undefined2 *)(iVar1 + 0xc) = 1;
    *(undefined4 *)(iVar1 + 0xe) = native_00710124;
    iVar2 = (int)(iVar1);
    if (native_006eac16 != (int *)0x0) {
      *native_006eac16 = (int )(iVar1);
      iVar2 = (int)(native_006eac1a);
    }
    native_006eac1a = (int)(iVar2);
    native_006eac0e = (int)(iVar1);
    native_006eac12 = (int)(iVar1);
    native_006eac16 = (int *)((int *)iVar1);
    iVar1 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar1), (int)(0x7a));
    *(undefined2 *)(iVar1 + 0x14) = 0x11;
    iVar2 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar1;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar1;
      *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar1;
    }
    *(int *)(native_006eac12 + 8) = iVar1;
    native_00710710 = (int)(iVar1);
    native_006eabfe = (int)(fn_00555930((char *)(literal_006b4a65), (undefined4)(1), (undefined4)(0)));
    native_006eabfa = (int)(fn_00555930((char *)(literal_006b4a71), (undefined4)(4), (undefined4)(0)));
    native_006eabe2 = (int)(fn_00555930((char *)(literal_006b4aaf), (undefined4)(1), (undefined4)(0)));
    native_006eabde = (int)(fn_00555930((char *)(literal_006b4abe), (undefined4)(1), (undefined4)(0)));
    native_006eabf6 = (int)(fn_00555930((char *)(literal_006b4a82), (undefined4)(4), (undefined4)(0)));
    native_006eabf2 = (int)(fn_00555930((char *)(literal_006b4a92), (undefined4)(1), (undefined4)(0)));
    native_006eabee = (int)(fn_00555930((char *)(literal_006b4a9e), (undefined4)(4), (undefined4)(0)));
    native_006eabd6 = (int)(fn_00555930((char *)(literal_006b4ad8), (undefined4)(1), (undefined4)(0)));
    native_006eabda = (int)(fn_00555930((char *)(literal_006b4ac9), (undefined4)(1), (undefined4)(0)));
    native_006eabd2 = (int)(fn_00555930((char *)(literal_006b4ae8), (undefined4)(1), (undefined4)(0)));
    fn_00555920();
    *(undefined4 *)(native_006eabfe + 0x58) = 0;
    fn_00555920();
    *(undefined4 *)(native_006eabf2 + 0x58) = 0;
    fn_00555920();
    *(undefined4 *)(native_006eabf2 + 0x58) = 0;
    native_007108d0 = (int)(fn_005cd470((undefined4)(literal_006b4a65), (int)(native_006eabfe), (char)(0), (undefined4)(3), (undefined4)(0)));
    native_00710110 = (int)(fn_005cd470((undefined4)(literal_006b4abe), (int)(native_006eabde), (char)(0), (undefined4)(3), (undefined4)(0)));
    native_00710324 = (int)(fn_005cd470((undefined4)(literal_006b4a92), (int)(native_006eabf2), (char)(0), (undefined4)(3), (undefined4)(0)));
    native_00716cd0 = (int)(fn_005cd470((undefined4)(literal_006b4ae8), (int)(native_006eabd2), (char)(0), (undefined4)(3), (undefined4)(0)));
    native_00710750 = (int)(fn_005cd470((undefined4)(literal_006b4ad8), (int)(native_006eabd6), (char)(0), (undefined4)(3), (undefined4)(0)));
    native_006eac02 = (undefined4 *)(0);
    native_006eac06 = (int)(0);
    native_006eabc6 = (int)(0x80);
    native_006ea930 = (int)(0xffffffff);
    native_006ea934 = (int)(0);
    native_006ea938 = (char)(0);
    native_006ea93a = (int)(0);
    native_006ea93e = (int)(&native_006ea946);
    native_006ea942 = (int)(0);
    iVar2 = (int)(0);
    do {
      iVar1 = (int)(iVar2 + 7);
      (&native_006ea89c)[iVar2] = 0;
      (&native_006ea8a0)[iVar2] = 0;
      (&native_006ea8a4)[iVar2] = 0;
      (&native_006ea8a8)[iVar2] = 0;
      (&native_006ea8ac)[iVar2] = 0;
      (&native_006ea8b0)[iVar2] = 0;
      (&native_006ea8b4)[iVar2] = 0;
      iVar2 = (int)(iVar1);
    } while (iVar1 < 0x1e);
    (&native_006ea89c)[iVar1] = 0;
    (&native_006ea8a0)[iVar1] = 0;
    native_00716ce8 = (int *)(0);
    native_00710220 = (int)(0);
    native_007108dc = (int)(0);
    native_00716ccc = (int *)(0);
    native_00715bfc = (int *)(0);
    native_00716d7c = (int)(0);
    native_00710b3c = (int)(0);
    native_00711be4 = (int)(0);
    native_006eac26 = (undefined4 *)(0);
    native_006eac22 = (undefined4 *)(0);
    fn_005d85a0();
    return;
  }
  return;
}

void fn_005cf400(int param_1, undefined4 param_2, undefined4 param_3)

{
  unsigned char nativeStack[32];
  int iVar1;
  char cVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 uVar5;
  short unaff_DI;

  (*(char  *)(nativeStack+0x1f)) = (char)('\0');
  puVar3 = (undefined1*)((undefined1 *)fn_0057a790((int)(param_1)));
  if ((native_0070f287 == '\0') || (native_006eac0e == 0)) {
    return;
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    return;
  }
  if (*(char *)(*(int *)(param_1 + 0xc) + 10) != '@') {
    fn_005d8640((undefined4)(param_1), (char *)(&(*(char  *)(nativeStack+0x1f))));
    native_006eac12 = (int)(native_006eac0e);
    iVar4 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar4), (int)(0x7a));
    *(undefined2 *)(iVar4 + 0x14) = 0x34;
    iVar1 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar4;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar1 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar4;
      iVar1 = (int)(native_006eac12);
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(iVar1 + 8) = iVar4;
    }
    *(int *)(native_006eac12 + 8) = iVar4;
    *(int *)(param_1 + 0x38) = iVar4;
    *(undefined4 *)(iVar4 + 0x16) = *(undefined4 *)(param_1 + 0xc);
    uVar5 = (undefined4)(COptimizer_GetFunctionObject((int)(param_1)));
    *(undefined4 *)(iVar4 + 0x1a) = uVar5;
    uVar5 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(param_1 + 0x10))));
    *(undefined4 *)(iVar4 + 0x1e) = uVar5;
    *(undefined1 *)(iVar4 + 0x60) = 0;
    *(char *)(iVar4 + 0x67) = (*(char  *)(nativeStack+0x1f));
    *(undefined1 *)(iVar4 + 0x68) = 0;
    cVar2 = (char)(fn_00452fe0((int)(param_1)));
    if (cVar2 == '\0') {
      if ((*(char  *)(nativeStack+0x1f)) == '\0') {
        if ((*(uint *)(param_1 + 0x14) & 0x20000) == 0) {
          if ((*(uint *)(param_1 + 0x14) & 0x40000) == 0) {
            *(undefined1 *)(iVar4 + 0x66) = 1;
          }
          else {
            *(undefined1 *)(iVar4 + 0x66) = 2;
          }
        }
        else {
          *(undefined1 *)(iVar4 + 0x66) = 2;
        }
      }
      else if ((*(uint *)(param_1 + 0x14) & 0x20000) == 0) {
        if ((*(uint *)(param_1 + 0x14) & 0x40000) == 0) {
          *(undefined1 *)(iVar4 + 0x66) = 0xfe;
        }
        else {
          *(undefined1 *)(iVar4 + 0x66) = 0xff;
        }
      }
      else {
        *(undefined1 *)(iVar4 + 0x66) = 0xfe;
      }
    }
    else {
      *(undefined1 *)(iVar4 + 0x66) = 0;
    }
    *(undefined4 *)(iVar4 + 0x62) = 0;
    fn_005cce90((undefined4)(param_1), (undefined4 *)(&(*(int  *)(nativeStack+0x18))), (undefined4 *)(&(*(undefined4  *)(nativeStack+0x14))), (undefined4 *)(&(*(undefined4  *)(nativeStack+0x10))));
    if ((puVar3 == (undefined1 *)0x0) || (puVar3[1] == '\0') || (native_0070f054 != '\0')) {
      if ((*(int  *)(nativeStack+0x18)) == -1) {
        *(undefined2 *)(iVar4 + 0x26) = 4;
      }
      else {
        *(undefined2 *)(iVar4 + 0x26) = 3;
        *(short *)(iVar4 + 0x34) = (short)(*(int  *)(nativeStack+0x18));
      }
    }
    else {
      switch(*puVar3) {
      case 2:
        unaff_DI = (short)(0x464);
        break;
      case 3:
        unaff_DI = (short)(0x20);
        break;
      case 4:
        unaff_DI = (short)(0);
        break;
      default:
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x13d2));
      }
      *(short *)(iVar4 + 0x34) = (char)puVar3[1] + unaff_DI;
      *(undefined2 *)(iVar4 + 0x26) = 5;
    }
    *(undefined4 *)(iVar4 + 0x38) = (*(undefined4  *)(nativeStack+0x14));
    *(undefined4 *)(iVar4 + 0x3c) = (*(undefined4  *)(nativeStack+0x10));
    *(undefined4 *)(iVar4 + 0x40) = param_3;
    if ((*(char  *)(nativeStack+0x1f)) == '\0') {
      (*(undefined4 * *)(nativeStack+0x0)) = (undefined4*)(native_00715c48);
      (*(undefined4  *)(nativeStack+0x4)) = (undefined4)(native_00715c4c);
      (*(undefined4  *)(nativeStack+0x8)) = (undefined4)(native_00715c50);
      fn_00447910((int *)(&(*(undefined4 * *)(nativeStack+0x0))));
      if ((*(undefined4 * *)(nativeStack+0x0)) == (undefined4 *)0x0) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x13f1));
      }
      *(undefined4 *)(iVar4 + 0x58) = *(*(undefined4 * *)(nativeStack+0x0));
      *(undefined4 *)(iVar4 + 0x5c) = (*(undefined4  *)(nativeStack+0x8));
    }
    return;
  }
  return;
}

void fn_005cf6d0(int param_1, int *param_2, undefined4 param_3, int param_4, undefined4 param_5,
                 undefined4 param_6)

{
  unsigned char nativeStack[20];
  char cVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  char cVar7;
  short sVar8;
  undefined2 uVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  char *pcVar16;
  char *pcVar17;
  char *pcVar18;
  char *pcVar19;

  if ((native_0070f287 == '\0') || (native_00710710 == 0)) {
    return;
  }
  if ((param_2 == (int *)0x0) || (*param_2 == 0)) {
    return;
  }
  if (native_006eabce == 0) {
    native_006eabce = (int)(*(int *)(param_4 + 4));
  }
  else if (native_006eabce != *(int *)(param_4 + 4)) {
    native_006eac2a = (char)(1);
  }
  iVar10 = (int)(galloc((int)(0x12)));
  memclrw((undefined1 *)(iVar10), (int)(0x12));
  *(undefined2 *)(iVar10 + 0xc) = 2;
  *(undefined4 *)(iVar10 + 0xe) = native_00710124;
  iVar4 = (int)(iVar10);
  if (native_006eac16 != (int *)0x0) {
    *native_006eac16 = (int )(iVar10);
    iVar4 = (int)(native_006eac1a);
  }
  native_006eac1a = (int)(iVar4);
  native_006eac12 = (int)(iVar10);
  native_006eac16 = (int *)((int *)iVar10);
  iVar10 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar10), (int)(0x7a));
  *(undefined2 *)(iVar10 + 0x14) = 0x2e;
  iVar4 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar10;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar4 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar10;
    *(undefined4 *)(iVar10 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar10;
  }
  iVar4 = (int)(native_006eac12);
  *(int *)(native_006eac12 + 8) = iVar10;
  iVar4 = (int)(*(int *)(iVar4 + 8));
  if ((*(uint *)(param_1 + 0x14) & 0x80000) != 0) {
    iVar10 = (int)(5);
    pcVar16 = (char*)((char *)(*(int *)(param_1 + 0xc) + 10));
    pcVar18 = (char*)(&native_006b4b07);
    do {
      pcVar17 = (char*)(pcVar16);
      pcVar19 = (char*)(pcVar18);
      if (iVar10 == 0) break;
      iVar10 = (int)(iVar10 - 1);
      pcVar19 = (char*)(pcVar18 + 1);
      pcVar17 = (char*)(pcVar16 + 1);
      cVar1 = (char)(*pcVar18);
      cVar7 = (char)(*pcVar16);
      pcVar16 = (char*)(pcVar17);
      pcVar18 = (char*)(pcVar19);
    } while (cVar7 == cVar1);
    if (pcVar17[-1] != pcVar19[-1]) {
      uVar11 = (undefined4)(fn_0045df60((undefined4)(param_1)));
      uVar11 = (undefined4)(GetHashNameNode((char *)(uVar11)));
      *(undefined4 *)(iVar4 + 0x16) = uVar11;
      goto label_005cf7d6;
    }
  }
  *(undefined4 *)(iVar4 + 0x16) = *(undefined4 *)(param_1 + 0xc);
label_005cf7d6:
  *(undefined1 *)(iVar4 + 0x40) = 0;
  uVar11 = (undefined4)(COptimizer_GetFunctionObject((int)(param_1)));
  *(undefined4 *)(iVar4 + 0x1a) = uVar11;
  uVar11 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(*(int *)(param_1 + 0x10) + 0xe))));
  *(undefined4 *)(iVar4 + 0x1e) = uVar11;
  *(int *)(iVar4 + 0x26) = param_4;
  *(undefined4 *)(iVar4 + 0x32) = param_5;
  *(undefined4 *)(iVar4 + 0x36) = param_6;
  *(undefined1 *)(iVar4 + 0x78) = 0;
  cVar7 = (char)(fn_00452fe0((int)(param_1)));
  if (cVar7 == '\0') {
    if ((*(uint *)(param_1 + 0x14) & 0x20000) == 0) {
      if ((*(uint *)(param_1 + 0x14) & 0x40000) == 0) {
        *(undefined1 *)(iVar4 + 0x6e) = 1;
      }
      else {
        *(undefined1 *)(iVar4 + 0x6e) = 2;
      }
    }
    else {
      *(undefined1 *)(iVar4 + 0x6e) = 2;
    }
  }
  else {
    *(undefined1 *)(iVar4 + 0x6e) = 0;
  }
  native_00710b3c = (int)(iVar4);
  (*(undefined4 * *)(nativeStack+0xc)) = (undefined4*)(native_00710924);
  if (native_00711be4 == 0) {
    native_00711be4 = (int)(iVar4);
  }
  do {
    if ((*(undefined4 * *)(nativeStack+0xc)) == (undefined4 *)0x0) {
      for (puVar12 = (undefined4*)((undefined4 *)fn_005d0020()); puVar12 != (undefined4 *)0x0;
          puVar12 = (undefined4 *)*puVar12) {
        iVar10 = (int)(puVar12[1]);
        if ((iVar10 != 0) && (iVar15 = *(int *)(iVar10 + 0x40), iVar15 != 0) &&
           (*(char *)(iVar15 + 9) != '\0') && (*(char *)(*(int *)(iVar10 + 0xc) + 10) != '@')) {
          iVar13 = (int)(galloc((int)(0x7a)));
          memclrw((undefined1 *)(iVar13), (int)(0x7a));
          *(undefined2 *)(iVar13 + 0x14) = 0x34;
          iVar14 = (int)(native_006eac12);
          if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
            *(int *)(native_006eac12 + 8) = iVar13;
            *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar14 + 8);
          }
          else {
            **(int **)(native_006eac12 + 8) = iVar13;
            *(undefined4 *)(iVar13 + 4) = *(undefined4 *)(native_006eac12 + 8);
            *(int *)(native_006eac12 + 8) = iVar13;
          }
          *(int *)(native_006eac12 + 8) = iVar13;
          *(undefined4 *)(iVar13 + 0x16) = *(undefined4 *)(iVar10 + 0xc);
          uVar11 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(iVar10 + 0x10))));
          *(undefined4 *)(iVar13 + 0x1e) = uVar11;
          *(undefined1 *)(iVar13 + 0x60) = 1;
          *(undefined1 *)(iVar13 + 0x61) = 0;
          *(undefined1 *)(iVar13 + 0x66) = 0;
          *(int *)(iVar13 + 0x62) = iVar4;
          iVar14 = (int)(Registers_GetInfo((int)(iVar10)));
          if ((iVar14 == 0) || ((*(byte *)(iVar14 + 0xe) & 6) != 6)) {
            iVar14 = (int)(Registers_GetInfo((int)(iVar10)));
            if ((iVar14 == 0) || ((*(byte *)(iVar14 + 0xe) & 2) == 0)) {
              *(undefined2 *)(iVar13 + 0x26) = 3;
              *(undefined2 *)(iVar13 + 0x34) = native_007172bc;
              uVar11 = (undefined4)(fn_005ccee0((undefined4)(iVar10)));
              *(undefined4 *)(iVar13 + 0x38) = uVar11;
              *(undefined4 *)(iVar13 + 0x40) = 0;
            }
            else {
              *(undefined2 *)(iVar13 + 0x26) = 0;
              *(undefined2 *)(iVar13 + 0x34) = *(undefined2 *)(iVar15 + 0x10);
            }
          }
          else {
            *(undefined2 *)(iVar13 + 0x26) = 1;
            *(undefined2 *)(iVar13 + 0x36) = *(undefined2 *)(iVar15 + 0x12);
            *(undefined2 *)(iVar13 + 0x34) = *(undefined2 *)(iVar15 + 0x10);
          }
          *(undefined4 *)(iVar13 + 0x48) = *(undefined4 *)(iVar10 + 0x24);
          *(undefined4 *)(iVar13 + 0x4c) = *(undefined4 *)(iVar10 + 0x28);
          *(undefined4 *)(iVar13 + 0x50) = *(undefined4 *)(iVar10 + 0x2c);
          puVar5 = (undefined4*)(*(undefined4 **)(iVar10 + 0x24));
          if (*(char *)(puVar5 + 2) == '\0') {
            *(undefined4 *)(iVar13 + 0x58) = *puVar5;
            *(undefined4 *)(iVar13 + 0x5c) = *(undefined4 *)(iVar10 + 0x2c);
          }
          else {
            switch(*(char *)(puVar5 + 2)) {
            case '\x01':
            case '\x02':
            case '\x03':
              *(undefined4 *)(iVar13 + 0x58) = **(undefined4 **)((int)puVar5 + 0x16);
              *(undefined4 *)(iVar13 + 0x5c) = *(undefined4 *)(*(int *)(iVar10 + 0x24) + 0x1e);
              break;
            default:
              CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x12a1));
            }
          }
        }
      }
      fn_005d00e0((undefined4 *)(native_00711b64), (undefined4)(param_4), (undefined4)(iVar4), (char)(1));
      for (puVar12 = (undefined4*)(native_006eac2c); puVar12 != (undefined4 *)0x0; puVar12 = (undefined4 *)*puVar12) {
        iVar10 = (int)(puVar12[1]);
        if ((*(int *)(iVar10 + 0x38) == 0) && (*(int *)(iVar10 + 0x40) != 0) &&
           (iVar10 != -0x24 && (*(int *)(iVar10 + 0x24) != 0))) {
          iVar14 = (int)(galloc((int)(0x7a)));
          memclrw((undefined1 *)(iVar14), (int)(0x7a));
          *(undefined2 *)(iVar14 + 0x14) = 0x34;
          iVar15 = (int)(native_006eac12);
          if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
            *(int *)(native_006eac12 + 8) = iVar14;
            *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar15 + 8);
          }
          else {
            **(int **)(native_006eac12 + 8) = iVar14;
            iVar15 = (int)(native_006eac12);
            *(undefined4 *)(iVar14 + 4) = *(undefined4 *)(native_006eac12 + 8);
            *(int *)(iVar15 + 8) = iVar14;
          }
          *(int *)(native_006eac12 + 8) = iVar14;
          *(undefined4 *)(iVar14 + 0x16) = *(undefined4 *)(iVar10 + 0xc);
          uVar11 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(iVar10 + 0x10))));
          *(undefined4 *)(iVar14 + 0x1e) = uVar11;
          *(undefined1 *)(iVar14 + 0x67) = 0;
          *(undefined1 *)(iVar14 + 0x68) = 0;
          *(int *)(iVar10 + 0x38) = iVar14;
          *(undefined4 *)(iVar14 + 0x16) = *(undefined4 *)(iVar10 + 0xc);
          uVar11 = (undefined4)(COptimizer_GetFunctionObject((int)(iVar10)));
          *(undefined4 *)(iVar14 + 0x1a) = uVar11;
          uVar11 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(iVar10 + 0x10))));
          *(undefined4 *)(iVar14 + 0x1e) = uVar11;
          fn_005cce90((undefined4)(iVar10), (undefined4 *)(&(*(int  *)(nativeStack+0x4))), (undefined4 *)(((undefined1  *)(nativeStack+0x0))), (undefined4 *)(&(*(undefined4  *)(nativeStack+0x8))));
          if ((*(int  *)(nativeStack+0x4)) == -1) {
            *(undefined2 *)(iVar14 + 0x26) = 4;
            *(undefined4 *)(iVar14 + 0x3c) = (*(undefined4  *)(nativeStack+0x8));
          }
          else {
            *(undefined2 *)(iVar14 + 0x26) = 3;
            *(undefined4 *)(iVar14 + 0x3c) = (*(undefined4  *)(nativeStack+0x8));
          }
          *(undefined4 *)(iVar14 + 0x38) = 0;
          uVar11 = (undefined4)(fn_005cd660((undefined4)(iVar10)));
          *(undefined4 *)(iVar14 + 0x40) = uVar11;
          puVar5 = (undefined4*)(*(undefined4 **)(iVar10 + 0x24));
          if (*(char *)(puVar5 + 2) == '\0') {
            *(undefined4 *)(iVar14 + 0x58) = *puVar5;
            *(undefined4 *)(iVar14 + 0x5c) = *(undefined4 *)(iVar10 + 0x2c);
          }
          else {
            switch(*(char *)(puVar5 + 2)) {
            case '\x01':
            case '\x02':
            case '\x03':
              *(undefined4 *)(iVar14 + 0x58) = **(undefined4 **)((int)puVar5 + 0x16);
              *(undefined4 *)(iVar14 + 0x5c) = *(undefined4 *)(*(int *)(iVar10 + 0x24) + 0x1e);
              break;
            default:
              CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x135d));
            }
          }
        }
      }
      if (*(int *)(native_006eac12 + 8) != iVar4) {
        iVar15 = (int)(galloc((int)(0x7a)));
        memclrw((undefined1 *)(iVar15), (int)(0x7a));
        *(undefined2 *)(iVar15 + 0x14) = 0xffff;
        iVar10 = (int)(native_006eac12);
        if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
          *(int *)(native_006eac12 + 8) = iVar15;
          *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar10 + 8);
        }
        else {
          **(int **)(native_006eac12 + 8) = iVar15;
          iVar10 = (int)(native_006eac12);
          *(undefined4 *)(iVar15 + 4) = *(undefined4 *)(native_006eac12 + 8);
          *(int *)(iVar10 + 8) = iVar15;
        }
        *(int *)(native_006eac12 + 8) = iVar15;
        *(int *)(iVar4 + 0x6a) = iVar15;
      }
      native_006eac2c = (int)((undefined4 *)0x0);
      *(undefined4 *)(iVar4 + 0x42) = *(undefined4 *)*param_2;
      *(int *)(iVar4 + 0x4e) = param_2[2];
      *(int *)(native_00710710 + 0x3a) = iVar4;
      fn_005d0820((int)(iVar4));
      return;
    }
    iVar10 = (int)((*(undefined4 * *)(nativeStack+0xc))[1]);
    iVar15 = (int)(*(int *)(iVar10 + 0x40));
    if (((*(char *)(iVar15 + 9) != '\0') || ((*(byte *)(iVar15 + 0xe) & 2) != 0)) &&
       (*(char *)(*(int *)(iVar10 + 0xc) + 10) != '@') &&
       (iVar10 != -0x24 && (*(int *)(iVar10 + 0x24) != 0)) &&
       ((*(byte *)(iVar15 + 0xe) & 2) != 0 || ((*(byte *)(iVar15 + 0xe) & 0x20) != 0))) {
      iVar13 = (int)(galloc((int)(0x7a)));
      memclrw((undefined1 *)(iVar13), (int)(0x7a));
      *(undefined2 *)(iVar13 + 0x14) = 5;
      iVar14 = (int)(native_006eac12);
      if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
        *(int *)(native_006eac12 + 8) = iVar13;
        *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar14 + 8);
      }
      else {
        **(int **)(native_006eac12 + 8) = iVar13;
        *(undefined4 *)(iVar13 + 4) = *(undefined4 *)(native_006eac12 + 8);
        *(int *)(native_006eac12 + 8) = iVar13;
      }
      *(int *)(native_006eac12 + 8) = iVar13;
      *(undefined4 *)(iVar13 + 0x16) = *(undefined4 *)(iVar10 + 0xc);
      uVar11 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(iVar10 + 0x10))));
      *(undefined4 *)(iVar13 + 0x1e) = uVar11;
      *(undefined1 *)(iVar13 + 0x60) = 1;
      *(undefined1 *)(iVar13 + 0x61) = 0;
      *(undefined1 *)(iVar13 + 0x66) = 0;
      *(int *)(iVar13 + 0x62) = iVar4;
      *(undefined1 *)(iVar13 + 0x67) = 0;
      *(undefined1 *)(iVar13 + 0x68) = 0;
      if ((*(byte *)(iVar15 + 0xe) & 2) == 0) {
        *(undefined2 *)(iVar13 + 0x26) = 3;
        uVar9 = (undefined2)(fn_00587230((undefined4)(iVar10)));
        *(undefined2 *)(iVar13 + 0x34) = uVar9;
        uVar11 = (undefined4)(fn_005ccee0((undefined4)(iVar10)));
        *(undefined4 *)(iVar13 + 0x38) = uVar11;
        *(undefined4 *)(iVar13 + 0x40) = 0;
      }
      else {
        pbVar6 = (byte*)(*(byte **)(iVar10 + 0x10));
        bVar2 = (byte)(*pbVar6);
        (*(uint  *)(nativeStack+0x10)) = (uint)((uint)bVar2);
        if ((bVar2 == 2) && (bVar3 = pbVar6[6], bVar3 < 0x17)) {
          if ((native_0070f019 == '\0') || (bVar3 > 0x16)) {
            sVar8 = (short)(0x20);
          }
          else if ((native_0070f019 == '\0') || (bVar3 > 0x16) || (*(int *)(pbVar6 + 2) == 4)) {
            sVar8 = (short)(0);
          }
          else {
            sVar8 = (short)(0);
          }
        }
        else if ((bVar2 == 5) &&
                ((char)pbVar6[0x10] > '\x03' && ((char)pbVar6[0x10] < '\x0f') &&
                (*(int *)(pbVar6 + 2) == 0x10))) {
          sVar8 = (short)(0x464);
        }
        else if (((*(short *)((char *)&native_0070eff8+2)) == 0x16) && (bVar2 == 2) && (pbVar6[6] == 0x19)) {
          sVar8 = (short)(0x485);
        }
        else if ((((bVar2 == 1) && (pbVar6[6] < 0x17)) || (bVar2 == 4)) &&
                (*(int *)(pbVar6 + 2) == 8)) {
          sVar8 = (short)(0);
        }
        else {
          sVar8 = (short)(0);
        }
        *(short *)(iVar13 + 0x34) = *(short *)(iVar15 + 0x10) + sVar8;
        if ((native_0070f019 == '\0') || (pcVar16 = *(char **)(iVar10 + 0x10), *pcVar16 != '\x02') ||
           ((byte)pcVar16[6] > 0x16 || (*(int *)(pcVar16 + 2) == 4))) {
          pcVar16 = (char*)(*(char **)(iVar10 + 0x10));
          if ((((*pcVar16 != '\x01') || ((byte)pcVar16[6] > 0x16)) && (*pcVar16 != '\x04')) ||
             (*(int *)(pcVar16 + 2) != 8)) {
            *(undefined2 *)(iVar13 + 0x26) = 0;
            goto label_005cfc16;
          }
        }
        *(undefined2 *)(iVar13 + 0x26) = 1;
        *(undefined2 *)(iVar13 + 0x36) = *(undefined2 *)(iVar15 + 0x12);
      }
label_005cfc16:
      puVar12 = (undefined4*)(*(undefined4 **)(iVar10 + 0x24));
      if (*(char *)(puVar12 + 2) == '\0') {
        *(undefined4 *)(iVar13 + 0x58) = *puVar12;
        *(undefined4 *)(iVar13 + 0x5c) = *(undefined4 *)(iVar10 + 0x2c);
      }
      else {
        switch(*(char *)(puVar12 + 2)) {
        case '\x01':
        case '\x02':
        case '\x03':
          *(undefined4 *)(iVar13 + 0x58) = **(undefined4 **)((int)puVar12 + 0x16);
          *(undefined4 *)(iVar13 + 0x5c) = *(undefined4 *)(*(int *)(iVar10 + 0x24) + 0x1e);
          break;
        default:
          CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x124a));
        }
      }
    }
    (*(undefined4 * *)(nativeStack+0xc)) = (undefined4*)((undefined4 *)*(*(undefined4 * *)(nativeStack+0xc)));
  } while( true );
}

int * fn_005d0020(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int *local_14;

  local_14 = (int*)((int *)0x0);
  if ((native_00716cc0 == (undefined4 *)0x0) && (native_00711b64 == 0)) {
    local_14 = (int*)(native_00716d50);
  }
  else if ((native_00716cc0 == (undefined4 *)0x0) && (native_00711b64 != 0)) {
    local_14 = (int*)((int *)0x0);
  }
  else {
    puVar1 = (undefined4*)(native_00716cc0);
    if (native_00716cc0 != (undefined4 *)0x0) {
      for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
        piVar2 = (int*)((int *)galloc((int)(8)));
        memclrw((undefined1 *)(piVar2), (int)(8));
        if (native_00716d50 != (int *)0x0) {
          piVar4 = (int*)(native_00716d50);
          do {
            iVar3 = (int)(piVar4[1]);
            if ((puVar1[1] == *(int *)(iVar3 + 0xc)) && (*(int *)(iVar3 + 0x3c) == puVar1[2]))
            goto label_005d0084;
            piVar4 = (int*)((int *)*piVar4);
          } while (piVar4 != (int *)0x0);
        }
        iVar3 = (int)(0);
label_005d0084:
        piVar2[1] = (int)(iVar3);
        *piVar2 = (int)((int)local_14);
        local_14 = (int*)(piVar2);
      }
    }
  }
  return local_14;
}

void fn_005d00e0(undefined4 *param_1, undefined4 param_2, undefined4 param_3, char param_4)

{
  undefined4 *puVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;

  iVar3 = (int)(0);
  for (; param_1 != (undefined4 *)0x0; param_1 = (undefined4 *)*param_1) {
    iVar4 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar4), (int)(0x7a));
    *(undefined2 *)(iVar4 + 0x14) = 0xb;
    iVar6 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar4;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar6 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar4;
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar4;
    }
    *(int *)(native_006eac12 + 8) = iVar4;
    *(undefined4 *)(iVar4 + 0x16) = param_2;
    uVar5 = (undefined4)(fn_005d0320((int)(param_1[4])));
    *(undefined4 *)(iVar4 + 0x26) = uVar5;
    iVar6 = (int)(param_1[5]);
    if (iVar6 == 0) {
      iVar6 = (int)(*(int *)(*(int *)(native_007108c8 + 0x18) + 0x20));
    }
    uVar5 = (undefined4)(fn_005d0320((int)(iVar6)));
    *(undefined4 *)(iVar4 + 0x2a) = uVar5;
    if ((param_1[3] != 0) || (param_1[1] != 0)) {
      *(undefined1 *)(iVar4 + 0x32) = 1;
    }
    if (iVar3 != 0) {
      *(int *)(iVar3 + 0x2e) = iVar4;
    }
    bVar2 = (bool)(false);
    puVar1 = (undefined4*)((undefined4 *)param_1[3]);
    if (puVar1 != (undefined4 *)0x0) {
      bVar2 = (bool)(true);
      for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
        fn_005d03a0((int)(puVar1), (undefined4)(param_3));
      }
    }
    if ((param_1[1] == 0) && (bVar2)) {
      iVar6 = (int)(galloc((int)(0x7a)));
      memclrw((undefined1 *)(iVar6), (int)(0x7a));
      *(undefined2 *)(iVar6 + 0x14) = 0xffff;
      iVar3 = (int)(native_006eac12);
      if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
        *(int *)(native_006eac12 + 8) = iVar6;
        *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar3 + 8);
      }
      else {
        **(int **)(native_006eac12 + 8) = iVar6;
        iVar3 = (int)(native_006eac12);
        *(undefined4 *)(iVar6 + 4) = *(undefined4 *)(native_006eac12 + 8);
        *(int *)(iVar3 + 8) = iVar6;
      }
      *(int *)(native_006eac12 + 8) = iVar6;
    }
    if (param_1[1] != 0) {
      fn_005d00e0((undefined4 *)(param_1[1]), (undefined4)(param_2), (undefined4)(param_3), (char)(0));
    }
    iVar3 = (int)(iVar4);
  }
  if (param_4 == '\0') {
    iVar6 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar6), (int)(0x7a));
    *(undefined2 *)(iVar6 + 0x14) = 0xffff;
    iVar3 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar6;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar3 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar6;
      *(undefined4 *)(iVar6 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar6;
    }
    *(int *)(native_006eac12 + 8) = iVar6;
  }
  return;
}

undefined4 fn_005d0320(int param_1)
{
    undefined4 *block;
    undefined4 *instruction;
    if (!param_1)
        CError_Internal((undefined4)literal_006b4af7, 0x10f1);
    for (block = (undefined4 *)native_007108c8; block; block = (undefined4 *)block[0]) {
        if (!(*(ushort *)((char *)block + 0x2a) & 0x100)) {
            for (instruction = (undefined4 *)block[5]; instruction; instruction = (undefined4 *)instruction[0]) {
                if (instruction[8] && *(int *)instruction[8] &&
                    *(uint *)(instruction[8] + 8) >= *(uint *)(param_1 + 8) &&
                    *(uint *)(instruction[8] + 4) >= *(uint *)(param_1 + 4))
                    return instruction[9];
            }
        }
    }
    return 0;
}

void fn_005d03a0(int param_1, undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;

  if (native_00716d50 != (int *)0x0) {
    piVar3 = (int*)(native_00716d50);
    do {
      iVar7 = (int)(piVar3[1]);
      if ((*(int *)(param_1 + 4) == *(int *)(iVar7 + 0xc)) &&
         (*(int *)(iVar7 + 0x3c) == *(int *)(param_1 + 8))) goto label_005d03c7;
      piVar3 = (int*)((int *)*piVar3);
    } while (piVar3 != (int *)0x0);
  }
  iVar7 = (int)(0);
label_005d03c7:
  if (iVar7 == 0) {
    return;
  }
  iVar1 = (int)(*(int *)(iVar7 + 0x40));
  if (iVar1 == 0) {
    return;
  }
  if ((*(char *)(iVar1 + 9) != '\0') && (*(char *)(*(int *)(iVar7 + 0xc) + 10) != '@')) {
    iVar4 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar4), (int)(0x7a));
    *(undefined2 *)(iVar4 + 0x14) = 0x34;
    iVar6 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar4;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar6 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar4;
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar4;
    }
    *(int *)(native_006eac12 + 8) = iVar4;
    *(undefined4 *)(iVar4 + 0x16) = *(undefined4 *)(iVar7 + 0xc);
    uVar5 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(iVar7 + 0x10))));
    *(undefined4 *)(iVar4 + 0x1e) = uVar5;
    *(undefined1 *)(iVar4 + 0x60) = 1;
    *(undefined1 *)(iVar4 + 0x61) = 0;
    *(undefined1 *)(iVar4 + 0x66) = 0;
    *(undefined4 *)(iVar4 + 0x62) = param_2;
    iVar6 = (int)(Registers_GetInfo((int)(iVar7)));
    if ((iVar6 == 0) || ((*(byte *)(iVar6 + 0xe) & 6) != 6)) {
      iVar6 = (int)(Registers_GetInfo((int)(iVar7)));
      if ((iVar6 == 0) || ((*(byte *)(iVar6 + 0xe) & 2) == 0)) {
        *(undefined2 *)(iVar4 + 0x26) = 3;
        *(undefined2 *)(iVar4 + 0x34) = native_007172bc;
        uVar5 = (undefined4)(fn_005ccee0((undefined4)(iVar7)));
        *(undefined4 *)(iVar4 + 0x38) = uVar5;
        *(undefined4 *)(iVar4 + 0x40) = 0;
      }
      else {
        *(undefined2 *)(iVar4 + 0x26) = 0;
        *(undefined2 *)(iVar4 + 0x34) = *(undefined2 *)(iVar1 + 0x10);
      }
    }
    else {
      *(undefined2 *)(iVar4 + 0x26) = 1;
      *(undefined2 *)(iVar4 + 0x36) = *(undefined2 *)(iVar1 + 0x12);
      *(undefined2 *)(iVar4 + 0x34) = *(undefined2 *)(iVar1 + 0x10);
    }
    *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar7 + 0x24);
    *(undefined4 *)(iVar4 + 0x4c) = *(undefined4 *)(iVar7 + 0x28);
    *(undefined4 *)(iVar4 + 0x50) = *(undefined4 *)(iVar7 + 0x2c);
    puVar2 = (undefined4*)(*(undefined4 **)(iVar7 + 0x24));
    if (*(char *)(puVar2 + 2) == '\0') {
      *(undefined4 *)(iVar4 + 0x58) = *puVar2;
      *(undefined4 *)(iVar4 + 0x5c) = *(undefined4 *)(iVar7 + 0x2c);
    }
    else {
      switch(*(char *)(puVar2 + 2)) {
      case '\x01':
      case '\x02':
      case '\x03':
        *(undefined4 *)(iVar4 + 0x58) = **(undefined4 **)((int)puVar2 + 0x16);
        *(undefined4 *)(iVar4 + 0x5c) = *(undefined4 *)(*(int *)(iVar7 + 0x24) + 0x1e);
        break;
      default:
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x10d9));
      }
    }
    return;
  }
  return;
}

void fn_005d05a0(int param_1)

{
  char cVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  char *pcVar12;
  int iVar13;
  int iVar14;
  int iVar15;

  uVar8 = (uint)(*(uint *)(param_1 + 0x62));
  iVar10 = (int)(*(int *)(param_1 + 0x66));
  iVar14 = (int)(*(int *)(native_006eabf2 + 0x2c));
  fn_005d0b20();
  uVar11 = (uint)(0);
  if (uVar8 != 0) {
    iVar9 = (int)(0);
    do {
      for (piVar2 = (int*)(native_00715bfc); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
        if (*piVar2 == *(int *)(iVar10 + iVar9)) {
          iVar5 = (int)(piVar2[4]);
          goto label_005d05f9;
        }
      }
      iVar5 = (int)(0);
label_005d05f9:
      uVar3 = (uint)(*(uint *)(iVar10 + 0xc + iVar9));
      fn_005d1190((uint)(iVar5), (int)(*(undefined4 *)(iVar10 + 4 + iVar9)), (int)(*(undefined4 *)(iVar10 + 8 + iVar9)), (char)(uVar3 & 1), (char)(uVar3 & 4));
      uVar11 = (uint)(uVar11 + 1);
      iVar9 = (int)(iVar9 + 0x10);
    } while (uVar11 < uVar8);
  }
  fn_00554930((int)(native_006eabf2), (undefined1)(2));
  fn_005d6dd0((undefined4)(native_006eabf2), (int)(0xffffffff), (uint)((*(uint *)(param_1 + 0x32) >> 2) - native_006ea880));
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  iVar10 = (int)(*(int *)(native_006eabf2 + 0x2c));
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  fn_00554930((int)(native_006eabf2), (undefined1)(1));
  uVar8 = (uint)((*(int *)(native_006eabf2 + 0x2c) - iVar10) - 1);
  if (uVar8 > 0x7f) {
    CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xe75));
  }
  iVar9 = (int)(native_006eabf2);
  uVar11 = (uint)((uint)(iVar10 != -1));
  do {
    bVar7 = (byte)((byte)uVar8 & 0x7f);
    uVar8 = (uint)(uVar8 >> 7);
    if (uVar8 != 0) {
      bVar7 = (byte)(bVar7 | 0x80);
    }
    if ((char)uVar11 == '\0') {
      fn_00554930((int)(iVar9), (undefined1)(bVar7));
    }
    else {
      fn_00554830((int)(iVar9), (int)(iVar10), (undefined1)(bVar7));
      iVar10 = (int)(iVar10 + 1);
    }
  } while (uVar8 != 0);
  native_006ea880 = (int)(0);
  native_006ea884 = (int)(1);
  native_006ea888 = (int)(1);
  native_006ea88c = (int)(0);
  native_006ea890 = (int)(native_006ea87c);
  native_006ea894 = (int)(0);
  native_006ea898 = (int)(0);
  iVar10 = (int)(*(int *)(native_006eabf2 + 0x2c) - iVar14);
  uVar8 = (uint)((uint)*(byte *)(param_1 + 0x6e));
  iVar9 = (int)(*(int *)(param_1 + 0x1a));
  iVar5 = (int)(-1);
  pcVar12 = (char*)(literal_006b49c5);
  do {
    if (iVar5 == 0) break;
    iVar5 = (int)(iVar5 - 1);
    cVar1 = (char)(*pcVar12);
    pcVar12 = (char*)(pcVar12 + 1);
  } while (cVar1 != '\0');
  iVar5 = (int)(-iVar5 - 2);
  iVar6 = (int)(-1);
  pcVar12 = (char*)((char *)(iVar9 + 10));
  do {
    if (iVar6 == 0) break;
    iVar6 = (int)(iVar6 - 1);
    cVar1 = (char)(*pcVar12);
    pcVar12 = (char*)(pcVar12 + 1);
  } while (cVar1 != '\0');
  iVar13 = (int)(-iVar6 - 2);
  iVar15 = (int)(native_006eabf2);
  iVar4 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
  iVar6 = (int)(0);
  for (; iVar5 != 0; iVar5 = iVar5 - 1) {
    *(char *)(iVar4 + iVar6) = literal_006b49c5[iVar6];
    iVar6 = (int)(iVar6 + 1);
  }
  iVar5 = (int)(0);
  for (; iVar13 != 0; iVar13 = iVar13 - 1) {
    *(undefined1 *)(iVar4 + iVar6) = *(undefined1 *)(iVar9 + 10 + iVar5);
    iVar6 = (int)(iVar6 + 1);
    iVar5 = (int)(iVar5 + 1);
  }
  *(undefined1 *)(iVar4 + iVar6) = 0;
  fn_005cd6a0((undefined4)(iVar4), (undefined4)(iVar15), (byte)(uVar8 & 0xff), (undefined4)(1), (undefined4)(iVar10), (int)(iVar14));
  return;
}

void fn_005d0820(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  bool bVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int local_20;
  int local_1c;
  int local_14;

  local_20 = (int)(0);
  local_1c = (int)(0);
  iVar9 = (int)(0);
  do {
    iVar11 = (int)(iVar9 + 8);
    (&native_006ea078)[iVar9] = 0;
    (&native_006ea07c)[iVar9] = 0;
    (&native_006ea080)[iVar9] = 0;
    (&native_006ea084)[iVar9] = 0;
    (&native_006ea088)[iVar9] = 0;
    (&native_006ea08c)[iVar9] = 0;
    (&native_006ea090)[iVar9] = 0;
    (&native_006ea094)[iVar9] = 0;
    iVar9 = (int)(iVar11);
    puVar5 = (undefined4*)(native_007108c8);
  } while (iVar11 < 0x200);
  for (; puVar5 != (undefined4 *)0x0; puVar5 = (undefined4 *)*puVar5) {
    iVar9 = (int)(puVar5[8]);
    for (puVar1 = (undefined4*)((undefined4 *)puVar5[5]); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if (((int *)puVar1[8] != (int *)0x0) && (*(int *)puVar1[8] != 0) &&
         (iVar11 = puVar1[8], iVar11 != local_1c)) {
        uVar10 = (uint)(*(uint *)(iVar11 + 8));
        uVar12 = (uint)(uVar10 >> 2 & 0x1ff);
        for (puVar8 = (undefined4*)((undefined4 *)(&native_006ea078)[uVar12]); puVar8 != (undefined4 *)0x0;
            puVar8 = (undefined4 *)*puVar8) {
          if (puVar8[1] == uVar10) {
            puVar8[3] = (undefined4)(iVar9);
            goto label_005d0946;
          }
        }
        puVar8 = (undefined4*)((undefined4 *)CompilerTools_AllocatePool((int)(0x10)));
        memclrw((undefined1 *)(puVar8), (int)(0x10));
        *puVar8 = (undefined4)((&native_006ea078)[uVar12]);
        (&native_006ea078)[uVar12] = puVar8;
        puVar8[1] = (undefined4)(uVar10);
        puVar8[3] = (undefined4)(iVar9);
        puVar8[2] = (undefined4)(puVar8[3]);
label_005d0946:
        local_20 = (int)(local_20 + 1);
        local_1c = (int)(iVar11);
      }
      iVar9 = (int)(iVar9 + 4);
    }
  }
  uVar7 = (undefined4)(galloc((int)(local_20 << 4)));
  *(undefined4 *)(param_1 + 0x66) = uVar7;
  *(int *)(param_1 + 0x62) = local_20;
  local_1c = (int)(0);
  local_14 = (int)(0);
  iVar9 = (int)(local_14);
  puVar5 = (undefined4*)(native_007108c8);
  do {
    if (puVar5 == (undefined4 *)0x0) {
      if (local_20 != iVar9) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x1038));
      }
      return;
    }
    bVar6 = (bool)(true);
    iVar11 = (int)(puVar5[8]);
    for (puVar1 = (undefined4*)((undefined4 *)puVar5[5]); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      local_14 = (int)(iVar9);
      if (((int *)puVar1[8] != (int *)0x0) && (*(int *)puVar1[8] != 0) &&
         (iVar2 = puVar1[8], iVar2 != local_1c)) {
        uVar10 = (uint)(*(uint *)(iVar2 + 8));
        uVar12 = (uint)(uVar10 >> 2 & 0x1ff);
        for (puVar8 = (undefined4*)((undefined4 *)(&native_006ea078)[uVar12]); puVar8 != (undefined4 *)0x0;
            puVar8 = (undefined4 *)*puVar8) {
          if (puVar8[1] == uVar10) {
            puVar8[3] = (undefined4)(iVar11);
            goto label_005d0a56;
          }
        }
        puVar8 = (undefined4*)((undefined4 *)CompilerTools_AllocatePool((int)(0x10)));
        memclrw((undefined1 *)(puVar8), (int)(0x10));
        *puVar8 = (undefined4)((&native_006ea078)[uVar12]);
        (&native_006ea078)[uVar12] = puVar8;
        puVar8[1] = (undefined4)(uVar10);
        puVar8[3] = (undefined4)(iVar11);
        puVar8[2] = (undefined4)(puVar8[3]);
label_005d0a56:
        iVar3 = (int)(puVar8[2]);
        iVar4 = (int)(puVar8[3]);
        uVar7 = (undefined4)(((undefined4 *)puVar1[8])[2]);
        local_14 = (int)(iVar9 + 1);
        puVar8 = (undefined4*)((undefined4 *)(iVar9 * 0x10 + *(int *)(param_1 + 0x66)));
        *puVar8 = (undefined4)(**(undefined4 **)puVar1[8]);
        puVar8[1] = (undefined4)(uVar7);
        puVar8[2] = (undefined4)(iVar11);
        puVar8[3] = (undefined4)(puVar8[3] | (uint)(iVar3 == iVar11));
        if (iVar4 == iVar11) {
          uVar10 = (uint)(2);
        }
        else {
          uVar10 = (uint)(0);
        }
        puVar8[3] = (undefined4)(puVar8[3] | uVar10);
        if (bVar6) {
          uVar10 = (uint)(4);
        }
        else {
          uVar10 = (uint)(0);
        }
        puVar8[3] = (undefined4)(puVar8[3] | uVar10);
        bVar6 = (bool)(false);
        local_1c = (int)(iVar2);
      }
      iVar11 = (int)(iVar11 + 4);
      iVar9 = (int)(local_14);
    }
    puVar5 = (undefined4*)((undefined4 *)*puVar5);
  } while( true );
}

void fn_005d0b20(void)

{
  int *piVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;

  piVar1 = (int*)(native_00715bfc);
  do {
    if (piVar1 == (int *)0x0) {
      uVar4 = (uint)(0);
label_005d0b59:
      if (native_006ea884 == uVar4) {
        fn_00554930((int)(native_006eabf2), (undefined1)(4));
        iVar5 = (int)(native_006eabf2);
        do {
          bVar3 = (byte)((byte)uVar4 & 0x7f);
          uVar4 = (uint)(uVar4 >> 7);
          if (uVar4 != 0) {
            bVar3 = (byte)(bVar3 | 0x80);
          }
          fn_00554930((int)(iVar5), (undefined1)(bVar3));
        } while (uVar4 != 0);
      }
      else {
        native_006ea884 = (int)(uVar4);
        fn_00554930((int)(native_006eabf2), (undefined1)(4));
        iVar5 = (int)(native_006eabf2);
        do {
          bVar3 = (byte)((byte)uVar4 & 0x7f);
          uVar4 = (uint)(uVar4 >> 7);
          if (uVar4 != 0) {
            bVar3 = (byte)(bVar3 | 0x80);
          }
          fn_00554930((int)(iVar5), (undefined1)(bVar3));
        } while (uVar4 != 0);
      }
      fn_00554930((int)(native_006eabf2), (undefined1)(0));
      iVar5 = (int)(*(int *)(native_006eabf2 + 0x2c));
      fn_00554930((int)(native_006eabf2), (undefined1)(0));
      fn_00554930((int)(native_006eabf2), (undefined1)(2));
      fn_005549c0((int)(native_006eabf2), (uint)(0));
      fn_00554a70((undefined4)(0x18), (int)(native_00710324), (undefined4)(*(int *)(native_006eabf2 + 0x2c) - 4), (undefined4)(*(undefined4 *)(*(int *)(native_006eac12 + 4) + 0x26)), (undefined4)(0));
      uVar4 = (uint)((*(int *)(native_006eabf2 + 0x2c) - iVar5) - 1);
      if (uVar4 > 0x7f) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xe75));
      }
      iVar2 = (int)(native_006eabf2);
      bVar6 = (bool)(iVar5 == -1);
      do {
        bVar3 = (byte)((byte)uVar4 & 0x7f);
        uVar4 = (uint)(uVar4 >> 7);
        if (uVar4 != 0) {
          bVar3 = (byte)(bVar3 | 0x80);
        }
        if (bVar6) {
          fn_00554930((int)(iVar2), (undefined1)(bVar3));
        }
        else {
          fn_00554830((int)(iVar2), (int)(iVar5), (undefined1)(bVar3));
          iVar5 = (int)(iVar5 + 1);
        }
      } while (uVar4 != 0);
      native_006ea880 = (int)(0);
      return;
    }
    if (*piVar1 == *(int *)(*(int *)(native_006eac12 + 4) + 0x42)) {
      uVar4 = (uint)(piVar1[4]);
      goto label_005d0b59;
    }
    piVar1 = (int*)((int *)piVar1[1]);
  } while( true );
}

void fn_005d0ce0(void)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  uint uVar10;
  char *pcVar11;
  int iVar12;
  undefined1 local_28 [16];
  int *local_18;
  int local_14;

  native_006ea878 = (int)(fn_005549c0((int)(native_006eabf2), (uint)(0)));
  fn_00554960((int)(native_006eabf2), (undefined2)(2));
  local_14 = (int)(fn_005549c0((int)(native_006eabf2), (uint)(0)));
  fn_00554930((int)(native_006eabf2), (undefined1)(4));
  native_006ea87c = (int)(1);
  fn_00554930((int)(native_006eabf2), (undefined1)(1));
  fn_00554930((int)(native_006eabf2), (undefined1)(0xff));
  fn_00554930((int)(native_006eabf2), (undefined1)(4));
  fn_00554930((int)(native_006eabf2), (undefined1)(0xc));
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  fn_00554930((int)(native_006eabf2), (undefined1)(1));
  fn_00554930((int)(native_006eabf2), (undefined1)(1));
  fn_00554930((int)(native_006eabf2), (undefined1)(1));
  fn_00554930((int)(native_006eabf2), (undefined1)(1));
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  fn_00554930((int)(native_006eabf2), (undefined1)(1));
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  for (puVar2 = (undefined4*)(native_0071008c); puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)puVar2[1]) {
    if (*(char *)(puVar2 + 2) != '\0') {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xf6e));
    }
    if ((*(byte *)((int)puVar2 + 0x32) >> 3 & 1) == 0) {
      fn_005d10f0((int)(*puVar2), (char)(*(byte *)((int)puVar2 + 0x32) >> 1 & 1));
    }
  }
  for (piVar3 = (int*)(native_00710220); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]) {
    fn_005548f0((int)(native_006eabf2), (char *)(*piVar3 + 10));
  }
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  local_18 = (int*)(native_00715bfc);
  if (native_00715bfc != (int *)0x0) {
    for (; local_18 != (int *)0x0; local_18 = (int *)local_18[1]) {
      pcVar9 = (char*)((char *)(*local_18 + 10));
      iVar6 = (int)(-1);
      pcVar11 = (char*)(pcVar9);
      do {
        if (iVar6 == 0) break;
        iVar6 = (int)(iVar6 - 1);
        cVar1 = (char)(*pcVar11);
        pcVar11 = (char*)(pcVar11 + 1);
      } while (cVar1 != '\0');
      for (iVar6 = (int)(-iVar6 - 2); iVar6 != 0 && (pcVar9[iVar6] != '\\'); iVar6 = iVar6 - 1) {
      }
      if (iVar6 != 0) {
        pcVar9 = (char*)((char *)(*local_18 + 0xb + iVar6));
      }
      fn_005548f0((int)(native_006eabf2), (char *)(pcVar9));
      iVar6 = (int)(native_006eabf2);
      uVar10 = (uint)(local_18[5]);
      do {
        bVar4 = (byte)((byte)uVar10 & 0x7f);
        uVar10 = (uint)(uVar10 >> 7);
        if (uVar10 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar6), (undefined1)(bVar4));
        iVar7 = (int)(native_006eabf2);
      } while (uVar10 != 0);
      uVar10 = (uint)(local_18[2]);
      do {
        bVar4 = (byte)((byte)uVar10 & 0x7f);
        uVar10 = (uint)(uVar10 >> 7);
        if (uVar10 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar7), (undefined1)(bVar4));
        iVar6 = (int)(native_006eabf2);
      } while (uVar10 != 0);
      uVar10 = (uint)(local_18[3]);
      do {
        bVar4 = (byte)((byte)uVar10 & 0x7f);
        uVar10 = (uint)(uVar10 >> 7);
        if (uVar10 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar6), (undefined1)(bVar4));
      } while (uVar10 != 0);
    }
  }
  fn_00554930((int)(native_006eabf2), (undefined1)(0));
  fn_00554890((int)(native_006eabf2), (int)(local_14), (uint)(*(int *)(native_006eabf2 + 0x2c) - 10));
  local_18 = (int*)(*(int **)(native_006eabf2 + 0x2c));
  local_14 = (int)(native_006eabf2);
  native_0070bc24 = (int)(0);
  fn_00455ea0((char *)(local_28));
  fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_28));
  fn_0044cfe0((int)(native_0070bc20));
  iVar6 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
  fn_0044d0a0((int)(native_0070bc20));
  iVar7 = (int)(-1);
  pcVar9 = (char*)(literal_006b4a4f);
  do {
    if (iVar7 == 0) break;
    iVar7 = (int)(iVar7 - 1);
    cVar1 = (char)(*pcVar9);
    pcVar9 = (char*)(pcVar9 + 1);
  } while (cVar1 != '\0');
  iVar7 = (int)(-iVar7 - 2);
  iVar8 = (int)(-1);
  pcVar9 = (char*)((char *)(iVar6 + 10));
  do {
    if (iVar8 == 0) break;
    iVar8 = (int)(iVar8 - 1);
    cVar1 = (char)(*pcVar9);
    pcVar9 = (char*)(pcVar9 + 1);
  } while (cVar1 != '\0');
  iVar12 = (int)(-iVar8 - 2);
  iVar5 = (int)(galloc((int)(-iVar8 + -1 + iVar7)));
  iVar8 = (int)(0);
  for (; iVar7 != 0; iVar7 = iVar7 - 1) {
    *(char *)(iVar5 + iVar8) = literal_006b4a4f[iVar8];
    iVar8 = (int)(iVar8 + 1);
  }
  iVar7 = (int)(0);
  for (; iVar12 != 0; iVar12 = iVar12 - 1) {
    *(undefined1 *)(iVar5 + iVar8) = *(undefined1 *)(iVar6 + 10 + iVar7);
    iVar8 = (int)(iVar8 + 1);
    iVar7 = (int)(iVar7 + 1);
  }
  *(undefined1 *)(iVar5 + iVar8) = 0;
  fn_005cd6a0((undefined4)(iVar5), (undefined4)(local_14), (byte)(0), (undefined4)(1), (undefined4)(local_18), (int)(0));
  native_006ea880 = (int)(0);
  native_006ea884 = (int)(1);
  native_006ea888 = (int)(1);
  native_006ea88c = (int)(0);
  native_006ea890 = (int)(native_006ea87c);
  native_006ea894 = (int)(0);
  native_006ea898 = (int)(0);
  return;
}

void fn_005d10f0(int param_1, char param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;

  if (native_0070f287 != '\0') {
    piVar2 = (int*)((int *)galloc((int)(0x18)));
    memclrw((undefined1 *)(piVar2), (int)(0x18));
    piVar1 = (int*)(piVar2);
    if (native_00716ccc != (int *)0x0) {
      *(int **)((int)native_00716ccc + 4) = piVar2;
      piVar1 = (int*)(native_00715bfc);
    }
    native_00715bfc = (int *)(piVar1);
    native_00716ccc = (int *)(piVar2);
    *piVar2 = (int)(param_1);
    if (param_2 != '\0') {
      *(int *)(native_00710710 + 0x32) = param_1;
    }
    piVar2[2] = (int)(0);
    piVar2[3] = (int)(0);
    iVar3 = (int)(fn_005d5f30((char *)(param_1 + 10), (char)(param_2)));
    piVar2[5] = (int)(iVar3);
    native_00716d7c = (int)(native_00716d7c + 1);
    piVar2[4] = (int)(native_00716d7c);
    return;
  }
  return;
}

void fn_005d1190(uint param_1, int param_2, int param_3, char param_4, char param_5)

{
  undefined4 uVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;

  if (native_006ea88c != 0) {
    fn_00554930((int)(native_006eabf2), (undefined1)(5));
    fn_00554930((int)(native_006eabf2), (undefined1)(0));
    native_006ea88c = (int)(0);
  }
  if (param_1 != native_006ea884) {
    if (native_006ea890 != 0) {
      fn_00554930((int)(native_006eabf2), (undefined1)(6));
      native_006ea890 = (int)(0);
    }
    if (native_006ea884 != param_1) {
      native_006ea884 = (int)(param_1);
      fn_00554930((int)(native_006eabf2), (undefined1)(4));
      uVar1 = (undefined4)(native_006eabf2);
      do {
        bVar3 = (byte)((byte)param_1 & 0x7f);
        param_1 = (uint)(param_1 >> 7);
        if (param_1 != 0) {
          bVar3 = (byte)(bVar3 | 0x80);
        }
        fn_00554930((int)(uVar1), (undefined1)(bVar3));
      } while (param_1 != 0);
    }
  }
  iVar2 = (int)((int)(param_3 + (param_3 >> 0x1f & 3U)) >> 2);
  uVar5 = (uint)(iVar2 - native_006ea880);
  iVar6 = (int)(param_2 - native_006ea888);
  if ((int)uVar5 < 0) {
    return;
  }
  uVar4 = (uint)(uVar5 * 4 + iVar6 + 0xd);
  if ((iVar6 < -1) || (iVar6 > 2) || ((int)uVar4 > 0xff)) {
    if (iVar6 != 0) {
      fn_00554930((int)(native_006eabf2), (undefined1)(3));
      fn_005d6dd0((undefined4)(native_006eabf2), (int)(0xffffffff), (uint)(iVar6));
    }
    if (uVar5 != 0) {
      fn_00554930((int)(native_006eabf2), (undefined1)(2));
      uVar1 = (undefined4)(native_006eabf2);
      do {
        bVar3 = (byte)((byte)uVar5 & 0x7f);
        uVar5 = (uint)(uVar5 >> 7);
        if (uVar5 != 0) {
          bVar3 = (byte)(bVar3 | 0x80);
        }
        fn_00554930((int)(uVar1), (undefined1)(bVar3));
      } while (uVar5 != 0);
    }
    fn_00554930((int)(native_006eabf2), (undefined1)(1));
  }
  else {
    fn_00554930((int)(native_006eabf2), (undefined1)(uVar4 & 0xff));
    native_006ea894 = (int)(0);
  }
  if (param_4 == '\0') {
    if (native_006ea890 != 0) {
      fn_00554930((int)(native_006eabf2), (undefined1)(6));
      native_006ea890 = (int)(0);
    }
  }
  else if (native_006ea890 == 0) {
    fn_00554930((int)(native_006eabf2), (undefined1)(6));
    native_006ea890 = (int)(1);
  }
  if (param_5 == '\0') {
    if (native_006ea894 != 0) {
      fn_00554930((int)(native_006eabf2), (undefined1)(1));
      native_006ea894 = (int)(0);
    }
  }
  else if (native_006ea894 == 0) {
    fn_00554930((int)(native_006eabf2), (undefined1)(7));
    native_006ea894 = (int)(1);
  }
  native_006ea880 = (int)(iVar2);
  native_006ea888 = (int)(param_2);
  return;
}

void fn_005d1400(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  char cVar7;
  int iVar8;
  char *pcVar9;
  undefined1 local_b8 [16];
  undefined1 local_a8 [16];
  undefined1 local_98 [16];
  undefined1 local_88 [16];
  undefined1 local_78 [16];
  undefined1 local_68 [16];
  undefined1 local_58 [16];
  undefined1 local_48 [16];
  undefined1 local_38 [16];
  uint local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  int local_18;
  uint local_14;

  switch(*(undefined2 *)(param_1 + 0x14)) {
  case 1:
    local_28 = (uint)(*(int *)(param_1 + 8));
    local_1c = (int)((*(int *)(*(int *)(param_1 + 0x22) + 8) - local_28) + 1);
    native_0070bc24 = (int)(0);
    fn_00455ea0((char *)(local_a8));
    fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_a8));
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    local_24 = (uint)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49b8);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49b8[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_24), (byte)(0), (undefined4)(1), (undefined4)(local_1c), (int)(local_28)));
    *(undefined4 *)(param_1 + 0x26) = uVar4;
    break;
  case 2:
  case 0x13:
  case 0x17:
    if (*(int *)(param_1 + 0x24) == 0) {
      cVar7 = (char)(-2);
    }
    else {
      cVar7 = (char)('\0');
    }
    local_14 = (uint)(*(int *)(param_1 + 8));
    local_1c = (int)((*(int *)(*(int *)(param_1 + 0x28) + 8) - local_14) + 1);
    native_0070bc24 = (int)(0);
    if (*(int *)(param_1 + 0x1e) == 0) {
      fn_00455ea0((char *)(local_38));
      fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_38));
      (*(char *)&local_28) = '\0';
    }
    else {
      fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(*(int *)(param_1 + 0x1e) + 10));
      (*(char *)&local_28) = '\x02';
    }
    if (cVar7 != '\0') {
      (*(char *)&local_28) = cVar7;
    }
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    local_18 = (int)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49b8);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49b8[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_18), (byte)((char)local_28), (undefined4)(1), (undefined4)(local_1c), (int)(local_14)));
    *(undefined4 *)(param_1 + 0x30) = uVar4;
    break;
  case 4:
    local_14 = (uint)(*(int *)(param_1 + 8));
    local_1c = (int)((*(int *)(*(int *)(param_1 + 0x22) + 8) - local_14) + 1);
    native_0070bc24 = (int)(0);
    if (*(int *)(param_1 + 0x1a) == 0) {
      fn_00455ea0((char *)(local_48));
      fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_48));
      *(unsigned char *)&local_28 = 0;
    }
    else {
      fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(*(int *)(param_1 + 0x1a) + 10));
      *(unsigned char *)&local_28 = 2;
    }
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    local_18 = (int)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49b8);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49b8[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_18), (byte)(local_28 & 0xff), (undefined4)(1), (undefined4)(local_1c), (int)(local_14)));
    *(undefined4 *)(param_1 + 0x26) = uVar4;
    break;
  case 5:
    goto switchD_005d1421_caseD_5;
  case 0xf:
    local_20 = (uint)(*(undefined4 *)(param_1 + 8));
    local_24 = (uint)(*(undefined4 *)(param_1 + 0xc));
    native_0070bc24 = (int)(0);
    fn_00455ea0((char *)(local_78));
    fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_78));
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    local_14 = (uint)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49b8);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49b8[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_14), (byte)(0), (undefined4)(1), (undefined4)(local_24), (int)(local_20)));
    *(undefined4 *)(param_1 + 0x1e) = uVar4;
    break;
  case 0x11:
    local_14 = (uint)(*(undefined4 *)(param_1 + 8));
    local_24 = (uint)(*(undefined4 *)(param_1 + 0xc));
    local_20 = (uint)(native_006eabfe);
    native_0070bc24 = (int)(0);
    fn_00455ea0((char *)(local_b8));
    fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_b8));
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49f5);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49f5[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_20), (byte)(0), (undefined4)(1), (undefined4)(local_24), (int)(local_14));
    break;
  case 0x15:
    if (*(int *)(param_1 + 0x22) == 0) {
      local_1c = (int)(*(int *)(param_1 + 0xc));
    }
    else {
      local_1c = (int)((*(int *)(*(int *)(param_1 + 0x22) + 8) - *(int *)(param_1 + 8)) + 1);
    }
    local_20 = (uint)(*(undefined4 *)(param_1 + 8));
    native_0070bc24 = (int)(0);
    fn_00455ea0((char *)(local_68));
    fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_68));
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    local_14 = (uint)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49b8);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49b8[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_14), (byte)(0), (undefined4)(1), (undefined4)(local_1c), (int)(local_20)));
    *(undefined4 *)(param_1 + 0x1e) = uVar4;
    break;
  case 0x16:
    local_20 = (uint)(*(undefined4 *)(param_1 + 8));
    local_18 = (int)(*(undefined4 *)(param_1 + 0xc));
    native_0070bc24 = (int)(0);
    if (*(int *)(param_1 + 0x16) == 0) {
      fn_00455ea0((char *)(local_58));
      fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_58));
      *(unsigned char *)&local_14 = 0;
    }
    else {
      fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(*(int *)(param_1 + 0x16) + 10));
      *(unsigned char *)&local_14 = 2;
    }
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    local_24 = (uint)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49b8);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49b8[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_24), (byte)(local_14 & 0xff), (undefined4)(1), (undefined4)(local_18), (int)(local_20)));
    *(undefined4 *)(param_1 + 0x22) = uVar4;
    break;
  case 0x1f:
    local_24 = (uint)(*(undefined4 *)(param_1 + 8));
    local_20 = (uint)(*(undefined4 *)(param_1 + 0xc));
    native_0070bc24 = (int)(0);
    fn_00455ea0((char *)(local_98));
    fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_98));
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    local_28 = (uint)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49b8);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49b8[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_28), (byte)(0), (undefined4)(1), (undefined4)(local_20), (int)(local_24)));
    *(undefined4 *)(param_1 + 0x2a) = uVar4;
    break;
  case 0x24:
    local_20 = (uint)(*(undefined4 *)(param_1 + 8));
    local_18 = (int)(*(undefined4 *)(param_1 + 0xc));
    native_0070bc24 = (int)(0);
    if (*(int *)(param_1 + 0x16) == 0) {
      fn_00455ea0((char *)(local_88));
      fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(local_88));
      *(unsigned char *)&local_28 = 0;
    }
    else {
      fn_0046d5a0((undefined4 *)(&native_0070bc20), (char *)(*(int *)(param_1 + 0x16) + 10));
      *(unsigned char *)&local_28 = 2;
    }
    fn_0044cfe0((int)(native_0070bc20));
    iVar2 = (int)(GetHashNameNode((char *)(*native_0070bc20)));
    fn_0044d0a0((int)(native_0070bc20));
    local_24 = (uint)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(literal_006b49b8);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(char *)(iVar3 + iVar6) = literal_006b49b8[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_24), (byte)(local_28 & 0xff), (undefined4)(1), (undefined4)(local_18), (int)(local_20)));
    *(undefined4 *)(param_1 + 0x26) = uVar4;
    break;
  case 0x2e:
    if (*(int *)(param_1 + 0x6a) == 0) {
      local_1c = (int)(*(int *)(param_1 + 0xc));
    }
    else {
      local_1c = (int)((*(int *)(*(int *)(param_1 + 0x6a) + 8) - *(int *)(param_1 + 8)) + 1);
    }
    local_14 = (uint)(*(undefined4 *)(param_1 + 8));
    local_24 = (uint)((uint)*(byte *)(param_1 + 0x6e));
    iVar2 = (int)(*(int *)(param_1 + 0x1a));
    local_18 = (int)(native_006eabfe);
    iVar5 = (int)(-1);
    pcVar9 = (char*)(&native_006b49de);
    do {
      if (iVar5 == 0) break;
      iVar5 = (int)(iVar5 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar5 = (int)(-iVar5 - 2);
    iVar6 = (int)(-1);
    pcVar9 = (char*)((char *)(iVar2 + 10));
    do {
      if (iVar6 == 0) break;
      iVar6 = (int)(iVar6 - 1);
      cVar7 = (char)(*pcVar9);
      pcVar9 = (char*)(pcVar9 + 1);
    } while (cVar7 != '\0');
    iVar8 = (int)(-iVar6 - 2);
    iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
    iVar6 = (int)(0);
    for (; iVar5 != 0; iVar5 = iVar5 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = (&native_006b49de)[iVar6];
      iVar6 = (int)(iVar6 + 1);
    }
    iVar5 = (int)(0);
    for (; iVar8 != 0; iVar8 = iVar8 - 1) {
      *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
      iVar6 = (int)(iVar6 + 1);
      iVar5 = (int)(iVar5 + 1);
    }
    *(undefined1 *)(iVar3 + iVar6) = 0;
    uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_18), (byte)(local_24 & 0xff), (undefined4)(1), (undefined4)(local_1c), (int)(local_14)));
    *(undefined4 *)(param_1 + 0x2a) = uVar4;
    if (*(char *)(param_1 + 0x78) == '\0') {
      local_28 = (uint)(*(int *)(param_1 + 0x5e));
      local_1c = (int)(*(int *)(native_006eabde + 0x2c) - local_28);
      local_20 = (uint)((uint)*(byte *)(param_1 + 0x6e));
      iVar2 = (int)(*(int *)(param_1 + 0x1a));
      local_18 = (int)(native_006eabde);
      iVar5 = (int)(-1);
      pcVar9 = (char*)(literal_006b49d2);
      do {
        if (iVar5 == 0) break;
        iVar5 = (int)(iVar5 - 1);
        cVar7 = (char)(*pcVar9);
        pcVar9 = (char*)(pcVar9 + 1);
      } while (cVar7 != '\0');
      iVar5 = (int)(-iVar5 - 2);
      iVar6 = (int)(-1);
      pcVar9 = (char*)((char *)(iVar2 + 10));
      do {
        if (iVar6 == 0) break;
        iVar6 = (int)(iVar6 - 1);
        cVar7 = (char)(*pcVar9);
        pcVar9 = (char*)(pcVar9 + 1);
      } while (cVar7 != '\0');
      iVar8 = (int)(-iVar6 - 2);
      iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
      iVar6 = (int)(0);
      for (; iVar5 != 0; iVar5 = iVar5 - 1) {
        *(char *)(iVar3 + iVar6) = literal_006b49d2[iVar6];
        iVar6 = (int)(iVar6 + 1);
      }
      iVar5 = (int)(0);
      for (; iVar8 != 0; iVar8 = iVar8 - 1) {
        *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
        iVar6 = (int)(iVar6 + 1);
        iVar5 = (int)(iVar5 + 1);
      }
      *(undefined1 *)(iVar3 + iVar6) = 0;
      uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_18), (byte)(local_20 & 0xff), (undefined4)(1), (undefined4)(local_1c), (int)(local_28)));
      *(undefined4 *)(param_1 + 0x2e) = uVar4;
    }
    break;
  case 0x34:
    if ((*(char *)(param_1 + 0x61) == '\0') && (*(char *)(param_1 + 0x60) == '\0')) {
      local_28 = (uint)(*(uint *)(param_1 + 8));
      local_14 = (uint)(*(uint *)(param_1 + 0xc));
      local_20 = (uint)((uint)*(byte *)(param_1 + 0x66));
      iVar2 = (int)(*(int *)(param_1 + 0x1a));
      local_18 = (int)(native_006eabfe);
      iVar5 = (int)(-1);
      pcVar9 = (char*)(&native_006b49de);
      do {
        if (iVar5 == 0) break;
        iVar5 = (int)(iVar5 - 1);
        cVar7 = (char)(*pcVar9);
        pcVar9 = (char*)(pcVar9 + 1);
      } while (cVar7 != '\0');
      iVar5 = (int)(-iVar5 - 2);
      iVar6 = (int)(-1);
      pcVar9 = (char*)((char *)(iVar2 + 10));
      do {
        if (iVar6 == 0) break;
        iVar6 = (int)(iVar6 - 1);
        cVar7 = (char)(*pcVar9);
        pcVar9 = (char*)(pcVar9 + 1);
      } while (cVar7 != '\0');
      iVar8 = (int)(-iVar6 - 2);
      iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
      iVar6 = (int)(0);
      for (; iVar5 != 0; iVar5 = iVar5 - 1) {
        *(undefined1 *)(iVar3 + iVar6) = (&native_006b49de)[iVar6];
        iVar6 = (int)(iVar6 + 1);
      }
      iVar5 = (int)(0);
      for (; iVar8 != 0; iVar8 = iVar8 - 1) {
        *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
        iVar6 = (int)(iVar6 + 1);
        iVar5 = (int)(iVar5 + 1);
      }
      *(undefined1 *)(iVar3 + iVar6) = 0;
      uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_18), (byte)(local_20 & 0xff), (undefined4)(1), (undefined4)(local_14), (int)(local_28)));
      *(undefined4 *)(param_1 + 0x54) = uVar4;
    }
switchD_005d1421_caseD_5:
    if (*(char *)(param_1 + 0x61) != '\0') {
      return;
    }
    if (*(char *)(param_1 + 0x68) != '\0') {
      return;
    }
    if (*(char *)(param_1 + 0x67) != '\0') {
      return;
    }
    if (*(char *)(param_1 + 0x60) == '\0') {
      local_28 = (uint)(*(undefined4 *)(param_1 + 0x2c));
      local_14 = (uint)(*(undefined4 *)(param_1 + 0x30));
      local_24 = (uint)((uint)*(byte *)(param_1 + 0x66));
      iVar2 = (int)(*(int *)(param_1 + 0x1a));
      local_18 = (int)(native_006eabde);
      iVar5 = (int)(-1);
      pcVar9 = (char*)(literal_006b49d2);
      do {
        if (iVar5 == 0) break;
        iVar5 = (int)(iVar5 - 1);
        cVar7 = (char)(*pcVar9);
        pcVar9 = (char*)(pcVar9 + 1);
      } while (cVar7 != '\0');
      iVar5 = (int)(-iVar5 - 2);
      iVar6 = (int)(-1);
      pcVar9 = (char*)((char *)(iVar2 + 10));
      do {
        if (iVar6 == 0) break;
        iVar6 = (int)(iVar6 - 1);
        cVar7 = (char)(*pcVar9);
        pcVar9 = (char*)(pcVar9 + 1);
      } while (cVar7 != '\0');
      iVar8 = (int)(-iVar6 - 2);
      iVar3 = (int)(galloc((int)(-iVar6 + -1 + iVar5)));
      iVar6 = (int)(0);
      for (; iVar5 != 0; iVar5 = iVar5 - 1) {
        *(char *)(iVar3 + iVar6) = literal_006b49d2[iVar6];
        iVar6 = (int)(iVar6 + 1);
      }
      iVar5 = (int)(0);
      for (; iVar8 != 0; iVar8 = iVar8 - 1) {
        *(undefined1 *)(iVar3 + iVar6) = *(undefined1 *)(iVar2 + 10 + iVar5);
        iVar6 = (int)(iVar6 + 1);
        iVar5 = (int)(iVar5 + 1);
      }
      *(undefined1 *)(iVar3 + iVar6) = 0;
      uVar4 = (undefined4)(fn_005cd6a0((undefined4)(iVar3), (undefined4)(local_18), (byte)(local_24 & 0xff), (undefined4)(1), (undefined4)(local_14), (int)(local_28)));
      *(undefined4 *)(param_1 + 0x44) = uVar4;
      return;
    }
    iVar2 = (int)(*(int *)(param_1 + 0x62));
    sVar1 = (short)(*(short *)(iVar2 + 0x14));
    if (sVar1 == 5) {
label_005d1da0:
      uVar4 = (undefined4)(*(undefined4 *)(iVar2 + 0x44));
    }
    else if (sVar1 == 0x2e) {
      uVar4 = (undefined4)(*(undefined4 *)(iVar2 + 0x2e));
    }
    else {
      if (sVar1 == 0x34) goto label_005d1da0;
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xcf1));
      uVar4 = (undefined4)(0);
    }
    *(undefined4 *)(param_1 + 0x44) = uVar4;
  }
  return;
}

void fn_005d2440(int param_1)

{
  short sVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;

  switch(*(undefined2 *)(param_1 + 0x14)) {
  case 1:
    if (*(int *)(*(int *)(param_1 + 0x16) + 8) == 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd0e));
    }
    uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x16) + 8))));
    iVar7 = (int)(*(int *)(param_1 + 0x1a));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    break;
  case 5:
  case 0x34:
    if (*(int *)(*(int *)(param_1 + 0x1e) + 8) == 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd2a));
    }
    uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x1e) + 8))));
    iVar7 = (int)(*(int *)(param_1 + 0x22));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    if (*(char *)(param_1 + 0x61) != '\0') {
      return;
    }
    if (*(char *)(param_1 + 0x68) != '\0') {
      return;
    }
    if (*(char *)(param_1 + 0x67) != '\0') {
      return;
    }
    if (*(char *)(param_1 + 0x60) == '\0') {
      uVar4 = (undefined4)(0);
    }
    else {
      uVar4 = (undefined4)(*(undefined4 *)(param_1 + 0x2c));
    }
    sVar1 = (short)(*(short *)(param_1 + 0x14));
    if (sVar1 == 5) {
label_005d25f5:
      uVar5 = (undefined4)(*(undefined4 *)(param_1 + 0x44));
    }
    else if (sVar1 == 0x2e) {
      uVar5 = (undefined4)(*(undefined4 *)(param_1 + 0x2e));
    }
    else {
      if (sVar1 == 0x34) goto label_005d25f5;
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xcf1));
      uVar5 = (undefined4)(0);
    }
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(*(undefined4 *)(param_1 + 0x28)), (undefined4)(uVar5), (undefined4)(uVar4));
    break;
  case 0xb:
    uVar4 = (undefined4)(*(undefined4 *)(param_1 + 0x26));
    iVar7 = (int)(*(int *)(param_1 + 0x1a));
    uVar5 = (undefined4)(uVar4);
    if (native_006b4af6 == '\0') {
      uVar5 = (undefined4)(0);
    }
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(*(undefined4 *)(param_1 + 0x16)), (undefined4)(uVar5));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(uVar4)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    uVar4 = (undefined4)(*(undefined4 *)(param_1 + 0x2a));
    iVar7 = (int)(*(int *)(param_1 + 0x1e));
    uVar5 = (undefined4)(uVar4);
    if (native_006b4af6 == '\0') {
      uVar5 = (undefined4)(0);
    }
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(*(undefined4 *)(param_1 + 0x16)), (undefined4)(uVar5));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(uVar4)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    if (*(int *)(param_1 + 0x2e) != 0) {
      uVar4 = (undefined4)(*(undefined4 *)(*(int *)(param_1 + 0x2e) + 8));
      iVar7 = (int)(*(int *)(param_1 + 0x22));
      uVar5 = (undefined4)(uVar4);
      if (native_006b4af6 == '\0') {
        uVar5 = (undefined4)(0);
      }
      fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(native_007108d0), (undefined4)(uVar5));
      if (native_006b4af6 == '\0') {
        uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(uVar4)));
        *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
      }
    }
    break;
  case 0xd:
    if (**(char **)(*(int *)(param_1 + 0x1a) + 4) == '\b') {
      if (*(int *)(*(int *)(param_1 + 0x1e) + 8) == 0) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd1d));
      }
      uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x1e) + 8))));
      iVar7 = (int)(*(int *)(param_1 + 0x22));
      fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
      if (native_006b4af6 == '\0') {
        uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
        *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
      }
    }
    else {
      if (*(int *)(*(int *)(param_1 + 0x1a) + 8) == 0) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd21));
      }
      uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x1a) + 8))));
      iVar7 = (int)(*(int *)(param_1 + 0x22));
      fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
      if (native_006b4af6 == '\0') {
        uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
        *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
      }
    }
    break;
  case 0xf:
    if (*(int *)(*(int *)(param_1 + 0x16) + 8) == 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd44));
    }
    uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x16) + 8))));
    iVar7 = (int)(*(int *)(param_1 + 0x1a));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    break;
  case 0x15:
    if (*(int *)(*(int *)(param_1 + 0x16) + 8) == 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd69));
    }
    uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x16) + 8))));
    iVar7 = (int)(*(int *)(param_1 + 0x1a));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    break;
  case 0x16:
    iVar7 = (int)(*(int *)(*(int *)(param_1 + 0x1e) + 8));
    sVar1 = (short)(*(short *)(iVar7 + 0x14));
    if ((sVar1 == 2) || (sVar1 == 0x13) || (sVar1 == 0x17)) {
      iVar3 = (int)(*(int *)(param_1 + 0x1a));
      fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar3), (undefined4)(*(undefined4 *)(iVar7 + 0x30)), (undefined4)(0));
      if (native_006b4af6 == '\0') {
        uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
        *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar3) = uVar4;
      }
    }
    else if (sVar1 == 0x24) {
      iVar3 = (int)(*(int *)(param_1 + 0x1a));
      fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar3), (undefined4)(*(undefined4 *)(iVar7 + 0x26)), (undefined4)(0));
      if (native_006b4af6 == '\0') {
        uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
        *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar3) = uVar4;
      }
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd7e));
    }
    break;
  case 0x1c:
    if (*(int *)(*(int *)(param_1 + 0x16) + 8) == 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd15));
    }
    uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x16) + 8))));
    iVar7 = (int)(*(int *)(param_1 + 0x1a));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    break;
  case 0x1f:
    if (*(int *)(*(int *)(param_1 + 0x1e) + 8) == 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd4b));
    }
    if (*(int *)(*(int *)(param_1 + 0x1a) + 8) == 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd4d));
    }
    uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x1a) + 8))));
    iVar7 = (int)(*(int *)(param_1 + 0x22));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x1e) + 8))));
    iVar7 = (int)(*(int *)(param_1 + 0x26));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    break;
  case 0x2e:
    if (*(int *)(*(int *)(param_1 + 0x1e) + 8) == 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xd55));
    }
    uVar4 = (undefined4)(fn_005d2c80((int)(*(undefined4 *)(*(int *)(param_1 + 0x1e) + 8))));
    iVar7 = (int)(*(int *)(param_1 + 0x22));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(uVar4), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    iVar7 = (int)(*(int *)(param_1 + 0x46));
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(*(undefined4 *)(param_1 + 0x26)), (undefined4)(0));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    uVar4 = (undefined4)(*(undefined4 *)(param_1 + 0x32));
    iVar7 = (int)(*(int *)(param_1 + 0x4a));
    uVar5 = (undefined4)(uVar4);
    if (native_006b4af6 == '\0') {
      uVar5 = (undefined4)(0);
    }
    fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(*(undefined4 *)(param_1 + 0x26)), (undefined4)(uVar5));
    if (native_006b4af6 == '\0') {
      uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(uVar4)));
      *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
    }
    if (*(char *)(param_1 + 0x78) == '\0') {
      iVar7 = (int)(*(int *)(param_1 + 0x5a));
      fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar7), (undefined4)(*(undefined4 *)(param_1 + 0x2e)), (undefined4)(0));
      if (native_006b4af6 == '\0') {
        uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
        *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar7) = uVar4;
      }
    }
    iVar7 = (int)(0);
    for (puVar2 = (undefined4*)(*(undefined4 **)(param_1 + 0x70)); puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)*puVar2) {
      iVar3 = (int)(*(int *)(*(int *)(puVar2[1] + 4) + 0x38));
      if (iVar3 != 0) {
        iVar6 = (int)(*(int *)(param_1 + 0x74) + iVar7);
        fn_00554a70((undefined4)(0x18), (int)(native_007108d0), (undefined4)(iVar6), (undefined4)(*(undefined4 *)(iVar3 + 0x54)), (undefined4)(0));
        if (native_006b4af6 == '\0') {
          uVar4 = (undefined4)(CTool_EndianConvertWord32((undefined4)(0)));
          *(undefined4 *)(**(int **)(native_006eabfe + 0x28) + iVar6) = uVar4;
        }
      }
      iVar7 = (int)(iVar7 + 4);
    }
  }
  return;
}

undefined4 fn_005d2c80(int param_1)

{
  switch(*(undefined2 *)(param_1 + 0x14)) {
  case 1:
    return *(undefined4 *)(param_1 + 0x26);
  case 2:
  case 0x13:
  case 0x17:
    break;
  default:
    CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xcd1));
    return 0;
  case 4:
    return *(undefined4 *)(param_1 + 0x26);
  case 0xf:
    return *(undefined4 *)(param_1 + 0x1e);
  case 0x15:
    return *(undefined4 *)(param_1 + 0x1e);
  case 0x1f:
    return *(undefined4 *)(param_1 + 0x2a);
  case 0x24:
    return *(undefined4 *)(param_1 + 0x26);
  }
  if ((*(char *)(param_1 + 0x22) != '\0') && (*(int *)(param_1 + 0x2c) != 0)) {
    return *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x22);
  }
  return *(undefined4 *)(param_1 + 0x30);
}

void fn_005d2ce0(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  ushort uVar3;
  undefined4 *puVar4;
  int *piVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined1 uVar12;
  int iVar13;
  char *pcVar14;
  bool bVar15;

  if (*(short *)(param_1 + 0x14) == -1) {
    uVar10 = (undefined4)(fn_00554930((int)(native_006eabfe), (undefined1)(0)));
    *(undefined4 *)(param_1 + 8) = uVar10;
    return;
  }
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(native_006eabfe + 0x2c);
  switch(*(undefined2 *)(param_1 + 0x14)) {
  case 1:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(1);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    uVar10 = (undefined4)(*(undefined4 *)(param_1 + 0x1e));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0xb;
      (&native_006ea94a)[iVar8 * 2] = 6;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005549c0((int)(native_006eabfe), (uint)(uVar10));
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x49;
      (&native_006ea94a)[iVar7 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x1a) = uVar10;
    uVar11 = (uint)(fn_005d5b00((char)(1)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 2:
  case 0x13:
  case 0x17:
    uVar3 = (ushort)(*(ushort *)(param_1 + 0x14));
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)((uint)uVar3);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    uVar10 = (undefined4)(*(undefined4 *)(param_1 + 0x24));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0xb;
      (&native_006ea94a)[iVar8 * 2] = 6;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005549c0((int)(native_006eabfe), (uint)(uVar10));
    iVar7 = (int)(*(int *)(param_1 + 0x16));
    if (iVar7 != 0) {
      iVar8 = (int)(strchr((char *)(iVar7 + 10), (char)(0x24)));
      if (iVar8 == 0) {
        iVar9 = (int)(iVar7 + 10);
      }
      else {
        iVar8 = (int)(iVar8 - (iVar7 + 10));
        iVar9 = (int)(CompilerTools_AllocatePool((int)(iVar8 + 1)));
        strncpy((char *)(iVar9), (char *)(iVar7 + 10), (int)(iVar8));
        *(undefined1 *)(iVar9 + iVar8) = 0;
      }
      iVar7 = (int)(native_006ea93a);
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 3;
        (&native_006ea94a)[iVar7 * 2] = 8;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      fn_005548f0((int)(native_006eabfe), (char *)(iVar9));
    }
    uVar11 = (uint)(fn_005d5b00((char)(1)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  default:
    CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xc7b));
    break;
  case 4:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(4);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    uVar10 = (undefined4)(*(undefined4 *)(param_1 + 0x1e));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0xb;
      (&native_006ea94a)[iVar8 * 2] = 6;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005549c0((int)(native_006eabfe), (uint)(uVar10));
    iVar7 = (int)(*(int *)(param_1 + 0x16));
    if (iVar7 != 0) {
      iVar8 = (int)(strchr((char *)(iVar7 + 10), (char)(0x24)));
      if (iVar8 == 0) {
        iVar9 = (int)(iVar7 + 10);
      }
      else {
        iVar8 = (int)(iVar8 - (iVar7 + 10));
        iVar9 = (int)(CompilerTools_AllocatePool((int)(iVar8 + 1)));
        strncpy((char *)(iVar9), (char *)(iVar7 + 10), (int)(iVar8));
        *(undefined1 *)(iVar9 + iVar8) = 0;
      }
      iVar7 = (int)(native_006ea93a);
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 3;
        (&native_006ea94a)[iVar7 * 2] = 8;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      fn_005548f0((int)(native_006eabfe), (char *)(iVar9));
    }
    uVar11 = (uint)(fn_005d5b00((char)(1)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 5:
  case 0x34:
    uVar3 = (ushort)(*(ushort *)(param_1 + 0x14));
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)((uint)uVar3);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (*(char *)(param_1 + 0x61) == '\0') {
      if (*(char *)(param_1 + 0x67) == '\0') {
        uVar11 = (uint)(*(uint *)(param_1 + 0x5c));
        if (native_006ea93a < 0x50) {
          (&native_006ea946)[native_006ea93a * 2] = 0x3b;
          (&native_006ea94a)[iVar8 * 2] = 5;
          native_006ea93a = (int)(native_006ea93a + 1);
        }
        else {
          CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
        }
        fn_00554960((int)(native_006eabfe), (undefined2)(uVar11 & 0xffff));
        iVar7 = (int)(native_006ea93a);
        for (piVar5 = (int*)(native_00715bfc); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
          if (*piVar5 == *(int *)(param_1 + 0x58)) {
            uVar11 = (uint)(piVar5[4]);
            goto label_005d4c7d;
          }
        }
        uVar11 = (uint)(0);
label_005d4c7d:
        if (native_006ea93a < 0x50) {
          (&native_006ea946)[native_006ea93a * 2] = 0x3a;
          (&native_006ea94a)[iVar7 * 2] = 5;
          native_006ea93a = (int)(native_006ea93a + 1);
        }
        else {
          CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
        }
        fn_00554960((int)(native_006eabfe), (undefined2)(uVar11 & 0xffff));
      }
      iVar7 = (int)(native_006ea93a);
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0x49;
        (&native_006ea94a)[iVar7 * 2] = 0x10;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
      *(undefined4 *)(param_1 + 0x22) = uVar10;
      iVar7 = (int)(native_006ea93a);
      cVar1 = (char)(*(char *)(param_1 + 0x66));
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0x3f;
        (&native_006ea94a)[iVar7 * 2] = 0xc;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      fn_00554930((int)(native_006eabfe), (undefined1)(cVar1 != '\0'));
      iVar7 = (int)(native_006ea93a);
      if (*(char *)(param_1 + 0x67) == '\0') {
        if (*(char *)(param_1 + 0x68) == '\0') {
          if (native_006ea93a < 0x50) {
            (&native_006ea946)[native_006ea93a * 2] = 2;
            (&native_006ea94a)[iVar7 * 2] = 6;
            native_006ea93a = (int)(native_006ea93a + 1);
          }
          else {
            CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
          }
          uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
          *(undefined4 *)(param_1 + 0x28) = uVar10;
          uVar10 = (undefined4)(fn_005d63f0((int)(param_1), (int)(*(undefined4 *)(param_1 + 0x62))));
          *(undefined4 *)(param_1 + 0x2c) = uVar10;
          *(int *)(param_1 + 0x30) = *(int *)(native_006eabde + 0x2c) - *(int *)(param_1 + 0x2c);
        }
        else {
          fn_005d6010((int)(param_1), (int)(*(undefined4 *)(param_1 + 0x62)));
        }
      }
      else {
        if (native_006ea93a < 0x50) {
          (&native_006ea946)[native_006ea93a * 2] = 0x3c;
          (&native_006ea94a)[iVar7 * 2] = 0xc;
          native_006ea93a = (int)(native_006ea93a + 1);
        }
        else {
          CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
        }
        fn_00554930((int)(native_006eabfe), (undefined1)(1));
      }
      iVar7 = (int)(*(int *)(param_1 + 0x16));
      iVar8 = (int)(strchr((char *)(iVar7 + 10), (char)(0x24)));
      if (iVar8 == 0) {
        iVar9 = (int)(iVar7 + 10);
      }
      else {
        iVar8 = (int)(iVar8 - (iVar7 + 10));
        iVar9 = (int)(CompilerTools_AllocatePool((int)(iVar8 + 1)));
        strncpy((char *)(iVar9), (char *)(iVar7 + 10), (int)(iVar8));
        *(undefined1 *)(iVar9 + iVar8) = 0;
      }
      iVar7 = (int)(native_006ea93a);
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 3;
        (&native_006ea94a)[iVar7 * 2] = 8;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      fn_005548f0((int)(native_006eabfe), (char *)(iVar9));
    }
    else {
      iVar7 = (int)(*(int *)(param_1 + 0x16));
      if (iVar7 != 0) {
        iVar8 = (int)(strchr((char *)(iVar7 + 10), (char)(0x24)));
        if (iVar8 == 0) {
          iVar9 = (int)(iVar7 + 10);
        }
        else {
          iVar8 = (int)(iVar8 - (iVar7 + 10));
          iVar9 = (int)(CompilerTools_AllocatePool((int)(iVar8 + 1)));
          strncpy((char *)(iVar9), (char *)(iVar7 + 10), (int)(iVar8));
          *(undefined1 *)(iVar9 + iVar8) = 0;
        }
        iVar7 = (int)(native_006ea93a);
        if (native_006ea93a < 0x50) {
          (&native_006ea946)[native_006ea93a * 2] = 3;
          (&native_006ea94a)[iVar7 * 2] = 8;
          native_006ea93a = (int)(native_006ea93a + 1);
        }
        else {
          CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
        }
        fn_005548f0((int)(native_006eabfe), (char *)(iVar9));
      }
      iVar7 = (int)(native_006ea93a);
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0x49;
        (&native_006ea94a)[iVar7 * 2] = 0x10;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
      *(undefined4 *)(param_1 + 0x22) = uVar10;
    }
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0xb:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0xb);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x11;
      (&native_006ea94a)[iVar8 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x1a) = uVar10;
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x12;
      (&native_006ea94a)[iVar7 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x1e) = uVar10;
    iVar7 = (int)(native_006ea93a);
    if (*(int *)(param_1 + 0x2e) != 0) {
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 1;
        (&native_006ea94a)[iVar7 * 2] = 0x10;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
      *(undefined4 *)(param_1 + 0x22) = uVar10;
    }
    if (*(char *)(param_1 + 0x32) == '\0') {
      uVar11 = (uint)(fn_005d5b00((char)(0)));
      if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
      }
      iVar7 = (int)(native_006eabfe);
      bVar15 = (bool)(iVar13 == -1);
      do {
        bVar6 = (byte)((byte)uVar11 & 0x7f);
        uVar11 = (uint)(uVar11 >> 7);
        if (uVar11 != 0) {
          bVar6 = (byte)(bVar6 | 0x80);
        }
        if (bVar15) {
          fn_00554930((int)(iVar7), (undefined1)(bVar6));
        }
        else {
          fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
          iVar13 = (int)(iVar13 + 1);
        }
      } while (uVar11 != 0);
    }
    else {
      uVar11 = (uint)(fn_005d5b00((char)(1)));
      if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
      }
      iVar7 = (int)(native_006eabfe);
      bVar15 = (bool)(iVar13 == -1);
      do {
        bVar6 = (byte)((byte)uVar11 & 0x7f);
        uVar11 = (uint)(uVar11 >> 7);
        if (uVar11 != 0) {
          bVar6 = (byte)(bVar6 | 0x80);
        }
        if (bVar15) {
          fn_00554930((int)(iVar7), (undefined1)(bVar6));
        }
        else {
          fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
          iVar13 = (int)(iVar13 + 1);
        }
      } while (uVar11 != 0);
    }
    break;
  case 0xd:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0xd);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x38;
      (&native_006ea94a)[iVar8 * 2] = 3;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    iVar7 = (int)(fn_00554960((int)(native_006eabfe), (undefined2)(0)));
    fn_00554930((int)(native_006eabfe), (undefined1)(0xc));
    fn_005549c0((int)(native_006eabfe), (uint)(*(undefined4 *)(param_1 + 0x28)));
    fn_00554850((int)(native_006eabfe), (int)(iVar7), (ushort)((*(int *)(native_006eabfe + 0x2c) - iVar7) - 2U & 0xffff));
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x49;
      (&native_006ea94a)[iVar7 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x22) = uVar10;
    iVar7 = (int)(*(int *)(param_1 + 0x16));
    iVar8 = (int)(strchr((char *)(iVar7 + 10), (char)(0x24)));
    if (iVar8 == 0) {
      iVar9 = (int)(iVar7 + 10);
    }
    else {
      iVar8 = (int)(iVar8 - (iVar7 + 10));
      iVar9 = (int)(CompilerTools_AllocatePool((int)(iVar8 + 1)));
      strncpy((char *)(iVar9), (char *)(iVar7 + 10), (int)(iVar8));
      *(undefined1 *)(iVar9 + iVar8) = 0;
    }
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 3;
      (&native_006ea94a)[iVar7 * 2] = 8;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005548f0((int)(native_006eabfe), (char *)(iVar9));
    iVar7 = (int)(native_006ea93a);
    if (**(char **)(*(int *)(param_1 + 0x1a) + 4) == '\b') {
      uVar2 = (undefined2)(*(undefined2 *)(param_1 + 0x2c));
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0xb;
        (&native_006ea94a)[iVar7 * 2] = 6;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      fn_005549c0((int)(native_006eabfe), (uint)(uVar2));
      iVar7 = (int)(native_006ea93a);
      uVar11 = (uint)((uint)*(ushort *)(param_1 + 0x2e));
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0xd;
        (&native_006ea94a)[iVar7 * 2] = 0xf;
        native_006ea93a = (int)(native_006ea93a + 1);
        iVar7 = (int)(native_006eabfe);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
        iVar7 = (int)(native_006eabfe);
      }
      do {
        bVar6 = (byte)((byte)uVar11 & 0x7f);
        uVar11 = (uint)(uVar11 >> 7);
        if (uVar11 != 0) {
          bVar6 = (byte)(bVar6 | 0x80);
        }
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
        iVar8 = (int)(native_006ea93a);
      } while (uVar11 != 0);
      uVar11 = (uint)((uint)*(ushort *)(param_1 + 0x30));
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0xc;
        (&native_006ea94a)[iVar8 * 2] = 0xf;
        native_006ea93a = (int)(native_006ea93a + 1);
        iVar7 = (int)(native_006eabfe);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
        iVar7 = (int)(native_006eabfe);
      }
      do {
        bVar6 = (byte)((byte)uVar11 & 0x7f);
        uVar11 = (uint)(uVar11 >> 7);
        if (uVar11 != 0) {
          bVar6 = (byte)(bVar6 | 0x80);
        }
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      } while (uVar11 != 0);
    }
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0xf:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0xf);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x49;
      (&native_006ea94a)[iVar8 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x1a) = uVar10;
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x11:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x11);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (native_0070f1a8 == '\0') {
      uVar12 = (undefined1)(2);
    }
    else {
      uVar12 = (undefined1)(4);
    }
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x13;
      (&native_006ea94a)[iVar8 * 2] = 0xf;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_00554930((int)(native_006eabfe), (undefined1)(uVar12));
    iVar7 = (int)(native_006ea93a);
    if ((native_00711be4 != 0) && (native_006eac2a == '\0')) {
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0x11;
        (&native_006ea94a)[iVar7 * 2] = 1;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
      *(undefined4 *)(param_1 + 0x1a) = uVar10;
      iVar7 = (int)(native_006ea93a);
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0x12;
        (&native_006ea94a)[iVar7 * 2] = 1;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
      *(undefined4 *)(param_1 + 0x1e) = uVar10;
    }
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x10;
      (&native_006ea94a)[iVar7 * 2] = 6;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x16) = uVar10;
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x43;
      (&native_006ea94a)[iVar7 * 2] = 6;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x22) = uVar10;
    iVar7 = (int)(native_006ea93a);
    if ((*(int *)(param_1 + 0x36) == 0) || (native_0070f28d != '\0')) {
      iVar8 = (int)(*(int *)(param_1 + 0x32));
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 3;
        (&native_006ea94a)[iVar7 * 2] = 8;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      fn_005548f0((int)(native_006eabfe), (char *)(iVar8 + 10));
    }
    else {
      pcVar14 = (char*)((char *)(*(int *)(param_1 + 0x32) + 10));
      strcpy((char *)(&native_006e9870), (char *)(pcVar14));
      iVar7 = (int)(native_006ea93a);
      iVar8 = (int)(-1);
      do {
        if (iVar8 == 0) break;
        iVar8 = (int)(iVar8 - 1);
        cVar1 = (char)(*pcVar14);
        pcVar14 = (char*)(pcVar14 + 1);
      } while (cVar1 != '\0');
      for (iVar8 = (int)(-iVar8 - 2); iVar8 > 0 && ((&native_006e9870)[iVar8] != '\\'); iVar8 = iVar8 - 1) {
      }
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 3;
        (&native_006ea94a)[iVar7 * 2] = 8;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      fn_005548f0((int)(native_006eabfe), (char *)(&native_006e9871 + iVar8));
    }
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x25;
      (&native_006ea94a)[iVar7 * 2] = 8;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005548f0((int)(native_006eabfe), (char *)(literal_006b4b0f));
    iVar8 = (int)(native_006ea93a);
    iVar7 = (int)(*(int *)(param_1 + 0x36));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x1b;
      (&native_006ea94a)[iVar8 * 2] = 8;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005548f0((int)(native_006eabfe), (char *)(iVar7 + 10));
    uVar11 = (uint)(fn_005d5b00((char)(1)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x15:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x15);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x49;
      (&native_006ea94a)[iVar8 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x1a) = uVar10;
    if (*(int *)(param_1 + 0x22) == 0) {
      uVar11 = (uint)(fn_005d5b00((char)(0)));
      if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
      }
      iVar7 = (int)(native_006eabfe);
      bVar15 = (bool)(iVar13 == -1);
      do {
        bVar6 = (byte)((byte)uVar11 & 0x7f);
        uVar11 = (uint)(uVar11 >> 7);
        if (uVar11 != 0) {
          bVar6 = (byte)(bVar6 | 0x80);
        }
        if (bVar15) {
          fn_00554930((int)(iVar7), (undefined1)(bVar6));
        }
        else {
          fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
          iVar13 = (int)(iVar13 + 1);
        }
      } while (uVar11 != 0);
    }
    else {
      uVar11 = (uint)(fn_005d5b00((char)(1)));
      if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
      }
      iVar7 = (int)(native_006eabfe);
      bVar15 = (bool)(iVar13 == -1);
      do {
        bVar6 = (byte)((byte)uVar11 & 0x7f);
        uVar11 = (uint)(uVar11 >> 7);
        if (uVar11 != 0) {
          bVar6 = (byte)(bVar6 | 0x80);
        }
        if (bVar15) {
          fn_00554930((int)(iVar7), (undefined1)(bVar6));
        }
        else {
          fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
          iVar13 = (int)(iVar13 + 1);
        }
      } while (uVar11 != 0);
    }
    break;
  case 0x16:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x16);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x49;
      (&native_006ea94a)[iVar8 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x1a) = uVar10;
    iVar7 = (int)(*(int *)(param_1 + 0x16));
    iVar8 = (int)(strchr((char *)(iVar7 + 10), (char)(0x24)));
    if (iVar8 == 0) {
      iVar9 = (int)(iVar7 + 10);
    }
    else {
      iVar8 = (int)(iVar8 - (iVar7 + 10));
      iVar9 = (int)(CompilerTools_AllocatePool((int)(iVar8 + 1)));
      strncpy((char *)(iVar9), (char *)(iVar7 + 10), (int)(iVar8));
      *(undefined1 *)(iVar9 + iVar8) = 0;
    }
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 3;
      (&native_006ea94a)[iVar7 * 2] = 8;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005548f0((int)(native_006eabfe), (char *)(iVar9));
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x18:
    uVar3 = (ushort)(*(ushort *)(param_1 + 0x14));
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)((uint)uVar3);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
    } while (uVar11 != 0);
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x1c:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x1c);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    uVar2 = (undefined2)(*(undefined2 *)(param_1 + 0x22));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x32;
      (&native_006ea94a)[iVar8 * 2] = 0xb;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_00554930((int)(native_006eabfe), (undefined1)((char)uVar2));
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x38;
      (&native_006ea94a)[iVar7 * 2] = 3;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    iVar7 = (int)(fn_00554960((int)(native_006eabfe), (undefined2)(0)));
    fn_00554930((int)(native_006eabfe), (undefined1)(0xc));
    fn_005549c0((int)(native_006eabfe), (uint)(*(undefined4 *)(param_1 + 0x1e)));
    fn_00554850((int)(native_006eabfe), (int)(iVar7), (ushort)((*(int *)(native_006eabfe + 0x2c) - iVar7) - 2U & 0xffff));
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x49;
      (&native_006ea94a)[iVar7 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x1a) = uVar10;
    iVar7 = (int)(native_006ea93a);
    uVar2 = (undefined2)(*(undefined2 *)(param_1 + 0x24));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x4c;
      (&native_006ea94a)[iVar7 * 2] = 0xb;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_00554930((int)(native_006eabfe), (undefined1)((char)uVar2));
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x1f:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x1f);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x49;
      (&native_006ea94a)[iVar8 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x22) = uVar10;
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x1d;
      (&native_006ea94a)[iVar7 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x26) = uVar10;
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x21:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x21);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    uVar11 = (uint)(*(uint *)(param_1 + 0x16));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x2f;
      (&native_006ea94a)[iVar8 * 2] = 5;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_00554960((int)(native_006eabfe), (undefined2)(uVar11 & 0xffff));
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x24:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x24);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    uVar10 = (undefined4)(*(undefined4 *)(param_1 + 0x1e));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0xb;
      (&native_006ea94a)[iVar8 * 2] = 6;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005549c0((int)(native_006eabfe), (uint)(uVar10));
    iVar7 = (int)(native_006ea93a);
    uVar11 = (uint)(*(uint *)(param_1 + 0x1a));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x3e;
      (&native_006ea94a)[iVar7 * 2] = 0xb;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_00554930((int)(native_006eabfe), (undefined1)(uVar11 & 0xff));
    iVar8 = (int)(native_006ea93a);
    iVar7 = (int)(*(int *)(param_1 + 0x16));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 3;
      (&native_006ea94a)[iVar8 * 2] = 8;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005548f0((int)(native_006eabfe), (char *)(iVar7 + 10));
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x28:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x28);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    iVar7 = (int)(*(int *)(param_1 + 0x16));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 3;
      (&native_006ea94a)[iVar8 * 2] = 8;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005548f0((int)(native_006eabfe), (char *)(iVar7 + 10));
    iVar7 = (int)(native_006ea93a);
    uVar10 = (undefined4)(*(undefined4 *)(param_1 + 0x1a));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x1c;
      (&native_006ea94a)[iVar7 * 2] = 6;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005549c0((int)(native_006eabfe), (uint)(uVar10));
    uVar11 = (uint)(fn_005d5b00((char)(0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
    break;
  case 0x2e:
    if (native_006ea934 != 0) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x863));
    }
    iVar7 = (int)(native_006eabfe);
    native_006ea934 = (int)(0x2e);
    native_006ea938 = (char)(0);
    native_006ea930 = (int)(0xffffffff);
    native_006ea93a = (int)(0);
    iVar13 = (int)(*(int *)(native_006eabfe + 0x2c));
    uVar11 = (uint)(0x80);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      fn_00554930((int)(iVar7), (undefined1)(bVar6));
      iVar8 = (int)(native_006ea93a);
    } while (uVar11 != 0);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x11;
      (&native_006ea94a)[iVar8 * 2] = 1;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x46) = uVar10;
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x12;
      (&native_006ea94a)[iVar7 * 2] = 1;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x4a) = uVar10;
    iVar7 = (int)(native_006ea93a);
    uVar11 = (uint)(*(uint *)(param_1 + 0x4e));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x3b;
      (&native_006ea94a)[iVar7 * 2] = 5;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_00554960((int)(native_006eabfe), (undefined2)(uVar11 & 0xffff));
    iVar7 = (int)(native_006ea93a);
    for (piVar5 = (int*)(native_00715bfc); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
      if (*piVar5 == *(int *)(param_1 + 0x42)) {
        uVar11 = (uint)(piVar5[4]);
        goto label_005d43ed;
      }
    }
    uVar11 = (uint)(0);
label_005d43ed:
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x3a;
      (&native_006ea94a)[iVar7 * 2] = 5;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_00554960((int)(native_006eabfe), (undefined2)(uVar11 & 0xffff));
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x49;
      (&native_006ea94a)[iVar7 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x22) = uVar10;
    iVar7 = (int)(native_006ea93a);
    cVar1 = (char)(*(char *)(param_1 + 0x6e));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 0x3f;
      (&native_006ea94a)[iVar7 * 2] = 0xc;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_00554930((int)(native_006eabfe), (undefined1)(cVar1 != '\0'));
    iVar7 = (int)(native_006ea93a);
    if (*(char *)(param_1 + 0x78) == '\0') {
      if (native_006ea93a < 0x50) {
        (&native_006ea946)[native_006ea93a * 2] = 0x40;
        (&native_006ea94a)[iVar7 * 2] = 6;
        native_006ea93a = (int)(native_006ea93a + 1);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
      }
      uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
      *(undefined4 *)(param_1 + 0x5a) = uVar10;
      uVar10 = (undefined4)(fn_005d6c80());
      *(undefined4 *)(param_1 + 0x5e) = uVar10;
    }
    else {
      fn_005d6b40();
    }
    iVar8 = (int)(native_006ea93a);
    iVar7 = (int)(*(int *)(param_1 + 0x16));
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 3;
      (&native_006ea94a)[iVar8 * 2] = 8;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    fn_005548f0((int)(native_006eabfe), (char *)(iVar7 + 10));
    uVar11 = (uint)(0);
    iVar7 = (int)(native_006ea93a);
    for (puVar4 = (undefined4*)(*(undefined4 **)(param_1 + 0x70)); native_006ea93a = iVar7,
        puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
      if (*(int *)(*(int *)(puVar4[1] + 4) + 0x38) == 0) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0xbfa));
      }
      else {
        uVar11 = (uint)(uVar11 + 4);
      }
      iVar7 = (int)(native_006ea93a);
    }
    if (uVar11 != 0) {
      if (iVar7 < 0x50) {
        (&native_006ea946)[iVar7 * 2] = 0x2020;
        (&native_006ea94a)[iVar7 * 2] = 9;
        native_006ea93a = (int)(native_006ea93a + 1);
        iVar7 = (int)(native_006eabfe);
      }
      else {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
        iVar7 = (int)(native_006eabfe);
      }
      do {
        bVar6 = (byte)((byte)uVar11 & 0x7f);
        uVar11 = (uint)(uVar11 >> 7);
        if (uVar11 != 0) {
          bVar6 = (byte)(bVar6 | 0x80);
        }
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      } while (uVar11 != 0);
      *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(native_006eabfe + 0x2c);
      for (puVar4 = (undefined4*)(*(undefined4 **)(param_1 + 0x70)); puVar4 != (undefined4 *)0x0;
          puVar4 = (undefined4 *)*puVar4) {
        if (*(int *)(*(int *)(puVar4[1] + 4) + 0x38) != 0) {
          fn_005549c0((int)(native_006eabfe), (uint)(0));
        }
      }
    }
    iVar7 = (int)(native_006ea93a);
    if (native_006ea93a < 0x50) {
      (&native_006ea946)[native_006ea93a * 2] = 1;
      (&native_006ea94a)[iVar7 * 2] = 0x10;
      native_006ea93a = (int)(native_006ea93a + 1);
    }
    else {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
    }
    uVar10 = (undefined4)(fn_005549c0((int)(native_006eabfe), (uint)(0)));
    *(undefined4 *)(param_1 + 0x56) = uVar10;
    uVar11 = (uint)(fn_005d5b00((char)(*(int *)(param_1 + 0x6a) != 0)));
    if (((int)uVar11 < 0x80) || ((int)uVar11 > 0x3fff)) {
      CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x9f2));
    }
    iVar7 = (int)(native_006eabfe);
    bVar15 = (bool)(iVar13 == -1);
    do {
      bVar6 = (byte)((byte)uVar11 & 0x7f);
      uVar11 = (uint)(uVar11 >> 7);
      if (uVar11 != 0) {
        bVar6 = (byte)(bVar6 | 0x80);
      }
      if (bVar15) {
        fn_00554930((int)(iVar7), (undefined1)(bVar6));
      }
      else {
        fn_00554830((int)(iVar7), (int)(iVar13), (undefined1)(bVar6));
        iVar13 = (int)(iVar13 + 1);
      }
    } while (uVar11 != 0);
  }
  *(int *)(param_1 + 0xc) = *(int *)(native_006eabfe + 0x2c) - *(int *)(param_1 + 8);
  return;
}

void fn_005d5930(void)

{
  uint *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  byte bVar4;
  uint uVar5;
  int local_18;
  int local_14;

  local_14 = (int)(0);
  do {
    puVar1 = (uint*)((uint *)(&native_006ea89c)[local_14]);
    uVar2 = (undefined4)(native_006eabd2);
    if (puVar1 != (uint *)0x0) {
      for (; native_006eabd2 = (int)(uVar2), puVar1 != (uint *)0x0; puVar1 = *(uint **)((int)puVar1 + 0x12)) {
        uVar5 = (uint)(*puVar1);
        do {
          bVar4 = (byte)((byte)uVar5 & 0x7f);
          uVar5 = (uint)(uVar5 >> 7);
          if (uVar5 != 0) {
            bVar4 = (byte)(bVar4 | 0x80);
          }
          fn_00554930((int)(uVar2), (undefined1)(bVar4));
          uVar3 = (undefined4)(native_006eabd2);
        } while (uVar5 != 0);
        uVar5 = (uint)(puVar1[1]);
        do {
          bVar4 = (byte)((byte)uVar5 & 0x7f);
          uVar5 = (uint)(uVar5 >> 7);
          if (uVar5 != 0) {
            bVar4 = (byte)(bVar4 | 0x80);
          }
          fn_00554930((int)(uVar3), (undefined1)(bVar4));
        } while (uVar5 != 0);
        fn_00554930((int)(native_006eabd2), (undefined1)((char)puVar1[2] != '\0'));
        local_18 = (int)(0);
        if ((*(int *)((int)puVar1 + 10) > 0) && (*(int *)((int)puVar1 + 10) > 0)) {
          do {
            uVar2 = (undefined4)(native_006eabd2);
            uVar5 = (uint)(*(uint *)(*(int *)((int)puVar1 + 0xe) + local_18 * 8));
            do {
              bVar4 = (byte)((byte)uVar5 & 0x7f);
              uVar5 = (uint)(uVar5 >> 7);
              if (uVar5 != 0) {
                bVar4 = (byte)(bVar4 | 0x80);
              }
              fn_00554930((int)(uVar2), (undefined1)(bVar4));
              uVar3 = (undefined4)(native_006eabd2);
            } while (uVar5 != 0);
            uVar5 = (uint)(*(uint *)(*(int *)((int)puVar1 + 0xe) + 4 + local_18 * 8));
            do {
              bVar4 = (byte)((byte)uVar5 & 0x7f);
              uVar5 = (uint)(uVar5 >> 7);
              if (uVar5 != 0) {
                bVar4 = (byte)(bVar4 | 0x80);
              }
              fn_00554930((int)(uVar3), (undefined1)(bVar4));
            } while (uVar5 != 0);
            local_18 = (int)(local_18 + 1);
          } while (local_18 < *(int *)((int)puVar1 + 10));
        }
        fn_00554930((int)(native_006eabd2), (undefined1)(0));
        fn_00554930((int)(native_006eabd2), (undefined1)(0));
        uVar2 = (undefined4)(native_006eabd2);
      }
    }
    local_14 = (int)(local_14 + 1);
  } while (local_14 < 0x25);
  fn_00554930((int)(native_006eabd2), (undefined1)(0));
  return;
}

int fn_005d5b00(char param_1)

{
  bool bVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int local_28;

  iVar4 = (int)(0);
  local_28 = (int)(native_006ea934 % 0x25);
  if (native_006ea93a > 0) {
    if (native_006ea93a > 8) {
      bVar1 = (bool)(false);
      if ((native_006ea93a > -1) && (native_006ea93a != 0x7fffffff)) {
        bVar1 = (bool)(true);
      }
      iVar5 = (int)(iVar4);
      if (bVar1) {
        do {
          iVar4 = (int)(iVar5 + 8);
          local_28 = ((&native_006ea982)[iVar5 * 2] * 0xb +
                     (&native_006ea97e)[iVar5 * 2] * 7 +
                     (((&native_006ea97a)[iVar5 * 2] * 0xb +
                      (&native_006ea976)[iVar5 * 2] * 7 +
                      (((&native_006ea972)[iVar5 * 2] * 0xb +
                       (&native_006ea96e)[iVar5 * 2] * 7 +
                       (((&native_006ea96a)[iVar5 * 2] * 0xb +
                        (&native_006ea966)[iVar5 * 2] * 7 +
                        (((&native_006ea962)[iVar5 * 2] * 0xb +
                         (&native_006ea95e)[iVar5 * 2] * 7 +
                         (((&native_006ea95a)[iVar5 * 2] * 0xb +
                          (&native_006ea956)[iVar5 * 2] * 7 +
                          (((&native_006ea952)[iVar5 * 2] * 0xb +
                           (&native_006ea94e)[iVar5 * 2] * 7 +
                           (((&native_006ea94a)[iVar5 * 2] * 0xb +
                            (&native_006ea946)[iVar5 * 2] * 7 + local_28 * 3) % 0x25) * 3) % 0x25) * 3)
                         % 0x25) * 3) % 0x25) * 3) % 0x25) * 3) % 0x25) * 3) % 0x25) * 3) % 0x25;
          iVar5 = (int)(iVar4);
        } while (iVar4 < native_006ea93a - 8U);
      }
    }
    for (; iVar4 < native_006ea93a; iVar4 = iVar4 + 1) {
      local_28 = ((&native_006ea94a)[iVar4 * 2] * 0xb + (&native_006ea946)[iVar4 * 2] * 7 + local_28 * 3)
                 % 0x25;
    }
  }
  native_006ea938 = (char)(param_1);
  for (piVar2 = (int*)((int *)(&native_006ea89c)[local_28]); piVar2 != (int *)0x0;
      piVar2 = *(int **)((int)piVar2 + 0x12)) {
    if ((native_006ea934 == piVar2[1]) && (param_1 == (char)piVar2[2]) &&
       (native_006ea93a == *(int *)((int)piVar2 + 10))) {
      iVar4 = (int)(0);
      if (native_006ea93a > 0) {
        do {
          iVar5 = (int)(*(int *)(native_006ea93e + 4 + iVar4 * 8));
          if ((iVar5 != *(int *)(*(int *)((int)piVar2 + 0xe) + 4 + iVar4 * 8)) ||
             (iVar5 != *(int *)(*(int *)((int)piVar2 + 0xe) + 4 + iVar4 * 8))) {
            bVar1 = (bool)(false);
            goto label_005d5e5e;
          }
          iVar4 = (int)(iVar4 + 1);
        } while (iVar4 < native_006ea93a);
      }
      bVar1 = (bool)(true);
    }
    else {
      bVar1 = (bool)(false);
    }
label_005d5e5e:
    if (bVar1) break;
  }
  if (piVar2 == (int *)0x0) {
    piVar2 = (int*)((int *)galloc((int)(0x16)));
    uVar3 = (undefined4)(galloc((int)(native_006ea93a * 8)));
    *(undefined4 *)((int)piVar2 + 0xe) = uVar3;
    iVar4 = (int)(0);
    if (native_006ea93a > 0) {
      do {
        *(undefined4 *)(*(int *)((int)piVar2 + 0xe) + iVar4 * 8) = (&native_006ea946)[iVar4 * 2];
        iVar5 = (int)(iVar4 + 1);
        *(undefined4 *)(*(int *)((int)piVar2 + 0xe) + 4 + iVar4 * 8) = (&native_006ea94a)[iVar4 * 2];
        iVar4 = (int)(iVar5);
      } while (iVar5 < native_006ea93a);
    }
    piVar2[1] = (int)(native_006ea934);
    *(char *)(piVar2 + 2) = native_006ea938;
    *(int *)((int)piVar2 + 10) = native_006ea93a;
    *piVar2 = (int)(native_006eabc6);
    native_006eabc6 = (int)(native_006eabc6 + 1);
    *(undefined4 *)((int)piVar2 + 0x12) = (uint)(&native_006ea89c)[local_28];
    (&native_006ea89c)[local_28] = piVar2;
  }
  native_006ea934 = (int)(0);
  return *piVar2;
}

int fn_005d5f30(char *param_1, char param_2)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;

  strcpy((char *)(&native_006e9c70), (char *)(param_1));
  iVar4 = (int)(-1);
  do {
    if (iVar4 == 0) break;
    iVar4 = (int)(iVar4 - 1);
    cVar1 = (char)(*param_1);
    param_1 = (char*)(param_1 + 1);
  } while (cVar1 != '\0');
  for (iVar4 = (int)(-iVar4 - 2); iVar4 > 0 && ((&native_006e9c70)[iVar4] != '\\'); iVar4 = iVar4 - 1) {
  }
  if (iVar4 == 0) {
    return 0;
  }
  *(undefined1 *)(iVar4 + 0x6e9c71) = 0;
  iVar4 = (int)(fn_0046d340((char *)(&native_006e9c70)));
  piVar2 = (int*)(native_00710220);
  if (param_2 != '\0') {
    *(int *)(native_00710710 + 0x36) = iVar4;
    piVar2 = (int*)(native_00710220);
  }
  while( true ) {
    if (piVar2 == (int *)0x0) {
      piVar3 = (int*)((int *)galloc((int)(0xc)));
      memclrw((undefined1 *)(piVar3), (int)(0xc));
      *piVar3 = (int)(iVar4);
      native_007108dc = (int)(native_007108dc + 1);
      piVar3[2] = (int)(native_007108dc);
      piVar2 = (int*)(piVar3);
      if (native_00716ce8 != (int *)0x0) {
        *(int **)((int)native_00716ce8 + 4) = piVar3;
        piVar2 = (int*)(native_00710220);
      }
      native_00710220 = (int)(piVar2);
      native_00716ce8 = (int *)(piVar3);
      return piVar3[2];
    }
    if (*piVar2 == iVar4) break;
    piVar2 = (int*)((int *)piVar2[1]);
  }
  return piVar2[2];
}

int fn_005d6010(int param_1, int param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  undefined4 uVar5;
  int local_14;

  local_14 = (int)(*(int *)(native_006eabfe + 0x2c));
  if ((*(short *)(param_1 + 0x14) != 0x34) && (*(short *)(param_1 + 0x14) != 5)) {
    CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x793));
  }
  iVar2 = (int)(native_006ea93a);
  if (native_006ea93a < 0x50) {
    (&native_006ea946)[native_006ea93a * 2] = 2;
    (&native_006ea94a)[iVar2 * 2] = 3;
    native_006ea93a = (int)(native_006ea93a + 1);
  }
  else {
    CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
  }
  iVar2 = (int)(fn_00554960((int)(native_006eabfe), (undefined2)(0)));
  switch(*(undefined2 *)(param_1 + 0x26)) {
  case 0:
  case 5:
    uVar4 = (uint)((uint)*(ushort *)(param_1 + 0x34));
    if (uVar4 < 0x20) {
      fn_00554930((int)(native_006eabfe), (undefined1)(uVar4 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabfe), (undefined1)(0x90));
      iVar1 = (int)(native_006eabfe);
      do {
        bVar3 = (byte)((byte)uVar4 & 0x7f);
        uVar4 = (uint)(uVar4 >> 7);
        if (uVar4 != 0) {
          bVar3 = (byte)(bVar3 | 0x80);
        }
        fn_00554930((int)(iVar1), (undefined1)(bVar3));
      } while (uVar4 != 0);
    }
    break;
  case 1:
  case 6:
    uVar4 = (uint)((uint)*(ushort *)(param_1 + 0x36));
    if (uVar4 < 0x20) {
      fn_00554930((int)(native_006eabfe), (undefined1)(uVar4 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabfe), (undefined1)(0x90));
      iVar1 = (int)(native_006eabfe);
      do {
        bVar3 = (byte)((byte)uVar4 & 0x7f);
        uVar4 = (uint)(uVar4 >> 7);
        if (uVar4 != 0) {
          bVar3 = (byte)(bVar3 | 0x80);
        }
        fn_00554930((int)(iVar1), (undefined1)(bVar3));
      } while (uVar4 != 0);
    }
    fn_00554930((int)(native_006eabfe), (undefined1)(0x93));
    fn_00554930((int)(native_006eabfe), (undefined1)(4));
    uVar4 = (uint)((uint)*(ushort *)(param_1 + 0x34));
    if (uVar4 < 0x20) {
      fn_00554930((int)(native_006eabfe), (undefined1)(uVar4 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabfe), (undefined1)(0x90));
      iVar1 = (int)(native_006eabfe);
      do {
        bVar3 = (byte)((byte)uVar4 & 0x7f);
        uVar4 = (uint)(uVar4 >> 7);
        if (uVar4 != 0) {
          bVar3 = (byte)(bVar3 | 0x80);
        }
        fn_00554930((int)(iVar1), (undefined1)(bVar3));
      } while (uVar4 != 0);
    }
    fn_00554930((int)(native_006eabfe), (undefined1)(0x93));
    fn_00554930((int)(native_006eabfe), (undefined1)(4));
    break;
  case 3:
    uVar4 = (uint)((uint)*(ushort *)(param_1 + 0x34));
    uVar5 = (undefined4)(*(undefined4 *)(param_1 + 0x38));
    if (uVar4 == (int)native_007172bc) {
      fn_00554930((int)(native_006eabfe), (undefined1)(0x91));
    }
    else if (uVar4 < 0x20) {
      fn_00554930((int)(native_006eabfe), (undefined1)(uVar4 + 0x70 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabfe), (undefined1)(0x92));
      iVar1 = (int)(native_006eabfe);
      do {
        bVar3 = (byte)((byte)uVar4 & 0x7f);
        uVar4 = (uint)(uVar4 >> 7);
        if (uVar4 != 0) {
          bVar3 = (byte)(bVar3 | 0x80);
        }
        fn_00554930((int)(iVar1), (undefined1)(bVar3));
      } while (uVar4 != 0);
    }
    fn_005d6dd0((undefined4)(native_006eabfe), (int)(0xffffffff), (uint)(uVar5));
    if (*(int *)(param_1 + 0x3c) != 0) {
      fn_00554930((int)(native_006eabfe), (undefined1)(0xc));
      fn_005549c0((int)(native_006eabfe), (uint)(0));
      fn_00554a70((undefined4)(*(undefined1 *)(param_1 + 0x3c)), (int)(native_007108d0), (undefined4)(*(int *)(native_006eabfe + 0x2c) - 4), (undefined4)(*(undefined4 *)(param_1 + 0x40)), (undefined4)(0));
      fn_00554930((int)(native_006eabfe), (undefined1)(0x22));
    }
    break;
  case 4:
    fn_00554930((int)(native_006eabfe), (undefined1)(3));
    fn_005549c0((int)(native_006eabfe), (uint)(0));
    fn_00554a70((undefined4)(*(undefined1 *)(param_1 + 0x3c)), (int)(native_007108d0), (undefined4)(*(int *)(native_006eabfe + 0x2c) - 4), (undefined4)(*(undefined4 *)(param_1 + 0x40)), (undefined4)(0));
  }
  fn_00554850((int)(native_006eabfe), (int)(iVar2), (ushort)((*(int *)(native_006eabfe + 0x2c) - iVar2) - 2U & 0xffff));
  if ((param_2 != 0) && (*(char *)(param_2 + 0x78) == '\0')) {
    local_14 = (int)(local_14 - *(int *)(param_2 + 0x5e));
  }
  return local_14;
}

int fn_005d63f0(int param_1, int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  int in_stack_ffffffe4;
  int local_14;

  local_14 = (int)(*(int *)(native_006eabde + 0x2c));
  if ((*(short *)(param_1 + 0x14) != 0x34) && (*(short *)(param_1 + 0x14) != 5)) {
    CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x6e3));
  }
  switch(*(undefined2 *)(param_1 + 0x26)) {
  case 0:
    iVar2 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x36));
    iVar3 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x32));
    fn_005549c0((int)(native_006eabde), (uint)(iVar2));
    fn_005549c0((int)(native_006eabde), (uint)(iVar3 + iVar2));
    in_stack_ffffffe4 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
    uVar5 = (uint)((uint)*(ushort *)(param_1 + 0x34));
    if (uVar5 < 0x20) {
      fn_00554930((int)(native_006eabde), (undefined1)(uVar5 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabde), (undefined1)(0x90));
      iVar2 = (int)(native_006eabde);
      do {
        bVar4 = (byte)((byte)uVar5 & 0x7f);
        uVar5 = (uint)(uVar5 >> 7);
        if (uVar5 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar2), (undefined1)(bVar4));
      } while (uVar5 != 0);
    }
    break;
  case 1:
    iVar2 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x36));
    iVar3 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x32));
    fn_005549c0((int)(native_006eabde), (uint)(iVar2));
    fn_005549c0((int)(native_006eabde), (uint)(iVar3 + iVar2));
    in_stack_ffffffe4 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
    uVar5 = (uint)((uint)*(ushort *)(param_1 + 0x36));
    if (uVar5 < 0x20) {
      fn_00554930((int)(native_006eabde), (undefined1)(uVar5 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabde), (undefined1)(0x90));
      iVar2 = (int)(native_006eabde);
      do {
        bVar4 = (byte)((byte)uVar5 & 0x7f);
        uVar5 = (uint)(uVar5 >> 7);
        if (uVar5 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar2), (undefined1)(bVar4));
      } while (uVar5 != 0);
    }
    fn_00554930((int)(native_006eabde), (undefined1)(0x93));
    fn_00554930((int)(native_006eabde), (undefined1)(4));
    uVar5 = (uint)((uint)*(ushort *)(param_1 + 0x34));
    if (uVar5 < 0x20) {
      fn_00554930((int)(native_006eabde), (undefined1)(uVar5 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabde), (undefined1)(0x90));
      iVar2 = (int)(native_006eabde);
      do {
        bVar4 = (byte)((byte)uVar5 & 0x7f);
        uVar5 = (uint)(uVar5 >> 7);
        if (uVar5 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar2), (undefined1)(bVar4));
      } while (uVar5 != 0);
    }
    fn_00554930((int)(native_006eabde), (undefined1)(0x93));
    fn_00554930((int)(native_006eabde), (undefined1)(4));
    break;
  case 3:
    uVar1 = (undefined4)(*(undefined4 *)(param_1 + 0x38));
    uVar5 = (uint)((uint)*(ushort *)(param_1 + 0x34));
    if (uVar5 == (int)native_007172bc) {
      iVar2 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x36));
      iVar3 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x32));
      fn_005549c0((int)(native_006eabde), (uint)(iVar2));
      fn_005549c0((int)(native_006eabde), (uint)(iVar3 + iVar2));
      in_stack_ffffffe4 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
      fn_00554930((int)(native_006eabde), (undefined1)(0x91));
    }
    else if (uVar5 < 0x20) {
      iVar2 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x36));
      iVar3 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x32));
      fn_005549c0((int)(native_006eabde), (uint)(iVar2));
      fn_005549c0((int)(native_006eabde), (uint)(iVar3 + iVar2));
      in_stack_ffffffe4 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
      fn_00554930((int)(native_006eabde), (undefined1)(uVar5 + 0x70 & 0xff));
    }
    else {
      iVar2 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x36));
      iVar3 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x32));
      fn_005549c0((int)(native_006eabde), (uint)(iVar2));
      fn_005549c0((int)(native_006eabde), (uint)(iVar3 + iVar2));
      in_stack_ffffffe4 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
      fn_00554930((int)(native_006eabde), (undefined1)(0x92));
      iVar2 = (int)(native_006eabde);
      do {
        bVar4 = (byte)((byte)uVar5 & 0x7f);
        uVar5 = (uint)(uVar5 >> 7);
        if (uVar5 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar2), (undefined1)(bVar4));
      } while (uVar5 != 0);
    }
    fn_005d6dd0((undefined4)(native_006eabde), (int)(0xffffffff), (uint)(uVar1));
    if (*(int *)(param_1 + 0x3c) != 0) {
      fn_00554930((int)(native_006eabde), (undefined1)(0xc));
      fn_005549c0((int)(native_006eabde), (uint)(0));
      fn_00554a70((undefined4)(*(undefined1 *)(param_1 + 0x3c)), (int)(native_00710110), (undefined4)(*(int *)(native_006eabde + 0x2c) - 4), (undefined4)(*(undefined4 *)(param_1 + 0x40)), (undefined4)(0));
      fn_00554930((int)(native_006eabde), (undefined1)(0x22));
    }
    break;
  case 4:
    fn_005549c0((int)(native_006eabde), (uint)(0));
    fn_005549c0((int)(native_006eabde), (uint)(0xffffffff));
    in_stack_ffffffe4 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
    fn_00554930((int)(native_006eabde), (undefined1)(3));
    fn_005549c0((int)(native_006eabde), (uint)(0));
    fn_00554a70((undefined4)(*(undefined1 *)(param_1 + 0x3c)), (int)(native_00710110), (undefined4)(*(int *)(native_006eabde + 0x2c) - 4), (undefined4)(*(undefined4 *)(param_1 + 0x40)), (undefined4)(0));
    break;
  case 5:
    fn_005549c0((int)(native_006eabde), (uint)(0));
    fn_005549c0((int)(native_006eabde), (uint)(0xffffffff));
    in_stack_ffffffe4 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
    uVar5 = (uint)((uint)*(ushort *)(param_1 + 0x34));
    if (uVar5 < 0x20) {
      fn_00554930((int)(native_006eabde), (undefined1)(uVar5 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabde), (undefined1)(0x90));
      iVar2 = (int)(native_006eabde);
      do {
        bVar4 = (byte)((byte)uVar5 & 0x7f);
        uVar5 = (uint)(uVar5 >> 7);
        if (uVar5 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar2), (undefined1)(bVar4));
      } while (uVar5 != 0);
    }
    break;
  case 6:
    fn_005549c0((int)(native_006eabde), (uint)(0));
    fn_005549c0((int)(native_006eabde), (uint)(0xffffffff));
    in_stack_ffffffe4 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
    uVar5 = (uint)((uint)*(ushort *)(param_1 + 0x36));
    if (uVar5 < 0x20) {
      fn_00554930((int)(native_006eabde), (undefined1)(uVar5 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabde), (undefined1)(0x90));
      iVar2 = (int)(native_006eabde);
      do {
        bVar4 = (byte)((byte)uVar5 & 0x7f);
        uVar5 = (uint)(uVar5 >> 7);
        if (uVar5 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar2), (undefined1)(bVar4));
      } while (uVar5 != 0);
    }
    fn_00554930((int)(native_006eabde), (undefined1)(0x93));
    fn_00554930((int)(native_006eabde), (undefined1)(4));
    uVar5 = (uint)((uint)*(ushort *)(param_1 + 0x34));
    if (uVar5 < 0x20) {
      fn_00554930((int)(native_006eabde), (undefined1)(uVar5 + 0x50 & 0xff));
    }
    else {
      fn_00554930((int)(native_006eabde), (undefined1)(0x90));
      iVar2 = (int)(native_006eabde);
      do {
        bVar4 = (byte)((byte)uVar5 & 0x7f);
        uVar5 = (uint)(uVar5 >> 7);
        if (uVar5 != 0) {
          bVar4 = (byte)(bVar4 | 0x80);
        }
        fn_00554930((int)(iVar2), (undefined1)(bVar4));
      } while (uVar5 != 0);
    }
    fn_00554930((int)(native_006eabde), (undefined1)(0x93));
    fn_00554930((int)(native_006eabde), (undefined1)(4));
  }
  fn_00554850((int)(native_006eabde), (int)(in_stack_ffffffe4), (ushort)((*(int *)(native_006eabde + 0x2c) - in_stack_ffffffe4) - 2U & 0xffff));
  fn_005549c0((int)(native_006eabde), (uint)(0));
  fn_005549c0((int)(native_006eabde), (uint)(0));
  if ((param_2 != 0) && (*(char *)(param_2 + 0x78) == '\0')) {
    local_14 = (int)(local_14 - *(int *)(param_2 + 0x5e));
  }
  return local_14;
}

undefined4 fn_005d6b40(void)

{
  unsigned char nativeStack[12];
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;

  uVar1 = (undefined4)(*(undefined4 *)(native_006eabfe + 0x2c));
  fn_005cceb0((int *)(((uint  *)(nativeStack+0x0))), (undefined4 *)(&(*(uint  *)(nativeStack+0x8))));
  iVar3 = (int)(native_006ea93a);
  if (native_006ea93a < 0x50) {
    (&native_006ea946)[native_006ea93a * 2] = 0x40;
    (&native_006ea94a)[iVar3 * 2] = 3;
    native_006ea93a = (int)(native_006ea93a + 1);
  }
  else {
    CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x872));
  }
  iVar3 = (int)(fn_00554960((int)(native_006eabfe), (undefined2)(0)));
  if ((int)((uint  *)(nativeStack+0x0))[0] < 0x20) {
    if ((*(uint  *)(nativeStack+0x8)) != 0) {
      ((uint  *)(nativeStack+0x0))[0] = ((uint  *)(nativeStack+0x0))[0] + 0x70 & 0xff;
      goto label_005d6bf9;
    }
    ((uint  *)(nativeStack+0x0))[0] = ((uint  *)(nativeStack+0x0))[0] + 0x50;
  }
  else {
    if ((*(uint  *)(nativeStack+0x8)) == 0) {
      fn_00554930((int)(native_006eabfe), (undefined1)(0x90));
      ((uint  *)(nativeStack+0x0))[0] = ((uint  *)(nativeStack+0x0))[0] & 0xff;
      goto label_005d6bf9;
    }
    fn_00554930((int)(native_006eabfe), (undefined1)(0x92));
  }
  ((uint  *)(nativeStack+0x0))[0] = ((uint  *)(nativeStack+0x0))[0] & 0xff;
label_005d6bf9:
  fn_00554930((int)(native_006eabfe), (undefined1)(((uint  *)(nativeStack+0x0))[0]));
  iVar2 = (int)(native_006eabfe);
  while ((*(uint  *)(nativeStack+0x8)) != 0) {
    bVar4 = (byte)((byte)(*(uint  *)(nativeStack+0x8)) & 0x7f);
    (*(uint  *)(nativeStack+0x8)) = (uint)((*(uint  *)(nativeStack+0x8)) >> 7);
    if ((*(uint  *)(nativeStack+0x8)) != 0) {
      bVar4 = (byte)(bVar4 | 0x80);
    }
    fn_00554930((int)(iVar2), (undefined1)(bVar4));
  }
  fn_00554850((int)(native_006eabfe), (int)(iVar3), (ushort)((*(int *)(native_006eabfe + 0x2c) - iVar3) - 2U & 0xffff));
  return uVar1;
}

undefined4 fn_005d6c80(void)

{
  unsigned char nativeStack[12];
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;

  uVar1 = (undefined4)(*(undefined4 *)(native_006eabde + 0x2c));
  fn_005cceb0((int *)(((uint  *)(nativeStack+0x0))), (undefined4 *)(&(*(uint  *)(nativeStack+0x8))));
  iVar3 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x36));
  iVar2 = (int)(*(int *)(*(int *)(native_006eac12 + 4) + 0x32));
  fn_005549c0((int)(native_006eabde), (uint)(iVar3));
  fn_005549c0((int)(native_006eabde), (uint)(iVar2 + iVar3));
  iVar3 = (int)(fn_00554960((int)(native_006eabde), (undefined2)(0)));
  if ((int)((uint  *)(nativeStack+0x0))[0] < 0x20) {
    if ((*(uint  *)(nativeStack+0x8)) == 0) {
      ((uint  *)(nativeStack+0x0))[0] = ((uint  *)(nativeStack+0x0))[0] + 0x50 & 0xff;
    }
    else {
      ((uint  *)(nativeStack+0x0))[0] = ((uint  *)(nativeStack+0x0))[0] + 0x70 & 0xff;
    }
  }
  else if ((*(uint  *)(nativeStack+0x8)) == 0) {
    fn_00554930((int)(native_006eabde), (undefined1)(0x90));
    ((uint  *)(nativeStack+0x0))[0] = ((uint  *)(nativeStack+0x0))[0] & 0xff;
  }
  else {
    fn_00554930((int)(native_006eabde), (undefined1)(0x92));
    ((uint  *)(nativeStack+0x0))[0] = ((uint  *)(nativeStack+0x0))[0] & 0xff;
  }
  fn_00554930((int)(native_006eabde), (undefined1)(((uint  *)(nativeStack+0x0))[0]));
  iVar2 = (int)(native_006eabde);
  while ((*(uint  *)(nativeStack+0x8)) != 0) {
    bVar4 = (byte)((byte)(*(uint  *)(nativeStack+0x8)) & 0x7f);
    (*(uint  *)(nativeStack+0x8)) = (uint)((*(uint  *)(nativeStack+0x8)) >> 7);
    if ((*(uint  *)(nativeStack+0x8)) != 0) {
      bVar4 = (byte)(bVar4 | 0x80);
    }
    fn_00554930((int)(iVar2), (undefined1)(bVar4));
  }
  fn_00554850((int)(native_006eabde), (int)(iVar3), (ushort)((*(int *)(native_006eabde + 0x2c) - iVar3) - 2U & 0xffff));
  fn_005549c0((int)(native_006eabde), (uint)(0));
  fn_005549c0((int)(native_006eabde), (uint)(0));
  return uVar1;
}

void fn_005d6dd0(undefined4 section, int offset, uint value)
{
    bool more;
    bool negative;
    bool patch;
    byte encoded;
    more = true;
    negative = (int)value < 0;
    patch = offset != -1;
    do {
        encoded = value & 0x7f;
        value = (int)value >> 7;
        if (negative)
            value |= 0xfe000000;
        if ((value == 0 && (encoded & 0x40) == 0) ||
            (value == 0xffffffff && (encoded & 0x40) == 0x40))
            more = false;
        else
            encoded |= 0x80;
        if (patch) {
            fn_00554830(section, offset++, encoded);
        } else {
            fn_00554930(section, encoded);
        }
    } while (more);
}

void fn_005d6e70(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;

  puVar1 = (undefined1*)(*(undefined1 **)(param_1 + 4));
label_005d6e80:
  if (*(char *)(param_1 + 0xc) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0xc) = 1;
  switch(*puVar1) {
  case 0:
  case 1:
  case 2:
    uVar4 = (undefined4)(fn_005d7640((char *)(puVar1)));
    break;
  default:
    goto switchD_005d6ea0_caseD_3;
  case 4:
    uVar4 = (undefined4)(fn_005d7de0((int)(puVar1)));
    break;
  case 5:
    uVar4 = (undefined4)(fn_005d7a10((char *)(puVar1)));
    break;
  case 6:
    uVar4 = (undefined4)(fn_005d7200((int)(puVar1)));
    break;
  case 7:
    uVar4 = (undefined4)(fn_005d6ff0((int)(puVar1)));
    break;
  case 0xb:
    iVar3 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar3), (int)(0x7a));
    *(undefined2 *)(iVar3 + 0x14) = 0x1f;
    iVar2 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar3;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar3;
      *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar3;
    }
    *(int *)(native_006eac12 + 8) = iVar3;
    uVar4 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(puVar1 + 6))));
    *(undefined4 *)(iVar3 + 0x1a) = uVar4;
    uVar4 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(puVar1 + 10))));
    *(undefined4 *)(iVar3 + 0x1e) = uVar4;
    *(int *)(param_1 + 8) = iVar3;
    return;
  case 0xc:
    goto switchD_005d6ea0_caseD_c;
  case 0xd:
    uVar4 = (undefined4)(fn_005d7f70((int)(puVar1)));
  }
  *(undefined4 *)(param_1 + 8) = uVar4;
switchD_005d6ea0_caseD_3:
  return;
switchD_005d6ea0_caseD_c:
  uVar4 = (undefined4)(*(undefined4 *)(puVar1 + 6));
  iVar3 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar3), (int)(0x7a));
  *(undefined2 *)(iVar3 + 0x14) = 0xf;
  iVar2 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar3;
  }
  *(int *)(native_006eac12 + 8) = iVar3;
  uVar4 = (undefined4)(fn_005d8180((undefined1 *)(uVar4)));
  *(undefined4 *)(iVar3 + 0x16) = uVar4;
  *(int *)(param_1 + 8) = iVar3;
  goto label_005d6e80;
}

int fn_005d6ff0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;

  iVar3 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar3), (int)(0x7a));
  *(undefined2 *)(iVar3 + 0x14) = 0x15;
  iVar2 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar3;
  }
  *(int *)(native_006eac12 + 8) = iVar3;
  uVar4 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(param_1 + 0xe))));
  *(undefined4 *)(iVar3 + 0x16) = uVar4;
  puVar1 = (undefined4*)(*(undefined4 **)(param_1 + 6));
  do {
    if (puVar1 == (undefined4 *)0x0) {
label_005d7145:
      if (*(int *)(param_1 + 6) != 0) {
        iVar5 = (int)(galloc((int)(0x7a)));
        memclrw((undefined1 *)(iVar5), (int)(0x7a));
        *(undefined2 *)(iVar5 + 0x14) = 0xffff;
        iVar2 = (int)(native_006eac12);
        if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
          *(int *)(native_006eac12 + 8) = iVar5;
          *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
        }
        else {
          **(int **)(native_006eac12 + 8) = iVar5;
          *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(native_006eac12 + 8);
          *(int *)(native_006eac12 + 8) = iVar5;
        }
        *(int *)(native_006eac12 + 8) = iVar5;
        *(int *)(iVar3 + 0x22) = iVar5;
      }
      return iVar3;
    }
    if ((puVar1 == (undefined4 *)&native_007037c0) || (puVar1 == (undefined4 *)&native_0070bb08)) {
      iVar5 = (int)(galloc((int)(0x7a)));
      memclrw((undefined1 *)(iVar5), (int)(0x7a));
      *(undefined2 *)(iVar5 + 0x14) = 0x18;
      iVar2 = (int)(native_006eac12);
      if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
        *(int *)(native_006eac12 + 8) = iVar5;
        *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
      }
      else {
        **(int **)(native_006eac12 + 8) = iVar5;
        *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(native_006eac12 + 8);
        *(int *)(native_006eac12 + 8) = iVar5;
      }
      *(int *)(native_006eac12 + 8) = iVar5;
      goto label_005d7145;
    }
    iVar5 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar5), (int)(0x7a));
    *(undefined2 *)(iVar5 + 0x14) = 5;
    iVar2 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar5;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar5;
      *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar5;
    }
    *(int *)(native_006eac12 + 8) = iVar5;
    *(undefined4 *)(iVar5 + 0x16) = puVar1[1];
    uVar4 = (undefined4)(fn_005d8180((undefined1 *)(puVar1[3])));
    *(undefined4 *)(iVar5 + 0x1e) = uVar4;
    *(undefined1 *)(iVar5 + 0x61) = 1;
    puVar1 = (undefined4*)((undefined4 *)*puVar1);
  } while( true );
}

int fn_005d7200(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;

  iVar3 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar3), (int)(0x7a));
  *(undefined2 *)(iVar3 + 0x14) = 2;
  iVar1 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar1 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar3;
  }
  iVar1 = (int)(native_006eac12);
  *(int *)(native_006eac12 + 8) = iVar3;
  iVar1 = (int)(*(int *)(iVar1 + 8));
  *(undefined4 *)(iVar1 + 0x16) = *(undefined4 *)(param_1 + 10);
  if (*(int *)(iVar1 + 0x16) == 0) {
    *(undefined1 *)(iVar1 + 0x22) = 1;
  }
  else {
    *(undefined1 *)(iVar1 + 0x22) = 0;
    uVar4 = (undefined4)(fn_005d82b0((undefined4 *)(*(undefined4 *)(param_1 + 6)), (int)(*(undefined4 *)(param_1 + 10))));
    *(undefined4 *)(iVar1 + 0x1e) = uVar4;
  }
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(param_1 + 2);
  fn_005d7400((int)(param_1), (char)(1), (int)(0));
  iVar5 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar5), (int)(0x7a));
  *(undefined2 *)(iVar5 + 0x14) = 0xffff;
  iVar3 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar5;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar3 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar5;
    iVar3 = (int)(native_006eac12);
    *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(iVar3 + 8) = iVar5;
  }
  *(int *)(native_006eac12 + 8) = iVar5;
  *(int *)(iVar1 + 0x28) = iVar5;
  native_00710380 = (int)(0);
  native_007107f4 = (int)(param_1);
  fn_004561d0((undefined4)(fn_005d80f0));
  for (puVar2 = (undefined4*)(native_006eac22); puVar2 != (undefined4 *)0x0;
      puVar2 = *(undefined4 **)((int)puVar2 + 6)) {
    if (*(char *)(puVar2 + 1) == '\0') {
      uVar4 = (undefined4)(*puVar2);
      iVar5 = (int)(galloc((int)(0x7a)));
      memclrw((undefined1 *)(iVar5), (int)(0x7a));
      *(undefined2 *)(iVar5 + 0x14) = 0x16;
      iVar3 = (int)(native_006eac12);
      if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
        *(int *)(native_006eac12 + 8) = iVar5;
        *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar3 + 8);
      }
      else {
        **(int **)(native_006eac12 + 8) = iVar5;
        iVar3 = (int)(native_006eac12);
        *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(native_006eac12 + 8);
        *(int *)(iVar3 + 8) = iVar5;
      }
      *(int *)(native_006eac12 + 8) = iVar5;
      *(undefined4 *)(iVar5 + 0x16) = uVar4;
      uVar4 = (undefined4)(fn_005d8180((undefined1 *)(param_1)));
      *(undefined4 *)(iVar5 + 0x1e) = uVar4;
      *(int *)(iVar1 + 0x2c) = iVar5;
      *(undefined1 *)(puVar2 + 1) = 1;
    }
  }
  return iVar1;
}

void fn_005d7400(int param_1, char param_2, int param_3)

{
  unsigned char nativeStack[16];
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 uVar4;
  char *pcVar5;
  char *pcVar6;

  if (param_2 != '\0') {
    fn_005d7870((int)(param_1));
  }
  pcVar5 = (char*)(*(char **)(param_1 + 0x16));
  if (pcVar5 != (char *)0x0) {
    (*(int  *)(nativeStack+0xc)) = (int)(param_3);
    do {
      if (*(int *)(pcVar5 + 8) != native_00715c64) {
        if (*pcVar5 == '\x04') {
          iVar2 = (int)(galloc((int)(0x7a)));
          memclrw((undefined1 *)(iVar2), (int)(0x7a));
          *(undefined2 *)(iVar2 + 0x14) = 0xd;
          iVar1 = (int)(native_006eac12);
          if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
            *(int *)(native_006eac12 + 8) = iVar2;
            *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar1 + 8);
          }
          else {
            **(int **)(native_006eac12 + 8) = iVar2;
            iVar1 = (int)(native_006eac12);
            *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(native_006eac12 + 8);
            *(int *)(iVar1 + 8) = iVar2;
          }
          *(int *)(native_006eac12 + 8) = iVar2;
          *(undefined4 *)(iVar2 + 0x16) = *(undefined4 *)(pcVar5 + 8);
          *(int *)(iVar2 + 0x28) = *(int *)(pcVar5 + 0x14) + (*(int  *)(nativeStack+0xc));
          *(undefined1 *)(iVar2 + 0x32) = 1;
          switch(pcVar5[1]) {
          case '\0':
            *(undefined2 *)(iVar2 + 0x26) = 1;
            break;
          case '\x01':
            *(undefined2 *)(iVar2 + 0x26) = 3;
            break;
          case '\x02':
            *(undefined2 *)(iVar2 + 0x26) = 2;
          }
          pcVar6 = (char*)(*(char **)(pcVar5 + 0xc));
          if (*pcVar6 == '\b') {
            if ((char)native_0070efe8 != '\0') {
              (*(undefined4  *)(nativeStack+0x0)) = (undefined4)(*(undefined4 *)pcVar6);
              (*(undefined4  *)(nativeStack+0x4)) = (undefined4)(*(undefined4 *)(pcVar6 + 4));
              (*(undefined4  *)(nativeStack+0x8)) = (undefined4)(*(undefined4 *)(pcVar6 + 8));
              CABI_ReverseBitField((int)(&(*(undefined4  *)(nativeStack+0x0))));
              pcVar6 = (char*)((char *)&(*(undefined4  *)(nativeStack+0x0)));
            }
            uVar3 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(pcVar5 + 0xc))));
            *(undefined4 *)(iVar2 + 0x1a) = uVar3;
            uVar3 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(pcVar6 + 6))));
            *(undefined4 *)(iVar2 + 0x1e) = uVar3;
            *(ushort *)(iVar2 + 0x30) = (ushort)(byte)pcVar6[10];
            *(ushort *)(iVar2 + 0x2e) = (ushort)(byte)pcVar6[0xb];
            *(undefined2 *)(iVar2 + 0x2c) = *(undefined2 *)(*(int *)(pcVar6 + 6) + 2);
          }
          else {
            uVar3 = (undefined4)(fn_005d8180((undefined1 *)(pcVar6)));
            *(undefined4 *)(iVar2 + 0x1a) = uVar3;
            *(undefined2 *)(iVar2 + 0x2c) = *(undefined2 *)(*(int *)(pcVar5 + 0xc) + 2);
          }
        }
        else {
          iVar2 = (int)(galloc((int)(0x7a)));
          memclrw((undefined1 *)(iVar2), (int)(0x7a));
          *(undefined2 *)(iVar2 + 0x14) = 0x2e;
          iVar1 = (int)(native_006eac12);
          if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
            *(int *)(native_006eac12 + 8) = iVar2;
            *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar1 + 8);
          }
          else {
            **(int **)(native_006eac12 + 8) = iVar2;
            iVar1 = (int)(native_006eac12);
            *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(native_006eac12 + 8);
            *(int *)(iVar1 + 8) = iVar2;
          }
          *(int *)(native_006eac12 + 8) = iVar2;
          *(undefined4 *)(iVar2 + 0x16) = *(undefined4 *)(pcVar5 + 8);
          if ((*(uint *)(param_1 + 0x22) & 8) == 0) {
            uVar4 = (undefined2)(1);
          }
          else {
            uVar4 = (undefined2)(2);
          }
          *(undefined2 *)(iVar2 + 0x3e) = uVar4;
          uVar3 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(*(int *)(pcVar5 + 0xc) + 0xe))));
          *(undefined4 *)(iVar2 + 0x1e) = uVar3;
          *(undefined1 *)(iVar2 + 0x40) = 1;
        }
      }
      pcVar5 = (char*)(*(char **)(pcVar5 + 4));
    } while (pcVar5 != (char *)0x0);
  }
  return;
}

int fn_005d7640(char *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint unaff_EBX;
  /* Unknown primitive encodings retain the native incoming EBX low byte. */
  asm { mov unaff_EBX, ebx }

  iVar4 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar4), (int)(0x7a));
  *(undefined2 *)(iVar4 + 0x14) = 0x24;
  iVar1 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar4;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar1 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar4;
    iVar1 = (int)(native_006eac12);
    *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(iVar1 + 8) = iVar4;
  }
  iVar1 = (int)(native_006eac12);
  *(int *)(native_006eac12 + 8) = iVar4;
  iVar1 = (int)(*(int *)(iVar1 + 8));
  uVar5 = (undefined4)(fn_0045ede0((undefined4)(param_1), (undefined4)(0), (char)(1)));
  uVar5 = (undefined4)(GetHashNameNode((char *)(uVar5)));
  *(undefined4 *)(iVar1 + 0x16) = uVar5;
  *(undefined4 *)(iVar1 + 0x1e) = *(undefined4 *)(param_1 + 2);
  if (*(int *)(param_1 + 2) == 1) {
    if (param_1[6] == '\0') {
      unaff_EBX = (uint)(2);
    }
    else if (param_1[6] == '\x03') {
      unaff_EBX = (uint)(7);
    }
    else {
      cVar3 = (char)(fn_00454260((char *)(param_1)));
      if (cVar3 == '\0') {
        unaff_EBX = (uint)(6);
      }
      else {
        unaff_EBX = (uint)(8);
      }
    }
  }
  else {
    cVar3 = (char)(*param_1);
    if (((cVar3 == '\x01') && ((byte)param_1[6] < 0x17)) || (cVar3 == '\x04')) {
      cVar3 = (char)(fn_00454260((char *)(param_1)));
      if (cVar3 == '\0') {
        unaff_EBX = (uint)(5);
      }
      else {
        unaff_EBX = (uint)(7);
      }
    }
    else if ((cVar3 == '\x02') && ((byte)param_1[6] < 0x17)) {
      unaff_EBX = (uint)(4);
    }
    else if (cVar3 == '\0') {
      unaff_EBX = (uint)(0);
    }
  }
  *(uint *)(iVar1 + 0x1a) = unaff_EBX & 0xff;
  native_00710380 = (int)(0);
  native_007107f4 = (int)(param_1);
  fn_004561d0((undefined4)(fn_005d80f0));
  for (puVar2 = (undefined4*)(native_006eac22); puVar2 != (undefined4 *)0x0;
      puVar2 = *(undefined4 **)((int)puVar2 + 6)) {
    if (*(char *)(puVar2 + 1) == '\0') {
      uVar5 = (undefined4)(*puVar2);
      iVar6 = (int)(galloc((int)(0x7a)));
      memclrw((undefined1 *)(iVar6), (int)(0x7a));
      *(undefined2 *)(iVar6 + 0x14) = 0x16;
      iVar4 = (int)(native_006eac12);
      if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
        *(int *)(native_006eac12 + 8) = iVar6;
        *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar4 + 8);
      }
      else {
        **(int **)(native_006eac12 + 8) = iVar6;
        *(undefined4 *)(iVar6 + 4) = *(undefined4 *)(native_006eac12 + 8);
        *(int *)(native_006eac12 + 8) = iVar6;
      }
      *(int *)(native_006eac12 + 8) = iVar6;
      *(undefined4 *)(iVar6 + 0x16) = uVar5;
      uVar5 = (undefined4)(fn_005d8180((undefined1 *)(param_1)));
      *(undefined4 *)(iVar6 + 0x1e) = uVar5;
      *(int *)(iVar1 + 0x22) = iVar6;
      *(undefined1 *)(puVar2 + 1) = 1;
    }
  }
  return iVar1;
}

void fn_005d7870(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;

  puVar1 = (undefined4*)(*(undefined4 **)(param_1 + 0xe));
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return;
    }
    iVar3 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar3), (int)(0x7a));
    *(undefined2 *)(iVar3 + 0x14) = 0x1c;
    iVar2 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar3;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar3;
      *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar3;
    }
    *(int *)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(iVar3 + 0x1e) = puVar1[2];
    uVar4 = (undefined4)(fn_005d8180((undefined1 *)(puVar1[1])));
    *(undefined4 *)(iVar3 + 0x16) = uVar4;
    switch(*(undefined1 *)(puVar1 + 4)) {
    case 0:
      *(undefined2 *)(iVar3 + 0x22) = 1;
      break;
    case 1:
      *(undefined2 *)(iVar3 + 0x22) = 3;
      break;
    case 2:
      *(undefined2 *)(iVar3 + 0x22) = 2;
    }
    if (*(char *)((int)puVar1 + 0x11) != '\0') {
      *(undefined2 *)(iVar3 + 0x24) = 1;
    }
    if (*(char *)((int)puVar1 + 0x11) != '\0') {
      piVar5 = (int*)(*(int **)(param_1 + 0x12));
      if (piVar5 != (int *)0x0) {
        iVar2 = (int)(*(int *)(puVar1[1] + 10));
        do {
          iVar3 = (int)(strcmp((byte *)(iVar2 + 10), (byte *)(*(int *)(piVar5[1] + 10) + 10)));
          if (iVar3 == 0) break;
          piVar5 = (int*)((int *)*piVar5);
        } while (piVar5 != (int *)0x0);
      }
      iVar3 = (int)(galloc((int)(0x7a)));
      memclrw((undefined1 *)(iVar3), (int)(0x7a));
      *(undefined2 *)(iVar3 + 0x14) = 0xd;
      iVar2 = (int)(native_006eac12);
      if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
        *(int *)(native_006eac12 + 8) = iVar3;
        *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
      }
      else {
        **(int **)(native_006eac12 + 8) = iVar3;
        *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
        *(int *)(native_006eac12 + 8) = iVar3;
      }
      *(int *)(native_006eac12 + 8) = iVar3;
      *(undefined4 *)(iVar3 + 0x16) = *(undefined4 *)(puVar1[1] + 10);
      *(int *)(iVar3 + 0x28) = piVar5[2];
      *(undefined1 *)(iVar3 + 0x32) = 1;
      *(undefined2 *)(iVar3 + 0x26) = 3;
      uVar4 = (undefined4)(fn_005d8180((undefined1 *)(puVar1[1])));
      *(undefined4 *)(iVar3 + 0x1a) = uVar4;
    }
    puVar1 = (undefined4*)((undefined4 *)*puVar1);
  } while( true );
}

int fn_005d7a10(char *param_1)

{
  unsigned char nativeStack[20];
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  short sVar5;
  char *pcVar6;

  if (param_1[0x10] == '\x01') {
    sVar5 = (short)(0x17);
  }
  else {
    sVar5 = (short)(0x13);
  }
  if (sVar5 == 0) {
    CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x2d0));
  }
  iVar3 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar3), (int)(0x7a));
  *(short *)(iVar3 + 0x14) = sVar5;
  iVar2 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar3;
  }
  iVar2 = (int)(native_006eac12);
  *(int *)(native_006eac12 + 8) = iVar3;
  (*(int  *)(nativeStack+0xc)) = (int)(*(int *)(iVar2 + 8));
  *(undefined4 *)((*(int  *)(nativeStack+0xc)) + 0x16) = *(undefined4 *)(param_1 + 6);
  (*(int  *)(nativeStack+0x10)) = (int)((*(int  *)(nativeStack+0xc)));
  if (*(int *)((*(int  *)(nativeStack+0xc)) + 0x16) == 0) {
    *(undefined1 *)((*(int  *)(nativeStack+0xc)) + 0x22) = 1;
  }
  else {
    *(undefined1 *)((*(int  *)(nativeStack+0xc)) + 0x22) = 0;
    uVar4 = (undefined4)(fn_005d82b0((undefined4 *)(0), (int)(*(undefined4 *)(param_1 + 6))));
    *(undefined4 *)((*(int  *)(nativeStack+0x10)) + 0x1e) = uVar4;
  }
  *(undefined4 *)((*(int  *)(nativeStack+0x10)) + 0x24) = *(undefined4 *)(param_1 + 2);
  for (puVar1 = (undefined4*)(*(undefined4 **)(param_1 + 10)); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    iVar3 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar3), (int)(0x7a));
    *(undefined2 *)(iVar3 + 0x14) = 0xd;
    iVar2 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar3;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar3;
      *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar3;
    }
    *(int *)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(iVar3 + 0x16) = puVar1[2];
    if ((*param_1 == '\x05') && (param_1[0x10] > '\x03') && (param_1[0x10] < '\x0f')) {
      if ((*(int *)(param_1 + 10) == 0) || (*(int *)(*(int *)(param_1 + 10) + 4) == 0)) {
        CError_Internal((undefined4)(literal_006b4af7), (undefined4)(0x42a));
      }
      if ((char)native_0070efe8 == '\0') {
        *(undefined4 *)(iVar3 + 0x28) = puVar1[3];
      }
      else {
        *(int *)(iVar3 + 0x28) =
             (*(int *)(param_1 + 2) - *(int *)(*(int *)(*(int *)(param_1 + 10) + 4) + 2)) -
             puVar1[3];
      }
    }
    else {
      *(undefined4 *)(iVar3 + 0x28) = puVar1[3];
    }
    pcVar6 = (char*)((char *)puVar1[1]);
    if (*pcVar6 == '\b') {
      if ((char)native_0070efe8 != '\0') {
        (*(undefined4  *)(nativeStack+0x0)) = (undefined4)(*(undefined4 *)pcVar6);
        (*(undefined4  *)(nativeStack+0x4)) = (undefined4)(*(undefined4 *)(pcVar6 + 4));
        (*(undefined4  *)(nativeStack+0x8)) = (undefined4)(*(undefined4 *)(pcVar6 + 8));
        CABI_ReverseBitField((int)(&(*(undefined4  *)(nativeStack+0x0))));
        pcVar6 = (char*)((char *)&(*(undefined4  *)(nativeStack+0x0)));
      }
      uVar4 = (undefined4)(fn_005d8180((undefined1 *)(puVar1[1])));
      *(undefined4 *)(iVar3 + 0x1a) = uVar4;
      uVar4 = (undefined4)(fn_005d8180((undefined1 *)(*(undefined4 *)(pcVar6 + 6))));
      *(undefined4 *)(iVar3 + 0x1e) = uVar4;
      *(ushort *)(iVar3 + 0x30) = (ushort)(byte)pcVar6[10];
      *(ushort *)(iVar3 + 0x2e) = (ushort)(byte)pcVar6[0xb];
      *(undefined2 *)(iVar3 + 0x2c) = *(undefined2 *)(*(int *)(pcVar6 + 6) + 2);
    }
    else {
      uVar4 = (undefined4)(fn_005d8180((undefined1 *)(pcVar6)));
      *(undefined4 *)(iVar3 + 0x1a) = uVar4;
      *(undefined2 *)(iVar3 + 0x2c) = *(undefined2 *)(puVar1[1] + 2);
    }
  }
  iVar3 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar3), (int)(0x7a));
  *(undefined2 *)(iVar3 + 0x14) = 0xffff;
  iVar2 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar3;
    *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar3;
  }
  *(int *)(native_006eac12 + 8) = iVar3;
  *(int *)((*(int  *)(nativeStack+0x10)) + 0x28) = iVar3;
  native_00710380 = (int)(0);
  native_007107f4 = (int)(param_1);
  fn_004561d0((undefined4)(fn_005d80f0));
  for (puVar1 = (undefined4*)(native_006eac22); puVar1 != (undefined4 *)0x0;
      puVar1 = *(undefined4 **)((int)puVar1 + 6)) {
    if (*(char *)(puVar1 + 1) == '\0') {
      uVar4 = (undefined4)(*puVar1);
      iVar3 = (int)(galloc((int)(0x7a)));
      memclrw((undefined1 *)(iVar3), (int)(0x7a));
      *(undefined2 *)(iVar3 + 0x14) = 0x16;
      iVar2 = (int)(native_006eac12);
      if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
        *(int *)(native_006eac12 + 8) = iVar3;
        *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar2 + 8);
      }
      else {
        **(int **)(native_006eac12 + 8) = iVar3;
        *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(native_006eac12 + 8);
        *(int *)(native_006eac12 + 8) = iVar3;
      }
      *(int *)(native_006eac12 + 8) = iVar3;
      *(undefined4 *)(iVar3 + 0x16) = uVar4;
      uVar4 = (undefined4)(fn_005d8180((undefined1 *)(param_1)));
      *(undefined4 *)(iVar3 + 0x1e) = uVar4;
      *(int *)((*(int  *)(nativeStack+0xc)) + 0x2c) = iVar3;
      *(undefined1 *)(puVar1 + 1) = 1;
    }
  }
  return (*(int  *)(nativeStack+0x10));
}

int fn_005d7de0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;

  iVar2 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar2), (int)(0x7a));
  *(undefined2 *)(iVar2 + 0x14) = 4;
  iVar1 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar2;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar1 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar2;
    iVar1 = (int)(native_006eac12);
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(iVar1 + 8) = iVar2;
  }
  *(int *)(native_006eac12 + 8) = iVar2;
  *(undefined4 *)(iVar2 + 0x16) = *(undefined4 *)(param_1 + 0x12);
  if (*(int *)(param_1 + 0x12) != 0) {
    uVar3 = (undefined4)(fn_005d82b0((undefined4 *)(*(undefined4 *)(param_1 + 6)), (int)(*(int *)(param_1 + 0x12))));
    *(undefined4 *)(iVar2 + 0x1a) = uVar3;
  }
  *(undefined4 *)(iVar2 + 0x1e) = *(undefined4 *)(*(int *)(param_1 + 0xe) + 2);
  for (iVar1 = (int)(*(int *)(param_1 + 10)); iVar1 != 0; iVar1 = *(int *)(iVar1 + 2)) {
    iVar4 = (int)(galloc((int)(0x7a)));
    memclrw((undefined1 *)(iVar4), (int)(0x7a));
    *(undefined2 *)(iVar4 + 0x14) = 0x28;
    iVar5 = (int)(native_006eac12);
    if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
      *(int *)(native_006eac12 + 8) = iVar4;
      *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar5 + 8);
    }
    else {
      **(int **)(native_006eac12 + 8) = iVar4;
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(native_006eac12 + 8);
      *(int *)(native_006eac12 + 8) = iVar4;
    }
    *(int *)(native_006eac12 + 8) = iVar4;
    *(undefined4 *)(iVar4 + 0x16) = *(undefined4 *)(iVar1 + 6);
    *(undefined4 *)(iVar4 + 0x1a) = *(undefined4 *)(iVar1 + 0x12);
  }
  iVar5 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar5), (int)(0x7a));
  *(undefined2 *)(iVar5 + 0x14) = 0xffff;
  iVar1 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar5;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar1 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar5;
    *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar5;
  }
  *(int *)(native_006eac12 + 8) = iVar5;
  *(int *)(iVar2 + 0x22) = iVar5;
  return iVar2;
}

int fn_005d7f70(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;

  iVar1 = (int)(*(int *)(param_1 + 6));
  iVar2 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar2), (int)(0x7a));
  *(undefined2 *)(iVar2 + 0x14) = 1;
  iVar5 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar2;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar5 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar2;
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar2;
  }
  *(int *)(native_006eac12 + 8) = iVar2;
  uVar3 = (undefined4)(fn_005d8180((undefined1 *)(iVar1)));
  *(undefined4 *)(iVar2 + 0x16) = uVar3;
  *(undefined4 *)(iVar2 + 0x1e) = *(undefined4 *)(param_1 + 2);
  iVar4 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar4), (int)(0x7a));
  *(undefined2 *)(iVar4 + 0x14) = 0x21;
  iVar5 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar4;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar5 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar4;
    *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(native_006eac12 + 8) = iVar4;
  }
  iVar5 = (int)(native_006eac12);
  *(int *)(native_006eac12 + 8) = iVar4;
  iVar1 = (int)(*(int *)(iVar1 + 2));
  if (iVar1 == 0) {
    *(undefined4 *)(*(int *)(iVar5 + 8) + 0x16) = 0;
  }
  else {
    *(int *)(*(int *)(iVar5 + 8) + 0x16) = *(int *)(param_1 + 2) / iVar1 - 1;
  }
  iVar5 = (int)(galloc((int)(0x7a)));
  memclrw((undefined1 *)(iVar5), (int)(0x7a));
  *(undefined2 *)(iVar5 + 0x14) = 0xffff;
  iVar1 = (int)(native_006eac12);
  if (*(int **)(native_006eac12 + 8) == (int *)0x0) {
    *(int *)(native_006eac12 + 8) = iVar5;
    *(undefined4 *)(native_006eac12 + 4) = *(undefined4 *)(iVar1 + 8);
  }
  else {
    **(int **)(native_006eac12 + 8) = iVar5;
    iVar1 = (int)(native_006eac12);
    *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(native_006eac12 + 8);
    *(int *)(iVar1 + 8) = iVar5;
  }
  *(int *)(native_006eac12 + 8) = iVar5;
  *(int *)(iVar2 + 0x22) = iVar5;
  return iVar2;
}

void fn_005d80f0(undefined4 param_1, undefined4 param_2, int param_3)

{
  undefined4 *puVar1;

  if (native_007107f4 == param_3) {
    native_00710380 = (int)(param_2);
    if (native_006eac22 == (undefined4 *)0x0) {
      native_006eac22 = (undefined4 *)((undefined4 *)galloc((int)(10)));
      memclrw((undefined1 *)(native_006eac22), (int)(10));
      native_006eac26 = (undefined4 *)(native_006eac22);
      *native_006eac22 = (undefined4 )(param_2);
    }
    else {
      puVar1 = (undefined4*)((undefined4 *)galloc((int)(10)));
      memclrw((undefined1 *)(puVar1), (int)(10));
      *(undefined4 **)((int)native_006eac26 + 6) = puVar1;
      *puVar1 = (undefined4)(param_2);
      native_006eac26 = (undefined4 *)(puVar1);
    }
  }
  return;
}

undefined4 * fn_005d8180(undefined1 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;

  for (puVar1 = (undefined4*)(native_006eac06); puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    if ((undefined1 *)puVar1[1] == param_1) {
      return puVar1;
    }
  }
  puVar3 = (undefined4*)((undefined4 *)galloc((int)(0xe)));
  memclrw((undefined1 *)(puVar3), (int)(0xe));
  puVar1 = (undefined4*)(puVar3);
  if (native_006eac02 != (undefined4 *)0x0) {
    *native_006eac02 = (undefined4 )(puVar3);
    puVar1 = (undefined4*)(native_006eac06);
  }
  native_006eac06 = (int)(puVar1);
  native_006eac02 = (undefined4 *)(puVar3);
  puVar3[1] = (undefined4)(param_1);
  *(undefined1 *)(puVar3 + 3) = 0;
  puVar3[2] = (undefined4)(0);
  switch(*param_1) {
  case 5:
    for (puVar1 = (undefined4*)(*(undefined4 **)(param_1 + 10)); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      fn_005d8180((undefined1 *)(puVar1[1]));
    }
    break;
  case 6:
    for (puVar1 = (undefined4*)(*(undefined4 **)(param_1 + 0xe)); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      fn_005d8180((undefined1 *)(puVar1[1]));
    }
    for (iVar2 = (int)(*(int *)(param_1 + 0x16)); iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
      fn_005d8180((undefined1 *)(*(undefined4 *)(iVar2 + 0xc)));
    }
    break;
  case 7:
    fn_005d8180((undefined1 *)(*(undefined4 *)(param_1 + 0xe)));
    for (puVar1 = (undefined4*)(*(undefined4 **)(param_1 + 6)); puVar1 != (undefined4 *)0x0 &&
        (puVar1 != (undefined4 *)&native_007037c0) && (puVar1 != (undefined4 *)&native_0070bb08);
        puVar1 = (undefined4 *)*puVar1) {
      fn_005d8180((undefined1 *)(puVar1[3]));
    }
    break;
  case 8:
    goto switchD_005d81eb_caseD_8;
  case 0xc:
    goto switchD_005d81eb_caseD_8;
  case 0xd:
switchD_005d81eb_caseD_8:
    fn_005d8180((undefined1 *)(*(undefined4 *)(param_1 + 6)));
  }
  return puVar3;
}

int fn_005d82b0(undefined4 *param_1, int param_2)
{
    if (CParser_IsNullOrAtOrDollarPrefixedName(param_2))
        return 0;
    while (param_1 && !param_1[1])
        param_1 = (undefined4 *)param_1[0];
    if (param_1) {
        native_0070bc24 = 0;
        fn_005d8330(param_1);
        fn_0046d5a0((undefined4 *)&native_0070bc20, (char *)(param_2 + 10));
        fn_0044cfe0((int)native_0070bc20);
        param_2 = (int)GetHashNameNode(*native_0070bc20);
        fn_0044d0a0((int)native_0070bc20);
    }
    return param_2;
}

void fn_005d8330(undefined4 *param_1)
{
    while (param_1 && !param_1[1])
        param_1 = (undefined4 *)param_1[0];
    if (param_1) {
        fn_005d8330((undefined4 *)param_1[0]);
        fn_0046d530((undefined4 *)&native_0070bc20, (char *)(param_1[1] + 10));
        fn_0046d530((undefined4 *)&native_0070bc20, &native_006b4b27);
    }
}

void fn_005d84f0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;

  if (native_00725eda == '\0') {
    fn_004c3010();
  }
  if (native_0070f287 == '\0') {
    return;
  }
  if (*(char *)(*(int *)(param_1 + 0xc) + 10) == '@') {
    return;
  }
  puVar2 = (undefined4*)(native_006eac32);
  if (*(char *)(param_1 + 2) != '\0') {
    return;
  }
  while ((puVar2 != (undefined4 *)0x0 && (cVar1 = fn_005d86b0((int)(puVar2[1]), (int)(param_1)), cVar1 == '\0')))
  {
    puVar2 = (undefined4*)((undefined4 *)*puVar2);
  }
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4*)((undefined4 *)galloc((int)(8)));
    *puVar2 = (undefined4)(0);
    puVar2[1] = (undefined4)(param_1);
    *puVar2 = (undefined4)(native_006eac32);
    native_006eac32 = (undefined4 *)(puVar2);
  }
  if (native_0070f06e == '\0') {
    fn_004da500((int)(puVar2));
  }
  else {
    fn_005ce570((int)(puVar2));
  }
  return;
}

void fn_005d85a0(void)

{
  native_006eac32 = (undefined4 *)(0);
  native_006eac30 = (char)(0);
  return;
}

void fn_005d85c0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 uVar3;
  char cVar4;
  undefined4 uVar5;

  uVar3 = (undefined1)(native_0070f287);
  native_006eac30 = (char)(1);
  native_0070f287 = (char)(1);
  for (puVar2 = (undefined4*)(native_006eac32); puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
    iVar1 = (int)(puVar2[1]);
    if (*(int *)(iVar1 + 0x38) == 0) {
      if (native_0070f06e == '\0') {
        DWARF_CreateObjectDebugEntry((int)(iVar1));
      }
      else {
        uVar5 = (undefined4)(fn_005cd660((undefined4)(iVar1)));
        cVar4 = (char)(fn_00452fe0((int)(iVar1)));
        fn_005cf400((int)(iVar1), (undefined4)(cVar4 == '\0'), (undefined4)(uVar5));
      }
    }
  }
  native_0070f287 = (char)(uVar3);
  return;
}

void fn_005d8640(undefined4 param_1, char *param_2)
{
    undefined4 *entry;
    *param_2 = native_006eac30;
    for (entry = native_006eac32; entry; entry = (undefined4 *)entry[0]) {
        if (fn_005d86b0((int)entry[1], (int)param_1)) {
            if (!*param_2)
                entry[1] = param_1;
            return;
        }
    }
    entry = (undefined4 *)galloc(8);
    entry[0] = 0;
    entry[1] = param_1;
    entry[0] = (undefined4)native_006eac32;
    native_006eac32 = entry;
}

bool fn_005d86b0(int param_1, int param_2)

{
  int iVar1;
  int iVar2;

  if (param_1 == param_2) {
    return true;
  }
  if ((*(uint *)(param_1 + 0x14) & 0x80000) == 0) {
    iVar1 = (int)(0);
  }
  else {
    iVar1 = (int)(*(int *)(param_1 + 8));
  }
  if ((*(uint *)(param_2 + 0x14) & 0x80000) == 0) {
    iVar2 = (int)(0);
  }
  else {
    iVar2 = (int)(*(int *)(param_2 + 8));
  }
  if ((*(int *)(param_1 + 0xc) == *(int *)(param_2 + 0xc)) &&
     (*(int *)(param_1 + 8) == *(int *)(param_2 + 8) || (iVar1 == iVar2))) {
    if ((*(char *)(param_1 + 2) == *(char *)(param_2 + 2)) &&
       (*(char *)(param_1 + 2) == '\0' && (*(char *)(param_2 + 2) == '\0'))) {
      iVar1 = (int)(COptimizer_GetFunctionObject((int)(param_2)));
      iVar2 = (int)(COptimizer_GetFunctionObject((int)(param_1)));
      return iVar2 == iVar1;
    }
  }
  return false;
}
