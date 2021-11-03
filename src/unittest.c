#include "unittest.h"

#include "array/unittest.h"
#include "json/unittest.h"
#include "set/unittest.h"
#include "vec/unittest.h"

void unittest(void) {
  array_unittest();
  json_unittest();
  set_unittest();
  vec_unittest();
}
