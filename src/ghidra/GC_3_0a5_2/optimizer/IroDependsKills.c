/*
 * GENERATED GHIDRA EVIDENCE - NOT A BUILD INPUT.
 * Proposed source group: src/GC_3_0a5_2/optimizer/IroDependsKills.c
 * Function identities and types remain provisional unless the ledger says mapped/high.
 */

/*
 * Target: 0x005f6530
 * Candidate: FUN_005f6530
 * State/confidence: source_assigned / medium
 * Basis: translation_unit_inventory
 */
void FUN_005f6530(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  bool bVar5;
  char cVar6;
  uint *puVar7;
  char *pcVar8;
  undefined4 *puVar9;
  int *local_20;
  char *local_1c;
  undefined4 *local_18;
  undefined4 *local_14;

  iVar1 = *(int *)(param_1 + 0x32);
  bVar5 = false;
  if ((iVar1 == 0) || (DAT_0070f240 == '\0') || (*(int *)(iVar1 + 0x1e) == 0) || (DAT_007107e8 == 0)
     ) {
    bVar5 = true;
  }
  else {
    local_14 = (undefined4 *)0x0;
    FUN_004a6fb0(DAT_007107e8, iVar1, &local_14);
    if (local_14 == (undefined4 *)0x0) {
      bVar5 = true;
    }
    else {
      puVar9 = local_14;
      if (local_14 != (undefined4 *)0x0) {
        while ((pcVar8 = (char *)*puVar9, pcVar8 != (char *)0x0 && (puVar9[1] != 0))) {
          local_18 = (undefined4 *)((uint)local_18 & 0xffffff00);
          if (pcVar8 != *(char **)(puVar9[1] + 0x3e)) {
            do {
              if ((*pcVar8 == '\x01') && (**(char **)(pcVar8 + 0x2a) == ';')) {
                local_18 = (undefined4 *)CONCAT31(local_18._1_3_, 1);
                iVar1 = *(int *)(*(char **)(pcVar8 + 0x2a) + 0x10);
                if (iVar1 == 0) {
                  CError_Internal(s_IroDependsKills_c_006b9b3a, 0x351);
                }
                local_20 = (int *)0x0;
                FUN_004a60c0(iVar1, param_1, &local_20);
                for (piVar2 = local_20; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
                  if (piVar2[1] == 0) {
                    bVar5 = true;
                    break;
                  }
                }
                if (local_20 != (int *)0x0) {
                  do {
                    piVar2 = (int *)*local_20;
                    FUN_004c5330(local_20);
                    local_20 = piVar2;
                  } while (piVar2 != (int *)0x0);
                  local_20 = (int *)0x0;
                }
                if (bVar5) break;
              }
              pcVar8 = *(char **)(pcVar8 + 0x3e);
            } while (pcVar8 != *(char **)(puVar9[1] + 0x3e));
          }
          if ((char)local_18 == '\0') {
            bVar5 = true;
          }
          if ((bVar5) || (puVar9 = (undefined4 *)puVar9[2], puVar9 == (undefined4 *)0x0))
          goto LAB_005f67d4;
        }
        bVar5 = true;
      }
LAB_005f67d4:
      puVar9 = local_18;
      local_18 = local_14;
      if (!bVar5) {
        for (; puVar9 = (undefined4 *)0, local_18 != (undefined4 *)0x0;
            local_18 = (undefined4 *)local_18[2]) {
          local_1c = (char *)*local_18;
          if (local_1c != *(char **)(local_18[1] + 0x3e)) {
            do {
              if ((*local_1c == '\x01') && (**(char **)(local_1c + 0x2a) == ';')) {
                local_20 = (int *)0x0;
                FUN_004a60c0(*(undefined4 *)(*(char **)(local_1c + 0x2a) + 0x10), param_1, &local_20
                            );
                for (piVar2 = local_20; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
                  puVar7 = (uint *)FUN_005b53d0(piVar2[1], 1, 1);
                  if (puVar7 == (uint *)0x0) {
                    CError_Internal(s_IroDependsKills_c_006b9b3a, 900);
                  }
                  uVar3 = *puVar7;
                  if (uVar3 == 0) {
                    CError_Internal(s_IroDependsKills_c_006b9b3a, 0x386);
                  }
                  if (uVar3 >> 5 < *DAT_00710358) {
                    DAT_00710358[(uVar3 >> 5) + 1] =
                         DAT_00710358[(uVar3 >> 5) + 1] | 1 << ((byte)uVar3 & 0x1f);
                  }
                  else {
                    CError_Internal(s_BitVector_h_00698a16, 0x52);
                  }
                }
                while (local_20 != (int *)0x0) {
                  piVar2 = (int *)*local_20;
                  FUN_004c5330(local_20);
                  local_20 = piVar2;
                }
              }
              local_1c = *(char **)(local_1c + 0x3e);
            } while (local_1c != *(char **)(local_18[1] + 0x3e));
          }
        }
      }
      while (local_18 = puVar9, local_14 != (undefined4 *)0x0) {
        puVar4 = (undefined4 *)local_14[2];
        FUN_004c5330(local_14);
        puVar9 = local_18;
        local_14 = puVar4;
      }
    }
  }
  if (bVar5) {
    FUN_005f5880(DAT_0071085c, param_1);
    FUN_005bf940(DAT_0071085c, DAT_00710358);
  }
  if ((*(int *)(param_1 + 0xe) != 0) && (cVar6 = FUN_005aba80(param_1), cVar6 != '\0')) {
    FUN_005a9dd0(*(undefined4 *)(*(int *)(param_1 + 0xe) + 0x12), &LAB_005f6890, 0);
  }
  return;
}

/*
 * Target: 0x005f6910
 * Candidate: FUN_005f6910
 * State/confidence: source_assigned / medium
 * Basis: translation_unit_inventory
 */
void FUN_005f6910(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  bool bVar4;
  uint *puVar5;
  char *pcVar6;
  undefined4 *local_1c;
  char *local_18;
  char local_11;

  local_18 = *(char **)(param_1 + 0x2a);
  local_11 = '\0';
  if ((local_18 == (char *)0x0) || (*local_18 != '\x02') || (local_18[1] != '\x04') ||
     (iVar1 = *(int *)(local_18 + 0x2a), iVar1 == 0 || (DAT_0070f240 == '\0')) ||
     (*(int *)(iVar1 + 0x1e) == 0 || (DAT_007107e8 == 0))) {
    local_11 = '\x01';
  }
  else {
    local_1c = (undefined4 *)0x0;
    FUN_004a6fb0(DAT_007107e8, iVar1, &local_1c);
    puVar3 = local_1c;
    if (local_1c == (undefined4 *)0x0) {
      local_11 = '\x01';
    }
    else {
      for (; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)puVar3[2]) {
        pcVar6 = (char *)*puVar3;
        if ((pcVar6 == (char *)0x0) || (puVar3[1] == 0)) {
          local_11 = '\x01';
          break;
        }
        bVar4 = false;
        for (; pcVar6 != *(char **)(puVar3[1] + 0x3e); pcVar6 = *(char **)(pcVar6 + 0x3e)) {
          if ((*pcVar6 == '\x01') && (**(char **)(pcVar6 + 0x2a) == ';')) {
            bVar4 = true;
            break;
          }
        }
        if (!bVar4) {
          local_11 = '\x01';
          break;
        }
      }
      puVar3 = local_1c;
      if (local_11 == '\0') {
        for (; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)puVar3[2]) {
          pcVar6 = (char *)*puVar3;
          if (pcVar6 != *(char **)(puVar3[1] + 0x3e)) {
            do {
              if ((*pcVar6 == '\x01') && (**(char **)(pcVar6 + 0x2a) == ';')) {
                iVar1 = *(int *)(*(char **)(pcVar6 + 0x2a) + 0x10);
                if (iVar1 == 0) {
                  CError_Internal(s_IroDependsKills_c_006b9b3a, 0x2f3);
                }
                puVar5 = (uint *)FUN_005b53d0(iVar1, 1, 1);
                if (puVar5 == (uint *)0x0) {
                  CError_Internal(s_IroDependsKills_c_006b9b3a, 0x2f5);
                }
                uVar2 = *puVar5;
                if (uVar2 == 0) {
                  CError_Internal(s_IroDependsKills_c_006b9b3a, 0x2f7);
                }
                if (uVar2 >> 5 < *DAT_00710358) {
                  DAT_00710358[(uVar2 >> 5) + 1] =
                       DAT_00710358[(uVar2 >> 5) + 1] | 1 << ((byte)uVar2 & 0x1f);
                }
                else {
                  CError_Internal(s_BitVector_h_00698a16, 0x52);
                }
              }
              pcVar6 = *(char **)(pcVar6 + 0x3e);
            } while (pcVar6 != *(char **)(puVar3[1] + 0x3e));
          }
        }
      }
      while (local_1c != (undefined4 *)0x0) {
        puVar3 = (undefined4 *)local_1c[2];
        FUN_004c5330(local_1c);
        local_1c = puVar3;
      }
    }
  }
  if (local_11 != '\0') {
    FUN_005f5880(DAT_0071085c, local_18);
    FUN_005bf940(DAT_0071085c, DAT_00710358);
  }
  return;
}

/*
 * Target: 0x005f6b80
 * Candidate: FUN_005f6b80
 * State/confidence: source_candidate / low
 * Basis: same_source_sandwich
 */
void FUN_005f6b80(undefined4 param_1, char param_2, undefined1 param_3, undefined1 param_4)

{
  if (param_2 == '\0') {
    FUN_005bf760(DAT_0071015c);
  }
  else {
    FUN_005bfae0(&DAT_0071015c, DAT_00710084 + 1);
  }
  DAT_00726059 = 0;
  DAT_007260c2 = 0;
  DAT_0072605f = 0;
  DAT_00725f44 = 0;
  FUN_005f6bf0(param_1, param_3, param_4);
  return;
}

/*
 * Target: 0x005f6bf0
 * Candidate: FUN_005f6bf0
 * State/confidence: source_assigned / medium
 * Basis: translation_unit_inventory
 */
void FUN_005f6bf0(byte *param_1, char param_2, char param_3)

{
  char cVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  char *pcVar5;
  int iStack_148;
  undefined4 local_144;
  char acStack_140 [4];
  undefined1 auStack_13c [4];
  undefined4 uStack_138;
  char acStack_132 [286];
  undefined2 local_14;

  if ((*(int *)(param_1 + 0x12) != 0) &&
     (cVar1 = FUN_004531f0(*(undefined4 *)(param_1 + 0x12), *(uint *)(param_1 + 6) & 0x1f200003),
     cVar1 != '\0')) {
    DAT_0072605f = 1;
    DAT_007260c2 = '\x01';
  }
  if ((*param_1 != 0) && (*param_1 < 8) && (cVar1 = FUN_005ac460(param_1), cVar1 != '\0')) {
    DAT_007260c2 = '\x01';
  }
  if ((DAT_007260c2 != '\0') && (DAT_00725f44 == '\0') && (param_2 != '\0')) {
    return;
  }
  switch(*param_1) {
  case 1:
  case 5:
    break;
  case 2:
    if (((&DAT_00725f47)[param_1[1]] != '\0') && (DAT_007260c2 = '\x01', param_2 != '\0')) {
      return;
    }
    pcVar5 = *(char **)(param_1 + 0x2a);
    if (param_1[1] == 4) {
      if ((*pcVar5 == '\x02') && (pcVar5[1] == '3')) {
        pcVar5 = *(char **)(pcVar5 + 0x2a);
      }
      if ((*pcVar5 == '\x01') && (**(char **)(pcVar5 + 0x2a) == ';')) {
        puVar3 = (uint *)FUN_005b53d0(*(undefined4 *)(*(char **)(pcVar5 + 0x2a) + 0x10), 0, 1);
        if (puVar3 == (uint *)0x0) {
          DAT_007260c2 = '\x01';
        }
        else {
          cVar1 = is_volatile_object(puVar3[1]);
          if (cVar1 != '\0') {
            DAT_0072605f = 1;
            DAT_007260c2 = '\x01';
          }
          uVar4 = *puVar3 >> 5;
          if (uVar4 < *DAT_0071015c) {
            DAT_0071015c[uVar4 + 1] = DAT_0071015c[uVar4 + 1] | 1 << ((byte)*puVar3 & 0x1f);
          }
          else {
            CError_Internal(s_BitVector_h_00698a16, 0x52);
          }
        }
      }
      else {
        FUN_005f7620(param_1);
      }
    }
    if (param_3 != '\0') {
      FUN_005f6bf0(pcVar5, param_2, param_3);
    }
    break;
  case 3:
    if (((&DAT_00725f47)[param_1[1]] != '\0') && (DAT_007260c2 = '\x01', param_2 != '\0')) {
      return;
    }
    if ((byte)(param_1[1] - 0xb) < 2) {
      cVar1 = FUN_005b07f0(*(undefined4 *)(param_1 + 0x2e));
      if (cVar1 == '\0') {
        DAT_00726059 = 1;
      }
      else {
        cVar1 = CInt64_Equal(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x2e) + 0x2a) + 0x10),
                             *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x2e) + 0x2a) + 0x14),
                             DAT_00704908, DAT_0070490c);
        if (cVar1 != '\0') {
          DAT_00726059 = 1;
        }
      }
    }
    if (param_3 != '\0') {
      FUN_005f6bf0(*(undefined4 *)(param_1 + 0x2a), param_2, param_3);
      FUN_005f6bf0(*(undefined4 *)(param_1 + 0x2e), param_2, param_3);
    }
    break;
  case 4:
    if (((&DAT_00725f47)[param_1[1]] != '\0') && (DAT_007260c2 = '\x01', param_2 != '\0')) {
      return;
    }
    if (param_3 != '\0') {
      FUN_005f6bf0(*(undefined4 *)(param_1 + 0x2a), param_2, param_3);
      FUN_005f6bf0(*(undefined4 *)(param_1 + 0x2e), param_2, param_3);
      FUN_005f6bf0(*(undefined4 *)(param_1 + 0x32), param_2, param_3);
    }
    break;
  case 6:
    if ((param_3 != '\0') && (*(int *)(param_1 + 0x2c) != 0)) {
      FUN_005f6bf0(*(int *)(param_1 + 0x2c), param_2, param_3);
    }
    break;
  case 7:
    DAT_007260c2 = '\x01';
    if ((DAT_0070f279 == '\0') || ((*(ushort *)(*(int *)(param_1 + 0x36) + 0x1c) & 3) != 3)) {
      if (param_2 != '\0') {
        return;
      }
    }
    else {
      DAT_00725f44 = '\x01';
    }
    FUN_005f7240(param_1);
    if ((*(int *)(param_1 + 0xe) != 0) && (cVar1 = FUN_005aba80(param_1), cVar1 != '\0')) {
      FUN_005a9dd0(*(undefined4 *)(*(int *)(param_1 + 0xe) + 0x12), &LAB_005f7580, 0);
    }
    if (param_3 != '\0') {
      FUN_005f6bf0(*(undefined4 *)(param_1 + 0x32), 0, param_3);
      iVar2 = (int)*(short *)(param_1 + 0x2c);
      while (iVar2 = iVar2 - 1, iVar2 > -1) {
        FUN_005f6bf0(*(undefined4 *)(*(int *)(param_1 + 0x2e) + iVar2 * 4), 0, param_3);
      }
    }
    break;
  default:
    CError_Internal(s_IroDependsKills_c_006b9b3a, 0x28d);
    break;
  case 0x14:
    if ((DAT_00711b98 != (code *)0x0) && (*(int *)(param_1 + 0x2a) != 0)) {
      iVar2 = 0;
      do {
        *(undefined4 *)((int)&local_144 + iVar2) = *(undefined4 *)((int)&DAT_007172d2 + iVar2);
        *(undefined4 *)(auStack_13c + (iVar2 - 4)) = *(undefined4 *)((int)&DAT_007172d6 + iVar2);
        *(undefined4 *)(auStack_13c + iVar2) = *(undefined4 *)((int)&DAT_007172da + iVar2);
        *(undefined4 *)((int)&uStack_138 + iVar2) = *(undefined4 *)((int)&DAT_007172de + iVar2);
        iVar2 = iVar2 + 0x10;
      } while (iVar2 < 0x130);
      local_14 = DAT_00717402;
      (*DAT_00711b98)(*(undefined4 *)(param_1 + 0x2a), &local_144);
      iStack_148 = 0;
      if (stack0xfffffec6 > 0) {
        iVar2 = 0;
        do {
          puVar3 = (uint *)FUN_005b53d0(*(undefined4 *)(acStack_132 + iVar2 + 2), 0, 1);
          cVar1 = acStack_132[iVar2];
          if ((byte)(cVar1 - 1U) < 2) {
            DAT_007260c2 = '\x01';
            if (param_2 != '\0') {
              return;
            }
            uVar4 = *puVar3 >> 5;
            if (uVar4 < *DAT_0071015c) {
              DAT_0071015c[uVar4 + 1] = DAT_0071015c[uVar4 + 1] | 1 << ((byte)*puVar3 & 0x1f);
            }
            else {
              CError_Internal(s_BitVector_h_00698a16, 0x52);
            }
          }
          else if ((cVar1 == '\0') || (cVar1 == '\x04')) {
            uVar4 = *puVar3 >> 5;
            if (uVar4 < *DAT_0071015c) {
              DAT_0071015c[uVar4 + 1] = DAT_0071015c[uVar4 + 1] | 1 << ((byte)*puVar3 & 0x1f);
            }
            else {
              CError_Internal(s_BitVector_h_00698a16, 0x52);
            }
          }
          iVar2 = iVar2 + 0xe;
          iStack_148 = iStack_148 + 1;
        } while (iStack_148 < stack0xfffffec6);
      }
      if (((local_144._2_1_ != '\0') || (local_144._1_1_ != '\0')) &&
         (FUN_005bf740(DAT_0071015c), local_144._1_1_ != '\0') &&
         (DAT_007260c2 = '\x01', param_2 != '\0')) {
        return;
      }
      if (acStack_140[0] != '\0') {
        DAT_007260c2 = '\x01';
        if (param_2 != '\0') {
          return;
        }
        FUN_005f57b0(DAT_0071085c, param_1);
        FUN_005bf940(DAT_0071085c, DAT_0071015c);
        if ((*(int *)(param_1 + 0xe) != 0) && (cVar1 = FUN_005aba80(param_1), cVar1 != '\0')) {
          FUN_005a9dd0(*(undefined4 *)(*(int *)(param_1 + 0xe) + 0x12), &LAB_005f7580, 0);
        }
      }
    }
  }
  return;
}

/*
 * Target: 0x005f7240
 * Candidate: FUN_005f7240
 * State/confidence: source_assigned / medium
 * Basis: translation_unit_inventory
 */
void FUN_005f7240(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  bool bVar4;
  undefined4 *puVar5;
  char cVar6;
  uint *puVar7;
  char *pcVar8;
  undefined4 *puVar9;
  int *local_20;
  char *local_1c;
  undefined4 *local_18;
  undefined4 *local_14;

  iVar1 = *(int *)(param_1 + 0x32);
  bVar4 = false;
  if ((iVar1 == 0) || (DAT_0070f240 == '\0') || (*(int *)(iVar1 + 0x1e) == 0) || (DAT_007107e8 == 0)
     ) {
    bVar4 = true;
  }
  else {
    local_14 = (undefined4 *)0x0;
    FUN_004a6fb0(DAT_007107e8, iVar1, &local_14);
    if (local_14 == (undefined4 *)0x0) {
      bVar4 = true;
    }
    else {
      puVar9 = local_14;
      if (local_14 != (undefined4 *)0x0) {
        while ((pcVar8 = (char *)*puVar9, pcVar8 != (char *)0x0 && (puVar9[1] != 0))) {
          local_18 = (undefined4 *)((uint)local_18 & 0xffffff00);
          if (pcVar8 != *(char **)(puVar9[1] + 0x3e)) {
            do {
              if ((*pcVar8 == '\x01') && (**(char **)(pcVar8 + 0x2a) == ';')) {
                local_18 = (undefined4 *)CONCAT31(local_18._1_3_, 1);
                iVar1 = *(int *)(*(char **)(pcVar8 + 0x2a) + 0x10);
                if (iVar1 == 0) {
                  CError_Internal(s_IroDependsKills_c_006b9b3a, 0x115);
                }
                local_20 = (int *)0x0;
                FUN_004a5fb0(iVar1, param_1, &local_20);
                for (piVar2 = local_20; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
                  if (piVar2[1] == 0) {
                    bVar4 = true;
                    break;
                  }
                }
                if (local_20 != (int *)0x0) {
                  do {
                    piVar2 = (int *)*local_20;
                    FUN_004c5330(local_20);
                    local_20 = piVar2;
                  } while (piVar2 != (int *)0x0);
                  local_20 = (int *)0x0;
                }
                if (bVar4) break;
              }
              pcVar8 = *(char **)(pcVar8 + 0x3e);
            } while (pcVar8 != *(char **)(puVar9[1] + 0x3e));
          }
          if ((char)local_18 == '\0') {
            bVar4 = true;
          }
          if ((bVar4) || (puVar9 = (undefined4 *)puVar9[2], puVar9 == (undefined4 *)0x0))
          goto LAB_005f74f2;
        }
        bVar4 = true;
      }
LAB_005f74f2:
      puVar9 = local_14;
      puVar5 = local_18;
      if (!bVar4) {
        while (local_18 = puVar9, puVar5 = (undefined4 *)0, local_18 != (undefined4 *)0x0) {
          local_1c = (char *)*local_18;
          if (local_1c != *(char **)(local_18[1] + 0x3e)) {
            do {
              if ((*local_1c == '\x01') && (**(char **)(local_1c + 0x2a) == ';')) {
                local_20 = (int *)0x0;
                FUN_004a5fb0(*(undefined4 *)(*(char **)(local_1c + 0x2a) + 0x10), param_1, &local_20
                            );
                for (piVar2 = local_20; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
                  puVar7 = (uint *)FUN_005b53d0(piVar2[1], 1, 1);
                  if (puVar7 == (uint *)0x0) {
                    CError_Internal(s_IroDependsKills_c_006b9b3a, 0x148);
                  }
                  uVar3 = *puVar7;
                  if (uVar3 == 0) {
                    CError_Internal(s_IroDependsKills_c_006b9b3a, 0x14a);
                  }
                  cVar6 = is_volatile_object(piVar2[1]);
                  if (cVar6 != '\0') {
                    DAT_0072605f = 1;
                    DAT_007260c2 = 1;
                  }
                  if (uVar3 >> 5 < *DAT_0071015c) {
                    DAT_0071015c[(uVar3 >> 5) + 1] =
                         DAT_0071015c[(uVar3 >> 5) + 1] | 1 << ((byte)uVar3 & 0x1f);
                  }
                  else {
                    CError_Internal(s_BitVector_h_00698a16, 0x52);
                  }
                }
                while (local_20 != (int *)0x0) {
                  piVar2 = (int *)*local_20;
                  FUN_004c5330(local_20);
                  local_20 = piVar2;
                }
              }
              local_1c = *(char **)(local_1c + 0x3e);
            } while (local_1c != *(char **)(local_18[1] + 0x3e));
          }
          puVar9 = (undefined4 *)local_18[2];
        }
      }
      while (local_18 = puVar5, local_14 != (undefined4 *)0x0) {
        puVar9 = (undefined4 *)local_14[2];
        FUN_004c5330(local_14);
        puVar5 = local_18;
        local_14 = puVar9;
      }
    }
  }
  if (bVar4) {
    FUN_005f57b0(DAT_0071085c, param_1);
    FUN_005bf940(DAT_0071085c, DAT_0071015c);
  }
  return;
}

/*
 * Target: 0x005f7620
 * Candidate: FUN_005f7620
 * State/confidence: source_assigned / medium
 * Basis: translation_unit_inventory
 */
void FUN_005f7620(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  bool bVar4;
  char cVar5;
  uint *puVar6;
  char *pcVar7;
  uint uVar8;
  undefined4 *local_24;
  int local_20;
  int local_1c;
  int iStack_18;
  char local_11;

  local_11 = '\0';
  if ((param_1 == 0) || (DAT_0070f240 == '\0') || (*(int *)(param_1 + 0x1e) == 0) ||
     (DAT_007107e8 == 0)) {
    local_11 = '\x01';
  }
  else {
    local_24 = (undefined4 *)0x0;
    FUN_004a6fb0(DAT_007107e8, param_1, &local_24);
    puVar2 = local_24;
    if (local_24 == (undefined4 *)0x0) {
      local_11 = '\x01';
    }
    else {
      for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)puVar2[2]) {
        pcVar7 = (char *)*puVar2;
        if ((pcVar7 == (char *)0x0) || (puVar2[1] == 0)) {
          local_11 = '\x01';
          break;
        }
        bVar4 = false;
        for (; pcVar7 != *(char **)(puVar2[1] + 0x3e); pcVar7 = *(char **)(pcVar7 + 0x3e)) {
          if ((*pcVar7 == '\x01') && (**(char **)(pcVar7 + 0x2a) == ';')) {
            bVar4 = true;
            break;
          }
        }
        if (!bVar4) {
          local_11 = '\x01';
          break;
        }
      }
      puVar2 = local_24;
      if (local_11 == '\0') {
        for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)puVar2[2]) {
          pcVar7 = (char *)*puVar2;
          if (pcVar7 != *(char **)(puVar2[1] + 0x3e)) {
            do {
              if ((*pcVar7 == '\x01') && (**(char **)(pcVar7 + 0x2a) == ';')) {
                iVar1 = *(int *)(*(char **)(pcVar7 + 0x2a) + 0x10);
                if (iVar1 == 0) {
                  CError_Internal(s_IroDependsKills_c_006b9b3a, 0x82);
                }
                puVar6 = (uint *)FUN_005b53d0(iVar1, 1, 1);
                if (puVar6 == (uint *)0x0) {
                  CError_Internal(s_IroDependsKills_c_006b9b3a, 0x84);
                }
                uVar8 = *puVar6;
                if (uVar8 == 0) {
                  CError_Internal(s_IroDependsKills_c_006b9b3a, 0x86);
                }
                cVar5 = is_volatile_object(iVar1);
                if (cVar5 != '\0') {
                  DAT_0072605f = 1;
                  DAT_007260c2 = 1;
                }
                if (uVar8 >> 5 < *DAT_0071015c) {
                  DAT_0071015c[(uVar8 >> 5) + 1] =
                       DAT_0071015c[(uVar8 >> 5) + 1] | 1 << ((byte)uVar8 & 0x1f);
                }
                else {
                  CError_Internal(s_BitVector_h_00698a16, 0x52);
                }
              }
              pcVar7 = *(char **)(pcVar7 + 0x3e);
            } while (pcVar7 != *(char **)(puVar2[1] + 0x3e));
          }
        }
      }
      while (local_24 != (undefined4 *)0x0) {
        puVar2 = (undefined4 *)local_24[2];
        FUN_004c5330(local_24);
        local_24 = puVar2;
      }
    }
  }
  if (local_11 != '\0') {
    pcVar7 = *(char **)(param_1 + 0x2a);
    if ((*pcVar7 == '\x02') && (pcVar7[1] == '3')) {
      pcVar7 = *(char **)(pcVar7 + 0x2a);
    }
    if ((*pcVar7 == '\x03') && (pcVar7[1] == '\x0f')) {
      FUN_005ab3b0(pcVar7, &iStack_18, &local_20, &local_1c);
      if (local_20 == 1) {
        uVar3 = *(undefined4 *)(*(int *)(iStack_18 + 0x2a) + 0x10);
        puVar6 = (uint *)FUN_005b53d0(uVar3, 1, 1);
        cVar5 = is_volatile_object(uVar3);
        if (cVar5 != '\0') {
          DAT_0072605f = 1;
          DAT_007260c2 = 1;
        }
        uVar8 = *puVar6 >> 5;
        if (uVar8 < *DAT_0071015c) {
          DAT_0071015c[uVar8 + 1] = DAT_0071015c[uVar8 + 1] | 1 << ((byte)*puVar6 & 0x1f);
        }
        else {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
      }
      else {
        DAT_00726059 = 1;
        if (*DAT_0071015c == 0) {
          CError_Internal(s_BitVector_h_00698a16, 0x52);
        }
        else {
          DAT_0071015c[1] = DAT_0071015c[1] | 1;
        }
        FUN_005f57b0(DAT_0071085c, param_1);
        FUN_005bf940(DAT_0071085c, DAT_0071015c);
      }
      if (local_1c != 0) {
        DAT_00726059 = 1;
      }
    }
    else {
      DAT_00726059 = 1;
      if (*DAT_0071015c == 0) {
        CError_Internal(s_BitVector_h_00698a16, 0x52);
      }
      else {
        DAT_0071015c[1] = DAT_0071015c[1] | 1;
      }
      FUN_005f57b0(DAT_0071085c, param_1);
      FUN_005bf940(DAT_0071085c, DAT_0071015c);
    }
  }
  return;
}
