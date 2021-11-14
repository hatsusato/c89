#include "return.h"

#include "block.h"
#include "json/json.h"

struct json *ir_return_new(struct json *retval) {
  struct json *retobj = json_new_obj();
  json_insert(retobj, "retval", retval);
  json_set(retobj, "retcount", json_new_int(0));
  json_set(retobj, "retblock", ir_block_new());
  return retobj;
}
