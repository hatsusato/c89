#include "sort.h"

#include "compare/compare.h"
#include "utility/utility.h"

static Size sort_threshold(void) {
  return 32;
}

void insert_sort(CompareElem *begin, CompareElem *end, Compare *cmp) {
  CompareElem *cur = begin;
  while (++cur < end) {
    CompareElem val = *cur, *dst = cur, *src = cur - 1;
    while (begin < dst && 0 < compare_cmp(cmp, *src, val)) {
      *dst-- = *src--;
    }
    *dst = val;
  }
}
void quick_sort(CompareElem *begin, CompareElem *end, Compare *cmp) {
  CompareElem pivot;
  CompareElem *lo = begin, *hi = end - 1;
  CompareElem *mid = begin + (end - begin) / 2;
  if (end - begin < sort_threshold()) {
    insert_sort(begin, end, cmp);
    return;
  }
  if (0 < compare_cmp(cmp, *lo, *hi)) {
    UTILITY_SWAP(CompareElem, *lo, *hi);
  }
  if (0 < compare_cmp(cmp, *lo, *mid)) {
    UTILITY_SWAP(CompareElem, *lo, *mid);
  } else if (0 < compare_cmp(cmp, *mid, *hi)) {
    UTILITY_SWAP(CompareElem, *mid, *hi);
  }
  pivot = *mid;
  while (lo < hi) {
    ++lo;
    --hi;
    while (compare_cmp(cmp, *lo, pivot) < 0) {
      ++lo;
    }
    while (compare_cmp(cmp, pivot, *hi) < 0) {
      --hi;
    }
    if (lo < hi) {
      UTILITY_SWAP(CompareElem, *lo, *hi);
    }
  }
  quick_sort(begin, lo, cmp);
  quick_sort(lo, end, cmp);
}
const CompareElem *binary_search(CompareElem key, const CompareElem *begin,
                                 const CompareElem *end, Compare *cmp) {
  while (begin < end) {
    const CompareElem *mid = begin + (end - begin) / 2;
    int ret = compare_cmp(cmp, key, *mid);
    if (ret < 0) {
      end = mid;
    } else if (0 < ret) {
      begin = mid + 1;
    } else {
      return mid;
    }
  }
  return NULL;
}
