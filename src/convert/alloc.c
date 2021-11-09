#include "alloc.h"

#include "json/json.h"
#include "module.h"

void convert_alloc_init(struct json *module) {
  struct json *alloc = json_new_arr();
  json_insert(module, "alloc", alloc);
  json_del(alloc);
}
struct json *convert_alloc_finish(struct json *module) {
  struct json *alloc = json_take(module, "alloc");
  json_insert(module, "alloc", json_null());
  return alloc;
}
struct json *convert_alloc_push(struct json *module) {
  struct json *alloc = json_get(module, "alloc");
  struct json *instr = convert_new_instr("alloca");
  json_push(alloc, instr);
  return instr;
}
