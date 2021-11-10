#include "global.h"

#include "json/json.h"

void ir_global_init(struct json *module) {
  struct json *global = json_new_obj();
  json_insert(module, "global", global);
  json_del(global);
}
void ir_global_finish(struct json *module) {
  struct json *global = json_get(module, "global");
  struct json *table = json_get(module, "table");
  json_merge(global, table);
}
struct json *ir_global_value_new(struct json *identifier) {
  struct json *value = json_new_obj();
  json_insert(value, "name", identifier);
  json_insert(value, "global", json_null());
  return value;
}
