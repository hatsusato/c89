#include "set.h"

#include <stdlib.h>

#include "vector.h"

struct struct_Set {
  Vector *data;
  SetCompare cmp;
};

static void *set_find(const Set *set, const void *key) {
  const void *const *data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  return bsearch(&key, data, count, vector_alignment(), set->cmp);
}
static void set_sort(Set *set) {
  const void **data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  qsort(data, count, vector_alignment(), set->cmp);
}

Set *set_new(SetCompare cmp) {
  Set *set = malloc(sizeof(Set));
  set->data = vector_new();
  set->cmp = cmp;
  return set;
}
void set_delete(Set *set) {
  assert(set);
  vector_delete(set->data);
  free(set);
}
Bool set_string_contains(const Set *set, const char *str) {
  assert(set);
  return set_find(set, str) != nil;
}
void set_string_insert(Set *set, const char *str) {
  assert(set);
  if (!set_string_contains(set, str)) {
    vector_push(set->data, str);
    set_sort(set);
  }
}
