#include "ir/definition.h"

#include "ir/stack_impl.h"

Value *stack_function_definition(Stack *stack, Sexp *ast) {
  Block *ret = stack_get_next(stack, STACK_NEXT_RETURN);
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  if (ret) {
    stack_alloca(stack, "$retval");
  }
  stack_ast(stack, sexp_at(ast, 4));
  if (ret) {
    Value *expr;
    stack_instruction_br(stack, value_of(ret));
    stack_jump_block(stack, value_of(ret));
    expr = stack_find_alloca(stack, "$retval");
    expr = stack_instruction_load(stack, expr);
    stack_instruction_ret(stack, expr);
  }
  return NULL;
}
