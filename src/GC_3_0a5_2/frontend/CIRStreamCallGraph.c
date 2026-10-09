/* Native CIRStreamCallGraph.c. The 1.2.5 tree has no corresponding stream TU.
 * Private UInt32 address views preserve the verified x86 record offsets while
 * source-file, object and IR layouts migrate separately from the older headers.
 * Generated switch tables receive no invented original-address bindings. */
#include "compiler/common.h"
#include <stddef.h>
#include <string.h>
#pragma pack(push,2)
typedef struct CGObject {UInt8 kind,access,storage,pad;UInt32 address,space,name,type,qualifiers;UInt16 sclass,flags;UInt32 graph;UInt8 unknown20[32];UInt32 payload,size,body;UInt8 unknown4c[12];UInt16 mode;UInt8 unknown5a[2];UInt16 aux;UInt8 tag,pad5f;} CGObject;
typedef struct CGHeader {UInt32 magic,version,types;UInt8 extended,pad[3];} CGHeader;
typedef struct CGSourceFile {UInt32 name,next;UInt8 kind,access;UInt32 contents,contentsSize,lines;UInt32 payload[7];UInt8 flags,pad33;} CGSourceFile;
typedef struct CGFixup {struct CGFixup *next;UInt32 *target;} CGFixup;
typedef struct CGImport {UInt32 object;CGFixup *fixups;} CGImport;
typedef struct CGFileIndex {struct CGFileIndex *next;CGSourceFile *scope;UInt32 index;} CGFileIndex;
typedef struct CGIRBody {UInt32 data,size,a,b,c,refs;UInt8 loaded,pad19;} CGIRBody;
typedef struct CGIRReference {UInt32 value;UInt8 kind,flags;UInt16 offset;} CGIRReference;
typedef struct CGIRFunction {CGIRBody *body;UInt32 temporary,flags;UInt8 registers[182],a,b,loaded,pad;} CGIRFunction;
#pragma pack(pop)
typedef char CGObjectSize[(sizeof(CGObject)==96)?1:-1];
typedef char CGObjectPayload[(offsetof(CGObject,payload)==64)?1:-1];
typedef char CGHeaderSize[(sizeof(CGHeader)==16)?1:-1];
typedef char CGSourceFileSize[(sizeof(CGSourceFile)==52)?1:-1];
typedef char CGSourceFileContents[(offsetof(CGSourceFile,contents)==10)?1:-1];
typedef char CGSourceFileLines[(offsetof(CGSourceFile,lines)==18)?1:-1];
typedef char CGSourceFileFlags[(offsetof(CGSourceFile,flags)==50)?1:-1];
typedef char CGIRBodySize[(sizeof(CGIRBody)==26)?1:-1];
typedef char CGIRReferenceSize[(sizeof(CGIRReference)==8)?1:-1];
typedef char CGIRFunctionSize[(sizeof(CGIRFunction)==198)?1:-1];
static char filename[]="CIRStreamCallGraph.c";
static char unknown_file[]="<unknown file>";
extern UInt32 galloc(UInt32),CompilerTools_AllocatePool(UInt32);
extern void memclrw(void *,UInt32),CError_FatalError(SInt16),CError_LongJump(void);
extern SInt32 CError_Internal(const char *,SInt32);
extern void CError_Warning(SInt32,...),CError_ReportError(SInt32,...);
extern SInt16 InitGList(void *,SInt32),iscpp_typeequal(UInt32,UInt32);
extern void FreeGList(void *);
extern UInt32 CCallGraph_AddFunction(UInt32),COptimizer_GetFunctionObject(UInt32);
extern void fn_00449d60(void);
extern UInt32 fn_0044b8f0(UInt32);
extern UInt32 fn_0044c0e0(void);
extern UInt8 fn_00452fe0(UInt32);
extern UInt32 fn_00455d40(UInt32);
extern void fn_00462e30(void);
extern UInt32 fn_0046c800(UInt32);
extern void fn_0046d950(void *);
extern void fn_0046d960(void *);
extern UInt32 fn_0047cde0(UInt32);
extern UInt32 fn_0047ce20(UInt32);
extern void fn_0047cf40(UInt32,UInt32);
extern UInt32 fn_0047d080(UInt32);
extern UInt32 fn_004be1f0(UInt32,UInt32,UInt32);
extern UInt32 fn_004be290(SInt32,UInt32 *,UInt32 *);
extern void fn_004be300(UInt32,UInt32);
extern void fn_004c0120(void *);
extern UInt32 fn_004eaff0(UInt32,UInt32);
extern UInt32 fn_004eb0d0(UInt32,UInt32);
extern void fn_00509e10(UInt8);
extern void fn_00509e40(void);
extern void fn_005a1720(void);
extern UInt8 fn_005a1780(UInt32);
extern UInt32 fn_005c9340(UInt32,void *);
extern void fn_005c93e0(UInt32);
extern UInt32 fn_005c95c0(UInt32,void *,UInt32);
extern void fn_005c95e0(UInt32,UInt32);
extern UInt32 fn_005c9600(UInt32,void *);
extern void fn_005c9640(UInt32);
extern UInt32 fn_005c9690(UInt32,void *);
extern void fn_005c96d0(SInt32);
extern UInt32 fn_005c9720(UInt32,void *);
extern void fn_005c9740(UInt16);
extern UInt32 fn_005c9760(UInt32,void *);
extern void fn_005c9780(SInt16);
extern void fn_005c97a0(SInt32);
extern UInt32 fn_005c97c0(UInt32,void *);
extern void fn_005c9cd0(UInt32);
extern UInt32 fn_005cb500(UInt32,void *);
extern void fn_005cb6e0(UInt32);

static UInt8 fn_006dcb18;
static UInt32 fn_006dcb1a;
static UInt32 fn_006dcb1e;
static UInt32 * fn_006dcb22;
extern UInt32 *fn_00702cf8;
extern UInt32 fn_00702cfc;
extern UInt32 *fn_00710094;
extern UInt32 fn_00710258;
extern UInt32 fn_007102c8;
extern UInt32 fn_00710330;
extern UInt32 fn_00710340;
extern UInt32 fn_00710378;
extern UInt32 fn_007107ac;
extern UInt32 fn_007107b8;
extern UInt32 fn_0071081c;
extern UInt32 fn_00710858;
extern UInt32 fn_007108b4;
extern UInt32 fn_007108c0;
extern UInt32 fn_00710928;
extern UInt32 fn_0071092c;
extern UInt32 fn_007109c4;
extern UInt32 fn_00711b00;
extern UInt32 fn_00711b1c;
extern UInt32 fn_00711b24;
extern UInt32 fn_00711b80;
extern UInt32 *fn_00711bac;
extern UInt32 fn_00711bb4;
extern UInt32 fn_00711bb8;
extern UInt32 fn_00715c00;
extern UInt32 fn_00715c18;
extern UInt32 fn_00715c58;
extern UInt32 fn_00716c1c;
extern UInt32 fn_00716c98;
extern UInt32 fn_00716cac;
extern UInt32 fn_00716cd8;
extern UInt32 fn_00716ce4;
extern UInt32 fn_00716d3c;
extern UInt32 fn_00716d60;
extern UInt32 fn_00716d68;
extern UInt32 fn_00716ee2;
extern UInt32 fn_00716ee6;
extern UInt32 fn_00716eea;
extern UInt8 fn_00725e5e;
void fn_004bac40(void);
void CIRStream_ImportCallGraph(UInt32 param_1, UInt32 param_2, UInt8 param_3);
UInt8 fn_004bafe0(int param_1, UInt32 param_2);
UInt8 * fn_004bb020(UInt32 param_1, int param_2);
void fn_004bb2d0(int param_1);
int fn_004bb490(int param_1, int *param_2, UInt32 param_3);
UInt8 *fn_004bb970(UInt32 param_1, int param_2);
void fn_004bbb30(int param_1);
UInt8 * fn_004bbc90(UInt32 param_1, int param_2, UInt32 param_3, UInt32 param_4);
void fn_004bbd90(int param_1);
UInt8 * fn_004bbeb0(UInt32 param_1, int *param_2, UInt8 *param_3);
void fn_004bc0f0(int *param_1);
UInt8 * fn_004bc2a0(UInt32 param_1, int *param_2);
void fn_004bc510(UInt32 *param_1);
void fn_004bc780(int param_1, int param_2, int param_3, char param_4);
UInt8 fn_004bcdb0(int param_1, int param_2);

/* Export the call graph, source-file cache and packed object bodies; patch the header after writing. */
void fn_004bac40(void) {
    struct {UInt32 **data;UInt32 size,capacity,extra;} list;
    CGHeader header;UInt32 *node;
    fn_00509e10(1);fn_006dcb22=0;fn_006dcb1e=0;
    memclrw(&header,16);fn_005c95e0((UInt32)&header,16);fn_004bc510((UInt32 *)fn_0044c0e0());
    if(InitGList(&list,500))CError_LongJump();
    fn_004c0120(&list);fn_005c9640(list.size);fn_0046d960(&list);fn_005c95e0((UInt32)*list.data,list.size);fn_0046d950(&list);FreeGList(&list);
    fn_005a1720();fn_005c9640(fn_00711bb4);
    for(node=fn_00711bac;node;node=(UInt32 *)*node)fn_004bb2d0((int)node);
    fn_005c9640(0xbaceecab);
    header.magic=0xbaceecab;header.version=0x10002;header.types=fn_00710378-0x38;header.extended=fn_00725e5e;
    *(CGHeader *)*fn_00702cf8=header;fn_00716ee2=0;fn_00716eea=fn_00702cfc;fn_00716ee6=0;
}

/* Import the graph, allocate object slots and resolve forward object references after every object is read. */
void CIRStream_ImportCallGraph(UInt32 param_1, UInt32 param_2, UInt8 param_3)
{
  UInt32 *puVar1;
  UInt32 uVar2;
  int iVar3;
  UInt32 header[4];
  UInt32 local_10;
  UInt32 local_c;
  fn_00509e40();
  fn_006dcb22 = 0;
  fn_006dcb1e = 0;
  fn_006dcb18 = param_3;
  fn_00710094 = (UInt32 *)galloc(8);
  memclrw((void *)(fn_00710094),(UInt32)(8));
  fn_00710094[1] = param_2;
  uVar2 = fn_005c95c0((UInt32)(param_1),(void *)(header),(UInt32)(0x10));
  if (header[0] != -0x45311355) {
    CError_FatalError(0x2913);
  }
  if (header[1] != 0x10002) {
    CError_FatalError(0x2914);
  }
  if (*(UInt8 *)(header+3) != '\0') {
    fn_00725e5e = 1;
  }
  fn_00710378 = 0x38;
  fn_00710258 = CompilerTools_AllocatePool(header[2] * 4);
  memclrw((void *)(fn_00710258),(UInt32)(header[2] * 4));
  uVar2 = (UInt32)fn_004bc2a0((UInt32)(uVar2),(int *)(fn_00710094));
  iVar3 = fn_005c9600((UInt32)(uVar2),(void *)(&local_c));
  fn_004be300((UInt32)(iVar3),(UInt32)(local_c));
  uVar2 = fn_005c9600((UInt32)(iVar3 + local_c),(void *)(&local_c));
  fn_006dcb1a = CompilerTools_AllocatePool(local_c * 8);
  memclrw((void *)(fn_006dcb1a),(UInt32)(local_c * 8));
  local_10 = 0;
  if (local_c != 0) {
    do {
      uVar2 = (UInt32)fn_004bb020(uVar2, local_10);
      local_10 = local_10 + 1;
    } while (local_10 < local_c);
  }
  local_10 = 0;
  if (local_c != 0) {
    do {
      if (*(int *)(fn_006dcb1a + local_10 * 8) == 0) {
        CError_Internal(filename, 0x60e);
      }
      for (puVar1 = *(UInt32 **)(fn_006dcb1a + 4 + local_10 * 8); puVar1 != (UInt32 *)0x0;
          puVar1 = (UInt32 *)*puVar1) {
        *(UInt32 *)puVar1[1] = *(UInt32 *)(fn_006dcb1a + local_10 * 8);
      }
      local_10 = local_10 + 1;
    } while (local_10 < local_c);
  }
  fn_005c9600((UInt32)(uVar2),(void *)(&local_10));
  if (local_10 != 0xbaceecab) {
    CError_FatalError(0x2913);
  }
  return;
}

/* Probe the 16-byte call-graph header without importing it. */
UInt8 fn_004bafe0(int param_1, UInt32 param_2)
{
  int local_10 [4];
  if ((param_1 != 0) && (param_2 >= 16)) {
    fn_005c95c0((UInt32)(param_1),(void *)(local_10),(UInt32)(0x10));
    return local_10[0] == -0x45311355;
  }
  return 0;
}

/* Import one builtin or full object record with packed 96-byte and 198-byte scratch views. */
UInt8 * fn_004bb020(UInt32 param_1, int param_2)
{
  UInt8 *puVar1;
  int iVar2;
  UInt32 uVar3;
  UInt8 *puVar4;
  UInt32 local_148;
  UInt8 local_144[198];
  UInt8 object[96];
  char local_19;
  int local_18;
  UInt32 local_14;
  int local_10;
  puVar1 = (UInt8 *)fn_005c9600((UInt32)(param_1),(void *)(&local_14));
  if (local_14 < 2) {
    memclrw((void *)((object+0)),(UInt32)(0x60));
    memclrw((void *)(local_144),(UInt32)(0xc6));
    *(UInt8 *)(object+0) = 5;
    *(UInt8 *)(object+1) = *puVar1;
    *(UInt8 *)(object+2) = puVar1[1];
    if (puVar1[2] == '\0') {
      iVar2 = fn_005c9690((UInt32)(puVar1 + 3),(void *)(&local_148));
      *(UInt32 *)(object+4) = local_148;
    }
    else {
      iVar2 = fn_005c9600((UInt32)(puVar1 + 3),(void *)(&local_10));
      fn_005c9640((UInt32)(local_10));
      *(UInt32 *)(object+4) = fn_004be1f0((UInt32)(0),(UInt32)(iVar2),(UInt32)(local_10));
      iVar2 = iVar2 + local_10;
    }
    uVar3 = fn_005cb500((UInt32)(iVar2),(void *)((object+8)));
    uVar3 = fn_005c9340((UInt32)(uVar3),(void *)((object+12)));
    uVar3 = fn_005c97c0((UInt32)(uVar3),(void *)((object+16)));
    uVar3 = fn_005c9600((UInt32)(uVar3),(void *)((object+20)));
    uVar3 = fn_005c9720((UInt32)(uVar3),(void *)((object+24)));
    puVar1 = (UInt8 *)fn_005c9720((UInt32)(uVar3),(void *)((object+26)));
    local_19 = '\0';
    switch(*(UInt8 *)(object+2)) {
    case 0:
      puVar1 = (UInt8 *)fn_004bb970((UInt32)(puVar1),(int)((object+0)));
      break;
    default:
      CError_Internal(filename, 0x598);
      break;
    case 2:
      puVar1 = (UInt8 *)fn_005c9600((UInt32)(puVar1),(void *)((object+64)));
      break;
    case 3:
    case 4:
      puVar1 = (UInt8 *)fn_004bbc90((UInt32)(puVar1),(int)((object+0)),(UInt32)(local_144),(UInt32)(&local_19));
      break;
    case 5:
      uVar3 = fn_005c9600((UInt32)(puVar1),(void *)((object+68)));
      *(UInt32 *)(object+64) = galloc(*(UInt32 *)(object+68));
      puVar1 = (UInt8 *)fn_005c95c0((UInt32)(uVar3),(void *)(*(UInt32 *)(object+64)),(UInt32)(*(UInt32 *)(object+68)));
    }
    if (local_19 == '\0') {
      puVar4 = (UInt8 *)0x0;
    }
    else {
      puVar4 = local_144;
    }
    fn_004bc780((int)((object+0)),(int)(puVar4),(int)(param_2),(char)(local_14 == 1));
    return puVar1;
  }
  fn_004bb490((int)(0),(int *)(&local_18),(int)(local_14 - 1));
  if (*(int *)(local_18 + 0x1c) == 0) {
    CCallGraph_AddFunction((UInt32)(local_18));
  }
  if (*(int *)(fn_006dcb1a + param_2 * 8) != 0) {
    CError_Internal(filename, 0x555);
  }
  *(int *)(fn_006dcb1a + param_2 * 8) = local_18;
  return puVar1;
}

/* Export a builtin reference or complete object record selected by storage kind. */
void fn_004bb2d0(int param_1)
{
  char *pcVar1;
  char cVar2;
  int iVar3;
  UInt32 uStack_10;
  UInt32 uStack_c;
  pcVar1 = *(char **)(param_1 + 8);
  if (pcVar1 == (char *)0x0) {
    CError_Internal(filename, 0x4ed);
  }
  iVar3 = fn_004bb490((int)(pcVar1),(int *)(0),(int)(0));
  if (iVar3 == 0) {
    fn_005c97a0((SInt32)(*(char *)(param_1 + 0x1d) != '\0'));
    if (*pcVar1 != '\x05') {
      CError_Internal(filename, 0x501);
    }
    fn_005c97a0((SInt32)((int)pcVar1[1]));
    fn_005c97a0((SInt32)((int)pcVar1[2]));
    cVar2 = fn_004be290((SInt32)(*(UInt32 *)(pcVar1 + 4)),(UInt32 *)(&uStack_c),(UInt32 *)(&uStack_10));
    if (cVar2 == '\0') {
      fn_005c97a0((SInt32)(0));
      fn_005c96d0((SInt32)(*(UInt32 *)(pcVar1 + 4)));
    }
    else {
      fn_005c97a0((SInt32)(1));
      fn_005c9640((UInt32)(uStack_10));
      fn_005c95e0((UInt32)(uStack_c),(UInt32)(uStack_10));
    }
    fn_005cb6e0((UInt32)(*(UInt32 *)(pcVar1 + 8)));
    fn_005c93e0((UInt32)(*(UInt32 *)(pcVar1 + 0xc)));
    fn_005c9cd0((UInt32)(*(UInt32 *)(pcVar1 + 0x10)));
    fn_005c9640((UInt32)(*(UInt32 *)(pcVar1 + 0x14)));
    fn_005c9740((UInt16)(*(UInt16 *)(pcVar1 + 0x18)));
    fn_005c9740((UInt16)(*(UInt16 *)(pcVar1 + 0x1a)));
    if (*(int *)(pcVar1 + 0x1c) != param_1) {
      CError_Internal(filename, 0x51e);
    }
    COptimizer_GetFunctionObject((UInt32)(pcVar1));
    switch(pcVar1[2]) {
    case '\0':
      fn_004bbb30((int)(pcVar1));
      break;
    default:
      CError_Internal(filename, 0x538);
      break;
    case '\x02':
      fn_005c9640((UInt32)(*(UInt32 *)(pcVar1 + 0x40)));
      break;
    case '\x03':
    case '\x04':
      fn_004bbd90((int)(pcVar1));
      break;
    case '\x05':
      fn_005c9640((UInt32)(*(UInt32 *)(pcVar1 + 0x44)));
      fn_005c95e0((UInt32)(*(UInt32 *)(pcVar1 + 0x40)),(UInt32)(*(UInt32 *)(pcVar1 + 0x44)));
      if (*(int *)(pcVar1 + 0x48) != 0) {
        CError_Internal(filename, 0x534);
      }
    }
    return;
  }
  fn_005c9640((UInt32)(iVar3 + 1));
  return;
}

/* Translate builtin object pointers and one-based wire IDs using an unsigned counter. */
int fn_004bb490(int param_1, int *param_2, UInt32 param_3)
{
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_0071092c;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_0071092c) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_007108c0;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_007108c0) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00711b24;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00711b24) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00716d3c;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00716d3c) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_0071081c;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_0071081c) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_007107b8;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_007107b8) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_007102c8;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_007102c8) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_007107ac;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_007107ac) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00710340;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00710340) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00710928;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00710928) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_007108b4;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_007108b4) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00716cac;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00716cac) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00711bb8;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00711bb8) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00715c58;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00715c58) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00710858;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00710858) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00711b80;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00711b80) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00711b00;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00711b00) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00711b1c;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00711b1c) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00716c98;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00716c98) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00715c18;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00715c18) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00716d68;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00716d68) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00716ce4;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00716ce4) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00716d60;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00716d60) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00716cd8;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00716cd8) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00710330;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00710330) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00716c1c;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00716c1c) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    --param_3;
    if (param_3 == 0) {
      *param_2 = fn_00715c00;
      return 0;
    }
  }
  else {
    param_3 = param_3 + 1;
    if (param_1 == fn_00715c00) {
      return param_3;
    }
  }
  if (param_1 == 0) {
    if (--param_3 == 0) {
      *param_2 = fn_007109c4;
      return 0;
    }
  }
  else if (param_1 == fn_007109c4) {
    return param_3 + 1;
  }
  if (param_1 == 0) {
    CError_Internal(filename, 0x4de);
  }
  return 0;
}

/* Import function source/body metadata and linked object references; EAX is the next stream position. */
UInt8 *fn_004bb970(UInt32 param_1, int param_2)
{
  int *piVar1;
  UInt32 uVar2;
  char *pcVar3;
  int iVar4;
  UInt8 *puVar5;
  UInt32 *puVar6;
  char *pcVar7;
  UInt32 *puVar8;
  UInt32 *puVar9;
  int local_1c;
  int local_18;
  int local_14;
  uVar2 = fn_005c9340((UInt32)(param_1),(void *)(param_2 + 0x48));
  pcVar3 = (char *)fn_005c9600((UInt32)(uVar2),(void *)(&local_14));
  if (local_14 != 0) {
    iVar4 = galloc(0x1a);
    memclrw((void *)(iVar4),(UInt32)(0x1a));
    *(int *)(param_2 + 0x4c) = iVar4;
    *(int *)(iVar4 + 0x14) = local_14;
    pcVar7 = pcVar3 + 1;
    if (*pcVar3 != '\0') {
      uVar2 = (UInt32)fn_004bc2a0((UInt32)(pcVar7),(int *)(iVar4));
      uVar2 = fn_005c9600((UInt32)(uVar2),(void *)(iVar4 + 4));
      pcVar7 = (char *)fn_005c9600((UInt32)(uVar2),(void *)(iVar4 + 8));
    }
    pcVar3 = pcVar7 + 1;
    if (*pcVar7 != '\0') {
      uVar2 = galloc(local_14);
      *(UInt32 *)(iVar4 + 0xc) = uVar2;
      pcVar3 = (char *)fn_005c95c0((UInt32)(pcVar3),(void *)(*(UInt32 *)(iVar4 + 0xc)),(UInt32)(local_14));
    }
    puVar8 = (UInt32 *)(iVar4 + 0x10);
    puVar5 = (UInt8 *)fn_005c9600((UInt32)(pcVar3),(void *)(&local_1c));
    puVar9 = puVar8;
    if (local_1c != 0) {
      do {
        puVar8 = (UInt32 *)galloc(0x10);
        memclrw((void *)(puVar8),(UInt32)(0x10));
        piVar1 = (int *)(puVar8 + 1);
        uVar2 = fn_005c9600((UInt32)(puVar5),(void *)(&local_18));
        *piVar1 = *(int *)(fn_006dcb1a + local_18 * 8);
        if (*piVar1 == 0) {
          puVar6 = (UInt32 *)CompilerTools_AllocatePool(8);
          *puVar6 = *(UInt32 *)(fn_006dcb1a + 4 + local_18 * 8);
          puVar6[1] = (UInt32)piVar1;
          *(UInt32 **)(fn_006dcb1a + 4 + local_18 * 8) = puVar6;
        }
        uVar2 = fn_005c9690((UInt32)(uVar2),(void *)(puVar8 + 2));
        puVar5 = (UInt8 *)fn_005c9690((UInt32)(uVar2),(void *)(puVar8 + 3));
        *puVar9 = (UInt32)puVar8;
        local_1c = local_1c - 1;
        puVar9 = puVar8;
      } while (local_1c != 0);
      local_1c = 0;
    }
    *puVar8 = 0;
    *(UInt8 *)(iVar4 + 0x18) = *puVar5;
    pcVar3 = (char *)puVar5 + 1;
  }
  return (UInt8 *)fn_005c95c0((UInt32)(pcVar3),(void *)(param_2 + 0x58),(UInt32)(2));
}

/* Export function source/body metadata and object-reference links. */
void fn_004bbb30(int param_1)
{
  UInt32 *puVar1;
  UInt32 *puVar2;
  int *piVar3;
  int iVar4;
  if (*(int *)(param_1 + 0x48) == 0) {
    CError_Internal(filename, 0x43b);
  }
  fn_005c93e0((UInt32)(*(UInt32 *)(param_1 + 0x48)));
  piVar3 = (int *)fn_0047cde0((UInt32)(param_1));
  if (piVar3 == (int *)0x0) {
    fn_005c9640((UInt32)(0));
  }
  else {
    if (piVar3[5] == 0) {
      CError_Internal(filename, 0x43f);
    }
    fn_005c9640((UInt32)(piVar3[5]));
    if (*piVar3 == 0) {
      fn_005c97a0((SInt32)(0));
    }
    else {
      fn_005c97a0((SInt32)(1));
      fn_004bc510((UInt32 *)(*piVar3));
      fn_005c9640((UInt32)(piVar3[1]));
      fn_005c9640((UInt32)(piVar3[2]));
    }
    if (piVar3[3] == 0) {
      fn_005c97a0((SInt32)(0));
    }
    else {
      fn_005c97a0((SInt32)(1));
      fn_005c95e0((UInt32)(piVar3[3]),(UInt32)(piVar3[5]));
    }
    iVar4 = 0;
    puVar1 = (UInt32 *)piVar3[4];
    for (puVar2 = puVar1; puVar2 != (UInt32 *)0x0; puVar2 = (UInt32 *)*puVar2) {
      iVar4 = iVar4 + 1;
    }
    fn_005c9640((UInt32)(iVar4));
    for (; puVar1 != (UInt32 *)0x0; puVar1 = (UInt32 *)*puVar1) {
      iVar4 = puVar1[1];
      if ((iVar4 == 0) || (*(int *)(iVar4 + 0x1c) == 0)) {
        CError_Internal(filename, 0x1d9);
      }
      fn_005c9640((UInt32)(*(UInt32 *)(*(int *)(iVar4 + 0x1c) + 0x18)));
      fn_005c96d0((SInt32)(puVar1[2]));
      fn_005c96d0((SInt32)(puVar1[3]));
    }
    fn_005c97a0((SInt32)((int)(char)piVar3[6]));
  }
  fn_005c95e0((UInt32)(param_1 + 0x58),(UInt32)(2));
  return;
}

/* Import function data, pointer-to-member thunk data or packed IR according to native flags. */
UInt8 * fn_004bbc90(UInt32 param_1, int param_2, UInt32 param_3, UInt32 param_4)
{
  UInt32 uVar1;
  int *piVar2;
  UInt8 *puVar3;
  UInt32 *puVar4;
  int local_10;
  uVar1 = fn_005c9340((UInt32)(param_1),(void *)(param_2 + 0x44));
  if ((*(UInt32 *)(*(int *)(param_2 + 0x10) + 0x16) & 0x200) == 0) {
    if ((*(UInt32 *)(param_2 + 0x14) & 0x800000) == 0) {
      uVar1 = (UInt32)fn_004bbeb0((UInt32)(uVar1),(int *)(param_3),(UInt8 *)(param_4));
    }
    else {
      piVar2 = (int *)galloc(0x10);
      memclrw((void *)(piVar2),(UInt32)(0x10));
      *(int **)(param_2 + 0x40) = piVar2;
      uVar1 = fn_005c9600((UInt32)(uVar1),(void *)(&local_10));
      *piVar2 = *(int *)(fn_006dcb1a + local_10 * 8);
      if (*piVar2 == 0) {
        puVar4 = (UInt32 *)CompilerTools_AllocatePool(8);
        *puVar4 = *(UInt32 *)(fn_006dcb1a + 4 + local_10 * 8);
        puVar4[1] = (UInt32)piVar2;
        *(UInt32 **)(fn_006dcb1a + 4 + local_10 * 8) = puVar4;
      }
      uVar1 = fn_005c9690((UInt32)(uVar1),(void *)(piVar2 + 1));
      uVar1 = fn_005c9690((UInt32)(uVar1),(void *)(piVar2 + 2));
      uVar1 = fn_005c9690((UInt32)(uVar1),(void *)(piVar2 + 3));
    }
  }
  else {
    uVar1 = fn_005c9690((UInt32)(uVar1),(void *)(param_2 + 0x40));
  }
  puVar3 = (UInt8 *)fn_005c9720((UInt32)(uVar1),(void *)(param_2 + 0x5c));
  *(UInt8 *)(param_2 + 0x5e) = *puVar3;
  return puVar3 + 1;
}

/* Export function data, pointer-to-member thunk data or packed IR according to native flags. */
void fn_004bbd90(int param_1)
{
  int iVar1;
  int *piVar2;
  UInt32 uVar3;
  if (*(int *)(param_1 + 0x44) == 0) {
    CError_Internal(filename, 0x39b);
  }
  if (**(char **)(param_1 + 0x10) != '\a') {
    CError_Internal(filename, 0x39c);
  }
  fn_005c93e0((UInt32)(*(UInt32 *)(param_1 + 0x44)));
  if ((*(UInt32 *)(*(int *)(param_1 + 0x10) + 0x16) & 0x200) == 0) {
    if ((*(UInt32 *)(param_1 + 0x14) & 0x800000) == 0) {
      uVar3 = fn_0047d080((UInt32)(param_1));
      fn_004bc0f0((int *)(uVar3));
    }
    else {
      piVar2 = (int *)fn_0047ce20((UInt32)(param_1));
      if (piVar2 == (int *)0x0) {
        CError_Internal(filename, 0x3ac);
      }
      iVar1 = *piVar2;
      if ((iVar1 == 0) || (*(int *)(iVar1 + 0x1c) == 0)) {
        CError_Internal(filename, 0x1d9);
      }
      fn_005c9640((UInt32)(*(UInt32 *)(*(int *)(iVar1 + 0x1c) + 0x18)));
      fn_005c96d0((SInt32)(piVar2[1]));
      fn_005c96d0((SInt32)(piVar2[2]));
      fn_005c96d0((SInt32)(piVar2[3]));
    }
  }
  else {
    fn_005c96d0((SInt32)(*(UInt32 *)(param_1 + 0x40)));
  }
  fn_005c9740((UInt16)(*(UInt16 *)(param_1 + 0x5c)));
  fn_005c97a0((SInt32)((int)*(char *)(param_1 + 0x5e)));
  return;
}

/* Import packed IR bytes, register state and typed/object/source-file/name relocations. */
UInt8 * fn_004bbeb0(UInt32 param_1, int *param_2, UInt8 *param_3)
{
  UInt8 *puVar1;
  UInt32 uVar2;
  UInt32 *puVar3;
  UInt32 uVar4;
  UInt32 *puVar5;
  UInt32 uVar6;
  int *piVar7;
  int local_20;
  UInt32 local_1c;
  int local_18;
  int local_14;
  puVar1 = (UInt8 *)fn_005c9600((UInt32)(param_1),(void *)(&local_18));
  if (local_18 == 0) {
    return puVar1;
  }
  *param_3 = 1;
  uVar2 = fn_005c9600((UInt32)(puVar1),(void *)(param_2 + 2));
  puVar1 = (UInt8 *)fn_005c95c0((UInt32)(uVar2),(void *)(param_2 + 3),(UInt32)(0xb6));
  *(UInt8 *)((int)param_2 + 0xc2) = *puVar1;
  *(UInt8 *)((int)param_2 + 0xc3) = puVar1[1];
  *(UInt8 *)(param_2 + 0x31) = 1;
  uVar2 = fn_005c9600((UInt32)(puVar1 + 2),(void *)(&local_1c));
  puVar3 = (UInt32 *)fn_0046c800((UInt32)(local_1c * 8 + 0x1a));
  memclrw((void *)(puVar3),(UInt32)(0x1a));
  *param_2 = (int)puVar3;
  uVar4 = fn_0046c800((UInt32)(local_18));
  *puVar3 = uVar4;
  puVar3[1] = local_18;
  puVar3[5] = local_1c;
  uVar2 = fn_005c95c0((UInt32)(uVar2),(void *)(*puVar3),(UInt32)(local_18));
  uVar2 = fn_005c9600((UInt32)(uVar2),(void *)(puVar3 + 2));
  uVar2 = fn_005c9600((UInt32)(uVar2),(void *)(puVar3 + 3));
  puVar1 = (UInt8 *)fn_005c9600((UInt32)(uVar2),(void *)(puVar3 + 4));
  *(UInt8 *)(puVar3 + 6) = 1;
  uVar6 = 0;
  if (local_1c != 0) {
    local_14 = 0;
    do {
      puVar1 = (UInt8 *)fn_005c9720((UInt32)(puVar1),(void *)(*param_2 + 0x20 + local_14));
      *(UInt8 *)(*param_2 + 0x1f + uVar6 * 8) = *puVar1;
      *(UInt8 *)((int)puVar3 + uVar6 * 8 + 0x1e) = puVar1[1];
      puVar1 = puVar1 + 2;
      switch(*(UInt8 *)((int)puVar3 + uVar6 * 8 + 0x1e)) {
      case 0:
        puVar1 = (UInt8 *)fn_005c97c0((UInt32)(puVar1),(void *)(*param_2 + 0x1a + local_14));
        break;
      case 1:
        piVar7 = (int *)(*param_2 + 0x1a + local_14);
        puVar1 = (UInt8 *)fn_005c9600((UInt32)(puVar1),(void *)(&local_20));
        *piVar7 = *(int *)(fn_006dcb1a + local_20 * 8);
        if (*piVar7 == 0) {
          puVar5 = (UInt32 *)CompilerTools_AllocatePool(8);
          *puVar5 = *(UInt32 *)(fn_006dcb1a + 4 + local_20 * 8);
          puVar5[1] = (UInt32)piVar7;
          *(UInt32 **)(fn_006dcb1a + 4 + local_20 * 8) = puVar5;
        }
        break;
      case 2:
        puVar1 = (UInt8 *)fn_004bc2a0((UInt32)(puVar1),(int *)(*param_2 + 0x1a + local_14));
        break;
      case 3:
        uVar2 = 0x20e;
        goto LAB_004bc09d;
      case 4:
        puVar1 = (UInt8 *)fn_005c9340((UInt32)(puVar1),(void *)(*param_2 + 0x1a + local_14));
        break;
      default:
        uVar2 = 0x38d;
LAB_004bc09d:
        CError_Internal(filename, uVar2);
      }
      uVar6 = uVar6 + 1;
      local_14 = local_14 + 8;
    } while (uVar6 < local_1c);
  }
  return puVar1;
}

/* Export packed IR and relocations, restoring the temporarily cleared function field afterward. */
void fn_004bc0f0(int *param_1)
{
  int iVar1;
  int iVar2;
  UInt32 uVar3;
  if (param_1 == (int *)0x0) {
    fn_005c9640((UInt32)(0));
    return;
  }
  iVar1 = param_1[1];
  param_1[1] = 0;
  if ((*param_1 == 0) || (*(int *)(*param_1 + 4) == 0)) {
    CError_Internal(filename, 0x309);
  }
  fn_005c9640((UInt32)(*(UInt32 *)(*param_1 + 4)));
  fn_005c9640((UInt32)(param_1[2]));
  fn_005c95e0((UInt32)(param_1 + 3),(UInt32)(0xb6));
  fn_005c97a0((SInt32)((int)*(char *)((int)param_1 + 0xc2)));
  fn_005c97a0((SInt32)((int)*(char *)((int)param_1 + 0xc3)));
  fn_005c9640((UInt32)(*(UInt32 *)(*param_1 + 0x14)));
  fn_005c95e0((UInt32)(*(UInt32 *)*param_1),(UInt32)(((UInt32 *)*param_1)[1]));
  fn_005c9640((UInt32)(*(UInt32 *)(*param_1 + 8)));
  fn_005c9640((UInt32)(*(UInt32 *)(*param_1 + 0xc)));
  fn_005c9640((UInt32)(*(UInt32 *)(*param_1 + 0x10)));
  iVar2 = *param_1;
  uVar3 = 0;
  if (*(int *)(iVar2 + 0x14) != 0) {
    do {
      fn_005c9740((UInt16)(*(UInt16 *)(iVar2 + 0x20 + uVar3 * 8)));
      fn_005c97a0((SInt32)((int)*(char *)(*param_1 + 0x1f + uVar3 * 8)));
      fn_005c97a0((SInt32)((int)*(char *)(*param_1 + 0x1e + uVar3 * 8)));
      iVar2 = *param_1;
      switch(*(UInt8 *)(iVar2 + 0x1e + uVar3 * 8)) {
      case 0:
        fn_005c9cd0((UInt32)(*(UInt32 *)(iVar2 + 0x1a + uVar3 * 8)));
        break;
      case 1:
        iVar2 = *(int *)(iVar2 + 0x1a + uVar3 * 8);
        if ((iVar2 == 0) || (*(int *)(iVar2 + 0x1c) == 0)) {
          CError_Internal(filename, 0x1d9);
        }
        fn_005c9640((UInt32)(*(UInt32 *)(*(int *)(iVar2 + 0x1c) + 0x18)));
        break;
      case 2:
        fn_004bc510((UInt32 *)(*(UInt32 *)(iVar2 + 0x1a + uVar3 * 8)));
        break;
      case 3:
        CError_Internal(filename, 0x1fe);
        break;
      case 4:
        fn_005c93e0((UInt32)(*(UInt32 *)(iVar2 + 0x1a + uVar3 * 8)));
        break;
      default:
        CError_Internal(filename, 0x33a);
      }
      uVar3 = uVar3 + 1;
      iVar2 = *param_1;
    } while (uVar3 < *(UInt32 *)(iVar2 + 0x14));
  }
  param_1[1] = iVar1;
  return;
}

/* Import or reference a 52-byte source-file record, registering it before recursive children. */
UInt8 * fn_004bc2a0(UInt32 param_1, int *param_2)
{
  UInt8 *pbVar1;
  int iVar2;
  UInt32 *puVar3;
  UInt8 *puVar4;
  char *pcVar5;
  char *pcVar6;
  UInt32 uVar7;
  int iVar8;
  UInt8 *pbVar9;
  int local_10;
  pbVar1 = (UInt8 *)fn_005c9600((UInt32)(param_1),(void *)(&local_10));
  puVar3 = fn_006dcb22;
  if (local_10 == 0) {
    iVar2 = galloc(0x34);
    memclrw((void *)(iVar2),(UInt32)(0x34));
    puVar3 = (UInt32 *)CompilerTools_AllocatePool(0xc);
    *puVar3 = (UInt32)fn_006dcb22;
    puVar3[1] = iVar2;
    fn_006dcb1e = fn_006dcb1e + 1;
    puVar3[2] = fn_006dcb1e;
    fn_006dcb22 = puVar3;
    *param_2 = iVar2;
    puVar4 = (UInt8 *)fn_005c9340((UInt32)(pbVar1),(void *)(iVar2));
    *(UInt8 *)(iVar2 + 8) = *puVar4;
    *(UInt8 *)(iVar2 + 9) = puVar4[1];
    pbVar1 = puVar4 + 2;
    switch(*(UInt8 *)(iVar2 + 8)) {
    case 0:
      uVar7 = galloc(0x104);
      *(UInt32 *)(iVar2 + 0x16) = uVar7;
      uVar7 = fn_005c95c0((UInt32)(pbVar1),(void *)(*(UInt32 *)(iVar2 + 0x16)),(UInt32)(0x104));
      uVar7 = fn_005c9760((UInt32)(uVar7),(void *)(iVar2 + 0x1c));
      pcVar5 = (char *)fn_005c95c0((UInt32)(uVar7),(void *)(iVar2 + 0x1e),(UInt32)(8));
      pbVar9 = (UInt8 *)(pcVar5 + 1);
      if (*pcVar5 != '\0') {
        iVar8 = galloc(0x12);
        memclrw((void *)(iVar8),(UInt32)(0x12));
        *(int *)(iVar2 + 0x2a) = iVar8;
        pcVar5 = pcVar5 + 2;
        if (*pbVar9 != 0) {
          pcVar5 = (char *)fn_004bc2a0((UInt32)(pcVar5),(int *)(iVar8));
        }
        puVar4 = (UInt8 *)fn_005c9340((UInt32)(pcVar5),(void *)(iVar8 + 4));
        *(UInt8 *)(iVar8 + 0xe) = *puVar4;
        *(UInt8 *)(iVar8 + 0xf) = puVar4[1];
        pbVar9 = puVar4 + 2;
        *(UInt8 *)(iVar8 + 0x10) = 1;
      }
      *(UInt8 *)(iVar2 + 0x32) = *(UInt8 *)(iVar2 + 0x32) & 0xfe;
      *(UInt8 *)(iVar2 + 0x32) = *(UInt8 *)(iVar2 + 0x32) & 0xfd | (*pbVar9 & 1) * '\x02';
      *(UInt8 *)(iVar2 + 0x32) = *(UInt8 *)(iVar2 + 0x32) & 0xfb;
      pbVar1 = pbVar9 + 2;
      *(UInt8 *)(iVar2 + 0x32) = *(UInt8 *)(iVar2 + 0x32) & 0xf7 | (pbVar9[1] & 1) << 3;
      break;
    case 1:
      puVar4 = puVar4 + 3;
      if (*pbVar1 != 0) {
        puVar4 = (UInt8 *)fn_004bc2a0((UInt32)(puVar4),(int *)(iVar2 + 0x16));
      }
      uVar7 = fn_005c9600((UInt32)(puVar4),(void *)(iVar2 + 0x1a));
      pcVar5 = (char *)fn_005c9600((UInt32)(uVar7),(void *)(iVar2 + 0x1e));
      pcVar6 = pcVar5 + 1;
      if (*pcVar5 != '\0') {
        pcVar6 = (char *)fn_004bc2a0((UInt32)(pcVar6),(int *)(iVar2 + 0x22));
      }
      uVar7 = fn_005c9600((UInt32)(pcVar6),(void *)(iVar2 + 0x2a));
      pbVar1 = (UInt8 *)fn_005c9600((UInt32)(uVar7),(void *)(iVar2 + 0x26));
      break;
    case 2:
      puVar4 = puVar4 + 3;
      if (*pbVar1 != 0) {
        puVar4 = (UInt8 *)fn_004bc2a0((UInt32)(puVar4),(int *)(iVar2 + 0x16));
      }
      uVar7 = fn_005c9600((UInt32)(puVar4),(void *)(iVar2 + 0x1a));
      pbVar1 = (UInt8 *)fn_005c9600((UInt32)(uVar7),(void *)(iVar2 + 0x1e));
      break;
    default:
      CError_Internal(filename, 0x2e6);
    }
    fn_0044b8f0((UInt32)(iVar2));
    return pbVar1;
  }
  while( 1 ) {
    if (puVar3 == (UInt32 *)0x0) {
      CError_Internal(filename, 0x293);
    }
    if (puVar3[2] == local_10) break;
    puVar3 = (UInt32 *)*puVar3;
  }
  *param_2 = puVar3[1];
  return pbVar1;
}

/* Export or reference a source-file record through the private index cache. */
void fn_004bc510(UInt32 *param_1)
{
  UInt32 *puVar1;
  puVar1 = fn_006dcb22;
  if (param_1 == (UInt32 *)0x0) {
    CError_Internal(filename, 0x21c);
    puVar1 = fn_006dcb22;
  }
  while( 1 ) {
    if (puVar1 == (UInt32 *)0x0) {
      puVar1 = (UInt32 *)CompilerTools_AllocatePool(0xc);
      *puVar1 = (UInt32)fn_006dcb22;
      puVar1[1] = (UInt32)param_1;
      fn_006dcb1e = fn_006dcb1e + 1;
      puVar1[2] = fn_006dcb1e;
      fn_006dcb22 = puVar1;
      fn_005c9640((UInt32)(0));
      fn_005c93e0((UInt32)(*param_1));
      fn_005c97a0((SInt32)((int)*(char *)(param_1 + 2)));
      fn_005c97a0((SInt32)((int)*(char *)((int)param_1 + 9)));
      switch(*(UInt8 *)(param_1 + 2)) {
      case 0:
        if (*(int *)((int)param_1 + 0x16) == 0) {
          CError_Internal(filename, 0x23c);
        }
        fn_005c95e0((UInt32)(*(UInt32 *)((int)param_1 + 0x16)),(UInt32)(0x104));
        fn_005c9780((SInt16)((int)*(short *)(param_1 + 7)));
        fn_005c95e0((UInt32)((int)param_1 + 0x1e),(UInt32)(8));
        if (*(int *)((int)param_1 + 0x2a) == 0) {
          fn_005c97a0((SInt32)(0));
        }
        else {
          fn_005c97a0((SInt32)(1));
          if (**(int **)((int)param_1 + 0x2a) == 0) {
            fn_005c97a0((SInt32)(0));
          }
          else {
            fn_005c97a0((SInt32)(1));
            fn_004bc510((UInt32 *)(**(UInt32 **)((int)param_1 + 0x2a)));
          }
          fn_005c93e0((UInt32)(*(UInt32 *)(*(int *)((int)param_1 + 0x2a) + 4)));
          fn_005c97a0((SInt32)((int)*(char *)(*(int *)((int)param_1 + 0x2a) + 0xe)));
          fn_005c97a0((SInt32)((int)*(char *)(*(int *)((int)param_1 + 0x2a) + 0xf)));
        }
        fn_005c97a0((SInt32)(*(UInt8 *)((int)param_1 + 0x32) >> 1 & 1));
        fn_005c97a0((SInt32)(*(UInt8 *)((int)param_1 + 0x32) >> 3 & 1));
        break;
      case 1:
        if (*(int *)((int)param_1 + 0x16) == 0) {
          fn_005c97a0((SInt32)(0));
        }
        else {
          fn_005c97a0((SInt32)(1));
          fn_004bc510((UInt32 *)(*(UInt32 *)((int)param_1 + 0x16)));
        }
        fn_005c9640((UInt32)(*(UInt32 *)((int)param_1 + 0x1a)));
        fn_005c9640((UInt32)(*(UInt32 *)((int)param_1 + 0x1e)));
        if (*(int *)((int)param_1 + 0x22) == 0) {
          fn_005c97a0((SInt32)(0));
        }
        else {
          fn_005c97a0((SInt32)(1));
          fn_004bc510((UInt32 *)(*(UInt32 *)((int)param_1 + 0x22)));
        }
        fn_005c9640((UInt32)(*(UInt32 *)((int)param_1 + 0x2a)));
        fn_005c9640((UInt32)(*(UInt32 *)((int)param_1 + 0x26)));
        break;
      case 2:
        if (*(int *)((int)param_1 + 0x16) == 0) {
          fn_005c97a0((SInt32)(0));
        }
        else {
          fn_005c97a0((SInt32)(1));
          fn_004bc510((UInt32 *)(*(UInt32 *)((int)param_1 + 0x16)));
        }
        fn_005c9640((UInt32)(*(UInt32 *)((int)param_1 + 0x1a)));
        fn_005c9640((UInt32)(*(UInt32 *)((int)param_1 + 0x1e)));
        break;
      default:
        CError_Internal(filename, 0x27e);
      }
      return;
    }
    if ((UInt32 *)puVar1[1] == param_1) break;
    puVar1 = (UInt32 *)*puVar1;
  }
  fn_005c9640((UInt32)(puVar1[2]));
  return;
}

/* Merge imported declarations or append new objects, preserving graph ownership and source context. */
void fn_004bc780(int param_1, int param_2, int param_3, char param_4)
{
  char *pcVar2;
  UInt8 bVar3;
  int *piVar4;
  int *piVar5;
  char cVar6;
  char cVar7;
  int iVar8;
  UInt32 uVar9;
  UInt32 *puVar10;
  int iVar11;
  int *piVar12;
  char *pcVar13;
  char *pcVar14;
  cVar6 = fn_00452fe0((UInt32)(param_1));
  iVar8 = COptimizer_GetFunctionObject((UInt32)(param_1));
  if (cVar6 == '\0') {
    if (param_4 == '\0') {
      for (puVar10 = (UInt32 *)
                     fn_004eb0d0((UInt32)(*(UInt32 *)(param_1 + 8)),(UInt32)(*(UInt32 *)(param_1 + 0xc)));
          puVar10 != (UInt32 *)0x0; puVar10 = (UInt32 *)*puVar10) {
        pcVar2 = (char *)puVar10[1];
        if (*pcVar2 == '\x05') {
          switch(pcVar2[2]) {
          case '\0':
          case '\x03':
          case '\x04':
            iVar11 = COptimizer_GetFunctionObject((UInt32)(pcVar2));
            if (iVar8 == iVar11) {
              cVar6 = fn_004bcdb0((int)(pcVar2),(int)(param_1));
              if (cVar6 == '\0') {
                fn_00449d60();
                fn_00462e30();
                iVar8 = *(int *)(pcVar2 + 0x1c);
                bVar3 = 0;
                if ((iVar8 != 0) && (*(int *)(iVar8 + 0xc) != 0)) {
                  bVar3 = 1;
                }
                if (bVar3) {
                  pcVar13 = (char *)(*(int *)**(UInt32 **)(iVar8 + 0xc) + 10);
                }
                else {
                  pcVar13 = unknown_file;
                }
                if (fn_00710094 == (UInt32 *)0x0) {
                  pcVar14 = unknown_file;
                }
                else {
                  pcVar14 = (char *)(*(int *)*fn_00710094 + 10);
                }
                CError_Warning(0x2915, param_1, *(UInt32 *)(param_1 + 0x10),
                               *(UInt32 *)(param_1 + 0x14), pcVar14, pcVar2,
                               *(UInt32 *)(pcVar2 + 0x10), *(UInt32 *)(pcVar2 + 0x14),
                               pcVar13);
              }
              iVar8 = *(int *)(pcVar2 + 0x1c);
              if (iVar8 == 0) {
                iVar8 = CCallGraph_AddFunction((UInt32)(pcVar2));
              }
              switch(*(UInt8 *)(iVar8 + 0x1c)) {
              case 1:
                if (param_2 != 0) {
                  fn_0047cf40((UInt32)(pcVar2),(UInt32)(param_2));
                  *(UInt32 **)(iVar8 + 0xc) = fn_00710094;
                  *(UInt32 *)(pcVar2 + 4) = *(UInt32 *)(param_1 + 4);
                  *(UInt32 *)(pcVar2 + 0x10) = *(UInt32 *)(param_1 + 0x10);
                  *(UInt32 *)(pcVar2 + 0x14) = *(UInt32 *)(param_1 + 0x14);
                  *(UInt16 *)(pcVar2 + 0x18) = *(UInt16 *)(param_1 + 0x18);
                  *(UInt16 *)(pcVar2 + 0x1a) = *(UInt16 *)(param_1 + 0x1a);
                }
                break;
              case 2:
                if (param_2 != 0) {
                  CError_Internal(filename, 0x14e);
                }
                *(UInt32 **)(iVar8 + 0xc) = fn_00710094;
                break;
              case 3:
                if (param_2 != 0) {
                  CError_Internal(filename, 0x153);
                }
                cVar6 = fn_005a1780((UInt32)(iVar8));
                if (cVar6 == '\0') {
                  iVar11 = 0;
                  do {
                    *(UInt32 *)(pcVar2 + iVar11) = *(UInt32 *)(iVar11 + param_1);
                    *(UInt32 *)(pcVar2 + iVar11 + 4) = *(UInt32 *)(iVar11 + 4 + param_1);
                    *(UInt32 *)(pcVar2 + iVar11 + 8) = *(UInt32 *)(iVar11 + 8 + param_1);
                    *(UInt32 *)(pcVar2 + iVar11 + 0xc) = *(UInt32 *)(iVar11 + 0xc + param_1)
                    ;
                    iVar11 = iVar11 + 0x10;
                  } while (iVar11 < 0x60);
                  *(int *)(pcVar2 + 0x1c) = iVar8;
                  cVar6 = fn_005a1780((UInt32)(iVar8));
                  if (cVar6 != '\0') {
                    *(UInt32 **)(iVar8 + 0xc) = fn_00710094;
                    *(UInt32 *)(pcVar2 + 4) = *(UInt32 *)(param_1 + 4);
                    *(UInt32 *)(pcVar2 + 0x10) = *(UInt32 *)(param_1 + 0x10);
                    *(UInt32 *)(pcVar2 + 0x14) = *(UInt32 *)(param_1 + 0x14);
                    *(UInt16 *)(pcVar2 + 0x18) = *(UInt16 *)(param_1 + 0x18);
                    *(UInt16 *)(pcVar2 + 0x1a) = *(UInt16 *)(param_1 + 0x1a);
                  }
                }
                break;
              default:
                CError_Internal(filename, 0x167);
              }
              if (*(int *)(fn_006dcb1a + param_3 * 8) != 0) {
                CError_Internal(filename, 0x16b);
              }
              *(char **)(fn_006dcb1a + param_3 * 8) = pcVar2;
              return;
            }
            break;
          default:
            CError_Internal(filename, 0x1a8);
            break;
          case '\x02':
            iVar11 = COptimizer_GetFunctionObject((UInt32)(pcVar2));
            if (iVar8 == iVar11) {
/* Compare imported declaration types, completing unsized array types when compatible. */
              if ((pcVar2[2] == '\x02') && (cVar7 = fn_004bcdb0((int)(pcVar2),(int)(param_1)), cVar7 != '\0') &&
                 (*(int *)(pcVar2 + 0x40) == *(int *)(param_1 + 0x40))) {
                if (*(int *)(fn_006dcb1a + param_3 * 8) != 0) {
                  CError_Internal(filename, 0x184);
                }
                *(char **)(fn_006dcb1a + param_3 * 8) = pcVar2;
                return;
              }
              fn_00449d60();
              fn_00462e30();
              iVar11 = *(int *)(pcVar2 + 0x1c);
              bVar3 = 0;
              if ((iVar11 != 0) && (*(int *)(iVar11 + 0xc) != 0)) {
                bVar3 = 1;
              }
              if (bVar3) {
                pcVar13 = (char *)(*(int *)**(UInt32 **)(iVar11 + 0xc) + 10);
              }
              else {
                pcVar13 = unknown_file;
              }
              if (fn_00710094 == (UInt32 *)0x0) {
                pcVar14 = unknown_file;
              }
              else {
                pcVar14 = (char *)(*(int *)*fn_00710094 + 10);
              }
              CError_ReportError(0x2915, param_1, *(UInt32 *)(param_1 + 0x10),
                                 *(UInt32 *)(param_1 + 0x14), pcVar14, pcVar2,
                                 *(UInt32 *)(pcVar2 + 0x10), *(UInt32 *)(pcVar2 + 0x14),
                                 pcVar13);
            }
            break;
          case '\x05':
            iVar11 = COptimizer_GetFunctionObject((UInt32)(pcVar2));
            if (iVar8 == iVar11) {
              if ((pcVar2[2] == '\x05') && (cVar7 = fn_004bcdb0((int)(pcVar2),(int)(param_1)), cVar7 != '\0') &&
                 (iVar11 = *(int *)(param_1 + 0x44), *(int *)(pcVar2 + 0x44) == iVar11)) {
                iVar11=memcmp(*(void **)(pcVar2+0x40),*(void **)(param_1+0x40),iVar11);
                if (iVar11 == 0) {
                  if (*(int *)(fn_006dcb1a + param_3 * 8) != 0) {
                    CError_Internal(filename, 0x1a0);
                  }
                  *(char **)(fn_006dcb1a + param_3 * 8) = pcVar2;
                  return;
                }
              }
              fn_00449d60();
              fn_00462e30();
              iVar11 = *(int *)(pcVar2 + 0x1c);
              bVar3 = 0;
              if ((iVar11 != 0) && (*(int *)(iVar11 + 0xc) != 0)) {
                bVar3 = 1;
              }
              if (bVar3) {
                pcVar13 = (char *)(*(int *)**(UInt32 **)(iVar11 + 0xc) + 10);
              }
              else {
                pcVar13 = unknown_file;
              }
              if (fn_00710094 == (UInt32 *)0x0) {
                pcVar14 = unknown_file;
              }
              else {
                pcVar14 = (char *)(*(int *)*fn_00710094 + 10);
              }
              CError_ReportError(0x2915, param_1, *(UInt32 *)(param_1 + 0x10),
                                 *(UInt32 *)(param_1 + 0x14), pcVar14, pcVar2,
                                 *(UInt32 *)(pcVar2 + 0x10), *(UInt32 *)(pcVar2 + 0x14),
                                 pcVar13);
            }
          }
        }
      }
    }
  }
  else if (fn_006dcb18 != '\0') {
    uVar9 = fn_00455d40((UInt32)(iVar8 + 10));
    switch(*(UInt8 *)(param_1 + 2)) {
    case 0:
      *(UInt32 *)(param_1 + 0x48) = uVar9;
      break;
    case 3:
    case 4:
      *(UInt32 *)(param_1 + 0x44) = uVar9;
    }
  }
  iVar8 = galloc(0x60);
  iVar11 = 0;
  do {
    *(UInt32 *)(iVar11 + iVar8) = *(UInt32 *)(iVar11 + param_1);
    *(UInt32 *)(iVar11 + 4 + iVar8) = *(UInt32 *)(iVar11 + 4 + param_1);
    *(UInt32 *)(iVar11 + 8 + iVar8) = *(UInt32 *)(iVar11 + 8 + param_1);
    *(UInt32 *)(iVar11 + 0xc + iVar8) = *(UInt32 *)(iVar11 + 0xc + param_1);
    iVar11 = iVar11 + 0x10;
  } while (iVar11 < 0x60);
  if (param_2 != 0) {
    fn_0047cf40((UInt32)(iVar8),(UInt32)(param_2));
  }
  if (cVar6 == '\0') {
    piVar12 = (int *)fn_004eb0d0((UInt32)(*(UInt32 *)(iVar8 + 8)),(UInt32)(*(UInt32 *)(iVar8 + 0xc)));
    if (piVar12 == (int *)0x0) {
      iVar11 = fn_004eaff0((UInt32)(*(UInt32 *)(iVar8 + 8)),(UInt32)(*(UInt32 *)(iVar8 + 0xc)));
    }
    else {
      piVar5 = (int *)*piVar12;
      while (piVar4 = piVar5, piVar4 != (int *)0x0) {
        piVar12 = piVar4;
        piVar5 = (int *)*piVar4;
      }
      iVar11 = galloc(8);
      *piVar12 = iVar11;
      memclrw((void *)(*piVar12),(UInt32)(8));
      iVar11 = *piVar12;
    }
    *(int *)(iVar11 + 4) = iVar8;
  }
  iVar11 = CCallGraph_AddFunction((UInt32)(iVar8));
  *(char *)(iVar11 + 0x1d) = param_4;
  cVar6 = fn_005a1780((UInt32)(iVar11));
  if ((cVar6 != '\0') || (*(int *)(iVar11 + 0xc) == 0)) {
    *(UInt32 **)(iVar11 + 0xc) = fn_00710094;
  }
  if (*(int *)(fn_006dcb1a + param_3 * 8) != 0) {
    CError_Internal(filename, 0x1ce);
  }
  *(int *)(fn_006dcb1a + param_3 * 8) = iVar8;
  return;
}

UInt8 fn_004bcdb0(int param_1, int param_2)
{
  char cVar1;
  char *pcVar2;
  short sVar3;
  if ((*(char *)(param_1 + 2) != *(char *)(param_2 + 2)) ||
     (**(char **)(param_1 + 0x10) != **(char **)(param_2 + 0x10))) {
    return 0;
  }
  sVar3 = iscpp_typeequal(*(UInt32 *)(param_1 + 0x10), *(UInt32 *)(param_2 + 0x10));
  if (sVar3 != 0) {
    return 1;
  }
  pcVar2 = *(char **)(param_1 + 0x10);
  cVar1 = *pcVar2;
  if ((cVar1 == '\x05') && (*(int *)(pcVar2 + 2) == *(int *)(*(int *)(param_2 + 0x10) + 2)) &&
     (*(int *)(pcVar2 + 6) == 0) && (*(int *)(pcVar2 + 10) == 0)) {
    return 1;
  }
  if ((cVar1 == '\x06') && (*(int *)(pcVar2 + 2) == *(int *)(*(int *)(param_2 + 0x10) + 2)) &&
     ((*(UInt32 *)(pcVar2 + 0x22) & 4) != 0 &&
     (*(int *)(pcVar2 + 10) == 0 && (*(int *)(pcVar2 + 0x16) == 0)))) {
    return 1;
  }
  if ((cVar1 == '\r') &&
     ((*(int *)(pcVar2 + 2) == 0 || (*(int *)(*(int *)(param_2 + 0x10) + 2) == 0)) &&
     (sVar3 = iscpp_typeequal(*(UInt32 *)(pcVar2 + 6),
                              *(UInt32 *)(*(int *)(param_2 + 0x10) + 6)), sVar3 != 0))) {
    if (*(int *)(*(int *)(param_1 + 0x10) + 2) == 0) {
      *(UInt32 *)(param_1 + 0x10) = *(UInt32 *)(param_2 + 0x10);
    }
    else {
      *(int *)(param_2 + 0x10) = *(int *)(param_1 + 0x10);
    }
    return 1;
  }
  return 0;
}
