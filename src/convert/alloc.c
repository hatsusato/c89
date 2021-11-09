#include "alloc.h"

#include "json/json.h"
#include "type.h"

static struct json *convert_new_alloca(void) {
  struct json *json = json_new_obj();
  json_insert_str(json, "instr", "alloca");
  return json;
}

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
struct json *convert_alloc_push(struct convert *self) {
  struct json *module = convert_get_module(self);
  struct json *alloc = json_get(module, "alloc");
  struct json *instr = convert_new_alloca();
  json_push(alloc, instr);
  return instr;
}
