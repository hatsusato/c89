#include "value.h"

#include <stdio.h>

#include "ir/block.h"
#include "ir/constant.h"
#include "ir/function.h"
#include "ir/global.h"
#include "ir/instruction.h"
#include "ir/type.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Value {
  ValueKind kind;
  Type *type;
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
Value *global_as_value(Global *global) {
  return (Value *)global;
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
Global *value_as_global(Value *value) {
  UTILITY_ASSERT(VALUE_GLOBAL == value->kind);
  return (Global *)value;
}
ValueKind value_kind(Value *value) {
  return value->kind;
}
Type *value_type(Value *value) {
  return value->type;
}
void value_print(Value *value, Bool comma) {
  printf(comma ? ", " : "");
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
  case VALUE_GLOBAL:
    global_print(value_as_global(value));
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
}
void value_print_type(Value *value) {
  switch (value->kind) {
  case VALUE_INSTRUCTION:
    instruction_print_type(value_as_instruction(value));
    break;
  case VALUE_GLOBAL:
    global_print_type(value_as_global(value));
    break;
  default:
    type_print(value->type);
    break;
  }
}
void value_print_with_type(Value *value, Bool comma) {
  printf(comma ? ", " : "");
  value_print_type(value);
  printf(" ");
  value_print(value, false);
}
