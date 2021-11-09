#include "module.h"

#include "function.h"
#include "json/json.h"
#include "table.h"

struct json *convert_module_new(void) {
  struct json *module = json_new_obj();
  struct json *array = json_new_arr();
  struct json *global = json_new_arr();
  json_insert(module, "module", array);
  json_del(array);
  json_insert(module, "global", global);
  json_del(global);
  convert_table_push(module);
  return module;
}
static struct json *convert_new_block(void) {
  struct json *json = json_new_obj();
  struct json *block = json_new_arr();
  json_insert(json, "block", block);
  json_del(block);
  return json;
}
void convert_push_block(struct json *module) {
  struct json *array = convert_function_get_blocks(module);
  struct json *block = convert_new_block();
  json_push(array, block);
  json_insert(module, "block", block);
  json_del(block);
}
struct json *convert_new_instr(const char *instr) {
  struct json *json = json_new_obj();
  json_insert_str(json, "instr", instr);
  return json;
}
struct json *convert_push_instr(struct json *module, const char *tag) {
  struct json *block = json_get(module, "block");
  struct json *array = json_get(block, "block");
  struct json *instr = convert_new_instr(tag);
  json_push(array, instr);
  json_del(instr);
  return instr;
}
