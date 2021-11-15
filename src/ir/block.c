#include "block.h"

#include "instr.h"
#include "json/json.h"
#include "json/map.h"

struct json *ir_block_new(void) {
  struct json *block = json_new_obj();
  json_set(block, "instructions", json_new_arr());
  json_insert(block, "terminator", json_null());
  return block;
}
struct json *ir_block_make_instr(struct json *block, const char *tag) {
  struct json *instr = ir_instr_new(tag);
  struct json *array = json_get(block, "instructions");
  json_push(array, instr);
  json_del(instr);
  return instr;
}
struct json *ir_block_make_terminator(struct json *block, const char *tag) {
  struct json *terminator = ir_instr_new(tag);
  json_insert(block, "terminator", terminator);
  json_del(terminator);
  return terminator;
}
struct json *ir_block_get_terminator(struct json *block) {
  return json_get(block, "terminator");
}
bool_t ir_block_has_terminator(struct json *block) {
  return !json_is_null(ir_block_get_terminator(block));
}
void ir_block_prepend(struct json *self, struct json *other) {
  struct json *array = json_new_arr();
  json_append(array, json_get(other, "instructions"));
  json_append(array, json_get(self, "instructions"));
  json_insert(self, "instructions", array);
  json_del(array);
}
void ir_block_foreach(struct json *block, json_map_t map, void *extra) {
  struct json *instructions = json_get(block, "instructions");
  json_foreach(instructions, map, extra);
}
