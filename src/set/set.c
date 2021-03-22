#include "set.h"

#include "compare/compare.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Set {
  Vector *vec;
  VectorCmp cmp;
};

Set *set_new(VectorDestructor dtor, VectorCmp cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->vec = vector_new(dtor);
  set->cmp = cmp;
  return set;
}
void set_delete(Set *set) {
  vector_delete(set->vec);
  UTILITY_FREE(set);
}
void set_clear(Set *set) {
  vector_clear(set->vec);
}
void set_insert(Set *set, CompareElem elem) {
  vector_push(set->vec, (VectorElem)elem);
  vector_sort(set->vec, set->cmp);
}
CompareElem set_find(const Set *set, CompareElem key) {
  return vector_search(set->vec, &key, set->cmp);
}
