/* IroJump.c: native member, ABI, layout and data review is recorded in the TU ledger. */
typedef unsigned char byte;
typedef byte undefined1;
typedef unsigned short ushort;
typedef short undefined2;
typedef unsigned int uint;
typedef uint undefined4;
typedef byte bool;
#define true 1
#define false 0
extern int DAT_00710990,DAT_00710b54,DAT_00710170,DAT_00710998,DAT_007107e8;
extern int *DAT_00710924;
extern void CError_Internal(const char *,int);
extern void FUN_005ed4c0(const char *,...);
extern void FUN_005be690(void),FUN_005bdb30(void),FUN_005a9d80(void),FUN_005be4b0(void);
extern void FUN_005be190(uint),FUN_005ac050(uint);
extern byte FUN_005aba80(uint);
extern uint FUN_005bd630(uint),FUN_005a9cc0(void),FUN_00521c20(uint,byte),FUN_005b7d30(uint);
extern void FUN_005ad400(uint,uint,uint),FUN_005ad440(uint,uint,uint),FUN_005ad280(uint *),FUN_005ad220(uint,uint *),FUN_005ad260(uint *),FUN_005ae7b0(uint);
extern uint FUN_005acf30(uint,uint *);
static char s_Chaining_goto_at__d_006b9dbb[]="Chaining goto at %d\n";
static char s_IroJump_c_006b9d0f[]="IroJump.c";
static char s_Removing_If_IfNot_Goto_next_at___006b9d7b[]="Removing If/IfNot_Goto next at %d\n";
static char s_Removing_Switch_next_at__d_006b9d9f[]="Removing Switch next at %d\n";
static char s_Removing_branch_around_goto_at___006b9d57[]="Removing branch around goto at %d\n";
static char s_Removing_goto_next_at__d_006b9d3b[]="Removing goto next at %d\n";
static char s_Removing_tail_recursion_at__d_006b9d1b[]="Removing tail recursion at %d\n";

char fn_00606400(void);
void fn_00606470(int param_1, undefined4 param_2);
void fn_00606530(char *param_1, undefined4 param_2, undefined1 *param_3);
void fn_00606640(undefined1 *param_1, int param_2, uint unusedBlock);
char IRO_RemoveLabels(void);
char IRO_RemoveRedundantJumps(void);
byte IRO_DoJumpChaining(void);
byte fn_00606ba0(int *param_1);

char fn_00606400(void)
{
  int iVar1;
  char local_5;
  local_5 = '\0';
  for (iVar1 = DAT_00710990; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
    *(undefined1 *)(iVar1 + 0x3d) = 0;
  }
  FUN_005bdb30();
  for (iVar1 = DAT_00710990; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
    if ((*(char *)(iVar1 + 0x38) != '\0') && (*(short *)(iVar1 + 2) == 0)) {
      fn_00606470((int)(iVar1), (undefined4)(&local_5));
    }
  }
  if (local_5 != '\0') {
    FUN_005be190(DAT_00710170);
  }
  return local_5;
}

void fn_00606470(int param_1, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  ushort uVar3;
  char *pcVar4;
  char *pcVar5;
  *(undefined1 *)(param_1 + 0x3d) = 1;
  pcVar5 = (char *)0x0;
  for (pcVar4 = *(char **)(param_1 + 0x10); pcVar4 != (char *)0x0 &&
      (pcVar4 != *(char **)(*(int *)(param_1 + 0x14) + 0x3e)); pcVar4 = *(char **)(pcVar4 + 0x3e)) {
    if (((*(uint *)(pcVar4 + 2) & 2) == 0) &&
       (cVar1 = *pcVar4, cVar1 != '\0' && (cVar1 != '\r') && (cVar1 != '\b') &&
       (cVar1 != '\t' && (cVar1 != '\x10'))) && (cVar1 != '\x17') &&
       (cVar1 != '\f' || (*(int *)(pcVar4 + 0x2a) != 0))) {
      pcVar5 = pcVar4;
    }
  }
  if (pcVar5 == (char *)0x0) {
    uVar3 = 0;
    if (*(short *)(param_1 + 8) != 0) {
      do {
        iVar2 = *(int *)(DAT_00710b54 +
                        (uint)*(ushort *)(*(int *)(param_1 + 10) + (uint)uVar3 * 2) * 4);
        if ((*(char *)(iVar2 + 0x38) != '\0') && (*(char *)(iVar2 + 0x3d) == '\0')) {
          fn_00606470((int)(iVar2), (undefined4)(param_2));
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(ushort *)(param_1 + 8));
    }
  }
  else {
    fn_00606530((char *)(pcVar5), (undefined4)(param_1), (undefined1 *)(param_2));
  }
  return;
}

void fn_00606530(char *param_1, undefined4 param_2, undefined1 *param_3)
{
  char *pcVar1;
  undefined4 *puVar2;
  char cVar3;
  short sVar4;
  short sVar5;
  char *pcVar6;
  pcVar6 = param_1;
  if (*param_1 == '\f') {
    pcVar6 = *(char **)(param_1 + 0x2a);
  }
  if ((*pcVar6 == '\a') && (**(char **)(pcVar6 + 0x32) == '\x01') &&
     (pcVar1 = *(char **)(*(char **)(pcVar6 + 0x32) + 0x2a), pcVar1 != (char *)0x0) &&
     (*pcVar1 == ';' && (*(int *)(pcVar1 + 0x10) == DAT_007107e8)) &&
     (DAT_007107e8 != 0 &&
     (*(int *)(param_1 + 0xe) == 0 || (*(int *)(*(int *)(param_1 + 0xe) + 0x12) == 0) ||
     (cVar3 = FUN_005aba80((uint)(pcVar6)), cVar3 == '\0')))) {
    sVar5 = 0;
    for (puVar2 = (uint *)DAT_00710924; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
      if (sVar5 == 0x7fff) {
        CError_Internal(s_IroJump_c_006b9d0f, 0x27c);
      }
      sVar5 = sVar5 + 1;
    }
    sVar4 = 0;
    for (puVar2 = *(undefined4 **)(*(int *)(DAT_007107e8 + 0x10) + 6); puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)*puVar2) {
      if (sVar4 == 0x7fff) {
        CError_Internal(s_IroJump_c_006b9d0f, 0x285);
      }
      sVar4 = sVar4 + 1;
    }
    if ((sVar4 == sVar5) && (sVar5 == *(short *)(pcVar6 + 0x2c))) {
      *param_3 = 1;
      fn_00606640((undefined1 *)(param_1), (int)(pcVar6), (uint)(param_2));
    }
  }
  return;
}

void fn_00606640(undefined1 *param_1, int param_2, uint unusedBlock)
{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  uint range[2];
  int local_1c;
  undefined4 local_18;
  int *local_14;
  FUN_005ed4c0(s_Removing_tail_recursion_at__d_006b9d1b, *(undefined4 *)(param_1 + 10));
  pcVar4 = *(char **)(DAT_00710990 + 0x10);
  pcVar2 = (char *)0x0;
  while ((pcVar1 = pcVar4, pcVar1 != (char *)0x0 && (*pcVar1 == '\0' || (*pcVar1 == '\x0f')))) {
    pcVar2 = pcVar1;
    pcVar4 = *(char **)(pcVar1 + 0x3e);
  }
  if ((pcVar1 == (char *)0x0) || (*pcVar1 != '\r')) {
    iVar7 = FUN_005bd630(0xd);
    *(int *)(iVar7 + 10) = DAT_00710998;
    DAT_00710998 = DAT_00710998 + 1;
    *(undefined4 *)(iVar7 + 0x3e) = 0;
    *(uint *)(iVar7 + 2) = *(uint *)(iVar7 + 2) | 1;
    FUN_005ad400((uint)(iVar7), (uint)(iVar7), (uint)(pcVar2));
    local_18 = FUN_005a9cc0();
    *(undefined4 *)(iVar7 + 0x2a) = local_18;
  }
  else {
    local_18 = *(undefined4 *)(pcVar1 + 0x2a);
  }
  local_1c = 0;
  local_14 = DAT_00710924;
  if (DAT_00710924 != (int *)0x0) {
    do {
      iVar7 = local_14[1];
      uVar6 = *(undefined4 *)(*(int *)(param_2 + 0x2e) + (short)local_1c * 4);
      FUN_005ad280(&range[0]);
      FUN_005acf30(uVar6, &range[0]);
      iVar3 = range[1];
      iVar5 = FUN_005bd630(1);
      *(undefined1 *)(iVar5 + 1) = 0x3b;
      uVar6 = FUN_00521c20(iVar7, 1);
      *(undefined4 *)(iVar5 + 0x2a) = uVar6;
      uVar6 = FUN_005b7d30(*(undefined4 *)(*(int *)(iVar5 + 0x2a) + 4));
      *(undefined4 *)(iVar5 + 0x12) = uVar6;
      *(int *)(iVar5 + 10) = DAT_00710998;
      DAT_00710998 = DAT_00710998 + 1;
      *(uint *)(iVar5 + 2) = *(uint *)(iVar5 + 2) | 0x26;
      iVar7 = FUN_005bd630(2);
      *(undefined1 *)(iVar7 + 1) = 4;
      uVar6 = FUN_005b7d30(*(undefined4 *)(iVar3 + 0x12));
      *(undefined4 *)(iVar7 + 0x12) = uVar6;
      *(int *)(iVar7 + 0x2a) = iVar5;
      *(int *)(iVar7 + 10) = DAT_00710998;
      DAT_00710998 = DAT_00710998 + 1;
      *(uint *)(iVar7 + 2) = *(uint *)(iVar7 + 2) | 6;
      iVar8 = FUN_005bd630(3);
      *(undefined1 *)(iVar8 + 1) = 0x1e;
      *(int *)(iVar8 + 0x2a) = iVar7;
      *(int *)(iVar8 + 0x2e) = iVar3;
      uVar6 = FUN_005b7d30(*(undefined4 *)(iVar3 + 0x12));
      *(undefined4 *)(iVar8 + 0x12) = uVar6;
      *(int *)(iVar8 + 10) = DAT_00710998;
      DAT_00710998 = DAT_00710998 + 1;
      *(int *)(iVar5 + 0x3e) = iVar7;
      *(int *)(iVar7 + 0x3e) = iVar8;
      FUN_005ad220(iVar5, &range[0]);
      FUN_005ad440((uint)(range[0]), (uint)(range[1]), (uint)(param_1));
      FUN_005ad260(&range[0]);
      local_1c = local_1c + 1;
      local_14 = (int *)*local_14;
    } while (local_14 != (int *)0x0);
    local_14 = (int *)0x0;
  }
  iVar7 = FUN_005bd630(8);
  *(int *)(iVar7 + 10) = DAT_00710998;
  DAT_00710998 = DAT_00710998 + 1;
  *(undefined4 *)(iVar7 + 0x3e) = 0;
  FUN_005ad400((uint)(iVar7), (uint)(iVar7), (uint)(param_1));
  *(undefined4 *)(iVar7 + 0x2a) = local_18;
  FUN_005ae7b0(param_2);
  *param_1 = 0;
  *(undefined4 *)(param_1 + 0x1a) = 0;
  return;
}

char IRO_RemoveLabels(void)
{
  uint *puVar1;
  char *pcVar2;
  int iVar3;
  char cVar4;
  cVar4 = '\0';
  FUN_005be690();
  for (iVar3 = DAT_00710990; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x30)) {
    pcVar2 = *(char **)(iVar3 + 0x10);
    if ((pcVar2 != (char *)0x0) && (*pcVar2 == '\r') && (*(char *)(iVar3 + 0x3c) == '\0')) {
      *pcVar2 = '\0';
      puVar1 = (uint *)(*(int *)(iVar3 + 0x10) + 2);
      *puVar1 = *puVar1 & 0xfffffffe;
      cVar4 = '\x01';
    }
  }
  if (cVar4 != '\0') {
    FUN_005be190(DAT_00710170);
  }
  FUN_005a9d80();
  return cVar4;
}

char IRO_RemoveRedundantJumps(void)
{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  char cVar6;
  char *pcVar7;
  cVar6 = '\0';
  iVar3 = DAT_00710990;
  do {
    if (iVar3 == 0) {
      if (cVar6 != '\0') {
        FUN_005be190(DAT_00710170);
      }
      FUN_005a9d80();
      return cVar6;
    }
    if (*(int *)(iVar3 + 0x10) != 0) {
      pcVar1 = *(char **)(iVar3 + 0x14);
      switch(*pcVar1) {
      case '\b':
        if ((*(uint *)(pcVar1 + 2) & 0x400) == 0) {
          for (pcVar4 = *(char **)(pcVar1 + 0x3e); pcVar4 != (char *)0x0 &&
              (*pcVar4 == '\0' ||
              (*pcVar4 == '\r' && (*(int *)(pcVar4 + 0x2a) != *(int *)(pcVar1 + 0x2a))));
              pcVar4 = *(char **)(pcVar4 + 0x3e)) {
          }
          for (; pcVar4 != (char *)0x0 && (*pcVar4 == '\r'); pcVar4 = *(char **)(pcVar4 + 0x3e)) {
            if (*(int *)(pcVar4 + 0x2a) == *(int *)(pcVar1 + 0x2a)) {
              FUN_005ed4c0(s_Removing_goto_next_at__d_006b9d3b, *(undefined4 *)(pcVar1 + 10));
              *pcVar1 = '\0';
              goto LAB_00606aa5;
            }
          }
        }
        break;
      case '\n':
      case '\v':
        for (pcVar4 = *(char **)(pcVar1 + 0x3e); pcVar4 != (char *)0x0 && (*pcVar4 == '\0');
            pcVar4 = *(char **)(pcVar4 + 0x3e)) {
        }
        if ((pcVar4 != (char *)0x0) && (*pcVar4 == '\b') && ((*(uint *)(pcVar4 + 2) & 0x400) == 0))
        {
          for (pcVar7 = *(char **)(pcVar4 + 0x3e); pcVar7 != (char *)0x0 &&
              (*pcVar7 == '\0' ||
              (*pcVar7 == '\r' && (*(int *)(pcVar7 + 0x2a) != *(int *)(pcVar1 + 0x2a))));
              pcVar7 = *(char **)(pcVar7 + 0x3e)) {
          }
          if ((pcVar7 != (char *)0x0) && (*pcVar7 == '\r') &&
             (*(int *)(pcVar7 + 0x2a) == *(int *)(pcVar1 + 0x2a))) {
            if (*pcVar1 == '\n') {
              *pcVar1 = '\v';
            }
            else {
              *pcVar1 = '\n';
            }
            *(undefined4 *)(pcVar1 + 0x2a) = *(undefined4 *)(pcVar4 + 0x2a);
            *pcVar4 = '\0';
            FUN_005ed4c0(s_Removing_branch_around_goto_at___006b9d57, *(undefined4 *)(pcVar1 + 10));
            cVar6 = '\x01';
          }
        }
        for (pcVar4 = *(char **)(pcVar1 + 0x3e); pcVar4 != (char *)0x0 &&
            (*pcVar4 == '\0' ||
            (*pcVar4 == '\r' && (*(int *)(pcVar4 + 0x2a) != *(int *)(pcVar1 + 0x2a))));
            pcVar4 = *(char **)(pcVar4 + 0x3e)) {
        }
        for (; pcVar4 != (char *)0x0 && (*pcVar4 == '\r'); pcVar4 = *(char **)(pcVar4 + 0x3e)) {
          if (*(int *)(pcVar4 + 0x2a) == *(int *)(pcVar1 + 0x2a)) {
            FUN_005ed4c0(s_Removing_If_IfNot_Goto_next_at___006b9d7b, *(undefined4 *)(pcVar1 + 10));
            *pcVar1 = '\0';
            FUN_005ac050(*(undefined4 *)(pcVar1 + 0x2e));
            goto LAB_00606aa5;
          }
        }
        break;
      case '\x0e':
        puVar2 = *(undefined4 **)(pcVar1 + 0x2a);
        for (puVar5 = (undefined4 *)*puVar2; puVar5 != (undefined4 *)0x0 && (puVar5[1] == puVar2[2])
            ; puVar5 = (undefined4 *)*puVar5) {
        }
        if (puVar5 == (undefined4 *)0x0) {
          FUN_005ed4c0(s_Removing_Switch_next_at__d_006b9d9f, *(undefined4 *)(pcVar1 + 10));
          FUN_005ac050(*(undefined4 *)(pcVar1 + 0x2e));
          *pcVar1 = '\b';
          *(undefined4 *)(pcVar1 + 0x2a) = puVar2[2];
LAB_00606aa5:
          cVar6 = '\x01';
        }
      }
    }
    iVar3 = *(int *)(iVar3 + 0x30);
  } while( true );
}

byte IRO_DoJumpChaining(void)
{
  undefined1 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  char cVar4;
  undefined4 *puVar5;
  byte bVar6;
  byte local_11;
  local_11 = 0;
  do {
    bVar6 = 0;
    for (iVar3 = DAT_00710990; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x30)) {
      if (*(int *)(iVar3 + 0x10) == 0) goto switchD_00606b14_caseD_9;
      puVar1 = *(undefined1 **)(iVar3 + 0x14);
      switch(*puVar1) {
      case 8:
        if ((*(uint *)(puVar1 + 2) & 0x400) == 0) {
          puVar5 = (undefined4 *)(puVar1 + 0x2a);
          goto LAB_00606b52;
        }
        break;
      case 10:
      case 0xb:
        puVar5 = (undefined4 *)(puVar1 + 0x2a);
        goto LAB_00606b52;
      case 0xe:
        puVar5 = *(undefined4 **)(puVar1 + 0x2a);
        for (puVar2 = (undefined4 *)*puVar5; puVar2 != (undefined4 *)0x0;
            puVar2 = (undefined4 *)*puVar2) {
          cVar4 = fn_00606ba0((int *)(puVar2 + 1));
          if (cVar4 != '\0') {
            bVar6 = 1;
          }
        }
        puVar5 = puVar5 + 2;
LAB_00606b52:
        cVar4 = fn_00606ba0((int *)(puVar5));
        if (cVar4 != '\0') {
          bVar6 = 1;
        }
      }
switchD_00606b14_caseD_9: ;
    }
    local_11 = local_11 | bVar6;
    FUN_005a9d80();
    if (bVar6 == 0) {
      if (local_11 != 0) {
        FUN_005be690();
        FUN_005be4b0();
      }
      return local_11;
    }
  } while( true );
}

byte fn_00606ba0(int *param_1)
{
 int block,saved,original;
 char *p;
 for(block=DAT_00710990;block;block=*(int *)(block+48)) {
  p=*(char **)(block+16);
  if(p && *p==13 && *(int *)(p+42)==*param_1) {
   original=*param_1;saved=0;
   for(p=*(char **)(p+62);p && (*p==13 || *p==0);p=*(char **)(p+62))
    if(*p==13)saved=*(int *)(p+42);
   if(*p==8 && !(*(uint *)(p+2)&0x400) && original!=*(int *)(p+42)) {
    *param_1=*(int *)(p+42);
    FUN_005ed4c0(s_Chaining_goto_at__d_006b9dbb,*(uint *)(p+10));
    return 1;
   }
   if(saved && original!=saved)*param_1=saved;
   return 0;
  }
 }
 return 0;
}
