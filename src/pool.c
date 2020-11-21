#include "pool.h"

#include <string.h>

#include "set.h"
#include "utility.h"

static int pool_compare(const ElemType *lhs, const ElemType *rhs) {
  return strcmp(*lhs, *rhs);
}

Pool *pool_new(Destructor dtor) {
  return set_new(dtor, pool_compare);
}
void pool_delete(Pool *pool) {
  set_delete(pool);
}
const char *pool_construct(const char *text, Size size) {
  char *buf = UTILITY_MALLOC_ARRAY(char, size + 1);
  UTILITY_MEMCPY(char, buf, text, size);
  buf[size] = '\0';
  return buf;
}
void pool_destruct(ElemType elem) {
  UTILITY_FREE(elem);
}
const char *pool_insert(Pool *pool, const char *str) {
  return set_insert(pool, (ElemType)str);
}
Bool pool_contains(Pool *pool, const char *str) {
  return set_contains(pool, (ElemType)str);
}
