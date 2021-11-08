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
static struct json *convert_primary_expression(struct convert *self,
                                               struct json *json) {
  convert_immediate_primary_expression(json);
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return convert_identifier(self, json_get(json, SYMBOL_IDENTIFIER));
  } else {
    return json;
  }
}
static struct json *convert_additive_expression(struct convert *self,
                                                struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_ADDITIVE_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_MULTIPLICATIVE_EXPRESSION);
  struct json *op1 = convert_rvalue(self, lhs);
  struct json *op2 = convert_rvalue(self, rhs);
  if (convert_immediate_additive_expression(json, op1, op2)) {
    return json;
  } else {
    struct json *instr = convert_push_instr(self, "add");
    json_insert(instr, "lhs", op1);
    json_insert(instr, "rhs", op2);
    return instr;
  }
}
static struct json *convert_assignment_expression(struct convert *self,
                                                  struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_UNARY_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION);
  struct json *value = convert_rvalue(self, rhs);
  struct json *pointer = convert_lvalue(self, lhs);
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
  const char *tag = json_get_str(json_get(json, "tag"));
  if (!tag) {
    return json;
  } else if (util_streq(tag, SYMBOL_PRIMARY_EXPRESSION)) {
    return convert_primary_expression(self, json);
  } else if (util_streq(tag, SYMBOL_ADDITIVE_EXPRESSION)) {
    return convert_additive_expression(self, json);
  } else if (util_streq(tag, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return convert_assignment_expression(self, json);
  } else {
    return json;
  }
}
