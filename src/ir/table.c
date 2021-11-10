#include "table.h"

#include "json/json.h"
#include "module.h"
#include "util/util.h"

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
void ir_table_insert(struct json *module, const char *name,
                     struct json *value) {
  struct json *table = json_get(module, "table");
  assert(!json_has(table, name));
  json_insert(table, name, value);
}
struct json *ir_table_lookup(struct json *module, const char *name) {
  struct json *table = json_get(module, "table");
  while (!json_is_null(table)) {
    if (json_has(table, name)) {
      struct json *value = json_get(table, name);
      ir_module_push_global(module, value);
      return value;
    }
    table = json_get(table, "$next");
  }
  return json_null();
}
bool_t ir_table_is_global(struct json *module) {
  struct json *table = json_get(module, "table");
  return !json_has(table, "$next");
}
