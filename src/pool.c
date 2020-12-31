#include "pool.h"

#include "set.h"
#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *vec;
  Set *set;
};

Pool *pool_new(Destructor dtor, Compare *compare) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->vec = vector_new(dtor);
  pool->set = set_new(NULL, compare);
  return pool;
}
void pool_delete(Pool *pool) {
  set_delete(pool->set);
  vector_delete(pool->vec);
  UTILITY_FREE(pool);
}
