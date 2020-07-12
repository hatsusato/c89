#include "set.h"

#include <stdlib.h>

#include "utility.h"
#include "vector.h"

struct struct_Set {
  Vector *data;
  int (*cmp)(const void *, const void *);
};

static int set_compare_default(const ElemType *lhs, const ElemType *rhs) {
  return *lhs < *rhs ? -1 : *lhs > *rhs ? 1 : 0;
}
static void set_sort(Set *set) {
  ElemType *data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  qsort(data, count, sizeof(ElemType), set->cmp);
}

Set *set_new(Compare cmp) {
  Set *set = malloc(sizeof(Set));
  set->data = vector_new();
  set->cmp =
      (int (*)(const void *, const void *))(cmp ? cmp : set_compare_default);
  return set;
}
void set_delete(Set *set) {
  assert(set);
  vector_delete(set->data);
  free(set);
}
void set_insert(Set *set, ElemType elem) {
  assert(set);
  if (!set_find(set, elem)) {
    vector_push(set->data, elem);
    set_sort(set);
  }
}
Bool set_contains(const Set *set, ElemType elem) {
  assert(set);
  return set_find(set, elem) != NULL;
}
const ElemType *set_find(const Set *set, ElemType key) {
  assert(set);
  return bsearch(&key, vector_begin(set->data), vector_length(set->data),
                 sizeof(ElemType), set->cmp);
}
const ElemType *set_begin(const Set *set) {
  assert(set);
  return vector_begin(set->data);
}
const ElemType *set_end(const Set *set) {
  assert(set);
  return vector_end(set->data);
}
