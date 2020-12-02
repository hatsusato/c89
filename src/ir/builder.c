#include "builder.h"

#include "ir/pool.h"
#include "ir/stack.h"
#include "ir/value_kind.h"
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
