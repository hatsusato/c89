#include "ir/value.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "builder.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

struct struct_Value {
  ValueHeader header;
  const void *value;
};

static Value *value_new(ValueKind kind, const void *value) {
  Value *v = UTILITY_MALLOC(Value);
  value_header_init(&v->header, kind);
  v->value = value;
  return v;
}

ValueKind value_kind(Value *value) {
  return value->header.kind;
}
void value_header_init(ValueHeader *header, ValueKind kind) {
  header->kind = kind;
  header->id = 0;
}
Value *value_integer_constant(Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  return value_new(VALUE_INTEGER_CONSTANT, sexp_get_symbol(ast));
}
void value_print(Value *value) {
  switch (value_kind(value)) {
  case VALUE_INTEGER_CONSTANT:
    printf("%s", (const char *)value->value);
    break;
  default:
    printf("%%%d", value->header.id);
    break;
  }
}
int value_get_id(Value *value) {
  return value->header.id;
}
void value_set_id(Builder *builder, Value *value) {
  switch (value_kind(value)) {
  case VALUE_BLOCK:
    /* FALLTHROUGH */
  case VALUE_INSTRUCTION:
    value->header.id = builder_fresh_id(builder);
    break;
  default:
    break;
  }
}
