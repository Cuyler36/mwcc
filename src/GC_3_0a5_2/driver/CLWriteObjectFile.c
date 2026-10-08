#define CERROR_FILE "CLWriteObjectFile.c"
#include "compiler/common.h"
#include "driver/CLWriteObjectFile.h"
#include "GC_3_0a5_2/driver/CLBrowser.h"
#include "driver/CLDropinCallbacks_V10.h"
#include "driver/CLErrors.h"
#include "driver/CLFileOps.h"
#include "driver/CLIO.h"
#include "driver/CLPlugins.h"
#include "driver/CLProj.h"
#include "driver/Files.h"
#include "driver/Memory.h"

/* GC 3.0 File field names come from the symbol map. Windows embeds its
 * 516-byte native OSSpec directly; the older driver record is a different ABI. */
#pragma pack(push, 1)
typedef struct WriterOSSpec {
    char path[0x104];
    char name[0x100];
} WriterOSSpec;
typedef struct WriterFile {
    unsigned char reserved000[0x21f];
    WriterOSSpec srcfss;
    WriterOSSpec outfss;
    unsigned char reserved627[5];
    short tempOnDisk;
    unsigned char reserved62e[2];
    Plugin *compiler;
    unsigned char reserved634[0x14];
    StorageHandle *objectdata;
    StorageHandle *browsedata;
} WriterFile;
#pragma pack(pop)

int WriteObjectFile(struct DropinFileRecord *input, unsigned int maccreator, unsigned int mactype)
{
    WriterFile *file = (WriterFile *)input;
    char *result;
    unsigned char *message;
    UInt8 success;

    if (!(file->objectdata && file->compiler))
        OS_ASSERT_AT("file->objectdata && file->compiler", "CLWriteObjectFile.c", 0x16);
    if (DAT_00541b28) {
        message = (file->tempOnDisk & 2) ? temporary_output_message : browse_file_message;
        result = CLProj_MakeRelativePath((OSSpec *)&file->outfss, NULL, data_005880e0, 0x104);
        CLErrors_ForwardMessage(0x10, message, result);
    }
    success = CLPlugins_WriteObjectFile(file->compiler, (CWFileSpec *)&file->srcfss,
                                        (CWFileSpec *)&file->outfss, maccreator, mactype,
                                        (int)file->objectdata);
    if (!success)
        return 0;
    return 1;
}

int WriteBrowseData(DropinFileRecord *input, unsigned int maccreator, unsigned int mactype)
{
    WriterFile *filedata = (WriterFile *)input;
    MemBuffer browsehandle;
    WriterOSSpec outfss;
    OutputSuffixes *cof;
    char *extension;

    cof = CLPlugins_GetObjectFlags(filedata->compiler);
    outfss = filedata->outfss;
    if (data_00541b95[0])
        extension = data_00541b95;
    else
        extension = cof->suffix0;
    CLProj_ChangeFileExtension(outfss.name, extension);
    if (DAT_00541b28) {
        char *result = CLProj_MakeRelativePath((OSSpec *)&outfss, NULL, data_005880e0, 260);
        CLErrors_ForwardMessage(17, result);
    }
    if (!Browser_PackBrowseFile(filedata->browsedata, &data_00587570, &browsehandle))
        return 0;
    if (!fn_00415090((OSSpec *)&outfss, maccreator, mactype, &browsehandle))
        return 0;
    return 1;
}
