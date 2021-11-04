#include "generate.h"

#include "json/json.h"
#include "json/map.h"
#include "printer/printer.h"
#include "util/util.h"

static void generate_header(struct printer *printer) {
  printer_print(printer, "target triple = ");
  printer_quote(printer, "x86_64-unknown-linux-gnu");
  printer_newline(printer);
}
static void generate_function(struct json_map *map) {
  struct printer *printer = map->extra;
  struct json *name = json_get(map->val, "name");
  assert(json_is_str(name));
  printer_newline(printer);
  printer_print(printer, "define i32 @%s() ", json_get_str(name));
  printer_open(printer, "{");
  printer_newline(printer);
  printer_print(printer, "ret i32 0");
  printer_newline(printer);
  printer_close(printer, "}");
  printer_newline(printer);
}
void generate(struct json *json) {
  struct printer *printer = printer_new_stdout();
  struct json *module = json_get(json, "module");
  struct json_map map;
  generate_header(printer);
  map.map = generate_function;
  map.extra = printer;
  assert(json_is_arr(module));
  json_arr_foreach(json_as_arr(module), &map);
  printer_del(printer);
}