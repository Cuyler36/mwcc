/* Native Alias.c candidate; private packed Windows records. */
#include "compiler/common.h"
#pragma pack(push,2)
typedef struct NativeAlias NativeAlias;
typedef struct NativeAliasEdge NativeAliasEdge;
struct NativeAlias {
    NativeAlias *next,*hashNext;
    NativeAliasEdge *incoming,*outgoing;
    void *object;
    SInt32 offset,size,sequence,unknown20;
    UInt32 *bits;
    SInt32 index;
    UInt8 kind,unknown2d;
};
struct NativeAliasEdge {NativeAliasEdge *nextOutgoing,*nextIncoming;NativeAlias *owner,*target;};
typedef struct NativeAliasPCode {UInt8 unknown00[28];NativeAlias *alias;} NativeAliasPCode;
#pragma pack(pop)
typedef char VerifyNativeAlias[(sizeof(NativeAlias)==46)?1:-1];
typedef char VerifyNativeAliasEdge[(sizeof(NativeAliasEdge)==16)?1:-1];
NativeAlias *aliasList,*aliasWorstCase;
extern SInt32 aliasSequence;
static NativeAlias *alias_hash[2039];
static SInt32 n_gathered_aliases,n_aliases;
static void *temp_alias_links;
static UInt32 *aliasScratch;
static NativeAlias *unknownAlias,*localWorstCase;
#pragma pack(push,2)
typedef struct AliasType {UInt8 kind,pad;SInt32 size;struct AliasType *element;SInt32 count;} AliasType;
typedef struct AliasObject {UInt8 kind,pad,datatype,rest03[9];void *name;AliasType *type;UInt32 qualifiers;UInt8 rest18[66],aliased,rest5b[5];} AliasObject;
#pragma pack(pop)
static AliasObject worst_case_obj;
extern AliasType native_char_type;
static AliasType worst_case_memory_type={13,0,0xffffff,&native_char_type,0};
static AliasType aliasVirtualType={13,0,0xffffff,&native_char_type,0};
UInt8 alias_external_option;
static char worst_case_name[]="@worst_case@";
extern void *GetHashNameNode(const char*),*CParser_GetUniqueName(void);
extern UInt8 fn_00455840(void*,void*),fn_004531a0(void*),fn_00542360(AliasType*),fn_00453290(AliasType*,UInt32);
extern UInt32 fn_004533f0(AliasType*,UInt32);
extern signed char Registers_ClassForType(AliasType*);
extern void bitvectorinitialize(UInt32*,SInt32,SInt32),fn_00599360(NativeAlias*,void*);
extern SInt32 bitvectorintersectionisempty(UInt32*,UInt32*,SInt32);
void fn_0059fee0(NativeAlias*,UInt32*);
void fn_0059fda0(NativeAlias*,UInt32*,NativeAlias*,int);
void fn_005a04c0(NativeAlias*,NativeAlias*);
UInt8 is_safe_const(AliasObject*);
static inline UInt32 aliasbit(NativeAlias *a,UInt32 *bits){return (bits[a->index>>5]>>(a->index&31))&1;}
static inline void setaliasbit(NativeAlias *a,UInt32 *bits){bits[a->index>>5]|=1U<<(a->index&31);}
static inline UInt8 overlap(NativeAlias *a,NativeAlias *b) {
 UInt8 x=1,y=1;
 if(a->offset!=b->offset && (a->offset<=b->offset || (SInt32)((UInt32)b->offset+b->size)<=a->offset))x=0;
 if(!x && (b->offset<=a->offset || (SInt32)((UInt32)a->offset+a->size)<=b->offset))y=0;
 return y;
}
extern UInt8 fn_005a0170(NativeAlias *,NativeAlias *);
extern NativeAlias *fn_005a05d0(void *,SInt32,SInt32);
extern SInt32 nbytes_loaded_or_stored_by(NativeAliasPCode *);
extern void fn_0063d460(void),fn_005a0370(void);
extern void *lalloc(SInt32);
extern void memclrw(void *,SInt32);
extern void CError_Internal(const char *,SInt32);
static char filename[]="Alias.c";

void fn_0059ffa0(void) {
    NativeAlias *a;
    for(a=aliasList;a;a=a->next) {a->sequence=aliasSequence;aliasSequence++;a->unknown20=0;}
}
UInt8 fn_0059ffd0(NativeAliasPCode *p,void *object) {
    NativeAlias *a=p->alias;
    if(a->kind!=2 && a->object==object && a->size==*(SInt32 *)(*(char **)((char *)object+16)+2))
        {SInt32 size=nbytes_loaded_or_stored_by(p);if(p->alias->size==size)return 1;}
    return 0;
}
UInt8 fn_005a0010(NativeAliasPCode *p,void *object) {
    NativeAlias *a=fn_005a05d0(object,0,0);
    return fn_005a0170(p->alias,a);
}
UInt8 fn_005a0040(NativeAliasPCode *p) {return fn_005a0170(p->alias,aliasWorstCase);}
UInt8 fn_005a0060(NativeAliasPCode *p,NativeAlias *a) {
    SInt32 size;NativeAlias *left;
    if(fn_005a0170(p->alias,a) && (left=p->alias)!=0 && a && left==a && left->kind!=2 && a->kind!=2 && (size=left->size)==a->size)
        if(size==nbytes_loaded_or_stored_by(p))return 1;
    return 0;
}
UInt8 fn_005a00c0(NativeAliasPCode *p,NativeAlias *a) {return fn_005a0170(p->alias,a);}
UInt8 fn_005a00e0(NativeAliasPCode *p,NativeAliasPCode *q) {
    NativeAlias *b,*a;SInt32 size;
    if(fn_005a0170(p->alias,q->alias) && (a=p->alias)!=0 && (b=q->alias)!=0 && a==b && a->kind!=2 && b->kind!=2 && (size=a->size)==b->size)
        if(size==nbytes_loaded_or_stored_by(p))if(size==nbytes_loaded_or_stored_by(q))return 1;
    return 0;
}
UInt8 fn_005a0150(NativeAliasPCode *p,NativeAliasPCode *q) {return fn_005a0170(p->alias,q->alias);}
void fn_005a0360(void) {fn_0063d460();fn_005a0370();}
NativeAlias *fn_005a0450(NativeAlias *a,SInt32 offset,SInt32 size) {
    NativeAlias *result;
    if(!size || a->size==*(SInt32 *)(*(char **)((char *)a->object+16)+2))result=fn_005a05d0(a->object,0,0);
    else result=fn_005a05d0(a->object,(SInt32)((UInt32)a->offset+(UInt32)offset),size);
    if(!result)CError_Internal(filename,728);
    return result;
}
void fn_005a04c0(NativeAlias *a,NativeAlias *b) {
    NativeAliasEdge *edge;
    if(a==b)return;
    if(b->kind==2)for(edge=b->outgoing;edge;edge=edge->nextOutgoing)fn_005a04c0(a,edge->target);
    else {
        if(a->kind==2 && b->kind==1)b=fn_005a05d0(b->object,0,0);
        for(edge=a->outgoing;edge;edge=edge->nextOutgoing)if(edge->target==b)return;
        edge=lalloc(16);memclrw(edge,16);edge->owner=a;edge->target=b;
        edge->nextOutgoing=a->outgoing;a->outgoing=edge;edge->nextIncoming=b->incoming;b->incoming=edge;
    }
}
NativeAlias *fn_005a0570(NativeAlias *a,NativeAlias *b) {
    if(a==b)return a;
    if(a->kind!=2 && b->kind!=2 && a->object==b->object)return fn_005a05d0(a->object,0,0);
    fn_005a04c0(aliasWorstCase,a);fn_005a04c0(aliasWorstCase,b);return aliasWorstCase;
}

void fn_0059fee0(NativeAlias *a,UInt32 *bits)
{
 NativeAliasEdge *e,*incoming;
 if(aliasbit(a,bits))return;
 for(e=a->outgoing;e;e=e->nextOutgoing) {
  if(e->target->kind!=1)CError_Internal(filename,1009);
  if(!aliasbit(e->target,bits)) {
   setaliasbit(e->target,bits);fn_00599360(e->target,0);
   for(incoming=e->target->incoming;incoming;incoming=incoming->nextIncoming)
    if(incoming->owner!=a)CError_Internal(filename,1019);
  }
 }
}
void fn_0059fda0(NativeAlias *a,UInt32 *bits,NativeAlias *set,int unused)
{
 NativeAliasEdge *e;
 if(aliasbit(set,bits))return;
 setaliasbit(set,bits);fn_00599360(set,0);
 if(((AliasObject*)a->object)->type==&aliasVirtualType) {
  for(e=set->outgoing;e;e=e->nextOutgoing)if(e->target!=a && !aliasbit(e->target,bits)) {
   fn_0059fee0(e->target,bits);setaliasbit(e->target,bits);fn_00599360(e->target,0);
  }
 } else {
  for(e=set->outgoing;e;e=e->nextOutgoing)if(e->target!=a && !aliasbit(e->target,bits) && ((AliasObject*)e->target->object)->type==&aliasVirtualType) {
   fn_0059fee0(e->target,bits);setaliasbit(e->target,bits);fn_00599360(e->target,0);
  }
 }
}
void fn_0059fa20(NativeAlias *a,void *value)
{
 NativeAliasEdge *e,*f,*g,*h;
 if(!a)CError_Internal(filename,1076);
 switch(a->kind) {
 case 0:
  bitvectorinitialize(aliasScratch,n_aliases,0);fn_0059fee0(a,aliasScratch);setaliasbit(a,aliasScratch);fn_00599360(a,value);
  for(e=a->incoming;e;e=e->nextIncoming) {
   if(e->owner->kind!=2)CError_Internal(filename,1095);
   fn_0059fda0(a,aliasScratch,e->owner,0);
  }
  break;
 case 1:
  bitvectorinitialize(aliasScratch,n_aliases,0);setaliasbit(a,aliasScratch);fn_00599360(a,value);
  for(e=a->incoming;e;e=e->nextIncoming) {
   if(!aliasbit(e->owner,aliasScratch)) {
    setaliasbit(e->owner,aliasScratch);fn_00599360(e->owner,0);
    if(e->owner->kind==0) {
     for(f=e->owner->outgoing;f;f=f->nextOutgoing)if(f->target!=a && overlap(a,f->target)) {
      if(!aliasbit(f->target,aliasScratch)) {setaliasbit(f->target,aliasScratch);fn_00599360(f->target,0);}
      for(g=e->target->incoming;g;g=g->nextIncoming)if(g->owner!=e->owner)CError_Internal(filename,1129);
     }
    } else CError_Internal(filename,1135);
   }
   for(f=e->owner->incoming;f;f=f->nextIncoming) {
    if(f->owner->kind==2)fn_0059fda0(e->owner,aliasScratch,f->owner,0);
    else CError_Internal(filename,1143);
   }
  }
  break;
 case 2:
  fn_00599360(a,0);
  for(e=a->outgoing;e;e=e->nextOutgoing) {
   fn_00599360(e->target,0);
   for(f=e->target->incoming;f;f=f->nextIncoming)if(f->owner!=a)fn_00599360(f->owner,0);
   for(g=e->target->outgoing;g;g=g->nextOutgoing) {
    fn_00599360(g->target,0);
    for(h=g->target->incoming;h;h=h->nextIncoming)if(h->owner!=e->target)fn_00599360(h->owner,0);
   }
  }
 }
}
UInt8 fn_005a0170(NativeAlias *a,NativeAlias *b)
{
 UInt8 result;
 if(a->kind!=2 && b->kind!=2 && a->object!=b->object && aliasbit(a,aliasWorstCase->bits) && aliasbit(b,aliasWorstCase->bits) &&
   (((AliasObject*)a->object)->type==&aliasVirtualType || ((AliasObject*)b->object)->type==&aliasVirtualType))return 1;
 switch(a->kind*3U+b->kind) {
 case 0:return a==b;
 case 1:case 3:return fn_00455840(a->object,b->object);
 case 2:case 5:return aliasbit(a,b->bits)!=0;
 case 6:case 7:return aliasbit(b,a->bits)!=0;
 case 8:return a==b || !bitvectorintersectionisempty(a->bits,b->bits,n_aliases);
 case 4:break;
 default:CError_Internal(filename,867);return 1;
 }
 result=0;if(fn_00455840(a->object,b->object) && overlap(a,b))result=1;return result;
}
void fn_005a0370(void)
{
 NativeAlias *a;NativeAliasEdge *e,*f;
 if(n_gathered_aliases!=n_aliases) {
  for(a=aliasList;a;a=a->next)if(a->kind==2) {
   a->bits=lalloc(((n_aliases+31)>>5)*4);bitvectorinitialize(a->bits,n_aliases,0);
   for(e=a->outgoing;e;e=e->nextOutgoing) {
    setaliasbit(e->target,a->bits);
    for(f=e->target->outgoing;f;f=f->nextOutgoing)setaliasbit(f->target,a->bits);
   }
  }
  n_gathered_aliases=n_aliases;aliasScratch=lalloc(((n_aliases+31)>>5)*4);
 }
}
static inline UInt32 hash_alias(AliasObject *o,SInt32 offset,SInt32 size)
{
 if(!size)size=o->type->size;
 return (UInt32)(*(SInt16*)((char*)o->name+8)*((UInt32)offset+1U)*(UInt32)size)%2039U;
}
static inline NativeAlias *create_alias(AliasObject *o,SInt32 offset,SInt32 size,UInt8 kind)
{
 NativeAlias *a=lalloc(46);memclrw(a,46);a->kind=kind;a->index=n_aliases++;a->next=aliasList;aliasList=a;a->object=o;a->offset=offset;a->size=size;return a;
}
UInt8 is_safe_const(AliasObject *o)
{
 AliasType *type=o->type;signed char kind;
 while(type->kind==13)type=type->element;
 kind=Registers_ClassForType(type);
 if(kind!=-2 || type->kind==5)return fn_004531a0(o);
 if(type->kind==6)return fn_004531a0(o) && fn_00542360(type);
 return 0;
}
NativeAlias *fn_005a05d0(void *object,SInt32 offset,SInt32 size)
{
 AliasObject *o=object;NativeAlias *a,*whole;UInt32 hash;
 if(!o)CError_Internal(filename,404);
 if(!size) {offset=0;size=o->type->size;}
 hash=hash_alias(o,offset,size);
 for(a=alias_hash[hash];a;a=a->hashNext)if(fn_00455840(a->object,o) && a->offset==offset && a->size==size)break;
 if(!a) {
  if(offset<1 && size==o->type->size) {
   a=create_alias(o,offset,size,0);hash=hash_alias(o,offset,size);a->hashNext=alias_hash[hash];alias_hash[hash]=a;
  } else {
   whole=fn_005a05d0(o,0,o->type->size);a=create_alias(o,offset,size,1);hash=hash_alias(o,offset,size);a->hashNext=alias_hash[hash];alias_hash[hash]=a;fn_005a04c0(whole,a);
  }
  if(o->datatype!=1 && !is_safe_const(o)) {
   if(o->type==&aliasVirtualType || (o->datatype==0 && o->aliased))fn_005a04c0(localWorstCase,fn_005a05d0(o,0,0));
   else fn_005a04c0(aliasWorstCase,fn_005a05d0(o,0,0));
  }
 }
 if((o->type->kind!=13 || o->type->size>0) && o->type->size<(SInt32)((UInt32)offset+size)) {
  fn_005a04c0(aliasWorstCase,fn_005a05d0(o,0,0));return aliasWorstCase;
 }
 return a;
}
void initialize_aliases(void)
{
 SInt32 i;NativeAlias *a;
 memclrw(&worst_case_obj,96);worst_case_obj.kind=5;worst_case_obj.type=&worst_case_memory_type;worst_case_obj.datatype=0;worst_case_obj.name=GetHashNameNode(worst_case_name);
 alias_external_option=0;aliasList=0;temp_alias_links=0;n_aliases=0;n_gathered_aliases=0;
 for(i=0;i<2039;i++)alias_hash[i]=0;
 a=create_alias(0,0,0,2);unknownAlias=a;
 a=create_alias(0,0,0,2);aliasWorstCase=a;fn_005a04c0(aliasWorstCase,fn_005a05d0(&worst_case_obj,0,0));
 a=create_alias(0,0,0,2);localWorstCase=a;fn_005a04c0(localWorstCase,fn_005a05d0(&worst_case_obj,0,0));
 fn_005a0370();
}
void fn_005a0b80(NativeAlias *a)
{
 NativeAliasEdge *e;AliasObject *o;
 if(a->kind==2)for(e=a->outgoing;e;e=e->nextOutgoing)fn_005a0b80(e->target);
 else if(a->kind<2) {
  o=a->object;
  if(o->datatype==1)fn_005a04c0(aliasWorstCase,fn_005a05d0(o,0,0));
  else if((o->type==&aliasVirtualType || (o->datatype==0 && o->aliased)) && !is_safe_const(o))fn_005a04c0(aliasWorstCase,fn_005a05d0(a->object,0,0));
 } else CError_Internal(filename,285);
}
NativeAlias *fn_005a0cb0(AliasObject *o)
{
 AliasType *type=o->type;UInt8 unsafe=0,qualifier=0;AliasObject *virtual;NativeAlias *a;UInt32 flags;
 if(type->kind!=12 && type->kind!=13)return 0;
 flags=fn_004533f0(o->type,o->qualifiers);
 if(!(flags&0x200000)) {
  if(!fn_00453290(type->element,o->qualifiers))unsafe=1;
  else {if(type->kind==6 && !fn_00542360(type))unsafe=1;qualifier=1;}
 }
 {void *name=CParser_GetUniqueName();virtual=lalloc(96);memclrw(virtual,96);virtual->kind=5;virtual->type=&aliasVirtualType;virtual->datatype=0;virtual->name=name;}
 if(qualifier)virtual->qualifiers=1;
 a=fn_005a05d0(virtual,0x7fffff,1);if(unsafe)fn_005a04c0(aliasWorstCase,a);return a;
}
UInt8 fn_005a0d90(NativeAlias *a)
{
 if(a->kind==2)return 1;
 if(((AliasObject*)a->object)->type==&aliasVirtualType && aliasbit(a,aliasWorstCase->bits))return 1;
 return 0;
}
UInt8 fn_005a0de0(NativeAlias *a) {if(((AliasObject*)a->object)->type!=&aliasVirtualType)return 0;return 1;}
