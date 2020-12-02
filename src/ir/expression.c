#include "ir/expression.h"

#include "ast/ast_tag.h"
#include "ir/builder_impl.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

void builder_additive_expression(Builder *builder, Sexp *ast) {
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 2)));
  assert(AST_PLUS == sexp_get_number(sexp_at(ast, 2)));
  builder_stack_new_value(builder, VALUE_INSTRUCTION_ADD);
  builder_ast(builder, sexp_at(ast, 1));
  builder_stack_pop_insert(builder);
  builder_ast(builder, sexp_at(ast, 3));
  builder_stack_pop_insert(builder);
  builder_stack_register(builder);
}
void builder_assignment_expression(Builder *builder, Sexp *ast) {
  Sexp *lhs, *op, *rhs;
  assert(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  lhs = sexp_at(ast, 1);
  op = sexp_at(ast, 2);
  rhs = sexp_at(ast, 3);
  assert(AST_IDENTIFIER == sexp_get_tag(lhs));
  assert(sexp_is_number(op) && AST_ASSIGN == sexp_get_number(op));
  lhs = sexp_at(lhs, 1);
  assert(sexp_is_symbol(lhs));
  builder_stack_new_value(builder, VALUE_INSTRUCTION_STORE);
  builder_ast(builder, rhs);
  builder_stack_pop_insert(builder);
  builder_stack_push_symbol(builder, sexp_get_symbol(lhs));
  builder_stack_pop_insert(builder);
  builder_stack_register(builder);
}
