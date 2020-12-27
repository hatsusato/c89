#include "expression.h"

#include "ast/tag.h"
#include "builder.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

void builder_additive_expression(Builder *builder, Sexp *ast) {
  Value *lhs, *rhs;
  builder_ast(builder, sexp_at(ast, 1));
  lhs = builder_get_value(builder);
  builder_ast(builder, sexp_at(ast, 3));
  rhs = builder_get_value(builder);
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
void builder_constant_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 1));
}
