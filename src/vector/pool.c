#include "vector/pool.h"

#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *pool;
};

static void pool_destructor(ElemType elem) {
  UTILITY_FREE(elem);
}

Pool *pool_new(void) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vector_new(pool_destructor);
  return pool;
}
void pool_delete(Pool *pool) {
  vector_delete(pool->pool);
  UTILITY_FREE(pool);
}
