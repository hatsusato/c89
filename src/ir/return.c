#include "return.h"

#include "block.h"
#include "instr.h"
#include "json/json.h"

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
