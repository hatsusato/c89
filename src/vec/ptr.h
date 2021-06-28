#ifndef INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E
#define INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E

#include "util/type.h"

struct vec_ptr;

void vec_ptr_new(struct vec_ptr *, void (*)(void *));
void vec_ptr_delete(struct vec_ptr *);
index_t vec_ptr_capacity(struct vec_ptr *);
index_t vec_ptr_length(struct vec_ptr *);
void *vec_ptr_at(struct vec_ptr *, index_t);
void *vec_ptr_top(struct vec_ptr *);
void vec_ptr_push(struct vec_ptr *, void *);
void vec_ptr_pop(struct vec_ptr *);
void vec_ptr_clear(struct vec_ptr *);
void vec_ptr_map(struct vec_ptr *, void (*)(void *));

#endif /* INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E */
