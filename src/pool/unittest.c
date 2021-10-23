#include "unittest.h"

#include <assert.h>

#include "any.h"

const int *pool_any_unittest_set(struct pool_any *pool, int len) {
  int i;
  int *p = pool_any_alloc(pool, sizeof(int) * len);
  for (i = 0; i < len; i++) {
    p[i] = i;
  }
  return p;
}
void pool_any_unittest_check(const int *p, int len) {
  int i;
  for (i = 0; i < len; i++) {
    assert(p[i] == i);
  }
}
void pool_any_unittest(void) {
  struct pool_any *pool = pool_any_new();
  int i, j;
  for (i = 0, j = 1; i < 16; i++, j *= 2) {
    const int *p = pool_any_unittest_set(pool, j);
    pool_any_unittest_check(p, j);
  }
  pool_any_delete(pool);
}
