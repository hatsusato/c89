#include "yyscan.h"

#include "ast/ast.h"
#include "parser.tab.h"
#include "print.h"
#include "scanner/register.h"
#include "scanner/scanner.h"
#include "set/set.h"
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
  register_declaration(scanner, ast);
}
