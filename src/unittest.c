#include "unittest.h"

#include "str/unittest.h"
#include "vec/unittest.h"

void unittest(void) {
  str_unittest();
  vec_unittest();
  vec_ptr_unittest();
}
