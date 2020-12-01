#include "ir/statement.h"

#include "ast/ast_tag.h"
#include "ir/builder_impl.h"
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
    Value *next = builder_stack_top(builder);
    assert(VALUE_BLOCK == value_kind(next));
    builder_stack_push(builder, VALUE_INSTRUCTION_BR);
    builder_stack_push_block(builder, next);
    builder_stack_pop_insert(builder);
    builder_stack_pop(builder);
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
static void builder_icmp_ne_zero(Builder *builder, Sexp *ast) {
  Sexp *zero = sexp_pair(sexp_symbol("0"), sexp_nil());
  zero = sexp_pair(sexp_number(AST_INTEGER_CONSTANT), zero);
  builder_stack_push(builder, VALUE_INSTRUCTION_ICMP_NE);
  builder_ast(builder, ast);
  builder_stack_pop_insert(builder);
  builder_stack_push(builder, VALUE_INTEGER_CONSTANT);
  builder_stack_init(builder, zero);
  builder_stack_pop_insert(builder);
  sexp_delete(zero);
}
void builder_selection_statement(Builder *builder, Sexp *ast) {
  Value *then, *next;
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 1)));
  assert(AST_IF == sexp_get_number(sexp_at(ast, 1)));
  assert(6 == sexp_length(ast));
  {
    builder_stack_push(builder, VALUE_INSTRUCTION_BR_COND);
    builder_icmp_ne_zero(builder, sexp_at(ast, 3));
    builder_stack_pop_insert(builder);
    builder_stack_push(builder, VALUE_BLOCK);
    then = builder_stack_pop_insert(builder);
    builder_stack_push(builder, VALUE_BLOCK);
    next = builder_stack_pop_insert(builder);
    builder_stack_pop(builder);
  }
  {
    builder_stack_push_block(builder, then);
    builder_block_pop_set(builder);
    builder_stack_push_block(builder, next);
    builder_ast(builder, sexp_at(ast, 5));
    assert(builder_stack_top(builder) == next);
    builder_block_pop_set(builder);
  }
}
void builder_jump_statement(Builder *builder, Sexp *ast) {
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  builder_stack_push(builder, VALUE_INSTRUCTION_RET);
  if (!sexp_is_nil(ast)) {
    builder_ast(builder, ast);
    builder_stack_pop_insert(builder);
  }
  builder_stack_pop(builder);
}
