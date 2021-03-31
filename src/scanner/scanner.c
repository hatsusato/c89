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

Scanner *scanner_new(Ast *ast) {
  yyscan_t yyscan;
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  int ret = yylex_init(&yyscan);
  assert(0 == ret);
  UTILITY_UNUSED(ret);
  yyset_extra(scanner, yyscan);
  scanner->ast = ast;
  scanner->typedefs = set_new(NULL, NULL);
  scanner->yyscan = yyscan;
  yyscan_register("__builtin_va_list", yyscan);
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  yyscan_t yyscan = scanner->yyscan;
  set_delete(scanner_typedefs(yyscan));
  UTILITY_FREE(yyget_extra(yyscan));
  yylex_destroy(yyscan);
}
int scanner_parse(Ast *ast) {
  Scanner *scanner = scanner_new(ast);
  int ret = yyparse(scanner->yyscan);
  scanner_delete(scanner);
  return ret;
}
Ast *scanner_get(Scanner *scanner) {
  yyscan_t yyscan = scanner->yyscan;
  return scanner_ast(yyscan);
}
