#include "compare.h"

#include "utility.h"

struct struct_Compare {
  Cmp cmp;
  CompareExtra extra;
};
typedef struct struct_Compare MutableCompare;

static MutableCompare *compare_mut(Compare *cmp) {
  return (MutableCompare *)cmp;
}

Compare *compare_new(Cmp cmp) {
  Compare *compare = UTILITY_MALLOC(Compare);
  compare_mut(compare)->cmp = cmp;
  compare_mut(compare)->extra = NULL;
  return compare;
}
void compare_delete(Compare *compare) {
  UTILITY_FREE(compare);
}
CompareExtra compare_set_extra(Compare *compare, CompareExtra extra) {
  UTILITY_SWAP(CompareExtra, compare_mut(compare)->extra, extra);
  return extra;
}
int compare_cmp(Compare *compare, ElemType lhs, ElemType rhs) {
  if (compare->cmp) {
    return compare->cmp(lhs, rhs, compare->extra);
  } else {
    return (lhs < rhs) ? -1 : (rhs < lhs);
  }
}
