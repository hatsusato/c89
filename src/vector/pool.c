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
  Entry *entry = entry_constructor(buf, size);
  vector_push(pool->pool, entry);
  return entry->buf;
}
