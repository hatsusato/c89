#include "unittest.h"

#include <assert.h>

#include "symbol.h"
#include "type.h"
#include "vec/ptr.h"

void set_symbol_unittest(void) {
  struct set_symbol *set = set_symbol_new();
  const char *a = "aaaaaaaa";
  int i;
  for (i = 0; i < 8; i++) {
    set_symbol_insert(set, a + i);
  }
  for (i = 0; i < 8; i++) {
    set_symbol_insert(set, a + i);
  }
  assert(vec_ptr_length(set->vec) == 8);
  for (i = 0; i < 8; i++) {
    assert(set_symbol_find(set, a + i));
  }
  assert(!set_symbol_find(set, "b"));
  set_symbol_delete(set);
}
