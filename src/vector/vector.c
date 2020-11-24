#include "vector.h"

#include "utility.h"

struct struct_Vector {
  ElemType *begin, *end, *last;
  Destructor dtor;
};

static const ElemType *vector_sentinel(void) {
  static const ElemType sentinel = NULL;
  return &sentinel;
}
static void vector_free(ElemType *buf) {
  if (vector_sentinel() != buf) {
    UTILITY_FREE(buf);
  }
}
static void vector_alloc(Vector *v) {
  ElemType *buf;
  Size leng = vector_length(v);
  Size size = vector_capacity(v);
  if (leng == size) {
    size += size == 0 ? 8 : size;
    buf = UTILITY_MALLOC_ARRAY(ElemType, size);
    UTILITY_MEMCPY(ElemType, buf, v->begin, leng);
    UTILITY_SWAP(ElemType *, buf, v->begin);
    vector_free(buf);
    v->end = v->last = v->begin + leng;
    while (leng++ < size) {
      *v->last++ = NULL;
    }
  }
}

Vector *vector_new(Destructor dtor) {
  Vector *v = UTILITY_MALLOC(Vector);
  v->begin = v->end = v->last = (ElemType *)vector_sentinel();
  v->dtor = dtor;
  return v;
}
void vector_delete(Vector *v) {
  assert(v);
  vector_clear(v);
  vector_free(v->begin);
  UTILITY_FREE(v);
}
void vector_destruct(const Vector *v, ElemType elem) {
  assert(v);
  if (v->dtor) {
    v->dtor(elem);
  }
}
Bool vector_empty(const Vector *v) {
  assert(v);
  return v->end == v->begin;
}
Size vector_length(const Vector *v) {
  assert(v);
  return v->end - v->begin;
}
Size vector_capacity(const Vector *v) {
  assert(v);
  return v->last - v->begin;
}
ElemType *vector_begin(const Vector *v) {
  assert(v);
  return v->begin;
}
ElemType *vector_end(const Vector *v) {
  assert(v);
  return v->end;
}
ElemType vector_front(const Vector *v) {
  assert(v);
  return vector_empty(v) ? NULL : v->begin[0];
}
ElemType vector_back(const Vector *v) {
  assert(v);
  return vector_empty(v) ? NULL : v->end[-1];
}
void vector_push(Vector *v, ElemType elem) {
  assert(v);
  vector_alloc(v);
  *v->end++ = elem;
}
void vector_pop(Vector *v) {
  assert(v);
  if (!vector_empty(v)) {
    --v->end;
    vector_destruct(v, *v->end);
    *v->end = NULL;
  }
}
void vector_clear(Vector *v) {
  assert(v);
  while (!vector_empty(v)) {
    vector_pop(v);
  }
}
