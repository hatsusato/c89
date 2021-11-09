#include "type.h"

#include "function.h"
#include "json/json.h"
#include "table.h"

static struct json *convert_new_block(void) {
  struct json *json = json_new_obj();
  struct json *block = json_new_arr();
  json_insert(json, "block", block);
  json_del(block);
  return json;
}
static struct json *convert_new_instr(const char *instr) {
  struct json *json = json_new_obj();
  json_insert_str(json, "instr", instr);
  return json;
}

struct json *convert_new_module(void) {
  struct json *json = json_new_obj();
  struct json *module = json_new_arr();
  struct json *table = json_new_obj();
  json_insert(json, "module", module);
  json_insert(json, "table", table);
  json_del(table);
  json_del(module);
  return json;
}
void convert_push_block(struct json *module) {
  struct json *array = convert_function_get_blocks(module);
  struct json *block = convert_new_block();
  json_push(array, block);
  json_insert(module, "block", block);
  json_del(block);
}
struct json *convert_push_instr(struct json *module, const char *tag) {
  struct json *block = json_get(module, "block");
  struct json *array = json_get(block, "block");
  struct json *instr = convert_new_instr(tag);
  json_push(array, instr);
  json_del(instr);
  return instr;
}
