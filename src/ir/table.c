#include "table.h"

#include "json/json.h"
#include "util/util.h"

struct json *ir_table_last(struct json *table) {
  while (json_has(table, "$next")) {
    table = json_get(table, "$next");
  }
  return table;
}

struct json *ir_table_new(void) {
  struct json *table = json_new_obj();
  json_set(table, "$global", json_new_obj());
  return table;
}
struct json *ir_table_push(struct json *next) {
  struct json *table = json_new_obj();
  json_insert(table, "$next", next);
  return table;
}
struct json *ir_table_pop(struct json *table) {
  struct json *next = json_get(table, "$next");
  json_ref(next);
  return next;
}
void ir_table_insert(struct json *table, const char *name, struct json *value) {
  assert(!json_has(table, name));
  json_insert(table, name, value);
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
