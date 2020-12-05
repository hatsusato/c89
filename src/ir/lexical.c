#include "ir/lexical.h"

#include "ir/stack_impl.h"

void stack_identifier(Stack *stack, Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  stack_load_from_symbol(stack, sexp_get_symbol(ast));
}
void stack_integer_constant(Stack *stack, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  stack_push_integer(stack, sexp_get_symbol(ast));
}
