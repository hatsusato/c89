#include "numbering.h"

#include "ir/block.h"
#include "ir/function.h"
#include "ir/instr.h"
#include "json/json.h"
#include "json/map.h"

static bool_t generate_numbering_has_register(struct json *json) {
  return !(json_has(json, "store") || json_has(json, "ret"));
}
static void generate_numbering_instr(struct json_map *map) {
  index_t *index = json_map_extra(map);
  struct json *instr = json_map_val(map);
  if (generate_numbering_has_register(instr)) {
    ir_instr_set_numbering(instr, (*index)++);
  }
}
static void generate_numbering_block(struct json_map *map) {
  index_t *index = json_map_extra(map);
  struct json *block = json_map_val(map);
  struct json *label = json_new_int((*index)++);
  json_insert(block, "label", label);
  json_del(label);
  ir_block_foreach(block, generate_numbering_instr, index);
}

void generate_numbering(struct json *function) {
  index_t index = 0;
  ir_function_foreach(function, generate_numbering_block, &index);
}
