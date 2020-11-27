#include "ir/register.h"

#include "ir/value_kind.h"
#include "utility.h"

struct struct_Register {
  ValueKind kind;
  int id;
};
typedef struct struct_Register Register;

Value *register_new(void) {
  Register *reg = UTILITY_MALLOC(Register);
  reg->kind = VALUE_REGISTER;
  reg->id = 0;
  return (Value *)reg;
}
void register_set_id(Value *value, int id) {
  Register *reg = (Register *)value;
  assert(VALUE_REGISTER == reg->kind);
  reg->id = id;
}
