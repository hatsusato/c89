#include "common.h"

static void builder_while_statement(Builder *builder, Sexp *ast) {
  Block *guard = builder_new_block(builder);
  Block *body = builder_new_block(builder);
  Block *next = builder_new_block(builder);
  builder_instruction_br(builder, guard);
  builder_jump_block(builder, guard);
  builder_guard_statement(builder, sexp_at(ast, 3), body, next);
  {
    Block *next_break = builder_set_next(builder, BUILDER_NEXT_BREAK, next);
    Block *next_continue =
        builder_set_next(builder, BUILDER_NEXT_CONTINUE, guard);
    builder_jump_block(builder, body);
    builder_ast(builder, sexp_at(ast, 5));
    builder_instruction_br(builder, guard);
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
    builder_jump_block(builder, body);
    builder_ast(builder, sexp_at(ast, 2));
    builder_instruction_br(builder, guard);
    builder_set_next(builder, BUILDER_NEXT_BREAK, next_break);
    builder_set_next(builder, BUILDER_NEXT_CONTINUE, next_continue);
  }
  builder_jump_block(builder, guard);
  builder_guard_statement(builder, sexp_at(ast, 5), body, next);
  builder_jump_block(builder, next);
}
static void builder_for_statement(Builder *builder, Sexp *ast) {
  Block *guard, *step;
  Block *body = builder_new_block(builder);
  Block *next = builder_new_block(builder);
  builder_ast(builder, sexp_at(ast, 3));
  guard = sexp_is_nil(sexp_at(ast, 5)) ? body : builder_new_block(builder);
  builder_instruction_br(builder, guard);
  if (!sexp_is_nil(sexp_at(ast, 5))) {
    builder_jump_block(builder, guard);
    UTILITY_ASSERT(sexp_at(ast, 5));
    builder_guard_statement(builder, sexp_at(ast, 5), body, next);
  }
  step = sexp_is_nil(sexp_at(ast, 7)) ? guard : builder_new_block(builder);
  {
    Block *next_break = builder_set_next(builder, BUILDER_NEXT_BREAK, next);
    Block *next_continue =
        builder_set_next(builder, BUILDER_NEXT_CONTINUE, step);
    builder_jump_block(builder, body);
    builder_ast(builder, sexp_at(ast, 9));
    builder_instruction_br(builder, step);
    builder_set_next(builder, BUILDER_NEXT_BREAK, next_break);
    builder_set_next(builder, BUILDER_NEXT_CONTINUE, next_continue);
  }
  if (!sexp_is_nil(sexp_at(ast, 7))) {
    builder_jump_block(builder, step);
    builder_ast(builder, sexp_at(ast, 7));
    builder_instruction_br(builder, guard);
  }
  builder_jump_block(builder, next);
}

void builder_iteration_statement(Builder *builder, Sexp *ast) {
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
}
