#include "set.h"

#include "type.h"
#include "util/util.h"
#include "vec/type.h"
#include "vec/vec.h"

static int set_cmp(const void *lhs, const void *rhs) {
  const struct vec_entry *l = lhs, *r = rhs;
  return util_strcmp(l->ptr, r->ptr);
}

struct set *set_new(void) {
  struct set *self = util_malloc(sizeof(struct set));
  self->vec = vec_new();
  return self;
}
void set_delete(struct set *self) {
  vec_map(self->vec, util_free);
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
