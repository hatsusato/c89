#include "factory.h"

#include <assert.h>

#include "cell.h"
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
static const struct cell *cell_factory_push(struct cell_factory *self,
                                            const struct cell *list,
                                            const struct cell *elem) {
  const struct cell *const *it = &list;
  while (cell_is_cons(*it)) {
    it = &(*it)->cdr;
  }
  assert(cell_is_nil(*it));
  *(const struct cell **)it = cell_factory_make(self, elem, cell_nil());
  return list;
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
const struct cell *cell_factory_list(struct cell_factory *self, index_t count,
                                     va_list args) {
  const struct cell *list = cell_nil();
  index_t i;
  for (i = 0; i < count; i++) {
    const struct cell *elem = va_arg(args, const struct cell *);
    list = cell_factory_push(self, list, elem);
  }
  return list;
}
