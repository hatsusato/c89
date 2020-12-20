#include "ir/value.h"

#include "ir/block.h"
#include "ir/constant.h"
#include "ir/instruction.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Value {
  ValueKind kind;
};

void value_print(Value *value) {
  switch (value->kind) {
  case VALUE_BLOCK:
    block_print((Block *)value);
    break;
  case VALUE_INSTRUCTION:
    instruction_print((Instruction *)value);
    break;
  case VALUE_CONSTANT:
    constant_print((Constant *)value);
    break;
  default:
    assert(0);
    break;
  }
}
