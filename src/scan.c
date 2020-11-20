#include "scan.h"

#include "parser.tab.h"
#include "print.h"
#include "result.h"
#include "sexp.h"
#include "utility.h"

yyscan_t scan_new(Result *result) {
  yyscan_t scan = NULL;
  int ret = yylex_init_extra(result, &scan);
  assert(!ret);
  (void)ret;
  return scan;
}
void scan_delete(yyscan_t scan) {
  yylex_destroy(scan);
}
int scan_parse(yyscan_t scan) {
  return yyparse(scan);
}
void scan_finish(yyscan_t scan, Sexp *sexp) {
  Result *result = yyget_extra(scan);
  assert(!result_get_sexp(result));
  result_set_sexp(result, sexp);
}
Sexp *scan_token(yyscan_t scan) {
  return sexp_string(yyget_text(scan), yyget_leng(scan));
}
Table *scan_table(yyscan_t scan) {
  Result *result = yyget_extra(scan);
  return result_get_table(result);
}
void scan_yyerror(yyscan_t scan, const char *msg) {
  FILE *fp = stderr;
  print_message(fp, "yyerror: ");
  print_message(fp, msg);
  print_message(fp, ": ");
  print_verbatim(fp, yyget_text(scan), yyget_leng(scan));
  print_newline(fp);
}
