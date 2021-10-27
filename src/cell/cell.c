#include "cell.h"

#include "tag.h"
#include "type.h"
#include "util/util.h"

static bool_t cell_is_atom(const struct cell *self) {
  return cell_is_nil(self) || cell_is_symbol(self);
}

const struct cell *cell_nil(void) {
  static struct cell cell = {NULL, NULL};
  return &cell;
}
bool_t cell_is_nil(const struct cell *self) {
  return self == cell_nil();
}
bool_t cell_is_cons(const struct cell *self) {
  return !cell_is_atom(self);
}
bool_t cell_is_symbol(const struct cell *self) {
  return self->cdr == cell_tag_symbol();
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
const char *cell_tag(const struct cell *self) {
  return cell_is_cons(self) ? cell_symbol(cell_car(self)) : NULL;
}
const struct cell *cell_at(const struct cell *self, index_t index) {
  assert(0 <= index);
  for (; cell_is_cons(self); self = cell_cdr(self)) {
    if (index == 0) {
      return cell_car(self);
    }
    index--;
  }
  return NULL;
}
index_t cell_length(const struct cell *self) {
  index_t length = 0;
  for (; cell_is_cons(self); self = cell_cdr(self)) {
    length++;
  }
  return length;
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
