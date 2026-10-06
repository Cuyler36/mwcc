#ifndef MSL_STARTUP_WIN32_H
#define MSL_STARTUP_WIN32_H

#include "compiler/win32.h"

#pragma pack(push, 1)
struct CFileRec {
    HANDLE handle;
    Boolean readonly;
    Boolean textmode;
    UInt8 trailingPadding[2]; /* 0x06: startup_win32.h CFileRec; two unused bytes following textmode */
};
typedef struct CFileRec CFileRec;
#pragma pack(pop)
struct EnvironmentBlock {
    char *strings;
};
typedef struct EnvironmentBlock EnvironmentBlock;
#pragma pack(push, 1)
struct ThreadLocalData {
    unsigned int initialValue;
    unsigned int secondaryValue;
    unsigned char *sharedData;
    unsigned char *secondarySharedData;
    unsigned int argument;
};
typedef struct ThreadLocalData ThreadLocalData;
#pragma pack(pop)
extern int data_0057d010[];
extern struct EnvironmentBlock data_0057d014;
extern struct CFileRec *_HandleTable[256];
extern struct CFileRec *data_0058476c;
extern struct CFileRec *data_00584770;
extern struct EnvironmentBlock *data_00587170;
extern char **_Environ;
extern LPCSTR PTR_s_Could_not_get_thread_local_data_00536250;
extern int *fn_00401de0(void);
extern int _CRTStartup(void);
extern int allocate_tls_index(void);
extern DWORD DAT_00536228;
extern void free_tls_index(void);
extern BOOL __cdecl initialize_thread_local_data(unsigned int argument);
extern unsigned char DAT_0053622c[];
extern int _InitializeMainThreadData(void);
extern SInt32 *_GetThreadLocalData(void);

#endif
