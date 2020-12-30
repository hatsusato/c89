#include "statement.h"

#include "ast/tag.h"
#include "block.h"
#include "builder.h"
#include "constant.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"

void builder_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STATEMENT == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 1));
}
void builder_compound_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  builder_push_table(builder);
  builder_ast(builder, sexp_at(ast, 2));
  builder_ast(builder, sexp_at(ast, 3));
  builder_pop_table(builder);
}
void builder_expression_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EXPRESSION_STATEMENT == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 1));
}
