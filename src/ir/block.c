#include "ir/block.h"

#include "ir/register.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Block {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

Block *block_new(void) {
  Block *block = UTILITY_MALLOC(Block);
  block->kind = VALUE_BLOCK;
  register_init(&block->reg);
  block->vec = vector_new(NULL);
  block->value = NULL;
  return block;
}
void block_delete(Block *block) {
  vector_delete(block->vec);
  UTILITY_FREE(block);
}
Bool block_empty(Block *block) {
  return vector_empty(block->vec);
}
