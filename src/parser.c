#include "parser.h"

#include "parser.tab.h"
#include "result.h"
#include "scanner.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

static Table *get_table(yyscan_t scanner) {
  Result *result = yyget_extra(scanner);
  return result_get_table(result);
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
  table_register(get_table(scanner), ast);
}
void parser_push(yyscan_t scanner) {
  table_push(get_table(scanner));
}
void parser_pop(yyscan_t scanner) {
  table_pop(get_table(scanner));
}
void parser_finish(yyscan_t scanner, Sexp *ast) {
  Result *result = yyget_extra(scanner);
  assert(!result_get_sexp(result));
  result_set_sexp(result, ast);
}
