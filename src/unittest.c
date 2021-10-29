#include "unittest.h"

#include "array/unittest.h"
#include "cell/unittest.h"
#include "dict/unittest.h"
#include "json/unittest.h"
#include "pool/unittest.h"
#include "set/unittest.h"
#include "vec/unittest.h"

void unittest(void) {
  array_unittest();
  cell_unittest();
  dict_unittest();
  json_unittest();
  pool_unittest();
  set_unittest();
  vec_unittest();
}
