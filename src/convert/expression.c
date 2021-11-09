#include "expression.h"

#include "immediate.h"
#include "json/json.h"
#include "module.h"
#include "table.h"
#include "util/symbol.h"
#include "util/util.h"

static struct json *convert_identifier(struct json *module, struct json *json) {
  struct json *pointer = convert_table_lookup(module, json);
  struct json *instr = convert_push_instr(module, "load");
  json_insert(instr, "pointer", pointer);
  return instr;
}
static struct json *convert_primary_expression(struct json *module,
                                               struct json *json) {
  convert_immediate_primary_expression(json);
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return convert_identifier(module, json_get(json, SYMBOL_IDENTIFIER));
  } else {
    return json;
  }
}
static struct json *convert_additive_expression(struct json *module,
                                                struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_ADDITIVE_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_MULTIPLICATIVE_EXPRESSION);
  struct json *op1 = convert_rvalue(module, lhs);
  struct json *op2 = convert_rvalue(module, rhs);
  if (convert_immediate_additive_expression(json, op1, op2)) {
    return json;
  } else {
    struct json *instr = convert_push_instr(module, "add");
    json_insert(instr, "lhs", op1);
    json_insert(instr, "rhs", op2);
    return instr;
  }
}
static struct json *convert_assignment_expression(struct json *module,
                                                  struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_UNARY_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION);
  struct json *value = convert_rvalue(module, rhs);
  struct json *pointer = convert_lvalue(module, lhs);
  struct json *instr = convert_push_instr(module, "store");
  json_insert(instr, "value", value);
  json_insert(instr, "pointer", pointer);
  return instr;
}

struct json *convert_lvalue(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return convert_table_lookup(module, json_get(json, SYMBOL_IDENTIFIER));
  } else {
    return json;
  }
}
struct json *convert_rvalue(struct json *module, struct json *json) {
  const char *tag = json_get_str(json_get(json, "tag"));
  if (!tag) {
    assert(false);
    return json;
  } else if (util_streq(tag, SYMBOL_PRIMARY_EXPRESSION)) {
    return convert_primary_expression(module, json);
  } else if (util_streq(tag, SYMBOL_ADDITIVE_EXPRESSION)) {
    return convert_additive_expression(module, json);
  } else if (util_streq(tag, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return convert_assignment_expression(module, json);
  } else {
    return json;
  }
}
