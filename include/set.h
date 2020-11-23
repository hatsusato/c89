#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "types.h"

struct struct_Set;
typedef struct struct_Set Set;
typedef int (*Compare)(const ElemType *, const ElemType *);

Set *set_new(Compare);
void set_delete(Set *);
ElemType set_insert(Set *, ElemType);
Bool set_contains(const Set *, ElemType);
const ElemType *set_find(const Set *, ElemType);
const ElemType *set_begin(const Set *);
const ElemType *set_end(const Set *);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
