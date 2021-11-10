#include "function.h"

#include "ir/module.h"
#include "json/json.h"
#include "statement.h"

static struct json *convert_function_get(struct json *module) {
  return json_get(module, "function");
}

struct json *convert_function_get_blocks(struct json *module) {
  struct json *function = convert_function_get(module);
  return json_get(function, "function");
}
void convert_function_definition(struct json *module, struct json *json) {
  struct json *name = json_find_identifier(json);
  ir_module_init_function(module, name);
  convert_statement(module, json);
  ir_module_finish_function(module);
}
