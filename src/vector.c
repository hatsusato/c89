#include "vector.h"

#include <stdlib.h>
#include <string.h>

#include "utility.h"

struct struct_Vector {
  ElemType *data;
  Size size, capacity;
  Destructor dtor;
};

static void vector_default_destructor(ElemType e) {
  (void)e;
}
static void vector_alloc(Vector *v) {
  ElemType *prev = v->data;
  v->data = malloc(v->capacity * sizeof(ElemType));
  if (prev) {
    memcpy(v->data, prev, v->size * sizeof(ElemType));
    free(prev);
  }
}

Vector *vector_new(Destructor dtor) {
  Vector *v = malloc(sizeof(Vector));
  v->data = NULL;
  v->size = v->capacity = 0;
  v->dtor = dtor ? dtor : vector_default_destructor;
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
ElemType *vector_begin(const Vector *v) {
  assert(v);
  return v->data;
}
ElemType *vector_end(const Vector *v) {
  assert(v);
  return v->data + v->size;
}
ElemType vector_front(const Vector *v) {
  assert(v);
  if (0 < v->size) {
    return v->data[0];
  }
  return NULL;
}
ElemType vector_back(const Vector *v) {
  assert(v);
  if (0 < v->size) {
    return v->data[v->size - 1];
  }
  return NULL;
}
void vector_push(Vector *v, ElemType elem) {
  assert(v);
  if (v->size == v->capacity) {
    v->capacity += 1 + v->size;
    vector_alloc(v);
  }
  v->data[v->size++] = elem;
}
void vector_pop(Vector *v) {
  assert(v);
  if (0 < v->size) {
    --v->size;
    v->dtor(v->data[v->size]);
    v->data[v->size] = NULL;
  }
}
void vector_clear(Vector *v) {
  assert(v);
  while (0 < v->size) {
    vector_pop(v);
  }
}
