#include "ir/expression.h"

#include "ir/stack_impl.h"

Value *stack_additive_expression(Stack *stack, Sexp *ast) {
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  {
    Value *lhs = stack_ast(stack, sexp_at(ast, 1));
    Value *rhs = stack_ast(stack, sexp_at(ast, 3));
    switch (sexp_get_tag(sexp_at(ast, 2))) {
    case AST_PLUS:
      return stack_instruction_add(stack, lhs, rhs);
    case AST_MINUS:
      return stack_instruction_sub(stack, lhs, rhs);
    default:
      assert(0);
      return NULL;
    }
  }
}
Value *stack_assignment_expression(Stack *stack, Sexp *ast) {
  assert(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  assert(AST_ASSIGN == sexp_get_tag(sexp_at(ast, 2)));
  {
    const char *symbol = stack_identifier_symbol(sexp_at(ast, 1));
    Value *lhs = stack_find_alloca(stack, symbol);
    Value *rhs = stack_ast(stack, sexp_at(ast, 3));
    return stack_instruction_store(stack, rhs, lhs);
  }
}
Value *stack_constant_expression(Stack *stack, Sexp *ast) {
  assert(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  return stack_ast(stack, sexp_at(ast, 1));
}
