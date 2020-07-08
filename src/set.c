#include "set.h"

#include <stdlib.h>
#include <string.h>

#include "vector.h"

struct struct_Set {
  Vector *data;
};

static int set_string_compare(const void *lhs, const void *rhs) {
  const char *const *l = lhs;
  const char *const *r = rhs;
  return strcmp(*l, *r);
}
static void *set_find(const Set *set, const void *key,
                      int (*cmp)(const void *, const void *)) {
  const void *const *data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  return bsearch(&key, data, count, vector_alignment(), cmp);
}
static void set_sort(Set *set, int (*cmp)(const void *, const void *)) {
  const void **data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  qsort(data, count, vector_alignment(), cmp);
}

Set *set_new(void) {
  Set *set = malloc(sizeof(Set));
  set->data = vector_new(vector_alignment());
  return set;
}
void set_delete(Set *set) {
  assert(set);
  vector_delete(set->data);
  free(set);
}
Bool set_string_contains(const Set *set, const char *str) {
  assert(set);
  return set_find(set, str, set_string_compare) != nil;
}
void set_string_insert(Set *set, const char *str) {
  assert(set);
  if (!set_string_contains(set, str)) {
    *(const char **)vector_back(set->data) = str;
    set_sort(set, set_string_compare);
  }
}
