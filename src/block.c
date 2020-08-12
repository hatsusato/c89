#include "block.h"

#include "instruction.h"
#include "utility.h"
#include "vector.h"

struct struct_Block {
  Function *parent;
  Vector *insts;
};

Block *block_new(Function *func) {
  Block *block = UTILITY_MALLOC(Block);
  block->parent = func;
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
  instr = instruction_new(block, tag);
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
