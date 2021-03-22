#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "utility/types.h"
#include "vector/typedef.h"

Set *set_new(VectorDestructor, VectorCmp);
void set_delete(Set *);
void set_clear(Set *);
void set_insert(Set *, VectorCmpElem);
VectorCmpElem set_find(const Set *, VectorCmpElem);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
