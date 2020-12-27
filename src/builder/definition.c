#include "definition.h"

#include "ast/tag.h"
#include "builder.h"
#include "declaration.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"

static void builder_external_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATOR == sexp_get_tag(ast));
  UTILITY_ASSERT(2 == sexp_length(ast));
  builder_direct_declarator(builder, sexp_at(ast, 1));
}
static void builder_external_init_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  UTILITY_ASSERT(2 == sexp_length(ast) || 4 == sexp_length(ast));
  builder_external_declarator(builder, sexp_at(ast, 1));
  if (4 == sexp_length(ast)) {
    Value *global = builder_get_value(builder), *init;
    builder_ast(builder, sexp_at(ast, 3));
    init = builder_get_value(builder);
    builder_init_global(builder, global, init);
  }
}
static void builder_function_return(Builder *builder) {
  Value *retval;
  retval = builder_get_retval(builder);
  builder_instruction_load(builder, retval);
  retval = builder_get_value(builder);
  builder_instruction_ret(builder, retval);
}

void builder_external_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EXTERNAL_DECLARATION == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(AST_DECLARATION == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  UTILITY_ASSERT(AST_INIT_DECLARATOR_LIST == sexp_get_tag(ast));
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    builder_external_init_declarator(builder, sexp_car(ast));
  }
}
void builder_function_definition(Builder *builder, Sexp *ast) {
  Block *ret;
  UTILITY_ASSERT(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  UTILITY_ASSERT(5 == sexp_length(ast));
  builder_function_init(builder, ast);
  ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  builder_ast(builder, sexp_at(ast, 4));
  if (ret) {
    builder_instruction_br(builder, ret);
    builder_jump_block(builder, ret);
    builder_function_return(builder);
  }
  builder_function_finish(builder);
}
