#include "set.h"

#include <stdlib.h>

#include "vector.h"

struct struct_Set {
  Vector *data;
  SetCompare cmp;
};
typedef int (*Compare)(const void *, const void *);

static int set_compare_default(const SetElem *lhs, const SetElem *rhs) {
  return *lhs < *rhs ? -1 : *lhs > *rhs ? 1 : 0;
}
static void set_sort(Set *set) {
  SetElem *data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  qsort(data, count, sizeof(SetElem), (Compare)set->cmp);
}

Set *set_new(SetCompare cmp) {
  Set *set = malloc(sizeof(Set));
  set->data = vector_new();
  set->cmp = cmp ? cmp : set_compare_default;
  return set;
}
void set_delete(Set *set) {
  assert(set);
  vector_delete(set->data);
  free(set);
}
void set_insert(Set *set, SetElem elem) {
  assert(set);
  if (!set_find(set, elem)) {
    vector_push(set->data, elem);
    set_sort(set);
  }
}
Bool set_contains(const Set *set, SetElem elem) {
  assert(set);
  return set_find(set, elem) != nil;
}
const SetElem *set_find(const Set *set, SetElem key) {
  assert(set);
  return bsearch(&key, vector_begin(set->data), vector_length(set->data),
                 sizeof(SetElem), (Compare)set->cmp);
}
const SetElem *set_begin(const Set *set) {
  assert(set);
  return vector_begin(set->data);
}
const SetElem *set_end(const Set *set) {
  assert(set);
  return vector_end(set->data);
}
