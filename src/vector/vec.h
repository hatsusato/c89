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
void vec_delete(struct vec *);
size_t vec_length(const struct vec *);
bool_t vec_empty(const struct vec *);
void *vec_begin(struct vec *);
void *vec_end(struct vec *);
void *vec_at(struct vec *, index_t);

#endif /* INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D */
