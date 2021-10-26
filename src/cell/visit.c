#include "visit.h"

#include "cell.h"
#include "dict/dict.h"
#include "util/util.h"

static cell_visitor_t cell_visit_match(const struct cell *car,
                                       const struct dict *visitors) {
  cell_visitor_t visitor = NULL;
  if (cell_is_symbol(car)) {
    struct cell_visitor_wrapper *wrapper =
        dict_find((struct dict *)visitors, cell_symbol(car));
    visitor = wrapper ? wrapper->func : NULL;
  }
  return visitor;
}

void cell_visit(const struct cell *it, const struct dict *visitors,
                void *extra) {
  if (cell_is_list(it)) {
    cell_visitor_t visitor = cell_visit_match(cell_car(it), visitors);
    if (visitor) {
      visitor(it, extra);
    } else {
      for (; cell_is_cons(it); it = cell_cdr(it)) {
        cell_visit(cell_car(it), visitors, extra);
      }
    }
  }
}
