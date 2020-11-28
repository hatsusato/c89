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
static void instruction_print_ret(Value *instr) {
  if (0 == value_length(instr)) {
    printf("  ret void");
  } else {
    printf("  ret i32 ");
    value_print(value_at(instr, 0));
  }
  printf("\n");
}

void instruction_print(Value *instr) {
  switch (value_kind(instr)) {
  case VALUE_INSTRUCTION:
    instruction_print_add(instr);
    break;
  case VALUE_INSTRUCTION_RET:
    instruction_print_ret(instr);
    break;
  default:
    assert(0);
    break;
  }
}
