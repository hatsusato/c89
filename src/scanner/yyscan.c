#include "scanner/yyscan.h"

#include "ast/ast.h"
#include "parser.tab.h"
#include "print.h"
#include "scanner.h"
#include "scanner/impl.h"
#include "scanner/register.h"

void yyerror(yyscan_t scan, const char *msg) {
  FILE *fp = stderr;
  print_message(fp, "yyerror: ");
  print_message(fp, msg);
  print_message(fp, ": ");
  print_verbatim(fp, yyget_text(scan), yyget_leng(scan));
  print_newline(fp);
}
Sexp *yyscan_token(yyscan_t yyscanner) {
  const char *text = yyget_text(yyscanner);
  Size leng = yyget_leng(yyscanner);
  Ast *ast = scanner_ast(yyscanner);
  const char *symbol = ast_symbol(ast, text, leng);
  return sexp_symbol(symbol);
}
void yyscan_finish(Sexp *ast, yyscan_t yyscanner) {
  scanner_finish(yyscanner, ast);
}
void yyscan_declaration(Sexp *ast, yyscan_t yyscanner) {
  register_declaration(yyscanner, ast);
}
