#ifndef INCLUDE_GUARD_DBC01AAE_EE94_4490_B009_30C1CDA3E9FF
#define INCLUDE_GUARD_DBC01AAE_EE94_4490_B009_30C1CDA3E9FF

#include "printer/typedef.h"
#include "utility/types.h"

Printer *printer_new(PrinterFile);
void printer_delete(Printer *);
void printer_print(Printer *, const char *, ...);
void printer_indent(Printer *, int);
void printer_newline(Printer *);

#endif /* INCLUDE_GUARD_DBC01AAE_EE94_4490_B009_30C1CDA3E9FF */
