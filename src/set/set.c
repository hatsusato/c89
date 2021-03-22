#include "set.h"

#include "compare/compare.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Set {
  Vector *vec;
  Compare *cmp;
  VectorCmp vcmp;
};

static CompareElem *set_begin(const Set *set) {
  return (CompareElem *)vector_begin(set->vec);
}
static CompareElem *set_end(const Set *set) {
  return (CompareElem *)vector_end(set->vec);
}

Set *set_new(VectorDestructor dtor, VectorCmp cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->vec = vector_new(dtor);
  set->cmp = compare_new_for_vector(cmp);
  set->vcmp = cmp;
  return set;
}
void set_delete(Set *set) {
  if (set->vcmp) {
    compare_delete(set->cmp);
  }
  vector_delete(set->vec);
  UTILITY_FREE(set);
}
void set_clear(Set *set) {
  vector_clear(set->vec);
}
void set_insert(Set *set, CompareElem elem) {
  vector_push(set->vec, (VectorElem)elem);
  compare_sort_quick(set->cmp, set_begin(set), set_end(set));
}
CompareElem set_find(const Set *set, CompareElem key) {
  return compare_binary_search(set->cmp, key, set_begin(set), set_end(set));
}
