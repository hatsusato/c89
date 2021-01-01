#include "new.h"

#include "../block.h"
#include "../builder.h"
#include "../type.h"
#include "struct.h"

static Instruction *builder_new_instruction(Builder *builder,
                                            InstructionKind kind) {
  Module *module = builder_get_module(builder);
  Instruction *instr = module_new_instruction(module);
  Block *current = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Block *alloc = builder_get_next(builder, BUILDER_NEXT_ALLOC);
  instr->ikind = kind;
  switch (kind) {
  case INSTRUCTION_ALLOCA:
    instr->type = builder_get_type(builder);
    block_insert(alloc, instr);
    break;
  case INSTRUCTION_ICMP_NE:
    instr->type = builder_type_integer(builder, 1);
    block_insert(current, instr);
    break;
  default:
    instr->type = builder_get_type(builder);
    block_insert(current, instr);
    break;
  }
  builder_set_value(builder, instruction_as_value(instr));
  return instr;
}
static void builder_instruction_unary(Builder *builder, InstructionKind kind,
                                      Value *value) {
  Instruction *instr = builder_new_instruction(builder, kind);
  instr->operands[0] = value;
}
static void builder_instruction_binary(Builder *builder, InstructionKind kind,
                                       Value *lhs, Value *rhs) {
  Instruction *instr = builder_new_instruction(builder, kind);
  instr->operands[0] = lhs;
  instr->operands[1] = rhs;
}
static Bool instruction_is_terminator(Instruction *instr) {
  switch (instr->ikind) {
#define DO_HANDLE(name, str) \
  case name:                 \
    return true;
#include "terminator.def"
#undef DO_HANDLE
  default:
    return false;
  }
}

void builder_instruction_ret(Builder *builder, Value *expr) {
  builder_instruction_unary(builder, INSTRUCTION_RET, expr);
}
void builder_instruction_br(Builder *builder, Block *label) {
  Block *current = builder_get_next(builder, BUILDER_NEXT_CURRENT);
  Instruction *last = block_last(current);
  if (!last || !instruction_is_terminator(last)) {
    builder_instruction_unary(builder, INSTRUCTION_BR, block_as_value(label));
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
  builder_instruction_unary(builder, INSTRUCTION_SWITCH, expr);
}
void builder_instruction_switch_finish(Builder *builder, Value *value) {
  Instruction *instr = value_as_instruction(value);
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
  builder_instruction_binary(builder, INSTRUCTION_ADD, lhs, rhs);
}
void builder_instruction_sub(Builder *builder, Value *lhs, Value *rhs) {
  builder_instruction_binary(builder, INSTRUCTION_SUB, lhs, rhs);
}
void builder_instruction_alloca(Builder *builder, const char *symbol) {
  Instruction *instr = builder_new_instruction(builder, INSTRUCTION_ALLOCA);
  builder_insert_local(builder, symbol, instr);
}
void builder_instruction_load(Builder *builder, Value *src) {
  builder_instruction_unary(builder, INSTRUCTION_LOAD, src);
}
void builder_instruction_store(Builder *builder, Value *src, Value *dst) {
  builder_instruction_binary(builder, INSTRUCTION_STORE, src, dst);
}
void builder_instruction_icmp_ne(Builder *builder, Value *lhs, Value *rhs) {
  builder_instruction_binary(builder, INSTRUCTION_ICMP_NE, lhs, rhs);
}
void builder_new_local(Builder *builder) {
  builder_new_instruction(builder, INSTRUCTION_ALLOCA);
}
