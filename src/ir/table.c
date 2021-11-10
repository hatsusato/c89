#include "table.h"

#include "json/json.h"

void ir_table_init(struct json *module) {
  struct json *table = json_new_obj();
  json_insert(module, "table", table);
  json_del(table);
}
void ir_table_push(struct json *module) {
  struct json *table = json_new_obj();
  struct json *next = json_get(module, "table");
  json_insert(table, "$next", next);
  json_insert(module, "table", table);
  json_del(table);
}
void ir_table_pop(struct json *module) {
  struct json *table = json_take(module, "table");
  struct json *next = json_get(table, "$next");
  json_insert(module, "table", next);
  json_del(table);
}
