#include "block.h"

#include "ir/instruction.h"
#include "ir/module.h"
#include "ir/type.h"
#include "ir/value.h"
#include "printer/printer.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Block {
  ValueKind kind;
  Type *type;
  int id;
  Vector *vec;
};

Block *block_new(Module *module) {
  Block *block = UTILITY_MALLOC(Block);
  block->kind = VALUE_BLOCK;
  block->type = module_type_label(module);
  block->id = -1;
  block->vec = vector_new(NULL);
  module_insert_value(module, value_of(block));
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
  VectorElem *begin = vector_begin(src->vec);
  VectorElem *end = vector_end(src->vec);
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
  VectorElem *begin = vector_begin(block->vec);
  VectorElem *end = vector_end(block->vec);
  block->id = id++;
  while (begin < end) {
    id = instruction_set_id(*begin++, id);
  }
  return id;
}
void block_print(Block *block, Printer *printer) {
  UTILITY_ASSERT(0 <= block->id);
  printer_print(printer, "%%%d", block->id);
}
void block_print_label(Block *block, Printer *printer) {
  UTILITY_ASSERT(0 <= block->id);
  printer_print(printer, "%d:", block->id);
  printer_newline(printer);
}
void block_pretty(Block *block, Printer *printer) {
  VectorElem *begin = vector_begin(block->vec);
  VectorElem *end = vector_end(block->vec);
  while (begin < end) {
    instruction_pretty(*begin++, printer);
  }
}
void block_pretty_switch(Block *block, Printer *printer) {
  VectorElem *begin = vector_begin(block->vec);
  VectorElem *end = vector_end(block->vec);
  while (begin < end) {
    printer_print(printer, "    ");
    value_print_with_type(*begin++, false, printer);
    value_print_with_type(*begin++, true, printer);
    printer_newline(printer);
  }
}
