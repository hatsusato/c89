#include "pool.h"

#include <string.h>

#include "set.h"
#include "utility.h"

static void pool_destructor(ElemType elem) {
  UTILITY_FREE(elem);
}
static int pool_compare(const ElemType *lhs, const ElemType *rhs) {
  return strcmp(*lhs, *rhs);
}
static char *duplicate_string(const char *text, Size size) {
  char *buf = UTILITY_MALLOC_ARRAY(char, size + 1);
  UTILITY_MEMCPY(char, buf, text, size);
  buf[size] = '\0';
  return buf;
}

Pool *pool_new(void) {
  return set_new(pool_destructor, pool_compare);
}
void pool_delete(Pool *pool) {
  set_delete(pool);
}
const char *pool_insert(Pool *pool, const char *text, Size size) {
  return set_insert(pool, duplicate_string(text, size));
}
Bool pool_contains(Pool *pool, const char *str) {
  return set_contains(pool, (ElemType)str);
}
