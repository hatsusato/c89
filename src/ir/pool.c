#include "ir/pool.h"

#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *pool;
};

Pool *pool_new(void) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vector_new(utility_free);
  return pool;
}
void pool_delete(Pool *pool) {
  vector_delete(pool->pool);
  UTILITY_FREE(pool);
}
