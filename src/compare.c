#include "compare.h"

#include "utility.h"

struct struct_Compare {
  Cmp cmp;
  void *extra;
};

Compare *compare_new(Cmp cmp) {
  Compare *compare = UTILITY_MALLOC(Compare);
  compare->cmp = cmp;
  compare->extra = NULL;
  return compare;
}
void compare_delete(Compare *compare) {
  UTILITY_FREE(compare);
}
void *compare_set_extra(Compare *compare, void *extra) {
  UTILITY_SWAP(void *, compare->extra, extra);
  return extra;
}
int compare_cmp(Compare *compare, ElemType lhs, ElemType rhs) {
  return compare->cmp(lhs, rhs, compare->extra);
}
