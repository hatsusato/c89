#include "instruction.h"

#include "print.h"
#include "utility.h"
#include "value.h"
#include "vector.h"

struct struct_Instruction {
  Block *parent;
  InstructionTag tag;
  Vector *operands;
};

Instruction *instruction_new(Block *block, InstructionTag tag) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->parent = block;
  instr->tag = tag;
  instr->operands = vector_new((Destructor)value_delete);
  return instr;
}
void instruction_delete(Instruction *instr) {
  assert(instr);
  vector_delete(instr->operands);
  UTILITY_FREE(instr);
}
void instruction_insert(Instruction *instr, Value *value) {
  assert(instr);
  vector_push(instr->operands, value);
}
void instruction_print(FILE *fp, Instruction *instr) {
  (void)instr;
  print_message(fp, "  ret i32 0\n");
}
