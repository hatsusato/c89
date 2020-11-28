#include "ir/pool.h"

#include "ir/value.h"
#include "types.h"
#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *pool;
};

Pool *pool_new(void) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vector_new((Destructor)value_delete);
  return pool;
}
void pool_delete(Pool *pool) {
  vector_delete(pool->pool);
  UTILITY_FREE(pool);
}
