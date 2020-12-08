#include "ir/instruction.h"

#include "ir/stack_impl.h"

static void stack_instruction_unary(Stack *stack, ValueKind kind) {
  Value *first = stack_pop(stack);
  stack_new_value(stack, kind);
  stack_insert_as_operand(stack, first);
  stack_insert_to_block(stack);
}
static void stack_instruction_binary(Stack *stack, ValueKind kind) {
  Value *second = stack_pop(stack);
  Value *first = stack_pop(stack);
  stack_new_value(stack, kind);
  stack_insert_as_operand(stack, first);
  stack_insert_as_operand(stack, second);
  stack_insert_to_block(stack);
}

void stack_instruction_ret(Stack *stack) {
  stack_instruction_unary(stack, VALUE_INSTRUCTION_RET);
  stack_pop(stack);
}
void stack_instruction_br(Stack *stack, Value *next) {
  if (!next) {
    next = stack_get_next_block(stack);
  }
  if (!stack_last_terminator(stack)) {
    stack_push(stack, next);
    stack_instruction_unary(stack, VALUE_INSTRUCTION_BR);
    stack_pop(stack);
  }
}
void stack_instruction_br_cond(Stack *stack, Value *then_block,
                               Value *else_block) {
  stack_instruction_unary(stack, VALUE_INSTRUCTION_BR_COND);
  stack_insert_as_operand(stack, then_block);
  stack_insert_as_operand(stack, else_block);
  stack_pop(stack);
}
void stack_instruction_switch(Stack *stack) {
  stack_instruction_binary(stack, VALUE_INSTRUCTION_SWITCH);
}
void stack_instruction_switch_case(Stack *stack) {
  Value *second = stack_pop(stack);
  Value *first = stack_pop(stack);
  stack_insert_as_operand(stack, first);
  stack_insert_as_operand(stack, second);
}
void stack_instruction_add(Stack *stack) {
  stack_instruction_binary(stack, VALUE_INSTRUCTION_ADD);
}
void stack_instruction_load(Stack *stack) {
  stack_instruction_unary(stack, VALUE_INSTRUCTION_LOAD);
}
void stack_instruction_store(Stack *stack) {
  stack_instruction_binary(stack, VALUE_INSTRUCTION_STORE);
}
void stack_instruction_icmp_ne(Stack *stack) {
  stack_instruction_binary(stack, VALUE_INSTRUCTION_ICMP_NE);
}
