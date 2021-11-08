#include "instruction.h"

#include "json/json.h"
#include "printer/printer.h"
#include "util/util.h"

static void generate_print(struct printer *printer, struct json *obj,
                           const char *key) {
  struct json *str = json_get(obj, key);
  printer_print(printer, "%s", json_get_str(str));
}
void generate_instruction(struct printer *printer, struct json *json) {
  const char *tag = json_get_str(json_get(json, "instr"));
  if (util_streq(tag, "ret")) {
    printer_print(printer, "ret i32 ");
    generate_print(printer, json, "value");
    printer_newline(printer);
  } else {
    json_print(json);
  }
}
