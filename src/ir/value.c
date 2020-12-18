#include "ir/value.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/block.h"
#include "ir/constant.h"
#include "ir/function.h"
#include "ir/instruction.h"
#include "ir/register.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Value {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

Value *value_new(ValueKind kind) {
  Value *value;
  switch (kind) {
  case VALUE_FUNCTION:
    return value_of(function_new());
  case VALUE_BLOCK:
    return value_of(block_new());
  default:
    value = UTILITY_MALLOC(Value);
    value->kind = kind;
    register_init(&value->reg);
    value->value = NULL;
    value->vec = vector_new(NULL);
    return value;
  }
}
void value_delete(Value *value) {
  switch (value_kind(value)) {
  case VALUE_FUNCTION:
    function_delete((Function *)value);
    break;
  case VALUE_BLOCK:
    block_delete((Block *)value);
    break;
  case VALUE_INTEGER_CONSTANT:
    constant_delete((Constant *)value);
    break;
  default:
    instruction_delete((Instruction *)value);
    break;
  }
}
Value *value_of(void *value) {
  return (Value *)value;
}
ValueKind value_kind(Value *value) {
  return value->kind;
}
void value_print(Value *value) {
  switch (value_kind(value)) {
  case VALUE_FUNCTION:
    printf("i32 @%s()", (const char *)value->value);
    break;
  case VALUE_INTEGER_CONSTANT:
    printf("%s", (const char *)value->value);
    break;
  default:
    register_print(&value->reg, true);
    break;
  }
}
