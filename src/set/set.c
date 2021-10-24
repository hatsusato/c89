#include "set.h"

#include "array/array.h"
#include "type.h"
#include "util/util.h"
#include "vec/vec.h"

static int set_cmp(const void *lhs, const void *rhs) {
  const char *const *l = lhs, *const *r = rhs;
  return util_strcmp(*l, *r);
}

struct set *set_new(void) {
  struct set *self = util_malloc(sizeof(struct set), 1);
  self->vec = vec_new();
  return self;
}
void set_delete(struct set *self) {
  index_t i, length = vec_length(self->vec);
  for (i = 0; i < length; i++) {
    const char *symbol = vec_at(self->vec, i);
    util_free(symbol);
  }
  vec_delete(self->vec);
  util_free(self);
}
const char *set_find(struct set *self, const char *symbol) {
  return vec_search(self->vec, symbol, set_cmp);
}
const char *set_insert(struct set *self, const char *symbol) {
  const char *found = set_find(self, symbol);
  if (!found) {
    const char *dup = util_strdup(symbol);
    vec_push(self->vec, (void *)dup);
    vec_sort(self->vec, set_cmp);
    found = dup;
  }
  return found;
}
