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
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

Value *value_new(ValueKind kind) {
  Value *value = UTILITY_MALLOC(Value);
  value->kind = kind;
  register_init(&value->reg);
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
Size value_length(Value *value) {
  return vector_length(value->vec);
}
ValueKind value_kind(Value *value) {
  return value->kind;
}
void value_print(Value *value) {
  switch (value_kind(value)) {
  case VALUE_INTEGER_CONSTANT:
    printf("%s", (const char *)value->value);
    break;
  default:
    register_print(&value->reg);
    break;
  }
}
void value_pretty(Value *value) {
  ElemType *begin = vector_begin(value->vec);
  ElemType *end = vector_end(value->vec);
  switch (value_kind(value)) {
  case VALUE_BLOCK:
    for (; begin < end; ++begin) {
      value_pretty(*begin);
    }
    break;
  case VALUE_INSTRUCTION_ADD:
    printf("  ");
    value_print(value);
    printf(" = add i32 ");
    value_print(value_at(value, 0));
    printf(", ");
    value_print(value_at(value, 1));
    printf("\n");
    break;
  case VALUE_INSTRUCTION_ALLOC:
    printf("  ");
    value_print(value);
    printf(" = alloca i32\n");
    break;
  case VALUE_INSTRUCTION_STORE:
    printf("  store i32 ");
    value_print(value_at(value, 0));
    printf(", i32* ");
    value_print(value_at(value, 1));
    printf("\n");
    break;
  case VALUE_INSTRUCTION_LOAD:
    printf("  ");
    value_print(value);
    printf(" = load i32, i32* ");
    value_print(value_at(value, 0));
    printf("\n");
    break;
  case VALUE_INSTRUCTION_RET:
    if (0 == value_length(value)) {
      printf("  ret void");
    } else {
      printf("  ret i32 ");
      value_print(value_at(value, 0));
    }
    printf("\n");
    break;
  default:
    assert(0);
    break;
  }
}
void value_set_reg(RegisterGenerator *gen, Value *value) {
  ElemType *begin = vector_begin(value->vec);
  ElemType *end = vector_end(value->vec);
  switch (value_kind(value)) {
  case VALUE_BLOCK:
    register_set(gen, &value->reg);
    for (; begin < end; ++begin) {
      value_set_reg(gen, *begin);
    }
    break;
  case VALUE_INSTRUCTION_ADD:
    /* FALLTHROUGH */
  case VALUE_INSTRUCTION_ALLOC:
    /* FALLTHROUGH */
  case VALUE_INSTRUCTION_LOAD:
    register_set(gen, &value->reg);
    break;
  default:
    break;
  }
}
const char *value_kind_show(Value *value) {
  switch (value_kind(value)) {
#define VALUE_KIND_HANDLER(k) \
  case k:                     \
    return #k
    VALUE_KIND_HANDLER(VALUE_BLOCK);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ADD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ALLOC);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_STORE);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_LOAD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_RET);
    VALUE_KIND_HANDLER(VALUE_INTEGER_CONSTANT);
#undef VALUE_KIND_HANDLER
  default:
    assert(VALUE_KIND_END == value_kind(value));
    return NULL;
  }
}
Bool value_is_instruction(Value *value) {
  switch (value_kind(value)) {
#define VALUE_KIND_HANDLER(k) \
  case k:                     \
    return true
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ADD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ALLOC);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_STORE);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_LOAD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_RET);
#undef VALUE_KIND_HANDLER
  default:
    return false;
  }
}
