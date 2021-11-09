#include "function.h"

#include "alloc.h"
#include "json/json.h"
#include "module.h"
#include "statement.h"
#include "table.h"

static struct json *convert_function_new(void) {
  struct json *json = json_new_obj();
  struct json *function = json_new_arr();
  json_insert(json, "function", function);
  json_del(function);
  return json;
}
static struct json *convert_function_get(struct json *module) {
  return json_get(module, "function");
}

static void convert_function_init(struct json *module) {
  struct json *array = json_get(module, "module");
  struct json *function = convert_function_new();
  json_push(array, function);
  json_del(function);
  json_insert(module, "function", function);
  convert_alloc_init(module);
  convert_table_push(module);
}
static void convert_function_finish(struct json *module) {
  struct json *array = convert_function_get_blocks(module);
  struct json *front = json_front(array);
  struct json *alloc = convert_alloc_finish(module);
  json_append(alloc, json_get(front, "block"));
  json_insert(front, "block", alloc);
  json_del(alloc);
  convert_table_pop(module);
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
