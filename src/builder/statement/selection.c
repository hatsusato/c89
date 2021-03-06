#include "selection.h"

#include "common.h"

static void builder_branch(Builder *builder, Sexp *ast, Block *current,
                           Block *next) {
  builder_jump_block(builder, current);
  builder_ast(builder, ast);
  builder_instruction_br(builder, next);
}

static void builder_if_statement(Builder *builder, Sexp *ast) {
  Module *module = builder_get_module(builder);
  Block *next = block_new(module);
  Block *then_block = block_new(module);
  builder_guard_statement(builder, sexp_at(ast, 3), then_block, next);
  builder_branch(builder, sexp_at(ast, 5), then_block, next);
  builder_jump_block(builder, next);
}
static void builder_if_else_statement(Builder *builder, Sexp *ast) {
  Module *module = builder_get_module(builder);
  Block *next = block_new(module);
  Block *then_block = block_new(module);
  Block *else_block = block_new(module);
  Block *prev, *then_next, *else_next;
  builder_guard_statement(builder, sexp_at(ast, 3), then_block, else_block);
  prev = builder_set_next(builder, BUILDER_NEXT_BLOCK, next);
  builder_branch(builder, sexp_at(ast, 5), then_block, next);
  then_next = builder_set_next(builder, BUILDER_NEXT_BLOCK, next);
  builder_branch(builder, sexp_at(ast, 7), else_block, next);
  else_next = builder_set_next(builder, BUILDER_NEXT_BLOCK, prev);
  if (then_next || else_next) {
    builder_jump_block(builder, next);
  }
}
static void builder_switch_body(Builder *builder, Sexp *ast, Value *instr) {
  Module *module = builder_get_module(builder);
  Block *block = block_new(module);
  Block *next_break = builder_set_next(builder, BUILDER_NEXT_BREAK, NULL);
  Block *next_default = builder_set_next(builder, BUILDER_NEXT_DEFAULT, NULL);
  Block *next_switch = builder_set_next(builder, BUILDER_NEXT_SWITCH, block);
  builder_ast(builder, ast);
  builder_instruction_switch_finish(builder, instr);
  builder_set_next(builder, BUILDER_NEXT_BREAK, next_break);
  builder_set_next(builder, BUILDER_NEXT_DEFAULT, next_default);
  builder_set_next(builder, BUILDER_NEXT_SWITCH, next_switch);
}
static void builder_switch_statement(Builder *builder, Sexp *ast) {
  Value *value;
  builder_set_type_int(builder);
  builder_ast(builder, sexp_at(ast, 3));
  value = builder_get_value(builder);
  builder_instruction_switch(builder, value);
  value = builder_get_value(builder);
  builder_switch_body(builder, sexp_at(ast, 5), value);
}

void builder_selection_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(SYNTAX_SELECTION_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case SYNTAX_IF:
    if (6 == sexp_length(ast)) {
      builder_if_statement(builder, ast);
    } else {
      UTILITY_ASSERT(8 == sexp_length(ast));
      builder_if_else_statement(builder, ast);
    }
    break;
  case SYNTAX_SWITCH:
    builder_switch_statement(builder, ast);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
}
