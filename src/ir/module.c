#include "module.h"

#include "function.h"
#include "global.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"
#include "value.h"

static struct json *ir_module_get_table(struct json *module) {
  return json_get(module, "table");
}
static void ir_module_set_table(struct json *module, struct json *table) {
  json_insert(module, "table", table);
  json_del(table);
}

void ir_module_init(struct json *module) {
  struct json *array = json_new_arr();
  struct json *table = json_new_obj();
  json_insert(module, "functions", array);
  json_del(array);
  ir_module_set_table(module, table);
  ir_global_init(module);
}
void ir_module_finish(struct json *module) {
  ir_global_finish(module);
}
void ir_module_push_scope(struct json *module) {
  struct json *table = ir_module_get_table(module);
  struct json *updated = ir_table_push(table);
  ir_module_set_table(module, updated);
}
void ir_module_pop_scope(struct json *module) {
  struct json *table = ir_module_get_table(module);
  struct json *updated = ir_table_pop(table);
  ir_module_set_table(module, updated);
}
bool_t ir_module_is_global_scope(struct json *module) {
  struct json *table = ir_module_get_table(module);
  return ir_table_is_global(table);
}
void ir_module_push_global(struct json *module, struct json *value) {
  if (ir_value_is_global(value)) {
    struct json *global = ir_global_get(module);
    const char *name = ir_value_get_name(value);
    json_insert(global, name, value);
  }
}
struct json *ir_module_new_instr(struct json *module, const char *tag) {
  struct json *function = json_get(module, "current");
  return ir_function_new_instr(function, tag);
}
struct json *ir_module_new_alloca(struct json *module) {
  struct json *function = json_get(module, "current");
  return ir_function_new_alloca(function);
}
struct json *ir_module_new_identifier(struct json *module,
                                      struct json *identifier) {
  if (ir_module_is_global_scope(module)) {
    return ir_value_new_global(identifier);
  } else {
    return ir_module_new_alloca(module);
  }
}
struct json *ir_module_new_function(struct json *module) {
  struct json *function = json_new_obj();
  struct json *array = json_get(module, "functions");
  json_push(array, function);
  json_insert(module, "current", function);
  return function;
}
void ir_module_insert_symbol(struct json *module, const char *name,
                             struct json *value) {
  struct json *table = ir_module_get_table(module);
  ir_table_insert(table, name, value);
}
struct json *ir_module_lookup_symbol(struct json *module, const char *name) {
  struct json *table = ir_module_get_table(module);
  struct json *value = ir_table_lookup(table, name);
  ir_module_push_global(module, value);
  return value;
}
void ir_module_init_function(struct json *module) {
  struct json *function = ir_module_new_function(module);
  ir_function_init(function);
  ir_module_push_scope(module);
  json_del(function);
}
void ir_module_finish_function(struct json *module) {
  struct json *function = json_get(module, "current");
  ir_function_finish(function);
  ir_module_pop_scope(module);
}
void ir_module_foreach(struct json *module, json_map_t map, void *extra) {
  struct json *functions = json_get(module, "functions");
  json_foreach(functions, map, extra);
}
