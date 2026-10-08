/* GC 3.0a5.2 native scope state and namespace storage. */
typedef unsigned char U8;
typedef signed char S8;
typedef unsigned short U16;
typedef short S16;
typedef unsigned long U32;
typedef long S32;
#pragma pack(push,2)
typedef struct HashNameNode { struct HashNameNode *next; U32 value; S16 hash; char name[1]; } HashNameNode;
typedef struct Type { S8 kind; U8 reserved; S32 size; } Type;
typedef struct NameSpace NameSpace;
typedef struct TypeClass TypeClass;
typedef struct BaseClass { struct BaseClass *next; TypeClass *base; S32 offset; U8 flags[6]; } BaseClass;
typedef struct ObjBase { U8 kind, access; } ObjBase;
typedef struct ObjType { ObjBase base; Type *type; } ObjType;
typedef struct Object { ObjBase base; U8 gap[6]; NameSpace *nspace; HashNameNode *name; Type *type; U32 quals; } Object;
typedef struct TypeMemberFunc { Type base; void *args; U8 gap[12]; U32 flags; U8 gap2[4]; TypeClass *theclass; U8 gap3[8]; U8 is_static; } TypeMemberFunc;
typedef struct NameSpaceObjectList { struct NameSpaceObjectList *next; ObjBase *object; } NameSpaceObjectList;
typedef struct NameSpaceName { struct NameSpaceName *next; HashNameNode *name; NameSpaceObjectList first; } NameSpaceName;
typedef struct NameSpaceList { struct NameSpaceList *next; NameSpace *nspace; } NameSpaceList;
struct NameSpace { NameSpace *parent; HashNameNode *name; NameSpaceList *usings; TypeClass *theclass; NameSpaceName *local_names; union { NameSpaceName *list; NameSpaceName **hash; } data; U32 names; U8 is_hash,is_global,is_unnamed,is_templ,is_function,padding; };
struct TypeClass { Type base; NameSpace *nspace; HashNameNode *name; BaseClass *bases; U8 reserved[16]; U32 flags; };
typedef struct CScopeSave { NameSpace *nspace; TypeClass *theclass; Object *function; U8 member; } CScopeSave;
typedef struct ScopeRec { struct ScopeRec *outer; NameSpace *ns; NameSpaceList *list; } ScopeRec;
typedef struct ScopeIterator { NameSpace *ns; NameSpaceName *name; NameSpaceObjectList *object; S32 bucket; } ScopeIterator;
typedef struct ParseResult { NameSpace *nspace; HashNameNode *name; ObjBase *object; NameSpaceObjectList *objects; BaseClass *basePath; TypeClass *mostderived,*foundclass; Type *type; Type *foundtemplate; U32 quals; U8 access,qualified,no_parent,ambiguous,destructor,is_type,unknown2e,unknown2f; } ParseResult;
typedef struct LookupContext { NameSpace *ns; ScopeRec *scope; ParseResult *result; } LookupContext;
typedef struct ObjTypeQualified { ObjBase base; Type *type; U32 quals; } ObjTypeQualified;
#pragma pack(pop)
extern int strcmp(const char *,const char *);
extern void *galloc(U32);
extern void *lalloc(U32);
extern void memclrw(void *,U32);
extern void CError_Internal(char *,int);
extern void fn_0045c480(int,...);
extern U8 fn_00458160(ObjBase *);
NameSpace *cscope_root,*cscope_current;
TypeClass *cscope_currentclass;
Object *cscope_currentfunc;
U8 cscope_is_member_func;
extern void *data_0071034c;
extern U8 access_00725ede;
static char filename[]="CScope.c";
void CScope_AddObject(NameSpace *,HashNameNode *,ObjBase *);

U8 CScope_IsEmptyNameSpace(NameSpace *ns) {
    if(ns->is_hash)CError_Internal(filename,928);
    return ns->data.list==0;
}
U8 CScope_IsStdNameSpace(NameSpace *ns) {
    U8 result=0;
    if(ns && !ns->theclass && ns->parent==cscope_root && ns->name && !strcmp(ns->name->name,"std"))result=1;
    return result;
}
NameSpace *CScope_FindGlobalNS(NameSpace *ns) {
    for(;ns;ns=ns->parent)if(ns->name && !ns->theclass && ns->is_global)return ns;
    return cscope_root;
}
NameSpace *CScope_FindNonClassNonFunctionNS(NameSpace *ns) {
    for(;ns;ns=ns->parent)if(!ns->theclass){if(!ns->is_templ && !ns->is_function)return ns;}
    return cscope_root;
}
NameSpace *CScope_NewListNameSpace(HashNameNode *name,U8 global) {
    NameSpace *ns=global?galloc(34):lalloc(34);
    memclrw(ns,34);ns->name=name;ns->is_hash=0;ns->is_global=global;return ns;
}
NameSpace *CScope_NewHashNameSpace(HashNameNode *name) {
    NameSpace *ns;
    NameSpaceName **table=galloc(4096);
    memclrw(table,4096);ns=galloc(34);memclrw(ns,34);ns->name=name;ns->data.hash=table;ns->is_hash=1;ns->is_global=1;return ns;
}
NameSpaceObjectList *CScope_AppendName(NameSpace *ns,HashNameNode *name) {
    NameSpaceName *entry,*tail;
    if(ns->is_hash)CError_Internal(filename,593);
    entry=ns->is_global?galloc(16):lalloc(16);
    entry->next=0;entry->name=name;entry->first.next=0;entry->first.object=0;
    if(ns->data.list){tail=ns->data.list;while(tail->next)tail=tail->next;tail->next=entry;}
    else ns->data.list=entry;
    ns->names++;return &entry->first;
}
NameSpaceObjectList *CScope_InsertName(NameSpace *ns,HashNameNode *name) {
    NameSpaceName *entry=ns->is_global?galloc(16):lalloc(16);
    entry->name=name;entry->first.next=0;entry->first.object=0;
    if(ns->is_hash){NameSpaceName **bucket=&ns->data.hash[name->hash&1023];entry->next=*bucket;*bucket=entry;}
    else {entry->next=ns->data.list;ns->data.list=entry;}
    ns->names++;return &entry->first;
}
NameSpaceName *CScope_FindNameSpaceName(NameSpace *ns,HashNameNode *name) {
    NameSpaceName *entry;
    for(entry=ns->local_names;entry;entry=entry->next)if(entry->name==name)return entry;
    if(!ns->is_hash)entry=ns->data.list;else entry=ns->data.hash[name->hash&1023];
    for(;entry;entry=entry->next)if(entry->name==name)return entry;
    return 0;
}
NameSpaceObjectList *CScope_FindQualName(NameSpace *ns,HashNameNode *name) {
    NameSpaceName *entry;
    if(!ns)CError_Internal(filename,526);
    if(!ns->is_hash)entry=ns->data.list;else entry=ns->data.hash[name->hash&1023];
    for(;entry;entry=entry->next)if(entry->name==name)return &entry->first;
    return 0;
}
NameSpaceObjectList *CScope_FindName(NameSpace *ns,HashNameNode *name) {
    NameSpaceName *entry;
    if(!ns)CError_Internal(filename,512);
    for(entry=ns->local_names;entry;entry=entry->next)if(entry->name==name)return &entry->first;
    if(!ns->is_hash)entry=ns->data.list;else entry=ns->data.hash[name->hash&1023];
    for(;entry;entry=entry->next)if(entry->name==name)return &entry->first;
    return 0;
}
U8 CScope_IsEmptySymTable(void) {
    S32 bucket;NameSpaceName *name;NameSpaceObjectList *entry;
    if(!cscope_root->is_hash)CError_Internal(filename,357);
    for(bucket=0;bucket<1024;bucket++)for(name=cscope_root->data.hash[bucket];name;name=name->next)for(entry=&name->first;entry;entry=entry->next)if(entry->object->kind!=5 || !fn_00458160(entry->object))return 0;
    return 1;
}
void CScope_RestoreScope(CScopeSave *saved) {
    cscope_current=saved->nspace;cscope_currentclass=saved->theclass;cscope_currentfunc=saved->function;cscope_is_member_func=saved->member;
}
void CScope_GetScope(CScopeSave *saved) {
    saved->nspace=cscope_current;saved->theclass=cscope_currentclass;saved->function=cscope_currentfunc;saved->member=cscope_is_member_func;
}
void CScope_SetMethodScope(Object *function,TypeClass *cls,U8 is_static,CScopeSave *saved) {
    saved->nspace=cscope_current;saved->theclass=cscope_currentclass;saved->function=cscope_currentfunc;saved->member=cscope_is_member_func;
    cscope_currentfunc=function;cscope_currentclass=cls;cscope_current=cls->nspace;cscope_is_member_func=!is_static;
}
void CScope_SetFunctionScope(Object *function,CScopeSave *saved) {
    saved->nspace=cscope_current;saved->theclass=cscope_currentclass;saved->function=cscope_currentfunc;saved->member=cscope_is_member_func;
    cscope_currentfunc=function;cscope_currentclass=0;cscope_is_member_func=0;
    if(((TypeMemberFunc *)function->type)->flags&0x10) {
        cscope_currentclass=((TypeMemberFunc *)function->type)->theclass;cscope_current=cscope_currentclass->nspace;cscope_is_member_func=!((TypeMemberFunc *)function->type)->is_static;
    } else cscope_current=function->nspace;
}
void fn_004eb3e0(TypeClass *cls,CScopeSave *saved) {
    saved->nspace=cscope_current;saved->theclass=cscope_currentclass;saved->function=cscope_currentfunc;saved->member=cscope_is_member_func;
    cscope_current=cls->nspace;cscope_currentclass=cls;if(!cscope_current)CError_Internal(filename,271);
}
void fn_004eb440(TypeClass *cls,CScopeSave *saved) {
    saved->nspace=cscope_current;saved->theclass=cscope_currentclass;saved->function=cscope_currentfunc;saved->member=cscope_is_member_func;
    cscope_current=cls->nspace;cscope_currentclass=cls;cscope_currentfunc=0;cscope_is_member_func=0;if(!cscope_current)CError_Internal(filename,252);
}
void CScope_SetNameSpaceScope(NameSpace *ns,CScopeSave *saved) {
    saved->nspace=cscope_current;saved->theclass=cscope_currentclass;saved->function=cscope_currentfunc;saved->member=cscope_is_member_func;
    cscope_current=ns;cscope_currentclass=ns->theclass;cscope_currentfunc=0;cscope_is_member_func=0;
}
void CScope_Cleanup(void) {cscope_currentfunc=0;cscope_currentclass=0;}
void CScope_Setup(void) {
    NameSpace *root;
    NameSpaceName **table=galloc(4096);
    memclrw(table,4096);root=galloc(34);memclrw(root,34);root->name=0;root->data.hash=table;root->is_hash=1;root->is_global=1;
    cscope_root=root;cscope_current=root;cscope_currentclass=0;cscope_currentfunc=0;data_0071034c=0;cscope_is_member_func=0;
}
void CScope_InitObjectIterator(ScopeIterator *state,NameSpace *ns) {
    memclrw(state,16);state->ns=ns;if(!state->ns->is_hash)state->name=ns->data.list;else state->name=ns->data.hash[0];
}
Object *CScope_NextObjectIteratorObject(ScopeIterator *state) {
    for(;;) {
        while(state->object) {
            Object *object=(Object *)state->object->object;
            if(object->base.kind==5){state->object=state->object->next;return object;}
            state->object=state->object->next;
        }
        if(state->name){state->object=&state->name->first;state->name=state->name->next;continue;}
        if(!state->ns->is_hash || ++state->bucket>=1024)return 0;
        state->name=state->ns->data.hash[state->bucket];
    }
}
ObjType *CScope_DefineTypeTag(NameSpace *ns,HashNameNode *name,Type *type) {
    ObjType *tag=galloc(6);memclrw(tag,6);tag->base.kind=2;tag->base.access=ns->theclass?access_00725ede:0;tag->type=type;
    CScope_AddObject(ns,name,(ObjBase *)tag);return tag;
}
Type *CScope_GetLocalTagType(NameSpace *ns,HashNameNode *name) {
    NameSpaceObjectList *list;NameSpaceName *entry;
    if(!ns)CError_Internal(filename,526);
    if(!ns->is_hash)entry=ns->data.list;else entry=ns->data.hash[name->hash&1023];
    while(entry){if(entry->name==name)break;entry=entry->next;}
    list=entry?&entry->first:0;
    for(;list;list=list->next)if(list->object->kind==2)return ((ObjType *)list->object)->type;
    return 0;
}
void CScope_AddGlobalObject(Object *object) {
    object->nspace=cscope_root;CScope_AddObject(cscope_root,object->name,(ObjBase *)object);
}
NameSpaceList *CScope_AddNameSpaceToList(NameSpaceList *list,NameSpace *ns) {
    NameSpaceList *entry;BaseClass *base;
    for(entry=list;entry;entry=entry->next)if(entry->nspace==ns)return list;
    entry=lalloc(8);entry->next=list;entry->nspace=ns;list=entry;
    if(ns->theclass){list=CScope_AddNameSpaceToList(list,ns->parent);for(base=ns->theclass->bases;base;base=base->next)list=CScope_AddNameSpaceToList(list,base->base->nspace);}
    return list;
}

NameSpace *CScope_ExtractNameSpace(NameSpaceObjectList *objects,U8 *error) {
    Type *type;
    for(;;) {
        if(!objects)return 0;
        switch(objects->object->kind) {
        case 1:type=((ObjType *)objects->object)->type;break;
        case 2:type=((ObjType *)objects->object)->type;break;
        case 3:return (NameSpace *)((ObjType *)objects->object)->type;
        case 0:case 4:case 5:objects=objects->next;continue;
        default:CError_Internal(filename,488);break;
        }
        if(type->kind!=6){if(type->kind==10)return 0;fn_0045c480(0x2850);if(error)*error=1;return 0;}
        return ((TypeClass *)type)->nspace;
    }
}
NameSpaceObjectList *CScope_GetLocalObject(NameSpace *ns,HashNameNode *name) {
    NameSpaceName *entry;NameSpaceObjectList *objects;
    if(!ns)CError_Internal(filename,526);
    if(!ns->is_hash)entry=ns->data.list;else entry=ns->data.hash[name->hash&1023];
    while(entry){if(entry->name==name)break;entry=entry->next;}
    objects=entry?&entry->first:0;
    if(objects){switch(objects->object->kind){case 2:return 0;case 5:return objects;default:fn_0045c480(0x278a,name->name);return 0;}}
    return 0;
}
static inline ScopeRec *find_using_scope(ScopeRec *scope,NameSpaceList *used) {
    NameSpace *ancestor;
    for(;scope;scope=scope->outer)for(ancestor=used->nspace;ancestor;ancestor=ancestor->parent)if(scope->ns==ancestor)return scope;
    CError_Internal(filename,140);return scope;
}
ScopeRec *CScope_BuildNameSpaceLookupList(NameSpace *ns) {
    ScopeRec *rec=lalloc(12),*r;
    NameSpaceList head,*scope,*u,*p,*used;
    memclrw(rec,12);rec->ns=ns;
    if(ns->parent)rec->outer=CScope_BuildNameSpaceLookupList(ns->parent);
    if(ns->usings){
        head.next=0;head.nspace=ns;
        for(scope=&head;scope;scope=scope->next)for(u=scope->nspace->usings;u;u=u->next){
            for(p=&head;p;p=p->next)if(p->nspace==u->nspace)break;
            if(!p){p=lalloc(8);p->nspace=u->nspace;p->next=scope->next;scope->next=p;}
        }
        for(used=head.next;used;used=used->next){
            r=find_using_scope(rec,used);
            for(p=r->list;p;p=p->next)if(p->nspace==used->nspace)break;
            if(!p){p=lalloc(8);p->nspace=used->nspace;p->next=r->list;r->list=p;}
        }
    }
    return rec;
}
extern void *fn_0053ed70(Type *);
NameSpaceList *CScope_BuildTypeAssociatedNameSpaceList(NameSpaceList *list,Type *type) {
    void *entry;
    for(;;) {
        switch(type->kind){
        case 0:case 1:case 2:case 3:case 5:case 8:case 10:case 15:return list;
        case 12:type=*(Type **)((U8 *)type+6);continue;
        case 13:type=*(Type **)((U8 *)type+6);continue;
        case 4:return CScope_AddNameSpaceToList(list,*(NameSpace **)((U8 *)type+6));
        case 7:
            for(entry=*(void **)((U8 *)type+6);entry;entry=*(void **)entry)if(*(Type **)((U8 *)entry+12))list=CScope_BuildTypeAssociatedNameSpaceList(list,*(Type **)((U8 *)entry+12));
            type=*(Type **)((U8 *)type+14);continue;
        case 11:
            list=CScope_BuildTypeAssociatedNameSpaceList(list,*(Type **)((U8 *)type+6));
            type=*(Type **)((U8 *)type+10);
            if(type->kind!=6)return list;
            /* Fall through to the owning class. */
        case 6:
            list=CScope_AddNameSpaceToList(list,((TypeClass *)type)->nspace);
            if(((TypeClass *)type)->flags&0x800){
                entry=*(void **)((U8 *)fn_0053ed70(type)+60);
                for(;entry;entry=*(void **)entry)switch(((U8 *)entry)[7]){
                case 0:list=CScope_BuildTypeAssociatedNameSpaceList(list,*(Type **)((U8 *)entry+8));break;
                case 1:break;
                case 2:list=CScope_BuildTypeAssociatedNameSpaceList(list,*(Type **)((U8 *)entry+8));break;
                default:CError_Internal(filename,722);break;
                }
            }
            return list;
        default:CError_Internal(filename,729);return list;
        }
    }
}
NameSpaceList *CScope_BuildAssociatedNameSpaceList(NameSpaceObjectList *arguments) {
    NameSpaceList *list=0;NameSpaceObjectList *object;
    for(;arguments;arguments=arguments->next){
        U8 *node=(U8 *)arguments->object;
        if(*node==75){
            for(object=*(NameSpaceObjectList **)(node+16);object;object=object->next){
                Object *obj=(Object *)object->object;
                if(obj->base.kind==5 && obj->type->kind==7){list=CScope_BuildTypeAssociatedNameSpaceList(list,obj->type);list=CScope_AddNameSpaceToList(list,obj->nspace);}
            }
        } else list=CScope_BuildTypeAssociatedNameSpaceList(list,*(Type **)(node+4));
    }
    return list;
}
extern S16 is_typesame(Type *,Type *);
NameSpaceObjectList *CScope_ArgumentDependentNameLookup(NameSpaceObjectList *results,HashNameNode *name,NameSpaceObjectList *arguments) {
    NameSpaceObjectList *original=results,*entry,*existing;
    NameSpaceList *list;
    Object *obj,*other;
    for(entry=results;entry;entry=entry->next){obj=(Object *)entry->object;if(obj->base.kind==5 && obj->type->kind==7 && (((TypeMemberFunc *)obj->type)->flags&0x10))return results;}
    for(list=CScope_BuildAssociatedNameSpaceList(arguments);list;list=list->next){
        for(entry=CScope_FindQualName(list->nspace,name);entry && entry!=original;entry=entry->next){
            obj=(Object *)entry->object;
            if(obj->base.kind==5 && obj->type->kind==7 && !(((TypeMemberFunc *)obj->type)->flags&0x10)){
                for(existing=results;existing;existing=existing->next){
                    other=(Object *)existing->object;
                    if(other->base.kind==5 && (other==obj || (other->nspace==obj->nspace && other->name==obj->name && is_typesame(other->type,obj->type))))break;
                }
                if(!existing){existing=lalloc(8);existing->object=entry->object;existing->next=results;results=existing;}
            }
        }
    }
    return results;
}

extern U8 CScope_FindClassMember(ParseResult *,NameSpace *,HashNameNode *,U8);
extern NameSpaceObjectList *fn_004e99e0(ScopeRec *,HashNameNode *,NameSpace **);
extern U8 option_0070f1a8;
U8 CScope_SetupParseNameResult(ParseResult *result,NameSpaceObjectList *objects,HashNameNode *name) {
    if(objects->next && objects->next->object->kind!=2){result->objects=objects;return 1;}
    switch(objects->object->kind){
    case 3:fn_0045c480(0x2851);return 0;
    case 1:
        result->type=((ObjType *)objects->object)->type;result->quals=((ObjTypeQualified *)objects->object)->quals;
        result->object=objects->object;result->name=name;result->access=objects->object->access;result->is_type=1;return 1;
    case 2:
        result->type=((ObjType *)objects->object)->type;result->quals=0;
        result->object=objects->object;result->name=name;result->access=objects->object->access;result->is_type=1;return 1;
    default:result->object=objects->object;result->objects=objects;return 1;
    }
}
NameSpaceObjectList *CScope_NSIteratorFind(LookupContext *ctx,HashNameNode *name) {
    NameSpaceObjectList *objects;
    if(ctx->scope){
        if(ctx->scope->list)return fn_004e99e0(ctx->scope,name,0);
        if(ctx->scope->ns->theclass){if(CScope_FindClassMember(ctx->result,ctx->scope->ns,name,0)){objects=ctx->result->objects;ctx->result->objects=0;return objects;}return 0;}
        if((objects=CScope_FindName(ctx->scope->ns,name))!=0)return objects;
    }else {
        if(ctx->ns->theclass){if(CScope_FindClassMember(ctx->result,ctx->ns,name,0)){objects=ctx->result->objects;ctx->result->objects=0;return objects;}return 0;}
        if((objects=CScope_FindName(ctx->ns,name))!=0)return objects;
    }
    return 0;
}
static inline void iterator_init(LookupContext *ctx,NameSpace *ns,ParseResult *result) {
    if(!ns->usings){ctx->ns=ns;ctx->scope=0;}
    else {ctx->ns=0;ctx->scope=CScope_BuildNameSpaceLookupList(ns);}
    ctx->result=result;
}
static inline U8 iterator_next(LookupContext *ctx) {
    NameSpace *ns;
    if(ctx->scope){ctx->scope=ctx->scope->outer;return ctx->scope!=0;}
    if(ctx->result->no_parent)return 0;
    ctx->ns=ctx->ns->parent;
    if(!ctx->ns)return 0;
    ns=ctx->ns;
    if(ns->usings && !ctx->result->no_parent){ctx->scope=CScope_BuildNameSpaceLookupList(ns);ctx->ns=0;}
    return 1;
}
U8 CScope_FindTypeName(NameSpace *ns,HashNameNode *name,ParseResult *result) {
    LookupContext ctx;NameSpaceObjectList *objects;
    memclrw(result,48);iterator_init(&ctx,ns,result);
    do {
        objects=CScope_NSIteratorFind(&ctx,name);
        if(objects){switch(objects->object->kind){case 3:result->nspace=(NameSpace *)((ObjType *)objects->object)->type;return 1;case 1:case 2:return CScope_SetupParseNameResult(result,objects,name);default:return 0;}}
    }while(iterator_next(&ctx));
    return 0;
}
U8 CScope_FindClassMemberObject(TypeClass *cls,ParseResult *result,HashNameNode *name) {
    NameSpaceObjectList *objects;
    memclrw(result,48);
    if(CScope_FindClassMember(result,cls->nspace,name,0)){
        objects=result->objects;result->objects=0;
        if(objects && objects->object->kind==5)return CScope_SetupParseNameResult(result,objects,name);
    }
    return 0;
}
U8 CScope_PossibleTypeName(HashNameNode *name) {
    ParseResult result;LookupContext ctx;NameSpaceObjectList *objects;
    memclrw(&result,48);iterator_init(&ctx,cscope_current,&result);
    do {
        objects=CScope_NSIteratorFind(&ctx,name);
        if(objects){switch(objects->object->kind){case 1:case 3:return 1;case 2:if(option_0070f1a8)return 1;break;default:return 0;}}
    }while(iterator_next(&ctx));return 0;
}
NameSpaceObjectList *CScope_FindObjectList(ParseResult *result,HashNameNode *name) {
    LookupContext ctx;NameSpaceObjectList *objects;
    memclrw(result,48);iterator_init(&ctx,cscope_current,result);
    do {
        objects=CScope_NSIteratorFind(&ctx,name);
        if(objects){while(objects && !option_0070f1a8 && objects->object->kind==2)objects=objects->next;
            if(objects){result->nspace=ctx.scope?ctx.scope->ns:ctx.ns;return objects;}}
    }while(iterator_next(&ctx));return 0;
}
U8 CScope_FindNonClassObject(NameSpace *ns,ParseResult *result,HashNameNode *name) {
    LookupContext ctx;NameSpaceObjectList *objects;
    memclrw(result,48);iterator_init(&ctx,ns,result);
    do {
        if(ctx.scope){if(ctx.scope->list)objects=fn_004e99e0(ctx.scope,name,0);else if(ctx.scope->ns->theclass)objects=0;else objects=CScope_FindName(ctx.scope->ns,name);}
        else if(ctx.ns->theclass)objects=0;else objects=CScope_FindName(ctx.ns,name);
        while(objects && !option_0070f1a8 && objects->object->kind==2)objects=objects->next;
        if(objects){if(ctx.scope)ctx.ns=ctx.scope->ns;result->nspace=ctx.ns;return CScope_SetupParseNameResult(result,objects,name);}
    }while(iterator_next(&ctx));return 0;
}

extern S16 tk;
extern HashNameNode *data_00710384;
extern S16 fn_00447b70(void);
extern void fn_0045baf0(int,...);
NameSpace *CScope_ParseQualifiedNamespaceSpecifier(NameSpace *ns) {
    ParseResult result;LookupContext ctx;NameSpaceObjectList *objects;
    memclrw(&result,48);
    if(tk==386){result.no_parent=1;ns=cscope_root;tk=fn_00447b70();}
    for(;;){
        if(tk!=-3){fn_0045c480(0x277b);return ns;}
        iterator_init(&ctx,ns,&result);
        do {
            objects=CScope_NSIteratorFind(&ctx,data_00710384);
            if(objects && objects->object->kind==3){ns=(NameSpace *)((ObjType *)objects->object)->type;goto found;}
        }while(iterator_next(&ctx));
        fn_0045c480(0x279c,data_00710384->name);
found:
        tk=fn_00447b70();if(tk!=386)return ns;
        result.no_parent=1;tk=fn_00447b70();
    }
}
void CScope_ParseUsingDirective(NameSpace *ns) {
    NameSpaceList *entry;NameSpace *used=CScope_ParseQualifiedNamespaceSpecifier(ns);
    if(used!=ns){
        for(entry=ns->usings;entry;entry=entry->next)if(entry->nspace==used)break;
        if(!entry){entry=galloc(8);entry->next=ns->usings;entry->nspace=used;ns->usings=entry;}
    }else fn_0045c480(0x2851);
    if(tk!=';')fn_0045baf0(0x278b);
}
void CScope_ParseNameSpaceAlias(HashNameNode *name) {
    NameSpaceObjectList *objects;
    NameSpaceName *entry;NameSpace *ns=cscope_current;
    if(!ns)CError_Internal(filename,526);
    if(!ns->is_hash)entry=ns->data.list;else entry=ns->data.hash[name->hash&1023];
    while(entry){if(entry->name==name)break;entry=entry->next;}
    objects=entry?&entry->first:0;
    if(objects){
        if(objects->object->kind==3){tk=fn_00447b70();if(CScope_ParseQualifiedNamespaceSpecifier(cscope_current)!=(NameSpace *)((ObjType *)objects->object)->type)fn_0045c480(0x278a,name->name);}
        else {fn_0045c480(0x2850);tk=fn_00447b70();CScope_ParseQualifiedNamespaceSpecifier(cscope_current);}
    }else {
        ObjType *alias;
        tk=fn_00447b70();alias=galloc(6);memclrw(alias,6);alias->base.kind=3;alias->base.access=0;
        alias->type=(Type *)CScope_ParseQualifiedNamespaceSpecifier(cscope_current);
        CScope_AddObject(cscope_current,name,(ObjBase *)alias);
    }
    if(tk!=';')fn_0045baf0(0x278b);
}

Type *CScope_GetTagType(NameSpace *ns,HashNameNode *name) {
    ParseResult result;LookupContext ctx;NameSpaceObjectList *objects;
    memclrw(&result,48);iterator_init(&ctx,ns,&result);
    do {for(objects=CScope_NSIteratorFind(&ctx,name);objects;objects=objects->next)if(objects->object->kind==2)return ((ObjType *)objects->object)->type;}while(iterator_next(&ctx));
    return 0;
}
Type *CScope_GetType(NameSpace *ns,HashNameNode *name,U32 *quals) {
    ParseResult result;LookupContext ctx;NameSpaceObjectList *objects;
    memclrw(&result,48);iterator_init(&ctx,ns,&result);
    do {for(objects=CScope_NSIteratorFind(&ctx,name);objects;objects=objects->next){
        if(objects->object->kind==2){if(quals)*quals=0;return ((ObjType *)objects->object)->type;}
        if(objects->object->kind==1){if(quals)*quals=((ObjTypeQualified *)objects->object)->quals;return ((ObjType *)objects->object)->type;}
    }}while(iterator_next(&ctx));return 0;
}
extern void fn_00514b90(TypeClass *);
U8 CScope_FindQualifiedClassMember(ParseResult *result,TypeClass *cls,HashNameNode *name,U8 report) {
    NameSpaceObjectList *objects;NameSpace *ns;
    memclrw(result,48);fn_00514b90(cls);
    if(CScope_FindClassMember(result,cls->nspace,name,0)){
        objects=result->objects;if(!objects)CError_Internal(filename,2099);
        result->objects=0;if(CScope_SetupParseNameResult(result,objects,name))return 1;
    }
    if(report){
        ns=cls->nspace;
        if(!ns)fn_0045c480(0x27a6,name->name);
        else if(ns->theclass)fn_0045c480(0x2899,name->name,ns->theclass,0);
        else if(ns!=cscope_root && ns->name)fn_0045c480(0x28a5,name->name,ns->name->name);
        else fn_0045c480(0x28a5,name->name,"::");
    }
    return 0;
}
NameSpaceObjectList *CScope_AddScopeObjects(NameSpace *ns,NameSpaceObjectList *results,HashNameNode *name) {
    ParseResult result;LookupContext ctx;NameSpaceObjectList *objects,*existing;
    Object *a,*b;
    memclrw(&result,48);iterator_init(&ctx,ns,&result);
    do {
        for(objects=CScope_NSIteratorFind(&ctx,name);objects;objects=objects->next){
            if(objects->object->kind!=5)continue;
            a=(Object *)objects->object;
            for(existing=results;existing;existing=existing->next){
                if(existing->object->kind!=5)continue;b=(Object *)existing->object;
                if(a==b || (a->nspace==b->nspace && a->name==b->name && is_typesame(a->type,b->type)))break;
            }
            if(!existing){existing=lalloc(8);existing->object=objects->object;existing->next=results;results=existing;}
        }
    }while(iterator_next(&ctx));return results;
}
NameSpaceObjectList *CScope_CopyNameSpaceObjectList(NameSpaceObjectList *objects,U8 global) {
    NameSpaceObjectList *head,*tail;
    if(!objects)return 0;
    head=global?galloc(8):lalloc(8);tail=head;
    for(;;){
        tail->object=objects->object;objects=objects->next;
        if(!objects){tail->next=0;return head;}
        tail->next=global?galloc(8):lalloc(8);tail=tail->next;
    }
}
static inline Object *unalias(Object *object) {
    while(((U8 *)object)[2]==6)object=*(Object **)((U8 *)object+64);
    return object;
}
U8 CScope_IsSameNSOL(NameSpaceObjectList *a,NameSpaceObjectList *b) {
    NameSpaceObjectList *x,*y;Object *object,*other;
    for(x=a;x;x=x->next){
        if(x->object->kind!=5)return 0;object=unalias((Object *)x->object);
        for(y=b;y;y=y->next){if(y->object->kind!=5)continue;other=unalias((Object *)y->object);if(object==other)break;}
        if(!y)return 0;
    }
    for(x=b;x;x=x->next){
        if(x->object->kind!=5)return 0;object=unalias((Object *)x->object);
        for(y=a;y;y=y->next){if(y->object->kind!=5)continue;other=unalias((Object *)y->object);if(object==other)break;}
        if(!y)return 0;
    }
    return 1;
}
extern U8 fn_00454700(void *,void *);
U8 CScope_HidesObject(Object *object,NameSpaceObjectList *candidate) {
    Object *other;TypeMemberFunc *a,*b;void *aa,*bb;
    other=(Object *)candidate->object;
    if(other->base.kind==5 && other!=object && other->type->kind==7){
        b=(TypeMemberFunc *)other->type;
        if(b->flags&0x10){
            a=(TypeMemberFunc *)object->type;
            if((a->flags&0x18000)==(b->flags&0x18000)){
                aa=a->args;if(aa && !a->is_static)aa=*(void **)aa;
                bb=b->args;if(bb && !b->is_static)bb=*(void **)bb;
                if(fn_00454700(aa,bb))return 1;
            }
        }
    }
    return 0;
}

NameSpaceList *fn_004ea650(NameSpaceList *list,NameSpace *ns,HashNameNode *name,U8 mode) {
    NameSpaceList *entry,*head,*used;
    for(entry=list;entry;entry=entry->next)if(entry->nspace==ns)return list;
    head=lalloc(8);head->next=list;head->nspace=ns;list=head;
    if(ns->usings){
        if(CScope_FindQualName(ns,name))return head;
        for(used=ns->usings;used;used=used->next)list=fn_004ea650(list,used->nspace,name,mode);
    }
    return list;
}
extern char *fn_0045d9e0(NameSpace *,HashNameNode *);
NameSpaceObjectList *CScope_FindLookupName(NameSpace *ns,HashNameNode *name,U8 mode) {
    NameSpaceList *list=fn_004ea650(0,ns,name,mode);
    NameSpaceObjectList *found=0,*candidate;NameSpace *first=0;
    for(;list;list=list->next){
        candidate=CScope_FindQualName(list->nspace,name);
        if(candidate){switch(mode){
        case 0:break;
        case 1:while(candidate && candidate->object->kind!=2)candidate=candidate->next;break;
        case 2:while(candidate && candidate->object->kind!=2 && candidate->object->kind!=1)candidate=candidate->next;break;
        case 3:{U8 error=0;if(!CScope_ExtractNameSpace(candidate,&error))candidate=0;break;}
        default:CError_Internal(filename,2166);break;
        }}
        if(candidate){
            if(!found){found=candidate;first=list->nspace;}
            else {
                if(name && first!=list->nspace)fn_0045c480(0x284f,fn_0045d9e0(first,name),fn_0045d9e0(list->nspace,name));
                else fn_0045c480(0x27cc);
                break;
            }
        }
    }
    return found;
}
U8 CScope_FindQualifiedType(ParseResult *result,NameSpace *ns,HashNameNode *name) {
    NameSpaceObjectList *objects;
    if(ns->theclass){fn_00514b90(ns->theclass);return CScope_FindClassMember(result,ns,name,2)!=0;}
    objects=CScope_FindLookupName(ns,name,2);
    if(!objects)return 0;
    if(objects->object->kind==2){result->type=((ObjType *)objects->object)->type;result->quals=0;}
    else if(objects->object->kind==1){result->type=((ObjType *)objects->object)->type;result->quals=((ObjTypeQualified *)objects->object)->quals;}
    else CError_Internal(filename,2417);
    return 1;
}

U8 cscope_isambig,cscope_lookuptype;
S32 cscope_foundclassoffset;
Type *cscope_foundtemplate;
TypeClass *cscope_foundclass,*cscope_mostderived;
HashNameNode *cscope_name;
extern U8 fn_005415f0(TypeClass *,TypeClass *,TypeClass *);
extern U8 fn_00541e20(BaseClass *,BaseClass *);
extern BaseClass *fn_00541730(TypeClass *,TypeClass *);
extern void *fn_0053ed20(Type *);
extern Type *fn_0053ee70(void *);
static inline void class_ambiguity(TypeClass *a,TypeClass *b,HashNameNode *name) {
    if(name && a->nspace!=b->nspace)fn_0045c480(0x284f,fn_0045d9e0(a->nspace,name),fn_0045d9e0(b->nspace,name));
    else fn_0045c480(0x27cc);
}
BaseClass *CScope_RecFindClassMember(ParseResult *result,TypeClass *cls,S32 offset) {
    NameSpaceObjectList *objects=CScope_FindName(cls->nspace,cscope_name);
    BaseClass *path,*node,*base,*best;TypeClass *previous_class;
    if(objects){
        if(cscope_foundclass){
            if(fn_005415f0(cscope_mostderived,cscope_foundclass,cls))return 0;
            if(fn_005415f0(cscope_mostderived,cls,cscope_foundclass))cscope_foundclass=0;
        }
        switch(cscope_lookuptype){
        case 3:{
            U8 error=0;NameSpace *ns=CScope_ExtractNameSpace(objects,&error);
            if(ns){
                if(cscope_foundclass){
                    if(cscope_foundclass==cls){if(cscope_foundclassoffset!=offset)cscope_isambig=1;return 0;}
                    class_ambiguity(cscope_foundclass,cls,cscope_name);return 0;
                }
                cscope_foundclass=cls;cscope_foundclassoffset=offset;result->nspace=ns;goto make_path;
            }
            if(error)return 0;break;
        }
        case 0:
            if(cscope_foundclass){
                if(objects->object->kind==2 && result->objects->object->kind==2){
                    void *a=fn_0053ed20(((ObjType *)objects->object)->type);
                    void *b=fn_0053ed20(((ObjType *)result->objects->object)->type);
                    if(a && b && *(void **)((U8 *)a+52)==*(void **)((U8 *)b+52)){
                        cscope_foundtemplate=fn_0053ee70(*(void **)((U8 *)a+52));goto accept_objects;
                    }
                }
                if(cscope_foundclass==cls){
                    if(cscope_foundclassoffset!=offset){cscope_isambig=1;return 0;}
                }else if(!CScope_IsSameNSOL(objects,result->objects)){
                    class_ambiguity(cscope_foundclass,cls,cscope_name);return 0;
                }
            }
accept_objects:
            cscope_foundclass=cls;cscope_foundclassoffset=offset;result->objects=objects;goto make_path;
        case 2:
            for(;objects;objects=objects->next)if(objects->object->kind==1 || objects->object->kind==2){
                if(cscope_foundclass){if(cscope_foundclass==cls){if(cscope_foundclassoffset!=offset)cscope_isambig=1;return 0;}class_ambiguity(cscope_foundclass,cls,cscope_name);return 0;}
                cscope_foundclass=cls;cscope_foundclassoffset=offset;result->type=((ObjType *)objects->object)->type;
                result->quals=objects->object->kind==2?0:((ObjTypeQualified *)objects->object)->quals;result->access=objects->object->access;goto make_path;
            }
            break;
        case 1:
            for(;objects;objects=objects->next)if(objects->object->kind==2){
                if(cscope_foundclass){if(cscope_foundclass==cls){if(cscope_foundclassoffset!=offset)cscope_isambig=1;return 0;}class_ambiguity(cscope_foundclass,cls,cscope_name);return 0;}
                cscope_foundclass=cls;cscope_foundclassoffset=offset;result->type=((ObjType *)objects->object)->type;result->access=objects->object->access;goto make_path;
            }
            break;
        default:CError_Internal(filename,1477);break;
        }
    }
    best=0;
    for(base=cls->bases;base;base=base->next){
        S32 next_offset;
        if(((U8 *)base)[17])next_offset=fn_00541730(cscope_mostderived,base->base)->offset;
        else next_offset=offset+base->offset;
        path=CScope_RecFindClassMember(result,base->base,next_offset);
        if(path){
            node=lalloc(8);node->next=path;node->base=cls;
            if(best && previous_class==cscope_foundclass){if(fn_00541e20(node,best))best=node;}
            else {previous_class=cscope_foundclass;best=node;}
        }
    }
    return best;
make_path:
    node=lalloc(8);node->next=0;node->base=cls;return node;
}
U8 CScope_FindClassMember(ParseResult *result,NameSpace *ns,HashNameNode *name,U8 mode) {
    BaseClass *path;
    cscope_mostderived=ns->theclass;cscope_foundclass=0;cscope_foundtemplate=0;cscope_name=name;cscope_lookuptype=mode;cscope_isambig=0;
    path=CScope_RecFindClassMember(result,cscope_mostderived,0);
    if(!path)return 0;
    result->mostderived=cscope_mostderived;
    while(path->next)path=path->next;
    result->foundclass=path->base;
    if(cscope_isambig)result->ambiguous=1;
    return 1;
}

void CScope_AddObject(NameSpace *ns,HashNameNode *name,ObjBase *object) {
    NameSpaceObjectList *objects,*tail,*new_entry;ObjBase *old;
    if(ns->is_function){ns=ns->parent;if(!ns)CError_Internal(filename,965);}
    objects=CScope_FindQualName(ns,name);
    tail=objects;
    if(!objects){
        if(ns->theclass && (ns->theclass->flags&0x900))CScope_AppendName(ns,name)->object=object;
        else CScope_InsertName(ns,name)->object=object;
        return;
    }
    new_entry=ns->is_global?galloc(8):lalloc(8);
    old=objects->object;
    if(object->kind==3 || old->kind==3){fn_0045c480(0x2852);return;}
    if(object->kind==2){
        for(;;){
            old=tail->object;
            if(old->kind==2){fn_0045c480(0x2852);return;}
            if(option_0070f1a8 && old->kind==1 && !is_typesame(((ObjType *)object)->type,((ObjType *)old)->type)){fn_0045c480(0x285c);return;}
            if(!tail->next)break;tail=tail->next;
        }
        tail->next=new_entry;new_entry->next=0;new_entry->object=object;return;
    }
    if(old->kind==2){
        if(option_0070f1a8 && object->kind==1 && !is_typesame(((ObjType *)object)->type,((ObjType *)old)->type)){fn_0045c480(0x285c);return;}
        if(objects->next)CError_Internal(filename,1007);
        new_entry->object=objects->object;new_entry->next=0;objects->object=object;objects->next=new_entry;return;
    }
    if(option_0070f1a8 && object->kind==5 && (((Object *)object)->type->kind==7 || *(S16 *)((U8 *)object+24)==357)){
        for(;;){
            old=tail->object;
            if(old->kind==2){
                tail->next=galloc(8);tail->next->next=0;tail->next->object=tail->object;tail->object=object;return;
            }
            if(old->kind!=5 || (((Object *)old)->type->kind!=7 && *(S16 *)((U8 *)old+24)!=357)){fn_0045c480(0x2852);return;}
            if(!tail->next){tail->next=galloc(8);tail->next->next=0;tail->next->object=object;return;}
            tail=tail->next;
        }
    }
    fn_0045c480(0x2852);
}

/* Qualified-name parsing retains the native 48-byte result ABI. */
U8 CScope_ParseQualifiedNameSpace(ParseResult *,NameSpace *,U8,U8);
NameSpace *fn_004e7c20(NameSpace *ns,HashNameNode *name,U8 report) {
    ParseResult result;LookupContext ctx;NameSpaceObjectList *objects;ObjBase *object;Type *type;
    memclrw(&result,48);iterator_init(&ctx,ns,&result);
    do {
        for(objects=CScope_NSIteratorFind(&ctx,name);objects;objects=objects->next){
            object=objects->object;
            switch(object->kind){
            case 3:return (NameSpace *)((ObjType *)object)->type;
            case 2:
                type=((ObjType *)object)->type;
                if(type->kind==6)return ((TypeClass *)type)->nspace;
                fn_0045c480(0x28a6,name->name);return 0;
            case 1:
                type=((ObjType *)object)->type;
                if(type->kind==6)return ((TypeClass *)type)->nspace;
                fn_0045c480(0x28a6,name->name);return 0;
            }
        }
    }while(iterator_next(&ctx));
    if(report){
        if(ns){if(ns->theclass)fn_0045c480(0x2899,name->name,ns->theclass,0);
            else fn_0045c480(0x28a5,name->name,ns!=cscope_root && ns->name?ns->name->name:"::");}
        else fn_0045c480(0x27a6,name->name);
    }
    return 0;
}
extern void fn_0045c2c0(int,...);
NameSpace *fn_004e6590(NameSpace *ns,HashNameNode *name,U8 *in_class) {
    ParseResult result;NameSpace *found=0,*outer;TypeClass *a,*b;
    memclrw(&result,48);
    if(CScope_FindClassMember(&result,ns,name,3)){
        found=result.nspace;if(!found)CError_Internal(filename,4115);*in_class=1;
    }else *in_class=0;
    outer=fn_004e7c20(cscope_current,name,0);
    if(found){
        if(outer && found!=outer){
            a=found->theclass;b=outer->theclass;
            if(!a || !b || !(a->flags&0x800) || !(b->flags&0x100))fn_0045c2c0(0x27cc);
        }
        return found;
    }
    if(outer)return outer;
    if(ns){if(ns->theclass)fn_0045c480(0x2899,name->name,ns->theclass,0);
        else fn_0045c480(0x28a5,name->name,ns!=cscope_root && ns->name?ns->name->name:"::");}
    else fn_0045c480(0x27a6,name->name);
    return 0;
}
extern U8 fn_00455f30(void *,U8,U8,void *,void *);
extern void fn_00448fa0(void);
U8 fn_004e8320(ParseResult *result) {
    HashNameNode *name;NameSpace *ns;NameSpaceObjectList *objects;ScopeRec scope;
    if((tk!=386 && tk!=-3) || !CScope_ParseQualifiedNameSpace(result,0,1,1) || !result->no_parent){fn_0045c480(0x27d8);return 0;}
    if(result->type)CError_Internal(filename,2956);
    if(!result->nspace)CError_Internal(filename,2957);
    switch(tk){
    case -3:name=data_00710384;break;
    case 342:
        if(!fn_00455f30(0,1,1,0,0))return 0;
        name=data_00710384;fn_00448fa0();break;
    default:fn_0045c480(0x277b);return 0;
    }
    ns=result->nspace;
    if(ns->theclass){
        fn_00514b90(ns->theclass);
        if(CScope_FindClassMember(result,ns,name,0)){objects=result->objects;result->objects=0;}else objects=0;
    }else{
        scope.outer=0;scope.ns=0;scope.list=fn_004ea650(0,ns,name,0);
        objects=fn_004e99e0(&scope,name,&result->nspace);
    }
    if(objects){result->objects=objects;result->name=name;return 1;}
    fn_0045c480(0x279c,fn_0045d9e0(result->nspace,name));return 0;
}
extern void *fn_005423e0(TypeClass *);
extern S16 fn_00447a30(void);
extern void *fn_0053ecc0(TypeClass *);
extern void *fn_004ef3a0(void **,U32 *);
extern U8 fn_0053c850(void *,void *);
U8 CScope_CheckDtorName(TypeClass *cls,U8 *implicit) {
    void *primary,*instance,*args,*expected;U32 flag;
    tk=fn_00447b70();if(tk!=-3)fn_0045c480(0x277b);
    if(!cls)goto invalid;
    *implicit=0;
    if(cls->name!=data_00710384 && CScope_GetType(cls->nspace,data_00710384,0)!=(Type *)cls && CScope_GetType(cscope_current,data_00710384,0)!=(Type *)cls)goto invalid;
    if(!fn_005423e0(cls))*implicit=1;
    if((cls->flags&0x800) && fn_00447a30()==60){
        primary=fn_0053ecc0(cls);
        while(*(void **)((U8 *)primary+70))primary=*(void **)((U8 *)primary+70);
        instance=fn_0053ed70((Type *)cls);tk=fn_00447b70();args=fn_004ef3a0(&primary,&flag);
        expected=*(void **)((U8 *)instance+68);if(!expected)expected=*(void **)((U8 *)instance+60);
        if(!fn_0053c850(expected,args))fn_0045c480(0x2886);
    }
    return 1;
invalid:fn_0045c480(0x279d);return 0;
}
static inline U8 same_lookup_object(ObjBase *a,ObjBase *b) {
    if(a==b)return 1;
    if(a->kind!=b->kind)return 0;
    switch(a->kind){
    case 0:return *(U32 *)((U8 *)a+10)==*(U32 *)((U8 *)b+10);
    case 1:return ((ObjTypeQualified *)a)->type==((ObjTypeQualified *)b)->type && ((ObjTypeQualified *)a)->quals==((ObjTypeQualified *)b)->quals;
    case 2:return ((ObjType *)a)->type==((ObjType *)b)->type;
    case 5:
        if(((U8 *)a)[2]==6){if(((U8 *)b)[2]==6)return *(ObjBase **)((U8 *)a+64)==*(ObjBase **)((U8 *)b+64);return *(ObjBase **)((U8 *)a+64)==b;}
        if(((U8 *)b)[2]==6)return a==*(ObjBase **)((U8 *)b+64);
    }
    return 0;
}
static inline U8 scope_object_function(ObjBase *object) {
    return object->kind==5 && (((Object *)object)->type->kind==7 || *(S16 *)((U8 *)object+24)==357);
}
NameSpaceObjectList *fn_004e99e0(ScopeRec *scope,HashNameNode *name,NameSpace **found_ns) {
    NameSpaceObjectList *found,*candidate,*x,*y,*tail,*node;NameSpaceList *used;NameSpaceName *local;NameSpace *owner;U8 copied=0;
    if(scope->ns){
        for(local=scope->ns->local_names;local;local=local->next)if(local->name==name)return &local->first;
        found=CScope_FindQualName(scope->ns,name);owner=found?scope->ns:0;
    }else {found=0;owner=0;}
    for(used=scope->list;used;used=used->next){
        candidate=CScope_FindQualName(used->nspace,name);if(!candidate)continue;
        if(!found){found=candidate;owner=used->nspace;continue;}
        for(x=candidate;x;x=x->next){
            for(y=found;y;y=y->next)if(same_lookup_object(y->object,x->object))break;
            if(y)continue;
            if(!copied){found=CScope_CopyNameSpaceObjectList(found,0);copied=1;}
            for(y=found;y;y=y->next){
                if(scope_object_function(x->object)){if(scope_object_function(y->object) || y->object->kind==2)continue;}
                else if(x->object->kind==2){if(y->object->kind!=2)continue;}
                else if(y->object->kind==2)continue;
                if(name && owner!=used->nspace)fn_0045c480(0x284f,fn_0045d9e0(owner,name),fn_0045d9e0(used->nspace,name));
                else fn_0045c480(0x27cc);
                break;
            }
            if(y)continue;
            node=lalloc(8);node->object=x->object;
            if(x->object->kind==2 && found){tail=found;while(tail->next)tail=tail->next;tail->next=node;node->next=0;}
            else {node->next=found;found=node;}
        }
    }
    if(found_ns)*found_ns=owner;
    return found;
}

#pragma pack(push,2)
typedef struct NativeObject { Object base; U8 extra[72]; } NativeObject;
typedef struct NativeEnum { ObjBase base; U8 extra[20]; } NativeEnum;
typedef struct NativeMember { ObjBase base; U8 extra[22]; TypeClass *owner; ObjBase *original; } NativeMember;
#pragma pack(pop)
extern U8 fn_0053f270(TypeClass *,TypeClass *);
extern void fn_0053f5b0(void *,TypeClass *,TypeClass *,U8,U8,HashNameNode *);
extern void fn_0053f570(Type *);
extern U8 CScope_ParseExprName(ParseResult *);
extern U8 parse_name_in_namespace(ParseResult *,NameSpace *);
extern HashNameNode *destructor_name;
static inline void scope_missing(NameSpace *ns,HashNameNode *name) {
    if(!ns)fn_0045c480(0x27a6,name->name);
    else if(ns->theclass)fn_0045c480(0x2899,name->name,ns->theclass,0);
    else fn_0045c480(0x28a5,name->name,ns!=cscope_root && ns->name?ns->name->name:"::");
}
static inline U8 validate_member(ParseResult *result,TypeClass *cls) {
    if(!result->foundclass)return 0;
    if(result->foundclass==cls || fn_0053f270(result->foundclass,cls))return 1;
    if(result->name)scope_missing(result->foundclass->nspace,result->name);else fn_0045c480(0x2858);
    return 0;
}
U8 CScope_ParseMemberName(TypeClass *cls,ParseResult *result,U8 allow_template,U8 restrict_class) {
    HashNameNode *name;U8 in_class,implicit;NameSpace *ns;NameSpaceObjectList *objects;ScopeRec scope;S16 next;
    if(tk!=386 && restrict_class){
        if(tk==-3){
            name=data_00710384;next=fn_00447a30();data_00710384=name;
            if(next==60){if(allow_template)goto expression;}
            else if(next==386){ns=fn_004e6590(cls->nspace,name,&in_class);if(ns && !in_class)goto expression;}
        }else if(tk==126){
            memclrw(result,48);if(!CScope_CheckDtorName(cls,&implicit))return 0;
            if(implicit){result->qualified=1;return 1;}
            ns=cls->nspace;name=destructor_name;
            if(ns->theclass){fn_00514b90(ns->theclass);
                if(CScope_FindClassMember(result,ns,name,0)){objects=result->objects;result->objects=0;}else objects=0;
            }else {scope.outer=0;scope.ns=0;scope.list=fn_004ea650(0,ns,name,0);objects=fn_004e99e0(&scope,name,&result->nspace);}
            if(objects)return CScope_SetupParseNameResult(result,objects,destructor_name);
            fn_0045c480(0x279c,fn_0045d9e0(result->nspace,destructor_name));return 0;
        }
        memclrw(result,48);return parse_name_in_namespace(result,cls->nspace);
    }
expression:
    if(!CScope_ParseExprName(result))return 0;
    if(result->foundtemplate)fn_0053f570(result->foundtemplate);
    if(result->type && result->type->kind==10 && ((U8 *)result->type)[6]==1){
        if(allow_template)return 1;
        fn_0045c480(0x2864,(*(HashNameNode **)((U8 *)result->type+12))->name);result->type=0;return 0;
    }
    if(result->qualified)return 1;
    return validate_member(result,cls);
}
void CScope_AddUsingObject(TypeClass *mostderived,TypeClass *foundclass,NameSpace *ns,ObjBase *object,HashNameNode *name,U8 access) {
    ObjBase *copy;NameSpaceObjectList *objects,*entry;Object *other;TypeMemberFunc *type;
    if(foundclass){
        if(!ns->theclass){fn_0045c480(0x27d8);return;}
        if(!name && object->kind==4)name=*(HashNameNode **)((U8 *)object+8);
        fn_0053f5b0(0,mostderived,foundclass,object->access,0,name);
    }
    if(object->kind==1){
        if(!ns->theclass){objects=CScope_FindQualName(ns,name);
            if(objects && objects->object->kind==1 && ((ObjTypeQualified *)object)->type==((ObjTypeQualified *)objects->object)->type && ((ObjTypeQualified *)object)->quals==((ObjTypeQualified *)objects->object)->quals)return;}
        copy=galloc(10);*(ObjTypeQualified *)copy=*(ObjTypeQualified *)object;copy->access=access;CScope_AddObject(ns,name,copy);return;
    }
    if(object->kind==2){
        if(!ns->theclass){objects=CScope_FindQualName(ns,name);if(objects && objects->object->kind==2 && ((ObjType *)object)->type==((ObjType *)objects->object)->type)return;}
        copy=galloc(6);*(ObjType *)copy=*(ObjType *)object;copy->access=access;CScope_AddObject(ns,name,copy);return;
    }
    if(object->kind==0){copy=galloc(22);*(NativeEnum *)copy=*(NativeEnum *)object;copy->access=access;CScope_AddObject(ns,*(HashNameNode **)((U8 *)copy+6),copy);return;}
    if(object->kind==4){
        if(!ns->theclass){fn_0045c480(0x27ed);return;}
        copy=galloc(32);
        *(Object *)copy=*(Object *)object;copy->access=access;((U8 *)copy)[3]=1;
        ((NativeMember *)copy)->owner=foundclass;((NativeMember *)copy)->original=object;
        CScope_AddObject(ns,*(HashNameNode **)((U8 *)copy+8),copy);return;
    }
    if(object->kind!=5){fn_0045c480(0x27d8);return;}
    objects=CScope_FindQualName(ns,((Object *)object)->name);
    if(ns->theclass){for(entry=objects;entry;entry=entry->next)if(entry->object->kind==5 && ((U8 *)entry->object)[2]!=6 && CScope_HidesObject((Object *)object,entry))return;}
    else {for(entry=objects;entry;entry=entry->next){if(entry->object->kind==5){other=unalias((Object *)entry->object);if(other==(Object *)object)return;}}}
    copy=galloc(96);*(NativeObject *)copy=*(NativeObject *)object;
    copy->access=access;((U8 *)copy)[2]=6;*(ObjBase **)((U8 *)copy+64)=object;
    *(TypeClass **)((U8 *)copy+68)=0;*(U32 *)((U8 *)copy+72)=0;
    if(!((Object *)copy)->nspace)CError_Internal(filename,4406);
    type=(TypeMemberFunc *)((Object *)copy)->type;
    if(type->base.kind==7 && (type->flags&0x10) && !type->is_static){
        if(!ns->theclass || !mostderived || (ns->theclass!=mostderived && !fn_0053f270(mostderived,ns->theclass)))fn_0045c480(0x27ed);
        *(TypeClass **)((U8 *)copy+68)=ns->theclass;
    }
    CScope_AddObject(ns,((Object *)copy)->name,copy);
}
void CScope_AddClassUsingDeclaration(TypeClass *cls,TypeClass *base,HashNameNode *name,U8 access) {
    ParseResult result;NameSpaceObjectList *entry;ObjBase *object;
    memclrw(&result,48);
    if(!CScope_FindClassMember(&result,base->nspace,name,0) || !validate_member(&result,cls)){fn_0045c480(0x2864,name->name);return;}
    if(result.objects){
        for(entry=result.objects;entry;entry=entry->next){object=entry->object;
            switch(object->kind){case 0:case 1:case 2:case 4:case 5:CScope_AddUsingObject(result.mostderived,result.foundclass,cls->nspace,object,result.name,access);}
        }
    }else if(result.object)CScope_AddUsingObject(result.mostderived,result.foundclass,cls->nspace,result.object,result.name,access);
    else fn_0045c480(0x2864,name->name);
}
extern void *fn_0053edb0(TypeClass *,...);
extern void fn_005dbf40(void *);
void CScope_ParseUsingDeclaration(NameSpace *ns,U8 access) {
    ParseResult result;NameSpace *saved;Type *type;ObjBase *object;NameSpaceObjectList *entry;U8 templ,is_typename=0;
    if(ns->theclass){
        templ=(ns->theclass->flags&0x100)!=0;
        if(tk==290){if(!templ)fn_0045c480(0x27d8);is_typename=1;tk=fn_00447b70();}
        if(!CScope_ParseMemberName(ns->theclass,&result,templ,0)){fn_0045c480(0x27d8);return;}
        type=result.type;
        if(type && type->kind==10 && ((U8 *)type)[6]==1){
            if(!templ)CError_Internal(filename,4505);
            if(is_typename){object=galloc(10);memclrw(object,10);object->kind=1;object->access=access;((ObjType *)object)->type=type;
                CScope_AddObject(ns,*(HashNameNode **)((U8 *)type+12),object);
            }else {object=galloc(96);memclrw(object,96);object->kind=5;object->access=access;((Object *)object)->type=type;
                ((U8 *)object)[2]=3;*(S16 *)((U8 *)object+24)=357;((Object *)object)->name=*(HashNameNode **)((U8 *)type+12);
                CScope_AddObject(ns,((Object *)object)->name,object);fn_005dbf40(fn_0053edb0(ns->theclass,type,access));}
            goto finish;
        }
        if(!result.no_parent){fn_0045c480(0x27d8);return;}
    }else {saved=cscope_current;cscope_current=ns;if(!fn_004e8320(&result)){cscope_current=saved;return;}cscope_current=saved;}
    if(result.object)CScope_AddUsingObject(result.mostderived,result.foundclass,ns,result.object,result.name,access);
    else if(result.objects){for(entry=result.objects;entry;entry=entry->next)CScope_AddUsingObject(result.mostderived,result.foundclass,ns,entry->object,result.name,access);}
    else fn_0045c480(0x27d8);
finish:tk=fn_00447b70();if(tk!=59)fn_0045baf0(0x278b);
}

static inline U8 scope_lookup_type(ParseResult *result,NameSpace *ns,HashNameNode *name,U8 tagonly) {
    LookupContext ctx;NameSpaceObjectList *objects;
    iterator_init(&ctx,ns,result);
    do {for(objects=CScope_NSIteratorFind(&ctx,name);objects;objects=objects->next){
        if(objects->object->kind==2 || (!tagonly && objects->object->kind==1)){
            result->nspace=ctx.scope?ctx.scope->ns:ctx.ns;return CScope_SetupParseNameResult(result,objects,name);
        }
    }}while(iterator_next(&ctx));
    result->name=name;return 1;
}
U8 CScope_ParseTypeName(ParseResult *result) {
    NameSpace *ns;HashNameNode *name;
    if(!option_0070f1a8){memclrw(result,48);if(tk!=-3){fn_0045c480(0x277b);return 0;}return scope_lookup_type(result,cscope_current,data_00710384,0);}
    if(tk!=386 && tk!=-3){fn_0045c480(0x277b);return 0;}
    if(CScope_ParseQualifiedNameSpace(result,0,0,0)){
        if(result->type)return 1;
        if(!result->nspace)CError_Internal(filename,3562);
        if(tk!=-3){fn_0045c480(0x277b);return 0;}
        ns=result->nspace;name=data_00710384;
        if(result->no_parent){
            if(ns->theclass)return CScope_FindClassMember(result,ns,name,2);
            return CScope_FindQualifiedType(result,ns,name);
        }
    }else {result->nspace=cscope_current;if(tk!=-3){fn_0045c480(0x277b);return 0;}ns=result->nspace;name=data_00710384;}
    return scope_lookup_type(result,ns,name,0);
}
U8 CScope_ParseElaborateName(ParseResult *result) {
    NameSpace *ns;HashNameNode *name;NameSpaceObjectList *objects;
    if(!option_0070f1a8){memclrw(result,48);if(tk!=-3){fn_0045c480(0x277b);return 0;}return scope_lookup_type(result,cscope_current,data_00710384,1);}
    if(tk!=386 && tk!=-3){fn_0045c480(0x277b);return 0;}
    if(CScope_ParseQualifiedNameSpace(result,0,0,0)){
        if(result->type)return 1;
        if(!result->nspace)CError_Internal(filename,3473);
        if(tk!=-3){fn_0045c480(0x277b);return 0;}
        ns=result->nspace;name=data_00710384;
        if(result->no_parent){
            if(ns->theclass)return CScope_FindClassMember(result,ns,name,1);
            /* Native inlined qualified-tag lookup deliberately uses mode 1. */
            if(ns->theclass){fn_00514b90(ns->theclass);return CScope_FindClassMember(result,ns,name,1);}
            objects=CScope_FindLookupName(ns,name,1);if(!objects)return 0;
            if(objects->object->kind!=2)CError_Internal(filename,2326);
            result->type=((ObjType *)objects->object)->type;return 1;
        }
    }else {result->nspace=cscope_current;if(tk!=-3){fn_0045c480(0x277b);return 0;}ns=result->nspace;name=data_00710384;}
    return scope_lookup_type(result,ns,name,0);
}
#pragma pack(push,2)
typedef struct ScopeAccess { struct ScopeAccess *next; TypeClass *mostderived,*foundclass; HashNameNode *name; U8 access,padding; } ScopeAccess;
#pragma pack(pop)
extern Type *fn_004ef2b0(TypeClass *);
extern Type *fn_004ef330(Type *);
extern U8 fn_004509a0(TypeClass *,U8);
extern Type *fn_0053e240(TypeClass *);
U8 parse_qualified_templdep_type(ParseResult *,Type *,U8,U8);
U8 CScope_ParseQualifiedNameSpace(ParseResult *result,NameSpace *ns,U8 flag1,U8 flag2) {
    U8 qualified=0,first=1;HashNameNode *name;S16 peek;LookupContext ctx;ScopeRec scope;NameSpaceObjectList *objects;ObjBase *object;Type *type;TypeClass *cls;ScopeAccess *access;void *context,*item;
    memclrw(result,48);
    for(;;){
        if(tk==386){ns=cscope_root;result->nspace=ns;qualified=1;result->no_parent=qualified;tk=fn_00447b70();}
        if(tk==346){if(!result->no_parent)fn_0045c480(0x2885);tk=fn_00447b70();if(tk!=-3){fn_0045c480(0x277b);return 0;}}
        if(tk!=-3)return ns!=0;
        name=data_00710384;peek=fn_00447a30();data_00710384=name;
        if(peek!=386 && peek!=60)return qualified;
        if(qualified && ns && !ns->theclass){ctx.ns=0;ctx.scope=&scope;ctx.result=result;scope.outer=0;scope.ns=0;scope.list=fn_004ea650(0,ns,name,0);}
        else iterator_init(&ctx,ns?ns:cscope_current,result);
        do {
            for(objects=CScope_NSIteratorFind(&ctx,name);objects;objects=objects->next){
                object=objects->object;
                if(object->kind==3){
                    if(!first && ns && ns->theclass)CError_Internal(filename,3237);
                    ns=(NameSpace *)((ObjType *)object)->type;result->nspace=ns;tk=fn_00447b70();
                    if(tk!=386){fn_0045c480(0x2851);return 0;}
                    qualified=1;result->no_parent=qualified;tk=fn_00447b70();goto again;
                }
                first=0;
                if(object->kind==2){
                    type=((ObjType *)object)->type;
                    if(type->kind!=6){if(peek==60){result->type=type;return 1;}fn_0045c480(0x2789);return 0;}
                    cls=(TypeClass *)type;goto class_template;
                }
                if(object->kind==1){
                    type=((ObjType *)object)->type;
                    if(type->kind==6){
                        cls=(TypeClass *)type;
                        if(peek==60){if(cls->flags&0x100)goto class_template;tk=fn_00447b70();if(tk!=60)CError_Internal(filename,3379);result->type=type;return 1;}
                        tk=fn_00447b70();if(tk!=386)CError_Internal(filename,3384);
                        if(!cls->base.size)fn_00514b90(cls);
                        if(result->mostderived && result->foundclass){
                            access=lalloc(18);access->next=(ScopeAccess *)result->foundtemplate;access->mostderived=result->mostderived;access->foundclass=result->foundclass;access->name=name;access->access=object->access;result->foundtemplate=(Type *)access;
                        }
                        ns=cls->nspace;result->nspace=ns;qualified=1;result->no_parent=qualified;tk=fn_00447b70();goto again;
                    }
                    if(type->kind==10){
                        if(((U8 *)type)[6]==11){type=fn_004ef330(type);if(type->kind!=10){result->type=type;return 1;}peek=fn_00447a30();if(peek!=386){result->type=type;return 1;}}
                        if(peek==386)return parse_qualified_templdep_type(result,type,flag1,flag2);
                    }
                    if(peek==60){result->type=type;return 1;}
                    fn_0045c480(0x2789);return 0;
                }
                if(peek==60)return ns!=0;
            }
        }while(iterator_next(&ctx));
        fn_0045c480(0x279c,name->name);return 0;
class_template:
        if(peek==60){
            if(cls->flags&0x800)cls=(TypeClass *)fn_0053ecc0(cls);
            else if(!(cls->flags&0x100)){result->type=(Type *)cls;return 1;}
        }
        tk=fn_00447b70();
        if(tk==60){
            if(!(cls->flags&0x100))CError_Internal(filename,3279);
            type=fn_004ef2b0(cls);
            if(type->kind==10){if(fn_00447a30()==386)return parse_qualified_templdep_type(result,type,flag1,flag2);result->type=type;return 1;}
            if(type->kind!=6)return 0;
            cls=(TypeClass *)type;ns=cls->nspace;result->nspace=ns;
            if(fn_00447a30()!=386){result->type=type;return 1;}
            tk=fn_00447b70();fn_00514b90(cls);
        }else {
            if(tk!=386)CError_Internal(filename,3302);
            if((cls->flags&0x100) && !fn_004509a0(cls,1))return 0;
            ns=cls->nspace;result->nspace=ns;fn_00514b90(cls);
        }
        qualified=1;result->no_parent=qualified;tk=fn_00447b70();
        if((cls->flags&0x100) && tk==-3){
            context=fn_0053edb0(cls);item=*(void **)((U8 *)context+78);
            for(;item;item=*(void **)item){if(((U8 *)item)[26]==3){
                if(!CScope_FindName(cls->nspace,data_00710384)){fn_00448fa0();fn_00448fa0();return parse_qualified_templdep_type(result,fn_0053e240(cls),flag1,flag2);}break;
            }}
        }
again:;
    }
}

extern void fn_005a85c0(void *,TypeClass *);
extern Object *fn_005a8450(void *);
extern Object *fn_005dc920(Object *,Type *,U32);
U8 parse_name_in_namespace(ParseResult *result,NameSpace *ns) {
    U8 destructor=0,error;HashNameNode *name;NameSpaceObjectList *objects,*node;TypeClass *cls;ScopeRec scope;
    U32 conversion_quals,iterator[8];Type *conversion_type=0;Object *candidate,*specialized;
    for(;;){
        switch(tk){
        case 346:
            tk=fn_00447b70();if(tk!=-3){fn_0045c480(0x277b);return 0;}
        case -3:
            name=data_00710384;
            if(fn_00447a30()==386){
                tk=fn_00447b70();
                if(ns->theclass){if(CScope_FindClassMember(result,ns,name,3)){ns=result->nspace;result->nspace=0;}else ns=0;}
                else {error=0;objects=CScope_FindLookupName(ns,name,3);ns=objects?CScope_ExtractNameSpace(objects,&error):0;}
                if(!ns)return 0;
                result->no_parent=1;tk=fn_00447b70();continue;
            }
            break;
        case 342:
            if(!fn_00455f30(0,1,1,&conversion_type,&conversion_quals))return 0;
            fn_00448fa0();name=data_00710384;break;
        case 126:
            if(!CScope_CheckDtorName(ns->theclass,&destructor))return 0;
            name=destructor_name;destructor=1;break;
        default:fn_0045c480(0x277b);return 0;
        }
        if(ns->theclass){fn_00514b90(ns->theclass);if(CScope_FindClassMember(result,ns,name,0)){objects=result->objects;result->objects=0;}else objects=0;}
        else {scope.outer=0;scope.ns=0;scope.list=fn_004ea650(0,ns,name,0);objects=fn_004e99e0(&scope,name,&result->nspace);}
        if(!objects || !CScope_SetupParseNameResult(result,objects,name)){
            if(destructor){result->qualified=1;return 1;}
            if(conversion_type && ns->theclass){
                fn_005a85c0(iterator,ns->theclass);
                while((candidate=fn_005a8450(iterator))!=0){
                    if(((TypeMemberFunc *)candidate->type)->flags&0x100000){
                        specialized=fn_005dc920(candidate,conversion_type,conversion_quals);
                        if(specialized){
                            node=galloc(8);node->next=0;node->object=(ObjBase *)specialized;result->mostderived=ns->theclass;
                            if(!specialized->nspace || !specialized->nspace->theclass)CError_Internal(filename,2731);
                            result->foundclass=specialized->nspace->theclass;
                            if(CScope_SetupParseNameResult(result,node,name))return 1;
                        }
                    }
                }
            }
            if(ns->theclass && !(ns->theclass->flags&2))fn_0045c480(0x2798,ns->theclass,0);
            else fn_0045c480(0x279c,name->name);
            return 0;
        }
        if(result->type && result->type->kind==6 && fn_00447a30()==60){
            cls=(TypeClass *)result->type;
            if(cls->flags&0x800)cls=(TypeClass *)fn_0053ecc0(cls);
            else if(!(cls->flags&0x100))return 1;
            tk=fn_00447b70();result->type=fn_004ef2b0(cls);
            if(result->type->kind==6 && fn_00447a30()==386){fn_00447b70();tk=fn_00447b70();result->no_parent=1;ns=((TypeClass *)result->type)->nspace;result->type=0;result->object=0;continue;}
        }
        return 1;
    }
}
#pragma pack(push,2)
typedef struct NativeTemplDep { Type base; U8 subtype,padding; Type *qualifier; void *name_or_args; } NativeTemplDep;
#pragma pack(pop)
extern void fn_00449090(U32 *);
extern void fn_00449010(U32 *);
extern NativeTemplDep *fn_00544400(U8);
extern void *fn_004efaa0(void *,U8);
extern void fn_0045c440(S16,U8);
U8 parse_qualified_templdep_type(ParseResult *result,Type *qualifier,U8 allow_operator,U8 no_template_args) {
    U32 saved;S16 token,op;NativeTemplDep *node,*inner;
    fn_00449090(&saved);if(fn_00447b70()!=386)CError_Internal(filename,2497);result->no_parent=1;
    for(;;){
        token=fn_00447b70();
        if(token==342){
            if(!fn_00455f30(&op,1,1,0,0))return 0;
            if(!allow_operator){if(op)fn_0045c480(0x2789);else result->unknown2e=1;}
            node=fn_00544400(1);node->qualifier=qualifier;node->name_or_args=data_00710384;
            if(no_template_args){fn_00448fa0();fn_00448fa0();}else {fn_00449010(&saved);fn_00447b70();}
            tk=fn_00447b70();result->type=(Type *)node;return 1;
        }
        if(token==346){
            if(fn_00447b70()!=-3){fn_0045c480(0x277b);return 0;}
            fn_00449090(&saved);inner=fn_00544400(1);inner->qualifier=qualifier;inner->name_or_args=data_00710384;
            token=fn_00447b70();if(token!=60){fn_0045c440(token,1);return 0;}
            tk=token;node=fn_00544400(4);node->qualifier=(Type *)inner;node->name_or_args=fn_004efaa0(0,1);
            fn_00449090(&saved);token=fn_00447b70();
            if(token==386){qualifier=(Type *)node;continue;}
            fn_00449010(&saved);result->type=(Type *)node;return 1;
        }
        if(token!=-3){fn_00449010(&saved);result->type=qualifier;return 1;}
        node=fn_00544400(1);node->qualifier=qualifier;node->name_or_args=data_00710384;
        tk=token;fn_00449090(&saved);token=fn_00447b70();data_00710384=node->name_or_args;
        if(token==386){qualifier=(Type *)node;continue;}
        if(token==60 && !no_template_args){tk=token;inner=node;node=fn_00544400(4);node->qualifier=(Type *)inner;node->name_or_args=fn_004efaa0(0,1);
            fn_00449090(&saved);token=fn_00447b70();if(token==386){qualifier=(Type *)node;continue;}}
        fn_00449010(&saved);result->type=(Type *)node;return 1;
    }
}

extern HashNameNode *constructor_name;
extern void fn_0045d870(NameSpace *,HashNameNode *,U8);
static inline NameSpaceObjectList *scope_qualified_objects(ParseResult *result,NameSpace *ns,HashNameNode *name) {
    NameSpaceObjectList *objects;ScopeRec scope;
    if(ns->theclass){fn_00514b90(ns->theclass);if(!CScope_FindClassMember(result,ns,name,0))return 0;objects=result->objects;result->objects=0;return objects;}
    scope.outer=0;scope.ns=0;scope.list=fn_004ea650(0,ns,name,0);return fn_004e99e0(&scope,name,&result->nspace);
}
U8 CScope_ParseDeclName(ParseResult *result,NameSpace *ns) {
    LookupContext ctx;NameSpaceObjectList *objects;HashNameNode *name;CScopeSave saved;U8 ok;S16 op;
    if(option_0070f1a8){
        if(tk!=386 && tk!=-3){fn_0045c480(0x277b);return 0;}
        if(CScope_ParseQualifiedNameSpace(result,ns,0,0)){
            if(result->type)return 1;
            ns=result->nspace;if(!ns)CError_Internal(filename,3036);
            switch(tk){
            case 342:
                saved.theclass=cscope_currentclass;saved.function=cscope_currentfunc;saved.member=cscope_is_member_func;saved.nspace=cscope_current;
                cscope_current=ns;cscope_currentclass=ns->theclass;cscope_currentfunc=0;cscope_is_member_func=0;
                ok=fn_00455f30(&op,1,1,0,0);
                cscope_current=saved.nspace;cscope_currentclass=saved.theclass;cscope_currentfunc=saved.function;cscope_is_member_func=saved.member;
                if(!ok)return 0;
                if(op)fn_0045c480(0x2789);result->unknown2e=1;return 1;
            case -3:
                name=data_00710384;if(ns->theclass && ns->theclass->name==name)name=constructor_name;break;
            case 126:
                if(!ns->theclass){fn_0045c480(0x2789);return 0;}
                tk=fn_00447b70();if(tk!=-3){fn_0045c480(0x277b);return 0;}
                if(ns->theclass->name!=data_00710384)fn_0045c480(0x2789);name=destructor_name;break;
            default:fn_0045c480(0x277b);return 0;
            }
            if(result->no_parent){
                objects=scope_qualified_objects(result,ns,name);
                if(objects)return CScope_SetupParseNameResult(result,objects,name);
                fn_0045d870(result->nspace,name,0);return 0;
            }
            iterator_init(&ctx,ns,result);
            do {objects=CScope_NSIteratorFind(&ctx,name);if(objects){result->nspace=ctx.scope?ctx.scope->ns:ctx.ns;return CScope_SetupParseNameResult(result,objects,name);}}while(iterator_next(&ctx));
            fn_0045c480(0x279c,name->name);return 0;
        }
    }
    if(!ns)ns=cscope_current;
    if(tk!=-3){fn_0045c480(0x277b);return 0;}
    memclrw(result,48);name=data_00710384;iterator_init(&ctx,ns,result);
    do {objects=CScope_NSIteratorFind(&ctx,name);if(objects && (option_0070f1a8 || objects->object->kind!=2)){result->nspace=ctx.scope?ctx.scope->ns:ctx.ns;return CScope_SetupParseNameResult(result,objects,name);}}while(iterator_next(&ctx));
    result->nspace=cscope_current;result->name=name;return 0;
}
#pragma pack(push,2)
typedef struct ScopeDependentName { struct ScopeDependentName *next; void *value; U32 quals; U8 kind,padding; } ScopeDependentName;
#pragma pack(pop)
extern U8 fn_0053d780(Type *);
extern void *fn_00524320(S16);
U8 CScope_ParseExprName(ParseResult *result) {
    LookupContext ctx;NameSpaceObjectList *objects;HashNameNode *name;NameSpace *ns,*saved;Type *conversion_type;U32 conversion_quals;U8 implicit;ScopeDependentName *dependent;void *expression;
    if(!option_0070f1a8){
        memclrw(result,48);if(tk!=-3){fn_0045c480(0x277b);return 0;}
        name=data_00710384;iterator_init(&ctx,cscope_current,result);
        do {objects=CScope_NSIteratorFind(&ctx,name);if(objects && objects->object->kind!=2){result->nspace=ctx.scope?ctx.scope->ns:ctx.ns;return CScope_SetupParseNameResult(result,objects,name);}}while(iterator_next(&ctx));
        result->nspace=cscope_current;result->name=name;return 1;
    }
    if((tk==386 || tk==-3) && CScope_ParseQualifiedNameSpace(result,0,1,1)){
        if(result->type)return 1;
        if(!result->nspace)CError_Internal(filename,2828);
    }else {memclrw(result,48);result->nspace=cscope_current;}
    switch(tk){
    case 346:
        if(!result->no_parent)fn_0045c480(0x2885);tk=fn_00447b70();if(tk!=-3){fn_0045c480(0x277b);return 0;}
    case -3:name=data_00710384;break;
    case 342:
        conversion_type=0;conversion_quals=0;
        saved=cscope_current;cscope_current=result->nspace;
        if(!fn_00455f30(0,1,1,&conversion_type,&conversion_quals)){cscope_current=saved;return 0;}
        cscope_current=saved;
        if(conversion_type && fn_0053d780(conversion_type)){
            dependent=lalloc(14);dependent->next=lalloc(14);dependent->kind=3;dependent->value=result->nspace;
            dependent->next->next=0;dependent->next->kind=1;dependent->next->value=conversion_type;dependent->next->quals=conversion_quals;
            expression=fn_00524320(27);*(ScopeDependentName **)((U8 *)expression+16)=dependent;result->basePath=(BaseClass *)expression;return 1;
        }
        name=data_00710384;fn_00448fa0();break;
    case 126:
        if(!CScope_CheckDtorName(result->nspace->theclass,&implicit))return 0;
        if(implicit){result->qualified=1;return 1;}name=destructor_name;break;
    default:fn_0045c480(0x277b);return 0;
    }
    ns=result->nspace;
    if(result->no_parent){
        objects=scope_qualified_objects(result,ns,name);
        if(objects)return CScope_SetupParseNameResult(result,objects,name);
        fn_0045c480(0x279c,fn_0045d9e0(result->nspace,name));return 0;
    }
    iterator_init(&ctx,ns,result);
    do {objects=CScope_NSIteratorFind(&ctx,name);if(objects){result->nspace=ctx.scope?ctx.scope->ns:ctx.ns;return CScope_SetupParseNameResult(result,objects,name);}}while(iterator_next(&ctx));
    if(result->no_parent){fn_0045c480(0x279c,name->name);return 0;}
    result->nspace=cscope_current;result->name=name;return 1;
}
