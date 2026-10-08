#define CERROR_FILE "CLProj.c"
#include "compiler/common.h"
#include "driver/OSAssert.h"

typedef struct ProjOSSpec { char path[260]; char name[256]; } ProjOSSpec;
typedef struct Project { void *targets; ProjOSSpec projectfile; } Project;
extern int __stdcall OS_MakeFileSpec(const char *, ProjOSSpec *);
extern void Targets_Term(void *);
#pragma auto_inline off

Boolean Proj_Initialize(Project *proj)
{
    proj->targets = NULL;
    OS_MakeFileSpec("Project.mcp", &proj->projectfile);
    return 1;
}

Boolean Proj_Terminate(Project *proj)
{
    if (!proj)
        OS_ASSERT_AT("this != NULL", "CLProj.c", 0x18);
    Targets_Term(proj->targets);
    return 1;
}
