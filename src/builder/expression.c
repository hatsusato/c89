#include "expression.h"

#include "immediate.h"
#include "ir/module.h"
#include "json/json.h"
#include "util/symbol.h"
#include "util/util.h"

static struct json *builder_identifier(struct json *module, struct json *json) {
  const char *name = json_get_str(json);
  struct json *pointer = ir_module_lookup_symbol(module, name);
  struct json *instr = ir_module_new_instr(module, "load");
  json_insert(instr, "pointer", pointer);
  json_del(instr);
  return instr;
}
static struct json *builder_primary_expression(struct json *module,
                                               struct json *json) {
  builder_immediate_primary_expression(json);
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return builder_identifier(module, json_get(json, SYMBOL_IDENTIFIER));
  } else {
    return json;
  }
}
static struct json *builder_additive_expression(struct json *module,
                                                struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_ADDITIVE_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_MULTIPLICATIVE_EXPRESSION);
  struct json *op1 = builder_rvalue(module, lhs);
  struct json *op2 = builder_rvalue(module, rhs);
  if (builder_immediate_additive_expression(json, op1, op2)) {
    return json;
  } else {
    struct json *instr = ir_module_new_instr(module, "add");
    json_insert(instr, "lhs", op1);
    json_insert(instr, "rhs", op2);
    json_del(instr);
    return instr;
  }
}
static struct json *builder_assignment_expression(struct json *module,
                                                  struct json *json) {
  struct json *lhs = json_get(json, SYMBOL_UNARY_EXPRESSION);
  struct json *rhs = json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION);
  struct json *value = builder_rvalue(module, rhs);
  struct json *pointer = builder_lvalue(module, lhs);
  struct json *instr = ir_module_new_instr(module, "store");
  json_insert(instr, "value", value);
  json_insert(instr, "pointer", pointer);
  json_del(instr);
  return instr;
}
static struct json *builder_initializer(struct json *module,
                                        struct json *json) {
  if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return builder_rvalue(module, json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
}

struct json *builder_lvalue(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    struct json *identifier = json_get(json, SYMBOL_IDENTIFIER);
    const char *name = json_get_str(identifier);
    return ir_module_lookup_symbol(module, name);
  } else {
    return json;
  }
}
struct json *builder_rvalue(struct json *module, struct json *json) {
  const char *tag = json_get_str(json_get(json, "tag"));
  if (util_streq(tag, SYMBOL_PRIMARY_EXPRESSION)) {
    return builder_primary_expression(module, json);
  } else if (util_streq(tag, SYMBOL_ADDITIVE_EXPRESSION)) {
    return builder_additive_expression(module, json);
  } else if (util_streq(tag, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return builder_assignment_expression(module, json);
  } else if (json_has(json, SYMBOL_INITIALIZER)) {
    return builder_initializer(module, json_get(json, SYMBOL_INITIALIZER));
  } else {
    return json;
  }
}
