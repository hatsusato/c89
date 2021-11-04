#include "printer.h"

#include <stdarg.h>
#include <stdio.h>

#include "util/util.h"

struct printer {
  FILE *fp;
  index_t indent;
  bool_t newline;
};

static void printer_shift(struct printer *self) {
  if (self->newline) {
    index_t i;
    for (i = 0; i < 2 * self->indent; i++) {
      fputc(' ', self->fp);
    }
  }
}

struct printer *printer_new(void *fp) {
  struct printer *self = util_malloc(sizeof(struct printer));
  self->fp = fp;
  self->indent = 0;
  self->newline = false;
  return self;
}
struct printer *printer_new_stdout(void) {
  return printer_new(stdout);
}
struct printer *printer_new_stderr(void) {
  return printer_new(stderr);
}
void printer_del(struct printer *self) {
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
void printer_open(struct printer *self, const char *symbol) {
  printer_print(self, "%s", symbol);
  self->indent++;
}
void printer_close(struct printer *self, const char *symbol) {
  self->indent--;
  printer_print(self, "%s", symbol);
}
