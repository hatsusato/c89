#include "expression.h"

#include "ast/tag.h"
#include "builder.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

Value *builder_additive_expression(Builder *builder, Sexp *ast) {
  Value *lhs = builder_ast(builder, sexp_at(ast, 1));
  Value *rhs = builder_ast(builder, sexp_at(ast, 3));
  UTILITY_ASSERT(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
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
  return builder_get_value(builder);
}
Value *builder_assignment_expression(Builder *builder, Sexp *ast) {
  Value *lhs = builder_find_identifier(builder, sexp_at(ast, 1));
  Value *rhs = builder_ast(builder, sexp_at(ast, 3));
  UTILITY_ASSERT(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  UTILITY_ASSERT(AST_ASSIGN == sexp_get_tag(sexp_at(ast, 2)));
  builder_instruction_store(builder, rhs, lhs);
  return builder_get_value(builder);
}
Value *builder_constant_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  return builder_ast(builder, sexp_at(ast, 1));
}
