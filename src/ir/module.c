#include "module.h"

#include "function.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"
#include "value.h"

static void ir_module_init_obj(struct json *module, const char *key) {
  struct json *value = json_new_obj();
  json_insert(module, key, value);
  json_del(value);
}
static struct json *ir_module_get_global(struct json *module) {
  return json_get(module, "global");
}

void ir_module_init(struct json *module) {
  struct json *array = json_new_arr();
  json_insert(module, "functions", array);
  json_del(array);
  ir_module_init_obj(module, "table");
  ir_module_init_obj(module, "global");
}
void ir_module_finish(struct json *module) {
  struct json *table = json_get(module, "table");
  struct json *global = ir_module_get_global(module);
  json_merge(global, table);
}
struct json *ir_module_new_function(struct json *module) {
  struct json *function = json_new_obj();
  struct json *array = json_get(module, "functions");
  struct json *table = json_get(module, "table");
  struct json *global = ir_module_get_global(module);
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
