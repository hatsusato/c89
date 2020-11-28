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

static void instruction_print_add(Value *instr) {
  printf("  ");
  value_print(instr);
  printf(" = add i32 ");
  value_print(value_at(instr, 0));
  printf(", ");
  value_print(value_at(instr, 1));
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

Value *instruction_ret(Value *val) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  value_init((Value *)instr, VALUE_INSTRUCTION_RET);
  instr->lhs = val;
  instr->rhs = NULL;
  return (Value *)instr;
}
void instruction_print(Value *instr) {
  switch (value_kind(instr)) {
  case VALUE_INSTRUCTION:
    instruction_print_add(instr);
    break;
  case VALUE_INSTRUCTION_RET:
    instruction_print_ret((Instruction *)instr);
    break;
  default:
    assert(0);
    break;
  }
}
