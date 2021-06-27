#ifndef INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70
#define INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70

#include "util/slice.h"

struct array {
  struct slice slice;
};

void array_init(struct array *, align_t, void *);
const struct slice *array_slice(const struct array *);
align_t array_align(const struct array *);
index_t array_length(const struct array *);
void *array_at(struct array *, index_t);
void array_insert(struct array *, index_t, const struct slice *);
void array_remove(struct array *, index_t, index_t);
void array_sort(struct array *, cmp_t);
void *array_search(const struct array *, const void *, cmp_t);

#endif /* INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70 */
