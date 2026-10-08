/* Spill.c native GC 3.0a5.2 candidate; private Windows records. */
typedef unsigned int U32;
typedef unsigned short U16;
typedef short S16;
typedef unsigned char U8;
#pragma pack(push, 2)
typedef struct Type { U8 kind,pad; int size; } Type;
typedef struct Info { U8 rest[9],used,rest2[4],flags,cls; S16 reg,hi; } Info;
typedef struct Object { U8 kind,pad,datatype,rest[9]; void *name; Type *type; U8 rest2[44]; Info *info; U8 rest3[4]; void *init; U8 rest4[20]; } Object;
typedef struct Edge Edge;
typedef struct Node Node;
typedef struct Inst Inst;
typedef struct Block Block;
typedef struct Operand { U8 kind,cls; U16 flags; S16 reg; U8 rest[8]; } Operand;
struct Edge { Edge *next,*a,*b; S16 lo,hi; };
struct Node { Node *next; Object *object; Inst *remat; int cost; S16 index,color; U16 flags,degree,nedges; Edge *edges; };
struct Inst { Inst *next,*prev; Block *block; U32 flags,flagsHi; U8 rest[22]; S16 nops; Operand ops[1]; };
struct Block { Block *next; U8 rest[16]; Inst *first,*last; int index; U8 rest2[4]; int weight; };
#pragma pack(pop)
extern signed char register_class;
extern U32 used_registers[],first_virtual[];
extern Node *interferencegraph;
extern Block *pcodeblocks;
extern U32 native_loads,native_stores,native_remats,native_load_weight,native_store_weight,native_remat_weight;
U32 rTEMP_for_VR_spill;
static int last_unused_vreg_before_spilling;
extern void *fn_0046c660(U32);
extern void fn_0046c400(void*,U32);
extern void *fn_00455e00(void);
extern Info *fn_0046bc00(void);
extern void fn_0045a250(const char*,int),fn_005ed260(int);
extern Type *fn_005789b0(Node*);
extern void fn_00578970(Node*,Type*),fn_0058a4e0(Object*);
extern Info *fn_00579790(Object*);
extern Inst *fn_00582db0(Inst*);
extern void fn_00579230(Inst*,S16,Inst*),fn_005829d0(Inst*,Inst*),fn_00582a50(Inst*);
extern void fn_00578a20(Inst*,U8,S16,Node*),fn_00578dd0(Inst*,S16,Node*);
void spillinstruction(Block*,Inst*);
void spillcopy(Block*,Inst*);
void spillcall(Block*,Inst*);
void assign_spill_locations(void);
Object *makespilltemporary(Type *type)
{
    Object *o=fn_0046c660(96);
    fn_0046c400(o,96);o->kind=5;o->pad=0;o->datatype=1;o->type=type;
    o->name=fn_00455e00();o->info=fn_0046bc00();o->init=0;
    return o;
}
static inline void insertrematerializer(Inst *before,S16 reg,Node *node)
{
    Inst *copy=fn_00582db0(node->remat);
    fn_00579230(before,reg,copy);
    if(copy->ops[0].kind!=0)fn_0045a250("Spill.c",156);
    copy->ops[0].reg=reg;fn_005829d0(before,copy);
    native_remats++;native_remat_weight+=before->block->weight*2;
}
void spillcopy(Block *block,Inst *pc)
{
    Node *dn,*sn;
    S16 dest,source;
    int temporary;
    sn=&interferencegraph[source=pc->ops[1].reg];
    dn=&interferencegraph[dest=pc->ops[0].reg];
    if(sn->flags&1){
        if(dn->flags&1){
            temporary=used_registers[register_class]++;
            if(temporary!=(S16)temporary)fn_005ed260(13);
            if(sn->remat)insertrematerializer(pc,temporary,sn);
            else {fn_00578dd0(pc,temporary,sn);native_loads++;native_load_weight+=block->weight*2;}
            fn_00578a20(pc,1,temporary,dn);native_stores++;native_store_weight+=block->weight;
        } else {
            if(sn->remat)insertrematerializer(pc,dest,sn);
            else {fn_00578dd0(pc,dest,sn);native_loads++;native_load_weight+=block->weight*2;}
        }
    } else {
        fn_00578a20(pc,1,source,dn);native_stores++;native_store_weight+=block->weight;
    }
    fn_00582a50(pc);
}
void spillinstruction(Block *block,Inst *pc)
{
    int n=used_registers[register_class],i,j,original,temporary,uses,defs;
    Node *node;Operand *op,*other;U8 remove=0;
    for(i=0,op=pc->ops;i<pc->nops;i++,op++)
        if(op->kind==0&&op->cls==(U8)register_class&&op->reg<n){
            node=&interferencegraph[original=op->reg];
            if(node->flags&1){
                temporary=used_registers[register_class]++;
                if(temporary!=(S16)temporary)fn_005ed260(13);
                uses=defs=0;
                for(j=i,other=op;j<pc->nops;j++,other++)
                    if(other->kind==0&&other->cls==(U8)register_class&&other->reg==original){
                        if(other->flags&1)uses++;if(other->flags&2)defs++;
                        other->reg=temporary;other->flags|=64;
                    }
                if(uses){
                    if(node->remat)insertrematerializer(pc,temporary,node);
                    else {fn_00578dd0(pc,temporary,node);native_loads++;native_load_weight+=block->weight*2;}
                }
                if(defs){
                    if(!node->remat&&(pc->flags&0x8002)!=0x8002){
                        fn_00578a20(pc,0,temporary,node);native_stores++;native_store_weight+=block->weight;
                    } else remove=1;
                }
            }
        }
    if(remove)fn_00582a50(pc);
}
void spillcall(Block *block,Inst *pc)
{
    int i,n=pc->nops;Operand *in=pc->ops,*out=in;
    for(i=0;i<n;i++,in++){
        if(in->kind==0&&in->cls==(U8)register_class&&(in->flags&8)&&(interferencegraph[in->reg].flags&1))
            pc->nops--;
        else *out++=*in;
    }
    spillinstruction(block,pc);
}
static inline int is_register_object(Object *o)
{
    Info *info=fn_00579790(o);
    if(info&&(info->flags&1))return 1;
    return 0;
}
void assign_spill_locations(void)
{
    U32 i,n=used_registers[register_class];Node *p;Info *info;Object *o;Type *type,*saved;
    last_unused_vreg_before_spilling=n;
    for(i=first_virtual[register_class];i<n;i++){
        p=&interferencegraph[i];
        if((p->flags&4)||!(p->flags&1))continue;
        if(p->remat){if(p->object)p->object->info->used=0;continue;}
        if(p->flags&0x20){
            if(!is_register_object(p->object))fn_0058a4e0(p->object);
            (p+1)->flags|=1;
        } else if(p->flags&0x10){
            if((p-1)->flags&1)continue;
            (p-1)->flags|=1;
            if(!is_register_object(p->object))fn_0058a4e0(p->object);
        } else if(register_class==1){
            type=fn_005789b0(p);fn_00578970(p,type);
        } else {
            o=p->object;
            if(o&&o->datatype==1){
                if(is_register_object(o)){
                    info=fn_00579790(p->object);info->flags&=~2;info->flags|=0x20;
                } else {
                    type=fn_005789b0(p);o=p->object;
                    if((o->info->flags&16)&&o->type->size<type->size){
                        saved=o->type;o->type=type;fn_0058a4e0(p->object);p->object->type=saved;
                        p->object->info->flags|=8;
                        if(p->flags&0x800)fn_0045a250("Spill.c",442);
                    } else fn_0058a4e0(o);
                }
            } else {
                type=fn_005789b0(p);p->object=makespilltemporary(type);fn_0058a4e0(p->object);
            }
        }
    }
}
void insertspillcode(void)
{
    Block *b;Inst *pc,*next;Operand *op;U32 i,count;int spilled;
    rTEMP_for_VR_spill=0;
    for(b=pcodeblocks;b;b=b->next)for(pc=b->first;pc;pc=pc->next)
        for(i=0,op=pc->ops;i<(U32)(int)pc->nops;i++,op++)
            if(op->kind==0&&op->cls==(U8)register_class&&(op->flags&0x8000))
                interferencegraph[op->reg].flags|=((op->flags&0x4000)?0x2000:0)|((op->flags&0x8000)?0x1000:0);
    assign_spill_locations();
    for(b=pcodeblocks;b;b=b->next)for(pc=b->first;pc;pc=next){
        next=pc->next;spilled=0;count=pc->nops;
        for(op=pc->ops;count--;op++)if(op->kind==0&&op->cls==(U8)register_class&&op->reg<last_unused_vreg_before_spilling&&(interferencegraph[op->reg].flags&1)){spilled=1;break;}
        if(spilled){
            if(!rTEMP_for_VR_spill)rTEMP_for_VR_spill=used_registers[4]++;
            if(pc->flags&16)spillcopy(b,pc);
            else if(pc->flags&8)spillcall(b,pc);
            else spillinstruction(b,pc);
        }
    }
}
