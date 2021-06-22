#ifndef INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D
#define INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D

#include "span.h"

struct buffer;
struct vec {
  struct vector_span span;
  size_t capacity;
};

align_t vector_aligned_size(size_t);
void vec_init(struct vec *, struct buffer *);
void vec_init_malloc(struct vec *, size_t);
struct vec *vec_new(size_t);
struct vec *vec_create(size_t);
void vec_delete(struct vec *);
void vec_reserve(struct vec *, size_t, struct buffer *);
size_t vec_capacity(const struct vec *);
size_t vec_length(const struct vec *);
bool_t vec_empty(const struct vec *);
bool_t vec_full(const struct vec *);
void *vec_begin(struct vec *);
void *vec_end(struct vec *);
void *vec_at(struct vec *, index_t);
void vec_push(struct vec *, const struct buffer *);
void vec_pop(struct vec *, struct buffer *);
void vec_copy(struct vec *, const struct vec *);
void vec_clear(struct vec *);

#endif /* INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D */
