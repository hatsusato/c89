#include "set.h"

#include "compare.h"
#include "set/sort.h"
#include "utility.h"
#include "vector.h"

struct struct_Set {
  Vector *vec;
  Compare *cmp;
};

static void set_sort(Set *set) {
  ElemType *begin = vector_begin(set->vec);
  ElemType *end = vector_end(set->vec);
  quick_sort(begin, end, set->cmp);
}
static const ElemType *set_search(const Set *set, ElemType key) {
  ElemType *begin = vector_begin(set->vec);
  ElemType *end = vector_end(set->vec);
  return binary_search(key, begin, end, set->cmp);
}

Set *set_new(Destructor dtor, Compare *cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->vec = vector_new(dtor);
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
void set_insert(Set *set, ElemType elem) {
  assert(set);
  vector_push(set->vec, elem);
  set_sort(set);
}
Bool set_contains(const Set *set, ElemType elem) {
  assert(set);
  return set_find(set, elem) != NULL;
}
const ElemType *set_find(const Set *set, ElemType key) {
  assert(set);
  return set_search(set, key);
}
const ElemType *set_begin(const Set *set) {
  assert(set);
  return vector_begin(set->vec);
}
const ElemType *set_end(const Set *set) {
  assert(set);
  return vector_end(set->vec);
}
