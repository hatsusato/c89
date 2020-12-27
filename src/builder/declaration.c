#include "declaration.h"

#include "ast/tag.h"
#include "builder.h"
#include "global.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"

static Value *builder_declarator_initializer(Builder *builder, Sexp *ast) {
  Value *src, *dst;
  builder_ast(builder, sexp_at(ast, 3));
  src = builder_get_value(builder);
  builder_declarator(builder, sexp_at(ast, 1));
  dst = builder_get_value(builder);
  builder_instruction_store(builder, src, dst);
  return builder_get_value(builder);
}

void builder_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATION == sexp_get_tag(ast));
  builder_ast(builder, sexp_at(ast, 2));
}
void builder_init_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    builder_declarator(builder, sexp_at(ast, 1));
    break;
  case 4:
    builder_declarator_initializer(builder, ast);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
}
void builder_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    builder_direct_declarator(builder, sexp_at(ast, 1));
    break;
  case 3:
    builder_direct_declarator(builder, sexp_at(ast, 2));
    break;
  default:
    UTILITY_ASSERT(0);
    break;
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
