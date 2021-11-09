#include "global.h"

#include "json/json.h"

void convert_global_init(struct json *module) {
  struct json *global = json_new_arr();
  json_insert(module, "global", global);
  json_del(global);
}
struct json *convert_global_new_value(struct json *identifier) {
  struct json *value = json_new_obj();
  json_insert(value, "name", identifier);
  json_insert(value, "global", json_null());
  return value;
}
