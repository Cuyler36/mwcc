#define CERROR_FILE "RegisterInfo.c"
#include "compiler/common.h"
#include "compiler/Registers.h"
#include "compiler/enode.h"
#include "compiler/objects.h"
#include "compiler/scopes.h"
#include "compiler/types.h"
#include "compiler/BE_symbol.h"
#include "compiler/CError.h"
#include "compiler/CException.h"
#include "compiler/CExpr.h"
#include "compiler/CExpr2.h"
#include "compiler/CFunc.h"
#include "compiler/CInline.h"
#include "compiler/COptimizer.h"
#include "compiler/CPrec.h"
#include "compiler/CPrep.h"
#include "compiler/CTemplateFunc.h"
#include "compiler/CTemplateNew.h"
#include "compiler/CTemplateTools.h"
#include "compiler/CodeGen.h"
#include "compiler/CompilerTools.h"
#include "compiler/CopyPropagation.h"
#include "compiler/DWARF.h"
#include "compiler/IROUseDef.h"
#include "compiler/InlineAsmPPC.h"
#include "compiler/InstrSelection.h"
#include "compiler/InterferenceGraph.h"
#include "compiler/Intrinsics.h"
#include "compiler/IroBitVect.h"
#include "compiler/IroCSE.h"
#include "compiler/IroJump.h"
#include "compiler/IroLoop.h"
#include "compiler/IroVars.h"
#include "compiler/LoopOptimization.h"
#include "compiler/ObjGen_PPC_EABI.h"
#include "compiler/PCode.h"
#include "compiler/PCodeAssembly.h"
#include "compiler/Scheduler.h"
#include "compiler/StackFrameEABI.h"
#include "compiler/Switch.h"
#include <string.h>

/* Imported GC 1.2.5 body; GC 3.0 behavior remains to be ported. */
VarInfo *Registers_GetInfo(Object *object)
{
    VarInfo *info;

    switch (object->datatype) {
        case DDATA:
            if (!object->u.data.info) {
                info = (VarInfo *)galloc(44U);
                memclrw(info, 44U);
                object->u.data.info = info;
            }
            return object->u.data.info;
        case DLOCAL:
            if (!object->u.var.info)
                CError_FATAL(745);
            return object->u.var.info;
        case DABSOLUTE:
            if (!object->u.data.info) {
                info = (VarInfo *)galloc(44U);
                memclrw(info, 44U);
                object->u.data.info = info;
            }
            return object->u.data.info;
        default:
            CError_FATAL(758);
            return NULL;
    }
}
