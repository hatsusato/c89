#include "instruction.h"

#include <stdio.h>

#include "block.h"
#include "builder.h"
#include "instruction/struct.h"
#include "module.h"
#include "utility.h"
#include "value.h"

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
#define DO_HANDLE(name, str) \
  case name:                 \
    return true;
#include "instruction/terminator.def"
#undef DO_HANDLE
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

Instruction *builder_new_instruction(Builder *builder, InstructionKind kind) {
  Module *module = builder_get_module(builder);
  Instruction *instr = module_new_instruction(module);
  Block *current = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Block *alloc = builder_get_next(builder, BUILDER_NEXT_ALLOC);
  instr->ikind = kind;
  block_insert(INSTRUCTION_ALLOCA == kind ? alloc : current, instr);
  builder_set_value(builder, instruction_as_value(instr));
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
void builder_instruction_switch(Builder *builder, Value *expr) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_SWITCH);
  instr->operands[0] = expr;
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
void builder_instruction_add(Builder *builder, Value *lhs, Value *rhs) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_ADD);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
}
void builder_instruction_sub(Builder *builder, Value *lhs, Value *rhs) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_SUB);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
}
void builder_instruction_alloca(Builder *builder, const char *symbol) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_ALLOCA);
  builder_insert_local(builder, symbol, instr);
}
void builder_instruction_load(Builder *builder, Value *src) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_LOAD);
  instr->operands[0] = src;
}
void builder_instruction_store(Builder *builder, Value *src, Value *dst) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_STORE);
  instr->operands[0] = src;
  instr->operands[1] = dst;
}
void builder_instruction_icmp_ne(Builder *builder, Value *lhs, Value *rhs) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_ICMP_NE);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
}
Instruction *builder_new_local(Builder *builder) {
  return builder_new_instruction(builder, INSTRUCTION_ALLOCA);
}
