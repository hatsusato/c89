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
  assert(result);
  return result->ast;
}
void scanner_set_ast(yyscan_t scanner, AstList ast) {
  Result *result = yyget_extra(scanner);
  assert(result);
  result->ast = ast.list;
  yyset_extra(result, scanner);
}
const char *scanner_get_text(yyscan_t scanner) {
  return yyget_text(scanner);
}
