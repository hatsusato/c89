#include "yyscan.h"

#include "parser.tab.h"
#include "print.h"
#include "scanner/register.h"
#include "scanner/scanner.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

void yyerror(yyscan_t scan, const char *msg) {
  FILE *fp = stderr;
  print_message(fp, "yyerror: ");
  print_message(fp, msg);
  print_message(fp, ": ");
  print_verbatim(fp, yyget_text(scan), yyget_leng(scan));
  print_newline(fp);
}
int yyscan_parse(Scanner *scanner) {
  yyscan_t yyscanner;
  int ret = yylex_init(&yyscanner);
  UTILITY_ASSERT(0 == ret);
  yyset_extra(scanner, yyscanner);
  scanner_register(scanner, "__builtin_va_list");
  ret = yyparse(yyscanner);
  yylex_destroy(yyscanner);
  return ret;
}
Sexp *yyscan_nil(void) {
  return sexp_nil();
}
Sexp *yyscan_cons(Sexp *x, Sexp *xs) {
  return sexp_pair(x, xs);
}
Sexp *yyscan_snoc(Sexp *xs, Sexp *x) {
  return sexp_snoc(xs, x);
}
Sexp *yyscan_list(Sexp *x) {
  return yyscan_cons(x, yyscan_nil());
}
Sexp *yyscan_symbol(AstTag tag) {
  return sexp_number(tag);
}
Sexp *yyscan_tag(AstTag tag) {
  return yyscan_list(yyscan_symbol(tag));
}
Sexp *yyscan_append(Sexp *xs, Sexp *ys) {
  return sexp_append(xs, ys);
}
Sexp *yyscan_token(yyscan_t yyscanner) {
  Scanner *scanner = yyget_extra(yyscanner);
  const char *text = yyget_text(yyscanner);
  Size leng = yyget_leng(yyscanner);
  const char *symbol = scanner_symbol(scanner, text, leng);
  return sexp_symbol(symbol);
}
Bool yyscan_query(const char *symbol, yyscan_t yyscanner) {
  Scanner *scanner = yyget_extra(yyscanner);
  return scanner_exists(scanner, symbol);
}
void yyscan_finish(Sexp *ast, yyscan_t yyscanner) {
  Scanner *scanner = yyget_extra(yyscanner);
  scanner_finish(scanner, ast);
}
void yyscan_declaration(Sexp *ast, yyscan_t yyscanner) {
  Scanner *scanner = yyget_extra(yyscanner);
  scanner_register_declaration(scanner, ast);
}
