#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "typedef.h"
#include "utility.h"

Set *set_new(SetCompare);
void set_delete(Set *);
void set_insert(Set *, SetElem);
Bool set_contains(const Set *, SetElem);
const SetElem *set_find(const Set *, SetElem);
const SetElem *set_begin(const Set *);
const SetElem *set_end(const Set *);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
