#include "global.h"

#include "json/json.h"
#include "printer/printer.h"

void generate_global(struct printer *printer, struct json *json) {
  const char *name = json_get_str(json_get(json, "name"));
  struct json *init = json_get(json, "init");
  int val = 0;
  if (json_has(init, "immediate")) {
    struct json *immediate = json_get(init, "immediate");
    val = json_int_get(json_as_int(immediate));
  }
  printer_print(printer, "@%s = global i32 %d, align 4", name, val);
  printer_newline(printer);
}
