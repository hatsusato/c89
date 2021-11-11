#include "function.h"

#include "block.h"
#include "instr.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"
#include "value.h"

struct json *ir_function_new(struct json *table) {
  struct json *function = json_new_obj();
  json_insert(function, "table", table);
  return function;
}
void ir_function_init(struct json *function, struct json *definition) {
  struct json *name = json_find_identifier(definition);
  json_set(function, "blocks", json_new_arr());
  json_set(function, "alloc", ir_block_new());
  json_insert(function, "front", ir_function_make_block(function));
  ir_function_set_name(function, name);
  ir_function_push_scope(function);
}
void ir_function_finish(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *front = json_get(function, "front");
  ir_block_prepend(front, alloc);
  ir_function_pop_scope(function);
  json_insert(function, "alloc", json_null());
  json_insert(function, "front", json_null());
  json_insert(function, "current", json_null());
  json_insert(function, "table", json_null());
}
void ir_function_push_scope(struct json *function) {
  struct json *table = json_get(function, "table");
  struct json *updated = ir_table_push(table);
  json_set(function, "table", updated);
}
void ir_function_pop_scope(struct json *function) {
  struct json *table = json_get(function, "table");
  struct json *updated = ir_table_pop(table);
  json_set(function, "table", updated);
}
void ir_function_insert_symbol(struct json *function, const char *key,
                               struct json *val) {
  struct json *table = json_get(function, "table");
  ir_table_insert(table, key, val);
}
struct json *ir_function_lookup_symbol(struct json *function, const char *key) {
  struct json *table = json_get(function, "table");
  struct json *value = ir_table_lookup(table, key);
  ir_table_insert_global(table, value);
  return value;
}
struct json *ir_function_make_block(struct json *function) {
  struct json *array = json_get(function, "blocks");
  struct json *block = ir_block_new();
  json_push(array, block);
  json_insert(function, "current", block);
  json_del(block);
  return block;
}
struct json *ir_function_make_instr(struct json *function, const char *tag) {
  struct json *block = json_get(function, "current");
  struct json *instr = ir_instr_new(tag);
  ir_block_push_instr(block, instr);
  json_del(instr);
  return instr;
}
struct json *ir_function_new_alloca(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *instr = ir_instr_new("alloca");
  ir_block_push_instr(alloc, instr);
  return instr;
}
void ir_function_set_name(struct json *function, struct json *name) {
  json_insert(function, "name", name);
}
const char *ir_function_get_name(struct json *function) {
  struct json *name = json_get(function, "name");
  return json_get_str(name);
}
void ir_function_foreach(struct json *function, json_map_t map, void *extra) {
  struct json *blocks = json_get(function, "blocks");
  json_foreach(blocks, map, extra);
}
