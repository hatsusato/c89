#include "instruction.h"

#include "utility.h"
#include "value.h"
#include "vector.h"

struct struct_Instruction {
  InstructionTag tag;
  Vector *operands;
};

Instruction *instruction_new(InstructionTag tag) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->tag = tag;
  instr->operands = vector_new((Destructor)value_delete);
  return instr;
}
void instruction_delete(Instruction *instr) {
  assert(instr);
  vector_delete(instr->operands);
  UTILITY_FREE(instr);
}
void instruction_insert_register(Instruction *instr, Instruction *operand) {
  assert(instr);
  vector_push(instr->operands, value_new_register(operand));
}
void instruction_insert_integer(Instruction *instr, int operand) {
  assert(instr);
  vector_push(instr->operands, value_new_integer(operand));
}
