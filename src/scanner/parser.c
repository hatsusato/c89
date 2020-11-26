#include "scanner/parser.h"

#include "parser.tab.h"
#include "scanner/register.h"
#include "scanner/scanner_impl.h"
#include "sexp.h"
#include "utility.h"

Sexp *parser_symbol(AstTag tag) {
  return sexp_number(tag);
}
Sexp *parser_token(yyscan_t scan) {
  return scanner_token(yyget_extra(scan));
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
void parser_register(yyscan_t scan, Sexp *ast) {
  Scanner *scanner = yyget_extra(scan);
  register_declaration(scanner, ast);
}
Bool parser_query(yyscan_t scan, const char *symbol) {
  Scanner *scanner = yyget_extra(scan);
  return scanner_query(scanner, symbol);
}
void parser_finish(yyscan_t scan, Sexp *ast) {
  scanner_finish(yyget_extra(scan), ast);
}
