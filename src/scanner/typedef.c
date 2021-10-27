#include "typedef.h"

#include "cell/cell.h"
#include "cell/visitor.h"
#include "dict/dict.h"
#include "set/set.h"
#include "util/util.h"

static bool_t typedef_set_bool(const struct cell *cell, void *extra) {
  bool_t *flag = extra;
  *flag = true;
  UTIL_UNUSED(cell);
  return true;
}
static bool_t typedef_insert_set(const struct cell *cell, void *extra) {
  struct set *set = extra;
  cell = cell_at(cell, 1);
  assert(cell && cell_is_symbol(cell));
  set_insert(set, cell_symbol(cell));
  return true;
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
/* TODO: more precise algorithm to find declarator identifier */
void typedef_register(const struct cell *decl, struct set *set) {
  struct dict *visitors = dict_new();
  struct cell_visitor_wrapper wrapper = {typedef_insert_set};
  dict_insert(visitors, "identifier", &wrapper);
  cell_visitor(cell_at(decl, 2), visitors, set);
  dict_delete(visitors);
}
