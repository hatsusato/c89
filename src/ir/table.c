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
void ir_table_insert(struct json *table, const char *name, struct json *value) {
  struct json *symbols = json_obj_get(table, SYMBOL_TABLE_SYMBOLS);
  assert(!json_has(symbols, name));
  assert(!util_streq(SYMBOL_TABLE_NEXT, name));
  json_obj_insert(symbols, name, value);
}
struct json *ir_table_lookup(struct json *table, const char *name) {
  struct json *symbols = json_obj_get(table, SYMBOL_TABLE_SYMBOLS);
  while (!json_is_null(symbols)) {
    if (json_has(symbols, name)) {
      return json_obj_get(symbols, name);
    }
    symbols = json_obj_get(symbols, SYMBOL_TABLE_NEXT);
  }
  return json_null();
}
void ir_table_insert_global(struct json *table, const char *key,
                            struct json *value) {
  struct json *global = json_obj_get(table, SYMBOL_TABLE_GLOBAL);
  assert(ir_value_is_global(value));
  if (json_has(global, key)) {
    assert(json_obj_get(global, key) == value);
  } else {
    json_obj_insert(global, key, value);
  }
}
static void ir_table_finish_map(struct json_map *map) {
  struct json *table = json_map_extra(map);
  const char *key = json_map_key(map);
  struct json *val = json_map_val(map);
  ir_table_insert_global(table, key, val);
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
