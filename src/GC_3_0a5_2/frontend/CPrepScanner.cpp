/* Native GC 3.0a5.2 scanner reconstruction. Private records reflect x86
 * payloads and do not reuse the GC 1.2.5 tokenizer layout.
 * Native member and data review is recorded in the TU ledger. */
#include <stddef.h>

typedef unsigned char ScanByte;
typedef unsigned long ScanWord;
struct ScanMagic {
    ScanWord value;
    ScanMagic() { value=12345; }
    operator ScanWord() const { return value; }
};
typedef char VerifyScanMagic[(sizeof(ScanMagic)==4)?1:-1];
#pragma pack(push,2)
struct ScanFile {
    void *name;
    ScanWord unknown4;
    ScanByte kind,padding;
    char *text;
    ScanWord length;
    void *lineTable,*parent;
};
struct ScanToken {
    short kind;
    ScanByte flags[2];
    char *text;
    ScanWord length;
    ScanByte tail[16];
};
struct ScanState {
    char *current;
    ScanByte lineStart, flags, whitespace, padding;
    char *line;
    ScanWord column;
};
struct ScanContext {
    ScanFile *file;
    char *text, *end;
    ScanByte active, decoderFlag, suppress, padding0;
    void *decoder;
    ScanByte decoderMode, padding1[3];
    void *callbacks[4];
    void *extra;
    ScanState state, previous;
    ScanWord finalWord;
};
struct ScanSourceRef { char filename[256];ScanWord filenameFlags,line,unknown108,start,length; };
struct ScanSourceText { int kind;char *text;ScanByte encoding,pad0;ScanWord start,length;ScanByte highlighted,pad1;ScanSourceText *next; };
struct ScanIterator { ScanContext saved;ScanByte suppress,padding;char *start,*end,*current; };
struct ScanPunctuation { const char *name; short token; };
struct ScanPunctuationNode { ScanPunctuationNode *next;char *text;short token;int longer; };
struct ScanTokenNameList { char ***data;ScanWord size,hndlsize,growsize; };
#pragma pack(pop)
typedef char VerifyScanState[(sizeof(ScanState)==16)?1:-1];
typedef char VerifyScanContext[(sizeof(ScanContext)==80)?1:-1];
typedef char VerifyScanTokenNameList[(sizeof(ScanTokenNameList)==16)?1:-1];

extern "C" {
extern ScanContext scannerContext;
extern void *scannerDefaultDecoder;
ScanMagic scannerMagic;
extern ScanPunctuationNode *scannerPunctuationBuckets[255];
extern ScanByte scannerPairFilter[312], scannerUnicodeFlags[65536];
extern ScanByte scannerDollarIdentifier, scannerOptionQuestion, scannerQuestionAlternate;
extern ScanPunctuation scannerInitialPunctuation[4], scannerStandardPunctuation[55];
extern ScanTokenNameList scannerTokenNameList;
extern int scannerDefaultEncoding;
extern ScanByte scannerDefaultGuess;
extern ScanByte scannerCharacterFlags[256];
extern void memclrw(void *,ScanWord);
extern void fn_0044ca40(int,int,const char *,const char *,int);
extern short InitGList(void *,ScanWord);
extern void FreeGList(void *);
extern void fn_00404960(void *);
extern void scanner_error(void *,int,int,short,...);
extern void add_punc_token(const ScanPunctuation *,const char *);
extern void scanner_init(ScanFile *);
extern void fn_00482b10(void);
extern void fn_00482ce0(ScanWord);
extern ScanWord sourcetext_get_line_offset(ScanFile *,ScanWord);
extern short fn_00490990(ScanToken *);
extern void scanner_init_decoder(ScanByte);
extern char scannerSingleTokenText[2],scannerEllipsisText[],scannerNegativeTokenText[],scannerUnknownTokenText[];
extern int strcmp(const char *,const char *);
extern int strncmp(const char *,const char *,size_t);
extern char *strcpy(char *,const char *);
extern size_t strlen(const char *);
extern void *memcpy(void *,const void *,size_t);
extern void *galloc(ScanWord);
extern void AppendGListLong(void *,ScanWord);
extern void *lalloc(ScanWord);
extern int snprintf(char *,size_t,const char *,...);
extern int sourcetext_get_line_number(ScanFile *,ScanWord);
extern void fn_0044b6c0(ScanSourceText *,int,int,ScanSourceRef *);
}
static char scannerFilename[]="CPrepScanner.cpp";
static char scannerSetupName[]="scanner_setup";
static char scannerLineTableName[]="scanner_getlinetable";
static char scannerFixedTextName[]="scanner_tokenhasfixedtext";
static char scannerAddPunctuationName[]="add_punc_token";
static char scannerSetupRefName[]="scanner_setupref";
static char scannerSourceLineFormat[]="%s line %d   ";
extern "C" ScanWord scannerBaseDecoderVTable[];

static inline ScanWord scanner_string_length(const char *text)
{
    const char *end=text;while(*end)++end;return end-text;
}
extern "C" ScanByte scanner_suppress_messages(ScanByte enabled)
{
    ScanByte old=scannerContext.suppress;
    scannerContext.suppress=enabled;
    return old;
}
extern "C" void scanner_unreadtoken(void) { scannerContext.state=scannerContext.previous; }
extern "C" void scanner_setstate(const ScanState *state) { scannerContext.state=*state; }
extern "C" void scanner_getstate(ScanState *state) { *state=scannerContext.state; }
extern "C" char *scanner_get_text(void) { return scannerContext.text; }
extern "C" void scanner_set_default_global_encoding(int value,ScanByte guess)
{
    scannerDefaultEncoding=value;
    scannerDefaultGuess=guess;
}
extern "C" void scanner_setcommentchar(ScanByte ch,ScanByte value) { scannerCharacterFlags[ch]=value; }
extern "C" void scanner_skipendofline(void) { ((void (*)(void))scannerContext.callbacks[3])(); }
extern "C" short scanner_readtoken(ScanToken *token)
{
    return ((short (*)(ScanToken *))scannerContext.callbacks[2])(token);
}
extern "C" void scanner_validate(void) {}
extern "C" void scanner_fixup_names(void) {}
extern "C" void scanner_term(void)
{
    if(scannerContext.decoder!=scannerDefaultDecoder && scannerContext.decoder) {
        *(void **)scannerContext.decoder=scannerBaseDecoderVTable;
        fn_00404960(scannerContext.decoder);
    }
    scannerContext.decoder=scannerDefaultDecoder;
}
extern "C" void scanner_cleanup(void)
{
    memclrw(&scannerContext,80);
    FreeGList(&scannerTokenNameList.data);
}
extern "C" void scanner_getlinetable(ScanFile *file)
{
    ScanContext saved=scannerContext;
    if(!file || !file->text)
        fn_0044ca40(1,0,scannerFilename,scannerLineTableName,0x12f1);
    scanner_init(file);
    fn_00482b10();
    scanner_term();
    scannerContext=saved;
}
extern "C" ScanByte scanner_tokenhasfixedtext(const ScanToken *token)
{
    short kind=token->kind;
    if(kind<0) {
        switch(kind) {
            case -20:case -19:case -18:case -7:return 1;
            case -17:case -16:case -15:case -14:case -13:case -12:
            case -11:case -10:case -9:case -8:case -6:case -3:return 0;
            default:fn_0044ca40(1,0,scannerFilename,scannerFixedTextName,0x1194);return 0;
        }
    }
    if(kind<256)return (signed char)token->text[0]==kind;
    if((unsigned long)kind>=scannerTokenNameList.size/4)return 0;
    const char *fixed=(*scannerTokenNameList.data)[kind];
    if(!fixed)fn_0044ca40(1,0,scannerFilename,scannerFixedTextName,0x11a2);
    return strcmp(token->text,fixed)==0;
}
extern "C" void scanner_setup(void)
{
    if(scannerMagic!=12345)fn_0044ca40(1,0,scannerFilename,scannerSetupName,0xf80);
    memclrw(&scannerContext,80);
    memclrw(scannerPunctuationBuckets,1020);
    memclrw(scannerPairFilter,312);
    if(InitGList(&scannerTokenNameList.data,1024))scanner_error(0,0,-1,0x28bb);
    unsigned int count=4;
    const ScanPunctuation *p=scannerInitialPunctuation;
    while(count-- && p->name) { add_punc_token(p,p->name);++p; }
    count=55;p=scannerStandardPunctuation;
    while(count-- && p->name) { add_punc_token(p,p->name);++p; }
    for(unsigned int i=0;i<65536;i++)scannerUnicodeFlags[i]&=(ScanByte)~8;
    if(scannerDollarIdentifier)scannerUnicodeFlags['$']|=1;
    else scannerUnicodeFlags['$']&=(ScanByte)~1;
    if(scannerOptionQuestion) {
        scannerUnicodeFlags['?']|=64;
        scannerQuestionAlternate|=7;
    } else {
        scannerUnicodeFlags['?']&=(ScanByte)~64;
        scannerQuestionAlternate=0;
    }
}

extern "C" void add_punc_token(const ScanPunctuation *punctuation,const char *text)
{
    ScanWord hash=0,bucket;
    int index=0;
    int ch=(signed char)text[0];
    while(ch) {
        if(index>0) {
            int previous=(signed char)text[index-1];
            int pair=(int)(((ScanWord)previous<<4)^(ScanWord)ch);
            scannerPairFilter[pair%312]|=(ScanByte)(1U<<((previous-ch)&7));
        }
        hash=(hash<<5)^((hash>>24)+(ScanWord)ch-32);
        bucket=hash%255;
        ScanPunctuationNode *node=scannerPunctuationBuckets[bucket];
        while(node) {
            if(!strncmp(node->text,text,index+1)) {
                if(!text[index+1]) {
                    short kind=punctuation->token;
                    if(node->token!=kind && node->token!=-6) {
                        fn_0044ca40(1,0,scannerFilename,scannerAddPunctuationName,0x1027);
                    } else node->token=kind;
                } else node->longer=1;
                break;
            }
            node=node->next;
        }
        if(!node) {
            node=(ScanPunctuationNode *)galloc(14);
            char *prefix=(char *)galloc(index+2);
            memcpy(prefix,text,index+1);
            prefix[index+1]=0;
            node->text=prefix;
            node->token=text[index+1]?-6:punctuation->token;
            node->longer=text[index+1]?1:0;
            node->next=scannerPunctuationBuckets[bucket];
            scannerPunctuationBuckets[bucket]=node;
        }
        ++index;ch=(signed char)text[index];
    }
    if(punctuation->token>=256) {
        ScanWord offset=(ScanWord)(int)punctuation->token*4;
        while(scannerTokenNameList.size<=offset)AppendGListLong(&scannerTokenNameList.data,0);
        char **slot=&(*scannerTokenNameList.data)[punctuation->token];
        if(!*slot) {
            char *copy=(char *)galloc(scanner_string_length(text)+1);
            strcpy(copy,text);
            *slot=copy;
        }
    }
}

extern "C" short scanner_peektoken(ScanToken *token)
{
    ScanToken temporary;
    if(!token)token=&temporary;
    scanner_readtoken(token);
    scanner_unreadtoken();
    return token->kind;
}
extern "C" int fn_0047f3e0(const char *name)
{
    if((name[0]=='l'||name[0]=='L') && !name[1])return -10;
    if(name[0]=='_' && name[1]=='_' && name[2]=='L' && name[3]=='1' && name[4]=='6' && !name[5])return -10;
    if(name[0]=='_' && name[1]=='_' && name[2]=='L' && name[3]=='3' && name[4]=='2' && !name[5])return -11;
    return 0;
}
extern "C" int fn_0047f460(const char *name)
{
    if((name[0]=='l'||name[0]=='L') && !name[1])return -13;
    if(name[0]=='_' && name[1]=='_' && name[2]=='L' && name[3]=='1' && name[4]=='6' && !name[5])return -13;
    if(name[0]=='_' && name[1]=='_' && name[2]=='L' && name[3]=='3' && name[4]=='2' && !name[5])return -14;
    return 0;
}
extern "C" char *scanner_get_token_text(short kind)
{
    if(kind==-7)return scannerEllipsisText;
    if(kind>=0 && kind<256) { scannerSingleTokenText[0]=(char)kind;return scannerSingleTokenText; }
    if(kind>=256 && (ScanWord)kind<scannerTokenNameList.size/4)return (*scannerTokenNameList.data)[kind];
    if(kind==-18)return scannerNegativeTokenText;
    return scannerUnknownTokenText;
}
extern "C" void scanner_parse_include(ScanByte enabled)
{
    scannerUnicodeFlags['<']&=(ScanByte)~32;
    scannerUnicodeFlags['"']&=(ScanByte)~32;
    if(enabled) {
        scannerUnicodeFlags['<']|=32;
        scannerUnicodeFlags['"']|=32;
    }
}
extern "C" void scanner_goto_line(ScanWord line)
{
    ScanFile *file=scannerContext.file;
    void *lineTable=*(void **)((char *)file+18);
    ScanWord count=lineTable?*(ScanWord *)((char *)lineTable+4)/4:0;
    if(line>count)fn_00482ce0(line);
    char *at=scannerContext.text+sourcetext_get_line_offset(scannerContext.file,line);
    scannerContext.state.current=at;
    scannerContext.state.line=at;
    scannerContext.state.column=line;
}
extern "C" ScanByte fn_0047f240(ScanToken *token,char *text)
{
    ScanState saved=scannerContext.state;
    char *oldText=scannerContext.text,*oldEnd=scannerContext.end;
    scannerContext.text=text;
    scannerContext.end=text+scanner_string_length(text);
    scannerContext.state.current=text;
    scannerContext.state.lineStart=1;
    scannerContext.state.flags=token->flags[0];
    scannerContext.state.whitespace=token->flags[1];
    scannerContext.state.line=text;
    scannerContext.state.column=0;
    fn_00490990(token);
    ScanByte complete=scannerContext.state.current==scannerContext.end;
    scannerContext.state=saved;
    scannerContext.text=oldText;scannerContext.end=oldEnd;
    return complete;
}
class ScanDecoder {
public:
    virtual ScanByte flag();
    virtual void reset();
    virtual void method08(char **current,char *end);
    virtual void method0c(char **current,char *end);
    virtual ScanByte mode();
    virtual void *callback14();
    virtual void *callback18();
    virtual void *callback1c();
    virtual void *callback20();
    virtual int decode(char *start,char *end,char **current);
    virtual void method28();
    virtual unsigned int method2c(unsigned int);
    virtual void method30();
    ScanDecoder *fn_0047fb60();
    ScanDecoder *fn_0047fb70();
    ScanDecoder *fn_0047fb80();
    ScanWord fn_00481eb0(char *,char *,char **);
};
extern "C" int scanner_iterator_decode_character(ScanIterator *iterator)
{
    return ((ScanDecoder *)scannerContext.decoder)->decode(iterator->start,iterator->end,&iterator->current);
}

extern "C" void scanner_resync(void)
{
    if(scannerContext.decoder)((ScanDecoder *)scannerContext.decoder)->reset();
}
extern "C" void *scannerCachedConverter;
extern "C" ScanByte scanner_guess_encoding(char *,char *,ScanByte);
extern "C" void scanner_reconfig(ScanByte *option)
{
    if(!option || option==&scannerDollarIdentifier) {
        if(scannerDollarIdentifier)scannerUnicodeFlags['$']|=1;
        else scannerUnicodeFlags['$']&=(ScanByte)~1;
    }
    if(!option || option==&scannerOptionQuestion) {
        if(scannerOptionQuestion) {
            scannerUnicodeFlags['?']|=64;scannerQuestionAlternate|=7;
        } else {
            scannerUnicodeFlags['?']&=(ScanByte)~64;scannerQuestionAlternate=0;
        }
    }
}
extern "C" void fn_00481900(void);
extern "C" void scanner_unload(void)
{
    if(scannerCachedConverter) {
        *(void **)scannerCachedConverter=scannerBaseDecoderVTable;
        fn_00404960(scannerCachedConverter);
    }
    scannerCachedConverter=0;
    if(scannerDefaultDecoder) {
        *(void **)scannerDefaultDecoder=scannerBaseDecoderVTable;
        fn_00404960(scannerDefaultDecoder);
    }
    scannerDefaultDecoder=0;
    fn_00481900();
}
extern "C" int scanner_set_charset(const char *);
extern "C" void sourcetext_define_line(ScanFile *,ScanWord,ScanWord);
extern "C" void scanner_init_decoding(void)
{
    if(!scannerDefaultEncoding || (!scannerDefaultGuess && ((ScanByte *)scannerContext.file)[9])) {
        scanner_init_decoder(((ScanByte *)scannerContext.file)[9]);
        return;
    }
    if(!scannerDefaultGuess) {
        ScanByte encoding=scanner_guess_encoding(scannerContext.state.current,scannerContext.end,0);
        if(encoding>3 && encoding<10) {
            scanner_init_decoder(encoding);
            goto finish;
        }
    }
    scanner_set_charset((const char *)scannerDefaultEncoding);
finish:
    if(scannerContext.active!=1)((ScanByte *)scannerContext.file)[9]=scannerContext.active;
}
extern "C" void scanner_init(ScanFile *file)
{
    memclrw(&scannerContext,80);
    scannerContext.file=file;scannerContext.text=file->text;
    scannerContext.end=file->text+file->length;
    memclrw(&scannerContext.state,16);
    scannerContext.state.current=scannerContext.text;
    scannerContext.state.lineStart=1;scannerContext.state.flags=0;scannerContext.state.whitespace=1;
    if((ScanWord)scannerContext.state.line<(ScanWord)scannerContext.text) {
        scannerContext.state.line=scannerContext.text;
        ++scannerContext.state.column;
        ScanWord count=file->lineTable?*(ScanWord *)((char *)file->lineTable+4)/4:0;
        if(count<scannerContext.state.column)sourcetext_define_line(file,scannerContext.state.column,0);
    }
    scannerContext.state.whitespace=1;scannerContext.state.flags=1;
    scannerContext.state.current=scannerContext.text;
    scannerContext.previous=scannerContext.state;
    scanner_init_decoding();
}

/* These virtual methods never read ECX. stdcall preserves their actual stack
 * cleanup while keeping the recovered address names until class names emerge. */
extern "C" void __stdcall fn_0047db10(char **,char *) {}
extern "C" void fn_0047ebf0(void) {}
extern "C" void __stdcall fn_0047f800(char **,char *) {}
extern "C" ScanByte fn_0047f810(void) { return 0; }
extern "C" int fn_0047f820(void) { return 1; }
extern "C" ScanByte fn_004834f0(void);
extern "C" short fn_00484b20(ScanToken *);
extern "C" ScanWord fn_004845f0(char *,char *,char **,ScanByte);
extern "C" ScanWord fn_00484a20(char *,char *,char **);
extern "C" ScanWord fn_00484af0(char *,char *,char **);
extern "C" void *fn_0047f830(void) { return (void *)fn_004834f0; }
extern "C" void *fn_0047f840(void) { return (void *)fn_00484b20; }
extern "C" void *fn_0047f850(void) { return (void *)fn_004845f0; }
extern "C" void *fn_0047f860(void) { return (void *)fn_00484af0; }
extern "C" ScanByte fn_00481e10(void) { return 1; }
extern "C" void __stdcall fn_00481e20(char **current,char *end)
{
    char *cursor;
    while((cursor=*current)+2<end && *cursor==27) {
        if(cursor[1]=='(') {
            if(cursor[2]=='B')scannerContext.state.lineStart=1;
            else if(cursor[2]=='J')scannerContext.state.lineStart=2;
            else scannerContext.state.lineStart=0;
            *current+=3;
        } else {
            if(cursor[1]!='$')return;
            scannerContext.state.lineStart=(cursor[2]=='@'||cursor[2]=='B')?3:0;
            *current+=3;
        }
    }
}
extern "C" void __stdcall fn_00482160(char **current,char *end)
{
    if(*current+3<end && !strncmp(*current,"\xEF\xBB\xBF",3))*current+=3;
}
extern "C" int fn_004825a0(void) { return 2; }
extern "C" int fn_004826c0(void) { return 2; }
extern "C" int fn_004827c0(void) { return 4; }
extern "C" int fn_00482870(void) { return 4; }
extern "C" void fn_00482b00(void) {}
extern "C" void scanner_iterator_destroy(ScanIterator *iterator)
{
    scannerContext=iterator->saved;
    if(scannerContext.decoder)((ScanDecoder *)scannerContext.decoder)->reset();
    scannerContext.suppress=iterator->suppress;
}
extern "C" void scanner_iterator_create_from_pptoken(ScanIterator *iterator,const ScanToken *token)
{
    ScanByte encoding=2;
    if(token->kind==-12 || token->kind==-9) {
        encoding=scannerContext.active;
        if(encoding>=4 && encoding<=9)encoding=2;
    }
    iterator->suppress=scannerContext.suppress;
    scannerContext.suppress=1;
    iterator->saved=scannerContext;
    scannerContext.text=token->text;
    scannerContext.state.current=token->text;
    scannerContext.end=token->text+token->length;
    scannerContext.decoder=0;
    scanner_init_decoder(encoding);
    iterator->start=scannerContext.state.current;
    iterator->end=scannerContext.end;
    iterator->current=iterator->start;
}

extern "C" ScanByte scanner_setupref(ScanSourceRef *out,int arg2,int arg3,char *start,char *end,int line)
{
    char prefix[80];
    ScanSourceText *head=0,*last=0;
    memclrw(out,276);
    if(!start)start=scannerContext.state.current;
    if(!end)end=scannerContext.state.current;
    if((ScanWord)start>(ScanWord)end)start=end;
    ScanFile *file=scannerContext.file;
    while(file) {
        if(file->kind==0)break;
        if(file->kind>3) { file=0;break; }
        file=(ScanFile *)file->parent;
    }
    if(!scannerContext.text)return 0;
    ScanWord first=(ScanWord)start-(ScanWord)scannerContext.text;
    ScanWord final=(ScanWord)end-(ScanWord)scannerContext.text;
    if(line<0)line=sourcetext_get_line_number(file,first);
    int originalLine=line;
    ScanWord lineStart=sourcetext_get_line_offset(file,line);
    ScanWord lineEnd=sourcetext_get_line_offset(file,(ScanWord)line+1);
    if(lineStart>first || lineStart>final) {
        line=sourcetext_get_line_number(file,first);
        originalLine=line;
        lineStart=sourcetext_get_line_offset(file,line);
        if(lineStart>first || lineStart>final)
            fn_0044ca40(1,0,scannerFilename,scannerSetupRefName,0x13e5);
    }
    if(!file && scannerContext.file) {
        const char *name=(char *)scannerContext.file->name+10;
        snprintf(prefix,80,scannerSourceLineFormat,name,line);
        head=(ScanSourceText *)lalloc(24);
        head->kind=1;head->text=prefix;head->encoding=2;head->start=0;
        head->length=scanner_string_length(prefix);head->highlighted=0;head->next=0;
        last=head;
    }
    ScanSourceText *part=(ScanSourceText *)lalloc(24);
    part->kind=1;part->text=scannerContext.text;part->encoding=scannerContext.active;
    part->start=lineStart;part->length=first-lineStart;part->highlighted=0;part->next=0;
    if(last)last->next=part;else head=part;
    last=part;
    part=(ScanSourceText *)lalloc(24);
    part->kind=1;part->text=scannerContext.text;part->encoding=scannerContext.active;
    part->start=first;part->length=final-first;part->highlighted=1;part->next=0;
    if(last)last->next=part;else head=part;
    last=part;
    part=(ScanSourceText *)lalloc(24);
    part->kind=1;part->text=scannerContext.text;part->encoding=scannerContext.active;
    part->start=final;part->length=lineEnd-final;part->highlighted=0;part->next=0;
    if(last)last->next=part;else head=part;
    out->line=line;
    if(file) {
        ScanState state={0};state.current=start;state.column=originalLine;
        ScanWord offset=(ScanWord)state.current-(ScanWord)scannerContext.text;
        memcpy(out,file->parent,260);
        out->start=offset;
        state.current=end;state.column=originalLine;
        out->length=(ScanWord)state.current-(ScanWord)scannerContext.text-out->start;
    }
    fn_0044b6c0(head,arg2,arg3,out);
    return 1;
}

extern "C" {
extern ScanWord scannerVTable00694d04[],scannerVTable00694c34[],scannerVTable00694c00[],scannerVTable00694bcc[];
extern ScanWord scannerVTable00694b98[],scannerVTable00694b64[],scannerVTable00694c9c[],scannerVTable00694c68[],scannerVTable00694cd0[];
extern ScanByte scannerGuessOption;
extern void *scannerCachedConverter;
extern int (__stdcall *scannerIsValidCodePage)(unsigned int);
extern unsigned int (__stdcall *scannerGetACP)(void);
extern void *fn_005a43e0(size_t);
extern ScanByte scanner_guess_encoding(char *,char *,ScanByte);
extern ScanByte fn_00481b10(char **,char *);
extern ScanDecoder *fn_0047f870(unsigned int,ScanByte);
extern void scanner_warning(void *,int,int,short,...);
}
static char scannerInitDecoderName[]="scanner_init_decoder";
static char scannerEncodingShiftJIS[]="SHIFT-JIS",scannerEncodingEUCJP[]="EUC-JP",scannerEncodingISO2022JP[]="ISO-2022-JP";
ScanDecoder *ScanDecoder::fn_0047fb60() { *(void **)this=scannerVTable00694c9c;return this; }
ScanDecoder *ScanDecoder::fn_0047fb70() { *(void **)this=scannerVTable00694c68;return this; }
ScanDecoder *ScanDecoder::fn_0047fb80() { *(void **)this=scannerVTable00694cd0;return this; }
static inline ScanDecoder *scanner_new_decoder(ScanWord *vtable)
{
    ScanDecoder *decoder=(ScanDecoder *)fn_005a43e0(4);
    if(decoder)*(void **)decoder=vtable;
    return decoder;
}
extern "C" void scanner_init_decoder(ScanByte encoding)
{
    char *cursor=scannerContext.state.current,*end=scannerContext.end;
    if(encoding>=13)fn_0044ca40(1,0,scannerFilename,scannerInitDecoderName,0x1072);
    if(!encoding)encoding=scanner_guess_encoding(cursor,end,scannerGuessOption);
    scannerContext.active=encoding;
    if(scannerContext.decoder!=scannerDefaultDecoder && scannerContext.decoder) {
        *(void **)scannerContext.decoder=scannerBaseDecoderVTable;
        fn_00404960(scannerContext.decoder);
    }
    ScanDecoder *decoder=0;
    switch(encoding) {
        case 2:decoder=scanner_new_decoder(scannerVTable00694d04);break;
        case 3:decoder=scanner_new_decoder(scannerVTable00694c34);break;
        case 4: {
            ScanByte little=0;
            if((ScanWord)cursor+2<(ScanWord)end) {
                if((ScanByte)cursor[0]==0xfe && (ScanByte)cursor[1]==0xff)cursor+=2;
                else if((ScanByte)cursor[0]==0xff && (ScanByte)cursor[1]==0xfe) { cursor+=2;little=1; }
                else little=cursor[0]!=0;
            }
            decoder=scanner_new_decoder(little?scannerVTable00694c00:scannerVTable00694bcc);
            break;
        }
        case 5:decoder=scanner_new_decoder(scannerVTable00694c00);break;
        case 6:decoder=scanner_new_decoder(scannerVTable00694bcc);break;
        case 7:decoder=scanner_new_decoder(fn_00481b10(&cursor,end)?scannerVTable00694b98:scannerVTable00694b64);break;
        case 8:decoder=scanner_new_decoder(scannerVTable00694b98);break;
        case 9:decoder=scanner_new_decoder(scannerVTable00694b64);break;
        case 1:decoder=fn_0047f870(scannerGetACP(),1);break;
        case 10:
            if(scannerCachedConverter) {
                decoder=(ScanDecoder *)fn_005a43e0(4);
                if(decoder)decoder=decoder->fn_0047fb80();
            } else {
                ScanDecoder *converter=fn_0047f870(51932,0);
                if(!converter)converter=fn_0047f870(932,0);
                if(!converter)scanner_warning(0,0,-1,0x28be,scannerEncodingISO2022JP);
                else {
                    scannerCachedConverter=converter;
                    decoder=(ScanDecoder *)fn_005a43e0(4);
                    if(decoder)decoder=decoder->fn_0047fb80();
                }
            }
            break;
        case 11:
            if(scannerIsValidCodePage(932))decoder=fn_0047f870(932,1);
            else if(scannerCachedConverter) {
                decoder=(ScanDecoder *)fn_005a43e0(4);
                if(decoder)decoder=decoder->fn_0047fb60();
            } else {
                ScanDecoder *converter=fn_0047f870(51932,0);
                if(!converter)scanner_warning(0,0,-1,0x28be,scannerEncodingShiftJIS);
                else {
                    scannerCachedConverter=converter;
                    decoder=(ScanDecoder *)fn_005a43e0(4);
                    if(decoder)decoder=decoder->fn_0047fb60();
                }
            }
            break;
        case 12:
            decoder=fn_0047f870(51932,0);
            if(!decoder) {
                if(scannerCachedConverter) {
                    decoder=(ScanDecoder *)fn_005a43e0(4);
                    if(decoder)decoder=decoder->fn_0047fb70();
                } else {
                    ScanDecoder *converter=fn_0047f870(932,0);
                    if(!converter)scanner_warning(0,0,-1,0x28be,scannerEncodingEUCJP);
                    else {
                        scannerCachedConverter=converter;
                        decoder=(ScanDecoder *)fn_005a43e0(4);
                        if(decoder)decoder=decoder->fn_0047fb70();
                    }
                }
            }
            break;
        default:fn_0044ca40(1,0,scannerFilename,scannerInitDecoderName,0x10ab);break;
    }
    scannerContext.decoder=decoder;
    if(!decoder)scannerContext.decoder=decoder=scanner_new_decoder(scannerVTable00694d04);
    scannerContext.callbacks[0]=decoder->callback14();
    scannerContext.callbacks[1]=decoder->callback18();
    scannerContext.callbacks[2]=decoder->callback1c();
    scannerContext.callbacks[3]=decoder->callback20();
    scannerContext.decoderFlag=decoder->mode();
    scannerContext.decoderMode=decoder->flag();
    decoder->method0c(&cursor,scannerContext.end);
    scannerContext.state.current=cursor;
}

extern "C" ScanWord fn_00484ac0(char *,char *,char **);
extern "C" void *fn_004825b0(void) { return (void *)fn_00484ac0; }
extern "C" ScanWord fn_004841f0(char *,char *,char **,ScanByte);
extern "C" void *fn_004825c0(void) { return (void *)fn_004841f0; }
extern "C" short fn_00486ed0(ScanToken *);
extern "C" void *fn_004825d0(void) { return (void *)fn_00486ed0; }
extern "C" ScanByte fn_00483370(void);
extern "C" void *fn_004825e0(void) { return (void *)fn_00483370; }
extern "C" ScanWord fn_00484a90(char *,char *,char **);
extern "C" void *fn_004826d0(void) { return (void *)fn_00484a90; }
extern "C" ScanWord fn_00483df0(char *,char *,char **,ScanByte);
extern "C" void *fn_004826e0(void) { return (void *)fn_00483df0; }
extern "C" short fn_00489270(ScanToken *);
extern "C" void *fn_004826f0(void) { return (void *)fn_00489270; }
extern "C" ScanByte fn_004831f0(void);
extern "C" void *fn_00482700(void) { return (void *)fn_004831f0; }
extern "C" ScanWord fn_00484a70(char *,char *,char **);
extern "C" void *fn_004827d0(void) { return (void *)fn_00484a70; }
extern "C" ScanWord fn_00483a30(char *,char *,char **,ScanByte);
extern "C" void *fn_004827e0(void) { return (void *)fn_00483a30; }
extern "C" short fn_0048b990(ScanToken *);
extern "C" void *fn_004827f0(void) { return (void *)fn_0048b990; }
extern "C" ScanByte fn_00483070(void);
extern "C" void *fn_00482800(void) { return (void *)fn_00483070; }
extern "C" ScanWord fn_00484a20(char *,char *,char **);
extern "C" void *fn_00482880(void) { return (void *)fn_00484a20; }
extern "C" ScanWord fn_00483670(char *,char *,char **,ScanByte);
extern "C" void *fn_00482890(void) { return (void *)fn_00483670; }
extern "C" short fn_0048dcc0(ScanToken *);
extern "C" void *fn_004828a0(void) { return (void *)fn_0048dcc0; }
extern "C" ScanByte fn_00482ef0(void);
extern "C" void *fn_004828b0(void) { return (void *)fn_00482ef0; }

static inline ScanWord scan_swap16(ScanWord value)
{
    return ((value&255)<<8)|(value>>8);
}
static inline ScanWord scan_swap32(ScanWord value)
{
    return ((value>>8)&0xff00)|(value>>24)|((value&0xff00)<<8)|(value<<24);
}
extern "C" ScanWord fn_00484af0(char *start,char *end,char **current)
{
    if(end<=start) { *current=end;return 0; }
    *current=start+1;return *(ScanByte *)start;
}
extern "C" ScanWord fn_00484ac0(char *start,char *end,char **current)
{
    if(end<=start) { *current=end;return 0; }
    *current=start+2;return *(unsigned short *)start;
}
extern "C" ScanWord fn_00484a90(char *start,char *end,char **current)
{
    if(end<=start) { *current=end;return 0; }
    *current=start+2;return scan_swap16(*(unsigned short *)start);
}
extern "C" ScanWord fn_00484a70(char *start,char *end,char **current)
{
    if(end<=start) { *current=end;return 0; }
    *current=start+4;return *(ScanWord *)start;
}
extern "C" ScanWord fn_00484a20(char *start,char *end,char **current)
{
    if(end<=start) { *current=end;return 0; }
    *current=start+4;return scan_swap32(*(ScanWord *)start);
}
extern "C" ScanWord __stdcall fn_0047eca0(char *start,char *end,char **current)
{
    ScanWord value=0;
    if(start<end) { value=*(ScanByte *)start;*current=start+1; }
    return value;
}
template <bool swapped> static inline ScanWord scanner_decode16(char *start,char *end,char **current)
{
    ScanWord value=0;
    if(end<start+2) {
        if(end!=start) { value=0xffff;start=end; }
    } else {
        value=*(unsigned short *)start;
        if(swapped)value=scan_swap16(value);
        if(value>=0xd800 && value<=0xdbff && start+4<=end) {
            ScanWord second=*(unsigned short *)(start+2);
            if(swapped)second=scan_swap16(second);
            if(second>=0xdc00 && second<=0xdfff) {
                start+=2;value=(value*0x400+second)-0x35fdc00;
            }
        }
        start+=2;
    }
    *current=start;return value;
}
extern "C" ScanWord __stdcall fn_004825f0(char *start,char *end,char **current)
{
    return scanner_decode16<false>(start,end,current);
}
extern "C" ScanWord __stdcall fn_00482710(char *start,char *end,char **current)
{
    return scanner_decode16<true>(start,end,current);
}
template <bool swapped> static inline ScanWord scanner_decode32(char *start,char *end,char **current)
{
    ScanWord value=0;
    if(end<start+4) {
        if(end!=start) { value=0xffff;start=end; }
    } else {
        value=*(ScanWord *)start;
        if(swapped)value=scan_swap32(value);
        start+=4;
    }
    *current=start;return value;
}
extern "C" ScanWord __stdcall fn_00482810(char *start,char *end,char **current)
{
    return scanner_decode32<false>(start,end,current);
}
extern "C" ScanWord __stdcall fn_004828c0(char *start,char *end,char **current)
{
    return scanner_decode32<true>(start,end,current);
}
extern "C" void __stdcall fn_004827a0(char **current,char *end)
{
    fn_00481b10(current,end);
}
extern "C" void __stdcall fn_00482850(char **current,char *end)
{
    fn_00481b10(current,end);
}

extern "C" void fn_004816a0(char *current)
{
    if(scannerContext.state.line<current) {
        scannerContext.state.line=current;++scannerContext.state.column;
        ScanFile *file=scannerContext.file;
        ScanWord count=file->lineTable?*(ScanWord *)((char *)file->lineTable+4)/4:0;
        if(count<scannerContext.state.column)
            sourcetext_define_line(file,scannerContext.state.column,current-scannerContext.text);
    }
    scannerContext.state.whitespace=1;scannerContext.state.flags=1;
    scannerContext.state.current=current;
}
static inline ScanWord scanner_utf8(char *start,char *end,char **current,ScanByte warnings)
{
    ScanWord value=0,minimum=0;
    char *cursor=start;
    if(start<end) {
        value=*(ScanByte *)cursor++;
        if(value>=0x80) {
            unsigned int count;
            if((value&0xe0)==0xc0 && start+1<end) { count=1;minimum=0x80;value&=0x1f; }
            else if((value&0xf0)==0xe0 && start+2<end) { count=2;minimum=0x800;value&=0xf; }
            else if((value&0xf8)==0xf0 && start+3<end) { count=3;minimum=0x10000;value&=7; }
            else if((value&0xfc)==0xf8 && start+4<end) { count=4;minimum=0x200000;value&=3; }
            else if((value&0xfe)==0xfc && start+5<end) { count=5;minimum=0x4000000;value&=1; }
            else goto invalid;
            while(count--) {
                ScanByte next=*(ScanByte *)cursor++;
                if((next&0xc0)!=0x80)goto invalid;
                value=(value<<6)|(next&0x3f);
            }
            if(value<minimum || (minimum==0x800 && value>=0xd800 && value<=0xdfff)) {
                *current=cursor;
                if(warnings && scannerContext.finalWord<(ScanWord)cursor) {
                    scannerContext.finalWord=(ScanWord)cursor;
                    scanner_warning(start,(int)cursor,-1,0x28d5);
                }
                return 0xffff;
            }
        }
    }
    *current=cursor;return value;
invalid:
    *current=start+1;value=*(ScanByte *)start;
    if(warnings && scannerContext.finalWord<(ScanWord)cursor) {
        scannerContext.finalWord=(ScanWord)cursor;
        scanner_warning(start,(int)cursor,-1,0x28d5);
    }
    return value;
}
extern "C" ScanWord fn_004812f0(char *start,char *end,char **current,ScanByte warnings)
{
    return scanner_utf8(start,end,current,warnings);
}
extern "C" ScanWord __stdcall fn_004821a0(char *start,char *end,char **current)
{
    return scanner_utf8(start,end,current,1);
}
extern "C" ScanByte fn_00481b10(char **current,char *end)
{
    ScanByte *start=(ScanByte *)*current;
    if(end<=(char *)start+4)return 0;
    if(start[0]==0 && start[1]==0 && start[2]==0xfe && start[3]==0xff) {
        *current+=4;return 0;
    }
    if(start[0]==0xff && start[1]==0xfe && start[2]==0 && start[3]==0) {
        *current+=4;return 1;
    }
    if(!start[0] && !start[1] && !start[2])return 0;
    return 1;
}
extern "C" ScanByte possibly_unicode(char **current,char *end,ScanByte *encoding)
{
    ScanByte *start=(ScanByte *)*current;
    int counts[6]={0},zeros=0,length=0;
    if((char *)start+4<=end) {
        if(start[0]==0 && start[1]==0 && start[2]==0xfe && start[3]==0xff) {
            *current+=4;*encoding=9;return 1;
        }
        if(start[0]==0xff && start[1]==0xfe && start[2]==0 && start[3]==0) {
            *current+=4;*encoding=8;return 1;
        }
    }
    if((char *)start+2<=end) {
        if(start[0]==0xfe && start[1]==0xff) { *current+=2;*encoding=6;return 1; }
        if(start[0]==0xff && start[1]==0xfe) { *current+=2;*encoding=5;return 1; }
    }
    for(ScanByte *cursor=start;(char *)cursor<end && length<256;++cursor,++length) {
        if(!*cursor) {
            ScanWord offset=cursor-start;++zeros;
            ++counts[offset&3];++counts[(offset&1)+4];
        }
    }
    if(length<2 || zeros<2)return 0;
    /* Native threshold at0x694b18 is0.5. */
    if(0.5<(double)zeros/(double)length)*encoding=counts[3]<counts[0]?9:8;
    else *encoding=counts[5]<counts[4]?6:5;
    return 1;
}
extern "C" ScanByte scannerCodePageFlags[256];
extern "C" ScanByte scanner_guess_encoding(char *start,char *end,ScanByte guess)
{
    ScanByte encoding;
    if(possibly_unicode(&start,end,&encoding))return encoding;
    if(start+3<end && (ScanByte)start[0]==0xef && (ScanByte)start[1]==0xbb && (ScanByte)start[2]==0xbf)
        return 3;
    if(!guess)return 2;
    int utf8=0,sjis=0,euc=0,invalid=0;
    while(start<end) {
        char *next=start+1;
        ScanByte first=*(ScanByte *)start;
        if(next<end) {
            ScanByte second=(ScanByte)start[1],flags=scannerCodePageFlags[first];
            if((flags&1) && (scannerCodePageFlags[second]&2)) { euc+=2;if(euc>7)return 12;next=start+2; }
            if((flags&4) && (scannerCodePageFlags[second]&8)) { sjis+=2;if(sjis>7)return 11;next=start+2; }
            if(first==27 && second=='$' && start+2<end) {
                if(start[2]=='@' || start[2]=='B')return 10;
                next=start+3;
            }
        }
        if(first>127) {
            next=start;
            ScanWord value=fn_004812f0(start,end,&next,0);
            if(value==0xffff || next<=start+1) {
                ++invalid;
                if(invalid>7 && !sjis && !euc && !utf8 && guess)return 1;
                next=start+1;
            } else {
                utf8+=next-start;if(utf8>7)return 3;
            }
        }
        start=next;
    }
    if((utf8|sjis|euc)<invalid)return 1;
    if((sjis|euc)<utf8)return 3;
    if(sjis<euc)return 12;
    if(!sjis)return 2;
    return 11;
}

extern "C" signed char scannerHexDigits[256];
extern "C" ScanByte scannerStrictCharacters;
template <int width,bool swapped> static inline ScanWord scanner_raw_unit(char *start,char *end,char **current)
{
    if(end<=start) { *current=end;return 0; }
    *current=start+width;
    if(width==1)return *(ScanByte *)start;
    if(width==2) {
        ScanWord value=*(unsigned short *)start;
        return swapped?scan_swap16(value):value;
    }
    ScanWord value=*(ScanWord *)start;
    return swapped?scan_swap32(value):value;
}
extern "C" ScanWord fn_00483670(char *start,char *end,char **current,ScanByte literal)
{
    ScanWord value;
    char *look,*third;
    for(;;) {
        value=fn_00484a20(start,end,&start);
again:
        if(value==13 || value==10) {
            if(value==13 && fn_00484a20(start,end,&look)==10)start=look;
            fn_004816a0(start);*current=start;return 10;
        }
        if(value!='\\') {
            if(value=='?' && scannerOptionQuestion && fn_00484a20(start,end,&look)=='?') {
                ScanWord last=fn_00484a20(look,end,&third);
                switch(last) {
                    case '!':value='|';start=third;break;
                    case '\'':value='^';start=third;break;
                    case '(':value='[';start=third;break;
                    case ')':value=']';start=third;break;
                    case '-':value='~';start=third;break;
                    case '/':value='\\';start=third;goto again;
                    case '<':value='{';start=third;break;
                    case '=':value='#';start=third;break;
                    case '>':value='}';start=third;break;
                }
            }
            *current=start;return value;
        }
        ScanWord next=fn_00484a20(start,end,&look);
        if(next==13 || next==10) {
            start=look;
            if(next==13 && fn_00484a20(start,end,&look)==10)start=look;
            fn_004816a0(start);continue;
        }
        if(!literal && (next=='u' || next=='U')) {
            int count=next=='u'?4:8;
            char *saved=start;start=look;value=0;
            while(count) {
                ScanWord digit=fn_00484a20(start,end,&start);
                if(scannerHexDigits[digit]<0)break;
                value=(value<<4)|(int)scannerHexDigits[digit];--count;
            }
            if(count==0) {
                if(value<0x10000 && (scannerUnicodeFlags[value]&0x80) && scannerStrictCharacters)
                    scanner_error(saved-4,(int)(start-4),scannerContext.state.column,0x28ce,value);
            } else {
                scanner_error(saved-4,(int)(start-4),scannerContext.state.column,0x28d4);
                start=saved;value='\\';
            }
            *current=start;return value;
        }
        *current=start;return '\\';
    }
}
extern "C" ScanWord fn_00483a30(char *start,char *end,char **current,ScanByte literal)
{
    ScanWord value;
    char *look,*third;
    for(;;) {
        value=fn_00484a70(start,end,&start);
again:
        if(value==13 || value==10) {
            if(value==13 && fn_00484a70(start,end,&look)==10)start=look;
            fn_004816a0(start);*current=start;return 10;
        }
        if(value!='\\') {
            if(value=='?' && scannerOptionQuestion && fn_00484a70(start,end,&look)=='?') {
                ScanWord last=fn_00484a70(look,end,&third);
                switch(last) {
                    case '!':value='|';start=third;break;
                    case '\'':value='^';start=third;break;
                    case '(':value='[';start=third;break;
                    case ')':value=']';start=third;break;
                    case '-':value='~';start=third;break;
                    case '/':value='\\';start=third;goto again;
                    case '<':value='{';start=third;break;
                    case '=':value='#';start=third;break;
                    case '>':value='}';start=third;break;
                }
            }
            *current=start;return value;
        }
        ScanWord next=fn_00484a70(start,end,&look);
        if(next==13 || next==10) {
            start=look;
            if(next==13 && fn_00484a70(start,end,&look)==10)start=look;
            fn_004816a0(start);continue;
        }
        if(!literal && (next=='u' || next=='U')) {
            int count=next=='u'?4:8;
            char *saved=start;start=look;value=0;
            while(count) {
                ScanWord digit=fn_00484a70(start,end,&start);
                if(scannerHexDigits[digit]<0)break;
                value=(value<<4)|(int)scannerHexDigits[digit];--count;
            }
            if(count==0) {
                if(value<0x10000 && (scannerUnicodeFlags[value]&0x80) && scannerStrictCharacters)
                    scanner_error(saved-4,(int)(start-4),scannerContext.state.column,0x28ce,value);
            } else {
                scanner_error(saved-4,(int)(start-4),scannerContext.state.column,0x28d4);
                start=saved;value='\\';
            }
            *current=start;return value;
        }
        *current=start;return '\\';
    }
}
extern "C" ScanWord fn_00483df0(char *start,char *end,char **current,ScanByte literal)
{
    ScanWord value;
    char *look,*third;
    for(;;) {
        value=fn_00484a90(start,end,&start);
again:
        if(value==13 || value==10) {
            if(value==13 && fn_00484a90(start,end,&look)==10)start=look;
            fn_004816a0(start);*current=start;return 10;
        }
        if(value!='\\') {
            if(value=='?' && scannerOptionQuestion && fn_00484a90(start,end,&look)=='?') {
                ScanWord last=fn_00484a90(look,end,&third);
                switch(last) {
                    case '!':value='|';start=third;break;
                    case '\'':value='^';start=third;break;
                    case '(':value='[';start=third;break;
                    case ')':value=']';start=third;break;
                    case '-':value='~';start=third;break;
                    case '/':value='\\';start=third;goto again;
                    case '<':value='{';start=third;break;
                    case '=':value='#';start=third;break;
                    case '>':value='}';start=third;break;
                }
            }
            *current=start;return value;
        }
        ScanWord next=fn_00484a90(start,end,&look);
        if(next==13 || next==10) {
            start=look;
            if(next==13 && fn_00484a90(start,end,&look)==10)start=look;
            fn_004816a0(start);continue;
        }
        if(!literal && (next=='u' || next=='U')) {
            int count=next=='u'?4:8;
            char *saved=start;start=look;value=0;
            while(count) {
                ScanWord digit=fn_00484a90(start,end,&start);
                if(scannerHexDigits[digit]<0)break;
                value=(value<<4)|(int)scannerHexDigits[digit];--count;
            }
            if(count==0) {
                if(value<0x10000 && (scannerUnicodeFlags[value]&0x80) && scannerStrictCharacters)
                    scanner_error(saved-2,(int)(start-2),scannerContext.state.column,0x28ce,value);
            } else {
                scanner_error(saved-2,(int)(start-2),scannerContext.state.column,0x28d4);
                start=saved;value='\\';
            }
            *current=start;return value;
        }
        *current=start;return '\\';
    }
}
extern "C" ScanWord fn_004841f0(char *start,char *end,char **current,ScanByte literal)
{
    ScanWord value;
    char *look,*third;
    for(;;) {
        value=fn_00484ac0(start,end,&start);
again:
        if(value==13 || value==10) {
            if(value==13 && fn_00484ac0(start,end,&look)==10)start=look;
            fn_004816a0(start);*current=start;return 10;
        }
        if(value!='\\') {
            if(value=='?' && scannerOptionQuestion && fn_00484ac0(start,end,&look)=='?') {
                ScanWord last=fn_00484ac0(look,end,&third);
                switch(last) {
                    case '!':value='|';start=third;break;
                    case '\'':value='^';start=third;break;
                    case '(':value='[';start=third;break;
                    case ')':value=']';start=third;break;
                    case '-':value='~';start=third;break;
                    case '/':value='\\';start=third;goto again;
                    case '<':value='{';start=third;break;
                    case '=':value='#';start=third;break;
                    case '>':value='}';start=third;break;
                }
            }
            *current=start;return value;
        }
        ScanWord next=fn_00484ac0(start,end,&look);
        if(next==13 || next==10) {
            start=look;
            if(next==13 && fn_00484ac0(start,end,&look)==10)start=look;
            fn_004816a0(start);continue;
        }
        if(!literal && (next=='u' || next=='U')) {
            int count=next=='u'?4:8;
            char *saved=start;start=look;value=0;
            while(count) {
                ScanWord digit=fn_00484ac0(start,end,&start);
                if(scannerHexDigits[digit]<0)break;
                value=(value<<4)|(int)scannerHexDigits[digit];--count;
            }
            if(count==0) {
                if(value<0x10000 && (scannerUnicodeFlags[value]&0x80) && scannerStrictCharacters)
                    scanner_error(saved-2,(int)(start-2),scannerContext.state.column,0x28ce,value);
            } else {
                scanner_error(saved-2,(int)(start-2),scannerContext.state.column,0x28d4);
                start=saved;value='\\';
            }
            *current=start;return value;
        }
        *current=start;return '\\';
    }
}
extern "C" ScanWord fn_004845f0(char *start,char *end,char **current,ScanByte literal)
{
    ScanWord value;
    char *look,*third;
    for(;;) {
        value=fn_00484af0(start,end,&start);
again:
        if(value==13 || value==10) {
            if(value==13 && fn_00484af0(start,end,&look)==10)start=look;
            fn_004816a0(start);*current=start;return 10;
        }
        if(value!='\\') {
            if(value=='?' && scannerOptionQuestion && fn_00484af0(start,end,&look)=='?') {
                ScanWord last=fn_00484af0(look,end,&third);
                switch(last) {
                    case '!':value='|';start=third;break;
                    case '\'':value='^';start=third;break;
                    case '(':value='[';start=third;break;
                    case ')':value=']';start=third;break;
                    case '-':value='~';start=third;break;
                    case '/':value='\\';start=third;goto again;
                    case '<':value='{';start=third;break;
                    case '=':value='#';start=third;break;
                    case '>':value='}';start=third;break;
                }
            }
            *current=start;return value;
        }
        ScanWord next=fn_00484af0(start,end,&look);
        if(next==13 || next==10) {
            start=look;
            if(next==13 && fn_00484af0(start,end,&look)==10)start=look;
            fn_004816a0(start);continue;
        }
        if(!literal && (next=='u' || next=='U')) {
            int count=next=='u'?4:8;
            char *saved=start;start=look;value=0;
            while(count) {
                ScanWord digit=fn_00484af0(start,end,&start);
                if(scannerHexDigits[digit]<0)break;
                value=(value<<4)|(int)scannerHexDigits[digit];--count;
            }
            if(count==0) {
                if(value<0x10000 && (scannerUnicodeFlags[value]&0x80) && scannerStrictCharacters)
                    scanner_error(saved-1,(int)(start-1),scannerContext.state.column,0x28ce,value);
            } else {
                scanner_error(saved-1,(int)(start-1),scannerContext.state.column,0x28d4);
                start=saved;value='\\';
            }
            *current=start;return value;
        }
        *current=start;return '\\';
    }
}

extern "C" short fn_004923e0(ScanToken *),fn_00494070(ScanToken *),fn_00495aa0(ScanToken *),fn_00497560(ScanToken *);
extern "C" ScanByte fn_004834f0(void)
{
    char *end=scannerContext.end,*cursor=scannerContext.state.current,*next,*look;
    ScanToken token;
    for(;;) {
        ScanWord value=fn_004845f0(cursor,end,&next,0);
        if(value==10) { scannerContext.state.current=cursor;return 1; }
        if(value==0) { scannerContext.state.current=cursor;return 0; }
        if(value=='"' || value=='\'') {
            scannerContext.state.current=cursor;
            short kind=(short)fn_00490990(&token);
            cursor=scannerContext.state.current;
            if(!kind)cursor=next;
            continue;
        }
        if(value=='/' && fn_004845f0(next,end,&look,0)=='/') {
            cursor=look;
            for(;;) {
                value=fn_004845f0(cursor,end,&next,1);
                if(value==10 || value==0)break;
                cursor=next;
            }
            continue;
        }
        cursor=next;
        if(value=='/' && fn_004845f0(next,end,&look,0)=='*') {
            char *commentStart=look;
            cursor=look;
            for(;;) {
                value=fn_004845f0(cursor,end,&next,1);
                if(value=='*' && fn_004845f0(next,end,&look,0)=='/') {
                    cursor=look;break;
                }
                cursor=next;
                if(value==0) {
                    scanner_error(commentStart,(int)(commentStart+2*1),scannerContext.state.column,0x28bf);
                    return 0;
                }
            }
        }
    }
}
extern "C" ScanByte fn_00483370(void)
{
    char *end=scannerContext.end,*cursor=scannerContext.state.current,*next,*look;
    ScanToken token;
    for(;;) {
        ScanWord value=fn_004841f0(cursor,end,&next,0);
        if(value==10) { scannerContext.state.current=cursor;return 1; }
        if(value==0) { scannerContext.state.current=cursor;return 0; }
        if(value=='"' || value=='\'') {
            scannerContext.state.current=cursor;
            short kind=(short)fn_00497560(&token);
            cursor=scannerContext.state.current;
            if(!kind)cursor=next;
            continue;
        }
        if(value=='/' && fn_004841f0(next,end,&look,0)=='/') {
            cursor=look;
            for(;;) {
                value=fn_004841f0(cursor,end,&next,1);
                if(value==10 || value==0)break;
                cursor=next;
            }
            continue;
        }
        cursor=next;
        if(value=='/' && fn_004841f0(next,end,&look,0)=='*') {
            char *commentStart=look;
            cursor=look;
            for(;;) {
                value=fn_004841f0(cursor,end,&next,1);
                if(value=='*' && fn_004841f0(next,end,&look,0)=='/') {
                    cursor=look;break;
                }
                cursor=next;
                if(value==0) {
                    scanner_error(commentStart,(int)(commentStart+2*2),scannerContext.state.column,0x28bf);
                    return 0;
                }
            }
        }
    }
}
extern "C" ScanByte fn_004831f0(void)
{
    char *end=scannerContext.end,*cursor=scannerContext.state.current,*next,*look;
    ScanToken token;
    for(;;) {
        ScanWord value=fn_00483df0(cursor,end,&next,0);
        if(value==10) { scannerContext.state.current=cursor;return 1; }
        if(value==0) { scannerContext.state.current=cursor;return 0; }
        if(value=='"' || value=='\'') {
            scannerContext.state.current=cursor;
            short kind=(short)fn_00495aa0(&token);
            cursor=scannerContext.state.current;
            if(!kind)cursor=next;
            continue;
        }
        if(value=='/' && fn_00483df0(next,end,&look,0)=='/') {
            cursor=look;
            for(;;) {
                value=fn_00483df0(cursor,end,&next,1);
                if(value==10 || value==0)break;
                cursor=next;
            }
            continue;
        }
        cursor=next;
        if(value=='/' && fn_00483df0(next,end,&look,0)=='*') {
            char *commentStart=look;
            cursor=look;
            for(;;) {
                value=fn_00483df0(cursor,end,&next,1);
                if(value=='*' && fn_00483df0(next,end,&look,0)=='/') {
                    cursor=look;break;
                }
                cursor=next;
                if(value==0) {
                    scanner_error(commentStart,(int)(commentStart+2*2),scannerContext.state.column,0x28bf);
                    return 0;
                }
            }
        }
    }
}
extern "C" ScanByte fn_00483070(void)
{
    char *end=scannerContext.end,*cursor=scannerContext.state.current,*next,*look;
    ScanToken token;
    for(;;) {
        ScanWord value=fn_00483a30(cursor,end,&next,0);
        if(value==10) { scannerContext.state.current=cursor;return 1; }
        if(value==0) { scannerContext.state.current=cursor;return 0; }
        if(value=='"' || value=='\'') {
            scannerContext.state.current=cursor;
            short kind=(short)fn_00494070(&token);
            cursor=scannerContext.state.current;
            if(!kind)cursor=next;
            continue;
        }
        if(value=='/' && fn_00483a30(next,end,&look,0)=='/') {
            cursor=look;
            for(;;) {
                value=fn_00483a30(cursor,end,&next,1);
                if(value==10 || value==0)break;
                cursor=next;
            }
            continue;
        }
        cursor=next;
        if(value=='/' && fn_00483a30(next,end,&look,0)=='*') {
            char *commentStart=look;
            cursor=look;
            for(;;) {
                value=fn_00483a30(cursor,end,&next,1);
                if(value=='*' && fn_00483a30(next,end,&look,0)=='/') {
                    cursor=look;break;
                }
                cursor=next;
                if(value==0) {
                    scanner_error(commentStart,(int)(commentStart+2*4),scannerContext.state.column,0x28bf);
                    return 0;
                }
            }
        }
    }
}
extern "C" ScanByte fn_00482ef0(void)
{
    char *end=scannerContext.end,*cursor=scannerContext.state.current,*next,*look;
    ScanToken token;
    for(;;) {
        ScanWord value=fn_00483670(cursor,end,&next,0);
        if(value==10) { scannerContext.state.current=cursor;return 1; }
        if(value==0) { scannerContext.state.current=cursor;return 0; }
        if(value=='"' || value=='\'') {
            scannerContext.state.current=cursor;
            short kind=(short)fn_004923e0(&token);
            cursor=scannerContext.state.current;
            if(!kind)cursor=next;
            continue;
        }
        if(value=='/' && fn_00483670(next,end,&look,0)=='/') {
            cursor=look;
            for(;;) {
                value=fn_00483670(cursor,end,&next,1);
                if(value==10 || value==0)break;
                cursor=next;
            }
            continue;
        }
        cursor=next;
        if(value=='/' && fn_00483670(next,end,&look,0)=='*') {
            char *commentStart=look;
            cursor=look;
            for(;;) {
                value=fn_00483670(cursor,end,&next,1);
                if(value=='*' && fn_00483670(next,end,&look,0)=='/') {
                    cursor=look;break;
                }
                cursor=next;
                if(value==0) {
                    scanner_error(commentStart,(int)(commentStart+2*4),scannerContext.state.column,0x28bf);
                    return 0;
                }
            }
        }
    }
}

extern "C" void *scannerDiagnosticContext;
extern "C" void fn_004592f0(void *,int,ScanSourceRef *,char *,int,void *);
extern "C" void fn_004599e0(void *);
extern "C" void scanner_error(void *start,int end,int line,short diagnostic,...)
{
    ScanSourceRef ref,*source=&ref;
    char text[128];
    if(!scannerContext.suppress) {
        if(!scanner_setupref(&ref,(int)text,128,(char *)start,(char *)end,line))source=0;
        fn_004592f0(scannerDiagnosticContext,2,source,text,(int)diagnostic,(char *)&diagnostic+4);
    }
    if(diagnostic==0x28bb)fn_004599e0(scannerDiagnosticContext);
}
extern "C" void scanner_warning(void *start,int end,int line,short diagnostic,...)
{
    ScanSourceRef ref,*source=&ref;
    char text[128];
    if(!scannerContext.suppress) {
        if(!scanner_setupref(&ref,(int)text,128,(char *)start,(char *)end,line))source=0;
        fn_004592f0(scannerDiagnosticContext,1,source,text,(int)diagnostic,(char *)&diagnostic+4);
    }
}
template <int unused> static inline void scanner_skip_utf16_marker(char **current,char *end)
{
    ScanByte *start=(ScanByte *)*current;
    if((char *)start+2<end && ((start[0]==0xff && start[1]==0xfe) || (start[0]==0xfe && start[1]==0xff)))
        *current+=2;
}
extern "C" void __stdcall fn_00482540(char **current,char *end) { scanner_skip_utf16_marker<0>(current,end); }
extern "C" void __stdcall fn_00482660(char **current,char *end) { scanner_skip_utf16_marker<1>(current,end); }
extern "C" int sprintf(char *,const char *,...);
extern "C" void fn_0055ec00(void *,char *,int);
static char scannerNumberFormat[]="%ld",scannerHexFormat[]="0x%.8X";
extern "C" void fn_00499060(char *out,int capacity,const char *format,ScanWord *arguments)
{
    char temporary[2048];
    for(;;) {
        ScanByte value=(ScanByte)*format++;
        if(!value) { *out=0;return; }
        if(value=='%') {
            value=(ScanByte)*format++;
            const char *text=0;
            switch(value) {
                case 'c':text=(char *)*arguments++;break;
                case 'h': {
                    ScanWord number=*arguments++;
                    if(capacity>11) { int count=sprintf(out,scannerHexFormat,number);out+=count;capacity-=count; }
                    continue;
                }
                case 'n': {
                    ScanWord number=*arguments++;
                    if(capacity>10) { int count=sprintf(out,scannerNumberFormat,number);out+=count;capacity-=count; }
                    continue;
                }
                case 'p': {
                    const ScanByte *text=(const ScanByte *)*arguments++;
                    unsigned int count=*text++;
                    while(count && capacity>1) { *out++=*text++;--count;--capacity; }
                    continue;
                }
                case 's':fn_0055ec00((void *)*arguments++,temporary,2048);text=temporary;break;
            }
            if(text) {
                while(*text && capacity>1) { *out++=*text++;--capacity; }
                continue;
            }
        }
        if(capacity>1) { *out++=(char)value;--capacity; }
    }
}

extern "C" unsigned short scannerSingleByteDecodeTable[256];
extern "C" ScanWord scannerCurrentCodePage;
extern "C" int (__stdcall *scannerMultiByteToWideChar)(unsigned int,ScanWord,const char *,int,unsigned short *,int);
extern "C" ScanWord (__stdcall *scannerGetLastError)(void);
extern "C" ScanWord scannerVTable00694b28[];
class ScanWindowsDecoder:public ScanDecoder {
public:
    unsigned int codePage;
    void fn_0047fa10();
    void fn_0047fa30();
    short fn_00482a50(char *,char *,char **);
    unsigned short fn_00482920(unsigned short);
};
void ScanWindowsDecoder::fn_0047fa10()
{
    if(codePage!=scannerCurrentCodePage) { scannerCurrentCodePage=codePage;method30(); }
}
void ScanWindowsDecoder::fn_0047fa30()
{
    unsigned int ch;
    for(ch=0;ch<128;++ch)scannerSingleByteDecodeTable[ch]=(unsigned short)ch;
    for(ch=128;ch<256;++ch)scannerSingleByteDecodeTable[ch]=0xffff;
    for(ch=128;ch<256;++ch) {
        char bytes[2];bytes[0]=(char)ch;bytes[1]=0;
        char *cursor=bytes;
        int value=decode(bytes,bytes+1,&cursor);
        if(cursor==bytes+1 && value!=0xffff)scannerSingleByteDecodeTable[ch]=(unsigned short)value;
    }
}
short ScanWindowsDecoder::fn_00482a50(char *start,char *end,char **current)
{
    short value=0;
    unsigned short output[2];
    if(start<end) {
        value=scannerSingleByteDecodeTable[*(ScanByte *)start];
        if(value==-1) {
            int maximum=end-start;if(maximum>8)maximum=8;
            for(int length=1;length<=maximum;++length) {
                int count=scannerMultiByteToWideChar(codePage,0,start,length,output,1);
                if(count==1 && output[0]) { *current=start+length;return output[0]; }
                if(count>=2)break;
            }
            value=-1;
        }
        ++start;
    }
    *current=start;return value;
}
unsigned short ScanWindowsDecoder::fn_00482920(unsigned short value)
{
    ScanByte high=(ScanByte)(value>>8),low=(ScanByte)value;
    char bytes[3];unsigned short output[2];
    if(codePage==51932) { bytes[0]=(char)(high-128);bytes[1]=(char)(low-128);bytes[2]=0; }
    else {
        if(codePage!=932)return 0xffff;
        if(high>0x20 && high<0x61)bytes[0]=(char)(((value>>8)+1>>1)+0x70);
        else bytes[0]=(char)(((value>>8)+1>>1)-0x50);
        if((high&1)==0)bytes[1]=(char)(low+0x7e);
        else bytes[1]=(char)((low>0x5f)+low+0x1f);
    }
    if(scannerMultiByteToWideChar(codePage,0,bytes,2,output,1)!=1) {
        scannerGetLastError();return 0xffff;
    }
    return output[0];
}
extern "C" ScanWord __stdcall fn_00482090(char *start,char *end,char **current)
{
    ScanWord value=0;
    if(start<end) {
        value=*(ScanByte *)start;
        if((scannerCodePageFlags[value]&1) && start+1<end) {
            ScanByte next=(ScanByte)start[1];
            if(scannerCodePageFlags[next]&2) {
                value=scannerCachedConverter?
                    ((ScanDecoder *)scannerCachedConverter)->method2c(((value-128)*256|(ScanWord)next-128)&0xffff):0xffff;
                *current=start+2;return value;
            }
            value=0xffff;
        } else if((scannerCodePageFlags[value]&16) && start+1<end) {
            ScanByte next=(ScanByte)start[1];
            if(scannerCodePageFlags[next]&32) { *current=start+2;return (ScanWord)next+0xfec0; }
            value=0xffff;
        }
        ++start;
    }
    *current=start;return value;
}
ScanWord ScanDecoder::fn_00481eb0(char *start,char *end,char **current)
{
    ScanWord value=0;
    while(start<end) {
        method08(&start,end);
        value=*(ScanByte *)start;
        if(value==13 || value==10)scannerContext.state.lineStart=0;
        if(scannerCodePageFlags[value]&32) { *current=start+1;return value+0xfec0; }
        if(scannerContext.state.lineStart!=3 || end<=start+1)break;
        ScanByte next=(ScanByte)start[1];
        if(next!=13 && next!=10) {
            value=scannerCachedConverter?
                ((ScanDecoder *)scannerCachedConverter)->method2c((value<<8)|next):0xffff;
            *current=start+2;return value;
        }
        scannerContext.state.lineStart=0;
    }
    *current=start+1;return value;
}

static char scannerCodePageFormat[]="codepage %d";
extern "C" ScanDecoder *fn_0047f870(unsigned int codePage,ScanByte warnings)
{
    if(codePage==1200)return scanner_new_decoder(scannerVTable00694c00);
    if(codePage==1201)return scanner_new_decoder(scannerVTable00694bcc);
    if(codePage==50220) {
        if(!scannerCachedConverter) {
            ScanDecoder *converter=fn_0047f870(51932,0);
            if(!converter)converter=fn_0047f870(932,0);
            if(!converter) { scanner_warning(0,0,-1,0x28be,scannerEncodingISO2022JP);return 0; }
            scannerCachedConverter=converter;
        }
        ScanDecoder *decoder=(ScanDecoder *)fn_005a43e0(4);
        if(decoder)decoder=decoder->fn_0047fb80();
        return decoder;
    }
    if(!scannerIsValidCodePage(codePage)) {
        if(warnings) { char text[32];snprintf(text,32,scannerCodePageFormat,codePage);scanner_warning(0,0,-1,0x28be,text); }
        return 0;
    }
    ScanWindowsDecoder *decoder=(ScanWindowsDecoder *)fn_005a43e0(8);
    if(decoder) { *(void **)decoder=scannerVTable00694b28;decoder->codePage=codePage;decoder->reset(); }
    return decoder;
}
#pragma pack(push,2)
struct ScanEncodingName { const char *name;ScanByte encoding,padding; };
#pragma pack(pop)
extern "C" ScanEncodingName scannerEncodingNames[];
extern "C" ScanByte fn_004819d0(void);
extern "C" unsigned int fn_00481710(const char *,const char **);
extern "C" int fn_0046d9f0(const char *,const char *);
extern "C" int scanner_set_charset(const char *name)
{
    if(!name) { scanner_init_decoder(scannerContext.file?((ScanByte *)scannerContext.file)[9]:0);return 1; }
    if(!strcmp(name,"unknown")) { scanner_init_decoder(0);return 1; }
    if(!strcmp(name,"system")) { scanner_init_decoder(1);return 1; }
    for(ScanEncodingName *entry=scannerEncodingNames;entry->name;++entry) {
        if(!fn_0046d9f0(name,entry->name)) { scanner_init_decoder(entry->encoding);return 1; }
    }
    ScanDecoder *decoder=0;
    if(fn_004819d0()) {
        unsigned int codePage=fn_00481710(name,0);
        if(codePage)decoder=fn_0047f870(codePage,0);
    }
    if(!decoder)return 0;
    if(scannerContext.decoder!=decoder && scannerContext.decoder!=scannerDefaultDecoder && scannerContext.decoder) {
        *(void **)scannerContext.decoder=scannerBaseDecoderVTable;fn_00404960(scannerContext.decoder);
    }
    scannerContext.decoder=decoder;
    scannerContext.callbacks[0]=decoder->callback14();scannerContext.callbacks[1]=decoder->callback18();
    scannerContext.callbacks[2]=decoder->callback1c();scannerContext.callbacks[3]=decoder->callback20();
    scannerContext.decoderFlag=decoder->mode();scannerContext.decoderMode=decoder->flag();
    decoder->method0c(&scannerContext.state.current,scannerContext.end);
    return 1;
}

class ScanBuffer {
public:
    char *text;
    int capacity,length;
    ScanByte embedded[256];
    void *allocation;
    int allocationCapacity;
    typedef void (ScanBuffer::*Grow)(int);
    Grow grow;
    void request(int value) { (this->*grow)(value); }
    ScanBuffer() {
        allocation=0;allocationCapacity=0;text=(char *)embedded;
        capacity=255;length=0;grow=&ScanBuffer::fn_00481da0;
    }
    ~ScanBuffer();
    void fn_0047ec00(const char *,int);
    void fn_0047ec60(ScanByte);
    void fn_0047ec80(int);
    void fn_00481da0(int);
};
typedef char VerifyScanGrow[(sizeof(ScanBuffer::Grow)==12)?1:-1];
typedef char VerifyScanBuffer[(sizeof(ScanBuffer)==288)?1:-1];
void ScanBuffer::fn_0047ec00(const char *input,int count)
{
    if(capacity<=length+count)(this->*grow)(length+count);
    while(count--)text[length++]=*input++;
}
void ScanBuffer::fn_0047ec60(ScanByte value)
{
    text[length++]=(char)value;
}
void ScanBuffer::fn_0047ec80(int count)
{
    if(capacity<=length+count)(this->*grow)(length+count);
}
extern "C" ScanByte scannerFastUnicodeFlags[16384];
extern "C" unsigned short scannerIdentifierRanges[],scannerIdentifierExtraRanges[],scannerDigitRanges[],scannerIdentifierSpecialRanges[];
extern "C" void setup_unichar_flags(void)
{
    unsigned int value;
    memclrw(scannerUnicodeFlags,65536);
    scannerUnicodeFlags[13]|=64;scannerUnicodeFlags[10]|=64;scannerUnicodeFlags['\\']|=64;
    scannerUnicodeFlags[65535]|=64;scannerUnicodeFlags[27]|=64;
    memclrw(scannerFastUnicodeFlags,16384);
    scannerFastUnicodeFlags[0xda8]|=6;scannerFastUnicodeFlags[0xda4]|=6;
    scannerFastUnicodeFlags[0x2e0d]|=7;scannerFastUnicodeFlags[0x2e0a]|=7;
    scannerFastUnicodeFlags[0x2e75]|=6;scannerFastUnicodeFlags[0x2e55]|=6;
    for(value=1;value<128;++value) {
        scannerFastUnicodeFlags[(value^0x680)&0x3fff]|=4;
        scannerFastUnicodeFlags[(value^0x500)&0x3fff]|=4;
    }
    for(value='0';value<='9';++value)scannerUnicodeFlags[value]|=16;
    unsigned short *range;
    for(range=scannerIdentifierRanges;range[0];range+=2)
        for(value=range[0];value<=range[1];++value)scannerUnicodeFlags[value]|=1;
    for(range=scannerIdentifierExtraRanges;range[0];range+=2)
        for(value=range[0];value<=range[1];++value)
            if(!(scannerUnicodeFlags[value]&1))scannerUnicodeFlags[value]|=3;
    for(range=scannerDigitRanges;range[0];range+=2)
        for(value=range[0];value<=range[1];++value)
            if(!(scannerUnicodeFlags[value]&16))scannerUnicodeFlags[value]|=18;
    for(range=scannerIdentifierSpecialRanges;range[0];range+=2)
        for(value=range[0];value<=range[1];++value) {
            if(!(scannerUnicodeFlags[value]&1))scannerUnicodeFlags[value]|=3;
            scannerUnicodeFlags[value]|=4;
        }
    for(value=0;value<160;++value)
        if(value!='$' && value!='@' && value!='`')scannerUnicodeFlags[value]|=128;
    for(value=0xd800;value<0xe000;++value)scannerUnicodeFlags[value]|=128;
}
extern "C" void *scannerComObject0,*scannerComEncodingRecords;
extern "C" unsigned int scannerComEncodingCount;
extern "C" void scanner_load(void)
{
    unsigned int value;
    scannerDefaultEncoding=0;scannerDefaultGuess=0;
    scannerDefaultDecoder=scanner_new_decoder(scannerVTable00694d04);
    scannerContext.decoder=scannerDefaultDecoder;
    for(value=0;value<256;++value)scannerHexDigits[value]=-1;
    for(value='0';value<='9';++value)scannerHexDigits[value]=(signed char)(value-'0');
    for(value=0;value<6;++value) {
        scannerHexDigits['A'+value]=(signed char)(value+10);
        scannerHexDigits['a'+value]=(signed char)(value+10);
    }
    for(value=0;value<256;++value) {
        scannerCodePageFlags[value]=0;
        if(value>0xa0 && value<0xff)scannerCodePageFlags[value]|=3;
        if(value==0x8e)scannerCodePageFlags[value]|=16;
        if((value>0x80 && value<0xa0) || (value>0xdf && value<0xf0))scannerCodePageFlags[value]|=4;
        if((value>0x3f && value<0x7f) || (value>0x7f && value<0xfd))scannerCodePageFlags[value]|=8;
        if(value>0xa0 && value<0xe0)scannerCodePageFlags[value]|=32;
    }
    setup_unichar_flags();memclrw(scannerCharacterFlags,256);
    scannerCachedConverter=0;scannerComObject0=0;scannerComEncodingRecords=0;scannerComEncodingCount=0;
    scannerCurrentCodePage=0xffffffff;
}

extern "C" ScanWord __stdcall fn_00481fa0(char *start,char *end,char **current)
{
    ScanWord value=0;
    if(start<end) {
        ScanByte first=*(ScanByte *)start,flags=scannerCodePageFlags[first];value=first;
        if((flags&4) && start+1<end) {
            ScanByte second=(ScanByte)start[1];
            /* The native routine tests the leading byte's flags again. */
            if(flags&8) {
                value=first<0xe0?(value-0x81)*2+0x21:(first-0xe0)*2+0x5f;
                ScanByte low;
                if(second<0x9f)low=(ScanByte)(second-0x1f);
                else { value=(ScanByte)(value+1);low=(ScanByte)(second-0x7e); }
                if(second>0x7f && second<0x9f)--low;
                value=scannerCachedConverter?
                    ((ScanDecoder *)scannerCachedConverter)->method2c(((value&255)<<8)|low):0xffff;
                *current=start+2;return value;
            }
            value=0xffff;
        } else if(flags&32)value+=0xfec0;
        ++start;
    }
    *current=start;return value;
}
static inline ScanWord scanner_line_count(void)
{
    void *table=scannerContext.file->lineTable;
    return table?*(ScanWord *)((char *)table+4)/4:0;
}
extern "C" void fn_00482b10(void)
{
    ScanState saved=scannerContext.state;
    char *end=scannerContext.end,*next;
    ScanWord count=scanner_line_count();
    if(!count) {
        scannerContext.state.current=scannerContext.text;scannerContext.state.line=scannerContext.text;
        scannerContext.state.column=1;sourcetext_define_line(scannerContext.file,1,0);
    } else {
        char *start=scannerContext.text+sourcetext_get_line_offset(scannerContext.file,count);
        scannerContext.state.line=start;scannerContext.state.current=start;scannerContext.state.column=count;
    }
    for(;;) {
        ScanWord value=((ScanWord (*)(char *,char *,char **))scannerContext.callbacks[0])(scannerContext.state.current,end,&next);
        char *cursor=next;
        if(value==13 || value==10) {
            if(value==13 && ((ScanWord (*)(char *,char *,char **))scannerContext.callbacks[0])(next,end,&next)==10)cursor=next;
            fn_004816a0(cursor);
        } else if(!value)break;
        else scannerContext.state.current=next;
    }
    scannerContext.state=saved;
}
extern "C" void fn_00482ce0(ScanWord requested)
{
    ScanState saved=scannerContext.state;
    char *end=scannerContext.end,*next;
    ScanWord count=scanner_line_count();
    if(count<requested) {
        char *cursor;
        if(!count) {
            scannerContext.state.current=scannerContext.text;scannerContext.state.line=scannerContext.text;
            scannerContext.state.column=1;sourcetext_define_line(scannerContext.file,1,0);cursor=scannerContext.state.current;
        } else {
            scannerContext.state.line=scannerContext.text+sourcetext_get_line_offset(scannerContext.file,count);
            cursor=scannerContext.state.line;scannerContext.state.column=count;
        }
        for(;;) {
            scannerContext.state.current=cursor;
            if(requested<=scannerContext.state.column)break;
            ScanWord value=((ScanWord (*)(char *,char *,char **))scannerContext.callbacks[0])(cursor,end,&next);
            cursor=next;
            if(value==13 || value==10) {
                if(value==13 && ((ScanWord (*)(char *,char *,char **))scannerContext.callbacks[0])(next,end,&next)==10)cursor=next;
                fn_004816a0(cursor);
            } else if(!value)break;
        }
        while(scannerContext.state.column<requested) {
            ++scannerContext.state.column;
            sourcetext_define_line(scannerContext.file,scannerContext.state.column,scannerContext.state.line-scannerContext.text);
        }
    }
    scannerContext.state=saved;
}

extern "C" void *scannerComObject1,*scannerComObject2,*scannerComConverter;
extern "C" ScanByte scannerComClassID[16],scannerComInterfaceID[16];
extern "C" char scannerCodePageDescription[50],scannerCodePageWebName[50],scannerCodePageHeaderName[50];
extern "C" int (__stdcall *scannerCoInitialize)(void *);
extern "C" void (__stdcall *scannerCoUninitialize)(void);
extern "C" int (__stdcall *scannerCoCreateInstance)(const void *,void *,ScanWord,const void *,void **);
extern "C" void *(__stdcall *scannerCoTaskMemAlloc)(ScanWord);
extern "C" void (__stdcall *scannerCoTaskMemFree)(void *);
struct ScanMimeCodePage {
    ScanWord flags,codePage,family;
    unsigned short description[64],webName[50],headerName[50],bodyName[50],fixedFont[32],proportionalFont[32];
    ScanByte charset,padding[3];
};
typedef char VerifyScanMimeCodePage[(sizeof(ScanMimeCodePage)==572)?1:-1];
static inline void scanner_release_com(void *object)
{
    ((ScanWord (__stdcall *)(void *))(*(void ***)object)[2])(object);
}
extern "C" void fn_00481900(void)
{
    ScanByte initialized=scannerComObject0!=0;
    if(scannerComObject0) { scanner_release_com(scannerComObject0);scannerComObject0=0; }
    if(scannerComObject1) { scanner_release_com(scannerComObject1);scannerComObject1=0; }
    if(scannerComObject2) { scanner_release_com(scannerComObject2);scannerComObject2=0; }
    if(scannerComConverter) { scanner_release_com(scannerComConverter);scannerComConverter=0; }
    if(scannerComEncodingRecords) { scannerCoTaskMemFree(scannerComEncodingRecords);scannerComEncodingRecords=0; }
    if(initialized)scannerCoUninitialize();
}
extern "C" ScanByte fn_004819d0(void)
{
    ScanWord fetched;
    if(scannerComObject0)return 1;
    if(scannerCoInitialize(0)<0)return 0;
    if(scannerCoCreateInstance(scannerComClassID,0,7,scannerComInterfaceID,&scannerComObject0)<0)return 0;
    ((int (__stdcall *)(void *,ScanWord,ScanWord,void **))(*(void ***)scannerComObject0)[6])
        (scannerComObject0,0x20000,0x409,&scannerComObject1);
    if(!scannerComObject0 || !scannerComObject1)return 0;
    if(((int (__stdcall *)(void *,ScanWord,ScanWord,ScanWord,void **))(*(void ***)scannerComObject0)[17])
        (scannerComObject0,1200,1252,0,&scannerComConverter)<0)return 0;
    if(((int (__stdcall *)(void *,unsigned int *))(*(void ***)scannerComObject0)[3])
        (scannerComObject0,&scannerComEncodingCount)<0)return 0;
    scannerComEncodingRecords=scannerCoTaskMemAlloc(scannerComEncodingCount*572);
    ((int (__stdcall *)(void *))(*(void ***)scannerComObject1)[5])(scannerComObject1);
    int status=((int (__stdcall *)(void *,ScanWord,void *,ScanWord *))(*(void ***)scannerComObject1)[4])
        (scannerComObject1,scannerComEncodingCount,scannerComEncodingRecords,&fetched);
    scannerComEncodingCount=fetched;
    return status>=0;
}
extern "C" unsigned int fn_0042d800(const char *,char **,int);
static inline void scanner_convert_code_page_name(const unsigned short *input,char *output)
{
    unsigned int length=0,capacity=50;
    while(input[length])++length;
    ((int (__stdcall *)(void *,const unsigned short *,unsigned int *,char *,unsigned int *))(*(void ***)scannerComConverter)[9])
        (scannerComConverter,input,&length,output,&capacity);
    output[capacity]=0;
}
extern "C" unsigned int fn_00481710(const char *name,const char **matched)
{
    char *end;
    unsigned int number=fn_0042d800(name,&end,10);
    ScanMimeCodePage *records=(ScanMimeCodePage *)scannerComEncodingRecords;
    for(unsigned int index=0;index<scannerComEncodingCount;++index) {
        scanner_convert_code_page_name(records[index].description,scannerCodePageDescription);
        scanner_convert_code_page_name(records[index].webName,scannerCodePageWebName);
        scanner_convert_code_page_name(records[index].headerName,scannerCodePageHeaderName);
        unsigned int codePage=records[index].codePage;
        if(number && number==codePage)return number;
        if(!fn_0046d9f0(scannerCodePageWebName,name)) { *matched=scannerCodePageWebName;return codePage; }
        if(!fn_0046d9f0(scannerCodePageHeaderName,name)) { *matched=scannerCodePageHeaderName;return codePage; }
        if(!fn_0046d9f0(scannerCodePageDescription,name)) { *matched=scannerCodePageDescription;return codePage; }
    }
    return 0;
}

extern "C" { ScanBuffer scannerLiteralBuffer,scannerCommentBuffer; }
extern "C" ScanByte scannerWarnExtendedIdentifier;
static char scannerHexCharacters[]="0123456789ABCDEF";
static inline void scanner_append_byte(ScanByte value)
{
    if(scannerLiteralBuffer.capacity<=scannerLiteralBuffer.length+1)
        (scannerLiteralBuffer.*scannerLiteralBuffer.grow)(scannerLiteralBuffer.length+1);
    scannerLiteralBuffer.text[scannerLiteralBuffer.length++]=(char)value;
}
static inline void scanner_append_bytes(const char *text,int length)
{
    if(scannerLiteralBuffer.capacity<=scannerLiteralBuffer.length+length)
        (scannerLiteralBuffer.*scannerLiteralBuffer.grow)(scannerLiteralBuffer.length+length);
    while(length--)scannerLiteralBuffer.text[scannerLiteralBuffer.length++]=*text++;
}
static inline void scanner_append_universal(ScanWord value)
{
    int count=value<0x10000?4:8;
    if(scannerLiteralBuffer.capacity<=scannerLiteralBuffer.length+count+2)
        (scannerLiteralBuffer.*scannerLiteralBuffer.grow)(scannerLiteralBuffer.length+count+2);
    scannerLiteralBuffer.text[scannerLiteralBuffer.length++]='\\';
    scannerLiteralBuffer.text[scannerLiteralBuffer.length++]=count==4?'u':'U';
    for(int shift=(count-1)*4;shift>=0;shift-=4)
        scannerLiteralBuffer.text[scannerLiteralBuffer.length++]=scannerHexCharacters[(value>>shift)&15];
}
extern "C" void fn_0047d1e0(ScanWord terminator,char **current,char *end)
{
    ScanByte warned=0;
    char *cursor=*current,*next;
    for(;;) {
        ScanWord value=((ScanWord (*)(char *,char *,char **,ScanByte))scannerContext.callbacks[1])(cursor,end,&next,1);
        if(value==terminator) { *current=next;return; }
        if(value==10 && terminator=='"' && !scannerStrictCharacters) {
            if(!warned) { scanner_warning(scannerContext.previous.current,(int)cursor,scannerContext.previous.column,0x28d1);warned=1; }
        } else if(!value || value==10) {
            scanner_error(scannerContext.previous.current,(int)scannerContext.state.current,scannerContext.previous.column,0x2780);
            *current=next;return;
        }
        if(value=='\\') {
            scanner_append_byte('\\');
            value=((ScanWord (*)(char *,char *,char **,ScanByte))scannerContext.callbacks[1])(next,end,&next,1);
        }
        cursor=next;
        if(value<256) {
            if(value==1)scanner_append_bytes("\\x01",4);
            else scanner_append_byte((ScanByte)value);
        } else scanner_append_universal(value);
    }
}
static inline char *scanner_skip_literal_splices(char *cursor,char *end)
{
    char *next,*look;
    for(;;) {
        ScanWord value=((ScanWord (*)(char *,char *,char **))scannerContext.callbacks[0])(cursor,end,&next);
        if(value!='\\')return cursor;
        value=((ScanWord (*)(char *,char *,char **))scannerContext.callbacks[0])(next,end,&look);
        if(value!=13 && value!=10)return cursor;
        cursor=look;
        if(value==13 && ((ScanWord (*)(char *,char *,char **))scannerContext.callbacks[0])(look,end,&next)==10)cursor=next;
        fn_004816a0(cursor);
    }
}
extern "C" void fn_0047d630(ScanWord terminator,char **current,char *end)
{
    char *cursor=*current,*next;
    ScanByte warned=0;
    for(;;) {
        cursor=scanner_skip_literal_splices(cursor,end);
        if(scannerContext.decoderFlag==1 && scannerContext.decoderMode) {
            next=cursor;((ScanDecoder *)scannerContext.decoder)->method08(&next,end);
            scanner_append_bytes(cursor,next-cursor);cursor=next;
            cursor=scanner_skip_literal_splices(cursor,end);
        }
        ScanWord value=((ScanWord (*)(char *,char *,char **,ScanByte))scannerContext.callbacks[1])(cursor,end,&next,1);
        if(value==terminator) { *current=next;return; }
        if(value==10 && terminator=='"' && !scannerStrictCharacters) {
            if(!warned) { scanner_warning(scannerContext.previous.current,(int)cursor,scannerContext.previous.column,0x28d1);warned=1; }
        } else if(!value || value==10) {
            scanner_error(scannerContext.previous.current,(int)scannerContext.state.current,scannerContext.previous.column,0x2780);
            *current=cursor;return;
        }
        if(value=='\\') {
            if(scannerOptionQuestion && next-cursor>=3 && cursor[0]=='?' && cursor[1]=='?')scanner_append_byte((ScanByte)value);
            else scanner_append_bytes(cursor,next-cursor);
            cursor=next;
            value=((ScanWord (*)(char *,char *,char **,ScanByte))scannerContext.callbacks[1])(cursor,end,&next,1);
        }
        if(scannerOptionQuestion && next-cursor>=3 && cursor[0]=='?' && cursor[1]=='?' && value!='?' && value<128)
            scanner_append_byte((ScanByte)value);
        else scanner_append_bytes(cursor,next-cursor);
        cursor=next;
    }
}
extern "C" void fn_0047db20(char **current,char *end,char **next,ScanWord *character)
{
    char *cursor=*current,*begin=scannerContext.previous.current,*after;
    ScanWord value=*character;
    if(value<0x10000 && (scannerUnicodeFlags[value]&12)==4 && scannerWarnExtendedIdentifier) {
        scannerUnicodeFlags[value]|=8;
        scanner_warning(begin,(int)cursor,scannerContext.previous.column,0x28df);
    }
    for(;;) {
        if(value>0xffff || (scannerUnicodeFlags[value]&10)==2) {
            if(value<0x10000)scannerUnicodeFlags[value]|=8;
            if(!scannerStrictCharacters) {
                if(scannerWarnExtendedIdentifier)scanner_warning(begin,(int)cursor,scannerContext.state.column,0x28e0);
            } else scanner_error(begin,(int)cursor,scannerContext.state.column,0x28e0);
        }
        if(value<128 || (value<256 && (scannerUnicodeFlags[value]&128)))scanner_append_byte((ScanByte)value);
        else scanner_append_universal(value);
        char *old=cursor;
        value=((ScanWord (*)(char *,char *,char **,ScanByte))scannerContext.callbacks[1])(cursor,end,&after,0);
        if(value<=0xffff && !(scannerUnicodeFlags[value]&17)) {
            *current=old;*next=after;*character=value;return;
        }
        begin=old;cursor=after;
    }
}

extern "C" void *realloc(void *,size_t);
extern "C" void free(void *);
extern "C" void *CompilerTools_AllocatePool(ScanWord);
void ScanBuffer::fn_00481da0(int requested)
{
    allocationCapacity=(ScanWord)requested*2+1;
    allocation=realloc(allocation,allocationCapacity);
    if(text==(char *)embedded)memcpy(allocation,text,length);
    capacity=allocationCapacity;text=(char *)allocation;
}
ScanBuffer::~ScanBuffer(void)
{
    free(allocation);allocation=0;
}
static inline void scanner_append_converted(ScanBuffer &buffer,ScanWord value)
{
    if(value<256) { buffer.fn_0047ec80(1);buffer.fn_0047ec60((ScanByte)value);return; }
    char escaped[10];int digits=value<0x10000?4:8;
    escaped[0]='\\';escaped[1]=digits==4?'u':'U';
    for(int index=0;index<digits;++index)
        escaped[index+2]=scannerHexCharacters[(value>>((digits-index-1)*4))&15];
    buffer.fn_0047ec00(escaped,digits+2);
}
extern "C" void scanner_convert_up_literal(short oldKind,short newKind,ScanByte encoding,char **text,int *length)
{
    ScanBuffer buffer;
    if(oldKind==newKind)return;
    int width;
    if(newKind==-12 || newKind==-9)width=1;
    else if(oldKind==-13 || newKind==-10)width=2;
    else width=4;
    if(buffer.capacity<=*length)(buffer.*buffer.grow)(*length);
    ScanByte oldSuppress=scannerContext.suppress;scannerContext.suppress=1;
    ScanContext saved=scannerContext;
    scannerContext.text=*text;scannerContext.end=*text+*length;
    scannerContext.state.current=*text;scannerContext.decoder=0;
    scanner_init_decoder(encoding);
    char *cursor=scannerContext.state.current,*end=scannerContext.end,*next;
    while(cursor<end) {
        next=cursor;((ScanDecoder *)scannerContext.decoder)->method08(&next,end);
        ScanWord value=((ScanDecoder *)scannerContext.decoder)->decode(cursor,end,&next);
        if(width==2 && value>=0x10000) {
            /* Preserve both arithmetic expressions emitted by the native TU. */
            scanner_append_converted(buffer,((value+0x35fdc00)>>10)&0xffff);
            scanner_append_converted(buffer,(value-0x2400)&0xffff);
        } else scanner_append_converted(buffer,value);
        cursor=next;
    }
    scannerContext=saved;
    if(scannerContext.decoder)((ScanDecoder *)scannerContext.decoder)->reset();
    scannerContext.suppress=oldSuppress;
    buffer.text[buffer.length]=0;*length=buffer.length;
    *text=(char *)CompilerTools_AllocatePool(*length+1);memcpy(*text,buffer.text,*length+1);
}
extern "C" void CompilerTools_AppendGListData(void *,const void *,ScanWord);
extern "C" void CompilerTools_AppendGListString(void *,const char *);
extern "C" void AppendGListByte(void *,int);
static char scannerUnicode16Format[]="\\u%04X",scannerUnicode32Format[]="\\U%08X";
extern "C" void scanner_converttoascii(void *list,char *text,ScanByte encoding,int start,int endOffset)
{
    if(!text || endOffset<=start)return;
    if(encoding==2) { CompilerTools_AppendGListData(list,text+start,endOffset-start);return; }
    ScanByte oldSuppress=scannerContext.suppress;scannerContext.suppress=1;
    ScanContext saved=scannerContext;
    scannerContext.text=text+start;scannerContext.end=text+endOffset;
    scannerContext.state.current=scannerContext.text;scannerContext.decoder=0;
    scanner_init_decoder(encoding);
    char *cursor=scannerContext.state.current,*end=scannerContext.end,*next;
    while(cursor<end) {
        next=cursor;((ScanDecoder *)scannerContext.decoder)->method08(&next,end);
        ScanWord value=((ScanDecoder *)scannerContext.decoder)->decode(cursor,end,&next);
        if(value) {
            if(value<256)AppendGListByte(list,(signed char)value);
            else {
                char escaped[12];sprintf(escaped,value<0x10000?scannerUnicode16Format:scannerUnicode32Format,value);
                CompilerTools_AppendGListString(list,escaped);
            }
        }
        cursor=next;
    }
    scannerContext=saved;
    if(scannerContext.decoder)((ScanDecoder *)scannerContext.decoder)->reset();
    scannerContext.suppress=oldSuppress;
}

typedef unsigned char byte,undefined,undefined1;typedef unsigned short ushort,undefined2;typedef unsigned int uint,undefined4;
extern "C" ScanBuffer scannerLiteralBuffer;
extern "C" void fn_0047d1e0(ScanWord,char **,char *),fn_0047d630(ScanWord,char **,char *),fn_0047db20(char **,char *,char **,ScanWord *);
extern "C" byte scannerNative0067ddf9;
extern "C" byte scannerNative0067de01;
extern "C" byte scannerNative0067de05;
extern "C" byte scannerNative0067de41;
extern "C" byte scannerNative0067de45;
extern "C" byte scannerNative0067de49;
extern "C" byte scannerNative0067de4d;
extern "C" byte scannerNative0067de51;
extern "C" byte scannerNative0067de55;
extern "C" byte scannerNative0067de5d;
extern "C" byte scannerNative0067de61;
extern "C" byte scannerNative0067de65;
extern "C" byte scannerNative0067de69;
extern "C" byte scannerNative0067de6d;
extern "C" byte scannerNative0067de71;
extern "C" byte scannerNative0067de75;
extern "C" byte scannerNative0067de79;
extern "C" byte scannerNative0067de7d;
extern "C" byte scannerNative0067de81;
extern "C" byte scannerNative0067de85;
extern "C" byte scannerNative0067de89;
extern "C" byte scannerNative0067de8d;
extern "C" byte scannerNative0067de91;
extern "C" byte scannerNative0067de95;
extern "C" byte scannerNative0067de99;
extern "C" byte scannerNative0067de9d;
extern "C" byte scannerNative0067dea1;
extern "C" byte scannerNative0067dea5;
extern "C" byte scannerNative0067dea9;
extern "C" byte scannerNative0067deb1;
extern "C" byte scannerNative0067deb5;
extern "C" byte scannerNative00694004;
extern "C" byte scannerNative00694b0e;
extern "C" byte scannerNative0070f071;
extern "C" byte scannerNative0070f072;
extern "C" byte scannerNative0070f1a8;
extern "C" byte scannerNative0070f1af;
extern "C" byte scannerNative0070f1ca;
extern "C" byte scannerNative00716ebc;
extern "C" byte scannerNative00716ec0;
extern "C" byte scannerNative00716ec2;
extern "C" byte scannerNative00716ec4;
extern "C" byte scannerNative0071726a;
extern "C" byte scannerNative007172ba;
extern "C" byte scannerNative007172be;
extern "C" byte scannerNative007172c2;
extern "C" byte scannerNative0071745a;
extern "C" byte scannerNative00725d94;
extern "C" byte scannerNative00725f3f;

extern "C" short fn_00484b20(ScanToken *token)
{
 short *param_1=(short *)token;
  bool bVar1;
  int iVar2;
  byte *pbVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  short sVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  char cVar10;
  byte bVar11;
  byte *pbVar12;
  byte *pbVar13;
  int *piVar14;
  byte *local_44;
  int *local_40;
  int *local_3c;
  undefined4 *local_38;
  undefined4 *local_34;
  undefined4 *local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined *local_1c;
  undefined4 *local_18;
  byte *local_14;
  pbVar3=(byte *)((*(byte **)&scannerContext.end));
  local_44=(byte *)((*(byte **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_28=(undefined4 *)(&(*(byte **)&scannerContext.state.current));
  local_24=(undefined4 *)(&(*(byte **)&scannerContext.state.current));
  local_2c=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_20=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_3c=(int *)(&(*(uint *)&scannerContext.previous.current));
  local_40=(int *)((int *)&(*(byte **)&scannerContext.state.current));
  local_1c=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_38=(undefined4 *)((undefined4 *)&(*(byte *)&scannerLiteralBuffer.grow));
LAB_00484b81:
  pbVar12=(byte *)(local_44);
  if (local_44 < pbVar3) {
    if (local_44 < pbVar3) {
      local_14=(byte *)(local_44 + 1);
      uVar7=(uint)((uint)*local_44);
    }
    else {
      local_14=(byte *)(pbVar3);
      uVar7=(uint)(0);
    }
    if ((uVar7 == 9) || (uVar7 - 0xb < 2) || (uVar7 == 0x1a) || (uVar7 == 0x20)) goto LAB_00484bc0;
    if (uVar7 == 0x5c) {
      if (local_14 < pbVar3) {
        pbVar13=(byte *)(local_14 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
      }
      else {
        local_18=(undefined4 *)((undefined4 *)0x0);
        pbVar13=(byte *)(pbVar3);
      }
      if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa)) goto LAB_00484cb0;
      local_44=(byte *)(pbVar13);
      if (local_18 == (undefined4 *)0xd) {
        if (pbVar13 < pbVar3) {
          local_14=(byte *)(pbVar13 + 1);
          bVar11=(byte)(*pbVar13);
        }
        else {
          bVar11=(byte)(0);
          local_14=(byte *)(pbVar3);
        }
        if (bVar11 == 10) {
          local_44=(byte *)(local_14);
        }
      }
      pbVar12=(byte *)(local_44);
      if ((*(byte **)&scannerContext.state.line) < local_44) {
        (*(byte **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar7=(uint)(0);
        }
        else {
          uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar7 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(byte **)&scannerContext.state.current) = pbVar12;
      goto LAB_00484b81;
    }
  }
LAB_00484cb0:
  (*(byte **)&scannerContext.state.current) = local_44;
  *local_20 = *local_24;
  local_20[1] = local_24[1];
  local_20[2] = local_24[2];
  local_20[3] = local_24[3];
  piVar14=(int *)(local_3c);
  if (local_3c == (int *)0x0) {
    piVar14=(int *)(local_40);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *piVar14 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = piVar14[3];
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  if (local_44 < pbVar3) {
    local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
    local_44=(byte *)(local_44 + 1);
  }
  else {
    local_44=(byte *)(pbVar3);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_18 == (undefined4 *)0x0) {
    if (scannerCharacterFlags[0] == '\0') {
      (*(byte **)&scannerContext.state.current) = local_44;
      *param_1 = 0;
      goto LAB_00485b12;
    }
    goto LAB_00485474;
  }
  if (local_44 + 3 < pbVar3) {
    local_34=(undefined4 *)(local_38);
LAB_00484da8:
    if ((scannerNative00725f3f != '\0') && (local_18 < (undefined4 *)0x10000)) {
      if ((*(byte *)(local_18 + 0x19fc00) & 1) != 0) {
switchD_00484dfc_caseD_41:
        puVar4=(undefined *)(local_1c);
        pbVar12=(byte *)(local_44);
        goto LAB_00485814;
      }
      if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) goto switchD_00484dfc_caseD_30;
      if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00485565;
    }
    do {
      switch((uint)local_18) {
      case 0x0:
        if (scannerCharacterFlags[0] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0;
        goto LAB_00485b12;
      default:
        if (local_18 > (undefined4 *)0x7f) goto switchD_00484dfc_caseD_1b;
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 1) != 0))
        goto switchD_00484dfc_caseD_41;
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 0x10) == 0)) {
          if (local_18 < (undefined4 *)0x100) {
            if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00485474;
            (*(byte **)&scannerContext.state.current) = local_44;
            *param_1 = (short)local_18;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_00485474;
            (*(byte **)&scannerContext.state.current) = local_44;
            *param_1 = -6;
          }
          goto LAB_00485b12;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_00484dfc_caseD_30:
        local_30=(undefined4 *)(local_34);
        pbVar13=(byte *)(local_44);
        while( true ) {
          local_44=(byte *)(pbVar13);
          puVar5=(undefined4 *)(local_18);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar8=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
          if (pbVar3 <= local_44) break;
          local_14=(byte *)(local_44 + 1);
          local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
          if ((local_18 > (undefined4 *)0x7f) ||
             (pbVar13 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0 &&
             (((local_18 != (undefined4 *)0x2b && (local_18 != (undefined4 *)0x2d)) ||
              (puVar5 != (undefined4 *)0x45 &&
              (puVar5 != (undefined4 *)0x65 && (puVar5 != (undefined4 *)0x50) &&
              (puVar5 != (undefined4 *)0x70)))) && (local_18 != (undefined4 *)0x2e)))) break;
        }
        if ((local_18 < (undefined4 *)0x80) && (local_14 < pbVar3) &&
           (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0))
        goto switchD_00484dfc_caseD_1b;
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           (puVar5 > (undefined4 *)0x2f && (puVar5 < (undefined4 *)0x3a)) ||
           (puVar5 > (undefined4 *)0xffff ||
           (local_18 = puVar5, (*(byte *)(puVar5 + 0x19fc00) & 0x10) == 0))) {
          (*(byte **)&scannerContext.state.current) = local_44;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00485af0;
        }
        break;
      case 0xa:
      case 0xd:
        if ((local_18 == (undefined4 *)0xd) && (local_14 = local_44 + 1, *local_44 == 10)) {
          local_44=(byte *)(local_14);
        }
        if ((*(byte **)&scannerContext.state.line) < local_44) {
          (*(byte **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar7=(uint)(0);
          }
          else {
            uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar7 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_00485af0;
      case 0x1b:
        goto switchD_00484dfc_caseD_1b;
      case 0x21:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[33] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x21;
        goto LAB_00485b12;
      case 0x22:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) goto LAB_004859c4;
      case 0x27:
        if (local_18 == (undefined4 *)0x27) {
          sVar6=(short)(-9);
        }
        else {
          sVar6=(short)(-0xc);
        }
        *param_1 = sVar6;
        goto LAB_0048595c;
      case 0x23:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x23) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[35] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x23;
        goto LAB_00485b12;
      case 0x25:
        pbVar13=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = pbVar13;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_14=(byte *)(local_44 + 2);
          local_18=(undefined4 *)((undefined4 *)(uint)*pbVar13);
          if (local_18 == (undefined4 *)0x25) {
            local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
            if (local_18 == (undefined4 *)0x3a) {
              (*(byte **)&scannerContext.state.current) = local_44 + 3;
              *param_1 = -0x12;
              *(undefined **)(param_1 + 2) = &scannerNative0067de55;
              param_1[4] = 4;
              param_1[5] = 0;
              goto LAB_00485af0;
            }
            bVar11=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[3]) & 0x3fff]);
          }
          else {
            bVar11=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff]);
          }
          local_44=(byte *)(pbVar13);
          if ((bVar11 & 1) != 0) goto switchD_00484dfc_caseD_1b;
          (*(byte **)&scannerContext.state.current) = pbVar13;
          *param_1 = 0x23;
          *(undefined **)(param_1 + 2) = &scannerNative0067de51;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(byte **)&scannerContext.state.current) = pbVar13;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        local_14=(byte *)(pbVar13);
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*pbVar13) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[37] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x25;
        goto LAB_00485b12;
      case 0x26:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x26) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[38] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x26;
        goto LAB_00485b12;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = (short)local_18;
        goto LAB_00485b12;
      case 0x2a:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[42] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2a;
        goto LAB_00485b12;
      case 0x2b:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x2b) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[43] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2b;
        goto LAB_00485b12;
      case 0x2d:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3e) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
          if ((scannerNative0070f1a8 == '\0') || (local_18 != (undefined4 *)0x2a)) {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[2]) & 0x3fff] & 1) != 0)
            goto switchD_00484dfc_caseD_1b;
            (*(byte **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            (*(byte **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_00485af0;
        }
        if (local_18 == (undefined4 *)0x2d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[45] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2d;
        goto LAB_00485b12;
      case 0x2e:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x2e) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
          if (local_18 == (undefined4 *)0x2e) {
            (*(byte **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            goto LAB_00485af0;
          }
          bVar11=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[2]) & 0x3fff]);
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x2a)) {
            (*(byte **)&scannerContext.state.current) = local_14;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            goto LAB_00485af0;
          }
          if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) {
            local_18=(undefined4 *)((undefined4 *)0x2e);
            goto switchD_00484dfc_caseD_30;
          }
          bVar11=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff]);
        }
        if ((bVar11 & 1) != 0) goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[46] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2e;
        goto LAB_00485b12;
      case 0x2f:
        local_14=(byte *)(local_44 + 1);
        scannerCommentBuffer.length = 0;
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_00485565;
          if (scannerNative0070f1ca != '\0') goto LAB_00485565;
          if (scannerNative0070f1af == '\0') goto LAB_00485565;
        }
        if (local_18 == (undefined4 *)0x2a) {
          local_30=(undefined4 *)((undefined4 *)0x0);
          local_34=(undefined4 *)(local_38);
          local_44=(byte *)(local_14);
          goto LAB_00486538;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[47] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2f;
        goto LAB_00485b12;
      case 0x3a:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x3a)) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[58] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3a;
        goto LAB_00485b12;
      case 0x3c:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) {
LAB_004859c4:
          if (local_18 == (undefined4 *)0x3c) {
            cVar10=(char)('>');
          }
          else {
            cVar10=(char)('\"');
          }
          local_20=(undefined4 *)((undefined4 *)(int)cVar10);
          goto LAB_004859e0;
        }
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (local_18 == (undefined4 *)0x3c) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
          if (local_18 == (undefined4 *)0x3d) {
            (*(byte **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[2]) & 0x3fff] & 1) != 0)
            goto switchD_00484dfc_caseD_1b;
            (*(byte **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00485af0;
        }
        if ((local_18 == (undefined4 *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[60] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3c;
        goto LAB_00485b12;
      case 0x3d:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[61] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3d;
        goto LAB_00485b12;
      case 0x3e:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (local_18 == (undefined4 *)0x3e) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
          if (local_18 == (undefined4 *)0x3d) {
            (*(byte **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[2]) & 0x3fff] & 1) != 0)
            goto switchD_00484dfc_caseD_1b;
            (*(byte **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[62] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3e;
        goto LAB_00485b12;
      case 0x3f:
        goto switchD_00484dfc_caseD_3f;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          local_1c=(undefined *)((undefined *)(uint)scannerUnicodeFlags[64]);
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_44),(char *)(pbVar3),(char **)(&local_14),(ScanWord *)(&local_18));
          scannerUnicodeFlags[64] = (byte)local_1c;
          (*(byte **)&scannerContext.state.current) = local_44;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00485af0;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x40;
        goto LAB_00485b12;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_00484dfc_caseD_41;
      case 0x5c:
        if (local_44 < pbVar3) {
          local_14=(byte *)(local_44 + 1);
          local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        }
        else {
          local_14=(byte *)(pbVar3);
          local_18=(undefined4 *)((undefined4 *)0x0);
        }
        if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa))
        goto switchD_00484dfc_caseD_1b;
        local_44=(byte *)(local_14);
        if (local_18 == (undefined4 *)0xd) {
          if (local_14 < pbVar3) {
            bVar11=(byte)(*local_14);
            local_14=(byte *)(local_14 + 1);
          }
          else {
            local_14=(byte *)(pbVar3);
            bVar11=(byte)(0);
          }
          if (bVar11 == 10) {
            local_44=(byte *)(local_14);
          }
        }
        pbVar12=(byte *)(local_44);
        if ((*(byte **)&scannerContext.state.line) < local_44) {
          (*(byte **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar7=(uint)(0);
          }
          else {
            uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar7 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(byte **)&scannerContext.state.current) = pbVar12;
        goto LAB_00484b81;
      case 0x5e:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[94] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x5e;
        goto LAB_00485b12;
      case 0x7c:
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x7c) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(byte **)&scannerContext.state.current) = local_14;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00485af0;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_00484dfc_caseD_1b;
        if (scannerCharacterFlags[124] != '\0') goto LAB_00485474;
        (*(byte **)&scannerContext.state.current) = local_44;
        *param_1 = 0x7c;
        goto LAB_00485b12;
      }
    } while( true );
  }
  goto switchD_00484dfc_caseD_1b;
LAB_00484bc0:
  local_44=(byte *)(local_14);
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  goto LAB_00484b81;
switchD_00484dfc_caseD_3f:
  if ((scannerNative0070f072 == '\0') || (local_14 = local_44 + 1, *local_44 != 0x3f))
  goto switchD_00484f23_caseD_22;
  pbVar13=(byte *)(local_44 + 2);
  switch(*local_14) {
  case 0x21:
    local_18=(undefined4 *)((undefined4 *)0x7c);
    local_44=(byte *)(pbVar13);
    goto LAB_00484da8;
  default:
    goto switchD_00484f23_caseD_22;
  case 0x27:
    local_18=(undefined4 *)((undefined4 *)0x5e);
    local_44=(byte *)(pbVar13);
    goto LAB_00484da8;
  case 0x28:
    local_18=(undefined4 *)((undefined4 *)0x5b);
    local_44=(byte *)(pbVar13);
    goto switchD_00484f23_caseD_22;
  case 0x29:
    local_18=(undefined4 *)((undefined4 *)0x5d);
    local_44=(byte *)(pbVar13);
    goto switchD_00484f23_caseD_22;
  case 0x2d:
    local_18=(undefined4 *)((undefined4 *)0x7e);
    local_44=(byte *)(pbVar13);
    goto switchD_00484f23_caseD_22;
  case 0x2f:
    if (pbVar13 < pbVar3) {
      local_14=(byte *)(local_44 + 3);
      local_18=(undefined4 *)((undefined4 *)(uint)*pbVar13);
    }
    else {
      local_18=(undefined4 *)((undefined4 *)0x0);
      local_14=(byte *)(pbVar3);
    }
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      local_44=(byte *)(local_14);
      if (local_18 == (undefined4 *)0xd) {
        if (local_14 < pbVar3) {
          bVar11=(byte)(*local_14);
          local_14=(byte *)(local_14 + 1);
        }
        else {
          local_14=(byte *)(pbVar3);
          bVar11=(byte)(0);
        }
        if (bVar11 == 10) {
          local_44=(byte *)(local_14);
        }
      }
      pbVar12=(byte *)(local_44);
      if ((*(byte **)&scannerContext.state.line) < local_44) {
        (*(byte **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar7=(uint)(0);
        }
        else {
          uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar7 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(byte **)&scannerContext.state.current) = pbVar12;
      goto LAB_00484b81;
    }
    local_18=(undefined4 *)((undefined4 *)0x5c);
    local_44=(byte *)(pbVar13);
    goto LAB_00484da8;
  case 0x3c:
    local_18=(undefined4 *)((undefined4 *)0x7b);
    local_44=(byte *)(pbVar13);
    goto switchD_00484f23_caseD_22;
  case 0x3d:
    local_18=(undefined4 *)((undefined4 *)0x23);
    local_44=(byte *)(pbVar13);
    goto LAB_00484da8;
  case 0x3e:
    break;
  }
  local_18=(undefined4 *)((undefined4 *)0x7d);
  local_44=(byte *)(pbVar13);
switchD_00484f23_caseD_22:
  if (*(char *)(local_18 + 0x1a3c00) == '\0') {
    (*(byte **)&scannerContext.state.current) = local_44;
    *param_1 = (short)local_18;
LAB_00485b12:
    scannerNative007172ba = (undefined1)*param_1;
    *(undefined1 **)(param_1 + 2) = &scannerNative007172ba;
    param_1[4] = 1;
    param_1[5] = 0;
    *(int *)(param_1 + 0xc) = (int)(*(byte **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
    return *param_1;
  }
LAB_00485474:
  local_14=(byte *)(local_44);
LAB_00485503:
  if (scannerNative0070f071 != '\0') {
    iVar8=(int)((int)local_44 - (int)pbVar12);
    pbVar13=(byte *)(pbVar12);
    iVar2=(int)(scannerLiteralBuffer.length);
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar8) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar8);
      iVar2=(int)(scannerLiteralBuffer.length);
    }
    for (; pbVar12 = local_44, scannerLiteralBuffer.length = iVar2, iVar8 != 0; iVar8 = iVar8 - 1) {
      scannerLiteralBuffer.length = iVar2 + 1;
      *(byte *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = *pbVar13;
      pbVar13=(byte *)(pbVar13 + 1);
      iVar2=(int)(scannerLiteralBuffer.length);
    }
  }
  if (local_44 < pbVar3) {
LAB_00485565:
    do {
      if (local_44 < pbVar3) {
        local_14=(byte *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
      }
      else {
        local_14=(byte *)(pbVar3);
        local_18=(undefined4 *)((undefined4 *)0x0);
      }
      if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa) ||
         (local_18 == (undefined4 *)0x0)) goto LAB_004855d3;
      if (local_18 > (undefined4 *)0x7f) goto switchD_00484dfc_caseD_1b;
      local_44=(byte *)(local_14);
      if (local_18 != (undefined4 *)0x5c) break;
      if (local_14 < pbVar3) {
        pbVar13=(byte *)(local_14 + 1);
        bVar11=(byte)(*local_14);
      }
      else {
        bVar11=(byte)(0);
        pbVar13=(byte *)(pbVar3);
      }
      if ((bVar11 == 0xd) || (bVar11 == 10)) {
        local_44=(byte *)(pbVar13);
        if (bVar11 == 0xd) {
          if (pbVar13 < pbVar3) {
            pbVar9=(byte *)(pbVar13 + 1);
            bVar11=(byte)(*pbVar13);
          }
          else {
            bVar11=(byte)(0);
            pbVar9=(byte *)(pbVar3);
          }
          if (bVar11 == 10) {
            local_44=(byte *)(pbVar9);
          }
        }
        pbVar13=(byte *)(local_44);
        if ((*(byte **)&scannerContext.state.line) < local_44) {
          (*(byte **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar7=(uint)(0);
          }
          else {
            uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar7 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        bVar1=(bool)(true);
        (*(byte **)&scannerContext.state.current) = pbVar13;
      }
      else {
        bVar1=(bool)(false);
      }
    } while (bVar1);
    goto LAB_00485503;
  }
LAB_004855d3:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 != '\0') {
    (*(byte **)&scannerContext.state.current) = local_44;
    *param_1 = -0x11;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
    *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
    *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
    goto LAB_00485af0;
  }
  (*(byte **)&scannerContext.state.current) = local_44;
  goto LAB_00484b81;
LAB_00486538:
  if (local_44 < pbVar3) {
    local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
    local_44=(byte *)(local_44 + 1);
  }
  else {
    local_44=(byte *)(pbVar3);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if ((local_18 == (undefined4 *)0x2f) && (local_30 == (undefined4 *)0x2a)) goto LAB_0048666e;
  if (local_18 != (undefined4 *)0x0) {
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      if (local_18 == (undefined4 *)0xd) {
        if (local_44 < pbVar3) {
          local_14=(byte *)(local_44 + 1);
          bVar11=(byte)(*local_44);
        }
        else {
          local_14=(byte *)(pbVar3);
          bVar11=(byte)(0);
        }
        if (bVar11 == 10) {
          local_44=(byte *)(local_14);
        }
      }
      pbVar13=(byte *)(local_44);
      if ((*(byte **)&scannerContext.state.line) < local_44) {
        (*(byte **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar7=(uint)(0);
        }
        else {
          uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar7 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(byte **)&scannerContext.state.current) = pbVar13;
      local_18=(undefined4 *)((undefined4 *)0xa);
      goto LAB_004865ec;
    }
    if (local_18 != (undefined4 *)0x5c) goto LAB_004865ec;
    if (local_44 < pbVar3) {
      pbVar13=(byte *)(local_44 + 1);
      bVar11=(byte)(*local_44);
    }
    else {
      bVar11=(byte)(0);
      pbVar13=(byte *)(pbVar3);
    }
    if ((bVar11 == 0xd) || (bVar11 == 10)) {
      local_44=(byte *)(pbVar13);
      if (bVar11 == 0xd) {
        if (pbVar13 < pbVar3) {
          pbVar9=(byte *)(pbVar13 + 1);
          bVar11=(byte)(*pbVar13);
        }
        else {
          bVar11=(byte)(0);
          pbVar9=(byte *)(pbVar3);
        }
        if (bVar11 == 10) {
          local_44=(byte *)(pbVar9);
        }
      }
      pbVar13=(byte *)(local_44);
      if ((*(byte **)&scannerContext.state.line) < local_44) {
        (*(byte **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar7=(uint)(0);
        }
        else {
          uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar7 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      bVar1=(bool)(true);
      (*(byte **)&scannerContext.state.current) = pbVar13;
    }
    else {
      bVar1=(bool)(false);
    }
    if (!bVar1) {
LAB_004865ec:
      local_30=(undefined4 *)(local_18);
      if (scannerNative0070f071 != '\0') {
        iVar8=(int)((int)local_44 - (int)pbVar12);
        pbVar13=(byte *)(pbVar12);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar8) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar8);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; pbVar12 = local_44, scannerLiteralBuffer.length = iVar2, iVar8 != 0; iVar8 = iVar8 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(byte *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = *pbVar13;
          pbVar13=(byte *)(pbVar13 + 1);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_00486538;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 2),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_0048666e:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(byte **)&scannerContext.state.current) = local_44;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_00484b81;
  }
  if (local_18 == (undefined4 *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar8=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = 0x2f;
  }
  (*(byte **)&scannerContext.state.current) = local_44;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00485af0;
LAB_004859e0:
  if (local_44 < pbVar3) {
    local_14=(byte *)(local_44 + 1);
    local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
  }
  else {
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_20 == local_18) goto LAB_00486e10;
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < pbVar3 &&
     (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)))
  goto switchD_00484dfc_caseD_1b;
  if ((local_18 == (undefined4 *)0x0) ||
     (local_18 == (undefined4 *)0xd || (local_18 == (undefined4 *)0xa))) goto LAB_00486d80;
  local_44=(byte *)(local_14);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar8=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
  goto LAB_004859e0;
LAB_00485814:
  local_44=(byte *)(pbVar12);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar8=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
  if (pbVar3 <= local_44) goto LAB_00486a31;
  local_14=(byte *)(local_44 + 1);
  local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
  if ((local_18 > (undefined4 *)0x7f) ||
     (pbVar12 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0)) goto LAB_00486a31;
  goto LAB_00485814;
LAB_00486a31:
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < pbVar3 &&
     (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 2) != 0)))
  goto switchD_00484dfc_caseD_1b;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_18 == (undefined4 *)0x27) {
    sVar6=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar6;
    if (*param_1 != 0) {
      local_44=(byte *)(local_14);
      scannerLiteralBuffer.length = 0;
LAB_0048595c:
      local_24=(undefined4 *)(local_18);
      while( true ) {
        if (local_44 < pbVar3) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
          local_44=(byte *)(local_44 + 1);
        }
        else {
          local_44=(byte *)(pbVar3);
          local_18=(undefined4 *)((undefined4 *)0x0);
        }
        if (local_24 == local_18) {
          (*(byte **)&scannerContext.state.current) = local_44;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00485af0;
        }
        if ((local_18 > (undefined4 *)0x7f) ||
           ((local_44 < pbVar3 &&
            (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_44) & 0x3fff] & 4) != 0)) ||
           (local_18 == (undefined4 *)0x0))) break;
        if (local_18 == (undefined4 *)0x5c) {
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar8=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
          if (local_44 < pbVar3) {
            local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
            local_44=(byte *)(local_44 + 1);
          }
          else {
            local_44=(byte *)(pbVar3);
            local_18=(undefined4 *)((undefined4 *)0x0);
          }
        }
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
        }
        iVar8=(int)(scannerLiteralBuffer.length);
        scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
        *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
      }
switchD_00484dfc_caseD_1b:
      *local_28 = *local_2c;
      local_28[1] = local_2c[1];
      local_28[2] = local_2c[2];
      local_28[3] = local_2c[3];
      sVar6=(short)(fn_00490990((ScanToken *)(param_1)));
      return sVar6;
    }
  }
  else if (local_18 == (undefined4 *)0x22) {
    sVar6=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar6;
    if (*param_1 != 0) {
      local_44=(byte *)(local_14);
      scannerLiteralBuffer.length = 0;
      goto LAB_0048595c;
    }
  }
  (*(byte **)&scannerContext.state.current) = local_44;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00485af0;
LAB_00486d80:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(byte **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_00486e10:
  (*(byte **)&scannerContext.state.current) = local_14;
  if (local_20 == (undefined4 *)0x3e) {
    sVar6=(short)(-0x10);
  }
  else {
    sVar6=(short)(-0xf);
  }
  *param_1 = sVar6;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_00485af0:
  *(int *)(param_1 + 0xc) = (int)(*(byte **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_00486ed0(ScanToken *token)
{
 short *param_1=(short *)token;
  byte bVar1;
  bool bVar2;
  int iVar3;
  ushort *puVar4;
  undefined *puVar5;
  undefined4 *puVar6;
  short sVar7;
  int iVar8;
  uint uVar9;
  char cVar10;
  ushort *puVar11;
  ushort uVar12;
  int *piVar13;
  undefined4 *puVar14;
  ushort *puVar15;
  ushort *puVar16;
  ushort *local_44;
  int *local_40;
  undefined4 *local_3c;
  int *local_38;
  undefined *local_34;
  undefined *local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined *local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  ushort *local_14;
  puVar4=(ushort *)((*(ushort **)&scannerContext.end));
  local_44=(ushort *)((*(ushort **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_28=(undefined4 *)(&(*(ushort **)&scannerContext.state.current));
  local_1c=(undefined4 *)(&(*(ushort **)&scannerContext.state.current));
  local_24=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_2c=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_38=(int *)(&(*(uint *)&scannerContext.previous.current));
  local_40=(int *)((int *)&(*(ushort **)&scannerContext.state.current));
  local_20=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_34=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
LAB_00486f31:
  puVar11=(ushort *)(local_44);
  if (local_44 < puVar4) {
    if (local_44 < puVar4) {
      local_14=(ushort *)(local_44 + 1);
      uVar9=(uint)((uint)*local_44);
    }
    else {
      local_14=(ushort *)(puVar4);
      uVar9=(uint)(0);
    }
    if ((uVar9 == 9) || (uVar9 - 0xb < 2) || (uVar9 == 0x1a) || (uVar9 == 0x20)) goto LAB_00486f70;
    if (uVar9 == 0x5c) {
      if (local_14 < puVar4) {
        puVar15=(ushort *)(local_14 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
      }
      else {
        local_18=(undefined4 *)((undefined4 *)0x0);
        puVar15=(ushort *)(puVar4);
      }
      if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa)) goto LAB_00487060;
      local_44=(ushort *)(puVar15);
      if (local_18 == (undefined4 *)0xd) {
        if (puVar15 < puVar4) {
          local_14=(ushort *)(puVar15 + 1);
          uVar12=(ushort)(*puVar15);
        }
        else {
          uVar12=(ushort)(0);
          local_14=(ushort *)(puVar4);
        }
        if (uVar12 == 10) {
          local_44=(ushort *)(local_14);
        }
      }
      puVar11=(ushort *)(local_44);
      if ((*(ushort **)&scannerContext.state.line) < local_44) {
        (*(ushort **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar9=(uint)(0);
        }
        else {
          uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar9 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar11;
      goto LAB_00486f31;
    }
  }
LAB_00487060:
  (*(ushort **)&scannerContext.state.current) = local_44;
  *local_2c = *local_1c;
  local_2c[1] = local_1c[1];
  local_2c[2] = local_1c[2];
  local_2c[3] = local_1c[3];
  piVar13=(int *)(local_38);
  if (local_38 == (int *)0x0) {
    piVar13=(int *)(local_40);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *piVar13 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = piVar13[3];
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  if (local_44 < puVar4) {
    local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
    local_44=(ushort *)(local_44 + 1);
  }
  else {
    local_44=(ushort *)(puVar4);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_18 == (undefined4 *)0x0) {
    if (scannerCharacterFlags[0] == '\0') {
      (*(ushort **)&scannerContext.state.current) = local_44;
      *param_1 = 0;
      goto LAB_00487ea2;
    }
    goto LAB_00487828;
  }
  if (local_44 + 3 < puVar4) {
    local_30=(undefined *)(local_34);
LAB_00487158:
    if ((scannerNative00725f3f != '\0') && (local_18 < (undefined4 *)0x10000)) {
      if ((*(byte *)(local_18 + 0x19fc00) & 1) != 0) {
switchD_004871ac_caseD_41:
        puVar5=(undefined *)(local_20);
        puVar11=(ushort *)(local_44);
        goto LAB_00487bc4;
      }
      if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) goto switchD_004871ac_caseD_30;
      if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00487925;
    }
    do {
      bVar1=(byte)(scannerUnicodeFlags[64]);
      switch((uint)local_18) {
      case 0x0:
        if (scannerCharacterFlags[0] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0;
        goto LAB_00487ea2;
      default:
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 1) != 0))
        goto switchD_004871ac_caseD_41;
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 0x10) == 0)) {
          if (local_18 < (undefined4 *)0x100) {
            if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00487828;
            (*(ushort **)&scannerContext.state.current) = local_44;
            *param_1 = (short)local_18;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_00487828;
            (*(ushort **)&scannerContext.state.current) = local_44;
            *param_1 = -6;
          }
          goto LAB_00487ea2;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_004871ac_caseD_30:
        puVar5=(undefined *)(local_30);
        puVar15=(ushort *)(local_44);
        while( true ) {
          local_44=(ushort *)(puVar15);
          puVar6=(undefined4 *)(local_18);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar8=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
          if (puVar4 <= local_44) break;
          local_14=(ushort *)(local_44 + 1);
          local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
          if ((local_18 > (undefined4 *)0x7f) ||
             (puVar15 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0 &&
             (((local_18 != (undefined4 *)0x2b && (local_18 != (undefined4 *)0x2d)) ||
              (puVar6 != (undefined4 *)0x45 &&
              (puVar6 != (undefined4 *)0x65 && (puVar6 != (undefined4 *)0x50) &&
              (puVar6 != (undefined4 *)0x70)))) && (local_18 != (undefined4 *)0x2e)))) break;
        }
        if ((local_18 < (undefined4 *)0x80) && (local_14 < puVar4) &&
           (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0))
        goto switchD_004871ac_caseD_1b;
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           (puVar6 > (undefined4 *)0x2f && (puVar6 < (undefined4 *)0x3a)) ||
           (puVar6 > (undefined4 *)0xffff ||
           (local_18 = puVar6, (*(byte *)(puVar6 + 0x19fc00) & 0x10) == 0))) {
          (*(ushort **)&scannerContext.state.current) = local_44;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00487e80;
        }
        break;
      case 0xa:
      case 0xd:
        if ((local_18 == (undefined4 *)0xd) && (local_14 = local_44 + 1, *local_44 == 10)) {
          local_44=(ushort *)(local_14);
        }
        if ((*(ushort **)&scannerContext.state.line) < local_44) {
          (*(ushort **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar9=(uint)(0);
          }
          else {
            uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar9 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_00487e80;
      case 0x1b:
        goto switchD_004871ac_caseD_1b;
      case 0x21:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[33] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x21;
        goto LAB_00487ea2;
      case 0x22:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) goto LAB_00487d60;
      case 0x27:
        if (local_18 == (undefined4 *)0x27) {
          sVar7=(short)(-9);
        }
        else {
          sVar7=(short)(-0xc);
        }
        *param_1 = sVar7;
        goto LAB_00487d04;
      case 0x23:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x23) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[35] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x23;
        goto LAB_00487ea2;
      case 0x25:
        puVar15=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = puVar15;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_14=(ushort *)(local_44 + 2);
          local_18=(undefined4 *)((undefined4 *)(uint)*puVar15);
          if (local_18 == (undefined4 *)0x25) {
            local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
            if (local_18 == (undefined4 *)0x3a) {
              (*(ushort **)&scannerContext.state.current) = local_44 + 3;
              *param_1 = -0x12;
              *(undefined **)(param_1 + 2) = &scannerNative0067de55;
              param_1[4] = 4;
              param_1[5] = 0;
              goto LAB_00487e80;
            }
            bVar1=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[3]) & 0x3fff]);
          }
          else {
            bVar1=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff]);
          }
          local_44=(ushort *)(puVar15);
          if ((bVar1 & 1) != 0) goto switchD_004871ac_caseD_1b;
          (*(ushort **)&scannerContext.state.current) = puVar15;
          *param_1 = 0x23;
          *(undefined **)(param_1 + 2) = &scannerNative0067de51;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(ushort **)&scannerContext.state.current) = puVar15;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        local_14=(ushort *)(puVar15);
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*puVar15) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[37] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x25;
        goto LAB_00487ea2;
      case 0x26:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x26) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[38] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x26;
        goto LAB_00487ea2;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = (short)local_18;
        goto LAB_00487ea2;
      case 0x2a:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[42] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2a;
        goto LAB_00487ea2;
      case 0x2b:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x2b) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[43] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2b;
        goto LAB_00487ea2;
      case 0x2d:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3e) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
          if ((scannerNative0070f1a8 == '\0') || (local_18 != (undefined4 *)0x2a)) {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[2]) & 0x3fff] & 1) != 0)
            goto switchD_004871ac_caseD_1b;
            (*(ushort **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            (*(ushort **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_00487e80;
        }
        if (local_18 == (undefined4 *)0x2d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[45] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2d;
        goto LAB_00487ea2;
      case 0x2e:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x2e) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
          if (local_18 == (undefined4 *)0x2e) {
            (*(ushort **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            goto LAB_00487e80;
          }
          bVar1=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[2]) & 0x3fff]);
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x2a)) {
            (*(ushort **)&scannerContext.state.current) = local_14;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            goto LAB_00487e80;
          }
          if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) {
            local_18=(undefined4 *)((undefined4 *)0x2e);
            goto switchD_004871ac_caseD_30;
          }
          bVar1=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff]);
        }
        if ((bVar1 & 1) != 0) goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[46] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2e;
        goto LAB_00487ea2;
      case 0x2f:
        local_14=(ushort *)(local_44 + 1);
        scannerCommentBuffer.length = 0;
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_00487925;
          if (scannerNative0070f1ca != '\0') goto LAB_00487925;
          if (scannerNative0070f1af == '\0') goto LAB_00487925;
        }
        if (local_18 == (undefined4 *)0x2a) {
          local_3c=(undefined4 *)((undefined4 *)0x0);
          local_30=(undefined *)(local_34);
          local_44=(ushort *)(local_14);
          goto LAB_00488897;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[47] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2f;
        goto LAB_00487ea2;
      case 0x3a:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x3a)) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[58] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3a;
        goto LAB_00487ea2;
      case 0x3c:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) {
LAB_00487d60:
          if (local_18 == (undefined4 *)0x3c) {
            cVar10=(char)('>');
          }
          else {
            cVar10=(char)('\"');
          }
          local_1c=(undefined4 *)((undefined4 *)(int)cVar10);
          goto LAB_00487d80;
        }
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (local_18 == (undefined4 *)0x3c) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
          if (local_18 == (undefined4 *)0x3d) {
            (*(ushort **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[2]) & 0x3fff] & 1) != 0)
            goto switchD_004871ac_caseD_1b;
            (*(ushort **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00487e80;
        }
        if ((local_18 == (undefined4 *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[60] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3c;
        goto LAB_00487ea2;
      case 0x3d:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[61] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3d;
        goto LAB_00487ea2;
      case 0x3e:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (local_18 == (undefined4 *)0x3e) {
          local_18=(undefined4 *)((undefined4 *)(uint)*local_14);
          if (local_18 == (undefined4 *)0x3d) {
            (*(ushort **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)local_44[2]) & 0x3fff] & 1) != 0)
            goto switchD_004871ac_caseD_1b;
            (*(ushort **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[62] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3e;
        goto LAB_00487ea2;
      case 0x3f:
        goto switchD_004871ac_caseD_3f;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_44),(char *)(puVar4),(char **)(&local_14),(ScanWord *)(&local_18));
          (*(ushort **)&scannerContext.state.current) = local_44;
          scannerUnicodeFlags[64] = bVar1;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00487e80;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x40;
        goto LAB_00487ea2;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_004871ac_caseD_41;
      case 0x5c:
        if (local_44 < puVar4) {
          local_14=(ushort *)(local_44 + 1);
          local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        }
        else {
          local_14=(ushort *)(puVar4);
          local_18=(undefined4 *)((undefined4 *)0x0);
        }
        if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa))
        goto switchD_004871ac_caseD_1b;
        local_44=(ushort *)(local_14);
        if (local_18 == (undefined4 *)0xd) {
          if (local_14 < puVar4) {
            uVar12=(ushort)(*local_14);
            local_14=(ushort *)(local_14 + 1);
          }
          else {
            local_14=(ushort *)(puVar4);
            uVar12=(ushort)(0);
          }
          if (uVar12 == 10) {
            local_44=(ushort *)(local_14);
          }
        }
        puVar11=(ushort *)(local_44);
        if ((*(ushort **)&scannerContext.state.line) < local_44) {
          (*(ushort **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar9=(uint)(0);
          }
          else {
            uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar9 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(ushort **)&scannerContext.state.current) = puVar11;
        goto LAB_00486f31;
      case 0x5e:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[94] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x5e;
        goto LAB_00487ea2;
      case 0x7c:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
        if (local_18 == (undefined4 *)0x7c) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00487e80;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)
        goto switchD_004871ac_caseD_1b;
        if (scannerCharacterFlags[124] != '\0') goto LAB_00487828;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x7c;
        goto LAB_00487ea2;
      }
    } while( true );
  }
  goto switchD_004871ac_caseD_1b;
LAB_00486f70:
  local_44=(ushort *)(local_14);
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  goto LAB_00486f31;
switchD_004871ac_caseD_3f:
  if ((scannerNative0070f072 == '\0') || (local_14 = local_44 + 1, *local_44 != 0x3f))
  goto switchD_004872d6_caseD_22;
  puVar15=(ushort *)(local_44 + 2);
  switch(*local_14) {
  case 0x21:
    local_18=(undefined4 *)((undefined4 *)0x7c);
    local_44=(ushort *)(puVar15);
    goto LAB_00487158;
  default:
    goto switchD_004872d6_caseD_22;
  case 0x27:
    local_18=(undefined4 *)((undefined4 *)0x5e);
    local_44=(ushort *)(puVar15);
    goto LAB_00487158;
  case 0x28:
    local_18=(undefined4 *)((undefined4 *)0x5b);
    local_44=(ushort *)(puVar15);
    goto switchD_004872d6_caseD_22;
  case 0x29:
    local_18=(undefined4 *)((undefined4 *)0x5d);
    local_44=(ushort *)(puVar15);
    goto switchD_004872d6_caseD_22;
  case 0x2d:
    local_18=(undefined4 *)((undefined4 *)0x7e);
    local_44=(ushort *)(puVar15);
    goto switchD_004872d6_caseD_22;
  case 0x2f:
    if (puVar15 < puVar4) {
      local_14=(ushort *)(local_44 + 3);
      local_18=(undefined4 *)((undefined4 *)(uint)*puVar15);
    }
    else {
      local_18=(undefined4 *)((undefined4 *)0x0);
      local_14=(ushort *)(puVar4);
    }
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      local_44=(ushort *)(local_14);
      if (local_18 == (undefined4 *)0xd) {
        if (local_14 < puVar4) {
          uVar12=(ushort)(*local_14);
          local_14=(ushort *)(local_14 + 1);
        }
        else {
          local_14=(ushort *)(puVar4);
          uVar12=(ushort)(0);
        }
        if (uVar12 == 10) {
          local_44=(ushort *)(local_14);
        }
      }
      puVar11=(ushort *)(local_44);
      if ((*(ushort **)&scannerContext.state.line) < local_44) {
        (*(ushort **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar9=(uint)(0);
        }
        else {
          uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar9 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar11;
      goto LAB_00486f31;
    }
    local_18=(undefined4 *)((undefined4 *)0x5c);
    local_44=(ushort *)(puVar15);
    goto LAB_00487158;
  case 0x3c:
    local_18=(undefined4 *)((undefined4 *)0x7b);
    local_44=(ushort *)(puVar15);
    goto switchD_004872d6_caseD_22;
  case 0x3d:
    local_18=(undefined4 *)((undefined4 *)0x23);
    local_44=(ushort *)(puVar15);
    goto LAB_00487158;
  case 0x3e:
    break;
  }
  local_18=(undefined4 *)((undefined4 *)0x7d);
  local_44=(ushort *)(puVar15);
switchD_004872d6_caseD_22:
  if (*(char *)(local_18 + 0x1a3c00) == '\0') {
    (*(ushort **)&scannerContext.state.current) = local_44;
    *param_1 = (short)local_18;
LAB_00487ea2:
    scannerNative007172be = (undefined1)*param_1;
    *(undefined1 **)(param_1 + 2) = &scannerNative007172be;
    param_1[4] = 1;
    param_1[5] = 0;
    *(int *)(param_1 + 0xc) = (int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
    return *param_1;
  }
LAB_00487828:
  local_14=(ushort *)(local_44);
LAB_004878b8:
  if (scannerNative0070f071 != '\0') {
    iVar8 = (int)((((int)local_44 - (int)puVar11) + 1U) -
                 (uint)((uint)((int)local_44 - (int)puVar11) < 0x80000000)) >> 1;
    puVar15=(ushort *)(puVar11);
    iVar3=(int)(scannerLiteralBuffer.length);
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar8) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar8);
      iVar3=(int)(scannerLiteralBuffer.length);
    }
    for (; puVar11 = local_44, scannerLiteralBuffer.length = iVar3, iVar8 != 0; iVar8 = iVar8 - 1) {
      scannerLiteralBuffer.length = iVar3 + 1;
      *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar15;
      puVar15=(ushort *)((ushort *)((int)puVar15 + 1));
      iVar3=(int)(scannerLiteralBuffer.length);
    }
  }
  if (local_44 < puVar4) {
LAB_00487925:
    do {
      if (local_44 < puVar4) {
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
      }
      else {
        local_14=(ushort *)(puVar4);
        local_18=(undefined4 *)((undefined4 *)0x0);
      }
      if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa) ||
         (local_18 == (undefined4 *)0x0)) goto LAB_00487987;
      local_44=(ushort *)(local_14);
      if (local_18 != (undefined4 *)0x5c) break;
      if (local_14 < puVar4) {
        puVar15=(ushort *)(local_14 + 1);
        uVar12=(ushort)(*local_14);
      }
      else {
        uVar12=(ushort)(0);
        puVar15=(ushort *)(puVar4);
      }
      if ((uVar12 == 0xd) || (uVar12 == 10)) {
        local_44=(ushort *)(puVar15);
        if (uVar12 == 0xd) {
          if (puVar15 < puVar4) {
            puVar16=(ushort *)(puVar15 + 1);
            uVar12=(ushort)(*puVar15);
          }
          else {
            uVar12=(ushort)(0);
            puVar16=(ushort *)(puVar4);
          }
          if (uVar12 == 10) {
            local_44=(ushort *)(puVar16);
          }
        }
        puVar15=(ushort *)(local_44);
        if ((*(ushort **)&scannerContext.state.line) < local_44) {
          (*(ushort **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar9=(uint)(0);
          }
          else {
            uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar9 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        bVar2=(bool)(true);
        (*(ushort **)&scannerContext.state.current) = puVar15;
      }
      else {
        bVar2=(bool)(false);
      }
    } while (bVar2);
    goto LAB_004878b8;
  }
LAB_00487987:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 != '\0') {
    (*(ushort **)&scannerContext.state.current) = local_44;
    *param_1 = -0x11;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
    *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
    *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
    goto LAB_00487e80;
  }
  (*(ushort **)&scannerContext.state.current) = local_44;
  goto LAB_00486f31;
LAB_00488897:
  if (local_44 < puVar4) {
    local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
    local_44=(ushort *)(local_44 + 1);
  }
  else {
    local_44=(ushort *)(puVar4);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if ((local_18 == (undefined4 *)0x2f) && (local_3c == (undefined4 *)0x2a)) goto LAB_004889de;
  if (local_18 != (undefined4 *)0x0) {
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      if (local_18 == (undefined4 *)0xd) {
        if (local_44 < puVar4) {
          local_14=(ushort *)(local_44 + 1);
          uVar12=(ushort)(*local_44);
        }
        else {
          local_14=(ushort *)(puVar4);
          uVar12=(ushort)(0);
        }
        if (uVar12 == 10) {
          local_44=(ushort *)(local_14);
        }
      }
      puVar15=(ushort *)(local_44);
      if ((*(ushort **)&scannerContext.state.line) < local_44) {
        (*(ushort **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar9=(uint)(0);
        }
        else {
          uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar9 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar15;
      local_18=(undefined4 *)((undefined4 *)0xa);
      goto LAB_0048894c;
    }
    if (local_18 != (undefined4 *)0x5c) goto LAB_0048894c;
    if (local_44 < puVar4) {
      puVar15=(ushort *)(local_44 + 1);
      uVar12=(ushort)(*local_44);
    }
    else {
      uVar12=(ushort)(0);
      puVar15=(ushort *)(puVar4);
    }
    if ((uVar12 == 0xd) || (uVar12 == 10)) {
      local_44=(ushort *)(puVar15);
      if (uVar12 == 0xd) {
        if (puVar15 < puVar4) {
          puVar16=(ushort *)(puVar15 + 1);
          uVar12=(ushort)(*puVar15);
        }
        else {
          uVar12=(ushort)(0);
          puVar16=(ushort *)(puVar4);
        }
        if (uVar12 == 10) {
          local_44=(ushort *)(puVar16);
        }
      }
      puVar15=(ushort *)(local_44);
      if ((*(ushort **)&scannerContext.state.line) < local_44) {
        (*(ushort **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar9=(uint)(0);
        }
        else {
          uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar9 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      bVar2=(bool)(true);
      (*(ushort **)&scannerContext.state.current) = puVar15;
    }
    else {
      bVar2=(bool)(false);
    }
    if (!bVar2) {
LAB_0048894c:
      local_3c=(undefined4 *)(local_18);
      if (scannerNative0070f071 != '\0') {
        iVar8 = (int)((((int)local_44 - (int)puVar11) + 1U) -
                     (uint)((uint)((int)local_44 - (int)puVar11) < 0x80000000)) >> 1;
        puVar15=(ushort *)(puVar11);
        iVar3=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar8) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar8);
          iVar3=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar11 = local_44, scannerLiteralBuffer.length = iVar3, iVar8 != 0; iVar8 = iVar8 - 1) {
          scannerLiteralBuffer.length = iVar3 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar15;
          puVar15=(ushort *)((ushort *)((int)puVar15 + 1));
          iVar3=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_00488897;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 4),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_004889de:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(ushort **)&scannerContext.state.current) = local_44;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_00486f31;
  }
  if (local_18 == (undefined4 *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar8=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = 0x2f;
  }
  (*(ushort **)&scannerContext.state.current) = local_44;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00487e80;
LAB_00487d80:
  if (local_44 < puVar4) {
    local_14=(ushort *)(local_44 + 1);
    local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
  }
  else {
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_1c == local_18) goto LAB_00489170;
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < puVar4 &&
     (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 1) != 0)))
  goto switchD_004871ac_caseD_1b;
  if ((local_18 == (undefined4 *)0x0) ||
     (local_18 == (undefined4 *)0xd || (local_18 == (undefined4 *)0xa))) goto LAB_004890e0;
  local_44=(ushort *)(local_14);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar8=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
  goto LAB_00487d80;
LAB_004890e0:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(ushort **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_00489170:
  (*(ushort **)&scannerContext.state.current) = local_14;
  if (local_1c == (undefined4 *)0x3e) {
    sVar7=(short)(-0x10);
  }
  else {
    sVar7=(short)(-0xf);
  }
  *param_1 = sVar7;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00487e80;
LAB_00487bc4:
  local_44=(ushort *)(puVar11);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar8=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
  if (puVar4 <= local_44) goto LAB_00488da1;
  local_14=(ushort *)(local_44 + 1);
  local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
  if ((local_18 > (undefined4 *)0x7f) ||
     (puVar11 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0)) goto LAB_00488da1;
  goto LAB_00487bc4;
LAB_00488da1:
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < puVar4 &&
     (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ (uint)*local_14) & 0x3fff] & 2) != 0))) {
switchD_004871ac_caseD_1b:
    *local_28 = *local_24;
    local_28[1] = local_24[1];
    local_28[2] = local_24[2];
    local_28[3] = local_24[3];
    sVar7=(short)(fn_00497560((ScanToken *)(param_1)));
    return sVar7;
  }
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_18 == (undefined4 *)0x27) {
    sVar7=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar7;
    if (*param_1 != 0) {
      local_44=(ushort *)(local_14);
      scannerLiteralBuffer.length = 0;
LAB_00487d04:
      do {
        puVar6=(undefined4 *)(local_18);
        if (local_44 < puVar4) {
          puVar14=(undefined4 *)((undefined4 *)(uint)*local_44);
          local_44=(ushort *)(local_44 + 1);
        }
        else {
          local_44=(ushort *)(puVar4);
          puVar14=(undefined4 *)((undefined4 *)0x0);
        }
        if (local_18 == puVar14) {
          (*(ushort **)&scannerContext.state.current) = local_44;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00487e80;
        }
        local_18=(undefined4 *)(puVar14);
        if ((puVar14 > (undefined4 *)0x7f) ||
           ((local_44 < puVar4 &&
            (((&scannerFastUnicodeFlags[0])[((int)puVar14 << 7 ^ (uint)*local_44) & 0x3fff] & 4) != 0)) ||
           (puVar14 == (undefined4 *)0x0))) goto switchD_004871ac_caseD_1b;
        if (puVar14 == (undefined4 *)0x5c) {
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar8=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
          if (local_44 < puVar4) {
            local_18=(undefined4 *)((undefined4 *)(uint)*local_44);
            local_44=(ushort *)(local_44 + 1);
          }
          else {
            local_44=(ushort *)(puVar4);
            local_18=(undefined4 *)((undefined4 *)0x0);
          }
        }
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
        }
        iVar8=(int)(scannerLiteralBuffer.length);
        scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
        *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
        local_18=(undefined4 *)(puVar6);
      } while( true );
    }
  }
  else if (local_18 == (undefined4 *)0x22) {
    sVar7=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar7;
    if (*param_1 != 0) {
      local_44=(ushort *)(local_14);
      scannerLiteralBuffer.length = 0;
      goto LAB_00487d04;
    }
  }
  (*(ushort **)&scannerContext.state.current) = local_44;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_00487e80:
  *(int *)(param_1 + 0xc) = (int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_00489270(ScanToken *token)
{
 short *param_1=(short *)token;
  byte bVar1;
  bool bVar2;
  int iVar3;
  ushort *puVar4;
  undefined *puVar5;
  undefined4 *puVar6;
  short sVar7;
  int iVar8;
  ushort *puVar9;
  undefined4 *puVar10;
  ushort *puVar11;
  char cVar12;
  ushort *puVar13;
  uint uVar14;
  int *piVar15;
  ushort *local_44;
  int *local_40;
  undefined4 *local_3c;
  int *local_38;
  undefined *local_34;
  undefined *local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined *local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  ushort *local_14;
  puVar4=(ushort *)((*(ushort **)&scannerContext.end));
  local_44=(ushort *)((*(ushort **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_28=(undefined4 *)(&(*(ushort **)&scannerContext.state.current));
  local_1c=(undefined4 *)(&(*(ushort **)&scannerContext.state.current));
  local_24=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_2c=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_38=(int *)(&(*(uint *)&scannerContext.previous.current));
  local_40=(int *)((int *)&(*(ushort **)&scannerContext.state.current));
  local_20=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_34=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
LAB_004892d1:
  puVar13=(ushort *)(local_44);
  if (local_44 < puVar4) {
    if (local_44 < puVar4) {
      local_14=(ushort *)(local_44 + 1);
      uVar14=(uint)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8);
    }
    else {
      local_14=(ushort *)(puVar4);
      uVar14=(uint)(0);
    }
    if ((uVar14 == 9) || (uVar14 - 0xb < 2) || (uVar14 == 0x1a) || (uVar14 == 0x20))
    goto LAB_00489310;
    if (uVar14 == 0x5c) {
      if (local_14 < puVar4) {
        puVar9=(ushort *)(local_14 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8));
      }
      else {
        local_18=(undefined4 *)((undefined4 *)0x0);
        puVar9=(ushort *)(puVar4);
      }
      if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa)) goto LAB_00489423;
      local_44=(ushort *)(puVar9);
      if (local_18 == (undefined4 *)0xd) {
        if (puVar9 < puVar4) {
          local_14=(ushort *)(puVar9 + 1);
          uVar14=(uint)((*puVar9 & 0xff) << 8 | (int)(uint)*puVar9 >> 8);
        }
        else {
          uVar14=(uint)(0);
          local_14=(ushort *)(puVar4);
        }
        if (uVar14 == 10) {
          local_44=(ushort *)(local_14);
        }
      }
      puVar13=(ushort *)(local_44);
      if ((*(ushort **)&scannerContext.state.line) < local_44) {
        (*(ushort **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar14=(uint)(0);
        }
        else {
          uVar14=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar14 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar13;
      goto LAB_004892d1;
    }
  }
LAB_00489423:
  (*(ushort **)&scannerContext.state.current) = local_44;
  *local_2c = *local_1c;
  local_2c[1] = local_1c[1];
  local_2c[2] = local_1c[2];
  local_2c[3] = local_1c[3];
  piVar15=(int *)(local_38);
  if (local_38 == (int *)0x0) {
    piVar15=(int *)(local_40);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *piVar15 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = piVar15[3];
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  if (local_44 < puVar4) {
    local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
    local_44=(ushort *)(local_44 + 1);
  }
  else {
    local_44=(ushort *)(puVar4);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_18 == (undefined4 *)0x0) {
    if (scannerCharacterFlags[0] == '\0') {
      (*(ushort **)&scannerContext.state.current) = local_44;
      *param_1 = 0;
      goto LAB_0048a462;
    }
    goto LAB_00489d00;
  }
  if (local_44 + 3 < puVar4) {
    local_30=(undefined *)(local_34);
LAB_00489520:
    if ((scannerNative00725f3f != '\0') && (local_18 < (undefined4 *)0x10000)) {
      if ((*(byte *)(local_18 + 0x19fc00) & 1) != 0) {
switchD_00489574_caseD_41:
        puVar5=(undefined *)(local_20);
        puVar13=(ushort *)(local_44);
        goto LAB_0048a140;
      }
      if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) goto switchD_00489574_caseD_30;
      if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00489e16;
    }
    do {
      bVar1=(byte)(scannerUnicodeFlags[64]);
      switch((uint)local_18) {
      case 0x0:
        if (scannerCharacterFlags[0] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0;
        goto LAB_0048a462;
      default:
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 1) != 0))
        goto switchD_00489574_caseD_41;
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 0x10) == 0)) {
          if (local_18 < (undefined4 *)0x100) {
            if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00489d00;
            (*(ushort **)&scannerContext.state.current) = local_44;
            *param_1 = (short)local_18;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_00489d00;
            (*(ushort **)&scannerContext.state.current) = local_44;
            *param_1 = -6;
          }
          goto LAB_0048a462;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_00489574_caseD_30:
        puVar5=(undefined *)(local_30);
        puVar9=(ushort *)(local_44);
        while( true ) {
          local_44=(ushort *)(puVar9);
          puVar6=(undefined4 *)(local_18);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar8=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
          if (puVar4 <= local_44) break;
          local_14=(ushort *)(local_44 + 1);
          local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
          if ((local_18 > (undefined4 *)0x7f) ||
             (puVar9 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0 &&
             (((local_18 != (undefined4 *)0x2b && (local_18 != (undefined4 *)0x2d)) ||
              (puVar6 != (undefined4 *)0x45 &&
              (puVar6 != (undefined4 *)0x65 && (puVar6 != (undefined4 *)0x50) &&
              (puVar6 != (undefined4 *)0x70)))) && (local_18 != (undefined4 *)0x2e)))) break;
        }
        if ((local_18 < (undefined4 *)0x80) && (local_14 < puVar4) &&
           (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0)) goto switchD_00489574_caseD_1b;
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           (puVar6 > (undefined4 *)0x2f && (puVar6 < (undefined4 *)0x3a)) ||
           (puVar6 > (undefined4 *)0xffff ||
           (local_18 = puVar6, (*(byte *)(puVar6 + 0x19fc00) & 0x10) == 0))) {
          (*(ushort **)&scannerContext.state.current) = local_44;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048a440;
        }
        break;
      case 0xa:
      case 0xd:
        if ((local_18 == (undefined4 *)0xd) &&
           (local_14 = local_44 + 1, (ushort)(*local_44 << 8 | *local_44 >> 8) == 10)) {
          local_44=(ushort *)(local_14);
        }
        if ((*(ushort **)&scannerContext.state.line) < local_44) {
          (*(ushort **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar14=(uint)(0);
          }
          else {
            uVar14=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar14 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_0048a440;
      case 0x1b:
        goto switchD_00489574_caseD_1b;
      case 0x21:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[33] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x21;
        goto LAB_0048a462;
      case 0x22:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) goto LAB_0048a310;
      case 0x27:
        if (local_18 == (undefined4 *)0x27) {
          sVar7=(short)(-9);
        }
        else {
          sVar7=(short)(-0xc);
        }
        *param_1 = sVar7;
        goto LAB_0048a2a0;
      case 0x23:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x23) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[35] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x23;
        goto LAB_0048a462;
      case 0x25:
        puVar9=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = puVar9;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_14=(ushort *)(local_44 + 2);
          local_18=(undefined4 *)((undefined4 *)((*puVar9 & 0xff) << 8 | (int)(uint)*puVar9 >> 8));
          if (local_18 == (undefined4 *)0x25) {
            local_18=(undefined4 *)((undefined4 *)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8));
            if (local_18 == (undefined4 *)0x3a) {
              (*(ushort **)&scannerContext.state.current) = local_44 + 3;
              *param_1 = -0x12;
              *(undefined **)(param_1 + 2) = &scannerNative0067de55;
              param_1[4] = 4;
              param_1[5] = 0;
              goto LAB_0048a440;
            }
            uVar14=(uint)((uint)local_44[3]);
            bVar1 = (&scannerFastUnicodeFlags[0])
                    [(((uVar14 & 0xff) << 8 | (int)uVar14 >> 8) ^ (int)local_18 << 7) & 0x3fff];
          }
          else {
            bVar1 = (&scannerFastUnicodeFlags[0])
                    [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) &
                     0x3fff];
          }
          local_44=(ushort *)(puVar9);
          if ((bVar1 & 1) != 0) goto switchD_00489574_caseD_1b;
          (*(ushort **)&scannerContext.state.current) = puVar9;
          *param_1 = 0x23;
          *(undefined **)(param_1 + 2) = &scannerNative0067de51;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(ushort **)&scannerContext.state.current) = puVar9;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        local_14=(ushort *)(puVar9);
        if (((&scannerFastUnicodeFlags[0])
             [(((*puVar9 & 0xff) << 8 | (int)(uint)*puVar9 >> 8) ^ (int)local_18 << 7) & 0x3fff] & 1
            ) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[37] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x25;
        goto LAB_0048a462;
      case 0x26:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x26) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[38] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x26;
        goto LAB_0048a462;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = (short)local_18;
        goto LAB_0048a462;
      case 0x2a:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[42] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2a;
        goto LAB_0048a462;
      case 0x2b:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x2b) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[43] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2b;
        goto LAB_0048a462;
      case 0x2d:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x3e) {
          local_18=(undefined4 *)((undefined4 *)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8));
          if ((scannerNative0070f1a8 == '\0') || (local_18 != (undefined4 *)0x2a)) {
            uVar14=(uint)((uint)local_44[2]);
            if (((&scannerFastUnicodeFlags[0])
                 [(((uVar14 & 0xff) << 8 | (int)uVar14 >> 8) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
                0) goto switchD_00489574_caseD_1b;
            (*(ushort **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            (*(ushort **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_0048a440;
        }
        if (local_18 == (undefined4 *)0x2d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[45] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2d;
        goto LAB_0048a462;
      case 0x2e:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x2e) {
          local_18=(undefined4 *)((undefined4 *)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8));
          if (local_18 == (undefined4 *)0x2e) {
            (*(ushort **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            goto LAB_0048a440;
          }
          uVar14=(uint)((uint)local_44[2]);
          bVar1 = (&scannerFastUnicodeFlags[0])
                  [(((uVar14 & 0xff) << 8 | (int)uVar14 >> 8) ^ (int)local_18 << 7) & 0x3fff];
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x2a)) {
            (*(ushort **)&scannerContext.state.current) = local_14;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            goto LAB_0048a440;
          }
          if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) {
            local_18=(undefined4 *)((undefined4 *)0x2e);
            goto switchD_00489574_caseD_30;
          }
          bVar1 = (&scannerFastUnicodeFlags[0])
                  [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) &
                   0x3fff];
        }
        if ((bVar1 & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[46] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2e;
        goto LAB_0048a462;
      case 0x2f:
        local_14=(ushort *)(local_44 + 1);
        scannerCommentBuffer.length = 0;
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_00489e16;
          if (scannerNative0070f1ca != '\0') goto LAB_00489e16;
          if (scannerNative0070f1af == '\0') goto LAB_00489e16;
        }
        if (local_18 == (undefined4 *)0x2a) {
          local_3c=(undefined4 *)((undefined4 *)0x0);
          local_30=(undefined *)(local_34);
          local_44=(ushort *)(local_14);
          goto LAB_0048af50;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[47] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x2f;
        goto LAB_0048a462;
      case 0x3a:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x3a)) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[58] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3a;
        goto LAB_0048a462;
      case 0x3c:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) {
LAB_0048a310:
          if (local_18 == (undefined4 *)0x3c) {
            cVar12=(char)('>');
          }
          else {
            cVar12=(char)('\"');
          }
          local_1c=(undefined4 *)((undefined4 *)(int)cVar12);
          goto LAB_0048a330;
        }
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (local_18 == (undefined4 *)0x3c) {
          local_18=(undefined4 *)((undefined4 *)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8));
          if (local_18 == (undefined4 *)0x3d) {
            (*(ushort **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            uVar14=(uint)((uint)local_44[2]);
            if (((&scannerFastUnicodeFlags[0])
                 [(((uVar14 & 0xff) << 8 | (int)uVar14 >> 8) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
                0) goto switchD_00489574_caseD_1b;
            (*(ushort **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_0048a440;
        }
        if ((local_18 == (undefined4 *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[60] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3c;
        goto LAB_0048a462;
      case 0x3d:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[61] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3d;
        goto LAB_0048a462;
      case 0x3e:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (local_18 == (undefined4 *)0x3e) {
          local_18=(undefined4 *)((undefined4 *)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8));
          if (local_18 == (undefined4 *)0x3d) {
            (*(ushort **)&scannerContext.state.current) = local_44 + 2;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            uVar14=(uint)((uint)local_44[2]);
            if (((&scannerFastUnicodeFlags[0])
                 [(((uVar14 & 0xff) << 8 | (int)uVar14 >> 8) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
                0) goto switchD_00489574_caseD_1b;
            (*(ushort **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[62] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x3e;
        goto LAB_0048a462;
      case 0x3f:
        goto switchD_00489574_caseD_3f;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_44),(char *)(puVar4),(char **)(&local_14),(ScanWord *)(&local_18));
          (*(ushort **)&scannerContext.state.current) = local_44;
          scannerUnicodeFlags[64] = bVar1;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048a440;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x40;
        goto LAB_0048a462;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_00489574_caseD_41;
      case 0x5c:
        if (local_44 < puVar4) {
          local_14=(ushort *)(local_44 + 1);
          local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        }
        else {
          local_14=(ushort *)(puVar4);
          local_18=(undefined4 *)((undefined4 *)0x0);
        }
        if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa))
        goto switchD_00489574_caseD_1b;
        local_44=(ushort *)(local_14);
        if (local_18 == (undefined4 *)0xd) {
          if (local_14 < puVar4) {
            uVar14=(uint)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8);
            local_14=(ushort *)(local_14 + 1);
          }
          else {
            local_14=(ushort *)(puVar4);
            uVar14=(uint)(0);
          }
          if (uVar14 == 10) {
            local_44=(ushort *)(local_14);
          }
        }
        puVar13=(ushort *)(local_44);
        if ((*(ushort **)&scannerContext.state.line) < local_44) {
          (*(ushort **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar14=(uint)(0);
          }
          else {
            uVar14=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar14 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(ushort **)&scannerContext.state.current) = puVar13;
        goto LAB_004892d1;
      case 0x5e:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[94] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x5e;
        goto LAB_0048a462;
      case 0x7c:
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
        if (local_18 == (undefined4 *)0x7c) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(ushort **)&scannerContext.state.current) = local_14;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048a440;
        }
        if (((&scannerFastUnicodeFlags[0])
             [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff]
            & 1) != 0) goto switchD_00489574_caseD_1b;
        if (scannerCharacterFlags[124] != '\0') goto LAB_00489d00;
        (*(ushort **)&scannerContext.state.current) = local_44;
        *param_1 = 0x7c;
        goto LAB_0048a462;
      }
    } while( true );
  }
  goto switchD_00489574_caseD_1b;
LAB_00489310:
  local_44=(ushort *)(local_14);
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  goto LAB_004892d1;
switchD_00489574_caseD_3f:
  if ((scannerNative0070f072 == '\0') ||
     (local_14 = local_44 + 1, (ushort)(*local_44 << 8 | *local_44 >> 8) != 0x3f))
  goto switchD_004896c0_caseD_22;
  puVar9=(ushort *)(local_44 + 2);
  switch((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) {
  case 0x21:
    local_18=(undefined4 *)((undefined4 *)0x7c);
    local_44=(ushort *)(puVar9);
    goto LAB_00489520;
  default:
    goto switchD_004896c0_caseD_22;
  case 0x27:
    local_18=(undefined4 *)((undefined4 *)0x5e);
    local_44=(ushort *)(puVar9);
    goto LAB_00489520;
  case 0x28:
    local_18=(undefined4 *)((undefined4 *)0x5b);
    local_44=(ushort *)(puVar9);
    goto switchD_004896c0_caseD_22;
  case 0x29:
    local_18=(undefined4 *)((undefined4 *)0x5d);
    local_44=(ushort *)(puVar9);
    goto switchD_004896c0_caseD_22;
  case 0x2d:
    local_18=(undefined4 *)((undefined4 *)0x7e);
    local_44=(ushort *)(puVar9);
    goto switchD_004896c0_caseD_22;
  case 0x2f:
    if (puVar9 < puVar4) {
      local_14=(ushort *)(local_44 + 3);
      local_18=(undefined4 *)((undefined4 *)((*puVar9 & 0xff) << 8 | (int)(uint)*puVar9 >> 8));
    }
    else {
      local_18=(undefined4 *)((undefined4 *)0x0);
      local_14=(ushort *)(puVar4);
    }
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      local_44=(ushort *)(local_14);
      if (local_18 == (undefined4 *)0xd) {
        if (local_14 < puVar4) {
          uVar14=(uint)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8);
          local_14=(ushort *)(local_14 + 1);
        }
        else {
          local_14=(ushort *)(puVar4);
          uVar14=(uint)(0);
        }
        if (uVar14 == 10) {
          local_44=(ushort *)(local_14);
        }
      }
      puVar13=(ushort *)(local_44);
      if ((*(ushort **)&scannerContext.state.line) < local_44) {
        (*(ushort **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar14=(uint)(0);
        }
        else {
          uVar14=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar14 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar13;
      goto LAB_004892d1;
    }
    local_18=(undefined4 *)((undefined4 *)0x5c);
    local_44=(ushort *)(puVar9);
    goto LAB_00489520;
  case 0x3c:
    local_18=(undefined4 *)((undefined4 *)0x7b);
    local_44=(ushort *)(puVar9);
    goto switchD_004896c0_caseD_22;
  case 0x3d:
    local_18=(undefined4 *)((undefined4 *)0x23);
    local_44=(ushort *)(puVar9);
    goto LAB_00489520;
  case 0x3e:
    break;
  }
  local_18=(undefined4 *)((undefined4 *)0x7d);
  local_44=(ushort *)(puVar9);
switchD_004896c0_caseD_22:
  if (*(char *)(local_18 + 0x1a3c00) == '\0') {
    (*(ushort **)&scannerContext.state.current) = local_44;
    *param_1 = (short)local_18;
LAB_0048a462:
    scannerNative00716ebc = (undefined1)*param_1;
    *(undefined1 **)(param_1 + 2) = &scannerNative00716ebc;
    param_1[4] = 1;
    param_1[5] = 0;
    *(int *)(param_1 + 0xc) = (int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
    return *param_1;
  }
LAB_00489d00:
  local_14=(ushort *)(local_44);
LAB_00489db0:
  if (scannerNative0070f071 != '\0') {
    iVar8 = (int)((((int)local_44 - (int)puVar13) + 1U) -
                 (uint)((uint)((int)local_44 - (int)puVar13) < 0x80000000)) >> 1;
    puVar9=(ushort *)(puVar13);
    iVar3=(int)(scannerLiteralBuffer.length);
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar8) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar8);
      iVar3=(int)(scannerLiteralBuffer.length);
    }
    for (; puVar13 = local_44, scannerLiteralBuffer.length = iVar3, iVar8 != 0; iVar8 = iVar8 - 1) {
      scannerLiteralBuffer.length = iVar3 + 1;
      *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar9;
      puVar9=(ushort *)((ushort *)((int)puVar9 + 1));
      iVar3=(int)(scannerLiteralBuffer.length);
    }
  }
  if (local_44 < puVar4) {
LAB_00489e16:
    do {
      if (local_44 < puVar4) {
        local_14=(ushort *)(local_44 + 1);
        local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
      }
      else {
        local_14=(ushort *)(puVar4);
        local_18=(undefined4 *)((undefined4 *)0x0);
      }
      if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa) ||
         (local_18 == (undefined4 *)0x0)) goto LAB_00489e78;
      local_44=(ushort *)(local_14);
      if (local_18 != (undefined4 *)0x5c) break;
      if (local_14 < puVar4) {
        puVar9=(ushort *)(local_14 + 1);
        uVar14=(uint)((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8);
      }
      else {
        uVar14=(uint)(0);
        puVar9=(ushort *)(puVar4);
      }
      if ((uVar14 == 0xd) || (uVar14 == 10)) {
        local_44=(ushort *)(puVar9);
        if (uVar14 == 0xd) {
          if (puVar9 < puVar4) {
            puVar11=(ushort *)(puVar9 + 1);
            uVar14=(uint)((*puVar9 & 0xff) << 8 | (int)(uint)*puVar9 >> 8);
          }
          else {
            uVar14=(uint)(0);
            puVar11=(ushort *)(puVar4);
          }
          if (uVar14 == 10) {
            local_44=(ushort *)(puVar11);
          }
        }
        puVar9=(ushort *)(local_44);
        if ((*(ushort **)&scannerContext.state.line) < local_44) {
          (*(ushort **)&scannerContext.state.line) = local_44;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar14=(uint)(0);
          }
          else {
            uVar14=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar14 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        bVar2=(bool)(true);
        (*(ushort **)&scannerContext.state.current) = puVar9;
      }
      else {
        bVar2=(bool)(false);
      }
    } while (bVar2);
    goto LAB_00489db0;
  }
LAB_00489e78:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 != '\0') {
    (*(ushort **)&scannerContext.state.current) = local_44;
    *param_1 = -0x11;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
    *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
    *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
    goto LAB_0048a440;
  }
  (*(ushort **)&scannerContext.state.current) = local_44;
  goto LAB_004892d1;
LAB_0048af50:
  if (local_44 < puVar4) {
    local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
    local_44=(ushort *)(local_44 + 1);
  }
  else {
    local_44=(ushort *)(puVar4);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if ((local_18 == (undefined4 *)0x2f) && (local_3c == (undefined4 *)0x2a)) goto LAB_0048b08e;
  if (local_18 != (undefined4 *)0x0) {
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      if (local_18 == (undefined4 *)0xd) {
        if (local_44 < puVar4) {
          local_14=(ushort *)(local_44 + 1);
          uVar14=(uint)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8);
        }
        else {
          local_14=(ushort *)(puVar4);
          uVar14=(uint)(0);
        }
        if (uVar14 == 10) {
          local_44=(ushort *)(local_14);
        }
      }
      puVar9=(ushort *)(local_44);
      if ((*(ushort **)&scannerContext.state.line) < local_44) {
        (*(ushort **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar14=(uint)(0);
        }
        else {
          uVar14=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar14 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar9;
      local_18=(undefined4 *)((undefined4 *)0xa);
      goto LAB_0048b000;
    }
    if (local_18 != (undefined4 *)0x5c) goto LAB_0048b000;
    if (local_44 < puVar4) {
      puVar9=(ushort *)(local_44 + 1);
      uVar14=(uint)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8);
    }
    else {
      uVar14=(uint)(0);
      puVar9=(ushort *)(puVar4);
    }
    if ((uVar14 == 0xd) || (uVar14 == 10)) {
      local_44=(ushort *)(puVar9);
      if (uVar14 == 0xd) {
        if (puVar9 < puVar4) {
          puVar11=(ushort *)(puVar9 + 1);
          uVar14=(uint)((*puVar9 & 0xff) << 8 | (int)(uint)*puVar9 >> 8);
        }
        else {
          uVar14=(uint)(0);
          puVar11=(ushort *)(puVar4);
        }
        if (uVar14 == 10) {
          local_44=(ushort *)(puVar11);
        }
      }
      puVar9=(ushort *)(local_44);
      if ((*(ushort **)&scannerContext.state.line) < local_44) {
        (*(ushort **)&scannerContext.state.line) = local_44;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar14=(uint)(0);
        }
        else {
          uVar14=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar14 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_44 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      bVar2=(bool)(true);
      (*(ushort **)&scannerContext.state.current) = puVar9;
    }
    else {
      bVar2=(bool)(false);
    }
    if (!bVar2) {
LAB_0048b000:
      local_3c=(undefined4 *)(local_18);
      if (scannerNative0070f071 != '\0') {
        iVar8 = (int)((((int)local_44 - (int)puVar13) + 1U) -
                     (uint)((uint)((int)local_44 - (int)puVar13) < 0x80000000)) >> 1;
        puVar9=(ushort *)(puVar13);
        iVar3=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar8) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar8);
          iVar3=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar13 = local_44, scannerLiteralBuffer.length = iVar3, iVar8 != 0; iVar8 = iVar8 - 1) {
          scannerLiteralBuffer.length = iVar3 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar9;
          puVar9=(ushort *)((ushort *)((int)puVar9 + 1));
          iVar3=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_0048af50;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 4),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_0048b08e:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(ushort **)&scannerContext.state.current) = local_44;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_004892d1;
  }
  if (local_18 == (undefined4 *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar8=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = 0x2f;
  }
  (*(ushort **)&scannerContext.state.current) = local_44;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_0048a440;
LAB_0048a330:
  if (local_44 < puVar4) {
    local_14=(ushort *)(local_44 + 1);
    local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
  }
  else {
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_1c == local_18) goto LAB_0048b896;
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < puVar4 &&
     (((&scannerFastUnicodeFlags[0])
       [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff] & 1)
      != 0))) goto switchD_00489574_caseD_1b;
  if ((local_18 == (undefined4 *)0x0) ||
     (local_18 == (undefined4 *)0xd || (local_18 == (undefined4 *)0xa))) goto LAB_0048b7f1;
  local_44=(ushort *)(local_14);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar8=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
  goto LAB_0048a330;
LAB_0048b7f1:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(ushort **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_0048b896:
  (*(ushort **)&scannerContext.state.current) = local_14;
  if (local_1c == (undefined4 *)0x3e) {
    sVar7=(short)(-0x10);
  }
  else {
    sVar7=(short)(-0xf);
  }
  *param_1 = sVar7;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_0048a440;
LAB_0048a140:
  local_44=(ushort *)(puVar13);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar8=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
  if (puVar4 <= local_44) goto LAB_0048b484;
  local_14=(ushort *)(local_44 + 1);
  local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
  if ((local_18 > (undefined4 *)0x7f) ||
     (puVar13 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0)) goto LAB_0048b484;
  goto LAB_0048a140;
LAB_0048b484:
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < puVar4 &&
     (((&scannerFastUnicodeFlags[0])
       [(((*local_14 & 0xff) << 8 | (int)(uint)*local_14 >> 8) ^ (int)local_18 << 7) & 0x3fff] & 2)
      != 0))) {
switchD_00489574_caseD_1b:
    *local_28 = *local_24;
    local_28[1] = local_24[1];
    local_28[2] = local_24[2];
    local_28[3] = local_24[3];
    sVar7=(short)(fn_00495aa0((ScanToken *)(param_1)));
    return sVar7;
  }
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_18 == (undefined4 *)0x27) {
    sVar7=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar7;
    if (*param_1 != 0) {
      local_44=(ushort *)(local_14);
      scannerLiteralBuffer.length = 0;
LAB_0048a2a0:
      do {
        puVar6=(undefined4 *)(local_18);
        if (local_44 < puVar4) {
          puVar10=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
          local_44=(ushort *)(local_44 + 1);
        }
        else {
          local_44=(ushort *)(puVar4);
          puVar10=(undefined4 *)((undefined4 *)0x0);
        }
        if (local_18 == puVar10) {
          (*(ushort **)&scannerContext.state.current) = local_44;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048a440;
        }
        local_18=(undefined4 *)(puVar10);
        if ((puVar10 > (undefined4 *)0x7f) ||
           ((local_44 < puVar4 &&
            (((&scannerFastUnicodeFlags[0])
              [(((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8) ^ (int)puVar10 << 7) & 0x3fff]
             & 4) != 0)) || (puVar10 == (undefined4 *)0x0))) goto switchD_00489574_caseD_1b;
        if (puVar10 == (undefined4 *)0x5c) {
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar8=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
          if (local_44 < puVar4) {
            local_18=(undefined4 *)((undefined4 *)((*local_44 & 0xff) << 8 | (int)(uint)*local_44 >> 8));
            local_44=(ushort *)(local_44 + 1);
          }
          else {
            local_44=(ushort *)(puVar4);
            local_18=(undefined4 *)((undefined4 *)0x0);
          }
        }
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
        }
        iVar8=(int)(scannerLiteralBuffer.length);
        scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
        *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
        local_18=(undefined4 *)(puVar6);
      } while( true );
    }
  }
  else if (local_18 == (undefined4 *)0x22) {
    sVar7=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar7;
    if (*param_1 != 0) {
      local_44=(ushort *)(local_14);
      scannerLiteralBuffer.length = 0;
      goto LAB_0048a2a0;
    }
  }
  (*(ushort **)&scannerContext.state.current) = local_44;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_0048a440:
  *(int *)(param_1 + 0xc) = (int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_0048b990(ScanToken *token)
{
 short *param_1=(short *)token;
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint *puVar4;
  undefined *puVar5;
  short sVar6;
  int iVar7;
  char cVar8;
  uint uVar9;
  uint *puVar10;
  undefined4 *puVar11;
  uint *puVar12;
  uint *puVar13;
  int *piVar14;
  undefined4 *puVar15;
  uint *local_40;
  int *local_3c;
  int *local_38;
  undefined *local_34;
  undefined *local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined *local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  uint *local_14;
  puVar4=(uint *)((*(uint **)&scannerContext.end));
  local_40=(uint *)((*(uint **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_28=(undefined4 *)(&(*(uint **)&scannerContext.state.current));
  local_1c=(undefined4 *)(&(*(uint **)&scannerContext.state.current));
  local_24=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_2c=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_38=(int *)(&(*(uint *)&scannerContext.previous.current));
  local_3c=(int *)((int *)&(*(uint **)&scannerContext.state.current));
  local_20=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_34=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
LAB_0048b9f1:
  puVar13=(uint *)(local_40);
  if (local_40 < puVar4) {
    if (local_40 < puVar4) {
      local_14=(uint *)(local_40 + 1);
      uVar9=(uint)(*local_40);
    }
    else {
      local_14=(uint *)(puVar4);
      uVar9=(uint)(0);
    }
    if ((uVar9 == 9) || (uVar9 - 0xb < 2) || (uVar9 == 0x1a) || (uVar9 == 0x20)) goto LAB_0048ba30;
    if (uVar9 == 0x5c) {
      if (local_14 < puVar4) {
        puVar10=(uint *)(local_14 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_14);
      }
      else {
        local_18=(undefined4 *)((undefined4 *)0x0);
        puVar10=(uint *)(puVar4);
      }
      if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa)) goto LAB_0048bb20;
      local_40=(uint *)(puVar10);
      if (local_18 == (undefined4 *)0xd) {
        if (puVar10 < puVar4) {
          local_14=(uint *)(puVar10 + 1);
          uVar9=(uint)(*puVar10);
        }
        else {
          uVar9=(uint)(0);
          local_14=(uint *)(puVar4);
        }
        if (uVar9 == 10) {
          local_40=(uint *)(local_14);
        }
      }
      puVar13=(uint *)(local_40);
      if ((*(uint **)&scannerContext.state.line) < local_40) {
        (*(uint **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar9=(uint)(0);
        }
        else {
          uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar9 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(uint **)&scannerContext.state.current) = puVar13;
      goto LAB_0048b9f1;
    }
  }
LAB_0048bb20:
  (*(uint **)&scannerContext.state.current) = local_40;
  *local_2c = *local_1c;
  local_2c[1] = local_1c[1];
  local_2c[2] = local_1c[2];
  local_2c[3] = local_1c[3];
  piVar14=(int *)(local_38);
  if (local_38 == (int *)0x0) {
    piVar14=(int *)(local_3c);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *piVar14 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = piVar14[3];
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  if (local_40 < puVar4) {
    local_18=(undefined4 *)((undefined4 *)*local_40);
    local_40=(uint *)(local_40 + 1);
  }
  else {
    local_40=(uint *)(puVar4);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_18 == (undefined4 *)0x0) {
    if (scannerCharacterFlags[0] == '\0') {
      (*(uint **)&scannerContext.state.current) = local_40;
      *param_1 = 0;
      goto LAB_0048c922;
    }
    goto LAB_0048c2c4;
  }
  if (local_40 + 3 < puVar4) {
    local_30=(undefined *)(local_34);
LAB_0048bc18:
    if ((scannerNative00725f3f != '\0') && (local_18 < (undefined4 *)0x10000)) {
      if ((*(byte *)(local_18 + 0x19fc00) & 1) != 0) {
switchD_0048bc6c_caseD_41:
        puVar5=(undefined *)(local_20);
        puVar13=(uint *)(local_40);
        goto LAB_0048c644;
      }
      if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) goto switchD_0048bc6c_caseD_30;
      if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_0048c3b5;
    }
    do {
      bVar1=(byte)(scannerUnicodeFlags[64]);
      switch((uint)local_18) {
      case 0x0:
        if (scannerCharacterFlags[0] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0;
        goto LAB_0048c922;
      default:
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 1) != 0))
        goto switchD_0048bc6c_caseD_41;
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 0x10) == 0)) {
          if (local_18 < (undefined4 *)0x100) {
            if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_0048c2c4;
            (*(uint **)&scannerContext.state.current) = local_40;
            *param_1 = (short)local_18;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_0048c2c4;
            (*(uint **)&scannerContext.state.current) = local_40;
            *param_1 = -6;
          }
          goto LAB_0048c922;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_0048bc6c_caseD_30:
        puVar5=(undefined *)(local_30);
        puVar10=(uint *)(local_40);
        while( true ) {
          local_40=(uint *)(puVar10);
          puVar15=(undefined4 *)(local_18);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar7=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_18+0));
          if (puVar4 <= local_40) break;
          local_14=(uint *)(local_40 + 1);
          local_18=(undefined4 *)((undefined4 *)*local_40);
          if ((local_18 > (undefined4 *)0x7f) ||
             (puVar10 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0 &&
             (((local_18 != (undefined4 *)0x2b && (local_18 != (undefined4 *)0x2d)) ||
              (puVar15 != (undefined4 *)0x45 &&
              (puVar15 != (undefined4 *)0x65 && (puVar15 != (undefined4 *)0x50) &&
              (puVar15 != (undefined4 *)0x70)))) && (local_18 != (undefined4 *)0x2e)))) break;
        }
        if ((local_18 < (undefined4 *)0x80) && (local_14 < puVar4) &&
           (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0))
        goto switchD_0048bc6c_caseD_1b;
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           (puVar15 > (undefined4 *)0x2f && (puVar15 < (undefined4 *)0x3a)) ||
           (puVar15 > (undefined4 *)0xffff ||
           (local_18 = puVar15, (*(byte *)(puVar15 + 0x19fc00) & 0x10) == 0))) {
          (*(uint **)&scannerContext.state.current) = local_40;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048c900;
        }
        break;
      case 0xa:
      case 0xd:
        if ((local_18 == (undefined4 *)0xd) && (local_14 = local_40 + 1, *local_40 == 10)) {
          local_40=(uint *)(local_14);
        }
        if ((*(uint **)&scannerContext.state.line) < local_40) {
          (*(uint **)&scannerContext.state.line) = local_40;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar9=(uint)(0);
          }
          else {
            uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar9 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_0048c900;
      case 0x1b:
        goto switchD_0048bc6c_caseD_1b;
      case 0x21:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[33] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x21;
        goto LAB_0048c922;
      case 0x22:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) goto LAB_0048c7e0;
      case 0x27:
        if (local_18 == (undefined4 *)0x27) {
          sVar6=(short)(-9);
        }
        else {
          sVar6=(short)(-0xc);
        }
        *param_1 = sVar6;
        goto LAB_0048c781;
      case 0x23:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x23) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[35] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x23;
        goto LAB_0048c922;
      case 0x25:
        puVar10=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = puVar10;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_14=(uint *)(local_40 + 2);
          local_18=(undefined4 *)((undefined4 *)*puVar10);
          if (local_18 == (undefined4 *)0x25) {
            local_18=(undefined4 *)((undefined4 *)*local_14);
            if (local_18 == (undefined4 *)0x3a) {
              (*(uint **)&scannerContext.state.current) = local_40 + 3;
              *param_1 = -0x12;
              *(undefined **)(param_1 + 2) = &scannerNative0067de55;
              param_1[4] = 4;
              param_1[5] = 0;
              goto LAB_0048c900;
            }
            bVar1=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ local_40[3]) & 0x3fff]);
          }
          else {
            bVar1=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff]);
          }
          local_40=(uint *)(puVar10);
          if ((bVar1 & 1) != 0) goto switchD_0048bc6c_caseD_1b;
          (*(uint **)&scannerContext.state.current) = puVar10;
          *param_1 = 0x23;
          *(undefined **)(param_1 + 2) = &scannerNative0067de51;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(uint **)&scannerContext.state.current) = puVar10;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        local_14=(uint *)(puVar10);
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *puVar10) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[37] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x25;
        goto LAB_0048c922;
      case 0x26:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x26) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[38] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x26;
        goto LAB_0048c922;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = (short)local_18;
        goto LAB_0048c922;
      case 0x2a:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[42] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2a;
        goto LAB_0048c922;
      case 0x2b:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x2b) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[43] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2b;
        goto LAB_0048c922;
      case 0x2d:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x3e) {
          local_18=(undefined4 *)((undefined4 *)*local_14);
          if ((scannerNative0070f1a8 == '\0') || (local_18 != (undefined4 *)0x2a)) {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ local_40[2]) & 0x3fff] & 1) != 0)
            goto switchD_0048bc6c_caseD_1b;
            (*(uint **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            (*(uint **)&scannerContext.state.current) = local_40 + 2;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_0048c900;
        }
        if (local_18 == (undefined4 *)0x2d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[45] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2d;
        goto LAB_0048c922;
      case 0x2e:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x2e) {
          local_18=(undefined4 *)((undefined4 *)*local_14);
          if (local_18 == (undefined4 *)0x2e) {
            (*(uint **)&scannerContext.state.current) = local_40 + 2;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            goto LAB_0048c900;
          }
          bVar1=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ local_40[2]) & 0x3fff]);
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x2a)) {
            (*(uint **)&scannerContext.state.current) = local_14;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            goto LAB_0048c900;
          }
          if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) {
            local_18=(undefined4 *)((undefined4 *)0x2e);
            goto switchD_0048bc6c_caseD_30;
          }
          bVar1=(byte)((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff]);
        }
        if ((bVar1 & 1) != 0) goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[46] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2e;
        goto LAB_0048c922;
      case 0x2f:
        local_14=(uint *)(local_40 + 1);
        scannerCommentBuffer.length = 0;
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_0048c3b5;
          if (scannerNative0070f1ca != '\0') goto LAB_0048c3b5;
          if (scannerNative0070f1af == '\0') goto LAB_0048c3b5;
        }
        if (local_18 == (undefined4 *)0x2a) {
          puVar15=(undefined4 *)((undefined4 *)0x0);
          local_30=(undefined *)(local_34);
          local_40=(uint *)(local_14);
          goto LAB_0048d2f1;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[47] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2f;
        goto LAB_0048c922;
      case 0x3a:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x3a)) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[58] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3a;
        goto LAB_0048c922;
      case 0x3c:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) {
LAB_0048c7e0:
          if (local_18 == (undefined4 *)0x3c) {
            cVar8=(char)('>');
          }
          else {
            cVar8=(char)('\"');
          }
          local_1c=(undefined4 *)((undefined4 *)(int)cVar8);
          goto LAB_0048c800;
        }
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (local_18 == (undefined4 *)0x3c) {
          local_18=(undefined4 *)((undefined4 *)*local_14);
          if (local_18 == (undefined4 *)0x3d) {
            (*(uint **)&scannerContext.state.current) = local_40 + 2;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ local_40[2]) & 0x3fff] & 1) != 0)
            goto switchD_0048bc6c_caseD_1b;
            (*(uint **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_0048c900;
        }
        if ((local_18 == (undefined4 *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[60] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3c;
        goto LAB_0048c922;
      case 0x3d:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[61] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3d;
        goto LAB_0048c922;
      case 0x3e:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (local_18 == (undefined4 *)0x3e) {
          local_18=(undefined4 *)((undefined4 *)*local_14);
          if (local_18 == (undefined4 *)0x3d) {
            (*(uint **)&scannerContext.state.current) = local_40 + 2;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ local_40[2]) & 0x3fff] & 1) != 0)
            goto switchD_0048bc6c_caseD_1b;
            (*(uint **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[62] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3e;
        goto LAB_0048c922;
      case 0x3f:
        goto switchD_0048bc6c_caseD_3f;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_40),(char *)(puVar4),(char **)(&local_14),(ScanWord *)(&local_18));
          (*(uint **)&scannerContext.state.current) = local_40;
          scannerUnicodeFlags[64] = bVar1;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048c900;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x40;
        goto LAB_0048c922;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_0048bc6c_caseD_41;
      case 0x5c:
        if (local_40 < puVar4) {
          local_14=(uint *)(local_40 + 1);
          local_18=(undefined4 *)((undefined4 *)*local_40);
        }
        else {
          local_14=(uint *)(puVar4);
          local_18=(undefined4 *)((undefined4 *)0x0);
        }
        if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa))
        goto switchD_0048bc6c_caseD_1b;
        local_40=(uint *)(local_14);
        if (local_18 == (undefined4 *)0xd) {
          if (local_14 < puVar4) {
            uVar9=(uint)(*local_14);
            local_14=(uint *)(local_14 + 1);
          }
          else {
            local_14=(uint *)(puVar4);
            uVar9=(uint)(0);
          }
          if (uVar9 == 10) {
            local_40=(uint *)(local_14);
          }
        }
        puVar13=(uint *)(local_40);
        if ((*(uint **)&scannerContext.state.line) < local_40) {
          (*(uint **)&scannerContext.state.line) = local_40;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar9=(uint)(0);
          }
          else {
            uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar9 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(uint **)&scannerContext.state.current) = puVar13;
        goto LAB_0048b9f1;
      case 0x5e:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[94] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5e;
        goto LAB_0048c922;
      case 0x7c:
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
        if (local_18 == (undefined4 *)0x7c) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048c900;
        }
        if (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)
        goto switchD_0048bc6c_caseD_1b;
        if (scannerCharacterFlags[124] != '\0') goto LAB_0048c2c4;
        (*(uint **)&scannerContext.state.current) = local_40;
        *param_1 = 0x7c;
        goto LAB_0048c922;
      }
    } while( true );
  }
  goto switchD_0048bc6c_caseD_1b;
LAB_0048ba30:
  local_40=(uint *)(local_14);
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  goto LAB_0048b9f1;
switchD_0048bc6c_caseD_3f:
  if ((scannerNative0070f072 == '\0') || (local_14 = local_40 + 1, *local_40 != 0x3f))
  goto switchD_0048bd94_caseD_22;
  puVar10=(uint *)(local_40 + 2);
  switch(*local_14) {
  case 0x21:
    local_18=(undefined4 *)((undefined4 *)0x7c);
    local_40=(uint *)(puVar10);
    goto LAB_0048bc18;
  default:
    goto switchD_0048bd94_caseD_22;
  case 0x27:
    local_18=(undefined4 *)((undefined4 *)0x5e);
    local_40=(uint *)(puVar10);
    goto LAB_0048bc18;
  case 0x28:
    local_18=(undefined4 *)((undefined4 *)0x5b);
    local_40=(uint *)(puVar10);
    goto switchD_0048bd94_caseD_22;
  case 0x29:
    local_18=(undefined4 *)((undefined4 *)0x5d);
    local_40=(uint *)(puVar10);
    goto switchD_0048bd94_caseD_22;
  case 0x2d:
    local_18=(undefined4 *)((undefined4 *)0x7e);
    local_40=(uint *)(puVar10);
    goto switchD_0048bd94_caseD_22;
  case 0x2f:
    if (puVar10 < puVar4) {
      local_14=(uint *)(local_40 + 3);
      local_18=(undefined4 *)((undefined4 *)*puVar10);
    }
    else {
      local_18=(undefined4 *)((undefined4 *)0x0);
      local_14=(uint *)(puVar4);
    }
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      local_40=(uint *)(local_14);
      if (local_18 == (undefined4 *)0xd) {
        if (local_14 < puVar4) {
          uVar9=(uint)(*local_14);
          local_14=(uint *)(local_14 + 1);
        }
        else {
          local_14=(uint *)(puVar4);
          uVar9=(uint)(0);
        }
        if (uVar9 == 10) {
          local_40=(uint *)(local_14);
        }
      }
      puVar13=(uint *)(local_40);
      if ((*(uint **)&scannerContext.state.line) < local_40) {
        (*(uint **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar9=(uint)(0);
        }
        else {
          uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar9 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(uint **)&scannerContext.state.current) = puVar13;
      goto LAB_0048b9f1;
    }
    local_18=(undefined4 *)((undefined4 *)0x5c);
    local_40=(uint *)(puVar10);
    goto LAB_0048bc18;
  case 0x3c:
    local_18=(undefined4 *)((undefined4 *)0x7b);
    local_40=(uint *)(puVar10);
    goto switchD_0048bd94_caseD_22;
  case 0x3d:
    local_18=(undefined4 *)((undefined4 *)0x23);
    local_40=(uint *)(puVar10);
    goto LAB_0048bc18;
  case 0x3e:
    break;
  }
  local_18=(undefined4 *)((undefined4 *)0x7d);
  local_40=(uint *)(puVar10);
switchD_0048bd94_caseD_22:
  if (*(char *)(local_18 + 0x1a3c00) == '\0') {
    (*(uint **)&scannerContext.state.current) = local_40;
    *param_1 = (short)local_18;
LAB_0048c922:
    scannerNative007172c2 = (undefined1)*param_1;
    *(undefined1 **)(param_1 + 2) = &scannerNative007172c2;
    param_1[4] = 1;
    param_1[5] = 0;
    *(int *)(param_1 + 0xc) = (int)(*(uint **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
    return *param_1;
  }
LAB_0048c2c4:
  local_14=(uint *)(local_40);
LAB_0048c350:
  if (scannerNative0070f071 != '\0') {
    iVar7 = (int)(((int)local_40 - (int)puVar13) + ((int)local_40 - (int)puVar13 >> 0x1f & 3U)) >> 2
    ;
    puVar10=(uint *)(puVar13);
    iVar3=(int)(scannerLiteralBuffer.length);
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar7) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar7);
      iVar3=(int)(scannerLiteralBuffer.length);
    }
    for (; puVar13 = local_40, scannerLiteralBuffer.length = iVar3, iVar7 != 0; iVar7 = iVar7 - 1) {
      scannerLiteralBuffer.length = iVar3 + 1;
      *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar10;
      puVar10=(uint *)((uint *)((int)puVar10 + 1));
      iVar3=(int)(scannerLiteralBuffer.length);
    }
  }
  if (local_40 < puVar4) {
LAB_0048c3b5:
    do {
      if (local_40 < puVar4) {
        local_14=(uint *)(local_40 + 1);
        local_18=(undefined4 *)((undefined4 *)*local_40);
      }
      else {
        local_14=(uint *)(puVar4);
        local_18=(undefined4 *)((undefined4 *)0x0);
      }
      if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa) ||
         (local_18 == (undefined4 *)0x0)) goto LAB_0048c417;
      local_40=(uint *)(local_14);
      if (local_18 != (undefined4 *)0x5c) break;
      if (local_14 < puVar4) {
        puVar10=(uint *)(local_14 + 1);
        uVar9=(uint)(*local_14);
      }
      else {
        uVar9=(uint)(0);
        puVar10=(uint *)(puVar4);
      }
      if ((uVar9 == 0xd) || (uVar9 == 10)) {
        local_40=(uint *)(puVar10);
        if (uVar9 == 0xd) {
          if (puVar10 < puVar4) {
            puVar12=(uint *)(puVar10 + 1);
            uVar9=(uint)(*puVar10);
          }
          else {
            uVar9=(uint)(0);
            puVar12=(uint *)(puVar4);
          }
          if (uVar9 == 10) {
            local_40=(uint *)(puVar12);
          }
        }
        puVar10=(uint *)(local_40);
        if ((*(uint **)&scannerContext.state.line) < local_40) {
          (*(uint **)&scannerContext.state.line) = local_40;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar9=(uint)(0);
          }
          else {
            uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar9 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        bVar2=(bool)(true);
        (*(uint **)&scannerContext.state.current) = puVar10;
      }
      else {
        bVar2=(bool)(false);
      }
    } while (bVar2);
    goto LAB_0048c350;
  }
LAB_0048c417:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 != '\0') {
    (*(uint **)&scannerContext.state.current) = local_40;
    *param_1 = -0x11;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
    *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
    *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
    goto LAB_0048c900;
  }
  (*(uint **)&scannerContext.state.current) = local_40;
  goto LAB_0048b9f1;
LAB_0048d2f1:
  if (local_40 < puVar4) {
    local_18=(undefined4 *)((undefined4 *)*local_40);
    local_40=(uint *)(local_40 + 1);
  }
  else {
    local_40=(uint *)(puVar4);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if ((local_18 == (undefined4 *)0x2f) && (puVar15 == (undefined4 *)0x2a)) goto LAB_0048d42e;
  if (local_18 != (undefined4 *)0x0) {
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      if (local_18 == (undefined4 *)0xd) {
        if (local_40 < puVar4) {
          local_14=(uint *)(local_40 + 1);
          uVar9=(uint)(*local_40);
        }
        else {
          local_14=(uint *)(puVar4);
          uVar9=(uint)(0);
        }
        if (uVar9 == 10) {
          local_40=(uint *)(local_14);
        }
      }
      puVar10=(uint *)(local_40);
      if ((*(uint **)&scannerContext.state.line) < local_40) {
        (*(uint **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar9=(uint)(0);
        }
        else {
          uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar9 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(uint **)&scannerContext.state.current) = puVar10;
      local_18=(undefined4 *)((undefined4 *)0xa);
      goto LAB_0048d3a1;
    }
    if (local_18 != (undefined4 *)0x5c) goto LAB_0048d3a1;
    if (local_40 < puVar4) {
      puVar10=(uint *)(local_40 + 1);
      uVar9=(uint)(*local_40);
    }
    else {
      uVar9=(uint)(0);
      puVar10=(uint *)(puVar4);
    }
    if ((uVar9 == 0xd) || (uVar9 == 10)) {
      local_40=(uint *)(puVar10);
      if (uVar9 == 0xd) {
        if (puVar10 < puVar4) {
          puVar12=(uint *)(puVar10 + 1);
          uVar9=(uint)(*puVar10);
        }
        else {
          uVar9=(uint)(0);
          puVar12=(uint *)(puVar4);
        }
        if (uVar9 == 10) {
          local_40=(uint *)(puVar12);
        }
      }
      puVar10=(uint *)(local_40);
      if ((*(uint **)&scannerContext.state.line) < local_40) {
        (*(uint **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar9=(uint)(0);
        }
        else {
          uVar9=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar9 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      bVar2=(bool)(true);
      (*(uint **)&scannerContext.state.current) = puVar10;
    }
    else {
      bVar2=(bool)(false);
    }
    if (!bVar2) {
LAB_0048d3a1:
      puVar15=(undefined4 *)(local_18);
      if (scannerNative0070f071 != '\0') {
        iVar7 = (int)(((int)local_40 - (int)puVar13) + ((int)local_40 - (int)puVar13 >> 0x1f & 3U))
                >> 2;
        puVar10=(uint *)(puVar13);
        iVar3=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar7) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar7);
          iVar3=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar13 = local_40, scannerLiteralBuffer.length = iVar3, iVar7 != 0; iVar7 = iVar7 - 1) {
          scannerLiteralBuffer.length = iVar3 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar10;
          puVar10=(uint *)((uint *)((int)puVar10 + 1));
          iVar3=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_0048d2f1;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 8),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_0048d42e:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(uint **)&scannerContext.state.current) = local_40;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_0048b9f1;
  }
  if (local_18 == (undefined4 *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar7=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = 0x2f;
  }
  (*(uint **)&scannerContext.state.current) = local_40;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_0048c900;
LAB_0048c800:
  if (local_40 < puVar4) {
    local_14=(uint *)(local_40 + 1);
    local_18=(undefined4 *)((undefined4 *)*local_40);
  }
  else {
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_1c == local_18) goto LAB_0048dbc0;
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < puVar4 && (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 1) != 0)))
  goto switchD_0048bc6c_caseD_1b;
  if ((local_18 == (undefined4 *)0x0) ||
     (local_18 == (undefined4 *)0xd || (local_18 == (undefined4 *)0xa))) goto LAB_0048db30;
  local_40=(uint *)(local_14);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar7=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_18+0));
  goto LAB_0048c800;
LAB_0048db30:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_0048dbc0:
  (*(uint **)&scannerContext.state.current) = local_14;
  if (local_1c == (undefined4 *)0x3e) {
    sVar6=(short)(-0x10);
  }
  else {
    sVar6=(short)(-0xf);
  }
  *param_1 = sVar6;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_0048c900;
LAB_0048c644:
  local_40=(uint *)(puVar13);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar7=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_18+0));
  if (puVar4 <= local_40) goto LAB_0048d7f1;
  local_14=(uint *)(local_40 + 1);
  local_18=(undefined4 *)((undefined4 *)*local_40);
  if ((local_18 > (undefined4 *)0x7f) ||
     (puVar13 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0)) goto LAB_0048d7f1;
  goto LAB_0048c644;
LAB_0048d7f1:
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < puVar4 && (((&scannerFastUnicodeFlags[0])[((int)local_18 << 7 ^ *local_14) & 0x3fff] & 2) != 0)))
  {
switchD_0048bc6c_caseD_1b:
    *local_28 = *local_24;
    local_28[1] = local_24[1];
    local_28[2] = local_24[2];
    local_28[3] = local_24[3];
    sVar6=(short)(fn_00494070((ScanToken *)(param_1)));
    return sVar6;
  }
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_18 == (undefined4 *)0x27) {
    sVar6=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar6;
    if (*param_1 != 0) {
      local_40=(uint *)(local_14);
      scannerLiteralBuffer.length = 0;
LAB_0048c781:
      do {
        puVar15=(undefined4 *)(local_18);
        if (local_40 < puVar4) {
          puVar11=(undefined4 *)((undefined4 *)*local_40);
          local_40=(uint *)(local_40 + 1);
        }
        else {
          local_40=(uint *)(puVar4);
          puVar11=(undefined4 *)((undefined4 *)0x0);
        }
        if (local_18 == puVar11) {
          (*(uint **)&scannerContext.state.current) = local_40;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048c900;
        }
        local_18=(undefined4 *)(puVar11);
        if ((puVar11 > (undefined4 *)0x7f) ||
           ((local_40 < puVar4 &&
            (((&scannerFastUnicodeFlags[0])[((int)puVar11 << 7 ^ *local_40) & 0x3fff] & 4) != 0)) ||
           (puVar11 == (undefined4 *)0x0))) goto switchD_0048bc6c_caseD_1b;
        if (puVar11 == (undefined4 *)0x5c) {
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar7=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_18+0));
          if (local_40 < puVar4) {
            local_18=(undefined4 *)((undefined4 *)*local_40);
            local_40=(uint *)(local_40 + 1);
          }
          else {
            local_40=(uint *)(puVar4);
            local_18=(undefined4 *)((undefined4 *)0x0);
          }
        }
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
        }
        iVar7=(int)(scannerLiteralBuffer.length);
        scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
        *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_18+0));
        local_18=(undefined4 *)(puVar15);
      } while( true );
    }
  }
  else if (local_18 == (undefined4 *)0x22) {
    sVar6=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar6;
    if (*param_1 != 0) {
      local_40=(uint *)(local_14);
      scannerLiteralBuffer.length = 0;
      goto LAB_0048c781;
    }
  }
  (*(uint **)&scannerContext.state.current) = local_40;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_0048c900:
  *(int *)(param_1 + 0xc) = (int)(*(uint **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_0048dcc0(ScanToken *token)
{
 short *param_1=(short *)token;
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint *puVar4;
  undefined *puVar5;
  undefined4 *puVar6;
  short sVar7;
  int iVar8;
  uint *puVar9;
  char cVar10;
  undefined4 *puVar11;
  uint *puVar12;
  uint uVar13;
  int *piVar14;
  uint *local_4c;
  int *local_48;
  int *local_44;
  undefined4 *local_40;
  undefined4 *local_3c;
  undefined4 *local_38;
  uint *local_34;
  uint *local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined *local_1c;
  undefined4 *local_18;
  uint *local_14;
  puVar4=(uint *)((*(uint **)&scannerContext.end));
  local_4c=(uint *)((*(uint **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_24=(undefined4 *)(&(*(uint **)&scannerContext.state.current));
  local_20=(undefined4 *)(&(*(uint **)&scannerContext.state.current));
  local_28=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_38=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_44=(int *)(&(*(uint *)&scannerContext.previous.current));
  local_48=(int *)((int *)&(*(uint **)&scannerContext.state.current));
  local_1c=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_40=(undefined4 *)((undefined4 *)&(*(byte *)&scannerLiteralBuffer.grow));
LAB_0048dd21:
  puVar12=(uint *)(local_4c);
  if (local_4c < puVar4) {
    if (local_4c < puVar4) {
      local_14=(uint *)(local_4c + 1);
      uVar13=(uint)(*local_4c);
      uVar13=(uint)(uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
    }
    else {
      local_14=(uint *)(puVar4);
      uVar13=(uint)(0);
    }
    if ((uVar13 == 9) || (uVar13 - 0xb < 2) || (uVar13 == 0x1a) || (uVar13 == 0x20))
    goto LAB_0048dd60;
    if (uVar13 == 0x5c) {
      if (local_14 < puVar4) {
        uVar13=(uint)(*local_14);
        puVar9=(uint *)(local_14 + 1);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
      }
      else {
        local_18=(undefined4 *)((undefined4 *)0x0);
        puVar9=(uint *)(puVar4);
      }
      if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa)) goto LAB_0048deb3;
      local_4c=(uint *)(puVar9);
      if (local_18 == (undefined4 *)0xd) {
        if (puVar9 < puVar4) {
          local_14=(uint *)(puVar9 + 1);
          uVar13=(uint)(*puVar9);
          uVar13=(uint)(uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
        }
        else {
          uVar13=(uint)(0);
          local_14=(uint *)(puVar4);
        }
        if (uVar13 == 10) {
          local_4c=(uint *)(local_14);
        }
      }
      puVar12=(uint *)(local_4c);
      if ((*(uint **)&scannerContext.state.line) < local_4c) {
        (*(uint **)&scannerContext.state.line) = local_4c;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar13=(uint)(0);
        }
        else {
          uVar13=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar13 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_4c - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(uint **)&scannerContext.state.current) = puVar12;
      goto LAB_0048dd21;
    }
  }
LAB_0048deb3:
  (*(uint **)&scannerContext.state.current) = local_4c;
  *local_38 = *local_20;
  local_38[1] = local_20[1];
  local_38[2] = local_20[2];
  local_38[3] = local_20[3];
  piVar14=(int *)(local_44);
  if (local_44 == (int *)0x0) {
    piVar14=(int *)(local_48);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *piVar14 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = piVar14[3];
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  if (local_4c < puVar4) {
    uVar13=(uint)(*local_4c);
    local_18 = (undefined4 *)
               (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
    local_4c=(uint *)(local_4c + 1);
  }
  else {
    local_4c=(uint *)(puVar4);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_18 == (undefined4 *)0x0) {
    if (scannerCharacterFlags[0] == '\0') {
      (*(uint **)&scannerContext.state.current) = local_4c;
      *param_1 = 0;
      goto LAB_0048f2a4;
    }
    goto LAB_0048e9b5;
  }
  if (local_4c + 3 < puVar4) {
    local_3c=(undefined4 *)(local_40);
LAB_0048dfb0:
    if ((scannerNative00725f3f != '\0') && (local_18 < (undefined4 *)0x10000)) {
      if ((*(byte *)(local_18 + 0x19fc00) & 1) != 0) {
switchD_0048e002_caseD_41:
        puVar5=(undefined *)(local_1c);
        puVar12=(uint *)(local_4c);
        goto LAB_0048ef34;
      }
      if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) goto switchD_0048e002_caseD_30;
      if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_0048eb05;
    }
    do {
      switch((uint)local_18) {
      case 0x0:
        if (scannerCharacterFlags[0] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0;
        goto LAB_0048f2a4;
      default:
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 1) != 0))
        goto switchD_0048e002_caseD_41;
        if ((local_18 > (undefined4 *)0xffff) || ((*(byte *)(local_18 + 0x19fc00) & 0x10) == 0)) {
          if (local_18 < (undefined4 *)0x100) {
            if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_0048e9b5;
            (*(uint **)&scannerContext.state.current) = local_4c;
            *param_1 = (short)local_18;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_0048e9b5;
            (*(uint **)&scannerContext.state.current) = local_4c;
            *param_1 = -6;
          }
          goto LAB_0048f2a4;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_0048e002_caseD_30:
        local_2c=(undefined4 *)(local_3c);
        puVar9=(uint *)(local_4c);
        while( true ) {
          local_4c=(uint *)(puVar9);
          puVar6=(undefined4 *)(local_18);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar8=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
          if (puVar4 <= local_4c) break;
          local_14=(uint *)(local_4c + 1);
          uVar13=(uint)(*local_4c);
          local_18 = (undefined4 *)
                     (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                     uVar13 << 0x18);
          if ((local_18 > (undefined4 *)0x7f) ||
             (puVar9 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0 &&
             (((local_18 != (undefined4 *)0x2b && (local_18 != (undefined4 *)0x2d)) ||
              (puVar6 != (undefined4 *)0x45 &&
              (puVar6 != (undefined4 *)0x65 && (puVar6 != (undefined4 *)0x50) &&
              (puVar6 != (undefined4 *)0x70)))) && (local_18 != (undefined4 *)0x2e)))) break;
        }
        if ((local_18 < (undefined4 *)0x80) && (local_14 < puVar4) &&
           (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0)) goto switchD_0048e002_caseD_1b;
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           (puVar6 > (undefined4 *)0x2f && (puVar6 < (undefined4 *)0x3a)) ||
           (puVar6 > (undefined4 *)0xffff ||
           (local_18 = puVar6, (*(byte *)(puVar6 + 0x19fc00) & 0x10) == 0))) {
          (*(uint **)&scannerContext.state.current) = local_4c;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048f282;
        }
        break;
      case 0xa:
      case 0xd:
        if (local_18 == (undefined4 *)0xd) {
          local_14=(uint *)(local_4c + 1);
          uVar13=(uint)(*local_4c);
          if ((uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18) ==
              10) {
            local_4c=(uint *)(local_14);
          }
        }
        if ((*(uint **)&scannerContext.state.line) < local_4c) {
          (*(uint **)&scannerContext.state.line) = local_4c;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar13=(uint)(0);
          }
          else {
            uVar13=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar13 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_4c - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_0048f282;
      case 0x1b:
        goto switchD_0048e002_caseD_1b;
      case 0x21:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[33] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x21;
        goto LAB_0048f2a4;
      case 0x22:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) goto LAB_0048f146;
      case 0x27:
        if (local_18 == (undefined4 *)0x27) {
          sVar7=(short)(-9);
        }
        else {
          sVar7=(short)(-0xc);
        }
        *param_1 = sVar7;
        goto LAB_0048f0c6;
      case 0x23:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x23) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[35] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x23;
        goto LAB_0048f2a4;
      case 0x25:
        puVar9=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = puVar9;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_14=(uint *)(local_4c + 2);
          uVar13=(uint)(*puVar9);
          local_18 = (undefined4 *)
                     (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                     uVar13 << 0x18);
          if (local_18 == (undefined4 *)0x25) {
            uVar13=(uint)(*local_14);
            local_18 = (undefined4 *)
                       (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                       uVar13 << 0x18);
            if (local_18 == (undefined4 *)0x3a) {
              (*(uint **)&scannerContext.state.current) = local_4c + 3;
              *param_1 = -0x12;
              *(undefined **)(param_1 + 2) = &scannerNative0067de55;
              param_1[4] = 4;
              param_1[5] = 0;
              goto LAB_0048f282;
            }
            uVar13=(uint)(local_4c[3]);
            bVar1 = (&scannerFastUnicodeFlags[0])
                    [((uVar13 >> 8 & 0xff00 | uVar13 >> 0x18) ^ (int)local_18 << 7) & 0x3fff];
          }
          else {
            bVar1 = (&scannerFastUnicodeFlags[0])
                    [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff];
          }
          local_4c=(uint *)(puVar9);
          if ((bVar1 & 1) != 0) goto switchD_0048e002_caseD_1b;
          (*(uint **)&scannerContext.state.current) = puVar9;
          *param_1 = 0x23;
          *(undefined **)(param_1 + 2) = &scannerNative0067de51;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(uint **)&scannerContext.state.current) = puVar9;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        local_14=(uint *)(puVar9);
        if (((&scannerFastUnicodeFlags[0])
             [((*puVar9 >> 8 & 0xff00 | *puVar9 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) != 0)
        goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[37] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x25;
        goto LAB_0048f2a4;
      case 0x26:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x26) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[38] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x26;
        goto LAB_0048f2a4;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if (*(char *)(local_18 + 0x1a3c00) != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = (short)local_18;
        goto LAB_0048f2a4;
      case 0x2a:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[42] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x2a;
        goto LAB_0048f2a4;
      case 0x2b:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x2b) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[43] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x2b;
        goto LAB_0048f2a4;
      case 0x2d:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x3e) {
          uVar13=(uint)(*local_14);
          local_18 = (undefined4 *)
                     (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                     uVar13 << 0x18);
          if ((scannerNative0070f1a8 == '\0') || (local_18 != (undefined4 *)0x2a)) {
            uVar13=(uint)(local_4c[2]);
            if (((&scannerFastUnicodeFlags[0])
                 [((uVar13 >> 8 & 0xff00 | uVar13 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) != 0
               ) goto switchD_0048e002_caseD_1b;
            (*(uint **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            (*(uint **)&scannerContext.state.current) = local_4c + 2;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_0048f282;
        }
        if (local_18 == (undefined4 *)0x2d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[45] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x2d;
        goto LAB_0048f2a4;
      case 0x2e:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x2e) {
          uVar13=(uint)(*local_14);
          local_18 = (undefined4 *)
                     (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                     uVar13 << 0x18);
          if (local_18 == (undefined4 *)0x2e) {
            (*(uint **)&scannerContext.state.current) = local_4c + 2;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            goto LAB_0048f282;
          }
          uVar13=(uint)(local_4c[2]);
          bVar1 = (&scannerFastUnicodeFlags[0])
                  [((uVar13 >> 8 & 0xff00 | uVar13 >> 0x18) ^ (int)local_18 << 7) & 0x3fff];
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x2a)) {
            (*(uint **)&scannerContext.state.current) = local_14;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            goto LAB_0048f282;
          }
          if ((*(byte *)(local_18 + 0x19fc00) & 0x10) != 0) {
            local_18=(undefined4 *)((undefined4 *)0x2e);
            goto switchD_0048e002_caseD_30;
          }
          bVar1 = (&scannerFastUnicodeFlags[0])
                  [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff];
        }
        if ((bVar1 & 1) != 0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[46] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x2e;
        goto LAB_0048f2a4;
      case 0x2f:
        local_14=(uint *)(local_4c + 1);
        scannerCommentBuffer.length = 0;
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_0048eb05;
          if (scannerNative0070f1ca != '\0') goto LAB_0048eb05;
          if (scannerNative0070f1af == '\0') goto LAB_0048eb05;
        }
        if (local_18 == (undefined4 *)0x2a) {
          local_2c=(undefined4 *)((undefined4 *)0x0);
          local_3c=(undefined4 *)(local_40);
          local_4c=(uint *)(local_14);
          goto LAB_0048fef7;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[47] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x2f;
        goto LAB_0048f2a4;
      case 0x3a:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if ((scannerNative0070f1a8 != '\0') && (local_18 == (undefined4 *)0x3a)) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if ((local_18 == (undefined4 *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[58] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x3a;
        goto LAB_0048f2a4;
      case 0x3c:
        if ((*(byte *)(local_18 + 0x19fc00) & 0x20) != 0) {
LAB_0048f146:
          if (local_18 == (undefined4 *)0x3c) {
            cVar10=(char)('>');
          }
          else {
            cVar10=(char)('\"');
          }
          local_20=(undefined4 *)((undefined4 *)(int)cVar10);
          goto LAB_0048f160;
        }
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (local_18 == (undefined4 *)0x3c) {
          uVar13=(uint)(*local_14);
          local_18 = (undefined4 *)
                     (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                     uVar13 << 0x18);
          if (local_18 == (undefined4 *)0x3d) {
            (*(uint **)&scannerContext.state.current) = local_4c + 2;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            uVar13=(uint)(local_4c[2]);
            if (((&scannerFastUnicodeFlags[0])
                 [((uVar13 >> 8 & 0xff00 | uVar13 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) != 0
               ) goto switchD_0048e002_caseD_1b;
            (*(uint **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_0048f282;
        }
        if ((local_18 == (undefined4 *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if ((local_18 == (undefined4 *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[60] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x3c;
        goto LAB_0048f2a4;
      case 0x3d:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[61] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x3d;
        goto LAB_0048f2a4;
      case 0x3e:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (local_18 == (undefined4 *)0x3e) {
          uVar13=(uint)(*local_14);
          local_18 = (undefined4 *)
                     (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                     uVar13 << 0x18);
          if (local_18 == (undefined4 *)0x3d) {
            (*(uint **)&scannerContext.state.current) = local_4c + 2;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            uVar13=(uint)(local_4c[2]);
            if (((&scannerFastUnicodeFlags[0])
                 [((uVar13 >> 8 & 0xff00 | uVar13 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) != 0
               ) goto switchD_0048e002_caseD_1b;
            (*(uint **)&scannerContext.state.current) = local_14;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[62] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x3e;
        goto LAB_0048f2a4;
      case 0x3f:
        goto switchD_0048e002_caseD_3f;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          local_1c=(undefined *)((undefined *)(uint)scannerUnicodeFlags[64]);
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_4c),(char *)(puVar4),(char **)(&local_14),(ScanWord *)(&local_18));
          scannerUnicodeFlags[64] = (byte)local_1c;
          (*(uint **)&scannerContext.state.current) = local_4c;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048f282;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x40;
        goto LAB_0048f2a4;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_0048e002_caseD_41;
      case 0x5c:
        if (local_4c < puVar4) {
          local_14=(uint *)(local_4c + 1);
          uVar13=(uint)(*local_4c);
          local_18 = (undefined4 *)
                     (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                     uVar13 << 0x18);
        }
        else {
          local_14=(uint *)(puVar4);
          local_18=(undefined4 *)((undefined4 *)0x0);
        }
        if ((local_18 != (undefined4 *)0xd) && (local_18 != (undefined4 *)0xa))
        goto switchD_0048e002_caseD_1b;
        local_4c=(uint *)(local_14);
        if (local_18 == (undefined4 *)0xd) {
          if (local_14 < puVar4) {
            uVar13=(uint)(*local_14);
            uVar13 = uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18
            ;
            local_14=(uint *)(local_14 + 1);
          }
          else {
            local_14=(uint *)(puVar4);
            uVar13=(uint)(0);
          }
          if (uVar13 == 10) {
            local_4c=(uint *)(local_14);
          }
        }
        puVar12=(uint *)(local_4c);
        if ((*(uint **)&scannerContext.state.line) < local_4c) {
          (*(uint **)&scannerContext.state.line) = local_4c;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar13=(uint)(0);
          }
          else {
            uVar13=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar13 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_4c - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(uint **)&scannerContext.state.current) = puVar12;
        goto LAB_0048dd21;
      case 0x5e:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[94] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x5e;
        goto LAB_0048f2a4;
      case 0x7c:
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
        if (local_18 == (undefined4 *)0x7c) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (local_18 == (undefined4 *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_14;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_0048f282;
        }
        if (((&scannerFastUnicodeFlags[0])
             [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) !=
            0) goto switchD_0048e002_caseD_1b;
        if (scannerCharacterFlags[124] != '\0') goto LAB_0048e9b5;
        (*(uint **)&scannerContext.state.current) = local_4c;
        *param_1 = 0x7c;
        goto LAB_0048f2a4;
      }
    } while( true );
  }
  goto switchD_0048e002_caseD_1b;
LAB_0048dd60:
  local_4c=(uint *)(local_14);
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  goto LAB_0048dd21;
switchD_0048e002_caseD_3f:
  if (scannerNative0070f072 == '\0') goto switchD_0048e189_caseD_22;
  local_14=(uint *)(local_4c + 1);
  uVar13=(uint)(*local_4c);
  if ((uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18) != 0x3f)
  goto switchD_0048e189_caseD_22;
  uVar13=(uint)(*local_14);
  puVar9=(uint *)(local_4c + 2);
  switch(uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18) {
  case 0x21:
    local_18=(undefined4 *)((undefined4 *)0x7c);
    local_4c=(uint *)(puVar9);
    goto LAB_0048dfb0;
  default:
    goto switchD_0048e189_caseD_22;
  case 0x27:
    local_18=(undefined4 *)((undefined4 *)0x5e);
    local_4c=(uint *)(puVar9);
    goto LAB_0048dfb0;
  case 0x28:
    local_18=(undefined4 *)((undefined4 *)0x5b);
    local_4c=(uint *)(puVar9);
    goto switchD_0048e189_caseD_22;
  case 0x29:
    local_18=(undefined4 *)((undefined4 *)0x5d);
    local_4c=(uint *)(puVar9);
    goto switchD_0048e189_caseD_22;
  case 0x2d:
    local_18=(undefined4 *)((undefined4 *)0x7e);
    local_4c=(uint *)(puVar9);
    goto switchD_0048e189_caseD_22;
  case 0x2f:
    if (puVar9 < puVar4) {
      local_14=(uint *)(local_4c + 3);
      uVar13=(uint)(*puVar9);
      local_18 = (undefined4 *)
                 (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
    }
    else {
      local_18=(undefined4 *)((undefined4 *)0x0);
      local_14=(uint *)(puVar4);
    }
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      local_4c=(uint *)(local_14);
      if (local_18 == (undefined4 *)0xd) {
        if (local_14 < puVar4) {
          uVar13=(uint)(*local_14);
          uVar13=(uint)(uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
          local_14=(uint *)(local_14 + 1);
        }
        else {
          local_14=(uint *)(puVar4);
          uVar13=(uint)(0);
        }
        if (uVar13 == 10) {
          local_4c=(uint *)(local_14);
        }
      }
      puVar12=(uint *)(local_4c);
      if ((*(uint **)&scannerContext.state.line) < local_4c) {
        (*(uint **)&scannerContext.state.line) = local_4c;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar13=(uint)(0);
        }
        else {
          uVar13=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar13 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_4c - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(uint **)&scannerContext.state.current) = puVar12;
      goto LAB_0048dd21;
    }
    local_18=(undefined4 *)((undefined4 *)0x5c);
    local_4c=(uint *)(puVar9);
    goto LAB_0048dfb0;
  case 0x3c:
    local_18=(undefined4 *)((undefined4 *)0x7b);
    local_4c=(uint *)(puVar9);
    goto switchD_0048e189_caseD_22;
  case 0x3d:
    local_18=(undefined4 *)((undefined4 *)0x23);
    local_4c=(uint *)(puVar9);
    goto LAB_0048dfb0;
  case 0x3e:
    break;
  }
  local_18=(undefined4 *)((undefined4 *)0x7d);
  local_4c=(uint *)(puVar9);
switchD_0048e189_caseD_22:
  if (*(char *)(local_18 + 0x1a3c00) == '\0') {
    (*(uint **)&scannerContext.state.current) = local_4c;
    *param_1 = (short)local_18;
LAB_0048f2a4:
    scannerNative0071726a = (undefined1)*param_1;
    *(undefined1 **)(param_1 + 2) = &scannerNative0071726a;
    param_1[4] = 1;
    param_1[5] = 0;
    *(int *)(param_1 + 0xc) = (int)(*(uint **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
    return *param_1;
  }
LAB_0048e9b5:
  local_14=(uint *)(local_4c);
LAB_0048ea95:
  if (scannerNative0070f071 != '\0') {
    iVar8 = (int)(((int)local_4c - (int)puVar12) + ((int)local_4c - (int)puVar12 >> 0x1f & 3U)) >> 2
    ;
    puVar9=(uint *)(puVar12);
    iVar3=(int)(scannerLiteralBuffer.length);
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar8) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar8);
      iVar3=(int)(scannerLiteralBuffer.length);
    }
    for (; puVar12 = local_4c, scannerLiteralBuffer.length = iVar3, iVar8 != 0; iVar8 = iVar8 - 1) {
      scannerLiteralBuffer.length = iVar3 + 1;
      *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar9;
      puVar9=(uint *)((uint *)((int)puVar9 + 1));
      iVar3=(int)(scannerLiteralBuffer.length);
    }
  }
  if (local_4c < puVar4) {
LAB_0048eb05:
    do {
      if (local_4c < puVar4) {
        local_14=(uint *)(local_4c + 1);
        uVar13=(uint)(*local_4c);
        local_18 = (undefined4 *)
                   (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18)
        ;
      }
      else {
        local_14=(uint *)(puVar4);
        local_18=(undefined4 *)((undefined4 *)0x0);
      }
      if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa) ||
         (local_18 == (undefined4 *)0x0)) goto LAB_0048eb68;
      local_4c=(uint *)(local_14);
      if (local_18 != (undefined4 *)0x5c) break;
      iVar8=(int)(fn_00484a20((char *)(local_14),(char *)(puVar4),(char **)(&local_34)));
      if ((iVar8 == 0xd) || (iVar8 == 10)) {
        local_4c=(uint *)(local_34);
        if ((iVar8 == 0xd) && (iVar8 = fn_00484a20((char *)(local_34),(char *)(puVar4),(char **)(&local_34)), iVar8 == 10)) {
          local_4c=(uint *)(local_34);
        }
        fn_004816a0((char *)(local_4c));
        bVar2=(bool)(true);
      }
      else {
        bVar2=(bool)(false);
      }
    } while (bVar2);
    goto LAB_0048ea95;
  }
LAB_0048eb68:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 != '\0') {
    (*(uint **)&scannerContext.state.current) = local_4c;
    *param_1 = -0x11;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
    *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
    *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
    goto LAB_0048f282;
  }
  (*(uint **)&scannerContext.state.current) = local_4c;
  goto LAB_0048dd21;
LAB_0048fef7:
  if (local_4c < puVar4) {
    uVar13=(uint)(*local_4c);
    local_18 = (undefined4 *)
               (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
    local_4c=(uint *)(local_4c + 1);
  }
  else {
    local_4c=(uint *)(puVar4);
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if ((local_18 == (undefined4 *)0x2f) && (local_2c == (undefined4 *)0x2a)) goto LAB_0049003e;
  if (local_18 != (undefined4 *)0x0) {
    if ((local_18 == (undefined4 *)0xd) || (local_18 == (undefined4 *)0xa)) {
      if (local_18 == (undefined4 *)0xd) {
        if (local_4c < puVar4) {
          local_14=(uint *)(local_4c + 1);
          uVar13=(uint)(*local_4c);
          uVar13=(uint)(uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
        }
        else {
          local_14=(uint *)(puVar4);
          uVar13=(uint)(0);
        }
        if (uVar13 == 10) {
          local_4c=(uint *)(local_14);
        }
      }
      puVar9=(uint *)(local_4c);
      if ((*(uint **)&scannerContext.state.line) < local_4c) {
        (*(uint **)&scannerContext.state.line) = local_4c;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar13=(uint)(0);
        }
        else {
          uVar13=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar13 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_4c - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(uint **)&scannerContext.state.current) = puVar9;
      local_18=(undefined4 *)((undefined4 *)0xa);
      goto LAB_0048ffaa;
    }
    if (local_18 != (undefined4 *)0x5c) goto LAB_0048ffaa;
    iVar8=(int)(fn_00484a20((char *)(local_4c),(char *)(puVar4),(char **)(&local_30)));
    if ((iVar8 == 0xd) || (iVar8 == 10)) {
      local_4c=(uint *)(local_30);
      if ((iVar8 == 0xd) && (iVar8 = fn_00484a20((char *)(local_30),(char *)(puVar4),(char **)(&local_30)), iVar8 == 10)) {
        local_4c=(uint *)(local_30);
      }
      fn_004816a0((char *)(local_4c));
      bVar2=(bool)(true);
    }
    else {
      bVar2=(bool)(false);
    }
    if (!bVar2) {
LAB_0048ffaa:
      local_2c=(undefined4 *)(local_18);
      if (scannerNative0070f071 != '\0') {
        iVar8 = (int)(((int)local_4c - (int)puVar12) + ((int)local_4c - (int)puVar12 >> 0x1f & 3U))
                >> 2;
        puVar9=(uint *)(puVar12);
        iVar3=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar8) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar8);
          iVar3=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar12 = local_4c, scannerLiteralBuffer.length = iVar3, iVar8 != 0; iVar8 = iVar8 - 1) {
          scannerLiteralBuffer.length = iVar3 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar9;
          puVar9=(uint *)((uint *)((int)puVar9 + 1));
          iVar3=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_0048fef7;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 8),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_0049003e:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(uint **)&scannerContext.state.current) = local_4c;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_0048dd21;
  }
  if (local_18 == (undefined4 *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar8=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = 0x2f;
  }
  (*(uint **)&scannerContext.state.current) = local_4c;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_0048f282;
LAB_0048f160:
  if (local_4c < puVar4) {
    local_14=(uint *)(local_4c + 1);
    uVar13=(uint)(*local_4c);
    local_18 = (undefined4 *)
               (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
  }
  else {
    local_18=(undefined4 *)((undefined4 *)0x0);
  }
  if (local_20 == local_18) goto LAB_00490891;
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < puVar4 &&
     (((&scannerFastUnicodeFlags[0])
       [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 1) != 0)))
  goto switchD_0048e002_caseD_1b;
  if ((local_18 == (undefined4 *)0x0) ||
     (local_18 == (undefined4 *)0xd || (local_18 == (undefined4 *)0xa))) goto LAB_004907d0;
  local_4c=(uint *)(local_14);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar8=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
  goto LAB_0048f160;
LAB_004907d0:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_00490891:
  (*(uint **)&scannerContext.state.current) = local_14;
  if (local_20 == (undefined4 *)0x3e) {
    sVar7=(short)(-0x10);
  }
  else {
    sVar7=(short)(-0xf);
  }
  *param_1 = sVar7;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_0048f282;
LAB_0048ef34:
  local_4c=(uint *)(puVar12);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar8=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
  if (puVar4 <= local_4c) goto LAB_004903e1;
  local_14=(uint *)(local_4c + 1);
  uVar13=(uint)(*local_4c);
  local_18 = (undefined4 *)
             (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18);
  if ((local_18 > (undefined4 *)0x7f) ||
     (puVar12 = local_14, (*(byte *)(local_18 + 0x19fc00) & 0x11) == 0)) goto LAB_004903e1;
  goto LAB_0048ef34;
LAB_004903e1:
  if ((local_18 > (undefined4 *)0x7f) ||
     (local_14 < puVar4 &&
     (((&scannerFastUnicodeFlags[0])
       [((*local_14 >> 8 & 0xff00 | *local_14 >> 0x18) ^ (int)local_18 << 7) & 0x3fff] & 2) != 0)))
  {
switchD_0048e002_caseD_1b:
    *local_24 = *local_28;
    local_24[1] = local_28[1];
    local_24[2] = local_28[2];
    local_24[3] = local_28[3];
    sVar7=(short)(fn_004923e0((ScanToken *)(param_1)));
    return sVar7;
  }
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_18 == (undefined4 *)0x27) {
    sVar7=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar7;
    if (*param_1 != 0) {
      local_4c=(uint *)(local_14);
      scannerLiteralBuffer.length = 0;
LAB_0048f0c6:
      do {
        puVar6=(undefined4 *)(local_18);
        if (local_4c < puVar4) {
          uVar13=(uint)(*local_4c);
          puVar11 = (undefined4 *)
                    (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 | uVar13 << 0x18
                    );
          local_4c=(uint *)(local_4c + 1);
        }
        else {
          local_4c=(uint *)(puVar4);
          puVar11=(undefined4 *)((undefined4 *)0x0);
        }
        if (local_18 == puVar11) {
          (*(uint **)&scannerContext.state.current) = local_4c;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_0048f282;
        }
        local_18=(undefined4 *)(puVar11);
        if ((puVar11 > (undefined4 *)0x7f) ||
           ((local_4c < puVar4 &&
            (((&scannerFastUnicodeFlags[0])
              [((*local_4c >> 8 & 0xff00 | *local_4c >> 0x18) ^ (int)puVar11 << 7) & 0x3fff] & 4) !=
             0)) || (puVar11 == (undefined4 *)0x0))) goto switchD_0048e002_caseD_1b;
        if (puVar11 == (undefined4 *)0x5c) {
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar8=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
          if (local_4c < puVar4) {
            uVar13=(uint)(*local_4c);
            local_18 = (undefined4 *)
                       (uVar13 >> 8 & 0xff00 | uVar13 >> 0x18 | (uVar13 & 0xff00) << 8 |
                       uVar13 << 0x18);
            local_4c=(uint *)(local_4c + 1);
          }
          else {
            local_4c=(uint *)(puVar4);
            local_18=(undefined4 *)((undefined4 *)0x0);
          }
        }
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
        }
        iVar8=(int)(scannerLiteralBuffer.length);
        scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
        *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar8) = (*(byte *)((char *)&local_18+0));
        local_18=(undefined4 *)(puVar6);
      } while( true );
    }
  }
  else if (local_18 == (undefined4 *)0x22) {
    sVar7=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar7;
    if (*param_1 != 0) {
      local_4c=(uint *)(local_14);
      scannerLiteralBuffer.length = 0;
      goto LAB_0048f0c6;
    }
  }
  (*(uint **)&scannerContext.state.current) = local_4c;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_0048f282:
  *(int *)(param_1 + 0xc) = (int)(*(uint **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_00490990(ScanToken *token)
{
 short *param_1=(short *)token;
  bool bVar1;
  int iVar2;
  byte *pbVar3;
  short sVar4;
  uint uVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  byte bVar9;
  char cVar10;
  byte *pbVar11;
  byte *local_40;
  byte *local_3c;
  byte *pbStack_38;
  undefined *local_34;
  undefined *local_30;
  undefined *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  byte *local_20;
  byte *local_1c;
  byte *local_18;
  byte *local_14;
  pbVar3=(byte *)((*(byte **)&scannerContext.end));
  local_40=(byte *)((*(byte **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_28=(undefined4 *)(&(*(byte **)&scannerContext.state.current));
  local_24=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_20=(byte *)((byte *)&(*(uint *)&scannerContext.previous.current));
  local_3c=(byte *)((byte *)&(*(byte **)&scannerContext.state.current));
  local_2c=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_30=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
LAB_004909e1:
  pbVar11=(byte *)(local_40);
  if (local_40 < pbVar3) {
    if (local_40 < pbVar3) {
      local_18=(byte *)(local_40 + 1);
      local_14=(byte *)((byte *)(uint)*local_40);
    }
    else {
      local_18=(byte *)(pbVar3);
      local_14=(byte *)((byte *)0x0);
    }
    if ((local_14 == (byte *)0x9) || (local_14 + -0xb < (byte *)0x2) || (local_14 == (byte *)0x1a)
       || (local_14 == (byte *)0x20)) {
      local_40=(byte *)(local_18);
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      goto LAB_004909e1;
    }
    if (local_14 == (byte *)0x5c) {
      if (local_18 < pbVar3) {
        local_1c=(byte *)(local_18 + 1);
        local_14=(byte *)((byte *)(uint)*local_18);
      }
      else {
        local_1c=(byte *)(pbVar3);
        local_14=(byte *)((byte *)0x0);
      }
      if ((local_14 != (byte *)0xd) && (local_14 != (byte *)0xa)) goto LAB_00490b10;
      local_40=(byte *)(local_1c);
      if (local_14 == (byte *)0xd) {
        if (local_1c < pbVar3) {
          local_18=(byte *)(local_1c + 1);
          bVar9=(byte)(*local_1c);
        }
        else {
          local_18=(byte *)(pbVar3);
          bVar9=(byte)(0);
        }
        if (bVar9 == 10) {
          local_40=(byte *)(local_18);
        }
      }
      pbVar11=(byte *)(local_40);
      if ((*(byte **)&scannerContext.state.line) < local_40) {
        (*(byte **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar5=(uint)(0);
        }
        else {
          uVar5=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar5 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(byte **)&scannerContext.state.current) = pbVar11;
      goto LAB_004909e1;
    }
  }
LAB_00490b10:
  (*(byte **)&scannerContext.state.current) = local_40;
  *local_24 = *local_28;
  local_24[1] = local_28[1];
  local_24[2] = local_28[2];
  local_24[3] = local_28[3];
  pbVar6=(byte *)(local_20);
  if (local_20 == (byte *)0x0) {
    pbVar6=(byte *)(local_3c);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *(int *)pbVar6 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = *(int *)(pbVar6 + 0xc);
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_40),(ScanByte)(0)));
  if (local_14 == (byte *)0x0) {
    if (scannerCharacterFlags[0] != '\0') goto LAB_004910a0;
    (*(byte **)&scannerContext.state.current) = local_40;
    *param_1 = 0;
    goto LAB_00491650;
  }
  pbVar6=(byte *)(local_14);
  if ((scannerNative00725f3f == '\0') || (local_14 > (byte *)0xffff)) {
LAB_00490c25:
    do {
      local_14=(byte *)(pbVar6);
      bVar9=(byte)(scannerUnicodeFlags[64]);
      sVar4=(short)((short)local_14);
      switch((uint)local_14) {
      case 0x0:
        goto switchD_00490c32_caseD_0;
      default:
        if ((local_14 > (byte *)0xffff) || ((local_14[0x67f000] & 1) != 0))
        goto switchD_00490c32_caseD_41;
        if ((local_14 > (byte *)0xffff) || ((local_14[0x67f000] & 0x10) == 0)) {
          if (local_14 < (byte *)0x100) {
            if (local_14[0x68f000] != 0) goto LAB_004910a0;
            (*(byte **)&scannerContext.state.current) = local_40;
            *param_1 = sVar4;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_004910a0;
            (*(byte **)&scannerContext.state.current) = local_40;
            *param_1 = -6;
          }
          goto LAB_00491650;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_00490c32_caseD_30:
        local_34=(undefined *)(local_30);
        while( true ) {
          pbVar6=(byte *)(local_14);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar7=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_14+0));
          local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 > (byte *)0x7f) ||
             ((local_14[0x67f000] & 0x11) == 0 &&
             ((local_14 != (byte *)0x2b && (local_14 != (byte *)0x2d)) ||
             (pbVar6 != (byte *)0x45 &&
             (pbVar6 != (byte *)0x65 && (pbVar6 != (byte *)0x50) && (pbVar6 != (byte *)0x70)))) &&
             (local_14 != (byte *)0x2e))) break;
          local_40=(byte *)(local_18);
        }
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           ((pbVar6 > (byte *)0x2f && (pbVar6 < (byte *)0x3a)) ||
           (pbVar6 > (byte *)0xffff || ((pbVar6[0x67f000] & 0x10) == 0)))) {
          (*(byte **)&scannerContext.state.current) = local_40;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00491621;
        }
        break;
      case 0xa:
      case 0xd:
        if ((*(byte **)&scannerContext.state.line) < local_40) {
          (*(byte **)&scannerContext.state.line) = local_40;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar5=(uint)(0);
          }
          else {
            uVar5=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar5 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_00491621;
      case 0x21:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(byte *)((byte *)0x3d);
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[33] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x21;
        goto LAB_00491650;
      case 0x22:
        if ((local_14[0x67f000] & 0x20) != 0) goto LAB_00491501;
      case 0x27:
        if (local_14 == (byte *)0x27) {
          sVar4=(short)(-9);
        }
        else {
          sVar4=(short)(-0xc);
        }
        *param_1 = sVar4;
        goto LAB_004914a8;
      case 0x23:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x23) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(byte *)((byte *)0x23);
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[35] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x23;
        goto LAB_00491650;
      case 0x25:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if ((local_14 == (byte *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(byte *)(local_18);
          local_14=(byte *)((byte *)fn_004845f0((char *)(local_18),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 == (byte *)0x25) &&
             (local_14 = (byte *)fn_004845f0((char *)(local_18),(char *)(pbVar3),(char **)(&local_1c),(ScanByte)(0)),
             local_14 == (byte *)0x3a)) {
            local_40=(byte *)(local_1c);
            (*(byte **)&scannerContext.state.current) = local_1c;
            *param_1 = -0x12;
            *(undefined **)(param_1 + 2) = &scannerNative0067de55;
            param_1[4] = 4;
            param_1[5] = 0;
          }
          else {
            (*(byte **)&scannerContext.state.current) = local_40;
            *param_1 = 0x23;
            *(undefined **)(param_1 + 2) = &scannerNative0067de51;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00491621;
        }
        if ((local_14 == (byte *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[37] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x25;
        goto LAB_00491650;
      case 0x26:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x26) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[38] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x26;
        goto LAB_00491650;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if (local_14[0x68f000] != 0) goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = sVar4;
        goto LAB_00491650;
      case 0x2a:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(byte *)((byte *)0x3d);
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[42] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2a;
        goto LAB_00491650;
      case 0x2b:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x2b) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[43] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2b;
        goto LAB_00491650;
      case 0x2d:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x3e) {
          local_14=(byte *)((byte *)fn_004845f0((char *)(local_18),(char *)(pbVar3),(char **)(&local_1c),(ScanByte)(0)));
          if ((scannerNative0070f1a8 == '\0') || (local_14 != (byte *)0x2a)) {
            local_40=(byte *)(local_18);
            (*(byte **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            local_40=(byte *)(local_1c);
            (*(byte **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_00491621;
        }
        if (local_14 == (byte *)0x2d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[45] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2d;
        goto LAB_00491650;
      case 0x2e:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x2e) {
          local_14=(byte *)((byte *)fn_004845f0((char *)(local_18),(char *)(pbVar3),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (byte *)0x2e) {
            local_40=(byte *)(local_1c);
            (*(byte **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            local_14=(byte *)((byte *)0x2e);
            goto LAB_00491621;
          }
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_14 == (byte *)0x2a)) {
            local_40=(byte *)(local_18);
            (*(byte **)&scannerContext.state.current) = local_18;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            local_14=(byte *)((byte *)0x2a);
            goto LAB_00491621;
          }
          if ((local_14 < (byte *)0x10000) && ((local_14[0x67f000] & 0x10) != 0)) {
            local_14=(byte *)((byte *)0x2e);
            goto switchD_00490c32_caseD_30;
          }
        }
        if (scannerCharacterFlags[46] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2e;
        goto LAB_00491650;
      case 0x2f:
        scannerCommentBuffer.length = 0;
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_00491170;
          if (scannerNative0070f1ca != '\0') goto LAB_00491170;
          if (scannerNative0070f1af == '\0') goto LAB_00491170;
        }
        if (local_14 == (byte *)0x2a) {
          pbStack_38=(byte *)((byte *)0x0);
          local_40=(byte *)(local_18);
          local_34=(undefined *)(local_30);
          goto LAB_00491cc0;
        }
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(byte *)((byte *)0x3d);
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[47] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2f;
        goto LAB_00491650;
      case 0x3a:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if ((scannerNative0070f1a8 != '\0') && (local_14 == (byte *)0x3a)) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if ((local_14 == (byte *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[58] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3a;
        goto LAB_00491650;
      case 0x3c:
        if ((local_14[0x67f000] & 0x20) != 0) {
LAB_00491501:
          if (local_14 == (byte *)0x3c) {
            cVar10=(char)('>');
          }
          else {
            cVar10=(char)('\"');
          }
          local_20=(byte *)((byte *)(int)cVar10);
          goto LAB_00491520;
        }
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (local_14 == (byte *)0x3c) {
          local_14=(byte *)((byte *)fn_004845f0((char *)(local_18),(char *)(pbVar3),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (byte *)0x3d) {
            local_40=(byte *)(local_1c);
            (*(byte **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_40=(byte *)(local_18);
            (*(byte **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00491621;
        }
        if ((local_14 == (byte *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if ((local_14 == (byte *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[60] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3c;
        goto LAB_00491650;
      case 0x3d:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(byte *)((byte *)0x3d);
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[61] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3d;
        goto LAB_00491650;
      case 0x3e:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(byte *)((byte *)0x3d);
          goto LAB_00491621;
        }
        if (local_14 == (byte *)0x3e) {
          local_14=(byte *)((byte *)fn_004845f0((char *)(local_18),(char *)(pbVar3),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (byte *)0x3d) {
            local_40=(byte *)(local_1c);
            (*(byte **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_40=(byte *)(local_18);
            (*(byte **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[62] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3e;
        goto LAB_00491650;
      case 0x3f:
        if (local_14[0x68f000] != 0) goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = sVar4;
        goto LAB_00491650;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_40),(char *)(pbVar3),(char **)(&local_18),(ScanWord *)(&local_14));
          (*(byte **)&scannerContext.state.current) = local_40;
          scannerUnicodeFlags[64] = bVar9;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x40;
        goto LAB_00491650;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_00490c32_caseD_41;
      case 0x5c:
        if (scannerCharacterFlags[92] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5c;
        goto LAB_00491650;
      case 0x5e:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(byte *)((byte *)0x3d);
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[94] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5e;
        goto LAB_00491650;
      case 0x7c:
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (byte *)0x7c) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (local_14 == (byte *)0x3d) {
          local_40=(byte *)(local_18);
          (*(byte **)&scannerContext.state.current) = local_18;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00491621;
        }
        if (scannerCharacterFlags[124] != '\0') goto LAB_004910a0;
        (*(byte **)&scannerContext.state.current) = local_40;
        *param_1 = 0x7c;
        goto LAB_00491650;
      }
    } while( true );
  }
  if ((local_14[0x67f000] & 1) == 0) {
    if ((local_14[0x67f000] & 0x10) != 0) goto switchD_00490c32_caseD_30;
    if (local_14[0x68f000] != 0) goto LAB_00491170;
    goto LAB_00490c25;
  }
switchD_00490c32_caseD_41:
  fn_0047db20((char **)(&local_40),(char *)(pbVar3),(char **)(&local_18),(ScanWord *)(&local_14));
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_14 == (byte *)0x27) {
    sVar4=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar4;
    if (*param_1 != 0) {
      local_40=(byte *)(local_18);
      scannerLiteralBuffer.length = 0;
LAB_004914a8:
      if ((*param_1 == -0xc) || (*param_1 == -9)) {
        fn_0047d630((uint)(local_14),(char **)(&local_40),(char *)(pbVar3));
      }
      else {
        fn_0047d1e0((uint)(local_14),(char **)(&local_40),(char *)(pbVar3));
      }
      (*(byte **)&scannerContext.state.current) = local_40;
      *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
      *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
      *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
      goto LAB_00491621;
    }
  }
  else if (local_14 == (byte *)0x22) {
    sVar4=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar4;
    if (*param_1 != 0) {
      local_40=(byte *)(local_18);
      scannerLiteralBuffer.length = 0;
      goto LAB_004914a8;
    }
  }
  (*(byte **)&scannerContext.state.current) = local_40;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00491621;
LAB_00491cc0:
  if (local_40 < pbVar3) {
    local_14=(byte *)((byte *)(uint)*local_40);
    local_40=(byte *)(local_40 + 1);
  }
  else {
    local_40=(byte *)(pbVar3);
    local_14=(byte *)((byte *)0x0);
  }
  if ((local_14 == (byte *)0x2f) && (pbStack_38 == (byte *)0x2a)) goto LAB_00491dfe;
  if (local_14 != (byte *)0x0) {
    if ((local_14 == (byte *)0xd) || (local_14 == (byte *)0xa)) {
      if (local_14 == (byte *)0xd) {
        if (local_40 < pbVar3) {
          local_18=(byte *)(local_40 + 1);
          bVar9=(byte)(*local_40);
        }
        else {
          local_18=(byte *)(pbVar3);
          bVar9=(byte)(0);
        }
        if (bVar9 == 10) {
          local_40=(byte *)(local_18);
        }
      }
      pbVar6=(byte *)(local_40);
      if ((*(byte **)&scannerContext.state.line) < local_40) {
        (*(byte **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar5=(uint)(0);
        }
        else {
          uVar5=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar5 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(byte **)&scannerContext.state.current) = pbVar6;
      local_14=(byte *)((byte *)0xa);
      goto LAB_00491d70;
    }
    if (local_14 != (byte *)0x5c) goto LAB_00491d70;
    if (local_40 < pbVar3) {
      pbVar6=(byte *)(local_40 + 1);
      bVar9=(byte)(*local_40);
    }
    else {
      bVar9=(byte)(0);
      pbVar6=(byte *)(pbVar3);
    }
    if ((bVar9 == 0xd) || (bVar9 == 10)) {
      local_40=(byte *)(pbVar6);
      if (bVar9 == 0xd) {
        if (pbVar6 < pbVar3) {
          pbVar8=(byte *)(pbVar6 + 1);
          bVar9=(byte)(*pbVar6);
        }
        else {
          bVar9=(byte)(0);
          pbVar8=(byte *)(pbVar3);
        }
        if (bVar9 == 10) {
          local_40=(byte *)(pbVar8);
        }
      }
      pbVar6=(byte *)(local_40);
      if ((*(byte **)&scannerContext.state.line) < local_40) {
        (*(byte **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar5=(uint)(0);
        }
        else {
          uVar5=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar5 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      bVar1=(bool)(true);
      (*(byte **)&scannerContext.state.current) = pbVar6;
    }
    else {
      bVar1=(bool)(false);
    }
    if (!bVar1) {
LAB_00491d70:
      pbStack_38=(byte *)(local_14);
      if (scannerNative0070f071 != '\0') {
        iVar7=(int)((int)local_40 - (int)pbVar11);
        pbVar6=(byte *)(pbVar11);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar7) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar7);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; pbVar11 = local_40, scannerLiteralBuffer.length = iVar2, iVar7 != 0; iVar7 = iVar7 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(byte *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = *pbVar6;
          pbVar6=(byte *)(pbVar6 + 1);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_00491cc0;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 2),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_00491dfe:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(byte **)&scannerContext.state.current) = local_40;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_004909e1;
  }
  if (local_14 == (byte *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar7=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = 0x2f;
  }
  (*(byte **)&scannerContext.state.current) = local_40;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00491621;
LAB_00491520:
  if (local_40 < pbVar3) {
    local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(1)));
  }
  else {
    local_14=(byte *)((byte *)0x0);
  }
  if (local_20 == local_14) goto LAB_004922b0;
  if ((local_14 == (byte *)0x0) || (local_14 == (byte *)0xd) || (local_14 == (byte *)0xa))
  goto LAB_00492218;
  local_40=(byte *)(local_18);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar7=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_14+0));
  goto LAB_00491520;
switchD_00490c32_caseD_0:
  if (scannerCharacterFlags[0] != '\0') {
LAB_004910a0:
    local_18=(byte *)(local_40);
    do {
      if (scannerNative0070f071 != '\0') {
        iVar7=(int)((int)local_40 - (int)pbVar11);
        pbVar6=(byte *)(pbVar11);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar7) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar7);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; pbVar11 = local_40, scannerLiteralBuffer.length = iVar2, iVar7 != 0; iVar7 = iVar7 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(byte *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = *pbVar6;
          pbVar6=(byte *)(pbVar6 + 1);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
LAB_00491170:
      do {
        local_14=(byte *)((byte *)fn_004845f0((char *)(local_40),(char *)(pbVar3),(char **)(&local_18),(ScanByte)(1)));
        if ((local_14 == (byte *)0xd) || (local_14 == (byte *)0xa) || (local_14 == (byte *)0x0)) {
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          if (scannerNative0070f071 != '\0') {
            (*(byte **)&scannerContext.state.current) = local_40;
            *param_1 = -0x11;
            *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
            *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
            *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
            goto LAB_00491621;
          }
          (*(byte **)&scannerContext.state.current) = local_40;
          goto LAB_004909e1;
        }
        local_40=(byte *)(local_18);
        if (local_14 != (byte *)0x5c) break;
        if (local_18 < pbVar3) {
          pbVar6=(byte *)(local_18 + 1);
          bVar9=(byte)(*local_18);
        }
        else {
          bVar9=(byte)(0);
          pbVar6=(byte *)(pbVar3);
        }
        if ((bVar9 == 0xd) || (bVar9 == 10)) {
          local_40=(byte *)(pbVar6);
          if (bVar9 == 0xd) {
            if (pbVar6 < pbVar3) {
              pbVar8=(byte *)(pbVar6 + 1);
              bVar9=(byte)(*pbVar6);
            }
            else {
              bVar9=(byte)(0);
              pbVar8=(byte *)(pbVar3);
            }
            if (bVar9 == 10) {
              local_40=(byte *)(pbVar8);
            }
          }
          pbVar6=(byte *)(local_40);
          if ((*(byte **)&scannerContext.state.line) < local_40) {
            (*(byte **)&scannerContext.state.line) = local_40;
            scannerContext.state.column = scannerContext.state.column + 1;
            if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
              uVar5=(uint)(0);
            }
            else {
              uVar5=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
            }
            if (uVar5 < scannerContext.state.column) {
              sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
            }
          }
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          bVar1=(bool)(true);
          (*(byte **)&scannerContext.state.current) = pbVar6;
        }
        else {
          bVar1=(bool)(false);
        }
      } while (bVar1);
    } while( true );
  }
  (*(byte **)&scannerContext.state.current) = local_40;
  *param_1 = 0;
LAB_00491650:
  if ((*(byte **)&scannerContext.state.current) < (*(byte **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(byte **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar7=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(byte **)&scannerContext.state.line) = (byte *)(iVar7 + (*(uint *)&scannerContext.text));
  }
  scannerNative00716ec0 = (undefined1)*param_1;
  *(undefined1 **)(param_1 + 2) = &scannerNative00716ec0;
  param_1[4] = 1;
  param_1[5] = 0;
  *(int *)(param_1 + 0xc) = (int)(*(byte **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
LAB_00492218:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(byte **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_004922b0:
  (*(byte **)&scannerContext.state.current) = local_18;
  local_40=(byte *)(local_18);
  if (local_20 == (byte *)0x3e) {
    sVar4=(short)(-0x10);
  }
  else {
    sVar4=(short)(-0xf);
  }
  *param_1 = sVar4;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_00491621:
  if ((*(byte **)&scannerContext.state.current) < (*(byte **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(byte **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar7=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(byte **)&scannerContext.state.line) = (byte *)(iVar7 + (*(uint *)&scannerContext.text));
  }
  *(int *)(param_1 + 0xc) = (int)(*(byte **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_004923e0(ScanToken *token)
{
 short *param_1=(short *)token;
  bool bVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  short sVar5;
  int iVar6;
  char cVar7;
  uint uVar8;
  uint *puVar9;
  int *piVar10;
  uint *local_48;
  int *local_44;
  int *piStack_40;
  undefined *local_3c;
  undefined *local_38;
  undefined4 *local_34;
  uint *puStack_30;
  uint *local_2c;
  undefined4 *local_28;
  int *local_24;
  undefined *local_20;
  uint *local_1c;
  uint *local_18;
  int *local_14;
  puVar4=(uint *)((*(uint **)&scannerContext.end));
  local_48=(uint *)((*(uint **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_34=(undefined4 *)(&(*(uint **)&scannerContext.state.current));
  local_28=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_24=(int *)(&(*(uint *)&scannerContext.previous.current));
  local_44=(int *)((int *)&(*(uint **)&scannerContext.state.current));
  local_20=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_3c=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
LAB_00492431:
  puVar9=(uint *)(local_48);
  if (local_48 < puVar4) {
    if (local_48 < puVar4) {
      local_18=(uint *)(local_48 + 1);
      uVar8=(uint)(*local_48);
      local_14 = (int *)(uVar8 >> 8 & 0xff00 | uVar8 >> 0x18 | (uVar8 & 0xff00) << 8 | uVar8 << 0x18
                        );
    }
    else {
      local_18=(uint *)(puVar4);
      local_14=(int *)((int *)0x0);
    }
    if ((local_14 == (int *)0x9) || ((int)local_14 - 0xbU < 2) || (local_14 == (int *)0x1a) ||
       (local_14 == (int *)0x20)) {
      local_48=(uint *)(local_18);
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      goto LAB_00492431;
    }
    if (local_14 == (int *)0x5c) {
      if (local_18 < puVar4) {
        local_1c=(uint *)(local_18 + 1);
        uVar8=(uint)(*local_18);
        local_14 = (int *)(uVar8 >> 8 & 0xff00 | uVar8 >> 0x18 | (uVar8 & 0xff00) << 8 |
                          uVar8 << 0x18);
      }
      else {
        local_1c=(uint *)(puVar4);
        local_14=(int *)((int *)0x0);
      }
      if ((local_14 != (int *)0xd) && (local_14 != (int *)0xa)) goto LAB_004925e7;
      local_48=(uint *)(local_1c);
      if (local_14 == (int *)0xd) {
        if (local_1c < puVar4) {
          local_18=(uint *)(local_1c + 1);
          uVar8=(uint)(*local_1c);
          uVar8=(uint)(uVar8 >> 8 & 0xff00 | uVar8 >> 0x18 | (uVar8 & 0xff00) << 8 | uVar8 << 0x18);
        }
        else {
          local_18=(uint *)(puVar4);
          uVar8=(uint)(0);
        }
        if (uVar8 == 10) {
          local_48=(uint *)(local_18);
        }
      }
      puVar9=(uint *)(local_48);
      if ((*(uint **)&scannerContext.state.line) < local_48) {
        (*(uint **)&scannerContext.state.line) = local_48;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar8=(uint)(0);
        }
        else {
          uVar8=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar8 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_48 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(uint **)&scannerContext.state.current) = puVar9;
      goto LAB_00492431;
    }
  }
LAB_004925e7:
  (*(uint **)&scannerContext.state.current) = local_48;
  *local_28 = *local_34;
  local_28[1] = local_34[1];
  local_28[2] = local_34[2];
  local_28[3] = local_34[3];
  piVar10=(int *)(local_24);
  if (local_24 == (int *)0x0) {
    piVar10=(int *)(local_44);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *piVar10 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = piVar10[3];
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_48),(ScanByte)(0)));
  if (local_14 == (int *)0x0) {
    if (scannerCharacterFlags[0] != '\0') goto LAB_00492be1;
    (*(uint **)&scannerContext.state.current) = local_48;
    *param_1 = 0;
    goto LAB_004931c0;
  }
  piVar10=(int *)(local_14);
  if ((scannerNative00725f3f == '\0') || (local_14 > (int *)0xffff)) {
LAB_00492715:
    do {
      local_14=(int *)(piVar10);
      sVar5=(short)((short)local_14);
      switch((uint)local_14) {
      case 0x0:
        goto switchD_00492722_caseD_0;
      default:
        if ((local_14 > (int *)0xffff) || ((*(byte *)(local_14 + 0x19fc00) & 1) != 0))
        goto switchD_00492722_caseD_41;
        if ((local_14 > (int *)0xffff) || ((*(byte *)(local_14 + 0x19fc00) & 0x10) == 0)) {
          if (local_14 < (int *)0x100) {
            if ((char)local_14[0x1a3c00] != '\0') goto LAB_00492be1;
            (*(uint **)&scannerContext.state.current) = local_48;
            *param_1 = sVar5;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_00492be1;
            (*(uint **)&scannerContext.state.current) = local_48;
            *param_1 = -6;
          }
          goto LAB_004931c0;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_00492722_caseD_30:
        local_38=(undefined *)(local_3c);
        while( true ) {
          piVar10=(int *)(local_14);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar6=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar6) = (*(byte *)((char *)&local_14+0));
          local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 > (int *)0x7f) ||
             ((*(byte *)(local_14 + 0x19fc00) & 0x11) == 0 &&
             ((local_14 != (int *)0x2b && (local_14 != (int *)0x2d)) ||
             (piVar10 != (int *)0x45 &&
             (piVar10 != (int *)0x65 && (piVar10 != (int *)0x50) && (piVar10 != (int *)0x70)))) &&
             (local_14 != (int *)0x2e))) break;
          local_48=(uint *)(local_18);
        }
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           ((piVar10 > (int *)0x2f && (piVar10 < (int *)0x3a)) ||
           (piVar10 > (int *)0xffff || ((*(byte *)(piVar10 + 0x19fc00) & 0x10) == 0)))) {
          (*(uint **)&scannerContext.state.current) = local_48;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00493188;
        }
        break;
      case 0xa:
      case 0xd:
        if ((*(uint **)&scannerContext.state.line) < local_48) {
          (*(uint **)&scannerContext.state.line) = local_48;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar8=(uint)(0);
          }
          else {
            uVar8=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar8 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_48 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_00493188;
      case 0x21:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[33] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x21;
        goto LAB_004931c0;
      case 0x22:
        if ((*(byte *)(local_14 + 0x19fc00) & 0x20) != 0) goto LAB_00493066;
      case 0x27:
        if (local_14 == (int *)0x27) {
          sVar5=(short)(-9);
        }
        else {
          sVar5=(short)(-0xc);
        }
        *param_1 = sVar5;
        goto LAB_0049301c;
      case 0x23:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x23) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x23);
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[35] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x23;
        goto LAB_004931c0;
      case 0x25:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if ((local_14 == (int *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_48=(uint *)(local_18);
          local_14=(int *)((int *)fn_00483670((char *)(local_18),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 == (int *)0x25) &&
             (local_14 = (int *)fn_00483670((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)),
             local_14 == (int *)0x3a)) {
            local_48=(uint *)(local_1c);
            (*(uint **)&scannerContext.state.current) = local_1c;
            *param_1 = -0x12;
            *(undefined **)(param_1 + 2) = &scannerNative0067de55;
            param_1[4] = 4;
            param_1[5] = 0;
          }
          else {
            (*(uint **)&scannerContext.state.current) = local_48;
            *param_1 = 0x23;
            *(undefined **)(param_1 + 2) = &scannerNative0067de51;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00493188;
        }
        if ((local_14 == (int *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[37] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x25;
        goto LAB_004931c0;
      case 0x26:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x26) {
          (*(uint **)&scannerContext.state.current) = local_18;
          local_48=(uint *)(local_18);
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[38] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x26;
        goto LAB_004931c0;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if ((char)local_14[0x1a3c00] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = sVar5;
        goto LAB_004931c0;
      case 0x2a:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[42] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x2a;
        goto LAB_004931c0;
      case 0x2b:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x2b) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[43] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x2b;
        goto LAB_004931c0;
      case 0x2d:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3e) {
          local_14=(int *)((int *)fn_00483670((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if ((scannerNative0070f1a8 == '\0') || (local_14 != (int *)0x2a)) {
            local_48=(uint *)(local_18);
            (*(uint **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            local_48=(uint *)(local_1c);
            (*(uint **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_00493188;
        }
        if (local_14 == (int *)0x2d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (local_14 == (int *)0x3d) {
          (*(uint **)&scannerContext.state.current) = local_18;
          local_48=(uint *)(local_18);
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[45] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x2d;
        goto LAB_004931c0;
      case 0x2e:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x2e) {
          local_14=(int *)((int *)fn_00483670((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (int *)0x2e) {
            local_48=(uint *)(local_1c);
            (*(uint **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            local_14=(int *)((int *)0x2e);
            goto LAB_00493188;
          }
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_14 == (int *)0x2a)) {
            local_48=(uint *)(local_18);
            (*(uint **)&scannerContext.state.current) = local_18;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            local_14=(int *)((int *)0x2a);
            goto LAB_00493188;
          }
          if ((local_14 < (int *)0x10000) && ((*(byte *)(local_14 + 0x19fc00) & 0x10) != 0)) {
            local_14=(int *)((int *)0x2e);
            goto switchD_00492722_caseD_30;
          }
        }
        if (scannerCharacterFlags[46] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x2e;
        goto LAB_004931c0;
      case 0x2f:
        scannerCommentBuffer.length = 0;
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_00492cb0;
          if (scannerNative0070f1ca != '\0') goto LAB_00492cb0;
          if (scannerNative0070f1af == '\0') goto LAB_00492cb0;
        }
        if (local_14 == (int *)0x2a) {
          piStack_40=(int *)((int *)0x0);
          local_48=(uint *)(local_18);
          local_38=(undefined *)(local_3c);
          goto LAB_004938e0;
        }
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[47] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x2f;
        goto LAB_004931c0;
      case 0x3a:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if ((scannerNative0070f1a8 != '\0') && (local_14 == (int *)0x3a)) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if ((local_14 == (int *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[58] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x3a;
        goto LAB_004931c0;
      case 0x3c:
        if ((*(byte *)(local_14 + 0x19fc00) & 0x20) != 0) {
LAB_00493066:
          if (local_14 == (int *)0x3c) {
            cVar7=(char)('>');
          }
          else {
            cVar7=(char)('\"');
          }
          local_24=(int *)((int *)(int)cVar7);
          goto LAB_00493080;
        }
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (local_14 == (int *)0x3c) {
          local_14=(int *)((int *)fn_00483670((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (int *)0x3d) {
            local_48=(uint *)(local_1c);
            (*(uint **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_48=(uint *)(local_18);
            (*(uint **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00493188;
        }
        if ((local_14 == (int *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if ((local_14 == (int *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[60] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x3c;
        goto LAB_004931c0;
      case 0x3d:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[61] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x3d;
        goto LAB_004931c0;
      case 0x3e:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00493188;
        }
        if (local_14 == (int *)0x3e) {
          local_14=(int *)((int *)fn_00483670((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (int *)0x3d) {
            (*(uint **)&scannerContext.state.current) = local_1c;
            local_48=(uint *)(local_1c);
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_48=(uint *)(local_18);
            (*(uint **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[62] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x3e;
        goto LAB_004931c0;
      case 0x3f:
        if ((char)local_14[0x1a3c00] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = sVar5;
        goto LAB_004931c0;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          local_20=(undefined *)((undefined *)(uint)scannerUnicodeFlags[64]);
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_48),(char *)(puVar4),(char **)(&local_18),(ScanWord *)(&local_14));
          scannerUnicodeFlags[64] = (byte)local_20;
          (*(uint **)&scannerContext.state.current) = local_48;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x40;
        goto LAB_004931c0;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_00492722_caseD_41;
      case 0x5c:
        if (scannerCharacterFlags[92] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x5c;
        goto LAB_004931c0;
      case 0x5e:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[94] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x5e;
        goto LAB_004931c0;
      case 0x7c:
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x7c) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (local_14 == (int *)0x3d) {
          local_48=(uint *)(local_18);
          (*(uint **)&scannerContext.state.current) = local_18;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00493188;
        }
        if (scannerCharacterFlags[124] != '\0') goto LAB_00492be1;
        (*(uint **)&scannerContext.state.current) = local_48;
        *param_1 = 0x7c;
        goto LAB_004931c0;
      }
    } while( true );
  }
  if ((*(byte *)(local_14 + 0x19fc00) & 1) == 0) {
    if ((*(byte *)(local_14 + 0x19fc00) & 0x10) != 0) goto switchD_00492722_caseD_30;
    if ((char)local_14[0x1a3c00] != '\0') goto LAB_00492cb0;
    goto LAB_00492715;
  }
switchD_00492722_caseD_41:
  fn_0047db20((char **)(&local_48),(char *)(puVar4),(char **)(&local_18),(ScanWord *)(&local_14));
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_14 == (int *)0x27) {
    sVar5=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar5;
    if (*param_1 != 0) {
      local_48=(uint *)(local_18);
      scannerLiteralBuffer.length = 0;
LAB_0049301c:
      fn_0047d1e0((uint)(local_14),(char **)(&local_48),(char *)(puVar4));
      (*(uint **)&scannerContext.state.current) = local_48;
      *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
      *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
      *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
      goto LAB_00493188;
    }
  }
  else if (local_14 == (int *)0x22) {
    sVar5=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar5;
    if (*param_1 != 0) {
      local_48=(uint *)(local_18);
      scannerLiteralBuffer.length = 0;
      goto LAB_0049301c;
    }
  }
  (*(uint **)&scannerContext.state.current) = local_48;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00493188;
LAB_004938e0:
  if (local_48 < puVar4) {
    uVar8=(uint)(*local_48);
    local_14=(int *)((int *)(uVar8 >> 8 & 0xff00 | uVar8 >> 0x18 | (uVar8 & 0xff00) << 8 | uVar8 << 0x18));
    local_48=(uint *)(local_48 + 1);
  }
  else {
    local_48=(uint *)(puVar4);
    local_14=(int *)((int *)0x0);
  }
  if ((local_14 == (int *)0x2f) && (piStack_40 == (int *)0x2a)) goto LAB_00493a2e;
  if (local_14 != (int *)0x0) {
    if ((local_14 == (int *)0xd) || (local_14 == (int *)0xa)) {
      if (local_14 == (int *)0xd) {
        if (local_48 < puVar4) {
          local_18=(uint *)(local_48 + 1);
          uVar8=(uint)(*local_48);
          uVar8=(uint)(uVar8 >> 8 & 0xff00 | uVar8 >> 0x18 | (uVar8 & 0xff00) << 8 | uVar8 << 0x18);
        }
        else {
          local_18=(uint *)(puVar4);
          uVar8=(uint)(0);
        }
        if (uVar8 == 10) {
          local_48=(uint *)(local_18);
        }
      }
      puVar2=(uint *)(local_48);
      if ((*(uint **)&scannerContext.state.line) < local_48) {
        (*(uint **)&scannerContext.state.line) = local_48;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar8=(uint)(0);
        }
        else {
          uVar8=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar8 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_48 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(uint **)&scannerContext.state.current) = puVar2;
      local_14=(int *)((int *)0xa);
      goto LAB_00493998;
    }
    if (local_14 != (int *)0x5c) goto LAB_00493998;
    iVar6=(int)(fn_00484a20((char *)(local_48),(char *)(puVar4),(char **)(&puStack_30)));
    if ((iVar6 == 0xd) || (iVar6 == 10)) {
      local_48=(uint *)(puStack_30);
      if ((iVar6 == 0xd) && (iVar6 = fn_00484a20((char *)(puStack_30),(char *)(puVar4),(char **)(&puStack_30)), iVar6 == 10)) {
        local_48=(uint *)(puStack_30);
      }
      fn_004816a0((char *)(local_48));
      bVar1=(bool)(true);
    }
    else {
      bVar1=(bool)(false);
    }
    if (!bVar1) {
LAB_00493998:
      piStack_40=(int *)(local_14);
      if (scannerNative0070f071 != '\0') {
        iVar6 = (int)(((int)local_48 - (int)puVar9) + ((int)local_48 - (int)puVar9 >> 0x1f & 3U)) >>
                2;
        puVar2=(uint *)(puVar9);
        iVar3=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar6) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar6);
          iVar3=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar9 = local_48, scannerLiteralBuffer.length = iVar3, iVar6 != 0; iVar6 = iVar6 - 1) {
          scannerLiteralBuffer.length = iVar3 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar2;
          puVar2=(uint *)((uint *)((int)puVar2 + 1));
          iVar3=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_004938e0;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 8),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_00493a2e:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(uint **)&scannerContext.state.current) = local_48;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_00492431;
  }
  if (local_14 == (int *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar6=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar6) = 0x2f;
  }
  (*(uint **)&scannerContext.state.current) = local_48;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00493188;
LAB_00493080:
  if (local_48 < puVar4) {
    local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(1)));
  }
  else {
    local_14=(int *)((int *)0x0);
  }
  if (local_24 == local_14) goto LAB_00493f30;
  if ((local_14 == (int *)0x0) || (local_14 == (int *)0xd) || (local_14 == (int *)0xa))
  goto LAB_00493e94;
  local_48=(uint *)(local_18);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar6=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar6) = (*(byte *)((char *)&local_14+0));
  goto LAB_00493080;
switchD_00492722_caseD_0:
  if (scannerCharacterFlags[0] != '\0') {
LAB_00492be1:
    local_18=(uint *)(local_48);
    do {
      if (scannerNative0070f071 != '\0') {
        iVar6 = (int)(((int)local_48 - (int)puVar9) + ((int)local_48 - (int)puVar9 >> 0x1f & 3U)) >>
                2;
        puVar2=(uint *)(puVar9);
        iVar3=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar6) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar6);
          iVar3=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar9 = local_48, scannerLiteralBuffer.length = iVar3, iVar6 != 0; iVar6 = iVar6 - 1) {
          scannerLiteralBuffer.length = iVar3 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar3) = (char)*puVar2;
          puVar2=(uint *)((uint *)((int)puVar2 + 1));
          iVar3=(int)(scannerLiteralBuffer.length);
        }
      }
LAB_00492cb0:
      do {
        local_14=(int *)((int *)fn_00483670((char *)(local_48),(char *)(puVar4),(char **)(&local_18),(ScanByte)(1)));
        if ((local_14 == (int *)0xd) || (local_14 == (int *)0xa) || (local_14 == (int *)0x0)) {
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          if (scannerNative0070f071 != '\0') {
            (*(uint **)&scannerContext.state.current) = local_48;
            *param_1 = -0x11;
            *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
            *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
            *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
            goto LAB_00493188;
          }
          (*(uint **)&scannerContext.state.current) = local_48;
          goto LAB_00492431;
        }
        local_48=(uint *)(local_18);
        if (local_14 != (int *)0x5c) break;
        iVar6=(int)(fn_00484a20((char *)(local_18),(char *)(puVar4),(char **)(&local_2c)));
        if ((iVar6 == 0xd) || (iVar6 == 10)) {
          local_48=(uint *)(local_2c);
          if ((iVar6 == 0xd) && (iVar6 = fn_00484a20((char *)(local_2c),(char *)(puVar4),(char **)(&local_2c)), iVar6 == 10)) {
            local_48=(uint *)(local_2c);
          }
          fn_004816a0((char *)(local_48));
          bVar1=(bool)(true);
        }
        else {
          bVar1=(bool)(false);
        }
      } while (bVar1);
    } while( true );
  }
  (*(uint **)&scannerContext.state.current) = local_48;
  *param_1 = 0;
LAB_004931c0:
  if ((*(uint **)&scannerContext.state.current) < (*(uint **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(uint **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar6=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(uint **)&scannerContext.state.line) = (uint *)(iVar6 + (*(uint *)&scannerContext.text));
  }
  scannerNative00725d94 = (undefined1)*param_1;
  *(undefined1 **)(param_1 + 2) = &scannerNative00725d94;
  param_1[4] = 1;
  param_1[5] = 0;
  *(int *)(param_1 + 0xc) = (int)(*(uint **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
LAB_00493e94:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_00493f30:
  (*(uint **)&scannerContext.state.current) = local_18;
  local_48=(uint *)(local_18);
  if (local_24 == (int *)0x3e) {
    sVar5=(short)(-0x10);
  }
  else {
    sVar5=(short)(-0xf);
  }
  *param_1 = sVar5;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_00493188:
  if ((*(uint **)&scannerContext.state.current) < (*(uint **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(uint **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar6=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(uint **)&scannerContext.state.line) = (uint *)(iVar6 + (*(uint *)&scannerContext.text));
  }
  *(int *)(param_1 + 0xc) = (int)(*(uint **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_00494070(ScanToken *token)
{
 short *param_1=(short *)token;
  bool bVar1;
  int iVar2;
  byte bVar3;
  int *piVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  char cVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  int *local_40;
  int *local_3c;
  int *piStack_38;
  undefined *local_34;
  undefined *local_30;
  undefined *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  int *local_20;
  int *local_1c;
  int *local_18;
  int *local_14;
  piVar4=(int *)((*(int **)&scannerContext.end));
  local_40=(int *)((*(int **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_28=(undefined4 *)(&(*(int **)&scannerContext.state.current));
  local_24=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_20=(int *)(&(*(uint *)&scannerContext.previous.current));
  local_3c=(int *)((int *)&(*(int **)&scannerContext.state.current));
  local_2c=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_30=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
LAB_004940c1:
  piVar11=(int *)(local_40);
  if (local_40 < piVar4) {
    if (local_40 < piVar4) {
      local_18=(int *)(local_40 + 1);
      local_14=(int *)((int *)*local_40);
    }
    else {
      local_18=(int *)(piVar4);
      local_14=(int *)((int *)0x0);
    }
    if ((local_14 == (int *)0x9) || ((int)local_14 - 0xbU < 2) || (local_14 == (int *)0x1a) ||
       (local_14 == (int *)0x20)) {
      local_40=(int *)(local_18);
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      goto LAB_004940c1;
    }
    if (local_14 == (int *)0x5c) {
      if (local_18 < piVar4) {
        local_1c=(int *)(local_18 + 1);
        local_14=(int *)((int *)*local_18);
      }
      else {
        local_1c=(int *)(piVar4);
        local_14=(int *)((int *)0x0);
      }
      if ((local_14 != (int *)0xd) && (local_14 != (int *)0xa)) goto LAB_004941f0;
      local_40=(int *)(local_1c);
      if (local_14 == (int *)0xd) {
        if (local_1c < piVar4) {
          local_18=(int *)(local_1c + 1);
          iVar7=(int)(*local_1c);
        }
        else {
          local_18=(int *)(piVar4);
          iVar7=(int)(0);
        }
        if (iVar7 == 10) {
          local_40=(int *)(local_18);
        }
      }
      piVar11=(int *)(local_40);
      if ((*(int **)&scannerContext.state.line) < local_40) {
        (*(int **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar6=(uint)(0);
        }
        else {
          uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar6 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(int **)&scannerContext.state.current) = piVar11;
      goto LAB_004940c1;
    }
  }
LAB_004941f0:
  (*(int **)&scannerContext.state.current) = local_40;
  *local_24 = *local_28;
  local_24[1] = local_28[1];
  local_24[2] = local_28[2];
  local_24[3] = local_28[3];
  piVar9=(int *)(local_20);
  if (local_20 == (int *)0x0) {
    piVar9=(int *)(local_3c);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *piVar9 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = piVar9[3];
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_40),(ScanByte)(0)));
  if (local_14 == (int *)0x0) {
    if (scannerCharacterFlags[0] != '\0') goto LAB_00494780;
    (*(int **)&scannerContext.state.current) = local_40;
    *param_1 = 0;
    goto LAB_00494d30;
  }
  piVar9=(int *)(local_14);
  if ((scannerNative00725f3f == '\0') || (local_14 > (int *)0xffff)) {
LAB_00494307:
    do {
      local_14=(int *)(piVar9);
      bVar3=(byte)(scannerUnicodeFlags[64]);
      sVar5=(short)((short)local_14);
      switch((uint)local_14) {
      case 0x0:
        goto switchD_00494314_caseD_0;
      default:
        if ((local_14 > (int *)0xffff) || ((*(byte *)(local_14 + 0x19fc00) & 1) != 0))
        goto switchD_00494314_caseD_41;
        if ((local_14 > (int *)0xffff) || ((*(byte *)(local_14 + 0x19fc00) & 0x10) == 0)) {
          if (local_14 < (int *)0x100) {
            if ((char)local_14[0x1a3c00] != '\0') goto LAB_00494780;
            (*(int **)&scannerContext.state.current) = local_40;
            *param_1 = sVar5;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_00494780;
            (*(int **)&scannerContext.state.current) = local_40;
            *param_1 = -6;
          }
          goto LAB_00494d30;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_00494314_caseD_30:
        local_34=(undefined *)(local_30);
        while( true ) {
          piVar9=(int *)(local_14);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar7=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_14+0));
          local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 > (int *)0x7f) ||
             ((*(byte *)(local_14 + 0x19fc00) & 0x11) == 0 &&
             ((local_14 != (int *)0x2b && (local_14 != (int *)0x2d)) ||
             (piVar9 != (int *)0x45 &&
             (piVar9 != (int *)0x65 && (piVar9 != (int *)0x50) && (piVar9 != (int *)0x70)))) &&
             (local_14 != (int *)0x2e))) break;
          local_40=(int *)(local_18);
        }
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           ((piVar9 > (int *)0x2f && (piVar9 < (int *)0x3a)) ||
           (piVar9 > (int *)0xffff || ((*(byte *)(piVar9 + 0x19fc00) & 0x10) == 0)))) {
          (*(int **)&scannerContext.state.current) = local_40;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00494d01;
        }
        break;
      case 0xa:
      case 0xd:
        if ((*(int **)&scannerContext.state.line) < local_40) {
          (*(int **)&scannerContext.state.line) = local_40;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar6=(uint)(0);
          }
          else {
            uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar6 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_00494d01;
      case 0x21:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[33] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x21;
        goto LAB_00494d30;
      case 0x22:
        if ((*(byte *)(local_14 + 0x19fc00) & 0x20) != 0) goto LAB_00494be0;
      case 0x27:
        if (local_14 == (int *)0x27) {
          sVar5=(short)(-9);
        }
        else {
          sVar5=(short)(-0xc);
        }
        *param_1 = sVar5;
        goto LAB_00494b98;
      case 0x23:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x23) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x23);
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[35] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x23;
        goto LAB_00494d30;
      case 0x25:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if ((local_14 == (int *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(int *)(local_18);
          local_14=(int *)((int *)fn_00483a30((char *)(local_18),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 == (int *)0x25) &&
             (local_14 = (int *)fn_00483a30((char *)(local_18),(char *)(piVar4),(char **)(&local_1c),(ScanByte)(0)),
             local_14 == (int *)0x3a)) {
            local_40=(int *)(local_1c);
            (*(int **)&scannerContext.state.current) = local_1c;
            *param_1 = -0x12;
            *(undefined **)(param_1 + 2) = &scannerNative0067de55;
            param_1[4] = 4;
            param_1[5] = 0;
          }
          else {
            (*(int **)&scannerContext.state.current) = local_40;
            *param_1 = 0x23;
            *(undefined **)(param_1 + 2) = &scannerNative0067de51;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00494d01;
        }
        if ((local_14 == (int *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[37] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x25;
        goto LAB_00494d30;
      case 0x26:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x26) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[38] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x26;
        goto LAB_00494d30;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if ((char)local_14[0x1a3c00] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = sVar5;
        goto LAB_00494d30;
      case 0x2a:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[42] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2a;
        goto LAB_00494d30;
      case 0x2b:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x2b) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[43] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2b;
        goto LAB_00494d30;
      case 0x2d:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3e) {
          local_14=(int *)((int *)fn_00483a30((char *)(local_18),(char *)(piVar4),(char **)(&local_1c),(ScanByte)(0)));
          if ((scannerNative0070f1a8 == '\0') || (local_14 != (int *)0x2a)) {
            local_40=(int *)(local_18);
            (*(int **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            local_40=(int *)(local_1c);
            (*(int **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_00494d01;
        }
        if (local_14 == (int *)0x2d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[45] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2d;
        goto LAB_00494d30;
      case 0x2e:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x2e) {
          local_14=(int *)((int *)fn_00483a30((char *)(local_18),(char *)(piVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (int *)0x2e) {
            local_40=(int *)(local_1c);
            (*(int **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            local_14=(int *)((int *)0x2e);
            goto LAB_00494d01;
          }
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_14 == (int *)0x2a)) {
            local_40=(int *)(local_18);
            (*(int **)&scannerContext.state.current) = local_18;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            local_14=(int *)((int *)0x2a);
            goto LAB_00494d01;
          }
          if ((local_14 < (int *)0x10000) && ((*(byte *)(local_14 + 0x19fc00) & 0x10) != 0)) {
            local_14=(int *)((int *)0x2e);
            goto switchD_00494314_caseD_30;
          }
        }
        if (scannerCharacterFlags[46] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2e;
        goto LAB_00494d30;
      case 0x2f:
        scannerCommentBuffer.length = 0;
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_00494850;
          if (scannerNative0070f1ca != '\0') goto LAB_00494850;
          if (scannerNative0070f1af == '\0') goto LAB_00494850;
        }
        if (local_14 == (int *)0x2a) {
          piStack_38=(int *)((int *)0x0);
          local_40=(int *)(local_18);
          local_34=(undefined *)(local_30);
          goto LAB_004953a0;
        }
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[47] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2f;
        goto LAB_00494d30;
      case 0x3a:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if ((scannerNative0070f1a8 != '\0') && (local_14 == (int *)0x3a)) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if ((local_14 == (int *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[58] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3a;
        goto LAB_00494d30;
      case 0x3c:
        if ((*(byte *)(local_14 + 0x19fc00) & 0x20) != 0) {
LAB_00494be0:
          if (local_14 == (int *)0x3c) {
            cVar8=(char)('>');
          }
          else {
            cVar8=(char)('\"');
          }
          local_20=(int *)((int *)(int)cVar8);
          goto LAB_00494c00;
        }
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (local_14 == (int *)0x3c) {
          local_14=(int *)((int *)fn_00483a30((char *)(local_18),(char *)(piVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (int *)0x3d) {
            local_40=(int *)(local_1c);
            (*(int **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_40=(int *)(local_18);
            (*(int **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00494d01;
        }
        if ((local_14 == (int *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if ((local_14 == (int *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[60] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3c;
        goto LAB_00494d30;
      case 0x3d:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[61] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3d;
        goto LAB_00494d30;
      case 0x3e:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00494d01;
        }
        if (local_14 == (int *)0x3e) {
          local_14=(int *)((int *)fn_00483a30((char *)(local_18),(char *)(piVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (int *)0x3d) {
            local_40=(int *)(local_1c);
            (*(int **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_40=(int *)(local_18);
            (*(int **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[62] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3e;
        goto LAB_00494d30;
      case 0x3f:
        if ((char)local_14[0x1a3c00] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = sVar5;
        goto LAB_00494d30;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_40),(char *)(piVar4),(char **)(&local_18),(ScanWord *)(&local_14));
          (*(int **)&scannerContext.state.current) = local_40;
          scannerUnicodeFlags[64] = bVar3;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x40;
        goto LAB_00494d30;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_00494314_caseD_41;
      case 0x5c:
        if (scannerCharacterFlags[92] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5c;
        goto LAB_00494d30;
      case 0x5e:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(int *)((int *)0x3d);
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[94] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5e;
        goto LAB_00494d30;
      case 0x7c:
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (int *)0x7c) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (local_14 == (int *)0x3d) {
          local_40=(int *)(local_18);
          (*(int **)&scannerContext.state.current) = local_18;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00494d01;
        }
        if (scannerCharacterFlags[124] != '\0') goto LAB_00494780;
        (*(int **)&scannerContext.state.current) = local_40;
        *param_1 = 0x7c;
        goto LAB_00494d30;
      }
    } while( true );
  }
  if ((*(byte *)(local_14 + 0x19fc00) & 1) == 0) {
    if ((*(byte *)(local_14 + 0x19fc00) & 0x10) != 0) goto switchD_00494314_caseD_30;
    if ((char)local_14[0x1a3c00] != '\0') goto LAB_00494850;
    goto LAB_00494307;
  }
switchD_00494314_caseD_41:
  fn_0047db20((char **)(&local_40),(char *)(piVar4),(char **)(&local_18),(ScanWord *)(&local_14));
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_14 == (int *)0x27) {
    sVar5=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar5;
    if (*param_1 != 0) {
      local_40=(int *)(local_18);
      scannerLiteralBuffer.length = 0;
LAB_00494b98:
      fn_0047d1e0((uint)(local_14),(char **)(&local_40),(char *)(piVar4));
      (*(int **)&scannerContext.state.current) = local_40;
      *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
      *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
      *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
      goto LAB_00494d01;
    }
  }
  else if (local_14 == (int *)0x22) {
    sVar5=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar5;
    if (*param_1 != 0) {
      local_40=(int *)(local_18);
      scannerLiteralBuffer.length = 0;
      goto LAB_00494b98;
    }
  }
  (*(int **)&scannerContext.state.current) = local_40;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00494d01;
LAB_004953a0:
  if (local_40 < piVar4) {
    local_14=(int *)((int *)*local_40);
    local_40=(int *)(local_40 + 1);
  }
  else {
    local_40=(int *)(piVar4);
    local_14=(int *)((int *)0x0);
  }
  if ((local_14 == (int *)0x2f) && (piStack_38 == (int *)0x2a)) goto LAB_004954de;
  if (local_14 != (int *)0x0) {
    if ((local_14 == (int *)0xd) || (local_14 == (int *)0xa)) {
      if (local_14 == (int *)0xd) {
        if (local_40 < piVar4) {
          local_18=(int *)(local_40 + 1);
          iVar7=(int)(*local_40);
        }
        else {
          local_18=(int *)(piVar4);
          iVar7=(int)(0);
        }
        if (iVar7 == 10) {
          local_40=(int *)(local_18);
        }
      }
      piVar9=(int *)(local_40);
      if ((*(int **)&scannerContext.state.line) < local_40) {
        (*(int **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar6=(uint)(0);
        }
        else {
          uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar6 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(int **)&scannerContext.state.current) = piVar9;
      local_14=(int *)((int *)0xa);
      goto LAB_00495450;
    }
    if (local_14 != (int *)0x5c) goto LAB_00495450;
    if (local_40 < piVar4) {
      piVar9=(int *)(local_40 + 1);
      iVar7=(int)(*local_40);
    }
    else {
      iVar7=(int)(0);
      piVar9=(int *)(piVar4);
    }
    if ((iVar7 == 0xd) || (iVar7 == 10)) {
      local_40=(int *)(piVar9);
      if (iVar7 == 0xd) {
        if (piVar9 < piVar4) {
          piVar10=(int *)(piVar9 + 1);
          iVar7=(int)(*piVar9);
        }
        else {
          iVar7=(int)(0);
          piVar10=(int *)(piVar4);
        }
        if (iVar7 == 10) {
          local_40=(int *)(piVar10);
        }
      }
      piVar9=(int *)(local_40);
      if ((*(int **)&scannerContext.state.line) < local_40) {
        (*(int **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar6=(uint)(0);
        }
        else {
          uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar6 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      bVar1=(bool)(true);
      (*(int **)&scannerContext.state.current) = piVar9;
    }
    else {
      bVar1=(bool)(false);
    }
    if (!bVar1) {
LAB_00495450:
      piStack_38=(int *)(local_14);
      if (scannerNative0070f071 != '\0') {
        iVar7 = (int)(((int)local_40 - (int)piVar11) + ((int)local_40 - (int)piVar11 >> 0x1f & 3U))
                >> 2;
        piVar9=(int *)(piVar11);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar7) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar7);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; piVar11 = local_40, scannerLiteralBuffer.length = iVar2, iVar7 != 0; iVar7 = iVar7 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = (char)*piVar9;
          piVar9=(int *)((int *)((int)piVar9 + 1));
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_004953a0;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 8),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_004954de:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(int **)&scannerContext.state.current) = local_40;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_004940c1;
  }
  if (local_14 == (int *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar7=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = 0x2f;
  }
  (*(int **)&scannerContext.state.current) = local_40;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00494d01;
LAB_00494c00:
  if (local_40 < piVar4) {
    local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(1)));
  }
  else {
    local_14=(int *)((int *)0x0);
  }
  if (local_20 == local_14) goto LAB_00495970;
  if ((local_14 == (int *)0x0) || (local_14 == (int *)0xd) || (local_14 == (int *)0xa))
  goto LAB_004958e4;
  local_40=(int *)(local_18);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar7=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar7) = (*(byte *)((char *)&local_14+0));
  goto LAB_00494c00;
switchD_00494314_caseD_0:
  if (scannerCharacterFlags[0] != '\0') {
LAB_00494780:
    local_18=(int *)(local_40);
    do {
      if (scannerNative0070f071 != '\0') {
        iVar7 = (int)(((int)local_40 - (int)piVar11) + ((int)local_40 - (int)piVar11 >> 0x1f & 3U))
                >> 2;
        piVar9=(int *)(piVar11);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar7) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar7);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; piVar11 = local_40, scannerLiteralBuffer.length = iVar2, iVar7 != 0; iVar7 = iVar7 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = (char)*piVar9;
          piVar9=(int *)((int *)((int)piVar9 + 1));
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
LAB_00494850:
      do {
        local_14=(int *)((int *)fn_00483a30((char *)(local_40),(char *)(piVar4),(char **)(&local_18),(ScanByte)(1)));
        if ((local_14 == (int *)0xd) || (local_14 == (int *)0xa) || (local_14 == (int *)0x0)) {
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          if (scannerNative0070f071 != '\0') {
            (*(int **)&scannerContext.state.current) = local_40;
            *param_1 = -0x11;
            *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
            *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
            *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
            goto LAB_00494d01;
          }
          (*(int **)&scannerContext.state.current) = local_40;
          goto LAB_004940c1;
        }
        local_40=(int *)(local_18);
        if (local_14 != (int *)0x5c) break;
        if (local_18 < piVar4) {
          piVar9=(int *)(local_18 + 1);
          iVar7=(int)(*local_18);
        }
        else {
          iVar7=(int)(0);
          piVar9=(int *)(piVar4);
        }
        if ((iVar7 == 0xd) || (iVar7 == 10)) {
          local_40=(int *)(piVar9);
          if (iVar7 == 0xd) {
            if (piVar9 < piVar4) {
              piVar10=(int *)(piVar9 + 1);
              iVar7=(int)(*piVar9);
            }
            else {
              iVar7=(int)(0);
              piVar10=(int *)(piVar4);
            }
            if (iVar7 == 10) {
              local_40=(int *)(piVar10);
            }
          }
          piVar9=(int *)(local_40);
          if ((*(int **)&scannerContext.state.line) < local_40) {
            (*(int **)&scannerContext.state.line) = local_40;
            scannerContext.state.column = scannerContext.state.column + 1;
            if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
              uVar6=(uint)(0);
            }
            else {
              uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
            }
            if (uVar6 < scannerContext.state.column) {
              sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
            }
          }
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          bVar1=(bool)(true);
          (*(int **)&scannerContext.state.current) = piVar9;
        }
        else {
          bVar1=(bool)(false);
        }
      } while (bVar1);
    } while( true );
  }
  (*(int **)&scannerContext.state.current) = local_40;
  *param_1 = 0;
LAB_00494d30:
  if ((*(int **)&scannerContext.state.current) < (*(int **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(int **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar7=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(int **)&scannerContext.state.line) = (int *)(iVar7 + (*(uint *)&scannerContext.text));
  }
  scannerNative00716ec2 = (undefined1)*param_1;
  *(undefined1 **)(param_1 + 2) = &scannerNative00716ec2;
  param_1[4] = 1;
  param_1[5] = 0;
  *(int *)(param_1 + 0xc) = (int)(*(int **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
LAB_004958e4:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(int **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_00495970:
  (*(int **)&scannerContext.state.current) = local_18;
  local_40=(int *)(local_18);
  if (local_20 == (int *)0x3e) {
    sVar5=(short)(-0x10);
  }
  else {
    sVar5=(short)(-0xf);
  }
  *param_1 = sVar5;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_00494d01:
  if ((*(int **)&scannerContext.state.current) < (*(int **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(int **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar7=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(int **)&scannerContext.state.line) = (int *)(iVar7 + (*(uint *)&scannerContext.text));
  }
  *(int *)(param_1 + 0xc) = (int)(*(int **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_00495aa0(ScanToken *token)
{
 short *param_1=(short *)token;
  bool bVar1;
  int iVar2;
  byte bVar3;
  ushort *puVar4;
  short sVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  ushort *puVar9;
  char cVar10;
  ushort *puVar11;
  ushort *local_40;
  ushort *local_3c;
  ushort *puStack_38;
  undefined *local_34;
  undefined *local_30;
  undefined *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  ushort *local_20;
  ushort *local_1c;
  ushort *local_18;
  ushort *local_14;
  puVar4=(ushort *)((*(ushort **)&scannerContext.end));
  local_40=(ushort *)((*(ushort **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_28=(undefined4 *)(&(*(ushort **)&scannerContext.state.current));
  local_24=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_20=(ushort *)((ushort *)&(*(uint *)&scannerContext.previous.current));
  local_3c=(ushort *)((ushort *)&(*(ushort **)&scannerContext.state.current));
  local_2c=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_30=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
LAB_00495af1:
  puVar11=(ushort *)(local_40);
  if (local_40 < puVar4) {
    if (local_40 < puVar4) {
      local_18=(ushort *)(local_40 + 1);
      local_14=(ushort *)((ushort *)((*local_40 & 0xff) << 8 | (int)(uint)*local_40 >> 8));
    }
    else {
      local_18=(ushort *)(puVar4);
      local_14=(ushort *)((ushort *)0x0);
    }
    if ((local_14 == (ushort *)0x9) || ((int)local_14 - 0xbU < 2) || (local_14 == (ushort *)0x1a) ||
       (local_14 == (ushort *)0x20)) {
      local_40=(ushort *)(local_18);
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      goto LAB_00495af1;
    }
    if (local_14 == (ushort *)0x5c) {
      if (local_18 < puVar4) {
        local_1c=(ushort *)(local_18 + 1);
        local_14=(ushort *)((ushort *)((*local_18 & 0xff) << 8 | (int)(uint)*local_18 >> 8));
      }
      else {
        local_1c=(ushort *)(puVar4);
        local_14=(ushort *)((ushort *)0x0);
      }
      if ((local_14 != (ushort *)0xd) && (local_14 != (ushort *)0xa)) goto LAB_00495c50;
      local_40=(ushort *)(local_1c);
      if (local_14 == (ushort *)0xd) {
        if (local_1c < puVar4) {
          local_18=(ushort *)(local_1c + 1);
          uVar7=(uint)((*local_1c & 0xff) << 8 | (int)(uint)*local_1c >> 8);
        }
        else {
          local_18=(ushort *)(puVar4);
          uVar7=(uint)(0);
        }
        if (uVar7 == 10) {
          local_40=(ushort *)(local_18);
        }
      }
      puVar11=(ushort *)(local_40);
      if ((*(ushort **)&scannerContext.state.line) < local_40) {
        (*(ushort **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar7=(uint)(0);
        }
        else {
          uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar7 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar11;
      goto LAB_00495af1;
    }
  }
LAB_00495c50:
  (*(ushort **)&scannerContext.state.current) = local_40;
  *local_24 = *local_28;
  local_24[1] = local_28[1];
  local_24[2] = local_28[2];
  local_24[3] = local_28[3];
  puVar8=(ushort *)(local_20);
  if (local_20 == (ushort *)0x0) {
    puVar8=(ushort *)(local_3c);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *(int *)puVar8 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = *(int *)(puVar8 + 6);
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_40),(ScanByte)(0)));
  if (local_14 == (ushort *)0x0) {
    if (scannerCharacterFlags[0] != '\0') goto LAB_004961e0;
    (*(ushort **)&scannerContext.state.current) = local_40;
    *param_1 = 0;
    goto LAB_00496790;
  }
  puVar8=(ushort *)(local_14);
  if ((scannerNative00725f3f == '\0') || (local_14 > (ushort *)0xffff)) {
LAB_00495d65:
    do {
      local_14=(ushort *)(puVar8);
      bVar3=(byte)(scannerUnicodeFlags[64]);
      sVar5=(short)((short)local_14);
      switch((uint)local_14) {
      case 0x0:
        goto switchD_00495d72_caseD_0;
      default:
        if ((local_14 > (ushort *)0xffff) || ((local_14[0x33f800] & 1) != 0))
        goto switchD_00495d72_caseD_41;
        if ((local_14 > (ushort *)0xffff) || ((local_14[0x33f800] & 0x10) == 0)) {
          if (local_14 < (ushort *)0x100) {
            if ((char)local_14[0x347800] != '\0') goto LAB_004961e0;
            (*(ushort **)&scannerContext.state.current) = local_40;
            *param_1 = sVar5;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_004961e0;
            (*(ushort **)&scannerContext.state.current) = local_40;
            *param_1 = -6;
          }
          goto LAB_00496790;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_00495d72_caseD_30:
        local_34=(undefined *)(local_30);
        while( true ) {
          puVar8=(ushort *)(local_14);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar6=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar6) = (*(byte *)((char *)&local_14+0));
          local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 > (ushort *)0x7f) ||
             ((local_14[0x33f800] & 0x11) == 0 &&
             ((local_14 != (ushort *)0x2b && (local_14 != (ushort *)0x2d)) ||
             (puVar8 != (ushort *)0x45 &&
             (puVar8 != (ushort *)0x65 && (puVar8 != (ushort *)0x50) && (puVar8 != (ushort *)0x70)))
             ) && (local_14 != (ushort *)0x2e))) break;
          local_40=(ushort *)(local_18);
        }
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           ((puVar8 > (ushort *)0x2f && (puVar8 < (ushort *)0x3a)) ||
           (puVar8 > (ushort *)0xffff || ((puVar8[0x33f800] & 0x10) == 0)))) {
          (*(ushort **)&scannerContext.state.current) = local_40;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00496761;
        }
        break;
      case 0xa:
      case 0xd:
        if ((*(ushort **)&scannerContext.state.line) < local_40) {
          (*(ushort **)&scannerContext.state.line) = local_40;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar7=(uint)(0);
          }
          else {
            uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar7 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_00496761;
      case 0x21:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[33] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x21;
        goto LAB_00496790;
      case 0x22:
        if ((local_14[0x33f800] & 0x20) != 0) goto LAB_00496640;
      case 0x27:
        if (local_14 == (ushort *)0x27) {
          sVar5=(short)(-9);
        }
        else {
          sVar5=(short)(-0xc);
        }
        *param_1 = sVar5;
        goto LAB_004965f8;
      case 0x23:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x23) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x23);
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[35] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x23;
        goto LAB_00496790;
      case 0x25:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if ((local_14 == (ushort *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_18),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 == (ushort *)0x25) &&
             (local_14 = (ushort *)fn_00483df0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)),
             local_14 == (ushort *)0x3a)) {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = -0x12;
            *(undefined **)(param_1 + 2) = &scannerNative0067de55;
            param_1[4] = 4;
            param_1[5] = 0;
          }
          else {
            (*(ushort **)&scannerContext.state.current) = local_40;
            *param_1 = 0x23;
            *(undefined **)(param_1 + 2) = &scannerNative0067de51;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00496761;
        }
        if ((local_14 == (ushort *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[37] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x25;
        goto LAB_00496790;
      case 0x26:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x26) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[38] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x26;
        goto LAB_00496790;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if ((char)local_14[0x347800] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = sVar5;
        goto LAB_00496790;
      case 0x2a:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[42] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2a;
        goto LAB_00496790;
      case 0x2b:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x2b) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[43] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2b;
        goto LAB_00496790;
      case 0x2d:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3e) {
          local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if ((scannerNative0070f1a8 == '\0') || (local_14 != (ushort *)0x2a)) {
            local_40=(ushort *)(local_18);
            (*(ushort **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_00496761;
        }
        if (local_14 == (ushort *)0x2d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[45] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2d;
        goto LAB_00496790;
      case 0x2e:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x2e) {
          local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (ushort *)0x2e) {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            local_14=(ushort *)((ushort *)0x2e);
            goto LAB_00496761;
          }
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_14 == (ushort *)0x2a)) {
            local_40=(ushort *)(local_18);
            (*(ushort **)&scannerContext.state.current) = local_18;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            local_14=(ushort *)((ushort *)0x2a);
            goto LAB_00496761;
          }
          if ((local_14 < (ushort *)0x10000) && ((local_14[0x33f800] & 0x10) != 0)) {
            local_14=(ushort *)((ushort *)0x2e);
            goto switchD_00495d72_caseD_30;
          }
        }
        if (scannerCharacterFlags[46] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2e;
        goto LAB_00496790;
      case 0x2f:
        scannerCommentBuffer.length = 0;
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_004962b1;
          if (scannerNative0070f1ca != '\0') goto LAB_004962b1;
          if (scannerNative0070f1af == '\0') goto LAB_004962b1;
        }
        if (local_14 == (ushort *)0x2a) {
          local_40=(ushort *)(local_18);
          puStack_38=(ushort *)((ushort *)0x0);
          local_34=(undefined *)(local_30);
          goto LAB_00496e17;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[47] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2f;
        goto LAB_00496790;
      case 0x3a:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if ((scannerNative0070f1a8 != '\0') && (local_14 == (ushort *)0x3a)) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if ((local_14 == (ushort *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[58] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3a;
        goto LAB_00496790;
      case 0x3c:
        if ((local_14[0x33f800] & 0x20) != 0) {
LAB_00496640:
          if (local_14 == (ushort *)0x3c) {
            cVar10=(char)('>');
          }
          else {
            cVar10=(char)('\"');
          }
          local_20=(ushort *)((ushort *)(int)cVar10);
          goto LAB_00496660;
        }
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (local_14 == (ushort *)0x3c) {
          local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (ushort *)0x3d) {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_40=(ushort *)(local_18);
            (*(ushort **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00496761;
        }
        if ((local_14 == (ushort *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if ((local_14 == (ushort *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[60] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3c;
        goto LAB_00496790;
      case 0x3d:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[61] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3d;
        goto LAB_00496790;
      case 0x3e:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_00496761;
        }
        if (local_14 == (ushort *)0x3e) {
          local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (ushort *)0x3d) {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_40=(ushort *)(local_18);
            (*(ushort **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[62] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3e;
        goto LAB_00496790;
      case 0x3f:
        if ((char)local_14[0x347800] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = sVar5;
        goto LAB_00496790;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_40),(char *)(puVar4),(char **)(&local_18),(ScanWord *)(&local_14));
          (*(ushort **)&scannerContext.state.current) = local_40;
          scannerUnicodeFlags[64] = bVar3;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x40;
        goto LAB_00496790;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_00495d72_caseD_41;
      case 0x5c:
        if (scannerCharacterFlags[92] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5c;
        goto LAB_00496790;
      case 0x5e:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[94] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5e;
        goto LAB_00496790;
      case 0x7c:
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x7c) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_00496761;
        }
        if (scannerCharacterFlags[124] != '\0') goto LAB_004961e0;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x7c;
        goto LAB_00496790;
      }
    } while( true );
  }
  if ((local_14[0x33f800] & 1) == 0) {
    if ((local_14[0x33f800] & 0x10) != 0) goto switchD_00495d72_caseD_30;
    if ((char)local_14[0x347800] != '\0') goto LAB_004962b1;
    goto LAB_00495d65;
  }
switchD_00495d72_caseD_41:
  fn_0047db20((char **)(&local_40),(char *)(puVar4),(char **)(&local_18),(ScanWord *)(&local_14));
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_14 == (ushort *)0x27) {
    sVar5=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar5;
    if (*param_1 != 0) {
      local_40=(ushort *)(local_18);
      scannerLiteralBuffer.length = 0;
LAB_004965f8:
      fn_0047d1e0((uint)(local_14),(char **)(&local_40),(char *)(puVar4));
      (*(ushort **)&scannerContext.state.current) = local_40;
      *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
      *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
      *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
      goto LAB_00496761;
    }
  }
  else if (local_14 == (ushort *)0x22) {
    sVar5=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar5;
    if (*param_1 != 0) {
      local_40=(ushort *)(local_18);
      scannerLiteralBuffer.length = 0;
      goto LAB_004965f8;
    }
  }
  (*(ushort **)&scannerContext.state.current) = local_40;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00496761;
LAB_00496e17:
  if (local_40 < puVar4) {
    local_14=(ushort *)((ushort *)((*local_40 & 0xff) << 8 | (int)(uint)*local_40 >> 8));
    local_40=(ushort *)(local_40 + 1);
  }
  else {
    local_40=(ushort *)(puVar4);
    local_14=(ushort *)((ushort *)0x0);
  }
  if ((local_14 == (ushort *)0x2f) && (puStack_38 == (ushort *)0x2a)) goto LAB_00496f5e;
  if (local_14 != (ushort *)0x0) {
    if ((local_14 == (ushort *)0xd) || (local_14 == (ushort *)0xa)) {
      if (local_14 == (ushort *)0xd) {
        if (local_40 < puVar4) {
          local_18=(ushort *)(local_40 + 1);
          uVar7=(uint)((*local_40 & 0xff) << 8 | (int)(uint)*local_40 >> 8);
        }
        else {
          local_18=(ushort *)(puVar4);
          uVar7=(uint)(0);
        }
        if (uVar7 == 10) {
          local_40=(ushort *)(local_18);
        }
      }
      puVar8=(ushort *)(local_40);
      if ((*(ushort **)&scannerContext.state.line) < local_40) {
        (*(ushort **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar7=(uint)(0);
        }
        else {
          uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar7 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar8;
      local_14=(ushort *)((ushort *)0xa);
      goto LAB_00496ecc;
    }
    if (local_14 != (ushort *)0x5c) goto LAB_00496ecc;
    if (local_40 < puVar4) {
      puVar8=(ushort *)(local_40 + 1);
      uVar7=(uint)((*local_40 & 0xff) << 8 | (int)(uint)*local_40 >> 8);
    }
    else {
      uVar7=(uint)(0);
      puVar8=(ushort *)(puVar4);
    }
    if ((uVar7 == 0xd) || (uVar7 == 10)) {
      local_40=(ushort *)(puVar8);
      if (uVar7 == 0xd) {
        if (puVar8 < puVar4) {
          puVar9=(ushort *)(puVar8 + 1);
          uVar7=(uint)((*puVar8 & 0xff) << 8 | (int)(uint)*puVar8 >> 8);
        }
        else {
          uVar7=(uint)(0);
          puVar9=(ushort *)(puVar4);
        }
        if (uVar7 == 10) {
          local_40=(ushort *)(puVar9);
        }
      }
      puVar8=(ushort *)(local_40);
      if ((*(ushort **)&scannerContext.state.line) < local_40) {
        (*(ushort **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar7=(uint)(0);
        }
        else {
          uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar7 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      bVar1=(bool)(true);
      (*(ushort **)&scannerContext.state.current) = puVar8;
    }
    else {
      bVar1=(bool)(false);
    }
    if (!bVar1) {
LAB_00496ecc:
      puStack_38=(ushort *)(local_14);
      if (scannerNative0070f071 != '\0') {
        iVar6 = (int)((((int)local_40 - (int)puVar11) + 1U) -
                     (uint)((uint)((int)local_40 - (int)puVar11) < 0x80000000)) >> 1;
        puVar8=(ushort *)(puVar11);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar6) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar6);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar11 = local_40, scannerLiteralBuffer.length = iVar2, iVar6 != 0; iVar6 = iVar6 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = (char)*puVar8;
          puVar8=(ushort *)((ushort *)((int)puVar8 + 1));
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_00496e17;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 4),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_00496f5e:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(ushort **)&scannerContext.state.current) = local_40;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_00495af1;
  }
  if (local_14 == (ushort *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar6=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar6) = 0x2f;
  }
  (*(ushort **)&scannerContext.state.current) = local_40;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_00496761;
LAB_00496660:
  if (local_40 < puVar4) {
    local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(1)));
  }
  else {
    local_14=(ushort *)((ushort *)0x0);
  }
  if (local_20 == local_14) goto LAB_00497430;
  if ((local_14 == (ushort *)0x0) || (local_14 == (ushort *)0xd) || (local_14 == (ushort *)0xa))
  goto LAB_00497398;
  local_40=(ushort *)(local_18);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar6=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar6) = (*(byte *)((char *)&local_14+0));
  goto LAB_00496660;
switchD_00495d72_caseD_0:
  if (scannerCharacterFlags[0] != '\0') {
LAB_004961e0:
    local_18=(ushort *)(local_40);
    do {
      if (scannerNative0070f071 != '\0') {
        iVar6 = (int)((((int)local_40 - (int)puVar11) + 1U) -
                     (uint)((uint)((int)local_40 - (int)puVar11) < 0x80000000)) >> 1;
        puVar8=(ushort *)(puVar11);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar6) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar6);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar11 = local_40, scannerLiteralBuffer.length = iVar2, iVar6 != 0; iVar6 = iVar6 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = (char)*puVar8;
          puVar8=(ushort *)((ushort *)((int)puVar8 + 1));
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
LAB_004962b1:
      do {
        local_14=(ushort *)((ushort *)fn_00483df0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(1)));
        if ((local_14 == (ushort *)0xd) || (local_14 == (ushort *)0xa) ||
           (local_14 == (ushort *)0x0)) {
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          if (scannerNative0070f071 != '\0') {
            (*(ushort **)&scannerContext.state.current) = local_40;
            *param_1 = -0x11;
            *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
            *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
            *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
            goto LAB_00496761;
          }
          (*(ushort **)&scannerContext.state.current) = local_40;
          goto LAB_00495af1;
        }
        local_40=(ushort *)(local_18);
        if (local_14 != (ushort *)0x5c) break;
        if (local_18 < puVar4) {
          puVar8=(ushort *)(local_18 + 1);
          uVar7=(uint)((*local_18 & 0xff) << 8 | (int)(uint)*local_18 >> 8);
        }
        else {
          uVar7=(uint)(0);
          puVar8=(ushort *)(puVar4);
        }
        if ((uVar7 == 0xd) || (uVar7 == 10)) {
          local_40=(ushort *)(puVar8);
          if (uVar7 == 0xd) {
            if (puVar8 < puVar4) {
              puVar9=(ushort *)(puVar8 + 1);
              uVar7=(uint)((*puVar8 & 0xff) << 8 | (int)(uint)*puVar8 >> 8);
            }
            else {
              uVar7=(uint)(0);
              puVar9=(ushort *)(puVar4);
            }
            if (uVar7 == 10) {
              local_40=(ushort *)(puVar9);
            }
          }
          puVar8=(ushort *)(local_40);
          if ((*(ushort **)&scannerContext.state.line) < local_40) {
            (*(ushort **)&scannerContext.state.line) = local_40;
            scannerContext.state.column = scannerContext.state.column + 1;
            if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
              uVar7=(uint)(0);
            }
            else {
              uVar7=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
            }
            if (uVar7 < scannerContext.state.column) {
              sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
            }
          }
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          bVar1=(bool)(true);
          (*(ushort **)&scannerContext.state.current) = puVar8;
        }
        else {
          bVar1=(bool)(false);
        }
      } while (bVar1);
    } while( true );
  }
  (*(ushort **)&scannerContext.state.current) = local_40;
  *param_1 = 0;
LAB_00496790:
  if ((*(ushort **)&scannerContext.state.current) < (*(ushort **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar6=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(ushort **)&scannerContext.state.line) = (ushort *)(iVar6 + (*(uint *)&scannerContext.text));
  }
  scannerNative0071745a = (undefined1)*param_1;
  *(undefined1 **)(param_1 + 2) = &scannerNative0071745a;
  param_1[4] = 1;
  param_1[5] = 0;
  *(int *)(param_1 + 0xc) = (int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
LAB_00497398:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(ushort **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_00497430:
  (*(ushort **)&scannerContext.state.current) = local_18;
  local_40=(ushort *)(local_18);
  if (local_20 == (ushort *)0x3e) {
    sVar5=(short)(-0x10);
  }
  else {
    sVar5=(short)(-0xf);
  }
  *param_1 = sVar5;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_00496761:
  if ((*(ushort **)&scannerContext.state.current) < (*(ushort **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar6=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(ushort **)&scannerContext.state.line) = (ushort *)(iVar6 + (*(uint *)&scannerContext.text));
  }
  *(int *)(param_1 + 0xc) = (int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


extern "C" short fn_00497560(ScanToken *token)
{
 short *param_1=(short *)token;
  bool bVar1;
  int iVar2;
  byte bVar3;
  ushort *puVar4;
  short sVar5;
  uint uVar6;
  ushort *puVar7;
  ushort *puVar8;
  int iVar9;
  char cVar10;
  ushort *puVar11;
  ushort uVar12;
  ushort *local_40;
  ushort *local_3c;
  ushort *puStack_38;
  undefined *local_34;
  undefined *local_30;
  undefined *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  ushort *local_20;
  ushort *local_1c;
  ushort *local_18;
  ushort *local_14;
  puVar4=(ushort *)((*(ushort **)&scannerContext.end));
  local_40=(ushort *)((*(ushort **)&scannerContext.state.current));
  param_1[2] = 0;
  param_1[3] = 0;
  local_28=(undefined4 *)(&(*(ushort **)&scannerContext.state.current));
  local_24=(undefined4 *)(&(*(uint *)&scannerContext.previous.current));
  local_20=(ushort *)((ushort *)&(*(uint *)&scannerContext.previous.current));
  local_3c=(ushort *)((ushort *)&(*(ushort **)&scannerContext.state.current));
  local_2c=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
  local_30=(undefined *)(&(*(byte *)&scannerLiteralBuffer.grow));
LAB_004975b1:
  puVar11=(ushort *)(local_40);
  if (local_40 < puVar4) {
    if (local_40 < puVar4) {
      local_18=(ushort *)(local_40 + 1);
      local_14=(ushort *)((ushort *)(uint)*local_40);
    }
    else {
      local_18=(ushort *)(puVar4);
      local_14=(ushort *)((ushort *)0x0);
    }
    if ((local_14 == (ushort *)0x9) || ((int)local_14 - 0xbU < 2) || (local_14 == (ushort *)0x1a) ||
       (local_14 == (ushort *)0x20)) {
      local_40=(ushort *)(local_18);
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      goto LAB_004975b1;
    }
    if (local_14 == (ushort *)0x5c) {
      if (local_18 < puVar4) {
        local_1c=(ushort *)(local_18 + 1);
        local_14=(ushort *)((ushort *)(uint)*local_18);
      }
      else {
        local_1c=(ushort *)(puVar4);
        local_14=(ushort *)((ushort *)0x0);
      }
      if ((local_14 != (ushort *)0xd) && (local_14 != (ushort *)0xa)) goto LAB_004976e0;
      local_40=(ushort *)(local_1c);
      if (local_14 == (ushort *)0xd) {
        if (local_1c < puVar4) {
          local_18=(ushort *)(local_1c + 1);
          uVar12=(ushort)(*local_1c);
        }
        else {
          local_18=(ushort *)(puVar4);
          uVar12=(ushort)(0);
        }
        if (uVar12 == 10) {
          local_40=(ushort *)(local_18);
        }
      }
      puVar11=(ushort *)(local_40);
      if ((*(ushort **)&scannerContext.state.line) < local_40) {
        (*(ushort **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar6=(uint)(0);
        }
        else {
          uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar6 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar11;
      goto LAB_004975b1;
    }
  }
LAB_004976e0:
  (*(ushort **)&scannerContext.state.current) = local_40;
  *local_24 = *local_28;
  local_24[1] = local_28[1];
  local_24[2] = local_28[2];
  local_24[3] = local_28[3];
  puVar7=(ushort *)(local_20);
  if (local_20 == (ushort *)0x0) {
    puVar7=(ushort *)(local_3c);
  }
  *(int *)(param_1 + 6) = (*(uint *)&scannerContext.file);
  *(int *)(param_1 + 8) = *(int *)puVar7 - (*(uint *)&scannerContext.text);
  *(int *)(param_1 + 10) = *(int *)(puVar7 + 6);
  *(undefined1 *)(param_1 + 1) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1));
  *(undefined1 *)((int)param_1 + 3) = (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2));
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 0;
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 0;
  scannerLiteralBuffer.length = 0;
  local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_40),(ScanByte)(0)));
  if (local_14 == (ushort *)0x0) {
    if (scannerCharacterFlags[0] != '\0') goto LAB_00497c70;
    (*(ushort **)&scannerContext.state.current) = local_40;
    *param_1 = 0;
    goto LAB_00498210;
  }
  puVar7=(ushort *)(local_14);
  if ((scannerNative00725f3f == '\0') || (local_14 > (ushort *)0xffff)) {
LAB_004977f5:
    do {
      local_14=(ushort *)(puVar7);
      bVar3=(byte)(scannerUnicodeFlags[64]);
      sVar5=(short)((short)local_14);
      switch((uint)local_14) {
      case 0x0:
        goto switchD_00497802_caseD_0;
      default:
        if ((local_14 > (ushort *)0xffff) || ((local_14[0x33f800] & 1) != 0))
        goto switchD_00497802_caseD_41;
        if ((local_14 > (ushort *)0xffff) || ((local_14[0x33f800] & 0x10) == 0)) {
          if (local_14 < (ushort *)0x100) {
            if ((char)local_14[0x347800] != '\0') goto LAB_00497c70;
            (*(ushort **)&scannerContext.state.current) = local_40;
            *param_1 = sVar5;
          }
          else {
            if (scannerUnicodeFlags[65530] != '\0') goto LAB_00497c70;
            (*(ushort **)&scannerContext.state.current) = local_40;
            *param_1 = -6;
          }
          goto LAB_00498210;
        }
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
switchD_00497802_caseD_30:
        local_34=(undefined *)(local_30);
        while( true ) {
          puVar7=(ushort *)(local_14);
          if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
            scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
          }
          iVar9=(int)(scannerLiteralBuffer.length);
          scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar9) = (*(byte *)((char *)&local_14+0));
          local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 > (ushort *)0x7f) ||
             ((local_14[0x33f800] & 0x11) == 0 &&
             ((local_14 != (ushort *)0x2b && (local_14 != (ushort *)0x2d)) ||
             (puVar7 != (ushort *)0x45 &&
             (puVar7 != (ushort *)0x65 && (puVar7 != (ushort *)0x50) && (puVar7 != (ushort *)0x70)))
             ) && (local_14 != (ushort *)0x2e))) break;
          local_40=(ushort *)(local_18);
        }
        if ((scannerNative00725f3f == '\0') || (scannerLiteralBuffer.length != 1) ||
           ((puVar7 > (ushort *)0x2f && (puVar7 < (ushort *)0x3a)) ||
           (puVar7 > (ushort *)0xffff || ((puVar7[0x33f800] & 0x10) == 0)))) {
          (*(ushort **)&scannerContext.state.current) = local_40;
          *param_1 = -8;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_004981e1;
        }
        break;
      case 0xa:
      case 0xd:
        if ((*(ushort **)&scannerContext.state.line) < local_40) {
          (*(ushort **)&scannerContext.state.line) = local_40;
          scannerContext.state.column = scannerContext.state.column + 1;
          if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
            uVar6=(uint)(0);
          }
          else {
            uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
          }
          if (uVar6 < scannerContext.state.column) {
            sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
          }
        }
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
        (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = -7;
        *(undefined **)(param_1 + 2) = &scannerNative00694b0e;
        param_1[4] = 1;
        param_1[5] = 0;
        goto LAB_004981e1;
      case 0x21:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x177;
          *(undefined **)(param_1 + 2) = &scannerNative0067de91;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[33] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x21;
        goto LAB_00498210;
      case 0x22:
        if ((local_14[0x33f800] & 0x20) != 0) goto LAB_004980c0;
      case 0x27:
        if (local_14 == (ushort *)0x27) {
          sVar5=(short)(-9);
        }
        else {
          sVar5=(short)(-0xc);
        }
        *param_1 = sVar5;
        goto LAB_00498078;
      case 0x23:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x23) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = -0x12;
          *(undefined **)(param_1 + 2) = &scannerNative00694004;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x23);
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[35] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x23;
        goto LAB_00498210;
      case 0x25:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16c;
          *(undefined **)(param_1 + 2) = &scannerNative0067de6d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if ((local_14 == (ushort *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_18),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
          if ((local_14 == (ushort *)0x25) &&
             (local_14 = (ushort *)fn_004841f0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)),
             local_14 == (ushort *)0x3a)) {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = -0x12;
            *(undefined **)(param_1 + 2) = &scannerNative0067de55;
            param_1[4] = 4;
            param_1[5] = 0;
          }
          else {
            (*(ushort **)&scannerContext.state.current) = local_40;
            *param_1 = 0x23;
            *(undefined **)(param_1 + 2) = &scannerNative0067de51;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_004981e1;
        }
        if ((local_14 == (ushort *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de45;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[37] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x25;
        goto LAB_00498210;
      case 0x26:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x26) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x175;
          *(undefined **)(param_1 + 2) = &scannerNative0067de9d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x171;
          *(undefined **)(param_1 + 2) = &scannerNative0067de75;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[38] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x26;
        goto LAB_00498210;
      case 0x28:
      case 0x29:
      case 0x2c:
      case 0x3b:
      case 0x5b:
      case 0x5d:
      case 0x7b:
      case 0x7d:
      case 0x7e:
        if ((char)local_14[0x347800] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = sVar5;
        goto LAB_00498210;
      case 0x2a:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16a;
          *(undefined **)(param_1 + 2) = &scannerNative0067de65;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[42] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2a;
        goto LAB_00498210;
      case 0x2b:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x2b) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17c;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea5;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de5d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[43] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2b;
        goto LAB_00498210;
      case 0x2d:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3e) {
          local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if ((scannerNative0070f1a8 == '\0') || (local_14 != (ushort *)0x2a)) {
            local_40=(ushort *)(local_18);
            (*(ushort **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17e;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb1;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          else {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x181;
            *(undefined **)(param_1 + 2) = &scannerNative0067deb5;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          goto LAB_004981e1;
        }
        if (local_14 == (ushort *)0x2d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x17d;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16e;
          *(undefined **)(param_1 + 2) = &scannerNative0067de61;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[45] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2d;
        goto LAB_00498210;
      case 0x2e:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x2e) {
          local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (ushort *)0x2e) {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x17f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de01;
            param_1[4] = 3;
            param_1[5] = 0;
            local_14=(ushort *)((ushort *)0x2e);
            goto LAB_004981e1;
          }
        }
        else {
          if ((scannerNative0070f1a8 != '\0') && (local_14 == (ushort *)0x2a)) {
            local_40=(ushort *)(local_18);
            (*(ushort **)&scannerContext.state.current) = local_18;
            *param_1 = 0x180;
            *(undefined **)(param_1 + 2) = &scannerNative0067de05;
            param_1[4] = 2;
            param_1[5] = 0;
            local_14=(ushort *)((ushort *)0x2a);
            goto LAB_004981e1;
          }
          if ((local_14 < (ushort *)0x10000) && ((local_14[0x33f800] & 0x10) != 0)) {
            local_14=(ushort *)((ushort *)0x2e);
            goto switchD_00497802_caseD_30;
          }
        }
        if (scannerCharacterFlags[46] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2e;
        goto LAB_00498210;
      case 0x2f:
        scannerCommentBuffer.length = 0;
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x2f) {
          if (scannerNative0070f1a8 != '\0') goto LAB_00497d40;
          if (scannerNative0070f1ca != '\0') goto LAB_00497d40;
          if (scannerNative0070f1af == '\0') goto LAB_00497d40;
        }
        if (local_14 == (ushort *)0x2a) {
          puStack_38=(ushort *)((ushort *)0x0);
          local_40=(ushort *)(local_18);
          local_34=(undefined *)(local_30);
          goto LAB_00498880;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x16b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de69;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[47] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x2f;
        goto LAB_00498210;
      case 0x3a:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if ((scannerNative0070f1a8 != '\0') && (local_14 == (ushort *)0x3a)) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x182;
          *(undefined **)(param_1 + 2) = &scannerNative0067ddf9;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if ((local_14 == (ushort *)0x3e) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5d;
          *(undefined **)(param_1 + 2) = &scannerNative0067de4d;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[58] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3a;
        goto LAB_00498210;
      case 0x3c:
        if ((local_14[0x33f800] & 0x20) != 0) {
LAB_004980c0:
          if (local_14 == (ushort *)0x3c) {
            cVar10=(char)('>');
          }
          else {
            cVar10=(char)('\"');
          }
          local_20=(ushort *)((ushort *)(int)cVar10);
          goto LAB_004980e0;
        }
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x178;
          *(undefined **)(param_1 + 2) = &scannerNative0067de95;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (local_14 == (ushort *)0x3c) {
          local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (ushort *)0x3d) {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x16f;
            *(undefined **)(param_1 + 2) = &scannerNative0067de85;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_40=(ushort *)(local_18);
            (*(ushort **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17a;
            *(undefined **)(param_1 + 2) = &scannerNative0067de7d;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_004981e1;
        }
        if ((local_14 == (ushort *)0x25) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x7b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de41;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if ((local_14 == (ushort *)0x3a) && (scannerNative0070f1a8 != '\0' || (scannerNative0070f1ca != '\0'))) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x5b;
          *(undefined **)(param_1 + 2) = &scannerNative0067de49;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[60] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3c;
        goto LAB_00498210;
      case 0x3d:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x176;
          *(undefined **)(param_1 + 2) = &scannerNative0067de8d;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[61] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3d;
        goto LAB_00498210;
      case 0x3e:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x179;
          *(undefined **)(param_1 + 2) = &scannerNative0067de99;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_004981e1;
        }
        if (local_14 == (ushort *)0x3e) {
          local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_18),(char *)(puVar4),(char **)(&local_1c),(ScanByte)(0)));
          if (local_14 == (ushort *)0x3d) {
            local_40=(ushort *)(local_1c);
            (*(ushort **)&scannerContext.state.current) = local_1c;
            *param_1 = 0x170;
            *(undefined **)(param_1 + 2) = &scannerNative0067de89;
            param_1[4] = 3;
            param_1[5] = 0;
          }
          else {
            local_40=(ushort *)(local_18);
            (*(ushort **)&scannerContext.state.current) = local_18;
            *param_1 = 0x17b;
            *(undefined **)(param_1 + 2) = &scannerNative0067de81;
            param_1[4] = 2;
            param_1[5] = 0;
          }
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[62] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x3e;
        goto LAB_00498210;
      case 0x3f:
        if ((char)local_14[0x347800] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = sVar5;
        goto LAB_00498210;
      case 0x40:
        if (scannerNative00725f3f != '\0') {
          scannerUnicodeFlags[64] = scannerUnicodeFlags[64] | 1;
          fn_0047db20((char **)(&local_40),(char *)(puVar4),(char **)(&local_18),(ScanWord *)(&local_14));
          (*(ushort **)&scannerContext.state.current) = local_40;
          scannerUnicodeFlags[64] = bVar3;
          *param_1 = -3;
          *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
          *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
          *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[64] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x40;
        goto LAB_00498210;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5f:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      case 0x6b:
      case 0x6c:
      case 0x6d:
      case 0x6e:
      case 0x6f:
      case 0x70:
      case 0x71:
      case 0x72:
      case 0x73:
      case 0x74:
      case 0x75:
      case 0x76:
      case 0x77:
      case 0x78:
      case 0x79:
      case 0x7a:
        goto switchD_00497802_caseD_41;
      case 0x5c:
        if (scannerCharacterFlags[92] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5c;
        goto LAB_00498210;
      case 0x5e:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x172;
          *(undefined **)(param_1 + 2) = &scannerNative0067de71;
          param_1[4] = 2;
          param_1[5] = 0;
          local_14=(ushort *)((ushort *)0x3d);
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[94] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x5e;
        goto LAB_00498210;
      case 0x7c:
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(0)));
        if (local_14 == (ushort *)0x7c) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x174;
          *(undefined **)(param_1 + 2) = &scannerNative0067dea1;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (local_14 == (ushort *)0x3d) {
          local_40=(ushort *)(local_18);
          (*(ushort **)&scannerContext.state.current) = local_18;
          *param_1 = 0x173;
          *(undefined **)(param_1 + 2) = &scannerNative0067de79;
          param_1[4] = 2;
          param_1[5] = 0;
          goto LAB_004981e1;
        }
        if (scannerCharacterFlags[124] != '\0') goto LAB_00497c70;
        (*(ushort **)&scannerContext.state.current) = local_40;
        *param_1 = 0x7c;
        goto LAB_00498210;
      }
    } while( true );
  }
  if ((local_14[0x33f800] & 1) == 0) {
    if ((local_14[0x33f800] & 0x10) != 0) goto switchD_00497802_caseD_30;
    if ((char)local_14[0x347800] != '\0') goto LAB_00497d40;
    goto LAB_004977f5;
  }
switchD_00497802_caseD_41:
  fn_0047db20((char **)(&local_40),(char *)(puVar4),(char **)(&local_18),(ScanWord *)(&local_14));
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  if (local_14 == (ushort *)0x27) {
    sVar5=(short)(fn_0047f3e0((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar5;
    if (*param_1 != 0) {
      local_40=(ushort *)(local_18);
      scannerLiteralBuffer.length = 0;
LAB_00498078:
      fn_0047d1e0((uint)(local_14),(char **)(&local_40),(char *)(puVar4));
      (*(ushort **)&scannerContext.state.current) = local_40;
      *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
      *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
      *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
      goto LAB_004981e1;
    }
  }
  else if (local_14 == (ushort *)0x22) {
    sVar5=(short)(fn_0047f460((const char *)((*(uint *)&scannerLiteralBuffer.text))));
    *param_1 = sVar5;
    if (*param_1 != 0) {
      local_40=(ushort *)(local_18);
      scannerLiteralBuffer.length = 0;
      goto LAB_00498078;
    }
  }
  (*(ushort **)&scannerContext.state.current) = local_40;
  *param_1 = -3;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_004981e1;
LAB_00498880:
  if (local_40 < puVar4) {
    local_14=(ushort *)((ushort *)(uint)*local_40);
    local_40=(ushort *)(local_40 + 1);
  }
  else {
    local_40=(ushort *)(puVar4);
    local_14=(ushort *)((ushort *)0x0);
  }
  if ((local_14 == (ushort *)0x2f) && (puStack_38 == (ushort *)0x2a)) goto LAB_004989be;
  if (local_14 != (ushort *)0x0) {
    if ((local_14 == (ushort *)0xd) || (local_14 == (ushort *)0xa)) {
      if (local_14 == (ushort *)0xd) {
        if (local_40 < puVar4) {
          local_18=(ushort *)(local_40 + 1);
          uVar12=(ushort)(*local_40);
        }
        else {
          local_18=(ushort *)(puVar4);
          uVar12=(ushort)(0);
        }
        if (uVar12 == 10) {
          local_40=(ushort *)(local_18);
        }
      }
      puVar7=(ushort *)(local_40);
      if ((*(ushort **)&scannerContext.state.line) < local_40) {
        (*(ushort **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar6=(uint)(0);
        }
        else {
          uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar6 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      (*(ushort **)&scannerContext.state.current) = puVar7;
      local_14=(ushort *)((ushort *)0xa);
      goto LAB_00498930;
    }
    if (local_14 != (ushort *)0x5c) goto LAB_00498930;
    if (local_40 < puVar4) {
      puVar7=(ushort *)(local_40 + 1);
      uVar12=(ushort)(*local_40);
    }
    else {
      uVar12=(ushort)(0);
      puVar7=(ushort *)(puVar4);
    }
    if ((uVar12 == 0xd) || (uVar12 == 10)) {
      local_40=(ushort *)(puVar7);
      if (uVar12 == 0xd) {
        if (puVar7 < puVar4) {
          puVar8=(ushort *)(puVar7 + 1);
          uVar12=(ushort)(*puVar7);
        }
        else {
          uVar12=(ushort)(0);
          puVar8=(ushort *)(puVar4);
        }
        if (uVar12 == 10) {
          local_40=(ushort *)(puVar8);
        }
      }
      puVar7=(ushort *)(local_40);
      if ((*(ushort **)&scannerContext.state.line) < local_40) {
        (*(ushort **)&scannerContext.state.line) = local_40;
        scannerContext.state.column = scannerContext.state.column + 1;
        if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
          uVar6=(uint)(0);
        }
        else {
          uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
        }
        if (uVar6 < scannerContext.state.column) {
          sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
        }
      }
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
      (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
      bVar1=(bool)(true);
      (*(ushort **)&scannerContext.state.current) = puVar7;
    }
    else {
      bVar1=(bool)(false);
    }
    if (!bVar1) {
LAB_00498930:
      puStack_38=(ushort *)(local_14);
      if (scannerNative0070f071 != '\0') {
        iVar9 = (int)((((int)local_40 - (int)puVar11) + 1U) -
                     (uint)((uint)((int)local_40 - (int)puVar11) < 0x80000000)) >> 1;
        puVar7=(ushort *)(puVar11);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar9) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar9);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar11 = local_40, scannerLiteralBuffer.length = iVar2, iVar9 != 0; iVar9 = iVar9 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = (char)*puVar7;
          puVar7=(ushort *)((ushort *)((int)puVar7 + 1));
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
    }
    goto LAB_00498880;
  }
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(uint *)&scannerContext.previous.current) + 4),(int)(scannerContext.previous.column),(short)(0x28bf));
LAB_004989be:
  (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
  if (scannerNative0070f071 == '\0') {
    (*(ushort **)&scannerContext.state.current) = local_40;
    (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = *(undefined1 *)((int)param_1 + 3);
    goto LAB_004975b1;
  }
  if (local_14 == (ushort *)0x2f) {
    if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
      scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
    }
    iVar9=(int)(scannerLiteralBuffer.length);
    scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
    *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar9) = 0x2f;
  }
  (*(ushort **)&scannerContext.state.current) = local_40;
  *param_1 = -0x11;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
  goto LAB_004981e1;
LAB_004980e0:
  if (local_40 < puVar4) {
    local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(1)));
  }
  else {
    local_14=(ushort *)((ushort *)0x0);
  }
  if (local_20 == local_14) goto LAB_00498e50;
  if ((local_14 == (ushort *)0x0) || (local_14 == (ushort *)0xd) || (local_14 == (ushort *)0xa))
  goto LAB_00498dc4;
  local_40=(ushort *)(local_18);
  if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + 1) {
    scannerLiteralBuffer.request(scannerLiteralBuffer.length + 1);
  }
  iVar9=(int)(scannerLiteralBuffer.length);
  scannerLiteralBuffer.length = scannerLiteralBuffer.length + 1;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + iVar9) = (*(byte *)((char *)&local_14+0));
  goto LAB_004980e0;
switchD_00497802_caseD_0:
  if (scannerCharacterFlags[0] != '\0') {
LAB_00497c70:
    local_18=(ushort *)(local_40);
    do {
      if (scannerNative0070f071 != '\0') {
        iVar9 = (int)((((int)local_40 - (int)puVar11) + 1U) -
                     (uint)((uint)((int)local_40 - (int)puVar11) < 0x80000000)) >> 1;
        puVar7=(ushort *)(puVar11);
        iVar2=(int)(scannerLiteralBuffer.length);
        if (scannerLiteralBuffer.capacity <= scannerLiteralBuffer.length + iVar9) {
          scannerLiteralBuffer.request(scannerLiteralBuffer.length + iVar9);
          iVar2=(int)(scannerLiteralBuffer.length);
        }
        for (; puVar11 = local_40, scannerLiteralBuffer.length = iVar2, iVar9 != 0; iVar9 = iVar9 - 1) {
          scannerLiteralBuffer.length = iVar2 + 1;
          *(char *)((*(uint *)&scannerLiteralBuffer.text) + iVar2) = (char)*puVar7;
          puVar7=(ushort *)((ushort *)((int)puVar7 + 1));
          iVar2=(int)(scannerLiteralBuffer.length);
        }
      }
LAB_00497d40:
      do {
        local_14=(ushort *)((ushort *)fn_004841f0((char *)(local_40),(char *)(puVar4),(char **)(&local_18),(ScanByte)(1)));
        if ((local_14 == (ushort *)0xd) || (local_14 == (ushort *)0xa) ||
           (local_14 == (ushort *)0x0)) {
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          if (scannerNative0070f071 != '\0') {
            (*(ushort **)&scannerContext.state.current) = local_40;
            *param_1 = -0x11;
            *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
            *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
            *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
            goto LAB_004981e1;
          }
          (*(ushort **)&scannerContext.state.current) = local_40;
          goto LAB_004975b1;
        }
        local_40=(ushort *)(local_18);
        if (local_14 != (ushort *)0x5c) break;
        if (local_18 < puVar4) {
          puVar7=(ushort *)(local_18 + 1);
          uVar12=(ushort)(*local_18);
        }
        else {
          uVar12=(ushort)(0);
          puVar7=(ushort *)(puVar4);
        }
        if ((uVar12 == 0xd) || (uVar12 == 10)) {
          local_40=(ushort *)(puVar7);
          if (uVar12 == 0xd) {
            if (puVar7 < puVar4) {
              puVar8=(ushort *)(puVar7 + 1);
              uVar12=(ushort)(*puVar7);
            }
            else {
              uVar12=(ushort)(0);
              puVar8=(ushort *)(puVar4);
            }
            if (uVar12 == 10) {
              local_40=(ushort *)(puVar8);
            }
          }
          puVar7=(ushort *)(local_40);
          if ((*(ushort **)&scannerContext.state.line) < local_40) {
            (*(ushort **)&scannerContext.state.line) = local_40;
            scannerContext.state.column = scannerContext.state.column + 1;
            if (*(int *)((*(uint *)&scannerContext.file) + 0x12) == 0) {
              uVar6=(uint)(0);
            }
            else {
              uVar6=(uint)(*(uint *)(*(int *)((*(uint *)&scannerContext.file) + 0x12) + 4) >> 2);
            }
            if (uVar6 < scannerContext.state.column) {
              sourcetext_define_line((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column),(ScanWord)((int)local_40 - (*(uint *)&scannerContext.text)));
            }
          }
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+2)) = 1;
          (*(byte *)((char *)&((*(uint *)&scannerContext.state.lineStart))+1)) = 1;
          bVar1=(bool)(true);
          (*(ushort **)&scannerContext.state.current) = puVar7;
        }
        else {
          bVar1=(bool)(false);
        }
      } while (bVar1);
    } while( true );
  }
  (*(ushort **)&scannerContext.state.current) = local_40;
  *param_1 = 0;
LAB_00498210:
  if ((*(ushort **)&scannerContext.state.current) < (*(ushort **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar9=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(ushort **)&scannerContext.state.line) = (ushort *)(iVar9 + (*(uint *)&scannerContext.text));
  }
  scannerNative00716ec4 = (undefined1)*param_1;
  *(undefined1 **)(param_1 + 2) = &scannerNative00716ec4;
  param_1[4] = 1;
  param_1[5] = 0;
  *(int *)(param_1 + 0xc) = (int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
LAB_00498dc4:
  scanner_error((void *)((*(uint *)&scannerContext.previous.current)),(int)((*(ushort **)&scannerContext.state.current)),(int)(scannerContext.previous.column),(short)(0x2780));
LAB_00498e50:
  (*(ushort **)&scannerContext.state.current) = local_18;
  local_40=(ushort *)(local_18);
  if (local_20 == (ushort *)0x3e) {
    sVar5=(short)(-0x10);
  }
  else {
    sVar5=(short)(-0xf);
  }
  *param_1 = sVar5;
  *(undefined1 *)((*(uint *)&scannerLiteralBuffer.text) + scannerLiteralBuffer.length) = 0;
  *(int *)(param_1 + 2) = (*(uint *)&scannerLiteralBuffer.text);
  *(int *)(param_1 + 4) = scannerLiteralBuffer.length;
LAB_004981e1:
  if ((*(ushort **)&scannerContext.state.current) < (*(ushort **)&scannerContext.state.line)) {
    scannerContext.state.column = sourcetext_get_line_number((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)((int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.text)));
    iVar9=(int)(sourcetext_get_line_offset((ScanFile *)((*(uint *)&scannerContext.file)),(ScanWord)(scannerContext.state.column)));
    (*(ushort **)&scannerContext.state.line) = (ushort *)(iVar9 + (*(uint *)&scannerContext.text));
  }
  *(int *)(param_1 + 0xc) = (int)(*(ushort **)&scannerContext.state.current) - (*(uint *)&scannerContext.previous.current);
  return *param_1;
}


/* Verified native decoder slots. True thiscall methods use opaque code
 * addresses, not callable C aliases; their class bodies above own the ABI. */
extern "C" {
extern const unsigned char scannerMethodCode0047fa10[];
extern const unsigned char scannerMethodCode00482a50[];
extern const unsigned char scannerMethodCode00482920[];
extern const unsigned char scannerMethodCode0047fa30[];
extern const unsigned char scannerMethodCode00481eb0[];
ScanWord scannerVTable00694b28[13] = {
    (ScanWord)fn_0047f810,
    (ScanWord)scannerMethodCode0047fa10,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_0047f800,
    (ScanWord)fn_0047f820,
    (ScanWord)fn_0047f860,
    (ScanWord)fn_0047f850,
    (ScanWord)fn_0047f840,
    (ScanWord)fn_0047f830,
    (ScanWord)scannerMethodCode00482a50,
    (ScanWord)fn_00482b00,
    (ScanWord)scannerMethodCode00482920,
    (ScanWord)scannerMethodCode0047fa30,
};
ScanWord scannerVTable00694b64[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_00482850,
    (ScanWord)fn_00482870,
    (ScanWord)fn_00482880,
    (ScanWord)fn_00482890,
    (ScanWord)fn_004828a0,
    (ScanWord)fn_004828b0,
    (ScanWord)fn_004828c0,
    (ScanWord)fn_00482b00,
};
ScanWord scannerVTable00694b98[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_004827a0,
    (ScanWord)fn_004827c0,
    (ScanWord)fn_004827d0,
    (ScanWord)fn_004827e0,
    (ScanWord)fn_004827f0,
    (ScanWord)fn_00482800,
    (ScanWord)fn_00482810,
    (ScanWord)fn_00482b00,
};
ScanWord scannerVTable00694bcc[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_00482660,
    (ScanWord)fn_004826c0,
    (ScanWord)fn_004826d0,
    (ScanWord)fn_004826e0,
    (ScanWord)fn_004826f0,
    (ScanWord)fn_00482700,
    (ScanWord)fn_00482710,
    (ScanWord)fn_00482b00,
};
ScanWord scannerVTable00694c00[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_00482540,
    (ScanWord)fn_004825a0,
    (ScanWord)fn_004825b0,
    (ScanWord)fn_004825c0,
    (ScanWord)fn_004825d0,
    (ScanWord)fn_004825e0,
    (ScanWord)fn_004825f0,
    (ScanWord)fn_00482b00,
};
ScanWord scannerVTable00694c34[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_00482160,
    (ScanWord)fn_0047f820,
    (ScanWord)fn_0047f860,
    (ScanWord)fn_0047f850,
    (ScanWord)fn_0047f840,
    (ScanWord)fn_0047f830,
    (ScanWord)fn_004821a0,
    (ScanWord)fn_00482b00,
};
ScanWord scannerVTable00694c68[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_0047f800,
    (ScanWord)fn_0047f820,
    (ScanWord)fn_0047f860,
    (ScanWord)fn_0047f850,
    (ScanWord)fn_0047f840,
    (ScanWord)fn_0047f830,
    (ScanWord)fn_00482090,
    (ScanWord)fn_00482b00,
};
ScanWord scannerVTable00694c9c[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_0047f800,
    (ScanWord)fn_0047f820,
    (ScanWord)fn_0047f860,
    (ScanWord)fn_0047f850,
    (ScanWord)fn_0047f840,
    (ScanWord)fn_0047f830,
    (ScanWord)fn_00481fa0,
    (ScanWord)fn_00482b00,
};
ScanWord scannerVTable00694cd0[11] = {
    (ScanWord)fn_00481e10,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_00481e20,
    (ScanWord)fn_0047f800,
    (ScanWord)fn_0047f820,
    (ScanWord)fn_0047f860,
    (ScanWord)fn_0047f850,
    (ScanWord)fn_0047f840,
    (ScanWord)fn_0047f830,
    (ScanWord)scannerMethodCode00481eb0,
    (ScanWord)fn_00482b00,
};
ScanWord scannerVTable00694d04[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_0047f800,
    (ScanWord)fn_0047f820,
    (ScanWord)fn_0047f860,
    (ScanWord)fn_0047f850,
    (ScanWord)fn_0047f840,
    (ScanWord)fn_0047f830,
    (ScanWord)fn_0047eca0,
    (ScanWord)fn_00482b00,
};
ScanWord scannerBaseDecoderVTable[11] = {
    (ScanWord)fn_0047f810,
    (ScanWord)fn_0047ebf0,
    (ScanWord)fn_0047db10,
    (ScanWord)fn_0047f800,
    (ScanWord)fn_0047f820,
    (ScanWord)fn_0047f860,
    (ScanWord)fn_0047f850,
    (ScanWord)fn_0047f840,
    (ScanWord)fn_0047f830,
    (ScanWord)fn_0047eca0,
    (ScanWord)fn_00482b00,
};
}
