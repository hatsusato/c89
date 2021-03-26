#include "scanner.h"

#include "ast/ast.h"
#include "parser.tab.h"
#include "scanner/impl.h"
#include "set/set.h"
#include "utility/utility.h"

struct struct_Scanner {
  Ast *ast;
  Set *typedefs;
  yyscan_t yyscan;
};

static void scanner_init(yyscan_t yyscan) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  yyset_extra(scanner, yyscan);
  scanner->ast = ast_new();
  scanner->typedefs = set_new(NULL, NULL);
  scanner->yyscan = yyscan;
}
static Ast *scanner_ast(yyscan_t yyscan) {
  Scanner *scanner = yyget_extra(yyscan);
  return scanner->ast;
}
static Set *scanner_typedefs(yyscan_t yyscan) {
  Scanner *scanner = yyget_extra(yyscan);
  return scanner->typedefs;
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
  UTILITY_FREE(yyget_extra(yyscan));
  yylex_destroy(yyscan);
}
int scanner_parse(yyscan_t yyscan) {
  return yyparse(yyscan);
}
Ast *scanner_get(yyscan_t yyscan) {
  return scanner_ast(yyscan);
}
yyscan_t scanner_yyscan(Scanner *scanner) {
  return scanner->yyscan;
}

void scanner_finish(yyscan_t yyscan, Sexp *ast) {
  ast_set(scanner_ast(yyscan), ast);
}
const char *scanner_token(yyscan_t yyscan) {
  const char *text = yyget_text(yyscan);
  Size leng = yyget_leng(yyscan);
  return ast_symbol(scanner_ast(yyscan), text, leng);
}
void scanner_register(yyscan_t yyscan, const char *symbol) {
  assert("redefinition of typedef" && !scanner_query(yyscan, symbol));
  set_insert(scanner_typedefs(yyscan), symbol);
}
Bool scanner_query(yyscan_t yyscan, const char *symbol) {
  return set_find(scanner_typedefs(yyscan), symbol) != NULL;
}
