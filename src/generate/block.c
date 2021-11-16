#include "block.h"

#include "instruction.h"
#include "ir/block.h"
#include "json/json.h"
#include "json/map.h"
#include "printer/printer.h"
#include "util/util.h"

static void generate_block_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *instr = json_map_val(map);
  generate_instruction(printer, instr);
}
void generate_block(struct printer *printer, struct json *json) {
  struct json *terminator = ir_block_get_terminator(json);
  ir_block_foreach(json, generate_block_map, printer);
  generate_instruction(printer, terminator);
}
void generate_block_label(struct printer *printer, struct json *block) {
  struct json *label = json_get(block, "label");
  int num = json_int_get(label);
  assert(json_is_int(label));
  printer_print(printer, "%d:", num);
}
