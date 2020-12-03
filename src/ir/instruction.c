#include "ir/instruction.h"

#include "ir/stack_impl.h"

static void stack_instruction_unary(Stack *stack, ValueKind kind) {
  Value *first = stack_pop(stack);
  stack_new_value(stack, kind);
  stack_add(stack, first);
  stack_insert_to_block(stack);
}
static void stack_instruction_binary(Stack *stack, ValueKind kind) {
  Value *second = stack_pop(stack);
  Value *first = stack_pop(stack);
  stack_new_value(stack, kind);
  stack_add(stack, first);
  stack_add(stack, second);
  stack_insert_to_block(stack);
}
static void stack_instruction_ternary(Stack *stack, ValueKind kind) {
  Value *third = stack_pop(stack);
  Value *second = stack_pop(stack);
  Value *first = stack_pop(stack);
  stack_new_value(stack, kind);
  stack_add(stack, first);
  stack_add(stack, second);
  stack_add(stack, third);
  stack_insert_to_block(stack);
}

void stack_instruction_ret(Stack *stack) {
  stack_instruction_unary(stack, VALUE_INSTRUCTION_RET);
  stack_pop(stack);
}
void stack_instruction_br(Stack *stack) {
  stack_instruction_unary(stack, VALUE_INSTRUCTION_BR);
  stack_pop(stack);
}
void stack_instruction_br_cond(Stack *stack) {
  stack_instruction_ternary(stack, VALUE_INSTRUCTION_BR_COND);
  stack_pop(stack);
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
