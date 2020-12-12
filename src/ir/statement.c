#include "ir/statement.h"

#include "ir/stack_impl.h"

static Bool has_default_statement(Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  if (AST_LABELED_STATEMENT == sexp_get_tag(ast)) {
    Sexp *head = sexp_at(ast, 1);
    if (!sexp_is_number(head)) {
      assert(AST_IDENTIFIER == sexp_get_tag(head));
      return has_default_statement(sexp_at(ast, 3));
    } else if (AST_CASE == sexp_get_number(head)) {
      return has_default_statement(sexp_at(ast, 4));
    } else {
      assert(AST_DEFAULT == sexp_get_number(head));
      return true;
    }
  }
  return false;
}
static Bool switch_has_default(Sexp *ast) {
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
    if (has_default_statement(sexp_car(ast))) {
      return true;
    }
  }
  return false;
}
static Bool switch_new_case(Stack *stack) {
  Value *curr = stack_get_next(stack, STACK_NEXT_CURRENT);
  Value *dflt = stack_get_next(stack, STACK_NEXT_DEFAULT);
  Value *top = stack_top(stack);
  assert(VALUE_INSTRUCTION_SWITCH == value_kind(top));
  return 2 == value_length(top) || value_length(curr) || dflt == curr;
}

void stack_statement(Stack *stack, Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
}
static void stack_case_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_get_next(stack, STACK_NEXT_CURRENT);
  if (switch_new_case(stack)) {
    next = stack_new_block(stack);
    stack_instruction_br(stack, next);
    stack_jump_block(stack, next);
  }
  stack_ast(stack, sexp_at(ast, 2));
  stack_instruction_switch_case(stack, next);
  stack_ast(stack, sexp_at(ast, 4));
}
static void stack_default_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_get_next(stack, STACK_NEXT_DEFAULT);
  stack_instruction_br(stack, next);
  stack_jump_block(stack, next);
  stack_ast(stack, sexp_at(ast, 3));
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
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 2));
  stack_ast(stack, sexp_at(ast, 3));
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
  Value *next = stack_new_block(stack);
  Value *then_block = stack_new_block(stack);
  {
    stack_ast(stack, sexp_at(ast, 3));
    stack_push_integer(stack, "0");
    stack_instruction_icmp_ne(stack);
    stack_instruction_br_cond(stack, then_block, next);
  }
  {
    stack_jump_block(stack, then_block);
    stack_ast(stack, sexp_at(ast, 5));
    stack_instruction_br(stack, next);
  }
  stack_jump_block(stack, next);
}
static void stack_if_else_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_new_block(stack);
  Value *then_block = stack_new_block(stack);
  Value *else_block = stack_new_block(stack);
  Value *then_next, *else_next;
  {
    stack_ast(stack, sexp_at(ast, 3));
    stack_push_integer(stack, "0");
    stack_instruction_icmp_ne(stack);
    stack_instruction_br_cond(stack, then_block, else_block);
  }
  stack_set_next(stack, STACK_NEXT_BLOCK, next);
  {
    stack_jump_block(stack, then_block);
    stack_ast(stack, sexp_at(ast, 5));
    stack_instruction_br(stack, next);
  }
  then_next = stack_get_next(stack, STACK_NEXT_BLOCK);
  assert(!then_next || then_next == next);
  stack_set_next(stack, STACK_NEXT_BLOCK, next);
  {
    stack_jump_block(stack, else_block);
    stack_ast(stack, sexp_at(ast, 7));
    stack_instruction_br(stack, next);
  }
  else_next = stack_get_next(stack, STACK_NEXT_BLOCK);
  assert(!else_next || else_next == next);
  if (then_next || else_next) {
    stack_jump_block(stack, next);
    stack_set_next(stack, STACK_NEXT_BLOCK, next);
  }
}
static void stack_switch_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_new_block(stack);
  Value *dflt = switch_has_default(ast) ? stack_new_block(stack) : next;
  {
    stack_ast(stack, sexp_at(ast, 3));
    stack_instruction_switch(stack, dflt);
    {
      Value *next_break = stack_set_next(stack, STACK_NEXT_BREAK, next);
      stack_ast(stack, sexp_at(ast, 5));
      stack_instruction_br(stack, next);
      stack_set_next(stack, STACK_NEXT_BREAK, next_break);
    }
    stack_pop(stack);
  }
  stack_jump_block(stack, next);
}
void stack_selection_statement(Stack *stack, Sexp *ast) {
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  switch (sexp_get_number(sexp_at(ast, 1))) {
  case AST_IF:
    assert(6 == sexp_length(ast) || 8 == sexp_length(ast));
    if (6 == sexp_length(ast)) {
      stack_if_statement(stack, ast);
    } else if (8 == sexp_length(ast)) {
      stack_if_else_statement(stack, ast);
    }
    break;
  case AST_SWITCH:
    stack_switch_statement(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
}
static void stack_while_statement(Stack *stack, Sexp *ast) {
  Value *guard = stack_new_block(stack);
  Value *body = stack_new_block(stack);
  Value *next = stack_new_block(stack);
  stack_instruction_br(stack, guard);
  {
    stack_jump_block(stack, guard);
    stack_ast(stack, sexp_at(ast, 3));
    stack_push_integer(stack, "0");
    stack_instruction_icmp_ne(stack);
    stack_instruction_br_cond(stack, body, next);
  }
  {
    Value *next_break = stack_set_next(stack, STACK_NEXT_BREAK, next);
    Value *next_continue = stack_set_next(stack, STACK_NEXT_CONTINUE, guard);
    stack_jump_block(stack, body);
    stack_ast(stack, sexp_at(ast, 5));
    stack_instruction_br(stack, guard);
    stack_set_next(stack, STACK_NEXT_BREAK, next_break);
    stack_set_next(stack, STACK_NEXT_CONTINUE, next_continue);
  }
  stack_jump_block(stack, next);
}
static void stack_do_while_statement(Stack *stack, Sexp *ast) {
  Value *body = stack_new_block(stack);
  Value *guard = stack_new_block(stack);
  Value *next = stack_new_block(stack);
  stack_instruction_br(stack, body);
  {
    Value *next_break = stack_set_next(stack, STACK_NEXT_BREAK, next);
    Value *next_continue = stack_set_next(stack, STACK_NEXT_CONTINUE, guard);
    stack_jump_block(stack, body);
    stack_ast(stack, sexp_at(ast, 2));
    stack_instruction_br(stack, guard);
    stack_set_next(stack, STACK_NEXT_BREAK, next_break);
    stack_set_next(stack, STACK_NEXT_CONTINUE, next_continue);
  }
  {
    stack_jump_block(stack, guard);
    stack_ast(stack, sexp_at(ast, 5));
    stack_push_integer(stack, "0");
    stack_instruction_icmp_ne(stack);
    stack_instruction_br_cond(stack, body, next);
  }
  stack_jump_block(stack, next);
}
static void stack_for_statement(Stack *stack, Sexp *ast) {
  Value *guard = stack_new_block(stack);
  Value *body = stack_new_block(stack);
  Value *next = stack_new_block(stack);
  Value *step;
  if (!sexp_is_nil(sexp_at(ast, 3))) {
    stack_ast(stack, sexp_at(ast, 3));
    stack_pop(stack);
  }
  stack_instruction_br(stack, guard);
  {
    stack_jump_block(stack, guard);
    assert(sexp_at(ast, 5));
    stack_ast(stack, sexp_at(ast, 5));
    stack_push_integer(stack, "0");
    stack_instruction_icmp_ne(stack);
    stack_instruction_br_cond(stack, body, next);
  }
  step = sexp_is_nil(sexp_at(ast, 7)) ? guard : stack_new_block(stack);
  {
    Value *next_break = stack_set_next(stack, STACK_NEXT_BREAK, next);
    Value *next_continue = stack_set_next(stack, STACK_NEXT_CONTINUE, step);
    stack_jump_block(stack, body);
    stack_ast(stack, sexp_at(ast, 9));
    stack_instruction_br(stack, step);
    stack_set_next(stack, STACK_NEXT_BREAK, next_break);
    stack_set_next(stack, STACK_NEXT_CONTINUE, next_continue);
  }
  if (!sexp_is_nil(sexp_at(ast, 7))) {
    stack_jump_block(stack, step);
    stack_ast(stack, sexp_at(ast, 7));
    stack_pop(stack);
    stack_instruction_br(stack, guard);
  }
  stack_jump_block(stack, next);
}
void stack_iteration_statement(Stack *stack, Sexp *ast) {
  assert(AST_ITERATION_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  switch (sexp_get_number(sexp_at(ast, 1))) {
  case AST_WHILE:
    stack_while_statement(stack, ast);
    break;
  case AST_DO:
    stack_do_while_statement(stack, ast);
    break;
  case AST_FOR:
    stack_for_statement(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
}
static void stack_continue_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_get_next(stack, STACK_NEXT_CONTINUE);
  assert(next);
  stack_instruction_br(stack, next);
  stack_set_next(stack, STACK_NEXT_BLOCK, NULL);
  UTILITY_UNUSED(ast);
}
static void stack_break_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_get_next(stack, STACK_NEXT_BREAK);
  assert(next);
  stack_instruction_br(stack, next);
  stack_set_next(stack, STACK_NEXT_BLOCK, NULL);
  UTILITY_UNUSED(ast);
}
static void stack_return_statement(Stack *stack, Sexp *ast) {
  Value *ret = stack_get_next(stack, STACK_NEXT_RETURN);
  assert(!sexp_is_nil(sexp_at(ast, 2)));
  stack_ast(stack, sexp_at(ast, 2));
  if (ret) {
    stack_store_to_symbol(stack, "$retval");
    stack_pop(stack);
    stack_instruction_br(stack, ret);
  } else {
    stack_instruction_ret(stack);
  }
}
void stack_jump_statement(Stack *stack, Sexp *ast) {
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  switch (sexp_get_number(sexp_at(ast, 1))) {
  case AST_CONTINUE:
    stack_continue_statement(stack, ast);
    break;
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
