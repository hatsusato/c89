#include "return.h"

#include "block.h"
#include "instr.h"
#include "json/json.h"
#include "json/map.h"

static struct json *ir_return_block_new(struct json *retval) {
  struct json *retblock = ir_block_new();
  struct json *load = ir_block_make_instr(retblock, "load");
  struct json *ret = ir_block_make_terminator(retblock, "ret");
  ir_instr_insert(load, "pointer", retval);
  ir_instr_insert(ret, "value", load);
  return retblock;
}

struct json *ir_return_new(struct json *retval) {
  struct json *retobj = json_new_obj();
  struct json *retblock = ir_return_block_new(retval);
  json_obj_insert(retobj, "retval", retval);
  json_obj_set(retobj, "retblock", retblock);
  json_obj_set(retobj, "blocks", json_new_arr());
  return retobj;
}
static void ir_return_set_block_terminator(struct json *retobj,
                                           struct json *block) {
  struct json *retblock = json_obj_get(retobj, "retblock");
  struct json *br = ir_block_make_terminator(block, "br");
  ir_instr_insert(br, "dest", retblock);
}
static void ir_return_finish_map(struct json_map *map) {
  struct json *block = json_map_val(map);
  struct json *retobj = json_map_extra(map);
  struct json *retval = json_obj_get(retobj, "retval");
  struct json *terminator = ir_block_get_terminator(block);
  if (ir_instr_check_kind(terminator, "ret")) {
    struct json *value = json_obj_get(terminator, "value");
    struct json *instr = ir_block_make_instr(block, "store");
    ir_instr_insert(instr, "value", value);
    ir_instr_insert(instr, "pointer", retval);
    ir_return_set_block_terminator(retobj, block);
  }
}
struct json *ir_return_finish(struct json *retobj) {
  struct json *array = json_obj_get(retobj, "blocks");
  if (json_arr_count(array) < 2) {
    struct json *retval = json_obj_get(retobj, "retval");
    ir_instr_set_skip(retval);
    return json_null();
  } else {
    json_foreach(array, ir_return_finish_map, retobj);
    return json_obj_get(retobj, "retblock");
  }
}
void ir_return_push(struct json *retobj, struct json *block) {
  struct json *array = json_obj_get(retobj, "blocks");
  json_arr_push(array, block);
}
