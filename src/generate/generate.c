#include "generate.h"

#include "json/json.h"
#include "json/map.h"
#include "printer/printer.h"

static void generate_instr(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *instr = json_map_val(map);
  struct json *tag = json_get(instr, "instr");
  struct json *val = json_get(instr, "value");
  printer_print(printer, "%s i32 %s", json_get_str(tag), json_get_str(val));
  printer_newline(printer);
}
static void generate_block(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *block = json_map_val(map);
  json_foreach(json_get(block, "block"), generate_instr, printer);
}
static void generate_function(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *func = json_map_val(map);
  struct json *name = json_get(func, "name");
  printer_newline(printer);
  printer_print(printer, "define i32 @%s() ", json_get_str(name));
  printer_open(printer, "{");
  printer_newline(printer);
  json_foreach(json_get(func, "function"), generate_block, printer);
  printer_close(printer, "}");
  printer_newline(printer);
}
static void generate_header(struct printer *printer) {
  printer_print(printer, "target triple = ");
  printer_quote(printer, "x86_64-unknown-linux-gnu");
  printer_newline(printer);
}

void generate(struct json *json) {
  struct printer *printer = printer_new_stdout();
  generate_header(printer);
  json_foreach(json_get(json, "module"), generate_function, printer);
  printer_del(printer);
}
