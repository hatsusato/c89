#include "ir/block.h"

#include "ir/block_type.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Block {
  ValueKind kind;
  int id;
  Vector *instrs;
};

Block *block_new(void) {
  Block *block = UTILITY_MALLOC(Block);
  block->kind = VALUE_BLOCK;
  block->id = 0;
  block->instrs = vector_new(NULL);
  return block;
}
void block_delete(Block *block) {
  vector_delete(block->instrs);
  UTILITY_FREE(block);
}
void block_insert(Block *block, Value *instr) {
  assert(VALUE_INSTRUCTION == value_kind(instr));
  vector_push(block->instrs, instr);
}
