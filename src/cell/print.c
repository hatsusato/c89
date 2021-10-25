#include "print.h"

#include <stdio.h>

#include "cell.h"
#include "printer/printer.h"

static void cell_print_rec(const struct cell *self, struct printer *printer) {
  if (cell_is_cons(self)) {
    printer_print(printer, "(");
    printer_indent(printer, 1);
    cell_print_rec(cell_car(self), printer);
    self = cell_cdr(self);
    while (cell_is_cons(self)) {
      printer_newline(printer);
      cell_print_rec(cell_car(self), printer);
      self = cell_cdr(self);
    }
    if (cell_is_symbol(self)) {
      printer_print(printer, " . ");
      cell_print_rec(self, printer);
    }
    printer_indent(printer, -1);
    printer_print(printer, ")");
  } else if (cell_is_symbol(self)) {
    printer_print(printer, "%s", cell_symbol(self));
  }
}

void cell_print(const struct cell *self) {
  struct printer *printer = printer_new(stdout);
  cell_print_rec(self, printer);
  printer_newline(printer);
  printer_delete(printer);
}
