#include "ir/value.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/register.h"
#include "ir/register_type.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

struct struct_Value {
  ValueHeader header;
  const void *value;
};

ValueKind value_kind(Value *value) {
  return value->header.kind;
}
void value_init(Value *value, ValueKind kind) {
  value->header.kind = kind;
  register_init(&value->header.reg);
}
void value_print(Value *value) {
  switch (value_kind(value)) {
  case VALUE_INTEGER_CONSTANT:
    printf("%s", (const char *)value->value);
    break;
  default:
    printf("%%%d", value->header.reg.id);
    break;
  }
}
void value_set_reg(RegisterGenerator *gen, Value *value) {
  switch (value_kind(value)) {
  case VALUE_BLOCK:
    /* FALLTHROUGH */
  case VALUE_INSTRUCTION:
    register_set(gen, &value->header.reg);
    break;
  default:
    break;
  }
}
