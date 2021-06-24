#ifndef INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70
#define INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70

#include "util/buffer.h"

struct array {
  align_t align;
  struct buffer buf;
  index_t len;
};

void array_init(struct array *, align_t, struct buffer *);
align_t array_align(const struct array *);
index_t array_capacity(const struct array *);
index_t array_length(const struct array *);
void *array_at(struct array *, index_t);

#endif /* INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70 */
