#include "ir/block.h"

#include "builder.h"
#include "ir/block_type.h"
#include "ir/instruction.h"
#include "ir/register.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "utility.h"
#include "vector.h"

struct struct_Block {
  ValueKind kind;
  int id;
  ValueHeader header;
  Register reg;
  Vector *instrs;
};

Block *block_new(void) {
  Block *block = UTILITY_MALLOC(Block);
  block->kind = VALUE_BLOCK;
  block->id = 0;
  value_header_init(&block->header, VALUE_BLOCK);
  register_init(&block->reg);
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
void block_set_id(Builder *builder, Block *block) {
  ElemType *begin = vector_begin(block->instrs);
  ElemType *end = vector_end(block->instrs);
  block->header.id = block->id = builder_fresh_id(builder);
  register_set(builder_generator(builder), &block->reg);
  for (; begin < end; ++begin) {
    value_set_id(builder, *begin);
  }
}
void block_print(Block *block) {
  ElemType *begin = vector_begin(block->instrs);
  ElemType *end = vector_end(block->instrs);
  for (; begin < end; ++begin) {
    instruction_print(*begin);
  }
}
