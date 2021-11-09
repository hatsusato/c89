#include "global.h"

#include "json/json.h"

void convert_global_init(struct json *module) {
  struct json *global = json_new_obj();
  json_insert(module, "global", global);
  json_del(global);
}
void convert_global_finish(struct json *module) {
  struct json *global = json_get(module, "global");
  struct json *table = json_get(module, "table");
  json_merge(global, table);
}
struct json *convert_global_new_value(struct json *identifier) {
  struct json *value = json_new_obj();
  json_insert(value, "name", identifier);
  json_insert(value, "global", json_null());
  return value;
}
void convert_global_push(struct json *module, struct json *value) {
  if (json_has(value, "global")) {
    struct json *global = json_get(module, "global");
    const char *name = json_get_str(json_get(value, "name"));
    json_insert(global, name, value);
  }
}
