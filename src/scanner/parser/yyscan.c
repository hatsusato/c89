#include "yyscan.h"

#include <ctype.h>
#include <stdio.h>

#include "parser.tab.h"
#include "scanner/register.h"
#include "scanner/scanner.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

static void verbatim(FILE *fp, char c) {
  if (isprint(c)) {
    fprintf(fp, "%c", c);
  } else {
    fprintf(fp, "\\x%02x", (unsigned char)c);
  }
}

void yyerror(yyscan_t yyscanner, const char *msg) {
  FILE *fp = stderr;
  const char *text = yyget_text(yyscanner);
  int leng = yyget_leng(yyscanner);
  int i;
  fprintf(fp, "yyerror: %s: ", msg);
  for (i = 0; i < leng; ++i) {
    verbatim(fp, text[i]);
  }
  fprintf(fp, "\n");
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
Sexp *yyscan_push(Sexp *xs, Sexp *x) {
  return sexp_snoc(xs, x);
}
Sexp *yyscan_symbol(SyntaxTag tag) {
  return sexp_number(tag);
}
Sexp *yyscan_tag(SyntaxTag tag) {
  return sexp_pair(sexp_number(tag), sexp_nil());
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
