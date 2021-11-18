#include "generate.h"

#include "function.h"
#include "global.h"
#include "ir/module.h"
#include "ir/table.h"
#include "json/json.h"
#include "json/map.h"
#include "printer/printer.h"

static void generate_header(struct printer *printer) {
  printer_print(printer, "target triple = ");
  printer_quote(printer, "x86_64-unknown-linux-gnu");
  printer_newline(printer);
}
static void generate_global_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *global = json_map_val(map);
  if (json_map_index(map) == 0) {
    printer_newline(printer);
  }
  generate_global(printer, global);
}
static void generate_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *function = json_map_val(map);
  generate_function(printer, function);
}

void generate(struct json *module) {
  struct printer *printer = printer_new_stdout();
  struct json *table = ir_module_get_table(module);
  generate_header(printer);
  ir_table_foreach_global(table, generate_global_map, printer);
  ir_module_foreach_function(module, generate_map, printer);
  printer_del(printer);
}
