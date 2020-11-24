#include "vector/pool.h"

#include <stdlib.h>

#include "compare.h"
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
  UTILITY_FREE(elem);
}
static int entry_compare(const void *l, const void *r) {
  const Entry *lhs = *(const Entry **)l;
  const Entry *rhs = *(const Entry **)r;
  const Size lsz = lhs->size, rsz = rhs->size;
  int ret = utility_memcmp(lhs->buf, rhs->buf, lsz < rsz ? lsz : rsz);
  return 0 == ret ? lsz - rsz : ret;
}
static int pool_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  const Entry *l = lhs, *r = rhs;
  const Size lsz = l->size, rsz = r->size;
  int ret = utility_memcmp(l->buf, r->buf, lsz < rsz ? lsz : rsz);
  (void)extra;
  return 0 == ret ? lsz - rsz : ret;
}
static const ElemType *pool_find(Pool *pool, const void *buf, Size size) {
  const ElemType *data = vector_begin(pool->pool);
  size_t count = vector_length(pool->pool);
  Entry entry;
  ElemType key = &entry;
  entry.size = size;
  entry.buf = buf;
  return bsearch(&key, data, count, sizeof(ElemType), entry_compare);
}
static void pool_sort(Pool *pool) {
  ElemType *data = vector_begin(pool->pool);
  size_t count = vector_length(pool->pool);
  qsort(data, count, sizeof(ElemType), entry_compare);
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
