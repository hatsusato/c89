#include "unittest.h"

#include <assert.h>

#include "array.h"
#include "util/range.h"

#define array_unittest_push(array, val)   \
  do {                                    \
    struct buffer buf;                    \
    struct range range;                   \
    buffer_init(&buf, &val, sizeof(int)); \
    range.begin = array_length(&array);   \
    range.end = range.begin + 1;          \
    array_insert(&array, &range, &buf);   \
  } while (false)
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
  struct range range;
  int i;
  buffer_malloc(&buf, 100 * sizeof(int));
  array_init(&array, sizeof(int));
  array_set(&array, &buf);
  assert(array_align(&array) == sizeof(int));
  assert(array_capacity(&array) == 100);
  assert(array_length(&array) == 0);
  for (i = 0; i < 100; i++) {
    array_unittest_push(array, i);
  }
  assert(array_length(&array) == 100);
  array_unittest_range(array, 0, 0, 100);
  range.begin = 0;
  range.end = array_length(&array);
  array_remove(&array, &range);
  assert(array_capacity(&array) == 100);
  assert(array_length(&array) == 0);
  buffer_free(&buf);
}
