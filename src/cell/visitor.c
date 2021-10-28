#include "visitor.h"

#include "cell.h"
#include "dict/dict.h"
#include "pool/pool.h"
#include "type.h"
#include "util/util.h"

static cell_visitor_t cell_visitor_find(struct cell_visitor *self,
                                        const struct cell *car) {
  if (cell_is_symbol(car)) {
    const char *symbol = cell_symbol(car);
    struct cell_visitor_wrapper *wrapper = dict_find(self->visitors, symbol);
    return wrapper ? wrapper->func : NULL;
  }
  return NULL;
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
void cell_visitor_insert(struct cell_visitor *self, const char *symbol,
                         cell_visitor_t visitor) {
  struct cell_visitor_wrapper *wrapper =
      pool_alloc(self->wrappers, sizeof(struct cell_visitor_wrapper));
  wrapper->func = visitor;
  dict_insert(self->visitors, symbol, wrapper);
}
void cell_visitor_visit(struct cell_visitor *self, const struct cell *cell) {
  for (; cell_is_cons(cell); cell = cell_cdr(cell)) {
    const struct cell *car = cell_car(cell);
    cell_visitor_t func = cell_visitor_find(self, car);
    if (func) {
      func(cell, self->extra);
      return;
    } else {
      cell_visitor_visit(self, car);
    }
  }
}
