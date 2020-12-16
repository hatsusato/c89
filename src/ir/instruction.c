#include "ir/instruction.h"

#include "ir/block.h"
#include "ir/stack_impl.h"
#include "vector.h"

struct struct_Instruction {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

static Value *instruction_new(Stack *stack, ValueKind kind) {
  Block *current = stack_get_next(stack, STACK_NEXT_CURRENT);
  Value *value = stack_new_value(stack, kind);
  assert(value_is_instruction(value));
  block_insert(current, value);
  return value;
}

void stack_instruction_ret(Stack *stack, Value *expr) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_RET);
  value_insert(instr, expr);
}
void stack_instruction_br(Stack *stack, Block *label) {
  assert(label);
  if (!stack_last_terminator(stack)) {
    Value *instr = instruction_new(stack, VALUE_INSTRUCTION_BR);
    value_insert_block(instr, label);
  }
}
void stack_instruction_br_cond(Stack *stack, Value *expr, Block *then_label,
                               Block *else_label) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_BR_COND);
  value_insert(instr, expr);
  value_insert_block(instr, then_label);
  value_insert_block(instr, else_label);
}
Value *stack_instruction_switch(Stack *stack, Value *expr) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_SWITCH);
  value_insert(instr, expr);
  return instr;
}
void stack_instruction_switch_finish(Stack *stack, Value *instr) {
  Block *default_label = stack_get_next(stack, STACK_NEXT_DEFAULT);
  Block *break_label = stack_get_next(stack, STACK_NEXT_BREAK);
  Block *switch_block = stack_get_next(stack, STACK_NEXT_SWITCH);
  Block *next = break_label ? break_label : stack_new_block(stack);
  stack_instruction_br(stack, next);
  value_insert_block(instr, default_label ? default_label : next);
  value_insert_block(instr, switch_block);
  if (break_label || !default_label) {
    stack_jump_block(stack, next);
  }
}
void stack_instruction_switch_case(Stack *stack, Value *constant,
                                   Block *label) {
  Block *cases = stack_get_next(stack, STACK_NEXT_SWITCH);
  block_insert(cases, constant);
  block_insert(cases, value_of(label));
}
Value *stack_instruction_add(Stack *stack, Value *lhs, Value *rhs) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_ADD);
  value_insert(instr, lhs);
  value_insert(instr, rhs);
  return instr;
}
Value *stack_instruction_sub(Stack *stack, Value *lhs, Value *rhs) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_SUB);
  value_insert(instr, lhs);
  value_insert(instr, rhs);
  return instr;
}
Value *stack_instruction_load(Stack *stack, Value *src) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_LOAD);
  value_insert(instr, src);
  return instr;
}
Value *stack_instruction_store(Stack *stack, Value *src, Value *dst) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_STORE);
  value_insert(instr, src);
  value_insert(instr, dst);
  return instr;
}
Value *stack_instruction_icmp_ne(Stack *stack, Value *lhs, Value *rhs) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_ICMP_NE);
  value_insert(instr, lhs);
  value_insert(instr, rhs);
  return instr;
}
