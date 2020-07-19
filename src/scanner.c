#include "scanner.h"

#include "parser.tab.h"
#include "result.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

static Table *get_table(yyscan_t scanner) {
  Result *result = yyget_extra(scanner);
  return result_get_table(result);
}

yyscan_t scanner_new(Result *result) {
  yyscan_t scanner = NULL;
  int ret = yylex_init_extra(result, &scanner);
  assert(!ret);
  (void)ret;
  return scanner;
}
void scanner_delete(yyscan_t scanner) {
  yylex_destroy(scanner);
}
int scanner_parse(yyscan_t scanner) {
  return yyparse(scanner);
}
void scanner_finish(yyscan_t scanner, Sexp *sexp) {
  Result *result = yyget_extra(scanner);
  assert(!result_get_sexp(result));
  result_set_sexp(result, sexp);
}
Sexp *scanner_token(yyscan_t scanner) {
  return sexp_string(yyget_text(scanner), yyget_leng(scanner));
}
void scanner_push_scope(yyscan_t scanner) {
  table_push(get_table(scanner));
}
void scanner_pop_scope(yyscan_t scanner) {
  table_pop(get_table(scanner));
}
void scanner_register(yyscan_t scanner, Sexp *ast) {
  table_register(get_table(scanner), ast);
}
Bool scanner_query(yyscan_t scanner, const char *symbol) {
  return table_query(get_table(scanner), symbol);
}
