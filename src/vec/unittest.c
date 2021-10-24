#include "unittest.h"

#include "ptr.h"
#include "util/util.h"

#define vec_unittest_check(vec, len, cap) \
  do {                                    \
    assert(vec_length(vec) == len);       \
    assert(vec_capacity(vec) == cap);     \
  } while (false)
#define vec_unittest_range(vec, start, begin, end)  \
  do {                                              \
    int i, j;                                       \
    for (i = start, j = begin; j < end; i++, j++) { \
      int *p = vec_at(vec, i);                      \
      assert(*p == j);                              \
      UTIL_UNUSED(p);                               \
    }                                               \
  } while (false)
#define vec_unittest_push(vec, begin, end)  \
  do {                                      \
    int i;                                  \
    for (i = begin; i < end; i++) {         \
      int *p = util_malloc(sizeof(int), 1); \
      *p = i;                               \
      vec_push(vec, p);                     \
    }                                       \
  } while (false)
#define vec_unittest_pop(vec, count) \
  do {                               \
    int i;                           \
    for (i = 0; i < count; i++) {    \
      util_free(vec_top(vec));       \
      vec_pop(vec);                  \
    }                                \
  } while (false)

void vec_unittest(void) {
  struct vec *vec = vec_new();
  {
    vec_unittest_check(vec, 0, 0);
  }
  {
    vec_unittest_push(vec, 0, 1000);
    vec_unittest_check(vec, 1000, 1024);
    vec_unittest_range(vec, 0, 0, 1000);
  }
  {
    vec_unittest_pop(vec, 500);
    vec_unittest_check(vec, 500, 1024);
    vec_unittest_range(vec, 0, 0, 500);
  }
  {
    vec_unittest_push(vec, 0, 1000);
    vec_unittest_check(vec, 1500, 2048);
    vec_unittest_range(vec, 0, 0, 500);
    vec_unittest_range(vec, 500, 0, 1000);
  }
  {
    vec_unittest_pop(vec, 500);
    vec_unittest_check(vec, 1000, 2048);
    vec_unittest_range(vec, 0, 0, 500);
    vec_unittest_range(vec, 500, 0, 500);
  }
  vec_map(vec, (void (*)(void *))util_free);
  vec_delete(vec);
}
