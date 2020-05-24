#include "vector.h"

#include <assert.h>
#include <stdlib.h>

struct struct_Vector {
  int *begin;
  int *end;
  int *capacity;
};

static boolean vector_allocated(const Vector *v) {
  return v->begin != NULL;
}

Vector *vector_new(void) {
  Vector *v = malloc(sizeof(Vector));
  v->begin = NULL;
  v->end = NULL;
  v->capacity = NULL;
  return v;
}
Vector *vector_free(Vector *v) {
  assert(v);
  free(v->begin);
  free(v);
  return NULL;
}
int vector_size(const Vector *v) {
  assert(v);
  return vector_allocated(v) ? v->end - v->begin : 0;
}
