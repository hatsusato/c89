#include "common.h"

static void builder_body_statement(Builder *builder, Sexp *ast,
                                   Block *next_break, Block *next_cont) {
  Block *prev_break = builder_set_next(builder, BUILDER_NEXT_BREAK, next_break);
  Block *prev_cont =
      builder_set_next(builder, BUILDER_NEXT_CONTINUE, next_cont);
  builder_ast(builder, ast);
  builder_set_next(builder, BUILDER_NEXT_BREAK, prev_break);
  builder_set_next(builder, BUILDER_NEXT_CONTINUE, prev_cont);
  builder_instruction_br(builder, next_cont);
}

static void builder_while_statement(Builder *builder, Sexp *ast) {
  Block *guard = builder_new_block(builder);
  Block *body = builder_new_block(builder);
  Block *next = builder_new_block(builder);
  builder_instruction_br(builder, guard);
  builder_jump_block(builder, guard);
  builder_guard_statement(builder, sexp_at(ast, 3), body, next);
  builder_jump_block(builder, body);
  builder_body_statement(builder, sexp_at(ast, 5), next, guard);
  builder_jump_block(builder, next);
}
static void builder_do_while_statement(Builder *builder, Sexp *ast) {
  Block *body = builder_new_block(builder);
  Block *guard = builder_new_block(builder);
  Block *next = builder_new_block(builder);
  builder_instruction_br(builder, body);
  builder_jump_block(builder, body);
  builder_body_statement(builder, sexp_at(ast, 2), next, guard);
  builder_jump_block(builder, guard);
  builder_guard_statement(builder, sexp_at(ast, 5), body, next);
  builder_jump_block(builder, next);
}
static Block *builder_for_guard_statement(Builder *builder, Sexp *ast,
                                          Block *body, Block *next) {
  if (sexp_is_nil(ast)) {
    builder_instruction_br(builder, body);
    return body;
  } else {
    Block *guard = builder_new_block(builder);
    builder_instruction_br(builder, guard);
    builder_jump_block(builder, guard);
    builder_guard_statement(builder, ast, body, next);
    return guard;
  }
}
static void builder_for_statement(Builder *builder, Sexp *ast) {
  Block *guard, *step;
  Block *body = builder_new_block(builder);
  Block *next = builder_new_block(builder);
  builder_ast(builder, sexp_at(ast, 3));
  guard = builder_for_guard_statement(builder, sexp_at(ast, 5), body, next);
  step = sexp_is_nil(sexp_at(ast, 7)) ? guard : builder_new_block(builder);
  builder_jump_block(builder, body);
  builder_body_statement(builder, sexp_at(ast, 9), next, step);
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
