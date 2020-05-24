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
static int vector_capacity(const Vector *v) {
  return vector_allocated(v) ? v->capacity - v->begin : 0;
}
static int *vector_alloc(Vector *v, int size, int capacity) {
  int *prev = v->begin;
  v->begin = malloc(capacity * sizeof(int));
  v->end = v->begin + size;
  v->capacity = v->begin + capacity;
  return prev;
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
boolean vector_empty(const Vector *v) {
  assert(v);
  return vector_allocated(v) ? v->begin == v->end : true;
}
