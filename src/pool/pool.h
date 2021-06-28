#ifndef INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6
#define INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6

#include "util/buffer.h"

struct pool {
  struct buffer buf;
  size_t offset;
};

void pool_malloc(struct pool *, size_t);
void pool_free(struct pool *);
const void *pool_insert(struct pool *, const struct buffer *);

#endif /* INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6 */
