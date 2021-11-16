#include "instruction.h"

#include "global.h"
#include "ir/instr.h"
#include "json/json.h"
#include "printer/printer.h"
#include "util/symbol.h"
#include "util/util.h"

static void generate_register(struct printer *printer, struct json *json,
                              const char *key) {
  if (key && json_has(json, key)) {
    json = json_obj_get(json, key);
  }
  if (json_has(json, SYMBOL_IMMEDIATE)) {
    struct json *immediate = json_obj_get(json, SYMBOL_IMMEDIATE);
    assert(json_is_int(immediate));
    printer_print(printer, "%d", json_int_get(immediate));
  } else if (json_has(json, "label")) {
    struct json *label = json_obj_get(json, "label");
    assert(json_is_int(label));
    printer_print(printer, "%%%d", json_int_get(label));
  } else if (ir_instr_has_numbering(json)) {
    int reg = ir_instr_get_numbering(json);
    printer_print(printer, "%%%d", reg);
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
static void generate_br(struct printer *printer, struct json *json) {
  if (json_has(json, "cond")) {
    printer_print(printer, "br i1 ");
    generate_register(printer, json, "cond");
    printer_print(printer, ", label ");
    generate_register(printer, json, "iftrue");
    printer_print(printer, ", label ");
    generate_register(printer, json, "iffalse");
  } else {
    printer_print(printer, "br label ");
    generate_register(printer, json, "dest");
  }
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
static void generate_icmp(struct printer *printer, struct json *json) {
  generate_register(printer, json, NULL);
  printer_print(printer, " = icmp ne i32 ");
  generate_register(printer, json, "lhs");
  printer_print(printer, ", ");
  generate_register(printer, json, "rhs");
}

void generate_instruction(struct printer *printer, struct json *json) {
  if (ir_instr_is_skip(json)) {
    return;
  } else if (ir_instr_check_kind(json, "ret")) {
    generate_ret(printer, json);
  } else if (ir_instr_check_kind(json, "br")) {
    generate_br(printer, json);
  } else if (ir_instr_check_kind(json, "add")) {
    generate_add(printer, json);
  } else if (ir_instr_check_kind(json, "alloca")) {
    generate_alloca(printer, json);
  } else if (ir_instr_check_kind(json, "load")) {
    generate_load(printer, json);
  } else if (ir_instr_check_kind(json, "store")) {
    generate_store(printer, json);
  } else if (ir_instr_check_kind(json, "icmp")) {
    generate_icmp(printer, json);
  } else {
    json_print(json);
    return;
  }
  printer_newline(printer);
}
