/* Native Windows IroType.c full body attempt. Private offsets remain explicit
 * while shared type and IR headers still describe the older ABI. */
#include "compiler/common.h"
typedef UInt8 bool;
typedef long long SInt64;
enum {false=0,true=1};
static char filename[]="IroType.c";
extern UInt8 is_unsigned(void *);
extern SInt16 fn_00454c20(void *,void *);
extern UInt8 fn_005b07f0(void *),CMachine_FunctionRequiresMemoryReturn(void *);
extern int fn_005ac9f0(void *,void *),fn_004c07c0(void);
extern void CError_Internal(const char *,SInt32);
extern void *galloc(SInt32),*CTTool_CopyTypePointer(void *);
extern SInt64 CInt64_And(UInt32,UInt32,UInt32,UInt32),CExpr2_BitwiseOrCInt64(UInt32,UInt32,UInt32,UInt32);
extern UInt8 CInt64_Equal(UInt32,UInt32,UInt32,UInt32);
extern void CExpr2_SignExtendSignedChar(void *),CExpr2_SignExtendShort(void *),CExpr2_SignExtendCInt64(void *),CExpr2_ConvertCInt64ToUInt8(void *),CExpr2_ConvertCInt64ToUnsignedShort(void *),CExpr2_ClearCInt64Hi(void *);
extern char *DAT_00710170;
extern UInt32 DAT_007107e8;
extern UInt8 DAT_00725f47,DAT_0070f268,DAT_0070f269,DAT_0070f26a,DAT_0070f26b,DAT_0070f1a8,DAT_0070f1bc;
extern UInt32 DAT_00710998;
extern char *fn_005bd630(SInt32),*CABI_GetPtrDiffTType(void);
extern void fn_005ad400(char*,char*,char*),fn_005ad220(char*,void*);
extern CInt64 native_one,native_zero,native_minus_one;
extern CInt64 CInt64_Shl(CInt64,CInt64),CInt64_Sub(CInt64,CInt64);
extern UInt8 CInt64_NotEqual(CInt64,CInt64);
static inline CInt64 native_and(CInt64 a,CInt64 b){union{SInt64 raw;CInt64 words;}v;v.raw=CInt64_And(a.hi,a.lo,b.hi,b.lo);return v.words;}
static inline CInt64 native_or(CInt64 a,CInt64 b){union{SInt64 raw;CInt64 words;}v;v.raw=CExpr2_BitwiseOrCInt64(a.hi,a.lo,b.hi,b.lo);return v.words;}
static inline void copy_native_ir(char *target,char *source){SInt32 i=0;do{*(UInt32*)(target+i)=*(UInt32*)(source+i);*(UInt32*)(target+i+4)=*(UInt32*)(source+i+4);*(UInt32*)(target+i+8)=*(UInt32*)(source+i+8);*(UInt32*)(target+i+12)=*(UInt32*)(source+i+12);i+=16;}while(i<64);*(UInt16*)(target+64)=*(UInt16*)(source+64);}
extern char DAT_00699c1c;
extern char DAT_00699c24;
extern char DAT_00699c2c;
extern SInt32 DAT_00699c2e;
extern char DAT_00699c34;
extern SInt32 DAT_00699c36;
extern char DAT_00699c3c;
extern char DAT_00699c44;
extern SInt32 DAT_00699c46;
extern char DAT_00699c4c;
extern SInt32 DAT_00699c4e;
extern char DAT_00699c54;
extern SInt32 DAT_00699c56;
extern char DAT_00699c5c;
extern SInt32 DAT_00699c5e;
extern char DAT_00699c64;
extern SInt32 DAT_00699c66;
extern char DAT_00699c6c;
extern SInt32 DAT_00699c6e;
extern char DAT_00699c74;
extern SInt32 DAT_00699c76;
extern char DAT_00699c7c;
extern SInt32 DAT_00699c7e;

extern UInt8 fn_005b5500(char *node);
extern char *fn_005b5580(char *node,char *type,void *list);
extern char *fn_005b5730(char *type);
extern char *fn_005b5760(void);
extern char *fn_005b5770(void);
extern CInt64 fn_005b5780(char *type);
extern CInt64 fn_005b5820(char *type);
extern void fn_005b58b0(CInt64 *value,char *type,char *bitfield);
extern void fn_005b5a50(UInt32 value,int type);
extern void fn_005b5fb0(char *param_1, int param_2, char param_3);
extern void fn_005b61f0(void);
extern void fn_005b6390(char *param_1);
extern char fn_005b6800(char *param_1, char *param_2, char param_3);
extern void fn_005b7230(int param_1, UInt32 param_2);
extern void fn_005b7580(int param_1, UInt32 param_2);
extern bool fn_005b7980(char *param_1, char *param_2);
extern char * fn_005b7af0(void);
extern char * fn_005b7b10(char *param_1);
extern char * fn_005b7c20(char *param_1);
extern UInt32 * fn_005b7d30(UInt32 *param_1);
extern bool fn_005b7e20(char *left,char *right);
UInt8 fn_005b5500(char *node)
{
 char *source=*(char **)(*(char **)(node+42)+18),*target=*(char **)(node+18);
 SInt32 sourceSize,targetSize;UInt8 sourceUnsigned,targetUnsigned;
 if(source[0]!=1 || (UInt8)source[6]>=23 || target[0]!=1 || (UInt8)target[6]>=23)return 0;
 sourceSize=*(SInt32*)(source+2);targetSize=*(SInt32*)(target+2);
 sourceUnsigned=is_unsigned((void*)(source));targetUnsigned=is_unsigned((void*)(target));
 if(sourceUnsigned==targetUnsigned && targetSize>=sourceSize)return 1;
 if(sourceUnsigned==1 && !targetUnsigned && targetSize>sourceSize)return 1;
 return 0;
}
char *fn_005b5580(char *node,char *type,void *list)
{
 char *first,*last;
 if(type[0]==1 && type[6]==0) {
  first=fn_005bd630(2);copy_native_ir(first,node);first[0]=2;first[1]=7;
  *(UInt32*)(first+10)=DAT_00710998++;*(char**)(first+18)=type;*(char**)(first+42)=node;
  last=fn_005bd630(2);*(char**)(first+62)=last;copy_native_ir(last,node);last[0]=2;last[1]=7;
  *(UInt32*)(last+10)=DAT_00710998++;*(char**)(last+18)=type;*(char**)(last+42)=first;*(char**)(last+62)=0;
  if(!list)fn_005ad400(first,last,node);else fn_005ad220(first,list);
 }else {
  last=fn_005bd630(2);copy_native_ir(last,node);last[0]=2;last[1]=50;
  *(UInt32*)(last+10)=DAT_00710998++;*(char**)(last+18)=type;*(char**)(last+42)=node;*(char**)(last+62)=0;
  if(fn_005b5500(last) && node[1]==50 && fn_005b5500(node)){*(char**)(node+18)=type;return node;}
  if(!list)fn_005ad400(last,last,node);else fn_005ad220(last,list);
 }
 return last;
}
char *fn_005b5730(char *type)
{
 if(type[0]==4)type=*(char**)(type+14);
 if((UInt8)type[6]>=7)return type;
 if(is_unsigned((void*)(type)))return &DAT_00699c5c;
 return &DAT_00699c54;
}
char *fn_005b5760(void)
{
 return &DAT_00699c6c;
}
char *fn_005b5770(void)
{
 return CABI_GetPtrDiffTType();
}
CInt64 fn_005b5780(char *type)
{
 CInt64 value,count;
 if(!is_unsigned((void*)(type))) {
  count.lo=*(SInt32*)(type+2)*8-1;count.hi=(SInt32)count.lo<0?-1:0;
  value=CInt64_Sub(CInt64_Shl(native_one,count),native_one);
 }else value=native_minus_one;
 fn_005b5a50((UInt32)((UInt32)&value),(int)((int)type));
 return value;
}
CInt64 fn_005b5820(char *type)
{
 CInt64 value,count;
 if(!is_unsigned((void*)(type))) {
  count.lo=*(SInt32*)(type+2)*8-1;count.hi=(SInt32)count.lo<0?-1:0;
  value=CInt64_Shl(native_one,count);fn_005b5a50((UInt32)((UInt32)&value),(int)((int)type));
 }else value=native_zero;
 return value;
}
void fn_005b58b0(CInt64 *value,char *type,char *bitfield)
{
 CInt64 mask=native_zero,count=native_zero,shift=native_zero;UInt32 width=0,bit;
 if((UInt8)bitfield[11])do {
  shift.lo=width;count=CInt64_Shl(native_one,shift);mask=native_or(mask,count);++width;count=mask;
 }while(width<(UInt8)bitfield[11]);
 *value=native_and(*value,count);
 if(!is_unsigned((void*)(type))) {
  mask=native_zero;bit=0;
  do {if(bit==width-1){shift.lo=bit;mask=native_or(mask,CInt64_Shl(native_one,shift));}++bit;}while(bit<=width-1);
  if(CInt64_NotEqual(native_and(mask,*value),native_zero))for(bit=width-1;bit<64;++bit){shift.lo=bit;*value=native_or(*value,CInt64_Shl(native_one,shift));}
 }
 fn_005b5a50((UInt32)((UInt32)value),(int)((int)type));
}


void fn_005b5a50(UInt32 value,int type)
{
 if(is_unsigned((void*)((void*)type))) {
  switch(*(UInt32*)(type+2)) {
  case 1:CExpr2_ConvertCInt64ToUInt8((void*)((void*)value));break;
  case 2:CExpr2_ConvertCInt64ToUnsignedShort((void*)((void*)value));break;
  case 4:CExpr2_ClearCInt64Hi((void*)((void*)value));break;
  case 8:break;
  }
 }else {
  switch(*(UInt32*)(type+2)) {
  case 1:CExpr2_SignExtendSignedChar((void*)((void*)value));break;
  case 2:CExpr2_SignExtendShort((void*)((void*)value));break;
  case 4:CExpr2_SignExtendCInt64((void*)((void*)value));break;
  case 8:break;
  }
 }
}




void fn_005b5fb0(char *param_1, int param_2, char param_3)

{
  char cVar1;
  int iVar2;
  char uVar3;
  SInt64 lVar4;
  
  if (param_3 != '\0') {
    fn_005b61f0();
  }
  for (; param_1 != (char *)0x0 && (param_1 != *(char **)(param_2 + 0x3e));
      param_1 = *(char **)(param_1 + 0x3e)) {
    *(UInt32 *)(param_1 + 0x12) = *(UInt32 *)(param_1 + 0x16);
    if ((*param_1 == '\x02') && (param_1[1] == '2')) {
      if (((*(int *)(param_1 + 0x16) == *(int *)(*(int *)(param_1 + 0x2a) + 0x16)) ||
          (cVar1 = fn_005b7e20((char*)(*(int *)(param_1 + 0x16)),(char*)( *(int *)(*(int *)(param_1 + 0x2a) + 0x16)))
          , cVar1 != '\0')) && ((*(UInt32 *)(param_1 + 6) & 8) == 0) &&
         (iVar2 = fn_005ac9f0((void*)(param_1),(void*)( *(UInt32 *)(param_1 + 0x2a))), iVar2 != 0)) {
        *param_1 = '\0';
        param_1[0x1a] = '\0';
        param_1[0x1b] = '\0';
        param_1[0x1c] = '\0';
        param_1[0x1d] = '\0';
        *(UInt32 *)(param_1 + 2) = *(UInt32 *)(param_1 + 2) & 0xfffffffd;
      }
    }
    else {
      cVar1 = fn_005b07f0((void*)(param_1));
      if (cVar1 != '\0') {
        *(UInt32 *)(*(int *)(param_1 + 0x2a) + 4) = *(UInt32 *)(param_1 + 0x16);
        iVar2 = *(int *)(*(int *)(param_1 + 0x16) + 2);
        if (iVar2 == 1) {
          uVar3 = 0;
        }
        else if (iVar2 == 2) {
          uVar3 = 1;
        }
        else if (iVar2 == 4) {
          uVar3 = 2;
        }
        else if (iVar2 == 8) {
          uVar3 = 3;
        }
        else {
          uVar3 = 0xff;
        }
        switch(uVar3) {
        case 0:
          CInt64_And(*(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x10),
                     *(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x14), 0, 0xff);
          cVar1 = is_unsigned((void*)(*(UInt32 *)(param_1 + 0x16)));
          if ((cVar1 == '\0') &&
             (lVar4 = CInt64_And(0, 0x80, *(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x10),
                                 *(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x14)), lVar4 != 0)) {
            CExpr2_BitwiseOrCInt64
                      (*(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x10),
                       *(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x14), 0xffffffff, 0xffffff00);
          }
          break;
        case 1:
          CInt64_And(*(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x10),
                     *(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x14), 0, 0xffff);
          cVar1 = is_unsigned((void*)(*(UInt32 *)(param_1 + 0x16)));
          if ((cVar1 == '\0') &&
             (lVar4 = CInt64_And(0, 0x8000, *(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x10),
                                 *(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x14)), lVar4 != 0)) {
            CExpr2_BitwiseOrCInt64
                      (*(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x10),
                       *(UInt32 *)(*(int *)(param_1 + 0x2a) + 0x14), 0xffffffff, 0xffff0000);
          }
        }
      }
    }
  }
  return;
}



void fn_005b61f0(void)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  bool bVar4;
  char *puVar5;
  char cVar6;
  char *puVar7;
  
  for (puVar7 = DAT_00710170; puVar5 = DAT_00710170, puVar7 != (char *)0x0;
      puVar7 = *(char **)(puVar7 + 0x3e)) {
    *(UInt32 *)(puVar7 + 0x16) = *(UInt32 *)(puVar7 + 0x12);
  }
  do {
    if (puVar5 == (char *)0x0) {
      return;
    }
    for (puVar7 = *(char **)(puVar5 + 0x3e); puVar7 != (char *)0x0 &&
        ((*(UInt32 *)(puVar7 + 2) & 2) != 0); puVar7 = *(char **)(puVar7 + 0x3e)) {
    }
    switch(*puVar5) {
    case 0:
    case 8:
    case 0xd:
    case 0xf:
    case 0x10:
    case 0x14:
    case 0x17:
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      fn_005b6390((char*)(puVar5));
      break;
    case 9:
      fn_005b6390((char*)(*(UInt32 *)(puVar5 + 0x2a)));
    case 0xc:
      if ((*(int *)(puVar5 + 0x2a) != 0) && (DAT_007107e8 != 0) &&
         (cVar6 = CMachine_FunctionRequiresMemoryReturn((void*)(*(UInt32 *)(DAT_007107e8 + 0x10))),
         cVar6 == '\0' || (cVar6 = fn_005b07f0((void*)(*(UInt32 *)(puVar5 + 0x2a))), cVar6 == '\0'))) {
        iVar1 = *(int *)(puVar5 + 0x2a);
        pcVar2 = *(char **)(iVar1 + 0x16);
        bVar4 = true;
        if ((*pcVar2 != '\x04') && (*pcVar2 != '\x01' || ((byte)pcVar2[6] > 0x16))) {
          bVar4 = false;
        }
        if (bVar4) {
          iVar3 = *(int *)(pcVar2 + 2);
          if (iVar3 == 1) {
            cVar6 = '\0';
          }
          else if (iVar3 == 2) {
            cVar6 = '\x01';
          }
          else if (iVar3 == 4) {
            cVar6 = '\x02';
          }
          else if (iVar3 == 8) {
            cVar6 = '\x03';
          }
          else {
            cVar6 = -1;
          }
          if ((cVar6 > -1) && (cVar6 < '\x03')) {
            fn_005b6800((char*)(pcVar2),(char*)( iVar1),(char)( 1));
          }
          fn_005b6390((char*)(*(UInt32 *)(puVar5 + 0x2a)));
        }
        else {
          fn_005b6390((char*)(iVar1));
        }
      }
      break;
    case 10:
    case 0xb:
      fn_005b6390((char*)(*(UInt32 *)(puVar5 + 0x2e)));
      break;
    case 0xe:
      fn_005b6390((char*)(*(UInt32 *)(puVar5 + 0x2e)));
      break;
    case 0x11:
      fn_005b6390((char*)(*(UInt32 *)(puVar5 + 0x2a)));
      break;
    case 0x12:
      fn_005b6390((char*)(*(UInt32 *)(puVar5 + 0x2a)));
      break;
    case 0x13:
      fn_005b6390((char*)(*(UInt32 *)(puVar5 + 0x2a)));
      break;
    default:
      CError_Internal(filename, 0x536);
    }
    puVar5 = puVar7;
  } while( true );
}



void fn_005b6390(char *param_1)

{
  char *pcVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  char cVar5;
  UInt32 uVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  char *puVar10;
  char local_19;
  
  pcVar1 = *(char **)(param_1 + 0x16);
  iVar9 = *(int *)(pcVar1 + 2);
  if (iVar9 == 1) {
    local_19 = '\0';
  }
  else if (iVar9 == 2) {
    local_19 = '\x01';
  }
  else if (iVar9 == 4) {
    local_19 = '\x02';
  }
  else if (iVar9 == 8) {
    local_19 = '\x03';
  }
  else {
    local_19 = -1;
  }
  cVar4 = *param_1;
  switch(cVar4) {
  case '\x01':
  case '\x05':
    break;
  case '\x02':
    if ((&DAT_00725f47)[(byte)param_1[1]] != '\0') {
      pcVar1 = *(char **)(param_1 + 0x2a);
      pcVar7 = pcVar1;
      if ((*pcVar1 == '\x02') && (pcVar1[1] == '\x04')) {
        pcVar7 = *(char **)(pcVar1 + 0x2a);
      }
      if ((pcVar7[1] == '3') && (*pcVar7 == '\x02')) {
        iVar9 = *(int *)(pcVar1 + 0x2a);
        if (cVar4 == '\x03') {
          fn_005b6390((char*)(*(UInt32 *)(param_1 + 0x2e)));
        }
        fn_005b6390((char*)(*(UInt32 *)(iVar9 + 0x2a)));
        return;
      }
    }
    fn_005b6390((char*)(*(UInt32 *)(param_1 + 0x2a)));
    break;
  case '\x03':
    iVar2 = *(int *)(param_1 + 0x2e);
    pcVar7 = *(char **)(param_1 + 0x2a);
    if ((&DAT_00725f47)[(byte)param_1[1]] != '\0') {
      pcVar8 = pcVar7;
      if ((*pcVar7 == '\x02') && (pcVar7[1] == '\x04')) {
        pcVar8 = *(char **)(pcVar7 + 0x2a);
      }
      if ((pcVar8[1] == '3') && (*pcVar8 == '\x02')) {
        iVar9 = *(int *)(pcVar7 + 0x2a);
        if (cVar4 == '\x03') {
          fn_005b6390((char*)(iVar2));
        }
        fn_005b6390((char*)(*(UInt32 *)(iVar9 + 0x2a)));
        return;
      }
    }
    if ((&DAT_00725f47)[(byte)param_1[1]] != '\0') {
      bVar3 = false;
      if (((byte)(param_1[1] - 0x1eU) < 0xb) && ((1 << (param_1[1] - 0x1eU & 0x1f) & 0x773U) != 0))
      {
        bVar3 = true;
      }
      if (bVar3) {
        bVar3 = true;
        if ((*pcVar1 != '\x04') && (*pcVar1 != '\x01' || ((byte)pcVar1[6] > 0x16))) {
          bVar3 = false;
        }
        if (bVar3) {
          if (local_19 != -1) goto switchD_005b64c9_caseD_3;
          switch(iVar9) {
          case 1:
            local_19 = '\0';
            cVar4 = is_unsigned((void*)(pcVar1));
            cVar5 = is_unsigned((void*)(&DAT_00699c2c));
            if ((cVar4 == '\0') == (cVar5 == '\0')) {
              *(char **)(param_1 + 0x16) = &DAT_00699c2c;
              goto switchD_005b64c9_caseD_3;
            }
            if (cVar4 == '\0') {
              uVar6 = (UInt32)fn_005b7b10((char*)(&DAT_00699c2c));
            }
            else {
              puVar10 = &DAT_00699c2c;
LAB_005b65db:
              uVar6 = (UInt32)fn_005b7c20((char*)(puVar10));
            }
            break;
          case 2:
            local_19 = '\x01';
            cVar4 = is_unsigned((void*)(pcVar1));
            cVar5 = is_unsigned((void*)(&DAT_00699c44));
            if ((cVar4 == '\0') == (cVar5 == '\0')) {
              *(char **)(param_1 + 0x16) = &DAT_00699c44;
              goto switchD_005b64c9_caseD_3;
            }
            if (cVar4 != '\0') {
              puVar10 = &DAT_00699c44;
              goto LAB_005b65db;
            }
            uVar6 = (UInt32)fn_005b7b10((char*)(&DAT_00699c44));
            break;
          default:
            goto switchD_005b64c9_caseD_3;
          case 4:
            local_19 = '\x02';
            cVar4 = is_unsigned((void*)(pcVar1));
            cVar5 = is_unsigned((void*)(&DAT_00699c64));
            if ((cVar4 == '\0') == (cVar5 == '\0')) {
              *(char **)(param_1 + 0x16) = &DAT_00699c64;
              goto switchD_005b64c9_caseD_3;
            }
            if (cVar4 != '\0') {
              puVar10 = &DAT_00699c64;
              goto LAB_005b65db;
            }
            uVar6 = (UInt32)fn_005b7b10((char*)(&DAT_00699c64));
            break;
          case 8:
            local_19 = '\x03';
            cVar4 = is_unsigned((void*)(pcVar1));
            cVar5 = is_unsigned((void*)(&DAT_00699c74));
            if ((cVar4 == '\0') == (cVar5 == '\0')) {
              *(char **)(param_1 + 0x16) = &DAT_00699c74;
              goto switchD_005b64c9_caseD_3;
            }
            if (cVar4 != '\0') {
              puVar10 = &DAT_00699c74;
              goto LAB_005b65db;
            }
            uVar6 = (UInt32)fn_005b7b10((char*)(&DAT_00699c74));
          }
          *(UInt32 *)(param_1 + 0x16) = uVar6;
switchD_005b64c9_caseD_3:
          if ((local_19 > -1) && (local_19 < '\x03')) {
            pcVar1 = *(char **)(pcVar7 + 0x16);
            cVar4 = *pcVar1;
            bVar3 = true;
            if ((cVar4 != '\x04') && (cVar4 != '\x01' || ((byte)pcVar1[6] > 0x16))) {
              bVar3 = false;
            }
            if (bVar3) {
              cVar5 = **(char **)(iVar2 + 0x16);
              bVar3 = true;
              if ((cVar5 != '\x04') &&
                 (cVar5 != '\x01' || ((byte)(*(char **)(iVar2 + 0x16))[6] > 0x16))) {
                bVar3 = false;
              }
              if ((bVar3) && (cVar4 == cVar5) &&
                 (DAT_0070f26a != '\0' || (param_1[1] != '\x1f' || (local_19 != '\0')))) {
                fn_005b6800((char*)(pcVar1),(char*)( iVar2),(char)( 1));
              }
            }
          }
          fn_005b6390((char*)(pcVar7));
          fn_005b6390((char*)(*(UInt32 *)(param_1 + 0x2e)));
          return;
        }
      }
    }
    fn_005b6390((char*)(pcVar7));
    fn_005b6390((char*)(iVar2));
    break;
  case '\x04':
    fn_005b6390((char*)(*(UInt32 *)(param_1 + 0x2a)));
    fn_005b6390((char*)(*(UInt32 *)(param_1 + 0x2e)));
    fn_005b6390((char*)(*(UInt32 *)(param_1 + 0x32)));
    break;
  case '\x06':
    if (*(int *)(param_1 + 0x2c) != 0) {
      fn_005b6390((char*)(*(int *)(param_1 + 0x2c)));
    }
    break;
  case '\a':
    iVar9 = 0;
    if (*(short *)(param_1 + 0x2c) > 0) {
      do {
        fn_005b6390((char*)(*(UInt32 *)(*(int *)(param_1 + 0x2e) + iVar9 * 4)));
        iVar9 = iVar9 + 1;
      } while (iVar9 < *(short *)(param_1 + 0x2c));
    }
    fn_005b6390((char*)(*(UInt32 *)(param_1 + 0x32)));
    break;
  default:
    CError_Internal(filename, 0x4d7);
  }
  return;
}



char fn_005b6800(char *param_1, char *param_2, char param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char cVar8;
  char cVar9;
  UInt32 uVar10;
  int iVar11;
  UInt32 uVar12;
  char *pcVar13;
  bool bVar14;
  bool bVar15;
  char local_32;
  char local_31;
  bool local_19;
  
  local_19 = false;
  iVar11 = *(int *)(param_1 + 2);
  if (iVar11 == 1) {
    local_32 = '\0';
  }
  else if (iVar11 == 2) {
    local_32 = '\x01';
  }
  else if (iVar11 == 4) {
    local_32 = '\x02';
  }
  else if (iVar11 == 8) {
    local_32 = '\x03';
  }
  else {
    local_32 = -1;
  }
  pcVar13 = *(char **)(param_2 + 0x16);
  iVar11 = *(int *)(pcVar13 + 2);
  if (iVar11 == 1) {
    local_31 = '\0';
  }
  else if (iVar11 == 2) {
    local_31 = '\x01';
  }
  else if (iVar11 == 4) {
    local_31 = '\x02';
  }
  else if (iVar11 == 8) {
    local_31 = '\x03';
  }
  else {
    local_31 = -1;
  }
  switch(*param_2) {
  case '\x01':
    switch(**(char **)(param_2 + 0x2a)) {
    case 0x34:
      cVar8 = fn_005b07f0((void*)(param_2));
      if (cVar8 == '\0') {
        return false;
      }
      local_19 = true;
      if (param_3 == '\0') {
        return true;
      }
      cVar8 = is_unsigned((void*)(*(UInt32 *)(param_2 + 0x16)));
      cVar9 = is_unsigned((void*)(param_1));
      if ((cVar8 == '\0') == (cVar9 == '\0')) {
        *(char **)(param_2 + 0x16) = param_1;
        return true;
      }
      if (cVar8 == '\0') {
        uVar10 = (UInt32)fn_005b7b10((char*)(param_1));
      }
      else {
LAB_005b6fa5:
        uVar10 = (UInt32)fn_005b7c20((char*)(param_1));
      }
      break;
    default:
      goto switchD_005b6886_default;
    case 0x3b:
      local_19 = true;
      if (param_3 == '\0') {
        return true;
      }
      cVar8 = is_unsigned((void*)(pcVar13));
      cVar9 = is_unsigned((void*)(param_1));
      if ((cVar8 == '\0') == (cVar9 == '\0')) {
        *(char **)(param_2 + 0x16) = param_1;
        return true;
      }
      if (cVar8 != '\0') goto LAB_005b6fa5;
      uVar10 = (UInt32)fn_005b7b10((char*)(param_1));
    }
    break;
  case '\x02':
    if ((byte)param_2[1] == 4) {
      if (local_31 != local_32) {
        iVar11 = fn_004c07c0();
        if (iVar11 != 0) {
          return false;
        }
        if (local_31 <= local_32) {
          return false;
        }
        pcVar13 = param_2;
        if ((*param_2 == '\x02') && (param_2[1] == '\x04')) {
          pcVar13 = *(char **)(param_2 + 0x2a);
        }
        if ((pcVar13[1] == '3') && (*pcVar13 == '\x02')) {
          return false;
        }
      }
      local_19 = true;
      if (param_3 == '\0') {
        return true;
      }
      cVar8 = is_unsigned((void*)(*(UInt32 *)(param_2 + 0x16)));
      cVar9 = is_unsigned((void*)(param_1));
      if ((cVar8 == '\0') == (cVar9 == '\0')) {
        *(char **)(param_2 + 0x16) = param_1;
        return true;
      }
      if (cVar8 == '\0') {
        uVar10 = (UInt32)fn_005b7b10((char*)(param_1));
      }
      else {
        uVar10 = (UInt32)fn_005b7c20((char*)(param_1));
      }
    }
    else {
      uVar12 = (byte)param_2[1] - 5;
      if (uVar12 > 1) {
        if (uVar12 != 0x2d) {
          return false;
        }
        cVar8 = *param_1;
        pcVar13 = *(char **)(*(int *)(param_2 + 0x2a) + 0x16);
        cVar9 = *pcVar13;
        if (cVar9 != cVar8) {
          if (DAT_0070f269 == '\0') {
            return false;
          }
          bVar14 = cVar8 == '\x04';
          if ((!bVar14) && (bVar14 = false, cVar8 == '\x01')) {
            bVar14 = (byte)param_1[6] < 0x17;
          }
          bVar15 = cVar9 == '\x04';
          if ((!bVar15) && (bVar15 = false, cVar9 == '\x01')) {
            bVar15 = (byte)pcVar13[6] < 0x17;
          }
          if (bVar15 != bVar14) {
            return false;
          }
        }
        if (cVar9 != '\x04') {
          bVar14 = false;
          if (cVar9 == '\x01') {
            bVar14 = (byte)pcVar13[6] < 0x17;
          }
          if (!bVar14) {
            return local_31 <= local_32;
          }
        }
        if (param_3 == '\0') {
          return true;
        }
        if (local_31 < local_32) {
          return true;
        }
        fn_005b6800((char*)(param_1),(char*)( *(int *)(param_2 + 0x2a)),(char)( param_3));
        cVar8 = is_unsigned((void*)(*(UInt32 *)(param_2 + 0x16)));
        cVar9 = is_unsigned((void*)(param_1));
        if ((cVar8 == '\0') == (cVar9 == '\0')) {
          *(char **)(param_2 + 0x16) = param_1;
        }
        else {
          if (cVar8 == '\0') {
            uVar10 = (UInt32)fn_005b7b10((char*)(param_1));
          }
          else {
            uVar10 = (UInt32)fn_005b7c20((char*)(param_1));
          }
          *(UInt32 *)(param_2 + 0x16) = uVar10;
        }
        fn_005b7580((int)(param_2),(UInt32)( param_1));
        fn_005b7230((int)(param_2),(UInt32)( param_1));
        return true;
      }
      pcVar7 = *(char **)(*(int *)(param_2 + 0x2a) + 0x16);
      cVar8 = *pcVar7;
      bVar14 = true;
      if ((cVar8 != '\x04') && (cVar8 != '\x01' || ((byte)pcVar7[6] > 0x16))) {
        bVar14 = false;
      }
      if (!bVar14) {
        return false;
      }
      if (local_31 < local_32) {
        param_1 = pcVar13;
      }
      if (*param_1 != cVar8) {
        return false;
      }
      local_19 = (bool)fn_005b6800((char*)(param_1),(char*)( *(int *)(param_2 + 0x2a)),(char)( param_3));
      if (local_19 == false) {
        return false;
      }
      if (param_3 == '\0') {
        return local_19;
      }
      param_1 = *(char **)(*(int *)(param_2 + 0x2a) + 0x16);
      cVar8 = is_unsigned((void*)(*(UInt32 *)(param_2 + 0x16)));
      cVar9 = is_unsigned((void*)(param_1));
      if ((cVar8 == '\0') == (cVar9 == '\0')) {
        *(char **)(param_2 + 0x16) = param_1;
        return local_19;
      }
      if (cVar8 != '\0') goto LAB_005b6fa5;
      uVar10 = (UInt32)fn_005b7b10((char*)(param_1));
    }
    break;
  case '\x03':
    switch(param_2[1]) {
    case '\t':
    case '\x0f':
    case '\x10':
    case '\x11':
    case '\x19':
    case '\x1a':
    case '\x1b':
      goto switchD_005b689d_caseD_9;
    default:
      goto switchD_005b6886_default;
    }
  default:
    goto switchD_005b6886_default;
  }
  *(UInt32 *)(param_2 + 0x16) = uVar10;
switchD_005b6886_default:
  return local_19;
switchD_005b689d_caseD_9:
  pcVar7 = *(char **)(param_2 + 0x2a);
  pcVar2 = *(char **)(param_2 + 0x2e);
  pcVar3 = *(char **)(pcVar7 + 0x16);
  cVar8 = *pcVar3;
  bVar14 = true;
  if ((cVar8 != '\x04') && (cVar8 != '\x01' || ((byte)pcVar3[6] > 0x16))) {
    bVar14 = false;
  }
  if (!bVar14) {
    return false;
  }
  pcVar4 = *(char **)(pcVar2 + 0x16);
  cVar9 = *pcVar4;
  bVar14 = true;
  if ((cVar9 != '\x04') && (cVar9 != '\x01' || ((byte)pcVar4[6] > 0x16))) {
    bVar14 = false;
  }
  if (!bVar14) {
    return false;
  }
  if (local_31 < local_32) {
    param_1 = pcVar13;
    local_32 = local_31;
  }
  cVar1 = *param_1;
  if ((cVar8 != cVar1) || (cVar9 != cVar1)) {
    if (DAT_0070f269 == '\0') goto LAB_005b6a2c;
    bVar14 = cVar1 == '\x04';
    if ((!bVar14) && (bVar14 = false, cVar1 == '\x01')) {
      bVar14 = (byte)param_1[6] < 0x17;
    }
    bVar15 = cVar8 == '\x04';
    if ((!bVar15) && (bVar15 = false, cVar8 == '\x01')) {
      bVar15 = (byte)pcVar3[6] < 0x17;
    }
    if (bVar15 != bVar14) goto LAB_005b6a2c;
    bVar14 = cVar1 == '\x04';
    if ((!bVar14) && (bVar14 = false, cVar1 == '\x01')) {
      bVar14 = (byte)param_1[6] < 0x17;
    }
    bVar15 = cVar9 == '\x04';
    if ((!bVar15) && (bVar15 = false, cVar9 == '\x01')) {
      bVar15 = (byte)pcVar4[6] < 0x17;
    }
    if (bVar15 != bVar14) goto LAB_005b6a2c;
  }
  cVar8 = fn_005b6800((char*)(param_1),(char*)( pcVar7),(char)( 0));
  if ((cVar8 != '\0') && (cVar8 = fn_005b6800((char*)(param_1),(char*)( pcVar2),(char)( 0)), cVar8 != '\0') &&
     (DAT_0070f26a != '\0' || (param_2[1] != '\t' || (local_32 != '\0'))) &&
     (local_19 = true, param_3 != '\0')) {
    fn_005b6800((char*)(param_1),(char*)( pcVar7),(char)( param_3));
    fn_005b6800((char*)(param_1),(char*)( pcVar2),(char)( param_3));
    cVar8 = is_unsigned((void*)(*(UInt32 *)(param_2 + 0x16)));
    cVar9 = is_unsigned((void*)(param_1));
    if ((cVar8 == '\0') == (cVar9 == '\0')) {
      *(char **)(param_2 + 0x16) = param_1;
    }
    else {
      if (cVar8 == '\0') {
        uVar10 = (UInt32)fn_005b7b10((char*)(param_1));
      }
      else {
        uVar10 = (UInt32)fn_005b7c20((char*)(param_1));
      }
      *(UInt32 *)(param_2 + 0x16) = uVar10;
    }
    local_31 = local_32;
  }
LAB_005b6a2c:
  if (DAT_0070f26b == '\0') {
    return local_19;
  }
  if (*param_2 != '\x03') {
    return local_19;
  }
  if (param_2[1] != '\t') {
    return local_19;
  }
  if (*pcVar7 != '\x03') {
    return local_19;
  }
  if (pcVar7[1] != '2') {
    return local_19;
  }
  if (*pcVar2 != '\x03') {
    return local_19;
  }
  if (pcVar2[1] != '2') {
    return local_19;
  }
  pcVar13 = *(char **)(pcVar7 + 0x16);
  iVar11 = *(int *)(pcVar13 + 2);
  if (iVar11 == 1) {
    cVar8 = '\0';
  }
  else if (iVar11 == 2) {
    cVar8 = '\x01';
  }
  else if (iVar11 == 4) {
    cVar8 = '\x02';
  }
  else if (iVar11 == 8) {
    cVar8 = '\x03';
  }
  else {
    cVar8 = -1;
  }
  if (cVar8 != '\x02') {
    return local_19;
  }
  pcVar3 = *(char **)(pcVar2 + 0x16);
  iVar11 = *(int *)(pcVar3 + 2);
  if (iVar11 == 1) {
    cVar8 = '\0';
  }
  else if (iVar11 == 2) {
    cVar8 = '\x01';
  }
  else if (iVar11 == 4) {
    cVar8 = '\x02';
  }
  else if (iVar11 == 8) {
    cVar8 = '\x03';
  }
  else {
    cVar8 = -1;
  }
  if (cVar8 != '\x02') {
    return local_19;
  }
  iVar11 = *(int *)(pcVar2 + 0x2a);
  pcVar4 = *(char **)(*(int *)(pcVar7 + 0x2a) + 0x16);
  iVar5 = *(int *)(pcVar4 + 2);
  if (iVar5 == 1) {
    cVar8 = '\0';
  }
  else if (iVar5 == 2) {
    cVar8 = '\x01';
  }
  else if (iVar5 == 4) {
    cVar8 = '\x02';
  }
  else if (iVar5 == 8) {
    cVar8 = '\x03';
  }
  else {
    cVar8 = -1;
  }
  if (cVar8 != '\x01') {
    return local_19;
  }
  pcVar6 = *(char **)(iVar11 + 0x16);
  iVar5 = *(int *)(pcVar6 + 2);
  if (iVar5 == 1) {
    cVar8 = '\0';
  }
  else if (iVar5 == 2) {
    cVar8 = '\x01';
  }
  else if (iVar5 == 4) {
    cVar8 = '\x02';
  }
  else if (iVar5 == 8) {
    cVar8 = '\x03';
  }
  else {
    cVar8 = -1;
  }
  if (cVar8 != '\x01') {
    return local_19;
  }
  cVar8 = *pcVar4;
  bVar14 = true;
  if ((cVar8 != '\x04') && (cVar8 != '\x01' || ((byte)pcVar4[6] > 0x16))) {
    bVar14 = false;
  }
  if (!bVar14) {
    return local_19;
  }
  cVar9 = *pcVar6;
  bVar14 = true;
  if ((cVar9 != '\x04') && (cVar9 != '\x01' || ((byte)pcVar6[6] > 0x16))) {
    bVar14 = false;
  }
  if (!bVar14) {
    return local_19;
  }
  cVar1 = *pcVar13;
  if ((cVar8 != cVar1) || (cVar9 != *pcVar3)) {
    if (DAT_0070f269 == '\0') {
      return local_19;
    }
    bVar14 = cVar1 == '\x04';
    if ((!bVar14) && (bVar14 = false, cVar1 == '\x01')) {
      bVar14 = (byte)pcVar13[6] < 0x17;
    }
    bVar15 = cVar8 == '\x04';
    if ((!bVar15) && (bVar15 = false, cVar8 == '\x01')) {
      bVar15 = (byte)pcVar4[6] < 0x17;
    }
    if (bVar15 != bVar14) {
      return local_19;
    }
    bVar14 = true;
    if ((*pcVar3 != '\x04') && (*pcVar3 != '\x01' || ((byte)pcVar3[6] > 0x16))) {
      bVar14 = false;
    }
    bVar15 = cVar9 == '\x04';
    if ((!bVar15) && (bVar15 = false, cVar9 == '\x01')) {
      bVar15 = (byte)pcVar6[6] < 0x17;
    }
    if (bVar15 != bVar14) {
      return local_19;
    }
  }
  if (local_31 < '\x02') {
    return local_19;
  }
  if (param_3 == '\0') {
    return true;
  }
  fn_005b6800((char*)(pcVar4),(char*)( pcVar7),(char)( param_3));
  fn_005b6800((char*)(*(UInt32 *)(iVar11 + 0x16)),(char*)( pcVar2),(char)( param_3));
  return true;
}



void fn_005b7230(int param_1, UInt32 param_2)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  char *pcVar5;
  UInt32 local_24;
  UInt32 local_20;
  UInt32 local_1c;
  UInt32 local_18;
  int local_14;
  
  pcVar1 = *(char **)(param_1 + 0x2a);
  local_14 = 1;
  cVar2 = pcVar1[1];
  if ((cVar2 != '\x12') && (cVar2 != '%')) {
    local_14 = 0;
  }
  if (*pcVar1 != '\x03') {
    return;
  }
  if (*(int *)(*(int *)(pcVar1 + 0x16) + 2) < *(int *)(*(int *)(param_1 + 0x16) + 2)) {
    return;
  }
  if (((char)local_14 == '\0') && (cVar2 != '\v') && (cVar2 != ' ')) {
    return;
  }
  cVar2 = is_unsigned((void*)(*(int *)(param_1 + 0x16)));
  cVar3 = is_unsigned((void*)(*(UInt32 *)(pcVar1 + 0x16)));
  if ((cVar3 == '\0') || (cVar2 == '\0')) {
    if (cVar3 != '\0') {
      return;
    }
    if (cVar2 != '\0') {
      return;
    }
    if (*(int *)(*(int *)(param_1 + 0x16) + 2) != *(int *)(*(int *)(pcVar1 + 0x16) + 2)) {
      return;
    }
  }
  pcVar5 = *(char **)(pcVar1 + 0x2a);
  pcVar4 = *(char **)(pcVar1 + 0x2e);
  cVar2 = fn_005b07f0((void*)(pcVar5));
  if (cVar2 != '\0') {
    local_1c = *(UInt32 *)(*(int *)(pcVar5 + 0x2a) + 0x10);
    local_18 = *(UInt32 *)(*(int *)(pcVar5 + 0x2a) + 0x14);
    if ((*(int *)(pcVar5 + 0x16) != *(int *)(param_1 + 0x16)) &&
       (cVar2 = fn_005b7e20((char*)(*(int *)(pcVar5 + 0x16)),(char*)( *(int *)(param_1 + 0x16))), cVar2 == '\0')) {
      fn_005b5a50((UInt32)(&local_1c),(int)( *(UInt32 *)(param_1 + 0x16)));
    }
  }
  cVar2 = fn_005b07f0((void*)(pcVar4));
  if (cVar2 != '\0') {
    local_24 = *(UInt32 *)(*(int *)(pcVar4 + 0x2a) + 0x10);
    local_20 = *(UInt32 *)(*(int *)(pcVar4 + 0x2a) + 0x14);
    if (*(int *)(pcVar4 + 0x16) != *(int *)(param_1 + 0x16)) {
      fn_005b5a50((UInt32)(&local_24),(int)( *(int *)(param_1 + 0x16)));
    }
  }
  if ((*(int *)(pcVar5 + 0x16) != *(int *)(pcVar1 + 0x16)) &&
     (cVar2 = fn_005b7e20((char*)(*(int *)(pcVar5 + 0x16)),(char*)( *(int *)(pcVar1 + 0x16))), cVar2 == '\0')) {
    return;
  }
  cVar2 = fn_005b07f0((void*)(pcVar5));
  if ((cVar2 == '\0') ||
     (cVar2 = CInt64_Equal(*(UInt32 *)(*(int *)(pcVar5 + 0x2a) + 0x10),
                           *(UInt32 *)(*(int *)(pcVar5 + 0x2a) + 0x14), local_1c, local_18),
     cVar2 == '\0')) {
    if (*pcVar5 != '\x02') {
      return;
    }
    if (pcVar5[1] != '2') {
      return;
    }
    if ((*(int *)(*(int *)(pcVar5 + 0x2a) + 0x16) != *(int *)(param_1 + 0x16)) &&
       (cVar2 = fn_005b7e20((char*)(*(int *)(*(int *)(pcVar5 + 0x2a) + 0x16)),(char*)( *(int *)(param_1 + 0x16))),
       cVar2 == '\0')) {
      return;
    }
  }
  if ((*(int *)(pcVar4 + 0x16) != *(int *)(pcVar1 + 0x16)) &&
     (cVar2 = fn_005b7e20((char*)(*(int *)(pcVar4 + 0x16)),(char*)( *(int *)(pcVar1 + 0x16))), cVar2 == '\0') &&
     ((char)local_14 == '\0')) {
    return;
  }
  cVar2 = fn_005b07f0((void*)(pcVar4));
  if ((cVar2 == '\0') ||
     (cVar2 = CInt64_Equal(*(UInt32 *)(*(int *)(pcVar4 + 0x2a) + 0x10),
                           *(UInt32 *)(*(int *)(pcVar4 + 0x2a) + 0x14), local_24, local_20),
     cVar2 == '\0')) {
    if ((*pcVar4 == '\x02') && (pcVar4[1] == '2')) {
      if ((*(int *)(*(int *)(pcVar4 + 0x2a) + 0x16) == *(int *)(param_1 + 0x16)) ||
         (cVar2 = fn_005b7e20((char*)(*(int *)(*(int *)(pcVar4 + 0x2a) + 0x16)),(char*)( *(int *)(param_1 + 0x16))),
         cVar2 != '\0')) goto LAB_005b7468;
    }
    if ((char)local_14 == '\0') {
      return;
    }
  }
LAB_005b7468:
  local_14 = *(int *)(pcVar1 + 0x16);
  *(UInt32 *)(pcVar1 + 0x16) = *(UInt32 *)(param_1 + 0x16);
  if (*pcVar5 == '\x02') {
    *(UInt32 *)(pcVar5 + 0x16) = *(UInt32 *)(param_1 + 0x16);
    pcVar5 = *(char **)(pcVar5 + 0x2a);
  }
  else {
    *(UInt32 *)(pcVar5 + 0x16) = *(UInt32 *)(param_1 + 0x16);
  }
  if ((*pcVar4 == '\x02') && (pcVar4[1] == '2')) {
    if ((*(int *)(*(int *)(pcVar4 + 0x2a) + 0x16) == *(int *)(param_1 + 0x16)) ||
       (cVar2 = fn_005b7e20((char*)(*(int *)(*(int *)(pcVar4 + 0x2a) + 0x16)),(char*)( *(int *)(param_1 + 0x16))),
       cVar2 != '\0')) {
      if ((*(int *)(pcVar4 + 0x16) == local_14) ||
         (cVar2 = fn_005b7e20((char*)(*(int *)(pcVar4 + 0x16)),(char*)( local_14)), cVar2 != '\0')) {
        *(UInt32 *)(pcVar4 + 0x16) = *(UInt32 *)(param_1 + 0x16);
        pcVar4 = *(char **)(pcVar4 + 0x2a);
      }
      goto LAB_005b74de;
    }
  }
  cVar2 = fn_005b07f0((void*)(pcVar4));
  if ((cVar2 != '\0') &&
     (cVar2 = CInt64_Equal(*(UInt32 *)(*(int *)(pcVar4 + 0x2a) + 0x10),
                           *(UInt32 *)(*(int *)(pcVar4 + 0x2a) + 0x14), local_24, local_20),
     cVar2 != '\0')) {
    *(UInt32 *)(pcVar4 + 0x16) = *(UInt32 *)(param_1 + 0x16);
  }
LAB_005b74de:
  fn_005b6800((char*)(param_2),(char*)( pcVar5),(char)( 1));
  fn_005b6800((char*)(param_2),(char*)( pcVar4),(char)( 1));
  return;
}



void fn_005b7580(int param_1, UInt32 param_2)

{
  char *puVar1;
  bool bVar2;
  char cVar3;
  char *unaff_ESI;
  UInt32 local_28;
  UInt32 local_24;
  char *local_20;
  char local_19;
  int local_18;
  char *local_14;
  
  cVar3 = is_unsigned((void*)(*(UInt32 *)(param_1 + 0x16)));
  local_19 = cVar3 == '\0';
  puVar1 = *(char **)(param_1 + 0x2a);
  if (*(int *)(*(int *)(param_1 + 0x16) + 2) != *(int *)(*(int *)(puVar1 + 0x16) + 2)) {
    return;
  }
  cVar3 = is_unsigned((void*)(*(int *)(puVar1 + 0x16)));
  if ((cVar3 == '\0') == (bool)local_19) {
    return;
  }
  local_19 = '\x01';
  switch(*puVar1) {
  case 2:
    local_14 = *(char **)(puVar1 + 0x2a);
    if ((*(int *)(local_14 + 0x16) == *(int *)(puVar1 + 0x16)) ||
       (cVar3 = fn_005b7e20((char*)(*(int *)(local_14 + 0x16)),(char*)( *(int *)(puVar1 + 0x16))), cVar3 != '\0')) {
      if (*local_14 == '\x03') {
        bVar2 = false;
        if (((byte)(local_14[1] - 0xbU) < 0x1b) &&
           ((1 << (local_14[1] - 0xbU & 0x1f) & 0x4600083U) != 0)) {
          bVar2 = true;
        }
        if (bVar2) break;
      }
      local_19 = '\0';
    }
    break;
  case 3:
    local_20 = *(char **)(puVar1 + 0x2a);
    unaff_ESI = *(char **)(puVar1 + 0x2e);
    local_18 = 1;
    cVar3 = puVar1[1];
    if ((cVar3 != '\x12') && (cVar3 != '%')) {
      local_18 = 0;
    }
    if (((char)local_18 == '\0') && (cVar3 != '\v') && (cVar3 != ' ') &&
       (cVar3 != '\f' && (cVar3 != '!'))) {
      if ((*(int *)(local_20 + 0x16) == *(int *)(puVar1 + 0x16)) ||
         (cVar3 = fn_005b7e20((char*)(*(int *)(local_20 + 0x16)),(char*)( *(int *)(puVar1 + 0x16))), cVar3 != '\0'))
      {
        if (*local_20 == '\x03') {
          bVar2 = false;
          if (((byte)(local_20[1] - 0xbU) < 0x1b) &&
             ((1 << (local_20[1] - 0xbU & 0x1f) & 0x4600083U) != 0)) {
            bVar2 = true;
          }
          if (bVar2) break;
        }
        if ((*(int *)(unaff_ESI + 0x16) == *(int *)(puVar1 + 0x16)) ||
           (cVar3 = fn_005b7e20((char*)(*(int *)(unaff_ESI + 0x16)),(char*)( *(int *)(puVar1 + 0x16))), cVar3 != '\0'
           ) || ((char)local_18 != '\0')) {
          if (*unaff_ESI == '\x03') {
            bVar2 = false;
            if (((byte)(unaff_ESI[1] - 0xbU) < 0x1b) &&
               ((1 << (unaff_ESI[1] - 0xbU & 0x1f) & 0x4600083U) != 0)) {
              bVar2 = true;
            }
            if (bVar2) break;
          }
          local_19 = '\0';
        }
      }
    }
  }
  if (local_19 != '\0') {
    return;
  }
  local_18 = *(int *)(puVar1 + 0x16);
  *(UInt32 *)(puVar1 + 0x16) = *(UInt32 *)(param_1 + 0x16);
  switch(*puVar1) {
  case 2:
    if ((*local_14 == '\x02') && (local_14[1] == '2')) {
      if ((*(int *)(*(int *)(local_14 + 0x2a) + 0x16) == *(int *)(param_1 + 0x16)) ||
         (cVar3 = fn_005b7e20((char*)(*(int *)(*(int *)(local_14 + 0x2a) + 0x16)),(char*)( *(int *)(param_1 + 0x16)))
         , cVar3 != '\0')) {
        *(UInt32 *)(local_14 + 0x16) = *(UInt32 *)(param_1 + 0x16);
        local_14 = *(char **)(local_14 + 0x2a);
        goto LAB_005b7816;
      }
    }
    *(UInt32 *)(local_14 + 0x16) = *(UInt32 *)(param_1 + 0x16);
LAB_005b7816:
    fn_005b6800((char*)(param_2),(char*)( local_14),(char)( 1));
    return;
  case 3:
    break;
  default:
    CError_Internal(filename, 0x2a1);
    return;
  }
  if ((*local_20 == '\x02') && (local_20[1] == '2')) {
    if ((*(int *)(*(int *)(local_20 + 0x2a) + 0x16) != *(int *)(param_1 + 0x16)) &&
       (cVar3 = fn_005b7e20((char*)(*(int *)(*(int *)(local_20 + 0x2a) + 0x16)),(char*)( *(int *)(param_1 + 0x16))),
       cVar3 == '\0')) goto LAB_005b78b0;
    *(UInt32 *)(local_20 + 0x16) = *(UInt32 *)(param_1 + 0x16);
    local_20 = *(char **)(local_20 + 0x2a);
  }
  else {
LAB_005b78b0:
    *(UInt32 *)(local_20 + 0x16) = *(UInt32 *)(param_1 + 0x16);
  }
  if ((*unaff_ESI == '\x02') && (unaff_ESI[1] == '2')) {
    if ((*(int *)(*(int *)(unaff_ESI + 0x2a) + 0x16) == *(int *)(param_1 + 0x16)) ||
       (cVar3 = fn_005b7e20((char*)(*(int *)(*(int *)(unaff_ESI + 0x2a) + 0x16)),(char*)( *(int *)(param_1 + 0x16))),
       cVar3 != '\0')) {
      if ((*(int *)(unaff_ESI + 0x16) == local_18) ||
         (cVar3 = fn_005b7e20((char*)(*(int *)(unaff_ESI + 0x16)),(char*)( local_18)), cVar3 != '\0')) {
        *(UInt32 *)(unaff_ESI + 0x16) = *(UInt32 *)(param_1 + 0x16);
        unaff_ESI = *(char **)(unaff_ESI + 0x2a);
      }
      goto LAB_005b77a6;
    }
  }
  cVar3 = fn_005b07f0((void*)(unaff_ESI));
  if (cVar3 == '\0') {
    *(UInt32 *)(unaff_ESI + 0x16) = *(UInt32 *)(param_1 + 0x16);
  }
  else if ((*(int *)(unaff_ESI + 0x16) == local_18) ||
          (cVar3 = fn_005b7e20((char*)(*(int *)(unaff_ESI + 0x16)),(char*)( local_18)), cVar3 != '\0')) {
    *(UInt32 *)(unaff_ESI + 0x16) = *(UInt32 *)(param_1 + 0x16);
  }
  else if ((*(int *)(unaff_ESI + 0x16) != *(int *)(param_1 + 0x16)) &&
          (cVar3 = fn_005b7e20((char*)(*(int *)(unaff_ESI + 0x16)),(char*)( *(int *)(param_1 + 0x16))), cVar3 == '\0'
          )) {
    local_24 = *(UInt32 *)(*(int *)(unaff_ESI + 0x2a) + 0x14);
    local_28 = *(UInt32 *)(*(int *)(unaff_ESI + 0x2a) + 0x10);
    fn_005b5a50((UInt32)(&local_28),(int)( *(UInt32 *)(param_1 + 0x16)));
    cVar3 = CInt64_Equal(*(UInt32 *)(*(int *)(unaff_ESI + 0x2a) + 0x10),
                         *(UInt32 *)(*(int *)(unaff_ESI + 0x2a) + 0x14), local_28, local_24);
    if (cVar3 != '\0') {
      *(UInt32 *)(unaff_ESI + 0x16) = *(UInt32 *)(param_1 + 0x16);
    }
  }
LAB_005b77a6:
  fn_005b6800((char*)(param_2),(char*)( local_20),(char)( 1));
  fn_005b6800((char*)(param_2),(char*)( unaff_ESI),(char)( 1));
  return;
}



bool fn_005b7980(char *param_1, char *param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  short sVar5;
  bool bVar6;
  
  cVar4 = *param_1;
  if ((cVar4 == '\f') && (*param_2 == '\f')) {
    return true;
  }
  if (DAT_0070f268 != '\0') {
    bVar6 = false;
    if (cVar4 == '\x01') {
      bVar6 = (byte)param_1[6] < 0x17;
    }
    if ((bVar6) || (cVar4 == '\x04') || (cVar4 == '\f') ||
       (cVar4 == '\v' && (**(char **)(param_1 + 6) != '\a'))) {
      bVar3 = true;
      cVar4 = *param_2;
      bVar2 = false;
      bVar1 = true;
      bVar6 = true;
      if ((cVar4 == '\x01') && ((byte)param_2[6] < 0x17)) {
        bVar2 = true;
      }
      if ((!bVar2) && (cVar4 != '\x04')) {
        bVar6 = false;
      }
      if ((!bVar6) && (cVar4 != '\f')) {
        bVar1 = false;
      }
      if ((!bVar1) && (cVar4 != '\v' || (**(char **)(param_2 + 6) == '\a'))) {
        bVar3 = false;
      }
      if (bVar3) {
        bVar6 = false;
        if (*(int *)(param_1 + 2) == *(int *)(param_2 + 2)) {
          bVar1 = false;
          bVar2 = true;
          cVar4 = is_unsigned((void*)(param_1));
          if (cVar4 != '\0') {
            cVar4 = is_unsigned((void*)(param_2));
            if (cVar4 != '\0') {
              bVar1 = true;
            }
          }
          if (!bVar1) {
            bVar1 = false;
            cVar4 = is_unsigned((void*)(param_1));
            if (cVar4 == '\0') {
              cVar4 = is_unsigned((void*)(param_2));
              if (cVar4 == '\0') {
                bVar1 = true;
              }
            }
            if (!bVar1) {
              bVar2 = false;
            }
          }
          if (bVar2) {
            bVar6 = true;
          }
        }
        return bVar6;
      }
    }
  }
  sVar5 = fn_00454c20((void*)(param_1),(void*)( param_2));
  return sVar5 != 0;
}



char * fn_005b7af0(void)

{
  if ((DAT_0070f1a8 != '\0') && (DAT_0070f1bc != '\0')) {
    return &DAT_00699c1c;
  }
  return &DAT_00699c54;
}



char * fn_005b7b10(char *param_1)

{
  if ((*param_1 != '\x04') && (*param_1 != '\f') &&
     (*param_1 != '\x01' || ((byte)param_1[6] > 0x16))) goto LAB_005b7b2e;
  if ((param_1 == &DAT_00699c1c) || (param_1 == &DAT_00699c3c) || (param_1 == &DAT_00699c24) ||
     (param_1 == &DAT_00699c2c || (param_1 == &DAT_00699c34))) {
LAB_005b7c07:
    if (*(int *)(param_1 + 2) == DAT_00699c2e) {
      return &DAT_00699c2c;
    }
LAB_005b7bb3:
    if (*(int *)(param_1 + 2) == DAT_00699c46) {
      return &DAT_00699c44;
    }
LAB_005b7bc5:
    if (*(int *)(param_1 + 2) == DAT_00699c56) {
      return &DAT_00699c54;
    }
LAB_005b7bd7:
    if (*(int *)(param_1 + 2) == DAT_00699c66) {
      return &DAT_00699c64;
    }
  }
  else {
    if ((param_1 == &DAT_00699c44) || (param_1 == &DAT_00699c4c)) goto LAB_005b7bb3;
    if ((param_1 == &DAT_00699c54) || (param_1 == &DAT_00699c5c)) goto LAB_005b7bc5;
    if ((param_1 == &DAT_00699c64) || (param_1 == &DAT_00699c6c)) goto LAB_005b7bd7;
    if ((param_1 != &DAT_00699c74) && (param_1 != &DAT_00699c7c)) goto LAB_005b7c07;
  }
  if (*(int *)(param_1 + 2) == DAT_00699c76) {
    return &DAT_00699c74;
  }
LAB_005b7b2e:
  CError_Internal(filename, 0x144);
  return (char *)0x0;
}



char * fn_005b7c20(char *param_1)

{
  if ((*param_1 != '\x04') && (*param_1 != '\f') &&
     (*param_1 != '\x01' || ((byte)param_1[6] > 0x16))) goto LAB_005b7c3e;
  if ((param_1 == &DAT_00699c1c) || (param_1 == &DAT_00699c3c) || (param_1 == &DAT_00699c24) ||
     (param_1 == &DAT_00699c2c || (param_1 == &DAT_00699c34))) {
LAB_005b7d17:
    if (*(int *)(param_1 + 2) == DAT_00699c36) {
      return &DAT_00699c34;
    }
LAB_005b7cc3:
    if (*(int *)(param_1 + 2) == DAT_00699c4e) {
      return &DAT_00699c4c;
    }
LAB_005b7cd5:
    if (*(int *)(param_1 + 2) == DAT_00699c5e) {
      return &DAT_00699c5c;
    }
LAB_005b7ce7:
    if (*(int *)(param_1 + 2) == DAT_00699c6e) {
      return &DAT_00699c6c;
    }
  }
  else {
    if ((param_1 == &DAT_00699c44) || (param_1 == &DAT_00699c4c)) goto LAB_005b7cc3;
    if ((param_1 == &DAT_00699c54) || (param_1 == &DAT_00699c5c)) goto LAB_005b7cd5;
    if ((param_1 == &DAT_00699c64) || (param_1 == &DAT_00699c6c)) goto LAB_005b7ce7;
    if ((param_1 != &DAT_00699c74) && (param_1 != &DAT_00699c7c)) goto LAB_005b7d17;
  }
  if (*(int *)(param_1 + 2) == DAT_00699c7e) {
    return &DAT_00699c7c;
  }
LAB_005b7c3e:
  CError_Internal(filename, 0x108);
  return (char *)0x0;
}



UInt32 * fn_005b7d30(UInt32 *param_1)

{
  UInt32 *puVar1;
  UInt32 uVar2;
  
  if (param_1 != (UInt32 *)0x0) {
    switch(*(char *)param_1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 8:
      return param_1;
    case 6:
    case 10:
      return param_1;
    case 7:
      return param_1;
    case 0xb:
      puVar1 = (UInt32 *)galloc(0x12);
      *puVar1 = *param_1;
      puVar1[1] = param_1[1];
      puVar1[2] = param_1[2];
      puVar1[3] = param_1[3];
      *(UInt16 *)(puVar1 + 4) = *(UInt16 *)(param_1 + 4);
      uVar2 = (UInt32)fn_005b7d30((UInt32*)(*(UInt32 *)((int)param_1 + 6)));
      *(UInt32 *)((int)puVar1 + 6) = uVar2;
      *(UInt32 *)((int)puVar1 + 0xe) = *(UInt32 *)((int)puVar1 + 0xe) & 0x1f200003;
      return puVar1;
    case 0xc:
      puVar1 = (UInt32 *)CTTool_CopyTypePointer((void*)(param_1));
      uVar2 = (UInt32)fn_005b7d30((UInt32*)(*(UInt32 *)((int)param_1 + 6)));
      *(UInt32 *)((int)puVar1 + 6) = uVar2;
      *(UInt32 *)((int)puVar1 + 10) = *(UInt32 *)((int)puVar1 + 10) & 0x1f200003;
      return puVar1;
    case 0xd:
      puVar1 = (UInt32 *)galloc(0x14);
      *puVar1 = *param_1;
      puVar1[1] = param_1[1];
      puVar1[2] = param_1[2];
      puVar1[3] = param_1[3];
      puVar1[4] = param_1[4];
      uVar2 = (UInt32)fn_005b7d30((UInt32*)(*(UInt32 *)((int)puVar1 + 6)));
      *(UInt32 *)((int)puVar1 + 6) = uVar2;
      return puVar1;
    case -1:
    case 9:
    case 0xe:
    case 0xf:
      return param_1;
    default:
      CError_Internal(filename, 0xa2);
      return (UInt32 *)0x0;
    }
  }
  return (UInt32 *)0x0;
}



bool fn_005b7e20(char *left,char *right)
{
 if(left==right)return true;
 if((UInt8)left[0]==8) {
  if((UInt8)right[0]==8 && *(UInt32*)(left+6)==*(UInt32*)(right+6) && (UInt8)left[10]==(UInt8)right[10] && (UInt8)left[11]==(UInt8)right[11])return true;
  return false;
 }
 if((UInt8)left[0]==12 && (UInt8)right[0]==12)return true;
 return fn_00454c20((void*)(left),(void*)(right))!=0;
}


