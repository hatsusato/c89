#include "print.h"

#include <stdio.h>

#include "printer/printer.h"
#include "struct.h"

void type_print(Type *type, Printer *printer) {
  if (!type) {
    return;
  }
  switch (type->kind) {
  case TYPE_INTEGER:
    if (0 == type->data.size) {
      printer_print(printer, "void");
    } else {
      printer_print(printer, "i%d", type->data.size);
    }
    break;
  case TYPE_POINTER:
    type_print(type->data.type, printer);
    printer_print(printer, "*");
    break;
  case TYPE_LABEL:
    printer_print(printer, "label");
    break;
  default:
    printer_print(printer, "null");
    break;
  }
}
void type_print_elem(Type *type) {
  if (TYPE_POINTER == type->kind) {
    type_print(type->data.type, NULL);
  }
}
void type_print_align(Type *type) {
  if (TYPE_INTEGER == type->kind) {
    printf(", align %d", type->data.size / 8);
  }
}
