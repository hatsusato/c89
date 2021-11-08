#include "generate.h"

#include "block.h"
#include "json/json.h"
#include "json/map.h"
#include "numbering.h"
#include "printer/printer.h"

static void generate_print(struct printer *printer, struct json *obj,
                           const char *key) {
  struct json *str = json_get(obj, key);
  printer_print(printer, "%s", json_get_str(str));
}
static void generate_function_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *block = json_map_val(map);
  generate_block(printer, block);
}
static void generate_function(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *func = json_map_val(map);
  struct json *blocks = json_get(func, "function");
  generate_numbering(func);
  printer_newline(printer);
  printer_print(printer, "define i32 @");
  generate_print(printer, func, "name");
  printer_print(printer, "() ");
  printer_open(printer, "{");
  printer_newline(printer);
  json_foreach(blocks, generate_function_map, printer);
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
