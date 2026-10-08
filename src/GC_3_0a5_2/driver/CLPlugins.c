/* GC 3.0 Windows plugin registry; names from explicit CLPlugins.c STABS. */
#include "compiler/common.h"
#include "driver/OSAssert.h"
#include <string.h>
#include <stdio.h>
#pragma pack(push, 2)
typedef struct OSSpec { char path[260], name[256]; } OSSpec;
typedef struct VersionInfo { UInt16 major,minor,patch,build; } VersionInfo;
typedef struct ToolVersionInfo {
    SInt16 version;
    char *company,*product,*tool,*copyright,*versionString;
    VersionInfo number;
    char *versionASCII;
    UInt32 unknown_22; /* Unreferenced tail inferred from adjacent retdf at6d618e. */ 
} ToolVersionInfo;
struct ObjFlagsData { SInt16 version; UInt32 compilerFlags; char *extensions[6]; UInt32 rest[10]; };
#pragma pack(pop)
#pragma options align = mac68k
struct FileMap {
    UInt32 type;
    char ext[0x20];
    unsigned int value;
    char unknown[32];
};
#pragma options align = reset
#pragma options align = mac68k
struct FileMapInfo {
    UInt16 unk0;
    SInt16 count;
    struct FileMap *maps;
};
#pragma options align = reset
#pragma options align = mac68k
struct PlugAux {
    short(__stdcall *getTargetInfo)(
        unsigned char **); 
    short(__stdcall *getFileMap)(struct FileMapInfo **); 
    UInt8 pad[0x08]; 
    SInt16(__stdcall *getObjectFlags)(
        unsigned char **); 
    short(__stdcall *writeObjectFile)(
        OSSpec *, OSSpec *, unsigned int, unsigned int,
        void *); 
};
#pragma options align = reset
struct Plugin {
    struct PluginDataCallbacks *callbacks;
    struct PlugAux *targetCallbacks;
    struct PluginQueryTable *queryCallbacks;
    struct CWPluginPrivateContext *object;
    char *cached_ascii_version;
    struct Plugin *next;
    void *module;
    OSSpec spec;
};
#pragma pack(push, 1)
struct PluginDataCallbacks {
    unsigned short(__stdcall *entry)(unsigned int);
    short(__stdcall *getData)(unsigned int **data, unsigned int *size);
    short(__stdcall *getDisplayName)(char **);
    short(__stdcall *getName)(char **);
    short(__stdcall *getDirectoryList)(struct PluginDirectoryList **);
    unsigned char unknown14
        [8]; 
    short(__stdcall *getResult)(void **result);
    short(__stdcall *getFileTypeMappings)(void **);
    short(__stdcall *getToolVersionInfo)(ToolVersionInfo **);
};
#pragma pack(pop)
#pragma options align = mac68k
struct PluginDesc {
    SInt16 descriptorVersion; 
    UInt32 type;              
    UInt16 api1;              
    UInt32 flags;             
    SInt32 lang;              
    UInt16 api2;              
};
#pragma options align = reset
#pragma pack(push, 1)
struct PluginDirectoryList {
    unsigned short value;
    short count;   
    char **panels; 
};
#pragma pack(pop)
struct PluginOptionalData {
    unsigned char bytes[24];
};
struct PluginQueryTable {
    unsigned int unknownEntry;
    short(__stdcall *query)(unsigned int argument, char **kind, UInt8 *result);
};
union PluginDataValidation {
    char message[36];
    UInt32 sizes[9];
};
#pragma options align = mac68k
struct PluginRequest {
    union {
        int signed_kind;
        unsigned int kind;
    } tag;
    int secondCode;
    int flags;
    unsigned int name;
    char flag_10;
    char reserved;
};
#pragma options align = reset
#pragma options align = mac68k
struct TargetInfo {
    UInt16 unk0;
    SInt16 ncpu;
    UInt32 *cpus;
    SInt16 nos;
    UInt32 *oses;
};
#pragma options align = reset

extern void *__stdcall xmalloc(const char *,unsigned int);
extern void *__stdcall xrealloc(const char *,void *,unsigned int);
extern char *__stdcall xstrdup(const char *);
extern void __stdcall xfree(void *);
static void GetToolVersionInfo(void);
extern void *__alloca(unsigned int);
extern void CLReport(SInt16,...);
extern void __stdcall fn_00412270(void *);
extern Boolean fn_00425e20(Plugin *, Boolean);
extern void CLReportWarning(SInt16,...);
extern void CLReportError(SInt16,...);
extern void CLPrintErr(const char *,...);
extern void CLPrint(const char *,...);
extern int __stdcall ustrcmp(const char *,const char *);
extern NameTableEntry *Prefs_FindPanel(const char *);
extern Boolean fn_004186c0(const OSSpec *,UInt32,UInt32,void *);
extern void __stdcall OS_AddFileTypeMappingList(void *,unsigned int);
extern UInt8 data_00702f34;
extern UInt8 data_0070324d;
static char *Plugin_GetDisplayName(Plugin *);
extern OSSpec data_00702d28;
static VersionInfo fakeversion;
static ToolVersionInfo data_006d6168;
static PluginDesc retdf;
static TargetInfo faketl = {1,0,0,0,0};
static struct PluginDirectoryList fakepnl = {1,0,0};
static FileMapInfo fakeel = {2,0,0};
static struct ObjFlagsData fake = {2,0,{"","","","","",""},{0}};
static UInt32 DropInFlagsSize[3] = {0,16,18};
static Plugin *pluginlist;
static struct { char *company,*product,*tool,*copyright,*version; } toolVersionInfo;
static VersionInfo toolVersion;
static UInt8 useToolVersion;

extern void *__stdcall fn_004263c0(unsigned int);
char *Plugin_GetVersionInfoASCII(Plugin *);
char *Plugin_GetDropInName(Plugin *plugin);
VersionInfo *Plugin_GetVersionInfo(Plugin *plugin);
PluginDesc *Plugin_GetDropInFlags(Plugin *provider);
unsigned int Plugin_GetPluginType(Plugin *type);
TargetInfo *Plugin_CL_GetTargetList(Plugin *entry);
void *Plugin_GetPanelList(Plugin *plugin);
FileMapInfo *Plugin_CL_GetExtMapList(Plugin *context);
unsigned int Plugin_GetFileTypeMappingList(void *input);
void *Plugin_CL_GetObjectFlags(Plugin *plugin);
Boolean Plugin_MatchesName(Plugin *plugin, char *name);
char Plugin_CL_MatchesTarget(Plugin *plugin, int firstIdentifier, int secondIdentifier, char flag);
char CL_MatchesExtMapping(FileMap *reference, int value, char *name, UInt8 flag);
char Plugin_CL_MatchesFileType(Plugin *entry, int value, char *text, UInt8 option);
Boolean Plugin_MatchesType(Plugin *entry, int type, int language, int flags);
Boolean Plugin_Pr_MatchesPlugin(Plugin *p, PluginRequest *a, SInt32 b, SInt32 c);
UInt8 Plugin_Pr_MatchesPanels(Plugin *plugin, unsigned int queryArgument, char **queryKind);
UInt8 Plugin_CL_GetCompilerMapping(Plugin *plugin, int mode, char *name, unsigned int *result);
static Boolean SupportedPlugin(Plugin *plug, const char **errmsg);
static Boolean VerifyPanels(Plugin *plugin);
void Plugin_Free(Plugin *allocations);
Boolean Plugin_VerifyPanels(Plugin *input);
void Plugins_Init(void);
void Plugins_Term(void);
int Plugins_Add(void *pluginHandle);
Plugin *Plugins_CL_MatchTarget(Plugin *node, SInt32 a, SInt32 b, SInt32 c, SInt32 d);
Plugin *Plugins_GetPluginForFile(Plugin *first, int selector, int optionKind, int optionValue,
                                                       int nameKind, char *name, int selectorValue);
Plugin *Plugins_GetLinker(Plugin *start, int kind, int variant);
Plugin *Plugins_GetPreLinker(Plugin *plugins, unsigned int kind, unsigned int subtype);
Plugin *Plugins_GetPostLinker(Plugin *plugins, int kind, int selector);
Plugin *Plugins_GetParserForPlugin(Plugin *plugins, int selector, int request_count,
                                                  PluginRequest *requests, int option4, int option5, int value_count,
                                                  char **values);
int Plugins_GetPluginList(Plugin *list, SInt32 *count, PluginRequest **out);
static inline SInt32 CountPluginNames(Plugin *list);
int Plugins_GetPrefPanelUnion(Plugin *nameList, SInt32 *nameCount, char ***nameArray);
int Plugin_AddFileTypeMappings(Plugin *plugin, SInt32 refCon);
int Plugins_AddFileTypeMappingsForTarget(Plugin *node, SInt32 argument, SInt32 firstIdentifier, SInt32 secondIdentifier);
short Plugin_Call(Plugin *dispatch, CWPluginPrivateContext *argument);

typedef short(__stdcall *code_short)(void *);

typedef short(__stdcall *cb_t)(char **);

typedef unsigned short(__stdcall *pfn_t)(void *);

typedef SInt16(__stdcall *CLPluginFunc)(PluginRequest *, SInt32, SInt32, Boolean *);

typedef struct PlugAux PlugAux;

typedef short(__stdcall *PluginInputCallback)(int, short *, unsigned int, int, int);
typedef short(__stdcall *PluginResultCallback)(unsigned int *);

char *Plugin_GetDropInName(Plugin *plugin)
{
    int result;
    char *name;
    ToolVersionInfo *tvi;
    int status;
    if (!plugin) OS_ASSERT_AT("pl","CLPlugins.c",0x114);
    if (plugin->callbacks->getToolVersionInfo && (status=plugin->callbacks->getToolVersionInfo(&tvi))==0 && tvi->product)
        return tvi->product;
    if (plugin->callbacks->getName) {
        result=plugin->callbacks->getName(&name);
        if (!result) return name;
    }
    return "(no name found)";
}

VersionInfo *Plugin_GetVersionInfo(Plugin *plugin)
{
    int status;
    VersionInfo *result;

    if (plugin == NULL) {
        OS_ASSERT_AT("pl", "CLPlugins.c", 0x126);
    }
    if (plugin->callbacks->getResult != NULL) {
        status = plugin->callbacks->getResult((void **)&result);
        if (status == 0) {
            return result;
        }
    }
    return &fakeversion;
}

PluginDesc *Plugin_GetDropInFlags(Plugin *provider)
{
    unsigned int *data;
    unsigned int size;
    int status;

    if (provider == NULL) {
        OS_ASSERT_AT("pl", "CLPlugins.c", 0x18a);
    }
    if (provider->callbacks->getData != NULL) {
        if ((status=provider->callbacks->getData(&data, &size)) == 0) {
            memset(&retdf, 0, sizeof(retdf));
            memcpy(&retdf, data, size);
            return &retdf;
        }
    }
    return NULL;
}

unsigned int Plugin_GetPluginType(Plugin *type)
{
    PluginDesc *resolvedType;
    if (!type)
        OS_ASSERT_AT("pl", "CLPlugins.c", 0x19a);
    resolvedType = Plugin_GetDropInFlags(type);
    if (resolvedType)
        return resolvedType->type;
    return 1313820229U;
}

TargetInfo *Plugin_CL_GetTargetList(Plugin *entry)
{
    int status;
    unsigned char *result;

    if (entry == NULL) {
        OS_ASSERT_AT("pl", "CLPlugins.c", 0x1a7);
    }
    if (((Plugin *)entry)->targetCallbacks == NULL) {
        OS_ASSERT_AT("pl->cl_cb != NULL", "CLPlugins.c", 0x1a8);
    }
    if (((Plugin *)entry)->targetCallbacks->getTargetInfo != NULL) {
        status = ((Plugin *)entry)->targetCallbacks->getTargetInfo(&result);
        if (status == 0) {
            return (TargetInfo *)result;
        }
    }
    return &faketl;
}

void *Plugin_GetPanelList(Plugin *plugin)
{
    struct PluginDirectoryList *directoryList;
    int status;
    if (plugin == NULL)
        OS_ASSERT_AT("pl", "CLPlugins.c", 0x1be);
    if (plugin->callbacks->getDirectoryList != NULL) {
        status = plugin->callbacks->getDirectoryList(&directoryList);
        if (status == 0)
            return directoryList;
    }
    return &fakepnl;
}

FileMapInfo *Plugin_CL_GetExtMapList(Plugin *context)
{
    FileMapInfo *result;
    int status;

    if (context == NULL) {
        OS_ASSERT_AT("pl", "CLPlugins.c", 0x1d2);
    }
    if (context->targetCallbacks == NULL) {
        OS_ASSERT_AT("pl->cl_cb != NULL", "CLPlugins.c", 0x1d3);
    }
    if (context->targetCallbacks->getFileMap != NULL) {
        if ((status=(*context->targetCallbacks->getFileMap)(&result)) == 0) {
            return result;
        }
    }
    return &fakeel;
}

unsigned int Plugin_GetFileTypeMappingList(void *input)
{
    int status;
    unsigned int result;
    PluginResultCallback **callbacks = input;

    if (callbacks == NULL) {
        OS_ASSERT_AT("pl", "CLPlugins.c", 0x1e7);
    }
    if ((*callbacks)[8] != NULL) {
        status = (*callbacks)[8](&result);
        if (status == 0) {
            return result;
        }
    }
    return 0;
}

void *Plugin_CL_GetObjectFlags(Plugin *plugin)
{
    unsigned char *flags;
    PluginDesc *info;
    int status;

    if (plugin == NULL) {
        OS_ASSERT_AT("pl", "CLPlugins.c", 0x1f3);
    }
    if (plugin->targetCallbacks == NULL) {
        OS_ASSERT_AT("pl->cl_cb != NULL", "CLPlugins.c", 0x1f4);
    }
    if (plugin->targetCallbacks->getObjectFlags != NULL) {
        if ((status=plugin->targetCallbacks->getObjectFlags(&flags)) == 0) {
            return flags;
        }
    }
    info = Plugin_GetDropInFlags(plugin);
    if (info->type == 0x436f6d70) {
        return NULL;
    }
    return &fake;
}

Boolean Plugin_MatchesName(Plugin *plugin, char *name)
{
    char *pluginName;
    int comparison;

    pluginName = Plugin_GetDropInName(plugin);
    comparison = strcmp(pluginName, name);
    return comparison == 0;
}

char Plugin_CL_MatchesTarget(Plugin *plugin, int firstIdentifier, int secondIdentifier, char flag)
{
    TargetInfo *lists;
    int firstIndex;

    lists = Plugin_CL_GetTargetList(plugin);
    for (firstIndex = 0; firstIndex < lists->ncpu; firstIndex = firstIndex + 1) {
        if (firstIdentifier == 0x2a2a2a2a || firstIdentifier == lists->cpus[firstIndex] ||
            (lists->cpus[firstIndex] == 0x2a2a2a2a && (char)flag == '\0')) {
            int secondIndex;
            for (secondIndex = 0; secondIndex < lists->nos; secondIndex = secondIndex + 1) {
                if (secondIdentifier == 0x2a2a2a2a || secondIdentifier == lists->oses[secondIndex] ||
                    (lists->oses[secondIndex] == 0x2a2a2a2a && (char)flag == '\0')) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

char CL_MatchesExtMapping(FileMap *reference, int value, char *name, UInt8 flag)
{
    if (flag && value && reference->type && value == reference->type) return 1;
    if (!(((reference->ext[0] != '\0' || flag != '\0') && (name[0] != '\0' || flag != '\0')) ||
          reference->type != value) ||
        (((reference->type == 0 && flag == '\0') || (value == 0 && flag == '\0')) &&
         ustrcmp(reference->ext, name) == 0) ||
        (ustrcmp(reference->ext, name) == 0 && reference->type == value))
        return 1;
    else
        return 0;
}

char Plugin_CL_MatchesFileType(Plugin *entry, int value, char *text, UInt8 option)
{
    FileMapInfo *list = Plugin_CL_GetExtMapList(entry);
    int index = 0;
    while (index < list->count) {
        if (CL_MatchesExtMapping(&list->maps[index], value, text, option) != 0) {
            return 1;
        }
        index++;
    }
    return 0;
}

Boolean Plugin_MatchesType(Plugin *entry, int type, int language, int flags)
{
    PluginDesc *desc = Plugin_GetDropInFlags(entry);
    if (desc->type == type || type == 0x2a2a2a2aU) {
        if (desc->lang == language || language == 0x2a2a2a2a || (desc->lang == 0x2a2a2a2a && (Boolean)flags == 0))
            return 1;
    }
    return 0;
}
Boolean Plugin_Pr_MatchesPlugin(Plugin *p, PluginRequest *a, SInt32 b, SInt32 c)
{
    CLPluginFunc f;
    Boolean result;
    int status;

    if (p->queryCallbacks == NULL) {
        OS_ASSERT_AT("pl->pr_cb != NULL", "CLPlugins.c", 0x277);
    }
    if ((f = *(CLPluginFunc *)p->queryCallbacks) != NULL) {
        if ((status=f(a, b, c, &result)) == 0) {
            return result;
        }
    }
    return 0;
}

UInt8 Plugin_Pr_MatchesPanels(Plugin *plugin, unsigned int queryArgument, char **queryKind)
{
    int status;
    UInt8 result;

    if (plugin->queryCallbacks == NULL) {
        OS_ASSERT_AT("pl->pr_cb != NULL", "CLPlugins.c", 0x283);
    }
    if (plugin->queryCallbacks->query != NULL) {
        status = plugin->queryCallbacks->query(queryArgument, queryKind, &result);
        if (status == 0) {
            return result;
        }
    }
    return 0;
}

UInt8 Plugin_CL_WriteObjectFile(Plugin *plugin, OSSpec *src, OSSpec *out, UInt32 creator, UInt32 type, void *data)
{
    OSSpec srcfss, outfss;
    int status;
    if (!plugin->targetCallbacks) OS_ASSERT_AT("pl->cl_cb != NULL", "CLPlugins.c", 0x28f);
    if (!(data && src && out)) OS_ASSERT_AT("data != NULL && src != NULL && out != NULL", "CLPlugins.c", 0x290);
    if (plugin->targetCallbacks->writeObjectFile) {
        srcfss = *src;
        outfss = *out;
        status=plugin->targetCallbacks->writeObjectFile(&srcfss, &outfss, creator, type, data);
        return status == 0;
    }
    return fn_004186c0(out, creator, type, data);
}

UInt8 Plugin_CL_GetCompilerMapping(Plugin *plugin, int mode, char *name, unsigned int *result)
{
    char matched;
    FileMapInfo *list;
    int index;
    int selected;

    list = Plugin_CL_GetExtMapList(plugin);
    selected = -1;
    for (index = 0; index < list->count; ++index) {
        matched = CL_MatchesExtMapping(&list->maps[index], mode, name, 0);
        if (matched != 0) {
            selected = index;
            matched = CL_MatchesExtMapping(&list->maps[index], mode, name, 1);
            if (matched != 0)
                break;
        }
    }
    if (selected < 0) {
        *result = 0;
        return 0;
    }
    *result = list->maps[selected].value;
    return 1;
}
static Boolean SupportedPlugin(Plugin *plug, const char **errmsg)
{
    PluginDesc *flags;
    unsigned int size;
    int status;
    *errmsg = "";

    if (plug->callbacks->getData == NULL) {
        *errmsg = "GetDropInFlags callback not found";
        return 0;
    }
    if ((status=plug->callbacks->getData((unsigned int **)&flags, &size)) != 0) {
        *errmsg = "GetDropInFlags callback failed";
        return 0;
    }
    if (flags->type != 'Comp' && flags->type != 'Link' && flags->type != 'Pars' &&
        flags->type != (unsigned int)'cldr') {
        *errmsg = "The plugin type is not supported by this driver";
        return 0;
    }
    if (flags->api1 > 15) {
        *errmsg = "The plugin's earliest compatible API version is too new for this driver";
        return 0;
    }
    if (flags->api1 > 1 && flags->api2 < 15 && data_00702f34) {
        CLPrintErr("%s's newest compatible API version is probably too old for this driver\n",
                                Plugin_GetDropInName(plug));
    }
    if (size != DropInFlagsSize[flags->descriptorVersion]) {
        *errmsg = "The plugin's DropInFlags has an unexpected size";
        return 0;
    }
    if ((flags->flags & 1) == 0 && plug->callbacks->entry == NULL) {
        *errmsg = "The plugin has no entry point";
        return 0;
    }
    if ((flags->flags & 1) != 0 && plug->callbacks->entry != NULL) {
        *errmsg = "The executable tool stub has an entry point";
        return 0;
    }
    if (plug->targetCallbacks != NULL) {
        ObjFlagsData *objectFlags;

        if (plug->targetCallbacks->getObjectFlags == NULL && flags->type == 'Comp') {
            *errmsg = "GetObjectFlags callback not found in compiler plugin";
            return 0;
        }
        objectFlags = Plugin_CL_GetObjectFlags(plug);
        if (objectFlags->version < 2 || ((objectFlags->compilerFlags & 0x3fffffff) != 0 || (objectFlags->compilerFlags & 0xc0000000) == 0xc0000000)) {
            *errmsg = "The object flags data is out-of-date or invalid";
            return 0;
        }
    }
    return 1;
}

static Boolean VerifyPanels(Plugin *plugin)
{
    PluginDirectoryList *directories;
    int index, status;
    if (plugin->callbacks->getDirectoryList && (status=plugin->callbacks->getDirectoryList(&directories)) == 0) {
        for (index=0; index<directories->count; index++) {
            if (!Prefs_FindPanel(directories->panels[index]) && data_00702f34)
                CLReportWarning(0x5d, directories->panels[index]);
        }
    }
    return 1;
}

Plugin *Plugin_New(struct PluginDataCallbacks *record36, PluginOptionalData *record24, PluginQueryTable *record8, const OSSpec *spec, void *module)
{
    PluginQueryTable *copy8;
    PluginQueryTable *source8 = record8;
    Plugin *copy = xmalloc(NULL, sizeof(Plugin));
    if (!copy) return NULL;
    if (!record36) return NULL;
    copy->callbacks = xmalloc(NULL, sizeof(struct PluginDataCallbacks));
    if (!copy->callbacks) return NULL;
    *copy->callbacks = *record36;
    if (record24) {
        copy->targetCallbacks = xmalloc(NULL, 24);
        if (!copy->targetCallbacks) return NULL;
        *(PluginOptionalData *)copy->targetCallbacks = *record24;
    } else copy->targetCallbacks = NULL;
    if (source8) {
        copy->queryCallbacks = xmalloc(NULL,8);
        if (!copy->queryCallbacks) return NULL;
        copy8 = copy->queryCallbacks;
        *copy8 = *source8;
    } else copy->queryCallbacks = NULL;
    if (spec) copy->spec = *spec;
    else copy->spec = data_00702d28;
    copy->module = module;
    copy->object = NULL;
    copy->cached_ascii_version = NULL;
    copy->next = NULL;
    return copy;
}

void Plugin_Free(Plugin *allocations)
{
    if (allocations) {
        xfree(allocations->callbacks);
        xfree(allocations->targetCallbacks);
        xfree(allocations->queryCallbacks);
        xfree(allocations->cached_ascii_version);
        if (allocations->module) fn_00412270(allocations->module);
        xfree(allocations);
    }
}

Boolean Plugin_VerifyPanels(Plugin *input)
{
    if (!VerifyPanels(input)) {
        CLReportError(0x5e, Plugin_GetDropInName(input));
        return 0;
    }
    return 1;
}

void Plugins_Init(void)
{
    pluginlist = NULL;
    GetToolVersionInfo();
}

void Plugins_Term(void)
{
    Plugin *p = pluginlist;
    while (p) {
        Plugin *next = p->next;
        fn_00425e20(p,0);
        Plugin_Free(p);
        p = next;
    }
    if (toolVersionInfo.company) xfree(toolVersionInfo.company);
    if (toolVersionInfo.product) xfree(toolVersionInfo.product);
    if (toolVersionInfo.tool) xfree(toolVersionInfo.tool);
    if (toolVersionInfo.copyright) xfree(toolVersionInfo.copyright);
    if (toolVersionInfo.version) xfree(toolVersionInfo.version);
}

int Plugins_Add(void *pluginHandle)
{
    Plugin *plugin = pluginHandle;
    char *name;
    const char *local;
    PluginDesc *desc;
    SInt32 lang;
    TargetInfo *ti;
    FileMapInfo *fm;
    PluginDirectoryList *pi;
    Plugin **slot;
    SInt16 i;

    name = Plugin_GetDropInName(plugin);
    Plugin_GetVersionInfoASCII(plugin);
    if (!SupportedPlugin(plugin, &local)) {
        CLReportError(0x58, name, plugin->cached_ascii_version, local);
        return 0;
    }
    slot = &pluginlist;
    while (*slot != NULL) {
        if (Plugin_MatchesName(*slot, name)) {
            CLReportError(0x5b, name);
            return 0;
        }
        slot = &(*slot)->next;
    }
    *slot = plugin;

    desc = Plugin_GetDropInFlags(plugin);
    if (((desc->flags & 1) == 0) && !(Boolean)fn_00425e20(plugin, 1)) {
        CLReportError(3, name);
        return 0;
    }
    if (desc->type == 0x436f6d70 && (desc->flags & 0x340000)) {
        CLReportError(4, "compiler", name);
    }
    if (desc->type == 0x4c696e6b && (desc->flags & 0x5824000)) {
        CLReportError(4, "linker", name);
    }

    if (data_00702f34) {
        lang = desc->lang;
        if (lang == 0)
            lang = 0x2d2d2d2d;
        CLPrint("Added plugin '%s', version '%s'\n", name, plugin->cached_ascii_version);
        CLPrint("Type: '%c%c%c%c';  Lang: '%c%c%c%c';  API range: %d-%d\n",
                                   (desc->type & 0xff000000) >> 24, (desc->type & 0xff0000) >> 16,
                                   (desc->type & 0xff00) >> 8, desc->type & 0xff, (lang & 0xff000000) >> 24,
                                   (lang & 0xff0000) >> 16, (lang & 0xff00) >> 8, lang & 0xff, desc->api1, desc->api2);

        if (plugin->targetCallbacks != NULL) {
            ti = Plugin_CL_GetTargetList(plugin);
            CLPrint("Target CPUs: ");
            for (i = 0; i < ti->ncpu; i++) {
                UInt32 v = ti->cpus[i];
                CLPrint("'%c%c%c%c', ", (v & 0xff000000) >> 24, (v & 0xff0000) >> 16,
                                           (v & 0xff00) >> 8, v & 0xff);
            }
            CLPrint("\nTarget OSes: ");
            for (i = 0; i < ti->nos; i++) {
                UInt32 v = ti->oses[i];
                CLPrint("'%c%c%c%c', ", (v & 0xff000000) >> 24, (v & 0xff0000) >> 16,
                                           (v & 0xff00) >> 8, v & 0xff);
            }
            CLPrint("\n");
            fm = Plugin_CL_GetExtMapList(plugin);
            CLPrint("File mappings:\n");
            for (i = 0; i < fm->count; i++) {
                if (fm->maps[i].type) CLPrint("\tFile type: '%c%c%c%c'  Extension: '%s'\n",
                                           (fm->maps[i].type & 0xff000000) >> 24, (fm->maps[i].type & 0xff0000) >> 16,
                                           (fm->maps[i].type & 0xff00) >> 8, fm->maps[i].type & 0xff, fm->maps[i].ext);
                else CLPrint("\tFile type: <none>  Extension: '%s'\n", fm->maps[i].ext);
            }
        }
        pi = Plugin_GetPanelList(plugin);
        CLPrint("Pref panels needed:\n");
        for (i = 0; i < pi->count; i++) {
            CLPrint("\t'%s'\n", pi->panels[i]);
        }
        CLPrint("Dropin flags:\n");
        if (desc->flags & 1) {
            CLPrint("\texecutable tool,\n");
        }
        if (desc->type == 0x436f6d70) {
            if (desc->flags & 0x80000000) CLPrint("\tgenerates code,\n");
            if (desc->flags & 0x40000000) CLPrint("\tgenerates resources, \n");
            if (desc->flags & 0x20000000) CLPrint("\tcan preprocess, \n");
            if (desc->flags & 0x10000000) CLPrint("\tcan precompile, \n");
            if (desc->flags & 0x8000000) CLPrint("\tis Pascal, \n");
            if (desc->flags & 0x4000000) CLPrint("\tcan import, \n");
            if (desc->flags & 0x2000000) CLPrint("\tcan disassemble, \n");
            if (desc->flags & 0x800000) CLPrint("\tallow duplicate filenames, \n");
            if (desc->flags & 0x400000) CLPrint("\tallow multiple targets, \n");
            if (desc->flags & 0x100000) CLPrint("\tuses target storage, \n");
            if (desc->flags & 0x80000) CLPrint("\temits own browser symbols, \n");
            if (desc->flags & 0x40000) CLPrint("\tshould be always reloaded, \n");
            if (desc->flags & 0x20000) CLPrint("\trequires project build started msg, \n");
            if (desc->flags & 0x10000) CLPrint("\trequires target build started msg, \n");
            if (desc->flags & 0x8000) CLPrint("\trequires subproject build started msg, \n");
            if (desc->flags & 0x4000) CLPrint("\trequires file list build started msg, \n");
            if (desc->flags & 0x2000) CLPrint("\tis reentrant, \n");
            if (desc->flags & 0x800) CLPrint("\trequires target compile started msg, \n");
            if (desc->flags & 0x400) CLPrint("\tsupports source-relative includes, \n");
            if (desc->flags & 0x200) CLPrint("\tsupports compiler querying, \n");
            if (desc->flags & 0x100) CLPrint("\thas placeholder support, \n");
            if (desc->flags & 0x80) CLPrint("\tsupports mmap'ed files, \n");
            if (desc->flags & 0x40) CLPrint("\trequires target link started msg, \n");
        }
        if (desc->type == 0x4c696e6b) {
            if (desc->flags & 0x80000000) CLPrint("\tcan't disassemble, \n");
            if (desc->flags & 0x40000000) CLPrint("\tis a post-linker, \n");
            if (desc->flags & 0x20000000) CLPrint("\tallow duplicate filenames, \n");
            if (desc->flags & 0x10000000) CLPrint("\tallow multiple targets, \n");
            if (desc->flags & 0x8000000) CLPrint("\tis a pre-linker, \n");
            if (desc->flags & 0x4000000) CLPrint("\tuses target storage, \n");
            if (desc->flags & 0x2000000) CLPrint("\tsupports unmangling, \n");
            if (desc->flags & 0x1000000) CLPrint("\tis Magic Cap linker, \n");
            if (desc->flags & 0x800000) CLPrint("\tshould be always reloaded, \n");
            if (desc->flags & 0x400000) CLPrint("\trequires project build started msg, \n");
            if (desc->flags & 0x200000) CLPrint("\trequires target build started msg, \n");
            if (desc->flags & 0x100000) CLPrint("\trequires subproject build started msg, \n");
            if (desc->flags & 0x80000) CLPrint("\trequires file list build started msg, \n");
            if (desc->flags & 0x40000) CLPrint("\trequires target link started msg, \n");
            if (desc->flags & 0x20000) CLPrint("\twants pre-run request, \n");
            if (desc->flags & 0x10000) CLPrint("\tcan get target info in thread-safe manner, \n");
            if (desc->flags & 0x8000) CLPrint("\tuses case-insensitive symbols, \n");
            if (desc->flags & 0x4000) CLPrint("\tneeds to preprocess before disassembling, \n");
            if (desc->flags & 0x2000) CLPrint("\tuses frameworks, \n");
            if (desc->flags & 0x1000) CLPrint("\tsuggests non-recursive access paths, \n");
            if (desc->flags & 0x800) CLPrint("\tuses package actions, \n");
        }
        CLPrint("\n");
    }
    return 1;
}

Plugin *Plugins_CL_MatchTarget(Plugin *node, SInt32 a, SInt32 b, SInt32 c, SInt32 d)
{
    Plugin *obj = node ? node : pluginlist;
    Plugin *result = NULL;

    while (obj != NULL) {
        if (obj->targetCallbacks != NULL && Plugin_CL_MatchesTarget(obj, a, b, 0) &&
            Plugin_MatchesType(obj, c, d, 0)) {
            result = obj;
            if (Plugin_CL_MatchesTarget(obj, a, b, 1) && Plugin_MatchesType(obj, c, d, 1))
                break;
        }
        obj = obj->next;
    }
    return result;
}

Plugin *Plugins_GetPluginForFile(Plugin *first, int selector, int optionKind, int optionValue,
                                                       int nameKind, char *name, int selectorValue)
{
    Plugin *candidate;
    Plugin *match;
    char nameMatch;

    candidate = first != NULL ? first : pluginlist;
    match = NULL;
    while (candidate != NULL) {
        if ((Plugin_MatchesType(candidate, selector, selectorValue, '\x01') != '\0') &&
            (candidate->targetCallbacks != NULL) &&
            (Plugin_CL_MatchesTarget(candidate, optionKind, optionValue, '\0') != '\0') &&
            ((nameMatch = Plugin_CL_MatchesFileType(candidate, nameKind, name, '\0')) != 0)) {
            match = candidate;
            if ((Plugin_CL_MatchesTarget(candidate, optionKind, optionValue, '\x01') != '\0') &&
                ((nameMatch = Plugin_CL_MatchesFileType(candidate, nameKind, name, '\x01')) != 0)) {
                if (!data_0070324d || strstr(Plugin_GetDisplayName(candidate), "Build Agent"))
                    break;
            }
        }
        candidate = candidate->next;
    }
    return match;
}

Plugin *Plugins_GetLinker(Plugin *start, int kind, int variant)
{
    Plugin *plugin;
    Plugin *candidate;
    PluginDesc *capabilities;

    plugin = start != NULL ? start : pluginlist;
    candidate = NULL;
    while (plugin != NULL) {
        if (Plugin_MatchesType(plugin, 0x4c696e6b, 0x2a2a2a2a, 1) != '\0' &&
            ((capabilities = Plugin_GetDropInFlags(plugin), (capabilities->flags & 0x48000000) == 0)) &&
            Plugin_CL_MatchesTarget(plugin, kind, variant, '\0') != '\0') {
            candidate = plugin;
            if (Plugin_CL_MatchesTarget(plugin, kind, variant, '\x01') != '\0') {
                break;
            }
        }
        plugin = plugin->next;
    }
    return candidate;
}

Plugin *Plugins_GetPreLinker(Plugin *plugins, unsigned int kind, unsigned int subtype)
{
    Plugin *plugin = plugins ? plugins : pluginlist;
    Plugin *result = NULL;
    while (plugin != NULL) {
        if (Plugin_MatchesType(plugin, 0x4c696e6bU, 0x2a2a2a2aU, 1U)) {
            if ((Plugin_GetDropInFlags(plugin)->flags & 0x8000000U) != 0U) {
                if (Plugin_CL_MatchesTarget(plugin, kind, subtype, 0U)) {
                    result = plugin;
                    if (Plugin_CL_MatchesTarget(plugin, kind, subtype, 1U))
                        break;
                }
            }
        }
        plugin = plugin->next;
    }
    return result;
}

Plugin *Plugins_GetPostLinker(Plugin *plugins, int kind, int selector)
{
    Plugin *plugin = plugins ? plugins : pluginlist;
    Plugin *match = NULL;
    while (plugin != NULL) {
        if (Plugin_MatchesType(plugin, 0x4c696e6b, 0x2a2a2a2a, 1) != '\0') {
            if ((Plugin_GetDropInFlags(plugin)->flags & 0x40000000) != 0) {
                if (Plugin_CL_MatchesTarget(plugin, kind, selector, 0) != '\0') {
                    match = plugin;
                    if (Plugin_CL_MatchesTarget(plugin, kind, selector, 1) != '\0')
                        break;
                }
            }
        }
        plugin = plugin->next;
    }
    return match;
}

Plugin *Plugins_GetParserForPlugin(Plugin *plugins, int selector, int request_count,
                                                  PluginRequest *requests, int option4, int option5, int value_count,
                                                  char **values)
{
    int request_index;
    UInt8 *results;
    int value_index;
    char **value;
    int failed_index;
    char matched;
    char all_succeeded;
    Plugin *plugin;
    Plugin *selected;
    plugin = plugins != NULL ? plugins : pluginlist;
    selected = NULL;
    results = __alloca(value_count);
    while (plugin != NULL) {
        if (Plugin_MatchesType(plugin, 1348563571, selector, 1) != 0) {
            request_index = 0;
            matched = 0;
            for (; request_index < request_count; request_index = request_index + 1) {
                if (requests[request_index].tag.signed_kind != 1348563571 &&
                    requests[request_index].tag.kind != 1668047986 && requests[request_index].flag_10 == 0 &&
                    Plugin_Pr_MatchesPlugin(plugin, &requests[request_index], option4, option5) != 0) {
                    matched = 1;
                }
            }
            if (matched != 0) {
                selected = plugin;
                value_index = 0;
                all_succeeded = 1;
                if (value_count > 0) {
                    value = values;
                    do {
                        results[value_index] = Plugin_Pr_MatchesPanels(plugin, 1, value);
                        value = value + 1;
                        all_succeeded &= results[value_index];
                        value_index = value_index + 1;
                    } while (value_index < value_count);
                }
                if (all_succeeded != 0) {
                    break;
                }
            }
        }
        plugin = plugin->next;
    }
    if (selected != NULL && all_succeeded == 0) {
        CLReport(5);
        failed_index = 0;
        for (; failed_index < value_count; failed_index = failed_index + 1) {
            if (results[failed_index] == 0) {
                CLReport(6, values[failed_index]);
            }
        }
    }
    return selected;
}

int Plugins_GetPluginList(Plugin *list, SInt32 *count, PluginRequest **out)
{
    Plugin *node;
    PluginDesc *info;
    VersionInfo *name;
    SInt32 itemCount;
    SInt32 index;

    node = list ? list : pluginlist;
    itemCount = 0;
    while (node != NULL) {
        itemCount++;
        node = node->next;
    }
    *count = itemCount;
    *out = xmalloc(NULL, itemCount * sizeof(PluginRequest));
    if (*out == NULL)
        return 0;

    node = list ? list : pluginlist;
    index = 0;
    while (node != NULL) {
        info = (PluginDesc *)Plugin_GetDropInFlags(node);
        name = Plugin_GetVersionInfo(node);
        if (info == NULL)
            OS_ASSERT_AT("df != NULL", "CLPlugins.c", 0x5f2);
        if (name == NULL)
            OS_ASSERT_AT("vi != NULL", "CLPlugins.c", 0x5f3);
        (*out)[index].tag.signed_kind = info->type;
        (*out)[index].secondCode = info->lang;
        (*out)[index].flags = info->flags;
        (*out)[index].name = (unsigned int)node->cached_ascii_version;
        (*out)[index].flag_10 = (info->flags & 1) != 0;
        index++;
        node = node->next;
    }
    return 1;
}

static inline SInt32 CountPluginNames(Plugin *list)
{
    Plugin *p;
    PluginDirectoryList *s;
    SInt32 total;

    p = list ? list : pluginlist;
    total = 0;
    for (; p != NULL; p = p->next) {
        s = Plugin_GetPanelList(p);
        total += s->count;
    }
    return total;
}

int Plugins_GetPrefPanelUnion(Plugin *nameList, SInt32 *nameCount, char ***nameArray)
{
    char **array;
    PluginDirectoryList *resolvedList;
    Plugin *list;
    SInt32 count;
    SInt32 nameIndex;
    SInt32 existingIndex;

    array = xmalloc("plugin preference union", CountPluginNames(nameList) << 2);

    count = 0;
    list = nameList ? nameList : pluginlist;

    for (; list != NULL; list = list->next) {
        resolvedList = Plugin_GetPanelList(list);
        for (nameIndex = 0; nameIndex < resolvedList->count; nameIndex++) {
            existingIndex = 0;
            if (0 < count) {
                do {
                    if (ustrcmp(array[existingIndex], resolvedList->panels[nameIndex]) == 0)
                        break;
                    existingIndex++;
                } while (existingIndex < count);
            }
            if (existingIndex >= count) {
                array[count] = resolvedList->panels[nameIndex];
                count++;
            }
        }
    }

    *nameArray = xrealloc("plugin preference union", array, count << 2);
    *nameCount = count;
    return 1;
}

int Plugin_AddFileTypeMappings(Plugin *plugin, SInt32 refCon)
{
    unsigned int fileTypesTable;

    fileTypesTable = Plugin_GetFileTypeMappingList(plugin);
    if (fileTypesTable == 0) {
        return 1;
    }
    OS_AddFileTypeMappingList(NULL, fileTypesTable);
    return 1;
}

int Plugins_AddFileTypeMappingsForTarget(Plugin *node, SInt32 argument, SInt32 firstIdentifier, SInt32 secondIdentifier)
{
    if (node == NULL) {
        node = pluginlist;
    }
    while (node != NULL) {
        if ((node->targetCallbacks == NULL) ||
            (Plugin_CL_MatchesTarget(node, firstIdentifier, secondIdentifier, 0) != 0)) {
            Plugin_AddFileTypeMappings(node, argument);
        }
        node = node->next;
    }
    return 1;
}

short Plugin_Call(Plugin *dispatch, CWPluginPrivateContext *argument)
{
    if (dispatch->callbacks->entry != NULL) {
        return dispatch->callbacks->entry((unsigned int)argument);
    }
    return 2;
}

static char *Plugin_GetDisplayName(Plugin *plugin)
{
    int result;
    char *name;
    ToolVersionInfo *tvi;
    int status;
    if (!plugin) OS_ASSERT_AT("pl","CLPlugins.c",0x101);
    if (plugin->callbacks->getToolVersionInfo && (status=plugin->callbacks->getToolVersionInfo(&tvi))==0 && tvi->tool)
        return tvi->tool;
    if (plugin->callbacks->getDisplayName) {
        result=plugin->callbacks->getDisplayName(&name);
        if (!result) return name;
    }
    return "(no name found)";
}
ToolVersionInfo *fn_00415170(Plugin *plugin)
{
    ToolVersionInfo *tvi;
    int status;
    if (!plugin) OS_ASSERT_AT("pl","CLPlugins.c",0x139);
    if (plugin->callbacks->getToolVersionInfo && (status=plugin->callbacks->getToolVersionInfo(&tvi))==0 && tvi->version==2)
        return tvi;
    return &data_006d6168;
}
static char *fn_004151d0(unsigned int major,unsigned int minor,unsigned int patch,unsigned int build)
{
    char vernum[64];
    char *bptr=vernum;
    char *buffer;
    bptr += snprintf(bptr,64,"%u",major);
    bptr += snprintf(bptr,64-(bptr-vernum),".%u",minor);
    if (patch) bptr += snprintf(bptr,64-(bptr-vernum),".%u",patch);
    if (build) snprintf(bptr,64-(bptr-vernum)," build %u",build);
    buffer=xmalloc("version info",64);
    snprintf(buffer,64,"Version %s",vernum);
    return buffer;
}
char *Plugin_GetVersionInfoASCII(Plugin *plugin)
{
    ToolVersionInfo *tvi;
    VersionInfo *vi;
    char *text;
    if (!plugin && useToolVersion)
        return fn_004151d0(toolVersion.major,toolVersion.minor,toolVersion.patch,toolVersion.build);
    if (!plugin) return NULL;
    if (plugin->cached_ascii_version) return plugin->cached_ascii_version;
    tvi=fn_00415170(plugin);
    vi=Plugin_GetVersionInfo(plugin);
    if (tvi && (text=tvi->versionASCII)!=NULL && strchr(text,'.')) {
        plugin->cached_ascii_version=xstrdup(text);
        return plugin->cached_ascii_version;
    }
    if (tvi && (tvi->number.major | tvi->number.minor | tvi->number.patch | tvi->number.build!=0))
        plugin->cached_ascii_version=fn_004151d0(tvi->number.major,tvi->number.minor,tvi->number.patch,tvi->number.build);
    else if (vi->major | vi->minor | vi->patch | vi->build!=0)
        plugin->cached_ascii_version=fn_004151d0(vi->major,vi->minor,vi->patch,vi->build);
    else return NULL;
    return plugin->cached_ascii_version;
}
Plugin *Plugins_GetDisassembler(Plugin *plugins,int kind,int selector)
{
    Plugin *plugin=plugins ? plugins : pluginlist;
    Plugin *match=NULL;
    while (plugin) {
        if (Plugin_MatchesType(plugin,0x4c696e6b,0x2a2a2a2a,1) &&
            !(Plugin_GetDropInFlags(plugin)->flags & 0x80000000) &&
            Plugin_CL_MatchesTarget(plugin,kind,selector,0)) {
            match=plugin;
            if (Plugin_CL_MatchesTarget(plugin,kind,selector,1)) break;
        }
        plugin=plugin->next;
    }
    return match;
}
int fn_00417220(int (*callback)(Plugin *,void *),void *refCon)
{
    Plugin *p=pluginlist;
    int result;
    while (p) {
        result=callback(p,refCon);
        if (result) return result;
        p=p->next;
    }
    return 0;
}

extern char *__stdcall OS_SpecToString(const OSSpec *,char *,int);
extern unsigned int __stdcall GetFileVersionInfoSizeA(const char *,unsigned int *);
extern int __stdcall GetFileVersionInfoA(const char *,unsigned int,unsigned int,void *);
extern int __stdcall VerQueryValueA(const void *,const char *,void **,unsigned int *);
static void GetToolVersionInfo(void)
{
    char filename[260];
    unsigned int ignored, size, querySize;
    unsigned int *fixed;
    void *data;
    char *text,*scan,*out;
    unsigned int i,length;
    char formatted[80];
    useToolVersion=0;
    OS_SpecToString(&data_00702d28,filename,260);
    size=GetFileVersionInfoSizeA(filename,&ignored);
    if (!size) return;
    data=__alloca(size);
    if (!GetFileVersionInfoA(filename,ignored,size,data)) return;
    if (!VerQueryValueA(data,"\\",(void **)&fixed,&querySize)) return;
    useToolVersion=1;
    toolVersion.major=fixed[2]>>16;
    toolVersion.minor=fixed[2];
    toolVersion.patch=fixed[3]>>16;
    toolVersion.build=fixed[3];
    if (VerQueryValueA(data,"\\StringFileInfo\\040904B0\\CompanyName",(void **)&text,&querySize))
        toolVersionInfo.company=xstrdup(text);
    else toolVersionInfo.company=NULL;
    if (VerQueryValueA(data,"\\StringFileInfo\\040904B0\\ProductName",(void **)&text,&querySize))
        toolVersionInfo.product=xstrdup(text);
    else toolVersionInfo.product=NULL;
    if (VerQueryValueA(data,"\\StringFileInfo\\040904B0\\FileDescription",(void **)&text,&querySize))
        toolVersionInfo.tool=xstrdup(text);
    else toolVersionInfo.tool=NULL;
    if (VerQueryValueA(data,"\\StringFileInfo\\040904B0\\LegalCopyright",(void **)&text,&querySize)) {
        length=0;
        for (i=0;text[i];i++) length += (UInt8)text[i]==0xa9 ? 3 : 1;
        toolVersionInfo.copyright=xmalloc(NULL,length+1);
        out=toolVersionInfo.copyright;
        for (i=0;text[i];i++) {
            if ((UInt8)text[i]==0xa9) { *out++='(';*out++='c';*out++=')'; }
            else *out++=text[i];
        }
        *out=0;
    } else toolVersionInfo.copyright=NULL;
    if (VerQueryValueA(data,"\\StringFileInfo\\040904B0\\ProductVersion",(void **)&text,&querySize)) {
        scan=text;
        while ((*scan>='0'&&*scan<='9')||*scan=='.'||*scan==' ') scan++;
        if (scan>text+2 && *scan)
            snprintf(formatted,80,"%s (%s)",Plugin_GetVersionInfoASCII(NULL),scan);
        else snprintf(formatted,80,"%s",Plugin_GetVersionInfoASCII(NULL));
        toolVersionInfo.version=xstrdup(formatted);
    } else toolVersionInfo.version=xstrdup("Version %%s");
}
void *Plugin_GetToolVersionInfo(void)
{
    return useToolVersion ? &toolVersionInfo : NULL;
}
