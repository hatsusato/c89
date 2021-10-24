#include "unittest.h"

#include "ptr.h"
#include "util/util.h"

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
      UTIL_UNUSED(p);                                  \
    }                                                  \
  } while (false)
#define vec_ptr_unittest_push(vec, begin, end) \
  do {                                         \
    int i;                                     \
    for (i = begin; i < end; i++) {            \
      int *p = util_malloc(sizeof(int), 1);    \
      *p = i;                                  \
      vec_ptr_push(vec, p);                    \
    }                                          \
  } while (false)
#define vec_ptr_unittest_pop(vec, count) \
  do {                                   \
    int i;                               \
    for (i = 0; i < count; i++) {        \
      util_free(vec_ptr_top(vec));       \
      vec_ptr_pop(vec);                  \
    }                                    \
  } while (false)

void vec_ptr_unittest(void) {
  struct vec_ptr *vec = vec_ptr_new();
  {
    vec_ptr_unittest_check(vec, 0, 0);
  }
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
  vec_ptr_map(vec, (void (*)(void *))util_free);
  vec_ptr_delete(vec);
}
