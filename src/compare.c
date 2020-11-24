#include "compare.h"

#include "utility.h"

struct struct_Compare {
  Cmp cmp;
  CompareExtra extra;
};
typedef struct struct_Compare MutableCompare;

MutableCompare *compare_as_mut(Compare *cmp) {
  return (MutableCompare *)cmp;
}

Compare *compare_new(Cmp cmp) {
  MutableCompare *compare = UTILITY_MALLOC(MutableCompare);
  compare->cmp = cmp;
  compare->extra = NULL;
  return compare;
}
void compare_delete(Compare *compare) {
  MutableCompare *mutcmp = compare_as_mut(compare);
  UTILITY_FREE(mutcmp);
}
CompareExtra compare_set_extra(Compare *compare, CompareExtra extra) {
  UTILITY_SWAP(CompareExtra, compare_as_mut(compare)->extra, extra);
  return extra;
}
int compare_cmp(Compare *compare, ElemType lhs, ElemType rhs) {
  if (compare->cmp) {
    return compare->cmp(lhs, rhs, compare->extra);
  } else {
    return (lhs < rhs) ? -1 : (rhs < lhs);
  }
}
