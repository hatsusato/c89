#include "printer.h"

#include <stdarg.h>
#include <stdio.h>

#include "utility/utility.h"

struct struct_Printer {
  FILE *fp;
  int indent;
  Bool newline;
};

static void printer_fputc(Printer *printer, char c) {
  if (printer->fp) {
    fputc(c, printer->fp);
  }
}
static void printer_print_indent(Printer *printer) {
  if (printer->newline) {
    int i;
    for (i = 0; i < printer->indent; ++i) {
      printer_fputc(printer, ' ');
    }
  }
  printer->newline = false;
}

Printer *printer_new(PrinterFile fp) {
  Printer *printer = UTILITY_MALLOC(Printer);
  printer->fp = fp;
  printer->indent = 0;
  printer->newline = true;
  return printer;
}
void printer_delete(Printer *printer) {
  UTILITY_FREE(printer);
}
void printer_print(Printer *printer, const char *format, ...) {
  if (printer->fp) {
    va_list args;
    va_start(args, format);
    printer_print_indent(printer);
    vfprintf(printer->fp, format, args);
    va_end(args);
  }
}
void printer_indent(Printer *printer, int indent) {
  printer->indent += indent;
}
void printer_newline(Printer *printer) {
  printer_fputc(printer, '\n');
  printer->newline = true;
}
