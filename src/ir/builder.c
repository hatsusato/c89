#include "builder.h"

#include "ir/stack.h"
#include "utility.h"

struct struct_Builder {
  Stack *stack;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->stack = stack_new();
  return builder;
}
void builder_delete(Builder *builder) {
  stack_delete(builder->stack);
  UTILITY_FREE(builder);
}
