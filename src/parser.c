#include "parser.h"

Sexp *parser_symbol(const char *sym) {
  return sexp_symbol(sym);
}
Sexp *parser_tag(const char *sym, Sexp *ast) {
  assert(sexp_is_list(ast));
  return sexp_cons(sexp_symbol(sym), ast);
}
Sexp *parser_token(const char *sym, yyscan_t scanner) {
  return PARSER_LIST2(sexp_symbol(sym), scanner_token(scanner));
}
