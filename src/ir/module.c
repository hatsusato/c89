#include "module.h"

#include "function.h"
#include "global.h"
#include "json/json.h"
#include "table.h"
#include "value.h"

static struct json *ir_module_get_table(struct json *module) {
  return json_get(module, "table");
}
static void ir_module_set_table(struct json *module, struct json *table) {
  json_insert(module, "table", table);
  json_del(table);
}

struct json *ir_module_new(void) {
  struct json *module = json_new_obj();
  struct json *array = json_new_arr();
  struct json *table = json_new_obj();
  json_insert(module, "module", array);
  json_del(array);
  ir_module_set_table(module, table);
  return module;
}
void ir_module_init(struct json *module) {
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
void ir_module_init_function(struct json *module, struct json *name) {
  struct json *function = json_new_obj();
  struct json *array = json_get(module, "module");
  ir_function_init(function, name);
  json_push(array, function);
  json_insert(module, "function", function);
  ir_module_push_scope(module);
  json_del(function);
}
void ir_module_finish_function(struct json *module) {
  struct json *function = json_get(module, "function");
  ir_function_finish(function);
  ir_module_pop_scope(module);
}
