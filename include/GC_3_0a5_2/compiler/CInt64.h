#ifndef GC3_COMPILER_CINT64_H
#define GC3_COMPILER_CINT64_H

#include "compiler/CInt64.h"

/* This TU implements the canonical GC3 names, rather than the import alias. */
#undef CInt64_Inv

#ifdef __cplusplus
extern "C" {
#endif

extern CInt64 CInt64_Neg(CInt64 value);
extern CInt64 CInt64_Inv(CInt64 value);
extern CInt64 CInt64_Not(CInt64 value);

#ifdef __cplusplus
}
#endif

#endif
