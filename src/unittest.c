#include "unittest.h"

#include "cell/unittest.h"
#include "pool/unittest.h"
#include "set/unittest.h"
#include "vec/unittest.h"

void unittest(void) {
  cell_unittest();
  pool_unittest();
  set_unittest();
  vec_unittest();
}
