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
static CompareElem *compare_sort_once(Compare *compare, CompareElem *lo,
                                      CompareElem *hi) {
  CompareElem pivot = lo[(hi - lo) / 2];
  while (lo < hi) {
    for (; lo < hi; ++lo) {
      if (compare_cmp(compare, pivot, *lo) < 0) {
        break;
      }
    }
    for (; lo < hi; --hi) {
      if (compare_cmp(compare, *hi, pivot) < 0) {
        break;
      }
    }
    UTILITY_SWAP(CompareElem, *lo, *hi);
  }
  return lo;
}
static int compare_for_vector(CompareElem l, CompareElem r, CompareExtra x) {
  UTILITY_UNUSED(l);
  UTILITY_UNUSED(r);
  UTILITY_UNUSED(x);
  return 0;
}

Compare *compare_new(CompareCmp cmp, CompareExtra extra) {
  MutableCompare *compare = UTILITY_MALLOC(MutableCompare);
  compare->cmp = cmp;
  compare->extra = extra;
  return compare;
}
Compare *compare_new_for_vector(VectorCmp cmp) {
  MutableCompare *compare = UTILITY_MALLOC(MutableCompare);
  compare->cmp = compare_for_vector;
  compare->extra = (CompareExtra)cmp;
  return compare;
}
void compare_delete(Compare *compare) {
  UTILITY_FREE(compare);
}
int compare_cmp(Compare *compare, CompareElem lhs, CompareElem rhs) {
  if (!compare) {
    return utility_strcmp(lhs, rhs);
  } else if (compare->cmp == compare_for_vector) {
    return ((VectorCmp)compare->extra)(&lhs, &rhs);
  } else if (compare->cmp) {
    return compare->cmp(lhs, rhs, compare->extra);
  } else {
    return utility_strcmp(lhs, rhs);
  }
}
void compare_sort_quick(Compare *compare, CompareElem *begin,
                        CompareElem *end) {
  static const Size threshold = 32;
  if (threshold < end - begin) {
    CompareElem *mid = compare_sort_once(compare, begin, end - 1);
    compare_sort_quick(compare, begin, mid);
    compare_sort_quick(compare, mid, end);
  } else if (0 < end - begin) {
    compare_sort_insert(compare, begin, end);
  }
}
CompareElem compare_binary_search(Compare *compare, CompareElem key,
                                  const CompareElem *begin,
                                  const CompareElem *end) {
  const CompareElem *it = begin;
  Size size = end - begin;
  while (size > 1) {
    const Size half = size / 2;
    if (compare_cmp(compare, it[half], key) <= 0) {
      it += half;
    }
    size -= half;
  }
  return begin != end && compare_cmp(compare, *it, key) == 0 ? *it : NULL;
}
