#include "declaration.h"

#include "ast/tag.h"
#include "builder.h"
#include "global.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"

void builder_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATION == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 2));
}
void builder_init_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  UTILITY_ASSERT(2 == sexp_length(ast) || 4 == sexp_length(ast));
  builder_declarator(builder, sexp_at(ast, 1));
  if (4 == sexp_length(ast)) {
    Value *dst = builder_get_value(builder), *src;
    builder_ast(builder, sexp_at(ast, 3));
    src = builder_get_value(builder);
    if (builder_is_local(builder)) {
      builder_instruction_store(builder, src, dst);
    } else {
      builder_init_global(builder, dst, src);
    }
  }
}
void builder_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATOR == sexp_get_tag(ast));
  if (2 == sexp_length(ast)) {
    builder_direct_declarator(builder, sexp_at(ast, 1));
  } else {
    UTILITY_ASSERT(3 == sexp_length(ast));
    UTILITY_ASSERT(builder_is_local(builder));
    builder_direct_declarator(builder, sexp_at(ast, 2));
  }
}
void builder_direct_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  if (2 == sexp_length(ast)) {
    if (builder_is_local(builder)) {
      builder_instruction_alloca(builder, sexp_at(ast, 1));
    } else {
      builder_new_global(builder, sexp_at(ast, 1));
    }
  } else {
    UTILITY_ASSERT(4 == sexp_length(ast));
    UTILITY_ASSERT(builder_is_local(builder));
    builder_declarator(builder, sexp_at(ast, 2));
  }
}
