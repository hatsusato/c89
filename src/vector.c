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

static boolean vector_allocated(const Vector *v) {
  return v->begin != NULL;
}
static int vector_capacity(const Vector *v) {
  return vector_allocated(v) ? (v->capacity - v->begin) / v->align : 0;
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
  int size = v->begin ? v->end - v->begin : 0;
  int capacity =
      v->begin ? 2 * (v->capacity - v->begin) : v->align * initial_size;
  src = vector_alloc(v, size, capacity);
  if (src) {
    memcpy(v->begin, src, size);
    free(src);
  }
}

Vector *vector_new(Alignment a) {
  Vector *v = NULL;
  assert(0 < a);
  v = malloc(sizeof(Vector));
  v->align = a;
  v->begin = NULL;
  v->end = NULL;
  v->capacity = NULL;
  return v;
}
void vector_free(Vector **v) {
  Vector *p = NULL;
  assert(v && *v);
  p = *v;
  free(p->begin);
  free(p);
  *v = NULL;
}
int vector_size(const Vector *v) {
  assert(v);
  return vector_allocated(v) ? (v->end - v->begin) / v->align : 0;
}
boolean vector_empty(const Vector *v) {
  assert(v);
  return vector_allocated(v) ? v->begin == v->end : true;
}
void vector_push_back(Vector *v, void *e, int size) {
  assert(v);
  assert(size <= v->align);
  if (v->end == v->capacity) {
    vector_extend(v);
  }
  memcpy(v->end, e, size);
  v->end += v->align;
}
