#include "parser.h"

#include "scan.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

void yyerror(yyscan_t scan, const char *msg) {
  scan_yyerror(scan, msg);
}

Sexp *parser_symbol(AstTag tag) {
  return sexp_number(tag);
}
Sexp *parser_token(yyscan_t scan) {
  return scan_token(scan);
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
void parser_register(yyscan_t scan, Sexp *ast) {
  table_register(scan_table(scan), ast);
}
Bool parser_query(yyscan_t scan, const char *symbol) {
  return table_query(scan_table(scan), symbol);
}
void parser_push(yyscan_t scan) {
  table_push(scan_table(scan));
}
void parser_pop(yyscan_t scan) {
  table_pop(scan_table(scan));
}
void parser_finish(yyscan_t scan, Sexp *ast) {
  scan_finish(scan, ast);
}
