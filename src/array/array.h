#ifndef INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70
#define INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70

#include "util/slice.h"

struct buffer;
struct range;
struct slice;

struct array {
  struct slice slice;
};

void array_init(struct array *, align_t, struct buffer *);
void array_slice(struct array *, struct slice *);
bool_t array_is_null(const struct array *);
align_t array_align(const struct array *);
index_t array_length(const struct array *);
void *array_at(struct array *, index_t);
void array_insert(struct array *, const struct range *, const struct slice *);
void array_remove(struct array *, const struct range *);
void array_push(struct array *, const struct slice *);
void array_pop(struct array *);
void array_clear(struct array *);
void array_sort(struct array *, cmp_t);
void *array_search(const struct array *, const void *, cmp_t);
void array_map(struct array *, void (*)(void *));

#endif /* INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70 */
