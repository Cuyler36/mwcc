#define CERROR_FILE "CMiddleLayer.c"
#include "compiler/common.h"
#include "compiler/CInline.h"
#include "compiler/enode.h"
#include "compiler/objects.h"
#include "compiler/scopes.h"
#include "compiler/types.h"
#include "compiler/BE_symbol.h"
#include "compiler/CABI.h"
#include "compiler/CClass.h"
#include "compiler/CDecl.h"
#include "compiler/CError.h"
#include "compiler/CException.h"
#include "compiler/CExpr.h"
#include "compiler/CExpr2.h"
#include "compiler/CFunc.h"
#include "compiler/CInit.h"
#include "compiler/CMachine.h"
#include "compiler/CMangler.h"
#include "compiler/CObjC.h"
#include "compiler/CObjCModern.h"
#include "compiler/CParser.h"
#include "compiler/CPrec.h"
#include "compiler/CPrep.h"
#include "compiler/CPrepTokenizer.h"
#include "compiler/CScope.h"
#include "compiler/CTemplateFunc.h"
#include "compiler/CTemplateNew.h"
#include "compiler/CTemplateTools.h"
#include "compiler/CodeGen.h"
#include "compiler/CompilerTools.h"
#include "compiler/DWARF.h"
#include "compiler/DumpIR.h"
#include "compiler/ELF_Endian.h"
#include "compiler/IROUseDef.h"
#include "compiler/InlineAsm.h"
#include "compiler/InlineAsmPPC.h"
#include "compiler/IroBitVect.h"
#include "compiler/IroCSE.h"
#include "compiler/IroJump.h"
#include "compiler/IroLoop.h"
#include "compiler/IroVars.h"
#include "compiler/ObjGen_PPC_EABI.h"
#include "compiler/PCode.h"
#include "compiler/Registers.h"
#include "compiler/Switch.h"
#include "driver/CLPluginRequests.h"
#include "driver/CLPlugins.h"
#include "driver/CWParserPluginsPrivate.h"
#include "driver/CWPluginsPrivate.h"
#include "driver/Files.h"
#include <string.h>
#include "compiler/ENode.h"

/* Imported GC 1.2.5 body; GC 3.0 behavior remains to be ported. */
Boolean CInline_DispatchNextDeferredNode(void)
{
    CPrecNode *work;
    TypeFunc *functionType;

    if (!anyerrors) {
        work = pending_prec_nodes;
        if (work != NULL) {
            pending_prec_nodes = pending_prec_nodes->next;
            dispatching_deferred_node = 1;
            switch (work->kind) {
                case 3:
                    make_auto_generated_method(work->obj);
                    break;
                case 0:
                    if (!(work->obj->flags & 4))
                        parse_inline_definition(work);
                    break;
                case 1:
                    functionType = (TypeFunc *)work->obj->type;
                    if (!(functionType->flags & FUNC_DEFINED))
                        CTemplateNew_CompileObject(work->u.k1.classTemplate, work->u.k1.context, work->u.k1.source,
                                                   work->obj, 0);
                    break;
                case 2:
                    functionType = (TypeFunc *)work->obj->type;
                    if (!(functionType->flags & FUNC_DEFINED))
                        CTemplateNew_InstantiateFunction(work->u.k2.definition, work->u.k2.specialization, 0);
                    break;
                default:
                    CError_FATAL(4292);
            }
            dispatching_deferred_node = 0;
            return 1;
        }
        if (deferredInlineNodes != NULL && copts.f71 == 0) {
            InlineNode *deferred = deferredInlineNodes;

            deferredInlineNodes = deferred->next;
            generate_inline_code(deferred->func, deferred->body, deferred->flag);
            return 1;
        }
    }
    return 0;
}
