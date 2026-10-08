/* Native CExprTools views; related 1.2.5 CExpr/CExpr2 algorithms are migrated here. */
#include "compiler/common.h"
#include <stddef.h>
#pragma pack(push,2)
typedef struct ExprType {UInt8 kind,pad;SInt32 size;} ExprType;
typedef struct ExprDerivedType {ExprType base;ExprType *target;UInt32 quals;} ExprDerivedType;
typedef struct ExprIntegralType {ExprType base;UInt8 rank;} ExprIntegralType;
typedef struct ExprEnumType {ExprType base;UInt8 unknown06[8];ExprType *underlying;} ExprEnumType;
typedef struct ExprFunctionType {ExprType base;void *args,*exspec;ExprType *result;UInt32 quals,flags;} ExprFunctionType;
typedef struct ExprWords {UInt32 hi,lo;} ExprWords;
typedef struct ExprNode ExprNode;
typedef struct ExprList {struct ExprList *next;ExprNode *node;} ExprList;
typedef struct ExprObject {UInt8 kind,access,storage,pad03;UInt32 unknown04;void *space,*name;ExprType *type;UInt32 quals;UInt16 sclass,flags;UInt8 unknown1c[36];struct ExprObject *alias;UInt32 valueLo;SInt32 offset;} ExprObject;
struct ExprNode {UInt8 kind,cost;UInt16 unknown02;ExprType *type;UInt32 flags,unknown0c;union {ExprWords value;struct {ExprNode *left,*right,*third,*fourth,*fifth,*sixth;} operands;struct {ExprType *type;UInt32 id;UInt8 needsDtor;} temp;ExprObject *object;UInt8 raw[30];}data;};
typedef struct ExprStatement {struct ExprStatement *next;UInt8 kind,unknown05[5];ExprNode *node;} ExprStatement;
#pragma pack(pop)
typedef char ExprNodeSize[(sizeof(ExprNode)==46)?1:-1];
typedef char ExprNodePayload[(offsetof(ExprNode,data)==16)?1:-1];
typedef char ExprPointerQuals[(offsetof(ExprDerivedType,quals)==10)?1:-1];
typedef char ExprObjectAlias[(offsetof(ExprObject,alias)==64)?1:-1];
#define QUALS 0x1f200003UL
#define TARGET(t) (((ExprDerivedType *)(t))->target)
#define TQUAL(t) (((ExprDerivedType *)(t))->quals)
#define RANK(t) (((ExprIntegralType *)(t))->rank)
#define ENUMTYPE(t) (((ExprEnumType *)(t))->underlying)
#define LEFT(n) ((n)->data.operands.left)
#define RIGHT(n) ((n)->data.operands.right)
#define THIRD(n) ((n)->data.operands.third)
static char filename[]="CExprTools.c";
static UInt8 has_func_call;
extern ExprType stbool,stchar,stunsignedchar,stunsignedshort,stsignedint,stunsignedint,stsignedlong,stunsignedlong,stsignedlonglong,stunsignedlonglong;
extern ExprWords cint64_zero,cint64_one,fn_00699b6e;
extern UInt8 fn_0070f1a8,fn_0070f1af,fn_0070f1b4,fn_0070f1b9,fn_0070f1db,fn_0070f1dc,fn_0070f1de,fn_0070f1ee,fn_0070f008;
extern void *this_name_node,*cscope_currentfunc,*cscope_currentclass;
extern ExprObject *clear_func;
extern ExprNode *CExpr_NewENode(UInt8),*CExpr_CopyENode(ExprNode *),*makemonadicnode(ExprNode *,UInt8),*makediadicnode(ExprNode *,ExprNode *,UInt8),*nullnode(void);
extern ExprType *CDecl_NewPointerType(ExprType *),*CABI_GetSizeTType(void);
extern UInt32 CParser_GetUniqueID(void),fn_00545160(UInt32,UInt32);
extern void CError_Internal(const char *,int),CError_Error(int,...),CError_Warning(int,...);
extern SInt16 is_typesame(ExprType *,ExprType *);
extern UInt8 fn_00453240(ExprType *,UInt32),is_unsigned(ExprType *),CMach_PassResultInHiddenArg(ExprType *);
extern ExprObject *fn_0053f4c0(void);
extern ExprNode *fn_00530810(ExprNode *,UInt8),*fn_00543c00(ExprObject *,ExprType *),*CExpr_New_EOBJREF_Node(ExprObject *,UInt8),*intconstnode(ExprType *,SInt32),*CExpr_New_EINDIRECT_Node(ExprObject *);
extern UInt8 CInt64_Equal(ExprWords,ExprWords),CMach_FloatIsZero(ExprWords),fn_004e38e0(ExprWords);
extern ExprWords CMach_CalcIntDiadic(ExprType *,ExprWords,int,ExprWords),CMach_CustomIntConvert(ExprType *,ExprType *,ExprWords),CMach_CalcFloatConvertFromInt(ExprType *,ExprWords),CMach_CalcFloatConvert(ExprType *,ExprWords),fn_004e4190(ExprType *,ExprWords);
extern ExprNode *argumentpromotion(ExprNode *,ExprType *,UInt32,UInt8),*fn_005418b0(ExprNode *,ExprType *,ExprType *,UInt8,UInt8,UInt8),*fn_005e1f10(ExprNode *,ExprType *,UInt32,UInt8,UInt8),*fn_00543680(ExprNode *,ExprType *,UInt32,UInt8,UInt8),*fn_0051ea50(ExprNode *,ExprNode *),*fn_00542fc0(UInt8,ExprNode *,ExprNode *);
extern ExprNode *fn_005e2a20(ExprNode *,ExprType *),*fn_0052df70(ExprType *),*funccallexpr(ExprObject *,ExprNode *,ExprNode *,ExprNode *,ExprNode *),*fn_005a8cd0(ExprNode *,ExprNode *,ExprList *,ExprType *,UInt32,UInt8,UInt8,UInt8);
extern UInt8 fn_00463ba0(ExprNode *,void *,ExprType *),fn_00542360(ExprType *);
extern void CDecl_CompleteType(ExprType *),fn_00514a10(ExprType *),fn_0045c2c0(int,...),fn_005454e0(ExprType *,ExprType **,UInt8 *);
extern ExprType *fn_005454a0(ExprType *),*fn_005454c0(ExprType *);
extern void *fn_00514dc0(ExprType *);
typedef void (*ExprVisitor)(ExprNode *);
typedef ExprNode *(*ExprRewriter)(ExprNode *);
ExprNode *fn_00559240(ExprNode *,UInt8,UInt8),*fn_00559b50(ExprNode *,UInt8),*fn_00559da0(ExprNode *,UInt8),*fn_00559ff0(ExprNode *),*fn_0055a140(ExprNode *),*fn_0055a1c0(ExprNode *),*fn_0055a2a0(ExprNode *),*CExpr_NewETEMPNode(ExprType *,UInt8),*fn_0055b2d0(ExprNode *,ExprType *),*integralpromote(ExprNode *),*fn_0055b6a0(ExprNode *),*fn_0055b810(ExprNode *),*checkreference(ExprNode *),*fn_0055ba60(ExprNode *),*fn_0055b280(ExprNode *,ExprType *),*fn_0055bf70(ExprNode *,ExprRewriter);
UInt8 CExpr_IsLValue(ExprNode *),fn_005597d0(ExprNode *);
int isnotzero(ExprNode *),iszero(ExprNode *);
void fn_0055ad80(ExprNode **,ExprNode **,UInt8),CExpr_ENodeTreeWalk(ExprNode *,ExprVisitor);
ExprNode *CExpr_NewETEMPNode(ExprType *type,UInt8 unique) {
    ExprNode *node=CExpr_NewENode(0x44);node->type=CDecl_NewPointerType(type);node->data.temp.type=type;
    node->data.temp.id=unique?CParser_GetUniqueID():0;node->data.temp.needsDtor=0;return node;
}
ExprNode *fn_0055a2a0(ExprNode *node) {
    ExprNode *copy;
    if(node->type->kind!=12)CError_Internal(filename,1730);
    copy=CExpr_CopyENode(node);copy=makemonadicnode(copy,4);copy->type=TARGET(copy->type);return copy;
}
ExprNode *fn_0055a1c0(ExprNode *node) {
    ExprNode *temp=CExpr_NewETEMPNode(node->type,1),*assignment,*result;
    temp->flags=node->flags;assignment=makediadicnode(fn_0055a2a0(temp),node,0x1e);
    RIGHT(assignment)=CExpr_CopyENode(node);*node=*assignment;
    result=makemonadicnode(temp,4);result->type=node->type;return result;
}
ExprNode *fn_0055a140(ExprNode *node) {
    ExprNode *temp=CExpr_NewETEMPNode(node->type,1),*copy=CExpr_CopyENode(temp),*left,*result;
    left=makemonadicnode(temp,4);left->type=node->type;left=makediadicnode(left,node,0x1e);
    result=makediadicnode(left,copy,0x29);result->type=copy->type;result=makemonadicnode(result,4);result->type=node->type;return result;
}
ExprNode *fn_00559ff0(ExprNode *node) {
    for(;;) {
        if(node->kind<4||(node->kind>=0x1e&&node->kind<=0x28)){node=LEFT(node);continue;}
        if(node->kind==0x29){node=RIGHT(node);continue;}
        if(node->kind!=4)return NULL;
        node=LEFT(node);while(node->kind==0x29)node=RIGHT(node);
        return node->kind==0x3b?CExpr_CopyENode(node):fn_0055a1c0(node);
    }
}
UInt8 fn_005597d0(ExprNode *node) {
    switch(node->kind) {
        case 0x38:return fn_005597d0(RIGHT(node))&&fn_005597d0(THIRD(node));
        case 0x39:
            if(((ExprFunctionType *)THIRD(node))->result->kind!=12||(((ExprFunctionType *)THIRD(node))->flags&0x1000))return 0;
            if(LEFT(node)->kind==0x3b&&LEFT(node)->data.object==clear_func)return 0;
            break;
        case 0x44:return 0;
    }
    return 1;
}
UInt8 CExpr_IsLValue(ExprNode *node) {
    UInt8 flag=fn_0070f1a8;
    while(node->kind!=4) {
        switch(node->kind) {
            case 2:case 3:return fn_0070f1a8;
            case 0x1e:case 0x1f:case 0x20:case 0x21:case 0x22:case 0x23:case 0x24:case 0x25:case 0x26:case 0x27:case 0x28:
                if(!flag)return 0;node=LEFT(node);break;
            case 0x29:if(node->flags&0x8000)return 1;if(!flag)return 0;node=RIGHT(node);break;
            case 0x38:
                if(fn_0070f1a8&&is_typesame(RIGHT(node)->type,THIRD(node)->type)&&
                    (RIGHT(node)->type->kind!=12||((RIGHT(node)->flags&QUALS)==(THIRD(node)->flags&QUALS))))
                    return CExpr_IsLValue(RIGHT(node))&&CExpr_IsLValue(THIRD(node));
                return 0;
            default:return 0;
        }
    }
    if(node->flags&0x8000)return 1;
    if(node->flags&0x1000)return 0;
    node=LEFT(node);while(node->kind==0x29)node=RIGHT(node);return fn_005597d0(node);
}
ExprNode *fn_00559240(ExprNode *node,UInt8 checkConst,UInt8 report) {
    ExprNode *result,*tmp;
    for(;;) {
        switch(node->kind) {
            case 4:
                if(report) {
                    if(!CExpr_IsLValue(node))CError_Warning(0x279e);
                    if(LEFT(node)->kind==0x3b&&LEFT(node)->data.object->name==this_name_node&&cscope_currentfunc&&cscope_currentclass&&LEFT(node)->data.object==fn_0053f4c0())CError_Error(0x27cd);
                }
                if(checkConst&&fn_00453240(node->type,node->flags&QUALS))CError_Error(0x27c3);
                return node;
            case 0x32:
                if(node->type->kind==12&&LEFT(node)->type->kind==12&&
                    (!(node->flags&8)||fn_0070f1b4||!fn_0070f1af)&&(LEFT(node)->kind==4||LEFT(node)->kind==0x32)) {
                    LEFT(node)->type=node->type;LEFT(node)->flags=0;LEFT(node)->flags=(LEFT(node)->flags&~QUALS)|(node->flags&QUALS);node=LEFT(node);continue;
                }
                break;
            case 0x29:
                if(!fn_0070f1a8&&!(node->flags&0x8000))CError_Warning(0x279e);
                tmp=fn_00559ff0(node);
                if(tmp){result=makediadicnode(node,tmp,0x29);result->type=RIGHT(result)->type;result=makemonadicnode(result,4);result->type=node->type;return result;}
                break;
            case 0x38:
                if(is_typesame(RIGHT(node)->type,THIRD(node)->type)&&
                    (RIGHT(node)->type->kind!=12||((RIGHT(node)->flags&QUALS)==(THIRD(node)->flags&QUALS)))) {
                    RIGHT(node)=fn_00559240(RIGHT(node),checkConst,report);THIRD(node)=fn_00559240(THIRD(node),checkConst,report);
                    if(RIGHT(node)->kind==4&&THIRD(node)->kind==4&&LEFT(RIGHT(node))->kind!=0x33&&LEFT(THIRD(node))->kind!=0x33) {
                        if(!fn_0070f1a8)CError_Warning(0x279e);
                        RIGHT(node)=fn_00559da0(RIGHT(node),0);THIRD(node)=fn_00559da0(THIRD(node),0);node->type=RIGHT(node)->type;
                        result=makemonadicnode(node,4);result->type=TARGET(result->type);return result;
                    }
                }
                break;
            case 0x39:if((node->type->kind==5||node->type->kind==6)&&!CMach_PassResultInHiddenArg(node->type))return fn_0055a140(node);break;
            case 0x51:fn_00530810(node,1);continue;
            case 0x52:node=fn_00543c00(node->data.object,node->type);continue;
            case 2:case 3:case 0x1e:case 0x1f:case 0x20:case 0x21:case 0x22:case 0x23:case 0x24:case 0x25:case 0x26:case 0x27:case 0x28:
                if(fn_0070f1a8&&(tmp=fn_00559ff0(node))!=NULL){result=makediadicnode(node,tmp,0x29);result->type=RIGHT(result)->type;result=makemonadicnode(result,4);result->type=node->type;return result;}
                break;
        }
        break;
    }
    if(report)CError_Error(0x279e);return node;
}
void fn_0055a640(ExprNode *node) {
    ExprObject *object=node->data.object;SInt32 offset=0;ExprNode *replacement;
    while(object->storage==6){offset+=object->offset;object=object->alias;}
    if(!offset)node->data.object=object;
    else {ExprNode *left=CExpr_New_EOBJREF_Node(object,1),*right=intconstnode(&stunsignedlong,offset);replacement=makediadicnode(left,right,0xf);*node=*replacement;}
}
ExprNode *fn_00559da0(ExprNode *node,UInt8 flag) {
    ExprNode *copy;ExprObject *object;
    if(node->kind==4) {
        if(flag&&LEFT(node)->kind==0x3b&&LEFT(node)->data.object->name==this_name_node&&cscope_currentfunc&&cscope_currentclass&&LEFT(node)->data.object==fn_0053f4c0())CError_Error(0x27cd);
    } else {node=fn_00559240(node,flag,flag);if(node->kind!=4){if(!flag)CError_Error(0x279e);return nullnode();}}
    copy=CExpr_CopyENode(node);
    for(;;) {
        switch(LEFT(copy)->kind) {
            case 0:case 1:case 2:case 3:copy->kind=0x32;if(copy->type->kind==12)copy->flags=(copy->flags&~QUALS)|(TQUAL(copy->type)&QUALS);copy->type=CDecl_NewPointerType(copy->type);return copy;
            case 0x33:CError_Error(0x27a0);return nullnode();
            case 0x3b:
                object=LEFT(copy)->data.object;if(object->storage==6){fn_0055a640(LEFT(copy));continue;}
                if(object->storage==5)CError_Error(0x27bf);object->flags|=2;
                if(flag&&!fn_0070f1a8&&object->sclass==0x101)CError_Error(0x27b3);break;
            case 0x39:if(flag&&((ExprFunctionType *)THIRD(LEFT(copy)))->result->kind!=12)CError_Warning(0x279e);break;
        }
        LEFT(copy)->type=CDecl_NewPointerType(copy->type);LEFT(copy)->flags=copy->flags;return LEFT(copy);
    }
}
ExprNode *fn_00559b50(ExprNode *node,UInt8 value) {
    ExprType *type=node->type;ExprNode *temp=CExpr_NewETEMPNode(type,1),*address,*assignment,*indirect,*constant,*sequence;
    if(node->kind==4&&LEFT(node)->kind==0x33)address=fn_0055a1c0(LEFT(LEFT(node)));
    else {address=fn_00559ff0(node);if(!address){CError_Error(0x279e);return node;}}
    indirect=makemonadicnode(temp,4);indirect->type=type;assignment=makediadicnode(indirect,node,0x1e);
    if(node->kind==4&&LEFT(node)->kind==0x33){address=makemonadicnode(address,0x33);address->type=LEFT(node)->type;}
    address=makemonadicnode(address,4);address->type=type;constant=nullnode();constant->type=&stbool;constant->data.value.lo=value!=0;constant->data.value.hi=0;
    sequence=makediadicnode(assignment,makediadicnode(address,constant,0x1e),0x29);indirect=makemonadicnode(temp,4);indirect->type=type;return makediadicnode(sequence,indirect,0x29);
}
UInt8 fn_0055a320(ExprNode *node) {
    if(node->kind!=0x34)return 0;
    switch(node->type->size){case 1:return (node->data.value.lo&0xff)==0xff;case 2:return (node->data.value.lo&0xffff)==0xffff;case 3:return (node->data.value.lo&0xffffff)==0xffffff;case 4:return node->data.value.lo==0xffffffff;}
    return CInt64_Equal(node->data.value,fn_00699b6e);
}
UInt8 fn_0055a3b0(ExprNode *node) {if(node->kind==0x34)return CInt64_Equal(node->data.value,cint64_one);if(node->kind==0x35)return fn_004e38e0(node->data.value);return 0;}
int isnotzero(ExprNode *node) {
    ExprObject *object;
    switch(node->kind) {
        case 0x34:return node->data.value.hi!=0||node->data.value.lo!=0;
        case 0x35:return !CMach_FloatIsZero(node->data.value);
        case 0x37:case 0x44:case 0x52:return 1;
        case 0x3b:object=node->data.object;break;
        case 0xf:case 0x10:
            if(LEFT(node)->kind==0x3b&&RIGHT(node)->kind==0x34)object=LEFT(node)->data.object;
            else if(LEFT(node)->kind==0x34&&RIGHT(node)->kind==0x3b)object=RIGHT(node)->data.object;else return 0;break;
        default:return 0;
    }
    switch(object->storage){case 1:return 1;default:return 0;}
}
int iszero(ExprNode *node) {switch(node->kind){case 0x34:return (UInt8)(!node->data.value.hi&&!node->data.value.lo);case 0x35:return CMach_FloatIsZero(node->data.value);default:return 0;}}
ExprNode *fn_0055a510(ExprNode *node) {
    if(node->type->kind!=12&&node->type->kind!=11)node->flags&=~QUALS;
    if(node->type->kind==2){if(fn_0070f1db)node->flags|=0x20000;if(fn_0070f1dc)node->flags|=0x10000;}
    return node;
}
ExprNode *fn_0055a560(ExprNode *node) {
    if(node->type->kind!=12&&node->type->kind!=11)node->flags&=~QUALS;
    if(node->type->kind==2){if(fn_0070f1db)node->flags|=0x20000;if(fn_0070f1dc)node->flags|=0x10000;}
    return node;
}
ExprNode *fn_0055a5b0(ExprNode *node) {
    if(node->type->kind!=12&&node->type->kind!=11)node->flags&=~QUALS;
    if(node->type->kind==2){if(fn_0070f1db)node->flags|=0x20000;if(fn_0070f1dc)node->flags|=0x10000;}
    return node;
}
UInt8 fn_0055a600(void) {if(fn_0070f1de)return 1;return !fn_0070f1dc;}
UInt8 fn_0055a620(ExprNode *node) {if(fn_0070f1de)return 1;return !(node->flags&0x10000);}
void CExpr_CombineQuals(ExprNode *node,ExprNode *left,ExprNode *right) {UInt32 a,b,q;node->flags=0;a=left->flags&QUALS;b=right->flags&QUALS;q=fn_00545160(a,b);q|=(a|b)&0xe0ffffff;node->flags&=~QUALS;node->flags|=q&QUALS;}
ExprNode *fn_0055a730(ExprNode *node) {if(node->type->kind!=12&&node->type->kind!=11)node->flags&=~QUALS;return node;}
void optimizecomm(ExprNode *node) {
    ExprNode *operand;
    if(RIGHT(node)->kind==0x34)return;
    if(LEFT(node)->kind==0x34){
    swap:operand=RIGHT(node);RIGHT(node)=LEFT(node);LEFT(node)=operand;return;
    }
    if(LEFT(node)->kind==0x35)return;
    if(RIGHT(node)->kind!=0x35){if((SInt8)node->type->kind>2)return;if(LEFT(node)->cost<=RIGHT(node)->cost)return;}
    goto swap;
}
ExprWords CExpr_IntConstConvert(ExprType *type,ExprType *old,ExprWords value) {if(type==&stbool)return CMach_CalcIntDiadic(old,value,0x177,cint64_zero);if((type->kind==1&&RANK(type)>=0x17)||(old->kind==1&&RANK(old)>=0x17))return CMach_CustomIntConvert(type,old,value);return CMach_CalcIntDiadic(type,value,0x2b,cint64_zero);}
ExprNode *fn_0055b2d0(ExprNode *node,ExprType *type) {
    if(node->kind==0x34){if(type->kind==2){node->kind=0x35;node->data.value=CMach_CalcFloatConvertFromInt(node->type,node->data.value);}else node->data.value=CExpr_IntConstConvert(type,node->type,node->data.value);node->type=type;node->flags&=~QUALS;return node;}
    if(node->kind==0x35){if(type->kind==2){node->data.value=CMach_CalcFloatConvert(type,node->data.value);node->type=type;node->flags&=~QUALS;return node;}if(type->kind==1){node->data.value=fn_004e4190(type,node->data.value);node->kind=0x34;node->type=type;node->flags&=~QUALS;return node;}}
    node=makemonadicnode(node,0x32);node->type=type;node->flags&=~QUALS;return node;
}
ExprNode *integralpromote(ExprNode *node) {
    ExprType *type;
    if(node->type->kind!=1){if(node->type->kind==4)node->type=ENUMTYPE(node->type);else {CError_Error(0x27a0);node=nullnode();}}
    if(RANK(node->type)<7){if(node->kind!=0x34)node=makemonadicnode(node,0x32);node->flags&=~QUALS;type=node->type;
        if(type->size==stunsignedint.size&&(type==&stunsignedshort||type==&stunsignedchar||(type==&stchar&&fn_0070f1b9)))node->type=&stunsignedint;else node->type=&stsignedint;}
    return node;
}
ExprNode *fn_0055b580(ExprNode *node,ExprType *type) {if(node->kind==0x34)node->data.value=CExpr_IntConstConvert(type,node->type,node->data.value);else node=makemonadicnode(node,0x32);node->type=type;return node;}
ExprNode *fn_0055b670(ExprNode *node) {if(node->type->kind==4){node->type=ENUMTYPE(node->type);return node;}CError_Error(0x27a0);return nullnode();}
ExprNode *checkreference(ExprNode *node) {
    ExprNode *result;
    if(node->type->kind==12&&(TQUAL(node->type)&0x20)) {
        result=makemonadicnode(node,4);result->type=TARGET(result->type);result->flags|=0x20;
        if(fn_0070f1ee&&node->type->kind==12&&(TQUAL(node->type)&0xa0)==0xa0&&(node->kind!=4||LEFT(node)->kind!=0x3b))result->flags|=0x1000;
        return result;
    }
    return node;
}
ExprNode *fn_0055b6a0(ExprNode *node) {
    ExprType *type;void *record;ExprNode *result;
    if(node->kind==4){type=node->type;switch(type->kind){case 7:return LEFT(node);case 13:
        if(*((UInt8 *)type+18)&&LEFT(node)->kind==0x3b&&LEFT(node)->data.object->type==type){record=fn_00514dc0(type);if(!*(ExprObject **)((UInt8 *)record+12))CError_Internal(filename,803);return checkreference(CExpr_New_EINDIRECT_Node(*(ExprObject **)((UInt8 *)record+12)));}
        LEFT(node)->type=CDecl_NewPointerType(TARGET(type));return LEFT(node);}}
    else if(node->kind==0x29&&(node->type->kind==7||node->type->kind==13)){RIGHT(node)=fn_0055b6a0(RIGHT(node));node->type=RIGHT(node)->type;}
    return node;
}
ExprNode *fn_0055b810(ExprNode *node) {
    ExprType *type;ExprNode *inner;void *record;
    if(node->kind==4){type=node->type;switch(type->kind){case 7:inner=LEFT(node);if(inner->kind==0x3b&&inner->data.object->storage==5)CError_Error(0x27bf);return inner;case 13:
        inner=LEFT(node);if(inner->kind<=3){node->kind=0x32;node->type=CDecl_NewPointerType(TARGET(node->type));return node;}
        if(*((UInt8 *)type+18)&&inner->kind==0x3b&&inner->data.object->type==type){record=fn_00514dc0(type);if(!*(ExprObject **)((UInt8 *)record+12))CError_Internal(filename,737);return checkreference(CExpr_New_EINDIRECT_Node(*(ExprObject **)((UInt8 *)record+12)));}
        LEFT(node)->type=CDecl_NewPointerType(TARGET(type));LEFT(node)->flags=node->flags;return LEFT(node);}}
    else if(node->kind==0x29&&(node->type->kind==7||node->type->kind==13)){RIGHT(node)=fn_0055b6a0(RIGHT(node));node->type=RIGHT(node)->type;}
    return node;
}
ExprNode *fn_0055ba60(ExprNode *node) {
    ExprObject *object;ExprNode *inner;
    for(;;){if(node->kind!=4)return node;inner=LEFT(node);if(inner->kind!=0x3b)return node;object=inner->data.object;if(object->storage==6){fn_0055a640(inner);continue;}
        if((object->quals&0x10000)&&node->type==object->type){switch(node->type->kind){case 1:case 4:node->kind=0x34;node->data.value=*(ExprWords *)((UInt8 *)object+64);break;
            case 12:node->kind=0x34;node->data.value=*(ExprWords *)((UInt8 *)object+64);node->type=&stunsignedlong;node=makemonadicnode(node,0x32);node->type=object->type;break;
            case 2:node->kind=0x35;if(object->alias)node->data.value=*(ExprWords *)object->alias;else node->data.value=CMach_CalcFloatConvertFromInt(&stsignedlong,cint64_zero);break;
            default:CError_Internal(filename,667);}}
        return node;
    }
}
ExprNode *pointer_generation(ExprNode *node) {return fn_0055ba60(fn_0055b810(node));}
ExprNode *CExpr_ConvertToCondition(ExprNode *node) {
    ExprType *type;
    if(node->kind==0x4b&&(node=fn_00543680(node,NULL,0,1,0))->type->kind!=11){CError_Error(0x285b);return nullnode();}
    type=node->type;switch(type->kind){case 1:case 2:case 12:return node;case 3:return fn_0051ea50(node,nullnode());case 4:node->type=ENUMTYPE(type);return node;case 6:return fn_005e1f10(node,&stbool,0,0,1);case 11:return fn_00542fc0(0x18,node,nullnode());default:CError_Error(0x2888,type,node->flags&QUALS);return nullnode();}
}
ExprNode *fn_0055aa00(ExprNode *node,ExprType *type,UInt32 qual) {node=fn_005e1f10(node,type,qual,1,0);return node;}
ExprNode *fn_0055aa20(ExprNode *node,ExprType *fromClass,ExprType *toClass,UInt8 reverse,UInt8 checkAccess) {
    ExprNode *converted=fn_005418b0(node,fromClass,toClass,reverse,1,checkAccess),*result;
    if(converted==node||(converted->kind==0x32&&LEFT(converted)==node)||(SInt16)isnotzero(node))return converted;
    result=CExpr_CopyENode(converted);result->kind=0x3c;LEFT(result)=CExpr_CopyENode(node);RIGHT(result)=converted;THIRD(result)=(ExprNode *)CParser_GetUniqueID();node->kind=0x3d;LEFT(node)=THIRD(result);return result;
}
ExprNode *fn_0055aaa0(ExprNode *node,ExprNode *preserve) {
    ExprNode *result;if((SInt16)isnotzero(preserve))return node;result=CExpr_CopyENode(node);result->kind=0x3c;LEFT(result)=CExpr_CopyENode(preserve);RIGHT(result)=node;THIRD(result)=(ExprNode *)CParser_GetUniqueID();preserve->kind=0x3d;LEFT(preserve)=THIRD(result);return result;
}
ExprNode *fn_0055b280(ExprNode *node,ExprType *type) {ExprNode *result=fn_005e2a20(node,type);if(result)return result;fn_0045c2c0(0x2804,node->type,node->flags&QUALS,type,0);return node;}
static void fn_0055bc00(ExprNode *node) {if(node->kind==0x39||node->kind==0x3a)has_func_call=1;}
UInt8 CExpr_HasFuncCall(ExprNode *node) {has_func_call=0;CExpr_ENodeTreeWalk(node,fn_0055bc00);return has_func_call;}
ExprNode *CExpr_DoExplicitConversion(ExprType *type,UInt32 qual,ExprList *arguments) {
    ExprNode *node,*value,*size;UInt32 constant[4];
    if(fn_0070f008&&type->kind==5&&*((SInt8 *)type+16)>3&&*((SInt8 *)type+16)<15&&arguments&&!arguments->next) {
        value=fn_0055ba60(fn_0055b810(arguments->node));
        if(fn_00463ba0(value,constant,type)){node=CExpr_NewENode(0x57);node->cost=1;node->flags=qual&QUALS;node->type=type;*(UInt32 *)(node->data.raw)=constant[0];*(UInt32 *)(node->data.raw+4)=constant[1];*(UInt32 *)(node->data.raw+8)=constant[2];*(UInt32 *)(node->data.raw+12)=constant[3];return node;}
    }
    if(type->kind!=6){if(arguments){if(arguments->next)CError_Error(0x2874);value=fn_0055ba60(fn_0055b810(arguments->node));}else value=nullnode();return fn_005e1f10(value,type,qual,1,0);}
    CDecl_CompleteType(type);if(!(*(UInt32 *)((UInt8 *)type+34)&2))CError_Error(0x2798,type,0);fn_00514a10(type);
    if(!arguments&&fn_00542360(type)){size=intconstnode(CABI_GetSizeTType(),type->size);value=fn_0052df70(type);value=funccallexpr(clear_func,value,size,NULL,NULL);node=makemonadicnode(value,4);node->type=type;node->flags=(node->flags&~QUALS)|(qual&QUALS);return node;}
    return fn_005a8cd0(NULL,NULL,arguments,type,qual,1,1,1);
}
void fn_0055aaf0(ExprNode **left,const char *op,ExprNode **right) {
    UInt8 floating=0,complex=0;ExprType *type;ExprNode **smaller;ExprType *common;
    type=(*left)->type;switch(type->kind){case 1:break;case 2:floating=1;break;case 3:complex=1;break;case 4:(*left)->type=ENUMTYPE(type);break;default:CError_Error(0x2889,type,(*left)->flags&QUALS,op,(*right)->type,(*right)->flags&QUALS);*left=nullnode();}
    type=(*right)->type;switch(type->kind){case 1:break;case 2:floating=1;break;case 3:complex=1;break;case 4:(*right)->type=ENUMTYPE(type);break;default:CError_Error(0x2889,(*left)->type,(*left)->flags&QUALS,op,type,(*right)->flags&QUALS);*right=nullnode();}
    if(complex){fn_0055ad80(left,right,*op=='*'||*op=='/');return;}
    if(floating){if((*left)->type==(*right)->type)return;if(RANK((*left)->type)>RANK((*right)->type))*right=fn_0055b2d0(*right,(*left)->type);else *left=fn_0055b2d0(*left,(*right)->type);return;}
    if(RANK((*left)->type)<0x17&&RANK((*right)->type)<0x17){*left=integralpromote(*left);*right=integralpromote(*right);if((*left)->type==(*right)->type)return;
        smaller=right;if(RANK((*left)->type)<RANK((*right)->type)){smaller=left;left=right;}
        if((*left)->type->size==(*smaller)->type->size&&!is_unsigned((*left)->type)&&is_unsigned((*smaller)->type)){
            if((*left)->type==&stsignedlong)common=&stunsignedlong;else{if((*left)->type!=&stsignedlonglong)CError_Internal(filename,1193);common=&stunsignedlonglong;}*left=fn_0055b2d0(*left,common);}
        *smaller=fn_0055b2d0(*smaller,(*left)->type);return;
    }
    if((*left)->type==(*right)->type)return;if(RANK((*left)->type)>RANK((*right)->type))*right=fn_0055b2d0(*right,(*left)->type);else *left=fn_0055b2d0(*left,(*right)->type);
}
void fn_0055ad80(ExprNode **left,ExprNode **right,UInt8 multiply) {
    ExprType *lt,*rt,*type;UInt8 li,ri;
    if((*left)->type==(*right)->type)return;
    if((*left)->type->kind==3){
        fn_005454e0((*left)->type,&lt,&li);
        if((*right)->type->kind==3){fn_005454e0((*right)->type,&rt,&ri);if(RANK(lt)!=RANK(rt)){if(RANK(lt)>RANK(rt)){type=ri?fn_005454c0(lt):fn_005454a0(lt);*right=fn_0055b280(*right,type);}else{type=li?fn_005454c0(rt):fn_005454a0(rt);*left=fn_0055b280(*left,type);}}return;}
        if(!li){if(!multiply){*left=fn_0055b280(*left,fn_005454c0(lt));li=1;}else{*left=fn_0055b280(*left,fn_005454a0(lt));li=0;}}
        if((*right)->type->kind==2){if(RANK(lt)==RANK((*right)->type))return;if(RANK(lt)>RANK((*right)->type))*right=fn_0055b2d0(*right,lt);else{type=li?fn_005454c0((*right)->type):fn_005454a0((*right)->type);*left=fn_0055b280(*left,type);}}
        else *right=fn_0055b2d0(*right,lt);
    }else{
        fn_005454e0((*right)->type,&rt,&ri);
        if(!ri){if(!multiply){*right=fn_0055b280(*right,fn_005454c0(rt));ri=1;}else{*right=fn_0055b280(*right,fn_005454a0(rt));ri=0;}}
        if((*left)->type->kind==2){if(RANK(rt)==RANK((*left)->type))return;if(RANK(rt)<RANK((*left)->type)){type=ri?fn_005454c0((*left)->type):fn_005454a0((*left)->type);*right=fn_0055b280(*right,type);}else *left=fn_0055b2d0(*left,rt);}
        else *left=fn_0055b2d0(*left,rt);
    }
}
#define NODEAT(n,o) (*(ExprNode **)((UInt8 *)(n)+(o)))
void CExpr_IRTreeWalk(ExprStatement *statement,ExprVisitor visit) {
    for(;statement;statement=statement->next){switch(statement->kind){case 1:case 2:case 3:case 0x10:break;
        case 8:if(statement->node)CExpr_ENodeTreeWalk(statement->node,visit);break;
        case 4:case 5:case 6:case 7:case 0xc:case 0xd:case 0xe:case 0xf:CExpr_ENodeTreeWalk(statement->node,visit);break;
        default:CError_Internal(filename,592);}}
}
void CExpr_ENodeTreeWalk(ExprNode *node,ExprVisitor visit) {
    UInt32 *a,*b;
    for(;;){visit(node);switch(node->kind){
        case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 0x32:case 0x33:node=LEFT(node);break;
        case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:case 20:case 21:case 22:case 23:case 24:case 25:case 26:case 27:case 28:case 29:case 30:case 31:case 32:case 33:case 34:case 35:case 36:case 37:case 38:case 39:case 40:case 41:case 42:case 43:case 44:case 45:case 46:case 47:case 48:case 49:case 0x4d:case 0x4e:
            CExpr_ENodeTreeWalk(LEFT(node),visit);node=RIGHT(node);break;
        case 0x34:case 0x35:case 0x36:case 0x37:case 0x3b:case 0x3d:case 0x3e:case 0x40:case 0x41:case 0x44:case 0x50:case 0x51:case 0x52:case 0x53:case 0x57:return;
        case 0x38:case 0x58:CExpr_ENodeTreeWalk(LEFT(node),visit);CExpr_ENodeTreeWalk(RIGHT(node),visit);node=THIRD(node);break;
        case 0x39:case 0x3a:for(a=(UInt32 *)RIGHT(node);a;a=(UInt32 *)a[0])CExpr_ENodeTreeWalk((ExprNode *)a[1],visit);node=LEFT(node);break;
        case 0x3c:case 0x43:case 0x48:case 0x49:CExpr_ENodeTreeWalk(LEFT(node),visit);node=RIGHT(node);break;
        case 0x3f:for(a=(UInt32 *)RIGHT(node);a;a=(UInt32 *)a[0])CExpr_ENodeTreeWalk((ExprNode *)a[2],visit);for(a=(UInt32 *)THIRD(node);a;a=(UInt32 *)a[0])CExpr_ENodeTreeWalk((ExprNode *)a[2],visit);return;
        case 0x42:if(LEFT(node))CExpr_ENodeTreeWalk(LEFT(node),visit);return;
        case 0x4a:if(LEFT(node))CExpr_ENodeTreeWalk(LEFT(node),visit);if(RIGHT(node))CExpr_ENodeTreeWalk(RIGHT(node),visit);if(THIRD(node))CExpr_ENodeTreeWalk(THIRD(node),visit);if(NODEAT(node,28))CExpr_ENodeTreeWalk(NODEAT(node,28),visit);return;
        case 0x4b:node=NODEAT(node,36);if(!node)return;break;
        case 0x4c:switch(*((UInt8 *)node+44)){
            case 0:case 3:case 4:case 5:case 8:case 0x16:case 0x17:case 0x18:case 0x19:case 0x1b:return;
            case 1:if(!*((UInt8 *)node+25))return;node=LEFT(node);break;
            case 2:for(a=(UInt32 *)LEFT(node);a;a=(UInt32 *)a[0])CExpr_ENodeTreeWalk((ExprNode *)a[1],visit);return;
            case 6:case 9:case 10:case 11:case 0x15:case 13:case 0x14:case 0x1a:node=LEFT(node);break;
            case 7:for(a=(UInt32 *)RIGHT(node);a;a=(UInt32 *)a[0])CExpr_ENodeTreeWalk((ExprNode *)a[1],visit);node=LEFT(node);break;
            case 12:if(THIRD(node))CExpr_ENodeTreeWalk(THIRD(node),visit);for(a=(UInt32 *)NODEAT(node,28);a;a=(UInt32 *)a[0])CExpr_ENodeTreeWalk((ExprNode *)a[1],visit);for(a=(UInt32 *)NODEAT(node,32);a;a=(UInt32 *)a[0])CExpr_ENodeTreeWalk((ExprNode *)a[1],visit);return;
            case 14:CExpr_ENodeTreeWalk(LEFT(node),visit);node=RIGHT(node);break;
            case 15:case 16:case 17:case 18:case 19:node=LEFT(node);if(!node)return;break;
            default:CError_Internal(filename,546);return;}break;
        case 0x4f:for(a=(UInt32 *)LEFT(node);a;a=(UInt32 *)a[0]){if(!*((UInt8 *)a+13)){for(b=(UInt32 *)a[1];b;b=(UInt32 *)b[0])CExpr_ENodeTreeWalk((ExprNode *)b[1],visit);}else if(a[1])CExpr_ENodeTreeWalk((ExprNode *)a[1],visit);}return;
        default:CError_Internal(filename,551);return;
    }}
}
ExprNode *fn_0055bf70(ExprNode *node,ExprRewriter rewrite) {
    UInt32 *a,*b;ExprStatement *statement;
    switch(node->kind){
        case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 0x32:case 0x33:LEFT(node)=fn_0055bf70(LEFT(node),rewrite);break;
        case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:case 20:case 21:case 22:case 23:case 24:case 25:case 26:case 27:case 28:case 29:case 30:case 31:case 32:case 33:case 34:case 35:case 36:case 37:case 38:case 39:case 40:case 41:case 42:case 43:case 44:case 45:case 46:case 47:case 48:case 49:case 0x4d:case 0x4e:LEFT(node)=fn_0055bf70(LEFT(node),rewrite);RIGHT(node)=fn_0055bf70(RIGHT(node),rewrite);break;
        case 0x34:case 0x35:case 0x36:case 0x37:case 0x3b:case 0x3d:case 0x3e:case 0x40:case 0x41:case 0x44:case 0x51:case 0x52:case 0x53:case 0x57:break;
        case 0x38:case 0x58:LEFT(node)=fn_0055bf70(LEFT(node),rewrite);RIGHT(node)=fn_0055bf70(RIGHT(node),rewrite);THIRD(node)=fn_0055bf70(THIRD(node),rewrite);break;
        case 0x39:case 0x3a:for(a=(UInt32 *)RIGHT(node);a;a=(UInt32 *)a[0])a[1]=(UInt32)fn_0055bf70((ExprNode *)a[1],rewrite);LEFT(node)=fn_0055bf70(LEFT(node),rewrite);break;
        case 0x3c:case 0x43:case 0x48:case 0x49:LEFT(node)=fn_0055bf70(LEFT(node),rewrite);RIGHT(node)=fn_0055bf70(RIGHT(node),rewrite);break;
        case 0x3f:for(a=(UInt32 *)RIGHT(node);a;a=(UInt32 *)a[0])a[2]=(UInt32)fn_0055bf70((ExprNode *)a[2],rewrite);for(a=(UInt32 *)THIRD(node);a;a=(UInt32 *)a[0])a[2]=(UInt32)fn_0055bf70((ExprNode *)a[2],rewrite);break;
        case 0x42:if(LEFT(node))LEFT(node)=fn_0055bf70(LEFT(node),rewrite);break;
        case 0x4a:if(LEFT(node))LEFT(node)=fn_0055bf70(LEFT(node),rewrite);if(RIGHT(node))RIGHT(node)=fn_0055bf70(RIGHT(node),rewrite);if(THIRD(node))THIRD(node)=fn_0055bf70(THIRD(node),rewrite);if(NODEAT(node,28))NODEAT(node,28)=fn_0055bf70(NODEAT(node,28),rewrite);break;
        case 0x4b:if(NODEAT(node,36))NODEAT(node,36)=fn_0055bf70(NODEAT(node,36),rewrite);break;
        case 0x4c:switch(*((UInt8 *)node+44)){
            case 0:case 3:case 4:case 5:case 8:case 0x16:case 0x17:case 0x18:case 0x19:case 0x1b:break;
            case 1:if(*((UInt8 *)node+25))LEFT(node)=fn_0055bf70(LEFT(node),rewrite);break;
            case 2:for(a=(UInt32 *)LEFT(node);a;a=(UInt32 *)a[0])a[1]=(UInt32)fn_0055bf70((ExprNode *)a[1],rewrite);break;
            case 6:case 9:case 10:case 11:case 0x15:case 13:case 0x14:case 0x1a:LEFT(node)=fn_0055bf70(LEFT(node),rewrite);break;
            case 7:for(a=(UInt32 *)RIGHT(node);a;a=(UInt32 *)a[0])a[1]=(UInt32)fn_0055bf70((ExprNode *)a[1],rewrite);LEFT(node)=fn_0055bf70(LEFT(node),rewrite);break;
            case 12:if(THIRD(node))THIRD(node)=fn_0055bf70(THIRD(node),rewrite);for(a=(UInt32 *)NODEAT(node,28);a;a=(UInt32 *)a[0])a[1]=(UInt32)fn_0055bf70((ExprNode *)a[1],rewrite);for(a=(UInt32 *)NODEAT(node,32);a;a=(UInt32 *)a[0])a[1]=(UInt32)fn_0055bf70((ExprNode *)a[1],rewrite);break;
            case 14:LEFT(node)=fn_0055bf70(LEFT(node),rewrite);RIGHT(node)=fn_0055bf70(RIGHT(node),rewrite);break;
            case 15:case 16:case 17:case 18:case 19:if(LEFT(node))LEFT(node)=fn_0055bf70(LEFT(node),rewrite);break;
            default:CError_Internal(filename,293);}break;
        case 0x4f:for(a=(UInt32 *)LEFT(node);a;a=(UInt32 *)a[0]){if(!*((UInt8 *)a+13)){for(b=(UInt32 *)a[1];b;b=(UInt32 *)b[0])b[1]=(UInt32)fn_0055bf70((ExprNode *)b[1],rewrite);}else if(a[1])a[1]=(UInt32)fn_0055bf70((ExprNode *)a[1],rewrite);}break;
        case 0x50:for(statement=(ExprStatement *)LEFT(node);statement;statement=statement->next){switch(statement->kind){case 1:case 2:case 3:case 0xc:case 0xd:case 0xe:case 0x10:break;case 8:if(statement->node)statement->node=fn_0055bf70(statement->node,rewrite);break;default:CError_Internal(filename,96);case 4:case 5:case 6:case 7:case 0xf:statement->node=fn_0055bf70(statement->node,rewrite);}}break;
        default:CError_Internal(filename,317);
    }
    return rewrite(node);
}
