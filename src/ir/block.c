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

Value *block_new(void) {
  return value_new(VALUE_BLOCK);
}
void block_delete(Value *block) {
  value_delete(block);
}
void block_insert(Value *block, Value *instr) {
  assert(VALUE_INSTRUCTION == value_kind(instr) ||
         VALUE_INSTRUCTION_RET == value_kind(instr));
  value_insert(block, instr);
}
void block_set_reg(RegisterGenerator *gen, Value *block) {
  Index i, size = value_length(block);
  value_set_reg(gen, block);
  for (i = 0; i < size; ++i) {
    value_set_reg(gen, value_at(block, i));
  }
}
void block_print(Value *block) {
  Index i, size = value_length(block);
  for (i = 0; i < size; ++i) {
    instruction_print(value_at(block, i));
  }
}
