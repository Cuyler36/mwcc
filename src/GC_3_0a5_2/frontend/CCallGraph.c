/* Native GC 3.0a5.2 call graph; private records until frontend callers migrate. */
#include "compiler/common.h"

#pragma pack(push, 2)
typedef struct NativeCGNode NativeCGNode;
typedef struct NativeCGObject {
    UInt8 kind, access, datatype, unknown03[5];
    void *nameSpace, *name, *type;
    UInt32 qualifiers;
    UInt16 storageClass, flags;
    NativeCGNode *graphNode;
} NativeCGObject;
typedef struct NativeCGEdge {
    struct NativeCGEdge *next;
    NativeCGNode *node;
    UInt32 count;
    UInt16 flags;
} NativeCGEdge;
struct NativeCGNode {
    NativeCGNode *next, *previous;
    NativeCGObject *object;
    UInt8 unknown0c[4];
    NativeCGEdge *outgoing, *incoming;
    SInt32 index;
    UInt8 kind, initCode, marked, marked2;
};
typedef struct NativeCallGraph {
    NativeCGNode *first, *last;
    SInt32 count;
} NativeCallGraph;
typedef struct NativeCGIR {
    void *unknown0;
    NativeCGObject *object;
    UInt8 unknown08[46];
} NativeCGIR;
typedef struct NativeCGIRSlot { void *packed; } NativeCGIRSlot;
typedef struct NativeCGReference {
    NativeCGObject *object;
    UInt8 kind, flags;
    UInt16 count;
} NativeCGReference;
typedef struct NativeCGPacked {
    UInt8 unknown00[20];
    UInt32 count;
    UInt8 unknown18[2];
    NativeCGReference references[1];
} NativeCGPacked;
typedef struct NativeCGObjectList {
    struct NativeCGObjectList *next;
    NativeCGObject *object;
} NativeCGObjectList;
typedef struct NativeCGListSlot {
    UInt8 unknown00[16];
    NativeCGObjectList *objects;
} NativeCGListSlot;
#pragma pack(pop)

NativeCallGraph ccallgraph;
void *ccallgraph_outfile;
extern UInt8 fn_0070f1f4, fn_0070f1d4;
extern void *cscope_root;
extern UInt8 rt_func[];
extern void CError_Internal(const char *, int);
extern void *galloc2(SInt32);
extern void fn_0046c6e0(void *, SInt32);
extern void memclrw(void *, SInt32);
extern UInt8 fn_00456a50(NativeCGObject *);
extern NativeCGIRSlot *fn_0047d080(NativeCGObject *);
extern NativeCGObject **fn_0047ce20(NativeCGObject *);
extern NativeCGListSlot *fn_0047cde0(NativeCGObject *);
extern void fn_0047cf40(NativeCGObject *, void *);
extern void fn_00509f00(void *);
extern void *CIRStream_PackCode(NativeCGIR *);
extern void CIRStream_UnpackCode(void *, NativeCGIR *, int);
extern NativeCGObject *CParser_NewFunctionObject(int);
extern void *CParser_AppendUniqueName(const char *);
extern void Dump_CloseToFile(void *), Dump_CloseToWindow(void *, int), Dump_FreeHandle(void *);

NativeCGNode *fn_005a1560(NativeCGObject *object);
void fn_005a1620(NativeCGNode *node);
void CCallGraph_RemoveNode(NativeCGNode *node);

UInt8 fn_005a0f00(NativeCGObject *object)
{
    NativeCGNode *node;
    if (!object) return 1;
    if (object->flags & 8) return 1;
    if (object->qualifiers & 0x20000) {
        if (fn_0070f1f4 && fn_00456a50(object)) return 1;
        return 0;
    }
    if (object->qualifiers & 0x10) return 0;
    if (object->storageClass == 0x102) return 0;
    for (node = object->nameSpace; node; node = node->next)
        if (node->marked) return 0;
    return 1;
}

UInt8 CCallGraph_RemoveDeadNodes(void)
{
    NativeCGNode *node, *next, *scan;
    UInt8 removed;
    SInt32 count;
    for (node = ccallgraph.first; node; node = node->next) node->marked = 0;
    for (node = ccallgraph.first; node; node = node->next)
        if (!node->marked && (node->initCode || fn_005a0f00(node->object))) fn_005a1620(node);
    removed = 0;
    for (node = ccallgraph.first; node; node = next) {
        next = node->next;
        if (!node->marked) {
            CCallGraph_RemoveNode(node);
            removed = 1;
        }
    }
    if (removed) {
        count = 0;
        for (scan = ccallgraph.first; scan; scan = scan->next) scan->index = count++;
        ccallgraph.count = count;
    }
    return removed;
}

static inline NativeCGEdge *native_new_edge(NativeCGNode *node, NativeCGNode *target,
    UInt32 count)
{
    NativeCGEdge *edge = galloc2(14);
    memclrw(edge, 14);
    edge->next = node->outgoing;
    edge->node = target;
    edge->count = count;
    node->outgoing = edge;
    return edge;
}

void CCallGraph_Compute(void)
{
    NativeCGNode *node, *target;
    NativeCGEdge *edge, *next, *reverse;
    NativeCGIRSlot *code;
    NativeCGPacked *packed;
    NativeCGReference *ref;
    NativeCGObject *object, **data;
    NativeCGListSlot *list;
    NativeCGObjectList *entry;
    UInt32 i, count, referenceCount;
    UInt8 referenceFlag;
    SInt32 index = 0;
    for (node = ccallgraph.first; node; node = node->next) node->index = index++;
    ccallgraph.count = index;
    for (node = ccallgraph.first; node; node = node->next) {
        for (edge = node->outgoing; edge; edge = next) {
            next = edge->next;
            fn_0046c6e0(edge, 14);
        }
        node->outgoing = 0;
        for (edge = node->incoming; edge; edge = next) {
            next = edge->next;
            fn_0046c6e0(edge, 14);
        }
        node->incoming = 0;
        switch (node->kind) {
            case 1:
                code = fn_0047d080(node->object);
                if (!code) break;
                if (!code->packed) CError_Internal("CCallGraph.c", 609);
                packed = code->packed;
                count = packed->count;
                ref = packed->references;
                for (i = 0; i < count; i++, ref++) {
                    if (ref->kind != 1) continue;
                    referenceFlag = (ref->flags & 1) != 0;
                    referenceCount = ref->count;
                    object = ref->object;
                    switch (object->datatype) {
                        case 0: case 2: case 3: case 4: case 5:
                            target = object->graphNode;
                            if (!target) target = fn_005a1560(object);
                            edge = native_new_edge(node, target, referenceCount);
                            if (referenceFlag) edge->flags |= 1;
                            break;
                    }
                }
                break;
            case 2:
                data = fn_0047ce20(node->object);
                if (!data) CError_Internal("CCallGraph.c", 627);
                object = *data;
                switch (object->datatype) {
                    case 0: case 2: case 3: case 4: case 5:
                        target = object->graphNode;
                        if (!target) target = fn_005a1560(object);
                        native_new_edge(node, target, 1);
                        break;
                }
                break;
            case 3:
                list = fn_0047cde0(node->object);
                if (!list) break;
                for (entry = list->objects; entry; entry = entry->next) {
                    object = entry->object;
                    switch (object->datatype) {
                        case 0: case 2: case 3: case 4: case 5:
                            target = object->graphNode;
                            if (!target) {
                                target = fn_005a1560(object);
                                edge = native_new_edge(node, target, 0);
                                edge->flags |= 1;
                            } else {
                                for (edge = node->outgoing; edge; edge = edge->next)
                                    if (edge->node == target) break;
                                if (edge) edge->flags |= 1;
                                else {
                                    edge = native_new_edge(node, target, 0);
                                    edge->flags |= 1;
                                }
                            }
                            break;
                    }
                }
                break;
            default: CError_Internal("CCallGraph.c", 642); break;
        }
    }
    for (node = ccallgraph.first; node; node = node->next)
        for (edge = node->outgoing; edge; edge = edge->next) {
            reverse = galloc2(14);
            memclrw(reverse, 14);
            reverse->next = edge->node->incoming;
            reverse->node = node;
            reverse->count = edge->count;
            reverse->flags = edge->flags;
            edge->node->incoming = reverse;
        }
}

void CCallGraph_SetIR(NativeCGNode *node, NativeCGIR *ir)
{
    NativeCGIRSlot *slot = fn_0047d080(node->object);
    if (!slot) CError_Internal("CCallGraph.c", 509);
    fn_00509f00(slot->packed);
    slot->packed = CIRStream_PackCode(ir);
}

NativeCGIR CCallGraph_GetIR(NativeCGNode *node)
{
    NativeCGIR ir;
    NativeCGIRSlot *slot = fn_0047d080(node->object);
    if (!slot) CError_Internal("CCallGraph.c", 490);
    CIRStream_UnpackCode(slot->packed, &ir, 0);
    if (!node->initCode) ir.object = node->object;
    return ir;
}

void CCallGraph_RemoveNode(NativeCGNode *node)
{
    NativeCGEdge *edge, **where, *removed, *next;
    if (!node->previous) {
        ccallgraph.first = node->next;
        if (node->next) node->next->previous = 0;
        else ccallgraph.last = 0;
    } else if (!node->next) {
        ccallgraph.last = node->previous;
        if (node->previous) node->previous->next = 0;
        else ccallgraph.first = 0;
    } else {
        node->previous->next = node->next;
        node->next->previous = node->previous;
    }
    for (edge = node->incoming; edge; edge = edge->next) {
        where = &edge->node->outgoing;
        for (;;) {
            if (!*where) CError_Internal("CCallGraph.c", 450);
            removed = *where;
            if (removed->node == node) break;
            where = &removed->next;
        }
        next = removed->next;
        fn_0046c6e0(removed, 14);
        *where = next;
    }
    for (edge = node->outgoing; edge; edge = edge->next) {
        where = &edge->node->incoming;
        for (;;) {
            if (!*where) CError_Internal("CCallGraph.c", 464);
            removed = *where;
            if (removed->node == node) break;
            where = &removed->next;
        }
        next = removed->next;
        fn_0046c6e0(removed, 14);
        *where = next;
    }
    for (edge = node->outgoing; edge; edge = next) {
        next = edge->next;
        fn_0046c6e0(edge, 14);
    }
    for (edge = node->incoming; edge; edge = next) {
        next = edge->next;
        fn_0046c6e0(edge, 14);
    }
    node->object->graphNode = 0;
    fn_0046c6e0(node, 32);
}

NativeCGNode *fn_005a1510(void *ir)
{
    NativeCGNode *node;
    NativeCGObject *object = CParser_NewFunctionObject(0);
    object->nameSpace = cscope_root;
    object->name = CParser_AppendUniqueName("<init-code>");
    object->type = rt_func;
    object->flags |= 8;
    fn_0047cf40(object, ir);
    node = fn_005a1560(object);
    node->initCode = 1;
    return node;
}

NativeCGNode *fn_005a1560(NativeCGObject *object)
{
    NativeCGNode *node;
    UInt8 kind;
    if (object->graphNode) CError_Internal("CCallGraph.c", 345);
    switch (object->datatype) {
        case 0: case 2: kind = 3; break;
        case 3: case 4: kind = object->qualifiers & 0x800000 ? 2 : 1; break;
        case 5: kind = 1; break;
        default: CError_Internal("CCallGraph.c", 365); break;
    }
    node = galloc2(32);
    memclrw(node, 32);
    if (ccallgraph.last) {
        ccallgraph.last->next = node;
        node->previous = ccallgraph.last;
        ccallgraph.last = node;
    } else ccallgraph.first = ccallgraph.last = node;
    node->object = object;
    node->index = ccallgraph.count++;
    object->graphNode = node;
    node->kind = kind;
    return node;
}

/* The retained body expands six marking levels before its recursive call. */
#define NATIVE_MARK_LEVEL(name, next_level) \
    static inline void name(NativeCGNode *node) \
    { \
        NativeCGEdge *edge; \
        node->marked = 1; \
        for (edge = node->outgoing; edge; edge = edge->next) \
            if (!edge->node->marked) next_level(edge->node); \
    }
NATIVE_MARK_LEVEL(native_mark_1, fn_005a1620)
NATIVE_MARK_LEVEL(native_mark_2, native_mark_1)
NATIVE_MARK_LEVEL(native_mark_3, native_mark_2)
NATIVE_MARK_LEVEL(native_mark_4, native_mark_3)
NATIVE_MARK_LEVEL(native_mark_5, native_mark_4)
#undef NATIVE_MARK_LEVEL

void fn_005a1620(NativeCGNode *node)
{
    NativeCGEdge *edge;
    node->marked = 1;
    for (edge = node->outgoing; edge; edge = edge->next)
        if (!edge->node->marked) native_mark_5(edge->node);
}

void fn_005a1720(void)
{
    NativeCGNode *node;
    SInt32 index = 0;
    for (node = ccallgraph.first; node; node = node->next) node->index = index++;
    ccallgraph.count = index;
}
void fn_005a1740(void)
{
    NativeCGNode *node;
    for (node = ccallgraph.first; node; node = node->next) {
        node->marked = 0;
        node->marked2 = 0;
    }
}
void fn_005a1760(void)
{
    NativeCGNode *node;
    for (node = ccallgraph.first; node; node = node->next) node->marked = 0;
}
UInt8 fn_005a1780(NativeCGNode *node)
{
    switch (node->kind) {
        case 1: return fn_0047d080(node->object) != 0;
        case 2: return 1;
        case 3: return fn_0047cde0(node->object) != 0;
        default: CError_Internal("CCallGraph.c", 248); return 0;
    }
}
void CCallGraph_Cleanup(void)
{
    if (ccallgraph_outfile) {
        if (fn_0070f1d4) Dump_CloseToFile(ccallgraph_outfile);
        else Dump_CloseToWindow(ccallgraph_outfile, 0);
        Dump_FreeHandle(ccallgraph_outfile);
        ccallgraph_outfile = 0;
    }
}
void CCallGraph_Setup(void)
{
    memclrw(&ccallgraph, 12);
    ccallgraph_outfile = 0;
}
