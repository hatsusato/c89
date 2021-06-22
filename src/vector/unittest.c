#include "unittest.h"

#include <assert.h>

#include "utility/buffer.h"
#include "vec.h"

#define vec_unittest_check(vec, len, cap) \
  do {                                    \
    assert(vec_length(vec) == len);       \
    assert(vec_capacity(vec) == cap);     \
  } while (0)
#define vec_unittest_push(vec, count)       \
  do {                                      \
    int i;                                  \
    size_t len = vec_length(vec);           \
    for (i = 0; i < count; i++) {           \
      struct buffer buf;                    \
      BUFFER_INIT(&buf, &i);                \
      if (vec_full(vec)) {                  \
        vec_reserve(vec, 0);                \
      }                                     \
      vec_push(vec, &buf);                  \
    }                                       \
    assert(vec_length(vec) == len + count); \
  } while (0)
#define vec_unittest_pop(vec, count)        \
  do {                                      \
    int i;                                  \
    size_t len = vec_length(vec);           \
    for (i = 0; i < count; i++) {           \
      vec_pop(vec, NULL);                   \
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

void vec_unittest(void) {
  struct vec *vec = vec_new(sizeof(int));
  vec_unittest_check(vec, 0, 0);
  vec_reserve(vec, 8);
  vec_unittest_check(vec, 0, 8);
  vec_unittest_push(vec, 1000);
  vec_unittest_check(vec, 1000, 1024);
  vec_unittest_range(vec, 0, 0, 1000);
  vec_unittest_check(vec, 1000, 1024);
  vec_unittest_pop(vec, 500);
  vec_unittest_check(vec, 500, 1024);
  vec_unittest_range(vec, 0, 0, 500);
  vec_unittest_push(vec, 1000);
  vec_unittest_range(vec, 0, 0, 500);
  vec_unittest_range(vec, 500, 0, 1000);
  vec_delete(vec);
}
