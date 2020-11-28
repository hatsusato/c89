#include "ir/value.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/register.h"
#include "ir/register_type.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Value {
  ValueHeader header;
  const void *value;
  Vector *vec;
};

Value *value_new(ValueKind kind) {
  Value *value = UTILITY_MALLOC(Value);
  value_init(value, kind);
  value->value = NULL;
  value->vec = vector_new(NULL);
  return value;
}
void value_delete(Value *value) {
  vector_delete(value->vec);
  UTILITY_FREE(value);
}
void value_insert(Value *value, Value *elem) {
  vector_push(value->vec, elem);
}
void value_set_value(Value *value, const void *val) {
  value->value = val;
}
Value *value_at(Value *value, Index i) {
  return vector_at(value->vec, i);
}
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
