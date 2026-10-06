#include "compiler/common.h"
#include "driver/LicenseImports.h"
#include "driver/CLLicenses.h"
__declspec(naked) int fn_004270ba(struct MWInfo *info, int version, int request, int options, int flag, char *path,
                                  int *handle)
{
    asm
    {
        jmp [data_0057a224]
    }
}

__declspec(naked) void fn_004270c0(int licenseHandle)
{
    __asm {
        jmp data_0057a228
    }
}

__declspec(naked) char *fn_004270c6(int handle)
{
    asm
    {
        jmp     data_0057a22c
    }
}
