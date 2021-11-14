#include "function.h"

#include "block.h"
#include "instr.h"
#include "json/json.h"
#include "json/map.h"
#include "return.h"
#include "table.h"
#include "value.h"

static void ir_function_push_return_block(struct json *function) {
  struct json *retobj = json_get(function, "retobj");
  struct json *retblock = json_get(retobj, "retblock");
  struct json *array = json_get(function, "blocks");
  json_push(array, retblock);
}

struct json *ir_function_new(struct json *table) {
  struct json *function = json_new_obj();
  json_set(function, "alloc", ir_block_new());
  json_set(function, "blocks", json_new_arr());
  json_insert(function, "table", table);
  return function;
}
void ir_function_init(struct json *function, struct json *definition) {
  struct json *name = json_find_identifier(definition);
  struct json *retval = ir_function_make_alloca(function);
  json_set(function, "retobj", ir_return_new(retval));
  json_insert(function, "entry", ir_function_make_block(function));
  ir_function_set_name(function, name);
  ir_function_push_scope(function);
}
static void ir_function_finish_return(struct json_map *map) {
  struct json *block = json_map_val(map);
  struct json *retobj = json_map_extra(map);
  struct json *retval = json_get(retobj, "retval");
  struct json *retblock = json_get(retobj, "retblock");
  ir_block_finish_return(block, retval, retblock);
}
void ir_function_finish(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *entry = json_get(function, "entry");
  struct json *retobj = json_get(function, "retobj");
  struct json *count = json_get(retobj, "retcount");
  ir_block_prepend(entry, alloc);
  ir_function_pop_scope(function);
  json_insert(function, "alloc", json_null());
  json_insert(function, "entry", json_null());
  json_insert(function, "current", json_null());
  json_insert(function, "table", json_null());
  if (json_int_get(json_as_int(count)) < 2) {
    struct json *retval = json_get(retobj, "retval");
    ir_instr_set_skip(retval);
  } else {
    ir_function_foreach(function, ir_function_finish_return, retobj);
    ir_function_push_return_block(function);
  }
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
void ir_function_insert_symbol(struct json *function, struct json *name,
                               struct json *val) {
  struct json *table = json_get(function, "table");
  const char *key = json_get_str(name);
  ir_table_insert(table, key, val);
}
struct json *ir_function_lookup_symbol(struct json *function,
                                       struct json *name) {
  struct json *table = json_get(function, "table");
  const char *key = json_get_str(name);
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
struct json *ir_function_make_alloca(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *instr = ir_instr_new("alloca");
  ir_block_push_instr(alloc, instr);
  json_del(instr);
  return instr;
}
struct json *ir_function_get_block(struct json *function) {
  return json_get(function, "current");
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
void ir_function_increment_return(struct json *function) {
  struct json *retobj = json_get(function, "retobj");
  struct json *count = json_get(retobj, "retcount");
  int num = json_int_get(json_as_int(count));
  json_int_set(json_as_int(count), num + 1);
}
