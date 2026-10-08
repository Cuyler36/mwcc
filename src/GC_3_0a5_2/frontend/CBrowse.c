/* Native GC 3.0a5.2 browse records use packed compiler structures.
 * Offsets below are verified against this executable, not the 1.2.5 layouts.
 */
#include "compiler/common.h"
#include "compiler/CompilerTools.h"
#include "compiler/CError.h"
#include <string.h>

struct GC3BrowseFileFlags { UInt8 browse : 1; UInt8 reserved : 7; };
#define BROWSE_ENABLED(f) (((struct GC3BrowseFileFlags *)((f) + 50))->browse)

static UInt8 use_name_ids;
static GList gBrowseData;
static GList gClassData;
static GList gMemberFuncList;
static SInt32 gNextMemberFuncID;
extern UInt8 data_00725d9e;
extern UInt8 data_0070f1a8;
extern char **data_00710144;
extern void CError_NoMem(void);
extern void *AppendGListData(GList *, const void *, SInt32);
extern void fn_0044d040(void *);
extern void fn_0044d0a0(void *);
extern void fn_00432620(void *, GList *);
extern void fn_004c5f00(void *, SInt32, SInt32, SInt32, SInt32);

void RecordName(GList *output, char *text, SInt32 id)
{
    char *node;
    SInt32 length;
    if (!output || !text || !*text) CError_Internal("CBrowse.c", 0xd3);
    if (id < 0 && use_name_ids) {
        for (node = data_00710144[CHash(text)]; node; node = *(char **)node) {
            if (!strcmp(text, node + 10)) { id = *(SInt32 *)(node + 4); break; }
        }
    }
    if (id >= 0 && use_name_ids) {
        AppendGListWord(output, -1);
        AppendGListLong(output, id);
    } else {
        length = strlen(text);
        if (length < 32000) {
            AppendGListWord(output, (SInt16)length);
            if (length) AppendGListData(output, text, length + 1);
        } else {
            AppendGListWord(output, 32000);
            AppendGListData(output, text, 32000);
            AppendGListByte(output, 0);
        }
    }
}

void CBrowse_Cleanup(void)
{
    FreeGList(&gBrowseData);
    FreeGList(&gClassData);
    FreeGList(&gMemberFuncList);
}

void CBrowse_Finish(void *cu)
{
    SInt32 index, count;
    char *volatile *objects;
    if (!cu) CError_Internal("CBrowse.c", 0x9f);
    if (gBrowseData.size >= 76U) {
        fn_0044d040(gMemberFuncList.data);
        count = (UInt32)gMemberFuncList.size >> 2;
        objects = *(char *volatile **)gMemberFuncList.data;
        for (index = 0; index < count; ++index, ++objects) {
            char *type = *(char **)(*objects + 16);
            if ((UInt8)*type == 7 && !(*(UInt32 *)(type + 22) & 2))
                fn_004c5f00(*objects, 0, 0, -1, -1);
        }
        fn_0044d0a0(gMemberFuncList.data);
        AppendGListByte(&gBrowseData, -1);
        fn_00432620(cu, &gBrowseData);
    }
}

struct GC3BrowseHeader {
    UInt32 magic, version;
    UInt16 language, valueA;
    UInt32 valueC;
    UInt8 reserved[60];
};

void CBrowse_Setup(char *cu)
{
    struct GC3BrowseHeader header;
    if (!cu) CError_Internal("CBrowse.c", 0x7a);
    *(UInt32 *)(cu + 8) = 0;
    if (InitGList(&gBrowseData, 65536)) CError_NoMem();
    if (InitGList(&gMemberFuncList, 1024)) CError_NoMem();
    gNextMemberFuncID = 1;
    data_00725d9e = 0;
    use_name_ids = 0;
    memclrw(&header, sizeof(header));
    header.magic = 0xbeabbaeb;
    header.version = 2;
    header.valueC = 2;
    header.language = data_0070f1a8 ? (UInt8)2 : (UInt8)1;
    header.valueA = use_name_ids;
    AppendGListData(&gBrowseData, &header, sizeof(header));
}

extern char *CError_GetObjectName(void *);
extern char *CError_GetTypeName(void *, UInt32, UInt8);
extern UInt8 fn_004531a0(void *);
extern SInt16 data_00717466;
extern SInt32 data_0070ffc8;

void CBrowse_NewTemplateClass(void *type, char *file, SInt32 first, SInt32 last)
{
    char *node;
    SInt32 id;
    SInt32 fileid;
    if (!(!file || file[8] || !BROWSE_ENABLED(file) || !*(SInt16 *)(file + 26) || first <= 0 || last < first)) {
    node = (char *)GetHashNameNode(CError_GetTypeName(type, 0, 0));
    id = *(SInt32 *)(node + 4); fileid = *(SInt16 *)(file + 26);
    if (!(node + 10)) CError_Internal("CBrowse.c", 0x262);
    AppendGListByte(&gBrowseData, 7);
    AppendGListWord(&gBrowseData, fileid); AppendGListWord(&gBrowseData, fileid);
    AppendGListLong(&gBrowseData, first - 1); AppendGListLong(&gBrowseData, last - 1);
    AppendGListLong(&gBrowseData, 0); RecordName(&gBrowseData, node + 10, id);
    AppendGListWord(&gBrowseData, 0); AppendGListByte(&gBrowseData, 0);
    }
}

void CBrowse_NewTemplateFunc(char *func)
{
    char *file = *(char **)(func + 54), *full, *shortnode, *name;
    SInt32 first, last, fullid, shortid;
    SInt32 fileid;
    if (!(!file || file[8] || !BROWSE_ENABLED(file) || !*(SInt16 *)(file + 26) || *(SInt32 *)(func + 58) <= 0 || *(SInt32 *)(func + 62) < *(SInt32 *)(func + 58))) {
    full = (char *)GetHashNameNode(CError_GetObjectName(*(void **)(func + 46)));
    fullid = *(SInt32 *)(full + 4); shortnode = *(char **)(func + 18);
    shortid = *(SInt32 *)(shortnode + 4); last = *(SInt32 *)(func + 62);
    first = *(SInt32 *)(func + 58); name = shortnode + 10; fileid = *(SInt16 *)(*(char **)(func + 54) + 26);
    if (!name) CError_Internal("CBrowse.c", 0x262);
    AppendGListByte(&gBrowseData, 7);
    AppendGListWord(&gBrowseData, fileid); AppendGListWord(&gBrowseData, fileid);
    AppendGListLong(&gBrowseData, first - 1); AppendGListLong(&gBrowseData, last - 1);
    AppendGListLong(&gBrowseData, 0); RecordName(&gBrowseData, name, shortid);
    if (full + 10 && full + 10 != name) RecordName(&gBrowseData, full + 10, fullid);
    else AppendGListWord(&gBrowseData, 0);
    AppendGListByte(&gBrowseData, 1);
    }
}

void CBrowse_NewMacro(char *macro, char *file, SInt32 first, SInt32 last)
{
    char *node, *name;
    SInt32 id;
    SInt32 fileid;
    if (!(*(UInt16 *)(macro + 30) & 8)) {
    if (!(!file || file[8] || !BROWSE_ENABLED(file) || !*(SInt16 *)(file + 26) || first <= 0 || last < first)) {
    node = *(char **)(macro + 4); id = *(SInt32 *)(node + 4); name = node + 10;
    fileid = *(SInt16 *)(file + 26);
    if (!name) CError_Internal("CBrowse.c", 0x262);
    AppendGListByte(&gBrowseData, 3);
    AppendGListWord(&gBrowseData, fileid); AppendGListWord(&gBrowseData, fileid);
    AppendGListLong(&gBrowseData, first - 1); AppendGListLong(&gBrowseData, last - 1);
    AppendGListLong(&gBrowseData, 0); RecordName(&gBrowseData, name, id);
    AppendGListWord(&gBrowseData, 0);
    }
    }
}

void CBrowse_NewFunction(void *object, char *firstfile, char *lastfile, SInt32 first, SInt32 last)
{
    if (!(!firstfile || firstfile[8] || !BROWSE_ENABLED(firstfile) || !lastfile || lastfile[8] || !*(SInt16 *)(lastfile + 26) || first <= 0 || last < first)) {
    if (last < *(SInt32 *)(firstfile + 14)) ++last;
    fn_004c5f00(object, *(SInt16 *)(firstfile + 26), *(SInt16 *)(lastfile + 26), first, last);
    }
}

void CBrowse_NewData(char *object, char *firstfile, char *lastfile, SInt32 first, SInt32 last)
{
    char *alternate = 0, *full, *shortnode, *name;
    SInt32 flags = 0, fullid, id, firstid, lastid;
    UInt8 isStatic = fn_004531a0(object);
    if (!object) CError_Internal("CBrowse.c", 0x3e0);
    if (data_00717466 == ';') last += data_0070ffc8;
    if (!(!firstfile || firstfile[8] || !BROWSE_ENABLED(firstfile) || !lastfile || lastfile[8] || !*(SInt16 *)(lastfile + 26) || first <= 0 || last < first)) {
    full = (char *)GetHashNameNode(CError_GetObjectName((void *)object));
    shortnode = *(char **)(object + 12);
    if (shortnode != full) alternate = full + 10;
    fullid = *(SInt32 *)(full + 4); id = *(SInt32 *)(shortnode + 4); lastid = *(SInt16 *)(lastfile + 26); name = shortnode + 10; firstid = *(SInt16 *)(firstfile + 26);
    if (!name) CError_Internal("CBrowse.c", 0x262);
    AppendGListByte(&gBrowseData, isStatic ? (UInt8)6 : (UInt8)1);
    AppendGListWord(&gBrowseData, (SInt16)firstid); AppendGListWord(&gBrowseData, (SInt16)lastid);
    AppendGListLong(&gBrowseData, first - 1); AppendGListLong(&gBrowseData, last - 1); AppendGListLong(&gBrowseData, 0);
    RecordName(&gBrowseData, name, id);
    if (alternate && alternate != name) RecordName(&gBrowseData, alternate, fullid);
    else AppendGListWord(&gBrowseData, 0);
    if (!isStatic) { if (*(UInt16 *)(object + 24) == 0x102) flags |= 2; AppendGListLong(&gBrowseData, flags); }
    }
}

void CBrowse_EndStruct(volatile SInt32 value, GList *saved)
{
    SInt32 offset;
    if (!saved) CError_Internal("CBrowse.c", 0x248);
    if (gClassData.data) {
        if (value > 0 && gClassData.size > 0) {
            *(SInt32 *)(*gClassData.data + 9) = value;
            offset = gBrowseData.size; AppendGListNoData(&gBrowseData, gClassData.size);
            memcpy(*gBrowseData.data + offset, *gClassData.data, gClassData.size);
            AppendGListByte(&gBrowseData, -1);
        }
        FreeGList(&gClassData);
    }
    gClassData = *saved;
}

void CBrowse_EndClass(volatile SInt32 value, char *saved)
{
    SInt32 offset;
    if (!saved) CError_Internal("CBrowse.c", 0x1df);
    if (gClassData.data) {
        if (gClassData.size > 0) {
            if (data_00717466 == ';' && (!*(char **)(saved + 16) || value < *(SInt32 *)(*(char **)(saved + 16) + 14))) ++value;
            *(SInt32 *)(*gClassData.data + 9) = value;
            offset = gBrowseData.size; AppendGListNoData(&gBrowseData, gClassData.size);
            memcpy(*gBrowseData.data + offset, *gClassData.data, gClassData.size);
            AppendGListByte(&gBrowseData, -1);
        }
        FreeGList(&gClassData);
    }
    gClassData = *(GList *)saved;
}

extern UInt8 IsTempName(void *);
extern UInt8 CParser_IsDataObject(void *);
extern char *fn_00558760(void *);
extern char *CTemplTool_Class2TemplClassInst(void *);
extern char *CTemplTool_Template2TemplClass(void *);
static const SInt8 gFromAccessType[4] = {4, 1, 2, 0};

void RecordFunction(char *object, SInt32 firstid, SInt32 lastid, SInt32 first, SInt32 last)
{
    char *name, *node, *full, *type = *(char **)(object + 16);
    char text[256];
    SInt32 flags, memberid, fullid, id;
    UInt32 qualifiers;
    if (!type || *type != 7) CError_Internal("CBrowse.c", 0x309);
    type = *(char **)(object + 16);
    if ((*(UInt32 *)(type + 22) & 0x300) && (!lastid || first < 0)) return;
    node = (char *)GetHashNameNode(CError_GetObjectName(object)); full = node + 10; fullid = *(SInt32 *)(node + 4);
    if (*(UInt32 *)(type + 22) & 0x1000) {
        node = *(char **)(*(char **)(type + 30) + 10); name = node + 10; id = *(SInt32 *)(node + 4);
    } else if (*(UInt32 *)(type + 22) & 0x2000) {
        text[0] = '~'; strncpy(text + 1, *(char **)(*(char **)(type + 30) + 10) + 10, 255); text[255] = 0;
        name = text; id = -1;
    } else {
    node = fn_00558760(*(void **)(object + 12));
    if (node) { name = node; id = -1; }
    else if (!IsTempName(*(void **)(object + 12))) { node = *(char **)(object + 12); name = node + 10; id = *(SInt32 *)(node + 4); }
    else { name = full; id = fullid; }
    }
    if (!name) CError_Internal("CBrowse.c", 0x262);
    AppendGListByte(&gBrowseData, 0);
    AppendGListWord(&gBrowseData, (SInt16)firstid); AppendGListWord(&gBrowseData, (SInt16)lastid);
    AppendGListLong(&gBrowseData, first - 1); AppendGListLong(&gBrowseData, last - 1); AppendGListLong(&gBrowseData, 0);
    RecordName(&gBrowseData, name, id);
    if (full && full != name) RecordName(&gBrowseData, full, fullid); else AppendGListWord(&gBrowseData, 0);
    qualifiers = *(UInt32 *)(object + 20); flags = 0;
    if (qualifiers & 16) flags |= 128;
    if (qualifiers & 8) flags |= 256;
    if (qualifiers & 4) flags |= 512;
    if (*(UInt16 *)(object + 24) == 0x102) flags |= 2;
    if (*(UInt32 *)(type + 22) & 16) flags |= 8;
    AppendGListLong(&gBrowseData, flags);
    memberid = 0;
    if (*(UInt32 *)(type + 22) & 16) {
        memberid = *(SInt32 *)(type + 38);
        if (memberid <= 0) { memberid = gNextMemberFuncID++; *(SInt32 *)(type + 38) = memberid; }
    }
    AppendGListLong(&gBrowseData, memberid);
}

void CBrowse_NewEnumConstant(void *nspace, char *node, char *firstfile, char *lastfile, SInt32 first, SInt32 last)
{
    char *alternate, *name;
    SInt32 id;
    SInt32 firstid, lastid;
    if (data_00717466 == ',') last += data_0070ffc8;
    if (!(!firstfile || firstfile[8] || !BROWSE_ENABLED(firstfile) || !lastfile || lastfile[8] || !*(SInt16 *)(lastfile + 26) || first <= 0 || last < first)) {
    alternate = CError_GetQualifiedName((NameSpace *)nspace, (HashNameNode *)node); id = *(SInt32 *)(node + 4); name = node + 10;
    lastid = *(SInt16 *)(lastfile + 26); firstid = *(SInt16 *)(firstfile + 26);
    if (!name) CError_Internal("CBrowse.c", 0x262);
    AppendGListByte(&gBrowseData, 6);
    AppendGListWord(&gBrowseData, (SInt16)firstid); AppendGListWord(&gBrowseData, (SInt16)lastid);
    AppendGListLong(&gBrowseData, first - 1); AppendGListLong(&gBrowseData, last - 1); AppendGListLong(&gBrowseData, 0);
    RecordName(&gBrowseData, node + 10, id);
    if (alternate && alternate != node + 10) RecordName(&gBrowseData, alternate, -1); else AppendGListWord(&gBrowseData, 0);
    }
}

void CBrowse_NewEnum(void *nspace, char *node, char *firstfile, char *lastfile, SInt32 first, SInt32 last)
{
    char *alternate, *name;
    SInt32 id;
    SInt32 firstid, lastid;
    if (!(!firstfile || firstfile[8] || !BROWSE_ENABLED(firstfile) || !lastfile || lastfile[8] || !*(SInt16 *)(lastfile + 26) || first <= 0 || last < first)) {
    alternate = CError_GetQualifiedName((NameSpace *)nspace, (HashNameNode *)node); id = *(SInt32 *)(node + 4); name = node + 10;
    lastid = *(SInt16 *)(lastfile + 26); firstid = *(SInt16 *)(firstfile + 26);
    if (!name) CError_Internal("CBrowse.c", 0x262);
    AppendGListByte(&gBrowseData, 4);
    AppendGListWord(&gBrowseData, (SInt16)firstid); AppendGListWord(&gBrowseData, (SInt16)lastid);
    AppendGListLong(&gBrowseData, first - 1); AppendGListLong(&gBrowseData, last - 1); AppendGListLong(&gBrowseData, 0);
    RecordName(&gBrowseData, node + 10, id);
    if (alternate && alternate != node + 10) RecordName(&gBrowseData, alternate, -1); else AppendGListWord(&gBrowseData, 0);
    }
}

void CBrowse_NewTypedef(void *nspace, char *node, char *firstfile, char *lastfile, SInt32 first, SInt32 last)
{
    char *alternate, *name;
    SInt32 id;
    SInt32 firstid, lastid;
    if (!(!firstfile || firstfile[8] || !BROWSE_ENABLED(firstfile) || !lastfile || lastfile[8] || !*(SInt16 *)(lastfile + 26) || first <= 0 || last < first)) {
    alternate = CError_GetQualifiedName((NameSpace *)nspace, (HashNameNode *)node); id = *(SInt32 *)(node + 4); name = node + 10;
    lastid = *(SInt16 *)(lastfile + 26); firstid = *(SInt16 *)(firstfile + 26);
    if (!name) CError_Internal("CBrowse.c", 0x262);
    AppendGListByte(&gBrowseData, 5);
    AppendGListWord(&gBrowseData, (SInt16)firstid); AppendGListWord(&gBrowseData, (SInt16)lastid);
    AppendGListLong(&gBrowseData, first - 1); AppendGListLong(&gBrowseData, last - 1); AppendGListLong(&gBrowseData, 0);
    RecordName(&gBrowseData, node + 10, id);
    if (alternate && alternate != node + 10) RecordName(&gBrowseData, alternate, -1); else AppendGListWord(&gBrowseData, 0);
    }
}

static inline void EmitStandardData(GList *out, char *name)
{
    SInt32 length = strlen(name);
    if (length < 32000) { AppendGListWord(out, (SInt16)length); if (length) AppendGListData(out, name, length + 1); }
    else { AppendGListWord(out, 32000); AppendGListData(out, name, 32000); AppendGListByte(out, 0); }
}

void CBrowse_AddStructMember(char *member, SInt32 first, SInt32 last)
{
    if (data_00717466 == ';') ++last;
    if (gClassData.data && member && first > 0 && last >= first) {
        AppendGListByte(&gClassData, 1); AppendGListByte(&gClassData, 4); AppendGListLong(&gClassData, 0);
        AppendGListLong(&gClassData, first - 1); AppendGListLong(&gClassData, last - 1);
        EmitStandardData(&gClassData, *(char **)(member + 8) + 10);
    }
}

void CBrowse_BeginStruct(char *context, char *type, char *saved)
{
    char *firstfile, *lastfile, *name;
    if (!context || !saved) CError_Internal("CBrowse.c", 0x1fb);
    *(GList *)saved = gClassData; *(char **)(saved + 16) = *(char **)(context + 132);
    firstfile = *(char **)(context + 132);
    if (!firstfile || firstfile[8] || !*(SInt16 *)(firstfile + 26) || !BROWSE_ENABLED(firstfile) || !(lastfile = *(char **)(context + 136)) || lastfile[8] || !*(SInt16 *)(lastfile + 26) || *(SInt32 *)(context + 140) <= 0) { memclrw(&gClassData, 16); return; }
    name = *(char **)(type + 6);
    if (!name || IsTempName(name)) { memclrw(&gClassData, 16); return; }
    if (InitGList(&gClassData, 16384)) CError_NoMem();
    AppendGListByte(&gClassData, 2);
    AppendGListWord(&gClassData, *(SInt16 *)(*(char **)(context + 132) + 26)); AppendGListWord(&gClassData, *(SInt16 *)(*(char **)(context + 136) + 26));
    AppendGListLong(&gClassData, *(SInt32 *)(context + 140) - 1);
    if (gClassData.size != 9) CError_Internal("CBrowse.c", 0x227);
    AppendGListLong(&gClassData, *(SInt32 *)(context + 140) - 1); AppendGListLong(&gClassData, 0);
    RecordName(&gClassData, name + 10, *(SInt32 *)(name + 4));
    AppendGListWord(&gClassData, 0); AppendGListLong(&gClassData, 0); AppendGListByte(&gClassData, 0);
}

void CBrowse_AddClassMemberData(char *object, SInt32 first, SInt32 last)
{
    if (!object) CError_Internal("CBrowse.c", 0x1cf);
    if (gClassData.data && first > 0 && last >= first && CParser_IsDataObject(object)) {
        if (data_00717466 == ';') ++last;
        AppendGListByte(&gClassData, 1); AppendGListByte(&gClassData, gFromAccessType[(UInt8)object[1]]); AppendGListLong(&gClassData, 2);
        AppendGListLong(&gClassData, first - 1); AppendGListLong(&gClassData, last - 1);
        EmitStandardData(&gClassData, *(char **)(object + 12) + 10);
    }
}

void CBrowse_AddClassMemberFunction(char *object, SInt32 first, SInt32 last)
{
    char *type;
    SInt32 flags, id;
    UInt32 tf;
    if (!object) CError_Internal("CBrowse.c", 0x19a);
    if (gClassData.data && first > 0 && last >= first) {
    type = *(char **)(object + 16); flags = 0;
    if (!type || *type != 7) CError_Internal("CBrowse.c", 0x1a5);
    type = *(char **)(object + 16); tf = *(UInt32 *)(type + 22);
    if (!(tf & 256)) {
    if (object[2] == 4) flags |= 1024;
    if (tf & 8) flags |= 1;
    if (type[42]) flags |= 2;
    if (tf & 0x1000) flags |= 0x800;
    if (tf & 0x2000) flags |= 0x1000;
    AppendGListByte(&gClassData, 0); AppendGListByte(&gClassData, gFromAccessType[(UInt8)object[1]]); AppendGListLong(&gClassData, flags);
    id = *(SInt32 *)(type + 38);
    if (id <= 0) {
        if (!( *(UInt32 *)(type + 22) & 2) || id == -1) AppendGListLong(&gMemberFuncList, (SInt32)object);
        id = gNextMemberFuncID++; *(SInt32 *)(type + 38) = id;
    }
    AppendGListLong(&gClassData, id); AppendGListLong(&gClassData, first - 1); AppendGListLong(&gClassData, last);
    }
    }
}

void CBrowse_AddClassMemberVar(char *member, SInt32 first, SInt32 last)
{
    if (!member) CError_Internal("CBrowse.c", 0x188);
    if (gClassData.data && first > 0 && last >= first) {
        if (data_00717466 == ';') ++last;
        AppendGListByte(&gClassData, 1); AppendGListByte(&gClassData, gFromAccessType[(UInt8)member[1]]); AppendGListLong(&gClassData, 0);
        AppendGListLong(&gClassData, first - 1); AppendGListLong(&gClassData, last - 1);
        EmitStandardData(&gClassData, *(char **)(member + 8) + 10);
    }
}

void CBrowse_BeginClass(char *context, char *saved)
{
    char *firstfile, *lastfile, *type, *node, *name, *base, *inst;
    SInt32 count, id;
    if (!context || !*(char **)context || !saved) CError_Internal("CBrowse.c", 0xf5);
    *(GList *)saved = gClassData; *(char **)(saved + 16) = *(char **)(context + 132);
    firstfile = *(char **)(context + 132);
    if (!firstfile || firstfile[8] || !*(SInt16 *)(firstfile + 26) || !BROWSE_ENABLED(firstfile) || !(lastfile = *(char **)(context + 136)) || lastfile[8] || !*(SInt16 *)(lastfile + 26) || *(SInt32 *)(context + 140) <= 0) { memclrw(&gClassData, 16); return; }
    type = *(char **)context;
    if (IsTempName(*(char **)(type + 10))) { memclrw(&gClassData, 16); return; }
    if (InitGList(&gClassData, 16384)) CError_NoMem();
    AppendGListByte(&gClassData, 2);
    AppendGListWord(&gClassData, *(SInt16 *)(*(char **)(context + 132) + 26)); AppendGListWord(&gClassData, *(SInt16 *)(*(char **)(context + 136) + 26));
    AppendGListLong(&gClassData, *(SInt32 *)(context + 140) - 1);
    if (gClassData.size != 9) CError_Internal("CBrowse.c", 0x123);
    AppendGListLong(&gClassData, *(SInt32 *)(context + 140) - 1); AppendGListLong(&gClassData, 0);
    node = *(char **)(*(char **)context + 10); RecordName(&gClassData, node + 10, *(SInt32 *)(node + 4));
    name = CError_GetTypeName(*(char **)context, 0, 0);
    if (strcmp(*(char **)(*(char **)context + 10) + 10, name)) RecordName(&gClassData, name, -1); else AppendGListWord(&gClassData, 0);
    AppendGListLong(&gClassData, 0);
    count = 0; for (base = *(char **)(*(char **)context + 14); base; base = *(char **)base) ++count;
    AppendGListByte(&gClassData, (SInt8)count);
    for (base = *(char **)(*(char **)context + 14); base; base = *(char **)base) {
        AppendGListByte(&gClassData, gFromAccessType[(UInt8)base[16]]); AppendGListByte(&gClassData, base[17]);
        type = *(char **)(base + 4);
        if (*(UInt32 *)(type + 34) & 0x800) { inst = CTemplTool_Class2TemplClassInst(type); if (!inst[65]) type = CTemplTool_Template2TemplClass(*(char **)(inst + 52)); }
        name = CError_GetTypeName(type, 0, 0);
        while (*name && *name >= '0' && *name <= '9') ++name;
        id = *(SInt32 *)(*(char **)(*(char **)(base + 4) + 10) + 4);
        while (*name && *name >= '0' && *name <= '9') { ++name; id = -1; }
        RecordName(&gClassData, name, id);
    }
}
