/* Native register coloring. Private records keep baseline payloads separate. */
#include "compiler/common.h"
#include <stddef.h>
#include <string.h>
#pragma pack(push,2)
typedef struct NativeObject NativeObject;
typedef struct NativeVarInfo {UInt8 unknown00[9],used,unknown0a[4],flags,regclass;SInt16 reg,regHi;} NativeVarInfo;
struct NativeObject {UInt8 unknown00[64];NativeVarInfo *info;};
typedef struct NativeEdge {struct NativeEdge *next,*left,*right;SInt16 a,b;} NativeEdge;
typedef struct NativeNode {struct NativeNode *next;NativeObject *object;SInt32 unknown08,cost;SInt16 index,color;UInt16 flags;SInt16 degree;UInt16 unknown18;NativeEdge *edges;} NativeNode;
typedef struct NativeOperand {UInt8 kind,regclass;UInt16 flags;SInt16 reg;UInt8 unknown06[8];} NativeOperand;
typedef struct NativeInstruction {struct NativeInstruction *next;UInt8 unknown04[8];UInt32 flags,flagsHi;UInt8 unknown14[20];SInt16 opcode,operandCount;NativeOperand operands[1];} NativeInstruction;
typedef struct NativeBlock {struct NativeBlock *next;UInt8 unknown04[16];NativeInstruction *first;} NativeBlock;
#pragma pack(pop)
typedef char node_size_check[sizeof(NativeNode)==30?1:-1];
typedef char node_edges_check[offsetof(NativeNode,edges)==26?1:-1];
typedef char operand_size_check[sizeof(NativeOperand)==14?1:-1];
typedef char instruction_operands_check[offsetof(NativeInstruction,operands)==44?1:-1];
static char filename[]="Coloring.c";
static UInt32 saved_registers[8];
static SInt16 used_regs_before_coloring;
SInt8 coloring_class;
extern NativeNode *nodes;
extern NativeBlock *blocks;
extern UInt32 register_count[5],first_virtual[5];
extern SInt32 used_register_count[5];
extern UInt32 register_state[5][8];
extern SInt32 iterations;
extern UInt32 stats[6];
extern UInt32 virtual_registers_active;
extern char *class_names[5];
extern void CError_Internal(const char *,int);
extern void fn_005792c0(int);
extern int fn_00594700(int),fn_005946b0(int);
extern SInt16 fn_00594590(int);
extern void fn_0061f280(void *),fn_00620500(void),fn_00620f10(void);
extern void CompilerTools_ResetPool(void),fn_004b9c40(int,UInt32 *);
extern void PPCError_ReportError(int,...);
extern void delete_instruction(NativeInstruction *);
extern NativeVarInfo *Registers_GetVarInfo(NativeObject *);
extern int fn_0057a740(NativeObject *);
void colorinstructions(void *function);
void rewritepcode(void);
int colorgraph(NativeNode *stack);
NativeNode *simplifygraph(void);

void colorinstructions(void *function) {
    SInt8 cls;
    int spill;
    for(cls=0;cls<5;cls++) {
        coloring_class=cls;
        fn_005792c0(cls);
        if(register_count[cls]==first_virtual[cls])continue;
        stats[0]=stats[3]=stats[1]=stats[4]=stats[2]=stats[5]=0;
        used_regs_before_coloring=used_register_count[cls];
        memcpy(saved_registers,register_state[cls],sizeof(saved_registers));
        if(!fn_00594700(cls)){PPCError_ReportError(12,class_names[cls]);return;}
        iterations=0;
        do {
            if(iterations>10)CError_Internal(filename,501);
            fn_0061f280(function);
            spill=0;
            if(!colorgraph(simplifygraph()))spill=1;
            if(spill){fn_00620500();iterations++;}
            else rewritepcode();
            CompilerTools_ResetPool();
        }while(spill);
        register_count[cls]=first_virtual[cls];
        fn_004b9c40(cls,stats);
    }
    virtual_registers_active=0;
}
void rewritepcode(void) {
    NativeBlock *block;
    NativeInstruction *instruction;
    NativeOperand *operand;
    UInt32 reg;
    int i;
    NativeNode *node;
    NativeVarInfo *info;
    SInt16 color;
    for(block=blocks;block;block=block->next) {
        for(instruction=block->first;instruction;instruction=instruction->next) {
            operand=instruction->operands;
            for(i=instruction->operandCount;i--;) {
                if(operand->kind==0 && operand->regclass==(UInt8)coloring_class)
                    operand->reg=nodes[operand->reg].color;
                operand++;
            }
            if((instruction->flags&16) && instruction->operands[1].regclass==(UInt8)coloring_class && instruction->operands[1].reg==instruction->operands[0].reg)
                delete_instruction(instruction);
        }
    }
    for(reg=first_virtual[coloring_class];reg<register_count[coloring_class];reg++) {
        node=&nodes[reg];
        if(node->object && !(node->flags&1)) {
            if(node->flags&16) {
                if(node->object->info->used) {
                    color=node->color;info=Registers_GetVarInfo(node->object);
                    if(info){info->regHi=color;info->flags|=6;}
                }
            } else {
                if(node->object->info->used) {
                    color=node->color;info=Registers_GetVarInfo(node->object);
                    if(info){info->reg=color;info->flags|=2;}
                }
            }
        }
    }
}
int colorgraph(NativeNode *stack) {
    int result=1,i;
    UInt32 mask,available;
    NativeEdge *edge;
    NativeNode *neighbor;
    SInt16 other,color;
    used_register_count[coloring_class]=used_regs_before_coloring;
    memcpy(register_state[coloring_class],saved_registers,sizeof(saved_registers));
    available=fn_005946b0(coloring_class);
    while(stack) {
        mask=available;
        for(edge=stack->edges;edge;) {
            if(stack->index<edge->b)other=edge->b;else other=edge->a;
            neighbor=&nodes[other];color=neighbor->color;
            if(color!=-1) {
                if(neighbor->flags&512)mask&=~(3U<<((UInt32)color&31));
                else mask&=~(1U<<((UInt32)color&31));
            }
            edge=stack->index<edge->b?edge->left:edge->right;
        }
        if(mask) {
            if(stack->flags&512) {
                for(i=0;i<(SInt32)first_virtual[coloring_class];i+=2) {
                    UInt32 pair=3U<<(i&31);
                    if((mask&pair)==pair){stack->color=i;break;}
                }
            } else {
                for(i=0;i<(SInt32)first_virtual[coloring_class];i++) {
                    if(mask&(1U<<(i&31))){stack->color=i;break;}
                }
            }
        }
        if(stack->color==-1) {
            color=fn_00594590(coloring_class);
            if(color!=-1){available|=1U<<((UInt32)color&31);continue;}
        }
        if(fn_0057a740(stack->object))CError_Internal(filename,391);
        if(stack->color==-1){stack->flags|=1;result=0;}
        stack=stack->next;
    }
    return result;
}
#define DECREMENT_NEIGHBORS(node,edge,other,neighbor) \
    for(edge=(node)->edges;edge;edge=(node)->index<edge->b?edge->left:edge->right) { \
        other=(node)->index<edge->b?edge->b:edge->a;neighbor=&nodes[other]; \
        if(((node)->flags&512)||(neighbor->flags&512))neighbor->degree-=2;else neighbor->degree--; \
    }
#define SIMPLIFY_PASS() \
    do { \
        remaining=0;changed=0; \
        for(reg=first_virtual[coloring_class];reg<register_count[coloring_class];reg++) { \
            node=&nodes[reg]; \
            if(!(node->flags&6)) { \
                if(node->degree<limit) { \
                    DECREMENT_NEIGHBORS(node,edge,other,neighbor) \
                    node->flags|=2;node->next=stack;stack=node;changed=1; \
                } else {node->next=remaining;remaining=node;} \
            } \
        } \
    }while(changed)
NativeNode *simplifygraph(void) {
    int limit=fn_00594700(coloring_class),changed;
    UInt32 reg;
    NativeNode *stack=0,*remaining,*node,*neighbor,*candidate;
    NativeEdge *edge;
    SInt16 other;
    float best=0,score=0;
    SIMPLIFY_PASS();
    if(remaining)fn_00620f10();
    while(remaining) {
        candidate=remaining;
        if(remaining->flags&128)best=3.4028234663852886e38f;
        else if(remaining->flags&1024)best=1.7014117331926443e38f;
        else best=(float)remaining->cost/(float)remaining->degree;
        for(node=remaining->next;node;node=node->next) {
            if(node->flags&128)score=3.4028234663852886e38f;
            else if(node->flags&1024)score=1.7014117331926443e38f;
            else score=(float)node->cost/(float)node->degree;
            if(score<best){best=score;candidate=node;}
        }
        DECREMENT_NEIGHBORS(candidate,edge,other,neighbor)
        candidate->flags|=2;candidate->next=stack;stack=candidate;
        SIMPLIFY_PASS();
    }
    return stack;
}
