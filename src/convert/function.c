#include "function.h"

#include "json/json.h"
#include "type.h"

static void convert_alloc_init(struct convert *self) {
  struct json *module = convert_get_module(self);
  struct json *alloc = json_new_arr();
  json_insert(module, "alloc", alloc);
  json_del(alloc);
}
static struct json *convert_alloc_finish(struct convert *self) {
  struct json *module = convert_get_module(self);
  struct json *alloc = json_take(module, "alloc");
  json_insert(module, "alloc", json_null());
  return alloc;
}
static struct json *convert_function_new(void) {
  struct json *json = json_new_obj();
  struct json *function = json_new_arr();
  json_insert(json, "function", function);
  json_del(function);
  return json;
}

void convert_function_init(struct convert *self) {
  struct json *module = convert_get_module(self);
  struct json *array = json_get(module, "module");
  struct json *function = convert_function_new();
  json_push(array, function);
  json_del(function);
  json_insert(module, "function", function);
  convert_alloc_init(self);
}
void convert_function_finish(struct convert *self) {
  struct json *function = convert_function_get(self);
  struct json *array = json_get(function, "function");
  struct json *front = json_front(array);
  struct json *alloc = convert_alloc_finish(self);
  json_append(alloc, json_get(front, "block"));
  json_insert(front, "block", alloc);
  json_del(alloc);
}
struct json *convert_function_get(struct convert *self) {
  struct json *module = convert_get_module(self);
  return json_get(module, "function");
}
void convert_function_set_name(struct convert *self, struct json *name) {
  struct json *function = convert_function_get(self);
  json_insert(function, "name", name);
}
