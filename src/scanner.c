#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>

#include "parser.tab.h"
#include "utility.h"

struct struct_Result {
  List *ast;
};

void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}

Result *result_new(void) {
  Result *result = malloc(sizeof(Result));
  result->ast = nil;
  return result;
}
void result_delete(Result *result) {
  assert(result);
  free(result);
}
List *result_get_ast(Result *result) {
  assert(result);
  return result->ast;
}
void result_set_ast(Result *result, List *ast) {
  assert(result);
  result->ast = ast;
}

yyscan_t scanner_new(void) {
  yyscan_t scanner = nil;
  int ret = yylex_init_extra(result_new(), &scanner);
  assert(ret == 0);
  return scanner;
}
void scanner_delete(yyscan_t scanner) {
  result_delete(yyget_extra(scanner));
  yylex_destroy(scanner);
}
int scanner_parse(yyscan_t scanner) {
  return yyparse(scanner);
}
List *scanner_get_ast(yyscan_t scanner) {
  Result *result = yyget_extra(scanner);
  return result_get_ast(result);
}
void scanner_set_ast(yyscan_t scanner, AstList ast) {
  Result *result = yyget_extra(scanner);
  result_set_ast(result, ast.list);
  yyset_extra(result, scanner);
}
const char *scanner_get_text(yyscan_t scanner) {
  return yyget_text(scanner);
}
