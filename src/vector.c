#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct struct_Vector {
  Alignment align;
  char *begin;
  char *end;
  char *capacity;
};

static char *vector_origin(void) {
  static char origin = 0;
  return &origin;
}
static void vector_free_begin(char *begin) {
  if (vector_origin() != begin) {
    free(begin);
  }
}
static int vector_size(const Vector *v) {
  return v->end - v->begin;
}
static int vector_capacity(const Vector *v) {
  return v->capacity - v->begin;
}
static boolean vector_full(const Vector *v) {
  return v->end == v->capacity;
}
static char *vector_alloc(Vector *v, int size, int capacity) {
  char *prev = v->begin;
  v->begin = malloc(capacity);
  v->end = v->begin + size;
  v->capacity = v->begin + capacity;
  return prev;
}
static void vector_extend(Vector *v) {
  static const int initial_size = 16;
  char *src = NULL;
  int size = vector_size(v);
  int capacity = vector_capacity(v);
  capacity = 0 < capacity ? 2 * capacity : v->align * initial_size;
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
int vector_length(const Vector *v) {
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
void *vector_at(Vector *v, int i) {
  assert(v);
  return v->begin + i * v->align;
}
