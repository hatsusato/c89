#include "print.h"

#include <stdio.h>

#include "../block.h"
#include "../type.h"
#include "struct.h"
#include "utility.h"

static void print_newline(void) {
  printf("\n");
}
static void print_indent(void) {
  printf("  ");
}
static const char *instruction_name(Instruction *instr) {
  switch (instr->ikind) {
#define DO_HANDLE(name, str) \
  case name:                 \
    return str;
#include "instruction.def"
#undef DO_HANDLE
  default:
    UTILITY_ASSERT(0);
    return NULL;
  }
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
  printf("%s ", instruction_name(instr));
}

static void instruction_pretty_ret(Instruction *instr) {
  instruction_print_name(instr);
  if (instr->operands[0]) {
    value_print_with_type(instr->operands[0], false);
  } else {
    printf("void");
  }
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
  printf(" [");
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
  instruction_print_name(instr);
  type_print(instr->type);
  type_print_align(instr->type);
}
static void instruction_pretty_load(Instruction *instr) {
  instruction_print_name(instr);
  type_print(instr->type);
  value_print_with_type(instr->operands[0], true);
  type_print_align(instr->type);
}
static void instruction_pretty_store(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  value_print_with_type(instr->operands[1], true);
  type_print_align(instr->type);
}
static void instruction_pretty_trunc(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  printf(" to ");
  type_print(instr->type);
}
static void instruction_pretty_sext(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  printf(" to ");
  type_print(instr->type);
}
static void instruction_pretty_icmp_ne(Instruction *instr) {
  instruction_print_name(instr);
  value_print_with_type(instr->operands[0], false);
  value_print(instr->operands[1], true);
}

void instruction_print(Instruction *instr) {
  printf("%%%d", instr->id);
}
void instruction_print_type(Instruction *instr) {
  type_print(instr->type);
  if (INSTRUCTION_ALLOCA == instr->ikind) {
    printf("*");
  }
}
void instruction_pretty(Instruction *instr) {
  void (*pretty[])(Instruction *) = {
      instruction_pretty_ret,     instruction_pretty_br,
      instruction_pretty_br_cond, instruction_pretty_switch,
      instruction_pretty_add,     instruction_pretty_sub,
      instruction_pretty_alloca,  instruction_pretty_load,
      instruction_pretty_store,   instruction_pretty_trunc,
      instruction_pretty_sext,    instruction_pretty_icmp_ne,
  };
  UTILITY_ASSERT(0 <= instr->ikind && instr->ikind < INSTRUCTION_KIND_COUNT);
  print_indent();
  pretty[instr->ikind](instr);
  print_newline();
}
