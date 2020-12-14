#include "ir/definition.h"

#include "ir/stack_impl.h"

static const char *stack_function_name(Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    return stack_identifier_symbol(ast);
  case AST_DECLARATOR:
    switch (sexp_length(ast)) {
    case 2:
      return stack_function_name(sexp_at(ast, 1));
    case 3:
      return stack_function_name(sexp_at(ast, 2));
    default:
      assert(0);
      return NULL;
    }
  case AST_DIRECT_DECLARATOR:
    switch (sexp_length(ast)) {
    case 2:
      return stack_function_name(sexp_at(ast, 1));
    case 4:
      return stack_function_name(sexp_at(ast, 2));
    case 5:
      return stack_function_name(sexp_at(ast, 1));
    default:
      assert(0);
      return NULL;
    }
  default:
    assert(0);
    return NULL;
  }
}
void stack_function_definition(Stack *stack, Sexp *ast) {
  Value *ret = stack_get_next(stack, STACK_NEXT_RETURN);
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  if (ret) {
    stack_alloca(stack, "$retval");
    stack_pop(stack);
  }
  stack_ast(stack, sexp_at(ast, 4));
  if (ret) {
    stack_instruction_br(stack, ret);
    stack_jump_block(stack, ret);
    stack_load_from_symbol(stack, "$retval");
    stack_instruction_ret(stack);
  }
  stack_set_function_name(stack, stack_function_name(sexp_at(ast, 2)));
}
