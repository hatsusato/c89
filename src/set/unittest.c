#include "unittest.h"

#include "set.h"
#include "type.h"
#include "util/util.h"
#include "vec/vec.h"

void set_unittest(void) {
  struct set *set = set_new();
  const char *a = "aaaaaaaa";
  int i;
  for (i = 0; i < 8; i++) {
    set_insert(set, a + i);
  }
  for (i = 0; i < 8; i++) {
    set_insert(set, a + i);
  }
  assert(vec_length(set->vec) == 8);
  for (i = 0; i < 8; i++) {
    assert(set_find(set, a + i));
  }
  assert(!set_find(set, "b"));
  set_delete(set);
}
