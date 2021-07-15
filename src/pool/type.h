#ifndef INCLUDE_GUARD_70E6EF5A_3885_49EF_9245_5EC21F7B08D1
#define INCLUDE_GUARD_70E6EF5A_3885_49EF_9245_5EC21F7B08D1

#include "vec/ptr_type.h"
#include "vec/type.h"

struct pool {
  struct vec_ptr vec;
};

struct pool_str {
  struct pool *pool;
  struct vec table;
};

#endif /* INCLUDE_GUARD_70E6EF5A_3885_49EF_9245_5EC21F7B08D1 */
