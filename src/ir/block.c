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
void ir_block_push_instr(struct json *block, struct json *instr) {
  struct json *array = json_get(block, "instructions");
  json_push(array, instr);
}
struct json *ir_block_new_terminator(struct json *block, const char *tag) {
  struct json *terminator = ir_instr_new(tag);
  json_insert(block, "terminator", terminator);
  return terminator;
}
struct json *ir_block_get_terminator(struct json *block) {
  return json_get(block, "terminator");
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
void ir_block_finish_return(struct json *block, struct json *retval,
                            struct json *retblock) {
  struct json *terminator = ir_block_get_terminator(block);
  if (ir_instr_check_kind(terminator, "ret")) {
    struct json *value = json_get(terminator, "value");
    struct json *instr = ir_instr_new("store");
    ir_block_push_instr(block, instr);
    ir_instr_insert(instr, "value", value);
    ir_instr_insert(instr, "pointer", retval);
    json_del(instr);
    {
      struct json *br = ir_block_new_terminator(block, "br");
      ir_instr_insert(br, "dest", retblock);
      json_del(br);
    }
  }
}
