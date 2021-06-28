#include "unittest.h"

#include <assert.h>

#include "pool.h"
#include "util/buffer.h"

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
