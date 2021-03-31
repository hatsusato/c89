#include "scanner/parser.h"

#include "scanner/impl.h"
#include "scanner/register.h"
#include "utility/utility.h"

Sexp *parser_list_snoc(Sexp *list, Sexp *ast) {
  assert(sexp_is_list(list));
  return sexp_snoc(list, ast);
}
