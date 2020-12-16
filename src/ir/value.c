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
void value_insert(Value *value, Value *elem) {
  vector_push(value->vec, elem);
}
void value_insert_block(Value *value, Block *block) {
  vector_push(value->vec, block);
}
void value_pop(Value *value) {
  vector_pop(value->vec);
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
Value *value_last(Value *value) {
  return vector_back(value->vec);
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
void value_print_block_label(Value *block) {
  assert(VALUE_BLOCK == value_kind(block));
  register_print(&block->reg, false);
  printf(":\n");
}
void value_print_switch_block(Value *block) {
  ElemType *begin = vector_begin(block->vec);
  ElemType *end = vector_end(block->vec);
  assert(VALUE_BLOCK == value_kind(block));
  while (begin < end) {
    printf("    i32 ");
    value_print(*begin++);
    printf(", label ");
    value_print(*begin++);
    printf("\n");
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
    puts("target triple = \"x86_64-unknown-linux-gnu\"");
    for (; begin < end; ++begin) {
      printf("\n");
      value_pretty(*begin);
    }
    return;
  case VALUE_FUNCTION:
    printf("define ");
    value_print(value);
    printf(" {\n");
    assert(begin != end);
    value_pretty(*begin++);
    for (; begin < end; ++begin) {
      printf("\n");
      value_print_block_label(*begin);
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
    value_print_switch_block(*begin++);
    printf("  ]");
    break;
  case VALUE_INSTRUCTION_ADD:
    value_print(value);
    printf(" = add nsw i32 ");
    value_print(value_at(value, 0));
    printf(", ");
    value_print(value_at(value, 1));
    break;
  case VALUE_INSTRUCTION_SUB:
    value_print(value);
    printf(" = sub nsw i32 ");
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
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_SUB);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ALLOCA);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_LOAD);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_STORE);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_ICMP_NE);
#undef VALUE_KIND_HANDLER
  default:
    return false;
  }
}
Bool value_is_terminator(Value *value) {
  switch (value_kind(value)) {
#define VALUE_KIND_HANDLER(k) \
  case k:                     \
    return true
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_RET);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_BR);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_BR_COND);
    VALUE_KIND_HANDLER(VALUE_INSTRUCTION_SWITCH);
#undef VALUE_KIND_HANDLER
  default:
    return false;
  }
}
