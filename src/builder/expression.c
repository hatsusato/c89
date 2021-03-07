#include "expression.h"

#include "ast/tag.h"
#include "builder.h"
#include "instruction.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

void builder_primary_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_PRIMARY_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_postfix_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_POSTFIX_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_argument_expression_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_ARGUMENT_EXPRESSION_LIST == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_unary_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_UNARY_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_cast_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_CAST_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_multiplicative_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_MULTIPLICATIVE_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_additive_expression(Builder *builder, Sexp *ast) {
  Value *lhs, *rhs;
  UTILITY_ASSERT(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 1));
  lhs = builder_get_value(builder);
  builder_ast(builder, sexp_at(ast, 3));
  rhs = builder_get_value(builder);
  switch (sexp_get_tag(sexp_at(ast, 2))) {
  case AST_PLUS:
    builder_instruction_add(builder, lhs, rhs);
    break;
  case AST_MINUS:
    builder_instruction_sub(builder, lhs, rhs);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
}
void builder_shift_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_SHIFT_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_relational_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_RELATIONAL_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_equality_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EQUALITY_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_and_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_AND_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_exclusive_or_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EXCLUSIVE_OR_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_inclusive_or_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INCLUSIVE_OR_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_logical_and_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_LOGICAL_AND_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_logical_or_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_LOGICAL_OR_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_conditional_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_CONDITIONAL_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_assignment_expression(Builder *builder, Sexp *ast) {
  const char *symbol;
  Value *lhs, *rhs;
  UTILITY_ASSERT(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  UTILITY_ASSERT(AST_ASSIGN == sexp_get_tag(sexp_at(ast, 2)));
  symbol = identifier_symbol(sexp_at(ast, 1));
  builder_find_identifier(builder, symbol);
  lhs = builder_get_value(builder);
  builder_ast(builder, sexp_at(ast, 3));
  rhs = builder_get_value(builder);
  builder_instruction_store(builder, rhs, lhs);
}
void builder_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EXPRESSION == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_constant_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 1));
}
