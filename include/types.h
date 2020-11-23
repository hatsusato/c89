#ifndef INCLUDE_GUARD_ADFC65B2_9360_4BBE_84CD_607E1F3D622C
#define INCLUDE_GUARD_ADFC65B2_9360_4BBE_84CD_607E1F3D622C

#include <stddef.h>

#define true (1)
#define false (0)
typedef int Bool, Size, Index;
typedef unsigned char Byte;

typedef void *ElemType;
typedef void (*Destructor)(ElemType);
typedef int (*Cmp)(const ElemType *, const ElemType *);

#endif /* INCLUDE_GUARD_ADFC65B2_9360_4BBE_84CD_607E1F3D622C */
