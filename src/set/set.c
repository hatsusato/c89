#include "set.h"

#include <stdlib.h>

#include "utility.h"
#include "vector.h"

struct struct_Set {
  Vector *data;
  SetCompare cmp;
};

static void set_sort(Set *set) {
  ElemType *data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  qsort(data, count, sizeof(ElemType), set->cmp);
}
static const ElemType *set_search(const Set *set, ElemType key) {
  const ElemType *data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  return bsearch(&key, data, count, sizeof(ElemType), set->cmp);
}

Set *set_new(SetCompare cmp) {
  Set *set = UTILITY_MALLOC(Set);
  set->data = vector_new(NULL);
  set->cmp = cmp;
  return set;
}
void set_delete(Set *set) {
  assert(set);
  vector_delete(set->data);
  UTILITY_FREE(set);
}
ElemType set_insert(Set *set, ElemType elem) {
  const ElemType *found;
  assert(set);
  found = set_find(set, elem);
  if (!found) {
    vector_push(set->data, elem);
    set_sort(set);
    found = &elem;
  }
  return *found;
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
  return vector_begin(set->data);
}
const ElemType *set_end(const Set *set) {
  assert(set);
  return vector_end(set->data);
}
