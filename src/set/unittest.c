#include "unittest.h"

#include <assert.h>

#include "set.h"
#include "symbol.h"
#include "type.h"
#include "vec/ptr.h"
#include "vec/vec.h"

static int set_intcmp(const void *lhs, const void *rhs) {
  const int *l = lhs, *r = rhs;
  return (*l < *r) ? -1 : (*l > *r);
}

void set_unittest(void) {
  struct set self;
  int i;
  set_init(&self, sizeof(int), set_intcmp);
  for (i = 0; i > -1024; i--) {
    set_insert(&self, &i);
  }
  for (i = 1024; i > -1024; i--) {
    set_insert(&self, &i);
  }
  assert(vec_length(&self.vec) == 2048);
  for (i = -1024; i < 1024; i++) {
    const int *p = set_search(&self, &i);
    if (p) {
      assert(*p == i);
    } else {
      assert(i == -1024);
    }
  }
  set_finish(&self);
}

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
