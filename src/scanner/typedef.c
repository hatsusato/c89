#include "typedef.h"

#include "cell/cell.h"
#include "cell/visitor.h"
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
  struct cell_visitor *visitor = cell_visitor_new(&contains);
  cell_visitor_insert(visitor, "typedef", typedef_set_bool);
  cell_visitor_visit(visitor, cell_at(decl, 1));
  cell_visitor_delete(visitor);
  return contains;
}
/* TODO: more precise algorithm to find declarator identifier */
void typedef_register(const struct cell *decl, struct set *set) {
  struct cell_visitor *visitor = cell_visitor_new(set);
  cell_visitor_insert(visitor, "typedef", typedef_insert_set);
  cell_visitor_visit(visitor, cell_at(decl, 2));
  cell_visitor_delete(visitor);
}
