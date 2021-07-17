#include "unittest.h"

#include <assert.h>

#include "view.h"
#include "view_type.h"

#define str_view_unittest_eq(lhs, rhs)     \
  do {                                     \
    assert(str_view_cmp(&lhs, &rhs) == 0); \
    assert(str_view_cmp(&rhs, &lhs) == 0); \
  } while (false)
#define str_view_unittest_lt(lhs, rhs)    \
  do {                                    \
    assert(str_view_cmp(&lhs, &rhs) < 0); \
    assert(str_view_cmp(&rhs, &lhs) > 0); \
  } while (false)

void str_view_unittest(void) {
  struct str_view str, prefix, suffix;
  str_view_set(&str, "0123456789");
  str_view_set(&prefix, "01234");
  str_view_set(&suffix, "56789");
  str_view_unittest_eq(str, str);
  str_view_unittest_lt(prefix, str);
  str_view_unittest_lt(str, suffix);
  str_view_unittest_lt(prefix, suffix);
  str_view_remove_prefix(&str, 5);
  str_view_unittest_eq(str, suffix);
  str_view_remove_prefix(&str, 5);
  str_view_unittest_lt(str, prefix);
  str_view_unittest_lt(str, suffix);
}
