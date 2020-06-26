#include "set.h"

#include <assert.h>
#include <stdlib.h>

#include "vector.h"

#define SET_ALIGNMENT (sizeof(void *))

struct struct_Set {
  Vector *data;
};

static void *set_find(const Set *set, const void *key,
                      int (*cmp)(const void *, const void *)) {
  const void *const *data = vector_begin(set->data);
  size_t count = vector_length(set->data);
  return bsearch(&key, data, count, SET_ALIGNMENT, cmp);
}

Set *set_new(void) {
  Set *set = malloc(sizeof(Set));
  set->data = vector_new(SET_ALIGNMENT);
  return set;
}
void set_delete(Set *set) {
  assert(set);
  vector_delete(set->data);
  free(set);
}
