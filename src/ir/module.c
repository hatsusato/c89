#include "module.h"

#include "function.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"
#include "value.h"

void ir_module_init(struct json *module) {
  json_set(module, "functions", json_new_arr());
  json_set(module, "table", json_new_obj());
  json_set(module, "global", json_new_obj());
}
void ir_module_finish(struct json *module) {
  struct json *table = json_get(module, "table");
  struct json *global = json_get(module, "global");
  json_merge(global, table);
}
struct json *ir_module_new_function(struct json *module) {
  struct json *function = json_new_obj();
  struct json *array = json_get(module, "functions");
  struct json *table = json_get(module, "table");
  struct json *global = json_get(module, "global");
  json_push(array, function);
  json_insert(module, "current", function);
  json_insert(function, "table", table);
  json_insert(function, "global", global);
  return function;
}
void ir_module_foreach(struct json *module, json_map_t map, void *extra) {
  struct json *functions = json_get(module, "functions");
  json_foreach(functions, map, extra);
}
