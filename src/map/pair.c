#include "pair.h"

#include "compare.h"
#include "utility.h"

int pair_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  const Pair *l = lhs, *r = rhs;
  return compare_cmp(extra, l->key, r->key);
}
Pair *pair_new(ElemType key, ElemType val) {
  Pair *pair = UTILITY_MALLOC(Pair);
  pair->key = key;
  pair->val = val;
  return pair;
}
void pair_delete(ElemType pair) {
  UTILITY_FREE(pair);
}
Pair pair_dummy(ElemType key) {
  Pair pair;
  pair.key = key;
  pair.val = NULL;
  return pair;
}
ElemType *pair_val(Pair *pair) {
  return &pair->val;
}
