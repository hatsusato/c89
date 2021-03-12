#include "pool.h"

#include "set/set.h"
#include "utility/utility.h"

struct struct_Pool {
  Set *set;
};

Pool *pool_new(VectorDestructor dtor, Compare *compare) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->set = set_new(dtor, compare);
  return pool;
}
void pool_delete(Pool *pool) {
  set_delete(pool->set);
  UTILITY_FREE(pool);
}
void pool_clear(Pool *pool) {
  set_clear(pool->set);
}
void pool_insert(Pool *pool, CompareElem elem) {
  set_insert(pool->set, elem);
}
const VectorElem *pool_find(Pool *pool, CompareElem elem) {
  return (const VectorElem *)set_find(pool->set, elem);
}
