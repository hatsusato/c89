#ifndef INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D
#define INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D

#include "util/type.h"

struct slice;
struct vec;

void vec_init(struct vec *, align_t);
void vec_finish(struct vec *);
void vec_reserve(struct vec *, index_t);
index_t vec_capacity(const struct vec *);
index_t vec_length(const struct vec *);
const struct slice *vec_slice(const struct vec *);
struct array *vec_get_array(struct vec *);
void *vec_at(struct vec *, index_t);
void vec_insert(struct vec *, index_t, const struct slice *);
void vec_remove(struct vec *, index_t, index_t);
void vec_push(struct vec *, const void *);
void vec_pop(struct vec *);
void vec_clear(struct vec *);
void vec_sort(struct vec *, cmp_t);
void *vec_search(const struct vec *, const void *, cmp_t);
void vec_map(struct vec *, void (*)(void *));

#endif /* INCLUDE_GUARD_C9808F6F_7A34_4226_A18A_9B7E94B05A1D */
