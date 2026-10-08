/* Native InterferenceGraph.c candidate. All records use the Windows ABI. */
typedef unsigned int U32;
typedef unsigned short U16;
typedef short S16;
typedef unsigned char U8;
#pragma pack(push, 2)
typedef struct Edge Edge;
typedef struct Node Node;
typedef struct Inst Inst;
typedef struct Block Block;
typedef struct Operand { U8 kind, cls; U16 flags; S16 reg; U8 rest[8]; } Operand;
struct Edge { Edge *next, *a, *b; S16 lo, hi; };
struct Node { Node *next; void *object; Inst *remat; int cost; S16 index, color; U16 flags, degree, nedges; Edge *edges; };
struct Inst { Inst *next, *prev; Block *block; U32 flags, flagsHi; U8 rest[22]; S16 nops; Operand ops[1]; };
struct Block { Block *next; U8 rest[16]; Inst *first,*last; int index; U8 rest2[4]; int weight; };
typedef struct List { struct List *next; void *object; U8 rest[4]; U8 cls; } List;
typedef struct Info { U8 rest[14]; U8 flags,cls; S16 reg,regHi; } Info;
typedef struct LiveBlock { U32 *in,*out,*use,*liveout; } LiveBlock;
typedef struct LiveClass { U32 nregs; LiveBlock *blocks; U32 rest; } LiveClass;
#pragma pack(pop)
extern signed char register_class;
extern U32 used_registers[], first_virtual[], call_clobber_count[],call_clobbers[][32];
Node *interferencegraph;
extern Block *pcodeblocks;
extern List *local_objects,*argument_objects,*register_objects;
extern LiveClass liveclasses[];
extern U8 uniform_spill_weight;
extern void *fn_0046c660(U32), *fn_0046c5e0(U32);
extern void fn_0046c480(void), fn_0045a250(const char *,int);
extern void fn_00578410(int),fn_006210c0(int),fn_00579420(Inst*);
extern void fn_00578460(int),fn_005784b0(void),fn_00582a50(Inst*);
extern int fn_0058ba80(Inst*),fn_00579300(S16,S16);
extern Info *fn_00579790(void*);
static S16 *coalesced;
static U32 coalesced_nregisters, blocked_count;
static U32 *blocked_dense,*blocked_sparse;
static Edge *interferencematrix[0x4000];
static inline S16 coalesced_path(S16 reg)
{
    if ((U32)(int)reg > used_registers[register_class])
        fn_0045a250("InterferenceGraph.c",412);
    while (reg != coalesced[reg]) reg=coalesced[reg];
    return reg;
}
int interferes(U32 a,U32 b)
{
    Edge *e;
    if(a<b) {
        for(e=interferencematrix[((b-1)*b/2+a)&0x3fff];e;e=e->next)
            if(e->lo==a && e->hi==b) return 1;
    } else if(a>b) {
        for(e=interferencematrix[((a-1)*a/2+b)&0x3fff];e;e=e->next)
            if(e->hi==a && e->lo==b) return 1;
    }
    return 0;
}
void makeinterfere(U32 a,U32 b)
{
    Edge *e; Node *na,*nb; U32 h;
    if(a<b) {
        h=((b-1)*b/2+a)&0x3fff;
        for(e=interferencematrix[h];e;e=e->next) if(e->lo==a && e->hi==b) return;
        na=&interferencegraph[a]; nb=&interferencegraph[b];
        e=fn_0046c5e0(sizeof(Edge)); e->next=interferencematrix[h];interferencematrix[h]=e;
        e->a=na->edges;na->edges=e;e->b=nb->edges;nb->edges=e;e->lo=a;e->hi=b;
        na->nedges++;nb->nedges++;na->degree++;nb->degree++;
        if((na->flags&0x200)||(nb->flags&0x200)){na->degree++;nb->degree++;}
    } else if(a>b) {
        h=((a-1)*a/2+b)&0x3fff;
        for(e=interferencematrix[h];e;e=e->next) if(e->hi==a && e->lo==b) return;
        na=&interferencegraph[a];nb=&interferencegraph[b];
        e=fn_0046c5e0(sizeof(Edge));e->next=interferencematrix[h];interferencematrix[h]=e;
        e->a=nb->edges;nb->edges=e;e->b=na->edges;na->edges=e;e->lo=b;e->hi=a;
        na->nedges++;nb->nedges++;na->degree++;nb->degree++;
        if((na->flags&0x200)||(nb->flags&0x200)){na->degree++;nb->degree++;}
    }
}
void fn_0061ff10(void)
{
    U32 i,n=used_registers[register_class];Node *p;
    interferencegraph=fn_0046c5e0(n*sizeof(Node));
    for(i=0;i<n;i++){
        p=&interferencegraph[i];p->next=0;p->object=0;p->remat=0;p->cost=0;
        p->index=i;p->color=-1;p->flags=0;p->degree=0;p->nedges=0;p->edges=0;
    }
    for(i=0;i<0x4000;i++)interferencematrix[i]=0;
}
void findrematerializations(void)
{
    U32 i,n=used_registers[register_class];Block *b;Inst *pc;Operand *op;U32 count;Node *p;
    for(b=pcodeblocks;b;b=b->next)for(pc=b->last;pc;pc=pc->prev){
        count=pc->nops;
        for(op=pc->ops;count--;op++)if(op->kind==0 && op->cls==(U8)register_class &&(op->flags&2)&&op->reg>=(int)first_virtual[register_class]){
            p=&interferencegraph[op->reg];
            if(!(p->flags&0x30)&&!(p->flags&0x40)&&!(p->flags&0x800)){
                if(!p->remat)p->remat=pc;
                else {p->remat=0;p->flags|=0x40;}
            }
        }
    }
    for(i=0;i<n;i++) {p=&interferencegraph[i];if(p->remat && !fn_0058ba80(p->remat))p->remat=0;}
    fn_00578460(register_class);
}
/* Native 61f659 uses the last object value retained from preceding lists.
 * The paired-register third-list path is reviewed only under that precondition. */
void fn_0061f470(void)
{
    U32 i;List *l;Info *v;void *o;
    for(i=0;i<first_virtual[register_class];i++)interferencegraph[i].color=i;
    for(l=local_objects;l;l=l->next){
        o=l->object;v=fn_00579790(o);
        if((v->flags&2)&&v->cls==register_class){
            interferencegraph[v->reg].object=o;
            if(v->flags&4){interferencegraph[v->reg].flags|=0x20;interferencegraph[v->regHi].object=o;interferencegraph[v->regHi].flags|=0x10;}
        }
    }
    for(l=argument_objects;l;l=l->next){
        o=l->object;v=fn_00579790(o);
        if((v->flags&2)&&v->cls==register_class){
            interferencegraph[v->reg].object=o;
            if(v->flags&4){interferencegraph[v->reg].flags|=0x20;interferencegraph[v->regHi].object=o;interferencegraph[v->regHi].flags|=0x10;}
        }
    }
    fn_005784b0();
    for(l=register_objects;l;l=l->next)if(l->cls==(U8)register_class){
        v=fn_00579790(l->object);
        if(v->flags&2)interferencegraph[v->reg].object=l->object;
        if(v->flags&4){interferencegraph[v->reg].flags|=0x20;interferencegraph[v->regHi].object=o;interferencegraph[v->regHi].flags|=0x10;}
    }
}
void fn_0061f690(void)
{
    U32 i,n=used_registers[register_class];Node *p;S16 root;
    for(i=0;i<n;i++){
        p=&interferencegraph[i];if(i!=(int)coalesced[i]){p->flags|=4;root=coalesced_path(i);
        interferencegraph[root].flags|=8;
        if((U32)(int)root<first_virtual[register_class])p->color=root;
    }}
    for(i=0;i<n;i++){
        p=&interferencegraph[i];
        if(p->object &&(p->flags&8)&&((U8*)p->object)[2]==1)
            ((U8*)*(void**)((U8*)p->object+64))[14]|=16;
    }
}
int coalescenodes(void)
{
    Block *b;Inst *pc;Operand *op;Node *p;Edge *e;S16 a,c,lo,hi;int changed=0;U32 i;
    for(b=pcodeblocks;b;b=b->next)for(pc=b->first;pc;pc=pc->next){
        if((pc->flags&16)&&pc->ops[1].cls==(U8)register_class){
            a=coalesced_path(pc->ops[1].reg);c=coalesced_path(pc->ops[0].reg);
            if(a==c)fn_00582a50(pc);
            else if(!interferes(a,c)&&!fn_00579300(a,c)){
                if(a<c){lo=a;hi=c;}else{lo=c;hi=a;}
                i=blocked_sparse[hi];
                if(i<blocked_count &&blocked_dense[i]==(U32)(int)hi)continue;
                coalesced[hi]=lo;p=&interferencegraph[hi];
                for(e=p->edges;e;){
                    if(p->index<e->hi){makeinterfere(lo,e->hi);e=e->a;}
                    else {makeinterfere(lo,e->lo);e=e->b;}
                }
                fn_00582a50(pc);changed=1;
            }
        }
    }
    for(b=pcodeblocks;b;b=b->next)for(pc=b->first;pc;pc=pc->next)
        for(i=pc->nops,op=pc->ops;i--;op++)
            if(op->kind==0 &&op->cls==(U8)register_class &&op->reg!=coalesced[op->reg])op->reg=coalesced_path(op->reg);
    return changed;
}
void buildinterferencematrix(void)
{
    U32 n=used_registers[register_class],physical=first_virtual[register_class],i,j,count,pos,r,last;
    U32 *dense,*sparse,*bits;Block *b;Inst *pc;Operand *op;U32 left;
    coalesced_nregisters=n;blocked_count=0;
    blocked_dense=fn_0046c5e0(n*4);blocked_sparse=fn_0046c5e0(n*4);blocked_count=0;
    for(i=0;i<physical;i++)for(j=0;j<physical;j++)if(i!=j)makeinterfere(i,j);
    fn_00578410(register_class);fn_006210c0(register_class);
    dense=fn_0046c5e0(n*4);sparse=fn_0046c5e0(n*4);
    for(b=pcodeblocks;b;b=b->next){
        bits=liveclasses[register_class].blocks[b->index].liveout;count=0;
        for(i=0;i<n;i++)if((bits[i>>5]>>(i&31))&1){sparse[i]=count;dense[count++]=i;}
        for(pc=b->last;pc;pc=pc->prev){
            left=pc->nops;for(op=pc->ops;left--;op++)if(op->kind==0&&op->cls==(U8)register_class&&(op->flags&2))
                for(i=0;i<count;i++)if(!(pc->flags&16)||pc->ops[1].reg!=(int)dense[i])makeinterfere(op->reg,dense[i]);
            left=pc->nops;for(op=pc->ops;left--;op++)if(op->kind==0&&op->cls==(U8)register_class&&(op->flags&2)){
                r=op->reg;pos=sparse[r];if(pos<count&&dense[pos]==r){last=dense[--count];dense[pos]=last;sparse[last]=pos;}
            }
            left=pc->nops;for(op=pc->ops;left--;op++)if(op->kind==0&&op->cls==(U8)register_class&&(op->flags&1)){
                r=op->reg;pos=sparse[r];if(!(pos<count&&dense[pos]==r))op->flags|=4;
                r=op->reg;pos=sparse[r];if(!(pos<count&&dense[pos]==r)){sparse[r]=count;dense[count++]=r;}
            }
            fn_00579420(pc);
            if(pc->flags&8)for(i=0,op=pc->ops;i<(U32)(int)pc->nops;i++,op++)
                if(op->kind==0&&(op->flags&8)&&op->cls==(U8)register_class){
                    interferencegraph[op->reg].flags|=0x800;
                    for(j=0;j<call_clobber_count[register_class];j++)makeinterfere(op->reg,call_clobbers[register_class][j]);
                    r=op->reg;pos=blocked_sparse[r];if(!(pos<blocked_count&&blocked_dense[pos]==r)){blocked_sparse[r]=blocked_count;blocked_dense[blocked_count++]=r;}
                }
        }
    }
}
void buildinterferencegraph(void *function)
{
    U32 i,n=used_registers[register_class];
    coalesced=fn_0046c660(n*2);for(i=0;i<n;i++)coalesced[i]=i;
    do {fn_0046c480();fn_0061ff10();buildinterferencematrix();} while(coalescenodes());
    fn_0061f470();fn_0061f690();findrematerializations();
}
void estimatespillcosts(void)
{
    Block *b;Inst *pc;Operand *op;Node *p;int weight;U32 count;
    for(b=pcodeblocks;b;b=b->next){
        weight=uniform_spill_weight?1:b->weight;
        for(pc=b->first;pc;pc=pc->next){
            count=pc->nops;for(op=pc->ops;count--;op++)if(op->kind==0&&op->cls==(U8)register_class&&(op->flags&1)){
                p=&interferencegraph[op->reg];if(op->flags&16)p->flags|=0x400;if(op->flags&64)p->flags|=0x80;
                p->cost+=(!p->remat&&!uniform_spill_weight)?weight*2:weight;
            }
            count=pc->nops;for(op=pc->ops;count--;op++)if(op->kind==0&&op->cls==(U8)register_class&&(op->flags&2)){
                p=&interferencegraph[op->reg];if(op->flags&16)p->flags|=0x400;if(op->flags&64)p->flags|=0x80;
                p->cost+=(p->remat ||(pc->flags&0x8002)==0x8002)?-weight:weight;
            }
        }
    }
}
