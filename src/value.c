#include "value.h"

#include "instruction.h"
#include "utility.h"

struct struct_Value {
  ValueTag tag;
  union {
    Instruction *instruction;
    int integer;
  } value;
};

static Value *value_new(ValueTag tag) {
  Value *value = UTILITY_MALLOC(Value);
  value->tag = tag;
  return value;
}

void value_delete(Value *value) {
  assert(value);
  UTILITY_FREE(value);
}
