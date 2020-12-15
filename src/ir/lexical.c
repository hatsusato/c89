#include "ir/lexical.h"

#include "ir/stack_impl.h"

const char *stack_identifier_symbol(Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  return sexp_get_symbol(ast);
}
void stack_identifier(Stack *stack, Sexp *ast) {
  stack_load_from_symbol(stack, stack_identifier_symbol(ast));
}
void stack_identifier_alloca(Stack *stack, Sexp *ast) {
  stack_alloca(stack, stack_identifier_symbol(ast));
}
void stack_integer_constant(Stack *stack, Sexp *ast) {
  Value *value;
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  value = stack_new_integer(stack, sexp_get_symbol(ast));
  stack_set_prev(stack, value);
}
