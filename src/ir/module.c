#include "module.h"

#include "global.h"
#include "json/json.h"
#include "value.h"

struct json *ir_module_new(void) {
  struct json *module = json_new_obj();
  struct json *array = json_new_arr();
  json_insert(module, "module", array);
  json_del(array);
  return module;
}
void ir_module_push_global(struct json *module, struct json *value) {
  if (ir_value_is_global(value)) {
    struct json *global = ir_global_get(module);
    const char *name = ir_value_get_name(value);
    json_insert(global, name, value);
  }
}
