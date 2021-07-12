#include "cell.h"

#include <assert.h>

#include "pool/pool.h"
#include "printer/printer.h"
#include "type.h"
#include "util/box.h"

static const struct cell *cell_new(struct pool *pool, const void *car,
                                   const void *cdr) {
  struct box *box = box_new(sizeof(struct cell), 1);
  struct cell *cell = pool_insert(pool, box);
  cell->car = car;
  cell->cdr = cdr;
  return cell;
}

const struct cell *cell_nil(void) {
  static struct cell cell = {NULL, NULL};
  return &cell;
}
const struct cell *cell_new_cons(struct pool *pool, const struct cell *car,
                                 const struct cell *cdr) {
  assert(car && cdr);
  return cell_new(pool, car, cdr);
}
const struct cell *cell_new_symbol(struct pool *pool, const char *symbol) {
  assert(symbol);
  return cell_new(pool, symbol, NULL);
}
const struct cell *cell_push(struct pool *pool, const struct cell *list,
                             const struct cell *elem) {
  const struct cell *const *it = &list;
  while (cell_is_cons(*it)) {
    it = &(*it)->cdr;
  }
  assert(cell_is_nil(*it));
  *(const struct cell **)it = cell_new_cons(pool, elem, cell_nil());
  return list;
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
void cell_print(const struct cell *self, struct printer *printer) {
  if (cell_is_cons(self)) {
    bool_t first;
    printer_print(printer, "(");
    printer_indent(printer, 1);
    for (first = true; cell_is_cons(self);
         first = false, self = cell_cdr(self)) {
      if (!first) {
        printer_newline(printer);
      }
      cell_print(cell_car(self), printer);
    }
    if (cell_is_symbol(self)) {
      printer_print(printer, " . ");
      cell_print(self, printer);
    }
    printer_indent(printer, -1);
    printer_print(printer, ")");
  } else if (cell_is_symbol(self)) {
    printer_print(printer, "%s", cell_symbol(self));
  }
}
