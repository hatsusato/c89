#include "ir/instruction.h"

#include <stdio.h>

#include "ir/block.h"
#include "ir/instruction_type.h"
#include "ir/module.h"
#include "ir/stack.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Instruction {
  ValueKind kind;
  InstructionKind ikind;
  int id;
  Value *operands[3];
};

Instruction *instruction_new(void) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = VALUE_INSTRUCTION;
  instr->ikind = INSTRUCTION_KIND_END;
  instr->id = -1;
  instr->operands[0] = instr->operands[1] = instr->operands[2] = NULL;
  return instr;
}
void instruction_delete(Instruction *instr) {
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
  if (instr->operands[0]) {
    printf("ret i32 ");
    value_print(instr->operands[0]);
  } else {
    printf("ret void");
  }
}
static void instruction_pretty_br(Instruction *instr) {
  printf("br label ");
  value_print(instr->operands[0]);
}
static void instruction_pretty_br_cond(Instruction *instr) {
  printf("br i1 ");
  value_print(instr->operands[0]);
  printf(", label ");
  value_print(instr->operands[1]);
  printf(", label ");
  value_print(instr->operands[2]);
}
static void instruction_pretty_switch(Instruction *instr) {
  printf("switch i32 ");
  value_print(instr->operands[0]);
  printf(", label ");
  value_print(instr->operands[1]);
  printf(" [\n");
  block_pretty_switch(value_as_block(instr->operands[2]));
  printf("  ]");
}
static void instruction_pretty_add(Instruction *instr) {
  instruction_print(instr);
  printf(" = add nsw i32 ");
  value_print(instr->operands[0]);
  printf(", ");
  value_print(instr->operands[1]);
}
static void instruction_pretty_sub(Instruction *instr) {
  instruction_print(instr);
  printf(" = sub nsw i32 ");
  value_print(instr->operands[0]);
  printf(", ");
  value_print(instr->operands[1]);
}
static void instruction_pretty_alloca(Instruction *instr) {
  instruction_print(instr);
  printf(" = alloca i32, align 4");
  UTILITY_UNUSED(instr);
}
static void instruction_pretty_load(Instruction *instr) {
  instruction_print(instr);
  printf(" = load i32, i32* ");
  value_print(instr->operands[0]);
  printf(", align 4");
}
static void instruction_pretty_store(Instruction *instr) {
  printf("store i32 ");
  value_print(instr->operands[0]);
  printf(", i32* ");
  value_print(instr->operands[1]);
  printf(", align 4");
}
static void instruction_pretty_icmp_ne(Instruction *instr) {
  instruction_print(instr);
  printf(" = icmp ne i32 ");
  value_print(instr->operands[0]);
  printf(", ");
  value_print(instr->operands[1]);
}
void instruction_print(Instruction *instr) {
  printf("%%%d", instr->id);
}
void instruction_pretty(Instruction *instr) {
  void (*pretty[])(Instruction *) = {
      instruction_pretty_ret,     instruction_pretty_br,
      instruction_pretty_br_cond, instruction_pretty_switch,
      instruction_pretty_add,     instruction_pretty_sub,
      instruction_pretty_alloca,  instruction_pretty_load,
      instruction_pretty_store,   instruction_pretty_icmp_ne,
  };
  assert(0 <= instr->ikind && instr->ikind < INSTRUCTION_KIND_END);
  printf("  ");
  pretty[instr->ikind](instr);
  printf("\n");
}

Instruction *stack_new_instruction(Builder *stack, InstructionKind kind) {
  Instruction *instr = module_new_instruction(stack_get_module(stack));
  Block *current = stack_get_next(stack, STACK_NEXT_CURRENT);
  Block *alloc = stack_get_next(stack, STACK_NEXT_ALLOC);
  instr->ikind = kind;
  block_insert(INSTRUCTION_ALLOCA == kind ? alloc : current, instr);
  return instr;
}
void stack_instruction_ret(Builder *stack, Value *expr) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_RET);
  instr->operands[0] = expr;
}
void stack_instruction_br(Builder *stack, Block *label) {
  if (!stack_last_terminator(stack)) {
    Instruction *instr = stack_new_instruction(stack, INSTRUCTION_BR);
    instr->operands[0] = block_as_value(label);
  }
}
void stack_instruction_br_cond(Builder *stack, Value *expr, Block *then_label,
                               Block *else_label) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_BR_COND);
  instr->operands[0] = expr;
  instr->operands[1] = block_as_value(then_label);
  instr->operands[2] = block_as_value(else_label);
}
Instruction *stack_instruction_switch(Builder *stack, Value *expr) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_SWITCH);
  instr->operands[0] = expr;
  return instr;
}
void stack_instruction_switch_finish(Builder *stack, Instruction *instr) {
  Block *default_label = stack_get_next(stack, STACK_NEXT_DEFAULT);
  Block *break_label = stack_get_next(stack, STACK_NEXT_BREAK);
  Block *switch_block = stack_get_next(stack, STACK_NEXT_SWITCH);
  Block *next = break_label ? break_label : stack_new_block(stack);
  stack_instruction_br(stack, next);
  instr->operands[1] = block_as_value(default_label ? default_label : next);
  instr->operands[2] = block_as_value(switch_block);
  if (break_label || !default_label) {
    stack_jump_block(stack, next);
  }
}
void stack_instruction_switch_case(Builder *stack, Value *value, Block *label) {
  Block *switch_block = stack_get_next(stack, STACK_NEXT_SWITCH);
  block_insert_switch(switch_block, value, label);
}
Instruction *stack_instruction_add(Builder *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_ADD);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}
Instruction *stack_instruction_sub(Builder *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_SUB);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}
Instruction *stack_instruction_alloca(Builder *stack, const char *symbol) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_ALLOCA);
  stack_alloca(stack, symbol, instr);
  return instr;
}
Instruction *stack_instruction_load(Builder *stack, Value *src) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_LOAD);
  instr->operands[0] = src;
  return instr;
}
Instruction *stack_instruction_store(Builder *stack, Value *src, Value *dst) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_STORE);
  instr->operands[0] = src;
  instr->operands[1] = dst;
  return instr;
}
Instruction *stack_instruction_icmp_ne(Builder *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_ICMP_NE);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}
