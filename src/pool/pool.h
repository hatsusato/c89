#ifndef INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6
#define INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6

struct box;
struct pool;

struct pool *pool_new(void);
void pool_delete(struct pool *);
void *pool_insert(struct pool *, struct box *);

#endif /* INCLUDE_GUARD_FD4CDA16_28C2_418A_84F7_67EFEEE7B0B6 */
