#include "builder.h"

#include "ir/pool.h"
#include "ir/stack.h"
#include "utility.h"

struct struct_Builder {
  Pool *pool;
  Stack *stack;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->pool = pool_new();
  builder->stack = stack_new(builder->pool);
  return builder;
}
void builder_delete(Builder *builder) {
  stack_delete(builder->stack);
  pool_delete(builder->pool);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  stack_build(builder->stack, ast);
  stack_print(builder->stack);
}
