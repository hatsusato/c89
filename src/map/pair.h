#ifndef INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A
#define INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A

#include "compare/typedef.h"
#include "utility/types.h"

typedef struct {
  CompareElem key, val;
} Pair;

Pair *pair_new(CompareElem, CompareElem);
void pair_delete(Pair *);
Compare *pair_new_compare(Compare *);
Pair pair_dummy(CompareElem);
CompareElem pair_key(const Pair *);
CompareElem *pair_val(Pair *);

#endif /* INCLUDE_GUARD_D1BC44FE_A7CB_4AB4_BBC6_18413DF0CB4A */
