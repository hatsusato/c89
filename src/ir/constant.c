#include "ir/constant.h"

#include <stdio.h>

#include "ir/module.h"
#include "ir/stack.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Constant {
  ValueKind kind;
  const char *symbol;
};

Constant *constant_new(void) {
  Constant *constant = UTILITY_MALLOC(Constant);
  constant->kind = VALUE_CONSTANT;
  constant->symbol = NULL;
  return constant;
}
Constant *constant_integer(const char *integer) {
  Constant *constant = constant_new();
  constant->symbol = integer;
  return constant;
}
void constant_delete(Constant *constant) {
  UTILITY_FREE(constant);
}
void constant_print(Constant *constant) {
  printf("%s", constant->symbol);
}

Constant *stack_new_integer(Stack *stack, const char *integer) {
  Constant *constant = module_new_integer(stack_get_module(stack), integer);
  return constant;
}
