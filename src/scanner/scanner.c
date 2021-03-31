#include "scanner.h"

#include "ast/ast.h"
#include "parser.tab.h"
#include "set/set.h"
#include "utility/utility.h"

struct struct_Scanner {
  Ast *ast;
  Set *typedefs;
  yyscan_t yyscan;
};

Ast *scanner_ast(yyscan_t yyscan) {
  Scanner *scanner = yyget_extra(yyscan);
  return scanner->ast;
}
Set *scanner_typedefs(yyscan_t yyscan) {
  Scanner *scanner = yyget_extra(yyscan);
  return scanner->typedefs;
}

static Scanner *scanner_new(Ast *ast, yyscan_t yyscan) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  scanner->ast = ast;
  scanner->typedefs = set_new(NULL, NULL);
  scanner->yyscan = yyscan;
  return scanner;
}
static void scanner_delete(Scanner *scanner) {
  set_delete(scanner->typedefs);
  UTILITY_FREE(scanner);
}
int scanner_parse(Ast *ast) {
  yyscan_t yyscan;
  int ret = yylex_init(&yyscan);
  Scanner *scanner = scanner_new(ast, yyscan);
  UTILITY_ASSERT(0 == ret);
  yyset_extra(scanner, yyscan);
  yyscan_register("__builtin_va_list", yyscan);
  ret = yyparse(yyscan);
  scanner_delete(scanner);
  yylex_destroy(yyscan);
  return ret;
}
Ast *scanner_get(Scanner *scanner) {
  yyscan_t yyscan = scanner->yyscan;
  return scanner_ast(yyscan);
}
const char *scanner_symbol(Scanner *scanner, const char *text, Size leng) {
  return ast_symbol(scanner->ast, text, leng);
}
Bool scanner_find(Scanner *scanner, const char *symbol) {
  return set_find(scanner->typedefs, symbol) != NULL;
}
void scanner_insert(Scanner *scanner, const char *symbol) {
  set_insert(scanner->typedefs, symbol);
}
void scanner_finish(Scanner *scanner, Sexp *ast) {
  ast_set(scanner->ast, ast);
}
