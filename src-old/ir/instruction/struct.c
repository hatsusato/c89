#include "struct.h"

#include "ir/module.h"
#include "utility/utility.h"

Instruction *instruction_new(Module *module) {
  Index i = 0;
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = VALUE_INSTRUCTION;
  instr->type = NULL;
  instr->ikind = INSTRUCTION_KIND_COUNT;
  instr->id = -1;
  while (i < INSTRUCTION_OPERAND_COUNT) {
    instr->operands[i++] = NULL;
  }
  module_insert_value(module, value_of(instr));
  return instr;
}
void instruction_delete(Instruction *instr) {
  UTILITY_FREE(instr);
}
Type *instruction_type(Instruction *instr) {
  return instr->type;
}
int instruction_set_id(Instruction *instr, int id) {
  switch (instr->ikind) {
#define DO_HANDLE(name, str) \
  case name:                 \
    break;
#include "terminator.def"
#undef DO_HANDLE
  case INSTRUCTION_STORE:
    break;
  default:
    instr->id = id++;
    break;
  }
  return id;
}
