/* GC3 BE_symbol.c uses 52-byte native ELF symbol records. */
#include <string.h>
#include <stddef.h>
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;
typedef long S32;
#pragma pack(push,2)
typedef struct Name { U8 prefix[10]; char text[1]; } Name;
typedef struct Section Section;
typedef struct Symbol Symbol;
typedef struct Pool Pool;
typedef struct PoolRoot PoolRoot;
typedef struct Object { U8 prefix[16]; void *type; U32 qualifiers; U16 flags, flags2; U8 unknown[24]; void *var; } Object;
struct Symbol { Name *name; Section *section; U32 index; S32 offset; U32 size; U8 info, other; U16 shndx; Symbol *next, *hashNext; U32 unknown[2]; U32 alignment; U8 linkage, flags; U16 unknown2; U16 kind; U8 defined, reserved; };
struct Pool { Pool *next; S32 offset; U32 reg; U32 unknown; U32 type; U32 unknown2; U8 valid, reserved; };
struct PoolRoot { Object *object; void *unknown; Pool *pools; Pool **tail; U8 active; };
struct Section { U8 prefix[24]; PoolRoot *pool; U32 unknown; char *name; U8 gap[8]; S32 offset; U8 gap2[60]; Symbol *symbol; };
typedef struct SymbolState { Symbol *hash[4096]; Symbol *head, *tail; U32 count; } SymbolState;
#pragma pack(pop)
typedef char CheckSymbol[sizeof(Symbol)==52?1:-1];
typedef char CheckSection[offsetof(Section,symbol)==108?1:-1];
SymbolState symbol_state;
Symbol *section_anchor;
extern U8 option_0070f016, option_0070f22b, option_0070f00a;
extern Section *default_section;
extern U8 type_006771c8;
extern U8 string_buffer[];
extern U32 string_buffer_size;
extern void *galloc(U32);
extern void memclrw(void *, U32);
extern void CError_Internal(char *, int);
extern U8 fn_00581be0(Object *);
extern U8 fn_004c3f60(Object *);
extern void fn_004c4480(Object *,void *,void *,S32);
extern void fn_005d84f0(Object *);
extern void *Registers_GetVarInfo(void *);
extern Name *CMangler_GetLinkName(Object *);
extern U8 CParser_HasInternalLinkage(Object *);
extern Name *fn_0046d340(char *);
extern Name *GetHashNameNode(char *);
extern void *fn_0046bc00(void);
extern void fn_0046d530(void *,char *);
extern void fn_00455ea0(void *);
extern void fn_0046d5a0(void *,void *);
extern void fn_0044cfe0(void *);
extern void fn_0044d0a0(void *);
extern S32 CMach_AllocationAlignment(void *,U32);
static char filename[]="BE_symbol.c";
#define ASSERT(n) CError_Internal(filename,n)
Symbol *MakeNamedSymbolTableEntry(Name *,short);
Symbol *MakeSymbolTableEntry(Object *);
Symbol *AddSymbol(Symbol *,U32,U32,short,U32,U8,Section *);
static inline U32 name_hash(Name *name)
{
 U32 length=strlen(name->text),hash=length,i;
 for(i=0;i<length;i++) hash=(hash<<5)^(hash>>27)^(S32)name->text[i];
 return (hash^(hash>>10)^(hash>>20))&4095;
}
static inline Symbol *new_symbol(Name *name)
{
 U32 hash=name_hash(name);
 Symbol *symbol=galloc(52);
 memset(symbol,0,52);
 symbol->name=name;
 symbol->hashNext=symbol_state.hash[hash];symbol_state.hash[hash]=symbol;
 if(symbol_state.head)symbol_state.tail->next=symbol;else symbol_state.head=symbol;
 symbol_state.tail=symbol;return symbol;
}
static inline Symbol *find_symbol(Name *name,short kind)
{
 Symbol *symbol;
 for(symbol=symbol_state.hash[name_hash(name)];symbol;symbol=symbol->hashNext)
  if(symbol->name==name && ((kind==0x102)==(symbol->kind==0x102)))return symbol;
 return 0;
}
U8 fn_005ccef0(Object *object)
{
 Section *section;Symbol *symbol;symbol=MakeSymbolTableEntry(object);section=symbol->section;
 if(!section)ASSERT(735);
 if(!fn_00581be0(object))return 1;
 section->pool->active=1;symbol->other|=0x80;return 0;
}
Pool *fn_005cd170(PoolRoot *root,S32 offset)
{
 Pool *pool;S32 base;
 for(pool=root->pools;pool;pool=pool->next){
  base=pool->offset;if(base-32768>offset)continue;if(offset>=base+32768)continue;return pool;
 }
 base=65536;
 while(base-32768>offset || offset>=base+32768)base+=65536;
 pool=galloc(26);memclrw(pool,26);pool->offset=base;pool->type=4;
 *root->tail=pool;root->tail=&pool->next;return pool;
}
Object *GetDataPoolRoot(Object *object)
{
 Symbol *symbol=MakeSymbolTableEntry(object);PoolRoot *root;
 if((object->flags2&0x200) && !symbol->size)
  fn_004c4480(object,0,0,*(S32 *)((U8 *)object->type+2));
 root=symbol->section->pool;
 if(option_0070f016 && root && root->unknown && !(object->qualifiers&0x20000) && !(object->qualifiers&0x40000) && object->prefix[2]!=3 && object->prefix[2]!=5 && object->prefix[2]!=4 && !fn_004c3f60(object)){
  fn_005cd170(root,symbol->offset);return root->object;
 }
 return 0;
}
static inline void find_valid_pool(PoolRoot *root,S32 offset,Pool **result)
{
 Pool *pool=root->pools;
 if(pool){for(;;){
  if(pool->offset-32768<=offset && offset<pool->offset+32768){
   if(!pool->valid)goto missing;*result=pool;return;
  }
  pool=pool->next;if(!pool)break;
 }}
missing:
 *result=0;
}
U32 fn_005ccff0(Object *object)
{
 Symbol *symbol=MakeSymbolTableEntry(object);S32 offset=symbol->offset;Pool *pool;
 if(offset==(short)offset)return *(short *)((U8 *)Registers_GetVarInfo(object->var)+16);
 find_valid_pool(symbol->section->pool,offset,&pool);
 return pool?pool->reg:0;
}
S32 fn_005cd070(Object *object)
{
 Symbol *symbol;S32 offset;Pool *pool;
 fn_005d84f0(object);symbol=MakeSymbolTableEntry(object);offset=symbol->offset;
 if(offset==(short)offset)return offset;
 find_valid_pool(symbol->section->pool,offset,&pool);
 if(!pool)ASSERT(679);
 return offset-pool->offset;
}
Pool *fn_005cd110(Object *object)
{
 Symbol *symbol=MakeSymbolTableEntry(object);Pool *pool;S32 offset=symbol->offset;
 for(pool=symbol->section->pool->pools;pool;pool=pool->next)
  if(pool->offset-32768<=offset && offset<pool->offset+32768)return pool;
 ASSERT(658);return 0;
}
Symbol *fn_005cd200(Section *section,Object *owner)
{
 char *text=galloc(strlen(section->name)+5);Object *object;Pool *pool;PoolRoot *root;Symbol *symbol;
 strcpy(text,"..");strcat(text,section->name);strcat(text,".0");
 object=galloc(96);section->pool->object=object;memclrw(object,96);
 object->type=&type_006771c8;object->prefix[0]=5;
 *(Name **)((U8 *)object+12)=GetHashNameNode(text);object->prefix[2]=0;object->flags=0x102;
 *(U32 *)((U8 *)object+4)=*(U32 *)((U8 *)owner+4);
 *(void **)((U8 *)object+64)=fn_0046bc00();*(U32 *)((U8 *)object+72)=0;
 pool=galloc(26);memclrw(pool,26);pool->type=3;
 root=section->pool;root->tail=&root->pools;*section->pool->tail=pool;section->pool->tail=&pool->next;
 symbol=new_symbol(*(Name **)((U8 *)object+12));symbol->info=0;symbol->shndx=0;symbol->section=section;symbol->alignment=1;symbol->kind=0x102;symbol->other|=0x40;symbol->flags|=0x10;return symbol;
}
Symbol *elf_declare_symbol(char *text,Section *section,U8 flag,U32 unused,U32 size,U32 unused2)
{
 Name *name=fn_0046d340(text);U8 saved=option_0070f22b;Symbol *symbol;short kind;
 if(flag)ASSERT(533);else kind=0x102;
 symbol=MakeNamedSymbolTableEntry(name,kind);if(!symbol){ASSERT(543);return symbol;}
 option_0070f22b=0;AddSymbol(symbol,size,0,kind,1,2,section);option_0070f22b=saved;section->symbol=symbol;return symbol;
}
Symbol *fn_005cd510(Section *section,U32 unused)
{
 U8 position[16];Name *name;Symbol *symbol;
 string_buffer_size=0;fn_0046d530(string_buffer,section->name);fn_0046d530(string_buffer,".");
 fn_00455ea0(position);fn_0046d5a0(string_buffer,position);fn_0044cfe0(*(void **)string_buffer);
 name=fn_0046d340(**(char ***)string_buffer);fn_0044d0a0(*(void **)string_buffer);
 symbol=MakeNamedSymbolTableEntry(name,0x102);if(!symbol){ASSERT(510);return symbol;}
 symbol->kind=0x102;symbol->info=0;symbol->size=0;symbol->shndx=0;symbol->offset=section->offset;symbol->section=section;symbol->alignment=1;symbol->linkage=0;symbol->flags=0x20;return symbol;
}
Symbol *fn_005cd5f0(Section *section)
{
 Symbol *symbol=section->symbol,*anchor;Symbol *next;
 if(symbol)return symbol;
 symbol=galloc(52);memset(symbol,0,52);symbol->name=fn_0046d340(section->name);symbol->kind=0x102;
 if(!section_anchor)section_anchor=symbol_state.head;
 anchor=section_anchor;next=anchor->next;anchor->next=symbol;symbol->next=next;section_anchor=symbol;section->symbol=symbol;return symbol;
}
Symbol *MakeSymbolTableEntry(Object *object)
{
 Name *name=CMangler_GetLinkName(object);short kind;
 if(CParser_HasInternalLinkage(object))kind=0x102;else kind=0x103;
 return MakeNamedSymbolTableEntry(name,kind);
}
Symbol *fn_005cd6a0(char *text,Section *section,U8 external,U32 unused,U32 size,S32 offset)
{
 Name *name=fn_0046d340(text);U8 saved=option_0070f22b,global;short kind=external?0x103:0x102;
 Symbol *symbol=find_symbol(name,kind);short effective=kind;
 if(symbol && strncmp(".dwarf_type.",text,12)){ASSERT(414);}
 if(symbol){external=0;symbol->kind=0x102;effective=symbol->kind;symbol->info&=15;}
 global=external;symbol=new_symbol(name);symbol->info=global<<4;symbol->kind=effective;symbol->section=default_section;
 option_0070f22b=0;AddSymbol(symbol,size,external==2?0x20000:0,external==254||external==255?external:effective,1,2,section);option_0070f22b=saved;symbol->offset=offset;return symbol;
}
Symbol *fn_005cda90(Name *name,short kind)
{
 Symbol *symbol=find_symbol(name,kind);U8 global=kind!=0x102;
 if(symbol){global=0;symbol->kind=0x102;kind=symbol->kind;symbol->info&=15;}
 symbol=new_symbol(name);symbol->info=global<<4;symbol->kind=kind;symbol->section=default_section;return symbol;
}
Symbol *MakeNamedSymbolTableEntry(Name *name,short kind)
{
 Symbol *symbol=find_symbol(name,kind);U8 global=kind!=0x102;
 if(symbol)return symbol;
 symbol=new_symbol(name);symbol->info=global<<4;symbol->kind=kind;symbol->section=default_section;return symbol;
}
U32 fn_005ce0a0(void){return symbol_state.count;}
void InitELFSymbols(void){memset(&symbol_state,0,16396);section_anchor=0;}
Symbol *fn_005ce0d0(Name *name){return new_symbol(name);}
Symbol *fn_005ce240(Object *object,Section *section)
{
 U8 global,weak=0;Symbol *symbol;
 if(CParser_HasInternalLinkage(object))global=0;else global=1;
 if(global==1 && (object->flags2&0x40))weak=1;
 symbol=MakeSymbolTableEntry(object);symbol->info=global<<4;symbol->size=0;symbol->shndx=0;symbol->section=section;symbol->alignment=4;symbol->linkage=0;symbol->flags=0;symbol->defined=1;
 if(option_0070f22b||weak)symbol->flags|=8;if(object->flags2&0x800)symbol->flags|=0x80;return symbol;
}
Symbol *AddFunction(Object *object,U32 size,Section *section)
{
 U8 global,linkage=0,weak=0;Symbol *symbol;
 if(CParser_HasInternalLinkage(object))global=0;else global=1;
 if(object->qualifiers&0x20000){global=2;linkage=13;}else if(object->qualifiers&0x40000){global=2;linkage=14;}
 if(global==1 && (object->flags2&0x40))weak=1;
 symbol=MakeSymbolTableEntry(object);symbol->size=size;symbol->shndx=0;symbol->section=section;symbol->alignment=1<<option_0070f00a;symbol->linkage=linkage;symbol->flags=0;symbol->defined=1;
 if(option_0070f22b||weak)symbol->flags|=8;if(object->flags2&0x800)symbol->flags|=0x80;symbol->info=(global<<4)+2;return symbol;
}
Symbol *fn_005ce3c0(Object *object,U32 size,Section *section)
{
 Symbol *symbol;short kind;
 if(*(U8 *)object->type==7)return AddFunction(object,size,section);
 symbol=MakeSymbolTableEntry(object);kind=CParser_HasInternalLinkage(object)?0x102:0x103;
 return AddSymbol(symbol,size,object->qualifiers,kind,CMach_AllocationAlignment(object->type,object->qualifiers),(U8)object->flags2,section);
}
Symbol *AddSymbol(Symbol *symbol,U32 size,U32 qualifiers,short kind,U32 alignment,U8 attrs,Section *section)
{
 U8 binding,linkage=0,extra=0;
 if(qualifiers&0x20000){binding=2;linkage=13;}else if(qualifiers&0x40000){binding=2;linkage=14;}
 else if(kind==0x102)binding=0;
 else if(kind==0xfe){extra|=0x40;binding=2;linkage=13;}
 else if(kind==0xff){extra|=0x40;binding=2;linkage=14;}else binding=1;
 symbol->info=(binding<<4)+1;symbol->size=size;symbol->shndx=0;symbol->section=section;symbol->alignment=alignment;symbol->linkage=linkage;symbol->flags=0;symbol->flags=extra;symbol->defined=1;
 if(!extra && (option_0070f22b||(binding==1 && (attrs&0x40))))symbol->flags|=8;
 return symbol;
}
Symbol *fn_005ce530(void){if(!symbol_state.tail)ASSERT(63);return symbol_state.tail=symbol_state.tail->next;}
Symbol *fn_005ce560(void){return symbol_state.tail=symbol_state.head;}
