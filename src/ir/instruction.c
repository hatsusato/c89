#include "ir/instruction.h"

#include "ir/block.h"
#include "ir/register.h"
#include "ir/stack_impl.h"
#include "vector.h"

struct struct_Instruction {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

static Instruction *instruction_new(Stack *stack, ValueKind kind) {
  Block *current = stack_get_next(stack, STACK_NEXT_CURRENT);
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = kind;
  register_init(&instr->reg);
  instr->vec = vector_new(NULL);
  instr->value = NULL;
  block_insert(current, value_of(instr));
  return instr;
}

void stack_instruction_ret(Stack *stack, Value *expr) {
  Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_RET);
  value_insert(value_of(instr), expr);
}
void stack_instruction_br(Stack *stack, Block *label) {
  assert(label);
  if (!stack_last_terminator(stack)) {
    Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_BR);
    value_insert_block(value_of(instr), label);
  }
}
void stack_instruction_br_cond(Stack *stack, Value *expr, Block *then_label,
                               Block *else_label) {
  Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_BR_COND);
  value_insert(value_of(instr), expr);
  value_insert_block(value_of(instr), then_label);
  value_insert_block(value_of(instr), else_label);
}
Value *stack_instruction_switch(Stack *stack, Value *expr) {
  Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_SWITCH);
  value_insert(value_of(instr), expr);
  return value_of(instr);
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
  Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_ADD);
  value_insert(value_of(instr), lhs);
  value_insert(value_of(instr), rhs);
  return value_of(instr);
}
Value *stack_instruction_sub(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_SUB);
  value_insert(value_of(instr), lhs);
  value_insert(value_of(instr), rhs);
  return value_of(instr);
}
Value *stack_instruction_load(Stack *stack, Value *src) {
  Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_LOAD);
  value_insert(value_of(instr), src);
  return value_of(instr);
}
Value *stack_instruction_store(Stack *stack, Value *src, Value *dst) {
  Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_STORE);
  value_insert(value_of(instr), src);
  value_insert(value_of(instr), dst);
  return value_of(instr);
}
Value *stack_instruction_icmp_ne(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = instruction_new(stack, VALUE_INSTRUCTION_ICMP_NE);
  value_insert(value_of(instr), lhs);
  value_insert(value_of(instr), rhs);
  return value_of(instr);
}
