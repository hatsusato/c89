#include "table.h"

#include "json/json.h"

static struct json *ir_table_get(struct json *module) {
  return json_get(module, "table");
}
static void ir_table_set(struct json *module, struct json *table) {
  json_insert(module, "table", table);
}

void ir_table_init(struct json *module) {
  struct json *table = json_new_obj();
  json_insert(module, "table", table);
  json_del(table);
}
void ir_table_push(struct json *module) {
  struct json *table = json_new_obj();
  struct json *next = ir_table_get(module);
  json_insert(table, "$next", next);
  ir_table_set(module, table);
  json_del(table);
}
