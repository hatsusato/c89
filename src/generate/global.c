#include "global.h"

#include "json/json.h"
#include "printer/printer.h"

static void generate_immediate(struct printer *printer, struct json *json) {
  struct json *immediate = json_get(json, "immediate");
  if (json_is_int(immediate)) {
    int val = json_int_get(json_as_int(immediate));
    printer_print(printer, "%d", val);
  }
}

void generate_global(struct printer *printer, struct json *json) {
  struct json *init = json_get(json, "init");
  if (json_is_null(json) || !json_has(json, "global")) {
    return;
  }
  generate_global_name(printer, json);
  printer_print(printer, " = global i32 ");
  if (json_has(init, "immediate")) {
    generate_immediate(printer, init);
  } else {
    printer_print(printer, "0");
  }
  printer_print(printer, ", align 4");
  printer_newline(printer);
}
void generate_global_name(struct printer *printer, struct json *json) {
  struct json *name = json_get(json, "name");
  if (json_is_str(name)) {
    printer_print(printer, "@%s", json_get_str(name));
  }
}
