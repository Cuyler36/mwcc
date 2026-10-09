/* Native CTemplateFuncInst.c; related template replay algorithms are in 1.2.5 CTemplateNew.c. */
#include "compiler/common.h"
#include <stddef.h>
#pragma pack(push,2)
typedef struct InstType {UInt8 kind,pad;SInt32 size;} InstType;
typedef struct InstObject InstObject;
typedef struct InstNode InstNode;
typedef struct InstStatement InstStatement;
typedef struct InstAction InstAction;
typedef struct InstPair {struct InstPair *next;void *value;} InstPair;
typedef struct InstMap {struct InstMap *next;InstObject *oldObject,*newObject;SInt32 key;} InstMap;
typedef struct InstContext {void *instance;UInt8 unknown04[16];InstMap *map;void *pending;UInt8 unknown1c[7],resolving,unknown24[2];} InstContext;
typedef struct InstFunction {InstType base;void *args,*exspec;InstType *result;UInt32 qualifiers,flags;UInt8 unknown1a[4];void *context;UInt8 unknown22[8],mode,pad;} InstFunction;
struct InstObject {UInt8 kind,access,storage,pad;void *unknown04,*space,*name;InstType *type;UInt32 qualifiers;UInt16 sclass,flags;UInt8 unknown1c[40];SInt32 key;UInt8 unknown48[8];InstObject *alternate;UInt8 unknown54[12];void *source,*specialization;UInt8 suppress,pad69;};
struct InstNode {UInt8 kind,cost;UInt16 pad;InstType *type;UInt32 flags,unknown0c;void *payload;UInt8 unknown14[24],operation,pad2d;};
struct InstStatement {struct InstStatement *next;UInt8 kind,pad;UInt32 unknown06;InstNode *expression;void *aux;InstAction *actions;};
struct InstAction {struct InstAction *next;InstObject *object;void *function;SInt32 offset,size;InstType *type;UInt32 qualifiers;UInt8 kind,pad;};
typedef struct InstInitializer {struct InstInitializer *next;void *target,*value;UInt8 dependentType,dependentTarget;} InstInitializer;
typedef struct InstInitValue {void *value;UInt8 kind,pad;} InstInitValue;
typedef struct InstInitTree {struct InstInitTree *next,*child;InstNode *expression;} InstInitTree;
typedef struct InstObjectCopy {UInt32 words[24];} InstObjectCopy;
typedef struct InstWorkspace {UInt8 unknown00[132];void *browseFile;UInt32 sourceStart,sourceEnd;UInt8 unknown90[8];} InstWorkspace;
#pragma pack(pop)
typedef char InstContextSize[(sizeof(InstContext)==38)?1:-1];
typedef char InstContextResolving[(offsetof(InstContext,resolving)==35)?1:-1];
typedef char InstFunctionSize[(sizeof(InstFunction)==44)?1:-1];
typedef char InstFunctionContext[(offsetof(InstFunction,context)==30)?1:-1];
typedef char InstObjectCopySize[(sizeof(InstObjectCopy)==96)?1:-1];
typedef char InstObjectSource[(offsetof(InstObject,source)==96)?1:-1];
typedef char InstObjectSuppress[(offsetof(InstObject,suppress)==104)?1:-1];
typedef char InstNodeSize[(sizeof(InstNode)==46)?1:-1];
typedef char InstStatementSize[(sizeof(InstStatement)==22)?1:-1];
typedef char InstActionSize[(sizeof(InstAction)==30)?1:-1];
typedef char InstInitializerSize[(sizeof(InstInitializer)==14)?1:-1];
typedef char InstWorkspaceSize[(sizeof(InstWorkspace)==152)?1:-1];
typedef char InstWorkspaceBrowse[(offsetof(InstWorkspace,browseFile)==132)?1:-1];
#define IP(p,o) (*(void **)((UInt8 *)(p)+(o)))
#define IU(p,o) (*(UInt32 *)((UInt8 *)(p)+(o)))
#define IS(p,o) (*(SInt32 *)((UInt8 *)(p)+(o)))
#define IW(p,o) (*(UInt16 *)((UInt8 *)(p)+(o)))
#define IB(p,o) (*((UInt8 *)(p)+(o)))
static char filename[]="CTemplateFuncInst.c";
static InstPair *pending_arrays;
extern void *fn_00710b38,*fn_00711af8,*fn_007101c4,*fn_00716d50,*fn_007109c4;
extern void *fn_00716cf8,*fn_00711be0,*fn_00716c9c,*fn_00710108,*fn_00710348,*fn_00716cb8;
extern InstPair *fn_00710924;
extern UInt32 fn_00710b30,fn_00711b70,fn_00711b74,fn_00711b78,fn_00715c48,fn_00715c4c,fn_00715c50,fn_00716ca0,fn_00716ca4,fn_00716ca8;
extern UInt8 fn_00725e5d,fn_0070f20b,fn_00725ecf,fn_00725dfa,fn_00725d9e,fn_0070f287,fn_0070f229;
extern SInt16 fn_00717466;
extern InstType fn_00699c44;
extern void *CompilerTools_AllocatePool(UInt32),*galloc(UInt32);
extern void memclrw(void *,UInt32),CError_Internal(const char *,SInt32),CError_Warning(SInt32,...),CError_Error(SInt32,...);
extern void fn_00479c20(void),fn_00462de0(void *,void *),CError_SetWrittenEntry(void *),fn_00462e40(void *);
extern UInt8 fn_00452f10(InstObject *),fn_00456950(InstObject *),CTemplateTools_IsDependentType(InstType *),CTemplTool_IsTypeDepExpr(InstNode *);
extern void CScope_InitScopeSearch(void *,void *);
extern InstObject *CScope_NextObject(void *),*CParser_NewObject(void *),*CParser_NewLocalDataObject(void *,UInt32);
extern void *fn_0053ebf0(void *),*fn_0053ee10(void *),*fn_0053ea50(void *,InstObject *),*fn_0053d900(void *,void *,void *),*fn_0053ee70(void *),*fn_005dc000(void *),*fn_0053da70(void *,void *,UInt8),*CPrep_GetPFile(void);
extern void fn_0053ea20(void *),fn_0053d880(void *,void *,void *),fn_0053dd60(InstType *,InstType *),fn_0053d9d0(void *),fn_0053d8c0(void *),fn_00448340(void *,void *),fn_00448100(void *,void *),fn_0044e900(void *),fn_004eb440(void *,void *),CScope_RestoreScope(void *);
extern SInt16 fn_00447b70(void);
extern void fn_004556f0(InstObject *,void *),CDecl_CompleteType(InstType *),fn_0052fbd0(InstObject *),fn_0052fd20(InstObject *,void *,InstStatement *,UInt8),CFunc_ParseFuncDef(InstObject *,InstWorkspace *,void *,UInt8,UInt8,void *),CBrowse_ForwardObjectFileRange(InstObject *,void *,UInt32,UInt32,UInt32);
extern InstInitValue *fn_00549a00(void *,UInt8);
extern void *fn_0053ecc0(void *);
extern InstNode *fn_0053a470(InstContext *,InstNode *),*fn_0055a940(InstNode *),*fn_00529bf0(InstNode *),*fn_005a8340(InstNode *);
extern InstType *CTemplateTools_ResolveType(InstContext *,InstType *,UInt32 *);
extern void *fn_0053c140(InstContext *,void *),*fn_0053bf70(InstContext *,void *),*fn_00514dc0(InstType *);
extern void fn_00526030(InstInitializer *),fn_0052c820(InstObject *),fn_00544c00(InstType *),fn_00530a70(InstObject *,InstInitValue *,InstStatement *,UInt8),fn_0052cbb0(void *,void *,void *,void *),fn_00526350(void *,InstInitializer *),fn_00515180(InstNode *);
extern InstStatement *fn_0052c580(void *,InstStatement *),*fn_0052c0f0(InstObject *,InstStatement *),*CFunc_InsertAfterStatement(UInt8,InstStatement *);
extern void *CClass_Destructor(InstType *);
extern void CFunc_FuncGenSetup(void *,void *,InstObject *,UInt8),fn_00547ed0(InstObject *,void *,void *,UInt8),fn_0052ec00(InstObject *),fn_00526d20(InstObject *,void *),fn_005268d0(InstObject *),fn_00526410(InstObject *,void *,void *,UInt8,UInt8);
extern UInt8 CMachine_FunctionRequiresMemoryReturn(InstType *);
UInt8 fn_005a19a0(void *,UInt8),fn_005a1b30(void *,InstObject *,UInt8),fn_005a1f80(void *,void *,UInt8),fn_005a2250(InstContext *,InstObject *,void *,void *,UInt8),fn_005a3290(InstAction *,InstAction **);
void fn_005a1b90(void *,void *,InstObject *,void *,InstObject *,UInt8),fn_005a25d0(InstContext *,InstStatement *),fn_005a2b10(InstContext *,InstStatement *,void *,UInt8 *),fn_005a2c50(InstContext *,InstStatement *,void *,UInt8 *),fn_005a2ec0(InstStatement *,InstObject *),fn_005a2fe0(InstContext *,InstInitValue *),fn_005a3050(InstContext *,InstInitTree *),fn_005a31f0(InstContext *,InstAction **);
InstInitializer *fn_005a2a60(InstContext *context,InstInitializer *value) {
    InstInitializer *copy;UInt32 qualifiers;
    if(value){copy=CompilerTools_AllocatePool(14);*copy=*value;copy->next=fn_005a2a60(context,copy->next);
        if(copy->dependentTarget)copy->target=fn_0053a470(context,copy->target);else copy->target=fn_0053c140(context,copy->target);
        if(copy->dependentType)copy->value=fn_0053bf70(context,copy->value);else{qualifiers=0;copy->value=CTemplateTools_ResolveType(context,copy->value,&qualifiers);}
        fn_00526030(copy);return copy;
    }return NULL;
}
void fn_005a3050(InstContext *context,InstInitTree *tree) {
    for(;tree;tree=tree->next){if(tree->expression)tree->expression=fn_0053a470(context,tree->expression);if(tree->child)fn_005a3050(context,tree->child);}
}
void fn_005a2fe0(InstContext *context,InstInitValue *initializer) {
    InstPair *item;
    if(initializer){switch(initializer->kind){case 0:initializer->value=fn_0053a470(context,initializer->value);break;
        case 1:for(item=initializer->value;item;item=item->next)item->value=fn_0053a470(context,item->value);break;
        case 2:fn_005a3050(context,initializer->value);break;default:CError_Internal(filename,293);}}
}
UInt8 fn_005a3290(InstAction *action,InstAction **link) {
    InstObject *object;InstType *type,*element;void *destructor;SInt32 total,size,index,count;InstPair *item;InstAction *copy;
    if(!IB(action,8))return 0;
    object=action->object;type=object->type;
    if(type->kind==6){destructor=CClass_Destructor(type);if(destructor){action->kind=1;action->object=object;action->function=destructor;fn_00725e5d=1;return 1;}return 0;}
    if(type->kind!=13)return 0;
    element=IP(type,6);while(element->kind==13)element=IP(element,6);
    if(element->kind!=6||(destructor=CClass_Destructor(element))==NULL)return 0;
    fn_00725e5d=1;if(!type->size||!element->size)CError_Internal(filename,108);total=type->size;size=element->size;
    for(item=pending_arrays;item;item=item->next)if(item->value==object)break;
    if(!item){action->kind=5;action->object=object;action->function=destructor;action->offset=type->size/element->size;action->size=element->size;return 1;}
    count=total/size;for(index=0;index<count;++index){if(index>0){copy=CompilerTools_AllocatePool(30);*copy=*action;action->next=copy;}
        size=element->size;if(index*size==0){action->kind=1;action->object=object;action->function=destructor;}else{action->kind=3;action->object=object;action->function=destructor;action->offset=index*size;}}
    *link=action;return 1;
}
void fn_005a31f0(InstContext *context,InstAction **link) {
    InstAction *action;
    while((action=*link)!=NULL){switch(action->kind){case 1:case 2:case 3:case 4:case 5:case 11:case 14:case 21:fn_00725e5d=1;break;
        case 6:case 7:case 8:case 9:case 10:case 12:case 15:case 17:case 19:case 20:CError_Internal(filename,212);break;
        case 13:if(action->type&&CTemplateTools_IsDependentType(action->type))action->type=CTemplateTools_ResolveType(context,action->type,&action->qualifiers);fn_00725e5d=1;break;
        case 16:case 18:break;case 22:if(!fn_005a3290(action,link)){*link=action->next;continue;}break;default:CError_Internal(filename,221);}
        link=&action->next;
    }
}
void fn_005a2ec0(InstStatement *statement,InstObject *object) {
    InstAction *action,*copy;void *vla;InstType *element;void *destructor=NULL;
    vla=fn_00514dc0(object->type);if(!IP(vla,12))CError_Internal(filename,311);
    element=object->type;while(element->kind==13)element=IP(element,6);if(element->kind==6)destructor=CClass_Destructor(element);
    for(;statement;statement=statement->next)for(action=statement->actions;action;action=action->next)if(action->kind==22&&action->object==object){
        if(!destructor){action->kind=11;action->object=IP(vla,12);action->function=fn_007109c4;}
        else{action->kind=21;action->object=IP(vla,12);action->function=IP(vla,16);action->offset=(SInt32)destructor;action->size=element->size;
            copy=CompilerTools_AllocatePool(30);memclrw(copy,30);copy->kind=11;copy->next=action->next;copy->object=IP(vla,12);copy->function=fn_007109c4;action->next=copy;}}
}
static inline InstNode *inst_unwrap(InstNode *node,void *save,UInt8 *saved) {
    if(node->kind==0x4c&&node->operation==6){fn_00462de0((UInt8 *)node+20,save);node=node->payload;*saved=1;}return node;
}
void fn_005a2b10(InstContext *context,InstStatement *statement,void *save,UInt8 *saved) {
    InstNode *node=inst_unwrap(statement->expression,save,saved);InstObject *oldObject,*object;InstInitValue *initializer;InstMap *map;
    if(node->kind!=0x4c||(node->operation!=23&&node->operation!=24))CError_Internal(filename,259);
    initializer=IP(node,20);oldObject=node->payload;object=CParser_NewObject(NULL);object->space=fn_007101c4;object->unknown04=oldObject->unknown04;object->type=oldObject->type;object->name=oldObject->name;object->qualifiers=oldObject->qualifiers;object->sclass=oldObject->sclass;
    if(CTemplateTools_IsDependentType(object->type)){object->type=CTemplateTools_ResolveType(context,object->type,&object->qualifiers);CDecl_CompleteType(object->type);}
    fn_0052c820(object);fn_004556f0(object,0);map=CompilerTools_AllocatePool(16);map->oldObject=oldObject;map->newObject=object;map->key=-1;map->next=context->map;context->map=map;statement->kind=1;
    fn_005a2fe0(context,initializer);fn_0052fd20(object,initializer,statement,1);fn_00544c00(object->type);
}
void fn_005a2c50(InstContext *context,InstStatement *statement,void *save,UInt8 *saved) {
    InstNode *node=inst_unwrap(statement->expression,save,saved);InstObject *oldObject,*object;InstInitValue *initializer;InstMap *map;InstPair *item,*copy,**link;
    if(node->kind!=0x4c||(node->operation!=23&&node->operation!=24))CError_Internal(filename,259);
    initializer=IP(node,20);oldObject=node->payload;if(oldObject->storage!=1)CError_Internal(filename,368);statement->kind=1;
    for(item=fn_00716d50;;item=item->next){if(!item)CError_Internal(filename,373);object=item->value;if(object->storage==1&&object->key==oldObject->key)break;}
    map=CompilerTools_AllocatePool(16);map->oldObject=oldObject;map->newObject=object;map->key=oldObject->key;map->next=context->map;context->map=map;
    if(CTemplateTools_IsDependentType(object->type)){context->resolving=1;context->pending=NULL;object->type=CTemplateTools_ResolveType(context,object->type,&object->qualifiers);context->resolving=0;
        if(context->pending){statement=fn_0052c580(context->pending,statement);if(object->type->kind==13&&IB(object->type,18)){if(initializer)CError_Error(0x27be);fn_005a2ec0(fn_0052c0f0(object,statement),object);return;}}
        CDecl_CompleteType(object->type);}
    fn_005a2fe0(context,initializer);
    if(initializer&&object->type->kind==13){copy=CompilerTools_AllocatePool(8);copy->value=object;copy->next=pending_arrays;pending_arrays=copy;}
    fn_00530a70(object,initializer,statement,1);fn_00544c00(object->type);
    if(fn_00452f10(object)){map->newObject=galloc(96);*(InstObjectCopy *)map->newObject=*(InstObjectCopy *)object;
        link=(InstPair **)&fn_00716d50;for(;;){if(!*link)CError_Internal(filename,450);if((*link)->value==object)break;link=&(*link)->next;}*link=(*link)->next;}
}
void fn_005a25d0(InstContext *context,InstStatement *statement) {
    UInt8 saved=0;UInt8 save[12],secondary[24],tertiary[16];InstNode *node,*original;InstPair *item;InstStatement *inserted;void *record;UInt8 kind;
    fn_00710b30=(UInt32)statement->actions;
    switch(statement->kind){case 1:case 2:case 3:case 16:break;
        case 4:original=statement->expression;node=original;kind=node->kind;if(kind==0x4c&&node->operation==6)node=node->payload;
            if(node->kind==0x4c&&node->operation==23){fn_005a2c50(context,statement,save,&saved);break;}if(node->kind==0x4c&&node->operation==24){fn_005a2b10(context,statement,save,&saved);break;}
            if(node->kind==0x4f){saved=kind==0x4c;if(saved)fn_00462de0((UInt8 *)original+20,save);if(!fn_00710108)CError_Internal(filename,646);statement->expression=node;node->payload=fn_005a2a60(context,node->payload);fn_00526350(fn_00710108,node->payload);}
            else{node=inst_unwrap(original,save,&saved);statement->expression=fn_0053a470(context,node);fn_00515180(statement->expression);}break;
        case 5:if(CTemplTool_IsTypeDepExpr(statement->expression)){node=statement->expression;if(node->kind==0x4c&&node->operation==6){if(!saved)node=inst_unwrap(node,save,&saved);else{fn_00462de0((UInt8 *)node+20,secondary);node=node->payload;}}statement->expression=fn_0053a470(context,node);statement->expression=fn_005a8340(statement->expression);IP(statement->aux,12)=statement->expression->type;}
            for(item=IP(statement->aux,4);item;item=item->next){record=item;node=IP(record,8);if(node->kind==0x4c&&node->operation==6){if(!saved)node=inst_unwrap(node,save,&saved);else{fn_00462de0((UInt8 *)node+20,tertiary);node=node->payload;}}IP(record,8)=fn_0053a470(context,node);node=IP(record,8);
                if(node->kind==0x34){if(!IP(record,12))fn_0052cbb0(statement->aux,(UInt8 *)node+16,NULL,IP(record,4));else{IP(record,8)=fn_0053a470(context,node);if(IB(IP(record,12),0)==0x34)fn_0052cbb0(statement->aux,(UInt8 *)IP(record,8)+16,(UInt8 *)IP(record,12)+16,IP(record,4));else CError_Error(0x278c);}}
                else CError_Error(0x278c);}IP(statement->aux,4)=NULL;break;
        case 6:case 7:node=inst_unwrap(statement->expression,save,&saved);statement->expression=fn_0053a470(context,node);statement->expression=fn_0055a940(statement->expression);break;
        case 8:node=statement->expression;if(node){node=inst_unwrap(node,save,&saved);original=statement->expression;node=fn_0053a470(context,node);if(CTemplTool_IsTypeDepExpr(original))node=fn_00529bf0(node);statement->expression=node;
                if(node->type->kind==0){statement->kind=4;if(statement->actions)fn_005a31f0(context,&statement->actions);inserted=CFunc_InsertAfterStatement(8,statement);inserted->expression=NULL;if(saved)CError_SetWrittenEntry(save);return;}}break;
        case 12:case 13:case 14:case 15:node=inst_unwrap(statement->expression,save,&saved);statement->expression=fn_0053a470(context,node);break;
        default:CError_Internal(filename,721);break;}
    if(statement->actions)fn_005a31f0(context,&statement->actions);if(saved)CError_SetWrittenEntry(save);
}
UInt8 fn_005a1b30(void *instance,InstObject *object,UInt8 report) {
    void *source,*definition;
    if(object->suppress)return 0;source=object->source;definition=fn_0053ebf0(source);
    if(definition){fn_005a1b90(instance,definition,source,NULL,object,report);return 1;}
    if(report)CError_Warning(0x27f9,object);return 0;
}
UInt8 fn_005a19a0(void *instance,UInt8 force) {
    UInt8 scope[16],changed=0;InstObject *object;
    if(!force&&IB(instance,66))return 0;
    CScope_InitScopeSearch(scope,IP(instance,6));object=CScope_NextObject(scope);
    while(object){if(object->type->kind==7&&object->storage!=6){if((force||(object->flags&2))&&!(((InstFunction *)object->type)->flags&0x102)&&fn_005a1b30(instance,object,force)&&(((InstFunction *)object->type)->flags&2))changed=1;}
        else if(fn_00452f10(object)&&!(object->qualifiers&0x10000)&&!(object->flags&4)&&(force||(object->flags&2))&&fn_005a1b30(instance,object,force)&&(object->flags&4))changed=1;
        object=CScope_NextObject(scope);
    }return changed;
}
UInt8 fn_005a1840(void) {
    void *type,*instance,*function,*specialization;InstPair *pair;InstObject *object;UInt8 changed=0;
    for(type=fn_00710b38;type;type=IP(type,48)){
        for(instance=IP(type,66);instance;instance=IP(instance,48))if((IU(instance,34)&0x800)&&!IB(instance,65)){if(fn_005a19a0(instance,0))changed=1;fn_00479c20();}
        for(pair=IP(type,74);pair;pair=pair->next)for(instance=IP(pair->value,66);instance;instance=IP(instance,48))if((IU(instance,34)&0x800)&&!IB(instance,65)){if(fn_005a19a0(instance,0))changed=1;fn_00479c20();}}
    for(function=fn_00711af8;function;function=IP(function,14))for(specialization=IP(function,50);specialization;specialization=IP(specialization,16))if(!IB(specialization,12)&&!IB(specialization,13)){
        object=IP(specialization,24);if((object->flags&2)&&!(((InstFunction *)object->type)->flags&2)){IB(specialization,12)=1;if(fn_005a1f80(function,specialization,0))changed=1;fn_00479c20();}
        object=object->alternate;if(object&&(object->flags&2)&&!(((InstFunction *)object->type)->flags&2)){IB(specialization,12)=1;if(fn_005a1f80(function,specialization,0))changed=1;fn_00479c20();}}
    return changed;
}
void fn_005a1b90(void *instance,void *definition,InstObject *source,void *override,InstObject *object,UInt8 report) {
    UInt8 scope[16],stream[4],error[12],scopeSave[16];InstContext context;InstWorkspace workspace;void *parameters,*savedOverride,*reference,*namespace,*expression;UInt8 savedTemplate,savedBrowse;
    parameters=IP(instance,52);if(!report&&!fn_00456950(object)){object->qualifiers|=0x20000;return;}
    if(object->sclass!=0x102){if(report)object->flags|=8;object->qualifiers|=0x20000;}
    if(!override&&(object->qualifiers&0x400000))override=object->specialization;
    if(IP(definition,28)){CDecl_CompleteType(instance);memclrw(&context,38);context.instance=(UInt8 *)instance+52;fn_005a2250(&context,object,override,IP(definition,28),report);return;}
    if(IP(definition,32)){CDecl_CompleteType(instance);expression=fn_00549a00(IP(definition,32),0);
        if(expression){memclrw(&context,38);context.instance=(UInt8 *)instance+52;if(override){savedOverride=fn_00716cf8;fn_00716cf8=override;}
            reference=fn_0053ea50(NULL,object);fn_00462de0((UInt8 *)definition+8,error);fn_004eb440(instance,scopeSave);fn_005a2fe0(&context,expression);CScope_RestoreScope(scopeSave);CError_SetWrittenEntry(error);fn_0053ea20(reference);if(override)fn_00716cf8=savedOverride;}
        fn_0052fd20(object,expression,NULL,0);return;}
    if(override){savedOverride=fn_00716cf8;fn_00716cf8=override;}reference=fn_0053ea50(NULL,object);namespace=IP(definition,0);
    if(!namespace)namespace=IP(fn_005dc000(fn_0053ee70(parameters)),60);
    parameters=fn_0053d900(namespace,instance,scope);
    fn_00711b70=IU(definition,8);fn_00711b74=IU(definition,12);fn_00711b78=IU(definition,16);
    fn_00715c48=fn_00711b70;fn_00715c4c=fn_00711b74;fn_00715c50=fn_00711b78;
    fn_00716ca0=fn_00711b70;fn_00716ca4=fn_00711b74;fn_00716ca8=fn_00711b78;
    fn_00448340((UInt8 *)definition+20,stream);savedTemplate=fn_00725d9e;fn_00725d9e=1;fn_00717466=fn_00447b70();savedBrowse=fn_0070f287;
    if(fn_0070f229||!fn_00711b70)fn_0070f287=0;memclrw(&workspace,152);workspace.sourceStart=IU(definition,36);workspace.browseFile=CPrep_GetPFile();workspace.sourceEnd=IU(definition,40);
    switch(object->storage){case 0:fn_004556f0(object,0);CDecl_CompleteType(object->type);fn_0052fbd0(object);break;
        case 3:case 4:if(source)fn_0053dd60(source->type,object->type);CFunc_ParseFuncDef(object,&workspace,instance,0,0,NULL);break;
        default:CError_Internal(filename,1182);break;}
    fn_0053ea20(reference);if(override)fn_00716cf8=savedOverride;fn_0053d880(parameters,instance,scope);fn_00448100((UInt8 *)definition+20,stream);fn_0070f287=savedBrowse;fn_00725d9e=savedTemplate;
}
UInt8 fn_005a1f80(void *definition,void *specialization,UInt8 report) {
    UInt8 stream[4],savedBrowse;InstContext context;InstWorkspace workspace;void *reference,*savedOverride,*namespace;InstObject *object;
    if(IB(specialization,14)&&!report)return 0;
    while(!IP(definition,42)&&!IP(definition,22)&&IP(definition,4)&&IP(definition,0))definition=fn_0053ee10(IP(definition,0));
    object=IP(specialization,24);if(!report&&!fn_00456950(object)){object->qualifiers|=0x20000;IB(specialization,12)=1;return 0;}
    if(object->sclass!=0x102){if(report)object->flags|=8;object->qualifiers|=0x20000;}
    if(IP(definition,42)){memclrw(&context,38);context.instance=specialization;return fn_005a2250(&context,object,IP(specialization,20),IP(definition,42),report);}
    if(IP(definition,22)){IB(specialization,12)=1;fn_00448340((UInt8 *)definition+22,stream);fn_0044e900((UInt8 *)definition+30);savedBrowse=fn_0070f287;
        if(fn_0070f229||!fn_00716ca0)fn_0070f287=0;fn_00717466=fn_00447b70();if(fn_00717466!=0x7b&&fn_00717466!=0x3a&&fn_00717466!=0x15d)CError_Internal(filename,998);
        memclrw(&workspace,152);workspace.sourceStart=IU(definition,54);workspace.browseFile=CPrep_GetPFile();workspace.sourceEnd=IU(definition,58);
        if(IP(specialization,20)){savedOverride=fn_00716cf8;fn_00716cf8=IP(specialization,20);}reference=fn_0053ea50(NULL,object);fn_0053dd60(((InstObject *)IP(definition,46))->type,object->type);
        namespace=fn_0053da70(IP(definition,8),IP(specialization,8),0);IP(namespace,0)=object->space;object->space=namespace;fn_0053d9d0(namespace);
        CFunc_ParseFuncDef(object,&workspace,NULL,0,0,namespace);fn_0053d8c0(namespace);object->space=IP(namespace,0);fn_0053ea20(reference);if(IP(specialization,20))fn_00716cf8=savedOverride;
        fn_00448100((UInt8 *)definition+22,stream);fn_0070f287=savedBrowse;CBrowse_ForwardObjectFileRange(object,workspace.browseFile,workspace.sourceStart,workspace.sourceEnd,IU(definition,62));return 1;}
    if(report){fn_00462e40((UInt8 *)definition+30);CError_Error(0x27f9,object);}return 0;
}
UInt8 fn_005a2250(InstContext *context,InstObject *object,void *override,void *body,UInt8 report) {
    UInt8 state[36],error[12],savedOption;void *savedOverride,*reference,*savedSpace,*classType,*definition;InstPair *item,*copy;InstObject *local;InstStatement *statement;
    pending_arrays=NULL;fn_004556f0(object,0);if(object->sclass!=0x102){if(report)object->flags|=8;object->qualifiers|=0x20000;}
    if(override){savedOverride=fn_00716cf8;fn_00716cf8=override;}reference=fn_0053ea50(NULL,object);savedOption=fn_0070f20b;fn_0070f20b=0;
    if(!context->instance)CError_Internal(filename,814);IB(context->instance,12)=1;savedSpace=fn_00711be0;fn_00711be0=object->space;if(!fn_00711be0)CError_Internal(filename,819);
    CFunc_FuncGenSetup(NULL,state,object,0);fn_00716c9c=object;fn_00710108=NULL;fn_00725ecf=0;if(object->type->kind!=7)CError_Internal(filename,824);
    if(((InstFunction *)object->type)->flags&0x10){fn_00710108=((InstFunction *)object->type)->context;fn_00725ecf=((InstFunction *)object->type)->mode==0;}
    fn_00547ed0(object,body,state,1);item=fn_00710924;classType=fn_00710108;
    if((((InstFunction *)object->type)->flags&0x1000)&&classType&&(IU(classType,34)&0x20)&&(IU(classType,34)&0x800)){
        definition=fn_0053ecc0(classType);item=fn_00710924;if(!(IU(definition,34)&0x20)){if(!item)CError_Internal(filename,853);local=CParser_NewLocalDataObject(NULL,0);local->name=fn_00710348;local->type=&fn_00699c44;fn_0052ec00(local);copy=CompilerTools_AllocatePool(8);copy->next=item->next;copy->value=local;item->next=copy;item=fn_00710924;}}
    for(;item;item=item->next){local=item->value;if(local->storage!=1)CError_Internal(filename,739);if(CTemplateTools_IsDependentType(local->type)){fn_00462de0((UInt8 *)local+36,error);local->type=CTemplateTools_ResolveType(context,local->type,&local->qualifiers);CError_SetWrittenEntry(error);fn_00526d20(local,state);}}
    CDecl_CompleteType(((InstFunction *)object->type)->result);if(CMachine_FunctionRequiresMemoryReturn(object->type)==1){for(item=fn_00710924;item;item=item->next)if(((InstObject *)item->value)->name==fn_00716cb8)break;if(!item)fn_005268d0(object);}
    statement=(InstStatement *)state;do{fn_005a25d0(context,statement);statement=statement->next;}while(statement);
    if(!fn_00725dfa)fn_00526410(object,state,state,0,0);fn_0053ea20(reference);if(override)fn_00716cf8=savedOverride;fn_00711be0=savedSpace;fn_00716c9c=NULL;fn_00710108=NULL;fn_0070f20b=savedOption;return 1;
}
