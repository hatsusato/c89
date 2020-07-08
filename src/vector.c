#include "vector.h"

#include <stdlib.h>
#include <string.h>

struct struct_Vector {
  const void **data;
  Size size, capacity;
};

static void vector_alloc(Vector *v) {
  void *prev = v->data;
  v->data = malloc(v->capacity * vector_alignment());
  if (prev) {
    memcpy(v->data, prev, v->size * vector_alignment());
    free(prev);
  }
}

Size vector_alignment(void) {
  return sizeof(void *);
}
Vector *vector_new(void) {
  Vector *v = malloc(sizeof(Vector));
  v->data = nil;
  v->size = v->capacity = 0;
  return v;
}
void vector_delete(Vector *v) {
  assert(v);
  free(v->data);
  free(v);
}
Size vector_length(const Vector *v) {
  assert(v);
  return v->size;
}
const void **vector_begin(const Vector *v) {
  assert(v);
  return v->data;
}
const void **vector_end(const Vector *v) {
  assert(v);
  return v->data + v->size;
}
void vector_push(Vector *v, const void *data) {
  assert(v);
  if (v->size == v->capacity) {
    v->capacity += 1 + v->size;
    vector_alloc(v);
  }
  v->data[v->size++] = data;
}
void vector_pop(Vector *v, VectorDestructor dtor) {
  assert(v);
  if (0 < v->size) {
    --v->size;
    if (dtor) {
      dtor(v->data[v->size]);
    }
    v->data[v->size] = nil;
  }
}
void vector_clean(Vector *v, VectorDestructor dtor) {
  assert(v);
  while (0 < v->size) {
    vector_pop(v, dtor);
  }
}
