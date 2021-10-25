#include "printer.h"

#include <stdarg.h>
#include <stdio.h>

#include "type.h"
#include "util/util.h"

static void printer_shift(struct printer *self) {
  if (self->newline) {
    index_t i;
    for (i = 0; i < self->indent; i++) {
      fputc(' ', self->fp);
    }
  }
}

struct printer *printer_new(void *fp) {
  struct printer *self = util_malloc(sizeof(struct printer), 1);
  self->fp = fp;
  self->indent = 0;
  self->newline = false;
  return self;
}
void printer_delete(struct printer *self) {
  util_free(self);
}
void printer_print(struct printer *self, const char *format, ...) {
  if (self->fp) {
    va_list args;
    va_start(args, format);
    printer_shift(self);
    vfprintf(self->fp, format, args);
    va_end(args);
  }
  self->newline = false;
}
void printer_newline(struct printer *self) {
  if (self->fp) {
    fputc('\n', self->fp);
  }
  self->newline = true;
}
void printer_indent(struct printer *self, index_t indent) {
  if (indent == 0) {
    self->indent = indent;
  } else {
    self->indent += indent;
  }
}
