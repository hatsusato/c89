#include "function.h"

#include "block.h"
#include "instr.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"

static struct json *ir_function_get_table(struct json *function) {
  return json_get(function, "table");
}
static void ir_function_set_table(struct json *function, struct json *table) {
  json_insert(function, "table", table);
  json_del(table);
}

void ir_function_init(struct json *function) {
  struct json *array = json_new_arr();
  struct json *alloc = json_new_arr();
  struct json *block;
  json_insert(function, "blocks", array);
  json_del(array);
  json_insert(function, "alloc", alloc);
  json_del(alloc);
  block = ir_function_new_block(function);
  json_insert(function, "front", block);
  json_del(block);
}
void ir_function_finish(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *front = json_get(function, "front");
  struct json *block = json_get(front, "instructions");
  json_append(alloc, block);
  json_insert(front, "instructions", alloc);
  json_insert(function, "alloc", json_null());
}
void ir_function_push_scope(struct json *function) {
  struct json *table = ir_function_get_table(function);
  struct json *updated = ir_table_push(table);
  ir_function_set_table(function, updated);
}
void ir_function_pop_scope(struct json *function) {
  struct json *table = ir_function_get_table(function);
  struct json *updated = ir_table_pop(table);
  ir_function_set_table(function, updated);
}
struct json *ir_function_new_block(struct json *function) {
  struct json *block = ir_block_new();
  struct json *array = json_get(function, "blocks");
  json_push(array, block);
  json_insert(function, "current", block);
  return block;
}
struct json *ir_function_new_instr(struct json *function, const char *tag) {
  struct json *instr = ir_instr_new(tag);
  struct json *block = json_get(function, "current");
  struct json *array = json_get(block, "instructions");
  json_push(array, instr);
  return instr;
}
struct json *ir_function_new_alloca(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *instr = ir_instr_new("alloca");
  json_push(alloc, instr);
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
