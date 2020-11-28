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
  Instruction *instr = (Instruction *)value;
  assert(VALUE_INSTRUCTION == value_kind(value));
  printf("  ");
  value_print(value);
  printf(" = add i32 ");
  value_print(instr->lhs);
  printf(", ");
  value_print(instr->rhs);
  printf("\n");
}
