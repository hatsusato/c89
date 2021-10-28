#include "typedef.h"

#include "cell/cell.h"
#include "cell/visitor.h"
#include "set/set.h"
#include "util/util.h"

static void typedef_set_bool(struct cell_visitor *self,
                             const struct cell *cell) {
  bool_t *flag = cell_visitor_extra(self);
  *flag = true;
  UTIL_UNUSED(cell);
}
static void typedef_insert_set(struct cell_visitor *self,
                               const struct cell *cell) {
  struct set *set = cell_visitor_extra(self);
  cell = cell_at(cell, 1);
  assert(cell && cell_is_symbol(cell));
  set_insert(set, cell_symbol(cell));
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
