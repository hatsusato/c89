#include "global.h"

#include "ir/constant.h"
#include "ir/module.h"
#include "ir/type.h"
#include "ir/value.h"
#include "printer/printer.h"
#include "utility/utility.h"

struct struct_Global {
  ValueKind kind;
  Type *type;
  const char *name;
  Constant *init;
  Bool prior;
};

Global *global_new(Module *module, const char *name, Type *type) {
  Global *global = UTILITY_MALLOC(Global);
  global->kind = VALUE_GLOBAL;
  global->type = type;
  global->name = name;
  global->init = NULL;
  global->prior = false;
  module_insert_value(module, value_of(global));
  return global;
}
void global_delete(Global *global) {
  UTILITY_FREE(global);
}
Type *global_type(Global *global) {
  return global->type;
}
void global_set_init(Global *global, Constant *init) {
  global->init = init;
}
Bool global_is_prior(Global *global) {
  return global->prior;
}
void global_set_prior(Global *global) {
  global->prior = true;
}
void global_print(Global *global, Printer *printer) {
  UTILITY_ASSERT(global->name);
  printer_print(printer, "@%s", global->name);
}
void global_print_type(Global *global, Printer *printer) {
  type_print(global->type, printer);
  printer_print(printer, "*");
}
void global_pretty(Global *global, Printer *printer) {
  global_print(global, printer);
  printer_print(printer, " = global ");
  type_print(global->type, printer);
  printer_print(printer, " ");
  if (global->init) {
    constant_print(global->init, printer);
  } else {
    printer_print(printer, "0");
  }
  printer_print(printer, ", align 4");
  printer_newline(printer);
}
