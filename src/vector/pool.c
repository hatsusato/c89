#include "vector/pool.h"

#include "compare.h"
#include "set/sort.h"
#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *pool;
  Compare *cmp;
};
typedef struct {
  Size size;
  const Byte *buf;
} Entry;

static Entry *entry_constructor(const void *buf, Size size) {
  Entry *entry = UTILITY_MALLOC(Entry);
  entry->size = size;
  entry->buf = UTILITY_MALLOC_ARRAY(Byte, size);
  UTILITY_MEMCPY(Byte, entry->buf, buf, size);
  return entry;
}
static void entry_destructor(ElemType elem) {
  Entry *entry = elem;
  UTILITY_FREE(entry->buf);
  UTILITY_FREE(entry);
}
static int pool_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  const Entry *l = lhs, *r = rhs;
  const Size lsz = l->size, rsz = r->size;
  int ret = utility_memcmp(l->buf, r->buf, lsz < rsz ? lsz : rsz);
  (void)extra;
  return 0 == ret ? lsz - rsz : ret;
}
static const ElemType *pool_find(Pool *pool, const void *buf, Size size) {
  ElemType *begin = vector_begin(pool->pool);
  ElemType *end = vector_end(pool->pool);
  Entry key;
  key.size = size;
  key.buf = buf;
  return binary_search(&key, begin, end, pool->cmp);
}
static void pool_sort(Pool *pool) {
  ElemType *begin = vector_begin(pool->pool);
  ElemType *end = vector_end(pool->pool);
  quick_sort(begin, end, pool->cmp);
}

Pool *pool_new(void) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vector_new(entry_destructor);
  pool->cmp = compare_new(pool_compare);
  return pool;
}
void pool_delete(Pool *pool) {
  compare_delete(pool->cmp);
  vector_delete(pool->pool);
  UTILITY_FREE(pool);
}
const void *pool_insert(Pool *pool, const void *buf, Size size) {
  const ElemType *found = pool_find(pool, buf, size);
  Entry *entry;
  if (found) {
    entry = *found;
  } else {
    entry = entry_constructor(buf, size);
    vector_push(pool->pool, entry);
    pool_sort(pool);
  }
  return entry->buf;
}
