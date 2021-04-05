#include "statement.h"

#include "ast/get.h"
#include "ast/tag.h"
#include "builder/builder.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

void builder_compound_statement(Builder *builder, Sexp *ast) {
  builder_push_table(builder);
  builder_ast_list(builder, ast_get_declaration_list(ast));
  builder_ast(builder, ast_get_statement_list(ast));
  builder_pop_table(builder);
}
void builder_statement_list(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(SYNTAX_STATEMENT_LIST == sexp_get_tag(ast));
  builder_ast_map(builder, ast);
}
void builder_expression_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(SYNTAX_EXPRESSION_STATEMENT == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 1));
}
