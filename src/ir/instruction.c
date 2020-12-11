#include "ir/instruction.h"

#include "ir/stack_impl.h"

static void stack_instruction_new(Stack *stack, ValueKind kind) {
  stack_new_value(stack, kind);
  stack_insert_to_block(stack);
}
static void stack_instruction_unary(Stack *stack, ValueKind kind) {
  Value *first = stack_pop(stack);
  stack_instruction_new(stack, kind);
  stack_insert_as_operand(stack, first);
}
static void stack_instruction_binary(Stack *stack, ValueKind kind) {
  Value *second = stack_pop(stack);
  Value *first = stack_pop(stack);
  stack_instruction_new(stack, kind);
  stack_insert_as_operand(stack, first);
  stack_insert_as_operand(stack, second);
}

void stack_instruction_ret(Stack *stack) {
  stack_instruction_unary(stack, VALUE_INSTRUCTION_RET);
  stack_pop(stack);
}
void stack_instruction_br(Stack *stack, Value *label) {
  assert(label);
  assert(!stack_last_terminator(stack));
  stack_instruction_new(stack, VALUE_INSTRUCTION_BR);
  stack_insert_as_operand(stack, label);
  stack_pop(stack);
}
void stack_instruction_br_cond(Stack *stack, Value *then_label,
                               Value *else_label) {
  stack_instruction_unary(stack, VALUE_INSTRUCTION_BR_COND);
  stack_insert_as_operand(stack, then_label);
  stack_insert_as_operand(stack, else_label);
  stack_pop(stack);
}
void stack_instruction_switch(Stack *stack, Value *default_label) {
  stack_instruction_unary(stack, VALUE_INSTRUCTION_SWITCH);
  stack_insert_as_operand(stack, default_label);
  stack_set_next(stack, STACK_NEXT_DEFAULT, default_label);
}
void stack_instruction_switch_case(Stack *stack, Value *label) {
  Value *first = stack_pop(stack);
  stack_insert_as_operand(stack, first);
  stack_insert_as_operand(stack, label);
}
void stack_instruction_add(Stack *stack) {
  stack_instruction_binary(stack, VALUE_INSTRUCTION_ADD);
}
void stack_instruction_sub(Stack *stack) {
  stack_instruction_binary(stack, VALUE_INSTRUCTION_SUB);
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
