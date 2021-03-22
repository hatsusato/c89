#include "set.h"

#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Set {
  Vector *vec;
  VectorCmp cmp;
};

static int set_cmp_default(const ConstGeneric *lhs, const ConstGeneric *rhs) {
  return utility_strcmp(*lhs, *rhs);
}

Set *set_new(VectorDestructor dtor, VectorCmp cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->vec = vector_new(dtor);
  set->cmp = cmp ? cmp : set_cmp_default;
  return set;
}
void set_delete(Set *set) {
  vector_delete(set->vec);
  UTILITY_FREE(set);
}
void set_clear(Set *set) {
  vector_clear(set->vec);
}
void set_insert(Set *set, ConstGeneric elem) {
  vector_push(set->vec, (Generic)elem);
  vector_sort(set->vec, set->cmp);
}
ConstGeneric set_find(const Set *set, ConstGeneric key) {
  return vector_search(set->vec, &key, set->cmp);
}
