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

Pool *pool_new(void) {
  return set_new(pool_destructor, pool_compare);
}
void pool_delete(Pool *pool) {
  set_delete(pool);
}
