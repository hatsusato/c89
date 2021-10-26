#include "labeled.h"

#include "ast/get.h"
#include "common.h"

static Bool switch_new_case(Builder *builder) {
  Block *curr = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Block *dflt = builder_get_next(builder, BUILDER_NEXT_DEFAULT);
  Block *swch = builder_get_next(builder, BUILDER_NEXT_SWITCH);
  return block_empty(swch) || !block_empty(curr) || dflt == curr;
}

void builder_goto_label(Builder *builder, Sexp *ast) {
  const char *label = sexp_get_symbol(ast_get_label_goto(ast));
  Block *next = builder_label(builder, label);
  builder_instruction_br(builder, next);
  builder_jump_block(builder, next);
  builder_ast(builder, ast_get_label_statement(ast));
}
void builder_case_label(Builder *builder, Sexp *ast) {
  Module *module = builder_get_module(builder);
  Block *next = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Value *value;
  if (switch_new_case(builder)) {
    next = block_new(module);
    builder_instruction_br(builder, next);
    builder_jump_block(builder, next);
  }
  builder_set_type_int(builder);
  builder_ast(builder, ast_get_label_case(ast));
  value = builder_get_value(builder);
  builder_instruction_switch_case(builder, value, next);
  builder_ast(builder, ast_get_label_statement(ast));
}
void builder_default_label(Builder *builder, Sexp *ast) {
  Module *module = builder_get_module(builder);
  Block *next = block_new(module);
  Block *prev_default = builder_set_next(builder, BUILDER_NEXT_DEFAULT, next);
  UTILITY_ASSERT(!prev_default);
  builder_instruction_br(builder, next);
  builder_jump_block(builder, next);
  builder_ast(builder, ast_get_label_statement(ast));
}
