#include "vector/pool.h"

#include "compare.h"
#include "set/sort.h"
#include "types.h"
#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *pool;
  Compare *cmp;
};

static const char *entry_constructor(const void *buf, Size size) {
  char *entry = UTILITY_MALLOC_ARRAY(char, size);
  UTILITY_MEMCPY(Byte, entry, buf, size);
  return entry;
}
static void entry_destructor(ElemType elem) {
  UTILITY_FREE(elem);
}
static void pool_sort(Pool *pool) {
  ElemType *begin = vector_begin(pool->pool);
  ElemType *end = vector_end(pool->pool);
  quick_sort(begin, end, pool->cmp);
}

Pool *pool_new(Compare *cmp) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vector_new(entry_destructor);
  pool->cmp = cmp;
  return pool;
}
void pool_delete(Pool *pool) {
  compare_delete(pool->cmp);
  vector_delete(pool->pool);
  UTILITY_FREE(pool);
}
const void *pool_insert(Pool *pool, const void *buf, Size size) {
  const char *entry = entry_constructor(buf, size);
  vector_push(pool->pool, (ElemType)entry);
  pool_sort(pool);
  return entry;
}
const ElemType *pool_find(Pool *pool, const void *buf, Size size) {
  ElemType *begin = vector_begin(pool->pool);
  ElemType *end = vector_end(pool->pool);
  (void)size;
  return binary_search((ElemType)buf, begin, end, pool->cmp);
}
