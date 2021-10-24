#include "cell.h"

#include "type.h"
#include "util/util.h"

const struct cell *cell_nil(void) {
  static struct cell cell = {NULL, NULL};
  return &cell;
}
bool_t cell_is_nil(const struct cell *self) {
  return !self->car && !self->cdr;
}
bool_t cell_is_cons(const struct cell *self) {
  return self->car && self->cdr;
}
bool_t cell_is_symbol(const struct cell *self) {
  return self->car && !self->cdr;
}
bool_t cell_is_list(const struct cell *self) {
  while (cell_is_cons(self)) {
    self = cell_cdr(self);
  }
  return cell_is_nil(self);
}
const struct cell *cell_car(const struct cell *self) {
  return cell_is_cons(self) ? self->car : NULL;
}
const struct cell *cell_cdr(const struct cell *self) {
  return cell_is_cons(self) ? self->cdr : NULL;
}
const char *cell_symbol(const struct cell *self) {
  return cell_is_symbol(self) ? self->car : NULL;
}
void cell_set_car(const struct cell *self, const struct cell *car) {
  struct cell *cell = (struct cell *)self;
  assert(cell_is_cons(self));
  cell->car = car;
}
void cell_set_cdr(const struct cell *self, const struct cell *cdr) {
  struct cell *cell = (struct cell *)self;
  assert(cell_is_cons(self));
  cell->cdr = cdr;
}
