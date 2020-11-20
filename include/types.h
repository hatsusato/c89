#ifndef INCLUDE_GUARD_ADFC65B2_9360_4BBE_84CD_607E1F3D622C
#define INCLUDE_GUARD_ADFC65B2_9360_4BBE_84CD_607E1F3D622C

#include <stddef.h>

#define true (1)
#define false (0)
typedef int Bool;
typedef unsigned char Byte;
typedef unsigned long PointerBytes;
typedef int Size;
typedef int Index;

typedef const void *ElemType;
typedef int (*Compare)(const ElemType *, const ElemType *);
typedef void (*Destructor)(ElemType);
typedef void (*ForeachMap)(ElemType, void *);

#endif /* INCLUDE_GUARD_ADFC65B2_9360_4BBE_84CD_607E1F3D622C */
