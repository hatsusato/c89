#include "printer.h"

#include <stdarg.h>
#include <stdio.h>

#include "utility/utility.h"

struct struct_Printer {
  FILE *fp;
};

Printer *printer_new(PrinterFile fp) {
  Printer *printer = UTILITY_MALLOC(Printer);
  printer->fp = fp;
  return printer;
}
void printer_delete(Printer *printer) {
  UTILITY_FREE(printer);
}
void printer_print(Printer *printer, const char *format, ...) {
  if (printer->fp) {
    va_list args;
    va_start(args, format);
    vfprintf(printer->fp, format, args);
    va_end(args);
  }
}
