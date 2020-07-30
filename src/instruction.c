#include "instruction.h"

#include "utility.h"

struct struct_Instruction {
  InstructionTag tag;
};

Instruction *instruction_new(InstructionTag tag) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->tag = tag;
  return instr;
}
void instruction_delete(Instruction *instr) {
  UTILITY_FREE(instr);
}
