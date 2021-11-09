#include "global.h"

#include "json/json.h"

void convert_global_init(struct json *module) {
  struct json *global = json_new_arr();
  json_insert(module, "global", global);
  json_del(global);
}
