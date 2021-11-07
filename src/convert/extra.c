#include "extra.h"

#include "json/json.h"

static struct json *convert_extra_new_function(void) {
  struct json *function = json_new_obj();
  struct json *blocks = json_new_arr();
  json_insert(function, "function", blocks);
  json_del(blocks);
  return function;
}

struct json *convert_extra_new_module(void) {
  struct json *module = json_new_obj();
  struct json *functions = json_new_arr();
  json_insert(module, "module", functions);
  json_del(functions);
  return module;
}
void convert_extra_init(struct convert_extra *self, struct json *module) {
  struct json *function = convert_extra_new_function();
  self->module = module;
  self->function = function;
  json_push(json_get(module, "module"), function);
  json_del(function);
}
