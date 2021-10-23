#include "unittest.h"

#include <assert.h>

#include "any.h"
#include "pool.h"
#include "str.h"
#include "str/view.h"
#include "str/view_type.h"
#include "str_type.h"
#include "type.h"
#include "util/box.h"
#include "util/buffer.h"
#include "vec/vec.h"

const int *pool_unittest_set(struct pool *pool, int len) {
  int i;
  int *p = pool_insert(pool, sizeof(int), len);
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
    pool_unittest_check(p, i);
  }
  pool_delete(pool);
}

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
