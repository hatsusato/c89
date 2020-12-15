#include "ir/statement.h"

#include "ir/stack_impl.h"

static Bool has_default_statement(Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  if (AST_LABELED_STATEMENT == sexp_get_tag(ast)) {
    switch (sexp_get_tag(sexp_at(ast, 1))) {
    case AST_IDENTIFIER:
      return has_default_statement(sexp_at(ast, 3));
    case AST_CASE:
      return has_default_statement(sexp_at(ast, 4));
    case AST_DEFAULT:
      return true;
    default:
      assert(0);
      break;
    }
  }
  return false;
}
static Bool switch_has_default(Sexp *ast) {
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(AST_SWITCH == sexp_get_tag(sexp_at(ast, 1)));
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
  Value *swch = stack_get_next(stack, STACK_NEXT_SWITCH);
  return 0 == value_length(swch) || 0 < value_length(curr) || dflt == curr;
}

void stack_statement(Stack *stack, Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
}
static void stack_label_statement(Stack *stack, Sexp *ast) {
  const char *label = stack_identifier_symbol(sexp_at(ast, 1));
  Value *next = stack_label(stack, label);
  stack_instruction_br(stack, next);
  stack_jump_block(stack, next);
  stack_ast(stack, sexp_at(ast, 3));
}
static void stack_case_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_get_next(stack, STACK_NEXT_CURRENT);
  Value *constant;
  if (switch_new_case(stack)) {
    next = stack_new_block(stack);
    stack_instruction_br(stack, next);
    stack_jump_block(stack, next);
  }
  stack_ast(stack, sexp_at(ast, 2));
  constant = stack_pop(stack);
  stack_instruction_switch_case(stack, constant, next);
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
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_IDENTIFIER:
    stack_label_statement(stack, ast);
    break;
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
    Value *lhs, *rhs, *icmp;
    stack_ast(stack, sexp_at(ast, 3));
    lhs = stack_pop(stack);
    stack_push_integer(stack, "0");
    rhs = stack_pop(stack);
    icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
    stack_instruction_br_cond(stack, icmp, then_block, next);
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
    Value *lhs, *rhs, *icmp;
    stack_ast(stack, sexp_at(ast, 3));
    lhs = stack_pop(stack);
    stack_push_integer(stack, "0");
    rhs = stack_pop(stack);
    icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
    stack_instruction_br_cond(stack, icmp, then_block, else_block);
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
      Value *next_default = stack_set_next(stack, STACK_NEXT_DEFAULT, dflt);
      Value *next_switch =
          stack_set_next(stack, STACK_NEXT_SWITCH, stack_top(stack));
      stack_ast(stack, sexp_at(ast, 5));
      stack_instruction_br(stack, next);
      stack_set_next(stack, STACK_NEXT_BREAK, next_break);
      stack_set_next(stack, STACK_NEXT_DEFAULT, next_default);
      stack_set_next(stack, STACK_NEXT_SWITCH, next_switch);
    }
    stack_pop(stack);
  }
  stack_jump_block(stack, next);
}
void stack_selection_statement(Stack *stack, Sexp *ast) {
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_IF:
    switch (sexp_length(ast)) {
    case 6:
      stack_if_statement(stack, ast);
      break;
    case 8:
      stack_if_else_statement(stack, ast);
      break;
    default:
      assert(0);
      break;
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
    Value *lhs, *rhs, *icmp;
    stack_jump_block(stack, guard);
    stack_ast(stack, sexp_at(ast, 3));
    lhs = stack_pop(stack);
    stack_push_integer(stack, "0");
    rhs = stack_pop(stack);
    icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
    stack_instruction_br_cond(stack, icmp, body, next);
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
    Value *lhs, *rhs, *icmp;
    stack_jump_block(stack, guard);
    stack_ast(stack, sexp_at(ast, 5));
    lhs = stack_pop(stack);
    stack_push_integer(stack, "0");
    rhs = stack_pop(stack);
    icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
    stack_instruction_br_cond(stack, icmp, body, next);
  }
  stack_jump_block(stack, next);
}
static void stack_for_statement(Stack *stack, Sexp *ast) {
  Value *guard;
  Value *body = stack_new_block(stack);
  Value *next = stack_new_block(stack);
  Value *step;
  if (!sexp_is_nil(sexp_at(ast, 3))) {
    stack_ast(stack, sexp_at(ast, 3));
    stack_pop(stack);
  }
  guard = sexp_is_nil(sexp_at(ast, 5)) ? body : stack_new_block(stack);
  stack_instruction_br(stack, guard);
  if (!sexp_is_nil(sexp_at(ast, 5))) {
    Value *lhs, *rhs, *icmp;
    stack_jump_block(stack, guard);
    assert(sexp_at(ast, 5));
    stack_ast(stack, sexp_at(ast, 5));
    lhs = stack_pop(stack);
    stack_push_integer(stack, "0");
    rhs = stack_pop(stack);
    icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
    stack_instruction_br_cond(stack, icmp, body, next);
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
  Value *next_switch = stack_set_next(stack, STACK_NEXT_SWITCH, NULL);
  assert(AST_ITERATION_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
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
  stack_set_next(stack, STACK_NEXT_SWITCH, next_switch);
}
static void stack_goto_statement(Stack *stack, Sexp *ast) {
  const char *label = stack_identifier_symbol(sexp_at(ast, 2));
  Value *next = stack_label(stack, label);
  stack_instruction_br(stack, next);
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
    stack_instruction_ret(stack, stack_pop(stack));
  }
}
void stack_jump_statement(Stack *stack, Sexp *ast) {
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_GOTO:
    stack_goto_statement(stack, ast);
    break;
  case AST_CONTINUE:
    stack_instruction_br(stack, stack_get_next(stack, STACK_NEXT_CONTINUE));
    break;
  case AST_BREAK:
    stack_instruction_br(stack, stack_get_next(stack, STACK_NEXT_BREAK));
    break;
  case AST_RETURN:
    stack_return_statement(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
  stack_set_next(stack, STACK_NEXT_BLOCK, NULL);
}
