#ifndef INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A
#define INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A

#include "utility/types.h"

typedef struct {
  ElemType key, val;
} Pair;

Pair *pair_new(ElemType, ElemType);
void pair_delete(ElemType);
Compare *pair_new_compare(Compare *);
Pair pair_dummy(ElemType);
ElemType pair_key(Pair *);
ElemType *pair_val(Pair *);

#endif /* INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A */
