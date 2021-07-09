#include "unittest.h"

#include <assert.h>

#include "array.h"
#include "type.h"
#include "util/box.h"
#include "util/slice.h"

#define array_unittest_range(array, index, begin, end) \
  do {                                                 \
    int i, j;                                          \
    for (i = index, j = begin; j < end; i++, j++) {    \
      int *p = array_at(&array, i);                    \
      assert(*p == j);                                 \
    }                                                  \
  } while (0)

void array_unittest(void) {
  struct array array;
  struct box *box;
  int i;
  box = box_new(sizeof(int), 1000);
  array_init(&array, sizeof(int), box_ptr(box));
  assert(array_align(&array) == sizeof(int));
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
  box_delete(box);
}
