#include "ir/value.h"

#include "ast/ast_tag.h"
#include "compare.h"
#include "set.h"
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
static int value_compare(Value *lhs, Value *rhs, CompareExtra extra) {
  UTILITY_UNUSED(extra);
  if (lhs->kind == rhs->kind) {
    switch (lhs->kind) {
    case VALUE_REGISTER:
      return utility_intcmp(lhs->value.reg, rhs->value.reg);
    case VALUE_INTEGER_CONSTANT:
      return utility_strcmp(lhs->value.integer, rhs->value.integer);
    default:
      assert(0);
      return 0;
    }
  } else {
    return lhs->kind < rhs->kind ? -1 : 1;
  }
}

Set *value_pool_new(void) {
  Compare *cmp = compare_new((Cmp)value_compare);
  Set *pool = set_new((Destructor)value_delete, cmp);
  return pool;
}
void value_pool_delete(Set *pool) {
  set_delete(pool);
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
void value_delete(Value *value) {
  UTILITY_FREE(value);
}
