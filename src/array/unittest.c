#include "unittest.h"

#include <assert.h>

#include "array.h"
#include "util/buffer.h"
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
  struct buffer buf;
  int i;
  array_init(&array, sizeof(int), buffer_malloc(&buf, 100 * sizeof(int)));
  assert(array_align(&array) == sizeof(int));
  assert(array_length(&array) == 0);
  for (i = 0; i < 100; i++) {
    array_push(&array, &i);
  }
  assert(array_length(&array) == 100);
  array_unittest_range(array, 0, 0, 100);
  array_clear(&array);
  assert(array_length(&array) == 0);
  buffer_free(&buf);
}
