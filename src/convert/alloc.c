#include "alloc.h"

#include "json/json.h"
#include "module.h"

void convert_alloc_init(struct json *module) {
  struct json *function = json_get(module, "function");
  struct json *alloc = json_new_arr();
  json_insert(function, "alloc", alloc);
  json_del(alloc);
}
struct json *convert_alloc_finish(struct json *module) {
  struct json *function = json_get(module, "function");
  struct json *alloc = json_take(function, "alloc");
  json_insert(function, "alloc", json_null());
  return alloc;
}
struct json *convert_alloc_push(struct json *module) {
  struct json *function = json_get(module, "function");
  struct json *alloc = json_get(function, "alloc");
  struct json *instr = convert_new_instr("alloca");
  json_push(alloc, instr);
  return instr;
}
