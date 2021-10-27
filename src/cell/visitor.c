#include "visitor.h"

#include "cell.h"
#include "dict/dict.h"
#include "util/util.h"

void cell_visitor(const struct cell *self, const struct dict *visitors,
                  void *extra) {
  for (; cell_is_cons(self); self = cell_cdr(self)) {
    const struct cell *car = cell_car(self);
    if (cell_is_cons(car)) {
      cell_visitor(car, visitors, extra);
    } else if (cell_is_symbol(car)) {
      struct cell_visitor_wrapper *wrapper =
          dict_find((struct dict *)visitors, cell_symbol(car));
      if (wrapper) {
        wrapper->func(self, extra);
      }
    }
  }
}
void cell_visitor_noop(const struct cell *self, void *extra) {
  UTIL_UNUSED(self);
  UTIL_UNUSED(extra);
}
