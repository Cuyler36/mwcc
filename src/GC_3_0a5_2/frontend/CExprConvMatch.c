/* Native CExprConvMatch; conversion algorithms are related to 1.2.5 CExpr2.c. */
#include "compiler/common.h"
#include <stddef.h>
#pragma pack(push,2)
typedef struct ConvType {UInt8 kind,pad;SInt32 size;} ConvType;
typedef struct ConvDerived {ConvType base;ConvType *target;UInt32 quals;} ConvDerived;
typedef struct ConvWords {UInt32 hi,lo;} ConvWords;
typedef struct ConvNode ConvNode;
typedef struct ConvList {struct ConvList *next;ConvNode *node;} ConvList;
typedef struct ConvArg {struct ConvArg *next;void *name,*defaultValue;ConvType *type;UInt32 quals,unknown14;} ConvArg;
typedef struct ConvFunction {ConvType base;ConvArg *args;void *exspec;ConvType *result;UInt32 quals,flags;UInt8 unknown1a[4];ConvType *context;UInt8 unknown22[8],mode,unknown2b;} ConvFunction;
typedef struct ConvObject {UInt8 kind,access,storage,pad;UInt32 unknown04;void *space,*name;ConvType *type;UInt32 quals;UInt16 sclass,flags;UInt8 unknown1c[36];void *value;ConvType *context;UInt8 unknown48[24];} ConvObject;
struct ConvNode {UInt8 kind,cost;UInt16 unknown02;ConvType *type;UInt32 flags,unknown0c;union {struct {ConvNode *left,*right,*third,*fourth,*fifth,*sixth;} op;struct {ConvWords real,imag;} complex;ConvWords value;ConvObject *object;UInt8 raw[30];}data;};
typedef struct ConvTypeItem {struct ConvTypeItem *next;ConvObject *object;ConvType *type;UInt32 quals;} ConvTypeItem;
typedef struct ConvMatch {ConvType *from,*to;UInt32 fromQuals,toQuals;UInt8 qualification,mode1,mode2,reference,special,isLValue,unknown16[4];} ConvMatch;
typedef struct ConvScore {UInt8 kind,pad;ConvMatch standard;UInt8 unknown1c[4];} ConvScore;
typedef struct ConvCandidate {struct ConvCandidate *next;ConvObject *object,*templateObject;ConvType *left;UInt32 leftQuals;ConvType *right;UInt32 rightQuals;ConvScore scores[3];} ConvCandidate;
typedef struct ConvObjectList {struct ConvObjectList *next;ConvObject *object;} ConvObjectList;
typedef struct ConvSelection {ConvObject *object;ConvObjectList *ambiguous;ConvMatch match;void *scope;} ConvSelection;
#pragma pack(pop)
typedef char ConvNodeSize[(sizeof(ConvNode)==46)?1:-1];
typedef char ConvMatchSize[(sizeof(ConvMatch)==26)?1:-1];
typedef char ConvScoreSize[(sizeof(ConvScore)==32)?1:-1];
typedef char ConvArgumentSize[(sizeof(ConvArg)==24)?1:-1];
typedef char ConvFunctionContext[(offsetof(ConvFunction,context)==30)?1:-1];
typedef char ConvFunctionSize[(sizeof(ConvFunction)==44)?1:-1];
typedef char ConvObjectSize[(sizeof(ConvObject)==96)?1:-1];
typedef char ConvCandidateSize[(sizeof(ConvCandidate)==124)?1:-1];
typedef char ConvSelectionSize[(sizeof(ConvSelection)==38)?1:-1];
typedef char ConvFunctionFlags[(offsetof(ConvFunction,flags)==22)?1:-1];
typedef char ConvNodeFlags[(offsetof(ConvNode,flags)==8)?1:-1];
#define CVMASK 0x1f200003UL
#define TARGET(t) (((ConvDerived *)(t))->target)
#define TQUAL(t) (((ConvDerived *)(t))->quals)
#define LEFT(n) ((n)->data.op.left)
#define RIGHT(n) ((n)->data.op.right)
#define THIRD(n) ((n)->data.op.third)
static char filename[]="CExprConvMatch.c";
extern ConvType stvoid,fn_006771c8;
extern ConvType stbool,stsignedint,stunsignedint,stsignedlong,stunsignedlong,stsignedlonglong,stunsignedlonglong,stfloat,stdouble,stlongdouble;
extern ConvWords cint64_zero;
extern void *fn_007101c4;
extern UInt8 fn_0070f1ee;
extern UInt8 fn_0070f1bd;
extern UInt8 fn_0070f1a8,fn_0070f1da,fn_0070f1af,fn_0070f1f1,fn_0070f1f3,fn_0070f1b0,fn_0070f1b3,fn_0070f1cb,fn_0070f203,fn_0070f215,fn_0070f20d,fn_0070f1f9;
extern ConvType fn_00699c24,fn_00699c8c,stunsignedchar,fn_006771c2;
extern void *fn_00711be0;
extern UInt8 fn_0070f1c7;
extern ConvArg fn_007037c0,fn_0070bb08;
extern void *CompilerTools_AllocatePool(UInt32);
extern void memclrw(void *,UInt32),CError_Internal(const char *,int),CError_Error(int,...),CError_OverloadedFunctionError(ConvObject *,void *),fn_0045aae0(ConvObject *,void *,int,void *);
extern SInt16 is_typesame(ConvType *,ConvType *);
extern UInt32 fn_004533b0(ConvType *,UInt32),fn_004533f0(ConvType *,UInt32);
extern UInt8 fn_00454280(UInt32,UInt32),fn_004542f0(UInt32,UInt32),fn_00453240(ConvType *,UInt32),CExpr_IsLValue(ConvNode *);
extern ConvType *fn_005444c0(ConvType *);
extern void *fn_00541ba0(ConvType *,ConvType *,SInt16 *,UInt8 *);
extern void fn_005a85c0(void *,ConvType *);
extern ConvObject *fn_005a8450(void *);
extern ConvNode *CExpr_NewENode(UInt8),*makemonadicnode(ConvNode *,UInt8),*intconstnode(ConvType *,SInt32),*fn_00524250(ConvType *,SInt32),*fn_00524210(ConvType *,ConvWords,ConvWords),*fn_0055b2d0(ConvNode *,ConvType *);
extern ConvNode *fn_00559da0(ConvNode *,UInt8),*fn_005a87c0(void *,ConvNode *,UInt8),*fn_00543680(ConvNode *,ConvType *,UInt32,UInt8,UInt8),*CExpr_New_EOBJREF_Node(ConvObject *,UInt8),*nullnode(void);
extern void CClass_CheckStaticAccess(void *,ConvType *,ConvType *,UInt8,ConvObject *,UInt8);
extern UInt8 fn_0053f270(ConvType *,ConvType *),fn_005dea90(ConvObject *,ConvObject *);
extern ConvWords fn_004e4190(ConvType *,ConvWords),CMach_CalcFloatConvertFromInt(ConvType *,ConvWords),CMach_CalcFloatConvert(ConvType *,ConvWords);
extern void fn_005454e0(ConvType *,ConvType **,UInt8 *);
extern void *GetHashNameNode(const char *);
extern void CDecl_CompleteType(ConvType *),fn_00462db0(void);
extern ConvType *CDecl_NewPointerType(ConvType *);
extern ConvObjectList *CClass_Constructor(ConvType *);
extern ConvArg *fn_00553440(ConvFunction *);
extern ConvObject *fn_005dca80(ConvObject *,void *,ConvList *,UInt8),*fn_0053ec20(ConvObject *),*fn_005dc920(ConvObject *,ConvType *,UInt32);
extern UInt8 fn_005dd010(ConvList *);
extern void *fn_005dedc0(ConvObject *,ConvType *,void *);
extern ConvObject *fn_005de940(ConvObjectList *);
extern UInt8 fn_00544710(ConvType *,ConvType *);
extern UInt8 fn_00454260(ConvType *),fn_004a05b0(void *,void *),fn_00542530(ConvType *,UInt8),fn_00542350(ConvType *);
extern SInt16 fn_00454e40(ConvType *,ConvType *);
extern ConvType *fn_004543f0(void),*fn_00544500(ConvType *);
extern void CError_Warning(int,...),fn_0045c2c0(int,...),fn_00514a80(ConvType *),fn_005a8080(ConvNode *,ConvType *);
extern ConvNode *fn_0055ba60(ConvNode *),*fn_00559240(ConvNode *,UInt8,UInt8),*fn_005a7f40(ConvNode *,UInt8),*fn_005a8680(ConvNode *,UInt8),*fn_00463460(ConvNode *),*fn_005432e0(ConvNode *,ConvType *,UInt8,UInt8),*fn_00543360(ConvNode *,ConvType *,ConvType *,UInt8),*fn_0055aa20(ConvNode *,ConvType *,ConvType *,UInt8,UInt8),*fn_004648e0(ConvNode *,ConvType *,UInt32);
extern SInt16 iszero(ConvNode *);
extern ConvWords CExpr_IntConstConvert(ConvType *,ConvType *,ConvWords);
extern void *galloc(UInt32),*CMangler_OperatorName(SInt32);
extern UInt8 fn_004e6a10(ConvType *,void *,void *),fn_004e6c70(void *,void *,void *);
extern ConvObjectList *fn_004eabd0(ConvObjectList *,void *,ConvList *),*fn_004ea5d0(ConvObjectList *,UInt8);
extern ConvType *fn_005547c0(void);
extern ConvNode *CExpr_MakeFunctionCall(ConvNode *,ConvList *),*CExpr_GenericFuncCall(void *,ConvObject *,ConvList *,UInt8,UInt8);
extern ConvNode *pointer_generation(ConvNode *),*checkreference(ConvNode *),*CExpr_AdjustFunctionCall(ConvNode *),*fn_00553250(ConvType *,ConvType *,UInt8,UInt8),*fn_005a7480(ConvType *,ConvNode *,ConvObject *,void *,ConvList *,UInt8);
extern ConvNode *fn_0052df70(ConvType *),*CExpr_ConstructObject(ConvType *,ConvType *,ConvNode *,ConvList *,UInt8,UInt8,UInt8,UInt8,UInt8),*fn_005418b0(ConvNode *,ConvType *,ConvType *,UInt8,UInt8,UInt8);
ConvNode *CExpr_Convert(ConvNode *,ConvType *,UInt32,UInt8,UInt8),*fn_005e3cc0(ConvNode *,ConvType *,UInt32,ConvScore *,UInt8,UInt8,UInt8);
ConvCandidate *fn_005e0710(void *,ConvNode *,SInt16,ConvNode *),*fn_005e16f0(ConvCandidate *,SInt32,void *,void **,void *);
UInt8 fn_005e1ab0(ConvCandidate *,ConvCandidate *,SInt32),fn_005e4c50(ConvNode *,ConvType *,UInt32,UInt8,ConvMatch *),fn_005e6480(ConvType *,UInt32,ConvType *,UInt32,UInt8);
ConvObject *fn_005e17c0(ConvCandidate *,void *);
UInt8 fn_005e5ef0(ConvMatch *,ConvMatch *),fn_005e1880(ConvObject *,ConvList *,ConvNode *,ConvScore *);
ConvCandidate *fn_005e1200(ConvCandidate *,ConvNode *,ConvType *,UInt32,ConvNode *,ConvType *,UInt32);
SInt32 fn_005e63f0(ConvType *,UInt32,ConvType *,UInt32);
void fn_005e3600(ConvType *,ConvNode *);
ConvNode *fn_005e3b50(ConvNode *,ConvType *,UInt32,UInt8,UInt8,UInt8);
UInt8 fn_005e59b0(ConvObjectList *,void *,ConvType *,ConvNode **);
ConvType *fn_005e66c0(ConvObject *object,UInt32 *quals) {
    ConvType *type;
    if(object->type->kind!=7)CError_Internal(filename,104);
    if(!(((ConvFunction *)object->type)->flags&0x10))CError_Internal(filename,105);
    if(((ConvFunction *)object->type)->mode)CError_Internal(filename,106);
    if(!((ConvFunction *)object->type)->args)CError_Internal(filename,107);
    if(object->storage==6){if(!object->context)CError_Internal(filename,111);type=fn_005444c0(object->context);}
    else type=fn_005444c0(((ConvFunction *)object->type)->context);
    *quals=((ConvFunction *)object->type)->args->quals&3;return type;
}
UInt8 fn_005e6480(ConvType *left,UInt32 lq,ConvType *right,UInt32 rq,UInt8 mode) {
    UInt8 kind=left->kind;
    if(kind!=right->kind)return 0;
    switch(mode){
        case 0:for(;;){switch(kind){case 11:if(!is_typesame(*(ConvType **)((UInt8 *)left+10),*(ConvType **)((UInt8 *)right+10)))return 0;case 12:left=TARGET(left);right=TARGET(right);kind=left->kind;if(kind!=right->kind)return 0;break;default:goto compare;}}break;
        case 1:switch(kind){case 11:if((lq&3)!=(rq&3))return 0;if(!is_typesame(*(ConvType **)((UInt8 *)left+10),*(ConvType **)((UInt8 *)right+10)))return 0;left=TARGET(left);right=TARGET(right);break;case 12:if((lq&3)!=(rq&3))return 0;left=TARGET(left);right=TARGET(right);}break;
        case 2:if((lq&3)!=(rq&3))return 0;break;
    }
compare:return left==right||is_typesame(left,right);
}
UInt8 fn_005e65b0(ConvType *left,UInt32 lq,ConvType *right,UInt32 rq) {
    UInt8 added=0,first=1;UInt32 a,b;
    for(;;){if(left->kind!=right->kind)return 0;
        if(!first){a=fn_004533f0(left,lq);b=fn_004533f0(right,rq);if(!(a&1)){if(b&1)added=1;}else if(!(b&1))return 0;if(!(a&2)){if(b&2)added=1;}else if(!(b&2))return 0;}
        switch(left->kind){case 11:if(!is_typesame(*(ConvType **)((UInt8 *)left+10),*(ConvType **)((UInt8 *)right+10)))return 0;break;case 12:break;default:return added&&(left==right||is_typesame(left,right));}
        first=0;left=TARGET(left);right=TARGET(right);
    }
}
SInt32 fn_005e63f0(ConvType *left,UInt32 lq,ConvType *right,UInt32 rq) {
    UInt32 a=fn_004533b0(right,rq),b=fn_004533b0(left,lq);SInt16 access;UInt8 ambiguous;
    if(fn_00454280(b,a)){if(fn_005e6480(left,lq,right,rq,1))return 1;if(right->kind==6&&left->kind==6&&fn_00541ba0(right,left,&access,&ambiguous))return 2;}return 0;
}
UInt8 fn_005e5c10(ConvType *left,UInt32 lq,ConvType *right,UInt32 rq,ConvMatch *match) {
    UInt8 allConst=1;UInt32 a,b;SInt32 comparison;
    for(;;){a=fn_004533b0(left,lq);b=fn_004533b0(right,rq);
        if((a&3)==(b&3))comparison=0;else if((!(b&1)||(a&1))&&(!(b&2)||(a&2)))comparison=1;else comparison=-1;
        switch(comparison){case 0:break;case 1:match->qualification=1;if(!allConst)return 0;break;default:return 0;}
        if(!(a&1))allConst=0;
        if(left->kind==12){if(right->kind!=12)CError_Internal(filename,884);left=TARGET(left);right=TARGET(right);}
        else if(left->kind==11){if(right->kind!=11)CError_Internal(filename,891);left=TARGET(left);right=TARGET(right);}
        else return 1;
    }
}
UInt8 fn_005e5d30(ConvNode *node,ConvType *type,UInt32 quals,UInt8 mode,UInt8 reference,UInt8 special,UInt8 allowRValue,ConvMatch *match) {
    UInt8 lvalue=0;UInt32 a,b;
    if(reference){lvalue=CExpr_IsLValue(node);if(!fn_00453240(type,quals)&&(!fn_0070f1ee||!special)){if(!allowRValue&&!lvalue)return 0;if(!fn_005e63f0(type,quals,node->type,node->flags&CVMASK))return 0;}
        a=fn_004533f0(type,quals);b=fn_004533f0(node->type,node->flags&CVMASK);if((a&3)!=(b&3)&&!fn_004542f0(a&3,b&3))return 0;}
    memclrw(match,26);match->to=type;match->toQuals=quals;match->from=node->type;match->fromQuals=node->flags&CVMASK;match->reference=reference;match->special=special;match->isLValue=lvalue;
    switch(mode){case 0:break;case 1:match->mode1=1;break;case 2:match->mode2=1;break;default:CError_Internal(filename,746);}return 1;
}
ConvTypeItem *fn_005e14d0(ConvNode *node) {
    ConvTypeItem *list,*item;ConvObject *object;ConvType *type;UInt8 iterator[32];
    if(node->type->kind==6){fn_005a85c0(iterator,node->type);object=fn_005a8450(iterator);list=NULL;
        while(object){type=((ConvFunction *)object->type)->result;if(type->kind==12&&(TQUAL(type)&0x20))type=TARGET(type);item=list;if(type->kind!=6){item=CompilerTools_AllocatePool(16);item->next=list;item->object=object;item->type=type;item->quals=((ConvFunction *)object->type)->quals&3;}object=fn_005a8450(iterator);list=item;}
    }else{list=CompilerTools_AllocatePool(16);list->next=NULL;list->object=NULL;list->type=node->type;list->quals=node->flags&CVMASK;if(list->type->kind==4)list->quals=0;}return list;
}
ConvObject *fn_005e17c0(ConvCandidate *candidate,void *name) {
    ConvFunction *function;ConvArg *argument;ConvObject *object;
    if(candidate->object)return candidate->object;
    function=CompilerTools_AllocatePool(30);memclrw(function,30);function->base.kind=7;function->result=&stvoid;
    argument=CompilerTools_AllocatePool(24);memclrw(argument,24);argument->type=candidate->left;argument->quals=candidate->leftQuals;function->args=argument;
    if(candidate->right){argument=CompilerTools_AllocatePool(24);memclrw(argument,24);argument->type=candidate->right;argument->quals=candidate->rightQuals;function->args->next=argument;}
    object=CompilerTools_AllocatePool(96);memclrw(object,96);object->name=name;object->kind=5;object->storage=3;object->space=fn_007101c4;object->type=(ConvType *)function;return object;
}
UInt8 fn_005e0670(ConvNode *left,ConvNode *right,ConvNode **out) {
    ConvCandidate *candidate=fn_005e0710(NULL,left,0x3a,right);
    if(candidate){candidate=fn_005e16f0(candidate,1,GetHashNameNode("operator?:"),NULL,NULL);if(candidate->object)CError_Internal(filename,4172);out[0]=NULL;out[1]=CExpr_Convert(left,candidate->left,candidate->leftQuals,0,1);out[2]=CExpr_Convert(right,candidate->right,candidate->rightQuals,0,1);return 1;}return 0;
}
ConvNode *fn_005e2a20(ConvNode *node,ConvType *type) {
    ConvNode *result;ConvType *from,*component;UInt8 fromReal,targetReal;ConvWords zero;
    if(node->type==type)return node;
    if(type->kind!=3){fn_005454e0(node->type,&from,&fromReal);switch(type->kind){
        case 1:if(!fromReal)return intconstnode(type,0);if(node->kind==0x36){result=CExpr_NewENode(0x34);result->type=type;result->data.value=fn_004e4190(type,node->data.value);return result;}break;
        case 2:if(!fromReal)return fn_00524250(type,0);if(node->kind==0x36){result=CExpr_NewENode(0x35);result->type=type;result->data.value=node->data.value;return result;}break;
        default:return NULL;}
        result=makemonadicnode(node,0x32);result->type=type;return result;
    }
    fn_005454e0(type,&component,&targetReal);zero=CMach_CalcFloatConvertFromInt(component,cint64_zero);
    switch(node->type->kind){case 1:case 2:
        if((UInt8)(node->kind-0x34)<2){result=fn_0055b2d0(node,component);if(result->kind!=0x35)CError_Internal(filename,2674);if(targetReal)return fn_00524210(type,result->data.value,zero);result->data.value=zero;result->type=type;return result;}break;
        case 3:fn_005454e0(node->type,&from,&fromReal);
            if(node->kind==0x36){if(!targetReal){result=fn_00524250(type,0);result->data.value=CMach_CalcFloatConvert(component,node->data.complex.imag);result->type=type;return result;}
                node->data.complex.real=CMach_CalcFloatConvert(component,node->data.complex.real);node->data.complex.imag=CMach_CalcFloatConvert(component,node->data.complex.imag);node->type=type;return node;}
            if(node->kind==0x35){if(!targetReal){node->data.value=CMach_CalcFloatConvert(component,node->data.value);node->type=type;return node;}return fn_00524210(type,zero,node->data.value);}break;
        default:return NULL;}
    result=makemonadicnode(node,0x32);result->type=type;return result;
}
void fn_005e4b80(ConvMatch *match,ConvType *type,UInt32 quals,ConvType *target,UInt32 targetQuals) {
    ConvNode *node=CExpr_NewENode(0x44);node->type=type;node->flags&=~CVMASK;node->flags|=quals&CVMASK;
    if(type->kind==12&&(TQUAL(type)&0x20)){node->type=TARGET(node->type);if(type->kind==12&&(TQUAL(type)&0xa0)==0x20&&!fn_00453240(node->type,quals)){node=makemonadicnode(node,4);LEFT(node)->type=&fn_006771c8;node=makemonadicnode(node,4);LEFT(node)->type=&fn_006771c8;}}
    if(!fn_005e4c50(node,target,targetQuals,0,match))CError_Internal(filename,1566);
}
ConvNode *fn_005e3b50(ConvNode *node,ConvType *type,UInt32 quals,UInt8 checkAccess,UInt8 checkNull,UInt8 convert) {
    void *path;SInt16 access;UInt8 ambiguous;
    if(type->kind==6&&node->type->kind==6){path=fn_00541ba0(node->type,type,&access,&ambiguous);if(path){
        if(ambiguous)CError_Error(0x28b5,node->type,0,type,0);
        if(checkAccess)CClass_CheckStaticAccess(NULL,node->type,type,0,NULL,0);
        if(convert){node=fn_00559da0(node,0);node=fn_005a87c0(path,node,checkNull);node=makemonadicnode(node,4);node->type=type;node->flags&=~CVMASK;node->flags|=quals&CVMASK;}return node;}}
    return NULL;
}
UInt8 fn_005e3c30(ConvNode *node,ConvType *type,UInt32 quals) {
    ConvScore score;
    if(fn_005e4c50(node,type,quals,0,&score.standard)){score.kind=3;return 1;}
    if((node->type->kind==6||type->kind==6||(type->kind==12&&(TQUAL(type)&0x20)&&TARGET(type)->kind==6))&&fn_005e3cc0(node,type,quals,&score,0,0,0)){score.kind=2;return 1;}return 0;
}
ConvNode *CExpr_AssignmentPromotion(ConvNode *node,ConvType *type,UInt32 quals,UInt8 flag) {
    ConvScore score;UInt8 ok;
    if(fn_005e4c50(node,type,quals,0,&score.standard)){score.kind=3;ok=1;}
    else if((node->type->kind==6||type->kind==6||(type->kind==12&&(TQUAL(type)&0x20)&&TARGET(type)->kind==6))&&fn_005e3cc0(node,type,quals,&score,0,0,0)){score.kind=2;ok=1;}else ok=0;
    if(!ok){if(node->kind==0x4b&&LEFT(node)){ConvObject *object=*(ConvObject **)((UInt8 *)LEFT(node)+4);if(object->kind==4)node=fn_00543680(node,NULL,0,0,0);else if(object->kind==5)node=CExpr_New_EOBJREF_Node(object,0);}CError_Error(0x27e1,node->type,node->flags&CVMASK,type,quals);return nullnode();}
    return CExpr_Convert(node,type,quals,0,flag);
}
ConvCandidate *fn_005e1200(ConvCandidate *list,ConvNode *left,ConvType *leftType,UInt32 lq,ConvNode *right,ConvType *rightType,UInt32 rq) {
    ConvCandidate local,*item;UInt8 ok;
    if(fn_005e4c50(left,leftType,lq,0,&local.scores[0].standard)){local.scores[0].kind=3;ok=1;}
    else if((left->type->kind==6||leftType->kind==6||(leftType->kind==12&&(TQUAL(leftType)&0x20)&&TARGET(leftType)->kind==6))&&fn_005e3cc0(left,leftType,lq,&local.scores[0],0,0,0)){local.scores[0].kind=2;ok=1;}else ok=0;
    if(ok){if(right){if(fn_005e4c50(right,rightType,rq,0,&local.scores[1].standard)){local.scores[1].kind=3;ok=1;}
        else if((right->type->kind==6||rightType->kind==6||(rightType->kind==12&&(TQUAL(rightType)&0x20)&&TARGET(rightType)->kind==6))&&fn_005e3cc0(right,rightType,rq,&local.scores[1],0,0,0)){local.scores[1].kind=2;ok=1;}else ok=0;if(!ok)return list;}
        if(right){for(item=list;item;item=item->next){if(!item->object){if(is_typesame(item->left,leftType)&&item->leftQuals==lq&&is_typesame(item->right,rightType)&&item->rightQuals==rq)return list;}
            else if(leftType->kind==4&&rightType->kind==4&&item->object->type->kind==7){ConvArg *arg=((ConvFunction *)item->object->type)->args;if(arg&&arg->type==leftType&&arg->next&&arg->next->type==rightType)return list;}}}
        local.next=list;local.object=NULL;local.templateObject=NULL;local.left=leftType;local.leftQuals=lq;local.right=rightType;local.rightQuals=rq;item=CompilerTools_AllocatePool(124);*item=local;return item;
    }return list;
}
ConvCandidate *fn_005e1120(ConvCandidate *list,SInt16 token,ConvNode *left,ConvNode *right) {
    UInt8 iterator[32];ConvObject *object;ConvFunction *function;ConvType *type;
    if(left->type->kind==6){fn_005a85c0(iterator,left->type);object=fn_005a8450(iterator);
        if(object){SInt32 operation=token;do{function=(ConvFunction *)object->type;type=function->result;if(type->kind==12&&(TQUAL(type)&0x20)){type=TARGET(type);switch(type->kind){case 1:if(type==&stbool&&operation==0x17d)break;case 2:case 12:if(!fn_00453240(type,function->quals))list=fn_005e1200(list,left,type,function->quals,right,right?&stsignedint:NULL,0);break;}}object=fn_005a8450(iterator);}while(object);}}
    return list;
}
ConvCandidate *fn_005e0f00(ConvCandidate *list,SInt16 token,ConvNode *node) {
    ConvTypeItem *item;ConvType *type;SInt32 index;
    if(token==0x21)return fn_005e1200(list,node,&stbool,0,NULL,NULL,0);
    if(token==0x2a){for(item=fn_005e14d0(node);item;item=item->next){type=item->type;if(type->kind==12&&TARGET(type)->kind)list=fn_005e1200(list,node,type,item->quals,NULL,NULL,0);}return list;}
    if(token==0x2b){for(item=fn_005e14d0(node);item;item=item->next)if(item->type->kind==12)list=fn_005e1200(list,node,item->type,item->quals,NULL,NULL,0);}
    else if(token!=0x2d){if(token==0x7e){for(index=0;;++index){switch(index){case 0:type=&stsignedint;break;case 1:type=&stunsignedint;break;case 2:type=&stsignedlong;break;case 3:type=&stunsignedlong;break;case 4:type=fn_0070f1bd?&stsignedlonglong:NULL;break;case 5:type=fn_0070f1bd?&stunsignedlonglong:NULL;break;default:type=NULL;}if(!type)break;list=fn_005e1200(list,node,type,0,NULL,NULL,0);}return list;}
        if((UInt32)((SInt32)token-0x17c)>1)return list;return fn_005e1120(list,token,node,NULL);}
    for(index=0;;++index){switch(index){case 0:type=&stsignedint;break;case 1:type=&stunsignedint;break;case 2:type=&stsignedlong;break;case 3:type=&stunsignedlong;break;case 4:type=&stfloat;break;case 5:type=&stdouble;break;case 6:type=&stlongdouble;break;case 7:type=fn_0070f1bd?&stsignedlonglong:NULL;break;case 8:type=fn_0070f1bd?&stunsignedlonglong:NULL;break;default:type=NULL;}if(!type)break;list=fn_005e1200(list,node,type,0,NULL,NULL,0);}return list;
}
#define MATCHBYTE(m,o) (*((UInt8 *)(m)+(o)))
UInt8 fn_005e5ef0(ConvMatch *left,ConvMatch *right) {
    UInt8 notWorse=1,better=0;ConvType *a,*b,*c,*d;UInt32 lq,rq;
    if(!right->qualification){if(left->qualification)notWorse=0;}else if(!left->qualification)better=1;
    if(!right->mode1){if(left->mode1)notWorse=0;}else if(!left->mode1)better=1;
    if(!right->mode2){if(left->mode2)notWorse=0;}else if(!left->mode2)better=1;
    else{UInt8 rightBool=right->to==&stbool&&(right->from->kind==12||right->from->kind==11),leftBool=left->to==&stbool&&(left->from->kind==12||left->from->kind==11);if(rightBool){if(!leftBool)return 1;}else if(leftBool)return 0;}
    if(notWorse&&better)return 1;
    if(!left->mode2){if(right->mode2)return 1;if(!left->mode1){if(right->mode1)return 1;}else if(!right->mode1)return 0;}else if(!right->mode2)return 0;
    if(left->from->kind==12&&(a=TARGET(left->from))->kind==6&&left->to->kind==12&&right->from->kind==12&&(c=TARGET(right->from))->kind==6&&right->to->kind==12){b=TARGET(left->to);d=TARGET(right->to);if(d==&stvoid){if(b==&stvoid){if(fn_0053f270(a,c))return 1;}else if(a==c&&b->kind==6)return 1;}else if(b->kind==6&&d->kind==6){if(a==c){if(fn_0053f270(d,b))return 1;}else if(b==d&&fn_0053f270(a,c))return 1;}}
    a=left->from;b=left->to;c=right->from;d=right->to;
    if(a->kind==6&&b->kind==6&&c->kind==6&&d->kind==6){if(a==c){if(fn_0053f270(d,b))return 1;}else if(b==d&&fn_0053f270(a,c))return 1;}
    if(left->from->kind==11&&left->to->kind==11&&right->from->kind==11&&right->to->kind==11&&(a=*(ConvType **)((UInt8 *)left->from+10))->kind==6&&(b=*(ConvType **)((UInt8 *)left->to+10))->kind==6&&(c=*(ConvType **)((UInt8 *)right->from+10))->kind==6&&(d=*(ConvType **)((UInt8 *)right->to+10))->kind==6){if(c==a){if(fn_0053f270(b,d))return 1;}else if(d==b&&fn_0053f270(c,a))return 1;}
    if((left->qualification||right->qualification)&&left->mode1==right->mode1&&left->mode2==right->mode2&&!MATCHBYTE(left,23)&&fn_005e65b0(left->to,left->toQuals,right->to,right->toQuals))return 1;
    if(left->reference&&right->reference){if(!MATCHBYTE(left,24)&&!MATCHBYTE(right,24)){if(!left->isLValue){if(left->special&&!right->special)return 1;if(!left->special&&right->special)return 0;}else{if(!left->special&&right->special)return 1;if(left->special&&!right->special)return 0;}}
        if(fn_005e6480(left->to,left->toQuals,right->to,right->toQuals,1)){lq=fn_004533f0(left->to,left->toQuals);rq=fn_004533f0(right->to,right->toQuals);if(fn_004542f0(rq,lq))return 1;}}
    return 0;
}
static inline UInt8 score_better(ConvScore *left,ConvScore *right) {
    if(left->kind>right->kind)return 1;
    if(left->kind==right->kind){if(left->kind==3)return fn_005e5ef0(&left->standard,&right->standard);
        if(left->kind==2&&*(ConvObject **)((UInt8 *)left+2)==*(ConvObject **)((UInt8 *)right+2)&&fn_005e5ef0((ConvMatch *)((UInt8 *)left+6),(ConvMatch *)((UInt8 *)right+6)))return 1;}return 0;
}
UInt8 fn_005e1ab0(ConvCandidate *left,ConvCandidate *right,SInt32 count) {
    ConvScore *ls=left->scores,*rs=right->scores;UInt8 better=0;SInt32 i;
    if(ls->kind&&rs->kind){if(score_better(rs,ls))return 0;if(score_better(ls,rs))better=1;}
    for(i=0;i<count;++i){++ls;++rs;if(score_better(rs,ls))return 0;if(score_better(ls,rs))better=1;}
    if(better)return 1;
    if(right->object){if(right->object->type->kind!=7)CError_Internal(filename,3245);
        if(*(void **)((UInt8 *)right->object+72)){if(!left->object)return 1;if(left->object->type->kind!=7)CError_Internal(filename,3249);if(!*(void **)((UInt8 *)left->object+72))return 1;if(!left->templateObject||!right->templateObject)CError_Internal(filename,3254);if(fn_005dea90(left->templateObject,right->templateObject))return 1;}}
    return 0;
}
ConvCandidate *fn_005e16f0(ConvCandidate *list,SInt32 count,void *name,void **ambiguous,void *arguments) {
    ConvCandidate *best=list,*item;ConvList *conflicts=NULL,*link;
    for(item=list->next;item;item=item->next)if(fn_005e1ab0(item,best,count))best=item;
    for(;list;list=list->next)if(list!=best&&!fn_005e1ab0(best,list,count)){link=CompilerTools_AllocatePool(8);link->next=conflicts;link->node=(ConvNode *)fn_005e17c0(list,name);conflicts=link;}
    if(ambiguous)*ambiguous=conflicts;else if(conflicts){if(!arguments)CError_OverloadedFunctionError(fn_005e17c0(best,name),conflicts);else fn_0045aae0(fn_005e17c0(best,name),conflicts,0,arguments);}return best;
}
UInt8 fn_005e1880(ConvObject *object,ConvList *arguments,ConvNode *instance,ConvScore *scores) {
    ConvFunction *function=(ConvFunction *)object->type;ConvArg *parameter=function->args;ConvScore *score;UInt32 quals;ConvType *type;ConvNode *node;UInt8 ok;
    if(!(function->flags&0x10))scores->kind=0;
    else if(!function->mode){if(!(function->flags&0x1000)){if(!instance)ok=0;else{type=fn_005e66c0(object,&quals);if(!fn_005e4c50(instance,type,quals,1,&scores->standard))ok=0;else{scores->kind=3;MATCHBYTE(scores,26)=1;ok=1;}}if(!ok)return 0;parameter=parameter->next;}else{scores->kind=0;parameter=parameter->next;}}
    else scores->kind=0;
    for(;;){score=scores+1;if(!parameter||parameter->type==&stvoid)return arguments==NULL;
        if(parameter==&fn_007037c0||parameter==&fn_0070bb08){for(;arguments;arguments=arguments->next){score->kind=1;++score;}return 1;}
        if(!arguments)return parameter->defaultValue!=NULL;
        quals=parameter->quals;node=arguments->node;type=parameter->type;
        if(fn_005e4c50(node,type,quals,0,&score->standard)){score->kind=3;ok=1;}
        else if((node->type->kind==6||type->kind==6||(type->kind==12&&(TQUAL(type)&0x20)&&TARGET(type)->kind==6))&&fn_005e3cc0(node,type,quals,score,0,0,0)){score->kind=2;ok=1;}else ok=0;
        if(!ok)return 0;arguments=arguments->next;parameter=parameter->next;scores=score;
    }
}
void fn_005e1590(ConvObjectList *source,void *templateContext,ConvList *arguments,void **out,ConvNode *instance,UInt8 excludeExplicit) {
    ConvList *arg;ConvObjectList *item;ConvCandidate *list,*candidate;ConvObject *object,*origin;SInt32 count=0;UInt32 size;UInt8 hasTemplate;
    for(arg=arguments;arg;arg=arg->next){CDecl_CompleteType(arg->node->type);++count;}size=(count-2)*32+124;
    do {list=NULL;candidate=CompilerTools_AllocatePool(size);hasTemplate=0;
        for(item=source;item;item=item->next){object=item->object;if(object->kind==5&&object->type->kind==7&&(!excludeExplicit||!(object->quals&0x40))){
            origin=NULL;if(((ConvFunction *)object->type)->flags&0x100000){hasTemplate=1;origin=object;object=fn_005dca80(object,templateContext,arguments,0);if(!object)continue;}else if(templateContext)continue;
            if(fn_005e1880(object,arguments,instance,candidate->scores)){candidate->object=object;candidate->templateObject=origin;candidate->next=list;list=candidate;candidate=CompilerTools_AllocatePool(size);}
        }}
        if(list){candidate=fn_005e16f0(list,count,NULL,out+1,arguments);out[0]=candidate->object;return;}
    }while(hasTemplate&&fn_005dd010(arguments));
}
ConvNode *fn_005e31a0(ConvNode *node,ConvType *referenceType,UInt32 quals,UInt8 flag) {
    ConvType *type=TARGET(referenceType);UInt32 cv;SInt32 relation;ConvNode *result;
    if(referenceType->kind!=12)CError_Internal(filename,2319);cv=fn_004533b0(type,quals);
    if(type->kind==7&&node->kind==0x4b){if(fn_005e59b0((ConvObjectList *)LEFT(node),(void *)node->data.op.fourth,CDecl_NewPointerType(type),&node))return node;return NULL;}
    if(!CExpr_IsLValue(node)){
        if(!flag&&type->kind==6&&node->type->kind==6){relation=fn_005e63f0(type,quals,node->type,node->flags&CVMASK);if(relation){fn_005e3600(type,node);if(relation==2)node=fn_005e3b50(node,type,quals,1,0,1);return fn_00559da0(node,0);}}
    }else{relation=fn_005e63f0(type,quals,node->type,node->flags&CVMASK);if(relation){if(relation==2){if(type->kind!=6||node->type->kind!=6)CError_Internal(filename,2337);node=fn_005e3b50(node,type,quals,1,0,1);}return fn_00559da0(node,0);}}
    if(node->type->kind==6){result=fn_005e3cc0(node,referenceType,quals,NULL,1,0,1);if(result)return fn_00559da0(result,0);}
    if(!fn_0070f1ee||referenceType->kind!=12||(TQUAL(referenceType)&0xa0)!=0xa0){if(!(cv&1)){CError_Error(0x27f4);fn_00462db0();}if(cv&2){CError_Error(0x2813);fn_00462db0();}}return NULL;
}
ConvNode *fn_005e3870(ConvNode *node,ConvType *referenceType,UInt32 quals,UInt8 checkAccess) {
    ConvType *type=TARGET(referenceType);SInt32 relation;ConvNode *result;
    if(CExpr_IsLValue(node)&&type->kind==6&&node->type->kind==6){relation=fn_005e63f0(type,0,node->type,0);if(relation){if(relation==2){if(type->kind!=6||node->type->kind!=6)CError_Internal(filename,2142);node=fn_005e3b50(node,type,quals,checkAccess,0,1);}node->flags=(node->flags&~CVMASK)|(quals&CVMASK);return node;}
        if(fn_005e63f0(node->type,0,type,0)){result=fn_005418b0(fn_00559da0(node,0),node->type,type,1,1,checkAccess);if(result->type->kind!=12)CError_Internal(filename,2154);node=makemonadicnode(result,4);node->type=type;node->flags=(node->flags&~CVMASK)|(quals&CVMASK);return node;}}
    if(node->type->kind==6)return fn_005e3cc0(node,referenceType,quals,NULL,1,0,1);return NULL;
}
void fn_005e3600(ConvType *type,ConvNode *node) {
    ConvObjectList *list,*item;ConvObject *object,*copy=NULL;ConvFunction *function;ConvArg *arg;UInt8 hasTemplate=0;ConvNode *dummy;ConvList *arguments;
    if(type->kind!=6||node->type->kind!=6)CError_Internal(filename,2188);
    if(type==node->type){list=CClass_Constructor(type);
        if(fn_0070f1ee){for(item=list;item;item=item->next){object=item->object;function=(ConvFunction *)object->type;if(object->kind==5&&function->base.kind==7&&!(function->flags&0x100000)){arg=fn_00553440(function);if(arg&&arg!=&fn_007037c0&&(!arg->next||arg->next->defaultValue||*((UInt8 *)arg->next+23))&&fn_0070f1ee&&arg->type->kind==12&&(TQUAL(arg->type)&0xa0)==0xa0&&TARGET(arg->type)==type)return;}}}
        for(item=list;item;item=item->next){object=item->object;function=(ConvFunction *)object->type;if(object->kind==5&&function->base.kind==7){if(function->flags&0x100000)hasTemplate=1;else{arg=fn_00553440(function);if(arg&&arg!=&fn_007037c0&&(!arg->next||arg->next->defaultValue||*((UInt8 *)arg->next+23))&&arg->type->kind==12&&(TQUAL(arg->type)&0xa0)==0x20&&TARGET(arg->type)==type){copy=object;if((arg->quals&1)&&!(arg->quals&2)){CClass_CheckStaticAccess(type,type,type,object->access,object,0);return;}}}}}
        if(copy&&!hasTemplate)CError_Error(0x28d6,copy);
    }else{arguments=CompilerTools_AllocatePool(8);arguments->next=NULL;dummy=nullnode();dummy->type=&fn_006771c8;dummy=makemonadicnode(dummy,4);dummy->type=node->type;dummy->flags=node->flags;if(!CExpr_IsLValue(node))dummy->flags|=0x1000;arguments->node=dummy;CExpr_ConstructObject(node->type,NULL,fn_0052df70(node->type),arguments,0,1,1,1,1);}
}
void fn_005e4450(ConvSelection *out,ConvNode *node,ConvType *type,UInt32 quals,UInt8 allowExplicit) {
    ConvObjectList *list,*link;ConvObject *object,*oldOrigin,*newOrigin;ConvFunction *function;ConvArg *arg;ConvList single;ConvMatch match;
    for(list=CClass_Constructor(type);list;list=list->next){object=list->object;function=(ConvFunction *)object->type;
        if(object->kind!=5||function->base.kind!=7||(!allowExplicit&&(object->quals&0x40)))continue;
        if(function->flags&0x100000){single.next=NULL;single.node=node;object=fn_005dca80(object,NULL,&single,0);if(!object)continue;function=(ConvFunction *)object->type;}
        arg=fn_00553440(function);if(!arg||arg==&fn_007037c0||(arg->next&&!arg->next->defaultValue&&arg->next!=&fn_007037c0))continue;
        if(arg->type->kind==12&&(TQUAL(arg->type)&0x20)&&!fn_00453240(TARGET(arg->type),arg->quals)&&!CExpr_IsLValue(node)&&(!fn_0070f1ee||(TQUAL(arg->type)&0xa0)!=0xa0))continue;
        if(!fn_005e4c50(node,arg->type,arg->quals,0,&match))continue;
        if(out->object){
            if((*(void **)((UInt8 *)object+72)&&!*(void **)((UInt8 *)out->object+72))||fn_005e5ef0(&out->match,&match))continue;
            if(!fn_005e5ef0(&match,&out->match)&&(*(void **)((UInt8 *)object+72)||!*(void **)((UInt8 *)out->object+72))){
                if(*(void **)((UInt8 *)object+72)&&*(void **)((UInt8 *)out->object+72)){
                    newOrigin=fn_0053ec20(object);oldOrigin=fn_0053ec20(out->object);if(fn_005dea90(oldOrigin,newOrigin))continue;
                    oldOrigin=fn_0053ec20(out->object);newOrigin=fn_0053ec20(object);if(fn_005dea90(newOrigin,oldOrigin)){out->object=object;out->match=match;out->ambiguous=NULL;continue;}
                }
                link=CompilerTools_AllocatePool(8);link->next=out->ambiguous;link->object=out->object;out->ambiguous=link;
            }else out->ambiguous=NULL;
        }
        out->object=object;out->match=match;
    }
}
void fn_005e46e0(ConvSelection *out,ConvNode *node,ConvType *originalTarget,ConvType *target,UInt32 quals,UInt8 referenceOnly) {
    UInt8 iterator[32],special;ConvObject *object,*oldOrigin,*newOrigin;ConvFunction *function;ConvType *type;ConvNode *value;ConvMatch match;ConvObjectList *link;UInt32 thisQual,bestQual;SInt32 comparison;
    fn_005a85c0(iterator,node->type);object=fn_005a8450(iterator);
    for(;object;object=fn_005a8450(iterator)){function=(ConvFunction *)object->type;if(function->flags&0x100000){object=fn_005dc920(object,target,quals);if(!object)continue;function=(ConvFunction *)object->type;}
        if(referenceOnly){type=function->result;if(type->kind!=12||!(TQUAL(type)&0x20)||!fn_005e63f0(target,quals,TARGET(type),function->quals))continue;}
        if(!function->args||function->args->type->kind!=12)CError_Internal(filename,1619);
        thisQual=function->args->quals;if((node->flags&3)!=(thisQual&3)&&(((node->flags&1)&&!(thisQual&1))||((node->flags&2)&&!(thisQual&2))))continue;
        value=CExpr_NewENode(0x44);value->type=function->result;value->flags=(value->flags&~CVMASK)|(function->quals&CVMASK);special=0;type=value->type;
        if(type->kind==12&&(TQUAL(type)&0x20)){value->type=TARGET(type);if(function->result->kind==12&&(TQUAL(function->result)&0xa0)==0x20&&!fn_00453240(value->type,function->quals)){value=makemonadicnode(value,4);LEFT(value)->type=&fn_006771c8;value=makemonadicnode(value,4);LEFT(value)->type=&fn_006771c8;special=1;}}
        if(!fn_005e4c50(value,originalTarget,quals,0,&match))continue;
        if(out->object&&out->object!=object){
            if((thisQual&3)==(bestQual&3))comparison=0;else if((!(bestQual&1)||(thisQual&1))&&(!(bestQual&2)||(thisQual&2)))comparison=1;else comparison=-1;
            switch(comparison){case 1:continue;case -1:
                if((bestQual&3)==(thisQual&3))comparison=0;else if((!(thisQual&1)||(bestQual&1))&&(!(thisQual&2)||(bestQual&2)))comparison=1;else comparison=-1;
                if(comparison==1){out->ambiguous=NULL;goto select;}break;
            case 0:break;default:CError_Internal(filename,1670);}
            if(fn_005e5ef0(&out->match,&match))continue;if(fn_005e5ef0(&match,&out->match)){out->ambiguous=NULL;goto select;}
            if(!*(void **)((UInt8 *)object+72)){if(*(void **)((UInt8 *)out->object+72)){out->ambiguous=NULL;goto select;}}
            else {if(!*(void **)((UInt8 *)out->object+72))continue;newOrigin=fn_0053ec20(object);oldOrigin=fn_0053ec20(out->object);if(fn_005dea90(oldOrigin,newOrigin))continue;oldOrigin=fn_0053ec20(out->object);newOrigin=fn_0053ec20(object);if(fn_005dea90(newOrigin,oldOrigin)){out->ambiguous=NULL;goto select;}}
            link=CompilerTools_AllocatePool(8);link->next=out->ambiguous;link->object=out->object;out->ambiguous=link;
        }
select: out->object=object;out->scope=*(void **)iterator?*(void **)((UInt8 *)*(void **)iterator+12):NULL;bestQual=thisQual;out->match=match;MATCHBYTE(out,30)=special;
    }
}
UInt8 fn_005e59b0(ConvObjectList *list,void *context,ConvType *pointerType,ConvNode **out) {
    ConvType *type;ConvObject *best=NULL,*object,*a,*b;ConvFunction *function;ConvObjectList *conflicts=NULL,*templates=NULL,*link;void *instance;UInt8 ordinary=0;
    if(pointerType->kind!=12||(type=TARGET(pointerType))->kind!=7)return 0;
    for(;list;list=list->next){object=list->object;function=(ConvFunction *)object->type;if(object->kind!=5||function->base.kind!=7)continue;
        if(!(function->flags&0x100000)){if((!(function->flags&0x10)||function->mode)&&is_typesame(object->type,type)){if(!best||!ordinary){conflicts=NULL;best=object;}else{a=object->storage==6?(ConvObject *)object->value:object;b=best->storage==6?(ConvObject *)best->value:best;if(a!=b){link=CompilerTools_AllocatePool(8);link->next=conflicts;link->object=object;conflicts=link;}}ordinary=1;}}
        else if(!ordinary&&(instance=fn_005dedc0(object,type,context))!=NULL&&is_typesame((*(ConvObject **)((UInt8 *)instance+24))->type,type)){link=CompilerTools_AllocatePool(8);link->next=templates;link->object=object;templates=link;a=*(ConvObject **)((UInt8 *)instance+24);if(!best||best==a)best=a;else{link=CompilerTools_AllocatePool(8);link->next=conflicts;link->object=a;conflicts=link;}}
    }
    if(!best)return 0;
    if(out){if(conflicts){ConvArg *arg;for(arg=((ConvFunction *)object->type)->args;arg;arg=arg->next){}if(ordinary||(object=fn_005de940(templates))==NULL)CError_OverloadedFunctionError(best,conflicts);else{instance=fn_005dedc0(object,type,context);if(instance)best=*(ConvObject **)((UInt8 *)instance+24);}}
        *out=CExpr_New_EOBJREF_Node(best,1);(*out)->type=CDecl_NewPointerType(best->type);(*out)->flags=((*out)->flags&~CVMASK)|(object->quals&CVMASK);best->flags|=1;if(best->storage==5)CError_Error(0x27bf);
    }return 1;
}
UInt8 fn_005e2cf0(ConvType *left,ConvType *right) {
    UInt8 a,b;void *li,*ri;ConvType *type;
    while(left->kind==12||left->kind==13)left=TARGET(left);while(right->kind==12||right->kind==13)right=TARGET(right);a=left->kind;b=right->kind;
    if((a==1&&(UInt8)(*((UInt8 *)left+6)-1)<3)||(b==1&&(UInt8)(*((UInt8 *)right+6)-1)<3)||!a||!b)return 1;
    if(a!=5&&a!=6&&b!=5&&b!=6)return fn_00544710(left,right);
    if((a==5||a==6)!=(b==5||b==6)){
        if(a==5||a==6){li=*(void **)((UInt8 *)left+(a==5?10:22));type=*(ConvType **)((UInt8 *)li+(a==5?4:12));while(type->kind==12||type->kind==13)type=TARGET(type);return fn_00544710(right,type)&&!*(void **)((UInt8 *)li+(a==5?0:4));}
        ri=*(void **)((UInt8 *)right+(b==5?10:22));type=*(ConvType **)((UInt8 *)ri+(b==5?4:12));while(type->kind==12||type->kind==13)type=TARGET(type);return fn_00544710(left,type)&&!*(void **)((UInt8 *)ri+(b==5?0:4));
    }
    if(fn_00544710(left,right)||left==right)return 1;
    if(a==5&&b==5){li=*(void **)((UInt8 *)left+10);ri=*(void **)((UInt8 *)right+10);for(;li;li=*(void **)li,ri=*(void **)ri){if(!ri)return 0;if(*(UInt32 *)((UInt8 *)li+8)!=*(UInt32 *)((UInt8 *)ri+8)||*(UInt32 *)((UInt8 *)li+12)!=*(UInt32 *)((UInt8 *)ri+12)||*(UInt32 *)((UInt8 *)li+16)!=*(UInt32 *)((UInt8 *)ri+16))return 0;if((*(ConvType **)((UInt8 *)li+4))->kind!=(*(ConvType **)((UInt8 *)ri+4))->kind||(*(ConvType **)((UInt8 *)li+4))->size!=(*(ConvType **)((UInt8 *)ri+4))->size)return 0;}return 1;}
    if(a==6&&b==6){li=*(void **)((UInt8 *)left+22);ri=*(void **)((UInt8 *)right+22);for(;li;li=*(void **)((UInt8 *)li+4),ri=*(void **)((UInt8 *)ri+4)){if(!ri)return 0;if(*(UInt32 *)((UInt8 *)li+8)!=*(UInt32 *)((UInt8 *)ri+8)||*(UInt32 *)((UInt8 *)li+20)!=*(UInt32 *)((UInt8 *)ri+20)||*(UInt32 *)((UInt8 *)li+16)!=*(UInt32 *)((UInt8 *)ri+16))return 0;if((*(ConvType **)((UInt8 *)li+12))->kind!=(*(ConvType **)((UInt8 *)ri+12))->kind||(*(ConvType **)((UInt8 *)li+12))->size!=(*(ConvType **)((UInt8 *)ri+12))->size)return 0;}return 1;}
    return 0;
}
ConvNode *fn_005e3cc0(ConvNode *node,ConvType *originalTarget,UInt32 quals,ConvScore *score,UInt8 apply,UInt8 allowExplicit,UInt8 referenceOnly) {
    ConvSelection conversion,constructor;ConvType *target=originalTarget,*pointerType;ConvFunction *function;ConvNode *value,*result,*extra;ConvList *arguments,*tail;ConvObjectList ambiguous;SInt16 access;UInt8 ambiguousBase;UInt32 pointerQual;
    memclrw(&conversion,38);memclrw(&constructor,38);
    if(originalTarget->kind==12&&(TQUAL(originalTarget)&0x20)){target=TARGET(originalTarget);if((!fn_0070f1ee||(TQUAL(originalTarget)&0xa0)!=0xa0)&&!fn_00453240(target,quals))referenceOnly=1;}else node=pointer_generation(node);
    if(!target->size)CDecl_CompleteType(target);if(!node->type->size)CDecl_CompleteType(node->type);
    if(node->type->kind==6){if(target->kind!=6||!apply||!fn_00541ba0(node->type,target,&access,&ambiguousBase))fn_005e46e0(&conversion,node,originalTarget,target,quals,referenceOnly);}
    if(!referenceOnly&&target->kind==6)fn_005e4450(&constructor,node,target,quals,allowExplicit);
    if(conversion.object&&constructor.object){if(fn_005e5ef0(&constructor.match,&conversion.match))conversion.object=NULL;else if(fn_005e5ef0(&conversion.match,&constructor.match))constructor.object=NULL;else{if(apply){ambiguous.next=NULL;ambiguous.object=constructor.object;CError_OverloadedFunctionError(conversion.object,&ambiguous);}conversion.object=NULL;}}
    if(conversion.object){function=(ConvFunction *)conversion.object->type;
        if(score){score->kind=2;*(ConvObject **)((UInt8 *)score+2)=conversion.object;fn_005e4b80((ConvMatch *)((UInt8 *)score+6),function->result,function->quals,originalTarget,quals);}
        if(!apply)return node;if(conversion.ambiguous)CError_OverloadedFunctionError(conversion.object,conversion.ambiguous);
        if(!(function->flags&0x10))CError_Internal(filename,1912);if(!conversion.scope)CError_Internal(filename,1913);
        CClass_CheckStaticAccess(node->type,node->type,(ConvType *)conversion.scope,conversion.object->access,conversion.object,0);
        value=fn_00559da0(node,0);arguments=CompilerTools_AllocatePool(8);arguments->next=NULL;pointerQual=value->flags&CVMASK;pointerType=CDecl_NewPointerType(function->context);arguments->node=CExpr_AssignmentPromotion(value,pointerType,pointerQual,0);
        result=CExpr_NewENode(0x39);result->cost=4;result->type=function->result;result->flags=(result->flags&~CVMASK)|(function->quals&CVMASK);LEFT(result)=CExpr_New_EOBJREF_Node(conversion.object,1);RIGHT(result)=(ConvNode *)arguments;THIRD(result)=(ConvNode *)function;
        result=checkreference(CExpr_AdjustFunctionCall(result));if(result->type!=target){if(referenceOnly){value=fn_005e3b50(result,target,quals,1,0,1);if(value)return value;}result=CExpr_Convert(result,target,quals,0,1);}return result;
    }
    if(!constructor.object)return NULL;
    if(score){score->kind=2;*(ConvObject **)((UInt8 *)score+2)=constructor.object;fn_005e4b80((ConvMatch *)((UInt8 *)score+6),target,quals,originalTarget,quals);}
    if(!apply)return node;if(constructor.ambiguous)CError_OverloadedFunctionError(constructor.object,constructor.ambiguous);
    arguments=CompilerTools_AllocatePool(8);arguments->next=NULL;arguments->node=node;extra=fn_00553250(target,target,1,0);
    if(extra){tail=CompilerTools_AllocatePool(8);arguments->next=tail;tail->next=NULL;tail->node=arguments->node;arguments->node=extra;}
    value=makemonadicnode(fn_0052df70(target),4);value->type=target;result=fn_005a7480(target,value,constructor.object,NULL,arguments,1);
    if((UInt8)(result->kind-0x39)<2){result->type=CDecl_NewPointerType(target);result=makemonadicnode(result,4);result->type=target;}return result;
}
UInt8 fn_005e4c50(ConvNode *node,ConvType *target,UInt32 quals,UInt8 allowRValue,ConvMatch *match) {
    ConvType *from=node->type,*a,*b;UInt32 fromQual=node->flags&CVMASK,currentQual=fromQual,cv;UInt8 reference=0,special=0,mode=2;ConvObjectList single;SInt16 access;UInt8 ambiguous;
    if(target->kind==12&&(TQUAL(target)&0x20)){if(fn_0070f1ee&&(TQUAL(target)&0xa0)==0xa0)special=1;target=TARGET(target);reference=1;}
    if(target->kind!=12){
        if(is_typesame(target,from))return fn_005e5d30(node,target,quals,0,reference,special,allowRValue,match);
        if(target==&stbool){switch(from->kind){case 1:case 2:case 3:case 4:case 11:case 12:return fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match);default:return 0;}}
        if(target->kind!=11){switch(from->kind){
            case 1:switch(target->kind){case 1:if(*((UInt8 *)from+6)<7){if(target==&stsignedint){if(from->size<stsignedint.size||!fn_00454260(from))mode=1;}else if(target==&stunsignedint&&stunsignedint.size==from->size&&fn_00454260(from))mode=1;}break;case 2:case 3:break;case 4:if(fn_0070f1a8)return 0;break;default:return 0;}break;
            case 2:switch(target->kind){case 1:case 3:break;case 2:if(target==&stdouble&&(from==&stfloat||from==&fn_00699c8c))mode=1;break;case 4:if(fn_0070f1a8)return 0;break;default:return 0;}break;
            case 3:switch(target->kind){case 1:case 2:case 3:case 4:break;default:return 0;}break;
            case 4:switch(target->kind){case 1:a=*(ConvType **)((UInt8 *)node->type+14);if(*((UInt8 *)a+6)<7){if(from->size==target->size&&fn_00454260(*(ConvType **)((UInt8 *)from+14))){if(target==&stunsignedint)mode=1;}else if(target==&stsignedint)mode=1;}else if(*(ConvType **)((UInt8 *)from+14)==target)mode=1;break;case 2:break;case 4:if(fn_0070f1a8)return 0;break;default:return 0;}break;
            case 6:if(target->kind!=6||!fn_00541ba0(from,target,&access,&ambiguous))return 0;break;
            case 12:if(fn_0070f1da&&!fn_0070f1a8){CError_Warning(0x27e1,from,fromQual,target,quals);return fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match);}return 0;
            default:return 0;}
            return fn_005e5d30(node,target,quals,mode,reference,special,allowRValue,match);
        }
        if(node->kind==0x34&&!node->data.value.hi&&!node->data.value.lo&&from->kind==1)return fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match);
        if(node->kind==0x4b&&MATCHBYTE(node,41)){node=fn_00543680(node,target,quals,0,0);from=node->type;currentQual=node->flags&CVMASK;}
        if(from->kind==11){a=*(ConvType **)((UInt8 *)target+10);b=*(ConvType **)((UInt8 *)from+10);if(a->kind!=6||b->kind!=6)CError_Internal(filename,1310);if(!fn_00454e40(TARGET(target),TARGET(from)))return 0;
            if(a==b)mode=0;else if(fn_00541ba0(a,b,&access,&ambiguous))mode=2;else return 0;
            if(!fn_005e5d30(node,target,quals,mode,reference,special,allowRValue,match))return 0;return fn_005e5c10(TARGET(target),quals,TARGET(from),currentQual,match);
        }return 0;
    }
    if(from->kind==13)from=CDecl_NewPointerType(TARGET(from));else if(from->kind==7)from=CDecl_NewPointerType(from);
    if(node->kind==0x34&&!node->data.value.hi&&!node->data.value.lo&&(from->kind==1||(!fn_0070f1a8&&from->kind==4)))return fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match);
    if(from->kind==1){if(node->kind==4&&LEFT(node)->kind==0x3b&&(LEFT(node)->data.object->quals&0x10000)&&!*(UInt32 *)((UInt8 *)LEFT(node)->data.object+64)&&!*(UInt32 *)((UInt8 *)LEFT(node)->data.object+68))return fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match);
        if(fn_0070f1da&&!fn_0070f1a8){CError_Warning(0x27e1,from,fromQual,target,quals);return fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match);}}
    if(node->kind==0x4b)return fn_005e59b0((ConvObjectList *)LEFT(node),(void *)node->data.op.fourth,target,NULL)&&fn_005e5d30(node,target,quals,0,reference,special,allowRValue,match);
    if(node->kind==0x3b&&node->data.object->type->kind==7&&(((ConvFunction *)node->data.object->type)->flags&0x100000)){single.next=NULL;single.object=node->data.object;return fn_005e59b0(&single,NULL,target,NULL)&&fn_005e5d30(node,target,quals,0,reference,special,allowRValue,match);}
    if(from->kind!=12)return 0;
    if((node->kind==0x37||(node->kind==4&&LEFT(node)->kind==0x37))&&TARGET(target)==TARGET(from)&&!(quals&1)&&!fn_0070f1f3&&(TARGET(target)==&fn_00699c24||TARGET(target)==&stunsignedchar||TARGET(target)==fn_004543f0())){
        if(fn_005e5d30(node,target,quals,0,reference,special,allowRValue,match)&&fn_005e5c10(TARGET(target),quals,TARGET(from),fromQual&~1UL,match)){match->qualification=1;MATCHBYTE(match,23)=1;return 1;}return 0;}
    a=TARGET(target);b=TARGET(from);
    if(!a->kind||(!fn_0070f1a8&&!b->kind)){
        if(fn_0070f1a8&&fn_0070f1af&&b->kind==7)return 0;mode=!b->kind?0:2;
        if(!fn_005e5d30(node,target,quals,mode,reference,special,allowRValue,match))return 0;if((fn_0070f1da||fn_0070f1f1)&&!fn_0070f1a8)return 1;
        cv=fn_004533b0(TARGET(from),fromQual);if((quals&3)==(cv&3))return 1;if((!(cv&1)||(quals&1))&&(!(cv&2)||(quals&2))){match->qualification=1;return 1;}return 0;
    }
    for(;;){if(a->kind!=b->kind)break;switch(a->kind){
        case 1:if(a!=b&&fn_0070f1da&&!fn_0070f1a8){if(a->size!=b->size)CError_Warning(0x27e1,from,fromQual,target,quals);if(fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match))return 1;}
        default:if(is_typesame(a,b)){if(!fn_005e5d30(node,target,quals,0,reference,special,allowRValue,match))return 0;if(!fn_005e5c10(TARGET(target),quals,TARGET(from),fromQual,match)){if((fn_0070f1da||fn_0070f1f1)&&!fn_0070f1a8){CError_Warning(0x27e1,from,fromQual,target,quals);return 1;}return 0;}return 1;}goto mismatch;
        case 11:if(!is_typesame(*(ConvType **)((UInt8 *)a+10),*(ConvType **)((UInt8 *)b+10)))goto mismatch;a=TARGET(a);b=TARGET(b);if(a->kind!=12&&a->kind!=11){if(fn_00454e40(a,b)){if(!fn_005e5d30(node,target,quals,0,reference,special,allowRValue,match))return 0;return fn_005e5c10(TARGET(target),quals,TARGET(from),fromQual,match);}goto mismatch;}break;
        case 12:a=TARGET(a);b=TARGET(b);break;
    }}
mismatch: if(TARGET(target)->kind==6&&TARGET(from)->kind==6&&fn_00541ba0(TARGET(from),TARGET(target),&access,&ambiguous)){if(!fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match))return 0;return fn_005e5c10(TARGET(target),quals,TARGET(from),fromQual,match);}
    if(fn_0070f1a8)return 0;if(fn_0070f1f1&&TARGET(target)->kind==1&&TARGET(from)->kind==1&&TARGET(target)->size==TARGET(from)->size&&fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match))return 1;
    return fn_0070f1b0&&fn_005e5d30(node,target,quals,2,reference,special,allowRValue,match);
}
ConvNode *CExpr_Convert(ConvNode *node,ConvType *target,UInt32 quals,UInt8 explicitCast,UInt8 checkAccess) {
    ConvNode *result,*child;ConvType *copy,*from;UInt32 q=quals&CVMASK;UInt8 a,b;ConvObjectList single;
    if(fn_0070f1cb&&node->type->kind==12&&target->kind==12&&!fn_005e2cf0(node->type,target))CError_Warning(0x2942);
    if(target->kind==12&&TARGET(target)->kind==7&&((ConvFunction *)TARGET(target))->exspec&&node->type->kind==12&&TARGET(node->type)->kind==7&&!fn_004a05b0(((ConvFunction *)TARGET(target))->exspec,((ConvFunction *)TARGET(node->type))->exspec))fn_0045c2c0(0x292d,((ConvFunction *)TARGET(target))->exspec,((ConvFunction *)TARGET(node->type))->exspec);
    if(fn_0070f1b3&&node->kind!=0x4b&&!((node->flags&CVMASK)&~q)&&is_typesame(node->type,target)){result=fn_0055ba60(node);result->type=target;result->flags=(result->flags&~CVMASK)|q;return result;}
    if(target==&stvoid){result=makemonadicnode(node,0x32);result->type=&stvoid;result->flags=(result->flags&~CVMASK)|q;return result;}
    if(target->kind==12&&(TQUAL(target)&0x20)){
        if(!explicitCast){result=fn_005e31a0(node,target,quals,0);if(!result){if(node->type!=TARGET(target))node=CExpr_Convert(node,TARGET(target),quals,0,1);if(!CExpr_IsLValue(node)){result=fn_00559240(node,0,0);if(result->kind==4)result=fn_00559da0(result,0);else result=fn_005a7f40(result,1);}else result=fn_00559da0(node,0);}}
        else{if(!CExpr_IsLValue(node))CError_Warning(0x279e);result=fn_005e3870(node,target,quals,checkAccess);if(!result){child=fn_00559da0(node,0);copy=fn_00544500(target);TQUAL(copy)&=~0x20UL;child=CExpr_Convert(child,copy,quals,0,checkAccess);result=makemonadicnode(child,4);result->type=TARGET(target);result->flags=(result->flags&~CVMASK)|q;}if(fn_0070f1ee&&target->kind==12&&(TQUAL(target)&0xa0)==0xa0&&CExpr_IsLValue(result))result->flags|=0x1000;}
        return result;
    }
    if((node->type->kind==13&&target->kind!=13)||(node->type->kind==7&&target->kind!=7))node=pointer_generation(node);else node=fn_0055ba60(node);
    if(node->kind==0x4b&&target->kind!=11){if(fn_005e59b0((ConvObjectList *)LEFT(node),(void *)node->data.op.fourth,target,&result))return result;if(target->kind!=6)goto failed;}
    if(node->kind==0x3b&&node->data.object->type->kind==7&&(((ConvFunction *)node->data.object->type)->flags&0x100000)){single.next=NULL;single.object=node->data.object;if(fn_005e59b0(&single,NULL,target,&result))return result;}
    else if(node->type->kind==6||target->kind==6){if(!node->type->size)CDecl_CompleteType(node->type);if(target->kind==6){fn_00514a80(target);if(!fn_00542530(target,0)||fn_00542350(target)){if(node->type==target)return node;result=fn_005e3b50(node,target,quals,checkAccess,0,1);if(result)return result;}}
        result=fn_005e3cc0(node,target,quals,NULL,1,explicitCast,0);if(result){result->flags=(result->flags&~CVMASK)|q;return result;}
    }else{
        if(!explicitCast){if(is_typesame(node->type,target)){if(node->kind==4&&q!=(node->flags&CVMASK)){switch(node->type->kind){case 1:case 2:case 4:case 12:node=makemonadicnode(node,0x32);break;default:node->flags|=0x1000;}}node->type=target;node->flags=(node->flags&~CVMASK)|q;return node;}
            if(fn_0070f203&&(UInt8)(target->kind-1)<2&&(UInt8)(node->type->kind-1)<2)fn_005a8080(node,target);}
        switch(target->kind){
            case 1:if(target!=&stbool){switch(node->type->kind){case 1:case 2:break;case 4:node->type=*(ConvType **)((UInt8 *)node->type+14);break;case 12:
                if(fn_0070f215)CError_Warning(0x28f7);if(target->size<node->type->size&&fn_0070f20d)CError_Warning(0x288e);
                if(node->kind==0x32&&(child=LEFT(node))->kind==0x34){child->type=target;child->flags=(child->flags&~CVMASK)|q;child->data.value=CExpr_IntConstConvert(target,&stunsignedlong,child->data.value);return child;}
                if(target->size!=4){node=makemonadicnode(node,0x32);node->type=&stunsignedlong;}node=makemonadicnode(node,0x32);node->type=target;node->flags=(node->flags&~CVMASK)|q;return node;
                default:goto failed;}goto arithmetic;
            }switch(node->type->kind){case 1:case 2:case 3:case 4:case 11:case 12:return fn_005a8680(node,explicitCast);default:break;}break;
            case 2:switch(node->type->kind){case 4:node->type=*(ConvType **)((UInt8 *)node->type+14);case 1:case 2:
arithmetic: if(node->kind==0x32&&node->type->kind==target->kind&&node->type->size==target->size){a=fn_00454260(target);b=fn_00454260(node->type);if(a==b&&quals==(node->flags&CVMASK)){node->type=target;node->flags|=8;return node;}}
                result=fn_0055b2d0(node,target);result->flags=(result->flags&~CVMASK)|q;if(result->kind==0x32&&result!=node)result->flags|=8;return fn_00463460(result);
                default:break;}break;
            case 4:if(!explicitCast&&node->type!=target&&fn_0070f1f9)CError_Warning(0x27e1,node->type,node->flags&CVMASK,target,quals);node=CExpr_Convert(node,*(ConvType **)((UInt8 *)target+14),quals,explicitCast,checkAccess);if(node->kind!=0x34)node=makemonadicnode(node,0x32);node->type=target;node->flags=(node->flags&~CVMASK)|q;return fn_00463460(node);
            case 11:if(node->type->kind!=11)node=fn_005432e0(node,target,1,explicitCast);if(node->type->kind==11){node=fn_00543360(node,node->type,target,checkAccess);node->flags=(node->flags&~CVMASK)|q;return node;}break;
            case 12:from=node->type;switch(from->kind){case 4:node->type=*(ConvType **)((UInt8 *)from+14);case 1:
                if(fn_0070f215&&(node->kind!=0x34||!iszero(node)))CError_Warning(0x28f8);if(node->type->size!=4){if(node->kind!=0x34)node=makemonadicnode(node,0x32);node->type=&stunsignedlong;}node=makemonadicnode(node,0x32);node->type=target;node->flags=(node->flags&~CVMASK)|q;return fn_00463460(node);
                case 12:if(TARGET(from)->kind==6&&TARGET(target)->kind==6)node=fn_0055aa20(node,TARGET(from),TARGET(target),1,checkAccess);
                    if(fn_0070f1af&&fn_0070f1a8){a=TARGET(node->type)->kind;b=TARGET(target)->kind;if((a==7||b==7)&&a!=b)CError_Warning(0x2807,node->type,node->flags&CVMASK,target,quals);}
                    if(node->kind!=0x32)node=makemonadicnode(node,0x32);node->type=target;node->flags=(node->flags&~CVMASK)|q;if(explicitCast)node->flags|=8;return fn_00463460(node);
                default:break;}break;
        }
    }
failed: if((target->kind==3||node->type->kind==3)&&(result=fn_005e2a20(node,target))!=NULL){result->flags=(result->flags&~CVMASK)|q;return result;}if(explicitCast&&(result=fn_004648e0(node,target,quals))!=NULL)return result;
    CError_Error(explicitCast?0x2807:0x27e1,node->type,node->flags&CVMASK,target,quals);return nullnode();
}
ConvCandidate *fn_005e02c0(ConvObject *object,ConvType *type,UInt32 quals,ConvList *arguments,ConvCandidate *list,SInt32 count) {
    ConvCandidate *candidate=CompilerTools_AllocatePool((count-2)*32+124);ConvObject *origin=NULL;ConvFunction *function;ConvArg *arg;ConvScore *score;ConvNode *node;UInt32 thisQual;ConvType *thisType;UInt8 ok;
    candidate->scores[0].kind=0;score=candidate->scores+1;
    if(!type){function=(ConvFunction *)object->type;if(function->base.kind!=7||!(function->flags&0x10))return list;if(function->flags&0x100000){origin=object;object=fn_005dca80(object,NULL,arguments->next,0);if(!object)return list;function=(ConvFunction *)object->type;}
        arg=function->args;if(!arg||!arguments)return list;node=arguments->node;if(!node)return list;thisType=fn_005e66c0(object,&thisQual);if(!fn_005e4c50(node,thisType,thisQual,1,&score->standard))return list;score->kind=3;MATCHBYTE(score,26)=1;arguments=arguments->next;arg=arg->next;++score;
    }else{node=arguments->node;if(fn_005e4c50(node,type,quals,0,&score->standard)){score->kind=3;ok=1;}else if((node->type->kind==6||type->kind==6||(type->kind==12&&(TQUAL(type)&0x20)&&TARGET(type)->kind==6))&&fn_005e3cc0(node,type,quals,score,0,0,0)){score->kind=2;ok=1;}else ok=0;if(!ok)return list;
        if(type->kind==12&&TARGET(type)->kind==7)arg=((ConvFunction *)TARGET(type))->args;else{if(type->kind!=7)CError_Internal(filename,4229);arg=((ConvFunction *)type)->args;}arguments=arguments->next;++score;
    }
    for(;arg&&arg->type!=&stvoid;arg=arg->next){if(arg==&fn_007037c0||arg==&fn_0070bb08){for(;arguments;arguments=arguments->next){score->kind=1;++score;}goto done;}
        if(!arguments){if(!arg->defaultValue)return list;goto done;}node=arguments->node;if(node->kind==0x4b&&MATCHBYTE(node,41))arguments->node=fn_00543680(node,arg->type,arg->quals,1,0);node=arguments->node;type=arg->type;quals=arg->quals;
        if(fn_005e4c50(node,type,quals,0,&score->standard)){score->kind=3;ok=1;}else if((node->type->kind==6||type->kind==6||(type->kind==12&&(TQUAL(type)&0x20)&&TARGET(type)->kind==6))&&fn_005e3cc0(node,type,quals,score,0,0,0)){score->kind=2;ok=1;}else ok=0;if(!ok)return list;++score;arguments=arguments->next;
    }
    if(arguments)return list;
done:candidate->object=object;candidate->templateObject=origin;candidate->next=list;return candidate;
}
ConvNode *fn_005dffb0(ConvNode *node,ConvList *arguments) {
    UInt8 lookup[48],iterator[32];ConvList *all;ConvObjectList *item,*single;ConvCandidate *list=NULL,*best;ConvObject *object;ConvFunction *function;ConvType *type;ConvNode *result;void *name;SInt32 count=1;
    if(node->type->kind!=6)CError_Internal(filename,4302);CDecl_CompleteType(node->type);for(all=arguments;all;all=all->next){CDecl_CompleteType(all->node->type);++count;}
    all=CompilerTools_AllocatePool(8);all->node=node;all->next=arguments;name=CMangler_OperatorName(0x28);
    if(fn_004e6a10(node->type,lookup,name)){for(item=*(ConvObjectList **)(lookup+12);item;item=item->next)if(item->object->kind==5)list=fn_005e02c0(item->object,NULL,0,all,list,count);}
    fn_005a85c0(iterator,node->type);object=fn_005a8450(iterator);while(object){function=(ConvFunction *)object->type;if(!(function->flags&0x100000)){type=function->result;if(type->kind==12&&(TQUAL(type)&0x20))type=TARGET(type);if((type->kind==7||(type->kind==12&&TARGET(type)->kind==7))&&(!(node->flags&1)||(function->flags&0x8000))&&(!(node->flags&2)||(function->flags&0x10000)))list=fn_005e02c0(object,type,function->quals,all,list,count);}object=fn_005a8450(iterator);}
    if(!list){CError_Error(0x27b1);return nullnode();}best=fn_005e16f0(list,count,name,NULL,arguments);function=(ConvFunction *)best->object->type;
    if(function->flags&0x40){type=function->result;if(type->kind==12&&(TQUAL(type)&0x20)){if(TARGET(type)->kind!=7){type=TARGET(type);if(type->kind!=12||TARGET(type)->kind!=7)CError_Internal(filename,4371);}}else if(type->kind!=12||TARGET(type)->kind!=7)CError_Internal(filename,4377);return CExpr_MakeFunctionCall(CExpr_Convert(node,type,function->quals,0,1),arguments);}
    result=CExpr_NewENode(0x4b);result->type=&fn_006771c2;RIGHT(result)=*(ConvNode **)(lookup+20);THIRD(result)=*(ConvNode **)(lookup+24);result->data.op.sixth=node;MATCHBYTE(result,41)=1;single=galloc(8);single->next=NULL;single->object=best->object;LEFT(result)=(ConvNode *)single;return CExpr_MakeFunctionCall(result,arguments);
}
static inline ConvType *builtin_type(SInt32 index,UInt8 arithmetic) {
    if(arithmetic){switch(index){case 0:return &stsignedint;case 1:return &stunsignedint;case 2:return &stsignedlong;case 3:return &stunsignedlong;case 4:return &stfloat;case 5:return &stdouble;case 6:return &stlongdouble;case 7:return fn_0070f1bd?&stsignedlonglong:NULL;case 8:return fn_0070f1bd?&stunsignedlonglong:NULL;default:return NULL;}}
    switch(index){case 0:return &stsignedint;case 1:return &stunsignedint;case 2:return &stsignedlong;case 3:return &stunsignedlong;case 4:return fn_0070f1bd?&stsignedlonglong:NULL;case 5:return fn_0070f1bd?&stunsignedlonglong:NULL;default:return NULL;}
}
ConvCandidate *fn_005e0710(void *listValue,ConvNode *left,SInt16 token,ConvNode *right) {
    ConvCandidate *list=listValue;ConvType *a,*b,*difference;ConvTypeItem *first,*second,*item;ConvObject *object;ConvFunction *function;UInt8 iterator[32],arithmetic=0,integral=0,assignArithmetic=0,assignIntegral=0,enumSame=0,memberSame=0,pointerPair=0,leftPointer=0,rightPointer=0;SInt32 op=token,i,j;
    left=pointer_generation(left);right=pointer_generation(right);
    if((UInt32)(op-0x25)<2||op==0x5e||op==0x7c||(UInt32)(op-0x17a)<2)integral=1;
    else if((UInt32)(op-0x2a)<2||op==0x2d||op==0x2f||op==0x3a||op==0x3c||op==0x3e||(UInt32)(op-0x176)<4||(UInt32)(op-0x183)<2)arithmetic=1;
    else if((UInt32)(op-0x16a)<2||(UInt32)(op-0x16d)<2)assignArithmetic=1;
    else if(op==0x16c||(UInt32)(op-0x16f)<5)assignIntegral=1;
    else if((UInt32)(op-0x174)<2)return fn_005e1200(list,left,&stbool,0,right,&stbool,0);
    else if((UInt32)(op-0x17c)<2)return fn_005e1120(list,token,left,right);
    else if(op==0x181){if(left->type->kind==12&&TARGET(left->type)->kind==6&&right->type->kind==6){a=TARGET(left->type);fn_005a85c0(iterator,right->type);for(object=fn_005a8450(iterator);object;object=fn_005a8450(iterator)){function=(ConvFunction *)object->type;b=function->result;if(b->kind==11&&(*(ConvType **)((UInt8 *)b+10))->kind==6&&(a==*(ConvType **)((UInt8 *)b+10)||fn_0053f270(a,*(ConvType **)((UInt8 *)b+10))))list=fn_005e1200(list,left,left->type,left->flags&CVMASK,right,b,function->quals);}}return list;}
    if(arithmetic||integral){for(i=0;(a=builtin_type(i,arithmetic))!=NULL;++i)for(j=0;(b=builtin_type(j,arithmetic))!=NULL;++j)list=fn_005e1200(list,left,a,0,right,b,0);}
    else if(assignArithmetic||assignIntegral){if(fn_00453240(left->type,left->flags&CVMASK))return list;if((assignArithmetic&&(UInt8)(left->type->kind-1)<2)||(assignIntegral&&left->type->kind==1)){for(i=0;(a=builtin_type(i,assignArithmetic))!=NULL;++i)list=fn_005e1200(list,left,left->type,0,right,a,0);}if(assignIntegral)return list;}
    if(op==0x2b||op==0x5b){rightPointer=1;leftPointer=1;}else if(op==0x2d){pointerPair=1;leftPointer=1;}else if(op==0x3a){memberSame=1;pointerPair=1;enumSame=1;}else if(op==0x3c||op==0x3e||(UInt32)(op-0x178)<2){pointerPair=1;enumSame=1;}else if((UInt32)(op-0x16d)<2)leftPointer=1;else if((UInt32)(op-0x176)<2){memberSame=1;pointerPair=1;enumSame=1;}else return list;
    first=fn_005e14d0(left);second=fn_005e14d0(right);difference=fn_005547c0();item=first;
    for(;;){if(!item){item=second;if(!second)return list;second=NULL;}a=item->type;if(a->kind==12&&(TQUAL(a)&0x20))a=TARGET(a);
        switch(a->kind){case 4:if(enumSame)list=fn_005e1200(list,left,a,item->quals,right,a,item->quals);break;case 11:if(memberSame)list=fn_005e1200(list,left,a,item->quals,right,a,item->quals);break;case 12:
            if(leftPointer)list=fn_005e1200(list,left,a,item->quals,right,difference,0);if(rightPointer)list=fn_005e1200(list,left,difference,0,right,a,item->quals);
            if(pointerPair){if(TARGET(a)->kind!=12)list=fn_005e1200(list,left,a,3,right,a,3);else{b=fn_00544500(a);TQUAL(b)|=3;list=fn_005e1200(list,left,b,item->quals,right,b,item->quals);}}break;
        }item=item->next;
    }
}
static inline UInt8 operator_score(ConvNode *node,ConvType *type,UInt32 quals,ConvScore *score) {
    if(fn_005e4c50(node,type,quals,0,&score->standard)){score->kind=3;return 1;}
    if((node->type->kind==6||type->kind==6||(type->kind==12&&(TQUAL(type)&0x20)&&TARGET(type)->kind==6))&&fn_005e3cc0(node,type,quals,score,0,0,0)){score->kind=2;return 1;}return 0;
}
static inline ConvArg *operator_first_arg(ConvFunction *function) {
    ConvArg *arg;
    if(function->base.kind!=7)CError_Internal(filename,140);arg=function->args;if(!arg)CError_Internal(filename,141);if((function->flags&0x10)&&!function->mode){arg=arg->next;if(!arg)CError_Internal(filename,145);}return arg;
}
static inline SInt32 operator_arg_count(ConvFunction *function) {
    ConvArg *arg;SInt32 count=0;
    if(function->base.kind!=7)CError_Internal(filename,166);arg=function->args;if(!arg)CError_Internal(filename,167);if((function->flags&0x10)&&!function->mode)arg=arg->next;for(;arg;arg=arg->next)++count;return count;
}
UInt8 fn_005df2f0(SInt16 token,ConvNode *left,ConvNode *right,ConvNode **out) {
    ConvType *leftType=left->type,*lt,*rt;ConvFunction *function;ConvCandidate local,*list=NULL,*copy,*best;ConvObjectList *members,*item,single;ConvObject *object,*origin;ConvList *arguments,*second;ConvArg *arg;UInt8 lookup[48],context[28];UInt32 lq,rq;void *name;SInt32 count=right!=NULL;
    if(leftType->kind==6)CDecl_CompleteType(leftType);else if(leftType->kind!=4&&(!right||(right->type->kind!=6&&right->type->kind!=4)))return 0;
    name=CMangler_OperatorName(token);memclrw(context,28);arguments=CompilerTools_AllocatePool(8);arguments->node=left;if(right){second=CompilerTools_AllocatePool(8);arguments->next=second;second->node=right;second->next=NULL;}else arguments->next=NULL;
    if(leftType->kind==6&&fn_004e6a10(leftType,lookup,name)&&(token!=0x3d||(*(ConvType **)(lookup+20)==leftType&&*(ConvType **)(lookup+20)==*(ConvType **)(lookup+24)))){
        if(*(ConvObject **)(lookup+8)){single.next=NULL;single.object=*(ConvObject **)(lookup+8);members=&single;}else{members=*(ConvObjectList **)(lookup+12);if(!members)CError_Internal(filename,4466);}
        for(item=members;item;item=item->next){object=item->object;if(object->kind!=5||object->type->kind!=7)continue;origin=NULL;
            if(((ConvFunction *)object->type)->flags&0x100000){origin=object;object=fn_005dca80(object,NULL,arguments->next,0);if(!object)continue;}
            lt=fn_005e66c0(object,&lq);function=(ConvFunction *)object->type;
            if(operator_arg_count(function)!=count)continue;
            if(right){arg=operator_first_arg(function);rt=arg->type;rq=arg->quals&3;}else{rt=NULL;rq=0;}
            if(!fn_005e4c50(left,lt,lq,1,&local.scores[0].standard))continue;local.scores[0].kind=3;MATCHBYTE(local.scores,26)=1;
            if(right&&!operator_score(right,rt,rq,&local.scores[1]))continue;
            local.next=list;local.object=object;local.templateObject=origin;copy=CompilerTools_AllocatePool(124);*copy=local;list=copy;*(void **)(context+4)=*(void **)(lookup+20);*(void **)(context+8)=*(void **)(lookup+24);
        }
    }
    if(!fn_004e6c70(fn_00711be0,lookup,name))members=NULL;else if(*(ConvObject **)(lookup+8)){single.next=NULL;single.object=*(ConvObject **)(lookup+8);members=&single;}else members=*(ConvObjectList **)(lookup+12);
    if(fn_0070f1c7)members=fn_004eabd0(members,name,arguments);members=fn_004ea5d0(members,0);
    for(item=members;item;item=item->next){object=item->object;if(object->kind!=5||object->type->kind!=7||(((ConvFunction *)object->type)->flags&0x10))continue;origin=NULL;
        if(((ConvFunction *)object->type)->flags&0x100000){origin=object;object=fn_005dca80(object,NULL,arguments,0);if(!object)continue;}
        function=(ConvFunction *)object->type;arg=operator_first_arg(function);lt=arg->type;lq=arg->quals&3;
        if(operator_arg_count(function)!=count+1)continue;
        if(right){arg=operator_first_arg(function);arg=arg->next;if(!arg)CError_Internal(filename,149);rt=arg->type;rq=arg->quals&3;}
        if(!operator_score(left,lt,lq,&local.scores[0]))continue;if(right&&!operator_score(right,rt,rq,&local.scores[1]))continue;
        local.next=list;local.object=object;local.templateObject=origin;copy=CompilerTools_AllocatePool(124);*copy=local;list=copy;
    }
    if(right)list=fn_005e0710(list,left,token,right);else list=fn_005e0f00(list,token,left);if(!list)return 0;
    out[0]=NULL;out[1]=NULL;out[2]=NULL;best=fn_005e16f0(list,count,name,NULL,arguments);
    if(best->object){function=(ConvFunction *)best->object->type;if(!(function->flags&0x10)||function->mode)left=fn_005a7480(NULL,NULL,best->object,NULL,arguments,0);else{if(!*(void **)(context+4))CError_Internal(filename,4587);*(ConvNode **)(context+20)=arguments->node;left=CExpr_GenericFuncCall(context,best->object,arguments->next,0,1);}out[0]=checkreference(left);return 1;}
    if(left->type->kind==6)out[1]=CExpr_Convert(left,best->left,best->leftQuals,0,1);else out[1]=left;
    if(right){if(right->type->kind==6)out[2]=CExpr_Convert(right,best->right,best->rightQuals,0,1);else out[2]=right;}return 1;
}
