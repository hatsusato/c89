#include "block.h"

#include "instruction.h"
#include "json/json.h"
#include "json/map.h"

static void generate_block_map(struct json_map *map) {
  struct printer *printer = json_map_extra(map);
  struct json *instr = json_map_val(map);
  generate_instruction(printer, instr);
}
void generate_block(struct printer *printer, struct json *json) {
  json_foreach(json_get(json, "block"), generate_block_map, printer);
}
