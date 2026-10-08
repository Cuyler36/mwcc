#define CERROR_FILE "StackFrame.c"
#include "compiler/common.h"
#include "compiler/StackFrameEABI.h"
#include "compiler/enode.h"
#include "compiler/objects.h"
#include "compiler/scopes.h"
#include "compiler/types.h"
#include "compiler/BE_symbol.h"
#include "compiler/CDecl.h"
#include "compiler/CError.h"
#include "compiler/CException.h"
#include "compiler/CExpr2.h"
#include "compiler/CFunc.h"
#include "compiler/CInline.h"
#include "compiler/CObjC.h"
#include "compiler/CObjCModern.h"
#include "compiler/CParser.h"
#include "compiler/CPrec.h"
#include "compiler/CPrep.h"
#include "compiler/CScope.h"
#include "compiler/CTemplateFunc.h"
#include "compiler/CTemplateTools.h"
#include "compiler/CodeGen.h"
#include "compiler/CompilerTools.h"
#include "compiler/ConstantPropagation.h"
#include "compiler/DWARF.h"
#include "compiler/IROUseDef.h"
#include "compiler/InlineAsmPPC.h"
#include "compiler/InstrSelection.h"
#include "compiler/InterferenceGraph.h"
#include "compiler/IroBitVect.h"
#include "compiler/IroCSE.h"
#include "compiler/IroJump.h"
#include "compiler/IroLoop.h"
#include "compiler/IroVars.h"
#include "compiler/LoopOptimization.h"
#include "compiler/ObjGen_PPC_EABI.h"
#include "compiler/PCode.h"
#include "compiler/PCodeAssembly.h"
#include "compiler/PCodeUtilities.h"
#include "compiler/PPCError.h"
#include "compiler/Peephole.h"
#include "compiler/Registers.h"
#include "compiler/Switch.h"
#include "driver/Files.h"
#include <string.h>
#include <stdio.h>

typedef enum { kMergeTag = 0x1f } MergeTag;

static inline UInt8 StackFrameEABI_LoadMultipleEnabled(void)
{
    return copts.useRegisterSaveHelpers;
}

static inline UInt8 StackFrameEABI_VRSAVEEnabled(void)
{
    return copts.altivecVrsave;
}

/* Imported GC 1.2.5 body; GC 3.0 behavior remains to be ported. */
void restore_gprs(PCodeBlock *func, Boolean a, Boolean b, SInt16 c)
{
    SInt32 i;
    Object *node;
    char *base;
    PCodeOperand *p;
    char buf[0x20];
    SInt32 regcount;
    NameSpace *old;

    if (b) {
        regcount = 0;
    } else {
        regcount = stack_frame_size;
    }

    if (a != 0 && (gGPRSaveSpan > 4 || (copts.uniformSpillBlockWeight != 0 && gGPRSaveSpan > 1))) {
        PCodeUtilities_EmitInstruction(PC_LMW, gGPRSaveSpan - 1, 0x20 - gGPRSaveSpan, c, 0,
                                       regcount - (data_00587638 + frame_alignment_padding + data_00587634));
        Operands_AllocateGPR(0x20000);
    } else if (a == 0 && (gGPRSaveSpan > 4 || (copts.uniformSpillBlockWeight != 0 && gGPRSaveSpan > 2))) {
        if (regcount > 0x7fff) {
            CError_FatalError(ERR_LOCAL_DATA_32K);
        }
        PCodeUtilities_EmitInstruction(PC_ADDI, 0xb, c, 0, regcount - (data_00587638 + frame_alignment_padding));
        Operands_AllocateGPR(0x400);
        sprintf(buf, "_restgpr_%d", 0x20 - gGPRSaveSpan);
        old = currentNameSpace;
        currentNameSpace = registration_context;
        node = CParser_NewRTFunc(&stvoid, NULL, 2, 0);
        currentNameSpace = old;
        node->name = GetHashNameNode(buf);
        BE_symbol_GetOrCreateFunctionObjectSymbol(node);
        base = (char *)PCodeUtilities_CreateInstruction(1, gGPRSaveSpan, node, 0);
        i = 1;
        p = (PCodeOperand *)(base + 0x28);
        for (; i <= gGPRSaveSpan;) {
            p->kind = PCOp_GPR;
            p->value.reg = 0x20 - i++;
            p->flags = 2;
            p++;
        }
        PCode_AppendInstruction(func, (PCodeInstruction *)base);
    } else {
        for (i = 1; i <= gGPRSaveSpan; i++) {
            PCodeUtilities_EmitInstruction(PC_LWZ, 0x20 - i, c, 0,
                                           regcount - (data_00587638 + frame_alignment_padding + 4 * i));
            Operands_AllocateGPR(0x20000);
        }
    }
}

/* Imported GC 1.2.5 body; GC 3.0 behavior remains to be ported. */
void StackFrameEABI_MergePrologueEpilogue(PCodeBlock *block, char emitReturn)
{
    PCodeBlock *savedBlock;
    PCodeInstruction *instruction;
    SInt32 frameReg;
    Boolean restoreLR;
    SInt32 largeFrame;
    SInt32 savedFrameReg;
    SInt16 restoreBaseReg;

    savedBlock = gCurrentBlock;
    largeFrame = (0x7fff < stack_frame_size);
    frameReg = -1;
    savedFrameReg = -1;
    restoreLR = !data_00588521 || (copts.uniformSpillBlockWeight != 0 && (gFPRSaveSpan > 3 || gVRSaveSpan > 3));
    if (!restoreLR) {
        if (StackFrameEABI_LoadMultipleEnabled() == 0 || copts.nativeByteOrder != 0) {
            restoreLR = (gGPRSaveSpan > 4) || (copts.uniformSpillBlockWeight != 0 && gGPRSaveSpan > 2);
        }
    }
    restoreBaseReg = stack_base_reg;
    gCurrentBlock = block;
    if (data_005882c0.record != NULL) {
        restoreLR = 0;
    }
    if (gHasAltivecFrame != 0) {
        instruction = block->instructions;
        if (data_00588521 != 0) {
            frameReg = 1;
            if (StackFrameEABI_VRSAVEEnabled() != 0) {
                if (block->instructions != NULL && block->instructions->opcode == PC_STW) {
                    savedFrameReg = block->instructions->operandData.operands[1].value.reg;
                    PCode_UnlinkInstruction(block->instructions);
                    if (savedFrameReg == -1) {
                        CError_FATAL(910);
                    }
                }
            }
        } else {
            if (instruction != NULL && instruction->opcode == PC_STW) {
                frameReg = instruction->operandData.operands[1].value.reg;
                PCode_UnlinkInstruction(instruction);
                instruction = block->instructions;
                if (StackFrameEABI_VRSAVEEnabled() != 0 && instruction != NULL && instruction->opcode == PC_STW) {
                    CError_FATAL(922);
                    savedFrameReg = instruction->operandData.operands[1].value.reg;
                    PCode_UnlinkInstruction(instruction);
                }
            } else {
                CError_FATAL(928);
            }
        }
        if (vrsave_mask != 0 && StackFrameEABI_VRSAVEEnabled() != 0) {
            if (data_00588521 != 0 && savedFrameReg != -1) {
                PCodeUtilities_EmitInstruction(PC_MTSPR, 0x100, savedFrameReg);
            } else {
                PCodeUtilities_EmitInstruction(PC_LWZ, 0xb, frameReg, 0,
                                               -(frame_alignment_padding + data_00587638 + stack_frame_adjustment +
                                                 data_00587634 + data_00588070 + data_0058764c + data_005880d8));
            }
        }
        if (vrsave_mask != 0 && gHasAltivecFrame != 0 && StackFrameEABI_VRSAVEEnabled() != 0 && savedFrameReg == -1) {
            PCodeUtilities_EmitInstruction(PC_MTSPR, 0x100, 0xb);
        }
    }
    if (gVRSaveSpan != 0) {
        restore_vrs(block);
    }
    if (!largeFrame && gHasAltivecFrame == 0 && restoreLR) {
        emit_opcode_with_base_offset(PC_LWZ, 0, stack_base_reg, NULL, stack_frame_size + 4);
    }
    if (data_005883ee != 0 && data_005882c0.record == NULL) {
        emit_opcode_with_base_offset(PC_LWZ, 0xc, stack_base_reg, NULL, r12_save_offset);
        PCodeUtilities_EmitInstruction(PC_MTCRF, 0xff, 0xc);
    }
    if (gFPRSaveSpan != 0) {
        emit_restore_fprs(block, 0);
    }
    if (restoreBaseReg == kMergeTag && gGPRSaveSpan != 0) {
        PCodeUtilities_EmitInstruction(PC_MR, 0xc, restoreBaseReg);
        restoreBaseReg = 0xc;
    }
    if (gGPRSaveSpan != 0) {
        restore_gprs(block, (StackFrameEABI_LoadMultipleEnabled() != 0) && !copts.nativeByteOrder, 0, restoreBaseReg);
    }
    if (data_005882c0.record == NULL && stack_frame_size != 0) {
        if (data_0058852d != 0 || largeFrame || gHasAltivecFrame != 0) {
            emit_opcode_with_base_offset(PC_LWZ, 1, 1, NULL, 0);
        } else {
            PCodeUtilities_EmitInstruction(PC_ADDI, 1, 1, 0, stack_frame_size);
        }
    }
    if ((largeFrame || gHasAltivecFrame != 0) && restoreLR) {
        emit_opcode_with_base_offset(PC_LWZ, 0, 1, NULL, 4);
    }
    if (restoreLR) {
        PCodeUtilities_EmitInstruction(PC_MTLR, 0);
    }
    if (data_005882c0.record != NULL) {
        emit_restore_special_registers(restoreBaseReg);
        if (stack_frame_size != 0) {
            if (data_0058852d != 0 || largeFrame || gHasAltivecFrame != 0) {
                emit_opcode_with_base_offset(PC_LWZ, 1, 1, NULL, 0);
            } else {
                PCodeUtilities_EmitInstruction(PC_ADDI, 1, 1, 0, stack_frame_size);
            }
        }
    }
    if (emitReturn != 0) {
        if (data_005882c0.record != NULL) {
            PCodeUtilities_EmitInstruction(PC_RFI);
        } else {
            PCodeUtilities_EmitInstruction(PC_BLR);
        }
        Operands_AllocateGPR(0x800000);
    }
    block->flags |= 2;
    gCurrentBlock = savedBlock;
}
