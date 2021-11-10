#include "table.h"

#include "json/json.h"

void ir_table_init(struct json *module) {
  struct json *table = json_new_obj();
  json_insert(module, "table", table);
  json_del(table);
}
