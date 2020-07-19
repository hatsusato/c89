#include "parser.h"

#include "ast.h"
#include "scanner.h"
#include "sexp.h"
#include "utility.h"

Sexp *parser_symbol(AstTag tag) {
  return sexp_number(tag);
}
Sexp *parser_tag(AstTag tag, Sexp *ast) {
  assert(sexp_is_list(ast));
  return PARSER_CONS(sexp_number(tag), ast);
}
Sexp *parser_token(yyscan_t scanner) {
  return scanner_token(scanner);
}
Sexp *parser_nil(void) {
  return sexp_nil();
}
Sexp *parser_cons(Sexp *car, Sexp *cdr) {
  return sexp_cons(car, cdr);
}
Sexp *parser_snoc(Sexp *xs, Sexp *x) {
  return sexp_snoc(xs, x);
}
