#include "symbol.h"

#include "array/array.h"
#include "type.h"
#include "util/util.h"
#include "vec/ptr.h"

static int set_symbol_cmp(const void *lhs, const void *rhs) {
  const char *const *pl = lhs, *const *pr = rhs;
  return util_strcmp(*pl, *pr);
}

struct set_symbol *set_symbol_new(void) {
  struct set_symbol *self = util_malloc(sizeof(struct set_symbol), 1);
  vec_ptr_init(self->vec);
  return self;
}
void set_symbol_delete(struct set_symbol *self) {
  index_t i, length = vec_ptr_length(self->vec);
  for (i = 0; i < length; i++) {
    const char *symbol = vec_ptr_at(self->vec, i);
    util_free(symbol);
  }
  vec_ptr_finish(self->vec);
  util_free(self);
}
const char *set_symbol_find(struct set_symbol *self, const char *symbol) {
  struct array *array = vec_ptr_get_array(self->vec);
  const char *const *found = array_search(array, symbol, set_symbol_cmp);
  return found ? *found : NULL;
}
