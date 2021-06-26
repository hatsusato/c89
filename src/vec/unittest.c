#include "unittest.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/buffer.h"
#include "util/range.h"
#include "util/slice.h"
#include "vec.h"
#include "vec_ptr.h"

#define vec_unittest_check(vec, len, cap) \
  do {                                    \
    assert(vec_length(vec) == len);       \
    assert(vec_capacity(vec) == cap);     \
  } while (false)
#define vec_unittest_push(vec, count)       \
  do {                                      \
    int i;                                  \
    index_t len = vec_length(vec);          \
    for (i = 0; i < count; i++) {           \
      struct slice slice;                   \
      slice_init(&slice, sizeof(i), &i, 1); \
      vec_push(vec, &slice);                \
    }                                       \
    assert(vec_length(vec) == len + count); \
  } while (false)
#define vec_unittest_pop(vec, count)        \
  do {                                      \
    int i;                                  \
    index_t len = vec_length(vec);          \
    for (i = 0; i < count; i++) {           \
      vec_pop(vec);                         \
    }                                       \
    assert(vec_length(vec) == len - count); \
  } while (false)
#define vec_unittest_range(vec, start, begin, end)  \
  do {                                              \
    int i, j;                                       \
    for (i = start, j = begin; j < end; i++, j++) { \
      int *p = vec_at(vec, i);                      \
      assert(*p == j);                              \
    }                                               \
  } while (false)
#define vec_unittest_insert(vec, start, begin, end)             \
  do {                                                          \
    int i, count = end - begin, *p;                             \
    struct buffer buf;                                          \
    struct slice slice;                                         \
    struct range range;                                         \
    range_init(&range, start, count);                           \
    buffer_malloc(&buf, sizeof(int) * count);                   \
    p = buffer_at(&buf, 0);                                     \
    for (i = begin; i < end; i++, p++) {                        \
      *p = i;                                                   \
    }                                                           \
    slice_init(&slice, sizeof(int), buffer_at(&buf, 0), count); \
    vec_insert(vec, &range, &slice);                            \
    buffer_free(&buf);                                          \
  } while (false)
#define vec_unittest_remove(vec, b, e) \
  do {                                 \
    struct range range;                \
    range.begin = b;                   \
    range.end = e;                     \
    vec_remove(vec, &range);           \
  } while (false)

void vec_unittest(void) {
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
  vec_delete(vec);
}

#define vec_ptr_unittest_check(vec, len, cap) \
  do {                                        \
    assert(vec_ptr_length(vec) == len);       \
    assert(vec_ptr_capacity(vec) == cap);     \
  } while (false)
#define vec_ptr_unittest_range(vec, start, begin, end) \
  do {                                                 \
    int i, j;                                          \
    for (i = start, j = begin; j < end; i++, j++) {    \
      int *p = vec_ptr_at(vec, i);                     \
      assert(*p == j);                                 \
    }                                                  \
  } while (false)
#define vec_ptr_unittest_push(vec, begin, end) \
  do {                                         \
    int i;                                     \
    for (i = begin; i < end; i++) {            \
      int *p = malloc(sizeof(int));            \
      *p = i;                                  \
      vec_ptr_push(vec, p);                    \
    }                                          \
  } while (false)
#define vec_ptr_unittest_pop(vec, count) \
  do {                                   \
    int i;                               \
    for (i = 0; i < count; i++) {        \
      vec_ptr_pop(vec);                  \
    }                                    \
  } while (false)

void vec_ptr_unittest(void) {
  struct vec_ptr *vec = vec_ptr_new(free);
  vec_ptr_unittest_check(vec, 0, 8);
  {
    vec_ptr_unittest_push(vec, 0, 1000);
    vec_ptr_unittest_check(vec, 1000, 1024);
    vec_ptr_unittest_range(vec, 0, 0, 1000);
  }
  {
    vec_ptr_unittest_pop(vec, 500);
    vec_ptr_unittest_check(vec, 500, 1024);
    vec_ptr_unittest_range(vec, 0, 0, 500);
  }
  {
    vec_ptr_unittest_push(vec, 0, 1000);
    vec_ptr_unittest_check(vec, 1500, 2048);
    vec_ptr_unittest_range(vec, 0, 0, 500);
    vec_ptr_unittest_range(vec, 500, 0, 1000);
  }
  {
    vec_ptr_unittest_pop(vec, 500);
    vec_ptr_unittest_check(vec, 1000, 2048);
    vec_ptr_unittest_range(vec, 0, 0, 500);
    vec_ptr_unittest_range(vec, 500, 0, 500);
  }
  vec_ptr_delete(vec);
}
