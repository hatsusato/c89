#include "unittest.h"

#include "array/unittest.h"
#include "json/unittest.h"
#include "vec/unittest.h"

void unittest(void) {
  array_unittest();
  json_unittest();
  vec_unittest();
}
