#include "statement.h"

#include "ast/convert/convert.h"
#include "sexp/sexp.h"

Sexp* convert_statement(Sexp* sexp) {
  sexp = sexp_cdr(sexp);
  sexp = sexp_car(sexp);
  return convert_ast(sexp);
}
