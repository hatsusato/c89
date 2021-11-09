#include "generate.h"

#include "function.h"
#include "json/json.h"
#include "json/map.h"
#include "printer/printer.h"

static void generate_header(struct printer *printer) {
  printer_print(printer, "target triple = ");
  printer_quote(printer, "x86_64-unknown-linux-gnu");
  printer_newline(printer);
}
static void generate_global(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *global = json_map_val(map);
  struct json *name = json_get(global, "name");
  printer_print(printer, "@%s", json_get_str(name));
  printer_print(printer, " = global i32 0, align 4");
  printer_newline(printer);
}
static void generate_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *function = json_map_val(map);
  generate_function(printer, function);
}

void generate(struct json *json) {
  struct printer *printer = printer_new_stdout();
  struct json *functions = json_get(json, "module");
  struct json *global = json_get(json, "global");
  generate_header(printer);
  json_foreach(global, generate_global, printer);
  json_foreach(functions, generate_map, printer);
  printer_del(printer);
}
