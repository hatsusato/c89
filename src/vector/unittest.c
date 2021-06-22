#include "unittest.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "utility/buffer.h"
#include "vec.h"
#include "vec_ptr.h"

#define vec_unittest_check(vec, len, cap) \
  do {                                    \
    assert(vec_length(vec) == len);       \
    assert(vec_capacity(vec) == cap);     \
  } while (0)
#define vec_unittest_push(vec, count)       \
  do {                                      \
    int i;                                  \
    index_t len = vec_length(vec);          \
    for (i = 0; i < count; i++) {           \
      struct buffer buf;                    \
      BUFFER_INIT(&buf, &i);                \
      if (vec_full(vec)) {                  \
        vec_reserve(vec, 0);                \
      }                                     \
      vec_insert(vec, -1, 1, &buf);         \
    }                                       \
    assert(vec_length(vec) == len + count); \
  } while (0)
#define vec_unittest_pop(vec, count)        \
  do {                                      \
    int i;                                  \
    index_t len = vec_length(vec);          \
    for (i = 0; i < count; i++) {           \
      vec_remove(vec, -1, 1);               \
    }                                       \
    assert(vec_length(vec) == len - count); \
  } while (0)
#define vec_unittest_range(vec, start, begin, end)  \
  do {                                              \
    int i, j;                                       \
    for (i = start, j = begin; j < end; i++, j++) { \
      int *p = vec_at(vec, i);                      \
      assert(*p == j);                              \
    }                                               \
  } while (0)
#define vec_unittest_insert(vec, start, begin, end) \
  do {                                              \
    int i, count = end - begin, *p;                 \
    struct buffer buf;                              \
    buffer_malloc(&buf, sizeof(int) * count);       \
    p = (int *)buf.ptr;                             \
    for (i = begin; i < end; i++, p++) {            \
      *p = i;                                       \
    }                                               \
    vec_insert(vec, start, count, &buf);            \
    buffer_free(&buf);                              \
  } while (0)
#define vec_unittest_remove(vec, begin, end) \
  do {                                       \
    vec_remove(vec, begin, end - begin);     \
  } while (0)

static void vec_unittest(void) {
  struct vec *vec = vec_new(sizeof(int));
  vec_unittest_check(vec, 0, 0);
  {
    vec_reserve(vec, 8);
    vec_unittest_check(vec, 0, 8);
  }
  {
    vec_unittest_push(vec, 1000);
    vec_unittest_check(vec, 1000, 1024);
    vec_unittest_range(vec, 0, 0, 1000);
  }
  {
    vec_unittest_pop(vec, 500);
    vec_unittest_check(vec, 500, 1024);
    vec_unittest_range(vec, 0, 0, 500);
  }
  {
    vec_unittest_push(vec, 1000);
    vec_unittest_check(vec, 1500, 2048);
    vec_unittest_range(vec, 0, 0, 500);
    vec_unittest_range(vec, 500, 0, 1000);
  }
  {
    vec_unittest_insert(vec, 500, 500, 1000);
    vec_unittest_check(vec, 2000, 2048);
    vec_unittest_range(vec, 0, 0, 1000);
    vec_unittest_range(vec, 1000, 0, 1000);
  }
  {
    vec_unittest_remove(vec, 500, 1500);
    vec_unittest_check(vec, 1000, 2048);
    vec_unittest_range(vec, 0, 0, 1000);
  }
  {
    vec_clear(vec);
    vec_unittest_check(vec, 0, 2048);
  }
  vec_delete(vec);
}

static void vec_ptr_unittest(void) {
  struct vec_ptr *vec = vec_ptr_new();
  int i;
  assert(vec_ptr_length(vec) == 0);
  assert(vec_ptr_capacity(vec) == 8);
  for (i = 0; i < 1000; i++) {
    int *p = malloc(sizeof(int));
    *p = i;
    vec_ptr_push(vec, p);
  }
  assert(vec_ptr_length(vec) == 1000);
  assert(vec_ptr_capacity(vec) == 1024);
  for (i = 0; i < 1000; i++) {
    int *p = vec_ptr_at(vec, i);
    assert(*p == i);
  }
  for (i = 0; i < 1000; i++) {
    int *p = vec_ptr_pop(vec);
    free(p);
  }
  assert(vec_ptr_length(vec) == 0);
  assert(vec_ptr_capacity(vec) == 1024);
  vec_ptr_delete(vec);
}

void unittest_vec(void) {
  vec_unittest();
  vec_ptr_unittest();
}
