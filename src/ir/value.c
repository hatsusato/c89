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
  register_init(&header->reg);
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
