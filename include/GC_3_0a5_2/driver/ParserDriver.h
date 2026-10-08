#ifndef GC3_PARSERDRIVER_H
#define GC3_PARSERDRIVER_H

/* Reuse the baseline ABI records while restoring symbol-map function names. */
#include "driver/Targets.h"

extern void CLPReportError_V(char *message, char *arguments);
extern void CLPReportWarning_V(char *a0, char *a1);
extern void CLPReport_V(char *first, char *second);
extern void CLPStatus_V(char *message, unsigned int *arguments);
extern void CLPAlert_V(const char *text, va_list position);
extern void CLPOSAlert_V(char *name, DWORD value, unsigned int *result);
extern char *CLPGetErrorString(SInt32 argument, char *buffer);
extern void CLPReport(int argument, ...);
extern unsigned char CLPOSAlert(int id, short code, ...);
extern void CLPStatus(int s, ...);
extern void CLPFatalError(const char *fmt, ...);
extern void Arg_AddToken(short kind, char *text);
extern void Arg_Setup(unsigned int value, char **otherValue);
extern void Arg_SkipRespFileWS(void);
extern Boolean Arg_OpenRespFile(char *name);
extern unsigned int Arg_CloseRespFile(void);
extern char *Arg_GetRespFileToken(void);
extern unsigned char Arg_GotMore(void);
extern void Arg_Reset(void);
extern unsigned int Arg_PeekToken(void);
extern TokenText *Arg_UsedToken(void);
extern int Arg_IsEmpty(void);
extern int Arg_GetToken(void);
extern TokenText *Arg_UndoToken(void);
extern char *Arg_GetTokenName(TokenText *token);
extern void Arg_GrowArgs(PtrList *list);
extern void Arg_AddToToolArgs(PtrList *list, short kind, char *text);
extern void Arg_FinishToolArgs(PtrList *list);
extern void Arg_ToolArgsForPlugin(PtrList *source, IntegerSequenceResult *result);
extern void Arg_InitToolArgs(PtrList *state);
extern void CLPReportError(SInt32 a, ...);
extern void CLPReportWarning(int a, ...);
extern char *Arg_GetNext(Boolean expand);
extern void Arg_Parse(void);
extern void Arg_Init(int argc, char **argv);
extern void Arg_Terminate(void);
extern char *Arg_GetTokenText(TokenText *arg, char *buffer, int maxlen, Boolean warn);
extern void Arg_GrowArg(struct PtrList *list, char *text);

#endif
