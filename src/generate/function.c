#include "function.h"

#include "block.h"
#include "ir/function.h"
#include "json/map.h"
#include "numbering.h"
#include "printer/printer.h"

static void generate_function_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *block = json_map_val(map);
  if (0 < json_map_index(map)) {
    printer_newline(printer);
    printer_close(printer, "");
    generate_block_label(printer, block);
    printer_open(printer, "");
    printer_newline(printer);
  }
  generate_block(printer, block);
}
void generate_function(struct printer *printer, struct json *function) {
  const char *name = ir_function_get_name(function);
  generate_numbering(function);
  printer_newline(printer);
  printer_print(printer, "define i32 @");
  printer_print(printer, "%s", name);
  printer_print(printer, "() ");
  printer_open(printer, "{");
  printer_newline(printer);
  ir_function_foreach(function, generate_function_map, printer);
  printer_close(printer, "}");
  printer_newline(printer);
}
