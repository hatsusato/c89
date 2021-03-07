#include "pair.h"

#include "compare/compare.h"
#include "utility.h"

static int pair_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  return compare_cmp(extra, pair_key(lhs), pair_key(rhs));
}
static void pair_delete_keycmp(ElemType keycmp) {
  compare_delete(keycmp);
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
Compare *pair_new_compare(Compare *keycmp) {
  Compare *compare = compare_new(pair_compare);
  compare_set_extra(compare, keycmp, pair_delete_keycmp);
  return compare;
}
Pair pair_dummy(ElemType key) {
  Pair pair;
  pair.key = key;
  pair.val = NULL;
  return pair;
}
ElemType pair_key(Pair *pair) {
  return pair->key;
}
ElemType *pair_val(Pair *pair) {
  return &pair->val;
}
