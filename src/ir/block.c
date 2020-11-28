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
