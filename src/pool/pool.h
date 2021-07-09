#ifndef INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6
#define INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6

#include "vec/type.h"

struct buffer;

struct pool {
  struct vec_ptr vec;
};

void pool_new(struct pool *);
void pool_delete(struct pool *);
const void *pool_insert(struct pool *, const struct buffer *);

#endif /* INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6 */
