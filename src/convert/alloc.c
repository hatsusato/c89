#include "alloc.h"

#include "json/json.h"
#include "type.h"

void convert_alloc_init(struct convert *self) {
  struct json *module = convert_get_module(self);
  struct json *alloc = json_new_arr();
  json_insert(module, "alloc", alloc);
  json_del(alloc);
}
struct json *convert_alloc_finish(struct convert *self) {
  struct json *module = convert_get_module(self);
  struct json *alloc = json_take(module, "alloc");
  json_insert(module, "alloc", json_null());
  return alloc;
}
