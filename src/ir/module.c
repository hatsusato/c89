#include "module.h"

#include "function.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"
#include "util/util.h"
#include "value.h"

void ir_module_init(struct json *module) {
  struct json *table = ir_table_new();
  json_set(module, "functions", json_new_arr());
  json_set(module, "table", table);
  json_insert(module, "global", ir_table_get_global(table));
}
void ir_module_finish(struct json *module) {
  struct json *table = json_get(module, "table");
  ir_table_finish(table);
}
struct json *ir_module_new_function(struct json *module) {
  struct json *array = json_get(module, "functions");
  struct json *table = json_get(module, "table");
  struct json *global = json_get(module, "global");
  struct json *function = ir_function_new(table, global);
  json_push(array, function);
  return function;
}
struct json *ir_module_make_global(struct json *module,
                                   struct json *identifier) {
  struct json *table = json_get(module, "table");
  const char *name = json_get_str(identifier);
  struct json *global = ir_value_new_global(identifier);
  assert(!json_has(table, "$next"));
  ir_table_insert(table, name, global);
  json_del(global);
  return global;
}
void ir_module_insert_global(struct json *module, struct json *global) {
  struct json *table = json_get(module, "table");
  ir_table_insert_global(table, global);
}
void ir_module_foreach(struct json *module, json_map_t map, void *extra) {
  struct json *functions = json_get(module, "functions");
  json_foreach(functions, map, extra);
}
