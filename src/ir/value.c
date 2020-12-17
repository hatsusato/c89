#include "ir/value.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/block.h"
#include "ir/function.h"
#include "ir/register.h"
#include "ir/register_type.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Value {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

Value *value_new(ValueKind kind) {
  Value *value;
  switch (kind) {
  case VALUE_FUNCTION:
    return value_of(function_new());
  case VALUE_BLOCK:
    return value_of(block_new());
  default:
    value = UTILITY_MALLOC(Value);
    value->kind = kind;
    register_init(&value->reg);
    value->value = NULL;
    value->vec = vector_new(NULL);
    return value;
  }
}
void value_delete(Value *value) {
  switch (value_kind(value)) {
  case VALUE_FUNCTION:
    function_delete((Function *)value);
    break;
  case VALUE_BLOCK:
    block_delete((Block *)value);
    break;
  default:
    vector_delete(value->vec);
    UTILITY_FREE(value);
    break;
  }
}
Value *value_of(void *value) {
  return (Value *)value;
}
void value_set_value(Value *value, const void *val) {
  value->value = val;
}
Value *value_at(Value *value, Index i) {
  return vector_at(value->vec, i);
}
Size value_length(Value *value) {
  return vector_length(value->vec);
}
ValueKind value_kind(Value *value) {
  return value->kind;
}
void value_print(Value *value) {
  switch (value_kind(value)) {
  case VALUE_FUNCTION:
    printf("i32 @%s()", (const char *)value->value);
    break;
  case VALUE_INTEGER_CONSTANT:
    printf("%s", (const char *)value->value);
    break;
  default:
    register_print(&value->reg, true);
    break;
  }
}
void value_set_reg(RegisterGenerator *gen, Value *value) {
  ElemType *begin = vector_begin(value->vec);
  ElemType *end = vector_end(value->vec);
  switch (value_kind(value)) {
  case VALUE_FUNCTION:
    while (begin < end) {
      value_set_reg(gen, *begin++);
    }
    break;
  case VALUE_BLOCK:
    register_set(gen, &value->reg);
    while (begin < end) {
      value_set_reg(gen, *begin++);
    }
    break;
#define VALUE_KIND_HANDLER(k) \
  case k:                     \
    break
    VALUE_KIND_HANDLER(VALUE_INTEGER_CONSTANT);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_RET);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_BR);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_BR_COND);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_SWITCH);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_STORE);
#undef VALUE_KIND_HANDLER
  default:
    register_set(gen, &value->reg);
    break;
  }
}
const char *value_kind_show(Value *value) {
  switch (value_kind(value)) {
#define VALUE_KIND_HANDLER(k) \
  case k:                     \
    return #k
    VALUE_KIND_HANDLER(VALUE_MODULE);
    VALUE_KIND_HANDLER(VALUE_FUNCTION);
    VALUE_KIND_HANDLER(VALUE_BLOCK);
    VALUE_KIND_HANDLER(VALUE_INTEGER_CONSTANT);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_RET);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_BR);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_BR_COND);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_SWITCH);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ADD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_SUB);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ALLOCA);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_LOAD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_STORE);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ICMP_NE);
#undef VALUE_KIND_HANDLER
  default:
    assert(VALUE_KIND_END == value_kind(value));
    return NULL;
  }
}
