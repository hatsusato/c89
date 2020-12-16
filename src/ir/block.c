#include "ir/block.h"

#include "ir/register.h"
#include "ir/value.h"
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
void block_append(Block *dst, Block *src) {
  ElemType *begin = vector_begin(src->vec);
  ElemType *end = vector_end(src->vec);
  while (begin < end) {
    vector_push(dst->vec, *begin++);
  }
}
Bool block_is_terminated(Block *block) {
  Value *last = vector_back(block->vec);
  return last && value_is_terminator(last);
}
