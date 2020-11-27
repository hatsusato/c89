#include "ir/instruction.h"

#include "builder.h"
#include "ir/register_type.h"
#include "utility.h"

struct struct_Instruction {
  Register *dst;
  Value *lhs, *rhs;
};

Instruction *instruction_binary(Builder *builder, Value *lhs, Value *rhs) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->dst = builder_register(builder);
  instr->lhs = lhs;
  instr->rhs = rhs;
  return instr;
}
