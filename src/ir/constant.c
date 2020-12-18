#include "ir/constant.h"

#include "ir/register.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Constant {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

static Constant *constant_new(void) {
  Constant *constant = UTILITY_MALLOC(Constant);
  constant->kind = VALUE_INTEGER_CONSTANT;
  register_init(&constant->reg);
  constant->value = NULL;
  constant->vec = vector_new(NULL);
  return constant;
}

Constant *constant_integer(const char *integer) {
  Constant *constant = constant_new();
  constant->value = integer;
  return constant;
}
void constant_delete(Constant *constant) {
  vector_delete(constant->vec);
  UTILITY_FREE(constant);
}
