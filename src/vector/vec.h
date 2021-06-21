#ifndef INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D
#define INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D

#include "span.h"

struct buffer;
struct vec {
  struct vector_span span;
  size_t capacity;
};

void vec_init(struct vec *, size_t, struct buffer *);
struct vec *vec_create(size_t);

#endif /* INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D */
