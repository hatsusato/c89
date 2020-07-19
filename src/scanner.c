#include "scanner.h"

#include "parser.tab.h"
#include "print.h"
#include "result.h"
#include "sexp.h"
#include "utility.h"

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
Table *scanner_table(yyscan_t scanner) {
  Result *result = yyget_extra(scanner);
  return result_get_table(result);
}
void scanner_print(yyscan_t scanner, const char *msg) {
  FILE *fp = stderr;
  print_message(fp, "yyerror: ");
  print_message(fp, msg);
  print_message(fp, ": ");
  print_verbatim(fp, yyget_text(scanner), yyget_leng(scanner));
  print_newline(fp);
}
