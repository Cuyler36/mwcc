#ifndef DRIVER_CLWRITEOBJECTFILE_H
#define DRIVER_CLWRITEOBJECTFILE_H

#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char temporary_output_message[];
extern unsigned char browse_file_message[];
extern UInt32 CLWriteObjectFile_WriteObjectFile(struct DropinFileRecord *self, unsigned int option1,
                                                unsigned int option2);

#ifdef __cplusplus
}
#endif

#endif
