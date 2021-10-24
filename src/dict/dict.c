#include "dict.h"

#include "type.h"
#include "util/util.h"
#include "vec/vec.h"

struct dict *dict_new(void) {
  struct dict *self = util_malloc(sizeof(struct dict), 1);
  self->vec = vec_new();
  return self;
}
void dict_delete(struct dict *self) {
  vec_delete(self->vec);
  util_free(self);
}
