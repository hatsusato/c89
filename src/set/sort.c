#include "set/sort.h"

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
