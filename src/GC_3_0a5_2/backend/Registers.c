/* Native register allocation state, separate from target-specific RegisterInfo.c. */
#include "compiler/common.h"
#pragma pack(push,2)
typedef struct NativeRegisterObject NativeRegisterObject;
typedef struct NativeRegisterInfo {UInt8 unknown00[14],flags,regclass;SInt16 reg,regHi;} NativeRegisterInfo;
#pragma pack(pop)
static char filename[]="Registers.c";
SInt32 used_virtual_registers[5],last_temporary_register[5],first_temporary_register[5];
extern SInt32 n_real_registers[5],n_nonvolatile_registers[5],n_scratch_registers[5],assignable_registers[5];
SInt32 used_nonvolatile_registers[5];
extern SInt32 nonvolatile_registers[5][32],scratch_registers[5][32];
UInt8 reg_state[5][32];
SInt32 optimizing,coloring;
extern void CError_Internal(const char *,int);
extern void fn_005ed260(int);
extern void init_target_registers(void);
extern NativeRegisterInfo *Registers_GetVarInfo(NativeRegisterObject *);
void close_temp_registers(void) {
    SInt8 cls;
    for(cls=0;cls<5;cls++) {
        if(used_virtual_registers[cls]<last_temporary_register[cls])used_virtual_registers[cls]=last_temporary_register[cls];
        else last_temporary_register[cls]=used_virtual_registers[cls];
    }
}
void check_temp_registers(void) {
    SInt8 cls;SInt32 limit=256;
    for(cls=0;cls<5;cls++)if(used_virtual_registers[cls]!=(SInt16)used_virtual_registers[cls])fn_005ed260(13);
    if(optimizing)limit=20000;
    for(cls=0;cls<5;cls++) {
        if(last_temporary_register[cls]<used_virtual_registers[cls])last_temporary_register[cls]=used_virtual_registers[cls];
        if(used_virtual_registers[cls]>limit)used_virtual_registers[cls]=first_temporary_register[cls];
    }
}
void open_temp_registers(void) {
    SInt8 cls;
    for(cls=0;cls<5;cls++)first_temporary_register[cls]=last_temporary_register[cls]=used_virtual_registers[cls];
}
int fn_00594590(SInt8 cls) {
    int reg=-1;
    while(used_nonvolatile_registers[cls]<n_nonvolatile_registers[cls]) {
        int candidate=nonvolatile_registers[cls][used_nonvolatile_registers[cls]++];
        if(!reg_state[cls][candidate]){reg=candidate;break;}
    }
    return reg;
}
int fn_005945f0(SInt8 cls,int reg) {
    int i;
    if(reg<n_real_registers[cls])for(i=0;i<n_scratch_registers[cls];i++)if(scratch_registers[cls][i]==reg)return 1;
    return 0;
}
int fn_00594650(SInt8 cls,int reg) {
    int i;
    if(reg<n_real_registers[cls])for(i=0;i<n_nonvolatile_registers[cls];i++)if(nonvolatile_registers[cls][i]==reg)return 1;
    return 0;
}
UInt32 fn_005946b0(SInt8 cls) {
    UInt32 result=0;int i,count=n_scratch_registers[cls];
    for(i=0;i<count;i++) {
        int reg=scratch_registers[cls][i];
        if(!reg_state[cls][reg])result|=1U<<((UInt32)reg&31);
    }
    return result;
}
int fn_00594700(SInt8 cls) {
    int result=0,i,count=n_real_registers[cls];
    for(i=0;i<count;i++)if(!reg_state[cls][i])result++;
    return result;
}

#pragma dont_inline on
void retain_register(NativeRegisterObject *object,SInt8 cls,SInt16 reg) {
    NativeRegisterInfo *info;
    if(reg>=32)CError_Internal(filename,168);
    if(!reg_state[cls][reg]) {
        if(assignable_registers[cls]>0)assignable_registers[cls]--;
        reg_state[cls][reg]=1;
        if(reg==nonvolatile_registers[cls][used_nonvolatile_registers[cls]])used_nonvolatile_registers[cls]++;
    }
    if(object) {
        info=Registers_GetVarInfo(object);info->regclass=cls;info->flags|=2;info->reg=reg;
    }
}

#pragma dont_inline reset
void assign_register_to_variable(NativeRegisterObject *object,SInt8 cls) {
    NativeRegisterInfo *info=Registers_GetVarInfo(object);
    int reg;
    if(optimizing)reg=used_virtual_registers[cls]++;
    else {
        reg=fn_00594590(cls);
        retain_register(object,cls,reg);
    }
    info->flags|=2;info->regclass=cls;info->reg=reg;
}
void init_registers(void) {
    SInt8 cls;int i;
    for(cls=0;cls<5;cls++)for(i=0;i<32;i++)reg_state[cls][i]=0;
    for(cls=0;cls<5;cls++)used_nonvolatile_registers[cls]=0;
    optimizing=1;
    init_target_registers();
    for(cls=0;cls<5;cls++)used_virtual_registers[cls]=n_real_registers[cls];
    coloring=1;
}
