#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "compare/typedef.h"
#include "utility/types.h"
#include "vector/typedef.h"

Set *set_new(VectorDestructor, Compare *);
void set_delete(Set *);
void set_clear(Set *);
void set_insert(Set *, CompareElem);
CompareElem set_find(const Set *, CompareElem);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
