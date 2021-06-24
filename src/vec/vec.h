#ifndef INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D
#define INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D

#include "util/type.h"

struct vec;

struct vec *vec_new(align_t);
void vec_delete(struct vec *);
void vec_init(struct vec *, align_t);
void vec_malloc(struct vec *, index_t);
void vec_free(struct vec *);
void vec_reserve(struct vec *, index_t);
index_t vec_capacity(const struct vec *);
index_t vec_length(const struct vec *);
void *vec_at(struct vec *, index_t);
void vec_insert(struct vec *, index_t, index_t, const struct buffer *);
void vec_remove(struct vec *, index_t, index_t);

bool_t vec_empty(const struct vec *);
bool_t vec_full(const struct vec *);
void *vec_begin(struct vec *);
void *vec_end(struct vec *);
void vec_clear(struct vec *);

#endif /* INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D */
