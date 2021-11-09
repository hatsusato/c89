#include "table.h"

#include "alloc.h"
#include "json/json.h"
#include "util/util.h"

struct json *convert_table_insert(struct json *module,
                                  struct json *identifier) {
  struct json *table = json_get(module, "table");
  const char *key = json_get_str(identifier);
  if (json_has(table, key)) {
    assert(false);
    return json_null();
  } else {
    struct json *instr = convert_alloc_push(module);
    json_insert(table, key, instr);
    json_del(instr);
    return instr;
  }
}
struct json *convert_table_lookup(struct json *module,
                                  struct json *identifier) {
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
void convert_table_push(struct json *module) {
  struct json *table = json_new_obj();
  struct json *next = json_take(module, "table");
  json_insert(module, "table", table);
  json_del(table);
  json_insert(table, "$next", next);
  json_del(next);
}
void convert_table_pop(struct json *module) {
  struct json *table = json_get(module, "table");
  struct json *next = json_take(table, "$next");
  json_insert(module, "table", next);
  json_del(next);
}
