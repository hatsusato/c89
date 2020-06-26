#include "set.h"

#include <assert.h>
#include <stdlib.h>

#include "vector.h"

struct struct_Set {
  Vector *data;
};

Set *set_new(void) {
  Set *set = malloc(sizeof(Set));
  set->data = vector_new(sizeof(void *));
  return set;
}
void set_delete(Set *set) {
  assert(set);
  vector_delete(set->data);
  free(set);
}
