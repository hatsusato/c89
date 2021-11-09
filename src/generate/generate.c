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
  const char *name = json_get_str(json_get(global, "name"));
  struct json *init = json_get(global, "init");
  int val = 0;
  if (json_has(init, "immediate")) {
    struct json *immediate = json_get(init, "immediate");
    val = json_int_get(json_as_int(immediate));
  }
  printer_print(printer, "@%s = global i32 %d, align 4", name, val);
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
