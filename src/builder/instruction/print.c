#include "print.h"

#include <stdio.h>

#include "../block.h"
#include "../type.h"
#include "struct.h"
#include "utility.h"

static void print_newline(void) {
  printf("\n");
}
static void print_space(void) {
  printf(" ");
}
static void print_indent(void) {
  print_space();
  print_space();
}
static void print_align(void) {
  printf(", align");
  print_space();
  printf("4");
}
static void instruction_print_name(Instruction *instr) {
  switch (instr->ikind) {
#define DO_HANDLE(name, str) \
  case name:                 \
    break;
#include "terminator.def"
#undef DO_HANDLE
  case INSTRUCTION_STORE:
    break;
  default:
    instruction_print(instr);
    printf(" = ");
    break;
  }
  switch (instr->ikind) {
#define DO_HANDLE(name, str) \
  case name:                 \
    printf("%s ", str);      \
    break;
#include "instruction.def"
#undef DO_HANDLE
  default:
    UTILITY_ASSERT(0);
    break;
  }
}

static void instruction_pretty_ret(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
}
static void instruction_pretty_br(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
}
static void instruction_pretty_br_cond(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  value_print_with_type(instr->operands[1], true);
  value_print_with_type(instr->operands[2], true);
}
static void instruction_pretty_switch(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  value_print_with_type(instr->operands[1], true);
  print_space();
  printf("[");
  print_newline();
  block_pretty_switch(value_as_block(instr->operands[2]));
  print_indent();
  printf("]");
}
static void instruction_pretty_add(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  value_print(instr->operands[1], true);
}
static void instruction_pretty_sub(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  value_print(instr->operands[1], true);
}
static void instruction_pretty_alloca(Instruction *instr) {
  Type *type = value_type(instruction_as_value(instr));
  instruction_print_name(instr);
  type_print(type_get_elem(type));
  print_align();
}
static void instruction_pretty_load(Instruction *instr) {
  Type *type = value_type(instruction_as_value(instr));
  instruction_print_name(instr);
  type_print(type);
  value_print_with_type(instr->operands[0], true);
  print_align();
}
static void instruction_pretty_store(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  value_print_with_type(instr->operands[1], true);
  print_align();
}
static void instruction_pretty_icmp_ne(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  value_print(instr->operands[1], true);
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
  print_indent();
  pretty[instr->ikind](instr);
  print_newline();
}
