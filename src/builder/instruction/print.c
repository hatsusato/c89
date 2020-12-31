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
static void print_comma(void) {
  printf(",");
  print_space();
}
static void print_assign(void) {
  print_space();
  printf("=");
  print_space();
}
static void print_align(void) {
  printf("align");
  print_space();
  printf("4");
}
static void instruction_print_operand(Instruction *instr, Index index) {
  UTILITY_ASSERT(0 <= index && index < INSTRUCTION_OPERAND_COUNT);
  value_print(instr->operands[index]);
}
static void instruction_print_name(Instruction *instr) {
  const char *names[] = {
#define DO_HANDLE(name, str) str,
#include "instruction.def"
#undef DO_HANDLE
      "kind-count"};
  printf("%s", names[instr->ikind]);
  print_space();
}

static void instruction_pretty_ret(Instruction *instr) {
  instruction_print_name(instr);
  type_print(instr->type);
  if (instr->operands[0]) {
    print_space();
    instruction_print_operand(instr, 0);
  }
}
static void instruction_pretty_br(Instruction *instr) {
  instruction_print_name(instr);
  instruction_print_operand(instr, 0);
}
static void instruction_pretty_br_cond(Instruction *instr) {
  instruction_print_name(instr);
  printf("i1");
  print_space();
  instruction_print_operand(instr, 0);
  print_comma();
  instruction_print_operand(instr, 1);
  print_comma();
  instruction_print_operand(instr, 2);
}
static void instruction_pretty_switch(Instruction *instr) {
  instruction_print_name(instr);
  type_print(instr->type);
  print_space();
  instruction_print_operand(instr, 0);
  print_comma();
  instruction_print_operand(instr, 1);
  print_space();
  printf("[");
  print_newline();
  block_pretty_switch(value_as_block(instr->operands[2]));
  print_indent();
  printf("]");
}
static void instruction_pretty_add(Instruction *instr) {
  instruction_print(instr);
  print_assign();
  instruction_print_name(instr);
  type_print(instr->type);
  print_space();
  instruction_print_operand(instr, 0);
  print_comma();
  instruction_print_operand(instr, 1);
}
static void instruction_pretty_sub(Instruction *instr) {
  instruction_print(instr);
  print_assign();
  instruction_print_name(instr);
  type_print(instr->type);
  print_space();
  instruction_print_operand(instr, 0);
  print_comma();
  instruction_print_operand(instr, 1);
}
static void instruction_pretty_alloca(Instruction *instr) {
  instruction_print(instr);
  print_assign();
  instruction_print_name(instr);
  type_print(instr->type);
  print_comma();
  print_align();
}
static void instruction_pretty_load(Instruction *instr) {
  instruction_print(instr);
  print_assign();
  instruction_print_name(instr);
  type_print(instr->type);
  print_comma();
  type_print(instr->type);
  printf("*");
  print_space();
  instruction_print_operand(instr, 0);
  print_comma();
  print_align();
}
static void instruction_pretty_store(Instruction *instr) {
  instruction_print_name(instr);
  type_print(instr->type);
  print_space();
  instruction_print_operand(instr, 0);
  print_comma();
  type_print(instr->type);
  printf("*");
  print_space();
  instruction_print_operand(instr, 1);
  print_comma();
  print_align();
}
static void instruction_pretty_icmp_ne(Instruction *instr) {
  instruction_print(instr);
  print_assign();
  instruction_print_name(instr);
  type_print(instr->type);
  print_space();
  instruction_print_operand(instr, 0);
  print_comma();
  instruction_print_operand(instr, 1);
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
