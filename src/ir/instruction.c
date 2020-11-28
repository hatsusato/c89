#include "ir/instruction.h"

#include <stdio.h>

#include "builder.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Instruction {
  ValueKind kind;
  int id;
  Value *dst, *lhs, *rhs;
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

Value *instruction_binary(Builder *builder, Value *lhs, Value *rhs) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = VALUE_INSTRUCTION;
  instr->id = 0;
  instr->dst = builder_register(builder);
  instr->lhs = lhs;
  instr->rhs = rhs;
  return (Value *)instr;
}
void instruction_print(Value *value) {
  assert(VALUE_INSTRUCTION == value_kind(value));
  instruction_print_add((Instruction *)value);
}
