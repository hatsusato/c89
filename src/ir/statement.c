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
static Bool has_break_statement(Sexp *ast) {
  Sexp *head;
  assert(AST_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  switch (sexp_get_tag(ast)) {
  case AST_LABELED_STATEMENT:
    head = sexp_at(ast, 1);
    if (sexp_is_number(head) && AST_CASE == sexp_get_number(head)) {
      return has_break_statement(sexp_at(ast, 4));
    } else {
      assert(sexp_is_number(head) || AST_IDENTIFIER == sexp_get_tag(head));
      assert(!sexp_is_number(head) || AST_DEFAULT == sexp_get_number(head));
      return has_break_statement(sexp_at(ast, 3));
    }
  case AST_COMPOUND_STATEMENT:
    ast = sexp_at(ast, 3);
    assert(AST_STATEMENT_LIST == sexp_get_tag(ast));
    for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
      if (has_break_statement(sexp_car(ast))) {
        return true;
      }
    }
    return false;
  case AST_SELECTION_STATEMENT:
    head = sexp_at(ast, 1);
    assert(sexp_is_number(head));
    if (AST_IF == sexp_get_number(head)) {
      if (6 == sexp_length(ast)) {
        return has_break_statement(sexp_at(ast, 5));
      } else {
        assert(8 == sexp_length(ast));
        return has_break_statement(sexp_at(ast, 5)) ||
               has_break_statement(sexp_at(ast, 7));
      }
    } else {
      assert(AST_SWITCH == sexp_get_number(head));
      return false;
    }
  case AST_JUMP_STATEMENT:
    head = sexp_at(ast, 1);
    assert(sexp_is_number(head));
    return AST_BREAK == sexp_get_number(head);
  default:
    return false;
  }
}
static Bool switch_exists_next(Sexp *ast) {
  if (!switch_has_default(ast)) {
    return true;
  }
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  assert(AST_SWITCH == sexp_get_number(sexp_at(ast, 1)));
  ast = sexp_at(ast, 5);
  assert(AST_STATEMENT == sexp_get_tag(ast));
  return has_break_statement(ast);
}
static Bool switch_new_case(Stack *stack) {
  Value *curr = stack_get_current_block(stack);
  Value *dflt = stack_get_default_block(stack);
  Value *top = stack_get_switch_instruction(stack);
  assert(top);
  return 2 == value_length(top) || value_length(curr) || dflt == curr;
}

void stack_statement(Stack *stack, Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 1));
}
static void stack_default_statement(Stack *stack, Sexp *ast) {
  Value *next = stack_get_default_block(stack);
  stack_instruction_br(stack, next);
  stack_into_next_block(stack, next);
  stack_ast(stack, sexp_at(ast, 3));
}
static void stack_case_statement(Stack *stack, Sexp *ast) {
  Value *curr = stack_get_current_block(stack);
  Value *next = curr;
  if (switch_new_case(stack)) {
    next = stack_new_block(stack);
    stack_instruction_br(stack, next);
    stack_into_next_block(stack, next);
  }
  stack_ast(stack, sexp_at(ast, 2));
  stack_instruction_switch_case(stack, next);
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
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 2));
  stack_ast(stack, sexp_at(ast, 3));
  stack_instruction_br(stack, NULL);
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
  stack_instruction_br_cond(stack, if_then, if_else);
  stack_into_next_block(stack, if_then);
  stack_set_next_block(stack, next);
  stack_ast(stack, sexp_at(ast, 5));
  if (8 == sexp_length(ast)) {
    stack_into_next_block(stack, if_else);
    stack_set_next_block(stack, next);
    stack_ast(stack, sexp_at(ast, 7));
  }
  stack_into_next_block(stack, next);
  stack_set_next_block(stack, prev);
}
static void stack_switch_statement(Stack *stack, Sexp *ast) {
  Value *prev = stack_get_next_block(stack);
  Value *next = stack_new_block(stack);
  Value *dflt = switch_has_default(ast) ? stack_new_block(stack) : next;
  stack_set_next_block(stack, next);
  stack_ast(stack, sexp_at(ast, 3));
  stack_instruction_switch(stack, dflt);
  stack_ast(stack, sexp_at(ast, 5));
  stack_pop(stack);
  if (switch_exists_next(ast)) {
    stack_into_next_block(stack, next);
    stack_set_next_block(stack, prev);
  }
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
static void stack_while_statement(Stack *stack, Sexp *ast) {
  Value *guard = stack_new_block(stack);
  Value *body = stack_new_block(stack);
  Value *next = stack_new_block(stack);
  Value *prev = stack_get_next_block(stack);
  stack_instruction_br(stack, guard);
  stack_into_next_block(stack, guard);
  stack_ast(stack, sexp_at(ast, 3));
  stack_push_integer(stack, "0");
  stack_instruction_icmp_ne(stack);
  stack_instruction_br_cond(stack, body, next);
  stack_into_next_block(stack, body);
  stack_set_next_block(stack, guard);
  stack_ast(stack, sexp_at(ast, 5));
  stack_into_next_block(stack, next);
  stack_set_next_block(stack, prev);
}
void stack_iteration_statement(Stack *stack, Sexp *ast) {
  assert(AST_ITERATION_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  switch (sexp_get_number(sexp_at(ast, 1))) {
  case AST_WHILE:
    stack_while_statement(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
  UTILITY_UNUSED(stack);
}
static void stack_break_statement(Stack *stack, Sexp *ast) {
  stack_instruction_br(stack, NULL);
  UTILITY_UNUSED(ast);
}
static void stack_return_statement(Stack *stack, Sexp *ast) {
  Value *ret = stack_get_return_block(stack);
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
