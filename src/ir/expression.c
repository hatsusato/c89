#include "ir/expression.h"

#include "ir/stack_impl.h"

Value *stack_additive_expression(Stack *stack, Sexp *ast) {
  Value *lhs, *rhs, *expr;
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
  lhs = stack_get_prev(stack);
  stack_ast(stack, sexp_at(ast, 3));
  rhs = stack_get_prev(stack);
  switch (sexp_get_tag(sexp_at(ast, 2))) {
  case AST_PLUS:
    expr = stack_instruction_add(stack, lhs, rhs);
    stack_set_prev(stack, expr);
    return expr;
  case AST_MINUS:
    expr = stack_instruction_sub(stack, lhs, rhs);
    stack_set_prev(stack, expr);
    return expr;
  default:
    assert(0);
    return NULL;
  }
}
Value *stack_assignment_expression(Stack *stack, Sexp *ast) {
  const char *symbol;
  Value *lhs, *rhs;
  assert(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  assert(AST_ASSIGN == sexp_get_tag(sexp_at(ast, 2)));
  symbol = stack_identifier_symbol(sexp_at(ast, 1));
  lhs = stack_find_alloca(stack, symbol);
  stack_ast(stack, sexp_at(ast, 3));
  rhs = stack_get_prev(stack);
  return stack_instruction_store(stack, rhs, lhs);
}
Value *stack_constant_expression(Stack *stack, Sexp *ast) {
  assert(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  return stack_ast(stack, sexp_at(ast, 1));
}
