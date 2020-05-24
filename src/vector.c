#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct struct_Vector {
  Alignment align;
  Byte *data;
  Size size, capacity;
};

static boolean vector_full(const Vector *v) {
  return v->size == v->capacity;
}
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
    vector_extend(v, 2 * v->capacity);
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
void vector_append(Vector *v, const Vector *w) {
  assert(v && w);
  assert(v->align == w->align);
  if (v->capacity < v->size + w->size) {
    vector_extend(v, v->size + w->size);
  }
  memcpy(v->data + v->size, w->data, w->size);
  v->size += w->size;
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
void vector_copy(Vector *v, void *buf, Size len) {
  assert(v);
  if (0 == len) {
    return;
  }
  assert(buf);
  len *= v->align;
  if (v->capacity < v->size + len) {
    vector_extend(v, v->size + len);
  }
  memcpy(v->data + v->size, buf, len);
  v->size += len;
}
void vector_clear(Vector *v) {
  assert(v);
  v->size = 0;
}
