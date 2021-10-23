#include "factory.h"

#include "type.h"
#include "util/util.h"

struct cell_factory *cell_factory_new(struct pool_any *pool,
                                      struct set_symbol *set) {
  struct cell_factory *self = util_malloc(sizeof(struct cell_factory), 1);
  self->pool = pool;
  self->set = set;
  return self;
}
void cell_factory_delete(struct cell_factory *self) {
  util_free(self);
}
