#include "block.h"

#include "json/json.h"
#include "json/map.h"

struct json *ir_block_new(void) {
  struct json *block = json_new_obj();
  struct json *array = json_new_arr();
  json_insert(block, "instructions", array);
  json_del(array);
  return block;
}
void ir_block_push_instr(struct json *block, struct json *instr) {
  struct json *array = json_get(block, "instructions");
  json_push(array, instr);
}
void ir_block_foreach(struct json *block, json_map_t map, void *extra) {
  struct json *instructions = json_get(block, "instructions");
  json_foreach(instructions, map, extra);
}
