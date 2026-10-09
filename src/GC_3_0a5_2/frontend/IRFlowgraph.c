#include "compiler/common.h"
#include <stddef.h>
#include <string.h>
/* Native IRFlowgraph.c. The original x86 layouts differ from IROLinear/IRONode. */
typedef struct FlowBlock FlowBlock;
typedef struct FlowStatement FlowStatement;
typedef struct FlowLabel FlowLabel;
typedef struct FlowAction FlowAction;
#pragma pack(push,2)
struct FlowBlock {
    SInt32 index, successorCount;
    SInt32 *successors;
    SInt32 predecessorCount;
    SInt32 *predecessors;
    FlowStatement *first, *last;
    UInt32 reserved;
    FlowBlock *next;
};
struct FlowLabel {
    FlowLabel *next;
    UInt8 unknown04[12];
    FlowBlock *block;
    UInt8 unknown20[8];
};
struct FlowStatement {
    FlowStatement *next;
    UInt8 kind, unknown05;
    UInt16 info, flags;
    void *expression;
    void *label;
    FlowAction *actions;
    UInt8 unknown22[12];
};
struct FlowAction {
    FlowAction *next;
    UInt8 unknown04[8];
    FlowLabel *label;
    UInt8 unknown16[12];
    UInt8 kind, unknown29;
};
typedef struct FlowCase { struct FlowCase *next; FlowLabel *label; } FlowCase;
typedef struct FlowSwitch { FlowCase *cases; UInt32 unknown04; FlowLabel *defaultLabel; } FlowSwitch;
typedef struct FlowLabelRecord { struct FlowLabelRecord *next; FlowLabel *label; UInt32 unknown08[4]; } FlowLabelRecord;
typedef struct FlowAsmEffects {
    UInt8 unknown00[4];
    UInt8 mayThrow, noFallthrough;
    UInt8 unknown06[8];
    SInt32 targetCount;
    UInt8 unknown18[224];
    FlowLabel *targets[16];
} FlowAsmEffects;
#pragma pack(pop)
typedef char FlowBlockSize[sizeof(FlowBlock)==36?1:-1];
typedef char FlowStatementSize[sizeof(FlowStatement)==34?1:-1];
typedef char FlowLabelSize[sizeof(FlowLabel)==28?1:-1];
typedef char FlowActionSize[sizeof(FlowAction)==30?1:-1];
typedef char FlowEffectsSize[sizeof(FlowAsmEffects)==306?1:-1];
typedef char FlowEffectsCount[offsetof(FlowAsmEffects,targetCount)==14?1:-1];
typedef char FlowEffectsTargets[offsetof(FlowAsmEffects,targets)==242?1:-1];
typedef char FlowBlockNext[offsetof(FlowBlock,next)==32?1:-1];
typedef char FlowLabelBlock[offsetof(FlowLabel,block)==16?1:-1];
typedef char FlowStatementExpression[offsetof(FlowStatement,expression)==10?1:-1];
typedef char FlowStatementLabel[offsetof(FlowStatement,label)==14?1:-1];
typedef char FlowStatementActions[offsetof(FlowStatement,actions)==18?1:-1];
typedef char FlowActionLabel[offsetof(FlowAction,label)==12?1:-1];
typedef char FlowActionKind[offsetof(FlowAction,kind)==28?1:-1];
static char flowFilename[]="IRFlowgraph.c";
SInt32 flowBlockCount;
FlowBlock *flowHead, *flowTail;
FlowBlock **flowByIndex;
extern FlowLabel *flowLabels;
extern void *(*flowAllocate)(UInt32);
extern void (*flowFree)(void *);
extern void (*flowAsmCallback)(FlowStatement *,FlowAsmEffects *);
extern UInt8 fn_005ea520(FlowStatement *),fn_005ea570(FlowStatement *);
extern FlowLabelRecord *fn_005ea280(FlowStatement *,SInt32 *);
extern void fn_005ea250(FlowLabelRecord *);
extern SInt32 CError_Internal(const char *,SInt32);
void fn_005ec910(void);
void fn_005ecf00(FlowBlock *,FlowStatement *,SInt32);
void fn_005ecfe0(FlowBlock *,SInt32);
void fn_005ed0e0(FlowStatement *);

/* Same list/edge architecture as 1.2.5 IroFlowgraph; native edges are unique. */
static void AddNext(FlowBlock *block,FlowBlock *target)
{
    SInt32 i;
    for(i=0;i<block->successorCount;i++)
        if(target->index==block->successors[i])return;
    block->successors[block->successorCount++]=target->index;
    target->predecessorCount++;
}
static void AddRef(FlowBlock *block,FlowBlock *target)
{
    if(target)AddNext(block,target);
    else CError_Internal(flowFilename,222);
}

/* Build statement blocks, publish the index array, then rebuild their edges. */
void fn_005ec6b0(FlowStatement *source)
{
    FlowStatement *statement;
    FlowBlock *block,*next;
    FlowLabel *label;
    FlowAction *action;
    FlowAsmEffects effects;
    SInt32 actionCount;
    FlowStatement *following;
    UInt8 done;
    if(flowHead){
        for(block=flowHead;block;block=next){
            next=block->next;
            flowBlockCount--;
            if(block->successors)flowFree(block->successors);
            if(block->predecessors)flowFree(block->predecessors);
            flowFree(block);
        }
    }
    flowBlockCount=0;
    flowHead=NULL;
    flowTail=NULL;
    for(label=flowLabels;label;label=label->next)label->block=NULL;
    statement=source;
    while(statement){
        fn_005ed0e0(statement);
        if(statement->kind==2)((FlowLabel *)statement->label)->block=flowTail;
        done=0;
        while(!done&&(following=statement->next)!=NULL&&following->kind!=11&&following->kind!=2){
            if(fn_005ea570(statement)){
                actionCount=0;
                for(action=statement->actions;action;action=action->next)
                    if(action->kind==13||action->kind==15)actionCount++;
                if(actionCount)done=1;
            }
            switch(statement->kind){
            case 3:case 5:case 6:case 7:case 8:case 10:case 11:case 15:
                done=1;break;
            case 16:
                if(flowAsmCallback&&statement){
                    flowAsmCallback(statement,&effects);
                    if(effects.targetCount)done=1;
                }
                break;
            }
            if(!done)statement=statement->next;
        }
        flowTail->last=statement;
        statement=statement->next;
    }
    if(flowByIndex)flowFree(flowByIndex);
    flowByIndex=NULL;
    flowByIndex=flowAllocate(flowBlockCount*4);
    memset(flowByIndex,0,flowBlockCount*4);
    for(block=flowHead;block;block=block->next)flowByIndex[block->index]=block;
    fn_005ec910();
}

/* The separately allocated index array remains live across graph cleanup. */
void fn_005ec8a0(void)
{
    FlowBlock *block,*next;
    if(flowHead){
        for(block=flowHead;block;block=next){
            next=block->next;
            flowBlockCount--;
            if(block->successors)flowFree(block->successors);
            if(block->predecessors)flowFree(block->predecessors);
            flowFree(block);
        }
    }
    flowBlockCount=0;
    flowHead=NULL;
    flowTail=NULL;
}

/* Rebuild all unique successor edges, count predecessors, then materialize them. */
void fn_005ec910(void)
{
    FlowBlock *block,*target;
    FlowLabel *label;
    FlowStatement *statement;
    FlowAction *action;
    FlowLabelRecord *list,*entry;
    FlowAsmEffects effects;
    SInt32 actionCount,count,i;
    for(label=flowLabels;label;label=label->next)label->block=NULL;
    for(block=flowHead;block;block=block->next){
        block->successorCount=0;
        block->predecessorCount=0;
        statement=block->first;
        if(statement&&statement->kind==2)((FlowLabel *)statement->label)->block=block;
    }
    for(block=flowHead;block;block=block->next){
        if(!block->first){
            if(block->next){
                block->successors=flowAllocate(4);
                AddNext(block,block->next);
            }
        }else{
            statement=block->last;
            actionCount=0;
            if(fn_005ea520(statement)){
                actionCount=0;
                for(action=statement->actions;action;action=action->next)
                    if(action->kind==13||action->kind==15)actionCount++;
            }
            switch(statement->kind){
            case 3:
                block->successors=flowAllocate((actionCount+1)*4);
                AddRef(block,((FlowLabel *)statement->label)->block);
                break;
            case 5:
                fn_005ecfe0(block,actionCount);break;
            case 6:case 7:
                block->successors=flowAllocate((actionCount+2)*4);
                AddNext(block,block->next);
                AddRef(block,((FlowLabel *)statement->label)->block);
                break;
            case 15:
                list=fn_005ea280(statement,&count);
                if(!list||count<1)CError_Internal(flowFilename,395);
                block->successors=flowAllocate((count+actionCount)*4);
                for(entry=list;entry;entry=entry->next){
                    AddRef(block,entry->label->block);
                    count--;
                }
                if(count)CError_Internal(flowFilename,409);
                fn_005ea250(list);
                break;
            case 16:
                if(flowAsmCallback){
                    flowAsmCallback(statement,&effects);
                    count=(effects.noFallthrough==0)+effects.targetCount;
                    block->successors=flowAllocate((count+actionCount)*4);
                    if(!effects.noFallthrough)AddNext(block,block->next);
                    for(i=0;i<effects.targetCount;i++)AddRef(block,effects.targets[i]->block);
                    break;
                }
                /* Native missing-callback path uses the ordinary fallthrough. */
            default:
                if(block->next){
                    block->successors=flowAllocate((actionCount+1)*4);
                    AddNext(block,block->next);
                }else if(actionCount){
                    block->successors=flowAllocate(actionCount*4);
                }
                break;
            }
            if(actionCount)fn_005ecf00(block,statement,actionCount);
        }
    }
    for(block=flowHead;block;block=block->next){
        if(!block->predecessorCount)block->predecessors=NULL;
        else block->predecessors=flowAllocate(block->predecessorCount*4);
        block->predecessorCount=0;
    }
    for(block=flowHead;block;block=block->next){
        for(i=0;i<block->successorCount;i++){
            target=flowByIndex[block->successors[i]];
            target->predecessors[target->predecessorCount++]=block->index;
        }
    }
}

/* The sole native caller passes count in a third slot; the callee does not read it. */
void fn_005ecf00(FlowBlock *block,FlowStatement *statement,SInt32 count)
{
    FlowAction *action;
    for(action=statement->actions;action;action=action->next){
        if(action->kind==13)AddRef(block,action->label->block);
        else if(action->kind==15)AddRef(block,action->label->block);
    }
}

/* Switch cases and default share duplicate suppression and predecessor counting. */
void fn_005ecfe0(FlowBlock *block,SInt32 actionCount)
{
    FlowSwitch *info=(FlowSwitch *)block->last->label;
    FlowCase *entry;
    SInt32 count=1;
    for(entry=info->cases;entry;entry=entry->next)count++;
    block->successors=flowAllocate((count+actionCount)*4);
    for(entry=info->cases;entry;entry=entry->next)AddRef(block,entry->label->block);
    AddRef(block,info->defaultLabel->block);
}

/* Allocate exactly 36 bytes; reserved +28 is zeroed with the full record. */
void fn_005ed0e0(FlowStatement *statement)
{
    FlowBlock *block=flowAllocate(36);
    memset(block,0,36);
    block->index=flowBlockCount++;
    block->next=NULL;
    block->successorCount=0;
    block->successors=NULL;
    block->predecessorCount=0;
    block->predecessors=NULL;
    block->first=statement;
    block->last=statement;
    block->next=NULL;
    if(!flowHead)flowHead=block;
    else flowTail->next=block;
    flowTail=block;
}
