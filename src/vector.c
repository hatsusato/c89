#include "vector.h"

#include "utility.h"

struct struct_Vector {
  ElemType *data;
  Size size, capacity;
  Destructor dtor;
};

static void vector_destructor_default(ElemType e) {
  (void)e;
}
static void vector_alloc(Vector *v) {
  ElemType *prev = v->data;
  v->data = UTILITY_MALLOC_ARRAY(ElemType, v->capacity);
  if (prev) {
    UTILITY_MEMCPY(ElemType, v->data, prev, v->size);
    UTILITY_FREE(prev);
  }
}

Vector *vector_new(Destructor dtor) {
  Vector *v = UTILITY_MALLOC(Vector);
  v->data = NULL;
  v->size = v->capacity = 0;
  v->dtor = dtor ? dtor : vector_destructor_default;
  return v;
}
void vector_delete(Vector *v) {
  assert(v);
  vector_clear(v);
  UTILITY_FREE(v->data);
  UTILITY_FREE(v);
}
void vector_destruct(Vector *v, ElemType elem) {
  assert(v);
  v->dtor(elem);
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
  v->data[v->size] = elem;
  ++v->size;
}
void vector_pop(Vector *v) {
  assert(v);
  if (0 < v->size) {
    --v->size;
    vector_destruct(v, v->data[v->size]);
    v->data[v->size] = NULL;
  }
}
void vector_clear(Vector *v) {
  assert(v);
  while (0 < v->size) {
    vector_pop(v);
  }
}
