#include "scanner/parser.h"

#include "scanner/register.h"
#include "scanner/scanner_impl.h"
#include "sexp.h"
#include "utility.h"

Sexp *parser_symbol(AstTag tag) {
  return sexp_number(tag);
}
Sexp *parser_tag(AstTag tag, Sexp *list) {
  assert(sexp_is_list(list));
  return sexp_pair(sexp_number(tag), list);
}
Sexp *parser_token(yyscan_t yyscan) {
  return sexp_symbol(scanner_token(yyscan));
}
Sexp *parser_nil(void) {
  return sexp_nil();
}
Sexp *parser_cons(Sexp *car, Sexp *cdr) {
  return sexp_pair(car, cdr);
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
