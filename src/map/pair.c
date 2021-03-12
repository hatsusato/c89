#include "pair.h"

#include "compare/compare.h"
#include "utility/utility.h"

static int pair_compare(CompareElem lhs, CompareElem rhs, CompareExtra extra) {
  return compare_cmp(extra, pair_key(lhs), pair_key(rhs));
}

Pair *pair_new(CompareElem key, CompareElem val) {
  Pair *pair = UTILITY_MALLOC(Pair);
  pair->key = key;
  pair->val = val;
  return pair;
}
void pair_delete(Pair *pair) {
  UTILITY_FREE(pair);
}
Compare *pair_new_compare(Compare *keycmp) {
  Compare *compare = compare_new(pair_compare);
  compare_set_extra(compare, keycmp);
  return compare;
}
Pair pair_dummy(CompareElem key) {
  Pair pair;
  pair.key = key;
  pair.val = NULL;
  return pair;
}
CompareElem pair_key(const Pair *pair) {
  return pair->key;
}
CompareElem *pair_val(Pair *pair) {
  return &pair->val;
}
