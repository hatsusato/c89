#include "ir/value.h"

#include "ir/block.h"
#include "ir/constant.h"
#include "ir/instruction.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Value {
  ValueKind kind;
};

Function *value_as_function(Value *value) {
  assert(VALUE_FUNCTION == value->kind);
  return (Function *)value;
}
Block *value_as_block(Value *value) {
  assert(VALUE_BLOCK == value->kind);
  return (Block *)value;
}
Instruction *value_as_instruction(Value *value) {
  assert(VALUE_INSTRUCTION == value->kind);
  return (Instruction *)value;
}
Constant *value_as_constant(Value *value) {
  assert(VALUE_CONSTANT == value->kind);
  return (Constant *)value;
}
void value_print(Value *value) {
  switch (value->kind) {
  case VALUE_BLOCK:
    block_print(value_as_block(value));
    break;
  case VALUE_INSTRUCTION:
    instruction_print(value_as_instruction(value));
    break;
  case VALUE_CONSTANT:
    constant_print(value_as_constant(value));
    break;
  default:
    assert(0);
    break;
  }
}
