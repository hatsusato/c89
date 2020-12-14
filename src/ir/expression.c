#include "ir/expression.h"

#include "ir/stack_impl.h"

void stack_additive_expression(Stack *stack, Sexp *ast) {
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
  stack_ast(stack, sexp_at(ast, 3));
  switch (sexp_get_tag(sexp_at(ast, 2))) {
  case AST_PLUS:
    stack_instruction_add(stack);
    break;
  case AST_MINUS:
    stack_instruction_sub(stack);
    break;
  default:
    assert(0);
    break;
  }
}
void stack_assignment_expression(Stack *stack, Sexp *ast) {
  assert(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  assert(AST_ASSIGN == sexp_get_tag(sexp_at(ast, 2)));
  stack_ast(stack, sexp_at(ast, 3));
  stack_identifier_store(stack, sexp_at(ast, 1));
}
void stack_constant_expression(Stack *stack, Sexp *ast) {
  assert(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
}
