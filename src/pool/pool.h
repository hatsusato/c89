#ifndef INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6
#define INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6

struct box;
struct pool;

void pool_init(struct pool *);
void pool_finish(struct pool *);
const void *pool_insert(struct pool *, struct box *);

#endif /* INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6 */
