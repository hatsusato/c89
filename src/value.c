#include "value.h"

struct struct_Value {
  ValueTag tag;
  union {
    Instruction *instruction;
    int integer;
  } value;
};
