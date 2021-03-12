#include "set.h"

#include "compare/compare.h"
#include "set/sort.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Set {
  Vector *vec;
  Compare *cmp;
};

static CompareElem *set_begin(const Set *set) {
  assert(set);
  return (CompareElem *)vector_begin(set->vec);
}
static CompareElem *set_end(const Set *set) {
  assert(set);
  return (CompareElem *)vector_end(set->vec);
}
static void set_sort(Set *set) {
  quick_sort(set_begin(set), set_end(set), set->cmp);
}
static const CompareElem *set_search(const Set *set, CompareElem key) {
  return binary_search(key, set_begin(set), set_end(set), set->cmp);
}

Set *set_new(Compare *cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->vec = vector_new(NULL);
  set->cmp = cmp;
  return set;
}
void set_delete(Set *set) {
  assert(set);
  compare_delete(set->cmp);
  vector_delete(set->vec);
  UTILITY_FREE(set);
}
void set_clear(Set *set) {
  vector_clear(set->vec);
}
void set_insert(Set *set, CompareElem elem) {
  assert(set);
  vector_push(set->vec, (VectorElem)elem);
  set_sort(set);
}
const CompareElem *set_find(const Set *set, CompareElem key) {
  assert(set);
  return set_search(set, key);
}
