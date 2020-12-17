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

static Instruction *instruction_new(ValueKind kind) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = kind;
  register_init(&instr->reg);
  instr->vec = vector_new(NULL);
  instr->value = NULL;
  return instr;
}
static Instruction *stack_instruction_new(Stack *stack, ValueKind kind) {
  Block *current = stack_get_next(stack, STACK_NEXT_CURRENT);
  Instruction *instr = instruction_new(kind);
  stack_pool_register(stack, value_of(instr));
  block_insert(current, value_of(instr));
  return instr;
}
static void instruction_insert(Instruction *instr, Value *value) {
  vector_push(instr->vec, value);
}
static void instruction_insert_block(Instruction *instr, Block *block) {
  vector_push(instr->vec, block);
}

void stack_instruction_ret(Stack *stack, Value *expr) {
  Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_RET);
  instruction_insert(instr, expr);
}
void stack_instruction_br(Stack *stack, Block *label) {
  assert(label);
  if (!stack_last_terminator(stack)) {
    Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_BR);
    instruction_insert(instr, value_of(label));
  }
}
void stack_instruction_br_cond(Stack *stack, Value *expr, Block *then_label,
                               Block *else_label) {
  Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_BR_COND);
  instruction_insert(instr, expr);
  instruction_insert(instr, value_of(then_label));
  instruction_insert(instr, value_of(else_label));
}
Value *stack_instruction_switch(Stack *stack, Value *expr) {
  Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_SWITCH);
  instruction_insert(instr, expr);
  return value_of(instr);
}
void stack_instruction_switch_finish(Stack *stack, Value *value) {
  Block *default_label = stack_get_next(stack, STACK_NEXT_DEFAULT);
  Block *break_label = stack_get_next(stack, STACK_NEXT_BREAK);
  Block *switch_block = stack_get_next(stack, STACK_NEXT_SWITCH);
  Block *next = break_label ? break_label : stack_new_block(stack);
  Instruction *instr = (Instruction *)value;
  stack_instruction_br(stack, next);
  instruction_insert_block(instr, default_label ? default_label : next);
  instruction_insert_block(instr, switch_block);
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
  Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_ADD);
  instruction_insert(instr, lhs);
  instruction_insert(instr, rhs);
  return value_of(instr);
}
Value *stack_instruction_sub(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_SUB);
  instruction_insert(instr, lhs);
  instruction_insert(instr, rhs);
  return value_of(instr);
}
Value *stack_instruction_load(Stack *stack, Value *src) {
  Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_LOAD);
  instruction_insert(instr, src);
  return value_of(instr);
}
Value *stack_instruction_store(Stack *stack, Value *src, Value *dst) {
  Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_STORE);
  instruction_insert(instr, src);
  instruction_insert(instr, dst);
  return value_of(instr);
}
Value *stack_instruction_icmp_ne(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_instruction_new(stack, VALUE_INSTRUCTION_ICMP_NE);
  instruction_insert(instr, lhs);
  instruction_insert(instr, rhs);
  return value_of(instr);
}
