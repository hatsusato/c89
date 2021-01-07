#include "labeled.h"

#include "common.h"

static Bool switch_new_case(Builder *builder) {
  Block *curr = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Block *dflt = builder_get_next(builder, BUILDER_NEXT_DEFAULT);
  Block *swch = builder_get_next(builder, BUILDER_NEXT_SWITCH);
  return block_empty(swch) || !block_empty(curr) || dflt == curr;
}

static void builder_label_statement(Builder *builder, Sexp *ast) {
  const char *label = identifier_symbol(sexp_at(ast, 1));
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
  builder_set_type_int(builder);
  builder_ast(builder, sexp_at(ast, 2));
  value = builder_get_value(builder);
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

void builder_labeled_statement(Builder *builder, Sexp *ast) {
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
}
