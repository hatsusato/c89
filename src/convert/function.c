#include "function.h"

#include "json/json.h"
#include "type.h"

static struct json *convert_function_new(void) {
  struct json *json = json_new_obj();
  struct json *function = json_new_arr();
  json_insert(json, "function", function);
  json_del(function);
  return json;
}
static void convert_alloc_init(struct convert *self) {
  struct json *module = convert_get_module(self);
  struct json *alloc = json_new_arr();
  json_insert(module, "alloc", alloc);
  json_del(alloc);
}

void convert_function_push(struct convert *self) {
  struct json *module = convert_get_module(self);
  struct json *array = json_get(module, "module");
  struct json *function = convert_function_new();
  json_push(array, function);
  json_del(function);
  json_insert(module, "function", function);
  convert_alloc_init(self);
}
struct json *convert_function_get(struct convert *self) {
  struct json *module = convert_get_module(self);
  return json_get(module, "function");
}
