#include "definition.h"

#include "ast/get.h"
#include "ast/tag.h"
#include "builder/builder.h"
#include "builder/ir.h"
#include "ir/function.h"
#include "ir/type.h"
#include "ir/value.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

static const char *function_name(Sexp *ast) {
  ast = ast_get_function_name(ast);
  UTILITY_ASSERT(sexp_get_tag(ast) == SYNTAX_IDENTIFIER);
  return identifier_symbol(ast);
}
static int function_count_return(Sexp *ast) {
  ast = ast_get_function_return_count(ast);
  UTILITY_ASSERT(sexp_is_number(ast));
  return sexp_get_number(ast);
}
static Type *builder_function_type(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(7 == sexp_length(ast));
  builder_ast(builder, sexp_at(ast, 1));
  return builder_get_type(builder);
}
static void builder_function_init(Builder *builder, Sexp *ast) {
  Module *module = builder_get_module(builder);
  const char *name = function_name(ast);
  Type *type = builder_function_type(builder, ast);
  Function *func = function_new(module, name, type);
  builder_init_next(builder, func);
}

void builder_translation_unit(Builder *builder, Sexp *ast) {
  builder_ast_map(builder, ast);
}
void builder_external_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(!builder_is_local(builder));
  builder_ast(builder, sexp_at(ast, 1));
}
void builder_function_definition(Builder *builder, Sexp *ast) {
  builder_function_init(builder, ast);
  if (1 < function_count_return(ast)) {
    builder_init_return(builder);
    builder_ast(builder, sexp_at(ast, 4));
    builder_finish_return(builder);
  } else {
    builder_ast(builder, sexp_at(ast, 4));
  }
  builder_function_finish(builder);
}
