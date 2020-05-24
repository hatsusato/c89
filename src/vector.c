#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct struct_Vector {
  Alignment align;
  Byte *data;
  Size size, capacity;
};

static Byte *vector_origin(void) {
  static Byte origin = 0;
  return &origin;
}
static void vector_free_data(Byte *data) {
  if (vector_origin() != data) {
    free(data);
  }
}
static Size vector_size(const Vector *v) {
  return v->size;
}
static Size vector_capacity(const Vector *v) {
  return v->capacity;
}
static boolean vector_full(const Vector *v) {
  return v->size == v->capacity;
}
static Size vector_capacity_next(const Vector *v) {
  Size initial_size = 16 * v->align;
  Size capacity = vector_capacity(v);
  return (0 == capacity) ? initial_size : 2 * capacity;
}
static Byte *vector_extend(Vector *v, Vector *base) {
  Byte *prev = v->data;
  int size = vector_size(base);
  int capacity = vector_capacity_next(base);
  v->data = malloc(capacity);
  v->size = size;
  v->capacity = capacity;
  return prev;
}
static void vector_copy(Vector *v, void *src) {
  memcpy(v->data, src, vector_size(v));
}

Vector *vector_new(Alignment a) {
  Vector *v = nil;
  assert(0 < a);
  v = malloc(sizeof(Vector));
  v->align = a;
  v->data = vector_origin();
  v->size = v->capacity = 0;
  return v;
}
void vector_free(Vector **v) {
  assert(v && *v);
  vector_free_data((*v)->data);
  free(*v);
  *v = nil;
}
Size vector_length(const Vector *v) {
  assert(v);
  return vector_size(v) / v->align;
}
boolean vector_empty(const Vector *v) {
  assert(v);
  return 0 == v->size;
}
void *vector_back(Vector *v) {
  void *ret = nil;
  assert(v);
  if (vector_full(v)) {
    Byte *src = vector_extend(v, v);
    vector_copy(v, src);
    vector_free_data(src);
  }
  ret = v->data + v->size;
  v->size += v->align;
  return ret;
}
void *vector_at(Vector *v, Index i) {
  assert(v);
  assert(i * v->align < v->size);
  return v->data + i * v->align;
}
