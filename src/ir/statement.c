#include "ir/statement.h"

#include "ir/stack_impl.h"

static Bool have_default(Sexp *ast) {
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  assert(AST_SWITCH == sexp_get_number(sexp_at(ast, 1)));
  ast = sexp_at(ast, 5);
  assert(AST_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 3);
  assert(AST_STATEMENT_LIST == sexp_get_tag(ast));
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    Sexp *stmt = sexp_car(ast);
    assert(AST_STATEMENT == sexp_get_tag(stmt));
    stmt = sexp_at(stmt, 1);
    if (AST_LABELED_STATEMENT == sexp_get_tag(stmt)) {
      stmt = sexp_at(stmt, 1);
      if (sexp_is_number(stmt) && AST_DEFAULT == sexp_get_number(stmt)) {
        return true;
      }
    }
  }
  return false;
}

void stack_statement(Stack *stack, Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
}
static void stack_default_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_get_default_block(stack);
  stack_change_flow(stack, next, NULL);
  stack_ast(stack, sexp_at(ast, 3));
}
static void stack_case_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_new_block(stack);
  stack_ast(stack, sexp_at(ast, 2));
  stack_push(stack, next);
  stack_instruction_switch_case(stack);
  stack_change_flow(stack, next, NULL);
  stack_ast(stack, sexp_at(ast, 4));
}
void stack_labeled_statement(Stack *stack, Sexp *ast) {
  assert(AST_LABELED_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  switch (sexp_get_number(sexp_at(ast, 1))) {
  case AST_CASE:
    stack_case_statement(stack, ast);
    break;
  case AST_DEFAULT:
    stack_default_statement(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
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
static void stack_if_statement(Stack *stack, Sexp *ast) {
  Value *if_then = stack_new_block(stack);
  Value *if_else = stack_new_block(stack);
  Value *prev = stack_get_next_block(stack);
  Value *next;
  if (8 == sexp_length(ast)) {
    next = stack_new_block(stack);
  } else {
    assert(6 == sexp_length(ast));
    next = if_else;
  }
  stack_ast(stack, sexp_at(ast, 3));
  stack_push_integer(stack, "0");
  stack_instruction_icmp_ne(stack);
  stack_push(stack, if_then);
  stack_push(stack, if_else);
  stack_instruction_br_cond(stack);
  stack_change_flow(stack, if_then, next);
  stack_ast(stack, sexp_at(ast, 5));
  if (8 == sexp_length(ast)) {
    stack_change_flow(stack, if_else, next);
    stack_ast(stack, sexp_at(ast, 7));
  }
  stack_change_flow(stack, next, prev);
}
static void stack_switch_statement(Stack *stack, Sexp *ast) {
  Value *prev = stack_get_next_block(stack);
  Value *next = stack_new_block(stack);
  Value *dflt = have_default(ast) ? stack_new_block(stack) : next;
  stack_set_next_block(stack, next);
  stack_ast(stack, sexp_at(ast, 3));
  stack_push(stack, dflt);
  stack_instruction_switch(stack);
  ast = sexp_at(ast, 5);
  stack_ast(stack, ast);
  stack_pop(stack);
  stack_change_flow(stack, next, prev);
}
void stack_selection_statement(Stack *stack, Sexp *ast) {
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  switch (sexp_get_number(sexp_at(ast, 1))) {
  case AST_IF:
    stack_if_statement(stack, ast);
    break;
  case AST_SWITCH:
    stack_switch_statement(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
}
static void stack_break_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_get_next_block(stack);
  stack_push(stack, next);
  stack_instruction_br(stack);
  stack_set_next_block(stack, NULL);
  UTILITY_UNUSED(ast);
}
static void stack_return_statement(Stack *stack, Sexp *ast) {
  Value *ret = stack_get_return_block(stack);
  assert(!sexp_is_nil(sexp_at(ast, 2)));
  stack_ast(stack, sexp_at(ast, 2));
  if (ret) {
    stack_store_to_symbol(stack, "$retval");
    stack_pop(stack);
    stack_push(stack, ret);
    stack_instruction_br(stack);
  } else {
    stack_instruction_ret(stack);
  }
  stack_set_next_block(stack, NULL);
}
void stack_jump_statement(Stack *stack, Sexp *ast) {
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  switch (sexp_get_number(sexp_at(ast, 1))) {
  case AST_BREAK:
    stack_break_statement(stack, ast);
    break;
  case AST_RETURN:
    stack_return_statement(stack, ast);
    break;
  default:
    break;
  }
}
