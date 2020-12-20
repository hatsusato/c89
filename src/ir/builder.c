#include "builder.h"

#include "ast/ast_tag.h"
#include "ir/module.h"
#include "ir/pool.h"
#include "ir/stack.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

struct struct_Builder {
  Pool *pool;
  Module *module;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = module_new();
  builder->pool = module_get(builder->module);
  return builder;
}
void builder_delete(Builder *builder) {
  module_delete(builder->module);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  Stack *stack = stack_new(builder->module);
  stack_ast(stack, ast);
  stack_delete(stack);
  module_pretty(builder->module);
}
