#include "ir/value.h"

#include "utility.h"

typedef enum { VALUE_REGISTER, VALUE_INTEGER_CONSTANT } ValueKind;
struct struct_Value {
  ValueKind kind;
  union {
    int reg;
  } value;
};

static Value *value_new(ValueKind kind) {
  Value *value = UTILITY_MALLOC(Value);
  value->kind = kind;
  return value;
}

Value *value_register(void) {
  Value *value = value_new(VALUE_REGISTER);
  value->value.reg = 0;
  return value;
}
