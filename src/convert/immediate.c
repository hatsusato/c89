#include "immediate.h"

#include "json/json.h"
#include "json/visitor.h"
#include "util/symbol.h"
#include "util/util.h"

static void convert_immediate_insert(struct json *json, int val) {
  json_set(json, "immediate", json_new_int(val));
}
static void convert_immediate_expression(struct json *);

static void convert_immediate_primary_expression(struct json *json) {
  if (json_has(json, SYMBOL_INTEGER_CONSTANT)) {
    struct json *val = json_get(json, SYMBOL_INTEGER_CONSTANT);
    int num = util_atoi(json_get_str(val));
    convert_immediate_insert(json, num);
  }
}
static void convert_immediate_additive_expression(struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_ADDITIVE_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_MULTIPLICATIVE_EXPRESSION);
  convert_immediate_expression(lhs);
  convert_immediate_expression(rhs);
  lhs = json_get(lhs, "immediate");
  rhs = json_get(rhs, "immediate");
  if (json_is_int(lhs) && json_is_int(rhs)) {
    int lval = json_int_get(json_as_int(lhs));
    int rval = json_int_get(json_as_int(rhs));
    if (json_has(json, SYMBOL_PLUS)) {
      convert_immediate_insert(json, lval + rval);
    } else if (json_has(json, SYMBOL_MINUS)) {
      convert_immediate_insert(json, lval - rval);
    }
  }
}
static void convert_immediate_expression(struct json *json) {
  const char *tag = json_get_str(json_get(json, "tag"));
  if (util_streq(tag, SYMBOL_PRIMARY_EXPRESSION)) {
    convert_immediate_primary_expression(json);
  } else if (util_streq(tag, SYMBOL_ADDITIVE_EXPRESSION)) {
    convert_immediate_additive_expression(json);
  }
}
static void convert_immediate_visitor(struct json_visitor *visitor,
                                      struct json *json) {
  if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    convert_immediate_expression(json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else if (json_has(json, SYMBOL_CONSTANT_EXPRESSION)) {
    convert_immediate_expression(json_get(json, SYMBOL_CONSTANT_EXPRESSION));
  } else if (json_has(json, SYMBOL_EXPRESSION)) {
    convert_immediate_expression(json_get(json, SYMBOL_EXPRESSION));
  } else {
    json_visit_foreach(visitor, json);
  }
}

void convert_immediate(struct json *json) {
  json_visit(convert_immediate_visitor, NULL, json);
}
