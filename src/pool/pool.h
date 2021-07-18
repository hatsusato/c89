#ifndef INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6
#define INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6

#include "util/type.h"

struct pool;

struct pool *pool_new(void);
void pool_delete(struct pool *);
void *pool_insert(struct pool *, align_t, index_t);

#endif /* INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6 */
