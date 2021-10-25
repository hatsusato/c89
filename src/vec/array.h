#ifndef INCLUDE_GUARD_C229D27C_DE8E_4AE2_A417_79D5A6C324D7
#define INCLUDE_GUARD_C229D27C_DE8E_4AE2_A417_79D5A6C324D7

#include "util/type.h"

struct vec_array;

void vec_array_init(struct vec_array *, align_t);
void vec_array_finish(struct vec_array *);
void vec_array_resize(struct vec_array *, index_t);
void vec_array_set(struct vec_array *, void *, index_t);
void *vec_array_at(struct vec_array *, index_t);
void vec_array_insert(struct vec_array *, const void *, index_t);
void vec_array_remove(struct vec_array *, index_t);
void vec_array_sort(struct vec_array *, cmp_t);
void *vec_array_search(struct vec_array *, const void *, cmp_t);

#endif /* INCLUDE_GUARD_C229D27C_DE8E_4AE2_A417_79D5A6C324D7 */
