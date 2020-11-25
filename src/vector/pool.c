#include "vector/pool.h"

#include "compare.h"
#include "set/sort.h"
#include "types.h"
#include "utility.h"

struct struct_Pool {
  Vector *pool;
  Compare *cmp;
};

static void pool_sort(Pool *pool) {
  ElemType *begin = vector_begin(pool->pool);
  ElemType *end = vector_end(pool->pool);
  quick_sort(begin, end, pool->cmp);
}

Pool *pool_new(Vector *vec, Compare *cmp) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vec;
  pool->cmp = cmp;
  return pool;
}
void pool_delete(Pool *pool) {
  compare_delete(pool->cmp);
  vector_delete(pool->pool);
  UTILITY_FREE(pool);
}
void pool_insert(Pool *pool, ElemType elem) {
  vector_push(pool->pool, elem);
  pool_sort(pool);
}
const ElemType *pool_find(Pool *pool, ElemType key) {
  ElemType *begin = vector_begin(pool->pool);
  ElemType *end = vector_end(pool->pool);
  return binary_search(key, begin, end, pool->cmp);
}
