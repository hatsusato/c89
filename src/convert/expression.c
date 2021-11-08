#include "expression.h"

#include "immediate.h"
#include "json/json.h"
#include "type.h"
#include "util/symbol.h"
#include "util/util.h"

static struct json *convert_identifier(struct convert *self,
                                       struct json *json) {
  struct json *pointer = convert_lookup_symbol(self, json);
  struct json *instr = convert_push_instr(self, "load");
  json_insert(instr, "pointer", pointer);
  return instr;
}
static struct json *convert_integer_constant(struct convert *self,
                                             struct json *json) {
  UTIL_UNUSED(self);
  return json;
}
static struct json *convert_additive_expression(struct convert *self,
                                                struct json *json) {
  struct json *lhs = convert_rvalue(self, json_get(json, "lhs"));
  struct json *rhs = convert_rvalue(self, json_get(json, "rhs"));
  struct json *instr = convert_push_instr(self, "add");
  json_insert(instr, "lhs", lhs);
  json_insert(instr, "rhs", rhs);
  return instr;
}
static struct json *convert_assignment_expression(struct convert *self,
                                                  struct json *json) {
  struct json *value = convert_rvalue(self, json_get(json, "rhs"));
  struct json *pointer = convert_lvalue(self, json_get(json, "lhs"));
  struct json *instr = convert_push_instr(self, "store");
  json_insert(instr, "value", value);
  json_insert(instr, "pointer", pointer);
  return instr;
}

struct json *convert_lvalue(struct convert *self, struct json *json) {
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return convert_lookup_symbol(self, json_get(json, SYMBOL_IDENTIFIER));
  } else {
    return json;
  }
}
struct json *convert_rvalue(struct convert *self, struct json *json) {
  convert_immediate(json);
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return convert_identifier(self, json_get(json, SYMBOL_IDENTIFIER));
  } else if (json_has(json, SYMBOL_INTEGER_CONSTANT)) {
    return convert_integer_constant(self,
                                    json_get(json, SYMBOL_INTEGER_CONSTANT));
  } else if (json_has(json, SYMBOL_ADDITIVE_EXPRESSION)) {
    return convert_additive_expression(
        self, json_get(json, SYMBOL_ADDITIVE_EXPRESSION));
  } else if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return convert_assignment_expression(
        self, json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
}
