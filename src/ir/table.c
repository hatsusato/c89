#include "table.h"

#include "json/json.h"

static struct json *ir_table_take(struct json *module) {
  return json_take(module, "table");
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
  struct json *next = ir_table_take(module);
  json_insert(table, "$next", next);
  ir_table_set(module, table);
  json_del(table);
  json_del(next);
}
void ir_table_pop(struct json *module) {
  struct json *table = ir_table_take(module);
  struct json *next = json_get(table, "$next");
  ir_table_set(module, next);
  json_del(table);
}
