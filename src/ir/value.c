#include "value.h"

#include "json/json.h"

struct json *ir_value_new_global(struct json *identifier) {
  struct json *value = json_new_obj();
  json_insert(value, "name", identifier);
  json_insert(value, "global", json_null());
  return value;
}
