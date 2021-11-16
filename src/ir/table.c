#include "table.h"

#include "json/json.h"
#include "json/map.h"
#include "util/util.h"
#include "value.h"

struct json *ir_table_last(struct json *table) {
  while (json_has(table, "$next")) {
    table = json_get(table, "$next");
  }
  return table;
}

struct json *ir_table_new(void) {
  struct json *table = json_new_obj();
  json_obj_set(table, "$global", json_new_obj());
  return table;
}
struct json *ir_table_push(struct json *next) {
  struct json *table = json_new_obj();
  json_obj_insert(table, "$next", next);
  return table;
}
struct json *ir_table_pop(struct json *table) {
  struct json *next = json_get(table, "$next");
  json_ref(next);
  return next;
}
void ir_table_insert(struct json *table, const char *name, struct json *value) {
  assert(!json_has(table, name));
  json_obj_insert(table, name, value);
}
struct json *ir_table_lookup(struct json *table, const char *name) {
  while (!json_is_null(table)) {
    if (json_has(table, name)) {
      return json_get(table, name);
    }
    table = json_get(table, "$next");
  }
  return json_null();
}
struct json *ir_table_get_global(struct json *table) {
  struct json *last = ir_table_last(table);
  return json_get(last, "$global");
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
  assert(!json_has(table, "$next"));
  assert(json_has(table, "$global"));
  json_foreach(table, ir_table_finish_map, json_get(table, "$global"));
}
