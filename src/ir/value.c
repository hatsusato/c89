#include "ir/value.h"

#include "ast/ast_tag.h"
#include "compare.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

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

Vector *value_pool_new(void) {
  return vector_new((Destructor)value_delete);
}
void value_pool_delete(Vector *pool) {
  vector_delete(pool);
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
