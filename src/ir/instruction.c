#include "ir/instruction.h"

#include <stdio.h>

#include "ir/block.h"
#include "ir/builder.h"
#include "ir/instruction/type.h"
#include "ir/module.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

enum { INSTRUCTION_OPERAND_COUNT = 3 };
struct struct_Instruction {
  ValueKind kind;
  InstructionKind ikind;
  int id;
  Value *operands[INSTRUCTION_OPERAND_COUNT];
};

static void instruction_print_operand(Instruction *instr, Index index) {
  UTILITY_ASSERT(0 <= index && index < INSTRUCTION_OPERAND_COUNT);
  value_print(instr->operands[index]);
}
static void instruction_pretty_ret(Instruction *instr) {
  if (instr->operands[0]) {
    printf("ret i32 ");
    instruction_print_operand(instr, 0);
  } else {
    printf("ret void");
  }
}
static void instruction_pretty_br(Instruction *instr) {
  printf("br label ");
  instruction_print_operand(instr, 0);
}
static void instruction_pretty_br_cond(Instruction *instr) {
  printf("br i1 ");
  instruction_print_operand(instr, 0);
  printf(", label ");
  instruction_print_operand(instr, 1);
  printf(", label ");
  instruction_print_operand(instr, 2);
}
static void instruction_pretty_switch(Instruction *instr) {
  printf("switch i32 ");
  instruction_print_operand(instr, 0);
  printf(", label ");
  instruction_print_operand(instr, 1);
  printf(" [\n");
  block_pretty_switch(value_as_block(instr->operands[2]));
  printf("  ]");
}
static void instruction_pretty_add(Instruction *instr) {
  instruction_print(instr);
  printf(" = add nsw i32 ");
  instruction_print_operand(instr, 0);
  printf(", ");
  instruction_print_operand(instr, 1);
}
static void instruction_pretty_sub(Instruction *instr) {
  instruction_print(instr);
  printf(" = sub nsw i32 ");
  instruction_print_operand(instr, 0);
  printf(", ");
  instruction_print_operand(instr, 1);
}
static void instruction_pretty_alloca(Instruction *instr) {
  instruction_print(instr);
  printf(" = alloca i32, align 4");
}
static void instruction_pretty_load(Instruction *instr) {
  instruction_print(instr);
  printf(" = load i32, i32* ");
  instruction_print_operand(instr, 0);
  printf(", align 4");
}
static void instruction_pretty_store(Instruction *instr) {
  printf("store i32 ");
  instruction_print_operand(instr, 0);
  printf(", i32* ");
  instruction_print_operand(instr, 1);
  printf(", align 4");
}
static void instruction_pretty_icmp_ne(Instruction *instr) {
  instruction_print(instr);
  printf(" = icmp ne i32 ");
  instruction_print_operand(instr, 0);
  printf(", ");
  instruction_print_operand(instr, 1);
}

Instruction *instruction_new(void) {
  Index i = 0;
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = VALUE_INSTRUCTION;
  instr->ikind = INSTRUCTION_KIND_COUNT;
  instr->id = -1;
  while (i < INSTRUCTION_OPERAND_COUNT) {
    instr->operands[i++] = NULL;
  }
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
  UTILITY_ASSERT(0 <= instr->ikind && instr->ikind < INSTRUCTION_KIND_COUNT);
  printf("  ");
  pretty[instr->ikind](instr);
  printf("\n");
}

Instruction *builder_new_instruction(Builder *builder, InstructionKind kind) {
  Module *module = builder_get_module(builder);
  Instruction *instr = module_new_instruction(module);
  Block *current = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Block *alloc = builder_get_next(builder, BUILDER_NEXT_ALLOC);
  instr->ikind = kind;
  block_insert(INSTRUCTION_ALLOCA == kind ? alloc : current, instr);
  return instr;
}
void builder_instruction_ret(Builder *builder, Value *expr) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_RET);
  instr->operands[0] = expr;
}
void builder_instruction_br(Builder *builder, Block *label) {
  Block *current = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  if (!block_is_terminated(current)) {
    Instruction *instr = builder_new_instruction(builder, INSTRUCTION_BR);
    instr->operands[0] = block_as_value(label);
  }
}
void builder_instruction_br_cond(Builder *builder, Value *expr,
                                 Block *then_label, Block *else_label) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_BR_COND);
  instr->operands[0] = expr;
  instr->operands[1] = block_as_value(then_label);
  instr->operands[2] = block_as_value(else_label);
}
Instruction *builder_instruction_switch(Builder *builder, Value *expr) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_SWITCH);
  instr->operands[0] = expr;
  return instr;
}
void builder_instruction_switch_finish(Builder *builder, Instruction *instr) {
  Block *default_label = builder_get_next(builder, BUILDER_NEXT_DEFAULT);
  Block *break_label = builder_get_next(builder, BUILDER_NEXT_BREAK);
  Block *switch_block = builder_get_next(builder, BUILDER_NEXT_SWITCH);
  Block *next = break_label ? break_label : builder_new_block(builder);
  builder_instruction_br(builder, next);
  instr->operands[1] = block_as_value(default_label ? default_label : next);
  instr->operands[2] = block_as_value(switch_block);
  if (break_label || !default_label) {
    builder_jump_block(builder, next);
  }
}
void builder_instruction_switch_case(Builder *builder, Value *value,
                                     Block *label) {
  Block *switch_block = builder_get_next(builder, BUILDER_NEXT_SWITCH);
  block_insert_switch(switch_block, value, label);
}
Instruction *builder_instruction_add(Builder *builder, Value *lhs, Value *rhs) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_ADD);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}
Instruction *builder_instruction_sub(Builder *builder, Value *lhs, Value *rhs) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_SUB);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}
Instruction *builder_instruction_alloca(Builder *builder, const char *symbol) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_ALLOCA);
  builder_alloca(builder, symbol, instr);
  return instr;
}
Instruction *builder_instruction_load(Builder *builder, Value *src) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_LOAD);
  instr->operands[0] = src;
  return instr;
}
Instruction *builder_instruction_store(Builder *builder, Value *src,
                                       Value *dst) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_STORE);
  instr->operands[0] = src;
  instr->operands[1] = dst;
  return instr;
}
Instruction *builder_instruction_icmp_ne(Builder *builder, Value *lhs,
                                         Value *rhs) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_ICMP_NE);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
  return instr;
}
