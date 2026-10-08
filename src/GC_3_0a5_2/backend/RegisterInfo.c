/* RegisterInfo.c Windows layout; remaining members are still being ported. */
#include "compiler/common.h"
#pragma pack(push, 2)
typedef struct NativeObject {
    UInt8 unknown_00[2];
    UInt8 datatype;
    UInt8 unknown_03[0x3d];
    void *localInfo;
    UInt8 unknown_44[0x10];
    void *dataInfo;
} NativeObject;
#pragma pack(pop)
extern void *galloc(SInt32);
extern void memclrw(void *, SInt32);
extern void CError_Internal(const char *, int);

void *Registers_GetVarInfo(NativeObject *object)
{
    void *info;
    switch (object->datatype) {
        case 0:
            if (!object->dataInfo) {
                info = galloc(20);
                memclrw(info, 20);
                object->dataInfo = info;
            }
            return object->dataInfo;
        case 1:
            if (!object->localInfo)
                CError_Internal("RegisterInfo.c", 649);
            return object->localInfo;
        case 2:
            if (!object->dataInfo) {
                info = galloc(20);
                memclrw(info, 20);
                object->dataInfo = info;
            }
            return object->dataInfo;
        default:
            CError_Internal("RegisterInfo.c", 662);
            return 0;
    }
}
