#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "utility.h"

struct struct_Set;
typedef struct struct_Set Set;
typedef const void *SetElem;
typedef int (*SetCompare)(const SetElem *, const SetElem *);

Set *set_new(SetCompare);
void set_delete(Set *);
void set_insert(Set *, SetElem);
Bool set_contains(const Set *, SetElem);
const SetElem *set_find(const Set *, SetElem);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
