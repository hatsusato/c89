#include "value.h"

#include "block.h"
#include "constant.h"
#include "instruction.h"
#include "utility.h"
#include "value/kind.h"

struct struct_Value {
  ValueKind kind;
};

Value *function_as_value(Function *func) {
  return (Value *)func;
}
Value *block_as_value(Block *block) {
  return (Value *)block;
}
Value *instruction_as_value(Instruction *instr) {
  return (Value *)instr;
}
Value *constant_as_value(Constant *constant) {
  return (Value *)constant;
}
Function *value_as_function(Value *value) {
  UTILITY_ASSERT(VALUE_FUNCTION == value->kind);
  return (Function *)value;
}
Block *value_as_block(Value *value) {
  UTILITY_ASSERT(VALUE_BLOCK == value->kind);
  return (Block *)value;
}
Instruction *value_as_instruction(Value *value) {
  UTILITY_ASSERT(VALUE_INSTRUCTION == value->kind);
  return (Instruction *)value;
}
Constant *value_as_constant(Value *value) {
  UTILITY_ASSERT(VALUE_CONSTANT == value->kind);
  return (Constant *)value;
}
ValueKind value_kind(Value *value) {
  return value->kind;
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
    UTILITY_ASSERT(0);
    break;
  }
}
