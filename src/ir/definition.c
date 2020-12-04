#include "ir/definition.h"

#include "ir/stack_impl.h"

static int stack_count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return stack_count_return(sexp_car(ast)) +
           stack_count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}
static const char *stack_function_name(Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    assert(2 == sexp_length(ast));
    ast = sexp_at(ast, 1);
    assert(sexp_is_symbol(ast));
    return sexp_get_symbol(ast);
  case AST_DECLARATOR:
    if (2 == sexp_length(ast)) {
      return stack_function_name(sexp_at(ast, 1));
    } else if (3 == sexp_length(ast)) {
      return stack_function_name(sexp_at(ast, 2));
    } else {
      assert(0);
      return NULL;
    }
  case AST_DIRECT_DECLARATOR:
    if (4 == sexp_length(ast)) {
      return stack_function_name(sexp_at(ast, 2));
    } else {
      return stack_function_name(sexp_at(ast, 1));
    }
  case AST_FUNCTION_DEFINITION:
    return stack_function_name(sexp_at(ast, 2));
  default:
    assert(0);
    return NULL;
  }
}
void stack_function_definition(Stack *stack, Sexp *ast) {
  Value *entry = stack_new_block(stack);
  Value *ret = NULL;
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  if (1 < stack_count_return(ast)) {
    ret = stack_init_return_block(stack);
    stack_alloca(stack, "$retval");
    stack_pop(stack);
  }
  stack_change_flow(stack, entry, NULL);
  stack_ast(stack, sexp_at(ast, 4));
  if (ret) {
    stack_change_flow(stack, ret, NULL);
    stack_load_from_symbol(stack, "$retval");
    stack_instruction_ret(stack);
  }
  stack_set_function_name(stack, stack_function_name(ast));
}
