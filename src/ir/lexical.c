#include "ir/lexical.h"

#include "ast/ast_tag.h"
#include "ir/instruction.h"
#include "ir/stack.h"
#include "ir/stack_impl.h"
#include "sexp.h"
#include "utility.h"

void stack_identifier(Stack *stack, Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  stack_push_symbol(stack, sexp_get_symbol(ast));
  stack_instruction_load(stack);
}
void stack_integer_constant(Stack *stack, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  stack_new_value(stack, VALUE_INTEGER_CONSTANT);
  stack_set_symbol(stack, sexp_get_symbol(ast));
}
