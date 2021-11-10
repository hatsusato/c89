#include "expression.h"

#include "immediate.h"
#include "ir/function.h"
#include "json/json.h"
#include "util/symbol.h"
#include "util/util.h"

static struct json *builder_identifier(struct json *function,
                                       struct json *json) {
  const char *name = json_get_str(json);
  struct json *pointer = ir_function_lookup_symbol(function, name);
  struct json *instr = ir_function_new_instr(function, "load");
  json_insert(instr, "pointer", pointer);
  json_del(instr);
  return instr;
}
static struct json *builder_primary_expression(struct json *function,
                                               struct json *json) {
  builder_immediate_primary_expression(json);
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return builder_identifier(function, json_get(json, SYMBOL_IDENTIFIER));
  } else {
    return json;
  }
}
static struct json *builder_additive_expression(struct json *function,
                                                struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_ADDITIVE_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_MULTIPLICATIVE_EXPRESSION);
  struct json *op1 = builder_rvalue(function, lhs);
  struct json *op2 = builder_rvalue(function, rhs);
  if (builder_immediate_additive_expression(json, op1, op2)) {
    return json;
  } else {
    struct json *instr = ir_function_new_instr(function, "add");
    json_insert(instr, "lhs", op1);
    json_insert(instr, "rhs", op2);
    json_del(instr);
    return instr;
  }
}
static struct json *builder_assignment_expression(struct json *function,
                                                  struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_UNARY_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION);
  struct json *value = builder_rvalue(function, rhs);
  struct json *pointer = builder_lvalue(function, lhs);
  struct json *instr = ir_function_new_instr(function, "store");
  json_insert(instr, "value", value);
  json_insert(instr, "pointer", pointer);
  json_del(instr);
  return instr;
}
static struct json *builder_initializer(struct json *function,
                                        struct json *json) {
  if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return builder_rvalue(function,
                          json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
}

struct json *builder_lvalue(struct json *function, struct json *json) {
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    struct json *identifier = json_get(json, SYMBOL_IDENTIFIER);
    const char *name = json_get_str(identifier);
    return ir_function_lookup_symbol(function, name);
  } else {
    return json;
  }
}
struct json *builder_rvalue(struct json *function, struct json *json) {
  const char *tag = json_get_str(json_get(json, "tag"));
  if (util_streq(tag, SYMBOL_PRIMARY_EXPRESSION)) {
    return builder_primary_expression(function, json);
  } else if (util_streq(tag, SYMBOL_ADDITIVE_EXPRESSION)) {
    return builder_additive_expression(function, json);
  } else if (util_streq(tag, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return builder_assignment_expression(function, json);
  } else if (json_has(json, SYMBOL_INITIALIZER)) {
    return builder_initializer(function, json_get(json, SYMBOL_INITIALIZER));
  } else {
    return json;
  }
}
