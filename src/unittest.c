#include "unittest.h"

#include "array/unittest.h"
#include "pool/unittest.h"
#include "str/unittest.h"
#include "vec/unittest.h"

void unittest(void) {
  array_unittest();
  pool_unittest();
  pool_str_unittest();
  str_unittest();
  vec_unittest();
  vec_ptr_unittest();
}
