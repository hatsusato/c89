#include "ir/instruction.h"

#include "ir/stack_impl.h"

static Value *instruction_new(Stack *stack, ValueKind kind) {
  Value *current = stack_get_next(stack, STACK_NEXT_CURRENT);
  Value *value = stack_new_value(stack, kind);
  assert(value_is_instruction(value));
  value_insert(current, value);
  return value;
}

void stack_instruction_ret(Stack *stack, Value *expr) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_RET);
  value_insert(instr, expr);
}
void stack_instruction_br(Stack *stack, Value *label) {
  assert(label && VALUE_BLOCK == value_kind(label));
  if (!stack_last_terminator(stack)) {
    Value *instr = instruction_new(stack, VALUE_INSTRUCTION_BR);
    value_insert(instr, label);
  }
}
void stack_instruction_br_cond(Stack *stack, Value *expr, Value *then_label,
                               Value *else_label) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_BR_COND);
  value_insert(instr, expr);
  value_insert(instr, then_label);
  value_insert(instr, else_label);
}
void stack_instruction_switch(Stack *stack, Value *expr, Value *label,
                              Value *block) {
  Value *instr = instruction_new(stack, VALUE_INSTRUCTION_SWITCH);
  value_insert(instr, expr);
  value_insert(instr, label);
  value_insert(instr, block);
}
void stack_instruction_switch_case(Stack *stack, Value *constant,
                                   Value *label) {
  Value *cases = stack_get_next(stack, STACK_NEXT_SWITCH);
  value_insert(cases, constant);
  value_insert(cases, label);
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
