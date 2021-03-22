#include "vector.h"

#include <stdlib.h>

#include "utility/utility.h"

typedef int (*CmpType)(const void *, const void *);

struct struct_Vector {
  VectorElem *begin, *end, *last;
  VectorDestructor dtor;
};

static const VectorElem *vector_sentinel(void) {
  static const VectorElem sentinel = NULL;
  return &sentinel;
}
static void vector_free(VectorElem *buf) {
  if (vector_sentinel() != buf) {
    UTILITY_FREE(buf);
  }
}
static void vector_alloc(Vector *v) {
  VectorElem *buf;
  Size leng = vector_length(v);
  Size size = vector_capacity(v);
  if (leng == size) {
    size += size == 0 ? 8 : size;
    buf = UTILITY_MALLOC_ARRAY(VectorElem, size);
    UTILITY_MEMCPY(VectorElem, buf, v->begin, leng);
    UTILITY_SWAP(VectorElem *, buf, v->begin);
    vector_free(buf);
    v->end = v->last = v->begin + leng;
    while (leng++ < size) {
      *v->last++ = NULL;
    }
  }
}

Vector *vector_new(VectorDestructor dtor) {
  Vector *v = UTILITY_MALLOC(Vector);
  v->begin = v->end = v->last = (VectorElem *)vector_sentinel();
  v->dtor = dtor;
  return v;
}
void vector_delete(Vector *v) {
  vector_clear(v);
  vector_free(v->begin);
  UTILITY_FREE(v);
}
void vector_destruct(const Vector *v, VectorElem elem) {
  if (v->dtor) {
    v->dtor(elem);
  }
}
Bool vector_empty(const Vector *v) {
  return v->end == v->begin;
}
Size vector_length(const Vector *v) {
  return v->end - v->begin;
}
Size vector_capacity(const Vector *v) {
  return v->last - v->begin;
}
VectorElem *vector_begin(const Vector *v) {
  return v->begin;
}
VectorElem *vector_end(const Vector *v) {
  return v->end;
}
VectorElem vector_front(const Vector *v) {
  return vector_empty(v) ? NULL : v->begin[0];
}
VectorElem vector_back(const Vector *v) {
  return vector_empty(v) ? NULL : v->end[-1];
}
VectorElem vector_at(const Vector *v, Index i) {
  assert(0 <= i && i < vector_length(v));
  return v->begin[i];
}
void vector_push(Vector *v, VectorElem elem) {
  vector_alloc(v);
  *v->end++ = elem;
}
void vector_pop(Vector *v) {
  if (!vector_empty(v)) {
    --v->end;
    vector_destruct(v, *v->end);
    *v->end = NULL;
  }
}
void vector_clear(Vector *v) {
  while (!vector_empty(v)) {
    vector_pop(v);
  }
}
void vector_sort(Vector *v, VectorCmp cmp) {
  VectorElem *base = vector_begin(v);
  Size len = vector_length(v);
  qsort(base, len, sizeof(VectorElem), (CmpType)cmp);
}
ConstGeneric vector_search(const Vector *v, ConstGeneric key, VectorCmp cmp) {
  VectorElem *base = vector_begin(v);
  Size len = vector_length(v);
  const ConstGeneric *found =
      bsearch(&key, base, len, sizeof(VectorElem), (CmpType)cmp);
  return found ? *found : NULL;
}
