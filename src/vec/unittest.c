#include "unittest.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ptr.h"
#include "type.h"
#include "util/box.h"
#include "util/slice.h"
#include "vec.h"

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
      vec_push(vec, &i);                    \
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
#define vec_unittest_insert(vec, start, begin, end)       \
  do {                                                    \
    int i, count = end - begin, *p;                       \
    struct box *box;                                      \
    struct slice slice;                                   \
    box = box_new(sizeof(int) * count);                   \
    p = box_ptr(box);                                     \
    for (i = begin; i < end; i++, p++) {                  \
      *p = i;                                             \
    }                                                     \
    slice_init(&slice, sizeof(int), box_ptr(box), count); \
    vec_insert(vec, start, &slice);                       \
    box_delete(box);                                      \
  } while (false)
#define vec_unittest_remove(vec, b, e) \
  do {                                 \
    vec_remove(vec, b, e - b);         \
  } while (false)

void vec_unittest(void) {
  struct vec vec;
  {
    vec_new(&vec, sizeof(int));
    vec_unittest_check(&vec, 0, 8);
  }
  {
    vec_unittest_push(&vec, 1000);
    vec_unittest_check(&vec, 1000, 1024);
    vec_unittest_range(&vec, 0, 0, 1000);
  }
  {
    vec_unittest_pop(&vec, 500);
    vec_unittest_check(&vec, 500, 1024);
    vec_unittest_range(&vec, 0, 0, 500);
  }
  {
    vec_unittest_push(&vec, 1000);
    vec_unittest_check(&vec, 1500, 2048);
    vec_unittest_range(&vec, 0, 0, 500);
    vec_unittest_range(&vec, 500, 0, 1000);
  }
  {
    vec_unittest_insert(&vec, 500, 500, 1000);
    vec_unittest_check(&vec, 2000, 2048);
    vec_unittest_range(&vec, 0, 0, 1000);
    vec_unittest_range(&vec, 1000, 0, 1000);
  }
  {
    vec_unittest_remove(&vec, 500, 1500);
    vec_unittest_check(&vec, 1000, 2048);
    vec_unittest_range(&vec, 0, 0, 1000);
  }
  vec_delete(&vec);
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
      free(vec_ptr_top(vec));            \
      vec_ptr_pop(vec);                  \
    }                                    \
  } while (false)

void vec_ptr_unittest(void) {
  struct vec_ptr vec;
  {
    vec_ptr_new(&vec);
    vec_ptr_unittest_check(&vec, 0, 8);
  }
  {
    vec_ptr_unittest_push(&vec, 0, 1000);
    vec_ptr_unittest_check(&vec, 1000, 1024);
    vec_ptr_unittest_range(&vec, 0, 0, 1000);
  }
  {
    vec_ptr_unittest_pop(&vec, 500);
    vec_ptr_unittest_check(&vec, 500, 1024);
    vec_ptr_unittest_range(&vec, 0, 0, 500);
  }
  {
    vec_ptr_unittest_push(&vec, 0, 1000);
    vec_ptr_unittest_check(&vec, 1500, 2048);
    vec_ptr_unittest_range(&vec, 0, 0, 500);
    vec_ptr_unittest_range(&vec, 500, 0, 1000);
  }
  {
    vec_ptr_unittest_pop(&vec, 500);
    vec_ptr_unittest_check(&vec, 1000, 2048);
    vec_ptr_unittest_range(&vec, 0, 0, 500);
    vec_ptr_unittest_range(&vec, 500, 0, 500);
  }
  vec_ptr_map(&vec, free);
  vec_ptr_delete(&vec);
}
