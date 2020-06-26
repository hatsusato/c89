#include "scanner.h"

#include <stdio.h>

#include "parser.tab.h"
#include "utility.h"

void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}

yyscan_t scanner_new(Result *result) {
  yyscan_t scanner = nil;
  int ret = yylex_init_extra(result, &scanner);
  assert(ret == 0);
  return scanner;
}
void scanner_delete(yyscan_t scanner) {
  yylex_destroy(scanner);
}
int scanner_parse(yyscan_t scanner) {
  return yyparse(scanner);
}
void scanner_set_ast(yyscan_t scanner, AstList ast) {
  Result *result = yyget_extra(scanner);
  result_set_ast(result, ast.list);
  yyset_extra(result, scanner);
}
const char *scanner_get_text(yyscan_t scanner) {
  return yyget_text(scanner);
}
void scanner_insert_symbol(yyscan_t scanner, const char *str) {
  Result *result = yyget_extra(scanner);
  Set *symbols = result_get_symbols(result);
  set_string_insert(symbols, str);
}
