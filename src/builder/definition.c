#include "definition.h"

#include "ast/tag.h"
#include "builder.h"
#include "function.h"
#include "instruction.h"
#include "sexp.h"
#include "type.h"
#include "utility.h"

static const char *function_name(Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    return identifier_symbol(ast);
  case AST_DECLARATOR:
    switch (sexp_length(ast)) {
    case 2:
      return function_name(sexp_at(ast, 1));
    case 3:
      return function_name(sexp_at(ast, 2));
    default:
      UTILITY_ASSERT(0);
      return NULL;
    }
  case AST_DIRECT_DECLARATOR:
    switch (sexp_length(ast)) {
    case 2:
      return function_name(sexp_at(ast, 1));
    case 4:
      return function_name(sexp_at(ast, 2));
    case 5:
      return function_name(sexp_at(ast, 1));
    default:
      UTILITY_ASSERT(0);
      return NULL;
    }
  case AST_FUNCTION_DEFINITION:
    UTILITY_ASSERT(5 == sexp_length(ast));
    return function_name(sexp_at(ast, 2));
  default:
    UTILITY_ASSERT(0);
    return NULL;
  }
}
static Type *builder_function_type(Builder *builder, Sexp *ast) {
  if (4 == sexp_length(ast)) {
    return builder_type_integer(builder, 32);
  } else {
    UTILITY_ASSERT(5 == sexp_length(ast));
    builder_ast(builder, sexp_at(ast, 1));
    return builder_get_type(builder);
  }
}

void builder_translation_unit(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_TRANSLATION_UNIT == sexp_get_tag(ast));
  builder_ast_map(builder, ast);
}
void builder_external_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EXTERNAL_DECLARATION == sexp_get_tag(ast));
  UTILITY_ASSERT(!builder_is_local(builder));
  builder_ast(builder, sexp_at(ast, 1));
}
void builder_function_definition(Builder *builder, Sexp *ast) {
  const char *name;
  Type *type;
  Function *func;
  UTILITY_ASSERT(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  name = function_name(ast);
  type = builder_function_type(builder, ast);
  func = builder_new_function(builder, name, type);
  builder_init_next(builder, func);
  if (1 < function_count_return(ast)) {
    builder_init_return(builder);
    builder_ast(builder, sexp_at(ast, sexp_length(ast) - 1));
    builder_finish_return(builder);
  } else {
    builder_ast(builder, sexp_at(ast, sexp_length(ast) - 1));
  }
  builder_function_finish(builder);
}
