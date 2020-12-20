#include "ir/expression.h"

#include "ir/stack_impl.h"

Value *stack_additive_expression(Stack *stack, Sexp *ast) {
  Value *lhs, *rhs;
  Instruction *instr = NULL;
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  lhs = stack_ast(stack, sexp_at(ast, 1));
  rhs = stack_ast(stack, sexp_at(ast, 3));
  switch (sexp_get_tag(sexp_at(ast, 2))) {
  case AST_PLUS:
    instr = stack_instruction_add(stack, lhs, rhs);
    break;
  case AST_MINUS:
    instr = stack_instruction_sub(stack, lhs, rhs);
    break;
  default:
    assert(0);
    break;
  }
  return instruction_as_value(instr);
}
Value *stack_assignment_expression(Stack *stack, Sexp *ast) {
  const char *symbol;
  Value *lhs, *rhs;
  Instruction *instr;
  assert(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  assert(AST_ASSIGN == sexp_get_tag(sexp_at(ast, 2)));
  symbol = stack_identifier_symbol(sexp_at(ast, 1));
  lhs = stack_find_alloca(stack, symbol);
  rhs = stack_ast(stack, sexp_at(ast, 3));
  instr = stack_instruction_store(stack, rhs, lhs);
  return instruction_as_value(instr);
}
Value *stack_constant_expression(Stack *stack, Sexp *ast) {
  assert(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  return stack_ast(stack, sexp_at(ast, 1));
}
