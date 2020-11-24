#include "set/sort.h"

#include "utility.h"

static Size sort_threshold(void) {
  return 32;
}
static const ElemType *middle(const ElemType *begin, const ElemType *end) {
  return begin + (end - begin) / 2;
}

void insert_sort(ElemType *begin, ElemType *end, Compare *cmp) {
  ElemType *cur = begin;
  while (++cur < end) {
    ElemType val = *cur, *dst = cur, *src = cur - 1;
    while (begin < dst && 0 < compare_cmp(cmp, *src, val)) {
      *dst-- = *src--;
    }
    *dst = val;
  }
}
void quick_sort(ElemType *begin, ElemType *end, Compare *cmp) {
  ElemType pivot;
  ElemType *lo = begin, *hi = end - 1;
  ElemType *mid = (ElemType *)middle(begin, end);
  if (end - begin < sort_threshold()) {
    insert_sort(begin, end, cmp);
    return;
  }
  if (0 < compare_cmp(cmp, *lo, *hi)) {
    UTILITY_SWAP(ElemType, *lo, *hi);
  }
  if (0 < compare_cmp(cmp, *lo, *mid)) {
    UTILITY_SWAP(ElemType, *lo, *mid);
  } else if (0 < compare_cmp(cmp, *mid, *hi)) {
    UTILITY_SWAP(ElemType, *mid, *hi);
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
      UTILITY_SWAP(ElemType, *lo, *hi);
    }
  }
  quick_sort(begin, lo, cmp);
  quick_sort(lo, end, cmp);
}
const ElemType *binary_search(ElemType key, const ElemType *begin,
                              const ElemType *end, Compare *cmp) {
  while (begin < end) {
    const ElemType *mid = middle(begin, end);
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
