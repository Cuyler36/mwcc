/* Source and function names recovered from mwccppc_pro8_syms. */
#define CERROR_FILE "Targets.c"
#include "compiler/common.h"
#include "driver/OSAssert.h"

typedef struct ParserTool {
    UInt32 TYPE, LANG, CPU, OS;
    int numPrefPanels;
    char **prefPanels;
    char *toolInfo;
    char *copyright;
    int numOptionLists;
    OptionList **optionLists;
    int numPrefDataPanels;
    void *prefDataPanels;
    void (*PreParse)(void);
    void (*MidParse)(void);
    void (*PostParse)(void);
} ParserTool;

extern ParserTool *pTool;
/* Only the prefix needed here; toolVersion is at byte 80 in the symbols. */
typedef struct ParseOptsPrefix {
    char prefix[80];
    void *toolVersion;
} ParseOptsPrefix;
extern ParseOptsPrefix parseopts;
extern void CLPFatalError(char *, ...);
extern int __stdcall CLIO_CompareStringsIgnoreCase(char *, char *);
extern void Options_Init(void);
extern void Options_AddList(OptionList *);
extern void Options_SortOptions(void);

int SetParserToolInfo(ParserTool *tool)
{
    pTool = tool;
    OS_ASSERT(16, pTool->toolInfo && (parseopts.toolVersion || pTool->copyright));
    return 1;
}

#define MATCH(x, y) ((x) == 0x2a2a2a2a || (y) == 0x2a2a2a2a || (y) == (x))

Boolean ParserToolMatchesPlugin(UInt32 type, UInt32 lang, UInt32 cpu, UInt32 os)
{
    if (!pTool) {
        CLPFatalError("No options loaded for command line\n");
    }
    else if (MATCH(type, pTool->TYPE)
        && (MATCH(lang, pTool->LANG) || lang == 0x3f3f3f3f || pTool->LANG == 0x3f3f3f3f)
        && MATCH(cpu, pTool->CPU) && MATCH(os, pTool->OS))
        return 1;
    return 0;
}

Boolean ParserToolHandlesPanels(int numPanels, char **panelNames)
{
    int i, j;
    Boolean ok;
    if (!pTool)
        CLPFatalError("No options loaded for command line\n");
    for (i = 0; i < numPanels; i++) {
        for (j = 0; j < pTool->numPrefPanels; j++) {
            if (CLIO_CompareStringsIgnoreCase(pTool->prefPanels[j], panelNames[i]) == 0)
                break;
        }
        if (j >= pTool->numPrefPanels)
            break;
    }
    if (i >= numPanels)
        ok = 1;
    else
        ok = 0;
    return ok;
}

Boolean SetupParserToolOptions(void)
{
    int idx;
    Options_Init();
    for (idx = 0; idx < pTool->numOptionLists; idx++)
        Options_AddList(pTool->optionLists[idx]);
    Options_SortOptions();
    return 1;
}
