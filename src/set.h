#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "utility.h"

struct struct_Set;
typedef struct struct_Set Set;
typedef int (*SetCompare)(const void *, const void *);

Set *set_new(SetCompare);
void set_delete(Set *);
void set_insert(Set *, const void *);
Bool set_contains(Set *, const void *);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
