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
  pool->set = set_new(compare);
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
void pool_insert(Pool *pool, ElemType elem) {
  vector_push(pool->vec, elem);
  set_insert(pool->set, elem);
}
const ElemType *pool_find(Pool *pool, ElemType elem) {
  return set_find(pool->set, elem);
}
