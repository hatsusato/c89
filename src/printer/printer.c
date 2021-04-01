#include "printer.h"

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
