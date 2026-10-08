/* Native GC 3.0a5.2 type utilities. Native structures are packed to two bytes. */
typedef unsigned char U8;
typedef signed char S8;
typedef unsigned short U16;
typedef short S16;
typedef unsigned long U32;
typedef long S32;
#pragma pack(push, 2)
typedef struct Type { S8 kind; U8 reserved; S32 size; } Type;
typedef struct TypeBitfield { Type base; Type *element; U8 reserved, width; } TypeBitfield;
typedef struct TypePointer { Type base; Type *target; U32 quals; } TypePointer;
typedef struct TypeArray { Type base; Type *element; U32 quals; S32 count; U8 unknown; } TypeArray;
typedef struct TypeFunction { Type base; void *args; Type *result; U32 quals; void *owner; U32 flags; U16 attrs; } TypeFunction;
typedef struct Node { struct Node *next; Type *type; U32 a, b, c; } Node;
typedef struct Member { U32 reserved; struct Member *next; U32 a; Type *type; U32 b, c; } Member;
typedef struct TypeRecord { Type base; void *name; void *members; U16 tag; U8 unused[2]; U8 flags; } TypeRecord;
typedef struct TypeClass { Type base; U32 reserved; void *name; U8 gap[8]; Member *members; U8 gap2[8]; U32 flags; U8 gap3[4]; U16 tag; } TypeClass;
typedef struct Object { U8 prefix[16]; Type *type; U32 quals; } Object;
typedef struct EnumItem { U16 reserved; struct EnumItem *next; void *name; U32 reserved2; U32 high, low; } EnumItem;
typedef struct Int64 { U32 hi, lo; } Int64;
#pragma pack(pop)
extern void *galloc(U32);
extern void memclrw(void *, U32);
extern void CError_Internal(char *, int);
extern void fn_0045c480(int, ...);
extern void fn_0045c2c0(int, ...);
extern void fn_0045a320(int, ...);
extern void fn_0045a490(Type *);
extern void fn_0045a010(U32);
extern U32 fn_004533f0(Type *, U32);
extern S16 is_typesame(Type *, Type *);
extern U8 fn_00454e40(void *, void *);
extern U8 fn_00454700(void *, void *);
extern U8 fn_005d87a0(Type *);
extern U8 fn_00542350(Type *);
extern U8 fn_00542340(Type *);
extern Node *fn_00542420(Type *);
extern U8 CInt64_GreaterU(Int64, Int64);
extern U8 CInt64_NotEqual(Int64, Int64);
extern Type stsignedchar, stunsignedchar, stlong, stunsignedlong, stlonglong, type_00699c64;
extern Type stfloat, stdouble, stlongdouble, type_00725d96;
extern U8 option_0070f1af, option_0070f1a8, option_0070f1ca, option_0070f22d;
extern U8 option_0070f1ee, option_0070f212, option_0070f1b3, option_0070f1da;
static char filename[] = "CTypeTools.c";
U8 CTTool_CanCreateTypeInstance(Type *);
int fn_00545210(U32);
U32 fn_00545320(int);
U8 fn_00545040(Type *);
void fn_005454e0(Type *, Type **, U8 *);

/* Native bitfield constructor; separate signed width rules for zero-width fields. */
Type *fn_00544300(Type *t, S32 width, U8 allow_zero) {
    S32 bits; TypeBitfield *r;
    if (t->kind != 1 && t->kind != 4) goto invalid;
    if (option_0070f1af && !option_0070f1a8 && t != &stlong && t != &stunsignedlong && !(option_0070f1ca && t == &stsignedchar)) goto invalid;
    if (t->size == stlonglong.size && stlonglong.size > type_00699c64.size && !option_0070f22d) goto invalid;
    bits = t->size * 8;
    goto check;
invalid:
    fn_0045c480(0x279a, t, 0);
    bits = stunsignedlong.size * 8;
    t = &stunsignedlong;
check:
    if (allow_zero) { if (width >= 0 && width <= bits) goto allocate; }
    else { if (width > 0 && width <= bits) goto allocate; }
badwidth: {
        fn_0045c480(0x28eb, width); width = 1;
    }
allocate:
    r = galloc(12); memclrw(r, 12); r->base.kind = 8; r->base.size = t->size; r->element = t; r->width = (U8)width;
    return (Type *)r;
}
void *CDecl_NewTemplDepType(U8 kind) {
    U8 *t = galloc(16); memclrw(t, 16); ((Type *)t)->kind = 10; ((Type *)t)->size = 1; t[6] = kind; return t;
}
Type *fn_00544430(Type *a, Type *b) {
    Type *target;
    TypePointer *p;
    if (option_0070f1ee && b->kind == 12 && b->kind == 12 && (((TypePointer *)b)->quals & 0xa0) == 0x20 &&
        !(a->kind == 12 && a->kind == 12 && (((TypePointer *)a)->quals & 0xa0) == 0x20)) {
        target = ((TypePointer *)b)->target;
        p = galloc(14); memclrw(p, 14); p->base.kind = 12; p->base.size = 4; p->target = target; p->quals = 0x20; return (Type *)p;
    }
    return b;
}
Type *fn_005444c0(Type *target) {
    TypePointer *p = galloc(14); memclrw(p, 14); p->base.kind = 12; p->base.size = 4; p->target = target; p->quals = 0x20; return (Type *)p;
}
TypePointer *CTTool_CopyTypePointer(TypePointer *p) { TypePointer *r = galloc(14); *r = *p; return r; }
Type *CDecl_NewPointerType(Type *target) {
    TypePointer *p = galloc(14); memclrw(p, 14); p->base.kind = 12; p->base.size = 4; p->target = target; return (Type *)p;
}
Type *CDecl_NewArrayType(Type *element, S32 size) {
    TypeArray *p = galloc(20); memclrw(p, 20); p->base.kind = 13; p->base.size = size; p->element = element; p->count = element->size ? size / element->size : 0; return (Type *)p;
}
Type *CDecl_NewOpaqueType(S32 size, S16 alignment) {
    U8 *p = galloc(18); memclrw(p, 18); ((Type *)p)->kind = 5; ((Type *)p)->size = size; *(S16 *)(p + 14) = alignment; p[16] = 0; return (Type *)p;
}
S32 fn_005445e0(S32 a, S32 b) {
    unsigned long long n;
    if (a >= 0 && b >= 0) {
        n = (unsigned long long)(U32)a * (U32)b;
        if(n <= 0x7fffffff)return (S32)n;
    }
    fn_0045c480(0x2900, 0x7fffffff);return 1;
}
S32 fn_00544620(Int64 value) {
    Int64 limit; limit.lo = 0x7fffffff; limit.hi = 0;
    if (CInt64_GreaterU(value, limit)) { fn_0045c480(0x2900, 0x7fffffff); return 1; }
    return value.lo;
}
U8 CTTool_DataObjectTypeCompare(Object *obj, Type *t, U32 quals) {
    if ((obj->quals & 0xb) != (quals & 0xb)) return 0;
    if (t->kind == 13 && obj->type->kind == 13) {
        if (((TypeArray *)t)->count && ((TypeArray *)obj->type)->count) {
            if (!is_typesame(t, obj->type)) return 0;
        } else if (!is_typesame(((TypePointer *)t)->target, ((TypePointer *)obj->type)->target)) return 0;
        if (!obj->type->size) obj->type = t;
        return 1;
    }
    return (U8)is_typesame(t, obj->type);
}
/* Structural compatibility, including packed enum/record/class member lists. */
U8 fn_00544710(Type *a, Type *b) {
    for (;;) {
        if (a == b) return 1;
        if (a->kind != b->kind || a->size != b->size) return 0;
        switch (a->kind) {
        case 0: case 1: case 2: case 3: return 0;
        case 12:
            if ((((TypePointer *)a)->quals & 0x200023) != (((TypePointer *)b)->quals & 0x200023)) return 0;
            a = ((TypePointer *)a)->target; b = ((TypePointer *)b)->target; continue;
        case 13:
            if (((TypeArray *)a)->unknown || ((TypeArray *)b)->unknown || ((TypeArray *)a)->count != ((TypeArray *)b)->count) return 0;
            a = ((TypePointer *)a)->target; b = ((TypePointer *)b)->target; continue;
        case 11:
            if (!is_typesame(((TypeFunction *)a)->result, ((TypeFunction *)b)->result) || (((TypeFunction *)a)->quals & 0x200023) != (((TypeFunction *)b)->quals & 0x200023)) return 0;
            return fn_00454e40(((TypeFunction *)a)->args, ((TypeFunction *)b)->args);
        case 7:
            if (!is_typesame(*(Type **)((U8 *)a+14), *(Type **)((U8 *)b+14)) || *(U32 *)((U8 *)a+18) != *(U32 *)((U8 *)b+18) || (*(U32 *)((U8 *)a+22)&0x18001) != (*(U32 *)((U8 *)b+22)&0x18001) || (*(U16 *)((U8 *)a+26)&0xf000) != (*(U16 *)((U8 *)b+26)&0xf000)) return 0;
            return fn_00454700(*(void **)((U8 *)a+6), *(void **)((U8 *)b+6));
        case 4: {
            EnumItem *x, *y;
            if (*(U32 *)((U8 *)a+14) != *(U32 *)((U8 *)b+14)) return 0;
            x=*(EnumItem **)((U8 *)a+10); y=*(EnumItem **)((U8 *)b+10);
            while (x) { Int64 p,q; if (!y || x->name != y->name) return 0; p.hi=x->high;p.lo=x->low;q.hi=y->high;q.lo=y->low;if(CInt64_NotEqual(p,q))return 0; x=x->next;y=y->next; }
            return y==0;
        }
        case 5: {
            Node *x,*y;
            if (*(void **)((U8 *)a+6) != *(void **)((U8 *)b+6) || *(U16 *)((U8 *)a+14) != *(U16 *)((U8 *)b+14)) return 0;
            x=*(Node **)((U8 *)a+10);y=*(Node **)((U8 *)b+10);
            while(x) { if(!y || x->a!=y->a || x->b!=y->b || x->c!=y->c || x->type->kind != y->type->kind || x->type->size != y->type->size) return 0;x=x->next;y=y->next; } return y==0;
        }
        case 6: {
            Member *x,*y;
            if (*(void **)((U8 *)a+10) != *(void **)((U8 *)b+10) || *(U16 *)((U8 *)a+42) != *(U16 *)((U8 *)b+42) || !(*(U32 *)((U8 *)a+34)&0x200000) || !(*(U32 *)((U8 *)b+34)&0x200000)) return 0;
            x=*(Member **)((U8 *)a+22);y=*(Member **)((U8 *)b+22);
            while(x) { if(!y || x->a!=y->a || x->c!=y->c || x->b!=y->b || x->type->kind!=y->type->kind || x->type->size!=y->type->size) return 0; x=x->next;y=y->next; } return y==0;
        }
        default: CError_Internal(filename, 786); return 0;
        }
    }
}
void fn_00544a80(U8 *state, Type *original, U32 quals) {
    Type *t=original,*base;
    Node *n;
    if (t->kind==12 && (((TypePointer *)t)->quals&0x20)) t=((TypePointer *)t)->target;
    if(t==&type_00725d96) fn_0045c2c0(0x278e,t,quals);
    fn_0045a010(fn_004533f0(t,quals)&0xe0cfff7c);
    if(state[46]!=1 || !option_0070f212)return;
    base=original;
    if(!option_0070f1b3 && original->kind==12 && (((TypePointer *)original)->quals&0x20))fn_0045c2c0(0x28a0);
    while(base->kind==13)base=((TypePointer *)base)->target;
    if(base->kind!=6)return;
    if(!fn_00542350(base) || !fn_00542340(base)){fn_0045a320(0x28a2);return;}
    for(n=fn_00542420(base);n;n=n->next)if(n->type->kind==5 && (*(Type **)((U8 *)n->type+16))->kind==7 && (*(U32 *)((U8 *)*(Type **)((U8 *)n->type+16)+22)&0x100)){fn_0045a320(0x28a2);break;}
}
U8 fn_00544b90(Type *t) {
    if(t->kind!=6)goto other;
    if(((TypeClass *)t)->flags&2)goto complete;
    if((((TypeClass *)t)->flags&0x800) && fn_005d87a0(t))goto complete;
    fn_0045c480(0x2798,t,0);return 0;
complete:
    if(((TypeClass *)t)->flags&8){fn_0045a490(t);return 0;}
    return 1;
other:
    return CTTool_CanCreateTypeInstance(t);
}
U8 CTTool_CanCreateTypeInstance(Type *t) {
    Type *base=t; U32 flags;
    while(base->kind==13)base=((TypePointer *)base)->target;
    switch(base->kind){
    case 0:case 7:fn_0045c480(0x278e,t,0);return 0;
    case 5:if(base->size || (((U8 *)base)[17]&1))return 1;fn_0045c480(0x2798,base,0);return 0;
    case 6:
        flags=*(U32 *)((U8 *)base+34);
        if(!(flags&2) && (!(flags&0x800)||!fn_005d87a0(base))){fn_0045c480(0x2798,base,0);return 0;}
        flags=*(U32 *)((U8 *)base+34);
        if(flags&8){fn_0045a490(base);return 0;}
        if(flags&1){fn_0045c480(0x27cf);return 0;}return 1;
    default:if(t->size || (t->kind==13 && ((TypeArray *)t)->unknown))return 1;fn_0045c480(0x27a1);return 0;
    }
}
/* Native completeness check; report controls diagnostics, not the result. */
U8 fn_00544d00(Type *t,U8 report) {
    U32 flags;
    if(report && !option_0070f1da && fn_00545040(t))fn_0045a320(0x2928);
    switch(t->kind){
    case -2:case -1:case 1:case 2:case 3:case 4:case 10:case 11:case 14:return 1;
    case 0:case 7:if(report)fn_0045c480(0x278e,t,0);return 0;
    case 5:if(t->size || (((U8 *)t)[17]&1))return 1;if(report)fn_0045c480(0x2798,t,0);return 0;
    case 6:
        flags=*(U32 *)((U8 *)t+34);
        if(!(flags&2) && (!(flags&0x800)||!fn_005d87a0(t))){if(report)fn_0045c480(0x2798,t,0);return 0;}
        flags=*(U32 *)((U8 *)t+34);
        if(flags&8){if(report)fn_0045a490(t);return 0;}
        if(flags&1){if(report)fn_0045c480(0x27cf);return 0;}return 1;
    case 13:if(((TypeArray *)t)->unknown || t->size)return 1;if(report)fn_0045c480(0x27a1);return 0;
    case 12:if(((TypePointer *)t)->quals&0x20){if(report)fn_0045c2c0(0x27d4,t,0);return 0;}return 1;
    default:CError_Internal(filename,494);return 0;
    }
}
void fn_00544f00(Type *original,U32 quals) {
    Type *t=original;
    if(t->kind==12 && (((TypePointer *)t)->quals&0x20))t=((TypePointer *)t)->target;
    if(t==&type_00725d96)fn_0045c2c0(0x278e,t,quals);
    fn_0045a010(fn_004533f0(t,quals)&0xe0cffffc);
}
void fn_00544f60(Type *t,U32 quals) {
    if(t->kind==12 && (((TypePointer *)t)->quals&0x20))t=((TypePointer *)t)->target;
    if(t==&type_00725d96)fn_0045c2c0(0x278e,t,quals);
    fn_0045a010(fn_004533f0(t,quals)&0xe0cfff7c);
}
void CTTool_CheckLocalType(Type *t,U32 quals) {
    if(t->kind==12 && (((TypePointer *)t)->quals&0x20))t=((TypePointer *)t)->target;
    if(t==&type_00725d96)fn_0045c2c0(0x278e,t,quals);
    fn_0045a010(fn_004533f0(t,quals)&0xe0cffffc);
}
void fn_00545020(Type *t,U32 quals){fn_0045a010(quals&0xe0e9fff4);}
U8 fn_00545040(Type *t) {
    Node *n;Member *m;
    if(t->kind==5){for(n=*(Node **)((U8 *)t+10);n;n=n->next)if(!n->type->size && n->type->kind==13)return 1;}
    else if(t->kind==6){for(m=*(Member **)((U8 *)t+22);m;m=m->next)if(!m->type->size && m->type->kind==13)return 1;}
    return 0;
}
U32 CTTool_CombineQuals(U32 a,U32 b) {
    U32 q;int x,y;
    if(a&0x10000000){if(b&0x10000000){x=fn_00545210(a);y=fn_00545210(b);q=fn_00545320(x>y?y:x)|0x10000000;}else q=a&0x1f000000;}
    else if(b&0x10000000)q=b&0x1f000000;
    else {x=fn_00545210(a);if(!x)q=b&0x1f000000;else {y=fn_00545210(b);if(y)q=fn_00545320(x<y?y:x);else q=a&0x1f000000;}}
    return ((a|b)&0xe0ffffff)|q;
}
U32 CTTool_CombineAlignmentQuals(U32 a,U32 b) {
    int x,y;
    if(a&0x10000000){if(!(b&0x10000000))return a&0x1f000000;x=fn_00545210(a);y=fn_00545210(b);return fn_00545320(x>y?y:x)|0x10000000;}
    if(b&0x10000000)return b&0x1f000000;
    x=fn_00545210(a);if(!x)return b&0x1f000000;
    y=fn_00545210(b);if(y)return fn_00545320(x<y?y:x);return a&0x1f000000;
}
int fn_00545210(U32 quals) {
    switch(quals&0xf000000){case 0:return (quals&0x10000000)?1:0;
    case 0x1000000: return 1;
    case 0x2000000: return 2;
    case 0x3000000: return 4;
    case 0x4000000: return 8;
    case 0x5000000: return 16;
    case 0x6000000: return 32;
    case 0x7000000: return 64;
    case 0x8000000: return 128;
    case 0x9000000: return 256;
    case 0xa000000: return 512;
    case 0xb000000: return 1024;
    case 0xc000000: return 2048;
    case 0xd000000: return 4096;
    case 0xe000000: return 8192;
    default:CError_Internal(filename,233);return 0;}
}
U32 fn_00545320(int alignment) {
    switch(alignment){
    case 1:return 0x1000000;
    case 2:return 0x2000000;
    case 4:return 0x3000000;
    case 8:return 0x4000000;
    case 16:return 0x5000000;
    case 32:return 0x6000000;
    case 64:return 0x7000000;
    case 128:return 0x8000000;
    case 256:return 0x9000000;
    case 512:return 0xa000000;
    case 1024:return 0xb000000;
    case 2048:return 0xc000000;
    case 4096:return 0xd000000;
    case 8192:return 0xe000000;
    default:fn_0045c480(0x2927);return 0;}
}
/* These native complex-type stubs deliberately retain their assertion paths. */
int fn_00545400(Type *a,Type *b) {
    Type *x,*y;U8 cx,cy;U8 bad;
    if(a==b)return (int)a;
    if(a->kind==3){fn_005454e0(a,&x,&cx);if(b->kind==3){fn_005454e0(b,&y,&cy);bad=cx!=0 || cy!=0;}else bad=1;}
    else {fn_005454e0(b,&y,&cy);bad=1;}
    if(bad)CError_Internal(filename,88);else CError_Internal(filename,108);return 0;
}
int fn_005454a0(void){CError_Internal(filename,108);return 0;}
int fn_005454c0(void){CError_Internal(filename,88);return 0;}
void fn_005454e0(Type *t,Type **real,U8 *complex) {
    switch(((U8 *)t)[6]){
    case 17:*real=&stfloat;*complex=0;break;
    case 18:*real=&stdouble;*complex=0;break;
    case 19:*real=&stlongdouble;*complex=0;break;
    case 20:*real=&stfloat;*complex=1;break;
    case 21:*real=&stdouble;*complex=1;break;
    case 22:*real=&stlongdouble;*complex=1;break;
    default:CError_Internal(filename,74);break;
    }
}
void CTTool_Cleanup(void){}
void CTTool_Setup(void){}
