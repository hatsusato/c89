#ifndef INCLUDE_GUARD_D300EE6C_9C63_45F4_9599_FB398D4BE800
#define INCLUDE_GUARD_D300EE6C_9C63_45F4_9599_FB398D4BE800

#include "vec/type.h"

struct pool_str {
  struct vec pool, table, big;
};

void pool_str_new(struct pool_str *);
void pool_str_delete(struct pool_str *);

#endif /* INCLUDE_GUARD_D300EE6C_9C63_45F4_9599_FB398D4BE800 */
