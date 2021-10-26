#include "unittest.h"

#include "array.h"
#include "type.h"
#include "util/util.h"

void array_unittest(void) {
  struct array a, *p = &a;
  int i, count = 1000;
  array_init(p, sizeof(int));
  array_resize(p, count);
  for (i = 0; i < count / 10; i++) {
    int j, val[10];
    for (j = 0; j < 10; j++) {
      val[j] = i * 10 + j;
    }
    array_insert(p, val, 10);
  }
  for (i = 0; i < count; i++) {
    int* v = array_at(p, i);
    assert(*v == i);
  }
  array_remove(p, count / 10);
  count -= count / 10;
  for (i = 0; i < count; i++) {
    int* v = array_at(p, i);
    assert(*v == i);
  }
  array_finish(p);
}
