#include "ir/instruction.h"

#include <stdio.h>

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

static void instruction_pretty_ret(Vector *vec) {
  if (vector_empty(vec)) {
    printf("ret void");
  } else {
    printf("ret i32 ");
    value_print(vector_at(vec, 0));
  }
}
static void instruction_pretty_br(Vector *vec) {
  printf("br label ");
  value_print(vector_at(vec, 0));
}
static void instruction_pretty_br_cond(Vector *vec) {
  printf("br i1 ");
  value_print(vector_at(vec, 0));
  printf(", label ");
  value_print(vector_at(vec, 1));
  printf(", label ");
  value_print(vector_at(vec, 2));
}
static void instruction_pretty_switch(Vector *vec) {
  printf("switch i32 ");
  value_print(vector_at(vec, 0));
  printf(", label ");
  value_print(vector_at(vec, 1));
  printf(" [\n");
  block_pretty_switch(vector_at(vec, 2));
  printf("  ]");
}
static void instruction_pretty_add(Vector *vec) {
  printf(" = add nsw i32 ");
  value_print(vector_at(vec, 0));
  printf(", ");
  value_print(vector_at(vec, 1));
}
static void instruction_pretty_sub(Vector *vec) {
  printf(" = sub nsw i32 ");
  value_print(vector_at(vec, 0));
  printf(", ");
  value_print(vector_at(vec, 1));
}
static void instruction_pretty_alloca(Vector *vec) {
  printf(" = alloca i32, align 4");
  UTILITY_UNUSED(vec);
}
static void instruction_pretty_load(Vector *vec) {
  printf(" = load i32, i32* ");
  value_print(vector_at(vec, 0));
  printf(", align 4");
}
static void instruction_pretty_store(Vector *vec) {
  printf("store i32 ");
  value_print(vector_at(vec, 0));
  printf(", i32* ");
  value_print(vector_at(vec, 1));
  printf(", align 4");
}
static void instruction_pretty_icmp_ne(Vector *vec) {
  printf(" = icmp ne i32 ");
  value_print(vector_at(vec, 0));
  printf(", ");
  value_print(vector_at(vec, 1));
}
void instruction_pretty(Instruction *instr) {
  Vector *vec = instr->vec;
  printf("  ");
  switch (instr->kind) {
  case VALUE_INSTRUCTION_RET:
    instruction_pretty_ret(vec);
    break;
  case VALUE_INSTRUCTION_BR:
    instruction_pretty_br(vec);
    break;
  case VALUE_INSTRUCTION_BR_COND:
    instruction_pretty_br_cond(vec);
    break;
  case VALUE_INSTRUCTION_SWITCH:
    instruction_pretty_switch(vec);
    break;
  case VALUE_INSTRUCTION_ADD:
    value_print(value_of(instr));
    instruction_pretty_add(vec);
    break;
  case VALUE_INSTRUCTION_SUB:
    value_print(value_of(instr));
    instruction_pretty_sub(vec);
    break;
  case VALUE_INSTRUCTION_ALLOCA:
    value_print(value_of(instr));
    instruction_pretty_alloca(vec);
    break;
  case VALUE_INSTRUCTION_LOAD:
    value_print(value_of(instr));
    instruction_pretty_load(vec);
    break;
  case VALUE_INSTRUCTION_STORE:
    instruction_pretty_store(vec);
    break;
  case VALUE_INSTRUCTION_ICMP_NE:
    value_print(value_of(instr));
    instruction_pretty_icmp_ne(vec);
    break;
  default:
    assert(0);
    break;
  }
  printf("\n");
}
