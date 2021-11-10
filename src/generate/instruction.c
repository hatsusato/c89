#include "instruction.h"

#include "global.h"
#include "json/json.h"
#include "printer/printer.h"
#include "util/util.h"

static void generate_register(struct printer *printer, struct json *json,
                              const char *key) {
  if (key && json_has(json, key)) {
    json = json_get(json, key);
  }
  if (json_has(json, "immediate")) {
    struct json *immediate = json_get(json, "immediate");
    assert(json_is_int(immediate));
    printer_print(printer, "%d", json_int_get(json_as_int(immediate)));
  } else if (json_has(json, "reg")) {
    struct json *reg = json_get(json, "reg");
    printer_print(printer, "%%%d", json_int_get(json_as_int(reg)));
  } else if (json_has(json, "global")) {
    generate_global_name(printer, json);
  } else {
    printer_print(printer, "%s", json_get_str(json));
  }
}
/* Terminator Instructions */
static void generate_ret(struct printer *printer, struct json *json) {
  printer_print(printer, "ret i32 ");
  generate_register(printer, json, "value");
}
/* Unary Operations */
/* Binary Operations */
static void generate_add(struct printer *printer, struct json *json) {
  generate_register(printer, json, NULL);
  printer_print(printer, " = add nsw i32 ");
  generate_register(printer, json, "lhs");
  printer_print(printer, ", ");
  generate_register(printer, json, "rhs");
}
/* Bitwise Binary Operations */
/* Vector Operations */
/* Aggregate Operations */
/* Memory Access and Addressing Operations */
static void generate_alloca(struct printer *printer, struct json *json) {
  generate_register(printer, json, NULL);
  printer_print(printer, " = alloca i32, align 4");
}
static void generate_load(struct printer *printer, struct json *json) {
  generate_register(printer, json, NULL);
  printer_print(printer, " = load i32, i32* ");
  generate_register(printer, json, "pointer");
  printer_print(printer, ", align 4");
}
static void generate_store(struct printer *printer, struct json *json) {
  printer_print(printer, "store i32 ");
  generate_register(printer, json, "value");
  printer_print(printer, ", i32* ");
  generate_register(printer, json, "pointer");
  printer_print(printer, ", align 4");
}
/* Conversion Operations */
/* Other Operations */

void generate_instruction(struct printer *printer, struct json *json) {
  if (json_has(json, "ret")) {
    generate_ret(printer, json);
  } else if (json_has(json, "add")) {
    generate_add(printer, json);
  } else if (json_has(json, "alloca")) {
    generate_alloca(printer, json);
  } else if (json_has(json, "load")) {
    generate_load(printer, json);
  } else if (json_has(json, "store")) {
    generate_store(printer, json);
  } else {
    json_print(json);
    return;
  }
  printer_newline(printer);
}
