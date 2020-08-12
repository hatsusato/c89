#include "block.h"

#include "instruction.h"
#include "utility.h"
#include "vector.h"

struct struct_Block {
  Vector *insts;
};

Block *block_new(void) {
  Block *block = UTILITY_MALLOC(Block);
  block->insts = vector_new((Destructor)instruction_delete);
  return block;
}
void block_delete(Block *block) {
  assert(block);
  vector_delete(block->insts);
  UTILITY_FREE(block);
}
Instruction *block_new_instruction(Block *block, InstructionTag tag) {
  Instruction *instr;
  assert(block);
  instr = instruction_new(tag);
  vector_push(block->insts, instr);
  return instr;
}
void block_print(FILE *fp, Block *block) {
  ElemType *it;
  assert(block);
  for (it = vector_begin(block->insts); it != vector_end(block->insts); ++it) {
    instruction_print(fp, (Instruction *)*it);
  }
}
