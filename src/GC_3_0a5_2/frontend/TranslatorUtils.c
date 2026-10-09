#include <string.h>
/* Native TranslatorUtils.c; private packed IR and label-list views. */
#include "compiler/common.h"
#include <stddef.h>
#pragma pack(push,2)
typedef struct TranslatorType { UInt8 kind,pad; SInt32 size; } TranslatorType;
typedef struct TranslatorReference { TranslatorType base; TranslatorType *target; UInt8 flag1,flag2; } TranslatorReference;
typedef struct TranslatorNode { UInt8 kind,unknown01[11]; UInt32 flags; void *value; } TranslatorNode;
typedef struct TranslatorStatement { struct TranslatorStatement *next; UInt8 kind,unknown05[5]; TranslatorNode *expression; void *label; } TranslatorStatement;
typedef struct TranslatorLabel { struct TranslatorLabel *next; void *statement,*unknown08; UInt8 *name; } TranslatorLabel;
typedef struct TranslatorRecord { struct TranslatorRecord *next; void *label; UInt32 unknown08[4]; } TranslatorRecord;
typedef struct TranslatorPair { struct TranslatorPair *next; TranslatorNode *expression; } TranslatorPair;
typedef struct TranslatorObject { UInt8 kind,unknown01,storage,unknown03[9]; void *name; UInt8 unknown10[48]; void *context; } TranslatorObject;
#pragma pack(pop)
typedef char TranslatorTypeSize[(sizeof(TranslatorType)==6)?1:-1];
typedef char TranslatorRecordSize[(sizeof(TranslatorRecord)==24)?1:-1];
typedef char TranslatorStatementExpression[(offsetof(TranslatorStatement,expression)==10)?1:-1];
typedef char TranslatorStatementLabel[(offsetof(TranslatorStatement,label)==14)?1:-1];
typedef char TranslatorObjectContext[(offsetof(TranslatorObject,context)==64)?1:-1];
static char translatorFilename[]="TranslatorUtils.c";
TranslatorRecord *translatorLabels;
SInt32 translatorLabelCount;
extern TranslatorLabel *translatorSourceLabels;
extern void *translatorCurrentContext;
extern UInt8 translatorDirectTargets;
extern void *(*translatorAllocate)(UInt32);
extern void (*translatorFree)(void *);
extern void CError_Internal(const char *,SInt32);
extern UInt8 fn_00454260(TranslatorType *),fn_00455840(void *,void *);
extern SInt16 fn_00454c20(TranslatorType *,TranslatorType *);
extern void fn_004d9030(void *),fn_004d9080(void *),fn_004d90d0(void *);
extern void fn_004d9050(void *),fn_004d90a0(void *),fn_004d90e0(void *);
extern TranslatorNode *fn_0055bf70(TranslatorNode *,TranslatorNode *(*)(TranslatorNode *));
extern void fn_004a6c00(void *,TranslatorNode *,TranslatorPair **),fn_004c5330(void *);
TranslatorNode *fn_005ea170(TranslatorNode *);

void fn_005e9f60(void *value,TranslatorType *type)
{
    if(fn_00454260(type)){
        switch(type->size){
        case 1:fn_004d9030(value);break;
        case 2:fn_004d9080(value);break;
        case 4:fn_004d90d0(value);break;
        case 8:break;
        }
    }else{
        switch(type->size){
        case 1:fn_004d9050(value);break;
        case 2:fn_004d90a0(value);break;
        case 4:fn_004d90e0(value);break;
        case 8:break;
        }
    }
}

TranslatorType *fn_005e9fd0(TranslatorType *type)
{
    return type;
}

UInt8 fn_005e9fe0(TranslatorType *left,TranslatorType *right)
{
    TranslatorReference *a=(TranslatorReference *)left,*b=(TranslatorReference *)right;
    if(left->kind!=8){
        if(left->kind==12&&right->kind==12)return 1;
        return fn_00454c20(left,right)!=0;
    }
    if(right->kind==8&&a->target==b->target&&a->flag1==b->flag1&&a->flag2==b->flag2)return 1;
    return 0;
}
void fn_005ea050(void)
{
    TranslatorRecord *record,*next;
    for(record=translatorLabels;record;record=next){
        next=record->next;
        translatorFree(record);
    }
    translatorLabels=NULL;
}

void fn_005ea080(TranslatorStatement *statement)
{
    TranslatorNode *expression;
    TranslatorLabel *label;
    TranslatorRecord *record;
    translatorLabelCount=0;
    if(translatorLabels)CError_Internal(translatorFilename,455);
    for(;statement;statement=statement->next){
        switch(statement->kind){
        case 15:
            expression=statement->expression;
            if(expression&&expression->kind==4&&expression->value&&((TranslatorNode *)expression->value)->kind!=59){
                for(label=translatorSourceLabels;label;label=label->next){
                    if(label->statement&&label->name[10]!='@'){
                        record=translatorAllocate(24);
                        memset(record,0,24);
                        record->label=label;
                        record->next=translatorLabels;
                        ++translatorLabelCount;
                        translatorLabels=record;
                    }
                }
            }
            fn_0055bf70(statement->expression,fn_005ea170);
            break;
        case 4:case 5:case 6:case 7:case 12:case 13:case 14:
            fn_0055bf70(statement->expression,fn_005ea170);break;
        case 8:
            if(statement->expression)fn_0055bf70(statement->expression,fn_005ea170);
            break;
        }
    }
}

TranslatorNode *fn_005ea170(TranslatorNode *expression)
{
    TranslatorRecord *record;
    TranslatorLabel *label;
    TranslatorObject *object;
    if(expression->kind==62&&expression->value){
        record=translatorAllocate(24);
        memset(record,0,24);
        record->label=expression->value;
        record->next=translatorLabels;
        ++translatorLabelCount;
        translatorLabels=record;
    }else if(expression->kind==59&&(object=expression->value)->storage==8){
        for(label=translatorSourceLabels;label;label=label->next){
            if(fn_00455840(object->context,translatorCurrentContext)&&label->name==object->name){
                record=translatorAllocate(24);
                memset(record,0,24);
                record->label=label;
                record->next=translatorLabels;
                ++translatorLabelCount;
                translatorLabels=record;
            }
        }
        /* The native walk reaches this invariant failure even after a match. */
        CError_Internal(translatorFilename,442);
    }
    return expression;
}

void fn_005ea250(TranslatorRecord *record)
{
    TranslatorRecord *next;
    if(record!=translatorLabels){
        for(;record;record=next){
            next=record->next;
            translatorFree(record);
        }
    }
}

TranslatorRecord *fn_005ea280(TranslatorStatement *statement,SInt32 *count)
{
    TranslatorRecord *result,*record;
    TranslatorPair *list,*item,*next;
    TranslatorNode *expression;
    UInt8 fallback=0;
    if(statement->kind==3){
        result=translatorAllocate(24);
        memset(result,0,24);
        result->label=statement->label;
        *count=1;
    }else if(statement->kind==15){
        expression=statement->expression;
        if(!translatorDirectTargets||!expression->flags||!translatorCurrentContext){
            fallback=1;
        }else{
            list=NULL;
            fn_004a6c00(translatorCurrentContext,expression,&list);
            if(!list){
                fallback=1;
            }else{
                for(item=list;item;item=item->next){
                    if(!item->expression||item->expression->kind!=62){fallback=1;break;}
                }
                if(!fallback){
                    *count=0;
                    result=NULL;
                    for(item=list;item;item=item->next){
                        if(!item->expression->value)CError_Internal(translatorFilename,356);
                        record=translatorAllocate(24);
                        memset(record,0,24);
                        record->label=item->expression->value;
                        record->next=result;
                        ++*count;
                        result=record;
                    }
                }
                for(;list;list=next){next=list->next;fn_004c5330(list);}
            }
        }
        if(fallback){*count=translatorLabelCount;result=translatorLabels;}
    }else{
        CError_Internal(translatorFilename,387);
    }
    return result;
}
