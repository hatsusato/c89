#include "ir/expression.h"

#include "ir/stack_impl.h"

void stack_additive_expression(Stack *stack, Sexp *ast) {
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 2)));
  assert(AST_PLUS == sexp_get_number(sexp_at(ast, 2)));
  stack_ast(stack, sexp_at(ast, 1));
  stack_ast(stack, sexp_at(ast, 3));
  stack_instruction_add(stack);
}
void stack_assignment_expression(Stack *stack, Sexp *ast) {
  Sexp *lhs, *op, *rhs;
  assert(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  lhs = sexp_at(ast, 1);
  op = sexp_at(ast, 2);
  rhs = sexp_at(ast, 3);
  assert(AST_IDENTIFIER == sexp_get_tag(lhs));
  assert(sexp_is_number(op) && AST_ASSIGN == sexp_get_number(op));
  lhs = sexp_at(lhs, 1);
  assert(sexp_is_symbol(lhs));
  stack_ast(stack, rhs);
  stack_store_to_symbol(stack, sexp_get_symbol(lhs));
}
void stack_constant_expression(Stack *stack, Sexp *ast) {
  assert(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
}
