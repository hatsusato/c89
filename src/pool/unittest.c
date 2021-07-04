#include "unittest.h"

#include <assert.h>

#include "pool.h"
#include "str.h"
#include "str/str.h"
#include "util/buffer.h"
#include "vec/vec.h"

#define pool_unittest_set_buffer(buf, len)      \
  do {                                          \
    int i;                                      \
    buffer_malloc(buf, sizeof(int) * len);      \
    for (i = 0; i < len; i++) {                 \
      int *p = buffer_at(buf, sizeof(int) * i); \
      *p = i;                                   \
    }                                           \
  } while (false)
#define pool_unittest_check(p, len) \
  do {                              \
    int i;                          \
    for (i = 0; i < len; i++) {     \
      assert(p[i] == i);            \
    }                               \
  } while (false)

void pool_unittest(void) {
  struct pool pool;
  struct buffer buf;
  const int *p10, *p100, *p1000;
  pool_new(&pool);
  pool_unittest_set_buffer(&buf, 10);
  p10 = pool_insert(&pool, &buf);
  buffer_free(&buf);
  pool_unittest_set_buffer(&buf, 100);
  p100 = pool_insert(&pool, &buf);
  buffer_free(&buf);
  pool_unittest_set_buffer(&buf, 1000);
  p1000 = pool_insert(&pool, &buf);
  buffer_free(&buf);
  pool_unittest_check(p10, 10);
  pool_unittest_check(p100, 100);
  pool_unittest_check(p1000, 1000);
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
