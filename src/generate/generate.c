#include "generate.h"

#include "function.h"
#include "global.h"
#include "ir/module.h"
#include "json/json.h"
#include "json/map.h"
#include "printer/printer.h"

static void generate_header(struct printer *printer) {
  printer_print(printer, "target triple = ");
  printer_quote(printer, "x86_64-unknown-linux-gnu");
  printer_newline(printer);
  printer_newline(printer);
}
static void generate_global_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *global = json_map_val(map);
  generate_global(printer, global);
}
static void generate_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *function = json_map_val(map);
  generate_function(printer, function);
}

void generate(struct json *module) {
  struct printer *printer = printer_new_stdout();
  struct json *global = generate_global_get(module);
  generate_header(printer);
  json_foreach(global, generate_global_map, printer);
  ir_module_foreach(module, generate_map, printer);
  printer_del(printer);
}
