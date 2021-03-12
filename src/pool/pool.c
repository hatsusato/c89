#include "pool.h"

#include "set/set.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Pool {
  Vector *vec;
  Set *set;
};

Pool *pool_new(VectorDestructor dtor, Compare *compare) {
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
void pool_clear(Pool *pool) {
  set_clear(pool->set);
  vector_clear(pool->vec);
}
void pool_insert(Pool *pool, CompareElem elem) {
  vector_push(pool->vec, (VectorElem)elem);
  set_insert(pool->set, elem);
}
const VectorElem *pool_find(Pool *pool, CompareElem elem) {
  return (const VectorElem *)set_find(pool->set, elem);
}
