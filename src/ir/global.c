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
struct json *ir_global_get(struct json *module) {
  return json_get(module, "global");
}
const char *ir_global_value_name(struct json *value) {
  struct json *name = json_get(value, "name");
  return json_get_str(name);
}
