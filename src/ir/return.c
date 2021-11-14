#include "return.h"

#include "block.h"
#include "instr.h"
#include "json/json.h"
#include "json/map.h"

static struct json *ir_return_block_new(struct json *retval) {
  struct json *retblock = ir_block_new();
  struct json *load = ir_instr_new("load");
  struct json *ret = ir_block_new_terminator(retblock, "ret");
  ir_block_push_instr(retblock, load);
  ir_instr_insert(load, "pointer", retval);
  json_del(load);
  ir_instr_insert(ret, "value", load);
  json_del(ret);
  return retblock;
}

struct json *ir_return_new(struct json *retval) {
  struct json *retobj = json_new_obj();
  struct json *retblock = ir_return_block_new(retval);
  json_insert(retobj, "retval", retval);
  json_set(retobj, "retcount", json_new_int(0));
  json_set(retobj, "retblock", retblock);
  return retobj;
}
int ir_return_get_count(struct json *retobj) {
  struct json *retcount = json_get(retobj, "retcount");
  return json_int_get(json_as_int(retcount));
}
void ir_return_skip(struct json *retobj) {
  struct json *retval = json_get(retobj, "retval");
  ir_instr_set_skip(retval);
}
void ir_return_finish_map(struct json_map *map) {
  struct json *block = json_map_val(map);
  struct json *retobj = json_map_extra(map);
  struct json *retval = json_get(retobj, "retval");
  struct json *retblock = json_get(retobj, "retblock");
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
