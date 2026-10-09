#include "compiler/common.h"
#include <string.h>
#include <stddef.h>
/* Native dump-control family, using original Mac roles and supplied SetupDump name. */
typedef struct DumpObjectPrefix { UInt8 unknown00[12]; void *name; } DumpObjectPrefix;
typedef char *DumpArguments;
typedef char DumpObjectNameOffset[offsetof(DumpObjectPrefix,name)==12?1:-1];
static char dumpMode[]="wt";
static char dumpSuffix[]=".log";
static char dumpAfter[]="Dumping function %s after %s (tick %u)\n";
static char dumpSeparator[]="--------------------------------------------------------------------------------\n";
static char optimizeAfter[]="Optimizing function %s after %s (tick %u)\n";
static char dumpInitCode[]="Init-code";
static char dumpBefore[]="Dumping function %s before %s (tick %u)\n";
static char optimizeBefore[]="Optimizing function %s before %s (tick %u)\n";
UInt32 dumpStartTicks;
void *dumpOutput;
extern UInt8 dumpEnabled,dumpForce;
extern DumpObjectPrefix *dumpCurrentObject;
extern char dumpSourcePath[];
extern void (*dumpPathCallback)(char *,UInt32);
extern void fn_0044dea0(char *,const char *,void *);
extern SInt32 fn_0040f2b0(void *);
extern void *fn_0040f3b0(const char *,const char *);
extern SInt32 fn_00407ed0(void *,const char *,DumpArguments);
extern UInt32 CompilerTools_GetScaledTicks(void);
extern void fn_005bd8e0(void);

/* Predicate result is a byte in native AL. */
UInt8 IRO_Dumping(void)
{
    return dumpEnabled!=0&&dumpOutput!=NULL;
}

void IRO_FlushDump(void)
{
    fn_0040f2b0(dumpOutput);
}

void IRO_Dump(const char *format,...)
{
    DumpArguments arguments;
    if(!dumpEnabled)return;
    arguments=(DumpArguments)&format+(((DumpArguments)(&format+1)-(DumpArguments)&format+3)/4)*4;
    fn_00407ed0(dumpOutput,format,arguments);
}

/* Suffix capacity uses the length before extension removal, as in native code. */
void IRO_SetupDump(void)
{
    char path[256];
    SInt32 length,i;
    if(dumpEnabled){
        if(dumpPathCallback)dumpPathCallback(path,256);
        else{
            fn_0044dea0(path,dumpSourcePath,NULL);
            length=strlen(path);
            for(i=length;i>=0;i--){
                char ch=path[i];
                if(ch=='/'||ch=='\\')break;
                if(ch=='.'){path[i]=0;break;}
            }
            strncat(path,dumpSuffix,255-length);
        }
        dumpOutput=fn_0040f3b0(path,dumpMode);
        if(!dumpOutput)dumpEnabled=0;
    }
}

void fn_005ed5d0(void)
{
    dumpStartTicks=CompilerTools_GetScaledTicks();
}

void IRO_DumpAfterPhase(const char *phase,UInt8 enabled)
{
    char *name;
    if(enabled||dumpForce){
        name=dumpCurrentObject?(char *)dumpCurrentObject->name+10:dumpInitCode;
        IRO_Dump(dumpAfter,name,phase,CompilerTools_GetScaledTicks()-dumpStartTicks);
        IRO_Dump(dumpSeparator);
        fn_005bd8e0();
    }else{
        name=dumpCurrentObject?(char *)dumpCurrentObject->name+10:dumpInitCode;
        IRO_Dump(optimizeAfter,name,phase,CompilerTools_GetScaledTicks()-dumpStartTicks);
    }
}

void IRO_DumpBeforePhase(const char *phase,UInt8 enabled)
{
    char *name;
    if(enabled||dumpForce){
        name=dumpCurrentObject?(char *)dumpCurrentObject->name+10:dumpInitCode;
        IRO_Dump(dumpBefore,name,phase,CompilerTools_GetScaledTicks()-dumpStartTicks);
        IRO_Dump(dumpSeparator);
        fn_005bd8e0();
    }else{
        name=dumpCurrentObject?(char *)dumpCurrentObject->name+10:dumpInitCode;
        IRO_Dump(optimizeBefore,name,phase,CompilerTools_GetScaledTicks()-dumpStartTicks);
    }
}
