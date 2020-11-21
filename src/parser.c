#include "parser.h"

#include "parser.tab.h"
#include "print.h"
#include "register.h"
#include "scanner.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

void yyerror(yyscan_t scan, const char *msg) {
  FILE *fp = stderr;
  print_message(fp, "yyerror: ");
  print_message(fp, msg);
  print_message(fp, ": ");
  print_verbatim(fp, yyget_text(scan), yyget_leng(scan));
  print_newline(fp);
}

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
  return sexp_cons(car, cdr);
}
Sexp *parser_snoc(Sexp *xs, Sexp *x) {
  return sexp_snoc(xs, x);
}
void parser_register(yyscan_t scan, Sexp *ast) {
  Scanner *scanner = yyget_extra(scan);
  Table *table = scanner_table(scanner);
  table_register(table, ast);
  register_declaration(scanner, ast);
}
Bool parser_query(yyscan_t scan, const char *symbol) {
  Table *table = scanner_table(yyget_extra(scan));
  return table_query(table, symbol);
}
void parser_push(yyscan_t scan) {
  Table *table = scanner_table(yyget_extra(scan));
  table_push(table);
}
void parser_pop(yyscan_t scan) {
  Table *table = scanner_table(yyget_extra(scan));
  table_pop(table);
}
void parser_finish(yyscan_t scan, Sexp *ast) {
  scanner_finish(yyget_extra(scan), ast);
}
