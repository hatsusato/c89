#include "vector.h"

#include <stdlib.h>
#include <string.h>

#include "utility.h"

struct struct_Vector {
  VectorElem *data;
  Size size, capacity;
};

static void vector_alloc(Vector *v) {
  VectorElem *prev = v->data;
  v->data = malloc(v->capacity * sizeof(VectorElem));
  if (prev) {
    memcpy(v->data, prev, v->size * sizeof(VectorElem));
    free(prev);
  }
}

Size vector_alignment(void) {
  return sizeof(VectorElem);
}
Vector *vector_new(void) {
  Vector *v = malloc(sizeof(Vector));
  v->data = NULL;
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
VectorElem *vector_begin(const Vector *v) {
  assert(v);
  return v->data;
}
VectorElem *vector_end(const Vector *v) {
  assert(v);
  return v->data + v->size;
}
VectorElem vector_front(const Vector *v) {
  assert(v);
  if (0 < v->size) {
    return v->data[0];
  }
  return NULL;
}
VectorElem vector_back(const Vector *v) {
  assert(v);
  if (0 < v->size) {
    return v->data[v->size - 1];
  }
  return NULL;
}
void vector_push(Vector *v, VectorElem elem) {
  assert(v);
  if (v->size == v->capacity) {
    v->capacity += 1 + v->size;
    vector_alloc(v);
  }
  v->data[v->size++] = elem;
}
void vector_pop(Vector *v, VectorDestructor dtor) {
  assert(v);
  if (0 < v->size) {
    --v->size;
    if (dtor) {
      dtor(v->data[v->size]);
    }
    v->data[v->size] = NULL;
  }
}
void vector_clear(Vector *v, VectorDestructor dtor) {
  assert(v);
  while (0 < v->size) {
    vector_pop(v, dtor);
  }
}
