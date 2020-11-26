#include "scanner.h"

#include "ast.h"
#include "compare.h"
#include "parser.tab.h"
#include "scanner/scanner_impl.h"
#include "scanner/yyscan.h"
#include "set.h"
#include "sexp.h"
#include "utility.h"

typedef struct {
  Ast *ast;
  Set *typedefs;
} Scanner;

static void scanner_init(yyscan_t yyscan) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  Compare *cmp = compare_new(compare_strcmp);
  yyset_extra(scanner, yyscan);
  scanner->ast = ast_new();
  scanner->typedefs = set_new(NULL, cmp);
}
static Scanner *scanner_get(yyscan_t yyscan) {
  return yyget_extra(yyscan);
}
static Set *scanner_typedefs(yyscan_t yyscan) {
  return scanner_get(yyscan)->typedefs;
}

yyscan_t scanner_new(void) {
  yyscan_t yyscan;
  int ret = yylex_init(&yyscan);
  assert(0 == ret);
  UTILITY_UNUSED(ret);
  scanner_init(yyscan);
  scanner_register(yyscan, "__builtin_va_list");
  return yyscan;
}
void scanner_delete(yyscan_t yyscan) {
  set_delete(scanner_typedefs(yyscan));
  ast_delete(scanner_ast(yyscan));
  UTILITY_FREE(scanner_get(yyscan));
  yylex_destroy(yyscan);
}
int scanner_parse(yyscan_t yyscan) {
  return yyparse(yyscan);
}
Ast *scanner_ast(yyscan_t yyscan) {
  return scanner_get(yyscan)->ast;
}
void scanner_finish(yyscan_t yyscan, Sexp *ast) {
  ast_set(scanner_ast(yyscan), ast);
}
Sexp *scanner_token(yyscan_t yyscan) {
  const char *text = yyget_text(yyscan);
  Size leng = yyget_leng(yyscan);
  const char *token = ast_symbol(scanner_ast(yyscan), text, leng);
  return sexp_symbol(token);
}
void scanner_register(yyscan_t yyscan, const char *symbol) {
  assert("redefinition of typedef" && !scanner_query(yyscan, symbol));
  set_insert(scanner_typedefs(yyscan), (ElemType)symbol);
}
Bool scanner_query(yyscan_t yyscan, const char *symbol) {
  return NULL != set_find(scanner_typedefs(yyscan), (ElemType)symbol);
}
