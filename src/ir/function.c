#include "function.h"

#include "block.h"
#include "instr.h"
#include "json/json.h"
#include "json/map.h"
#include "return.h"
#include "table.h"
#include "value.h"

static void ir_function_clear(struct json *function, const char *key) {
  json_obj_insert(function, key, json_null());
}
static void ir_function_finish_alloc(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *entry = json_get(function, "entry");
  ir_block_prepend(entry, alloc);
}

struct json *ir_function_new(struct json *table) {
  struct json *function = json_new_obj();
  json_set(function, "alloc", ir_block_new());
  json_set(function, "blocks", json_new_arr());
  json_obj_insert(function, "table", table);
  json_obj_insert(function, "next", json_null());
  return function;
}
void ir_function_init(struct json *function, struct json *definition) {
  struct json *name = json_find_identifier(definition);
  struct json *retval = ir_function_make_alloca(function);
  struct json *entry = ir_block_new();
  json_set(function, "retobj", ir_return_new(retval));
  ir_function_push_block(function, entry);
  json_obj_insert(function, "entry", entry);
  json_del(entry);
  ir_function_set_name(function, name);
  ir_function_push_scope(function);
}
void ir_function_finish(struct json *function) {
  struct json *retobj = json_get(function, "retobj");
  ir_function_finish_alloc(function);
  ir_function_pop_scope(function);
  ir_function_clear(function, "alloc");
  ir_function_clear(function, "entry");
  ir_function_clear(function, "current");
  ir_function_clear(function, "table");
  if (ir_return_get_count(retobj) < 2) {
    ir_return_skip(retobj);
  } else {
    struct json *retblock = json_get(retobj, "retblock");
    ir_function_foreach(function, ir_return_finish_map, retobj);
    ir_function_push_block(function, retblock);
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
struct json *ir_function_make_instr(struct json *function, const char *tag) {
  struct json *block = json_get(function, "current");
  return ir_block_make_instr(block, tag);
}
struct json *ir_function_make_alloca(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  return ir_block_make_instr(alloc, "alloca");
}
struct json *ir_function_get_block(struct json *function) {
  return json_get(function, "current");
}
void ir_function_push_block(struct json *function, struct json *block) {
  struct json *array = json_get(function, "blocks");
  json_arr_push(array, block);
  json_obj_insert(function, "current", block);
}
void ir_function_next_block(struct json *function, struct json *block) {
  struct json *prev = ir_function_get_block(function);
  struct json *next = ir_function_get_next(function);
  if (!ir_block_has_terminator(prev)) {
    struct json *terminator = ir_block_make_terminator(prev, "br");
    ir_instr_insert(terminator, "dest", json_is_null(next) ? block : next);
  }
  ir_function_push_block(function, block);
}
void ir_function_set_next(struct json *function, struct json *next) {
  json_obj_insert(function, "next", next);
}
struct json *ir_function_get_next(struct json *function) {
  return json_get(function, "next");
}
void ir_function_set_name(struct json *function, struct json *name) {
  json_obj_insert(function, "name", name);
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
  ir_return_increment(retobj);
}
