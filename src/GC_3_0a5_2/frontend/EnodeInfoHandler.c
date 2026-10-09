/* GC 3.0a5.2 expression-info records. Layouts follow the native x86 accesses. */
#pragma pack(push,2)
typedef struct InfoScope InfoScope;
typedef struct InfoVariable InfoVariable;
typedef struct InfoLocation {
    struct InfoLocation *next;
    void *file;
    unsigned long offset;
} InfoLocation;
struct InfoScope {
    InfoScope *next, *child, *parent;
    InfoVariable *variables;
    InfoLocation *begin, *end;
};
struct InfoVariable {
    InfoVariable *next;
    void *identity;
    InfoScope *scope;
};
typedef struct InfoObject {
    unsigned char prefix[12];
    void *identity;
    unsigned char middle[44];
    InfoScope *scope;
} InfoObject;
typedef struct InfoExpr {
    unsigned char kind, prefix[15];
    union { struct InfoExpr *expr; InfoObject *object; } data;
    unsigned char infoKind;
} InfoExpr;
typedef struct InfoStatement {
    unsigned char prefix[26];
    void *file;
    unsigned long offset;
} InfoStatement;
#pragma pack(pop)
typedef char InfoScopeSize[(sizeof(InfoScope)==24)?1:-1];
typedef char InfoVariableSize[(sizeof(InfoVariable)==12)?1:-1];
typedef char InfoLocationSize[(sizeof(InfoLocation)==12)?1:-1];
extern void *galloc(unsigned long);
extern void memclrw(void *,unsigned long);
extern void CError_Internal(const char *,int);
InfoScope *enodeInfoScopes, *enodeInfoCurrentScope;
InfoVariable *enodeInfoVariables;
static char enodeInfoFilename[]="EnodeInfoHandler.c";
void fn_00593070(InfoExpr *);
void fn_00593120(InfoStatement *);

void HandleENodeInfo(InfoExpr *expr,InfoStatement *statement)
{
    if(expr->kind!=66)CError_Internal(enodeInfoFilename,165);
    switch(expr->infoKind){
    case 0:
        CError_Internal(enodeInfoFilename,170);
        break;
    case 3:
        fn_00593120(statement);
        break;
    case 4:
        if(enodeInfoCurrentScope){
            enodeInfoCurrentScope->end=galloc(12);
            enodeInfoCurrentScope->end->next=0;
            enodeInfoCurrentScope->end->file=statement->file;
            enodeInfoCurrentScope->end->offset=statement->offset;
            enodeInfoCurrentScope=enodeInfoCurrentScope->parent;
        }
        break;
    case 5:
        fn_00593070(expr->data.expr);
        break;
    case 1:case 2:case 6:
        break;
    }
}

void fn_00593050(void)
{
    enodeInfoScopes=0;
    enodeInfoVariables=0;
    enodeInfoCurrentScope=0;
}

void fn_00593070(InfoExpr *expr)
{
    InfoVariable *variable;
    int count=0;
    if(!expr)return;
    if(expr->kind!=59){
        if(expr->kind!=4)return;
        expr=expr->data.expr;
        while(expr->kind!=59){
            if(++count>50)return;
            expr=expr->data.expr;
        }
    }
    variable=galloc(12);
    memclrw(variable,12);
    if(!enodeInfoCurrentScope){
        variable->scope=0;
        variable->next=enodeInfoVariables;
        enodeInfoVariables=variable;
    }else{
        variable->scope=enodeInfoCurrentScope;
        variable->next=enodeInfoCurrentScope->variables;
        enodeInfoCurrentScope->variables=variable;
    }
    variable->identity=expr->data.object->identity;
    expr->data.object->scope=enodeInfoCurrentScope;
}

void fn_00593120(InfoStatement *statement)
{
    InfoScope *scope, *newScope;
    if(!enodeInfoScopes){
        newScope=galloc(24);
        memclrw(newScope,24);
        enodeInfoScopes=enodeInfoCurrentScope=newScope;
    }else if(!enodeInfoCurrentScope){
        for(scope=enodeInfoScopes;scope->next;scope=scope->next){}
        newScope=galloc(24);
        memclrw(newScope,24);
        scope->next=newScope;
        scope->next->parent=scope->parent;
        enodeInfoCurrentScope=scope->next;
    }else if(!enodeInfoCurrentScope->child){
        newScope=galloc(24);
        memclrw(newScope,24);
        enodeInfoCurrentScope->child=newScope;
        enodeInfoCurrentScope->child->parent=enodeInfoCurrentScope;
        enodeInfoCurrentScope=enodeInfoCurrentScope->child;
    }else{
        for(scope=enodeInfoCurrentScope->child;scope->next;scope=scope->next){}
        newScope=galloc(24);
        memclrw(newScope,24);
        scope->next=newScope;
        scope->next->parent=scope->parent;
        enodeInfoCurrentScope=scope->next;
    }
    enodeInfoCurrentScope->begin=galloc(12);
    enodeInfoCurrentScope->begin->next=0;
    enodeInfoCurrentScope->begin->file=statement->file;
    enodeInfoCurrentScope->begin->offset=statement->offset;
}
