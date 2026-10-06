#ifndef DRIVER_DROPINCOMPILERLINKERPRIVATE_H
#define DRIVER_DROPINCOMPILERLINKERPRIVATE_H

#include "compiler/common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char has_valid_shell_signature(CWPluginPrivateContext *object);
extern int __stdcall fn_0041bcb0(CWPluginPrivateContext *object, struct StorageHandle *argument2, long *argument3);
extern unsigned int __stdcall dispatch_request_callback(CWPluginPrivateContext *object, unsigned int argument2,
                                                        void *argument3);
extern int __stdcall DropInCompilerLinkerPrivate_CallArgumentValue(CWPluginPrivateContext *context,
                                                                   const char *argument, void *value);

#ifdef __cplusplus
}
#endif

#endif
