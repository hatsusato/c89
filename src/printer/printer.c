#include "printer.h"

#include <stdarg.h>
#include <stdio.h>

#include "utility/utility.h"

struct struct_Printer {
  FILE *fp;
  int indent;
  Bool newline;
};

static void printer_fputc(Printer *printer, char c, int n) {
  FILE *fp = printer ? printer->fp : stdout;
  if (fp) {
    int i;
    for (i = 0; i < n; ++i) {
      fputc(c, fp);
    }
  }
}
static void printer_vfprintf(Printer *printer, const char *format,
                             va_list args) {
  FILE *fp = printer ? printer->fp : stdout;
  if (fp) {
    vfprintf(fp, format, args);
  }
}
static void printer_print_indent(Printer *printer) {
  if (printer) {
    if (printer->newline) {
      printer_fputc(printer, ' ', printer->indent);
    }
    printer->newline = false;
  }
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
  va_list args;
  va_start(args, format);
  printer_print_indent(printer);
  printer_vfprintf(printer, format, args);
  va_end(args);
}
void printer_indent(Printer *printer, int indent) {
  if (printer) {
    printer->indent += indent;
  }
}
void printer_newline(Printer *printer) {
  printer_fputc(printer, '\n', 1);
  if (printer) {
    printer->newline = true;
  }
}
