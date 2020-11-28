#include "ir/constant.h"

#include "ast/ast_tag.h"
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

Value *constant_new(Sexp *ast) {
  Constant *constant;
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  constant = UTILITY_MALLOC(Constant);
  value_init((Value *)constant, VALUE_INTEGER_CONSTANT);
  constant->value = sexp_get_symbol(ast);
  return (Value *)constant;
}
