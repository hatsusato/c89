#include "ir/lexical.h"

#include "ir/constant.h"
#include "ir/stack_impl.h"

const char *stack_identifier_symbol(Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  return sexp_get_symbol(ast);
}
Value *stack_identifier(Builder *stack, Sexp *ast) {
  const char *symbol = stack_identifier_symbol(ast);
  Value *expr = stack_find_alloca(stack, symbol);
  Instruction *instr = stack_instruction_load(stack, expr);
  return instruction_as_value(instr);
}
Value *stack_integer_constant(Builder *stack, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  return constant_as_value(stack_new_integer(stack, sexp_get_symbol(ast)));
}
