/* Native type and namespace stream records; review is recorded in the TU ledger. */
#include <stddef.h>

typedef unsigned char Byte;
typedef unsigned int Word;
typedef struct CIRType CIRType;
typedef struct CIRNamespace CIRNamespace;
#pragma pack(push, 2)
struct CIRType { signed char kind; Byte reserved; int size; };
struct CIRNamespace { CIRNamespace *parent; void *name; Word unknown08; CIRType *type; };
typedef struct CIRList { struct CIRList *next; void *value; } CIRList;
typedef struct CIRReference { struct CIRReference *next; CIRType **slot; } CIRReference;
typedef struct CIRExport { struct CIRExport *next; CIRType *type; Byte kind, unknown09[3]; Word index; } CIRExport;
typedef struct CIRNamespaceRef { struct CIRNamespaceRef *next; CIRNamespace *scope; Word index; } CIRNamespaceRef;
typedef struct CIRHashEntry { Word unknown00, unknown04, index; } CIRHashEntry;
typedef struct CIRObject { Byte kind, flags; void *value; } CIRObject;
typedef struct CIRWordView { Word value; } CIRWordView;
typedef struct CIRIntView { int value; } CIRIntView;
typedef struct CIRPointerView { void *value; } CIRPointerView;
typedef struct CIRTypePointerView { CIRType *value; } CIRTypePointerView;
#pragma pack(pop)
typedef char CheckType[(sizeof(CIRType)==6)?1:-1];
typedef char CheckNamespace[(sizeof(CIRNamespace)==16)?1:-1];
typedef char CheckExport[(sizeof(CIRExport)==16)?1:-1];
typedef char CheckObject[(sizeof(CIRObject)==6)?1:-1];

/* These native views preserve the distinct packed record layouts. */
#define U(p,n) (((CIRWordView *)((Byte *)(p)+(n)))->value)
#define I(p,n) (((CIRIntView *)((Byte *)(p)+(n)))->value)
#define H(p,n) (*(unsigned short *)((Byte *)(p)+(n)))
#define S(p,n) (*(short *)((Byte *)(p)+(n)))
#define B(p,n) (*((Byte *)(p)+(n)))
#define C(p,n) (*((signed char *)(p)+(n)))
#define P(p,n) (((CIRPointerView *)((Byte *)(p)+(n)))->value)
#define T(p,n) (((CIRTypePointerView *)((Byte *)(p)+(n)))->value)

extern void *galloc(int), *CompilerTools_AllocatePool(int), *fn_0046c730(int);
extern void fn_0046c6e0(void *, int), memclrw(void *, int);
extern int CError_Internal(const char *, int);
extern void CError_Warning(int, ...), fn_00462e30(void);
extern CIRType *fn_004e2290(Word);
extern Byte *fn_005c9340(Byte *, void *), *fn_005c9490(Byte *, void *, signed char);
extern Byte *fn_005c95c0(Byte *, void *, int), *fn_005c9600(Byte *, void *), *fn_005c9690(Byte *, void *);
extern Byte *fn_005c9720(Byte *, void *), *fn_005c9760(Byte *, void *);
extern void fn_005c93e0(void *), fn_005c9530(void *), fn_005c95e0(void *, int);
extern void fn_005c9640(Word), fn_005c96d0(int), fn_005c9740(unsigned short), fn_005c9780(short), fn_005c97a0(signed char);
extern Word fn_005441e0(CIRType *);
extern CIRHashEntry *fn_00544180(void *, CIRType *, Word);
extern void fn_00544130(void *, CIRType *, Word, Word);
extern signed char fn_00544710(CIRType *, CIRType *), CParser_IsNullOrAtOrDollarPrefixedName(void *);
extern CIRList *fn_004eb0d0(CIRNamespace *, void *), *fn_004eaff0(CIRNamespace *, void *);
extern CIRNamespace *CScope_NewListNameSpace(void *, signed char);
extern void CScope_AddObject(CIRNamespace *, void *, CIRObject *);
extern CIRNamespace *CScope_NewHashNameSpace(void *);
extern void *GetHashNameNode(void *), *fn_0045ef20(CIRType *, int);
extern void *fn_005c92e0(CIRType *);
extern void fn_005c9310(CIRType *);
extern Byte cirBuiltinTypes[], cirVectorTypes[];
extern CIRType cirVoidType, cirUnknownType;
extern Byte cirEllipsisArgument[], cirVoidArgument[];
extern CIRType **cirReadTypes;
extern Word cirNextTypeIndex, cirNextExportIndex, cirStreamSize, cirNextNamespaceIndex;
extern Byte *cirImportContext;
extern signed char cirWriteTypes;
extern CIRExport *cirExports;
extern Byte cirTypeHashTable[];
extern CIRNamespaceRef *cirNamespaceRefs;
extern CIRNamespace *cirGlobalNamespace;
extern CIRList *cirAnonymousTypes;
extern void *cirCurrentSource;

/* Only the two native discard slots are private to this supported cluster. */
CIRType *cirDiscardStructType;
CIRType *cirDiscardClassType;
static char cirTypeFilename[] = "CIRStreamType.c";
static Byte cirUnknownFile[] = "<unknown file>";

Byte *fn_005c97c0(Byte *, CIRType **);
void fn_005c9cd0(CIRType *);
Word fn_005c9e70(CIRType *);
Byte *fn_005ca0c0(Byte *, CIRType *);
Word fn_005ca220(CIRType *);
Byte *fn_005ca390(Byte *, CIRType **);
Word fn_005ca9f0(CIRType *);
Byte *fn_005cac20(Byte *, CIRType **);
Word fn_005cafd0(CIRType *);
Byte *fn_005cb130(Byte *, CIRType **);
Word fn_005cb430(CIRType *);
Byte *fn_005cb500(Byte *, CIRNamespace **);
void fn_005cb6e0(CIRNamespace *);

Byte *fn_005c97c0(Byte *cursor, CIRType **out)
{
    Word index;
    CIRType *type;
    CIRReference *reference;
    cursor = fn_005c9600(cursor, &index);
    if (index < 56) {
        switch (index) {
            case 0: *out = (CIRType *)(cirBuiltinTypes + 0*8); break;
            case 1: *out = (CIRType *)(cirBuiltinTypes + 1*8); break;
            case 2: *out = (CIRType *)(cirBuiltinTypes + 2*8); break;
            case 3: *out = (CIRType *)(cirBuiltinTypes + 3*8); break;
            case 4: *out = (CIRType *)(cirBuiltinTypes + 4*8); break;
            case 5: *out = (CIRType *)(cirBuiltinTypes + 5*8); break;
            case 6: *out = (CIRType *)(cirBuiltinTypes + 6*8); break;
            case 7: *out = (CIRType *)(cirBuiltinTypes + 7*8); break;
            case 8: *out = (CIRType *)(cirBuiltinTypes + 8*8); break;
            case 9: *out = (CIRType *)(cirBuiltinTypes + 9*8); break;
            case 10: *out = (CIRType *)(cirBuiltinTypes + 10*8); break;
            case 11: *out = (CIRType *)(cirBuiltinTypes + 11*8); break;
            case 12: *out = (CIRType *)(cirBuiltinTypes + 12*8); break;
            case 13: *out = (CIRType *)(cirBuiltinTypes + 13*8); break;
            case 14: *out = (CIRType *)(cirBuiltinTypes + 14*8); break;
            case 15: *out = (CIRType *)(cirBuiltinTypes + 15*8); break;
            case 16: *out = (CIRType *)(cirBuiltinTypes + 16*8); break;
            case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
                *out = fn_004e2290(index); break;
            case 31: *out = 0; break;
            case 32: *out = &cirVoidType; break;
            case 33: *out = &cirUnknownType; break;
            case 34:
                cursor = fn_005c9600(cursor, &index);
                if (U(cirImportContext,20) < index || B(cirImportContext,30+index*8) != 0)
                    CError_Internal(cirTypeFilename, 1702);
                *out = T(cirImportContext,26+index*8); break;
            case 35:
                type = galloc(14); memclrw(type,14); *out = type;
                cirReadTypes[cirNextTypeIndex++-56] = type; type->kind = 12;
                cursor = fn_005c97c0(cursor, (CIRType **)((Byte *)type+6));
                type->size = 4; return cursor;
            case 36:
                type = galloc(14); memclrw(type,14); *out = type;
                cirReadTypes[cirNextTypeIndex++-56] = type; type->kind = 12;
                cursor = fn_005c9600(cursor, (Byte *)type+10);
                cursor = fn_005c97c0(cursor, (CIRType **)((Byte *)type+6));
                type->size = 4; return cursor;
            case 37:
                type = galloc(20); memclrw(type,20); *out = type;
                cirReadTypes[cirNextTypeIndex++-56] = type; type->kind = 13;
                cursor = fn_005c9690(cursor, (Byte *)type+2);
                cursor = fn_005c97c0(cursor, (CIRType **)((Byte *)type+6));
                cursor = fn_005c9600(cursor, (Byte *)type+10);
                cursor = fn_005c9690(cursor, (Byte *)type+14);
                B(type,18) = cursor[0]; B(type,19) = cursor[1]; return cursor+2;
            case 38: return fn_005cb130(cursor,out);
            case 39: return fn_005cac20(cursor,out);
            case 40: return fn_005ca390(cursor,out);
            case 41:
                type = galloc(30); memclrw(type,30); *out = type;
                return fn_005ca0c0(cursor,type);
            case 42:
                type = galloc(44); memclrw(type,44); *out = type;
                cursor = fn_005ca0c0(cursor,type);
                cursor = fn_005c97c0(cursor,(CIRType **)((Byte *)type+30));
                cursor = fn_005c9690(cursor,(Byte *)type+34);
                B(type,42) = *cursor; return cursor+1;
            case 43:
                type = galloc(18); memclrw(type,18); *out = type;
                cirReadTypes[cirNextTypeIndex++-56] = type; type->kind = 11;
                cursor = fn_005c9690(cursor,(Byte *)type+2);
                cursor = fn_005c97c0(cursor,(CIRType **)((Byte *)type+6));
                cursor = fn_005c97c0(cursor,(CIRType **)((Byte *)type+10));
                return fn_005c9600(cursor,(Byte *)type+14);
            case 44:
                type = galloc(12); memclrw(type,12); *out = type;
                cirReadTypes[cirNextTypeIndex++-56] = type; type->kind = 8;
                cursor = fn_005c97c0(cursor,(CIRType **)((Byte *)type+6));
                type->size = T(type,6)->size;
                B(type,10) = cursor[0]; B(type,11) = cursor[1]; return cursor+2;
            case 45: *out = (CIRType *)(cirVectorTypes+0*18); break;
            case 46: *out = (CIRType *)(cirVectorTypes+1*18); break;
            case 47: *out = (CIRType *)(cirVectorTypes+2*18); break;
            case 48: *out = (CIRType *)(cirVectorTypes+3*18); break;
            case 49: *out = (CIRType *)(cirVectorTypes+4*18); break;
            case 50: *out = (CIRType *)(cirVectorTypes+5*18); break;
            case 51: *out = (CIRType *)(cirVectorTypes+6*18); break;
            case 52: *out = (CIRType *)(cirVectorTypes+7*18); break;
            case 53: *out = (CIRType *)(cirVectorTypes+8*18); break;
            case 54: *out = (CIRType *)(cirVectorTypes+9*18); break;
            case 55: *out = (CIRType *)(cirVectorTypes+10*18); break;
            default: CError_Internal(cirTypeFilename,1751); break;
        }
        return cursor;
    }
    if (cirNextTypeIndex <= index) CError_Internal(cirTypeFilename,1636);
    *out = cirReadTypes[index-56];
    if (!*out) CError_Internal(cirTypeFilename,1637);
    if ((*out)->kind == -2) {
        reference = CompilerTools_AllocatePool(8);
        reference->next = P(*out,6); reference->slot = out; P(*out,6) = reference;
    }
    return cursor;
}

void fn_005c9cd0(CIRType *type)
{
    Word size, index;
    CIRExport *entry;
    size = cirStreamSize;
    if (cirWriteTypes) {
        index = fn_005c9e70(type);
        if (size == cirStreamSize) fn_005c9640(index);
        return;
    }
    if (!type) { fn_005c9640(31); return; }
    switch (type->kind) {
        case 0: fn_005c9640(33); return;
        case 1: case 2: case 3: fn_005c9640(B(type,6)); return;
        case 5:
            switch (B(type,16)) {
                case 4: fn_005c9640(45); return;
                case 5: fn_005c9640(46); return;
                case 6: fn_005c9640(47); return;
                case 7: fn_005c9640(48); return;
                case 8: fn_005c9640(49); return;
                case 9: fn_005c9640(50); return;
                case 10: fn_005c9640(51); return;
                case 11: fn_005c9640(52); return;
                case 12: fn_005c9640(53); return;
                case 13: fn_005c9640(54); return;
                case 14: fn_005c9640(55); return;
            }
            break;
        case -1: fn_005c9640(32); return;
    }
    for (entry = cirExports; entry; entry = entry->next)
        if (entry->type == type && entry->kind == 0) break;
    if (!entry) {
        entry = CompilerTools_AllocatePool(16); entry->next = cirExports;
        entry->index = cirNextExportIndex++; entry->kind = 0;
        entry->type = type; cirExports = entry;
    }
    fn_005c9640(34); fn_005c9640(entry->index);
}

Word fn_005c9e70(CIRType *type)
{
    Word result, hash, flags;
    CIRHashEntry *entry;
    result = cirNextTypeIndex;
    if (!type) return 31;
    switch (type->kind) {
        case 0: return 33;
        case 1: case 2: case 3: return B(type,6);
        case 4: return fn_005cb430(type);
        case 5: return fn_005cafd0(type);
        case 6: return fn_005ca9f0(type);
        case 7: return fn_005ca220(type);
        case 8:
            ++cirNextTypeIndex; fn_005c97a0(44); fn_005c9cd0(T(type,6));
            fn_005c97a0(C(type,10)); fn_005c97a0(C(type,11)); return result;
        case 11:
            hash = fn_005441e0(type); entry = fn_00544180(cirTypeHashTable,type,hash);
            result = cirNextTypeIndex;
            if (entry) return entry->index;
            ++cirNextTypeIndex; fn_00544130(cirTypeHashTable,type,hash,result);
            fn_005c97a0(43); fn_005c96d0(type->size); fn_005c9cd0(T(type,6));
            fn_005c9cd0(T(type,10)); fn_005c9640(U(type,14)); return result;
        case 12:
            hash = fn_005441e0(type); entry = fn_00544180(cirTypeHashTable,type,hash);
            result = cirNextTypeIndex;
            if (entry) return entry->index;
            ++cirNextTypeIndex; fn_00544130(cirTypeHashTable,type,hash,result);
            flags = U(type,10) & 0xffefffff;
            fn_005c97a0(flags ? 36 : 35);
            if (flags) fn_005c9640(flags);
            fn_005c9cd0(T(type,6)); return result;
        case 13:
            hash = fn_005441e0(type); entry = fn_00544180(cirTypeHashTable,type,hash);
            result = cirNextTypeIndex;
            if (entry) return entry->index;
            ++cirNextTypeIndex; fn_00544130(cirTypeHashTable,type,hash,result);
            fn_005c97a0(37); fn_005c96d0(type->size); fn_005c9cd0(T(type,6));
            fn_005c9640(U(type,10)); fn_005c96d0(I(type,14));
            fn_005c97a0(C(type,18)); fn_005c97a0(C(type,19)); return result;
        case -1: return 32;
        case 9: case 10: case 14: case 15: break;
        default: CError_Internal(cirTypeFilename,1463); break;
    }
    CError_Internal(cirTypeFilename,1469); return 33;
}

Byte *fn_005ca0c0(Byte *cursor, CIRType *type)
{
    int count;
    Byte tag;
    void **slot, *argument;
    cirReadTypes[cirNextTypeIndex++-56] = type; type->kind = 7;
    cursor = fn_005c97c0(cursor,(CIRType **)((Byte *)type+14));
    cursor = fn_005c9600(cursor,(Byte *)type+18);
    cursor = fn_005c9600(cursor,(Byte *)type+22);
    cursor = fn_005c9720(cursor,(Byte *)type+26);
    cursor = fn_005c9720(cursor,(Byte *)type+28);
    cursor = fn_005c9600(cursor,&count);
    slot = (void **)((Byte *)type+6);
    for (; count; --count) {
        tag = *cursor++; argument = slot;
        switch (tag) {
            case 0: case 1:
                argument = galloc(24); memclrw(argument,24); B(argument,22) = tag;
                cursor = fn_005c9340(cursor,(Byte *)argument+4);
                cursor = fn_005c97c0(cursor,(CIRType **)((Byte *)argument+12));
                cursor = fn_005c9600(cursor,(Byte *)argument+16);
                cursor = fn_005c9760(cursor,(Byte *)argument+20);
                *slot = argument; break;
            case 2:
                if (count != 1) CError_Internal(cirTypeFilename,1194);
                *slot = cirEllipsisArgument; break;
            case 3:
                if (count != 1) CError_Internal(cirTypeFilename,1199);
                *slot = cirVoidArgument; break;
            default: CError_Internal(cirTypeFilename,1204); break;
        }
        slot = argument;
    }
    return cursor;
}

Word fn_005ca220(CIRType *type)
{
    Word hash, index;
    CIRHashEntry *entry;
    void *argument;
    int count;
    hash = fn_005441e0(type); entry = fn_00544180(cirTypeHashTable,type,hash);
    if (entry) return entry->index;
    index = cirNextTypeIndex++;
    fn_00544130(cirTypeHashTable,type,hash,index);
    fn_00544130(cirTypeHashTable,type,hash,index);
    fn_005c97a0((U(type,22)&16)?42:41);
    fn_005c9cd0(T(type,14)); fn_005c9640(U(type,18)); fn_005c9640(U(type,22));
    fn_005c9740(H(type,26)); fn_005c9740(H(type,28));
    count = 0; for (argument=P(type,6); argument; argument=P(argument,0)) ++count;
    fn_005c9640(count);
    for (argument=P(type,6); argument; argument=P(argument,0)) {
        if (argument==cirEllipsisArgument) fn_005c97a0(2);
        else if (argument==cirVoidArgument) fn_005c97a0(3);
        else {
            fn_005c97a0(C(argument,22)!=0); fn_005c93e0(P(argument,4));
            fn_005c9cd0(T(argument,12)); fn_005c9640(U(argument,16)); fn_005c9780(S(argument,20));
        }
    }
    if (U(type,22)&16) {
        fn_005c9cd0(T(type,30)); fn_005c96d0(I(type,34)); fn_005c97a0(C(type,42));
    }
    return index;
}

Byte *fn_005ca390(Byte *cursor, CIRType **out)
{
    CIRType *type, *previous;
    CIRNamespace *scope, *newScope;
    CIRList *list, *patch, *anonymous;
    CIRObject *object;
    Byte duplicate, *record;
    void *name, *lookupName, *mangled;
    void *source, *currentFile, *previousFile;
    Word index, flags;
    int size, count, discarded;
    unsigned short discardedShort;
    void **tail;
    duplicate = 0;
    type = fn_0046c730(48); memclrw(type,48); type->kind = -2;
    cirReadTypes[cirNextTypeIndex-56] = type; index = cirNextTypeIndex++;
    cursor = fn_005c9690(cursor,&size); cursor = fn_005c9340(cursor,&name);
    cursor = fn_005cb500(cursor,&scope); cursor = fn_005c9600(cursor,&flags);
    lookupName = name;
    if (flags & 0x100000) { cursor=fn_005c9490(cursor,&mangled,0); lookupName=GetHashNameNode(mangled); }
    if (flags & 0x400) goto create_unbound;
    list = fn_004eb0d0(scope,lookupName);
    while (list && ((CIRObject *)list->value)->kind != 2) list=list->next;
    if (!list) {
        type->kind=6; type->size=size; P(type,10)=name; U(type,34)=flags;
        newScope=CScope_NewListNameSpace(lookupName,1); newScope->parent=scope; newScope->type=type; P(type,6)=newScope;
        object=galloc(6); memclrw(object,6); object->kind=2; object->flags=0; object->value=type;
        CScope_AddObject(scope,lookupName,object);
    } else {
        previous=((CIRObject *)list->value)->value;
        if (previous->kind != 6 || ((U(previous,34)&2) && (flags&2) && previous->size!=size)) goto incompatible;
        for (patch=P(type,6); patch; patch=patch->next) *(CIRType **)patch->value=previous;
        cirReadTypes[index-56]=previous; fn_0046c6e0(type,48);
        if (!(U(previous,34)&2)) {
            previous->size=size; P(previous,10)=name; U(previous,34)=flags;
        } else duplicate=1;
        type=previous;
    }
    goto selected;
incompatible:
    source=fn_005c92e0(previous); fn_00462e30();
    currentFile=cirCurrentSource ? (Byte *)P(P(cirCurrentSource,0),0)+10 : cirUnknownFile;
    previousFile=source ? (Byte *)P(P(source,0),0)+10 : cirUnknownFile;
    CError_Warning(0x2916,previous,0,previousFile,currentFile);
create_unbound:
    type->kind=6; type->size=size; P(type,10)=name; U(type,34)=flags;
    newScope=CScope_NewListNameSpace(lookupName,1); newScope->parent=scope; newScope->type=type; P(type,6)=newScope;
selected:
    *out=type; if (flags&2) fn_005c9310(type);
    if (!duplicate) {
        cursor=fn_005c9720(cursor,(Byte *)type+42); cursor=fn_005c9720(cursor,(Byte *)type+44);
        B(type,46)=cursor[0]; B(type,47)=cursor[1];
    } else {
        cursor=fn_005c9720(cursor,&discardedShort); cursor=fn_005c9720(cursor,&discardedShort);
    }
    cursor=fn_005c9600(cursor+2,&count);
    if (!duplicate) {
        tail=(void **)((Byte *)type+14);
        for (;count;--count) {
            record=galloc(20); memclrw(record,20);
            cursor=fn_005c97c0(cursor,(CIRType **)(record+4)); cursor=fn_005c9690(cursor,record+8);
            record[17]=*cursor++; *tail=record; tail=(void **)record;
        }
    } else for (;count;--count) {
        cursor=fn_005c97c0(cursor,&cirDiscardClassType); cursor=fn_005c9690(cursor,&discarded); ++cursor;
    }
    cursor=fn_005c9600(cursor,&count);
    if (!duplicate) {
        tail=(void **)((Byte *)type+18);
        for (;count;--count) {
            record=galloc(18); memclrw(record,18);
            cursor=fn_005c97c0(cursor,(CIRType **)(record+4)); cursor=fn_005c9690(cursor,record+8);
            cursor=fn_005c9690(cursor,record+12); *tail=record; tail=(void **)record;
        }
    } else for (;count;--count) {
        cursor=fn_005c97c0(cursor,&cirDiscardClassType); cursor=fn_005c9690(cursor,&discarded); cursor=fn_005c9690(cursor,&discarded);
    }
    cursor=fn_005c9600(cursor,&count);
    if (!duplicate) {
        tail=(void **)((Byte *)type+22);
        for (;count;--count) {
            record=galloc(24); memclrw(record,24); record[0]=4; record[1]=cursor[0]; record[2]=cursor[1];
            cursor=fn_005c97c0(cursor+2,(CIRType **)(record+12)); cursor=fn_005c9340(cursor,record+8);
            cursor=fn_005c9600(cursor,record+20); cursor=fn_005c9600(cursor,record+16);
            *tail=record; tail=(void **)(record+4);
        }
    } else for (;count;--count) {
        cursor=fn_005c97c0(cursor+2,&cirDiscardClassType); cursor=fn_005c9340(cursor,&mangled);
        cursor=fn_005c9600(cursor,&discarded); cursor=fn_005c9600(cursor,&discarded);
    }
    if (*cursor++) {
        if (!duplicate) {
            record=galloc(16); memclrw(record,16); P(type,26)=record;
            cursor=fn_005c9690(cursor,record+12);
        } else cursor=fn_005c9690(cursor,&discarded);
    }
    if (!name && (flags&0x200000)) {
        for (anonymous=cirAnonymousTypes;anonymous;anonymous=anonymous->next)
            if (fn_00544710(type,anonymous->value)) { type=anonymous->value; goto interned; }
        anonymous=galloc(8); anonymous->next=cirAnonymousTypes; anonymous->value=type; cirAnonymousTypes=anonymous;
interned:
        *out=type; cirReadTypes[index-56]=*out;
    }
    return cursor;
}

Word fn_005ca9f0(CIRType *type)
{
    Word hash,index,flags;
    CIRHashEntry *entry;
    void *record;
    int count;
    hash=fn_005441e0(type); entry=fn_00544180(cirTypeHashTable,type,hash);
    if (entry) return entry->index;
    index=cirNextTypeIndex++; fn_00544130(cirTypeHashTable,type,hash,index);
    if (U(type,34)&0x300) CError_Internal(cirTypeFilename,716);
    fn_005c97a0(40); fn_005c96d0(type->size); fn_005c93e0(P(type,10));
    if (!P(type,6)) CError_Internal(cirTypeFilename,722);
    fn_005cb6e0(((CIRNamespace *)P(type,6))->parent);
    flags=U(type,34);
    if (!(flags&0x800)) fn_005c9640(flags);
    else { fn_005c9640((flags&~0x800)|0x100000); fn_005c9530(fn_0045ef20(type,0)); }
    fn_005c9740(H(type,42)); fn_005c9740(H(type,44)); fn_005c97a0(C(type,46)); fn_005c97a0(C(type,47));
    count=0; for (record=P(type,14);record;record=P(record,0)) ++count;
    fn_005c9640(count);
    for (record=P(type,14);record;record=P(record,0)) { fn_005c9cd0(T(record,4)); fn_005c96d0(I(record,8)); fn_005c97a0(C(record,17)); }
    count=0; for (record=P(type,18);record;record=P(record,0)) ++count;
    fn_005c9640(count);
    for (record=P(type,18);record;record=P(record,0)) { fn_005c9cd0(T(record,4)); fn_005c96d0(I(record,8)); fn_005c96d0(I(record,12)); }
    count=0; for (record=P(type,22);record;record=P(record,4)) ++count;
    fn_005c9640(count);
    for (record=P(type,22);record;record=P(record,4)) {
        fn_005c97a0(C(record,1)); fn_005c97a0(C(record,2)); fn_005c9cd0(T(record,12)); fn_005c93e0(P(record,8));
        fn_005c9640(U(record,20)); fn_005c9640(U(record,16));
    }
    if (!P(type,26)) fn_005c97a0(0);
    else { fn_005c97a0(1); fn_005c96d0(I(P(type,26),12)); }
    return index;
}

Byte *fn_005cac20(Byte *cursor, CIRType **out)
{
    CIRType *type;
    CIRList *list, *anonymous;
    CIRObject *object;
    Byte duplicate, anonymousFlag, complete, *record, *header;
    int size, count, discarded;
    Word index;
    void *name, *source, *previousFile, *currentFile, *discardedName;
    unsigned short discardedShort;
    void **tail;
    duplicate=0;
    cursor=fn_005c9690(cursor,&size); header=fn_005c9340(cursor,&name);
    anonymousFlag=header[0]; complete=header[1];
    if (!anonymousFlag && name) {
        for (list=fn_004eb0d0(cirGlobalNamespace,name);list;list=list->next) {
            if (((CIRObject *)list->value)->kind != 2) continue;
            type=((CIRObject *)list->value)->value;
            if (type->kind==5) {
                if (!(B(type,17)&1)) goto selected;
                if (!complete || type->size==size) { duplicate=1; goto selected; }
            }
            source=fn_005c92e0(type); fn_00462e30();
            currentFile=cirCurrentSource ? (Byte *)P(P(cirCurrentSource,0),0)+10 : cirUnknownFile;
            previousFile=source ? (Byte *)P(P(source,0),0)+10 : cirUnknownFile;
            CError_Warning(0x2916,type,0,previousFile,currentFile);
            type=galloc(18); memclrw(type,18); type->kind=5; type->size=size; P(type,6)=name;
            B(type,17)=(B(type,17)&~1)|(complete&1); goto selected;
        }
        type=galloc(18); memclrw(type,18); type->kind=5; type->size=size; P(type,6)=name;
        B(type,17)=(B(type,17)&~1)|(complete&1);
        object=galloc(6); memclrw(object,6); object->kind=2; object->flags=0; object->value=type;
        CScope_AddObject(cirGlobalNamespace,name,object);
    } else {
        type=galloc(18); memclrw(type,18); type->kind=5; type->size=size; P(type,6)=name;
        B(type,17)=(B(type,17)&~1)|(complete&1);
        B(type,17)=(B(type,17)&~2)|((anonymousFlag&1)*2);
    }
selected:
    *out=type; cirReadTypes[cirNextTypeIndex-56]=type; index=cirNextTypeIndex++;
    if (!duplicate) {
        cursor=fn_005c9720(header+2,(Byte *)type+14); B(type,16)=*cursor;
        if (B(type,17)&1) fn_005c9310(type);
        cursor=fn_005c9600(cursor+1,&count); tail=(void **)((Byte *)type+10);
        for (;count;--count) {
            record=galloc(20); memclrw(record,20);
            cursor=fn_005c97c0(cursor,(CIRType **)(record+4)); cursor=fn_005c9340(cursor,record+8);
            cursor=fn_005c9690(cursor,record+12); cursor=fn_005c9600(cursor,record+16);
            *tail=record; tail=(void **)record;
        }
        if (!name) {
            for (anonymous=cirAnonymousTypes;anonymous;anonymous=anonymous->next)
                if (fn_00544710(type,anonymous->value)) { type=anonymous->value; goto interned; }
            anonymous=galloc(8); anonymous->next=cirAnonymousTypes; anonymous->value=type; cirAnonymousTypes=anonymous;
interned:
            *out=type; cirReadTypes[index-56]=*out;
        }
    } else {
        cursor=fn_005c9760(header+2,&discardedShort); cursor=fn_005c9600(cursor+1,&count);
        for (;count;--count) {
            cursor=fn_005c97c0(cursor,&cirDiscardStructType); cursor=fn_005c9340(cursor,&discardedName);
            cursor=fn_005c9690(cursor,&discarded); cursor=fn_005c9600(cursor,&discarded);
        }
    }
    return cursor;
}

Word fn_005cafd0(CIRType *type)
{
    Word hash,index,flags;
    CIRHashEntry *entry;
    void *record;
    int count;
    hash=fn_005441e0(type); entry=fn_00544180(cirTypeHashTable,type,hash);
    if (entry) return entry->index;
    index=cirNextTypeIndex++; fn_00544130(cirTypeHashTable,type,hash,index);
    fn_005c97a0(40); fn_005c96d0(type->size); fn_005c93e0(P(type,6)); fn_005cb6e0(cirGlobalNamespace);
    flags=(B(type,17)&1)?0x270006:0x270004;
    if (B(type,17)&4) flags|=0x400000;
    if (!P(type,6) || (B(type,17)&2)) flags|=0x400;
    fn_005c9640(flags); fn_005c9740(H(type,14)); fn_005c9740(0);
    fn_005c97a0(C(type,16)); fn_005c97a0(2); fn_005c9640(0); fn_005c9640(0);
    count=0; for (record=P(type,10);record;record=P(record,0)) ++count;
    fn_005c9640(count);
    for (record=P(type,10);record;record=P(record,0)) {
        fn_005c97a0(0); fn_005c97a0(0); fn_005c9cd0(T(record,4)); fn_005c93e0(P(record,8));
        fn_005c9640(U(record,12)); fn_005c9640(U(record,16));
    }
    fn_005c97a0(0); return index;
}

Byte *fn_005cb130(Byte *cursor, CIRType **out)
{
    CIRType *type, *base, *previous;
    CIRNamespace *scope;
    CIRList *list, *patch, *anonymous;
    CIRObject *object;
    Byte duplicate, *record;
    Word index;
    int count;
    void *name, *source, *previousFile, *currentFile, *discardedName;
    Byte discardedValue[8];
    void **tail;
    duplicate=0; type=fn_0046c730(22); memclrw(type,22); type->kind=-2;
    cirReadTypes[cirNextTypeIndex-56]=type; index=cirNextTypeIndex++;
    cursor=fn_005c97c0(cursor,&base); cursor=fn_005cb500(cursor,&scope); cursor=fn_005c9340(cursor,&name);
    for (list=fn_004eb0d0(scope,name);list;list=list->next) {
        if (((CIRObject *)list->value)->kind != 2) continue;
        previous=((CIRObject *)list->value)->value;
        if (previous->kind==4 && T(previous,14)==base) {
            for (patch=P(type,6);patch;patch=patch->next) *(CIRType **)patch->value=previous;
            cirReadTypes[index-56]=previous; fn_0046c6e0(type,22); duplicate=1; type=previous;
        } else {
            source=fn_005c92e0(previous); fn_00462e30();
            currentFile=cirCurrentSource ? (Byte *)P(P(cirCurrentSource,0),0)+10 : cirUnknownFile;
            previousFile=source ? (Byte *)P(P(source,0),0)+10 : cirUnknownFile;
            CError_Warning(0x2916,previous,0,previousFile,currentFile);
            type->kind=4; type->size=base->size; T(type,14)=base; P(type,6)=scope; P(type,18)=name;
        }
        goto selected;
    }
    type->kind=4; type->size=base->size; T(type,14)=base; P(type,6)=scope; P(type,18)=name;
    object=galloc(6); memclrw(object,6); object->kind=2; object->flags=0; object->value=type;
    CScope_AddObject(scope,name,object); fn_005c9310(type);
selected:
    *out=type; cursor=fn_005c9600(cursor,&count);
    if (!duplicate) {
        tail=(void **)((Byte *)type+10);
        for (;count;--count) {
            record=galloc(22); memclrw(record,22); record[0]=0; T(record,10)=type; record[1]=*cursor;
            cursor=fn_005c9340(cursor+1,record+6); cursor=fn_005c95c0(cursor,record+14,8);
            *tail=record; tail=(void **)(record+2);
        }
        if (CParser_IsNullOrAtOrDollarPrefixedName(name)) {
            for (anonymous=cirAnonymousTypes;anonymous;anonymous=anonymous->next)
                if (fn_00544710(type,anonymous->value)) { type=anonymous->value; goto interned; }
            anonymous=galloc(8); anonymous->next=cirAnonymousTypes; anonymous->value=type; cirAnonymousTypes=anonymous;
interned:
            *out=type; cirReadTypes[index-56]=*out;
        }
    } else for (;count;--count) {
        cursor=fn_005c9340(cursor+1,&discardedName); cursor=fn_005c95c0(cursor,discardedValue,8);
    }
    return cursor;
}

Word fn_005cb430(CIRType *type)
{
    Word hash,index;
    CIRHashEntry *entry;
    void *record;
    int count;
    hash=fn_005441e0(type); entry=fn_00544180(cirTypeHashTable,type,hash);
    if (entry) return entry->index;
    index=cirNextTypeIndex++; fn_00544130(cirTypeHashTable,type,hash,index);
    fn_005c97a0(38); fn_005c9cd0(T(type,14)); fn_005cb6e0(P(type,6)); fn_005c93e0(P(type,18));
    count=0; for (record=P(type,10);record;record=P(record,2)) ++count;
    fn_005c9640(count);
    for (record=P(type,10);record;record=P(record,2)) {
        fn_005c97a0(C(record,1)); fn_005c93e0(P(record,6)); fn_005c95e0((Byte *)record+14,8);
    }
    return index;
}

Byte *fn_005cb500(Byte *cursor, CIRNamespace **out)
{
    CIRNamespaceRef *reference;
    CIRNamespace *parent, *scope;
    CIRList *list, *slot;
    CIRObject *object;
    CIRType *type;
    Word index;
    void *name;
    switch (*cursor++) {
        case 0: *out=0; break;
        case 1: *out=cirGlobalNamespace; break;
        case 2:
            cursor=fn_005c9600(cursor,&index);
            for (reference=cirNamespaceRefs;reference;reference=reference->next) if (reference->index==index) break;
            if (!reference) CError_Internal(cirTypeFilename,261);
            *out=reference->scope; break;
        case 3:
            index=cirNextNamespaceIndex++;
            cursor=fn_005cb500(cursor,&parent); cursor=fn_005c9340(cursor,&name);
            list=fn_004eb0d0(parent,name);
            for (slot=list;slot;slot=slot->next) if (((CIRObject *)slot->value)->kind==3) break;
            if (slot) scope=((CIRObject *)slot->value)->value;
            else {
                scope=CScope_NewHashNameSpace(name); scope->parent=parent;
                object=galloc(6); memclrw(object,6); object->kind=3; object->value=scope;
                if (!list) slot=fn_004eaff0(parent,name);
                else {
                    while (list->next) list=list->next;
                    slot=galloc(8); memclrw(slot,8); list->next=slot;
                }
                slot->value=object;
            }
            *out=scope;
            reference=CompilerTools_AllocatePool(12); reference->next=cirNamespaceRefs; reference->scope=scope;
            reference->index=index; cirNamespaceRefs=reference; break;
        case 4: cursor=fn_005c97c0(cursor,&type); *out=P(type,6); break;
        default: CError_Internal(cirTypeFilename,276); break;
    }
    return cursor;
}

void fn_005cb6e0(CIRNamespace *scope)
{
    CIRNamespaceRef *reference;
    if (!scope) { fn_005c97a0(0); return; }
    if (scope==cirGlobalNamespace) { fn_005c97a0(1); return; }
    if (!scope->type) {
        for (reference=cirNamespaceRefs;reference;reference=reference->next)
            if (reference->scope==scope) { fn_005c97a0(2); fn_005c9640(reference->index); return; }
        reference=CompilerTools_AllocatePool(12); reference->next=cirNamespaceRefs; reference->scope=scope;
        reference->index=cirNextNamespaceIndex++; cirNamespaceRefs=reference;
        fn_005c97a0(3); fn_005cb6e0(scope->parent); fn_005c93e0(scope->name);
    } else { fn_005c97a0(4); fn_005c9cd0(scope->type); }
}
