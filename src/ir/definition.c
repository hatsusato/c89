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
static void stack_function_definition(Stack *stack, Sexp *ast) {
  Value *entry = stack_new_block(stack);
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  if (1 < stack_count_return(ast)) {
    stack_ret_init(stack);
  }
  if (stack_ret(stack)) {
    stack_instruction_alloca(stack, "$retval");
    stack_pop(stack);
  }
  stack_change_flow(stack, entry, stack_ret(stack));
  stack_ast(stack, sexp_at(ast, 4));
  if (stack_ret(stack)) {
    stack_change_flow(stack, stack_ret(stack), NULL);
    stack_push_symbol(stack, "$retval");
    stack_instruction_load(stack);
    stack_instruction_ret(stack);
  }
  stack_set_function_name(stack, ast);
}
static void stack_ast_map(Stack *stack, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    stack_ast(stack, sexp_car(ast));
  }
}

void stack_ast(Stack *stack, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    stack_identifier(stack, ast);
    break;
  case AST_INTEGER_CONSTANT:
    stack_integer_constant(stack, ast);
    break;
  case AST_ADDITIVE_EXPRESSION:
    stack_additive_expression(stack, ast);
    break;
  case AST_ASSIGNMENT_EXPRESSION:
    stack_assignment_expression(stack, ast);
    break;
  case AST_DECLARATION:
    stack_declaration(stack, ast);
    break;
  case AST_STATEMENT:
    stack_statement(stack, ast);
    break;
  case AST_COMPOUND_STATEMENT:
    stack_compound_statement(stack, ast);
    break;
  case AST_DECLARATION_LIST:
    stack_ast_map(stack, ast);
    break;
  case AST_STATEMENT_LIST:
    stack_ast_map(stack, ast);
    break;
  case AST_EXPRESSION_STATEMENT:
    stack_expression_statement(stack, ast);
    break;
  case AST_SELECTION_STATEMENT:
    stack_selection_statement(stack, ast);
    break;
  case AST_JUMP_STATEMENT:
    stack_jump_statement(stack, ast);
    break;
  case AST_TRANSLATION_UNIT:
    stack_ast_map(stack, ast);
    break;
  case AST_EXTERNAL_DECLARATION:
    break;
  case AST_FUNCTION_DEFINITION:
    stack_function_definition(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
}
