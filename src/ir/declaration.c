#include "ir/declaration.h"

#include "ast/ast_tag.h"
#include "ir/builder_impl.h"
#include "ir/instruction.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

static void builder_declarator(Builder *, Sexp *);
static void builder_direct_declarator(Builder *builder, Sexp *ast) {
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    ast = sexp_at(ast, 1);
    assert(AST_IDENTIFIER == sexp_get_tag(ast));
    ast = sexp_at(ast, 1);
    assert(sexp_get_symbol(ast));
    builder_instruction_alloca(builder, sexp_get_symbol(ast));
    break;
  case 4:
    ast = sexp_at(ast, 2);
    builder_declarator(builder, ast);
    break;
  case 5:
    ast = sexp_at(ast, 1);
    builder_direct_declarator(builder, ast);
    break;
  default:
    assert(0);
    break;
  }
}
static void builder_declarator(Builder *builder, Sexp *ast) {
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  assert(2 == sexp_length(ast) || 3 == sexp_length(ast));
  ast = sexp_at(ast, sexp_length(ast) - 1);
  builder_direct_declarator(builder, ast);
}
static void builder_init_declarator(Builder *builder, Sexp *ast) {
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  if (4 == sexp_length(ast)) {
    builder_declarator(builder, sexp_at(ast, 1));
    builder_ast(builder, sexp_at(ast, 3));
    builder_stack_swap(builder);
    builder_instruction_store(builder);
    builder_stack_pop(builder);
  } else {
    builder_declarator(builder, sexp_at(ast, 1));
    builder_stack_pop(builder);
  }
}
void builder_declaration(Builder *builder, Sexp *ast) {
  assert(AST_DECLARATION == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  assert(AST_INIT_DECLARATOR_LIST == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  builder_init_declarator(builder, ast);
}
