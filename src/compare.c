#include "compare.h"

#include "utility.h"

struct struct_Compare {
  Cmp cmp;
};

Compare *compare_new(Cmp cmp) {
  Compare *compare = UTILITY_MALLOC(Compare);
  compare->cmp = cmp;
  return compare;
}
void compare_delete(Compare *compare) {
  UTILITY_FREE(compare);
}
