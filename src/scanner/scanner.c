#include "scanner.h"

#include "ast.h"
#include "compare.h"
#include "parser.tab.h"
#include "scanner/scanner_impl.h"
#include "scanner/yyscan.h"
#include "set.h"
#include "sexp.h"
#include "utility.h"

struct struct_Scanner {
  yyscan_t yyscan;
  Ast *ast;
  Set *typedefs;
};

yyscan_t scanner_new(void) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  Compare *cmp = compare_new(compare_strcmp);
  int ret = yylex_init(&scanner->yyscan);
  assert(0 == ret);
  UTILITY_UNUSED(ret);
  yyset_extra(scanner, scanner->yyscan);
  scanner->ast = ast_new();
  scanner->typedefs = set_new(NULL, cmp);
  scanner_register(scanner->yyscan, "__builtin_va_list");
  return scanner->yyscan;
}
void scanner_delete(yyscan_t yyscan) {
  Scanner *scanner = yyget_extra(yyscan);
  set_delete(scanner->typedefs);
  ast_delete(scanner->ast);
  yylex_destroy(scanner->yyscan);
  UTILITY_FREE(scanner);
}
int scanner_parse(yyscan_t yyscan) {
  return yyparse(yyscan);
}
Ast *scanner_ast(yyscan_t yyscan) {
  Scanner *scanner = yyget_extra(yyscan);
  return scanner->ast;
}
yyscan_t scanner_yyscan(Scanner *scanner) {
  return scanner->yyscan;
}
void scanner_finish(yyscan_t yyscan, Sexp *ast) {
  Scanner *scanner = yyget_extra(yyscan);
  ast_set(scanner->ast, ast);
}
Sexp *scanner_token(yyscan_t yyscan) {
  Scanner *scanner = yyget_extra(yyscan);
  const char *text = yyget_text(yyscan);
  Size leng = yyget_leng(yyscan);
  const char *token = ast_symbol(scanner->ast, text, leng);
  return sexp_symbol(token);
}
void scanner_register(yyscan_t yyscan, const char *symbol) {
  Scanner *scanner = yyget_extra(yyscan);
  assert("redefinition of typedef" && !scanner_query(yyscan, symbol));
  set_insert(scanner->typedefs, (ElemType)symbol);
}
Bool scanner_query(yyscan_t yyscan, const char *symbol) {
  Scanner *scanner = yyget_extra(yyscan);
  return NULL != set_find(scanner->typedefs, (ElemType)symbol);
}
