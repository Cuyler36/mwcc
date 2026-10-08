/* Native IroNonRegLoopAccesses.c; private packed Windows records. */
#include "compiler/common.h"
#pragma pack(push,2)
typedef struct NativeIR NativeIR;
typedef struct NativeBlock NativeBlock;
typedef struct NativeCandidate NativeCandidate;
typedef struct NativeReference NativeReference;
typedef struct NativeVariable NativeVariable;
typedef struct NativeObject NativeObject;
typedef struct NativeBits {UInt32 count,words[1];} NativeBits;
struct NativeIR {
 UInt8 kind,operation;UInt32 flags;UInt8 unknown06[4];UInt32 serial;
 UInt8 unknown0e[4];void *type;UInt8 unknown16[20];
 NativeIR *left,*right;UInt8 unknown32[12];NativeIR *next;
};
struct NativeReference {NativeIR *node;NativeReference *next;};
struct NativeCandidate {UInt8 state,unknown01;NativeIR *node;NativeReference *references;NativeIR *value;NativeObject *object;NativeCandidate *next;};
struct NativeVariable {UInt32 index;NativeObject *object;UInt8 unknown08[8];NativeVariable *next;UInt8 unknown14[16];NativeCandidate *candidate;};
struct NativeObject {UInt8 unknown00[16];void *type;UInt32 qualifiers;UInt8 unknown18[8];NativeVariable *variable;};
struct NativeBlock {UInt16 index;UInt8 unknown02[6];UInt16 predecessors;UInt8 unknown0a[6];NativeIR *first,*last;UInt8 unknown18[24];NativeBlock *next;UInt8 unknown34[7];UInt8 control;};
typedef struct NativeLoop {UInt8 unknown00[8];NativeBits *blocks,*modified;NativeBlock *header,*last;void *unknown18;NativeBlock *back;UInt8 unknown20[58];SInt16 count;UInt8 unknown5c[2];NativeBlock *end;} NativeLoop;
typedef struct NativeIRLeaf {UInt8 unknown00[16];NativeObject *object;} NativeIRLeaf;
typedef struct NativeExpression {NativeIR *value;SInt32 count;NativeReference *references;UInt8 unknown0c[20];} NativeExpression;
typedef struct NativeIRList {NativeIR *first,*last;} NativeIRList;
typedef struct NativeCandidateList {NativeCandidate *first,*last;} NativeCandidateList;
#pragma pack(pop)
typedef char CheckCandidateSize[(sizeof(NativeCandidate)==22)?1:-1];
typedef char CheckIRSize[(sizeof(NativeIR)==66)?1:-1];
typedef char CheckExpressionSize[(sizeof(NativeExpression)==32)?1:-1];
extern NativeVariable *native_variables;
extern NativeBlock *native_blocks;
extern NativeBits *native_modified;
extern UInt32 native_variable_count,native_serial;
extern void *native_work;
extern UInt8 (*native_side_effect)(NativeIR *,SInt32);
extern NativeObject *create_temp_object(void *);
extern NativeVariable *fn_005b53d0(NativeObject *,SInt32,SInt32);
extern void fn_005ad280(NativeIRList *),fn_005ad220(NativeIR *,NativeIRList *),fn_005ad440(NativeIR *,NativeIR *,NativeIR *),fn_005ad400(NativeIR *,NativeIR *,NativeIR *),fn_005acb80(NativeIR *,NativeIR *);
extern NativeIR *fn_005bd630(SInt32),*fn_005acdf0(NativeObject *),*fn_005acf30(NativeIR *,NativeIRList *);
extern void *fn_005b7d30(void *);
extern UInt8 fn_00453290(void *,UInt32);
extern void CError_Internal(const char *,SInt32),fn_005ed4c0(const char *,...);
extern void fn_005bfae0(NativeBits **,UInt32),fn_004c53c0(void *);
extern void *fn_004c5470(SInt32);
extern NativeObject *fn_005ac1e0(NativeIR *);
extern UInt8 fn_005ac320(NativeIR *),fn_005b04a0(NativeIR *,NativeIR *),fn_00455840(NativeObject *,NativeObject *),fn_005b1fc0(NativeObject *);
extern void fn_005ab7d0(NativeExpression *,NativeIR *),fn_005ab710(NativeIR *,NativeReference **,void *(*)(SInt32)),fn_005ab500(NativeIR *,NativeExpression *,void *(*)(SInt32));
extern void IroBitVect_ClearBitVector(NativeBits *),fn_005f6b80(NativeIR *,SInt32,SInt32,SInt32),fn_005bf780(NativeBits *,NativeBits *);
extern UInt8 fn_005bf6c0(NativeBits *),fn_005c6400(NativeLoop *);
extern void fn_005c6340(NativeLoop *,NativeBlock *,void *,NativeIR **,void *),fn_005b8d90(void *);
extern NativeBlock *fn_005c64e0(NativeLoop *);
static char filename[]="IroNonRegLoopAccesses.c";
static char log_replace[]="Replacing Loop Motion Candidate Reference at Int = %d\n";
static char log_candidate[]="Loop Motion Candidate:: Int = %d";
static char log_valid[]="<valid>";
static char log_invalid[]="<invalid>";
static char log_possible[]="<possibly_valid>";
static char log_newline[]="\n";
static char log_no_predecessor[]="No predecessor outside the loop\n";
static inline UInt8 contains(NativeBits *bits,UInt32 bit) {return (bit>>5)<bits->count && (bits->words[bit>>5]&(1U<<(bit&31)))!=0;}
void fn_0063e430(NativeLoop *,NativeCandidate *,NativeIR *);
void fn_0063e6b0(NativeBits *,NativeCandidateList *);
void fn_0063e8a0(NativeIR *,UInt8,NativeBits *,NativeCandidateList *);
void fn_0063ea50(NativeIR *,NativeBits *,NativeCandidateList *);
void fn_0063eb40(NativeIR *,NativeIR *,NativeObject *,UInt8,UInt8,NativeCandidateList *);
void IRO_OptimizeNonRegAccesses(NativeLoop *,void *);

void fn_0063e430(NativeLoop *loop,NativeCandidate *candidate,NativeIR *entry)
{
 NativeObject *temporary=create_temp_object(candidate->node->type);NativeVariable *variable;
 NativeIR *access,*target;NativeIRList list;NativeReference *ref;
 fn_005b53d0(temporary,1,1);variable=fn_005b53d0(candidate->object,0,1);
 if(!variable)CError_Internal(filename,569);
 else {
  NativeIR *assign;fn_005ad280(&list);assign=fn_005bd630(3);assign->serial=++native_serial;assign->type=fn_005b7d30(candidate->node->type);assign->operation=0x1e;
  assign->left=fn_005acdf0(temporary);fn_005ad220(assign->left->left,&list);assign->left->flags|=0x26;assign->left->left->flags|=0x24;
  assign->right=fn_005acf30(candidate->node,&list);fn_005ad220(assign,&list);fn_005ad440(list.first,list.last,entry);
 }
 if(contains(loop->modified,variable->index) && !fn_00453290(candidate->object->type,candidate->object->qualifiers)) {
  NativeIR *assign;fn_005ad280(&list);assign=fn_005bd630(3);assign->serial=++native_serial;assign->type=fn_005b7d30(candidate->node->type);assign->operation=0x1e;
  assign->left=fn_005acf30(candidate->node,&list);assign->left->flags|=0x24;assign->left->left->flags|=0x24;
  assign->right=fn_005acdf0(temporary);assign->right->flags|=2;fn_005ad220(assign->right->left,&list);fn_005ad220(assign,&list);target=loop->end->first;
  if(target->kind==13)fn_005ad400(list.first,list.last,target);else fn_005ad440(list.first,list.last,target);
 }
 for(ref=candidate->references;ref;ref=ref->next) {
  fn_005ed4c0(log_replace,ref->node->serial);fn_005ad280(&list);access=fn_005acdf0(temporary);fn_005ad220(access->left,&list);list.last->flags|=2;
  fn_005ad440(list.first,list.last,ref->node);fn_005acb80(ref->node,list.last);
 }
}
void fn_0063e6b0(NativeBits *blocks,NativeCandidateList *candidates)
{
 NativeVariable *v;NativeBits *bits;NativeBlock *block;NativeIR *node;
 for(v=native_variables;v;v=v->next)v->candidate=0;
 fn_005bfae0(&bits,native_variable_count+1);fn_005bfae0(&native_modified,native_variable_count+1);
 for(block=native_blocks;block;block=block->next)if(contains(blocks,block->index))
  for(node=block->first;node && node!=block->last->next;node=node->next)
   if(node->kind==2 && node->operation==4 && (node->left->flags&0x100) && !fn_005ac1e0(node) && !fn_005ac320(node))fn_0063e8a0(node,block->control,bits,candidates);
   else fn_0063ea50(node,bits,candidates);
 /* Both scans are present in the native control flow. */
 {NativeBlock *block2;NativeIR *node2;
 for(block2=native_blocks;block2;block2=block2->next)if(contains(blocks,block2->index))
  for(node2=block2->first;node2 && node2!=block2->last->next;node2=node2->next)
   if(node2->kind==2 && node2->operation==4 && (node2->left->flags&0x100) && !fn_005ac1e0(node2) && !fn_005ac320(node2))fn_0063e8a0(node2,block2->control,bits,candidates);
   else fn_0063ea50(node2,bits,candidates);
 }
 if(native_modified) {fn_004c53c0(native_modified);native_modified=0;}
 if(bits) {fn_004c53c0(bits);bits=0;}
}
void fn_0063e8a0(NativeIR *node,UInt8 control,NativeBits *bits,NativeCandidateList *candidates)
{
 NativeIR *value=node->left;NativeExpression expression;NativeCandidate *candidate;NativeReference *ref;UInt8 movable;
 fn_005ab7d0(&expression,value);
 if(value->kind==1 && value->left->kind==59) {expression.count=1;fn_005ab710(value,&expression.references,fn_004c5470);}
 else if(value->kind==3 && value->operation==15)fn_005ab500(value,&expression,fn_004c5470);
 if(expression.count==1) {
 movable=1;
 if(!(node->flags&0x100000) && (node->flags&2))movable=0;
 for(candidate=candidates->first;candidate;candidate=candidate->next)
  if(fn_00455840(((NativeIRLeaf*)expression.references->node->left)->object,candidate->object))break;
 if(!candidate)fn_0063eb40(node,expression.value,((NativeIRLeaf*)expression.references->node->left)->object,control,movable,candidates);
 else if(candidate->state!=1) {
  if(!fn_005b04a0(value,candidate->value))candidate->state=1;
  else {
   for(ref=candidate->references;ref && ref->node!=node;ref=ref->next){}
   if(!ref) {ref=fn_004c5470(8);ref->node=node;ref->next=0;if(!candidate->references)candidate->references=ref;else {ref->next=candidate->references;candidate->references=ref;}}
  }
  if(!control && movable)candidate->state=1;
  else if(candidate->state==2 && (control || movable))candidate->state=0;
 }
 }else fn_0063ea50(node,bits,candidates);
}
void fn_0063ea50(NativeIR *node,NativeBits *bits,NativeCandidateList *candidates)
{
 NativeVariable *variable;
 if((node->kind==2 && node->operation==4) || node->kind==7 || (native_side_effect && native_side_effect(node,0)) || node->kind==20) {
  IroBitVect_ClearBitVector(bits);fn_005f6b80(node,0,0,0);fn_005bf780(native_modified,bits);
  if(!fn_005bf6c0(bits))for(variable=native_variables;variable;variable=variable->next)if(contains(bits,variable->index)) {
   if(!variable->candidate)fn_0063eb40(node,0,variable->object,0,1,candidates);
   else variable->candidate->state=1;
  }
 }
}
void fn_0063eb40(NativeIR *node,NativeIR *value,NativeObject *object,UInt8 control,UInt8 movable,NativeCandidateList *list)
{
 NativeCandidate *candidate;NativeReference *ref;
 if(!fn_005b1fc0(object)) {
 if(!list->first) {candidate=fn_004c5470(22);list->first=candidate;}
 else {candidate=fn_004c5470(22);list->last->next=candidate;candidate=list->last->next;}
 list->last=candidate;list->last->state=2;list->last->node=node;list->last->value=value;list->last->object=object;list->last->next=0;list->last->references=0;
 if(object->variable)object->variable->candidate=list->last;
 ref=fn_004c5470(8);ref->node=node;ref->next=0;
 if(!list->last->references)list->last->references=ref;else {ref->next=list->last->references;list->last->references=ref;}
 if(!control && movable)list->last->state=1;
 else if(control || movable)list->last->state=0;
 }
}
void IRO_OptimizeNonRegAccesses(NativeLoop *loop,void *context)
{
 NativeCandidateList list;NativeIR *entry;NativeCandidate *candidate;UInt8 valid;
 if(!fn_005c6400(loop)) {fn_005ed4c0(log_no_predecessor);return;}
 fn_005c6340(loop,loop->last,loop->unknown18,&entry,context);
 valid=loop->back!=0;
 if(valid && loop->count==1) {
  if(loop->end->predecessors!=1) {loop->end=fn_005c64e0(loop);if(!loop->end)valid=0;}
  if(valid) {
   list.first=0;list.last=0;fn_0063e6b0(loop->blocks,&list);
   for(candidate=list.first;candidate;candidate=candidate->next) {
    if(candidate->state==2)candidate->state=1;
    fn_005ed4c0(log_candidate,candidate->node->serial);
    switch(candidate->state) {case 0:fn_005ed4c0(log_valid);break;case 1:fn_005ed4c0(log_invalid);break;case 2:fn_005ed4c0(log_possible);break;default:CError_Internal(filename,186);}
    fn_005ed4c0(log_newline);if(!candidate->state)fn_0063e430(loop,candidate,entry);
   }
  }
 }
 fn_005b8d90(native_work);
}
