#include "ir/constant.h"

#include "ast/ast_tag.h"
#include "ir/pool.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp.h"
#include "utility.h"

struct struct_Constant {
  ValueHeader header;
  const char *value;
};
typedef struct struct_Constant Constant;

Value *constant_new(Pool *pool, Sexp *ast) {
  Value *value;
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  value = pool_alloc(pool, VALUE_INTEGER_CONSTANT);
  value_set_value(value, sexp_get_symbol(ast));
  return value;
}
