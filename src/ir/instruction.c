#include "ir/instruction.h"

#include "builder.h"
#include "ir/instruction_type.h"
#include "ir/register_type.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Instruction {
  ValueKind kind;
  Register *dst;
  Value *lhs, *rhs;
};

Value *instruction_binary(Builder *builder, Value *lhs, Value *rhs) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = VALUE_INSTRUCTION;
  instr->dst = builder_register(builder);
  instr->lhs = lhs;
  instr->rhs = rhs;
  return (Value *)instr;
}
