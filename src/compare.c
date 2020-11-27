#include "compare.h"

#include "types.h"
#include "utility.h"

struct struct_Compare {
  Cmp cmp;
  CompareExtra extra;
  Destructor dtor;
};
typedef struct struct_Compare MutableCompare;

Compare *compare_new(Cmp cmp) {
  MutableCompare *compare = UTILITY_MALLOC(MutableCompare);
  compare->cmp = cmp;
  compare->extra = NULL;
  compare->dtor = NULL;
  return compare;
}
void compare_delete(Compare *compare) {
  if (compare->dtor) {
    compare->dtor((ElemType)compare->extra);
  }
  UTILITY_FREE(compare);
}
CompareExtra compare_get_extra(Compare *compare) {
  return compare->extra;
}
void compare_set_extra(Compare *compare, CompareExtra extra, Destructor dtor) {
  MutableCompare *mutcmp = (MutableCompare *)compare;
  mutcmp->extra = extra;
  mutcmp->dtor = dtor;
}
int compare_cmp(Compare *compare, ElemType lhs, ElemType rhs) {
  if (compare->cmp) {
    return compare->cmp(lhs, rhs, compare->extra);
  } else {
    return utility_ptrcmp(lhs, rhs);
  }
}
int compare_strcmp(ElemType lhs, ElemType rhs, CompareExtra extra) {
  UTILITY_UNUSED(extra);
  return utility_strcmp(lhs, rhs);
}
