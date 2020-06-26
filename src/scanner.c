#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>

#include "parser.tab.h"
#include "utility.h"

struct struct_Extra {
  List *ast;
};

void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}

Extra *extra_new(void) {
  Extra *extra = malloc(sizeof(Extra));
  extra->ast = nil;
  return extra;
}
void extra_delete(Extra *extra) {
  assert(extra);
  free(extra);
}

yyscan_t scanner_new(void) {
  yyscan_t scanner = nil;
  int ret = yylex_init_extra(extra_new(), &scanner);
  assert(ret == 0);
  return scanner;
}
void scanner_delete(yyscan_t scanner) {
  extra_delete(yyget_extra(scanner));
  yylex_destroy(scanner);
}
int scanner_parse(yyscan_t scanner) {
  return yyparse(scanner);
}
List *scanner_get_ast(yyscan_t scanner) {
  Extra *extra = yyget_extra(scanner);
  assert(extra);
  return extra->ast;
}
void scanner_set_ast(yyscan_t scanner, AstList ast) {
  Extra *extra = yyget_extra(scanner);
  assert(extra);
  extra->ast = ast.list;
  yyset_extra(extra, scanner);
}
const char *scanner_get_text(yyscan_t scanner) {
  return yyget_text(scanner);
}
