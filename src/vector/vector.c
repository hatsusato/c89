#include "vector.h"

#include "utility.h"

struct struct_Vector {
  ElemType *begin, *end, *last;
  Size size, capacity;
  Destructor dtor;
};

static void vector_destructor_default(ElemType e) {
  (void)e;
}
static const ElemType *vector_sentinel(void) {
  static const ElemType sentinel = NULL;
  return &sentinel;
}
static Bool vector_positive(const Vector *v) {
  const ElemType *const sentinel = vector_sentinel();
  assert((sentinel == v->begin && sentinel == v->end && sentinel == v->last) ||
         (sentinel != v->begin && sentinel != v->end && sentinel != v->last));
  return sentinel != v->begin;
}
static void vector_free(ElemType *buf) {
  if (vector_sentinel() != buf) {
    UTILITY_FREE(buf);
  }
}
static void vector_alloc(Vector *v) {
  Size leng = vector_length(v);
  Size size = vector_positive(v) ? 2 * vector_capacity(v) : 8;
  ElemType *buf = UTILITY_MALLOC_ARRAY(ElemType, size);
  UTILITY_MEMCPY(ElemType, buf, v->begin, leng);
  UTILITY_SWAP(ElemType *, buf, v->begin);
  vector_free(buf);
  v->end = v->last = v->begin + leng;
  while (leng++ < size) {
    *v->last++ = NULL;
  }
  v->capacity = size;
}

Vector *vector_new(Destructor dtor) {
  Vector *v = UTILITY_MALLOC(Vector);
  v->begin = v->end = v->last = (ElemType *)vector_sentinel();
  v->size = v->capacity = 0;
  v->dtor = dtor ? dtor : vector_destructor_default;
  return v;
}
void vector_delete(Vector *v) {
  assert(v);
  vector_clear(v);
  vector_free(v->begin);
  UTILITY_FREE(v);
}
void vector_destruct(Vector *v, ElemType elem) {
  assert(v);
  v->dtor(elem);
}
Bool vector_empty(const Vector *v) {
  assert(v);
  return 0 == vector_length(v);
}
Size vector_length(const Vector *v) {
  assert(v);
  return v->size;
}
Size vector_capacity(const Vector *v) {
  assert(v);
  return v->capacity;
}
ElemType *vector_begin(const Vector *v) {
  assert(v);
  return v->begin;
}
ElemType *vector_end(const Vector *v) {
  assert(v);
  return v->begin + v->size;
}
ElemType vector_front(const Vector *v) {
  assert(v);
  return vector_empty(v) ? NULL : v->begin[0];
}
ElemType vector_back(const Vector *v) {
  assert(v);
  return vector_empty(v) ? NULL : v->begin[v->size - 1];
}
void vector_push(Vector *v, ElemType elem) {
  assert(v);
  if (vector_length(v) == vector_capacity(v)) {
    vector_alloc(v);
  }
  v->begin[v->size] = elem;
  ++v->size;
  ++v->end;
}
void vector_pop(Vector *v) {
  assert(v);
  if (!vector_empty(v)) {
    --v->size;
    --v->end;
    vector_destruct(v, v->begin[v->size]);
    v->begin[v->size] = NULL;
  }
}
void vector_clear(Vector *v) {
  assert(v);
  while (!vector_empty(v)) {
    vector_pop(v);
  }
}
