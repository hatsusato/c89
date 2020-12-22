#include "ir/statement.h"

#include "ast/ast_tag.h"
#include "ir/block.h"
#include "ir/builder.h"
#include "ir/constant.h"
#include "ir/instruction.h"
#include "ir/instruction_type.h"
#include "ir/lexical.h"
#include "ir/value.h"
#include "sexp.h"
#include "utility.h"

static Bool switch_new_case(Builder *builder) {
  Block *curr = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Block *dflt = builder_get_next(builder, BUILDER_NEXT_DEFAULT);
  Block *swch = builder_get_next(builder, BUILDER_NEXT_SWITCH);
  return block_empty(swch) || !block_empty(curr) || dflt == curr;
}
static void builder_guard(Builder *builder, Sexp *expr, Block *then_block,
                          Block *else_block) {
  Value *lhs = builder_ast(builder, expr);
  Constant *rhs = builder_new_integer(builder, "0");
  Instruction *icmp =
      builder_instruction_icmp_ne(builder, lhs, constant_as_value(rhs));
  builder_instruction_br_cond(builder, instruction_as_value(icmp), then_block,
                              else_block);
}
static void builder_branch(Builder *builder, Sexp *ast, Block *current,
                           Block *next) {
  builder_jump_block(builder, current);
  builder_ast(builder, ast);
  builder_instruction_br(builder, next);
}
static void builder_label_statement(Builder *builder, Sexp *ast) {
  const char *label = builder_identifier_symbol(sexp_at(ast, 1));
  Block *next = builder_label(builder, label);
  builder_instruction_br(builder, next);
  builder_jump_block(builder, next);
  builder_ast(builder, sexp_at(ast, 3));
}
static void builder_case_statement(Builder *builder, Sexp *ast) {
  Block *next = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Value *value;
  if (switch_new_case(builder)) {
    next = builder_new_block(builder);
    builder_instruction_br(builder, next);
    builder_jump_block(builder, next);
  }
  value = builder_ast(builder, sexp_at(ast, 2));
  builder_instruction_switch_case(builder, value, next);
  builder_ast(builder, sexp_at(ast, 4));
}
static void builder_default_statement(Builder *builder, Sexp *ast) {
  Block *next = builder_new_block(builder);
  Block *prev_default = builder_set_next(builder, BUILDER_NEXT_DEFAULT, next);
  UTILITY_ASSERT(!prev_default);
  builder_instruction_br(builder, next);
  builder_jump_block(builder, next);
  builder_ast(builder, sexp_at(ast, 3));
}
static void builder_if_statement(Builder *builder, Sexp *ast) {
  Block *next = builder_new_block(builder);
  Block *then_block = builder_new_block(builder);
  builder_guard(builder, sexp_at(ast, 3), then_block, next);
  builder_branch(builder, sexp_at(ast, 5), then_block, next);
  builder_jump_block(builder, next);
}
static void builder_if_else_statement(Builder *builder, Sexp *ast) {
  Block *next = builder_new_block(builder);
  Block *then_block = builder_new_block(builder);
  Block *else_block = builder_new_block(builder);
  Block *prev, *then_next, *else_next;
  builder_guard(builder, sexp_at(ast, 3), then_block, else_block);
  prev = builder_set_next(builder, BUILDER_NEXT_BLOCK, next);
  builder_branch(builder, sexp_at(ast, 5), then_block, next);
  then_next = builder_set_next(builder, BUILDER_NEXT_BLOCK, next);
  builder_branch(builder, sexp_at(ast, 7), else_block, next);
  else_next = builder_set_next(builder, BUILDER_NEXT_BLOCK, prev);
  if (then_next || else_next) {
    builder_jump_block(builder, next);
  }
}
static void builder_switch_statement(Builder *builder, Sexp *ast) {
  Block *block = builder_new_block(builder);
  Value *expr = builder_ast(builder, sexp_at(ast, 3));
  Instruction *instr = builder_instruction_switch(builder, expr);
  {
    Block *next_break = builder_set_next(builder, BUILDER_NEXT_BREAK, NULL);
    Block *next_default = builder_set_next(builder, BUILDER_NEXT_DEFAULT, NULL);
    Block *next_switch = builder_set_next(builder, BUILDER_NEXT_SWITCH, block);
    builder_ast(builder, sexp_at(ast, 5));
    builder_instruction_switch_finish(builder, instr);
    builder_set_next(builder, BUILDER_NEXT_BREAK, next_break);
    builder_set_next(builder, BUILDER_NEXT_DEFAULT, next_default);
    builder_set_next(builder, BUILDER_NEXT_SWITCH, next_switch);
  }
}
static void builder_while_statement(Builder *builder, Sexp *ast) {
  Block *guard = builder_new_block(builder);
  Block *body = builder_new_block(builder);
  Block *next = builder_new_block(builder);
  builder_instruction_br(builder, guard);
  builder_jump_block(builder, guard);
  builder_guard(builder, sexp_at(ast, 3), body, next);
  {
    Block *next_break = builder_set_next(builder, BUILDER_NEXT_BREAK, next);
    Block *next_continue =
        builder_set_next(builder, BUILDER_NEXT_CONTINUE, guard);
    builder_branch(builder, sexp_at(ast, 5), body, guard);
    builder_set_next(builder, BUILDER_NEXT_BREAK, next_break);
    builder_set_next(builder, BUILDER_NEXT_CONTINUE, next_continue);
  }
  builder_jump_block(builder, next);
}
static void builder_do_while_statement(Builder *builder, Sexp *ast) {
  Block *body = builder_new_block(builder);
  Block *guard = builder_new_block(builder);
  Block *next = builder_new_block(builder);
  builder_instruction_br(builder, body);
  {
    Block *next_break = builder_set_next(builder, BUILDER_NEXT_BREAK, next);
    Block *next_continue =
        builder_set_next(builder, BUILDER_NEXT_CONTINUE, guard);
    builder_branch(builder, sexp_at(ast, 2), body, guard);
    builder_set_next(builder, BUILDER_NEXT_BREAK, next_break);
    builder_set_next(builder, BUILDER_NEXT_CONTINUE, next_continue);
  }
  builder_jump_block(builder, guard);
  builder_guard(builder, sexp_at(ast, 5), body, next);
  builder_jump_block(builder, next);
}
static void builder_for_statement(Builder *builder, Sexp *ast) {
  Block *guard, *step;
  Block *body = builder_new_block(builder);
  Block *next = builder_new_block(builder);
  if (!sexp_is_nil(sexp_at(ast, 3))) {
    builder_ast(builder, sexp_at(ast, 3));
  }
  guard = sexp_is_nil(sexp_at(ast, 5)) ? body : builder_new_block(builder);
  builder_instruction_br(builder, guard);
  if (!sexp_is_nil(sexp_at(ast, 5))) {
    builder_jump_block(builder, guard);
    UTILITY_ASSERT(sexp_at(ast, 5));
    builder_guard(builder, sexp_at(ast, 5), body, next);
  }
  step = sexp_is_nil(sexp_at(ast, 7)) ? guard : builder_new_block(builder);
  {
    Block *next_break = builder_set_next(builder, BUILDER_NEXT_BREAK, next);
    Block *next_continue =
        builder_set_next(builder, BUILDER_NEXT_CONTINUE, step);
    builder_branch(builder, sexp_at(ast, 9), body, step);
    builder_set_next(builder, BUILDER_NEXT_BREAK, next_break);
    builder_set_next(builder, BUILDER_NEXT_CONTINUE, next_continue);
  }
  if (!sexp_is_nil(sexp_at(ast, 7))) {
    builder_branch(builder, sexp_at(ast, 7), step, guard);
  }
  builder_jump_block(builder, next);
}
static void builder_goto_statement(Builder *builder, Sexp *ast) {
  const char *label = builder_identifier_symbol(sexp_at(ast, 2));
  Block *next = builder_label(builder, label);
  builder_instruction_br(builder, next);
}
static void builder_continue_statement(Builder *builder) {
  Block *next = builder_get_next(builder, BUILDER_NEXT_CONTINUE);
  builder_instruction_br(builder, next);
}
static void builder_break_statement(Builder *builder) {
  Block *next = builder_get_next(builder, BUILDER_NEXT_BREAK);
  if (!next) {
    next = builder_new_block(builder);
    builder_set_next(builder, BUILDER_NEXT_BREAK, next);
  }
  builder_instruction_br(builder, next);
}
static void builder_return_statement(Builder *builder, Sexp *ast) {
  Block *ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  Value *src;
  UTILITY_ASSERT(!sexp_is_nil(sexp_at(ast, 2)));
  src = builder_ast(builder, sexp_at(ast, 2));
  if (ret) {
    Value *dst = builder_find_alloca(builder, "$retval");
    builder_instruction_store(builder, src, dst);
    builder_instruction_br(builder, ret);
  } else {
    builder_instruction_ret(builder, src);
  }
}

Value *builder_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STATEMENT == sexp_get_tag(ast));
  return builder_ast(builder, sexp_at(ast, 1));
}
Value *builder_labeled_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_LABELED_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_IDENTIFIER:
    builder_label_statement(builder, ast);
    break;
  case AST_CASE:
    builder_case_statement(builder, ast);
    break;
  case AST_DEFAULT:
    builder_default_statement(builder, ast);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
  return NULL;
}
Value *builder_compound_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 2));
  builder_ast(builder, sexp_at(ast, 3));
  return NULL;
}
Value *builder_expression_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EXPRESSION_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  if (!sexp_is_nil(ast)) {
    builder_ast(builder, ast);
  }
  return NULL;
}
Value *builder_selection_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_IF:
    switch (sexp_length(ast)) {
    case 6:
      builder_if_statement(builder, ast);
      break;
    case 8:
      builder_if_else_statement(builder, ast);
      break;
    default:
      UTILITY_ASSERT(0);
      break;
    }
    break;
  case AST_SWITCH:
    builder_switch_statement(builder, ast);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
  return NULL;
}
Value *builder_iteration_statement(Builder *builder, Sexp *ast) {
  Block *next_switch = builder_set_next(builder, BUILDER_NEXT_SWITCH, NULL);
  UTILITY_ASSERT(AST_ITERATION_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_WHILE:
    builder_while_statement(builder, ast);
    break;
  case AST_DO:
    builder_do_while_statement(builder, ast);
    break;
  case AST_FOR:
    builder_for_statement(builder, ast);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
  builder_set_next(builder, BUILDER_NEXT_SWITCH, next_switch);
  return NULL;
}
Value *builder_jump_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_GOTO:
    builder_goto_statement(builder, ast);
    break;
  case AST_CONTINUE:
    builder_continue_statement(builder);
    break;
  case AST_BREAK:
    builder_break_statement(builder);
    break;
  case AST_RETURN:
    builder_return_statement(builder, ast);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
  builder_set_next(builder, BUILDER_NEXT_BLOCK, NULL);
  return NULL;
}
