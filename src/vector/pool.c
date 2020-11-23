#include "vector/pool.h"

#include "utility.h"
#include "vector.h"

struct struct_Pool {
  Vector *pool;
};
typedef struct {
  Size size;
  const Byte *buf;
} Entry;

static Entry *entry_constructor(const void *buf, Size size) {
  Entry *entry = UTILITY_MALLOC(Entry);
  entry->size = size;
  entry->buf = UTILITY_MALLOC_ARRAY(Byte, size);
  UTILITY_MEMCPY(Byte, (Byte *)entry->buf, buf, size);
  return entry;
}
static void entry_destructor(ElemType elem) {
  Entry *entry = elem;
  Byte *buf = (Byte *)entry->buf;
  UTILITY_FREE(buf);
  UTILITY_FREE(elem);
}
static int entry_compare(const ElemType *l, const ElemType *r) {
  Entry *lhs = *l;
  Entry *rhs = *r;
  int diff = lhs->size - rhs->size;
  int ret = memcmp(lhs->buf, rhs->buf, 0 < diff ? lhs->size : rhs->size);
  return 0 == ret ? diff : ret;
}
static const ElemType *pool_find(Pool *pool, const void *buf, Size size) {
  const ElemType *it;
  const ElemType *begin = vector_begin(pool->pool);
  const ElemType *end = vector_end(pool->pool);
  Entry entry;
  ElemType key = &entry;
  entry.size = size;
  entry.buf = buf;
  for (it = begin; it != end; ++it) {
    if (entry_compare(it, &key)) {
      return it;
    }
  }
  return NULL;
}

Pool *pool_new(void) {
  Pool *pool = UTILITY_MALLOC(Pool);
  pool->pool = vector_new(entry_destructor);
  return pool;
}
void pool_delete(Pool *pool) {
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
  }
  return entry->buf;
}
