#include "printer.h"

#include <stdarg.h>
#include <stdio.h>

#include "type.h"

static void printer_shift(struct printer *self) {
  if (self->newline && self->fp) {
    index_t i;
    for (i = 0; i < self->indent; i++) {
      fputc(' ', self->fp);
    }
  }
  self->newline = false;
}
static void printer_vfprintf(struct printer *self, const char *format,
                             va_list args) {
  if (self->fp) {
    vfprintf(self->fp, format, args);
  }
}

void printer_init(struct printer *self, void *fp) {
  self->fp = fp;
  self->indent = 0;
  self->newline = false;
}
void printer_print(struct printer *self, const char *format, ...) {
  va_list args;
  va_start(args, format);
  printer_shift(self);
  printer_vfprintf(self, format, args);
  va_end(args);
}
