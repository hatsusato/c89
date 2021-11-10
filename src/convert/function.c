#include "function.h"

#include "ir/module.h"
#include "json/json.h"
#include "statement.h"

void convert_function_definition(struct json *module, struct json *json) {
  struct json *name = json_find_identifier(json);
  ir_module_init_function(module, name);
  convert_statement(module, json);
  ir_module_finish_function(module);
}
