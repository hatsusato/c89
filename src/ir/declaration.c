#include "ir/declaration.h"

#include "ast/ast_tag.h"
#include "ir/builder_impl.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

void builder_declaration(Builder *builder, Sexp *ast) {
  assert(AST_DECLARATION == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  assert(AST_INIT_DECLARATOR_LIST == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  builder_stack_push(builder, VALUE_INSTRUCTION_ALLOCA, NULL);
  builder_stack_init(builder, ast);
  builder_stack_pop(builder);
}
