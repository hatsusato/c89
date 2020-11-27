#include "ir/value.h"

#include "ast/ast_tag.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

struct struct_Value {
  ValueKind kind;
  const void *value;
};

static Value *value_new(ValueKind kind, const void *value) {
  Value *v = UTILITY_MALLOC(Value);
  v->kind = kind;
  v->value = value;
  return v;
}

Value *value_register(Register *reg) {
  return value_new(VALUE_REGISTER, reg);
}
Value *value_instruction(Instruction *instr) {
  return value_new(VALUE_INSTRUCTION, instr);
}
Value *value_integer_constant(Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  return value_new(VALUE_INTEGER_CONSTANT, sexp_get_symbol(ast));
}
