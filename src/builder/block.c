#include "block.h"

#include <stdio.h>

#include "builder.h"
#include "instruction.h"
#include "module.h"
#include "utility.h"
#include "value.h"
#include "vector.h"

struct struct_Block {
  ValueKind kind;
  int id;
  Vector *vec;
};

Block *block_new(void) {
  Block *block = UTILITY_MALLOC(Block);
  block->kind = VALUE_BLOCK;
  block->id = -1;
  block->vec = vector_new(NULL);
  return block;
}
void block_delete(Block *block) {
  vector_delete(block->vec);
  UTILITY_FREE(block);
}
void block_insert(Block *block, Instruction *instr) {
  vector_push(block->vec, instr);
}
void block_insert_switch(Block *block, Value *value, Block *label) {
  vector_push(block->vec, value);
  vector_push(block->vec, label);
}
void block_append(Block *dst, Block *src) {
  ElemType *begin = vector_begin(src->vec);
  ElemType *end = vector_end(src->vec);
  while (begin < end) {
    vector_push(dst->vec, *begin++);
  }
}
Bool block_empty(Block *block) {
  return vector_empty(block->vec);
}
Instruction *block_last(Block *block) {
  Value *last = vector_back(block->vec);
  return last ? value_as_instruction(last) : NULL;
}
int block_set_id(Block *block, int id) {
  ElemType *begin = vector_begin(block->vec);
  ElemType *end = vector_end(block->vec);
  block->id = id++;
  while (begin < end) {
    id = instruction_set_id(*begin++, id);
  }
  return id;
}
void block_print(Block *block) {
  UTILITY_ASSERT(0 <= block->id);
  printf("%%%d", block->id);
}
void block_print_label(Block *block) {
  UTILITY_ASSERT(0 <= block->id);
  printf("%d:\n", block->id);
}
void block_pretty(Block *block) {
  ElemType *begin = vector_begin(block->vec);
  ElemType *end = vector_end(block->vec);
  while (begin < end) {
    instruction_pretty(*begin++);
  }
}
void block_pretty_switch(Block *block) {
  ElemType *begin = vector_begin(block->vec);
  ElemType *end = vector_end(block->vec);
  while (begin < end) {
    printf("    ");
    value_print(*begin++, true);
    printf(", ");
    value_print(*begin++, true);
    printf("\n");
  }
}

Block *builder_new_block(Builder *builder) {
  Module *module = builder_get_module(builder);
  return module_new_block(module);
}
