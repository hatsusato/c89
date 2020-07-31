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

Value *value_new_register(Instruction *instr) {
  Value *value = value_new(VALUE_REGISTER);
  value->value.instruction = instr;
  return value;
}
Value *value_new_integer(int num) {
  Value *value = value_new(VALUE_INTEGER);
  value->value.integer = num;
  return value;
}
void value_delete(Value *value) {
  assert(value);
  UTILITY_FREE(value);
}
