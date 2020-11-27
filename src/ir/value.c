#include "ir/value.h"

#include "ast/ast_tag.h"
#include "sexp.h"
#include "utility.h"

typedef enum { VALUE_REGISTER, VALUE_INTEGER_CONSTANT } ValueKind;
struct struct_Value {
  ValueKind kind;
  union {
    int reg;
    const char *integer;
  } value;
};

static Value *value_new(ValueKind kind) {
  Value *value = UTILITY_MALLOC(Value);
  value->kind = kind;
  return value;
}

Value *value_register(void) {
  Value *value = value_new(VALUE_REGISTER);
  value->value.reg = 0;
  return value;
}
Value *value_integer_constant(Sexp *ast) {
  Value *value = value_new(VALUE_INTEGER_CONSTANT);
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  value->value.integer = sexp_get_symbol(ast);
  return value;
}
