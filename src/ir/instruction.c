#include "ir/instruction.h"

#include <stdio.h>

#include "builder.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "utility.h"

struct struct_Instruction {
  ValueHeader header;
  Value *lhs, *rhs;
};
typedef struct struct_Instruction Instruction;

static void instruction_print_add(Instruction *instr) {
  printf("  ");
  value_print((Value *)instr);
  printf(" = add i32 ");
  value_print(instr->lhs);
  printf(", ");
  value_print(instr->rhs);
  printf("\n");
}
static void instruction_print_ret(Instruction *instr) {
  if (instr->lhs) {
    printf("  ret i32 ");
    value_print(instr->lhs);
  } else {
    printf("  ret void");
  }
  printf("\n");
}

Value *instruction_binary(Value *lhs, Value *rhs) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  value_header_init(&instr->header, VALUE_INSTRUCTION);
  instr->lhs = lhs;
  instr->rhs = rhs;
  return (Value *)instr;
}
Value *instruction_ret(Value *val) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  value_header_init(&instr->header, VALUE_INSTRUCTION_RET);
  instr->lhs = val;
  instr->rhs = NULL;
  return (Value *)instr;
}
void instruction_print(Value *instr) {
  switch (value_kind(instr)) {
  case VALUE_INSTRUCTION:
    instruction_print_add((Instruction *)instr);
    break;
  case VALUE_INSTRUCTION_RET:
    instruction_print_ret((Instruction *)instr);
    break;
  default:
    assert(0);
    break;
  }
}
