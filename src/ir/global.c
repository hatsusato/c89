#include "global.h"

#include "json/json.h"

void ir_global_init(struct json *module) {
  struct json *global = json_new_obj();
  json_insert(module, "global", global);
  json_del(global);
}
void ir_global_finish(struct json *module) {
  struct json *global = json_get(module, "global");
  struct json *table = json_get(module, "table");
  json_merge(global, table);
}
