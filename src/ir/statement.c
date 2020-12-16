#include "ir/statement.h"

#include "ir/stack_impl.h"

static Bool switch_new_case(Stack *stack) {
  Block *curr = stack_get_next(stack, STACK_NEXT_CURRENT);
  Block *dflt = stack_get_next(stack, STACK_NEXT_DEFAULT);
  Block *swch = stack_get_next(stack, STACK_NEXT_SWITCH);
  return 0 == value_length(value_of(swch)) ||
         0 < value_length(value_of(curr)) || dflt == curr;
}

Value *stack_statement(Stack *stack, Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  return stack_ast(stack, sexp_at(ast, 1));
}
static void stack_label_statement(Stack *stack, Sexp *ast) {
  const char *label = stack_identifier_symbol(sexp_at(ast, 1));
  Block *next = stack_label(stack, label);
  stack_instruction_br(stack, next);
  stack_jump_block(stack, next);
  stack_ast(stack, sexp_at(ast, 3));
}
static void stack_case_statement(Stack *stack, Sexp *ast) {
  Block *next = stack_get_next(stack, STACK_NEXT_CURRENT);
  if (switch_new_case(stack)) {
    next = stack_new_block(stack);
    stack_instruction_br(stack, next);
    stack_jump_block(stack, next);
  }
  {
    Value *constant = stack_ast(stack, sexp_at(ast, 2));
    stack_instruction_switch_case(stack, constant, value_of(next));
    stack_ast(stack, sexp_at(ast, 4));
  }
}
static void stack_default_statement(Stack *stack, Sexp *ast) {
  Block *next = stack_new_block(stack);
  assert(!stack_get_next(stack, STACK_NEXT_DEFAULT));
  stack_set_next(stack, STACK_NEXT_DEFAULT, next);
  stack_instruction_br(stack, next);
  stack_jump_block(stack, next);
  stack_ast(stack, sexp_at(ast, 3));
}
Value *stack_labeled_statement(Stack *stack, Sexp *ast) {
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
  return NULL;
}
Value *stack_compound_statement(Stack *stack, Sexp *ast) {
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 2));
  stack_ast(stack, sexp_at(ast, 3));
  return NULL;
}
Value *stack_expression_statement(Stack *stack, Sexp *ast) {
  assert(AST_EXPRESSION_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  if (!sexp_is_nil(ast)) {
    stack_ast(stack, ast);
  }
  return NULL;
}
static void stack_if_statement(Stack *stack, Sexp *ast) {
  Block *next = stack_new_block(stack);
  Block *then_block = stack_new_block(stack);
  {
    Value *lhs = stack_ast(stack, sexp_at(ast, 3));
    Value *rhs = stack_new_integer(stack, "0");
    Value *icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
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
  Block *next = stack_new_block(stack);
  Block *then_block = stack_new_block(stack);
  Block *else_block = stack_new_block(stack);
  Block *then_next, *else_next;
  {
    Value *lhs = stack_ast(stack, sexp_at(ast, 3));
    Value *rhs = stack_new_integer(stack, "0");
    Value *icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
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
  Block *block = stack_new_block(stack);
  Value *expr = stack_ast(stack, sexp_at(ast, 3));
  Value *instr = stack_instruction_switch(stack, expr);
  {
    Block *next_break = stack_set_next(stack, STACK_NEXT_BREAK, NULL);
    Block *next_default = stack_set_next(stack, STACK_NEXT_DEFAULT, NULL);
    Block *next_switch = stack_set_next(stack, STACK_NEXT_SWITCH, block);
    stack_ast(stack, sexp_at(ast, 5));
    stack_instruction_switch_finish(stack, instr);
    stack_set_next(stack, STACK_NEXT_BREAK, next_break);
    stack_set_next(stack, STACK_NEXT_DEFAULT, next_default);
    stack_set_next(stack, STACK_NEXT_SWITCH, next_switch);
  }
}
Value *stack_selection_statement(Stack *stack, Sexp *ast) {
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
  return NULL;
}
static void stack_while_statement(Stack *stack, Sexp *ast) {
  Block *guard = stack_new_block(stack);
  Block *body = stack_new_block(stack);
  Block *next = stack_new_block(stack);
  stack_instruction_br(stack, guard);
  stack_jump_block(stack, guard);
  {
    Value *lhs = stack_ast(stack, sexp_at(ast, 3));
    Value *rhs = stack_new_integer(stack, "0");
    Value *icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
    stack_instruction_br_cond(stack, icmp, body, next);
  }
  {
    Block *next_break = stack_set_next(stack, STACK_NEXT_BREAK, next);
    Block *next_continue = stack_set_next(stack, STACK_NEXT_CONTINUE, guard);
    stack_jump_block(stack, body);
    stack_ast(stack, sexp_at(ast, 5));
    stack_instruction_br(stack, guard);
    stack_set_next(stack, STACK_NEXT_BREAK, next_break);
    stack_set_next(stack, STACK_NEXT_CONTINUE, next_continue);
  }
  stack_jump_block(stack, next);
}
static void stack_do_while_statement(Stack *stack, Sexp *ast) {
  Block *body = stack_new_block(stack);
  Block *guard = stack_new_block(stack);
  Block *next = stack_new_block(stack);
  stack_instruction_br(stack, body);
  {
    Block *next_break = stack_set_next(stack, STACK_NEXT_BREAK, next);
    Block *next_continue = stack_set_next(stack, STACK_NEXT_CONTINUE, guard);
    stack_jump_block(stack, body);
    stack_ast(stack, sexp_at(ast, 2));
    stack_instruction_br(stack, guard);
    stack_set_next(stack, STACK_NEXT_BREAK, next_break);
    stack_set_next(stack, STACK_NEXT_CONTINUE, next_continue);
  }
  stack_jump_block(stack, guard);
  {
    Value *lhs = stack_ast(stack, sexp_at(ast, 5));
    Value *rhs = stack_new_integer(stack, "0");
    Value *icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
    stack_instruction_br_cond(stack, icmp, body, next);
  }
  stack_jump_block(stack, next);
}
static void stack_for_statement(Stack *stack, Sexp *ast) {
  Block *guard;
  Block *body = stack_new_block(stack);
  Block *next = stack_new_block(stack);
  Block *step;
  if (!sexp_is_nil(sexp_at(ast, 3))) {
    stack_ast(stack, sexp_at(ast, 3));
  }
  guard = sexp_is_nil(sexp_at(ast, 5)) ? body : stack_new_block(stack);
  stack_instruction_br(stack, guard);
  if (!sexp_is_nil(sexp_at(ast, 5))) {
    stack_jump_block(stack, guard);
    assert(sexp_at(ast, 5));
    {
      Value *lhs = stack_ast(stack, sexp_at(ast, 5));
      Value *rhs = stack_new_integer(stack, "0");
      Value *icmp = stack_instruction_icmp_ne(stack, lhs, rhs);
      stack_instruction_br_cond(stack, icmp, body, next);
    }
  }
  step = sexp_is_nil(sexp_at(ast, 7)) ? guard : stack_new_block(stack);
  {
    Block *next_break = stack_set_next(stack, STACK_NEXT_BREAK, next);
    Block *next_continue = stack_set_next(stack, STACK_NEXT_CONTINUE, step);
    stack_jump_block(stack, body);
    stack_ast(stack, sexp_at(ast, 9));
    stack_instruction_br(stack, step);
    stack_set_next(stack, STACK_NEXT_BREAK, next_break);
    stack_set_next(stack, STACK_NEXT_CONTINUE, next_continue);
  }
  if (!sexp_is_nil(sexp_at(ast, 7))) {
    stack_jump_block(stack, step);
    stack_ast(stack, sexp_at(ast, 7));
    stack_instruction_br(stack, guard);
  }
  stack_jump_block(stack, next);
}
Value *stack_iteration_statement(Stack *stack, Sexp *ast) {
  Block *next_switch = stack_set_next(stack, STACK_NEXT_SWITCH, NULL);
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
  return NULL;
}
static void stack_goto_statement(Stack *stack, Sexp *ast) {
  const char *label = stack_identifier_symbol(sexp_at(ast, 2));
  Block *next = stack_label(stack, label);
  stack_instruction_br(stack, next);
}
static void stack_continue_statement(Stack *stack) {
  Block *next = stack_get_next(stack, STACK_NEXT_CONTINUE);
  stack_instruction_br(stack, next);
}
static void stack_break_statement(Stack *stack) {
  Block *next = stack_get_next(stack, STACK_NEXT_BREAK);
  if (!next) {
    next = stack_new_block(stack);
    stack_set_next(stack, STACK_NEXT_BREAK, next);
  }
  stack_instruction_br(stack, next);
}
static void stack_return_statement(Stack *stack, Sexp *ast) {
  Block *ret = stack_get_next(stack, STACK_NEXT_RETURN);
  assert(!sexp_is_nil(sexp_at(ast, 2)));
  {
    Value *src = stack_ast(stack, sexp_at(ast, 2));
    if (ret) {
      Value *dst = stack_find_alloca(stack, "$retval");
      stack_instruction_store(stack, src, dst);
      stack_instruction_br(stack, ret);
    } else {
      stack_instruction_ret(stack, src);
    }
  }
}
Value *stack_jump_statement(Stack *stack, Sexp *ast) {
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_GOTO:
    stack_goto_statement(stack, ast);
    break;
  case AST_CONTINUE:
    stack_continue_statement(stack);
    break;
  case AST_BREAK:
    stack_break_statement(stack);
    break;
  case AST_RETURN:
    stack_return_statement(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
  stack_set_next(stack, STACK_NEXT_BLOCK, NULL);
  return NULL;
}
