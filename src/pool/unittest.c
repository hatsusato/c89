#include "unittest.h"

#include <assert.h>

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
  int *p = pool_insert2(pool, sizeof(int) * len);
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

void pool_str_unittest(void) {
  struct pool *pool = pool_new();
  struct pool_str spool;
  struct vec expect, *actual;
  const char *ab = "ababababab";
  int i, j;
  pool_str_init(&spool, pool);
  for (i = 0; i < 10; i++) {
    pool_str_insert(&spool, ab + i);
  }
  for (i = 0; i < 6; i++) {
    struct str_view str;
    for (j = 0; j <= 10 - i; j++) {
      str_view_init(&str, ab + i, j);
      pool_str_canonicalize(&spool, &str);
    }
  }
  actual = &spool.table;
  vec_init(&expect, sizeof(struct str_view));
  assert(vec_length(actual) == 20);
  for (i = 0; i <= 10; i++) {
    struct str_view str;
    str_view_init(&str, ab, i);
    vec_push(&expect, &str);
  }
  for (i = 0; i < 9; i++) {
    struct str_view str;
    str_view_init(&str, ab + 1, i + 1);
    vec_push(&expect, &str);
  }
  for (i = 0; i < 20; i++) {
    struct str_view *lhs, *rhs;
    lhs = vec_at(actual, i);
    rhs = vec_at(&expect, i);
    assert(str_view_cmp(lhs, rhs) == 0);
  }
  vec_finish(&expect);
  pool_str_finish(&spool);
  pool_delete(pool);
}
