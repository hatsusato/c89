#include "ir/statement.h"

#include "ast/ast_tag.h"
#include "ir/instruction.h"
#include "ir/stack_impl.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

void stack_statement(Stack *stack, Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
}
void stack_compound_statement(Stack *stack, Sexp *ast) {
  Value *next;
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 2));
  stack_ast(stack, sexp_at(ast, 3));
  next = stack_get_next_block(stack);
  if (next) {
    stack_push(stack, next);
    stack_instruction_br(stack);
  }
}
void stack_expression_statement(Stack *stack, Sexp *ast) {
  assert(AST_EXPRESSION_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  if (!sexp_is_nil(ast)) {
    stack_ast(stack, ast);
    stack_pop(stack);
  }
}
static void stack_new_integer_constant(Stack *stack, const char *integer) {
  stack_new_value(stack, VALUE_INTEGER_CONSTANT);
  stack_set_symbol(stack, integer);
}
void stack_selection_statement(Stack *stack, Sexp *ast) {
  Value *if_then = stack_new_block(stack);
  Value *if_else = stack_new_block(stack);
  Value *prev = stack_get_next_block(stack);
  Value *next;
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(AST_IF == sexp_get_number(sexp_at(ast, 1)));
  switch (sexp_length(ast)) {
  case 6:
    stack_ast(stack, sexp_at(ast, 3));
    stack_new_integer_constant(stack, "0");
    stack_instruction_icmp_ne(stack);
    stack_push(stack, if_then);
    stack_push(stack, if_else);
    stack_instruction_br_cond(stack);
    stack_change_flow(stack, if_then, if_else);
    stack_ast(stack, sexp_at(ast, 5));
    stack_change_flow(stack, if_else, prev);
    break;
  case 8:
    next = stack_new_block(stack);
    stack_ast(stack, sexp_at(ast, 3));
    stack_new_integer_constant(stack, "0");
    stack_instruction_icmp_ne(stack);
    stack_push(stack, if_then);
    stack_push(stack, if_else);
    stack_instruction_br_cond(stack);
    stack_change_flow(stack, if_then, next);
    stack_ast(stack, sexp_at(ast, 5));
    stack_change_flow(stack, if_else, next);
    stack_ast(stack, sexp_at(ast, 7));
    stack_change_flow(stack, next, prev);
    break;
  default:
    assert(0);
    break;
  }
}
void stack_jump_statement(Stack *stack, Sexp *ast) {
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  assert(!sexp_is_nil(ast));
  stack_ast(stack, ast);
  stack_return(stack);
}
