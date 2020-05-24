#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct struct_Vector {
  Alignment align;
  Byte *begin;
  Byte *end;
  Byte *capacity;
};

static Byte *vector_origin(void) {
  static Byte origin = 0;
  return &origin;
}
static void vector_free_begin(Byte *begin) {
  if (vector_origin() != begin) {
    free(begin);
  }
}
static Size vector_size(const Vector *v) {
  return v->end - v->begin;
}
static Size vector_capacity(const Vector *v) {
  return v->capacity - v->begin;
}
static boolean vector_full(const Vector *v) {
  return v->end == v->capacity;
}
static Size vector_capacity_next(const Vector *v) {
  Size initial_size = 16 * v->align;
  Size capacity = vector_capacity(v);
  return (0 == capacity) ? initial_size : 2 * capacity;
}
static Byte *vector_alloc(Vector *v, Size size, Size capacity) {
  Byte *prev = v->begin;
  v->begin = malloc(capacity);
  v->end = v->begin + size;
  v->capacity = v->begin + capacity;
  return prev;
}
static void vector_extend(Vector *v) {
  Byte *src = NULL;
  Size size = vector_size(v);
  Size capacity = vector_capacity_next(v);
  src = vector_alloc(v, size, capacity);
  memcpy(v->begin, src, size);
  vector_free_begin(src);
}

Vector *vector_new(Alignment a) {
  Vector *v = NULL;
  assert(0 < a);
  v = malloc(sizeof(Vector));
  v->align = a;
  v->begin = vector_origin();
  v->end = v->begin;
  v->capacity = v->begin;
  return v;
}
void vector_free(Vector **v) {
  assert(v && *v);
  vector_free_begin((*v)->begin);
  free(*v);
  *v = NULL;
}
Size vector_length(const Vector *v) {
  assert(v);
  return vector_size(v) / v->align;
}
boolean vector_empty(const Vector *v) {
  assert(v);
  return v->begin == v->end;
}
void *vector_back(Vector *v) {
  assert(v);
  if (vector_full(v)) {
    vector_extend(v);
  }
  v->end += v->align;
  return v->end - v->align;
}
void *vector_at(Vector *v, Index i) {
  assert(v);
  return v->begin + i * v->align;
}
