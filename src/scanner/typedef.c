#include "typedef.h"

#include "cell/cell.h"
#include "cell/visitor.h"
#include "dict/dict.h"
#include "util/util.h"

static void typedef_set_bool(const struct cell *cell, void *extra) {
  bool_t *flag = extra;
  *flag = true;
  UTIL_UNUSED(cell);
}

bool_t typedef_contains(const struct cell *decl) {
  bool_t contains = false;
  struct dict *visitors = dict_new();
  struct cell_visitor_wrapper wrapper = {typedef_set_bool};
  dict_insert(visitors, "typedef", &wrapper);
  cell_visitor(cell_at(decl, 1), visitors, &contains);
  dict_delete(visitors);
  return contains;
}
