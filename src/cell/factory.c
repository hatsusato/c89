#include "factory.h"

#include <assert.h>

#include "pool/any.h"
#include "set/symbol.h"
#include "type.h"
#include "util/util.h"

static const struct cell *cell_factory_make(struct cell_factory *self,
                                            const void *car, const void *cdr) {
  struct cell *cons = pool_any_alloc(self->pool, sizeof(struct cell));
  cons->car = car;
  cons->cdr = cdr;
  return cons;
}

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
const struct cell *cell_factory_cons(struct cell_factory *self,
                                     const struct cell *car,
                                     const struct cell *cdr) {
  assert(car && cdr);
  return cell_factory_make(self, car, cdr);
}
const struct cell *cell_factory_symbol(struct cell_factory *self,
                                       const char *symbol) {
  assert(symbol);
  symbol = set_symbol_insert(self->set, symbol);
  return cell_factory_make(self, symbol, NULL);
}
