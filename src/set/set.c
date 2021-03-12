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
  return (CompareElem *)vector_begin(set->vec);
}
static CompareElem *set_end(const Set *set) {
  return (CompareElem *)vector_end(set->vec);
}

Set *set_new(Compare *cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->vec = vector_new(NULL);
  set->cmp = cmp;
  return set;
}
void set_delete(Set *set) {
  compare_delete(set->cmp);
  vector_delete(set->vec);
  UTILITY_FREE(set);
}
void set_clear(Set *set) {
  vector_clear(set->vec);
}
void set_insert(Set *set, CompareElem elem) {
  vector_push(set->vec, (VectorElem)elem);
  quick_sort(set_begin(set), set_end(set), set->cmp);
}
const CompareElem *set_find(const Set *set, CompareElem key) {
  return binary_search(key, set_begin(set), set_end(set), set->cmp);
}
