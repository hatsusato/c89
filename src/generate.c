#include "generate.h"

#include "ast.h"
#include "sexp.h"
#include "utility.h"

static AstTag get_tag(Sexp *ast) {
  if (sexp_is_number(ast)) {
    return sexp_get_number(ast);
  } else if (sexp_is_pair(ast)) {
    return get_tag(sexp_car(ast));
  }
  return AST_NULL;
}
