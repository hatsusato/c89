#ifndef INCLUDE_GUARD_C229D27C_DE8E_4AE2_A417_79D5A6C324D7
#define INCLUDE_GUARD_C229D27C_DE8E_4AE2_A417_79D5A6C324D7

#include "util/type.h"

struct array;

void array_init(struct array *, align_t);
void array_finish(struct array *);
void array_resize(struct array *, index_t);
void array_set(struct array *, void *, index_t);
void *array_at(struct array *, index_t);
void array_insert(struct array *, const void *, index_t);
void array_remove(struct array *, index_t);
void array_sort(struct array *, cmp_t);
void *array_search(struct array *, const void *, cmp_t);

#endif /* INCLUDE_GUARD_C229D27C_DE8E_4AE2_A417_79D5A6C324D7 */
