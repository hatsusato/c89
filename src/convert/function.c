#include "function.h"

#include "alloc.h"
#include "ir/function.h"
#include "ir/module.h"
#include "json/json.h"
#include "module.h"
#include "statement.h"

static struct json *convert_function_get(struct json *module) {
  return json_get(module, "function");
}

static void convert_function_init(struct json *module) {
  struct json *array = json_get(module, "module");
  struct json *function = json_new_obj();
  ir_function_init(function);
  json_push(array, function);
  json_del(function);
  json_insert(module, "function", function);
  ir_module_push_scope(module);
}
static void convert_function_finish(struct json *module) {
  struct json *function = convert_function_get(module);
  ir_function_finish(function);
  ir_module_pop_scope(module);
}
static void convert_function_set_name(struct json *module, struct json *name) {
  struct json *function = convert_function_get(module);
  json_insert(function, "name", name);
}

struct json *convert_function_get_blocks(struct json *module) {
  struct json *function = convert_function_get(module);
  return json_get(function, "function");
}
void convert_function_definition(struct json *module, struct json *json) {
  convert_function_init(module);
  convert_function_set_name(module, json_find_identifier(json));
  convert_push_block(module);
  convert_statement(module, json);
  convert_function_finish(module);
}
