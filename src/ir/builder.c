#include "builder.h"

#include "ast/ast_tag.h"
#include "ir/pool.h"
#include "ir/stack.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

struct struct_Builder {
  Pool *pool;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->pool = pool_new();
  return builder;
}
void builder_delete(Builder *builder) {
  pool_delete(builder->pool);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  Stack *stack = stack_new(builder->pool);
  stack_build(stack, ast);
  stack_print(stack);
  stack_delete(stack);
}
static builder_ast_map(Builder *builder, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    builder_ast(builder, sexp_car(ast));
  }
}
void builder_ast(Builder *builder, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_TRANSLATION_UNIT:
    builder_ast_map(builder, ast);
    break;
  case AST_EXTERNAL_DECLARATION:
    break;
  case AST_FUNCTION_DEFINITION:
    break;
  default:
    assert(0);
    break;
  }
}
