#include "block.h"

#include "json/json.h"

struct json *ir_block_new(void) {
  struct json *block = json_new_obj();
  struct json *array = json_new_arr();
  json_insert(block, "block", array);
  json_del(array);
  return block;
}
