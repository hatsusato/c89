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
Sexp *parser_nil(const char *sym) {
  return PARSER_LIST1(sexp_symbol(sym));
}
Sexp *parser_atom(const char *sym, Sexp *atom) {
  return PARSER_LIST2(sexp_symbol(sym), atom);
}
Sexp *parser_pair(Sexp *list, Sexp *last) {
  return sexp_snoc(list, last);
}
