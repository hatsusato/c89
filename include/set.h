#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "compare/types.h"
#include "set/types.h"
#include "utility/types.h"

Set *set_new(Destructor, Compare *);
void set_delete(Set *);
void set_clear(Set *);
void set_insert(Set *, ElemType);
Bool set_contains(const Set *, ElemType);
const ElemType *set_find(const Set *, ElemType);
const ElemType *set_begin(const Set *);
const ElemType *set_end(const Set *);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
