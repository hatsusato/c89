#include "print.h"

#include "ir/block.h"
#include "ir/type.h"
#include "printer/printer.h"
#include "struct.h"
#include "utility/utility.h"

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
static void instruction_print_name(Instruction *instr, Printer *printer) {
  switch (instr->ikind) {
#define DO_HANDLE(name, str) \
  case name:                 \
    break;
#include "terminator.def"
#undef DO_HANDLE
  case INSTRUCTION_STORE:
    break;
  default:
    instruction_print(instr, printer);
    printer_print(printer, " = ");
    break;
  }
  printer_print(printer, "%s ", instruction_name(instr));
}

static void instruction_pretty_ret(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  if (instr->operands[0]) {
    value_print_with_type(instr->operands[0], false, printer);
  } else {
    printer_print(printer, "void");
  }
}
static void instruction_pretty_br(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
}
static void instruction_pretty_br_cond(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
  value_print_with_type(instr->operands[1], true, printer);
  value_print_with_type(instr->operands[2], true, printer);
}
static void instruction_pretty_switch(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
  value_print_with_type(instr->operands[1], true, printer);
  printer_print(printer, " [");
  printer_newline(printer);
  block_pretty_switch(value_as_block(instr->operands[2]), printer);
  printer_print(printer, "  ");
  printer_print(printer, "]");
}
static void instruction_pretty_add(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
  value_print(instr->operands[1], true, printer);
}
static void instruction_pretty_sub(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
  value_print(instr->operands[1], true, printer);
}
static void instruction_pretty_alloca(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  type_print(instr->type, printer);
  type_print_align(instr->type);
}
static void instruction_pretty_load(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  type_print(instr->type, printer);
  value_print_with_type(instr->operands[0], true, printer);
  type_print_align(instr->type);
}
static void instruction_pretty_store(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
  value_print_with_type(instr->operands[1], true, printer);
  type_print_align(instr->type);
}
static void instruction_pretty_trunc(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
  printer_print(printer, " to ");
  type_print(instr->type, printer);
}
static void instruction_pretty_sext(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
  printer_print(printer, " to ");
  type_print(instr->type, printer);
}
static void instruction_pretty_icmp_ne(Instruction *instr, Printer *printer) {
  instruction_print_name(instr, printer);
  value_print_with_type(instr->operands[0], false, printer);
  value_print(instr->operands[1], true, printer);
}

void instruction_print(Instruction *instr, Printer *printer) {
  printer_print(printer, "%%%d", instr->id);
}
void instruction_print_type(Instruction *instr, Printer *printer) {
  type_print(instr->type, printer);
  if (INSTRUCTION_ALLOCA == instr->ikind) {
    printer_print(printer, "*");
  }
}
void instruction_pretty(Instruction *instr, Printer *printer) {
  void (*pretty[])(Instruction *, Printer *) = {
      instruction_pretty_ret,     instruction_pretty_br,
      instruction_pretty_br_cond, instruction_pretty_switch,
      instruction_pretty_add,     instruction_pretty_sub,
      instruction_pretty_alloca,  instruction_pretty_load,
      instruction_pretty_store,   instruction_pretty_trunc,
      instruction_pretty_sext,    instruction_pretty_icmp_ne,
  };
  UTILITY_ASSERT(0 <= instr->ikind && instr->ikind < INSTRUCTION_KIND_COUNT);
  printer_print(printer, "  ");
  pretty[instr->ikind](instr, printer);
  printer_newline(printer);
}
