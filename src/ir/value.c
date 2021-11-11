#include "value.h"

#include "json/json.h"

struct json *ir_value_new_global(struct json *identifier) {
  struct json *value = json_new_obj();
  json_insert(value, "name", identifier);
  json_insert(value, "global", json_null());
  return value;
}
const char *ir_value_get_name(struct json *value) {
  struct json *name = json_get(value, "name");
  return json_get_str(name);
}
bool_t ir_value_is_global(struct json *value) {
  return json_has(value, "global");
}
