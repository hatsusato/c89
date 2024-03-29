#include "table.h"

#include "json/json.h"
#include "json/map.h"
#include "util/symbol.h"
#include "util/util.h"
#include "value.h"

struct json *ir_table_new(void) {
  struct json *table = json_new_obj();
  json_obj_set(table, SYMBOL_TABLE_GLOBAL, json_new_obj());
  json_obj_set(table, SYMBOL_TABLE_SYMBOLS, json_new_obj());
  return table;
}
void ir_table_push(struct json *table) {
  struct json *symbols = json_new_obj();
  struct json *next = json_obj_get(table, SYMBOL_TABLE_SYMBOLS);
  json_obj_insert(symbols, SYMBOL_TABLE_NEXT, next);
  json_obj_set(table, SYMBOL_TABLE_SYMBOLS, symbols);
}
void ir_table_pop(struct json *table) {
  struct json *symbols = json_obj_get(table, SYMBOL_TABLE_SYMBOLS);
  struct json *next = json_obj_get(symbols, SYMBOL_TABLE_NEXT);
  json_ref(next);
  json_obj_set(table, SYMBOL_TABLE_SYMBOLS, next);
}
void ir_table_insert(struct json *table, struct json *identifier,
                     struct json *value) {
  struct json *symbols = json_obj_get(table, SYMBOL_TABLE_SYMBOLS);
  const char *name = json_get_str(identifier);
  assert(!json_has(symbols, name));
  assert(!util_streq(SYMBOL_TABLE_NEXT, name));
  json_obj_insert(symbols, name, value);
}
static struct json *ir_table_symbols_find(struct json *symbols,
                                          const char *name) {
  while (json_is_obj(symbols) && !json_has(symbols, name)) {
    symbols = json_obj_get(symbols, SYMBOL_TABLE_NEXT);
  }
  return json_is_obj(symbols) ? json_obj_get(symbols, name) : json_null();
}
struct json *ir_table_lookup(struct json *table, struct json *identifier) {
  struct json *symbols = json_obj_get(table, SYMBOL_TABLE_SYMBOLS);
  const char *name = json_get_str(identifier);
  struct json *found = ir_table_symbols_find(symbols, name);
  if (ir_value_is_global(found)) {
    ir_table_insert_global(table, found);
  }
  return found;
}
struct json *ir_table_make_global(struct json *table, struct json *identifier) {
  struct json *global = ir_value_new_global(identifier);
  assert(!json_has(table, SYMBOL_TABLE_NEXT));
  ir_table_insert(table, identifier, global);
  json_del(global);
  return global;
}
void ir_table_insert_global(struct json *table, struct json *value) {
  struct json *global = json_obj_get(table, SYMBOL_TABLE_GLOBAL);
  const char *key = ir_value_get_name(value);
  assert(ir_value_is_global(value));
  if (json_has(global, key)) {
    assert(json_obj_get(global, key) == value);
  } else {
    json_obj_insert(global, key, value);
  }
}
static void ir_table_finish_map(struct json_map *map) {
  struct json *table = json_map_extra(map);
  struct json *val = json_map_val(map);
  ir_table_insert_global(table, val);
}
void ir_table_finish(struct json *table) {
  struct json *symbols = json_obj_get(table, SYMBOL_TABLE_SYMBOLS);
  assert(!json_has(symbols, SYMBOL_TABLE_NEXT));
  json_foreach(symbols, ir_table_finish_map, table);
}
void ir_table_foreach_global(struct json *table, json_map_t map, void *extra) {
  struct json *global = json_obj_get(table, SYMBOL_TABLE_GLOBAL);
  json_foreach(global, map, extra);
}
