#include "compare.h"

#include "utility/utility.h"

struct struct_Compare {
  CompareCmp cmp;
  CompareExtra extra;
};
typedef struct struct_Compare MutableCompare;

static int compare_strcmp_extra(CompareElem lhs, CompareElem rhs,
                                CompareExtra extra) {
  UTILITY_UNUSED(extra);
  return utility_strcmp(lhs, rhs);
}

Compare *compare_new(CompareCmp cmp) {
  MutableCompare *compare = UTILITY_MALLOC(MutableCompare);
  compare->cmp = cmp;
  compare->extra = NULL;
  return compare;
}
void compare_delete(Compare *compare) {
  if (compare_strcmp() != compare) {
    UTILITY_FREE(compare);
  }
}
CompareExtra compare_get_extra(Compare *compare) {
  return compare->extra;
}
void compare_set_extra(Compare *compare, CompareExtra extra) {
  MutableCompare *mutcmp = (MutableCompare *)compare;
  mutcmp->extra = extra;
}
int compare_cmp(Compare *compare, CompareElem lhs, CompareElem rhs) {
  if (compare->cmp) {
    return compare->cmp(lhs, rhs, compare->extra);
  } else {
    return utility_ptrcmp(lhs, rhs);
  }
}
Compare *compare_strcmp(void) {
  static Compare cmp = {compare_strcmp_extra, NULL};
  return &cmp;
}
