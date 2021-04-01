#include "printer.h"

#include <stdio.h>

#include "utility/utility.h"

struct struct_Printer {
  FILE *fp;
};

Printer *printer_new(void) {
  Printer *printer = UTILITY_MALLOC(Printer);
  printer->fp = NULL;
  return printer;
}
void printer_delete(Printer *printer) {
  UTILITY_FREE(printer);
}
