#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct struct_Vector {
  Alignment align;
  Byte *data;
  Size size, capacity;
};

static Size max_size(Size x, Size y) {
  return x < y ? y : x;
}
static boolean vector_full(const Vector *v) {
  return v->size == v->capacity;
}
static void vector_extend(Vector *v) {
  Size initial_size = 16 * v->align;
  v->capacity += max_size(initial_size, v->capacity);
}
static Byte *vector_alloc(Vector *v) {
  Byte *prev = v->data;
  v->data = malloc(v->capacity);
  return prev;
}

Vector *vector_new(Alignment a) {
  Vector *v = nil;
  assert(0 < a);
  v = malloc(sizeof(Vector));
  v->align = a;
  v->data = nil;
  v->size = v->capacity = 0;
  return v;
}
void vector_free(Vector **v) {
  assert(v && *v);
  free((*v)->data);
  free(*v);
  *v = nil;
}
Size vector_length(const Vector *v) {
  assert(v);
  return v->size / v->align;
}
boolean vector_empty(const Vector *v) {
  assert(v);
  return 0 == v->size;
}
void *vector_back(Vector *v) {
  void *ptr = nil;
  assert(v);
  if (vector_full(v)) {
    vector_extend(v);
    if ((ptr = vector_alloc(v))) {
      memcpy(v->data, ptr, v->size);
      free(ptr);
    }
  }
  ptr = v->data + v->size;
  v->size += v->align;
  return ptr;
}
void *vector_at(Vector *v, Index i) {
  assert(v);
  assert(i * v->align < v->size);
  return v->data + i * v->align;
}
