#include "ir/value.h"

#include "ir/block.h"
#include "ir/constant.h"
#include "ir/instruction.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Value {
  ValueKind kind;
};

Value *value_of(void *value) {
  return (Value *)value;
}
void value_print(Value *value) {
  switch (value->kind) {
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
