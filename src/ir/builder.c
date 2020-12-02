#include "builder.h"

#include "ast/ast_tag.h"
#include "ir/pool.h"
#include "ir/stack.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

struct struct_Builder {
  Pool *pool;
  Value *module;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->pool = pool_new();
  builder->module = pool_alloc(builder->pool, VALUE_MODULE);
  return builder;
}
void builder_delete(Builder *builder) {
  pool_delete(builder->pool);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  builder_ast(builder, ast);
  value_pretty(builder->module);
}
static void builder_ast_map(Builder *builder, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    builder_ast(builder, sexp_car(ast));
  }
}
void builder_ast(Builder *builder, Sexp *ast) {
  Stack *stack;
  switch (sexp_get_tag(ast)) {
  case AST_TRANSLATION_UNIT:
    builder_ast_map(builder, ast);
    break;
  case AST_EXTERNAL_DECLARATION:
    break;
  case AST_FUNCTION_DEFINITION:
    stack = stack_new(builder->pool);
    value_insert(builder->module, stack_build(stack, ast));
    stack_delete(stack);
    break;
  default:
    assert(0);
    break;
  }
}
