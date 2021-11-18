#include "module.h"

#include "function.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"
#include "util/util.h"
#include "value.h"

void ir_module_init(struct json *module) {
  struct json *table = ir_table_new();
  json_obj_set(module, "functions", json_new_arr());
  json_obj_set(module, "table", table);
}
void ir_module_finish(struct json *module) {
  struct json *table = ir_module_get_table(module);
  ir_table_finish(table);
}
struct json *ir_module_get_table(struct json *module) {
  return json_obj_get(module, "table");
}
struct json *ir_module_make_function(struct json *module) {
  struct json *array = json_obj_get(module, "functions");
  struct json *table = ir_module_get_table(module);
  struct json *function = ir_function_new(table);
  json_arr_push(array, function);
  json_del(function);
  return function;
}
void ir_module_foreach_function(struct json *module, json_map_t map,
                                void *extra) {
  struct json *functions = json_obj_get(module, "functions");
  json_foreach(functions, map, extra);
}
