#include "unittest.h"

#include <assert.h>

#include "pool.h"
#include "str.h"
#include "str/str.h"
#include "util/box.h"
#include "util/buffer.h"
#include "vec/vec.h"

const int *pool_unittest_set(struct pool *pool, int len) {
  int i;
  struct box *box;
  struct buffer buf;
  const int *p;
  box = box_new(sizeof(int), len);
  box_buffer(box, &buf);
  for (i = 0; i < len; i++) {
    int *p = buffer_at(&buf, sizeof(int) * i);
    *p = i;
  }
  p = pool_insert(pool, box);
  return p;
}
void pool_unittest_check(const int *p, int len) {
  int i;
  for (i = 0; i < len; i++) {
    assert(p[i] == i);
  }
}

void pool_unittest(void) {
  struct pool pool;
  int i, j;
  pool_new(&pool);
  for (i = 0, j = 1; i < 16; i++, j *= 2) {
    const int *p = pool_unittest_set(&pool, j);
    pool_unittest_check(p, i);
  }
  pool_delete(&pool);
}

void pool_str_unittest(void) {
  struct pool_str pool;
  struct vec expect, *actual;
  const char *ab = "ababababab";
  int i, j;
  pool_str_new(&pool);
  for (i = 0; i < 6; i++) {
    struct str str;
    for (j = 0; j <= 10 - i; j++) {
      str_init(&str, ab + i, j);
      pool_str_insert(&pool, &str);
    }
  }
  actual = &pool.table;
  vec_new(&expect, sizeof(struct str));
  assert(vec_length(actual) == 20);
  for (i = 0; i <= 10; i++) {
    struct str str;
    str_init(&str, ab, i);
    vec_push(&expect, &str);
  }
  for (i = 0; i < 9; i++) {
    struct str str;
    str_init(&str, ab + 1, i + 1);
    vec_push(&expect, &str);
  }
  for (i = 0; i < 20; i++) {
    struct str *lhs, *rhs;
    lhs = vec_at(actual, i);
    rhs = vec_at(&expect, i);
    assert(str_cmp(lhs, rhs) == 0);
  }
  vec_delete(&expect);
  pool_str_delete(&pool);
}
