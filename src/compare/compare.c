#include "compare.h"

#include "utility/utility.h"

struct struct_Compare {
  CompareCmp cmp;
  CompareExtra extra;
};
typedef struct struct_Compare MutableCompare;

static void compare_sort_rotate(Compare *compare, CompareElem *lo,
                                CompareElem *hi) {
  CompareElem *it;
  for (it = lo; it < hi; ++it) {
    if (compare_cmp(compare, *hi, *it) < 0) {
      CompareElem val = *hi;
      UTILITY_MEMMOVE(CompareElem, it + 1, it, hi - it);
      *it = val;
      return;
    }
  }
}
static void compare_sort_insert(Compare *compare, CompareElem *begin,
                                CompareElem *end) {
  CompareElem *it;
  for (it = begin; it < end; ++it) {
    compare_sort_rotate(compare, begin, it);
  }
}

Compare *compare_new(CompareCmp cmp) {
  MutableCompare *compare = UTILITY_MALLOC(MutableCompare);
  compare->cmp = cmp;
  compare->extra = NULL;
  return compare;
}
void compare_delete(Compare *compare) {
  UTILITY_FREE(compare);
}
CompareExtra compare_get_extra(Compare *compare) {
  return compare->extra;
}
void compare_set_extra(Compare *compare, CompareExtra extra) {
  MutableCompare *mutcmp = (MutableCompare *)compare;
  mutcmp->extra = extra;
}
int compare_cmp(Compare *compare, CompareElem lhs, CompareElem rhs) {
  if (compare && compare->cmp) {
    return compare->cmp(lhs, rhs, compare->extra);
  } else {
    return utility_strcmp(lhs, rhs);
  }
}
