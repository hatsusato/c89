#include "value.h"

#include "block.h"
#include "constant.h"
#include "function.h"
#include "global.h"
#include "instruction.h"
#include "utility.h"
#include "vector.h"

struct struct_Value {
  ValueKind kind;
};

struct struct_ValuePool {
  Vector *vec;
};

static void value_pool_delete_value(ElemType value) {
  switch (value_kind(value)) {
  case VALUE_FUNCTION:
    function_delete(value);
    break;
  case VALUE_BLOCK:
    block_delete(value);
    break;
  case VALUE_INSTRUCTION:
    instruction_delete(value);
    break;
  case VALUE_CONSTANT:
    constant_delete(value);
    break;
  case VALUE_GLOBAL:
    global_delete(value);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
}

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
Type *value_type(Value *value) {
  switch (value->kind) {
  case VALUE_INSTRUCTION:
    return instruction_type(value_as_instruction(value));
  case VALUE_CONSTANT:
    return constant_type(value_as_constant(value));
  case VALUE_GLOBAL:
    return global_type(value_as_global(value));
  default:
    return NULL;
  }
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
  case VALUE_GLOBAL:
    global_print(value_as_global(value));
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
}

ValuePool *value_pool_new(void) {
  ValuePool *pool = UTILITY_MALLOC(ValuePool);
  pool->vec = vector_new(value_pool_delete_value);
  return pool;
}
void value_pool_delete(ValuePool *pool) {
  vector_delete(pool->vec);
  UTILITY_FREE(pool);
}
void value_pool_insert(ValuePool *pool, Value *value) {
  vector_push(pool->vec, value);
}
Block *value_pool_new_block(ValuePool *pool) {
  Block *block = block_new();
  vector_push(pool->vec, block);
  return block;
}
Instruction *value_pool_new_instruction(ValuePool *pool) {
  Instruction *instr = instruction_new();
  vector_push(pool->vec, instr);
  return instr;
}
Constant *value_pool_new_constant(ValuePool *pool) {
  Constant *constant = constant_new();
  vector_push(pool->vec, constant);
  return constant;
}
Global *value_pool_new_global(ValuePool *pool) {
  Global *global = global_new();
  vector_push(pool->vec, global);
  return global;
}
