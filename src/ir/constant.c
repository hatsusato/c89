#include "ir/constant.h"

#include <stdio.h>

#include "ir/module.h"
#include "ir/stack.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Constant {
  ValueKind kind;
  const char *symbol;
};

static Constant *constant_new(void) {
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

Value *stack_new_integer(Stack *stack, const char *integer) {
  Constant *value = module_new_integer(stack_get_module(stack), integer);
  return constant_as_value(value);
}
