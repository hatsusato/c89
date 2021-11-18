#include "table.h"

#include "json/json.h"
#include "json/map.h"
#include "util/util.h"
#include "value.h"

struct json *ir_table_last(struct json *table) {
  struct json *symbols = json_obj_get(table, "symbols");
  while (json_has(symbols, "$next")) {
    symbols = json_obj_get(symbols, "$next");
  }
  return symbols;
}

struct json *ir_table_new(void) {
  struct json *table = json_new_obj();
  struct json *symbols = json_new_obj();
  json_obj_set(symbols, "$global", json_new_obj());
  json_obj_set(table, "symbols", symbols);
  return table;
}
void ir_table_push(struct json *table) {
  struct json *symbols = json_new_obj();
  struct json *next = json_obj_get(table, "symbols");
  json_obj_insert(symbols, "$next", next);
  json_obj_set(table, "symbols", symbols);
}
void ir_table_pop(struct json *table) {
  struct json *symbols = json_obj_get(table, "symbols");
  struct json *next = json_obj_get(symbols, "$next");
  json_ref(next);
  json_obj_set(table, "symbols", next);
}
void ir_table_insert(struct json *table, const char *name, struct json *value) {
  struct json *symbols = json_obj_get(table, "symbols");
  assert(!json_has(symbols, name));
  json_obj_insert(symbols, name, value);
}
struct json *ir_table_lookup(struct json *table, const char *name) {
  struct json *symbols = json_obj_get(table, "symbols");
  while (!json_is_null(symbols)) {
    if (json_has(symbols, name)) {
      return json_obj_get(symbols, name);
    }
    symbols = json_obj_get(symbols, "$next");
  }
  return json_null();
}
struct json *ir_table_get_global(struct json *table) {
  struct json *last = ir_table_last(table);
  return json_obj_get(last, "$global");
}
void ir_table_insert_global(struct json *table, struct json *value) {
  if (ir_value_is_global(value)) {
    struct json *global = ir_table_get_global(table);
    const char *name = ir_value_get_name(value);
    json_obj_insert(global, name, value);
  }
}
static void ir_table_finish_map(struct json_map *map) {
  struct json *global = json_map_extra(map);
  const char *key = json_map_key(map);
  struct json *val = json_map_val(map);
  if (!util_streq(key, "$global") && !json_has(global, key)) {
    json_obj_insert(global, key, val);
  }
}
void ir_table_finish(struct json *table) {
  struct json *symbols = json_obj_get(table, "symbols");
  assert(!json_has(symbols, "$next"));
  assert(json_has(symbols, "$global"));
  json_foreach(symbols, ir_table_finish_map, json_obj_get(symbols, "$global"));
}
