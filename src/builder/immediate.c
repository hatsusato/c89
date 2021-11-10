#include "immediate.h"

#include "json/json.h"
#include "util/symbol.h"
#include "util/util.h"

#define SYMBOL_IMMEDIATE "immediate"

static void convert_insert_immediate(struct json *json, int val) {
  struct json *immediate = json_new_int(val);
  json_insert(json, SYMBOL_IMMEDIATE, immediate);
  json_del(immediate);
}

void convert_immediate_primary_expression(struct json *json) {
  if (json_has(json, SYMBOL_INTEGER_CONSTANT)) {
    struct json *val = json_get(json, SYMBOL_INTEGER_CONSTANT);
    convert_insert_immediate(json, util_atoi(json_get_str(val)));
  }
}
bool_t convert_immediate_additive_expression(struct json *json,
                                             struct json *lhs,
                                             struct json *rhs) {
  lhs = json_get(lhs, SYMBOL_IMMEDIATE);
  rhs = json_get(rhs, SYMBOL_IMMEDIATE);
  if (json_is_null(lhs) || json_is_null(rhs)) {
    return false;
  } else {
    int lval, rval;
    assert(json_is_int(lhs) && json_is_int(rhs));
    lval = json_int_get(json_as_int(lhs));
    rval = json_int_get(json_as_int(rhs));
    convert_insert_immediate(json, lval + rval);
    return true;
  }
}
