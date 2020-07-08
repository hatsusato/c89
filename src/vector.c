#include "vector.h"

#include <stdlib.h>
#include <string.h>

struct struct_Vector {
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
  Size initial_size = 16 * vector_alignment();
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
  return v->size / vector_alignment();
}
void *vector_back(Vector *v) {
  Size size = 0;
  assert(v);
  if (v->size == v->capacity) {
    vector_extend(v, 2 * v->capacity);
  }
  size = v->size;
  v->size += vector_alignment();
  return vector_offset(v, size);
}
void *vector_begin(Vector *v) {
  assert(v);
  return vector_offset(v, 0);
}
void *vector_end(Vector *v) {
  assert(v);
  return vector_offset(v, v->size);
}
