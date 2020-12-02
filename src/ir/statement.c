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
  Value *next;
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 2));
  builder_ast(builder, sexp_at(ast, 3));
  next = builder_stack_get_next_block(builder);
  if (next) {
    builder_stack_push(builder, next);
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
void builder_selection_statement(Builder *builder, Sexp *ast) {
  Value *if_then = builder_stack_new_block(builder);
  Value *if_else = builder_stack_new_block(builder);
  Value *prev = builder_stack_get_next_block(builder);
  Value *next;
  assert(AST_SELECTION_STATEMENT == sexp_get_tag(ast));
  assert(AST_IF == sexp_get_number(sexp_at(ast, 1)));
  switch (sexp_length(ast)) {
  case 6:
    builder_ast(builder, sexp_at(ast, 3));
    builder_new_integer_constant(builder, "0");
    builder_instruction_icmp_ne(builder);
    builder_stack_push(builder, if_then);
    builder_stack_push(builder, if_else);
    builder_instruction_br_cond(builder);
    builder_stack_set_current_block(builder, if_then);
    builder_stack_set_next_block(builder, if_else);
    builder_stack_push(builder, if_else);
    builder_ast(builder, sexp_at(ast, 5));
    builder_stack_pop(builder);
    builder_stack_set_current_block(builder, if_else);
    builder_stack_set_next_block(builder, prev);
    break;
  case 8:
    next = builder_stack_new_block(builder);
    builder_ast(builder, sexp_at(ast, 3));
    builder_new_integer_constant(builder, "0");
    builder_instruction_icmp_ne(builder);
    builder_stack_push(builder, if_then);
    builder_stack_push(builder, if_else);
    builder_instruction_br_cond(builder);
    builder_stack_set_current_block(builder, if_then);
    builder_stack_set_next_block(builder, next);
    builder_stack_push(builder, next);
    builder_ast(builder, sexp_at(ast, 5));
    builder_stack_pop(builder);
    builder_stack_set_current_block(builder, if_else);
    builder_stack_set_next_block(builder, next);
    builder_stack_push(builder, next);
    builder_ast(builder, sexp_at(ast, 7));
    builder_stack_pop(builder);
    builder_stack_set_current_block(builder, next);
    builder_stack_set_next_block(builder, prev);
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
  if (builder_multiple_return(builder)) {
    builder_ast(builder, ast);
    builder_stack_push_symbol(builder, "$retval");
    builder_instruction_store(builder);
    builder_stack_pop(builder);
  } else {
    builder_ast(builder, ast);
    builder_instruction_ret(builder);
  }
  builder_stack_set_next_block(builder, NULL);
}
