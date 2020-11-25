#include "scanner.h"

#include <string.h>

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

static int scanner_strcmp(ElemType lhs, ElemType rhs, CompareExtra extra) {
  (void)extra;
  return strcmp(lhs, rhs);
}

Scanner *scanner_new(void) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  Compare *cmp = compare_new(scanner_strcmp);
  int ret = yylex_init(&scanner->yyscan);
  assert(0 == ret);
  (void)ret;
  yyset_extra(scanner, scanner->yyscan);
  scanner->ast = ast_new();
  scanner->typedefs = set_new(NULL, cmp);
  scanner_register(scanner, "__builtin_va_list");
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  set_delete(scanner->typedefs);
  ast_delete(scanner->ast);
  yylex_destroy(scanner->yyscan);
  UTILITY_FREE(scanner);
}
int scanner_parse(Scanner *scanner) {
  return yyparse(scanner->yyscan);
}
Ast *scanner_ast(Scanner *scanner) {
  return scanner->ast;
}
void scanner_finish(Scanner *scanner, Sexp *ast) {
  ast_set(scanner->ast, ast);
}
Sexp *scanner_token(Scanner *scanner) {
  const char *text = yyget_text(scanner->yyscan);
  Size leng = yyget_leng(scanner->yyscan);
  const char *token = ast_symbol(scanner->ast, text, leng);
  return sexp_symbol(token);
}
void scanner_register(Scanner *scanner, const char *symbol) {
  assert("redefinition of typedef" &&
         !scanner_query((ElemType)scanner, symbol));
  set_insert(scanner->typedefs, (ElemType)symbol);
}
Bool scanner_query(Scanner *scanner, const char *symbol) {
  return NULL != set_find(scanner->typedefs, (ElemType)symbol);
}
