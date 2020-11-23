#include "scanner.h"

#include "parser.tab.h"
#include "scanner_impl.h"
#include "set.h"
#include "sexp.h"
#include "utility.h"
#include "yyscan.h"

struct struct_Scanner {
  yyscan_t yyscan;
  Ast *ast;
  Pool *typedefs;
};

Scanner *scanner_new(void) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  int ret = yylex_init(&scanner->yyscan);
  assert(0 == ret);
  (void)ret;
  yyset_extra(scanner, scanner->yyscan);
  scanner->ast = ast_new();
  scanner->typedefs = pool_new(false);
  scanner_register(scanner, "__builtin_va_list");
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  pool_delete(scanner->typedefs);
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
  assert("redefinition of typedef" && !scanner_query(scanner, symbol));
  pool_insert(scanner->typedefs, symbol);
}
Bool scanner_query(Scanner *scanner, const char *symbol) {
  return pool_contains(scanner->typedefs, symbol);
}
