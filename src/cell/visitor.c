#include "visitor.h"

#include "cell.h"
#include "dict/dict.h"
#include "pool/pool.h"
#include "type.h"
#include "util/util.h"

static cell_visitor_t cell_visitor_extract(const struct cell *car,
                                           const struct dict *visitors) {
  if (cell_is_symbol(car)) {
    struct cell_visitor_wrapper *wrapper =
        dict_find((struct dict *)visitors, cell_symbol(car));
    return wrapper ? wrapper->func : NULL;
  }
  return NULL;
}

void cell_visitor(const struct cell *self, const struct dict *visitors,
                  void *extra) {
  for (; cell_is_cons(self); self = cell_cdr(self)) {
    const struct cell *car = cell_car(self);
    cell_visitor_t func = cell_visitor_extract(car, visitors);
    if (func && func(self, extra)) {
      return;
    }
    cell_visitor(car, visitors, extra);
  }
}
bool_t cell_visitor_noop(const struct cell *self, void *extra) {
  UTIL_UNUSED(self);
  UTIL_UNUSED(extra);
  return true;
}

struct cell_visitor *cell_visitor_new(void *extra) {
  struct cell_visitor *self = util_malloc(sizeof(struct cell_visitor));
  self->wrappers = pool_new();
  self->visitors = dict_new();
  self->extra = extra;
  return self;
}
void cell_visitor_delete(struct cell_visitor *self) {
  dict_delete(self->visitors);
  pool_delete(self->wrappers);
  util_free(self);
}
