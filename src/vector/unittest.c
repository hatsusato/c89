#include "unittest.h"

#include <assert.h>

#include "utility/buffer.h"
#include "vec.h"

static void vec_unittest_check(struct vec *vec, size_t len, size_t cap) {
  assert(vec_length(vec) == len);
  assert(vec_capacity(vec) == cap);
}
static void vec_unittest_push(struct vec *vec, int count) {
  int i;
  size_t len = vec_length(vec);
  for (i = 0; i < count; i++) {
    struct buffer buf;
    BUFFER_INIT(&buf, &i);
    if (vec_full(vec)) {
      vec_reserve(vec, 0);
    }
    vec_push(vec, &buf);
  }
  assert(vec_length(vec) == len + count);
}
static void vec_unittest_pop(struct vec *vec, int count) {
  int i;
  size_t len = vec_length(vec);
  for (i = 0; i < count; i++) {
    vec_pop(vec, NULL);
  }
  assert(vec_length(vec) == len - count);
}
static void vec_unittest_range(struct vec *vec, int start, int begin, int end) {
  int i, j;
  for (i = start, j = begin; j < end; i++, j++) {
    int *p = vec_at(vec, i);
    assert(*p == j);
  }
}

void vec_unittest(void) {
  struct vec *vec = vec_new(8);
  struct buffer buf;
  int i;
  vec_unittest_check(vec, 0, 0);
  assert(sizeof(int) < 8);
  vec_reserve(vec, 8);
  vec_unittest_check(vec, 0, 8);
  vec_unittest_push(vec, 1000);
  vec_unittest_check(vec, 1000, 1024);
  vec_unittest_range(vec, 0, 0, 1000);
  vec_unittest_check(vec, 1000, 1024);
  vec_unittest_pop(vec, 500);
  vec_unittest_check(vec, 500, 1024);
  vec_unittest_range(vec, 0, 0, 500);
  for (i = 0; i < 1000; i++) {
    BUFFER_INIT(&buf, &i);
    if (vec_full(vec)) {
      vec_reserve(vec, 0);
    }
    vec_push(vec, &buf);
  }
  vec_unittest_range(vec, 0, 0, 500);
  vec_unittest_range(vec, 500, 0, 1000);
  vec_delete(vec);
}
