#include "global.h"

#include "json/json.h"
#include "printer/printer.h"

struct json *generate_global_get(struct json *module) {
  return json_get(module, "global");
}
void generate_global(struct printer *printer, struct json *json) {
  struct json *init = json_get(json, "init");
  int val = 0;
  if (json_has(init, "immediate")) {
    struct json *immediate = json_get(init, "immediate");
    val = json_int_get(json_as_int(immediate));
  }
  generate_global_name(printer, json);
  printer_print(printer, " = global i32 %d, align 4", val);
  printer_newline(printer);
}
void generate_global_name(struct printer *printer, struct json *json) {
  struct json *name = json_get(json, "name");
  if (json_is_str(name)) {
    printer_print(printer, "@%s", json_get_str(name));
  }
}
