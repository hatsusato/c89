#ifndef INCLUDE_GUARD_D300EE6C_9C63_45F4_9599_FB398D4BE800
#define INCLUDE_GUARD_D300EE6C_9C63_45F4_9599_FB398D4BE800

struct pool;
struct pool_str;
struct str;

void pool_str_init(struct pool_str *, struct pool *);
void pool_str_finish(struct pool_str *);
const char *pool_str_insert(struct pool_str *, const struct str *);

#endif /* INCLUDE_GUARD_D300EE6C_9C63_45F4_9599_FB398D4BE800 */
