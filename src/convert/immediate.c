#include "immediate.h"

#include "json/json.h"
#include "util/symbol.h"
#include "util/util.h"

static void convert_insert_immediate(struct json *json, int val) {
  struct json *immediate = json_new_int(val);
  json_insert(json, SYMBOL_IMMEDIATE, immediate);
  json_del(immediate);
}

void convert_immediate(struct json *json) {
  if (json_has(json, SYMBOL_INTEGER_CONSTANT)) {
    struct json *val = json_get(json, SYMBOL_INTEGER_CONSTANT);
    convert_insert_immediate(json, util_atoi(json_get_str(val)));
  }
}
