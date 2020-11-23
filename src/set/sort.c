#include "set/sort.h"

#include "utility.h"

static Size sort_threshold(void) {
  return 32;
}

void insert_sort(ElemType *begin, ElemType *end, Compare *cmp) {
  ElemType *cur = begin;
  while (++cur < end) {
    ElemType val = *cur, *dst = cur, *src = cur - 1;
    while (begin < dst && 0 < compare(cmp, *src, val)) {
      *dst-- = *src--;
    }
    *dst = val;
  }
}
void quick_sort(ElemType *begin, ElemType *end, Compare *cmp) {
  ElemType pivot;
  Size size = end - begin;
  ElemType *lo = begin, *hi = end - 1;
  ElemType *mid = begin + size / 2;
  if (size < sort_threshold()) {
    insert_sort(begin, end, cmp);
    return;
  }
  if (0 < compare(cmp, *lo, *hi)) {
    UTILITY_SWAP(ElemType, *lo, *hi);
  }
  if (0 < compare(cmp, *lo, *mid)) {
    UTILITY_SWAP(ElemType, *lo, *mid);
  } else if (0 < compare(cmp, *mid, *hi)) {
    UTILITY_SWAP(ElemType, *mid, *hi);
  }
  pivot = *mid;
  while (lo < hi) {
    ++lo;
    --hi;
    while (compare(cmp, *lo, pivot) < 0) {
      ++lo;
    }
    while (compare(cmp, pivot, *hi) < 0) {
      --hi;
    }
    if (lo < hi) {
      UTILITY_SWAP(ElemType, *lo, *hi);
    }
  }
  quick_sort(begin, lo, cmp);
  quick_sort(lo, end, cmp);
}
