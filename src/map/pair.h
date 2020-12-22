#ifndef INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A
#define INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A

#include "compare/type.h"
#include "types.h"

typedef struct {
  ElemType key, val;
} Pair;

int pair_compare(ElemType, ElemType, CompareExtra);
Pair *pair_new(ElemType, ElemType);
void pair_delete(ElemType);
Pair pair_dummy(ElemType);
ElemType *pair_val(Pair *);

#endif /* INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A */
