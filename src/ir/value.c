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
void value_append(Value *dst, const Value *src) {
  ElemType *begin = vector_begin(src->vec);
  ElemType *end = vector_end(src->vec);
  while (begin < end) {
    vector_push(dst->vec, *begin++);
  }
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
void value_pretty(Value *value) {
  ElemType *begin = vector_begin(value->vec);
  ElemType *end = vector_end(value->vec);
  if (value_is_instruction(value)) {
    printf("  ");
  }
  switch (value_kind(value)) {
  case VALUE_MODULE:
    puts("target triple = \"x86_64-pc-linux-gnu\"");
    for (; begin < end; ++begin) {
      printf("\n");
      value_pretty(*begin);
    }
    return;
  case VALUE_FUNCTION:
    printf("define dso_local ");
    value_print(value);
    printf(" {\n");
    assert(begin != end);
    value_pretty(*begin++);
    for (; begin < end; ++begin) {
      printf("\n");
      register_print(&((Value *)*begin)->reg, false);
      printf(":\n");
      value_pretty(*begin);
    }
    printf("}");
    break;
  case VALUE_BLOCK:
    for (; begin < end; ++begin) {
      value_pretty(*begin);
    }
    return;
  case VALUE_INSTRUCTION_RET:
    if (0 == value_length(value)) {
      printf("ret void");
    } else {
      printf("ret i32 ");
      value_print(value_at(value, 0));
    }
    break;
  case VALUE_INSTRUCTION_BR:
    printf("br label ");
    value_print(value_at(value, 0));
    break;
  case VALUE_INSTRUCTION_BR_COND:
    printf("br i1 ");
    value_print(value_at(value, 0));
    printf(", label ");
    value_print(value_at(value, 1));
    printf(", label ");
    value_print(value_at(value, 2));
    break;
  case VALUE_INSTRUCTION_SWITCH:
    printf("switch i32 ");
    value_print(*begin++);
    printf(", label ");
    value_print(*begin++);
    printf(" [\n");
    while (begin < end) {
      printf("    i32 ");
      value_print(*begin++);
      printf(", label ");
      value_print(*begin++);
      printf("\n");
    }
    printf(" ]");
    break;
  case VALUE_INSTRUCTION_ADD:
    value_print(value);
    printf(" = add nsw i32 ");
    value_print(value_at(value, 0));
    printf(", ");
    value_print(value_at(value, 1));
    break;
  case VALUE_INSTRUCTION_ALLOCA:
    value_print(value);
    printf(" = alloca i32, align 4");
    break;
  case VALUE_INSTRUCTION_LOAD:
    value_print(value);
    printf(" = load i32, i32* ");
    value_print(value_at(value, 0));
    printf(", align 4");
    break;
  case VALUE_INSTRUCTION_STORE:
    printf("store i32 ");
    value_print(value_at(value, 0));
    printf(", i32* ");
    value_print(value_at(value, 1));
    printf(", align 4");
    break;
  case VALUE_INSTRUCTION_ICMP_NE:
    value_print(value);
    printf(" = icmp ne i32 ");
    value_print(value_at(value, 0));
    printf(", ");
    value_print(value_at(value, 1));
    break;
  default:
    assert(0);
    break;
  }
  printf("\n");
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
Bool value_is_instruction(Value *value) {
  switch (value_kind(value)) {
#define VALUE_KIND_HANDLER(k) \
  case k:                     \
    return true
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_RET);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_BR);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_BR_COND);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_SWITCH);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ADD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ALLOCA);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_LOAD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_STORE);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ICMP_NE);
#undef VALUE_KIND_HANDLER
  default:
    return false;
  }
}
