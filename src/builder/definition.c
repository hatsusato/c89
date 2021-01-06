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
  Block *ret;
  UTILITY_ASSERT(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  name = function_name(ast);
  type = builder_function_type(builder, ast);
  func = builder_new_function(builder, name, ast);
  builder_function_init(builder, func, ast);
  ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  builder_ast(builder, sexp_at(ast, sexp_length(ast) - 1));
  if (ret) {
    Value *retval = NULL;
    builder_instruction_br(builder, ret);
    builder_jump_block(builder, ret);
    retval = builder_get_retval(builder);
    if (!type_is_void(type)) {
      builder_instruction_load(builder, retval);
      retval = builder_get_value(builder);
    }
    builder_instruction_ret(builder, retval);
  }
  builder_function_finish(builder);
}
