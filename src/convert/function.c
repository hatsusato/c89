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

static void convert_function_set_name(struct json *module, struct json *name) {
  struct json *function = convert_function_get(module);
  json_insert(function, "name", name);
}

struct json *convert_function_get_blocks(struct json *module) {
  struct json *function = convert_function_get(module);
  return json_get(function, "function");
}
void convert_function_definition(struct json *module, struct json *json) {
  ir_module_init_function(module);
  convert_function_set_name(module, json_find_identifier(json));
  convert_push_block(module);
  convert_statement(module, json);
  ir_module_finish_function(module);
}
