#include "expression.h"

#include "ir/function.h"
#include "ir/instr.h"
#include "ir/table.h"
#include "json/json.h"
#include "util/symbol.h"
#include "util/util.h"

static struct json *builder_identifier(struct json *function,
                                       struct json *json) {
  struct json *table = ir_function_get_table(function);
  struct json *pointer = ir_table_lookup(table, json);
  struct json *instr = ir_function_make_instr(function, "load");
  ir_instr_insert(instr, "pointer", pointer);
  return instr;
}
static struct json *builder_primary_expression(struct json *function,
                                               struct json *json) {
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return builder_identifier(function, json_obj_get(json, SYMBOL_IDENTIFIER));
  } else {
    return json;
  }
}
static struct json *builder_additive_expression(struct json *function,
                                                struct json *json) {
  struct json *lhs = json_obj_get(json, SYMBOL_ADDITIVE_EXPRESSION);
  struct json *rhs = json_obj_get(json, SYMBOL_MULTIPLICATIVE_EXPRESSION);
  struct json *op1 = builder_rvalue(function, lhs);
  struct json *op2 = builder_rvalue(function, rhs);
  struct json *instr = ir_function_make_instr(function, "add");
  ir_instr_insert(instr, "lhs", op1);
  ir_instr_insert(instr, "rhs", op2);
  return instr;
}
static struct json *builder_assignment_expression(struct json *function,
                                                  struct json *json) {
  struct json *lhs = json_obj_get(json, SYMBOL_UNARY_EXPRESSION);
  struct json *rhs = json_obj_get(json, SYMBOL_ASSIGNMENT_EXPRESSION);
  struct json *value = builder_rvalue(function, rhs);
  struct json *pointer = builder_lvalue(function, lhs);
  struct json *instr = ir_function_make_instr(function, "store");
  ir_instr_insert(instr, "value", value);
  ir_instr_insert(instr, "pointer", pointer);
  return instr;
}
static struct json *builder_initializer(struct json *function,
                                        struct json *json) {
  if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return builder_rvalue(function,
                          json_obj_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
}
static struct json *builder_global_initializer(struct json *json) {
  if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return builder_global_rvalue(
        json_obj_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
}

struct json *builder_lvalue(struct json *function, struct json *json) {
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    struct json *table = ir_function_get_table(function);
    struct json *identifier = json_obj_get(json, SYMBOL_IDENTIFIER);
    return ir_table_lookup(table, identifier);
  } else {
    return json;
  }
}
struct json *builder_rvalue(struct json *function, struct json *json) {
  const char *tag = json_get_str(json_obj_get(json, SYMBOL_EXPR_TAG));
  if (json_has(json, SYMBOL_IMMEDIATE)) {
    return json;
  } else if (util_streq(tag, SYMBOL_PRIMARY_EXPRESSION)) {
    return builder_primary_expression(function, json);
  } else if (util_streq(tag, SYMBOL_ADDITIVE_EXPRESSION)) {
    return builder_additive_expression(function, json);
  } else if (util_streq(tag, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return builder_assignment_expression(function, json);
  } else if (json_has(json, SYMBOL_INITIALIZER)) {
    return builder_initializer(function,
                               json_obj_get(json, SYMBOL_INITIALIZER));
  } else {
    return json;
  }
}
struct json *builder_global_rvalue(struct json *json) {
  const char *tag = json_get_str(json_obj_get(json, SYMBOL_EXPR_TAG));
  if (json_has(json, SYMBOL_IMMEDIATE)) {
    return json;
  } else if (util_streq(tag, SYMBOL_PRIMARY_EXPRESSION)) {
    return json;
  } else if (json_has(json, SYMBOL_INITIALIZER)) {
    return builder_global_initializer(json_obj_get(json, SYMBOL_INITIALIZER));
  } else {
    return json;
  }
}
