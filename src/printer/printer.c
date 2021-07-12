#include "printer.h"

#include <stdio.h>

#include "type.h"

void printer_shift(struct printer *self) {
  if (self->newline && self->fp) {
    index_t i;
    for (i = 0; i < self->indent; i++) {
      fputc(' ', self->fp);
    }
  }
  self->newline = false;
}
void printer_init(struct printer *self, void *fp) {
  self->fp = fp;
  self->indent = 0;
  self->newline = false;
}
