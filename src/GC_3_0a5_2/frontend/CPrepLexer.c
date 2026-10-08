#include <string.h>
#include <stddef.h>
/* Native CPrepLexer.c: private records during caller migration. */
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef unsigned short UInt16;
typedef signed short SInt16;
typedef unsigned int UInt32;
typedef signed int SInt32;
#pragma pack(push, 2)
typedef struct LexerFile LexerFile;
typedef struct HashName { void *unknown00; UInt32 unknown04; SInt16 hash; char text[1]; } HashName;
typedef struct SourceRef { void *file; SInt32 offset, line; } SourceRef;
typedef struct LexerToken { SInt16 kind; UInt8 space, bol; void *value; SInt32 value2; SourceRef ref; union { void *macro; SInt32 length; } tail; } LexerToken;
typedef struct LexerFile { HashName *name; UInt32 unknown04; UInt8 kind, unknown09; char *contents; SInt32 contentsSize, unknown12; void *backing; UInt8 unknown1a[16]; void *diskInfo; } LexerFile;
typedef struct LogicalLineFile { HashName *name; UInt8 unknown04[26]; SInt32 sourceLine; LexerFile *file; SInt32 logicalLine; } LogicalLineFile;
typedef struct CompilerToken { SInt16 kind, flags; UInt8 payload[10]; SourceRef ref; UInt8 space, bol; } CompilerToken;
typedef struct StringPiece { char *text; SInt32 size; UInt8 encoding, unknown09; SInt16 kind; struct StringPiece *next; } StringPiece;
typedef struct KeywordInput { const char *name; SInt16 token; UInt8 condition, unknown07; void *handler; } KeywordInput;
typedef struct ScannerPosition { char *current; UInt8 unknown04[8]; SInt32 line; } ScannerPosition;
typedef struct ScannerState { void *file; char *base; UInt8 unknown08[36]; ScannerPosition position; UInt8 unknown3c[20]; } ScannerState;
typedef struct MacroNode { struct MacroNode *next; char *text; SInt16 kind; UInt8 flags, unknown0b;  } MacroNode;
typedef struct MacroList { MacroNode *head, *current, *previous; } MacroList;
typedef struct Macro { struct Macro *next; HashName *name; void *text; SInt32 textSize; SourceRef ref; UInt16 argCount, flags; SInt32 unknown20; } Macro;
typedef struct Keyword { struct Keyword *next; HashName *name; SInt16 token; UInt8 condition, unknown0b; void *handler; } Keyword;
typedef struct GList { void *data; SInt32 size, capacity, unknown0c; } GList;
typedef struct ParamView { UInt8 unknown00[0x30a], logicalNames; } ParamView;
typedef struct MacroStream { struct MacroStream *next; SourceRef ref; SInt32 offset; MacroList tokens; Macro *macro; SInt32 depth; } MacroStream;
typedef struct LexerState {
    LexerFile *file; LogicalLineFile *logicalFile; ScannerState *scannerSave; ScannerState *forceLogical; struct LexerState *parent; MacroStream *stream; SInt32 unknown18, depth, savedState; UInt8 silent, flag25, flag26, unread, flag28, flag29; SInt32 savedIgSize, macroLocks;
} LexerState;
#pragma pack(pop)
extern LexerState *lexer;
extern SInt32 lexer_lines, lexer_readaheadidx, lexer_readaheadsize;
extern LexerToken *lexer_readahead;
extern UInt8 peekeol(void);
extern SInt16 lexer_plex(LexerToken *);
extern void lexer_string_handling(SInt16, LexerToken *);
extern SInt16 lexer_convert_to_token(LexerToken *, CompilerToken *, UInt8, UInt8);
extern void preprocessor_internal_msg(int, int, const char *, const char *, int);
void lexer_validate(void) {}
void lexer_macro_expansion_lock(void) { lexer->macroLocks++; }
SInt32 lexer_get_silent(void) { return lexer ? lexer->silent : 1; }
SInt32 lexer_get_depth(void) { return lexer ? lexer->depth : 0; }
SInt32 lexer_get_lines(void) { return lexer_lines; }
UInt8 lexer_isendofline(void) { return peekeol(); }
void lexer_unload(void) {}
SInt16 lexer_lex(LexerToken *raw, CompilerToken *token, UInt8 newline, UInt8 flag1, UInt8 flag2)
{
    do {
        if (lexer_readaheadidx < lexer_readaheadsize) {
            *raw = lexer_readahead[lexer_readaheadidx];
            if (lexer_readaheadsize < 1) preprocessor_internal_msg(1, 0, "CPrepLexer.c", "lexer_skipahead", 9117);
            if (lexer_readaheadidx + 1 >= lexer_readaheadsize) lexer_readaheadidx = lexer_readaheadsize = 0;
            else lexer_readaheadidx++;
        } else lexer_plex(raw);
    } while ((raw->kind == -7 && !newline) || raw->kind == -17);
    if (raw->kind <= -12 && raw->kind >= -14) lexer_string_handling(raw->kind, raw);
    lexer_convert_to_token(raw, token, flag1, flag2);
    return token->kind;
}

extern Macro *pp_macrohashtable[2048];
extern Keyword *lexer_kwhash[2048];
extern GList lexer_inclfromlist, lexer_asmlist, lexer_iglist, lexer_mlist;
extern UInt8 lexer_gathering_asm_args, lexer_record_tokens;
extern UInt8 asciistring[512];
extern ScannerState scanner;
extern ParamView *cparamblkptr;
extern void *(*clt_get_current_disk_filespec)(void);
extern Macro *(*fn_007106a8)(Macro *);
extern void memclrw(void *, SInt32), FreeGList(GList *);
extern HashName *GetHashNameNodeExport(const char *);
extern void lexer_error(LexerToken *, SInt32, ...), lexer_skipendofline(void);
extern char *preprocesstoken(SInt16, void *, SInt32, UInt8);
extern void lexer_message_v(SourceRef *, void *, int, SInt16, char *);
extern void preprocessor_sourceref_make_pptoken(SourceRef *, LexerToken *);
extern SInt16 scanner_readtoken(LexerToken *);
extern void scanner_unreadtoken(LexerToken *);
extern SInt16 lexer_readmacrotoken(MacroStream *, LexerToken *, UInt8 *);

void lexer_reconfig(void) {}
void lexer_macro_expansion_unlock(void)
{
    if (!lexer->macroLocks)
        preprocessor_internal_msg(1, 0, "CPrepLexer.c", "lexer_macro_expansion_unlock", 8123);
    lexer->macroLocks--;
}
UInt8 lexer_plextokenorfail(LexerToken *t, SInt16 expected, SInt16 error)
{
    if (lexer_plex(t) != expected) { if(t->kind == -7) lexer_error(t,0x2780); else lexer_error(t,error); return 0; }
    return 1;
}
UInt8 lexer_plextokenorskip(LexerToken *t, SInt16 expected, SInt16 error)
{
    if (lexer_plex(t) != expected) {
        if (t->kind == -7) lexer_error(t, 0x2780);
        else { lexer_error(t, error); lexer_skipendofline(); }
        return 0;
    }
    return 1;
}
UInt8 lexer_readmacrotokenorskip(LexerToken *t, SInt16 expected, SInt16 error)
{
    UInt8 flag;
    if (lexer_readmacrotoken(0, t, &flag) != expected) {
        if (t->kind == -7) lexer_error(t, 0x2780);
        else { lexer_error(t, error); lexer_skipendofline(); }
        return 0;
    }
    return 1;
}
void lexer_clear_macros(void) { memclrw(pp_macrohashtable, 8192); }
void lexer_fixup_names(void)
{
    int i; Keyword *k;
    for (i=0; i<2048; i++) for (k=lexer_kwhash[i]; k; k=k->next)
        k->name=GetHashNameNodeExport(k->name->text);
}
void lexer_cleanup(void)
{
    FreeGList(&lexer_inclfromlist); FreeGList(&lexer_asmlist);
    lexer_gathering_asm_args=0; FreeGList(&lexer_iglist);
    lexer=0; FreeGList(&lexer_mlist);
}
void scanner_getsourceref(ScannerPosition *p, SourceRef *r)
{
    if (!p) p=&scanner.position;
    r->file=scanner.file; r->offset=p->current-scanner.base; r->line=p->line;
}
void lexer_getsourceref(SourceRef *r)
{
    ScannerPosition *p=&scanner.position;
    r->file=scanner.file; r->offset=p->current-scanner.base; r->line=p->line;
    if (lexer && lexer->logicalFile &&
        (cparamblkptr->logicalNames || lexer->forceLogical)) r->file=lexer->logicalFile;
}
SInt32 lexer_get_current_line(void)
{
    if (!lexer) return 0;
    if (lexer->logicalFile) {
        ScannerPosition *position=&scanner.position;
        return position->line-lexer->logicalFile->sourceLine+lexer->logicalFile->logicalLine;
    }
    return scanner.position.line;
}
HashName *lexer_get_current_filename(void)
{
    if (!lexer) return 0;
    if (lexer->logicalFile) return lexer->logicalFile->name;
    return lexer->file->name;
}
LexerFile *lexer_get_current_file(void)
{
    if (!lexer) return 0;
    if (lexer->logicalFile) {
        LexerFile *file=lexer->logicalFile->file;
        if (!file) file=lexer->file;
        return file;
    }
    return lexer->file;
}
UInt8 lexer_matchendofline(void)
{
    UInt8 result=peekeol(); LexerToken token; SourceRef ref;
    if (!result) {
        ScannerPosition *p=&scanner.position;
        ref.file=scanner.file; ref.offset=p->current-scanner.base; ref.line=p->line;
        preprocessor_sourceref_make_pptoken(&ref,&token); lexer_error(&token,0x2781); lexer_skipendofline();
    }
    return result;
}
char *lexer_preprocess_token(LexerToken *t, UInt8 flag)
{ return preprocesstoken(t->kind,t->value,t->value2,flag); }
Macro *lexer_lookup_macro(HashName *name)
{
    Macro *m=pp_macrohashtable[name->hash];
    for (;m;m=m->next) if (m->name==name) {
        if (m->flags&16) return 0;
        if (m->flags&8) { Macro *(*callback)(Macro *)=fn_007106a8; if(callback) m=callback(m); }
        return m;
    }
    return m;
}
void lexer_delete_special_macros(void)
{
    int i; Macro **m;
    for (i=0;i<2048;i++) {
        m=&pp_macrohashtable[i];
        while (*m) { if ((*m)->flags&8) *m=(*m)->next; else m=&(*m)->next; }
    }
}
void mlist_delete_after_thru(MacroList *list, MacroNode *after, MacroNode *thru)
{
    if (after) {
        if (after->next != list->head) {
            after->next=thru?thru->next:0;
            if (!after->next) list->current=after;
            return;
        }
        after->next=thru?thru->next:0;
    }
    list->head=thru?thru->next:0;
    if (!list->head) list->current=0;
}
void lexer_warning(LexerToken *token, SInt32 error, ...)
{
    char *start=(char *)&error;
    char *end=(char *)(&error+1);
    char *args=start+((end-start+3)/4*4);
    lexer_message_v(token?&token->ref:0,token?token->tail.macro:0,1,error,args);
}
void lexer_info_at_sourceref(SourceRef *ref, SInt32 error, ...)
{
    char *start=(char *)&error;
    char *end=(char *)(&error+1);
    char *args=start+((end-start+3)/4*4);
    lexer_message_v(ref,0,0,error,args);
}
void lexer_warning_at_sourceref(SourceRef *ref, SInt32 error, ...)
{
    char *start=(char *)&error;
    char *end=(char *)(&error+1);
    char *args=start+((end-start+3)/4*4);
    lexer_message_v(ref,0,1,error,args);
}

extern GList lexer_dlist;
void lexer_unreadtoken(LexerToken *token)
{
    if (lexer_record_tokens) {
        if (token->space && !token->bol) lexer_dlist.size--;
        lexer_dlist.size-=strlen(preprocesstoken(token->kind,token->value,token->value2,0));
    }
    lexer->unread=0;
    scanner_unreadtoken(token);
}


extern SInt32 lexer_macro_stacks;
extern void *aalloc(SInt32), *galloc(SInt32);
extern void scanner_getstate(ScannerPosition *), scanner_setstate(ScannerPosition *);
extern void AppendGListByte(GList *, SInt8), AppendGListName(GList *, const char *);
extern SInt32 COS_FileExists(void *);
extern char *COS_PathGetFileName(const char *);
extern int CTool_strcasecmp(const char *, const char *);
extern void appendmacrotoken(GList *, LexerToken *, SInt8);
static __inline SInt16 lexer_readtoken_impl(LexerToken *token)
{
    SInt16 result=scanner_readtoken(token);
    if (lexer && lexer->logicalFile && (cparamblkptr->logicalNames || lexer->forceLogical)) token->ref.file=lexer->logicalFile;
    if (lexer_record_tokens) {
        if (token->space && !token->bol) AppendGListByte(&lexer_dlist,32);
        AppendGListName(&lexer_dlist,preprocesstoken(token->kind,token->value,token->value2,0));
    }
    lexer->unread=0;
    return result;
}
LexerFile *lexer_match_stacked_file(const char *name)
{
    LexerState *state;
    for (state=lexer;state;state=state->parent)
        if(state->file && !CTool_strcasecmp(COS_PathGetFileName(state->file->name->text),name)) return state->file;
    return 0;
}

UInt8 peekeol(void)
{
    MacroStream *stream; MacroList list; MacroNode *token; LexerToken result; ScannerPosition saved; SInt16 kind;
    for(stream=lexer->stream;stream;stream=stream->next) {
        list=stream->tokens;
        while((token=list.current)!=0) {
            kind=token->kind;
            if(kind!=-19 && kind!=-20 && kind!=-17) return kind==-7;
            if(token) { list.previous=token; list.current=list.current->next; }
        }
    }
    scanner_getstate(&saved);
    do { kind=scanner_readtoken(&result); } while(kind==-17);
    scanner_setstate(&saved);
    return kind==-7 || kind==0;
}
UInt8 peekargparen(void)
{
    MacroStream *stream; MacroList list; MacroNode *token; SInt16 kind;
    for(stream=lexer->stream;stream;stream=stream->next) {
        list=stream->tokens;
        while((token=list.current)!=0) {
            kind=token->kind;
            if(kind!=-7 && kind!=-17 && kind!=-19 && kind!=-20) return kind==40;
            if(token) { list.previous=token; list.current=list.current->next; }
        }
        if(!stream->macro) return 0;
    }
    return 0;
}
SInt16 lexer_peekmacrotoken(MacroStream *stop, LexerToken *result, UInt8 stopAtEnd, UInt8 skipNewline)
{
    MacroStream *stream; MacroList list; MacroNode *token; ScannerPosition saved; SInt16 kind;
    for(stream=lexer->stream;stream;stream=stream->next) {
        list=stream->tokens;
        while((token=list.current)!=0) {
            kind=token->kind;
            if ((!skipNewline || kind!=-7) && kind!=-17 && kind!=-19 && kind!=-20) {
                result->kind=token->kind; result->value=token->text;
                result->tail.length=strlen(result->value); result->value2=result->tail.length;
                result->space=(token->flags&1)!=0; result->bol=0; return kind;
            }
            if(token) { list.previous=token; list.current=list.current->next; }
        }
        if(stopAtEnd && stream==stop) return 0;
    }
    scanner_getstate(&saved);
    do { kind=scanner_readtoken(result); } while(kind==-7 || kind==-17);
    scanner_setstate(&saved);
    return kind;
}
void lexer_push_mstream(Macro *macro, MacroList *list, UInt8 disable, SourceRef *source)
{
    SourceRef ref; MacroStream *stream;
    ScannerPosition *position=&scanner.position;
    ref.file=scanner.file;ref.offset=position->current-scanner.base;ref.line=position->line;
    stream=aalloc(40);stream->next=lexer->stream;
    if(source) stream->ref=*source;
    else if(stream->next) stream->ref=stream->next->ref;
    else stream->ref=ref;
    stream->macro=macro;
    if(macro && disable) macro->flags|=4;
    stream->tokens.head=(MacroNode *)list;stream->tokens.current=list->head;stream->tokens.previous=0;
    stream->depth=stream->next?stream->next->depth+1:0;
    stream->offset=ref.offset;
    lexer->stream=stream;
    lexer_macro_stacks++;
}
SInt32 ppgetprec(SInt16 token)
{
    switch(token) {
    case 37:case 42:case 47:return 11;
    case 43:case 45:return 10;
    case 378:case 379:return 9;
    case 60:case 62:case 376:case 377:return 8;
    case 374:case 375:return 7;
    case 38:return 6;
    case 94:return 5;
    case 124:return 4;
    case 373:return 3;
    case 372:return 2;
    default:return 0;
    }
}
char *lexer_macro_encode_number(char *text, SInt32 *size)
{
    LexerToken token={0};GList *list=&lexer_mlist;char *result;
    list->size=0;
    if(*text=='-') {
        token.kind=45;token.value="-";token.value2=1;token.tail.length=token.value2;
        appendmacrotoken(list,&token,0);text++;
    }
    token.kind=-8;token.value=text;token.value2=strlen(text);token.tail.length=token.value2;
    appendmacrotoken(list,&token,0);*size=list->size;
    appendmacrotoken(list,0,0);
    result=aalloc(list->size);memcpy(result,*(void **)list->data,list->size);return result;
}
char *lexer_macro_encode_string(char *text, SInt32 *size)
{
    LexerToken token={0};GList *list=&lexer_mlist;char *result,*cursor;
    list->size=0;result=aalloc(strlen(text)*2+1);cursor=result;
    for(;*text;text++) { if(*text=='\\' || *text=='"') *cursor++='\\'; *cursor++=*text; }
    *cursor=0;token.kind=-12;token.value=result;*cursor=0;token.value2=cursor-result;token.tail.length=token.value2;
    appendmacrotoken(list,&token,0);*size=list->size;
    appendmacrotoken(list,0,0);
    result=aalloc(list->size);memcpy(result,*(void **)list->data,list->size);return result;
}
char *lexer_macro_encode_escaped_string(char *text, SInt32 *size)
{
    LexerToken token={0};GList *list=&lexer_mlist;char *first=text+1,*last=text+strlen(text)-1,*result;
    list->size=0;
    if(*text!='"' || *last!='"') preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_macro_encode_escaped_string",3748);
    token.kind=-12;token.value=first;*last=0;token.value2=last-1-first;token.tail.length=token.value2;
    appendmacrotoken(list,&token,0);*size=list->size;
    appendmacrotoken(list,0,0);
    result=aalloc(list->size);memcpy(result,*(void **)list->data,list->size);return result;
}

extern UInt8 scanner_tokenhasfixedtext(LexerToken *);
extern char *scanner_get_token_text(SInt16);
extern void AppendGListID(GList *,const char *), AppendGListWord(GList *,SInt16);
SInt16 decodemacrotoken(Macro *macro, UInt8 **input, LexerToken *token, UInt8 *flags)
{
    UInt8 *start=*input; UInt16 encoding=(UInt16)(start[0]|(start[1]<<8)); UInt8 bits=0;
    if(!encoding) { *flags=0;token->kind=0;return token->kind; }
    *input+=2;
    token->kind=(SInt16)(encoding<<2)>>2;
    if(encoding&0x4000) bits|=1;
    if(encoding&0x8000) { bits|=**input;(*input)++; }
    *flags=bits;token->space=(bits&1)!=0;token->bol=0;
    if(bits&0x20) {
        token->value=*input;token->value2=strlen(token->value);*input+=token->value2+1;
    } else if(bits&4) {
        token->value=macro?((HashName **)((char *)macro+32))[token->kind-1]->text:"<arg>";
        token->value2=strlen(token->value);
    } else if((UInt32)(SInt32)token->kind<256) {
        token->value=&asciistring[token->kind*2];token->value2=1;
    } else {
        token->value=scanner_get_token_text(token->kind);token->value2=strlen(token->value);
    }
    token->tail.length=*input-start;return token->kind;
}
void appendmacrotoken(GList *list, LexerToken *token, SInt8 flags)
{
    UInt16 encoding;
    if(!token) { AppendGListWord(list,0);return; }
    encoding=token->kind&0x3fff;
    if(!(flags&0x24) && !scanner_tokenhasfixedtext(token)) flags|=0x20;
    if(token->space || (flags&1)) { flags&=~1;encoding|=0x4000; }
    if(flags) encoding|=0x8000;
    AppendGListByte(list,(SInt8)encoding);AppendGListByte(list,(SInt8)(encoding>>8));
    if(flags) {
        AppendGListByte(list,flags);
        if(flags&0x20) AppendGListID(list,token->value);
    }
}
LexerFile *lexer_get_current_disk_file(void)
{
    LexerState *state;LexerFile *file;
    for(state=lexer;state;state=state->parent) {
        if(state->file) {
            file=state->file;
            while(file) {
                switch(file->kind) {
                case 0:goto found;
                case 1:case 2:case 3:file=file->backing;break;
                default:file=0;break;
                }
            }
found:
            if(file && file->kind==0 && (file->name->text[0]!='(' || !COS_FileExists(file->backing))) return file;
        }
    }
    return 0;
}
void *lexer_get_current_disk_filespec(void)
{
    LexerState *state;LexerFile *file;
    for(state=lexer;state;state=state->parent) {
        if(state->file) {
            file=state->file;
            while(file) {
                switch(file->kind) {
                case 0:goto found;
                case 1:case 2:case 3:file=file->backing;break;
                default:file=0;break;
                }
            }
found:
            if(file && file->kind==0 && (file->name->text[0]!='(' || !COS_FileExists(file->backing))) return file?file->backing:0;
        }
    }
    file=0;return file?file->backing:0;
}
void lexer_load(void)
{
    int i;
    clt_get_current_disk_filespec=lexer_get_current_disk_filespec;
    for(i=0;i<256;i++) { asciistring[i*2]=i;asciistring[i*2+1]=0; }
}

extern void *lalloc(SInt32);
extern void scanner_convert_up_literal(SInt16,SInt16,UInt8,char **,SInt32 *);
extern SInt32 lexer_readaheadmax;
SInt16 lexer_peekahead(LexerToken *token,SInt32 distance)
{
    SInt32 index=lexer_readaheadidx+distance;
    while(lexer_readaheadsize<=index) {
        LexerToken *item,*buffer;char *text;SInt32 size;
        if(!lexer_plex(token)) return 0;
        if(lexer_readaheadsize>=lexer_readaheadmax) {
            lexer_readaheadmax=lexer_readaheadmax?lexer_readaheadmax*2:64;
            buffer=galloc(lexer_readaheadmax*28);
            memcpy(buffer,lexer_readahead,lexer_readaheadsize*28);lexer_readahead=buffer;
        }
        item=&lexer_readahead[lexer_readaheadsize++];*item=*token;
        size=token->value2;text=galloc(size+1);memcpy(text,token->value,size+1);item->value=text;
        index=lexer_readaheadidx+distance;
    }
    if(lexer_readaheadsize>index) { *token=lexer_readahead[index];return token->kind; }
    return 0;
}
void cat_strings(StringPiece *first,char **text,SInt32 *size)
{
    StringPiece *piece;SInt32 length;char *cursor;
    if(!first->next) { *text=first->text;*size=first->size;return; }
    for(length=0,piece=first;piece;piece=piece->next) { length+=piece->size;if(piece->next) length+=2; }
    *size=length;cursor=lalloc(length+1);*text=cursor;
    for(piece=first;piece;piece=piece->next) {
        memcpy(cursor,piece->text,piece->size);cursor+=piece->size;
        if(piece->next) { memcpy(cursor,"\x5c\x01",2);cursor+=2; }
    }
    *cursor=0;
}
void lexer_string_handling(SInt16 kind,LexerToken *raw)
{
    StringPiece *first,*last,*piece;LexerToken token;SInt32 distance=0;
    first=lalloc(16);first->size=raw->value2;first->text=lalloc(first->size+1);
    memcpy(first->text,raw->value,first->size+1);first->encoding=((UInt8 *)&scanner)[12];first->kind=raw->kind;first->next=0;last=first;
    for(;;) {
        if(!lexer_peekahead(&token,distance)) break;
        distance++;
        if(token.kind==-7 || token.kind==-17) continue;
        if(token.kind>-12 || token.kind<-14) break;
        if(lexer_readaheadsize<distance) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_skipahead",9117);
        if(distance+lexer_readaheadidx>=lexer_readaheadsize) lexer_readaheadidx=lexer_readaheadsize=0;else lexer_readaheadidx+=distance;
        if((kind==-12 && token.kind!=-12)||(kind==-13 && token.kind==-14)) {
            kind=token.kind;
            for(piece=first;piece;piece=piece->next) {
                scanner_convert_up_literal(piece->kind,kind,piece->encoding,&piece->text,&piece->size);piece->kind=kind;
            }
        }
        piece=lalloc(16);piece->size=token.value2;piece->text=lalloc(piece->size+1);
        memcpy(piece->text,token.value,piece->size+1);piece->encoding=((UInt8 *)&scanner)[12];piece->kind=token.kind;piece->next=0;
        if(last) last->next=piece;last=piece;distance=0;
    }
    cat_strings(first,(char **)&raw->value,&raw->value2);raw->kind=kind;
}
void lexer_add_keywords(KeywordInput *keywords, UInt32 count)
{
    while(count--) {
        HashName *name=GetHashNameNodeExport(keywords->name);Keyword *keyword=galloc(16);
        SInt32 masked=keywords->token&0x3fff;
        if(masked!=((SInt16)(masked<<2)>>2)) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_add_keywords",8170);
        keyword->name=name;keyword->token=keywords->token;keyword->condition=keywords->condition;keyword->handler=keywords->handler;
        keyword->next=lexer_kwhash[name->hash];lexer_kwhash[name->hash]=keyword;keywords++;
    }
}
extern void parsenumber(LexerToken *,CompilerToken *,UInt8),parselit(LexerToken *,CompilerToken *);
SInt16 lexer_convert_to_token(LexerToken *raw,CompilerToken *result,UInt8 option,UInt8 keywords)
{
    SInt16 kind=raw->kind;HashName *name;Keyword *keyword;UInt8 enabled;
    result->space=raw->space;result->bol=raw->bol;result->ref=raw->ref;result->flags=0;
    switch(kind) {
    case -18:case -17:case -16:case -15:result->kind=-6;break;
    case -14:case -13:case -12:case -11:case -10:case -9:parselit(raw,result);break;
    case -8:parsenumber(raw,result,option);break;
    case -3:
        name=GetHashNameNodeExport(raw->value);
        if(keywords) {
            for(keyword=lexer_kwhash[name->hash];keyword;keyword=keyword->next) if(keyword->name==name) {
                switch(keyword->condition) {
                case 0:enabled=1;break;
                case 1:enabled=0;break;
                case 2:enabled=*(UInt8 *)keyword->handler!=0;break;
                case 3:enabled=*(UInt8 *)keyword->handler==0;break;
                case 4:enabled=((UInt8 (*)(const char *,SInt16))keyword->handler)(name->text,keyword->token);break;
                default:preprocessor_internal_msg(1,0,"CPrepLexer.c","kwcheck",8192);enabled=0;break;
                }
                if(enabled) break;
            }
            if(keyword) { kind=keyword->token;result->kind=kind;break; }
        }
        result->kind=-3;*(HashName **)result->payload=name;break;
    default:result->kind=kind;break;
    }
    return result->kind;
}
UInt8 lexer_readtokenorskip(LexerToken *token,SInt16 expected,SInt16 error)
{
    if(lexer_readtoken_impl(token)!=expected) {
        if(token->kind==-7) lexer_error(token,0x2780);
        else { lexer_error(token,error);lexer_skipendofline(); }
        return 0;
    }
    return 1;
}


SInt16 lexer_readtoken(LexerToken *token) { return lexer_readtoken_impl(token); }
extern SInt32 iflevel,now_time;
extern LexerToken *lexer_incltoken;
extern UInt8 lexer_pragmaonce,lexer_incondexpr,lexer_in_directive;
extern LexerFile *lexer_igtext,*lexer_first_line_file;
extern void *pp_msgcontext;
extern void freeaheap(void),Msg_FatalJump(void *);
extern SInt16 InitGList(GList *,SInt32);
extern SInt32 time(SInt32 *);
extern LexerFile *preprocessor_new_string_file(HashName *,UInt8,char *,SInt32,SourceRef *);
extern UInt8 preprocessor_load_file(LexerFile *),lexer_pop(void);
extern void scanner_init(LexerFile *);
extern void (*fn_0071068c)(LexerFile *,SInt32,UInt8,UInt8);
extern void (*fn_00710690)(LexerFile *,HashName *,SInt32,SInt32,UInt8,UInt8);
extern void lexer_error_at_sourceref(SourceRef *,SInt32,...);
static __inline void lexer_pop_mstream_impl(void)
{
    if(!lexer->stream) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_pop_mstream",4718);
    if(lexer->stream->macro) lexer->stream->macro->flags&=~4;
    lexer->stream=lexer->stream->next;
    if(!lexer->flag26 && --lexer_macro_stacks==0) freeaheap();
}
void lexer_error(LexerToken *token,SInt32 error,...)
{
    char *start=(char *)&error,*end=(char *)(&error+1);char *args=start+((end-start+3)/4*4);
    lexer_message_v(token?&token->ref:0,token?token->tail.macro:0,2,error,args);
    if(error==0x28bb) {
        iflevel=0;
        if(lexer) while(lexer->stream) lexer_pop_mstream_impl();
        Msg_FatalJump(pp_msgcontext);
    }
}
void lexer_error_at_sourceref(SourceRef *ref,SInt32 error,...)
{
    char *start=(char *)&error,*end=(char *)(&error+1);char *args=start+((end-start+3)/4*4);
    lexer_message_v(ref,0,2,error,args);
    if(error==0x28bb) {
        iflevel=0;
        if(lexer) while(lexer->stream) lexer_pop_mstream_impl();
        Msg_FatalJump(pp_msgcontext);
    }
}
void lexer_push(LexerState *state,UInt8 silent,UInt8 flag)
{
    SourceRef ref;
    if(lexer && lexer->depth>=256) {
        lexer_getsourceref(&ref);lexer_error_at_sourceref(&ref,0x2803);
        iflevel=0;
        if(lexer) while(lexer->stream) lexer_pop_mstream_impl();
        Msg_FatalJump(pp_msgcontext);return;
    }
    if(lexer && lexer->scannerSave) *lexer->scannerSave=scanner;
    if(!state) state=galloc(50);
    memclrw(state,50);state->parent=lexer;lexer=state;
    state->depth=state->parent?state->parent->depth+1:0;
    lexer->scannerSave=galloc(80);
    lexer->silent=silent;lexer->flag25=flag;lexer->savedState=iflevel;
    lexer->flag28=0;lexer_in_directive=0;lexer->macroLocks=0;lexer->savedIgSize=lexer_iglist.size;
    lexer->flag29=lexer->parent?lexer->parent->flag29:0;
}
UInt8 lexer_push_string(const char *name,char *text,SInt32 size,UInt8 kind,SourceRef *ref,UInt8 silent,UInt8 flag,LexerFile **out)
{
    LexerFile *file;void (*notify)(LexerFile *,SInt32,UInt8,UInt8);void (*notify2)(LexerFile *,HashName *,SInt32,SInt32,UInt8,UInt8);
    if(!name || !text) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_push_string",1627);
    file=preprocessor_new_string_file(GetHashNameNodeExport(name),kind,text,size,ref);
    lexer_push(0,silent,flag);lexer->file=file;
    notify=fn_0071068c;if(notify) notify(file,lexer->depth,silent,1);
    notify2=fn_00710690;if(notify2) notify2(file,file->name,1,lexer->depth,silent,0);
    scanner_init(file);lexer->unread=!silent;((UInt8 *)&scanner.position)[6]=!silent;
    if(out) *out=file;return 1;
}
UInt8 lexer_push_file(LexerFile *file,UInt8 silent,UInt8 flag,LexerFile **out)
{
    void (*notify)(LexerFile *,SInt32,UInt8,UInt8);void (*notify2)(LexerFile *,HashName *,SInt32,SInt32,UInt8,UInt8);
    if(!file) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_push_file",1570);
    lexer_push(0,silent,flag);lexer->file=file;
    if(file->kind==0) {
        UInt16 *refs;
        if(!preprocessor_load_file(file)) { if(out) *out=0;scanner_init(file);lexer_pop();return 0; }
        refs=(UInt16 *)((char *)file->diskInfo+12);if(++*refs==0) --*refs;
    } else if(!file->contents) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_push_file",1588);
    notify=fn_0071068c;if(notify) notify(file,lexer->depth,silent,1);
    notify2=fn_00710690;if(notify2) notify2(file,file->name,1,lexer->depth,silent,0);
    scanner_init(file);lexer->unread=1;if(out) *out=file;return 1;
}
void lexer_insert_special_macro(Macro *macro,const char *name,char *text)
{
    char *encoded;
    memclrw(macro,36);macro->name=GetHashNameNodeExport(name);macro->flags|=8;
    if(text) { extern char *lexer_macro_encode_text(char *,UInt8,SInt32 *);encoded=lexer_macro_encode_text(text,2,&macro->textSize);macro->text=galloc(macro->textSize+2);memcpy(macro->text,encoded,macro->textSize+2); }
    else { macro->text=0;macro->textSize=0; }
    macro->ref.file=0;macro->ref.offset=0;macro->ref.line=0;
    if(!lexer_lookup_macro(macro->name)) { macro->next=pp_macrohashtable[macro->name->hash];pp_macrohashtable[macro->name->hash]=macro; }
}
extern Macro lineM,fileM,dateM,timeM,trgtM,envrM;
void lexer_insert_special_macros(void)
{
    lexer_insert_special_macro(&lineM,"__LINE__",0);lexer_insert_special_macro(&fileM,"__FILE__",0);
    lexer_insert_special_macro(&dateM,"__DATE__",0);lexer_insert_special_macro(&timeM,"__TIME__",0);
    lexer_insert_special_macro(&trgtM,"__ide_target",0);lexer_insert_special_macro(&envrM,"__env_var",0);
}
void lexer_setup(void)
{
    lexer=0;memclrw(lexer_kwhash,8192);
    if(InitGList(&lexer_mlist,16384)) lexer_error(0,0x28bb);
    if(InitGList(&lexer_dlist,1024)) lexer_error(0,0x28bb);
    if(InitGList(&lexer_asmlist,1024)) lexer_error(0,0x28bb);
    lexer_gathering_asm_args=0;if(InitGList(&lexer_inclfromlist,256)) lexer_error(0,0x28bb);
    lexer_lines=0;now_time=time(0);iflevel=0;lexer_incltoken=0;lexer_macro_stacks=0;lexer_pragmaonce=0;lexer_incondexpr=0;lexer_record_tokens=0;
    memclrw(pp_macrohashtable,8192);lexer_insert_special_macros();
    if(InitGList(&lexer_iglist,256)) lexer_error(0,0x28bb);
    lexer_igtext=preprocessor_new_string_file(GetHashNameNodeExport("(include guard test)"),2,"",0,0);
    lexer_first_line_file=0;lexer_readahead=0;lexer_readaheadmax=0;lexer_readaheadsize=lexer_readaheadmax;lexer_readaheadidx=0;
}

extern UInt8 fn_0070f1af,fn_0070f1b1,fn_0070f1f9,fn_0070f1ca,fn_0070f1cc;
extern SInt8 scanner_hexvals[256];
extern UInt8 unichar_flags[];
UInt32 parseescape(LexerToken *token,char **input,UInt8 *unicode)
{
    char spelling[2];UInt32 value,number=0;int count,digit,i;
    spelling[0]=*(*input)++;value=(SInt32)spelling[0];*unicode=0;
    switch(value) {
    case 'a':return 7;case 'b':return 8;case 'e':return 27;case 'f':return 12;
    case 'n':return fn_0070f1b1?13:10;
    case 'r':return fn_0070f1b1?10:13;
    case 't':return 9;case 'v':return 11;
    case 'x':
        count=0;
        for(;;) {
            digit=(UInt32)(SInt32)**input<256?scanner_hexvals[(SInt32)**input]:-1;
            if(digit==-1) break;
            number=number*16+digit;count++;(*input)++;
        }
        if(!count) lexer_error(token,0x2774);return number;
    case 'u':count=4;break;
    case 'U':count=8;break;
    default:
        if((SInt32)value>=48 && (SInt32)value<=55) {
            value-=48;
            for(count=1;count<3 && **input>=48 && **input<=55;count++) value=value*8+*(*input)++-48;
        } else if(value!='\\' && value!='\'' && value!='?' && value!='"') {
            spelling[1]=0;
            if(fn_0070f1ca) lexer_error(token,0x28c0,spelling);
            else if(fn_0070f1f9) lexer_warning(token,0x28c0,spelling);
        }
        return value;
    }
    *unicode=1;
    for(i=0;i<count;i++) {
        digit=(UInt32)(SInt32)**input<256?scanner_hexvals[(SInt32)**input]:-1;
        if(digit==-1) break;
        number=number*16+digit;(*input)++;
    }
    if(digit==-1) lexer_error(token,0x2774);
    if(fn_0070f1af && ((number<160 && (unichar_flags[number]&0x80)) || (number>=0xd800 && number<=0xdfff))) lexer_error(token,0x28ce,number);
    return number;
}
#pragma pack(push,2)
typedef struct Number64 { UInt32 high,low; } Number64;
typedef struct NumericType { SInt16 kind; SInt32 size; UInt8 rest[2]; } NumericType;
#pragma pack(pop)
extern NumericType stfloat,stdouble,stlongdouble;
extern Number64 cint64_zero;
extern Number64 CMach_CalcFloatConvert(NumericType *,Number64);
extern void *CMach_FloatScan(char *,Number64 *,UInt8 *);
extern char *CInt64_ScanHexString(Number64 *,char *,UInt8 *),*CInt64_ScanBinString(Number64 *,char *,UInt8 *),*CInt64_ScanOctString(Number64 *,char *,UInt8 *),*CInt64_ScanDecString(Number64 *,char *,UInt8 *);
extern char *(*fn_007106d0)(CompilerToken *,char *);
extern void parseintsuffix(LexerToken *,CompilerToken *,char *,UInt8);
extern char *lexer_scan_hexfloat(char *,Number64 *,UInt8 *,UInt8 *);
void parsefloatsuffix(LexerToken *token,CompilerToken *result,char *suffix)
{
    SInt16 datatype;Number64 *number=(Number64 *)result->payload;
    switch(*suffix) {
    case 'f':case 'F':suffix++;datatype=14;if(stfloat.size!=stlongdouble.size) *number=CMach_CalcFloatConvert(&stfloat,*number);break;
    case 'l':case 'L':suffix++;datatype=17;break;
    case 'd':case 'D':if(fn_0070f1af) break;suffix++;datatype=16;if(stdouble.size!=stlongdouble.size) *number=CMach_CalcFloatConvert(&stdouble,*number);break;
    case 0:
        if(fn_0070f1cc) { datatype=14;if(stfloat.size!=stlongdouble.size) *number=CMach_CalcFloatConvert(&stfloat,*number); }
        else { datatype=16;if(stdouble.size!=stlongdouble.size) *number=CMach_CalcFloatConvert(&stdouble,*number); }
        break;
    }
    if(*suffix) { lexer_error(token,0x28cb);datatype=16; }
    result->flags=datatype;
}
void parsenumber(LexerToken *token,CompilerToken *result,UInt8 custom)
{
    char *cursor=token->value,*suffix;UInt8 overflow,failed,range,octal;Number64 *number=(Number64 *)result->payload;
    char *(*callback)(CompilerToken *,char *);
    if(custom && (callback=fn_007106d0)!=0 && (suffix=callback(result,cursor))!=0 && !*suffix) return;
    if(*cursor=='0') {
        cursor++;
        if(*cursor=='x' || *cursor=='X') {
            for(;*cursor;cursor++) if(*cursor=='p' || *cursor=='P') break;
            if(!*cursor) { result->kind=-1;suffix=CInt64_ScanHexString(number,(char *)token->value+2,&overflow);parseintsuffix(token,result,suffix,1);return; }
            result->kind=-2;result->flags=0;suffix=lexer_scan_hexfloat(token->value,number,&failed,&range);
            if(failed) lexer_error(token,0x27aa);else if(range && fn_0070f1f9) lexer_warning(token,0x28d2);
            parsefloatsuffix(token,result,suffix);return;
        }
        if(!fn_0070f1af && (*cursor=='b' || *cursor=='B')) { result->kind=-1;suffix=CInt64_ScanBinString(number,(char *)token->value+2,&overflow);parseintsuffix(token,result,suffix,1);return; }
        octal=1;
    } else octal=0;
    for(;*cursor>=48 && *cursor<=57;cursor++) {}
    if(*cursor=='.' || *cursor=='E' || *cursor=='F' || *cursor=='e' || *cursor=='f') {
        result->kind=-2;result->flags=0;suffix=CMach_FloatScan(token->value,number,&failed);
        if(failed) lexer_error(token,0x27aa);parsefloatsuffix(token,result,suffix);
    } else {
        result->kind=-1;result->flags=0;
        suffix=octal?CInt64_ScanOctString(number,token->value,&overflow):CInt64_ScanDecString(number,token->value,&overflow);
        if(overflow) { if(fn_0070f1af) lexer_error(token,0x27aa);else lexer_warning(token,0x27aa);*number=cint64_zero; }
        parseintsuffix(token,result,suffix,octal);
    }
}

char *preprocesstoken(SInt16 kind,void *value,SInt32 size,UInt8 escape)
{
    char *text=value,*prefix="",*cursor,*result,*scan;SInt32 extra=0;
    UInt8 character=kind<=-9 && kind>=-11,string=kind<=-12 && kind>=-14;
    if(!character && !string) return text;
    if(kind==-10 || kind==-13) prefix="L";else if(kind==-11 || kind==-14) prefix="__L32";
    if(escape) for(scan=text;*scan;scan++) if(*scan=='"' || *scan=='\\') extra++;
    size+=character?2:escape?4:2;
    result=aalloc(strlen(prefix)+strlen(text)+size+extra+1);strcpy(result,prefix);cursor=result+strlen(prefix);
    if(character) *cursor++='\'';else { if(escape) *cursor++='\\';*cursor++='"'; }
    for(scan=text;*scan;scan++) { if(escape && (*scan=='"' || *scan=='\\')) *cursor++='\\';*cursor++=*scan; }
    if(character) *cursor++='\'';else { if(escape) *cursor++='\\';*cursor++='"'; }
    *cursor=0;return result;
}
SInt16 expandmacrotoken(Macro *macro,UInt8 **input,MacroNode **out)
{
    UInt16 encoding=(*input)[0]|((*input)[1]<<8);UInt8 flags=0;MacroNode *token;
    if(!encoding) { *out=0;return 0; }
    *input+=2;token=aalloc(12);*out=token;token->kind=(SInt16)(encoding<<2)>>2;
    if(encoding&0x4000) flags|=1;
    if(encoding&0x8000) { flags|=**input;(*input)++; }
    token->flags=flags;
    if(flags&0x20) { token->text=(char *)*input;*input+=strlen(token->text)+1; }
    else if(flags&4) token->text=macro?((HashName **)((char *)macro+32))[token->kind-1]->text:"<arg>";
    else if((UInt32)(SInt32)token->kind<256) token->text=(char *)&asciistring[token->kind*2];
    else token->text=scanner_get_token_text(token->kind);
    token->next=0;return token->kind;
}
extern SInt16 readmacrotoken(MacroStream *,MacroNode **);
UInt8 gathermacroargument(UInt8 variadic,MacroList *list)
{
    MacroNode *node,*copy;SInt16 kind;SInt32 level=0;SourceRef ref;
    list->head=list->current=0;kind=readmacrotoken(0,&node);
    for(;;) {
        if(!level && (kind==')' || (!variadic && kind==','))) break;
        if(!kind) {
            if(lexer->stream) ref=lexer->stream->ref;else lexer_getsourceref(&ref);
            lexer_error_at_sourceref(&ref,0x2776);break;
        }
        if(kind!=-7) {
            if(lexer->stream) { copy=aalloc(12);*copy=*node;copy->next=0; }
            else copy=node;
            if(list->current) list->current->next=copy;else list->head=copy;
            list->current=copy;
            if(kind=='(') level++;else if(kind==')') level--;
        }
        kind=readmacrotoken(0,&node);
    }
    return kind==0 || kind==')';
}
char *lexer_macro_encode_text(char *text,UInt8 encoding,SInt32 *size)
{
    LexerToken token={0};SourceRef ref;char *result;
    lexer_mlist.size=0;
    if(!strcmp(text,"0") || !strcmp(text,"1")) {
        token.kind=-8;token.value=text;token.value2=strlen(text);token.tail.length=token.value2;appendmacrotoken(&lexer_mlist,&token,0);
    } else {
        lexer_getsourceref(&ref);
        if(!lexer_push_string("(special compiler macro)",text,strlen(text),encoding,&ref,1,1,0)) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_macro_encode_text",3892);
        while(lexer_readtoken_impl(&token)) appendmacrotoken(&lexer_mlist,&token,token.kind==-3?0x40:0);
        lexer_pop();
    }
    *size=lexer_mlist.size;appendmacrotoken(&lexer_mlist,0,0);
    result=aalloc(lexer_mlist.size);memcpy(result,*(void **)lexer_mlist.data,lexer_mlist.size);return result;
}
extern UInt8 peekparen(MacroStream *,UInt8);
void lexer_reparse_macro(SourceRef *ref)
{
    MacroStream *stop=lexer->stream;MacroNode *token;SInt16 kind=0,previous=0;SInt32 depth,size;char *text;
    lexer_asmlist.size=0;
    while(stop && stop->next) stop=stop->next;
    if(!stop) return;
    while(lexer->stream && (kind=readmacrotoken(stop,&token))!=0) {
        if(token->flags&1) AppendGListByte(&lexer_asmlist,32);
        AppendGListName(&lexer_asmlist,preprocesstoken(token->kind,token->text,strlen(token->text),0));previous=kind;
    }
    if(previous==-3 && peekparen(0,0)) {
        depth=0;
        do {
            kind=readmacrotoken(0,&token);if(!kind) break;
            if(kind=='(') depth++;else if(kind==')') depth--;
            if(token->flags&1) AppendGListByte(&lexer_asmlist,32);
            AppendGListName(&lexer_asmlist,preprocesstoken(token->kind,token->text,strlen(token->text),0));
        } while(depth>0);
    }
    size=lexer_asmlist.size;text=galloc(size);memcpy(text,*(void **)lexer_asmlist.data,size);lexer_asmlist.size=0;
    if(!lexer_push_string("(asm macro expansion)",text,size,2,ref,1,0,0)) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_reparse_macro",4885);
}

#pragma pack(push,2)
typedef struct IfState { LexerToken token; SInt16 mode; SInt32 savedSize; UInt8 hadToken, valid, seen, unknown25; } IfState;
#pragma pack(pop)
extern IfState ifstack[256];
extern LexerToken if_tok;
extern SInt32 ig_entry_iglist_size;
extern SInt16 igtlevel;
extern UInt8 ig_entry_had_token;
extern SourceRef igtest_start_ref,igtest_end_ref;
extern char *igtip;
extern void prepifskip(void),igtdirective(void),scanner_converttoascii(GList *,char *,UInt8,SInt32,SInt32);
static __inline void ig_boundary_impl(void)
{
    if(lexer_iglist.size==lexer->savedIgSize || (*(char **)lexer_iglist.data)[lexer_iglist.size-1]!='$') AppendGListByte(&lexer_iglist,'$');
    if(iflevel>0) ifstack[iflevel-1].seen=1;
}
void popifstate(void)
{
    SInt16 mode;
    if(iflevel<1) { lexer_error(&if_tok,0x2785);return; }
    if(ifstack[iflevel-1].mode==0 || ifstack[iflevel-1].mode==1 || !ifstack[iflevel-1].valid) {
        if(iflevel>1) ifstack[iflevel-2].valid=0;
    } else { lexer_iglist.size=ifstack[iflevel-1].savedSize;ig_boundary_impl(); }
    lexer->flag28=ifstack[iflevel-1].hadToken;
    mode=ifstack[iflevel-1].mode;
    switch(mode) { case 1:case 3:case 4:iflevel--;return; }
    iflevel--;
    if(iflevel>0) switch(ifstack[iflevel-1].mode) { case 1:case 3:case 4:prepifskip();return; }
}
void negativeif(UInt8 skipping)
{
    if(iflevel<256) {
        ifstack[iflevel].mode=skipping?1:3;ifstack[iflevel].token=if_tok;
        ifstack[iflevel].savedSize=ig_entry_iglist_size;ifstack[iflevel].hadToken=ig_entry_had_token;
        ifstack[iflevel].valid=1;ifstack[iflevel].seen=0;iflevel++;
    } else {
        lexer_error(&if_tok,0x27e7);iflevel=0;
        if(lexer) while(lexer->stream) lexer_pop_mstream_impl();
        Msg_FatalJump(pp_msgcontext);
    }
    if(skipping) prepifskip();
}
static __inline void ig_finish_directive_impl(SInt8 marker)
{
    if(iflevel>0 && !ifstack[iflevel-1].hadToken) {
        if(lexer->flag28) ig_boundary_impl();
        else if((*(char **)lexer_iglist.data)[lexer_iglist.size-1]!='$') ifstack[iflevel-1].valid=0;
        AppendGListByte(&lexer_iglist,'#');AppendGListByte(&lexer_iglist,marker);
    }
}
void lexer_prependif(LexerToken *token)
{
    if_tok=*token;
    if(iflevel>0) {
        if(fn_0070f1af) lexer_matchendofline();else lexer_skipendofline();
        ig_finish_directive_impl('f');popifstate();return;
    }
    if(!ifstack[iflevel-1].hadToken) AppendGListByte(&lexer_iglist,'?');
    lexer_error(token,0x2786);lexer_skipendofline();
}
void lexer_prepelse(LexerToken *token)
{
    if_tok=*token;
    if(iflevel>0 && ifstack[iflevel-1].mode!=2 && ifstack[iflevel-1].mode!=4) {
        if(fn_0070f1af) lexer_matchendofline();else lexer_skipendofline();
        ig_finish_directive_impl('e');lexer->flag28=ifstack[iflevel-1].hadToken;
        switch(ifstack[iflevel-1].mode) {
        case 0:ifstack[iflevel-1].mode=4;prepifskip();return;
        case 1:ifstack[iflevel-1].mode=2;return;
        case 3:ifstack[iflevel-1].mode=4;return;
        default:preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_prepelse",6793);return;
        }
    }
    if(!ifstack[iflevel-1].hadToken) AppendGListByte(&lexer_iglist,'?');
    lexer_error(token,0x2786);lexer_skipendofline();
}
void ig_save_if(SInt8 marker)
{
    UInt8 hadToken=marker=='i'?ig_entry_had_token:ifstack[iflevel-1].hadToken;
    if(!hadToken) {
        if(igtest_start_ref.file==igtest_end_ref.file && igtest_start_ref.offset<igtest_end_ref.offset) {
            if(marker=='l') {
                if(lexer->flag28) ig_boundary_impl();
                else if((*(char **)lexer_iglist.data)[lexer_iglist.size-1]!='$' && iflevel>0) ifstack[iflevel-1].valid=0;
            }
            AppendGListByte(&lexer_iglist,'#');AppendGListByte(&lexer_iglist,marker);
            scanner_converttoascii(&lexer_iglist,lexer->file->contents,lexer->file->unknown09,igtest_start_ref.offset,igtest_end_ref.offset);
            AppendGListByte(&lexer_iglist,10);
        } else if(!ifstack[iflevel-1].hadToken) AppendGListByte(&lexer_iglist,'?');
    }
}
void lexer_prepundef(void)
{
    LexerToken token;HashName *name;Macro *macro,*previous=0;
    if(!lexer_readtokenorskip(&token,-3,0x277b)) return;
    lexer->flag28=1;name=GetHashNameNodeExport(token.value);
    for(macro=pp_macrohashtable[name->hash];macro;previous=macro,macro=macro->next) if(macro->name==name) {
        if(macro->flags&16) macro=0;
        else if(macro->flags&8) { Macro *(*callback)(Macro *)=fn_007106a8;if(callback) macro=callback(macro); }
        break;
    }
    if(macro) { if(previous) previous->next=macro->next;else pp_macrohashtable[name->hash]=macro->next; }
}
void pragma_once(UInt8 once)
{
    LexerToken token;LexerFile *file;
    if(lexer_readtoken_impl(&token)!=-3) {
        lexer_unreadtoken(&token);file=lexer->file;
        if(file && file->kind==0) { *((UInt8 *)file->diskInfo+14)=once;if(!once) lexer->flag28=1; }
    } else if(!once) lexer_error(&token,0x27ca);
    else if(!strcmp(token.value,"on")) lexer_pragmaonce=1;
    else if(!strcmp(token.value,"off")) { lexer_pragmaonce=0;lexer->flag28=1; }
}
UInt8 ig_test(LexerFile *file)
{
    char *text;UInt8 saved;
    if(file->kind) return 0;
    text=*(char **)((char *)file->diskInfo+8);
    if(!text) return 0;
    if(lexer) { saved=lexer->flag29;lexer->flag29=1; } else saved=0;
    igtlevel=0;
    while(*text && *text!='$' && *text!='?') {
        igtip=text+1;
        if(*text!='#') preprocessor_internal_msg(1,0,"CPrepLexer.c","ig_test",5357);
        igtdirective();text=igtip;
    }
    igtip=text;if(lexer) lexer->flag29=saved;
    return *text==0;
}
extern char *parse_include_name(LexerToken *,UInt8 *,UInt8);
extern UInt8 lexer_push_include_file(char *,UInt8,UInt8,UInt8,LexerFile **);
void lexer_prepinclude(UInt8 once)
{
    LexerToken token;UInt8 flag;LexerFile *file;char *name;
    lexer->flag28=1;name=parse_include_name(&token,&flag,0);
    if(!name) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_prepinclude",7182);
    lexer_incltoken=&token;
    if(!lexer_push_include_file(name,flag,0,0,&file)) { lexer_error(&token,0x27a7,name);lexer_skipendofline(); }
    else if(once && file && file->kind==0) *((UInt8 *)file->diskInfo+14)=1;
    lexer_incltoken=0;
}

extern void scanner_resync(void);
SInt16 readmacrotoken(MacroStream *stop,MacroNode **out)
{
    UInt8 space=0;UInt16 kind;LexerToken raw;LexerState *saved;MacroNode *node;
    for(;;) {
        while(lexer->stream) {
            *out=lexer->stream->tokens.current;
            if(*out) break;
            if(lexer->stream==stop) return 0;
            space=1;lexer_pop_mstream_impl();
        }
        if(!lexer->stream) {
            saved=lexer;
            for(;;) {
                kind=lexer_readtoken_impl(&raw);
                if(kind || !lexer_gathering_asm_args || !lexer->parent || lexer->flag25 || lexer->file->kind!=2) break;
                *lexer->scannerSave=scanner;lexer=lexer->parent;scanner=*lexer->scannerSave;scanner_resync();
            }
            if(lexer!=saved) { *lexer->scannerSave=scanner;lexer=saved;scanner=*saved->scannerSave;scanner_resync(); }
            if(raw.space) space=1;
            node=aalloc(12);*out=node;node->kind=raw.kind;node->flags=space;node->text=aalloc(raw.value2+1);memcpy(node->text,raw.value,raw.value2+1);node->next=0;
            return kind;
        }
        kind=(*out)->kind;
        if(lexer->stream->tokens.current) {
            lexer->stream->tokens.previous=lexer->stream->tokens.current;
            lexer->stream->tokens.current=lexer->stream->tokens.current->next;
        }
        if(kind==(UInt16)-7) continue;
        if(*out) (*out)->flags|=space;return kind;
    }
}
SInt16 lexer_readmacrotoken(MacroStream *stop,LexerToken *raw,UInt8 *flags)
{
    UInt8 space=0;UInt16 kind;MacroNode *node;LexerState *saved;
    for(;;) {
        saved=lexer;
        while(lexer->stream) {
            node=lexer->stream->tokens.current;
            if(node || lexer->stream==stop) break;
            space=1;lexer_pop_mstream_impl();
        }
        if(!lexer->stream) {
            for(;;) {
                kind=lexer_readtoken_impl(raw);
                if(kind || !lexer_gathering_asm_args || !lexer->parent || lexer->flag25 || lexer->file->kind!=2) break;
                *lexer->scannerSave=scanner;lexer=lexer->parent;scanner=*lexer->scannerSave;scanner_resync();
            }
            if(space || raw->space) { raw->space=1;*flags=1; } else *flags=0;
            if(lexer!=saved) { *lexer->scannerSave=scanner;lexer=saved;scanner=*saved->scannerSave;scanner_resync(); }
            return kind;
        }
        kind=node->kind;
        if(lexer->stream->tokens.current) {
            lexer->stream->tokens.previous=lexer->stream->tokens.current;
            lexer->stream->tokens.current=lexer->stream->tokens.current->next;
        }
        if(kind==(UInt16)-7) continue;
        *flags=node->flags|space;raw->kind=node->kind;raw->value=node->text;raw->tail.length=strlen(raw->value);raw->value2=raw->tail.length;
        raw->space=(node->flags&1)!=0;raw->bol=0;
        if(lexer->stream) raw->ref=lexer->stream->ref;else scanner_getsourceref(0,&raw->ref);
        if(lexer_record_tokens) {
            if(raw->space && !raw->bol) AppendGListByte(&lexer_dlist,32);
            AppendGListName(&lexer_dlist,preprocesstoken(raw->kind,raw->value,raw->value2,0));
        }
        return kind;
    }
}
UInt8 peekparen(MacroStream *stop,UInt8 stopAtEnd)
{
    LexerState *saved=lexer;MacroStream *stream;MacroList list;MacroNode *token;SInt16 kind;ScannerPosition position;LexerToken raw;UInt8 recording;
    for(stream=lexer->stream;stream;stream=stream->next) {
        list=stream->tokens;
        while((token=list.current)!=0) {
            kind=token->kind;
            if(kind!=-7 && kind!=-17 && kind!=-19 && kind!=-20) return kind==40;
            if(token) { list.previous=token;list.current=list.current->next; }
        }
        if(stopAtEnd && stream==stop) return 0;
    }
    scanner_getstate(&position);recording=lexer_record_tokens;lexer_record_tokens=0;
    for(;;) {
        do { kind=lexer_readtoken_impl(&raw); } while(kind==-7 || kind==-17);
        if(kind || !lexer->parent || lexer->flag25 || lexer->file->kind!=2) break;
        if(lexer==saved) *lexer->scannerSave=scanner;
        lexer=lexer->parent;scanner=*lexer->scannerSave;scanner_resync();
    }
    if(lexer!=saved) { lexer=saved;scanner=*saved->scannerSave;scanner_resync(); }
    scanner_setstate(&position);lexer_record_tokens=recording;return kind==40;
}
extern UInt8 cprep_in_assembler;
extern void (*fn_00710694)(void);
extern void lexer_expand_macro(Macro *,UInt8,SourceRef *,MacroList *),lexer_directive(LexerToken *,UInt8);
static __inline UInt8 kwcheck_impl(Keyword *keyword,HashName *name)
{
    switch(keyword->condition) {
    case 0:return 1;case 1:return 0;
    case 2:return *(UInt8 *)keyword->handler!=0;
    case 3:return *(UInt8 *)keyword->handler==0;
    case 4:return ((UInt8 (*)(char *,SInt16))keyword->handler)(name->text,keyword->token);
    default:preprocessor_internal_msg(1,0,"CPrepLexer.c","kwcheck",8192);return 0;
    }
}
SInt16 lexer_plex(LexerToken *raw)
{
    UInt8 carry=0,flags,recording,savedAsm,hasAsm;SInt16 kind;HashName *name;Macro *macro;MacroList *list;MacroNode *node;Keyword *keyword;
    for(;;) {
        if(!lexer) { raw->kind=0;return raw->kind; }
        kind=lexer_readmacrotoken(0,raw,&flags);raw->space|=carry;carry=0;
        if(kind==-17) return raw->kind;
        if(kind==-7) {
            lexer->unread=1;
            if(!lexer->stream) {
                SInt32 lines=scanner.position.line-lexer->unknown18;
                if(lines>0) lexer_lines+=lines;lexer->unknown18=scanner.position.line;
                if(fn_00710694) fn_00710694();
            }
            return raw->kind;
        }
        if(kind==-3) {
            if(!lexer_in_directive) lexer->flag28=1;
            if(lexer->macroLocks || (flags&0x40)) return raw->kind;
            name=GetHashNameNodeExport(raw->value);macro=lexer_lookup_macro(name);
            if(!macro || (macro->flags&4)) return raw->kind;
            raw->value=name->text;
            if(macro->argCount && !peekparen(0,0)) return raw->kind;
            recording=0;
            if(lexer_record_tokens) {
                recording=1;
                if(raw->space && !raw->bol) lexer_dlist.size--;
                lexer_dlist.size-=strlen(preprocesstoken(raw->kind,raw->value,raw->value2,0));lexer_record_tokens=0;
            }
            list=aalloc(8);lexer_expand_macro(macro,flags,&raw->ref,list);
            hasAsm=0;
            if(!cprep_in_assembler) {
                for(node=list->head;node;node=node->next) if(node->kind==-3 && strstr(node->text,"asm")) {
                    name=GetHashNameNodeExport(node->text);
                    for(keyword=lexer_kwhash[name->hash];keyword;keyword=keyword->next) if(keyword->name==name && kwcheck_impl(keyword,name)) break;
                    if(keyword && keyword->token==0x144) { hasAsm=1;break; }
                }
            } else hasAsm=1;
            if(hasAsm) { savedAsm=lexer_gathering_asm_args;lexer_gathering_asm_args=1;lexer_reparse_macro(&raw->ref);lexer_gathering_asm_args=savedAsm; }
            else carry=raw->space;
            lexer_record_tokens=recording;
        } else if(!kind) {
            if(lexer->flag25 || !lexer_pop()) return raw->kind;
        } else if(kind=='#' && !lexer->stream && raw->bol) lexer_directive(raw,0);
        else { if(!lexer_in_directive) lexer->flag28=1;return raw->kind; }
    }
}

extern UInt8 fn_0070f1b3,fn_0070f1bd;
extern NumericType stsignedint,stunsignedint,stsignedlong,stunsignedlong,stsignedlonglong;
extern UInt8 CInt64_IsInRange(Number64,SInt16),CInt64_IsInURange(Number64,SInt16);
void parseintsuffix(LexerToken *raw,CompilerToken *result,char *suffix,UInt8 octal)
{
    UInt8 uns=0,islong=0,islonglong=0;char *cursor=suffix;Number64 *number=(Number64 *)result->payload;
    switch(*suffix) {
    case '+':case '-':lexer_error(raw,0x2901,suffix);break;
    case 'L':case 'l':
        islong=1;cursor++;
        if(*cursor=='u'||*cursor=='U') { uns=1;cursor++; }
        else if(fn_0070f1bd&&(*cursor=='l'||*cursor=='L')) { islonglong=1;cursor++;if(*cursor=='u'||*cursor=='U') {uns=1;cursor++;} }
        break;
    case 'I':case 'i':
        if(fn_0070f1b3&&!fn_0070f1af&&fn_0070f1bd) {
            cursor++;if(*cursor=='6') {cursor++;if(*cursor=='4') {islong=islonglong=1;cursor++;}}
        }
        break;
    case 'U':case 'u':
        uns=1;cursor++;if(*cursor=='l'||*cursor=='L') {islong=1;cursor++;if(fn_0070f1bd&&(*cursor=='l'||*cursor=='L')) {islonglong=1;cursor++;}}
        break;
    }
    if(number->high&0x80000000) {
        if(!islong&&!uns&&!octal&&fn_0070f1ca&&fn_0070f1bd) {if(fn_0070f1af) goto overflow;lexer_warning(raw,0x27aa);}
        uns=1;
    }
    if(*cursor) {lexer_error(raw,0x28ca);result->flags=7;return;}
    if(!islonglong&&!islong) {
        if(!uns&&CInt64_IsInRange(*number,(SInt16)stsignedint.size)) {result->flags=7;return;}
        if((octal||uns)&&CInt64_IsInURange(*number,(SInt16)stunsignedint.size)) {result->flags=8;return;}
    }
    if(!islonglong) {
        if(!uns&&CInt64_IsInRange(*number,(SInt16)stsignedlong.size)) {result->flags=9;return;}
        if(!islong&&!uns&&fn_0070f1ca&&fn_0070f1bd) {
            if(CInt64_IsInRange(*number,(SInt16)stsignedlonglong.size)) {result->flags=11;return;} goto overflow;
        }
        if(CInt64_IsInURange(*number,(SInt16)stunsignedlong.size)) {result->flags=10;return;}
    }
    if(fn_0070f1bd) {
        if(!uns&&CInt64_IsInRange(*number,(SInt16)stsignedlonglong.size)) {result->flags=11;return;}
        if(CInt64_IsInURange(*number,(SInt16)stsignedlonglong.size)) {result->flags=12;return;}
    }
overflow:lexer_error(raw,0x27aa);*number=cint64_zero;result->flags=7;
}
char *parsefilename(char *text)
{
    SInt32 length=0,original=0;char *cursor=text,*result,*dest;
    while(*cursor) {if(*cursor=='\\'&&(cursor[1]=='\\'||cursor[1]=='"')) length--;cursor++;length++;original++;}
    if(length==original) return text;
    result=aalloc(length+1);dest=result;
    while(*text) {if(*text=='\\'&&(text[1]=='\\'||text[1]=='"')) {text++;*dest=*text;}else *dest=*text;dest++;text++;}
    *dest=0;return result;
}
void lexer_skipendofline(void)
{
    LexerToken raw;SInt16 kind;
    if(!lexer_record_tokens) {while(lexer->stream) lexer_pop_mstream_impl();scanner_skipendofline();}
    else {
        while(lexer->stream) lexer_plex(&raw);
        do {kind=lexer_readtoken_impl(&raw);}while(kind!=-7&&raw.kind);
        lexer_unreadtoken(&raw);
    }
}
extern SInt16 scanner_peektoken(LexerToken *);
void ig_skipline(UInt8 active)
{
    UInt8 saved;SInt16 kind;LexerToken raw;
    if(!active) {saved=lexer->flag28;lexer_skipendofline();lexer->flag28=saved;}
    else {kind=scanner_peektoken(&raw);if(kind!=-7&&kind!=-17) {ig_boundary_impl();lexer->flag28=1;}if(kind!=-7) lexer_skipendofline();}
}
SInt16 stringizemlist(SourceRef *ref,MacroList *list,MacroNode *result)
{
    MacroNode *node=list->head,*first=0;char *buffer=0,*oldBuffer=0,*dest=0,*text;SInt32 size=0,capacity=0,length,required;
    while(node) {
        text=preprocesstoken(node->kind,node->text,strlen(node->text),1);if(!first) first=node;
        length=strlen(text);required=length+size+2;
        if(capacity<=required) {capacity=capacity*2+required;buffer=aalloc(capacity);if(size) memcpy(buffer,oldBuffer,size);dest=buffer+size;}
        if(size>0&&(node->flags&1)) {*dest++=' ';size++;}
        memcpy(dest,text,length);dest+=length;size+=length;oldBuffer=buffer;node=node->next;
    }
    if(!dest) {buffer=aalloc(1);dest=buffer;}*dest=0;
    result->kind=-12;result->flags=first?first->flags:0;result->text=buffer;result->next=0;return -12;
}

#pragma pack(push,2)
typedef struct PPValue { Number64 value;UInt8 uns,unknown09; } PPValue;
typedef struct LexerTemp { LexerState *saved;ScannerPosition position;LexerFile *pushed; } LexerTemp;
#pragma pack(pop)
extern UInt8 lexer_skipcond,fn_0070f081,fn_0070f084,fn_0070f1b9;
extern LexerToken exprtok;
extern SInt16 exprtk;
extern NumericType stunsignedlonglong;
extern Number64 cint64_one;
extern SInt16 (*fn_007106b4)(SInt16);
extern Number64 CMach_CalcIntDiadic(NumericType *,Number64,SInt16,Number64),CMach_CalcIntMonadic(NumericType *,SInt16,Number64);
extern PPValue parseunary(void),parsebinary(PPValue *,SInt16),parsecond(void);
static __inline NumericType *pp_type(UInt8 uns)
{
    if(!fn_0070f081&&!fn_0070f1ca) return uns?&stunsignedlong:&stsignedlong;
    return uns?&stunsignedlonglong:&stsignedlonglong;
}
PPValue parsecond(void)
{
    PPValue test=parsebinary(0,-1),yes,no;UInt8 skipping=lexer_skipcond;
    if(exprtk=='?') {
        if(!test.value.high&&!test.value.low) lexer_skipcond=1;
        yes=parsecond();
        if(exprtok.kind==-7) {lexer_error(&exprtok,0x2780);return test;}
        if(exprtk!=':') {lexer_error(&exprtok,0x27ba);return test;}
        lexer_skipcond=skipping||(test.value.high||test.value.low);
        no=parsecond();test=(test.value.high||test.value.low)?yes:no;
    }
    return test;
}
PPValue parsebinary(PPValue *initial,SInt16 minimum)
{
    PPValue left,right;SInt16 operation,prec,nextprec;UInt8 skipping;
    SInt16 (*precedence)(SInt16)=fn_007106b4?fn_007106b4:ppgetprec;
    left=initial?*initial:parseunary();
    for(;;) {
        operation=exprtk;prec=precedence(operation);skipping=lexer_skipcond;
        if(!prec) return left;
        if(exprtok.kind==-7) {lexer_error(&exprtok,0x2780);return left;}
        if(operation==373&&!left.value.high&&!left.value.low) lexer_skipcond=1;
        if(operation==372&&(left.value.high||left.value.low)) lexer_skipcond=1;
        right=parseunary();lexer_skipcond=skipping;
        for(;;) {
            if(exprtk==')'||exprtok.kind==-7) {
                if(right.uns) left.uns=1;
                left.value=CMach_CalcIntDiadic(pp_type(left.uns),left.value,operation,right.value);return left;
            }
            nextprec=precedence(exprtok.kind);
            if(nextprec<=prec||!nextprec) break;
            right=parsebinary(&right,prec);
        }
        if(right.uns) left.uns=1;
        left.value=CMach_CalcIntDiadic(pp_type(left.uns),left.value,operation,right.value);
        if(!nextprec) return left;
        if(precedence(nextprec)<=minimum) return left;
    }
}
PPValue parseunary(void)
{
    PPValue result;CompilerToken converted;UInt8 flags,parenthesized;UInt32 datatype;Macro *macro;
    lexer_plex(&exprtok);exprtk=lexer_convert_to_token(&exprtok,&converted,0,1);
    if(exprtk==-7) {lexer_error(&exprtok,0x2780);result.value=cint64_zero;result.uns=0;}
    else if(exprtk==-3) {
        if(!strcmp(exprtok.value,"true")) {result.value=cint64_one;result.uns=1;}
        else if(!strcmp(exprtok.value,"false")) {result.value=cint64_zero;result.uns=1;}
        else {
            result.value=cint64_zero;result.uns=0;
            if(!strcmp(exprtok.value,"defined")) {
                exprtk=lexer_readmacrotoken(0,&exprtok,&flags);parenthesized=exprtk=='(';
                if(!parenthesized||lexer_readmacrotokenorskip(&exprtok,-3,0x277b)) {
                    macro=lexer_lookup_macro(GetHashNameNodeExport(exprtok.value));if(macro) result.value=cint64_one;
                    if(parenthesized) lexer_readmacrotokenorskip(&exprtok,')',0x2783);
                }
            } else if(!lexer_skipcond&&fn_0070f084) lexer_warning(&exprtok,0x28de,exprtok.value);
        }
    } else if(exprtk==-1) {
        result.value=*(Number64 *)converted.payload;datatype=(UInt32)(converted.flags-3);
        result.uns=(datatype<10&&((1U<<datatype)&0x2a9))||(converted.flags==2&&fn_0070f1b9);
    } else if(exprtk=='!') {result=parseunary();result.value.low=!result.value.high&&!result.value.low;result.value.high=0;return result;}
    else if(exprtk=='(') {result=parsecond();if(exprtk!=')') {lexer_error(&exprtok,0x2783);return result;}}
    else if(exprtk=='+') return parseunary();
    else if(exprtk=='-'||exprtk=='~') {SInt16 op=exprtk;result=parseunary();result.value=CMach_CalcIntMonadic(pp_type(result.uns),op,result.value);return result;}
    else {
        result.uns=1;
        if(!strcmp(exprtok.value,"true")) result.value=cint64_one;
        else if(!strcmp(exprtok.value,"false")) result.value=cint64_zero;
        else {lexer_error(&exprtok,0x28c8);result.value=cint64_zero;}
    }
    if(lexer_plex(&exprtok)==-7) {lexer_unreadtoken(&exprtok);exprtk=0;}
    else exprtk=lexer_convert_to_token(&exprtok,&converted,0,1);
    return result;
}
extern UInt8 fn_0070f1da,fn_0070f08c,fn_0070f1a8,fn_0070f1e5;
extern void fn_00449d60(void);
void lexer_macro_redef_error(LexerToken *raw,Macro *macro,UInt8 *reported)
{
    UInt8 emit=1,fatal=1,saved;
    if(*reported) return;
    if((fn_0070f1da&&!fn_0070f1af)||(fn_0070f1b3&&!fn_0070f1af)) fatal=0;
    if(fn_0070f08c&&!fn_0070f1a8) emit=0;
    if(emit) {
        if(fatal) {
            lexer_error(raw,0x277c,macro->name->text);saved=fn_0070f1e5;
            if(!macro->ref.file) goto done;fn_0070f1e5=0;fn_00449d60();
        } else {lexer_warning(raw,0x277c,macro->name->text);saved=fn_0070f1e5;if(!macro->ref.file) goto done;fn_0070f1e5=0;}
        lexer_info_at_sourceref(&macro->ref,0x28c4);fn_0070f1e5=saved;
    }
done:*reported=1;
}
UInt8 lexer_temp_push(LexerFile *file,LexerTemp *temp)
{
    LexerState *state=lexer;ScannerState *restore;
    temp->pushed=0;temp->saved=0;
    while(state) {
        if(state->file==file) restore=state->scannerSave;
        else if(state->logicalFile&&state->forceLogical&&state->logicalFile->file==file) restore=state->forceLogical;
        else {state=state->parent;continue;}
        *lexer->scannerSave=scanner;scanner_getstate(&temp->position);temp->saved=lexer;
        lexer=state;scanner=*restore;scanner_resync();return 1;
    }
    return lexer_push_file(file,1,1,&temp->pushed);
}
extern void scanner_goto_line(SInt32);
void lexer_flattensourceref(SourceRef *ref,UInt8 physical)
{
    LexerFile *file;LogicalLineFile *logical;LexerTemp temp;SInt32 line;
    for(;;) {
        file=ref->file;if(!file) return;
        switch(file->kind) {
        case 0:return;
        case 1:
            logical=(LogicalLineFile *)file;
            if(physical&&logical->file&&lexer_temp_push(logical->file,&temp)) {
                line=ref->line-logical->sourceLine+logical->logicalLine;
                if(line<0) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_flattensourceref",1307);
                scanner_goto_line(line);ref->file=scanner.file;ref->offset=scanner.position.current-scanner.base;ref->line=scanner.position.line;ref->file=logical->file;
                if(temp.pushed) lexer_pop();
                else if(temp.saved) {lexer=temp.saved;scanner=*temp.saved->scannerSave;scanner_resync();scanner_setstate(&temp.position);}
                return;
            }
            ref->file=file->backing;break;
        case 2:if(!file->backing) return;
        case 3:*ref=*(SourceRef *)&file->backing;break;
        default:preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_flattensourceref",1333);
        }
    }
}

extern UInt8 fn_0070f086,fn_0070f087,fn_0070f071;
extern UInt8 lexer_setupref(void *,char *,SInt32,SourceRef *,SourceRef *,void *,UInt8);
extern char *Msg_GetRsrcString(void *,SInt16),*Msg_FormatV(void *,char *,SInt32,char *,char *);
extern void *Msg_MapMsgNumToHelpIndex(void *,SInt16,char *,int);
extern UInt8 Msg_EmitCoreV(void *,SInt32,void *,char *,void *),Msg_EmitRef(void *,SInt32,void *,char *,SInt16);
extern SInt32 Msg_SetMsgFilter(void *,SInt32);
extern void Msg_FreeFormat(void *,char *);
void lexer_message_v(SourceRef *ref,void *macro,SInt32 kind,SInt16 error,char *args)
{
    char buffer[1024],line[256];UInt8 record[276];void *recordPtr,*formatted;char *linePtr,*text;SInt32 filter;
    text=Msg_FormatV(pp_msgcontext,buffer,1024,Msg_GetRsrcString(pp_msgcontext,error),args);
    if(!lexer||!lexer->flag29) {
        if(lexer_setupref(record,line,256,ref,0,macro,0)) {recordPtr=record;linePtr=line;}else {recordPtr=0;linePtr=0;}
        formatted=Msg_MapMsgNumToHelpIndex(pp_msgcontext,error,text,0);
        if(Msg_EmitCoreV(pp_msgcontext,kind,recordPtr,linePtr,formatted)&&fn_0070f086&&fn_0070f087&&lexer&&lexer->file&&lexer->logicalFile&&(void *)lexer->file!=(void *)lexer->logicalFile) {
            filter=Msg_SetMsgFilter(pp_msgcontext,0);
            if(lexer_setupref(record,line,256,ref,0,0,1)) Msg_EmitRef(pp_msgcontext,0,record,line,0x28c3);
            Msg_SetMsgFilter(pp_msgcontext,filter);
        }
    }
    if(text!=buffer) Msg_FreeFormat(pp_msgcontext,text);
}
extern void preprocessor_reconfig(UInt8 *),AppendGListData(GList *,void *,SInt32),LockGList(GList *),UnlockGList(GList *);
extern UInt8 scanner_suppress_messages(UInt8);
void lexer_prepmessage(LexerToken *raw,SInt16 kind,SInt16 error)
{
    UInt8 saved=fn_0070f071,suppression;LexerToken token;SourceRef end;char line[256];UInt8 record[276];SInt16 tokenKind;SInt32 filter;
    if(fn_0070f071!=1) {fn_0070f071=1;preprocessor_reconfig(&fn_0070f071);}
    suppression=scanner_suppress_messages(1);
    do {tokenKind=lexer_readtoken_impl(&token);}while(tokenKind!=-7&&token.kind);
    scanner_suppress_messages(suppression);
    if(token.kind==-7) lexer_unreadtoken(&token);
    end=token.ref;lexer_setupref(record,line,256,&raw->ref,&end,0,0);
    *(SInt16 *)(record+266)=0;*(void **)(record+272)=0;
    if(Msg_EmitRef(pp_msgcontext,kind,record,line,error)&&lexer->file&&lexer->logicalFile&&(void *)lexer->file!=(void *)lexer->logicalFile) {
        filter=Msg_SetMsgFilter(pp_msgcontext,0);
        if(lexer_setupref(record,line,256,&raw->ref,&end,0,1)) {*(SInt16 *)(record+266)=0;Msg_EmitRef(pp_msgcontext,kind,record,line,0x28c3);}
        Msg_SetMsgFilter(pp_msgcontext,filter);
    }
    if(fn_0070f071!=saved) {fn_0070f071=saved;preprocessor_reconfig(&fn_0070f071);}
}
char *lexer_simple_expand_string(Macro *macro,MacroList *list,MacroNode *selected,char **start,char **end,SInt32 *outSize)
{
    SInt32 savedSize=lexer_mlist.size,previousStart=0,selectedStart=-1,selectedEnd=-1;char *saved=aalloc(savedSize),*result,*text;MacroNode *node;
    memcpy(saved,*(char **)lexer_mlist.data,savedSize);lexer_mlist.size=0;
    for(node=list->head;node;node=node->next) {
        SInt32 before,loopStart=lexer_mlist.size;
        if(node->flags&1) AppendGListByte(&lexer_mlist,' ');
        before=lexer_mlist.size;if(node==selected) selectedStart=previousStart;
        if(!(node->flags&4)) text=preprocesstoken(node->kind,node->text,strlen(node->text),0);
        else {
            if(node->flags&8) AppendGListByte(&lexer_mlist,'#');
            if(!macro||macro->argCount<=node->kind-1) text="<arg>";
            else text=((HashName **)((char *)macro+32))[node->kind-1]->text;
        }
        AppendGListName(&lexer_mlist,text);
        if(node==selected) selectedEnd=loopStart;
        previousStart=before;
    }
    if(selectedStart<0) selectedStart=lexer_mlist.size;if(selectedEnd<0) selectedEnd=lexer_mlist.size;
    result=aalloc(lexer_mlist.size+1);memcpy(result,*(char **)lexer_mlist.data,lexer_mlist.size);result[lexer_mlist.size]=0;
    *outSize=lexer_mlist.size;*start=result+selectedStart;*end=result+selectedEnd;
    lexer_mlist.size=0;AppendGListData(&lexer_mlist,saved,savedSize);return result;
}
void pragma_message(LexerToken *raw)
{
    LexerToken token;GList list;char line[256],*linePtr;UInt8 record[276];void *recordPtr,*formatted;SInt32 filter;
    if(!lexer_plextokenorskip(&token,'(',0x2782)) return;
    if(InitGList(&list,128)) return;
    while(!peekeol()&&lexer_plex(&token)!=')') {if(token.space||token.bol) AppendGListByte(&list,' ');AppendGListName(&list,token.value);}
    if(!peekeol()) {lexer_plex(&token);lexer_warning(&token,0x2781);while(!peekeol()) lexer_plex(&token);}
    if(token.kind!=')') lexer_warning(&token,0x27ca);
    AppendGListByte(&list,0);LockGList(&list);
    if(!lexer||!lexer->flag29) {
        if(lexer_setupref(record,line,256,raw?&raw->ref:0,0,raw?raw->tail.macro:0,0)) {recordPtr=record;linePtr=line;}else {recordPtr=0;linePtr=0;}
        formatted=Msg_MapMsgNumToHelpIndex(pp_msgcontext,0,*(char **)list.data,0);
        if(Msg_EmitCoreV(pp_msgcontext,0,recordPtr,linePtr,formatted)&&fn_0070f086&&fn_0070f087&&lexer&&lexer->file&&lexer->logicalFile&&(void *)lexer->file!=(void *)lexer->logicalFile) {
            filter=Msg_SetMsgFilter(pp_msgcontext,0);if(lexer_setupref(record,line,256,raw?&raw->ref:0,0,0,1)) Msg_EmitRef(pp_msgcontext,0,record,line,0x28c3);Msg_SetMsgFilter(pp_msgcontext,filter);
        }
    }
    UnlockGList(&list);FreeGList(&list);
}
extern GList macro_temp;
extern char fn_0069990d[],fn_00699915[],fn_00699909[],fn_00699929[],fn_0069992d[],fn_00699931[],fn_00699935[],fn_00699939[],fn_0069993d[];
void dump_macro(Macro *macro)
{
    UInt8 *cursor=macro->text,flags;LexerToken raw;SInt16 kind;SInt32 i,savedSize;char *text,*saved;Macro *nested;
    macro_temp.size=0;AppendGListName(&macro_temp,"#define ");AppendGListName(&macro_temp,macro->name->text);
    if(macro->argCount) {
        AppendGListName(&macro_temp,fn_00699929);
        for(i=1;i<macro->argCount;i++) {
            text=((HashName **)((char *)macro+32))[i-1]->text;
            AppendGListName(&macro_temp,!strcmp(text,"__VA_ARGS__")?fn_00699939:text);
            if(i+1<macro->argCount) AppendGListName(&macro_temp,fn_0069993d);
        }
        AppendGListName(&macro_temp,fn_0069992d);
    }
    AppendGListName(&macro_temp,fn_00699931);
    while(cursor<(UInt8 *)macro->text+macro->textSize) {
        kind=decodemacrotoken(macro,&cursor,&raw,&flags);
        if(!kind) AppendGListName(&macro_temp,"/*eof*/");
        if(raw.space||raw.bol) AppendGListName(&macro_temp,fn_00699931);
        if(flags&8) AppendGListName(&macro_temp,fn_00699909);
        text=(flags&4)?((HashName **)((char *)macro+32))[kind-1]->text:preprocesstoken(raw.kind,raw.value,raw.value2,0);
        AppendGListName(&macro_temp,text);
        if(kind==-3) {
            nested=lexer_lookup_macro(GetHashNameNodeExport(raw.value));
            if(nested) {savedSize=macro_temp.size;saved=aalloc(savedSize);memcpy(saved,*(char **)macro_temp.data,savedSize);dump_macro(nested);macro_temp.size=0;AppendGListData(&macro_temp,saved,savedSize);}
        }
    }
    AppendGListName(&macro_temp,fn_00699935);AppendGListData(&lexer_dlist,*(char **)macro_temp.data,macro_temp.size);
}
void pragma_dump_macro(void)
{
    LexerToken raw;HashName *name;Macro *macro;SInt32 bucket,length;
    if(!lexer_plextokenorskip(&raw,'(',0x2782)||!lexer_readtokenorskip(&raw,-3,0x277b)) return;
    name=GetHashNameNodeExport(raw.value);if(!lexer_plextokenorskip(&raw,')',0x2783)||!lexer_record_tokens) return;
    if(InitGList(&macro_temp,500)) {lexer_error(0,0x28bb);return;}
    AppendGListName(&lexer_dlist,fn_0069990d);length=strlen(name->text);
    for(bucket=0;bucket<2048;bucket++) for(macro=pp_macrohashtable[bucket];macro;macro=macro->next) if(!strncmp(macro->name->text,name->text,length)) dump_macro(macro);
    AppendGListName(&lexer_dlist,fn_00699915);FreeGList(&macro_temp);
}

extern UInt8 lexer_skipping_if;
extern char fn_00699ab1[];
extern int snprintf(char *,UInt32,const char *,...);
static __inline UInt8 inactive_if(void)
{
    if(iflevel>0) switch(ifstack[iflevel-1].mode) {case 1:case 3:case 4:return 1;}
    return 0;
}
static __inline void begin_if(LexerToken *raw)
{
    ig_entry_had_token=1;
    if(!lexer->flag28&&(iflevel<=lexer->savedState||!ifstack[iflevel-1].seen)) ig_entry_had_token=0;
    ig_entry_iglist_size=lexer_iglist.size;if_tok=*raw;
}
static __inline void positive_if(void)
{
    if(iflevel<256) {
        ifstack[iflevel].mode=0;ifstack[iflevel].token=if_tok;
        ifstack[iflevel].savedSize=ig_entry_iglist_size;ifstack[iflevel].hadToken=ig_entry_had_token;
        ifstack[iflevel].valid=1;ifstack[iflevel].seen=0;iflevel++;
    } else {lexer_error(&if_tok,0x27e7);iflevel=0;if(lexer) while(lexer->stream) lexer_pop_mstream_impl();Msg_FatalJump(pp_msgcontext);}
}
static __inline void save_defined(LexerToken *raw,SInt8 marker)
{
    char length[16];
    if(!ig_entry_had_token) {
        snprintf(length,16,fn_00699ab1,strlen(raw->value));
        AppendGListByte(&lexer_iglist,'#');AppendGListByte(&lexer_iglist,marker);AppendGListName(&lexer_iglist,length);AppendGListName(&lexer_iglist,raw->value);
    }
}
void lexer_prepifdef(LexerToken *raw)
{
    LexerToken name;SInt16 kind;begin_if(raw);
    if(inactive_if()) {lexer_readtoken_impl(&name);save_defined(&name,'d');lexer_skipendofline();negativeif(0);return;}
    kind=lexer_readtoken_impl(&name);
    if(kind!=-3) {
        if(!ifstack[iflevel-1].hadToken) AppendGListByte(&lexer_iglist,'?');
        lexer_error(&name,kind==-7?0x2780:0x277b);negativeif(1);return;
    }
    save_defined(&name,'d');
    if(!lexer_lookup_macro(GetHashNameNodeExport(name.value))) {lexer_skipendofline();negativeif(1);}
    else {lexer_skipendofline();positive_if();}
}
void lexer_prepifndef(LexerToken *raw)
{
    LexerToken name;SInt16 kind;begin_if(raw);
    if(inactive_if()) {lexer_readtoken_impl(&name);save_defined(&name,'n');lexer_skipendofline();negativeif(0);return;}
    kind=lexer_readtoken_impl(&name);
    if(kind!=-3) {
        if(!ifstack[iflevel-1].hadToken) AppendGListByte(&lexer_iglist,'?');
        lexer_error(&name,kind==-7?0x2780:0x277b);negativeif(1);return;
    }
    save_defined(&name,'n');
    if(!lexer_lookup_macro(GetHashNameNodeExport(name.value))) {lexer_skipendofline();positive_if();}
    else {lexer_skipendofline();negativeif(1);}
}
static __inline PPValue evaluate_if(void)
{
    PPValue value;scanner_getsourceref(0,&igtest_start_ref);lexer_incondexpr=1;lexer_skipcond=0;value=parsecond();
    if(exprtk) lexer_error(&exprtok,0x28c8);
    lexer_incondexpr=0;scanner_getsourceref(0,&igtest_end_ref);return value;
}
void lexer_prepif(LexerToken *raw)
{
    UInt8 saved;PPValue value;begin_if(raw);
    if(inactive_if()) {saved=lexer->flag28;scanner_getsourceref(0,&igtest_start_ref);lexer_skipendofline();scanner_getsourceref(0,&igtest_end_ref);lexer->flag28=saved;ig_save_if('i');negativeif(0);return;}
    value=evaluate_if();ig_save_if('i');
    if(!value.value.high&&!value.value.low) negativeif(1);else positive_if();
}
void lexer_prepelif(LexerToken *raw)
{
    UInt8 saved;PPValue value;SInt16 mode;if_tok=*raw;
    if(iflevel>0&&ifstack[iflevel-1].mode!=2&&ifstack[iflevel-1].mode!=4) {
        mode=ifstack[iflevel-1].mode;
        switch(mode) {
        case 0:case 3:
            saved=lexer->flag28;scanner_getsourceref(0,&igtest_start_ref);lexer_skipendofline();scanner_getsourceref(0,&igtest_end_ref);lexer->flag28=saved;ig_save_if('l');lexer->flag28=ifstack[iflevel-1].hadToken;
            if(mode==0) {ifstack[iflevel-1].mode=3;prepifskip();}return;
        case 1:
            value=evaluate_if();if(value.value.high||value.value.low) ifstack[iflevel-1].mode=0;
            ig_save_if('l');lexer->flag28=ifstack[iflevel-1].hadToken;return;
        default:preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_prepelif",6752);return;
        }
    }
    if(!ifstack[iflevel-1].hadToken) AppendGListByte(&lexer_iglist,'?');
    lexer_error(raw,0x2786);lexer_skipendofline();
}
void prepifskip(void)
{
    UInt8 suppressed=scanner_suppress_messages(1),saved=lexer_skipping_if;LexerToken raw;SInt16 kind;
    lexer_skipping_if=1;
    while(iflevel>0&&inactive_if()) {
        while(lexer->stream) lexer_pop_mstream_impl();
        for(;;) {
            kind=lexer_readtoken_impl(&raw);
            if(kind==-7) {
                lexer->unread=1;
                if(!lexer->stream) {SInt32 delta=scanner.position.line-lexer->unknown18;if(delta>0) lexer_lines+=delta;lexer->unknown18=scanner.position.line;if(fn_00710694) fn_00710694();}
                continue;
            }
            if(!kind) {
                if(iflevel<1) lexer_error(0,0x2787);else {raw=ifstack[iflevel-1].token;lexer_error(&raw,0x2787);}
                if(!lexer_pop()) {iflevel=0;if(lexer) while(lexer->stream) lexer_pop_mstream_impl();Msg_FatalJump(pp_msgcontext);goto done;}
                continue;
            }
            if(kind=='#') {if(raw.bol) break;}
            else {ig_boundary_impl();lexer_skipendofline();}
        }
        lexer_directive(&raw,1);
    }
done:scanner_suppress_messages(suppressed);lexer_skipping_if=saved;
}
extern UInt8 scanner_set_charset(char *);
extern void scanner_set_default_global_encoding(char *,UInt8);
void pragma_text_encoding(UInt8 mode)
{
    LexerToken name,token;HashName *hash;SInt16 kind;UInt8 global=0;LexerState *state;
    if(!lexer_plextokenorskip(&name,'(',0x2782)) return;
    kind=lexer_plex(&name);hash=GetHashNameNodeExport(name.value);
    if(lexer_plex(&token)==','&&!mode) {
        if(lexer_plex(&token)==-3) {if(!strcmp(token.value,"global")) global=1;else lexer_warning(&token,0x27ca);}
        else lexer_warning(&token,0x277b);
        lexer_plex(&token);
    }
    if(token.kind!=')') {lexer_error(&token,0x2783);return;}
    lexer_plextokenorskip(&token,-7,0x2781);lexer->unread=1;
    if(!lexer->stream) {SInt32 delta=scanner.position.line-lexer->unknown18;if(delta>0) lexer_lines+=delta;lexer->unknown18=scanner.position.line;if(fn_00710694) fn_00710694();}
    if(!mode&&kind==-3&&!strcmp(hash->text,"reset")) {scanner_set_charset(0);if(global) scanner_set_default_global_encoding(0,0);return;}
    if(!mode&&kind==-3&&!strcmp(hash->text,"unknown")) {scanner_set_charset("unknown");if(global) scanner_set_default_global_encoding(0,0);return;}
    if(kind==-12) {
        if(!scanner_set_charset(hash->text)) lexer_warning(&name,0x28be,hash->text,0);
        else if(global) {
            scanner_set_default_global_encoding(hash->text,1);*lexer->scannerSave=scanner;
            for(state=lexer->parent;state;state=state->parent) {scanner=*state->scannerSave;scanner_resync();if(scanner.position.current==scanner.base) {scanner_set_charset(hash->text);*state->scannerSave=scanner;}}
            scanner=*lexer->scannerSave;scanner_resync();
        }
    } else {lexer_error(&name,0x28c2);lexer_skipendofline();}
}

#pragma pack(push,2)
typedef struct MacroArgument { MacroNode *head,*tail; } MacroArgument;
#pragma pack(pop)
static __inline void add_node(MacroArgument *list,MacroNode *node)
{
    if(!list->tail) list->head=list->tail=node;else {list->tail->next=node;list->tail=node;}
}
static __inline void clone_node(MacroArgument *list,MacroNode *node)
{
    MacroNode *copy=aalloc(12);*copy=*node;copy->next=0;add_node(list,copy);
}
void lexer_expand_argument(MacroArgument *input,MacroArgument *output,SourceRef *ref)
{
    MacroStream *stop,*stream;MacroNode *node,*next,*identifier;MacroList saved;Macro *macro;
    lexer_push_mstream(0,(MacroList *)input,0,ref);stop=lexer->stream;output->head=output->tail=0;
    for(;;) {
        node=0;
        while((stream=lexer->stream)!=0) {
            node=stream->tokens.current;
            if(!node) {if(stream==stop) break;lexer_pop_mstream_impl();}
            else {stream->tokens.previous=node;stream->tokens.current=node->next;if(node->kind!=-7) break;}
        }
        if(!node) {if(lexer->stream==stop) {lexer_pop_mstream_impl();return;}if(!lexer->stream) return;lexer_pop_mstream_impl();continue;}
        if(node->kind==-3) {
            if(lexer_incondexpr&&!strcmp(node->text,"defined")) {
                stream=lexer->stream;saved=stream->tokens;next=stream->tokens.current;
                if(next&&next->kind==-3) {clone_node(output,node);clone_node(output,next);continue;}
                if(next&&next->kind=='(') {
                    stream->tokens.previous=next;stream->tokens.current=next->next;identifier=stream->tokens.current;
                    if(identifier&&identifier->kind==-3) {
                        stream->tokens.previous=identifier;stream->tokens.current=identifier->next;next=stream->tokens.current;
                        if(next&&next->kind==')') {
                            stream->tokens.previous=next;stream->tokens.current=next->next;
                            clone_node(output,node);clone_node(output,node->next);clone_node(output,node->next->next);clone_node(output,node->next->next->next);continue;
                        }
                    }
                }
                lexer->stream->tokens=saved;
            }
            if(!(node->flags&0x40)) {
                macro=lexer_lookup_macro(GetHashNameNodeExport(node->text));
                if(macro) {
                    if(!(macro->flags&4)) {
                        if(!macro->argCount||peekargparen()) {MacroList *list=aalloc(8);lexer_expand_macro(macro,node->flags,&lexer->stream->ref,list);continue;}
                    } else node->flags|=0x40;
                }
            }
        }
        clone_node(output,node);
    }
}
UInt8 expand_mstream(Macro *macro,UInt8 *cursor,MacroArgument *arguments,MacroArgument *expanded,SourceRef *ref,MacroArgument *output)
{
    MacroNode *node,*previous=0,*source,*first;SInt16 index;UInt8 special=0;
    output->head=output->tail=0;
    while(expandmacrotoken(macro,&cursor,&node)) {
        if(!(node->flags&4)) {
            if((UInt16)(node->kind+20)<3) special=1;
            add_node(output,node);
        } else {
            index=node->kind-1;
            if(previous&&previous->kind==-18&&index+1==macro->argCount-1&&(macro->flags&2)) previous->flags|=0x80;
            if(node->flags&8) {stringizemlist((SourceRef *)macro,(MacroList *)&arguments[index],node);add_node(output,node);}
            else {
                if(node->flags&0x10) source=arguments[index].head;
                else {if(!expanded[index].head&&arguments[index].head) lexer_expand_argument(&arguments[index],&expanded[index],ref);source=expanded[index].head;}
                first=0;
                for(;source;source=source->next) {clone_node(output,source);if(!first) first=output->tail;}
                if(first) first->flags|=node->flags&1;
            }
        }
        previous=node;
    }
    return special;
}
extern void *fn_007106f0;
extern char *(*fn_007106ac)(Macro *);
extern UInt8 fn_0070f07b;
extern char fn_006999a1[],fn_006999a5[],fn_006999a9[],fn_006999ad[],fn_006999b5[],fn_006999b9[],fn_006999c1[];
extern int CWGetTargetName(void *,char *,SInt32),sprintf(char *,const char *,...);
extern void *localtime(SInt32 *);
extern UInt32 strftime(char *,UInt32,const char *,void *);
extern char *COS_GetEnv(char *);
extern void CError_Warning(SInt16,...);
char *lexer_expand_special_macro(Macro *macro,SInt32 *size)
{
    LexerToken raw;UInt8 match=0;char buffer[256],day[32],target[256],*text;void *tm;char *encoded;
    if(macro==&trgtM) {
        if(lexer_plextokenorfail(&raw,'(',0x2782)&&lexer_plextokenorfail(&raw,-12,0x28c2)) {
            match=!CWGetTargetName(fn_007106f0,target,256)&&!strcmp(target,raw.value);
            if(!lexer_plextokenorfail(&raw,')',0x2783)) match=0;
        }
        return lexer_macro_encode_number(match?fn_006999a1:fn_006999a5,size);
    }
    if(macro==&lineM) {sprintf(buffer,fn_006999a9,lexer_get_current_line());return lexer_macro_encode_number(buffer,size);}
    if(macro==&fileM) {text=lexer_get_current_filename()->text;if(!fn_0070f07b) text=COS_PathGetFileName(text);return lexer_macro_encode_string(text,size);}
    if(macro==&dateM) {
        tm=localtime(&now_time);strftime(buffer,64,fn_006999ad,tm);strftime(day,32,fn_006999b5,tm);if(day[0]=='0') day[0]=' ';strcat(buffer,day);strftime(day,32,fn_006999b9,tm);strcat(buffer,day);return lexer_macro_encode_escaped_string(buffer,size);
    }
    if(macro==&timeM) {tm=localtime(&now_time);strftime(buffer,64,fn_006999c1,tm);return lexer_macro_encode_escaped_string(buffer,size);}
    if(macro==&envrM) {
        if(!lexer_plextokenorfail(&raw,'(',0x2782)||!lexer_plextokenorfail(&raw,-3,0x277b)) return 0;
        text=COS_GetEnv(raw.value);if(!text) {text="";CError_Warning(0x2938,raw.value);}
        if(!lexer_plextokenorfail(&raw,')',0x2783)) return 0;return lexer_macro_encode_string(text,size);
    }
    if(!fn_007106ac) {preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_expand_special_macro",4149);return lexer_macro_encode_number(fn_006999a5,size);}
    if(!macro->text) {
        text=fn_007106ac(macro);
        if(!text) {lexer_mlist.size=0;*size=0;appendmacrotoken(&lexer_mlist,0,0);encoded=aalloc(lexer_mlist.size);memcpy(encoded,*(char **)lexer_mlist.data,lexer_mlist.size);return encoded;}
        return lexer_macro_encode_text(text,2,size);
    }
    *size=macro->textSize;return macro->text;
}

extern void scanner_term(void),preprocessor_unload_file(LexerFile *);
extern char fn_00699979[],fn_006999f9[],fn_00699a11[],fn_00699a19[];
UInt8 lexer_pop(void)
{
    LexerState *state=lexer;LexerFile *file;UInt8 silent;SInt32 level,start;char *guard;
    if(!state) return 0;
    if(fn_0071068c) fn_0071068c(state->file,state->depth,state->silent,0);
    level=state->savedState;
    if(level!=iflevel) {if(iflevel>0) level=iflevel-1;lexer_error(&ifstack[level].token,0x2787);iflevel=lexer->savedState;}
    state=lexer;silent=state->silent;lexer_in_directive=0;file=state->file;
    if(!file->kind&&!*(void **)((char *)file->diskInfo+8)&&*(SInt16 *)((char *)file+28)!=2) {
        if(state->flag28) ig_boundary_impl();
        start=state->savedIgSize;
        if(lexer_iglist.size==start) guard="";
        else if((*(char **)lexer_iglist.data)[start]=='$'||(*(char **)lexer_iglist.data)[lexer_iglist.size-1]=='$') guard=fn_00699979;
        else {AppendGListWord(&lexer_iglist,0);guard=galloc(lexer_iglist.size-start);strcpy(guard,*(char **)lexer_iglist.data+start);}
        *(char **)((char *)lexer->file->diskInfo+8)=guard;
    }
    lexer_iglist.size=lexer->savedIgSize;
    if(!lexer->flag26) {
        scanner_term();file=lexer->file;
        if(file&&!file->kind) {UInt16 *count=(UInt16 *)((char *)file->diskInfo+12);if(!--*count) preprocessor_unload_file(file);}
        if(lexer->logicalFile) preprocessor_unload_file((LexerFile *)lexer->logicalFile);
    }
    lexer=lexer->parent;
    if(!lexer||!lexer->scannerSave) return 0;
    scanner=*lexer->scannerSave;scanner_resync();lexer->macroLocks=0;file=lexer->file;
    if(file&&(file->kind||*(SInt16 *)((char *)file+28)!=2)) preprocessor_load_file(file);
    if(lexer->forceLogical) preprocessor_load_file(*(LexerFile **)((char *)lexer->logicalFile+22));
    if(fn_00710690&&lexer->file) fn_00710690(lexer_get_current_file(),lexer_get_current_filename(),lexer_get_current_line(),lexer->depth,silent,1);
    return 1;
}
extern UInt8 fn_0070f08b,fn_0070f089,fn_0070f076,fn_0070f079,fn_0070f07a,fn_0070f077;
static __inline LexerFile *resolve_disk(LexerFile *file)
{
    while(file) {switch(file->kind) {case 0:return file;case 1:case 2:case 3:file=file->backing;break;default:return 0;}}
    return 0;
}
char *lexer_get_file_stack_string(UInt8 force,UInt8 macros)
{
    LexerState *state;LexerFile *file;MacroStream *stream;char buffer[264],*name,*result;
    if(!lexer||(!force&&lexer->depth<3)) return 0;
    lexer_inclfromlist.size=0;
    if(macros) for(stream=lexer->stream;stream;stream=stream->next) if(stream->macro) {snprintf(buffer,264,fn_006999f9,stream->macro->name->text);AppendGListName(&lexer_inclfromlist,buffer);}
    *lexer->scannerSave=scanner;
    for(state=lexer->parent;state;state=state->parent) {
        file=resolve_disk(state->file);if(!file) file=state->file;
        if(!state->scannerSave) continue;
        scanner=*state->scannerSave;scanner_resync();
        if(!fn_0070f08b&&!file->kind) {
            HashName *display=file->diskInfo?*(HashName **)((char *)file->diskInfo+4):0;
            name=display?display->text:COS_PathGetFileName(file->name->text);
        } else name=file->name->text;
        snprintf(buffer,264,fn_00699a11,name,scanner.position.line);AppendGListName(&lexer_inclfromlist,buffer);
    }
    scanner=*lexer->scannerSave;scanner_resync();
    if(!lexer_inclfromlist.size) return 0;
    lexer_inclfromlist.size--;AppendGListByte(&lexer_inclfromlist,0);result=galloc(lexer_inclfromlist.size);memcpy(result,*(char **)lexer_inclfromlist.data,lexer_inclfromlist.size);return result;
}
extern void scanner_parse_include(UInt8);
char *parse_include_name(LexerToken *raw,UInt8 *system,UInt8 direct)
{
    UInt8 suppression,saved;char *name,*text,*copy;SInt32 size=0,capacity=0,length;
    *system=0;suppression=scanner_suppress_messages(1);scanner_peektoken(raw);scanner_suppress_messages(suppression);saved=fn_0070f089;
    if(raw->kind=='<'||raw->kind==-12) {*system=raw->kind=='<';scanner_parse_include(1);scanner_readtoken(raw);scanner_parse_include(0);name=raw->value;}
    else {
        if(direct) return 0;
        if(fn_0070f089) {fn_0070f089=0;preprocessor_reconfig(&fn_0070f089);}
        lexer_plex(raw);name=0;
        for(;;) {
            text=preprocesstoken(raw->kind,raw->value,raw->value2,0);length=strlen(text);
            if(capacity<=length+size) {capacity=(capacity+length+size)*2;copy=aalloc(capacity);if(!name) *copy=0;else strcpy(copy,name);name=copy;}
            strcpy(name+size,text);size+=length;if(peekeol()) break;lexer_plex(raw);
        }
        if(name[0]=='<'&&name[size-1]=='>') {name[size-1]=0;name++;*system=1;}
        else if(name[0]=='"'&&name[size-1]=='"') {name[size-1]=0;name++;*system=0;}
        else lexer_error(raw,0x2785);
        if(fn_0070f089!=saved) {fn_0070f089=saved;preprocessor_reconfig(&fn_0070f089);}
    }
    name=GetHashNameNodeExport(name)->text;
    if(!direct&&lexer->stream) {if(!peekeol()) lexer_error(raw,0x2785);do {lexer_pop_mstream_impl();}while(lexer->stream);}
    raw->value=name;if(fn_0070f076) name=COS_PathGetFileName(name);return name;
}
extern LexerFile *preprocessor_lookup_file(HashName *,UInt8,LexerFile *,UInt8,UInt8);
extern char *COS_PathGetExtension(char *),*COS_FileGetFileName(void *);
extern void COS_FileFixFileSpec(void *);
extern void (*fn_00710688)(LexerToken *,LexerFile *,UInt8);
UInt8 lexer_push_include_file(char *name,UInt8 system,UInt8 silent,UInt8 flag,LexerFile **out)
{
    LexerFile *parent=0,*file;LexerState *state;HashName *hash;char *extension,*actual,*requested;UInt8 plain;UInt16 *count;UInt8 *once;
    if(!name) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_push_include_file",1444);
    extension=COS_PathGetExtension(name);plain=!*extension||!CTool_strcasecmp(extension,fn_00699a19);
    hash=GetHashNameNodeExport(name);
    for(state=lexer;state;state=state->parent) if(state->file) {
        parent=resolve_disk(state->file);
        if(parent&&!parent->kind&&(parent->name->text[0]!='('||!COS_FileExists(parent->backing))) break;
        parent=0;
    }
    file=preprocessor_lookup_file(hash,system,parent,1,!plain);
    if(!file) {if(out) *out=0;return 0;}
    if(!file->kind&&fn_0070f079&&(fn_0070f07a||!system)) {
        COS_FileFixFileSpec(file->backing);requested=COS_PathGetFileName(name);actual=COS_FileGetFileName(file->backing);
        if(strcmp(actual,requested)) lexer_warning(lexer_incltoken,0x28ab,name,COS_FileGetFileName(file->backing));
    }
    if(!file->kind&&(*(UInt8 *)((char *)file->diskInfo+14)||ig_test(file))) {if(out) *out=0;return 1;}
    if(!preprocessor_load_file(file)) {if(out) *out=0;return 0;}
    lexer_push(0,silent,flag);lexer->file=file;once=(UInt8 *)file->diskInfo+14;*once|=lexer_pragmaonce;
    if(*once&&!fn_0070f077) *((UInt8 *)file->diskInfo+15)=0;
    count=(UInt16 *)((char *)file->diskInfo+12);if(!++*count) --*count;
    if(fn_00710688) fn_00710688(lexer_incltoken,file,system);
    if(fn_0071068c) fn_0071068c(file,lexer->depth,silent,1);
    if(fn_00710690) fn_00710690(file,file->name,1,lexer->depth,silent,0);
    scanner_init(file);lexer->unread=1;if(out) *out=file;return 1;
}


void setup_line_file(HashName *name,SInt32 line,LexerFile *file)
{
    LogicalLineFile *logical;SourceRef ref;LexerFile *original=scanner.file;SInt32 offset=scanner.position.current-scanner.base,originalLine=scanner.position.line;
    if(file==scanner.file&&line==scanner.position.line) {lexer->logicalFile=0;lexer->forceLogical=0;if(fn_00710690) fn_00710690(file,name,line,lexer->depth,0,2);return;}
    if(lexer->logicalFile&&file==lexer->logicalFile->file) {lexer_getsourceref(&ref);lexer_flattensourceref(&ref,1);if(line==ref.line) return;}
    logical=galloc(52);memclrw(logical,52);logical->name=name;*((UInt8 *)logical+9)=file?file->unknown09:0;*((UInt8 *)logical+8)=1;
    *(LexerFile **)((char *)logical+22)=original;*(SInt32 *)((char *)logical+26)=offset;logical->sourceLine=originalLine;logical->file=file;logical->logicalLine=line;
    lexer->logicalFile=logical;if(!lexer_first_line_file) lexer_first_line_file=(LexerFile *)logical;
    if(!cparamblkptr->logicalNames&&file&&(file->kind||!(*((UInt8 *)file+50)&8))) {
        lexer->forceLogical=galloc(80);preprocessor_load_file(file);*lexer->scannerSave=scanner;scanner_init(file);scanner_goto_line(line);
        *(SInt32 *)((char *)logical+42)=scanner.position.current-scanner.base;logical->logicalLine=scanner.position.line;*lexer->forceLogical=scanner;
        scanner=*lexer->scannerSave;scanner_resync();
    } else {lexer->forceLogical=0;*(SInt32 *)((char *)logical+42)=0;logical->logicalLine=line;}
    if(fn_00710690) fn_00710690(lexer_get_current_file(),lexer_get_current_filename(),lexer_get_current_line(),lexer->depth,0,2);
}
extern LexerFile *preprocessor_lookup_line_file(HashName *,UInt8,UInt8);
void lexer_prepline(LexerToken *raw)
{
    LexerToken token;CompilerToken converted;SInt32 line;HashName *name;LexerFile *file;
    if(!raw) {if(!lexer_plextokenorskip(&token,-8,0x28c1)) return;raw=&token;}
    if(lexer_convert_to_token(raw,&converted,0,1)==-1&&(line=(SInt32)((Number64 *)converted.payload)->low)>0) {
        scanner_parse_include(1);lexer_plex(&token);scanner_parse_include(0);
        if(token.kind==-7) {
            if(!lexer->logicalFile) setup_line_file(lexer->file->name,line,lexer->file);
            else setup_line_file(lexer->logicalFile->name,line,lexer->logicalFile->file);
        } else {
            if(token.kind!=-12&&token.kind!=-15) {lexer_error(&token,0x28c2);lexer_skipendofline();return;}
            name=GetHashNameNodeExport(parsefilename(token.value));if(raw!=&token) lexer_skipendofline();
            if(lexer_readtoken_impl(&token)!=-7) lexer_error(&token,0x2781);
            file=preprocessor_lookup_line_file(name,0,0);setup_line_file(*(HashName **)((char *)file->diskInfo+4),line,file);
        }
        lexer->unread=1;
        if(!lexer->stream) {SInt32 delta=scanner.position.line-lexer->unknown18;if(delta>0) lexer_lines+=delta;lexer->unknown18=scanner.position.line;if(fn_00710694) fn_00710694();}
    } else {lexer_error(raw,0x28c1);lexer_skipendofline();}
}
extern UInt8 fn_0070f1fb,fn_0070f08e;
extern UInt8 (*fn_007106b8)(LexerToken *),(*fn_007106bc)(LexerToken *),(*fn_007106c4)(char *);
extern void (*fn_007106c0)(GList *);
extern char *fn_006997c8;
extern void AppendGListNoData(GList *,SInt32);
void lexer_preppragma(LexerToken *raw,UInt8 *consume)
{
    LexerToken token;UInt8 savedOption=fn_0070f071,savedFlag;SInt32 position,length;char *name;
    if(fn_0070f071) {fn_0070f071=0;preprocessor_reconfig(&fn_0070f071);}
    savedFlag=lexer->flag25;lexer->flag25=1;
    if(lexer_plex(&token)!=-3) {
        if(token.kind==-7) lexer_unreadtoken(&token);
        else {if(fn_0070f1fb) lexer_warning(&token,0x27ca);lexer_skipendofline();}
        goto done;
    }
    name=token.value;
    if(!strcmp(name,"once")) pragma_once(1);
    else if(!strcmp(name,"notonce")) pragma_once(0);
    else if(!strcmp(name,"message")) pragma_message(raw);
    else if(!strcmp(name,"mark")) {ig_skipline(0);goto done;}
    else if(!strcmp(name,"text_encoding")||!strcmp(name,"setlocale")) {
        position=lexer_dlist.size;pragma_text_encoding(!strcmp(name,"setlocale"));*consume=0;
        if(lexer_record_tokens&&*((UInt8 *)&scanner+13)!=1) {
            length=strlen(fn_006997c8);AppendGListNoData(&lexer_dlist,length);
            memmove(*(char **)lexer_dlist.data+position+length,*(char **)lexer_dlist.data+position,lexer_dlist.size-position-length);
            memcpy(*(char **)lexer_dlist.data+position,fn_006997c8,length);
        }
        goto done;
    } else if(!strcmp(name,"dump_macro")) pragma_dump_macro();
    else {
        if(!fn_007106b8||!fn_007106b8(&token)) {if(fn_0070f1fb) lexer_warning(raw,0x27ca);lexer_skipendofline();goto done;}
        lexer->flag28=1;
    }
    lexer_matchendofline();
done:lexer->unread=1;lexer->flag25=savedFlag;
    while(lexer->stream) lexer_pop_mstream_impl();preprocessor_reconfig(0);
    if(!fn_0070f071&&savedOption) {fn_0070f071=savedOption;preprocessor_reconfig(&fn_0070f071);}
}
extern void lexer_prepdefine(void);
void lexer_directive(LexerToken *raw,UInt8 skipping)
{
    LexerToken token;UInt8 recording=lexer_record_tokens,savedOption=fn_0070f071,consume=!skipping,savedWarning;SInt32 position;SInt16 kind;char *name;
    if(fn_0070f071) {fn_0070f071=0;preprocessor_reconfig(&fn_0070f071);}
    position=lexer_dlist.size;lexer_in_directive=1;
    if(!skipping&&fn_007106c0&&fn_007106c4) {
        lexer_record_tokens=1;if(!recording) lexer_dlist.size=0;
        if(raw->space&&!raw->bol) AppendGListByte(&lexer_dlist,' ');
        AppendGListName(&lexer_dlist,preprocesstoken(raw->kind,raw->value,raw->value2,0));
    }
    kind=lexer_readtoken_impl(&token);
    if(kind==-8) {
        if(!skipping) {
            if(!fn_0070f1af) {if(lexer_record_tokens&&!fn_007106c4("line")) {lexer_record_tokens=0;lexer_dlist.size=position;}lexer_prepline(&token);consume=0;}
            else lexer_error(&token,0x2778,token.value);
        } else {lexer->flag28=1;lexer_skipendofline();}
    } else if(kind==-7) {
        if(lexer_record_tokens&&!fn_007106c4("")) {lexer_record_tokens=0;lexer_dlist.size=position;}
        lexer_unreadtoken(&token);
    } else if(kind==-3) {
        name=token.value;if(lexer_record_tokens&&!fn_007106c4(name)) {lexer_record_tokens=0;lexer_dlist.size=position;}
        if(!strcmp(name,"if")) lexer_prepif(raw);
        else if(!strcmp(name,"ifdef")) lexer_prepifdef(raw);
        else if(!strcmp(name,"ifndef")) lexer_prepifndef(raw);
        else if(!strcmp(name,"elif")) lexer_prepelif(raw);
        else if(!strcmp(name,"else")) lexer_prepelse(raw);
        else if(!strcmp(name,"endif")) lexer_prependif(raw);
        else if(skipping) {lexer->flag28=1;lexer_skipendofline();}
        else if(!strcmp(name,"define")) lexer_prepdefine();
        else if(!strcmp(name,"undef")) lexer_prepundef();
        else if(!strcmp(name,"pragma")) lexer_preppragma(raw,&consume);
        else if(!strcmp(name,"line")) {lexer_prepline(0);consume=0;}
        else if(!strcmp(name,"include")) {lexer_prepinclude(0);consume=0;}
        else if(!strcmp(name,"error")) {lexer_prepmessage(raw,2,0x284e);lexer->flag28=1;}
        else if(!strcmp(name,"warning")&&!fn_0070f1af) {lexer->flag28=1;savedWarning=fn_0070f08e;fn_0070f08e=0;lexer_prepmessage(raw,1,0x2861);fn_0070f08e=savedWarning;lexer->flag28=1;}
        else if(!fn_007106bc||!fn_007106bc(&token)) {
            if(!strcmp(name,"import")&&!fn_0070f1af) {lexer->flag28=1;lexer_prepinclude(1);consume=0;}
            else if(!strcmp(name,"ident")) lexer_skipendofline();
            else {lexer_error(&token,0x2778,token.value);lexer_skipendofline();}
        }
    } else if(!skipping) {lexer_error(&token,0x2778,token.value);lexer_skipendofline();}
    else {lexer->flag28=1;lexer_skipendofline();}
    if(consume) {
        kind=lexer_readtoken_impl(&token);
        if(kind==-7||!token.kind) {
            lexer->unread=1;
            if(!lexer->stream) {SInt32 delta=scanner.position.line-lexer->unknown18;if(delta>0) lexer_lines+=delta;lexer->unknown18=scanner.position.line;if(fn_00710694) fn_00710694();}
        } else lexer_error(&token,0x2781);
    }
    if(lexer_record_tokens&&!recording) fn_007106c0(&lexer_dlist);
    if(!fn_0070f071&&savedOption) {fn_0070f071=savedOption;preprocessor_reconfig(&fn_0070f071);}
    lexer_record_tokens=recording;lexer_in_directive=0;
}


#pragma pack(push,2)
typedef struct ScannerIterator { UInt8 unknown00[82];char *current,*end,*next; } ScannerIterator;
#pragma pack(pop)
extern void scanner_iterator_create_from_pptoken(ScannerIterator *,LexerToken *),scanner_iterator_destroy(ScannerIterator *);
extern SInt32 scanner_iterator_decode_character(ScannerIterator *);
extern UInt8 fn_0070498c;
extern void (*fn_007106c8)(SInt32,UInt8,UInt8,UInt8,SInt16 *,void **,UInt8 *);
extern Number64 CInt64_Shl(Number64,Number64),CInt64_Or(Number64,Number64);
extern void CInt64_ConvertInt8(Number64 *),CInt64_ConvertInt16(Number64 *),CInt64_ConvertInt32(Number64 *);
static __inline Number64 literal_append(Number64 value,UInt32 character,SInt32 bits)
{
    Number64 shift,unit;shift.high=bits<0?0xffffffff:0;shift.low=bits;unit.high=0;unit.low=character;
    return CInt64_Or(unit,CInt64_Shl(value,shift));
}
static __inline void literal_store(char *dest,SInt32 width,UInt32 value)
{
    if(width==1) *dest=(UInt8)value;else if(width==2) *(UInt16 *)dest=(UInt16)value;else *(UInt32 *)dest=value;
}
void parselit(LexerToken *raw,CompilerToken *result)
{
    Number64 value=cint64_zero;ScannerIterator iterator;SInt32 width,capacity,size=0,bits,decoded;UInt32 mask,character,extra;UInt8 wide,string,pascalStyle=0,unicode,sign;char *buffer,*cursor,*end;void *type;
    string=raw->kind<=-12&&raw->kind>=-14;
    switch(raw->kind) {
    case -14:case -11:width=4;mask=0xffffffff;wide=1;break;
    case -13:case -10:width=2;mask=0xffff;wide=1;break;
    case -12:case -9:width=1;mask=0xff;wide=0;break;
    default:preprocessor_internal_msg(1,0,"CPrepLexer.c","parselit",8719);
    }
    if(!string&&!raw->value2) lexer_error(raw,0x2774);
    scanner_iterator_create_from_pptoken(&iterator,raw);capacity=(iterator.end-iterator.current+1)*width;buffer=galloc(capacity);bits=width*8;
    if(string&&iterator.current[0]=='\\'&&iterator.current[1]=='p') {size+=width;pascalStyle=1;iterator.current+=2;}
    while(iterator.current<iterator.end) {
        if(capacity<=size) preprocessor_internal_msg(1,0,"CPrepLexer.c","parselit",8745);
        decoded=scanner_iterator_decode_character(&iterator);
        if(decoded=='\\') {
            if(fn_0070498c&&iterator.next-iterator.current>1) {
                end=iterator.next-1;
                if(!string) {for(cursor=iterator.current;cursor<end;cursor++) value=literal_append(value,(UInt8)*cursor,bits);}
                else {for(cursor=iterator.current;cursor<end;cursor++) {literal_store(buffer+size,width,(UInt8)*cursor);size+=width;}}
            }
            iterator.current=iterator.next;
            if(*iterator.current==1) iterator.current++;
            else {
                character=parseescape(raw,&iterator.current,&unicode);
                if((~mask&character)&&(!unicode||fn_0070f1f9)) {if(!fn_0070f1af) lexer_warning(raw,0x28cc);else lexer_error(raw,0x28cc);}
                if(!string) {value=literal_append(value,character,bits);size++;}
                else {literal_store(buffer+size,width,character);size+=width;}
            }
        } else {
            if(!string) {for(cursor=iterator.current;cursor<iterator.next;cursor++) value=literal_append(value,(UInt8)*cursor,bits);size+=iterator.next-iterator.current;}
            else {for(cursor=iterator.current;cursor<iterator.next;cursor++) {literal_store(buffer+size,width,(UInt8)*cursor);size+=width;}}
            iterator.current=iterator.next;
        }
    }
    scanner_iterator_destroy(&iterator);
    if(!string) {
        if(size>1) {
            extra=(size-1)&size;if(extra) {lexer_error(raw,0x2774);size-=extra;}width*=size;
            if(width!=(SInt16)stsignedlonglong.size&&(SInt16)stsignedlonglong.size<=width) {lexer_error(raw,0x28cd);width=8;}
        }
        result->kind=-1;
        if(!fn_007106c8) {result->flags=2;sign=1;}else fn_007106c8(width,0,pascalStyle,wide,&result->flags,&type,&sign);
        if(sign) switch(width) {
        case 1:CInt64_ConvertInt8(&value);break;
        case 2:CInt64_ConvertInt16(&value);break;
        case 4:CInt64_ConvertInt32(&value);break;
        case 8:break;
        default:preprocessor_internal_msg(1,0,"CPrepLexer.c","parselit",8866);break;
        }
        *(Number64 *)result->payload=value;
    } else {
        if(!pascalStyle) {literal_store(buffer+size,width,0);size+=width;}
        else {size-=width;character=size/width;if(~mask&character) {lexer_error(raw,0x277a);character=mask;}literal_store(buffer,width,character);size+=width;}
        result->kind=raw->kind==-12?-4:-5;
        if(!fn_007106c8) result->flags=2;else fn_007106c8(width,1,pascalStyle,wide,&result->flags,&type,&sign);
        *(char **)result->payload=buffer;
        *(UInt32 *)(result->payload+4)=(*(UInt32 *)(result->payload+4)&0x80000000)|((UInt32)size&0x7fffffff);
        result->payload[8]=(result->payload[8]&0xfe)|(pascalStyle&1);
    }
}
extern SInt16 fn_006dd056[256];
extern LexerFile *lexer_igtext;
extern SInt32 fn_0042d890(char *,char **,SInt32);
static __inline void igt_skip(void)
{
    while(igtlevel>0) {
        switch(fn_006dd056[igtlevel-1]) {case 1:case 3:case 4:while(*igtip++!='#') {}igtdirective();break;default:return;}
    }
}
static __inline PPValue igt_eval(void)
{
    LexerState state;PPValue value;
    lexer_igtext->contents=igtip;lexer_igtext->contentsSize=strlen(igtip)+2;
    lexer_push(&state,1,1);state.file=lexer_igtext;scanner_init(lexer_igtext);value=evaluate_if();igtip+=igtest_end_ref.offset-igtest_start_ref.offset;
    if(*igtip!='\n') preprocessor_internal_msg(1,0,"CPrepLexer.c","igtevalconstexpr",5188);
    igtip++;lexer_pop();return value;
}
void igtdirective(void)
{
    char *start=igtip++,directive=*start,*name;UInt8 expected=1;SInt32 length;Macro *macro;PPValue value;
    switch(directive) {
    case 'e':
        switch(fn_006dd056[igtlevel-1]) {case 0:fn_006dd056[igtlevel-1]=4;igt_skip();return;case 1:fn_006dd056[igtlevel-1]=2;return;case 3:fn_006dd056[igtlevel-1]=4;return;default:preprocessor_internal_msg(1,0,"CPrepLexer.c","igtdirective",5274);return;}
    case 'f':
        switch(fn_006dd056[igtlevel-1]) {case 1:case 3:case 4:igtlevel--;return;default:igtlevel--;if(igtlevel>0) switch(ifstack[iflevel-1].mode) {case 1:case 3:case 4:igt_skip();}return;}
    case 'l':
        switch(fn_006dd056[igtlevel-1]) {
        case 0:while(*igtip&&*igtip!='\n') igtip++;if(*igtip=='\n') igtip++;igt_skip();return;
        case 1:value=igt_eval();if(value.value.high||value.value.low) fn_006dd056[igtlevel-1]=0;return;
        case 3:while(*igtip&&*igtip!='\n') igtip++;if(*igtip=='\n') igtip++;return;
        default:preprocessor_internal_msg(1,0,"CPrepLexer.c","igtdirective",5293);return;
        }
    case 'i':value=igt_eval();break;
    case 'n':expected=0;
    case 'd':
        start=igtip;length=fn_0042d890(igtip,&igtip,10);
        if(start==igtip||length<0) preprocessor_internal_msg(1,0,"CPrepLexer.c","igtevaldefinedmacro",5210);
        name=aalloc(length+1);memcpy(name,igtip,length);name[length]=0;igtip+=length;macro=lexer_lookup_macro(GetHashNameNodeExport(name));value.value.high=0;value.value.low=(macro!=0)==expected;break;
    default:preprocessor_internal_msg(1,0,"CPrepLexer.c","igtdirective",5304);return;
    }
    if(igtlevel>0) switch(fn_006dd056[igtlevel-1]) {case 1:case 3:case 4:fn_006dd056[igtlevel++]=3;return;}
    if(!value.value.high&&!value.value.low) {fn_006dd056[igtlevel++]=1;igt_skip();}
    else fn_006dd056[igtlevel++]=0;
}


extern void *localeconv(void),*_GetThreadLocalData(SInt32);
extern Number64 CMach_CalcFloatConvertFromInt(NumericType *,Number64);
static __inline SInt32 hexfloat_take(char **cursor)
{
    SInt32 ch=**cursor;if(ch) (*cursor)++;return ch;
}
static __inline UInt16 hexfloat_class(SInt32 ch,UInt16 mask)
{
    if((UInt32)ch>255) return 0;
    return (*(UInt16 **)((char *)*(void **)((char *)_GetThreadLocalData(1)+444)+8))[ch]&mask;
}
static __inline SInt32 hexfloat_upper(SInt32 ch)
{
    if((UInt32)ch<=255) return (*(UInt8 **)((char *)*(void **)((char *)_GetThreadLocalData(1)+444)+12))[ch];return ch;
}
char *lexer_scan_hexfloat(char *text,Number64 *result,UInt8 *range,UInt8 *inexact)
{
    UInt8 digits[8],packed[9],byte,original,carry,temp;UInt32 state=1,status=0x8000,integerDigits=0,used=0;SInt32 exponent=0,negative=0,ch,count=0,i,shift,decimal=**(UInt8 **)localeconv();
    *range=*inexact=0;*result=CMach_CalcFloatConvertFromInt(&stsignedint,cint64_zero);
    ch=hexfloat_take(&text);if(ch!='0') return text;
    count=2;ch=hexfloat_take(&text);if(ch!='x'&&ch!='X') return text;
    while(ch&&!(status&0x1800)) {
        switch(state) {
        case 1:*(UInt32 *)digits=0;*(UInt32 *)(digits+4)=0;used=integerDigits=0;state=2;ch=hexfloat_take(&text);count++;break;
        case 2:if(ch=='0') {ch=hexfloat_take(&text);count++;}else state=4;break;
        case 4:
            if(!hexfloat_class(ch,0x400)) {if(ch==decimal) {state=8;ch=hexfloat_take(&text);count++;}else state=16;break;}
            if(integerDigits<14) {
                integerDigits++;ch=hexfloat_upper(ch);byte=(UInt8)(ch<65?ch-48:ch-55);
                if(!(used&1)) byte<<=4;digits[used/2]|=byte;used++;
            } else *inexact|=ch!='0';
            ch=hexfloat_take(&text);count++;break;
        case 8:
            if(!hexfloat_class(ch,0x400)) {state=16;break;}
            if(integerDigits<14) {
                ch=hexfloat_upper(ch);byte=(UInt8)(ch<65?ch-48:ch-55);
                if(!(used&1)) byte<<=4;digits[used/2]|=byte;used++;
            } else *inexact|=ch!='0';
            ch=hexfloat_take(&text);count++;break;
        case 16:if(hexfloat_upper(ch)=='P') {state=32;ch=hexfloat_take(&text);count++;}else status=0x800;break;
        case 32:
            if(ch=='-') negative=1;else if(ch!='+') {count--;text--;}
            state=64;ch=hexfloat_take(&text);count++;break;
        case 64:
            if(!hexfloat_class(ch,8)) status=0x1000;
            else if(ch=='0') {state=128;ch=hexfloat_take(&text);count++;}else state=256;
            break;
        case 128:if(ch=='0') {ch=hexfloat_take(&text);count++;}else state=256;break;
        case 256:
            if(!hexfloat_class(ch,8)) status=0x800;else {exponent=exponent*10+ch-48;ch=hexfloat_take(&text);count++;}break;
        }
    }
    if((UInt32)(count-1)<=2||!(state&0x18e)) return text;
    if(ch) text--;if(negative) exponent=-exponent;exponent+=integerDigits*4;
    for(shift=0;shift<4&&!(digits[0]&(0x80>>shift));shift++) exponent--;
    carry=0;
    for(i=7;i>=0;i--) {original=digits[i];digits[i]=(original<<(shift+1))|carry;carry=original>>(8-(shift+1));}
    *(UInt32 *)packed=0;*(UInt32 *)(packed+4)=0;
    for(i=0;i<7;i++) {
        byte=digits[i];if(i*8+8>52) {byte&=(UInt8)(0xff<<(52-i*8));*inexact|=byte!=digits[i];}
        packed[i+1]|=byte>>4;packed[i+2]|=byte<<4;
    }
    if(((UInt32)(exponent+1022)&0xfffff800)!=0) {*range=1;return text;}
    packed[0]|=(UInt32)(exponent+1022)>>4;packed[1]|=(UInt32)(exponent+1022)<<4;
    for(i=0;i<4;i++) {temp=packed[i];packed[i]=packed[7-i];packed[7-i]=temp;}
    memcpy(result,packed,8);return text;
}

#pragma pack(push,2)
typedef struct MacroCursor { MacroArgument *list;MacroNode *current,*previous; } MacroCursor;
#pragma pack(pop)
extern UInt8 fn_0047f240(LexerToken *,char *);
static __inline void delete_after(MacroArgument *list,MacroNode *before)
{
    if(!before) {list->head=list->head->next;if(!list->head) list->tail=0;}
    else if(before->next) {before->next=before->next->next;if(!before->next) list->tail=before;}
}
static __inline void assert_position(MacroNode *before,MacroNode *current,UInt8 thru)
{
    if(before&&before->next!=current) preprocessor_internal_msg(1,0,"CPrepLexer.c",thru?"mstate_delete_after_thru_keep_pos":"mstate_delete_after_keep_pos",thru?2648:2660);
}
UInt8 pastemacrotoken(MacroCursor *cursor,MacroNode *beforePrevious,Macro *macro)
{
    MacroNode *paste=cursor->current,*left=cursor->previous,*right,*node;LexerToken raw;char small[256],*buffer=small,*leftText,*rightText;SInt32 length,total;UInt8 saved;SourceRef ref;
    if(!paste||paste->kind!=-18) preprocessor_internal_msg(1,0,"CPrepLexer.c","pastemacrotoken",3492);
    for(;;) {
        if(cursor->current) {cursor->previous=cursor->current;cursor->current=cursor->current->next;}
        right=cursor->current;if(!right||right->kind!=-18) break;
        assert_position(left,paste,0);delete_after(cursor->list,paste);cursor->previous=left;cursor->current=paste?paste:cursor->list->head;
    }
    if(right) right->flags&=0xfe;
    if(left&&(UInt16)(left->kind+20)>1) {
        if(!right||right->kind==-19) {assert_position(beforePrevious,left,1);mlist_delete_after_thru((MacroList *)cursor->list,left,right);cursor->previous=beforePrevious;cursor->current=left;return 1;}
        if(right->kind==-20) {
            if(left->kind==',') {mlist_delete_after_thru((MacroList *)cursor->list,beforePrevious,right);cursor->previous=beforePrevious;cursor->current=right?right->next:0;return 1;}
            assert_position(beforePrevious,left,1);mlist_delete_after_thru((MacroList *)cursor->list,left,paste);cursor->previous=beforePrevious;cursor->current=left;return 1;
        }
        if(left->kind>-14&&left->kind<-11&&left->kind==right->kind) goto unpasted;
        if(left->kind>=-14&&left->kind<=-12&&left->kind==right->kind) goto unpasted;
        leftText=preprocesstoken(left->kind,left->text,strlen(left->text),0);length=strlen(leftText);
        rightText=preprocesstoken(right->kind,right->text,strlen(right->text),0);total=length+strlen(rightText);
        if((UInt32)total>255) buffer=aalloc(total+1);strcpy(buffer,leftText);strcpy(buffer+length,rightText);
        if(fn_0047f240(&raw,buffer)) {
            node=aalloc(12);node->kind=raw.kind;node->flags=left->flags&0xbf;node->text=aalloc(raw.value2+1);memcpy(node->text,raw.value,raw.value2+1);node->next=0;
            mlist_delete_after_thru((MacroList *)cursor->list,beforePrevious,right);
            if(!beforePrevious) {node->next=cursor->list->head;cursor->list->head=node;if(!cursor->list->tail) cursor->list->tail=node;}
            else {node->next=beforePrevious->next;if(!node->next) cursor->list->tail=node;beforePrevious->next=node;}
            cursor->previous=beforePrevious;cursor->current=node;return 0;
        }
        if(!(paste->flags&0x80)&&fn_0070f089&&!(macro->flags&0x80)) {
            saved=fn_0070f08e;if(saved) {fn_0070f08e=0;preprocessor_reconfig(&fn_0070f08e);}macro->flags|=0x80;
            if(!lexer->stream) scanner_getsourceref(0,&ref);else ref=lexer->stream->ref;
            left->text=leftText;rightText=preprocesstoken(right->kind,right->text,strlen(right->text),0);leftText=preprocesstoken(left->kind,left->text,strlen(left->text),0);
            lexer_warning_at_sourceref(&ref,0x28c7,leftText,rightText,macro->name->text);
            if(fn_0070f08e!=saved) {fn_0070f08e=saved;preprocessor_reconfig(&fn_0070f08e);}
        }
unpasted:assert_position(beforePrevious,left,0);delete_after(cursor->list,left);cursor->previous=beforePrevious;cursor->current=left?left:cursor->list->head;return 0;
    }
    right->flags|=left->flags&1;mlist_delete_after_thru((MacroList *)cursor->list,beforePrevious,paste);cursor->previous=beforePrevious;cursor->current=paste?paste->next:0;return 1;
}
void lexer_expand_macro(Macro *macro,UInt8 flags,SourceRef *ref,MacroList *outputRaw)
{
    MacroArgument *output=(MacroArgument *)outputRaw,*arguments,*expanded;MacroNode *node;UInt8 saved=fn_0070f071,finished=0,hasSpecial=0,variadic;UInt8 *encoded;SInt32 count=0,index,size;SourceRef at;MacroCursor cursor;MacroNode *beforePrevious=0;
    if(fn_0070f071) {fn_0070f071=0;preprocessor_reconfig(&fn_0070f071);}lexer_macro_stacks++;
    if(macro->flags&8) {
        encoded=(UInt8 *)lexer_expand_special_macro(macro,&size);output->head=output->tail=0;
        while(expandmacrotoken(macro,&encoded,&node)) add_node(output,node);goto done;
    }
    if(macro->argCount) {
        if(lexer->macroLocks<0) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_expand_macro",4305);
        lexer->macroLocks++;
        do {do {size=readmacrotoken(0,&node);}while(size==-7);}while(size==-20||size==-19);
        if(macro->argCount<2) finished=readmacrotoken(0,&node)==')';
        else {
            size=(macro->argCount-1)*8;arguments=aalloc(size);expanded=aalloc(size);
            for(count=0;!finished&&count<macro->argCount-1;count++) {
                variadic=(macro->flags&3)&&count+1==macro->argCount-1;
                finished=gathermacroargument(variadic,(MacroList *)&arguments[count]);
                if(!arguments[count].head) {node=aalloc(12);node->kind=variadic?-20:-19;node->flags=0;node->text="";node->next=0;add_node(&arguments[count],node);hasSpecial=1;}
                if(arguments[count].tail) arguments[count].tail->next=0;expanded[count].head=expanded[count].tail=0;
            }
            if(finished&&(macro->flags&2)&&count+1==macro->argCount-1) {
                arguments[count].head=arguments[count].tail=0;node=aalloc(12);node->kind=-20;node->flags=0;node->text="";node->next=0;add_node(&arguments[count],node);expanded[count].head=expanded[count].tail=0;hasSpecial=1;count++;
            }
        }
        if(!finished||count<macro->argCount-1) {
            if(lexer->stream) at=lexer->stream->ref;else lexer_getsourceref(&at);
            if(!finished) lexer_error_at_sourceref(&at,0x28c6,macro->name->text,macro->argCount-1);
            else lexer_error_at_sourceref(&at,0x28c5,macro->name->text,count,(macro->flags&3)?"...":"",macro->argCount-1);
            output->head=output->tail=0;goto done;
        }
        lexer->macroLocks--;if(lexer->macroLocks<0) preprocessor_internal_msg(1,0,"CPrepLexer.c","lexer_expand_macro",4401);
    }
    if(!macro->text) output->head=output->tail=0;
    else if(!(macro->flags&0x20)) {
        output->head=output->tail=0;encoded=macro->text;while(expandmacrotoken(macro,&encoded,&node)) add_node(output,node);
        if(output->head) output->head->flags|=flags&1;
    } else {
        hasSpecial|=expand_mstream(macro,macro->text,arguments,expanded,ref,output);
        if(hasSpecial) {
            cursor.list=output;cursor.current=output->head;cursor.previous=0;
            while(cursor.current) {
                if(cursor.current->kind==-20||(cursor.current->kind==-19&&(!cursor.current->next||cursor.current->next->kind!=-18)&&(!beforePrevious||beforePrevious->next==cursor.previous))) {
                    assert_position(beforePrevious,cursor.previous,0);delete_after(output,cursor.previous);cursor.current=cursor.previous;cursor.previous=beforePrevious;if(!cursor.current) {cursor.current=output->head;continue;}
                } else if(cursor.current->kind==-18&&pastemacrotoken(&cursor,beforePrevious,macro)) continue;
                beforePrevious=cursor.previous;if(cursor.current) {cursor.previous=cursor.current;cursor.current=cursor.current->next;}
            }
        }
        if(output->head) output->head->flags|=flags&1;
    }
done:if(output->head) lexer_push_mstream(macro,(MacroList *)output,1,ref);
    if(fn_0070f071!=saved) {fn_0070f071=saved;preprocessor_reconfig(&fn_0070f071);}lexer_macro_stacks--;
}

#pragma pack(push,2)
typedef struct FormatPiece { UInt32 kind;void *source;UInt8 encoding,unknown09;SInt32 offset,length;UInt8 marked,unknown13;struct FormatPiece *next; } FormatPiece;
#pragma pack(pop)
extern SInt32 sourcetext_get_line_number(LexerFile *,SInt32),sourcetext_get_line_offset(LexerFile *,SInt32);
extern char *scanner_get_text(void);
extern void preprocessor_format_source_line(FormatPiece *,char *,UInt32,void *);
extern char fn_00699a21[],fn_00699a2d[];
static __inline void format_append(FormatPiece **head,FormatPiece **tail,UInt32 kind,void *source,SInt32 offset,SInt32 length,UInt8 marked)
{
    FormatPiece *piece=aalloc(24);piece->kind=kind;piece->source=source;if(kind) piece->encoding=2;piece->offset=offset;piece->length=length;piece->marked=marked;piece->next=0;
    if(*tail) (*tail)->next=piece;else *head=piece;*tail=piece;
}
static __inline void lexer_temp_restore(LexerTemp *temp)
{
    if(temp->pushed) lexer_pop();else if(temp->saved) {lexer=temp->saved;scanner=*temp->saved->scannerSave;scanner_resync();scanner_setstate(&temp->position);}
}
UInt8 lexer_setupref(void *output,char *line, SInt32 capacity,SourceRef *start,SourceRef *finish,void *tokenLength,UInt8 physical)
{
    UInt8 *record=output,haveSpec=0,inMacro=0,suppressed;LexerFile *file,*disk,*physicalFile;SourceRef first,last;LexerTemp temp;ScannerPosition position;LexerToken token;FormatPiece *head=0,*tail=0;SInt32 length=(SInt32)tokenLength,begin,end,left,right,expandedSize;char filename[256],*expanded,*expandedStart,*expandedEnd;MacroStream *stream;
    memclrw(record,276);*line=0;if(!start) return 0;if(!finish) finish=start;
    if(start->file!=finish->file) start=finish;file=finish->file;if(!file) return 0;
    if(physical|| (file->kind==1&&!fn_0070f087&&fn_0070f086)) {
        if(physical&&(!fn_0070f086||!fn_0070f087)) return 0;
        if(file->kind!=1||!(physicalFile=((LogicalLineFile *)file)->file)||physicalFile->kind) return 0;
        memcpy(record,physicalFile->backing,260);first=*start;lexer_flattensourceref(&first,1);
        begin=sourcetext_get_line_offset(physicalFile,first.line);end=sourcetext_get_line_offset(physicalFile,first.line+1);
        *(SInt32 *)(record+268)=begin;*(SInt32 *)(record+272)=0;*(SInt32 *)(record+260)=first.line;
        format_append(&head,&tail,0,physicalFile,begin,end-begin,0);goto format;
    }
    stream=lexer?lexer->stream:0;
    if(stream&&(finish==&stream->ref||(finish->file==stream->ref.file&&finish->offset==stream->ref.offset))) inMacro=1;
    if(inMacro&&length>0) length=0;
    disk=resolve_disk(file);
    if(file->kind==1||file->kind==3) {first=*start;last=*finish;start=&first;finish=&last;lexer_flattensourceref(start,0);lexer_flattensourceref(finish,0);file=start->file;}
    else if(file->kind==2) {
        disk=0;physicalFile=file->backing;
        if(physicalFile&&!physicalFile->kind) {memcpy(record,physicalFile->backing,260);*(SInt32 *)(record+268)=*(SInt32 *)((char *)file+26);*(SInt32 *)(record+272)=1;*(SInt32 *)(record+260)=*(SInt32 *)((char *)file+30);haveSpec=1;}
    }
    if(!disk) {
        if(!haveSpec) *(SInt32 *)(record+260)=start->line;
        snprintf(filename,256,haveSpec?fn_00699a21:fn_00699a2d,file->name->text,start->line);
        format_append(&head,&tail,1,filename,0,strlen(filename),0);length=0;
    } else {
        memcpy(record,disk->backing,260);
        if(length==-1) length=0;
        else if(!length) {
            suppressed=0;if(lexer) {suppressed=lexer->flag29;lexer->flag29=1;}
            haveSpec=lexer_temp_push(finish->file,&temp);if(lexer) lexer->flag29=suppressed;
            if(haveSpec) {
                scanner_getstate(&position);position.current=finish->offset+((LexerFile *)finish->file)->contents;
                position.line=sourcetext_get_line_number(scanner.file,finish->offset);
                *(char **)((char *)&position+8)=scanner_get_text()+sourcetext_get_line_offset(scanner.file,position.line);
                scanner_setstate(&position);suppressed=scanner_suppress_messages(1);scanner_readtoken(&token);scanner_suppress_messages(suppressed);lexer_temp_restore(&temp);length=token.tail.length;
            } else length=1;
        }
        *(SInt32 *)(record+268)=start->offset;*(SInt32 *)(record+272)=finish->offset+length-start->offset;*(SInt32 *)(record+260)=start->line;
    }
    begin=sourcetext_get_line_offset(file,start->line);end=sourcetext_get_line_offset(file,finish->line+1);left=start->offset;right=finish->offset+length;
    if(left<begin||right<begin) {begin=sourcetext_get_line_offset(file,sourcetext_get_line_number(file,left));if(left<begin||right<begin) return 0;}
    if(end<left||end<right) {end=sourcetext_get_line_offset(file,sourcetext_get_line_number(file,right)+1);if(end<left||end<right) return 0;}
    if(inMacro) {
        stream=lexer->stream;
        expanded=lexer_simple_expand_string(stream->macro,(MacroList *)stream->tokens.head,stream->tokens.current,&expandedStart,&expandedEnd,&expandedSize);
        if(expanded) {
            if(expanded+32<expandedStart) expanded=expandedStart-32;
            if(expandedEnd+64<expanded+expandedSize) expandedSize=expandedEnd+64-expanded;
            if(stream->ref.offset<left) left=stream->ref.offset;if(right<stream->offset) right=stream->offset;
            format_append(&head,&tail,0,file,begin,left-begin,0);
            format_append(&head,&tail,1,expanded,0,expandedStart-expanded,0);
            format_append(&head,&tail,1,expanded,expandedStart-expanded,expandedEnd-expandedStart,1);
            format_append(&head,&tail,1,expanded,expandedEnd-expanded,expandedSize-(expandedEnd-expanded),0);
            goto suffix;
        }
    }
    if(begin+64<left) begin=left-64;
    if((UInt32)capacity<(UInt32)(end-begin)&&begin+capacity<end) end=begin+capacity;
    format_append(&head,&tail,0,file,begin,left-begin,0);format_append(&head,&tail,0,file,left,right-left,1);
suffix:if(right<end) format_append(&head,&tail,0,file,right,end-right,0);
format:preprocessor_format_source_line(head,line,capacity,record);return 1;
}

extern void (*fn_007106b0)(LexerFile *,LexerToken *,LexerToken *,Macro *);
void lexer_prepdefine(void)
{
    LexerToken raw,original,hashToken;HashName *name,*arg,*arguments[256];Macro *old,*macro,*entry,*previous;Keyword *keyword;SInt32 argCount=0,i,allocation,lastIndex=0;SInt16 kind,previousKind=0;UInt8 reported=0,variadic=0,flags,pendingPaste=0,vararg=0;char *copy;UInt8 *encoded;
    if(!lexer_readtokenorskip(&raw,-3,0x277b)) return;
    original=raw;name=GetHashNameNodeExport(raw.value);
    if(!strcmp(name->text,"defined")) lexer_error(&raw,0x28ef,name->text);
    else if(fn_0070f1a8) {
        for(keyword=lexer_kwhash[name->hash];keyword;keyword=keyword->next) if(keyword->name==name&&kwcheck_impl(keyword,name)) break;
        if(keyword) {
            kind=keyword->token;
            if(kind=='!'||kind=='&'||kind=='^'||kind=='|'||kind=='~'||(UInt32)(kind-369)<3||kind==373||kind==375) {
                if(!fn_0070f1af) lexer_warning(&raw,0x28ee,name->text);else lexer_error(&raw,0x28ee,name->text);
            }
        }
    }
    old=lexer_lookup_macro(name);lexer->flag28=1;kind=lexer_readtoken_impl(&raw);
    if(kind=='('&&!raw.space) {
        argCount=1;
        for(;;) {
            kind=lexer_readtoken_impl(&raw);
            if(kind!=-3&&kind!=383) break;
            arg=GetHashNameNodeExport(raw.value);
            if((fn_0070f1ca||!fn_0070f1af)&&!strcmp(raw.value,"__VA_ARGS__")) {lexer_error(&raw,0x287d,raw.value);lexer_skipendofline();return;}
            if(kind==383) {
                if(!fn_0070f1ca&&fn_0070f1af) lexer_error(&raw,0x287d,raw.value);
                arg=GetHashNameNodeExport("__VA_ARGS__");vararg=1;variadic=1;
            }
            for(i=1;i<argCount;i++) if(arguments[i-1]==arg) {lexer_error(&raw,0x287d,arg->text);lexer_skipendofline();return;}
            arguments[argCount-1]=arg;
            if(old) {
                if(old->argCount<argCount) lexer_macro_redef_error(&raw,old,&reported);
                if(((HashName **)((char *)old+32))[argCount-1]!=arg&&!fn_0070f1b3) lexer_macro_redef_error(&raw,old,&reported);
            }
            if(argCount<256) argCount++;else lexer_error(&raw,0x277e);
            kind=lexer_readtoken_impl(&raw);if(vararg||kind!=',') break;
        }
        if(!vararg&&kind==383) {
            if(!fn_0070f1da&&fn_0070f1af) lexer_error(&raw,0x287d,raw.value);
            variadic|=2;lexer_readtoken_impl(&raw);
        } else {
            if(kind==-7) {lexer_error(&raw,0x2780);return;}
            if(kind!=')') {lexer_error(&raw,0x277d);lexer_skipendofline();return;}
        }
        kind=lexer_readtoken_impl(&raw);
    }
    raw.space=raw.bol=0;
    if(old&&old->argCount!=argCount) {copy=aalloc(raw.value2+1);memcpy(copy,raw.value,raw.value2+1);raw.value=copy;lexer_macro_redef_error(&original,old,&reported);}
    allocation=argCount?(argCount-2)*4+36:32;macro=galloc(allocation);memclrw(macro,allocation);macro->name=name;macro->argCount=argCount;macro->ref=original.ref;macro->flags=variadic;
    for(i=1;i<argCount;i++) ((HashName **)((char *)macro+32))[i-1]=arguments[i-1];
    lexer_mlist.size=0;
    for(;;) {
        flags=0;if(!lexer_mlist.size) raw.space=raw.bol=0;
        if(kind==-18) {
            if(!lexer_mlist.size||peekeol()) {lexer_error(&raw,0x2785);lexer_skipendofline();goto finish;}
            macro->flags|=0x20;encoded=*(UInt8 **)lexer_mlist.data+lastIndex;
            if((encoded[1]&0x80)&&(encoded[2]&4)) encoded[2]|=0x10;
            pendingPaste=1;
        } else if(kind==-7||!kind) break;
        else if(kind==-3) {
            arg=GetHashNameNodeExport(raw.value);
            for(i=1;i<macro->argCount;i++) if(((HashName **)((char *)macro+32))[i-1]==arg) {
                macro->flags|=0x20;flags=pendingPaste?0x14:4;pendingPaste=0;raw.kind=i;break;
            }
        } else if(kind=='#') {
            flags=raw.space!=0;hashToken=raw;kind=lexer_readtoken_impl(&raw);
            if(kind==-3) {
                macro->flags|=0x20;raw.space=raw.bol=0;arg=GetHashNameNodeExport(raw.value);flags|=8;
                for(i=1;i<macro->argCount;i++) if(((HashName **)((char *)macro+32))[i-1]==arg) {raw.kind=i;flags|=4;break;}
                if(fn_0070f1af&&argCount>0&&!(flags&4)) lexer_error(&raw,0x2926);
            } else {
                if(fn_0070f1af&&argCount>0&&kind!=-18&&previousKind!=-18) lexer_error(&raw,0x2926);
                lexer_unreadtoken(&raw);raw=hashToken;raw.value=fn_00699909;raw.value2=raw.tail.length=1;
            }
        }
        lastIndex=lexer_mlist.size;appendmacrotoken(&lexer_mlist,&raw,flags);previousKind=raw.kind;kind=lexer_readtoken_impl(&raw);
    }
    lexer_unreadtoken(&raw);
finish:
    if(lexer_mlist.size<1) {macro->text=0;macro->textSize=0;if(old&&old->text) lexer_macro_redef_error(&original,old,&reported);}
    else {
        macro->textSize=lexer_mlist.size;appendmacrotoken(&lexer_mlist,0,0);
        if(lexer_mlist.size>0x100000) {lexer_error(&raw,0x277f);return;}
        if(old&&(!old->text||memcmp(*(char **)lexer_mlist.data,old->text,lexer_mlist.size))) lexer_macro_redef_error(&original,old,&reported);
        macro->text=galloc(lexer_mlist.size);memcpy(macro->text,*(char **)lexer_mlist.data,lexer_mlist.size);
    }
    if(!old||reported) {
        macro->next=pp_macrohashtable[name->hash];pp_macrohashtable[name->hash]=macro;
        if(reported) {
            previous=0;
            for(entry=pp_macrohashtable[old->name->hash];entry;entry=entry->next) {if(entry==old) {if(previous) previous->next=entry->next;else pp_macrohashtable[old->name->hash]=entry->next;break;}previous=entry;}
        }
        if(fn_007106b0) fn_007106b0(lexer->file,&original,&raw,macro);
    }
}

/* Offsets independently read from the x86 image; keep native layouts private. */
#define LEXER_SIZE(T,N) typedef char lexer_size_##T[(sizeof(T)==(N))?1:-1]
#define LEXER_OFFSET(T,F,N) typedef char lexer_offset_##T##_##F[(offsetof(T,F)==(N))?1:-1]
LEXER_SIZE(SourceRef,12); LEXER_SIZE(LexerToken,28); LEXER_SIZE(CompilerToken,28);
LEXER_OFFSET(LexerToken,ref,12); LEXER_OFFSET(LexerToken,tail,24);
LEXER_OFFSET(CompilerToken,ref,14); LEXER_OFFSET(CompilerToken,space,26);
LEXER_OFFSET(HashName,text,10); LEXER_OFFSET(LexerFile,contents,10);
LEXER_OFFSET(LexerFile,backing,22); LEXER_OFFSET(LexerFile,diskInfo,42);
LEXER_OFFSET(LogicalLineFile,sourceLine,30); LEXER_OFFSET(LogicalLineFile,file,34); LEXER_OFFSET(LogicalLineFile,logicalLine,38);
LEXER_SIZE(ScannerPosition,16); LEXER_OFFSET(ScannerPosition,line,12);
LEXER_SIZE(ScannerState,80); LEXER_OFFSET(ScannerState,position,44);
LEXER_SIZE(MacroNode,12); LEXER_SIZE(MacroList,12); LEXER_SIZE(MacroArgument,8);
LEXER_SIZE(Macro,36); LEXER_OFFSET(Macro,ref,16); LEXER_OFFSET(Macro,argCount,28); LEXER_OFFSET(Macro,flags,30);
LEXER_SIZE(Keyword,16); LEXER_SIZE(KeywordInput,12); LEXER_SIZE(GList,16);
LEXER_SIZE(MacroStream,40); LEXER_OFFSET(MacroStream,tokens,20); LEXER_OFFSET(MacroStream,macro,32);
LEXER_SIZE(LexerState,50); LEXER_OFFSET(LexerState,stream,20); LEXER_OFFSET(LexerState,silent,36); LEXER_OFFSET(LexerState,savedIgSize,42); LEXER_OFFSET(LexerState,macroLocks,46);
LEXER_SIZE(IfState,38); LEXER_OFFSET(IfState,savedSize,30); LEXER_OFFSET(IfState,seen,36);
LEXER_SIZE(Number64,8); LEXER_SIZE(NumericType,8); LEXER_SIZE(PPValue,10);
LEXER_SIZE(LexerTemp,24); LEXER_OFFSET(LexerTemp,pushed,20);
LEXER_SIZE(ScannerIterator,94); LEXER_OFFSET(ScannerIterator,current,82);
LEXER_SIZE(MacroCursor,12); LEXER_SIZE(FormatPiece,24); LEXER_OFFSET(FormatPiece,offset,10); LEXER_OFFSET(FormatPiece,next,20);
#undef LEXER_SIZE
#undef LEXER_OFFSET

/* Lexer-owned zero-initialized storage; address aliases remain unnamed in original evidence. */
SInt16 igtlevel;
GList macro_temp;
LexerToken if_tok;
char * igtip;
SInt16 fn_006dd056[256];
LexerToken exprtok;
SInt16 exprtk;
LexerToken * lexer_incltoken;
SInt32 now_time;
Macro envrM;
Macro trgtM;
Macro timeM;
Macro dateM;
Macro fileM;
Macro lineM;
SInt32 lexer_macro_stacks;
UInt8 lexer_pragmaonce;
UInt8 lexer_incondexpr;
SInt32 lexer_lines;
SInt32 ig_entry_iglist_size;
UInt8 ig_entry_had_token;
SourceRef igtest_end_ref;
SourceRef igtest_start_ref;
SInt32 iflevel;
IfState ifstack[256];
Keyword * lexer_kwhash[2048];
SInt32 lexer_readaheadmax;
SInt32 lexer_readaheadidx;
SInt32 lexer_readaheadsize;
LexerToken * lexer_readahead;
LexerFile * lexer_first_line_file;
LexerFile * lexer_igtext;
GList lexer_iglist;
UInt8 lexer_skipping_if;
GList lexer_inclfromlist;
UInt8 lexer_in_directive;
GList lexer_dlist;
UInt8 lexer_record_tokens;
UInt8 asciistring[512];
GList lexer_mlist;
LexerState * lexer;
UInt8 lexer_gathering_asm_args;
GList lexer_asmlist;
