#include "ir/value.h"

#include "ast/ast_tag.h"
#include "compare.h"
#include "set.h"
#include "sexp.h"
#include "utility.h"

typedef enum { VALUE_REGISTER, VALUE_INTEGER_CONSTANT } ValueKind;
struct struct_Value {
  ValueKind kind;
  const void *value;
};

static Value *value_new(ValueKind kind) {
  Value *value = UTILITY_MALLOC(Value);
  value->kind = kind;
  return value;
}
static void value_delete(Value *value) {
  UTILITY_FREE(value);
}
static int value_compare(Value *lhs, Value *rhs, CompareExtra extra) {
  UTILITY_UNUSED(extra);
  if (lhs->kind == rhs->kind) {
    switch (lhs->kind) {
    case VALUE_REGISTER:
      return utility_ptrcmp(lhs->value, rhs->value);
    case VALUE_INTEGER_CONSTANT:
      return utility_strcmp(lhs->value, rhs->value);
    default:
      assert(0);
      return 0;
    }
  } else {
    return utility_intcmp(lhs->kind, rhs->kind);
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
Value *value_register(Register *reg) {
  Value *value = value_new(VALUE_REGISTER);
  value->value = reg;
  return value;
}
Value *value_integer_constant(Sexp *ast) {
  Value *value = value_new(VALUE_INTEGER_CONSTANT);
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  value->value = sexp_get_symbol(ast);
  return value;
}
