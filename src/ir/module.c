#include "module.h"

#include "function.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"
#include "util/symbol.h"

void ir_module_init(struct json *module) {
  json_obj_set(module, SYMBOL_MODULE_FUNCTIONS, json_new_arr());
  json_obj_set(module, SYMBOL_MODULE_TABLE, ir_table_new());
}
void ir_module_finish(struct json *module) {
  struct json *table = ir_module_get_table(module);
  ir_table_finish(table);
}
struct json *ir_module_get_table(struct json *module) {
  return json_obj_get(module, SYMBOL_MODULE_TABLE);
}
struct json *ir_module_make_function(struct json *module) {
  struct json *array = json_obj_get(module, SYMBOL_MODULE_FUNCTIONS);
  struct json *table = ir_module_get_table(module);
  struct json *function = ir_function_new(table);
  json_arr_push(array, function);
  json_del(function);
  return function;
}
void ir_module_foreach_function(struct json *module, json_map_t map,
                                void *extra) {
  struct json *functions = json_obj_get(module, SYMBOL_MODULE_FUNCTIONS);
  json_foreach(functions, map, extra);
}
