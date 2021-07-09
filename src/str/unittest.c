#include "unittest.h"

#include <assert.h>

#include "str.h"
#include "type.h"

#define str_unittest_eq(lhs, rhs)     \
  do {                                \
    assert(str_cmp(&lhs, &rhs) == 0); \
    assert(str_cmp(&rhs, &lhs) == 0); \
  } while (false)
#define str_unittest_lt(lhs, rhs)    \
  do {                               \
    assert(str_cmp(&lhs, &rhs) < 0); \
    assert(str_cmp(&rhs, &lhs) > 0); \
  } while (false)

void str_unittest(void) {
  struct str str, prefix, suffix;
  str_set(&str, "0123456789");
  str_set(&prefix, "01234");
  str_set(&suffix, "56789");
  str_unittest_eq(str, str);
  str_unittest_lt(prefix, str);
  str_unittest_lt(str, suffix);
  str_unittest_lt(prefix, suffix);
  str_remove_prefix(&str, 5);
  str_unittest_eq(str, suffix);
  str_remove_prefix(&str, 5);
  str_unittest_lt(str, prefix);
  str_unittest_lt(str, suffix);
}
