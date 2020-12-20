#include "ir/instruction.h"

#include <stdio.h>

#include "ir/block.h"
#include "ir/instruction_type.h"
#include "ir/stack.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Instruction {
  ValueKind kind;
  InstructionKind ikind;
  int id;
  Vector *vec;
  Value *operands[3];
};

void stack_instruction_ret(Stack *stack, Value *expr) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_RET);
  vector_push(instr->vec, expr);
  instr->operands[0] = expr;
}
void stack_instruction_br(Stack *stack, Block *label) {
  if (!stack_last_terminator(stack)) {
    Instruction *instr = stack_new_instruction(stack, INSTRUCTION_BR);
    vector_push(instr->vec, label);
    instr->operands[0] = block_as_value(label);
  }
}
void stack_instruction_br_cond(Stack *stack, Value *expr, Block *then_label,
                               Block *else_label) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_BR_COND);
  vector_push(instr->vec, expr);
  vector_push(instr->vec, then_label);
  vector_push(instr->vec, else_label);
  instr->operands[0] = expr;
  instr->operands[1] = block_as_value(then_label);
  instr->operands[2] = block_as_value(else_label);
}
Instruction *stack_instruction_switch(Stack *stack, Value *expr) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_SWITCH);
  vector_push(instr->vec, expr);
  instr->operands[0] = expr;
  return instr;
}
void stack_instruction_switch_finish(Stack *stack, Instruction *instr) {
  Block *default_label = stack_get_next(stack, STACK_NEXT_DEFAULT);
  Block *break_label = stack_get_next(stack, STACK_NEXT_BREAK);
  Block *switch_block = stack_get_next(stack, STACK_NEXT_SWITCH);
  Block *next = break_label ? break_label : stack_new_block(stack);
  stack_instruction_br(stack, next);
  vector_push(instr->vec, default_label ? default_label : next);
  vector_push(instr->vec, switch_block);
  instr->operands[1] = block_as_value(default_label ? default_label : next);
  instr->operands[2] = block_as_value(switch_block);
  if (break_label || !default_label) {
    stack_jump_block(stack, next);
  }
}
void stack_instruction_switch_case(Stack *stack, Value *value, Block *label) {
  Block *switch_block = stack_get_next(stack, STACK_NEXT_SWITCH);
  block_insert_switch(switch_block, value, label);
}
Instruction *stack_instruction_add(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_ADD);
  vector_push(instr->vec, lhs);
  vector_push(instr->vec, rhs);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}
Instruction *stack_instruction_sub(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_SUB);
  vector_push(instr->vec, lhs);
  vector_push(instr->vec, rhs);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}
Instruction *stack_instruction_alloca(Stack *stack, const char *symbol) {
  Instruction *instr = instruction_new(INSTRUCTION_ALLOCA);
  stack_alloca(stack, symbol, instr);
  return instr;
}
Instruction *stack_instruction_load(Stack *stack, Value *src) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_LOAD);
  vector_push(instr->vec, src);
  instr->operands[0] = src;
  return instr;
}
Instruction *stack_instruction_store(Stack *stack, Value *src, Value *dst) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_STORE);
  vector_push(instr->vec, src);
  vector_push(instr->vec, dst);
  instr->operands[0] = src;
  instr->operands[1] = dst;
  return instr;
}
Instruction *stack_instruction_icmp_ne(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_ICMP_NE);
  vector_push(instr->vec, lhs);
  vector_push(instr->vec, rhs);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}

Instruction *instruction_new(InstructionKind kind) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = VALUE_INSTRUCTION;
  instr->ikind = kind;
  instr->id = -1;
  instr->vec = vector_new(NULL);
  instr->operands[0] = instr->operands[1] = instr->operands[2] = NULL;
  return instr;
}
void instruction_delete(Instruction *instr) {
  vector_delete(instr->vec);
  UTILITY_FREE(instr);
}
Bool instruction_is_terminator(Instruction *instr) {
  switch (instr->ikind) {
#define HANDLE_INSTRUCTION_KIND(k) \
  case k:                          \
    return true
    HANDLE_INSTRUCTION_KIND(INSTRUCTION_RET);
    HANDLE_INSTRUCTION_KIND(INSTRUCTION_BR);
    HANDLE_INSTRUCTION_KIND(INSTRUCTION_BR_COND);
    HANDLE_INSTRUCTION_KIND(INSTRUCTION_SWITCH);
#undef HANDLE_INSTRUCTION_KIND
  default:
    return false;
  }
}
int instruction_set_id(Instruction *instr, int id) {
  if (!instruction_is_terminator(instr) && INSTRUCTION_STORE != instr->ikind) {
    instr->id = id++;
  }
  return id;
}
static void instruction_pretty_ret(Instruction *instr) {
  if (vector_empty(instr->vec)) {
    printf("ret void");
  } else {
    printf("ret i32 ");
    value_print(vector_at(instr->vec, 0));
  }
}
static void instruction_pretty_br(Instruction *instr) {
  printf("br label ");
  value_print(vector_at(instr->vec, 0));
}
static void instruction_pretty_br_cond(Instruction *instr) {
  printf("br i1 ");
  value_print(vector_at(instr->vec, 0));
  printf(", label ");
  value_print(vector_at(instr->vec, 1));
  printf(", label ");
  value_print(vector_at(instr->vec, 2));
}
static void instruction_pretty_switch(Instruction *instr) {
  printf("switch i32 ");
  value_print(vector_at(instr->vec, 0));
  printf(", label ");
  value_print(vector_at(instr->vec, 1));
  printf(" [\n");
  block_pretty_switch(vector_at(instr->vec, 2));
  printf("  ]");
}
static void instruction_pretty_add(Instruction *instr) {
  instruction_print(instr);
  printf(" = add nsw i32 ");
  value_print(vector_at(instr->vec, 0));
  printf(", ");
  value_print(vector_at(instr->vec, 1));
}
static void instruction_pretty_sub(Instruction *instr) {
  instruction_print(instr);
  printf(" = sub nsw i32 ");
  value_print(vector_at(instr->vec, 0));
  printf(", ");
  value_print(vector_at(instr->vec, 1));
}
static void instruction_pretty_alloca(Instruction *instr) {
  instruction_print(instr);
  printf(" = alloca i32, align 4");
  UTILITY_UNUSED(instr);
}
static void instruction_pretty_load(Instruction *instr) {
  instruction_print(instr);
  printf(" = load i32, i32* ");
  value_print(vector_at(instr->vec, 0));
  printf(", align 4");
}
static void instruction_pretty_store(Instruction *instr) {
  printf("store i32 ");
  value_print(vector_at(instr->vec, 0));
  printf(", i32* ");
  value_print(vector_at(instr->vec, 1));
  printf(", align 4");
}
static void instruction_pretty_icmp_ne(Instruction *instr) {
  instruction_print(instr);
  printf(" = icmp ne i32 ");
  value_print(vector_at(instr->vec, 0));
  printf(", ");
  value_print(vector_at(instr->vec, 1));
}
void instruction_print(Instruction *instr) {
  printf("%%%d", instr->id);
}
void instruction_pretty(Instruction *instr) {
  printf("  ");
  switch (instr->ikind) {
  case INSTRUCTION_RET:
    instruction_pretty_ret(instr);
    break;
  case INSTRUCTION_BR:
    instruction_pretty_br(instr);
    break;
  case INSTRUCTION_BR_COND:
    instruction_pretty_br_cond(instr);
    break;
  case INSTRUCTION_SWITCH:
    instruction_pretty_switch(instr);
    break;
  case INSTRUCTION_ADD:
    instruction_pretty_add(instr);
    break;
  case INSTRUCTION_SUB:
    instruction_pretty_sub(instr);
    break;
  case INSTRUCTION_ALLOCA:
    instruction_pretty_alloca(instr);
    break;
  case INSTRUCTION_LOAD:
    instruction_pretty_load(instr);
    break;
  case INSTRUCTION_STORE:
    instruction_pretty_store(instr);
    break;
  case INSTRUCTION_ICMP_NE:
    instruction_pretty_icmp_ne(instr);
    break;
  default:
    assert(0);
    break;
  }
  printf("\n");
}
