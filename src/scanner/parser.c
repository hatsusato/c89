#include "scanner/parser.h"

#include "scanner/impl.h"
#include "scanner/register.h"
#include "utility/utility.h"

Sexp *parser_nil(void) {
  return sexp_nil();
}
Sexp *parser_list_nil(AstTag tag) {
  return PARSER_LIST1(sexp_number(tag));
}
Sexp *parser_list_atom(AstTag tag, Sexp *ast) {
  return PARSER_LIST2(sexp_number(tag), ast);
}
Sexp *parser_list_snoc(Sexp *list, Sexp *ast) {
  assert(sexp_is_list(list));
  return sexp_snoc(list, ast);
}
