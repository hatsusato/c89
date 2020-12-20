#include "ir/constant.h"

#include <stdio.h>

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
Value *constant_as_value(Constant *constant) {
  return (Value *)constant;
}
void constant_print(Constant *constant) {
  printf("%s", constant->symbol);
}
