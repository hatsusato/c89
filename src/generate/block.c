#include "block.h"

#include "instruction.h"
#include "ir/block.h"
#include "json/map.h"

static void generate_block_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *instr = json_map_val(map);
  generate_instruction(printer, instr);
}
void generate_block(struct printer *printer, struct json *json) {
  ir_block_foreach(json, generate_block_map, printer);
}
