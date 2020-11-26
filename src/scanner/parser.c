#include "scanner/parser.h"

#include "scanner/register.h"
#include "scanner/scanner_impl.h"
#include "sexp.h"
#include "utility.h"

Sexp *parser_symbol(AstTag tag) {
  return sexp_number(tag);
}
Sexp *parser_token(yyscan_t scan) {
  return scanner_token(scan);
}
Sexp *parser_nil(void) {
  return sexp_nil();
}
Sexp *parser_cons(Sexp *car, Sexp *cdr) {
  return sexp_pair(car, cdr);
}
Sexp *parser_snoc(Sexp *xs, Sexp *x) {
  return sexp_snoc(xs, x);
}
Bool parser_query(yyscan_t scan, const char *symbol) {
  return scanner_query(scan, symbol);
}
void parser_finish(yyscan_t scan, Sexp *ast) {
  scanner_finish(scan, ast);
}
