#include "printer.h"

#include "type.h"

void printer_init(struct printer *self, void *fp) {
  self->fp = fp;
  self->indent = 0;
  self->newline = false;
}
