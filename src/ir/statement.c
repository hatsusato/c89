#include "ir/statement.h"

#include "ast/ast_tag.h"
#include "ir/builder_impl.h"
#include "ir/instruction.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

void builder_statement(Builder *builder, Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 1));
}
void builder_compound_statement(Builder *builder, Sexp *ast) {
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 2));
  builder_ast(builder, sexp_at(ast, 3));
  if (!builder_stack_empty(builder)) {
    assert(VALUE_BLOCK == builder_stack_top_kind(builder));
    builder_instruction_br(builder);
  }
}
void builder_expression_statement(Builder *builder, Sexp *ast) {
  assert(AST_EXPRESSION_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  if (!sexp_is_nil(ast)) {
    builder_ast(builder, ast);
    builder_stack_pop(builder);
  }
}
static void builder_new_integer_constant(Builder *builder,
                                         const char *integer) {
  builder_stack_new_value(builder, VALUE_INTEGER_CONSTANT);
  builder_stack_set_symbol(builder, integer);
}
static void builder_br_cond(Builder *builder, Sexp *ast) {
  builder_ast(builder, ast);
  builder_new_integer_constant(builder, "0");
  builder_instruction_icmp_ne(builder);
  builder_stack_new_value(builder, VALUE_BLOCK);
  builder_stack_new_value(builder, VALUE_BLOCK);
  builder_instruction_br_cond(builder);
  builder_stack_swap(builder);
}
void builder_selection_statement(Builder *builder, Sexp *ast) {
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(AST_IF == sexp_get_number(sexp_at(ast, 1)));
  switch (sexp_length(ast)) {
  case 6:
    builder_br_cond(builder, sexp_at(ast, 3));
    builder_stack_pop_block(builder);
    builder_ast(builder, sexp_at(ast, 5));
    builder_stack_pop_block(builder);
    break;
  case 8:
    builder_br_cond(builder, sexp_at(ast, 3));
    builder_stack_pop_block(builder);
    builder_stack_new_value(builder, VALUE_BLOCK);
    builder_ast(builder, sexp_at(ast, 5));
    builder_stack_swap(builder);
    builder_stack_pop_block(builder);
    builder_ast(builder, sexp_at(ast, 7));
    builder_stack_pop_block(builder);
    break;
  default:
    assert(0);
    break;
  }
}
void builder_jump_statement(Builder *builder, Sexp *ast) {
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  assert(!sexp_is_nil(ast));
  builder_ast(builder, ast);
  builder_instruction_ret(builder);
}
