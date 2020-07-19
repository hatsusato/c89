#include "parser.h"

#include "parser.tab.h"
#include "print.h"
#include "result.h"
#include "scanner.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

void yyerror(yyscan_t scanner, const char *msg) {
  FILE *fp = stderr;
  print_message(fp, "yyerror: ");
  print_message(fp, msg);
  print_message(fp, ": ");
  print_verbatim(fp, yyget_text(scanner), yyget_leng(scanner));
  print_newline(fp);
}

Sexp *parser_symbol(AstTag tag) {
  return sexp_number(tag);
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
void parser_register(yyscan_t scanner, Sexp *ast) {
  table_register(scanner_table(scanner), ast);
}
Bool parser_query(yyscan_t scanner, const char *symbol) {
  return table_query(scanner_table(scanner), symbol);
}
void parser_push(yyscan_t scanner) {
  table_push(scanner_table(scanner));
}
void parser_pop(yyscan_t scanner) {
  table_pop(scanner_table(scanner));
}
void parser_finish(yyscan_t scanner, Sexp *ast) {
  Result *result = yyget_extra(scanner);
  assert(!result_get_sexp(result));
  result_set_sexp(result, ast);
}
