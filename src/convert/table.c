#include "table.h"

#include "json/json.h"
#include "type.h"
#include "util/util.h"

struct json *convert_table_insert(struct convert *self,
                                  struct json *identifier) {
  struct json *module = convert_get_module(self);
  struct json *table = json_get(module, "table");
  const char *key = json_get_str(identifier);
  if (json_has(table, key)) {
    assert(false);
    return json_null();
  } else {
    struct json *instr = convert_new_instr("alloca");
    json_insert(table, key, instr);
    json_del(instr);
    return instr;
  }
}
struct json *convert_table_lookup(struct convert *self,
                                  struct json *identifier) {
  struct json *module = convert_get_module(self);
  struct json *table = json_get(module, "table");
  const char *key = json_get_str(identifier);
  while (!json_is_null(table)) {
    if (json_has(table, key)) {
      return json_get(table, key);
    }
    table = json_get(table, "$next");
  }
  return json_null();
}
