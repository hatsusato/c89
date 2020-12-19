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
  case VALUE_BLOCK:
    block_print((Block *)value);
    break;
  case VALUE_INTEGER_CONSTANT:
    constant_print((Constant *)value);
    break;
  case VALUE_INSTRUCTION:
    instruction_print((Instruction *)value);
    break;
  default:
    assert(0);
    break;
  }
}
