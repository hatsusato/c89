#include "set/pool.h"

#include "compare.h"
#include "set/sort.h"
#include "types.h"
#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *vec;
  Compare *cmp;
};

static void pool_sort(Pool *pool) {
  ElemType *begin = vector_begin(pool->vec);
  ElemType *end = vector_end(pool->vec);
  quick_sort(begin, end, pool->cmp);
}

Pool *pool_new(Vector *vec, Compare *cmp) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->vec = vec;
  pool->cmp = cmp;
  return pool;
}
void pool_delete(Pool *pool) {
  compare_delete(pool->cmp);
  vector_delete(pool->vec);
  UTILITY_FREE(pool);
}
void pool_insert(Pool *pool, ElemType elem) {
  vector_push(pool->vec, elem);
  pool_sort(pool);
}
const ElemType *pool_find(Pool *pool, ElemType key) {
  ElemType *begin = vector_begin(pool->vec);
  ElemType *end = vector_end(pool->vec);
  return binary_search(key, begin, end, pool->cmp);
}
