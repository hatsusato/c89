#include "global.h"

#include "ir/global.h"
#include "json/json.h"
#include "table.h"

void convert_global_init(struct json *module) {
  ir_global_init(module);
  convert_table_push(module);
}
void convert_global_finish(struct json *module) {
  ir_global_finish(module);
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
