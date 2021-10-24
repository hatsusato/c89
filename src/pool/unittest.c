#include "unittest.h"

#include "pool.h"
#include "util/util.h"

const int *pool_unittest_set(struct pool *pool, int len) {
  int i;
  int *p = pool_alloc(pool, sizeof(int) * len);
  for (i = 0; i < len; i++) {
    p[i] = i;
  }
  return p;
}
void pool_unittest_check(const int *p, int len) {
  int i;
  for (i = 0; i < len; i++) {
    assert(p[i] == i);
  }
}
void pool_unittest(void) {
  struct pool *pool = pool_new();
  int i, j;
  for (i = 0, j = 1; i < 16; i++, j *= 2) {
    const int *p = pool_unittest_set(pool, j);
    pool_unittest_check(p, j);
  }
  pool_delete(pool);
}
