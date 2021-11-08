#include "instruction.h"

#include "json/json.h"
#include "printer/printer.h"
#include "util/util.h"

static void generate_print(struct printer *printer, struct json *obj,
                           const char *key) {
  struct json *str = json_get(obj, key);
  printer_print(printer, "%s", json_get_str(str));
}
static void generate_reg(struct printer *printer, struct json *json) {
  if (json_has(json, "reg")) {
    struct json *reg = json_get(json, "reg");
    printer_print(printer, "%%%d", json_int_get(json_as_int(reg)));
  } else {
    printer_print(printer, "%s", json_get_str(json));
  }
}
static void generate_ret(struct printer *printer, struct json *json) {
  printer_print(printer, "ret i32 ");
  generate_print(printer, json, "value");
}
static void generate_alloca(struct printer *printer, struct json *json) {
  generate_reg(printer, json);
  printer_print(printer, " = alloca i32, align 4");
}
static void generate_store(struct printer *printer, struct json *json) {
  printer_print(printer, "store i32 ");
  generate_reg(printer, json_get(json, "value"));
  printer_print(printer, ", i32* ");
  generate_reg(printer, json_get(json, "pointer"));
  printer_print(printer, ", align 4");
}
void generate_instruction(struct printer *printer, struct json *json) {
  const char *tag = json_get_str(json_get(json, "instr"));
  if (util_streq(tag, "ret")) {
    generate_ret(printer, json);
  } else if (util_streq(tag, "alloca")) {
    generate_alloca(printer, json);
  } else if (util_streq(tag, "store")) {
    generate_store(printer, json);
  } else {
    json_print(json);
    return;
  }
  printer_newline(printer);
}
