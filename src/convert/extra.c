#include "extra.h"

#include "json/json.h"

struct json *convert_extra_new_module(void) {
  struct json *module = json_new_obj();
  struct json *functions = json_new_arr();
  json_insert(module, "module", functions);
  json_del(functions);
  return module;
}
void convert_extra_init(struct convert_extra *self, struct json *module) {
  self->module = module;
  self->function = json_new_obj();
}
