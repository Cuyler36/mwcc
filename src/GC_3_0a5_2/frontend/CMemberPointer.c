/* Native CMemberPointer.c records stay private while callers migrate. */
#include "compiler/common.h"
#include <string.h>
#include <stddef.h>
#pragma pack(push,2)
typedef struct NativeMemberType {SInt8 kind;UInt8 pad;SInt32 size;} NativeMemberType;
typedef struct NativeMemberPointer {NativeMemberType base;NativeMemberType *member,*owner;UInt32 quals;} NativeMemberPointer;
typedef struct NativeMemberTypePointer {NativeMemberType base;NativeMemberType *target;UInt32 quals;} NativeMemberTypePointer;
typedef struct NativeMemberFuncArg {struct NativeMemberFuncArg *next;void *name;UInt32 unknown08;NativeMemberType *type;UInt32 quals;} NativeMemberFuncArg;
typedef struct NativeMemberFunction {NativeMemberType base;NativeMemberFuncArg *args;void *exspecs;NativeMemberType *result;UInt32 quals,flags,attrs;} NativeMemberFunction;
typedef struct NativeMemberFunctionContext {NativeMemberFunction function;NativeMemberType *context;UInt8 unknown22[8],mode,unknown2b;} NativeMemberFunctionContext;
typedef struct NativeMemberExpr NativeMemberExpr;
typedef struct NativeMemberWords {UInt32 hi,lo;} NativeMemberWords;
struct NativeMemberExpr {
    UInt8 kind,operation;UInt16 unknown02;NativeMemberType *type;
    UInt32 flags,unknown0c;
    union {NativeMemberWords integer;struct {NativeMemberExpr *left,*right,*third;} operands;} data;
};
#pragma pack(pop)
typedef char CheckMemberType[(sizeof(NativeMemberPointer)==18)?1:-1];
typedef char CheckMemberFunction[(sizeof(NativeMemberFunction)==30)?1:-1];
typedef char CheckMemberFunctionContext[(sizeof(NativeMemberFunctionContext)==44)?1:-1];
extern void *galloc(UInt32);
extern void memclrw(void *,UInt32);
extern NativeMemberType *CDecl_NewPointerType(NativeMemberType *);
extern NativeMemberFuncArg *CParser_NewFuncArg(void);
extern NativeMemberType stvoid;
extern void *this_name_node;
extern SInt16 tk;
extern SInt16 lex(void);
extern UInt32 fn_00514660(void);
extern void CError_Error(int,...);
extern void CDecl_AddThisPointerArgument(NativeMemberFunctionContext *,NativeMemberType *);
extern void *rt_ptmf_null;
extern NativeMemberExpr *CExpr_New_EINDIRECT_Node(void *);
extern NativeMemberExpr *checkreference(NativeMemberExpr *);
extern NativeMemberExpr *intconstnode(NativeMemberType *,SInt32);
extern NativeMemberExpr *fn_00543680(NativeMemberExpr *,NativeMemberType *,UInt32,UInt8,UInt8);
extern NativeMemberExpr *CExpr_NewENode(UInt8);
extern void CError_Internal(const char *,int);
static char filename[]="CMemberPointer.c";


#pragma pack(push,2)
typedef struct NativeMemberExprList {struct NativeMemberExprList *next;NativeMemberExpr *expr;} NativeMemberExprList;
typedef struct NativeMemberObject {UInt8 kind,access,storage,pad03;UInt32 unknown04;void *nspace,*name;NativeMemberType *type;UInt32 quals;UInt8 remainder[56];} NativeMemberObject;
typedef struct NativeMemberObjectList {struct NativeMemberObjectList *next;NativeMemberObject *object;} NativeMemberObjectList;
typedef struct NativeMemberReference {NativeMemberExpr base;UInt32 templateArgs,unknown20,errorState;UInt8 warned,convert,warningBits;} NativeMemberReference;
typedef struct NativeMemberData {UInt8 kind,access;UInt16 unknown02;void *unknown04,*unknown08;NativeMemberType *type;UInt32 quals;SInt32 offset;} NativeMemberData;
typedef struct NativeMemberReloc {struct NativeMemberReloc *next;NativeMemberObject *object;SInt32 offset;UInt32 unknown0c;} NativeMemberReloc;
#pragma pack(pop)
extern NativeMemberType stunsignedlong,stsignedlong,void_ptr,ptmstruct;
extern NativeMemberObject *rt_ptmf_scall,*fn_00716cac,*rt_ptmf_cmpr,*rt_ptmf_test,*rt_ptmf_cast;
extern void *cscope_root;
extern NativeMemberFuncArg elipsis,oldstyle;
extern UInt8 fn_0070f1b3;
extern void *lalloc(UInt32);
extern UInt8 CMach_PassResultInHiddenArg(NativeMemberType *);
extern NativeMemberExpr *fn_00559da0(NativeMemberExpr *,UInt8);
extern NativeMemberExpr *CExpr_New_EOBJREF_Node(NativeMemberObject *,UInt8);
extern NativeMemberExpr *fn_005a7d70(NativeMemberExpr *,NativeMemberExprList *,NativeMemberFunction *,NativeMemberFuncArg *);
extern NativeMemberExpr *fn_005a7ac0(NativeMemberExpr *,UInt8);
extern NativeMemberExpr *argumentpromotion(NativeMemberExpr *,NativeMemberType *,UInt32,UInt8);
extern NativeMemberExpr *nullnode(void);
extern SInt16 fn_00454c20(NativeMemberType *,NativeMemberType *),fn_00454e40(NativeMemberType *,NativeMemberType *);
extern NativeMemberType *CABI_GetPtrDiffTType(void);
extern NativeMemberExpr *makediadicnode(NativeMemberExpr *,NativeMemberExpr *,UInt8),*makemonadicnode(NativeMemberExpr *,UInt8);
extern NativeMemberExpr *fn_005162a0(NativeMemberExpr *),*fn_00520110(NativeMemberExpr *,NativeMemberExpr *);
extern void *CClass_GetBasePath(NativeMemberType *,NativeMemberType *,SInt16 *,UInt8 *);
extern SInt32 CClass_GetPathOffset(void *);
extern void CClass_NewAccessCheck(NativeMemberType *,NativeMemberType *,NativeMemberType *,UInt8,void *,void *);
extern UInt8 CInt64_NotEqual(NativeMemberWords,NativeMemberWords);
extern NativeMemberWords CInt64_Add(NativeMemberWords,NativeMemberWords);
extern NativeMemberExpr *CExpr_NewETEMPNode(NativeMemberType *,UInt8),*CExpr_CopyENode(NativeMemberExpr *);
extern NativeMemberExpr *create_temp_node(NativeMemberType *,UInt8);
extern NativeMemberExpr *funccallexpr(NativeMemberObject *,NativeMemberExpr *,NativeMemberExpr *,NativeMemberExpr *,NativeMemberExpr *);
extern NativeMemberObject *fn_005dca80(NativeMemberObject *,void *,UInt8,UInt8);
extern void *fn_005dedc0(NativeMemberObject *,NativeMemberType *,void *);
extern UInt8 CClass_IsDestructor(NativeMemberObject *);
extern void CMid_ObjectAddrRef(NativeMemberObject *);
extern void CError_Warning(int,...);
extern NativeMemberObject *CParser_NewGlobalDataObject(UInt8);
extern void *CParser_GetUniqueName(void);
extern void CInit_DeclareData(NativeMemberObject *,void *,NativeMemberReloc *,SInt32);
extern void CMach_InitIntMem(NativeMemberType *,NativeMemberWords,void *);
extern NativeMemberExpr *fn_00542ef0(NativeMemberObject *,NativeMemberFunction *,NativeMemberExprList *);
extern NativeMemberExpr *fn_00543360(NativeMemberExpr *,NativeMemberPointer *,NativeMemberPointer *,UInt8);
extern NativeMemberExpr *fn_00543970(NativeMemberType *,NativeMemberType *,NativeMemberObjectList *,void *,NativeMemberPointer *,void *,UInt8,UInt8);
extern NativeMemberReloc *fn_00543c70(void *,NativeMemberObject *);
extern NativeMemberObject *fn_00543db0(NativeMemberObjectList *,void *,NativeMemberPointer *,void *,UInt8 *,UInt8);

NativeMemberExpr *fn_005432e0(NativeMemberExpr *node,NativeMemberType *type,UInt8 convert,UInt8 mode) {
    NativeMemberExpr *result;
    if(node->kind==0x34 && !node->data.integer.hi && !node->data.integer.lo) {
        if(((NativeMemberPointer *)type)->member->kind==7) {
            *(NativeMemberType **)((UInt8 *)rt_ptmf_null+16)=type;
            result=checkreference(CExpr_New_EINDIRECT_Node(rt_ptmf_null));result->type=type;
        }
        else result=intconstnode(type,0);
        return result;
    }
    if(node->kind!=0x4b)return node;
    return fn_00543680(node,type,0,convert,mode);
}
NativeMemberExpr *fn_00543830(NativeMemberExpr *node,NativeMemberExpr *value) {
    NativeMemberExpr *result;
    if(node->kind!=4)CError_Internal(filename,715);
    if(node->type->kind!=6)CError_Internal(filename,716);
    result=CExpr_NewENode(0x43);result->operation=4;result->type=&stvoid;
    result->data.operands.left=node;result->data.operands.right=value;return result;
}

/* The GC3 flags supply qualifiers which 1.2.5 consumed from the token stream. */
void CDecl_MakePTMFuncType(NativeMemberFunction *func) {
    NativeMemberFuncArg *a,*b;
    NativeMemberTypePointer *pointer=(NativeMemberTypePointer *)CDecl_NewPointerType(&stvoid);
    pointer->quals=1;
    a=CParser_NewFuncArg();a->name=this_name_node;a->type=(NativeMemberType *)pointer;
    if(func->flags&0x8000)a->quals|=1;
    if(func->flags&0x10000)a->quals|=2;
    b=CParser_NewFuncArg();b->name=this_name_node;b->type=(NativeMemberType *)pointer;b->quals=1;
    a->next=func->args;b->next=a;func->args=b;func->flags|=0x80;
}
void fn_00543ee0(NativeMemberType **type,NativeMemberType *owner) {
    NativeMemberPointer *p=galloc(18);
    p->base.kind=11;
    if((*type)->kind==7) {CDecl_MakePTMFuncType((NativeMemberFunction *)*type);p->base.size=12;}
    else p->base.size=4;
    p->member=*type;p->owner=owner;tk=lex();p->quals=fn_00514660();*type=(NativeMemberType *)p;
}
void fn_00543f40(NativeMemberType **type,NativeMemberType *owner,UInt32 quals) {
    NativeMemberPointer *p;NativeMemberFunction *f;
    if(*(UInt32 *)((UInt8 *)owner+34)&1) {CError_Error(0x27cf);return;}
    p=galloc(18);memclrw(p,18);p->base.kind=11;p->owner=owner;p->quals=quals;
    if((*type)->kind==7) {
        f=galloc(30);*f=*(NativeMemberFunction *)*type;p->member=(NativeMemberType *)f;p->base.size=12;CDecl_MakePTMFuncType(f);
    } else {p->base.size=4;p->member=*type;}
    *type=(NativeMemberType *)p;
}
NativeMemberFunctionContext *fn_00543ff0(NativeMemberFunction *f,NativeMemberType *context,UInt8 mode) {
    NativeMemberFunctionContext *r=galloc(44);
    memclrw(r,44);r->function=*f;r->context=context;r->mode=mode;r->function.flags|=16;
    if(!mode)CDecl_AddThisPointerArgument(r,context);
    if((mode || (f->flags&0x3000)) && (f->flags&0x18000))CError_Error(0x2890);
    return r;
}
int CPTM_GetMemberFunctionPointerSize(void) {return 12;}
int fn_00544120(void) {return 4;}

NativeMemberExpr *fn_00542e40(NativeMemberExpr *node,NativeMemberExprList *args)
{
    NativeMemberFunction *function=(NativeMemberFunction *)((NativeMemberPointer *)node->data.operands.right->type)->member;
    NativeMemberObject *helper=CMach_PassResultInHiddenArg(function->result)?fn_00716cac:rt_ptmf_scall;
    NativeMemberExprList *first=lalloc(8),*second;
    first->next=args;first->expr=node->data.operands.left->data.operands.left;
    function=(NativeMemberFunction *)((NativeMemberPointer *)node->data.operands.right->type)->member;
    second=lalloc(8);second->next=first;second->expr=fn_00559da0(node->data.operands.right,0);
    if(second->expr->type->kind!=12)CError_Internal(filename,1404);
    second->expr->type=&void_ptr;
    return fn_00542ef0(helper,function,second);
}
NativeMemberExpr *fn_00542ef0(NativeMemberObject *helper,NativeMemberFunction *function,NativeMemberExprList *args)
{
    NativeMemberFuncArg *arg=function->args;NativeMemberExprList *item;
    for(item=args;item;item=item->next) {
        if(!arg) {CError_Error(0x27b2);return nullnode();}
        if(arg==&elipsis||arg==&oldstyle) item->expr=fn_005a7ac0(item->expr,arg==&elipsis);
        else {item->expr=argumentpromotion(item->expr,arg->type,arg->quals,1);arg=arg->next;}
    }
    if(arg) {
        if(arg!=&elipsis&&arg!=&oldstyle) {
            if(arg->unknown08) goto finish;
            CError_Error(0x27b2);
        }
        arg=0;
    }
finish:return fn_005a7d70(CExpr_New_EOBJREF_Node(helper,1),args,function,arg);
}
NativeMemberExpr *fn_00542fc0(UInt8 op,NativeMemberExpr *left,NativeMemberExpr *right)
{
    NativeMemberPointer *type=(NativeMemberPointer *)left->type;NativeMemberExpr *zero,*result;NativeMemberExprList *args,*tail;NativeMemberObject *helper;
    if(type->base.kind==11) {
        if(right->type->kind==11) {
            if(!fn_00454c20(left->type,right->type)) left=fn_00543360(left,(NativeMemberPointer *)left->type,(NativeMemberPointer *)right->type,1);
            if(((NativeMemberPointer *)left->type)->member->kind!=7) {
                left->type=CABI_GetPtrDiffTType();right->type=CABI_GetPtrDiffTType();
                return fn_005162a0(makediadicnode(left,right,op));
            }
        } else {
            if(right->type->kind!=1||right->kind!=0x34||right->data.integer.hi||right->data.integer.lo) {CError_Error(0x27a0);return nullnode();}
            if(type->member->kind!=7) {
                if(type->member->kind==7) {*(NativeMemberType **)((UInt8 *)rt_ptmf_null+16)=(NativeMemberType *)type;zero=checkreference(CExpr_New_EINDIRECT_Node(rt_ptmf_null));zero->type=(NativeMemberType *)type;}
                else zero=intconstnode((NativeMemberType *)type,0);
                left->type=CABI_GetPtrDiffTType();zero->type=CABI_GetPtrDiffTType();return fn_005162a0(makediadicnode(left,zero,op));
            }
        }
    } else {
        if(right->type->kind!=11) CError_Internal(filename,1040);
        if(left->type->kind!=1||left->kind!=0x34||left->data.integer.hi||left->data.integer.lo) {CError_Error(0x27a0);return nullnode();}
        type=(NativeMemberPointer *)right->type;
        if(type->member->kind!=7) {
            if(type->member->kind==7) {*(NativeMemberType **)((UInt8 *)rt_ptmf_null+16)=(NativeMemberType *)type;zero=checkreference(CExpr_New_EINDIRECT_Node(rt_ptmf_null));zero->type=(NativeMemberType *)type;}
            else zero=intconstnode((NativeMemberType *)type,0);
            zero->type=CABI_GetPtrDiffTType();right->type=CABI_GetPtrDiffTType();return fn_005162a0(makediadicnode(zero,right,op));
        }
    }
    args=lalloc(8);helper=rt_ptmf_cmpr;
    if(left->kind==0x34||right->kind==0x34) {args->expr=fn_00559da0(left->kind==0x34?right:left,0);args->next=0;helper=rt_ptmf_test;}
    else {tail=lalloc(8);args->next=tail;args->expr=fn_00559da0(left,0);tail->expr=fn_00559da0(right,0);tail->next=0;}
    result=CExpr_NewENode(0x39);result->type=&stsignedlong;result->operation=4;result->data.operands.left=CExpr_New_EOBJREF_Node(helper,1);result->data.operands.right=(NativeMemberExpr *)args;result->data.operands.third=(NativeMemberExpr *)helper->type;
    result->flags=(result->flags&~0x1f200003)|(*(UInt32 *)((UInt8 *)helper->type+18)&0x1f200003);
    if(op==0x17) result=makemonadicnode(result,7);return result;
}
NativeMemberExpr *fn_00543360(NativeMemberExpr *node,NativeMemberPointer *from,NativeMemberPointer *to,UInt8 access)
{
    void *path;SInt16 pathFlags;UInt8 ambiguous,reversed=0;SInt32 offset;NativeMemberWords amount,zero={0,0};NativeMemberExpr *temporary,*a,*b,*result,*call;
    if(from->owner->kind!=6)CError_Internal(filename,792);
    if(to->owner->kind!=6)CError_Internal(filename,793);
    if(from->owner==to->owner) {node->type=(NativeMemberType *)to;return node;}
    path=CClass_GetBasePath(to->owner,from->owner,&pathFlags,&ambiguous);
    if(path) {if(access)CClass_NewAccessCheck(0,to->owner,from->owner,0,0,0);}
    else {path=CClass_GetBasePath(from->owner,to->owner,&pathFlags,&ambiguous);if(!path)goto error;reversed=1;if(access)CClass_NewAccessCheck(0,from->owner,to->owner,0,0,0);}
    if(ambiguous)CError_Error(0x28b5,from,0,to,0);
    offset=CClass_GetPathOffset(path);if(offset<0)goto error;
    if(reversed)offset=-offset;
    if(from->base.size!=to->base.size)goto error;
    if(!offset) {node->type=(NativeMemberType *)to;return node;}
    if(from->member->kind!=7) {
        if(node->kind==0x34) {
            if(!CInt64_NotEqual(node->data.integer,zero)) {amount.hi=offset<0?0xffffffff:0;amount.lo=offset;node->data.integer=CInt64_Add(node->data.integer,amount);}
            node->type=(NativeMemberType *)to;return node;
        }
        temporary=CExpr_NewETEMPNode((NativeMemberType *)from,1);
        a=makemonadicnode(CExpr_CopyENode(temporary),4);a->type=(NativeMemberType *)from;
        a=makemonadicnode(makediadicnode(a,node,0x1e),0x32);a->type=&stunsignedlong;
        a=makediadicnode(a,intconstnode(&stunsignedlong,0),0x18);
        result=CExpr_NewENode(0x38);result->type=&stunsignedlong;result->data.operands.left=a;
        b=makemonadicnode(temporary,4);b->type=&stunsignedlong;
        result->data.operands.right=makediadicnode(b,intconstnode(&stunsignedlong,offset),0xf);result->data.operands.third=intconstnode(&stunsignedlong,0);
        result=makemonadicnode(result,0x32);result->type=(NativeMemberType *)to;return result;
    }
    temporary=create_temp_node(&ptmstruct,0);
    a=fn_00559da0(node,0);
    b=intconstnode(&stsignedlong,offset);
    call=funccallexpr(rt_ptmf_cast,b,a,temporary,0);
    result=makemonadicnode(call,4);result->type=(NativeMemberType *)to;return result;
error:CError_Error(0x2807,from,0,to,0);return nullnode();
}
NativeMemberExpr *fn_00543680(NativeMemberExpr *node,NativeMemberType *type,UInt32 context,UInt8 convert,UInt8 mode)
{
    NativeMemberReference *ref=(NativeMemberReference *)node;NativeMemberObjectList *objects;NativeMemberData *data;NativeMemberType *owner;NativeMemberPointer *pointer;NativeMemberExpr *result;SInt32 offset;
    if(node->kind!=0x4b)CError_Internal(filename,737);
    if(!ref->convert)return node;
    if(!node->data.operands.left)CError_Internal(filename,739);
    if(!fn_0070f1b3) {
        if(ref->errorState)CError_Error(0x285b);
        if((!(ref->warningBits&2)||!ref->warned)&&type&&type->kind==11) {CError_Warning(0x285b);ref->warned=1;ref->warningBits=(ref->warningBits&~2)|((ref->warned&1)<<1);}
    }
    objects=(NativeMemberObjectList *)node->data.operands.left;data=(NativeMemberData *)objects->object;
    if(data->kind!=4) {
        if(type&&type->kind!=11) {CError_Error(0x285b);return nullnode();}
        return fn_00543970((NativeMemberType *)node->data.operands.right,(NativeMemberType *)node->data.operands.third,objects,(void *)ref->templateArgs,(NativeMemberPointer *)type,(void *)context,convert,mode);
    }
    owner=(NativeMemberType *)node->data.operands.third;
    CClass_NewAccessCheck((NativeMemberType *)node->data.operands.right,(NativeMemberType *)node->data.operands.right,owner,data->access,0,data->unknown08);
    result=nullnode();pointer=galloc(18);memclrw(pointer,18);pointer->base.kind=11;pointer->base.size=4;pointer->owner=owner;pointer->member=data->type;result->type=(NativeMemberType *)pointer;
    result->flags=(result->flags&~0x1f200003)|(data->quals&0x1f200003);offset=(SInt32)((UInt32)data->offset+1);result->data.integer.lo=offset;result->data.integer.hi=offset<0?0xffffffff:0;return result;
}
NativeMemberExpr *fn_00543890(NativeMemberType *type,UInt32 quals,NativeMemberExpr *base,NativeMemberExpr *member)
{
    NativeMemberExpr *a,*b,*result;NativeMemberType *original;
    if(base->type->kind!=6)CError_Internal(filename,668);
    a=fn_00559da0(base,0);original=a->type;a=makemonadicnode(a,0x32);a->type=&stunsignedlong;
    b=makemonadicnode(member,0x32);b->type=&stunsignedlong;b=fn_00520110(b,intconstnode(&stunsignedlong,-1));a=fn_00520110(a,b);
    result=makemonadicnode(a,0x32);result->type=original;
    if(type->kind==8) {result=makemonadicnode(result,0x33);result->type=type;type=((NativeMemberTypePointer *)type)->target;}
    result=makemonadicnode(result,4);result->type=type;result->flags=(result->flags&~0x1f200003)|(quals&0x1f200003);return checkreference(result);
}
NativeMemberExpr *fn_00543970(NativeMemberType *scope,NativeMemberType *owner,NativeMemberObjectList *objects,void *templateArgs,NativeMemberPointer *target,void *context,UInt8 diagnose,UInt8 mode)
{
    NativeMemberObject *object;NativeMemberFunctionContext *function,*copy;NativeMemberPointer *pointer;NativeMemberExpr *result;UInt8 access;
    if(objects->object->kind!=5)CError_Internal(filename,548);
    if(!target) {
        if(objects->next&&objects->next->object->kind==5) {CError_Error(0x27d7);return nullnode();}
        object=objects->object;access=object->access;
        while(object->storage==6)object=*(NativeMemberObject **)((UInt8 *)object+64);
        function=(NativeMemberFunctionContext *)object->type;
        if(object->kind!=5||function->function.base.kind!=7||!(function->function.flags&16))CError_Internal(filename,574);
        if(function->mode)return CExpr_New_EINDIRECT_Node(object);
        if(function->function.flags&0x100000) {object=fn_005dca80(object,templateArgs,0,1);if(!object){CError_Error(0x27d7);return nullnode();}}
    } else {
        object=fn_00543db0(objects,templateArgs,target,context,&access,mode);
        if(!object) {if(diagnose)CError_Error(0x27a2);return nullnode();}
    }
    if(CClass_IsDestructor(object)) {CError_Error(0x27a2);return nullnode();}
    if(fn_0070f1b3) {owner=((NativeMemberFunctionContext *)object->type)->context;scope=0;CClass_NewAccessCheck(scope,owner,owner,object->access,object,0);}
    else CClass_NewAccessCheck(scope,scope,owner,access,object,0);
    pointer=galloc(18);memclrw(pointer,18);pointer->base.kind=11;
    copy=galloc(44);memclrw(copy,44);*copy=*(NativeMemberFunctionContext *)object->type;
    if(!copy->function.args)CError_Internal(filename,612);
    copy->function.args=copy->function.args->next;CDecl_MakePTMFuncType(&copy->function);copy->function.flags&=~2;
    pointer->base.size=12;pointer->owner=copy->context;pointer->member=(NativeMemberType *)copy;
    result=CExpr_NewENode(0x52);result->type=(NativeMemberType *)pointer;result->data.operands.left=(NativeMemberExpr *)object;
    if(*(void **)((UInt8 *)object+72))CMid_ObjectAddrRef(object);return result;
}
NativeMemberExpr *fn_00543c00(NativeMemberObject *function,NativeMemberType *type)
{
    NativeMemberObject *object=CParser_NewGlobalDataObject(0);void *data;NativeMemberReloc *reloc;
    object->name=CParser_GetUniqueName();object->nspace=cscope_root;object->type=type;*(UInt16 *)((UInt8 *)object+24)=0x102;
    data=lalloc(12);reloc=fn_00543c70(data,function);CInit_DeclareData(object,data,reloc,object->type->size);
    return checkreference(CExpr_New_EINDIRECT_Node(object));
}
NativeMemberReloc *fn_00543c70(void *buffer,NativeMemberObject *object)
{
    NativeMemberReloc *reloc=0;NativeMemberWords words={0,0};NativeMemberFunctionContext *function=(NativeMemberFunctionContext *)object->type;SInt32 value;void *vtable;
    memclrw(buffer,12);CMach_InitIntMem(CABI_GetPtrDiffTType(),words,buffer);
    if(object->storage==4) {
        value=*(SInt32 *)((UInt8 *)function+34);words.hi=value<0?0xffffffff:0;words.lo=value;CMach_InitIntMem(CABI_GetPtrDiffTType(),words,(UInt8 *)buffer+4);
        vtable=*(void **)((UInt8 *)function->context+26);value=*(SInt32 *)((UInt8 *)vtable+12);words.hi=value<0?0xffffffff:0;words.lo=value;CMach_InitIntMem(&stunsignedlong,words,(UInt8 *)buffer+8);
    } else {
        words.hi=words.lo=0xffffffff;CMach_InitIntMem(CABI_GetPtrDiffTType(),words,(UInt8 *)buffer+4);
        words.hi=words.lo=0;CMach_InitIntMem(&stunsignedlong,words,(UInt8 *)buffer+8);
        reloc=lalloc(16);memclrw(reloc,16);reloc->object=object;reloc->offset=8;
    }
    return reloc;
}
NativeMemberObject *fn_00543db0(NativeMemberObjectList *objects,void *templateArgs,NativeMemberPointer *target,void *context,UInt8 *access,UInt8 fallback)
{
    UInt8 exact=1;NativeMemberObject *selected=0,*object;NativeMemberObjectList *item;NativeMemberFunctionContext *function;void *instantiation;
again:
    for(item=objects;item;item=item->next) {
        object=item->object;function=(NativeMemberFunctionContext *)object->type;
        if(object->kind!=5||function->function.base.kind!=7||!(function->function.flags&16)||function->mode)continue;
        if(!(function->function.flags&0x100000)) {if(templateArgs)object=0;}
        else {if(selected)object=0;else {instantiation=fn_005dedc0(object,target->member,templateArgs);object=instantiation?*(NativeMemberObject **)((UInt8 *)instantiation+24):0;}}
        if(object&&(!exact||fn_00454e40(object->type,target->member))) {
            if(selected) {CError_Error(0x27d7);goto finish;}
            selected=object;
        }
    }
finish:
    if(!selected&&exact&&fallback) {exact=0;goto again;}
    if(selected) {
        *access=selected->access;while(selected->storage==6)selected=*(NativeMemberObject **)((UInt8 *)selected+64);
        function=(NativeMemberFunctionContext *)selected->type;
        if(selected->kind!=5||function->function.base.kind!=7||!(function->function.flags&16)||function->mode)CError_Internal(filename,416);
    }
    return selected;
}

#define PTM_OFFSET(T,F,N) typedef char ptm_offset_##T##_##F[(offsetof(T,F)==N)?1:-1]
PTM_OFFSET(NativeMemberPointer,member,6);PTM_OFFSET(NativeMemberPointer,owner,10);PTM_OFFSET(NativeMemberPointer,quals,14);
PTM_OFFSET(NativeMemberFunction,result,14);PTM_OFFSET(NativeMemberFunction,flags,22);
PTM_OFFSET(NativeMemberFunctionContext,context,30);PTM_OFFSET(NativeMemberFunctionContext,mode,42);
PTM_OFFSET(NativeMemberFuncArg,type,12);PTM_OFFSET(NativeMemberFuncArg,quals,16);
PTM_OFFSET(NativeMemberExpr,data,16);PTM_OFFSET(NativeMemberReference,templateArgs,28);PTM_OFFSET(NativeMemberReference,errorState,36);
PTM_OFFSET(NativeMemberReference,warned,40);PTM_OFFSET(NativeMemberReference,convert,41);PTM_OFFSET(NativeMemberReference,warningBits,42);
PTM_OFFSET(NativeMemberObject,type,16);PTM_OFFSET(NativeMemberObject,storage,2);
PTM_OFFSET(NativeMemberData,type,12);PTM_OFFSET(NativeMemberData,offset,20);
#undef PTM_OFFSET
