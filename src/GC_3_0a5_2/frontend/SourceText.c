/* Native SourceText.c file and line-table views remain private during migration. */
#include "compiler/common.h"
#include <stddef.h>
#pragma pack(push,2)
typedef struct SourceTextList {UInt32 **data;UInt32 size,capacity,unknown0c;} SourceTextList;
typedef struct SourceTextFile {void *name;UInt32 unknown04;UInt8 kind,unknown09;char *contents;UInt32 contentsSize;SourceTextList *lines;} SourceTextFile;
#pragma pack(pop)
typedef char SourceTextFileLinesOffset[(offsetof(SourceTextFile,lines)==18)?1:-1];
typedef char SourceTextFileContentsOffset[(offsetof(SourceTextFile,contents)==10)?1:-1];
typedef char SourceTextFileContentsSizeOffset[(offsetof(SourceTextFile,contentsSize)==14)?1:-1];
typedef char SourceTextListSize[(sizeof(SourceTextList)==16)?1:-1];
static char sourcetext_filename[]="SourceText.c";
static char sourcetext_define_line_name[]="sourcetext_define_line";
extern void *galloc(UInt32);
extern SInt16 InitGList(SourceTextList *,SInt32);
extern void AppendGListLong(SourceTextList *,UInt32);
extern void preprocessor_internal_msg(int,int,const char *,const char *,int);
extern UInt8 preprocessor_load_file(SourceTextFile *);
extern void scanner_getlinetable(SourceTextFile *);

void sourcetext_define_line(SourceTextFile *file,SInt32 line,UInt32 offset)
{
    if(!file->lines||!file->lines->data) {
        file->lines=galloc(16);
        if(InitGList(file->lines,(SInt32)file->contentsSize/16+4))return;
    }
    if(file->lines->size+4==(UInt32)line*4)AppendGListLong(file->lines,offset);
    else preprocessor_internal_msg(1,0,sourcetext_filename,sourcetext_define_line_name,117);
}
UInt32 sourcetext_get_line_number(SourceTextFile *file,UInt32 offset)
{
    SourceTextList *list;UInt32 *table;SInt32 low,high,middle;
    if(!file)return 0;
    list=file->lines;
    if(!list||!(table=(UInt32 *)list->data)||offset>*(UInt32 *)((UInt8 *)*(UInt32 **)table+list->size-4)) {
        if(file&&(file->contents||preprocessor_load_file(file)))scanner_getlinetable(file);
        list=file->lines;if(!list||!(table=(UInt32 *)list->data))return 0;
    }
    if(offset>file->contentsSize)offset=file->contentsSize;
    low=0;high=list->size>>2;table=*(UInt32 **)table;
    while(low+1<high) {
        middle=(SInt32)(low+high)>>1;
        if(table[middle]<=offset)low=middle;else high=middle;
    }
    return low+1;
}
UInt32 sourcetext_get_line_offset(SourceTextFile *file,UInt32 line)
{
    SourceTextList *list;
    if(!file)return 0;
    list=file->lines;
    if(!list||!list->data||line>(list->size>>2)) {
        if(file&&(file->contents||preprocessor_load_file(file)))scanner_getlinetable(file);
        list=file->lines;if(!list||!list->data)return 0;
    }
    if(line<=(list->size>>2)) {if(line<1)line=1;return (*list->data)[line-1];}
    return file->contentsSize;
}
