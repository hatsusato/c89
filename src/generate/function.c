#include "function.h"

#include "block.h"
#include "json/json.h"
#include "json/map.h"
#include "numbering.h"
#include "printer/printer.h"

static void generate_function_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *block = json_map_val(map);
  generate_block(printer, block);
}
void generate_function(struct printer *printer, struct json *function) {
  struct json *blocks = json_get(function, "function");
  struct json *name = json_get(function, "name");
  generate_numbering(function);
  printer_newline(printer);
  printer_print(printer, "define i32 @");
  printer_print(printer, "%s", json_get_str(name));
  printer_print(printer, "() ");
  printer_open(printer, "{");
  printer_newline(printer);
  json_foreach(blocks, generate_function_map, printer);
  printer_close(printer, "}");
  printer_newline(printer);
}
