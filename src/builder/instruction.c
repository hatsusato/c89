#include "instruction.h"

#include "instruction/struct.h"
#include "utility.h"

Instruction *instruction_new(void) {
  Index i = 0;
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = VALUE_INSTRUCTION;
  instr->ikind = INSTRUCTION_KIND_COUNT;
  instr->id = -1;
  while (i < INSTRUCTION_OPERAND_COUNT) {
    instr->operands[i++] = NULL;
  }
  return instr;
}
void instruction_delete(Instruction *instr) {
  UTILITY_FREE(instr);
}
Bool instruction_is_terminator(Instruction *instr) {
  switch (instr->ikind) {
#define DO_HANDLE(name, str) \
  case name:                 \
    return true;
#include "instruction/terminator.def"
#undef DO_HANDLE
  default:
    return false;
  }
}
int instruction_set_id(Instruction *instr, int id) {
  if (!instruction_is_terminator(instr) && INSTRUCTION_STORE != instr->ikind) {
    instr->id = id++;
  }
  return id;
}
