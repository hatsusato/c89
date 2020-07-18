#include "parser.h"

#include "ast.h"
#include "scanner.h"
#include "sexp.h"
#include "utility.h"

Sexp *parser_symbol(const char *sym) {
  return sexp_number(ast_to_int(sym));
}
Sexp *parser_tag(const char *sym, Sexp *ast) {
  assert(sexp_is_list(ast));
  return PARSER_CONS(parser_symbol(sym), ast);
}
Sexp *parser_token(const char *sym, yyscan_t scanner) {
  return PARSER_LIST2(parser_symbol(sym), scanner_token(scanner));
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
