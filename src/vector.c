#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct struct_Vector {
  Alignment align;
  void *data;
  Size size, capacity;
};

static void vector_alloc(Vector *v) {
  void *prev = v->data;
  v->data = malloc(v->capacity);
  if (prev) {
    memcpy(v->data, prev, v->size);
    free(prev);
  }
}
static void vector_extend(Vector *v, Size size) {
  Size initial_size = 16 * v->align;
  if (v->capacity < size) {
    v->capacity = size;
  } else {
    v->capacity += initial_size;
  }
  vector_alloc(v);
}
static void *vector_offset(Vector *v, Size offset) {
  Byte *ptr = v->data;
  return ptr + offset;
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
void vector_delete(Vector **v) {
  assert(v && *v);
  free((*v)->data);
  free(*v);
  *v = nil;
}
Size vector_length(const Vector *v) {
  assert(v);
  return v->size / v->align;
}
void *vector_back(Vector *v) {
  Size size = 0;
  assert(v);
  if (v->size == v->capacity) {
    vector_extend(v, 2 * v->capacity);
  }
  size = v->size;
  v->size += v->align;
  return vector_offset(v, size);
}
void *vector_at(Vector *v, Index i) {
  assert(v);
  assert(v->align * i < v->size);
  return vector_offset(v, v->align * i);
}
Vector *vector_clone(const Vector *v) {
  Vector *w = nil;
  assert(v);
  w = vector_new(v->align);
  if (0 == v->size) {
    return w;
  }
  vector_extend(w, v->size);
  memcpy(w->data, v->data, v->size);
  w->size = v->size;
  return w;
}
void vector_append(Vector *v, void *buf, Size len) {
  assert(v);
  if (0 == len) {
    return;
  }
  assert(buf);
  len *= v->align;
  if (v->capacity < v->size + len) {
    vector_extend(v, v->size + len);
  }
  memcpy(vector_offset(v, v->size), buf, len);
  v->size += len;
}
void vector_clear(Vector *v) {
  assert(v);
  v->size = 0;
}
void vector_pop(Vector *v) {
  assert(v);
  assert(0 < v->size);
  --v->size;
}
