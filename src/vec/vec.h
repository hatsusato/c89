#ifndef INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E
#define INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E

#include "util/type.h"

struct vec;

struct vec *vec_new(void);
void vec_delete(struct vec *);
index_t vec_capacity(struct vec *);
index_t vec_length(struct vec *);
void *vec_at(struct vec *, index_t);
void *vec_top(struct vec *);
void vec_push(struct vec *, void *);
void vec_pop(struct vec *);
void vec_clear(struct vec *);
void vec_sort(struct vec *, cmp_t);
const void *vec_search(struct vec *, const void *, cmp_t);

void vec_map(struct vec *, map_t);

#endif /* INCLUDE_GUARD_163637DD_0D83_468B_88CC_AEFD8917410E */
