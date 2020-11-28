#include "ir/block.h"

#include "ir/block_type.h"
#include "ir/instruction.h"
#include "ir/register.h"
#include "ir/register_type.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "utility.h"
#include "vector.h"

struct struct_Block {
  ValueHeader header;
  Vector *instrs;
};

Block *block_new(void) {
  Block *block = UTILITY_MALLOC(Block);
  value_header_init(&block->header, VALUE_BLOCK);
  block->instrs = vector_new(NULL);
  return block;
}
void block_delete(Block *block) {
  vector_delete(block->instrs);
  UTILITY_FREE(block);
}
void block_insert(Block *block, Value *instr) {
  assert(VALUE_INSTRUCTION == value_kind(instr) ||
         VALUE_INSTRUCTION_RET == value_kind(instr));
  vector_push(block->instrs, instr);
}
void block_set_reg(RegisterGenerator *gen, Block *block) {
  ElemType *begin = vector_begin(block->instrs);
  ElemType *end = vector_end(block->instrs);
  value_set_reg(gen, (Value *)block);
  for (; begin < end; ++begin) {
    value_set_reg(gen, *begin);
  }
}
void block_print(Block *block) {
  ElemType *begin = vector_begin(block->instrs);
  ElemType *end = vector_end(block->instrs);
  for (; begin < end; ++begin) {
    instruction_print(*begin);
  }
}
