#include "unittest.h"

#include "array.h"
#include "slice.h"
#include "type.h"
#include "util/util.h"

#define array_unittest_range(array, index, begin, end) \
  do {                                                 \
    int i, j;                                          \
    for (i = index, j = begin; j < end; i++, j++) {    \
      int *p = array_at(&array, i);                    \
      assert(*p == j);                                 \
      UTIL_UNUSED(p);                                  \
    }                                                  \
  } while (0)

void array_unittest(void) {
  struct array array;
  int *p = util_malloc(sizeof(int), 1000);
  int i;
  array_init(&array, sizeof(int), p);
  assert(slice_align(array_slice(&array)) == sizeof(int));
  assert(array_length(&array) == 0);
  for (i = 0; i < 100; i++) {
    struct slice slice;
    slice_init(&slice, sizeof(int), &i, 1);
    array_insert(&array, array_length(&array), &slice);
  }
  assert(array_length(&array) == 100);
  array_unittest_range(array, 0, 0, 100);
  array_remove(&array, 0, 100);
  assert(array_length(&array) == 0);
  util_free(p);
}
