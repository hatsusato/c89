#include "block.h"

#include "utility.h"
#include "vector.h"

struct struct_Block {
  Vector *insts;
};

Block *block_new(void) {
  Block *block = UTILITY_MALLOC(Block);
  block->insts = vector_new(NULL);
  return block;
}
void block_delete(Block *block) {
  assert(block);
  vector_delete(block->insts);
  UTILITY_FREE(block);
}
