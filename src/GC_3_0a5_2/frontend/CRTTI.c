/* Native CRTTI.c. Cast/type-info algorithms are related to 1.2.5 CRTTI.c;
 * native packed layouts and split parser/semantic entry ABIs are retained. */
#include "compiler/common.h"
#include <stddef.h>
#include <string.h>
#pragma pack(push,2)
typedef struct RType {UInt8 kind,pad;SInt32 size;} RType;
typedef struct RNode {UInt8 kind,cost;UInt16 pad;RType *type;UInt32 flags,unknown0c;struct RNode *payload;UInt8 unknown14[26];} RNode;
typedef struct RObject {UInt8 kind,access,storage,pad;void *unknown04,*space,*name;RType *type;UInt32 qualifiers;UInt16 sclass,flags;UInt8 unknown1c[68];} RObject;
typedef struct RDecl {RType *type;UInt32 qualifiers;UInt8 unknown08[144];} RDecl;
typedef struct RBase {struct RBase *next;RType *type;SInt32 offset;UInt32 unknown0c;UInt8 access,isVirtual;} RBase;
typedef struct RChild {struct RChild *next;RType *type;SInt32 offset;} RChild;
typedef struct RPath {struct RPath *next;RType *type;RChild *children;SInt32 offset;SInt16 count;UInt8 isPrivate,isAmbiguous;} RPath;
typedef struct RReference {struct RReference *next;RObject *object;SInt32 offset,zero;} RReference;
typedef struct RPointerCopy {UInt8 bytes[14];} RPointerCopy;
typedef struct RMemberCopy {UInt8 bytes[18];} RMemberCopy;
#pragma pack(pop)
typedef char RNodeSize[(sizeof(RNode)==46)?1:-1];
typedef char RObjectSize[(sizeof(RObject)==96)?1:-1];
typedef char RDeclSize[(sizeof(RDecl)==152)?1:-1];
typedef char RBaseSize[(sizeof(RBase)==18)?1:-1];
typedef char RPathSize[(sizeof(RPath)==20)?1:-1];
typedef char RReferenceSize[(sizeof(RReference)==16)?1:-1];
#define RP(p,o) (*(void **)((UInt8 *)(p)+(o)))
#define RU(p,o) (*(UInt32 *)((UInt8 *)(p)+(o)))
#define RB(p,o) (*((UInt8 *)(p)+(o)))
#define RQ 0x1f200003UL
static char filename[]="CRTTI.c",std_name[]="std",type_info_name[]="type_info";
extern SInt16 fn_00717466;
extern UInt8 fn_0070f1ee,fn_0070f1af,fn_0070f1a8,fn_0070f1b4,fn_0070f1b5;
extern void *fn_007101c4,*fn_00711bb8,*fn_00715c58;
extern RType fn_00699c1c,fn_00699c24,fn_00699c44,fn_00699c54,fn_00699c64;
extern void *CompilerTools_AllocatePool(UInt32),*GetHashNameNode(const char *),*CScope_FindName(void *,void *),*CScope_GetTagType(void *,void *);
extern void memclrw(void *,UInt32),CError_Internal(const char *,SInt32),CError_ReportError(SInt32,...),CError_Warning(SInt32,...),CError_ReportErrorAndUpdateToken(SInt32);
extern UInt8 CTemplateTools_IsDependentType(RType *),fn_0053d470(RNode *),fn_00559680(RNode *),iscpp_typeequal(RType *,RType *),fn_00541b10(RType *,RType *,void *,void *,UInt8),fn_005e3c30(RNode *,RType *,UInt32),fn_00542810(RType *),fn_00452f10(RObject *);
extern SInt16 fn_00454a80(RType *,RType *),fn_00447b70(void);
extern UInt32 fn_004533b0(RType *,UInt32);
extern RNode *nullnode(void),*fn_00524320(UInt8),*fn_0055aa00(RNode *,RType *,UInt32),*fn_0055b7f0(RNode *),*fn_00543680(RNode *,RType *,UInt32,UInt8,UInt8),*fn_00559240(RNode *,UInt8,UInt8),*fn_005432e0(RNode *,RType *,UInt8,UInt8),*fn_005e1e00(RNode *,RType *,UInt32,UInt8),*fn_005e1f10(RNode *,RType *,UInt32,UInt8,UInt8),*fn_00559da0(RNode *,UInt8),*makemonadicnode(RNode *,UInt8),*fn_005150d0(void),*fn_00521c20(RObject *,UInt8),*intconstnode(RType *,SInt32);
extern RNode *fn_005a88b0(void *,RNode *,RNode *,RNode *,RNode *,RNode *,RNode *),*fn_005a89a0(void *,RNode *,RNode *,RNode *,RNode *);
extern RType *CDecl_NewPointerType(RType *),*fn_004538b0(UInt32 *,UInt8),*fn_005445b0(SInt32,SInt32);
extern void CDecl_CompleteType(RType *),CParser_GetDeclSpecs(RDecl *,UInt8),CDecl_ParseDeclarator(RDecl *),fn_0045c440(SInt32,UInt8),CScope_AddGlobalObject(RObject *),fn_0052f040(RObject *,void *,RReference *,SInt32),CMach_InitIntMem(RType *,UInt32,UInt32,void *);
extern RObject *fn_00455570(void),*fn_0052f930(char *,SInt32,UInt8,UInt8);
extern void *CParser_GetUniqueName(void),*CClass_FindVBaseOffset(RType *,RType *);
extern void *fn_00558210(RType *,UInt32);
extern char *fn_0045ede0(RType *,UInt32,UInt8);
RNode *fn_005e8490(void),*fn_005e84d0(RNode *,RType *,UInt32),*fn_005e8620(void),*fn_005e8660(RNode *,RType *,UInt32),*fn_005e8910(void),*fn_005e8950(RNode *,RType *,UInt32),*fn_005e8c30(RNode *,RType *,UInt32),*fn_005e8f30(void),*fn_005e8f80(RNode *,RType *,UInt32),*fn_005e92b0(RDecl *),*CRTTI_ParseTypeid(void),*fn_005e95a0(RNode *,RType *,UInt32);
void fn_005e93c0(RType *,UInt32,RType *,UInt32),fn_005e9940(RObject *,RType *,UInt32),fn_005e9db0(RType *,RPath *,RType *,SInt32,UInt8);
RObject *CRTTI_GetTypeInfoObject(RType *,UInt32),*fn_005e9a10(RType *);
RPath *fn_005e9e60(RType *,RType *,RPath *,SInt32,UInt8);
static inline void rtti_set_type(RNode *node,RType *type,UInt32 qual) {node->type=type;node->flags=(node->flags&~RQ)|(qual&RQ);}
static inline RNode *rtti_dependent(UInt8 kind,RNode *node,RType *type,UInt32 qual) {RNode *result=fn_00524320(kind);result->payload=node;RP(result,20)=type;RU(result,24)=qual;return result;}
static inline UInt8 rtti_same_type(RType *a,RType *b) {
    while(a->kind==b->kind){switch(a->kind){case 0:return 1;case 1:case 2:case 3:case 4:case 5:return a==b;case 12:a=RP(a,6);b=RP(b,6);break;default:return iscpp_typeequal(a,b);}}return 0;
}
static inline void rtti_reference_flag(RNode *node,RType *type) {if(fn_0070f1ee&&type->kind==12&&(RU(type,10)&0xa0)==0xa0&&fn_00559680(node))node->flags|=0x1000;}
RNode *fn_005e8490(void) {RDecl decl;RNode *node=fn_005e92b0(&decl);if(node)return fn_005e84d0(node,decl.type,decl.qualifiers);return nullnode();}
RNode *fn_005e8620(void) {RDecl decl;RNode *node=fn_005e92b0(&decl);if(node)return fn_005e8660(node,decl.type,decl.qualifiers);return nullnode();}
RNode *fn_005e8910(void) {RDecl decl;RNode *node=fn_005e92b0(&decl);if(node)return fn_005e8950(node,decl.type,decl.qualifiers);return nullnode();}
RNode *fn_005e8f30(void) {RDecl decl;RNode *node=fn_005e92b0(&decl);if(node){if(!fn_0070f1b5)CError_Warning(0x2811);return fn_005e8f80(node,decl.type,decl.qualifiers);}return nullnode();}
RNode *fn_005e84d0(RNode *node,RType *type,UInt32 qual) {
    if(CTemplateTools_IsDependentType(type)||fn_0053d470(node))return rtti_dependent(0x12,node,type,qual);
    if(type->kind==12){if(RU(type,10)&0x20){if(!fn_00454a80(RP(type,6),node->type))CError_ReportError(0x27b4);if(node->kind==4){rtti_set_type(node,RP(type,6),qual);rtti_reference_flag(node,type);}else CError_ReportError(0x279e);}
        else{if(!fn_00454a80(type,node->type))CError_ReportError(0x27b4);node=fn_0055aa00(node,type,qual);}}
    else if(type->kind==11){if(!fn_00454a80(type,node->type))CError_ReportError(0x27b4);node=fn_0055aa00(node,type,qual);}else CError_ReportError(0x27b4);return node;
}
RNode *fn_005e8660(RNode *node,RType *type,UInt32 qual) {
    RType *reference,*source;
    if(CTemplateTools_IsDependentType(type)||fn_0053d470(node))return rtti_dependent(0x11,node,type,qual);
    if(type->kind!=12||!(RU(type,10)&0x20))node=fn_0055b7f0(node);
    fn_005e93c0(node->type,node->flags&RQ,type,qual);if(node->kind==0x4b&&RB(node,41))node=fn_00543680(node,NULL,0,1,1);
    if(type->kind==12&&(RU(type,10)&0x20)){node=fn_00559240(node,0,1);if(node->kind!=4)return node;node->payload->type=CDecl_NewPointerType(node->type);node=node->payload;reference=type;type=CDecl_NewPointerType(RP(type,6));}else reference=NULL;
    switch(type->kind){case 1:if(node->type->kind==11||node->type->kind==12){node=fn_0055aa00(node,type,qual);goto done;}break;
        case 11:source=node->type;if(source->kind==11&&((*(RType **) ((UInt8 *)type+6))->kind==7)==((*(RType **)((UInt8 *)source+6))->kind==7)){rtti_set_type(node,type,qual);goto done;}node=fn_0055aa00(node,type,qual);goto done;
        case 12:switch(node->type->kind){case 1:case 4:if(reference)type=reference;node=fn_0055aa00(node,type,qual);goto done;
            case 12:source=node->type;if(fn_0070f1af&&fn_0070f1a8&&((*(RType **)((UInt8 *)source+6))->kind==7||(*(RType **)((UInt8 *)type+6))->kind==7)&&(*(RType **)((UInt8 *)source+6))->kind!=(*(RType **)((UInt8 *)type+6))->kind)CError_Warning(0x2807,source,node->flags&RQ,type,qual);node=makemonadicnode(node,0x32);rtti_set_type(node,type,qual);goto done;}break;}
    CError_ReportError(0x27b4);
done:if(reference){if(node->type->kind==12){node=makemonadicnode(node,4);node->type=RP(type,6);}rtti_reference_flag(node,reference);}return node;
}
RNode *fn_005e8950(RNode *node,RType *type,UInt32 qual) {
    RNode *result;RType *source,*target;
    if(CTemplateTools_IsDependentType(type)||fn_0053d470(node))return rtti_dependent(0x10,node,type,qual);
    if(type->kind==12&&(RU(type,10)&0x20)){
        target=RP(type,6);source=node->type;
        if(rtti_same_type(target,source)||(target->kind==6&&source->kind==6&&(fn_00541b10(target,source,NULL,NULL,1)||fn_00541b10(source,target,NULL,NULL,1))))result=fn_005e1f10(node,type,qual,1,1);else result=NULL;
        if(result){rtti_reference_flag(result,type);return result;}
        if(node->type->kind==6&&fn_005e3c30(node,type,qual)){result=fn_005e1f10(node,type,qual,0,1);if(result->type->kind!=12)CError_Internal(filename,0x752);result=makemonadicnode(result,4);rtti_set_type(result,RP(type,6),qual);rtti_reference_flag(result,type);return result;}
    }else if(fn_005e3c30(node,type,qual))return fn_005e1f10(node,type,qual,1,1);
    fn_005e93c0(node->type,node->flags&RQ,type,qual);
    if(type->kind!=0&&(node->type->kind!=12||(*(RType **)((UInt8 *)node->type+6))->kind!=0)){
        target=type;if(target->kind==12)target=RP(target,6);if(target->kind==6&&!target->size){CDecl_CompleteType(target);if(!(RU(target,34)&2))CError_ReportError(0x2798,target,0);}
        source=node->type;if(source->kind==12)source=RP(source,6);if(source->kind==6&&!source->size){CDecl_CompleteType(source);if(!(RU(source,34)&2))CError_ReportError(0x2798,source,0);}}
    return fn_005e8c30(node,type,qual);
}
RNode *fn_005e8c30(RNode *node,RType *type,UInt32 qual) {
    UInt8 invalid=0,pointerCast=0,direct=0;RType *source,*a,*b;
    if(node->kind==0x4b){if(type->kind!=11)return fn_005e1e00(node,type,qual,1);node=fn_005432e0(node,type,1,1);}
    switch(type->kind){case 1:case 4:if(node->type->kind==12&&type!=&fn_00699c1c)invalid=1;break;
        case 11:source=node->type;if(source->kind==11){a=RP(type,10);b=RP(source,10);if(a->kind==6&&b->kind==6&&!fn_00541b10(a,b,NULL,NULL,1)&&!fn_00541b10(b,a,NULL,NULL,1))invalid=1;else if(!rtti_same_type(RP(type,6),RP(source,6)))invalid=1;}break;
        case 12:if(RU(type,10)&0x20)invalid=1;else{source=node->type;if(source->kind==12){a=RP(type,6);b=RP(source,6);if(!rtti_same_type(type,source)&&a->kind!=0&&b->kind!=0){if(a->kind!=6||b->kind!=6||(!fn_00541b10(a,b,NULL,NULL,1)&&!fn_00541b10(b,a,NULL,NULL,1)))invalid=1;}else pointerCast=direct=1;}
            else{if(source->kind==4)node->type=RP(source,14);if(node->type->kind==1&&node->kind==0x34&&!RU(node,16)&&!RU(node,20))direct=1;else if(node->type->kind!=6)invalid=1;}}break;}
    if(invalid){CError_ReportError(0x2807,node->type,node->flags&RQ,type,qual);return node;}if(!direct)return fn_005e1f10(node,type,qual,1,1);
    if(pointerCast&&node->kind==4&&(fn_0070f1b4||!fn_0070f1af))node=makemonadicnode(node,0x32);rtti_set_type(node,type,qual);return node;
}
void fn_005e93c0(RType *source,UInt32 sourceQual,RType *target,UInt32 targetQual) {
    UInt8 outer=1;UInt32 a,b;
    if(target->kind==12&&(RU(target,10)&0x20)){target=RP(target,6);outer=0;}
    while(source->kind==target->kind){switch(source->kind){case 11:if(!outer&&((RU(source,14)&1)&&!(RU(target,14)&1)||(RU(source,14)&2)&&!(RU(target,14)&2)))CError_ReportError(0x2812);break;
        case 12:if(!outer&&((RU(source,10)&1)&&!(RU(target,10)&1)||(RU(source,10)&2)&&!(RU(target,10)&2)))CError_ReportError(0x2812);break;default:goto done;}outer=0;source=RP(source,6);target=RP(target,6);}
done:if(!outer&&source->kind!=7&&target->kind!=7){b=fn_004533b0(target,targetQual);a=fn_004533b0(source,sourceQual);if((a&1)&&!(b&1)||(a&2)&&!(b&2))CError_ReportError(0x2812);}
}
RNode *fn_005e92b0(RDecl *decl) {
    RNode *node;fn_00717466=fn_00447b70();if(fn_00717466!=0x3c){fn_0045c440(fn_00717466,0);return NULL;}
    fn_00717466=fn_00447b70();memclrw(decl,152);CParser_GetDeclSpecs(decl,0);CDecl_ParseDeclarator(decl);if(RU(decl,24))CError_ReportError(0x27b4);
    if(fn_00717466!=0x3e){CError_ReportError(0x27f7);return NULL;}if(fn_00447b70()!=0x28){CError_ReportError(0x2782);return NULL;}
    fn_00717466=fn_00447b70();node=fn_005150d0();if(decl->type->kind!=12||!(RU(decl->type,10)&0x20))node=fn_0055b7f0(node);
    if(fn_00717466!=0x29){CError_ReportError(0x2783);return NULL;}fn_00717466=fn_00447b70();return node;
}
RNode *fn_005e8f80(RNode *node,RType *type,UInt32 qual) {
    RType *target,*source;UInt8 reference;RNode *destinationInfo,*sourceInfo,*flag,*offset,*result;
    if(CTemplateTools_IsDependentType(type)||fn_0053d470(node))return rtti_dependent(0xf,node,type,qual);
    fn_005e93c0(node->type,node->flags&RQ,type,qual);if(type->kind!=12){CError_ReportError(0x27b4);return node;}
    reference=(RU(type,10)&0x20)!=0;target=RP(type,6);if(target->kind==6){CDecl_CompleteType(target);if(!(RU(target,34)&2)){CError_ReportError(0x2798,target,0);return node;}}
    else{if(reference||target->kind!=0){CError_ReportError(0x27b4);return node;}target=NULL;}
    if(reference){source=node->type;if(source->kind!=6){CError_ReportError(0x27b4);return node;}if(target&&(source==target||fn_00541b10(source,target,NULL,NULL,1)))return fn_0055aa00(node,type,qual);node=fn_00559da0(node,1);}
    else{if(node->type->kind!=12||(source=RP(node->type,6))->kind!=6){CError_ReportError(0x27b4);return node;}if(target&&(source==target||fn_00541b10(source,target,NULL,NULL,1)))return fn_0055aa00(node,type,qual);}
    if(!(RU(source,34)&2)){CError_ReportError(0x2798,source,0);return node;}if(!fn_00542810(source)){CError_ReportError(0x27b4);return node;}
    destinationInfo=target?fn_00521c20(CRTTI_GetTypeInfoObject(target,0),1):nullnode();sourceInfo=fn_00521c20(CRTTI_GetTypeInfoObject(source,0),1);flag=intconstnode(&fn_00699c44,reference);offset=intconstnode(&fn_00699c64,RU(RP(source,26),12));
    result=fn_005a88b0(fn_00715c58,node,offset,destinationInfo,sourceInfo,flag,NULL);if(reference){if(!target)CError_Internal(filename,0x671);result->type=CDecl_NewPointerType(target);result=makemonadicnode(result,4);result->type=target;}else result->type=type;rtti_set_type(result,result->type,qual);return result;
}
RNode *CRTTI_ParseTypeid(void) {
    RNode *node;RType *type;UInt32 qual;if(!fn_0070f1b5)CError_Warning(0x2811);if(fn_00447b70()!=0x28){CError_ReportError(0x2782);return nullnode();}
    fn_00717466=fn_00447b70();qual=0;node=NULL;type=fn_004538b0(&qual,0);if(!type)node=fn_005150d0();if(fn_00717466==0x29)fn_00717466=fn_00447b70();else CError_ReportErrorAndUpdateToken(0x2783);return fn_005e95a0(node,type,qual);
}
RNode *fn_005e95a0(RNode *node,RType *type,UInt32 qual) {
    void *space,*found,*name;RType *typeInfo,*pointer;RNode *result,*offset;
    name=GetHashNameNode(std_name);found=CScope_FindName(fn_007101c4,name);space=fn_007101c4;if(found&&RB(RP(found,4),0)==3)space=RP(RP(found,4),2);
    typeInfo=CScope_GetTagType(space,GetHashNameNode(type_info_name));if(!typeInfo||typeInfo->kind!=6||!typeInfo->size){CError_ReportError(0x293b);typeInfo=&fn_00699c24;}
    pointer=CDecl_NewPointerType(typeInfo);CDecl_NewPointerType(pointer);
    if(!type){if(fn_0053d470(node))return rtti_dependent(0x13,node,NULL,qual);if(node->kind==0x4b)node=fn_00543680(node,NULL,0,1,0);type=node->type;qual=node->flags&RQ;if(type->kind==12&&(RU(type,10)&0x20))type=RP(type,6);
        if(type->kind==6&&fn_00542810(type)){offset=intconstnode(&fn_00699c64,RU(RP(type,26),12));node=fn_00559da0(node,0);result=fn_005a89a0(fn_00711bb8,node,offset,NULL,NULL);result->type=pointer;result=makemonadicnode(result,4);result->type=typeInfo;result->flags|=0x8001;return result;}}
    else{if(CTemplateTools_IsDependentType(type))return rtti_dependent(0x13,node,type,qual);if(type->kind==12&&(RU(type,10)&0x20))type=RP(type,6);}
    result=makemonadicnode(fn_00521c20(CRTTI_GetTypeInfoObject(type,qual),1),4);result->type=typeInfo;result->flags=0x8001;return result;
}
RObject *CRTTI_GetTypeInfoObject(RType *type,UInt32 qual) {
    RMemberCopy member;RPointerCopy pointer;void *name,*found;RObject *object;
    switch(type->kind){case 11:if(RU(type,14)&3){member=*(RMemberCopy *)type;RU(&member,14)&=~3UL;type=(RType *)&member;}break;
        case 12:if(RU(type,10)&3){pointer=*(RPointerCopy *)type;RU(&pointer,10)&=~3UL;type=(RType *)&pointer;}break;default:qual=0;}
    if(type->kind==6){if(!type->size){CDecl_CompleteType(type);if(!(RU(type,34)&2))CError_ReportError(0x2798,type,0);}if(!RP(type,30)){name=fn_00558210(type,qual);object=fn_00455570();object->name=name;object->type=fn_005445b0(8,4);object->qualifiers=0x20000;object->qualifiers|=1;CScope_AddGlobalObject(object);RP(type,30)=object;}return RP(type,30);}
    name=fn_00558210(type,qual);found=CScope_FindName(fn_007101c4,name);object=found?RP(found,4):NULL;if(object&&object->kind!=5)object=NULL;if(object&&!fn_00452f10(object))CError_Internal(filename,0x3eb);
    if(!object){object=fn_00455570();object->name=name;object->type=fn_005445b0(8,4);object->qualifiers=0x20000;object->qualifiers|=1;CScope_AddGlobalObject(object);object->sclass=0x102;object->qualifiers|=0x20000;fn_005e9940(object,type,qual);}return object;
}
void fn_005e9940(RObject *object,RType *type,UInt32 qual) {
    char *text=fn_0045ede0(type,qual,0);RObject *stringObject=fn_0052f930(text,strlen(text)+1,0,0),*bases=NULL;void *data;RReference *refs,*copy;
    if(type->kind==6)bases=fn_005e9a10(type);data=CompilerTools_AllocatePool(8);memclrw(data,8);refs=CompilerTools_AllocatePool(16);refs->next=NULL;refs->object=stringObject;refs->offset=0;refs->zero=0;
    if(bases){copy=CompilerTools_AllocatePool(16);refs->next=copy;copy->next=NULL;copy->object=bases;copy->offset=4;copy->zero=0;}fn_0052f040(object,data,refs,object->type->size);
}
void fn_005e9db0(RType *root,RPath *path,RType *type,SInt32 offset,UInt8 recurse) {
    RChild *child;RBase *base;SInt32 nextOffset;
    if(path->type!=type){for(child=path->children;child;child=child->next)if(child->type==type&&child->offset==offset)break;if(!child){child=CompilerTools_AllocatePool(12);child->next=path->children;path->children=child;child->type=type;child->offset=offset;++path->count;}}
    for(base=RP(type,14);base;base=base->next)if(!base->access){if(!base->isVirtual)nextOffset=offset+base->offset;else{if(!recurse)continue;nextOffset=RU(CClass_FindVBaseOffset(root,base->type),8);}fn_005e9db0(root,path,base->type,nextOffset,recurse);}
}
RPath *fn_005e9e60(RType *root,RType *type,RPath *list,SInt32 offset,UInt8 privatePath) {
    RPath *path,*result=list;RBase *base;UInt8 ambiguous;SInt32 nextOffset;
    if(root!=type){ambiguous=0;for(path=list;path;path=path->next)if(path->type==type){if(path->offset==offset){if(!privatePath)path->isPrivate=0;ambiguous=0;}else{path->isAmbiguous=1;ambiguous=1;}break;}
        if(!path||ambiguous){result=CompilerTools_AllocatePool(20);memclrw(result,20);result->next=list;result->type=type;result->offset=offset;result->isPrivate=privatePath;result->isAmbiguous=ambiguous;}}
    for(base=RP(type,14);base;base=base->next){nextOffset=base->isVirtual?RU(CClass_FindVBaseOffset(root,base->type),8):offset+base->offset;result=fn_005e9e60(root,base->type,result,nextOffset,privatePath||base->access==1);}return result;
}
RObject *fn_005e9a10(RType *type) {
    RType *wordType;RPath *paths,*path;RChild *child;SInt16 singles=0,groups=0,children=0;SInt32 entrySize,groupSize,size;UInt8 *data,*cursor;RObject *object;RReference *refs=NULL,*copy;
    if(fn_00699c54.size==4)wordType=&fn_00699c54;else if(fn_00699c64.size==4)wordType=&fn_00699c64;else if(fn_00699c44.size==4)wordType=&fn_00699c44;else CError_Internal(filename,0x303);
    entrySize=wordType->size+4;groupSize=wordType->size*2+4;paths=fn_005e9e60(type,type,NULL,0,0);if(!paths)return NULL;
    for(path=paths;path;path=path->next)if(!path->isAmbiguous&&!path->isPrivate)++singles;else{fn_005e9db0(type,path,path->type,path->offset,!path->isAmbiguous);if(path->count){++groups;children+=path->count;}}
    if(!singles&&!groups)return NULL;size=groups*groupSize+(children+singles)*entrySize+4;data=CompilerTools_AllocatePool(size);memclrw(data,size);object=fn_00455570();object->name=CParser_GetUniqueName();object->type=fn_005445b0(size,4);object->qualifiers=1;object->sclass=0x102;cursor=data;
    if(singles)for(path=paths;path;path=path->next)if(!path->isPrivate&&!path->isAmbiguous){copy=CompilerTools_AllocatePool(16);copy->next=refs;copy->object=CRTTI_GetTypeInfoObject(path->type,0);copy->offset=cursor-data;copy->zero=0;refs=copy;CMach_InitIntMem(wordType,(UInt32)path->offset>>31?0xffffffff:0,path->offset,cursor+4);cursor+=entrySize;}
    if(groups)for(path=paths;path;path=path->next)if(path->count){copy=CompilerTools_AllocatePool(16);copy->next=refs;copy->object=CRTTI_GetTypeInfoObject(path->type,0);copy->offset=cursor-data;copy->zero=0;refs=copy;CMach_InitIntMem(wordType,0xffffffff,(UInt32)path->offset|0x80000000UL,cursor+4);CMach_InitIntMem(wordType,path->count<0?0xffffffff:0,path->count,cursor+4+wordType->size);cursor+=groupSize;
        for(child=path->children;child;child=child->next){copy=CompilerTools_AllocatePool(16);copy->next=refs;copy->object=CRTTI_GetTypeInfoObject(child->type,0);copy->offset=cursor-data;copy->zero=0;refs=copy;CMach_InitIntMem(wordType,child->offset<0?0xffffffff:0,child->offset,cursor+4);cursor+=entrySize;}}
    fn_0052f040(object,data,refs,object->type->size);return object;
}
